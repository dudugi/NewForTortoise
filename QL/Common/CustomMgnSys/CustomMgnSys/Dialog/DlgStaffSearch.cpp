// StaffSearchDlg.cpp : 实现文件
//
#include "StdAfx.h"
#include "CustomMgnSys.h"
#include "DlgStaffSearch.h"

#include "CGridCtrlTableAttributeOp.h"
#include "DlgGridCtrlTableStyle.h"
#include "rnstring.h"
#include "CDBFieldDefine.h"
#include "WorkLog/WorkLog.h"

// CStaffSearchDlg 对话框

IMPLEMENT_DYNAMIC(CDlgStaffSearch, CBCGPDialog)

CDlgStaffSearch::CDlgStaffSearch(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CDlgStaffSearch::IDD, pParent)
{
	m_pDlgComGrid = NULL;
	m_pCurSelectData = NULL;

	m_strDlgTitle = _T("用户管理");
	m_bShow = TRUE;
   m_pUserInfoList = nullptr;
}

CDlgStaffSearch::~CDlgStaffSearch()
{
	if (NULL != m_pDlgComGrid)
	{
		delete m_pDlgComGrid;
		m_pDlgComGrid = NULL;
	}
}

void CDlgStaffSearch::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgStaffSearch, CBCGPDialog)
	ON_MESSAGE(BCGM_GRID_ITEM_LCLICK, &CDlgStaffSearch::OnLClickedBCGGrid)
	ON_MESSAGE(BCGM_GRID_ITEM_LDBCLICK, &CDlgStaffSearch::OnDblClickedBCGGrid)	
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CStaffSearchDlg 消息处理程序

BOOL CDlgStaffSearch::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();
	
	InitComGridDlg();//初始化表格

   m_pUserInfoList = CDBUserInfoList::Instance();
   m_pUserInfoList->GetListFromDB(theApp.m_pADOConn);
	RefrushComGridDlg();

	return TRUE;
}

void CDlgStaffSearch::InitComGridDlg()//初始化表格
{
	S_GridCtrl_TableAttri attri;
	if(!CGridCtrlTableAttributeOp::Instance()->ReadTableAttri(TABLE_STAFFMGN,attri/*,TRUE*/))
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
	m_pDlgComGrid->SetWindowText(m_strDlgTitle);
	//设置表格样式xml文件名
	m_pDlgComGrid->SetTableStyleFileName(TABLE_STAFFMGN);
}

void CDlgStaffSearch::ResizeCtrl(CRect rt)
{
	if (m_pDlgComGrid && IsWindow(m_pDlgComGrid->GetSafeHwnd()))
	{
		if (m_bShow)
		{
			m_pDlgComGrid->SetWindowPos(NULL ,rt.left, rt.top, rt.right, rt.Height(), SWP_SHOWWINDOW);
		}
		else
		{
			m_pDlgComGrid->ShowWindow(SW_HIDE);
		}
	}
}

void CDlgStaffSearch::RefrushComGridDlg()
{
   if (m_pDlgComGrid && IsWindow(m_pDlgComGrid->GetSafeHwnd()))
   {      
      ASSERT(NULL != m_pUserInfoList);
      MAP_GridCtrl_AllData data;
      if (NULL != m_pUserInfoList)
      { 
         data = m_pUserInfoList->CreateGridData();
      }
      //设置初始化数据		
      m_pDlgComGrid->SetGridDataInfo(data);
      m_pDlgComGrid->RefreshGridCtrlInfo();
   }
}

