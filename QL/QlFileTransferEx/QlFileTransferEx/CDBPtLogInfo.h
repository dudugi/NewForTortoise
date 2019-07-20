#pragma once
#include "stdafx.h"
#include "ADOConnEx.h"
#include "ClassDB\DBPersonInfo.h"
#include "DBDef.h"
#include "ClassDB\DBCustomInfo.h"
#include "CommonAPI.h"
class CDBPtLogInfo
{
private:
	typedef enum S_FileTrans_LoginType{
		En_Login_User = 0,//员工登录
		En_Login_Custom,//客户登录
	}S_FILETRANS_LOGINTYPE;

	int m_nLoginType;

public:
	CDBPtLogInfo(int nLoginType){m_nLoginType = nLoginType;}
	virtual ~CDBPtLogInfo(){}
	void operator()(CADOConnEx *pADOConn,CString strCate,CString strCode,CString strMakerID,CString strType,CString strMemo)
	{
		ASSERT(NULL != pADOConn);

		CString strSQL = _T(""),strPersonName = _T(""),strPersonID = _T("");
		switch (m_nLoginType)
		{
		case En_Login_Custom:
			{
				strSQL.Format(_T("select * from %s where %s = '%s'"),DB_TABLE_CUSTOM,DBCustomer_key_Code,strMakerID);
				if(pADOConn->GetRecordSet(strSQL))
				{
               strPersonID = pADOConn->GetValueString(DBPerson_key_UserID);
               strPersonName = pADOConn->GetValueString(DBPerson_key_UserName);
				}
			}
			break;
		case En_Login_User:
			{
				strSQL.Format(_T("select * from %s where %s = '%s'"),DB_TABLE_PERSON,DBPerson_key_UserID,strMakerID);
				if(pADOConn->GetRecordSet(strSQL))
				{
					strPersonID = pADOConn->GetValueString(DBPerson_key_UserID);
               strPersonName = pADOConn->GetValueString(DBPerson_key_UserName);
				}
			}
			break;
		}

		if (strPersonName.IsEmpty())
		{
			strPersonName = strMakerID;
		}

		strPersonName = _T("(")+ strPersonID + _T(",") + strPersonName + _T(")");
      CString strMacAddr;
      QLCOMAPI.GetMacByNetBIOS(strMacAddr);
		strSQL.Format(_T(""));

		CString strFormat = _T(""),strValue = _T("");
		//					 1 ,2 ,3 ,4 ,5 ,6
		strFormat.Format(_T("%s,%s,%s,%s,%s,%s,%s"),
			DBWorkLog_key_Cate	,//1
			DBWorkLog_key_Code	,//2
			DBWorkLog_key_Date	,//3
			DBWorkLog_key_Maker	,//4
			DBWorkLog_key_Type	,//5
			DBWorkLog_key_Detail ,//6
         DBWorkLog_key_MacAddr
			);
		//					1   ,2   ,3        ,4   ,5   ,6
		strValue.Format(_T("'%s','%s',GetDate(),'%s','%s','%s','%s'"),
			strCate,	//1
			strCode,	//2
//			m_dDate,	//3
			strPersonName,	//4
			strType,	//5
			strMemo,	//6
         strMacAddr
			);

		strSQL.Format(_T("insert into %s(%s) values(%s)"),DB_TABLE_LOG,strFormat,strValue);

		pADOConn->ExecuteSQL(strSQL);
	}
};

#define DBPTLOGUSER	CDBPtLogInfo(0)
#define DBPTLOGCUSTOM	CDBPtLogInfo(1)

