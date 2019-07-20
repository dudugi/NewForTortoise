#include "StdAfx.h"
#include "DBP_PictureInfo.h"

IMPLEMENT_SERIAL(CDBP_PictureInfoData,  CDataMid, 1)
IMPLEMENT_SERIAL(CDBP_PictureInfoList,  CDataListMid, 1)
   CDBP_PictureInfoData::CDBP_PictureInfoData(void)
{
   ResetData();
}


CDBP_PictureInfoData::~CDBP_PictureInfoData(void)
{
}

void CDBP_PictureInfoData::ResetData()
{
   m_nID               =NULL;
   m_nType             =En_Type_Planning;
   m_nAssociatedID     =NULL;
   m_nPicType          =NULL;
   m_nAssociatedFileID =NULL;
   m_strcRemark        =_T("");
   SetDataType(DAT_PICTURE);
}

void CDBP_PictureInfoData::Copy( CDBP_PictureInfoData *pData )
{
   ASSERT(pData != NULL);
   CDataMid::Copy(pData);
   m_nID               =pData->m_nID               ;
   m_nType             =pData->m_nType             ;
   m_nAssociatedID     =pData->m_nAssociatedID     ;
   m_nPicType         =pData->m_nPicType        ;
   m_nAssociatedFileID=pData->m_nAssociatedFileID;
   m_strcRemark       =pData->m_strcRemark;
}

BOOL CDBP_PictureInfoData::GetAllDBInfoByID( CADOConn *pADOConn,int nID )
{
   ASSERT(pADOConn);
   CString strSql =_T("");
   strSql.Format(_T("select *from %s where %s = %s"),DB_TABLE_PICTUREINFO,DBP_PictureInfo_Key_ID,nID);
   pADOConn->GetRecordSet(strSql);
   if (!pADOConn->adoEOF())
   {
      m_nID               =pADOConn->GetValueInt(DBP_PictureInfo_Key_ID);
      m_nType             =En_Type_Planning;
      m_nAssociatedID     =pADOConn->GetValueInt64(DBP_PictureInfo_Key_nAssociatedID);
      m_nPicType         =pADOConn->GetValueInt(DBP_PictureInfo_Key_nPicType);
      m_nAssociatedFileID=pADOConn->GetValueInt64(DBP_PictureInfo_Key_nAssociatedFileID);
      m_strcRemark       =pADOConn->GetValueString(DBP_PictureInfo_Key_cRemark);
      return TRUE;
   }
   return FALSE;
}

BOOL CDBP_PictureInfoData::InsertAllDBInfo( CADOConn *pADOConn )
{
   CString strSql = _T("");
   strSql.Format(_T("insert into %s(%s,%s,%s,%s,%s) values(%d,%d,%d,%d,'%s')"),DB_TABLE_PICTUREINFO
      ,DBP_PictureInfo_Key_nType,DBP_PictureInfo_Key_nAssociatedID,DBP_PictureInfo_Key_nPicType,DBP_PictureInfo_Key_nAssociatedFileID,DBP_PictureInfo_Key_cRemark
      ,m_nType,m_nAssociatedID,m_nPicType,m_nAssociatedFileID,m_strcRemark);
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

BOOL CDBP_PictureInfoData::UpdateAllDBInfoByID( CADOConn *pADOConn )
{
   CString strSQL = _T("");
   strSQL.Format(_T("Update %s set %s = %d,%s = %d,%s = %d,%s = %d,%s = %d,\
                    %s = '%s') where %s=%d"),DB_TABLE_PICTUREINFO
                    ,DBP_PictureInfo_Key_nType,m_nType,DBP_PictureInfo_Key_nAssociatedID,m_nAssociatedID
                    ,DBP_PictureInfo_Key_nPicType,m_nPicType,DBP_PictureInfo_Key_nAssociatedFileID,m_nAssociatedFileID,DBP_PictureInfo_Key_cRemark,m_strcRemark,DBP_PictureInfo_Key_ID,m_nID);
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

BOOL CDBP_PictureInfoData::DelAllDBInfoByID( CADOConn *pADOConn )
{
   CString strSQL = _T("");
   strSQL.Format(_T("delete from %s where %s = %d"),DB_TABLE_PICTUREINFO,DBP_PictureInfo_Key_ID,m_nID);
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

CDBP_PictureInfoList::CDBP_PictureInfoList( void )
{

}

CDBP_PictureInfoList::~CDBP_PictureInfoList( void )
{

}

void CDBP_PictureInfoList::Copy( CDBP_PictureInfoList *pList )
{
   if (pList != NULL)
   {
      for (int nIndex = 0;nIndex < pList->GetCount();nIndex++)
      {
         CDBP_PictureInfoData *pPlanning =(CDBP_PictureInfoData *)pList->GetAt(pList->FindIndex(nIndex));
         if (pPlanning != NULL)
         {
            AddItem(pPlanning);
         }
      }
   }
}

void CDBP_PictureInfoList::AddItem( CDBP_PictureInfoData *pItem )
{
   ASSERT(pItem != NULL);
   CDBP_PictureInfoData *pPlanning = new CDBP_PictureInfoData;
   pPlanning->Copy(pItem);
   AddTail(pPlanning);
}

void CDBP_PictureInfoList::DeleteItemByIndex( int nIndex )
{
   if (nIndex != NULL)
   {

      CDBP_PictureInfoData *pPlanning =(CDBP_PictureInfoData *)GetAt(FindIndex(nIndex));
      if (pPlanning != NULL)
      {
         RemoveAt(FindIndex(nIndex));
      }

   }
}
