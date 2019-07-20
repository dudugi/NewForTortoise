
// LogReportDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LogReport.h"
#include "LogReportDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLogReportDlg 对话框




CLogReportDlg::CLogReportDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLogReportDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
   m_dwtick = 0;
}

void CLogReportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLogReportDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
   ON_WM_CLOSE()
   ON_WM_COPYDATA()
   ON_COMMAND(IDM_CLEAR, &CLogReportDlg::OnClear)
END_MESSAGE_MAP()


// CLogReportDlg 消息处理程序

BOOL CLogReportDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

   ::SetProp(GetSafeHwnd(),SOFT_TAG, (HANDLE)1);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CLogReportDlg::OnPaint()
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
HCURSOR CLogReportDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CLogReportDlg::ClearUp()
{
   ::RemoveProp(GetSafeHwnd(), SOFT_TAG); 
   m_dwtick = 0;
}

void CLogReportDlg::OnClose()
{
   ClearUp();

   CDialogEx::OnClose();
}

BOOL CLogReportDlg::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
   int nLogType = pCopyDataStruct->dwData;
   if (nLogType != CLogCommandLineInfo::LogNothing)
   {
      CString strlogContent((char *)pCopyDataStruct->lpData);

      //获取当前的时间  
      COleDateTime logtime = COleDateTime::GetCurrentTime();
      CString strlog = _T("");
      strlog.Format(_T("%s%s"),logtime.Format(_T("%H:%M:%S")),strlogContent);
      CString strTick;
      DWORD dwNowTick = GetTickCount();

      if (0 != m_dwtick)
      {
         strTick.Format(_T("间隔：%lu"),dwNowTick - m_dwtick);
      }

      strlog += (_T("  ") + strTick);
      strlog += _T("\n");
      m_dwtick = dwNowTick;

      auto pListWnd = (CRichEditCtrl *)GetDlgItem(IDC_RICHEDIT_LOG_REPORT);
      pListWnd->SetSel(-1, -1);
      pListWnd->ReplaceSel(strlog);
   }

   return CDialogEx::OnCopyData(pWnd, pCopyDataStruct);
}


void CLogReportDlg::OnClear()
{
   auto pListWnd = (CRichEditCtrl *)GetDlgItem(IDC_RICHEDIT_LOG_REPORT);
   pListWnd->SetSel(0, -1);
   pListWnd->ReplaceSel(_T(""));
}
