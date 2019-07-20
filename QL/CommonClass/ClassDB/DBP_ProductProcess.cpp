#include "StdAfx.h"
#include "DBP_ProductProcess.h"
#include "DBKeyDef.h"

///////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CDBP_ProductProcessData,  CDataMid, 1)
IMPLEMENT_SERIAL(CDBP_ProductProcessList,  CDataListMid, 1)

std::shared_ptr<CDBP_ProductProcessList> CDBP_ProductProcessList::sm_inst;

CDBP_ProductProcessData::CDBP_ProductProcessData()
{
   ResetData(); 
} 

CDBP_ProductProcessData::~CDBP_ProductProcessData()
{
}

void CDBP_ProductProcessData::ResetData()
{
   m_nID             = 0;
   m_strProcessName = _T("");
   m_nSortID        = 0;
   m_nProcessType   = En_ProcessType_Design;

   SetDataType(DAT_PRODUCTPROCESS);
}

void CDBP_ProductProcessData:: Copy(CDBP_ProductProcessData *pData)
{
   ASSERT(pData != NULL);
   CDataMid::Copy(pData);

   m_nID              =  pData->m_nID              ;
   m_strProcessName  =  pData->m_strProcessName  ;
   m_nSortID         =  pData->m_nSortID         ;
   m_nProcessType    =  pData->m_nProcessType    ;
}

BOOL CDBP_ProductProcessData::GetAllDBInfo(CADOConn *pADOConn)
{
   ASSERT(pADOConn != NULL);

   BOOL bRet = FALSE;
   if (NULL != pADOConn)
   {
      m_nID             = pADOConn->GetValueInt64( DBP_ProductProcess_Key_ID              );
      m_strProcessName  = pADOConn->GetValueString( DBP_ProductProcess_Key_cProcessName   );
      m_nSortID         = pADOConn->GetValueInt( DBP_ProductProcess_Key_nSortID           );
      m_nProcessType    = (EN_ProcessType)pADOConn->GetValueInt( DBP_ProductProcess_Key_nProcessType );

      bRet = TRUE;
   }

   return bRet;
}

BOOL CDBP_ProductProcessData::DelAllDBInfoByID(CADOConn *pADOConn)
{
   ASSERT(NULL != pADOConn);
   CString strSQL = _T("");
   strSQL.Format(_T("delete from %s where %s = '%lld';"),DB_TABLE_PRODUCTPROCESS,DBP_ProductProcess_Key_ID,m_nID);

   return pADOConn->ExecuteSQL(strSQL);
}

BOOL CDBP_ProductProcessData::UpdateAllDBInfoByID( CADOConn *pADOConn )
{
   ASSERT(NULL != pADOConn);
   CString strSQL = _T("");
   //更新时不需要更新其它的关联信息  
   strSQL.Format(_T("update %s set %s = '%s',%s = '%d',%s = '%d' where %s = '%lld';"),DB_TABLE_PRODUCTPROCESS,
      DBP_ProductProcess_Key_cProcessName,m_strProcessName,
      DBP_ProductProcess_Key_nSortID     ,m_nSortID       ,
      DBP_ProductProcess_Key_nProcessType,m_nProcessType  ,
      DBP_ProductProcess_Key_ID,m_nID);

   return pADOConn->ExecuteSQL(strSQL);
}

BOOL CDBP_ProductProcessData::InsertAllDBInfo( CADOConn *pADOConn )
{
   ASSERT(NULL != pADOConn);
   CString strSQL = _T(""),strParam = _T(""),strValue = _T("");
   strParam.Format(_T("%s,%s,%s"),
      DBP_ProductProcess_Key_cProcessName,DBP_ProductProcess_Key_nSortID ,DBP_ProductProcess_Key_nProcessType);

   strValue.Format(_T("'%s','%d','%d'"),m_strProcessName,m_nSortID ,m_nProcessType);

   strSQL.Format(_T("insert into %s (%s) values(%s);"),
      DB_TABLE_PRODUCTPROCESS,strParam,strValue);

   return pADOConn->ExecuteSQL(strSQL);
}

void CDBP_ProductProcessData::Trim()
{
   m_strProcessName.Trim();
}

CDBP_ProductProcessList::CDBP_ProductProcessList()
{

}
CDBP_ProductProcessList::~CDBP_ProductProcessList()
{

}

CDBP_ProductProcessData* CDBP_ProductProcessList::GetItem(int nIndex)
{
   if (nIndex<0||nIndex>=GetCount())
      return NULL;
   return (CDBP_ProductProcessData*)GetAt(FindIndex(nIndex));
}

void CDBP_ProductProcessList::AddItem(CDBP_ProductProcessData* pItem)
{
   CDBP_ProductProcessData*pData=new CDBP_ProductProcessData;
   pData->Copy(pItem);
   AddTail(pData);
}

void CDBP_ProductProcessList::DeleteItem(int nIndex)
{
   if (nIndex<0||nIndex>GetCount())
      return;
   CDBP_ProductProcessData *pObject=(CDBP_ProductProcessData*)GetItem(nIndex);
   delete pObject;
   pObject=NULL;
   RemoveAt(FindIndex(nIndex));
}

CDBP_ProductProcessList * CDBP_ProductProcessList::Instance()
{
   if(sm_inst.get() == 0)
      sm_inst = shared_ptr<CDBP_ProductProcessList>(new CDBP_ProductProcessList);

   return sm_inst.get();
}
