#include "StdAfx.h"
#include "DBSampleClothingRecords.h"
#include "DBKeyDef.h"
IMPLEMENT_SERIAL(CDBSampleClothingRecords,CDataMid,1)
IMPLEMENT_SERIAL(CDBSampleClothingRecordsList,CDataListMid,1)

CDBSampleClothingRecords::CDBSampleClothingRecords()
{
   ResetData();
}

CDBSampleClothingRecords::~CDBSampleClothingRecords()
{
}

void CDBSampleClothingRecords::ResetData()   
{
   m_ID;
   m_strcBarCode;
   m_strcKuanhao;
   m_LendReturnState;
   m_strLendReturnPerson;
   m_strLendReturnTime;
   m_strConfirmMan;
   m_strLocation;
   m_strReason;
   m_strMemo;
}

void CDBSampleClothingRecords::Copy( CDBSampleClothingRecords *pData )
{
   ASSERT(pData!=NULL);
   CDataMid::Copy(pData);
   m_ID;
   m_strcBarCode;
   m_strcKuanhao;
   m_LendReturnState;
   m_strLendReturnPerson;
   m_strLendReturnTime;
   m_strConfirmMan;
   m_strLocation;
   m_strReason;
   m_strMemo;
}

BOOL CDBSampleClothingRecords::GetAllDBInfo( CADOConn *pADOConn )
{
   ASSERT(pADOConn != NULL);
   m_ID = pADOConn->GetValueInt(DBSampleClothingRecords_Key_ID);
   m_strcBarCode = pADOConn->GetValueString(DBSampleClothingRecords_Key_cBarCode);
   m_strcKuanhao = pADOConn->GetValueString(DBSampleClothingRecords_Key_cKuanhao);
   m_LendReturnState = pADOConn->GetValueInt(DBSampleClothingRecords_Key_LendReturnState);
   m_strLendReturnPerson = pADOConn->GetValueString(DBSampleClothingRecords_Key_LendReturnPerson);
   m_strLendReturnTime = pADOConn->GetValueString(DBSampleClothingRecords_Key_LendReturnTime);
   m_strConfirmMan = pADOConn->GetValueString(DBSampleClothingRecords_Key_ConfirmMan);
   m_strLocation = pADOConn->GetValueString(DBSampleClothingRecords_Key_Location);
   m_strReason = pADOConn->GetValueString(DBSampleClothingRecords_Key_Reason);
   m_strMemo = pADOConn->GetValueString(DBSampleClothingRecords_Key_Memo);

   return TRUE;
}

CString CDBSampleClothingRecords::GetInsertSql()
{
   CString strSql = _T("");
   strSql.Format(_T("insert into %s (%s,%s,%s,%s,%s, %s,%s,%s,%s) values('%s','%s','%d','%s','%s', '%s','%s','%s','%s')"),DB_TABLE_SAMPLE_CLOTHING_RECORDS,
      DBSampleClothingRecords_Key_cBarCode,        
      DBSampleClothingRecords_Key_cKuanhao,
      DBSampleClothingRecords_Key_LendReturnState,
      DBSampleClothingRecords_Key_LendReturnPerson,
      DBSampleClothingRecords_Key_LendReturnTime,
      DBSampleClothingRecords_Key_ConfirmMan,
      DBSampleClothingRecords_Key_Location,
      DBSampleClothingRecords_Key_Reason,
      DBSampleClothingRecords_Key_Memo,
      m_strcBarCode,
      m_strcKuanhao,
      m_LendReturnState,
      m_strLendReturnPerson,
      m_strLendReturnTime,
      m_strConfirmMan,
      m_strLocation,
      m_strReason,
      m_strMemo
      );
   return strSql;
}

CString CDBSampleClothingRecords::GetUpdateSql()
{
   CString strSql = _T("");
   
   return strSql;
}

CString CDBSampleClothingRecords::GetDeleteSql()
{
   CString strSql = _T("");
   return strSql;
}

BOOL CDBSampleClothingRecords::InsertData(CADOConn *pADOConn)
{
   ASSERT(pADOConn != NULL);
   return pADOConn->ExecuteSQL(GetInsertSql());
}

BOOL CDBSampleClothingRecords::UpdateData(CADOConn *pADOConn)
{
   return FALSE;
}

BOOL CDBSampleClothingRecords::DeleteData(CADOConn *pADOConn)
{
   return FALSE;
}

CDBSampleClothingRecords* CDBSampleClothingRecordsList::GetItem( int nIndex )
{
   if (nIndex <0 || nIndex>=GetCount())
   {
      return NULL;
   }

   return (CDBSampleClothingRecords *) GetAt(FindIndex(nIndex));
}



std::shared_ptr<CDBSampleClothingRecordsList> CDBSampleClothingRecordsList::sm_inst;


CDBSampleClothingRecordsList * CDBSampleClothingRecordsList::Instance()
{
   if(sm_inst.get() == 0)
      sm_inst = shared_ptr<CDBSampleClothingRecordsList>(new CDBSampleClothingRecordsList);

   return sm_inst.get();
}

CDBSampleClothingRecordsList::CDBSampleClothingRecordsList()
{

}

CDBSampleClothingRecordsList::~CDBSampleClothingRecordsList()
{

}

