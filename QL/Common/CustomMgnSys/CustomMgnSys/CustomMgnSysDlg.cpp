
// CustomMgnSysDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CustomMgnSys.h"
#include "CustomMgnSysDlg.h"
#include "DlgStaffMgnTab.h"
#include "Dialog/CustomerMgn/DlgCusMgn.h"
#include "VerInfo.h"
#include "DlgLoading.h"
#include "DBCustomer.h"
#include "DlgOrderLog.h"
#include "Base64Code.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define TIMER_ID_UpdatePdmEncrypt_TIMEOUT 100
#define TIMER_UpdatePdmEncrypt_TIME (5*60*1000) // 5����
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

UINT ThreadUpdatePdmEncrypt(LPVOID lpParam)
{
   CCustomMgnSysDlg *pThis = (CCustomMgnSysDlg *)lpParam;
   if (!pThis) return 0;
   pThis->m_bIsBeginThread = TRUE;
   CString strSQL = _T("");
   CDBVCustomerInfoList dbList;
   CADOConnEx adoThisApp;
   dbList.GetListFromDB(&adoThisApp);
   int size = dbList.GetCount();
   CBase64Code Base64Code;
   for (int i=0;i<size;++i)
   {
      auto pData = dbList.GetItem(i);
      if (pData)
      {
         CADOConnEx adoPdm;
         CString strSvr,strPwd;
         strSvr.Format(_T("%s,%d"),pData->m_cDbServerIP,pData->m_iDbServerPort);         
         strPwd = Base64Code.base64Decode(pData->m_cDbPassword);         
         CString strConnect = adoPdm.CreateConncetSqlStrByDecodeParam(strSvr,pData->m_cDbServerName,pData->m_cDbAccount,strPwd);
         adoPdm.SetConnectSqlStr(strConnect);
         if (FALSE == adoPdm.InitConnect())
         {
            TRACE(_T("�ͻ���%d����������ʧ�ܣ�"),pData->m_strCusName);
            continue;
         }
         strSQL.Format(_T("if (exists (select ID from CheckConfig))\
                          Update top(1) CheckConfig set cData1='%s',cData2='%s',cData3='%s',cData4='%s'\
                          else \
                          insert into CheckConfig (cData1,cData2,cData3,cData4) values('%s','%s','%s','%s')")
                          ,pData->m_cData1,pData->m_cData2,pData->m_cData3,pData->m_cData4,
                          pData->m_cData1,pData->m_cData2,pData->m_cData3,pData->m_cData4);        
         if (adoPdm.ExecuteSQL(strSQL))
         {
            TRACE(_T("�ͻ���%d��д�������ݳɹ�\n"),pData->m_strCusName);
         }else
         {
            TRACE(_T("�ͻ���%d��д��������ʧ��\n"),pData->m_strCusName);
         }
      }      
   }
   pThis->m_bIsBeginThread = FALSE;
   return 1;
}

class CAboutDlg : public CBCGPDialog
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
public:
   virtual BOOL OnInitDialog();
   afx_msg void OnActivateApp(BOOL bActive, DWORD dwThreadID);
};

CAboutDlg::CAboutDlg() : CBCGPDialog(CAboutDlg::IDD)
{
   EnableVisualManagerStyle(TRUE, TRUE);

}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CBCGPDialog)
   ON_WM_ACTIVATEAPP()
END_MESSAGE_MAP()


// CCustomMgnSysDlg �Ի���



UINT UM_SHOWLOADING_MSG = ::RegisterWindowMessage(_T("UM_SHOWLOADING_MSG"));


HWND CCustomMgnSysDlg::s_hWnd = nullptr;

//		by WangZY 2018/08/23
void CCustomMgnSysDlg::ShowLoadingWnd(BOOL bShow /*= TRUE*/)
{
   ::SendMessage(s_hWnd,UM_SHOWLOADING_MSG,(WPARAM)bShow,0);
}

CCustomMgnSysDlg::CCustomMgnSysDlg(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CCustomMgnSysDlg::IDD, pParent)
{
   EnableVisualManagerStyle(TRUE, TRUE);
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
   m_pDlgLoading = nullptr;
   m_bIsBeginThread = FALSE;
}

//		by WangZY 2018/08/23
CCustomMgnSysDlg::~CCustomMgnSysDlg()
{
   if (nullptr != m_pDlgLoading)
   {
      delete m_pDlgLoading;
      m_pDlgLoading = nullptr;
   }
}

void CCustomMgnSysDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCustomMgnSysDlg, CBCGPDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
   ON_BN_CLICKED(IDC_BTN_STAFFMGN, &CCustomMgnSysDlg::OnBnClickedBtnStaffmgn)
   ON_BN_CLICKED(IDC_BUTTON1, &CCustomMgnSysDlg::OnBnClickedButton1)
   ON_BN_CLICKED(IDC_BTN_LOG, &CCustomMgnSysDlg::OnBnClickedBtnLog)
   ON_REGISTERED_MESSAGE(UM_SHOWLOADING_MSG,OnShowLoadingMsg)
   ON_WM_ACTIVATEAPP()
   ON_WM_TIMER()
END_MESSAGE_MAP()


// CCustomMgnSysDlg ��Ϣ�������

