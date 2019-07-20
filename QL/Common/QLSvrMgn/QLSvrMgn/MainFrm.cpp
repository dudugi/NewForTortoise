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

// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "QLSvrMgn.h"

#include "MainFrm.h"
#include "QLSvrMgnView.h"
#include "MyADOConnEx.h"
#include "LocalConfigureDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)
//#define  WM_BACKUP_D WM_USER+1

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_COMMAND(IDD_DLG_PANE1_ITEM1, &CMainFrame::OnComdPaneItem)
	// by zhangyx 2017//11//29
	ON_COMMAND(IDD_DLG_PANE1_ITEM2, &CMainFrame::OnComdPaneItem)
	ON_COMMAND(IDD_DLG_PANE1_ITEM3, &CMainFrame::OnComdPaneItem)
	ON_COMMAND(IDD_DLG_PANE2_ITEM1, &CMainFrame::OnComdPaneItem)
	ON_COMMAND(IDD_DLG_PANE2_ITEM2, &CMainFrame::OnComdPaneItem)
	ON_COMMAND(IDD_DLG_PANE2_ITEM3, &CMainFrame::OnComdPaneItem)
   ON_COMMAND(IDD_DIALOG_CREATE_SQL_SCRIPT, &CMainFrame::OnComdPaneItem)
	// by zhangyx 2017//11//29end
	ON_WM_CREATE()
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)
	ON_COMMAND(ID_VIEW_CAPTION_BAR, &CMainFrame::OnViewCaptionBar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CAPTION_BAR, &CMainFrame::OnUpdateViewCaptionBar)
	ON_COMMAND(ID_TOOLS_OPTIONS, &CMainFrame::OnOptions)
	ON_WM_CLOSE()
   ON_MESSAGE(WM_ADOCONN_MSG, &CMainFrame::OnAdoconnMsg)
   ON_MESSAGE(WM_TRAY, &CMainFrame::OnTrayMsg)
   ON_COMMAND(IDM_EXIT,OnExit)
   ON_COMMAND(ID_APP_EXIT,OnExit)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,          // 状态行指示器
	ID_INDICATOR_CUS,		//自定义：现在账户及职务
	ID_INDICATOR_TIME,		//自定义：显示刷新时间
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_OFF_2007_BLUE);
}

CMainFrame::~CMainFrame()
{
   Shell_NotifyIcon(NIM_DELETE, &m_nid);
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// 基于持久值设置视觉管理器和样式
	OnApplicationLook(theApp.m_nAppLook);
#ifdef USING_RIB_CAPTION
	BOOL bNameValid;
	m_wndRibbonBar.Create(this);
	m_wndRibbonBar.LoadFromResource(IDR_RIBBON);
	m_wndRibbonBar.ToggleMimimizeState();

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}

	CString strTitlePane1;
	CString strTitlePane2;
	bNameValid = strTitlePane1.LoadString(IDS_STATUS_PANE1);
	ASSERT(bNameValid);
	bNameValid = strTitlePane2.LoadString(IDS_STATUS_PANE2);
	ASSERT(bNameValid);
	m_wndStatusBar.AddElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE1, strTitlePane1, TRUE), strTitlePane1);
	m_wndStatusBar.AddExtendedElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE2, strTitlePane2, TRUE), strTitlePane2);
