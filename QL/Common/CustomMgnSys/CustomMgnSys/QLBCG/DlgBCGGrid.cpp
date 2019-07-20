// DlgBCGGrid.cpp : 实现文件
//

#include "stdafx.h"
#include "..\CustomMgnSys.h"
//#include "..\CDataTableDlgDefine.h"
#include "DlgBCGGrid.h"
#include "QLBCGGridCtrl.h"
#include <map>
#include "tinyxml/tinyxml.h"
#include "rnstring.h"
#include "CGridCtrlTableAttributeOp.h"
#include "customcells.h"
#include "DlgGridCtrlTableStyle.h"
#include <algorithm>
#include "QLBCGMESSAGE.h"
//#include "DBTableStyleGlobalSetInfo.h"
//#include "DBPersonInfo_V.h"


enum USER_MSG
{
	UID_TIMER_REFRESH_HEADER_SORT = (WM_USER + 1),
	UID_TIMER_REFRESH_FILTER_CHANGED,
	UID_GRID_BTN1,
	UID_GRID_BTN2,
	UID_TIMER_REFRESH_SUMARY_ROW_INFO,	//刷新统计行的信息		by WangZY 2017/11/24
};

//导出EXCEL消息		by WangZY 2018/08/14
UINT UM_EXPORT_DATA_TO_EXCEL_MSG = ::RegisterWindowMessage(_T("UM_EXPORT_DATA_TO_EXCEL_MSG"));

const int CN_REFRESH_FILTER_BAR_TIME = 400; 
const int CN_REFRESH_SUMARY_ROW_INFO_TIME = 500; 


// CDlgBCGGrid 对话框

IMPLEMENT_DYNAMIC(CDlgBCGGrid, CBCGPDialog)

CDlgBCGGrid::CDlgBCGGrid(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CDlgBCGGrid::IDD, pParent)
{
	m_pBCGGrid = NULL;
	m_mapColID.clear();	
	m_mapColName.clear();
	m_mapColName.clear();
	m_mapColWithFieldId.clear();

	
//	m_dbRecordSetPtr = nullptr;		//网格数据记录集指针
	m_strSortInfo = _T("");			//排序的信息

	m_bUserPaginationMode = FALSE;	//使用自定义分页模式 by WangZY 2017/11/08
	m_bShowPageInfo = FALSE;		//是否显示分页控件 by WangZY 2017/10/30
   m_emPMPaginationModeFlag = emPM_Null;     //分页模式标志
	
	m_bShowLeftHeaderColumn = TRUE;	//是否显示左侧序号列 by WangZY 2017/11/21
	m_bShowLineNumber = TRUE;		//是否左侧序号列显示行号 by WangZY 2017/11/21
	m_nLeftHeaderColumnWidth = 45;	//左侧序号列的宽度 by WangZY 2017/11/21

	m_nRClickHeadCol = -1;			//右键点击的列标题
	m_bEnableColHeadMenu = TRUE;	//默认启用列点击菜单

	m_tableStyleFileName = _T("");//表格样式的xml文件名 yangjr 2017-12-13

	m_bKeyShiftDown	= FALSE;
	m_bKeyCtrlDown	= FALSE;	
	m_bUseNewAttri = FALSE;						//新的表属性方式	by WangZY 2018/01/31

	m_nCheckRowCount = 0;
	m_lastShowCheckRowCount = 0;
}

CDlgBCGGrid::~CDlgBCGGrid()
{
	if (m_pBCGGrid != NULL)
	{
		delete m_pBCGGrid;
		m_pBCGGrid = NULL;
	}
}

void CDlgBCGGrid::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_BTN_PAGEDOWN, m_btnPagedown);
	DDX_Control(pDX, IDC_BTN_PAGEUP, m_btnPageUp);
	DDX_Control(pDX, IDC_BTN_PAGEDOWN, m_btnPageDown);
	DDX_Control(pDX, IDC_TEXT_PAGE, m_textPageInfo);

}

BEGIN_MESSAGE_MAP(CDlgBCGGrid, CBCGPDialog)
	ON_WM_SIZE()
	ON_REGISTERED_MESSAGE(BCGM_GRID_ITEM_CHANGED, &CDlgBCGGrid::OnGrid_ItemChanged)
	ON_MESSAGE(BCGM_GRID_ITEM_RCLICK, &CDlgBCGGrid::OnGrid_ItemRClick)
	ON_MESSAGE(BCGM_GRID_ITEM_LCLICK, &CDlgBCGGrid::OnGrid_ItemLClick)
	ON_MESSAGE(BCGM_GRID_ITEM_LDBCLICK, &CDlgBCGGrid::OnGrid_ItemDBLClick)
	ON_MESSAGE(BCGM_GRID_ITEM_HEADRCLICK, &CDlgBCGGrid::OnGrid_ItemHeadRClick)
	// wangzl 2017-11-21
	ON_REGISTERED_MESSAGE(BCGM_GRID_ITEM_BEGININPLACEEDIT, &CDlgBCGGrid::OnGrid_BeginPlaceEdit)
	ON_REGISTERED_MESSAGE(BCGM_GRID_ITEM_ENDINPLACEEDIT, &CDlgBCGGrid::OnGrid_EndPlaceEdit)
	// wangzl 2017-11-21 end
	ON_BN_CLICKED(IDC_BTN_PAGEUP, &CDlgBCGGrid::OnBnClickedBtnPageup)
	ON_BN_CLICKED(IDC_BTN_PAGEDOWN, &CDlgBCGGrid::OnBnClickedBtnPagedown)
	ON_WM_TIMER()
	ON_REGISTERED_MESSAGE(BCGM_GRID_HEADER_SORT, OnGridHeaderSort)
	ON_REGISTERED_MESSAGE(BCGM_GRID_FILTER_BAR_CHANGED, OnGridFilterBarChanged)
   ON_REGISTERED_MESSAGE(BCGM_GRID_FILTER_BAR_ENTER_MSG, OnGridFilterBarEnterMsg)
   ON_REGISTERED_MESSAGE(BCGM_GRID_CLICK_FILTER_BAR_CLEAR_BTN, OnGridFilterBarClearBtnMsg)
	ON_REGISTERED_MESSAGE(BCGM_GRID_ROW_CHECKBOX_CLICK,OnGrid_RowCheckBoxClick)
	ON_REGISTERED_MESSAGE(BCGM_GRID_HEADERCHECKBOX_CLICK,OnGrid_HeaderCheckBoxClick)
	// wangzl 2017-12-11
	ON_COMMAND_RANGE(IDM_DLGGRID_STYLE, IDM_DLGGRID_STYLE_SAVETOSERVER, &CDlgBCGGrid::OnGridHeadMenu)
	//ON_COMMAND_RANGE(IDM_TurnOverSelect,IDM_TurnOverSelect,&CDlgBCGGrid::OnGridHeadMenu)
 //  ON_COMMAND_RANGE(IDM_DLGGRID_GRID_UPDATESERVERSTYLE,IDM_DLGGRID_STYLE_SAVETOSERVER,&CDlgBCGGrid::OnGridHeadMenu)
	// wangzl 2017-12-11 end
   ON_WM_DESTROY()
	//ON_COMMAND(ID_APPLY_FILTER, OnApplyFilter)
	ON_MESSAGE(BCGM_GRID_TITLE_FILTER_CHANGED,OnGridTitleFilterChanged)

END_MESSAGE_MAP()

// #if defined _M_IX86  
// #pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")  
// #elif defined _M_IA64  
// #pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")  
// #elif defined _M_X64  
// #pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")  
// #else  
// #pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")  
// #endif  

BOOL CDlgBCGGrid::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

   InitBCGGridCtrl();
	//m_progressCtrl.Create(WS_CHILD|WS_VISIBLE|PBS_MARQUEE|PBS_SMOOTH,CRect(100,0,250,30),this,11);
	
	//m_progressCtrl.SetBkColor(RGB(255,0,0));

	//m_progressCtrl.SetMarquee(TRUE, 30);

	if (m_bShowPageInfo)
	{
		m_btnPageDown.ShowWindow(SW_SHOW);
		m_btnPageUp.ShowWindow(SW_SHOW);
		m_textPageInfo.ShowWindow(SW_SHOW);
	}
	else
	{
		m_btnPageDown.ShowWindow(SW_HIDE);
		m_btnPageUp.ShowWindow(SW_HIDE);
		m_textPageInfo.ShowWindow(SW_HIDE);
	}

	return TRUE; 
}


void CDlgBCGGrid::SetScale(double dblScale/*=1.0*/)
{
   if (nullptr == m_pBCGGrid
      ||!IsWindow(m_pBCGGrid->GetSafeHwnd()))
   {
      return;
   }

   m_pBCGGrid->SetScalingRange(dblScale,dblScale);
   m_pBCGGrid->SetScale(dblScale);
   
}

void CDlgBCGGrid::InitBCGGridCtrl()
{
	if (m_pBCGGrid != NULL)
	{
		delete m_pBCGGrid;
		m_pBCGGrid = NULL;
	}

	m_pBCGGrid = new CQLBCGGridCtrl;
	m_pBCGGrid->Create(WS_CHILD|WS_VISIBLE|WS_BORDER,CRect(0,0,0,0),this,6666);
	m_pBCGGrid->SetOwner(this);
	m_pBCGGrid->SetParent(this);
	
	CBCGPGridColors colors;
	colors.m_EvenColors.m_clrBackground = RGB(224,255,255);
	colors.m_SelColors.m_clrBackground = RGB(255,232,166);

	m_pBCGGrid->SetColorTheme(colors);
	m_pBCGGrid->EnableAlternateRows(TRUE);
	
	m_pBCGGrid->EnableRowHeader (m_bShowLeftHeaderColumn);
	if (m_bShowLeftHeaderColumn)
	{
		m_pBCGGrid->SetRowHeaderWidth(m_nLeftHeaderColumnWidth);
		m_pBCGGrid->EnableLineNumbers(m_bShowLineNumber);		
	}
	else
	{
		m_pBCGGrid->SetRowHeaderWidth(0);
	}
	
	m_pBCGGrid->SetEditFirstClick(FALSE);
	m_pBCGGrid->SetClearInplaceEditOnEnter (FALSE);		//按Enter就地编辑单元格内容，FALSE 不会清空数据，TRUE 清空单元格内容
	
	m_pBCGGrid->SetUserPaginationMode(m_bUserPaginationMode?true:false,m_emPMPaginationModeFlag);	//设置用户自定义分页模式		by WangZY 2017/11/02
	
	//m_pBCGGrid->EnableInvertSelOnCtrl ();
	//m_pBCGGrid->FreezeColumns(2);
	//m_pBCGGrid->FreezeRightColumns(2);
	
	if (m_tableAttri.isShowSumBar)
	{
		m_pBCGGrid->SetGridFooterHeight(m_tableAttri.nDataRowHeight);
		m_pBCGGrid->GetColumnsInfo().SetEnableShowFooterRow(TRUE);
      m_pBCGGrid->GetColumnsInfo().SetFooterHeaderText(_T("合计"));
	}
	else
	{
		m_pBCGGrid->SetGridFooterHeight(0);
		m_pBCGGrid->GetColumnsInfo().SetEnableShowFooterRow(FALSE);
	}
	

	CRect rt;
	GetClientRect(rt);
	m_pBCGGrid->SetWindowPos(NULL,rt.left,rt.top,rt.right,rt.bottom,SWP_SHOWWINDOW);
}

BOOL CDlgBCGGrid::SaveAtrriToXml(CString strXmlName)
{
	BOOL bRet = FALSE;

	if (!IsWindow(this->GetSafeHwnd()))
	{
		ASSERT(FALSE);
		return bRet;
	}

	if (strXmlName.IsEmpty())
	{
		ASSERT(FALSE);
		return bRet;
	}

	S_GridCtrl_TableAttri tableAttri;
	if (GetGridAttriInfo(tableAttri))
	{
      bRet = CGridCtrlTableAttributeOp::Instance()->WriteTableAttri(strXmlName,tableAttri);
	}

	return bRet;
}

//清空当前的排序状态		by WangZY 2017/12/12
BOOL CDlgBCGGrid::ClearSortState()
{
	if (nullptr == m_pBCGGrid
		||!m_tableAttri.isAllowSort)
	{
		return FALSE;
	}
	
	m_pBCGGrid->RemoveAllSortColumn();
	
	return TRUE;
}

// CDlgBCGGrid 消息处理程序

void CDlgBCGGrid::OnSize(UINT nType, int cx, int cy)
{
	CBCGPDialog::OnSize(nType, cx, cy);
	CRect rt;
	GetClientRect(rt);
	if (m_pBCGGrid && IsWindow(m_pBCGGrid->GetSafeHwnd()))
	{
		if (m_bShowPageInfo)
		{
			m_pBCGGrid->SetWindowPos(NULL,rt.left,rt.top,rt.right,rt.bottom -40,SWP_SHOWWINDOW);
		}
		else
		{
			m_pBCGGrid->SetWindowPos(NULL,rt.left,rt.top,rt.right,rt.bottom,SWP_SHOWWINDOW);
		
		}

      //表格刷新代码处理调整尝试 2018-1-19 wangzl
      //m_pBCGGrid->AdjustLayout();
	}
		
	if (m_bShowPageInfo)
	{
		if (IsWindow(m_btnPageUp.GetSafeHwnd()))
		{
			m_btnPageUp.SetWindowPos(NULL,(rt.left + rt.right)/2- 150,rt.bottom - 35,0,0,SWP_NOSIZE);
		}
		if (IsWindow(m_btnPageDown.GetSafeHwnd()))
		{
			m_btnPageDown.SetWindowPos(NULL,(rt.left + rt.right)/2+ 50,rt.bottom - 35,0,0,SWP_NOSIZE);
		}
		if (IsWindow(m_textPageInfo.GetSafeHwnd()))
		{
			m_textPageInfo.SetWindowPos(NULL,(rt.left + rt.right)/2- 40,rt.bottom - 31,0,0,SWP_NOSIZE);
		}
	}
}
// wangzl 2017-11-21
LRESULT CDlgBCGGrid::OnGrid_BeginPlaceEdit(WPARAM wParam,LPARAM lParam)
{
	this->GetOwner()->SendMessage (BCGM_GRID_ITEM_BEGINEDIT, (WPARAM)this, lParam);
	return 1;
}
// wangzl 2017-11-21
LRESULT CDlgBCGGrid::OnGrid_EndPlaceEdit(WPARAM wParam,LPARAM lParam)
{
	this->GetOwner()->SendMessage (BCGM_GRID_ITEM_ENDEDIT, (WPARAM)this, lParam);
	return 1;
}

LRESULT CDlgBCGGrid::OnGrid_ItemChanged(WPARAM wParam,LPARAM lParam)
{
	BCGPGRID_ITEM_INFO* pii = (BCGPGRID_ITEM_INFO*)lParam;
	ASSERT(pii != NULL);
	ASSERT_VALID (pii->pItem);
	if (pii->nCol >= 0 && pii->nRow >= 0)
	{
		CString strColName = _T("");
		auto itr_col_id = m_mapColWithFieldId.find(pii->nCol);
		if (itr_col_id != m_mapColWithFieldId.end())
		{
			strColName = itr_col_id->second;
		}

		CBCGPGridRow* pRow = m_pBCGGrid->GetRow(pii->nRow);
		if (pRow && !strColName.IsEmpty())
		{
			_bstr_t strValue = pRow->GetItem(pii->nCol)->GetValue();		//修改后的值

			MAP_GridCtrl_RowData& dataRow = (*((MAP_GridCtrl_RowData*)pRow->GetData()));
			auto itr_col_data = dataRow.find(strColName); 
			if (itr_col_data != dataRow.end())
			{
				CString strNew = strValue;
				if (itr_col_data->second.fieldCtrlType == CB_enum_FieldCtrl_Checkbox
					||itr_col_data->second.fieldCtrlType == CB_enum_FieldCtrl_Radio)	//checkbox
				{
					if (0 != _ttoi(strNew))		//checked
					{
						strNew = _T("1");
					}
					else //unchecked
					{
						strNew = _T("0");
					}
				}
				itr_col_data->second.strValue = strNew;
			}
		}
	}
	this->GetOwner()->SendMessage (BCGM_GRID_ITEM_BECHANGED, (WPARAM)this, lParam);

	if (m_bUserPaginationMode )
	{
      if (m_emPMPaginationModeFlag == emPM_DbSvr && !m_pBCGGrid->IsTitleFilterEmpty())
      {
         KillTimer(UID_TIMER_REFRESH_SUMARY_ROW_INFO);
         SetTimer(UID_TIMER_REFRESH_SUMARY_ROW_INFO, CN_REFRESH_SUMARY_ROW_INFO_TIME, NULL);
      }
	}
	else
	{
		KillTimer(UID_TIMER_REFRESH_SUMARY_ROW_INFO);
		SetTimer(UID_TIMER_REFRESH_SUMARY_ROW_INFO, CN_REFRESH_SUMARY_ROW_INFO_TIME, NULL);
	}

	return 1;
}

//响应头排序消息 BCGM_GRID_HEADER_SORT		by WangZY 2017/11/02
LRESULT CDlgBCGGrid::OnGridHeaderSort(WPARAM wParam, LPARAM lParam)
{
	BCGP_SORT_ITEM_INFO infoSort = *(BCGP_SORT_ITEM_INFO*)lParam;
	if (m_bUserPaginationMode
      &&emPM_DbSvr == m_emPMPaginationModeFlag)
	{
      if (infoSort.nCol>=0)
      {
         CPageInfo info = m_infoPage;
       
         GetOwner()->SendMessage(UM_PAGINATION_REFRESH_DATA_MSG,(WPARAM)&info,emRDM_CurPage);
      }
      
      return 1;
	}

	auto it = m_mapColWithFieldId.find(infoSort.nCol);
	if (it != m_mapColWithFieldId.end())
	{
		KillTimer(UID_TIMER_REFRESH_HEADER_SORT);
		CString strFieldId = it->second;
		
		if (infoSort.bSortAscending)
		{
			m_strSortInfo.Format(_T("%s asc"),strFieldId);
		}
		else
		{
			m_strSortInfo.Format(_T("%s desc"),strFieldId);
		}
		
		SetTimer(UID_TIMER_REFRESH_HEADER_SORT, 10, NULL);

		return 1;
	}

	return 0;
}

//响应筛选行改变的消息 BCGM_GRID_FILTER_BAR_CHANGED		by WangZY 2017/11/02
LRESULT CDlgBCGGrid::OnGridFilterBarChanged(WPARAM wParam, LPARAM lParam)
{
	BCGP_FILTER_COLUMN_INFO infoFilter(*(BCGP_FILTER_COLUMN_INFO*)lParam);
   if (m_bUserPaginationMode
      &&emPM_DbSvr == m_emPMPaginationModeFlag)
   {
      CPageInfo info = m_infoPage;
      //info.m_nCurPage += in1;
      info.m_nCurPage %= info.m_nTotalPage;
      //GetOwner()->SendMessage(UM_PAGINATION_REFRESH_DATA_MSG,(WPARAM)&info,emRDM_CurPage);

      return 0;
   }

	if (m_bUserPaginationMode)
	{
		auto it = m_mapColWithFieldId.find(infoFilter.nCol);
		if (it != m_mapColWithFieldId.end())
		{
			KillTimer(UID_TIMER_REFRESH_FILTER_CHANGED);
			CString strFieldId = it->second;

			CString strFieldInfo;
			if (infoFilter.bAll)
			{
				strFieldInfo = _T("");
			}
			else if (!infoFilter.strFilter.IsEmpty())
			{
				strFieldInfo.Format(_T("%s like '*%s*'"),strFieldId, infoFilter.strFilter);
			}
			else
			{
				//需要在这里处理，标题头过滤的处理		by WangZY 2017/11/02
			}

			auto itFilter = m_mapFilterInfo.find(strFieldId);
			if (itFilter != m_mapFilterInfo.end())
			{
				if (strFieldInfo.IsEmpty())
				{
					m_mapFilterInfo.erase(itFilter);	//筛选信息
				}
				else
				{
					itFilter->second = strFieldInfo;
				}
			}
			else
			{
				if (!strFieldInfo.IsEmpty())
				{
					m_mapFilterInfo.insert(map<CString/*FieldId*/,CString/*FilterInfo*/>::value_type(
						strFieldId,strFieldInfo));
				}
			}
			SetTimer(UID_TIMER_REFRESH_FILTER_CHANGED, CN_REFRESH_FILTER_BAR_TIME, NULL);

			return 1;
		}
	}
	else
	{
		KillTimer(UID_TIMER_REFRESH_SUMARY_ROW_INFO);
		SetTimer(UID_TIMER_REFRESH_SUMARY_ROW_INFO, CN_REFRESH_SUMARY_ROW_INFO_TIME, NULL);
	}
	

	return 0;
}

//		by WangZY 2018/06/07
LRESULT CDlgBCGGrid::OnGridFilterBarEnterMsg(WPARAM wParam, LPARAM lParam)
{
   BCGP_FILTER_COLUMN_INFO infoFilter(*(BCGP_FILTER_COLUMN_INFO*)lParam);
   if (m_bUserPaginationMode
      &&emPM_DbSvr == m_emPMPaginationModeFlag)
   {
      CPageInfo info = m_infoPage;

      //info.m_nCurPage %= info.m_nTotalPage;
      //info.m_nCurPage += 1;

      GetOwner()->SendMessage(UM_PAGINATION_REFRESH_DATA_MSG,(WPARAM)&info,emRDM_Restart);

      return 0;
   }

   return 0;
}

//		by WangZY 2018/06/07
LRESULT CDlgBCGGrid::OnGridFilterBarClearBtnMsg(WPARAM wParam, LPARAM lParam)
{
   //BCGP_FILTER_COLUMN_INFO infoFilter(*(BCGP_FILTER_COLUMN_INFO*)lParam);
   if (m_bUserPaginationMode
      &&emPM_DbSvr == m_emPMPaginationModeFlag)
   {
      CPageInfo info = m_infoPage;

      //info.m_nCurPage %= info.m_nTotalPage;
      //info.m_nCurPage += 1;

      GetOwner()->SendMessage(UM_PAGINATION_REFRESH_DATA_MSG,(WPARAM)&info,emRDM_Restart);

      return 0;
   }

   return 0;
}

//		by WangZY 2018/03/12
LRESULT CDlgBCGGrid::OnGridTitleFilterChanged(WPARAM wParam, LPARAM lParam)
{   
	if (m_bUserPaginationMode && m_emPMPaginationModeFlag !=emPM_DbSvr)
	{
		KillTimer(UID_TIMER_REFRESH_FILTER_CHANGED);
		SetTimer(UID_TIMER_REFRESH_FILTER_CHANGED, CN_REFRESH_FILTER_BAR_TIME, NULL);
	}
   else
   {
      //if (m_bUserPaginationMode && m_emPMPaginationModeFlag ==emPM_DbSvr)//数据库分页模式也重新计算求和
      //{
      //   return 0;
      //}
      KillTimer(UID_TIMER_REFRESH_SUMARY_ROW_INFO);
      SetTimer(UID_TIMER_REFRESH_SUMARY_ROW_INFO, CN_REFRESH_SUMARY_ROW_INFO_TIME, NULL);
   }

	return 0;
}

LRESULT CDlgBCGGrid::OnGrid_ItemRClick(WPARAM wParam,LPARAM lParam)
{
	BCGPGRID_ITEM_INFO ii = *(BCGPGRID_ITEM_INFO*)lParam;
	if(nullptr != ii.pItem)
	{
		if (m_tableAttri.isWholeRowSelect)
		{
			SetSelWholeRow(ii.nRow,ii.nCol,FALSE);
		}
		this->GetOwner()->SendMessage (BCGM_GRID_ITEM_RCLICK, (WPARAM)this, lParam);
	}
	else
	{
		//BCGPGRID_ITEM_INFO ii = *(BCGPGRID_ITEM_INFO*)lParam;
		//if (ii.nRow < 0 || ii.nCol < 0)
		//	return 0;

		//CMenu Menu; 
		//VERIFY(Menu.LoadMenu(IDR_MENU_TABMENU));//加载菜单资源
		//CMenu* pPopup = Menu.GetSubMenu(0); 
		//ASSERT(pPopup != NULL); 
		//int nIndex = 0,nCount = pPopup->GetMenuItemCount();
		//for (nIndex = 0;nIndex < nCount;nIndex++)
		//{
		//	pPopup->DeleteMenu(0,MF_BYPOSITION);
		//}
		//pPopup->InsertMenu(0,MF_BYPOSITION,IDM_GRIDMAIN_COPYORDERNO,_T("复制订单号"));
		//CPoint point;
		//GetCursorPos(&point);
		//theApp.OnShowCMFCPopupMenu(this,pPopup,point);
	}
	/*右键列标题时不发送消息
	this->GetOwner()->SendMessage (BCGM_GRID_ITEM_RCLICK, (WPARAM)this, lParam);*/
	return 0;
}

//响应每行的左侧的CheckBox的点击消息		by WangZY 2017/11/22
LRESULT CDlgBCGGrid::OnGrid_RowCheckBoxClick(WPARAM wParam,LPARAM lParam)
{
	LRESULT rt = GetOwner()->SendMessage (BCGM_GRID_ROW_CHECKBOX_CLICK, 
		(WPARAM)this, lParam);

	CBCGPGridRow* pRow = (CBCGPGridRow*)lParam;
	if (pRow)
	{
		if (!pRow->GetCheck())
		{
			m_pBCGGrid->GetColumnsInfo().SetCheckBoxState(FALSE);
			--m_nCheckRowCount;
		}	
		else
		{
			++m_nCheckRowCount;
		}
	}
	SetFootValue_CheckNum(m_nCheckRowCount);
	return rt;
}

//响应标题头的左侧的CheckBox的点击消息			by WangZY 2017/11/22
LRESULT CDlgBCGGrid::OnGrid_HeaderCheckBoxClick(WPARAM wParam,LPARAM lParam)
{
	LRESULT rt = GetOwner()->SendMessage (BCGM_GRID_HEADERCHECKBOX_CLICK, 
	(WPARAM)this, lParam);

	if (m_pBCGGrid->GetColumnsInfo().GetCheckBoxState() == 0)
	{
		m_nCheckRowCount = m_pBCGGrid->GetTotalRowCount(TRUE);
	}
	else
	{
		m_nCheckRowCount = 0;
	}
	SetFootValue_CheckNum(m_nCheckRowCount);
	return rt;
}

LRESULT CDlgBCGGrid::OnGrid_ItemLClick(WPARAM wParam,LPARAM lParam)
{
	BCGPGRID_ITEM_INFO ii = *(BCGPGRID_ITEM_INFO*)lParam;
	if (m_tableAttri.isWholeRowSelect)
	{
		SetSelWholeRow(ii.nRow,ii.nCol,TRUE);
		if(m_tableAttri.IsMultiRowSelectNoLoseFocus)
		{
			if(ii.nRow < 0 && ii.nCol < 0)
			{
            //点击check栏时....
            if (m_bKeyCtrlDown || m_bKeyShiftDown)
            {
               SetMulRowSelectCheck(TRUE);
               GetCheckRowNum();
               SetFootValue_CheckNum(m_nCheckRowCount);
            }
			}
			else
			{
				if (m_bKeyCtrlDown || m_bKeyShiftDown)
				{
					SetMulRowSelectCheck(TRUE);
					GetCheckRowNum();
				}
				else
				{
					m_pBCGGrid->GetColumnsInfo().SetCheckBoxState(FALSE);
					m_pBCGGrid->CheckHeaderBoxClick(FALSE);
					m_pBCGGrid->GetRow(ii.nRow)->SetCheck(TRUE);
					m_pBCGGrid->Invalidate(TRUE);
					m_nCheckRowCount = 1;
				}
				SetFootValue_CheckNum(m_nCheckRowCount);
				//修复：错误 #6439	任务指派；勾一个下拉列表还是灰的		by WangZY 2018/02/05
				LRESULT rt = GetOwner()->SendMessage (BCGM_GRID_ROW_CHECKBOX_CLICK, 
					(WPARAM)this, lParam);
			}
		}
	}
	
#ifdef _DEBUG	//测试
//	CString strValue = _T("");
//	GetValueByGridRowAndCol(strValue,ii.nRow,ii.nCol);
#endif

	this->GetOwner()->SendMessage (BCGM_GRID_ITEM_LCLICK, (WPARAM)this, lParam);
	return 0;
}

LRESULT CDlgBCGGrid::OnGrid_ItemDBLClick(WPARAM wParam,LPARAM lParam)
{
	//BCGPGRID_ITEM_INFO ii = *(BCGPGRID_ITEM_INFO*)lParam;
	this->GetOwner()->SendMessage (BCGM_GRID_ITEM_LDBCLICK, (WPARAM)this, lParam);
	return 0;
}

//设置显示左侧序号列		by WangZY 2017/11/21
void CDlgBCGGrid::SetShowLeftHeaderColumn(BOOL bShowLeftHeaderColumn /*= TRUE*/)
{
	m_bShowLeftHeaderColumn = bShowLeftHeaderColumn;
}

//设置左侧序号列显示行号			by WangZY 2017/11/21
void CDlgBCGGrid::SetShowLeftLineNumber(BOOL bShowLineNumber /*= TRUE*/)
{
	m_bShowLineNumber = bShowLineNumber;
}

//设置显示左侧序号列的宽度		by WangZY 2017/11/21
void CDlgBCGGrid::SetShowLeftHeaderColumnWidth(int nWidth/*=35*/)
{
	m_nLeftHeaderColumnWidth = nWidth;
}

//		by WangZY 2018/06/06
void CDlgBCGGrid::SetAndRefreshPageInfo(CPageInfo &info)
{
   m_infoPage = info;
   RefreshPageInfo(info.m_nTotalPage,info.m_nCurPage,info.m_nPerPageCount);

}

//设置使用用户自定义分页模式标志		by WangZY 2017/11/08
void CDlgBCGGrid::SetUserPaginationMode(BOOL bUserPaginationMode /*= TRUE*/,
   EM_PAGINATION_MODE emPMPaginationMode/* = emPM_Local*/)
{
	m_bUserPaginationMode = bUserPaginationMode;

	m_bShowPageInfo = m_bUserPaginationMode;
   m_emPMPaginationModeFlag = emPMPaginationMode;
}

//获取使用用户自定义分页模式标志		by WangZY 2017/11/08
BOOL CDlgBCGGrid::GetUserPaginationMode() const
{
	return m_bUserPaginationMode;
}

//通过数据集设置网格数据			by WangZY 2017/10/25
//void CDlgBCGGrid::SetGridDataInfoByRecordSetPtr(_RecordsetPtr &dbRecordSetPtr)
//{
//	m_dbRecordSetPtr = dbRecordSetPtr;
//	if (nullptr == dbRecordSetPtr)
//	{
//		return;
//	}
//
//	RefreshDataInfoToGrid(0,TRUE);
//}

// CDlgBCGGrid 公共接口

void CDlgBCGGrid::PrintTime_Test(CString strTitle/* = _T("")*/)
{
#ifdef _DEBUG
	COleDateTime ole_time = COleDateTime::GetTickCount();
	CString strTime = ole_time.Format(_T("%y-%m-%d %H:%M:%S"));
	TRACE(strTitle + _T(":") + strTime);
	TRACE(_T("\n"));
#endif
}

void CDlgBCGGrid::SetGridEnableEdit(BOOL bEnableEdit /*= TRUE*/)
{
	if (nullptr != m_pBCGGrid)
	{
		m_pBCGGrid->EnableWindow(bEnableEdit);
		m_tableAttri.isEnableEdit = bEnableEdit?true:false;
		m_pBCGGrid->SetReadOnly(!m_tableAttri.isEnableEdit);						//表是否可编辑	
	}
}

BOOL CDlgBCGGrid::SetGridAttriAndDatas(__in const S_GridCtrl_TableAttri &tableAttri,
	__in const MAP_GridCtrl_AllData &data,int iShowColAlign/* = HDF_CENTER*/)
{
	//m_tableData = data;
	SetGridAttriInfo(tableAttri,iShowColAlign);
	SetGridDataInfo(data);

	return TRUE;
}

BOOL CDlgBCGGrid::SetGridDataInfo(__in const MAP_GridCtrl_AllData &data)
{
	m_tableData = data;
   if (m_pBCGGrid)
   {//bcg网格重新设置数据的时候，清空标题过滤条件 yangjr2018/7/4
      m_pBCGGrid->ClearTitleFilter();
   }
   
	return TRUE;
}

