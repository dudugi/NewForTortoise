#include "StdAfx.h"
#include "QL_HttpClient.h"
#include <atlutil.h>


#include "crypto\include\osrng.h"
using CryptoPP::AutoSeededRandomPool;

#include <cstdlib>

#include "crypto\include\cryptlib.h"
using CryptoPP::Exception;

#include "crypto\include\hex.h"
using CryptoPP::HexEncoder;
using CryptoPP::HexDecoder;

#include "crypto\include\filters.h"
using CryptoPP::StringSink;
using CryptoPP::StringSource;
using CryptoPP::StreamTransformationFilter;

#include "crypto\include\aes.h"
using CryptoPP::AES;

#include "crypto\include\ccm.h"
using CryptoPP::CBC_Mode;

#include "crypto\include\config.h"
#include "CommonAPI.h"

byte s_key[CryptoPP::AES::DEFAULT_KEYLENGTH];
byte s_iv[CryptoPP::AES::DEFAULT_KEYLENGTH];

#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include "QlFileTransferEx.h"
#include <sys\stat.h>
#include <sstream>


#define URL_KEY_COMMAND    _T("/file/command")//move copy对应需要的url附加
#define URL_KEY_DEL        _T("/file/delete/dir")//删除对应的url
#define URL_KEY_GETLIST    _T("/file/get/dir")//获取列表对应的url
#define URL_KEY_DOWNLOAD   _T("/file/download")//下载对应的url
#define URL_KEY_UPLOAD     _T("/file/upload")//下载对应的url

#define AES_KEY   "woshijiamisuijis"
//head所包含信息的key
#define HEAD_USER    _T("userName")
#define HEAD_TOKEN   _T("token")
#define HEAD_RANDKEY _T("randKey")
//Command命令包含的json对应的key
#define COMMAND_JSON_SRCFILE  "srcFile"
#define COMMAND_JSON_DESFILE  "desFile"
#define COMMAND_JSON_PARAMS   "params"
#define COMMAND_JSON_COMMAND  "command"
#define COMMAND_JSON_MOVE     "move"
#define COMMAND_JSON_COPY     "copy"
//删除命令对应参数的key
#define COMMAND_DELETE_KEY    _T("cFileName")
//获取列表对应参数的key
#define COMMAND_GETLIST_KEY   _T("path")
//下载文件对应参数的key
#define COMMAND_DOWNLOAD_KEY   _T("cFileName")
//上传文件对应参数的key
#define COMMAND_UPLOAD_KEY    _T("cFileName")
#define COMMAND_UPLOAD_FILE   "file"
#define COMMAND_UPLOAD_REMOTEFILENAME "remoteFileName"

#define LOGIN_ERROR_STATUS_CODE  403
#define LOGIN_ERROR_STATUS_NOTFOND  404
#define LOGIN_ERROR_STATUS_NORMAL   200

//写入数据到字符串里面...
static size_t OnWriteStringData(void* buffer, size_t size, size_t nmemb, void* lpVoid)
{
   std::string* str = dynamic_cast<std::string*>((std::string *)lpVoid);
   if( NULL == str || NULL == buffer )
   {
      return -1;
   }

   char* pData = (char*)buffer;
   str->append(pData, size * nmemb);
   return nmemb;
}

static int progress_callback(void *clientp,   curl_off_t dltotal,   curl_off_t dlnow,   curl_off_t ultotal,   curl_off_t ulnow)
{
   HWND hRecvWnd = (HWND)clientp;

   //获取对应的百分比
   int nPercent = 0;
   if (0 != ultotal)
   {
      nPercent = ulnow * 100 / ultotal;
   }
   if (0 != dltotal && 0 != nPercent)
   {
      nPercent = dlnow * 100 / dltotal;
   }

   if (NULL != hRecvWnd)
   {
      ::PostMessage(hRecvWnd,WM_QL_FTP_PROGRESS,nPercent,0);
   }

   //从此回调返回非零值将导致libcurl中止传输并返回CURLE_ABORTED_BY_CALLBACK。
   return 0;
}

QL_HttpClient::QL_HttpClient(const CString & strIP,const CString & strUser, const CString & strPassword)
{
   m_strIP = strIP;
   m_strUserName = strUser;
   m_strUserPassword = strPassword;
}

QL_HttpClient::~QL_HttpClient(void)
{
}

void QL_HttpClient::Http_ProcessMsg(HWND hWnd)
{
   m_hProcess = hWnd;
}

