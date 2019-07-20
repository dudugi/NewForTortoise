// MyStatusBar.cpp : 实现文件
//

#include "stdafx.h"
#include "MyStatusBar.h"


// CMyStatusBar

IMPLEMENT_DYNAMIC(CMyStatusBar, CMFCStatusBar)

CMyStatusBar::CMyStatusBar()
{

}

CMyStatusBar::~CMyStatusBar()
{
}


BEGIN_MESSAGE_MAP(CMyStatusBar, CMFCStatusBar)
END_MESSAGE_MAP()



// CMyStatusBar 消息处理程序

CSize CMyStatusBar::CalcFixedLayout(BOOL bStretch, BOOL bHorz)
{
	CSize size;
	size.cx = (bStretch && bHorz ? 32767 : 0);
	//size.cy = (bStretch && !bHorz ? 32767 : 0);
	int k = GetSystemMetrics(SM_CYCAPTION);
	size.cy = k * 1.2;
	return size;
}
