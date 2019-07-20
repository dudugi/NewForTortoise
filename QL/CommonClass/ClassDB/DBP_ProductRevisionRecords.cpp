#include "StdAfx.h"
#include "DBP_ProductRevisionRecords.h"
#include "DBKeyDef.h"

///////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CDBP_ProductRevisionRecordsData,  CDataMid, 1)
IMPLEMENT_SERIAL(CDBP_ProductRevisionRecordsList,  CDataListMid, 1)

std::shared_ptr<CDBP_ProductRevisionRecordsList> CDBP_ProductRevisionRecordsList::sm_inst;

CDBP_ProductRevisionRecordsData::CDBP_ProductRevisionRecordsData()
{
   ResetData(); 
} 

CDBP_ProductRevisionRecordsData::~CDBP_ProductRevisionRecordsData()
{
}

void CDBP_ProductRevisionRecordsData::ResetData()
{
   
   m_nID                    = 0;
   m_nAssociatedProductID   = 0;
   m_strVersion             = _T("");
   m_nVersionNo             = 0;
   m_strCode                = _T("");
   m_strAlias               = _T("");
   m_strSponsor             = _T("");
   m_strRecordTime          = _T("");
   m_strRevisionType        = _T("");
   m_strRevisionReason      = _T("");
   m_strLastRecordProcess   = _T("");
   m_bCheckState            = FALSE;
   m_strCheckUserID         = _T("");
   m_strCheckTime           = _T("");
   m_strCheckOpinion        = _T("");
   m_nCheckResult           = En_Refuse;

   SetDataType(DAT_PRODUCTREVISIONRECORDS);
}

void CDBP_ProductRevisionRecordsData:: Copy(CDBP_ProductRevisionRecordsData *pData)
{
   ASSERT(pData != NULL);
   CDataMid::Copy(pData);

   m_nID                    = pData->m_nID                    ;
   m_nAssociatedProductID   = pData->m_nAssociatedProductID   ;
   m_strVersion             = pData->m_strVersion             ;
   m_nVersionNo             = pData->m_nVersionNo             ;
   m_strCode                = pData->m_strCode                ;
   m_strAlias               = pData->m_strAlias               ;
   m_strSponsor             = pData->m_strSponsor             ;
   m_strRecordTime          = pData->m_strRecordTime          ;
   m_strRevisionType        = pData->m_strRevisionType        ;
   m_strRevisionReason      = pData->m_strRevisionReason      ;
   m_strLastRecordProcess   = pData->m_strLastRecordProcess   ;
   m_bCheckState            = pData->m_bCheckState            ;
   m_nCheckResult           = pData->m_nCheckResult           ;
   m_strCheckUserID         = pData->m_strCheckUserID         ;
   m_strCheckTime           = pData->m_strCheckTime           ;
   m_strCheckOpinion        = pData->m_strCheckOpinion        ;

}

BOOL CDBP_ProductRevisionRecordsData::GetAllDBInfo(CADOConn *pADOConn)
{
   ASSERT(pADOConn != NULL);

   BOOL bRet = FALSE;
   if (NULL != pADOConn)
   {

      m_nID                    = pADOConn->GetValueInt64 (DBP_ProductRevisionRecords_Key_ID                  );
      m_nAssociatedProductID   = pADOConn->GetValueInt64 (DBP_ProductRevisionRecords_Key_nAssociatedProductID);
      m_strVersion             = pADOConn->GetValueString(DBP_ProductRevisionRecords_Key_cVersion            );
      m_nVersionNo             = pADOConn->GetValueInt   (DBP_ProductRevisionRecords_Key_nVersionNo          );
      m_strCode                = pADOConn->GetValueString(DBP_ProductRevisionRecords_Key_cCode               );
      m_strAlias               = pADOConn->GetValueString(DBP_ProductRevisionRecords_Key_cAlias              );
      m_strSponsor             = pADOConn->GetValueString(DBP_ProductRevisionRecords_Key_cSponsor            );
      m_strRecordTime          = pADOConn->GetValueString(DBP_ProductRevisionRecords_Key_cRecordTime         );
      m_strRevisionType        = pADOConn->GetValueString(DBP_ProductRevisionRecords_Key_cRevisionType       );
      m_strRevisionReason      = pADOConn->GetValueString(DBP_ProductRevisionRecords_Key_cRevisionReason     );
      m_strLastRecordProcess   = pADOConn->GetValueString(DBP_ProductRevisionRecords_Key_cLastRecordProcess  );
      m_bCheckState            = pADOConn->GetValueInt   (DBP_ProductRevisionRecords_Key_nCheckState         );
      m_nCheckResult           = pADOConn->GetValueInt   (DBP_ProductRevisionRecords_Key_nCheckResult        );
      m_strCheckUserID         = pADOConn->GetValueString(DBP_ProductRevisionRecords_Key_cCheckUserID        );
      m_strCheckTime           = pADOConn->GetValueString(DBP_ProductRevisionRecords_Key_cCheckTime          );
      m_strCheckOpinion        = pADOConn->GetValueString(DBP_ProductRevisionRecords_Key_cCheckOpinion       );

      bRet = TRUE;
   }

   return bRet;
}

