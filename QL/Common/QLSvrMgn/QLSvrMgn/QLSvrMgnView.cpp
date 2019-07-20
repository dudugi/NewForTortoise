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

// QLSvrMgnView.cpp : CQLSvrMgnView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "QLSvrMgn.h"
#endif

#include "QLSvrMgnDoc.h"
#include "QLSvrMgnView.h"
#include "MainFrm.h"
#include "LocalConfigureDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CQLSvrMgnView

IMPLEMENT_DYNCREATE(CQLSvrMgnView, CFormView)

BEGIN_MESSAGE_MAP(CQLSvrMgnView, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
	ON_COMMAND(ID_CONFIGURE, &CQLSvrMgnView::OnConfigure)
   ON_UPDATE_COMMAND_UI(IDM_AUTO_START, &CQLSvrMgnView::OnUpdateAutoStart)
   ON_UPDATE_COMMAND_UI(IDM_AUTO_START_HIDE, &CQLSvrMgnView::OnUpdateAutoStartHide)
   ON_COMMAND(IDM_AUTO_START, &CQLSvrMgnView::OnAutoStart)
   ON_COMMAND(IDM_AUTO_START_HIDE, &CQLSvrMgnView::OnAutoStartHide)
END_MESSAGE_MAP()

// CQLSvrMgnView 构造/析构

CQLSvrMgnView::CQLSvrMgnView()
	: CFormView(CQLSvrMgnView::IDD)
{
	// TODO: 在此处添加构造代码

}

CQLSvrMgnView::~CQLSvrMgnView()
{
}

void CQLSvrMgnView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CQLSvrMgnView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	cs.style &= ~WS_BORDER;//除去凹陷风格

	return CFormView::PreCreateWindow(cs);
}

void CQLSvrMgnView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	//ResizeParentToFit();//最大化，故屏蔽


	//初始化
	InitMyTabCtrl();

   //菜单初始化
   /*CMenu *pMenu,*pMenuSub;
   pMenu = new CMenu;
   pMenu->LoadMenu(IDR_MAINFRAME);
   pMenuSub=pMenu->GetSubMenu(0);
   pMenuSub->CheckMenuItem(IDM_AUTO_START,FALSE);
   pMenuSub->CheckMenuItem(IDM_AUTO_START,FALSE);*/

}

void CQLSvrMgnView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CQLSvrMgnView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CQLSvrMgnView 诊断

#ifdef _DEBUG
void CQLSvrMgnView::AssertValid() const
{
	CFormView::AssertValid();
}

void CQLSvrMgnView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CQLSvrMgnDoc* CQLSvrMgnView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CQLSvrMgnDoc)));
	return (CQLSvrMgnDoc*)m_pDocument;
}
#endif //_DEBUG


// CQLSvrMgnView 消息处理程序


void CQLSvrMgnView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if(SIZE_MINIMIZED == nType) return;//最小化不做任何处理

	if (SIZE_RESTORED == nType)
	{
		if (::IsWindow(m_ctrMyTabCtrl.GetSafeHwnd()))
		{
			m_ctrMyTabCtrl.SetWindowPos(this,-1,-1, cx-2, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
			m_ctrMyTabCtrl.ShowWindow(SW_SHOW);
		}
	}

	ShowScrollBar(SB_BOTH,FALSE);//禁用水平、竖直滚动条
}

void CQLSvrMgnView::InitMyTabCtrl()
{
	CRect rc;
	this->GetWindowRect(rc);
	ScreenToClient(&rc);
	rc.DeflateRect(1,1);
	m_ctrMyTabCtrl.Create(CMFCTabCtrl::STYLE_3D_SCROLLED,rc,this,1,CMFCTabCtrl::LOCATION_TOP);
	m_ctrMyTabCtrl.EnableAutoColor (FALSE);
	m_ctrMyTabCtrl.EnableCustomToolTips (TRUE);
	m_ctrMyTabCtrl.SetTabBorderSize (0);
	m_ctrMyTabCtrl.EnableTabSwap(FALSE);//拖拽
	m_ctrMyTabCtrl.SetActiveTabBoldFont(TRUE);

	CString strNavigationTitle = _T("欢迎界面");
// 	strNavigationTitle.LoadString(IDS_TABTITLE_NAVIGATION);
 	m_ctrMyTabCtrl.SetActiveTab(&m_DlgWelcome,IDD_DLG_WELCOME,strNavigationTitle);

	m_ctrMyTabCtrl.ShowWindow(SW_SHOW);
}


void CQLSvrMgnView::OnActiveTabDlg(int nMenuID,WPARAM wpData)
{
	int nDlgID;
	CString strDlgTitle;
	CWnd * pWnd = m_dlgFactory.factoryMethod(nMenuID,nDlgID,strDlgTitle);

	if (pWnd)
	{ 
		m_ctrMyTabCtrl.SetActiveTab(pWnd,nDlgID,strDlgTitle,wpData);
	   CMainFrame *pMainFrame = (CMainFrame *)AfxGetMainWnd();
	   if(pMainFrame)
	   {
		   pMainFrame->SetStatusBarPane(0, strDlgTitle);
	   }
	}
}

void CQLSvrMgnView::OnConfigure()
{
	// TODO: 在此添加命令处理程序代码
	CLocalConfigureDlg localConfigureDlg;
	localConfigureDlg.DoModal();
}


void CQLSvrMgnView::OnUpdateAutoStart(CCmdUI *pCmdUI)
{
   // TODO: 在此添加命令更新用户界面处理程序代码
      pCmdUI->SetCheck(theApp.m_bAutoStart);
}


void CQLSvrMgnView::OnUpdateAutoStartHide(CCmdUI *pCmdUI)
{
   // TODO: 在此添加命令更新用户界面处理程序代码

  if (theApp.m_bAutoStart)
  {
     pCmdUI->SetCheck(theApp.m_bStartHide);
     
  }
}


void CQLSvrMgnView::OnAutoStart()
{
   // TODO: 在此添加命令处理程序代码
   CMenu Menu,*pMenuSub;
   Menu.LoadMenu(IDR_MAINFRAME);
   pMenuSub = Menu.GetSubMenu(0);
   theApp.m_bAutoStart = !theApp.m_bAutoStart;
   //pMenuSub->CheckMenuItem(IDM_AUTO_START,theApp.m_bAutoStart);
}


void CQLSvrMgnView::OnAutoStartHide()
{
   // TODO: 在此添加命令处理程序代码
   CMenu Menu,*pMenuSub;
   Menu.LoadMenu(IDR_MAINFRAME);
   pMenuSub = Menu.GetSubMenu(0);
   theApp.m_bStartHide = !theApp.m_bStartHide;
   //pMenuSub->CheckMenuItem(IDM_AUTO_START_HIDE,theApp.m_bStartHide);
   
}
