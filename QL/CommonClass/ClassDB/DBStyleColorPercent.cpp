#include "StdAfx.h"
#include "DBStyleColorPercent.h"
#include "DBKeyDef.h"

//***************** CDBStyleColorPercent *********************//
IMPLEMENT_SERIAL(CDBStyleColorPercent,  CDataMid, 1)

CDBStyleColorPercent::CDBStyleColorPercent(void)
{
   ResetData();
}

CDBStyleColorPercent::~CDBStyleColorPercent(void)
{
}

void CDBStyleColorPercent::ResetData()
{
   m_id        =0  ;         // 自增ID  = 0;
   m_nRow       =0;         //行号  = 0;
   m_nPeiSeNum  = 0;
   m_strStyleNo  = _T("");         // 款号 = _T("");
   m_strMainClr  = _T("");         //主色 = _T("");
   m_strFirst     = _T("");             //配色1 = _T("");
   m_strSecond   = _T("");         //配色2 = _T("");
   m_strThird    = _T("");         //配色3 = _T("");
   m_strFourth   = _T("");         //配色4 = _T("");
   m_strFifth    = _T("");         //配色5 = _T("");
   m_strSixth    = _T("");         //配色6 = _T("");
   m_isWeight    = 0 ;        //是否是重量数据
   m_strSizeInfo  = _T("");
   m_strPinZhong = _T("");
   m_strSeMing = _T("");
   m_strShazhi = _T("");
  }

void CDBStyleColorPercent::Copy(CDBStyleColorPercent *pData)
{
   ASSERT(pData      != NULL);
   m_id              = pData->m_id;
   m_nRow            = pData->m_nRow;
   m_nPeiSeNum       = pData->m_nPeiSeNum;
   m_strStyleNo      = pData->m_strStyleNo;
   m_strMainClr      = pData->m_strMainClr;
   m_strFirst        = pData->m_strFirst;
   m_strSecond       = pData->m_strSecond;
   m_strThird        = pData->m_strThird;
   m_strFourth       = pData->m_strFourth;
   m_strFifth        = pData->m_strFifth;
   m_strSixth        = pData->m_strSixth;
   m_isWeight        = pData->m_isWeight;
   m_strSizeInfo     = pData->m_strSizeInfo;
   m_mapSizeInfo = pData->m_mapSizeInfo;
   m_strShazhi = pData->m_strShazhi;
}

void CDBStyleColorPercent::GetAllDBInfo(CADOConn* pADOConn)
{
   ASSERT(pADOConn  != NULL);
   m_id           = pADOConn->GetValueInt   (DBStyleColor_ID        );
   m_nRow         = pADOConn->GetValueInt   (DBStyleColor_nRowNo        );
   m_nPeiSeNum    = pADOConn->GetValueInt(DBStyleColor_nPeiSeNum);
   m_strStyleNo   = pADOConn->GetValueString(DBStyleColor_nWeight   );
   m_strMainClr   = pADOConn->GetValueString(DBStyleColor_cMainClr);
   m_strFirst     = pADOConn->GetValueString(DBStyleColor_cFirst);
   m_strSecond    = pADOConn->GetValueString(DBStyleColor_cSecond   );
   m_strThird     = pADOConn->GetValueString(DBStyleColor_cThird    );
   m_strFourth    = pADOConn->GetValueString(DBStyleColor_cFourth   );
   m_strFifth     = pADOConn->GetValueString(DBStyleColor_cFifth    );
   m_strSixth     = pADOConn->GetValueString(DBStyleColor_cSixth    );
   m_isWeight      = pADOConn->GetValueInt(DBStyleColor_nWeight);
   m_strSizeInfo  = pADOConn->GetValueString(DBStyleColor_cSizeInfo    );
   ParaseSizeInfo(m_strSizeInfo,m_mapSizeInfo);
}

BOOL CDBStyleColorPercent::InsetAllDBInfo(CADOConn* pADOConn)
{
   ASSERT(pADOConn != NULL);
   return pADOConn->ExecuteSQL(GetInsertSql());
}

BOOL CDBStyleColorPercent::UpdateAllDBInfo(CADOConn* pADOConn)
{
   ASSERT(pADOConn != NULL);                                 
   return pADOConn->ExecuteSQL(GetUpdateSql());              
}                                                            
                                                             
