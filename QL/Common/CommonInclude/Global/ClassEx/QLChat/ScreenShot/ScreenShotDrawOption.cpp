// ScreenShotDrawOption.cpp : 实现文件
//

#include "stdafx.h"
#include "ScreenShotDrawOption.h"
#include "afxdialogex.h"
#include <windowsx.h>

enum
{
   PEN_WIDTH_START_X = 6,
   PEN_WIDTH_START_Y = 6,
   PEN_WIDTH_BTN_WIDTH = 24,
   PEN_WIDTH_BTN_HEIGHT = 24,
   FIRST_PEN_PT_X = PEN_WIDTH_START_X + PEN_WIDTH_BTN_WIDTH / 2,
   FIRST_PEN_PT_Y = PEN_WIDTH_START_Y + PEN_WIDTH_BTN_HEIGHT / 2,
   SECOND_PEN_PT_X = FIRST_PEN_PT_X + PEN_WIDTH_BTN_WIDTH,
   SECOND_PEN_PT_Y = FIRST_PEN_PT_Y,
   THIRD_PEN_PT_X = SECOND_PEN_PT_X + PEN_WIDTH_BTN_WIDTH,
   THIRD_PEN_PT_Y = FIRST_PEN_PT_Y,
   SPLIT_LINE_X = PEN_WIDTH_START_X + PEN_WIDTH_BTN_WIDTH * 3 + 2,
   SPLIT_LINE_Y = 6,
   SPLIT_LINE_Y_END = 32,
   CURRENT_COLOR_RECT_X = SPLIT_LINE_X + 2,
   CURRENT_COLOR_RECT_Y = 6,
   CURRENT_COLOR_RECT_WIDTH = 26,
   CURRENT_COLOR_RECT_HEIGHT = CURRENT_COLOR_RECT_WIDTH,
   PALETTE_START_X = CURRENT_COLOR_RECT_X + CURRENT_COLOR_RECT_WIDTH + 2,
   PALETTE_START_Y = 6,
   PALETTE_WIDTH = 12,
   PALETTE_HEIDGHT = PALETTE_WIDTH,
   PALETTE_INTERVAL_X = 2,
   PALETTE_INTERVAL_Y = 2,
   PALETTE_ROW_COUNT = 2,
   PALETTE_COL_COUNT = 8,
   FONT_SIZE_COUNT = 10,
};

enum
{
   SCREEN_SHOT_IDC_COMBO_FONT_SIZE = 10001,
};

static const int anSizes[FONT_SIZE_COUNT] = {8, 9, 10, 11, 12, 14, 16, 18, 20,
   22};

const static COLORREF PaletteColor[PALETTE_ROW_COUNT][PALETTE_COL_COUNT] = {
   {
      RGB(0, 0, 0), RGB(128, 128, 128), RGB(128, 0, 0), RGB(247, 136, 58),
         RGB(48, 132, 48), RGB(56, 90, 211), RGB(128, 0, 128), RGB(0, 153, 153)
   },
   {
      RGB(255, 255, 255), RGB(192, 192, 192), RGB(251, 56, 56), RGB(255, 255, 0),
         RGB(153, 204, 0), RGB(56, 148, 228), RGB(243, 27, 243), RGB(22, 220, 220)
      }
};

// CScreenShotDrawOption 对话框

IMPLEMENT_DYNAMIC(CScreenShotDrawOption, CWnd)

CScreenShotDrawOption::CScreenShotDrawOption()
	: m_nPenWidth(1),m_curColor(RGB(251, 56, 56)), m_bShowFontSize(FALSE)
{

}

CScreenShotDrawOption::~CScreenShotDrawOption()
{
}

BEGIN_MESSAGE_MAP(CScreenShotDrawOption, CWnd)
   ON_WM_LBUTTONDOWN()
   ON_WM_PAINT()
   ON_CBN_SELCHANGE(SCREEN_SHOT_IDC_COMBO_FONT_SIZE, &CScreenShotDrawOption::OnCbnSelchangeComboFontSize)
   ON_WM_CREATE()
   ON_WM_ERASEBKGND()
   ON_WM_SETCURSOR()
END_MESSAGE_MAP()


// CScreenShotDrawOption 消息处理程序


