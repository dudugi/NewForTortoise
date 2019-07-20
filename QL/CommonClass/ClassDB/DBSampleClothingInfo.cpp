#include "StdAfx.h"
#include "DBSampleClothingInfo.h"
#include "DBKeyDef.h"
IMPLEMENT_SERIAL(CDBSampleClothingInfo,CDataMid,1)
IMPLEMENT_SERIAL(CDBSampleClothingInfoList,CDataListMid,1)

CDBSampleClothingInfo::CDBSampleClothingInfo()
{
   ResetData();
}

CDBSampleClothingInfo::~CDBSampleClothingInfo()
{
}

void CDBSampleClothingInfo::ResetData()   
{
   m_ID = 0;
   m_strKuanhao = _T("");
   m_strMainColor = _T("");      //主色
   m_strSize = _T("");           //尺码
   m_strBarCode = _T("");        //条码
   m_strCreator = _T("");        //创建人
   m_strMakeTime = _T("");       //成衣时间
   m_strKeeper = _T("");         //保管人
   m_strKeepLocation = _T("");   //保管地点
   m_strMemo = _T("");           //样衣备注
   m_LendReturnState = 1;   //当前样衣状态 0借出，1归还
   m_strCate = _T("");
}

void CDBSampleClothingInfo::Copy( CDBSampleClothingInfo *pData )
{
   ASSERT(pData!=NULL);
   CDataMid::Copy(pData);
   m_ID = pData->m_ID;
   m_strKuanhao = pData->m_strKuanhao;
   m_strMainColor = pData->m_strMainColor;      //主色
   m_strSize = pData->m_strSize;           //尺码
   m_strBarCode = pData->m_strBarCode;        //条码
   m_strCreator = pData->m_strCreator;        //创建人
   m_strMakeTime = pData->m_strMakeTime;       //成衣时间
   m_strKeeper = pData->m_strKeeper;         //保管人
   m_strKeepLocation = pData->m_strKeepLocation;   //保管地点
   m_strMemo = pData->m_strMemo;           //样衣备注
   m_LendReturnState = pData->m_LendReturnState;   //当前样衣状态 0借出，1归还
   m_strCate= pData->m_strCate;
}

BOOL CDBSampleClothingInfo::GetAllDBInfo( CADOConn *pADOConn )
{
   ASSERT(pADOConn != NULL);
   m_ID = pADOConn->GetValueInt(DBSampleClothingInfo_Key_ID);
   m_strKuanhao = pADOConn->GetValueString(DBSampleClothingInfo_Key_cKuanhao);
   m_strMainColor = pADOConn->GetValueString(DBSampleClothingInfo_Key_cMainColor);      //主色
   m_strSize = pADOConn->GetValueString(DBSampleClothingInfo_Key_cSize);            //尺码
   m_strBarCode = pADOConn->GetValueString(DBSampleClothingInfo_Key_cBarCode);        //条码
   m_strCreator = pADOConn->GetValueString(DBSampleClothingInfo_Key_Creator);        //创建人
   m_strMakeTime = pADOConn->GetValueString(DBSampleClothingInfo_Key_MakeTime);       //成衣时间
   m_strKeeper = pADOConn->GetValueString(DBSampleClothingInfo_Key_Keeper);         //保管人
   m_strKeepLocation = pADOConn->GetValueString(DBSampleClothingInfo_Key_KeepLocation);   //保管地点
   m_strMemo = pADOConn->GetValueString(DBSampleClothingInfo_Key_Memo);           //样衣备注
   m_LendReturnState = pADOConn->GetValueInt(DBSampleClothingInfo_Key_LendReturnState);   //当前样衣状态 0借出，1归还
   m_strCate = pADOConn->GetValueString(DBSampleClothingInfo_Key_cCate);
   return TRUE;
}

BOOL CDBSampleClothingInfo::Insert(CADOConn *pADOConn)
{
   ASSERT(pADOConn != NULL);
   return pADOConn->ExecuteSQL(GetInsertSql());
}

BOOL CDBSampleClothingInfo::Update(CADOConn *pADOConn)
{
   ASSERT(pADOConn != NULL);
   return  pADOConn->ExecuteSQL(GetUpdateSql());
}

