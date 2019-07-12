
// TestThreadEventDlg.cpp : ʵ���ļ�
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


// CTestThreadEventDlg �Ի���




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


// CTestThreadEventDlg ��Ϣ�������

BOOL CTestThreadEventDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

  
   m_pThreadInfo = new /*(std::nothrow)*/ CThreadInfo(GetSafeHwnd());
   if (!m_pThreadInfo)
   {
      return TRUE;
   }

   m_pThreadInfo->m_hEvent[0] = CreateEvent(NULL, FALSE, FALSE, NULL);
   m_pThreadInfo->m_hEvent[1] = CreateEvent(NULL, FALSE, FALSE, NULL);

   //���������������ÿһ���ļ� Emmm
   HANDLE hThrRefresh = ::CreateThread(NULL,0,
      (LPTHREAD_START_ROUTINE)ThreadFresh, m_pThreadInfo,0,0);

   CloseHandle(hThrRefresh);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTestThreadEventDlg::OnPaint()
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
HCURSOR CTestThreadEventDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTestThreadEventDlg::OnBnClickedButton1()
{
   // TODO: �ڴ���ӿؼ�֪ͨ����������
   if (m_pThreadInfo && m_pThreadInfo->m_hEvent[0])
      SetEvent(m_pThreadInfo->m_hEvent[0]);
}


void CTestThreadEventDlg::OnBnClickedButton2()
{
   // TODO: �ڴ���ӿؼ�֪ͨ����������
   if (m_pThreadInfo && m_pThreadInfo->m_hEvent[1])
      SetEvent(m_pThreadInfo->m_hEvent[1]);
}
