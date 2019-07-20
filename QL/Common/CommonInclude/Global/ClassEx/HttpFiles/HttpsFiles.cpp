#include "stdafx.h"
#include "HttpFiles/HttpsFiles.h"

std::shared_ptr<CQLHttpsFiles> CQLHttpsFiles::sm_inst = NULL;

CQLHttpsFiles::CQLHttpsFiles()
{

}

CQLHttpsFiles::~CQLHttpsFiles()
{

}

CQLHttpsFiles* CQLHttpsFiles::GetInstance()
{
   if(sm_inst.get() == 0)
      sm_inst = shared_ptr<CQLHttpsFiles>(new CQLHttpsFiles);
   return sm_inst.get();
}

BOOL CQLHttpsFiles::DownLoadFile(const CString& strFileURLInServer, const CString & strFileLocalFullPath)
{
   ASSERT(strFileURLInServer != "");
   ASSERT(strFileLocalFullPath != "");
   CInternetSession session;
   CHttpConnection* pHttpConnection = NULL;
   CHttpFile* pHttpFile = NULL;
   CString strServer, strObject;
   INTERNET_PORT wPort;

   DWORD dwType;
   const int nTimeOut = 2000;
   session.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, nTimeOut); //重试之间的等待延时
   session.SetOption(INTERNET_OPTION_CONNECT_RETRIES, 1);   //重试次数
   char* pszBuffer = NULL;  

   try
   {
      AfxParseURL(strFileURLInServer, dwType, strServer, strObject, wPort);
      pHttpConnection = session.GetHttpConnection(strServer, wPort);
      pHttpFile = pHttpConnection->OpenRequest(CHttpConnection::HTTP_VERB_GET, strObject);
      if(pHttpFile->SendRequest() == FALSE)
         return FALSE;
      DWORD dwStateCode;

      pHttpFile->QueryInfoStatusCode(dwStateCode);
      if(dwStateCode == HTTP_STATUS_OK)
      {
         HANDLE hFile = CreateFile(strFileLocalFullPath, GENERIC_WRITE,
            FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL,
            NULL);  //创建本地文件
         if(hFile == INVALID_HANDLE_VALUE)
         {
            pHttpFile->Close();
            pHttpConnection->Close();
            session.Close();
            return FALSE;
         }

         char szInfoBuffer[1000];  //返回消息
         DWORD dwFileSize = 0;   //文件长度
         DWORD dwInfoBufferSize = sizeof(szInfoBuffer);
         BOOL bResult = FALSE;
         bResult = pHttpFile->QueryInfo(HTTP_QUERY_CONTENT_LENGTH,
            (void*)szInfoBuffer,&dwInfoBufferSize,NULL);

         dwFileSize = atoi(szInfoBuffer);
         const int BUFFER_LENGTH = 1024 * 10;
         pszBuffer = new char[BUFFER_LENGTH];  //读取文件的缓冲
         DWORD dwWrite, dwTotalWrite;
         dwWrite = dwTotalWrite = 0;
         UINT nRead = pHttpFile->Read(pszBuffer, BUFFER_LENGTH); //读取服务器上数据

         while(nRead > 0)
         {
            WriteFile(hFile, pszBuffer, nRead, &dwWrite, NULL);  //写到本地文件
            dwTotalWrite += dwWrite;
            nRead = pHttpFile->Read(pszBuffer, BUFFER_LENGTH);
         }

         delete[]pszBuffer;
         pszBuffer = NULL;
         CloseHandle(hFile);
      }
      else
      {
         delete[]pszBuffer;
         pszBuffer = NULL;
         if(pHttpFile != NULL)
         {
            pHttpFile->Close();
            delete pHttpFile;
            pHttpFile = NULL;
         }
         if(pHttpConnection != NULL)
         {
            pHttpConnection->Close();
            delete pHttpConnection;
            pHttpConnection = NULL;
         }
         session.Close();
         return FALSE;
      }
   }
   catch(...)
   {
      delete[]pszBuffer;
      pszBuffer = NULL;
      if(pHttpFile != NULL)
      {
         pHttpFile->Close();
         delete pHttpFile;
         pHttpFile = NULL;
      }
      if(pHttpConnection != NULL)
      {
         pHttpConnection->Close();
         delete pHttpConnection;
         pHttpConnection = NULL;
      }
      session.Close();
      return FALSE;
   }

   if(pHttpFile != NULL)
      pHttpFile->Close();
   if(pHttpConnection != NULL)
      pHttpConnection->Close();
   session.Close();
   return TRUE;
}

BOOL CQLHttpsFiles::UploadFile(LPCTSTR strURL,LPCTSTR strLocalFileName)
{
   ASSERT(strURL != NULL && strLocalFileName != NULL);

   BOOL bResult = FALSE;
   DWORD dwType = 0;
   CString strServer;
   CString strObject;
   INTERNET_PORT wPort = 0;
   DWORD dwFileLength = 0;
   char * pFileBuff = NULL;

   CHttpConnection * pHC = NULL;
   CHttpFile * pHF = NULL;
   CInternetSession cis;

   bResult =  AfxParseURL(strURL, dwType, strServer, strObject, wPort);
   if(!bResult)
      return FALSE;
   CFile file;
   try
   {
      if(!file.Open(strLocalFileName, CFile::shareDenyNone | CFile::modeRead))
         return FALSE;
      dwFileLength = file.GetLength();
      if(dwFileLength <= 0)
         return FALSE;
      pFileBuff = new char[dwFileLength];
      memset(pFileBuff, 0, sizeof(char) * dwFileLength);
      file.Read(pFileBuff, dwFileLength);

      const int nTimeOut = 5000;
      cis.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, nTimeOut); //联接超时设置
      cis.SetOption(INTERNET_OPTION_CONNECT_RETRIES, 1);  //重试1次
      pHC = cis.GetHttpConnection(strServer, wPort);  //取得一个Http联接

      pHF = pHC->OpenRequest(CHttpConnection::HTTP_VERB_POST, strObject);
      if(!pHF->SendRequest(NULL, 0, pFileBuff, dwFileLength))
      {
         delete[]pFileBuff;
         pFileBuff = NULL;
         pHF->Close();
         pHC->Close();
         cis.Close();
         return FALSE;
      }
      DWORD dwStateCode = 0;
      pHF->QueryInfoStatusCode(dwStateCode);

      if(dwStateCode == HTTP_STATUS_OK)
         bResult = TRUE;
      else
      {
         DWORD dwError = GetLastError();
         CString str;
         str.Format(_T("Unknow Exception occur!\r\n%d"), dwError);
         AfxMessageBox(str);
      }
   }

   catch(CInternetException * pEx)
   {
      //char sz[256] = _T("");
      CString sz;
      pEx->GetErrorMessage((LPTSTR)(LPCTSTR)sz, 25);
      CString str;
      str.Format(_T("InternetException occur!\r\n%s"), sz);
      AfxMessageBox(str);
   }
   catch(CFileException& fe)
   {
      CString str;
      str.Format(_T("FileException occur!\r\n%d"), fe.m_lOsError);
      AfxMessageBox(str);
   }
   catch(...)
   {
      DWORD dwError = GetLastError();
      CString str;
      str.Format(_T("Unknow Exception occur!\r\n%d"), dwError);
      AfxMessageBox(str);
   }

   delete[]pFileBuff;
   pFileBuff = NULL;
   file.Close();
   pHF->Close();
   pHC->Close();
   cis.Close();
   return bResult;
}

