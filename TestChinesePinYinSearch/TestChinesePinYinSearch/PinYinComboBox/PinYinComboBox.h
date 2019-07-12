#include <afxeditbrowsectrl.h>
#include <vector>
#include <memory>
#include <functional>

class CPinYinComboBoxDlg;
class CPinYinComboBox:public CMFCEditBrowseCtrl
{
   DECLARE_MESSAGE_MAP()
public:
   CPinYinComboBox();
   void AddString(LPCTSTR lpszString);//Ìí¼Óitem
   int DeleteString(UINT nIndex);
   void ResetContent();
   int GetCount() const;
   void GetLBText(int nIndex, CString &rString) const;
   std::function<void(const CString &sText)> m_funcDeleteString;
   std::function<void(const CString &sText)> m_funcEditChange;
   std::function<void(const CString &sText)> m_funcSelChange;
   std::function<BOOL(const CString &sText)> m_funcDeleteStringCheck;
   void Init();
   void SetMaxCount(int nMaxCount);
private:
   virtual void OnBrowse() override;
   std::shared_ptr<CPinYinComboBoxDlg> GetDropdownDlg();
   afx_msg BOOL OnEditchange();
   BOOL ShowDropDown(BOOL bInitalFilter);
   virtual BOOL PreTranslateMessage(MSG* pMsg) override;
   afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
   void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
   std::shared_ptr<CPinYinComboBoxDlg> m_spDropdownDlg;
   void OnTimer(UINT_PTR nIDEvent);
};