#else
	if (!m_wndMenuBar.Create(this))
	{
		TRACE0("未能创建菜单栏\n");
		return -1;      // 未能创建
	}

	m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);

	// 防止菜单栏在激活时获得焦点
	CMFCPopupMenu::SetForceMenuFocus(FALSE);

	// 允许用户定义的工具栏操作:
	//InitUserToolbars(NULL, uiFirstUserToolBarId, uiLastUserToolBarId);

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	//设置状态栏宽度
	CRect rt;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rt, 0);
	int nWidth = rt.Width()/9;
	m_wndStatusBar.SetPaneInfo(0, ID_INDICATOR_CUS, SBPS_STRETCH, nWidth);
	m_wndStatusBar.SetPaneInfo(1, ID_INDICATOR_TIME, SBPS_STRETCH, nWidth*7);
	// TODO: 如果您不希望工具栏和菜单栏可停靠，请删除这五行
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndMenuBar);
#endif

	// 启用 Visual Studio 2005 样式停靠窗口行为
	CDockingManager::SetDockingMode(DT_SMART);
	// 启用 Visual Studio 2005 样式停靠窗口自动隐藏行为
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// 导航窗格将创建在左侧，因此将暂时禁用左侧的停靠:
	EnableDocking(CBRS_ALIGN_TOP | CBRS_ALIGN_BOTTOM | CBRS_ALIGN_RIGHT);

	// 创建并设置“Outlook”导航栏:
	//if (!CreateOutlookBar(m_wndNavigationBar, ID_VIEW_NAVIGATION, m_wndTree, m_wndCalendar, 200))
	if (!CreateOutlookBar(m_wndNavigationBar, ID_VIEW_NAVIGATION, &m_wndRibbonBarPane1,&m_wndRibbonBarPane2,200))
	{
		TRACE0("未能创建导航窗格\n");
		return -1;      // 未能创建
	}

	// 创建标题栏:
	if (!CreateCaptionBar())
	{
		TRACE0("未能创建标题栏\n");
		return -1;      // 未能创建
	}

	// 已创建 Outlook 栏，应允许在左侧停靠。
	EnableDocking(CBRS_ALIGN_LEFT);
	EnableAutoHidePanes(CBRS_ALIGN_RIGHT);
   InitTray();

   //添加窗口标志
   ::SetProp(GetSafeHwnd(), theApp.m_pszAppName, (HANDLE)1);

   
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	cs.style &= ~FWS_ADDTOTITLE;//允许修改标题
//	cs.hMenu = NULL;//除去主菜单
// 	cs.style &= ~WS_MINIMIZEBOX; //去除最小化
// 	cs.style &= ~WS_MAXIMIZEBOX; //去除最大化


	return TRUE;
}

