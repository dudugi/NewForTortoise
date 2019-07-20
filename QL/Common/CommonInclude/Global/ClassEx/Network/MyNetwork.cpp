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

	//memset(m_szDesAdress,0,sizeof(m_szDesAdress)/sizeof(char));//清空char数组
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
	memset(szDesAdress,0,sizeof(szDesAdress)/sizeof(char));//清空char数组

#ifdef _UNICODE
	USES_CONVERSION;
	char *pszDesAdress = T2A(m_strDesAdress);
	strcpy(szDesAdress, pszDesAdress);
#else
	_tcscpy(szDesAdress, (LPCTSTR)m_strDesAdress);
#endif

	ASSERT(strlen(szDesAdress) != 0);//判断char数组为空：if(m_szDesAdress[0]=='\0') 或 strlen(m_szDesAdress)==0

	//ping5次，如果全部超时说明与服务端断开
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

	// 当传递的参数为域名时，解析该域名的IP
	ulDesIP = inet_addr(v_pszDesAdress);//a.b.c.d
	//域名
	if(ulDesIP == INADDR_NONE)
	{
		//2017/04/11 zhangt 地址是域名adc.net.com
		//#include <winsock2.h>
		//#pragma comment(lib, "ws2_32.lib")
		WSADATA wsaData;
		WSAStartup(MAKEWORD(2, 2), &wsaData);//初始化
		// 解析传入域名
		PHOSTENT pHostent = gethostbyname(v_pszDesAdress);
		if (pHostent == NULL)
		{
			TRACE(_T("%d is the error."), WSAGetLastError());  
			return -1;
		}
		ulDesIP = *(DWORD *)pHostent->h_addr;
		WSACleanup();//释放资源
	}

	// 申请发送缓冲区
	void *sendBuffer = new char[32];
	if (sendBuffer == NULL)
	{
		return -1;
	}

	// 申请接收缓冲区
	unsigned long replySize = sizeof(ICMP_ECHO_REPLY) + 32;
	void *replyBuffer = new char[replySize];
	if (replyBuffer == NULL)
	{
		delete [] sendBuffer;
		sendBuffer = NULL;
		return -1;
	}
	PICMP_ECHO_REPLY pIcmpEchoReply = (PICMP_ECHO_REPLY)replyBuffer;

	// 获取ICMP echo所需句柄
	HANDLE hIcmpFile = pIcmpCreateFile();
	if (hIcmpFile == INVALID_HANDLE_VALUE)
	{
		delete [] sendBuffer;
		sendBuffer = NULL;
		delete [] replyBuffer;
		replyBuffer = NULL;
		return -1;
	}

	// 调用IcmpSendEcho，获取Ping值
	for (int i=0; i<v_usTimes; i++)
	{
		pIcmpSendEcho(hIcmpFile, ulDesIP, sendBuffer, 32, NULL, replyBuffer, replySize, v_ulTimeout);

		if (pIcmpEchoReply->Status == 0)	// 未超时
		{
			ret++;
		}
	}

	//释放缓冲区，关闭句柄
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