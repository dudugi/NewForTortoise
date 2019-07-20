#pragma once

/************************************************************************
 * @Date��2017/01/08 ������
 * @Author��zhangtao
 * @brief: �ж��Ƿ���̶�IP��ͨ
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
	static CMyNetwork* Instance();//��ȡ��ָ�룩ʵ��
	void SetDesAdress(CString strUrl);
	BOOL PingNet();

	/*******************************************************************
	 * @brief : pingĳ����ַ����Ip�����ؽ��
	 * @date : 2017/01/08 16:26
	 * @param : v_pszDesAddress-Ŀ����������IP
	 * @param : v_usTimes-��Ҫping�Ĵ���
	 * @param : v_ulTimeout-��ʱʱ�䣬��λ����
	 * @example : 
	 * @return : -1-�����쳣,�������ڵ���0��ֵ��ʾδ��ʱ�Ĵ���
	 *******************************************************************/
	int PingNet(const char *v_pszDesAdress, USHORT v_usTimes=5, ULONG v_ulTimeout=5000);

	//�������״̬
	BOOL SimpleCheckNet();

	/*******************************************************************
	 * @brief :����Ƿ���Ŀ���ַ��ͨ
	 * @date : 2018/02/28 16:22
	 * @param : strUrl ��������IP��ַ
	 * @example : 
	 * @return : TRUE��ͨ�ɹ�
	 *******************************************************************/
	BOOL OnConnectNet();
};

