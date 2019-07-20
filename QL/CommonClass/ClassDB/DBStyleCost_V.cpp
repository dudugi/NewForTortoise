#include "StdAfx.h"
#include "DBStyleCost_V.h"
#include "DBKeyDef_V.h"
IMPLEMENT_SERIAL(CDBStyleCostData_V,CDataMid,1)
IMPLEMENT_SERIAL(CDBStyleCostList_V,CDataListMid,1)

CDBStyleCostData_V::CDBStyleCostData_V()
{
   ResetData();
}

CDBStyleCostData_V::~CDBStyleCostData_V()
{
}

void CDBStyleCostData_V::ResetData()   
{
   m_ID          = 0      ;
   m_strStyleNo  = _T("") ;
   m_strCostItem = _T("") ;
   m_strCostType = _T("") ;
   m_fCostPrice       = 0 ;
   m_fCostAddedValue  = 0 ;
   m_fSalesPrice      = 0 ;
   m_fSalesAddedValue = 0 ;
   m_fCalculatedValue = 0 ;
   m_fCost            = 0 ;
   m_fQuotedPrice     = 0 ;

   SetDataType(DAT_V_STYLE_COST);
}

void CDBStyleCostData_V::Copy( CDBStyleCostData_V *pData )
{
   ASSERT(pData!=NULL);
   CDataMid::Copy(pData);

   m_ID          = pData->m_ID          ;   //ID 
   m_strStyleNo  = pData->m_strStyleNo  ;   //款号      
   m_strCostItem = pData->m_strCostItem ;   //成本项
   m_strCostType = pData->m_strCostType ;   //成本类别
   m_fCostPrice       = pData->m_fCostPrice       ;
   m_fCostAddedValue  = pData->m_fCostAddedValue  ;
   m_fSalesPrice      = pData->m_fSalesPrice      ;
   m_fSalesAddedValue = pData->m_fSalesAddedValue ;
   m_fCalculatedValue = pData->m_fCalculatedValue ;
   m_fCost            = pData->m_fCost            ;
   m_fQuotedPrice     = pData->m_fQuotedPrice     ;
}

BOOL CDBStyleCostData_V::GetAllDBInfo( CADOConn *pADOConn )
{
   ASSERT(pADOConn != NULL);

   m_ID                 = pADOConn->GetValueInt64 (DBStyleCost_V_ID              );
   m_strStyleNo         = pADOConn->GetValueString(DBStyleCost_V_cStyleNo        );
   m_strCostItem        = pADOConn->GetValueString(DBStyleCost_V_cCostItem       );
   m_strCostType        = pADOConn->GetValueString(DBStyleCost_V_cCostType       );
   m_fCostPrice         = pADOConn->GetValueDouble(DBStyleCost_V_fCostPrice      );
   m_fCostAddedValue    = pADOConn->GetValueDouble(DBStyleCost_V_fCostAddedValue );
   m_fSalesPrice        = pADOConn->GetValueDouble(DBStyleCost_V_fSalesPrice     );
   m_fSalesAddedValue   = pADOConn->GetValueDouble(DBStyleCost_V_fSalesAddedValue);
   m_fCalculatedValue   = pADOConn->GetValueDouble(DBStyleCost_V_fCalculatedValue);
   m_fCost              = pADOConn->GetValueDouble(DBStyleCost_V_fCost           );
   m_fQuotedPrice       = pADOConn->GetValueDouble(DBStyleCost_V_fQuotedPrice    );

   return TRUE;
}

void CDBStyleCostData_V::CalculatedPrice()
{
   m_fCost = m_fCostPrice * m_fCalculatedValue + m_fCostAddedValue;
   m_fQuotedPrice = m_fSalesPrice * m_fCalculatedValue + m_fSalesAddedValue;
}

CDBStyleCostData_V* CDBStyleCostList_V::GetItem( int nIndex )
{
   if (nIndex <0 || nIndex>=GetCount())
   {
      return NULL;
   }

   return (CDBStyleCostData_V *) GetAt(FindIndex(nIndex));
}

CDBStyleCostData_V* CDBStyleCostList_V::GetItemByCostItem( CString strCostItem )
{
   for (int nIndex =0;nIndex < GetCount();nIndex++)
   {
       auto pAuto = GetItem(nIndex);
       if (pAuto->m_strCostItem == strCostItem)
       {
          return pAuto;
       }
   }

   return NULL;

}

CDBStyleCostList_V::CDBStyleCostList_V()
{

}

CDBStyleCostList_V::~CDBStyleCostList_V()
{

}

void CDBStyleCostList_V::AddItem( CDBStyleCostData_V* pItem )
{
   ASSERT(pItem != NULL);
   CDBStyleCostData_V *pTail = new CDBStyleCostData_V;
   pTail->Copy(pItem);

   AddTail(pTail);
}

BOOL CDBStyleCostList_V::DeleteItem( int nIndex )
{
   if (nIndex <0 || nIndex>=GetCount())
   {
      return FALSE;
   }
   CDBStyleCostData_V *pStyleCost = GetItem(nIndex);
   delete pStyleCost;
   pStyleCost = NULL;
   RemoveAt(FindIndex(nIndex));

   return TRUE;
}

BOOL CDBStyleCostList_V::DeleteItemByCostItem( CString strCostItem )
{
   for (int nIndex =0;nIndex < GetCount();nIndex++)
   {
      auto pAuto = GetItem(nIndex);
      if (pAuto->m_strCostItem == strCostItem)
      {
         return DeleteItem(nIndex);
      }
   }

   return FALSE;
}

void CDBStyleCostList_V::GetDBDataByStyleNo( CADOConn *pADOConn,CString strStyleNo )
{
   ASSERT(pADOConn != NULL);
   Empty();
   CString strSQL;
   strSQL.Format(_T("select * from %s where %s = '%s'"),DB_VIEW_STYLE_COST,DBStyleCost_V_cStyleNo,strStyleNo);

   pADOConn->GetRecordSet(strSQL);

   while(!pADOConn->adoEOF())
   {
       CDBStyleCostData_V DBCostData;
       DBCostData.GetAllDBInfo(pADOConn);
       AddItem(&DBCostData);
       pADOConn->MoveNext();
   }

}

void CDBStyleCostList_V::Copy(CDBStyleCostList_V *pList)
{
   if (pList != NULL)
   {
      for (int nIndex = 0;nIndex < pList->GetCount();nIndex++)
      {
         CDBStyleCostData_V *pData =(CDBStyleCostData_V *)pList->GetAt(pList->FindIndex(nIndex));
         if (pData != NULL)
         {
            AddItem(pData);
         }
      }
   }
}
