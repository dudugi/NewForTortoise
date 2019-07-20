#include "StdAfx.h"
#include "DBProductOrderInfo.h"
#include "DBKeyDef.h"

//***************** CDBProductOrderInfo *********************//
IMPLEMENT_SERIAL(CDBProductOrderInfo,  CDataMid, 1)

CDBProductOrderInfo::CDBProductOrderInfo(void)
{
   ResetData();
}

CDBProductOrderInfo::~CDBProductOrderInfo(void)
{
}

void CDBProductOrderInfo::ResetData()
{
   m_id =0;                // 自增ID
   m_strStyleNo =_T("");         //款号
   m_strProductOrder =_T("");     //生产单号
   m_strMainClrNo =_T("");
   m_strMainClrCate =_T("");
   m_strMainClrName =_T("");
   m_strSizeNumInfo =_T("");       //尺码数量信息：s(1);m(2);l(3);....   
   m_mapSizeInfo.clear();
   m_strDate  =_T(""); 
   m_iTotalNum = 0;
}

void CDBProductOrderInfo::Copy(CDBProductOrderInfo *pData)
{
   ASSERT(pData      != NULL);
   m_id = pData->m_id;                
   m_strStyleNo = pData->m_strStyleNo;     
   m_strProductOrder = pData->m_strProductOrder;
   m_strMainClrNo = pData->m_strMainClrNo;
   m_strMainClrCate = pData->m_strMainClrCate;
   m_strMainClrName = pData->m_strMainClrName;
   m_strSizeNumInfo = pData->m_strSizeNumInfo; 
   m_iTotalNum = pData->m_iTotalNum;
}

void CDBProductOrderInfo::GetAllDBInfo(CADOConn* pADOConn)
{
   ASSERT(pADOConn  != NULL);
   m_id                   =pADOConn->GetValueInt(DBProductOrderInfo_Key_ID);
   m_strStyleNo            =pADOConn->GetValueString(DBProductOrderInfo_Key_StyleNo);
   m_strProductOrder       =pADOConn->GetValueString(DBProductOrderInfo_Key_ProductOrder);
   m_strMainClrNo          =pADOConn->GetValueString(DBProductOrderInfo_Key_MainClrNo);
   m_strMainClrCate        =pADOConn->GetValueString(DBProductOrderInfo_Key_MainClrCate);
   m_strMainClrName        =pADOConn->GetValueString(DBProductOrderInfo_Key_MainClrName);
   m_strSizeNumInfo        =pADOConn->GetValueString(DBProductOrderInfo_Key_SizeNumInfo);
   m_strDate            = pADOConn->GetValueString(DBProductOrderInfo_Key_MakeDate);
   m_iTotalNum             = pADOConn->GetValueInt(DBProductOrderInfo_Key_TotalNum);
   ParaseSizeInfo(m_strSizeNumInfo,m_mapSizeInfo);
}

BOOL CDBProductOrderInfo::InsetAllDBInfo(CADOConn* pADOConn)
{
   ASSERT(pADOConn != NULL);
   return pADOConn->ExecuteSQL(GetInsertSql());
}

BOOL CDBProductOrderInfo::UpdateAllDBInfo(CADOConn* pADOConn)
{
   ASSERT(pADOConn != NULL);                                 
   return pADOConn->ExecuteSQL(GetUpdateSql());              
}                                                            
                                                             
BOOL CDBProductOrderInfo::DeleteAllDBInfo(CADOConn* pADOConn)
{                                                            
   ASSERT(pADOConn != NULL);
   return pADOConn->ExecuteSQL(GetDeleteSql());
}

CString CDBProductOrderInfo::GetInsertSql()
{
   CString strSql = _T("");
   strSql.Format(_T("insert into %s (%s,%s,%s,%s,%s,%s,%s,%s) \
                    values (%s,'%s','%s','%s','%s','%s','%s',%d); "), 
                    DB_TABLE_PRODUCTORDERINFO,    
                    DBProductOrderInfo_Key_MakeDate   ,  
                    DBProductOrderInfo_Key_ProductOrder ,
                    DBProductOrderInfo_Key_MainClrNo    ,
                    DBProductOrderInfo_Key_MainClrCate  ,
                    DBProductOrderInfo_Key_MainClrName  ,
                    DBProductOrderInfo_Key_SizeNumInfo  ,
                    DBProductOrderInfo_Key_StyleNo   ,
                    DBProductOrderInfo_Key_TotalNum,
                    DBS_GETDATESTR,
                    m_strProductOrder,
                    m_strMainClrNo,
                    m_strMainClrCate,
                    m_strMainClrName,
                    m_strSizeNumInfo,
                    m_strStyleNo,
                    m_iTotalNum
                    );
   return strSql;
}

