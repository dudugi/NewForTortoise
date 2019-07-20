
// LogReport.cpp : 定义应用程序的类行为。
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


// CLogReportApp 构造

CLogReportApp::CLogReportApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CLogReportApp 对象

CLogReportApp theApp;
CCommonAPI QLCOMAPI;


// CLogReportApp 初始化

BOOL CLogReportApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();
   AfxInitRichEdit();
   CLogCommandLineInfo cmdInfo;
   ParseCommandLine(cmdInfo);

   //CustomPraseCommandLine(cmdInfo);


   // nothing 可以继续   
   //不是nothing 且不是只有一个实例 则返回

   if(!OnlyOneInstance(cmdInfo))
   {
      return FALSE;
   }

   if (cmdInfo.m_nLogShellCommand != CLogCommandLineInfo::LogNothing )
   {
      return FALSE;
   }

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("LogReport"));
   

	CLogReportDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}

BOOL CLogReportApp::OnlyOneInstance(const CLogCommandLineInfo & cmdInfo)
{
   BOOL bRet = TRUE;

   m_hSem = CreateSemaphore(NULL, 1, 1, SOFT_TAG);
   CString strPrePath = _T("");

   // 信号量存在，则程序已有一个实例运行
   if (GetLastError() == ERROR_ALREADY_EXISTS)
   {
      //bRet = FALSE;
      // 寻找先前实例的窗口
      HWND hWndPrevious = ::GetWindow(::GetDesktopWindow(), GW_CHILD);
      while (::IsWindow(hWndPrevious))
      {
         // 检查窗口是否有预设的标记
         if (::GetProp(hWndPrevious, SOFT_TAG))
         {
            GetAppPathFromHwnd(hWndPrevious,strPrePath);
            //if (strPrePath == m_strCurAppPath)//路径完全一样的App
            {
               bRet = FALSE;

               {
                  //主窗口已最小化，则恢复其大小
                  /*if (IsIconic(hWndPrevious))
                  {
                     ShowWindow(hWndPrevious, SW_SHOW);
                  }*/

                  //将主窗激活
                  /*SetForegroundWindow(hWndPrevious);
                  //将主窗的对话框激活
                  SetForegroundWindow(GetLastActivePopup(hWndPrevious));*/

                  //给之前的窗口发送对应的数据
                  char szCallInfo[MAX_PATH] = {0};
                  QLCOMAPI.WCharToMByte(cmdInfo.m_strLog,szCallInfo,sizeof(szCallInfo)/sizeof(szCallInfo[0]));

                  COPYDATASTRUCT cpd; // 给COPYDATASTRUCT结构赋值
                  cpd.dwData = cmdInfo.m_nLogShellCommand;
                  cpd.cbData =  MAX_PATH;
                  cpd.lpData = (void *)szCallInfo;

                  ::SendMessage(hWndPrevious,WM_COPYDATA,NULL,(LPARAM)&cpd); // 发送
               }

               //退出本实例
               break;
            }	
         }
         // 继续寻找下一个窗口
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

      //全部的命令行
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

