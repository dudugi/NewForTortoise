#include "StdAfx.h"
#include "DBDesignData.h"
#include "DBKeyDef.h"
#include <afx.h>


/////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CDBDesignData, CDataMid, 1)
std::shared_ptr<CDBDesignData> CDBDesignData::sm_inst;
CDBDesignData::CDBDesignData()
{
   ResetData();
}


CDBDesignData::~CDBDesignData()
{
}

void CDBDesignData::ResetData()
{
   m_nID = -1;
   m_strName = _T("");
   m_strSavedUserID = _T("");
   m_strSaveTime = _T("");
   m_strData = _T("");
}

BOOL CDBDesignData::UpdateDBInfo(CADOConn *pADOConn)
{
   pADOConn->GetValueString(DBDesignData_key_Name) = m_strName;			//名称
   return TRUE;
}

BOOL CDBDesignData::GetAllDBInfo(CADOConn *pADOConn)
{
   ASSERT(pADOConn != NULL);

   BOOL bRet = TRUE;
   if (NULL == pADOConn)
   {
      bRet = FALSE;
   }
   else
   {
      m_nID = pADOConn->GetValueInt(DBDesignData_key_ID);
      m_strName = pADOConn->GetValueString(DBDesignData_key_Name);
      m_strSavedUserID = pADOConn->GetValueString(DBDesignData_key_cSavedUserID);
      m_strSaveTime = pADOConn->GetValueString(DBDesignData_key_cSaveTime);
      m_strData = pADOConn->GetValueString(DBDesignData_key_cData);
   }
   return bRet;
}

void CDBDesignData::Copy(CDBDesignData *pData)
{
   m_nID            = pData->m_nID;
   m_strName        = pData->m_strName;
   m_strSavedUserID = pData->m_strSavedUserID;
   m_strSaveTime    = pData->m_strSaveTime;
   m_strData          = pData->m_strData;
}

CString CDBDesignData::GetInsertSQL()
{
   CString strRet = _T(""), strFormat = _T(""), strValue = _T("");
   strFormat.Format(_T("%s,%s,%s,%s"),
      DBDesignData_key_Name,
      DBDesignData_key_cSavedUserID,
      DBDesignData_key_cSaveTime,
      DBDesignData_key_cData
   );
   CString strSaveTime = _T("");
   if (m_strSaveTime.IsEmpty())
   {
      strSaveTime = DBS_GETDATESTR;
   }
   else
   {
      strSaveTime.Format(_T("'%s'"), m_strSaveTime);
   }
   strValue.Format(_T("'%s','%s','%s','%s'"),
      m_strName,
      m_strSavedUserID,
      strSaveTime,
      m_strData);
   strRet.Format(_T("insert into %s(%s) values(%s)"), DB_TABLE_DesignData, strFormat, strValue);

   return strRet;
};

CDBDesignData * CDBDesignData::Instance()
{
   if (sm_inst.get() == 0)
      sm_inst = shared_ptr<CDBDesignData>(new CDBDesignData);

   return sm_inst.get();
}

