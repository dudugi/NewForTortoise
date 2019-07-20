// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// (“Fluent UI”)。该示例仅供参考，
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问  
// http://msdn.microsoft.com/officeui。
//
// 版权所有(C) Microsoft Corporation
// 保留所有权利。

// QLSvrMgn.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "QLSvrMgn.h"
#include "MainFrm.h"

#include "QLSvrMgnDoc.h"
#include "QLSvrMgnView.h"
#include <winbase.h>
#include "MyADOConnEx.h"
#include "MyCtrlEx/Desktop/CMFCDesktopAlertMid.h"
#include "DlgDesktop.h"
#include "DlgPane1Item1.h"

#include <stdio.h> 
#include <io.h> 
#include <fcntl.h> 
#include <iostream>
#include <stdlib.h>
#include <Psapi.h>

#pragma comment(lib, "Psapi.lib ")
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

UINT ThreadStartLoading(LPVOID lpParam)
{

	HWND hWnd = theApp.m_dlgLoading.GetSafeHwnd();
	if ( ::IsWindow(hWnd))
	{
		theApp.m_dlgLoading.OnCancel();
	}
	else
	{
		//BOOL bContinueModal = theApp.m_dlgLoading.ContinueModal();
		if (theApp.m_dlgLoading.m_bInitModal/*bContinueModal || (theApp.m_dlgLoading.m_nFlags & (WF_MODALLOOP|WF_CONTINUEMODAL))*/)
			theApp.m_dlgLoading.OnCancel();
		else
			theApp.m_dlgLoading.DoModal();
	}


	return 0;
}

// CQLSvrMgnApp

BEGIN_MESSAGE_MAP(CQLSvrMgnApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CQLSvrMgnApp::OnAppAbout)
	// 基于文件的标准文档命令
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
END_MESSAGE_MAP()


// CQLSvrMgnApp 构造

CQLSvrMgnApp::CQLSvrMgnApp()
{
	m_bHiColorIcons = TRUE;

	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// 如果应用程序是利用公共语言运行时支持(/clr)构建的，则:
	//     1) 必须有此附加设置，“重新启动管理器”支持才能正常工作。
	//     2) 在您的项目中，您必须按照生成顺序向 System.Windows.Forms 添加引用。
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: 将以下应用程序 ID 字符串替换为唯一的 ID 字符串；建议的字符串格式
	//为 CompanyName.ProductName.SubProduct.VersionInformation

   //任务ID初始化
   m_nTaskID = 1;
   m_bTaskMark = FALSE;
   m_bLastTaskMark = FALSE;
   m_nWorkType = -1;
   m_MutexMark = FALSE;
   m_bAutoStart = FALSE;
   m_bStartHide = FALSE;
	SetAppID(_T("QLSvrMgn.AppID.NoVersion"));

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}

// 唯一的一个 CQLSvrMgnApp 对象

CQLSvrMgnApp theApp;
CMySerial MySerial;
// CQLSvrMgnApp 初始化


BOOL CQLSvrMgnApp::InitInstance()
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

	CWinAppEx::InitInstance();


	// 初始化 OLE 库
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// 使用 RichEdit 控件需要  AfxInitRichEdit2()	
	AfxInitRichEdit2();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("QLSvrMgn"));
	LoadStdProfileSettings(4);  // 加载标准 INI 文件选项(包括 MRU)

	//CleanState();//清空注册表

	InitContextMenuManager();
	InitShellManager();

	InitKeyboardManager();

	InitTooltipManager();


	GetCurrentFilePath();


	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// 注册应用程序的文档模板。文档模板
	// 将用作文档、框架窗口和视图之间的连接
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CQLSvrMgnDoc),
		RUNTIME_CLASS(CMainFrame),       // 主 SDI 框架窗口
		RUNTIME_CLASS(CQLSvrMgnView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// 分析标准 shell 命令、DDE、打开文件操作的命令行
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
   if (!OnlyInstance())//只允许只有一个服务实例在运行
   {
      return FALSE;
   }

	m_nCmdShow = SW_SHOW/*SW_SHOWMAXIMIZED*/;//最大化

	// 调度在命令行中指定的命令。如果
	// 用 /RegServer、/Register、/Unregserver 或 /Unregister 启动应用程序，则返回 FALSE。
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// 唯一的一个窗口已初始化，因此显示它并对其进行更新

   //检验知否自启动最小化,自启动
   CString strStartHide,strAutoStart;
   theApp.OnReadIni(_T("ConfigureInfo"), _T("AppAutoStartHide"), strStartHide,INI_SQLSVR);
   theApp.OnReadIni(_T("ConfigureInfo"), _T("AppAutoStart"), strAutoStart,INI_SQLSVR);
   theApp.m_bStartHide = _ttoi(strStartHide);
   theApp.m_bAutoStart = _ttoi(strAutoStart);
   if (_ttoi(strAutoStart) && _ttoi(strStartHide))
   {
      m_pMainWnd->ShowWindow(SW_HIDE);
   }
   else
   {
      m_pMainWnd->ShowWindow(SW_SHOW);
   }
	m_pMainWnd->UpdateWindow();
	// 仅当具有后缀时才调用 DragAcceptFiles
	//  在 SDI 应用程序中，这应在 ProcessShellCommand 之后发生

   //任务监控初始化
   InitTaskInfo();
   InitMontiorThread();
   //ContrlCreate();
   //ADoConn初始化
   m_pADOConn = new CMyADOConnEx(TRUE);
   m_pADOConn->SetExceptionHwnd(AfxGetMainWnd()->GetSafeHwnd());
   //任务表数据初始化
   
	return TRUE;
}

int CQLSvrMgnApp::ExitInstance()
{
	//TODO: 处理可能已添加的附加资源
	AfxOleTerm(FALSE);

   //备份pADOConn释放
   if(nullptr != m_pADOConn)
   {
      delete m_pADOConn;
      m_pADOConn = nullptr;
   }

   //线程资源释放
   if (m_pMonitorThread != NULL)
   {
      ::PostThreadMessage(m_pMonitorThread->m_nThreadID,WM_QUIT,0,0);
      delete m_pMonitorThread;
   }
   if (m_pWorkThread != NULL)
   {
      ::PostThreadMessage(m_pWorkThread->m_nThreadID,WM_QUIT,0,0);
       delete m_pWorkThread;
   }
   
   //自启动配置文件填写   add anjie by 2019/1/7
   CString strAutoStart,strStartHide;
   strAutoStart.Format(_T("%d"),theApp.m_bAutoStart);
   strStartHide.Format(_T("%d"),theApp.m_bStartHide);
   //修改注册表启动项数据
   if (theApp.m_bAutoStart)
   {
      strStartHide.Format(_T("%d"),theApp.m_bStartHide);

      CRegistry Regist;
      CString strKeyName,strKeyValue;
      strKeyName = _T("QLSvrMgn");
      CString strPath = _T("Software\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Run");//HKEY_LOCAL_MACHINE\SOFTWARE\Wow6432Node\Microsoft\Windows\CurrentVersion\Run。实现的效果和admin是一样的
      strKeyValue = theApp.m_strAppPath+_T("\\QLSvrMgn.exe");

loop :
	  if(Regist.OpenKey(CRegistry::localMachine,strPath))
      {
         if(!Regist.SetValue(strKeyName,strKeyValue))
         {
         }
         Regist.CloseKey();
      }
	  else
	  {
		  goto loop;
	  }
   }
   else
   {
      strStartHide.Format(_T("%d"),FALSE);
      CRegistry Regist;
      CString strKeyName,strKeyValue;
      strKeyName = _T("QLSvrMgn");
      CString strPath = _T("Software\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Run");//HKEY_LOCAL_MACHINE\SOFTWARE\Wow6432Node\Microsoft\Windows\CurrentVersion\Run。实现的效果和admin是一样的
      strKeyValue = theApp.m_strAppPath+_T("\\QLSvrMgn.exe");
      if(Regist.OpenKey(CRegistry::localMachine,strPath))
      {
         if(!Regist.DeleteValue(strKeyName))
         {
         }
         Regist.CloseKey();
      }
   }
   //写配置文件，避免注册表修改失败，数据丢失
   theApp.OnWriteIni(_T("ConfigureInfo"), _T("AppAutoStart"), strAutoStart,INI_SQLSVR);
   theApp.OnWriteIni(_T("ConfigureInfo"), _T("AppAutoStartHide"), strStartHide,INI_SQLSVR);

	return CWinAppEx::ExitInstance();
}

// CQLSvrMgnApp 消息处理程序


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
//	virtual BOOL OnInitDialog();
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// 用于运行对话框的应用程序命令
void CQLSvrMgnApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CQLSvrMgnApp 自定义加载/保存方法

void CQLSvrMgnApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CQLSvrMgnApp::LoadCustomState()
{
}

void CQLSvrMgnApp::SaveCustomState()
{
}

