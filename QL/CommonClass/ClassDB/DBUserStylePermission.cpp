#include "StdAfx.h"
#include "DBUserStylePermission.h"

IMPLEMENT_SERIAL(CDBUserStylePermissionData,  CDataMid, 1)
IMPLEMENT_SERIAL(CDBUserStylePermissionList,  CDataListMid, 1)

CDBUserStylePermissionData::CDBUserStylePermissionData(void)
{
   ResetData();
}


CDBUserStylePermissionData::~CDBUserStylePermissionData(void)
{
}

void CDBUserStylePermissionData::ResetData()
{
   m_nID = 0;
   m_nUserID = 0;
   m_nStyleID = 0;
   m_nPermission = 0;//权限默认为没有权限
   m_cPermissionTime = _T("");
   SetDataType(DAT_USERSTYLE_PERMISSION);
}

void CDBUserStylePermissionData::Copy( CDBUserStylePermissionData *pData )
{
   ASSERT(pData != NULL);
   CDataMid::Copy(pData);
   m_nID          = pData->m_nID         ;
   m_nUserID      = pData->m_nUserID     ;
   m_nStyleID     = pData->m_nStyleID    ;
   m_nPermission  = pData->m_nPermission ;
   m_cPermissionTime = pData->m_cPermissionTime;
}

BOOL CDBUserStylePermissionData::GetAllDBInfo( CADOConn *pADOConn)
{
   ASSERT(pADOConn);

   m_nID          = pADOConn->GetValueInt64(DBUserStylePermission_Key_ID         );
   m_nUserID      = pADOConn->GetValueInt  (DBUserStylePermission_Key_UID        );
   m_nStyleID     = pADOConn->GetValueInt  (DBUserStylePermission_Key_SID        );
   m_nPermission  = pADOConn->GetValueInt  (DBUserStylePermission_Key_nPermission);
   m_cPermissionTime = pADOConn->GetValueString(DBUserStylePermission_Key_cPermissionTime);
   return TRUE;
}

BOOL CDBUserStylePermissionData::InsertAllDBInfo( CADOConn *pADOConn )
{
   CString strSQL = _T("");
   
   strSQL.Format(_T("insert into %s (%s,%s,%s,%s) values(%d,%d,%d,'%s')"),
      DB_TABLE_USER_STYLEPERMISSION,
      DBUserStylePermission_Key_UID        , DBUserStylePermission_Key_SID        ,
      DBUserStylePermission_Key_nPermission,DBUserStylePermission_Key_cPermissionTime ,
      m_nUserID,m_nStyleID,m_nPermission,m_cPermissionTime
      );
   if (pADOConn != NULL)
   {
      BOOL bExecute = pADOConn->ExecuteSQL(strSQL);
      if (bExecute)
      {
         return TRUE;
      }

      return FALSE;
   }
   return FALSE;
}

BOOL CDBUserStylePermissionData::UpdateAllDBInfoByID( CADOConn *pADOConn )
{
   CString strSQL = _T("");

   strSQL.Format(_T("update %s set %s = '%d' where %s = '%lld'"),
      DB_TABLE_USER_STYLEPERMISSION,
      DBUserStylePermission_Key_nPermission,m_nPermission,
      DBUserStylePermission_Key_ID,m_nID
      );

   if (pADOConn != NULL)
   {
      BOOL bExecute = pADOConn->ExecuteSQL(strSQL);
      if (bExecute)
      {
         return TRUE;
      }

      return FALSE;
   }
   return FALSE;
}

BOOL CDBUserStylePermissionData::DelAllDBInfoByID( CADOConn *pADOConn )
{
   CString strSQL = _T("");
   strSQL.Format(_T("delete from %s where %s = '%lld'"),DB_TABLE_USER_STYLEPERMISSION,DBUserStylePermission_Key_ID,m_nID);
   if (pADOConn != NULL)
   {
      BOOL bExecute = pADOConn->ExecuteSQL(strSQL);
      if (bExecute)
      {
         return TRUE;
      }

      return FALSE;
   }
   return FALSE;
}

CDBUserStylePermissionList::CDBUserStylePermissionList( void )
{

}

CDBUserStylePermissionList::~CDBUserStylePermissionList( void )
{

}

void CDBUserStylePermissionList::Copy( CDBUserStylePermissionList *pList )
{
   if (pList != NULL)
   {
      for (int nIndex = 0;nIndex < pList->GetCount();nIndex++)
      {
         CDBUserStylePermissionData *pPlanning =(CDBUserStylePermissionData *)pList->GetAt(pList->FindIndex(nIndex));
         if (pPlanning != NULL)
         {
            AddItem(pPlanning);
         }
      }
   }
}

CDBUserStylePermissionData* CDBUserStylePermissionList::GetItem(int nIndex)
{
   if (nIndex<0||nIndex>=GetCount())
      return NULL;
   return (CDBUserStylePermissionData*)GetAt(FindIndex(nIndex));
}

void CDBUserStylePermissionList::AddItem( CDBUserStylePermissionData *pItem )
{
   ASSERT(pItem != NULL);
   CDBUserStylePermissionData *pPlanning = new CDBUserStylePermissionData;
   pPlanning->Copy(pItem);
   AddTail(pPlanning);
}

void CDBUserStylePermissionList::DeleteItemByIndex( int nIndex )
{
   if (nIndex != NULL)
   {
      CDBUserStylePermissionData *pPlanning =(CDBUserStylePermissionData *)GetAt(FindIndex(nIndex));
      if (pPlanning != NULL)
      {
         RemoveAt(FindIndex(nIndex));
      }

   }
}
