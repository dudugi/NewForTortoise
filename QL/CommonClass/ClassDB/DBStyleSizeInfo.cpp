#include "StdAfx.h"
#include "DBStyleSizeInfo.h"
#include "DBKeyDef.h"

//部位表

IMPLEMENT_SERIAL(CDBStyleChiMaInfoData,  CDataMid, 1)
   IMPLEMENT_SERIAL(CDBStyleChiMaInfoList,  CDataListMid, 1)

   std::shared_ptr<CDBStyleChiMaInfoData> CDBStyleChiMaInfoData::sm_inst;
std::shared_ptr<CDBStyleChiMaInfoList> CDBStyleChiMaInfoList::sm_inst;

CDBStyleChiMaInfoData::CDBStyleChiMaInfoData()
{
   ResetData();
}

CDBStyleChiMaInfoData::~CDBStyleChiMaInfoData()
{

}

void CDBStyleChiMaInfoData::ResetData()
{
   m_nID = 0;//ID
   m_cKuanhao = _T("");//款号
   m_cChima = _T("");//尺码
   m_iBase = 0;//是否为基码

   SetDataType(DAT_STYLE_CHIMA);
}

void CDBStyleChiMaInfoData::Copy(CDBStyleChiMaInfoData *pData)
{
   ASSERT(pData != NULL);
   CDataMid::Copy(pData);

   m_nID       =  pData->m_nID ;
   m_cKuanhao  =  pData->m_cKuanhao;
   m_cChima    =  pData->m_cChima;
   m_iBase     = pData->m_iBase;
}

void CDBStyleChiMaInfoData::Serialize(CArchive& ar)
{

   CDataMid::Serialize(ar);//父类函数

   int nTagSize = 0;
   CString strName;
   int nNameSize;

   ar.Flush();
   if (ar.IsStoring())
   {
      MySerial.SaveDataInt64(ar,_T("STYLEID"),m_nID);
      MySerial.SaveDataStr(ar,_T("STYLECKUANHAO"),m_cKuanhao);
      MySerial.SaveDataStr(ar,_T("STYLECHIMA"),m_cChima);
      MySerial.SaveDataInt(ar,_T("STYLEBASE"),m_iBase);
      nNameSize = 8;
      strName = _T("DENDDEND");
      ar << nNameSize;
      ar << strName;
   }
   else
   {
      int nNumber = 0;
      ar >> nNameSize;
      ar >> strName;

      if(strName.GetLength()!=nNameSize)
         return;

      while(strName != _T("DENDDEND"))
      {
         if(nNumber > 200)
         {
            return;
         }
         else if (strName == _T("STYLEID"))
         {
            ar >>nTagSize >> m_nID;
         }
         else if (strName == _T("STYLECKUANHAO"))
         {
            ar >>nTagSize >> m_cKuanhao;
         }
         else if (strName == _T("STYLECHIMA"))
         {
            ar >> nTagSize >> m_cChima;
         }
         else if (strName == _T("STYLEBASE"))
         {
            ar >> nTagSize >> m_iBase;
         }
         else
         {
            ar >> nTagSize;
            ar.Flush();
            ar.GetFile()->Seek(nTagSize, CFile::current);
         }
         /////////////////////////////////////////////
         strName = _T("");
         ar >> nNameSize;
         ar >> strName;
         if(strName.GetLength() != nNameSize)
            return;
         nNumber++;
      }
   }
}

CDBStyleChiMaInfoData * CDBStyleChiMaInfoData::Instance()
{
   if(sm_inst.get() == 0)
      sm_inst = shared_ptr<CDBStyleChiMaInfoData>(new CDBStyleChiMaInfoData);

   return sm_inst.get();
}

BOOL CDBStyleChiMaInfoData::GetAllDBInfo(CADOConn *pADOConn)
{
   ASSERT(pADOConn!= NULL);
   BOOL bRet= FALSE;

   if(NULL != pADOConn)
   {
      m_nID = _ttoi64(pADOConn->GetValueString(DBStyleChiMa_Key_ID));
      m_cKuanhao = pADOConn->GetValueString(DBStyleChiMa_Key_cKuanhao);
      m_cChima = pADOConn->GetValueString(DBStyleChiMa_Key_cChima);
      m_iBase =  pADOConn->GetValueInt(DBStyleChiMa_Key_iBase);
      bRet = TRUE;
   }
   return bRet;
}