BOOL CDBP_ProductRevisionRecordsData::DelAllDBInfoByID(CADOConn *pADOConn)
{
   ASSERT(NULL != pADOConn);
   CString strSQL = _T("");
   strSQL.Format(_T("delete from %s where %s = '%lld';"),DB_TABLE_PRODUCTREVISIONRECORDS,DBP_ProductRevisionRecords_Key_ID,m_nID);

   return pADOConn->ExecuteSQL(strSQL);
}

BOOL CDBP_ProductRevisionRecordsData::UpdateAllDBInfoByID( CADOConn *pADOConn )
{
   ASSERT(NULL != pADOConn);
   CString strSQL = _T(""),strKeyValue = _T("");
   //关联企划ID 和 创建人 禁止修改

   strKeyValue.Format(_T("%s = '%s',%s = '%d',%s = '%s',%s = '%s',%s = '%s',%s = '%s'\
                         ,%s = '%s',%s = '%s',%s = '%s',%s = '%d',%s = '%d',%s = '%s',%s = '%s',%s = '%s'"),
                         DBP_ProductRevisionRecords_Key_cVersion            ,m_strVersion             ,
                         DBP_ProductRevisionRecords_Key_nVersionNo          ,m_nVersionNo             ,
                         DBP_ProductRevisionRecords_Key_cCode               ,m_strCode                ,
                         DBP_ProductRevisionRecords_Key_cAlias              ,m_strAlias               ,
                         DBP_ProductRevisionRecords_Key_cSponsor            ,m_strSponsor             ,
                         DBP_ProductRevisionRecords_Key_cRecordTime         ,m_strRecordTime          ,
                         DBP_ProductRevisionRecords_Key_cRevisionType       ,m_strRevisionType        ,
                         DBP_ProductRevisionRecords_Key_cRevisionReason     ,m_strRevisionReason      ,
                         DBP_ProductRevisionRecords_Key_cLastRecordProcess  ,m_strLastRecordProcess   ,
                         DBP_ProductRevisionRecords_Key_nCheckState         ,m_bCheckState            ,
                         DBP_ProductRevisionRecords_Key_nCheckResult        ,m_nCheckResult           ,
                         DBP_ProductRevisionRecords_Key_cCheckUserID        ,m_strCheckUserID         ,
                         DBP_ProductRevisionRecords_Key_cCheckTime          ,m_strCheckTime           ,
                         DBP_ProductRevisionRecords_Key_cCheckOpinion       ,m_strCheckOpinion        
      );

   //更新时不需要更新其它的关联信息  
   strSQL.Format(_T("update %s set %s where %s = '%lld';"),DB_TABLE_PRODUCTREVISIONRECORDS,
      strKeyValue,DBP_ProductRevisionRecords_Key_ID,m_nID);

   return pADOConn->ExecuteSQL(strSQL);
}

