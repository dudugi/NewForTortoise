#include "StdAfx.h"
#include "DBStandardSize.h"
#include "DBKeyDef.h"
#include "ADOConn/DBImage.h"
#include <afx.h>

/////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CDBStandardSize, CDataMid, 1)
std::shared_ptr<CDBStandardSize> CDBStandardSize::sm_inst;
CDBStandardSize::CDBStandardSize()
{
   ResetData();
}


CDBStandardSize::~CDBStandardSize()
{
   if (m_pModifyList)
   {
      delete m_pModifyList;
      m_pModifyList = NULL;
   }
}

void CDBStandardSize::ResetData()
{
   m_nID = -1;
   m_strName = _T("");
   m_strRemark = _T("");
   m_vecSize.swap(vector<CString>());
   m_mapPosition.swap(map<CString,CString>());
   m_vecPinMing.swap(vector<CString>());
   m_pModifyList = NULL;
}

BOOL CDBStandardSize::UpdateDBInfo(CADOConn *pADOConn)
{
   return TRUE;
}

BOOL CDBStandardSize::GetAllDBInfo(CADOConn *pADOConn)
{
   ASSERT(pADOConn != NULL);

   BOOL bRet = TRUE;
   if (NULL == pADOConn)
   {
      bRet = FALSE;
   }
   else
   {
      m_nID = pADOConn->GetValueInt(DBStandardSize_key_ID);
      m_strName = pADOConn->GetValueString(DBStandardSize_key_cName);
      m_strRemark = pADOConn->GetValueString(DBStandardSize_key_cMark);
   }
   return bRet;
}

void CDBStandardSize::Copy(CDBStandardSize *pData)
{
   m_nID = pData->m_nID;
   m_strName = pData->m_strName;
   m_strRemark = pData->m_strRemark;
   m_vecSize = pData->m_vecSize;
   m_mapPosition = pData->m_mapPosition;
   m_vecPinMing = pData->m_vecPinMing;
   m_pModifyList = pData->m_pModifyList;
}

CString CDBStandardSize::GetInsertSQL()
{
   CString strRet = _T(""), strFormat = _T(""), strValue = _T("");
   strFormat.Format(_T("%s,%s"),
      DBStandardSize_key_cName
      DBStandardSize_key_cMark
   );
   strValue.Format(_T("'%s','%s'"),
      m_strName,
      m_strRemark);
   strRet.Format(_T("insert into %s(%s) values(%s)"), DB_TABLE_STANDARDSIZE, strFormat, strValue);

   return strRet;
};

CDBStandardSize * CDBStandardSize::Instance()
{
   if (sm_inst.get() == 0)
      sm_inst = shared_ptr<CDBStandardSize>(new CDBStandardSize);

   return sm_inst.get();
}

BOOL CDBStandardSize::UpdateAllDBInfoByID(CADOConn *pADOConn)
{
   ASSERT(pADOConn != NULL);
   BOOL bRet = TRUE;
   CString strSQL = _T("");
   pADOConn->BeginTrans();
   strSQL.Format(_T("update %s set \
      %s='%s',%s='%s'\
      where %s='%lld'"), DB_TABLE_STANDARDSIZE,
      DBStandardSize_key_cName, m_strName,
      DBStandardSize_key_cMark, m_strRemark,
      DBStandardSize_key_ID, m_nID);

   if (!pADOConn->ExecuteSQL(strSQL))
   {
      pADOConn->RollbackTrans();
      return FALSE;
   }

   if (pADOConn->CommitTrans())
   {
      bRet = TRUE;
   }
   else
   {
      bRet = FALSE;
   }

   return bRet;
}

BOOL CDBStandardSize::InsertAllDBInfoByID(CADOConn *pADOConn)
{
   ASSERT(pADOConn != NULL);

   BOOL bRet = TRUE;

   CString strSQL = _T("");
   CString strLabel = _T("");
   strSQL.Format(_T("insert into %s (%s,%s)\
      values('%s','%s')"), DB_TABLE_STANDARDSIZE, \
      DBStandardSize_key_cName,
      DBStandardSize_key_cMark,
      m_strName,
      m_strRemark
   );

   if (!pADOConn->ExecuteSQL(strSQL))
   {
      return FALSE;
   }
   return TRUE;
}

void CDBStandardSize::UpdateDataValue()
{
   for (int nIndex = 0;nIndex< m_pModifyList->GetSize();nIndex++)
   {
      CDBStandardSizeModify* pModify = m_pModifyList->GetItem(nIndex);
      pModify->m_strName = m_strName;
      pModify->m_nID = m_nID;
   }
}