void CScreenShotDrawOption::OnLButtonDown(UINT nFlags, CPoint point)
{
   // TODO: 在此添加消息处理程序代码和/或调用默认值
   CRect PenWidthRect(PEN_WIDTH_START_X, PEN_WIDTH_START_Y, 
      PEN_WIDTH_START_X + PEN_WIDTH_BTN_WIDTH, PEN_WIDTH_START_Y + PEN_WIDTH_BTN_HEIGHT);
   if (PenWidthRect.PtInRect(point))
   {
      m_nPenWidth = 1;
      Invalidate();
      if (m_funcChangePenWidth)
         m_funcChangePenWidth(m_nPenWidth, m_nPenWidth - 1);
      return;
   }

   PenWidthRect.OffsetRect(CPoint(PEN_WIDTH_BTN_WIDTH, 0));

   if (PenWidthRect.PtInRect(point))
   {
      m_nPenWidth = 2;
      Invalidate();
      if (m_funcChangePenWidth)
         m_funcChangePenWidth(m_nPenWidth, m_nPenWidth - 1);
      return;
   }

   PenWidthRect.OffsetRect(CPoint(PEN_WIDTH_BTN_WIDTH, 0));

   if (PenWidthRect.PtInRect(point))
   {
      m_nPenWidth = 3;
      Invalidate();
      if (m_funcChangePenWidth)
         m_funcChangePenWidth(m_nPenWidth, m_nPenWidth - 1);
      return;
   }


   for (int j = 0; j < PALETTE_ROW_COUNT; ++j)
   {
      for (int i = 0; i < PALETTE_COL_COUNT; ++i)
      {
         CRect Rect(PALETTE_START_X + i * (PALETTE_WIDTH + PALETTE_INTERVAL_X), 
            PALETTE_START_Y + j * (PALETTE_HEIDGHT + PALETTE_INTERVAL_Y), 
            PALETTE_START_X + i * (PALETTE_WIDTH + PALETTE_INTERVAL_X) + PALETTE_WIDTH, 
            PALETTE_START_Y + j * (PALETTE_HEIDGHT + PALETTE_INTERVAL_Y) + PALETTE_HEIDGHT);

         if (Rect.PtInRect(point))
         {
            m_curColor = PaletteColor[j][i];
            InvalidateRect(CRect(CURRENT_COLOR_RECT_X, CURRENT_COLOR_RECT_Y, 
               CURRENT_COLOR_RECT_X + CURRENT_COLOR_RECT_WIDTH, 
               CURRENT_COLOR_RECT_Y + CURRENT_COLOR_RECT_HEIGHT));

            if (m_funcChangeColor)
               m_funcChangeColor(m_curColor, j * PALETTE_COL_COUNT + i);
            return;
         }
      }
   }

   CWnd::OnLButtonDown(nFlags, point);
}


void CScreenShotDrawOption::OnPaint()
{
   CPaintDC dc(this); // device context for painting
   // TODO: 在此处添加消息处理程序代码
   // 不为绘图消息调用 CDialogEx::OnPaint()

   int nSaveDC = dc.SaveDC();

   if (!m_bShowFontSize)
   {
      CPen Pen;
      Pen.CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
      dc.SelectObject(&Pen);
      dc.Ellipse(FIRST_PEN_PT_X, 
         FIRST_PEN_PT_Y, FIRST_PEN_PT_X + 1, FIRST_PEN_PT_Y + 1);

      CPen PenMiddle;
      PenMiddle.CreatePen(PS_SOLID, 5, RGB(0, 0, 255));
      dc.SelectObject(&PenMiddle);
      dc.Ellipse(SECOND_PEN_PT_X, SECOND_PEN_PT_Y, SECOND_PEN_PT_X + 1, SECOND_PEN_PT_Y + 1);

      CPen PenBig;
      PenBig.CreatePen(PS_SOLID, 8, RGB(0, 0, 255));
      dc.SelectObject(&PenBig);
      dc.Ellipse(THIRD_PEN_PT_X, THIRD_PEN_PT_Y, THIRD_PEN_PT_X + 1, THIRD_PEN_PT_Y + 1);

      CPen PenFrame;
      PenFrame.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
      dc.SelectObject(&PenFrame);

      CRect PenWidthRect(PEN_WIDTH_START_X, PEN_WIDTH_START_Y, 
         PEN_WIDTH_START_X + PEN_WIDTH_BTN_WIDTH, PEN_WIDTH_START_Y + PEN_WIDTH_BTN_HEIGHT);
      PenWidthRect.OffsetRect(CPoint((m_nPenWidth - 1) * PEN_WIDTH_BTN_WIDTH, 0));
      dc.SelectObject(GetStockBrush(NULL_BRUSH));

      dc.Rectangle(PenWidthRect);
   }

   CPen PenSplitLine;
   PenSplitLine.CreatePen(PS_SOLID, 1, RGB(192, 192, 192));
   dc.SelectObject(&PenSplitLine);
   dc.MoveTo(SPLIT_LINE_X, SPLIT_LINE_Y);
   dc.LineTo(SPLIT_LINE_X, SPLIT_LINE_Y_END);

   CBrush BrushCurColor;
   BrushCurColor.CreateSolidBrush(m_curColor);
   dc.SelectObject(&BrushCurColor);
   dc.Rectangle(CURRENT_COLOR_RECT_X, CURRENT_COLOR_RECT_Y, 
      CURRENT_COLOR_RECT_X + CURRENT_COLOR_RECT_WIDTH, 
      CURRENT_COLOR_RECT_Y + CURRENT_COLOR_RECT_HEIGHT);

   CBrush PaletteBrush[PALETTE_ROW_COUNT][PALETTE_COL_COUNT];
   CPen PaletteFramePen;
   PaletteFramePen.CreatePen(PS_SOLID, 1, RGB(128, 128, 128));
   dc.SelectObject(&PaletteFramePen);
   for (int j = 0; j < PALETTE_ROW_COUNT; ++j)
   {
      for (int i = 0; i < PALETTE_COL_COUNT; ++i)
      {
         PaletteBrush[j][i].CreateSolidBrush(PaletteColor[j][i]);

         dc.SelectObject(&PaletteBrush[j][i]);
         dc.Rectangle(PALETTE_START_X + i * (PALETTE_WIDTH + PALETTE_INTERVAL_X), 
            PALETTE_START_Y + j * (PALETTE_HEIDGHT + PALETTE_INTERVAL_Y), 
            PALETTE_START_X + i * (PALETTE_WIDTH + PALETTE_INTERVAL_X) + PALETTE_WIDTH, 
            PALETTE_START_Y + j * (PALETTE_HEIDGHT + PALETTE_INTERVAL_Y) + PALETTE_HEIDGHT);
      }
   }

   dc.RestoreDC(nSaveDC);
}

