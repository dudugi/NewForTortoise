// DlgCusMgn.cpp : 实现文件
//

#include "stdafx.h"
#include "CustomMgnSys.h"
#include "DlgCusMgn.h"
#include "afxdialogex.h"
#include "DlgCusModify.h"
#include "CGridCtrlTableAttributeOp.h"
#include "CDBFieldDefine.h"
#include "CustomMgnSysDlg.h"
#include "WorkLog/WorkLog.h"
#include "DBCusOpRecords.h"

// CDlgCusMgn 对话框

IMPLEMENT_DYNAMIC(CDlgCusMgn, CBCGPDialog)

CDlgCusMgn::CDlgCusMgn(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CDlgCusMgn::IDD, pParent)
{
   m_pDlgCusModify = NULL;
   m_pDlgComGrid = NULL;
   m_strTitle = _T("客户管理");
   m_iShowMode = en_view;
   m_bDoFreshing = FALSE;
}

CDlgCusMgn::~CDlgCusMgn()
{
   if (m_pDlgCusModify != NULL)
   {
      delete m_pDlgCusModify;
      m_pDlgCusModify = NULL;
   }

   if (m_pDlgComGrid != NULL)
   {
      delete m_pDlgComGrid;
      m_pDlgComGrid = NULL;
   }
}

void CDlgCusMgn::DoDataExchange(CDataExchange* pDX)
{
   CBCGPDialog::DoDataExchange(pDX);
   DDX_Control(pDX, IDC_BTN_ADD, m_btn_add);
   DDX_Control(pDX, IDC_BTN_DEL, m_btn_del);
   DDX_Control(pDX, IDC_BTN_MODIFY, m_btn_modify);
   DDX_Control(pDX, IDC_BTN_REFRESH, m_btn_refresh);
   DDX_Control(pDX, IDC_BTN_SAVE, m_btn_save);
   DDX_Control(pDX, IDC_BTN_CANCEL, m_btn_cancel);
   DDX_Control(pDX, IDC_BTN_Expiring, m_btn_expiring);
   DDX_Control(pDX, IDC_BTN_Expired, m_btn_expired);
   DDX_Control(pDX, IDC_EDIT_DAYS, m_edit_days);
}

BOOL CDlgCusMgn::OnInitDialog()
{
   //CCustomMgnSysDlg::ShowLoadingWnd(TRUE);
   CBCGPDialog::OnInitDialog();
   

   m_bDoFreshing = FALSE;
   m_edit_days.SetWindowText(_T("1"));
   InitGridCtrl();
   ShowDlgMode(m_iShowMode);
   DoRefreshData();

   return TRUE;  
}

void CDlgCusMgn::InitGridCtrl()
{
   S_GridCtrl_TableAttri attri;
   if(!CGridCtrlTableAttributeOp::Instance()->ReadTableAttri(TABLE_CUSMGN,attri/*,TRUE*/))
   {
      TRACE(_T("CDlgStaffSearch:Failed\n"));
   }	
   //新表格控件，封装的数据
   MAP_GridCtrl_AllData data ;
   if (NULL != m_pDlgComGrid)
   {
      delete m_pDlgComGrid;
      m_pDlgComGrid = NULL;
   }
   m_pDlgComGrid = new CDlgBCGGrid;

   if (!IsWindow(m_pDlgComGrid->GetSafeHwnd()))
   {
      m_pDlgComGrid->Create(CDlgBCGGrid::IDD,this);
   }

   //设置初始化数据
   m_pDlgComGrid->SetGridAttriAndDatas(attri,data);
   m_pDlgComGrid->RefreshGridCtrlInfo();

   //设置打印导出title
   m_pDlgComGrid->SetWindowText(m_strTitle);
   //设置表格样式xml文件名
   m_pDlgComGrid->SetTableStyleFileName(TABLE_CUSMGN);
}

