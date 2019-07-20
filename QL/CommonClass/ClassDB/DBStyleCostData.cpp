#include "StdAfx.h"
#include "DBStyleCostData.h"
#include "DBKeyDef.h"
IMPLEMENT_SERIAL(CDBStyleCostData,CDataMid,1)
IMPLEMENT_SERIAL(CDBStyleCostList,CDataListMid,1)

#ifdef USING_GRIDCTRL_MARK
void CDBStyleCostList::CreateGridData( MAP_GridCtrl_AllData & map_allData )
{
   map_allData.clear();
   for (int nIndex =0;nIndex <GetCount();nIndex++)
   {
     auto pAuto = GetItem(nIndex);
     if (pAuto != NULL)
     {
        MAP_GridCtrl_RowData mapRowData;
        InsertRowData(DBStyleCost_cStyleNo,mapRowData,CB_enum_FieldData_CString,CB_enum_FieldCtrl_Text,pAuto->m_strStyleNo);
        InsertRowData(DBStyleCost_cCostItem,mapRowData,CB_enum_FieldData_CString,CB_enum_FieldCtrl_Text,pAuto->m_strCostItem);
        InsertRowData(DBStyleCost_cCostType,mapRowData,CB_enum_FieldData_CString,CB_enum_FieldCtrl_Text,pAuto->m_strCostType);
        InsertRowData(DBStyleCost_cCostJinE,mapRowData,CB_enum_FieldData_CString,CB_enum_FieldCtrl_Text,pAuto->m_strCostJinE);

        map_allData.insert(make_pair(nIndex,mapRowData));
     }
   }
}
#endif // USING_GRIDCTRL_MARK

std::shared_ptr<CDBStyleCostList> CDBStyleCostList::sm_inst;

CDBStyleCostData::CDBStyleCostData()
{
   ResetData();
}

CDBStyleCostData::~CDBStyleCostData()
{
}

void CDBStyleCostData::Serialize(CArchive& ar)
{
   int dateSize=0;
   int tagsize=0;
   CString strname;
   int namesize;
   ar.Flush();
   if (ar.IsStoring())
   {
      MySerial.SaveDataInt(ar,_T("COSTID00"),m_ID          );
      MySerial.SaveDataStr(ar,_T("STYLENO0"),m_strStyleNo  );
      MySerial.SaveDataStr(ar,_T("COSTITEM"),m_strCostItem );
      MySerial.SaveDataStr(ar,_T("COSTTYPE"),m_strCostType );
      MySerial.SaveDataStr(ar,_T("COSTJINE"),m_strCostJinE );
      MySerial.SaveDataDouble(ar,_T("COSTPRIC"),m_fCostPrice);
      MySerial.SaveDataDouble(ar,_T("COSTADDV"),m_fCostAddedValue );
      MySerial.SaveDataDouble(ar,_T("SALEPRIC"),m_fSalesPrice     );
      MySerial.SaveDataDouble(ar,_T("SALEADDV"),m_fSalesAddedValue);
      MySerial.SaveDataDouble(ar,_T("CALACULA"),m_fCalculatedValue);

      namesize=8;
      strname=_T("DENDDEND");
      ar << namesize;
      ar << strname;
   }
   else
   {
      int nNumber=0;
      ar >> namesize;
      ar >> strname;
      if(strname.GetLength()!=namesize)return;

      while(strname != _T("DENDDEND"))
      {
         if(nNumber > 150)
         {
            return;
         }
         else if(strname== _T("COSTID00")){ar >> tagsize >> m_ID              ;}
         else if(strname== _T("STYLENO0")){ar >> tagsize >> m_strStyleNo      ;}
         else if(strname== _T("COSTITEM")){ar >> tagsize >> m_strCostItem     ;}
         else if(strname== _T("COSTTYPE")){ar >> tagsize >> m_strCostType     ;}
         else if(strname== _T("COSTJINE")){ar >> tagsize >> m_strCostJinE     ;}
         else if(strname== _T("COSTPRIC")){ar >> tagsize >> m_fCostPrice      ;}
         else if(strname== _T("COSTADDV")){ar >> tagsize >> m_fCostAddedValue ;}
         else if(strname== _T("SALEPRIC")){ar >> tagsize >> m_fSalesPrice     ;}
         else if(strname== _T("SALEADDV")){ar >> tagsize >> m_fSalesAddedValue;}
         else if(strname== _T("CALACULA")){ar >> tagsize >> m_fCalculatedValue;}
         //2016/12/28_end
         else
         {
            ar >> tagsize;
            ar.Flush();
            ar.GetFile()->Seek( tagsize, CFile::current);//2016/08/02 zhangt 优化串行化读取
         }
         strname=_T("");
         ar >> namesize;
         ar >> strname;
         if(strname.GetLength()!=namesize)
            return;
         nNumber++;
      }
   }
}