BOOL CDBSampleClothingInfo::Del(CADOConn *pADOConn)
{
   ASSERT(pADOConn != NULL);
   return  pADOConn->ExecuteSQL(GetDelSql());
}

CString CDBSampleClothingInfo::GetInsertSql()
{
   CString strSql;
   strSql.Format(_T("insert into %s (%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s) values ('%s','%s','%s','%s','%s','%s','%s','%s','%s',%d,'%s')"),
      DB_TABLE_SAMPLE_CLOTHING_INFO,
      DBSampleClothingInfo_Key_cKuanhao      ,
      DBSampleClothingInfo_Key_cMainColor    ,     
      DBSampleClothingInfo_Key_cSize         ,
      DBSampleClothingInfo_Key_cBarCode      ,
      DBSampleClothingInfo_Key_Creator       ,
      DBSampleClothingInfo_Key_MakeTime      ,
      DBSampleClothingInfo_Key_Keeper        ,
      DBSampleClothingInfo_Key_KeepLocation   ,
      DBSampleClothingInfo_Key_Memo          ,
      DBSampleClothingInfo_Key_LendReturnState,
      DBSampleClothingInfo_Key_cCate,
      m_strKuanhao,
      m_strMainColor,   
      m_strSize,        
      m_strBarCode,     
      m_strCreator,     
      m_strMakeTime,    
      m_strKeeper,      
      m_strKeepLocation,
      m_strMemo,        
      m_LendReturnState,
      m_strCate);
   return strSql;
}

CString CDBSampleClothingInfo::GetUpdateSql()
{
   //根据条码号更新数据
   CString strSql;
   strSql.Format(_T("update %s set %s='%s',%s='%s',%s='%s',%s='%s',%s='%s',%s='%s',%s='%s',%s='%s',%s='%s',%s='%s' where %s='%s'"),DB_TABLE_SAMPLE_CLOTHING_INFO,
      DBSampleClothingInfo_Key_cKuanhao,m_strKuanhao,
      DBSampleClothingInfo_Key_cMainColor,m_strMainColor,
      DBSampleClothingInfo_Key_cSize,m_strSize,
      DBSampleClothingInfo_Key_Creator,m_strCreator,
      DBSampleClothingInfo_Key_MakeTime,m_strMakeTime,
      DBSampleClothingInfo_Key_Keeper,m_strKeeper,
      DBSampleClothingInfo_Key_KeepLocation,m_strKeepLocation,
      DBSampleClothingInfo_Key_Memo,m_strMemo,
      DBSampleClothingInfo_Key_LendReturnState,m_LendReturnState,
      DBSampleClothingInfo_Key_cCate,m_strCate,
      DBSampleClothingInfo_Key_cBarCode,m_strBarCode);
   return strSql;
}

CString CDBSampleClothingInfo::GetDelSql()
{
   //根据条码号删除数据
   CString strSql;
   strSql.Format(_T("delete from %s where %s = %s;"),DB_TABLE_SAMPLE_CLOTHING_INFO,DBSampleClothingInfo_Key_cBarCode,m_strBarCode);
   return strSql;
}

CDBSampleClothingInfo* CDBSampleClothingInfoList::GetItem( int nIndex )
{
   if (nIndex <0 || nIndex>=GetCount())
   {
      return NULL;
   }

   return (CDBSampleClothingInfo *) GetAt(FindIndex(nIndex));
}


/**************************************** CDBSampleClothingInfoList **********************************************************/ 
std::shared_ptr<CDBSampleClothingInfoList> CDBSampleClothingInfoList::sm_inst;

CDBSampleClothingInfoList * CDBSampleClothingInfoList::Instance()
{
   if(sm_inst.get() == 0)
      sm_inst = shared_ptr<CDBSampleClothingInfoList>(new CDBSampleClothingInfoList);

   return sm_inst.get();
}


CDBSampleClothingInfoList::CDBSampleClothingInfoList()
{

}

CDBSampleClothingInfoList::~CDBSampleClothingInfoList()
{

}

void CDBSampleClothingInfoList::AddItem( CDBSampleClothingInfo* pItem )
{
   ASSERT(pItem != NULL);
   CDBSampleClothingInfo *pTail = new CDBSampleClothingInfo;
   pTail->Copy(pItem);

   AddTail(pTail);
}

