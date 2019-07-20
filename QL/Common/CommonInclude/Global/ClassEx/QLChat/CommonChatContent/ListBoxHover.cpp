#include "stdafx.h"
#include <vector>
#include <algorithm>
#include "ListBoxHover.h"
#include <winuser.h>

enum
{
   //COLOR_TEXT = (RGB(192, 192, 230)),
   COLOR_TEXT = (RGB(0, 0, 0)),
   COLOR_TEXT_UNREAD_COUNT = (RGB(255, 0, 0)),
   COLOR_SELECTED_RECT = (RGB(21, 123, 225)),
   COLOR_HOVER_RECT = (RGB(51, 153, 255)),
   //COLOR_NORMAL_RECT = (RGB(128, 128, 128)),
   COLOR_NORMAL_RECT = (RGB(255, 255, 255)),

   PEN_RIGHT_SPACE = 10,
};

BEGIN_MESSAGE_MAP(CListBoxHover, CListBox)
   ON_WM_MOUSEMOVE()
   ON_MESSAGE(WM_MOUSELEAVE, &CListBoxHover::OnMouseLeave)
   ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

CListBoxHover::CListBoxHover()
   :m_nHoverIndex(enClearHoverIndex), m_bIsMouseTrack(TRUE), m_bPenHeight(FALSE),
   m_hIconHighlight(NULL), m_hIconNormal(NULL)
{

}

