#pragma once
#include <vector>
#include "ADOConn\ADOConn.h"
using namespace std;

//by zhangyx 2017/12/6 
class CMyADOConnEx :
	public CADOConn
{
public:
   CMyADOConnEx(void)
   {

   };
   CMyADOConnEx(const CMyADOConnEx& ADOConn)
   {
      m_strConnectSql = ADOConn.m_strConnectSql;
   }
	CMyADOConnEx(BOOL bRet);
	~CMyADOConnEx(void);
	void GetTableName(CString strSQL);
    CString GetLocalConncetSqlStr(BOOL bRet = TRUE);
    BOOL CreateConnectSql(CString strSvr,CString strDBName,CString strDBAct,CString strDBPwd);

    virtual BOOL InitConnect();


   void SetConnectSqlStr(CString strConectStr);

   //已加密的数据
   static CString CreateConncetSqlStrByEncodeParam(CString strSvr, CString strDB, 
      CString strUID, CString strPWD, CString strProvide = _T("SQL Server"));

   //未加密的数据
   static CString CreateConncetSqlStrByDecodeParam(CString strSvr, CString strDB, 
      CString strUID, CString strPWD, CString strProvide = _T("SQL Server"));

public:
	CString m_strDBName;			//数据库名称

	vector<CString> m_vecCString;	//容器 存储数据表名称
};
