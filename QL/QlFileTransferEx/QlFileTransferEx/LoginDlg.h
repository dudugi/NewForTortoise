#pragma once
#include "resource.h"
#include "afxeditbrowsectrl.h"
#include "MFCEditBrowserNoShell.h"

// CLoginDlg 对话框

class CLoginDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLoginDlg)

public:
	typedef enum S_FileTrans_LoginType{
		En_Login_User = 0,//员工登录
		En_Login_Custom,//客户登录
	}S_FILETRANS_LOGINTYPE;

	CLoginDlg(int nLoginType = En_Login_User,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLoginDlg();
	void SetCtrState(BOOL bEnable);
	void SetDlgPos(BOOL bExpand);
	void SetSvrConfigValue();
	void SetActValue();

public:
	CRect m_rcMain;
	BOOL m_bExpandDlg;

// 对话框数据
	enum { IDD = IDD_DLG_LOGIN };
private:
	int m_nLoginType;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnConfigLogindlg();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedChkActLogindlg();
	afx_msg void OnBnClickedChkApplyLogindlg();
	afx_msg void OnBnClickedBtnEmptyLogindlg();
	afx_msg void OnBnClickedBtnDbsaveLogindlg();
protected:
	afx_msg LRESULT OnAdoconnMsg(WPARAM wParam, LPARAM lParam);
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CMFCEditBrowserNoShell m_EditBrawoer;
};
