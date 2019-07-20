#include "StdAfx.h"
#include "QLBCGGridCtrl.h"
#include "../CustomMgnSys.h"
//#include "FilterListDlg.h"
//#include "FilterStringDlg.h"
#include "QLBCGMESSAGE.h"
//#include "DBGlobalSet.h"


const int CN_TITLE_FILTER_DEF_ROW_LIMIT = 10000;
const int CN_TITLE_FILTER_DEF_CONTENT_LIMIT = 1000;

IMPLEMENT_DYNCREATE(CQLBCGGridCtrl, CBCGPGridCtrl)

CQLBCGGridCtrl::CQLBCGGridCtrl(void)
{
	m_bVisualManagerStyle = TRUE;
	m_nLastClickedColumn = -1;
   m_nDirection = NextColumn | Right;
   m_bEnableEnterGo = FALSE;

   m_nRowHeightEx = -1;
}

CQLBCGGridCtrl::~CQLBCGGridCtrl(void)
{
	m_infoFilter.Clear();
}

BEGIN_MESSAGE_MAP(CQLBCGGridCtrl, CBCGPGridCtrl)
	//{{AFX_MSG_MAP(CQLBCGGridCtrl)
	//ON_WM_CREATE()
	//ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXT, 0, 0xFFFF, OnNeedTipText)
	//ON_COMMAND(ID_FILTER_SORT_A_Z,OnSortAZ)
	////标题过滤器响应命令相关		by WangZY 2018/02/27
	//ON_COMMAND(ID_FILTER_SORT_Z_A, OnSortZA)
	//ON_COMMAND(ID_FILTER_SET, OnFilterSet)
	//ON_COMMAND(ID_FILTER_CLEAR, OnFilterClear)
	////ON_UPDATE_COMMAND_UI(ID_FILTER_CLEAR, OnUpdateFilterClear)
	//ON_COMMAND(ID_APPLY_FILTER, OnApplyFilter)

	ON_REGISTERED_MESSAGE(BCGM_EDIT_ON_FILL_AUTOCOMPLETE_LIST,OnFillAutoCompleteList)
END_MESSAGE_MAP()


LRESULT CALLBACK CQLBCGGridCtrl::pfnFilterCallback (WPARAM wParam, LPARAM lParam)
{
	CBCGPGridRow* pRow = (CBCGPGridRow*) wParam;
	ASSERT_VALID (pRow);

	FILTER_PARAM* pParam = (FILTER_PARAM*)lParam;
	ASSERT (pParam != NULL);

	if (pRow->IsGroup ())
	{
		return FALSE; // do not hide groups
	}

	CBCGPGridItem* pItem = pRow->GetItem (pParam->nCol);
	if (pItem == NULL)
	{
		return FALSE;
	}

	ASSERT_VALID (pItem);

	//-------------------------
	// Filter by column "Name":
	//-------------------------
	if (pParam->nCol == 0)
	{
		if (!pParam->bAll && pParam->lstValues.GetCount() == 0)
		{
			// use custom filter
			const CString strItem = pItem->GetLabel ();
			if (strItem.Find (pParam->strFilter) == -1)
			{
				return TRUE; // hide
			}

			return FALSE;
		}

		if (!pParam->bAll)
		{
			const CString strItem = pItem->GetLabel ();
			if (pParam->lstValues.Find (strItem) == NULL)
			{
				return TRUE; // hide
			}
		}

		return FALSE;
	}

	//----------------------------
	// Filter by column "Company":
	//----------------------------
	if (pParam->nCol == 1)
	{
		if (!pParam->bAll)
		{
			const CString strItem = pItem->GetLabel ();
			if (pParam->lstValues.Find (strItem) == NULL)
			{
				return TRUE; // hide
			}
		}

		return FALSE;
	}

	//-------------------------------
	// Filter by column "Department":
	//-------------------------------
	if (pParam->nCol == 2)
	{
		if (!pParam->bAll)
		{
			const CString strItem = pItem->GetLabel ();
			if (pParam->lstValues.Find (strItem) == NULL)
			{
				return TRUE; // hide
			}
		}

		return FALSE;
	}

	//---------------------------
	// Filter by column "Gender":
	//---------------------------
	if (pParam->nCol == 3)
	{
		if (!pParam->bAll)
		{
			const CString strItem = pItem->GetLabel ();
			if (pParam->lstValues.Find (strItem) == NULL)
			{
				return TRUE; // hide
			}
		}

		return FALSE;
	}

	//------------------------
	// Filter by column "Age":
	//------------------------
	if (pParam->nCol == 4)
	{
		if (!pParam->bAll)
		{
			const CString strItem = pItem->GetLabel ();
			if (pParam->lstValues.Find (strItem) == NULL)
			{
				return TRUE; // hide
			}
		}
		return FALSE;

		if (!pParam->bAll)
		{
			int nItemValue = 0;;
			switch (pItem->GetValue ().vt)
			{
			case VT_I4:
			case VT_INT:
			case VT_UINT:
			case VT_UI4:
				nItemValue = (long) pItem->GetValue ();
			}

			int nAgeCategory = -1;
			if (nItemValue < 25)
			{
				nAgeCategory = 0; // Age < 25
			}
			else if (nItemValue >= 25 && nItemValue < 40)
			{
				nAgeCategory = 1; // 25 <= Age < 40
			}
			else if (nItemValue >= 40 && nItemValue < 50)
			{
				nAgeCategory = 2; // 40 <= Age < 50
			}
			else
			{
				nAgeCategory = 3; // Age >= 50
			}

			if (pParam->lstNumericValues.Find (nAgeCategory) == NULL)
			{
				return TRUE; // hide
			}
		}

		return FALSE;
	}

	//----------------------------------
	// Filter by column "Family Status":
	//----------------------------------
	if (pParam->nCol == 5)
	{
		if (!pParam->bAll)
		{
			const CString strItem = pItem->GetLabel ();
			if (pParam->lstValues.Find (strItem) == NULL)
			{
				return TRUE; // hide
			}
		}

		return FALSE;
	}

	return FALSE; // show all
}