BOOL CDBStyleChiMaInfoData::InsertAllDBInfo(CADOConn *pADOConn)
{
   ASSERT(pADOConn!= NULL);
   BOOL bRet= FALSE;

   if (pADOConn!=NULL)
   {
      CString strSQL = _T("");
      strSQL.Format(_T("insert into %s(%s,%s,%s)\
                       values('%s','%s','%d')"),
                       DB_TABLE_STYLE_CHIMA,
                       DBStyleChiMa_Key_cKuanhao,DBStyleChiMa_Key_cChima,DBStyleChiMa_Key_iBase,
                       m_cKuanhao,m_cChima,m_iBase);
      bRet = pADOConn->ExecuteSQL(strSQL);		
   }
   return bRet;
}
void CDBStyleChiMaInfoData::GetInsertAllDBSql(CString &strSql)
{
   if(m_cKuanhao.IsEmpty())
   {
      return;
   }
   strSql.Format(_T("insert into %s(%s,%s,%s)\
                    values('%s','%s','%d')"),
                    DB_TABLE_STYLE_CHIMA,
                    DBStyleChiMa_Key_cKuanhao,DBStyleChiMa_Key_cChima,DBStyleChiMa_Key_iBase,
                    m_cKuanhao,m_cChima,m_iBase);
}

BOOL CDBStyleChiMaInfoData::UpdateAllDBInfoByID(CADOConn *pADOConn)
{
   ASSERT(pADOConn!= NULL);
   BOOL bRet= FALSE;

   if (pADOConn!=NULL)
   {
      CString strSQL = _T("");
      strSQL.Format(_T("update %s set %s = '%s',%s = '%s',%s = '%d' where %s = %d"),DB_TABLE_STYLE_CHIMA
         ,DBStyleChiMa_Key_cKuanhao,m_cKuanhao
         ,DBStyleChiMa_Key_cChima,m_cChima
         ,DBStyleChiMa_Key_iBase,m_iBase
         ,DBSizePart_key_ID,m_nID
         );
      bRet = pADOConn->ExecuteSQL(strSQL);		
   }
   return bRet;
}

BOOL CDBStyleChiMaInfoData::DelAllDBInfoByID(CADOConn *pADOConn)
{
   ASSERT(pADOConn!= NULL);
   BOOL bRet= FALSE;

   if (NULL != pADOConn)
   {
      CString strSQL = _T("");
      strSQL.Format(_T("delete from %s where %s = %d"),DB_TABLE_STYLE_CHIMA,DBStyleChiMa_Key_ID,m_nID);
      bRet = pADOConn->ExecuteSQL(strSQL);
   }

   return bRet;
}

BOOL CDBStyleChiMaInfoData::DelAllDBInfoByStyleNo(CADOConn *pADOConn)
{
   ASSERT(pADOConn!= NULL);
   BOOL bRet= FALSE;
   if (NULL != pADOConn)
   {
      CString strSQL = GetDelAllDBInfoByStyleNoSql(m_cKuanhao);
      bRet = pADOConn->ExecuteSQL(strSQL);
   }

   return bRet;
}
CString CDBStyleChiMaInfoData::GetDelAllDBInfoByStyleNoSql(CString strStyleNo)
{
   CString strSQL = _T("");
   strSQL.Format(_T("delete from %s where %s = '%s'"),DB_TABLE_STYLE_CHIMA,DBStyleChiMa_Key_cKuanhao,strStyleNo);
   return strSQL;
}
BOOL CDBStyleChiMaInfoData::IsBasicMa(CADOConn *pADOConn)//判断是否为基码
{
   ASSERT(pADOConn!=NULL);
   CString strSql = _T("");
   strSql.Format(_T("select %s from %s where %s = '%s' and %s = '%s'"),DBStyleChiMa_Key_iBase,DB_TABLE_STYLE_CHIMA
      ,DBStyleChiMa_Key_cKuanhao,m_cKuanhao,DBStyleChiMa_Key_cChima,m_cChima);
   pADOConn->GetRecordSet(strSql);
   if (!pADOConn->adoEOF())
   {
      return TRUE;//yES
   }
   else
   {
      return FALSE;//NO
   }
}


CDBStyleChiMaInfoList::CDBStyleChiMaInfoList()
{

}

CDBStyleChiMaInfoList::~CDBStyleChiMaInfoList()
{
   Empty();
}

CDBStyleChiMaInfoData* CDBStyleChiMaInfoList::GetItem(int nIndex)
{
   if (nIndex<0||nIndex>=GetCount())
      return NULL;
   return (CDBStyleChiMaInfoData*)GetAt(FindIndex(nIndex));
}

