// StaffMgnTabDlg.cpp : 实现文件
//

#include "StdAfx.h"
#include "CustomMgnSys.h"
#include "DlgStaffMgnTab.h"
#include "DBUserInfo.h"
#include "Base64Code.h"

// CStaffMgnTabDlg 对话框

IMPLEMENT_DYNAMIC(CDlgStaffMgnTab, CBCGPDialog)

   CDlgStaffMgnTab::CDlgStaffMgnTab(CWnd* pParent /*=NULL*/)
   : CBCGPDialog(CDlgStaffMgnTab::IDD, pParent)
{
   m_pStaffSearchDlg = NULL;
   m_pStaffModifyDlg = NULL;
   m_nOpenFlag = STAFF_MAINTYPE_VIEW;
}

CDlgStaffMgnTab::~CDlgStaffMgnTab()
{
   if (NULL != m_pStaffSearchDlg)
   {
      delete m_pStaffSearchDlg;
      m_pStaffSearchDlg = NULL;
   }
   if (NULL != m_pStaffModifyDlg)
   {
      delete m_pStaffModifyDlg;
      m_pStaffModifyDlg = NULL;
   }
}

void CDlgStaffMgnTab::DoDataExchange(CDataExchange* pDX)
{
   CBCGPDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgStaffMgnTab, CBCGPDialog)  
   ON_WM_DESTROY()
   ON_BN_CLICKED(IDC_BTN_ADDSTAFF_STAFFMAINTAIN, &CDlgStaffMgnTab::OnBtnAddStaff)
   ON_BN_CLICKED(IDC_BTN_CHANGESTAFF_STAFFMAINTAIN, &CDlgStaffMgnTab::OnBtnChangeStaff)
   ON_BN_CLICKED(IDC_BTN_DELSTAFF_STAFFMAINTAIN, &CDlgStaffMgnTab::OnBtnDelStaff)  
   ON_MESSAGE(WM_MSG_STAFFMODIFY, &CDlgStaffMgnTab::OnStaffModifyAct)
   ON_WM_SIZE()
END_MESSAGE_MAP()


// CStaffMgnTabDlg 消息处理程序
BOOL CDlgStaffMgnTab::OnInitDialog()
{
   CBCGPDialog::OnInitDialog();
   InitStaffSearchDlg();  
   return TRUE;
}

void CDlgStaffMgnTab::OnDestroy()
{
   CBCGPDialog::OnDestroy();

   if (NULL != m_pStaffSearchDlg)
   {
      if (IsWindow(m_pStaffSearchDlg->GetSafeHwnd()))
      {
         m_pStaffSearchDlg->DestroyWindow();
      }

      delete m_pStaffSearchDlg;
      m_pStaffSearchDlg = NULL;
   }
   if (NULL != m_pStaffModifyDlg)
   {
      if (IsWindow(m_pStaffModifyDlg->GetSafeHwnd()))
      {
         m_pStaffModifyDlg->DestroyWindow();
      }

      delete m_pStaffModifyDlg;
      m_pStaffModifyDlg = NULL;
   }
}

void CDlgStaffMgnTab::OnBtnAddStaff()
{
   if (m_pStaffSearchDlg && ::IsWindow(m_pStaffSearchDlg->GetSafeHwnd()))
   {
      m_pStaffSearchDlg->MyShowWindow(FALSE);
   }

   if (m_pStaffModifyDlg == NULL)
   {
      InitStaffModifyDlg(STAFF_TYPE_ADD);
   }
   else
   {
      m_pStaffModifyDlg->SetModifyMode(STAFF_TYPE_ADD);
      m_pStaffModifyDlg->RefreshData();
      m_pStaffModifyDlg->MyShowWindow(TRUE);      
      ResizeCtrl();
   }

   m_nOpenFlag = STAFF_MAINTYPE_ADD;
   UpdateBtnState();
}

