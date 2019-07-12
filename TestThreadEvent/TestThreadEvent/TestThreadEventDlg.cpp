
// TestThreadEventDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TestThreadEvent.h"
#include "TestThreadEventDlg.h"
#include "afxdialogex.h"
#include <new.h>
#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestThreadEventDlg 对话框




CTestThreadEventDlg::CTestThreadEventDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTestThreadEventDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestThreadEventDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTestThreadEventDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
   ON_BN_CLICKED(IDC_BUTTON1, &CTestThreadEventDlg::OnBnClickedButton1)
   ON_BN_CLICKED(IDC_BUTTON2, &CTestThreadEventDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CTestThreadEventDlg 消息处理程序

BOOL CTestThreadEventDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

  
   m_pThreadInfo = new /*(std::nothrow)*/ CThreadInfo(GetSafeHwnd());
   if (!m_pThreadInfo)
   {
      return TRUE;
   }

   m_pThreadInfo->m_hEvent[0] = CreateEvent(NULL, FALSE, FALSE, NULL);
   m_pThreadInfo->m_hEvent[1] = CreateEvent(NULL, FALSE, FALSE, NULL);

   //批量下载如何区分每一个文件 Emmm
   HANDLE hThrRefresh = ::CreateThread(NULL,0,
      (LPTHREAD_START_ROUTINE)ThreadFresh, m_pThreadInfo,0,0);

   CloseHandle(hThrRefresh);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

UINT CTestThreadEventDlg::ThreadFresh(LPVOID lpParam)
{
   CTestThreadEventDlg::CThreadInfo *pThreadInfo = reinterpret_cast<CTestThreadEventDlg::CThreadInfo *>(lpParam);
   if (!pThreadInfo)
      return 0;
   CTestThreadEventDlg::CThreadInfo &ThreadInfo(*pThreadInfo);

   DWORD dwRet = WAIT_OBJECT_0;
   int i = 0;
   while (dwRet == WAIT_OBJECT_0 || dwRet == WAIT_TIMEOUT)
   {
      TRACE(_T("%d\n"), i++);

      dwRet = WaitForMultipleObjects(2, ThreadInfo.m_hEvent, FALSE, 10000);
      if (dwRet == WAIT_TIMEOUT)
      {
         TRACE(_T("WAIT_TIMEOUT:"));
      }
      else if (dwRet == WAIT_OBJECT_0)
      {
         TRACE(_T("WAIT_OBJECT_0:"));
      }
      else if (dwRet == WAIT_OBJECT_0 + 1)
      {
         TRACE(_T("WAIT_OBJECT_1:"));
      }
      else if (dwRet == WAIT_FAILED)
      {
         TRACE(_T("WAIT_FAILED:"));
      }
      TRACE(_T("dw%d\n"), dwRet);
   }

   delete pThreadInfo;
   return 0;
}

CTestThreadEventDlg::CThreadInfo::~CThreadInfo()
{
   if (m_hEvent[1])
   {
      CloseHandle(m_hEvent[1]);
   }

   if (m_hEvent[0])
   {
      CloseHandle(m_hEvent[0]);
   }
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTestThreadEventDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTestThreadEventDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTestThreadEventDlg::OnBnClickedButton1()
{
   // TODO: 在此添加控件通知处理程序代码
   if (m_pThreadInfo && m_pThreadInfo->m_hEvent[0])
      SetEvent(m_pThreadInfo->m_hEvent[0]);
}


void CTestThreadEventDlg::OnBnClickedButton2()
{
   // TODO: 在此添加控件通知处理程序代码
   if (m_pThreadInfo && m_pThreadInfo->m_hEvent[1])
      SetEvent(m_pThreadInfo->m_hEvent[1]);
}