// CQLSvrMgnApp 消息处理程序

void CQLSvrMgnApp::OnReadIni(CString strSection,CString strKey,CString &strKeyValue,int nType)
{
   CString strPathFile =_T("");
   switch(nType)
   {
   case INI_SQLSVR:
      {
         strPathFile = m_strAppPath+_T("\\SQLSVR.ini");
         break;
      }
   case INI_TASKINFO:
      {
         strPathFile = m_strAppPath+_T("\\TASKINFO.ini");
         break;
      }
   case INI_TASKVTY:
      {
         strPathFile = m_strAppPath+_T("\\TASKVTY.ini");
      }
   default:
      break;
   }
	TCHAR temp[MAX_PATH];
	GetPrivateProfileString(strSection,strKey,_T(""),temp,MAX_PATH,strPathFile);
	strKeyValue.Format(_T("%s"),temp);
	strKeyValue.Trim();

}

void CQLSvrMgnApp::OnWriteIni(CString strSection,CString strKey,CString strKeyValue,int nType)
{
	CString strPathFile = _T("");
  
	strKeyValue.Trim();
   switch(nType)
   {
   case INI_SQLSVR:
      {
         strPathFile = m_strAppPath+_T("\\SQLSVR.ini");
         break;
      }
      break;
   case INI_TASKINFO:
      {
          strPathFile = m_strAppPath+_T("\\TASKINFO.ini");//任务表
          break;
      }
      break;
   case INI_TASKVTY:
      {
         strPathFile = m_strAppPath+_T("\\TASKVTY.ini");//任务表
         break;
      }
      break;
   default:
      break;
   }
   WritePrivateProfileString(strSection,strKey,strKeyValue,strPathFile);
} 

void CQLSvrMgnApp::GetCurrentFilePath()
{
	TCHAR temp[MAX_PATH];
	GetModuleFileName(NULL,temp,MAX_PATH);
	m_strAppPath.Format(_T("%s"),temp);
	int pos = m_strAppPath.ReverseFind('\\');
	m_strAppPath = m_strAppPath.Left(pos);
	
}

BOOL CQLSvrMgnApp::GetFileNameByRoot(__out CStringList *pListPath,__in CString strRootPath,__in DWORD nFlag/*=0x0001*/)
{
	BOOL bRet = TRUE;
	strRootPath.Trim();
	ASSERT(!strRootPath.IsEmpty());
	pListPath->RemoveAll();

	if (strRootPath.IsEmpty() || !PathFileExists(strRootPath))
	{
		bRet = FALSE;
	}
	else
	{
		CFileFind objFind;
		CString strFullPath = strRootPath + _T("\\*.*");	//所有文件都列出
		if(objFind.FindFile(strFullPath, 0))	//开始检索文件
		{
			BOOL bFlag = TRUE;
			while(bFlag)
			{
				bFlag = objFind.FindNextFile();	//枚举一个文件
				if(objFind.IsDots())	//如果是. 或 .. 做下一个
					continue;

				if(objFind.IsDirectory())
				{
					if (0x0002 == (nFlag&0x0002))
					{
						pListPath->AddTail(objFind.GetFilePath());
					}

					if (0x0004 == (nFlag&0x0004))
					{
						GetFileNameByRoot(pListPath,objFind.GetFilePath(),nFlag);
					}

					if (0x0008 == (nFlag&0x0008))
					{
						GetFileNameByRoot(pListPath,objFind.GetFilePath(),nFlag);
					}
				}
				else
				{
					if (0x0001 == (nFlag&0x0001))
					{
						pListPath->AddTail(objFind.GetFilePath());
					}
				}
			}

			objFind.Close();
		}
	}


	return bRet;
}

void CQLSvrMgnApp::ShowLoading()
{
	HANDLE hThrLoading = ::CreateThread(NULL,0,
		(LPTHREAD_START_ROUTINE)ThreadStartLoading,0,0,NULL);

	if (hThrLoading == NULL)		
	{		
		::MessageBox(NULL,_T("启动获取线程（加载对话框）失败！"),_T("温馨提示"),MB_ICONERROR);	
	}
}

void CQLSvrMgnApp::CloseLoading()
{
	if (::IsWindow(m_dlgLoading.GetSafeHwnd()))
	{
		m_dlgLoading.OnCancel();
		//m_dlgLoading.SendMessage(WM_CLOSE,0,0);
	}
}

void CQLSvrMgnApp::OnShowDesktopAlert(
	CString strTip,
	COLORREF clrTip/*=RGB(255,0,0)*/,
	int nDelayTime/*=1*/,
	CWnd *pWndParent/*=NULL*/,
	CPoint ptPos/*=(-1,-1)*/,
	CString strTitle/*=_T("")*/,
	WPARAM wParam/*=0*/,
	LPARAM lParam/*=0*/
	)
{
	if (pWndParent == NULL) pWndParent = AfxGetMainWnd();
	BOOL bCusTile = FALSE;
	if (strTitle.IsEmpty())
	{
		bCusTile = FALSE;
		strTitle =  _T("温馨提示：");
	}
	else
	{
		bCusTile = TRUE;
	}

	CMFCDesktopAlertMid* pPopup = new CMFCDesktopAlertMid;
	pPopup->SetAnimationType (CMFCPopupMenu::NO_ANIMATION);
	pPopup->SetAnimationSpeed (10);
	pPopup->SetTransparency (230);//0-255
	pPopup->SetSmallCaption (!bCusTile);
	pPopup->SetAutoCloseTime(nDelayTime * 1000);//1000ms

	HICON hIcon = (HICON) ::LoadImage (::AfxGetResourceHandle (), 
		MAKEINTRESOURCE (IDR_MAINFRAME),
		IMAGE_ICON, ::GetSystemMetrics (SM_CXSMICON), ::GetSystemMetrics (SM_CYSMICON), 0);

	CPoint ptShowPos = ptPos;
	if (ptPos == CPoint(0,0))
	{
		CRect rc;
		AfxGetMainWnd()->GetClientRect(&rc);
		AfxGetMainWnd()->ClientToScreen(&rc);
		ptShowPos.x = rc.right/2-50;
		ptShowPos.y = rc.top;
	}

	pPopup->Create(pWndParent, IDD_DLG_DESKTOP, NULL, 
		ptShowPos, RUNTIME_CLASS(CDlgDesktop));
	if(::IsWindow(pPopup->GetSafeHwnd()))
	{
		CDlgDesktop *pDlgDesktop = (CDlgDesktop *)pPopup->GetRuntimeDlg();
		if (pDlgDesktop)
		{
			pDlgDesktop->m_strText = strTip;
			pDlgDesktop->m_clrText = clrTip;
			pDlgDesktop->wParam = wParam;
			pDlgDesktop->lParam = lParam;
			pDlgDesktop->pOwerWnd = AfxGetMainWnd();
		}

		pPopup->SetIcon(hIcon, FALSE);
		pPopup->SetWindowText(strTitle);
	}
}

BOOL CQLSvrMgnApp::MakeDirByCheck(CString strDir)
{
	BOOL bRet = TRUE;

	strDir.Trim();
	if (strDir.IsEmpty())
	{
		bRet = FALSE;
	}
	else
	{
		int nRet = SHCreateDirectoryEx(NULL,strDir,NULL);
		switch(nRet)
		{
		default:
		case ERROR_SUCCESS://创建成功
			bRet = TRUE;
			break;
		case ERROR_BAD_PATHNAME://pszPath 参数为相对路径
			bRet = FALSE;
			break;
		case ERROR_FILENAME_EXCED_RANGE://pszPath 参数太长
			bRet = FALSE;
			break;
		case ERROR_PATH_NOT_FOUND://创建时系统找不到指定路径，可能路径中包含非法入口。(如Z:\,但不存在Z盘。)
			bRet = FALSE;
			break;
		case ERROR_FILE_EXISTS://文件已经存在
			bRet = TRUE;
			break;
		case ERROR_ALREADY_EXISTS://路径已经存在
			bRet = TRUE;
			break;
		case ERROR_CANCELLED://用户取消了操作
			bRet = FALSE;
			break;	
		}
	}

	return bRet;
}

BOOL CQLSvrMgnApp::FilterPathToFileName(CString &strFilePath,CString strNameEx)
{
	BOOL bRet = FALSE;

	int nPos = strFilePath.ReverseFind('\\');
	int nLength = strFilePath.GetLength();
	nPos = nLength - nPos;
	CString strTemp = strFilePath.Right(nPos-1);


	nPos = strFilePath.ReverseFind('.');
	nPos = nLength - nPos;
	strFilePath = strFilePath.Right(nPos-1);
	if(0 == strFilePath.CompareNoCase(strNameEx))
	{
		bRet = TRUE;
		strFilePath = strTemp;
	}

	return bRet;
}

