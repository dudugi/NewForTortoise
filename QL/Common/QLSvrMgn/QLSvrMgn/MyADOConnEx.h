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

   //�Ѽ��ܵ�����
   static CString CreateConncetSqlStrByEncodeParam(CString strSvr, CString strDB, 
      CString strUID, CString strPWD, CString strProvide = _T("SQL Server"));

   //δ���ܵ�����
   static CString CreateConncetSqlStrByDecodeParam(CString strSvr, CString strDB, 
      CString strUID, CString strPWD, CString strProvide = _T("SQL Server"));

public:
	CString m_strDBName;			//���ݿ�����

	vector<CString> m_vecCString;	//���� �洢���ݱ�����
};