BOOL CDBStyleColorPercent::DeleteAllDBInfo(CADOConn* pADOConn)
{                                                            
   ASSERT(pADOConn != NULL);
   return pADOConn->ExecuteSQL(GetDeleteSql());
}

CString CDBStyleColorPercent::GetInsertSql()
{
   CString strSql = _T("");
   strSql.Format(_T("insert into %s (%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s) \
                    values ('%d','%d','%s','%s','%s','%s','%s','%s','%s','%s','%d','%s'); "), 
                    DB_TABLE_STYLECOLORPERCENT,
                    DBStyleColor_nRowNo,   
                    DBStyleColor_nPeiSeNum,
                    DBStyleColor_cStyleNo,
                    DBStyleColor_cMainClr, 
                    DBStyleColor_cFirst,   
                    DBStyleColor_cSecond , 
                    DBStyleColor_cThird,   
                    DBStyleColor_cFourth,  
                    DBStyleColor_cFifth,   
                    DBStyleColor_cSixth,   
                    DBStyleColor_nWeight,
                    DBStyleColor_cSizeInfo,
                    m_nRow,     
                    m_nPeiSeNum,
                    m_strStyleNo, 
                    m_strMainClr, 
                    m_strFirst,  
                    m_strSecond,  
                    m_strThird,  
                    m_strFourth,  
                    m_strFifth,  
                    m_strSixth,  
                    m_isWeight,
                    m_strSizeInfo);
   return strSql;
}

CString CDBStyleColorPercent::GetUpdateSql()
{
   CString strSql = _T("");
   strSql.Format(_T("update %s set %s = '%d',%s = '%d',%s = '%s',%s = '%s',%s = '%s',\
                    %s = '%s',%s = '%s',%s = '%s',%s = '%s',%s = '%s'\
                     %s = '%d',%s = '%s' where %s = %d"),
      DB_TABLE_STYLECOLORPERCENT
      DBStyleColor_nRowNo     ,m_nRow,
      DBStyleColor_nPeiSeNum  ,m_nPeiSeNum,
      DBStyleColor_cStyleNo  , m_strStyleNo,
      DBStyleColor_cMainClr  , m_strMainClr,
      DBStyleColor_cFirst    , m_strFirst,
      DBStyleColor_cSecond   , m_strSecond,
      DBStyleColor_cThird    , m_strThird,
      DBStyleColor_cFourth   , m_strFourth,
      DBStyleColor_cFifth    , m_strFifth,
      DBStyleColor_cSixth    , m_strSixth,
      DBStyleColor_nWeight   , m_isWeight,
      DBStyleColor_cSizeInfo , m_strSizeInfo,
      DBStyleColor_ID        , m_id);
   return strSql;
}

CString CDBStyleColorPercent::GetDeleteSql()
{
   CString strSql = _T("");
   strSql.Format(_T("delete from %s where %s = %d;"), DB_TABLE_STYLECOLORPERCENT, DBStyleColor_ID, m_id);
   return strSql;
}

CString CDBStyleColorPercent::GetDeleteSqlByStyleNo(CString strStyleNo)
{
   CString strSql = _T("");
   strSql.Format(_T("delete from %s where %s = '%s';"), DB_TABLE_STYLECOLORPERCENT, DBStyleColor_cStyleNo, strStyleNo);
   return strSql;
}

void CDBStyleColorPercent::ParaseSizeInfo(const CString strSizeInfo,map<CString,CString>& mapSizeInfo)
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

void CDBStyleColorPercent::ParaseSizeInfo(const map<CString,CString> mapSizeInfo,CString& strSizeInfo)
{
   strSizeInfo = _T("");
   if (mapSizeInfo.empty())
      return;

   for (auto itr_ = mapSizeInfo.begin();itr_ != mapSizeInfo.end(); ++itr_)
   {
      CString strValue;
      strValue.Format(_T("%s(%s);"),itr_->first,itr_->second);
      strSizeInfo+=strValue;
   }
}

//***************** CDBStyleColorPercentList *********************//                     

IMPLEMENT_SERIAL(CDBStyleColorPercentList, CDataMid, 1)

std::shared_ptr<CDBStyleColorPercentList> CDBStyleColorPercentList::sm_inst;

CDBStyleColorPercentList::CDBStyleColorPercentList(void)
{

}

CDBStyleColorPercentList::~CDBStyleColorPercentList(void)
{

}

