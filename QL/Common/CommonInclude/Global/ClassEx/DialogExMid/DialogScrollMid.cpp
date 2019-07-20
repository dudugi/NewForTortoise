#include "stdafx.h"
#include "DialogScrollMid.h"

CDialogScrollMid::CDialogScrollMid(UINT nIDD,CWnd* pParent /*=NULL*/)
   : CDialogExMid(nIDD, pParent)
{
   m_pScrollHelper = NULL;
}

CDialogScrollMid::~CDialogScrollMid()
{
   if (NULL != m_pScrollHelper)
   {
      delete m_pScrollHelper;
      m_pScrollHelper = NULL;
   }
}

BEGIN_MESSAGE_MAP(CDialogScrollMid, CDialogExMid)
   ON_WM_SIZE()
   ON_WM_HSCROLL()
   ON_WM_VSCROLL()
   ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

BOOL CDialogScrollMid::OnInitDialog()
{
   CDialogExMid::OnInitDialog();

   m_pScrollHelper = new CScrollHelper;
   m_pScrollHelper->AttachWnd(this);

   return TRUE;
}

void CDialogScrollMid::UpdateDisplaySize(int nWidth,int nHeight)
{
   if (NULL != m_pScrollHelper)
   {
      m_pScrollHelper->SetDisplaySize(nWidth,nHeight);
   }
}

void CDialogScrollMid::PostNcDestroy()
{
   if (NULL != m_pScrollHelper)
   {
      m_pScrollHelper->DetachWnd();
   }
}

BOOL CDialogScrollMid::PreTranslateMessage(MSG* pMsg)
{
   return CDialogExMid::PreTranslateMessage(pMsg);
}

void CDialogScrollMid::OnSize(UINT nType, int cx, int cy)
{
   CDialogExMid::OnSize(nType,cx,cy);
}

void CDialogScrollMid::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
   if (NULL != m_pScrollHelper)
   {
      m_pScrollHelper->OnHScroll(nSBCode, nPos, pScrollBar);
   }
}

void CDialogScrollMid::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
   if (NULL != m_pScrollHelper)
   {
      m_pScrollHelper->OnVScroll(nSBCode, nPos, pScrollBar);
   }
}

BOOL CDialogScrollMid::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
   if (NULL != m_pScrollHelper)
   {
      BOOL wasScrolled = m_pScrollHelper->OnMouseWheel(nFlags, zDelta, pt);

      return wasScrolled;
   }
   else
      return CDialogExMid::OnMouseWheel(nFlags,zDelta,pt);
}

