#pragma once
#include "afxwin.h"
#include "MyCtrlEx\TabDlg\TabDialog.h"
#include "MyADOConnEx.h"
#include "Directory.h"
#include "usr_define.h"

// add by lida  2018/09/04
// CDlgCreateSqlScript 差异脚本生成对话框

class CDlgCreateSqlScript : public CTabDialog
{
	DECLARE_DYNAMIC(CDlgCreateSqlScript)

public:
	CDlgCreateSqlScript(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgCreateSqlScript();

// 对话框数据
	enum { IDD = IDD_DIALOG_CREATE_SQL_SCRIPT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
   CIPAddressCtrl m_IpAddress;
   CIPAddressCtrl m_IpAddress2;
   CEdit m_edit_port;
   CEdit m_edit_port2;
   CEdit m_edit_dbname;
   CEdit m_edit_dbname2;
   CEdit m_edit_dbaccount;
   CEdit m_edit_dbaccount2;
   CEdit m_edit_dbpwd;
   CEdit m_edit_dbpwd2;
   CEdit m_edit_file_path;

   CDirectory m_CDirectroy;

   map_db_attri   m_map_db_attri_src;
   map_db_attri   m_map_db_attri_dst;

   CMyADOConnEx       m_ado_src;
   CMyADOConnEx       m_ado_dst;

   tag_db_info    m_db_info_src;
   tag_db_info    m_db_info_dst;

   mapSqlScript   m_map_sql_script;   //<tablename,vec<sql>>

public:
   BOOL bConnectDB_src();
   BOOL bConnectDB_dst();

   void GetAllValue(CMyADOConnEx* pAdo,tag_db_attri& oData);
   void Add2MapAttri(map_db_attri& map_attri,tag_db_attri& oData);

   afx_msg void OnBnClickedButtonFile();
   afx_msg void OnBnClickedButtonCreateScript();
   afx_msg void OnBnClickedBtnTestConnect();
   
   virtual BOOL OnInitDialog();
};
