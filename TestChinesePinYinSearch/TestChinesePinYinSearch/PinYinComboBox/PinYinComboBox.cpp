#include "stdafx.h"
#include "PinYinComboBox.h"
#include "PinYinComboBoxDlg.h"

BEGIN_MESSAGE_MAP(CPinYinComboBox, CMFCEditBrowseCtrl)
   ON_CONTROL_REFLECT_EX(EN_CHANGE, &CPinYinComboBox::OnEditchange)
   ON_WM_CTLCOLOR_REFLECT()
   ON_WM_CHAR()
   ON_WM_TIMER()
END_MESSAGE_MAP()

CPinYinComboBox::CPinYinComboBox()
{
}

IMPLEMENT_DYNCREATE(CPinYinComboBox, CMFCEditBrowseCtrl)

void CPinYinComboBox::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
   CMFCEditBrowseCtrl::OnChar(nChar, nRepCnt, nFlags);
   //ShowDropDown(TRUE);
   KillTimer(1);
   SetTimer(1, 100, NULL); //输入法输入的文字是一个一个出来的，所以要用定时器，最后一起ShowDropDown
}

void CPinYinComboBox::Init()
{
   EnableBrowseButton(TRUE); //▽

   auto hbmp = CPinYinComboBoxDlg::GetButtonBitmap();
   
   SetBrowseButtonImage(hbmp, FALSE);
   SetMaxCount(20);
}

void CPinYinComboBox::SetMaxCount(int nMaxCount)
{
   auto spDlg = GetDropdownDlg();
   spDlg->SetMaxCount(nMaxCount);
}

HBRUSH CPinYinComboBox::CtlColor(CDC* pDC, UINT nCtlColor) 
{
   // TODO: Change any attributes of the DC here
   CClientDC dc(this); //获取画布对象
   CRect rect;
   GetClientRect(rect); //获取客户区域
   rect.InflateRect(1,1,1,1);//将客户区域增大一个像素


   CBrush brush(RGB(255,255,255));//创建画刷
   dc.FrameRect(rect,&brush);//绘制边框

   CBrush brush2(RGB(171,193,222));//创建画刷
   rect.InflateRect(1,1,1,1);//将客户区域增大一个像素
   dc.FrameRect(rect,&brush2);//绘制边框

   GetWindowRect(rect);
   ScreenToClient(&rect);
   dc.FrameRect(rect, &brush2);

   // TODO: Return a non-NULL brush if the parent's handler should not be called
   return NULL;
}

void CPinYinComboBox::AddString(LPCTSTR lpszString)
{
   auto sp = GetDropdownDlg();
   sp->AddString(lpszString);
}

void CPinYinComboBox::ResetContent()
{
   auto sp = GetDropdownDlg();
   sp->ResetContent();
}

int CPinYinComboBox::GetCount() const
{
   if (!m_spDropdownDlg)
      return 0;
   return m_spDropdownDlg->GetCount();
}

void CPinYinComboBox::GetLBText(int nIndex, CString &rString) const
{
   if (!m_spDropdownDlg)
      return;
   m_spDropdownDlg->GetLBText(nIndex, rString);
}

int CPinYinComboBox::DeleteString(UINT nIndex)
{
   auto sp = GetDropdownDlg();
   return sp->DeleteString(nIndex);
}

void CPinYinComboBox::OnBrowse()
{
   ShowDropDown(FALSE);
}