BOOL CMainFrame::CreateOutlookBar(CMyOutlookBar& bar, UINT uiID, CMyOutlookBarPane *pOutlookBarPane1,CMyOutlookBarPane *pOutlookBarPane2,int nInitialWidth)
{
	BOOL bNameValid;
	CString strTemp;
	bNameValid = strTemp.LoadString(IDS_SHORTCUTS);
	ASSERT(bNameValid);
	if (!bar.Create(strTemp, this, CRect(0, 0, nInitialWidth, 32000), uiID, WS_CHILD | WS_VISIBLE | CBRS_LEFT))
	{
		return FALSE; // 未能创建
	}

	CMFCOutlookBarTabCtrl* pOutlookBar = (CMFCOutlookBarTabCtrl*)bar.GetUnderlyingWindow();

	if (pOutlookBar == NULL)
	{
		ASSERT(FALSE);
		return FALSE;
	}

	pOutlookBar->EnableInPlaceEdit(TRUE);

	//加载图标
	CWindowDC dc(NULL);
	const BOOL bIsHiColor = dc.GetDeviceCaps(BITSPIXEL) > 16;
	CImageList images;
	CBitmap bmp;
	if (!bmp.LoadBitmap(bIsHiColor ? IDB_NAVIGATION_LARGE_HC : IDB_NAVIGATION_LARGE))
	{
		return FALSE;
	}
	BITMAP bm;
	bmp.GetBitmap(&bm);

	UINT nFlags = ILC_MASK;
	if (bIsHiColor) nFlags |= ILC_COLOR24;
	else nFlags |= ILC_COLOR;

	images.Create(32, bm.bmHeight, nFlags, 0, 0);
	images.Add(&bmp, RGB(255, 0, 255));

	static UINT uiPageID = 1;
	// 可浮动，可自动隐藏，可调整大小，但不能关闭
	DWORD dwStyle = AFX_CBRS_FLOAT | AFX_CBRS_AUTOHIDE | AFX_CBRS_RESIZE;
	DWORD dwPaneStyle = AFX_DEFAULT_TOOLBAR_STYLE | CBRS_FLOAT_MULTI;

	if(pOutlookBarPane1->Create(&bar,dwPaneStyle,uiPageID++,dwStyle))
	{
		pOutlookBarPane1->SetOwner(this);
		pOutlookBarPane1->EnableTextLabels();

		//addItem
		//by zhangyx 2017//11//29 添加对话框ID
      pOutlookBarPane1->AddItem(2,_T("差异生成数据库脚本"),IDD_DIALOG_CREATE_SQL_SCRIPT,images);
		pOutlookBarPane1->AddItem(2,_T("备份"), IDD_DLG_PANE1_ITEM1, images);
		pOutlookBarPane1->AddItem(2,_T("还原"), IDD_DLG_PANE1_ITEM2, images);
		pOutlookBarPane1->AddItem(2,_T("升级数据库"), IDD_DLG_PANE1_ITEM3, images);
		pOutlookBarPane1->AddItem(2,_T("安装数据库"), IDD_DLG_PANE2_ITEM1, images);
      pOutlookBarPane1->AddItem(2,_T("执行数据库脚本"), IDD_DLG_PANE2_ITEM2, images);
		bar.AddPane(pOutlookBarPane1,_T("Pane1"),1);
	}

 	/*if(pOutlookBarPane2->Create(&bar,dwPaneStyle,uiPageID++,dwStyle))
 	{
 		pOutlookBarPane2->SetOwner(this);
 		pOutlookBarPane2->EnableTextLabels();
 
 		//addItem
 		//by zhangyx 2017//11//29 添加对话框ID
 		pOutlookBarPane2->AddItem(2,_T("Pane2_Item1"), IDD_DLG_PANE2_ITEM1, images);
 		pOutlookBarPane2->AddItem(2,_T("Pane2_Item2"), IDD_DLG_PANE2_ITEM2, images);
 		pOutlookBarPane2->AddItem(2,_T("Pane2_Item3"), IDD_DLG_PANE2_ITEM3, images);
 
 		bar.AddPane(pOutlookBarPane2,_T("Pane2"),1);
 	}*/

	bar.SetPaneStyle(bar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	pOutlookBar->SetImageList(theApp.m_bHiColorIcons ? IDB_PAGES_HC : IDB_PAGES, 24);
	pOutlookBar->SetToolbarImageList(theApp.m_bHiColorIcons ? IDB_PAGES_SMALL_HC : IDB_PAGES_SMALL, 16);
	pOutlookBar->RecalcLayout();


	BOOL bAnimation = theApp.GetInt(_T("OutlookAnimation"), TRUE);
	CMFCOutlookBarTabCtrl::EnableAnimation(bAnimation);

	bar.SetButtonsFont(&afxGlobalData.fontBold);

	return TRUE;
}
/*
BOOL CMainFrame::CreateOutlookBar(CMyOutlookBar& bar, UINT uiID, CMFCShellTreeCtrl& tree, CCalendarBar& calendar, int nInitialWidth)
{
	//bar.SetMode2003();

	BOOL bNameValid;
	CString strTemp;
	bNameValid = strTemp.LoadString(IDS_SHORTCUTS);
	ASSERT(bNameValid);
	if (!bar.Create(strTemp, this, CRect(0, 0, nInitialWidth, 32000), uiID, WS_CHILD | WS_VISIBLE | CBRS_LEFT))
	{
		return FALSE; // 未能创建
	}

	CMFCOutlookBarTabCtrl* pOutlookBar = (CMFCOutlookBarTabCtrl*)bar.GetUnderlyingWindow();

	if (pOutlookBar == NULL)
	{
		ASSERT(FALSE);
		return FALSE;
	}

	pOutlookBar->EnableInPlaceEdit(TRUE);

	static UINT uiPageID = 1;

	// 可浮动，可自动隐藏，可调整大小，但不能关闭
	DWORD dwStyle = AFX_CBRS_FLOAT | AFX_CBRS_AUTOHIDE | AFX_CBRS_RESIZE;

	CRect rectDummy(0, 0, 0, 0);
	const DWORD dwTreeStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS;

	DWORD dwPaneStyle = AFX_DEFAULT_TOOLBAR_STYLE | CBRS_FLOAT_MULTI;

	if(m_wndRibbonBarPane.Create(&bar,dwPaneStyle,uiPageID++,dwStyle))
	{
		m_wndRibbonBarPane.SetOwner(this);
		m_wndRibbonBarPane.EnableTextLabels();

		bar.AddPane(&m_wndRibbonBarPane,_T("Pane1"));
	}

	tree.Create(dwTreeStyle, rectDummy, &bar, 1200);
	bNameValid = strTemp.LoadString(IDS_FOLDERS);
	ASSERT(bNameValid);
	pOutlookBar->AddControl(&tree, strTemp, uiPageID++, TRUE, dwStyle);

	calendar.Create(rectDummy, &bar, 1201);
	bNameValid = strTemp.LoadString(IDS_CALENDAR);
	ASSERT(bNameValid);
	pOutlookBar->AddControl(&calendar, strTemp, uiPageID++, TRUE, dwStyle);

	bar.SetPaneStyle(bar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	pOutlookBar->SetImageList(theApp.m_bHiColorIcons ? IDB_PAGES_HC : IDB_PAGES, 24);
	pOutlookBar->SetToolbarImageList(theApp.m_bHiColorIcons ? IDB_PAGES_SMALL_HC : IDB_PAGES_SMALL, 16);
	pOutlookBar->RecalcLayout();


	BOOL bAnimation = theApp.GetInt(_T("OutlookAnimation"), TRUE);
	CMFCOutlookBarTabCtrl::EnableAnimation(bAnimation);

	bar.SetButtonsFont(&afxGlobalData.fontBold);

	return TRUE;
}*/

BOOL CMainFrame::CreateCaptionBar()
{

	if (!m_wndCaptionBar.Create(WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, this, ID_VIEW_CAPTION_BAR, -1, TRUE))
	{
		TRACE0("未能创建标题栏\n");
		return FALSE;
	}
	m_wndCaptionBar.ShowWindow(SW_HIDE);

#ifdef USING_RIB_CAPTION
	BOOL bNameValid;

	CString strTemp, strTemp2;
	bNameValid = strTemp.LoadString(IDS_CAPTION_BUTTON);
	ASSERT(bNameValid);
	m_wndCaptionBar.SetButton(strTemp, ID_TOOLS_OPTIONS, CMFCCaptionBar::ALIGN_LEFT, FALSE);
	bNameValid = strTemp.LoadString(IDS_CAPTION_BUTTON_TIP);
	ASSERT(bNameValid);
	m_wndCaptionBar.SetButtonToolTip(strTemp);

	bNameValid = strTemp.LoadString(IDS_CAPTION_TEXT);
	ASSERT(bNameValid);
	m_wndCaptionBar.SetText(strTemp, CMFCCaptionBar::ALIGN_LEFT);

	m_wndCaptionBar.SetBitmap(IDB_INFO, RGB(255, 255, 255), FALSE, CMFCCaptionBar::ALIGN_LEFT);
	bNameValid = strTemp.LoadString(IDS_CAPTION_IMAGE_TIP);
	ASSERT(bNameValid);
	bNameValid = strTemp2.LoadString(IDS_CAPTION_IMAGE_TEXT);
	ASSERT(bNameValid);
	m_wndCaptionBar.SetImageToolTip(strTemp, strTemp2);
#else
	m_wndCaptionBar.SetFlatBorder();
	m_wndCaptionBar.SetFont(&afxGlobalData.fontBold);
#endif
	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
#ifdef USING_RIB_CAPTION
		m_wndRibbonBar.SetWindows7Look(FALSE);
#endif
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
#ifdef USING_RIB_CAPTION
		m_wndRibbonBar.SetWindows7Look(FALSE);
#endif
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
#ifdef USING_RIB_CAPTION
		m_wndRibbonBar.SetWindows7Look(FALSE);
#endif
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
#ifdef USING_RIB_CAPTION
		m_wndRibbonBar.SetWindows7Look(FALSE);
#endif
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
#ifdef USING_RIB_CAPTION
		m_wndRibbonBar.SetWindows7Look(FALSE);
#endif
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		CDockingManager::SetDockingMode(DT_SMART);
#ifdef USING_RIB_CAPTION
		m_wndRibbonBar.SetWindows7Look(FALSE);
#endif
		break;

	case ID_VIEW_APPLOOK_WINDOWS_7:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
		CDockingManager::SetDockingMode(DT_SMART);
#ifdef USING_RIB_CAPTION
		m_wndRibbonBar.SetWindows7Look(TRUE);
#endif
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
#ifdef USING_RIB_CAPTION
		m_wndRibbonBar.SetWindows7Look(FALSE);
#endif
	}

	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}

