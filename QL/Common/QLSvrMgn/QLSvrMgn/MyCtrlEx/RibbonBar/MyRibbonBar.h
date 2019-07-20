#pragma once


class CMyRibbonStatusBar : public CMFCRibbonStatusBar
{
	DECLARE_DYNAMIC(CMyRibbonStatusBar)

public:
	CMyRibbonStatusBar();
	virtual ~CMyRibbonStatusBar();

protected:
	DECLARE_MESSAGE_MAP()
};

// CMyRibbonBar

class CMyRibbonBar : public CMFCRibbonBar
{
	DECLARE_DYNAMIC(CMyRibbonBar)

public:
	CMyRibbonBar();
	virtual ~CMyRibbonBar();

protected:
	DECLARE_MESSAGE_MAP()
};