int QL_HttpClient::Http_Delete(const CString & strServerFileName)
{
   CString strUrl;
   strUrl = m_strIP;

   if (strServerFileName.IsEmpty())
   {
      return HTTP_RET_CODE_FAIL;
   }

   strUrl+= URL_KEY_DEL;
   char szParam[MAX_PATH],szUrl[MAX_PATH];
   CString strDelParam = _T("");
   strDelParam.Format(_T("%s=%s"),COMMAND_DELETE_KEY, EncodeParam(strServerFileName));
   memset(szParam, 0, sizeof(szParam));
   memset(szUrl,0,sizeof(szUrl));
#ifdef _UNICODE
   QLCOMAPI.WCharToMByte(strDelParam,szParam,sizeof(szParam)/sizeof(szParam[0]));
   QLCOMAPI.WCharToMByte(strUrl,szUrl,sizeof(szUrl)/sizeof(szUrl[0]));
#else
   strncpy_s(szParam,(LPSTR)(LPCTSTR)strDelParam, sizeof(szParam) - 1);
   strncpy_s(szUrl,(LPSTR)(LPCTSTR)strUrl, sizeof(szUrl) - 1);
#endif // _DEBUG

   std::string sResult;
   CURLcode res;
   CURL* curl = curl_easy_init();
   if(NULL == curl)
   {
      return HTTP_RET_CODE_FAIL;
   }

   curl_easy_setopt(curl, CURLOPT_URL, szUrl);

   //附加用户信息头
   auto plist = AppendUserInfo(NULL);
   curl_easy_setopt(curl,CURLOPT_HTTPHEADER,plist);

   curl_easy_setopt(curl, CURLOPT_POST, 1);
   curl_easy_setopt(curl, CURLOPT_POSTFIELDS, szParam);
   curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);

   curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, OnWriteStringData);
   curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&sResult);
   curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
   curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 3);
   curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3);
   res = curl_easy_perform(curl);
   BOOL bIsLoginError = IsLoginError(curl);
   curl_easy_cleanup(curl);

   if (res == CURLE_OK && !bIsLoginError)
   {
      CString strResult = theApp.UTF8_TO_UNICODE(sResult);
      if (strResult.IsEmpty())
      {
         strResult = _T("{}");
      }
      //登录成功的话 就解析反馈的json
      char sRet[3000];
      memset(sRet,0,sizeof(sRet)/sizeof(sRet[0]));
#ifdef _UNICODE
      QLCOMAPI.WCharToMByte(strResult,sRet,sizeof(sRet)/sizeof(sRet[0]));
#else
      strncpy_s(sRet,(LPSTR)(LPCTSTR)strResult, sizeof(sRet) - 1);
#endif // _DEBUG
      //解析返回值
      rapidjson::Document document;
      document.Parse(sRet);

      if (document.HasMember("state"))
      {
         if(document["state"].IsInt())
         {
            if(1 == document["state"].GetInt())
            {//返回操作成功的值
               //表示操作成功 此处不处理了
            }
            else
            {
               return HTTP_RET_CODE_FAIL;
            }
         }
      }
   }
   else
   {
      //登录失败
      return HTTP_RET_CODE_LOGIN_ERROR;
   }

   return HTTP_RET_CODE_SUCCESS;
}

int QL_HttpClient::Http_Getlist(const CString & strPath,FileMsg **ppItems,int *num,DWORD dwStyle)
{
   CString strConfigUrl = m_strIP;

   CString strUrl;
   strUrl.Format(_T("%s%s?%s=%s"),strConfigUrl,URL_KEY_GETLIST,COMMAND_GETLIST_KEY, EncodeParam(strPath));

   char szUrl[MAX_PATH];
   memset(szUrl,0,sizeof(szUrl));
#ifdef _UNICODE
   QLCOMAPI.WCharToMByte(strUrl,szUrl,sizeof(szUrl)/sizeof(szUrl[0]));
#else
   strncpy_s(szUrl,(LPSTR)(LPCTSTR)strUrl, sizeof(szUrl) - 1);
#endif // _DEBUG

   CURL *curl;
   CURLcode res;

   curl = curl_easy_init();
   if (NULL == curl)
   {
      return HTTP_RET_CODE_FAIL;
   }
   std::string sResult;
   curl_easy_setopt(curl, CURLOPT_URL, szUrl);
   curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
   curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,  OnWriteStringData);
   curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&sResult);
   //curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "cookie.txt");

   auto plist = AppendUserInfo(NULL);

   curl_easy_setopt(curl,CURLOPT_HTTPHEADER,plist);

   /**
   * 当多个线程都使用超时处理的时候，同时主线程中有sleep或是wait等操作。
   * 如果不设置这个选项，libcurl将会发信号打断这个wait从而导致程序退出。
   */
   curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
   curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 5);
   curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5);
   res = curl_easy_perform(curl);

   long http_code = 0;
   curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &http_code);
   //404也当做失败处理
   BOOL bLoginError = http_code != LOGIN_ERROR_STATUS_NORMAL;//只要不等于200 都是错误
   curl_easy_cleanup(curl);

   CString strResult = theApp.UTF8_TO_UNICODE(sResult);
   if (strResult.IsEmpty())
   {
      strResult = _T("{}");
   }
   if (res == CURLE_OK && !bLoginError)
   {//登录成功的话 就解析反馈的json
      char sRet[3000];
      memset(sRet,0,sizeof(sRet)/sizeof(sRet[0]));
#ifdef _UNICODE
      QLCOMAPI.WCharToMByte(strResult,sRet,sizeof(sRet)/sizeof(sRet[0]));
#else
      strncpy_s(sRet,(LPSTR)(LPCTSTR)strResult, sizeof(sRet) - 1);
#endif // _DEBUG

      rapidjson::Document document;
      document.Parse(sRet);

      CString strDisplay;
      if (document.HasMember("rows"))
      {
         rapidjson::Value & contents = document["rows"];
         if (contents.IsArray()) 
         {
            *ppItems = (FileMsg*)malloc(sizeof(FileMsg)*contents.Size());
            memset(*ppItems,0,sizeof(FileMsg)*contents.Size());

            for (size_t i = 0; i < contents.Size(); ++i) {
               rapidjson::Value & v = contents[i];
               assert(v.IsObject());
               if (v.HasMember("getName") && v["getName"].IsString()) {
                  strncpy_s((*ppItems)[i].filename,v["getName"].GetString(),strlen(v["getName"].GetString()));
               }
               if (v.HasMember("isFile") && v["isFile"].IsBool()) {
                  (*ppItems)[i].nFileType = v["isFile"].GetBool() ? FTP_TYPE_FILE : FTP_TYPE_DIR ;
               }
               if (v.HasMember("length") && v["length"].IsNumber()) {
                  (*ppItems)[i].nFileSize = v["length"].GetUint64();
               }
               if (v.HasMember("lastModified") && v["lastModified"].IsNumber()) {
                  time_t t;
                  t = v["lastModified"].GetUint64() /1000;
                  (*ppItems)[i].tTime = CTime(t);
               }
            }

            *num = contents.Size();
         }
      }
      
   }
   else if (bLoginError || res == CURLE_OPERATION_TIMEDOUT)
   {
      //如果登录失败了
      return HTTP_RET_CODE_LOGIN_ERROR;
   }
   return HTTP_RET_CODE_SUCCESS;
}

