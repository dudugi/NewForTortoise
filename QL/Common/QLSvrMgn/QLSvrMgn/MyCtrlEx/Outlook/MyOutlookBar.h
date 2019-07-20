#pragma once
#include "MyOutlookBarPane.h"


// CMyOutlookBar

class CMyOutlookBar : public CMFCOutlookBar
{
	DECLARE_DYNAMIC(CMyOutlookBar)

public:
	CMyOutlookBar();
	virtual ~CMyOutlookBar();
	BOOL AddPane(CMyOutlookBarPane* pWndPane, LPCTSTR lpszName, int nImageID = -1, BOOL bDetachable = TRUE,
		DWORD dwControlBarStyle = AFX_CBRS_FLOAT | AFX_CBRS_CLOSE | AFX_CBRS_RESIZE | AFX_CBRS_AUTOHIDE);

	virtual BOOL AllowShowOnPaneMenu() const { return TRUE; }
	virtual void GetPaneName(CString& strName) const { BOOL bNameValid = strName.LoadString(IDS_OUTLOOKBAR); ASSERT(bNameValid); if (!bNameValid) strName.Empty(); }
	//by zhangyx 2017//11//29 消除鼠标自带触发右键菜单功能
	virtual BOOL OnShowControlBarMenu(CPoint point) { return FALSE; }

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL Create(LPCTSTR lpszCaption, CWnd* pParentWnd, const RECT& rect, UINT nID, DWORD dwStyle, DWORD dwControlBarStyle = AFX_CBRS_RESIZE, CCreateContext* pContext = NULL);
};


