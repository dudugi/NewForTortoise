// DlgProgressMarquee.cpp : 实现文件
//

#include "stdafx.h"
#include "DlgProgressMarquee.h"
#include "afxdialogex.h"


// CDlgProgressMarquee 对话框

IMPLEMENT_DYNAMIC(CDlgProgressMarquee, CDialogEx)

CDlgProgressMarquee::CDlgProgressMarquee(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgProgressMarquee::IDD, pParent)
{

}

CDlgProgressMarquee::~CDlgProgressMarquee()
{
}

void CDlgProgressMarquee::DoDataExchange(CDataExchange* pDX)
{
   CDialogEx::DoDataExchange(pDX);
   DDX_Control(pDX, IDC_PROGRESS_MARQUEE, m_progressCtrl);
}

#define PROGRESS_TIME_ID   1
#define PROGRESS_TIME_LONG 30

BEGIN_MESSAGE_MAP(CDlgProgressMarquee, CDialogEx)
   ON_WM_TIMER()
END_MESSAGE_MAP()


// CDlgProgressMarquee 消息处理程序


BOOL CDlgProgressMarquee::OnInitDialog()
{
   CDialogEx::OnInitDialog();

#ifdef _UNICODE
   m_progressCtrl.ModifyStyle(0,PBS_MARQUEE);
   m_progressCtrl.SetMarquee(TRUE,30);
#else
   m_progressCtrl.SetPos(0);
   m_progressCtrl.SetStep(1);
   SetTimer(PROGRESS_TIME_ID,PROGRESS_TIME_LONG,NULL);
#endif // _UNICODE

#ifndef _DEBUG
   SetWindowPos(&CWnd::wndTop,0,0,0,0, SWP_NOMOVE|SWP_NOSIZE); //置顶	
#endif

   return TRUE;  // return TRUE unless you set the focus to a control
   // 异常: OCX 属性页应返回 FALSE
}


void CDlgProgressMarquee::OnTimer(UINT_PTR nIDEvent)
{
   

   switch(nIDEvent)
   {
   case PROGRESS_TIME_ID:
      {
         m_progressCtrl.StepIt();
         int nPos = m_progressCtrl.GetPos();
         if (100 == nPos)
         {
            m_progressCtrl.SetPos(0);
         }
      }
      break;
   }


   CDialogEx::OnTimer(nIDEvent);
}
