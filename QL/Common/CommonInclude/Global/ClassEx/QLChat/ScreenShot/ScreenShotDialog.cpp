// ScreenShotDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "ScreenShotDialog.h"
#include "afxdialogex.h"
#include "..\Utilities\QLChatString.h"
#include "..\Utilities\QLChatImage.h"
#include <imm.h>
#include <windowsx.h>

#pragma comment(lib, "imm32.lib")

// CScreenShotDialog 对话框

const BYTE ANDmaskCursor[] = 
{ 
   0xFF, 0xFF, 0xFF, 0xFF,   // line 1
   0xFF, 0xFF, 0xFF, 0xFF,   // line 2
   0xFF, 0xFF, 0xFF, 0xFF,   // line 3
   0xFF, 0xFF, 0xFF, 0xFF,   // line 4

   0xFF, 0xFF, 0xFF, 0xFF,   // line 5
   0xFF, 0xFF, 0xFF, 0xFF,   // line 6
   0xFF, 0xFF, 0xFF, 0xFF,   // line 7
   0xFF, 0xFF, 0xFF, 0xFF,   // line 8

   0xFF, 0xFF, 0xFF, 0xFF,   // line 9
   0xFF, 0xFF, 0xFF, 0xFF,   // line 10
   0xFF, 0xFF, 0xFF, 0xFF,   // line 11
   0xFF, 0xFF, 0xFF, 0xFF,   // line 12

   0xFF, 0xFF, 0xFF, 0xFF,   // line 13
   0xFF, 0xFF, 0xFF, 0xFF,   // line 14
   0xFF, 0xFF, 0xFF, 0xFF,   // line 15
   0xFF, 0xFF, 0xFF, 0xFF,   // line 16

   0xFF, 0xFF, 0xFF, 0xFF,   // line 17
   0xFF, 0xFF, 0xFF, 0xFF,   // line 18
   0xFF, 0xFF, 0xFF, 0xFF,   // line 19
   0xFF, 0xFF, 0xFF, 0xFF,   // line 20

   0xFF, 0xFF, 0xFF, 0xFF,   // line 21
   0xFF, 0xFF, 0xFF, 0xFF,   // line 22
   0xFF, 0xFF, 0xFF, 0xFF,   // line 23
   0xFF, 0xFF, 0xFF, 0xFF,   // line 24

   0xFF, 0xFF, 0xFF, 0xFF,   // line 25
   0xFF, 0xFF, 0xFF, 0xFF,   // line 26
   0xFF, 0xFF, 0xFF, 0xFF,   // line 27
   0xFF, 0xFF, 0xFF, 0xFF,   // line 28

   0xFF, 0xFF, 0xFF, 0xFF,   // line 29
   0xFF, 0xFF, 0xFF, 0xFF,   // line 30
   0xFF, 0xFF, 0xFF, 0xFF,   // line 31
   0xFF, 0xFF, 0xFF, 0xFF,   // line 32
};

// Yin-shaped cursor XOR mask 

const BYTE XORmaskCursor[] = 
{ 
   0x00, 0x00, 0x00, 0x00,   // line 1
   0x00, 0x00, 0x00, 0x00,   // line 2
   0x00, 0x00, 0x00, 0x00,   // line 3
   0x00, 0x00, 0x00, 0x00,   // line 4

   0x00, 0x00, 0x80, 0x00,   // line 5
   0x00, 0x00, 0x80, 0x00,   // line 6
   0x00, 0x00, 0x80, 0x00,   // line 7
   0x00, 0x00, 0x80, 0x00,   // line 8

   0x00, 0x00, 0x80, 0x00,   // line 9
   0x00, 0x00, 0x80, 0x00,   // line 10
   0x00, 0x00, 0x80, 0x00,   // line 11
   0x00, 0x00, 0x80, 0x00,   // line 12

   0x00, 0x00, 0x80, 0x00,   // line 13
   0x00, 0x03, 0xE0, 0x00,   // line 14
   0x00, 0x02, 0x20, 0x00,   // line 15
   0x0F, 0xFE, 0x3F, 0xF0,   // line 16

   0x00, 0x02, 0x20, 0x00,   // line 17
   0x00, 0x03, 0xE0, 0x00,   // line 18
   0x00, 0x00, 0x80, 0x00,   // line 19
   0x00, 0x00, 0x80, 0x00,   // line 20

   0x00, 0x00, 0x80, 0x00,   // line 21
   0x00, 0x00, 0x80, 0x00,   // line 22
   0x00, 0x00, 0x80, 0x00,   // line 23
   0x00, 0x00, 0x80, 0x00,   // line 24

   0x00, 0x00, 0x80, 0x00,   // line 25
   0x00, 0x00, 0x80, 0x00,   // line 26
   0x00, 0x00, 0x80, 0x00,   // line 27
   0x00, 0x00, 0x00, 0x00,   // line 28

   0x00, 0x00, 0x00, 0x00,   // line 29
   0x00, 0x00, 0x00, 0x00,   // line 30
   0x00, 0x00, 0x00, 0x00,   // line 31
   0x00, 0x00, 0x00, 0x00,   // line 32
};

const CPoint CScreenShotDialog::NULL_POINT(-1, -1);

IMPLEMENT_DYNAMIC(CScreenShotDialog, CDialogEx)

CScreenShotDialog::CScreenShotDialog(IScreenShotSetting *pScreenShotSetting, CWnd* pParent /*=NULL*/)
	: /*CDialogEx(CScreenShotDialog::IDD, pParent),*/
   m_hBitmap(NULL), m_bMemDCPrepared(FALSE), m_hCursorDraw(NULL),
   m_oldRectMouseMovePoint(NULL_POINT),
   m_oldDrawSecondPoint(NULL_POINT),
   m_DrawFirstPoint(NULL_POINT),
   m_eEditStatus(START_UP),
   m_nPenWidth(1),
   m_Color(RGB(251, 56, 56)),
   m_DarkRect(-1, -1, -1, -1),
   m_DrawTextFirstPoint(NULL_POINT),
   m_DrawTextMovePoint(NULL_POINT),
   m_nCurEditIndex(-1),
   m_nFontSize(10),
   m_oldMouseMovePoint(NULL_POINT),
   m_pScreenShotSetting(pScreenShotSetting),
   m_vecTemplate(sizeof(DLGTEMPLATE)/sizeof(WORD), 0)
{
   BOOL bResult=FALSE;
   DLGTEMPLATE *pTemplate = (DLGTEMPLATE *)m_vecTemplate.data();
   pTemplate->style = DS_SETFONT | DS_FIXEDSYS | WS_POPUP | WS_SYSMENU;
   pTemplate->x = 0;
   pTemplate->y = 0;
   pTemplate->cx = 100;
   pTemplate->cy = 100;
   pTemplate->cdit = 0;
   m_vecTemplate.push_back(0); // 菜单
   m_vecTemplate.push_back(0); // class
   m_vecTemplate.push_back(0); // Caption
   InitModalIndirect((DLGTEMPLATE *)m_vecTemplate.data());

   m_hCursorDraw = CreateCursor(AfxGetInstanceHandle(), 16, 15, 32, 32, ANDmaskCursor, XORmaskCursor);
}

