#pragma once
#include "BCGPDialog.h"
#include "DlgStaffSearch.h"
#include "DlgStaffModify.h"
// CStaffMgnTabDlg 对话框

enum{
	STAFF_MAINTYPE_VIEW = -1,
	STAFF_MAINTYPE_ADD,
	STAFF_MAINTYPE_MODIFY
};
class CDBUserInfoData;
class CDlgStaffMgnTab : public CBCGPDialog
{
	DECLARE_DYNAMIC(CDlgStaffMgnTab)

public:
	CDlgStaffMgnTab(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgStaffMgnTab();

// 对话框数据
	enum { IDD = IDD_DLGTAB_STAFFMGN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()


private:
	CDlgStaffSearch * m_pStaffSearchDlg;
	CDlgStaffModify * m_pStaffModifyDlg;
	int m_nOpenFlag;
private:

	void UpdateBtnState();
   void ResizeCtrl();
   void RefreshSearchData(); 
	void InitStaffSearchDlg();
	void InitStaffModifyDlg(int nMode,CDBUserInfoData *pData = NULL);
	afx_msg LRESULT OnStaffModifyAct(WPARAM wParam,LPARAM lParam);

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnBtnAddStaff();
	afx_msg void OnBtnChangeStaff();
	afx_msg void OnBtnDelStaff();
	afx_msg void OnSize(UINT nType, int cx, int cy);

};