BOOL CQLSvrMgnApp::GetStateConnectDB(CADOConn *pADOConn)
{
   BOOL bRet = FALSE;
   ASSERT(pADOConn);

   if (pADOConn)
   {
      CString strSQL = _T("");
      strSQL.Format(_T("select GETDATE()"));
      pADOConn->GetRecordSet(strSQL);
      if (pADOConn->adoEOF())
      {
         bRet = FALSE;
      }
      else
      {
         bRet = TRUE;
      }
   }
   
   return bRet;
}

BOOL CQLSvrMgnApp::GetStateConnectDB(BOOL bCreateDB/*=FALSE*/)
{
   BOOL bRet = FALSE;

   CMyADOConnEx MyADOConnEx(!bCreateDB);
   CString strSQL = _T("");
   strSQL.Format(_T("select GETDATE()"));
   MyADOConnEx.GetRecordSet(strSQL);
   if (MyADOConnEx.adoEOF())
   {
      bRet = FALSE;
   }
   else
   {
      bRet = TRUE;
   }

   return bRet;
}

void CQLSvrMgnApp::InitMontiorThread()
{
   ASSERT(!m_pMonitorThread);
   m_pMonitorThread = AfxBeginThread(DealMontior,NULL,THREAD_PRIORITY_NORMAL,0,0,NULL);
   m_pMonitorThread->m_bAutoDelete = TRUE;
   if (m_pMonitorThread)
   {
      printf("%d:%s监控线程创建成功",__LINE__,__FILE__);
   }
}

UINT CQLSvrMgnApp::DealMontior(LPVOID pParam)
{
   printf("%d:%s::监控线程启动!\n",__LINE__,__FILE__);
   while(1)
   {
      if (theApp.m_TaskList.GetCount()>0)
      {
         //结束任务 其他任务时间调整
         if (theApp.DBExTask.m_nState == 3)
         {
            PTLOG("任务终止");
            theApp.m_bTaskMark = FALSE;
            CTime tCurTime = CTime::GetCurrentTime();
            CDBTaskInfoList DBTasList;
            CTime tDayEndTime(theApp.DBExTask.m_tStdStartTime.GetYear(),theApp.DBExTask.m_tStdStartTime.GetMonth(),theApp.DBExTask.m_tStdStartTime.GetDay(),23,59,59);
            for(int i = 0;i<theApp.m_TaskList.GetCount();i++)
            {
               CDBTaskInfo *DBTask = (CDBTaskInfo*)theApp.m_TaskList.GetAt(theApp.m_TaskList.FindIndex(i));
               if(DBTask)
               {

                  //当天任务时间更新（任务超过标准执行当天）
                  if (tCurTime> tDayEndTime && tDayEndTime.GetYear() == DBTask->m_tStdStartTime.GetYear()
                     &&tDayEndTime.GetMonth() == DBTask->m_tStdStartTime.GetMonth()
                     &&tDayEndTime.GetDay() == DBTask->m_tStdStartTime.GetDay()
                     )
                  {
                     //时间周期更新
                     if (!DBTask->m_strCyc.IsEmpty())
                     {
                        DBTask->m_strCyc.Right(DBTask->m_strCyc.GetLength()-1);
                        int day = _ttoi(DBTask->m_strCyc.Right(DBTask->m_strCyc.GetLength()-1));
                        if (DBTask->m_strCycType == CYCLE_DAY)
                        {
                           LONG64 lSpan = day *DAY;
                           DBTask->m_tStdStartTime+=lSpan;
                           DBTask->m_tNextStartTime = DBTask->m_tStdStartTime;
                        }
                        else if (DBTask->m_strCycType == CYCLE_WEEK)
                        {
                           LONG64 lSpan = day *WEEK;
                           DBTask->m_tStdStartTime+=lSpan;
                           DBTask->m_tNextStartTime += lSpan;
                        }
                        else if (DBTask->m_strCycType == CYCLE_MONTH)
                        {
                           CTime ttTime(DBTask->m_tStdStartTime.GetYear()+1,DBTask->m_tStdStartTime.GetMonth(),DBTask->m_tStdStartTime.GetDay(),DBTask->m_tStdStartTime.GetHour(),DBTask->m_tStdStartTime.GetMinute(),DBTask->m_tStdStartTime.GetSecond());
                           DBTask->m_tStdStartTime = ttTime;
                           DBTask->m_tNextStartTime = ttTime;
                        }
                        DBTasList.addItem(DBTask);
                        printf("%d:%s::任务清理，任务周期时间更新，周期性任务添加成功!\n",__LINE__,__FILE__);
                     }
                     continue;
                  }
                  else if (DBTask->m_tStdStartTime < tCurTime
                     && tDayEndTime.GetYear() == DBTask->m_tStdStartTime.GetYear()
                     &&tDayEndTime.GetMonth() == DBTask->m_tStdStartTime.GetMonth()
                     &&tDayEndTime.GetDay() == DBTask->m_tStdStartTime.GetDay())
                  {
                     DBTask->m_tNextStartTime = tCurTime;
                     DBTask->m_tStdStartTime = tCurTime;
                     DBTasList.addItem(DBTask);
                     break;
                  }
                  else
                  {
                     DBTasList.addItem(DBTask);
                  }

               }
            }
            theApp.m_TaskList.RemoveAll();
            theApp.m_TaskList = DBTasList;
            theApp.DBExTask.ResetData();

         }

         CDBTaskInfo * pDBTaskInfo = (CDBTaskInfo *)theApp.m_TaskList.GetAt(theApp.m_TaskList.FindIndex(0));
         CTime ttCurTime = CTime::GetCurrentTime();
         if (pDBTaskInfo == nullptr)
         {
            continue;
         }
         if (pDBTaskInfo&&(pDBTaskInfo->m_tNextStartTime.GetYear() == ttCurTime.GetYear()
            &&pDBTaskInfo->m_tNextStartTime.GetDay() == ttCurTime.GetDay()
            &&pDBTaskInfo->m_tNextStartTime.GetMonth() == ttCurTime.GetMonth()
            &&pDBTaskInfo->m_tNextStartTime.GetHour() == ttCurTime.GetHour()
            &&pDBTaskInfo->m_tNextStartTime.GetMinute() == ttCurTime.GetMinute())&& (theApp.m_bTaskMark != TRUE))
         {
            printf("%d:%s::执行任务%d!\n",__LINE__,__FILE__,pDBTaskInfo->m_tStartTime);
            PTLOG("执行任务");
            theApp.m_bTaskMark = TRUE;

            CDBTaskInfo *pNewDBTask = new CDBTaskInfo;
            pNewDBTask->Copy(pDBTaskInfo);
            theApp.m_pWorkThread = AfxBeginThread(DealWork,pNewDBTask,THREAD_PRIORITY_NORMAL,0,0,NULL);
            CDBTaskInfo * pDBTask = (CDBTaskInfo*)theApp.m_TaskList.GetAt(theApp.m_TaskList.FindIndex(0));
            if (!pDBTask)
            {
               return 0;
            }
            else
            {
               theApp.DBExTask.Copy(pDBTask);
               theApp.DBExTask.m_nState = 1;//更新执行状态
               theApp.m_pWorkThread->m_bAutoDelete = TRUE;
               theApp.m_TaskList.deleteItem(0);
            }
         }
         else if(pDBTaskInfo->m_tNextStartTime<ttCurTime&&!theApp.m_MutexMark)//解决待机时，线程挂起后启动时，超时任务清理
         {
            //处理延时周期时间修改
            //解决任务重复添加
            CDBTaskInfo *pNewDBTask = new CDBTaskInfo;
            pNewDBTask->Copy(pDBTaskInfo);
            while (TRUE)
            {
               CTime tBCurTime = CTime::GetCurrentTime();
               if (pNewDBTask->m_tNextStartTime>tBCurTime)//解决数据过滤
               {
                  theApp.m_TaskList.deleteItem(0);//内部已释放资源
                  theApp.m_TaskList.addItem(pNewDBTask);
                  break;
               }

               //更改周期时间，进行任务装填
               if (!pNewDBTask->m_strCyc.IsEmpty())
               {
                  pNewDBTask->m_strCyc.Right(pNewDBTask->m_strCyc.GetLength()-1);
                  int day = _ttoi(pNewDBTask->m_strCyc.Right(pNewDBTask->m_strCyc.GetLength()-1));
                  if (pNewDBTask->m_strCycType == CYCLE_DAY)
                  {
                     LONG64 lSpan = day *DAY;
                     pNewDBTask->m_tStdStartTime+=lSpan;
                     pNewDBTask->m_tNextStartTime = pNewDBTask->m_tStdStartTime;
                  }
                  else if (pNewDBTask->m_strCycType == CYCLE_WEEK)
                  {
                     LONG64 lSpan = day *WEEK;
                     pNewDBTask->m_tStdStartTime+=lSpan;
                     pNewDBTask->m_tNextStartTime += lSpan;
                  }
                  else if (pNewDBTask->m_strCycType == CYCLE_MONTH)
                  {
                     CTime ttTime(pNewDBTask->m_tStdStartTime.GetYear()+1,pNewDBTask->m_tStdStartTime.GetMonth(),pNewDBTask->m_tStdStartTime.GetDay(),pNewDBTask->m_tStdStartTime.GetHour(),pNewDBTask->m_tStdStartTime.GetMinute(),pNewDBTask->m_tStdStartTime.GetSecond());
                     pNewDBTask->m_tStdStartTime = ttTime;
                     pNewDBTask->m_tNextStartTime = ttTime;
                  }
                  printf("%d:%s::任务清理，任务周期时间更新，周期性任务添加成功!\n",__LINE__,__FILE__);
               }
            }
         }
      }

	  //定时删除相关任务文件
	  for(int i = 0;i<theApp.m_TaskSuccessList.GetCount();i++)
	  {
		  CDBTaskInfo *DBTask = (CDBTaskInfo*)theApp.m_TaskSuccessList.GetAt(theApp.m_TaskSuccessList.FindIndex(i));
		  CTime tCurTime = CTime::GetCurrentTime();
		  if(DBTask != NULL)
		  {
			  LONG64 lSpan = DBTask->m_nAutoDeleteTime *DAY;
			  if (tCurTime-DBTask->m_tLastExecutionTime > lSpan)
			  {
				  //启动删除线程
				  theApp.m_pAutoDeleteThread = AfxBeginThread(DealAutoDelete,DBTask,THREAD_PRIORITY_NORMAL,0,0,NULL);
			  }
		  }
	  }


      Sleep(1000);
   }
}