BOOL CDlgBCGGrid::SetGridAttriInfo(__in const S_GridCtrl_TableAttri &tableAttri,
	int iShowColAlign/* = HDF_CENTER*/)
{
	m_tableAttri = tableAttri;

	if (NULL == m_pBCGGrid 
		|| !IsWindow(m_pBCGGrid->GetSafeHwnd()))
	{
		return FALSE;
	}

	m_pBCGGrid->SetRedraw(FALSE);

	int iRowCounts = m_pBCGGrid->GetRowCount();
	for (int i=iRowCounts-1; i>=0; --i)
	{
		m_pBCGGrid->RemoveRow(i);		//清空行
	}

	// add by wuzhihua 2018/1/13  获取筛选信息
	std::map<CString , CString > mapFiledFilter;//字段 对应 筛选信息 map
	GetFilterFieldInfo(mapFiledFilter);
	

	m_pBCGGrid->GetColumnsInfo().DeleteAllColumns();	//清空列

	int nColID_Min = 100;

	m_mapColWithFieldId.clear();
	m_mapColID.clear();
	m_mapColName.clear();
	m_mapColEdit.clear();
	m_mapCol_Name_ID.clear();
	//初始化表格数据时，清空表格原有数据，重新插入列标题。。。
	m_pBCGGrid->RemoveAll();

	int iCol = 0;
	for (auto itr_ = tableAttri.mapFeildAtrri.begin();
		itr_ != tableAttri.mapFeildAtrri.end(); ++itr_, ++iCol)
	{
		if (itr_->second.iColIndex < nColID_Min)
			nColID_Min = itr_->second.iColIndex;

		m_pBCGGrid->InsertColumn(iCol,_T(""),10);		//先插入空的数据
		m_pBCGGrid->SetHeaderAlign(iCol,iShowColAlign);
		m_pBCGGrid->SetColumnAlign(iCol, iShowColAlign);	


		//分页模式下的暂不使用标题头过滤器功能		by WangZY 2018/03/14
		if (m_bUserPaginationMode && m_emPMPaginationModeFlag == emPM_Local)
		{
			continue;
		}

		//{
		//	//设置列标题过滤		by WangZY 2018/02/28
		//	m_pBCGGrid->GetColumnsInfo().SetColumnEnableTitleFilter(iCol,
		//		tableAttri.isShowTitleFilter);
		//}

		//auto itFilter = std::find(m_vecFilterId.begin(),m_vecFilterId.end(),itr_->first);
		//if (itFilter != m_vecFilterId.end())
		bool bFilter = (itr_->second.isEnableFilter&&tableAttri.isShowTitleFilter);
		{
			//设置列标题过滤		by WangZY 2018/02/28
			m_pBCGGrid->GetColumnsInfo().SetColumnEnableTitleFilter(iCol,bFilter);

			auto itLst = m_mapFilterListInfo.find(itr_->first);
			if (itLst != m_mapFilterListInfo.end())
			{
				CStringList lst;
				for (auto itVec=itLst->second.begin(); 
					itVec!=itLst->second.end();++itVec)
				{
					lst.AddTail(*itVec);
				}
				m_pBCGGrid->m_infoFilter.AddColumnFilterList(iCol,lst);
			}
		}
	}

	const int nColCounts  = m_pBCGGrid->GetColumnCount();

	DWORD dHeaderFlag = m_pBCGGrid->GetHeaderFlags();

	m_pBCGGrid->EnableHeader(TRUE,tableAttri.isAllowSort ? dHeaderFlag|BCGP_GRID_HEADER_SORT : dHeaderFlag & 0x03);	//是否允许排序
	m_pBCGGrid->EnableFilterBar(tableAttri.isShowSortBar,_T("<all>"));		//是否显示筛选栏
	m_pBCGGrid->SetWholeRowSel(tableAttri.isWholeRowSelect);				//整行选择
	m_pBCGGrid->EnableCheckBoxes(tableAttri.isMultiRowSelect);				//多行选择 
	m_pBCGGrid->EnableDragHeaderItems(tableAttri.isEnableDragCol);			//列位置能否拖动
	m_pBCGGrid->SetReadOnly(!tableAttri.isEnableEdit);						//表是否可编辑	
	m_pBCGGrid->setUserRowHeight(tableAttri.nDataRowHeight,TRUE);					//表格行高

	//修复：#5911：标题过滤icon调整		by WangZY 2017/12/11
	m_pBCGGrid->EnableShowFilterBarSearchImg(FALSE);

	//设置字体
	HFONT hft;
	hft = CreateFont(tableAttri.iDataRowFont+2,0,0,0,FW_NORMAL,false,false,false,GB2312_CHARSET,OUT_OUTLINE_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,FF_MODERN,_T("宋体"));
	//m_pBCGGrid->SendMessage(WM_SETFONT,(WPARAM)hft);
   CFont oCreateFont;
   oCreateFont.FromHandle(hft);
   m_pBCGGrid->SetFont(&oCreateFont);
   DeleteObject(hft);

	m_pBCGGrid->EnableFilter_My(tableAttri.isShowTitleFilter);				//是否显示列标题筛选器

	tableAttri.IsMultiRowSelectNoLoseFocus;		//多行选择不失焦点
	tableAttri.isPrintHengXiang;					//是否横向打印
	tableAttri.isShowSumBar;					//是否显示合计栏
	if (m_tableAttri.isShowSumBar)
	{
		m_pBCGGrid->SetGridFooterHeight(m_tableAttri.nDataRowHeight);
		m_pBCGGrid->GetColumnsInfo().SetEnableShowFooterRow(TRUE);
      m_pBCGGrid->GetColumnsInfo().SetFooterHeaderText(_T("合计"));
	}
	else
	{
		m_pBCGGrid->SetGridFooterHeight(0);
		m_pBCGGrid->GetColumnsInfo().SetEnableShowFooterRow(FALSE);
	}

	int nColMinWidth = m_pBCGGrid->GetBaseHeight();		//最小列宽

	int nFrozenCounts_Left = 0;			//左侧冰冻列数量	
	int nFrozenCounts_Right = 0;		//右侧冰冻列数量
	m_vecFrozenIndex.clear();

	//按数据结构里面的列顺序显示
	for (auto itr_ = tableAttri.mapFeildAtrri.begin(); itr_ != tableAttri.mapFeildAtrri.end(); ++itr_)
	{
		if (nColCounts <= itr_->second.iColIndex - nColID_Min)
			continue;

		m_pBCGGrid->SetColumnName(itr_->second.iColIndex - nColID_Min,itr_->second.strColShowName);		//设置显示的中文名称
		m_pBCGGrid->SetColumnWidth(itr_->second.iColIndex - nColID_Min,itr_->second.iColWidth < nColMinWidth ? nColMinWidth :itr_->second.iColWidth);			//设置宽度
		m_pBCGGrid->SetColumnVisible(itr_->second.iColIndex - nColID_Min,itr_->second.isShow);			//是否显示

		m_pBCGGrid->EnableColumnFilterEdit(itr_->second.isEnableFilter,itr_->second.iColIndex - nColID_Min,_T(""));		//当前列是否允许筛选

		m_mapColID.insert(make_pair(itr_->second.strColID,itr_->second.iColIndex - nColID_Min));
		m_mapColWithFieldId.insert(make_pair(itr_->second.iColIndex - nColID_Min, itr_->second.strColID));
		m_mapColName.insert(make_pair(itr_->second.iColIndex - nColID_Min,itr_->second.strColShowName));
		m_mapColEdit.insert(make_pair(itr_->second.strColID,itr_->second.isEdit));
		m_mapCol_Name_ID.insert(make_pair(itr_->second.strColID,itr_->second.strColShowName));

		//右侧冰冻列		by WangZY 2017/11/28
		if(itr_->second.iLock==2)
		{
			m_pBCGGrid->GetColumnsInfo().SetRightFreezeColumn(itr_->second.iColIndex - nColID_Min,TRUE);
		}

		if (itr_->second.iLock == 1)	//左侧冰冻
		{
			nFrozenCounts_Left += 1;
			m_vecFrozenIndex.push_back(itr_->second.iColIndex- nColID_Min);
		}
		else if (itr_->second.iLock == 2) //右侧冰冻
		{
			nFrozenCounts_Right += 1;
			m_vecFrozenIndex.push_back(itr_->second.iColIndex- nColID_Min);
		}
	}

	//设置左侧冰冻列
	if (nFrozenCounts_Left>0)
	{
		m_pBCGGrid->FreezeColumns(nFrozenCounts_Left,FALSE);
	}
	else
	{
		m_pBCGGrid->UnfreezeColumns(FALSE);
	}

	//设置右侧冰冻列
	if (nFrozenCounts_Right>0)
	{
		m_pBCGGrid->FreezeRightColumns(nFrozenCounts_Right,FALSE);
	}
	else
	{
		m_pBCGGrid->UnfreezeRightColumns(FALSE);
	}
	SetFilterFieldInfo(mapFiledFilter); //设置筛选数据		by WangZY 2018/06/06

	m_pBCGGrid->SetRedraw(TRUE);
	m_pBCGGrid->AdjustLayout();

   //DeleteObject(hft);
	return TRUE;
}

BOOL CDlgBCGGrid::GetGridAttriInfo(__out S_GridCtrl_TableAttri &tableAttri)
{
	if (m_pBCGGrid)
	{
      const double clf_ScaleValue = m_pBCGGrid->GetScale();
		int nColID_Min = 100;
		for (auto itr_ = tableAttri.mapFeildAtrri.begin();
			itr_ != tableAttri.mapFeildAtrri.end(); ++itr_)
		{
			if (itr_->second.iColIndex < nColID_Min)
				nColID_Min = itr_->second.iColIndex;
		}

		const int nColumnCount = m_pBCGGrid->GetColumnCount ();

		int* aColumnsOrder = new int [nColumnCount];
		memset (aColumnsOrder, -1, nColumnCount * sizeof (int));
		vector<int> vec_col_order;		//列的显示顺序
		if (m_pBCGGrid->GetColumnsInfo().GetColumnOrderArray((LPINT) aColumnsOrder, nColumnCount))
		{
			for (int i=0; i< nColumnCount; ++i)
			{
				if (aColumnsOrder[i] == -1)
				{
					for (int k=0; k < nColumnCount; ++k)
					{
						auto itr_find = std::find(vec_col_order.begin(),vec_col_order.end(),k);
						if (itr_find == vec_col_order.end())
						{
							vec_col_order.push_back(k);
							break;
						}
					}
				}
				else
				{
					vec_col_order.push_back(aColumnsOrder[i]);
				}
			}
		}
		delete [] aColumnsOrder;

		if (nColumnCount >0 && m_mapColID.size() > 0)
		{
			for (auto itr_attri = m_tableAttri.mapFeildAtrri.begin(); itr_attri != m_tableAttri.mapFeildAtrri.end(); ++itr_attri)
			{
				auto itr_col = m_mapColID.find(itr_attri->second.strColID);
				if (itr_col == m_mapColID.end())
				{
					continue;
				}
				int iCol = itr_col->second ;
				if (iCol >=0 && iCol < nColumnCount)
				{
					itr_attri->second.isShow = m_pBCGGrid->GetColumnVisible(iCol) ? true : false;		//是否显示
					if (true == itr_attri->second.isShow)
					{
						itr_attri->second.iColWidth = 
                     m_pBCGGrid->GetColumnWidth(iCol)/clf_ScaleValue;		//列宽
					}

					for (int kk = 0; kk <  vec_col_order.size(); ++kk)
					{
						if (GetColName(vec_col_order[kk]) == itr_attri->first)
						{
							itr_attri->second.iColIndex = kk;
							break;
						}
					}
				}
			}
		}
	}
	tableAttri = m_tableAttri;
	return TRUE;
}

BOOL CDlgBCGGrid::GetGridDataInfo(__out MAP_GridCtrl_AllData &data)
{

	data.clear();
	//if (NULL == m_pBCGGrid || !IsWindow(m_pBCGGrid->GetSafeHwnd()))
	//	return FALSE;

	//const int nColCounts  = m_pBCGGrid->GetColumnCount();
	//const int nRowCounts = m_pBCGGrid->GetRowCount();

	//CBCGPGridRow* pRow = NULL;
	//for (int iRow = 0; iRow < nRowCounts; ++iRow)
	//{
	//	pRow = m_pBCGGrid->GetRow(iRow);
	//	if (pRow)
	//	{
	//		DWORD_PTR ptr = pRow->GetData();
	//		MAP_GridCtrl_RowData row_data = *(MAP_GridCtrl_RowData*)ptr;
	//		data.insert(make_pair(iRow,row_data));
	//	}
	//}
	data = m_tableData;
	return TRUE;
}

void CDlgBCGGrid::RefreshGridCtrlInfo(__in BOOL bEnsureVisableFirstDataRow /*= TRUE*/)
{

	m_nCheckRowCount = 0;
	if (!IsWindow(m_pBCGGrid->GetSafeHwnd()))
	{
		return;
	}

	if (m_bUserPaginationMode
      &&emPM_Local == m_emPMPaginationModeFlag)
	{
		//if (nullptr == m_dbRecordSetPtr)
		//{
		//	return;
		//}
		//RefreshDataInfoToGrid(0,FALSE);

		return;
	}

	{
		START_MY_OUTPUT_LOG_;
		MY_OUTPUT_LOG_;
		m_pBCGGrid->SetRedraw(FALSE);
		int iRowCounts = m_pBCGGrid->GetRowCount();
		for (int i=iRowCounts-1; i>=0; --i)
		{
			m_pBCGGrid->RemoveRow(i);
		}
		MY_OUTPUT_LOG_;
		const int nColCounts  = m_pBCGGrid->GetColumnCount();
		int iRow = 0;
		MY_OUTPUT_LOG_;
		for (auto itr_ = m_tableData.begin(); itr_ != m_tableData.end(); ++itr_)
		{
			//Create Row
			CBCGPGridRow* pRow = m_pBCGGrid->CreateRow(nColCounts);

			//保存行数据属性等
			const MAP_GridCtrl_RowData &dataRow = itr_->second;
			pRow->SetData((DWORD_PTR)(&dataRow));		
			//end 保存行数据属性等

			int nCol = 0;	//当前列
			for (auto itr_2 = itr_->second.begin(); 
				itr_2 != itr_->second.end(); ++itr_2)
			{
				if (m_mapColID.size() <= 0)
					break;

				auto itr_col = m_mapColID.find(itr_2->first);
				if (itr_col == m_mapColID.end() || itr_col->second >= nColCounts)
					continue;
				nCol = itr_col->second;

				//是否可编辑
				BOOL bEdit = TRUE;
				auto itr_edit = m_mapColEdit.find(itr_2->first);
				if (itr_edit != m_mapColEdit.end())
				{
					bEdit = itr_edit->second;
				}
				pRow->GetItem(nCol)->SetReadOnly(!bEdit);
				//end 编辑

				//test
				//pRow->GetItem(nCol)->SetDataBar(nCol);			//百分比
				auto itr_frozen_index = std::find(m_vecFrozenIndex.begin(),m_vecFrozenIndex.end(),nCol);
				if (itr_frozen_index != m_vecFrozenIndex.end())
				{
					//单元格背景颜色
					if (itr_2->second.sptr_cellBackgroundClrVec.get())
					{	
						if ((*(itr_2->second.sptr_cellBackgroundClrVec)).size() > 0)
						{
						}
						else
						{
							pRow->GetItem(nCol)->SetDataColorScale(10);
						}
					}
					else
					{
						pRow->GetItem(nCol)->SetDataColorScale(10);
					}
				}
				//end 

				

				switch(itr_2->second.fieldCtrlType)		//控件类型
				{
				
				case CB_enum_FieldCtrl_Checkbox:
					{
						pRow->ReplaceItem(nCol,new CBCGPGridCheckItem(itr_2->second.strValue != _T("0") ? TRUE:FALSE));		//check box
					}
					break;
				case CB_enum_FieldCtrl_NormalCombox:	//drop list
					{
						//LPCTSTR Data_Array [30] = {};
						CBCGPGridItem* pItem = new CBCGPGridItem (itr_2->second.strValue.GetBuffer(0));
						pItem->SetReadOnly (TRUE);
						if (itr_2->second.sptr_normalComboxData.get())
						{
							for(int i=0; i< itr_2->second.sptr_normalComboxData->size(); ++i)
							{
								pItem->AddOption((*itr_2->second.sptr_normalComboxData)[i],TRUE);
							}
						}
						else
						{
							pItem->AddOption(_T(""),TRUE);
						}
						pRow->ReplaceItem (nCol, pItem);
					}
					break;
				case CB_enum_FieldCtrl_SpecialCombox:	//pop dlg
					{}
					break;
				case CB_enum_FieldCtrl_Radio:
					{
						CBCGPGridCheckItem *pItem = new CBCGPGridCheckItem(
							(bool)(itr_2->second.strValue == _T("1")));		//check box
						pRow->ReplaceItem(nCol,pItem);		//check box
					}
					break;
				case CB_enum_FieldCtrl_EditCombox:	//drop down
					{
						//LPCTSTR Data_Array [30] = {};
						CBCGPGridItem* pItem = new CBCGPGridItem (itr_2->second.strValue.GetBuffer(0));
						if (itr_2->second.sptr_normalComboxData.get())
						{
							for(int i=0; i< itr_2->second.sptr_normalComboxData->size(); ++i)
							{
								pItem->AddOption((*itr_2->second.sptr_normalComboxData)[i],TRUE);
							}
						}
						else
						{
							pItem->AddOption(_T(""),TRUE);
						}
						pRow->ReplaceItem (nCol, pItem);
					}
					break;
				case CB_enum_FieldCtrl_Button: //按钮
					{
						CButtonItem *pItem = new CButtonItem(
							itr_2->second.strValue, UID_GRID_BTN1);		
						pRow->ReplaceItem(nCol,pItem);
						if (0 == itr_2->second.byteProgress)
						{
							pItem->Enable(TRUE);
						}
						else
						{
							pItem->Enable(FALSE);
						}
					}
					break;
            case CB_enum_FieldCtrl_BallColor://颜色球
               {
                  COLORREF color1 = -1,color2 = -1,color3 = -1;
                  if (itr_2->second.sptr_cellBackgroundClrVec.get())
                  {
                     if ((*(itr_2->second.sptr_cellBackgroundClrVec)).size() > 1)
                     {
                        auto itColor1 = (*(itr_2->second.sptr_cellBackgroundClrVec)).at(1);
                        color1 = itColor1;
                     }
                     if ((*(itr_2->second.sptr_cellBackgroundClrVec)).size() > 2)
                     {
                        auto itColor2 = (*(itr_2->second.sptr_cellBackgroundClrVec)).at(2);
                        color2 = itColor2;
                     }
                     if ((*(itr_2->second.sptr_cellBackgroundClrVec)).size() > 3)
                     {
                        auto itColor3 = (*(itr_2->second.sptr_cellBackgroundClrVec)).at(3);
                        color2 = itColor3;
                     }
                  }
                  CString strText1,strText2,strText3;
                  if (itr_2->second.sptr_normalComboxData.get())
                  {
                     if ((*(itr_2->second.sptr_normalComboxData)).size() > 0)
                     {
                        strText1 = (*(itr_2->second.sptr_normalComboxData)).at(0);
                     }
                     if ((*(itr_2->second.sptr_normalComboxData)).size() > 1)
                     {
                        strText2 = (*(itr_2->second.sptr_normalComboxData)).at(1);
                     }
                     if ((*(itr_2->second.sptr_normalComboxData)).size() > 2)
                     {
                        strText3 = (*(itr_2->second.sptr_normalComboxData)).at(2);
                     }
                  }
                  CBallColorBCGPGridCellItem *pItem = new CBallColorBCGPGridCellItem(strText1,strText2,strText3,color1, color2,color3);
                  pRow->ReplaceItem(nCol,pItem);
                  if (0 == itr_2->second.byteProgress)
                  {
                     pItem->Enable(TRUE);
                  }
                  else
                  {
                     pItem->Enable(FALSE);
                  }
               }
               break;
				case CB_enum_FieldCtrl_Text:
				default:
					break;
				}

				switch(itr_2->second.fieldDataType)		//数据类型
				{
				case CB_enum_FieldData_Int:	//整型
					{
						if (itr_2->second.fieldCtrlType == CB_enum_FieldCtrl_Checkbox 
							|| itr_2->second.fieldCtrlType == CB_enum_FieldCtrl_Radio)
						{
							pRow->GetItem(nCol)->SetValue(
								(bool)(_ttoi(itr_2->second.strValue) != 0));
						}
						else
						{
							long iValue = _ttoi(itr_2->second.strValue);
							pRow->GetItem(nCol)->SetValue(iValue);
						}
						
					}
					break;
				case CB_enum_FieldData_Double2Point:	//小数点
					{
						double fValue = _ttof(itr_2->second.strValue);

						//扣重精确度修改
						if(itr_2->first == _T("iKouzhong"))
						{
							pRow->GetItem(nCol)->SetUserFormat(TRUE,_T("%.4f"),fValue);
						}
						else
						{
							pRow->GetItem(nCol)->SetUserFormat(TRUE,_T("%.2f"),fValue);
						}
						pRow->GetItem(nCol)->SetValue(fValue);


					}
					break;
				case CB_enum_FieldData_Double3Point:
					{
						double fValue = _ttof(itr_2->second.strValue);
						pRow->GetItem(nCol)->SetUserFormat(TRUE,_T("%.3f"),fValue);
						pRow->GetItem(nCol)->SetValue(fValue);
					}
					break;
            case CB_enum_FieldData_Double4Point:
               {
                  double fValue = _ttof(itr_2->second.strValue);
                  pRow->GetItem(nCol)->SetUserFormat(TRUE,_T("%.4f"),fValue);
                  pRow->GetItem(nCol)->SetValue(fValue);
               }
               break;
				case CB_enum_FieldData_Button:	//按钮
					{
						_bstr_t strValue = itr_2->second.strValue;
						pRow->GetItem(nCol)->SetValue(strValue);
					}
					break;
            case CB_enum_FieldData_BallColor:
               {
                  auto pCell =  pRow->GetItem(nCol);
                  if (pCell->GetRuntimeClass() == RUNTIME_CLASS(CBallColorBCGPGridCellItem))
                  {
                     COLORREF color1 = -1,color2 = -1,color3 = -1;
                     if (itr_2->second.sptr_cellBackgroundClrVec.get())
                     {
                        if ((*(itr_2->second.sptr_cellBackgroundClrVec)).size() > 1)
                        {
                           auto itColor1 = (*(itr_2->second.sptr_cellBackgroundClrVec)).at(1);
                           color1 = itColor1;
                        }
                        if ((*(itr_2->second.sptr_cellBackgroundClrVec)).size() > 2)
                        {
                           auto itColor2 = (*(itr_2->second.sptr_cellBackgroundClrVec)).at(2);
                           color2 = itColor2;
                        }
                        if ((*(itr_2->second.sptr_cellBackgroundClrVec)).size() > 3)
                        {
                           auto itColor3 = (*(itr_2->second.sptr_cellBackgroundClrVec)).at(3);
                           color3 = itColor3;
                        }
                     }
                     CString strText1,strText2,strText3;
                     if (itr_2->second.sptr_normalComboxData.get())
                     {
                        if ((*(itr_2->second.sptr_normalComboxData)).size() > 0)
                        {
                           strText1 = (*(itr_2->second.sptr_normalComboxData)).at(0);
                        }
                        if ((*(itr_2->second.sptr_normalComboxData)).size() > 1)
                        {
                           strText2 = (*(itr_2->second.sptr_normalComboxData)).at(1);
                        }
                        if ((*(itr_2->second.sptr_normalComboxData)).size() > 2)
                        {
                           strText3 = (*(itr_2->second.sptr_normalComboxData)).at(2);
                        }
                     }
                     ((CBallColorBCGPGridCellItem *)pCell)->SetDisplayText(strText1,strText2,strText3);
                     ((CBallColorBCGPGridCellItem *)pCell)->SetColor(color1,color2,color3);
                  }
               }
               break;
				case CB_enum_FieldData_CString:
				default:
					{
						_bstr_t strValue = itr_2->second.strValue;
						if (itr_2->second.fieldCtrlType == CB_enum_FieldCtrl_Checkbox 
							|| itr_2->second.fieldCtrlType == CB_enum_FieldCtrl_Radio)
						{
							pRow->GetItem(nCol)->SetValue(
								(bool)(_ttoi(itr_2->second.strValue) != 0));
						}
						else
						{
							pRow->GetItem(nCol)->SetValue(strValue);
						}
					}
					break;
				}

				//单元格背景颜色
				if (itr_2->second.sptr_cellBackgroundClrVec.get())
				{
					vector<int>& vec_clr = *(itr_2->second.sptr_cellBackgroundClrVec);
					if (vec_clr.size() > 0)
					{
						pRow->GetItem(nCol)->SetBackgroundColor(vec_clr[0]);
					}
				}

				++nCol;
			}
			
			m_pBCGGrid->AddRow(pRow, FALSE ); 
		}
		MY_OUTPUT_LOG_;
		m_pBCGGrid->EnableAlternateRows(TRUE);
		m_pBCGGrid->SetRedraw(TRUE);
		m_pBCGGrid->AdjustLayout();
		MY_OUTPUT_LOG_;
		RefreshGridStatisticRow(m_pBCGGrid);		//放在adjustlayout后面，不然会奔溃情况
		MY_OUTPUT_LOG_;
	}

	return;
}

int CDlgBCGGrid::ChangeDataInfoByFieldId(__in const CString &strFieldId,
	__in const S_GridCtrl_FieldData &dataInfo,
	__in const EM_SEL_TYPE &nSelType /*= emSel*/)
{
	//return value : -1 错误，0 数据未修改，1 数据修改成功
	if (NULL == m_pBCGGrid || 
		!IsWindow(m_pBCGGrid->GetSafeHwnd()))
	{
		return -1;
	}

	if (emNull == nSelType)
	{
		return 0;
	}

	//要改变的列 ID
	int nCurCol = -1;		
	auto itr_col_id = m_mapColID.find(strFieldId);
	if (itr_col_id != m_mapColID.end())
		nCurCol = itr_col_id->second;

	if (nCurCol < 0)
		return -1;

	//总的行数
	const int nRowCounts = m_pBCGGrid->GetRowCount();
	CBCGPGridRow* pRow = NULL;

	m_pBCGGrid->SetRedraw(FALSE);

	if (emSel == nSelType)		//改变选中行的数据	
	{
		for (int iRow = 0; iRow < nRowCounts; ++iRow)
		{
			pRow = m_pBCGGrid->GetRow(iRow);
			if (pRow)
			{ 
				if (pRow->GetCheck() == 1) 
				{
					MAP_GridCtrl_RowData& dataRow = (*((MAP_GridCtrl_RowData*)pRow->GetData()));
					auto itr_col_data = dataRow.find(strFieldId); 
					if (itr_col_data != dataRow.end())
					{
						itr_col_data->second.strValue = dataInfo.strValue;
						pRow->GetItem(nCurCol)->SetValue(_bstr_t(dataInfo.strValue));
					}
				}
			}
		}
	}

	if (emJudgeHasSel == nSelType)	//判断是否有选中行，不做数据修改
	{
		return 0;
	}
	 
	if (emAllOnGrid == nSelType || emAllData == nSelType)	//改变网格上所有行的数据 （包含在网格上和不在网格上的）
	{
		for (int iRow = 0; iRow < nRowCounts; ++iRow)
		{
			pRow = m_pBCGGrid->GetRow(iRow);
			if (pRow)
			{ 
				MAP_GridCtrl_RowData& dataRow = (*((MAP_GridCtrl_RowData*)pRow->GetData()));
				auto itr_col_data = dataRow.find(strFieldId); 
				if (itr_col_data != dataRow.end())
				{
					itr_col_data->second.strValue = dataInfo.strValue;
					pRow->GetItem(nCurCol)->SetValue(_bstr_t(dataInfo.strValue));
				}
			}
		}
	}

	if (emUnSel == nSelType)	//改变网格上未选中的行的数据
	{
		for (int iRow = 0; iRow < nRowCounts; ++iRow)
		{
			pRow = m_pBCGGrid->GetRow(iRow);
			if (pRow)
			{ 
				if (pRow->GetCheck() != 1) 
				{
					MAP_GridCtrl_RowData& dataRow = (*((MAP_GridCtrl_RowData*)pRow->GetData()));
					auto itr_col_data = dataRow.find(strFieldId); 
					if (itr_col_data != dataRow.end())
					{
						itr_col_data->second.strValue = dataInfo.strValue;
						pRow->GetItem(nCurCol)->SetValue(_bstr_t(dataInfo.strValue));
					}
				}
			}
		}
	}

	m_pBCGGrid->SetRedraw(TRUE);
	m_pBCGGrid->Invalidate();

	return 1;
}

int CDlgBCGGrid::ChangeDataInfoByFieldId(__in const CString &strFieldId,
	__in const CString &strValue,
	__in const EM_SEL_TYPE &nSelType /*= emSel*/)
{
	S_GridCtrl_FieldData dataInfo;
	dataInfo.strValue = strValue;
	return ChangeDataInfoByFieldId(strFieldId,dataInfo,nSelType);
}

//		by WangZY 2018/01/31
BOOL CDlgBCGGrid::SetGridAttriInfoNew(
	__in const S_GridCtrl_TableAttri &infoTableAttri,
	__in int iShowColAlign /*= HDF_CENTER*/)
{

	m_bUseNewAttri = TRUE;						//新的表属性方式	by WangZY 2018/01/31
	m_tableAttri = infoTableAttri;
	S_GridCtrl_TableAttri &tableAttri = m_tableAttri;

	if (NULL == m_pBCGGrid 
		|| !IsWindow(m_pBCGGrid->GetSafeHwnd()))
	{
		return FALSE;
	}

	m_pBCGGrid->SetRedraw(FALSE);

	int iRowCounts = m_pBCGGrid->GetRowCount();
	for (int i=iRowCounts-1; i>=0; --i)
	{
		m_pBCGGrid->RemoveRow(i);		//清空行
	}

	// add by wuzhihua 2018/1/13  获取筛选信息
	std::map<CString , CString > mapFiledFilter;//字段 对应 筛选信息 map
	
   GetFilterFieldInfo(mapFiledFilter);
   
	m_pBCGGrid->GetColumnsInfo().DeleteAllColumns();	//清空列

	int nColID_Min = 100;

	m_mapColWithFieldId.clear();
	m_mapColID.clear();
	m_mapColName.clear();
	m_mapColEdit.clear();
	m_mapCol_Name_ID.clear();
	//初始化表格数据时，清空表格原有数据，重新插入列标题。。。
	m_pBCGGrid->RemoveAll();



	//是否允许排序
	DWORD dHeaderFlag = m_pBCGGrid->GetHeaderFlags();
	if (tableAttri.isAllowSort)
	{
		dHeaderFlag = dHeaderFlag|BCGP_GRID_HEADER_SORT ;
	}
	else
	{
		dHeaderFlag = dHeaderFlag & 0x03;	
	}
	m_pBCGGrid->EnableHeader(TRUE,dHeaderFlag);	//是否允许排序

	//修复：#5911：标题过滤icon调整		by WangZY 2017/12/11
	m_pBCGGrid->EnableShowFilterBarSearchImg(FALSE);
	m_pBCGGrid->EnableFilterBar(tableAttri.isShowSortBar,_T("<all>"));	//是否显示筛选栏
	m_pBCGGrid->SetWholeRowSel(tableAttri.isWholeRowSelect);					//整行选择
	m_pBCGGrid->EnableCheckBoxes(tableAttri.isMultiRowSelect);				//多行选择 
	m_pBCGGrid->EnableDragHeaderItems(tableAttri.isEnableDragCol);			//列位置能否拖动
	m_pBCGGrid->SetReadOnly(!tableAttri.isEnableEdit);							//表是否可编辑	
	m_pBCGGrid->setUserRowHeight(tableAttri.nDataRowHeight,TRUE);			//表格行高


	//设置字体
	HFONT hft;
	hft = CreateFont(tableAttri.iDataRowFont+2,0,0,0,FW_NORMAL,false,false,false,GB2312_CHARSET,OUT_OUTLINE_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,FF_MODERN,_T("宋体"));
	//m_pBCGGrid->SendMessage(WM_SETFONT,(WPARAM)hft);
   CFont oCreateFont;
   oCreateFont.FromHandle(hft);
   m_pBCGGrid->SetFont(&oCreateFont);
   DeleteObject(hft);

	//是否显示列标题筛选器	by WangZY 2018/02/26
	m_pBCGGrid->EnableFilter_My(tableAttri.isShowTitleFilter);	

	//tableAttri.IsMultiRowSelectNoLoseFocus;		//多行选择不失焦点
	//tableAttri.isPrintHengXiang;					//是否横向打印
	//tableAttri.isShowSumBar;					//是否显示合计栏

	//是否显示合计栏
	if (m_tableAttri.isShowSumBar)
	{
		m_pBCGGrid->SetGridFooterHeight(m_tableAttri.nDataRowHeight);
		m_pBCGGrid->GetColumnsInfo().SetEnableShowFooterRow(TRUE);
      m_pBCGGrid->GetColumnsInfo().SetFooterHeaderText(_T("合计"));
	}
	else
	{
		m_pBCGGrid->SetGridFooterHeight(0);
		m_pBCGGrid->GetColumnsInfo().SetEnableShowFooterRow(FALSE);
	}

	std::map<int,CString> &mapShowCol = m_mapShowCol;
	mapShowCol.clear();
	int iCol = 0;
	for (auto itr_ = tableAttri.mapFeildAtrri.begin();
		itr_ != tableAttri.mapFeildAtrri.end(); ++itr_ )
	{
		if (itr_->second.iColIndex < nColID_Min)
		{
			nColID_Min = itr_->second.iColIndex;
		}
		if (!itr_->second.isShow)
		{
			continue;
		}
		mapShowCol[itr_->second.iColIndex] = itr_->first;
		
		m_pBCGGrid->InsertColumn(iCol,_T(""),10);		//先插入空的数据
		m_pBCGGrid->SetHeaderAlign(iCol,iShowColAlign);
		m_pBCGGrid->SetColumnAlign(iCol, iShowColAlign);
		++iCol;
	}

	const int nColCounts  = m_pBCGGrid->GetColumnCount();
	int nColMinWidth = m_pBCGGrid->GetBaseHeight();		//最小列宽

	int nFrozenCounts_Left = 0;			//左侧冰冻列数量	
	int nFrozenCounts_Right = 0;		//右侧冰冻列数量
	m_vecFrozenIndex.clear();
	
	int nCol=0;
	for (auto it=mapShowCol.begin();it!=mapShowCol.end(); it++,nCol++)
	{
		auto itr_ = tableAttri.mapFeildAtrri.find(it->second);
		if (itr_ == tableAttri.mapFeildAtrri.end())
		{
			continue;
		}
		
		
		//分页模式下的暂不使用标题头过滤器功能		by WangZY 2018/03/14
		if (!m_bUserPaginationMode ||  !(m_bUserPaginationMode && m_emPMPaginationModeFlag == emPM_Local))
		{
			//以下两行代码只是测试用，非正式代码		by WangZY 2018/02/27
			//auto itFilter = std::find(m_vecFilterId.begin(),m_vecFilterId.end(),it->second);
			//if (itFilter != m_vecFilterId.end())
			bool bFilter = (itr_->second.isEnableFilter&&tableAttri.isShowTitleFilter);
			{
				//设置列标题过滤		by WangZY 2018/02/28
				m_pBCGGrid->GetColumnsInfo().SetColumnEnableTitleFilter(nCol,bFilter);
				auto itLst = m_mapFilterListInfo.find(it->second);
				if (itLst != m_mapFilterListInfo.end())
				{
					CStringList lst;
					for (auto itVec=itLst->second.begin(); itVec!=itLst->second.end();++itVec)
					{
						lst.AddTail(*itVec);
					}	
					m_pBCGGrid->m_infoFilter.AddColumnFilterList(nCol,lst);
				}
			}
		}
		

		m_pBCGGrid->GetColumnsInfo().SetColumnData(nCol,(DWORD_PTR)&(itr_->second));
		m_pBCGGrid->SetColumnName(nCol,itr_->second.strColShowName);		//设置显示的中文名称
		m_pBCGGrid->SetColumnWidth(nCol,itr_->second.iColWidth < nColMinWidth ? nColMinWidth :itr_->second.iColWidth);			//设置宽度
		//m_pBCGGrid->SetColumnVisible(itr_->second.iColIndex - nColID_Min,itr_->second.isShow);			//是否显示
		
		m_pBCGGrid->EnableColumnFilterEdit(itr_->second.isEnableFilter,itr_->second.iColIndex - nColID_Min,_T(""));		//当前列是否允许筛选

		m_mapColID.insert(make_pair(itr_->second.strColID,nCol));
		m_mapColWithFieldId.insert(make_pair(nCol, itr_->second.strColID));
		//m_mapColName.insert(make_pair(itr_->second.iColIndex - nColID_Min,itr_->second.strColShowName));
		m_mapColEdit.insert(make_pair(itr_->second.strColID,itr_->second.isEdit));
		//m_mapCol_Name_ID.insert(make_pair(itr_->second.strColID,itr_->second.strColShowName));

		//右侧冰冻列		by WangZY 2017/11/28
		if(itr_->second.iLock==2)
		{
			m_pBCGGrid->GetColumnsInfo().SetRightFreezeColumn(itr_->second.iColIndex - nColID_Min,TRUE);
		}

		if (itr_->second.iLock == 1)	//左侧冰冻
		{
			nFrozenCounts_Left += 1;
			m_vecFrozenIndex.push_back(itr_->second.iColIndex- nColID_Min);
		}
		else if (itr_->second.iLock == 2) //右侧冰冻
		{
			nFrozenCounts_Right += 1;
			m_vecFrozenIndex.push_back(itr_->second.iColIndex- nColID_Min);
		}
	}

	//设置左侧冰冻列
	if (nFrozenCounts_Left>0)
	{
		m_pBCGGrid->FreezeColumns(nFrozenCounts_Left,FALSE);
	}
	else
	{
		m_pBCGGrid->UnfreezeColumns(FALSE);
	}

	//设置右侧冰冻列
	if (nFrozenCounts_Right>0)
	{
		m_pBCGGrid->FreezeRightColumns(nFrozenCounts_Right,FALSE);
	}
	else
	{
		m_pBCGGrid->UnfreezeRightColumns(FALSE);
	}

   SetFilterFieldInfo(mapFiledFilter); //设置筛选数据		by WangZY 2018/06/06

	m_pBCGGrid->SetRedraw(TRUE);
	m_pBCGGrid->AdjustLayout();

   //DeleteObject(hft);
	return TRUE;
}

