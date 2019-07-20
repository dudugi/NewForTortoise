#include "StdAfx.h"
#include "DBProductRevisionRecords_V.h"
#include "DBKeyDef_V.h"

///////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CDBProductRevisionRecords_VData,  CDataMid, 1)
IMPLEMENT_SERIAL(CDBProductRevisionRecords_VList,  CDataListMid, 1)

std::shared_ptr<CDBProductRevisionRecords_VList> CDBProductRevisionRecords_VList::sm_inst;

CDBProductRevisionRecords_VData::CDBProductRevisionRecords_VData()
{
   ResetData(); 
} 

CDBProductRevisionRecords_VData::~CDBProductRevisionRecords_VData()
{
}

void CDBProductRevisionRecords_VData::ResetData()
{
   m_strClassification  = _T("");
   m_strCategory        = _T("");
   m_strBand_Name       = _T("");
   m_nCurProSort        = 0;
   m_ProductRevisionData.ResetData();
}

void CDBProductRevisionRecords_VData:: Copy(CDBProductRevisionRecords_VData *pData)
{
   ASSERT(pData != NULL);
   CDataMid::Copy(pData);

   m_strClassification  = pData->m_strClassification;
   m_strCategory        = pData->m_strCategory      ;
   m_strBand_Name       = pData->m_strBand_Name     ;
   m_nCurProSort        = pData->m_nCurProSort      ;

   m_ProductRevisionData.Copy(&(pData->m_ProductRevisionData));

}

BOOL CDBProductRevisionRecords_VData::GetAllDBInfo(CADOConn *pADOConn)
{
   ASSERT(pADOConn != NULL);

   BOOL bRet = FALSE;
   if (NULL != pADOConn)
   {
      m_strClassification                             = pADOConn->GetValueString(DBV_ProductRevisionRecords_Key_cClassification     );
      m_strCategory                                   = pADOConn->GetValueString(DBV_ProductRevisionRecords_Key_cCategory           );
      m_strBand_Name                                  = pADOConn->GetValueString(DBV_ProductRevisionRecords_Key_cBand_Name          );
      m_nCurProSort                                   = pADOConn->GetValueInt   (DBV_ProductRevisionRecords_Key_nCurProSort         );
      m_ProductRevisionData.m_nID                     = pADOConn->GetValueInt64 (DBV_ProductRevisionRecords_Key_ID                  );
      m_ProductRevisionData.m_nAssociatedProductID    = pADOConn->GetValueInt64 (DBV_ProductRevisionRecords_Key_nAssociatedProductID);
      m_ProductRevisionData.m_strVersion              = pADOConn->GetValueString(DBV_ProductRevisionRecords_Key_cVersion            );
      m_ProductRevisionData.m_nVersionNo              = pADOConn->GetValueInt   (DBV_ProductRevisionRecords_Key_nVersionNo          );
      m_ProductRevisionData.m_strCode                 = pADOConn->GetValueString(DBV_ProductRevisionRecords_Key_cCode               );
      m_ProductRevisionData.m_strAlias                = pADOConn->GetValueString(DBV_ProductRevisionRecords_Key_cAlias              );
      m_ProductRevisionData.m_strSponsor              = pADOConn->GetValueString(DBV_ProductRevisionRecords_Key_cSponsor            );
      m_ProductRevisionData.m_strRecordTime           = pADOConn->GetValueString(DBV_ProductRevisionRecords_Key_cRecordTime         );
      m_ProductRevisionData.m_strRevisionType         = pADOConn->GetValueString(DBV_ProductRevisionRecords_Key_cRevisionType       );
      m_ProductRevisionData.m_strRevisionReason       = pADOConn->GetValueString(DBV_ProductRevisionRecords_Key_cRevisionReason     );
      m_ProductRevisionData.m_strLastRecordProcess    = pADOConn->GetValueString(DBV_ProductRevisionRecords_Key_cLastRecordProcess  );
      m_ProductRevisionData.m_bCheckState             = pADOConn->GetValueInt   (DBV_ProductRevisionRecords_Key_nCheckState         );
      m_ProductRevisionData.m_nCheckResult            = pADOConn->GetValueInt   (DBV_ProductRevisionRecords_Key_nCheckResult        );
      m_ProductRevisionData.m_strCheckUserID          = pADOConn->GetValueString(DBV_ProductRevisionRecords_Key_cCheckUserID        );
      m_ProductRevisionData.m_strCheckTime            = pADOConn->GetValueString(DBV_ProductRevisionRecords_Key_cCheckTime          );
      m_ProductRevisionData.m_strCheckOpinion         = pADOConn->GetValueString(DBV_ProductRevisionRecords_Key_cCheckOpinion       );

      bRet = TRUE;
   }

   return bRet;
}


void CDBProductRevisionRecords_VData::Trim()
{
   m_strClassification.Trim();
   m_strCategory      .Trim();
   m_strBand_Name     .Trim();

   m_ProductRevisionData.Trim();
}

