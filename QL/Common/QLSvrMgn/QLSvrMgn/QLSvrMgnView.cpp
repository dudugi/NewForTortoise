// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// (��Fluent UI��)����ʾ�������ο���
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������  
// http://msdn.microsoft.com/officeui��
//
// ��Ȩ����(C) Microsoft Corporation
// ��������Ȩ����

// QLSvrMgnView.cpp : CQLSvrMgnView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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

// CQLSvrMgnView ����/����

CQLSvrMgnView::CQLSvrMgnView()
	: CFormView(CQLSvrMgnView::IDD)
{
	// TODO: �ڴ˴���ӹ������

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
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	cs.style &= ~WS_BORDER;//��ȥ���ݷ��

	return CFormView::PreCreateWindow(cs);
}

void CQLSvrMgnView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	//ResizeParentToFit();//��󻯣�������


	//��ʼ��
	InitMyTabCtrl();

   //�˵���ʼ��
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


// CQLSvrMgnView ���

#ifdef _DEBUG
void CQLSvrMgnView::AssertValid() const
{
	CFormView::AssertValid();
}

void CQLSvrMgnView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CQLSvrMgnDoc* CQLSvrMgnView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CQLSvrMgnDoc)));
	return (CQLSvrMgnDoc*)m_pDocument;
}
#endif //_DEBUG


// CQLSvrMgnView ��Ϣ�������


void CQLSvrMgnView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	if(SIZE_MINIMIZED == nType) return;//��С�������κδ���

	if (SIZE_RESTORED == nType)
	{
		if (::IsWindow(m_ctrMyTabCtrl.GetSafeHwnd()))
		{
			m_ctrMyTabCtrl.SetWindowPos(this,-1,-1, cx-2, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
			m_ctrMyTabCtrl.ShowWindow(SW_SHOW);
		}
	}

	ShowScrollBar(SB_BOTH,FALSE);//����ˮƽ����ֱ������
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
	m_ctrMyTabCtrl.EnableTabSwap(FALSE);//��ק
	m_ctrMyTabCtrl.SetActiveTabBoldFont(TRUE);

	CString strNavigationTitle = _T("��ӭ����");
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
	// TODO: �ڴ���������������
	CLocalConfigureDlg localConfigureDlg;
	localConfigureDlg.DoModal();
}


void CQLSvrMgnView::OnUpdateAutoStart(CCmdUI *pCmdUI)
{
   // TODO: �ڴ������������û����洦��������
      pCmdUI->SetCheck(theApp.m_bAutoStart);
}


void CQLSvrMgnView::OnUpdateAutoStartHide(CCmdUI *pCmdUI)
{
   // TODO: �ڴ������������û����洦��������

  if (theApp.m_bAutoStart)
  {
     pCmdUI->SetCheck(theApp.m_bStartHide);
     
  }
}


void CQLSvrMgnView::OnAutoStart()
{
   // TODO: �ڴ���������������
   CMenu Menu,*pMenuSub;
   Menu.LoadMenu(IDR_MAINFRAME);
   pMenuSub = Menu.GetSubMenu(0);
   theApp.m_bAutoStart = !theApp.m_bAutoStart;
   //pMenuSub->CheckMenuItem(IDM_AUTO_START,theApp.m_bAutoStart);
}


void CQLSvrMgnView::OnAutoStartHide()
{
   // TODO: �ڴ���������������
   CMenu Menu,*pMenuSub;
   Menu.LoadMenu(IDR_MAINFRAME);
   pMenuSub = Menu.GetSubMenu(0);
   theApp.m_bStartHide = !theApp.m_bStartHide;
   //pMenuSub->CheckMenuItem(IDM_AUTO_START_HIDE,theApp.m_bStartHide);
   
}
