#include "StdAfx.h"
#include "DBKeyDef.h"
#include "DBStyle_FileInfo.h"

IMPLEMENT_SERIAL(CDBStyle_FileInfoData,  CDataMid, 1)
IMPLEMENT_SERIAL(CDBStyle_FileInfoList,  CDataListMid, 1)

CDBStyle_FileInfoData::CDBStyle_FileInfoData(void)
{
   ResetData();
}


CDBStyle_FileInfoData::~CDBStyle_FileInfoData(void)
{
}

void CDBStyle_FileInfoData::ResetData()
{
   m_nID        = 0;
   m_nFileID    = 0;
   m_strStyleNo = _T("");
   m_nFileType  = 0;
   SetDataType(DAT_STYLE_FILEINFO);
}

void CDBStyle_FileInfoData::Copy( CDBStyle_FileInfoData *pData )
{
   ASSERT(pData != NULL);
   CDataMid::Copy(pData);

   m_nID        = pData->m_nID         ;
   m_nFileID    = pData->m_nFileID     ;
   m_strStyleNo = pData->m_strStyleNo  ;
   m_nFileType  = pData->m_nFileType   ;
}

BOOL CDBStyle_FileInfoData::GetAllDBInfo( CADOConn *pADOConn)
{
   ASSERT(pADOConn);

   m_nID             = pADOConn->GetValueInt64  ( DBStyle_FileInfo_ID       );
   m_nFileID         = pADOConn->GetValueInt64  ( DBStyle_FileInfo_nFileID  );
   m_strStyleNo      = pADOConn->GetValueString ( DBStyle_FileInfo_cStyleNo );
   m_nFileType       = pADOConn->GetValueInt    ( DBStyle_FileInfo_nFileType);

   return TRUE;
}

BOOL CDBStyle_FileInfoData::InsertAllDBInfo(CADOConn *pADOConn)
{
   CString strSQL = _T("");

   strSQL.Format(_T("insert into %s (%s,%s,%s) values('%lld','%s','%d')"),
      DB_TABLE_STYLE_FILEINFO,
      DBStyle_FileInfo_nFileID  , DBStyle_FileInfo_cStyleNo ,
      DBStyle_FileInfo_nFileType,
      m_nFileID,m_strStyleNo,m_nFileType
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

BOOL CDBStyle_FileInfoData::UpdateAllDBInfoByID(CADOConn *pADOConn)
{
   CString strSQL = _T("");

   strSQL.Format(_T("update %s set %s = '%lld',%s = '%s',%s = '%d' where %s = '%lld'"),
      DB_TABLE_STYLE_FILEINFO,
      DBStyle_FileInfo_nFileID  ,m_nFileID,
      DBStyle_FileInfo_cStyleNo ,m_strStyleNo,
      DBStyle_FileInfo_nFileType,m_nFileType,
      DBStyle_FileInfo_ID,m_nID
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

BOOL CDBStyle_FileInfoData::SaveDBInfo(CADOConn * pADOConn)
{
   CString strSQL;
   //文件ID是唯一的  
   strSQL.Format(_T("if exists (select * from %s where %s = '%lld')\
                    update %s set %s = '%s',%s = '%d' where %s = '%lld'\
                    else \
                    insert into %s (%s,%s,%s,%s) values('%lld','%s','%d','%d')"),
                    DB_TABLE_STYLE_FILEINFO,
                    DBStyle_FileInfo_nFileID  ,m_nFileID,
                    DB_TABLE_STYLE_FILEINFO,
                    DBStyle_FileInfo_cStyleNo ,m_strStyleNo,
                    DBStyle_FileInfo_nFileType,m_nFileType,
                    DBStyle_FileInfo_nFileID  ,m_nFileID,
                    DB_TABLE_STYLE_FILEINFO,
                    DBStyle_FileInfo_nFileID  , DBStyle_FileInfo_cStyleNo ,
                    DBStyle_FileInfo_nFileType,DBStyle_FileInfo_nSort,
                    m_nFileID,m_strStyleNo,m_nFileType,m_nSortID++
                    );

   if (pADOConn != NULL)
   {
      return  pADOConn->ExecuteSQL(strSQL);
   }

   return FALSE;
}

CDBStyle_FileInfoList::CDBStyle_FileInfoList( void )
{

}

CDBStyle_FileInfoList::~CDBStyle_FileInfoList( void )
{

}

void CDBStyle_FileInfoList::Copy( CDBStyle_FileInfoList *pList )
{
   Empty();
   if (pList != NULL)
   {
      for (int nIndex = 0;nIndex < pList->GetCount();nIndex++)
      {
         CDBStyle_FileInfoData *pPlanning =(CDBStyle_FileInfoData *)pList->GetAt(pList->FindIndex(nIndex));
         if (pPlanning != NULL)
         {
            AddItem(pPlanning);
         }
      }
   }
}

CDBStyle_FileInfoData* CDBStyle_FileInfoList::GetItem(int nIndex)
{
   if (nIndex<0||nIndex>=GetCount())
      return NULL;
   return (CDBStyle_FileInfoData*)GetAt(FindIndex(nIndex));   
}

void CDBStyle_FileInfoList::AddItem( CDBStyle_FileInfoData *pItem )
{
   ASSERT(pItem != NULL);
   CDBStyle_FileInfoData *pPlanning = new CDBStyle_FileInfoData;
   pPlanning->Copy(pItem);
   AddTail(pPlanning);
}

void CDBStyle_FileInfoList::DeleteItemByIndex( int nIndex )
{
   if ((nIndex>=0&&nIndex<GetCount()))
   {
      CDBStyle_FileInfoData *pPlanning =(CDBStyle_FileInfoData *)GetAt(FindIndex(nIndex));
      if (pPlanning != NULL)
      {
         RemoveAt(FindIndex(nIndex));
      }

   }
}
