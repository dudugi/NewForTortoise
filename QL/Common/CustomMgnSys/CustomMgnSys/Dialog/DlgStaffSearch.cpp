// StaffSearchDlg.cpp : ʵ���ļ�
//
#include "StdAfx.h"
#include "CustomMgnSys.h"
#include "DlgStaffSearch.h"

#include "CGridCtrlTableAttributeOp.h"
#include "DlgGridCtrlTableStyle.h"
#include "rnstring.h"
#include "CDBFieldDefine.h"
#include "WorkLog/WorkLog.h"

// CStaffSearchDlg �Ի���

IMPLEMENT_DYNAMIC(CDlgStaffSearch, CBCGPDialog)

CDlgStaffSearch::CDlgStaffSearch(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CDlgStaffSearch::IDD, pParent)
{
	m_pDlgComGrid = NULL;
	m_pCurSelectData = NULL;

	m_strDlgTitle = _T("�û�����");
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


// CStaffSearchDlg ��Ϣ�������

BOOL CDlgStaffSearch::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();
	
	InitComGridDlg();//��ʼ�����

   m_pUserInfoList = CDBUserInfoList::Instance();
   m_pUserInfoList->GetListFromDB(theApp.m_pADOConn);
	RefrushComGridDlg();

	return TRUE;
}

void CDlgStaffSearch::InitComGridDlg()//��ʼ�����
{
	S_GridCtrl_TableAttri attri;
	if(!CGridCtrlTableAttributeOp::Instance()->ReadTableAttri(TABLE_STAFFMGN,attri/*,TRUE*/))
	{
		TRACE(_T("CDlgStaffSearch:Failed\n"));
	}	
	//�±��ؼ�����װ������
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

	//���ó�ʼ������
	m_pDlgComGrid->SetGridAttriAndDatas(attri,data);
	m_pDlgComGrid->RefreshGridCtrlInfo();
	
	//���ô�ӡ����title
	m_pDlgComGrid->SetWindowText(m_strDlgTitle);
	//���ñ����ʽxml�ļ���
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
      //���ó�ʼ������		
      m_pDlgComGrid->SetGridDataInfo(data);
      m_pDlgComGrid->RefreshGridCtrlInfo();
   }
}

void CDlgStaffSearch::OnBnClickedBtnUserdel()
{
	if(m_pCurSelectData)
	{	
		if(IDOK == MessageBox(_T("ȷ��ɾ����ǰ�û���Ϣ��"),_T("��ܰ��ʾ��"),MB_ICONQUESTION|MB_OKCANCEL))
		{
         WorkLog::InsertOneWorkLog(enLog_Cate_SQL_Transaction,enLog_Type_Add,_T(""),_T("������������"),m_strDlgTitle);
         theApp.m_pADOConn->BeginTrans();
         WorkLog::InsertOneWorkLog(enLog_Cate_TableName_Userinfo,enLog_Type_Del,m_pCurSelectData->m_strUserID,_T("ɾ���û�"),m_strDlgTitle);
         if (m_pCurSelectData->DelAllDBInfoByUserID(theApp.m_pADOConn))
         {	
            WorkLog::InsertOneWorkLog(enLog_Cate_SQL_Transaction,enLog_Type_Add,_T(""),_T("ɾ���û��ɹ����ύ��������"),m_strDlgTitle);
            theApp.m_pADOConn->CommitTrans();
            CString str;
            str.Format(_T("ɾ��Ա��,���� %s,��� %s") , m_pCurSelectData->m_strUserName , m_pCurSelectData->m_strUserID);

            m_pUserInfoList->DeleteItem(m_pUserInfoList->GetIndexByUserID(m_pCurSelectData->m_strUserID));
            theApp.OnShowDesktopAlert(_T("��ϲ����ɾ���û��ɹ���"),TIP_COLOR_SUC,TIP_TIME_DELAY);

            RefrushComGridDlg();
            m_pCurSelectData = NULL;
         }
         else
         {
            theApp.m_pADOConn->RollbackTrans();
            WorkLog::InsertOneWorkLog(enLog_Cate_SQL_Transaction,enLog_Type_Add,_T(""),_T("ɾ���û�ʧ�ܣ��ع�����"),m_strDlgTitle);
            theApp.OnShowDesktopAlert(_T("��Ǹ��ɾ���û�ʧ�ܣ����ݿ�ִ��ʧ�ܣ���"),TIP_COLOR_WARNING,TIP_TIME_DELAY);
         }
		}
	}
	else
	{
		theApp.OnShowDesktopAlert(_T("��ѡ����Ҫɾ�����˻���"),TIP_COLOR_WARNING,TIP_TIME_DELAY);
	}
}


CDBUserInfoData * CDlgStaffSearch::GetSelectData()
{
	return m_pCurSelectData;
}

void CDlgStaffSearch::OnSize(UINT nType, int cx, int cy)
{
	CBCGPDialog::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
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