UINT CQLSvrMgnApp::DealWork(LPVOID pParam)
{
   //任务处理

	//添加互斥锁
   CSingleLock   sinLock(&theApp.m_Mutex);
   sinLock.Lock();
   CDBTaskInfo * pTaskInfo = (CDBTaskInfo *)pParam;//类型转换
   CDBTaskInfo * pTaskInfoMom = pTaskInfo;
   BOOL bExce = FALSE;
   CTime tTaskExce;
   PTLOG("处理任务中!\n");
   if (pParam)
   {
      if(pTaskInfo->m_strOldPath.IsEmpty() || (!PathFileExists(pTaskInfo->m_strOldPath)))
      {
         //printf("%d:%s::源目录不存在,无法完成备份!\n",__LINE__,__FILE__);
         bExce = TRUE;

      }

      if(pTaskInfo->m_strNewDirPath.IsEmpty() || (!PathFileExists(pTaskInfo->m_strNewDirPath)))
      {
         //printf("%d:%s::目标目录不存在,无法完成备份!\n",__LINE__,__FILE__);
         bExce = TRUE;
      }
      //路径条件判断_end

      PTLOG("检测数据连接");
      if (!theApp.GetStateConnectDB(theApp.m_pADOConn))
      {
         //theApp.m_pADOConn->InitConnect();
         pTaskInfo->m_tLastExecutionTime = NULL;
         PTLOG("无法连接到备份的数据库!\n");
        
      }

      if (!bExce)
      {
         COleDateTime CurrentTime=COleDateTime::GetCurrentTime();
         CString strTime;
         strTime = CurrentTime.Format(_T("%Y_%m_%d_%H时%M分"));
         //strTime.Format(_T("%d_%d_%d_%d时%d分") ,CurrentTime.GetYear(), CurrentTime.GetMonth(),CurrentTime.GetDay(), CurrentTime.GetHour(), CurrentTime.GetMinute()); 
         CString strFullBackUpDirPath = pTaskInfo->m_strNewDirPath + _T("\\")+ pTaskInfo->m_strID+ _T("\\") +_T("FullBackUp") +_T("\\")  +strTime;
         CString strDifferentialDirPath = pTaskInfo->m_strNewDirPath + _T("\\") + pTaskInfo->m_strID+ _T("\\")+_T("XBackUp")+_T("\\")+strTime;
         if(!PathFileExists(strFullBackUpDirPath))
         {
            theApp.MakeDirByCheck(strFullBackUpDirPath);
         }
         if(!PathFileExists(strDifferentialDirPath))
         {
            theApp.MakeDirByCheck(strDifferentialDirPath);
         }
         //开始备份
         theApp.ShowLoading();
         BOOL bFlag = FALSE;
         BOOL bXFlag = FALSE;
         BOOL bXBack = FALSE;

         //检索本地是否存在完整备份 或当前任务为整体备份 进行整体备份

         if(!theApp.FindBackupFile(pTaskInfo->m_strNewDirPath) || pTaskInfo->m_bAutoBackUp)
         {
            PTLOG("整体备份1");
            bFlag = theApp.BackupDatabase(strFullBackUpDirPath + _T("\\backup.bak"),TRUE);//整体备份
            if(bFlag)
            {
               if(strFullBackUpDirPath.IsEmpty() || (!PathFileExists(strFullBackUpDirPath)))
               {
                  theApp.CloseLoading();
				  sinLock.Unlock();
                  return 0;
               }
               PTLOG("数据库完整备份成功!\n");
               BOOL bRet = theApp.m_CDirectroy.CopyDirFileAPI(pTaskInfo->m_strOldPath, strFullBackUpDirPath+_T("\\订单库"));
               if(bRet)
               {
                  pTaskInfo->m_strTaskType = TASK_FILE_BACKUP;
                  PTLOG("完整备份文件成功!\n");
                  theApp.m_strXbackUpFileTime = pTaskInfo->m_tNextStartTime.Format("%m-%d-%y");
                  pTaskInfo->m_tLastExecutionTime = tTaskExce = CTime::GetTickCount();

				  //解决任务表备份类型区分
				  if (!pTaskInfo->m_bAutoBackUp)
				  {
					  pTaskInfo->m_bAutoBackUp = TRUE;
					  theApp.m_TaskSuccessList.addItem(pTaskInfo);
					  pTaskInfo->m_bAutoBackUp = FALSE;
				  }
				  else
				  {
					  theApp.m_TaskSuccessList.addItem(pTaskInfo);
				  }

                  theApp.SaveTaskInfo();
               }
               else
               {
                  //printf("%d:%s::完整备份文件失败!\n",__LINE__,__FILE__);
                  PTLOG("完整备份文件失败!\n");
                  pTaskInfo->m_tLastExecutionTime = NULL;
                  theApp.RemoveDir(strFullBackUpDirPath);
                  //return 0;
               }
            }
            else
            {
               //printf("%d:%s::完整备份数据库失败!\n",__LINE__,__FILE__);
               //printf("%d:%s::完整备份文件失败!\n",__LINE__,__FILE__);
               PTLOG("完整备份数据库失败!\n");
               PTLOG("完整备份文件失败!\n");
               pTaskInfo->m_tLastExecutionTime = NULL;
               theApp.RemoveDir(strFullBackUpDirPath);
               //  return 0;
            }
         }

		 //每个任务必定有差异备份
         if(!bXBack)
         {
            PTLOG("差异备份");
            bXFlag = theApp.BackupDatabase(strDifferentialDirPath + _T("\\Xbackup.bak"),FALSE);//差异备份
            if(bXFlag)
            {
               CString strDifferentialDirFilePath = strDifferentialDirPath+_T("\\订单库\\");
               if(strDifferentialDirPath.IsEmpty() || (!PathFileExists(strDifferentialDirPath)))
               {
                  theApp.CloseLoading();
				  sinLock.Unlock(); //解锁
                  return 0;
               }

               //printf("%d:%s::数据库差分备份成功!\n",__LINE__,__FILE__);
               PTLOG("数据库差分备份成功!\n");
               //文件差异备份
               if (pTaskInfo->m_bFileBackup)
               {
                  if(strDifferentialDirFilePath.IsEmpty() || (!PathFileExists(strDifferentialDirFilePath)))
                  {
                     theApp.MakeDirByCheck(strDifferentialDirFilePath);
                  }

                  CString str;
				  
                  str.Format(_T("/c %s\\xcopyAdd %s %s /e /k /d:%s"),theApp.m_strAppPath,pTaskInfo->m_strOldPath,strDifferentialDirFilePath,theApp.m_strXbackUpFileTime);

                  HINSTANCE n=ShellExecute(NULL,L"open",L"cmd.exe",str,NULL,SW_SHOW);
                  int a = (int)n;
                  if(a<=32)
                  {
                     //printf("%d:%s::差分备份文件失败!\n",__LINE__,__FILE__);
                     PTLOG("差分备份文件失败!\n");
                     pTaskInfo->m_tLastExecutionTime = NULL;
                     theApp.RemoveDir(strDifferentialDirPath);
                  }
                  else
                  {
                     //printf("%d:%s::差分备份文件成功!\n",__LINE__,__FILE__);
                     PTLOG("差分备份文件成功!\n");
                     theApp.m_strXbackUpFileTime = pTaskInfo->m_tNextStartTime.Format("%m-%d-%y");
                     pTaskInfo->m_tLastExecutionTime = tTaskExce = CTime::GetTickCount();
                     theApp.m_TaskSuccessList.addItem(pTaskInfo);
                     theApp.SaveTaskInfo();
                  }
               }
               else
               {
                  pTaskInfo->m_tLastExecutionTime = tTaskExce = CTime::GetTickCount();
                  theApp.m_TaskSuccessList.addItem(pTaskInfo);
                  theApp.SaveTaskInfo();
               }
            }
            else
            {
               // printf("%d:%s::差异备份数据库失败!\n",__LINE__,__FILE__);
               // printf("%d:%s::差异备份文件失败!\n",__LINE__,__FILE__);
               pTaskInfo->m_tLastExecutionTime = NULL;
               PTLOG("差异备份数据库失败!\n");
               theApp.RemoveDir(strDifferentialDirPath);
               // return 0;
            }

         }
       }

   }
   else
   {
      //printf("%d:%s::执行任务数据异常!\n",__LINE__,__FILE__);
      pTaskInfo->m_tLastExecutionTime = NULL;
      PTLOG("执行任务数据异常!\n");
   }
   //处理顺延问题
   CTime tCurTime = CTime::GetCurrentTime();
   CTime tDayEndTime(pTaskInfo->m_tStdStartTime.GetYear(),pTaskInfo->m_tStdStartTime.GetMonth(),pTaskInfo->m_tStdStartTime.GetDay(),23,59,59);
   int nListCount = theApp.m_TaskList.GetCount();
   CDBTaskInfoList DBTasList;
   for (int i = 0;i<nListCount;i++)
   {
      CDBTaskInfo *pDBTask = (CDBTaskInfo*)theApp.m_TaskList.GetAt(theApp.m_TaskList.FindIndex(i));
      if(pDBTask)
      {
         //当天任务时间更新（任务超过标准执行当天,没周期）
         if (tCurTime> tDayEndTime && tDayEndTime.GetYear() == pDBTask->m_tStdStartTime.GetYear()
            &&tDayEndTime.GetMonth() == pDBTask->m_tStdStartTime.GetMonth()
            &&tDayEndTime.GetDay() == pDBTask->m_tStdStartTime.GetDay()
            )
         {
            //时间周期更新---tasklist中未执行的（没有周期的，不再执行）
            if (!pDBTask->m_strCyc.IsEmpty())
            {
               pDBTask->m_strCyc.Right(pDBTask->m_strCyc.GetLength()-1);
               int day = _ttoi(pDBTask->m_strCyc.Right(pDBTask->m_strCyc.GetLength()-1));
               if (pDBTask->m_strCycType == CYCLE_DAY)
               {
                  LONG64 lSpan = day *DAY;
                  pDBTask->m_tStdStartTime+=lSpan;
                  pDBTask->m_tNextStartTime = pDBTask->m_tStdStartTime;
               }
               else if (pDBTask->m_strCycType == CYCLE_WEEK)
               {
                  LONG64 lSpan = day *WEEK;
                  pDBTask->m_tStdStartTime+=lSpan;
                  pDBTask->m_tNextStartTime += lSpan;
               }
               else if (pTaskInfoMom->m_strCycType == CYCLE_MONTH)
               {
                  CTime ttTime(pDBTask->m_tStdStartTime.GetYear()+1,pDBTask->m_tStdStartTime.GetMonth(),pDBTask->m_tStdStartTime.GetDay(),pDBTask->m_tStdStartTime.GetHour(),pDBTask->m_tStdStartTime.GetMinute(),pDBTask->m_tStdStartTime.GetSecond());
                  pDBTask->m_tStdStartTime = ttTime;
                  pDBTask->m_tNextStartTime = ttTime;
               }
               DBTasList.addItem(pDBTask);
               //printf("%d:%s::任务清理，任务周期时间更新，周期性任务添加成功!\n",__LINE__,__FILE__);
               PTLOG("任务清理，任务周期时间更新，周期性任务添加成功!!\n");
            }
         }
         else if (pDBTask->m_tStdStartTime < tCurTime
            && tDayEndTime.GetYear() == pDBTask->m_tStdStartTime.GetYear()
            &&tDayEndTime.GetMonth() == pDBTask->m_tStdStartTime.GetMonth()
            &&tDayEndTime.GetDay() == pDBTask->m_tStdStartTime.GetDay())
         {
            pDBTask->m_tNextStartTime = tCurTime;
            pDBTask->m_tStdStartTime = tCurTime;
            DBTasList.addItem(pDBTask);
            break;
         }
         else //注意之前的任务影响！！！！！
         {
            DBTasList.addItem(pDBTask);
         }

      }
   }
   //解决延时
   theApp.m_TaskList.RemoveAll();
   theApp.m_TaskList = DBTasList;

   //当前执行任务，为周期性任务，进行任务周期添加
   if (!pTaskInfoMom->m_strCyc.IsEmpty())
   {
      pTaskInfoMom->m_strCyc.Right(pTaskInfoMom->m_strCyc.GetLength()-1);
      int day = _ttoi(pTaskInfoMom->m_strCyc.Right(pTaskInfoMom->m_strCyc.GetLength()-1));
      if (pTaskInfoMom->m_strCycType == CYCLE_DAY)
      {
         LONG64 lSpan = day *DAY;
         pTaskInfoMom->m_tStdStartTime+=lSpan;
         pTaskInfoMom->m_tNextStartTime = pTaskInfoMom->m_tStdStartTime;
      }
      else if (pTaskInfoMom->m_strCycType == CYCLE_WEEK)
      {
         LONG64 lSpan = day *WEEK;
         pTaskInfoMom->m_tStdStartTime+=lSpan;
         pTaskInfoMom->m_tNextStartTime += lSpan;
      }
      else if (pTaskInfoMom->m_strCycType == CYCLE_MONTH)
      {
         CTime ttTime(pTaskInfoMom->m_tStdStartTime.GetYear()+1,pTaskInfoMom->m_tStdStartTime.GetMonth(),pTaskInfoMom->m_tStdStartTime.GetDay(),pTaskInfoMom->m_tStdStartTime.GetHour(),pTaskInfoMom->m_tStdStartTime.GetMinute(),pTaskInfoMom->m_tStdStartTime.GetSecond());
         pTaskInfoMom->m_tStdStartTime = ttTime;
         pTaskInfoMom->m_tNextStartTime = ttTime;
      }
      pTaskInfoMom->m_tLastExecutionTime = tTaskExce;
      theApp.m_TaskList.addItem(pTaskInfoMom);
      //printf("%d:%s::任务清理，任务周期时间更新，周期性任务添加成功!\n",__LINE__,__FILE__);
      PTLOG("任务清理，任务周期时间更新，周期性任务添加成功!\n");
   }

   //数据添加    theApp.CloseLoading();
   //printf("%d:%s::当前任务执行完毕!\n",__LINE__,__FILE__);
   PTLOG("当前任务执行完毕\n");
   theApp.m_bTaskMark = FALSE;
   theApp.CloseLoading();
   delete pTaskInfoMom;
   AfxEndThread(0);

   //解锁
   sinLock.Unlock();
   return 1;
}

