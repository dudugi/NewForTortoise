#include "StdAfx.h"
#include "DBKeyDef.h"
#include "DBConfig_TagName.h"

IMPLEMENT_SERIAL(CDBConfig_TagNameData,  CDataMid, 1)
IMPLEMENT_SERIAL(CDBConfig_TagNameList,  CDataListMid, 1)

std::shared_ptr<CDBConfig_TagNameList> CDBConfig_TagNameList::sm_inst;

CDBConfig_TagNameData::CDBConfig_TagNameData(void)
{
   ResetData();
}


CDBConfig_TagNameData::~CDBConfig_TagNameData(void)
{
}

void CDBConfig_TagNameData::ResetData()
{
   m_strTagName     = _T("");
   m_strDisplayName = _T("");
   m_nHide = 0;//ÊÇ·ñÒþ²Ø yangjr 2019/07/09   
   SetDataType(DAT_CONFIG_TAGNAME);
}

void CDBConfig_TagNameData::Copy( CDBConfig_TagNameData *pData )
{
   ASSERT(pData != NULL);
   CDataMid::Copy(pData);
   m_strTagName     = pData->m_strTagName    ;
   m_strDisplayName = pData->m_strDisplayName;
   m_nHide= pData->m_nHide;//ÊÇ·ñÒþ²Ø yangjr 2019/07/09   
}

BOOL CDBConfig_TagNameData::GetAllDBInfo( CADOConn *pADOConn)
{
   ASSERT(pADOConn);

   m_strTagName     = pADOConn->GetValueString(DBConfig_TagName_Key_cTagName     );
   m_strDisplayName = pADOConn->GetValueString(DBConfig_TagName_Key_cDisplayName );
   m_nHide = pADOConn->GetValueInt(DBConfig_TagName_Key_nHide );
   return TRUE;
}

BOOL CDBConfig_TagNameData::UpdateAllDBInfo(CADOConn * pADOConn)
{
   ASSERT(pADOConn != NULL);
   ASSERT(m_strTagName.IsEmpty());
   CString strSQL = GetUpdateSQL();
   return pADOConn->ExecuteSQL(strSQL);
}

CString CDBConfig_TagNameData::GetUpdateSQL()
{
   CString strSQL;
   strSQL.Format(_T("update %s set %s = '%s',%s = '%d' where %s = '%s'"),
      DB_TABLE_CONFIG_TAGNAME,
      DBConfig_TagName_Key_cDisplayName,m_strDisplayName,
      DBConfig_TagName_Key_nHide,m_nHide,
      DBConfig_TagName_Key_cTagName,m_strTagName);
   return strSQL;
}

CString CDBConfig_TagNameData::GetInsertSQL()
{
   CString strSQL;
   strSQL.Format(_T("insert into %s (%s,%s,%s) values('%s','%s','%d')"),
      DB_TABLE_CONFIG_TAGNAME,
      DBConfig_TagName_Key_cTagName,DBConfig_TagName_Key_cDisplayName,
      DBConfig_TagName_Key_nHide,
      m_strTagName,m_strDisplayName,m_nHide);
   return strSQL;
}

BOOL CDBConfig_TagNameData::InsertAllDBInfo(CADOConn * pADOConn)
{
   ASSERT(pADOConn != NULL);
   ASSERT(m_strTagName.IsEmpty());

   CString strSQL = GetInsertSQL();

   return pADOConn->ExecuteSQL(strSQL);
}

CDBConfig_TagNameList::CDBConfig_TagNameList( void )
{

}

CDBConfig_TagNameList::~CDBConfig_TagNameList( void )
{

}

void CDBConfig_TagNameList::Copy( CDBConfig_TagNameList *pList )
{
   Empty();
   if (pList != NULL)
   {
      for (int nIndex = 0;nIndex < pList->GetCount();nIndex++)
      {
         CDBConfig_TagNameData *pPlanning =(CDBConfig_TagNameData *)pList->GetAt(pList->FindIndex(nIndex));
         if (pPlanning != NULL)
         {
            AddItem(pPlanning);
         }
      }
   }
}

CDBConfig_TagNameData* CDBConfig_TagNameList::GetItem(int nIndex)
{
   if (nIndex<0||nIndex>=GetCount())
      return NULL;
   return (CDBConfig_TagNameData*)GetAt(FindIndex(nIndex));
}

CDBConfig_TagNameData* CDBConfig_TagNameList::GetItemByTagName(const CString & strTagName)
{
   for (int nIndex = 0;nIndex < GetCount();++nIndex)
   {
      CDBConfig_TagNameData *pData =(CDBConfig_TagNameData *)GetAt(FindIndex(nIndex));
      if (pData != NULL && pData->m_strTagName == strTagName)
      {
         return pData;
      }
   }
   return NULL;
}

void CDBConfig_TagNameList::AddItem( CDBConfig_TagNameData *pItem )
{
   ASSERT(pItem != NULL);
   CDBConfig_TagNameData *pPlanning = new CDBConfig_TagNameData;
   pPlanning->Copy(pItem);
   AddTail(pPlanning);
}

void CDBConfig_TagNameList::DeleteItemByIndex( int nIndex )
{
   if ((nIndex>=0&&nIndex<GetCount()))
   {
      CDBConfig_TagNameData *pPlanning =(CDBConfig_TagNameData *)GetAt(FindIndex(nIndex));
      if (pPlanning != NULL)
      {
         RemoveAt(FindIndex(nIndex));
      }

   }
}

CString CDBConfig_TagNameList::GetItemDisplayName(const CString & strTagName)
{
   auto pData =GetItemByTagName(strTagName);
   if (NULL != pData)
   {
      return pData->m_strDisplayName.IsEmpty() ? pData->m_strTagName : pData->m_strDisplayName;
   }
   return strTagName;
}

BOOL CDBConfig_TagNameList::GetListFromDB(CADOConn * pADOConn)
{
   Empty();
   CString strSQL;
   strSQL.Format(_T("select * from %s"),DB_TABLE_CONFIG_TAGNAME);
   pADOConn->GetRecordSet(strSQL);
   while(!pADOConn->adoEOF())
   {
      CDBConfig_TagNameData * pNewData = new CDBConfig_TagNameData;
      pNewData->GetAllDBInfo(pADOConn);
      AddTail(pNewData);
      pADOConn->MoveNext();
   }
   return TRUE;
}

CDBConfig_TagNameList * CDBConfig_TagNameList::Instance()
{
   if(sm_inst.get() == 0)
      sm_inst = shared_ptr<CDBConfig_TagNameList>(new CDBConfig_TagNameList);

   return sm_inst.get();
}

