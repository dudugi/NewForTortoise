#pragma once

/************************************************************************
 * @Date：2017/01/08 星期日
 * @Author：zhangtao
 * @brief: 判断是否与固定IP连通
 ************************************************************************/

#include <IPHlpApi.h>
#pragma comment(lib, "iphlpapi.lib")

#include <Sensapi.h>
#pragma comment(lib, "Sensapi.lib")

#include <WinInet.h>
#pragma comment(lib,"wininet.lib")

#include <memory>
using namespace std;


// User Agent
#define USER_AGENT _T("SP_InetStatus/1.0")

class CMyNetwork
{
public:
	CMyNetwork();
	~CMyNetwork();

private:
	HINSTANCE hIcmp;
	typedef HANDLE (WINAPI *PIcmpCreateFile)(VOID);
	typedef DWORD  (WINAPI *PIcmpSendEcho)(HANDLE, IPAddr, LPVOID, WORD, PIP_OPTION_INFORMATION, LPVOID, DWORD, DWORD);
	typedef BOOL   (WINAPI *PIcmpCloseHandle)(HANDLE);
	PIcmpCreateFile		pIcmpCreateFile;
	PIcmpSendEcho		pIcmpSendEcho;
	PIcmpCloseHandle	pIcmpCloseHandle;

	//char m_szDesAdress[MAX_PATH];
	CString m_strDesAdress;

	static std::shared_ptr<CMyNetwork> sm_inst;

	BOOL OpenInternetUrl(HINTERNET hInternet, LPCTSTR lpszUrl);

public:
	static CMyNetwork* Instance();//获取（指针）实例
	void SetDesAdress(CString strUrl);
	BOOL PingNet();

	/*******************************************************************
	 * @brief : ping某个地址或者Ip，返回结果
	 * @date : 2017/01/08 16:26
	 * @param : v_pszDesAddress-目标域名或者IP
	 * @param : v_usTimes-需要ping的次数
	 * @param : v_ulTimeout-超时时间，单位毫秒
	 * @example : 
	 * @return : -1-发生异常,其他大于等于0的值表示未超时的次数
	 *******************************************************************/
	int PingNet(const char *v_pszDesAdress, USHORT v_usTimes=5, ULONG v_ulTimeout=5000);

	//检测网络状态
	BOOL SimpleCheckNet();

	/*******************************************************************
	 * @brief :检测是否与目标地址连通
	 * @date : 2018/02/28 16:22
	 * @param : strUrl 域名或者IP地址
	 * @example : 
	 * @return : TRUE连通成功
	 *******************************************************************/
	BOOL OnConnectNet();
};

