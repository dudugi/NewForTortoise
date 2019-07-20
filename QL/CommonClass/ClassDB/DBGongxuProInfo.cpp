#include "StdAfx.h"
#include "DBGongxuProInfo.h"

IMPLEMENT_SERIAL(CDBGongxuProInfoData,  CDataMid, 1)
IMPLEMENT_SERIAL(CDBGongxuProInfoDataList,  CDataListMid, 1)

std::shared_ptr<CDBGongxuProInfoDataList> CDBGongxuProInfoDataList::sm_inst;

CDBGongxuProInfoData::CDBGongxuProInfoData()
{
	ResetData();
} 

CDBGongxuProInfoData::~CDBGongxuProInfoData()
{
}

void CDBGongxuProInfoData::ResetData()
{
	m_ID					= _T("");
	m_strProName			= _T("");
	m_strProcedureName		= _T("");
   m_strZhiPaiPerson = _T("");
}

void CDBGongxuProInfoData::Copy(CDBGongxuProInfoData *pData)
{
	ASSERT(pData != NULL);
	CDataMid::Copy(pData);
	m_ID				= pData->m_ID;
	m_strProName		= pData->m_strProName;
	m_strProcedureName	= pData->m_strProcedureName;
   m_strZhiPaiPerson = pData->m_strZhiPaiPerson;
}

BOOL CDBGongxuProInfoData::GetAllDBInfo( CADOConn *pADOConn )
{
	ASSERT(pADOConn != NULL);

	BOOL bRet = TRUE;

	if (NULL == pADOConn)
	{
		bRet = FALSE;
	}
	else
	{
		m_ID = pADOConn->GetValueString(DBFangAnGongxu_key_ID);
		m_strProName = pADOConn->GetValueString(DBFangAnGongxu_key_cFangAnName);
		m_strProcedureName = pADOConn->GetValueString(DBFangAnGongxu_key_cGXName);
      m_strZhiPaiPerson = pADOConn->GetValueString(DBFangAnGongxu_key_cZhiPaiPerson);
		bRet = TRUE;
	}

	return bRet;
}


BOOL CDBGongxuProInfoData::DelAllDBInfo( CADOConn *pADOConn )
{
	ASSERT(pADOConn != NULL);
	m_ID.Trim();
	ASSERT(!m_ID.IsEmpty());
	BOOL bRet = TRUE;

	CString strSQL = _T("");
	strSQL.Format(_T("delete from %s where %s='%s'")
		,DB_TABLE_FANGANGONGXU
		,DBFangAnGongxu_key_ID
		,m_ID);

	if (pADOConn->ExecuteSQL(strSQL))
	{
		bRet = TRUE;
	}
	else
	{
		bRet = FALSE;
	}

	return bRet;
}

BOOL CDBGongxuProInfoData::InsertAllDBInfo( CADOConn *pADOConn )
{
	ASSERT(pADOConn != NULL);
	m_strProName.Trim();
	m_strProcedureName.Trim();
	ASSERT(!m_strProName.IsEmpty());

	BOOL bRet = TRUE;

	CString strSQL = _T("");
	strSQL.Format(_T("insert into %s(%s,%s,%s) \
					 values('%s','%s','%s')"),DB_TABLE_FANGANGONGXU,
					 DBFangAnGongxu_key_cFangAnName, DBFangAnGongxu_key_cGXName,DBFangAnGongxu_key_cZhiPaiPerson,m_strProName, m_strProcedureName,m_strZhiPaiPerson);

	if (pADOConn->ExecuteSQL(strSQL))
	{
		bRet = TRUE;
	}
	else
	{
		bRet = FALSE;
	}

	return bRet;
}