int QL_HttpClient::Http_Download(const CString &strLocalPath, const CString & strServerPath)
{
   CString strUrl = m_strIP;
   strUrl.Format(_T("%s%s?%s=%s"),
      m_strIP,
      URL_KEY_DOWNLOAD,
      COMMAND_DOWNLOAD_KEY,
      EncodeParam(strServerPath)
      );

   char szUrl[MAX_PATH],szLocalPath[MAX_PATH];
   memset(szUrl, 0, sizeof(szUrl));
   memset(szLocalPath, 0, sizeof(szLocalPath));

#ifdef _UNICODE
   QLCOMAPI.WCharToMByte(strUrl,szUrl,sizeof(szUrl)/sizeof(szUrl[0]));
   QLCOMAPI.WCharToMByte(strLocalPath,szLocalPath,sizeof(szLocalPath)/sizeof(szLocalPath[0]));
#else
   strncpy_s(szUrl,(LPSTR)(LPCTSTR)strUrl, sizeof(szUrl) - 1);
   strncpy_s(szLocalPath,(LPSTR)(LPCTSTR)strLocalPath, sizeof(szLocalPath) - 1);
#endif // _DEBUG

   CURL *curl;
   CURLcode res;
   std::string sResult;
   curl = curl_easy_init();
   if (NULL == curl)
   {
      return HTTP_RET_CODE_FAIL;
   }

   curl_easy_setopt(curl, CURLOPT_URL, szUrl);

   char ac[4] = "wb";
   FILE * pFile = fopen(szLocalPath, ac);
   if (NULL == pFile)
   {
      return HTTP_RET_CODE_FAIL;
   }
   curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
   curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, fwrite/*OnWriteStringData*/);
   curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)pFile/*&sResult*/);
   curl_slist *plist = curl_slist_append(NULL, 
      "Content-Type: 'application/octet-stream'");
   //附加用户信息头
   plist = AppendUserInfo(plist);
   curl_easy_setopt(curl,CURLOPT_HTTPHEADER,plist);
   /**
   * 当多个线程都使用超时处理的时候，同时主线程中有sleep或是wait等操作。
   * 如果不设置这个选项，libcurl将会发信号打断这个wait从而导致程序退出。
   */
   curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
   curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 50);
   curl_easy_setopt(curl, CURLOPT_TIMEOUT, 50);
   res = curl_easy_perform(curl);

   long http_code = 0;
   curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &http_code);
   BOOL bIsLoginError = http_code == LOGIN_ERROR_STATUS_CODE;

   curl_easy_cleanup(curl);

   fflush(pFile);
   fclose(pFile);

   if (res == CURLE_OK && !bIsLoginError)
   {
      if (http_code != 200)
      {
         return HTTP_RET_CODE_FAIL;
      }
   }
   else if (http_code == LOGIN_ERROR_STATUS_NOTFOND)//404被当做找不到文件
   {
      return HTTP_RET_CODE_FILE_NOTEXISTS;
   }
   else
   {
      //登录失败
      return HTTP_RET_CODE_LOGIN_ERROR;
   }

   if (NULL != m_hProcess)
   {
      ::PostMessage(m_hProcess,WM_QL_FTP_PROGRESS,100,1);
   }

   return HTTP_RET_CODE_SUCCESS;
}

