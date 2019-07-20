#include "StdAfx.h"
#include "DBColorInfo.h"

IMPLEMENT_SERIAL(CDBColorInfoData,  CDBProofingAssociatedData, 1)
IMPLEMENT_SERIAL(CDBColorInfoList,  CDataListMid, 1)

CDBColorInfoData::CDBColorInfoData(void)
{
      ResetData();
}


CDBColorInfoData::~CDBColorInfoData(void)
{
}

void CDBColorInfoData::ResetData()
{
   m_nID               =NULL;
   m_nType             =En_Type_Planning;
   m_nAssociatedID     =NULL;
   m_nAssociatedColorID=NULL;
   SetDataType(DAT_COLORINFO);
}

void CDBColorInfoData::Copy( CDBColorInfoData *pData )
{
   ASSERT(pData != NULL);
   CDBProofingAssociatedData::Copy(pData);
   m_nID               =pData->m_nID               ;
   m_nType             =pData->m_nType             ;
   m_nAssociatedID     =pData->m_nAssociatedID     ;
   m_nColorType        =pData->m_nColorType        ;
   m_nAssociatedColorID=pData->m_nAssociatedColorID;

}

BOOL CDBColorInfoData::GetAllDBInfoByID( CADOConn *pADOConn,int nID )
{
   ASSERT(pADOConn);
   CString strSql =_T("");
   strSql.Format(_T("select *from %s where %s = %lld"),DB_TABLE_COLORINFO,DBP_ColorInfo_Key_ID,nID);
   pADOConn->GetRecordSet(strSql);
   if (!pADOConn->adoEOF())
   {
         m_nID               =pADOConn->GetValueInt64(DBP_ColorInfo_Key_ID);
         m_nType             =En_Type_Planning;
         m_nAssociatedID     =pADOConn->GetValueInt64(DBP_ColorInfo_Key_nAssociatedID);
         m_nColorType        =(EM_COLOR)pADOConn->GetValueInt(DBP_ColorInfo_Key_nColorType);
         m_nAssociatedColorID=pADOConn->GetValueInt64(DBP_ColorInfo_Key_nAssociatedColorID);

         return TRUE;
   }
   return FALSE;
}

BOOL CDBColorInfoData::InsertAllDBInfo( CADOConn *pADOConn )
{
   CString strSql = _T("");
   strSql.Format(_T("insert into %s(%s,%s,%s,%s) values(%d,%lld,%d,%lld)"),DB_TABLE_COLORINFO
                    ,DBP_ColorInfo_Key_nType,DBP_ColorInfo_Key_nAssociatedID,DBP_ColorInfo_Key_nColorType,DBP_ColorInfo_Key_nAssociatedColorID
                    ,m_nType,m_nAssociatedID,m_nColorType,m_nAssociatedColorID);
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

BOOL CDBColorInfoData::UpdateAllDBInfoByID( CADOConn *pADOConn )
{
   CString strSQL = _T("");
   strSQL.Format(_T("Update %s set %s = %d,%s = %d,%s = %d,%s = %d,%s = %d\
                    ) where %s=%d"),DB_TABLE_COLORINFO
                    ,DBP_ColorInfo_Key_nType,m_nType,DBP_ColorInfo_Key_nAssociatedID,m_nAssociatedID
                    ,DBP_ColorInfo_Key_nColorType,m_nColorType,DBP_ColorInfo_Key_nAssociatedColorID,m_nAssociatedColorID,DBP_ColorInfo_Key_ID,m_nID);
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

BOOL CDBColorInfoData::DelAllDBInfoByID( CADOConn *pADOConn )
{
   CString strSQL = _T("");
   strSQL.Format(_T("delete from %s where %s = %d"),DB_TABLE_COLORINFO,DBP_BindInfo_Key_ID,m_nID);
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

CDBColorInfoList::CDBColorInfoList( void )
{

}

CDBColorInfoList::~CDBColorInfoList( void )
{

}

void CDBColorInfoList::Copy( CDBColorInfoList *pList )
{
   if (pList != NULL)
   {
      for (int nIndex = 0;nIndex < pList->GetCount();nIndex++)
      {
         CDBColorInfoData *pPlanning =(CDBColorInfoData *)pList->GetAt(pList->FindIndex(nIndex));
         if (pPlanning != NULL)
         {
            AddItem(pPlanning);
         }
      }
   }
}

void CDBColorInfoList::AddItem( CDBColorInfoData *pItem )
{
   ASSERT(pItem != NULL);
   CDBColorInfoData *pPlanning = new CDBColorInfoData;
   pPlanning->Copy(pItem);
   AddTail(pPlanning);
}

void CDBColorInfoList::DeleteItemByIndex( int nIndex )
{
   if (nIndex != NULL)
   {
      CDBColorInfoData *pPlanning =(CDBColorInfoData *)GetAt(FindIndex(nIndex));
      if (pPlanning != NULL)
      {
         RemoveAt(FindIndex(nIndex));
      }

   }
}
