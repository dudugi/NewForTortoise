
// MyEqualDlg.cpp : ʵ���ļ�
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


// CMyEqualDlg �Ի���




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


// CMyEqualDlg ��Ϣ�������

BOOL CMyEqualDlg::OnInitDialog()
{
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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMyEqualDlg::OnPaint()
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
   // TODO: �ڴ���ӿؼ�֪ͨ����������

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
   lower_bound( begin,end,num)���������beginλ�õ�end-1λ�ö��ֲ��ҵ�һ�����ڻ����num�����֣��ҵ����ظ����ֵĵ�ַ���������򷵻�end��ͨ�����صĵ�ַ��ȥ��ʼ��ַbegin,�õ��ҵ������������е��±ꡣ

   upper_bound( begin,end,num)���������beginλ�õ�end-1λ�ö��ֲ��ҵ�һ������num�����֣��ҵ����ظ����ֵĵ�ַ���������򷵻�end��ͨ�����صĵ�ַ��ȥ��ʼ��ַbegin,�õ��ҵ������������е��±ꡣ
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
