#pragma once
#include "afxcmn.h"


// CDlgTask 对话框

class CDlgTask : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgTask)

public:
	CDlgTask(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgTask();

// 对话框数据
	enum { IDD = IDD_DLG_TASK};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
   void refreshData(); //任务刷新
   afx_msg void OnBnClickedButtonSupend();
   afx_msg void OnBnClickedButton2();
   afx_msg void OnBnClickedButtonStart();
   virtual BOOL OnInitDialog();
   CListCtrl m_TaskBackList;
   CListCtrl m_TaskHistoryList;
   afx_msg void OnTimer(UINT_PTR nIDEvent);
   afx_msg void OnContextMenu(CWnd * ,CPoint point);
   afx_msg void OnDeleteTask();
};
