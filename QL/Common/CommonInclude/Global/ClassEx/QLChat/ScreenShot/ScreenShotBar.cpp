// ScreenShotDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "ScreenShotBar.h"
#include "afxdialogex.h"
#include <afxwin.h>
#include <imm.h>
#include <GdiplusHeaders.h>

using namespace Gdiplus;

enum
{
   SCREEN_SHOT_IDC_BTN_FINISH = 10001,
   SCREEN_SHOT_IDC_BTN_ABORT,
   SCREEN_SHOT_IDC_BTN_WITHDRAW
};

// CScreenShotDialog 对话框

IMPLEMENT_DYNAMIC(CScreenShotBar, CDialogEx)

CScreenShotBar::CScreenShotBar(CWnd* pParent /*=NULL*/)
	: 
   m_nCurBottonIndex(-1), m_vecTemplate(sizeof(DLGTEMPLATE)/sizeof(WORD), 0),
   m_RectRect(6, 0, 6 + 26, 14),
   m_RectEllipse(33, 0, 33 + 26, 14),
   m_RectText(60, 0, 60 + 26, 14),
   m_RectArrow(87, 0, 87 + 26, 14)
{
   DLGTEMPLATE *pTemplate = (DLGTEMPLATE *)m_vecTemplate.data();
   pTemplate->style = /*DS_SETFONT |*/ DS_FIXEDSYS | WS_POPUP | WS_SYSMENU;
   pTemplate->x = 0;
   pTemplate->y = 0;
   pTemplate->cx = 201;
   pTemplate->cy = 14;
   pTemplate->cdit = 0;
   m_vecTemplate.push_back(0); // 菜单
   m_vecTemplate.push_back(0); // class
   m_vecTemplate.push_back(0); // Caption
}

BOOL CScreenShotBar::CreateBarIndirect(CWnd* pParent)
{
   if (GetSafeHwnd())
      return FALSE;
   if (!CreateIndirect((DLGTEMPLATE *)m_vecTemplate.data(), pParent))
      return FALSE;
   MapDialogRect(&m_RectRect);
   MapDialogRect(&m_RectEllipse);
   MapDialogRect(&m_RectText);
   MapDialogRect(&m_RectArrow);
   return TRUE;
}

CScreenShotBar::~CScreenShotBar()
{
}

BEGIN_MESSAGE_MAP(CScreenShotBar, CDialogEx)
   ON_BN_CLICKED(SCREEN_SHOT_IDC_BTN_FINISH, &CScreenShotBar::OnBnClickedBtnFinish)
   ON_BN_CLICKED(SCREEN_SHOT_IDC_BTN_ABORT, &CScreenShotBar::OnBnClickedBtnAbort)
   ON_WM_PAINT()
   ON_WM_LBUTTONDOWN()
   ON_BN_CLICKED(SCREEN_SHOT_IDC_BTN_WITHDRAW, &CScreenShotBar::OnBnClickedBtnWithdraw)
END_MESSAGE_MAP()



void CScreenShotBar::OnBnClickedBtnFinish()
{
   // TODO: 在此添加控件通知处理程序代码
   if (m_funFinish)
      m_funFinish();
}


void CScreenShotBar::OnBnClickedBtnAbort()
{
   // TODO: 在此添加控件通知处理程序代码
   if (m_funAbort)
      m_funAbort();
}


void CScreenShotBar::OnCancel()
{
   // TODO: 在此添加专用代码和/或调用基类
   CDialogEx::OnCancel();
   if (m_funAbort)
      m_funAbort();
}

