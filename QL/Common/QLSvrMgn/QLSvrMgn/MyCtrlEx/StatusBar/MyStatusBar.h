#pragma once


// CMyStatusBar

class CMyStatusBar : public CMFCStatusBar
{
	DECLARE_DYNAMIC(CMyStatusBar)

public:
	CMyStatusBar();
	virtual ~CMyStatusBar();

protected:
	DECLARE_MESSAGE_MAP()

public:
	virtual CSize CalcFixedLayout(BOOL bStretch, BOOL bHorz);
};


