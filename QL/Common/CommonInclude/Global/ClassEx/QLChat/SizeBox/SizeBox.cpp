
// MyTabDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SizeBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyTabDlg 对话框

BEGIN_MESSAGE_MAP(CSizeBox, CWnd)
   ON_WM_PAINT()
   ON_WM_SHOWWINDOW()
   ON_WM_SETCURSOR()
   ON_WM_MOUSEMOVE()
   ON_WM_LBUTTONDOWN()
   ON_WM_LBUTTONUP()
   ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

void CSizeBox::OnPaint()
{
   CPaintDC dc(this); // 用于绘制的设备上下文
}

BOOL CSizeBox::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
   CPoint Point;
   GetCursorPos(&Point);
   CRect Rect;
   GetWindowRect(&Rect);

   if (IsWindowVisible()) //从当前鼠标的坐标获得鼠标所在窗口的句柄，并判断是否为LISTBOX控件 
   {
      LPTSTR pszID = m_ResizeHelper.GetCursorResourceID(Point, Rect);
      if (pszID)
         ::SetCursor(::LoadCursor(NULL, pszID));
      else
         ::SetCursor(::LoadCursor(NULL, IDC_ARROW));
   }
   else
   {
      ::SetCursor(::LoadCursor(NULL, IDC_ARROW));
   }
   return TRUE;
}

void CSizeBox::SetPos(int nX, int nY)
{
   if (!GetSafeHwnd())
      return;
   CRect Rect;
   GetWindowRect(&Rect);
   Rect.MoveToXY(nX, nY);
   MoveWindow(&Rect);
}

void CSizeBox::OnShowWindow(BOOL bShow, UINT nStatus)
{
   CWnd::OnShowWindow(bShow, nStatus);
}

BOOL CSizeBox::Create(int nX, int nY, int nWidth, int nHeight, HWND hParent, const CString &sText)
{
   if (!CreateEx(0, _T("Static"), _T(""), WS_CHILD, nX, nY, nWidth, nHeight, hParent, 0, NULL))
      return FALSE;

   ModifyStyle(0,SS_NOTIFY);

   return TRUE;
}

CSizeBox::CSizeBox()
{

}

CSizeBox::~CSizeBox()
{

}

BOOL CSizeBox::Show()
{
   if (!GetSafeHwnd())
      return FALSE;
   ShowWindow(SW_SHOW);
   return TRUE;
}

BOOL CSizeBox::Hide()
{
   if (!ShowWindow(SW_HIDE))
      return FALSE;

   return TRUE;
}

void CSizeBox::OnLButtonDown(UINT nFlags, CPoint point)
{
   CRect Rect;
   GetClientRect(&Rect);

   m_ResizeHelper.SetMouseDownPos(point, Rect);
   if (m_ResizeHelper.IsDownInRect())
      SetCapture();
}

void CSizeBox::OnLButtonUp(UINT nFlags, CPoint point)
{
   ReleaseCapture();
   if (m_ResizeHelper.IsDownInRect() && m_funcDragOver)
   {
      m_funcDragOver(this);
   }
}

void CSizeBox::OnMouseMove(UINT nFlags, CPoint Point)
{
   if (GetKeyState(VK_LBUTTON) < 0 && m_ResizeHelper.IsDownInRect())
   {
      CRect OrgRect;
      GetWindowRect(&OrgRect);
      CPoint PointScreen(Point);
      ClientToScreen(&PointScreen);

      CRect NewRect;
      BOOL bDontChangeSize;
      m_ResizeHelper.NewPointMove(OrgRect, PointScreen, &NewRect, &bDontChangeSize);

      if (m_funcOnDragToNewRect)
         m_funcOnDragToNewRect(NewRect, bDontChangeSize);
   }
   CWnd::OnMouseMove(nFlags, Point);
}

BOOL CSizeBox::OnEraseBkgnd(CDC* pDC)
{
   CRect RectScreen;
   GetWindowRect(&RectScreen);
   CRect RectClient(RectScreen);
   ScreenToClient(&RectClient);

   if (!m_funcDrawBackground)
   {
      CBrush Brush;
      Brush.CreateSolidBrush(RGB(255, 255, 255));
      pDC->SelectObject(&Brush);
      pDC->Rectangle(RectClient);
   }
   else
   {
      m_funcDrawBackground(RectScreen, RectClient, pDC);
   }

   m_ResizeHelper.PaintResizeRect(pDC, RectClient);

   return TRUE;
}