void CMainFrame::OnViewCaptionBar()
{
	m_wndCaptionBar.ShowWindow(m_wndCaptionBar.IsVisible() ? SW_HIDE : SW_SHOW);
	RecalcLayout(FALSE);
}

void CMainFrame::OnComdPaneItem()
{
	CMyADOConnEx myADOConn;
	if(myADOConn.GetLocalConncetSqlStr().IsEmpty())
	{
		CLocalConfigureDlg dlg;
		if(IDOK != dlg.DoModal())
		{
			return;			
		}
	}
	CString strStatusBar = _T("");
	strStatusBar.Format(_T("当前数据库：%s"),myADOConn.m_strDBName);
	SetStatusBarPane(1,strStatusBar);

	//by zhangyx 2017//11//29
	CQLSvrMgnView *pView = (CQLSvrMgnView *)GetActiveView();
	UINT nID = LOWORD(GetCurrentMessage()->wParam);
	if (pView)
	{
		pView->OnActiveTabDlg(nID, 0);
	}
}

void CMainFrame::OnUpdateViewCaptionBar(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_wndCaptionBar.IsVisible());
}

void CMainFrame::OnOptions()
{
#ifdef USING_RIB_CAPTION
	CMFCRibbonCustomizeDialog *pOptionsDlg = new CMFCRibbonCustomizeDialog(this, &m_wndRibbonBar);
	ASSERT(pOptionsDlg != NULL);

	pOptionsDlg->DoModal();
	delete pOptionsDlg;
#endif
}


