#pragma once


// CLocalConfigureDlg 对话框

class CLocalConfigureDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLocalConfigureDlg)

public:
	CLocalConfigureDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLocalConfigureDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_LOCAL_CONFIGURE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_strIP;
	CString m_strDatabaseName;
	CString m_strDatabaseAccount;
	CString m_strDatabasePassword;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
