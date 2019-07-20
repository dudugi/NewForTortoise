//*******************************************************************************
// COPYRIGHT NOTES
// ---------------
// This is a sample for BCGControlBar Library Professional Edition
// Copyright (C) 1998-2016 BCGSoft Ltd.
// All rights reserved.
//
// This source code can be used, distributed or modified
// only under terms and conditions 
// of the accompanying license agreement.
//*******************************************************************************
//
// CustomCells.h: interface for the CColorGridItem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CUSTOMCELLS_H__2E159741_6592_4EA9_BBB1_B18CEE7D0BD5__INCLUDED_)
#define AFX_CUSTOMCELLS_H__2E159741_6592_4EA9_BBB1_B18CEE7D0BD5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//////////////////////////////////////////////////////////////////////
// CPasswordItem Class

class CPasswordItem : public CBCGPGridItem
{
public:
	CPasswordItem (const CString& strPassword, TCHAR cPassword = _T('*'));
	virtual void WriteToArchive(CArchive& ar);

protected:
	virtual CString FormatItem ();
	virtual CWnd* CreateInPlaceEdit (CRect rectEdit, BOOL& bDefaultFormat);

	TCHAR m_cPassword;
};

/////////////////////////////////////////////////////////////////////////////
// CSliderItem object

class CItemSliderCtrl;

class CSliderItem : public CBCGPGridItem
{
public:
	CSliderItem (long lValue);

	void SetValue (const _variant_t& varValue);

protected:

	virtual CWnd* CreateInPlaceEdit (CRect rectEdit, BOOL& bDefaultFormat);
	virtual BOOL OnSetCursor () const	
	{
		return FALSE; /* Use default */	
	}

	virtual BOOL OnUpdateValue ();
	virtual int GetAlign () const;
};

/////////////////////////////////////////////////////////////////////////////
// CItemSliderCtrl window

class CItemSliderCtrl : public CBCGPSliderCtrl
{
	DECLARE_DYNAMIC(CItemSliderCtrl)

// Construction
public:
	CItemSliderCtrl(CSliderItem* pItem, COLORREF clrBack);

// Attributes
protected:
	CBrush			m_brBackground;
	COLORREF		m_clrBack;
	CSliderItem*	m_pItem;

// Operations
public:
	void Redraw ();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropSliderCtrl)
	//}}AFX_VIRTUAL

	virtual void OnDrawThumb (CDC* pDC, 
		CRect rect, BOOL bIsHighlighted, BOOL bIsPressed, BOOL bIsDisabled,
		BOOL bVert, BOOL bLeftTop, BOOL bRightBottom,
		BOOL bDrawOnGlass);

// Implementation
public:
	virtual ~CItemSliderCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CItemSliderCtrl)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////
// CFileItem Class

class  CFileItem : public CBCGPGridItem
{
// Construction
public:
	CFileItem(const CString& strFileName);

// Overrides
	virtual void OnClickButton (CPoint point);
};

//////////////////////////////////////////////////////////////////////
// CFolderItem Class

class  CFolderItem : public CBCGPGridItem
{
// Construction
public:
	CFolderItem(const CString& strFolderName);

// Overrides
	virtual void OnClickButton (CPoint point);
};

//////////////////////////////////////////////////////////////////////
// CFontItem Class

class CFontItem : public CBCGPGridItem
{
// Construction
public:
	CFontItem(LOGFONT& lf);
	
// Overrides
public:
	virtual void OnClickButton (CPoint point);
	virtual CString FormatProperty ();

// Attributes
protected:
	LOGFONT		m_lf;
	LOGFONT		m_lfOrig;
	DWORD		m_dwFontDialogFlags;
	COLORREF	m_Color;

	virtual BOOL IsValueChanged () const
	{
		return memcmp (&m_lf, &m_lfOrig, sizeof (LOGFONT) != 0) ||
			lstrcmp (m_lf.lfFaceName, m_lfOrig.lfFaceName) != 0;
	}
};

//////////////////////////////////////////////////////////////////////
// CIconGridItem Class

class CIconGridItem : public CBCGPGridItem
{
public:
	CIconGridItem(
		const CImageList& imageListIcons, int nItem);

protected:
	
	virtual void OnDrawValue (CDC* pDC, CRect rect);
	virtual void OnPrintValue (CDC* pDC, CRect rect);
	
	CBCGPToolBarImages	m_imageListIcons;
	int					m_nItem;
};

////////////////////////////////////////////////////////////////////////////////
// CIconListItem Class

class CIconListItem : public CBCGPGridItem
{
public:
	CIconListItem(const _variant_t varValue, const CImageList& imageListIcons,
							CStringList* plstIconNames = NULL);

