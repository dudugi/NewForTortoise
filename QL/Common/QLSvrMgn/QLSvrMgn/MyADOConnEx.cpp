#include "StdAfx.h"
#include "MyADOConnEx.h"
#include "QLSvrMgn.h"
#include "LocalConfigureDlg.h"

const CString CS_DRIVER = _T("Driver");
const CString CS_SERVER = _T("Server");
const CString CS_DEF_PORT = _T("1433");
const CString CS_DATABASE = _T("Database");
const CString CS_UID = _T("UID");
const CString CS_PWD = _T("PWD");

CMyADOConnEx::CMyADOConnEx(BOOL bRet /*= TRUE*/)
{
	m_strDBName = _T("");
	m_strConnectSql = GetLocalConncetSqlStr(bRet);
}


CMyADOConnEx::~CMyADOConnEx(void)
{
}


CString CMyADOConnEx::GetLocalConncetSqlStr(BOOL bRet /*= TRUE*/)
{
	CString strRetConnect = _T("");
	CString strProvide,strSvr,strDB,strUID,strPWD;
	CString strFilePath = theApp.m_strAppPath +_T("\\SQLSVR.ini");//设置配置文件路径

	if (!PathFileExists(strFilePath))
	{
		return strRetConnect;
	}

	theApp.OnReadIni(_T("ConfigureInfo"), _T("DatabaseIP"), strSvr,INI_SQLSVR);
	if(bRet)
	{
		theApp.OnReadIni(_T("ConfigureInfo"), _T("DatabaseName"), strDB,INI_SQLSVR);
	}
	else
	{
		strDB = _T("master");
	}
	theApp.OnReadIni(_T("ConfigureInfo"), _T("DatabaseAccount"), strUID,INI_SQLSVR);
	theApp.OnReadIni(_T("ConfigureInfo"), _T("DatabasePassword"), strPWD,INI_SQLSVR);


	strProvide = _T("SQL Server");//SQL2008


	if (strSvr.IsEmpty())//192.168.2.65 ,1433
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
		strSvr += _T(",1433");
 	}

	strRetConnect = _T("Server=")+ strSvr + _T(";Database=")+ strDB + _T(";UID=")+ strUID + _T(";PWD=")+ strPWD;
	m_strDBName = strDB;

	CString strDrive = _T("Driver={")+strProvide +_T("};");
	
	strRetConnect = strDrive + strRetConnect;

	return strRetConnect;
}

void CMyADOConnEx::GetTableName(CString strSQL)
{
	m_vecCString.clear();
	/*m_pRecordset = */GetRecordSet(strSQL);
	
	try  
	{  
		/*while (m_pRecordset->adoEOF==0)  
		{  
			strTableName = (LPCTSTR)((_bstr_t)m_pRecordset->GetCollect(_variant_t((long)nx)));  
			m_vecCString.push_back(strTableName);
			m_pRecordset->MoveNext();  
		}*/  
		while (!adoEOF())  
		{  
			CString strTableName = GetValueString(0);  
			if (!strTableName.IsEmpty())
			{
				m_vecCString.push_back(strTableName);
			}	
			
			MoveNext();  
		} 
	}  
	catch(_com_error &e)  
	{  
		CString strError = e.Description();
		OutputDebugString(strError);
		return;  
	}  
}

BOOL CMyADOConnEx::CreateConnectSql(CString strSvr,CString strDBName,CString strDBAct,CString strDBPwd)
{
   BOOL bRet = TRUE;

   CString strProvide = _T("SQL Server");//SQL2008

   if (strSvr.IsEmpty())//192.168.2.65,1433
   {
      return FALSE;
   }
   else if (strDBName.IsEmpty())//qili
   {
      return FALSE;
   }
   else if (strDBAct.IsEmpty())//sa
   {
      return FALSE;
   }
   else if (strDBPwd.IsEmpty())//123456zt
   {
      return FALSE;
   }

   //添加默认端口
   if (strSvr.Find(',')<0)
   {
      strSvr += _T(",1433");
   }

   m_strConnectSql = _T("Server=")+ strSvr \
      +_T(";Database=")+ strDBName \
      +_T(";UID=")+ strDBAct \
      +_T(";PWD=")+ strDBPwd;

   CString strDrive = _T("Driver={")+strProvide +_T("};");

   m_strConnectSql = strDrive + m_strConnectSql;

   return bRet;
}

BOOL CMyADOConnEx::InitConnect()
{
   BOOL bRet = FALSE;

   CloseConnect();//2017/04/28 zhangt

   //初始化OLE/COM库环境
   ::CoInitialize(NULL);
   m_pConnection = NULL;
   m_pRecordset = NULL;

   HRESULT hr = m_pConnection.CreateInstance("ADODB.Connection");

   //设置连接字符串，必须是BSTR型或者_bstr_t类型
   _bstr_t vConnect;

   //通过外部配置文件获取连接数据库字符串 
#ifdef _DEBUG
   if (m_strConnectSql.IsEmpty())
   {
      vConnect = _bstr_t("Driver={SQL Server};Server=192.168.3.39,1433;Database=qili;UID=sa;PWD=wzl123456");
   }
   else
   {
      vConnect = _bstr_t(m_strConnectSql);
   }
#else
   vConnect = _bstr_t(m_strConnectSql);
#endif // _DEBUG

   try
   {
      if (SUCCEEDED(hr))//创建成功
      {
         m_pConnection->ConnectionTimeout = 5;//连接超时时间
         m_pConnection->CommandTimeout = 0;//命令超时时间
         hr = m_pConnection->Open(vConnect,_bstr_t(""),_bstr_t(""),/*adModeUnknown*/adConnectUnspecified);
         if (SUCCEEDED(hr))
         {
            m_bInitConnect = TRUE;
            bRet = TRUE;
         }
      }
   }
   catch(_com_error& e)
   {
      CString strError = e.ErrorMessage();
      CString strDescripion = e.Description();//2017-08-03 wangzl 数据库错误信息描述

      ThrowExceptionMsg(strError,strDescripion);
   }
   catch(...)
   {
      //未知信息
   }

   ASSERT(m_pConnection != NULL);

   if (!bRet)
   {
      ::CoUninitialize();//释放环境
   }
   return bRet;
}

void CMyADOConnEx::SetConnectSqlStr(CString strConectStr)
{
   m_strConnectSql = strConectStr;
}

CString CMyADOConnEx::CreateConncetSqlStrByEncodeParam(CString strSvr, CString strDB, CString strUID, CString strPWD, CString strProvide /*= _T("SQL Server")*/)
{
   CString strRetConnect = _T("");

   //strSvr = theApp.OnDecodeStr(strSvr);
   //strDB = theApp.OnDecodeStr(strDB);
   //strUID = theApp.OnDecodeStr(strUID);
   //strPWD = theApp.OnDecodeStr(strPWD);

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

CString CMyADOConnEx::CreateConncetSqlStrByDecodeParam(CString strSvr, CString strDB, CString strUID, CString strPWD, CString strProvide /*= _T("SQL Server")*/)
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