BOOL CQLSvrMgnApp::ContrlCreate()
{
   //任务处理
   FreeConsole(); 
   if ( AllocConsole() ) 
   { 
      m_nCrt = _open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT); 
      *stdout = *(::_fdopen(m_nCrt, "w")); 
      ::setvbuf(stdout, NULL, _IONBF, 0); 
      *stderr = *(::_fdopen(m_nCrt, "w")); 
      ::setvbuf(stderr, NULL, _IONBF, 0);

      //Console隐藏关闭
      HWND hwnd = GetConsoleWindow();
      LONG Style;    //窗口风格
      Style = GetWindowLong(hwnd, GWL_STYLE);   // 得到窗口风格   
      Style = Style & ~WS_CAPTION;             //去掉标题栏
      SetConsoleTitle(_T("日志信息打印"));
      SetWindowLong(hwnd, GWL_STYLE, Style);     //为窗口设置新的风格
      return TRUE;
   } 
   return FALSE;
}

BOOL CQLSvrMgnApp::BackupDatabase(CString strDirectory,BOOL btype)
{
   PTLOG("执行备份");
   BOOL bRet = TRUE;
   CString strSQL = _T("");
   CString strDatabase = _T("");
   theApp.OnReadIni(_T("ConfigureInfo"), _T("DatabaseName"), strDatabase,INI_SQLSVR);
   if(btype)
      strSQL.Format(_T("BACKUP DATABASE [%s] TO disk = '%s'"), strDatabase, strDirectory);
   else
      strSQL.Format(_T("BACKUP DATABASE [%s] TO disk = '%s' WITH  DIFFERENTIAL,init"),strDatabase,strDirectory);

   if(m_pADOConn->ExecuteSQL(strSQL))
   {
      bRet = TRUE;
   }
   else
   {
      bRet = FALSE;
   }

   return bRet;
}


