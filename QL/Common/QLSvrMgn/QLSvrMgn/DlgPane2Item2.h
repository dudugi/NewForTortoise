#pragma once
#include "MyCtrlEx\TabDlg\TabDialog.h"
#include "FileTxt.h"

// CDlgPane2Item2 �Ի���

class CDlgPane2Item2 : public CTabDialog
{
	DECLARE_DYNAMIC(CDlgPane2Item2)

public:
	CDlgPane2Item2(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgPane2Item2();

// �Ի�������
	enum { IDD = IDD_DLG_PANE2_ITEM2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
   CDirectory m_CDirectroy;
   CFileTxt m_FileTxt;
public:
   afx_msg void OnBnClickedCarryDatabaseButton();
   afx_msg void OnBnClickedBtnCarry();
   CString CompareDataName(CString strPath);
};