void CMainFrame::OnUpdateFrameTitle(BOOL bAddToTitle)
{
	// TODO: 在此添加专用代码和/或调用基类
	CString strSysTitle = _T("琪利服务");
	//strSysTitle.LoadString(IDS_FRAME_TITLE);
	SetWindowText(strSysTitle);

	CFrameWndEx::OnUpdateFrameTitle(bAddToTitle);
}


void CMainFrame::OnUpdateFrameMenu(HMENU hMenuAlt)
{
	// TODO: 在此添加专用代码和/或调用基类

	CFrameWndEx::OnUpdateFrameMenu(hMenuAlt);
}

BOOL CMainFrame::SetStatusBarPane(int nIndex,CString strText)
{
	BOOL bRet = FALSE;
	if(m_wndStatusBar.GetSafeHwnd())
	{
		int nCount = m_wndStatusBar.GetCount();
		if((nIndex < nCount) && (nIndex > -1))
		{
			bRet = TRUE;
			m_wndStatusBar.SetPaneText(nIndex, strText, TRUE);
		}
		else
		{
			bRet = FALSE;
		}
	}
	else
	{
		bRet = FALSE;
	}
	return bRet;
}


void CMainFrame::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
    ::ShowWindow(AfxGetMainWnd()->GetSafeHwnd(),SW_HIDE);
}

afx_msg LRESULT CMainFrame::OnAdoconnMsg(WPARAM wParam, LPARAM lParam)
{
	LPCTSTR pMsg = (LPCTSTR)lParam;
	if (pMsg)
	{
		CString strMsg = _T("数据库执行失败！");

      strMsg += pMsg;
		PTLOG("数据库操作失败");
		theApp.OnShowDesktopAlert(strMsg,COLOR_TIP_FAIL,3,NULL,CPoint(-1,-1));
	}


   return 0;
}

LRESULT CMainFrame::OnTrayMsg( WPARAM wParam, LPARAM lParam )
{
   switch (lParam)
   {
   case WM_LBUTTONDBLCLK: //双击托盘图标
      {
         ShowWindow(SW_SHOWNORMAL);
         SetForegroundWindow();
      }
      break;
   case WM_RBUTTONUP: //右击
      {
         CMenu menu;
         menu.LoadMenu(IDR_MENU_TRAY); //载入事先定义的选单
         CMenu* pMenu=menu.GetSubMenu(0);
         SetForegroundWindow();
         CPoint pos;
         GetCursorPos(&pos);

         int ntt = pMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,pos.x,pos.y, this);
         if (ntt == IDR_MENU_TRAY)
         {
            ::ShowWindow(AfxGetMainWnd()->GetSafeHwnd(),SW_SHOWNORMAL);
            if(IDOK == MessageBox(_T("确定退出吗？"),_T("温馨提示："),MB_ICONQUESTION|MB_OKCANCEL))
            {
               CFrameWndEx::OnClose();
               //::ShowWindow(AfxGetMainWnd()->GetSafeHwnd(),SW_HIDE);
            }
         }
      }

      break;
   }
   return 0;
}


void CMainFrame::InitTray()
{
   //托盘初始化
   m_nid.cbSize  = (DWORD)sizeof(NOTIFYICONDATA);

   m_nid.hWnd    = AfxGetMainWnd()->GetSafeHwnd();

   m_nid.uID     = IDR_MAINFRAME;

   m_nid.uFlags  = NIF_ICON | NIF_MESSAGE | NIF_TIP ;

   m_nid.uCallbackMessage = WM_TRAY;             // 自定义的消息名称
   m_nid.hIcon   = ::LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));
   wcscpy_s(m_nid.szTip,_T("QLSvrMgn"));
   Shell_NotifyIcon(NIM_ADD, &m_nid);                // 在托盘区添加图标
}

void CMainFrame::OnExit()
{
   if(IDOK == MessageBox(_T("确定退出吗？"),_T("温馨提示："),MB_ICONQUESTION|MB_OKCANCEL))
   {
      CFrameWndEx::OnClose();
      //::ShowWindow(AfxGetMainWnd()->GetSafeHwnd(),SW_HIDE);
   }
}
