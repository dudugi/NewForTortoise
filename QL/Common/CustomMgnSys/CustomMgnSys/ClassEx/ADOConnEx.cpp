#include "StdAfx.h"


#include "ADOConnEx.h"
#include "..\CustomMgnSys.h"
//#include "CustomMgnSys.h"
//#include "KDS-FileMgn.h"

const CString CS_DRIVER = _T("Driver");
const CString CS_SERVER = _T("Server");
const CString CS_DEF_PORT = _T("1433");
const CString CS_DATABASE = _T("Database");
const CString CS_UID = _T("UID");
const CString CS_PWD = _T("PWD");


CADOConnEx::CADOConnEx(void)
{
	m_strConnectSql = GetConncetSqlStr();
}


CADOConnEx::~CADOConnEx(void)
{
}


CString CADOConnEx::GetConncetSqlStr(BOOL bWithDrive/* = TRUE*/)
{
 	CString strRetConnect = _T("");
	CString strProvide,strSvr,strDB,strUID,strPWD;
	CString strFilePath = theApp.m_strAppPath +_T("\\ConfigSvr.ini");//设置配置文件路径

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

	strRetConnect = _T("Server=")+ strSvr \
		+_T(";Database=")+ strDB \
		+_T(";UID=")+ strUID \
		+_T(";PWD=")+ strPWD;

	CString strDrive = _T("Driver={")+strProvide +_T("};");
	if(bWithDrive)
	{
		strRetConnect = strDrive + strRetConnect;
	}



	return strRetConnect;
}

COleDateTime CADOConnEx::GetSqlTime(int nTimeFormat /*= 20*/)
{
	//暂未验证除此数值之外的获取
	ASSERT((nTimeFormat >= -1 || nTimeFormat <= 25) || (nTimeFormat >= 100 || nTimeFormat <= 114) || (nTimeFormat >= 130 || nTimeFormat <= 131));
	CString strSQL = _T("");
	switch (nTimeFormat)
	{
	case -1:
		{
			strSQL.Format(_T("select GETDATE()"));
		}
		break;
	default:
		{
			strSQL.Format(_T("Select CONVERT(varchar(100), GETDATE(), %d)"),nTimeFormat);
		}
		break;
	}


	GetRecordSet(strSQL);

	return GetValueDate(0);

	/*
	Select CONVERT(varchar(100), GETDATE(), 0): 05 16 2008 10:57AM
	Select CONVERT(varchar(100), GETDATE(), 1): 05/16/08
	Select CONVERT(varchar(100), GETDATE(), 2): 08.05.16
	Select CONVERT(varchar(100), GETDATE(), 3): 16/05/08
	Select CONVERT(varchar(100), GETDATE(), 4): 16.05.08
	Select CONVERT(varchar(100), GETDATE(), 5): 16-05-08
	Select CONVERT(varchar(100), GETDATE(), 6): 16 05 08
	Select CONVERT(varchar(100), GETDATE(), 7): 05 16, 08
	Select CONVERT(varchar(100), GETDATE(), 8): 10:57:46
	Select CONVERT(varchar(100), GETDATE(), 9): 05 16 2008 10:57:46:827AM
	Select CONVERT(varchar(100), GETDATE(), 10): 05-16-08
	Select CONVERT(varchar(100), GETDATE(), 11): 08/05/16
	Select CONVERT(varchar(100), GETDATE(), 12): 080516
	Select CONVERT(varchar(100), GETDATE(), 13): 16 05 2008 10:57:46:937
	Select CONVERT(varchar(100), GETDATE(), 14): 10:57:46:967
	Select CONVERT(varchar(100), GETDATE(), 20): 2008-05-16 10:57:47
	Select CONVERT(varchar(100), GETDATE(), 21): 2008-05-16 10:57:47.157
	Select CONVERT(varchar(100), GETDATE(), 22): 05/16/08 10:57:47 AM
	Select CONVERT(varchar(100), GETDATE(), 23): 2008-05-16
	Select CONVERT(varchar(100), GETDATE(), 24): 10:57:47
	Select CONVERT(varchar(100), GETDATE(), 25): 2008-05-16 10:57:47.250
	Select CONVERT(varchar(100), GETDATE(), 100): 05 16 2008 10:57AM
	Select CONVERT(varchar(100), GETDATE(), 101): 05/16/2008
	Select CONVERT(varchar(100), GETDATE(), 102): 2008.05.16
	Select CONVERT(varchar(100), GETDATE(), 103): 16/05/2008
	Select CONVERT(varchar(100), GETDATE(), 104): 16.05.2008
	Select CONVERT(varchar(100), GETDATE(), 105): 16-05-2008
	Select CONVERT(varchar(100), GETDATE(), 106): 16 05 2008
	Select CONVERT(varchar(100), GETDATE(), 107): 05 16, 2008
	Select CONVERT(varchar(100), GETDATE(), 108): 10:57:49
	Select CONVERT(varchar(100), GETDATE(), 109): 05 16 2008 10:57:49:437AM
	Select CONVERT(varchar(100), GETDATE(), 110): 05-16-2008
	Select CONVERT(varchar(100), GETDATE(), 111): 2008/05/16
	Select CONVERT(varchar(100), GETDATE(), 112): 20080516
	Select CONVERT(varchar(100), GETDATE(), 113): 16 05 2008 10:57:49:513
	Select CONVERT(varchar(100), GETDATE(), 114): 10:57:49:547
	Select CONVERT(varchar(100), GETDATE(), 120): 2008-05-16 10:57:49
	Select CONVERT(varchar(100), GETDATE(), 121): 2008-05-16 10:57:49.700
	Select CONVERT(varchar(100), GETDATE(), 126): 2008-05-16T10:57:49.827
	Select CONVERT(varchar(100), GETDATE(), 130): 18 ???? ?????? 1427 10:57:49:907AM
	Select CONVERT(varchar(100), GETDATE(), 131): 18/04/1427 
	10:57:49:920AM
	*/

}

