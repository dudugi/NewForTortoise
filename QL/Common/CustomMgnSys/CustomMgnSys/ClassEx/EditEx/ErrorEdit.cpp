// NewEdit.cpp : 实现文件
//

#include "stdafx.h"
#include "ErrorEdit.h"


// CNewEdit

IMPLEMENT_DYNAMIC(CErrorEdit, CWnd)

CErrorEdit::CErrorEdit()
{
	FreeResources(FALSE);
	m_bIsError = FALSE;
	m_byAlign = ST_ALIGN_HORIZ;

	m_pbmpOldBk = NULL;
	m_prcOldWind = NULL;

	m_pctrEt = NULL;
	RegisterWindowClass();
}

CErrorEdit::~CErrorEdit()
{

	if (m_dcBk.m_hDC && m_pbmpOldBk)
	{
		m_dcBk.SelectObject(m_pbmpOldBk);
	} // if
	if (NULL != m_prcOldWind)
	{
		delete m_prcOldWind;
		m_prcOldWind = NULL;
	}

	if (NULL != m_pctrEt)
	{
		delete m_pctrEt;
		m_pctrEt = NULL;
	}

	DestroyWindow();
}


BOOL CErrorEdit::Create( const RECT& rect, CWnd* parent, UINT nID, DWORD dwStyle /*= WS_CHILD | WS_BORDER | WS_TABSTOP | WS_VISIBLE*/ )
{
	ASSERT(parent->GetSafeHwnd());

	if (!CWnd::Create(ERROREDIT_CLASSNAME, NULL, dwStyle, rect, parent, nID))
		return FALSE;
	return TRUE;
}

BOOL CErrorEdit::RegisterWindowClass()
{
	WNDCLASS wndcls;
	HINSTANCE hInst = AfxGetResourceHandle();

	if (!(::GetClassInfo(hInst, ERROREDIT_CLASSNAME, &wndcls)))
	{
		wndcls.style            = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
		wndcls.lpfnWndProc      = ::DefWindowProc;
		wndcls.cbClsExtra       = wndcls.cbWndExtra = 0;
		wndcls.hInstance        = hInst;
		wndcls.hIcon            = NULL;
#ifndef _WIN32_WCE_NO_CURSOR
		wndcls.hCursor          = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
#else
		wndcls.hCursor          = 0;
#endif
		wndcls.hbrBackground    = (HBRUSH) (COLOR_3DFACE + 1);
		wndcls.lpszMenuName     = NULL;
		wndcls.lpszClassName    = ERROREDIT_CLASSNAME;

		if (!AfxRegisterClass(&wndcls))
		{
			AfxThrowResourceException();
			return FALSE;
		}
	}

	return TRUE;
}

void CErrorEdit::SetError( BOOL bError /*= TRUE*/,BOOL bRepaint /*= TRUE*/ )
{
	if (m_csIcons.hIcon)
	{
		m_bIsError = bError;
		if (bRepaint)
		{
			Invalidate();
		}
	}
}

DWORD CErrorEdit::SetAlign( BYTE byAlign, BOOL bRepaint /*= TRUE*/ )
{
	switch (byAlign)
	{    
	case ST_ALIGN_HORIZ:
	case ST_ALIGN_HORIZ_RIGHT:
		m_byAlign = byAlign;
		if (bRepaint)	Invalidate();
		return ERROREDIT_OK;
		break;
	} // switch

	return ERROREDIT_INVALIDALIGN;
}

DWORD CErrorEdit::SetIcon( int nIcon, int nCxDesired, int nCyDesired )
{
	HICON		hIcon			= NULL;
	HINSTANCE	hInstResource	= NULL;

	// Find correct resource handle
	hInstResource = AfxFindResourceHandle(MAKEINTRESOURCE(nIcon), RT_GROUP_ICON);
	hIcon = (HICON)::LoadImage(hInstResource, MAKEINTRESOURCE(nIcon), IMAGE_ICON, nCxDesired, nCxDesired, 0);
	return SetIcon(hIcon);
}

DWORD CErrorEdit::SetIcon( int nIcon )
{
	return SetIcon(nIcon, 0, 0);
}

DWORD CErrorEdit::SetIcon( HICON hIcon )
{
	BOOL		bRetValue;
	ICONINFO	ii;

	// Free any loaded resource
	FreeResources();

	if (hIcon)
	{
		// Icon when mouse over button?
		m_csIcons.hIcon = hIcon;
		// Get icon dimension
		::ZeroMemory(&ii, sizeof(ICONINFO));
		bRetValue = ::GetIconInfo(hIcon, &ii);
		if (bRetValue == FALSE)
		{
			FreeResources();
			return ERROREDIT_INVALIDRESOURCE;
		} // if

		m_csIcons.dwWidth	= (DWORD)(ii.xHotspot * 2);
		m_csIcons.dwHeight	= (DWORD)(ii.yHotspot * 2);
		::DeleteObject(ii.hbmMask);
		::DeleteObject(ii.hbmColor);
	} // if

	Invalidate();

	return ERROREDIT_OK;
}


BOOL CErrorEdit::SetToolTip( LPCTSTR szTips,UINT nDelay /*= 200*/ )
{
	EnableToolTips(TRUE);

	if (!m_ctrTip)
	{
		m_ctrTip.Create(this);
		m_ctrTip.Activate(TRUE);
		m_ctrTip.AddTool(this,szTips);
		m_ctrTip.SetDelayTime(nDelay); 
	}
	else
	{
		m_ctrTip.UpdateTipText(szTips,this);
	}
	return TRUE;
}