BOOL CCustomMgnSysDlg::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

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
   s_hWnd = m_hWnd;
   m_pDlgLoading = new CDlgLoading;
   m_pDlgLoading->Create(CDlgLoading::IDD,this);

   CString strText;
   GetWindowText(strText);
   strText += FILE_VERSION;
   SetWindowText(strText);

	ShowWindow(SW_MAXIMIZE);

   if (theApp.m_objDBPerson.m_strUserID == _T("admin"))//����Ա�ſ�ʼ��ʱ������ʱд���ݵ��ͻ������ݿ�
   {
      SetTimer(TIMER_ID_UpdatePdmEncrypt_TIMEOUT,TIMER_UpdatePdmEncrypt_TIME,NULL);//nTime��λ��10����
   }   

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CCustomMgnSysDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CBCGPDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCustomMgnSysDlg::OnPaint()
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
		CBCGPDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CCustomMgnSysDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL HasChineseChar(const CString& str)
{
   for(int i=0; i < str.GetLength(); ++i)
   {
      if(str[i] >= 0XA0)
         return TRUE;
   }

   return FALSE;
}


void CCustomMgnSysDlg::OnBnClickedBtnStaffmgn()
{
   CDlgStaffMgnTab DlgStaffMgn;
   DlgStaffMgn.DoModal();
}


void CCustomMgnSysDlg::OnBnClickedButton1()
{
   //CCustomMgnSysDlg::ShowLoadingWnd(TRUE);
   CDlgCusMgn dlg;
   dlg.DoModal();
   //CCustomMgnSysDlg::ShowLoadingWnd(FALSE);
}

//		by WangZY 2018/08/24
void CCustomMgnSysDlg::OnBnClickedBtnLog()
{
   CDlgOrderLog dlg;
   dlg.DoModal();
}

//		by WangZY 2018/08/23
LRESULT CCustomMgnSysDlg::OnShowLoadingMsg(WPARAM wParam, LPARAM lParam)
{
   OutputDebugString(_T("OnShowLoadingMsg"));
   BOOL bShow = (BOOL)wParam;

   if (bShow)
   {
      CRect rtWnd;
      GetWindowRect(&rtWnd);
      CRect rtLoading(rtWnd);

      //rtLoading.DeflateRect(CSize(rtWnd.Width()/4,rtWnd.Height()/4));
      if (m_pDlgLoading!=nullptr
         &&IsWindow(m_pDlgLoading->GetSafeHwnd()))
      {
         m_pDlgLoading->SetWindowPos(&CWnd::wndTopMost,rtLoading.left,rtLoading.top,
            rtLoading.Width(),rtLoading.Height(),SWP_SHOWWINDOW);

#ifdef _DEBUG        
         m_pDlgLoading->SetWindowPos(&CWnd::wndNoTopMost,0,0,0,0,
            SWP_NOMOVE|SWP_NOSIZE|SWP_SHOWWINDOW);
#endif


         return 1;
      }
      else 
      {
         m_pDlgLoading = new CDlgLoading;
         m_pDlgLoading->Create(CDlgLoading::IDD,this);

         m_pDlgLoading->SetWindowPos(&CWnd::wndTopMost,rtLoading.left,rtLoading.top,
            rtLoading.Width(),rtLoading.Height(),SWP_SHOWWINDOW);
         //GetTopWindow()
         //m_pDlgLoading->SetWindowPos(GetTopWindow(),0,0,0,0,
         //   SWP_NOMOVE|SWP_NOSIZE|SWP_SHOWWINDOW);
#ifdef _DEBUG        
         m_pDlgLoading->SetWindowPos(&CWnd::wndNoTopMost,0,0,0,0,
            SWP_NOMOVE|SWP_NOSIZE|SWP_SHOWWINDOW);
#endif
         return 1;
      }
   }
   else
   {
      if (m_pDlgLoading!=nullptr
         &&IsWindow(m_pDlgLoading->GetSafeHwnd()))
      {
         m_pDlgLoading->ShowWindow(SW_HIDE);

         return 2;
      }
   }

   return 0;
}


BOOL CAboutDlg::OnInitDialog()
{
   CBCGPDialog::OnInitDialog();

   // TODO:  Add extra initialization here
 

   return TRUE;  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}


void CAboutDlg::OnActivateApp(BOOL bActive, DWORD dwThreadID)
{
   CBCGPDialog::OnActivateApp(bActive, dwThreadID);

   // TODO: Add your message handler code here

}


void CCustomMgnSysDlg::OnActivateApp(BOOL bActive, DWORD dwThreadID)
{
   CBCGPDialog::OnActivateApp(bActive, dwThreadID);

   // TODO: Add your message handler code here
   //CString str;
   //str.Format(_T("%s,%d"),bActive?_T("TRUE"):_T("FALSE"),dwThreadID);
   if (bActive)
   {
      if (m_pDlgLoading!=nullptr
         &&IsWindow(m_pDlgLoading->GetSafeHwnd())
         &&m_pDlgLoading->IsWindowVisible())
      {

#ifndef _DEBUG
         m_pDlgLoading->SetWindowPos(&CWnd::wndTopMost,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE);
#endif

      }
      //OutputDebugString(str);
   }
   else
   {
      if (m_pDlgLoading!=nullptr
         &&IsWindow(m_pDlgLoading->GetSafeHwnd())
         &&m_pDlgLoading->IsWindowVisible())
      {
         m_pDlgLoading->SetWindowPos(&CWnd::wndNoTopMost,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE);
      }
      //OutputDebugString(str);
   }
}

void CCustomMgnSysDlg::OnTimer(UINT_PTR nIDEvent)
{
   if(nIDEvent == TIMER_ID_UpdatePdmEncrypt_TIMEOUT)
   {
      //KillTimer(TIMER_ID_UpdatePdmEncrypt_TIMEOUT);
      if (!m_bIsBeginThread)
      {
         HANDLE hThrRefresh = ::CreateThread(NULL,0,
            (LPTHREAD_START_ROUTINE)ThreadUpdatePdmEncrypt,this,0,0);

         CloseHandle(hThrRefresh);
      }      
   }
   CBCGPDialog::OnTimer(nIDEvent);
}
