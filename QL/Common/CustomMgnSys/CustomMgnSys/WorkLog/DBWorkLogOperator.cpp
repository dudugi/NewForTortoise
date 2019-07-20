#include "StdAfx.h"
#include "DBWorkLogOperator.h"
#include "DBLogInfo.h"
#include "Resource.h"


CDBWorkLogOperator* CDBWorkLogOperator::p_Instance = NULL;

CDBWorkLogOperator::CDBWorkLogOperator(void)
{
}

CDBWorkLogOperator::~CDBWorkLogOperator(void)
{
}

BOOL CDBWorkLogOperator::InsertWorkLog(CADOConn *pADOConn,Em_WorkLog_Cate nCate,Em_WorkLog_Type nType, CString strMaker ,
										CString strInterfaceID/*= _T("")*/,CString strCode/*= _T("")*/,CString strLogInfo/*= _T("")*/)
{
	ASSERT(pADOConn != NULL);
	ASSERT(!strMaker.IsEmpty());

	CString strCate = _T("");
   CString strType = _T("");
   CString strProName;
   strProName.LoadString(IDS_PRO_NAME);

	if (nCate < Log_Cate_Num)
	{
		strCate = g_TableID[nCate];
	}

	if(nType < Log_Type_Num)
	{
		strType = g_LogType[nType];
	}

	CDBLogInfoData::Instance()->SetLogData(strCate,strCode,strMaker,strType,strLogInfo,strInterfaceID,strProName);
	return CDBLogInfoData::Instance()->InsertAllDBInfoByAct(pADOConn);
}

BOOL CDBWorkLogOperator::InsertMultiWorkLog(CADOConn *pADOConn,Em_WorkLog_Cate nCate,Em_WorkLog_Type nType,CString strMaker , 
											CString strInterfaceID/*= _T("")*/,vector<CString> vecCode /*= vector<CString>()*/,CString strLogInfo/*= _T("")*/)
{
	if (vecCode.size() <= 0)
	{
		return FALSE;
	}

	ASSERT(pADOConn != NULL);
	ASSERT(!strMaker.IsEmpty());

	CString strCate = _T(""),strType = _T(""),strProName;
   strProName.LoadString(IDS_PRO_NAME);

	if (nCate < Log_Cate_Num)
	{
		strCate = g_TableID[nCate];
	}

	if(nType < Log_Type_Num)
	{
		strType = g_LogType[nType];
	}

	for (int i=0; i< (int)vecCode.size(); ++i)
	{
		CDBLogInfoData::Instance()->SetLogData(strCate,vecCode[i],strMaker,strType,strLogInfo,strInterfaceID,strProName);
		CString strSQL = CDBLogInfoData::Instance()->GetInsertSQL();
		pADOConn->AppendBatchSQL(strSQL);
	}
	return pADOConn->ExecuteBatchSQL();
}

CString CDBWorkLogOperator::Get_InsertWorkLog_Sql(CADOConn *pADOConn,Em_WorkLog_Cate nCate,Em_WorkLog_Type nType,CString strMaker , CString strInterfaceID/*= _T("")*/,CString strCode/*= _T("")*/,CString strLogInfo/*= _T("")*/)
{
	ASSERT(pADOConn != NULL);
	ASSERT(!strMaker.IsEmpty());

	CString strCate = _T(""),strType = _T(""),strProName;
   strProName.LoadString(IDS_PRO_NAME);

	if (nCate < Log_Cate_Num)
	{
		strCate = g_TableID[nCate];
	}

	if(nType < Log_Type_Num)
	{
		strType = g_LogType[nType];
	}

	CDBLogInfoData::Instance()->SetLogData(strCate,strCode,strMaker,strType,strLogInfo,strInterfaceID,strProName);
	return CDBLogInfoData::Instance()->GetInsertSQL();
}