void CDBStyleChiMaInfoList::AddItem(CDBStyleChiMaInfoData* pItem)
{
   CDBStyleChiMaInfoData*pData=new CDBStyleChiMaInfoData;
   pData->Copy(pItem);
   AddTail(pData);
}

void CDBStyleChiMaInfoList::DeleteItem(int nIndex)
{
   if (nIndex<0||nIndex>GetCount())
      return;
   CDBStyleChiMaInfoData *pObject=(CDBStyleChiMaInfoData*)GetItem(nIndex);
   delete pObject;
   pObject=NULL;
   RemoveAt(FindIndex(nIndex));
}

CDBStyleChiMaInfoList * CDBStyleChiMaInfoList::Instance()
{
   if(sm_inst.get() == 0)
      sm_inst = shared_ptr<CDBStyleChiMaInfoList>(new CDBStyleChiMaInfoList);

   return sm_inst.get();
}


IMPLEMENT_SERIAL(CDBStyleSizeInfoData,  CDataMid, 1)
   IMPLEMENT_SERIAL(CDBStyleSizeInfoList,  CDataListMid, 1)

   std::shared_ptr<CDBStyleSizeInfoData> CDBStyleSizeInfoData::sm_inst;
std::shared_ptr<CDBStyleSizeInfoList> CDBStyleSizeInfoList::sm_inst;

CDBStyleSizeInfoData::CDBStyleSizeInfoData()
{
   ResetData();
} 

CDBStyleSizeInfoData::~CDBStyleSizeInfoData()
{
}

void CDBStyleSizeInfoData::ResetData()
{
   m_nID = 0;           //ID
   m_cKuanhao = _T(""); //款号
   m_cChima = _T("");   //尺码
   m_iPartID = 0;       //部位ID
   m_fSize = 0;         //尺寸
   m_cFangAn = _T("");  //尺寸方案名
   m_strSize = _T("0");
   SetDataType(DAT_STYLE_SIZE);
}

void CDBStyleSizeInfoData::Copy(CDBStyleSizeInfoData *pData)
{
   ASSERT(pData != NULL);
   CDataMid::Copy(pData);

   m_nID = pData->m_nID;           //ID
   m_cKuanhao = pData->m_cKuanhao; //款号
   m_cChima = pData->m_cChima;   //尺码
   m_iPartID = pData->m_iPartID;       //部位ID
   m_fSize = pData->m_fSize;         //尺寸
   m_cFangAn = pData->m_cFangAn;  //尺寸方案名
   m_strSize = pData->m_strSize;
}

void CDBStyleSizeInfoData::Serialize(CArchive& ar)
{
   CDataMid::Serialize(ar);//父类函数

   int nTagSize = 0;
   CString strName;
   int nNameSize;

   ar.Flush();
   if (ar.IsStoring())
   {
      MySerial.SaveDataInt64(ar,_T("STYLESIZEID"),m_nID);
      MySerial.SaveDataStr(ar,_T("STYLESIZEKUANHAO"),m_cKuanhao);
      MySerial.SaveDataStr(ar,_T("STYLESIZEIDCHIMA"),m_cChima);
      MySerial.SaveDataInt(ar,_T("STYLESIZEIDPARTID"),m_iPartID);
      MySerial.SaveDataDouble(ar,_T("STYLESIZEIDSIZE"),m_fSize);
      MySerial.SaveDataStr(ar,_T("STYLESIZEFANGAN"),m_cFangAn);

      nNameSize = 8;
      strName = _T("DENDDEND");
      ar << nNameSize;
      ar << strName;
   }
   else
   {
      int nNumber = 0;
      ar >> nNameSize;
      ar >> strName;

      if(strName.GetLength()!=nNameSize)
         return;

      while(strName != _T("DENDDEND"))
      {
         if(nNumber > 200)
         {
            return;
         }
         else if (strName == _T("STYLESIZEID"))
         {
            ar >>nTagSize >> m_nID;
         }
         else if (strName == _T("STYLESIZEKUANHAO"))
         {
            ar >>nTagSize >> m_cKuanhao;
         }
         else if (strName == _T("STYLESIZEIDCHIMA"))
         {
            ar >>nTagSize >> m_cChima;
         }
         else if (strName == _T("STYLESIZEIDPARTID"))
         {
            ar >>nTagSize >> m_iPartID;
         }
         else if (strName == _T("STYLESIZEIDSIZE"))
         {
            ar >> nTagSize >> m_fSize;
         }
         else if (strName == _T("STYLESIZEFANGAN"))
         {
            ar >> nTagSize >>m_cFangAn;
         }
         else
         {
            ar >> nTagSize;
            ar.Flush();
            ar.GetFile()->Seek(nTagSize, CFile::current);
         }
         /////////////////////////////////////////////
         strName = _T("");
         ar >> nNameSize;
         ar >> strName;
         if(strName.GetLength() != nNameSize)
            return;
         nNumber++;
      }
   }
}

