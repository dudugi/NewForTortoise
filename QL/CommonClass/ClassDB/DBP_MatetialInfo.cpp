#include "StdAfx.h"
#include "DBP_MatetialInfo.h"

IMPLEMENT_SERIAL(CDBP_MatetialInfoData,  CDataMid, 1)
IMPLEMENT_SERIAL(CDBP_MatetialInfoList,  CDataListMid, 1)

   CDBP_MatetialInfoData::CDBP_MatetialInfoData(void)
{
   ResetData();
}


CDBP_MatetialInfoData::~CDBP_MatetialInfoData(void)
{
}

void CDBP_MatetialInfoData::ResetData()
{
   m_nID               =NULL;
   m_nType             =En_Type_Planning;
   m_nAssociatedID     =NULL;
   m_strAssociatedMaterialID=_T("");
   SetDataType(DAT_MATETIALINfO);
}

void CDBP_MatetialInfoData::Copy( CDBP_MatetialInfoData *pData )
{
   ASSERT(pData != NULL);
   CDataMid::Copy(pData);
   m_nID               =pData->m_nID               ;
   m_nType             =pData->m_nType             ;
   m_nAssociatedID     =pData->m_nAssociatedID     ;
   m_strAssociatedMaterialID=pData->m_strAssociatedMaterialID;

}

BOOL CDBP_MatetialInfoData::GetAllDBInfoByID( CADOConn *pADOConn,int nID )
{
   ASSERT(pADOConn);
   CString strSql =_T("");
   strSql.Format(_T("select *from %s where %s = %s"),DB_TABLE_MATERIALINFO,DBP_MatetialInfo_Key_ID,nID);
   pADOConn->GetRecordSet(strSql);
   if (!pADOConn->adoEOF())
   {
      m_nID               =pADOConn->GetValueInt64(DBP_MatetialInfo_Key_ID);
      m_nType             =En_Type_Planning;
      m_nAssociatedID     =pADOConn->GetValueInt64(DBP_MatetialInfo_Key_nAssociatedID);
      m_strAssociatedMaterialID=pADOConn->GetValueString(DBP_MatetialInfo_Key_nAssociatedMaterialID);

      return TRUE;
   }
   return FALSE;
}

BOOL CDBP_MatetialInfoData::InsertAllDBInfo( CADOConn *pADOConn )
{
   CString strSql = _T("");
   strSql.Format(_T("insert into %s(%s,%s,%s,%s) values(%d,%d,%d,'%s')"),DB_TABLE_MATERIALINFO,DBP_MatetialInfo_Key_ID
      ,DBP_MatetialInfo_Key_nType,DBP_MatetialInfo_Key_nAssociatedID,DBP_MatetialInfo_Key_nAssociatedMaterialID
      ,m_nID,m_nType,m_nAssociatedID,m_strAssociatedMaterialID);
   if (pADOConn != NULL)
   {
      BOOL bExecute = pADOConn->ExecuteSQL(strSql);
      if (bExecute)
      {
         return TRUE;
      }

      return FALSE;
   }
   return FALSE;
}

BOOL CDBP_MatetialInfoData::UpdateAllDBInfoByID( CADOConn *pADOConn )
{
   CString strSQL = _T("");
   strSQL.Format(_T("Update %s set %s = %d,%s = %d,%s = %d,%s = '%s'\
                    ) where %s=%d"),DB_TABLE_MATERIALINFO
                    ,DBP_MatetialInfo_Key_nType,m_nType,DBP_MatetialInfo_Key_nAssociatedID,m_nAssociatedID
                    ,DBP_MatetialInfo_Key_nAssociatedMaterialID,m_strAssociatedMaterialID,DBP_MatetialInfo_Key_ID,m_nID);
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

BOOL CDBP_MatetialInfoData::DelAllDBInfoByID( CADOConn *pADOConn )
{
   CString strSQL = _T("");
   strSQL.Format(_T("delete from %s where %s = %d"),DB_TABLE_MATERIALINFO,DBP_MatetialInfo_Key_ID,m_nID);
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

CDBP_MatetialInfoList::CDBP_MatetialInfoList( void )
{

}

CDBP_MatetialInfoList::~CDBP_MatetialInfoList( void )
{

}

void CDBP_MatetialInfoList::Copy( CDBP_MatetialInfoList *pList )
{
   if (pList != NULL)
   {
      for (int nIndex = 0;nIndex < pList->GetCount();nIndex++)
      {
         CDBP_MatetialInfoData *pPlanning =(CDBP_MatetialInfoData *)pList->GetAt(pList->FindIndex(nIndex));
         if (pPlanning != NULL)
         {
            AddItem(pPlanning);
         }
      }
   }
}

void CDBP_MatetialInfoList::AddItem( CDBP_MatetialInfoData *pItem )
{
   ASSERT(pItem != NULL);
   CDBP_MatetialInfoData *pPlanning = new CDBP_MatetialInfoData;
   pPlanning->Copy(pItem);
   AddTail(pPlanning);
}

void CDBP_MatetialInfoList::DeleteItemByIndex( int nIndex )
{
   if (nIndex != NULL)
   {
      CDBP_MatetialInfoData *pPlanning =(CDBP_MatetialInfoData *)GetAt(FindIndex(nIndex));
      if (pPlanning != NULL)
      {
         RemoveAt(FindIndex(nIndex));
      }

   }
}
