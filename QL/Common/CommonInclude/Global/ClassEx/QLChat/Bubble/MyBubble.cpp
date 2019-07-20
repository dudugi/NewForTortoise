
// MyTabDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MyBubble.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyTabDlg 对话框

BEGIN_MESSAGE_MAP(CMyBubble, CWnd)
   ON_WM_PAINT()
   ON_WM_SHOWWINDOW()
   ON_WM_TIMER()
END_MESSAGE_MAP()

enum
{
   TIMER_ID_HIDE = 133,
   TIMER_TIME = 1500,
   WINDOW_WIDTH = 190,
   WINDOW_HEIGHT = 19,
};

void CMyBubble::OnPaint()
{
   CPaintDC dc(this); // 用于绘制的设备上下文
   dc.SaveDC();
   HGDIOBJ hBrush = GetStockObject(m_nBrush);
   if (hBrush)
      dc.SelectObject(hBrush);
   dc.RoundRect(0, 0, m_nWindowWidth, WINDOW_HEIGHT, 10, 10);
   dc.SelectObject(&m_Font);
   dc.SetTextColor(RGB(0, 0, 255));
   dc.SetBkMode(TRANSPARENT);
   dc.TextOut(3, 3, m_sText);
   dc.RestoreDC(-1);
}

void CMyBubble::SetPos(int nX, int nY)
{
   CRect Rect;
   GetWindowRect(&Rect);
   Rect.MoveToXY(nX, nY);
   MoveWindow(&Rect);
}

void CMyBubble::OnShowWindow(BOOL bShow, UINT nStatus)
{
   CWnd::OnShowWindow(bShow, nStatus);
}

void CMyBubble::OnTimer(UINT_PTR nIDEvent)
{
   // TODO: 在此添加消息处理程序代码和/或调用默认值
   if (TIMER_ID_HIDE == nIDEvent)
   {
      KillTimer(TIMER_ID_HIDE);
      this->ShowWindow(SW_HIDE);
   }
   else
   {
      CWnd::OnTimer(nIDEvent);
   }
}

BOOL CMyBubble::Create(int nX, int nY, HWND hParent, const CString &sText)
{

   if (!CreateEx(0, _T("Static"), _T(""), WS_CHILD, nX, nY, WINDOW_WIDTH, WINDOW_HEIGHT, hParent, 0, NULL))
      return FALSE;

   m_Font.CreateFont( 13,                                          //   nHeight   
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
      _T("宋体"));

   m_sText = sText;


   CDC MemDC;
   CClientDC ClientDC(this);
   MemDC.CreateCompatibleDC(&ClientDC);
   MemDC.SelectObject(&m_Font);
   CSize TextSize = MemDC.GetTextExtent(m_sText);
   m_nWindowWidth = 3 + TextSize.cx + 4;

   CRect Rect;
   GetWindowRect(&Rect);
   Rect.right = Rect.left + m_nWindowWidth;
   MoveWindow(&Rect);

   return TRUE;
}

void CMyBubble::SetText(const CString &sText)
{
   if (m_sText == sText)
      return;
   m_sText = sText;
   CDC MemDC;
   CClientDC ClientDC(this);
   MemDC.CreateCompatibleDC(&ClientDC);
   MemDC.SelectObject(&m_Font);
   CSize TextSize = MemDC.GetTextExtent(m_sText);
   m_nWindowWidth = 3 + TextSize.cx + 4;
   CWnd *pParent = GetParent();
   if (pParent && pParent->GetSafeHwnd())
   {
      CRect Rect;
      GetWindowRect(&Rect);
      Rect.right = Rect.left + m_nWindowWidth;
      pParent->ScreenToClient(&Rect);
      MoveWindow(&Rect);
   }
}

CMyBubble::CMyBubble()
   :m_nWindowWidth(0),m_nBrush(NULL_BRUSH)
{

}

BOOL CMyBubble::Show()
{
   ShowWindow(SW_SHOW);
   SetTimer(TIMER_ID_HIDE, TIMER_TIME, NULL);
   return TRUE;
}

BOOL CMyBubble::Hide()
{
   if (!ShowWindow(SW_HIDE))
      return FALSE;

   return TRUE;
}