#ifdef USING_GRIDCTRL_MARK
MAP_GridCtrl_RowData CDBProductRevisionRecords_VData::CreateGridRowData(CADOConn * pADOConn)
{
   MAP_GridCtrl_RowData rowData;
   CDataMid::InsertRowData(DBV_ProductRevisionRecords_Key_cClassification     ,pADOConn->GetValueString(DBV_ProductRevisionRecords_Key_cClassification     ),rowData);
   CDataMid::InsertRowData(DBV_ProductRevisionRecords_Key_cCategory           ,pADOConn->GetValueString(DBV_ProductRevisionRecords_Key_cCategory           ),rowData);
   CDataMid::InsertRowData(DBV_ProductRevisionRecords_Key_cBand_Name          ,pADOConn->GetValueString(DBV_ProductRevisionRecords_Key_cBand_Name          ),rowData);
   CDataMid::InsertRowData(DBV_ProductRevisionRecords_Key_nCurProSort         ,pADOConn->GetValueString(DBV_ProductRevisionRecords_Key_nCurProSort         ),rowData);
   CDataMid::InsertRowData(DBV_ProductRevisionRecords_Key_ID                  ,pADOConn->GetValueString(DBV_ProductRevisionRecords_Key_ID                  ),rowData);
   CDataMid::InsertRowData(DBV_ProductRevisionRecords_Key_nAssociatedProductID,pADOConn->GetValueString(DBV_ProductRevisionRecords_Key_nAssociatedProductID),rowData);
   CDataMid::InsertRowData(DBV_ProductRevisionRecords_Key_cVersion            ,pADOConn->GetValueString(DBV_ProductRevisionRecords_Key_cVersion            ),rowData);
   CDataMid::InsertRowData(DBV_ProductRevisionRecords_Key_nVersionNo          ,pADOConn->GetValueString(DBV_ProductRevisionRecords_Key_nVersionNo          ),rowData);
   CDataMid::InsertRowData(DBV_ProductRevisionRecords_Key_cCode               ,pADOConn->GetValueString(DBV_ProductRevisionRecords_Key_cCode               ),rowData);
   CDataMid::InsertRowData(DBV_ProductRevisionRecords_Key_cAlias              ,pADOConn->GetValueString(DBV_ProductRevisionRecords_Key_cAlias              ),rowData);
   CDataMid::InsertRowData(DBV_ProductRevisionRecords_Key_cSponsor            ,pADOConn->GetValueString(DBV_ProductRevisionRecords_Key_cSponsor            ),rowData);
   CDataMid::InsertRowData(DBV_ProductRevisionRecords_Key_cRecordTime         ,pADOConn->GetValueString(DBV_ProductRevisionRecords_Key_cRecordTime         ),rowData);
   CDataMid::InsertRowData(DBV_ProductRevisionRecords_Key_cRevisionType       ,pADOConn->GetValueString(DBV_ProductRevisionRecords_Key_cRevisionType       ),rowData);
   CDataMid::InsertRowData(DBV_ProductRevisionRecords_Key_cRevisionReason     ,pADOConn->GetValueString(DBV_ProductRevisionRecords_Key_cRevisionReason     ),rowData);
   CDataMid::InsertRowData(DBV_ProductRevisionRecords_Key_cLastRecordProcess  ,pADOConn->GetValueString(DBV_ProductRevisionRecords_Key_cLastRecordProcess  ),rowData);
   CDataMid::InsertRowData(DBV_ProductRevisionRecords_Key_nCheckState         ,pADOConn->GetValueString(DBV_ProductRevisionRecords_Key_nCheckState         ),rowData);
   CDataMid::InsertRowData(DBV_ProductRevisionRecords_Key_nCheckResult        ,pADOConn->GetValueString(DBV_ProductRevisionRecords_Key_nCheckResult        ),rowData);
   CDataMid::InsertRowData(DBV_ProductRevisionRecords_Key_cCheckUserID        ,pADOConn->GetValueString(DBV_ProductRevisionRecords_Key_cCheckUserID        ),rowData);
   CDataMid::InsertRowData(DBV_ProductRevisionRecords_Key_cCheckTime          ,pADOConn->GetValueString(DBV_ProductRevisionRecords_Key_cCheckTime          ),rowData);
   CDataMid::InsertRowData(DBV_ProductRevisionRecords_Key_cCheckOpinion       ,pADOConn->GetValueString(DBV_ProductRevisionRecords_Key_cCheckOpinion       ),rowData);

   return rowData;
}
#endif // USING_GRIDCTRL_MARK

CDBProductRevisionRecords_VList::CDBProductRevisionRecords_VList()
{

}
CDBProductRevisionRecords_VList::~CDBProductRevisionRecords_VList()
{

}

CDBProductRevisionRecords_VData* CDBProductRevisionRecords_VList::GetItem(int nIndex)
{
   if (nIndex<0||nIndex>=GetCount())
      return NULL;
   return (CDBProductRevisionRecords_VData*)GetAt(FindIndex(nIndex));
}

void CDBProductRevisionRecords_VList::AddItem(CDBProductRevisionRecords_VData* pItem)
{
   CDBProductRevisionRecords_VData*pData=new CDBProductRevisionRecords_VData;
   pData->Copy(pItem);
   AddTail(pData);
}

void CDBProductRevisionRecords_VList::DeleteItem(int nIndex)
{
   if (nIndex<0||nIndex>GetCount())
      return;
   CDBProductRevisionRecords_VData *pObject=(CDBProductRevisionRecords_VData*)GetItem(nIndex);
   delete pObject;
   pObject=NULL;
   RemoveAt(FindIndex(nIndex));
}

CDBProductRevisionRecords_VList * CDBProductRevisionRecords_VList::Instance()
{
   if(sm_inst.get() == 0)
      sm_inst = shared_ptr<CDBProductRevisionRecords_VList>(new CDBProductRevisionRecords_VList);

   return sm_inst.get();
}
