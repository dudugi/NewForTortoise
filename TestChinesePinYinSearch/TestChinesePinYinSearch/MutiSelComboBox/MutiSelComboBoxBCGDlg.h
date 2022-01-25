#pragma once
#include "MutiSelComboBoxListBCG.h"
#include <vector>
#include <afxeditbrowsectrl.h>
#include <afxdialogex.h>

class CMyBCGEditBrowseCtrl:public CMFCEditBrowseCtrl
{
   BOOL OnEditchange();
   virtual void OnBrowse() override;
   afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
   void OnKillFocus(CWnd* pNewWnd);
   DECLARE_MESSAGE_MAP()
public:
   void ShowScrollBarIfNecessary();
   std::function<void(void)> m_funcOnBrowse;
   std::function<void(CWnd *)> m_funcOnKillFocus;
};

class CMutiSelComboBoxBCGDlg: public CDialogEx
{
public:
   DECLARE_MESSAGE_MAP()
public:
   DECLARE_DYNCREATE(CMutiSelComboBoxBCGDlg)
public:
   CMutiSelComboBoxBCGDlg();
   BOOL CreateDlgIndirect(CWnd* pParent, int nStyle, int nListItemHeight, BOOL bChildWindow);
   void SetAutoHide(BOOL bHide);
   void SetEditFont(const LOGFONT &LogFont){if (!m_EditFont.GetSafeHandle()) m_EditFont.CreateFontIndirect(&LogFont);}
   //返回值：下拉过滤后显示的item个数
   int Init(const CRect &Rect, const CString &sEditText, int nEditSelStart, int nEditSelEnd, BOOL bInitialFilter, BOOL bShowBrowserButton, const CRect &RectParent);
   std::function<void(const CString &sNewText)> m_funcSelString;
   std::function<void(const CString &sNewText)> m_funcEditChange;
   std::function<void(const CString &sNewText, int nEditSelStart, int nEditSelEnd, UINT message, WPARAM wParam)> m_funcOnHide;
   std::function<BOOL(const CString &sText)> m_funcDeleteStringCheck;
   std::function<void(const CString &sNewText)> m_funcReturn;
   std::function<void(CWnd *)> m_funcKillFocus;
   CString GetPreviousString(const CString &sOrgText);
   CString GetNextString(const CString &sOrgText);
   void AddString(LPCTSTR lpszString);//添加item
   void GetLBText(int nIndex, CString &rString);
   int DeleteString(UINT nIndex);
   void ResetContent();
   int GetCount() const;
   void GetLBText(int nIndex, CString &rString) const;
   static HBITMAP GetButtonBitmap();
   std::function<void(const CString &sText)> m_funcDeleteString;
   void SetMaxCount(int nMaxCount){m_nMaxCount = nMaxCount;}
   void NewPutChar(WPARAM nChar);
   void OnKillFocus(CWnd* pNewWnd);
protected:
   CMyBCGEditBrowseCtrl m_editSearch;
private:
   struct ComboItem
   {
      CString m_sOrg;
      CString m_sPinYin;
      CString m_sShortHand;
   };
   BOOL ChangeDropDownContents(const std::vector<CString> &vecContents);
   virtual BOOL OnInitDialog() override;
   virtual void DoDataExchange(CDataExchange* pDX) override;    // DDX/DDV 支持
   afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
   afx_msg void OnLbnSelchangeListContent();
   afx_msg void OnEnChangeEditSearch();
   afx_msg void OnCbnCommandEditchange();
   afx_msg void OnCbnCommandEditComposing();

   virtual BOOL PreTranslateMessage(MSG* pMsg) override;
   BOOL Filter(const CString &sInputText, const std::vector<ComboItem> &vecTotalContents, std::vector<CString> *pvecResultContents);
   BOOL FilterWithImm(const CString &sInputText, const CString &sImmString, const std::vector<ComboItem> &vecTotalContents, std::vector<CString> *pvecResultContents);
   CString GetImmStringFromEdit();
   CMutiSelComboBoxListBCG m_lstBox;
   CFont m_ListFont;
   CFont m_EditFont;
   CRect m_EditRect;
   BOOL m_bDisableEnChangeEvent;
   std::vector<ComboItem> m_vecContents;
   BOOL m_bHided;
   int m_nMaxCount; //客户端设置的最大同时显示条数
   int m_nTmpMaxCount; //受屏幕空间限制的最大同时显示条数，小于m_nMaxCount
   BOOL m_bDropUp;
   int m_nListItemHeight;
   BOOL m_bAutoHide;
   static WNDPROC m_oldEditProc;
   static LRESULT MyEditProc(HWND hWnd,  UINT message, WPARAM wParam, LPARAM lParam );
   virtual void OnCancel() override{return;}
   afx_msg void OnSetFocus( CWnd* );
};