CScreenShotDialog::~CScreenShotDialog()
{
   if (m_hBitmap)
   {
      if (DeleteObject(m_hBitmap))
      {
         m_hBitmap = NULL;
      }
   }

   if (m_hCursorDraw)
   {
      if (DestroyCursor(m_hCursorDraw))
      {
         m_hCursorDraw = NULL;
      }
   }
}

void CScreenShotDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CScreenShotDialog, CDialogEx)
   ON_WM_PAINT()
   ON_WM_SETCURSOR()
   ON_WM_MOUSEMOVE()
   ON_WM_LBUTTONDOWN()
   ON_WM_LBUTTONUP()
   ON_WM_RBUTTONDOWN()
   ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CScreenShotDialog 消息处理程序


BOOL CScreenShotDialog::OnInitDialog()
{
   CDialogEx::OnInitDialog();

   // TODO:  在此添加额外的初始化

   int nWidth = GetSystemMetrics ( SM_CXSCREEN ); 
   int nHeight= GetSystemMetrics ( SM_CYSCREEN ); 

   MoveWindow(0, 0, nWidth, nHeight, 1);

   m_ScreenRect = CRect(0, 0, nWidth, nHeight);

   auto funcFinish = [this]()
   {
      PutCurEditOnBitmap();
      SaveFinalBmp(m_SelectedRect);
      OnOK();
   };

   m_ScreenShotBar.m_funFinish = funcFinish;

   auto funcAbort = [this]()
   {
      OnCancel();
   };

   m_ScreenShotBar.m_funAbort = funcAbort;

   auto funcDrawRect = [this]()
   {
      m_eEditStatus = DRAW_RECT;
      PutCurEditOnBitmap();
      ShowDrawOptionDialog(FALSE);
   };

   m_ScreenShotBar.m_funDrawRect = funcDrawRect;

   auto funcDrawArrow = [this]()
   {
      m_eEditStatus = DRAW_ARROW;
      PutCurEditOnBitmap();
      ShowDrawOptionDialog(FALSE);
   };

   m_ScreenShotBar.m_funDrawArrow = funcDrawArrow;

   auto funcDrawEllipse = [this]()
   {
      m_eEditStatus = DRAW_ELLIPSE;
      PutCurEditOnBitmap();
      ShowDrawOptionDialog(FALSE);
   };

   m_ScreenShotBar.m_funDrawEllipse = funcDrawEllipse;

   auto funcDrawText = [this]()
   {
      if (m_eEditStatus == DRAW_TEXT)
         return;
      m_eEditStatus = DRAW_TEXT;
      ShowDrawOptionDialog(TRUE);
   };

   m_ScreenShotBar.m_funDrawText = funcDrawText;

   m_ScreenShotBar.m_funWithdraw = std::bind(&CScreenShotDialog::Withdraw, this);

   m_ScreenShotBar.CreateBarIndirect(this);

   m_ScreenShotBar.GetWindowRect(&m_BarRect);

   auto funcPenWidth = [this](int nWidth, int nSizeIndex)
   {
      m_nPenWidth = nWidth;

      if (m_pScreenShotSetting)
      {
         IScreenShotSetting::ScreenShotToolType eToolType;
         switch (m_eEditStatus)
         {
         case DRAW_RECT:
            eToolType = IScreenShotSetting::SCREEN_SHOT_TOOL_RECT;
            break;
         case DRAW_ELLIPSE:
            eToolType = IScreenShotSetting::SCREEN_SHOT_TOOL_ELLIPSE;
            break;
         case DRAW_TEXT:
            eToolType = IScreenShotSetting::SCREEN_SHOT_TOOL_TEXT;
            break;
         case DRAW_ARROW:
         default:
            eToolType = IScreenShotSetting::SCREEN_SHOT_TOOL_ARROW;
            break;
         }
         m_pScreenShotSetting->SetScreenShotSettingSize(eToolType, nSizeIndex);
      }
   };

   m_ScreenShotDrawOption.m_funcChangePenWidth = funcPenWidth;

   auto funcChangeColor = [this](COLORREF Color, int nColorIndex)
   {
      m_Color = Color;
      if (m_pScreenShotSetting)
      {
         IScreenShotSetting::ScreenShotToolType eToolType;
         switch (m_eEditStatus)
         {
         case DRAW_RECT:
            eToolType = IScreenShotSetting::SCREEN_SHOT_TOOL_RECT;
            break;
         case DRAW_ELLIPSE:
            eToolType = IScreenShotSetting::SCREEN_SHOT_TOOL_ELLIPSE;
            break;
         case DRAW_TEXT:
            eToolType = IScreenShotSetting::SCREEN_SHOT_TOOL_TEXT;
            break;
         case DRAW_ARROW:
         default:
            eToolType = IScreenShotSetting::SCREEN_SHOT_TOOL_ARROW;
            break;
         }
         m_pScreenShotSetting->SetScreenShotSettingColor(eToolType, nColorIndex);
      }

      if (m_nCurEditIndex >= 0 && m_nCurEditIndex < static_cast<int>(m_vecSizeBoxEdit.size()))
         m_vecSizeBoxEdit[m_nCurEditIndex]->SetEditColor(m_Color);
   };

   m_ScreenShotDrawOption.m_funcChangeColor = funcChangeColor;

   auto funcChangeFontSize = [this](int nFontSize, int nSizeIndex)
   {
      m_nFontSize = nFontSize;
      CFont Font;
      CClientDC dc(this);
      int nHeight = dc.GetDeviceCaps(LOGPIXELSY)*nFontSize/72;
      
      if (m_nCurEditIndex >= 0 && m_nCurEditIndex < static_cast<int>(m_vecSizeBoxEdit.size()))
      {
         m_vecSizeBoxEdit[m_nCurEditIndex]->SetEditFontHeight(nHeight);
         m_vecSizeBoxEdit[m_nCurEditIndex]->SetEditColor(m_Color);
      }
      if (m_pScreenShotSetting)
      {
         IScreenShotSetting::ScreenShotToolType eToolType;
         switch (m_eEditStatus)
         {
         case DRAW_RECT:
            eToolType = IScreenShotSetting::SCREEN_SHOT_TOOL_RECT;
            break;
         case DRAW_ELLIPSE:
            eToolType = IScreenShotSetting::SCREEN_SHOT_TOOL_ELLIPSE;
            break;
         case DRAW_TEXT:
            eToolType = IScreenShotSetting::SCREEN_SHOT_TOOL_TEXT;
            break;
         case DRAW_ARROW:
         default:
            eToolType = IScreenShotSetting::SCREEN_SHOT_TOOL_ARROW;
            break;
         }
         m_pScreenShotSetting->SetScreenShotSettingSize(eToolType, nSizeIndex);
      }
   };

   m_ScreenShotDrawOption.m_funcSizeChange = funcChangeFontSize;

   //m_ScreenShotDrawOption.Create(CScreenShotDrawOption::IDD, this);
   m_ScreenShotDrawOption.MyCreate(GetSafeHwnd());

   m_ScreenShotDrawOption.GetWindowRect(&m_DrawOptionRect);

   ShowWindow(SW_SHOW);

   return TRUE;  // return TRUE unless you set the focus to a control
   // 异常: OCX 属性页应返回 FALSE
}

