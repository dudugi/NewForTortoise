#include "PinYinComboBoxList.h"
#include <vector>
#include <afxeditbrowsectrl.h>

class CMyMFCEditBrowseCtrl:public CMFCEditBrowseCtrl
{
   virtual void OnBrowse() override;
   afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
   DECLARE_MESSAGE_MAP()
public:
   std::function<void(void)> m_funcOnBrowse;
};

class CPinYinComboBoxDlg: public CDialogEx
{
public:
   CPinYinComboBoxDlg();
   BOOL CreateDlgIndirect(CWnd* pParent);
   void SetEditFont(const LOGFONT &LogFont){if (!m_EditFont.GetSafeHandle()) m_EditFont.CreateFontIndirect(&LogFont);}
   //返回值：下拉过滤后显示的item个数
   int Init(const CRect &Rect, const CString &sEditText, int nEditSelStart, int nEditSelEnd, BOOL bInitialFilter);
   std::function<void(const CString &sNewText)> m_funcSelString;
   std::function<void(const CString &sNewText)> m_funcEditChange;
   std::function<void(const CString &sNewText, int nEditSelStart, int nEditSelEnd)> m_funcOnHide;
   std::function<BOOL(const CString &sText)> m_funcDeleteStringCheck;
   CString GetPreviousString(const CString &sOrgText);
   CString GetNextString(const CString &sOrgText);
   void AddString(LPCTSTR lpszString);//添加item
   int DeleteString(UINT nIndex);
   void ResetContent();
   int GetCount() const;
   void GetLBText(int nIndex, CString &rString) const;
   static HBITMAP GetButtonBitmap();
   std::function<void(const CString &sText)> m_funcDeleteString;
   void SetMaxCount(int nMaxCount){m_nMaxCount = nMaxCount;}
protected:
   DECLARE_MESSAGE_MAP()
private:
   struct ComboItem
   {
      CString m_sOrg;
      CString m_sPinYin;
      CString m_sShortHand;
   };
   virtual BOOL OnInitDialog() override;
   virtual void DoDataExchange(CDataExchange* pDX) override;    // DDX/DDV 支持
   afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
   afx_msg void OnLbnSelchangeListContent();
   afx_msg void OnEnChangeEditSearch();
   afx_msg void OnCbnCommandEditchange();
   afx_msg void OnCbnCommandEditComposing();

   virtual BOOL PreTranslateMessage(MSG* pMsg) override;
   BOOL ChangeDropDownContents(const std::vector<CString> &vecContents);
   BOOL Filter(const CString &sInputText, const std::vector<ComboItem> &vecTotalContents, std::vector<CString> *pvecResultContents);
   BOOL FilterWithImm(const CString &sInputText, const CString &sImmString, const std::vector<ComboItem> &vecTotalContents, std::vector<CString> *pvecResultContents);
   CString GetImmStringFromEdit();
   CPinYinComboBoxList m_lstBox;
   CFont m_ListFont;
   CFont m_EditFont;
   CRect m_EditRect;
   BOOL m_bDisableEnChangeEvent;
   CMyMFCEditBrowseCtrl m_editSearch;
   std::vector<ComboItem> m_vecContents;
   BOOL m_bHided;
   int m_nMaxCount; //客户端设置的最大同时显示条数
   int m_nTmpMaxCount; //受屏幕空间限制的最大同时显示条数，小于m_nMaxCount
   BOOL m_bDropUp;
   static WNDPROC m_oldEditProc;
   static LRESULT MyEditProc(HWND hWnd,  UINT message, WPARAM wParam, LPARAM lParam );
};