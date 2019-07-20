#include "StdAfx.h"
#include "DBKeyDef_V.h"
#include "DBKuanshi_NextProInfo_V.h"

IMPLEMENT_SERIAL(CDBKuanshi_NextProInfo_VData,  CDataMid, 1)
IMPLEMENT_SERIAL(CDBKuanshi_NextProInfo_VList,  CDataListMid, 1)

CDBKuanshi_NextProInfo_VData::CDBKuanshi_NextProInfo_VData(void)
{
   ResetData();
}


CDBKuanshi_NextProInfo_VData::~CDBKuanshi_NextProInfo_VData(void)
{
}

void CDBKuanshi_NextProInfo_VData::ResetData()
{
   m_strStyleNo     = _T("");
   m_strProcessName = _T("");
   m_strNextUserID  = _T("");
   SetDataType(DAT_STYLE_NEXTPROINFO);
}

void CDBKuanshi_NextProInfo_VData::Copy( CDBKuanshi_NextProInfo_VData *pData )
{
   ASSERT(pData != NULL);
   CDataMid::Copy(pData);
   m_strStyleNo     = pData->m_strStyleNo    ;
   m_strProcessName = pData->m_strProcessName;
   m_strNextUserID  = pData->m_strNextUserID ;
}

BOOL CDBKuanshi_NextProInfo_VData::GetAllDBInfo( CADOConn *pADOConn)
{
   ASSERT(pADOConn);

   m_strStyleNo     = pADOConn->GetValueString(DBKuanshi_NextProInfo_V_key_cKuanhao   );
   m_strProcessName = pADOConn->GetValueString(DBKuanshi_NextProInfo_V_key_cGXName    );
   m_strNextUserID  = pADOConn->GetValueString(DBKuanshi_NextProInfo_V_key_cNextUserID);

   return TRUE;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

CDBKuanshi_NextProInfo_VList::CDBKuanshi_NextProInfo_VList( void )
{

}

CDBKuanshi_NextProInfo_VList::~CDBKuanshi_NextProInfo_VList( void )
{

}

void CDBKuanshi_NextProInfo_VList::Copy( CDBKuanshi_NextProInfo_VList *pList )
{
   Empty();
   if (pList != NULL)
   {
      for (int nIndex = 0;nIndex < pList->GetCount();nIndex++)
      {
         CDBKuanshi_NextProInfo_VData *pPlanning =(CDBKuanshi_NextProInfo_VData *)pList->GetAt(pList->FindIndex(nIndex));
         if (pPlanning != NULL)
         {
            AddItem(pPlanning);
         }
      }
   }
}

CDBKuanshi_NextProInfo_VData* CDBKuanshi_NextProInfo_VList::GetItem(int nIndex)
{
   if (nIndex<0||nIndex>=GetCount())
      return NULL;
   return (CDBKuanshi_NextProInfo_VData*)GetAt(FindIndex(nIndex));   
}

void CDBKuanshi_NextProInfo_VList::AddItem( CDBKuanshi_NextProInfo_VData *pItem )
{
   ASSERT(pItem != NULL);
   CDBKuanshi_NextProInfo_VData *pPlanning = new CDBKuanshi_NextProInfo_VData;
   pPlanning->Copy(pItem);
   AddTail(pPlanning);
}

void CDBKuanshi_NextProInfo_VList::DeleteItemByIndex( int nIndex )
{
   if ((nIndex>=0&&nIndex<GetCount()))
   {
      CDBKuanshi_NextProInfo_VData *pPlanning =(CDBKuanshi_NextProInfo_VData *)GetAt(FindIndex(nIndex));
      if (pPlanning != NULL)
      {
         RemoveAt(FindIndex(nIndex));
      }

   }
}