void CScreenShotDialog::ShowDrawOptionDialog(BOOL bShowFont)
{
   int nOptionBarY;

   if (m_BarRect.top > m_SelectedRect.bottom) //如果工具条在选框下方
   {
      nOptionBarY = m_BarRect.bottom + 1;

      if (nOptionBarY + m_DrawOptionRect.Height() > m_ScreenRect.bottom)
      { //主工具条跳到上面去
         int nBarY = m_SelectedRect.top - 1 - m_BarRect.Height();

         if (nBarY < 0)
            nBarY = 0;

         m_ScreenShotBar.SetWindowPos(NULL, m_BarRect.left, nBarY, 0, 0, SWP_NOSIZE|SWP_NOZORDER);
         m_BarRect.MoveToY(nBarY);

         nOptionBarY = m_BarRect.top - m_DrawOptionRect.Height() - 1;
      }
   }
   else
   {
      nOptionBarY = m_BarRect.top - m_DrawOptionRect.Height() - 1;

      if (nOptionBarY < 0)
         nOptionBarY = m_BarRect.bottom + 1;
   }

   IScreenShotSetting::ScreenShotToolType eToolType;
   switch (m_eEditStatus)
   {
   case DRAW_RECT:
      eToolType = IScreenShotSetting::SCREEN_SHOT_TOOL_RECT;
      break;
   case DRAW_ELLIPSE:
      eToolType = IScreenShotSetting::SCREEN_SHOT_TOOL_ELLIPSE;
      break;
   case DRAW_TEXT:
      eToolType = IScreenShotSetting::SCREEN_SHOT_TOOL_TEXT;
      break;
   case DRAW_ARROW:
   default:
      eToolType = IScreenShotSetting::SCREEN_SHOT_TOOL_ARROW;
      break;
   }
   
   int nSize = 0;
   int nColor = 0;
   if (m_pScreenShotSetting)
      m_pScreenShotSetting->GetScreenShotSetting(eToolType, &nSize, &nColor);
   m_ScreenShotDrawOption.SetShowStatus(bShowFont, nColor, nSize);

   m_ScreenShotDrawOption.SetWindowPos(NULL, m_BarRect.left, nOptionBarY, 0, 0, 
      SWP_NOSIZE | SWP_NOZORDER);

   m_ScreenShotDrawOption.ShowWindow(SW_SHOW);
}

CRect CScreenShotDialog::GetTrueRect(const CRect &Rect)
{
   int nLeft = Rect.left;
   int nRight = Rect.right;
   if (nLeft > nRight)
      std::swap(nLeft, nRight);
   ++nRight;
   int nTop = Rect.top;
   int nBottom = Rect.bottom;
   if (nTop > nBottom)
      std::swap(nTop, nBottom);
   ++nBottom;

   return CRect(nLeft, nTop, nRight, nBottom);
}

void CScreenShotDialog::DrawSelectedRect(const CRect &Rect)
{
//    CRect DrawRect = MakeTrueRect(Rect);
// 
//    HGDIOBJ hNullBrush = GetStockObject(NULL_BRUSH);
//    HGDIOBJ hOldBrush = m_memDC.SelectObject(hNullBrush);
//    int nOldRop = m_memDC.SetROP2(R2_NOTXORPEN);
//    m_memDC.Rectangle(&DrawRect);
//    m_memDC.SetROP2(nOldRop);
//    m_memDC.SelectObject(hOldBrush);
// 
//    InvalidateRect(CRect(DrawRect.left, DrawRect.top, DrawRect.right, DrawRect.top + 1));
//    InvalidateRect(CRect(DrawRect.left, DrawRect.bottom - 1, DrawRect.right, DrawRect.bottom));
//    InvalidateRect(CRect(DrawRect.left, DrawRect.top, DrawRect.left + 1, DrawRect.bottom));
//    InvalidateRect(CRect(DrawRect.right - 1, DrawRect.top, DrawRect.right, DrawRect.bottom));
}

BOOL CScreenShotDialog::InvalidateDiffRect(const CRect &RectOld, const CRect &RectNew) //可优化
{
   if (RectOld == CRect(-1,-1,-1,-1))
   {
      InvalidateRect(RectNew);
      return TRUE;
   }
   InvalidateRect(RectOld);
   InvalidateRect(RectNew);
   return TRUE;
}

void CScreenShotDialog::DrawCrossLine(CDC *pDC, const CPoint &pt)
{
   if (!pDC)
      return;
   int nSave = pDC->SaveDC();
   CPen pen;
   pen.CreatePen(PS_DOT, 1, RGB(1, 1, 1));
   pDC->SelectObject(&pen);

   pDC->SetROP2(R2_NOTXORPEN);

   pDC->MoveTo(0, pt.y);
   pDC->LineTo(m_ScreenRect.Width(), pt.y);
   pDC->MoveTo(pt.x, 0);
   pDC->LineTo(pt.x, m_ScreenRect.Height());

   pDC->RestoreDC(nSave);
}

void CScreenShotDialog::OnPaint()
{
   CPaintDC dc(this); // device context for painting
   // TODO: 在此处添加消息处理程序代码
   // 不为绘图消息调用 CDialogEx::OnPaint()
   if (m_eEditStatus == START_UP)
      return;

   int nGrayWidth = m_ScreenRect.Width();
   int nGrayHeight = m_ScreenRect.Height();
   int nXScreen = m_ScreenRect.Width();
   int nYScreen = m_ScreenRect.Height();

   if (!m_GrayDC.GetSafeHdc())
   {
      m_GrayDC.CreateCompatibleDC(&dc);
      CBitmap GrayBitmap;
      GrayBitmap.CreateCompatibleBitmap(&dc, nGrayWidth, nGrayHeight);
      m_GrayDC.SelectObject(&GrayBitmap);
   }

   BLENDFUNCTION blend;
   memset(&blend,0,sizeof(blend));
   blend.BlendOp = AC_SRC_OVER;
   blend.SourceConstantAlpha = 180;//ALPHA_GRAY;//透明度  

   CRect rect(0, 0, 0, 0);

   //if (m_eEditStatus == RECT_FIRST_POINT_SELECTED)
   if (m_eEditStatus != START_UP)
   {
      if (m_oldRectMouseMovePoint != NULL_POINT)
         rect = CRect(m_MouseDownPoint, m_oldRectMouseMovePoint);
   }

   if (rect.left==rect.right||rect.top==rect.bottom)
   {
         dc.AlphaBlend(0, 0, nXScreen, nYScreen,
            &m_GrayDC, 0, 0, nGrayWidth, nGrayHeight, blend);
   }else
   {
      //【除去矩形后，alpha混合其余四个区域都灰化】  
      int x1 = rect.left < rect.right  ? rect.left   : rect.right;
      int y1 = rect.top  < rect.bottom ? rect.top    : rect.bottom;
      int x2 = rect.left < rect.right  ? rect.right  : rect.left;
      int y2 = rect.top  < rect.bottom ? rect.bottom : rect.top;

      if (y1 > 0)
      {
         dc.AlphaBlend(0, 0, nXScreen, y1, &m_GrayDC, 0,0 , nGrayWidth, nGrayHeight, blend);
      }

      if (y2 < nYScreen)
      {
         dc.AlphaBlend(0, y2, nXScreen, nYScreen-y2, &m_GrayDC, 0, 0, nGrayWidth,nGrayHeight, blend);
      }

      if (x1 > 0)
      {
         dc.AlphaBlend(0, y1, x1, y2 - y1, &m_GrayDC, 0, 0, nGrayWidth, nGrayHeight, blend);
      }

      if (x2 < nXScreen)
      {
         dc.AlphaBlend(x2, y1, nXScreen - x2, y2 - y1, &m_GrayDC,0, 0, nGrayWidth, nGrayHeight, blend);
      }
   }

   if ( (m_eEditStatus == DRAW_RECT || m_eEditStatus == DRAW_ELLIPSE)
      && m_DrawFirstPoint != NULL_POINT)
   {
      CRect DrawRect(m_DrawFirstPoint, m_DrawSecondPoint);
      DrawRect = GetTrueRect(DrawRect);

      int nSaveDC = dc.SaveDC();
      HGDIOBJ hNullBrush = GetStockObject(NULL_BRUSH);
      CPen DrawPen(PS_SOLID, m_nPenWidth, m_Color);
      dc.SelectObject(&DrawPen);
      dc.SelectObject(hNullBrush);
      if (m_eEditStatus == DRAW_RECT)
         dc.Rectangle(DrawRect);
      else if (m_eEditStatus == DRAW_ELLIPSE)
         dc.Ellipse(DrawRect);
      dc.RestoreDC(nSaveDC);
   }
   else if (m_eEditStatus == DRAW_ARROW
      && m_DrawFirstPoint != NULL_POINT)
   {
      int nSaveDC = dc.SaveDC();
      CPen DrawPen(PS_SOLID, m_nPenWidth, m_Color);
      dc.SelectObject(&DrawPen);
      dc.MoveTo(m_DrawFirstPoint);
      dc.LineTo(m_DrawSecondPoint);
      CPoint NewPoint1, NewPoint2;
      DrawArrow(m_DrawFirstPoint, m_DrawSecondPoint, &NewPoint1 , &NewPoint2);
      dc.MoveTo(NewPoint1);
      dc.LineTo(m_DrawSecondPoint);
      dc.MoveTo(NewPoint2);
      dc.LineTo(m_DrawSecondPoint);
      dc.RestoreDC(nSaveDC);
   }

   DrawDrawObjects(&dc);
}