std::shared_ptr<CPinYinComboBoxDlg> CPinYinComboBox::GetDropdownDlg()
{
   if (m_spDropdownDlg)
   {
      return m_spDropdownDlg;
   }

   m_spDropdownDlg.reset(new CPinYinComboBoxDlg);
   auto *pFont = GetFont();
   if (pFont)
   {
      LOGFONT LGFont;
      memset(&LGFont, 0, sizeof(LGFont));
      pFont->GetLogFont(&LGFont);
      m_spDropdownDlg->SetEditFont(LGFont);
   }

   m_spDropdownDlg->m_funcSelString = [this](const CString &sSelString)
   {
      if (m_funcSelChange)
         m_funcSelChange(sSelString);
   };

   m_spDropdownDlg->m_funcEditChange = [this](const CString &sNewString)
   {
      this->SetWindowText(sNewString);
   };

   m_spDropdownDlg->m_funcOnHide = [this](const CString &sNewText, int nEditSelStart, int nEditSelEnd)
   {
      this->SetWindowText(sNewText);
      this->SetSel(nEditSelStart, nEditSelEnd);
      this->SetFocus(); //SetFocus也会导致EnChange
   };

   m_spDropdownDlg->m_funcDeleteString = [this](const CString &sText)
   {
      if (m_funcDeleteString)
      {
         m_funcDeleteString(sText);
      }
   };

   m_spDropdownDlg->m_funcDeleteStringCheck = [this](const CString &sText)->BOOL
   {
      if (m_funcDeleteStringCheck)
      {
         return m_funcDeleteStringCheck(sText);
      }
      return TRUE;
   };

   return m_spDropdownDlg;
}

BOOL CPinYinComboBox::PreTranslateMessage(MSG* pMsg)
{
   //BOOL bVirtualKey = FALSE;
   //KEYDOWN
   if (pMsg->message == WM_KEYDOWN)
   {
/*      if (pMsg->wParam == VK_PROCESSKEY)  
      {  
         bVirtualKey = TRUE;
      }
      else */if (pMsg->wParam == VK_UP)
      {
         auto spDlg = GetDropdownDlg();
         CString sEdit;
         GetWindowText(sEdit);
         CString sResult = spDlg->GetPreviousString(sEdit);
         if (sEdit != sResult)
         {
            SetWindowText(sResult);
            SetSel(0, -1);
         }
         return TRUE;
      }
      else if (pMsg->wParam == VK_DOWN)
      {
         auto spDlg = GetDropdownDlg();
         CString sEdit;
         GetWindowText(sEdit);
         CString sResult = spDlg->GetNextString(sEdit);
         if (sEdit != sResult)
         {
            SetWindowText(sResult);
            SetSel(0, -1);
         }
         return TRUE;
      }
   }

   BOOL bRet = CMFCEditBrowseCtrl::PreTranslateMessage(pMsg);
//    if (bVirtualKey)
//    {
//       ShowDropDown(TRUE);
//    }
   return bRet;
}

void CPinYinComboBox::OnTimer(UINT_PTR nIDEvent)
{
   // TODO: Add your message handler code here and/or call default
   if (nIDEvent == 1)
   {
      KillTimer(1);
      ShowDropDown(TRUE);
   }

   CMFCEditBrowseCtrl::OnTimer(nIDEvent);
}

BOOL CPinYinComboBox::OnEditchange()
{
   if (m_funcEditChange)
   {
      CString sText;
      GetWindowText(sText);
      m_funcEditChange(sText);
   }

   return FALSE;
}

BOOL CPinYinComboBox::ShowDropDown(BOOL bInitalFilter)
{
   std::shared_ptr<CPinYinComboBoxDlg> spDropdown = GetDropdownDlg();
   if (!spDropdown->GetSafeHwnd())
      spDropdown->CreateDlgIndirect(this);
   CRect BtnRect;
   GetWindowRect(&BtnRect);

   CString sEditText;
   GetWindowText(sEditText);
   int nEditSelStart = 0;
   int nEditSelEnd = 0;
   GetSel(nEditSelStart, nEditSelEnd);

   int nShowCount = spDropdown->Init(BtnRect, sEditText, nEditSelStart, nEditSelEnd, bInitalFilter);

   if (nShowCount > 0)
      spDropdown->ShowWindow(SW_SHOW);
   else
      SetFocus();

   return TRUE;
}