int QL_HttpClient::Http_DownDir(const CString & strLocalDir, const CString &strServerDirName,int &nFileNum, int &nDirNum,HWND hWnd,DWORD wpMsg,int nFlag,BOOL bNoDir,BOOL bZipDel,BOOL bUnZipFailRename)
{
   //1.新建文件夹到本地目录
   if (!PathFileExists(strLocalDir))
   {
      if (!::CreateDirectory(strLocalDir,NULL))
      {
         return HTTP_RET_CODE_FAIL;
      }
   }
   //2.获取云端目录列表
   FileMsg *pData = NULL;
   int num = 0;

   int nRet = Http_Getlist(strServerDirName,&pData,&num,FS_DEFAULT);
   if(nRet != HTTP_RET_CODE_SUCCESS){
      printf(("get list error!\n"));
      return nRet;
   }

   if(pData && num>0)
   { //文件夹非空
      for(int i=0;i<num;i++)
      {
         int nLen = strlen(pData[i].filename);
         if('.' == pData[i].filename[nLen-1])//.和..跳过
            continue;

         CString strFarName;

         CString strFileName(pData[i].filename);
         strFarName.Format(_T("%s/%s"),strServerDirName,strFileName);

         CString strOutPathName,strNoZipPathName;

         if(pData[i].nFileType == FTP_TYPE_FILE)
         {//若是文件，则直接下载
            strOutPathName.Format(_T("%s/%sQLtransDownload"),strLocalDir,strFileName);
            strNoZipPathName.Format(_T("%s/%s"),strLocalDir,strFileName);
            LpMsg_QLtransEx *pLpMsg = new LpMsg_QLtransEx;
            ZeroMemory(pLpMsg,sizeof(LpMsg_QLtransEx));
            nRet = Http_Download(strOutPathName,strFarName);
            if (nRet != HTTP_RET_CODE_SUCCESS)
            {
               if (NULL != hWnd)
               {
                  pLpMsg->nFlag = nFlag;
                  pLpMsg->nAction = FTP_ACTION_FAIL;
                  //转char *
                  char szLocalPath[MAX_PATH] = {0};
#ifdef _UNICODE
                  QLCOMAPI.WCharToMByte(strNoZipPathName,szLocalPath,sizeof(szLocalPath)/sizeof(szLocalPath[0]));
#else
                  strncpy_s(szLocalPath,(LPSTR)(LPCTSTR)strNoZipPathName, sizeof(szLocalPath) - 1);
#endif // _DEBUG
                  SendMessage(hWnd,wpMsg,(WPARAM)szLocalPath,(LPARAM)pLpMsg);
               }
               free(pData);pData=NULL;
               return nRet;
            }
            else
            {
               if(-1 == TransferEx_UnzipFile(strOutPathName,bZipDel))
               {
                  if (bUnZipFailRename)
                  {
                     MoveFileEx(strOutPathName,strNoZipPathName,MOVEFILE_REPLACE_EXISTING|MOVEFILE_COPY_ALLOWED);
                  }
               }

               if (NULL != hWnd)
               {
                  pLpMsg->nFlag = nFlag;
                  pLpMsg->nAction = FTP_ACTION_SUC;

                  //转char *
                  char szLocalPath[MAX_PATH] = {0};
#ifdef _UNICODE
                  QLCOMAPI.WCharToMByte(strNoZipPathName,szLocalPath,sizeof(szLocalPath)/sizeof(szLocalPath[0]));
#else
                  strncpy_s(szLocalPath,(LPSTR)(LPCTSTR)strNoZipPathName, sizeof(szLocalPath) - 1);
#endif // _DEBUG
                  SendMessage(hWnd,wpMsg,(WPARAM)szLocalPath,(LPARAM)pLpMsg);
               }
            }

            nFileNum++;
         }
         else{
            if(bNoDir)
            {
               nRet = Http_DownDir(strLocalDir,strFarName,nFileNum,nDirNum,hWnd,wpMsg,nFlag,bNoDir,bZipDel,bUnZipFailRename);
               if( nRet != HTTP_RET_CODE_SUCCESS ){//若是文件夹，则递归下载
                  free(pData);pData=NULL;
                  return nRet;
               }
            }
            else
            {
               strOutPathName.Format(_T("%s/%s"),strLocalDir,strFileName);
               nRet = Http_DownDir(strOutPathName,strFarName,nFileNum,nDirNum,hWnd,wpMsg,nFlag,bNoDir,bZipDel,bUnZipFailRename);
               if( nRet == HTTP_RET_CODE_SUCCESS ){//若是文件夹，则递归下载
                  free(pData);pData=NULL;
                  return nRet;
               }
            }
         }
      }
   }
   if(pData){
      free(pData);
      pData=NULL;
   }
   return HTTP_RET_CODE_SUCCESS;
}