static double GetLineLength(int x1, int y1, int x2, int y2)
{
   return sqrt(pow((double)(x1 - x2), 2.0) + pow((double)(y1 - y2), 2.0));
}

void CScreenShotDialog::DrawArrow(const CPoint &BeginPoint, 
   const CPoint &EndPoint, CPoint *pNewPoint1, CPoint *pNewPoint2)
{
   const double FPAI = 3.141592653589793238462643383249901429;
   const double FPAI_DOT_5 = FPAI*0.5;
   const double FPAI_1_DOT_5 = FPAI*1.5;

   CPoint ptBegin = BeginPoint;
   CPoint ptEnd = EndPoint;

   int x1 = ptBegin.x;
   int y1 = ptBegin.y;

   int x2 = ptEnd.x;
   int y2 = ptEnd.y;

   double fArrowAngle = 0;
   double fLineLengthNew = (float)fabs(GetLineLength(x1, y1, x2, y2) + 0.5);

   double fOffsetY = fabs((long double)(y2 - y1));
   double fOffsetX = fabs((long double)(x2 - x1));
   double fSin = 0;
   double fCos = 0;

   int PtArrowBeginX = 0;
   int PtArrowBeginY = 0;

   // 分4个象限进行显示
   if ((x2 >= x1) && (y2 > y1)) {
      // 270 ~ 360度
      fArrowAngle = FPAI_DOT_5 + atan2(1.0, fOffsetX / fOffsetY);
   } else if ((x2 > x1) && (y2 <= y1)) {
      // 0 ~ 90度
      fArrowAngle = FPAI_DOT_5 - atan2(1.0, fOffsetX / fOffsetY);
   } else if ((x2 <= x1) && (y2 < y1)) {
      // 90 ~ 180度
      fArrowAngle = FPAI_1_DOT_5 + atan2(1.0, fOffsetX / fOffsetY);
   } else if ((x2 < x1) && (y2 >= y1)) {
      // 180 ~ 270度
      fArrowAngle = FPAI_1_DOT_5 - atan2(1.0, fOffsetX / fOffsetY);
   }

   fSin = sin(fArrowAngle);
   fCos = cos(fArrowAngle);
   PtArrowBeginX = x1 + (int)(fSin * fLineLengthNew);
   PtArrowBeginY = (int)fabs(fCos * fLineLengthNew - y1);

   if (pNewPoint1)
   {
      pNewPoint1->x = x1 + (int)(fSin * (fLineLengthNew - 10) - fCos * 10.0);
      pNewPoint1->y = (int)fabs(fCos * (fLineLengthNew - 10) - fSin * -10.0 - y1);
   }

   if (pNewPoint2)
   {
      pNewPoint2->x = x1 + (int)(fSin * (fLineLengthNew - 10) + fCos * 10.0);
      pNewPoint2->y = (int)fabs(fCos * (fLineLengthNew - 10) - fSin * 10.0 - y1);
   }
}

void CScreenShotDialog::DrawMultLineText(CDC *pDC, CRect rect, int nRowDis, UINT nFromat, CString strText)
{
   if( strText.GetLength() <= 0 )
      return;

   rect.top += 2;
   rect.left += 1;

   WCHAR* pText = strText.GetBuffer(strText.GetLength());
   int nCount = strText.GetLength();
   CRect rtChar;
   CSize size = pDC->GetTextExtent(pText + 0, 1);
   int nRowHeight = size.cy + nRowDis;
   rtChar.top = rect.top;
   rtChar.left = rect.left;
   rtChar.bottom  = rtChar.top + nRowDis + size.cy;
   rtChar.right  = rtChar.left + size.cx; 
   CString strChar;
   for (int nCharIndex = 0; nCharIndex < nCount; nCharIndex++)
   {
      if( rtChar.right > rect.right )
      {
         rtChar.top = rtChar.bottom;
         rtChar.bottom += nRowHeight;
         size = pDC->GetTextExtent(pText + nCharIndex, 1);
         rtChar.left = rect.left;
         rtChar.right = rtChar.left + size.cx;
         if( rtChar.bottom > rect.bottom )
            break;
      }
      strChar = pText[nCharIndex];
      pDC->DrawText(strChar, rtChar, nFromat);
      size = pDC->GetTextExtent(pText + nCharIndex + 1, 1);

      if (strChar != _T("\r"))
      {
         rtChar.left = rtChar.right;
         rtChar.right += size.cx;
      }
      else
      {
         rtChar.top = rtChar.bottom;
         rtChar.bottom += nRowHeight;
         rtChar.left = rect.left;
         rtChar.right = rtChar.left + size.cx;
         if( rtChar.bottom > rect.bottom )
            break;
      }
   }
}

BOOL CScreenShotDialog::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
   // TODO: 在此添加消息处理程序代码和/或调用默认值
   if (m_eEditStatus == RECT_SELECTED)
      ::SetCursor(::LoadCursor(NULL, IDC_ARROW));
   else if (DRAW_RECT == m_eEditStatus || DRAW_ELLIPSE == m_eEditStatus 
      || DRAW_TEXT == m_eEditStatus || DRAW_ARROW == m_eEditStatus)
   {
      if (m_hCursorDraw)
      {
         ::SetCursor(m_hCursorDraw);
      }
      else
      {
         ::SetCursor(::LoadCursor(NULL, IDC_CROSS));
      }
   }
   else
      ::SetCursor(::LoadCursor(NULL, IDC_CROSS)); 
      
   return TRUE;
}


