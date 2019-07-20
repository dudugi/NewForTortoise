#pragma once
//////////////////////////////////// HttpClient.h add����


#include <afxinet.h>
#include <string.h>
using namespace std;

#define  IE_AGENT  _T("Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1; .NET CLR 2.0.50727)")

// �����ɹ�
#define SUCCESS        0
// ����ʧ��
#define FAILURE        1
// ������ʱ
#define OUTTIME        2

class CHttpClient
{
public:
   CHttpClient(LPCTSTR strAgent = IE_AGENT);
   virtual ~CHttpClient(void);

   int HttpGet(LPCTSTR strUrl, LPCTSTR strPostData, CString &strResponse);
   int HttpPost(LPCTSTR strUrl, LPCTSTR strPostData, CString &strResponse);
   int HttpPost(LPCTSTR strHeader, LPCTSTR strUrl, LPCTSTR strPostData, CString &strResponse);

   CString EncodeParam(const CString & strParam);

private:
   int ExecuteRequest(LPCTSTR strHeader,LPCTSTR strMethod, LPCTSTR strUrl, LPCTSTR strPostData, CString &strResponse);
   void Clear();
private:
   CInternetSession *m_pSession;
   CHttpConnection *m_pConnection;
   CHttpFile *m_pFile;

};
