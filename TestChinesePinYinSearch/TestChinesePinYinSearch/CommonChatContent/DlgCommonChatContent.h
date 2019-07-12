#pragma once
#include "afxwin.h"
#include <functional>
#include <deque>
#include "ListBoxHover.h"
#include "..\Bubble\MyBubble.h"


// dlg1 对话框

class CDlgCommonChatContent : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgCommonChatContent)

public:
	CDlgCommonChatContent(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgCommonChatContent();

// 对话框数据

   std::function<void(const CString &sText)> m_funcOutputText;
   std::function<void(const CString &sText)> m_funcCreateText;
   void SetSettingPath(const CString &sPath);
   BOOL CreateDlgIndirect(CWnd* pParent);
   void Init(int nXLeft = -1, int nYBottom = -1);
protected:
	DECLARE_MESSAGE_MAP()
private:
   CListBoxHover m_lstBox;
   CEdit m_EditFilter;
   enum Status
   {
      SELECT_CONTENT,
      CREATE_CONTENT,
      EDIT_CONTENT,
      DELETE_CONFIRM,
   };
   Status m_eStatus;

   CButton m_btnAdd;
   CButton m_btnReturn;
   CButton m_btnDeleteConfirm;
   CStatic m_staticTitleCreate;
   CFont m_ListFont;
   CFont m_HintFont;
   CFont m_BigHintFont;
   std::deque<CString> m_deqContents;
   CButton m_btnCreateOK;
   CEdit m_editNew;
   CButton m_btnDelete;
   CButton m_btnEditFinish;
   CString m_sEditItemStringOld;
   CMyBubble m_Bubble;
   int m_nXLeft;
   int m_nYBottom;
   CString m_sSettingFilePath;
   void ShowEditWindow(BOOL bNew, const CString &sInitText);
   void TurnBack();
   BOOL WriteFile();
   afx_msg void OnBnClickedBtnReturn();
   afx_msg void OnLbnSelchangeListContent();
   afx_msg void OnEnChangeEditSearch();
   afx_msg void OnBnClickedBtnAdd();
   virtual void OnOK();
   afx_msg void OnBnClickedBtnCreateOk();
   virtual BOOL OnInitDialog();
   afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
   afx_msg BOOL OnEraseBkgnd(CDC* pDC);
   afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
   afx_msg void OnBnClickedBtnEditFinish();
   afx_msg void OnBnClickedBtnDelete();
   afx_msg void OnBnClickedBtnDeleteConfirm();
   virtual BOOL PreTranslateMessage(MSG* pMsg);
};