inline int Rand (int nMax)
{
	int nRes = rand () % nMax;
	return min (nRes, nMax - 1);
}

void CQLBCGGridCtrl::GetStringList (CStringList& lstValues, int nColumn)
{
	m_infoFilter.GetColumnFilterList(nColumn,lstValues);
	if (lstValues.IsEmpty())
	{
		GetColumnValuesList(nColumn, lstValues);
	}
}

int CQLBCGGridCtrl::GetHeaderMenuButtonImageIndex (int nColumn, BOOL bSortArrow) const
{
	BCGP_FILTER_COLUMN_INFO* pFilterColumnInfo = m_pDefaultFilter->GetColumnInfo (nColumn);	
	//BOOL bFilterColumn = (m_param.nCol == nColumn && !m_param.bAll);

	BOOL bFilterColumn = !pFilterColumnInfo->bAll;
	int nIndex = bFilterColumn ? 3 : 0;

	if (bSortArrow)
	{
		int nSortVal = m_Columns.GetColumnState (nColumn);
		if (nSortVal > 0)
		{
			nIndex += 1;
		}
		else if (nSortVal < 0)
		{
			nIndex += 2;
		}
	}

	//CBCGPToolBarImages* pImages = GetHeaderBtnImageList ();
	//if (pImages != NULL && pImages->GetCount () >= nIndex)
	{
		return nIndex;
	}

	return CBCGPGridCtrl::GetHeaderMenuButtonImageIndex (nColumn, bSortArrow);
}

//void CQLBCGGridCtrl::OnHeaderMenuButtonClick (int nColumn, CRect rectMenuButton)
//{
//	CBCGPGridCtrl::OnHeaderMenuButtonClick (nColumn, rectMenuButton);
//
//	SelectColumn (nColumn, TRUE);
//
//	m_nLastClickedColumn = nColumn;
//
//	//int nRowLimit = CDBGlobalSetList::Instance()->GetIntValueByName(
//	//	DBGlogalSet_TitleFilter_OrderLimitCount,CN_TITLE_FILTER_DEF_ROW_LIMIT);
//	//int nRowCount = GetRowCount();
//	//if (nRowCount>nRowLimit)
//	//{
//	//	AfxMessageBox(_T("数据数量超出了全局设置上限!"));
//
//	//	return;
//	//}
//
//	CStringList lstValues;
//	GetStringList(lstValues, nColumn);
//
//	//int nContentCount = lstValues.GetCount();
//
//	//int nContentLimit = CDBGlobalSetList::Instance()->GetIntValueByName(
//	//	DBGlogalSet_TitleFilter_ContentLimitCount,CN_TITLE_FILTER_DEF_CONTENT_LIMIT);
//
//	//if (nContentCount>nContentLimit)
//	//{
//	//	AfxMessageBox(_T("过滤列表项数量超出了全局设置上限!"));
//
//	//	return;
//	//}
//
//
//	int nCount = lstValues.GetCount();
//	ShowFilterMenu(NULL/*menu.GetSubMenu(0)->GetSafeHmenu()*/, ID_APPLY_FILTER,
//		nColumn, 0, lstValues);
//	
//}

