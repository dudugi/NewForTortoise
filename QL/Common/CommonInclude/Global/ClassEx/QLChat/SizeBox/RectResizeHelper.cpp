#include "stdafx.h"
#include "RectResizeHelper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

LPTSTR CRectResizeHelper::GetCursorResourceID(const CPoint &MousePoint, const CRect &WindowRect)
{
   MouseDragType Pos = SetMouseDownPos(MousePoint, WindowRect);
   LPTSTR pszRet = nullptr;
   switch (Pos)
   {
   case MOUSE_POS_LEFT_TOP:
   case MOUSE_POS_RIGHT_BOTTOM:
      pszRet = IDC_SIZENWSE;
      break;
   case MOUSE_POS_RIGHT_TOP:
   case MOUSE_POS_LEFT_BOTTOM:
      pszRet = IDC_SIZENESW;
      break;
   case MOUSE_POS_LINE:
      pszRet = IDC_SIZEALL;
      break;
   case MOUSE_POS_MIDDLE_BOTTOM:
   case MOUSE_POS_MIDDLE_TOP:
      pszRet = IDC_SIZENS;
      break;
   case MOUSE_POS_LEFT_MIDDLE:
   case MOUSE_POS_RIGHT_MIDDLE:
      pszRet = IDC_SIZEWE;
      break;
   default:
   case MOUSE_POS_OTHER:
   case MOUSE_POS_OUTER:
      break;
   }
   return pszRet;
}

CRectResizeHelper::CRectResizeHelper(int nFrameWidth, int nFrameWidthMouse, int nMinWindowHeight, int nMinWindowWidth)
   : m_eMouseDownPos(MOUSE_POS_OUTER),
   m_nFrameWidth(nFrameWidth),
   m_nFrameWidthHalf(nFrameWidth / 2),
   m_nFrameWidthMouse(nFrameWidthMouse),
   m_nFrameWidthMouseHalf(nFrameWidthMouse / 2),
   m_nMinWindowHeight(nMinWindowHeight),
   m_nMinWindowWidth(nMinWindowWidth)
{

}

CRectResizeHelper::~CRectResizeHelper()
{

}

CRectResizeHelper::MouseDragType CRectResizeHelper::SetMouseDownPos(const CPoint &MousePoint, const CRect &WindowRect)
{
   if (!WindowRect.PtInRect(MousePoint))
   {
      m_eMouseDownPos = MOUSE_POS_OUTER;
      return MOUSE_POS_OUTER;
   }

   MouseDragType eMousePos;
   eMousePos = MOUSE_POS_OTHER;

   if (MousePoint.x - WindowRect.left < m_nFrameWidthMouse)
   {
      if (MousePoint.y - WindowRect.top < m_nFrameWidthMouse)
      {
         eMousePos = MOUSE_POS_LEFT_TOP;
      }
      else if (WindowRect.bottom - MousePoint.y < m_nFrameWidthMouse)
      {
         eMousePos = MOUSE_POS_LEFT_BOTTOM;
      }
      else if (abs(MousePoint.y - (WindowRect.top + WindowRect.Height() / 2)) <= m_nFrameWidthMouseHalf)
      {
         eMousePos = MOUSE_POS_LEFT_MIDDLE;
      }
      else
      {
         eMousePos = MOUSE_POS_LINE;
      }
   }
   else if (WindowRect.right - MousePoint.x < m_nFrameWidthMouse)
   {
      if (MousePoint.y - WindowRect.top < m_nFrameWidthMouse)
      {
         eMousePos = MOUSE_POS_RIGHT_TOP;
      }
      else if (WindowRect.bottom - MousePoint.y < m_nFrameWidthMouse)
      {
         eMousePos = MOUSE_POS_RIGHT_BOTTOM;
      }
      else if (abs(MousePoint.y - (WindowRect.top + WindowRect.Height() / 2)) <= m_nFrameWidthMouseHalf)
      {
         eMousePos = MOUSE_POS_RIGHT_MIDDLE;
      }
      else
      {
         eMousePos = MOUSE_POS_LINE;
      }
   }
   else if (abs(MousePoint.x - (WindowRect.left + WindowRect.Width() / 2)) <= m_nFrameWidthMouseHalf)
   {
      if (MousePoint.y - WindowRect.top < m_nFrameWidthMouse)
      {
         eMousePos = MOUSE_POS_MIDDLE_TOP;
      }
      else if (WindowRect.bottom - MousePoint.y < m_nFrameWidthMouse)
      {
         eMousePos = MOUSE_POS_MIDDLE_BOTTOM;
      }
   }
   else
   {
      if (MousePoint.y - WindowRect.top < m_nFrameWidthMouse)
      {
         eMousePos = MOUSE_POS_LINE;
      }
      else if (WindowRect.bottom - MousePoint.y < m_nFrameWidthMouse)
      {
         eMousePos = MOUSE_POS_LINE;
      }
   }
   m_eMouseDownPos = eMousePos;
   m_MouseDownPointInRect.x = MousePoint.x - WindowRect.left;
   m_MouseDownPointInRect.y = MousePoint.y - WindowRect.top;
   return eMousePos;
}

