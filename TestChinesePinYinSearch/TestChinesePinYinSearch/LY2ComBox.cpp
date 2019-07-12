// LComBox.cpp : 实现文件
//

#include "stdafx.h"

#include "LY2ComBox.h"
#include <vector>
#include <algorithm>
#include <imm.h>

using namespace std;

#pragma comment(lib, "imm32.lib")

// CLY2ComBox

enum
{
   COMMAND_EDITCHANGE = 10001,
   COMMAND_COMPOSING = 10002
};

static CString ConvertChineseUnicodeToPyt(const wchar_t* chrstr);
static CString ConvertChineseToShorthand(const wchar_t* chrstr);

IMPLEMENT_DYNAMIC(CLY2ComBox, CComboBox)

CLY2ComBox::CLY2ComBox()
{
	m_pEdit = NULL;
	m_pListBox = NULL;
	m_pEdtFont = NULL;
	m_pListFont = NULL;
	m_nEdtFontPtSize = 0;
	m_nListFontPtSize = 0;
	m_csListFontName = _T("");
	m_csEdtFontName = _T("");
	m_clrEditText = RGB(0, 0, 0);
	m_clrListText = RGB(0, 0, 0);
	m_clrEditTextBg = RGB(255, 255, 255);
	m_clrListTextBg = RGB(255, 255, 255);
	m_bEditTextHasBgColor = FALSE;
	m_bListTextHasBgColor = FALSE;
	m_bReadOnly = FALSE;

	m_bBtnFlags = FALSE;
	m_bFocus = FALSE;
	m_bDown = FALSE;
	m_bPaint = FALSE;
	m_clrEdtFrame = RGB(148, 148, 148);

	m_clr3DHilight = RGB(181, 207, 231);
	m_clr3DShadow  = RGB(61, 123, 173);
	m_clr3DFace    = RGB(198, 201, 210);

	m_bDisableAC = FALSE;
	m_bAComplete = FALSE;

	m_bmButton.LoadBitmap(IDB_BUTTON);

	m_fsFremeStyle = WIN7;
	// VC win7 组合框默认边框颜色值
	m_clrNormalCombFrameLeft = RGB( 226, 227, 234 );
	m_clrNormalCombFrameTop = RGB( 171, 173, 179);
	m_clrNormalCombFrameRight = RGB( 219, 223, 230);
	m_clrNormalCombFrameBottom = RGB( 227, 233, 239);
	m_clrFocusCombFrameLeft = RGB( 181, 207, 231);
	m_clrFocusCombFrameTop = RGB( 61, 123, 173);
	m_clrFocusCombFrameRight = RGB( 164, 201, 227);
	m_clrFocusCombFrameBottom = RGB( 183, 217, 237);
	// 
	m_clrNormalCombFrame = RGB( 233, 236, 240);
	m_clrFocusCombFrame = RGB( 119, 162, 192);

	//
	m_clrListItemBg = RGB(51, 153, 255);
	m_clrListHilightItemBg = RGB(51, 153, 255);
	m_clrListFrame = RGB(51, 153, 255);
	m_clrListEvenItem = RGB( 255, 255, 255);
	m_clrListOddItem = RGB( 255, 255, 255);
	m_clrListItemPartLine = RGB( 255, 255, 255);
	m_clrListHilightItemText = RGB( 255, 255, 255);

	m_bListItemFocus = FALSE;
	m_nPreFocusListItem = 0;
	m_nCurrFocusListItem = 0;
	m_bAllowDel = TRUE;

   m_flagVKBack = FALSE;

   m_bDropdownShowAll = TRUE;

   m_nCaretStart = -1;
   m_nCaretEnd = -1;
}

CLY2ComBox::~CLY2ComBox()
{
	if(m_pEdit)
		m_pEdit = NULL;

	if(m_pListBox)
		m_pListBox = NULL;

	if(m_pEdtFont)
	{
		delete m_pEdtFont;
		m_pEdtFont = NULL;
	}

	if(m_pListFont)
	{
		delete m_pListFont;
		m_pListFont = NULL;
	}

}


BEGIN_MESSAGE_MAP(CLY2ComBox, CComboBox)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEHOVER()
	ON_WM_MOUSELEAVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_CONTROL_REFLECT(CBN_DROPDOWN, &CLY2ComBox::OnCbnDropdown)
	ON_CONTROL_REFLECT(CBN_CLOSEUP, &CLY2ComBox::OnCbnCloseup)
	ON_CONTROL_REFLECT(CBN_SETFOCUS, OnSetFocus)
	ON_CONTROL_REFLECT(CBN_KILLFOCUS, OnKillFocus)
	ON_WM_SETCURSOR()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_WM_SYSCOLORCHANGE()
	ON_CONTROL_REFLECT(CBN_EDITUPDATE, &CLY2ComBox::OnCbnEditupdate)
	ON_CONTROL_REFLECT(CBN_SELCHANGE, &CLY2ComBox::OnCbnSelchange)
   ON_CONTROL_REFLECT_EX(CBN_EDITCHANGE, &CLY2ComBox::OnCbnEditchange)
   ON_COMMAND(COMMAND_EDITCHANGE, &CLY2ComBox::OnCbnCommandEditchange)
   ON_COMMAND(COMMAND_COMPOSING, &CLY2ComBox::OnCbnCommandEditComposing)
END_MESSAGE_MAP()

void CLY2ComBox::OnCbnCommandEditchange()
{
   OnCbnEditchange();
}

LRESULT CLY2ComBox::WindowProc( UINT message, WPARAM wParam, LPARAM lParam )
{
	CRect rcComboClient;
	GetClientRect(&rcComboClient);

	if(WM_CTLCOLORBTN==message)
	{
		HWND hWndBtn = (HWND)lParam;
		CButton* pButton = (CButton*)FromHandle(hWndBtn);
		CRect rcBtnClient;
		pButton->GetClientRect(&rcBtnClient);
		int i = 0;
	}

	if(WM_CTLCOLORSCROLLBAR==message)
	{
		HWND hWndBtn = (HWND)lParam;
		CScrollBar* pButton = (CScrollBar*)FromHandle(hWndBtn);
		CRect rcBtnClient;
		pButton->GetClientRect(&rcBtnClient);
		int i = 0;
	}

	if(WM_CTLCOLOREDIT==message)
	{
		HWND hWndEdit = (HWND)lParam;
		m_pEdit = (CEdit*)FromHandle(hWndEdit);
	}

	if(WM_CTLCOLORSTATIC==message)
	{
		HWND hWndStatic = (HWND)lParam;
		CStatic* pStatic = (CStatic*)FromHandle(hWndStatic);
		CRect rcStaticClient;
		pStatic->GetClientRect(&rcStaticClient);
	}

	if(WM_CTLCOLORLISTBOX==message)
	{
		HWND hWndListBox = (HWND)lParam;
		m_pListBox = (CListBox*)FromHandle(hWndListBox);

		if(m_pListBox)
		{
			CRect rcListBoxClient;
			m_pListBox->GetClientRect(&rcListBoxClient);
			int nItemCount = m_pListBox->GetCount();
			
			if(CB_ERR!=nItemCount)
			{
				CPoint point;
				GetCursorPos(&point);
				m_pListBox->ScreenToClient(&point);

				CRect rcItem;
				for(int i=0; i<nItemCount; i++)
				{
					m_pListBox->GetItemRect(i, &rcItem);
					if(rcItem.PtInRect(point))
					{
						m_nPreFocusListItem = m_nCurrFocusListItem;
						m_nCurrFocusListItem = i;
						if(m_nCurrFocusListItem != m_nPreFocusListItem)
						{
							CRect rcFocus(rcItem);
							//rcFocus.left = rcFocus.right - 18;

							CRect rcPreItem;
							m_pListBox->GetItemRect(m_nPreFocusListItem, &rcPreItem);
							m_pListBox->InvalidateRect(&rcPreItem);

							if(rcFocus.PtInRect(point))
							{
								m_bListItemFocus = TRUE;
								m_nPreFocusListItem = m_nCurrFocusListItem;
								m_pListBox->InvalidateRect(&rcItem);
							}
							else
							{
								m_bListItemFocus = FALSE;
								m_nCurrFocusListItem = m_nPreFocusListItem;
								m_pListBox->InvalidateRect(&rcItem);								
							}
						} // end if(m_nCurrFocusListItem != m_nPreFocusListItem)
						break;
					} // end if(rcItem.PtInRect(point))
				} // end for
			} // end if(CB_ERR!=nItemCount)
		} // end if(m_pListBox)
	} // end if(WM_CTLCOLORLISTBOX==message)

   if (WM_SETTEXT == message)
   {
      m_strLastEditText = (LPCTSTR)lParam;
   }

	return CComboBox::WindowProc(message, wParam, lParam);
}

WNDPROC CLY2ComBox::m_CBoldProc = 0;

// CLY2ComBox 消息处理程序
LRESULT CLY2ComBox::CBProc(HWND hWnd,  UINT message, WPARAM wParam, LPARAM lParam )
{
   switch(message)
   {
   case WM_KEYDOWN:
      break;
   case WM_IME_ENDCOMPOSITION:
      {
         HWND hCombo = ::GetParent(hWnd);
         ::PostMessage(hCombo, WM_COMMAND, COMMAND_EDITCHANGE, 0);
      }
      break;
   case WM_IME_COMPOSITION:
      {
         HWND hCombo = ::GetParent(hWnd);
         ::PostMessage(hCombo, WM_COMMAND, COMMAND_COMPOSING, 0);
      }
      break;
   }
   return CallWindowProc(m_CBoldProc, hWnd, message, wParam, lParam);
}

