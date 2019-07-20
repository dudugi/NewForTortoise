#pragma once
#include "MyCtrlEx/TabDlg/TabDialog.h"


// CDlgWelcome 对话框

class CDlgWelcome : public CTabDialog
{
	DECLARE_DYNAMIC(CDlgWelcome)

public:
	CDlgWelcome(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgWelcome();

	void  ShowWaterMark(CDC* pDC);

// 对话框数据
	enum { IDD = IDD_DLG_WELCOME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};