BOOL CDBDesignData::UpdateAllDBInfoByID(CADOConn *pADOConn)
{
   ASSERT(pADOConn != NULL);
   BOOL bRet = TRUE;
   CString strSQL = _T("");
   pADOConn->BeginTrans(); 
   strSQL.Format(_T("update %s set \
      %s='%s',%s='%s',%s='%s',%s=%s where %s='%lld'"), DB_TABLE_DesignData,
      DBDesignData_key_cData, m_strData,
      DBDesignData_key_Name, m_strName,
      DBDesignData_key_cSavedUserID, m_strSavedUserID,
      DBDesignData_key_cSaveTime, DBS_GETDATESTR,
      DBDesignData_key_ID, m_nID);

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

BOOL CDBDesignData::InsertAllDBInfoByID(CADOConn *pADOConn)
{
   ASSERT(pADOConn != NULL);

   BOOL bRet = TRUE;

   CString strSQL = _T("");
   CString strLabel = _T("");
   CString strSaveTime = _T("");
   if (m_strSaveTime.IsEmpty())
   {
      strSaveTime = DBS_GETDATESTR;
   }
   else
   {
      strSaveTime.Format(_T("'%s'"), m_strSaveTime);
   }
   strSQL.Format(_T("insert into %s (%s, %s,%s,%s)\
					 values('%s','%s','%s','%s')"), DB_TABLE_DesignData, \
      DBDesignData_key_Name,               
      DBDesignData_key_cSavedUserID,       
      DBDesignData_key_cSaveTime,       
      DBDesignData_key_cData,
      m_strName,                           
      m_strSavedUserID,                    
      strSaveTime,
      m_strData
   );

   if (!pADOConn->ExecuteSQL(strSQL))
   {
      return FALSE;
   }
   return TRUE;
}

IMPLEMENT_SERIAL(CDBDesignDataList, CDataListMid, 1)
std::shared_ptr<CDBDesignDataList> CDBDesignDataList::sm_inst;

CDBDesignDataList::CDBDesignDataList()
{

}

CDBDesignDataList::~CDBDesignDataList()
{

}

CDBDesignData*  CDBDesignDataList::GetItem(int nIndex)
{
   if (nIndex < 0 || nIndex >= GetCount())
      return NULL;

   return (CDBDesignData*)GetAt(FindIndex(nIndex));
}

void CDBDesignDataList::AddItem(CDBDesignData* pItem)
{
   CDBDesignData*pData = new CDBDesignData;
   pData->Copy(pItem);
   AddTail(pData);
}

void CDBDesignDataList::DeleteItem(int nIndex)
{
   if (nIndex<0 || nIndex>GetCount())
      return;

   CDBDesignData *pObject = (CDBDesignData*)GetItem(nIndex);
   delete pObject;
   pObject = NULL;

   RemoveAt(FindIndex(nIndex));
}

BOOL CDBDesignDataList::DeleteUserByUserID(CADOConn* pADOConn, vector<CString>vecUserID)
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
   strSql.Format(_T("delete from %s where %s in (%s)"), _T("DesignData"), DBDesignData_key_ID, strUserID);
   return pADOConn->ExecuteSQL(strSql);
}

CDBDesignDataList* CDBDesignDataList::Instance()		//获取（指针）实例
{
   if (sm_inst.get() == 0)
      sm_inst = shared_ptr<CDBDesignDataList>(new CDBDesignDataList);

   return sm_inst.get();
}

#ifdef USING_GRIDCTRL_MARK
MAP_GridCtrl_AllData CDBDesignDataList::CreateGridData(const CString & strUserDuty/*=_T("")*/)
{
   MAP_GridCtrl_AllData map_all_data;

   int nIndex = 0, nCount = GetCount();
   int nValidCount = 1;
   for (nIndex = 0; nIndex < nCount; nIndex++)
   {
      CDBDesignData * pData = GetItem(nIndex);
      if (NULL != pData)
      {
         MAP_GridCtrl_RowData map_row_data;
         pData->InsertRowData(DBDesignData_key_ID, map_row_data, CB_enum_FieldData_Int, CB_enum_FieldCtrl_Text, _T("%lld"), pData->m_nID);             //ID
         pData->InsertRowData(DBDesignData_key_Name, map_row_data, FORMAT_STRING, pData->m_strName);         //名称
         pData->InsertRowData(DBDesignData_key_cSavedUserID, map_row_data, FORMAT_STRING, pData->m_strSavedUserID);  //用户ID
         pData->InsertRowData(DBDesignData_key_cSaveTime, map_row_data, CB_enum_FieldData_Time, CB_enum_FieldCtrl_DateTime, FORMAT_STRING, pData->m_strSaveTime);     //保存时间
         pData->InsertRowData(DBDesignData_key_cData, map_row_data, FORMAT_STRING, pData->m_strData);     //保存时间
         map_all_data.insert(make_pair(nValidCount, map_row_data));
         //行数据插入所有数据中

         nValidCount++;
      }
   }

   return map_all_data;
}
#endif

