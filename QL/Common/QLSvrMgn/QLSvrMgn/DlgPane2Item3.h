#pragma once
#include "MyCtrlEx\TabDlg\TabDialog.h"


// CDlgPane2Item3 �Ի���

class CDlgPane2Item3 : public CTabDialog
{
	DECLARE_DYNAMIC(CDlgPane2Item3)

public:
	CDlgPane2Item3(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgPane2Item3();

// �Ի�������
	enum { IDD = IDD_DLG_PANE2_ITEM3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
