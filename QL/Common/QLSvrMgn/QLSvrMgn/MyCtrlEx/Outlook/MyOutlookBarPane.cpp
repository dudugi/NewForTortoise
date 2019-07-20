// MyOutlookBarPane.cpp : ʵ���ļ�
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



// CMyOutlookBarPane ��Ϣ�������


BOOL CMyOutlookBarPane::Create(CWnd* pParentWnd, DWORD dwStyle/* = AFX_DEFAULT_TOOLBAR_STYLE*/, UINT uiID/* = (UINT)-1*/, DWORD dwControlBarStyle/* = 0*/)
{
	// TODO: �ڴ����ר�ô����/����û���
	//eg:pane.Create(&bar, dwPaneStyle, uiPageID++, dwStyle);
	return CMFCOutlookBarPane::Create(pParentWnd, dwStyle, uiID, dwControlBarStyle);
}


BOOL CMyOutlookBarPane::AddItem(const int iIconIndex, LPCTSTR lpszLabel, UINT iIdCommand, CImageList& images,int iInsertAt/* = -1*/,BOOL bAlphaBlend/* = FALSE*/)
{
	return AddButton(images.ExtractIcon(iIconIndex), lpszLabel, iIdCommand,iInsertAt, bAlphaBlend);
}