//更新【整条】记录
BOOL CDBGongxuProInfoData::UpdateAllDBInfo(CADOConn *pADOConn)
{
	ASSERT(pADOConn != NULL);
	m_ID.Trim();
	m_strProName.Trim();
	m_strProcedureName.Trim();
	//ASSERT(!m_strProName.IsEmpty());
	ASSERT(!m_strProcedureName.IsEmpty());

	BOOL bRet = TRUE;

	CString strSQL = _T("");
	strSQL.Format(_T("update %s set %s = '%s', %s = '%s',%s = '%s' where %s = '%s'"), DB_TABLE_FANGANGONGXU,
					 DBFangAnGongxu_key_cFangAnName,m_strProName, DBFangAnGongxu_key_cGXName,m_strProcedureName,DBFangAnGongxu_key_cZhiPaiPerson,m_strZhiPaiPerson, DBFangAnGongxu_key_ID ,m_ID);

	if (pADOConn->ExecuteSQL(strSQL))
	{
		bRet = TRUE;
	}
	else
	{
		bRet = FALSE;
	}

	return bRet;
}



//CDBYarnFindInfoList
CDBGongxuProInfoDataList::CDBGongxuProInfoDataList()
{
	m_pADOConn = nullptr;
}
CDBGongxuProInfoDataList::~CDBGongxuProInfoDataList()
{
	for(int i=0;i< GetCount();i++)
	{
		DeleteItem(i);
	}
}

BOOL CDBGongxuProInfoDataList::GetListFromDB( CADOConn *pADOConn )
{
	Empty();
	BOOL bRet = FALSE;

	ASSERT(pADOConn != NULL);

	if (NULL == pADOConn)
	{
		bRet = FALSE;
	}
	else
	{
		m_pADOConn = pADOConn;

		CString strSQL = _T("");
      strSQL.Format(_T("select a.* from %s a left join %s b on a.%s = b.%s \
                       order by a.%s,b.%s asc"), 
                       DB_TABLE_FANGANGONGXU,DB_TABLE_PROCESS,DBFangAnGongxu_key_cGXName,DBProcess_key_Name,
                       DBFangAnGongxu_key_cFangAnName,DBProcess_key_SortID);

		pADOConn->GetRecordSet(strSQL);

		while (!pADOConn->adoEOF())
		{
			CDBGongxuProInfoData oData;
			oData.GetAllDBInfo(pADOConn);

			AddItem(&oData);
			pADOConn->MoveNext();
		}
	}

	return bRet;
}

CDBGongxuProInfoData*  CDBGongxuProInfoDataList::GetItem(int nIndex)
{
	if (nIndex<0||nIndex>=GetCount())
		return NULL;
	return (CDBGongxuProInfoData*)GetAt(FindIndex(nIndex));
}
void CDBGongxuProInfoDataList::AddItem(CDBGongxuProInfoData* pItem)
{
	CDBGongxuProInfoData*pData=new CDBGongxuProInfoData;
	pData->Copy(pItem);
	AddTail(pData);
}
void CDBGongxuProInfoDataList::DeleteItem(int nIndex)
{
	if (nIndex<0||nIndex>GetCount())
		return;
	CDBGongxuProInfoData *pObject=(CDBGongxuProInfoData*)GetItem(nIndex);
	if (pObject != nullptr)
	{
		delete pObject;
		pObject=NULL;
		RemoveAt(FindIndex(nIndex));
	}
}

CDBGongxuProInfoData* CDBGongxuProInfoDataList::GetItemByID( CString strID )
{
	CDBGongxuProInfoData * pItem = NULL;
	strID.Trim();
	if (!strID.IsEmpty())
	{
		for(int i=0;i< GetCount();i++)
		{
			CDBGongxuProInfoData * pObject = GetItem(i);
			if(strID == pObject->m_ID)
			{
				pItem = pObject;
				break;
			}
		}
	}

	return pItem;
}

int CDBGongxuProInfoDataList::GetIndexByID( CString strID )
{
	int nSel = -1;
	strID.Trim();
	if (!strID.IsEmpty())
	{
		for(int i=0;i< GetCount();i++)
		{
			CDBGongxuProInfoData * pObject = GetItem(i);
			if(strID == pObject->m_ID)
			{
				nSel = i;
				break;
			}
		}
	}

	return nSel;
}



// 获取工序方案列表
void CDBGongxuProInfoDataList::GetGongxuProNameLst(std::vector<CString> &nameLst)
{
	nameLst.clear();

	for(int i=0;i< GetCount();i++)
	{
		CDBGongxuProInfoData * pObject = GetItem(i);
		
		auto it = std::find_if(nameLst.begin() , nameLst.end() , [&](CString ele){return ele == pObject->m_strProName;});
		if (it == nameLst.end())
		{
			nameLst.push_back(pObject->m_strProName);
		}
	}
}

