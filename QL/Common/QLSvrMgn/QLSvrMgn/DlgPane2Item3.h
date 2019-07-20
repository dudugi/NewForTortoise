#pragma once
#include "MyCtrlEx\TabDlg\TabDialog.h"


// CDlgPane2Item3 对话框

class CDlgPane2Item3 : public CTabDialog
{
	DECLARE_DYNAMIC(CDlgPane2Item3)

public:
	CDlgPane2Item3(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgPane2Item3();

// 对话框数据
	enum { IDD = IDD_DLG_PANE2_ITEM3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