CDBStyleColorPercentList * CDBStyleColorPercentList::Instance()
{
   if(sm_inst.get() == 0)
      sm_inst = shared_ptr<CDBStyleColorPercentList>(new CDBStyleColorPercentList);

   return sm_inst.get();
}

#ifdef USING_GRIDCTRL_MARK
BOOL CDBStyleColorPercentList::GetStyleColorPercentInfo(CADOConn* pADOConn,CString strStyleNo,MAP_GridCtrl_AllData& all_data,int& nPSNum,int& nSZNum,map<CString,CString>& mapSize)
{
   ASSERT(pADOConn != NULL);
   mapSize.clear();
   all_data.clear();
   nPSNum = nSZNum = 0;

   if (!strStyleNo.IsEmpty())
   {
      CString strSql = _T("");
      strSql.Format(_T("select a.*,b.cCate,b.cSeming,b.cShazhi from %s as a \
                       left join Color as b on a.cMainClr = b.cSehao where cStyleNo = '%s' order by nRowNo;"), DB_TABLE_STYLECOLORPERCENT,strStyleNo);
      pADOConn->GetRecordSet(strSql);
      while (!pADOConn->adoEOF())
      {
         CDBStyleColorPercent oData;
         oData.GetAllDBInfo(pADOConn);
         oData.m_strPinZhong = pADOConn->GetValueString(DBColor_key_Cate);
         oData.m_strSeMing = pADOConn->GetValueString(DBColor_key_YarnName);
         oData.m_strShazhi = pADOConn->GetValueString(DBColor_key_ThickNess);
         oData.m_nPeiSeNum >nPSNum?nPSNum=oData.m_nPeiSeNum:0; 

         MAP_GridCtrl_RowData row_data;  
         if (oData.m_isWeight == 1)
         {
            CDataMid::InsertRowData(DBStyleColor_RowName, row_data, FORMAT_STRING, _T("重量"), CB_enum_FieldData_CString);
         }
         else
         {
            CString strRowName;
            strRowName.Format(_T("色组%d"),oData.m_nRow);
            CDataMid::InsertRowData(DBStyleColor_RowName, row_data, FORMAT_STRING, strRowName, CB_enum_FieldData_CString);
            ++nSZNum;
         }
         CDataMid::InsertRowData(DBStyleColor_cMainClr,   row_data, FORMAT_STRING, oData.m_strMainClr, CB_enum_FieldData_CString);
         CDataMid::InsertRowData(DBStyleColor_ColorName,   row_data, FORMAT_STRING, oData.m_strSeMing, CB_enum_FieldData_CString);
         CDataMid::InsertRowData(DBColor_key_Ingredient,   row_data, FORMAT_STRING, oData.m_strPinZhong, CB_enum_FieldData_CString);
         CDataMid::InsertRowData(DBStyleColor_cFirst,    row_data, FORMAT_STRING, oData.m_strFirst, CB_enum_FieldData_CString);
         CDataMid::InsertRowData(DBStyleColor_cSecond,    row_data, FORMAT_STRING,oData.m_strSecond, CB_enum_FieldData_CString);
         CDataMid::InsertRowData(DBStyleColor_cThird,     row_data, FORMAT_STRING,oData.m_strThird, CB_enum_FieldData_CString);
         CDataMid::InsertRowData(DBStyleColor_cFourth,    row_data, FORMAT_STRING,oData.m_strFourth, CB_enum_FieldData_CString);
         CDataMid::InsertRowData(DBStyleColor_cFifth,     row_data, FORMAT_STRING,oData.m_strFifth, CB_enum_FieldData_CString);
         CDataMid::InsertRowData(DBStyleColor_cSixth,     row_data, FORMAT_STRING,oData.m_strSixth, CB_enum_FieldData_CString);
         CDataMid::InsertRowData(DBColor_key_ThickNess,   row_data, FORMAT_STRING, oData.m_strShazhi, CB_enum_FieldData_CString);
         CDataMid::InsertRowData(DBStyleColor_cFirst_Name,    row_data, FORMAT_STRING, _T(""), CB_enum_FieldData_CString);
         CDataMid::InsertRowData(DBStyleColor_cSecond_Name,    row_data, FORMAT_STRING,_T(""), CB_enum_FieldData_CString);
         CDataMid::InsertRowData(DBStyleColor_cThird_Name,     row_data, FORMAT_STRING,_T(""), CB_enum_FieldData_CString);
         CDataMid::InsertRowData(DBStyleColor_cFourth_Name,    row_data, FORMAT_STRING,_T(""), CB_enum_FieldData_CString);
         CDataMid::InsertRowData(DBStyleColor_cFifth_Name,     row_data, FORMAT_STRING,_T(""), CB_enum_FieldData_CString);
         CDataMid::InsertRowData(DBStyleColor_cSixth_Name,     row_data, FORMAT_STRING,_T(""), CB_enum_FieldData_CString);
         for (auto itr_size = oData.m_mapSizeInfo.begin(); itr_size != oData.m_mapSizeInfo.end(); ++itr_size)
         {
            CDataMid::InsertRowData(itr_size->first,     row_data, FORMAT_STRING,itr_size->second, CB_enum_FieldData_CString);
            mapSize.insert(make_pair(itr_size->first,itr_size->second));
         }

         all_data.insert(make_pair(all_data.size(), row_data));
         pADOConn->MoveNext();
      }
   }
   
   if (all_data.size() <=0)
   {
      nSZNum = 1;
      CString strValue = _T("");
      for (int k=0;k<2;++k)
      {
         MAP_GridCtrl_RowData row_data; 
         if (k==0)
         {
            CDataMid::InsertRowData(DBStyleColor_RowName, row_data, FORMAT_STRING, _T("色组1"), CB_enum_FieldData_CString);
         }
         else
         {
            CDataMid::InsertRowData(DBStyleColor_RowName, row_data, FORMAT_STRING, _T("重量"), CB_enum_FieldData_CString);
         }
         CDataMid::InsertRowData(DBStyleColor_cMainClr,   row_data, FORMAT_STRING, strValue, CB_enum_FieldData_CString);
         CDataMid::InsertRowData(DBStyleColor_ColorName,   row_data, FORMAT_STRING, strValue, CB_enum_FieldData_CString);
         CDataMid::InsertRowData(DBColor_key_Ingredient,   row_data, FORMAT_STRING, strValue, CB_enum_FieldData_CString);
         CDataMid::InsertRowData(DBStyleColor_cFirst,    row_data, FORMAT_STRING, strValue, CB_enum_FieldData_CString);
         CDataMid::InsertRowData(DBStyleColor_cSecond,    row_data, FORMAT_STRING,strValue, CB_enum_FieldData_CString);
         CDataMid::InsertRowData(DBStyleColor_cThird,     row_data, FORMAT_STRING,strValue, CB_enum_FieldData_CString);
         CDataMid::InsertRowData(DBStyleColor_cFourth,    row_data, FORMAT_STRING,strValue, CB_enum_FieldData_CString);
         CDataMid::InsertRowData(DBStyleColor_cFifth,     row_data, FORMAT_STRING,strValue, CB_enum_FieldData_CString);
         CDataMid::InsertRowData(DBStyleColor_cSixth,     row_data, FORMAT_STRING,strValue, CB_enum_FieldData_CString);
         CDataMid::InsertRowData(DBColor_key_ThickNess,   row_data, FORMAT_STRING, strValue, CB_enum_FieldData_CString);
         CDataMid::InsertRowData(DBStyleColor_cFirst_Name,    row_data, FORMAT_STRING, _T(""), CB_enum_FieldData_CString);
         CDataMid::InsertRowData(DBStyleColor_cSecond_Name,    row_data, FORMAT_STRING,_T(""), CB_enum_FieldData_CString);
         CDataMid::InsertRowData(DBStyleColor_cThird_Name,     row_data, FORMAT_STRING,_T(""), CB_enum_FieldData_CString);
         CDataMid::InsertRowData(DBStyleColor_cFourth_Name,    row_data, FORMAT_STRING,_T(""), CB_enum_FieldData_CString);
         CDataMid::InsertRowData(DBStyleColor_cFifth_Name,     row_data, FORMAT_STRING,_T(""), CB_enum_FieldData_CString);
         CDataMid::InsertRowData(DBStyleColor_cSixth_Name,     row_data, FORMAT_STRING,_T(""), CB_enum_FieldData_CString);
         all_data.insert(make_pair(all_data.size(), row_data));
      }
   }
   else
   {
      if(nSZNum <=0)  //默认一个色组
      {
         nSZNum = 1;
         all_data.insert(make_pair(1,all_data.begin()->second));
         all_data.erase(all_data.begin());
         CString strValue = _T("");
         MAP_GridCtrl_RowData row_data; 
         CDataMid::InsertRowData(DBStyleColor_RowName, row_data, FORMAT_STRING, _T("色组1"), CB_enum_FieldData_CString);
         CDataMid::InsertRowData(DBStyleColor_cMainClr,   row_data, FORMAT_STRING, strValue, CB_enum_FieldData_CString);
         CDataMid::InsertRowData(DBStyleColor_ColorName,   row_data, FORMAT_STRING, strValue, CB_enum_FieldData_CString);
         CDataMid::InsertRowData(DBColor_key_Ingredient,   row_data, FORMAT_STRING, strValue, CB_enum_FieldData_CString);
         CDataMid::InsertRowData(DBStyleColor_cFirst,    row_data, FORMAT_STRING, strValue, CB_enum_FieldData_CString);
         CDataMid::InsertRowData(DBStyleColor_cSecond,    row_data, FORMAT_STRING,strValue, CB_enum_FieldData_CString);
         CDataMid::InsertRowData(DBStyleColor_cThird,     row_data, FORMAT_STRING,strValue, CB_enum_FieldData_CString);
         CDataMid::InsertRowData(DBStyleColor_cFourth,    row_data, FORMAT_STRING,strValue, CB_enum_FieldData_CString);
         CDataMid::InsertRowData(DBStyleColor_cFifth,     row_data, FORMAT_STRING,strValue, CB_enum_FieldData_CString);
         CDataMid::InsertRowData(DBStyleColor_cSixth,     row_data, FORMAT_STRING,strValue, CB_enum_FieldData_CString);
         CDataMid::InsertRowData(DBColor_key_ThickNess,   row_data, FORMAT_STRING, strValue, CB_enum_FieldData_CString);
         CDataMid::InsertRowData(DBStyleColor_cFirst_Name,    row_data, FORMAT_STRING, _T(""), CB_enum_FieldData_CString);
         CDataMid::InsertRowData(DBStyleColor_cSecond_Name,    row_data, FORMAT_STRING,_T(""), CB_enum_FieldData_CString);
         CDataMid::InsertRowData(DBStyleColor_cThird_Name,     row_data, FORMAT_STRING,_T(""), CB_enum_FieldData_CString);
         CDataMid::InsertRowData(DBStyleColor_cFourth_Name,    row_data, FORMAT_STRING,_T(""), CB_enum_FieldData_CString);
         CDataMid::InsertRowData(DBStyleColor_cFifth_Name,     row_data, FORMAT_STRING,_T(""), CB_enum_FieldData_CString);
         CDataMid::InsertRowData(DBStyleColor_cSixth_Name,     row_data, FORMAT_STRING,_T(""), CB_enum_FieldData_CString);
         all_data.insert(make_pair(0, row_data));
      }
      else if (all_data.size() == nSZNum )   //没有重量信息
      {
         CString strValue = _T("");
         MAP_GridCtrl_RowData row_data; 
         CDataMid::InsertRowData(DBStyleColor_RowName, row_data, FORMAT_STRING, _T("重量"), CB_enum_FieldData_CString);
         CDataMid::InsertRowData(DBStyleColor_cMainClr,   row_data, FORMAT_STRING, strValue, CB_enum_FieldData_CString);
         CDataMid::InsertRowData(DBStyleColor_ColorName,   row_data, FORMAT_STRING, strValue, CB_enum_FieldData_CString);
         CDataMid::InsertRowData(DBColor_key_Ingredient,   row_data, FORMAT_STRING, strValue, CB_enum_FieldData_CString);
         CDataMid::InsertRowData(DBStyleColor_cFirst,    row_data, FORMAT_STRING, strValue, CB_enum_FieldData_CString);
         CDataMid::InsertRowData(DBStyleColor_cSecond,    row_data, FORMAT_STRING,strValue, CB_enum_FieldData_CString);
         CDataMid::InsertRowData(DBStyleColor_cThird,     row_data, FORMAT_STRING,strValue, CB_enum_FieldData_CString);
         CDataMid::InsertRowData(DBStyleColor_cFourth,    row_data, FORMAT_STRING,strValue, CB_enum_FieldData_CString);
         CDataMid::InsertRowData(DBStyleColor_cFifth,     row_data, FORMAT_STRING,strValue, CB_enum_FieldData_CString);
         CDataMid::InsertRowData(DBStyleColor_cSixth,     row_data, FORMAT_STRING,strValue, CB_enum_FieldData_CString);
          CDataMid::InsertRowData(DBColor_key_ThickNess,   row_data, FORMAT_STRING, strValue, CB_enum_FieldData_CString);
          CDataMid::InsertRowData(DBStyleColor_cFirst_Name,    row_data, FORMAT_STRING, _T(""), CB_enum_FieldData_CString);
          CDataMid::InsertRowData(DBStyleColor_cSecond_Name,    row_data, FORMAT_STRING,_T(""), CB_enum_FieldData_CString);
          CDataMid::InsertRowData(DBStyleColor_cThird_Name,     row_data, FORMAT_STRING,_T(""), CB_enum_FieldData_CString);
          CDataMid::InsertRowData(DBStyleColor_cFourth_Name,    row_data, FORMAT_STRING,_T(""), CB_enum_FieldData_CString);
          CDataMid::InsertRowData(DBStyleColor_cFifth_Name,     row_data, FORMAT_STRING,_T(""), CB_enum_FieldData_CString);
          CDataMid::InsertRowData(DBStyleColor_cSixth_Name,     row_data, FORMAT_STRING,_T(""), CB_enum_FieldData_CString);
         all_data.insert(make_pair(all_data.size(), row_data));
      }
   }


   if (nSZNum <=0) nSZNum =1;

   //if (nPSNum <=0) nPSNum = 1;
   return TRUE;
}

