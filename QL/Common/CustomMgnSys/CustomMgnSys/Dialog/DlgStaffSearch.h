#pragma once

#include "BCGPDialog.h"
#include "QLBCG/DlgBCGGrid.h"
#include "DBUserInfo.h"

#define ACT_COL_INLISTCTR		2

#define STAFFSEARCH_TYPE_MODIFY	0
#define STAFFSEARCH_TYPE_ADD	1
// CStaffSearchDlg �Ի���
class CDBUserInfoData;
class CDBUserInfoList;
class CDlgBCGGrid;
class CDlgStaffSearch : public CBCGPDialog
{
	DECLARE_DYNAMIC(CDlgStaffSearch)

public:
	CDlgStaffSearch(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgStaffSearch();
	CDBUserInfoData * GetSelectData();

// �Ի�������
	enum { IDD = IDD_DLG_STAFFSEARCH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:	
	CDBUserInfoData *m_pCurSelectData;	
   CDBUserInfoList *m_pUserInfoList;//�û�����
private:
	CString GetXmlLabelString();
	void InitComGridDlg();//��ʼ�����
	void ResizeCtrl(CRect rt);
public:
	void RefrushComGridDlg();

private:
	CDlgBCGGrid*			m_pDlgComGrid;				//�±��ؼ�
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