BOOL CScreenShotBar::OnInitDialog()
{
   CDialogEx::OnInitDialog();

   struct  
   {
      CButton *pButton;
      int nID;
      RECT Rect;
      TCHAR *pszCaption;
      CString sPictureFileName;
   } IDRect[] = {
      {&m_BtnWithDraw, SCREEN_SHOT_IDC_BTN_WITHDRAW, {114, 0, 114 + 22, 14}, _T("撤销"), _T("ScreenShotWithDraw.png")}
      ,{&m_BtnAbort, SCREEN_SHOT_IDC_BTN_ABORT, {141, 0, 141 + 22, 14}, _T("放弃"), _T("ScreenShotAbort.png")}
      ,{&m_BtnFinish, SCREEN_SHOT_IDC_BTN_FINISH, {168, 0, 168 + 22, 14}, _T("完成"), _T("ScreenShotFinish.png")}
      ,{NULL, 0}
   };

   TCHAR path[MAX_PATH] = {0};
   GetModuleFileName(NULL, path, MAX_PATH);  //获取到完整路径 eg：E:\Tools\qq.exe
   CString strExeFullPath = path;
   CString strSalePath = strExeFullPath.Left(strExeFullPath.ReverseFind('\\'));
   CString sBasePath = strSalePath + _T("\\res\\");

   CFont *pFont = GetFont();
   auto *pIDRect = &IDRect[0];
   while (pIDRect->pButton)
   {
      MapDialogRect(&pIDRect->Rect);
      BOOL bRet = pIDRect->pButton->Create(pIDRect->pszCaption, DS_SETFONT, pIDRect->Rect, this, pIDRect->nID);
      if (bRet)
      pIDRect->pButton->SetFont(pFont);

      CString sFullPath = sBasePath + pIDRect->sPictureFileName;
      if (PathFileExists(sFullPath))
      {
         Bitmap bmp1(sFullPath);
         HBITMAP hBitmap= NULL;
         Color clr(0,0,0,0); 
         if (Gdiplus::Ok == bmp1.GetHBITMAP(clr, &hBitmap))
         {
            pIDRect->pButton->SetBitmap(hBitmap);
         }
      }


      pIDRect->pButton->ShowWindow(SW_SHOW);
      ++pIDRect;
   }

   return TRUE;  // return TRUE unless you set the focus to a control
   // 异常: OCX 属性页应返回 FALSE
}