//新的刷新网格控件的信息的接口		by WangZY 2018/01/31
void CDlgBCGGrid::RefreshGridCtrlInfoNew(
	__in BOOL bEnsureVisableFirstDataRow /*= TRUE*/)
{
	if (!IsWindow(m_pBCGGrid->GetSafeHwnd()))
	{
		return;
	}

	if (m_bUserPaginationMode
      &&emPM_Local==m_emPMPaginationModeFlag)
	{
		//if (nullptr == m_dbRecordSetPtr)
		//{
		//	return;
		//}
		//RefreshDataInfoToGrid(0,FALSE);

		return;
	}

	{
		START_MY_OUTPUT_LOG_;
		MY_OUTPUT_LOG_;
		m_pBCGGrid->SetRedraw(FALSE);
		//int iRowCounts = m_pBCGGrid->GetRowCount();
		//for (int i=iRowCounts-1; i>=0; --i)
		//{
		//	m_pBCGGrid->RemoveRow(i);
		//}
		m_pBCGGrid->RemoveAll();
		MY_OUTPUT_LOG_;
		const int nColCounts  = m_pBCGGrid->GetColumnCount();
		int iRow = 0;
		MY_OUTPUT_LOG_;
		if (m_mapColID.size() <= 0)
		{
			return;
		}
		
		MY_OUTPUT_LOG_;
		std::map<int,CString> &mapShowCol = m_mapShowCol;
		for (auto itr_=m_tableData.begin(); itr_!=m_tableData.end(); ++itr_)
		{
			//MY_OUTPUT_LOG_;
			//Create Row
			CBCGPGridRow* pRow = m_pBCGGrid->CreateRow(nColCounts);

			//保存行数据属性等
			MAP_GridCtrl_RowData &dataRow = itr_->second;
			pRow->SetData((DWORD_PTR)(&dataRow));

			//m_pBCGGrid->AddRow(pRow, FALSE ); 
			//continue;
			//end 保存行数据属性等
			//MY_OUTPUT_LOG_;
			int nCol = 0;	//当前列
			for (auto itShow=mapShowCol.begin();itShow!=mapShowCol.end();
				itShow++,nCol++)
			{
				auto itr_2=dataRow.find(itShow->second);
				if (itr_2 == dataRow.end())
				{
					continue;
				}
			/*}
			for (auto itr_2=dataRow.begin(); itr_2!=dataRow.end(); ++itr_2)
			{*/
// 				const CString &strFieldId = itr_2->first;
// 				auto itAttri = m_tableAttri.mapFeildAtrri.find(strFieldId);
// 				if (itAttri == m_tableAttri.mapFeildAtrri.end())
// 				{
// 					continue;
// 				}
// 				BOOL bShow = itAttri->second.isShow;
// 				if (!bShow)
// 				{
// 					continue;
// 				}
// 				auto itr_col = m_mapColID.find(itr_2->first);
// 				if (itr_col == m_mapColID.end() 
// 					|| itr_col->second >= nColCounts)
// 				{
// 					continue;
// 				}
// 				nCol = itr_col->second;

				//是否可编辑
				BOOL bEdit = TRUE;
				auto itr_edit = m_mapColEdit.find(itr_2->first);
				if (itr_edit != m_mapColEdit.end())
				{
					bEdit = itr_edit->second;
				}
				pRow->GetItem(nCol)->SetReadOnly(!bEdit);
				//end 编辑
				
				auto itr_frozen_index = std::find(m_vecFrozenIndex.begin(),m_vecFrozenIndex.end(),nCol);
				if (itr_frozen_index != m_vecFrozenIndex.end())
				{
					if (itr_2->second.sptr_cellBackgroundClrVec.get())
					{
						if ((*(itr_2->second.sptr_cellBackgroundClrVec)).size() > 0)
						{
						}
						else
						{
							pRow->GetItem(nCol)->SetDataColorScale(10);
						}
					}
					else
					{
						pRow->GetItem(nCol)->SetDataColorScale(10);
					}
				}

				
				switch(itr_2->second.fieldCtrlType)		//控件类型
				{
				case CB_enum_FieldCtrl_Checkbox:
					{
						pRow->ReplaceItem(nCol,new CBCGPGridCheckItem(itr_2->second.strValue != _T("0") ? TRUE:FALSE));		//check box
					}
					break;
				case CB_enum_FieldCtrl_NormalCombox:	//drop list
					{
						CBCGPGridItem* pItem = new CBCGPGridItem (itr_2->second.strValue.GetBuffer(0));
						pItem->SetReadOnly (TRUE);
						if (itr_2->second.sptr_normalComboxData.get())
						{
							for(int i=0; i< itr_2->second.sptr_normalComboxData->size(); ++i)
							{
								pItem->AddOption((*itr_2->second.sptr_normalComboxData)[i],TRUE);
							}
						}
						else
						{
							pItem->AddOption(_T(""),TRUE);
						}
						pRow->ReplaceItem (nCol, pItem);
					}
					break;
				case CB_enum_FieldCtrl_SpecialCombox:	//pop dlg
					{}
					break;
				case CB_enum_FieldCtrl_Radio:
					{
						CBCGPGridCheckItem *pItem = new CBCGPGridCheckItem(
							(bool)(itr_2->second.strValue == _T("1")));		//check box
						pRow->ReplaceItem(nCol,pItem);		//check box
					}
					break;
				case CB_enum_FieldCtrl_EditCombox:	//drop down
					{
						CBCGPGridItem* pItem = new CBCGPGridItem (itr_2->second.strValue.GetBuffer(0));
						if (itr_2->second.sptr_normalComboxData.get())
						{
							for(int i=0; i< itr_2->second.sptr_normalComboxData->size(); ++i)
							{
								pItem->AddOption((*itr_2->second.sptr_normalComboxData)[i],TRUE);
							}
						}
						else
						{
							pItem->AddOption(_T(""),TRUE);
						}
						pRow->ReplaceItem (nCol, pItem);
					}
					break;
				case CB_enum_FieldCtrl_Button: //按钮
					{
						CButtonItem *pItem = new CButtonItem(
							itr_2->second.strValue, UID_GRID_BTN1);		
						pRow->ReplaceItem(nCol,pItem);
						if (0 == itr_2->second.byteProgress)
						{
							pItem->Enable(TRUE);
						}
						else
						{
							pItem->Enable(FALSE);
						}
					}
					break;
            case CB_enum_FieldCtrl_BallColor:
               {
                  COLORREF color1 = -1,color2 = -1,color3 = -1;
                  if (itr_2->second.sptr_cellBackgroundClrVec.get())
                  {
                     if ((*(itr_2->second.sptr_cellBackgroundClrVec)).size() > 1)
                     {
                        auto itColor1 = (*(itr_2->second.sptr_cellBackgroundClrVec)).at(1);
                        color1 = itColor1;
                     }
                     if ((*(itr_2->second.sptr_cellBackgroundClrVec)).size() > 2)
                     {
                        auto itColor2 = (*(itr_2->second.sptr_cellBackgroundClrVec)).at(2);
                        color2 = itColor2;
                     }
                     if ((*(itr_2->second.sptr_cellBackgroundClrVec)).size() > 3)
                     {
                        auto itColor3 = (*(itr_2->second.sptr_cellBackgroundClrVec)).at(3);
                        color3 = itColor3;
                     }
                  }
                  CString strText1,strText2,strText3;
                  if (itr_2->second.sptr_normalComboxData.get())
                  {
                     if ((*(itr_2->second.sptr_normalComboxData)).size() > 0)
                     {
                        strText1 = (*(itr_2->second.sptr_normalComboxData)).at(0);
                     }
                     if ((*(itr_2->second.sptr_normalComboxData)).size() > 1)
                     {
                        strText2 = (*(itr_2->second.sptr_normalComboxData)).at(1);
                     }
                     if ((*(itr_2->second.sptr_normalComboxData)).size() > 2)
                     {
                        strText3 = (*(itr_2->second.sptr_normalComboxData)).at(2);
                     }
                  }
                  CBallColorBCGPGridCellItem *pItem = new CBallColorBCGPGridCellItem(strText1,strText2,strText3,color1, color2,color3);
                  pRow->ReplaceItem(nCol,pItem);
               }
               break;
				case CB_enum_FieldCtrl_Text:
				default:
					break;
				}
				
				switch(itr_2->second.fieldDataType)		//数据类型
				{
				case CB_enum_FieldData_Int:	//整型
					{
						if (itr_2->second.fieldCtrlType == CB_enum_FieldCtrl_Checkbox 
							|| itr_2->second.fieldCtrlType == CB_enum_FieldCtrl_Radio)
						{
							pRow->GetItem(nCol)->SetValue(
								(bool)(_ttoi(itr_2->second.strValue) != 0),FALSE);
						}
						else
						{
							long iValue = _ttoi(itr_2->second.strValue);
							pRow->GetItem(nCol)->SetValue(iValue,FALSE);
						}

					}
					break;
				case CB_enum_FieldData_Double2Point:	//小数点
					{
						double fValue = _ttof(itr_2->second.strValue);
						pRow->GetItem(nCol)->SetUserFormat(TRUE,_T("%.2f"),fValue);
						pRow->GetItem(nCol)->SetValue(fValue,FALSE);


					}
					break;
				case CB_enum_FieldData_Double3Point:
					{
						double fValue = _ttof(itr_2->second.strValue);
						pRow->GetItem(nCol)->SetUserFormat(TRUE,_T("%.3f"),fValue);
						pRow->GetItem(nCol)->SetValue(fValue,FALSE);
					}
					break;
            case CB_enum_FieldData_Double4Point:
               {
                  double fValue = _ttof(itr_2->second.strValue);
                  pRow->GetItem(nCol)->SetUserFormat(TRUE,_T("%.4f"),fValue);
                  pRow->GetItem(nCol)->SetValue(fValue,FALSE);
               }
               break;
				case CB_enum_FieldData_Button:	//按钮
					{
						_bstr_t strValue = itr_2->second.strValue;
						pRow->GetItem(nCol)->SetValue(strValue,FALSE);
					}
					break;
            case CB_enum_FieldData_BallColor:
               {
                  auto pCell =  pRow->GetItem(nCol);
                  if (pCell->GetRuntimeClass() == RUNTIME_CLASS(CBallColorBCGPGridCellItem))
                  {
                     COLORREF color1 = -1,color2 = -1,color3 = -1;
                     if (itr_2->second.sptr_cellBackgroundClrVec.get())
                     {
                        if ((*(itr_2->second.sptr_cellBackgroundClrVec)).size() > 1)
                        {
                           auto itColor1 = (*(itr_2->second.sptr_cellBackgroundClrVec)).at(1);
                           color1 = itColor1;
                        }
                        if ((*(itr_2->second.sptr_cellBackgroundClrVec)).size() > 2)
                        {
                           auto itColor2 = (*(itr_2->second.sptr_cellBackgroundClrVec)).at(2);
                           color2 = itColor2;
                        }
                        if ((*(itr_2->second.sptr_cellBackgroundClrVec)).size() > 3)
                        {
                           auto itColor3 = (*(itr_2->second.sptr_cellBackgroundClrVec)).at(3);
                           color3 = itColor3;
                        }
                     }
                     CString strText1,strText2,strText3;
                     if (itr_2->second.sptr_normalComboxData.get())
                     {
                        if ((*(itr_2->second.sptr_normalComboxData)).size() > 0)
                        {
                           strText1 = (*(itr_2->second.sptr_normalComboxData)).at(0);
                        }
                        if ((*(itr_2->second.sptr_normalComboxData)).size() > 1)
                        {
                           strText2 = (*(itr_2->second.sptr_normalComboxData)).at(1);
                        }
                        if ((*(itr_2->second.sptr_normalComboxData)).size() > 2)
                        {
                           strText3 = (*(itr_2->second.sptr_normalComboxData)).at(2);
                        }
                     }
                     ((CBallColorBCGPGridCellItem *)pCell)->SetDisplayText(strText1,strText2,strText3);
                     ((CBallColorBCGPGridCellItem *)pCell)->SetColor(color1,color2,color3);
                  }
               }
               break;
				case CB_enum_FieldData_CString:
				default:
					{
						_bstr_t strValue = itr_2->second.strValue;
						if (itr_2->second.fieldCtrlType == CB_enum_FieldCtrl_Checkbox 
							|| itr_2->second.fieldCtrlType == CB_enum_FieldCtrl_Radio)
						{
							pRow->GetItem(nCol)->SetValue(
								(bool)(_ttoi(itr_2->second.strValue) != 0),FALSE);
						}
						else
						{
							pRow->GetItem(nCol)->SetValue(strValue,FALSE);
						}
					}
					break;
				}

				//单元格背景颜色
				if (itr_2->second.sptr_cellBackgroundClrVec.get())
				{
					vector<int>& vec_clr = *(itr_2->second.sptr_cellBackgroundClrVec);
					if (vec_clr.size() > 0)
					{
						pRow->GetItem(nCol)->SetBackgroundColor(vec_clr[0]);
					}
				}
			}
			//MY_OUTPUT_LOG_;
			m_pBCGGrid->AddRow(pRow, FALSE ); 
			
		}
		MY_OUTPUT_LOG_;
		m_pBCGGrid->EnableAlternateRows(TRUE);
		m_pBCGGrid->SetRedraw(TRUE);
		m_pBCGGrid->AdjustLayout();
		MY_OUTPUT_LOG_;      
		RefreshGridStatisticRow(m_pBCGGrid);		//放在adjustlayout后面，不然会奔溃情况
		MY_OUTPUT_LOG_;
	}

	return;
}

//		by WangZY 2018/06/06
BOOL CDlgBCGGrid::GetFilterFieldInfo(
   __out std::map<CString/*strFieldId*/,CString /*strFilter*/> &mapFilterInfo)
{
   BOOL bRet = FALSE;
   
   if (nullptr == m_pBCGGrid
      ||!IsWindow(m_pBCGGrid->GetSafeHwnd()))
   {
      return bRet;
   }

   int colCount = m_pBCGGrid->GetColumnsInfo().GetColumnCount();
   for (int i = 0; i < colCount; i++)
   {
      if (!m_pBCGGrid->GetColumnsInfo().GetColumnVisible(i))
      {
         continue;
      }

      auto pWnd = m_pBCGGrid->GetColumnsInfo().GetColumnFilterBarCtrl(i);
      if (pWnd != nullptr)
      {
         CString filterStr;
         pWnd->GetWindowText(filterStr);
         if (!filterStr.IsEmpty())
         {
            auto it = m_mapColWithFieldId.find(i);
            if (it != m_mapColWithFieldId.end())
            {
               mapFilterInfo[it->second] = filterStr;
            }
         }
      }
   }

   if (mapFilterInfo.size()>0)
   {
      bRet = TRUE;
   }

   return bRet;
}

BOOL CDlgBCGGrid::SetFilterFieldInfo(
   __in std::map<CString/*strFieldId*/,CString /*strFilter*/> &mapFilterInfo)
{
   BOOL bRet = FALSE;

   if (nullptr == m_pBCGGrid
      ||!IsWindow(m_pBCGGrid->GetSafeHwnd()))
   {
      return bRet;
   }

   for (auto it = mapFilterInfo.begin(); it != mapFilterInfo.end(); it++)
   {
      auto itt = m_mapColID.find(it->first);
      if (itt != m_mapColID.end())
      {
         if (!m_pBCGGrid->GetColumnsInfo().GetColumnVisible(itt->second))
            continue;

         auto pWnd = m_pBCGGrid->GetColumnsInfo().GetColumnFilterBarCtrl(itt->second);
         if (pWnd != nullptr)
         {
            pWnd->SetWindowText(it->second);

            bRet = TRUE;
         }
      }
   }

   return bRet;
}

//获取排序信息		by WangZY 2018/06/07
BOOL CDlgBCGGrid::GetSortFieldInfo(__out CString &strFieldId, __out BOOL &bAscening)
{
   BOOL bRet = FALSE;

   if (nullptr == m_pBCGGrid
      ||!IsWindow(m_pBCGGrid->GetSafeHwnd()))
   {
      return bRet;
   }
 
   int nCol = m_pBCGGrid->GetColumnsInfo().GetSortColumn();
   if (nCol<0)
   {
      return bRet;
   }

   int nState = m_pBCGGrid->GetColumnsInfo().GetColumnState(nCol);
   if (1==nState)
   {
      bAscening = TRUE;
   }
   else if (-1==nState)
   {
      bAscening = FALSE;
   }
   else
   {
      return bRet;
   }

   for (auto it=m_mapColID.begin(); it!=m_mapColID.end(); ++it)
   {
      if (it->second == nCol)
      {
         bRet = TRUE;
         strFieldId = it->first;

         break;
      }
   }

   return bRet;
}

//设置排序信息		by WangZY 2018/06/07
BOOL CDlgBCGGrid::SetSortFieldInfo(__in CString strFieldId, __in BOOL bAscening) 
{
   BOOL bRet = FALSE;

   if (nullptr == m_pBCGGrid
      ||!IsWindow(m_pBCGGrid->GetSafeHwnd()))
   {
      return bRet;
   }

   auto it = m_mapColID.find(strFieldId);
   if (it!=m_mapColID.end())
   {
      m_pBCGGrid->SetSortColumn(it->second,bAscening);
      bRet = TRUE;
   }
   
   return bRet;
}

//获取必需打包的数据字段			by WangZY 2018/02/01
BOOL CDlgBCGGrid::GetNeedfulPackageFieldId(
	__out std::vector<CString/*strFieldId*/> &vecFieldId,
	__in BOOL bNewCreate/* = FALSE*/)
{
	if (bNewCreate)
	{
		m_vecNeedfulPackageFieldId.clear();
	}

   if (m_vecNeedfulPackageFieldId.size()<=0)
   {
      CreateNeedfulPackageFieldId();
   }
		
	if (m_vecNeedfulPackageFieldId.size()>0)
   {
      vecFieldId = m_vecNeedfulPackageFieldId;
		return TRUE;
   }	
      
	return FALSE;
}

//获取网格上最后一行数据的数据索引
BOOL CDlgBCGGrid::GetLastRowIndex(__out int &nIndex)
{
	nIndex = m_pBCGGrid->GetRowCount()-1;
	int nRowCounts = m_pBCGGrid->GetRowCount()-1;
	while(nRowCounts >= 0)
	{	
		if (m_pBCGGrid->IsRowVisible(m_pBCGGrid->GetRow(nRowCounts)))
      {
         MAP_GridCtrl_RowData* p_data = (MAP_GridCtrl_RowData*)m_pBCGGrid->GetRow(nRowCounts)->GetData();
         for (auto itr_data = m_tableData.rbegin();itr_data != m_tableData.rend(); ++itr_data)
         {
            if (&(itr_data->second) == p_data)
            {
               nIndex = itr_data->first;
               return TRUE;
            }
         }
        
		}
		--nRowCounts;
	}
	return FALSE;
}

int CDlgBCGGrid::GetSelectData(__out MAP_GridCtrl_AllData &mapSelectData)
{
	if (NULL == m_pBCGGrid || !IsWindow(m_pBCGGrid->GetSafeHwnd()))
		return FALSE;

	int nSelCounts = 0;
	mapSelectData.clear();

	const int nRowCounts = m_pBCGGrid->GetRowCount();			//行数
	const int nColCounts = m_pBCGGrid->GetColumnCount();		//列数

	CBCGPGridRow* pRow = NULL;
	if (!m_bUserPaginationMode
      ||(m_bUserPaginationMode&&emPM_DbSvr==m_emPMPaginationModeFlag))
	{
		if (m_tableAttri.isMultiRowSelect)		//多行选择
		{
			for (int iRow = 0; iRow < nRowCounts; ++iRow)
			{
				pRow = m_pBCGGrid->GetRow(iRow);
				if (pRow)
				{
					if (pRow->GetCheck() == 1)
					{
						++nSelCounts;
						DWORD_PTR ptr = pRow->GetData();
						MAP_GridCtrl_RowData dataRow = *((MAP_GridCtrl_RowData*)ptr);
						mapSelectData.insert(MAP_GridCtrl_AllData::value_type(iRow,dataRow));
					}
				}
			}
		}
		else		//单行选择
		{
			pRow = m_pBCGGrid->GetCurSel();
			if (pRow)
			{
				if (pRow->GetRowId() > -1)
				{
					DWORD_PTR ptr = pRow->GetData();
					MAP_GridCtrl_RowData dataRow = *((MAP_GridCtrl_RowData*)ptr);
					mapSelectData.insert(MAP_GridCtrl_AllData::value_type(pRow->GetRowId(),dataRow));
					nSelCounts = 1;
				}
			}
		}
	}
	else
	{
		if (m_tableAttri.isMultiRowSelect)		//多行选择
		{
			for (int iRow = 0; iRow < nRowCounts; ++iRow)
			{
				pRow = m_pBCGGrid->GetRow(iRow);
				if (pRow)
				{
					if (pRow->GetCheck() == 1)
					{
						++nSelCounts;
						MAP_GridCtrl_RowData dataRow;
						for (int nCol=0;nCol<nColCounts;++nCol)
						{
							CString strValue = pRow->GetItem(nCol)->FormatItem();
							auto it = m_mapColWithFieldId.find(nCol);
							if (it!= m_mapColWithFieldId.end())
							{
								CString strFieldId = it->second;
								S_GridCtrl_FieldData data;
								data.strValue = strValue;
								dataRow.insert(MAP_GridCtrl_RowData::value_type(strFieldId,data));
							}
						}
						mapSelectData.insert(MAP_GridCtrl_AllData::value_type(iRow,dataRow));
					}
				}
			}
		}
		else		//单行选择
		{
			pRow = m_pBCGGrid->GetCurSel();
			if (pRow)
			{
				if (pRow->GetRowId() > -1)
				{
					MAP_GridCtrl_RowData dataRow;
					for (int nCol=0;nCol<nColCounts;++nCol)
					{
						CString strValue = pRow->GetItem(nCol)->FormatItem();
						auto it = m_mapColWithFieldId.find(nCol);
						if (it!= m_mapColWithFieldId.end())
						{
							CString strFieldId = it->second;
							S_GridCtrl_FieldData data;
							data.strValue = strValue;
							dataRow.insert(MAP_GridCtrl_RowData::value_type(strFieldId,data));
						}
					}
					mapSelectData.insert(MAP_GridCtrl_AllData::value_type(pRow->GetRowId(),dataRow));
					nSelCounts = 1;
				}
			}
		}
	}
	

	return nSelCounts;
}

int CDlgBCGGrid::GetShowData(__out MAP_GridCtrl_AllData &mapShowData)
{
	if (NULL == m_pBCGGrid || !IsWindow(m_pBCGGrid->GetSafeHwnd()))
		return -1;

	CBCGPGridRow* pRow = NULL;
	const int nRowCounts = m_pBCGGrid->GetRowCount();
	for (int iRow = 0; iRow < nRowCounts; ++iRow)
	{
		pRow = m_pBCGGrid->GetRow(iRow);
		if (pRow && m_pBCGGrid->IsRowVisible(pRow))		//判断行是否示显
		{
			DWORD_PTR ptr = pRow->GetData();
			mapShowData.insert(make_pair(iRow,*(MAP_GridCtrl_RowData*)ptr));
		}
	}
	return nRowCounts;

	return 0;
}

int CDlgBCGGrid::GetShowDataIndex(__out std::vector<int/*dataIndex*/> &vecShowIndex)
{
	if (NULL == m_pBCGGrid || !IsWindow(m_pBCGGrid->GetSafeHwnd()))
		return 0;
	vecShowIndex.clear();
	const int nRowCounts = m_pBCGGrid->GetRowCount();
	CBCGPGridRow* pRow = NULL;
	for (int iRow = 0; iRow < nRowCounts; ++iRow)
	{
		pRow = m_pBCGGrid->GetRow(iRow);
		if (m_pBCGGrid->IsRowVisible(pRow))
		{
			MAP_GridCtrl_RowData& row_data = *(MAP_GridCtrl_RowData*)pRow->GetData();
			for (auto itr_data = m_tableData.begin(); itr_data != m_tableData.end(); ++itr_data)
			{
				if (&itr_data->second == &row_data)
				{
					vecShowIndex.push_back(itr_data->first);
				}
			}	
		}
	}
	return vecShowIndex.size();
}

int CDlgBCGGrid::GetShowDataSelIndex(__out std::vector<int/*dataIndex*/> &vecShowSelIndex)
{
	if (NULL == m_pBCGGrid || !IsWindow(m_pBCGGrid->GetSafeHwnd()))
		return 0;
	vecShowSelIndex.clear();
	const int nRowCounts = m_pBCGGrid->GetRowCount();
	CBCGPGridRow* pRow = NULL;
	for (int iRow = 0; iRow < nRowCounts; ++iRow)
	{
		pRow = m_pBCGGrid->GetRow(iRow);
		if (m_pBCGGrid->IsRowVisible(pRow) && pRow->GetCheck() == 1)
		{
			MAP_GridCtrl_RowData& row_data = *(MAP_GridCtrl_RowData*)pRow->GetData();
			for (auto itr_data = m_tableData.begin(); itr_data != m_tableData.end(); ++itr_data)
			{
				if (&itr_data->second == &row_data)
				{
					vecShowSelIndex.push_back(itr_data->first);
				}
			}	
		}
	}
	return vecShowSelIndex.size();
}

int CDlgBCGGrid::GetSelectDataIndex(__out std::vector<int/*dataIndex*/> &vecSelectIndex)
{
	if (NULL == m_pBCGGrid || !IsWindow(m_pBCGGrid->GetSafeHwnd()))
		return -1;
	vecSelectIndex.clear();
	const int nRowCounts = m_pBCGGrid->GetRowCount();
	if (m_tableAttri.isMultiRowSelect)		//多行选择
	{
		CBCGPGridRow* pRow = nullptr;
		for (int iRow = 0; iRow < nRowCounts; ++iRow)
		{
			pRow = m_pBCGGrid->GetRow(iRow);
			if (nullptr != pRow
				&&pRow->GetCheck()
				&&m_pBCGGrid->IsRowVisible(pRow))
			{
				MAP_GridCtrl_RowData& row_data = *(MAP_GridCtrl_RowData*)m_pBCGGrid->GetRow(iRow)->GetData();
				for (auto itr_data = m_tableData.begin(); itr_data != m_tableData.end(); ++itr_data)
				{
					if (&itr_data->second == &row_data)
					{
						vecSelectIndex.push_back(itr_data->first);
					}
				}	
			}
		}
	}
	else	//单行选择模式
	{
		CBCGPGridRow* pRow = NULL;
		pRow = m_pBCGGrid->GetCurSel();
		if (pRow)
		{
			if (pRow->GetRowId() > -1)
			{
				MAP_GridCtrl_RowData& row_data = *(MAP_GridCtrl_RowData*)pRow->GetData();
				for (auto itr_data = m_tableData.begin(); itr_data != m_tableData.end(); ++itr_data)
				{
					if (&itr_data->second == &row_data)
					{
						vecSelectIndex.push_back(itr_data->first);
					}
				}	
			}
		}
	}
	return vecSelectIndex.size();
}

int CDlgBCGGrid::GetSelectDataIndex()
{
	if (NULL == m_pBCGGrid || !IsWindow(m_pBCGGrid->GetSafeHwnd()))
		return -1;

	CBCGPGridRow* pRow = NULL;
	pRow = m_pBCGGrid->GetCurSel();
	if (pRow)
	{
		if (pRow->GetRowId() > -1)
		{
			MAP_GridCtrl_RowData& row_data = *(MAP_GridCtrl_RowData*)pRow->GetData();
			for (auto itr_data = m_tableData.begin(); itr_data != m_tableData.end(); ++itr_data)
			{
				if (&itr_data->second == &row_data)
				{
					return itr_data->first;
				}
			}	
		}
	}
	return -1;
}

int CDlgBCGGrid::GetSelectRowNo(__out std::vector<int/*rowIndex*/> &vecSelectIndex)
{
	if (NULL == m_pBCGGrid || !IsWindow(m_pBCGGrid->GetSafeHwnd()))
		return -1;

	vecSelectIndex.clear();

	const int nRowCounts = m_pBCGGrid->GetRowCount();
	CBCGPGridRow* pRow = NULL;
	if (m_tableAttri.isMultiRowSelect)		//多行选择
	{
		for (int iRow = 0; iRow < nRowCounts; ++iRow)
		{
			pRow = m_pBCGGrid->GetRow(iRow);
			if (pRow)
			{
				if (pRow->GetCheck()
					&&m_pBCGGrid->IsRowVisible(pRow)	)
				{
					vecSelectIndex.push_back(iRow);
				}
			}
		}
	}
	else	//单行选择模式
	{
		pRow = m_pBCGGrid->GetCurSel();
		if (pRow)
		{
			if (pRow->GetRowId() > -1)
			{
				vecSelectIndex.push_back(pRow->GetRowId());
			}
		}
	}

	return vecSelectIndex.size();
}

BOOL CDlgBCGGrid::GetRowIndexofDataInfo(__out int &nDataRowIndex, __in int nGridRow)
{
	BOOL bRet = FALSE;

	nDataRowIndex = -1;

	if (NULL == m_pBCGGrid 
		|| !IsWindow(m_pBCGGrid->GetSafeHwnd()))
	{
		return bRet;
	}
	if (nGridRow<0)
	{
		return FALSE;
	}

	const int nRowCounts = m_pBCGGrid->GetRowCount();
	if (nGridRow < nRowCounts)
	{
		CBCGPGridRow* pRow = m_pBCGGrid->GetRow(nGridRow);
		if (pRow)
		{
			DWORD_PTR ptr = pRow->GetData();
			for (auto itr_ = m_tableData.begin(); itr_ != m_tableData.end(); ++itr_)
			{
				if ((MAP_GridCtrl_RowData*)ptr == &itr_->second)
				{
					nDataRowIndex = itr_->first;
					bRet =  TRUE;
					break;
				}
			}
		}
	}

	return bRet;
}

