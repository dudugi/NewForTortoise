#include "StdAfx.h"
#include "DBP_ProductTaskAssign.h"
#include "DBKeyDef.h"

///////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CDBP_ProductTaskAssignData,  CDataMid, 1)
IMPLEMENT_SERIAL(CDBP_ProductTaskAssignList,  CDataListMid, 1)

std::shared_ptr<CDBP_ProductTaskAssignList> CDBP_ProductTaskAssignList::sm_inst;

CDBP_ProductTaskAssignData::CDBP_ProductTaskAssignData()
{
   ResetData(); 
} 

CDBP_ProductTaskAssignData::~CDBP_ProductTaskAssignData()
{
}

void CDBP_ProductTaskAssignData::ResetData()
{
   m_nID                  = 0;
   m_nAssociatedProductID = 0;
   m_nPersonType          = 0;
   m_strAssignUserID      = _T("");
   m_strAllotUserID       = _T("");
   m_strAllotTime         = _T("");

   SetDataType(DAT_PRODUCTTASKASSIGN);
}

void CDBP_ProductTaskAssignData:: Copy(CDBP_ProductTaskAssignData *pData)
{
   ASSERT(pData != NULL);
   CDataMid::Copy(pData);

   m_nID                   =  pData->m_nID                  ;
   m_nAssociatedProductID  =  pData->m_nAssociatedProductID ;
   m_nPersonType           =  pData->m_nPersonType          ;
   m_strAssignUserID       =  pData->m_strAssignUserID      ;
   m_strAllotUserID        =  pData->m_strAllotUserID       ;
   m_strAllotTime          =  pData->m_strAllotTime         ;
}

BOOL CDBP_ProductTaskAssignData::GetAllDBInfo(CADOConn *pADOConn)
{
   ASSERT(pADOConn != NULL);

   BOOL bRet = FALSE;
   if (NULL != pADOConn)
   {
      m_nID                   = pADOConn->GetValueInt64(DBP_ProductTaskAssign_Key_ID                   );
      m_nAssociatedProductID  = pADOConn->GetValueInt64(DBP_ProductTaskAssign_Key_nAssociatedProductID );
      m_nPersonType           = pADOConn->GetValueInt(DBP_ProductTaskAssign_Key_nPersonType            );
      m_strAssignUserID       = pADOConn->GetValueString(DBP_ProductTaskAssign_Key_cAssignUserID       );
      m_strAllotUserID        = pADOConn->GetValueString(DBP_ProductTaskAssign_Key_cAllotUserID        );
      m_strAllotTime          = pADOConn->GetValueString(DBP_ProductTaskAssign_Key_cAllotTime          );


      bRet = TRUE;
   }

   return bRet;
}

BOOL CDBP_ProductTaskAssignData::DelAllDBInfoByID(CADOConn *pADOConn)
{
   ASSERT(NULL != pADOConn);
   CString strSQL = _T("");
   strSQL.Format(_T("delete from %s where %s = '%lld';"),DB_TABLE_PRODUCTTASKASSIGN,DBP_ProductTaskAssign_Key_ID,m_nID);

   return pADOConn->ExecuteSQL(strSQL);
}

BOOL CDBP_ProductTaskAssignData::UpdateAllDBInfoByID( CADOConn *pADOConn )
{
   ASSERT(NULL != pADOConn);
   CString strSQL = _T("");
   //更新时不需要更新其它的关联信息  
   strSQL.Format(_T("update %s set %s = '%d',%s = '%s',%s = '%s',%s = %s, where %s = '%lld';"),DB_TABLE_PRODUCTTASKASSIGN,
      DBP_ProductTaskAssign_Key_nPersonType         ,m_nPersonType            ,
      DBP_ProductTaskAssign_Key_cAssignUserID       ,m_strAssignUserID        ,
      DBP_ProductTaskAssign_Key_cAllotUserID        ,m_strAllotUserID         ,
      DBP_ProductTaskAssign_Key_cAllotTime          ,DBS_GETDATESTR           ,
      DBP_ProductTaskAssign_Key_ID,m_nID);

   return pADOConn->ExecuteSQL(strSQL);
}

BOOL CDBP_ProductTaskAssignData::InsertAllDBInfo( CADOConn *pADOConn )
{
   ASSERT(NULL != pADOConn);
   CString strSQL = _T("");

   if(GetInsertSQL(strSQL))
      return pADOConn->ExecuteSQL(strSQL);
   else
      return FALSE;
}

