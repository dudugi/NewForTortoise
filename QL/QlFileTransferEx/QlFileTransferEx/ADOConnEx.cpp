#include "StdAfx.h"
#include "ADOConnEx.h"
#include "QlFileTransferEx.h"

CADOConnEx::CADOConnEx(void)
{
	m_strConnectSql = GetConncetSqlStr();
}


CADOConnEx::~CADOConnEx(void)
{
}

CString CADOConnEx::GetConncetSqlStr()
{
 	CString strRetConnect = _T("");
	CString strProvide,strSvr,strDB,strUID,strPWD;
	CString strFilePath = theApp.m_strSvrPath;//设置配置文件路径

	if (!PathFileExists(strFilePath))
	{
		return strRetConnect;
	}

	GetConfigSvr(_T("SQLSVR"),_T("SVR"),strSvr,strFilePath);
	GetConfigSvr(_T("SQLSVR"),_T("DB"),strDB,strFilePath);
	GetConfigSvr(_T("SQLSVR"),_T("UID"),strUID,strFilePath);
	GetConfigSvr(_T("SQLSVR"),_T("PWD"),strPWD,strFilePath);

	strSvr = theApp.OnDecodeStr(strSvr);
	strDB = theApp.OnDecodeStr(strDB);
	strUID = theApp.OnDecodeStr(strUID);
	strPWD = theApp.OnDecodeStr(strPWD);

	strProvide = _T("SQL Server");//SQL2008

	CString strApply = _T("");
	GetConfigSvr(_T("Setting"),_T("LG_CHK_APPLY"),strApply,strFilePath);

	BOOL bApply = FALSE;
	if (strApply == _T("TRUE"))
	{
		bApply = TRUE;
	}

	if (bApply)
	{
		if (strSvr.IsEmpty())//192.168.2.65,1433
		{
			return strRetConnect;
		}
		else if (strDB.IsEmpty())//qili
		{
			return strRetConnect;
		}

		strUID = strDB + _T("123QL");
		strPWD = strDB + _T("123456QL");
	}
	else
	{
		if (strSvr.IsEmpty())//192.168.2.65,1433
		{
			return strRetConnect;
		}
		else if (strDB.IsEmpty())//qili
		{
			return strRetConnect;
		}
		else if (strUID.IsEmpty())//sa
		{
			return strRetConnect;
		}
		else if (strPWD.IsEmpty())//123456zt
		{
			return strRetConnect;
		}
	}

	//添加默认端口
	if (strSvr.Find(',')<0)
	{
		strSvr += _T(",1433");
	}

	strRetConnect = _T("Driver={")+strProvide \
		+_T("};Server=")+ strSvr \
		+_T(";Database=")+ strDB \
		+_T(";UID=")+ strUID \
		+_T(";PWD=")+ strPWD;

	return strRetConnect;
}

void CADOConnEx::GetConfigSvr( CString strAppName,CString strKeyName,CString &strKeyValue,CString strPathFile )
{
	TCHAR temp[MAX_PATH];
	GetPrivateProfileString(strAppName,strKeyName,_T(""),temp,MAX_PATH,strPathFile);
	strKeyValue.Format(_T("%s"),temp);
	strKeyValue.Trim();
}