BOOL CDlgBCGGrid::GetRowIndexofDataInfo(__out MAP_GridCtrl_RowData& data_row, __in int nGridRow)
{
	BOOL bRet = FALSE;

	if (NULL == m_pBCGGrid 
		|| !IsWindow(m_pBCGGrid->GetSafeHwnd()))
	{
		return bRet;
	}
	if (nGridRow<0)
	{
		return FALSE;
	}

	const int nRowCounts = m_pBCGGrid->GetRowCount();
	if (nGridRow < nRowCounts)
	{
		CBCGPGridRow* pRow = m_pBCGGrid->GetRow(nGridRow);
		if (pRow)
		{
			data_row = *(MAP_GridCtrl_RowData*)(pRow->GetData());
			bRet = TRUE;
		}
	}

	return bRet;
}

BOOL CDlgBCGGrid::GetValueByGridRowAndCol(__out CString &strValue,
	__in int nGridRow,__in int nGridCol)
{
	if (NULL == m_pBCGGrid 
		|| !IsWindow(m_pBCGGrid->GetSafeHwnd()))
	{
		return FALSE;
	}
	if (nGridRow<0
		||nGridCol<0)
	{
		return FALSE;
	}

	const int nRowCounts = m_pBCGGrid->GetRowCount();
	if (nGridRow < nRowCounts)
	{
		CBCGPGridRow* pRow = NULL;
		for (int irow =0; irow < nRowCounts; ++irow)
		{
			pRow = m_pBCGGrid->GetRow(irow);
			if (pRow && m_pBCGGrid->IsRowVisible(pRow) && pRow->GetRowId() == nGridRow)
			{
				strValue = pRow->GetItem(nGridCol)->FormatItem();
				//_bstr_t bstrValue = pRow->GetItem(nGridCol)->GetValue();
				//strValue = (LPCTSTR)bstrValue;
				break;
			}
		}
	}
	return TRUE;
}

BOOL CDlgBCGGrid::GetValueByGridRowAndCol(__out S_GridCtrl_FieldData &data,__in int nGridRow, __in int nGridCol)
{
	if (NULL == m_pBCGGrid 
		|| !IsWindow(m_pBCGGrid->GetSafeHwnd()))
	{
		return FALSE;
	}
	if (nGridRow<0
		||nGridCol<0)
	{
		return FALSE;
	}

	CString strFiledID = _T("");
	for (auto itr_col = m_mapColID.begin(); itr_col != m_mapColID.end(); ++itr_col)
	{
		if (itr_col->second == nGridCol)
		{
			strFiledID = itr_col->first;
			break;
		}
	}

	if (strFiledID.IsEmpty())
	{
		return FALSE;
	}

	const int nRowCounts = m_pBCGGrid->GetRowCount();
	if (nGridRow < nRowCounts)
	{
		CBCGPGridRow* pRow = m_pBCGGrid->GetRow(nGridRow);
		if (pRow && pRow->GetRowId() == nGridRow)
		{
			MAP_GridCtrl_RowData& data_row = *(MAP_GridCtrl_RowData*)(pRow->GetData());
			auto itr_value = data_row.find(strFiledID);
			if (itr_value != data_row.end())
			{
				data = itr_value->second;
			}
		}
		else
		{
			for (int i=0; i< nRowCounts; ++i)
			{
				pRow = m_pBCGGrid->GetRow(i);
				if (pRow && pRow->GetRowId() == nGridRow)
				{
					MAP_GridCtrl_RowData& data_row = *(MAP_GridCtrl_RowData*)(pRow->GetData());
					auto itr_value = data_row.find(strFiledID);
					if (itr_value != data_row.end())
					{
						data = itr_value->second;
					}
					break;
				}
			}
		}
	}
	return TRUE;
}

BOOL CDlgBCGGrid::GetValueByGridRowAndFieldId(__out CString &strValue,
	__in int nGridRow,__in CString strFieldId)
{
	BOOL bRet = FALSE;

	if (NULL == m_pBCGGrid 
		|| !IsWindow(m_pBCGGrid->GetSafeHwnd()))
	{
		return bRet;
	}

	const int nRowCounts = m_pBCGGrid->GetRowCount();
	//使用分页模式下的处理		by WangZY 2018/01/13
	if (m_bUserPaginationMode
      &&emPM_Local==m_emPMPaginationModeFlag)
	{
		if (nGridRow<nRowCounts)
		{
			CBCGPGridRow* pRow = m_pBCGGrid->GetRow(nGridRow);
			if (pRow)
			{
				int nCol = 0;
				auto it=m_mapColID.find(strFieldId);
				if (it==m_mapColID.end())
				{
					return bRet;
				}
				
				nCol = it->second;	
				
				strValue =  pRow->GetItem(nCol)->FormatItem();
				bRet = TRUE;
			}
		}

		return bRet;
	}

	//非分页模式		by WangZY 2018/01/13
	if (nGridRow < nRowCounts)
	{
		CBCGPGridRow* pRow = m_pBCGGrid->GetRow(nGridRow);
		if (pRow && pRow->GetRowId() == nGridRow)
		{
			MAP_GridCtrl_RowData *pdata_row = (MAP_GridCtrl_RowData*)(pRow->GetData());
			if (pdata_row == NULL)
			{
				return FALSE;
			}
			MAP_GridCtrl_RowData &data_row = *pdata_row;
			auto itr_value = data_row.find(strFieldId);
			if (itr_value != data_row.end())
			{
				strValue = itr_value->second.strValue;
				//检验内存数据和界面数据是否一致，不一致则使用界面数据
				auto itr_col = m_mapColID.find(strFieldId);
				if (itr_col != m_mapColID.end())
				{
					_bstr_t bstrValue = pRow->GetItem(itr_col->second)->GetValue();
					CString strTempValude = (LPCTSTR)bstrValue;
					if (strTempValude != strValue)
					{
						strValue = strTempValude;
						 itr_value->second.strValue = strTempValude;
					}
				}
			}

			bRet = TRUE;
		}
		else
		{
			for (int i=0; i< nRowCounts; ++i)
			{
				pRow = m_pBCGGrid->GetRow(i);
				if (pRow && pRow->GetRowId() == nGridRow)
				{
					MAP_GridCtrl_RowData& data_row = *(MAP_GridCtrl_RowData*)(pRow->GetData());
					auto itr_value = data_row.find(strFieldId);
					if (itr_value != data_row.end())
					{
						strValue = itr_value->second.strValue;
						//检验内存数据和界面数据是否一致，不一致则使用界面数据
						auto itr_col = m_mapColID.find(strFieldId);
						if (itr_col != m_mapColID.end())
						{
							_bstr_t bstrValue = pRow->GetItem(itr_col->second)->GetValue();
							CString strTempValude = (LPCTSTR)bstrValue;
							if (strTempValude != strValue)
							{
								strValue = strTempValude;
								itr_value->second.strValue = strTempValude;
							}
						}
					}

					bRet = TRUE;
					break;
				}
			}
		}
	}

	return bRet;
}

BOOL CDlgBCGGrid::GetValueByGridRowAndFieldId(__out S_GridCtrl_FieldData &data,__in int nGridRow, __in CString strFieldId)
{
	BOOL bRet = FALSE;

	if (NULL == m_pBCGGrid || !IsWindow(m_pBCGGrid->GetSafeHwnd()))
		return bRet;

	const int nRowCounts = m_pBCGGrid->GetRowCount();
	if (nGridRow < nRowCounts)
	{
		CBCGPGridRow* pRow = m_pBCGGrid->GetRow(nGridRow);
		if (pRow && pRow->GetRowId() == nGridRow)
		{
			MAP_GridCtrl_RowData& data_row = *(MAP_GridCtrl_RowData*)(pRow->GetData());
			auto itr_value = data_row.find(strFieldId);
			if (itr_value != data_row.end())
			{
				data = itr_value->second;
			}
			bRet = TRUE;
		}
		else
		{
			for (int i=0; i< nRowCounts; ++i)
			{
				pRow = m_pBCGGrid->GetRow(nGridRow);
				if (pRow && pRow->GetRowId() == nGridRow)
				{
					MAP_GridCtrl_RowData& data_row = *(MAP_GridCtrl_RowData*)(pRow->GetData());
					auto itr_value = data_row.find(strFieldId);
					if (itr_value != data_row.end())
					{
						data = itr_value->second;
					}
					bRet = TRUE;
					break;
				}
			}
		}
	}

	return bRet;
}

BOOL CDlgBCGGrid::GetValuebyFieldIdAndValue(__in CString strFieldId,
	__in CString strValue,__in CString strTarField,__out CString& strTarValue)
{
	BOOL bRet = FALSE;

	if (NULL == m_pBCGGrid 
		|| !IsWindow(m_pBCGGrid->GetSafeHwnd()))
	{
		return bRet;
	}
	//使用分页模式		by WangZY 2018/01/13
	if (m_bUserPaginationMode
      &&emPM_Local==m_emPMPaginationModeFlag)
	{
		try
		{
			//CString strFind;
			//strFind.Format(_T("%s='%s'"),strFieldId,strValue);

			//auto Bookmark = m_dbRecordSetPtr->Bookmark;
			//auto it = m_dbRecordSetPtr->Find(strFind.GetBuffer(0),0,adSearchForward);
			//_bstr_t bstrValue = m_dbRecordSetPtr->GetCollect((LPCTSTR)strTarField);
			//strValue = (LPCTSTR)bstrValue;
			////m_dbRecordSetPtr->Bookmark = Bookmark;
			//m_dbRecordSetPtr->Move(0,Bookmark);

			//bRet = TRUE;
		}
		catch (CMemoryException* e)
		{
			TCHAR   szError[1024];   
			e->GetErrorMessage(szError,1024); 
			CString strDes = szError;
		}
		catch (CFileException* e)
		{
			TCHAR   szError[1024];   
			e->GetErrorMessage(szError,1024); 
			CString strDes = szError;
		}
		catch (_com_error& e)
		{
			CString strDes = e.Description();
			//MessageBox(NULL,strDes,_T("数据库异常"),MB_ICONERROR);
			CString strMsg = _T("");

		}
		catch (CException* e)
		{
			TCHAR   szError[1024];   
			e->GetErrorMessage(szError,1024); 
			CString strDes = szError;
		}
		catch (...)
		{
		
		}
		

		return bRet;
	}

	//非使用分页模式		by WangZY 2018/01/13
	for (auto itr_row = m_tableData.begin(); itr_row != m_tableData.end(); ++itr_row)
	{
		auto itr_data_scr = itr_row->second.find(strFieldId);
		auto itr_data_tar = itr_row->second.find(strTarField);
		if (itr_data_scr != itr_row->second.end() && itr_data_tar != itr_row->second.end())
		{
			if (itr_data_scr->second.strValue == strValue)
			{
				strTarValue = itr_data_tar->second.strValue;
				bRet = TRUE;
				break;
			}
		}
	}

	return bRet;
}

BOOL CDlgBCGGrid::GetPrintDataXmlText(__out CString &strFieldXml,
	__out CString &strDataXml,__out CString &strStatisticRowXml)
{
	BOOL bField = CreatePrintFieldXml(strFieldXml);
	if (!bField)
	{
		return FALSE;
	}
	BOOL bData = FALSE;
	if (m_bUserPaginationMode
      &&emPM_Local==m_emPMPaginationModeFlag)
	{
		bData = CreateUsedPaginationModePrintDataXml(strDataXml);
	}
	else
	{
		bData = CreatePrintDataXml(strDataXml);
	}
	
	BOOL bTotal = CreatePrintStatisticRowXml(strStatisticRowXml);

	return TRUE;
}

//内部用的接口,千万不要改外用:设置Cell的item的值		by WangZY 2018/02/01		by WangZY 2018/02/01
BOOL CDlgBCGGrid::_in_SetGridItemValue(__in CBCGPGridItem *pItem,
	__in CString &strValue)
{
	if (nullptr == pItem)
	{
		return FALSE;
	}

	_variant_t vValue = pItem->GetValue();
	switch(vValue.vt)
	{
	case VT_UI1:
	case VT_I2:
	case VT_I4:
	case VT_BOOL:
		{
			long lValue = _ttoi(strValue);
			pItem->SetValue(lValue);
		}		
		break;
	case VT_R4:
	case VT_R8:
		{
			double dValue = _ttof(strValue);
			pItem->SetValue(dValue);
		}			
		break;
	case VT_EMPTY:
	case VT_NULL:
	default:
		{
			_bstr_t bstrValue = _bstr_t(strValue);
			pItem->SetValue(bstrValue);
		}		
		break;
	}

	return TRUE;
}

//生成必需打包的数据字段		by WangZY 2018/02/01
BOOL CDlgBCGGrid::CreateNeedfulPackageFieldId()
{
	m_vecNeedfulPackageFieldId.clear();
	for (auto it=m_tableAttri.mapFeildAtrri.begin();
		it!=m_tableAttri.mapFeildAtrri.end(); ++it)
	{
		if (it->second.isShow)
		{
			m_vecNeedfulPackageFieldId.push_back(it->first);
		}
		
	}

	for (auto itNeed=m_vecNeedfulFieldId.begin();
		itNeed!=m_vecNeedfulFieldId.end(); ++itNeed)
	{
		auto itFind = std::find(m_vecNeedfulPackageFieldId.begin(),
			m_vecNeedfulPackageFieldId.end(),*itNeed);
		if (itFind != m_vecNeedfulPackageFieldId.end())
		{
			continue;
		}
		m_vecNeedfulPackageFieldId.push_back(*itNeed);
	}

	return TRUE;
}

BOOL CDlgBCGGrid::CreatePrintFieldXml(__out CString &strFieldXml)
{
	if (nullptr == m_pBCGGrid || !IsWindow(m_pBCGGrid->GetSafeHwnd()))
		return FALSE;

	CString strRet = _T("");

	try
	{
		//const int nRowCounts = m_pBCGGrid->GetRowCount();		//行数
		//const int nColCounts = m_pBCGGrid->GetColumnCount();	//列数
		//const int nFrozenColCounts = m_pBCGGrid->GetColumnsInfo().GetFrozenColumnCount();	//冰冻列数

		//if (nColCounts - nFrozenColCounts <= 0 || nRowCounts <= 0)
		//{
		//	return FALSE;		//无数据
		//}	

		//创建一个XML的文档对象。
		TiXmlDocument *myDocument =new TiXmlDocument();

		//建立描述节点，设置了版本和字符编码，并添加到top节点
		TiXmlDeclaration* declaration = new TiXmlDeclaration("1.0", "UTF-8", "yes");
		if(!declaration)
		{
			return FALSE;
		}

		myDocument->LinkEndChild(declaration);

		//创建一个根元素并连接。
		TiXmlElement *RootElement =new TiXmlElement("GridDataSet");
		myDocument->LinkEndChild(RootElement);

		TiXmlElement *pElementChild = new TiXmlElement("dt1");
		RootElement->LinkEndChild(pElementChild);

		TiXmlElement *pElementAttri = new TiXmlElement("dt1");
		RootElement->LinkEndChild(pElementAttri);
		
		vector<int > vecShowCol;
		GetShowColID(vecShowCol);
		for (int index =0; index < vecShowCol.size(); ++index)
		{
			int iColWidth = m_pBCGGrid->GetColumnWidth(vecShowCol[index]);

			CString strColShowName = m_pBCGGrid->GetColumnName(vecShowCol[index]);	//获取表格列显示的名称
			CString strColShowID = m_pBCGGrid->GetColumnName(vecShowCol[index]);	//获取表格列显示的名称
			auto itr_col_id = m_mapColWithFieldId.find(vecShowCol[index]);
			if (itr_col_id != m_mapColWithFieldId.end())
			{
				strColShowID = itr_col_id->second;			//数据库字段
			}

			//添加FieldID
			string strId = RnString::UNICODE_TO_UTF8(strColShowID);
			TiXmlElement *pElementID = new TiXmlElement(strId.c_str());
			pElementChild->LinkEndChild(pElementID);
			CGridCtrlTableAttributeOp::LinkCStringValueToElement(strColShowName,pElementID);

			TiXmlElement *pElementWidth = new TiXmlElement(strId.c_str());
			pElementAttri->LinkEndChild(pElementWidth);
			CGridCtrlTableAttributeOp::LinkIntValueToElement(iColWidth,pElementWidth);
		}

		TiXmlPrinter xmlPrint;
		myDocument->Accept(&xmlPrint);

		string strTmp = xmlPrint.CStr();
		myDocument->Clear();
		delete myDocument;//2017/06/06  释放内存

		strRet = RnString::UTF8_TO_UNICODE(strTmp);
		strFieldXml = strRet;
		//strRet = strTmp.c_str();

		return TRUE;
	}
	catch(string& e)
	{
		CString strException = RnString::UTF8_TO_UNICODE(e);
		AfxMessageBox(strException);

		return FALSE;
	}

	return TRUE;
}

BOOL CDlgBCGGrid::CreatePrintDataXml(__out CString &strDataXml)
{
	if (nullptr == m_pBCGGrid 
		|| !IsWindow(m_pBCGGrid->GetSafeHwnd()))
	{
		return FALSE;
	}

	CString strRet = _T("");
	try
	{
		const int nRowCounts = m_pBCGGrid->GetRowCount();		//行数
		const int nColCounts = m_pBCGGrid->GetColumnCount();	//列数
		const int nFrozenColCounts = m_pBCGGrid->GetColumnsInfo().GetFrozenColumnCount();	//冰冻列数

		if (nRowCounts <= 0 || nColCounts <= 0 
			|| nColCounts - nFrozenColCounts <= 0)
			return FALSE;

		//创建一个XML的文档对象。
		TiXmlDocument *myDocument =new TiXmlDocument();

		//建立描述节点，设置了版本和字符编码，并添加到top节点
		TiXmlDeclaration* declaration = new TiXmlDeclaration("1.0", "UTF-8", "yes");
		if(!declaration)
		{
			return FALSE;
		}
		myDocument->LinkEndChild(declaration);

		//创建一个根元素并连接。
		TiXmlElement *RootElement =new TiXmlElement("GridDataSet");
		myDocument->LinkEndChild(RootElement);
	
		CBCGPGridRow* pRow = NULL;

		if (m_tableAttri.isMultiRowSelect)		//多行选择
		{
			for (int iRow =0; iRow < nRowCounts; ++iRow)
			{
				pRow = m_pBCGGrid->GetRow(iRow);
				if (pRow)
				{
					if (pRow->GetCheck() == 1)
					{
						TiXmlElement *pElementChild = new TiXmlElement("dt1");
						RootElement->LinkEndChild(pElementChild);
						MAP_GridCtrl_RowData map_row_data = *(MAP_GridCtrl_RowData*)(pRow->GetData());		//行数据集合
						for (auto itr_row = map_row_data.begin(); itr_row != map_row_data.end(); ++itr_row)
						{
							CString strFieldId = itr_row->first;
							CString strValue = itr_row->second.strValue;

							//添加FieldID
							string strId = RnString::UNICODE_TO_UTF8(strFieldId);
							TiXmlElement *pElementID = new TiXmlElement(strId.c_str());
							pElementChild->LinkEndChild(pElementID);
							CGridCtrlTableAttributeOp::LinkCStringValueToElement(strValue,pElementID);
						}
					}
				}
			}
		}
		else
		{
			for (int iRow =0; iRow < nRowCounts; ++iRow)
			{
				pRow = m_pBCGGrid->GetRow(iRow);
				if (pRow && m_pBCGGrid->IsRowVisible(pRow))
				{
					TiXmlElement *pElementChild = new TiXmlElement("dt1");
					RootElement->LinkEndChild(pElementChild);
					MAP_GridCtrl_RowData map_row_data = *(MAP_GridCtrl_RowData*)(pRow->GetData());		//行数据集合
					for (auto itr_row = map_row_data.begin(); itr_row != map_row_data.end(); ++itr_row)
					{
						CString strFieldId = itr_row->first;
						CString strValue = itr_row->second.strValue;

						//添加FieldID
						string strId = RnString::UNICODE_TO_UTF8(strFieldId);
						TiXmlElement *pElementID = new TiXmlElement(strId.c_str());
						pElementChild->LinkEndChild(pElementID);
						CGridCtrlTableAttributeOp::LinkCStringValueToElement(strValue,pElementID);
					}
				}
			}
		}

		TiXmlPrinter xmlPrint;
		myDocument->Accept(&xmlPrint);

		string strTmp = xmlPrint.CStr();
		myDocument->Clear();
		delete myDocument;//2017/06/06  释放内存

		strRet = RnString::UTF8_TO_UNICODE(strTmp);
		strDataXml = strRet;

		return TRUE;
	}
	catch(string& e)
	{
		CString strException = RnString::UTF8_TO_UNICODE(e);
		AfxMessageBox(strException);

		return FALSE;
	}

	return TRUE;
}

//打包分页模式下生成数据行的打印需要xml信息		by WangZY 2018/01/19
BOOL CDlgBCGGrid::CreateUsedPaginationModePrintDataXml(__out CString &strDataXml)
{
	if (nullptr == m_pBCGGrid 
		|| !IsWindow(m_pBCGGrid->GetSafeHwnd()))
	{
		return FALSE;
	}

	CString strRet = _T("");
	try
	{
		const int nRowCounts = m_pBCGGrid->GetRowCount();		//行数
		const int nColCounts = m_pBCGGrid->GetColumnCount();	//列数
		const int nFrozenColCounts = m_pBCGGrid->GetColumnsInfo().GetFrozenColumnCount();	//冰冻列数

		if (nRowCounts <= 0 || nColCounts <= 0 
			|| nColCounts - nFrozenColCounts < 0)
			return FALSE;

		//创建一个XML的文档对象。
		TiXmlDocument *myDocument =new TiXmlDocument();

		//建立描述节点，设置了版本和字符编码，并添加到top节点
		TiXmlDeclaration* declaration = new TiXmlDeclaration("1.0", "UTF-8", "yes");
		if(!declaration)
		{
			return FALSE;
		}
		myDocument->LinkEndChild(declaration);

		//创建一个根元素并连接。
		TiXmlElement *RootElement =new TiXmlElement("GridDataSet");
		myDocument->LinkEndChild(RootElement);

		CBCGPGridRow* pRow = NULL;

		if (m_tableAttri.isMultiRowSelect)		//多行选择
		{
			for (int iRow =0; iRow < nRowCounts; ++iRow)
			{
				pRow = m_pBCGGrid->GetRow(iRow);
				if (pRow)
				{
					if (pRow->GetCheck() == 1)
					{
						TiXmlElement *pElementChild = new TiXmlElement("dt1");
						RootElement->LinkEndChild(pElementChild);
						
						for (auto it=m_mapColWithFieldId.begin(); it!=m_mapColWithFieldId.end(); ++it)
						{
							CString strFieldId = it->second;
							int nCol = it->first;
							CString strValue = pRow->GetItem(nCol)->FormatItem();
							if (strValue.IsEmpty())
							{
								continue;
							}

							//添加FieldID
							string strId = RnString::UNICODE_TO_UTF8(strFieldId);
							TiXmlElement *pElementID = new TiXmlElement(strId.c_str());
							pElementChild->LinkEndChild(pElementID);
							CGridCtrlTableAttributeOp::LinkCStringValueToElement(strValue,pElementID);
						}
					}
				}
			}
		}
		else
		{
			for (int iRow =0; iRow < nRowCounts; ++iRow)
			{
				pRow = m_pBCGGrid->GetRow(iRow);
				if (pRow && m_pBCGGrid->IsRowVisible(pRow))
				{
					TiXmlElement *pElementChild = new TiXmlElement("dt1");
					RootElement->LinkEndChild(pElementChild);

					for (auto it=m_mapColWithFieldId.begin(); it!=m_mapColWithFieldId.end(); ++it)
					{
						CString strFieldId = it->second;
						int nCol = it->first;
						CString strValue = pRow->GetItem(nCol)->FormatItem();
						if (strValue.IsEmpty())
						{
							continue;
						}

						//添加FieldID
						string strId = RnString::UNICODE_TO_UTF8(strFieldId);
						TiXmlElement *pElementID = new TiXmlElement(strId.c_str());
						pElementChild->LinkEndChild(pElementID);
						CGridCtrlTableAttributeOp::LinkCStringValueToElement(strValue,pElementID);
					}
				}
			}
		}

		TiXmlPrinter xmlPrint;
		myDocument->Accept(&xmlPrint);

		string strTmp = xmlPrint.CStr();
		myDocument->Clear();
		delete myDocument;//2017/06/06  释放内存

		strRet = RnString::UTF8_TO_UNICODE(strTmp);
		strDataXml = strRet;

		return TRUE;
	}
	catch(string& e)
	{
		CString strException = RnString::UTF8_TO_UNICODE(e);
		AfxMessageBox(strException);

		return FALSE;
	}

	return TRUE;
}

BOOL CDlgBCGGrid::CreatePrintStatisticRowXml(__out CString &strStatisticRowXml)
{
	if (nullptr == m_pBCGGrid  
		|| !IsWindow(m_pBCGGrid->GetSafeHwnd()))
	{
		return FALSE;
	}
	CString strRet = _T("");

	try
	{
		if (!m_pBCGGrid->GetColumnsInfo().IsEnableShowFooterRow())
		{
			return FALSE;
		}

		int nColCount = m_pBCGGrid->GetColumnCount();
		int nRowCount = m_pBCGGrid->GetRowCount();

		if (nRowCount <=0
			||nColCount<=0)
		{
			return FALSE;
		}

		//创建一个XML的文档对象。
		TiXmlDocument *myDocument =new TiXmlDocument();

		//建立描述节点，设置了版本和字符编码，并添加到top节点
		TiXmlDeclaration* declaration = new TiXmlDeclaration("1.0", "UTF-8", "yes");
		if(!declaration)
		{
			return FALSE;
		}
		myDocument->LinkEndChild(declaration);

		//创建一个根元素并连接。
		TiXmlElement *RootElement =new TiXmlElement("GridStatisticSet");
		myDocument->LinkEndChild(RootElement);


		int nColumnCount = m_mapColWithFieldId.size();

		TiXmlElement *pElementChild = new TiXmlElement("dt1");
		RootElement->LinkEndChild(pElementChild);

		for (auto it=m_mapColWithFieldId.begin(); it!=m_mapColWithFieldId.end(); ++it)
		{
			CString strFieldId = it->second;
			int nCol = it->first;

			BOOL bShow = m_pBCGGrid->GetColumnsInfo().GetColumnVisible(nCol);
			if (!bShow)
			{
				continue;
			}

			CString strValue = m_pBCGGrid->GetColumnsInfo().GetColumnFooterValue(nCol);
			if (strValue.IsEmpty())
			{
				continue;
			}

			//添加FieldID
			string strId = RnString::UNICODE_TO_UTF8(strFieldId);
			TiXmlElement *pElementID = new TiXmlElement(strId.c_str());
			pElementChild->LinkEndChild(pElementID);
			CGridCtrlTableAttributeOp::LinkCStringValueToElement(strValue,pElementID);
		}


		TiXmlPrinter xmlPrint;
		myDocument->Accept(&xmlPrint);

		string strTmp = xmlPrint.CStr();
		myDocument->Clear();
		delete myDocument;//2017/06/06  释放内存

		strRet = RnString::UTF8_TO_UNICODE(strTmp);
		strStatisticRowXml = strRet;

		return TRUE;
	}
	catch(string& e)
	{
		CString strException = RnString::UTF8_TO_UNICODE(e);
		AfxMessageBox(strException);

		return FALSE;
	}

	return TRUE;
}

BOOL CDlgBCGGrid::GetShowColID(vector<int>& vecShowCol)
{
	BOOL bRet = FALSE;

	if (nullptr == m_pBCGGrid  
		|| !IsWindow(m_pBCGGrid->GetSafeHwnd()))
	{
		return FALSE;
	}

	//获取显示的列
	const int nColCounts = m_pBCGGrid->GetColumnCount();
	int* aSortOrder = new int[nColCounts];
	memset (aSortOrder, -1, nColCounts * sizeof (int));
	m_pBCGGrid->GetColumnsInfo().GetColumnOrderArray((LPINT)aSortOrder,nColCounts);
	vecShowCol.clear();
	for (int i =0; i< nColCounts; ++i)
	{
		if (aSortOrder[i] >= 0)
			vecShowCol.push_back(aSortOrder[i]);
	}
	delete[] aSortOrder;
	bRet = TRUE;

	return bRet;
}

BOOL CDlgBCGGrid::GetRowPrintDateXmlTextDataIndex(__in int nDataIndex, __out CString &strDataXml)
{
	if (nDataIndex < m_tableData.size())
	{
		auto itr_row_data = m_tableData.find(nDataIndex);
		if (itr_row_data != m_tableData.end())
		{
			CString strRet = _T("");
			//创建一个XML的文档对象。
			TiXmlDocument *myDocument =new TiXmlDocument();

			//建立描述节点，设置了版本和字符编码，并添加到top节点
			TiXmlDeclaration* declaration = new TiXmlDeclaration("1.0", "UTF-8", "yes");
			if(!declaration)
			{
				return FALSE;
			}
			myDocument->LinkEndChild(declaration);

			//创建一个根元素并连接。
			TiXmlElement *RootElement =new TiXmlElement("GridDataSet");
			myDocument->LinkEndChild(RootElement);

			TiXmlElement *pElementChild = new TiXmlElement("dt1");
			RootElement->LinkEndChild(pElementChild);

			for (auto itr_row = itr_row_data->second.begin(); itr_row != itr_row_data->second.end(); ++itr_row)
			{
				CString strFieldId = itr_row->first;
				CString strValue = itr_row->second.strValue;

				//添加FieldID
				string strId = RnString::UNICODE_TO_UTF8(strFieldId);
				TiXmlElement *pElementID = new TiXmlElement(strId.c_str());
				pElementChild->LinkEndChild(pElementID);
				CGridCtrlTableAttributeOp::LinkCStringValueToElement(strValue,pElementID);
			}

			TiXmlPrinter xmlPrint;
			myDocument->Accept(&xmlPrint);

			string strTmp = xmlPrint.CStr();
			myDocument->Clear();
			delete myDocument;//2017/06/06  释放内存

			strRet = RnString::UTF8_TO_UNICODE(strTmp);
			strDataXml = strRet;
		}
	}
	return FALSE;
}

BOOL CDlgBCGGrid::GetSelectedAllFieldPrintDataXmlText(__out CString &strDataXml)
{
	if (nullptr == m_pBCGGrid || !IsWindow(m_pBCGGrid->GetSafeHwnd()))
		return FALSE;

	CString strRet = _T("");
	try
	{
		const int nRowCounts = m_pBCGGrid->GetRowCount();		//行数
		const int nColCounts = m_pBCGGrid->GetColumnCount();	//列数
		const int nFrozenColCounts = m_pBCGGrid->GetColumnsInfo().GetFrozenColumnCount();	//冰冻列数

		if (nRowCounts <= 0 || nColCounts <= 0 || nColCounts - nFrozenColCounts <= 0)
			return FALSE;

		//创建一个XML的文档对象。
		TiXmlDocument *myDocument =new TiXmlDocument();

		//建立描述节点，设置了版本和字符编码，并添加到top节点
		TiXmlDeclaration* declaration = new TiXmlDeclaration("1.0", "UTF-8", "yes");
		if(!declaration)
			return FALSE;

		myDocument->LinkEndChild(declaration);

		//创建一个根元素并连接。
		TiXmlElement *RootElement =new TiXmlElement("GridDataSet");
		myDocument->LinkEndChild(RootElement);

		CBCGPGridRow* pRow = NULL;

		if (m_tableAttri.isMultiRowSelect)		//多行选择
		{
			for (int iRow =0; iRow < nRowCounts; ++iRow)
			{
				pRow = m_pBCGGrid->GetRow(iRow);
				if (pRow)
				{
					if (pRow->GetCheck() == 1)
					{
						TiXmlElement *pElementChild = new TiXmlElement("dt1");
						RootElement->LinkEndChild(pElementChild);
						MAP_GridCtrl_RowData map_row_data = *(MAP_GridCtrl_RowData*)(pRow->GetData());		//行数据集合
						for (auto itr_row = map_row_data.begin(); itr_row != map_row_data.end(); ++itr_row)
						{
							CString strFieldId = itr_row->first;
							CString strValue = itr_row->second.strValue;

							//添加FieldID
							string strId = RnString::UNICODE_TO_UTF8(strFieldId);
							TiXmlElement *pElementID = new TiXmlElement(strId.c_str());
							pElementChild->LinkEndChild(pElementID);
							CGridCtrlTableAttributeOp::LinkCStringValueToElement(strValue,pElementID);
						}
					}
				}
			}
		}
		else
		{
			CBCGPGridRow* pRow = m_pBCGGrid->GetCurSel();
			if (pRow && m_pBCGGrid->IsRowVisible(pRow))
			{
				TiXmlElement *pElementChild = new TiXmlElement("dt1");
				RootElement->LinkEndChild(pElementChild);
				MAP_GridCtrl_RowData map_row_data = *(MAP_GridCtrl_RowData*)(pRow->GetData());		//行数据集合
				for (auto itr_row = map_row_data.begin(); itr_row != map_row_data.end(); ++itr_row)
				{
					CString strFieldId = itr_row->first;
					CString strValue = itr_row->second.strValue;

					//添加FieldID
					string strId = RnString::UNICODE_TO_UTF8(strFieldId);
					TiXmlElement *pElementID = new TiXmlElement(strId.c_str());
					pElementChild->LinkEndChild(pElementID);
					CGridCtrlTableAttributeOp::LinkCStringValueToElement(strValue,pElementID);
				}
			}
		}

		TiXmlPrinter xmlPrint;
		myDocument->Accept(&xmlPrint);

		string strTmp = xmlPrint.CStr();
		myDocument->Clear();
		delete myDocument;//2017/06/06  释放内存

		strRet = RnString::UTF8_TO_UNICODE(strTmp);
		strDataXml = strRet;

		return TRUE;
	}
	catch(string& e)
	{
		CString strException = RnString::UTF8_TO_UNICODE(e);
		AfxMessageBox(strException);

		return FALSE;
	}

	return TRUE;
}