BOOL CDBSampleClothingInfoList::DeleteItem( int nIndex )
{
   if (nIndex <0 || nIndex>=GetCount())
   {
      return FALSE;
   }
   CDBSampleClothingInfo *pStyleCost = GetItem(nIndex);
   delete pStyleCost;
   pStyleCost = NULL;
   RemoveAt(FindIndex(nIndex));

   return TRUE;
}

void CDBSampleClothingInfoList::Copy(CDBSampleClothingInfoList *pList)
{
   if (pList != NULL)
   {
      for (int nIndex = 0;nIndex < pList->GetCount();nIndex++)
      {
         CDBSampleClothingInfo *pData =(CDBSampleClothingInfo *)pList->GetAt(pList->FindIndex(nIndex));
         if (pData != NULL)
         {
            AddItem(pData);
         }
      }
   }
}

BOOL CDBSampleClothingInfoList::GetSampleClothingDataByBarCode(__in CADOConn* pAdo,__in CString strBarCode,__out CDBSampleClothingInfo* pData)
{
   if (pData == nullptr)
   {
      pData = new CDBSampleClothingInfo;
   }
   pData->ResetData();

   if (strBarCode.IsEmpty())
      return FALSE;

   ASSERT(pAdo != NULL);

   CString strSql;
   strSql.Format(_T("select * from %s where %s = '%s';"),DB_TABLE_SAMPLE_CLOTHING_INFO,DBSampleClothingInfo_Key_cBarCode,strBarCode);
   pAdo->GetRecordSet(strSql);
   if (!pAdo->adoEOF())
   {
      pData->GetAllDBInfo(pAdo);
      return TRUE;
   }
   return FALSE;
}

#ifdef USING_GRIDCTRL_MARK
BOOL CDBSampleClothingInfoList::GetSampleClothingListGridData(__in CADOConn* pAdo,__in CString strStyleNo,__out MAP_GridCtrl_AllData& all_data,__out set<CString>& setBarCode)
{
   setBarCode.clear();
   all_data.clear();
   ASSERT(pAdo != NULL);
   if (strStyleNo.IsEmpty())
      return FALSE;

   CString strSql;
   strSql.Format(_T("select * from %s where %s = '%s';"),DB_TABLE_SAMPLE_CLOTHING_INFO,DBSampleClothingInfo_Key_cKuanhao,strStyleNo);
   pAdo->GetRecordSet(strSql);
   while(!pAdo->adoEOF())
   {
      CDBSampleClothingInfo oData;
      oData.GetAllDBInfo(pAdo);

      MAP_GridCtrl_RowData row_data;
      CString strValue;
      strValue.Format(_T("%d"),oData.m_ID);
      InsertRowData(DBSampleClothingInfo_Key_ID             ,strValue,row_data);
      InsertRowData(DBSampleClothingInfo_Key_cKuanhao       ,oData.m_strKuanhao,row_data);
      InsertRowData(DBSampleClothingInfo_Key_cMainColor      ,oData.m_strMainColor,row_data);
      InsertRowData(DBSampleClothingInfo_Key_cSize          ,oData.m_strSize,row_data);
      InsertRowData(DBSampleClothingInfo_Key_cBarCode       ,oData.m_strBarCode,row_data);
      InsertRowData(DBSampleClothingInfo_Key_Creator        ,oData.m_strCreator,row_data);
      InsertRowData(DBSampleClothingInfo_Key_MakeTime       ,oData.m_strMakeTime,row_data);
      InsertRowData(DBSampleClothingInfo_Key_Keeper         ,oData.m_strKeeper,row_data);
      InsertRowData(DBSampleClothingInfo_Key_KeepLocation    ,oData.m_strKeepLocation,row_data);
      InsertRowData(DBSampleClothingInfo_Key_Memo           ,oData.m_strMemo,row_data);
      InsertRowData(DBSampleClothingInfo_Key_LendReturnState ,oData.m_LendReturnState==0?_T("借出"):_T("归还"),row_data);
      all_data.insert(make_pair(all_data.size(),row_data));

      setBarCode.insert(oData.m_strBarCode); //条码号
      pAdo->MoveNext();
   }
   return TRUE;
}

#endif
