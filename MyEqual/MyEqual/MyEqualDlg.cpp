
// MyEqualDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MyEqual.h"
#include "MyEqualDlg.h"
#include "afxdialogex.h"
#include <algorithm>
#include <vector>
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMyEqualDlg 对话框




CMyEqualDlg::CMyEqualDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyEqualDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyEqualDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialogEx::DoDataExchange(pDX);
   DDX_Control(pDX, IDC_EDIT1, m_editItems);
   DDX_Control(pDX, IDC_EDIT_LOWER, m_EditLower);
   DDX_Control(pDX, IDC_EDIT_UPPER, m_editUpper);
   DDX_Control(pDX, IDC_EDIT_FIND, m_editFind);
}

BEGIN_MESSAGE_MAP(CMyEqualDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
   ON_BN_CLICKED(IDC_BUTTON1, &CMyEqualDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMyEqualDlg 消息处理程序

BOOL CMyEqualDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

   //m_editItems
   int nData[] =  { 1, 1, 2, 3, 3, 3, 3, 5, 5, 6 };
   std::vector<int> data(nData, nData + sizeof(nData)/sizeof(*nData));
   CString strItems;
   for (auto Iter = data.begin(); Iter != data.end(); ++Iter)
   {
      strItems.AppendFormat(_T("%d\r\n"),*Iter);
   }
   m_editItems.SetWindowText(strItems);

   m_editFind.SetWindowText(_T("4"));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMyEqualDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMyEqualDlg::OnPaint()
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
HCURSOR CMyEqualDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

std::vector<CStringW> SplitStrW(const CStringW &strOrg, const WCHAR *delim)
{
   std::vector<WCHAR> vecProcessTCHAR(strOrg.GetLength() + 1);

   memcpy(vecProcessTCHAR.data(), (LPCWSTR)strOrg, strOrg.GetLength() * sizeof(WCHAR));
   WCHAR *pTUploadChar = ::wcstok(vecProcessTCHAR.data(), delim);

   std::vector<CStringW> setResultString;

   while(pTUploadChar != NULL)
   {
      CStringW strExt;

      strExt = pTUploadChar;


      setResultString.push_back(strExt);
      pTUploadChar = ::wcstok(NULL, delim);
   }
   return setResultString;
}

void CMyEqualDlg::OnBnClickedButton1()
{
   // TODO: 在此添加控件通知处理程序代码

   //int nData[] =  { 1, 1, 2, 3, 3, 3, 3, 5, 5, 6 };
   //std::vector<int> data(nData, nData + sizeof(nData)/sizeof(*nData));
   CString strItems;
   m_editItems.GetWindowText(strItems);
   std::vector<CString> vecStr = SplitStrW(strItems, _T("\r\n"));
   std::vector<int> data(vecStr.size());
   std::transform(vecStr.begin(), vecStr.end(), data.begin(), ::_ttoi);

   CString strFind;
   m_editFind.GetWindowText(strFind);
   int nFind = _ttoi(strFind);

   auto lower = std::lower_bound(data.begin(), data.end(), nFind);
   auto upper = std::upper_bound(data.begin(), data.end(), nFind);

  // std::copy(lower, upper, std::ostream_iterator<int>(std::cout, " "));
   if (upper != data.end())
      std::cout << *upper << std::endl;
   if (lower != data.end())
      std::cout << *lower << std::endl;

   /*
   lower_bound( begin,end,num)：从数组的begin位置到end-1位置二分查找第一个大于或等于num的数字，找到返回该数字的地址，不存在则返回end。通过返回的地址减去起始地址begin,得到找到数字在数组中的下标。

   upper_bound( begin,end,num)：从数组的begin位置到end-1位置二分查找第一个大于num的数字，找到返回该数字的地址，不存在则返回end。通过返回的地址减去起始地址begin,得到找到数字在数组中的下标。
   */

   CString sLower;
   if (lower != data.end())
      sLower.Format(_T("%d-%d"), std::distance(data.begin(), lower), *lower);
   CString sUpper;
   if (upper != data.end())
      sUpper.Format(_T("%d-%d"), std::distance(data.begin(), upper), *upper);

   m_EditLower.SetWindowText(sLower);
   m_editUpper.SetWindowText(sUpper);
}