void CDBStyleCostData::ResetData()   
{
   m_ID          = 0      ;
   m_strStyleNo  = _T("") ;
   m_strCostItem = _T("") ;
   m_strCostType = _T("") ;
   m_strCostJinE = _T("") ; 
   m_fCostPrice       = 0 ;
   m_fCostAddedValue  = 0 ;
   m_fSalesPrice      = 0 ;
   m_fSalesAddedValue = 0 ;
   m_fCalculatedValue = 0 ;

   SetDataType(DAT_STYLE_COST);
}

void CDBStyleCostData::Copy( CDBStyleCostData *pData )
{
   ASSERT(pData!=NULL);
   CDataMid::Copy(pData);

   m_ID          = pData->m_ID          ;   //ID 
   m_strStyleNo  = pData->m_strStyleNo  ;   //款号      
   m_strCostItem = pData->m_strCostItem ;   //成本项
   m_strCostType = pData->m_strCostType ;   //成本类别
   m_strCostJinE = pData->m_strCostJinE ;   //成本金额
   m_fCostPrice       = pData->m_fCostPrice       ;
   m_fCostAddedValue  = pData->m_fCostAddedValue  ;
   m_fSalesPrice      = pData->m_fSalesPrice      ;
   m_fSalesAddedValue = pData->m_fSalesAddedValue ;
   m_fCalculatedValue = pData->m_fCalculatedValue ;
}

BOOL CDBStyleCostData::GetAllDBInfo( CADOConn *pADOConn )
{
   ASSERT(pADOConn != NULL);

   m_ID          = pADOConn->GetValueInt64(DBStyleCost_ID);
   m_strStyleNo  = pADOConn->GetValueString(DBStyleCost_cStyleNo);
   m_strCostItem = pADOConn->GetValueString(DBStyleCost_cCostItem);
   m_strCostType = pADOConn->GetValueString(DBStyleCost_cCostType);
   m_strCostJinE = pADOConn->GetValueString(DBStyleCost_cCostJinE);
   m_fCostPrice       = pADOConn->GetValueDouble(DBStyleCost_fCostPrice      );
   m_fCostAddedValue  = pADOConn->GetValueDouble(DBStyleCost_fCostAddedValue );
   m_fSalesPrice      = pADOConn->GetValueDouble(DBStyleCost_fSalesPrice     );
   m_fSalesAddedValue = pADOConn->GetValueDouble(DBStyleCost_fSalesAddedValue);
   m_fCalculatedValue = pADOConn->GetValueDouble(DBStyleCost_fCalculatedValue);

   return TRUE;
}

CString CDBStyleCostData::GetDeleteByStyleNoSql(const CString & strStyleNo)
{
   CString strSQL = _T("");
   strSQL.Format(_T("delete from %s where %s='%s';"),DB_TABLE_STYLE_COST,
      DBStyleCost_cStyleNo,strStyleNo);
   return strSQL;
}