int QL_HttpClient::Http_DownByEx(const CString & strLocalDir, const CString &strServerDirName, const CString & strExtension,FilePathMsg ** szFilePath,int &nFileNum,BOOL bDir,HWND hWnd,DWORD wpMsg,int nFlag,BOOL bNoDir,BOOL bZipDel,BOOL bUnZipFailRename)
{
   //建立本地文件夹
   if (!PathFileExists(strLocalDir + _T("/")))
   {
      if (!::CreateDirectory(strLocalDir + _T("/"),NULL))
      {
         return HTTP_RET_CODE_FAIL;
      }
   }
   //2.获取文件列表
   FileMsg *pData = NULL;
   int num = 0;

   int nRet = Http_Getlist(strServerDirName,&pData,&num,FS_DEFAULT);
   if(nRet != HTTP_RET_CODE_SUCCESS){
      printf(("get list error!\n"));
      return nRet;
   }

   if(pData && num>0)
   { //文件夹非空
      CStringList oStrList;
      for(int i=0;i<num;i++)
      {
         int nLen = strlen(pData[i].filename);
         if('.' == pData[i].filename[nLen-1])//.和..跳过
            continue;

         CString strFileName(pData[i].filename);
         CString strFarName;
         strFarName.Format(_T("%s/%s"),strServerDirName,strFileName);

         CString strOutPathName,strNoZipPathName;
         if(pData[i].nFileType == FTP_TYPE_FILE)
         {//若是文件，则直接下载
            //增加文件后缀过滤器
            CString strNameEx = PathFindExtension(strFarName);
            if (0 == strNameEx.CompareNoCase(strExtension))//后缀一致才下载
            {
               strOutPathName.Format(_T("%s/%sQLtransDownload"),strLocalDir,strFileName);
               strNoZipPathName.Format(_T("%s/%s"),strLocalDir,strFileName);
               LpMsg_QLtransEx *pLpMsg = new LpMsg_QLtransEx;
               ZeroMemory(pLpMsg,sizeof(LpMsg_QLtransEx));
               nRet = Http_Download(strOutPathName,strFarName);
               if (nRet != HTTP_RET_CODE_SUCCESS)
               {
                  if (NULL != hWnd)
                  {
                     pLpMsg->nFlag = nFlag;
                     pLpMsg->nAction = FTP_ACTION_FAIL;
                     //转char *
                     char szLocalPath[MAX_PATH] = {0};
#ifdef _UNICODE
                     QLCOMAPI.WCharToMByte(strNoZipPathName,szLocalPath,sizeof(szLocalPath)/sizeof(szLocalPath[0]));
#else
                     strncpy_s(szLocalPath,(LPSTR)(LPCTSTR)strNoZipPathName, sizeof(szLocalPath) - 1);
#endif // _DEBUG
                     SendMessage(hWnd,wpMsg,(WPARAM)szLocalPath,(LPARAM)pLpMsg);
                  }
                  free(pData);pData=NULL;
                  return nRet;
               }
               else
               {
                  if(-1 == TransferEx_UnzipFile(strOutPathName,bZipDel))
                  {
                     if (bUnZipFailRename)
                     {
                        MoveFileEx(strOutPathName,strNoZipPathName,MOVEFILE_REPLACE_EXISTING|MOVEFILE_COPY_ALLOWED);
                     }
                  }

                  oStrList.AddTail(strOutPathName);
                  if (NULL != hWnd)
                  {
                     pLpMsg->nFlag = nFlag;
                     pLpMsg->nAction = FTP_ACTION_SUC;

                     //转char *
                     char szLocalPath[MAX_PATH] = {0};
#ifdef _UNICODE
                     QLCOMAPI.WCharToMByte(strNoZipPathName,szLocalPath,sizeof(szLocalPath)/sizeof(szLocalPath[0]));
#else
                     strncpy_s(szLocalPath,(LPSTR)(LPCTSTR)strNoZipPathName, sizeof(szLocalPath) - 1);
#endif // _DEBUG
                     SendMessage(hWnd,wpMsg,(WPARAM)szLocalPath,(LPARAM)pLpMsg);
                  }
               }

               nFileNum++;
            }
         }
         else{

            if (!bDir)
            {
               continue;
            }

            FilePathMsg * szDirPathRecv = NULL;
            int nDirFileNum = 0;

            if(bNoDir)
            {
               nRet = Http_DownByEx(strLocalDir,strFarName,strExtension,&szDirPathRecv,nDirFileNum,bDir,hWnd,wpMsg,nFlag,bNoDir,bZipDel,bUnZipFailRename);
               if( nRet != HTTP_RET_CODE_SUCCESS ){//若是文件夹，则递归下载
                  free(pData);pData=NULL;
                  return nRet;
               }
            }
            else
            {
               strOutPathName.Format(_T("%s/%s"),strLocalDir,strFileName);

               nRet = Http_DownByEx(strOutPathName,strFarName,strExtension,&szDirPathRecv,nDirFileNum,bDir,hWnd,wpMsg,nFlag,bNoDir,bZipDel,bUnZipFailRename);
               if( nRet != HTTP_RET_CODE_SUCCESS ){//若是文件夹，则递归下载
                  free(pData);pData=NULL;
                  return nRet;
               }
            }

            //下载成功  将所有数据拷贝到strList当中
            int nDirFileIndex = 0;
            for (nDirFileIndex = 0;nDirFileIndex < nDirFileNum;nDirFileIndex++)
            {
               CString strFilePath(szDirPathRecv[nDirFileIndex].filePath);

               oStrList.AddTail(strFilePath);
            }
            nFileNum += nDirFileNum;

            //释放内存
            if (NULL != szDirPathRecv)
            {
               free(szDirPathRecv);
               szDirPathRecv = NULL;
            }
         }
      }

      *szFilePath = (FilePathMsg *)malloc(sizeof(FilePathMsg) * (nFileNum));//二维的字符串数组指针   
      memset( *szFilePath,0,sizeof(FilePathMsg) * (nFileNum));
      int nIndex = 0,nCount = oStrList.GetCount();
      for (nIndex = 0;nIndex < (nFileNum);nIndex++)
      {
#ifdef _UNICODE
         QLCOMAPI.WCharToMByte(oStrList.GetAt(oStrList.FindIndex(nIndex)),(*szFilePath)[nIndex].filePath,MAX_PATH);
#else
         strncpy_s((*szFilePath)[nIndex].filePath,(LPSTR)(LPCTSTR)oStrList.GetAt(oStrList.FindIndex(nIndex)), MAX_PATH - 1);
#endif // _UNICODE
      }
   }
   if(pData){
      free(pData);
      pData=NULL;
   }
   return HTTP_RET_CODE_SUCCESS;

}

