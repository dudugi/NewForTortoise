#pragma once


// CLocalConfigureDlg �Ի���

class CLocalConfigureDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLocalConfigureDlg)

public:
	CLocalConfigureDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLocalConfigureDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_LOCAL_CONFIGURE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_strIP;
	CString m_strDatabaseName;
	CString m_strDatabaseAccount;
	CString m_strDatabasePassword;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
