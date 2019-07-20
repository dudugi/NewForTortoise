#include "StdAfx.h"
#include "DBKeyDef.h"
#include "DBSampleClothing_FileInfo_V.h"
#include "DBKeyDef_V.h"

IMPLEMENT_SERIAL(CDBSampleClothing_FileInfo_VData,  CDataMid, 1)
IMPLEMENT_SERIAL(CDBSampleClothing_FileInfo_VList,  CDataListMid, 1)

CDBSampleClothing_FileInfo_VData::CDBSampleClothing_FileInfo_VData(void)
{
   ResetData();
}


CDBSampleClothing_FileInfo_VData::~CDBSampleClothing_FileInfo_VData(void)
{
}

void CDBSampleClothing_FileInfo_VData::ResetData()
{
   m_ID               = 0;
   m_nFileID          = 0;
   m_strBarCode       = _T("");
   m_nFileType        = 0;
   m_strRelativePath  = _T("");
   m_strUploadUserID  = _T("");
   m_strUploadTime    = _T("");
   m_strFileMD5       = _T("");
   m_strFileName      = _T("");
   m_strFileExtension = _T("");
   m_nFileSize        = 0;
   m_strRemark        = _T("");



   SetDataType(DAT_STYLE_FILEINFO);
}

void CDBSampleClothing_FileInfo_VData::Copy( CDBSampleClothing_FileInfo_VData *pData )
{
   ASSERT(pData != NULL);
   CDataMid::Copy(pData);

   m_ID               = pData->m_ID               ;
   m_nFileID          = pData->m_nFileID          ;
   m_strBarCode       = pData->m_strBarCode       ;
   m_nFileType        = pData->m_nFileType        ;
   m_strRelativePath  = pData->m_strRelativePath  ;
   m_strUploadUserID  = pData->m_strUploadUserID  ;
   m_strUploadTime    = pData->m_strUploadTime    ;
   m_strFileMD5       = pData->m_strFileMD5       ;
   m_strFileName      = pData->m_strFileName      ;
   m_strFileExtension = pData->m_strFileExtension ;
   m_nFileSize        = pData->m_nFileSize        ;
   m_strRemark        = pData->m_strRemark        ;
}

BOOL CDBSampleClothing_FileInfo_VData::GetAllDBInfo( CADOConn *pADOConn)
{
   ASSERT(pADOConn);

   m_ID              = pADOConn->GetValueInt64 (DBSampleClothing_V_key_ID             );
   m_nFileID         = pADOConn->GetValueInt64 (DBSampleClothing_V_key_nFileID        );
   m_strBarCode      = pADOConn->GetValueString(DBSampleClothing_V_key_cBarCode       );
   m_nFileType       = pADOConn->GetValueInt64 (DBSampleClothing_V_key_nFileType      );
   m_strRelativePath = pADOConn->GetValueString(DBSampleClothing_V_key_cRelativePath  );
   m_strUploadUserID = pADOConn->GetValueString(DBSampleClothing_V_key_cUploadUserID  );
   m_strUploadTime   = pADOConn->GetValueString(DBSampleClothing_V_key_cUploadTime    );
   m_strFileMD5      = pADOConn->GetValueString(DBSampleClothing_V_key_cFileMD5       );
   m_strFileName     = pADOConn->GetValueString(DBSampleClothing_V_key_cFileName      );
   m_strFileExtension= pADOConn->GetValueString(DBSampleClothing_V_key_cFileExtension );
   m_nFileSize       = pADOConn->GetValueInt64 (DBSampleClothing_V_key_nFileSize      );
   m_strRemark       = pADOConn->GetValueString(DBSampleClothing_V_key_cRemark        );

   return TRUE;
}

CDBSampleClothing_FileInfo_VList::CDBSampleClothing_FileInfo_VList( void )
{

}

CDBSampleClothing_FileInfo_VList::~CDBSampleClothing_FileInfo_VList( void )
{

}

void CDBSampleClothing_FileInfo_VList::Copy( CDBSampleClothing_FileInfo_VList *pList )
{
   Empty();
   if (pList != NULL)
   {
      for (int nIndex = 0;nIndex < pList->GetCount();nIndex++)
      {
         CDBSampleClothing_FileInfo_VData *pPlanning =(CDBSampleClothing_FileInfo_VData *)pList->GetAt(pList->FindIndex(nIndex));
         if (pPlanning != NULL)
         {
            AddItem(pPlanning);
         }
      }
   }
}

CDBSampleClothing_FileInfo_VData* CDBSampleClothing_FileInfo_VList::GetItem(int nIndex)
{
   if (nIndex<0||nIndex>=GetCount())
      return NULL;
   return (CDBSampleClothing_FileInfo_VData*)GetAt(FindIndex(nIndex));   
}

void CDBSampleClothing_FileInfo_VList::AddItem( CDBSampleClothing_FileInfo_VData *pItem )
{
   ASSERT(pItem != NULL);
   CDBSampleClothing_FileInfo_VData *pPlanning = new CDBSampleClothing_FileInfo_VData;
   pPlanning->Copy(pItem);
   AddTail(pPlanning);
}

void CDBSampleClothing_FileInfo_VList::DeleteItemByIndex( int nIndex )
{
   if ((nIndex>=0&&nIndex<GetCount()))
   {
      CDBSampleClothing_FileInfo_VData *pPlanning =(CDBSampleClothing_FileInfo_VData *)GetAt(FindIndex(nIndex));
      if (pPlanning != NULL)
      {
         RemoveAt(FindIndex(nIndex));
      }

   }
}

void CDBSampleClothing_FileInfo_VList::GetStyleFileInfo(CADOConn* pAdo,CString strStyleNo,vector<CDBSampleClothing_FileInfo_VData*>& vecFileInfo)
{
  ASSERT(pAdo != nullptr);
  ASSERT(!strStyleNo.IsEmpty());
  vecFileInfo.clear();
  CString strSql;
  strSql.Format(_T("select * from V_StyleFileInfo where cStyleNo = '%s'"),strStyleNo);
  pAdo->GetRecordSet(strSql);
  while(!pAdo->adoEOF())
  {
     CDBSampleClothing_FileInfo_VData* pData = new CDBSampleClothing_FileInfo_VData;
     pData->GetAllDBInfo(pAdo);
     vecFileInfo.push_back(pData);
     pAdo->MoveNext();
  }
}
