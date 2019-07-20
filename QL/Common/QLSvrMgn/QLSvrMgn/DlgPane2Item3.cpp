// DlgPane2Item3.cpp : 实现文件
//

#include "stdafx.h"
#include "QLSvrMgn.h"
#include "DlgPane2Item3.h"


// CDlgPane2Item3 对话框

IMPLEMENT_DYNAMIC(CDlgPane2Item3, CTabDialog)

CDlgPane2Item3::CDlgPane2Item3(CWnd* pParent /*=NULL*/)
	: CTabDialog(CDlgPane2Item3::IDD, pParent)
{

}

CDlgPane2Item3::~CDlgPane2Item3()
{
}

void CDlgPane2Item3::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgPane2Item3, CTabDialog)
END_MESSAGE_MAP()


// CDlgPane2Item3 消息处理程序
