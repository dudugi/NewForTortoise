
// TestDragFileFromClipboardDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TestDragFileFromClipboard.h"
#include "TestDragFileFromClipboardDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestDragFileFromClipboardDlg 对话框




CTestDragFileFromClipboardDlg::CTestDragFileFromClipboardDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTestDragFileFromClipboardDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestDragFileFromClipboardDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTestDragFileFromClipboardDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
   ON_BN_CLICKED(IDC_BUTTON1, &CTestDragFileFromClipboardDlg::OnBnClickedButton1)
   ON_BN_CLICKED(IDC_BTN_TESTHASCLIPFILE, &CTestDragFileFromClipboardDlg::OnBnClickedBtnTesthasclipfile)
   ON_WM_DROPFILES()
END_MESSAGE_MAP()


// CTestDragFileFromClipboardDlg 消息处理程序

BOOL CTestDragFileFromClipboardDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTestDragFileFromClipboardDlg::OnPaint()
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
HCURSOR CTestDragFileFromClipboardDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CTestDragFileFromClipboardDlg::GetDropFilePaths(HDROP hDrop, std::list<CString> *pListPaths)
{
   if (!pListPaths)
   {
      return FALSE;
   }
   std::list<CString> ListPaths;
   int cch;
   int iFiles=DragQueryFile(hDrop,-1,NULL,0);
   for (int i = 0; i < iFiles; i++)
   {
      cch = DragQueryFile(hDrop,i,NULL,0);
      CString str;
      DragQueryFile(hDrop,i,str.GetBuffer(cch + 1),cch+1);
      str.ReleaseBuffer();
      if (!::PathIsDirectory(str))
      {
         ListPaths.push_back(str);
      }
   }
   pListPaths->swap(ListPaths);
   return TRUE;
}

BOOL CTestDragFileFromClipboardDlg::GetClipFilePaths(std::list<CString> *pListPaths)
{
   if (!OpenClipboard())//打开剪贴板  
      return FALSE;

   if (!IsClipboardFormatAvailable(CF_HDROP))//判断格式是否是我们所需要  
   {
      CloseClipboard();
      return FALSE;
   }
   std::list<CString> ListPaths;
   int cch;
   //读取数据  
   HDROP hDrop=(HDROP)GetClipboardData(CF_HDROP);  
   int iFiles=DragQueryFile(hDrop,-1,NULL,0);
   for (int i = 0; i < iFiles; i++)
   {
      cch = DragQueryFile(hDrop,i,NULL,0);
      CString str;
      DragQueryFile(hDrop,i,str.GetBuffer(cch + 1),cch+1);
      str.ReleaseBuffer();
      if (!::PathIsDirectory(str))
      {
         ListPaths.push_back(str);
      }
   }
   CloseClipboard();
   if (ListPaths.empty())
      return FALSE;
   if (pListPaths)
      pListPaths->swap(ListPaths);
   return TRUE;
}

void CTestDragFileFromClipboardDlg::OnBnClickedButton1()
{
   std::list<CString> lstPaths;
   if (!GetClipFilePaths(&lstPaths))
   {
      MessageBox(_T("None"));
      return;
   }
   CString strAll;
   for (auto Iter = lstPaths.begin(); Iter != lstPaths.end(); ++Iter)
   {
      if (!strAll.IsEmpty())
         strAll += _T("\n");
      strAll += *Iter;
   }

   MessageBox(strAll);
}

BOOL CTestDragFileFromClipboardDlg::HasClipFile()
{
   if (!OpenClipboard())//打开剪贴板
      return FALSE;

   BOOL bRet = FALSE;
   if (IsClipboardFormatAvailable(CF_HDROP))//判断格式是否是我们所需要  
   {  
      //读取数据  
      HDROP hDrop=(HDROP)GetClipboardData(CF_HDROP);  
      int iFiles=DragQueryFile(hDrop,-1,NULL,0);
      if (iFiles > 0)
         bRet = TRUE;
   }

   CloseClipboard();
   return bRet;
}

void CTestDragFileFromClipboardDlg::OnBnClickedBtnTesthasclipfile()
{
   if (!HasClipFile())
   {
      MessageBox(_T("None"));
      return;
   }
   MessageBox(_T("Has"));
}


void CTestDragFileFromClipboardDlg::OnDropFiles(HDROP hDropInfo)
{
   // TODO: 在此添加消息处理程序代码和/或调用默认值
   std::list<CString> lstPaths;
   GetDropFilePaths(hDropInfo, &lstPaths);
   CString strAll;
   for (auto Iter = lstPaths.begin(); Iter != lstPaths.end(); ++Iter)
   {
      if (!strAll.IsEmpty())
         strAll += _T("\n");
      strAll += *Iter;
   }

   MessageBox(strAll);

   CDialogEx::OnDropFiles(hDropInfo);
}