BOOL CDBP_ProductRevisionRecordsData::InsertAllDBInfo( CADOConn *pADOConn )
{
   ASSERT(NULL != pADOConn);
   CString strSQL = _T(""),strParam = _T(""),strValue = _T("");
   strParam.Format(_T("%s,%s,%s,%s,%s,%s,%s\
                      ,%s,%s,%s,%s,%s,%s,%s,%s"),
      DBP_ProductRevisionRecords_Key_nAssociatedProductID,
      DBP_ProductRevisionRecords_Key_cVersion            ,
      DBP_ProductRevisionRecords_Key_nVersionNo          ,
      DBP_ProductRevisionRecords_Key_cCode               ,
      DBP_ProductRevisionRecords_Key_cAlias              ,
      DBP_ProductRevisionRecords_Key_cSponsor            ,
      DBP_ProductRevisionRecords_Key_cRecordTime         ,
      DBP_ProductRevisionRecords_Key_cRevisionType       ,
      DBP_ProductRevisionRecords_Key_cRevisionReason     ,
      DBP_ProductRevisionRecords_Key_cLastRecordProcess  ,
      DBP_ProductRevisionRecords_Key_nCheckState         ,
      DBP_ProductRevisionRecords_Key_nCheckResult        ,
      DBP_ProductRevisionRecords_Key_cCheckUserID        ,
      DBP_ProductRevisionRecords_Key_cCheckTime          ,
      DBP_ProductRevisionRecords_Key_cCheckOpinion       
      );

   strValue.Format(_T("'%lld','%s','%d','%s','%s','%s','%s',\
                      '%s','%s','%s','%d','%d','%s','%s','%s'"),
                      m_nAssociatedProductID   ,
                      m_strVersion             ,
                      m_nVersionNo             ,
                      m_strCode                ,
                      m_strAlias               ,
                      m_strSponsor             ,
                      m_strRecordTime          ,
                      m_strRevisionType        ,
                      m_strRevisionReason      ,
                      m_strLastRecordProcess   ,
                      m_bCheckState            ,
                      m_nCheckResult           ,
                      m_strCheckUserID         ,
                      m_strCheckTime           ,
                      m_strCheckOpinion        
                      );

   strSQL.Format(_T("insert into %s (%s) values(%s);"),
      DB_TABLE_PRODUCTREVISIONRECORDS,strParam,strValue);

   return pADOConn->ExecuteSQL(strSQL);
}

void CDBP_ProductRevisionRecordsData::Trim()
{
   m_strVersion .Trim();
   m_strCode .Trim();
   m_strAlias .Trim();
   m_strSponsor .Trim();
   m_strRecordTime .Trim();
   m_strRevisionType .Trim();
   m_strRevisionReason .Trim();
   m_strLastRecordProcess.Trim();
   m_strCheckUserID .Trim();
   m_strCheckTime .Trim();
   m_strCheckOpinion .Trim();
}

CDBP_ProductRevisionRecordsList::CDBP_ProductRevisionRecordsList()
{

}
CDBP_ProductRevisionRecordsList::~CDBP_ProductRevisionRecordsList()
{

}

CDBP_ProductRevisionRecordsData* CDBP_ProductRevisionRecordsList::GetItem(int nIndex)
{
   if (nIndex<0||nIndex>=GetCount())
      return NULL;
   return (CDBP_ProductRevisionRecordsData*)GetAt(FindIndex(nIndex));
}

void CDBP_ProductRevisionRecordsList::AddItem(CDBP_ProductRevisionRecordsData* pItem)
{
   CDBP_ProductRevisionRecordsData*pData=new CDBP_ProductRevisionRecordsData;
   pData->Copy(pItem);
   AddTail(pData);
}

void CDBP_ProductRevisionRecordsList::DeleteItem(int nIndex)
{
   if (nIndex<0||nIndex>GetCount())
      return;
   CDBP_ProductRevisionRecordsData *pObject=(CDBP_ProductRevisionRecordsData*)GetItem(nIndex);
   delete pObject;
   pObject=NULL;
   RemoveAt(FindIndex(nIndex));
}

CDBP_ProductRevisionRecordsList * CDBP_ProductRevisionRecordsList::Instance()
{
   if(sm_inst.get() == 0)
      sm_inst = shared_ptr<CDBP_ProductRevisionRecordsList>(new CDBP_ProductRevisionRecordsList);

   return sm_inst.get();
}