BOOL CDlgBCGGrid::GetAllFieldXml(__out CString &strFieldXml)
{
	return CreatePrintFieldXml(strFieldXml);
}

int CDlgBCGGrid::GetFocusRow()
{
	if (nullptr == m_pBCGGrid  
		|| !IsWindow(m_pBCGGrid->GetSafeHwnd()))
	{
		return -1;
	}

	CBCGPGridRow* pRow = m_pBCGGrid->GetCurSel();
	if (pRow)
	{
		return pRow->GetRowId();
	}

	return -1;
}

BOOL CDlgBCGGrid::GetFocusRowData(MAP_GridCtrl_RowData & rowdata)
{
	BOOL bRet = FALSE;
	
	if (nullptr == m_pBCGGrid  
		|| !IsWindow(m_pBCGGrid->GetSafeHwnd()))
	{
		return bRet;
	}

	//rowdata.clear();
	CBCGPGridRow* pRow = m_pBCGGrid->GetCurSel();
	if (pRow)
	{  
      if(m_bUserPaginationMode
         &&emPM_Local==m_emPMPaginationModeFlag)
      {
         const int nColCounts = m_pBCGGrid->GetColumnCount();		//列数
         for (int nCol=0;nCol<nColCounts;++nCol)
         {
            CString strValue = pRow->GetItem(nCol)->FormatItem();
            auto it = m_mapColWithFieldId.find(nCol);
            if (it!= m_mapColWithFieldId.end())
            {
               CString strFieldId = it->second;
               S_GridCtrl_FieldData data;
               data.strValue = strValue;
               rowdata.insert(MAP_GridCtrl_RowData::value_type(strFieldId,data));
            }
         }
         bRet = TRUE;
      }
      else
      {
         DWORD_PTR ptr = pRow->GetData();
         if (ptr != NULL)
         {
            bRet = TRUE;
            rowdata = *(MAP_GridCtrl_RowData*)ptr;

         } 
      }      
	}

	return bRet;
}

BOOL CDlgBCGGrid::GetFocusRowValue(__out CString & strValue,
	__in CString strFieldId)
{
	BOOL bRet = FALSE;

	if (nullptr == m_pBCGGrid 
		|| !IsWindow(m_pBCGGrid->GetSafeHwnd()))
	{
		return bRet;
	}

	strValue = _T("");
	
	//使用分页模式		by WangZY 2018/01/13
	if (m_bUserPaginationMode
      &&emPM_Local==m_emPMPaginationModeFlag)
	{
 		CBCGPGridRow* pRow = m_pBCGGrid->GetCurSel();
		if (pRow != nullptr )
		{
			auto it = m_mapColID.find(strFieldId);
			if (it != m_mapColID.end())
			{
				auto pItem = pRow->GetItem(it->second);
				if (pItem != nullptr)
				{
					strValue = pItem->FormatItem();
				
					bRet = TRUE;
				}
			}
		}
		
		return bRet;
	}

	CBCGPGridRow* pRow = m_pBCGGrid->GetCurSel();
	if (pRow)
	{
		bRet = TRUE;
		MAP_GridCtrl_RowData &row_data = *(MAP_GridCtrl_RowData*)pRow->GetData();
		auto itr_col = row_data.find(strFieldId);
		if (itr_col != row_data.end())
		{
			strValue = itr_col->second.strValue;
		}
	}

	return bRet;
}

BOOL CDlgBCGGrid::GetFocusRowDataIndex(__out int &nDataIndex)
{
	BOOL bRet = FALSE;

	if (nullptr == m_pBCGGrid || !IsWindow(m_pBCGGrid->GetSafeHwnd()))
		return bRet;

	CBCGPGridRow* pRow = m_pBCGGrid->GetCurSel();
	if (pRow)
	{
		bRet = TRUE;
		DWORD_PTR ptr = pRow->GetData();
		for (auto itr_ = m_tableData.begin(); itr_ != m_tableData.end(); ++itr_)
		{
			if ((MAP_GridCtrl_RowData*)ptr == &itr_->second)
			{
				nDataIndex = itr_->first;
				bRet = TRUE;
				return bRet;
			}
		}
	}

	nDataIndex = -1;
	return bRet;
}

BOOL CDlgBCGGrid::GetFilterInfoByFieldId(__out BOOL &bUseFilter, 
	__out SERCH_DATA &infoFilter, __in const CString &strFieldId)
{
	BOOL bRet = FALSE;

	if (nullptr == m_pBCGGrid  || !IsWindow(m_pBCGGrid->GetSafeHwnd()))
		return bRet;

	bUseFilter = FALSE;

	if (m_pBCGGrid->IsFilterBarEnabled())		//开启过滤
	{	
		auto itr_col_id = m_mapColID.find(strFieldId);
		if (itr_col_id != m_mapColID.end())
		{
			CWnd* pWnd = m_pBCGGrid->GetColumnsInfo().GetColumnFilterBarCtrl(itr_col_id->second);
			if (pWnd != NULL)
			{
				bRet = bUseFilter = TRUE;
				pWnd->GetWindowText(infoFilter.strText);
			}
		}
	}	

	return bRet;
}

BOOL CDlgBCGGrid::AddFieldValueByFieldId(__in CString strValue,
	__in const CString &strFieldId, __in const EM_SEL_TYPE &nSelType /*= emSel*/)
{
	if (NULL == m_pBCGGrid || !IsWindow(m_pBCGGrid->GetSafeHwnd()))
		return FALSE;

	double lfValue = _ttof(strValue);
	if (-0.00001<lfValue && 0.00001>lfValue)
		return FALSE;

	const int nRowCounts = m_pBCGGrid->GetRowCount();		//总行数
	const int nColCounts = m_pBCGGrid->GetColumnCount();	//总列数
	int nChangeColID = -1;									//要改变的列 id
	CString nChangeColName = _T("");
	auto itr_col = m_mapColID.find(strFieldId);
	if (itr_col != m_mapColID.end())
		nChangeColID = itr_col->second;
	if (nChangeColID < 0 || nChangeColID >= nColCounts)
		return FALSE;

	//nChangeColName = m_pBCGGrid->GetColumnName(nChangeColID);
	//auto itr_filter = m_mapCol_Name_ID.find(nChangeColName);
	//CString strFilterID = _T("");
	//if (itr_filter != m_mapCol_Name_ID.end())
	//{
	//	strFilterID = itr_filter->second;
	//}



	if (strFieldId.IsEmpty())
		return FALSE;

	CBCGPGridRow* pRow = NULL;

	if (emNull == nSelType || emJudgeHasSel == nSelType)
		return FALSE;

	if (emSel == nSelType)		//勾选
	{
		for (int iRow = 0; iRow < nRowCounts; ++iRow)
		{
			pRow = m_pBCGGrid->GetRow(iRow);
			if (pRow && 1 == pRow->GetCheck())
			{
				MAP_GridCtrl_RowData& dataRow = (*((MAP_GridCtrl_RowData*)pRow->GetData()));
				auto itr_col_data = dataRow.find(strFieldId); 
				if (itr_col_data != dataRow.end())
				{
					AddDataValue(strValue,itr_col_data->second);
					pRow->GetItem(nChangeColID)->SetValue(_bstr_t(itr_col_data->second.strValue));
				}
			}
		}
	}
	else if (emUnSel == nSelType)	//非勾选
	{
		for (int iRow = 0; iRow < nRowCounts; ++iRow)
		{
			pRow = m_pBCGGrid->GetRow(iRow);
			if (pRow && 0 == pRow->GetCheck())
			{
				MAP_GridCtrl_RowData& dataRow = (*((MAP_GridCtrl_RowData*)pRow->GetData()));
				auto itr_col_data = dataRow.find(strFieldId); 
				if (itr_col_data != dataRow.end())
				{
					AddDataValue(strValue,itr_col_data->second);
					pRow->GetItem(nChangeColID)->SetValue(_bstr_t(itr_col_data->second.strValue));
				}
			}
		}
	}
	else if (emAllOnGrid == nSelType || emAllData == nSelType)
	{
		for (int iRow = 0; iRow < nRowCounts; ++iRow)
		{
			pRow = m_pBCGGrid->GetRow(iRow);
			if (pRow)
			{
				MAP_GridCtrl_RowData& dataRow = (*((MAP_GridCtrl_RowData*)pRow->GetData()));
				auto itr_col_data = dataRow.find(strFieldId); 
				if (itr_col_data != dataRow.end())
				{
					AddDataValue(strValue,itr_col_data->second);
					pRow->GetItem(nChangeColID)->SetValue(_bstr_t(itr_col_data->second.strValue));
				}
			}
		}
	}
	return TRUE;
}

BOOL CDlgBCGGrid::AddDataValue(__in const CString &strValue,
	__inout S_GridCtrl_FieldData &data)
{
	CString strNewValue;

	if (CB_enum_FieldData_Double2Point== data.fieldDataType)
	{
		double lfNewValue = _ttof(data.strValue);
		lfNewValue += _ttof(strValue);
		strNewValue.Format(_T("%.2f"), lfNewValue);
		data.strValue = strNewValue;
	}
	else if (CB_enum_FieldData_Double3Point == data.fieldDataType)
	{
		double lfNewValue = _ttof(data.strValue);
		lfNewValue += _ttof(strValue);
		strNewValue.Format(_T("%.3f"), lfNewValue);
		data.strValue = strNewValue;
	}
   else if (CB_enum_FieldData_Double4Point == data.fieldDataType)
   {
      double lfNewValue = _ttof(data.strValue);
      lfNewValue += _ttof(strValue);
      strNewValue.Format(_T("%.4f"), lfNewValue);
      data.strValue = strNewValue;
   }
	else
	{
		int nNewValue = _ttoi(data.strValue);
		nNewValue += _ttoi(strValue);
		strNewValue.Format(_T("%d"), nNewValue);
		data.strValue = strNewValue;
	}

	return TRUE;
}

//Include "DlgComGrid.h"
//刷新数据到网格上		by WangZY 2017/10/31
void CDlgBCGGrid::RefreshDataInfoToGrid(int nPageType/* =0*/,BOOL bGoFirstPage /*= TRUE*/)
{
   /*
	CString strFieldId;
	try
	{
		if (nullptr == m_pBCGGrid 
			||!IsWindow(m_pBCGGrid->GetSafeHwnd()))
		{
			return;
		}

		if (nullptr == m_dbRecordSetPtr)
		{
			return;
		}
	
		_RecordsetPtr &dbRecordSetPtr = m_dbRecordSetPtr;			//网格数据记录集指针
		CQLBCGGridCtrl * &pBcgpGrid = m_pBCGGrid;

		long lRecordCount;
		dbRecordSetPtr->get_RecordCount(&lRecordCount);
		if (0 >= lRecordCount)
		{
			pBcgpGrid->SetRedraw(FALSE);
			int nOldRowCount = pBcgpGrid->GetRowCount();
			for (int i=nOldRowCount-1; i>=0; i--)
			{
				pBcgpGrid->RemoveRow(i,FALSE);
			}

			RefreshPageInfo(0, 0, 0);

			pBcgpGrid->EnableAlternateRows(TRUE);
			pBcgpGrid->SetRedraw(TRUE);
			pBcgpGrid->AdjustLayout();

			return;
		}

		if (bGoFirstPage)
		{
			dbRecordSetPtr->MoveFirst();
		}
		else
		{
			int nCurPage = dbRecordSetPtr->AbsolutePage;
			if (1 == nPageType)
			{
				dbRecordSetPtr->AbsolutePage = (PositionEnum_Param)(dbRecordSetPtr->AbsolutePage - 1);
			}
			else if (2 == nPageType)
			{
				dbRecordSetPtr->AbsolutePage = (PositionEnum_Param)(dbRecordSetPtr->AbsolutePage + 1);
			}
		}
		
		
		
		long nPageSize = dbRecordSetPtr->PageSize;
		long nPageCount = dbRecordSetPtr->PageCount;
		int nCurPage = dbRecordSetPtr->AbsolutePage;

		int nLineNumberBase = (nCurPage -1)*nPageSize;

		long lNewRowCount = nPageSize;
		pBcgpGrid->SetRedraw(FALSE);
		int nGridRowCount = pBcgpGrid->GetRowCount();
		for (int i=nGridRowCount-1; i>=0; i--)
		{
			pBcgpGrid->RemoveRow(i,FALSE);
		}
		pBcgpGrid->RemoveAll ();
		//pBcgpGrid->SetRedraw(TRUE);
		//pBcgpGrid->AdjustLayout();

		if (nCurPage == nPageCount)
		{
			lNewRowCount = lRecordCount - nLineNumberBase;
		}
		if (lNewRowCount>0)
		{
			int nColCount =  pBcgpGrid->GetColumnCount();
			for (int i=0;i<lNewRowCount; ++i)
			{
				CBCGPGridRow* pRow = pBcgpGrid->CreateRow(nColCount);
				pBcgpGrid->AddRow(pRow, FALSE ); 
				int nRowCount = pBcgpGrid->GetRowCount();
				for (auto itFreeze=m_vecFrozenIndex.begin(); itFreeze!=m_vecFrozenIndex.end();
					++itFreeze)
				{
					int nCol = *itFreeze;
					
					auto pItem = pRow->GetItem(nCol);
					if (nullptr != pItem)
					{
						pItem->SetDataColorScale(50);
					}
					
				}
			}
		}
		else if (nGridRowCount > lNewRowCount)
		{
			for (int i=nGridRowCount-1; i>=lNewRowCount; i--)
			{
				pBcgpGrid->RemoveRow(i,FALSE);
			}
		}

		RefreshPageInfo(nPageCount, nCurPage, nPageSize);
		
		
		
		lNewRowCount = dbRecordSetPtr->AbsolutePage*nPageSize;
		
		
		
		int nFieldCount = m_mapColID.size();
		if (nFieldCount <=0)
		{
			return;
		}

		int nCol = 0;	//当前列
		
		CBCGPGridItem *pItem = nullptr;
		_variant_t vValue;//var型返回值
		int nRowNo = 0;
		CString strOut;
		DWORD dwTimeOld = GetTickCount();
		pBcgpGrid->SetLineNumberBase(nLineNumberBase);

		long lTime = GetCycleCount();
		long lTmp;

		while(!dbRecordSetPtr->adoEOF
			&&nRowNo<nPageSize)
		{
			lTmp = GetCycleCount() - lTime;
			lTime = GetCycleCount();
			TRACE(_T("while( = %I64u\n"),lTmp);
			CBCGPGridRow* pRow = pBcgpGrid->GetRow(nRowNo);
			lTmp = GetCycleCount() - lTime;
			lTime = GetCycleCount();
			TRACE(_T("m_pBCGGrid->CreateRow( = %I64u\n"),lTmp);
			for (auto it=m_mapColID.begin(); it!=m_mapColID.end(); ++it)
			{
				nCol = it->second;
				strFieldId = it->first;
				pItem = pRow->GetItem(nCol);
				lTmp = GetCycleCount() - lTime;
				lTime = GetCycleCount();
				TRACE(_T("m_pBCGGrid->CreateRow( = %I64u\n"),lTmp);
				vValue = dbRecordSetPtr->GetCollect((LPCTSTR)strFieldId);
				if (pItem->GetValue().vt != vValue.vt)
				{
					pItem->EmptyValue(FALSE);
				}
				pItem->SetValue(vValue,FALSE);
				
				lTmp = GetCycleCount() - lTime;
				lTime = GetCycleCount();
				TRACE(_T("m_pBCGGrid->CreateRow( = %I64u\n"),lTmp);
			}

			lTmp = GetCycleCount() - lTime;
			lTime = GetCycleCount();
			TRACE(_T("for( = %I64u\n"),lTmp);

			//m_pBCGGrid->AddRow(pRow, FALSE ); 
			lTmp = GetCycleCount() - lTime;
			lTime = GetCycleCount();
			TRACE(_T("AddRow( = %I64u\n"),lTmp);

			nRowNo++;
			if (nRowNo>=nPageSize)
			{
				break;
			}
			dbRecordSetPtr->MoveNext();
			
			
		}
	
		
		if (dbRecordSetPtr->adoEOF)
		{
			dbRecordSetPtr->MovePrevious();
		}


	}
	catch (_com_error& e)
	{
		CString strDes = e.Description();
		//MessageBox(NULL,strDes,_T("数据库异常"),MB_ICONERROR);
		CString strMsg = _T("");
		strMsg.Format(_T("数据库异常：%s(%s)"),strDes,strFieldId);
		CWnd *pWnd = AfxGetMainWnd();
		if (pWnd)
		{
			pWnd->SendMessage(WM_ADOCONN_MSG, NULL, (LPARAM)(LPCTSTR)strMsg);
		}
	}
	catch (...)
	{

	}

	m_pBCGGrid->EnableAlternateRows(TRUE);
	m_pBCGGrid->SetRedraw(TRUE);
	long lTime = GetCycleCount();
	m_pBCGGrid->AdjustLayout();
	
	long lTmp = GetCycleCount() - lTime;
	TRACE(_T("AdjustLayout() = %I64u\n"),lTmp);
   */
}

//刷新分页控件信息		by WangZY 2017/10/31
void CDlgBCGGrid::RefreshPageInfo(int nPageCount,int nCurPage, int nPageSize)
{
	if (1 >= nCurPage)
	{
		m_btnPageUp.EnableWindow(FALSE);
	}
	else
	{
		m_btnPageUp.EnableWindow(TRUE);
	}

	if (nCurPage>=nPageCount)
	{
		m_btnPageDown.EnableWindow(FALSE);
	}
	else
	{
		m_btnPageDown.EnableWindow(TRUE);
	}

	CString strPageInfo;

	strPageInfo.Format(_T("第 %d / %d 页"),nCurPage,nPageCount);
	m_textPageInfo.SetWindowText(strPageInfo);

}

//刷新排序信息		by WangZY 2017/11/02
void CDlgBCGGrid::RefreshDataBySort()
{
	//if (m_dbRecordSetPtr != nullptr)
	//{
	//	m_dbRecordSetPtr->Sort = m_strSortInfo.GetBuffer(0);
	//	
	//	RefreshDataInfoToGrid(0,TRUE);
	//}
}

//刷新筛选过滤信息		by WangZY 2017/11/02
void CDlgBCGGrid::RefreshDataByFilter()
{
	//if (m_dbRecordSetPtr != nullptr)
	//{
	//	try
	//	{
	//		CString strFilter;
	//		auto it = m_mapFilterInfo.begin();
	//		if (it != m_mapFilterInfo.end())
	//		{
	//			strFilter = it->second;
	//			++it;
	//		}
	//		while(it != m_mapFilterInfo.end())
	//		{
	//			strFilter += _T(" and ");
	//			strFilter += it->second;
	//			++it;
	//		}

	//		CString strTitleFilter = DealCalcTitleFilter();
	//		if (!strTitleFilter.IsEmpty())
	//		{
	//			if (!strFilter.IsEmpty())
	//			{
	//				strFilter += _T(" and ");
	//			}
	//			
	//			strFilter += strTitleFilter;
	//		}
	//		//AfxMessageBox(strFilter);
	//		
	//		m_dbRecordSetPtr->Filter = _bstr_t(strFilter);
	//		//m_dbRecordSetPtr->Filter = strFilter.GetBuffer(0);
	//		//m_dbRecordSetPtr->PutFilter(strFilter.GetBuffer(0));
	//		
	//		RefreshDataInfoToGrid(0,TRUE);
	//	}
	//	catch (CMemoryException* e)
	//	{
 //        TCHAR buf[512] = {0};

 //        e->GetErrorMessage(buf,512);
	//	}
	//	catch (CFileException* e)
 //     {
 //        TCHAR buf[512] = {0};

 //        e->GetErrorMessage(buf,512);
	//	}
	//	catch (CException* e)
	//	{
	//		TCHAR buf[512] = {0};
	//		
	//		e->GetErrorMessage(buf,512);
	//	}
	//	catch (_com_error& e)
	//	{
	//		CString strDes = e.Description();
	//		//MessageBox(NULL,strDes,_T("数据库异常"),MB_ICONERROR);
	//		CString strMsg = _T("");
	//		strMsg.Format(_T("数据库异常：%s"),strDes);
	//		CWnd *pWnd = AfxGetMainWnd();
	//		if (pWnd)
	//		{
	//			pWnd->SendMessage(WM_ADOCONN_MSG, NULL, (LPARAM)(LPCTSTR)strMsg);
	//		}
	//	}
	//	catch(...)
	//	{

	//	}
	//}
}

//根据字段+值设定焦点行 yangjr 2018/6/12
BOOL CDlgBCGGrid::SetFocusRowByFieldIdAndValue(__in CString strFieldId, __in CString strFieldValue)
{
   if (NULL == m_pBCGGrid 
      || !IsWindow(m_pBCGGrid->GetSafeHwnd()))
   {
      return FALSE;
   }

   auto itr_col_id = m_mapColID.find(strFieldId);
   if (itr_col_id == m_mapColID.end())
      return FALSE;

   int iColID = itr_col_id->second;		//列号

   const int nRowCounts = m_pBCGGrid->GetRowCount();
   const int nColCounts = m_pBCGGrid->GetColumnCount();

   if (iColID < 0 || iColID >= nColCounts)
      return FALSE;

   CBCGPGridRow* pRow = NULL;
   for (int iRow = 0; iRow < nRowCounts; ++iRow)
   {
      pRow = m_pBCGGrid->GetRow(iRow);
      if (pRow)
      {
         MAP_GridCtrl_RowData &row_data = *(MAP_GridCtrl_RowData*)pRow->GetData();
         auto itr_fieldid = row_data.find(strFieldId);
         if (itr_fieldid != row_data.end())
         {
            if (strFieldValue == itr_fieldid->second.strValue)
            {
               m_pBCGGrid->SetCurSel(CBCGPGridItemID(iRow,0),SM_SINGE_SEL_GROUP | SM_SINGLE_ITEM | SM_ROW);	//选择一行
               return TRUE;
            }
         }
      }
   }
   return FALSE;
}

BOOL CDlgBCGGrid::SetFocusRowByGridRow(__in int nRowNo)
{
	if (NULL == m_pBCGGrid 
		|| !IsWindow(m_pBCGGrid->GetSafeHwnd()))
	{
		return FALSE;
	}

	const int nRowCounts = m_pBCGGrid->GetRowCount();

	if (nRowNo < nRowCounts && nRowNo >= 0)
	{
		m_pBCGGrid->SetCurSel(CBCGPGridItemID(nRowNo,0),SM_SINGE_SEL_GROUP | SM_SINGLE_ITEM | SM_ROW);	//选择一行
	}
	return TRUE;
}

BOOL CDlgBCGGrid::SetFocusRowByDataIndex(__in int nDataIndex)
{
	if (NULL == m_pBCGGrid 
		|| !IsWindow(m_pBCGGrid->GetSafeHwnd()))
	{
		return FALSE;
	}

	auto itr_row = m_tableData.find(nDataIndex);
	if (itr_row != m_tableData.end())
	{
		const int nRowCounts = m_pBCGGrid->GetRowCount();
		for(int i = 0; i< nRowCounts; ++i)
		{
			CBCGPGridRow* pRow = m_pBCGGrid->GetRow(i);
			if (pRow != NULL && m_pBCGGrid->IsRowVisible(pRow))
			{
				if((MAP_GridCtrl_RowData*)pRow->GetData() == &itr_row->second)
				{
					m_pBCGGrid->SetCurSel(CBCGPGridItemID(i,0),SM_SINGE_SEL_GROUP | SM_SINGLE_ITEM | SM_ROW);	//选择一行
					return TRUE;
				}
			}
		}
	}

	return FALSE;
}

BOOL CDlgBCGGrid::SetMultiSelectTurnOver()
{
	if (NULL == m_pBCGGrid || !IsWindow(m_pBCGGrid->GetSafeHwnd()))
		return FALSE;

	if(FALSE == m_pBCGGrid->IsCheckBoxesEnabled())
		return FALSE;

	m_pBCGGrid->GetColumnsInfo().SetCheckBoxState(FALSE);

	m_nCheckRowCount = 0;
	const int nRowCounts = m_pBCGGrid->GetRowCount();//bVisibleOnly);
	for (int i=0; i < nRowCounts; ++i)
	{
		auto pRow =m_pBCGGrid->GetRow(i);
		BOOL bCheck = pRow->GetCheck();
		pRow->SetCheck(!bCheck);
		if (!bCheck)
		{
			++m_nCheckRowCount;
		}
	}
	SetFootValue_CheckNum(m_nCheckRowCount);
	if (m_nCheckRowCount == nRowCounts)
	{
		m_pBCGGrid->GetColumnsInfo().SetCheckBoxState(TRUE);
	}
	m_pBCGGrid->Invalidate();
	return TRUE;
}

BOOL CDlgBCGGrid::SetMultiSelectCheckAll(BOOL bCheck /*= TRUE*/,BOOL bVisibleOnly /*= FALSE*/)
{
	if (NULL == m_pBCGGrid || !IsWindow(m_pBCGGrid->GetSafeHwnd()))
		return FALSE;

	if(FALSE == m_pBCGGrid->IsCheckBoxesEnabled())
		return FALSE;

	if (bVisibleOnly)
	{
		m_pBCGGrid->GetColumnsInfo().SetCheckBoxState(bCheck);
		m_pBCGGrid->CheckHeaderBoxClick(bCheck);
		m_pBCGGrid->Invalidate();

		return TRUE;
	}
	
	m_nCheckRowCount = 0;
	const int nRowCounts = m_pBCGGrid->GetRowCount();//bVisibleOnly);
	m_pBCGGrid->GetColumnsInfo().SetCheckBoxState(bCheck);
	for (int i=0; i < nRowCounts; ++i)
	{
		auto pRow =m_pBCGGrid->GetRow(i);
		
		pRow->SetCheck(bCheck);
		if (bCheck)
		{
			++m_nCheckRowCount;
		}
	}
	SetFootValue_CheckNum(m_nCheckRowCount);
	m_pBCGGrid->Invalidate();
	return TRUE;
}

BOOL CDlgBCGGrid::SetMultSelectCheckByGridRows(__in const std::vector<int/*RowNo*/> &vecRowNo,__in BOOL bCheck /*= TRUE*/)
{
	if (NULL == m_pBCGGrid || !IsWindow(m_pBCGGrid->GetSafeHwnd()))
		return FALSE;

	if(FALSE == m_pBCGGrid->IsCheckBoxesEnabled())
		return FALSE;

	const int nRowCounts = m_pBCGGrid->GetRowCount();

	for (int i=0; i < vecRowNo.size(); ++i)
	{
		if (vecRowNo[i] >= 0 && vecRowNo[i] < nRowCounts)
		{
			m_pBCGGrid->GetRow(vecRowNo[i])->SetCheck(bCheck);
		}
	}
	m_pBCGGrid->Invalidate();
	return TRUE;
}

BOOL CDlgBCGGrid::SetMultiSelectCheckByFieldId(__in CString strFieldId, __in CString strFieldValue, __in BOOL bCheck /*= TRUE*/)
{
	if (NULL == m_pBCGGrid || !IsWindow(m_pBCGGrid->GetSafeHwnd()))
		return FALSE;

	if(FALSE == m_pBCGGrid->IsCheckBoxesEnabled())
		return FALSE;

	auto itr_col_id = m_mapColID.find(strFieldId);
	if (itr_col_id == m_mapColID.end())
		return FALSE;

	int iColID = itr_col_id->second;		//列号

	const int nRowCounts = m_pBCGGrid->GetRowCount();
	const int nColCounts = m_pBCGGrid->GetColumnCount();

	if (iColID < 0 || iColID >= nColCounts)
		return FALSE;

	CBCGPGridRow* pRow = NULL;
	for (int iRow = 0; iRow < nRowCounts; ++iRow)
	{
		pRow = m_pBCGGrid->GetRow(iRow);
		if (pRow)
		{
			MAP_GridCtrl_RowData &row_data = *(MAP_GridCtrl_RowData*)pRow->GetData();
			auto itr_fieldid = row_data.find(strFieldId);
			if (itr_fieldid != row_data.end())
			{
				if (strFieldValue == itr_fieldid->second.strValue)
				{
					pRow->SetCheck(bCheck);
				}
			}
		}
	}
	m_pBCGGrid->Invalidate();		//刷新 add by lida 2017/12/26
	return TRUE;
}

BOOL CDlgBCGGrid::SetValuebyGridRowAndFieldId(__in CString &strValue,
	__in int nGridRow,__in CString strFieldId)
{
	if (NULL == m_pBCGGrid 
		|| !IsWindow(m_pBCGGrid->GetSafeHwnd()))
	{
		return FALSE;
	}

	const int nRowCounts = m_pBCGGrid->GetRowCount();
	const int nColCounts = m_pBCGGrid->GetColumnCount();

	if (nGridRow < 0 
		|| nGridRow >= nRowCounts)
	{
		return FALSE;
	}
	
	//使用分页模式		by WangZY 2018/01/13
	if (m_bUserPaginationMode
      &&emPM_Local==m_emPMPaginationModeFlag)
	{
		auto pRow = m_pBCGGrid->GetRow(nGridRow);
		if (nullptr != pRow)
		{
			auto it = m_mapColID.find(strFieldId);
			if (it == m_mapColID.end())
			{
				return FALSE;
			}
			int iCol = it->second;
			//auto vtValue = pRow->GetItem(iCol)->GetValue();
			pRow->GetItem(iCol)->EmptyValue(FALSE);
			
			pRow->GetItem(iCol)->SetValue(strValue.GetBuffer(0),TRUE);
			
			return TRUE;
			
		}

		return FALSE;
	}

   CBCGPGridRow* pRow = m_pBCGGrid->GetRow(nGridRow);
   if (pRow && pRow->GetRowId() != nGridRow)
   {
      for (int irow =0; irow < nRowCounts; ++irow)
      {
         pRow = m_pBCGGrid->GetRow(nGridRow);
         if (pRow && pRow->GetRowId() == nGridRow)
         {
            break;
         }
      }
   }

	int nGridCol = -1;
	auto itr_col_id = m_mapColID.find(strFieldId);
	if (itr_col_id == m_mapColID.end())
   {
      if (pRow)
      {
         MAP_GridCtrl_RowData &row_data = *(MAP_GridCtrl_RowData*)pRow->GetData();
         auto itr_col_data = row_data.find(strFieldId);
         if (itr_col_data != row_data.end())
         {
            itr_col_data->second.strValue = strValue;
         }
			else
         {
            return FALSE;
         }
      }
      return TRUE;
   } 

   nGridCol = itr_col_id->second;	
	if (pRow)
	{
		CBCGPGridItem* pItem = pRow->GetItem(nGridCol);

		MAP_GridCtrl_RowData &row_data = *(MAP_GridCtrl_RowData*)pRow->GetData();
		auto itr_col_data = row_data.find(strFieldId);
		if (itr_col_data != row_data.end())
		{
			itr_col_data->second.strValue = strValue;
			switch(itr_col_data->second.fieldDataType)		//判断数据类型
			{
			default:
			case CB_enum_FieldData_Time:
				{
					_bstr_t bstrValue = strValue;
					if (itr_col_data->second.fieldCtrlType == CB_enum_FieldCtrl_Checkbox 
						|| itr_col_data->second.fieldCtrlType == CB_enum_FieldCtrl_Radio)
					{
						pItem->SetValue((bool)(_ttoi(strValue) != 0));
					}
					else
						pItem->SetValue(bstrValue);
				}
				break;
			case CB_enum_FieldData_Int:	//整型
				{
					if (itr_col_data->second.fieldCtrlType == CB_enum_FieldCtrl_Checkbox 
						|| itr_col_data->second.fieldCtrlType == CB_enum_FieldCtrl_Radio)
					{
						pItem->SetValue(
							(bool)(_ttoi(strValue) != 0));
					}
					else
					{
						long nValue = _ttoi(strValue);
						pItem->SetValue(nValue);
					}
				}
				break;
			case CB_enum_FieldData_Double2Point:	//小数点
				{
					double fValue = _ttof(strValue);
					pItem->SetUserFormat(TRUE,_T("%.2f"),fValue);
					pItem->SetValue(fValue);
				}
			case CB_enum_FieldData_Double3Point:
				{
					double fValue = _ttof(strValue);
					pItem->SetUserFormat(TRUE,_T("%.3f"),fValue);
					pItem->SetValue(fValue);
				}
				break;
         case CB_enum_FieldData_Double4Point:
            {
               double fValue = _ttof(strValue);
               pItem->SetUserFormat(TRUE,_T("%.4f"),fValue);
               pItem->SetValue(fValue);
            }
            break;
			}
		}
	}
	return TRUE;
}

