// TabDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "../../QLSvrMgn.h"
#include "TabDialog.h"
#include "afxdialogex.h"


// CTabDialog �Ի���

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


// CTabDialog ��Ϣ�������

BOOL CTabDialog::Create(UINT nIDTemplate, CWnd* pParentWnd,WPARAM wpData/*=0*/)
{
	// TODO: �ڴ����ר�ô����/����û���

	m_wpData = wpData;

	return CDialogEx::Create(nIDTemplate, pParentWnd);
}

//��ֹ�ڶԻ����а�Enter���Ի�����ʧ
LRESULT CTabDialog::OnGetDefID(WPARAM wParam,LPARAM lParam) 
{  
	return MAKELONG(0,DC_HASDEFID);    
}  