CDBStyleSizeInfoData * CDBStyleSizeInfoData::Instance()
{
   if(sm_inst.get() == 0)
      sm_inst = shared_ptr<CDBStyleSizeInfoData>(new CDBStyleSizeInfoData);

   return sm_inst.get();
}

BOOL CDBStyleSizeInfoData::InsertAllDBInfo(CADOConn *pADOConn)
{
   ASSERT(pADOConn != NULL);
   BOOL bRet = TRUE;
   if (m_cKuanhao.IsEmpty())
   {
      return FALSE;
   }

   if (NULL != pADOConn)
   {
      CString strSQL = _T("");
      strSQL.Format(_T("insert into %s(%s,%s,%s,%s,%s)\
                       values('%s','%s','%d','%.2f','%s')"),
                       DB_TABLE_STYLE_SIZE,
                       DBStyleSize_Key_cKuanhao,DBStyleSize_Key_cChima,DBStyleSize_Key_iPartID,DBStyleSize_Key_fSize,DBStyelSize_Key_cFangAn,
                       m_cKuanhao,m_cChima,m_iPartID,m_fSize,m_cFangAn);
      bRet = pADOConn->ExecuteSQL(strSQL);		
   }
   return bRet;
}
BOOL CDBStyleSizeInfoData::UpdateAllDBInfoByID(CADOConn *pADOConn)
{
   ASSERT(pADOConn!= NULL);
   BOOL bRet= FALSE;

   if (pADOConn!=NULL)
   {
      CString strSQL = _T("");
      strSQL.Format(_T("update %s set %s = '%s',%s = '%s',%s = '%d',%s = '%.2f',%s = '%s' where %s = %d"),DB_TABLE_STYLE_SIZE
         ,DBStyleSize_Key_cKuanhao,m_cKuanhao
         ,DBStyleSize_Key_cChima,m_cChima
         ,DBStyleSize_Key_iPartID,m_iPartID
         ,DBStyleSize_Key_fSize,m_fSize
         ,DBStyelSize_Key_cFangAn,m_cFangAn
         ,DBStyleSize_Key_ID,m_nID
         );
      bRet = pADOConn->ExecuteSQL(strSQL);		
   }
   return bRet;
}
void CDBStyleSizeInfoData::GetUpdateAllDBInfoByStyleNo(CString &strSql)
{
   if (m_cKuanhao.IsEmpty())
   {
      return;
   }
   strSql.Format(_T("update %s set %s = '%s',%s = '%d',%s = '%.2f',%s = '%s' where %s = '%s'"),DB_TABLE_STYLE_SIZE
      ,DBStyleSize_Key_cChima,m_cChima
      ,DBStyleSize_Key_iPartID,m_iPartID
      ,DBStyleSize_Key_fSize,m_fSize
      ,DBStyelSize_Key_cFangAn,m_cFangAn
      ,DBStyleSize_Key_cKuanhao,m_cKuanhao
      );
}

void CDBStyleSizeInfoData::GetInsertAllDBInfo(CString &strSQL)
{
   if(m_cKuanhao.IsEmpty())
   {
      return;
   }
   strSQL.Format(_T("insert into %s(%s,%s,%s,%s,%s)\
                    values('%s','%s','%d','%.2f','%s')"),
                    DB_TABLE_STYLE_SIZE,
                    DBStyleSize_Key_cKuanhao,DBStyleSize_Key_cChima,DBStyleSize_Key_iPartID,DBStyleSize_Key_fSize,DBStyelSize_Key_cFangAn,
                    m_cKuanhao,m_cChima,m_iPartID,m_fSize,m_cFangAn);
}

