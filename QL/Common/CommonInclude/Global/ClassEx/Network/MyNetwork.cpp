#include "StdAfx.h"
#include "MyNetwork.h"

std::shared_ptr<CMyNetwork> CMyNetwork::sm_inst;

CMyNetwork::CMyNetwork()
{
	hIcmp = LoadLibrary(_T("icmp.dll"));
	if(NULL != hIcmp)
	{
		pIcmpCreateFile = (PIcmpCreateFile)GetProcAddress(hIcmp, "IcmpCreateFile");
		pIcmpSendEcho = (PIcmpSendEcho)GetProcAddress(hIcmp, "IcmpSendEcho");
		pIcmpCloseHandle = (PIcmpCloseHandle)GetProcAddress(hIcmp, "IcmpCloseHandle");
	}

	//memset(m_szDesAdress,0,sizeof(m_szDesAdress)/sizeof(char));//���char����
	m_strDesAdress = _T("");
}


CMyNetwork::~CMyNetwork()
{
	FreeLibrary(hIcmp);
}

CMyNetwork* CMyNetwork::Instance()
{
	if(sm_inst.get() == 0)
		sm_inst = shared_ptr<CMyNetwork>(new CMyNetwork);

	return sm_inst.get();
}

void CMyNetwork::SetDesAdress(CString strUrl)
{
	strUrl.Trim();
	ASSERT(!strUrl.IsEmpty());

	m_strDesAdress = strUrl;
}

BOOL CMyNetwork::PingNet()
{
	ASSERT(!m_strDesAdress.IsEmpty());

	char szDesAdress[MAX_PATH];
	memset(szDesAdress,0,sizeof(szDesAdress)/sizeof(char));//���char����

#ifdef _UNICODE
	USES_CONVERSION;
	char *pszDesAdress = T2A(m_strDesAdress);
	strcpy(szDesAdress, pszDesAdress);
#else
	_tcscpy(szDesAdress, (LPCTSTR)m_strDesAdress);
#endif

	ASSERT(strlen(szDesAdress) != 0);//�ж�char����Ϊ�գ�if(m_szDesAdress[0]=='\0') �� strlen(m_szDesAdress)==0

	//ping5�Σ����ȫ����ʱ˵�������˶Ͽ�
	USHORT usTimes = 5;
	if(PingNet(szDesAdress,usTimes) > 0)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

int CMyNetwork::PingNet(const char *v_pszDesAdress, USHORT v_usTimes, ULONG v_ulTimeout)
{
	ULONG ulDesIP = 0;
	int ret = 0;

	// �����ݵĲ���Ϊ����ʱ��������������IP
	ulDesIP = inet_addr(v_pszDesAdress);//a.b.c.d
	//����
	if(ulDesIP == INADDR_NONE)
	{
		//2017/04/11 zhangt ��ַ������adc.net.com
		//#include <winsock2.h>
		//#pragma comment(lib, "ws2_32.lib")
		WSADATA wsaData;
		WSAStartup(MAKEWORD(2, 2), &wsaData);//��ʼ��
		// ������������
		PHOSTENT pHostent = gethostbyname(v_pszDesAdress);
		if (pHostent == NULL)
		{
			TRACE(_T("%d is the error."), WSAGetLastError());  
			return -1;
		}
		ulDesIP = *(DWORD *)pHostent->h_addr;
		WSACleanup();//�ͷ���Դ
	}

	// ���뷢�ͻ�����
	void *sendBuffer = new char[32];
	if (sendBuffer == NULL)
	{
		return -1;
	}

	// ������ջ�����
	unsigned long replySize = sizeof(ICMP_ECHO_REPLY) + 32;
	void *replyBuffer = new char[replySize];
	if (replyBuffer == NULL)
	{
		delete [] sendBuffer;
		sendBuffer = NULL;
		return -1;
	}
	PICMP_ECHO_REPLY pIcmpEchoReply = (PICMP_ECHO_REPLY)replyBuffer;

	// ��ȡICMP echo������
	HANDLE hIcmpFile = pIcmpCreateFile();
	if (hIcmpFile == INVALID_HANDLE_VALUE)
	{
		delete [] sendBuffer;
		sendBuffer = NULL;
		delete [] replyBuffer;
		replyBuffer = NULL;
		return -1;
	}

	// ����IcmpSendEcho����ȡPingֵ
	for (int i=0; i<v_usTimes; i++)
	{
		pIcmpSendEcho(hIcmpFile, ulDesIP, sendBuffer, 32, NULL, replyBuffer, replySize, v_ulTimeout);

		if (pIcmpEchoReply->Status == 0)	// δ��ʱ
		{
			ret++;
		}
	}

	//�ͷŻ��������رվ��
	delete[] replyBuffer;
	delete[] sendBuffer;
	pIcmpCloseHandle(hIcmpFile);

	return ret;
}

BOOL CMyNetwork::SimpleCheckNet()
{
	BOOL bNetState = FALSE;
	DWORD dwFlags;	

	if (IsNetworkAlive(&dwFlags))
	{
		bNetState = TRUE;
	}
	else
	{
		bNetState = FALSE;
	}

	return bNetState;
}

// OpenInternetUrl Sub Method 
BOOL CMyNetwork::OpenInternetUrl(HINTERNET hInternet, LPCTSTR lpszUrl)
{
	BOOL bRet = TRUE;
	HINTERNET hConnectOpenUrl = InternetOpenUrl(hInternet, lpszUrl, NULL, 0, INTERNET_FLAG_RELOAD, 0);
	if (hConnectOpenUrl == NULL)
	{
		DWORD dwRet = GetLastError();
		bRet = FALSE;
	}
	else
	{
		// Close Internet Handle 
		InternetCloseHandle(hConnectOpenUrl);
	}
	
	return bRet;
}

BOOL CMyNetwork::OnConnectNet()
{
	ASSERT(!m_strDesAdress.IsEmpty());

	BOOL bRet = TRUE;

	return bRet;

	CString strUrl = m_strDesAdress;
	CString strPre = _T("http://");
	int nLen = strPre.GetLength();
	if (strUrl.GetLength()>nLen)
	{
		if (0 != strUrl.Left(nLen).CompareNoCase(strPre))
		{
			strUrl = strPre + strUrl;
		}

		HINTERNET hInternetOpen = InternetOpen(USER_AGENT, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
		if (hInternetOpen == NULL)
		{
			DWORD dwRet = GetLastError();
			bRet = FALSE;
			goto END_OPEN;
		}

		BOOL bOpen = OpenInternetUrl(hInternetOpen, strUrl);
		if (!bOpen)
		{
			bRet = FALSE;
		}

END_OPEN:
		// Close HINTERNET
		if (hInternetOpen)
		{
			InternetCloseHandle(hInternetOpen);
		}
	}
	else
	{
		bRet = FALSE;
	}
	
	return bRet;
}