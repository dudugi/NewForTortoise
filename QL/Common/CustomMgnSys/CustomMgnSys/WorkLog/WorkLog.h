#pragma once
#include "DBWorkLogOperator.h"

namespace WorkLog
{

   //����һ��������¼��worklog�� by YangJR 2017/08/16
   BOOL InsertOneWorkLog(Em_WorkLog_Cate enCate,Em_WorkLog_Type enType,
      CString strCode,CString strMemo,CString strInterfaceID= _T(""));

   BOOL InsertMultiWorkLog(Em_WorkLog_Cate enCate,Em_WorkLog_Type enType,
      vector<CString> vecCode,CString strMemo,CString strInterfaceID= _T(""));

   CString Get_InsertOneWorkLog_Sql(Em_WorkLog_Cate enCate,Em_WorkLog_Type enType,
      CString strCode,CString strMemo,CString strInterfaceID= _T(""));

};