BOOL CQLSvrMgnApp::FindBackupFile(CString strPath)
{
   CFileFind filefind;
   CString strDir = strPath; 
   strDir = strPath + _T("\\") +_T("FullBackUp") +_T("\\");

   if (!PathFileExists(strDir))
   {
      return FALSE;
   }
   if (strDir.Right(1)!="\\")
   {
      strDir+="\\";
   }
   strDir+="*.*";
   bool bwork = filefind.FindFile(strDir);
   while(bwork)
   {
      bwork = filefind.FindNextFileW();
      CString DataFile = filefind.GetFilePath();
      if (filefind.IsDirectory()&&!filefind.IsDots())
      {
         CFileFind filefind1;
         CString fil = DataFile +"\\backup.bak";
         bool b1work = filefind1.FindFile(fil);
         if (b1work)
         {
            b1work = filefind1.FindNextFileW();
            CString Dataile = filefind1.GetFilePath();
            if (!filefind1.IsDirectory()&&!filefind1.IsDots())
            {
                return TRUE;
            }
         }
      }
      else if(!filefind.IsDots())
      {
         
      }
   }

   filefind.Close();
   return FALSE;
}

void CQLSvrMgnApp::InitTaskInfo()
{
   //任务表数据初始化
   //当前待执行任务数
   CString strTaskCount;
   OnReadIni(_T("TaskCount"),_T("Count"),strTaskCount,INI_TASKINFO);
   m_nTaskCount =  _ttoi(strTaskCount); 

   //任务记录总数
   CString strTaskAllCount;
   OnReadIni(_T("TaskALLCount"),_T("ALLCount"),strTaskAllCount,INI_TASKINFO);
   m_nTaskID = _ttoi(strTaskAllCount);

   //任务ID
   for (int j = 0;j<m_nTaskCount;j++)
   {
      CString strIndex,strData;
      strIndex.Format(_T("%d"),j);
       OnReadIni(_T("TaskID"),strIndex,strData,INI_TASKINFO);
       m_mapTaskID.insert(std::pair<int, CString>(j, strData));
   }
   //任务配置
   for (int i = 0;i<m_nTaskCount;i++)
   {
      CDBTaskInfo DBTask;
      CString strAutoBackUp,strFileBackUp,strStartTime,strStdStartTime,strNextStartTime,strState,strLastSuccessTime;
      theApp.OnReadIni(theApp.m_mapTaskID[i],_T("m_strID"),DBTask.m_strID,INI_TASKINFO);
      theApp.OnReadIni(theApp.m_mapTaskID[i],_T("m_bAutoBackUp"),strAutoBackUp,INI_TASKINFO);
      theApp.OnReadIni(theApp.m_mapTaskID[i],_T("m_bFileBackup"),strFileBackUp,INI_TASKINFO);
      theApp.OnReadIni(theApp.m_mapTaskID[i],_T("m_tStartTime"),strStartTime,INI_TASKINFO);
      theApp.OnReadIni(theApp.m_mapTaskID[i],_T("m_tStdStartTime"),strStdStartTime,INI_TASKINFO);
      theApp.OnReadIni(theApp.m_mapTaskID[i],_T("m_tNextStartTime"),strNextStartTime,INI_TASKINFO);
      theApp.OnReadIni(theApp.m_mapTaskID[i],_T("m_nState"),strState,INI_TASKINFO);
      theApp.OnReadIni(theApp.m_mapTaskID[i],_T("m_strCyc"),DBTask.m_strCyc,INI_TASKINFO);
      theApp.OnReadIni(theApp.m_mapTaskID[i],_T("m_strCycType"),DBTask.m_strCycType,INI_TASKINFO);
      theApp.OnReadIni(theApp.m_mapTaskID[i],_T("m_strOldPath"),DBTask.m_strOldPath,INI_TASKINFO);
      theApp.OnReadIni(theApp.m_mapTaskID[i],_T("m_strNewDirPath"),DBTask.m_strNewDirPath,INI_TASKINFO);
      theApp.OnReadIni(theApp.m_mapTaskID[i],_T("m_strTaskType"),DBTask.m_strTaskType,INI_TASKINFO);
      theApp.OnReadIni(theApp.m_mapTaskID[i],_T("m_tLastExecutionTime"),strLastSuccessTime,INI_TASKINFO);

      //处理配置文件数据不完整问题  2018/09/05
      if (DBTask.m_strID.IsEmpty()||strAutoBackUp.IsEmpty()||strFileBackUp.IsEmpty()
         ||strStartTime.IsEmpty()||strStdStartTime.IsEmpty()||strNextStartTime.IsEmpty()
         ||strState.IsEmpty()||DBTask.m_strCyc.IsEmpty()||DBTask.m_strCycType.IsEmpty()
         ||DBTask.m_strNewDirPath.IsEmpty()||DBTask.m_strOldPath.IsEmpty() || DBTask.m_strTaskType.IsEmpty())
      {
         continue;

      }


      if (strAutoBackUp ==_T("0"))
      {
         DBTask.m_bAutoBackUp = FALSE;
      }
      else
         DBTask.m_bAutoBackUp = TRUE;

      if (strFileBackUp ==_T("0"))
      {
         DBTask.m_bFileBackup = FALSE;
      }
      else
         DBTask.m_bFileBackup = TRUE;

      COleVariant vtime1(strStartTime);
      vtime1.ChangeType(VT_DATE);
      COleDateTime time1=vtime1;
      SYSTEMTIME systime1;
      VariantTimeToSystemTime(time1, &systime1);
      CTime tm1(systime1);   //CString=======>CTime
      DBTask.m_tStartTime = tm1;

      COleVariant vtime2(strStdStartTime);
      vtime2.ChangeType(VT_DATE);
      COleDateTime time2=vtime2;
      SYSTEMTIME systime2;
      VariantTimeToSystemTime(time2, &systime2);
      CTime tm2(systime2);   //CString=======>CTime
      DBTask.m_tStdStartTime = tm2;

      COleVariant vtime3(strNextStartTime);
      vtime3.ChangeType(VT_DATE);
      COleDateTime time3=vtime3;
      SYSTEMTIME systime3;
      VariantTimeToSystemTime(time3, &systime3);
      CTime tm3(systime3);
      DBTask.m_tNextStartTime = tm3;
      DBTask.m_nState = _ttoi(strState);

      if (!strLastSuccessTime.IsEmpty())
      {
         COleVariant vtime4(strLastSuccessTime);
         vtime4.ChangeType(VT_DATE);
         COleDateTime time4 =vtime4;
         SYSTEMTIME systime4;
         VariantTimeToSystemTime(time4, &systime4);
         CTime tm4(systime4);   //CString=======>CTime
         DBTask.m_tLastExecutionTime = tm4;
      }

      //任务表延时处理
       CTime tCurTime = CTime::GetCurrentTime();
       CString tt = tCurTime.Format(_T("%y/%m/%d %H:%M:%S"));
        //当天任务时间更新（任务超过标准执当天,没周期）
        if (DBTask.m_tNextStartTime>tCurTime)
        {
            theApp.m_TaskList.addItem(&DBTask);
       }
        else
        {
           //处理延时周期时间修改
           while (TRUE)
           {
              CTime tBCurTime = CTime::GetCurrentTime();
              if (DBTask.m_tNextStartTime>tCurTime)
              {
                 theApp.m_TaskList.addItem(&DBTask);
                 break;
              }

              if (!DBTask.m_strCyc.IsEmpty())
              {
                 DBTask.m_strCyc.Right(DBTask.m_strCyc.GetLength()-1);
                 int day = _ttoi(DBTask.m_strCyc.Right(DBTask.m_strCyc.GetLength()-1));
                 if (DBTask.m_strCycType == CYCLE_DAY)
                 {
                    LONG64 lSpan = day *DAY;
                    DBTask.m_tStdStartTime+=lSpan;
                    DBTask.m_tNextStartTime = DBTask.m_tStdStartTime;
                 }
                 else if (DBTask.m_strCycType == CYCLE_WEEK)
                 {
                    LONG64 lSpan = day *WEEK;
                    DBTask.m_tStdStartTime+=lSpan;
                    DBTask.m_tNextStartTime += lSpan;
                 }
                 else if (DBTask.m_strCycType == CYCLE_MONTH)
                 {
                    CTime ttTime(DBTask.m_tStdStartTime.GetYear()+1,DBTask.m_tStdStartTime.GetMonth(),DBTask.m_tStdStartTime.GetDay(),DBTask.m_tStdStartTime.GetHour(),DBTask.m_tStdStartTime.GetMinute(),DBTask.m_tStdStartTime.GetSecond());
                    DBTask.m_tStdStartTime = ttTime;
                    DBTask.m_tNextStartTime = ttTime;
                 }
                 printf("%d:%s::任务清理，任务周期时间更新，周期性任务添加成功!\n",__LINE__,__FILE__);
              }
              else
              {
                   break;//立即任务/周期为空   跳过该条
              }
           }
        }
   }


   //成功任务表数据初始化
   //成功任务数
   CString strTaskSuccessCount;
   OnReadIni(_T("TaskSuccess"),_T("TaskSuccessCount"),strTaskSuccessCount,INI_TASKVTY);
   m_nTaskSucessfullCount =  _ttoi(strTaskSuccessCount);
   //任务ID
   for (int j = 0;j<m_nTaskSucessfullCount;j++)
   {
      CString strIndex;
      strIndex.Format(_T("%d"),j);
      OnReadIni(_T("TaskSuccessID"),strIndex,m_mapTaskSuccessfullID[j],INI_TASKVTY);
   }
   //任务配置
   for (int i = 0;i<m_nTaskSucessfullCount;i++)
   {
      CDBTaskInfo DBTask;
      CString strIndex;
      strIndex.Format(_T("%d"),i);
      CString strAutoBackUp,strFileBackUp,strStartTime,strStdStartTime,strNextStartTime,strState,strLastSuccessTime;
      theApp.OnReadIni(strIndex,_T("m_strID"),DBTask.m_strID,INI_TASKVTY);
      theApp.OnReadIni(strIndex,_T("m_bAutoBackUp"),strAutoBackUp,INI_TASKVTY);
      theApp.OnReadIni(strIndex,_T("m_bFileBackup"),strFileBackUp,INI_TASKVTY);
      theApp.OnReadIni(strIndex,_T("m_tStartTime"),strStartTime,INI_TASKVTY);
      theApp.OnReadIni(strIndex,_T("m_tStdStartTime"),strStdStartTime,INI_TASKVTY);
      theApp.OnReadIni(strIndex,_T("m_tNextStartTime"),strNextStartTime,INI_TASKVTY);
      theApp.OnReadIni(strIndex,_T("m_nState"),strState,INI_TASKVTY);
      theApp.OnReadIni(strIndex,_T("m_strCyc"),DBTask.m_strCyc,INI_TASKVTY);
      theApp.OnReadIni(strIndex,_T("m_strCycType"),DBTask.m_strCycType,INI_TASKVTY);
      theApp.OnReadIni(strIndex,_T("m_strOldPath"),DBTask.m_strOldPath,INI_TASKVTY);
      theApp.OnReadIni(strIndex,_T("m_strNewDirPath"),DBTask.m_strNewDirPath,INI_TASKVTY);
      theApp.OnReadIni(strIndex,_T("m_tLastExecutionTime"),strLastSuccessTime,INI_TASKVTY);
      if (DBTask.m_strID.IsEmpty()||strAutoBackUp.IsEmpty()||strFileBackUp.IsEmpty()
         ||strStartTime.IsEmpty()||strStdStartTime.IsEmpty()||strNextStartTime.IsEmpty()
         ||strState.IsEmpty()||DBTask.m_strCyc.IsEmpty()||DBTask.m_strCycType.IsEmpty()
         ||DBTask.m_strNewDirPath.IsEmpty()||DBTask.m_strOldPath.IsEmpty() || DBTask.m_strTaskType.IsEmpty())
      {
         continue;
      }
      if (strAutoBackUp ==_T("0"))
      {
         DBTask.m_bAutoBackUp = FALSE;
      }
      else
         DBTask.m_bAutoBackUp = TRUE;

      if (strFileBackUp ==_T("0"))
      {
         DBTask.m_bFileBackup = FALSE;
      }
      else
         DBTask.m_bFileBackup = TRUE;

      COleVariant vtime1(strStartTime);
      vtime1.ChangeType(VT_DATE);
      COleDateTime time1=vtime1;
      SYSTEMTIME systime1;
      VariantTimeToSystemTime(time1, &systime1);
      CTime tm1(systime1);   //CString=======>CTime
      DBTask.m_tStartTime = tm1;

      COleVariant vtime2(strStdStartTime);
      vtime2.ChangeType(VT_DATE);
      COleDateTime time2=vtime2;
      SYSTEMTIME systime2;
      VariantTimeToSystemTime(time2, &systime2);
      CTime tm2(systime2);   //CString=======>CTime
      DBTask.m_tStdStartTime = tm2;

      COleVariant vtime3(strNextStartTime);
      vtime3.ChangeType(VT_DATE);
      COleDateTime time3=vtime3;
      SYSTEMTIME systime3;
      VariantTimeToSystemTime(time3, &systime3);
      CTime tm3(systime3);
      DBTask.m_tNextStartTime = tm3;
      DBTask.m_nState = _ttoi(strState);

      if (!strLastSuccessTime.IsEmpty())
      {
         COleVariant vtime4(strLastSuccessTime);
         vtime4.ChangeType(VT_DATE);
         COleDateTime time4=vtime4;
         SYSTEMTIME systime4;
         VariantTimeToSystemTime(time4, &systime4);
         CTime tm4(systime4);
         DBTask.m_tLastExecutionTime = tm4;
      }

      m_TaskSuccessList.addItem(&DBTask);
   }
}