void CScreenShotDialog::OnMouseMove(UINT nFlags, CPoint point)
{
   // TODO: 在此添加消息处理程序代码和/或调用默认值

   if (m_bMemDCPrepared)
   {
      if (m_eEditStatus == START_UP)
      {
         CPoint ptCursor;
         GetCursorPos(&ptCursor);

         CClientDC dc(this);
         if (m_oldMouseMovePoint != NULL_POINT)
            DrawCrossLine(&dc, m_oldMouseMovePoint);


         CPoint ptCur;
         GetCursorPos(&ptCur);
         DrawCrossLine(&dc, ptCur);
         m_oldMouseMovePoint = ptCur;

      }
      else if (m_eEditStatus == RECT_FIRST_POINT_SELECTED)
      {
         CPoint ptCursor;
         GetCursorPos(&ptCursor);
         CRect oldRect(-1,-1,-1,-1);
         if (m_oldRectMouseMovePoint != NULL_POINT)
         {
            oldRect = CRect(m_MouseDownPoint, m_oldRectMouseMovePoint);
            DrawSelectedRect(oldRect);
         }
         
         CRect newRect(m_MouseDownPoint, ptCursor);
         DrawSelectedRect(newRect);

         InvalidateDiffRect(oldRect, newRect);
         m_oldRectMouseMovePoint = ptCursor;
      }
      else if ((DRAW_RECT == m_eEditStatus || DRAW_ELLIPSE == m_eEditStatus) 
         && (nFlags & MK_LBUTTON) && m_DrawFirstPoint != NULL_POINT)
      {
         if (m_oldDrawSecondPoint != NULL_POINT)
         {
            CRect oldRect = CRect(m_DrawFirstPoint, m_oldDrawSecondPoint);
            oldRect = GetTrueRect(oldRect);
            oldRect.InflateRect(CSize(m_nPenWidth - 1, m_nPenWidth - 1));
            InvalidateRect(oldRect);
         }

         GetCursorPos(&m_DrawSecondPoint);
         CorrectPointInRect(m_SelectedRect, &m_DrawSecondPoint);

         CRect DrawRect(m_DrawFirstPoint, m_DrawSecondPoint);
         m_oldDrawSecondPoint = m_DrawSecondPoint;
         DrawRect = GetTrueRect(DrawRect);
         DrawRect.InflateRect(CSize(m_nPenWidth - 1, m_nPenWidth - 1));
         InvalidateRect(DrawRect);
         return;
      }
      else if (DRAW_ARROW == m_eEditStatus && (nFlags & MK_LBUTTON) && m_DrawFirstPoint != NULL_POINT)
      {
         if (m_oldDrawSecondPoint != NULL_POINT)
         {
            CRect oldRect = CRect(m_DrawFirstPoint, m_oldDrawSecondPoint);
            oldRect = GetTrueRect(oldRect);
            oldRect.InflateRect(CSize(m_nPenWidth - 1, m_nPenWidth - 1));
            InvalidateRect(oldRect);

            CPoint NewPoint1, NewPoint2;
            DrawArrow(m_DrawFirstPoint, m_oldDrawSecondPoint, &NewPoint1 , &NewPoint2);

            CRect DrawRectSmall1(m_oldDrawSecondPoint, NewPoint1);
            DrawRectSmall1 = GetTrueRect(DrawRectSmall1);
            DrawRectSmall1.InflateRect(CSize(m_nPenWidth - 1, m_nPenWidth - 1));
            InvalidateRect(DrawRectSmall1);
            CRect DrawRectSmall2(m_oldDrawSecondPoint, NewPoint2);
            DrawRectSmall2 = GetTrueRect(DrawRectSmall2);
            DrawRectSmall2.InflateRect(CSize(m_nPenWidth - 1, m_nPenWidth - 1));
            InvalidateRect(DrawRectSmall2);
         }

         GetCursorPos(&m_DrawSecondPoint);
         CorrectPointInRect(m_SelectedRect, &m_DrawSecondPoint);

         CRect DrawRect(m_DrawFirstPoint, m_DrawSecondPoint);
         m_oldDrawSecondPoint = m_DrawSecondPoint;
         DrawRect = GetTrueRect(DrawRect);
         DrawRect.InflateRect(CSize(m_nPenWidth - 1, m_nPenWidth - 1));
         InvalidateRect(DrawRect);

         CPoint NewPoint1, NewPoint2;
         DrawArrow(m_DrawFirstPoint, m_DrawSecondPoint, &NewPoint1 , &NewPoint2);

         CRect DrawRectSmall1(m_DrawSecondPoint, NewPoint1);
         DrawRectSmall1 = GetTrueRect(DrawRectSmall1);
         DrawRectSmall1.InflateRect(CSize(m_nPenWidth - 1, m_nPenWidth - 1));
         InvalidateRect(DrawRectSmall1);
         CRect DrawRectSmall2(m_DrawSecondPoint, NewPoint2);
         DrawRectSmall2 = GetTrueRect(DrawRectSmall2);
         DrawRectSmall2.InflateRect(CSize(m_nPenWidth - 1, m_nPenWidth - 1));
         InvalidateRect(DrawRectSmall2);
         return;
      }
      else if (m_eEditStatus == DRAW_TEXT && (nFlags & MK_LBUTTON) && m_DrawTextFirstPoint != NULL_POINT)
      {
         CClientDC dc(this);
         int nSave = dc.SaveDC();
         CPen Pen(PS_DASH, 1, RGB(0, 0, 0));
         dc.SelectObject(&Pen);
         dc.SetROP2(R2_NOTXORPEN);

         if (m_DrawTextMovePoint != NULL_POINT)
         {
            CRect DrawRect(m_DrawTextFirstPoint, m_DrawTextMovePoint);
            DrawRect = GetTrueRect(DrawRect);
            dc.Rectangle(DrawRect);
         }

         m_DrawTextMovePoint = point;
         CorrectPointInRect(m_SelectedRect, &m_DrawTextMovePoint);
         CRect DrawRect(m_DrawTextFirstPoint, m_DrawTextMovePoint);
         
         DrawRect = GetTrueRect(DrawRect);

         dc.Rectangle(DrawRect);
         dc.RestoreDC(nSave);

         TRACE(_T("%d %d %d %d\n"), DrawRect.left, DrawRect.top, DrawRect.Width(), DrawRect.Height());
      }
   }

   //Invalidate();
   CDialogEx::OnMouseMove(nFlags, point);
}

BOOL CScreenShotDialog::CorrectPointInRect(const CRect &Rect, CPoint *pPoint)
{
   ASSERT(pPoint);
   if (!pPoint)
      return FALSE;
   pPoint->x = max(Rect.left, pPoint->x);
   pPoint->y = max(Rect.top, pPoint->y);
   pPoint->x = min(Rect.right - 1, pPoint->x);
   pPoint->y = min(Rect.bottom - 1, pPoint->y);
   return TRUE;
}