void CADOConnEx::SetConnectSqlStr(CString strConectStr)
{
   m_strConnectSql = strConectStr;
}

void CADOConnEx::GetConfigSvr( CString strAppName,CString strKeyName,CString &strKeyValue,CString strPathFile )
{
	TCHAR temp[MAX_PATH];
	GetPrivateProfileString(strAppName,strKeyName,_T(""),temp,MAX_PATH,strPathFile);
	strKeyValue.Format(_T("%s"),temp);
	strKeyValue.Trim();
}

//		by WangZY 2018/08/22
CString CADOConnEx::CreateConncetSqlStrByEncodeParam(CString strSvr, CString strDB, 
   CString strUID, CString strPWD, CString strProvide /*= _T("SQL Server")*/)
{
   CString strRetConnect = _T("");

   strSvr = theApp.OnDecodeStr(strSvr);
   strDB = theApp.OnDecodeStr(strDB);
   strUID = theApp.OnDecodeStr(strUID);
   strPWD = theApp.OnDecodeStr(strPWD);

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
   
   //添加默认端口
   if (strSvr.Find(',')<0)
   {
      strSvr += _T(",") + CS_DEF_PORT; 
   }

   strRetConnect.Format(_T("%s=%s;%s=%s;%s=%s;%s=%s"),
      CS_SERVER, strSvr,
      CS_DATABASE,strDB,
      CS_UID,strUID,
      CS_PWD,strPWD);

   if (!strProvide.IsEmpty())
   {
       CString strDriver = CS_DRIVER + _T("={")+strProvide +_T("};");
       strRetConnect = strDriver + strRetConnect;
   }
  
   return strRetConnect;
}

//		by WangZY 2018/08/22
CString CADOConnEx::CreateConncetSqlStrByDecodeParam(CString strSvr, CString strDB, 
   CString strUID, CString strPWD, CString strProvide /*= _T("SQL Server")*/)
{
   CString strRetConnect = _T("");

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

   //添加默认端口
   if (strSvr.Find(',')<0)
   {
      strSvr += _T(",") + CS_DEF_PORT; 
   }

   strRetConnect.Format(_T("%s=%s;%s=%s;%s=%s;%s=%s"),
      CS_SERVER, strSvr,
      CS_DATABASE,strDB,
      CS_UID,strUID,
      CS_PWD,strPWD);

   if (!strProvide.IsEmpty())
   {
      CString strDriver = CS_DRIVER + _T("={")+strProvide +_T("};");
      strRetConnect = strDriver + strRetConnect;
   }

   return strRetConnect;
}
