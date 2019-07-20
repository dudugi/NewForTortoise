#include "StdAfx.h"
#include "DBKeyDef.h"
#include "DBSampleClothing_FileInfo.h"

IMPLEMENT_SERIAL(CDBSampleClothing_FileInfoData,  CDataMid, 1)
IMPLEMENT_SERIAL(CDBSampleClothing_FileInfoList,  CDataListMid, 1)

CDBSampleClothing_FileInfoData::CDBSampleClothing_FileInfoData(void)
{
   ResetData();
}


CDBSampleClothing_FileInfoData::~CDBSampleClothing_FileInfoData(void)
{
}

void CDBSampleClothing_FileInfoData::ResetData()
{
   m_nID        = 0;
   m_nFileID    = 0;
   m_strBarCode = _T("");
   m_nFileType  = 0;
   SetDataType(DAT_STYLE_FILEINFO);
}

void CDBSampleClothing_FileInfoData::Copy( CDBSampleClothing_FileInfoData *pData )
{
   ASSERT(pData != NULL);
   CDataMid::Copy(pData);

   m_nID        = pData->m_nID         ;
   m_nFileID    = pData->m_nFileID     ;
   m_strBarCode = pData->m_strBarCode  ;
   m_nFileType  = pData->m_nFileType   ;
}

BOOL CDBSampleClothing_FileInfoData::GetAllDBInfo( CADOConn *pADOConn)
{
   ASSERT(pADOConn);

   m_nID             = pADOConn->GetValueInt64  ( DBSampleClothing_FileInfo_ID       );
   m_nFileID         = pADOConn->GetValueInt64  ( DBSampleClothing_FileInfo_nFileID  );
   m_strBarCode      = pADOConn->GetValueString ( DBSampleClothing_FileInfo_cBarCode );
   m_nFileType       = pADOConn->GetValueInt    ( DBSampleClothing_FileInfo_nFileType);

   return TRUE;
}

BOOL CDBSampleClothing_FileInfoData::InsertAllDBInfo(CADOConn *pADOConn)
{
   CString strSQL = _T("");

   strSQL.Format(_T("insert into %s (%s,%s,%s) values('%lld','%s','%d')"),
      DB_TABLE_STYLE_FILEINFO,
      DBSampleClothing_FileInfo_nFileID  , DBSampleClothing_FileInfo_cBarCode ,
      DBSampleClothing_FileInfo_nFileType,
      m_nFileID,m_strBarCode,m_nFileType
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

BOOL CDBSampleClothing_FileInfoData::UpdateAllDBInfoByID(CADOConn *pADOConn)
{
   CString strSQL = _T("");

   strSQL.Format(_T("update %s set %s = '%lld',%s = '%s',%s = '%d' where %s = '%lld'"),
      DB_TABLE_STYLE_FILEINFO,
      DBSampleClothing_FileInfo_nFileID  ,m_nFileID,
      DBSampleClothing_FileInfo_cBarCode ,m_strBarCode,
      DBSampleClothing_FileInfo_nFileType,m_nFileType,
      DBSampleClothing_FileInfo_ID,m_nID
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

BOOL CDBSampleClothing_FileInfoData::SaveDBInfo(CADOConn * pADOConn)
{
   CString strSQL;
   //文件ID是唯一的  
   strSQL.Format(_T("if exists (select * from %s where %s = '%lld')\
                    update %s set %s = '%s',%s = '%d' where %s = '%lld'\
                    else \
                    insert into %s (%s,%s,%s,%s) values('%lld','%s','%d','%d')"),
                    DB_TABLE_STYLE_FILEINFO,
                    DBSampleClothing_FileInfo_nFileID  ,m_nFileID,
                    DB_TABLE_STYLE_FILEINFO,
                    DBSampleClothing_FileInfo_cBarCode ,m_strBarCode,
                    DBSampleClothing_FileInfo_nFileType,m_nFileType,
                    DBSampleClothing_FileInfo_nFileID  ,m_nFileID,
                    DB_TABLE_STYLE_FILEINFO,
                    DBSampleClothing_FileInfo_nFileID  , DBSampleClothing_FileInfo_cBarCode ,
                    DBSampleClothing_FileInfo_nFileType,DBSampleClothing_FileInfo_nSort,
                    m_nFileID,m_strBarCode,m_nFileType,m_nSortID++
                    );

   if (pADOConn != NULL)
   {
      return  pADOConn->ExecuteSQL(strSQL);
   }

   return FALSE;
}

CDBSampleClothing_FileInfoList::CDBSampleClothing_FileInfoList( void )
{

}

CDBSampleClothing_FileInfoList::~CDBSampleClothing_FileInfoList( void )
{

}

void CDBSampleClothing_FileInfoList::Copy( CDBSampleClothing_FileInfoList *pList )
{
   Empty();
   if (pList != NULL)
   {
      for (int nIndex = 0;nIndex < pList->GetCount();nIndex++)
      {
         CDBSampleClothing_FileInfoData *pPlanning =(CDBSampleClothing_FileInfoData *)pList->GetAt(pList->FindIndex(nIndex));
         if (pPlanning != NULL)
         {
            AddItem(pPlanning);
         }
      }
   }
}

CDBSampleClothing_FileInfoData* CDBSampleClothing_FileInfoList::GetItem(int nIndex)
{
   if (nIndex<0||nIndex>=GetCount())
      return NULL;
   return (CDBSampleClothing_FileInfoData*)GetAt(FindIndex(nIndex));   
}

void CDBSampleClothing_FileInfoList::AddItem( CDBSampleClothing_FileInfoData *pItem )
{
   ASSERT(pItem != NULL);
   CDBSampleClothing_FileInfoData *pPlanning = new CDBSampleClothing_FileInfoData;
   pPlanning->Copy(pItem);
   AddTail(pPlanning);
}

void CDBSampleClothing_FileInfoList::DeleteItemByIndex( int nIndex )
{
   if ((nIndex>=0&&nIndex<GetCount()))
   {
      CDBSampleClothing_FileInfoData *pPlanning =(CDBSampleClothing_FileInfoData *)GetAt(FindIndex(nIndex));
      if (pPlanning != NULL)
      {
         RemoveAt(FindIndex(nIndex));
      }

   }
}