CString CDBProductOrderInfo::GetUpdateSql()
{
   CString strSql = _T("");
   return strSql;
}

CString CDBProductOrderInfo::GetDeleteSql()
{
   CString strSql = _T("");
   strSql.Format(_T("delete from %s where %s = %d;"), DB_TABLE_PRODUCTORDERINFO, DBProductOrderInfo_Key_ID, m_id);
   return strSql;
}

CString CDBProductOrderInfo::GetDeleteSqlByStyleNo(CString strStyleNo)
{
   CString strSql = _T("");
   strSql.Format(_T("delete from %s where %s = '%s';"), DB_TABLE_PRODUCTORDERINFO, DBProductOrderInfo_Key_StyleNo, strStyleNo);
   return strSql;
}

void CDBProductOrderInfo::ParaseSizeInfo(const CString strSizeInfo,map<CString,CString>& mapSizeInfo)
{
   mapSizeInfo.clear();
   if (strSizeInfo.IsEmpty())
      return;

   int iPosBeg = 0,iPosEnd = 0,iLen = strSizeInfo.GetLength();
   iPosEnd = strSizeInfo.Find(_T(";"),iPosBeg);
   while(iPosEnd<iLen && iPosEnd >0)
   {
      CString strText = strSizeInfo.Mid(iPosBeg,iPosEnd-iPosBeg);
      CString strKey,strValue;
      int tPos1=0,tPos2=0;
      tPos2 = strText.Find(_T("("));
      strKey = strText.Mid(tPos1,tPos2-tPos1);
      tPos1 = tPos2 +1;
      tPos2 = strText.Find(_T(")"));
      strValue = strText.Mid(tPos1,tPos2-tPos1);
      mapSizeInfo.insert(make_pair(strKey,strValue));
      iPosBeg = iPosEnd+1;
      iPosEnd = strSizeInfo.Find(_T(";"),iPosBeg);
   }
}

void CDBProductOrderInfo::ParaseSizeInfo(const map<CString,CString> mapSizeInfo,CString& strSizeInfo,int& iTotalNum)
{
   strSizeInfo = _T("");
   if (mapSizeInfo.empty())
      return;

   iTotalNum = 0;
   for (auto itr_ = mapSizeInfo.begin();itr_ != mapSizeInfo.end(); ++itr_)
   {
      CString strValue;
      strValue.Format(_T("%s(%s);"),itr_->first,itr_->second);
      iTotalNum += _ttoi(itr_->second);
      strSizeInfo+=strValue;
   }
}

void CDBProductOrderInfo::CreateRowData(CDBProductOrderInfo* pData,MAP_GridCtrl_RowData& row_data)
{
   row_data.clear();
   if (pData)
   {
      CString strValue;
      strValue.Format(_T("%d"),pData->m_id);
      CDataMid::InsertRowData(DBProductOrderInfo_Key_ID,            row_data, FORMAT_STRING, strValue, CB_enum_FieldData_CString);
      CDataMid::InsertRowData(DBProductOrderInfo_Key_StyleNo,      row_data, FORMAT_STRING, pData->m_strStyleNo, CB_enum_FieldData_CString);
      CDataMid::InsertRowData(DBProductOrderInfo_Key_ProductOrder,   row_data, FORMAT_STRING, pData->m_strProductOrder, CB_enum_FieldData_CString);
      CDataMid::InsertRowData(DBProductOrderInfo_Key_MainClrNo,      row_data, FORMAT_STRING, pData->m_strMainClrNo, CB_enum_FieldData_CString);
      CDataMid::InsertRowData(DBProductOrderInfo_Key_MainClrCate,    row_data, FORMAT_STRING, pData->m_strMainClrCate, CB_enum_FieldData_CString);
      CDataMid::InsertRowData(DBProductOrderInfo_Key_MainClrName,    row_data, FORMAT_STRING, pData->m_strMainClrName, CB_enum_FieldData_CString);
      CDataMid::InsertRowData(DBProductOrderInfo_Key_SizeNumInfo,    row_data, FORMAT_STRING, pData->m_strSizeNumInfo, CB_enum_FieldData_CString);
      CDataMid::InsertRowData(DBProductOrderInfo_Key_MakeDate,    row_data, FORMAT_STRING, pData->m_strDate, CB_enum_FieldData_CString);
      strValue.Format(_T("%d"),pData->m_iTotalNum);
      CDataMid::InsertRowData(DBProductOrderInfo_Key_TotalNum,    row_data, FORMAT_STRING, strValue, CB_enum_FieldData_CString);
   }
}

