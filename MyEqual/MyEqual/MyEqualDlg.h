
// MyEqualDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CMyEqualDlg �Ի���
class CMyEqualDlg : public CDialogEx
{
// ����
public:
	CMyEqualDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MYEQUAL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
   afx_msg void OnBnClickedButton1();
   CEdit m_editItems;
   CEdit m_EditLower;
   CEdit m_editUpper;
   CEdit m_editFind;
};
