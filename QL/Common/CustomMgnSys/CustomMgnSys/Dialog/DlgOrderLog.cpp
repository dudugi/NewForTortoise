// DlgOrderLog.cpp : 实现文件
//

#include "stdafx.h"
#include "CustomMgnSys.h"
#include "DlgOrderLog.h"

#include "CGridCtrlTableAttributeOp.h"
#include "DlgGridCtrlTableStyle.h"
#include "DBLogInfo.h"
#include "DlgBCGGrid.h"

// CDlgOrderLog 对话框

IMPLEMENT_DYNAMIC(CDlgOrderLog, CBCGPDialog)

CDlgOrderLog::CDlgOrderLog(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CDlgOrderLog::IDD, pParent)
{
	m_pDlgComGrid = NULL;
	m_strOrderCode = _T("");
}

CDlgOrderLog::~CDlgOrderLog()
{
	if (nullptr != m_pDlgComGrid)
	{
		delete m_pDlgComGrid;
		m_pDlgComGrid = nullptr;
	}
}

void CDlgOrderLog::SetOrderCode(CString strOrderCode)
{
		m_strOrderCode = strOrderCode;
}

void CDlgOrderLog::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
}

BOOL CDlgOrderLog::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	InitComGridDlg();

	CRect cRt;
	GetClientRect(cRt);
	if (m_pDlgComGrid)
	{
		m_pDlgComGrid->SetWindowPos(NULL,cRt.left,cRt.top,cRt.right,cRt.bottom,
         SWP_SHOWWINDOW);
	}

	return TRUE;  
}

void CDlgOrderLog::InitComGridDlg()
{
	CGridCtrlTableAttributeOp::Instance()->ReadTableAttri(TABLE_ORDER_LOG,
      m_GridEx_tableAttri);

	if (nullptr != m_pDlgComGrid)
	{
		delete m_pDlgComGrid;
	}
	m_pDlgComGrid = new CDlgBCGGrid;

	//新表格控件，封装的数据
	CDBLogInfoList tmp_list;
   tmp_list.GetLogListData(theApp.m_pADOConn);
   MAP_GridCtrl_AllData data = tmp_list.CreatrGridData();
   /*map<CString,CDBLogInfoData*> mapData = tmp_list.GetOrderLogByOrderCode(
   theApp.m_pADOConn,m_strOrderCode);
   MAP_GridCtrl_AllData data = Package_NewGrid_Data(mapData);
   */
	if (!IsWindow(m_pDlgComGrid->GetSafeHwnd()))
	{
		//设置初始化数据
		m_pDlgComGrid->Create(CDlgBCGGrid::IDD,this);
	}


   //设置打印导出title
   m_pDlgComGrid->SetWindowText(_T("查看此单日志"));
   //设置表格样式xml文件名
   m_pDlgComGrid->SetTableStyleFileName(TABLE_ORDER_LOG);
	//设置初始化数据	
	m_pDlgComGrid->SetGridAttriAndDatas(m_GridEx_tableAttri,data);

	m_pDlgComGrid->RefreshGridCtrlInfo();

}

MAP_GridCtrl_AllData CDlgOrderLog::Package_NewGrid_Data(map<CString,CDBLogInfoData*> mapData)
{
	MAP_GridCtrl_AllData  map_all_data;

	for (auto itr_ = mapData.begin(); itr_ != mapData.end(); ++itr_)
	{
		if (itr_->second == NULL)
			continue;

		MAP_GridCtrl_RowData map_row_data;
		InsertRowData(itr_->second->m_strCate,	DBWorkLog_key_Cate,		map_row_data);
		InsertRowData(itr_->second->m_strCode,	DBWorkLog_key_Code,		map_row_data);
		InsertRowData(itr_->second->m_dDate.Format(_T("%Y-%m-%d %H:%M:%S")),	DBWorkLog_key_Date,		map_row_data);
		InsertRowData(itr_->second->m_strMaker,	DBWorkLog_key_Maker,	map_row_data);
		InsertRowData(itr_->second->m_strType,	DBWorkLog_key_Type,		map_row_data);
		InsertRowData(itr_->second->m_strAction,DBWorkLog_key_Detail,	map_row_data);

		map_all_data.insert(make_pair(_ttoi(itr_->first),map_row_data));
	}
	return map_all_data;
}

void CDlgOrderLog::InsertRowData( CString strValue,CString strFiedID,MAP_GridCtrl_RowData& map_row_data )
{
	S_GridCtrl_FieldData s_data;
	s_data.strValue = strValue;
	s_data.fieldDataType = CB_enum_FieldData_CString;
	s_data.fieldCtrlType = CB_enum_FieldCtrl_Text;
	map_row_data.insert(make_pair(strFiedID,s_data));
}

BEGIN_MESSAGE_MAP(CDlgOrderLog, CBCGPDialog)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CDlgOrderLog 消息处理程序

void CDlgOrderLog::OnSize(UINT nType, int cx, int cy)
{
	CBCGPDialog::OnSize(nType, cx, cy);

	if (IsWindowVisible())
	{
		if (m_pDlgComGrid && IsWindow(m_pDlgComGrid->GetSafeHwnd()))
		{
			CRect cRt;
			GetClientRect(cRt);
			m_pDlgComGrid->SetWindowPos(NULL,cRt.left,cRt.top,cRt.right,cRt.bottom,SWP_SHOWWINDOW);
		}
	}
}