CString CDBP_ProductTaskAssignData::GetTypeString()
{
   return GetTypeString((CDBP_ProductProcessData::EN_ProcessType)m_nPersonType);
}

CString CDBP_ProductTaskAssignData::GetTypeString(CDBP_ProductProcessData::EN_ProcessType nAssignType)
{
   CString strRet = _T("");
   switch(nAssignType)
   {
   case CDBP_ProductProcessData::En_ProcessType_Design:
      strRet = _T("设计师");
      break;
   case CDBP_ProductProcessData::En_ProcessType_Pattern:
      strRet = _T("打板师");
      break;
   default:
      strRet = _T("未知");
      break;
   }

   return strRet;
}

CDBP_ProductProcessData::EN_ProcessType CDBP_ProductTaskAssignData::GetTypeByTypeString(const CString & strTypeString)
{
   CDBP_ProductProcessData::EN_ProcessType nRet = CDBP_ProductProcessData::En_ProcessType_Design;
   if (strTypeString == _T("设计师"))
   {
      nRet = CDBP_ProductProcessData::En_ProcessType_Design;
   }
   else if (strTypeString == _T("打板师"))
   {
      nRet = CDBP_ProductProcessData::En_ProcessType_Pattern;
   }

   return nRet;
}

BOOL CDBP_ProductTaskAssignData::GetInsertSQL(CString & strSQL)
{
   if (m_nAssociatedProductID == 0 || m_strAssignUserID.IsEmpty())
   {
      ASSERT( FALSE);
      return FALSE;
   }

   CString strParam = _T(""),strValue = _T("");
   strParam.Format(_T("%s,%s,%s,%s,%s"),
      DBP_ProductTaskAssign_Key_nAssociatedProductID,
      DBP_ProductTaskAssign_Key_nPersonType         ,
      DBP_ProductTaskAssign_Key_cAssignUserID       ,
      DBP_ProductTaskAssign_Key_cAllotUserID        ,
      DBP_ProductTaskAssign_Key_cAllotTime          
      );

   strValue.Format(_T("'%lld','%d','%s','%s',%s"),
      m_nAssociatedProductID,
      m_nPersonType         ,
      m_strAssignUserID     ,
      m_strAllotUserID      ,
      DBS_GETDATESTR);


   strSQL.Format(_T("insert into %s (%s) values(%s);"),
      DB_TABLE_PRODUCTTASKASSIGN,strParam,strValue);

   return TRUE;
}

void CDBP_ProductTaskAssignData::Trim()
{
   m_strAssignUserID.Trim();
   m_strAllotUserID .Trim();
   m_strAllotTime   .Trim();
}

CDBP_ProductTaskAssignList::CDBP_ProductTaskAssignList()
{

}
CDBP_ProductTaskAssignList::~CDBP_ProductTaskAssignList()
{

}

CDBP_ProductTaskAssignData* CDBP_ProductTaskAssignList::GetItem(int nIndex)
{
   if (nIndex<0||nIndex>=GetCount())
      return NULL;
   return (CDBP_ProductTaskAssignData*)GetAt(FindIndex(nIndex));
}

CDBP_ProductTaskAssignData* CDBP_ProductTaskAssignList::GetItemByPersonType(CDBP_ProductProcessData::EN_ProcessType nPersonType)
{
   int nCount = GetCount();
   for (int nIndex = 0;nIndex < nCount;++nIndex)
   {
      auto pData = GetItem(nIndex);
      if (NULL != pData && pData->m_nPersonType == nPersonType)
      {
         return pData;
      }
   }

   return NULL;
}

void CDBP_ProductTaskAssignList::AddItem(CDBP_ProductTaskAssignData* pItem)
{
   CDBP_ProductTaskAssignData*pData=new CDBP_ProductTaskAssignData;
   pData->Copy(pItem);
   AddTail(pData);
}

void CDBP_ProductTaskAssignList::DeleteItem(int nIndex)
{
   if (nIndex<0||nIndex>GetCount())
      return;
   CDBP_ProductTaskAssignData *pObject=(CDBP_ProductTaskAssignData*)GetItem(nIndex);
   delete pObject;
   pObject=NULL;
   RemoveAt(FindIndex(nIndex));
}

CDBP_ProductTaskAssignList * CDBP_ProductTaskAssignList::Instance()
{
   if(sm_inst.get() == 0)
      sm_inst = shared_ptr<CDBP_ProductTaskAssignList>(new CDBP_ProductTaskAssignList);

   return sm_inst.get();
}