void CScreenShotDialog::OnLButtonDown(UINT nFlags, CPoint point)
{
   // TODO: 在此添加消息处理程序代码和/或调用默认值
   if (START_UP == m_eEditStatus)
   {
      CRect Rect;
      GetClientRect(&Rect);

      CClientDC dc(this);
      DrawCrossLine(&dc, m_oldMouseMovePoint);


      Invalidate();

      m_oldMouseMovePoint = NULL_POINT;

      GetCursorPos(&m_MouseDownPoint);
      
      m_eEditStatus = RECT_FIRST_POINT_SELECTED;
   }
   else if (DRAW_RECT == m_eEditStatus || DRAW_ELLIPSE == m_eEditStatus || DRAW_ARROW == m_eEditStatus)
   {
      CPoint FirstPoint;
      GetCursorPos(&FirstPoint);
      if (m_SelectedRect.PtInRect(FirstPoint))
      {
         m_DrawFirstPoint = FirstPoint;
      }
      else
      {
         m_DrawFirstPoint = NULL_POINT;
      }
   }
   else if (DRAW_TEXT == m_eEditStatus)
   {
      m_DrawTextMovePoint = NULL_POINT;
      if (m_SelectedRect.PtInRect(point))
      {
         m_DrawTextFirstPoint = point;
      }
      else
      {
         m_DrawTextFirstPoint = NULL_POINT;
      }
   }

   CDialogEx::OnLButtonDown(nFlags, point);
}

BOOL CScreenShotDialog::PutCurEditOnBitmap()
{
   if (m_nCurEditIndex < 0 || m_nCurEditIndex >= static_cast<int>(m_vecSizeBoxEdit.size()))
   {
      return FALSE;
   }

   if (!m_vecSizeBoxEdit[m_nCurEditIndex]->GetSafeHwnd())
   {
      return FALSE;
   }

   CString sText;
   CRect Rect;
   m_vecSizeBoxEdit[m_nCurEditIndex]->GetCurText(&sText, &Rect);

   m_vecSizeBoxEdit[m_nCurEditIndex]->ShowWindow(SW_HIDE);

   if (sText.IsEmpty())
   {
      m_nCurEditIndex = -1;
      return TRUE;
   }
   CDrawObject Obj;
   Obj.m_eDrawType = CDrawObject::TEXT;
   Obj.m_Color = m_Color;
   Obj.m_Rect = Rect;
   Obj.m_nPenWidth = m_nPenWidth;
   Obj.m_sText = sText;
   Obj.m_nFontSize = m_nFontSize;
   m_lstDrawObjects.push_back(Obj);
   m_nCurEditIndex = -1;
   return TRUE;
}

void CScreenShotDialog::OnLButtonUp(UINT nFlags, CPoint point)
{
   // TODO: 在此添加消息处理程序代码和/或调用默认值
   if (m_eEditStatus == RECT_FIRST_POINT_SELECTED && m_oldRectMouseMovePoint != NULL_POINT)
   {
      CRect oldRect(m_MouseDownPoint, m_oldRectMouseMovePoint);

      DrawSelectedRect(oldRect); //还原矩形？

      CRect CurRect(m_MouseDownPoint, point);
      m_SelectedRect = GetTrueRect(CurRect);

//       CRect SelectRectDraw(m_SelectedRect);
//       --SelectRectDraw.bottom;
//       --SelectRectDraw.right;
//       DrawSelectedRect(SelectRectDraw); //画最终矩形

      //SaveFinalBmp(TrueCurRect);

      m_eEditStatus = RECT_SELECTED;

      int nBarY;

      if (m_SelectedRect.bottom + 1 + m_BarRect.Height() > m_ScreenRect.bottom)
      {
         nBarY = m_SelectedRect.top - m_BarRect.Height() - 1;
         if (nBarY < 0)
            nBarY = 0;
      }
      else
      {
         nBarY = m_SelectedRect.bottom + 1;
      }

      int nBarX = m_SelectedRect.right - m_BarRect.Width();

      if (nBarX < 0)
         nBarX = 0;

      m_ScreenShotBar.SetWindowPos(NULL, nBarX, nBarY, 0, 0, 
         SWP_NOSIZE | SWP_NOZORDER);

      m_ScreenShotBar.ShowWindow(SW_SHOW);

      m_BarRect.MoveToXY(nBarX, nBarY);
      return;
   }
   else if ((DRAW_RECT == m_eEditStatus || DRAW_ELLIPSE == m_eEditStatus)
      && m_DrawFirstPoint != NULL_POINT)
   {
      GetCursorPos(&m_DrawSecondPoint);
      CorrectPointInRect(m_SelectedRect, &m_DrawSecondPoint);
      CRect DrawRect(m_DrawFirstPoint, m_DrawSecondPoint);
      DrawRect = GetTrueRect(DrawRect);

      CDrawObject Obj;
      if (DRAW_RECT == m_eEditStatus)
         Obj.m_eDrawType = CDrawObject::RECT;
      else if (DRAW_ELLIPSE == m_eEditStatus)
         Obj.m_eDrawType = CDrawObject::ELLIPSE;
      Obj.m_Color = m_Color;
      Obj.m_Rect = DrawRect;
      Obj.m_nPenWidth = m_nPenWidth;
      m_lstDrawObjects.push_back(Obj);
      m_DrawFirstPoint = NULL_POINT;
      InvalidateRect(DrawRect);
      return;
   }
   else if (DRAW_ARROW == m_eEditStatus && m_DrawFirstPoint != NULL_POINT)
   {
      GetCursorPos(&m_DrawSecondPoint);
      CorrectPointInRect(m_SelectedRect, &m_DrawSecondPoint);
      CRect DrawRect(m_DrawFirstPoint, m_DrawSecondPoint);
      DrawRect = GetTrueRect(DrawRect);

      CPoint NewPoint1, NewPoint2;
      DrawArrow(m_DrawFirstPoint, m_DrawSecondPoint, &NewPoint1 , &NewPoint2);

      CRect DrawRectSmall1(m_DrawSecondPoint, NewPoint1);
      DrawRectSmall1 = GetTrueRect(DrawRectSmall1);

      CRect DrawRectSmall2(m_DrawSecondPoint, NewPoint2);
      DrawRectSmall2 = GetTrueRect(DrawRectSmall2);

      CRect UnionRect;
      UnionRect.UnionRect(&DrawRectSmall1, &DrawRectSmall2);
      CRect UnionRectBig;
      UnionRectBig.UnionRect(&UnionRect, &DrawRect);

      CDrawObject Obj;
      Obj.m_eDrawType = CDrawObject::ARROW;
      Obj.m_Color = m_Color;
      Obj.m_Rect = UnionRectBig;
      Obj.m_StartPoint = m_DrawFirstPoint;
      Obj.m_EndPoint = m_DrawSecondPoint;
      Obj.m_nPenWidth = m_nPenWidth;
      m_lstDrawObjects.push_back(Obj);
      m_DrawFirstPoint = NULL_POINT;
      InvalidateRect(DrawRect);
      return;
   }
   else if (m_eEditStatus == DRAW_TEXT && m_DrawTextFirstPoint != NULL_POINT)
   {
      BOOL bPut = PutCurEditOnBitmap();

      if (bPut && point == m_DrawTextFirstPoint) //如果前次有上图且起始点和结束点相同，则不新建输入框
      {
         return;
      }

      CClientDC dc(this);
      int nSave = dc.SaveDC();
      CPen Pen(PS_DASH, 1, RGB(0, 0, 0));
      dc.SelectObject(&Pen);
      dc.SetROP2(R2_NOTXORPEN);

      if (m_DrawTextMovePoint != NULL_POINT)
      {
         CRect DrawRect(m_DrawTextFirstPoint, m_DrawTextMovePoint);
         DrawRect = GetTrueRect(DrawRect);
         dc.Rectangle(DrawRect);
      }

      dc.RestoreDC(nSave);
      CorrectPointInRect(m_SelectedRect, &point);
      CRect DrawRect(m_DrawTextFirstPoint, point);
      DrawRect = GetTrueRect(DrawRect);

//       m_SizeBoxEdit.MoveWindow(DrawRect);
//       m_SizeBoxEdit.Show();

      std::shared_ptr<CSizeBoxEdit> spNewEdit(new CSizeBoxEdit);

      auto funcNewRect = [this](const CRect &argNewRect, BOOL bDontChangeSize)
      {
         CRect NewRect;

         if (!bDontChangeSize)
         {
            NewRect.IntersectRect(argNewRect, m_SelectedRect);
         }
         else
         {
            NewRect = argNewRect;

            if (NewRect.left < m_SelectedRect.left)
            {
               NewRect.MoveToX(m_SelectedRect.left);
            }

            if (NewRect.top < m_SelectedRect.top)
            {
               NewRect.MoveToY(m_SelectedRect.top);
            }

            if (NewRect.bottom > m_SelectedRect.bottom)
            {
               NewRect.OffsetRect(CPoint(0, m_SelectedRect.bottom - NewRect.bottom));
            }

            if (NewRect.right > m_SelectedRect.right)
            {
               NewRect.OffsetRect(CPoint(m_SelectedRect.right - NewRect.right, 0));
            }
         }

         this->ScreenToClient(&NewRect);

         CClientDC dc(this);
         int nSave = dc.SaveDC();
         CPen Pen(PS_SOLID, 5, RGB(0, 0, 0));

         dc.SelectObject(&Pen);

         dc.SelectObject(GetStockBrush(NULL_BRUSH));

         dc.SetROP2(R2_NOTXORPEN);

         if (m_DarkRect != CRect(-1, -1, -1, -1))
         {
            CRect Rect = m_DarkRect;
            Rect.InflateRect(-3, -3);
            dc.Rectangle(Rect);
         }
         m_DarkRect = NewRect;
         CRect Rect = m_DarkRect;
         Rect.InflateRect(-3, -3);
         dc.Rectangle(Rect);

         dc.RestoreDC(nSave);
      };

      spNewEdit->m_funcOnDragToNewRect = funcNewRect;

      

      auto funcDragOver = [this](CSizeBox *psizeBoxEdit)
      {
         if (m_DarkRect == CRect(-1, -1, -1, -1))
         {
            return;
         }
         CRect Rect(m_DarkRect);
         m_DarkRect = CRect(-1, -1, -1, -1);
         this->InvalidateRect(Rect);
         psizeBoxEdit->MoveWindow(&Rect);
      };

      spNewEdit->m_funcDragOver = funcDragOver;

      auto funcDrawRectBitmap = [this](const CRect &Rect, const CRect &RectInClient, CDC *pTargetDC)
      {
         pTargetDC->BitBlt(RectInClient.left , RectInClient.top, RectInClient.Width(), RectInClient.Height(), &m_memDC, Rect.left, Rect.top, SRCCOPY);
         DrawDrawObjects(pTargetDC, Rect.left, Rect.top);
      };

      spNewEdit->SetEditDrawBackgroundFunc(funcDrawRectBitmap);

      if (DrawRect.Height() < 40)
         DrawRect.bottom = DrawRect.top + 40;
      if (DrawRect.bottom > m_SelectedRect.bottom)
         DrawRect.bottom  = m_SelectedRect.bottom;
      if (DrawRect.Width() < 100)
         DrawRect.right = DrawRect.left + 100;
      if (DrawRect.right > m_SelectedRect.right)
         DrawRect.right  = m_SelectedRect.right;

      int nHeight = dc.GetDeviceCaps(LOGPIXELSY)*m_nFontSize/72;

      spNewEdit->Create(DrawRect.left, DrawRect.top, DrawRect.Width(), DrawRect.Height(), GetSafeHwnd(), _T("6666"));
      spNewEdit->SetEditFontHeight(nHeight);
      spNewEdit->SetEditColor(m_Color);
      spNewEdit->SetBottomY(m_SelectedRect.bottom);
      spNewEdit->Show();

      m_vecSizeBoxEdit.push_back(spNewEdit);

      m_nCurEditIndex = m_vecSizeBoxEdit.size() - 1;
   }

   CDialogEx::OnLButtonUp(nFlags, point);
}