void CLY2ComBox::PreSubclassWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	
	// 默认情况下，创建和和系统一样的字体
	CFont* pFont = GetFont();
	LOGFONT lg;
	pFont->GetLogFont(&lg);
	m_nEdtFontPtSize = lg.lfHeight*8;
	m_csEdtFontName = lg.lfFaceName;
	m_nListFontPtSize = m_nEdtFontPtSize;
	m_csListFontName = m_csEdtFontName;
	// 创建字体
	SetEdtFontHelper();
	SetListFontHelper();

   {
      ::CWnd *pWnd = this->GetWindow(GW_CHILD);
      while(pWnd)
      {
         TCHAR classname[256];
         ::GetClassName(pWnd->m_hWnd, classname, 256);
         if(lstrcmpi(classname, _T("Edit")) == 0)
            break;
         if(pWnd)
            pWnd = pWnd->GetNextWindow();
      }
      CEdit *pEdit = (CEdit*)pWnd;
      m_pEdit = pEdit;

      auto CBoldProc = (WNDPROC)SetWindowLong(pEdit->GetSafeHwnd(), GWL_WNDPROC, (LONG)CBProc); 
      if (m_CBoldProc == 0)
      {
         m_CBoldProc = CBoldProc;
      }
   }

	CComboBox::PreSubclassWindow();
}

HBRUSH CLY2ComBox::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CComboBox::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	// 编辑框设置
	if(nCtlColor==CTLCOLOR_EDIT)
	{
		CFont* font = new CFont;
		font->CreatePointFont(m_nEdtFontPtSize, m_csEdtFontName);
		pDC->SelectObject(font);
		pDC->SetTextColor(m_clrEditText);
		
		if(m_bEditTextHasBgColor)
			pDC->SetBkColor(m_clrEditTextBg);
		else
			pDC->SetBkMode(TRANSPARENT);
		
		HBRUSH B = CreateSolidBrush(RGB(255,255,255));
		return (HBRUSH) B; //返回画刷句柄
	}

	// 列表框设置
	if(nCtlColor==CTLCOLOR_LISTBOX)
	{
		CFont* font = new CFont;
		font->CreatePointFont(m_nListFontPtSize, m_csListFontName);
		pDC->SelectObject(font);
		pDC->SetTextColor(m_clrListText);
		
		if(m_bListTextHasBgColor)
			pDC->SetBkColor(m_clrListTextBg);
		else
			pDC->SetBkMode(TRANSPARENT);

		pDC->SetBkColor(RGB(0, 255, 0));
		HBRUSH B = CreateSolidBrush(RGB(255, 255, 255));
		return (HBRUSH) B; //返回画刷句柄
	}

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

///////////////////////////////  功能函数  ///////////////////////////////////////////

void CLY2ComBox::SetEdtFontHelper()
{
	if(m_pEdtFont)
	{
		if(m_pEdtFont->m_hObject)
			m_pEdtFont->DeleteObject();
	}
	m_pEdtFont = new CFont;

	LOGFONT lgFont;
	lgFont.lfCharSet = DEFAULT_CHARSET;
	lgFont.lfClipPrecision = 0;
	lgFont.lfEscapement = 0;
	_tcscpy_s(lgFont.lfFaceName, m_csEdtFontName);
	lgFont.lfHeight = m_nEdtFontPtSize;
	lgFont.lfItalic = 0;
	lgFont.lfOrientation = 0;
	lgFont.lfOutPrecision = 0;
	lgFont.lfPitchAndFamily = 2;
	lgFont.lfQuality = 0;
	lgFont.lfStrikeOut = 0;
	lgFont.lfUnderline = 0;
	lgFont.lfWidth = 0;
	lgFont.lfWeight = FW_NORMAL;

	m_pEdtFont->CreatePointFontIndirect(&lgFont);
	SetFont(m_pEdtFont);
}

void CLY2ComBox::SetListFontHelper()
{
	if(m_pListFont)
	{
		if(m_pListFont->m_hObject)
			m_pListFont->DeleteObject();
	}
	m_pListFont = new CFont;

	LOGFONT lgFont;
	lgFont.lfCharSet = DEFAULT_CHARSET;
	lgFont.lfClipPrecision = 0;
	lgFont.lfEscapement = 0;
	_tcscpy_s(lgFont.lfFaceName, m_csListFontName);
	lgFont.lfHeight = m_nListFontPtSize;
	lgFont.lfItalic = 0;
	lgFont.lfOrientation = 0;
	lgFont.lfOutPrecision = 0;
	lgFont.lfPitchAndFamily = 2;
	lgFont.lfQuality = 0;
	lgFont.lfStrikeOut = 0;
	lgFont.lfUnderline = 0;
	lgFont.lfWidth = 0;
	lgFont.lfWeight = FW_NORMAL;

	m_pListFont->CreatePointFontIndirect(&lgFont);
}

void CLY2ComBox::SetCombNewFont( int nPtSize, CString csFontName/*=_T("微软雅黑")*/ )
{
	SetEdtNewFont(nPtSize, csFontName);
	SetListNewFont(nPtSize, csFontName);
}

void CLY2ComBox::SetEdtNewFont( int nPtSize, CString csFontName/*=_T("微软雅黑")*/ )
{
	if(nPtSize>0)
		m_nEdtFontPtSize = nPtSize;
	m_csEdtFontName = csFontName;
	SetEdtFontHelper();
}

void CLY2ComBox::SetListNewFont( int nPtSize, CString csFontName/*=_T("微软雅黑")*/ )
{
	if(nPtSize>0)
		m_nListFontPtSize = nPtSize;
	m_csListFontName = csFontName;
	SetListFontHelper();
}

void CLY2ComBox::SetCombTextColor( COLORREF clrCombText )
{
	SetEdtTextColor(clrCombText);
	SetListTextColor(clrCombText);
}

void CLY2ComBox::SetEdtTextColor( COLORREF clrEdtText )
{
	m_clrEditText = clrEdtText;
}

void CLY2ComBox::SetListTextColor( COLORREF clrListText )
{
	m_clrListText = clrListText;
}

void CLY2ComBox::SetEdtTextBgColor( BOOL bEditTextHasBgColor, COLORREF clrEditTextBg/*=RGB(255, 255, 255)*/ )
{
	m_bEditTextHasBgColor = bEditTextHasBgColor;
	if(bEditTextHasBgColor)
		m_clrEditTextBg = clrEditTextBg;
}

void CLY2ComBox::SetListTextBgColor( BOOL bListTextHasBgColor, COLORREF clrListTextBg/*=RGB(255, 255, 255)*/ )
{
	m_bListTextHasBgColor = bListTextHasBgColor;
	if(bListTextHasBgColor)
		m_clrListTextBg = clrListTextBg;
}

void CLY2ComBox::SetEdtReadOnly( BOOL bEdtReadOnly/*=TRUE*/ )
{
	m_bReadOnly = bEdtReadOnly;
	// 获取组合框中的编辑框窗口指针，设置只读属性
	::CWnd *pWnd = this->GetWindow(GW_CHILD);
	while(pWnd)
	{
		TCHAR classname[256];
		::GetClassName(pWnd->m_hWnd, classname, 256);
		if(lstrcmpi(classname, _T("Edit")) == 0)
			break;
		if(pWnd)
			pWnd = pWnd->GetNextWindow();
	}
	CEdit *pEdit = (CEdit*)pWnd;
	m_pEdit = pEdit;
	m_pEdit->SetReadOnly(m_bReadOnly);
}

void CLY2ComBox::AotuAdjustDroppedWidth()
{
	// 计算下拉列表最长宽度
	CString csItem;
	int nWidth = 0; //GetDroppedWidth();
	CSize sz;

	CDC* pDC = this->GetDC();
	CFont* pOldFont = pDC->SelectObject(m_pListFont); // m_pListFont 在PreSubclassWindow 中已经初始化，因此有效

	for(int i=0; i<GetCount(); i++)
	{
		GetLBText(i, csItem);
		sz = pDC->GetTextExtent(csItem);
		if(sz.cx>nWidth)
			nWidth = sz.cx;
	}

	// 如果非只读，则预留出删除叉叉的宽度
	if(m_bReadOnly)
		SetDroppedWidth(nWidth);
	else
		SetDroppedWidth(nWidth+30);

	pDC->SelectObject(pOldFont);
	ReleaseDC(pDC);
}

/////////////////////////////////  消息函数  /////////////////////////////////////////
void CLY2ComBox::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CComboBox::OnPaint()

	//// 绘制编辑框边框
	//CPen pen(PS_SOLID, 1, m_clrEdtFrame);
	//CPen* pOldPen = dc.SelectObject(&pen);
	//CRect rcClient;
	//this->GetClientRect(&rcClient);
	//rcClient.InflateRect(1, 1);
	//CPoint pt(5, 5);
	//dc.RoundRect(rcClient, pt);
	//dc.SelectObject(&pOldPen);

	OnNoFlickerPaint(&dc);

	COMBOBOXINFO combInfo;
	combInfo.cbSize = sizeof(COMBOBOXINFO);
	GetComboBoxInfo(&combInfo);
	if(combInfo.stateButton==8)
		m_bDown = TRUE;

	DrawBtnImg(&dc, combInfo.rcButton); // 绘制右边下拉按钮

}

void CLY2ComBox::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CComboBox::OnMouseMove(nFlags, point);
}

void CLY2ComBox::OnMouseHover(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CComboBox::OnMouseHover(nFlags, point);
}

void CLY2ComBox::OnMouseLeave()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(m_bListItemFocus)
		m_bListItemFocus = FALSE;

	CComboBox::OnMouseLeave();
}

void CLY2ComBox::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	m_bDown = TRUE;

	CComboBox::OnLButtonDown(nFlags, point);
}

void CLY2ComBox::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	m_bDown = FALSE;
	Invalidate();

	CComboBox::OnLButtonUp(nFlags, point);
}

void CLY2ComBox::OnCbnDropdown()
{
	// TODO: 在此添加控件通知处理程序代码
	//if(m_pListBox && m_pListBox->GetCount()>0)
	//{
	//	CRect rcItem;
	//	m_nCurrFocusListItem = 0;
	//	m_pListBox->GetItemRect(0, &rcItem);
	//	m_pListBox->InvalidateRect(&rcItem);
	//}

   if (m_bDropdownShowAll)
   {
      //DWORD dwPos = GetEditSel();
      //int nStart = LOWORD(dwPos);
      //int nEnd = HIWORD(dwPos);
      //CString sText;
      //GetWindowText(sText); //如果不备份，会导致有前方一致候选项的情况下的文字消失
      SetRedraw(FALSE);
      while(this->GetCount() > 0)
         CComboBox::DeleteString(0);

      for (auto Iter = m_vecItem.begin(); Iter != m_vecItem.end(); ++Iter)
      {
         AddString(Iter->m_sOrg);
      }
      SetRedraw(TRUE);
//       SetWindowText(sText);
//       SetEditSel(nStart, nEnd);
      SetWindowText(m_strLastEditText);
      SetEditSel(m_nCaretStart, m_nCaretEnd);
   }

	// 下拉列表标识重设
	m_nPreFocusListItem = -1;
	m_nCurrFocusListItem = -1;
	m_bListItemFocus = TRUE;

	m_bBtnFlags = TRUE;
	Invalidate(FALSE);
}