BOOL CDlgBCGGrid::SetValuebyGridRowAndFieldId(__in S_GridCtrl_FieldData &data,
	__in int nGridRow,__in CString strFieldId)
{
	if (NULL == m_pBCGGrid 
		|| !IsWindow(m_pBCGGrid->GetSafeHwnd()))
	{
		return FALSE;
	}

	const int nRowCounts = m_pBCGGrid->GetRowCount();
	const int nColCounts = m_pBCGGrid->GetColumnCount();

	if (nGridRow < 0 || nGridRow >= nRowCounts)
		return FALSE;

	int nGridCol = -1;
	auto itr_col_id = m_mapColID.find(strFieldId);
	if (itr_col_id != m_mapColID.end())
		nGridCol = itr_col_id->second;

	if (nGridCol < 0 || nGridCol >= nColCounts)
		return FALSE;

	CBCGPGridRow* pRow = m_pBCGGrid->GetRow(nGridRow);
	if (pRow && pRow->GetRowId() != nGridRow)
	{
		for (int i=0; i< nRowCounts; ++i)
		{
			pRow = m_pBCGGrid->GetRow(nGridRow);
			if (pRow && pRow->GetRowId() == nGridRow)
			{
				break;
			}
		}
	}
	if (pRow)
	{
		CBCGPGridItem* pItem = pRow->GetItem(nGridCol);
      MAP_GridCtrl_RowData* p_row_data = NULL;
      if(m_bUserPaginationMode
         &&emPM_Local==m_emPMPaginationModeFlag)
      {
         //const int nColCounts = m_pBCGGrid->GetColumnCount();		//列数
         //for (int nCol=0;nCol<nColCounts;++nCol)
         //{
         //   CString strValue = pRow->GetItem(nCol)->FormatItem();
         //   auto it = m_mapColWithFieldId.find(nCol);
         //   if (it!= m_mapColWithFieldId.end())
         //   {
         //      CString strFieldId = it->second;
         //      S_GridCtrl_FieldData data;
         //      data.strValue = strValue;
         //      row_data.insert(MAP_GridCtrl_RowData::value_type(strFieldId,data));
         //   }
         //}
      }
      else
      {
         DWORD_PTR ptr = pRow->GetData();
         if (ptr == NULL) return FALSE;
         p_row_data = (MAP_GridCtrl_RowData*)ptr;
      }

      if (p_row_data == NULL)
      {
         return FALSE;
      }
  
      MAP_GridCtrl_RowData& row_data = *p_row_data;

		auto itr_col_data = row_data.find(strFieldId);
		if (itr_col_data != row_data.end())
		{
			itr_col_data->second = data;
			switch(itr_col_data->second.fieldDataType)		//判断数据类型
			{
			default:
			case CB_enum_FieldData_Time:
				{
					_bstr_t bstrValue = data.strValue;
					if (itr_col_data->second.fieldCtrlType == CB_enum_FieldCtrl_Checkbox 
						|| itr_col_data->second.fieldCtrlType == CB_enum_FieldCtrl_Radio)
					{
						pItem->SetValue((bool)(_ttoi(data.strValue) != 0));
					}
					else
						pItem->SetValue(bstrValue);
				}
				break;
			case CB_enum_FieldData_Int:	//整型
				{
					if (itr_col_data->second.fieldCtrlType == CB_enum_FieldCtrl_Checkbox 
						|| itr_col_data->second.fieldCtrlType == CB_enum_FieldCtrl_Radio)
					{
						pItem->SetValue(
							(bool)(_ttoi(data.strValue) != 0));
					}
					else
					{
						long nValue = _ttof(data.strValue);
						pItem->SetValue(nValue);
					}
				}
				break;
			case CB_enum_FieldData_Double2Point:	//小数点
				{
					double fValue = _ttof(data.strValue);
					pItem->SetUserFormat(TRUE,_T("%.2f"),fValue);
					pItem->SetValue(fValue);
				}
				break;
			case CB_enum_FieldData_Double3Point:
				{
					double fValue = _ttof(data.strValue);
					pItem->SetUserFormat(TRUE,_T("%.3f"),fValue);
					pItem->SetValue(fValue);
				}
				break;
         case CB_enum_FieldData_Double4Point:
            {
               double fValue = _ttof(data.strValue);
               pItem->SetUserFormat(TRUE,_T("%.4f"),fValue);
               pItem->SetValue(fValue);
            }
            break;
			case CB_enum_FieldData_Button:
				{
					_bstr_t bstrValue = data.strValue;
					pItem->SetValue(bstrValue);
				}
				break;
         case CB_enum_FieldData_BallColor:
            {
               if (pItem->GetRuntimeClass() == RUNTIME_CLASS(CBallColorBCGPGridCellItem))
               {
                  COLORREF color1 = -1,color2 = -1,color3 = -1;
                  if (data.sptr_cellBackgroundClrVec.get())
                  {
                     if ((*(data.sptr_cellBackgroundClrVec)).size() > 1)
                     {
                        auto itColor1 = (*(data.sptr_cellBackgroundClrVec)).at(1);
                        color1 = itColor1;
                     }
                     if ((*(data.sptr_cellBackgroundClrVec)).size() > 2)
                     {
                        auto itColor2 = (*(data.sptr_cellBackgroundClrVec)).at(2);
                        color2 = itColor2;
                     }
                     if ((*(data.sptr_cellBackgroundClrVec)).size() > 3)
                     {
                        auto itColor3 = (*(data.sptr_cellBackgroundClrVec)).at(3);
                        color3 = itColor3;
                     }
                  }
                  CString strText1,strText2,strText3;
                  if (data.sptr_normalComboxData.get())
                  {
                     if ((*(data.sptr_normalComboxData)).size() > 0)
                     {
                        strText1 = (*(data.sptr_normalComboxData)).at(0);
                     }
                     if ((*(data.sptr_normalComboxData)).size() > 1)
                     {
                        strText2 = (*(data.sptr_normalComboxData)).at(1);
                     }
                     if ((*(data.sptr_normalComboxData)).size() > 2)
                     {
                        strText3 = (*(data.sptr_normalComboxData)).at(2);
                     }
                  }
                  ((CBallColorBCGPGridCellItem *)pItem)->SetDisplayText(strText1,strText2,strText3);
                  ((CBallColorBCGPGridCellItem *)pItem)->SetColor(color1,color2,color3);
               }
            }
            break;
			}

			//控件类型
			switch(itr_col_data->second.fieldCtrlType)		
			{
			default:
			case CB_enum_FieldCtrl_Text:
				{
					//CString strTemp(typeid(pItem).name());
					//CString strTemp2(typeid(pRow->GetItem(nGridCol)).name());
					//
					////pItem->GetThisClass()->TypeId;
					////pItem->IsKindOf()
					//CBCGPGridItem * pItem1 = pRow->GetItem(nGridCol);
					//BOOL bKind = pItem1->IsKindOf(RUNTIME_CLASS(CBCGPGridItem));
					//BOOL bKind2 = pItem1->IsKindOf(RUNTIME_CLASS(CButtonItem));

					//BOOL bKind3 = 
					//	(pItem->GetRuntimeClass() == RUNTIME_CLASS(CBCGPGridItem));
					//BOOL bKind4 = 
					//	(pItem->GetRuntimeClass() == RUNTIME_CLASS(CButtonItem));

					//
					//CRuntimeClass * pClass1 = pItem1->GetThisClass();
					//CRuntimeClass * pClass2 = pItem1->GetRuntimeClass();

					//CRuntimeClass *pClass3 = pRow->GetItem(nGridCol)->GetRuntimeClass();
					//CString strTemp1(pRow->GetItem(nGridCol)->GetThisClass()->m_lpszClassName);
					CString strTemp(pItem->GetRuntimeClass()->m_lpszClassName);


					if (strTemp != _T("CBCGPGridItem"))
					{
						_bstr_t strValue = data.strValue;
						CBCGPGridItem *pItemNew = new CBCGPGridItem(strValue);
						
						pRow->ReplaceItem(nGridCol,pItemNew);
						pItem = pItemNew;
					}
				}
				break;
			case CB_enum_FieldCtrl_Checkbox:		//check box 控件
				{
					CBCGPGridCheckItem* pCheckItem = (CBCGPGridCheckItem*)pItem;
					if (pCheckItem)
					{
						/*if (data.strValue == _T("1"))
							pCheckItem->SetState(CBCGPGridCheckItem::Checked);
						else
							pCheckItem->SetState(CBCGPGridCheckItem::Checked);	*/
						//2017-11-21 wangzl
						if (_T("0") == data.strValue)
							pCheckItem->SetState(CBCGPGridCheckItem::UnChecked);
						else
							pCheckItem->SetState(CBCGPGridCheckItem::Checked);
					}
				}
				break;
			case CB_enum_FieldCtrl_NormalCombox:	//drop list
				{
					pItem->RemoveAllOptions();
					if (data.sptr_normalComboxData.get())
					{
						for(int i=0; i< data.sptr_normalComboxData->size(); ++i)
						{
							pItem->AddOption((*data.sptr_normalComboxData)[i],TRUE);
						}
						if (data.sptr_normalComboxData->size() <= 0)
						{
							pItem->AddOption(_T(""),TRUE);
						}
					}
				}
				break;
			case CB_enum_FieldCtrl_SpecialCombox:	//pop dlg
				{}
				break;
			case CB_enum_FieldCtrl_Radio:
				{
					CBCGPGridCheckItem* pCheckItem = (CBCGPGridCheckItem*)pItem;
					if (pCheckItem)
					{
						if (_T("0") == data.strValue)
							pCheckItem->SetState(CBCGPGridCheckItem::UnChecked);
						else
							pCheckItem->SetState(CBCGPGridCheckItem::UnChecked);	
					}
				}
				break;
			case CB_enum_FieldCtrl_EditCombox:	//drop down
				{
					pItem->RemoveAllOptions();
					if (data.sptr_normalComboxData.get())
					{
						for(int i=0; i< data.sptr_normalComboxData->size(); ++i)
						{
							pItem->AddOption((*data.sptr_normalComboxData)[i],TRUE);
						}
						if (data.sptr_normalComboxData->size() <= 0)
						{
							pItem->AddOption(_T(""),TRUE);
						}
					}
				}
				break;
			case CB_enum_FieldCtrl_Button:	//按钮
				{
					//CBCGPGridItem* pItem = pRow->GetItem(nGridCol);
					//CString strTemp(pItem->GetThisClass()->m_lpszClassName);
					CString strTemp(pItem->GetRuntimeClass()->m_lpszClassName);
					if (strTemp != _T("CButtonItem"))
					{
						CButtonItem *pItemNew = new CButtonItem(
							data.strValue , UID_GRID_BTN1);	
						pRow->ReplaceItem(nGridCol,pItemNew);
						pItem = pItemNew;
					}
					
					/*if (0 == data.byteProgress)
					{
					pItem->Enable(TRUE);
					}
					else
					{
					pItem->Enable(FALSE);
					}*/

					//pItem->enable
				}
				break;
         case CB_enum_FieldCtrl_BallColor:
            {
               if (pItem->GetRuntimeClass() == RUNTIME_CLASS(CBallColorBCGPGridCellItem))
               {
                  COLORREF color1 = -1,color2 = -1,color3 = -1;
                  if (data.sptr_cellBackgroundClrVec.get())
                  {
                     if ((*(data.sptr_cellBackgroundClrVec)).size() > 1)
                     {
                        auto itColor1 = (*(data.sptr_cellBackgroundClrVec)).at(1);
                        color1 = itColor1;
                     }
                     if ((*(data.sptr_cellBackgroundClrVec)).size() > 2)
                     {
                        auto itColor2 = (*(data.sptr_cellBackgroundClrVec)).at(2);
                        color2 = itColor2;
                     }
                     if ((*(data.sptr_cellBackgroundClrVec)).size() > 3)
                     {
                        auto itColor3 = (*(data.sptr_cellBackgroundClrVec)).at(3);
                        color3 = itColor3;
                     }
                  }
                  CString strText1,strText2,strText3;
                  if (data.sptr_normalComboxData.get())
                  {
                     if ((*(data.sptr_normalComboxData)).size() > 0)
                     {
                        strText1 = (*(data.sptr_normalComboxData)).at(0);
                     }
                     if ((*(data.sptr_normalComboxData)).size() > 1)
                     {
                        strText2 = (*(data.sptr_normalComboxData)).at(1);
                     }
                     if ((*(data.sptr_normalComboxData)).size() > 2)
                     {
                        strText3 = (*(data.sptr_normalComboxData)).at(2);
                     }
                  }
                  CBallColorBCGPGridCellItem *pItemNew = new CBallColorBCGPGridCellItem(strText1,strText2,strText3,color1, color2,color3);
                  pRow->ReplaceItem(nGridCol,pItemNew);
                  pItem = pItemNew;
               }
               
            }
            break;
			}

			//单元格背景颜色
			if ((data.sptr_cellBackgroundClrVec).get())
			{
				vector<int>& vec_clr = *(data.sptr_cellBackgroundClrVec);
				if (vec_clr.size() > 0)
				{
					pItem->SetBackgroundColor(vec_clr[0]);              
            }else
            {
               pItem->SetBackgroundColor(-1);//颜色恢复默认 yangjr 2018/1/9
            }
			}
		}
	}

	return TRUE;
}

BOOL CDlgBCGGrid::SetValueByGridRowAndCol(__in CString &strValue,
	__in int nGridRow,__in int nGridCol)
{
	if (NULL == m_pBCGGrid 
		|| !IsWindow(m_pBCGGrid->GetSafeHwnd()))
	{
		return FALSE;
	}
	
	auto pRow = m_pBCGGrid->GetRow(nGridRow);
	if (nullptr == pRow)
	{
		return FALSE;
	}
	auto pData = pRow->GetData();
	if (NULL == pData)
	{
		return FALSE;
	}
	MAP_GridCtrl_RowData &dataRow = *(MAP_GridCtrl_RowData*)pData;
	auto itr_col_id = m_mapColWithFieldId.find(nGridCol);
	if (itr_col_id == m_mapColWithFieldId.end())
	{
		return FALSE;
	}
	CString strFieldId = _T("");
	strFieldId = itr_col_id->second;
	auto itData = dataRow.find(strFieldId);
	if (itData == dataRow.end())
	{
		return FALSE;
	}

	auto pItem = pRow->GetItem(nGridCol);
	BOOL bSet = _in_SetGridItemValue(pItem,strValue);
	if (!bSet)
	{
		return FALSE;
	}
	
	itData->second.strValue = strValue;

	return TRUE;
}

BOOL CDlgBCGGrid::SetValuebyDataRowIndexAndFieldId(__in CString &strValue,
	__in int nGridRow,__in CString strFieldId)
{
	if (NULL == m_pBCGGrid || !IsWindow(m_pBCGGrid->GetSafeHwnd()))
		return FALSE;
	const int nRowCounts = m_pBCGGrid->GetRowCount();
	const int nColCounts = m_pBCGGrid->GetColumnCount();

	if (nGridRow < 0 || nGridRow >= nRowCounts)
		return FALSE;

	int nGridCol = -1;
	auto itr_col_id = m_mapColID.find(strFieldId);
	if (itr_col_id != m_mapColID.end())
		nGridCol = itr_col_id->second;

	if (nGridCol < 0 || nGridCol >= nColCounts)
		return FALSE;

	CBCGPGridRow* pRow = m_pBCGGrid->GetRow(nGridRow);
	if (pRow && pRow->GetRowId() != nGridRow)
	{
		for (int i=0; i< nRowCounts; ++i)
		{
			if (pRow && pRow->GetRowId() == nGridRow)
			{
				break;
			}
		}
	}
	if (pRow)
	{
		CBCGPGridItem* pItem = pRow->GetItem(nGridCol);
		MAP_GridCtrl_RowData &row_data = *(MAP_GridCtrl_RowData*)pRow->GetData();
		auto itr_col_data = row_data.find(strFieldId);
		if (itr_col_data != row_data.end())
		{
			itr_col_data->second.strValue = strValue;
			BOOL bSetValue = TRUE;
			//控件类型
			switch(itr_col_data->second.fieldCtrlType)
			{
			default:
			case CB_enum_FieldCtrl_Text:
				break;
			case CB_enum_FieldCtrl_Checkbox:		//check box 控件
				{
					bSetValue = FALSE;
					CBCGPGridCheckItem* pCheckItem = (CBCGPGridCheckItem*)pItem;
					if (pCheckItem)
					{
						if (_T("0") == strValue)
							pCheckItem->SetState(CBCGPGridCheckItem::UnChecked);
						else
							pCheckItem->SetState(CBCGPGridCheckItem::Checked);
					}
				}
				break;
			case CB_enum_FieldCtrl_NormalCombox:	//drop list
				{}
				break;
			case CB_enum_FieldCtrl_SpecialCombox:	//pop dlg
				{}
				break;
			case CB_enum_FieldCtrl_Radio:
				{}
				break;
			case CB_enum_FieldCtrl_EditCombox:	//drop down
				{}
				break;
			}

			if (bSetValue)
			{
				switch(itr_col_data->second.fieldDataType)		//判断数据类型
				{
				default:
				case CB_enum_FieldData_Time:
					{
						_bstr_t bstrValue = strValue;
						if (itr_col_data->second.fieldCtrlType == CB_enum_FieldCtrl_Checkbox 
							|| itr_col_data->second.fieldCtrlType == CB_enum_FieldCtrl_Radio)
						{
							pItem->SetValue((bool)(_ttoi(strValue) != 0));
						}
						else
							pItem->SetValue(bstrValue);
					}
					break;
				case CB_enum_FieldData_Int:	//整型
					{
						if (itr_col_data->second.fieldCtrlType == CB_enum_FieldCtrl_Checkbox 
							|| itr_col_data->second.fieldCtrlType == CB_enum_FieldCtrl_Radio)
						{
							pItem->SetValue((bool)(_ttoi(strValue) != 0));
						}
						else
						{
							long nValue = _ttoi(strValue);
							pItem->SetValue(nValue);
						}
						
					}
					break;
				case CB_enum_FieldData_Double2Point:	//小数点
					{
						double fValue = _ttof(strValue);
						pItem->SetUserFormat(TRUE,_T("%.2f"),fValue);
						pItem->SetValue(fValue);
					}
				case CB_enum_FieldData_Double3Point:
					{
						double fValue = _ttof(strValue);
						pItem->SetUserFormat(TRUE,_T("%.3f"),fValue);
						pItem->SetValue(fValue);
					}
					break;
            case CB_enum_FieldData_Double4Point:
               {
                  double fValue = _ttof(strValue);
                  pItem->SetUserFormat(TRUE,_T("%.4f"),fValue);
                  pItem->SetValue(fValue);
               }
               break;
				}
			}
		}
	}

	return TRUE;
}

BOOL CDlgBCGGrid::SetValuebyFieldIdAndValue(__in CString strFieldIdIndex,
	__in CString &strValueIndex,__in CString strTarFieldID,__in CString strTarValue)
{
	if (NULL == m_pBCGGrid 
		|| !IsWindow(m_pBCGGrid->GetSafeHwnd()))
	{
		return FALSE;
	}

	//使用分页模式		by WangZY 2018/01/13
	if (m_bUserPaginationMode
      &&emPM_Local==m_emPMPaginationModeFlag)
	{
		CString strFind;
		strFind.Format(_T("%s='%s'"),strFieldIdIndex,strValueIndex);
		//auto Bookmark1 = m_dbRecordSetPtr->Bookmark;

		try
		{
			//m_dbRecordSetPtr->Find(strFind.GetBuffer(0),0,adSearchBackward);
			//m_dbRecordSetPtr->PutCollect((LPCTSTR)strTarFieldID,(LPCTSTR)strTarValue);
			//int nPos = m_dbRecordSetPtr->AbsolutePosition;
			//int nPageSize = m_dbRecordSetPtr->PageSize;
			//m_dbRecordSetPtr->Move(0,Bookmark1);

			//int nGridRow = (nPos-1)%nPageSize;
			//
			//auto itr_col_id = m_mapColID.find(strTarFieldID);
			//if (itr_col_id != m_mapColID.end())
			//{
			//	int iColID = itr_col_id->second;
			//	CBCGPGridRow *pRow = m_pBCGGrid->GetRow(nGridRow);
			//	CBCGPGridItem *pItem = pRow->GetItem(iColID);
			//	_in_SetGridItemValue(pItem,strTarValue);
			//}
		}
		catch (CMemoryException* e)
		{
			TCHAR   szError[1024];   
			e->GetErrorMessage(szError,1024); 
			CString strDes = szError;
		}
		catch (CFileException* e)
		{
			TCHAR   szError[1024];   
			e->GetErrorMessage(szError,1024); 
			CString strDes = szError;
		}
		catch (_com_error& e)
		{
			CString strDes = e.Description();
			//MessageBox(NULL,strDes,_T("数据库异常"),MB_ICONERROR);
			CString strMsg = _T("");
			
		}
		catch (CException* e)
		{
			TCHAR   szError[1024];   
			e->GetErrorMessage(szError,1024); 
			CString strDes = szError;
		}
		catch (...)
		{

		}
		
		

		return TRUE;
	}

	const int nRowCounts = m_pBCGGrid->GetRowCount();
	const int nColCounts = m_pBCGGrid->GetColumnCount();
	if (m_bUseNewAttri)
	{
		std::vector<CString> vecNeedfulField;

		GetNeedfulPackageFieldId(vecNeedfulField);
		auto itField1 = std::find(vecNeedfulField.begin(),
			vecNeedfulField.end(),strFieldIdIndex);
		if (itField1 == vecNeedfulField.end())
		{
			return FALSE;
		}

		auto itField2 = std::find(vecNeedfulField.begin(),
			vecNeedfulField.end(),strTarFieldID);
		if (itField1 == vecNeedfulField.end())
		{
			return FALSE;
		}
	}

	int iColID = -1,iColID_Tar = -1;
	auto itr_col_id = m_mapColID.find(strFieldIdIndex);
	if (itr_col_id != m_mapColID.end())
	{
		iColID = itr_col_id->second;
	}

	itr_col_id = m_mapColID.find(strTarFieldID);
	if (itr_col_id != m_mapColID.end())
	{
		iColID_Tar = itr_col_id->second;
	}

	if ((iColID < 0 
		|| iColID_Tar < 0)
		&&!m_bUseNewAttri	)
	{
		return FALSE;
	}
	
	for (int iRow =0; iRow < nRowCounts; ++iRow)
	{
		_bstr_t strValue = m_pBCGGrid->GetRow(iRow)->GetItem(iColID)->GetValue();
		if ((LPCTSTR)strValue != strValueIndex)
			continue;
		
		//2017/11/04 zhangt 设置数据 BCGP根据Item类型 插入数据
		//m_pBCGGrid->GetRow(iRow)->GetItem(iColID_2)->SetValue(_bstr_t(strTarValue));
		CBCGPGridRow *pRow = m_pBCGGrid->GetRow(iRow);
		CBCGPGridItem *pItem = pRow->GetItem(iColID_Tar);
		_in_SetGridItemValue(pItem, strTarValue);
		
		
		MAP_GridCtrl_RowData &row_data = *(MAP_GridCtrl_RowData*)m_pBCGGrid->GetRow(iRow)->GetData();
		auto itr_tag = row_data.find(strTarFieldID);
		if (itr_tag != row_data.end())
			itr_tag->second.strValue =strTarValue;
		break;
	}

	return TRUE;
}

BOOL CDlgBCGGrid::IsValidDataRgn()
{
	BOOL bRet = FALSE;
	if (::IsWindow(m_pBCGGrid->GetSafeHwnd()))
	{
		CRect rc;
		m_pBCGGrid->GetClientRect(rc);

		//获取水平滚动条信息
// 		CScrollBar *pHorzScroll = m_pBCGGrid->GetScrollBarCtrl(SB_HORZ);
// 		if (pHorzScroll && IsWindow(pHorzScroll->GetSafeHwnd()))
// 		{
// 			int nHorzScrollHeight = GetSystemMetrics(SM_CXHSCROLL);//水平滚动条的高度; 
// 			rc.bottom = rc.top+rc.Height()-nHorzScrollHeight;
// 		}

		BOOL bShowSumBar = m_pBCGGrid->GetColumnsInfo().IsEnableShowFooterRow();
		if (bShowSumBar)//存在统计栏
		{
			rc.bottom = rc.top+rc.Height()-m_tableAttri.nDataRowHeight;
		}
		
		CPoint pt;
		GetCursorPos(&pt);
		m_pBCGGrid->ScreenToClient(&pt);
		if (rc.PtInRect(pt))
		{	
			bRet = TRUE;
		}
	}

	return bRet;
}

BOOL CDlgBCGGrid::IsInfoInMapByFieldId(__in const MAP_GridCtrl_AllData &mapData,__in const CString &strFieldId,__in const CString &strValue)
{
	BOOL bRet = FALSE;
	if (mapData.size()<=0 || strFieldId.IsEmpty())
		return bRet;

	for (auto it=mapData.begin(); it!=mapData.end(); ++it)
	{
		auto itData = it->second.find(strFieldId);
		if (itData != it->second.end())
		{
			if (itData->second.strValue == strValue)
			{
				bRet = TRUE;
				return bRet;
			}
		}
	}

	return bRet;
}

BOOL CDlgBCGGrid::GetFieldIdByGridCol(__out CString &strFieldId, __in int nGridCol)
{
	strFieldId = _T("");

	if (NULL == m_pBCGGrid || !IsWindow(m_pBCGGrid->GetSafeHwnd()))
		return FALSE;

	const int nColCounts = m_pBCGGrid->GetColumnCount();

	if (nGridCol < 0 || nGridCol > nColCounts)
		return FALSE;

	CString strColName = m_pBCGGrid->GetColumnName(nGridCol);

	//auto itr_col_id = m_mapCol_Name_ID.find(strColName);
	//if (itr_col_id != m_mapCol_Name_ID.end())
	//{
	//	strFieldId = itr_col_id->second;
	//}

	auto itr_col_id = m_mapColWithFieldId.find(nGridCol);
	if (itr_col_id != m_mapColWithFieldId.end())
	{
		strFieldId = itr_col_id->second;
	}

	return TRUE;
}

