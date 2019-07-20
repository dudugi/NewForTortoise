// MyOutlookBar.cpp : 实现文件
//

#include "stdafx.h"
#include "../../QLSvrMgn.h"
#include "MyOutlookBar.h"


// CMyOutlookBar

IMPLEMENT_DYNAMIC(CMyOutlookBar, CMFCOutlookBar)

CMyOutlookBar::CMyOutlookBar()
{

}

CMyOutlookBar::~CMyOutlookBar()
{
}


BEGIN_MESSAGE_MAP(CMyOutlookBar, CMFCOutlookBar)
END_MESSAGE_MAP()



// CMyOutlookBar 消息处理程序

BOOL CMyOutlookBar::Create(LPCTSTR lpszCaption, CWnd* pParentWnd, const RECT& rect, UINT nID, DWORD dwStyle, DWORD dwControlBarStyle/* = AFX_CBRS_RESIZE*/, CCreateContext* pContext/* = NULL*/)
{
	// TODO: 在此添加专用代码和/或调用基类
	SetMode2003();

	//eg:bar.Create(_T("Shortcuts"), this, CRect(0, 0, nInitialWidth, 32000), uiID, WS_CHILD | WS_VISIBLE | CBRS_LEFT)
	return CMFCOutlookBar::Create(lpszCaption, pParentWnd, rect, nID, dwStyle, dwControlBarStyle,pContext);
}


BOOL CMyOutlookBar::AddPane(CMyOutlookBarPane* pWndPane, LPCTSTR lpszName, int nImageID/* = -1*/, BOOL bDetachable/* = TRUE*/,
	DWORD dwControlBarStyle/* = AFX_CBRS_FLOAT | AFX_CBRS_CLOSE | AFX_CBRS_RESIZE | AFX_CBRS_AUTOHIDE*/)
{
	BOOL  bRet = TRUE;

	if (pWndPane && IsWindow(GetSafeHwnd()))
	{
		CMFCOutlookBarTabCtrl* pOutlookBar = (CMFCOutlookBarTabCtrl*)GetUnderlyingWindow();
		if (pOutlookBar == NULL)
		{
			ASSERT(FALSE);
			return FALSE;
		}

		if (!pOutlookBar->IsInPlaceEdit())
		{
			pOutlookBar->EnableInPlaceEdit(TRUE);
		}
		
		pOutlookBar->AddControl(pWndPane, lpszName, nImageID, bDetachable, dwControlBarStyle);
		pWndPane->EnableDocking(CBRS_ALIGN_ANY);
		pWndPane->SetDefaultState();
	}
	else
	{
		bRet = FALSE;
	}

	return bRet;
}