void CLY2ComBox::OnCbnCloseup()
{
	// TODO: 在此添加控件通知处理程序代码
   SetWindowText(m_strLastEditText);
   SetEditSel(m_nCaretStart, m_nCaretEnd);

	m_bBtnFlags = FALSE;
	Invalidate(FALSE);
}

void CLY2ComBox::OnKillFocus(/*CWnd* pNewWnd*/)
{
	//CComboBox::OnKillFocus(pNewWnd);
	
	// TODO: 在此处添加消息处理程序代码

	m_bFocus = FALSE;
	CClientDC dc(this);
	DrawCombo(&dc, NORMAL, m_clr3DFace, m_clr3DFace);
	//DrawCombo(&dc, NORMAL, RGB(183, 217, 237), m_clr3DFace);
}

void CLY2ComBox::OnSetFocus()
{
	//CComboBox::OnSetFocus(pOldWnd);

	// TODO: 在此处添加消息处理程序代码

	m_bFocus = TRUE;
	CClientDC dc(this);
	DrawCombo(&dc, RAISED, m_clr3DShadow, m_clr3DHilight);
	
}

BOOL CLY2ComBox::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(message==WM_MOUSEMOVE)
	{
		CRect rcWnd;
		GetWindowRect(&rcWnd);
		if(rcWnd.PtInRect(GetCurrentMessage()->pt))
		{
			SetTimer(1, 10, NULL);
			OnTimer(1);
		}
	}

	return CComboBox::OnSetCursor(pWnd, nHitTest, message);
}

void CLY2ComBox::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	UNREFERENCED_PARAMETER(nIDEvent);

	CClientDC dc(this);
	if(m_bDown)
	{
		KillTimer(1);
		if(m_bPaint)
		{
			DrawCombo(&dc, PRESSED, m_clr3DShadow, m_clr3DHilight);
			m_bPaint = FALSE;
		}
	}
	else if(!PointInRect() && !m_bFocus)
	{
		KillTimer(1);
		if(m_bPaint)
		{
			DrawCombo(&dc, PRESSED, m_clr3DFace, m_clr3DFace);
			//DrawCombo(&dc, NORMAL, RGB(183, 217, 237), m_clr3DFace);
			m_bPaint = FALSE;
		}
	}
	else
	{
		if(m_bPaint)
			return ;
		else
		{
			m_bPaint = TRUE;
			DrawCombo(&dc, PRESSED, m_clr3DShadow, m_clr3DHilight);
		}
	}

	CComboBox::OnTimer(nIDEvent);
}

BOOL CLY2ComBox::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	UNREFERENCED_PARAMETER(pDC);
	return TRUE;

	return CComboBox::OnEraseBkgnd(pDC);
}

void CLY2ComBox::OnSysColorChange()
{
	CComboBox::OnSysColorChange();

	//m_clr3DHilight = ::GetSysColor(COLOR_3DHILIGHT);
	//m_clr3DShadow  = ::GetSysColor(COLOR_3DSHADOW);
	//m_clr3DFace    = ::GetSysColor(COLOR_3DFACE);

	m_clr3DHilight = RGB(181, 207, 231);
	m_clr3DShadow  = RGB(61, 123, 173);
	m_clr3DFace    = RGB(226, 227, 234);
}

void CLY2ComBox::OnCbnEditupdate()
{
	// TODO: 在此添加控件通知处理程序代码

	//if(m_bAComplete)
	//{
	//	if (m_bDisableAC)
	//	{
	//		Default();
	//	}
	//	else
	//	{
	//		// Get the text in the edit box
	//		CString strItemTyped;
	//		GetWindowText(strItemTyped);
	//		int nLength = strItemTyped.GetLength();

	//		if (nLength >= 1)
	//		{
	//			// Currently selected range
	//			DWORD dwCurSel = GetEditSel();
	//			WORD dStart = LOWORD(dwCurSel);
	//			WORD dEnd   = HIWORD(dwCurSel);

	//			// Search for, and select in, and string in the combo box that is prefixed
	//			// by the text in the edit box
	//			if (SelectString(-1, strItemTyped) == CB_ERR)
	//			{
	//				SetWindowText(strItemTyped);     // No text selected, so restore what was there before
	//				if (dwCurSel != CB_ERR) {
	//					SetEditSel(dStart, dEnd);   //restore cursor postion
	//				}
	//			}

	//			// Set the text selection as the additional text that we have added
	//			if (dEnd < nLength && dwCurSel != CB_ERR) {
	//				SetEditSel(dStart, dEnd);
	//			}
	//			else {
	//				SetEditSel(nLength, -1);
	//			}
	//		}
	//	}
	//}

}

//BOOL CLY2ComBox::PreTranslateMessage(MSG* pMsg)
//{
//	// TODO: 在此添加专用代码和/或调用基类
//
//	if (m_bAComplete)
//	{
//		// Make sure that the keystrokes continue to the edit control.
//		if (pMsg->message == WM_KEYDOWN || pMsg->message==WM_KEYUP)
//		{
//			if (pMsg->message == WM_KEYDOWN)
//			{
//				if (pMsg->wParam == VK_DELETE ||
//					pMsg->wParam == VK_BACK)
//				{
//					m_bDisableAC = TRUE;
//				}
//			}
//
//			if (pMsg->message == WM_KEYUP)
//			{
//				if (pMsg->wParam == VK_DELETE ||
//					pMsg->wParam == VK_BACK)
//				{
//					m_bDisableAC = FALSE;
//				}
//			}
//
//			::TranslateMessage(pMsg);
//			::DispatchMessage(pMsg);
//
//			return TRUE;
//		}
//	}
//
//	return CComboBox::PreTranslateMessage(pMsg);
//}

/////////////////////////////  功能函数  ///////////////////////////////////////

void CLY2ComBox::SetAutoComplete( BOOL bAutoComplete )
{
	m_bAComplete = bAutoComplete;
}

void CLY2ComBox::SetFrameStyle( FRAMESTYLE fsFrameStyle )
{
	m_fsFremeStyle = fsFrameStyle;
}

void CLY2ComBox::Set3DFrameColor( COLORREF clr3Dface, COLORREF clr3DHilight, COLORREF clr3DShadow )
{
	m_clr3DFace = clr3Dface;
	m_clr3DHilight = clr3DHilight;
	m_clr3DShadow = clr3DShadow;
}

void CLY2ComBox::Set3DFrameColorDefault()
{
	m_clr3DHilight = RGB(181, 207, 231);
	m_clr3DShadow  = RGB(61, 123, 173);
	m_clr3DFace    = RGB(198, 201, 210);
}

void CLY2ComBox::SetEdtFrameColor( COLORREF clrEdtFrame )
{
	m_clrEdtFrame = clrEdtFrame;
	m_clr3DFace = clrEdtFrame;
	m_clr3DHilight = clrEdtFrame;
	m_clr3DShadow = clrEdtFrame;
}

void CLY2ComBox::DrawBtnImg( CDC* pDC, CRect rcButton )
{
	CBitmap* pOldBitmap;
	CDC* pMemDC = new CDC;
	BITMAP bitmapBtn;
	m_bmButton.GetBitmap(&bitmapBtn); // 获取位图信息
	// 针对本例图片进行的特定计算
	int nLeft = (rcButton.Width()-bitmapBtn.bmWidth/2)/2;
	int nTop = (rcButton.Height()-bitmapBtn.bmHeight/2)/2;

	// 读位图到内存
	pMemDC->CreateCompatibleDC(pDC);
	pOldBitmap = pMemDC->SelectObject(&m_bmButton);
	// 根据不同的状态读取图片的不同部分，本例中只有两种
	//if(m_bDown || m_bFocus)
	if(PointInBtn())
		pDC->BitBlt(rcButton.left, rcButton.top+nTop, rcButton.Width()/2, rcButton.Height(), pMemDC, rcButton.Width()/2+1, 0, SRCCOPY);
	else
		pDC->BitBlt(rcButton.left, rcButton.top+nTop, rcButton.Width()/2, rcButton.Height(), pMemDC, 0, 0, SRCCOPY);

	pMemDC->SelectObject(pOldBitmap);

	// 释放内存， 删除DC
	ReleaseDC(pMemDC);
	delete pMemDC;
	pMemDC = NULL;
}

void CLY2ComBox::OnNoFlickerPaint(CDC* pDC)
{
	CRect rcClient;
	GetClientRect(&rcClient);

	CDC dcMem; // 内存设备上下文（DC）
	dcMem.CreateCompatibleDC(pDC); // 创建兼容设备DC
	dcMem.SetMapMode(pDC->GetMapMode()); // 设置映射模式

	CBitmap bitmap; // 创建兼容位图，使其能容下整个窗口图像
	bitmap.CreateCompatibleBitmap(pDC, rcClient.Width(), rcClient.Height());

	CBitmap* pOldBitmap = dcMem.SelectObject(&bitmap); // 用内存DC选择位图

	//dcMem.FillSolidRect(rcClient, m_clr3DFace);
	dcMem.FillSolidRect(rcClient, RGB(255, 255, 255));
	//rcClient.DeflateRect(1, 1);

	if(PointInRect() || m_bFocus)
		DrawCombo(&dcMem, RAISED, m_clr3DShadow, m_clr3DHilight);
	else
		DrawCombo(&dcMem, NORMAL, m_clr3DFace/*RGB(183, 217, 237)*/, m_clr3DFace);

	pDC->BitBlt(rcClient.left, rcClient.top, rcClient.Width(), rcClient.Height(),
		&dcMem, rcClient.left, rcClient.top, SRCCOPY);

	dcMem.SelectObject(pOldBitmap);
	bitmap.DeleteObject();
	dcMem.DeleteDC();
}

