#pragma once
#include "MyCtrlEx\TabDlg\TabDialog.h"
#include "DBDatabaseFields.h"
#include "MyADOConnEx.h"
#include "FileTxt.h"
#include "Directory.h"
#include "afxwin.h"


// CDlgPane1Item3 对话框

class CDlgPane1Item3 : public CTabDialog
{
	DECLARE_DYNAMIC(CDlgPane1Item3)

public:
	CDlgPane1Item3(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgPane1Item3();
	

	/*******************************
	*************
		* @brief：将数据库保存到文件中
		* @author：zhangyx 2017/12/20
		* @example：
		* @return：
		  **************************
	********************************/
	void SaveDatabaseToFile(CString strFile, CString strDatabase = _T("[QLPLM]")); 
   
		/*******************************
	*************
		* @brief：获取字段名
		* @author：zhangyx 2017/12/20
		* @example：
		* @return：
		  **************************
	********************************/
	void GetFieldsName(CDBDatabaseTableList *pDBDatabaseTableList,CString strDatabase, CString strTable);   

	/*******************************
	*************
		* @brief：将客户数据库信息读取到链表中
		* @author：zhangyx 2017/12/20
		* @example：
		* @return：
		  **************************
	********************************/
	void PutClientDatabaseToClist(CDBDatabaseTableList &DBDatabaseTableListClient, CString strDatabase);	


	/*******************************
	*************
		* @brief：比较数据库信息并更新客户数据库
		* @author：zhangyx 2017/12/20
		* @example：
		* @return：BOOL
					TRUE：更新客户数据库成功
					FALSE：更新客户数据库失败
		  **************************
	********************************/
	BOOL CompareDatabase(CDBDatabaseTableList &DBDatabaseTableList, CDBDatabaseTableList &DBDatabaseTableListClient, CString strDatabase);	


	/*******************************
		*************
		* @brief：比较两个数据库的表字段名
		* @author：zhangyx 2017/12/20
		* @example：
		* @return：BOOL
		TRUE：比较成功
		FALSE：比较失败
		**************************
		********************************/
	BOOL CompareTableFields(CDBDatabaseTable* pDBDatabaseTable, CDBDatabaseTable* pDBDatabaseTableClient, CString strDatabase);		

	/*******************************
	*************
		* @brief：根据保存的文件中数据库信息创建数据库
		* @author：zhangyx 2017/12/20
		* @example：
		* @return：
		  **************************
	********************************/
	void CreateDatabaseFromFile(CString strDatabase, BOOL &bRet);			

		/*******************************
	*************
		* @brief：获取读文件时创建数据库字段信息语句
		* @author：zhangyx 2017/12/20
		* @example：
		* @return：CString：返回创建数据库语句
		  **************************
	********************************/
	CString GetFieldsInfoFromReadFile(CDBDatabaseTable *pDBDatabaseTable);			

	/*******************************
	*************
		* @brief：创建数据表
		* @author：zhangyx 2017/12/20
		* @example：
		* @return：BOOL
					TRUE：创建成功
					FALSE：创建失败
		  **************************
	********************************/
	BOOL CreateDataBaseTable(CString strDatabase, CString strTable, CString strlist);  

		/*******************************
	*************
		* @brief：过滤数据字段类型长度
		* @author：zhangyx 2017/12/20
		* @example：
		* @return：
		  **************************
	********************************/
	void FilterFieldsLength(CString &strFieldsType, CString &strFieldsLength);		

		/*******************************
		*************
		* @brief：添加客户端数据库没有的信息
		* @author：zhangyx 2017/12/20
		* @example：
		* @return：BOOL
		TRUE：添加客户数据库成功
		FALSE：添加客户数据库失败
		**************************
		********************************/
	BOOL AddFieldsToDatabase(CString strDatabase, CString strTable, CDBDatabaseFields* pDBDatabaseFields);	

   //触发器相关
   void SaveTriggerToFile(CString strFile); 
   BOOL GetTrigger(CString strFile);


// 对话框数据
	enum { IDD = IDD_DLG_PANE1_ITEM3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

private:
	CDBDatabaseTableList m_DBDatabaseTableList;  //存储本地数据库信息链
	//数据库变量
	CMyADOConnEx *m_pADOConn;
	/*CString m_strDatabase;*/
	CFileTxt m_FileTxt;
	CDirectory m_CDirectroy;
	CStringList m_strList;
   CEdit m_edit_trigger;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSaveDir();
	afx_msg void OnBnClickedUpdateDatabaseButton();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnSave();
	afx_msg void OnBnClickedBtnUpdate();
	afx_msg void OnBnClickedUpdateFunctionButton();
	afx_msg void OnBnClickedBtnUpdateFunction();

   CString CompareDataName(CString strPath);
   
   //触发器相关
   afx_msg void OnBnClickedBtnSaveTrigger();
   afx_msg void OnBnClickedBtnDirTrigger();
   afx_msg void OnBnClickedUpdateTriggerButton();
   afx_msg void OnBnClickedBtnUpdateTrigger();
};
