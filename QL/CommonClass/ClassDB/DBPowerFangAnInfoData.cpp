#include "StdAfx.h"
#include "DBPowerFangAnInfoData.h"
#include "StdAfx.h"
#include "DBDataDictionary.h"

#include "DBKeyDef.h"
#include "DBKeyDef_V.h"
#include "DBKeyDef_Cust.h"
std::shared_ptr<CDBPowerFangAnInfoDataList> CDBPowerFangAnInfoDataList::sm_inst;

CDBPowerFangAnInfoData::CDBPowerFangAnInfoData(void)
{
   ResetData();
}

CDBPowerFangAnInfoData::~CDBPowerFangAnInfoData(void)
{

}

void CDBPowerFangAnInfoData::ResetData()
{
   m_strcFangAnName = _T("");
   m_strcFangAnPower = _T("");
   m_nID = 0;
   m_nNum = 0;
   SetDataType(DAT_VPERSON);
}

void CDBPowerFangAnInfoData::Copy( CDBPowerFangAnInfoData * pData )
{
   ASSERT(NULL != pData); 
   CDataMid::Copy(pData);
   m_strcFangAnName  = pData->m_strcFangAnName;
   m_strcFangAnPower = pData->m_strcFangAnPower;
   m_nID             = pData->m_nID;
   m_nNum            = pData->m_nNum;
}

void CDBPowerFangAnInfoData::ToDBData( CDBPowerFangAnInfoData & oDBData)
{
   oDBData.m_strcFangAnName = m_strcFangAnName;
   oDBData.m_strcFangAnPower = m_strcFangAnPower;
   oDBData.m_nID             = m_nID;
   oDBData.m_nNum            = m_nNum;

}

BOOL CDBPowerFangAnInfoData::GetAllDBInfo( CADOConn *pADOConn )
{
   ASSERT(NULL != pADOConn);
   BOOL bRet = FALSE;
   if (NULL != pADOConn)
   {
      m_nID                = pADOConn->GetValueInt64(DBFangAn_Power_Key_ID);
      m_strcFangAnName		=	pADOConn->GetValueString(DBFangAn_Power_Key_FangAnName		);
      m_strcFangAnPower		=	pADOConn->GetValueString(DBFangAn_Power_Key_FangAnPower		);
      m_nNum               = pADOConn->GetValueInt64(DBFangAn_Power_Key_Num);

      bRet = TRUE;
   }

   return bRet;
}

BOOL CDBPowerFangAnInfoData::UpdateToDB( CADOConn * pADo )
{
   BOOL bRet = FALSE;
   CString strSQL = _T("");
   strSQL.Format(_T("update %s set %s = '%s',%s = '%s',%s = %lld where %s = %lld")
      ,DB_TABLE_FANGANPOWER,DBFangAn_Power_Key_FangAnName,m_strcFangAnName
      ,DBFangAn_Power_Key_FangAnPower,m_strcFangAnPower
      ,DBFangAn_Power_Key_Num,m_nNum
      ,DBFangAn_Power_Key_ID,m_nID);

   if(pADo->ExecuteSQL(strSQL))
   {
      bRet = TRUE;
   }

   return bRet;
}

CDBPowerFangAnInfoDataList::CDBPowerFangAnInfoDataList()
{

}

CDBPowerFangAnInfoDataList::~CDBPowerFangAnInfoDataList()
{

}

CDBPowerFangAnInfoData* CDBPowerFangAnInfoDataList::GetItem( int nIndex )
{
   if (nIndex<0||nIndex>=GetCount())
      return NULL;
   return (CDBPowerFangAnInfoData*)GetAt(FindIndex(nIndex));
}

CDBPowerFangAnInfoData* CDBPowerFangAnInfoDataList::GetItemByName( CString strUserID )
{
   CDBPowerFangAnInfoData * pItem = NULL;
   strUserID.Trim();
   if (!strUserID.IsEmpty())
   {
      for(int i=0;i< GetCount();i++)
      {
         CDBPowerFangAnInfoData * pObject = GetItem(i);
         if(0 == strUserID.CompareNoCase(pObject->m_strcFangAnName))
         {
            pItem = pObject;
            break;
         }
      }
   }

   return pItem;
}

int CDBPowerFangAnInfoDataList::GetIndexByUserID( CString strUserID )
{
   int nSel = -1;
   strUserID.Trim();
   if (!strUserID.IsEmpty())
   {
      for(int i=0;i< GetCount();i++)
      {
         auto pObject = GetItem(i);
         if(strUserID==pObject->m_strcFangAnName)
         {
            nSel++;
            break;
         }
      }
   }

   return nSel;
}

void CDBPowerFangAnInfoDataList::AddItem( CDBPowerFangAnInfoData* pItem )
{
   CDBPowerFangAnInfoData*pData=new CDBPowerFangAnInfoData;
   pData->Copy(pItem);
   BOOL bInsert = FALSE;
   for (int nIndex = 0;nIndex < GetCount();nIndex++)
   {
      CDBPowerFangAnInfoData* pFangAn = (CDBPowerFangAnInfoData*) GetAt(FindIndex(nIndex));
      if (pFangAn != nullptr)
      {
         if (pFangAn->m_nNum > pData->m_nNum)
         {
            bInsert = TRUE;
            InsertBefore(FindIndex(nIndex),pData);
            break;
         }
      }

   }
   if (!bInsert)
   {
      AddTail(pData);
   }

}

void CDBPowerFangAnInfoDataList::DeleteItem( int nIndex )
{
   if (nIndex<0||nIndex>GetCount())
      return;
   CDBPowerFangAnInfoData *pObject=(CDBPowerFangAnInfoData*)GetItem(nIndex);
   delete pObject;
   pObject=NULL;
   RemoveAt(FindIndex(nIndex));
}

BOOL CDBPowerFangAnInfoDataList::GetListFromDB( CADOConn *pADOConn )
{
   BOOL bRet = FALSE;

   ASSERT(pADOConn != NULL);
   Empty();
   if (NULL == pADOConn)
   {
      bRet = FALSE;
   }
   else
   {
      CString strSQL = _T("");
      strSQL.Format(_T("select * from %s"),DB_TABLE_FANGANPOWER);

      bRet = pADOConn->GetRecordSet(strSQL);

      while (!pADOConn->adoEOF())
      {
         CDBPowerFangAnInfoData oData;
         oData.GetAllDBInfo(pADOConn);

         AddItem(&oData);
         pADOConn->MoveNext();
      }
   }

   return bRet;
}

CDBPowerFangAnInfoDataList * CDBPowerFangAnInfoDataList::Instance()
{
   if(sm_inst.get() == 0)
      sm_inst = shared_ptr<CDBPowerFangAnInfoDataList>(new CDBPowerFangAnInfoDataList);

   return sm_inst.get();
}

void CDBPowerFangAnInfoDataList::deletebyName(CString strname,CADOConn *pAdo)
{
   CDBPowerFangAnInfoData *pObject=(CDBPowerFangAnInfoData*)GetItemByName(strname);
   CString strSQL;
   strSQL.Format(_T("delete from %s where %s = '%s'"),DB_TABLE_FANGANPOWER,DBFangAn_Power_Key_FangAnName,pObject->m_strcFangAnName);
   if(pAdo->ExecuteSQL(strSQL))
   {
      RemoveAt(Find(pObject));
   }
}
