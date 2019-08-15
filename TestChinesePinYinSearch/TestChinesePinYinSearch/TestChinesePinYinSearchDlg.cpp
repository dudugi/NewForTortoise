
// TestChinesePinYinSearchDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TestChinesePinYinSearch.h"
#include "TestChinesePinYinSearchDlg.h"
#include "afxdialogex.h"
#include "CommonChatContent\DlgCommonChatContent.h"
#include <iosfwd>
#include <string>
#include <sstream> 
#include "PinYinComboBox\PinYinComboBox.h"

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


// CTestChinesePinYinSearchDlg 对话框

void CTestChinesePinYinSearchDlg::OnBnClickedBtnDelusertext()
{
   CString str;
   CLY2ComBox *pComb1= &m_cbo1;//(CLYComBox*)GetDlgItem(IDC_CMB_NAME);

   if (pComb1->m_bFocus)
   {
      pComb1->GetLBText(pComb1->GetCurSel(),str);
      pComb1->DeleteString(pComb1->GetCurSel());	
      //theApp.m_UserTextList.DelItem(IDD_DLG_FSMATRELATION,IDC_CMB_NAME,str);
   }
}

CTestChinesePinYinSearchDlg::~CTestChinesePinYinSearchDlg()
{
	if (m_pPinYinCombobox) 
		delete m_pPinYinCombobox;
}

CTestChinesePinYinSearchDlg::CTestChinesePinYinSearchDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTestChinesePinYinSearchDlg::IDD, pParent)
   , m_sTextPinYin(_T(""))
   , m_sCBOBox2(_T(""))
   , m_pPinYinCombobox(nullptr)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestChinesePinYinSearchDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialogEx::DoDataExchange(pDX);
   DDX_Control(pDX, IDC_EDIT1, m_edit1);
   DDX_Control(pDX, IDC_COMBO1, m_cbo1);
   DDX_Control(pDX, IDC_COMBO2, m_cboBox2);
   DDX_Control(pDX, IDC_COMBOBOXEX1, m_cboExt);
   DDX_Control(pDX, IDC_MFCEDITBROWSE_NAME, *m_pPinYinCombobox);
   DDX_Control(pDX, IDC_EDIT_3, m_edit3);

   DDX_Text(pDX, IDC_MFCEDITBROWSE_NAME, m_sTextPinYin);
   DDX_CBString(pDX, IDC_COMBO2, m_sCBOBox2);

   DDX_Control(pDX, IDC_EDIT_CONTENT, m_editContents);
}

