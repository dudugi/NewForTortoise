#pragma once
#include "ADOConn\ADOConn.h"


class CADOConnEx :
	public CADOConn
{
public:
	CADOConnEx(void);
	CADOConnEx(const CADOConnEx& ADOConn)
	{
		m_strConnectSql = ADOConn.m_strConnectSql;
	}
	~CADOConnEx(void);

	/*
	 * @brief	获取连接数据的字符串
	 */
	CString GetConncetSqlStr(BOOL bWithDrive = TRUE);

	/*
	 * @brief	获取数据库当前的时间
	 */
	COleDateTime GetSqlTime(int nTimeFormat = 20);

   void SetConnectSqlStr(CString strConectStr);


public:

	/*
	 * @brief	获取配置文件ConfigSvr.ini的键值
	 */
	static void GetConfigSvr(CString strAppName,CString strKeyName,
      CString &strKeyValue,CString strPathFile);

   //已加密的数据
   static CString CreateConncetSqlStrByEncodeParam(CString strSvr, CString strDB, 
      CString strUID, CString strPWD, CString strProvide = _T("SQL Server"));

   //未加密的数据
   static CString CreateConncetSqlStrByDecodeParam(CString strSvr, CString strDB, 
      CString strUID, CString strPWD, CString strProvide = _T("SQL Server"));
};

