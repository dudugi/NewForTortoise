#include "StdAfx.h"
#include "DBKeyDef_V.h"
#include "DBUserStylePermission_V.h"

IMPLEMENT_SERIAL(CDBUserStylePermission_VData,  CDataMid, 1)
IMPLEMENT_SERIAL(CDBUserStylePermission_VList,  CDataListMid, 1)

CDBUserStylePermission_VData::CDBUserStylePermission_VData(void)
{
   ResetData();
}


CDBUserStylePermission_VData::~CDBUserStylePermission_VData(void)
{
}

void CDBUserStylePermission_VData::ResetData()
{
   m_strUserID    = _T("");
   m_strStyleNo   = _T("");
   m_nPermission  = 0     ;
   m_nFixPermission = 0;
   m_nUserType = 0;
   SetDataType(DAT_USERSTYLE_PERMISSION);
}

void CDBUserStylePermission_VData::Copy( CDBUserStylePermission_VData *pData )
{
   ASSERT(pData != NULL);
   CDataMid::Copy(pData);
   m_strUserID    = pData->m_strUserID   ;
   m_strStyleNo   = pData->m_strStyleNo  ;
   m_nPermission  = pData->m_nPermission ;
   m_nFixPermission = pData->m_nFixPermission;
   m_nUserType      = pData->m_nUserType;
   m_cPermissionTime = pData->m_cPermissionTime;
}

BOOL CDBUserStylePermission_VData::GetAllDBInfo( CADOConn *pADOConn)
{
   ASSERT(pADOConn);

   m_strUserID    = pADOConn->GetValueString(DBUserStylePermission_V_key_cUserID     );
   m_strStyleNo   = pADOConn->GetValueString(DBUserStylePermission_V_key_cKuanhao    );
   m_nPermission  = pADOConn->GetValueInt   (DBUserStylePermission_V_key_nPermission );
   m_nFixPermission = pADOConn->GetValueInt (DBUserStylePermission_V_key_FixPermission);
   m_nUserType      = pADOConn->GetValueInt (DBUserStylePermission_V_key_nUserType   );
   m_cPermissionTime = pADOConn->GetValueString(DBUserStylePermission_V_key_nPermissionTime);

   return TRUE;
}

CDBUserStylePermission_VList::CDBUserStylePermission_VList( void )
{

}

CDBUserStylePermission_VList::~CDBUserStylePermission_VList( void )
{

}

void CDBUserStylePermission_VList::Copy( CDBUserStylePermission_VList *pList )
{
   Empty();
   if (pList != NULL)
   {
      for (int nIndex = 0;nIndex < pList->GetCount();nIndex++)
      {
         CDBUserStylePermission_VData *pPlanning =(CDBUserStylePermission_VData *)pList->GetAt(pList->FindIndex(nIndex));
         if (pPlanning != NULL)
         {
            AddItem(pPlanning);
         }
      }
   }
}

CDBUserStylePermission_VData* CDBUserStylePermission_VList::GetItem(int nIndex)
{
   if (nIndex<0||nIndex>=GetCount())
      return NULL;
   return (CDBUserStylePermission_VData*)GetAt(FindIndex(nIndex));   
}

CDBUserStylePermission_VData* CDBUserStylePermission_VList::GetItemByUserID(const CString & strUserID)
{
   CDBUserStylePermission_VData * pItem = NULL;
   if (!strUserID.IsEmpty())
   {
      int count = GetCount();
      for(int i=0;i< count;++i)
      {
         CDBUserStylePermission_VData * pObject = GetItem(i);
         if(NULL != pObject && 0 == pObject->m_strUserID.Compare(strUserID))
         {
            pItem = pObject;
            break;
         }
      }
   }

   return pItem;
}

int CDBUserStylePermission_VList::GetIndexByUserID( const CString & strUserID )
{
   CDBUserStylePermission_VData * pItem = NULL;
   if (!strUserID.IsEmpty())
   {
      int count = GetCount();
      for(int i=0;i< count;++i)
      {
         CDBUserStylePermission_VData * pObject = GetItem(i);
         if(NULL != pObject && 0 == pObject->m_strUserID.Compare(strUserID))
         {
            return i;
         }
      }
   }

   return -1;
}

void CDBUserStylePermission_VList::AddItem( CDBUserStylePermission_VData *pItem )
{
   ASSERT(pItem != NULL);
   CDBUserStylePermission_VData *pPlanning = new CDBUserStylePermission_VData;
   pPlanning->Copy(pItem);
   AddTail(pPlanning);
}