CDBStyleCostData* CDBStyleCostList::GetItem( int nIndex )
{
   if (nIndex <0 || nIndex>=GetCount())
   {
      return NULL;
   }

   return (CDBStyleCostData *) GetAt(FindIndex(nIndex));
}

CDBStyleCostData* CDBStyleCostList::GetItemByCostItem( CString strCostItem )
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

CDBStyleCostList::CDBStyleCostList()
{

}

CDBStyleCostList::~CDBStyleCostList()
{

}

void CDBStyleCostList::Serialize(CArchive& ar)
{
   int dateSize=0;
   int tagsize=0;
   CString strname;
   int namesize;
   ar.Flush();
   if (ar.IsStoring())
   {
      MySerial.SaveDataObjectList(ar,_T("COSTLIST"),this);
      namesize=8;
      strname=_T("DENDDEND");
      ar << namesize;
      ar << strname;
   }
   else
   {
      int nNumber=0;
      ar >> namesize;
      ar >> strname;
      if(strname.GetLength()!=namesize)return;
      Empty();

      while(strname != _T("DENDDEND"))
      {
         if(nNumber > 150)
         {
            return;
         }	

         if(strname== _T("COSTLIST"))
         {
            int dateSize;
            ar >> tagsize;
            ar >> dateSize;
            for(int i=0; i<dateSize; i++)
            {
               CDBStyleCostData* pPZ=new CDBStyleCostData;
               pPZ->Serialize(ar);
               AddTail(pPZ);
            }
         }
         else
         {
            ar >> tagsize;
            ar.Flush();
            ar.GetFile()->Seek( tagsize, CFile::current);//2016/08/02 zhangt 优化串行化读取
         }
         strname=_T("");
         ar >> namesize;
         ar >> strname;
         if(strname.GetLength()!=namesize)
            return;
         nNumber++;
      }
   }
}

void CDBStyleCostList::AddItem( CDBStyleCostData* pItem )
{
   ASSERT(pItem != NULL);
   CDBStyleCostData *pTail = new CDBStyleCostData;
   pTail->Copy(pItem);

   AddTail(pTail);
}

BOOL CDBStyleCostList::DeleteItem( int nIndex )
{
   if (nIndex <0 || nIndex>=GetCount())
   {
      return FALSE;
   }
   CDBStyleCostData *pStyleCost = GetItem(nIndex);
   delete pStyleCost;
   pStyleCost = NULL;
   RemoveAt(FindIndex(nIndex));

 return TRUE;
}

BOOL CDBStyleCostList::DeleteItemByCostItem( CString strCostItem )
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