void CQLBCGGridCtrl::OnApplyFilter()
{
	//m_param.Clear ();		// Clear old filter settings
	//m_param.bAll = m_FilterMenuResults.bAll;
	//m_param.nCol = m_FilterMenuResults.nCol;
	//m_param.lstValues.AddTail (&m_FilterMenuResults.lstValues);

	//if (m_param.nCol == 4)
	//{
	//	//------------------------
	//	// Filter by column "Age":
	//	//------------------------

	//	// Update checked list:
	//	for (POSITION pos = m_param.lstValues.GetHeadPosition (); pos != NULL;)
	//	{
	//		const CString& strChecked = m_param.lstValues.GetNext (pos);
	//		//for (int i = 0; i < AGES_NUM; i++)
	//		//{
	//		//	if (strChecked == arAges [i])
	//		//	{
	//		//		int nCategory = i;
	//		//		m_param.lstNumericValues.AddTail (nCategory);
	//		//	}
	//		//}
	//	}
	//}

	if (m_bUserPaginationMode && m_emPMPaginationMode == emPM_Local)
	{
		GetOwner()->PostMessage (BCGM_GRID_TITLE_FILTER_CHANGED, NULL, NULL);
	}
	else
	{
     
		SetCurSel (NULL);
		AdjustLayout ();

      GetOwner()->PostMessage (BCGM_GRID_TITLE_FILTER_CHANGED, NULL, NULL);
	}
}

void CQLBCGGridCtrl::SetDefaultDemoFilter (int nColumn)
{
	m_param.Clear ();		// Clear old filter settings
	m_param.nCol = nColumn;

	CString str;
	str.Format (_T("Demo filter for column \"%s\""), GetColumnName (nColumn));
	BCGPMessageBox (str);

	AdjustLayout ();
}

void CQLBCGGridCtrl::OnSortAZ()
{
	if (m_nLastClickedColumn >= 0)
	{
		Sort (m_nLastClickedColumn);
	}
}

void CQLBCGGridCtrl::OnSortZA()
{
	if (m_nLastClickedColumn >= 0)
	{
		Sort (m_nLastClickedColumn, FALSE);
	}
}

void CQLBCGGridCtrl::OnFilterSet()
{
	if (m_nLastClickedColumn < 0)
	{
		return;
	}

	CStringList lstFilterStrings;
	GetStringList(lstFilterStrings, m_nLastClickedColumn);

	FILTER_PARAM param;
	param.Copy (m_param);

	if (param.nCol != m_nLastClickedColumn)
	{
		param.Clear ();		// Clear old column filter settings
		param.nCol = m_nLastClickedColumn;
	}

	switch (param.nCol)
	{
		//-------------------------
		// Filter by column "Name":
		//-------------------------
	case 0:
		{
			//CFilterStringDlg dlg (param, this);
			//if (dlg.DoModal () == IDOK)
			//{
			//	m_param.Copy (param);
			//}
			break;
		}

		//-------------------------------------------
		// Filter by columns "Company", "Department", 
		// "Gender", "Family Status":
		//-------------------------------------------
	case 1:
	case 2:
	case 3:
	case 5:
		{
			//CFilterListDlg dlg (lstFilterStrings, param, this);

			//if (dlg.DoModal () == IDOK)
			//{
			//	m_param.Copy (param);
			//}

			break;
		}

		//------------------------
		// Filter by column "Age":
		//------------------------
	case 4:
		{
			//CFilterListDlg dlg (lstFilterStrings, param, this);

			//if (dlg.DoModal () == IDOK)
			//{
			//	m_param.Copy (param);
			//}

			//// Update checked list:
			//m_param.lstNumericValues.RemoveAll ();

			//for (POSITION pos = m_param.lstValues.GetHeadPosition (); pos != NULL;)
			//{
			//	const CString& strChecked = m_param.lstValues.GetNext (pos);
			//	//for (int i = 0; i < AGES_NUM; i++)
			//	//{
			//	//	if (strChecked == arAges [i])
			//	//	{
			//	//		int nCategory = i;
			//	//		m_param.lstNumericValues.AddTail (nCategory);
			//	//	}
			//	//}
			//}

			break;
		}
	}

	SetCurSel (NULL);
	AdjustLayout ();
}