BOOL CDBStandardSize::GetDataByGrid(CADOConn *pADOConn, const MAP_GridCtrl_AllData& data)
{
   m_vecSize.swap(vector<CString>());
   m_mapPosition.swap(map<CString,CString>());
   m_pModifyList->RemoveAll();

   vector<CString> vec_Size, vec_Position, vec_Num;
   //行遍历
   for (auto itr_ = data.begin(); itr_ != data.end(); ++itr_)
   {
      //rowdata key为列名称，"部位/尺码"对应值为部位，其他对应为尺码
      MAP_GridCtrl_RowData rowdata = itr_->second;
      if (0 >= rowdata.count(STANDARD_SIZEMODIFY_ROWNAME))
      {
         return FALSE;
      }
      m_mapPosition.insert(make_pair(rowdata[STANDARD_SIZEMODIFY_ROWNAME].strValue,rowdata[DBStandardSizeModify_key_cMemo].strValue));
      vec_Position.push_back(rowdata[STANDARD_SIZEMODIFY_ROWNAME].strValue);
      CString strCurPostion = rowdata[STANDARD_SIZEMODIFY_ROWNAME].strValue;
      CString strCurMemo = rowdata[DBStandardSizeModify_key_cMemo].strValue;
      //列遍历
      for (auto itr_2 = rowdata.begin(); itr_2 != rowdata.end(); ++itr_2)
      {
         if (STANDARD_SIZEMODIFY_ROWNAME != itr_2->first && DBStandardSizeModify_key_cMemo != itr_2->first)
         {
            //尺码集合
            vec_Size.push_back(itr_2->first);
            m_vecSize.push_back(itr_2->first);
            //尺码值集合
            vec_Num.push_back(itr_2->second.strValue);
            CDBStandardSizeModify* pModify = new  CDBStandardSizeModify;
            pModify->m_strSize = itr_2->first;
            pModify->m_strPosition = strCurPostion;
            pModify->m_nNumber = _ttof(itr_2->second.strValue);
            pModify->m_cMemo = strCurMemo;
            m_pModifyList->AddItem(pModify);
         }
      }
   }
   return TRUE;
}
BOOL CDBStandardSize::GetStyleNoByFangAn(CADOConn *pADOConn,CString strStyleNo)
{
   ASSERT(pADOConn != NULL);
   CString strSql = _T(""),strFangAn = _T("");
   strSql.Format(_T(" select top 1 %s from\
                    %s where cPinMing = (select %s from %s where %s = '%s')"),
                    DBStandardSizePinming_key_cStandardSize,DB_TABLE_STANDARDSIZE_PINMING,DBStandardSizePinming_key_cPinMing,
                    DB_TABLE_STYLE,DBKuanShi_key_StyleNo,strStyleNo);
   BOOL bRet = pADOConn->GetRecordSet(strSql);
   if (!pADOConn->adoEOF())
   {
      m_strName = pADOConn->GetValueString(DBStandardSizePinming_key_cStandardSize);
   }
   return bRet;
}
BOOL CDBStandardSize::GetStyleNoByPingMing(CADOConn *pADOConn,CString strPM)
{
   ASSERT(pADOConn != NULL);
   CString strSql = _T(""),strFangAn = _T("");
   strSql.Format(_T(" select top 1 %s from\
                    %s where %s = '%s'"),
                    DBStandardSizePinming_key_cStandardSize,
                    DB_TABLE_STANDARDSIZE_PINMING,
                    DBStandardSizePinming_key_cPinMing,
                    strPM);
   BOOL bRet = pADOConn->GetRecordSet(strSql);
   if (!pADOConn->adoEOF())
   {
      m_strName = pADOConn->GetValueString(DBStandardSizePinming_key_cStandardSize);
   }
   return bRet;
}

IMPLEMENT_SERIAL(CDBStandardSizeList, CDataListMid, 1)
std::shared_ptr<CDBStandardSizeList> CDBStandardSizeList::sm_inst;

CDBStandardSizeList::CDBStandardSizeList()
{

}

