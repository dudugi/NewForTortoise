#include "StdAfx.h"
#include "ThreadFileTrans.h"

#include "Zip/zip.h"
#include "Zip/unzip.h"
#include "DBImage.h"
#include "CDBPtLogInfo_new.h"
#include "QL_HttpClient.h"
#include "MD5/md5.h"
/*
SO_REUSERADDR 允许重用本地地址和端口 int 
导致大量文件上传和下载 持续的占用某个端口，其它的客户端连接服务端时也可能使用该端口
导致WSAGetLastError()=10054，故实现重新连接
*/
#define NUMS_RECONN_FTP		3			//重新连接FTP服务端次数为： NUMS_RECONN_FTP-1
#define TIME_SLEEP_RECONN	3000		//3s

/*
#ifdef _UNICODE
inline CString GetSqlConnectStr(const char * szDBIP,const char * szDB,const char *szDBID,const char * szDBPwd);
#else
inline CString GetSqlConnectStr(CString strDBIP,CString strDB,CString strDBID,CString strDBPwd);
#endif*/

#ifdef _UNICODE
CString GetSqlConnectStr( const char * szDBIP,const char * szDB,const char *szDBID,const char * szDBPwd )
{

   LOGBUG(_T("GetSqlConnectStr "));


   CString strProvide = _T("SQL Server");//SQL2008
   CString strRet = _T("");
   USES_CONVERSION;
   strRet.Format(_T("Driver={%s};Server=%s;Database=%s;UID=%s;PWD=%s")
      ,strProvide
      ,A2T(szDBIP)
      ,A2T(szDB)
      ,A2T(szDBID)
      ,A2T(szDBPwd)
      );

   LOGBUG(_T("GetSqlConnectStr_end "));

   return strRet;
}
#else
CString GetSqlConnectStr( CString strDBIP,CString strDB,CString strDBID,CString strDBPwd )
{

   LOGBUG(_T("GetSqlConnectStr "));


   CString strProvide = _T("SQL Server");//SQL2008
   CString strRet = _T("");
   strRet.Format(_T("Driver={%s};Server=%s;Database=%s;UID=%s;PWD=%s")
      ,strProvide
      ,strDBIP
      ,strDB
      ,strDBID
      ,strDBPwd
      );

   LOGBUG(_T("GetSqlConnectStr_end "));


   return strRet;
}
#endif

int TransferEx_ZipFile(CString &strSrc)
{
   CString strTarget = strSrc + STR_ZIP_CACH_QLTRANSFEREX;
   strSrc.Replace('/','\\');
   CString strName=strSrc.Right(strSrc.GetLength()-strSrc.ReverseFind('\\')-1);
   HZIP hz;
   hz = CreateZip(strTarget,0);
   if (hz==0)
   {
      return -1;
   }

   ZipAdd(hz,strName, strSrc);

   CloseZip(hz);

   strSrc = strTarget;
   return 1;
}

int TransferEx_UnzipFile(CString &strSrc,BOOL bDel /* = FALSE */)
{
   HZIP hz; 
   hz = OpenZip(strSrc,0);
   if (hz==0)
   {
      CloseZip(hz);
      if (bDel)
      {	
         //2018/01/12 zhangt 解压失败就直接还原文件名称
         CString strNewTmp = strSrc;
         strNewTmp.Replace(STR_UNZIP_CACH_QLTRANSFEREX,_T(""));
         MoveFileEx(strSrc,strNewTmp,MOVEFILE_REPLACE_EXISTING|MOVEFILE_COPY_ALLOWED);
         //DeleteFile(strSrc);
         //2018/01/12_end
      }
      return -1;
   }
   strSrc.Replace('/','\\');
   CString sPath=strSrc.Left(strSrc.ReverseFind('\\')+1);

   SetUnzipBaseDir(hz,sPath);
   ZIPENTRY ze; 
   GetZipItem(hz,-1,&ze); 
   int numitems=ze.index;
   for (int zi=0; zi<numitems; zi++)
   { 
      GetZipItem(hz,zi,&ze);
      UnzipItem(hz,zi,ze.name);
   }
   CloseZip(hz);

   if (bDel)
   {
      DeleteFile(strSrc);
   }
   return 1;
}

