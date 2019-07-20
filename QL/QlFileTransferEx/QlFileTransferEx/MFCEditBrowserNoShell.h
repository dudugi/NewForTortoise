#pragma once


// CMFCEditBrowserNoShell

class CMFCEditBrowserNoShell : public CMFCEditBrowseCtrl
{
	DECLARE_DYNAMIC(CMFCEditBrowserNoShell)

public:
	CMFCEditBrowserNoShell();
	virtual ~CMFCEditBrowserNoShell();

	virtual void OnBrowse();

protected:
	DECLARE_MESSAGE_MAP()
};