void CDlgCusMgn::ShowCusModifyDlg(BOOL bShow,CDBVCustomerInfoData* pCusData)
{
   if (m_pDlgCusModify == NULL)
   {
      m_pDlgCusModify = new CDlgCusModify;
   }

   if (!IsWindow(m_pDlgCusModify->GetSafeHwnd()))
   {
      m_pDlgCusModify->Create(CDlgCusModify::IDD,this);
   }
   if (bShow)
   {
      m_pDlgCusModify->SetCusData(pCusData);
      CRect rt;
      GetClientRect(rt);
      int iHeight = 40; //第一排按钮位置；
      rt.top += iHeight;
      m_pDlgCusModify->SetWindowPos(NULL,rt.left,rt.top,rt.Width(),rt.Height(),SWP_SHOWWINDOW);
   }
   else
   {
      m_pDlgCusModify->ShowWindow(SW_HIDE);
   }
}

void CDlgCusMgn::ShowDlgMode(int iFlag)
{
   switch(iFlag)
   {
   default:
   case en_view:
      {
         m_btn_add.EnableWindow(TRUE);
         m_btn_del.EnableWindow(TRUE);
         m_btn_modify.EnableWindow(TRUE);
         m_btn_refresh.EnableWindow(TRUE);
         m_btn_cancel.EnableWindow(FALSE);
         m_btn_save.EnableWindow(FALSE);
         m_edit_days.EnableWindow(TRUE);
         m_btn_expiring.EnableWindow(TRUE);
         m_btn_expired.EnableWindow(TRUE);
         CRect rt;
         GetClientRect(rt);
         int iHeight = 40;
         rt.top += iHeight;
         if (m_pDlgComGrid && IsWindow(m_pDlgComGrid->GetSafeHwnd()))
         {
             m_pDlgComGrid->SetWindowPos(NULL,rt.left,rt.top,rt.Width(),rt.Height(),SWP_SHOWWINDOW);
         }
      }
      break;
   case en_modify:
      {
         m_btn_add.EnableWindow(FALSE);
         m_btn_del.EnableWindow(FALSE);
         m_btn_modify.EnableWindow(FALSE);
         m_btn_refresh.EnableWindow(FALSE);
         m_btn_cancel.EnableWindow(TRUE);
         m_btn_save.EnableWindow(TRUE);
         m_edit_days.EnableWindow(FALSE);
         m_btn_expiring.EnableWindow(FALSE);
         m_btn_expired.EnableWindow(FALSE);
         if (m_pDlgComGrid && IsWindow(m_pDlgComGrid->GetSafeHwnd()))
         {
             m_pDlgComGrid->ShowWindow(SW_HIDE);
         }
      }
      break;
   }
}

void CDlgCusMgn::DoRefreshData()
{
   if (m_bDoFreshing == TRUE)
   {
      theApp.OnShowDesktopAlert(_T("刷新太频繁啦~~~，请稍后再试！"),TIP_COLOR_WARNING,2);
      return;
   }
   m_bDoFreshing = TRUE;
   MAP_GridCtrl_AllData all_data;
   if(!CDBVCustomerInfoList::Instance()->GetAllCustomerGridData(theApp.m_pADOConn,&theApp.m_LDK,all_data))
   {
      theApp.OnShowDesktopAlert(_T("读取数据失败：加密数据异常！"),TIP_COLOR_WARNING,2);
      m_bDoFreshing = FALSE;
      return;
   }
   if (m_pDlgComGrid)
   {
      m_pDlgComGrid->SetGridDataInfo(all_data);
      m_pDlgComGrid->RefreshGridCtrlInfo();
   }
   all_data.clear();
   m_bDoFreshing = FALSE;
}