void CQLBCGGridCtrl::OnFilterClear()
{
	SetCurSel (NULL);
	m_param.Clear ();
	AdjustLayout ();
}

void CQLBCGGridCtrl::ClearTitleFilter()
{
   if (m_pDefaultFilter)
   {
      m_pDefaultFilter->m_params.ClearAll();
   }  
}
BOOL CQLBCGGridCtrl::IsTitleFilterEmpty()
{
   if (m_pDefaultFilter)
   {
      return m_pDefaultFilter->m_params.IsEmpty();
   }else
   {
      return TRUE;
   }
}

void CQLBCGGridCtrl::SetRowHeight(const int & nHeight)
{
   m_nRowHeightEx = nHeight;
}

void CQLBCGGridCtrl::SetRowHeight()
{
   CBCGPGridCtrl::SetRowHeight();

   if (-1 != m_nRowHeightEx)
   {
      if (m_bIsPrinting)
      {
         m_PrintParams.m_nRowHeight = m_nRowHeightEx;
         m_PrintParams.m_nLargeRowHeight = m_nRowHeightEx;
      }
      else
      {
         m_nRowHeight = m_nRowHeightEx;
         m_nLargeRowHeight = m_nRowHeightEx;
      }
   }
}

void CQLBCGGridCtrl::GetHeaderMenuButtonTooltip (int nColumn, CString& strText) const
{
	//strText.Format (_T("Filter by %s"), GetColumnName (nColumn));
	strText.Format(_T("通过(%s)过滤"),GetColumnName (nColumn));
}

BOOL CQLBCGGridCtrl::OnNeedTipText(UINT id, NMHDR* pNMH, LRESULT* pResult)
{
	if (!CBCGPGridCtrl::OnNeedTipText(id, pNMH, pResult))
	{
		return FALSE;
	}

	//-------------------------------------------
	// Add tooltip description for Filter buttons
	//-------------------------------------------
	CBCGPToolTipCtrl* pToolTip = DYNAMIC_DOWNCAST (CBCGPToolTipCtrl, m_pToolTip);

	if (pToolTip != NULL)
	{
		ASSERT_VALID (pToolTip);
		pToolTip->SetDescription (GetCurFilterButtonDescription ());
	}

	return TRUE;
}

void CQLBCGGridCtrl::OnRButtonDown(UINT nFlags, CPoint point)
{
	//获取表格的列头的区域
	//如果点击的是列头的区域 则单独进行处理 wangzl 2017-12-21 当表格没有列时无法弹出右键菜单进行样式编辑的问题处理
	CRect rcHeadRect = m_rectHeader;
	if (rcHeadRect.PtInRect(point))
	{
		if (m_nDraggedColumn >= 0 || m_bTracking || m_bSelecting)
		{
			return;
		}

		SetFocus ();

		// -------------
		// Track header:
		// -------------
		if (OnTrackHeader () && point.y >= m_rectList.top)
		{
			CPoint ptHeader = point;
			ptHeader.y = m_rectHeader.top;

			if (GetColumnsInfo ().HitTestColumn (ptHeader, TRUE, 2/*STRETCH_DELTA*/) != -1)
			{
				return;
			}
		}

		int nColumnHit = GetColumnsInfo ().HitTestColumn (point, FALSE, 2/*STRETCH_DELTA*/);

		OnHeaderColumnRClick (nColumnHit);
		return;
	}
	else
		CBCGPGridCtrl::OnRButtonDown(nFlags,point);
}