void CDBSampleClothingRecordsList::AddItem( CDBSampleClothingRecords* pItem )
{
   ASSERT(pItem != NULL);
   CDBSampleClothingRecords *pTail = new CDBSampleClothingRecords;
   pTail->Copy(pItem);

   AddTail(pTail);
}

BOOL CDBSampleClothingRecordsList::DeleteItem( int nIndex )
{
   if (nIndex <0 || nIndex>=GetCount())
   {
      return FALSE;
   }
   CDBSampleClothingRecords *pStyleCost = GetItem(nIndex);
   delete pStyleCost;
   pStyleCost = NULL;
   RemoveAt(FindIndex(nIndex));

   return TRUE;
}

void CDBSampleClothingRecordsList::Copy(CDBSampleClothingRecordsList *pList)
{
   if (pList != NULL)
   {
      for (int nIndex = 0;nIndex < pList->GetCount();nIndex++)
      {
         CDBSampleClothingRecords *pData =(CDBSampleClothingRecords *)pList->GetAt(pList->FindIndex(nIndex));
         if (pData != NULL)
         {
            AddItem(pData);
         }
      }
   }
}

#ifdef USING_GRIDCTRL_MARK
void CDBSampleClothingRecordsList::CreateRowData(CDBSampleClothingRecords*pData,__out MAP_GridCtrl_RowData& row_data)
{
   row_data.clear();
   CString strValue;
   strValue.Format(_T("%d"),pData->m_ID);
   CDBSampleClothingRecordsList::Instance()->InsertRowData(DBSampleClothingRecords_Key_ID,strValue,row_data);
   CDBSampleClothingRecordsList::Instance()->InsertRowData(DBSampleClothingRecords_Key_cBarCode       ,pData->m_strcBarCode,row_data);
   CDBSampleClothingRecordsList::Instance()->InsertRowData(DBSampleClothingRecords_Key_cKuanhao       ,pData->m_strcKuanhao,row_data);

   pData->m_LendReturnState == 0 ? strValue=_T("½è³ö"):strValue=_T("¹é»¹");
   CDBSampleClothingRecordsList::Instance()->InsertRowData(DBSampleClothingRecords_Key_LendReturnState ,strValue,row_data);

   CDBSampleClothingRecordsList::Instance()->InsertRowData(DBSampleClothingRecords_Key_LendReturnPerson,pData->m_strLendReturnPerson,row_data);
   CDBSampleClothingRecordsList::Instance()->InsertRowData(DBSampleClothingRecords_Key_LendReturnTime  ,pData->m_strLendReturnTime,row_data);
   CDBSampleClothingRecordsList::Instance()->InsertRowData(DBSampleClothingRecords_Key_ConfirmMan      ,pData->m_strConfirmMan,row_data);
   CDBSampleClothingRecordsList::Instance()->InsertRowData(DBSampleClothingRecords_Key_Location       ,pData->m_strLocation,row_data);
   CDBSampleClothingRecordsList::Instance()->InsertRowData(DBSampleClothingRecords_Key_Reason       ,pData->m_strReason,row_data);
   CDBSampleClothingRecordsList::Instance()->InsertRowData(DBSampleClothingRecords_Key_Memo       ,pData->m_strMemo,row_data);       
}  

BOOL CDBSampleClothingRecordsList::GetRecordsGridData(CADOConn *pADOConn,CString strBarCode,__out MAP_GridCtrl_AllData& all_data)
{
   all_data.clear();
   ASSERT(pADOConn != NULL);
   if (strBarCode.IsEmpty())
      return FALSE;

   CString strSql;
   strSql.Format(_T("select * from %s where %s = '%s';"),DB_TABLE_SAMPLE_CLOTHING_RECORDS,DBSampleClothingRecords_Key_cBarCode,strBarCode);
   pADOConn->GetRecordSet(strSql);
   while(!pADOConn->adoEOF())
   {
      CDBSampleClothingRecords oData;
      oData.GetAllDBInfo(pADOConn);
      MAP_GridCtrl_RowData row_data;
      CreateRowData(&oData,row_data);
      all_data.insert(make_pair(all_data.size(),row_data));
      pADOConn->MoveNext();
   }

   return TRUE;
}

BOOL CDBSampleClothingRecordsList::GetRecordsGridDataByStyleNo(CADOConn *pADOConn,CString strStyleNo,__out MAP_GridCtrl_AllData& all_data)
{
   all_data.clear();
   ASSERT(pADOConn != NULL);
   if (strStyleNo.IsEmpty())
      return FALSE;

   CString strSql;
   strSql.Format(_T("select * from %s where %s = '%s';"),DB_TABLE_SAMPLE_CLOTHING_RECORDS,DBSampleClothingRecords_Key_cKuanhao,strStyleNo);
   pADOConn->GetRecordSet(strSql);
   while(!pADOConn->adoEOF())
   {
      CDBSampleClothingRecords oData;
      oData.GetAllDBInfo(pADOConn);
      MAP_GridCtrl_RowData row_data;
      CreateRowData(&oData,row_data);
      all_data.insert(make_pair(all_data.size(),row_data));
      pADOConn->MoveNext();
   }

   return TRUE;
}

#endif



