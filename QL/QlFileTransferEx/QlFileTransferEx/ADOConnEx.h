#pragma once
#include "ADOConn.h"
class CADOConnEx :
	public CADOConn
{
public:
	CADOConnEx(void);
	~CADOConnEx(void);

	/*
	 * @brief	获取连接数据的字符串
	 */
	CString GetConncetSqlStr();

	void SetConnecetSqlStr(CString strConnectSql){m_strConnectSql = strConnectSql;}

private:
	/*
	 * @brief	获取配置文件ConfigSvr.ini的键值
	 */
	void GetConfigSvr(CString strAppName,CString strKeyName,CString &strKeyValue,CString strPathFile);
};

