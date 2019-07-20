// .\Dialog\DlgLoading.cpp : implementation file
//

#include "stdafx.h"
#include "CustomMgnSys.h"
#include "DlgLoading.h"
#include "afxdialogex.h"


// CDlgLoading dialog

IMPLEMENT_DYNAMIC(CDlgLoading, CBCGPDialog)

CDlgLoading::CDlgLoading(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CDlgLoading::IDD, pParent)
{

}

CDlgLoading::~CDlgLoading()
{
}

void CDlgLoading::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
   DDX_Control(pDX, IDC_STATIC_LOADING, m_ctrLoadingGif);
}


BEGIN_MESSAGE_MAP(CDlgLoading, CBCGPDialog)
   ON_WM_SIZE()
END_MESSAGE_MAP()



// CDlgLoading message handlers


BOOL CDlgLoading::OnInitDialog()
{
   CBCGPDialog::OnInitDialog();

   // TODO:  Add extra initialization here
   UINT nIDD = IDB_LOADING;
   
   LPCTSTR szRes = MAKEINTRESOURCE(nIDD);
   if (m_ctrLoadingGif.Load(szRes,_T("GIF"))) 
   {	
      m_ctrLoadingGif.Draw(); 
      m_ctrLoadingGif.SetBkColor(RGB(255,0,0));
   }

   SetBackgroundColor(RGB(46,63,93));
   ::SetWindowLong(GetSafeHwnd(),GWL_EXSTYLE,::GetWindowLongPtr(GetSafeHwnd(),
      GWL_EXSTYLE)|WS_EX_LAYERED);
   SetLayeredWindowAttributes(0,(255*70)/100,LWA_ALPHA);

   
   
   return TRUE;  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgLoading::OnSize(UINT nType, int cx, int cy)
{
   CBCGPDialog::OnSize(nType, cx, cy);

   // TODO: Add your message handler code here
   if (nullptr != m_ctrLoadingGif.GetSafeHwnd())
   {
      CSize si = m_ctrLoadingGif.GetSize();
      m_ctrLoadingGif.SetWindowPos(NULL,(cx-si.cx)/2,(cy-si.cy)/2,0,0,SWP_NOSIZE);
   }
}
