#include "StdAfx.h"
#include "DBP_ProcessRecords.h"
#include "DBKeyDef.h"
#include "DBKeyDef_V.h"

///////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CDBP_ProcessRecordsData,  CDataMid, 1)
IMPLEMENT_SERIAL(CDBP_ProcessRecordsList,  CDataListMid, 1)

std::shared_ptr<CDBP_ProcessRecordsList> CDBP_ProcessRecordsList::sm_inst;

CDBP_ProcessRecordsData::CDBP_ProcessRecordsData()
{
   ResetData(); 
} 

CDBP_ProcessRecordsData::~CDBP_ProcessRecordsData()
{
}

void CDBP_ProcessRecordsData::ResetData()
{
   m_nID                   = 0;
   m_nAssociatedProductID  = 0;
   m_strReceiveUserID      = _T("");
   m_strSponsorID          = _T("");
   m_nProcessType          = 0;
   m_strInitiateTime       = _T("");
   m_strRealStartTime      = _T("");
   m_strFinishTime         = _T("");
   m_nState                = 0;
   m_bCheckState           = FALSE;

   SetDataType(DAT_PROCESSRECORDS);
}

void CDBP_ProcessRecordsData:: Copy(CDBP_ProcessRecordsData *pData)
{
   ASSERT(pData != NULL);
   CDataMid::Copy(pData);

   m_nID                   = pData->m_nID                   ;
   m_nAssociatedProductID  = pData->m_nAssociatedProductID  ;
   m_strReceiveUserID      = pData->m_strReceiveUserID      ;
   m_strSponsorID          = pData->m_strSponsorID          ;
   m_nProcessType          = pData->m_nProcessType          ;
   m_strInitiateTime       = pData->m_strInitiateTime       ;
   m_strRealStartTime      = pData->m_strRealStartTime      ;
   m_strFinishTime         = pData->m_strFinishTime         ;
   m_nState                = pData->m_nState                ;
   m_bCheckState           = pData->m_bCheckState           ;

}

BOOL CDBP_ProcessRecordsData::GetAllDBInfo(CADOConn *pADOConn)
{
   ASSERT(pADOConn != NULL);

   BOOL bRet = FALSE;
   /*if (NULL != pADOConn)
   {
      m_nID                   = pADOConn->GetValueInt64(DBP_ProcessRecords_Key_ID            );
      m_nAssociatedProductID  = pADOConn->GetValueInt64(DBP_ProcessRecords_Key_nAssociatedProductID  );
      m_strReceiveUserID      = pADOConn->GetValueString(DBP_ProcessRecords_Key_cReceiveUserID);
      m_strSponsorID          = pADOConn->GetValueString(DBP_ProcessRecords_Key_cSponsorID    );
      m_nProcessType          = pADOConn->GetValueInt(DBP_ProcessRecords_Key_nProcessType     );
      m_strInitiateTime       = pADOConn->GetValueString(DBP_ProcessRecords_Key_cInitiateTime );
      m_strRealStartTime      = pADOConn->GetValueString(DBP_ProcessRecords_Key_cRealStartTime);
      m_strFinishTime         = pADOConn->GetValueString(DBP_ProcessRecords_Key_cFinishTime   );
      m_nState                = pADOConn->GetValueInt(DBP_ProcessRecords_Key_nState        );
      m_bCheckState           = pADOConn->GetValueInt(DBP_ProcessRecords_Key_nCheckState   );

      bRet = TRUE;
   }
   */
   bRet = TRUE;
   return bRet;
}

BOOL CDBP_ProcessRecordsData::DelAllDBInfoByID(CADOConn *pADOConn)
{
   ASSERT(NULL != pADOConn);
   CString strSQL = _T("");
   strSQL.Format(_T("delete from %s where %s = '%lld';"),DB_TABLE_P_PROCESSRECORDS,DBP_Programming_Key_ID,m_nID);

   return pADOConn->ExecuteSQL(strSQL);
}

