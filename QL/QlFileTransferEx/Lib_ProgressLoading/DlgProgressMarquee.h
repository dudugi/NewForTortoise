#pragma once
#include "resource.h"
#include "afxcmn.h"


// CDlgProgressMarquee �Ի���

class CDlgProgressMarquee : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgProgressMarquee)

public:
	CDlgProgressMarquee(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgProgressMarquee();

// �Ի�������
	enum { IDD = IDD_DLG_PROGRESSMARQUE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
   virtual BOOL OnInitDialog();
   CProgressCtrl m_progressCtrl;
   afx_msg void OnTimer(UINT_PTR nIDEvent);
};