BOOL CScreenShotDialog::DrawDrawObjects(CDC *pDC, int nX/* = 0*/, int nY/* = 0*/)
{
   if (!pDC)
      return FALSE;
   CDC &dc = *pDC;
   //上图
   for (auto Iter = m_lstDrawObjects.begin(); Iter != m_lstDrawObjects.end(); ++Iter)
   {
      if (Iter->m_eDrawType == CDrawObject::DRAW_TYPE_NULL)
         continue;
      int nSaveDC = dc.SaveDC();

      if (CDrawObject::ELLIPSE == Iter->m_eDrawType || CDrawObject::RECT == Iter->m_eDrawType)
      {
         HGDIOBJ hNullBrush = GetStockObject(NULL_BRUSH);
         CPen DrawPen(PS_SOLID, Iter->m_nPenWidth, Iter->m_Color);
         dc.SelectObject(&DrawPen);
         dc.SelectObject(hNullBrush);
         if (Iter->m_eDrawType == CDrawObject::RECT)
         {
            dc.Rectangle(-nX + Iter->m_Rect.left, -nY + Iter->m_Rect.top, 
               -nX + Iter->m_Rect.right, -nY + Iter->m_Rect.bottom);
         }
         else if (Iter->m_eDrawType == CDrawObject::ELLIPSE)
         {
            dc.Ellipse(-nX + Iter->m_Rect.left, -nY + Iter->m_Rect.top, 
               -nX + Iter->m_Rect.right, -nY + Iter->m_Rect.bottom);
         }
      }
      else if (CDrawObject::ARROW == Iter->m_eDrawType)
      {
         CPen DrawPen(PS_SOLID, Iter->m_nPenWidth, Iter->m_Color);
         dc.SelectObject(&DrawPen);
         dc.MoveTo(-nX + Iter->m_StartPoint.x, -nY + Iter->m_StartPoint.y);
         dc.LineTo(-nX + Iter->m_EndPoint.x, -nY + Iter->m_EndPoint.y);
         CPoint NewPoint1, NewPoint2;
         DrawArrow(Iter->m_StartPoint, Iter->m_EndPoint, &NewPoint1 , &NewPoint2);
         dc.MoveTo(-nX + NewPoint1.x, -nY + NewPoint1.y);
         dc.LineTo(-nX + Iter->m_EndPoint.x, -nY + Iter->m_EndPoint.y);
         dc.MoveTo(-nX + NewPoint2.x, -nY + NewPoint2.y);
         dc.LineTo(-nX + Iter->m_EndPoint.x, -nY + Iter->m_EndPoint.y);
      }
      else if (CDrawObject::TEXT == Iter->m_eDrawType)
      {
         CFont Font;
         int nHeight = dc.GetDeviceCaps(LOGPIXELSY)*Iter->m_nFontSize/72;
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
            _T("宋体"));

         dc.SelectObject(&Font);
         dc.SetTextColor(Iter->m_Color);
         dc.SetBkMode(TRANSPARENT);
//          dc.DrawText(Iter->m_sText, Iter->m_sText.GetLength(), 
//             &Iter->m_Rect, DT_TOP | DT_LEFT | DT_WORDBREAK | DT_EDITCONTROL);

         CRect TextRect(Iter->m_Rect);
         TextRect.OffsetRect(-nX, -nY);
         DrawMultLineText(&dc, TextRect, nHeight / 3, 
            DT_TOP | DT_LEFT | DT_WORDBREAK | DT_EDITCONTROL, Iter->m_sText);
      }
      dc.RestoreDC(nSaveDC);
   }
   return TRUE;
}