int QL_HttpClient::Http_Upload(const CString & strLocalPath, const CString & strServerPath,const CString & strServerFileName)
{
   CString strUrl = m_strIP;

   FileMsg *pItem = NULL;
   int nNum = 0;
   //获取一下空路径对应的列表以免连接错误.....
   int nRet = Http_Getlist(_T(""),&pItem,&nNum,FS_DEFAULT);
   if (NULL != pItem)
   {
      delete pItem;
      pItem = NULL;
   }
   if (nRet == HTTP_RET_CODE_LOGIN_ERROR)
   {
      return HTTP_RET_CODE_LOGIN_ERROR;
   }

   strUrl.Format(_T("%s%s?%s=%s"),m_strIP,URL_KEY_UPLOAD,COMMAND_UPLOAD_KEY,EncodeParam(strServerPath));

   char szRemoteFileName[MAX_PATH],szFilePath[MAX_PATH],szUrl[MAX_PATH];
   memset(szRemoteFileName,0,sizeof(szRemoteFileName));
   memset(szFilePath, 0, sizeof(szFilePath));
   memset(szUrl, 0, sizeof(szUrl));
#ifdef _UNICODE
   QLCOMAPI.WCharToMByte(EncodeParam(strServerFileName),szRemoteFileName,sizeof(szRemoteFileName)/sizeof(szRemoteFileName[0]));
   QLCOMAPI.WCharToMByte(strLocalPath,szFilePath,sizeof(szFilePath)/sizeof(szFilePath[0]));
   QLCOMAPI.WCharToMByte(strUrl,szUrl,sizeof(szUrl)/sizeof(szUrl[0]));
#else
   strncpy_s(szRemoteFileName,(LPSTR)(LPCTSTR)EncodeParam(strServerFileName), sizeof(szRemoteFileName) - 1);
   strncpy_s(szFilePath,(LPSTR)(LPCTSTR)strLocalPath, sizeof(szFilePath) - 1);
   strncpy_s(szUrl,(LPSTR)(LPCTSTR)strUrl, sizeof(szUrl) - 1);
#endif // _DEBUG

   CURL *curl;
   CURLcode res;
   struct stat file_info;

   FILE * fp = fopen(szFilePath, "rb"); 
   if(!fp) {
      return HTTP_RET_CODE_FAIL;
   }

   if(fstat(fileno(fp), &file_info) != 0) {
      return HTTP_RET_CODE_FAIL;
   }
   fclose(fp);
   curl = curl_easy_init();
   if (NULL == curl)
   {
      return HTTP_RET_CODE_FAIL;
   }
   std::string sResult;

   struct curl_httppost* post = NULL;
   struct curl_httppost* last = NULL;

   curl_easy_setopt(curl, CURLOPT_URL, szUrl);
   auto plist = AppendUserInfo(NULL);
   curl_easy_setopt(curl,CURLOPT_HTTPHEADER,plist);

   curl_formadd(&post, &last, CURLFORM_COPYNAME, COMMAND_UPLOAD_FILE, CURLFORM_FILE, szFilePath, CURLFORM_END);
   curl_formadd(&post, &last, CURLFORM_COPYNAME, COMMAND_UPLOAD_REMOTEFILENAME, CURLFORM_COPYCONTENTS, szRemoteFileName, CURLFORM_END);

   curl_easy_setopt(curl, CURLOPT_HTTPPOST, post);
   curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE, (curl_off_t)file_info.st_size); // upload file size--- Content-Length: size
   curl_easy_setopt(curl, CURLOPT_MAX_SEND_SPEED_LARGE, 20*1000); // speed limit

   curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, OnWriteStringData);
   curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&sResult);

   // progress callback 
   curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L); 
   curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, progress_callback);
   curl_easy_setopt(curl, CURLOPT_XFERINFODATA, m_hProcess);

   res = curl_easy_perform(curl);
   BOOL bIsLoginError = IsLoginError(curl);
   curl_easy_cleanup(curl); 

   if (res == CURLE_OK && !bIsLoginError)
   {
      CString strResult = theApp.UTF8_TO_UNICODE(sResult);
      if (strResult.IsEmpty())
      {
         strResult = _T("{}");
      }
      //登录成功的话 就解析反馈的json
      char sRet[3000];
      memset(sRet,0,sizeof(sRet)/sizeof(sRet[0]));
#ifdef _UNICODE
      QLCOMAPI.WCharToMByte(strResult,sRet,sizeof(sRet)/sizeof(sRet[0]));
#else
      strncpy_s(sRet,(LPSTR)(LPCTSTR)strResult, sizeof(sRet) - 1);
#endif // _DEBUG
      //解析返回值
      rapidjson::Document document;
      document.Parse(sRet);

      if (document.HasMember("state"))
      {
         if(document["state"].IsInt())
         {
            if(1 == document["state"].GetInt())
            {//返回操作成功的值

            }
            else
            {
               return HTTP_RET_CODE_FAIL;
            }
         }
      }
   }
   else
   {
      //登录失败
      return HTTP_RET_CODE_LOGIN_ERROR;
   }

   if (NULL != m_hProcess)
   {
      ::PostMessage(m_hProcess,WM_QL_FTP_PROGRESS,100,1);
   }

   return HTTP_RET_CODE_SUCCESS;
}

int QL_HttpClient::Http_Move(const CString & strOrgPath, const CString & strDstPath)
{
   vector<pair<CString,CString>> vecParams;
   vecParams.push_back(make_pair(strOrgPath,strDstPath));
   return Http_Commond(COMMAND_JSON_MOVE,vecParams);
}

int QL_HttpClient::Http_Copy(const CString & strOrgPath, const CString & strDstPath)
{
   vector<pair<CString,CString>> vecParams;
   vecParams.push_back(make_pair(strOrgPath,strDstPath));
   return Http_Commond(COMMAND_JSON_COPY,vecParams);
}

BOOL QL_HttpClient::IsLoginError(CURL * curl)
{
   long http_code = 0;
   curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &http_code);
   return http_code == LOGIN_ERROR_STATUS_CODE;
}