void CQLSvrMgnApp::SaveTaskInfo()
{
   //成功任务计数配置写入
   CString strTaskSuccessCount;
   strTaskSuccessCount.Format(_T("%d"),theApp.m_TaskSuccessList.GetCount());
   OnWriteIni(_T("TaskSuccess"),_T("TaskSuccessCount"),strTaskSuccessCount,INI_TASKVTY);

   //成功任务配置写入
   for (int i = 0;i<m_TaskSuccessList.GetCount();i++)
   {
      //数据写入
      CDBTaskInfo *pDBTask =(CDBTaskInfo*) m_TaskSuccessList.GetAt(m_TaskSuccessList.FindIndex(i));
      if (pDBTask)
      {
         //任务ID写入
         CString strIndex;
         strIndex.Format(_T("%d"),i);
         theApp.OnWriteIni(_T("TaskSuccessID"),strIndex,pDBTask->m_strID,INI_TASKVTY);

         //任务写入
         CString strAutoBackUp,strFileBackUp,strStartTime,strStdStartTime,strNextStartTime,strState,strLastSuccessTime;
         strAutoBackUp.Format(_T("%d"),pDBTask->m_bAutoBackUp);
         strFileBackUp.Format(_T("%d"),pDBTask->m_bFileBackup);
         strStartTime = pDBTask->m_tStartTime.Format("%Y-%m-%d %H:%M:%S");
         strStdStartTime = pDBTask->m_tStdStartTime.Format("%Y-%m-%d %H:%M:%S");
         strNextStartTime = pDBTask->m_tNextStartTime.Format("%Y-%m-%d %H:%M:%S");
         strState.Format(_T("%d"),pDBTask->m_nState);
         strLastSuccessTime = pDBTask->m_tLastExecutionTime.Format("%Y-%m-%d %H:%M:%S");
         theApp.OnWriteIni(strIndex,_T("m_strID"),pDBTask->m_strID,INI_TASKVTY);
         theApp.OnWriteIni(strIndex,_T("m_bAutoBackUp"),strAutoBackUp,INI_TASKVTY);
         theApp.OnWriteIni(strIndex,_T("m_bFileBackup"),strFileBackUp,INI_TASKVTY);
         theApp.OnWriteIni(strIndex,_T("m_tStartTime"),strStartTime,INI_TASKVTY);
         theApp.OnWriteIni(strIndex,_T("m_tStdStartTime"),strStdStartTime,INI_TASKVTY);
         theApp.OnWriteIni(strIndex,_T("m_tNextStartTime"),strNextStartTime,INI_TASKVTY);
         theApp.OnWriteIni(strIndex,_T("m_nState"),strState,INI_TASKVTY);
         theApp.OnWriteIni(strIndex,_T("m_strCyc"),pDBTask->m_strCyc,INI_TASKVTY);
         theApp.OnWriteIni(strIndex,_T("m_strCycType"),pDBTask->m_strCycType,INI_TASKVTY);
         theApp.OnWriteIni(strIndex,_T("m_strOldPath"),pDBTask->m_strOldPath,INI_TASKVTY);
         theApp.OnWriteIni(strIndex,_T("m_strNewDirPath"),pDBTask->m_strNewDirPath,INI_TASKVTY);
         theApp.OnWriteIni(strIndex,_T("m_strTaskType"),pDBTask->m_strTaskType,INI_TASKVTY);
         theApp.OnWriteIni(strIndex,_T("m_tLastExecutionTime"),strLastSuccessTime,INI_TASKVTY);
      }

   }

   //任务表数据写入
   //任务数
   DeleteFile(m_strAppPath+_T("\\TASKINFO.ini"));//任务表;
   CString strTaskCount;
   theApp.m_nTaskCount = theApp.m_TaskList.GetCount();
   strTaskCount.Format(_T("%d"),theApp.m_TaskList.GetCount());
   OnWriteIni(_T("TaskCount"),_T("Count"),strTaskCount,INI_TASKINFO);

   //任务记录总数
   CString strTaskAllCount;
   strTaskAllCount.Format(_T("%d"),theApp.m_nTaskID);
   OnWriteIni(_T("TaskALLCount"),_T("ALLCount"),strTaskAllCount,INI_TASKINFO);

   //任务配置写入
   for (int j = 0;j<m_TaskList.GetCount();j++)
   {
      //数据写入
      CDBTaskInfo *pDBTask =(CDBTaskInfo*) m_TaskList.GetAt(m_TaskList.FindIndex(j));
      if (pDBTask)
      {
         CDBTaskInfo DBTask;
         DBTask.Copy(pDBTask);
         //任务ID写入
         CString nIndex;
         nIndex.Format(_T("%d"),j);
         theApp.OnWriteIni(_T("TaskID"),nIndex,DBTask.m_strID,INI_TASKINFO);

         //任务数据写入
         CString strAutoBackUp,strFileBackUp,strStartTime,strStdStartTime,strNextStartTime,strState,strLastSuccessTime;
         strAutoBackUp.Format(_T("%d"),DBTask.m_bAutoBackUp);
         strFileBackUp.Format(_T("%d"),DBTask.m_bFileBackup);
         strStartTime = DBTask.m_tStartTime.Format("%Y-%m-%d %H:%M:%S");
         strStdStartTime = DBTask.m_tStdStartTime.Format("%Y-%m-%d %H:%M:%S");
         strNextStartTime = DBTask.m_tNextStartTime.Format("%Y-%m-%d %H:%M:%S");
         strState.Format(_T("%d"),DBTask.m_nState);
         strLastSuccessTime = DBTask.m_tLastExecutionTime.Format("%Y-%m-%d %H:%M:%S");
         theApp.OnWriteIni(DBTask.m_strID,_T("m_strID"),DBTask.m_strID,INI_TASKINFO);
         theApp.OnWriteIni(DBTask.m_strID,_T("m_bAutoBackUp"),strAutoBackUp,INI_TASKINFO);
         theApp.OnWriteIni(DBTask.m_strID,_T("m_bFileBackup"),strFileBackUp,INI_TASKINFO);
         theApp.OnWriteIni(DBTask.m_strID,_T("m_tStartTime"),strStartTime,INI_TASKINFO);
         theApp.OnWriteIni(DBTask.m_strID,_T("m_tStdStartTime"),strStdStartTime,INI_TASKINFO);
         theApp.OnWriteIni(DBTask.m_strID,_T("m_tNextStartTime"),strNextStartTime,INI_TASKINFO);
         theApp.OnWriteIni(DBTask.m_strID,_T("m_nState"),strState,INI_TASKINFO);
         theApp.OnWriteIni(DBTask.m_strID,_T("m_strCyc"),DBTask.m_strCyc,INI_TASKINFO);
         theApp.OnWriteIni(DBTask.m_strID,_T("m_strCycType"),DBTask.m_strCycType,INI_TASKINFO);
         theApp.OnWriteIni(DBTask.m_strID,_T("m_strOldPath"),DBTask.m_strOldPath,INI_TASKINFO);
         theApp.OnWriteIni(DBTask.m_strID,_T("m_strNewDirPath"),DBTask.m_strNewDirPath,INI_TASKINFO);
         theApp.OnWriteIni(DBTask.m_strID,_T("m_strTaskType"),pDBTask->m_strTaskType,INI_TASKINFO);
         theApp.OnWriteIni(DBTask.m_strID,_T("m_tLastExecutionTime"),strLastSuccessTime,INI_TASKINFO);
      }


   }
}

