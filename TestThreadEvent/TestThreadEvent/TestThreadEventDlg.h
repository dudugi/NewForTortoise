
// TestThreadEventDlg.h : 头文件
//

#pragma once


// CTestThreadEventDlg 对话框
class CTestThreadEventDlg : public CDialogEx
{
// 构造
public:
	CTestThreadEventDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TESTTHREADEVENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
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

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
   afx_msg void OnBnClickedButton1();
   afx_msg void OnBnClickedButton2();
};