BEGIN_MESSAGE_MAP(CDlgCusMgn, CBCGPDialog)
   ON_WM_SIZE()
   ON_BN_CLICKED(IDC_BTN_ADD, &CDlgCusMgn::OnBnClickedBtnAdd)
   ON_BN_CLICKED(IDC_BTN_DEL, &CDlgCusMgn::OnBnClickedBtnDel)
   ON_BN_CLICKED(IDC_BTN_MODIFY, &CDlgCusMgn::OnBnClickedBtnModify)
   ON_BN_CLICKED(IDC_BTN_REFRESH, &CDlgCusMgn::OnBnClickedBtnRefresh)
   ON_BN_CLICKED(IDC_BTN_SAVE, &CDlgCusMgn::OnBnClickedBtnSave)
   ON_BN_CLICKED(IDC_BTN_CANCEL, &CDlgCusMgn::OnBnClickedBtnCancel)
   ON_MESSAGE(BCGM_GRID_ITEM_LCLICK,&CDlgCusMgn::OnLClickedComGridMsg)
   ON_MESSAGE(BCGM_GRID_ITEM_LDBCLICK,&CDlgCusMgn::OnLDBClickedComGridMsg)
   ON_MESSAGE(BCGM_GRID_ITEM_RCLICK,&CDlgCusMgn::OnRClickedComGridMsg)
   ON_BN_CLICKED(IDC_BTN_Expiring, &CDlgCusMgn::OnBnClickedBtnExpiring)
   ON_BN_CLICKED(IDC_BTN_Expired, &CDlgCusMgn::OnBnClickedBtnExpired)
END_MESSAGE_MAP()

// CDlgCusMgn 消息处理程序

void CDlgCusMgn::OnBnClickedBtnAdd()
{
   m_iShowMode = en_modify;
   m_oData.ResetData();
   ShowCusModifyDlg(TRUE,&m_oData);
   ShowDlgMode(m_iShowMode);
}

void CDlgCusMgn::OnBnClickedBtnDel()
{
   if (m_pDlgComGrid)
   {
      MAP_GridCtrl_AllData all_sel;
      m_pDlgComGrid->GetSelectData(all_sel);
      vector<CString> vecSelCusCode;
      for (auto itr_ = all_sel.begin(); itr_ != all_sel.end(); ++itr_)
      {
         auto itr_id = itr_->second.find(DBCusBase_key_cCusCode);
         if (itr_id != itr_->second.end())
         {
            vecSelCusCode.push_back(itr_id->second.strValue);
         }
      }
      if (vecSelCusCode.size() <=0)
      {
         theApp.OnShowDesktopAlert(_T("请选择数据后再删除！"));
         return;
      }

      CString strSql = CDBVCustomerInfoList::Instance()->GetDelSql_CustomerDataByCusCode(vecSelCusCode);
      
      theApp.m_pADOConn->BeginTrans();
      WorkLog::InsertMultiWorkLog(enLog_Cate_TableName_Customer,enLog_Type_Del,vecSelCusCode,_T("删除客户数据"),m_strTitle);
      if (!strSql.IsEmpty() && theApp.m_pADOConn->ExecuteSQL(strSql))
      {
         theApp.m_pADOConn->CommitTrans();
         WorkLog::InsertOneWorkLog(enLog_Cate_SQL_Transaction,enLog_Type_Add,_T(""),_T("删除数据成功！,提交事物请求"),m_strTitle);
         //插入客户操作记录表 yangjr 2018/8/30
         int size = vecSelCusCode.size();
         CDBCusOpRecordsData DBOpRd;
         DBOpRd.m_cOpType = _T("删除");
         for (int i=0; i<size; ++i)
         {
            DBOpRd.m_strCusCode = vecSelCusCode[i];
         }  
         DBOpRd.InsertDBInfo(theApp.m_pADOConn);
         theApp.OnShowDesktopAlert(_T("删除成功！"),TIP_COLOR_SUC,1);        
      }
      else{
         theApp.m_pADOConn->RollbackTrans();
         WorkLog::InsertOneWorkLog(enLog_Cate_SQL_Transaction,enLog_Type_Add,_T(""),_T("删除数据失败！,回滚事物"),m_strTitle);
         theApp.OnShowDesktopAlert(_T("删除失败！请重新操作"),TIP_COLOR_WARNING,3);
      }
      DoRefreshData();
   }
}