CDBStandardSizeList::~CDBStandardSizeList()
{

}
void CDBStandardSizeList::Copy( CDBStandardSizeList *pList )
{

   this->Empty();
   if (pList != NULL)
   {
      for (int nIndex = 0;nIndex < pList->GetCount();nIndex++)
      {
         CDBStandardSize *pPlanning = pList->GetItem(nIndex);
         if (pPlanning != NULL)
         {
            AddItem(pPlanning);
         }
      }
   }
}
CDBStandardSize*  CDBStandardSizeList::GetItem(int nIndex)
{
   if (nIndex < 0 || nIndex >= GetCount())
      return NULL;

   return (CDBStandardSize*)GetAt(FindIndex(nIndex));
}

void CDBStandardSizeList::AddItem(CDBStandardSize* pItem)
{
   CDBStandardSize*pData = new CDBStandardSize;
   pData->Copy(pItem);
   AddTail(pData);
}

void CDBStandardSizeList::DeleteItem(int nIndex)
{
   if (nIndex<0 || nIndex>GetCount())
      return;

   CDBStandardSize *pObject = (CDBStandardSize*)GetItem(nIndex);
   delete pObject;
   pObject = NULL;

   RemoveAt(FindIndex(nIndex));
}

BOOL CDBStandardSizeList::DeleteUserByUserID(CADOConn* pADOConn, vector<CString>vecUserID)
{
   ASSERT(pADOConn != NULL);
   if (vecUserID.size() <= 0)
      return FALSE;

   CString strUserID;
   for (int i = 0; i < (int)vecUserID.size(); ++i)
   {
      strUserID += _T("'") + vecUserID[i] + _T("',");
   }
   strUserID.TrimRight(_T(","));
   CString strSql;
   strSql.Format(_T("delete from %s where %s in (%s)"), DB_TABLE_STANDARDSIZE, DBStandardSize_key_ID, strUserID);
   return pADOConn->ExecuteSQL(strSql);
}
BOOL CDBStandardSizeList::GetAllDBInfo(CADOConn *pADOConn)
{
   ASSERT(pADOConn != NULL);
   Empty();
   CString strSql = _T("");
   strSql.Format(_T("select * from %s "),DB_TABLE_STANDARDSIZE);
   BOOL bRet = pADOConn->GetRecordSet(strSql);
   while(!pADOConn->adoEOF())
   {
      CDBStandardSize oData;
      oData.m_nID = pADOConn->GetValueInt(DBStandardSize_key_ID);
      oData.m_strName = pADOConn->GetValueString(DBStandardSize_key_cName);
      AddItem(&oData);
      pADOConn->MoveNext();
   }
   return bRet;
}


CDBStandardSizeList* CDBStandardSizeList::Instance()		//获取（指针）实例
{
   if (sm_inst.get() == 0)
      sm_inst = shared_ptr<CDBStandardSizeList>(new CDBStandardSizeList);

   return sm_inst.get();
}

#ifdef USING_GRIDCTRL_MARK
MAP_GridCtrl_AllData CDBStandardSizeList::CreateGridData(const CString & strUserDuty/*=_T("")*/)
{
   MAP_GridCtrl_AllData map_all_data;

   int nIndex = 0, nCount = GetCount();
   int nValidCount = 1;
   for (nIndex = 0; nIndex < nCount; nIndex++)
   {
      CDBStandardSize * pData = GetItem(nIndex);
      if (NULL != pData)
      {
         MAP_GridCtrl_RowData                               map_row_data;
         pData->InsertRowData(DBStandardSize_key_ID, map_row_data, _T("%lld"), pData->m_nID);       //ID
         pData->InsertRowData(DBStandardSize_key_cName, map_row_data, FORMAT_STRING, pData->m_strName);     //名称
         pData->InsertRowData(DBStandardSize_key_cMark, map_row_data, FORMAT_STRING, pData->m_strRemark);   //说明
         map_all_data.insert(make_pair(nValidCount, map_row_data));
         //行数据插入所有数据中

         nValidCount++;
      }
   }

   return map_all_data;
}
#endif


/////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CDBStandardSizeModify, CDataMid, 1)
std::shared_ptr<CDBStandardSizeModify> CDBStandardSizeModify::sm_inst;
CDBStandardSizeModify::CDBStandardSizeModify()
{
   ResetData();
}


CDBStandardSizeModify::~CDBStandardSizeModify()
{
}

void CDBStandardSizeModify::ResetData()
{
   m_nID = -1;
   m_strName = _T("");
   m_nSizeID = -1;
   m_strSize = _T("");
   m_strPosition = _T("");
   m_nNumber = 0;
   m_cMemo = _T("");
}

BOOL CDBStandardSizeModify::UpdateDBInfo(CADOConn *pADOConn)
{
   return TRUE;
}