void CDlgStaffMgnTab::OnBtnChangeStaff()
{
   if (NULL == m_pStaffSearchDlg)
   {
      return;
   }
   auto pData = m_pStaffSearchDlg->GetSelectData();
   if (NULL == pData)
   {
      theApp.OnShowDesktopAlert(_T("请选择需要修改的账户！"),TIP_COLOR_WARNING,TIP_TIME_DELAY);
      return;
   }

   if (0 == pData->m_strUserID.CompareNoCase(_T("admin")))
   {
      theApp.OnShowDesktopAlert(_T("不允许修改超级管理员admin！"),TIP_COLOR_WARNING,TIP_TIME_DELAY);
      return;
   }
     
   if (NULL != m_pStaffSearchDlg)
   {
      m_pStaffSearchDlg->MyShowWindow(FALSE);
   }

   if (m_pStaffModifyDlg == NULL)
   {
      InitStaffModifyDlg(STAFF_TYPE_MODIFY,pData);
   }
   else
   {
      m_pStaffModifyDlg->SetModifyMode(STAFF_TYPE_MODIFY,pData);
      m_pStaffModifyDlg->RefreshData();
      m_pStaffModifyDlg->MyShowWindow(TRUE);
   }


   m_nOpenFlag = STAFF_MAINTYPE_MODIFY;
   UpdateBtnState();
}

void CDlgStaffMgnTab::OnBtnDelStaff()
{
   if(NULL == m_pStaffSearchDlg)
   {		
      return;
   }

   auto pData = m_pStaffSearchDlg->GetSelectData();
   if (NULL == pData)
   {
      theApp.OnShowDesktopAlert(_T("请选择需要删除的账户！"),TIP_COLOR_WARNING,TIP_TIME_DELAY);
      return;
   }

   if (0 == pData->m_strUserID.CompareNoCase(_T("admin")))
   {
      theApp.OnShowDesktopAlert(_T("不允许删除超级管理员admin！"),TIP_COLOR_WARNING,TIP_TIME_DELAY);
      return;
   }

   //if (pData->m_strcUserID == theApp.m_objDBPerson.m_strUserID)
   //{
   //   theApp.OnShowDesktopAlert(_T("不允许删除自己！"),TIP_COLOR_WARNING,TIP_TIME_DELAY);
   //   return;
   //} 
   m_pStaffSearchDlg->OnBnClickedBtnUserdel();
}
void CDlgStaffMgnTab::UpdateBtnState()
{
   BOOL bEnableWindow = FALSE;

   if (STAFF_MAINTYPE_VIEW == m_nOpenFlag)
   {
      bEnableWindow = TRUE;
   }
   else
   {
      bEnableWindow = FALSE;
   }

   auto pBtn = GetDlgItem(IDC_BTN_ADDSTAFF_STAFFMAINTAIN);
   pBtn->EnableWindow(bEnableWindow);

   pBtn = GetDlgItem(IDC_BTN_CHANGESTAFF_STAFFMAINTAIN);
   pBtn->EnableWindow(bEnableWindow);

   pBtn = GetDlgItem(IDC_BTN_DELSTAFF_STAFFMAINTAIN);
   pBtn->EnableWindow(bEnableWindow);
}

void CDlgStaffMgnTab::InitStaffSearchDlg()
{
   if (NULL != m_pStaffSearchDlg)
   {
      delete m_pStaffSearchDlg;
      m_pStaffSearchDlg = NULL;
   }

   m_pStaffSearchDlg = new CDlgStaffSearch;
   m_pStaffSearchDlg->Create(CDlgStaffSearch::IDD,this);
   

   ResizeCtrl();
}

void CDlgStaffMgnTab::InitStaffModifyDlg( int nMode,CDBUserInfoData *pData /*= NULL*/ )
{
   if (NULL != m_pStaffModifyDlg)
   {
      delete m_pStaffModifyDlg;
      m_pStaffModifyDlg = NULL;
   }

   m_pStaffModifyDlg = new CDlgStaffModify;
   m_pStaffModifyDlg->SetModifyMode(nMode,pData);

   m_pStaffModifyDlg->Create(CDlgStaffModify::IDD,this);
     
   ResizeCtrl();
}

