#pragma once
#include "BCGPDialog.h"
#include "DBUserInfo.h"
#include "Resource.h"
// CStaffModifyDlg �Ի���
#define STAFF_TYPE_MODIFY	0
#define STAFF_TYPE_ADD	1

#define STAFFMODIFY_TYPE_EXIT	0
#define STAFFMODIFY_TYPE_SAVE	1
class CDBUserInfoData;
class CDlgStaffModify : public CBCGPDialog
{
	DECLARE_DYNAMIC(CDlgStaffModify)

public:
	CDlgStaffModify(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgStaffModify();

// �Ի�������
	enum { IDD = IDD_DLG_STAFFMODIFY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

private:
	CDBUserInfoData *m_pObjPerson;
	BOOL m_bShow;
   int m_wpData;
   CString m_strDlgTitle;
private:
	void ResizeCtrl(CRect rt);
	void ResetCtrl();
public:
	virtual BOOL OnInitDialog();
	void SetModifyMode(int nMode,CDBUserInfoData * pData = NULL)
	{
		m_wpData = nMode;
		m_pObjPerson = pData;
	}	

	void RefreshData();		//ˢ�½�����Ϣ
	void MyShowWindow(BOOL bShow);  
	BOOL GetMyShowFlag()
	{
		return m_bShow;
	}
	
protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