CString CQLBCGGridCtrl::GetCurFilterButtonDescription () const
{
	CPoint ptCursor;
	::GetCursorPos (&ptCursor);
	ScreenToClient (&ptCursor);

	if (m_param.nCol != m_Columns.HitTestColumn (ptCursor) || m_param.bAll)
	{
		//return _T("Click to set new filter by this column");
		return _T("点击当前按钮进行列标题过滤设置");
	}

	switch (m_param.nCol)
	{
		//-------------------------
		// Filter by column "Name":
		//-------------------------
	case 0:
		if (!m_param.strFilter.IsEmpty ()) // custom filter by column "Name" uses only m_param.strFilter field
		{
			CString str;
			str.Format (_T("Contains \"%s\""), m_param.strFilter);
			return str;
		}
		// else same as other columns

		//-------------------------------------------
		// Filter by columns "Company", "Department", 
		// "Gender", "Family Status":
		//-------------------------------------------
	case 1:
	case 2:
	case 3:
	case 5:
		{
			if (m_param.bAll)
			{
				return _T("(Showing All)");
			}

			if (m_param.lstValues.IsEmpty ())
			{
				return _T("(Showing None)");
			}

			CString strList;
			for (POSITION pos = m_param.lstValues.GetHeadPosition (); pos != NULL; )
			{
				if (!strList.IsEmpty ())
				{
					strList += _T(", ");
				}

				strList += m_param.lstValues.GetNext (pos);
			}

			CString str;
			str.Format (_T("Contains \"%s\""), strList);

			return str;
		}

		//------------------------
		// Filter by column "Age":
		//------------------------
	case 4:
		{
			if (m_param.bAll)
			{
				return _T("(Showing All)");
			}

			if (m_param.lstValues.IsEmpty ())
			{
				return _T("(Showing None)");
			}

			CString strList;
			for (POSITION pos = m_param.lstNumericValues.GetHeadPosition (); pos != NULL; )
			{
				int nValue = m_param.lstNumericValues.GetNext (pos);

				//if (nValue >= 0 && nValue < AGES_NUM)
				//{
				//	if (!strList.IsEmpty ())
				//	{
				//		strList += _T(";\n");
				//	}

				//	strList += arAges [nValue];
				//}
			}

			return strList;
		}
	}

	return _T("");
}

void CQLBCGGridCtrl::EnableFilter_My(BOOL bEnable /*= TRUE*/)
{
	if (bEnable)
	{
		EnableFilter(NULL,0);
	}
	else
	{
		m_bFilter = bEnable;
		if (NULL != m_pDefaultFilter)
		{
			m_pDefaultFilter->m_params.ClearAll();
		}
	}
	return;

	if (bEnable)
	{
		EnableFilter (CQLBCGGridCtrl::pfnFilterCallback, (LPARAM)&m_param);
	}
	else
	{
		EnableFilter(NULL,0);
	}
}

void CQLBCGGridCtrl::OnRButtonUp(UINT nFlags, CPoint point)
{
	CBCGPGridCtrl::OnRButtonUp(nFlags, point);

	CBCGPGridItemID  id;
	CBCGPGridItem* pItem = NULL;
	CBCGPGridRow* pRow = HitTest(point,id,pItem);
	BCGPGRID_ITEM_INFO ii;
	memset (&ii, 0, sizeof (BCGPGRID_ITEM_INFO));
	if (pRow && id.m_nRow >=0 && id.m_nColumn >= 0)
	{
		ii.pItem = pItem;
		ii.nRow = id.m_nRow;
		ii.nCol = id.m_nColumn;
		ii.dwResultCode = 0;
	}

	this->GetOwner()->SendMessage (BCGM_GRID_ITEM_RCLICK, GetDlgCtrlID (), LPARAM (&ii));

	//const int nColCounts = GetColumnsInfo().GetColumnCount();

	//int* aSortOrder = new int[nColCounts];
	//memset (aSortOrder, -1, nColCounts * sizeof (int));

	//GetColumnsInfo().GetColumnOrderArray((LPINT)aSortOrder,nColCounts);

	//vector<int> vecTemp;
	//for (int i =0; i< nColCounts; ++i)
	//{
	//	vecTemp.push_back(aSortOrder[i]);
	//}

	//delete[] aSortOrder;
	//const int nRowCounts = GetRowCount();

	//筛选栏数据
	//CString strFilterBar;
	//GetColumnsInfo().GetColumnFilterBarCtrl(id.m_nColumn)->GetWindowText(strFilterBar);
	//GetColumnsInfo().GetColumnFilterBarCtrl(id.m_nColumn)->SetWindowText(_T("88"));

	//修改值
	//pRow->GetItem(0)->SetValue(_bstr_t(_T("8888")));
	//BCGPGRID_ITEM_INFO ii;
	//memset (&ii, 0, sizeof (BCGPGRID_ITEM_INFO));
	//ii.pItem = pItem;
	//ii.nRow = id.m_nRow;
	//ii.nCol = id.m_nColumn;
	//ii.dwResultCode = 0;
	//this->GetOwner()->SendMessage (BCGM_GRID_ITEM_CHANGED, GetDlgCtrlID (), LPARAM (&ii));

	//选择一行
	//this->SetCurSel(CBCGPGridItemID(5,0),SM_SINGE_SEL_GROUP | SM_SINGLE_ITEM | SM_ROW);

	//设置勾选
	//this->GetRow(5)->SetCheck(1);
}