//***************** CDBProductOrderInfoList *********************//                     

IMPLEMENT_SERIAL(CDBProductOrderInfoList, CDataMid, 1)

std::shared_ptr<CDBProductOrderInfoList> CDBProductOrderInfoList::sm_inst;

CDBProductOrderInfoList::CDBProductOrderInfoList(void)
{

}

CDBProductOrderInfoList::~CDBProductOrderInfoList(void)
{

}

CDBProductOrderInfoList * CDBProductOrderInfoList::Instance()
{
   if(sm_inst.get() == 0)
      sm_inst = shared_ptr<CDBProductOrderInfoList>(new CDBProductOrderInfoList);

   return sm_inst.get();
}

#ifdef USING_GRIDCTRL_MARK

void CDBProductOrderInfoList::GetGridDataInfo(CADOConn* pAdo,CString strStyleNo,MAP_GridCtrl_AllData& all_data)
{
   ASSERT(pAdo != NULL);
   all_data.clear();
   if (strStyleNo.IsEmpty())
      return;
   CString strSql;
   strSql.Format(_T("select * from %s where %s = '%s'"),DB_TABLE_PRODUCTORDERINFO,DBProductOrderInfo_Key_StyleNo,strStyleNo);
   pAdo->GetRecordSet(strSql);
   while(!pAdo->adoEOF())
   {
      CDBProductOrderInfo oData;
      oData.GetAllDBInfo(pAdo);

      MAP_GridCtrl_RowData row_data;
      CDBProductOrderInfo::CreateRowData(&oData,row_data);
      all_data.insert(make_pair(all_data.size(),row_data));

      pAdo->MoveNext();
   }
}

#endif

CDBProductOrderInfo* CDBProductOrderInfoList::GetItem(int nIndex)
{
   if (nIndex<0||nIndex>=GetCount())
      return NULL;
   return (CDBProductOrderInfo*)GetAt(FindIndex(nIndex));
}

void CDBProductOrderInfoList::AddItem(CDBProductOrderInfo* pItem)
{
   CDBProductOrderInfo*pData=new CDBProductOrderInfo;
   pData->Copy(pItem);
   AddTail(pData);
}

void CDBProductOrderInfoList::DeleteItem(int nIndex)
{
   if (nIndex<0||nIndex>GetCount())
      return;
   CDBProductOrderInfo *pObject=(CDBProductOrderInfo*)GetItem(nIndex);
   delete pObject;
   pObject=NULL;
   RemoveAt(FindIndex(nIndex));
}

void CDBProductOrderInfoList::GetProductOrderRecords(CADOConn* pAdo,CString strID,__out map<CString,tuple<CString,CString>>& mapColorInfo,__out map<CString,map<CString,CString>>& mapSizeInfo)
{
   ASSERT(pAdo != NULL);
   if (strID.IsEmpty())
      return;

   mapColorInfo.clear();
   mapSizeInfo.clear();

   CString strSql;
   strSql.Format(_T("select * from %s where %s = %s"),DB_TABLE_PRODUCTORDERINFO,DBProductOrderInfo_Key_ID,strID);
   pAdo->GetRecordSet(strSql);
   if (!pAdo->adoEOF())
   {
      CDBProductOrderInfo oData;
      oData.GetAllDBInfo(pAdo);
      oData.ParaseSizeInfo(oData.m_strSizeNumInfo,oData.m_mapSizeInfo);
      mapColorInfo.insert(make_pair(oData.m_strMainClrNo,std::make_tuple(oData.m_strMainClrCate,oData.m_strMainClrName)));
      mapSizeInfo.insert(make_pair(oData.m_strMainClrNo,oData.m_mapSizeInfo));
   }
}