int QL_HttpClient::Http_Commond(const char * szCommand,vector<pair<CString,CString>> vec_CommandParams)
{
   if (0 == static_cast<int>(vec_CommandParams.size()))
   {//如果参数为0 则直接返回成功
      return HTTP_RET_CODE_SUCCESS;
   }
   //准备URL
   CString strUrl = m_strIP;
   strUrl += URL_KEY_COMMAND;
   char szUrl[MAX_PATH];
   memset(szUrl,0,sizeof(szUrl));
#ifdef _UNICODE
   QLCOMAPI.WCharToMByte(strUrl,szUrl,sizeof(szUrl)/sizeof(szUrl[0]));
#else
   strncpy_s(szUrl,(LPSTR)(LPCTSTR)strUrl, sizeof(szUrl) - 1);
#endif // _UNICODE

   //准备JSON

   rapidjson::Document document;
   document.SetObject();
   rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
   document.AddMember(rapidjson::Value(COMMAND_JSON_COMMAND, allocator).Move(), // copy string
      rapidjson::Value(szCommand,allocator).Move(),
      allocator
      );

   char szSrcFile[MAX_PATH],szDestPath[MAX_PATH];
   rapidjson::Value array_objects(rapidjson::kArrayType);

   for (auto it = vec_CommandParams.begin();it != vec_CommandParams.end();++it)
   {
      CString strSrcParam = EncodeParam(it->first);
      CString strDestParam = EncodeParam(it->second);

      rapidjson::Value object(rapidjson::kObjectType);

      memset(szSrcFile,0,sizeof(szSrcFile));
      memset(szDestPath,0,sizeof(szDestPath));

#ifdef _UNICODE
      QLCOMAPI.WCharToMByte(strSrcParam,szSrcFile,sizeof(szSrcFile)/sizeof(szSrcFile[0]));
      QLCOMAPI.WCharToMByte(strDestParam,szDestPath,sizeof(szDestPath)/sizeof(szDestPath[0]));
#else
      strncpy_s(szSrcFile,(LPSTR)(LPCTSTR)strSrcParam, sizeof(szSrcFile) - 1);
      strncpy_s(szDestPath,(LPSTR)(LPCTSTR)strDestParam, sizeof(szDestPath) - 1);
#endif // _DEBUG

      /*Value s;
      s.SetString(szSrcFile);
      //s = szSrcFile;
      object.AddMember(StringRef("srcFile"), StringRef(s), document.GetAllocator());
      */
      // ref方法并不会拷贝字符串  因此使用临时value 或者可以显式指定value
      // 官方文档 http://rapidjson.org/zh-cn/md_doc_tutorial_8zh-cn.html#CreateString
      object.AddMember(rapidjson::Value(COMMAND_JSON_SRCFILE, allocator).Move(), // copy string
         rapidjson::Value(szSrcFile,allocator).Move(),                // copy string
         allocator);

      object.AddMember(rapidjson::Value(COMMAND_JSON_DESFILE, allocator).Move(),
         rapidjson::Value(szDestPath,allocator).Move(),
         allocator);

      array_objects.PushBack(object, allocator);
   }
   document.AddMember(rapidjson::StringRef(COMMAND_JSON_PARAMS), array_objects, allocator);

   //转string
   rapidjson::StringBuffer buffer;
   rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
   document.Accept(writer);
   auto out = buffer.GetString();

   //http请求
   CURL *curl;
   CURLcode res;
   curl = curl_easy_init();

   if (NULL == curl)
   {
      return HTTP_RET_CODE_FAIL;
   }

   std::string sResult;
   
   curl_easy_setopt(curl, CURLOPT_URL, szUrl);

   curl_slist *plist = curl_slist_append(NULL, 
      "Content-Type: application/json");

   //追加用户信息
   plist = AppendUserInfo(plist);

   curl_easy_setopt(curl,CURLOPT_HTTPHEADER,plist);

   curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
   curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,  OnWriteStringData);
   curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&sResult);

   curl_easy_setopt(curl, CURLOPT_HTTPPOST, 1);
   curl_easy_setopt(curl, CURLOPT_POSTFIELDS,out);


   /**
   * 当多个线程都使用超时处理的时候，同时主线程中有sleep或是wait等操作。
   * 如果不设置这个选项，libcurl将会发信号打断这个wait从而导致程序退出。
   */
   curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
   curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 50);
   curl_easy_setopt(curl, CURLOPT_TIMEOUT, 50);
   res = curl_easy_perform(curl);
   BOOL bIsLoginError = IsLoginError(curl);
   curl_easy_cleanup(curl);

   if (res == CURLE_OK && !bIsLoginError)
   {
      CString strResult = theApp.UTF8_TO_UNICODE(sResult);
      if (strResult.IsEmpty())
      {
         strResult = _T("{}");
      }
      //登录成功的话 就解析反馈的json
      char sRet[3000];
      memset(sRet,0,sizeof(sRet)/sizeof(sRet[0]));
#ifdef _UNICODE
      QLCOMAPI.WCharToMByte(strResult,sRet,sizeof(sRet)/sizeof(sRet[0]));
#else
      strncpy_s(sRet,(LPSTR)(LPCTSTR)strResult, sizeof(sRet) - 1);
#endif // _DEBUG
      //解析返回值
      rapidjson::Document documentParse;
      documentParse.Parse(sRet);

      if (documentParse.HasMember("state"))
      {
         if(documentParse["state"].IsInt())
         {
            if(1 == documentParse["state"].GetInt())
            {//返回操作成功的值

            }
            else
            {
               if (documentParse.HasMember("message") && documentParse["message"].IsString())
               {
                  CString strMessage(documentParse["message"].GetString());
                  CString strNotExists = _T("不存在");

                  if (strMessage.Right(strNotExists.GetLength()) == strNotExists)
                  {
                     return HTTP_RET_CODE_FILE_NOTEXISTS;
                  }
               }

               return HTTP_RET_CODE_FAIL;
            }
         }
      }
   }
   else
   {
      //登录失败
      return HTTP_RET_CODE_LOGIN_ERROR;
   }

   return HTTP_RET_CODE_SUCCESS;
}