BOOL CDBStyleCostList::BatchInsertDataToDB( CADOConn *pADOConn )
{
   ASSERT(pADOConn != NULL);

   std::vector<CString> vecSQL;
   CString strSQL,strCheckExistSQL;
   for (int nIndex = 0; nIndex <GetCount();nIndex++)
   {
      auto pAuto = GetItem(nIndex);
      if (pAuto != NULL)
      {
         //缺少数据  暂不清楚  临时修改 wangzl 2019-5-28
         //strSQL.Format(_T("select count(*) from %s where %s = '%s' and %s = '%s' and %s = '%s'"),DB_TABLE_STYLE_COST,DBStyleCost_cStyleNo,pAuto->m_strStyleNo,DBStyleCost_cCostItem,pAuto->m_strCostItem);
         strCheckExistSQL.Format(_T("select * from %s where %s = '%s' and %s = '%s' "),DB_TABLE_STYLE_COST,DBStyleCost_cStyleNo,pAuto->m_strStyleNo,DBStyleCost_cCostItem,pAuto->m_strCostItem);

         strSQL.Format(_T("if exists (%s) \
                          update %s Set %s = '%s',%s = '%.4f',%s = '%.4f',%s = '%.4f',%s = '%.4f',%s = '%.4f' Where %s = '%s' and %s = '%s' \
                          else \
                          insert into %s (%s,%s,%s,%s,%s,%s,%s,%s) values('%s','%s','%s','%.4f','%.4f','%.4f','%.4f','%.4f')"),
                          strCheckExistSQL,//end if condition
                          DB_TABLE_STYLE_COST,
                          DBStyleCost_cCostType,pAuto->m_strCostType,
                          DBStyleCost_fCostPrice      ,pAuto->m_fCostPrice,
                          DBStyleCost_fCostAddedValue ,pAuto->m_fCostAddedValue,
                          DBStyleCost_fSalesPrice     ,pAuto->m_fSalesPrice,
                          DBStyleCost_fSalesAddedValue,pAuto->m_fSalesAddedValue,
                          DBStyleCost_fCalculatedValue,pAuto->m_fCalculatedValue,
                          DBStyleCost_cStyleNo,pAuto->m_strStyleNo,DBStyleCost_cCostItem,pAuto->m_strCostItem,//end update
                          DB_TABLE_STYLE_COST,
                          DBStyleCost_cStyleNo,DBStyleCost_cCostItem,
                          DBStyleCost_cCostType       ,DBStyleCost_fCostPrice      ,
                          DBStyleCost_fCostAddedValue ,DBStyleCost_fSalesPrice     ,
                          DBStyleCost_fSalesAddedValue,DBStyleCost_fCalculatedValue,
                          pAuto->m_strStyleNo         ,pAuto->m_strCostItem,
                          pAuto->m_strCostType        ,pAuto->m_fCostPrice,
                          pAuto->m_fCostAddedValue    ,pAuto->m_fSalesPrice,
                          pAuto->m_fSalesAddedValue   ,pAuto->m_fCalculatedValue
                          );

        /* if (!pADOConn->adoEOF())
         {
            strSQL.Format(_T("update %s Set %s = '%s',%s = '%s' Where %s = '%s' and %s = '%s'"),DB_TABLE_STYLE_COST,DBStyleCost_cCostType,pAuto->m_strCostType,DBStyleCost_cCostJinE,pAuto->m_strCostJinE,DBStyleCost_cStyleNo,pAuto->m_strStyleNo,DBStyleCost_cCostItem,pAuto->m_strCostItem);
         } 
         else
         {
            strSQL.Format(_T("insert into %s (%s,%s,%s,%s) values('%s','%s','%s','%s')"),DB_TABLE_STYLE_COST,DBStyleCost_cStyleNo,DBStyleCost_cCostItem,DBStyleCost_cCostType,DBStyleCost_cCostJinE,pAuto->m_strStyleNo,pAuto->m_strCostItem,pAuto->m_strCostType,pAuto->m_strCostJinE);
         }*/

         vecSQL.push_back(strSQL);

      }
   }

   if(vecSQL.size()>0&&pADOConn->ExecuteSQLByTransaction(vecSQL))
   {
      return TRUE;
   }
   else
   {
      return FALSE;
   }
}

void CDBStyleCostList::GetDBDataByStyleNo( CADOConn *pADOConn,CString strStyleNo )
{
   ASSERT(pADOConn != NULL);
   Empty();
   CString strSQL;
   strSQL.Format(_T("select * from %s where %s = '%s'"),DB_TABLE_STYLE_COST,DBStyleCost_cStyleNo,strStyleNo);

   pADOConn->GetRecordSet(strSQL);

   while(!pADOConn->adoEOF())
   {
       CDBStyleCostData DBCostData;
       DBCostData.GetAllDBInfo(pADOConn);

       AddItem(&DBCostData);

       pADOConn->MoveNext();
   }

}

void CDBStyleCostList::Copy(CDBStyleCostList *pList)
{
   if (pList != NULL)
   {
      for (int nIndex = 0;nIndex < pList->GetCount();nIndex++)
      {
         CDBStyleCostData *pData =(CDBStyleCostData *)pList->GetAt(pList->FindIndex(nIndex));
         if (pData != NULL)
         {
            AddItem(pData);
         }
      }
   }
}
