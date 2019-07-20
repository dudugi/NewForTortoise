#pragma once


// CMyOutlookBarPane

class CMyOutlookBarPane : public CMFCOutlookBarPane
{
	DECLARE_DYNAMIC(CMyOutlookBarPane)

public:
	CMyOutlookBarPane();
	virtual ~CMyOutlookBarPane();
	BOOL AddItem(const int iIconIndex, LPCTSTR lpszLabel, UINT iIdCommand, CImageList& images, int iInsertAt = -1, BOOL bAlphaBlend = FALSE);
	
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL Create(CWnd* pParentWnd, DWORD dwStyle = AFX_DEFAULT_TOOLBAR_STYLE, UINT uiID = (UINT)-1, DWORD dwControlBarStyle = 0);	
};


