#include "stdafx.h"
#include "MyTransparentRichEdit.h"

#include <afxcmn.h>
#include "richole.h"
#include <windowsx.h>

using namespace std;

BEGIN_MESSAGE_MAP(CMyTransparentRichEdit, CRichEditCtrl)
   ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


afx_msg BOOL CMyTransparentRichEdit::OnEraseBkgnd(CDC* pDC)
{
   CRect Rect;
   GetWindowRect(&Rect);
   CRect RectClient(Rect);
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
      m_funcDrawBackground(Rect, RectClient, pDC);
   }

   return TRUE;
}

CMyTransparentRichEdit::~CMyTransparentRichEdit()
{
}