BEGIN_MESSAGE_MAP(CTestChinesePinYinSearchDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
   ON_BN_CLICKED(IDC_BUTTON1, &CTestChinesePinYinSearchDlg::OnBnClickedButton1)
   ON_COMMAND(COMBOX_DELITEM, &CTestChinesePinYinSearchDlg::OnBnClickedBtnDelusertext)
   ON_BN_SETFOCUS(IDC_BUTTON1, &CTestChinesePinYinSearchDlg::OnBnSetfocusButton1)
   ON_WM_SETFOCUS()
   ON_WM_KILLFOCUS()
   ON_CBN_SETFOCUS(IDC_COMBO1, &CTestChinesePinYinSearchDlg::OnCbnSetfocusCombo1)
   ON_BN_CLICKED(IDC_BUTTON2, &CTestChinesePinYinSearchDlg::OnBnClickedButton2)
   ON_BN_CLICKED(IDC_BTN_CLEAR, &CTestChinesePinYinSearchDlg::OnBnClickedBtnClear)
   ON_BN_CLICKED(IDC_BUTTON3, &CTestChinesePinYinSearchDlg::OnBnClickedButton3)
   ON_BN_CLICKED(IDC_BTN_UPDATE, &CTestChinesePinYinSearchDlg::OnBnClickedBtnUpdate)
   ON_EN_CHANGE(IDC_MFCEDITBROWSE_NAME, &CTestChinesePinYinSearchDlg::OnEnChangeMfceditbrowseName)
   ON_BN_CLICKED(IDC_BTN_SELDLG, &CTestChinesePinYinSearchDlg::OnBnClickedBtnSeldlg)
   ON_BN_CLICKED(IDC_BUTTON4, &CTestChinesePinYinSearchDlg::OnBnClickedButton4)
   ON_BN_CLICKED(IDC_BUTTON5, &CTestChinesePinYinSearchDlg::OnBnClickedButton5)
   ON_BN_CLICKED(IDC_BUTTON6, &CTestChinesePinYinSearchDlg::OnBnClickedButton6)
   ON_BN_CLICKED(IDC_BUTTON7, &CTestChinesePinYinSearchDlg::OnBnClickedButton7)
   ON_BN_CLICKED(IDC_BUTTON8, &CTestChinesePinYinSearchDlg::OnBnClickedButton8)
END_MESSAGE_MAP()


// CTestChinesePinYinSearchDlg 消息处理程序

BOOL CTestChinesePinYinSearchDlg::OnInitDialog()
{
	m_pPinYinCombobox = (CPinYinComboBox*)RUNTIME_CLASS(CPinYinComboBox)->CreateObject();
	
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
   CString sContents = _T("前放\r\n袖宽\r\n前领深\r\n大身");
   m_editContents.SetWindowText(sContents);


//    m_cbo1.InsertString(0, _T("11122wow"));
//    m_cbo1.InsertString(1, _T("我的天"));
//    m_cbo1.InsertString(2, _T("天的我"));
   m_cbo1.AddStringNew(_T("11122wow"));
   m_cbo1.AddStringNew(_T("我的天"));
   m_cbo1.AddStringNew(_T("天的我"));
   m_cboBox2.AddString(_T("天的我1"));
   m_cboBox2.AddString(_T("天的我2"));
   m_cboBox2.AddString(_T("天的我3"));
   m_cboBox2.AddString(_T("天的我4"));
   m_cboBox2.AddString(_T("天的我5"));
   m_cboBox2.AddString(_T("天的我6"));

   m_cboBox2.AddString(_T("11122wow"));
   m_cboBox2.AddString(_T("我的天"));
   m_cboBox2.AddString(_T("天的我"));
   m_cboBox2.AddString(_T("天的我1"));
   m_cboBox2.AddString(_T("天的我2"));
   m_cboBox2.AddString(_T("天的我3"));
   m_cboBox2.AddString(_T("天的我4"));
   m_cboBox2.AddString(_T("天的我5"));
   m_cboBox2.AddString(_T("天的我6"));

   //COMBOBOXEXITEM item;
   //
   //item.pszText = _T("12123");
   //int nRet = m_cboExt.InsertItem(&item);
   //item.pszText = _T("12123221");
   // nRet = m_cboExt.InsertItem(&item);


//    m_cboExt.AddString(_T("12123"));
//    m_cboExt.AddString(_T("12123221"));

   //m_cboExt.AddString()

  // m_pPinYinCombobox->EnableBrowseButton(TRUE, _T("▼"));
   m_pPinYinCombobox->Init();

   //m_MFCEditBrowseCtrlName.AddStringNew()


   m_pPinYinCombobox->m_funcDeleteString = [this](const CString &sText)
   {
      this->MessageBox(sText);
   };

   m_pPinYinCombobox->m_funcDeleteStringCheck = [](const CString &sText)->BOOL
   {
      if(AfxMessageBox(_T("是否删除该选项"), MB_YESNO) == IDNO)
         return FALSE;
      return TRUE;
   };

   m_pPinYinCombobox->m_funcDeleteStringCheck = nullptr;

   m_nEditCount = 0;
   m_pPinYinCombobox->m_funcEditChange = [this](const CString &sText)
   {
      //this->MessageBox(sText);
      CString sOutput;
      sOutput.Format(_T("edit change %s, %d"), sText, m_nEditCount);

      CClientDC dc(this);
      dc.TextOut(10, 10, _T("                                                                                               "));
      dc.TextOut(10, 10, sOutput);

      CString sText2;
      this->GetDlgItemText(IDC_MFCEDITBROWSE_NAME, sText2);
      sOutput.Format(_T("edit change %s, %d"), sText2, m_nEditCount);

      dc.TextOut(10, 30, _T("                                                                                               "));
      dc.TextOut(10, 30, sOutput);

      ++m_nEditCount;
   };

   m_nSelCount = 0;
   m_pPinYinCombobox->m_funcSelChange = [this](const CString &sText)
   {
      //this->MessageBox(sText);
      //TRACE(_T("edit SelChange %s\n"), sText);

      CString sOutput;
      sOutput.Format(_T("edit SelChange %s, %d"), sText, m_nSelCount);

      CClientDC dc(this);
      dc.TextOut(10, 50, _T("                                                                                               "));
      dc.TextOut(10, 50, sOutput);

      CString sText2;
      this->GetDlgItemText(IDC_MFCEDITBROWSE_NAME, sText2);
      sOutput.Format(_T("edit SelChange %s, %d"), sText2, m_nSelCount);

      dc.TextOut(10, 90, _T("                                                                                               "));
      dc.TextOut(10, 90, sOutput);

      ++m_nSelCount;
   };

   //m_pPinYinCombobox->SetMaxCount(5);

   //m_pPinYinCombobox->SetReadOnly(1);

   
// 
//    m_pPinYinCombobox->SetWindowText(_T(""));
// 
//    ::SetWindowText(m_pPinYinCombobox->GetSafeHwnd(), _T("我就是我"));
// 
// 
//    m_pPinYinCombobox->SendMessage(WM_SETTEXT, 0, (LPARAM)_T("wweee22"));
// 
//    //m_pPinYinCombobox->SetReadOnly(0);
// 
//    m_pPinYinCombobox->SetSel(0, -1);
//    m_pPinYinCombobox->ReplaceSel(_T("1212"));

   OnBnClickedButton5(); //初始化下拉框内容


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTestChinesePinYinSearchDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTestChinesePinYinSearchDlg::OnPaint()
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
HCURSOR CTestChinesePinYinSearchDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


CString ConvertChineseUnicodeToPyt(const wchar_t* chrstr);

CString ConvertChineseToShorthand(const wchar_t* chrstr);

void CTestChinesePinYinSearchDlg::OnBnClickedButton1()
{
   // TODO: 在此添加控件通知处理程序代码

   CString sText;
   m_edit1.GetWindowText(sText);

   CString sText2 = ConvertChineseUnicodeToPyt(sText);
   sText2 += ConvertChineseToShorthand(sText);

   MessageBox(sText2);
}


void CTestChinesePinYinSearchDlg::OnBnSetfocusButton1()
{
   // TODO: 在此添加控件通知处理程序代码

   TRACE(_T("focus\n"));
}


void CTestChinesePinYinSearchDlg::OnSetFocus(CWnd* pOldWnd)
{
   CDialogEx::OnSetFocus(pOldWnd);

   // TODO: 在此处添加消息处理程序代码

   TRACE(_T("OnSetFocus\n"));
}


void CTestChinesePinYinSearchDlg::OnKillFocus(CWnd* pNewWnd)
{
   CDialogEx::OnKillFocus(pNewWnd);

   // TODO: 在此处添加消息处理程序代码

   TRACE(_T("OnKillFocus\n"));
}


void CTestChinesePinYinSearchDlg::OnCbnSetfocusCombo1()
{
   // TODO: 在此添加控件通知处理程序代码


   TRACE(_T("CBN_SET_FOCUS\n"));
}


void CTestChinesePinYinSearchDlg::OnBnClickedButton2()
{
   // TODO: 在此添加控件通知处理程序代码

   static CDlgCommonChatContent Dlg;

   if (!Dlg.GetSafeHwnd())
   {
//       auto func = [this](const CString &sText)
//       {
//          m_InputEdit.ReplaceSel(sText);
//       };
//       Dlg.m_funcOutputText = func;
//       Dlg.m_funcCreateText = func;
      CString sPath = _T("E:\\ABC.XML");
      Dlg.SetSettingPath(sPath);
      Dlg.CreateDlgIndirect(this);
   }

   CRect BtnRect;
   //m_btnCommonChatContent.GetWindowRect(&BtnRect);
   GetDlgItem(IDC_BUTTON2)->GetWindowRect(&BtnRect);
   Dlg.Init(BtnRect.left, BtnRect.top);

   Dlg.ShowWindow(SW_SHOW);
}


void CTestChinesePinYinSearchDlg::OnBnClickedBtnClear()
{
   // TODO: 在此添加控件通知处理程序代码
   m_pPinYinCombobox->ResetContent();
}


void CTestChinesePinYinSearchDlg::OnBnClickedButton3()
{
   // TODO: 在此添加控件通知处理程序代码
   CString sText;
   m_edit3.GetWindowText(sText);

   m_pPinYinCombobox->SetWindowText(sText);
}


void CTestChinesePinYinSearchDlg::OnBnClickedBtnUpdate()
{
   // TODO: 在此添加控件通知处理程序代码
   UpdateData();

   MessageBox(m_sTextPinYin);

   static int i = 0;

   CString stmp;
   stmp.Format(_T(":%d"), i);
   m_sTextPinYin.Append(stmp);

   UpdateData(FALSE);
}


void CTestChinesePinYinSearchDlg::OnEnChangeMfceditbrowseName()
{
   // TODO:  如果该控件是 RICHEDIT 控件，它将不
   // 发送此通知，除非重写 CDialogEx::OnInitDialog()
   // 函数并调用 CRichEditCtrl().SetEventMask()，
   // 同时将 ENM_CHANGE 标志“或”运算到掩码中。

   // TODO:  在此添加控件通知处理程序代码

   TRACE(_T("123\n"));
}


void CTestChinesePinYinSearchDlg::OnBnClickedBtnSeldlg()
{
   // TODO: 在此添加控件通知处理程序代码
   SetDlgItemText(IDC_MFCEDITBROWSE_NAME, _T("set dlg item"));
}


void CTestChinesePinYinSearchDlg::OnBnClickedButton4()
{
   // TODO: 在此添加控件通知处理程序代码
   int nCount = m_pPinYinCombobox->GetCount();
   CString sOut;
   sOut.Format(_T("%d"), nCount);
   MessageBox(sOut);
}


void CTestChinesePinYinSearchDlg::OnBnClickedButton5()
{
   // TODO: 在此添加控件通知处理程序代码

//    m_pPinYinCombobox->AddString(_T("前片"));
//    m_pPinYinCombobox->AddString(_T("ABCDEFGHI00000000001"));
//    m_pPinYinCombobox->AddString(_T("00000000001"));
//    m_pPinYinCombobox->AddString(_T("00000000002"));
//    m_pPinYinCombobox->AddString(_T("请问我是谁"));
//    m_pPinYinCombobox->AddString(_T("我是谁"));
//    m_pPinYinCombobox->AddString(_T("我到底是谁"));
//    m_pPinYinCombobox->AddString(_T("请问你又是谁"));
//    m_pPinYinCombobox->AddString(_T("谁在问我我是谁"));
//    m_pPinYinCombobox->AddString(_T("我是谁这个问题我自己能回答"));
//    m_pPinYinCombobox->AddString(_T("我以前是谁"));
//    m_pPinYinCombobox->AddString(_T("我将来是谁"));
//    m_pPinYinCombobox->AddString(_T("请问我以前是谁"));
//    m_pPinYinCombobox->AddString(_T("请问我现在是谁"));
//    m_pPinYinCombobox->AddString(_T("我现在是谁"));
//    m_pPinYinCombobox->AddString(_T("00000000014"));

   m_pPinYinCombobox->ResetContent();

   CString sContents;
   m_editContents.GetWindowText(sContents);
   std::wstring ws = sContents;
   std::wstringstream ss(ws);
   std::wstring sTemp;
   while(std::getline(ss, sTemp, _T('\n')))
   {
      if (!sTemp.empty() && sTemp.back() == _T('\r'))
      {
         sTemp.pop_back();
      }
      m_pPinYinCombobox->AddString(sTemp.c_str());
   }

}


void CTestChinesePinYinSearchDlg::OnBnClickedButton6()
{
   // TODO: 在此添加控件通知处理程序代码
   CString sOut;
   m_pPinYinCombobox->GetLBText(3, sOut);
   MessageBox(sOut);
}


void CTestChinesePinYinSearchDlg::OnBnClickedButton7()
{
   // TODO: 在此添加控件通知处理程序代码
   UpdateData(TRUE);
}


void CTestChinesePinYinSearchDlg::OnBnClickedButton8()
{
   // TODO: 在此添加控件通知处理程序代码

   MessageBox(m_sCBOBox2);
}


void CTestChinesePinYinSearchDlg::OnOK()
{
   // TODO: 在此添加专用代码和/或调用基类

   //CDialogEx::OnOK();
}
