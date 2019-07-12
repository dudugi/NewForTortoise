
// TestThreadEventDlg.h : ͷ�ļ�
//

#pragma once


// CTestThreadEventDlg �Ի���
class CTestThreadEventDlg : public CDialogEx
{
// ����
public:
	CTestThreadEventDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TESTTHREADEVENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

   class CThreadInfo
   {
   public:
      CThreadInfo(HWND hWnd)
         :m_hWnd(hWnd),m_bContinue(TRUE){m_hEvent[0]=m_hEvent[1]=NULL;}
      ~CThreadInfo();
      HWND m_hWnd;
      volatile BOOL m_bContinue;
      HANDLE m_hEvent[2];
   };
   CThreadInfo *m_pThreadInfo;
   static UINT ThreadFresh(LPVOID lpParam);

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
   afx_msg void OnBnClickedButton1();
   afx_msg void OnBnClickedButton2();
};