// 根据工序方案名获取工序列表
void CDBGongxuProInfoDataList::GetGongxuProByGongxuProName(std::vector<CString> &productionLst , CString proName)
{
	productionLst.clear();
	for(int i=0;i< GetCount();i++)
	{
		CDBGongxuProInfoData * pObject = GetItem(i);
		if(proName == pObject->m_strProName)
		{
			productionLst.push_back(pObject->m_strProcedureName);
		}
	}
}

void CDBGongxuProInfoDataList::GetGongxuProAndZhipaiPersonByGongxuProName( std::vector<pair<CString,CString>> &productionLst , CString proName )
{
   productionLst.clear();
   for(int i=0;i< GetCount();i++)
   {
      CDBGongxuProInfoData * pObject = GetItem(i);
      if(proName == pObject->m_strProName)
      {
         productionLst.push_back(make_pair(pObject->m_strProcedureName,pObject->m_strZhiPaiPerson));
      }
   }
}

// 添加工序方案
BOOL CDBGongxuProInfoDataList::AddGongxuProByGongxuProName(std::vector<CString> productionLst , CString proName)
{
	if (productionLst.size() == 0)
	{
		productionLst.push_back(_T(""));
	}

	BOOL bRet = TRUE;
	for (size_t i = 0; i < productionLst.size(); i++)
	{
		CDBGongxuProInfoData data;
		data.m_strProcedureName = productionLst[i];
		data.m_strProName = proName;
		bRet &= data.InsertAllDBInfo(m_pADOConn);
		AddItem(&data);
	}

	return bRet;
}

BOOL CDBGongxuProInfoDataList::AddGongxuProAndZhipaiPersonByGongxuProName( std::vector<pair<CString,CString>> productionLst , CString proName )
{
   //写入数据库 不获取就加入到链表中....  ID呢？
   BOOL bRet = TRUE;
   for (auto itr = productionLst.begin(); itr != productionLst.end(); itr++)
   {
      
      CDBGongxuProInfoData data;
      data.m_strProcedureName = itr->first;
      data.m_strProName = proName;
      data.m_strZhiPaiPerson = itr->second;
      bRet &= data.InsertAllDBInfo(m_pADOConn);
      AddItem(&data);
   }


   return bRet;
}

// 更新工序方案
BOOL CDBGongxuProInfoDataList::UpdateGongxuProByGongxuProName(std::vector<CString> productionLst , CString proName , CString oldProName)
{
	BOOL bRet = TRUE;
	/*bRet &= DeleteGongxuProByGongxuProName(oldProName);
	bRet &= AddGongxuProByGongxuProName(productionLst , proName);*/

	std::vector<CDBGongxuProInfoData*> pObjLst;
	for(int i=0; i < GetCount();i++)
	{
		CDBGongxuProInfoData * pObject = GetItem(i);
		if(pObject->m_strProName == oldProName)
		{
			pObjLst.push_back(pObject);
		}
	}

	if (pObjLst.size() <= productionLst.size())
	{
		for (size_t i = 0; i < productionLst.size(); i++)
		{
			if (i < pObjLst.size())
			{
				pObjLst[i]->m_strProcedureName = productionLst[i];
				pObjLst[i]->m_strProName = proName;
				bRet &= pObjLst[i]->UpdateAllDBInfo(m_pADOConn);
			}
			else
			{
				CDBGongxuProInfoData data;
				data.m_strProcedureName = productionLst[i];
				data.m_strProName = proName;
				bRet &= data.InsertAllDBInfo(m_pADOConn);
				AddItem(&data);
			}
		}
	}
	else
	{
		for (size_t i = 0; i < pObjLst.size(); i++)
		{
			if (i < productionLst.size())
			{
				pObjLst[i]->m_strProcedureName = productionLst[i];
				pObjLst[i]->m_strProName = proName;
				bRet &= pObjLst[i]->UpdateAllDBInfo(m_pADOConn);
			}
			else
			{
				bRet &= pObjLst[i]->DelAllDBInfo(m_pADOConn);
			}
		}
	}

	return bRet;
}

