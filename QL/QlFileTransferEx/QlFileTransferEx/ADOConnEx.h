#pragma once
#include "ADOConn.h"
class CADOConnEx :
	public CADOConn
{
public:
	CADOConnEx(void);
	~CADOConnEx(void);

	/*
	 * @brief	��ȡ�������ݵ��ַ���
	 */
	CString GetConncetSqlStr();

	void SetConnecetSqlStr(CString strConnectSql){m_strConnectSql = strConnectSql;}

private:
	/*
	 * @brief	��ȡ�����ļ�ConfigSvr.ini�ļ�ֵ
	 */
	void GetConfigSvr(CString strAppName,CString strKeyName,CString &strKeyValue,CString strPathFile);
};