void CDlgCusMgn::OnBnClickedBtnModify()
{
   if (m_pDlgComGrid)
   {
      int nRow = m_pDlgComGrid->GetFocusRow();
      if (nRow >= 0)
      {   
         m_iShowMode = en_modify;
         CString strID;
         m_pDlgComGrid->GetValueByGridRowAndFieldId(strID,nRow,DBCusBase_key_ID);
         m_oData.m_nID = _ttoi(strID);
        
         CDBVCustomerInfoList::Instance()->GetCustomerDataByID(theApp.m_pADOConn,m_oData.m_nID,&theApp.m_LDK,&m_oData);
         ShowCusModifyDlg(TRUE,&m_oData);

         ShowDlgMode(m_iShowMode);
      }
      else
      {
         theApp.OnShowDesktopAlert(_T("请选择一条数据！"));
         return;
      }
   }
}

void CDlgCusMgn::OnBnClickedBtnRefresh()
{
   CCustomMgnSysDlg::ShowLoadingWnd(TRUE);;
   DoRefreshData();
   CCustomMgnSysDlg::ShowLoadingWnd(FALSE);
}

void CDlgCusMgn::OnBnClickedBtnSave()
{
   if (m_pDlgCusModify)
   {
      if(!m_pDlgCusModify->DoSave(&m_oData))
      {
         theApp.OnShowDesktopAlert(_T("加密数据加密失败！"),TIP_COLOR_WARNING,2);
         return;
      }
      //验证客户编号
      if (m_oData.m_strCusCode.Trim() == _T(""))
      {
         theApp.OnShowDesktopAlert(_T("客户编码不能为空！"),TIP_COLOR_WARNING,2);
         return;
      }

      //验证客户编码是否存在 id =0
      if (m_oData.m_nID <= 0)
      {
         if (TRUE == CDBVCustomerInfoList::Instance()->CheckCusCodeExists(theApp.m_pADOConn,m_oData.m_strCusCode))
         {
            theApp.OnShowDesktopAlert(_T("客户编号已经存在，保存失败！"),TIP_COLOR_WARNING,3);
            return;
         }
      }

      //检查数据库配置
      if (m_oData.m_cDbServerName.IsEmpty() || m_oData.m_cDbAccount.IsEmpty() 
         || m_oData.m_cDbPassword.IsEmpty() || m_oData.m_cDbServerIP.IsEmpty())
      {
         theApp.OnShowDesktopAlert(_T("数据库信息配置错误，保存失败！"),TIP_COLOR_WARNING,3);
         return;
      }
      else
      {
         //验证数据库是否可以连接
         if (m_oData.m_isLocalDB == 0)    //云端数据库
         {
            CString strSvr;
            strSvr.Format(_T("%s,%d"),m_oData.m_cDbServerIP,m_oData.m_iDbServerPort);
            CBase64Code Base64Code;
            CString strConnetInfo = CADOConnEx::CreateConncetSqlStrByDecodeParam(strSvr,m_oData.m_cDbServerName,
               m_oData.m_cDbAccount, Base64Code.base64Decode(m_oData.m_cDbPassword));
            CADOConnEx ado_test;
            ado_test.SetConnectSqlStr(strConnetInfo);
            if (FALSE == ado_test.InitConnect())
            {
               theApp.OnShowDesktopAlert(_T("数据连接失败！请检查数据库配置"),TIP_COLOR_WARNING,3);
               //return;
            }
            else{
               //写入认证信息
               CString strSqlCertification = _T("");
               strSqlCertification.Format(_T("declare @num int\
                                             select @num = count(*) from CheckConfig;\
                                             if @num <= 0\
                                             begin \
                                             SET NOCOUNT ON\
                                             insert into CheckConfig(cData1,cData2,cData3,cData4) values ('%s','%s','%s','%s')\
                                             end\
                                             else\
                                             begin\
                                             SET NOCOUNT ON\
                                             update CheckConfig set cData1 = '%s',cData2 = '%s',cData3 = '%s',cData4 = '%s'\
                                             end\
                                             select @@ROWCOUNT as num;"),m_oData.m_cData1,m_oData.m_cData2,m_oData.m_cData3,m_oData.m_cData4
                                             ,m_oData.m_cData1,m_oData.m_cData2,m_oData.m_cData3,m_oData.m_cData4);
               if (ado_test.ExecuteSQL(strSqlCertification) == FALSE)
               {
                  ado_test.CloseConnect();
                  theApp.OnShowDesktopAlert(_T("写入PDM认证信息失败！请重新操作"),TIP_COLOR_WARNING,3);
                  return;
               }
               WorkLog::InsertOneWorkLog(enLog_Cate_TableName_CheckConfig,enLog_Type_Add,_T("写入PDM认证信息成功"),
                  m_oData.m_cData1+m_oData.m_cData2+m_oData.m_cData3+m_oData.m_cData4,m_strTitle);
               ado_test.CloseConnect();
            }
         }
      }

      WorkLog::InsertOneWorkLog(enLog_Cate_SQL_Transaction,enLog_Type_Add,_T(""),_T("发起事物请求"),m_strTitle);
      theApp.m_pADOConn->BeginTrans();
      BOOL bRet = FALSE;
      if (m_oData.m_nID <=0)     //insert
      {
         CString strSqlTemp = m_oData.GetInsertSql();
         bRet = theApp.m_pADOConn->ExecuteSQL(strSqlTemp);
         WorkLog::InsertOneWorkLog(enLog_Cate_TableName_Customer,enLog_Type_Add,m_oData.m_strCusCode,strSqlTemp,m_strTitle);
      }
      else  //update
      {
         CString strSqlTemp = m_oData.GetUpdateSql();
         bRet = theApp.m_pADOConn->ExecuteSQL(strSqlTemp);
         WorkLog::InsertOneWorkLog(enLog_Cate_TableName_Customer,enLog_Type_Upadate,m_oData.m_strCusCode,strSqlTemp,m_strTitle);
      }

      if (bRet)
      {
         theApp.m_pADOConn->CommitTrans();
         WorkLog::InsertOneWorkLog(enLog_Cate_SQL_Transaction,enLog_Type_Add,_T(""),_T("客户数据保存成功，提交SQL事物成功"),m_strTitle);
         theApp.OnShowDesktopAlert(_T("保存数据库成功！"),TIP_COLOR_SUC,1);

         //插入客户操作记录表 yangjr 2018/8/30
         CDBCusOpRecordsData DBOpRd;
         DBOpRd.Copy(&m_oData);
         DBOpRd.m_cOpType = _T("新增");
         if (m_oData.m_nID >0)     //insert
         {            
            DBOpRd.m_cOpType = _T("更新");
         }
         DBOpRd.InsertDBInfo(theApp.m_pADOConn);

         DoRefreshData();  
         m_iShowMode = en_view;
         ShowDlgMode(m_iShowMode);
         ShowCusModifyDlg(FALSE,NULL);
      }
      else
      {
         theApp.m_pADOConn->RollbackTrans();
         WorkLog::InsertOneWorkLog(enLog_Cate_SQL_Transaction,enLog_Type_Add,_T(""),_T("客户数据保存失败，回滚SQL事物"),m_strTitle);
         theApp.OnShowDesktopAlert(_T("保存数据库失败！"),TIP_COLOR_WARNING,2);
      }
   }
}