BOOL CDBStyleSizeInfoData::DelAllDBInfoByID(CADOConn *pADOConn)
{
   ASSERT(pADOConn!= NULL);
   BOOL bRet= FALSE;

   if (NULL != pADOConn)
   {
      CString strSQL = _T("");
      strSQL.Format(_T("delete from %s where %s = %d"),DB_TABLE_STYLE_SIZE,DBStyleSize_Key_ID,m_nID);
      bRet = pADOConn->ExecuteSQL(strSQL);
   }

   return bRet;
}
BOOL CDBStyleSizeInfoData::DelAllDBInfoByStyleNo(CADOConn *pADOConn)
{
   ASSERT(pADOConn!= NULL);
   BOOL bRet= FALSE;

   if (NULL != pADOConn)
   {
      CString strSQL = GetDelAllDBInfoByStyleNoSql(m_cKuanhao);
      bRet = pADOConn->ExecuteSQL(strSQL);
   }

   return bRet;
}

CString CDBStyleSizeInfoData::GetDelAllDBInfoByStyleNoSql(CString strStyleNo)
{
   CString strSQL = _T("");
   strSQL.Format(_T("delete from %s where %s = '%s'"),DB_TABLE_STYLE_SIZE,DBStyleSize_Key_cKuanhao,strStyleNo);
   return strSQL;
}

void CDBStyleSizeInfoData::GetAllDBInfo(CADOConn *pADOConn)
{
   if (pADOConn == NULL)
   {
      return;
   }
   else
   {
      m_nID = pADOConn->GetValueInt64(DBStyleSize_Key_ID);
      m_cKuanhao = pADOConn->GetValueString(DBStyleSize_Key_cKuanhao);
      m_cChima = pADOConn->GetValueString(DBStyleSize_Key_cChima);
      m_fSize = pADOConn->GetValueDouble(DBStyleSize_Key_fSize);
      m_strSize = pADOConn->GetValueString(DBStyleSize_Key_fSize);
      m_iPartID = pADOConn->GetValueInt(DBStyleSize_Key_iPartID);
      m_cFangAn = pADOConn->GetValueString(DBStyelSize_Key_cFangAn);
   }
}

//CDBSizeInfoList
CDBStyleSizeInfoList::CDBStyleSizeInfoList()
{

}
CDBStyleSizeInfoList::~CDBStyleSizeInfoList()
{
   Empty();
}

CDBStyleSizeInfoData*  CDBStyleSizeInfoList::GetItem(int nIndex)
{
   if (nIndex<0||nIndex>=GetCount())
      return NULL;
   return (CDBStyleSizeInfoData*)GetAt(FindIndex(nIndex));
}
void CDBStyleSizeInfoList::AddItem(CDBStyleSizeInfoData* pItem)
{
   CDBStyleSizeInfoData*pData=new CDBStyleSizeInfoData;
   pData->Copy(pItem);
   AddTail(pData);
}
void CDBStyleSizeInfoList::DeleteItem(int nIndex)
{
   if (nIndex<0||nIndex>GetCount())
      return;
   CDBStyleSizeInfoData *pObject=(CDBStyleSizeInfoData*)GetItem(nIndex);
   delete pObject;
   pObject=NULL;
   RemoveAt(FindIndex(nIndex));
}
CDBStyleSizeInfoList * CDBStyleSizeInfoList::Instance()
{
   if(sm_inst.get() == 0)
      sm_inst = shared_ptr<CDBStyleSizeInfoList>(new CDBStyleSizeInfoList);

   return sm_inst.get();
}
void CDBStyleSizeInfoList::CopyList(CDBStyleSizeInfoList* pList)
{

   this->Empty();
   for (int i=0;i<pList->GetCount();++i)
   {
      auto pItem = pList->GetItem(i);
      if (pItem)
      {
         AddItem(pItem);
      }
   }
}
BOOL  CDBStyleSizeInfoList::InsertAllDBListInfo(CADOConn *pADOConn)
{
   if (pADOConn == NULL)
   {
      return FALSE;
   }
   int nIndex = 0,nCount = GetCount();
   vector<CString> vecStrSQL;
   for(;nIndex < nCount; ++nIndex)
   {
      CDBStyleSizeInfoData *pData = GetItem(nIndex);
      CString strSql = _T("");
      pData->GetInsertAllDBInfo(strSql);
      vecStrSQL.push_back(strSql);
   }
   if (vecStrSQL.size() > 0)
   {
      if (pADOConn->ExecuteSQLByTransaction(vecStrSQL))
      {
         return TRUE;
      }
   }
   return FALSE;
}

