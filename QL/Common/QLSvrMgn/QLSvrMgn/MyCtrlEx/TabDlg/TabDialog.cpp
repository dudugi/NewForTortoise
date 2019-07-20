// TabDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "../../QLSvrMgn.h"
#include "TabDialog.h"
#include "afxdialogex.h"


// CTabDialog 对话框

IMPLEMENT_DYNAMIC(CTabDialog, CDialogEx)

CTabDialog::CTabDialog(UINT nIDD,CWnd* pParent /*=NULL*/)
	:CDialogEx(nIDD, pParent)
{
	m_wpData = 0;
}


CTabDialog::~CTabDialog()
{
}


BEGIN_MESSAGE_MAP(CTabDialog, CDialogEx)
	ON_MESSAGE(DM_GETDEFID,	&CTabDialog::OnGetDefID)
END_MESSAGE_MAP()


// CTabDialog 消息处理程序

BOOL CTabDialog::Create(UINT nIDTemplate, CWnd* pParentWnd,WPARAM wpData/*=0*/)
{
	// TODO: 在此添加专用代码和/或调用基类

	m_wpData = wpData;

	return CDialogEx::Create(nIDTemplate, pParentWnd);
}

//防止在对话框中安Enter键对话框消失
LRESULT CTabDialog::OnGetDefID(WPARAM wParam,LPARAM lParam) 
{  
	return MAKELONG(0,DC_HASDEFID);    
}  