void CQLBCGGridCtrl::OnHeaderCheckBoxClick(int nColumn)
{
	CBCGPGridCtrl::OnHeaderCheckBoxClick(nColumn);
	BOOL bCheck = GetColumnsInfo().GetCheckBoxState();
	CheckHeaderBoxClick(bCheck);
	//this->SetRedraw(TRUE);
}

void CQLBCGGridCtrl::CheckHeaderBoxClick(BOOL bCheck)
{
	const int nRowCounts = this->GetRowCount();

	CBCGPGridRow* pRow = NULL;

	for (int iRow =0; iRow < nRowCounts; ++iRow)
	{
		bool bFilterItem = true;
		pRow = this->GetRow(iRow);

		if (pRow &&	!FilterItem(pRow))//GetTotalRowCount())
		{
			pRow->SetCheck(bCheck);
		}
	}
}

//		by WangZY 2018/03/12
CBCGPGridFilterParams * CQLBCGGridCtrl::GetTitleFilterInfos()
{
	if (m_pDefaultFilter != nullptr)
	{
		return &m_pDefaultFilter->m_params;
	}

	return nullptr;
}

void CQLBCGGridCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{
	CBCGPGridCtrl::OnLButtonUp(nFlags, point);

	CBCGPGridItemID  id;
	CBCGPGridItem* pItem = NULL;
	CBCGPGridRow* pRow = HitTest(point,id,pItem);
	BCGPGRID_ITEM_INFO ii;
	memset (&ii, 0, sizeof (BCGPGRID_ITEM_INFO));
	ii.nCol = ii.nRow = -1;
	if (pRow && id.m_nRow >=0 && id.m_nColumn >= 0)
	{
		ii.pItem = pItem;
		ii.nRow = id.m_nRow;
		ii.nCol = id.m_nColumn;
		ii.dwResultCode = 0;
	}

	this->GetOwner()->SendMessage (BCGM_GRID_ITEM_LCLICK, GetDlgCtrlID (), LPARAM (&ii));
}

void CQLBCGGridCtrl::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CBCGPGridCtrl::OnLButtonDblClk(nFlags, point);
	CBCGPGridItemID  id;
	CBCGPGridItem* pItem = NULL;
	CBCGPGridRow* pRow = HitTest(point,id,pItem);
	BCGPGRID_ITEM_INFO ii;
	memset (&ii, 0, sizeof (BCGPGRID_ITEM_INFO));
	ii.nCol = ii.nRow = -1;
	if (pRow && id.m_nRow >=0 && id.m_nColumn >= 0)
	{
		ii.pItem = pItem;
		ii.nRow = id.m_nRow;
		ii.nCol = id.m_nColumn;
		ii.dwResultCode = 0;
	}

	this->GetOwner()->SendMessage (BCGM_GRID_ITEM_LDBCLICK, GetDlgCtrlID (), LPARAM (&ii));
}

void CQLBCGGridCtrl::OnHeaderColumnRClick(int nColumn)
{
	this->GetOwner()->SendMessage (BCGM_GRID_ITEM_HEADRCLICK, GetDlgCtrlID (), LPARAM (nColumn));
}