void CErrorEdit::FreeResources( BOOL bCheckForNULL /*= TRUE*/ )
{
	if (bCheckForNULL)
	{
		if (m_csIcons.hIcon)	::DestroyIcon(m_csIcons.hIcon);
	} // if

	::ZeroMemory(&m_csIcons, sizeof(m_csIcons));
}

void CErrorEdit::PaintBk( CDC* pDC )
{
	CClientDC clDC(GetParent());
	CRect rect;
	CRect rect1;

	GetClientRect(rect);

	GetWindowRect(rect1);
	GetParent()->ScreenToClient(rect1);

	if (m_dcBk.m_hDC == NULL)
	{
		m_dcBk.CreateCompatibleDC(&clDC);
		m_bmpBk.CreateCompatibleBitmap(&clDC, rect.Width(), rect.Height());
		m_pbmpOldBk = m_dcBk.SelectObject(&m_bmpBk);
		m_dcBk.BitBlt(0, 0, rect.Width(), rect.Height(), &clDC, rect1.left, rect1.top, SRCCOPY);
	} // if

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &m_dcBk, 0, 0, SRCCOPY);
}

void CErrorEdit::DrawTheIcon( CDC* pDC, CRect* rcItem )
{
	CRect	rImage;

	// Ole'!
	pDC->DrawState(	rcItem->TopLeft(),
		rcItem->Size(), 
		m_csIcons.hIcon,
		DSS_NORMAL, 
		(CBrush*)NULL);
}

CRect CErrorEdit::GetIconRect()
{
	//获取icon的区域
	CRect rcClient(0,0,0,0),rcIcon(0,0,0,0);
	GetClientRect(&rcClient);
	if (m_bIsError)
	{
		switch(m_byAlign)
		{
		case ST_ALIGN_HORIZ://Icon在左边
			{
				rcIcon.left = rcClient.left;
				rcIcon.right = rcClient.left + m_csIcons.dwWidth;
				rcIcon.top = rcClient.top;
				rcIcon.bottom = rcClient.top + m_csIcons.dwHeight;
			}
			break;
		case ST_ALIGN_HORIZ_RIGHT://Icon在右边
			{
				rcIcon.left = rcClient.right - m_csIcons.dwWidth;
				rcIcon.right = rcClient.right;
				rcIcon.top = rcClient.top;
				rcIcon.bottom = rcClient.top + m_csIcons.dwHeight;
			}
			break;
		}
	}

	return rcIcon;
}

CRect CErrorEdit::GetEditRect()
{
	//获取编辑框的区域
	CRect rcClient(0,0,0,0),rcEdit(0,0,0,0);
	GetClientRect(&rcClient);
	if (m_bIsError)
	{
		switch(m_byAlign)
		{
		case ST_ALIGN_HORIZ://Icon在左边
			{
				rcEdit.left = rcClient.left + m_csIcons.dwWidth;
				rcEdit.right = rcClient.right;
				rcEdit.top = rcClient.top;
				rcEdit.bottom = rcClient.bottom;
			}
			break;
		case ST_ALIGN_HORIZ_RIGHT://Icon在右边
			{
				rcEdit.left = rcClient.left;
				rcEdit.right = rcClient.right - m_csIcons.dwWidth;
				rcEdit.top = rcClient.top;
				rcEdit.bottom = rcClient.bottom;
			}
			break;
		}
	}
	else
	{
		rcEdit.CopyRect(&rcClient);
	}
	
	return rcEdit;
}

BEGIN_MESSAGE_MAP(CErrorEdit, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CNewEdit 消息处理程序

void CErrorEdit::OnPaint()
{
	CDC *pDC = GetDC();
	PaintBk(pDC);
	if (NULL == m_pctrEt)
	{
		CRect rcEt(0,0,0,0);
		m_pctrEt = new CEdit;
		m_pctrEt->Create(ES_LEFT|ES_AUTOHSCROLL|WS_CHILD | WS_BORDER | WS_TABSTOP | WS_VISIBLE,rcEt,this,IDC_EDITINPLACE_CONTROL);
		m_pctrEt->ShowWindow(SW_SHOW);
		m_pctrEt->SetFont(GetParent()->GetFont());
	}

	CRect rcEt = GetEditRect();
	m_pctrEt->MoveWindow(rcEt);
	if (m_bIsError)
	{
		DrawTheIcon(pDC,&(GetIconRect()));
	}
	ReleaseDC(pDC);

	CWnd::OnPaint();
}


void CErrorEdit::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (IsWindow(m_pctrEt->GetSafeHwnd()))
	{
		m_pctrEt->SetFocus();
	}

	CWnd::OnLButtonDown(nFlags, point);
}

BOOL CErrorEdit::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_MOUSEMOVE)
	{
		if (m_ctrTip)
		{
			CRect rcIcon;
			rcIcon.CopyRect(GetIconRect());
			CPoint hitPt = pMsg->pt;
			ScreenToClient(&hitPt);

			if (rcIcon.PtInRect(hitPt))
			{
				m_ctrTip.RelayEvent(pMsg);
			}
		}
	}

	return CWnd::PreTranslateMessage(pMsg);
}

