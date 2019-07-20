// MyOutlookBarPane.cpp : 实现文件
//

#include "stdafx.h"
#include "../../QLSvrMgn.h"
#include "MyOutlookBarPane.h"


// CMyOutlookBarPane

IMPLEMENT_DYNAMIC(CMyOutlookBarPane, CMFCOutlookBarPane)

CMyOutlookBarPane::CMyOutlookBarPane()
{

}

CMyOutlookBarPane::~CMyOutlookBarPane()
{
}


BEGIN_MESSAGE_MAP(CMyOutlookBarPane, CMFCOutlookBarPane)
END_MESSAGE_MAP()



// CMyOutlookBarPane 消息处理程序


BOOL CMyOutlookBarPane::Create(CWnd* pParentWnd, DWORD dwStyle/* = AFX_DEFAULT_TOOLBAR_STYLE*/, UINT uiID/* = (UINT)-1*/, DWORD dwControlBarStyle/* = 0*/)
{
	// TODO: 在此添加专用代码和/或调用基类
	//eg:pane.Create(&bar, dwPaneStyle, uiPageID++, dwStyle);
	return CMFCOutlookBarPane::Create(pParentWnd, dwStyle, uiID, dwControlBarStyle);
}


BOOL CMyOutlookBarPane::AddItem(const int iIconIndex, LPCTSTR lpszLabel, UINT iIdCommand, CImageList& images,int iInsertAt/* = -1*/,BOOL bAlphaBlend/* = FALSE*/)
{
	return AddButton(images.ExtractIcon(iIconIndex), lpszLabel, iIdCommand,iInsertAt, bAlphaBlend);
}