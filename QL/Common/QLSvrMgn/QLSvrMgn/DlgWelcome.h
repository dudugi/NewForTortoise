#pragma once
#include "MyCtrlEx/TabDlg/TabDialog.h"


// CDlgWelcome �Ի���

class CDlgWelcome : public CTabDialog
{
	DECLARE_DYNAMIC(CDlgWelcome)

public:
	CDlgWelcome(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgWelcome();

	void  ShowWaterMark(CDC* pDC);

// �Ի�������
	enum { IDD = IDD_DLG_WELCOME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};
