#include "StdAfx.h"
#include "Lib_ProcessIO.h"
#include "DlgProgressMarquee.h"

CDialogEx * g_pDlgWnd = NULL;

inline void HideAny()
{
   if (NULL != g_pDlgWnd)
   {
      g_pDlgWnd->EndDialog(IDCANCEL);
      //g_pDlgWnd->DestroyWindow();
   }
}

void ShowMarquee()
{
   HideAny();

   CDlgProgressMarquee * pNewPoint = new CDlgProgressMarquee; //cache it

   g_pDlgWnd = pNewPoint;

   g_pDlgWnd->DoModal();
   g_pDlgWnd = NULL;

   ASSERT(NULL != pNewPoint);
   if (NULL != pNewPoint)
   {
      delete pNewPoint;
      pNewPoint = NULL;
   }
}

void HideMarquee()
{
   HideAny();
}