BOOL CDBStandardSizeModify::GetAllDBInfo(CADOConn *pADOConn)
{
   ASSERT(pADOConn != NULL);

   BOOL bRet = TRUE;
   if (NULL == pADOConn)
   {
      bRet = FALSE;
   }
   else
   {
      m_nID         = pADOConn->GetValueInt(DBStandardSize_key_ID);
      m_nSizeID     = pADOConn->GetValueInt(DBStandardSizeModify_key_nSizeID);
      m_nNumber     = pADOConn->GetValueDouble(DBStandardSizeModify_key_nNumber);
      m_strSize     = pADOConn->GetValueString(DBStandardSizeModify_key_cSize);
      m_strPosition = pADOConn->GetValueString(DBStandardSizeModify_key_cPosition);
      m_cMemo       = pADOConn->GetValueString(DBStandardSizeModify_key_cMemo);  
   }
   return bRet;
}

void CDBStandardSizeModify::Copy(CDBStandardSizeModify *pData)
{
   m_nID         = pData->m_nID;
   m_nSizeID     = pData->m_nSizeID;
   m_nNumber     = pData->m_nNumber;
   m_strSize     = pData->m_strSize;
   m_strPosition = pData->m_strPosition;
   m_cMemo = pData->m_cMemo;
}

CString CDBStandardSizeModify::GetInsertSQL()
{
   CString strRet = _T(""), strFormat = _T(""), strValue = _T("");
   strFormat.Format(_T("%s,%s,%s,%s,%s"),
      DBStandardSizeModify_key_nSizeID,
      DBStandardSizeModify_key_nNumber,
      DBStandardSizeModify_key_cSize,
      DBStandardSizeModify_key_cPosition,
      DBStandardSizeModify_key_cMemo
   );
   strValue.Format(_T("'%d','%.2lf','%s','%s','%s'"),
      m_nSizeID,
      m_nNumber,
      m_strSize,
      m_strPosition,
      m_cMemo);
   strRet.Format(_T("insert into %s(%s) values(%s)"), DB_TABLE_STANDARDSIZE, strFormat, strValue);

   return strRet;
};

CDBStandardSizeModify * CDBStandardSizeModify::Instance()
{
   if (sm_inst.get() == 0)
      sm_inst = shared_ptr<CDBStandardSizeModify>(new CDBStandardSizeModify);

   return sm_inst.get();
}

BOOL CDBStandardSizeModify::UpdateAllDBInfoByID(CADOConn *pADOConn)
{
   ASSERT(pADOConn != NULL);
   BOOL bRet = TRUE;
   CString strSQL = _T("");
   pADOConn->BeginTrans();
   strSQL.Format(_T("update %s set \
      %s='%lld',%s='%s',%s='%s',%s='%.2lf',%s='%s'\
      where %s='%lld'"), DB_TABLE_STANDARDSIZEMODIFY,
      DBStandardSizeModify_key_nSizeID, m_nSizeID,
      DBStandardSizeModify_key_cSize, m_strSize,
      DBStandardSizeModify_key_cPosition, m_strPosition,
      DBStandardSizeModify_key_nNumber, m_nNumber,
      DBStandardSizeModify_key_cMemo, m_cMemo,
      DBStandardSizeModify_key_ID, m_nID);

   if (!pADOConn->ExecuteSQL(strSQL))
   {
      pADOConn->RollbackTrans();
      return FALSE;
   }

   if (pADOConn->CommitTrans())
   {
      bRet = TRUE;
   }
   else
   {
      bRet = FALSE;
   }

   return bRet;
}

BOOL CDBStandardSizeModify::InsertAllDBInfoByID(CADOConn *pADOConn)
{
   ASSERT(pADOConn != NULL);

   BOOL bRet = TRUE;

   CString strSQL = _T("");
   CString strLabel = _T("");
   strSQL.Format(_T("insert into %s (%s,%s,%s,%s,%s)\
					 values('%lld','%s','%s','%.2lf','%s')"),\
      DB_TABLE_STANDARDSIZEMODIFY, \
      DBStandardSizeModify_key_nSizeID,
      DBStandardSizeModify_key_cSize,
      DBStandardSizeModify_key_cPosition,
      DBStandardSizeModify_key_nNumber,
       DBStandardSizeModify_key_cMemo,
      m_nSizeID,
      m_strSize,
      m_strPosition,
      m_nNumber,
      m_cMemo
   );

   if (!pADOConn->ExecuteSQL(strSQL))
   {
      return FALSE;
   }
   return TRUE;
}

