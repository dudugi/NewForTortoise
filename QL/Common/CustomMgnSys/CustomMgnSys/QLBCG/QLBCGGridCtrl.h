#pragma once
//#include <BCGGridCtrl.h>
#include <map>

struct FILTER_PARAM	// used by filter callback function
{
	// Construction
	FILTER_PARAM () : nCol (-1), bAll (TRUE) {}
	FILTER_PARAM (const FILTER_PARAM& src)
	{
		Copy (src);
	}

	void Clear ()
	{
		nCol = -1;

		strFilter.Empty ();

		bAll = TRUE;
		lstValues.RemoveAll ();
		lstNumericValues.RemoveAll ();
	};

	void Copy (const FILTER_PARAM& src)
	{
		Clear ();

		nCol = src.nCol;
		strFilter = src.strFilter;
		bAll = src.bAll;

		lstValues.AddTail ((CStringList*) &src.lstValues);
		lstNumericValues.AddTail ((CList<int, int>*) &src.lstNumericValues);
	};

	BOOL IsEmpty () const
	{
		if (nCol == -1)
		{
			return TRUE;
		}

		return strFilter.IsEmpty () && lstValues.IsEmpty () && lstValues.IsEmpty ();
	};

	// Attributes
	int				nCol;				// Column index

	CString			strFilter;			// Filter string text

	BOOL			bAll;
	CStringList		lstValues;			// Allowed values
	CList<int, int>	lstNumericValues;	// Allowed numeric values
};


typedef std::map<int/* nColumn*/,CStringList * /* lstFilterContent*/> MAP_FILTER;

struct FILTER_CONTENT
{
	FILTER_CONTENT()
	{

	};

// 接口：
	void Clear()
	{
		auto it = m_mapFilterInfo.begin();
		while(it != m_mapFilterInfo.end())
		{
			it->second->RemoveAll();
			delete it->second;
			it->second = nullptr;
			++it;
		}
		m_mapFilterInfo.clear();
	};

	BOOL AddColumnFilterList(__in int nColumn, __in CStringList &lst)
	{
		if (nColumn<0)
		{
			return FALSE;
		}

		auto it = m_mapFilterInfo.find(nColumn);
		if (it != m_mapFilterInfo.end())
		{
			it->second->RemoveAll();
			it->second->AddTail(&lst);

			return TRUE;
		}

		CStringList *pList = new CStringList();
		pList->AddTail(&lst);
		m_mapFilterInfo.insert(MAP_FILTER::value_type(nColumn,pList));

		return TRUE;
	};

	BOOL GetColumnFilterList(__in int nColumn, __out CStringList &lst)
	{
		lst.RemoveAll();

		if (nColumn<0)
		{
			return FALSE;
		}
		
		auto it = m_mapFilterInfo.find(nColumn);
		if (it != m_mapFilterInfo.end())
		{
			if (it->second != nullptr)
			{
				lst.AddTail(it->second);

				return TRUE;
			}
		}
		
		return FALSE;
	};

// Attributes 属性：
	MAP_FILTER m_mapFilterInfo;
};


//BCG表格相关 add by lida 2017/10/09

class CQLBCGGridCtrl :public  CBCGPGridCtrl
{
	DECLARE_DYNCREATE(CQLBCGGridCtrl)

public:
	CQLBCGGridCtrl(void);
	~CQLBCGGridCtrl(void);

	// Attributes
public:
	FILTER_PARAM			m_param;//过滤参数
	CBCGPToolBarImages		m_ImagesHeaderBtn;
	FILTER_CONTENT m_infoFilter;	//标题过滤器信息	by WangZY 2018/03/06

   UINT      m_nDirection;     //回车跳转方向       add by lida 2018/05/29  
   BOOL              m_bEnableEnterGo; //是否使用回车跳转   add by lida 2018/05/29



protected:
	int						m_nLastClickedColumn;
	BCGP_FILTER_COLUMN_INFO m_FilterMenuResults;

   int m_nRowHeightEx;

	// Operations
public:
	static LRESULT CALLBACK pfnFilterCallback (WPARAM wParam, LPARAM lParam);

	void EnableFilter_My(BOOL bEnable = TRUE);	//开启过滤器

	void GetStringList (CStringList& lst, int nColumn);
	void SetDefaultDemoFilter (int nColumn);
	void OnApplyFilter();
	void OnSortAZ();
	void OnSortZA();
	void OnFilterSet();
	void OnFilterClear();

   virtual void SetRowHeight(const int & nHeight);
   virtual void SetRowHeight();

	BOOL IsFilterExist () const
	{
		return !m_param.IsEmpty ();
	}

	CString GetCurFilterButtonDescription () const;

	void CheckHeaderBoxClick(BOOL bCheck);

	CBCGPGridFilterParams * GetTitleFilterInfos();

   virtual BOOL PreTranslateMessage(MSG* pMsg);

   void ClearTitleFilter(); //清除标题过滤数据 yangjr 2018/7/4

   BOOL IsTitleFilterEmpty();//标题过滤数据是否为空  yangjr 2018/7/6

protected:
	virtual int GetHeaderMenuButtonImageIndex (int nColumn, BOOL bSortArrow) const;
//	virtual void OnHeaderMenuButtonClick (int nColumn, CRect rectMenuButton);
	virtual void GetHeaderMenuButtonTooltip (int nColumn, CString& strText) const;
	virtual void OnHeaderCheckBoxClick  ( int  nColumn ) ;
	virtual BOOL OnTrackHeader ()
	{
		return FALSE; // do not resize columns inside client area by mouse
	}
	virtual void OnHeaderColumnRClick (int /*nColumn*/);		//右键表头 add by lida 2017/12/11


   void GotoNextRowCell();     //跳转到下一行的cell add by lida  2018/05/29

	virtual BOOL CanEndInplaceEditOnChar (UINT nChar, UINT nRepCnt, UINT nFlags) const;
	
	virtual BOOL OnInplaceEditKeyDown (CBCGPGridRow* pSel, MSG* pMsg);


protected:

	afx_msg BOOL OnNeedTipText(UINT id, NMHDR* pNMH, LRESULT* pResult);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg LRESULT OnFillAutoCompleteList(WPARAM wp, LPARAM lp);
	DECLARE_MESSAGE_MAP()
};

