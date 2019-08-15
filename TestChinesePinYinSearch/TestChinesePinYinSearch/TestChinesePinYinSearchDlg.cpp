
// TestChinesePinYinSearchDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CTestChinesePinYinSearchDlg �Ի���

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


// CTestChinesePinYinSearchDlg ��Ϣ�������

BOOL CTestChinesePinYinSearchDlg::OnInitDialog()
{
	m_pPinYinCombobox = (CPinYinComboBox*)RUNTIME_CLASS(CPinYinComboBox)->CreateObject();
	
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
   CString sContents = _T("ǰ��\r\n���\r\nǰ����\r\n����");
   m_editContents.SetWindowText(sContents);


//    m_cbo1.InsertString(0, _T("11122wow"));
//    m_cbo1.InsertString(1, _T("�ҵ���"));
//    m_cbo1.InsertString(2, _T("�����"));
   m_cbo1.AddStringNew(_T("11122wow"));
   m_cbo1.AddStringNew(_T("�ҵ���"));
   m_cbo1.AddStringNew(_T("�����"));
   m_cboBox2.AddString(_T("�����1"));
   m_cboBox2.AddString(_T("�����2"));
   m_cboBox2.AddString(_T("�����3"));
   m_cboBox2.AddString(_T("�����4"));
   m_cboBox2.AddString(_T("�����5"));
   m_cboBox2.AddString(_T("�����6"));

   m_cboBox2.AddString(_T("11122wow"));
   m_cboBox2.AddString(_T("�ҵ���"));
   m_cboBox2.AddString(_T("�����"));
   m_cboBox2.AddString(_T("�����1"));
   m_cboBox2.AddString(_T("�����2"));
   m_cboBox2.AddString(_T("�����3"));
   m_cboBox2.AddString(_T("�����4"));
   m_cboBox2.AddString(_T("�����5"));
   m_cboBox2.AddString(_T("�����6"));

   //COMBOBOXEXITEM item;
   //
   //item.pszText = _T("12123");
   //int nRet = m_cboExt.InsertItem(&item);
   //item.pszText = _T("12123221");
   // nRet = m_cboExt.InsertItem(&item);


//    m_cboExt.AddString(_T("12123"));
//    m_cboExt.AddString(_T("12123221"));

   //m_cboExt.AddString()

  // m_pPinYinCombobox->EnableBrowseButton(TRUE, _T("��"));
   m_pPinYinCombobox->Init();

   //m_MFCEditBrowseCtrlName.AddStringNew()


   m_pPinYinCombobox->m_funcDeleteString = [this](const CString &sText)
   {
      this->MessageBox(sText);
   };

   m_pPinYinCombobox->m_funcDeleteStringCheck = [](const CString &sText)->BOOL
   {
      if(AfxMessageBox(_T("�Ƿ�ɾ����ѡ��"), MB_YESNO) == IDNO)
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
//    ::SetWindowText(m_pPinYinCombobox->GetSafeHwnd(), _T("�Ҿ�����"));
// 
// 
//    m_pPinYinCombobox->SendMessage(WM_SETTEXT, 0, (LPARAM)_T("wweee22"));
// 
//    //m_pPinYinCombobox->SetReadOnly(0);
// 
//    m_pPinYinCombobox->SetSel(0, -1);
//    m_pPinYinCombobox->ReplaceSel(_T("1212"));

   OnBnClickedButton5(); //��ʼ������������


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTestChinesePinYinSearchDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CTestChinesePinYinSearchDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


CString ConvertChineseUnicodeToPyt(const wchar_t* chrstr);

CString ConvertChineseToShorthand(const wchar_t* chrstr);

void CTestChinesePinYinSearchDlg::OnBnClickedButton1()
{
   // TODO: �ڴ���ӿؼ�֪ͨ����������

   CString sText;
   m_edit1.GetWindowText(sText);

   CString sText2 = ConvertChineseUnicodeToPyt(sText);
   sText2 += ConvertChineseToShorthand(sText);

   MessageBox(sText2);
}


void CTestChinesePinYinSearchDlg::OnBnSetfocusButton1()
{
   // TODO: �ڴ���ӿؼ�֪ͨ����������

   TRACE(_T("focus\n"));
}


void CTestChinesePinYinSearchDlg::OnSetFocus(CWnd* pOldWnd)
{
   CDialogEx::OnSetFocus(pOldWnd);

   // TODO: �ڴ˴������Ϣ����������

   TRACE(_T("OnSetFocus\n"));
}


void CTestChinesePinYinSearchDlg::OnKillFocus(CWnd* pNewWnd)
{
   CDialogEx::OnKillFocus(pNewWnd);

   // TODO: �ڴ˴������Ϣ����������

   TRACE(_T("OnKillFocus\n"));
}


void CTestChinesePinYinSearchDlg::OnCbnSetfocusCombo1()
{
   // TODO: �ڴ���ӿؼ�֪ͨ����������


   TRACE(_T("CBN_SET_FOCUS\n"));
}


void CTestChinesePinYinSearchDlg::OnBnClickedButton2()
{
   // TODO: �ڴ���ӿؼ�֪ͨ����������

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
   // TODO: �ڴ���ӿؼ�֪ͨ����������
   m_pPinYinCombobox->ResetContent();
}


void CTestChinesePinYinSearchDlg::OnBnClickedButton3()
{
   // TODO: �ڴ���ӿؼ�֪ͨ����������
   CString sText;
   m_edit3.GetWindowText(sText);

   m_pPinYinCombobox->SetWindowText(sText);
}


void CTestChinesePinYinSearchDlg::OnBnClickedBtnUpdate()
{
   // TODO: �ڴ���ӿؼ�֪ͨ����������
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
   // TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
   // ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
   // ���������� CRichEditCtrl().SetEventMask()��
   // ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

   // TODO:  �ڴ���ӿؼ�֪ͨ����������

   TRACE(_T("123\n"));
}


void CTestChinesePinYinSearchDlg::OnBnClickedBtnSeldlg()
{
   // TODO: �ڴ���ӿؼ�֪ͨ����������
   SetDlgItemText(IDC_MFCEDITBROWSE_NAME, _T("set dlg item"));
}


void CTestChinesePinYinSearchDlg::OnBnClickedButton4()
{
   // TODO: �ڴ���ӿؼ�֪ͨ����������
   int nCount = m_pPinYinCombobox->GetCount();
   CString sOut;
   sOut.Format(_T("%d"), nCount);
   MessageBox(sOut);
}


void CTestChinesePinYinSearchDlg::OnBnClickedButton5()
{
   // TODO: �ڴ���ӿؼ�֪ͨ����������

//    m_pPinYinCombobox->AddString(_T("ǰƬ"));
//    m_pPinYinCombobox->AddString(_T("ABCDEFGHI00000000001"));
//    m_pPinYinCombobox->AddString(_T("00000000001"));
//    m_pPinYinCombobox->AddString(_T("00000000002"));
//    m_pPinYinCombobox->AddString(_T("��������˭"));
//    m_pPinYinCombobox->AddString(_T("����˭"));
//    m_pPinYinCombobox->AddString(_T("�ҵ�����˭"));
//    m_pPinYinCombobox->AddString(_T("����������˭"));
//    m_pPinYinCombobox->AddString(_T("˭����������˭"));
//    m_pPinYinCombobox->AddString(_T("����˭����������Լ��ܻش�"));
//    m_pPinYinCombobox->AddString(_T("����ǰ��˭"));
//    m_pPinYinCombobox->AddString(_T("�ҽ�����˭"));
//    m_pPinYinCombobox->AddString(_T("��������ǰ��˭"));
//    m_pPinYinCombobox->AddString(_T("������������˭"));
//    m_pPinYinCombobox->AddString(_T("��������˭"));
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
   // TODO: �ڴ���ӿؼ�֪ͨ����������
   CString sOut;
   m_pPinYinCombobox->GetLBText(3, sOut);
   MessageBox(sOut);
}


void CTestChinesePinYinSearchDlg::OnBnClickedButton7()
{
   // TODO: �ڴ���ӿؼ�֪ͨ����������
   UpdateData(TRUE);
}


void CTestChinesePinYinSearchDlg::OnBnClickedButton8()
{
   // TODO: �ڴ���ӿؼ�֪ͨ����������

   MessageBox(m_sCBOBox2);
}


void CTestChinesePinYinSearchDlg::OnOK()
{
   // TODO: �ڴ����ר�ô����/����û���

   //CDialogEx::OnOK();
}
