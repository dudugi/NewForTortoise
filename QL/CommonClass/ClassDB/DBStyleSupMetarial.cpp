#include "StdAfx.h"
#include "DBStyleSupMetarial.h"
#include "DBKeyDef.h"

//***************** CDBStyleSupMetarial *********************//
IMPLEMENT_SERIAL(CDBStyleSupMetarial,  CDataMid, 1)

   CDBStyleSupMetarial::CDBStyleSupMetarial(void)
{
   ResetData();
}

CDBStyleSupMetarial::~CDBStyleSupMetarial(void)
{
}

void CDBStyleSupMetarial::ResetData()
{
   m_id              = 0;
   m_nPrice          = 0;
   m_nSumPrice       = 0;
   m_nNumber         = 0;
   m_strMemo         = _T("");
   m_strStyleNo      = _T("");
   m_strName         = _T("");
}

void CDBStyleSupMetarial::Copy(CDBStyleSupMetarial *pData)
{
   ASSERT(pData      != NULL);
   m_id              = pData->m_id;
   m_nPrice          = pData->m_nPrice;
   m_nSumPrice       = pData->m_nSumPrice;
   m_nNumber         = pData->m_nNumber;
   m_strMemo         = pData->m_strMemo;
   m_strStyleNo      = pData->m_strStyleNo;
   m_strName         = pData->m_strName;
}

void CDBStyleSupMetarial::GetAllDBInfo(CADOConn* pADOConn)
{
   ASSERT(pADOConn  != NULL);
   m_id              = pADOConn->GetValueInt(DBStyleMetarial_ID);
   m_nPrice          = pADOConn->GetValueDouble(DBStyleSupMetarial_nPrice);
   m_nSumPrice       = pADOConn->GetValueDouble(DBStyleSupMetarial_nSumPrice);
   m_nNumber         = pADOConn->GetValueInt(DBStyleSupMetarial_nNumber);
   m_strMemo         = pADOConn->GetValueString(DBStyleSupMetarial_cMemo);
   m_strStyleNo      = pADOConn->GetValueString(DBStyleSupMetarial_cStyleNo);
   m_strName         = pADOConn->GetValueString(DBStyleSupMetarial_cName);
}

BOOL CDBStyleSupMetarial::InsetAllDBInfo(CADOConn* pADOConn)
{
   ASSERT(pADOConn != NULL);
   return pADOConn->ExecuteSQL(GetInsertSql());
}

BOOL CDBStyleSupMetarial::UpdateAllDBInfo(CADOConn* pADOConn)
{
   ASSERT(pADOConn != NULL);                                 
   return pADOConn->ExecuteSQL(GetUpdateSql());              
}                                                            
                                                             
BOOL CDBStyleSupMetarial::DeleteAllDBInfo(CADOConn* pADOConn)
{                                                            
   ASSERT(pADOConn != NULL);
   return pADOConn->ExecuteSQL(GetDeleteSql());
}

CString CDBStyleSupMetarial::GetInsertSql()
{
   CString strSql = _T("");
   strSql.Format(_T("insert into %s (%s,%s,%s,%s,%s,%s) values ('%s',%.2lf,%d,%.2lf,'%s','%s'); "), DB_TABLE_STYLESUPMETARIAL,
      DBStyleSupMetarial_cName,DBStyleSupMetarial_nPrice, DBStyleSupMetarial_nNumber, DBStyleSupMetarial_nSumPrice, DBStyleSupMetarial_cMemo, DBStyleSupMetarial_cStyleNo,
      m_strName, m_nPrice, m_nNumber, m_nSumPrice, m_strMemo, m_strStyleNo);
   return strSql;
}

CString CDBStyleSupMetarial::GetUpdateSql()
{
   CString strSql = _T("");
   //update StyleMetarial set cStyleNo = '18G200',cColorNo = 'color7',iIsPrimary = 1,iSortId = 1 where ID = 7"
   strSql.Format(_T("update %s set %s = 's',%s = %.2lf,%s = %d,%s = %.2lf,%s = '%s',%s = '%s' where %s = %d"), DB_TABLE_STYLESUPMETARIAL,
      DBStyleSupMetarial_cName, m_strName,
      DBStyleSupMetarial_nPrice, m_nPrice,
      DBStyleSupMetarial_nNumber, m_nNumber,
      DBStyleSupMetarial_nSumPrice, m_nSumPrice,
      DBStyleSupMetarial_cMemo, m_strMemo,
      DBStyleSupMetarial_cStyleNo, m_strStyleNo,
      DBStyleSupMetarial_ID, m_id);
   return strSql;
}