BOOL CDBP_ProcessRecordsData::UpdateAllDBInfoByID( CADOConn *pADOConn )
{
   /*ASSERT(NULL != pADOConn);
   CString strSQL = _T(""),strKeyValue = _T("");
   //关联企划ID 和 创建人 禁止修改

   strKeyValue.Format(_T("%s = '%lld',%s = '%s',%s = '%d',%s = '%s',%s = '%s',%s = '%s',%s = '%d',%s = '%d'"),
      DBP_ProcessRecords_Key_nAssociatedProductID         ,m_nAssociatedProductID   ,
      DBP_ProcessRecords_Key_cReceiveUserID,m_strReceiveUserID       ,
      DBP_ProcessRecords_Key_cSponsorID    ,m_strSponsorID           ,
      DBP_ProcessRecords_Key_nProcessType    ,m_nProcessType           ,
      DBP_ProcessRecords_Key_cInitiateTime ,m_strInitiateTime        ,
      DBP_ProcessRecords_Key_cRealStartTime,m_strRealStartTime       ,
      DBP_ProcessRecords_Key_cFinishTime   ,m_strFinishTime          ,
      DBP_ProcessRecords_Key_nState        ,m_nState                 ,
      DBP_ProcessRecords_Key_nCheckState   ,m_bCheckState   
      );

   //更新时不需要更新其它的关联信息  
   strSQL.Format(_T("update %s set %s where %s = '%lld';"),DB_TABLE_PROCESSRECORDS,
      strKeyValue,DBP_ProcessRecords_Key_ID,m_nID);

   return pADOConn->ExecuteSQL(strSQL);
   */
   return TRUE;
}

BOOL CDBP_ProcessRecordsData::InsertAllDBInfo( CADOConn *pADOConn )
{
   /*ASSERT(NULL != pADOConn);
   CString strSQL = _T(""),strParam = _T(""),strValue = _T("");
   strParam.Format(_T("%s,%s,%s,%s,%s,%s,%s,%s,%s"),
      DBP_ProcessRecords_Key_nAssociatedProductID , DBP_ProcessRecords_Key_cReceiveUserID ,
      DBP_ProcessRecords_Key_cSponsorID , DBP_ProcessRecords_Key_nProcessType ,
      DBP_ProcessRecords_Key_cInitiateTime , DBP_ProcessRecords_Key_cRealStartTime ,
      DBP_ProcessRecords_Key_cFinishTime , DBP_ProcessRecords_Key_nState ,
      DBP_ProcessRecords_Key_nCheckState);


   strValue.Format(_T("'%lld','%s','%s','%d','%s','%s','%s','%d','%d',"),
      m_nAssociatedProductID , m_strReceiveUserID,
      m_strSponsorID , m_nProcessType ,
      m_strInitiateTime , m_strRealStartTime,
      m_strFinishTime , m_nState ,
      m_bCheckState);

   strSQL.Format(_T("insert into %s (%s) values(%s);"),
      DB_TABLE_PROCESSRECORDS,strParam,strValue);

   return pADOConn->ExecuteSQL(strSQL);
   */
   return TRUE;
}

void CDBP_ProcessRecordsData::Trim()
{
   m_strReceiveUserID .Trim();
   m_strSponsorID .Trim();
   m_strInitiateTime .Trim();
   m_strRealStartTime .Trim();
   m_strFinishTime .Trim();
}

CDBP_ProcessRecordsList::CDBP_ProcessRecordsList()
{

}
CDBP_ProcessRecordsList::~CDBP_ProcessRecordsList()
{

}

CDBP_ProcessRecordsData* CDBP_ProcessRecordsList::GetItem(int nIndex)
{
   if (nIndex<0||nIndex>=GetCount())
      return NULL;
   return (CDBP_ProcessRecordsData*)GetAt(FindIndex(nIndex));
}

void CDBP_ProcessRecordsList::AddItem(CDBP_ProcessRecordsData* pItem)
{
   CDBP_ProcessRecordsData*pData=new CDBP_ProcessRecordsData;
   pData->Copy(pItem);
   AddTail(pData);
}

void CDBP_ProcessRecordsList::DeleteItem(int nIndex)
{
   if (nIndex<0||nIndex>GetCount())
      return;
   CDBP_ProcessRecordsData *pObject=(CDBP_ProcessRecordsData*)GetItem(nIndex);
   delete pObject;
   pObject=NULL;
   RemoveAt(FindIndex(nIndex));
}

CDBP_ProcessRecordsList * CDBP_ProcessRecordsList::Instance()
{
   if(sm_inst.get() == 0)
      sm_inst = shared_ptr<CDBP_ProcessRecordsList>(new CDBP_ProcessRecordsList);

   return sm_inst.get();
}