void CDBUserStylePermission_VList::DeleteItemByIndex( int nIndex )
{
   if ((nIndex>=0&&nIndex<GetCount()))
   {
      CDBUserStylePermission_VData *pPlanning =(CDBUserStylePermission_VData *)GetAt(FindIndex(nIndex));
      if (pPlanning != NULL)
      {
         RemoveAt(FindIndex(nIndex));
      }

   }
}

void CDBUserStylePermission_VList::DeleteItemByUserID( CString strUserID )
{
    int nIndex = GetIndexByUserID(strUserID);
    if (nIndex != -1)
    {
       DeleteItemByIndex(nIndex);
    }
}

//对应款式是否有删除权限 yangjr 2019/05/20
BOOL CDBUserStylePermission_VList::IsStyleHaveDeletePermission(CADOConn *pADOConn,CString strLoadUserID,std::vector<CString>vecKuanhao)
{
   if (!pADOConn)
   {
      return FALSE;
   }
   CString strSQL = _T("");
   CString strStyleNo = _T("");
   int size = vecKuanhao.size();

   int count = 0;
   for (int i=0;i<size;++i)
   {
      if (!strStyleNo.IsEmpty())
      {
         strStyleNo += _T(",");
      }
      CString strOneKuan;
      strOneKuan.Format(_T("'%s'"),vecKuanhao[i]);
      strStyleNo += strOneKuan;
      ++count;
      if (i==size-1)//到队尾
      {
         strSQL.Format(_T("select count(*) as num from %s where %s='%s' and ((%s & 4)=0 and (%s & 4)=0)and ((%s >= GETDATE()) or (%s ='')) and %s in(%s)") 
            ,DB_VIEW_USERSTYLE_PERMISSION,DBUserStylePermission_V_key_cUserID,strLoadUserID,
            DBUserStylePermission_V_key_nPermission,DBUserStylePermission_V_key_FixPermission,
            DBUserStylePermission_V_key_nPermissionTime,DBUserStylePermission_V_key_nPermissionTime,
            DBUserStylePermission_V_key_cKuanhao,strStyleNo);
         pADOConn->GetRecordSet(strSQL);
         if(!pADOConn->adoEOF())
         {
            if (pADOConn->GetValueInt(_T("num"))>0)
            {
               return FALSE;
            }
         }
      }else if (count==50)
      {
         strSQL.Format(_T("select count(*) as num from %s where %s='%s' and ((%s & 4)=0 and (%s & 4)=0)and((%s >= GETDATE()) or (%s = '')) and %s in(%s)")
            ,DB_VIEW_USERSTYLE_PERMISSION,DBUserStylePermission_V_key_cUserID,strLoadUserID,
            DBUserStylePermission_V_key_nPermission,DBUserStylePermission_V_key_FixPermission,
            DBUserStylePermission_V_key_nPermissionTime,DBUserStylePermission_V_key_nPermissionTime,
            DBUserStylePermission_V_key_cKuanhao,strStyleNo);
         pADOConn->GetRecordSet(strSQL);
         if(!pADOConn->adoEOF())
         {
            if (pADOConn->GetValueInt(_T("num"))>0)
            {
               return FALSE;
            }      
         }
         count = 0;
      }
   }
   
   return TRUE;
}
//根据款号获取权限list yangjr 2019/05/22
BOOL CDBUserStylePermission_VList::GetDataByStyleNo(CADOConn *pADOConn,CString strStyleNo)
{
   Empty();
   CString strSQL = _T("");
   strSQL.Format(_T("select * from %s where %s = '%s'"),DB_VIEW_USERSTYLE_PERMISSION,DBUserStylePermission_V_key_cKuanhao,strStyleNo);
   pADOConn->GetRecordSet(strSQL);
   while(!pADOConn->adoEOF())
   {
      CDBUserStylePermission_VData oData;
      oData.GetAllDBInfo(pADOConn);
      AddItem(&oData);
      pADOConn->MoveNext();
   }
   return TRUE;
}


BOOL CDBUserStylePermission_VList::SimpleHasPermision(CADOConn *pADOConn, 
   const CString &strStyleNo, const CString &strLoadUserID)
{
   CString strSQL;
   strSQL.Format(_T("select * from %s where %s = '%s' and %s = '%s'"),DB_VIEW_USERSTYLE_PERMISSION,
      DBUserStylePermission_V_key_cKuanhao,strStyleNo,
      DBUserStylePermission_V_key_cUserID, strLoadUserID);
   pADOConn->GetRecordSet(strSQL);
   if (!pADOConn->adoEOF())
      return TRUE;
   return FALSE;
}