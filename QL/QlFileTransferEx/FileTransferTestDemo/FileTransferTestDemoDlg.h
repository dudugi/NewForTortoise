
// FileTransferTestDemoDlg.h : 头文件
//

#pragma once
#include "DlgRecvWnd.h"


// CFileTransferTestDemoDlg 对话框
class CFileTransferTestDemoDlg : public CDialogEx
{
// 构造
public:
	CFileTransferTestDemoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_FILETRANSFERTESTDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

private:

   HWND GetRecvMsgHwnd();

   void AddMsgToLog(const CString & strLog);

   CString GetActionKey();
/*
   int GetWholeType();

   int GetFileType();
   */
   void GetParamList(CStringList & strParamList);
   /*
   void DownloadMethod(BOOL bDir = FALSE);*/

   FILETRANS * PrepareFileTrans();
   void ClearFileTrans(FILETRANS *);
private:

   CDlgRecvWnd m_wndRecvWnd1;
   CDlgRecvWnd m_wndRecvWnd2;

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
   afx_msg void OnBnClickedBtnPopup();
   afx_msg void OnBnClickedBtnUpload();
   afx_msg void OnBnClickedBtnDownload();
   afx_msg void OnBnClickedBtnDownloadDir();
    afx_msg void OnBnClickedBtnDownByEx();

   afx_msg void OnBnClickedBtnDelete();
   afx_msg void OnBnClickedBtnDeleteDir();
   afx_msg void OnBnClickedBtnCopyfile();
   afx_msg void OnBnClickedBtnCopydir();
   afx_msg void OnBnClickedBtnGetlist();

   afx_msg void OnBnClickedBtnOrderexists();
   afx_msg void OnBnClickedBtnIsFileExists();
   afx_msg void OnBnClickedBtnClearrecvlog();

   /*
   afx_msg void OnBnClickedBtnDelOrderDir();*/
   afx_msg void OnBnClickedBtnBackup();
   afx_msg void OnBnClickedBtnCopyVersionToNewOne();
protected:
   afx_msg LRESULT OnQlFtpProgress(WPARAM wParam, LPARAM lParam);
};
