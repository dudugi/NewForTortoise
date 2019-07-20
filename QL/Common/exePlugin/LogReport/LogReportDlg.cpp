
// LogReportDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LogReport.h"
#include "LogReportDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLogReportDlg �Ի���




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


// CLogReportDlg ��Ϣ�������

BOOL CLogReportDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

   ::SetProp(GetSafeHwnd(),SOFT_TAG, (HANDLE)1);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CLogReportDlg::OnPaint()
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

      //��ȡ��ǰ��ʱ��  
      COleDateTime logtime = COleDateTime::GetCurrentTime();
      CString strlog = _T("");
      strlog.Format(_T("%s%s"),logtime.Format(_T("%H:%M:%S")),strlogContent);
      CString strTick;
      DWORD dwNowTick = GetTickCount();

      if (0 != m_dwtick)
      {
         strTick.Format(_T("�����%lu"),dwNowTick - m_dwtick);
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
