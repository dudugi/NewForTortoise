#include "stdafx.h"
#include "SizeBoxEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

enum
{
   RICH_EDIT_ID = 1323,
};

BEGIN_MESSAGE_MAP(CSizeBoxEdit, CSizeBox)
   ON_WM_SIZE()
   ON_WM_MOVE()
   ON_EN_CHANGE(RICH_EDIT_ID, &CSizeBoxEdit::OnEnChangeRichedit21)
END_MESSAGE_MAP()

void CSizeBoxEdit::SetEditDrawBackgroundFunc(std::function<void(const CRect &RectInScreen, const CRect &RectInClient, CDC *pTargetDC)> funcBackGround)
{
   m_funcDrawBackground = funcBackGround;
   m_RichTransparent.m_funcDrawBackground = funcBackGround;
}

BOOL CSizeBoxEdit::Create(int nX, int nY, int nWidth, int nHeight,
   HWND hParent, const CString &sText)
{
   if (!CSizeBox::Create(nX, nY, nWidth, nHeight, hParent, sText))
      return FALSE;
   CRect Rect(0, 0, nWidth, nHeight);
   Rect.InflateRect(-8, -8);

   if (!m_RichTransparent.Create(ES_MULTILINE | ES_AUTOVSCROLL | ES_WANTRETURN | WS_TABSTOP , Rect, this, RICH_EDIT_ID))
      return FALSE;

   if (!m_RichTransparent.ModifyStyleEx(0, WS_EX_TRANSPARENT))
      return FALSE;

   m_RichTransparent.SetEventMask(m_RichTransparent.GetEventMask() |
      ENM_CHANGE);

   return TRUE;
}

void CSizeBoxEdit::OnMove(int x, int y)
{
   if (!m_RichTransparent.GetSafeHwnd())
      return;
}

void CSizeBoxEdit::OnSize(UINT nType, int cx, int cy)
{
    CRect RectClient;
    GetClientRect(&RectClient);
    if (!m_RichTransparent.GetSafeHwnd())
       return;
 
    RectClient.InflateRect(-8, -8);
    m_RichTransparent.MoveWindow(RectClient);
}

BOOL CSizeBoxEdit::Show()
{
   if (!CSizeBox::Show())
      return FALSE;
   m_RichTransparent.ShowWindow(SW_SHOW);
   m_RichTransparent.SetFocus();
   return TRUE;
}

BOOL CSizeBoxEdit::GetCurText(CString *psText, CRect *pRect)
{
   if (!m_RichTransparent.GetSafeHwnd())
      return FALSE;

   CRect Rect1;
   m_RichTransparent.GetRect(&Rect1);

   int n1 = m_RichTransparent.CharFromPos(Rect1.TopLeft());
   int n2 = m_RichTransparent.CharFromPos(Rect1.BottomRight());
   CString sText;
   m_RichTransparent.GetTextRange(n1, n2, sText);

   if (psText)
      *psText = sText;

   if (pRect)
   {
      CRect Rect2;
      m_RichTransparent.GetWindowRect(&Rect2);
      *pRect = Rect2;
   }

   return TRUE;
}

BOOL CSizeBoxEdit::SetEditFontHeight(int nHeight, int nFontSize)
{
   if (!m_RichTransparent.GetSafeHwnd())
      return FALSE;
   
   CFont Font;
   Font.CreateFont(nHeight,                                          //   nHeight   
      0,                                                   //   nWidth   
      0,                                                   //   nEscapement 
      0,                                                   //   nOrientation   
      FW_NORMAL,                                   //   nWeight   
      FALSE,                                           //   bItalic   
      FALSE,                                           //   bUnderline   
      0,                                                   //   cStrikeOut   
      ANSI_CHARSET,                             //   nCharSet   
      OUT_DEFAULT_PRECIS,                 //   nOutPrecision   
      CLIP_DEFAULT_PRECIS,               //   nClipPrecision   
      DEFAULT_QUALITY,                       //   nQuality   
      DEFAULT_PITCH   |   FF_SWISS,     //   nPitchAndFamily     
      _T("ËÎÌו"));
   m_nFontHeight = nHeight;
   m_RichTransparent.SetFont(&Font);

   m_nFontSize = nFontSize;
   return TRUE;
}

BOOL CSizeBoxEdit::SetEditColor(COLORREF color)
{
   if (!m_RichTransparent.GetSafeHwnd())
      return FALSE;
   ::CHARFORMAT2 cf;
   m_RichTransparent.GetDefaultCharFormat(cf);
   cf.crTextColor = color;
   cf.dwMask = CFM_COLOR;
   cf.dwEffects &= ~CFE_AUTOCOLOR;
   m_RichTransparent.SetDefaultCharFormat(cf);
   return TRUE;
}

CSizeBoxEdit::CSizeBoxEdit()
   :m_nFontHeight(0), m_nBottomY(0), m_nFontSize(0)
{

}

void CSizeBoxEdit::OnEnChangeRichedit21()
{
   int n = m_RichTransparent.GetLineCount();
   int nPerLineHeight = m_nFontHeight + m_nFontHeight / 3;
   int nHeight = (n + 1) * nPerLineHeight;
   CRect Rect;
   m_RichTransparent.GetWindowRect(&Rect);

   if (Rect.Height() >= nHeight)
      return;

   if (Rect.bottom + 8 >= m_nBottomY)
      return;

   Rect.bottom = Rect.top + nHeight;

   if (Rect.bottom + 8 > m_nBottomY)
      Rect.bottom = m_nBottomY - 8;

   CRect RectFrame;
   RectFrame = Rect;
   RectFrame.InflateRect(8, 8);
   MoveWindow(&RectFrame);
 
   Invalidate();
}

BOOL CSizeBoxEdit::SetEditText(const CString &sText)
{
   if (!m_RichTransparent.GetSafeHwnd())
      return FALSE;
   m_RichTransparent.SetWindowText(sText);
   return TRUE;
}

BOOL CSizeBoxEdit::ReplaceSelEditText(const CString &sText)
{
   if (!m_RichTransparent.GetSafeHwnd())
      return FALSE;
   m_RichTransparent.ReplaceSel(sText);
   return TRUE;
}