CString CDBStyleSupMetarial::GetDeleteSql()
{
   CString strSql = _T("");
   strSql.Format(_T("delete from %s where %s = %d;"), DB_TABLE_STYLESUPMETARIAL, DBStyleMetarial_ID, m_id);
   return strSql;
}

//***************** CDBStyleSupMetarialList *********************//                     

IMPLEMENT_SERIAL(CDBStyleSupMetarialList, CDataMid, 1)

std::shared_ptr<CDBStyleSupMetarialList> CDBStyleSupMetarialList::sm_inst;

CDBStyleSupMetarialList::CDBStyleSupMetarialList(void)
{

}

CDBStyleSupMetarialList::~CDBStyleSupMetarialList(void)
{

}

CDBStyleSupMetarialList * CDBStyleSupMetarialList::Instance()
{
   if(sm_inst.get() == 0)
      sm_inst = shared_ptr<CDBStyleSupMetarialList>(new CDBStyleSupMetarialList);

   return sm_inst.get();
}

#ifdef USING_GRIDCTRL_MARK
BOOL CDBStyleSupMetarialList::GetStyleMetarialInfo(CADOConn* pADOConn,CString strStyleNo,MAP_GridCtrl_AllData& all_data)
{
   ASSERT(pADOConn != NULL);
   ASSERT(!strStyleNo.IsEmpty());
   all_data.clear();

   CString str = _T("");
   vector<CString> vec_Name;
   CString strNameSql = _T("");
   strNameSql.Format(_T("select distinct cName from %s "),DB_TABLE_MATERIEL_INFO);
   pADOConn->GetRecordSet(strNameSql);
   while (!pADOConn->adoEOF())
   {
      CString strName = pADOConn->GetValueString(DBMateriel_Key_cName);
      vec_Name.push_back(strName);
      pADOConn->MoveNext();
   }
   if (!vec_Name.empty())
   {
      str = *vec_Name.begin();
   }

   CString strSql = _T("");
   strSql.Format(_T("select * from %s where cStyleNo = '%s';"), DB_TABLE_STYLESUPMETARIAL,strStyleNo);
   pADOConn->GetRecordSet(strSql);

   MAP_GridCtrl_RowData row_data;
   while (!pADOConn->adoEOF())
   {
      row_data.clear();
      //第一行名称为combobox，读取物料管理数据
      CString strName = pADOConn->GetValueString(DBStyleSupMetarial_cName);
      InsertRowData(DBStyleSupMetarial_cName, strName, row_data, CB_enum_FieldData_CString, CB_enum_FieldCtrl_NormalCombox, vector<int>(), vec_Name);
      InsertRowData(DBStyleSupMetarial_nPrice, row_data, _T("%.2lf"), pADOConn->GetValueDouble(DBStyleSupMetarial_nPrice), CB_enum_FieldData_Double2Point);
      InsertRowData(DBStyleSupMetarial_nSumPrice,row_data, _T("%.2lf"), pADOConn->GetValueDouble(DBStyleSupMetarial_nSumPrice), CB_enum_FieldData_Double2Point);
      InsertRowData(DBStyleSupMetarial_nNumber,  row_data, FORMAT_INT,    pADOConn->GetValueInt(DBStyleSupMetarial_nNumber), CB_enum_FieldData_Int);
      InsertRowData(DBStyleSupMetarial_cMemo,    row_data, FORMAT_STRING,    pADOConn->GetValueString(DBStyleSupMetarial_cMemo), CB_enum_FieldData_CString);
      InsertRowData(DBStyleSupMetarial_cStyleNo, row_data, FORMAT_STRING,    pADOConn->GetValueString(DBStyleSupMetarial_cStyleNo), CB_enum_FieldData_CString);
      all_data.insert(make_pair(all_data.size(), row_data));
      pADOConn->MoveNext();
   }
   return TRUE;
}

