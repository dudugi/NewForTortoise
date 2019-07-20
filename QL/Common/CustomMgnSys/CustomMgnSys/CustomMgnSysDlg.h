
// CustomMgnSysDlg.h : ͷ�ļ�
//

#pragma once

class CDlgLoading;
// CCustomMgnSysDlg �Ի���
class CCustomMgnSysDlg : public CBCGPDialog
{
// ����
public:
	CCustomMgnSysDlg(CWnd* pParent = NULL);	// ��׼���캯��
   ~CCustomMgnSysDlg();

// �Ի�������
	enum { IDD = IDD_CUSTOMMGNSYS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


public:
   static HWND s_hWnd;
   static void ShowLoadingWnd(BOOL bShow = TRUE);
private:
   CDlgLoading * m_pDlgLoading;

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
   afx_msg void OnBnClickedBtnStaffmgn();
   afx_msg void OnBnClickedButton1();
   afx_msg void OnBnClickedBtnLog();
   afx_msg LRESULT OnShowLoadingMsg(WPARAM wParam, LPARAM lParam);
   afx_msg void OnActivateApp(BOOL bActive, DWORD dwThreadID);
   afx_msg void OnTimer(UINT_PTR nIDEvent);
   BOOL m_bIsBeginThread; //�Ѿ���ʼ��ʱ��
};

extern UINT UM_SHOWLOADING_MSG;
