// DlgLoading.cpp : 实现文件
//

#include "stdafx.h"
#include "QLSvrMgn.h"
#include "DlgLoading.h"
#include "afxdialogex.h"


// CDlgLoading 对话框

IMPLEMENT_DYNAMIC(CDlgLoading, CDialogEx)

CDlgLoading::CDlgLoading(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgLoading::IDD, pParent)
{
	m_bInitModal = FALSE;
}

CDlgLoading::~CDlgLoading()
{
}

void CDlgLoading::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_LOADING, m_ctrLoadingGif);
}


BEGIN_MESSAGE_MAP(CDlgLoading, CDialogEx)
END_MESSAGE_MAP()


// CDlgLoading 消息处理程序
BOOL CDlgLoading::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CRect rcMain;
	GetWindowRect(&rcMain);

	LPCTSTR szRes = MAKEINTRESOURCE(IDB_LOADING);
	if (m_ctrLoadingGif.Load(szRes,_T("GIF"))) 
	{	
		m_ctrLoadingGif.Draw(); 
		//m_ctrLoadingGif.SetBkColor(RGB(255,0,0));
	}

	CSize szPic = m_ctrLoadingGif.GetSize();
	rcMain.right = rcMain.left + szPic.cx;
	rcMain.bottom = rcMain.top + szPic.cy;
	MoveWindow(rcMain);

	::SetWindowLong(m_hWnd, GWL_EXSTYLE, WS_EX_TOOLWINDOW );

#ifndef USING_LIB_BCGP
	BringWindowToTop();
#endif // USING_LIB_BCGP
	SetWindowPos(&CWnd::wndTopMost,0,0,0,0, SWP_NOMOVE|SWP_NOSIZE); //置顶

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgLoading::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
	m_bInitModal = FALSE;
	CDialogEx::OnCancel();
}

INT_PTR CDlgLoading::DoModal()
{
	// TODO: 在此添加专用代码和/或调用基类
	m_bInitModal = TRUE;
	return CDialogEx::DoModal();
}