BOOL CDlgBCGGrid::GetGridColByFieldId(__out int &nGridCol, __in CString strFieldId)
{
	nGridCol = -1;

	if (NULL == m_pBCGGrid 
		|| !IsWindow(m_pBCGGrid->GetSafeHwnd()))
	{
		return FALSE;
	}

	auto itr_col_id = m_mapColID.find(strFieldId);
	if(itr_col_id != m_mapColID.end())
	{
		nGridCol = itr_col_id->second;
		
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CDlgBCGGrid::SetFilterInfoByFieldId(__in const std::vector<CString> &vecFilter,__in const CString &strFieldId)
{
	if (vecFilter.size() <= 0 )
		return FALSE;

	if (NULL == m_pBCGGrid || !IsWindow(m_pBCGGrid->GetSafeHwnd()))
		return FALSE;

	int iColID = -1;
	auto itr_col_id = m_mapColID.find(strFieldId);
	if (itr_col_id != m_mapColID.end())
		iColID = itr_col_id->second;

	if (iColID < 0)
		return FALSE;

	//筛选栏数据
	if (m_pBCGGrid->IsFilterBarEnabled())
	{
		m_pBCGGrid->GetColumnsInfo().GetColumnFilterBarCtrl(iColID)->SetWindowText(vecFilter[0]);
	}

	return TRUE;
}

BOOL CDlgBCGGrid::SetFilterInfoByFieldId(__in const CString &strFilter, __in const CString &strFieldId)
{
	vector<CString> vecFilter;
	vecFilter.push_back(strFilter);
	return SetFilterInfoByFieldId(vecFilter,strFieldId);
}

BOOL CDlgBCGGrid::SortByFieldId(__in const CString &strFieldId, BOOL bAscending /*= TRUE*/)
{
	if (m_pBCGGrid && IsWindow(m_pBCGGrid->GetSafeHwnd()))
	{
		auto itr_col_id = m_mapColID.find(strFieldId);
		if (itr_col_id != m_mapColID.end())
		{
			int iCol = itr_col_id->second;
			const int nCols = m_pBCGGrid->GetColumnCount();
			if (iCol >= 0 && iCol < nCols)
			{
				m_pBCGGrid->Sort(iCol,bAscending);
				return TRUE;
			}
		}
	}
	return FALSE;
}

BOOL CDlgBCGGrid::SortByColumn(__in const int nColumn, BOOL bAscending /*= TRUE*/)
{
	if (m_pBCGGrid && IsWindow(m_pBCGGrid->GetSafeHwnd()))
	{
		const int nCols = m_pBCGGrid->GetColumnCount();
		if (nColumn >= 0 && nColumn < nCols)
		{
			m_pBCGGrid->Sort(nColumn,bAscending);
			return TRUE;
		}	
	}
	return FALSE;
}

BOOL CDlgBCGGrid::IsCanEdit(int nRow, int nColumn)
{
	if (NULL == m_pBCGGrid || !IsWindow(m_pBCGGrid->GetSafeHwnd()))
		return FALSE;

	const int nRowCounts = m_pBCGGrid->GetRowCount();
	const int nColCounts = m_pBCGGrid->GetColumnCount();

	if (nRow < 0 || nRow >= nRowCounts || nColumn < 0 || nColumn >= nColCounts || nRowCounts < 0 || nColCounts < 0)
		return FALSE;

	CBCGPGridRow* pRow = m_pBCGGrid->GetRow(nRow);
	if (pRow != NULL)
	{
		CBCGPGridItem* pItem = pRow->GetItem(nColumn);
		if (pItem != NULL)
		{
			return !pItem->IsReadOnly();
		}
	}

	return FALSE;
}

BOOL CDlgBCGGrid::IsValidRow(__in int nRow)
{
	if (NULL == m_pBCGGrid || !IsWindow(m_pBCGGrid->GetSafeHwnd()))
		return FALSE;

	const int nRowCounts = m_pBCGGrid->GetRowCount();

	if (nRow < 0 || nRow >= nRowCounts)
		return FALSE;

	return TRUE;
}

BOOL CDlgBCGGrid::SetSelWholeRow(int iRow,int iCol,BOOL bLeftDown/* = TRUE*/)		//选择一行,默认左键)
{
	if (m_pBCGGrid && IsWindow(m_pBCGGrid->GetSafeHwnd()))
	{
		if (iRow >= 0 && iRow < m_pBCGGrid->GetRowCount())
		{
			iCol = iCol < 0 ? 0 : iCol;
			iCol = iCol > m_pBCGGrid->GetColumnCount() ? m_pBCGGrid->GetColumnCount() : iCol;

			//选择一行
			//m_pBCGGrid->SetCurSel(CBCGPGridItemID(iRow,iCol),SM_SINGE_SEL_GROUP | SM_SINGLE_ITEM | SM_ROW);

			DWORD dw_style = SM_SINGE_SEL_GROUP | SM_SINGLE_ITEM | SM_ROW;
			if (m_tableAttri.isMultiRowSelect)
			{
				if (bLeftDown)	//左键
				{
					if (m_bKeyCtrlDown && !m_bKeyShiftDown)	//ctrl 按下
					{
						dw_style = SM_ADD_SEL_GROUP | SM_SECOND_CLICK | SM_ROW;
					}
					else if (!m_bKeyCtrlDown && m_bKeyShiftDown)	//shift 按下
					{
						dw_style = SM_CONTINUE_SEL_GROUP | SM_SECOND_CLICK | SM_ROW;
					}
				}
				else	//右键
				{

				}
			}

			m_pBCGGrid->SetCurSel(CBCGPGridItemID(iRow,iCol),dw_style);
			return TRUE;
		}	
	}
	return FALSE;
}

void CDlgBCGGrid::OnBnClickedBtnPageup()
{
	// TODO: Add your control notification handler code here
   if (emPM_Local == m_emPMPaginationModeFlag)
   {
      RefreshDataInfoToGrid(1,FALSE);
   }

   if (emPM_DbSvr)
   {
      CPageInfo info = m_infoPage;
      info.m_nCurPage -= 1;
      GetOwner()->SendMessage(UM_PAGINATION_REFRESH_DATA_MSG,(WPARAM)&info,emRDM_PrePage);
   }
}

void CDlgBCGGrid::OnBnClickedBtnPagedown()
{
	// TODO: Add your control notification handler code here
   if (emPM_Local == m_emPMPaginationModeFlag)
   {
      RefreshDataInfoToGrid(2,FALSE);
   }

   if (emPM_DbSvr)
   {
      CPageInfo info = m_infoPage;
      info.m_nCurPage += 1;
      GetOwner()->SendMessage(UM_PAGINATION_REFRESH_DATA_MSG,(WPARAM)&info,emRDM_NextPage);
   }
	
}

void CDlgBCGGrid::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	
	switch (nIDEvent)
	{
	case UID_TIMER_REFRESH_HEADER_SORT:
		{
			KillTimer(nIDEvent);
			RefreshDataBySort();
		}
		break;
	case UID_TIMER_REFRESH_FILTER_CHANGED:
		{
			KillTimer(nIDEvent);
			RefreshDataByFilter();
		}
		break;
	case UID_TIMER_REFRESH_SUMARY_ROW_INFO:
		{
			KillTimer(nIDEvent);
			RefreshGridStatisticRow(m_pBCGGrid,TRUE);
		}
		break;
	default:
		break;
	}

	CBCGPDialog::OnTimer(nIDEvent);
}

void CDlgBCGGrid::OnGridHeadMenu(UINT id)
{
	S_GridCtrl_TableAttri tableAttri;
	GetGridAttriInfo(tableAttri);
	BOOL bRefreshGrid = TRUE;

	MAP_GridCtrl_FieldAtrri::iterator itFieldAtrri = tableAttri.mapFeildAtrri.end();

	CString strFieldName = _T("");
	if(GetFieldIdByGridCol(strFieldName,m_nRClickHeadCol))
	{
		itFieldAtrri = tableAttri.mapFeildAtrri.find(strFieldName);
	}

	switch (id)
	{
	case IDM_DLGGRID_COL_SHOW            :
		{
			if (itFieldAtrri != tableAttri.mapFeildAtrri.end())
			{
				itFieldAtrri->second.isShow = !itFieldAtrri->second.isShow;
			}
		}
		break;
	case IDM_DLGGRID_COL_LOCK_NONE       :
		{
			if (itFieldAtrri != tableAttri.mapFeildAtrri.end())
			{
				if (0 == itFieldAtrri->second.iLock)
				{
					bRefreshGrid = FALSE;
				}
				else
				{
					//从锁定到不锁定
					//当前列索引值
					int nCurIndex = itFieldAtrri->second.iColIndex;
					if (1 == itFieldAtrri->second.iLock)
					{
						//从锁定到左侧到不锁定
						//最大一个锁定在左侧的列的索引值
						int nMaxLockLeftIndex = -1;

						//将所有锁定在左侧 索引大于当前项的列提前 当前项放在第一个非锁定项之前
						for (auto itSort = tableAttri.mapFeildAtrri.begin();itSort != tableAttri.mapFeildAtrri.end();itSort++)
						{
							//忽略不显示项
							if (!itSort->second.isShow)
							{
								continue;
							}

							if( itSort->second.iColIndex == nCurIndex )
							{
								//忽略当前项
								continue;
							}

							if (itSort->second.iColIndex > nCurIndex && 1 == itSort->second.iLock)
							{
								itSort->second.iColIndex--;
							}

							if (1 == itSort->second.iLock /*2 != itSort->second.iLock*/)
							{
								nMaxLockLeftIndex = itSort->second.iColIndex > nMaxLockLeftIndex ? itSort->second.iColIndex : nMaxLockLeftIndex;
							}
						}

						itFieldAtrri->second.iColIndex = nMaxLockLeftIndex + 1;
					}
					else if (2 == itFieldAtrri->second.iLock)
					{
						//从锁定到右侧到不锁定
						//当前列索引值
						//遍历所有列 获取到最后一个不锁定的列 将当前列索引放到该列后面
						//对锁定到右侧的列且列索引小于当前列的项的索引值++
						int nMaxNoLockIndex = -1;
						for (auto itSort = tableAttri.mapFeildAtrri.begin();itSort != tableAttri.mapFeildAtrri.end();itSort++)
						{
							if (!itSort->second.isShow)
							{
								continue;
							}
							if (itSort->second.iColIndex == nCurIndex)
							{
								//忽略当前项
								continue;
							}
							//当前项之前的锁定到右侧的项 顺序后移
							if (itSort->second.iColIndex < nCurIndex && 2 == itSort->second.iLock)
							{
								itSort->second.iColIndex++;
							}
							//最大的非锁定右侧项
							if (2 != itSort->second.iLock)
							{
								nMaxNoLockIndex = itSort->second.iColIndex > nMaxNoLockIndex ? itSort->second.iColIndex : nMaxNoLockIndex;
							}
						}
						itFieldAtrri->second.iColIndex = nMaxNoLockIndex + 1;
					}
					itFieldAtrri->second.iLock = 0;
				}
			}
		}
		break;
	case IDM_DLGGRID_COL_LOCK_LEFT       :
		{
			if (itFieldAtrri != tableAttri.mapFeildAtrri.end())
			{
				if (1 == itFieldAtrri->second.iLock)
				{
					bRefreshGrid = FALSE;
				}
				else
				{
					int nCurIndex = itFieldAtrri->second.iColIndex;
					if (0 == itFieldAtrri->second.iLock)
					{
						int iMaxLockLeft = -1;
						//从不锁定到锁定到左侧
						//从不锁定项开始讲所有索引项小于当前项的列索引值+1
						for (auto itSort = tableAttri.mapFeildAtrri.begin();itSort != tableAttri.mapFeildAtrri.end();itSort++)
						{
							if (!itSort->second.isShow)
							{
								continue;
							}

							//忽略当前项
							if (nCurIndex == itSort->second.iColIndex)
							{
								continue;
							}
							//当前项之前的不锁定的项 顺序后移
							if (itSort->second.iColIndex < nCurIndex && 0 == itSort->second.iLock)
							{
								itSort->second.iColIndex++;
							}
							//最大的非锁定项
							if (1 == itSort->second.iLock)
							{
								iMaxLockLeft = itSort->second.iColIndex > iMaxLockLeft ? itSort->second.iColIndex : iMaxLockLeft;
							}
						}

						itFieldAtrri->second.iColIndex = iMaxLockLeft + 1;
					}
					else if (2 == itFieldAtrri->second.iLock)
					{
						//从锁定到右侧到锁定到左侧
						int iMaxLockLeft = -1;
						//从不锁定到锁定到左侧
						//从不锁定项开始讲所有索引项小于当前项的列索引值+1
						for (auto itSort = tableAttri.mapFeildAtrri.begin();itSort != tableAttri.mapFeildAtrri.end();itSort++)
						{
							if (!itSort->second.isShow)
							{
								continue;
							}

							//忽略当前项
							if (nCurIndex == itSort->second.iColIndex)
							{
								continue;
							}
							//所有的小于当前项的 不锁定在左侧的项 顺序后移

							if (itSort->second.iColIndex < nCurIndex && 1 != itSort->second.iLock)
							{
								itSort->second.iColIndex++;
							}

							if (1 == itSort->second.iLock)
							{
								iMaxLockLeft = itSort->second.iColIndex > iMaxLockLeft ? itSort->second.iColIndex : iMaxLockLeft ;
							}
						}
						itFieldAtrri->second.iColIndex = iMaxLockLeft + 1;
					}

					itFieldAtrri->second.iLock = 1;
				}
			}
		}
		break;
	case IDM_DLGGRID_COL_LOCK_RIGHT      :
		{
			if (itFieldAtrri != tableAttri.mapFeildAtrri.end())
			{
				if (2 == itFieldAtrri->second.iLock)
				{
					bRefreshGrid = FALSE;
				}
				else
				{
					//当前索引项
					int nCurIndex = itFieldAtrri->second.iColIndex;
					int nMaxIndex = itFieldAtrri->second.iColIndex;

					//从不锁定到锁定到右侧
					for (auto itSort = tableAttri.mapFeildAtrri.begin();itSort != tableAttri.mapFeildAtrri.end();itSort++)
					{
						if (!itSort->second.isShow)
						{
							continue;
						}
						//忽略当前项
						if (nCurIndex == itSort->second.iColIndex)
						{
							continue;
						}
						//所有大于当前项索引值的项 顺序前移

                  nMaxIndex = itSort->second.iColIndex > nMaxIndex ? itSort->second.iColIndex : nMaxIndex;

						if (itSort->second.iColIndex > nCurIndex) 
						{
							itSort->second.iColIndex--;
						}						
					}

					itFieldAtrri->second.iColIndex = nCurIndex >= nMaxIndex ? nCurIndex : nMaxIndex;

					itFieldAtrri->second.iLock = 2;
				}
			}
		}
		break;
	case IDM_DLGGRID_COL_COUNT_NONE      :
		{
			if (itFieldAtrri != tableAttri.mapFeildAtrri.end())
			{
				itFieldAtrri->second.enColSumType = CB_enum_ColSumType_None ;
            if (m_bUserPaginationMode && emPM_DbSvr == m_emPMPaginationModeFlag)//数据库分页模式
            {
               GetOwner()->PostMessage(UM_ATTRI_FIELD_HAS_ADD_MSG,NULL,NULL);
            }            
			}
		}
		break;
	case IDM_DLGGRID_COL_COUNT_COUNT     :
		{
			if (itFieldAtrri != tableAttri.mapFeildAtrri.end())
			{
				itFieldAtrri->second.enColSumType = CB_enum_ColSumType_Count;
            if (m_bUserPaginationMode && emPM_DbSvr == m_emPMPaginationModeFlag)//数据库分页模式
            {
               GetOwner()->PostMessage(UM_ATTRI_FIELD_HAS_ADD_MSG,NULL,NULL);
            }
			}
		}
		break;
	case IDM_DLGGRID_COL_COUNT_SUM       :
		{
			if (itFieldAtrri != tableAttri.mapFeildAtrri.end())
			{
				itFieldAtrri->second.enColSumType = CB_enum_ColSumType_Sum;
            if (m_bUserPaginationMode && emPM_DbSvr == m_emPMPaginationModeFlag)//数据库分页模式
            {
               GetOwner()->PostMessage(UM_ATTRI_FIELD_HAS_ADD_MSG,NULL,NULL);
            }
			}
		}
		break;
	case IDM_DLGGRID_COL_COUNT_AVERAGE   :
		{
			if (itFieldAtrri != tableAttri.mapFeildAtrri.end())
			{
				itFieldAtrri->second.enColSumType = CB_enum_ColSumType_Average;
			}
		}
		break;
	case IDM_DLGGRID_EXPORTEXCEL://导出excel
		{
			bRefreshGrid = FALSE;
         UINT uRet = GetOwner()->SendMessage(UM_EXPORT_DATA_TO_EXCEL_MSG,0,0);
         if (0!=uRet)
         {
            return;
         }

			ASSERT(NULL != this);
         ExportExcel();	
		}
		break;
	case IDM_DLGGRID_READSTYLE  ://读取样式
		{
			ASSERT(IsWindow(this->GetSafeHwnd()));
			if (!IsWindow(GetSafeHwnd()))
			{
				return;
			}

			CFileDialog openDlg(true);
			openDlg.m_ofn.lpstrFilter = LPCTSTR(_T("XML文件(*.XML)\0*.XML\0"));
			openDlg.m_ofn.lpstrTitle = LPCTSTR(_T("请选择表格样式"));

			openDlg.m_ofn.Flags = openDlg.m_ofn.Flags | OFN_HIDEREADONLY | OFN_FILEMUSTEXIST;

			CString fileName;
			openDlg.m_ofn.lpstrFile = fileName.GetBuffer(MAX_PATH);
			openDlg.m_ofn.nMaxFile = MAX_PATH;
			if (IDOK != openDlg.DoModal())	return;
			fileName.ReleaseBuffer();
			CString strXmlPath = openDlg.GetPathName();

			if (!PathFileExists(strXmlPath))
			{
				theApp.OnShowDesktopAlert(_T("请选择需要打开的表格样式文件！"),TIP_COLOR_WARNING,TIP_TIME_DELAY);
				return;
			}

			if (!CGridCtrlTableAttributeOp::Instance()->ReadTableAttriFromXml(strXmlPath,tableAttri))
			{
				//当字段数量不一致 或者内容不一致可能会导致崩溃
				theApp.OnShowDesktopAlert(_T("样式读取失败！"),TIP_COLOR_WARNING,TIP_TIME_DELAY);
				return;
			}
		}
		break;
	case IDM_DLGGRID_SAVESTYLE  ://保存样式
		{
			bRefreshGrid = FALSE;
			ASSERT(IsWindow(this->GetSafeHwnd()));
			if (!IsWindow(GetSafeHwnd()))
			{
				return;
			}

			CString strXmlPath = _T("");
			CFileDialog saveDlg(false);
			saveDlg.m_ofn.lpstrFilter = LPCTSTR(_T("Excel File(*.xml)\0*.xml\0"));
			saveDlg.m_ofn.lpstrTitle = LPCTSTR(_T("导出样式"));
			saveDlg.m_ofn.Flags = saveDlg.m_ofn.Flags | OFN_HIDEREADONLY | OFN_CREATEPROMPT | OFN_PATHMUSTEXIST;   

			CString fileName;
			GetWindowText(fileName);
			if (!fileName.IsEmpty())
			{
				fileName += _T(".xml");
				CString backUpFileName = fileName;//备份一下供后面使用，不然会被saveDlg修改掉
				saveDlg.m_ofn.lpstrFile = fileName.GetBuffer(MAX_PATH);
				saveDlg.m_ofn.nMaxFile = MAX_PATH;
			}
			if (IDOK != saveDlg.DoModal())	return;
			fileName.ReleaseBuffer();
			strXmlPath = saveDlg.GetPathName();

			CString strExe = PathFindExtension(strXmlPath);
			strExe.MakeUpper();
			if (strExe.IsEmpty() || strExe != _T(".XML"))
			{
				strXmlPath += _T(".XML");
			}

			if (strXmlPath.IsEmpty())
			{
				theApp.OnShowDesktopAlert(_T("文件名不能为空！"),TIP_COLOR_WARNING,TIP_TIME_DELAY);
				return;
			}
			//theApp.ShowLoading();
			
			if (!IsWindow(this->GetSafeHwnd()))
			{
				ASSERT(FALSE);
				return;
			}

			S_GridCtrl_TableAttri tableAttri;
			if (GetGridAttriInfo(tableAttri))
			{
				CGridCtrlTableAttributeOp::Instance()->WriteTableAttriToXml(strXmlPath,tableAttri);
			}

			//theApp.CloseLoading();
			
		}
		break;
	case IDM_DLGGRID_GRID_FILTER         :
		{
			tableAttri.isShowSortBar = !tableAttri.isShowSortBar;
		}
		break;
	case IDM_DLGGRID_GRID_COUNT          :
		{
			tableAttri.isShowSumBar = !tableAttri.isShowSumBar;
         if (tableAttri.isShowSumBar && m_bUserPaginationMode && emPM_DbSvr == m_emPMPaginationModeFlag)//数据库分页模式
         {
            GetOwner()->PostMessage(UM_ATTRI_FIELD_HAS_ADD_MSG,NULL,NULL);
         }         
		}
		break;
	case IDM_DLGGRID_GRID_SORT           :
		{
			tableAttri.isAllowSort = !tableAttri.isAllowSort;
		}
		break;
	case IDM_DLGGRID_GRID_WHOLESEL       :
		{
			tableAttri.isWholeRowSelect = !tableAttri.isWholeRowSelect;
		}
		break;
	case IDM_DLGGRID_GRID_DRAGCOL        :
		{
			tableAttri.isEnableDragCol = !tableAttri.isEnableDragCol;
		}
		break;
	case IDM_DLGGRID_GRID_HORZPRINT      :
		{
			tableAttri.isPrintHengXiang = !tableAttri.isPrintHengXiang;
		}
		break;
	case IDM_DLGGRID_GRID_TITLEFILTER    :
		{
			tableAttri.isShowTitleFilter = !tableAttri.isShowTitleFilter;
		}
		break;
	case IDM_DLGGRID_GRID_MULTISEL       :
		{
			tableAttri.isMultiRowSelect = !tableAttri.isMultiRowSelect;
		}
		break;
	case IDM_DLGGRID_GRID_MULTISEL_NOLOSE:
		{
			tableAttri.IsMultiRowSelectNoLoseFocus = !tableAttri.IsMultiRowSelectNoLoseFocus;
		}
		break;
   case IDM_DLGGRID_GRID_UPDATESERVERSTYLE      :
      {
         tableAttri.isNoUpdateServerStyle = !tableAttri.isNoUpdateServerStyle;
      }
      break;
	case IDM_DLGGRID_PRINTPREV://打印预览
		{
			//bRefreshGrid = FALSE;
			//if (!IsWindow(this->GetSafeHwnd()))
			//{
			//	ASSERT(FALSE);
			//	return;
			//}

			//CString strFieldXml;
			//CString strDataXml;
			//CString strSumXml;
			//BOOL bRet = GetPrintDataXmlText(strFieldXml,strDataXml,strSumXml);
			//if (bRet)
			//{
			//	WaitCursorBegin();
			//	//使用xml字串流动态创建报表预览
			//	CoInitialize(NULL);    
			//	KDS_CSharpReport::IXtraReportPtr pMyXtraReport(__uuidof(KDS_CSharpReport::MyXtraReport)); 
			//	pMyXtraReport->LocalizerReport();

			//	CString strTitle = _T("");
			//	GetWindowText(strTitle);

			//	if (strTitle.IsEmpty())
			//	{
			//		strTitle.Format(_T("打印预览"));
			//	}

			//	S_GridCtrl_tableAttri tableAtrri;
			//	GetGridAttriInfo(tableAtrri);
			//	if (tableAtrri.isPrintHengXiang)//横向打印 yangjr 2017-9-19
			//	{
			//		pMyXtraReport->ShowNewLandscapePrintPreviewByXmlText(strTitle.GetBuffer(0),
			//			strFieldXml.GetBuffer(0), strDataXml.GetBuffer(0),strSumXml.GetBuffer(0));
			//	}else
			//	{
			//		pMyXtraReport->ShowNewPrintPreviewByXmlText(strTitle.GetBuffer(0),
			//			strFieldXml.GetBuffer(0), strDataXml.GetBuffer(0),strSumXml.GetBuffer(0));
			//	}
			//}

		}
		break;
	case IDM_DLGGRID_STYLE               :
		{
			//整体表格样式设置
			CDlgGridCtrlTableStyle dlg;
			dlg.SetTableAttriFileNameAndData(m_tableStyleFileName,tableAttri);
         int iBackupPageRows = tableAttri.iPageRows;
         if (iBackupPageRows<50)
         {
            iBackupPageRows = 50;
         }         
			if (m_bUseNewAttri)
			{
				if(IDOK == dlg.DoModal())
				{
					//theApp.ShowLoading();

					tableAttri = dlg.GetTableAttriData();
					BOOL bHasAdd = dlg.HasAddShowField();
					if (bHasAdd)
					{	
						BOOL bPost = FALSE;
						std::vector<CString> vecNeedful;
						BOOL bNeedful = GetNeedfulPackageFieldId(vecNeedful);
						if (!bNeedful)
						{
							bPost = TRUE;
						}
						SetGridAttriInfoNew(tableAttri);
						if (!bPost)
						{
							std::vector<CString> vecNeedful2;
							BOOL bNeedful2 = GetNeedfulPackageFieldId(vecNeedful2,TRUE);
							if (!bNeedful2)
							{
								bPost = FALSE;
							}
							else
							{
								auto it2=vecNeedful2.begin();
								for (;it2!=vecNeedful2.end();++it2)
								{
									auto itFind = std::find(vecNeedful.begin(),
										vecNeedful.end(),*it2);
									if (itFind == vecNeedful.end())
									{
										bPost = TRUE;
										break;
									}
								}
							}
						}
                  if (m_bUserPaginationMode && emPM_DbSvr == m_emPMPaginationModeFlag)//数据库分页模式
                  {
                     if (tableAttri.isShowSumBar)
                     {
                        if (!bPost)
                        {
                           std::map<CString,ENUM_COLSUMTYPE> mapTongJiData;
                           GetTongJiDataByAttri(tableAttri,mapTongJiData);
                           for (auto iterCol=mapTongJiData.begin();iterCol!=mapTongJiData.end();++iterCol)
                           {			
                              auto iterFindCol = m_mapTongJiValue.find(iterCol->first);
                              if (iterFindCol == m_mapTongJiValue.end())//有新的统计字段
                              {//需要通知外部刷新
                                 bPost = TRUE;
                                 break;
                              }else
                              {
                                 auto iterFindAttri = m_tableAttri.mapFeildAtrri.find(iterCol->first);
                                 if (iterFindAttri == m_tableAttri.mapFeildAtrri.end())
                                 {
                                    bPost = TRUE;
                                    break;
                                 }
                                 if (iterFindCol->second != iterFindAttri->second.enColSumType)
                                 {//相同字段统计方式改变了需要通知外部刷新
                                    bPost = TRUE;
                                    break;
                                 }
                              }
                           }
                        }
                     }
                     if (iBackupPageRows != tableAttri.iPageRows) //分页模式每页行数变化了
                     {
                        bPost = TRUE;
                     }
                  }
                                    

						if (bPost)
						{
							GetOwner()->PostMessage(UM_ATTRI_FIELD_HAS_ADD_MSG,NULL,NULL);
						}
						else
						{
							RefreshGridCtrlInfoNew();
						}	
					}
					else
               {
                  SetGridAttriInfoNew(tableAttri);
                  RefreshGridCtrlInfoNew();
               }
					//theApp.CloseLoading();
				}
				return;
			}
			else
			{
				if(IDOK != dlg.DoModal())
				{
					bRefreshGrid = FALSE;
				}
				else
				{
					tableAttri = dlg.GetTableAttriData();
				}
			}
			
		}
		break;
	case IDM_TurnOverSelect:		//反选 add by lida 2018/03/15
		{
			//AfxMessageBox(_T("1111"));
			SetMultiSelectTurnOver();
			return;
		}
		break;
   case IDM_DLGGRID_UPDATE_STYLE://更新表格样式
      {
         //theApp.ShowLoading();
         //S_GridCtrl_tableAttri attri = m_tableAttri;
         //if(CGridCtrlTableAttributeOp::Instance()->GetServerStyleAndUpdateLocal(m_tableStyleFileName , attri))
         //{
         //   SetGridAttriInfoNew(attri);
         //   RefreshGridCtrlInfoNew();
         //}         
         //theApp.CloseLoading();
         return;
      }
      break;
   case IDM_DLGGRID_STYLE_SAVETOSERVER://保存样式到服务器 yangjr 2018/5/29
      {
  
         return;
      }
      break;
   case IDM_DLGGRID_GRID_INITUSERSTYLE://初始化表格样式 yangjr 2018/5/29
      {
         S_GridCtrl_TableAttri tableAttri;
         if(CGridCtrlTableAttributeOp::Instance()->InitUserTableAttri(m_tableStyleFileName,tableAttri))        
         {    
            tableAttri.strUpdateTime = m_tableAttri.strUpdateTime;//更新日期不要初始化掉 yangjr 2018/6/12
            int iBackupPageRows = m_tableAttri.iPageRows;
            if (iBackupPageRows<50)
            {
               iBackupPageRows = 50;
            }
            //theApp.ShowLoading();
            BOOL bHasAddShowField = FALSE;
            std::vector<CString/*strFieldId*/> vecOldShowFieldId;
            for (auto it=m_tableAttri.mapFeildAtrri.begin();
               it!=m_tableAttri.mapFeildAtrri.end(); ++it)
            {
               if (it->second.isShow)
               {
                  vecOldShowFieldId.push_back(it->first);
               }
            }
            for (auto it=tableAttri.mapFeildAtrri.begin();
               it!=tableAttri.mapFeildAtrri.end(); ++it)
            {
               if (it->second.isShow)
               {
                  auto itAddShow = std::find(vecOldShowFieldId.begin(),
                     vecOldShowFieldId.end(),it->first);
                  if (itAddShow == vecOldShowFieldId.end())
                  {
                     bHasAddShowField = TRUE;
                     break;
                  }
               }
            }               
       
            if (bHasAddShowField)
            {	
               BOOL bPost = FALSE;
               std::vector<CString> vecNeedful;
               BOOL bNeedful = GetNeedfulPackageFieldId(vecNeedful);
               if (!bNeedful)
               {
                  bPost = TRUE;
               }
               SetGridAttriInfoNew(tableAttri);
               if (!bPost)
               {
                  std::vector<CString> vecNeedful2;
                  BOOL bNeedful2 = GetNeedfulPackageFieldId(vecNeedful2,TRUE);
                  if (!bNeedful2)
                  {
                     bPost = FALSE;
                  }
                  else
                  {
                     auto it2=vecNeedful2.begin();
                     for (;it2!=vecNeedful2.end();++it2)
                     {
                        auto itFind = std::find(vecNeedful.begin(),
                           vecNeedful.end(),*it2);
                        if (itFind == vecNeedful.end())
                        {
                           bPost = TRUE;
                           break;
                        }
                     }
                  }
               }
               if (m_bUserPaginationMode && emPM_DbSvr == m_emPMPaginationModeFlag)//数据库分页模式
               {                  
                  if (iBackupPageRows != tableAttri.iPageRows) //分页模式每页行数变化了
                  {
                     bPost = TRUE;
                  }
               }

               if (bPost)
               {
                  GetOwner()->PostMessage(UM_ATTRI_FIELD_HAS_ADD_MSG,NULL,NULL);
               }
               else
               {
                  RefreshGridCtrlInfoNew();
               }	
            }
            else
            {
               SetGridAttriInfoNew(tableAttri);
               RefreshGridCtrlInfoNew();
            }
            //theApp.CloseLoading();
            theApp.OnShowDesktopAlert(_T("初始化用户表格样式成功！"),TIP_COLOR_SUC,TIP_TIME_DELAY);
         }else
         {
            theApp.OnShowDesktopAlert(_T("初始化用户表格样式失败！"),TIP_COLOR_WARNING,2);
         }
         return;
      }
      break;
	}
	
	if (bRefreshGrid)
	{
		//theApp.ShowLoading();
		if (m_bUseNewAttri)
		{
			SetGridAttriInfoNew(tableAttri);
			RefreshGridCtrlInfoNew();
		}
		else
		{
			SetGridAttriInfo(tableAttri);
			RefreshGridCtrlInfo();
		}
		
		//theApp.CloseLoading();
	}
}

CString CDlgBCGGrid::GetColName(int nCol)
{
	if (m_pBCGGrid && IsWindow(m_pBCGGrid->GetSafeHwnd()))
	{
		//if (nCol > -1 && nCol < m_pBCGGrid->GetColumnCount() && nCol < m_mapCol_Name_ID.size())
		//{
		//	CString strColName = m_pBCGGrid->GetColumnName(nCol);
		//	auto itr_id = m_mapCol_Name_ID.find(strColName);
		//	if (itr_id != m_mapCol_Name_ID.end())
		//		return itr_id->second;
		//	else
		//		return _T("");
		//}

		if (nCol > -1 && nCol < m_pBCGGrid->GetColumnCount() && nCol < m_mapColWithFieldId.size())
		{
			auto itr_col_id = m_mapColWithFieldId.find(nCol);
			if (itr_col_id != m_mapColWithFieldId.end())
			{
				return itr_col_id->second;
			}
			else
				return _T("");
		}

	}
	return _T("ERROR");
}

CString CDlgBCGGrid::GetColShowName(int nCol)
{
	if (m_pBCGGrid && IsWindow(m_pBCGGrid->GetSafeHwnd()))
	{
		if (nCol > -1 && nCol < m_pBCGGrid->GetColumnCount())
		{
			return m_pBCGGrid->GetColumnName(nCol);
		}
	}
	return _T("ERROR");
}

//设置必要的字段		by WangZY 2018/02/01
void CDlgBCGGrid::SetNeedfulFieldId(std::vector<CString /*strFieldId*/> vecNeedfulFieldId)
{
	m_vecNeedfulFieldId = vecNeedfulFieldId;
}

void CDlgBCGGrid::RefreshBCGGridCtrl()
{
	if (m_pBCGGrid && IsWindow(m_pBCGGrid->GetSafeHwnd()))
	{
		m_pBCGGrid->AdjustLayout();
	}
}

//刷新统计行信息		by WangZY 2017/11/23
BOOL CDlgBCGGrid::RefreshGridStatisticRow(CQLBCGGridCtrl *pGrid,BOOL bFenYeModeSvrGridTongJi)
{
	if (nullptr == pGrid)
	{
		return FALSE;
	}
	S_GridCtrl_TableAttri &tableAttri = m_tableAttri;
	if(!tableAttri.isShowSumBar)
	{
		return FALSE;
	}
	BOOL bShowSumBar = pGrid->GetColumnsInfo().IsEnableShowFooterRow();
	if (!bShowSumBar)
	{
		return FALSE;
	}

	BOOL bNeedShowStatisticRow = TRUE;	//是否需要显示统计行
	auto itAttri = tableAttri.mapFeildAtrri.begin();
	for (; itAttri!=tableAttri.mapFeildAtrri.end(); ++itAttri)
	{
		S_GridCtrl_FieldAtrri *pAttri = &itAttri->second;
		if(!pAttri->isShow)
		{
			continue;
		}

		auto itField = m_mapColID.find(pAttri->strColID);
		if (itField == m_mapColID.end())
		{
			continue;
		}

		int nCol = itField->second;
		if (CB_enum_ColSumType_None == pAttri->enColSumType )
		{
			pGrid->GetColumnsInfo().SetColumnFooterValue(nCol, _T(""));
			
			continue;	//无统计
		}
      BOOL bFenYeDBSvrTongJi = FALSE;
      std::map<CString,CString>::iterator itTongJi = m_mapTongJiValue.end();
      if (!bFenYeModeSvrGridTongJi && m_bUserPaginationMode && emPM_DbSvr == m_emPMPaginationModeFlag)//数据库分页模式
      {
         itTongJi = m_mapTongJiValue.find(pAttri->strColID);
         if(itTongJi == m_mapTongJiValue.end())
         {
            continue;	//无统计
         }
         bFenYeDBSvrTongJi = TRUE;
      }      

		bNeedShowStatisticRow = TRUE;
		
      if (!bFenYeDBSvrTongJi) //非数据库分页模式 
      {
         int nSumCount = pGrid->GetTotalRowCount(TRUE);
         int nStartRow = 0;
         int nRowCount = pGrid->GetRowCount();
         //计数
         if (CB_enum_ColSumType_Count == pAttri->enColSumType)
         {
            CString strText;
            strText.Format(_T("计数=%d"),nSumCount);
            pGrid->GetColumnsInfo().SetColumnFooterValue(nCol, strText);
            continue;
         }

         if (CB_enum_ColSumType_Average != pAttri->enColSumType
            &&CB_enum_ColSumType_Sum != pAttri->enColSumType)
         {
            continue;
         }

         ENUM_FIELDTYPE_DATA fieldDataType = CB_enum_FieldData_Int;
         if (m_tableData.size()>0)
         {
            auto itData = m_tableData.begin()->second.find(pAttri->strColID);
            if (itData !=m_tableData.begin()->second.end())
            {
               fieldDataType = itData->second.fieldDataType;
            }
         }

         double lfSum  = 0.0f;	//总和
         for (int nRow=0; nRow<nRowCount; nRow++)
         {
            CBCGPGridRow *pRow = pGrid->GetRow(nRow);
            if (!pGrid->IsRowVisible(pRow))
            {
               continue;
            }

            _bstr_t strValue = pRow->GetItem(nCol)->GetValue();

            lfSum += _ttof(strValue);
         }

         if (CB_enum_ColSumType_Average == pAttri->enColSumType)
         {
            CString strText;
            nSumCount = nSumCount==0?1:nSumCount;
            double fSumAve = lfSum/nSumCount;
            int iSumAve = int(lfSum/nSumCount);
            switch (fieldDataType)
            {
            case CB_enum_FieldData_Int:
               {
                  strText.Format(_T("平均=%d"),iSumAve);
               }
               break;
            case CB_enum_FieldData_Double2Point:
               {
                  strText.Format(_T("平均=%.02f"),fSumAve);
               }
               break;
            case CB_enum_FieldData_Double3Point:
               {
                  strText.Format(_T("平均=%.03f"),fSumAve);
               }
               break;
            case CB_enum_FieldData_Double4Point:
               {
                  strText.Format(_T("平均=%.04f"),fSumAve);
               }
               break;
            default:
               {
                  strText.Format(_T("平均=%.04f"),fSumAve);
                  strText = RnString::RemoveLastZero(strText);
               }
               break;
            }
            pGrid->GetColumnsInfo().SetColumnFooterValue(nCol, strText);

            continue;
         }

         if (CB_enum_ColSumType_Sum == pAttri->enColSumType)
         {
            CString strText;

            //const CString CS_SUM = _T("合计="); 
            const CString CS_SUM = _T("");            
            switch (fieldDataType)
            {
            case CB_enum_FieldData_Int:
               {
                  strText.Format(_T("%s%d"),CS_SUM,(int)lfSum);
               }
               break;
            case CB_enum_FieldData_Double2Point:
               {
                  strText.Format(_T("%s%.02f"),CS_SUM,lfSum);
               }
               break;
            case CB_enum_FieldData_Double3Point:
               {
                  strText.Format(_T("%s%.03f"),CS_SUM,lfSum);
               }
               break;
            case CB_enum_FieldData_Double4Point:
               {
                  strText.Format(_T("%s%.04f"),CS_SUM,lfSum);
               }
               break;
            default:
               {
                  strText.Format(_T("%s%.4f"),CS_SUM,lfSum);
                  strText = RnString::RemoveLastZero(strText);
               }
               break;
            }
            pGrid->GetColumnsInfo().SetColumnFooterValue(nCol, strText);

            continue;
         }
      }
      else //数据库分页模式
      {      
         int iSum = _ttoi(itTongJi->second);
         //计数
         if (CB_enum_ColSumType_Count == pAttri->enColSumType)
         {
            CString strText;
            strText.Format(_T("计数=%d"),iSum);
            pGrid->GetColumnsInfo().SetColumnFooterValue(nCol, strText);
            continue;
         }
         if (CB_enum_ColSumType_Average != pAttri->enColSumType
            &&CB_enum_ColSumType_Sum != pAttri->enColSumType)
         {
            continue;
         }

         ENUM_FIELDTYPE_DATA fieldDataType = CB_enum_FieldData_Int;
         if (m_tableData.size()>0)
         {
            auto itData = m_tableData.begin()->second.find(pAttri->strColID);
            if (itData !=m_tableData.begin()->second.end())
            {
               fieldDataType = itData->second.fieldDataType;
            }
         }            

         double lfSum = _ttof(itTongJi->second);         
         //求平均值
         if (CB_enum_ColSumType_Average == pAttri->enColSumType)
         {
            CString strText; 

            switch (fieldDataType)
            {
            case CB_enum_FieldData_Int:
               {
                  strText.Format(_T("平均=%d"),iSum);
               }
               break;
            case CB_enum_FieldData_Double2Point:
               {
                  strText.Format(_T("平均=%.02f"),lfSum);
               }
               break;
            case CB_enum_FieldData_Double3Point:
               {
                  strText.Format(_T("平均=%.03f"),lfSum);
               }
               break;
            case CB_enum_FieldData_Double4Point:
               {
                  strText.Format(_T("平均=%.04f"),lfSum);
               }
               break;
            default:
               {
                  strText.Format(_T("平均=%s"),itTongJi->second);                 
               }
               break;
            }
            pGrid->GetColumnsInfo().SetColumnFooterValue(nCol, strText);
            continue;
         }

         if (CB_enum_ColSumType_Sum == pAttri->enColSumType)
         {
            CString strText;

            //const CString CS_SUM = _T("合计="); 
            const CString CS_SUM = _T(""); 

            switch (fieldDataType)
            {
            case CB_enum_FieldData_Int:
               {
                  strText.Format(_T("%s%d"),CS_SUM,iSum);
               }
               break;
            case CB_enum_FieldData_Double2Point:
               {
                  strText.Format(_T("%s%.02f"),CS_SUM,lfSum);
               }
               break;
            case CB_enum_FieldData_Double3Point:
               {
                  strText.Format(_T("%s%.03f"),CS_SUM,lfSum);
               }
               break;
            case CB_enum_FieldData_Double4Point:
               {
                  strText.Format(_T("%s%.04f"),CS_SUM,lfSum);
               }
               break;
            default:
               {                  
                  strText.Format(_T("%s%s"),CS_SUM,itTongJi->second);
               }
               break;
            }
            pGrid->GetColumnsInfo().SetColumnFooterValue(nCol, strText);
            continue;
         }
      }
	}
	
	pGrid->GetColumnsInfo().SetEnableShowFooterRow(bNeedShowStatisticRow);
	if (bNeedShowStatisticRow)
	{
		pGrid->SetGridFooterHeight(m_tableAttri.nDataRowHeight);
	}
	else
	{
		pGrid->SetGridFooterHeight(0);
	}
	pGrid->AdjustLayout();
   if (!(m_bUserPaginationMode && emPM_DbSvr == m_emPMPaginationModeFlag))//非数据库分页模式
   {
	   SetFootValue_CheckNum(GetCheckRowNum());	//刷新check统计数量
   }

	return TRUE;
}

void CDlgBCGGrid::SetFootValue_CheckNum(int k)
{
	if(!m_tableAttri.isShowSumBar)
	{
		return ;
	}

	//取列的顺序
	int iFirstColID = -1;
	const int nColumnCount = m_pBCGGrid->GetColumnCount ();
	if (nColumnCount > 0)
	{
		int* aColumnsOrder = new int [nColumnCount];
		memset (aColumnsOrder, -1, nColumnCount * sizeof (int));
		m_pBCGGrid->GetColumnsInfo().GetColumnOrderArray((LPINT) aColumnsOrder, nColumnCount);
		iFirstColID	= aColumnsOrder[0];
	}
	//取列的顺序 end

	CString strNewInfo = _T("");
	CString strText = _T("");
	CRect rt;
	rt = m_pBCGGrid->GetGridFooterRect();

	if (m_lastShowCheckRowCount >= 0 && iFirstColID >= 0 && m_lastShowCheckRowCount != iFirstColID)
	{
		//把旧的刷回去
		strText = m_pBCGGrid->GetColumnsInfo().GetColumnFooterValue(m_lastShowCheckRowCount);
		int ipos = strText.ReverseFind(',');
		strText = strText.Right(strText.GetLength()-ipos-1);
		m_pBCGGrid->GetColumnsInfo().SetColumnFooterValue(m_lastShowCheckRowCount, strNewInfo+strText);
		m_pBCGGrid->InvalidateRect(rt);
	}

	if (iFirstColID < 0)
	{
		return;
	}

	strText = m_pBCGGrid->GetColumnsInfo().GetColumnFooterValue(iFirstColID);
	if (k > 1)
	{
		if (strText.IsEmpty())
		{
			strNewInfo.Format(_T("选中(%d) "),k);
		}
		else
		{
			strNewInfo.Format(_T("选中(%d),"),k);
			int ipos = strText.ReverseFind(',');
			if (ipos < 0)
			{
				ipos = strText.ReverseFind(' ');
			}
			strText = strText.Right(strText.GetLength()-ipos-1);	
			if (strText.IsEmpty())
			{
				strNewInfo.Format(_T("选中(%d) "),k);
			}
		}	
	}
	else
	{
		int ipos = strText.ReverseFind(',');
		if (ipos < 0)
		{
			ipos = strText.ReverseFind(' ');
		}
		strText = strText.Right(strText.GetLength()-ipos-1);
	}
	m_pBCGGrid->GetColumnsInfo().SetColumnFooterValue(iFirstColID, strNewInfo+strText);
	m_pBCGGrid->InvalidateRect(rt);
	m_lastShowCheckRowCount = iFirstColID;
}

LRESULT CDlgBCGGrid::OnGrid_ItemHeadRClick(WPARAM wParam, LPARAM lParam)
{
	m_nRClickHeadCol = (int)lParam;

	if (/*-1 != m_nRClickHeadCol &&*/ m_bEnableColHeadMenu)
	{
		CPoint ptCursor;
		if(GetCursorPos(&ptCursor))
		{
			//弹出菜单按钮
			CMenu Menu; 
			VERIFY(Menu.LoadMenu(IDR_MENU_GRID_COLHEAD));//加载菜单资源
			CMenu* pPopup = Menu.GetSubMenu(0); 
			ASSERT(pPopup != NULL);

         if (m_tableAttri.isMultiRowSelect == false)
         {
            pPopup->DeleteMenu(IDM_TurnOverSelect,MF_BYCOMMAND);
         }
         //if (0 != theApp.m_objDBPerson.m_strUserDuty.CompareNoCase(_T("超级管理员")))
         //{
         //   pPopup->DeleteMenu(IDM_DLGGRID_STYLE_SAVETOSERVER,MF_BYCOMMAND);
         //}

			//根据当前的属性 设置弹出菜单的对应勾选项
			//筛选栏
			pPopup->CheckMenuItem(IDM_DLGGRID_GRID_FILTER,MF_BYCOMMAND | ( m_tableAttri.isShowSortBar == true ? MF_CHECKED : MF_UNCHECKED));
			//合计栏
			pPopup->CheckMenuItem(IDM_DLGGRID_GRID_COUNT,MF_BYCOMMAND | ( m_tableAttri.isShowSumBar == true ? MF_CHECKED : MF_UNCHECKED));
			//允许排序
			pPopup->CheckMenuItem(IDM_DLGGRID_GRID_SORT,MF_BYCOMMAND | ( m_tableAttri.isAllowSort == true ? MF_CHECKED : MF_UNCHECKED));
			//整行选择
			pPopup->CheckMenuItem(IDM_DLGGRID_GRID_WHOLESEL,MF_BYCOMMAND | ( m_tableAttri.isWholeRowSelect == true ? MF_CHECKED : MF_UNCHECKED));
			//列标题拖动
			pPopup->CheckMenuItem(IDM_DLGGRID_GRID_DRAGCOL,MF_BYCOMMAND | ( m_tableAttri.isEnableDragCol == true ? MF_CHECKED : MF_UNCHECKED));
			//横向打印
			pPopup->CheckMenuItem(IDM_DLGGRID_GRID_HORZPRINT,MF_BYCOMMAND | ( m_tableAttri.isPrintHengXiang == true ? MF_CHECKED : MF_UNCHECKED));
			//标题过滤
			pPopup->CheckMenuItem(IDM_DLGGRID_GRID_TITLEFILTER,MF_BYCOMMAND | ( m_tableAttri.isShowTitleFilter == true ? MF_CHECKED : MF_UNCHECKED));
			//多行选择
			pPopup->CheckMenuItem(IDM_DLGGRID_GRID_MULTISEL,MF_BYCOMMAND | ( m_tableAttri.isMultiRowSelect == true ? MF_CHECKED : MF_UNCHECKED));
			//多行选择不失焦点
			pPopup->CheckMenuItem(IDM_DLGGRID_GRID_MULTISEL_NOLOSE,MF_BYCOMMAND | ( m_tableAttri.IsMultiRowSelectNoLoseFocus == true ? MF_CHECKED : MF_UNCHECKED));
         //更新服务器表格样式
         pPopup->CheckMenuItem(IDM_DLGGRID_GRID_UPDATESERVERSTYLE,MF_BYCOMMAND | ( m_tableAttri.isNoUpdateServerStyle == false ? MF_CHECKED : MF_UNCHECKED));

			//列属性设置
			if (-1 != m_nRClickHeadCol)
			{
				CString strFieldName = _T("");
				if(GetFieldIdByGridCol(strFieldName,m_nRClickHeadCol))
				{
					//获取选中的列的名称
					auto itFieldAtrri = m_tableAttri.mapFeildAtrri.find(strFieldName);
					if (itFieldAtrri != m_tableAttri.mapFeildAtrri.end())
					{
						//显示
						pPopup->CheckMenuItem(IDM_DLGGRID_COL_SHOW         ,MF_BYCOMMAND | ( itFieldAtrri->second.isShow == true ? MF_CHECKED : MF_UNCHECKED));
						//锁定-无
						pPopup->CheckMenuItem(IDM_DLGGRID_COL_LOCK_NONE    ,MF_BYCOMMAND | ( itFieldAtrri->second.iLock == 0 ? MF_CHECKED : MF_UNCHECKED));
						//锁定-左侧
						pPopup->CheckMenuItem(IDM_DLGGRID_COL_LOCK_LEFT    ,MF_BYCOMMAND | ( itFieldAtrri->second.iLock == 1 ? MF_CHECKED : MF_UNCHECKED));
						//锁定-右侧
						pPopup->CheckMenuItem(IDM_DLGGRID_COL_LOCK_RIGHT   ,MF_BYCOMMAND | ( itFieldAtrri->second.iLock == 2 ? MF_CHECKED : MF_UNCHECKED));
						//合计-无
						pPopup->CheckMenuItem(IDM_DLGGRID_COL_COUNT_NONE   ,MF_BYCOMMAND | ( itFieldAtrri->second.enColSumType == CB_enum_ColSumType_None ? MF_CHECKED : MF_UNCHECKED));
						//合计-计数
						pPopup->CheckMenuItem(IDM_DLGGRID_COL_COUNT_COUNT  ,MF_BYCOMMAND | ( itFieldAtrri->second.enColSumType == CB_enum_ColSumType_Count ? MF_CHECKED : MF_UNCHECKED));
						//合计-求和
						pPopup->CheckMenuItem(IDM_DLGGRID_COL_COUNT_SUM    ,MF_BYCOMMAND | ( itFieldAtrri->second.enColSumType == CB_enum_ColSumType_Sum ? MF_CHECKED : MF_UNCHECKED));
						//合计-平均值
						pPopup->CheckMenuItem(IDM_DLGGRID_COL_COUNT_AVERAGE,MF_BYCOMMAND | ( itFieldAtrri->second.enColSumType == CB_enum_ColSumType_Average ? MF_CHECKED : MF_UNCHECKED));
					}
				}
			}
			else
			{
				//禁用列选项
				pPopup->EnableMenuItem(2,MF_BYPOSITION|MF_DISABLED);
				pPopup->EnableMenuItem(3,MF_BYPOSITION|MF_DISABLED);
				pPopup->EnableMenuItem(4,MF_BYPOSITION|MF_DISABLED);
			}

			CPoint point;
			GetCursorPos(&point);
			theApp.OnShowCMFCPopupMenu(this,pPopup,point);
		}
	}
	return 0;
}

//销毁时保存表格样式 yangjr 2017-12-20
void CDlgBCGGrid::OnDestroy()
{
   if (nullptr != m_pBCGGrid)
   {
      if (!m_tableStyleFileName.IsEmpty())
      {
         SaveAtrriToXml(m_tableStyleFileName);
      }      
   }

   CBCGPDialog::OnDestroy();
}

BOOL CDlgBCGGrid::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam==VK_ESCAPE)//Esc
		{

		}
		else if (pMsg->wParam == VK_SHIFT)
		{
			if (m_bKeyShiftDown == FALSE)
				m_bKeyShiftDown = TRUE;

	
		}
		else if (pMsg->wParam == VK_CONTROL)
		{
			if (m_bKeyCtrlDown == FALSE)
				m_bKeyCtrlDown = TRUE;
		}

		//!!!这下面三行代码不要掉，目前是为了修改上下左右键会跳两行（格）的问题，而注释掉，
		//但之前不知道是谁因为什么原因而加这个代码，故先保留!!!		by WangZY 2018/06/01
		//if (IsWindow(m_pBCGGrid->GetSafeHwnd()))
		//{
		//	::SendMessage(m_pBCGGrid->GetSafeHwnd(),WM_KEYDOWN,pMsg->wParam,pMsg->lParam);
		//}

      auto pOwner = GetOwner();
      if ( NULL != pOwner && IsWindow(pOwner->GetSafeHwnd()))
      {
         ::SendMessage(pOwner->GetSafeHwnd(),WM_KEYDOWN,pMsg->wParam,pMsg->lParam);
      }
	}
	else if (pMsg->message == WM_KEYUP)
	{
		if (pMsg->wParam == VK_SHIFT)
		{
			if (m_bKeyShiftDown == TRUE)
				m_bKeyShiftDown = FALSE;
		}
		else if (pMsg->wParam == VK_CONTROL)
		{
			if (m_bKeyCtrlDown == TRUE)
				m_bKeyCtrlDown = FALSE;
		}

		if (IsWindow(m_pBCGGrid->GetSafeHwnd()))
		{
			::SendMessage(m_pBCGGrid->GetSafeHwnd(),WM_KEYUP,pMsg->wParam,pMsg->lParam);
		}
   }else if (pMsg->message == WM_RBUTTONDOWN )
   {
      //if (IsWindow(m_pBCGGrid->GetSafeHwnd()))
      //{         
      //   CRect rect;
      //   m_pBCGGrid->GetWindowRect(&rect);
      //   CPoint  pt;
      //   GetCursorPos(&pt);

      //   if (rect.PtInRect(pt))
      //   {
      //      m_pBCGGrid->SetFocus();
      //      bool flag = false;
      //      for (auto iterCol = m_tableAttri.mapFeildAtrri.begin();iterCol != m_tableAttri.mapFeildAtrri.end();++iterCol)
      //      {
      //         if (iterCol->second.isShow)
      //         {
      //            flag = true;
      //            break;
      //         }
      //      }
      //      if (!flag)
      //      {
      //         //::SendMessage(m_pBCGGrid->GetSafeHwnd(),WM_LBUTTONDOWN,pMsg->wParam,pMsg->lParam);
      //         AfxGetMainWnd()->SendMessage(WM_LBUTTONUP,pMsg->wParam,pMsg->lParam);
      //         ::SendMessage(m_pBCGGrid->GetSafeHwnd(),pMsg->message,pMsg->wParam,pMsg->lParam);
      //         return FALSE;
      //      }            
      //   }        
      //            
      //}
   }

	return CBCGPDialog::PreTranslateMessage(pMsg);
}