BOOL CScreenShotDialog::SaveFinalBmp(const CRect &Rect)
{
   CDC memorydc;
   memorydc.CreateCompatibleDC(&m_memDC);
   CBitmap bm;
   bm.CreateCompatibleBitmap(&m_memDC, Rect.Width(), Rect.Height());
   CBitmap *pOldBitmap = memorydc.SelectObject(&bm);

   //上图
   DrawDrawObjects(&m_memDC);

   memorydc.BitBlt(0, 0, Rect.Width(),
      Rect.Height(), &m_memDC, Rect.left, Rect.top, SRCCOPY);
   memorydc.SelectObject(pOldBitmap);

   if (m_sOutputPath.IsEmpty())
   {
      return FALSE;
   }

   CLSID bmpClsid;
   QLChat::GetEncoderClsid(L"image/bmp", &bmpClsid);

   //保存到磁盘上的bmp文件
   Gdiplus::Bitmap bitmap((HBITMAP)bm.m_hObject, NULL);
   bitmap.Save(m_sOutputPath, &bmpClsid, NULL);

   return TRUE;
}

void CScreenShotDialog::OnRButtonDown(UINT nFlags, CPoint point)
{
   // TODO: 在此添加消息处理程序代码和/或调用默认值
   if (m_eEditStatus == START_UP)
   {
      OnCancel();
      return;
   }
   else if (m_eEditStatus == RECT_FIRST_POINT_SELECTED)
   {
      m_eEditStatus = START_UP;
      if (m_oldRectMouseMovePoint != NULL_POINT)
      {
         CRect oldRect(m_MouseDownPoint, m_oldRectMouseMovePoint);
         DrawSelectedRect(oldRect);
         m_oldRectMouseMovePoint = NULL_POINT;
      }
      m_MouseDownPoint = CPoint(0, 0);
   }
}

BOOL CScreenShotDialog::SetJPGOutputPath(const CString &sPath)
{
   //CString sExt = QLChat::GetPathExtUpper(sPath);
   //if (sExt != _T(".JPG") && sExt != _T(".JPEG"))
   //{
   //   return FALSE;
   //}
   m_sOutputPath = sPath;
   return TRUE;
}

BOOL CScreenShotDialog::PreTranslateMessage(MSG* pMsg)
{
   // TODO: 在此添加专用代码和/或调用基类
   WPARAM wParam;
   if (pMsg->wParam == VK_PROCESSKEY)  
   {  
      wParam = ImmGetVirtualKey(pMsg->hwnd);  
   }
   else
   {
      wParam = pMsg->wParam;
   }

   if (pMsg->message == WM_KEYDOWN)
   {
      if (wParam == 'Z' && GetKeyState(VK_CONTROL) < 0)
      {
         Withdraw();
         return TRUE;
      }
      else if (wParam == VK_ESCAPE)
      {
         OnCancel();
         return TRUE;
      }
   }
   return CDialogEx::PreTranslateMessage(pMsg);
}

BOOL CScreenShotDialog::OnEraseBkgnd(CDC* pDC)
{
   // TODO: 在此添加消息处理程序代码和/或调用默认值
   if (!m_hBitmap)
   {
      return CDialogEx::OnEraseBkgnd(pDC);
   }

   if (!m_bMemDCPrepared)
   {
      CDC memorydc;
      m_memDC.CreateCompatibleDC(pDC);
      memorydc.CreateCompatibleDC(pDC);

      CBitmap bm;
      bm.CreateCompatibleBitmap(pDC, m_ScreenRect.Width(), m_ScreenRect.Height());
      m_memDC.SelectObject(&bm);

      //选中
      HGDIOBJ hOld = memorydc.SelectObject((HGDIOBJ)m_hBitmap);  
      //绘制图像

      m_memDC.BitBlt(0, 0, m_ScreenRect.Width(), m_ScreenRect.Height(), &memorydc, 0, 0, SRCCOPY);  
      memorydc.SelectObject(hOld);

      m_bMemDCPrepared = TRUE;
   }

   pDC->BitBlt(0, 0, m_ScreenRect.Width(), m_ScreenRect.Height(), &m_memDC, 0, 0, SRCCOPY);

   return TRUE;
}

void CScreenShotDialog::Withdraw()
{
   if (!m_lstDrawObjects.empty())
   {
      CDrawObject Last = m_lstDrawObjects.back();
      CRect lastRect = Last.m_Rect;
      m_lstDrawObjects.pop_back();
      lastRect.InflateRect(CSize(Last.m_nPenWidth - 1, Last.m_nPenWidth - 1));
      InvalidateRect(lastRect);
   }
}

BOOL CScreenShotDialog::ScreenShot(BOOL bHideWindow, CWnd *pMainWnd, const CString &sOutputPath, IScreenShotSetting *pScreenShotSetting)
{
   if (!pMainWnd)
      return FALSE;

   if (!::IsWindow(pMainWnd->GetSafeHwnd()))
      return FALSE;

   BOOL bRet = FALSE;

   if (bHideWindow)
      pMainWnd->ShowWindow(SW_HIDE);

   CWnd *pDesktop = pMainWnd->GetDesktopWindow();  
   CClientDC DesktopDC(pDesktop);
   CRect re;
   //获取窗口的大小
   pDesktop->GetClientRect(&re);
   CBitmap bmp;
   bmp.CreateCompatibleBitmap(&DesktopDC, re.Width(), re.Height());
   CDC memorydc;
   memorydc.CreateCompatibleDC(&DesktopDC);
   //选中画笔
   CBitmap *pold = memorydc.SelectObject(&bmp);
   //绘制图像
   memorydc.BitBlt(0, 0, re.Width(), re.Height(), &DesktopDC, 0, 0, SRCCOPY);

   memorydc.SelectObject(pold);

   HBITMAP hCSreenBitmap = (HBITMAP)bmp.Detach();
   CScreenShotDialog ShotDlg(pScreenShotSetting);
   ShotDlg.AttachHBitmap(hCSreenBitmap);
   ShotDlg.SetJPGOutputPath(sOutputPath);

   auto ret = ShotDlg.DoModal();

   if (ret == IDOK)
   {
      bRet = TRUE;
   }

   if (bHideWindow)
      pMainWnd->ShowWindow(SW_SHOW);

   return bRet;
}