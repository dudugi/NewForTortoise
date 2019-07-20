#pragma once

#include "BCGPDialog.h"
#include "QLBCG/DlgBCGGrid.h"
#include "DBUserInfo.h"

#define ACT_COL_INLISTCTR		2

#define STAFFSEARCH_TYPE_MODIFY	0
#define STAFFSEARCH_TYPE_ADD	1
// CStaffSearchDlg 对话框
class CDBUserInfoData;
class CDBUserInfoList;
class CDlgBCGGrid;
class CDlgStaffSearch : public CBCGPDialog
{
	DECLARE_DYNAMIC(CDlgStaffSearch)

public:
	CDlgStaffSearch(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgStaffSearch();
	CDBUserInfoData * GetSelectData();

// 对话框数据
	enum { IDD = IDD_DLG_STAFFSEARCH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:	
	CDBUserInfoData *m_pCurSelectData;	
   CDBUserInfoList *m_pUserInfoList;//用户数据
private:
	CString GetXmlLabelString();
	void InitComGridDlg();//初始化表格
	void ResizeCtrl(CRect rt);
public:
	void RefrushComGridDlg();

private:
	CDlgBCGGrid*			m_pDlgComGrid;				//新表格控件
	CString m_strDlgTitle;
	BOOL		m_bShow;	
public:
	virtual BOOL OnInitDialog();
	void MyShowWindow(BOOL bShow);
	BOOL GetMyShowFlag()
	{
		return m_bShow;
	}
	afx_msg void OnBnClickedBtnUserdel();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnDblClickedBCGGrid(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnLClickedBCGGrid(WPARAM wParam, LPARAM lParam);
};