int CScreenShotDrawOption::OnCreate(LPCREATESTRUCT p)
{
   CWnd::OnCreate(p);

   ModifyStyle(0,SS_NOTIFY);

      // TODO:  在此添加额外的初始化
   //10,5,35,77
   m_cboFontSize.Create(WS_CHILD|WS_VISIBLE|WS_VSCROLL|CBS_DROPDOWNLIST, 
      CRect(15, 7, 15 + 52, 7 + 18), this, SCREEN_SHOT_IDC_COMBO_FONT_SIZE);

   CString sSize;
   for (int i = 0; i < FONT_SIZE_COUNT; ++i)
   {
      sSize.Format(_T("%d"), anSizes[i]);
      m_cboFontSize.InsertString(-1, sSize);
   }

   m_cboFontSize.SetCurSel(2);

   return TRUE;
}

void CScreenShotDrawOption::SetShowStatus(BOOL bShowFontSize, int nColorIndex, int nSizeIndex)
{
   m_bShowFontSize = bShowFontSize;
   int j = nColorIndex / PALETTE_COL_COUNT;
   int i = nColorIndex % PALETTE_COL_COUNT;
   if (j >= 0 && j < PALETTE_ROW_COUNT)
   {
      m_curColor = PaletteColor[j][i];
      if (m_funcChangeColor)
         m_funcChangeColor(m_curColor, nColorIndex);
   }

   int nCmdShow = 0;
   if (!bShowFontSize)
   {
      if (nSizeIndex >= 0 && nSizeIndex < 3)
         m_nPenWidth = nSizeIndex + 1;
      nCmdShow = SW_HIDE;
      if (m_funcChangePenWidth)
         m_funcChangePenWidth(m_nPenWidth, nSizeIndex);
   }
   else
   {
      if (nSizeIndex >= 0 && nSizeIndex < m_cboFontSize.GetCount())
      {
         m_cboFontSize.SetCurSel(nSizeIndex);
         if (m_funcSizeChange)
            m_funcSizeChange(anSizes[nSizeIndex], nSizeIndex);
      }
      nCmdShow = SW_SHOW;
   }
   m_cboFontSize.ShowWindow(nCmdShow);
   Invalidate();
}

void CScreenShotDrawOption::OnCbnSelchangeComboFontSize()
{
   int nCurSel = m_cboFontSize.GetCurSel();
   if (nCurSel < 0 || nCurSel >= FONT_SIZE_COUNT)
      return;

   if (m_funcSizeChange)
      m_funcSizeChange(anSizes[nCurSel], nCurSel);
}

BOOL CScreenShotDrawOption::OnEraseBkgnd(CDC* pDC)
{
   CRect Rect;
   GetWindowRect(&Rect);
   CBrush Brush;
   Brush.CreateSolidBrush(RGB(255, 255, 255));
   pDC->SaveDC();
   pDC->SelectObject(&Brush);
   pDC->PatBlt(0, 0, Rect.Width(), Rect.Height(), PATCOPY);
   pDC->RestoreDC(-1);

   return TRUE;
}

BOOL CScreenShotDrawOption::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
   ::SetCursor(::LoadCursor(NULL, IDC_ARROW));
   return TRUE;
}

BOOL CScreenShotDrawOption::MyCreate(HWND hParent)
{
   return CreateEx(0, _T("Static"), _T(""), WS_CHILD, 0, 0, 226, 38, 
      hParent, 0, NULL);
}