BOOL CDBStyleSizeInfoList::GetStyleNoAllDBInfo(CADOConn *pADOConn,CString strStyleNo,CString &strBasicMa)
{
   if(pADOConn == NULL)
   {
      return FALSE;
   }

   if (strStyleNo.IsEmpty())
   {
      return FALSE;
   }
   if (GetCount() > 0)
   {
      Empty();
   }
   CString strSql = _T("");
   strSql.Format(_T("select s.*,c.cChima as BasicChima from %s as s\
                    left join %s as c on s.cKuanhao = c.cKuanhao left join %s as sp on sp.%s = s.%s where s.%s = '%s' order by %s "),
      DB_TABLE_STYLE_SIZE,DB_TABLE_STYLE_CHIMA,
      DB_TABLE_SIZEPART,DBSizePart_key_ID,DBStyleSize_Key_iPartID,
      DBStyleSize_Key_cKuanhao,strStyleNo,DBSizePart_key_UserSort);
   BOOL bRet = pADOConn->GetRecordSet(strSql);
   while(!pADOConn->adoEOF())
   {
      CDBStyleSizeInfoData oData;
      oData.GetAllDBInfo(pADOConn);
      strBasicMa = pADOConn->GetValueString(_T("BasicChima"));
  
      AddItem(&oData);
      pADOConn->MoveNext();
   }
   return bRet;
}

BOOL CDBStyleSizeInfoList::GetStyleNoAllDBInfo(CADOConn *pADOConn,CString strStyleNo,BOOL bDecimalPoint /*= FALSE*/)
{
   if(pADOConn == NULL)
   {
      return FALSE;
   }

   if (strStyleNo.IsEmpty())
   {
      return FALSE;
   }
   if (GetCount() > 0)
   {
      Empty();
   }
   CString strSql = _T("");
   strSql.Format(_T("select s.%s,s.%s,s.%s,s.%s,CONVERT(float,s.%s) as %s,s.%s from %s as s\
                    left join %s as sp on sp.%s = s.%s where s.%s = '%s' order by %s "),
                    DBStyleSize_Key_ID,DBStyleSize_Key_cKuanhao,DBStyleSize_Key_cChima,DBStyleSize_Key_iPartID,DBStyleSize_Key_fSize,DBStyleSize_Key_fSize,DBStyelSize_Key_cFangAn,
                    DB_TABLE_STYLE_SIZE,
                    DB_TABLE_SIZEPART,DBSizePart_key_ID,DBStyleSize_Key_iPartID,
                    DBStyleSize_Key_cKuanhao,strStyleNo,DBSizePart_key_UserSort);
   BOOL bRet = pADOConn->GetRecordSet(strSql);
   while(!pADOConn->adoEOF())
   {
      CDBStyleSizeInfoData oData;
      //oData.GetAllDBInfo(pADOConn);
      oData.m_nID = pADOConn->GetValueInt64(DBStyleSize_Key_ID);
      oData.m_cKuanhao = pADOConn->GetValueString(DBStyleSize_Key_cKuanhao);
      oData.m_cChima = pADOConn->GetValueString(DBStyleSize_Key_cChima);
      oData.m_fSize = pADOConn->GetValueDouble(DBStyleSize_Key_fSize);
      oData.m_strSize = pADOConn->GetValueString(DBStyleSize_Key_fSize);
      oData.m_iPartID = pADOConn->GetValueInt(DBStyleSize_Key_iPartID);
      oData.m_cFangAn = pADOConn->GetValueString(DBStyelSize_Key_cFangAn);

      AddItem(&oData);
      pADOConn->MoveNext();
   }
   return bRet;
}

map<int,map<CString,CString>> CDBStyleSizeInfoList::CreateMapSizeData()
{
   map<int,map<CString,CString>> allSizeData;
   for (int i = 0; i < GetCount(); ++i)
   {
      map<CString,CString> map_size_info;
      CDBStyleSizeInfoData *pData = GetItem(i);
      if(pData != NULL)
      {
         auto itr_all = allSizeData.find(pData->m_iPartID);
         if (itr_all != allSizeData.end())
         {
            CString strValue;
            strValue.Format(FORMAT_FLOAT2DOT,pData->m_fSize);
            itr_all->second.insert(make_pair(pData->m_cChima,strValue));
         }
         else
         {
            map_size_info.clear();
            CString strValue;
            strValue.Format(FORMAT_FLOAT2DOT,pData->m_fSize);
            map_size_info.insert(make_pair(pData->m_cChima,strValue));
            allSizeData.insert(make_pair(pData->m_iPartID,map_size_info));
         }
      }
   }
   return allSizeData;
}