#endif

CDBStyleColorPercent* CDBStyleColorPercentList::GetItem(int nIndex)
{
   if (nIndex<0||nIndex>=GetCount())
      return NULL;
   return (CDBStyleColorPercent*)GetAt(FindIndex(nIndex));
}

void CDBStyleColorPercentList::AddItem(CDBStyleColorPercent* pItem)
{
   CDBStyleColorPercent*pData=new CDBStyleColorPercent;
   pData->Copy(pItem);
   AddTail(pData);
}

void CDBStyleColorPercentList::DeleteItem(int nIndex)
{
   if (nIndex<0||nIndex>GetCount())
      return;
   CDBStyleColorPercent *pObject=(CDBStyleColorPercent*)GetItem(nIndex);
   delete pObject;
   pObject=NULL;
   RemoveAt(FindIndex(nIndex));
}

BOOL CDBStyleColorPercentList::GetStyleColorPercentData(CADOConn* pADOConn,CString strStyleNo,CDBStyleColorPercentList& oList)
{
   ASSERT(pADOConn != NULL);
   ASSERT(!strStyleNo.IsEmpty());
   oList.Empty();
   CString strSql;
   strSql.Format(_T("select * from StyleColorPercent where cStyleNo = '%s';"),strStyleNo);
   pADOConn->GetRecordSet(strSql);
   while(!pADOConn->adoEOF())
   {
      CDBStyleColorPercent oData;
      oData.GetAllDBInfo(pADOConn);
      oList.AddItem(&oData);
      pADOConn->MoveNext();
   }
   return TRUE;
}

BOOL CDBStyleColorPercentList::DelStyleColorPercentData(CADOConn* pADOConn,CString strStyleNo)
{
   ASSERT(pADOConn != NULL);
   ASSERT(!strStyleNo.IsEmpty());
   CString strSql;
   strSql.Format(_T("delete  from StyleColorPercent where cStyleNo = '%s';"),strStyleNo);
   return pADOConn->ExecuteSQL(strSql);
}

BOOL CDBStyleColorPercentList::InsertStyleColorPercentData(CADOConn* pADOConn,CDBStyleColorPercentList& oList)
{
   ASSERT(pADOConn != NULL);
   pADOConn->BeginTrans();
   for (int k=0;k<oList.GetCount();++k)
   {
      auto pData = oList.GetItem(k);
      if (pData != NULL)
      {
         BOOL bRet = pData->InsetAllDBInfo(pADOConn);
         if (bRet == FALSE)
         {
            pADOConn->RollbackTrans();
            return FALSE;
         }
      }
   }
   pADOConn->CommitTrans();
   return TRUE;
}