void CDlgCusMgn::OnBnClickedBtnCancel()
{
   m_iShowMode = en_view;
   ShowDlgMode(m_iShowMode);
   ShowCusModifyDlg(FALSE,NULL);
}

void CDlgCusMgn::OnSize(UINT nType, int cx, int cy)
{
   CBCGPDialog::OnSize(nType, cx, cy);
   CRect rt;
   GetClientRect(rt);
   int iHeight = 45;
   rt.top += iHeight;
   if (m_pDlgComGrid && IsWindow(m_pDlgComGrid->GetSafeHwnd()))
   {
      if (m_iShowMode == en_view)   
         m_pDlgComGrid->SetWindowPos(NULL,rt.left,rt.top,rt.Width(),rt.Height(),SWP_SHOWWINDOW);
      else
         m_pDlgComGrid->ShowWindow(SW_HIDE);
   }
}

LRESULT CDlgCusMgn::OnLClickedComGridMsg(WPARAM wParam, LPARAM lParam)
{
   return 1;
}

LRESULT CDlgCusMgn::OnLDBClickedComGridMsg(WPARAM wParam, LPARAM lParam)
{
   if (m_pDlgComGrid && IsWindow(m_pDlgComGrid->GetSafeHwnd()))
   {
      BCGPGRID_ITEM_INFO ii = *(BCGPGRID_ITEM_INFO*)lParam;
      int nRow = ii.nRow;
      if (nRow>= 0)
      {
         m_iShowMode = en_modify;
         CString strID;
         m_pDlgComGrid->GetValueByGridRowAndFieldId(strID,nRow,DBCusBase_key_ID);
         m_oData.m_nID = _ttoi(strID);
         CDBVCustomerInfoList::Instance()->GetCustomerDataByID(theApp.m_pADOConn,m_oData.m_nID,&theApp.m_LDK,&m_oData);
         ShowCusModifyDlg(TRUE,&m_oData);

         ShowDlgMode(m_iShowMode);
      }
   }
   return 1;
}