BOOL CQLSvrMgnApp::RemoveDir( CString strDirName )
{
   PTLOG("执行删除文件夹");

   CString PUBPATH;

   PUBPATH=strDirName;

   CFileFind tempFind;

   strDirName+="\\*.*";

   BOOL IsFinded=(BOOL)tempFind.FindFile(strDirName);

   while(IsFinded)

   {

      IsFinded=(BOOL)tempFind.FindNextFile();

      if(!tempFind.IsDots())

      {

         CString strDirZanName;

         strDirZanName+=PUBPATH;

         strDirZanName+="\\";

         strDirZanName+=tempFind.GetFileName();

         if(tempFind.IsDirectory())

         {

            //strDirName += PUBPATH;

            RemoveDir(strDirZanName);

         }

         else

         {

            SetFileAttributes(strDirName,FILE_ATTRIBUTE_NORMAL); //去掉文件的系统和隐藏属性

            DeleteFile(strDirName);

         }

      }

   }

   tempFind.Close();

   if(!RemoveDirectory(PUBPATH))

   {

      return false ;

   }

   PTLOG("文件夹删除成功...");

   return true;
}

BOOL CQLSvrMgnApp::OnlyInstance()
{
   BOOL bRet = TRUE;
   m_hSem = CreateSemaphore(NULL, 1, 1, m_pszAppName);
   CString strPrePath = _T("");
   CString strAppPath = m_strAppPath+_T("\\")+m_pszAppName+_T(".exe");
   // 信号量存在，则程序已有一个实例运行
   if (GetLastError() == ERROR_ALREADY_EXISTS)
   {
      // 寻找先前实例的窗口
      HWND hWndPrevious = ::GetWindow(::GetDesktopWindow(), GW_CHILD);
      while (::IsWindow(hWndPrevious))
      {
         // 检查窗口是否有预设的标记
         if (::GetProp(hWndPrevious, m_pszAppName))
         {
            GetAppPathFromHwnd(hWndPrevious,strPrePath);
            if (strPrePath == strAppPath)//路径完全一样的App
            {
               bRet = FALSE;

               //主窗口已最小化或最大化显示，则最大化显示
               if (IsIconic(hWndPrevious)||IsZoomed(hWndPrevious))
               {
                  //ShowWindow(hWndPrevious, SW_RESTORE);//恢复其大小
                  ShowWindow(hWndPrevious, SW_MAXIMIZE);
               }
               else
               {
                  ShowWindow(hWndPrevious, SW_NORMAL);
               }

               //将主窗激活
               //SetForegroundWindow(hWndPrevious);
               BringWindowToTop(hWndPrevious);
               //将主窗的对话框激活
               //SetForegroundWindow(GetLastActivePopup(hWndPrevious));		
               SetWindowPos(hWndPrevious,HWND_TOPMOST,0,0,0,0, SWP_NOMOVE|SWP_NOSIZE);
               SetWindowPos(hWndPrevious,HWND_NOTOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);

               ::SendMessage(hWndPrevious,WM_KDSFILEMGN_WORKTYPE,(WPARAM )m_nWorkType,(LPARAM)0);

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

int CQLSvrMgnApp::GetAppPathFromHwnd(HWND hWnd, CString& ExePath) 
{ 
   TCHAR szPath[MAX_PATH]; 
   int ErrorCode = 0; 
   DWORD idProcess; 
   GetWindowThreadProcessId(hWnd, &idProcess); 
   HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, idProcess); 
   if( NULL != hProcess ) 
   { 
      HMODULE hMod; 
      DWORD cbNeeded; 
      if(EnumProcessModules( hProcess, &hMod, sizeof( hMod ), &cbNeeded )) 
      { 
         DWORD dw = GetModuleFileNameEx( hProcess, hMod, szPath, MAX_PATH ); 
         if(dw > 0) 
         { 
            ExePath = szPath; 
         } 
         else 
         { 
            ErrorCode = GetLastError(); 
         } 
      } 
      CloseHandle(hProcess); 
   } 

   return ErrorCode; 
} 

UINT CQLSvrMgnApp::DealAutoDelete( LPVOID pParam )
{
	//任务相关文件清理
	CDBTaskInfo * pTaskInfo = (CDBTaskInfo *)pParam;//类型转换
	if (pTaskInfo != NULL)
	{
		CString strTime;
		 strTime = pTaskInfo->m_tLastExecutionTime.Format(_T("%Y_%m_%d_%H时%M分"));
		CString strFullBackUpDirPath = pTaskInfo->m_strNewDirPath + _T("\\")+ pTaskInfo->m_strID+ _T("\\") +_T("FullBackUp") +_T("\\")  +strTime;
		CString strDifferentialDirPath = pTaskInfo->m_strNewDirPath + _T("\\") + pTaskInfo->m_strID+ _T("\\")+_T("XBackUp")+_T("\\") + strTime;
		//执行删除操作
		theApp.RemoveDir(strFullBackUpDirPath);
		theApp.RemoveDir(strDifferentialDirPath);
	}

	AfxEndThread(0);
	return 0;
}
