#pragma once
#include "stdafx.h"
#include "ADOConnEx.h"

#include "CDBPtLogInfo_new.h"
#include "CDBPtLogInfo.h"

std::shared_ptr<CDBPtLogInfo_New> CDBPtLogInfo_New::sm_inst;

CDBPtLogInfo_New::CDBPtLogInfo_New()
{
   ResetData();
}

CDBPtLogInfo_New::~CDBPtLogInfo_New()
{

}
void CDBPtLogInfo_New::ResetData()
{
   m_nTheardEndFlag = 0;
   m_strMacAddr = _T("");
   QLCOMAPI.GetMacByNetBIOS(m_strMacAddr);
}
void CDBPtLogInfo_New::Clear()
{
   m_LogInfo.clear();
}

void CDBPtLogInfo_New::SetDataLogInfo(CADOConnEx *pADOConn,CString strCate, CString strCode ,CString strMemo,CString strType,CString strMakerID,int nLoginType)//设置日志数据
{
   if (nLoginType == -1)
   {
      return;
   }
   CString strPersonID = _T(""), strPersonName = _T(""), strSQL = _T("");
   switch (nLoginType)
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
   STRUCT_LOGINFO stc_log_Info;
   stc_log_Info.m_strCate = strCate;
   stc_log_Info.m_strCode = strCode;
   stc_log_Info.m_strMaker = strPersonName;
   stc_log_Info.m_strMemo = strMemo;      //日志内容 
   stc_log_Info.m_strType = strType;      //日志操作
   m_LogInfo.insert(make_pair(m_LogInfo.size(),stc_log_Info));
}
BOOL CDBPtLogInfo_New::InsertSQL_LogInfo(CADOConnEx *pADOConn)//插入日志信息
{
   ASSERT(NULL != pADOConn);
   if (m_LogInfo.size() == 0)
   {
      return FALSE;
   }
   CString strAct = _T(""), strCate = _T("") , strCode = _T(""), strMaker = _T(""), strType = _T(""), strMemo = _T("");
   auto itr_map = m_LogInfo.begin();
   for (;itr_map != m_LogInfo.end(); ++itr_map)
   {
      strType = itr_map->second.m_strType;
      strMaker = itr_map->second.m_strMaker;
      strCode = itr_map->second.m_strCode;
      strCate = itr_map->second.m_strCate;
      strMemo += itr_map->second.m_strMemo + _T(",");
   }
   CString strSQL;
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
      strMaker,	//4
      strType,	//5
      strMemo,	//6
      m_strMacAddr
      );

   strSQL.Format(_T("insert into %s(%s) values(%s)"),DB_TABLE_LOG,strFormat,strValue);

   pADOConn->ExecuteSQL(strSQL);
   return TRUE;
}
CDBPtLogInfo_New *CDBPtLogInfo_New::Instance()
{
   if(sm_inst.get() == 0)
      sm_inst = shared_ptr<CDBPtLogInfo_New>(new CDBPtLogInfo_New);

   return sm_inst.get();
}