#pragma once


// CTabDialog 对话框

class CTabDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CTabDialog)

public:
	CTabDialog(UINT nIDD,CWnd* pParent = NULL);
	~CTabDialog(void);
	virtual BOOL Create(UINT nIDTemplate, CWnd* pParentWnd = NULL,WPARAM wpData=0);

private:
	WPARAM m_wpData;//当前对话框需要执行的操作类型


protected:
	afx_msg LRESULT OnGetDefID(WPARAM wParam,LPARAM lParam); 
	DECLARE_MESSAGE_MAP()
};
