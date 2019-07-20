#include "StdAfx.h"
#include "DBUserTaskInfo_V.h"
#include "DBKeyDef_V.h"
#include "DBProSet_Style.h"
IMPLEMENT_SERIAL(CDBUserTaskInfoData_V,CDataMid,1)

CDBUserTaskInfoData_V::CDBUserTaskInfoData_V()
{
   ResetData();
}

CDBUserTaskInfoData_V::~CDBUserTaskInfoData_V()
{
}

void CDBUserTaskInfoData_V::ResetData()   
{
   m_strUserID          = _T("");
   m_strKuanhao         = _T("");
   m_nTaskType          = 0;
   m_nIsGroup           = CDBProSet_StyleData::en_Person;

   SetDataType(DAT_V_USER_TASKINFO);
}

void CDBUserTaskInfoData_V::Copy( CDBUserTaskInfoData_V *pData )
{
   ASSERT(pData!=NULL);
   CDataMid::Copy(pData);
   m_strUserID    = pData->m_strUserID   ;
   m_strKuanhao   = pData->m_strKuanhao  ;
   m_nTaskType    = pData->m_nTaskType   ;
   m_nIsGroup     = pData->m_nIsGroup    ;
}

BOOL CDBUserTaskInfoData_V::GetAllDBInfo( CADOConn *pADOConn )
{
   ASSERT(pADOConn != NULL);

   m_strUserID   = pADOConn->GetValueString(DBUserTaskInfo_V_cUserID           );
   m_strKuanhao  = pADOConn->GetValueString(DBUserTaskInfo_V_cKuanhao);
   m_nTaskType   = pADOConn->GetValueInt(DBUserTaskInfo_V_nTaskType);
   m_nIsGroup    = pADOConn->GetValueInt(DBUserTaskInfo_V_bIsGroup);

   return TRUE;
}


CDBUserTaskInfoList_V::CDBUserTaskInfoList_V()
{

}

CDBUserTaskInfoList_V::~CDBUserTaskInfoList_V()
{

}
