#pragma once

#include <afxwin.h>
#include <map>
#include <afxdd_.h>
#include <functional>

class CPinYinComboBoxList:public CListBox
{

public:
   CPinYinComboBoxList();
   ~CPinYinComboBoxList();
   std::function<void (int nIndex)> m_funcOnClickItemButton;
protected:
   virtual void DrawItem(LPDRAWITEMSTRUCT lpDIS) override;
   virtual void MeasureItem(LPMEASUREITEMSTRUCT) override;
   virtual BOOL SetHoverIndex(int nIndex, BOOL bPenHeight, const CRect &PenRect) ;
   virtual BOOL ClearHoverIndex();
   enum
   {
      enClearHoverIndex = -2
   };
   int  m_nHoverIndex;
   DECLARE_MESSAGE_MAP()
private:
   CRect GetPenRectByItemIndex(int nIndex);

   afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
   afx_msg void OnMouseMove(UINT nFlags, CPoint point);
   void OnLButtonDown(UINT nFlags, CPoint point);

   bool m_bIsPressed;
   BOOL m_bIsMouseTrack;          // Êó±ê×·×Ù
   BOOL m_bPenHeight;
   HICON m_hIconHighlight;
   HICON m_hIconNormal;
};