DWORD WINAPI ThreadUpLoad( LPVOID lpParam )
{
   //xq define 20170823 ==============================================       
   TIME_LIMIT

   if( cTime < sTime )
   {
      return 0;
   }

   if( cTime > eTime )
   {
      return 0;
   }
   //xq end  20170823 ===================================================

   //WaitForSingleObject(g_FileTransferEx_hMutex, INFINITE);
   TransferMsg *pUpLoadMsg = (TransferMsg *)lpParam;
   HWND hWnd = pUpLoadMsg->hWnd;
   int nFlag = pUpLoadMsg->nSpecFlag;
   BOOL bDelSrc = pUpLoadMsg->bDelSrc;
   int nLoginType = pUpLoadMsg->nLoginType;//En_Login_Null
   BOOL bZip = pUpLoadMsg->bZip;
   BOOL bHttpMode = pUpLoadMsg->bUseHttp;

   int nTransFileNum = pUpLoadMsg->nTransFileNum;
   TransferFileMsg * pTransFileMsg = pUpLoadMsg->pTransFileMsg;

   CString strFileType = _T("");//标记上传类型  记录日志用

   LpMsg_QLtransEx *pLpMsg = new LpMsg_QLtransEx;
   if (NULL != pLpMsg)
   {
      ZeroMemory(pLpMsg,sizeof(LpMsg_QLtransEx));
   }

   int nFileIndex = 0;

   if (!bHttpMode)//FTPMode
   {
#ifdef _UNICODE
      char szLocalPath[MAX_PATH] = {0};
      char szFarPath[MAX_PATH] = {0};
      char szIp[50] = {0};
      char szName[50] = {0};
      char szPwd[50] = {0};

      char szDBIP[50] = {0};
      char szDB[50] = {0};
      char szDBID[50] = {0};
      char szDBPWD[50] = {0};
      char szUserID[50] = {0};
      char szFileName[MAX_PATH] = {0};

      strcpy_s(szIp,pUpLoadMsg->strIP);
      strcpy_s(szName,pUpLoadMsg->strName);
      strcpy_s(szPwd,pUpLoadMsg->strPwd);

      strcpy_s(szDBIP,pUpLoadMsg->strDBIP);
      strcpy_s(szDB,pUpLoadMsg->strDB);
      strcpy_s(szDBID,pUpLoadMsg->strDBID);
      strcpy_s(szDBPWD,pUpLoadMsg->strDBPWD);
      strcpy_s(szUserID,pUpLoadMsg->strUserID);
#else
      CString strLocalPath = _T("");
      CString strFarPath = _T("");
      CString strFileName = _T("");
      CString strIP = pUpLoadMsg->strIP;
      CString strName = pUpLoadMsg->strName;
      CString strPwd = pUpLoadMsg->strPwd;

      CString strDBIP = pUpLoadMsg->strDBIP;
      CString strDB = pUpLoadMsg->strDB;
      CString strDBID = pUpLoadMsg->strDBID;
      CString strDBPWD = pUpLoadMsg->strDBPWD;
      CString strUserId = pUpLoadMsg->strUserID;
#endif // _UNICODE

      int nNumsReConn = 0;

loop_ThreadUpLoad:

      zt_FtpComm objFtpComm;
      int nOpenFtp = 0;
#ifdef _UNICODE
      nOpenFtp = objFtpComm.Ftp_OpenEx(szIp,szName, szPwd);
#else
      nOpenFtp = objFtpComm.Ftp_OpenEx(strIP,strName, strPwd);
#endif // _UNICODE

      if (1 == nOpenFtp)
      {
         objFtpComm.Ftp_ProcessMsg(hWnd);
         objFtpComm.Ftp_MkDir(pUpLoadMsg->strFarPath);

         for (;nFileIndex < nTransFileNum;nFileIndex++)
         {
            if(NULL != hWnd)
            {
               //发送上传文件名给句柄
               if (NULL != pLpMsg)
               {
                  pLpMsg->nFlag = nFlag;
                  pLpMsg->nAction = FTP_ACTION_START;
                  pLpMsg->nFileSize_Upload = 0;
               }
               SendMessage(hWnd,WM_QL_FTP_UPLOAD,(WPARAM)pTransFileMsg[nFileIndex].strLocalPath,(LPARAM)pLpMsg);
            }

            CString strFileNameold = PathFindFileName(CString(pTransFileMsg[nFileIndex].strLocalPath));

#ifdef _UNICODE
            strcpy_s(szFarPath,pTransFileMsg[nFileIndex].strFarPath);
            strcpy_s(szLocalPath,pTransFileMsg[nFileIndex].strLocalPath);
            QLCOMAPI.WCharToMByte(strFileNameold,szFileName,sizeof(szFileName)/sizeof(szFileName[0]));
#else
            strLocalPath = pTransFileMsg[nFileIndex].strLocalPath;
            strFarPath = pTransFileMsg[nFileIndex].strFarPath;
            strFileName = strFileNameold;
#endif // _UNICODE

            //开启服务成功，执行上传动作
            CFileStatus FileStatus;
#ifdef  _UNICODE 
            USES_CONVERSION;
            if (CFile::GetStatus(A2T(szLocalPath),FileStatus) == TRUE)
            {
               if (FileStatus.m_size > 5)
               {
                  //1.压缩文件
                  CString strLocalZipFile = A2T(szLocalPath);
                  if (bZip)
                  {
                     TransferEx_ZipFile(strLocalZipFile);
                  }
                  //2.上传
                  char szLocalPathZip[MAX_PATH] = {0};
                  strcpy_s(szLocalPathZip,T2A(strLocalZipFile));
                  FILEUPLOADMSG msg;
                  msg.bSuccess = false;
                  if (1 == objFtpComm.Ftp_Upload(szLocalPathZip,szFarPath))
                  {
                     msg.bSuccess = true;
                     msg.nSize = FileStatus.m_size;
#else
            if(CFile::GetStatus(strLocalPath,FileStatus) == TRUE)
            {
               if (FileStatus.m_size > 5)
               {
                  if (bZip)
                  {
                     TransferEx_ZipFile(strLocalPath);
                  }
                  CString strLocalZipFile = strLocalPath;
                  FILEUPLOADMSG msg;
                  msg.bSuccess = false;
                  if(1 == objFtpComm.Ftp_Upload(strLocalPath,strFarPath))
                  {
                     msg.bSuccess = true;
                     msg.nSize = FileStatus.m_size;
#endif
                     if(NULL != hWnd)
                     {
                        if (CFile::GetStatus(strLocalZipFile,FileStatus) == TRUE)
                        {
                           if (NULL != pLpMsg)
                           {
                              pLpMsg->nFileSize_Upload = FileStatus.m_size;
                              msg.nSize = FileStatus.m_size;
                           }
                        }

                        //发送文件名给句柄
                        if (NULL != pLpMsg)
                        {
                           pLpMsg->nFlag = nFlag;
                           pLpMsg->nAction = FTP_ACTION_SUC;
                        }
                     }
                     if(pUpLoadMsg->funcUpload)
                     {
#ifdef _UNICODE
                        strcpy_s(msg.szFileName,szFileName);
                        strcpy_s(msg.szLocalPath,szLocalPathZip);
                        strcpy_s(msg.szMD5,MD5(ifstream(szLocalPathZip, ios::binary)).toString().c_str());
#else
                        strcpy_s(msg.szFileName,strFileName);
                        strcpy_s(msg.szLocalPath,strLocalPath);
                        strcpy_s(msg.szMD5,MD5(ifstream(strLocalPath, ios::binary)).toString().c_str());
                        
#endif
                        strcpy_s(msg.szRelativePath,pTransFileMsg[nFileIndex].strFarPath);
                     }
                  }
                  else
                  {
                     nNumsReConn++;
                     if (nNumsReConn<NUMS_RECONN_FTP)
                     {
                        objFtpComm.Ftp_Close();
                        Sleep(TIME_SLEEP_RECONN);
                        goto loop_ThreadUpLoad;
                     }

                     if(NULL != hWnd)
                     {
                        //发送上传文件名给句柄
                        if (NULL != pLpMsg)
                        {
                           pLpMsg->nFlag = nFlag;
                           pLpMsg->nAction = FTP_ACTION_FAIL;
                        }
                     }
                  }

                  if(pUpLoadMsg->funcUpload)
                  {
                     pUpLoadMsg->funcUpload(&msg,pUpLoadMsg->pUserCallBackData,(nFileIndex+1) == nTransFileNum);
                  }

#ifdef _UNICODE
                  if (bDelSrc)
                  {
                     DeleteFile(A2T(szLocalPath));
                  }
#else
                  if (bDelSrc)
                  {
                     DeleteFile(pTransFileMsg[nFileIndex].strLocalPath);
                  }
#endif // _UNICODE

                  if (bZip)
                  {//如果压缩过则删除对应的压缩文件 否则不删除  2018-03-19 wangzl
                     //3.删除本地压缩文件
                     DeleteFile(strLocalZipFile);
                  }

                  SendMessage(hWnd,WM_QL_FTP_UPLOAD,(WPARAM)pTransFileMsg[nFileIndex].strLocalPath,(LPARAM)pLpMsg);
               }
            }
         }
      }
      else
      {
         if(NULL != hWnd)
         {
            int nFileIndex = 0;
            for (nFileIndex = 0;nFileIndex < nTransFileNum;nFileIndex++)
            {

               //发送上传文件名给句柄
               if (NULL != pLpMsg)
               {
                  pLpMsg->nFlag = nFlag;
                  if (2 == nOpenFtp) pLpMsg->nAction = FTP_ACTION_DISCONNECTED;
                  else pLpMsg->nAction = FTP_ACTION_OPENFAIL;
               }
               SendMessage(hWnd,WM_QL_FTP_UPLOAD,(WPARAM)pTransFileMsg[nFileIndex].strLocalPath,(LPARAM)pLpMsg);
            }
         }
      }

      if (1 == nOpenFtp) objFtpComm.Ftp_Close();//关闭

   }
   else//HTTPmode
   {
      CString strIP(pUpLoadMsg->strIP),strName(pUpLoadMsg->strName),strPwd(pUpLoadMsg->strPwd);
      QL_HttpClient objHttpClient(strIP,strName,strPwd);
      objHttpClient.Http_ProcessMsg(hWnd);
     
      for (;nFileIndex < nTransFileNum;nFileIndex++)
      {
         CString strLocalPath(pTransFileMsg[nFileIndex].strLocalPath);
         CString strFarPath(pTransFileMsg[nFileIndex].strFarPath);
         CString strFileName = PathFindFileName(strLocalPath);

         if(NULL != hWnd)
         {
            //发送上传文件名给句柄
            if (NULL != pLpMsg)
            {
               pLpMsg->nFlag = nFlag;
               pLpMsg->nAction = FTP_ACTION_START;
               pLpMsg->nFileSize_Upload = 0;
            }
            SendMessage(hWnd,WM_QL_FTP_UPLOAD,(WPARAM)pTransFileMsg[nFileIndex].strLocalPath,(LPARAM)pLpMsg);
         }
         CFileStatus FileStatus;
         if (CFile::GetStatus(strLocalPath,FileStatus) == TRUE)
         {
            //文件过小不上传
            if (FileStatus.m_size > 5)
            {
               //1.压缩文件
               CString strLocalZipFile = strLocalPath;
               if (bZip)
               {
                  TransferEx_ZipFile(strLocalZipFile);
               }

               CString strFarFileName = PathFindFileName(strFarPath);

               strFarPath = strFarPath.Left(strFarPath.GetLength() - strFarFileName.GetLength());
               strFarPath.TrimRight('\\');
               FILEUPLOADMSG msg;
               msg.bSuccess = false;
               int nRet = objHttpClient.Http_Upload(strLocalZipFile,strFarPath,strFarFileName);
               if (nRet == HTTP_RET_CODE_SUCCESS)
               {
                  msg.bSuccess = true;
                  msg.nSize = FileStatus.m_size;
                  if(NULL != hWnd)
                  {
                     if (CFile::GetStatus(strLocalZipFile,FileStatus) == TRUE)
                     {
                        if (NULL != pLpMsg)
                        {
                           msg.nSize = FileStatus.m_size;
                           pLpMsg->nFileSize_Upload = FileStatus.m_size;
                        }
                     }

                     //发送文件名给句柄
                     if (NULL != pLpMsg)
                     {
                        pLpMsg->nFlag = nFlag;
                        pLpMsg->nAction = FTP_ACTION_SUC;
                     }
                  }
                  if(pUpLoadMsg->funcUpload)
                  {
#ifdef _UNICODE
                     QLCOMAPI.WCharToMByte(strFileName,msg.szFileName,sizeof(msg.szFileName)/sizeof(msg.szFileName[0]));

                     QLCOMAPI.WCharToMByte(strLocalPath,msg.szLocalPath,sizeof(msg.szLocalPath)/sizeof(msg.szLocalPath[0]));

                     strcpy_s(msg.szMD5,MD5(ifstream(strLocalPath, ios::binary)).toString().c_str());
#else
                     strncpy_s(msg.szFileName,(LPSTR)(LPCTSTR)strFileName, sizeof(msg.szFileName) - 1);
                     strcpy_s(msg.szLocalPath,strLocalPath);
                     strcpy_s(msg.szMD5,MD5(ifstream(strLocalPath, ios::binary)).toString().c_str());
#endif
                     strcpy_s(msg.szRelativePath,pTransFileMsg[nFileIndex].strFarPath);
                  }
               }
               else if (nRet == HTTP_RET_CODE_FAIL)
               {
                  if(NULL != hWnd)
                  {
                     //发送上传文件名给句柄
                     if (NULL != pLpMsg)
                     {
                        pLpMsg->nFlag = nFlag;
                        pLpMsg->nAction = FTP_ACTION_FAIL;
                     }
                  }
               }
               else if (nRet == HTTP_RET_CODE_LOGIN_ERROR)
               {
                  //发送上传文件名给句柄
                  if (NULL != pLpMsg)
                  {
                     pLpMsg->nFlag = nFlag;
                     pLpMsg->nAction = FTP_ACTION_DISCONNECTED;
                  }
               }
               if (pUpLoadMsg->funcUpload)
               {
                  pUpLoadMsg->funcUpload(&msg,pUpLoadMsg->pUserCallBackData,(nFileIndex+1) == nTransFileNum);
               }

               if (bDelSrc)
               {
                  DeleteFile(strLocalPath);
               }

               if (bZip)
               {//如果压缩过则删除对应的压缩文件 否则不删除  2018-03-19 wangzl
                  //3.删除本地压缩文件
                  DeleteFile(strLocalZipFile);
               }

               SendMessage(hWnd,WM_QL_FTP_UPLOAD,(WPARAM)pTransFileMsg[nFileIndex].strLocalPath,(LPARAM)pLpMsg);
            }
         }
      }
   }

   if (NULL != pTransFileMsg)
   {
      delete []pTransFileMsg;
      pTransFileMsg = NULL;
   }

   if (pUpLoadMsg != NULL)
   {
      delete pUpLoadMsg;
      pUpLoadMsg = NULL;
   }
   if (NULL != pLpMsg)
   {
      delete pLpMsg;
      pLpMsg = NULL;
   }

   if (_T("工艺文件") == strFileType)
   {   
      CADOConnEx ADOConn;
      ADOConn.SetConnecetSqlStr(CDBPtLogInfo_New::Instance()->m_strConnectSql);
      //ReleaseMutex(g_FileTransferEx_hMutex);
      CDBPtLogInfo_New::Instance()->InsertSQL_LogInfo(&ADOConn);
   }

   return 0;
}

DWORD WINAPI ThreadDownLoad( LPVOID lpParam )
{
   //xq define 20170823 ==============================================       
   TIME_LIMIT

   if( cTime < sTime )
   {
      return 0;
   }

   if( cTime > eTime )
   {
      return 0;
   }
   //xq end  20170823 ===================================================

   //WaitForSingleObject(g_FileTransferEx_hMutex, INFINITE);
   TransferMsg *pDownLoadMsg = (TransferMsg *)lpParam;
   HWND hWnd = pDownLoadMsg->hWnd;
   int nFlag = pDownLoadMsg->nSpecFlag;
   TransferFileMsg *pTransFileMsg = pDownLoadMsg->pTransFileMsg;
   int nTransFileNum = pDownLoadMsg->nTransFileNum;
   int nLoginType = pDownLoadMsg->nLoginType;
   CString strFileType = _T("");

   BOOL bDelZip = pDownLoadMsg->bDelZip;
   BOOL bUnZipFailRename = pDownLoadMsg->bUnZipFailRename;

   BOOL bHttpMode = pDownLoadMsg->bUseHttp;

   LpMsg_QLtransEx *pLpMsg = new LpMsg_QLtransEx;
   if (NULL != pLpMsg)
   {
      ZeroMemory(pLpMsg,sizeof(LpMsg_QLtransEx));
   }

   int nFileIndex = 0;

   if (!bHttpMode)//FTP模式
   {
#ifdef _UNICODE
      char szLocalPath[MAX_PATH] = {0};
      char szFarPath[MAX_PATH] = {0};
      char szIp[50] = {0};
      char szName[50] = {0};
      char szPwd[50] = {0};

      char szDBIP[50] = {0};
      char szDB[50] = {0};
      char szDBID[50] = {0};
      char szDBPWD[50] = {0};
      char szUserID[50] = {0};

      strcpy_s(szIp,pDownLoadMsg->strIP);
      strcpy_s(szName,pDownLoadMsg->strName);
      strcpy_s(szPwd,pDownLoadMsg->strPwd);
      // 	strcpy_s(szFarPath,pDownLoadMsg->strFarPath);
      // 	strcpy_s(szLocalPath,pDownLoadMsg->strLocalPath);

      strcpy_s(szDBIP,pDownLoadMsg->strDBIP);
      strcpy_s(szDB,pDownLoadMsg->strDB);
      strcpy_s(szDBID,pDownLoadMsg->strDBID);
      strcpy_s(szDBPWD,pDownLoadMsg->strDBPWD);
      strcpy_s(szUserID,pDownLoadMsg->strUserID);
#else
      CString strLocalPath = _T("");
      CString strFarPath = _T("");
      CString strIP = pDownLoadMsg->strIP;
      CString strName = pDownLoadMsg->strName;
      CString strPwd = pDownLoadMsg->strPwd;

      CString strDBIP = pDownLoadMsg->strDBIP;
      CString strDB = pDownLoadMsg->strDB;
      CString strDBID = pDownLoadMsg->strDBID;
      CString strDBPWD = pDownLoadMsg->strDBPWD;
      CString strUserId = pDownLoadMsg->strUserID;
#endif // _UNICODE

      int nNumsReConn = 0;

loop_ThreadDownLoad:

      zt_FtpComm objFtpComm;
      int nOpenFtp = 0;
#ifdef _UNICODE
      nOpenFtp = objFtpComm.Ftp_OpenEx(szIp,szName, szPwd);
#else
      nOpenFtp = objFtpComm.Ftp_OpenEx(strIP,strName, strPwd);
#endif // _UNICODE

      if (1 == nOpenFtp)
      {
         objFtpComm.Ftp_ProcessMsg(hWnd);
         for (;nFileIndex < nTransFileNum;nFileIndex++)
         {
            if (NULL != hWnd)
            {
               if (NULL != pLpMsg)
               {
                  pLpMsg->nFlag = nFlag;
                  pLpMsg->nAction = FTP_ACTION_START;
               }
               SendMessage(hWnd,WM_QL_FTP_DOWNLOAD,(WPARAM)pTransFileMsg[nFileIndex].strLocalPath,(LPARAM)pLpMsg);
            }

#ifdef _UNICODE
            strcpy_s(szFarPath,pTransFileMsg[nFileIndex].strFarPath);
            strcpy_s(szLocalPath,pTransFileMsg[nFileIndex].strLocalPath);
#else
            strLocalPath = pTransFileMsg[nFileIndex].strLocalPath;
            strFarPath = pTransFileMsg[nFileIndex].strFarPath;
#endif // _UNICODE

            //开启服务成功，执行动作

            //先询问是否需要下载 如果不需要下载 则直接发送通知可以句柄 下载成功
            if (pDownLoadMsg->funcBeforeDownload)
            {
               if (!pDownLoadMsg->funcBeforeDownload(pTransFileMsg[nFileIndex].strFarPath,pTransFileMsg[nFileIndex].strLocalPath,pDownLoadMsg->pUserCallBackData,(nFileIndex+1) == nTransFileNum))
               {
                  if (NULL != hWnd)
                  {
                     if (NULL != pLpMsg)
                     {
                        pLpMsg->nFlag = nFlag;
                        pLpMsg->nAction = FTP_ACTION_SUC;
                     }
                     SendMessage(hWnd,WM_QL_FTP_DOWNLOAD,(WPARAM)pTransFileMsg[nFileIndex].strLocalPath,(LPARAM)pLpMsg);
                  }
                  continue;
               }
            }

#ifdef  _UNICODE 
            //1.命名下载文件
            USES_CONVERSION;
            CString strUnzipPath = A2T(szLocalPath);
            strUnzipPath += STR_UNZIP_CACH_QLTRANSFEREX;

            char szUnzipPath[MAX_PATH] = {0};
            strcpy_s(szUnzipPath,T2A(strUnzipPath));

            //2.下载
            //3.解压缩并删除源文件
            int nDownRet = objFtpComm.Ftp_DownloadEx(szUnzipPath,szFarPath);
            //if(1 == objFtpComm.Ftp_Download(szUnzipPath,szFarPath))
            if(1 == nDownRet)
            {
               if(-1 == TransferEx_UnzipFile(strUnzipPath,bDelZip))
               {
                  if (bUnZipFailRename)
                  {
                     MoveFileEx(strUnzipPath,A2T(szLocalPath),MOVEFILE_REPLACE_EXISTING|MOVEFILE_COPY_ALLOWED);
                  }
               }
#else
            CString strUnzipPath = strLocalPath;
            strUnzipPath += STR_UNZIP_CACH_QLTRANSFEREX;
            int nDownRet = objFtpComm.Ftp_DownloadEx(strUnzipPath,strFarPath);
            //if(1 == objFtpComm.Ftp_Download(strUnzipPath,strFarPath))
            if(1 == nDownRet)
            {
               //TransferEx_UnzipFile(strUnzipPath,TRUE);
               if(-1 == TransferEx_UnzipFile(strUnzipPath,bDelZip))
               {
                  if (bUnZipFailRename)
                  {
                     MoveFileEx(strUnzipPath,strLocalPath,MOVEFILE_REPLACE_EXISTING|MOVEFILE_COPY_ALLOWED);
                  }
               }
#endif
               if (NULL != hWnd)
               {
                  if (NULL != pLpMsg)
                  {
                     pLpMsg->nFlag = nFlag;
                     pLpMsg->nAction = FTP_ACTION_SUC;
                  }
                  SendMessage(hWnd,WM_QL_FTP_DOWNLOAD,(WPARAM)pTransFileMsg[nFileIndex].strLocalPath,(LPARAM)pLpMsg);
               }
            }
            else
            {
               int nRetAction = FTP_ACTION_FAIL;
               if (2 == nDownRet)//文件不存在
               {
                  nNumsReConn = NUMS_RECONN_FTP;
                  nRetAction = FTP_ACTION_NOFILE;
               }
               else
               {
                  nNumsReConn++;
                  nRetAction = FTP_ACTION_FAIL;
               }
               if (nNumsReConn<NUMS_RECONN_FTP)
               {
                  objFtpComm.Ftp_Close();
                  Sleep(TIME_SLEEP_RECONN);
                  goto loop_ThreadDownLoad;
               }

               if (NULL != hWnd)
               {
                  if (NULL != pLpMsg)
                  {
                     pLpMsg->nFlag = nFlag;
                     pLpMsg->nAction = nRetAction;
                  }
                  SendMessage(hWnd,WM_QL_FTP_DOWNLOAD,(WPARAM)pTransFileMsg[nFileIndex].strLocalPath,(LPARAM)pLpMsg);
               }
            }
            if (PathFileExists(strUnzipPath))
            {
               DeleteFile(strUnzipPath);
            }
         }
      }
      else
      {
         if (NULL != hWnd)
         {
            int nFileIndex = 0;
            for (nFileIndex = 0;nFileIndex < nTransFileNum;nFileIndex++)
            {
               if (NULL != pLpMsg)
               {
                  pLpMsg->nFlag = nFlag;
                  if (2 == nOpenFtp) pLpMsg->nAction = FTP_ACTION_DISCONNECTED;
                  else pLpMsg->nAction = FTP_ACTION_OPENFAIL;
               }
               SendMessage(hWnd,WM_QL_FTP_DOWNLOAD,(WPARAM)pTransFileMsg[nFileIndex].strLocalPath,(LPARAM)pLpMsg);
            }
         }
      }

      if (1 == nOpenFtp) objFtpComm.Ftp_Close();//关闭
   }
   else//HTTP模式
   {
      CString strIP(pDownLoadMsg->strIP),strName(pDownLoadMsg->strName),strPwd(pDownLoadMsg->strPwd);
      QL_HttpClient objHttpClient(strIP,strName,strPwd);
      objHttpClient.Http_ProcessMsg(hWnd);

      for (;nFileIndex < nTransFileNum;nFileIndex++)
      {
         if (NULL != hWnd)
         {
            if (NULL != pLpMsg)
            {
               pLpMsg->nFlag = nFlag;
               pLpMsg->nAction = FTP_ACTION_START;
            }
            SendMessage(hWnd,WM_QL_FTP_DOWNLOAD,(WPARAM)pTransFileMsg[nFileIndex].strLocalPath,(LPARAM)pLpMsg);
         }

         //先询问是否需要下载 如果不需要下载 则直接发送通知可以句柄 下载成功
         if (pDownLoadMsg->funcBeforeDownload)
         {
            if (!pDownLoadMsg->funcBeforeDownload(pTransFileMsg[nFileIndex].strFarPath,pTransFileMsg[nFileIndex].strLocalPath,pDownLoadMsg->pUserCallBackData,(nFileIndex+1) == nTransFileNum))
            {
               if (NULL != hWnd)
               {
                  if (NULL != pLpMsg)
                  {
                     pLpMsg->nFlag = nFlag;
                     pLpMsg->nAction = FTP_ACTION_SUC;
                  }
                  SendMessage(hWnd,WM_QL_FTP_DOWNLOAD,(WPARAM)pTransFileMsg[nFileIndex].strLocalPath,(LPARAM)pLpMsg);
               }
               continue;
            }
         }

         CString strLocalPath(pTransFileMsg[nFileIndex].strLocalPath);
         CString strFarPath(pTransFileMsg[nFileIndex].strFarPath);

         //开启服务成功，执行动作
         CString strUnzipPath = strLocalPath;
         strUnzipPath += STR_UNZIP_CACH_QLTRANSFEREX;
         int nRet = objHttpClient.Http_Download(strUnzipPath,strFarPath);
         if (nRet == HTTP_RET_CODE_SUCCESS)
         {
            if(-1 == TransferEx_UnzipFile(strUnzipPath,bDelZip))
            {
               if (bUnZipFailRename)
               {
                  MoveFileEx(strUnzipPath,strLocalPath,MOVEFILE_REPLACE_EXISTING|MOVEFILE_COPY_ALLOWED);
               }
            }

            if (NULL != hWnd)
            {
               if (NULL != pLpMsg)
               {
                  pLpMsg->nFlag = nFlag;
                  pLpMsg->nAction = FTP_ACTION_SUC;
               }
               SendMessage(hWnd,WM_QL_FTP_DOWNLOAD,(WPARAM)pTransFileMsg[nFileIndex].strLocalPath,(LPARAM)pLpMsg);
            }
         }
         else if (nRet == HTTP_RET_CODE_FAIL)
         {
            if (NULL != hWnd)
            {
               if (NULL != pLpMsg)
               {
                  pLpMsg->nFlag = nFlag;
                  pLpMsg->nAction = FTP_ACTION_FAIL;
               }
               SendMessage(hWnd,WM_QL_FTP_DOWNLOAD,(WPARAM)pTransFileMsg[nFileIndex].strLocalPath,(LPARAM)pLpMsg);
            }
         }
         else if (nRet == HTTP_RET_CODE_FILE_NOTEXISTS)
         {
            if (NULL != hWnd)
            {
               if (NULL != pLpMsg)
               {
                  pLpMsg->nFlag = nFlag;
                  pLpMsg->nAction = FTP_ACTION_NOFILE;
               }
               SendMessage(hWnd,WM_QL_FTP_DOWNLOAD,(WPARAM)pTransFileMsg[nFileIndex].strLocalPath,(LPARAM)pLpMsg);
            }
         }
         else if (nRet == HTTP_RET_CODE_LOGIN_ERROR)
         {
            if (NULL != hWnd)
            {
               if (NULL != pLpMsg)
               {
                  pLpMsg->nFlag = nFlag;
                  pLpMsg->nAction = FTP_ACTION_DISCONNECTED;
               }
               SendMessage(hWnd,WM_QL_FTP_DOWNLOAD,(WPARAM)pTransFileMsg[nFileIndex].strLocalPath,(LPARAM)pLpMsg);
            }
         }

         if (PathFileExists(strUnzipPath))
         {
            DeleteFile(strUnzipPath);
         }
      }
   }

   if (NULL != pTransFileMsg)
   {
      delete []pTransFileMsg;
      pTransFileMsg = NULL;
   }

   if (pDownLoadMsg != NULL)
   {
      delete pDownLoadMsg;
      pDownLoadMsg = NULL;
   }
   if (NULL != pLpMsg)
   {
      delete pLpMsg;
      pLpMsg = NULL;
   }

   if (_T("工艺文件") == strFileType)
   {
      CADOConnEx ADOConn;
      ADOConn.SetConnecetSqlStr(CDBPtLogInfo_New::Instance()->m_strConnectSql);
      //ReleaseMutex(g_FileTransferEx_hMutex);
      CDBPtLogInfo_New::Instance()->InsertSQL_LogInfo(&ADOConn);   
   }
   return 0;
}

DWORD WINAPI ThreadDel( LPVOID lpParam )
{
   //WaitForSingleObject(g_FileTransferEx_hMutex, INFINITE);
   TransferMsg *pDelMsg = (TransferMsg *)lpParam;
   HWND hWnd = pDelMsg->hWnd;
   int nFlag = pDelMsg->nSpecFlag;

   int nTransFileNum = pDelMsg->nTransFileNum;
   TransferFileMsg * pTransFileMsg = pDelMsg->pTransFileMsg;
   int nLoginType = pDelMsg->nLoginType;
   BOOL bHttpMode = pDelMsg->bUseHttp;

   LpMsg_QLtransEx *pLpMsg = new LpMsg_QLtransEx;
   if (NULL != pLpMsg)
   {
      ZeroMemory(pLpMsg,sizeof(pLpMsg));
   }
   int nFileIndex = 0;

   if ( !bHttpMode )
   {
#ifdef _UNICODE
      char szLocalPath[MAX_PATH] = {0};
      char szFarPath[MAX_PATH] = {0};
      char szIp[50] = {0};
      char szName[50] = {0};
      char szPwd[50] = {0};
      strcpy_s(szIp,pDelMsg->strIP);
      strcpy_s(szName,pDelMsg->strName);
      strcpy_s(szPwd,pDelMsg->strPwd);
      /*strcpy_s(szFarPath,pDelMsg->pTransFileMsg->strFarPath);*/
#else
      CString strFarPath = _T("");
      CString strIP = pDelMsg->strIP;
      CString strName = pDelMsg->strName;
      CString strPwd = pDelMsg->strPwd;
#endif // _UNICODE

      int nNumsReConn = 0;

loop_ThreadDel:

      zt_FtpComm objFtpComm;
      int nOpenFtp = 0;
#ifdef _UNICODE
      nOpenFtp = objFtpComm.Ftp_OpenEx(szIp,szName, szPwd);
#else
      nOpenFtp = objFtpComm.Ftp_OpenEx(strIP,strName, strPwd);
#endif // _UNICODE

      if (1 == nOpenFtp)
      {
         objFtpComm.Ftp_ProcessMsg(hWnd);
         for (;nFileIndex < nTransFileNum;nFileIndex++)
         {
            if (NULL != hWnd)
            {
               if (NULL != pLpMsg)
               {
                  pLpMsg->nFlag = nFlag;
                  pLpMsg->nAction = FTP_ACTION_START;
               }
               SendMessage(hWnd,WM_QL_FTP_DEL,(WPARAM)pTransFileMsg[nFileIndex].strFarPath,(LPARAM)pLpMsg);
            }

#ifdef _UNICODE
            strcpy_s(szFarPath,pTransFileMsg[nFileIndex].strFarPath);
#else
            strFarPath = pTransFileMsg[nFileIndex].strFarPath;
#endif // _UNICODE


            //开启服务成功，执行动作
#ifdef  _UNICODE 
            if(1 == objFtpComm.Ftp_Delete(szFarPath))
            {
#else
            if(1 == objFtpComm.Ftp_Delete(strFarPath))
            {
#endif
               if (NULL != hWnd)
               {
                  if (NULL != pLpMsg)
                  {
                     pLpMsg->nFlag = nFlag;
                     pLpMsg->nAction = FTP_ACTION_SUC;
                  }
                  SendMessage(hWnd,WM_QL_FTP_DEL,(WPARAM)pTransFileMsg[nFileIndex].strFarPath,(LPARAM)pLpMsg);
               }
            }
            else
            {
               nNumsReConn++;
               if (nNumsReConn<NUMS_RECONN_FTP)
               {
                  objFtpComm.Ftp_Close();
                  Sleep(TIME_SLEEP_RECONN);
                  goto loop_ThreadDel;
               }			

               if (NULL != hWnd)
               {
                  if (NULL != pLpMsg)
                  {
                     pLpMsg->nFlag = nFlag;
                     pLpMsg->nAction = FTP_ACTION_FAIL;
                  }
                  SendMessage(hWnd,WM_QL_FTP_DEL,(WPARAM)pTransFileMsg[nFileIndex].strFarPath,(LPARAM)pLpMsg);
               }
            }
            if (pDelMsg->funcDelete)
            {
               pDelMsg->funcDelete(pLpMsg->nAction == FTP_ACTION_SUC,pTransFileMsg[nFileIndex].strFarPath,pDelMsg->pUserCallBackData,(nFileIndex+1) == nTransFileNum);
            }
         }
      }
      else
      {
         if (NULL != hWnd)
         {
            int nFileIndex = 0;
            for (nFileIndex = 0;nFileIndex < nTransFileNum;nFileIndex++)
            {
               if (NULL != pLpMsg)
               {
                  pLpMsg->nFlag = nFlag;
                  if (2 == nOpenFtp) pLpMsg->nAction = FTP_ACTION_DISCONNECTED;
                  else pLpMsg->nAction = FTP_ACTION_OPENFAIL;
               }
               SendMessage(hWnd,WM_QL_FTP_DEL,(WPARAM)pTransFileMsg[nFileIndex].strFarPath,(LPARAM)pLpMsg);
            }
         }
      }

      if (1 == nOpenFtp) objFtpComm.Ftp_Close();//关闭

   }
   else//HTTP
   {
      CString strIP(pDelMsg->strIP),strName(pDelMsg->strName),strPwd(pDelMsg->strPwd);
      QL_HttpClient objHttpClient(strIP,strName,strPwd);
      objHttpClient.Http_ProcessMsg(hWnd);

      for (;nFileIndex < nTransFileNum;nFileIndex++)
      {
         if (NULL != hWnd)
         {
            if (NULL != pLpMsg)
            {
               pLpMsg->nFlag = nFlag;
               pLpMsg->nAction = FTP_ACTION_START;
            }
            SendMessage(hWnd,WM_QL_FTP_DEL,(WPARAM)pTransFileMsg[nFileIndex].strFarPath,(LPARAM)pLpMsg);
         }

         CString strFarPath(pTransFileMsg[nFileIndex].strFarPath);
         int nRet = objHttpClient.Http_Delete(strFarPath);
         int nRetAction;
         if(nRet == HTTP_RET_CODE_SUCCESS)
         {
            nRetAction = FTP_ACTION_SUC;
         }
         else if (nRet == HTTP_RET_CODE_FAIL)
         {
            nRetAction = FTP_ACTION_FAIL;
         }
         else if (nRet == HTTP_RET_CODE_LOGIN_ERROR)
         {
            nRetAction = FTP_ACTION_DISCONNECTED;
         }

         if (NULL != hWnd)
         {
            if (NULL != pLpMsg)
            {
               pLpMsg->nFlag = nFlag;
               pLpMsg->nAction = nRetAction;
            }
            SendMessage(hWnd,WM_QL_FTP_DEL,(WPARAM)pTransFileMsg[nFileIndex].strFarPath,(LPARAM)pLpMsg);
         }


         if (pDelMsg->funcDelete)
         {
            pDelMsg->funcDelete(nRetAction == FTP_ACTION_SUC,pTransFileMsg[nFileIndex].strFarPath,pDelMsg->pUserCallBackData,(nFileIndex+1) == nTransFileNum);
         }
      }

   }

   if (NULL != pTransFileMsg)
   {
      delete []pTransFileMsg;
      pTransFileMsg = NULL;
   }

   if (pDelMsg != NULL)
   {
      delete pDelMsg;
      pDelMsg = NULL;
   }
   if (NULL != pLpMsg)
   {
      delete pLpMsg;
      pLpMsg = NULL;
   }
   //ReleaseMutex(g_FileTransferEx_hMutex);
   return 0;
}

DWORD WINAPI ThreadMkDir( LPVOID lpParam )
{
   //WaitForSingleObject(g_FileTransferEx_hMutex, INFINITE);
   TransferMsg *pMkDirMsg = (TransferMsg *)lpParam;
   HWND hWnd = pMkDirMsg->hWnd;
   int nFlag = pMkDirMsg->nSpecFlag;
   int nLoginType = pMkDirMsg->nLoginType;
   BOOL bHttpMode = pMkDirMsg->bUseHttp;

   LpMsg_QLtransEx *pLpMsg = new LpMsg_QLtransEx;
   if (NULL != pLpMsg)
   {
      ZeroMemory(pLpMsg,sizeof(pLpMsg));
   }

   if (NULL != hWnd)
   {
      if (NULL != pLpMsg)
      {
         pLpMsg->nFlag = nFlag;
         pLpMsg->nAction = FTP_ACTION_START;
      }
      SendMessage(hWnd,WM_QL_FTP_MKDIR,(WPARAM)pMkDirMsg->strOrderNo,(LPARAM)pLpMsg);
   }

   if (!bHttpMode)
   {
#ifdef _UNICODE
      char szOrderNo[50] = {0};

      char szIp[50] = {0};
      char szName[50] = {0};
      char szPwd[50] = {0};
      strcpy_s(szIp,pMkDirMsg->strIP);
      strcpy_s(szName,pMkDirMsg->strName);
      strcpy_s(szPwd,pMkDirMsg->strPwd);
      strcpy_s(szOrderNo,pMkDirMsg->strOrderNo);
#else
      CString strOrderNo = pMkDirMsg->strOrderNo;
      CString strIP = pMkDirMsg->strIP;
      CString strName = pMkDirMsg->strName;
      CString strPwd = pMkDirMsg->strPwd;
#endif // _UNICODE

      int nNumsReConn = 0;
loop_ThreadMkDir:

      zt_FtpComm objFtpComm;
      int nOpenFtp = 0;
#ifdef _UNICODE
      nOpenFtp = objFtpComm.Ftp_OpenEx(szIp,szName, szPwd);
#else
      nOpenFtp = objFtpComm.Ftp_OpenEx(strIP,strName, strPwd);
#endif // _UNICODE

      BOOL bMkSuc = FALSE;
      if (1 == nOpenFtp)
      {
         objFtpComm.Ftp_ProcessMsg(hWnd);
         //开启服务成功，执行动作
         //创建订单号对应的文件夹

#ifdef  _UNICODE 
         char szDir[MAX_PATH] = {0};
         char szLib[50] = "订单库/";
         char szo[] = "/";
         USES_CONVERSION;
         char *sz_normal_0 = T2A(STR_NORMAL_PATH_0);
         char *sz_normal_1 = T2A(STR_NORMAL_PATH_1);
         char *sz_normal_2 = T2A(STR_NORMAL_PATH_2);
         char *sz_normal_3 = T2A(STR_NORMAL_PATH_3);
         char *sz_normal_4 = T2A(STR_NORMAL_PATH_4);

         strcpy_s(szDir,szLib);
         strcat_s(szDir,szOrderNo);
         strcat_s(szDir,szo);
         strcpy_s(szLib,szDir);
         if (1 == objFtpComm.Ftp_MkDir(szDir))
         {
            bMkSuc = TRUE;
            strcat_s(szDir,sz_normal_0);
            if(!objFtpComm.Ftp_MkDir(szDir)) bMkSuc = FALSE;

            strcpy_s(szDir,szLib);
            strcat_s(szDir,sz_normal_1);
            if(!objFtpComm.Ftp_MkDir(szDir)) bMkSuc = FALSE;

            strcpy_s(szDir,szLib);
            strcat_s(szDir,sz_normal_2);
            if(!objFtpComm.Ftp_MkDir(szDir)) bMkSuc = FALSE;

            strcpy_s(szDir,szLib);
            strcat_s(szDir,sz_normal_3);
            if(!objFtpComm.Ftp_MkDir(szDir)) bMkSuc = FALSE;

            strcpy_s(szDir,szLib);
            strcat_s(szDir,sz_normal_4);
            if(!objFtpComm.Ftp_MkDir(szDir)) bMkSuc = FALSE;
#else
         CString strDir = _T(""),strLib = _T("");
         strLib.Format(_T("订单库/%s/"),strOrderNo);
         strDir = strLib;
         if(objFtpComm.Ftp_MkDir(strDir))
         {
            bMkSuc = TRUE;
            strDir = strLib + STR_NORMAL_PATH_0;
            if(!objFtpComm.Ftp_MkDir(strDir)) bMkSuc = FALSE;

            strDir = strLib + STR_NORMAL_PATH_1;
            if(!objFtpComm.Ftp_MkDir(strDir)) bMkSuc = FALSE;

            strDir = strLib + STR_NORMAL_PATH_2;
            if(!objFtpComm.Ftp_MkDir(strDir)) bMkSuc = FALSE;

            strDir = strLib + STR_NORMAL_PATH_3;
            if(!objFtpComm.Ftp_MkDir(strDir)) bMkSuc = FALSE;

            strDir = strLib + STR_NORMAL_PATH_4;
            if(!objFtpComm.Ftp_MkDir(strDir)) bMkSuc = FALSE;
#endif
         }
         else
         {
            nNumsReConn++;
            if (nNumsReConn<NUMS_RECONN_FTP)
            {
               objFtpComm.Ftp_Close();
               Sleep(TIME_SLEEP_RECONN);
               goto loop_ThreadMkDir;
            }			

            bMkSuc = FALSE;
         }
      }

      if (bMkSuc)
      {
         if (NULL != pLpMsg)
         {
            pLpMsg->nFlag = nFlag;
            pLpMsg->nAction = FTP_ACTION_SUC;
         }
         SendMessage(hWnd,WM_QL_FTP_MKDIR,(WPARAM)pMkDirMsg->strOrderNo,(LPARAM)pLpMsg);
      }
      else
      {
         if (1 == nOpenFtp)
         {
            if (NULL != pLpMsg)
            {
               pLpMsg->nFlag = nFlag;
               pLpMsg->nAction = FTP_ACTION_FAIL;
            }
            SendMessage(hWnd,WM_QL_FTP_MKDIR,(WPARAM)pMkDirMsg->strOrderNo,(LPARAM)pLpMsg);
         }
         else
         {
            if (NULL != pLpMsg)
            {
               pLpMsg->nFlag = nFlag;
               if (2 == nOpenFtp) pLpMsg->nAction = FTP_ACTION_DISCONNECTED;
               else pLpMsg->nAction = FTP_ACTION_OPENFAIL;
            }
            SendMessage(hWnd,WM_QL_FTP_MKDIR,(WPARAM)pMkDirMsg->strOrderNo,(LPARAM)pLpMsg);
         }
      }

      if (1 == nOpenFtp) objFtpComm.Ftp_Close();//关闭
   }
   else//http模式暂不处理
   {
      if (NULL != pLpMsg)
      {
         pLpMsg->nFlag = nFlag;
         pLpMsg->nAction = FTP_ACTION_SUC;
      }
      SendMessage(hWnd,WM_QL_FTP_MKDIR,(WPARAM)pMkDirMsg->strOrderNo,(LPARAM)pLpMsg);
   }

   if (pMkDirMsg != NULL)
   {
      delete pMkDirMsg;
      pMkDirMsg = NULL;
   }
   if (NULL != pLpMsg)
   {
      delete pLpMsg;
      pLpMsg = NULL;
   }

   //ReleaseMutex(g_FileTransferEx_hMutex);
   return 0;
}

DWORD WINAPI ThreadDownDir( LPVOID lpParam )
{
   //WaitForSingleObject(g_FileTransferEx_hMutex, INFINITE);
   TransferMsg *pDownDirMsg = (TransferMsg *)lpParam;
   HWND hWnd = pDownDirMsg->hWnd;
   int nFlag = pDownDirMsg->nSpecFlag;
   int nTransFileNum = pDownDirMsg->nTransFileNum;
   int nLoginType = pDownDirMsg->nLoginType;
   TransferFileMsg * pTransFileMsg = pDownDirMsg->pTransFileMsg;
   BOOL bHttpMode = pDownDirMsg->bUseHttp;

   BOOL bDelZip = pDownDirMsg->bDelZip;
   BOOL bUnZipFailRename = pDownDirMsg->bUnZipFailRename;

   CString strFileType = _T("");

   LpMsg_QLtransEx *pLpMsg = new LpMsg_QLtransEx;
   if (NULL != pLpMsg)
   {
      ZeroMemory(pLpMsg,sizeof(LpMsg_QLtransEx));
   }
   int nFileIndex = 0;

   if ( !bHttpMode)//FTP
   {
#ifdef _UNICODE
      char szFarPath[MAX_PATH] = {0};
      char szDownPath[MAX_PATH] = {0};
      char szIp[50] = {0};
      char szName[50] = {0};
      char szPwd[50] = {0};

      char szDBIP[50] = {0};
      char szDB[50] = {0};
      char szDBID[50] = {0};
      char szDBPWD[50] = {0};
      char szUserID[50] = {0};

      strcpy_s(szIp,pDownDirMsg->strIP);
      strcpy_s(szName,pDownDirMsg->strName);
      strcpy_s(szPwd,pDownDirMsg->strPwd);
      // 	strcpy_s(szFarPath,pDownDirMsg->strFarPath);
      // 	strcpy_s(szDownPath,pDownDirMsg->strLocalPath);

      strcpy_s(szDBIP,pDownDirMsg->strDBIP);
      strcpy_s(szDB,pDownDirMsg->strDB);
      strcpy_s(szDBID,pDownDirMsg->strDBID);
      strcpy_s(szDBPWD,pDownDirMsg->strDBPWD);
      strcpy_s(szUserID,pDownDirMsg->strUserID);
#else
      CString strFarPath = _T("");
      CString strDownPath = _T("");
      CString strIP = pDownDirMsg->strIP;
      CString strName = pDownDirMsg->strName;
      CString strPwd = pDownDirMsg->strPwd;

      CString strDBIP = pDownDirMsg->strDBIP;
      CString strDB = pDownDirMsg->strDB;
      CString strDBID = pDownDirMsg->strDBID;
      CString strDBPWD = pDownDirMsg->strDBPWD;
      CString strUserId = pDownDirMsg->strUserID;
#endif // _UNICODE

      int nNumsReConn = 0;

loop_ThreadDownDir:

      zt_FtpComm objFtpComm;
      int nOpenFtp = 0;
#ifdef _UNICODE
      nOpenFtp = objFtpComm.Ftp_OpenEx(szIp,szName, szPwd);
#else
      nOpenFtp = objFtpComm.Ftp_OpenEx(strIP,strName, strPwd);
#endif // _UNICODE

      if (1 == nOpenFtp)
      {
         objFtpComm.Ftp_ProcessMsg(hWnd);
         for (;nFileIndex < nTransFileNum;nFileIndex++)
         {
            if (NULL != hWnd)
            {
               if (NULL != pLpMsg)
               {
                  pLpMsg->nFlag = nFlag;
                  pLpMsg->nAction = FTP_ACTION_START;
               }
               SendMessage(hWnd,WM_QL_FTP_DOWNDIR,(WPARAM)pTransFileMsg[nFileIndex].strLocalPath,(LPARAM)pLpMsg);
            }

#ifdef _UNICODE
            strcpy_s(szFarPath,pTransFileMsg[nFileIndex].strFarPath);
            strcpy_s(szDownPath,pTransFileMsg[nFileIndex].strLocalPath);
#else
            strFarPath = pTransFileMsg[nFileIndex].strFarPath;
            strDownPath = pTransFileMsg[nFileIndex].strLocalPath;
#endif // _UNICODE

            //开启服务成功，执行动作
            
            int nFileNum = 0,nDirNum = 0;

#ifdef  _UNICODE 
            //USES_CONVERSION;
            //theApp.CreateFolder(A2T(szDownPath));
            if(1 == objFtpComm.Ftp_DownDir(szDownPath,szFarPath,&nFileNum,&nDirNum,bDelZip,bUnZipFailRename))
            {
#else
            //theApp.CreateFolder(strDownPath);
            if(1 == objFtpComm.Ftp_DownDir(strDownPath,strFarPath,&nFileNum,&nDirNum,bDelZip,bUnZipFailRename))
            {
#endif
               //对该文件夹下所有文件
               if (NULL != hWnd)
               {
                  if (NULL != pLpMsg)
                  {
                     pLpMsg->nFlag = nFlag;
                     pLpMsg->nAction = FTP_ACTION_SUC;
                  }
                  SendMessage(hWnd,WM_QL_FTP_DOWNDIR,(WPARAM)pTransFileMsg[nFileIndex].strLocalPath,(LPARAM)pLpMsg);
               }
            }
            else
            {
               nNumsReConn++;
               if (nNumsReConn<NUMS_RECONN_FTP)
               {
                  objFtpComm.Ftp_Close();
                  Sleep(TIME_SLEEP_RECONN);
                  goto loop_ThreadDownDir;
               }			

               if (NULL != hWnd)
               {
                  if (NULL != pLpMsg)
                  {
                     pLpMsg->nFlag = nFlag;
                     pLpMsg->nAction = FTP_ACTION_FAIL;
                  }
                  SendMessage(hWnd,WM_QL_FTP_DOWNDIR,(WPARAM)pTransFileMsg[nFileIndex].strLocalPath,(LPARAM)pLpMsg);
               }
            }
         }
      }
      else
      {
         if (NULL != hWnd)
         {
            int nFileIndex = 0;
            for (nFileIndex = 0;nFileIndex < nTransFileNum;nFileIndex++)
            {
               if (NULL != pLpMsg)
               {
                  pLpMsg->nFlag = nFlag;
                  if (2 == nOpenFtp) pLpMsg->nAction = FTP_ACTION_DISCONNECTED;
                  else pLpMsg->nAction = FTP_ACTION_OPENFAIL;
               }
               SendMessage(hWnd,WM_QL_FTP_DOWNDIR,(WPARAM)pTransFileMsg[nFileIndex].strLocalPath,(LPARAM)pLpMsg);
            }
         }
      }

      if (1 == nOpenFtp) objFtpComm.Ftp_Close(); //关闭
   }
   else
   {
      CString strIP(pDownDirMsg->strIP),strName(pDownDirMsg->strName),strPwd(pDownDirMsg->strPwd);
      QL_HttpClient objHttpClient(strIP,strName,strPwd);
      objHttpClient.Http_ProcessMsg(hWnd);
      for (;nFileIndex < nTransFileNum;nFileIndex++)
      {
         if (NULL != hWnd)
         {
            if (NULL != pLpMsg)
            {
               pLpMsg->nFlag = nFlag;
               pLpMsg->nAction = FTP_ACTION_START;
            }
            SendMessage(hWnd,WM_QL_FTP_DOWNDIR,(WPARAM)pTransFileMsg[nFileIndex].strLocalPath,(LPARAM)pLpMsg);
         }

         CString strFarPath (pTransFileMsg[nFileIndex].strFarPath);
         CString strDownPath( pTransFileMsg[nFileIndex].strLocalPath);
         int nFileNum = 0,nDirNum = 0;
         int nRet = objHttpClient.Http_DownDir(strDownPath,strFarPath,nFileNum,nDirNum,NULL,0,pDownDirMsg->nSpecFlag,FALSE,bDelZip,bUnZipFailRename);
         int nRetAction;
         if(nRet == HTTP_RET_CODE_SUCCESS)
         {
            nRetAction = FTP_ACTION_SUC;
         }
         else if(nRet == HTTP_RET_CODE_FAIL)
         {
            nRetAction = FTP_ACTION_FAIL;
         }
         else if (nRet == HTTP_RET_CODE_LOGIN_ERROR)
         {
            nRetAction = FTP_ACTION_DISCONNECTED;
         }
         if (NULL != hWnd)
         {
            if (NULL != pLpMsg)
            {
               pLpMsg->nFlag = nFlag;
               pLpMsg->nAction = nRetAction;
            }
            SendMessage(hWnd,WM_QL_FTP_DOWNDIR,(WPARAM)pTransFileMsg[nFileIndex].strLocalPath,(LPARAM)pLpMsg);
         }
      }
   }

   if (NULL != pTransFileMsg)
   {
      delete []pTransFileMsg;
      pTransFileMsg = NULL;
   }

   if (pDownDirMsg != NULL)
   {
      delete pDownDirMsg;
      pDownDirMsg = NULL;
   }
   if (NULL != pLpMsg)
   {
      delete pLpMsg;
      pLpMsg = NULL;
   }
   if (_T("工艺文件") == strFileType)
   {
      CADOConnEx ADOConn;
      ADOConn.SetConnecetSqlStr(CDBPtLogInfo_New::Instance()->m_strConnectSql);
      //ReleaseMutex(g_FileTransferEx_hMutex);
      CDBPtLogInfo_New::Instance()->InsertSQL_LogInfo(&ADOConn);   
   }
   return 0;
}

DWORD WINAPI ThreadDownDirMsg( LPVOID lpParam )
{
   //WaitForSingleObject(g_FileTransferEx_hMutex, INFINITE);
   TransferMsg *pDownDirMsg = (TransferMsg *)lpParam;
   HWND hWnd = pDownDirMsg->hWnd;
   int nFlag = pDownDirMsg->nSpecFlag;
   int nTransFileNum = pDownDirMsg->nTransFileNum;
   TransferFileMsg * pTransFileMsg = pDownDirMsg->pTransFileMsg;
   int nLoginType = pDownDirMsg->nLoginType;
   DWORD dwStyle = pDownDirMsg->dwStyle;
   BOOL bDelZip = pDownDirMsg->bDelZip;
   BOOL bUnZipFailRename = pDownDirMsg->bUnZipFailRename;
   BOOL bHttpMode = pDownDirMsg->bUseHttp;

   CString strFileType = _T("");

   LpMsg_QLtransEx *pLpMsg = new LpMsg_QLtransEx;
   if (NULL != pLpMsg)
   {
      ZeroMemory(pLpMsg,sizeof(LpMsg_QLtransEx));
   }

   int nFileIndex = 0;
   if (!bHttpMode)
   {
#ifdef _UNICODE
      char szFarPath[MAX_PATH] = {0};
      char szDownPath[MAX_PATH] = {0};
      char szIp[50] = {0};
      char szName[50] = {0};
      char szPwd[50] = {0};

      char szDBIP[50] = {0};
      char szDB[50] = {0};
      char szDBID[50] = {0};
      char szDBPWD[50] = {0};
      char szUserID[50] = {0};

      strcpy_s(szIp,pDownDirMsg->strIP);
      strcpy_s(szName,pDownDirMsg->strName);
      strcpy_s(szPwd,pDownDirMsg->strPwd);
      // 	strcpy_s(szFarPath,pDownDirMsg->strFarPath);
      // 	strcpy_s(szDownPath,pDownDirMsg->strLocalPath);

      strcpy_s(szDBIP,pDownDirMsg->strDBIP);
      strcpy_s(szDB,pDownDirMsg->strDB);
      strcpy_s(szDBID,pDownDirMsg->strDBID);
      strcpy_s(szDBPWD,pDownDirMsg->strDBPWD);
      strcpy_s(szUserID,pDownDirMsg->strUserID);
#else
      CString strFarPath = _T("");
      CString strDownPath = _T("");
      CString strIP = pDownDirMsg->strIP;
      CString strName = pDownDirMsg->strName;
      CString strPwd = pDownDirMsg->strPwd;

      CString strDBIP = pDownDirMsg->strDBIP;
      CString strDB = pDownDirMsg->strDB;
      CString strDBID = pDownDirMsg->strDBID;
      CString strDBPWD = pDownDirMsg->strDBPWD;
      CString strUserId = pDownDirMsg->strUserID;
#endif // _UNICODE

      int nNumsReConn = 0;


loop_ThreadDownDirMsg:

      zt_FtpComm objFtpComm;
      int nOpenFtp = 0;
#ifdef _UNICODE
      nOpenFtp = objFtpComm.Ftp_OpenEx(szIp,szName, szPwd);
#else
      nOpenFtp = objFtpComm.Ftp_OpenEx(strIP,strName, strPwd);
#endif // _UNICODE

      if (1 == nOpenFtp)
      {
         objFtpComm.Ftp_ProcessMsg(hWnd);
         for (;nFileIndex < nTransFileNum;nFileIndex++)
         {
            if (NULL != hWnd)
            {
               if (NULL != pLpMsg)
               {
                  pLpMsg->nFlag = nFlag;
                  pLpMsg->nAction = FTP_ACTION_START;
               }
               SendMessage(hWnd,WM_QL_FTP_DOWNDIR,(WPARAM)pTransFileMsg[nFileIndex].strLocalPath,(LPARAM)pLpMsg);
            }

#ifdef _UNICODE
            strcpy_s(szFarPath,pTransFileMsg[nFileIndex].strFarPath);
            strcpy_s(szDownPath,pTransFileMsg[nFileIndex].strLocalPath);
#else
            strFarPath = pTransFileMsg[nFileIndex].strFarPath;
            strDownPath = pTransFileMsg[nFileIndex].strLocalPath;
#endif // _UNICODE


            //开启服务成功，执行动作

            int nFileNum = 0,nDirNum = 0;
            BOOL bNoDir = FALSE;
            bNoDir = ((FS_NODIR & dwStyle) == FS_NODIR);
#ifdef  _UNICODE 
            if(1 == objFtpComm.Ftp_DownDirEx(szDownPath,szFarPath,&nFileNum,&nDirNum,hWnd,WM_QL_FTP_DOWNDIRMSG,nFlag,bNoDir,bDelZip,bUnZipFailRename))
            {
#ifdef _DEBUG

#else
               USES_CONVERSION;
               CString strAction = _T("");
               CString strFileName = _T("");
               strFileName.Format(_T("%s"),A2T(pTransFileMsg[nFileIndex].strLocalPath));
               strFileName = PathFindFileName(strFileName);
               strAction.Format(_T("下载文件 订单号：%s 文件类型 ：%s "),A2T(pDownDirMsg->strOrderNo),strFileType);
               CADOConnEx ADOConn;

               CString strConnectSql = GetSqlConnectStr(szDBIP,szDB,szDBID,szDBPWD);

               ADOConn.SetConnecetSqlStr(strConnectSql);

               CString strOrderNo(pDownDirMsg->strOrderNo);
               CString strLogUserID(szUserID);
               strAction.Format(_T("文件名：%s 文件类型 ：%s "),strFileName,strFileType);
               if (_T("工艺文件") == strFileType)
               {
                  CDBPtLogInfo_New::Instance()->m_strConnectSql = strConnectSql;
                  CDBPtLogInfo_New::Instance()->SetDataLogInfo(&ADOConn,strFileType,strOrderNo,strFileName,_T("下载"),strLogUserID,nLoginType);
               }
               else
               {
                  switch(nLoginType)
                  {
                  case En_Login_Custom:
                     {
                        DBPTLOGCUSTOM(&ADOConn,strFileType,strOrderNo,strLogUserID,_T("下载"),strAction);
                     }
                     break;
                  case En_Login_User:
                     {
                        DBPTLOGUSER(&ADOConn,strFileType,strOrderNo,strLogUserID,_T("下载"),strAction);
                     }
                     break;
                  case En_Login_Null:
                  default:
                     break;
                  }
               }
#endif // _DEBUG

#else
            if(1 == objFtpComm.Ftp_DownDirEx(strDownPath,strFarPath,&nFileNum,&nDirNum,hWnd,WM_QL_FTP_DOWNDIRMSG,nFlag,bNoDir,bDelZip,bUnZipFailRename))
            {
#ifdef _DEBUG

#else
               CString strAction = _T("");
               CString strFileName = pTransFileMsg[nFileIndex].strLocalPath;
               strFileName = PathFindFileName(strFileName);
               CADOConnEx ADOConn;

               CString strConnectSql = GetSqlConnectStr(strDBIP,strDB,strDBID,strDBPWD);

               ADOConn.SetConnecetSqlStr(strConnectSql);

               CString strOrderNo(pDownDirMsg->strOrderNo);
               strAction.Format(_T("文件名：%s 文件类型 ：%s "),strFileName,strFileType);
               if (_T("工艺文件") == strFileType)
               {
                  CDBPtLogInfo_New::Instance()->m_strConnectSql = strConnectSql;
                  CDBPtLogInfo_New::Instance()->SetDataLogInfo(&ADOConn,strFileType,strOrderNo,strFileName,_T("下载"),strUserId,nLoginType);
               }
               else
               {
                  switch(nLoginType)
                  {
                  case En_Login_Custom:
                     {
                        DBPTLOGCUSTOM(&ADOConn,strFileType,strOrderNo,strUserId,_T("下载"),strAction);
                     }
                     break;
                  case En_Login_User:
                     {
                        DBPTLOGUSER(&ADOConn,strFileType,strOrderNo,strUserId,_T("下载"),strAction);
                     }
                     break;
                  case En_Login_Null:
                  default:
                     break;
                  }
               }
#endif // _DEBUG

#endif
               //对该文件夹下所有文件
               if (NULL != hWnd)
               {
                  if (NULL != pLpMsg)
                  {
                     pLpMsg->nFlag = nFlag;
                     pLpMsg->nAction = FTP_ACTION_SUC;
                  }
                  SendMessage(hWnd,WM_QL_FTP_DOWNDIR,(WPARAM)pTransFileMsg[nFileIndex].strLocalPath,(LPARAM)pLpMsg);
               }
            }
            else
            {
               nNumsReConn++;
               if (nNumsReConn<NUMS_RECONN_FTP)
               {
                  objFtpComm.Ftp_Close();
                  Sleep(TIME_SLEEP_RECONN);
                  goto loop_ThreadDownDirMsg;
               }			

               if (NULL != hWnd)
               {
                  if (NULL != pLpMsg)
                  {
                     pLpMsg->nFlag = nFlag;
                     pLpMsg->nAction = FTP_ACTION_FAIL;
                  }
                  SendMessage(hWnd,WM_QL_FTP_DOWNDIR,(WPARAM)pTransFileMsg[nFileIndex].strLocalPath,(LPARAM)pLpMsg);
               }
            }
         }
      }
      else
      {
         if (NULL != hWnd)
         {
            int nFileIndex = 0;
            for (nFileIndex = 0;nFileIndex < nTransFileNum;nFileIndex++)
            {
               if (NULL != pLpMsg)
               {
                  pLpMsg->nFlag = nFlag;
                  if (2 == nOpenFtp) pLpMsg->nAction = FTP_ACTION_DISCONNECTED;
                  else pLpMsg->nAction = FTP_ACTION_OPENFAIL;
               }
               SendMessage(hWnd,WM_QL_FTP_DOWNDIR,(WPARAM)pTransFileMsg[nFileIndex].strLocalPath,(LPARAM)pLpMsg);
            }
         }
      }

      if (1 == nOpenFtp) objFtpComm.Ftp_Close();//关闭
   }
   else//FTP
   {
      CString strIP(pDownDirMsg->strIP),strName(pDownDirMsg->strName),strPwd(pDownDirMsg->strPwd);
      QL_HttpClient objHttpClient(strIP,strName,strPwd);
      objHttpClient.Http_ProcessMsg(hWnd);
      for (;nFileIndex < nTransFileNum;nFileIndex++)
      {
         if (NULL != hWnd)
         {
            if (NULL != pLpMsg)
            {
               pLpMsg->nFlag = nFlag;
               pLpMsg->nAction = FTP_ACTION_START;
            }
            SendMessage(hWnd,WM_QL_FTP_DOWNDIR,(WPARAM)pTransFileMsg[nFileIndex].strLocalPath,(LPARAM)pLpMsg);
         }
         CString strFarPath (pTransFileMsg[nFileIndex].strFarPath);
         CString strDownPath (pTransFileMsg[nFileIndex].strLocalPath);


         //开启服务成功，执行动作

         int nFileNum = 0,nDirNum = 0;
         BOOL bNoDir = FALSE;
         bNoDir = ((FS_NODIR & dwStyle) == FS_NODIR);
         int nRet = objHttpClient.Http_DownDir(strDownPath,strFarPath,nFileNum,nDirNum,
            hWnd,WM_QL_FTP_DOWNDIRMSG,nFlag,bNoDir,bDelZip,bUnZipFailRename);
         int nRetAction;
         if (nRet == HTTP_RET_CODE_SUCCESS)
         {
            nRetAction = FTP_ACTION_SUC;
         }
         else if (nRet == HTTP_RET_CODE_FAIL)
         {
            nRetAction = FTP_ACTION_FAIL;
         }
         else if (nRet == HTTP_RET_CODE_LOGIN_ERROR)
         {
            nRetAction = FTP_ACTION_DISCONNECTED;
         }

         if (NULL != hWnd)
         {
            if (NULL != pLpMsg)
            {
               pLpMsg->nFlag = nFlag;
               pLpMsg->nAction = nRetAction;
            }
            SendMessage(hWnd,WM_QL_FTP_DOWNDIR,(WPARAM)pTransFileMsg[nFileIndex].strLocalPath,(LPARAM)pLpMsg);
         }
      }
   }

   if (NULL != pTransFileMsg)
   {
      delete []pTransFileMsg;
      pTransFileMsg = NULL;
   }

   if (pDownDirMsg != NULL)
   {
      delete pDownDirMsg;
      pDownDirMsg = NULL;
   }
   if (NULL != pLpMsg)
   {
      delete pLpMsg;
      pLpMsg = NULL;
   }
   if (_T("工艺文件") == strFileType)
   {
      CADOConnEx ADOConn;
      ADOConn.SetConnecetSqlStr(CDBPtLogInfo_New::Instance()->m_strConnectSql);
      //ReleaseMutex(g_FileTransferEx_hMutex);
      CDBPtLogInfo_New::Instance()->InsertSQL_LogInfo(&ADOConn);
   }
   return 0;
}

DWORD WINAPI ThreadGetDirList( LPVOID lpParam )
{
   //WaitForSingleObject(g_FileTransferEx_hMutex, INFINITE);
   TransferListMsg *pGetListMsg = (TransferListMsg *)lpParam;
   HWND hWnd = pGetListMsg->hWnd;
   FileMsg *pItem = NULL;
   int nNum = 0;
   int nFlag = pGetListMsg->nSpecFlag;
   BOOL bHttpMode =  pGetListMsg->bUseHttp;

   //获取列表扩展属性...
   DWORD dwStyle = pGetListMsg->dwStyle;

   LpMsg_QLtransEx *pLpMsg = new LpMsg_QLtransEx;
   if (NULL != pLpMsg)
   {
      ZeroMemory(pLpMsg,sizeof(pLpMsg));
   }

   if (NULL != hWnd)
   {
      if (NULL != pLpMsg)
      {
         pLpMsg->nFlag = nFlag;
         pLpMsg->nAction = FTP_ACTION_START;
      }
      SendMessage(hWnd,WM_QL_FTP_GETLIST,(WPARAM)pGetListMsg->strListDir,(LPARAM)pLpMsg);
   }

   if(!bHttpMode)//FTP模式
   {
#ifdef _UNICODE
      char szFarPath[MAX_PATH] = {0};
      char szIp[50] = {0};
      char szName[50] = {0};
      char szPwd[50] = {0};
      strcpy_s(szIp,pGetListMsg->strIP);
      strcpy_s(szName,pGetListMsg->strName);
      strcpy_s(szPwd,pGetListMsg->strPwd);
      strcpy_s(szFarPath,pGetListMsg->strListDir);
#else
      CString strFarPath = pGetListMsg->strListDir;
      CString strIP = pGetListMsg->strIP;
      CString strName = pGetListMsg->strName;
      CString strPwd = pGetListMsg->strPwd;
#endif // _UNICODE

      int nNumsReConn = 0;
loop_ThreadGetDirList:

      zt_FtpComm objFtpComm;
      int nOpenFtp = 0;
#ifdef _UNICODE
      nOpenFtp = objFtpComm.Ftp_OpenEx(szIp,szName, szPwd);
#else
      nOpenFtp = objFtpComm.Ftp_OpenEx(strIP,strName, strPwd);
#endif // _UNICODE

      if (1 == nOpenFtp)
      {
         objFtpComm.Ftp_ProcessMsg(hWnd);
         //开启服务成功，执行上传动作
         objFtpComm.Ftp_ClearResponse();
#ifdef  _UNICODE 
         if(1 == objFtpComm.Ftp_Getlist(szFarPath,&pItem,&nNum))
         {
#else
         if(1 == objFtpComm.Ftp_Getlist(strFarPath,&pItem,&nNum))
         {
#endif
            if (NULL != hWnd)
            {
               if (NULL != pLpMsg)
               {
                  pLpMsg->nFlag = nFlag;
                  pLpMsg->nNum = nNum;
                  pLpMsg->pVoid = (void *)pItem;
                  pLpMsg->nAction = FTP_ACTION_SUC;
               }
               SendMessage(hWnd,WM_QL_FTP_GETLIST,(WPARAM)pGetListMsg->strListDir,(LPARAM)pLpMsg);
            }
         }
         else if (1 == objFtpComm.Ftp_IsResponseDirectoryNotFound())
         {
            if (NULL != hWnd)
            {
               if (NULL != pLpMsg)
               {
                  pLpMsg->nFlag = nFlag;
                  pLpMsg->nNum = 0;
                  pLpMsg->nAction = FTP_ACTION_FAIL;
               }
               SendMessage(hWnd,WM_QL_FTP_GETLIST,(WPARAM)pGetListMsg->strListDir,(LPARAM)pLpMsg);
            }
         }
         else
         {
            nNumsReConn++;
            if (nNumsReConn<NUMS_RECONN_FTP)
            {
               objFtpComm.Ftp_Close();
               Sleep(TIME_SLEEP_RECONN);
               goto loop_ThreadGetDirList;
            }			

            if (NULL != hWnd)
            {
               if (NULL != pLpMsg)
               {
                  pLpMsg->nFlag = nFlag;
                  pLpMsg->nNum = 0;
                  pLpMsg->nAction = FTP_ACTION_FAIL;
               }
               SendMessage(hWnd,WM_QL_FTP_GETLIST,(WPARAM)pGetListMsg->strListDir,(LPARAM)pLpMsg);
            }
         }
      }
      else
      {
         if (NULL != hWnd)
         {
            if (NULL != pLpMsg)
            {
               pLpMsg->nFlag = nFlag;
               if (2 == nOpenFtp) pLpMsg->nAction = FTP_ACTION_DISCONNECTED;
               else pLpMsg->nAction = FTP_ACTION_OPENFAIL;
            }
            SendMessage(hWnd,WM_QL_FTP_GETLIST,(WPARAM)pGetListMsg->strListDir,(LPARAM)pLpMsg);
         }
      }

      if (1 == nOpenFtp) objFtpComm.Ftp_Close();//关闭
   }
   else//HTTP模式
   {
      CString strFarPath(pGetListMsg->strListDir);
      CString strIP(pGetListMsg->strIP);
      CString strName(pGetListMsg->strName);
      CString strPwd(pGetListMsg->strPwd);
      QL_HttpClient objHttpClient(strIP,strName,strPwd);
      objHttpClient.Http_ProcessMsg(hWnd);
      int nRet = objHttpClient.Http_Getlist(strFarPath,&pItem,&nNum,FS_DEFAULT);
      if ( nRet == HTTP_RET_CODE_SUCCESS)//成功
      {
         if (NULL != hWnd)
         {
            if (NULL != pLpMsg)
            {
               pLpMsg->nFlag = nFlag;
               pLpMsg->nNum = nNum;
               pLpMsg->pVoid = (void *)pItem;
               pLpMsg->nAction = FTP_ACTION_SUC;
            }
            SendMessage(hWnd,WM_QL_FTP_GETLIST,(WPARAM)pGetListMsg->strListDir,(LPARAM)pLpMsg);
         }
      }
      else if (nRet == HTTP_RET_CODE_FAIL)//失败
      {
         if (NULL != hWnd)
         {
            if (NULL != pLpMsg)
            {
               pLpMsg->nFlag = nFlag;
               pLpMsg->nAction = FTP_ACTION_OPENFAIL;
            }
            SendMessage(hWnd,WM_QL_FTP_GETLIST,(WPARAM)pGetListMsg->strListDir,(LPARAM)pLpMsg);
         }
      }
      else if (nRet == HTTP_RET_CODE_LOGIN_ERROR)//登录失败
      {
         if (NULL != hWnd)
         {
            if (NULL != pLpMsg)
            {
               pLpMsg->nFlag = nFlag;
               pLpMsg->nAction = FTP_ACTION_DISCONNECTED;
            }
            SendMessage(hWnd,WM_QL_FTP_GETLIST,(WPARAM)pGetListMsg->strListDir,(LPARAM)pLpMsg);
         }
      }
   }

   if (NULL != pItem)
   {
      delete pItem;
      pItem = NULL;
   }

   if (pGetListMsg != NULL)
   {
      delete pGetListMsg;
      pGetListMsg = NULL;
   }
   if (NULL != pLpMsg)
   {
      delete pLpMsg;
      pLpMsg = NULL;
   }
   //ReleaseMutex(g_FileTransferEx_hMutex);
   return 0;
}

DWORD WINAPI ThreadGetDirListEx( LPVOID lpParam )
{
   //WaitForSingleObject(g_FileTransferEx_hMutex, INFINITE);
   TransferListMsg *pGetListMsg = (TransferListMsg *)lpParam;
   HWND hWnd = pGetListMsg->hWnd;
   FileMsg *pItem = NULL;
   int nNum = 0;
   int nFlag = pGetListMsg->nSpecFlag;

   //获取列表扩展属性...
   DWORD dwStyle = pGetListMsg->dwStyle;

   LpMsg_QLtransEx *pLpMsg = new LpMsg_QLtransEx;
   if (NULL != pLpMsg)
   {
      ZeroMemory(pLpMsg,sizeof(pLpMsg));
   }

   if (NULL != hWnd)
   {
      if (NULL != pLpMsg)
      {
         pLpMsg->nFlag = nFlag;
         pLpMsg->nAction = FTP_ACTION_START;
      }
      SendMessage(hWnd,WM_QL_FTP_GETLIST,(WPARAM)pGetListMsg->strListDir,(LPARAM)pLpMsg);
   }
   BOOL bHttpMode = pGetListMsg->bUseHttp;
   if (!bHttpMode)//FTP
   {
#ifdef _UNICODE
      char szFarPath[MAX_PATH] = {0};
      char szIp[50] = {0};
      char szName[50] = {0};
      char szPwd[50] = {0};
      strcpy_s(szIp,pGetListMsg->strIP);
      strcpy_s(szName,pGetListMsg->strName);
      strcpy_s(szPwd,pGetListMsg->strPwd);
      strcpy_s(szFarPath,pGetListMsg->strListDir);
#else
      CString strFarPath = pGetListMsg->strListDir;
      CString strIP = pGetListMsg->strIP;
      CString strName = pGetListMsg->strName;
      CString strPwd = pGetListMsg->strPwd;
#endif // _UNICODE

      int nNumsReConn = 0;

loop_ThreadGetDirListEx:

      zt_FtpComm objFtpComm;
      int nOpenFtp = 0;
#ifdef _UNICODE
      nOpenFtp = objFtpComm.Ftp_OpenEx(szIp,szName, szPwd);
#else
      nOpenFtp = objFtpComm.Ftp_OpenEx(strIP,strName, strPwd);
#endif // _UNICODE

      if (1 == nOpenFtp)
      {
         objFtpComm.Ftp_ProcessMsg(hWnd);
         //开启服务成功，执行上传动作

#ifdef  _UNICODE 
         if(1 == objFtpComm.Ftp_Getlist(szFarPath,&pItem,&nNum,dwStyle))
         {
#else
         if(1 == objFtpComm.Ftp_Getlist(strFarPath,&pItem,&nNum,dwStyle))
         {
#endif
            if (NULL != hWnd)
            {
               if (NULL != pLpMsg)
               {
                  pLpMsg->nFlag = nFlag;
                  pLpMsg->nNum = nNum;
                  pLpMsg->pVoid = (void *)pItem;
                  pLpMsg->nAction = FTP_ACTION_SUC;
               }
               SendMessage(hWnd,WM_QL_FTP_GETLIST,(WPARAM)pGetListMsg->strListDir,(LPARAM)pLpMsg);
            }
         }
         else
         {
            nNumsReConn++;
            if (nNumsReConn<NUMS_RECONN_FTP)
            {
               objFtpComm.Ftp_Close();
               Sleep(TIME_SLEEP_RECONN);
               goto loop_ThreadGetDirListEx;
            }	  

            if (NULL != hWnd)
            {
               if (NULL != pLpMsg)
               {
                  pLpMsg->nFlag = nFlag;
                  pLpMsg->nNum = 0;
                  pLpMsg->nAction = FTP_ACTION_FAIL;
               }
               SendMessage(hWnd,WM_QL_FTP_GETLIST,(WPARAM)pGetListMsg->strListDir,(LPARAM)pLpMsg);
            }
         }
      }
      else
      {
         if (NULL != hWnd)
         {
            if (NULL != pLpMsg)
            {
               pLpMsg->nFlag = nFlag;
               if (2 == nOpenFtp) pLpMsg->nAction = FTP_ACTION_DISCONNECTED;
               else pLpMsg->nAction = FTP_ACTION_OPENFAIL;
            }
            SendMessage(hWnd,WM_QL_FTP_GETLIST,(WPARAM)pGetListMsg->strListDir,(LPARAM)pLpMsg);
         }
      }

      if (1 == nOpenFtp) objFtpComm.Ftp_Close();//关闭
   }
   else//HTTP
   {
      CString strFarPath(pGetListMsg->strListDir);
      CString strIP(pGetListMsg->strIP);
      CString strName(pGetListMsg->strName);
      CString strPwd(pGetListMsg->strPwd);
      QL_HttpClient objHttpClient(strIP,strName,strPwd);
      objHttpClient.Http_ProcessMsg(hWnd);
      int nRet = objHttpClient.Http_Getlist(strFarPath,&pItem,&nNum,dwStyle);
      if ( nRet == HTTP_RET_CODE_SUCCESS)//成功
      {
         if (NULL != hWnd)
         {
            if (NULL != pLpMsg)
            {
               pLpMsg->nFlag = nFlag;
               pLpMsg->nNum = nNum;
               pLpMsg->pVoid = (void *)pItem;
               pLpMsg->nAction = FTP_ACTION_SUC;
            }
            SendMessage(hWnd,WM_QL_FTP_GETLIST,(WPARAM)pGetListMsg->strListDir,(LPARAM)pLpMsg);
         }
      }
      else if (nRet == HTTP_RET_CODE_FAIL)//失败
      {
         if (NULL != hWnd)
         {
            if (NULL != pLpMsg)
            {
               pLpMsg->nFlag = nFlag;
               pLpMsg->nAction = FTP_ACTION_OPENFAIL;
            }
            SendMessage(hWnd,WM_QL_FTP_GETLIST,(WPARAM)pGetListMsg->strListDir,(LPARAM)pLpMsg);
         }
      }
      else if (nRet == HTTP_RET_CODE_LOGIN_ERROR)//登录失败
      {
         if (NULL != hWnd)
         {
            if (NULL != pLpMsg)
            {
               pLpMsg->nFlag = nFlag;
               pLpMsg->nAction = FTP_ACTION_DISCONNECTED;
            }
            SendMessage(hWnd,WM_QL_FTP_GETLIST,(WPARAM)pGetListMsg->strListDir,(LPARAM)pLpMsg);
         }
      }
   }

   if (NULL != pItem)
   {
      delete pItem;
      pItem = NULL;
   }

   if (pGetListMsg != NULL)
   {
      delete pGetListMsg;
      pGetListMsg = NULL;
   }
   if (NULL != pLpMsg)
   {
      delete pLpMsg;
      pLpMsg = NULL;
   }
   //ReleaseMutex(g_FileTransferEx_hMutex);
   return 0;
}

BOOL ThreadMoveFileSub(TransferMsg *pBackupFileMsg, TransferFileMsg *pTransFileMsg, LpMsg_QLtransEx *pLpMsg)
{
   BOOL bRet = FALSE;
   HWND hWnd = pBackupFileMsg->hWnd;
   int nFlag = pBackupFileMsg->nSpecFlag;

   int nTransFileNum = pBackupFileMsg->nTransFileNum;
   int nLoginType = pBackupFileMsg->nLoginType;
   BOOL bHttpMode = pBackupFileMsg->bUseHttp;

   if (NULL != hWnd)
   {
      if (NULL != pLpMsg)
      {
         pLpMsg->nFlag = nFlag;
         pLpMsg->nAction = FTP_ACTION_START;
      }
      SendMessage(hWnd,WM_QL_FTP_BACKUPFILE,(WPARAM)pBackupFileMsg->strOrderNo,(LPARAM)pLpMsg);
   }

   int nFileIndex = 0;
   if (!bHttpMode)//FTP
   {
#ifdef _UNICODE
      char szFarPath[MAX_PATH] = {0};
      char szCurPath[MAX_PATH] = {0};
      char szIp[50] = {0};
      char szName[50] = {0};
      char szPwd[50] = {0};
      strcpy_s(szIp,pBackupFileMsg->strIP);
      strcpy_s(szName,pBackupFileMsg->strName);
      strcpy_s(szPwd,pBackupFileMsg->strPwd);
      //strcpy_s(szFarPath,pDelDirMsg->strFarPath);
#else
      CString strFarPath = _T("");
      CString strCurPath = _T("");
      CString strIP = pBackupFileMsg->strIP;
      CString strName = pBackupFileMsg->strName;
      CString strPwd = pBackupFileMsg->strPwd;
#endif // _UNICODE

      int nNumsReConn = 0;


loop_ThreadMoveDir:
      zt_FtpComm objFtpComm;
      int nOpenFtp = 0;
#ifdef _UNICODE
      nOpenFtp = objFtpComm.Ftp_OpenEx(szIp,szName, szPwd);
#else
      nOpenFtp = objFtpComm.Ftp_OpenEx(strIP,strName, strPwd);
#endif // _UNICODE

      if (1 == nOpenFtp)
      {
         objFtpComm.Ftp_ProcessMsg(hWnd);
         BOOL bSuc = TRUE;
         for (;nFileIndex < nTransFileNum;nFileIndex++)
         {

#ifdef _UNICODE
            strcpy_s(szFarPath,pTransFileMsg[nFileIndex].strFarPath);
            strcpy_s(szCurPath, pTransFileMsg[nFileIndex].strLocalPath);
#else
            strFarPath = pTransFileMsg[nFileIndex].strFarPath;
            strCurPath = pTransFileMsg[nFileIndex].strLocalPath;
#endif // _UNICODE

            //开启服务成功，重命名
#ifdef  _UNICODE 
            int nRet = objFtpComm.Ftp_RenameDir(szCurPath, szFarPath);
#else
            int nRet = objFtpComm.Ftp_RenameDir(strCurPath, strFarPath);
#endif

            if (1 == nRet)
            {
            }
            else if (2 == nRet)
            {
            }
            else
            {
               nNumsReConn++;
               if (nNumsReConn<NUMS_RECONN_FTP)
               {
                  objFtpComm.Ftp_Close();
                  Sleep(TIME_SLEEP_RECONN);
                  goto loop_ThreadMoveDir;
               }			

               bSuc = FALSE;
               break;
            }
         }
         if (bSuc)
         {
            if (NULL != hWnd)
            {
               if (NULL != pLpMsg)
               {
                  pLpMsg->nFlag = nFlag;
                  pLpMsg->nAction = FTP_ACTION_SUC;
               }
               SendMessage(hWnd,WM_QL_FTP_BACKUPFILE,(WPARAM)pBackupFileMsg->strOrderNo,(LPARAM)pLpMsg);
            }
            bRet = TRUE;
         }
         else
         {
            if (NULL != hWnd)
            {
               if (NULL != pLpMsg)
               {
                  pLpMsg->nFlag = nFlag;
                  pLpMsg->nAction = FTP_ACTION_FAIL;
               }
               SendMessage(hWnd,WM_QL_FTP_BACKUPFILE,(WPARAM)pBackupFileMsg->strOrderNo,(LPARAM)pLpMsg);
            }
         }
      }
      else
      {
         if (NULL != hWnd)
         {
            if (NULL != pLpMsg)
            {
               pLpMsg->nFlag = nFlag;
               if (2 == nOpenFtp) pLpMsg->nAction = FTP_ACTION_DISCONNECTED;
               else pLpMsg->nAction = FTP_ACTION_OPENFAIL;
            }
            SendMessage(hWnd,WM_QL_FTP_BACKUPFILE,(WPARAM)pBackupFileMsg->strOrderNo,(LPARAM)pLpMsg);
         }
      }

      if (1 == nOpenFtp) objFtpComm.Ftp_Close();//关闭
   }
   else
   {
      CString strIP(pBackupFileMsg->strIP),strName(pBackupFileMsg->strName),strPwd(pBackupFileMsg->strPwd);
      QL_HttpClient objHttpClient(strIP,strName,strPwd);
      objHttpClient.Http_ProcessMsg(hWnd);

      for (;nFileIndex < nTransFileNum;nFileIndex++)
      {
         CString strFarPath(pTransFileMsg[nFileIndex].strFarPath);
         CString strCurPath(pTransFileMsg[nFileIndex].strLocalPath);
         int nRet = objHttpClient.Http_Move(strCurPath,strFarPath);
         int nRetAction;
         if (nRet == HTTP_RET_CODE_SUCCESS)
         {
            nRetAction = FTP_ACTION_SUC;
            bRet = TRUE;
         }
         else if (nRet == HTTP_RET_CODE_FILE_NOTEXISTS)
         {
            nRetAction = FTP_ACTION_SUC;
            bRet = TRUE;
         }
         else if (nRet == HTTP_RET_CODE_FAIL)
         {
            nRetAction = FTP_ACTION_FAIL;
            bRet = FALSE;
         }
         else if (nRet == HTTP_RET_CODE_LOGIN_ERROR)
         {
            nRetAction = FTP_ACTION_DISCONNECTED;
            bRet = FALSE;
         }

         if (NULL != hWnd)
         {
            if (NULL != pLpMsg)
            {
               pLpMsg->nFlag = nFlag;
               pLpMsg->nAction = nRetAction;
            }
            SendMessage(hWnd,WM_QL_FTP_BACKUPFILE,(WPARAM)pBackupFileMsg->strOrderNo,(LPARAM)pLpMsg);
         }
      }
   }

   //ReleaseMutex(g_FileTransferEx_hMutex);
   return bRet;
}

DWORD WINAPI ThreadMoveFile(LPVOID lpParam)
{
   //WaitForSingleObject(g_FileTransferEx_hMutex, INFINITE);
   TransferMsg *pBackupFileMsg = (TransferMsg *)lpParam;
   TransferFileMsg *pTransFileMsg = pBackupFileMsg->pTransFileMsg;
   LpMsg_QLtransEx *pLpMsg = new LpMsg_QLtransEx;
   if (NULL != pLpMsg)
   {
      ZeroMemory(pLpMsg,sizeof(LpMsg_QLtransEx));
   }

   ThreadMoveFileSub(pBackupFileMsg, pTransFileMsg, pLpMsg);

   if (NULL != pLpMsg)
   {
      delete pLpMsg;
      pLpMsg = NULL;
   }

   if (NULL != pTransFileMsg)
   {
      delete []pTransFileMsg;
      pTransFileMsg = NULL;
   }

   if (pBackupFileMsg != NULL)
   {
      delete pBackupFileMsg;
      pBackupFileMsg = NULL;
   }

   //ReleaseMutex(g_FileTransferEx_hMutex);

   return 0;
}

BOOL ThreadCopyFilesSub(TransferMsg *pBackupFileMsg, TransferFileMsg *pTransFileMsg, LpMsg_QLtransEx *pLpMsg)
{
   //WaitForSingleObject(g_FileTransferEx_hMutex, INFINITE);
   BOOL bRet = FALSE;
   HWND hWnd = pBackupFileMsg->hWnd;
   int nFlag = pBackupFileMsg->nSpecFlag;

   int nTransFileNum = pBackupFileMsg->nTransFileNum;
   int nLoginType = pBackupFileMsg->nLoginType;
   BOOL bHttpMode = pBackupFileMsg->bUseHttp;

   if (NULL != hWnd)
   {
      if (NULL != pLpMsg)
      {
         pLpMsg->nFlag = nFlag;
         pLpMsg->nAction = FTP_ACTION_START;
      }
      SendMessage(hWnd,WM_QL_FTP_BACKUPFILE,(WPARAM)pBackupFileMsg->strOrderNo,(LPARAM)pLpMsg);
   }

   int nFileIndex = 0;
   if (!bHttpMode)
   {
#ifdef _UNICODE
      char szFarPath[MAX_PATH] = {0};
      char szCurPath[MAX_PATH] = {0};
      char szIp[50] = {0};
      char szName[50] = {0};
      char szPwd[50] = {0};
      strcpy_s(szIp,pBackupFileMsg->strIP);
      strcpy_s(szName,pBackupFileMsg->strName);
      strcpy_s(szPwd,pBackupFileMsg->strPwd);
      //strcpy_s(szFarPath,pDelDirMsg->strFarPath);
#else
      CString strFarPath = _T("");
      CString strCurPath = _T("");
      CString strIP = pBackupFileMsg->strIP;
      CString strName = pBackupFileMsg->strName;
      CString strPwd = pBackupFileMsg->strPwd;
#endif // _UNICODE

      zt_FtpComm objFtpComm;
      int nOpenFtp = 0;
#ifdef _UNICODE
      nOpenFtp = objFtpComm.Ftp_OpenEx(szIp,szName, szPwd);
#else
      nOpenFtp = objFtpComm.Ftp_OpenEx(strIP,strName, strPwd);
#endif // _UNICODE

      if (1 == nOpenFtp)
      {
         objFtpComm.Ftp_ProcessMsg(hWnd);
         BOOL bSuc = TRUE;
         for (;nFileIndex < nTransFileNum;nFileIndex++)
         {
            int nNumsReConnMsg = 0;
            if (NULL != hWnd)
            {
               if (NULL != pLpMsg)
               {
                  pLpMsg->nFlag = nFlag;
                  pLpMsg->nAction = FTP_ACTION_START;
               }
               SendMessage(hWnd, WM_QL_FTP_BACKUPFILEMSG, (WPARAM)pTransFileMsg[nFileIndex].strLocalPath, (LPARAM)pLpMsg);
            }
loop_ThreadMoveDirMsg:
#ifdef _UNICODE
            strcpy_s(szFarPath,pTransFileMsg[nFileIndex].strFarPath);
            strcpy_s(szCurPath, pTransFileMsg[nFileIndex].strLocalPath);
#else
            strFarPath = pTransFileMsg[nFileIndex].strFarPath;
            strCurPath = pTransFileMsg[nFileIndex].strLocalPath;
#endif // _UNICODE

            //开启服务成功，重命名
#ifdef  _UNICODE 
            int nRet;
            int nLen = strlen(szFarPath);
            if (nLen <= 0)
            {
               ASSERT(0);
               //bSuc = FALSE;
               if (NULL != hWnd)
               {
                  if (NULL != pLpMsg)
                  {
                     pLpMsg->nFlag = nFlag;
                     pLpMsg->nAction = FTP_ACTION_FAIL;
                  }
                  SendMessage(hWnd, WM_QL_FTP_BACKUPFILEMSG, (WPARAM)pTransFileMsg[nFileIndex].strLocalPath, (LPARAM)pLpMsg);
               }
               bSuc = FALSE;
               continue;
            }
            if (szFarPath[nLen - 1] == '\\')
            {
               nRet = objFtpComm.Ftp_CopyDir(szFarPath, szCurPath);
            }
            else
            {
               BOOL bMkDir = FALSE;
               for (int n = nLen - 2; n >= 0; --n)
               {
                  if (szFarPath[n] == '\\')
                  {
                     char cTemp = szFarPath[n + 1];
                     szFarPath[n + 1] = 0;
                     objFtpComm.Ftp_ClearResponse();
                     nRet = objFtpComm.Ftp_MkDir(szFarPath);
                     if (0 == nRet)
                     {
                        if (objFtpComm.Ftp_IsResponseDirectoryAlreadyExists())
                        {
                           bMkDir = TRUE;
                        }
                     }
                     else
                     {
                        bMkDir = TRUE;
                     }
                     szFarPath[n + 1] = cTemp;
                     break;
                  }
               }
               if (bMkDir)
                  nRet = objFtpComm.Ftp_RemoteCopyFile(szCurPath, szFarPath);
               else
                  nRet = 0;
            }
#else
            int nRet;
            int nLen = strFarPath.GetLength();
            if (nLen <= 0)
            {
               ASSERT(0);
               bSuc = FALSE;
               break;
            }
            if (strFarPath[nLen - 1] == '\\')
               nRet = objFtpComm.Ftp_CopyDir(strFarPath, strCurPath);
            else
               nRet = objFtpComm.Ftp_RemoteCopyFile(strCurPath, strFarPath);
#endif
            if (1 == nRet)
            {
               if (NULL != hWnd)
               {
                  if (NULL != pLpMsg)
                  {
                     pLpMsg->nFlag = nFlag;
                     pLpMsg->nAction = FTP_ACTION_SUC;
                  }
                  SendMessage(hWnd, WM_QL_FTP_BACKUPFILEMSG, (WPARAM)pTransFileMsg[nFileIndex].strLocalPath, (LPARAM)pLpMsg);
               }
            }
            else if (2 == nRet)
            {
               if (NULL != hWnd)
               {
                  if (NULL != pLpMsg)
                  {
                     pLpMsg->nFlag = nFlag;
                     pLpMsg->nAction = FTP_ACTION_NOFILE;
                  }
                  SendMessage(hWnd, WM_QL_FTP_BACKUPFILEMSG, (WPARAM)pTransFileMsg[nFileIndex].strLocalPath, (LPARAM)pLpMsg);
               }
            }
            else
            {
               nNumsReConnMsg++;
               while (nNumsReConnMsg<NUMS_RECONN_FTP)
               {
                  objFtpComm.Ftp_Close();
                  Sleep(TIME_SLEEP_RECONN);
#ifdef _UNICODE
                  nOpenFtp = objFtpComm.Ftp_OpenEx(szIp,szName, szPwd);
#else
                  nOpenFtp = objFtpComm.Ftp_OpenEx(strIP,strName, strPwd);
#endif // _UNICODE
                  if (nOpenFtp == 1)
                     goto loop_ThreadMoveDirMsg;
                  else
                     nNumsReConnMsg++;
               }			

               if (NULL != hWnd)
               {
                  if (NULL != pLpMsg)
                  {
                     pLpMsg->nFlag = nFlag;
                     pLpMsg->nAction = FTP_ACTION_FAIL;
                  }
                  SendMessage(hWnd, WM_QL_FTP_BACKUPFILEMSG, (WPARAM)pTransFileMsg[nFileIndex].strLocalPath, (LPARAM)pLpMsg);
               }
               bSuc = FALSE;
            }
         }

         if (bSuc)
         {
            if (NULL != hWnd)
            {
               if (NULL != pLpMsg)
               {
                  pLpMsg->nFlag = nFlag;
                  pLpMsg->nAction = FTP_ACTION_SUC;
               }
               SendMessage(hWnd, WM_QL_FTP_BACKUPFILE, (WPARAM)pBackupFileMsg->strOrderNo, (LPARAM)pLpMsg);
            }
            bRet = TRUE;
         }
         else
         {
            if (NULL != hWnd)
            {
               if (NULL != pLpMsg)
               {
                  pLpMsg->nFlag = nFlag;
                  pLpMsg->nAction = FTP_ACTION_FAIL;
               }
               SendMessage(hWnd, WM_QL_FTP_BACKUPFILE, (WPARAM)pBackupFileMsg->strOrderNo, (LPARAM)pLpMsg);
            }
         }
      }
      else
      {
         if (NULL != hWnd)
         {
            if (NULL != pLpMsg)
            {
               pLpMsg->nFlag = nFlag;
               if (2 == nOpenFtp) pLpMsg->nAction = FTP_ACTION_DISCONNECTED;
               else pLpMsg->nAction = FTP_ACTION_OPENFAIL;
            }
            SendMessage(hWnd, WM_QL_FTP_BACKUPFILE, (WPARAM)pBackupFileMsg->strOrderNo, (LPARAM)pLpMsg);
         }
      }

      if (1 == nOpenFtp) objFtpComm.Ftp_Close();//关闭
   }
   else
   {
      CString strIP(pBackupFileMsg->strIP),strName(pBackupFileMsg->strName),strPwd(pBackupFileMsg->strPwd);
      QL_HttpClient objHttpClient(strIP,strName,strPwd);
      objHttpClient.Http_ProcessMsg(hWnd);
      for (;nFileIndex < nTransFileNum;nFileIndex++)
      {
         if (NULL != hWnd)
         {
            if (NULL != pLpMsg)
            {
               pLpMsg->nFlag = nFlag;
               pLpMsg->nAction = FTP_ACTION_START;
            }
            SendMessage(hWnd, WM_QL_FTP_BACKUPFILEMSG, (WPARAM)pTransFileMsg[nFileIndex].strLocalPath, (LPARAM)pLpMsg);
         }
         CString strFarPath(pTransFileMsg[nFileIndex].strFarPath);
         strFarPath.Replace('/','\\');
         int nFind = strFarPath.ReverseFind('\\');
         strFarPath = strFarPath.Left(nFind);

         CString strCurPath(pTransFileMsg[nFileIndex].strLocalPath);
         int nRet = objHttpClient.Http_Copy(strCurPath,strFarPath);
         int nRetAction;
         if (nRet == HTTP_RET_CODE_SUCCESS)
         {
            nRetAction = FTP_ACTION_SUC;
            bRet = TRUE;
         }
         if (nRet == HTTP_RET_CODE_FILE_NOTEXISTS)
         {
            nRetAction = FTP_ACTION_SUC;
            bRet = TRUE;
         }
         else if (nRet == HTTP_RET_CODE_FAIL)
         {
            nRetAction = FTP_ACTION_FAIL;
            bRet = FALSE;
         }
         else if (nRet == HTTP_RET_CODE_LOGIN_ERROR)
         {
            nRetAction = FTP_ACTION_DISCONNECTED;
            bRet = FALSE;
         }

         if (NULL != hWnd)
         {
            if (NULL != pLpMsg)
            {
               pLpMsg->nFlag = nFlag;
               pLpMsg->nAction = nRetAction;
            }
            SendMessage(hWnd, WM_QL_FTP_BACKUPFILE, (WPARAM)pBackupFileMsg->strOrderNo, (LPARAM)pLpMsg);
         }
      }
   }

   //ReleaseMutex(g_FileTransferEx_hMutex);

   return bRet;
}

DWORD WINAPI ThreadCopyVersionToNewCreatedOne(LPVOID lpParam)
{
   TransferMsg *pBackupFileMsg = (TransferMsg *)lpParam;
   TransferFileMsg *pTransFileMsg = pBackupFileMsg->pTransFileMsg;
   LpMsg_QLtransEx *pLpMsg = new LpMsg_QLtransEx;
   if (NULL != pLpMsg)
   {
      ZeroMemory(pLpMsg,sizeof(LpMsg_QLtransEx));
   }
   HWND hWnd = pBackupFileMsg->hWnd;
   pBackupFileMsg->hWnd = NULL; //不让sub函数发消息
   int nFlag = pBackupFileMsg->nSpecFlag;
   if (NULL != hWnd)
   {
      if (NULL != pLpMsg)
      {
         pLpMsg->nFlag = nFlag;
         pLpMsg->nAction = FTP_ACTION_START;
      }
      SendMessage(hWnd,WM_QL_FTP_COPY_VERSION_TO_NEW,(WPARAM)pBackupFileMsg->strOrderNo,(LPARAM)pLpMsg);
   }

   BOOL bSuc = ThreadMoveFileSub(pBackupFileMsg, pTransFileMsg, pLpMsg);
   if (NULL != pTransFileMsg)
   {
      delete []pTransFileMsg;
      pTransFileMsg = NULL;
   }

   TransferMsg *pBackupFileMsg2 = pBackupFileMsg + 1;
   pBackupFileMsg2->hWnd = NULL; //不让sub函数发消息
   TransferFileMsg *pTransFileMsg2 = pBackupFileMsg2->pTransFileMsg;
   if (bSuc)
   {
      bSuc = ThreadCopyFilesSub(pBackupFileMsg2, pTransFileMsg2, pLpMsg);
   }

   if (NULL != pTransFileMsg2)
   {
      delete []pTransFileMsg2;
      pTransFileMsg2 = NULL;
   }

   if (NULL != hWnd)
   {
      if (NULL != pLpMsg)
      {
         pLpMsg->nFlag = nFlag;
         if (bSuc)
            pLpMsg->nAction = FTP_ACTION_SUC;
         else
            pLpMsg->nAction = FTP_ACTION_FAIL;
      }
      SendMessage(hWnd, WM_QL_FTP_COPY_VERSION_TO_NEW,(WPARAM)pBackupFileMsg->strOrderNo,(LPARAM)pLpMsg);
   }

   if (NULL != pLpMsg)
   {
      delete pLpMsg;
      pLpMsg = NULL;
   }

   if (pBackupFileMsg != NULL)
   {
      delete []pBackupFileMsg; //这里有2个
      pBackupFileMsg = NULL;
   }
   return 0;
}

DWORD WINAPI ThreadCopyFiles(LPVOID lpParam)
{
   //WaitForSingleObject(g_FileTransferEx_hMutex, INFINITE);
   TransferMsg *pBackupFileMsg = (TransferMsg *)lpParam;
   TransferFileMsg *pTransFileMsg = pBackupFileMsg->pTransFileMsg;
   LpMsg_QLtransEx *pLpMsg = new LpMsg_QLtransEx;
   if (NULL != pLpMsg)
   {
      ZeroMemory(pLpMsg,sizeof(LpMsg_QLtransEx));
   }

   ThreadCopyFilesSub(pBackupFileMsg, pTransFileMsg, pLpMsg);

   if (NULL != pLpMsg)
   {
      delete pLpMsg;
      pLpMsg = NULL;
   }

   if (NULL != pTransFileMsg)
   {
      delete []pTransFileMsg;
      pTransFileMsg = NULL;
   }

   if (pBackupFileMsg != NULL)
   {
      delete pBackupFileMsg;
      pBackupFileMsg = NULL;
   }
   //ReleaseMutex(g_FileTransferEx_hMutex);

   return 0;
}

DWORD WINAPI ThreadDelDir( LPVOID lpParam )
{
   //WaitForSingleObject(g_FileTransferEx_hMutex, INFINITE);
   TransferMsg *pDelDirMsg = (TransferMsg *)lpParam;
   HWND hWnd = pDelDirMsg->hWnd;
   int nFlag = pDelDirMsg->nSpecFlag;

   int nTransFileNum = pDelDirMsg->nTransFileNum;
   int nLoginType = pDelDirMsg->nLoginType;
   TransferFileMsg *pTransFileMsg = pDelDirMsg->pTransFileMsg;
   BOOL bHttpMode = pDelDirMsg->bUseHttp;

   LpMsg_QLtransEx *pLpMsg = new LpMsg_QLtransEx;
   if (NULL != pLpMsg)
   {
      ZeroMemory(pLpMsg,sizeof(LpMsg_QLtransEx));
   }

   if (NULL != hWnd)
   {
      if (NULL != pLpMsg)
      {
         pLpMsg->nFlag = nFlag;
         pLpMsg->nAction = FTP_ACTION_START;
      }
      SendMessage(hWnd,WM_QL_FTP_DELDIR,(WPARAM)pDelDirMsg->strOrderNo,(LPARAM)pLpMsg);
   }

   int nFileIndex = 0;
   if (!bHttpMode)
   {
#ifdef _UNICODE
      char szFarPath[MAX_PATH] = {0};
      char szIp[50] = {0};
      char szName[50] = {0};
      char szPwd[50] = {0};
      strcpy_s(szIp,pDelDirMsg->strIP);
      strcpy_s(szName,pDelDirMsg->strName);
      strcpy_s(szPwd,pDelDirMsg->strPwd);
      //strcpy_s(szFarPath,pDelDirMsg->strFarPath);
#else
      CString strFarPath = _T("");
      CString strIP = pDelDirMsg->strIP;
      CString strName = pDelDirMsg->strName;
      CString strPwd = pDelDirMsg->strPwd;
#endif // _UNICODE

      int nNumsReConn = 0;


loop_ThreadDelDir:
      zt_FtpComm objFtpComm;
      int nOpenFtp = 0;
#ifdef _UNICODE
      nOpenFtp = objFtpComm.Ftp_OpenEx(szIp,szName, szPwd);
#else
      nOpenFtp = objFtpComm.Ftp_OpenEx(strIP,strName, strPwd);
#endif // _UNICODE

      if (1 == nOpenFtp)
      {
         objFtpComm.Ftp_ProcessMsg(hWnd);
         for (;nFileIndex < nTransFileNum;nFileIndex++)
         {

#ifdef _UNICODE
            strcpy_s(szFarPath,pTransFileMsg[nFileIndex].strFarPath);
#else
            strFarPath = pTransFileMsg[nFileIndex].strFarPath;
#endif // _UNICODE


            //开启服务成功，执行上传动作
#ifdef  _UNICODE 
            if(1 == objFtpComm.Ftp_DelDir(szFarPath))
            {
#else
            if(1 == objFtpComm.Ftp_DelDir(strFarPath))
            {
#endif
               if (NULL != hWnd)
               {
                  if (NULL != pLpMsg)
                  {
                     pLpMsg->nFlag = nFlag;
                     pLpMsg->nAction = FTP_ACTION_SUC;
                  }
                  SendMessage(hWnd,WM_QL_FTP_DELDIR,(WPARAM)pDelDirMsg->strOrderNo,(LPARAM)pLpMsg);
               }
            }
            else
            {
               nNumsReConn++;
               if (nNumsReConn<NUMS_RECONN_FTP)
               {
                  objFtpComm.Ftp_Close();
                  Sleep(TIME_SLEEP_RECONN);
                  goto loop_ThreadDelDir;
               }

               if (NULL != hWnd)
               {
                  if (NULL != pLpMsg)
                  {
                     pLpMsg->nFlag = nFlag;
                     pLpMsg->nAction = FTP_ACTION_FAIL;
                  }
                  SendMessage(hWnd,WM_QL_FTP_DELDIR,(WPARAM)pDelDirMsg->strOrderNo,(LPARAM)pLpMsg);
               }
            }
            if (pDelDirMsg->funcDelete)
            {
               pDelDirMsg->funcDelete(pLpMsg->nAction == FTP_ACTION_SUC,pTransFileMsg[nFileIndex].strFarPath,pDelDirMsg->pUserCallBackData,(nFileIndex+1) == nTransFileNum);
            }
         }
      }
      else
      {
         if (NULL != hWnd)
         {
            if (NULL != pLpMsg)
            {
               pLpMsg->nFlag = nFlag;
               if (2 == nOpenFtp) pLpMsg->nAction = FTP_ACTION_DISCONNECTED;
               else pLpMsg->nAction = FTP_ACTION_OPENFAIL;
            }
            SendMessage(hWnd,WM_QL_FTP_DELDIR,(WPARAM)pDelDirMsg->strOrderNo,(LPARAM)pLpMsg);
         }
      }

      if (1 == nOpenFtp) objFtpComm.Ftp_Close();//关闭
   }
   else
   {
      CString strIP(pDelDirMsg->strIP),strName(pDelDirMsg->strName),strPwd(pDelDirMsg->strPwd);
      QL_HttpClient objHttpClient(strIP,strName,strPwd);
      objHttpClient.Http_ProcessMsg(hWnd);

      for (;nFileIndex < nTransFileNum;nFileIndex++)
      {
         CString strFarPath(pTransFileMsg[nFileIndex].strFarPath);
         int nRet =  objHttpClient.Http_Delete(strFarPath);
         int nRetAction;
         if (nRet == HTTP_RET_CODE_SUCCESS)
         {
            nRetAction = FTP_ACTION_SUC;
         }
         else if (nRet == HTTP_RET_CODE_FAIL)
         {
            nRetAction = FTP_ACTION_FAIL;
         }
         else if (nRet == HTTP_RET_CODE_LOGIN_ERROR)
         {
            nRetAction = FTP_ACTION_DISCONNECTED;
         }

         if (NULL != hWnd)
         {
            if (NULL != pLpMsg)
            {
               pLpMsg->nFlag = nFlag;
               pLpMsg->nAction = nRetAction;
            }
            SendMessage(hWnd,WM_QL_FTP_DELDIR,(WPARAM)pDelDirMsg->strOrderNo,(LPARAM)pLpMsg);
         }

         if (pDelDirMsg->funcDelete)
         {
            pDelDirMsg->funcDelete(pLpMsg->nAction == FTP_ACTION_SUC,pTransFileMsg[nFileIndex].strFarPath,pDelDirMsg->pUserCallBackData,(nFileIndex+1) == nTransFileNum);
         }
      }
   }

   if (NULL != pTransFileMsg)
   {
      delete []pTransFileMsg;
      pTransFileMsg = NULL;
   }

   if (pDelDirMsg != NULL)
   {
      delete pDelDirMsg;
      pDelDirMsg = NULL;
   }
   if (NULL != pLpMsg)
   {
      delete pLpMsg;
      pLpMsg = NULL;
   }
   //ReleaseMutex(g_FileTransferEx_hMutex);

   return 0;
}

DWORD WINAPI ThreadDownByEx( LPVOID lpParam )
{
   //WaitForSingleObject(g_FileTransferEx_hMutex, INFINITE);
   TransferMsg *pDownByExMsg = (TransferMsg *)lpParam;
   HWND hWnd = pDownByExMsg->hWnd;
   int nFlag = pDownByExMsg->nSpecFlag;
   CString strFileType = _T("");
   FilePathMsg * szPathRecv = NULL;
   int nFileNum = 0;
   BOOL bDir = pDownByExMsg->bDir;
   int nLoginType = pDownByExMsg->nLoginType;

   int nTransFileNum = pDownByExMsg->nTransFileNum;
   TransferFileMsg * pTransFileMsg = pDownByExMsg->pTransFileMsg;

   DWORD dwStyle = pDownByExMsg->dwStyle;

   BOOL bDelZip = pDownByExMsg->bDelZip;
   BOOL bUnZipFailRename = pDownByExMsg->bUnZipFailRename;
   BOOL bHttpMode = pDownByExMsg->bUseHttp;

   LpMsg_QLtransEx *pLpMsg = new LpMsg_QLtransEx;
   if (NULL != pLpMsg)
   {
      ZeroMemory(pLpMsg,sizeof(LpMsg_QLtransEx));
   }

   int nFileIndex = 0;
   if (!bHttpMode)
   {
#ifdef _UNICODE
      char szFarPath[MAX_PATH] = {0};
      char szDownPath[MAX_PATH] = {0};
      char szIp[50] = {0};
      char szName[50] = {0};
      char szPwd[50] = {0};

      char szDBIP[50] = {0};
      char szDB[50] = {0};
      char szDBID[50] = {0};
      char szDBPWD[50] = {0};
      char szUserID[50] = {0};

      char szEx[10] = {0};

      strcpy_s(szIp,pDownByExMsg->strIP);
      strcpy_s(szName,pDownByExMsg->strName);
      strcpy_s(szPwd,pDownByExMsg->strPwd);
      // 	strcpy_s(szFarPath,pDownByExMsg->strFarPath);
      // 	strcpy_s(szDownPath,pDownByExMsg->strLocalPath);

      strcpy_s(szDBIP,pDownByExMsg->strDBIP);
      strcpy_s(szDB,pDownByExMsg->strDB);
      strcpy_s(szDBID,pDownByExMsg->strDBID);
      strcpy_s(szDBPWD,pDownByExMsg->strDBPWD);
      strcpy_s(szUserID,pDownByExMsg->strUserID);

      //	strcpy_s(szEx,pDownByExMsg->strExtension);
#else
      CString strFarPath = _T("");
      CString strDownPath = _T("");
      CString strIP = pDownByExMsg->strIP;
      CString strName = pDownByExMsg->strName;
      CString strPwd = pDownByExMsg->strPwd;

      CString strDBIP = pDownByExMsg->strDBIP;
      CString strDB = pDownByExMsg->strDB;
      CString strDBID = pDownByExMsg->strDBID;
      CString strDBPWD = pDownByExMsg->strDBPWD;
      CString strUserId = pDownByExMsg->strUserID;

      CString strEx = _T("");
#endif // _UNICODE

      int nNumsReConn = 0;

loop_ThreadDownByEx:

      zt_FtpComm objFtpComm;
      int nOpenFtp = 0;
#ifdef _UNICODE
      nOpenFtp = objFtpComm.Ftp_OpenEx(szIp,szName, szPwd);
#else
      nOpenFtp = objFtpComm.Ftp_OpenEx(strIP,strName, strPwd);
#endif // _UNICODE

      if (1 == nOpenFtp)
      {
         objFtpComm.Ftp_ProcessMsg(hWnd);

         for (;nFileIndex < nTransFileNum;nFileIndex++)
         {
            nFileNum = 0;
            if (NULL != hWnd)
            {
               if (NULL != pLpMsg)
               {
                  pLpMsg->nFlag = nFlag;
                  pLpMsg->nAction = FTP_ACTION_START;
                  pLpMsg->nNum = nFileNum;
               }
               SendMessage(hWnd,WM_QL_FTP_DOWNBYEX,(WPARAM)szPathRecv,(LPARAM)pLpMsg);
            }

#ifdef _UNICODE
            strcpy_s(szFarPath,pTransFileMsg[nFileIndex].strFarPath);
            strcpy_s(szDownPath,pTransFileMsg[nFileIndex].strLocalPath);
            strcpy_s(szEx,pTransFileMsg[nFileIndex].strExtension);
#else
            strFarPath = pTransFileMsg[nFileIndex].strFarPath;
            strDownPath = pTransFileMsg[nFileIndex].strLocalPath;
            strEx = pTransFileMsg[nFileIndex].strExtension;
#endif // _UNICODE
            //开启服务成功，执行动作
            BOOL bNoDir = FALSE;
            bNoDir = ((FS_NODIR & dwStyle) == FS_NODIR);
#ifdef  _UNICODE 
            int nRet = objFtpComm.Ftp_DownByEx(szDownPath, szFarPath, szEx,&szPathRecv,&nFileNum,bDir,hWnd,WM_QL_FTP_DOWNBYEXMSG,nFlag,bNoDir,bDelZip,bUnZipFailRename);
            if(1 == nRet)
            {
               //不写日志的话 就不要了

#else
            int nRet = objFtpComm.Ftp_DownByEx(strDownPath, strFarPath, (LPSTR)(LPCTSTR)strEx,&szPathRecv,&nFileNum,bDir,hWnd,WM_QL_FTP_DOWNBYEXMSG,nFlag,bNoDir,bDelZip,bUnZipFailRename);
            if(1 == nRet)
            {
               //不写日志的话 就不要了
#endif
               //对该文件夹下所有文件
               if (NULL != hWnd)
               {
                  if (NULL != pLpMsg)
                  {
                     pLpMsg->nFlag = nFlag;
                     pLpMsg->nAction = FTP_ACTION_SUC;
                     pLpMsg->nNum = nFileNum;
                  }
                  SendMessage(hWnd,WM_QL_FTP_DOWNBYEX,(WPARAM)szPathRecv,(LPARAM)pLpMsg);
               }
            }
            else
            {
               if (2 == nRet)
               {
                  nNumsReConn = NUMS_RECONN_FTP;
               }
               else
               {
                  nNumsReConn++;
                  if (nNumsReConn<NUMS_RECONN_FTP)
                  {
                     objFtpComm.Ftp_Close();
                     Sleep(TIME_SLEEP_RECONN);
                     goto loop_ThreadDownByEx;
                  }
               }

               if (NULL != hWnd)
               {
                  if (NULL != pLpMsg)
                  {
                     pLpMsg->nFlag = nFlag;
                     pLpMsg->nAction = FTP_ACTION_FAIL;
                     pLpMsg->nNum = nFileNum;
                  }
                  SendMessage(hWnd,WM_QL_FTP_DOWNBYEX,(WPARAM)szPathRecv,(LPARAM)pLpMsg);
               }
            }

            if (NULL != szPathRecv)
            {
               free(szPathRecv);
               szPathRecv = NULL;
            }
         }
      }
      else
      {
         if (NULL != hWnd)
         {
            if (NULL != pLpMsg)
            {
               pLpMsg->nFlag = nFlag;
               if (2 == nOpenFtp) pLpMsg->nAction = FTP_ACTION_DISCONNECTED;
               else pLpMsg->nAction = FTP_ACTION_OPENFAIL;
               pLpMsg->nNum = nFileNum;
            }
            SendMessage(hWnd,WM_QL_FTP_DOWNBYEX,(WPARAM)szPathRecv,(LPARAM)pLpMsg);
         }
      }

      if (1 == nOpenFtp) objFtpComm.Ftp_Close();//关闭
   }
   else
   {
      CString strIP(pDownByExMsg->strIP),strName(pDownByExMsg->strName),strPwd(pDownByExMsg->strPwd);
      QL_HttpClient objHttpClient(strIP,strName,strPwd);
      objHttpClient.Http_ProcessMsg(hWnd);
      for (;nFileIndex < nTransFileNum;nFileIndex++)
      {
         if (NULL != hWnd)
         {
            if (NULL != pLpMsg)
            {
               pLpMsg->nFlag = nFlag;
               pLpMsg->nAction = FTP_ACTION_START;
               pLpMsg->nNum = nFileNum;
            }
            SendMessage(hWnd,WM_QL_FTP_DOWNBYEX,(WPARAM)szPathRecv,(LPARAM)pLpMsg);
         }

         CString strFarPath(pTransFileMsg[nFileIndex].strFarPath);
         CString strDownPath(pTransFileMsg[nFileIndex].strLocalPath);
         CString strEx(pTransFileMsg[nFileIndex].strExtension);

         BOOL bNoDir = FALSE;
         bNoDir = ((FS_NODIR & dwStyle) == FS_NODIR);
         int nRet = objHttpClient.Http_DownByEx(strDownPath, strFarPath, strEx,&szPathRecv,nFileNum,bDir,hWnd,WM_QL_FTP_DOWNBYEXMSG,nFlag,bNoDir,bDelZip,bUnZipFailRename);
         int nRetAction ;
         if (nRet == HTTP_RET_CODE_SUCCESS)
         {
            nRetAction = FTP_ACTION_SUC;
         }
         else if (nRet == HTTP_RET_CODE_FAIL)
         {
            nRetAction = FTP_ACTION_FAIL;
         }
         else if (nRet == HTTP_RET_CODE_LOGIN_ERROR)
         {
            nRetAction = FTP_ACTION_DISCONNECTED;
         }

         if (NULL != hWnd)
         {
            if (NULL != pLpMsg)
            {
               pLpMsg->nFlag = nFlag;
               pLpMsg->nAction = nRetAction;
               pLpMsg->nNum = nFileNum;
            }
            SendMessage(hWnd,WM_QL_FTP_DOWNBYEX,(WPARAM)szPathRecv,(LPARAM)pLpMsg);
         }
      }
   }

   if (NULL != pTransFileMsg)
   {
      delete []pTransFileMsg;
      pTransFileMsg = NULL;
   }

   if (pDownByExMsg != NULL)
   {
      delete pDownByExMsg;
      pDownByExMsg = NULL;
   }
   if (NULL != pLpMsg)
   {
      delete pLpMsg;
      pLpMsg = NULL;
   }
   if (NULL != szPathRecv)
   {
      free(szPathRecv);
      szPathRecv = NULL;
   }
   //ReleaseMutex(g_FileTransferEx_hMutex);
   return 0;
}

DWORD WINAPI ThreadLogFileToCloud(LPVOID lpParam)
{
   CloudLogMsg * pCloudMsg = (CloudLogMsg *)lpParam;

   if (NULL == pCloudMsg)
   {
      return 0;
   }

   CString strLocalPath = _T(""),strTypeName = _T(""),strFileName = _T("");

#ifdef _UNICODE
   char szLocalPath[MAX_PATH] = {0};
   char szTypeName[TypeNameLength] = {0};
   char szFileName[MAX_PATH] = {0};

   strcpy_s(szLocalPath,pCloudMsg->strLocalPath);
   strcpy_s(szTypeName,pCloudMsg->strTypeName);
   strcpy_s(szFileName,pCloudMsg->strSourceFileName);

   strLocalPath = CString(szLocalPath);
   strTypeName = CString(szTypeName);
   strFileName = CString(szFileName);
#else
   strLocalPath = pCloudMsg->strLocalPath;
   strTypeName = pCloudMsg->strTypeName;
   strFileName = pCloudMsg->strSourceFileName;
#endif // _UNICODE


   zt_FtpComm objFtpComm;
   int nOpenFtp = 0;
   nOpenFtp = objFtpComm.Ftp_OpenEx("www.qilirj.cn","ql160504", "ql160504");
   if (1 != nOpenFtp)
   {
      DeleteFile(strLocalPath);
      return 0;
   }

   CString strFarPath = _T("");
   strFarPath.Format(_T("Log_Bug\\%s"),strTypeName);

   char szFarPath[30] = {0},szFarFilePath[MAX_PATH] = {0};
   memset(szFarPath,0,30);
   memset(szFarFilePath,0,sizeof(szFarFilePath));
#ifdef _UNICODE
   QLCOMAPI.WCharToMByte(strFarPath,szFarPath,sizeof(szFarPath)/sizeof(szFarPath[0]));
   objFtpComm.Ftp_MkDir(szFarPath);

   CString strFarFilePath(szFarPath);
   strFarFilePath = strFarFilePath + _T("\\") + strFileName;

   QLCOMAPI.WCharToMByte(strFarFilePath,szFarFilePath,sizeof(szFarFilePath)/sizeof(szFarFilePath[0]));

   objFtpComm.Ftp_Upload(szLocalPath,szFarFilePath);
#else
   strncpy_s(szFarPath,(LPSTR)(LPCTSTR)strFarPath, sizeof(szFarPath) - 1);
   objFtpComm.Ftp_MkDir(szFarPath);

   CString strFarFilePath(szFarPath);
   strFarFilePath = strFarFilePath + _T("\\") + strFileName;

   strncpy_s(szFarFilePath,(LPSTR)(LPCTSTR)strFarFilePath, sizeof(szFarFilePath) - 1);

   objFtpComm.Ftp_Upload(strLocalPath,szFarFilePath);

#endif // _UNICODE

   if (NULL != pCloudMsg)
   {
      delete pCloudMsg;
      pCloudMsg = NULL;
   }
   DeleteFile(strLocalPath);
   return 0;
}


DWORD WINAPI ThreadShowLoading(LPVOID lpParam)
{
   S_Loading * pLoading = (S_Loading*)lpParam;

   ASSERT(NULL != pLoading);

   AFX_MANAGE_STATE(AfxGetStaticModuleState());
   switch (pLoading->nLoadingType)
   {
   case En_Loading_Marquee:
      ShowMarquee();
      break;
   }

   if (NULL != pLoading)
   {
      delete pLoading;
      pLoading = NULL;
   }

   return 0;
}