curl_slist * QL_HttpClient::AppendUserInfo(curl_slist * plist)
{
   CString strUserName ;
   strUserName.Format(_T("%s:%s"),HEAD_USER,m_strUserName);
   char szUserName[MAX_PATH] = {0};
#ifdef _UNICODE
   QLCOMAPI.WCharToMByte(strUserName,szUserName,sizeof(szUserName)/sizeof(szUserName[0]));
#else
   strncpy_s(szUserName,(LPSTR)(LPCTSTR)strUserName, sizeof(szUserName) - 1);
#endif // _DEBUG

   plist = curl_slist_append(plist, szUserName);

   //qildocqildoc
   CString strEncrypted,strEncrytedKey;
   GetEntryString(m_strUserPassword,strEncrypted,strEncrytedKey);

   CString strToken,strRandKey;
   strToken.Format(_T("%s:%s"),HEAD_TOKEN,strEncrypted);
   strRandKey.Format(_T("%s:%s"),HEAD_RANDKEY,strEncrytedKey);

   char szEncrypted[MAX_PATH] = {0},szEncryptedKey[MAX_PATH] = {0};

#ifdef _UNICODE
   QLCOMAPI.WCharToMByte(strToken,szEncrypted,sizeof(szEncrypted)/sizeof(szEncrypted[0]));
   QLCOMAPI.WCharToMByte(strRandKey,szEncryptedKey,sizeof(szEncryptedKey)/sizeof(szEncryptedKey[0]));
#else
   strncpy_s(szEncrypted,(LPSTR)(LPCTSTR)strToken, sizeof(szEncrypted) - 1);
   strncpy_s(szEncryptedKey,(LPSTR)(LPCTSTR)strRandKey, sizeof(szEncryptedKey) - 1);
#endif // _DEBUG

   plist = curl_slist_append(plist, szEncrypted);
   plist = curl_slist_append(plist, szEncryptedKey);

   return plist;
}

void QL_HttpClient::GetEntryString(const CString & strUnEncrypted , CString & strEncodeString, CString & strEncryptKey)
{
   char szUnEncrypted[50] = {0};
   char szIV[50] = {0};

#ifdef _UNICODE
   QLCOMAPI.WCharToMByte(strUnEncrypted,szUnEncrypted,sizeof(szUnEncrypted)/sizeof(szUnEncrypted[0]));
#else
   strncpy_s(szUnEncrypted,(LPSTR)(LPCTSTR)strUnEncrypted, sizeof(szUnEncrypted) - 1);
#endif

   const char CCH[] = "0123456789ABCDEFGHIGKLMNOPQRSTUVWXYZ";
   int nRandCount = 16;
   for (int i = 0; i < nRandCount; ++i)
   {
      srand((unsigned)time(NULL)+i);
      int x = rand()%36;
      strEncryptKey.AppendChar(CCH[x]);
   }

#ifdef _UNICODE
   QLCOMAPI.WCharToMByte(strEncryptKey,szIV,sizeof(szIV)/sizeof(szIV[0]));
#else
   strncpy_s(szIV,(LPSTR)(LPCTSTR)strEncryptKey, sizeof(szIV) - 1);
#endif
   Init(AES_KEY, szIV);

   std::string en = Encrypt(szUnEncrypted);
   strEncodeString = CString(en.c_str());
}

bool QL_HttpClient::Init(const std::string& key, const std::string& iv)
{
   if (key.size() != CryptoPP::AES::DEFAULT_KEYLENGTH) {
      return false;
   }
   if (iv.size() != CryptoPP::AES::BLOCKSIZE) {
      return false;
   }

   for(int i = 0; i < CryptoPP::AES::DEFAULT_KEYLENGTH; i++) {
      s_key[i] = key[i];
   }
   for(int i = 0; i < CryptoPP::AES::BLOCKSIZE; i++) {
      s_iv[i] = iv[i];
   }

   return true;
}

std::string QL_HttpClient::Encrypt(const std::string& plainText)
{
   std::string cipherTextHex;
   try {
      std::string cipherText;
      CryptoPP::AES::Encryption aesEncryption(s_key, CryptoPP::AES::DEFAULT_KEYLENGTH);
      CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption( aesEncryption, s_iv);
      //CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink( cipherText ), CryptoPP::StreamTransformationFilter::NO_PADDING);
      CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink( cipherText ));
      stfEncryptor.Put( reinterpret_cast<const unsigned char*>( plainText.c_str() ), plainText.length() );
      stfEncryptor.MessageEnd();

      for( unsigned int i = 0; i < cipherText.size(); i++ )
      {
         char ch[3] = {0};
         sprintf(ch, "%02X",  static_cast<byte>(cipherText[i]));
         cipherTextHex += ch;
      }
   } catch (const std::exception &e) {
      cipherTextHex = "";
   }

   return cipherTextHex;
}

std::string QL_HttpClient::Decrypt(const std::string& cipherTextHex)
{
   std::string cipherText;
   std::string decryptedText;

   unsigned int i = 0;
   while(true)
   {
      char c;
      int x;
      std::stringstream ss;
      ss<<std::ios::hex<<cipherTextHex.substr(i, 2).c_str();
      ss>>x;
      c = (char)x;
      cipherText += c;
      if(i >= cipherTextHex.length() - 2)break;
      i += 2;
   }

   try {
      CryptoPP::AES::Decryption aesDecryption(s_key, CryptoPP::AES::DEFAULT_KEYLENGTH);
      CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption( aesDecryption, s_iv );
      //CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink( decryptedText ),CryptoPP::StreamTransformationFilter::NO_PADDING);
      CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink( decryptedText ));
      stfDecryptor.Put( reinterpret_cast<const unsigned char*>( cipherText.c_str() ), cipherText.size());

      stfDecryptor.MessageEnd();
   } catch (const std::exception &e) {
      decryptedText = "";
   }

   return decryptedText;
}

CString QL_HttpClient::EncodeParam(const CString & strParam)
{

   wchar_t szParamEncode[ 1024 ] = {0};
   DWORD dwLength = 1024 ; 
   CStringW  strWParam(strParam);
   AtlEscapeUrl( strWParam , szParamEncode , &dwLength , 1024 ,ATL_URL_ESCAPE   ) ;
   return CString(szParamEncode);
}

