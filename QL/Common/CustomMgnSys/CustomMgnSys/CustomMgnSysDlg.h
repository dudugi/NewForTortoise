
// CustomMgnSysDlg.h : 头文件
//

#pragma once

class CDlgLoading;
// CCustomMgnSysDlg 对话框
class CCustomMgnSysDlg : public CBCGPDialog
{
// 构造
public:
	CCustomMgnSysDlg(CWnd* pParent = NULL);	// 标准构造函数
   ~CCustomMgnSysDlg();

// 对话框数据
	enum { IDD = IDD_CUSTOMMGNSYS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


public:
   static HWND s_hWnd;
   static void ShowLoadingWnd(BOOL bShow = TRUE);
private:
   CDlgLoading * m_pDlgLoading;

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
   
public:
   afx_msg void OnBnClickedBtnStaffmgn();
   afx_msg void OnBnClickedButton1();
   afx_msg void OnBnClickedBtnLog();
   afx_msg LRESULT OnShowLoadingMsg(WPARAM wParam, LPARAM lParam);
   afx_msg void OnActivateApp(BOOL bActive, DWORD dwThreadID);
   afx_msg void OnTimer(UINT_PTR nIDEvent);
   BOOL m_bIsBeginThread; //已经开始定时器
};

extern UINT UM_SHOWLOADING_MSG;
