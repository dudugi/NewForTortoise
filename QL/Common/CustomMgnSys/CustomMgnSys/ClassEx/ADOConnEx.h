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
	 * @brief	��ȡ�������ݵ��ַ���
	 */
	CString GetConncetSqlStr(BOOL bWithDrive = TRUE);

	/*
	 * @brief	��ȡ���ݿ⵱ǰ��ʱ��
	 */
	COleDateTime GetSqlTime(int nTimeFormat = 20);

   void SetConnectSqlStr(CString strConectStr);


public:

	/*
	 * @brief	��ȡ�����ļ�ConfigSvr.ini�ļ�ֵ
	 */
	static void GetConfigSvr(CString strAppName,CString strKeyName,
      CString &strKeyValue,CString strPathFile);

   //�Ѽ��ܵ�����
   static CString CreateConncetSqlStrByEncodeParam(CString strSvr, CString strDB, 
      CString strUID, CString strPWD, CString strProvide = _T("SQL Server"));

   //δ���ܵ�����
   static CString CreateConncetSqlStrByDecodeParam(CString strSvr, CString strDB, 
      CString strUID, CString strPWD, CString strProvide = _T("SQL Server"));
};