BOOL CRectResizeHelper::PaintResizeRect(CDC *pDC, const CRect &RectToPaint)
{
   if (!pDC)
      return FALSE;

   CDC &dc = *pDC;

   dc.SaveDC();

   HGDIOBJ hNullBrush = GetStockObject(NULL_BRUSH);
   dc.SelectObject(hNullBrush);

   CPen Pen;
   Pen.CreatePen(PS_DASH, 1, RGB(0, 0, 0));

   dc.SelectObject(&Pen);

   CRect Rect(RectToPaint);

   int nWindowWidth = Rect.Width();
   int nWindowHeight = Rect.Height();

   Rect.InflateRect(CSize(-m_nFrameWidthHalf, -m_nFrameWidthHalf));
   dc.Rectangle(&Rect);

   CBrush Brush;
   Brush.CreateSolidBrush(RGB(255, 255, 255));
   dc.SelectObject(&Brush);

   CRect SmallRect(RectToPaint.left, RectToPaint.top, RectToPaint.left + m_nFrameWidth, 
      RectToPaint.top + m_nFrameWidth);
   dc.Rectangle(&SmallRect);

   SmallRect.MoveToX(RectToPaint.left + nWindowWidth/2 - m_nFrameWidthHalf);
   dc.Rectangle(&SmallRect);

   SmallRect.MoveToX(RectToPaint.left + nWindowWidth - m_nFrameWidth);
   dc.Rectangle(&SmallRect);

   SmallRect.MoveToXY(RectToPaint.left, RectToPaint.top + nWindowHeight / 2 - m_nFrameWidthHalf);
   dc.Rectangle(&SmallRect);

   SmallRect.MoveToX(RectToPaint.left + nWindowWidth - m_nFrameWidth);
   dc.Rectangle(&SmallRect);

   SmallRect.MoveToXY(RectToPaint.left, RectToPaint.top + nWindowHeight - m_nFrameWidth);
   dc.Rectangle(&SmallRect);

   SmallRect.MoveToX(RectToPaint.left + nWindowWidth/2 - m_nFrameWidthHalf);
   dc.Rectangle(&SmallRect);

   SmallRect.MoveToX(RectToPaint.left + nWindowWidth - m_nFrameWidth);
   dc.Rectangle(&SmallRect);

   dc.RestoreDC(-1);

   return TRUE;
}

