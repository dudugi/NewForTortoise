#pragma once
#include "MyCtrlEx\TabDlg\TabDialog.h"
#include "FileTxt.h"
#include "Directory.h"
#include "MyADOConnEx.h"
#include "DBDatabaseFields.h"
#include "DlgTask.h"
#include "afxwin.h"
using namespace std;


// CDlgPane1item1 对话框

class CDlgPane1Item1 : public CTabDialog
{
	DECLARE_DYNAMIC(CDlgPane1Item1)

private:
	/*CString m_strDatabase;*/
	//数据库变量
	CMyADOConnEx *m_pADOConn;
	CDirectory m_CDirectroy;
	CDBDatabaseTableList m_DBDatabaseTableList;  //存储本地数据库信息链
   BOOL m_bStopCy; //停止备份标志
   BOOL m_bWait;   //等待备份标志
   int m_nCtlIDM[12]; //check月组件ID
   int m_nCtlIDR[30]; //check日组件ID
   int m_nImmediately;

   CDlgTask *m_pDlgTask; 
public:
	
	CDlgPane1Item1(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgPane1Item1();

	/*******************************
	*************
		* @brief：备份数据库(整体备份)
		* @author：zhangyx 2017/12/20
		* @example：
		* @return：
      * @parameter: btype 备份类型：TRUE 整体备份 FALSE 差异备份
		  **************************
	********************************/

	BOOL BackupDatabase(CString strDirectory,BOOL btype = FALSE);	
   BOOL RunBackUp();

   void reset(BOOL bStopCy);
	

public:
// 对话框数据
	enum { IDD = IDD_DLG_PANE1_ITEM1 };


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOldPathButton();
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeOldPathEdit();
	afx_msg void OnBnClickedButton1();
   afx_msg void  AddTask();
   afx_msg void OnTimer(UINT_PTR nIDEvent);
   afx_msg void OnBnClickedCheckAutoBackup();
   int m_radioGroup;
   afx_msg void OnBnClickedRadio1();
   afx_msg void OnBnClickedBtnOpenTaskview();
   afx_msg void OnBnClickedButtonAddTask();
   afx_msg void OnEnKillfocusEditCycle();
   afx_msg void OnBnClickedMonthAllCheck();
   afx_msg void OnBnClickedDayAllCheck();
   CEdit m_etDeleteDay;
   afx_msg void OnBnClickedChkAutoDelte();
protected:
	CButton m_btnAutoDelete;
};

extern CString strWeek[7];
