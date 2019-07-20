
// LogReport.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "LogReport.h"
#include "LogReportDlg.h"
#include "LogCommandLineInfo.h"


#include <Psapi.h>
#include "CommonAPI.h"
#pragma comment( lib, "PSAPI.LIB" )

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLogReportApp

BEGIN_MESSAGE_MAP(CLogReportApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CLogReportApp ����

CLogReportApp::CLogReportApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CLogReportApp ����

CLogReportApp theApp;
CCommonAPI QLCOMAPI;


// CLogReportApp ��ʼ��

BOOL CLogReportApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();
   AfxInitRichEdit();
   CLogCommandLineInfo cmdInfo;
   ParseCommandLine(cmdInfo);

   //CustomPraseCommandLine(cmdInfo);


   // nothing ���Լ���   
   //����nothing �Ҳ���ֻ��һ��ʵ�� �򷵻�

   if(!OnlyOneInstance(cmdInfo))
   {
      return FALSE;
   }

   if (cmdInfo.m_nLogShellCommand != CLogCommandLineInfo::LogNothing )
   {
      return FALSE;
   }

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("LogReport"));
   

	CLogReportDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

BOOL CLogReportApp::OnlyOneInstance(const CLogCommandLineInfo & cmdInfo)
{
   BOOL bRet = TRUE;

   m_hSem = CreateSemaphore(NULL, 1, 1, SOFT_TAG);
   CString strPrePath = _T("");

   // �ź������ڣ����������һ��ʵ������
   if (GetLastError() == ERROR_ALREADY_EXISTS)
   {
      //bRet = FALSE;
      // Ѱ����ǰʵ���Ĵ���
      HWND hWndPrevious = ::GetWindow(::GetDesktopWindow(), GW_CHILD);
      while (::IsWindow(hWndPrevious))
      {
         // ��鴰���Ƿ���Ԥ��ı��
         if (::GetProp(hWndPrevious, SOFT_TAG))
         {
            GetAppPathFromHwnd(hWndPrevious,strPrePath);
            //if (strPrePath == m_strCurAppPath)//·����ȫһ����App
            {
               bRet = FALSE;

               {
                  //����������С������ָ����С
                  /*if (IsIconic(hWndPrevious))
                  {
                     ShowWindow(hWndPrevious, SW_SHOW);
                  }*/

                  //����������
                  /*SetForegroundWindow(hWndPrevious);
                  //�������ĶԻ��򼤻�
                  SetForegroundWindow(GetLastActivePopup(hWndPrevious));*/

                  //��֮ǰ�Ĵ��ڷ��Ͷ�Ӧ������
                  char szCallInfo[MAX_PATH] = {0};
                  QLCOMAPI.WCharToMByte(cmdInfo.m_strLog,szCallInfo,sizeof(szCallInfo)/sizeof(szCallInfo[0]));

                  COPYDATASTRUCT cpd; // ��COPYDATASTRUCT�ṹ��ֵ
                  cpd.dwData = cmdInfo.m_nLogShellCommand;
                  cpd.cbData =  MAX_PATH;
                  cpd.lpData = (void *)szCallInfo;

                  ::SendMessage(hWndPrevious,WM_COPYDATA,NULL,(LPARAM)&cpd); // ����
               }

               //�˳���ʵ��
               break;
            }	
         }
         // ����Ѱ����һ������
         hWndPrevious = ::GetWindow(hWndPrevious, GW_HWNDNEXT);
      }
   }

   return bRet;
}

int CLogReportApp::GetAppPathFromHwnd(HWND hWnd, CString& AppPath)
{
   TCHAR szPath[MAX_PATH]; 
   int ErrorCode = 0; 
   DWORD idProcess; 
   GetWindowThreadProcessId(hWnd, &idProcess); 
   HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, idProcess); 
   if(NULL != hProcess) 
   { 
      HMODULE hMod; 
      DWORD cbNeeded; 
      if(EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded)) 
      { 
         DWORD dw = GetModuleFileNameEx(hProcess, hMod, szPath, MAX_PATH ); 
         if(dw > 0) 
         { 
            //printf("szPath:   %S   \n",   szPath); 
            AppPath = szPath; 
         } 
         else 
         { 
            //printf("GetLastError:%d   \n",   GetLastError()); 
            ErrorCode = GetLastError(); 
         } 
      } 
      CloseHandle(hProcess); 
   } 

   return ErrorCode; 
}

void CLogReportApp::CustomPraseCommandLine(CLogCommandLineInfo & cmdInfo)
{
   CString strName = _T("");
   if ('\0' != m_lpCmdLine[0])
   {
      strName = m_lpCmdLine;

      //ȫ����������
      //\n = LogNew
      BOOL bFlag = FALSE;
      int nLength = strName.GetLength();
      CString strCache = _T("");
      for (int nIndex = 0;nIndex < nLength;++nIndex)
      {
         char cAt = strName.GetAt(nIndex);
         if (cAt == '-' || cAt == '/')
         {
            bFlag = TRUE;
         }

         if (cAt == 'n')
         {
            cmdInfo.m_nLogShellCommand = CLogCommandLineInfo::LogNew;
         }

         if (bFlag)
            bFlag = FALSE;

         if (CLogCommandLineInfo::LogNew == cmdInfo.m_nLogShellCommand && !bFlag)
         {
            cmdInfo.m_strLog = strName.Right(nLength - nIndex-1);
         }
      }
   }
   else
   {
      cmdInfo.m_nLogShellCommand = CLogCommandLineInfo::LogNothing;
   }
}