LRESULT CDlgStaffMgnTab::OnStaffModifyAct( WPARAM wParam,LPARAM lParam )
{
   int nFlag = (int)lParam;
   int nType = (int)wParam;
   if (nFlag == 1)
   {
      switch(nType)
      {
      case STAFFSEARCH_TYPE_MODIFY:
         {
            OnBtnChangeStaff();
         }
         break;
      case STAFFSEARCH_TYPE_ADD:
         {
            OnBtnAddStaff();
         }
         break;
      default:
         break;
      }
   }
   else if (nFlag == 0)
   {
      switch(nType)
      {
      case STAFFMODIFY_TYPE_SAVE:
         {
            if (NULL != m_pStaffModifyDlg)
            { 
               m_pStaffModifyDlg->MyShowWindow(FALSE);
            }
            if (NULL != m_pStaffSearchDlg)
            {
               RefreshSearchData();               
               m_pStaffSearchDlg->MyShowWindow(TRUE);
            }
            else
            {
               InitStaffSearchDlg();
            }

            m_nOpenFlag = STAFF_MAINTYPE_VIEW;
            UpdateBtnState();
         }
         break;
      case STAFFMODIFY_TYPE_EXIT:
         {
            if (NULL != m_pStaffModifyDlg)
            {
               m_pStaffModifyDlg->MyShowWindow(FALSE);
            }
            if (NULL != m_pStaffSearchDlg)
            {
               RefreshSearchData();
               m_pStaffSearchDlg->MyShowWindow(TRUE);
            }
            else
            {
               InitStaffSearchDlg();
            }
            m_nOpenFlag = STAFF_MAINTYPE_VIEW;
            UpdateBtnState();
         }
         break;
      default:
         break;
      }
   }	

   return 0L;
}


void CDlgStaffMgnTab::OnSize(UINT nType, int cx, int cy)
{
   CBCGPDialog::OnSize(nType, cx, cy);

   // TODO: 在此处添加消息处理程序代码  
   ResizeCtrl();
}

void  CDlgStaffMgnTab::ResizeCtrl()
{
   auto pPic = GetDlgItem(IDC_STATIC_CHILD_POS_STAFFTABDLG);
   if (!pPic || !IsWindow(pPic->GetSafeHwnd()))
   {
      return;
   }
   CRect dlgRect;
   GetClientRect(dlgRect);
   CRect rt;
   pPic->GetWindowRect(rt); 
   ScreenToClient(&rt);
   pPic->SetWindowPos(NULL ,rt.left, rt.top, dlgRect.right, dlgRect.Height()-rt.top, SWP_SHOWWINDOW);  
   if (m_pStaffSearchDlg && IsWindow(m_pStaffSearchDlg->GetSafeHwnd()))
   {
      if (m_pStaffSearchDlg->GetMyShowFlag())
         m_pStaffSearchDlg->SetWindowPos(NULL ,rt.left, rt.top, dlgRect.right-5, dlgRect.bottom-5, SWP_SHOWWINDOW);
      else
         m_pStaffSearchDlg->MyShowWindow(FALSE);
   }

   if (m_pStaffModifyDlg && IsWindow(m_pStaffModifyDlg->GetSafeHwnd()))
   {
      if (m_pStaffModifyDlg->GetMyShowFlag())
         m_pStaffModifyDlg->SetWindowPos(NULL ,rt.left, rt.top, dlgRect.right, dlgRect.bottom, SWP_SHOWWINDOW);
      else
         m_pStaffModifyDlg->MyShowWindow(FALSE);
   }
}

void CDlgStaffMgnTab::RefreshSearchData()
{
   if (NULL != m_pStaffSearchDlg)
   { 
      m_pStaffSearchDlg->RefrushComGridDlg();
   }
}

