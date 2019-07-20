#include "stdafx.h"
#include "WorkLog.h"
#include "CustomMgnSys.h"

using namespace WorkLog;

//		by WangZY 2018/08/22
BOOL WorkLog::InsertOneWorkLog(Em_WorkLog_Cate enCate,Em_WorkLog_Type enType,
   CString strCode,CString strMemo,CString strInterfaceID/*= _T("")*/)
{
   return CDBWorkLogOperator::GetInstance()->InsertWorkLog(theApp.m_pADOConn,
      enCate,enType,theApp.m_objDBPerson.m_strUserID,strInterfaceID,strCode,strMemo);
}

//		by WangZY 2018/08/22
BOOL WorkLog::InsertMultiWorkLog(Em_WorkLog_Cate enCate,Em_WorkLog_Type enType,
   vector<CString> vecCode,CString strMemo,CString strInterfaceID/*= _T("")*/)
{
   return CDBWorkLogOperator::GetInstance()->InsertMultiWorkLog(theApp.m_pADOConn,
      enCate,enType,theApp.m_objDBPerson.m_strUserID,strInterfaceID,vecCode,strMemo);

}

//		by WangZY 2018/08/22
CString WorkLog::Get_InsertOneWorkLog_Sql(Em_WorkLog_Cate enCate,
   Em_WorkLog_Type enType,CString strCode,CString strMemo,
   CString strInterfaceID/*= _T("")*/)
{
   return CDBWorkLogOperator::GetInstance()->Get_InsertWorkLog_Sql(theApp.m_pADOConn,
      enCate,enType,theApp.m_objDBPerson.m_strUserID,strInterfaceID,strCode,strMemo);

}