void CDlgBCGGrid::SetMulRowSelectCheck(BOOL bCheck)
{
	const int nRowCounts =  m_pBCGGrid->GetRowCount();
	CBCGPGridRow* pRow = NULL;
	for (int irow =0; irow < nRowCounts; ++irow)
	{
		pRow = m_pBCGGrid->GetRow(irow);
		if (pRow && m_pBCGGrid->IsRowVisible(pRow))
		{
			if (pRow->IsSelected())
			{
				pRow->SetCheck(bCheck);
			}
         else
         {
            pRow->SetCheck(!bCheck);
         }
		}
	}
	m_pBCGGrid->Invalidate();
}

void CDlgBCGGrid::SetHeaderCheckBoxState(BOOL bCheck)
{
	if (nullptr != m_pBCGGrid)
	{
		m_pBCGGrid->GetColumnsInfo().SetCheckBoxState(bCheck);
	}
}

void CDlgBCGGrid::GetRow_Col_Num(int& iRow,int& iCol)
{
	iRow =  m_pBCGGrid->GetRowCount();		//行数
	iCol =	m_pBCGGrid->GetColumnCount();	//列数
}

//设置某列标题头过滤		by WangZY 2018/03/07
BOOL CDlgBCGGrid::EnableFilterColumns(__in vector<CString/*strFieldId*/> vecFieldIds,
	__in BOOL bEnable/*=TRUE */)
{
	//throw std::logic_error("The method or operation is not implemented.");
	if (bEnable)
	{
		for (auto it=vecFieldIds.begin(); it!=vecFieldIds.end(); ++it)
		{
			auto itFind = std::find(m_vecFilterId.begin(), m_vecFilterId.end(), *it);
			if (itFind == m_vecFilterId.end())
			{
				m_vecFilterId.push_back(*it);
			}
		}
	}
	else
	{
		for (auto it=vecFieldIds.begin(); it!=vecFieldIds.end(); ++it)
		{
			auto itFind = std::find(m_vecFilterId.begin(), m_vecFilterId.end(), *it);
			if (itFind != m_vecFilterId.end())
			{
				m_vecFilterId.erase(itFind);
			}
		}
	}

	if (m_pBCGGrid != nullptr)
	{
		bool bFilter = bEnable?true:false;
		for (auto itId=vecFieldIds.begin(); itId!=vecFieldIds.end(); ++itId)
		{
			auto it = m_mapColID.find(*itId);
			if (it != m_mapColID.end())
			{
				m_pBCGGrid->GetColumnsInfo().SetColumnEnableTitleFilter(it->second,bFilter);
			}
		}
	}

	return TRUE;
}

//设置标题过滤自定义列表的接口		by WangZY 2018/03/07
BOOL CDlgBCGGrid::SetColumnFilterList(__in CString strFieldId,
	__in const vector<CString> &vecLst)
{
	auto itInfo = m_mapFilterListInfo.find(strFieldId);
	if (itInfo != m_mapFilterListInfo.end())
	{
		itInfo->second = vecLst;
	}
	else
	{
		m_mapFilterListInfo.insert(
			map<CString,vector<CString>>::value_type(strFieldId,vecLst));
	}

	if (m_pBCGGrid != nullptr)
	{
		auto it = m_mapColID.find(strFieldId);
		if (it != m_mapColID.end())
		{
			CStringList lst;
			for (auto itLst=vecLst.begin();itLst!=vecLst.end();++itLst)
			{
				lst.AddTail(*itLst);
			}
			
			m_pBCGGrid->m_infoFilter.AddColumnFilterList(it->second, lst);

			return TRUE;
		}
	}

	return TRUE;
}

//生成分页模式下的标题头过滤的相关字串信息		by WangZY 2018/03/12
CString CDlgBCGGrid::DealCalcTitleFilter()
{
	CString strFilter;
	

	//待实现处理		by WangZY 2018/03/12
	if (nullptr == m_pBCGGrid)
	{
		return strFilter;
	}

	CBCGPGridFilterParams *pInfos = m_pBCGGrid->GetTitleFilterInfos();
	if (nullptr == pInfos)
	{
		return strFilter;
	}
	
	CString strLink;
	auto it = m_mapColID.begin();
	while (it != m_mapColID.end())
	{
		CString strFieldId = it->first;
		int nCol = it->second;
		++it;
		BCGP_FILTER_COLUMN_INFO* pInfo = pInfos->Column(nCol);
		if (pInfo == nullptr)
		{
			continue;
		}
		if(pInfo->IsEmpty()
			||pInfo->bAll)
		{
			continue;
		}

		CString strFilterTmp;
		CString strLinkTmp;
		int nFlag = 0;
		for (POSITION pos = pInfo->lstValues.GetHeadPosition (); pos != NULL; )
		{
			CString strValue = pInfo->lstValues.GetNext (pos);

			strFilterTmp += strLinkTmp;
			strFilterTmp += strFieldId;
			strFilterTmp += _T(" <> '");
			strFilterTmp += strValue;
			strFilterTmp += _T("'");
			strLinkTmp = _T(" OR ");
			nFlag++;
		}

		if (strFilterTmp.IsEmpty())
		{
			continue;
		}

		strFilter += strLink;
		if (nFlag>1)
		{
			strFilter += _T("( ");
		}
		
		strFilter += strFilterTmp;
		if (nFlag>1)
		{
			strFilter += _T(" )");
		}
		strLink = _T(" AND ");
	}

	return strFilter;
}

int CDlgBCGGrid::GetCheckRowNum()
{
	m_nCheckRowCount = 0;
	if (m_pBCGGrid && IsWindow(m_pBCGGrid->GetSafeHwnd()))
	{
		int nSumCount = m_pBCGGrid->GetTotalRowCount(TRUE);
		for (int irow = 0; irow < nSumCount; ++irow)
		{
			if (m_pBCGGrid->GetRow(irow)->GetCheck())
			{
				m_nCheckRowCount++;
			}
		}
	}
	return m_nCheckRowCount;
}


const CBCGPGridColors& CDlgBCGGrid::GetColorTheme() const
{
   //不做安全监测了  调用者应该知道当前表格是否经过了初始化
   return m_pBCGGrid->GetColorTheme();
}

void CDlgBCGGrid::SetColorTheme(const CBCGPGridColors& theme, BOOL bRedraw /*= TRUE*/, BOOL bFullCopy /*= FALSE*/)
{
   m_pBCGGrid->SetColorTheme(theme,bRedraw,bFullCopy);
}

void CDlgBCGGrid::ScrollToRow(__in const int & nRow)
{
   if (NULL != m_pBCGGrid && IsWindow(m_pBCGGrid->GetSafeHwnd()))
   {
      m_pBCGGrid->SendMessage(WM_VSCROLL,SB_TOP, 0);
      if (nRow>2)//当行号大于2时才滚动
      {
         for(int i=0;i<nRow;i++)
            m_pBCGGrid->SendMessage(WM_VSCROLL,SB_LINEDOWN, 0);//控制滚动条位置
      }
   }
}

BOOL CDlgBCGGrid::SetCustomColors(
   COLORREF	clrBackground,
   COLORREF	clrText,
   COLORREF	clrGroupBackground,
   COLORREF	clrGroupText,
   COLORREF	clrLeftOffset,
   COLORREF	clrLine)
{
   BOOL bRet = FALSE;

   if (NULL == m_pBCGGrid)
   {
      TRACE(_T("CDlgBCGGrid::SetCustomColors: you've to initGrid before you use it\n"));
      ASSERT(FALSE);
      bRet = FALSE;
   }
   else
   {
      m_pBCGGrid->SetCustomColors(clrBackground,clrText,clrGroupBackground,clrGroupText,clrLeftOffset,clrLine);
      bRet = TRUE;
   }

   return bRet;
}

void CDlgBCGGrid::SetGridFont(CFont* pFont, BOOL bRedraw /*= TRUE*/)
{
   if (NULL != m_pBCGGrid)
   {
      m_pBCGGrid->SetFont(pFont,bRedraw);
   }
}

BOOL CDlgBCGGrid::EditGridItem(const int & nRow,const int & nCol)
{
   BOOL bRet = FALSE;
   if (NULL != m_pBCGGrid)
   {
      auto pRow = m_pBCGGrid->GetRow(nRow);
      if (NULL != pRow)
      {
         if(m_pBCGGrid->GetColumnVisible(nCol))
         {
            auto pCol = pRow->GetItem(nCol);
            if (NULL != pCol)
            {
               CRect rcCol = pCol->GetRect();
               CPoint ptCellMid = rcCol.CenterPoint();
               bRet = m_pBCGGrid->EditItem(pRow,&ptCellMid);
            }
         }
      }
   }
   return bRet;
}

void CDlgBCGGrid::SetRowBackgroundColor(int iRow,MAP_GridCtrl_RowData& row_data,COLORREF bkcolor)
{
   for (auto itr_col = row_data.begin(); itr_col != row_data.end(); ++itr_col)
   {
      if (nullptr == itr_col->second.sptr_cellBackgroundClrVec)
      {
         itr_col->second.sptr_cellBackgroundClrVec = shared_ptr<vector<int>>(new(vector<int>));
      }
      else
      {
         itr_col->second.sptr_cellBackgroundClrVec->clear();
      }
      itr_col->second.sptr_cellBackgroundClrVec->push_back(bkcolor);//背景色数据
      SetValuebyGridRowAndFieldId(itr_col->second,iRow,itr_col->first);
   }
}

void CDlgBCGGrid::SetEnterGoDirection(UINT nDirection,BOOL bEnable /*= TRUE*/)
{
   m_pBCGGrid->m_nDirection = nDirection;
   m_pBCGGrid->m_bEnableEnterGo = bEnable;
}

//获取表格的统计字段数据 yangjr 2018/6/20
BOOL CDlgBCGGrid::GetTongJiData(__out std::map<CString/*strFieldId*/,ENUM_COLSUMTYPE> &mapTongJiData)
{
   return GetTongJiDataByAttri(m_tableAttri,mapTongJiData);
}

BOOL CDlgBCGGrid::GetTongJiDataByAttri(const S_GridCtrl_TableAttri &tableAttri,__out std::map<CString/*strFieldId*/,ENUM_COLSUMTYPE> &mapTongJiData)
{
   if (!tableAttri.isShowSumBar)
   {
      return FALSE;
   }
   BOOL bRet = FALSE;
   for (auto iterCol=tableAttri.mapFeildAtrri.begin();iterCol!=tableAttri.mapFeildAtrri.end();++iterCol)
   {
      if (iterCol->second.isShow && iterCol->second.enColSumType != CB_enum_ColSumType_None)
      {
         mapTongJiData.insert(make_pair(iterCol->first,iterCol->second.enColSumType));
         bRet = TRUE;
      }
   }
   return bRet;
}

//设置表格的统计字段显示数据 yangjr 2018/6/21
void CDlgBCGGrid::SetTongJiData(__in const std::map<CString,CString> &mapTongJiValue/*统计数据*/)
{
   m_mapTongJiValue = mapTongJiValue;/*统计数据*/
}
//获取分页模式每页行数 yangjr 2018/7/6
int CDlgBCGGrid::GetFenYePageRows()
{
   int iPageRows = m_tableAttri.iPageRows;
   if (iPageRows <50)
   {
      iPageRows = 50;
   }
   return iPageRows;
}

BOOL CDlgBCGGrid::GetShowFieldId(__out std::vector<CString> &vecShowFieldId,
   __out std::vector<CString> &vecFieldName)
{
   if (nullptr == m_pBCGGrid 
      || !IsWindow(m_pBCGGrid->GetSafeHwnd()))
   {
      return FALSE;
   }

   auto &vecHeadData = vecFieldName;

   vecHeadData.clear();

   vector<int > vecShowCol;
   GetShowColID(vecShowCol);
   
   for (int index =0; index < vecShowCol.size(); ++index)
   {
      CString strColShowName = m_pBCGGrid->GetColumnName(vecShowCol[index]);	//获取表格列显示的名称
      vecHeadData.push_back(strColShowName);

      //m_pBCGGrid->GetColumnsInfo().GetColumnData(vecShowCol[index]);
      auto it = m_mapShowCol.find(vecShowCol[index]);
      if (it!=m_mapShowCol.end())
      {
         vecShowFieldId.push_back(it->second);
      }
   }
   
   return TRUE;
}

BOOL CDlgBCGGrid::GetExportExcelData(std::vector<std::vector<CString>> &vecDatas)
{
   std::vector<CString> vecHeadData;
   std::vector<CString> vecFieldId;
   BOOL bGet = GetShowFieldId(vecFieldId,vecHeadData);
   if (!bGet)
   {
      return FALSE;
   }
  
   vecDatas.push_back(vecHeadData);
   
   const int nRowCounts = m_pBCGGrid->GetRowCount();		//行数
   const int nColCounts = m_pBCGGrid->GetColumnCount();	//列数   
   if (nColCounts<= 0 || nRowCounts <= 0)
   {
      return FALSE;		//无数据
   }

   vector<int > vecShowCol;
   GetShowColID(vecShowCol);
   if (m_tableAttri.isMultiRowSelect)		//多行选择
   {
      for (int iRow =0; iRow < nRowCounts; ++iRow)
      {
         auto pRow = m_pBCGGrid->GetRow(iRow);
         if (pRow && pRow->GetCheck() == 1 && m_pBCGGrid->IsRowVisible(pRow))
         {
            std::vector<CString> vecOneData; 
            MAP_GridCtrl_RowData map_row_data = *(MAP_GridCtrl_RowData*)(pRow->GetData());		//行数据集合
            for (int index =0; index < vecShowCol.size(); ++index)
            {     
               CString strValue = _T("");
               auto itr_col_id = m_mapColWithFieldId.find(vecShowCol[index]);
               if (itr_col_id != m_mapColWithFieldId.end())
               {                
                  auto itr_col_Value = map_row_data.find(itr_col_id->second);
                  if (itr_col_Value != map_row_data.end())
                  {
                     strValue = itr_col_Value->second.strValue;
                  }
               }                 
               vecOneData.push_back(strValue);
            }
            vecDatas.push_back(vecOneData);
         }
      }
   }
   else
   {
      for (int iRow =0; iRow < nRowCounts; ++iRow)
      {
         auto pRow = m_pBCGGrid->GetRow(iRow);
         if (pRow && m_pBCGGrid->IsRowVisible(pRow))
         {
            std::vector<CString> vecOneData; 
            MAP_GridCtrl_RowData map_row_data = *(MAP_GridCtrl_RowData*)(pRow->GetData());		//行数据集合
            for (int index =0; index < vecShowCol.size(); ++index)
            {     
               CString strValue = _T("");
               auto itr_col_id = m_mapColWithFieldId.find(vecShowCol[index]);
               if (itr_col_id != m_mapColWithFieldId.end())
               {                
                  auto itr_col_Value = map_row_data.find(itr_col_id->second);
                  if (itr_col_Value != map_row_data.end())
                  {
                     strValue = itr_col_Value->second.strValue;
                  }
               }                 
               vecOneData.push_back(strValue);
            }
            vecDatas.push_back(vecOneData);
         }
      }
   }

   if (m_pBCGGrid->GetColumnsInfo().IsEnableShowFooterRow()) //有显示合计栏
   {
      std::vector<CString> vecHeJiData;      
      for (int index =0; index < vecShowCol.size(); ++index)
      {     
         CString strValue = _T("");
         auto itr_col_id = m_mapColWithFieldId.find(vecShowCol[index]);
         if (itr_col_id != m_mapColWithFieldId.end())
         {                
            strValue = m_pBCGGrid->GetColumnsInfo().GetColumnFooterValue(itr_col_id->first);
         }                 
         vecHeJiData.push_back(strValue);
      }
      vecDatas.push_back(vecHeJiData);     
   }

   return TRUE;
}

//导出表格数据到excel yangjr 2018/7/19
BOOL CDlgBCGGrid::ExportExcel()
{
   /*
   std::vector<std::vector<CString>> vecDatas;
   //DWORD t1 = GetTickCount();
   START_MY_OUTPUT_LOG_
   BOOL bRet = GetExportExcelData(vecDatas);
   MY_OUTPUT_LOG_
   //DWORD t2 = GetTickCount();
   if (!bRet)
   {
      theApp.OnShowDesktopAlert(_T("表格没有数据，不能导出！"),TIP_COLOR_WARNING,TIP_TIME_DELAY);
      return FALSE;
   }

   CString strExcelPath = _T("");
   CFileDialog saveDlg(false);
   saveDlg.m_ofn.lpstrFilter = LPCTSTR(_T("Excel File(*.xls)\0*.xls\0"));
   saveDlg.m_ofn.lpstrTitle = LPCTSTR(_T("导出XLS"));
   saveDlg.m_ofn.Flags = saveDlg.m_ofn.Flags | OFN_HIDEREADONLY | OFN_CREATEPROMPT | OFN_PATHMUSTEXIST;   

   CString fileName;
   GetWindowText(fileName);
   if (!fileName.IsEmpty())
   {
      fileName += _T(".xls");				
      saveDlg.m_ofn.lpstrFile = fileName.GetBuffer(MAX_PATH);
      saveDlg.m_ofn.nMaxFile = MAX_PATH;
   }
   if (IDOK != saveDlg.DoModal())	return FALSE;
   fileName.ReleaseBuffer();
   strExcelPath = saveDlg.GetPathName();

   if (strExcelPath.IsEmpty())
   {
      theApp.OnShowDesktopAlert(_T("文件名不能为空！"),TIP_COLOR_WARNING,TIP_TIME_DELAY);
      return FALSE;
   }

   CString strExe = PathFindExtension(strExcelPath);
   strExe.MakeUpper();
   if (strExe.IsEmpty() || strExe != _T(".XLS"))
   {
      strExcelPath += _T(".XLS");
   }

   //CExcelOp execlOp;

   //WaitCursorBegin();
   MY_OUTPUT_LOG_
   //BOOL bResult = execlOp.Save2Excel(strExcelPath,vecDatas);
   MY_OUTPUT_LOG_
   //WaitCursorEnd();

   if (bResult == FALSE)
   {
      CString info;
      info.Format(_T("导出到文件[%s]保存失败！"),strExcelPath);
      theApp.OnShowDesktopAlert(info,TIP_COLOR_WARNING,TIP_TIME_DELAY);
   }else
   {
      CoInitialize(NULL);   
      CString info;
      info.Format(_T("是否打开文件[%s]？"),strExcelPath);
      if (AfxMessageBox(info,MB_YESNO) == IDYES)
      {
         //theApp.ShowLoading();
         //KDS_CSharpReport::IXtraReportPtr pMyXtraReport(__uuidof(KDS_CSharpReport::MyXtraReport)); 
         //pMyXtraReport->StartProcessOpenXls(strExcelPath.GetBuffer(0));
         //theApp.CloseLoading();
         //strExcelPath.ReleaseBuffer();
      }
      CoUninitialize();
   }
   */
   return TRUE;
}	