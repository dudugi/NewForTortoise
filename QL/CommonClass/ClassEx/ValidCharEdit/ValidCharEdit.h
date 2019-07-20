#pragma once

#include "afxcontrolbarutil.h"

// CValidCharEdit
//该类仅用于扩展CEdit 控件，使其支持用户输入的部分限制字符 wangzl 2017-10-10

class CValidCharEdit : public CEdit
{
	DECLARE_DYNAMIC(CValidCharEdit)

public:
	CValidCharEdit();
	virtual ~CValidCharEdit();

public:
	void SetValidChars(LPCTSTR lpszValid = NULL);
	void SetWindowText(LPCTSTR lpszString);
	virtual BOOL IsMaskedChar(TCHAR chChar, TCHAR chMaskChar) const;

	const CString GetValue() const { return m_str;}
	BOOL SetValue(LPCTSTR lpszString, BOOL bWithDelimiters = TRUE);
private:
	BOOL CheckChar(TCHAR chChar, int nPos);
	BOOL DoUpdate(BOOL bRestoreLastGood = TRUE, int nBeginOld = -1, int nEndOld = -1);
private:
	CString m_str;                  // Initial value
	CString m_strMask;              // The mask string
	CString m_strValid;             // Valid string characters
	BOOL    m_bPasteProcessing;
	BOOL    m_bSetTextProcessing;
protected:
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnPaste(WPARAM, LPARAM);
	afx_msg LRESULT OnSetText(WPARAM, LPARAM);
	afx_msg LRESULT OnGetText(WPARAM, LPARAM);
	afx_msg LRESULT OnGetTextLength(WPARAM, LPARAM);
	afx_msg LRESULT OnInitControl(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
public:
   afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};