void CScreenShotBar::OnPaint()
{
   CPaintDC dc(this); // device context for painting
   // TODO: 在此处添加消息处理程序代码
   // 不为绘图消息调用 CDialogEx::OnPaint()

   dc.SelectObject(GetFont());
   dc.SetBkMode(TRANSPARENT);

   //dc.DrawText(_T("矩形"), 2, &m_RectRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
   //dc.DrawText(_T("椭圆"), 2, &m_RectEllipse, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
   //dc.DrawText(_T("文字"), 2, &m_RectText, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
   //dc.DrawText(_T("箭头"), 2, &m_RectArrow, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

   //默认图片资源加载
   TCHAR path[MAX_PATH] = {0};
   GetModuleFileName(NULL, path, MAX_PATH);  //获取到完整路径 eg：E:\Tools\qq.exe
   CString strExeFullPath = path;
   CString strSalePath = strExeFullPath.Left(strExeFullPath.ReverseFind('\\'));
   CString sBasePath = strSalePath + _T("\\res\\");

   CString sArrow = sBasePath + _T("ScreenShotArrow.png");
   if (PathFileExists(sArrow))
   {
      CImage defNoPic;
      defNoPic.Load(sArrow);
      int nHeight = defNoPic.GetHeight();
      int nWidth = defNoPic.GetWidth();
      CRect rtNew(0, 0, nWidth, nHeight);
      int nNewX = m_RectArrow.left + (m_RectArrow.Width() - nWidth) / 2;
      int nNewY = m_RectArrow.top + (m_RectArrow.Height() - nHeight) / 2;
      rtNew.MoveToXY(nNewX, nNewY);
      defNoPic.Draw(dc, rtNew);
   }
   else
   {
      dc.DrawText(_T("箭头"), 2, &m_RectArrow, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
   }

   CString sText = sBasePath + _T("ScreenShotText.png");
   if (PathFileExists(sText))
   {
      CImage defNoPic;
      defNoPic.Load(sText);
      int nHeight = defNoPic.GetHeight();
      int nWidth = defNoPic.GetWidth();
      CRect rtNew(0, 0, nWidth, nHeight);
      int nNewX = m_RectText.left + (m_RectText.Width() - nWidth) / 2;
      int nNewY = m_RectText.top + (m_RectText.Height() - nHeight) / 2;
      rtNew.MoveToXY(nNewX, nNewY);
      defNoPic.Draw(dc, rtNew);
   }
   else
   {
      dc.DrawText(_T("文字"), 2, &m_RectText, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
   }

   CString sEllipse = sBasePath + _T("ScreenShotEllipse.png");
   if (PathFileExists(sEllipse))
   {
      CImage defNoPic;
      defNoPic.Load(sEllipse);
      int nHeight = defNoPic.GetHeight();
      int nWidth = defNoPic.GetWidth();
      CRect rtNew(0, 0, nWidth, nHeight);
      int nNewX = m_RectEllipse.left + (m_RectEllipse.Width() - nWidth) / 2;
      int nNewY = m_RectEllipse.top + (m_RectEllipse.Height() - nHeight) / 2;
      rtNew.MoveToXY(nNewX, nNewY);
      defNoPic.Draw(dc, rtNew);
   }
   else
   {
      dc.DrawText(_T("椭圆"), 2, &m_RectEllipse, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
   }

   CString sRect = sBasePath + _T("ScreenShotRect.png");
   if (PathFileExists(sRect))
   {
      CImage defNoPic;
      defNoPic.Load(sRect);
      int nHeight = defNoPic.GetHeight();
      int nWidth = defNoPic.GetWidth();
      CRect rtNew(0, 0, nWidth, nHeight);
      int nNewX = m_RectRect.left + (m_RectRect.Width() - nWidth) / 2;
      int nNewY = m_RectRect.top + (m_RectRect.Height() - nHeight) / 2;
      rtNew.MoveToXY(nNewX, nNewY);
      defNoPic.Draw(dc, rtNew);
   }
   else
   {
      dc.DrawText(_T("矩形"), 2, &m_RectRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
   }
   
   HGDIOBJ hNullBrush = GetStockObject(NULL_BRUSH);

   dc.SelectObject(hNullBrush);

   switch (m_nCurBottonIndex)
   {
   case 0:
      {
         CRect Rect(m_RectRect);
         Rect.InflateRect(-2, -2);
         dc.Rectangle(Rect);
      }
      break;
   case 1:
      {
         CRect Rect(m_RectEllipse);
         Rect.InflateRect(-2, -2);
         dc.Rectangle(Rect);
      }
      break;
   case 2:
      {
         CRect Rect(m_RectText);
         Rect.InflateRect(-2, -2);
         dc.Rectangle(Rect);
      }
      break;
   case 3:
      {
         CRect Rect(m_RectArrow);
         Rect.InflateRect(-2, -2);
         dc.Rectangle(Rect);
      }
      break;
   }
}


void CScreenShotBar::OnLButtonDown(UINT nFlags, CPoint point)
{
   // TODO: 在此添加消息处理程序代码和/或调用默认值

   if (m_RectRect.PtInRect(point))
   {
      m_nCurBottonIndex = 0;
      if (m_funDrawRect)
         m_funDrawRect();
   }
   else if (m_RectEllipse.PtInRect(point))
   {
      m_nCurBottonIndex = 1;
      if (m_funDrawEllipse)
         m_funDrawEllipse();
   }
   else if (m_RectText.PtInRect(point))
   {
      m_nCurBottonIndex = 2;
      if (m_funDrawText)
         m_funDrawText();
   }
   else if (m_RectArrow.PtInRect(point))
   {
      m_nCurBottonIndex = 3;
      if (m_funDrawArrow)
         m_funDrawArrow();
   }

   Invalidate();
}


void CScreenShotBar::OnBnClickedBtnWithdraw()
{
   // TODO: 在此添加控件通知处理程序代码
   if (m_funWithdraw)
      m_funWithdraw();
}



BOOL CScreenShotBar::PreTranslateMessage(MSG* pMsg)
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
         if (m_funWithdraw)
         {
            m_funWithdraw();
            return TRUE;
         }
      }
   }
   return CDialogEx::PreTranslateMessage(pMsg);
}