void CDlgStaffSearch::OnBnClickedBtnUserdel()
{
	if(m_pCurSelectData)
	{	
		if(IDOK == MessageBox(_T("确定删除当前用户信息吗？"),_T("温馨提示："),MB_ICONQUESTION|MB_OKCANCEL))
		{
         WorkLog::InsertOneWorkLog(enLog_Cate_SQL_Transaction,enLog_Type_Add,_T(""),_T("发起事物请求"),m_strDlgTitle);
         theApp.m_pADOConn->BeginTrans();
         WorkLog::InsertOneWorkLog(enLog_Cate_TableName_Userinfo,enLog_Type_Del,m_pCurSelectData->m_strUserID,_T("删除用户"),m_strDlgTitle);
         if (m_pCurSelectData->DelAllDBInfoByUserID(theApp.m_pADOConn))
         {	
            WorkLog::InsertOneWorkLog(enLog_Cate_SQL_Transaction,enLog_Type_Add,_T(""),_T("删除用户成功，提交事物请求"),m_strDlgTitle);
            theApp.m_pADOConn->CommitTrans();
            CString str;
            str.Format(_T("删除员工,名字 %s,编号 %s") , m_pCurSelectData->m_strUserName , m_pCurSelectData->m_strUserID);

            m_pUserInfoList->DeleteItem(m_pUserInfoList->GetIndexByUserID(m_pCurSelectData->m_strUserID));
            theApp.OnShowDesktopAlert(_T("恭喜您，删除用户成功！"),TIP_COLOR_SUC,TIP_TIME_DELAY);

            RefrushComGridDlg();
            m_pCurSelectData = NULL;
         }
         else
         {
            theApp.m_pADOConn->RollbackTrans();
            WorkLog::InsertOneWorkLog(enLog_Cate_SQL_Transaction,enLog_Type_Add,_T(""),_T("删除用户失败，回滚事物"),m_strDlgTitle);
            theApp.OnShowDesktopAlert(_T("抱歉，删除用户失败（数据库执行失败）！"),TIP_COLOR_WARNING,TIP_TIME_DELAY);
         }
		}
	}
	else
	{
		theApp.OnShowDesktopAlert(_T("请选择需要删除的账户！"),TIP_COLOR_WARNING,TIP_TIME_DELAY);
	}
}


CDBUserInfoData * CDlgStaffSearch::GetSelectData()
{
	return m_pCurSelectData;
}

void CDlgStaffSearch::OnSize(UINT nType, int cx, int cy)
{
	CBCGPDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	CRect cRt;
	GetClientRect(cRt);
	ResizeCtrl(cRt);
}

LRESULT CDlgStaffSearch::OnLClickedBCGGrid(WPARAM wParam, LPARAM lParam)
{
	BCGPGRID_ITEM_INFO ii = *(BCGPGRID_ITEM_INFO*)lParam;
	m_pCurSelectData = NULL;
	if (IsWindow(m_pDlgComGrid->GetSafeHwnd()) && m_pDlgComGrid->IsValidDataRgn() && m_pDlgComGrid->IsValidRow(ii.nRow) && ii.nCol >= 0)
	{		
      CString strUserID = _T("");
      m_pDlgComGrid->GetValueByGridRowAndFieldId(strUserID,ii.nRow,DBUser_key_cUserID);
      strUserID.Trim();

      ASSERT(NULL != m_pUserInfoList);
      if (NULL != m_pUserInfoList)
      {
         m_pCurSelectData = m_pUserInfoList->GetItemByUserID(strUserID);
      }
      		
	}
	return 0;
}

LRESULT CDlgStaffSearch::OnDblClickedBCGGrid(WPARAM wParam, LPARAM lParam)
{
	BCGPGRID_ITEM_INFO ii = *(BCGPGRID_ITEM_INFO*)lParam;
	m_pCurSelectData = NULL;
	if (IsWindow(m_pDlgComGrid->GetSafeHwnd()) && m_pDlgComGrid->IsValidDataRgn() && m_pDlgComGrid->IsValidRow(ii.nRow) && ii.nCol >= 0)
	{		
      CString strUserID = _T("");
      m_pDlgComGrid->GetValueByGridRowAndFieldId(strUserID,ii.nRow,DBUser_key_cUserID);
      strUserID.Trim();     

      ASSERT(NULL != m_pUserInfoList);
      if (NULL != m_pUserInfoList)
      {
         m_pCurSelectData = m_pUserInfoList->GetItemByUserID(strUserID);
      }
      auto pWnd = this->GetParent()->GetSafeHwnd();
      ::PostMessage(pWnd,WM_MSG_STAFFMODIFY,STAFFSEARCH_TYPE_MODIFY,1);			
	}
	return 0;
}

void CDlgStaffSearch::MyShowWindow(BOOL bShow)
{
	m_bShow = bShow;
	if (bShow)
	{
		this->ShowWindow(SW_SHOW);
		if (m_pDlgComGrid && IsWindow(m_pDlgComGrid->GetSafeHwnd()))
		{
			m_pDlgComGrid->ShowWindow(SW_SHOW);
		}
	}
	else
	{
		this->ShowWindow(SW_HIDE);
		if (m_pDlgComGrid && IsWindow(m_pDlgComGrid->GetSafeHwnd()))
		{
			m_pDlgComGrid->ShowWindow(SW_HIDE);
		}
	}
}