	virtual void OnSelectCombo ();

protected:

	virtual CWnd* CreateInPlaceEdit (CRect rectEdit, BOOL& bDefaultFormat);
	virtual CComboBox* CreateCombo (CWnd* pWndParent, CRect rect);
	virtual void OnDrawValue (CDC* pDC, CRect rect);
	virtual void OnPrintValue (CDC* pDC, CRect rect);
	virtual	BOOL OnDblClick (CPoint /*point*/) { return FALSE; }

	CBCGPToolBarImages	m_imageListIcons;
	CStringList			m_lstIconNames;
	CString				m_strVal;
};

/////////////////////////////////////////////////////////////////////////////
// CIconCombo window

class CIconCombo : public CBCGPComboBox
{
// Construction
public:
	CIconCombo(CBCGPToolBarImages& imageListIcons, CStringList& lstIconNames);
	CIconListItem* GetIconListItem()
	{
		return m_pIconListItem;
	}
	void SetIconListItem(CIconListItem* pIconListItem)
	{
		m_pIconListItem=pIconListItem;
	}
	
// Attributes
protected:
	CBCGPToolBarImages&	m_imageListIcons;
	CStringList&		m_lstIconNames;
	CIconListItem* m_pIconListItem;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIconCombo)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CIconCombo();

	// Generated message map functions
protected:
	//{{AFX_MSG(CIconCombo)
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnCbnSelEndOk();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

////////////////////////////////////////////////////////////////////////////////
// CProgressItem Class

class CProgressItem : public CBCGPGridItem
{
public:
	CProgressItem (long lValue, long lTotal);

	long GetTotal () const
	{
		return m_lTotal;
	}

protected:
	virtual CWnd* CreateInPlaceEdit (CRect /*rectEdit*/, BOOL& /*bDefaultFormat*/)
	{
		return NULL;
	}

	virtual void OnDrawValue (CDC* pDC, CRect rect);

	long m_lTotal;
};

////////////////////////////////////////////////////////////////////////////////
// CButtonItem Class

class CButtonItem : public CBCGPGridItem
{
	DECLARE_SERIAL(CButtonItem)
public:
	CButtonItem();
	CButtonItem (LPCTSTR lpszText, UINT id);
	

protected:
	virtual BOOL IsPushButton() const
	{
		return TRUE;
	}

	virtual BOOL OnSetCursor () const
	{
		return FALSE; /* Use default */	
	}

	virtual void OnDrawValue (CDC* pDC, CRect rect);
	virtual BOOL OnClickValue (UINT uiMsg, CPoint point);
	virtual BOOL PushChar (UINT nChar);

	UINT	m_id;
};

////////////////////////////////////////////////////////////////////////////////
// CAnimationItem Class

class CAnimationItem : public CBCGPGridItem
{
public:
	CAnimationItem (const CImageList& imageListIcons, LPCTSTR lpszCaption = NULL);
	CAnimationItem (UINT idBitmapRes, LPCTSTR lpszCaption = NULL);

	void DoStep ();
	void SetReady();
	
protected:
	virtual CWnd* CreateInPlaceEdit (CRect /*rectEdit*/, BOOL& /*bDefaultFormat*/)
	{
		return NULL;
	}
	
	virtual void OnDrawValue (CDC* pDC, CRect rect);
	
	CBCGPToolBarImages	m_imageListIcons;
	int					m_nItem;
};

////////////////////////////////////////////////////////////////////////////////
// CSubscriptItem Class

class CSubscriptItem : public CBCGPGridItem
{
public:
	CSubscriptItem (LPCTSTR lpszPostfix, const _variant_t& varValue, DWORD_PTR dwData = 0);

	virtual BOOL IsSubscript () const 
	{
		return TRUE;
	}

protected:
	virtual CString GetValueTooltip ();
	virtual CWnd* CreateInPlaceEdit (CRect /*rectEdit*/, BOOL& /*bDefaultFormat*/)
	{
		return NULL;
	}

	virtual void OnDrawValue (CDC* pDC, CRect rect);
	virtual void OnPrintValue (CDC* pDC, CRect rect);

	CString m_strPostfix;
};

class CSupercriptItem : public CSubscriptItem
{
public:
	CSupercriptItem (LPCTSTR lpszPostfix, const _variant_t& varValue, DWORD_PTR dwData = 0)
		: CSubscriptItem (lpszPostfix, varValue, dwData) {}
	
	virtual BOOL IsSubscript () const 
	{
		return FALSE;
	}
};

/////////////////////////////////////////////////////////////////////////////////////
// CGridColorItem Class (BCGSuite only, BCGControlBar has CBCGPGridColorItem class)

