#pragma once
#include "DBWorkLogOperator.h"

namespace WorkLog
{

   //插入一条操作记录到worklog表 by YangJR 2017/08/16
   BOOL InsertOneWorkLog(Em_WorkLog_Cate enCate,Em_WorkLog_Type enType,
      CString strCode,CString strMemo,CString strInterfaceID= _T(""));

   BOOL InsertMultiWorkLog(Em_WorkLog_Cate enCate,Em_WorkLog_Type enType,
      vector<CString> vecCode,CString strMemo,CString strInterfaceID= _T(""));

   CString Get_InsertOneWorkLog_Sql(Em_WorkLog_Cate enCate,Em_WorkLog_Type enType,
      CString strCode,CString strMemo,CString strInterfaceID= _T(""));

};