BOOL CDBStyleSupMetarialList::SaveStyleMetarialInfo(CADOConn* pADOConn,CString strStyleNo,MAP_GridCtrl_AllData all_data)
{
   ASSERT(pADOConn != NULL);
   CString strSql_Del;
   strSql_Del.Format(_T("delete from %s where %s = '%s';"),DB_TABLE_STYLESUPMETARIAL,DBStyleSupMetarial_cStyleNo,strStyleNo);
   pADOConn->ExecuteSQL(strSql_Del);
   if (all_data.size() > 0)
   {
      CString strSql_Insert = _T("");
      for (auto itr_row = all_data.begin(); itr_row != all_data.end(); ++itr_row)
      {
         CDBStyleSupMetarial obj;
 
         obj.m_strStyleNo = strStyleNo;
         for (auto itr_col = itr_row->second.begin(); itr_col != itr_row->second.end(); ++itr_col)
         {
            if (XMLCFG_MI_KEY_NAME == itr_col->first)
            {
               obj.m_strName = itr_col->second.strValue;
            }
            if (XMLCFG_MI_KEY_NUMBER == itr_col->first)
            {
               obj.m_nNumber = _ttoi(itr_col->second.strValue);
            }
            if (XMLCFG_MI_KEY_PRICE == itr_col->first)
            {
               obj.m_nPrice = _ttof(itr_col->second.strValue);
            }
            if (XMLCFG_MI_KEY_SUMPRICE == itr_col->first)
            {
               obj.m_nSumPrice = _ttof(itr_col->second.strValue);
            }
            if (XMLCFG_MI_KEY_METO == itr_col->first)
            {
               obj.m_strMemo = itr_col->second.strValue;
            }
         }
         if (!obj.m_strName.IsEmpty())   //名称为空，则不插数据
         {
            strSql_Insert += obj.GetInsertSql();
         }
         else
            continue;
      }
      if (!strSql_Insert.IsEmpty())
         pADOConn->ExecuteSQL(strSql_Insert);
   }
   return TRUE;
}
#endif

BOOL CDBStyleSupMetarialList::ClearStyleMetarialInfo(CADOConn* pADOConn,CString strStyleNo)
{
   ASSERT(pADOConn != NULL);
   CString strSql_Del;
   strSql_Del.Format(_T("delete from %s where %s = '%s';"),DB_TABLE_STYLESUPMETARIAL, DBStyleSupMetarial_cStyleNo,strStyleNo);
   return pADOConn->ExecuteSQL(strSql_Del);
}

BOOL CDBStyleSupMetarialList::IsStyleMetarialInfoExist(CADOConn* pADOConn,CString strStyleNo)
{
   ASSERT(pADOConn != NULL);
   CString strSql;
   strSql.Format(_T("select count(*) as num from %s where %s = '%s';"),DB_TABLE_STYLESUPMETARIAL,DBStyleSupMetarial_cStyleNo,strStyleNo);
   pADOConn->GetRecordSet(strSql);
   if (!pADOConn->adoEOF())
   {
      int count = pADOConn->GetValueInt(_T("num"));
      if (count>0)
      {
         return TRUE;
      }
      return FALSE;
   }
   return TRUE;
}

CDBStyleSupMetarial* CDBStyleSupMetarialList::GetItem(int nIndex)
{
   if (nIndex<0||nIndex>=GetCount())
      return NULL;
   return (CDBStyleSupMetarial*)GetAt(FindIndex(nIndex));
}


void CDBStyleSupMetarialList::AddItem(CDBStyleSupMetarial* pItem)
{
   CDBStyleSupMetarial*pData=new CDBStyleSupMetarial;
   pData->Copy(pItem);
   AddTail(pData);
}

void CDBStyleSupMetarialList::DeleteItem(int nIndex)
{
   if (nIndex<0||nIndex>GetCount())
      return;
   CDBStyleSupMetarial *pObject=(CDBStyleSupMetarial*)GetItem(nIndex);
   delete pObject;
   pObject=NULL;
   RemoveAt(FindIndex(nIndex));
}

BOOL CDBStyleSupMetarialList::SaveStyleMetarial(CADOConn* pADOConn,CString strStyleNo)
{
   if (!pADOConn)
   {
      return FALSE;
   }
   int count = GetCount();
   if (count>0)
   {
      pADOConn->BeginTrans();
      BOOL bSuccess = TRUE;
      for (int index=0;index<count;++index)
      {
         CDBStyleSupMetarial *pData = GetItem(index);
         if (pData)
         {
            bSuccess = pData->InsetAllDBInfo(pADOConn);
         }
         if (!bSuccess)
         {
            break;
         }
      }
      if (bSuccess)
      {
         pADOConn->CommitTrans();
         return TRUE;
      }else
      {
         pADOConn->RollbackTrans();
         return FALSE;
      }
   }else
   {
      return FALSE;
   }
   
}

void CDBStyleSupMetarialList::GetDBInfoFromDB( CADOConn *pADOConn )
{
	if (!pADOConn)
	{
		return ;
	}

	CString strSQL = _T("");
	strSQL.Format(_T("select * from %s"),DB_TABLE_STYLESUPMETARIAL);
	pADOConn->GetRecordSet(strSQL);
	while(!pADOConn->adoEOF())
	{
		CDBStyleSupMetarial oDBMetarial;
		oDBMetarial.GetAllDBInfo(pADOConn);
		AddItem(&oDBMetarial);

		pADOConn->MoveNext();
	}
}