#ifdef _BCGSUITE_INC_

class CGridColorItem : public CBCGPGridItem
{
public:
	CGridColorItem ();
	CGridColorItem(const COLORREF& color, DWORD_PTR dwData = 0);

	// Overrides
public:
	virtual void OnDrawValue (CDC* pDC, CRect rect);

	virtual void OnClickButton (CPoint point);
	virtual BOOL OnEdit (LPPOINT lptClick);
	virtual BOOL OnUpdateValue ();
	virtual CString FormatItem ();

	virtual	CRect GetTooltipRect () const;

protected:
	virtual void AdjustInPlaceEditRect (CRect& rectEdit, CRect& rectSpin);

	// Attributes
public:
	COLORREF GetColor () const
	{
		return m_Color;
	}

	void SetColor (COLORREF color);

	// Attributes
protected:
	COLORREF					m_Color;			// Color value
};

#endif

////////////////////////////////////////////////////////////////////////////////
// CColorListItem Class

class CColorListItem : public CBCGPGridItem
{
public:
	CColorListItem(COLORREF color, const CArray<COLORREF, COLORREF>& arColors, const CStringArray& arColorNames, BOOL bAddNoColor = FALSE);

	COLORREF GetColor() const { return (COLORREF)GetData(); }

protected:
	virtual CWnd* CreateInPlaceEdit (CRect rectEdit, BOOL& bDefaultFormat);
	virtual CComboBox* CreateCombo (CWnd* pWndParent, CRect rect);
	virtual void OnDrawValue (CDC* pDC, CRect rect);
	virtual void OnPrintValue (CDC* pDC, CRect rect);
	virtual void OnSelectCombo ();
	virtual CString FormatItem();
	virtual	CRect GetTooltipRect () const;
	virtual	BOOL OnDblClick (CPoint /*point*/) { return FALSE; }
};

////////////////////////////////////////////////////////////////////////////////
// CTwoButtonsItem Class

class CTwoButtonsItem : public CBCGPGridItem
{
public:
	CTwoButtonsItem(const _variant_t& varValue);
	
	void RedrawButton ();

protected:
	virtual BOOL HasButton () const	{	return TRUE;	}
	virtual void AdjustButtonRect ();
	virtual void OnClickButton (CPoint point);
	virtual void OnDrawButton (CDC* pDC, CRect rectButton);
	virtual void OnDrawValue (CDC* pDC, CRect rect);

	CBCGPToolBarImages	m_images;
	int					m_iClickedButton;
};


//可以显示颜色球的表格项  目前只支持两个颜色
class CBallColorBCGPGridCellItem : public CBCGPGridItem
{
public:
   //构造函数  用于设置两个浮球的颜色  如果为-1  则不显示该球
   CBallColorBCGPGridCellItem (const CString & strText1,const CString & strText2,const CString &strText3,COLORREF color1 = -1,COLORREF color2 = -1,COLORREF color3 = -1);

   void SetDisplayText(const CString & strText1,const CString & strText2,const CString & strText3){m_strText1 = strText1;m_strText2 = strText2;m_strText3 = strText3;}
   void SetColor(COLORREF color1 = -1,COLORREF color2 = -1,COLORREF color3 = -1){m_colorBall1 = color1;m_colorBall2 = color2;m_colorBall3 = color3;}

   void GetDisplayText(CString & strText1,CString & strText2,CString & strText3){strText1 = m_strText1;strText2 = m_strText2;strText3 = m_strText3;}
   void GetColor(COLORREF & color1,COLORREF & color2,COLORREF & color3){color1 = m_colorBall1;color2 = m_colorBall2;color3 = m_colorBall3;}

protected:
   virtual BOOL IsPushButton() const
   {
      return FALSE;
   }

   virtual BOOL OnSetCursor () const
   {
      return FALSE; /* Use default */	
   }

   virtual void OnDrawValue (CDC* pDC, CRect rect);

   void DrawBall(CDC* pDC, CRect &rcBall1, int nCenterOffectWidth, BOOL bDrawText, UINT uiTextFlags,
      COLORREF colorDraw,//圈的颜色
      COLORREF colorBorder,//边..
      COLORREF colorText,//文字
      const CString & strText
      );

   //两个球的颜色
   COLORREF m_colorBall1;
   COLORREF m_colorBall2;
   COLORREF m_colorBall3;
   CString m_strText1;
   CString m_strText2;
   CString m_strText3;
};

/////////////////////////////////////////////////////////////////////////////
#endif // !defined(AFX_CUSTOMCELLS_H__2E159741_6592_4EA9_BBB1_B18CEE7D0BD5__INCLUDED_)