BOOL CDBGongxuProInfoDataList::UpdateGongxuProAndZhipaiPersonByGongxuProName( std::vector<pair<CString,CString>> productionLst , CString proName , CString oldProName )
{
   BOOL bRet = TRUE;

	std::vector<CDBGongxuProInfoData*> pObjLst;
	for(int i=0; i < GetCount();i++)
	{
		CDBGongxuProInfoData * pObject = GetItem(i);
		if(pObject->m_strProName == oldProName)
		{
			pObjLst.push_back(pObject);
		}
	}
   int nCount = productionLst.size();
   //删除旧方案，重新插入
   DeleteGongxuProByGongxuProName(oldProName);
   for (auto itr = productionLst.begin(); itr!= productionLst.end(); itr++)
   {
      CDBGongxuProInfoData data;
      data.m_strProcedureName = itr->first;
      data.m_strProName = proName;
      data.m_strZhiPaiPerson = itr->second;
      bRet &= data.InsertAllDBInfo(m_pADOConn);
      AddItem(&data);
   }
	return bRet;
}

// 删除工序方案
BOOL CDBGongxuProInfoDataList::DeleteGongxuProByGongxuProName(CString proName)
{
	BOOL bRet = TRUE;
	for(int i=0;i< GetCount();i++)
	{
		CDBGongxuProInfoData * pObject = GetItem(i);
		if(proName == pObject->m_strProName)
		{
			bRet &= pObject->DelAllDBInfo(m_pADOConn);
		}
	}

	return bRet;
}
struct S_GX_Filed
{
   CString strFiled;
   CString strFiledValued;
   S_GX_Filed()
   {
      strFiled = _T("");
      strFiledValued = _T("");
   }
};
void CDBGongxuProInfoDataList::CreateGridStyleGX(CADOConn *pADOConn,MAP_GridCtrl_AllData &allData,vector<CString> &vecGXField)
{
   ASSERT(pADOConn != NULL);
   vector<CString> vecFA;//工序方案，查重
   map<CString,S_GX_Filed> mapGXField;
   CString strSql = _T("");
   strSql.Format(_T("select * from %s"),DB_TABLE_FANGANGONGXU);
   pADOConn->GetRecordSet(strSql);
   while(!pADOConn->adoEOF())
   {
      CDBGongxuProInfoData oData;
      oData.GetAllDBInfo(pADOConn);
      CString strFiled;
      strFiled.Format(_T("%s工序"),oData.m_strProcedureName);
      auto itr_filed = find(vecGXField.begin(),vecGXField.end(),strFiled);
      if (itr_filed == vecGXField.end())
      {
         vecGXField.push_back(strFiled);
      }
      S_GX_Filed s_gx_filed;
      s_gx_filed.strFiled = strFiled;
      s_gx_filed.strFiledValued = oData.m_strZhiPaiPerson;
      CString strKey;
      strKey.Format(_T("%s(%d)"),oData.m_strProName,mapGXField.size());
      mapGXField.insert(make_pair(strKey,s_gx_filed));

      auto itr_FA = find(vecFA.begin(),vecFA.end(),oData.m_strProName);
      if (itr_FA == vecFA.end())
      {
         vecFA.push_back(oData.m_strProName);
      }
      pADOConn->MoveNext();
   }
   for (auto itr_FA = vecFA.begin();itr_FA != vecFA.end();++itr_FA)
   {
      MAP_GridCtrl_RowData rowData;
      InsertRowData(DBFangAnGongxu_key_cFangAnName,*itr_FA,rowData);
      for (auto itr_map = mapGXField.begin();itr_map != mapGXField.end();++itr_map)
      {
         CString strKey = itr_map->first.Left(itr_map->first.Find('('));
         if (strKey == *itr_FA)
         {
            InsertRowData(itr_map->second.strFiled,itr_map->second.strFiledValued,rowData);
         }
      }
      allData.insert(make_pair(allData.size(),rowData));
   }
}

CDBGongxuProInfoDataList * CDBGongxuProInfoDataList::Instance()
{
	if(sm_inst.get() == 0)
		sm_inst = shared_ptr<CDBGongxuProInfoDataList>(new CDBGongxuProInfoDataList);

	return sm_inst.get();
}																					 