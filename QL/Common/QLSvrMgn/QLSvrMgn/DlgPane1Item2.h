#pragma once
#include "MyCtrlEx\TabDlg\TabDialog.h"
#include "MyADOConnEx.h"
#include "Directory.h"
#include "afxwin.h"


// CDlgPane1Item2 对话框

class CDlgPane1Item2 : public CTabDialog
{
	DECLARE_DYNAMIC(CDlgPane1Item2)

public:
	CDlgPane1Item2(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgPane1Item2();
	CDirectory m_CDirectroy;
// 对话框数据
	enum { IDD = IDD_DLG_PANE1_ITEM2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRestoreButton();
	afx_msg void OnBnClickedNewPathButton();
	virtual BOOL OnInitDialog();

private:
	//数据库变量
	CMyADOConnEx *m_pADOConn;
/*	CString m_strDatabase;*/
	CStringList m_strList;
	CListBox m_listBox;
	CString m_FileName;
   CDBTaskInfoList m_TaskList;
public:

	/*******************************
	*************
		* @brief：还原数据库
		* @author：zhangyx 2017/12/20
		* @example：
		* @return：
		  **************************
	********************************/
	BOOL RestoreDatabase(const CString &  strDirectory,const CString &  strXDirectory,int nType);

   BOOL RestoreXDatabase(const CString &  strDirectory);
	/**************************************************************************
		* @brief：将文件目录下的文件显示在List Box中
		* @author：zhangyx 2017/12/22
		* @example：
		* @return：
	 **************************************************************************/
	void ShowFileListBox(CString strDirPath);
	afx_msg void OnBnClickedButtonRestore();
	
   BOOL m_RadGroup;
   afx_msg void OnBnClickedRadio1();
   CListBox m_listBox2;
};