void CLY2ComBox::DrawCombo(CDC* pDC, STATE eState, COLORREF clrTopLeft, COLORREF clrBottomRight)
{
	CRect rcItem;
	GetClientRect(&rcItem);
	if(m_fsFremeStyle==THREEDGR)
		pDC->Draw3dRect(rcItem, clrTopLeft, clrBottomRight);
	else if(m_fsFremeStyle==ONLYONE)
		pDC->Draw3dRect(rcItem, m_clr3DFace, m_clr3DFace);
	else if(m_fsFremeStyle==TWO)
		pDC->Draw3dRect(rcItem, clrBottomRight, clrBottomRight);
	else if(m_fsFremeStyle==WIN7)
	{
		// 用系统默认颜色绘制
		// int nRound = 2;
		if(PointInRect() || m_bFocus)
		{
			CPen bgItemPen;
			bgItemPen.CreatePen(PS_SOLID, 1, m_clrFocusCombFrame);
			CPen* pOldPen = pDC->SelectObject(&bgItemPen);
			//pDC->RoundRect(&rcItem, CPoint(nRound, nRound));
			pDC->SelectObject(pOldPen);
			bgItemPen.DeleteObject();
			// 左
			bgItemPen.CreatePen(PS_SOLID, 1, m_clrFocusCombFrameLeft);
			pOldPen = pDC->SelectObject(&bgItemPen);
			pDC->MoveTo(rcItem.left, rcItem.top);
			pDC->LineTo(rcItem.left, rcItem.bottom);
			bgItemPen.DeleteObject();
			// 上
			bgItemPen.CreatePen(PS_SOLID, 1, m_clrFocusCombFrameTop);
			pOldPen = pDC->SelectObject(&bgItemPen);
			pDC->MoveTo(rcItem.left, rcItem.top);
			pDC->LineTo(rcItem.right, rcItem.top);
			bgItemPen.DeleteObject();
			// 右
			bgItemPen.CreatePen(PS_SOLID, 1, m_clrFocusCombFrameRight);
			pOldPen = pDC->SelectObject(&bgItemPen);
			pDC->MoveTo(rcItem.right, rcItem.top);
			pDC->LineTo(rcItem.right, rcItem.bottom);
			bgItemPen.DeleteObject();
			// 下
			bgItemPen.CreatePen(PS_SOLID, 1, m_clrFocusCombFrameBottom);
			pOldPen = pDC->SelectObject(&bgItemPen);
			pDC->MoveTo(rcItem.left, rcItem.bottom);
			pDC->LineTo(rcItem.right, rcItem.bottom);
			bgItemPen.DeleteObject();
			// 设置角点的像素颜色
			// 左上
			pDC->SetPixel(CPoint(rcItem.left, rcItem.top), RGB(173, 196, 215));
			pDC->SetPixel(CPoint(rcItem.left+1, rcItem.top), RGB(92, 147, 188));
			pDC->SetPixel(CPoint(rcItem.left+1, rcItem.top+1), RGB(198, 222, 236));
			// 右上
			pDC->SetPixel(CPoint(rcItem.right, rcItem.top), RGB(173, 196, 215));
			pDC->SetPixel(CPoint(rcItem.right-1, rcItem.top), RGB(92, 147, 188));
			pDC->SetPixel(CPoint(rcItem.right-1, rcItem.top+1), RGB(198, 222, 236));
			// 左下
			pDC->SetPixel(CPoint(rcItem.left, rcItem.bottom), RGB( 218, 228, 237));
			pDC->SetPixel(CPoint(rcItem.left+1, rcItem.bottom-1), RGB(198, 222, 238));
			// 右下
			pDC->SetPixel(CPoint(rcItem.right, rcItem.bottom), RGB( 218, 228, 237));
			pDC->SetPixel(CPoint(rcItem.right-1, rcItem.bottom-1), RGB(198, 222, 238));
		}
		else
		{
			CPen bgItemPen;
			bgItemPen.CreatePen(PS_SOLID, 1, m_clrNormalCombFrame);
			CPen* pOldPen = pDC->SelectObject(&bgItemPen);
			//pDC->RoundRect(&rcItem, CPoint(nRound, nRound));
			pDC->SelectObject(pOldPen);
			bgItemPen.DeleteObject();
			// 左
			bgItemPen.CreatePen(PS_SOLID, 1, m_clrNormalCombFrameLeft);
			pOldPen = pDC->SelectObject(&bgItemPen);
			pDC->MoveTo(rcItem.left, rcItem.top);
			pDC->LineTo(rcItem.left, rcItem.bottom);
			bgItemPen.DeleteObject();
			// 上
			bgItemPen.CreatePen(PS_SOLID, 1, m_clrNormalCombFrameTop);
			pOldPen = pDC->SelectObject(&bgItemPen);
			pDC->MoveTo(rcItem.left, rcItem.top);
			pDC->LineTo(rcItem.right, rcItem.top);
			bgItemPen.DeleteObject();
			// 右
			bgItemPen.CreatePen(PS_SOLID, 1, m_clrNormalCombFrameRight);
			pOldPen = pDC->SelectObject(&bgItemPen);
			pDC->MoveTo(rcItem.right, rcItem.top);
			pDC->LineTo(rcItem.right, rcItem.bottom);
			bgItemPen.DeleteObject();
			// 下
			bgItemPen.CreatePen(PS_SOLID, 1, m_clrNormalCombFrameBottom);
			pOldPen = pDC->SelectObject(&bgItemPen);
			pDC->MoveTo(rcItem.left, rcItem.bottom);
			pDC->LineTo(rcItem.right, rcItem.bottom);
			bgItemPen.DeleteObject();
			// 设置角点的像素颜色
			// 左上
			pDC->SetPixel(CPoint(rcItem.left, rcItem.top), RGB(214, 215, 217));
			pDC->SetPixel(CPoint(rcItem.left+1, rcItem.top), RGB(187, 189, 194));
			pDC->SetPixel(CPoint(rcItem.left+1, rcItem.top+1), RGB(233, 236, 240));
			// 右上
			pDC->SetPixel(CPoint(rcItem.right, rcItem.top), RGB(214, 215, 217));
			pDC->SetPixel(CPoint(rcItem.right-1, rcItem.top), RGB(187, 189, 194));
			pDC->SetPixel(CPoint(rcItem.right-1, rcItem.top+1), RGB(233, 236, 240));
			// 左下
			pDC->SetPixel(CPoint(rcItem.left, rcItem.bottom), RGB( 235, 235, 238));
			pDC->SetPixel(CPoint(rcItem.left+1, rcItem.bottom-1), RGB(233, 236, 240));
			// 右下
			pDC->SetPixel(CPoint(rcItem.right, rcItem.bottom), RGB( 235, 235, 238));
			pDC->SetPixel(CPoint(rcItem.right-1, rcItem.bottom-1), RGB(233, 236, 240));
		}
	}

	// 下面的是画下拉按钮的边框的
	/*rcItem.DeflateRect(1, 1);

	if(!IsWindowEnabled())
	pDC->Draw3dRect(rcItem, m_clr3DHilight, m_clr3DHilight);
	else
	pDC->Draw3dRect(rcItem, m_clr3DFace, m_clr3DFace);
	*/
	/*rcItem.DeflateRect(1, 1);
	rcItem.left = rcItem.right - 18;
	pDC->Draw3dRect(rcItem, m_clr3DFace, m_clr3DFace);

	rcItem.DeflateRect(1, 1);
	pDC->Draw3dRect(rcItem, m_clr3DFace, m_clr3DFace);

	if(IsWindowEnabled())
	{
		rcItem.InflateRect(0, 1);
		switch(eState)
		{
		case NORMAL:
			{
				pDC->Draw3dRect(rcItem, m_clr3DHilight, m_clr3DHilight);
				rcItem.left -= 1;
				pDC->Draw3dRect(rcItem, m_clr3DHilight, m_clr3DHilight);
			}
			break;
		case RAISED:
			{
				pDC->Draw3dRect(rcItem, m_clr3DHilight, m_clr3DHilight);
			}
			break;
		case PRESSED:
			{
				rcItem.OffsetRect(1, 1);
				pDC->Draw3dRect(rcItem, m_clr3DShadow, m_clr3DHilight);
			}
			break;
		default:
			break;
		}
	}*/
}

BOOL CLY2ComBox::PointInRect()
{
	CPoint pt; 
	GetCursorPos(&pt); 
	CRect rcItem; 
	GetWindowRect(&rcItem); 
	return rcItem.PtInRect(pt);
}

BOOL CLY2ComBox::PointInBtn()
{
	CPoint point;
	GetCursorPos(&point);
	ScreenToClient(&point);
	CRect rcClient;
	GetClientRect(&rcClient);
	rcClient.left = rcClient.right - 18;
	return rcClient.PtInRect(point);
}

void CLY2ComBox::MeasureItem( LPMEASUREITEMSTRUCT lpMeasureItemStruct )
{
	lpMeasureItemStruct->itemWidth = 200;
	lpMeasureItemStruct->itemHeight = 30;
}

void CLY2ComBox::DrawItem( LPDRAWITEMSTRUCT lpDrawItemStruct )
{
	if(lpDrawItemStruct->CtlType!=ODT_COMBOBOX)
		return ;
	
	int nItemID = lpDrawItemStruct->itemID;
	CRect rcItem = lpDrawItemStruct->rcItem;
	UINT uItemState = lpDrawItemStruct->itemState;
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);

	DrawListBox(pDC, nItemID, uItemState, rcItem);
}

void CLY2ComBox::DeleteItem( LPDELETEITEMSTRUCT lpDeleteItemStruct )
{
	CComboBox::DeleteItem(lpDeleteItemStruct);
}

int CLY2ComBox::CompareItem( LPCOMPAREITEMSTRUCT lpCompareItemStruct )
{
	return CComboBox::CompareItem(lpCompareItemStruct);
}