#define	BCGPGRIDCTRL_ID_INPLACE	1
LRESULT CQLBCGGridCtrl::OnFillAutoCompleteList(WPARAM wp, LPARAM lp)
{
	int nCtrlID = (int)wp;
	if (nCtrlID != BCGPGRIDCTRL_ID_INPLACE)
	{
		return 0;
	}

	CBCGPGridItem* pSelItem = GetCurSelItem ();
	if (pSelItem == NULL)
	{
		return 0;
	}

	ASSERT_VALID (pSelItem);

	CWnd* pWndInPlace = pSelItem->GetInPlaceWnd ();
	if (pWndInPlace->GetSafeHwnd () == NULL)
	{
		return 0;
	}

	ASSERT_VALID (pWndInPlace);

	CString strText;
	pWndInPlace->GetWindowText (strText);

	strText.MakeUpper();

	if (strText.IsEmpty())
	{
		return 0;
	}

	CStringList* pList = (CStringList*)lp;
	ASSERT(pList != NULL);

	int nCount = pSelItem->GetOptionCount();
	for (int i=0; i<nCount; ++i)
	{
		CString strList = pSelItem->GetOption(i);
		CString strListUpper = strList;
		strListUpper.MakeUpper();

		int nFind = strListUpper.Find(strText);
		if (0 != nFind
			||strText == strList)
		{
			continue;
		}

		pList->AddTail (strList);
	}


	return 0;
}

BOOL CQLBCGGridCtrl::PreTranslateMessage(MSG* pMsg)
{
   BOOL bFlag = CBCGPGridCtrl::PreTranslateMessage(pMsg);
   if (pMsg->message == WM_KEYDOWN)
   {
      if (pMsg->wParam==VK_RETURN)
      {
         //回车之后跳到下一行的cell
         GotoNextRowCell();
      }
   }

   return bFlag;
}

void CQLBCGGridCtrl::GotoNextRowCell()
{
   if (m_bEnableEnterGo)
   {
      GoToNextItem(m_nDirection);
   }
}

//		by WangZY 2018/06/01
BOOL CQLBCGGridCtrl::CanEndInplaceEditOnChar(UINT nChar, UINT nRepCnt, UINT nFlags) const
{
	switch (nChar)
	{
	case VK_UP:
	case VK_DOWN:
	case VK_LEFT:
	case VK_RIGHT:	// Enable these keys
	case VK_TAB:
		{
			return TRUE; // To close in-place edit
		}
	case VK_RETURN:
		{
			const BOOL bShift = (::GetAsyncKeyState (VK_SHIFT) & 0x8000) != 0;
			const BOOL bCtrl = (::GetAsyncKeyState (VK_CONTROL) & 0x8000) != 0;

			return (!bShift && !bCtrl); // If SHIFT or CONTROL - continue edit
		}

	default:
		{
			return CBCGPGridCtrl::CanEndInplaceEditOnChar( nChar,  nRepCnt,  nFlags);
		}
	}

}

//		by WangZY 2018/06/01
BOOL CQLBCGGridCtrl::OnInplaceEditKeyDown(CBCGPGridRow* pSel, MSG* pMsg)
{
	BOOL bRet = CBCGPGridCtrl::OnInplaceEditKeyDown(pSel,pMsg);
	if (bRet)
	{
		switch (pMsg->wParam)
		{
		case VK_LEFT:
			{
				GoToNextItem ((PrevColumn | Up));
			}
			break;
		case VK_RIGHT:
			{
				GoToNextItem ((NextColumn | Down));
			}
			break;
		case VK_UP:
			{
				GoToNextItem ((PrevRow | Up));
			}
			break;
		case VK_DOWN:
			{
				GoToNextItem ((NextRow | Down));
			}
			break;
		case VK_TAB:
			{
				const BOOL bShift = (::GetAsyncKeyState (VK_SHIFT) & 0x8000) != 0 && !m_bIgnoreShiftBtn;
				GoToNextItem (!bShift ? 
					(NextColumn | Down): 
				(PrevColumn | Up) );
			}
			break;
		default:
			break;
		}
	}
	
	
	return bRet;
}

