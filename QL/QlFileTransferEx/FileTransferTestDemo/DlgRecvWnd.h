#pragma once


// CDlgRecvWnd �Ի���
//������Ϣ�õĴ���
class CDlgRecvWnd : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgRecvWnd)

public:
	CDlgRecvWnd(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgRecvWnd();

// �Ի�������
	enum { IDD = IDD_DLG_MSG_RECV };

public:
   void ClearLog();

private:
   void ResizeCtrl();

   void AddMsgToLog(const CString & strLog);

   void LogActionResult(int nAction);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
   afx_msg void OnSize(UINT nType, int cx, int cy);
   virtual BOOL OnInitDialog();
protected:
   afx_msg LRESULT OnQlFtpGetlist(WPARAM wParam, LPARAM lParam);
   afx_msg LRESULT OnQlFtpUpload(WPARAM wParam, LPARAM lParam);
   afx_msg LRESULT OnQlFtpProgress(WPARAM wParam, LPARAM lParam);
   afx_msg LRESULT OnQlFtpDel(WPARAM wParam, LPARAM lParam);
   afx_msg LRESULT OnQlFtpDownload(WPARAM wParam, LPARAM lParam);
   afx_msg LRESULT OnQlFtpMkdir(WPARAM wParam, LPARAM lParam);
   afx_msg LRESULT OnQlFtpDeldir(WPARAM wParam, LPARAM lParam);
   afx_msg LRESULT OnQlFtpDowndir(WPARAM wParam, LPARAM lParam);
   afx_msg LRESULT OnQlFtpDownbyex(WPARAM wParam, LPARAM lParam);
   afx_msg LRESULT OnQlFtpDowndirmsg(WPARAM wParam, LPARAM lParam);
   afx_msg LRESULT OnQlFtpDownbyexmsg(WPARAM wParam, LPARAM lParam);
   afx_msg LRESULT OnQlFtpBackupfile(WPARAM wParam, LPARAM lParam);
   afx_msg LRESULT OnQlFtpBackupfilemsg(WPARAM wParam, LPARAM lParam);
   afx_msg LRESULT OnQlFtpCopyVersionToNew(WPARAM wParam, LPARAM lParam);
};
