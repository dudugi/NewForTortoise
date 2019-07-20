#pragma once
#include "afxcmn.h"


// CDlgTask �Ի���

class CDlgTask : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgTask)

public:
	CDlgTask(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgTask();

// �Ի�������
	enum { IDD = IDD_DLG_TASK};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()
public:
   void refreshData(); //����ˢ��
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