void CListBoxHover::DrawItem(LPDRAWITEMSTRUCT lpDIS)  
{  
   if (lpDIS->itemID == -1)
      return;
   CDC dc ;  
   dc.Attach(lpDIS->hDC);  
   CRect rcItem = lpDIS->rcItem ;  
   CString text;  
   GetText(lpDIS->itemID, text);  
   dc.SetBkMode(TRANSPARENT);  
   dc.SetTextColor(COLOR_TEXT);  
   if ((lpDIS->itemState & ODS_SELECTED))  
      dc.FillSolidRect(&rcItem, COLOR_SELECTED_RECT);
   else if(lpDIS->itemID == m_nHoverIndex)
      dc.FillSolidRect(&rcItem, COLOR_HOVER_RECT);
   else  
      dc.FillSolidRect(&rcItem, COLOR_NORMAL_RECT);

   CRect TextRect = rcItem;
   TextRect.right -= 16 + PEN_RIGHT_SPACE;
   dc.DrawText(text, &TextRect, DT_SINGLELINE|DT_VCENTER| DT_WORD_ELLIPSIS);

   if(lpDIS->itemID == m_nHoverIndex)
   {
      if (!m_hIconNormal)
      {
         int nX = 16;
         int nY = 16;
         int cb = ((nX + 3) & (-4)) * nY;

         std::vector<BYTE> bufBmpInfo;
         bufBmpInfo.resize(sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD));

         LPBITMAPINFO lpbi = (LPBITMAPINFO)&bufBmpInfo[0];
         lpbi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
         lpbi->bmiHeader.biWidth = nX;
         lpbi->bmiHeader.biHeight = nY;
         lpbi->bmiHeader.biPlanes = 1;
         lpbi->bmiHeader.biBitCount = 8;
         lpbi->bmiHeader.biCompression = BI_RGB;
         lpbi->bmiHeader.biSizeImage = (DWORD)cb;
         lpbi->bmiHeader.biXPelsPerMeter = 0;
         lpbi->bmiHeader.biYPelsPerMeter = 0;
         lpbi->bmiHeader.biClrUsed = 0;
         lpbi->bmiHeader.biClrImportant = 0;

         RGBQUAD tmp;
         tmp.rgbBlue = 0;
         tmp.rgbGreen = 0;
         tmp.rgbRed = 0;
         tmp.rgbReserved = 0;
         std::vector<RGBQUAD> vecRgbQuad(256, tmp);

         vecRgbQuad[1].rgbBlue = 255;
         vecRgbQuad[1].rgbGreen = 255;
         vecRgbQuad[1].rgbRed = 255;
         vecRgbQuad[1].rgbReserved = 0;
         vecRgbQuad[2].rgbBlue = 255;
         vecRgbQuad[2].rgbGreen = 0;
         vecRgbQuad[2].rgbRed = 0;
         vecRgbQuad[2].rgbReserved = 0;
         vecRgbQuad[3].rgbBlue = 128;
         vecRgbQuad[3].rgbGreen = 128;
         vecRgbQuad[3].rgbRed = 128;
         vecRgbQuad[3].rgbReserved = 0;

         memcpy(&bufBmpInfo[sizeof(BITMAPINFOHEADER)], vecRgbQuad.data(), sizeof(RGBQUAD)*256);

         BYTE* pBmpBits = NULL;
    
         HBITMAP hbmp = CreateDIBSection(dc.GetSafeHdc(), lpbi, DIB_RGB_COLORS, (void **)&pBmpBits, NULL, 0);
         ASSERT(hbmp);

         BYTE bits[256] = 
         {
            3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,
            3,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,
            0,3,0,0,3,3,3,0,0,0,0,0,0,0,0,0,
            0,3,0,3,0,0,0,3,0,0,0,0,0,0,0,0,
            0,3,3,0,0,0,0,0,3,0,0,0,0,0,0,0,
            0,0,3,0,0,0,0,0,0,3,0,0,0,0,0,0,
            0,0,0,3,0,0,0,0,0,0,3,0,0,0,0,0,
            0,0,0,0,3,0,0,0,0,0,0,3,0,0,0,0,
            0,0,0,0,0,3,0,0,0,0,0,0,3,0,0,0,
            0,0,0,0,0,0,3,0,0,0,0,0,0,3,0,0,
            0,0,0,0,0,0,0,3,0,0,0,0,0,3,3,0,
            0,0,0,0,0,0,0,0,3,0,0,0,3,0,3,3,
            0,0,0,0,0,0,0,0,0,3,0,3,0,0,0,3,
            0,0,0,0,0,0,0,0,0,0,3,0,0,0,3,3,
            0,0,0,0,0,0,0,0,0,0,0,3,0,3,3,0,
            0,0,0,0,0,0,0,0,0,0,0,0,3,3,0,0,
         };

         memcpy(pBmpBits, bits, 256);


         ICONINFO Info; 
         Info.fIcon = TRUE;
         Info.xHotspot = 0;
         Info.yHotspot = 0;
         Info.hbmColor = hbmp;

         BYTE* pBmpBits2 = NULL;
         lpbi->bmiHeader.biHeight = nY;
         HBITMAP hbmp2 = CreateDIBSection(dc.GetSafeHdc(), lpbi, DIB_RGB_COLORS, (void **)&pBmpBits2, NULL, 0);
         ASSERT(hbmp2);

         BYTE bits2[256] =
         {
            0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,
            0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,
            1,0,1,1,0,0,0,1,1,1,1,1,1,1,1,1,
            1,0,1,0,1,1,1,0,1,1,1,1,1,1,1,1,
            1,0,0,1,1,1,1,1,0,1,1,1,1,1,1,1,
            1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,
            1,1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,
            1,1,1,1,0,1,1,1,1,1,1,0,1,1,1,1,
            1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,1,
            1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,
            1,1,1,1,1,1,1,0,1,1,1,1,1,0,0,1,
            1,1,1,1,1,1,1,1,0,1,1,1,0,1,0,0,
            1,1,1,1,1,1,1,1,1,0,1,0,1,1,1,0,
            1,1,1,1,1,1,1,1,1,1,0,1,1,1,0,0,
            1,1,1,1,1,1,1,1,1,1,1,0,1,0,0,1,
            1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,
         };
         memcpy(pBmpBits2, bits2, 256);

         Info.hbmMask = hbmp2;
         m_hIconNormal = CreateIconIndirect(&Info);

         BYTE bits3[256] = 
         {
            2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,
            2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,
            0,2,0,0,2,2,2,0,0,0,0,0,0,0,0,0,
            0,2,0,2,0,0,0,2,0,0,0,0,0,0,0,0,
            0,2,2,0,0,0,0,0,2,0,0,0,0,0,0,0,
            0,0,2,0,0,0,0,0,0,2,0,0,0,0,0,0,
            0,0,0,2,0,0,0,0,0,0,2,0,0,0,0,0,
            0,0,0,0,2,0,0,0,0,0,0,2,0,0,0,0,
            0,0,0,0,0,2,0,0,0,0,0,0,2,0,0,0,
            0,0,0,0,0,0,2,0,0,0,0,0,0,2,0,0,
            0,0,0,0,0,0,0,2,0,0,0,0,0,2,2,0,
            0,0,0,0,0,0,0,0,2,0,0,0,2,0,2,2,
            0,0,0,0,0,0,0,0,0,2,0,2,0,0,0,2,
            0,0,0,0,0,0,0,0,0,0,2,0,0,0,2,2,
            0,0,0,0,0,0,0,0,0,0,0,2,0,2,2,0,
            0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,
         };

         memcpy(pBmpBits, bits3, 256);

         m_hIconHighlight = CreateIconIndirect(&Info);

         DeleteObject(hbmp);
         DeleteObject(hbmp2);
      }
      
      HICON hIcon = 0;
      if (m_bPenHeight)
         hIcon = m_hIconHighlight;
      else
         hIcon = m_hIconNormal;

      if (hIcon)
      {
         ::DrawIconEx(dc.GetSafeHdc(), rcItem.right - 16 - PEN_RIGHT_SPACE, 
            rcItem.top + (rcItem.Height() - 16)/2, hIcon, 
            16, 16, 0, NULL, DI_NORMAL | DI_COMPAT);
      }
   }

   dc.Detach();//不分离的话就只能显示一项，其他的要点击后才出来  
}

void CListBoxHover::MeasureItem(LPMEASUREITEMSTRUCT)
{

}