IMPLEMENT_SERIAL(CDBStandardSizeModifyList, CDataListMid, 1)
std::shared_ptr<CDBStandardSizeModifyList> CDBStandardSizeModifyList::sm_inst;

CDBStandardSizeModifyList::CDBStandardSizeModifyList()
{

}

CDBStandardSizeModifyList::~CDBStandardSizeModifyList()
{

}

CDBStandardSizeModify*  CDBStandardSizeModifyList::GetItem(int nIndex)
{
   if (nIndex < 0 || nIndex >= GetCount())
      return NULL;

   return (CDBStandardSizeModify*)GetAt(FindIndex(nIndex));
}
void CDBStandardSizeModifyList::Copy( CDBStandardSizeModifyList *pList )
{

   this->Empty();

   if (pList != NULL)
   {
      for (int nIndex = 0;nIndex < pList->GetCount();nIndex++)
      {
         CDBStandardSizeModify *pPlanning = pList->GetItem(nIndex);
         if (pPlanning != NULL)
         {
            AddItem(pPlanning);
         }
      }
   }
}
BOOL  CDBStandardSizeModifyList::GetItemBySize(CString strName)
{
   for (int nIndex = 0; nIndex < GetSize(); nIndex++)
   {
      if (strName == GetItem(nIndex)->m_strSize)
         return TRUE;
   }
   return FALSE;
}

BOOL  CDBStandardSizeModifyList::GetItemByPos(CString strName)
{
   for (int nIndex = 0; nIndex < GetSize(); nIndex++)
   {
      if (strName == GetItem(nIndex)->m_strPosition)
         return TRUE;
   }
   return FALSE;
}

void CDBStandardSizeModifyList::AddItem(CDBStandardSizeModify* pItem)
{
   CDBStandardSizeModify*pData = new CDBStandardSizeModify;
   pData->Copy(pItem);
   AddTail(pData);
}

void CDBStandardSizeModifyList::DeleteItem(int nIndex)
{
   if (nIndex<0 || nIndex>GetCount())
      return;

   CDBStandardSizeModify *pObject = (CDBStandardSizeModify*)GetItem(nIndex);
   delete pObject;
   pObject = NULL;

   RemoveAt(FindIndex(nIndex));
}

BOOL CDBStandardSizeModifyList::DeleteUserByUserID(CADOConn* pADOConn, vector<CString>vecUserID)
{
   ASSERT(pADOConn != NULL);
   if (vecUserID.size() <= 0)
      return FALSE;

   CString strUserID;
   for (int i = 0; i < (int)vecUserID.size(); ++i)
   {
      strUserID += _T("'") + vecUserID[i] + _T("',");
   }
   strUserID.TrimRight(_T(","));
   CString strSql;
   strSql.Format(_T("delete from %s where %s in (%s)"), DB_TABLE_STANDARDSIZE, DBStandardSize_key_ID, strUserID);
   return pADOConn->ExecuteSQL(strSql);
}
BOOL CDBStandardSizeModifyList::GetAllDBInfoByFangAnName(CADOConn *pADOConn,CString strFangAnNmae)// 根据方案名获取所有尺寸数据 liuhw 2019/05/16
{
   ASSERT(pADOConn != NULL);
   Empty();
   CString strSql = _T("");
   strSql.Format(_T("select * from %s where %s = (select %s as nID from %s where %s = '%s')"),
      DB_TABLE_STANDARDSIZEMODIFY,DBStandardSizeModify_key_nSizeID,
      DBStandardSize_key_ID,DB_TABLE_STANDARDSIZE,DBStandardSize_key_cName,strFangAnNmae);
   pADOConn->GetRecordSet(strSql);
   while(!pADOConn->adoEOF())
   {
      CDBStandardSizeModify oData;
      if(oData.GetAllDBInfo(pADOConn))
      {
         AddItem(&oData);
      }      
      pADOConn->MoveNext();
   }
   return FALSE;
}

