#pragma once
#include "MyCtrlEx\TabDlg\TabDialog.h"
#include "Directory.h"
#include "FileTxt.h"


// CDlgPane2Item1 对话框

class CDlgPane2Item1 : public CTabDialog
{
	DECLARE_DYNAMIC(CDlgPane2Item1)

public:
	CDlgPane2Item1(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgPane2Item1();
	CDirectory m_CDirectroy;

public:
	BOOL CreateDatabase();
	BOOL CreateTablesFromFile(CString strFilePath);
	void RefreshFileList(CString strDir);
// 对话框数据
	enum { IDD = IDD_DLG_PANE2_ITEM1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedInstallDatabaseButton();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnInstall();

private:
	CListBox m_listBox;
	CStringList m_strList;
	CFileTxt m_FileTxt;
	/*CString m_strDatabase;*/
};