LRESULT CDlgCusMgn::OnRClickedComGridMsg(WPARAM wParam, LPARAM lParam)
{
   return 1;
}

void CDlgCusMgn::OnBnClickedBtnExpiring()
{
   if (m_bDoFreshing == TRUE)
   {
      theApp.OnShowDesktopAlert(_T("刷新太频繁啦~~~，请稍后再试！"),TIP_COLOR_WARNING,2);
      return;
   }

   CString strDays;
   m_edit_days.GetWindowText(strDays);

   m_bDoFreshing = TRUE;
   MAP_GridCtrl_AllData all_data;
   if(!CDBVCustomerInfoList::Instance()->GetExpiringCustomerGridData(theApp.m_pADOConn,_ttoi(strDays),&theApp.m_LDK,all_data))
   {
      theApp.OnShowDesktopAlert(_T("读取数据失败：加密数据异常！"),TIP_COLOR_WARNING,2);
      m_bDoFreshing = FALSE;
      return;
   }
   if (m_pDlgComGrid)
   {
      m_pDlgComGrid->SetGridDataInfo(all_data);
      m_pDlgComGrid->RefreshGridCtrlInfo();
   }
   all_data.clear();
   m_bDoFreshing = FALSE;
}

void CDlgCusMgn::OnBnClickedBtnExpired()
{
   if (m_bDoFreshing == TRUE)
   {
      theApp.OnShowDesktopAlert(_T("刷新太频繁啦~~~，请稍后再试！"),TIP_COLOR_WARNING,2);
      return;
   }
   m_bDoFreshing = TRUE;
   MAP_GridCtrl_AllData all_data;
   if(!CDBVCustomerInfoList::Instance()->GetExpiredCustomerGridData(theApp.m_pADOConn,&theApp.m_LDK,all_data))
   {
      theApp.OnShowDesktopAlert(_T("读取数据失败：加密数据异常！"),TIP_COLOR_WARNING,2);
      m_bDoFreshing = FALSE;
      return;
   }
   if (m_pDlgComGrid)
   {
      m_pDlgComGrid->SetGridDataInfo(all_data);
      m_pDlgComGrid->RefreshGridCtrlInfo();
   }
   all_data.clear();
   m_bDoFreshing = FALSE;
}
