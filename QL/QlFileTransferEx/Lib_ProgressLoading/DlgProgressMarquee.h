#pragma once
#include "resource.h"
#include "afxcmn.h"


// CDlgProgressMarquee 对话框

class CDlgProgressMarquee : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgProgressMarquee)

public:
	CDlgProgressMarquee(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgProgressMarquee();

// 对话框数据
	enum { IDD = IDD_DLG_PROGRESSMARQUE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
   virtual BOOL OnInitDialog();
   CProgressCtrl m_progressCtrl;
   afx_msg void OnTimer(UINT_PTR nIDEvent);
};
