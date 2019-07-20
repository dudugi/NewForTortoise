// DesktopDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DlgDesktop.h"


// CDesktopDlg �Ի���

IMPLEMENT_DYNCREATE(CDlgDesktop, CMFCDesktopAlertDialog)

CDlgDesktop::CDlgDesktop()
{
	m_strText = _T("��ϲ���������ɹ���");
	m_Font.DeleteObject();
	m_Font.CreateFont(14,0,0,0,700,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FF_SWISS, _T("����"));
	m_clrText = RGB(255,0,0);
	m_clrTitle = RGB(255,0,0);

	wParam = 0;
	lParam = 0;
	pOwerWnd = NULL;
}

CDlgDesktop::~CDlgDesktop()
{
	m_Font.DeleteObject();
}

void CDlgDesktop::DoDataExchange(CDataExchange* pDX)
{
	CMFCDesktopAlertDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgDesktop, CMFCDesktopAlertDialog)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CDesktopDlg ��Ϣ�������

void CDlgDesktop::OnDraw (CDC* pDC)
{
	CMFCDesktopAlertDialog::OnDraw (pDC);

	CRect rectClient;
	GetClientRect (rectClient);
	
	CSize sizeLogo = m_imgLogo.GetImageSize ();
	CAfxDrawState ds;
	m_imgLogo.PrepareDrawImage (ds);

	m_imgLogo.Draw (pDC, 
		rectClient.right - sizeLogo.cx - 5,
		rectClient.bottom - sizeLogo.cy - 5,
		0);

	m_imgLogo.EndDrawImage (ds);

	
	//��ʾ��ʾ��Ϣ
	CFont * pOldFont = pDC->SelectObject(&m_Font);//ʹ�õ�ʱ��ѡ���Լ�������
	CRect rcText = rectClient;
	rcText.InflateRect(0,0,-sizeLogo.cy,0);
	pDC->SetTextColor(m_clrText);
	pDC->SetBkMode(TRANSPARENT);

	//���У��������ң���ʾ
	CRect temp = rcText; 
	int height = pDC->DrawText(m_strText, temp, DT_CENTER | DT_WORDBREAK | DT_EDITCONTROL | DT_CALCRECT);  
	rcText.DeflateRect(0, (rcText.Height() - height)/2);// change rect  
	pDC->DrawText(m_strText, rcText, DT_CENTER | DT_WORDBREAK | DT_EDITCONTROL);

	pDC->SelectObject(pOldFont);//��ԭ
}

BOOL CDlgDesktop::OnInitDialog() 
{
	CMFCDesktopAlertDialog::OnInitDialog();

	m_imgLogo.Load (/*IDB_PNG_LOGOSIMPLE*/IDB_MAIN);
	m_imgLogo.SetTransparentColor (RGB (236, 0, 140));
	m_imgLogo.SetSingleImage ();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgDesktop::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (pOwerWnd)
	{
		pOwerWnd->SendMessage(WM_DESKTOP_DBCLICK,wParam,lParam);
	}
	CMFCDesktopAlertDialog::OnLButtonDblClk(nFlags, point);
}

void CDlgDesktop::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (pOwerWnd)
	{
		pOwerWnd->SendMessage(WM_DESKTOP_DBCLICK,wParam,lParam);
	}
	CMFCDesktopAlertDialog::OnLButtonDown(nFlags, point);
}

void CDlgDesktop::OnLButtonUp(UINT nFlags, CPoint point)
{
	CMFCDesktopAlertDialog::OnLButtonUp(nFlags, point);
}