void CRectResizeHelper::NewPointMove(const CRect &OrgRect, const CPoint &NewPoint, CRect *pNewRect, BOOL *pbDontChangeSize)
{
   CRect NewRect(OrgRect);
   MouseDragType DragType = m_eMouseDownPos;
   CPoint MousePoint = NewPoint;

   if (DragType == CRectResizeHelper::MOUSE_POS_LEFT_MIDDLE)
   {
      NewRect.left = MousePoint.x;
      if (OrgRect.right - NewRect.left < m_nMinWindowWidth)
      {
         NewRect.left = OrgRect.right - m_nMinWindowWidth;
      }
   }
   else if (DragType == CRectResizeHelper::MOUSE_POS_RIGHT_MIDDLE)
   {
      NewRect.right = MousePoint.x;
      if (NewRect.right - OrgRect.left < m_nMinWindowWidth)
      {
         NewRect.right = OrgRect.left + m_nMinWindowWidth;
      }
   }
   else if (DragType == CRectResizeHelper::MOUSE_POS_MIDDLE_TOP)
   {
      NewRect.top = MousePoint.y;
      if (OrgRect.bottom - NewRect.top < m_nMinWindowHeight)
      {
         NewRect.top = OrgRect.bottom - m_nMinWindowHeight;
      }
   }
   else if (DragType == CRectResizeHelper::MOUSE_POS_MIDDLE_BOTTOM)
   {
      NewRect.bottom = MousePoint.y;
      if (NewRect.bottom - OrgRect.top < m_nMinWindowHeight)
      {
         NewRect.bottom = OrgRect.top + m_nMinWindowHeight;
      }
   }
   else if (DragType == CRectResizeHelper::MOUSE_POS_LEFT_TOP)
   {
      NewRect.left = MousePoint.x;
      NewRect.top = MousePoint.y;
      if (OrgRect.right - NewRect.left < m_nMinWindowWidth)
      {
         NewRect.left = OrgRect.right - m_nMinWindowWidth;
      }
      if (OrgRect.bottom - NewRect.top < m_nMinWindowHeight)
      {
         NewRect.top = OrgRect.bottom - m_nMinWindowHeight;
      }
   }
   else if (DragType == CRectResizeHelper::MOUSE_POS_LEFT_BOTTOM)
   {
      NewRect.left = MousePoint.x;
      NewRect.bottom = MousePoint.y;
      if (OrgRect.right - NewRect.left < m_nMinWindowWidth)
      {
         NewRect.left = OrgRect.right - m_nMinWindowWidth;
      }
      if (NewRect.bottom - OrgRect.top < m_nMinWindowHeight)
      {
         NewRect.bottom = OrgRect.top + m_nMinWindowHeight;
      }
   }
   else if (DragType == CRectResizeHelper::MOUSE_POS_RIGHT_BOTTOM)
   {
      NewRect.right = MousePoint.x;
      NewRect.bottom = MousePoint.y;
      if (NewRect.right - OrgRect.left < m_nMinWindowWidth)
      {
         NewRect.right = OrgRect.left + m_nMinWindowWidth;
      }
      if (NewRect.bottom - OrgRect.top < m_nMinWindowHeight)
      {
         NewRect.bottom = OrgRect.top + m_nMinWindowHeight;
      }
   }
   else if (DragType == CRectResizeHelper::MOUSE_POS_RIGHT_TOP)
   {
      NewRect.right = MousePoint.x;
      NewRect.top = MousePoint.y;
      if (NewRect.right - OrgRect.left < m_nMinWindowWidth)
      {
         NewRect.right = OrgRect.left + m_nMinWindowWidth;
      }
      if (OrgRect.bottom - NewRect.top < m_nMinWindowHeight)
      {
         NewRect.top = OrgRect.bottom - m_nMinWindowHeight;
      }
   }
   else if (DragType == CRectResizeHelper::MOUSE_POS_LINE || DragType == CRectResizeHelper::MOUSE_POS_OTHER)
   {
      NewRect.MoveToXY(MousePoint.x - m_MouseDownPointInRect.x, MousePoint.y - m_MouseDownPointInRect.y);
   }
   BOOL bDontChangeSize = FALSE;
   if (DragType == CRectResizeHelper::MOUSE_POS_LINE || DragType == CRectResizeHelper::MOUSE_POS_OTHER)
      bDontChangeSize = TRUE;

   if (pNewRect)
   {
      *pNewRect = NewRect;
   }

   if (pbDontChangeSize)
   {
      *pbDontChangeSize = bDontChangeSize;
   }
}