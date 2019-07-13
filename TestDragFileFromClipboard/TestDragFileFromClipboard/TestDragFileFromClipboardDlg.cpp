
// TestDragFileFromClipboardDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestDragFileFromClipboard.h"
#include "TestDragFileFromClipboardDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestDragFileFromClipboardDlg �Ի���




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
END_MESSAGE_MAP()


// CTestDragFileFromClipboardDlg ��Ϣ�������

BOOL CTestDragFileFromClipboardDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTestDragFileFromClipboardDlg::OnPaint()
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
HCURSOR CTestDragFileFromClipboardDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CTestDragFileFromClipboardDlg::GetClipFilePaths(std::list<CString> *pListPaths)
{
   if (!OpenClipboard())//�򿪼�����  
      return FALSE;

   if (!IsClipboardFormatAvailable(CF_HDROP))//�жϸ�ʽ�Ƿ�����������Ҫ  
   {
      CloseClipboard();
      return FALSE;
   }
   std::list<CString> ListPaths;
   int cch;
   LPTSTR lpszFile;
   //��ȡ����  
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
   if (!OpenClipboard())//�򿪼�����
      return FALSE;

   BOOL bRet = FALSE;
   if (IsClipboardFormatAvailable(CF_HDROP))//�жϸ�ʽ�Ƿ�����������Ҫ  
   {  
      //��ȡ����  
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