void CLY2ComBox::DrawListItem(CDC* pDC, CString csText, CRect rcItem, COLORREF clrText, COLORREF clrBg, COLORREF clrFrame )
{
	CPen penFrame;
	penFrame.CreatePen(PS_SOLID, 1, clrFrame);
	CPen* pOldPen = pDC->SelectObject(&penFrame);
	CBrush brushBg;
	brushBg.CreateSolidBrush(clrBg);
	CBrush* pOldBrush = pDC->SelectObject(&brushBg);
	rcItem.InflateRect(0, 1, 0, 1);
	pDC->RoundRect(&rcItem, CPoint(0, 0));
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
	penFrame.DeleteObject();
	brushBg.DeleteObject();

	rcItem.InflateRect(0, -1, 0, -1);
	pDC->SetTextColor(clrText);
	CFont* pOldFont = pDC->SelectObject(m_pListFont);
	rcItem.left += 3;
	pDC->DrawText(csText, &rcItem, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

}

void CLY2ComBox::DrawListBox(CDC* pDC, int nItemID, UINT uState, CRect rcItem)
{
	CString csShowText;
	GetLBText(nItemID, csShowText);

	pDC->SetBkMode(TRANSPARENT);

	if(uState&ODS_SELECTED)
		Invalidate();

	if(nItemID == /*m_nCurrFocusListItem*/GetCurSel())
	{
		DrawListItem(pDC, csShowText, rcItem, m_clrListHilightItemText, m_clrListHilightItemBg, m_clrListItemPartLine);
		//SetWindowText(csShowText);
	}
	else if(nItemID%2)
	{
		DrawListItem(pDC, csShowText, rcItem, m_clrListText, m_clrListEvenItem, m_clrListItemPartLine);
	}
	else
	{
		DrawListItem(pDC, csShowText, rcItem, m_clrListText, m_clrListOddItem, m_clrListItemPartLine);
	}

	// 列表框边框
	CBrush brushListFrame;
	brushListFrame.CreateSolidBrush(m_clrListFrame);
	CRect rcListClient;
	m_pListBox->GetClientRect(&rcListClient);
	//pDC->FrameRect(rcListClient, &brushListFrame); //画边框后，在上下滚的时候会出现一条条线，暂时注释了

	if(!m_bReadOnly && (m_nCurrFocusListItem==nItemID ) &&
		m_bListItemFocus && m_bAllowDel )
	{
		// 绘制右边图标
		CRect rcDelIcon(rcItem);
		rcDelIcon.left = rcDelIcon.right - 18;
// 		rcDelIcon.top += (rcDelIcon.Height()-2)/2;
		rcDelIcon.top +=2;
		DrawIconEx(pDC->m_hDC, rcDelIcon.left, rcDelIcon.top, AfxGetApp()->LoadIcon(IDI_ICON1), 12, 12, NULL, NULL, DI_NORMAL);
	}

}

void CLY2ComBox::SetListFrameColor( COLORREF clrListFrame = RGB(51, 153, 255) )
{
	m_clrListFrame = clrListFrame;
}

void CLY2ComBox::SetListHilightItemBgColor( COLORREF clrListHilightItemBg = RGB(51, 153, 255) )
{
	m_clrListHilightItemBg = clrListHilightItemBg;
}

void CLY2ComBox::SetListItemBgColor( COLORREF clrListItemBg = RGB(51, 153, 255) )
{
	m_clrListItemBg = clrListItemBg;
}

void CLY2ComBox::SetAllowDeleteList( BOOL bAllowDelistItem/*=FALSE*/ )
{
	m_bAllowDel = bAllowDelistItem;
}

void CLY2ComBox::SetListEvenItemColor( COLORREF clrListEvenItem )
{
	m_clrListEvenItem = clrListEvenItem;
}

void CLY2ComBox::SetListOddItemColor( COLORREF clrListOddItem )
{
	m_clrListOddItem = clrListOddItem;
}

void CLY2ComBox::SetListPartLineColor( COLORREF clrListPartLine )
{
	m_clrListItemPartLine = clrListPartLine;
}

void CLY2ComBox::setListHilightItemTextColor( COLORREF clrListHilightItemText )
{
	m_clrListHilightItemText = clrListHilightItemText;
}


void CLY2ComBox::OnCbnSelchange()
{
	// TODO: 在此添加控件通知处理程序代码
	// 只读时，不能删除
	if(!m_bReadOnly)
	{
		int nIndex = GetCurSel();//m_combol为控件变量
		if (nIndex<0)return;

		SetCurSel(nIndex);
		//下面根据nIndex进行不同的事件处理
// 		CRect rcItem;
// 		m_pListBox->GetItemRect(nIndex, rcItem);
		CPoint point;
		GetCursorPos(&point);
		this->ScreenToClient(&point); // 转换不要忘记
//		m_pListBox->ScreenToClient(&point);
		// 上面一句可以用  pListBox->ScreenToClient(&point); 直接映射到列表控件中去，
		// 这样就不需要进行下面的鼠标坐标的转换，这里采用下面的一种方法，作为学习用
		::CWnd *pWnd = this->GetWindow(GW_CHILD);
		while(pWnd)
		{
			TCHAR classname[256];
			::GetClassName(pWnd->m_hWnd, classname, 256);
			if(lstrcmpi(classname, _T("Edit")) == 0)
				break;
			if(pWnd)
				pWnd = pWnd->GetNextWindow();
		}
		CEdit *pEdit = (CEdit*)pWnd;

		CRect rcEdit;
		pEdit->GetClientRect(&rcEdit);
		// 鼠标的坐标包含了组合框中的编辑框高度，所以实际计算时需减去它，18是设置的删除图标的宽度
		point.y -= rcEdit.Height();
// 		rcItem.left = rcItem.right - 18;
		CWnd *pOwner = this->GetParent();
		if(pOwner==NULL)return;
		if(rcEdit.right-8<point.x&&rcEdit.right+18>point.x)
		{
// 			CString csTemp;
// 			GetLBText(nIndex, csTemp);
// 			m_pListBox->DeleteString(nIndex);
// 			// 因为本例中只要鼠标在列表中移动，组合框就可以显示相应的项值，
// 			// 所以删除一项后将组合框的显示值设为空，当然也可以设置为其他项的值
// 			this->SetWindowText(_T(""));
			pOwner->SendMessage(WM_COMMAND,COMBOX_DELITEM,0);
			
		}
		else
		{
         CString sText;
         GetWindowText(sText);
         m_strLastEditText = sText;
         m_nCaretStart = 0;
         m_nCaretEnd = -1;
			pOwner->SendMessage(WM_COMMAND,COMBOX_SELCHANGE,0);
			return;
		}
	}

	Invalidate();
}

int CLY2ComBox::DeleteString(UINT nIndex)
{
   CString str;
   GetLBText(nIndex,str);
   for (auto Iter = m_vecItem.begin(); Iter != m_vecItem.end(); ++Iter)
   {
      if (Iter->m_sOrg == str)
      {
         m_vecItem.erase(Iter);
         break;
      }
   }
   return CComboBox::DeleteString(nIndex);
}

void CLY2ComBox::OnCbnCommandEditComposing()
{
  // OnCbnEditchange();

   vector<TCHAR> vecTChar(512);
   ::GetWindowText(GetSafeHwnd(), vecTChar.data(), vecTChar.size());
   DWORD dwPos = GetEditSel();
   int nStart = LOWORD(dwPos);
   int nEnd = HIWORD(dwPos);

   //if (!strTest.IsEmpty() && nEnd == strTest.GetLength())
   CString strImmString;
   {
      auto hIMC = ImmGetContext(GetSafeHwnd());
      vector<char> vecbyBuf(1, 0);
      LONG BufSize = ImmGetCompositionString(hIMC, GCS_COMPSTR, vecbyBuf.data(), 0);

      if (BufSize > 0)
      {
         vecbyBuf.assign(BufSize + 1, 0);
         LONG lRet = ImmGetCompositionString(hIMC, GCS_COMPSTR, vecbyBuf.data(), BufSize);
         if (IMM_ERROR_NODATA == lRet)
         {
            return;
         }

         if (IMM_ERROR_GENERAL == lRet)
         {
            return;
         }
      }

      CStringA str = vecbyBuf.data();

      int nLen = str.GetLength();
      for(int i = 0; i < nLen; i++)
      {
         if (str[i] != _T('\''))
         {
            strImmString.AppendChar(str[i]);
         }
      }

      TRACE(_T("m_strImmString：%s\n"), strImmString);

      ImmReleaseContext(GetSafeHwnd(), hIMC);
   }

   strImmString.MakeLower();

   TRACE(_T("nStart %d nEnd %d Composing %s\n"), nStart, nEnd, strImmString);

   CString strTest;
   GetWindowText(strTest);
  
   CStringA strTextA(strTest);
   if (nStart == nEnd && nStart == strTextA.GetLength())
   {
      BOOL bDroppedState = GetDroppedState();
      if (!bDroppedState)
      {
         while(GetCount() > 0)
         {
            CComboBox::DeleteString(0);
         }

         auto it = m_vecItem.begin();
         for (; it != m_vecItem.end(); ++it)
         {
            AddString(it->m_sOrg);
         }

         ShowDropDown();
      }

      CString strOrgTest = strTest;
      strTest += strImmString;

      std::vector<CString> vecFileredString;

      if (!strTest.IsEmpty())
      {
         auto it = m_vecItem.begin();
         for (; it != m_vecItem.end(); ++it)
         {
            if (0 == it->m_sOrg.Find(strTest)) //最开头包含子串
            {
               vecFileredString.push_back(it->m_sOrg);
            }
            else if (0 == it->m_sPinYin.Find(strTest))
            {
               vecFileredString.push_back(it->m_sOrg);
            }
            else if (0 == it->m_sShortHand.Find(strTest))
            {
               vecFileredString.push_back(it->m_sOrg);
            }
            else if (!strImmString.IsEmpty() && !strOrgTest.IsEmpty() && 0 == it->m_sOrg.Find(strOrgTest))
            {
               CStringW strW = strOrgTest;
               CString sOldBefore = ConvertChineseUnicodeToPyt(strW);
               CString sOldBeforeShort = ConvertChineseToShorthand(strW);

               int nOldBeforeLen = sOldBefore.GetLength();
               int nOldBeforeShortLen = sOldBeforeShort.GetLength();

               if (it->m_sPinYin.Mid(nOldBeforeLen, it->m_sPinYin.GetLength() - nOldBeforeLen).Find(strImmString) == 0)
               {
                  vecFileredString.push_back(it->m_sOrg);
               }
               else if (it->m_sShortHand.Mid(nOldBeforeShortLen, it->m_sShortHand.GetLength() - nOldBeforeShortLen).Find(strImmString) == 0)
               {
                  vecFileredString.push_back(it->m_sOrg);
               }
            }
         }
      }
      else
      {
         auto it = m_vecItem.begin();
         for (; it != m_vecItem.end(); ++it)
         {
            vecFileredString.push_back(it->m_sOrg);
         }
      }
      SetRedraw(FALSE);
      
      while(GetCount() > 0)
      {
         CComboBox::DeleteString(0);
      }

      for (auto Iter = vecFileredString.begin(); Iter != vecFileredString.end(); ++Iter)
      {
         AddString(*Iter);
      }

      if (vecFileredString.empty())
      {
         AddString(_T(" "));
      }
      
      SetRedraw(TRUE);

      if (!bDroppedState)
      {
         SetWindowText(strOrgTest);
         SendMessage(WM_KEYDOWN, VK_END, 0);//文本框得到光标  
         SetEditSel(nStart,nStart);
      }
   }
}

BOOL CLY2ComBox::OnCbnEditchange()
{
   CString strTest;
   GetWindowText(strTest);
   m_strLastEditText = strTest;
   DWORD dwPos = GetEditSel();
   int nStart = LOWORD(dwPos);
   int nEnd = HIWORD(dwPos);
   m_nCaretStart = nStart;
   m_nCaretEnd = nEnd;
   CString strOrgTest = strTest;

   CString strImmString;
   {
      auto hIMC = ImmGetContext(GetSafeHwnd());
      BYTE byBuf[256] = {0};
      LONG BufSize = ImmGetCompositionString(hIMC, GCS_COMPSTR, byBuf, 0);

      CString str;

      if (BufSize > 0)
      {
         if (ImmGetCompositionString(hIMC, GCS_COMPSTR, byBuf, BufSize))
         {
            for (int nIndex = 0; nIndex < BufSize; ++nIndex)
            {
               if (byBuf[nIndex] != '\'')
               {
                  str.AppendChar(byBuf[nIndex]);
               }
            }
         }
      }
//       WPARAM wParam;
//       wParam = ImmGetVirtualKey(GetSafeHwnd());
//       if (::isalpha(wParam))
//       {
//          str.AppendChar((TCHAR)wParam);
//       }

      str.MakeLower();

      strImmString = str;
      TRACE(_T("m_strImmString：%s\n"), str);

      ImmReleaseContext(GetSafeHwnd(), hIMC);
   }

   ASSERT(strImmString.IsEmpty());

   strImmString.MakeLower();
   strTest.Append(strImmString);
   TRACE(_T("strTest:%s\n"), strTest);
   strTest.MakeLower();

   // TODO: Add your control notification handler code here 
   //if (m_flagVKBack)
   {
      m_flagVKBack = FALSE;

      BOOL bDroppedState = GetDroppedState();
      if (!bDroppedState)
      {
         //while(GetCount() > 0)
         //{
         //   CComboBox::DeleteString(0);
         //}

         //auto it = m_vecItem.begin();
         //for (; it != m_vecItem.end(); ++it)
         //{
         //   AddString(it->m_sOrg);
         //}

         ShowDropDown();
      }

      std::vector<CString> vecFileredString;

      if (!strTest.IsEmpty())
      {
         auto it = m_vecItem.begin();
         for (; it != m_vecItem.end(); ++it)
         {
            //最开头包含子串
            if (0 == it->m_sOrg.Find(strTest))
            {
               vecFileredString.push_back(it->m_sOrg);
            }
            else if (0 == it->m_sPinYin.Find(strTest))
            {
               vecFileredString.push_back(it->m_sOrg);
            }
            else if (0 == it->m_sShortHand.Find(strTest))
            {
               vecFileredString.push_back(it->m_sOrg);
            }
            else if (!strImmString.IsEmpty() && !strOrgTest.IsEmpty() && 0 == it->m_sOrg.Find(strOrgTest))
            {
               CStringW strW = strOrgTest;
               CString sOldBefore = ConvertChineseUnicodeToPyt(strW);
               CString sOldBeforeShort = ConvertChineseToShorthand(strW);

               int nOldBeforeLen = sOldBefore.GetLength();
               int nOldBeforeShortLen = sOldBeforeShort.GetLength();

               if (it->m_sPinYin.Mid(nOldBeforeLen, it->m_sPinYin.GetLength() - nOldBeforeLen).Find(strImmString) == 0)
               {
                  vecFileredString.push_back(it->m_sOrg);
               }
               else if (it->m_sShortHand.Mid(nOldBeforeShortLen, it->m_sShortHand.GetLength() - nOldBeforeShortLen).Find(strImmString) == 0)
               {
                  vecFileredString.push_back(it->m_sOrg);
               }
            }
         }
      }
      else
      {
         auto it = m_vecItem.begin();
         for (; it != m_vecItem.end(); ++it)
         {
            vecFileredString.push_back(it->m_sOrg);
         }
      }
      SetRedraw(FALSE);

      while(GetCount() > 0)
      {
         CComboBox::DeleteString(0);
      }

      for (auto Iter = vecFileredString.begin(); Iter != vecFileredString.end(); ++Iter)
      {
         AddString(*Iter);
      }

      if (vecFileredString.empty())
      {
         AddString(_T(" "));
      }
      SetRedraw(TRUE);
      SetCursor(LoadCursor(NULL,MAKEINTRESOURCE(IDC_ARROW)));//很重要，鼠标重得光标

//       m_bDropdownShowAll = FALSE;
//       ShowDropDown(FALSE);
//       ShowDropDown();
//       m_bDropdownShowAll = TRUE;
// 
//       SetWindowText(strOrgTest);
//       SendMessage(WM_KEYDOWN, VK_END, 0);//文本框得到光标  
// 
//       {
//          SetEditSel(nStart,nStart);
//       }

      if (!bDroppedState)
      {
         SetWindowText(strOrgTest);
         SendMessage(WM_KEYDOWN, VK_END, 0);//文本框得到光标  
         SetEditSel(nStart,nStart);
      }

	  //2018/07/09 wangqy
	  CWnd *pOwner = this->GetParent();
	  if(pOwner!=NULL)
		  pOwner->SendMessage(WM_COMMAND,COMBOX_EDITCHANGE,0);
	  //2018/07/09_end
     //return FALSE;
   }

  // {
  //    BOOL bEqual = FALSE;
  //    BOOL findFlag = FALSE;

  //    {         
  //       std::vector<CString> vecFileredString;

  //       if (!strTest.IsEmpty())
  //       {
  //          auto it = m_vecItem.begin();
  //          for (; it != m_vecItem.end(); ++it)
  //          {
  //             if (0 == it->m_sOrg.Find(strTest)) //最开头包含子串
  //             {
  //                vecFileredString.push_back(it->m_sOrg);
  //             }
  //             else if (0 == it->m_sPinYin.Find(strTest))
  //             {
  //                vecFileredString.push_back(it->m_sOrg);
  //             }
  //             else if (0 == it->m_sShortHand.Find(strTest))
  //             {
  //                vecFileredString.push_back(it->m_sOrg);
  //             }
  //             else if (!strImmString.IsEmpty() && !strOrgTest.IsEmpty() && 0 == it->m_sOrg.Find(strOrgTest))
  //             {
  //                CStringW strW = strOrgTest;
  //                CString sOldBefore = ConvertChineseUnicodeToPyt(strW);
  //                CString sOldBeforeShort = ConvertChineseToShorthand(strW);

  //                int nOldBeforeLen = sOldBefore.GetLength();
  //                int nOldBeforeShortLen = sOldBeforeShort.GetLength();

  //                if (it->m_sPinYin.Mid(nOldBeforeLen, it->m_sPinYin.GetLength() - nOldBeforeLen).Find(strImmString) == 0)
  //                {
  //                   vecFileredString.push_back(it->m_sOrg);
  //                }
  //                else if (it->m_sShortHand.Mid(nOldBeforeShortLen, it->m_sShortHand.GetLength() - nOldBeforeShortLen).Find(strImmString) == 0)
  //                {
  //                   vecFileredString.push_back(it->m_sOrg);
  //                }
  //             }
  //          }
  //       }
  //       else
  //       {
  //          auto it = m_vecItem.begin();
  //          for (; it != m_vecItem.end(); ++it)
  //          {
  //             vecFileredString.push_back(it->m_sOrg);
  //          }
  //       }
  //       SetRedraw(FALSE);

  //       while(GetCount() > 0)
  //       {
  //          CComboBox::DeleteString(0);
  //       }

  //       for (auto Iter = vecFileredString.begin(); Iter != vecFileredString.end(); ++Iter)
  //       {
  //          AddString(*Iter);
  //       }

  //       if (vecFileredString.empty())
  //       {
  //          AddString(_T(" "));
  //       }
  //       SetRedraw(TRUE);
  //    }

  //    if (!GetDroppedState())
  //    {
  //       m_bDropdownShowAll = FALSE;
  //       ShowDropDown();
  //       m_bDropdownShowAll = TRUE;

  //       SetWindowText(strOrgTest);
  //       SendMessage(WM_KEYDOWN, VK_END, 0);//文本框得到光标  
  //       SetEditSel(nStart,nStart);
  //    }
  // }
  // 
  //  CWnd *pOwner = this->GetParent();
  //  if(pOwner!=NULL)
		//pOwner->SendMessage(WM_COMMAND,COMBOX_EDITCHANGE,0);//2017/11/17 wangqy

    return TRUE;
}

int CLY2ComBox::AddStringNew(LPCTSTR lpszString)
{
   CString tmp = lpszString;
   //tmp.MakeUpper(); //如果大小写不区分的话，需要打开这个
   ComboItem item;
   item.m_sOrg = tmp;
   CStringW sOrgWide(tmp);
   item.m_sPinYin = ConvertChineseUnicodeToPyt(sOrgWide);
   item.m_sShortHand = ConvertChineseToShorthand(sOrgWide);
   m_vecItem.push_back(item);
   return CComboBox::AddString(tmp);
}

int CLY2ComBox::InsertStringNew(int nIndex, LPCTSTR lpszString)
{
   CString tmp = lpszString;
   //tmp.MakeUpper();//如果大小写不区分的话，需要打开这个
   ComboItem item;
   item.m_sOrg = tmp;
   CStringW sOrgWide(tmp);
   item.m_sPinYin = ConvertChineseUnicodeToPyt(sOrgWide);
   item.m_sShortHand = ConvertChineseToShorthand(sOrgWide);
   m_vecItem.push_back(item);
   return CComboBox::InsertString(nIndex,tmp);
}
void CLY2ComBox::ResetContentNew()
{
   m_vecItem.clear();
   return CComboBox::ResetContent();;
}

void CLY2ComBox::SetStrings(const std::set<CString> &setData)
{
//    m_vecString.assign(setData.begin(), setData.end());
//    ResetContent();
//    for (auto iter = m_vecString.begin(); iter != m_vecString.end(); ++iter)
//    {
//       CString tmp = *iter;
//       //tmp.MakeUpper();//如果大小写不区分的话，需要打开这个
//       AddString(tmp);
//    }
}

BOOL CLY2ComBox::PreTranslateMessage(MSG* pMsg)
{ 
   if (pMsg->message == WM_KEYDOWN)
   {
      if (pMsg->wParam == VK_DELETE)
      {
         DWORD dwPos = GetEditSel();
         int nStart = LOWORD(dwPos);
         int nEnd = HIWORD(dwPos);
         int size = nEnd-nStart;
         CString strValue;
         if (size>0)
         { 
            GetWindowText(strValue);            
            strValue.Delete(nStart,size);  
            SetWindowText(strValue);
            SetEditSel(nStart,nStart);            
         }  
         return TRUE;
      }
      //else if (pMsg->wParam == VK_BACK)
      //{
      //   CString strValue;
      //   GetWindowText(strValue);
      //   if (!strValue.IsEmpty())
      //   {
      //      m_flagVKBack = TRUE;
      //   }
      //}
      else if (pMsg->wParam == VK_RETURN)
      {
         if (GetDroppedState())
         {
            if (GetCurSel() < 0)
            {
               DWORD dwPos = GetEditSel();
               int nStart = LOWORD(dwPos);
               int nEnd = HIWORD(dwPos);
               CString sText;
               GetWindowText(sText);
               ShowDropDown(FALSE);
               SetWindowText(sText);
               SetEditSel(nStart, nEnd);
               return TRUE;
            }
         }
      }
   } 
   BOOL bRet = CComboBox::PreTranslateMessage(pMsg);
   return bRet;
}

static CString ConvertChineseToShorthand(const wchar_t* chrstr)
{
   const  int pyvalue[] = {-20319,-20317,-20304,-20295,-20292,-20283,-20265,-20257,-20242,-20230,-20051,-20036,-20032,-20026,
      -20002,-19990,-19986,-19982,-19976,-19805,-19784,-19775,-19774,-19763,-19756,-19751,-19746,-19741,-19739,-19728,
      -19725,-19715,-19540,-19531,-19525,-19515,-19500,-19484,-19479,-19467,-19289,-19288,-19281,-19275,-19270,-19263,
      -19261,-19249,-19243,-19242,-19238,-19235,-19227,-19224,-19218,-19212,-19038,-19023,-19018,-19006,-19003,-18996,
      -18977,-18961,-18952,-18783,-18774,-18773,-18763,-18756,-18741,-18735,-18731,-18722,-18710,-18697,-18696,-18526,
      -18518,-18501,-18490,-18478,-18463,-18448,-18447,-18446,-18239,-18237,-18231,-18220,-18211,-18201,-18184,-18183,
      -18181,-18012,-17997,-17988,-17970,-17964,-17961,-17950,-17947,-17931,-17928,-17922,-17759,-17752,-17733,-17730,
      -17721,-17703,-17701,-17697,-17692,-17683,-17676,-17496,-17487,-17482,-17468,-17454,-17433,-17427,-17417,-17202,
      -17185,-16983,-16970,-16942,-16915,-16733,-16708,-16706,-16689,-16664,-16657,-16647,-16474,-16470,-16465,-16459,
      -16452,-16448,-16433,-16429,-16427,-16423,-16419,-16412,-16407,-16403,-16401,-16393,-16220,-16216,-16212,-16205,
      -16202,-16187,-16180,-16171,-16169,-16158,-16155,-15959,-15958,-15944,-15933,-15920,-15915,-15903,-15889,-15878,
      -15707,-15701,-15681,-15667,-15661,-15659,-15652,-15640,-15631,-15625,-15454,-15448,-15436,-15435,-15419,-15416,
      -15408,-15394,-15385,-15377,-15375,-15369,-15363,-15362,-15183,-15180,-15165,-15158,-15153,-15150,-15149,-15144,
      -15143,-15141,-15140,-15139,-15128,-15121,-15119,-15117,-15110,-15109,-14941,-14937,-14933,-14930,-14929,-14928,
      -14926,-14922,-14921,-14914,-14908,-14902,-14894,-14889,-14882,-14873,-14871,-14857,-14678,-14674,-14670,-14668,
      -14663,-14654,-14645,-14630,-14594,-14429,-14407,-14399,-14384,-14379,-14368,-14355,-14353,-14345,-14170,-14159,
      -14151,-14149,-14145,-14140,-14137,-14135,-14125,-14123,-14122,-14112,-14109,-14099,-14097,-14094,-14092,-14090,
      -14087,-14083,-13917,-13914,-13910,-13907,-13906,-13905,-13896,-13894,-13878,-13870,-13859,-13847,-13831,-13658,
      -13611,-13601,-13406,-13404,-13400,-13398,-13395,-13391,-13387,-13383,-13367,-13359,-13356,-13343,-13340,-13329,
      -13326,-13318,-13147,-13138,-13120,-13107,-13096,-13095,-13091,-13076,-13068,-13063,-13060,-12888,-12875,-12871,
      -12860,-12858,-12852,-12849,-12838,-12831,-12829,-12812,-12802,-12607,-12597,-12594,-12585,-12556,-12359,-12346,
      -12320,-12300,-12120,-12099,-12089,-12074,-12067,-12058,-12039,-11867,-11861,-11847,-11831,-11798,-11781,-11604,
      -11589,-11536,-11358,-11340,-11339,-11324,-11303,-11097,-11077,-11067,-11055,-11052,-11045,-11041,-11038,-11024,
      -11020,-11019,-11018,-11014,-10838,-10832,-10815,-10800,-10790,-10780,-10764,-10587,-10544,-10533,-10519,-10331,
      -10329,-10328,-10322,-10315,-10309,-10307,-10296,-10281,-10274,-10270,-10262,-10260,-10256,-10254};
   const char pystr[396][7] = {"a","ai","an","ang","ao","ba","bai","ban","bang","bao","bei","ben","beng","bi","bian","biao",
      "bie","bin","bing","bo","bu","ca","cai","can","cang","cao","ce","ceng","cha","chai","chan","chang","chao","che","chen",
      "cheng","chi","chong","chou","chu","chuai","chuan","chuang","chui","chun","chuo","ci","cong","cou","cu","cuan","cui",
      "cun","cuo","da","dai","dan","dang","dao","de","deng","di","dian","diao","die","ding","diu","dong","dou","du","duan",
      "dui","dun","duo","e","en","er","fa","fan","fang","fei","fen","feng","fo","fou","fu","ga","gai","gan","gang","gao",
      "ge","gei","gen","geng","gong","gou","gu","gua","guai","guan","guang","gui","gun","guo","ha","hai","han","hang",
      "hao","he","hei","hen","heng","hong","hou","hu","hua","huai","huan","huang","hui","hun","huo","ji","jia","jian",
      "jiang","jiao","jie","jin","jing","jiong","jiu","ju","juan","jue","jun","ka","kai","kan","kang","kao","ke","ken",
      "keng","kong","kou","ku","kua","kuai","kuan","kuang","kui","kun","kuo","la","lai","lan","lang","lao","le","lei",
      "leng","li","lia","lian","liang","liao","lie","lin","ling","liu","long","lou","lu","lv","luan","lue","lun","luo",
      "ma","mai","man","mang","mao","me","mei","men","meng","mi","mian","miao","mie","min","ming","miu","mo","mou","mu",
      "na","nai","nan","nang","nao","ne","nei","nen","neng","ni","nian","niang","niao","nie","nin","ning","niu","nong",
      "nu","nv","nuan","nue","nuo","o","ou","pa","pai","pan","pang","pao","pei","pen","peng","pi","pian","piao","pie",
      "pin","ping","po","pu","qi","qia","qian","qiang","qiao","qie","qin","qing","qiong","qiu","qu","quan","que","qun",
      "ran","rang","rao","re","ren","reng","ri","rong","rou","ru","ruan","rui","run","ruo","sa","sai","san","sang",
      "sao","se","sen","seng","sha","shai","shan","shang","shao","she","shen","sheng","shi","shou","shu","shua",
      "shuai","shuan","shuang","shui","shun","shuo","si","song","sou","su","suan","sui","sun","suo","ta","tai",
      "tan","tang","tao","te","teng","ti","tian","tiao","tie","ting","tong","tou","tu","tuan","tui","tun","tuo",
      "wa","wai","wan","wang","wei","wen","weng","wo","wu","xi","xia","xian","xiang","xiao","xie","xin","xing",
      "xiong","xiu","xu","xuan","xue","xun","ya","yan","yang","yao","ye","yi","yin","ying","yo","yong","you",
      "yu","yuan","yue","yun","za","zai","zan","zang","zao","ze","zei","zen","zeng","zha","zhai","zhan","zhang",
      "zhao","zhe","zhen","zheng","zhi","zhong","zhou","zhu","zhua","zhuai","zhuan","zhuang","zhui","zhun","zhuo",
      "zi","zong","zou","zu","zuan","zui","zun","zuo"};

   int chrasc = 0;         

   char* pcReturnString = NULL;

   //unicode转换为ANSI
   int length = WideCharToMultiByte(CP_ACP, 0, chrstr, -1, 0, 0, 0, 0 ); 
   char* nowchar = new char[length+1];
   memset(nowchar,0,length+1);
   WideCharToMultiByte( CP_ACP, 0, chrstr, -1, nowchar,length, 0, 0 );

   //转换ANSI,字符部分不变，汉字转换成相应的拼音
   char *returnstr = new char[6*length +1];
   memset(returnstr,0,6*length +1);

   int offset = 0; 
   for (int j = 0; j < length;) // 循环处理字节数组
   {
      if (nowchar[j] >= 0 && nowchar[j] < 128) // 非汉字处理
      {
         returnstr[offset] = nowchar[j];
         offset++;
         j++;
         continue;
      }

      // 汉字处理
      chrasc = nowchar[j] * 256 + nowchar[j+1]+256;

      if (chrasc > 0 && chrasc < 160)
      {
         returnstr[offset]= nowchar[j];
         offset++;
         j++;
      }
      else
      {
         for (int i = (sizeof(pyvalue)/sizeof(pyvalue[0]) - 1); i >= 0; i--)
         {
            if (pyvalue[i] <= chrasc)
            {
               returnstr[offset]= pystr[i][0];
               offset++;  
               break;
            }
         }
         j +=2;
      }
   }
   if(strlen(returnstr)>0)
   {
      pcReturnString = new char[strlen(returnstr)+1];
      memset(pcReturnString,0,strlen(returnstr)+1);
      strcpy(pcReturnString,returnstr);
   }
   delete []returnstr;
   delete []nowchar;

   CString strShorthand(pcReturnString);
   delete []pcReturnString;

   return strShorthand;
}

static CString ConvertChineseUnicodeToPyt(const wchar_t* chrstr)
{
   const  int pyvalue[] = {-20319,-20317,-20304,-20295,-20292,-20283,-20265,-20257,-20242,-20230,-20051,-20036,-20032,-20026,
      -20002,-19990,-19986,-19982,-19976,-19805,-19784,-19775,-19774,-19763,-19756,-19751,-19746,-19741,-19739,-19728,
      -19725,-19715,-19540,-19531,-19525,-19515,-19500,-19484,-19479,-19467,-19289,-19288,-19281,-19275,-19270,-19263,
      -19261,-19249,-19243,-19242,-19238,-19235,-19227,-19224,-19218,-19212,-19038,-19023,-19018,-19006,-19003,-18996,
      -18977,-18961,-18952,-18783,-18774,-18773,-18763,-18756,-18741,-18735,-18731,-18722,-18710,-18697,-18696,-18526,
      -18518,-18501,-18490,-18478,-18463,-18448,-18447,-18446,-18239,-18237,-18231,-18220,-18211,-18201,-18184,-18183,
      -18181,-18012,-17997,-17988,-17970,-17964,-17961,-17950,-17947,-17931,-17928,-17922,-17759,-17752,-17733,-17730,
      -17721,-17703,-17701,-17697,-17692,-17683,-17676,-17496,-17487,-17482,-17468,-17454,-17433,-17427,-17417,-17202,
      -17185,-16983,-16970,-16942,-16915,-16733,-16708,-16706,-16689,-16664,-16657,-16647,-16474,-16470,-16465,-16459,
      -16452,-16448,-16433,-16429,-16427,-16423,-16419,-16412,-16407,-16403,-16401,-16393,-16220,-16216,-16212,-16205,
      -16202,-16187,-16180,-16171,-16169,-16158,-16155,-15959,-15958,-15944,-15933,-15920,-15915,-15903,-15889,-15878,
      -15707,-15701,-15681,-15667,-15661,-15659,-15652,-15640,-15631,-15625,-15454,-15448,-15436,-15435,-15419,-15416,
      -15408,-15394,-15385,-15377,-15375,-15369,-15363,-15362,-15183,-15180,-15165,-15158,-15153,-15150,-15149,-15144,
      -15143,-15141,-15140,-15139,-15128,-15121,-15119,-15117,-15110,-15109,-14941,-14937,-14933,-14930,-14929,-14928,
      -14926,-14922,-14921,-14914,-14908,-14902,-14894,-14889,-14882,-14873,-14871,-14857,-14678,-14674,-14670,-14668,
      -14663,-14654,-14645,-14630,-14594,-14429,-14407,-14399,-14384,-14379,-14368,-14355,-14353,-14345,-14170,-14159,
      -14151,-14149,-14145,-14140,-14137,-14135,-14125,-14123,-14122,-14112,-14109,-14099,-14097,-14094,-14092,-14090,
      -14087,-14083,-13917,-13914,-13910,-13907,-13906,-13905,-13896,-13894,-13878,-13870,-13859,-13847,-13831,-13658,
      -13611,-13601,-13406,-13404,-13400,-13398,-13395,-13391,-13387,-13383,-13367,-13359,-13356,-13343,-13340,-13329,
      -13326,-13318,-13147,-13138,-13120,-13107,-13096,-13095,-13091,-13076,-13068,-13063,-13060,-12888,-12875,-12871,
      -12860,-12858,-12852,-12849,-12838,-12831,-12829,-12812,-12802,-12607,-12597,-12594,-12585,-12556,-12359,-12346,
      -12320,-12300,-12120,-12099,-12089,-12074,-12067,-12058,-12039,-11867,-11861,-11847,-11831,-11798,-11781,-11604,
      -11589,-11536,-11358,-11340,-11339,-11324,-11303,-11097,-11077,-11067,-11055,-11052,-11045,-11041,-11038,-11024,
      -11020,-11019,-11018,-11014,-10838,-10832,-10815,-10800,-10790,-10780,-10764,-10587,-10544,-10533,-10519,-10331,
      -10329,-10328,-10322,-10315,-10309,-10307,-10296,-10281,-10274,-10270,-10262,-10260,-10256,-10254};
   const char pystr[396][7] = {"a","ai","an","ang","ao","ba","bai","ban","bang","bao","bei","ben","beng","bi","bian","biao",
      "bie","bin","bing","bo","bu","ca","cai","can","cang","cao","ce","ceng","cha","chai","chan","chang","chao","che","chen",
      "cheng","chi","chong","chou","chu","chuai","chuan","chuang","chui","chun","chuo","ci","cong","cou","cu","cuan","cui",
      "cun","cuo","da","dai","dan","dang","dao","de","deng","di","dian","diao","die","ding","diu","dong","dou","du","duan",
      "dui","dun","duo","e","en","er","fa","fan","fang","fei","fen","feng","fo","fou","fu","ga","gai","gan","gang","gao",
      "ge","gei","gen","geng","gong","gou","gu","gua","guai","guan","guang","gui","gun","guo","ha","hai","han","hang",
      "hao","he","hei","hen","heng","hong","hou","hu","hua","huai","huan","huang","hui","hun","huo","ji","jia","jian",
      "jiang","jiao","jie","jin","jing","jiong","jiu","ju","juan","jue","jun","ka","kai","kan","kang","kao","ke","ken",
      "keng","kong","kou","ku","kua","kuai","kuan","kuang","kui","kun","kuo","la","lai","lan","lang","lao","le","lei",
      "leng","li","lia","lian","liang","liao","lie","lin","ling","liu","long","lou","lu","lv","luan","lue","lun","luo",
      "ma","mai","man","mang","mao","me","mei","men","meng","mi","mian","miao","mie","min","ming","miu","mo","mou","mu",
      "na","nai","nan","nang","nao","ne","nei","nen","neng","ni","nian","niang","niao","nie","nin","ning","niu","nong",
      "nu","nv","nuan","nue","nuo","o","ou","pa","pai","pan","pang","pao","pei","pen","peng","pi","pian","piao","pie",
      "pin","ping","po","pu","qi","qia","qian","qiang","qiao","qie","qin","qing","qiong","qiu","qu","quan","que","qun",
      "ran","rang","rao","re","ren","reng","ri","rong","rou","ru","ruan","rui","run","ruo","sa","sai","san","sang",
      "sao","se","sen","seng","sha","shai","shan","shang","shao","she","shen","sheng","shi","shou","shu","shua",
      "shuai","shuan","shuang","shui","shun","shuo","si","song","sou","su","suan","sui","sun","suo","ta","tai",
      "tan","tang","tao","te","teng","ti","tian","tiao","tie","ting","tong","tou","tu","tuan","tui","tun","tuo",
      "wa","wai","wan","wang","wei","wen","weng","wo","wu","xi","xia","xian","xiang","xiao","xie","xin","xing",
      "xiong","xiu","xu","xuan","xue","xun","ya","yan","yang","yao","ye","yi","yin","ying","yo","yong","you",
      "yu","yuan","yue","yun","za","zai","zan","zang","zao","ze","zei","zen","zeng","zha","zhai","zhan","zhang",
      "zhao","zhe","zhen","zheng","zhi","zhong","zhou","zhu","zhua","zhuai","zhuan","zhuang","zhui","zhun","zhuo",
      "zi","zong","zou","zu","zuan","zui","zun","zuo"};

   int chrasc = 0;         

   char* pcReturnString = NULL;

   //unicode转换为ANSI
   int length = WideCharToMultiByte(CP_ACP, 0, chrstr, -1, 0, 0, 0, 0 ); 
   char* nowchar = new char[length+1];
   memset(nowchar,0,length+1);
   WideCharToMultiByte( CP_ACP, 0, chrstr, -1, nowchar,length, 0, 0 );

   //转换ANSI,字符部分不变，汉字转换成相应的拼音
   char *returnstr = new char[6*length +1];
   memset(returnstr,0,6*length +1);

   int offset = 0; 
   for (int j = 0; j < length;) // 循环处理字节数组
   {
      if (nowchar[j] >= 0 && nowchar[j] < 128) // 非汉字处理
      {

         returnstr[offset] = nowchar[j];
         offset++;
         j++;
         continue;
      }

      // 汉字处理
      chrasc = nowchar[j] * 256 + nowchar[j+1]+256;

      if (chrasc > 0 && chrasc < 160)
      {
         returnstr[offset]= nowchar[j];
         offset++;
         j++;
      }
      else
      {
         for (int i = (sizeof(pyvalue)/sizeof(pyvalue[0]) - 1); i >= 0; i--)
         {
            if (pyvalue[i] <= chrasc)
            {
               strcpy(returnstr+offset ,pystr[i]);

               offset +=strlen(pystr[i]);  
               break;
            }
         }
         j +=2;
      }
   }
   if(strlen(returnstr)>0)
   {
      pcReturnString = new char[strlen(returnstr)+1];
      memset(pcReturnString,0,strlen(returnstr)+1);
      strcpy(pcReturnString,returnstr);
   }
   delete []returnstr;
   delete []nowchar;

   CString strPy(pcReturnString);
   delete []pcReturnString;

   return strPy;
}