BOOL CDBStandardSizeModifyList::GetAllDBInfoByPM(CADOConn *pADOConn,CString strPinMing)// 根据品名获取所有尺寸方案数据 liuhw 2019/05/16
{
   ASSERT(pADOConn != NULL);
   Empty();
   CString strSql = _T("");
   strSql.Format(_T("select * from %s where %s = \
                    (select %s as nID from %s where %s = (select top 1 %s as cName from %s where %s = '%s'))"),
                    DB_TABLE_STANDARDSIZEMODIFY,DBStandardSizeModify_key_nSizeID,
                    DBStandardSize_key_ID,DB_TABLE_STANDARDSIZE,DBStandardSize_key_cName,
                    DBStandardSizePinming_key_cStandardSize,DB_TABLE_STANDARDSIZE_PINMING,
                    DBStandardSizePinming_key_cPinMing,strPinMing);
   BOOL bRet = pADOConn->GetRecordSet(strSql);
   while(!pADOConn->adoEOF())
   {
      CDBStandardSizeModify oData;
      if(oData.GetAllDBInfo(pADOConn))
      {
         AddItem(&oData);
      }  
      pADOConn->MoveNext();
   }
   return bRet;
}

void CDBStandardSizeModifyList::SortList(CDBSizePartInfoList * pSizePartList)
{
   int nCount = GetCount();
   for (int i = 0; i < nCount - 1;++i)
   {
      for (int j = i;j < nCount ;j++)
      {
         auto pElementI = GetItem(i);
         auto pElementJ = GetItem(j);
         ASSERT(pElementI && pElementJ);
         auto pPartI = pSizePartList->GetItemByName(pElementI->m_strPosition);
         auto pPartJ = pSizePartList->GetItemByName(pElementJ->m_strPosition);
         auto swapElement = [](CDBStandardSizeModify * pDataI,CDBStandardSizeModify * pDataJ){
            CDBStandardSizeModify oTmpData;
            oTmpData.Copy(pDataI);
            pDataI->Copy(pDataJ);
            pDataJ->Copy(&oTmpData);
         };
         if (pPartI && pPartJ)
         {
            if (pPartI->m_nUserSort > pPartJ->m_nUserSort)
            {
               swapElement(pElementI,pElementJ);
            }
         }
         else
         {
            if (pPartJ)
            {
               swapElement(pElementI,pElementJ);
            }
         }
      }
   }
}

CDBStandardSizeModifyList* CDBStandardSizeModifyList::Instance()		//获取（指针）实例
{
   if (sm_inst.get() == 0)
      sm_inst = shared_ptr<CDBStandardSizeModifyList>(new CDBStandardSizeModifyList);

   return sm_inst.get();
}

#ifdef USING_GRIDCTRL_MARK
MAP_GridCtrl_AllData CDBStandardSizeModifyList::CreateGridData(map<CString,CString> & map_Position)
{
   MAP_GridCtrl_AllData map_all_data;

   //行数为部位数
   int nIndex = 0, nCount = map_Position.size();
   int nValidCount = 1;
   for (auto iter = map_Position.begin(); iter != map_Position.end(); ++iter)
   {
      MAP_GridCtrl_RowData                               map_row_data;
      map<CString, double> map_size_num;
      //收集数据中有此部位的数据，记录在vector中
      for (int n = 0; n < GetCount(); n++)
      {
         CDBStandardSizeModify * pData = GetItem(n);
         //当前数据部位名与当前行数部位名一样
         if (NULL != pData && pData->m_strPosition == iter->first)
         {
            map_size_num[pData->m_strSize] = pData->m_nNumber;
         }
      }

      //插入此行数据
      for (auto iter_find = map_size_num.begin(); iter_find != map_size_num.end(); iter_find++)
      {
         S_GridCtrl_FieldData s_data;	
         s_data.strValue.Format(_T("%.2lf") , iter_find->second);
         map_row_data.insert(make_pair(iter_find->first, s_data));
      }
      S_GridCtrl_FieldData s_dataColTitle;		
      s_dataColTitle.strValue = iter->first;

      //第一列背景色设为灰黑色
      vector<int> cellBackgroundClrVec;
      cellBackgroundClrVec.push_back(RGB(230,230,230));
      shared_ptr<vector<int>> sptr_bgd(new vector<int>);
      *sptr_bgd = cellBackgroundClrVec;
      s_dataColTitle.sptr_cellBackgroundClrVec = sptr_bgd;
      map_row_data.insert(make_pair(STANDARD_SIZEMODIFY_ROWNAME, s_dataColTitle));
      
      //说明
      S_GridCtrl_FieldData s_dataMemo;		
      s_dataMemo.strValue = iter->second;
      map_row_data.insert(make_pair(DBStandardSizeModify_key_cMemo, s_dataMemo));

      map_all_data.insert(make_pair(nValidCount, map_row_data));
      nValidCount++;
   }

   return map_all_data;
}
#endif