void CListBoxHover::OnMouseMove(UINT nFlags, CPoint point)
{
   // TODO: 在此添加消息处理程序代码和/或调用默认值

   if (m_bIsMouseTrack)     // 若允许 追踪，则。 
   {
      TRACKMOUSEEVENT csTME;
      csTME.cbSize       = sizeof (csTME);
      csTME.dwFlags      = TME_LEAVE|TME_HOVER;
      csTME.hwndTrack    = m_hWnd ;                 // 指定要 追踪 的窗口 
      csTME.dwHoverTime  = 50;                      // 鼠标在按钮上停留超过 10ms ，才认为状态为 HOVER
      ::_TrackMouseEvent (&csTME);                  // 开启 Windows 的 WM_MOUSELEAVE ， WM_MOUSEHOVER 事件支持

      m_bIsMouseTrack = FALSE ;                     // 若已经 追踪 ，则停止 追踪 
   }

   CPoint Point;
   GetCursorPos(&Point); //取得当前鼠标的坐标
   if (::WindowFromPoint(Point) == GetSafeHwnd()) //从当前鼠标的坐标获得鼠标所在窗口的句柄，并判断是否为LISTBOX控件 
   {
      ScreenToClient(&Point); //由 于GetCursorPos函数返回的是相对于整个屏幕的坐标值，因此需要把这个坐标值转换成相对于ListBox 的坐标.
      BOOL bOutSide;
      int nNindex = ItemFromPoint(Point, bOutSide);//从鼠标坐标获得鼠标目前所在的LISTBOX项目索引

      if (!bOutSide)
      {
         if(nNindex >= 0 /* &&  nNindex < m_pCtrlInfo->GetCount()*/)
         {
            CRect PenRect = GetPenRectByItemIndex(nNindex);
            CRect PenRectInflate = PenRect;
            PenRectInflate.InflateRect(PEN_RIGHT_SPACE, PEN_RIGHT_SPACE);
            BOOL bPenHeight = PenRectInflate.PtInRect(Point);

            SetHoverIndex(nNindex, bPenHeight, PenRect);
         }
         else
         {
            ClearHoverIndex();
         }
      }
      else
      {
         ClearHoverIndex();
      }
   }
   else
   {
      ClearHoverIndex();
   }

   CListBox::OnMouseMove(nFlags, point);
}

LRESULT CListBoxHover::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
   //m_bIsInRect          = FALSE;
   m_bIsMouseTrack      = TRUE;
   m_bIsPressed         = FALSE;
   
   ClearHoverIndex();
   return 0;
}// end: OnMouseLeave

BOOL CListBoxHover::ClearHoverIndex()
{
   if(m_nHoverIndex != enClearHoverIndex)
   {
      CRect Rect;
      GetItemRect(m_nHoverIndex, &Rect);
      m_nHoverIndex = enClearHoverIndex;
      m_bPenHeight = FALSE;
      InvalidateRect(&Rect);
      return TRUE;
   }
   return FALSE;
}

BOOL CListBoxHover::SetHoverIndex(int nIndex, BOOL bPenHeight, const CRect &PenRect)
{
   if(m_nHoverIndex != nIndex)
   {
      int nHoverIndexOld = m_nHoverIndex;

      m_nHoverIndex = nIndex;
      m_bPenHeight = bPenHeight;

      if (nHoverIndexOld != enClearHoverIndex)
      { //原高亮取消
         CRect Rect;
         GetItemRect(nHoverIndexOld, &Rect);
         InvalidateRect(&Rect);
      }

      CRect RectNew;
      GetItemRect(nIndex, &RectNew);
      InvalidateRect(&RectNew);
      return TRUE;
   }
   if (m_bPenHeight != bPenHeight)
   {
      m_bPenHeight = bPenHeight;
      InvalidateRect(PenRect);
   }
   return FALSE;
}

CRect CListBoxHover::GetPenRectByItemIndex(int nIndex)
{
   CRect rcItem;
   GetItemRect(m_nHoverIndex, &rcItem);
   CRect PenRect(0, 0, 16, 16);
   PenRect.MoveToXY(rcItem.right - 16 - PEN_RIGHT_SPACE, rcItem.top + (rcItem.Height() - 16)/2);
   return PenRect;
}

void CListBoxHover::OnLButtonDown(UINT nFlags, CPoint point)
{
   if (m_nHoverIndex != enClearHoverIndex)
   {
      CRect PenRect = GetPenRectByItemIndex(m_nHoverIndex);
      CRect PenRectInflate = PenRect;
      PenRectInflate.InflateRect(PEN_RIGHT_SPACE, PEN_RIGHT_SPACE);
      if (PenRectInflate.PtInRect(point))
      {
         if (m_funcEditItem)
         {
            m_funcEditItem(m_nHoverIndex);
         }
         return;
      }
   }

   CListBox::OnLButtonDown(nFlags, point);
}

CListBoxHover::~CListBoxHover()
{
   if (m_hIconNormal)
   {
      ::DestroyIcon(m_hIconNormal);
      m_hIconNormal = 0;
   }

   if (m_hIconHighlight)
   {
      ::DestroyIcon(m_hIconHighlight);
      m_hIconHighlight = 0;
   }
}