#include "StdAfx.h"
#include "DBGlobalSet.h"

IMPLEMENT_SERIAL(CDBGlobalSetData,  CDataMid, 1)
IMPLEMENT_SERIAL(CDBGlobalSetList,  CDataListMid, 1)

std::shared_ptr<CDBGlobalSetData> CDBGlobalSetData::sm_inst;
std::shared_ptr<CDBGlobalSetList> CDBGlobalSetList::sm_inst;

CDBGlobalSetData::CDBGlobalSetData()
{
	ResetData();
} 

CDBGlobalSetData::~CDBGlobalSetData()
{
}

void CDBGlobalSetData::ResetData()
{
	m_nID = ID_DEFAULT;		//自增ID
	m_strName = _T("");		//名称
	m_strValue = _T("");	//值
	m_strRemark = _T("");	//备注

	SetDataType(DAT_CONFIG);
}

void CDBGlobalSetData::Copy(CDBGlobalSetData *pData)
{
	ASSERT(pData != NULL);
	CDataMid::Copy(pData);
	
	m_nID = pData->m_nID;			
	m_strName = pData->m_strName;		
	m_strValue = pData->m_strValue;	
	m_strRemark = pData->m_strRemark;
}


void CDBGlobalSetData::Serialize(CArchive& ar)
{
	CDataMid::Serialize(ar);//父类函数

	int nTagSize = 0;
	CString strName;
	int nNameSize;

	ar.Flush();
	if (ar.IsStoring())
	{

		MySerial.SaveDataInt(ar,_T("CFGADDID"),m_nID);
		MySerial.SaveDataStr(ar,_T("CFGNAME0"),m_strName);
		/* 下面数据还未写串行化
		m_strValue = _T("");	//值
		m_strRemark = _T("");	//备注
		*/

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
			else if (strName == _T("CFGADDID"))
			{
				ar >> nTagSize >> m_nID;
			}
			else if (strName == _T("CFGNAME0"))
			{
				ar >>nTagSize >> m_strName;
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

BOOL CDBGlobalSetData::GetAllDBInfo(CADOConn *pADOConn)
{
	ASSERT(pADOConn != NULL);

	BOOL bRet = TRUE;

	if (NULL == pADOConn)
	{
		bRet = FALSE;
	}
	else
	{
		m_nID = pADOConn->GetValueInt(DBGlobalSet_key_ID);
		m_strName = pADOConn->GetValueString(DBGlobalSet_key_Name);
		m_strValue = pADOConn->GetValueString(DBGlobalSet_key_Value);
		m_strRemark = pADOConn->GetValueString(DBGlobalSet_key_Remark);

		bRet = TRUE;
	}

	return bRet;
}

CString CDBGlobalSetData::GetTextUpdateAllDBInfoByID()
{
	CString strRet = _T("");

	if (m_nID > ID_DEFAULT)
	{
		strRet.Format(_T("update %s set %s = '%s',%s = '%s',%s = '%s' where %s = %d"),DB_TABLE_CONFIG
						 ,DBGlobalSet_key_Name,m_strName
						 ,DBGlobalSet_key_Value,m_strValue
						 ,DBGlobalSet_key_Remark,m_strRemark
						 ,DBGlobalSet_key_ID,m_nID
						 );
	}

	return strRet;
}

CString CDBGlobalSetData::GetTextInsertAllDBInfoByID()
{
   CString strRet = _T("");

   strRet.Format(_T("insert into %s (%s,%s,%s) values('%s','%s','%s');"),DB_TABLE_CONFIG\
      ,DBGlobalSet_key_Name,DBGlobalSet_key_Value,DBGlobalSet_key_Remark\
      ,m_strName,m_strValue,m_strRemark);

   return strRet;
}

BOOL CDBGlobalSetData::UpdateAllDBInfoByID(CADOConn *pADOConn)
{
	ASSERT(pADOConn!= NULL);
	BOOL bRet= FALSE;

	if ((pADOConn!=NULL) && (m_nID>ID_DEFAULT))
	{
		CString strSQL = _T("");
		strSQL = GetTextUpdateAllDBInfoByID();
		bRet = pADOConn->ExecuteSQL(strSQL);
	}
	return bRet;
}

BOOL CDBGlobalSetData::InsertAllDBInfo(CADOConn *pADOConn)
{
	ASSERT(pADOConn!= NULL);
	BOOL bRet = FALSE;

	CString strSQL = _T("");

	strSQL.Format(_T("insert into %s (%s,%s,%s)values('%s','%s','%s')"),DB_TABLE_CONFIG\
		,DBGlobalSet_key_Name,DBGlobalSet_key_Value,DBGlobalSet_key_Remark\
		,m_strName,m_strValue,m_strRemark);

	bRet = pADOConn->ExecuteSQL(strSQL);

	return bRet;
}

CDBGlobalSetData * CDBGlobalSetData::Instance()
{
	if(sm_inst.get() == 0)
		sm_inst = shared_ptr<CDBGlobalSetData>(new CDBGlobalSetData);

	return sm_inst.get();
}

BOOL CDBGlobalSetData::SetData_By_Key(CString strKey, CString strValue)
{
	BOOL bRet = TRUE;
	if (DBGlobalSet_key_ID == strKey)
	{
		m_nID = _ttoi(strValue);		
	}
	else if (DBGlobalSet_key_Name == strKey)
	{
		m_strName = strValue;
	}
	else if (DBGlobalSet_key_Value == strKey)
	{
		m_strValue = strValue;
	}
	else if (DBGlobalSet_key_Remark == strKey)
	{
		m_strRemark = strValue;
	}
	else
	{
		bRet = FALSE;
	}
	return bRet;
}

tag_sql_data CDBGlobalSetData::GetDBAllValueByName(CADOConn* pADOConn,CString strName)
{
	ASSERT(pADOConn != NULL);
	tag_sql_data nRet;

	strName.Trim();
	if (!strName.IsEmpty())
	{
		CString strSQL = _T("");
		strSQL.Format(_T("select * from %s where %s = '%s'"),DB_TABLE_CONFIG,DBGlobalSet_key_Name,strName);
		pADOConn->GetRecordSet(strSQL);
		CDBGlobalSetData objData;
		while (!pADOConn->adoEOF())
		{
			objData.GetAllDBInfo(pADOConn);
			break;
		}

		nRet.nID = objData.m_nID;
		nRet.strName = objData.m_strName;
		nRet.strValue = objData.m_strValue;
		nRet.strRemark = objData.m_strRemark;
	}

	return nRet;
}

CString CDBGlobalSetData::GetDBValueByName(CADOConn* pADOConn,CString strName)
{
	ASSERT(pADOConn != NULL);
	CString strRet = _T("");

	strName.Trim();
	if (!strName.IsEmpty())
	{
		CString strSQL = _T("");
		strSQL.Format(_T("select * from %s where %s = '%s'"),DB_TABLE_CONFIG,DBGlobalSet_key_Name,strName);
		pADOConn->GetRecordSet(strSQL);
		CDBGlobalSetData objData;
		while (!pADOConn->adoEOF())
		{
			objData.GetAllDBInfo(pADOConn);
			break;
		}

		strRet = objData.m_strValue;
	}
	
	return strRet;
}

#ifdef USING_GRIDCTRL_MARK

MAP_GridCtrl_RowData CDBGlobalSetData::CreateGridRowData()
{ 
	MAP_GridCtrl_RowData map_row_data;

	CString strTmp;
	strTmp.Format(FORMAT_INT,m_nID);
	InsertRowData(DBGlobalSet_key_ID		,strTmp			,map_row_data,CB_enum_FieldData_Int);
	InsertRowData(DBGlobalSet_key_Name		,m_strName		,map_row_data);
	InsertRowData(DBGlobalSet_key_Value		,m_strValue		,map_row_data);
	InsertRowData(DBGlobalSet_key_Remark	,m_strRemark	,map_row_data);

	return map_row_data;
}

#endif // #ifdef USING_GRIDCTRL_MARK

//CDBGlobalSetList
CDBGlobalSetList::CDBGlobalSetList()
{
}

CDBGlobalSetList::~CDBGlobalSetList()
{
}

CDBGlobalSetData*  CDBGlobalSetList::GetItem(int nIndex)
{
	if (nIndex<0||nIndex>=GetCount())
		return NULL;
	return (CDBGlobalSetData*)GetAt(FindIndex(nIndex));
}

CDBGlobalSetData* CDBGlobalSetList::GetItemByName(CString strName)
{
   CDBGlobalSetData * pRet = NULL;

   int nCount = GetCount();
   for (int nIndex = 0;nIndex < nCount;++nIndex)
   {
      auto pData = GetItem(nIndex);
      if (NULL != pData)
      {
         if(pData->m_strName == strName)
         {
            pRet = pData;
            break;
         }
      }
   }
   return pRet;
}

void CDBGlobalSetList:: AddItem(CDBGlobalSetData* pItem)
{
	CDBGlobalSetData*pData=new CDBGlobalSetData;
	pData->Copy(pItem);
	AddTail(pData);
}

void CDBGlobalSetList::DeleteItem(int nIndex)
{
	if (nIndex<0||nIndex>GetCount())
		return;
	CDBGlobalSetData *pObject=(CDBGlobalSetData*)GetItem(nIndex);
	delete pObject;
	pObject=NULL;
	RemoveAt(FindIndex(nIndex));
}


CDBGlobalSetList * CDBGlobalSetList::Instance()
{
	if(sm_inst.get() == 0)
		sm_inst = shared_ptr<CDBGlobalSetList>(new CDBGlobalSetList);

	return sm_inst.get();
}


void CDBGlobalSetList::GetListFromDB(CADOConn *pADOConn)
{
	ASSERT(pADOConn != NULL);

	Empty();
	CString strSQL = _T("");
	strSQL.Format(_T("select * from %s"),DB_TABLE_CONFIG);

	pADOConn->GetRecordSet(strSQL);
	while (!pADOConn->adoEOF())
	{
		CDBGlobalSetData oData;
		oData.GetAllDBInfo(pADOConn);
		AddItem(&oData);
		pADOConn->MoveNext();
	}
}

CString CDBGlobalSetList::GetValueByName(CString strName)
{
	CString  strRet = _T("");
	strName.Trim();

	for (int nIndex = 0;nIndex < GetCount();nIndex++)
	{
		auto pData = GetItem(nIndex);
		if (NULL != pData && pData->m_strName == strName)
		{
			strRet = pData->m_strValue;
			strRet.Trim();
			break;
		}
	}

	return strRet;
}

//根据需要的名称从链表中获取相关的数值		by WangZY 2018/03/09
int CDBGlobalSetList::GetIntValueByName(CString strName, int nDef)
{
	CString strValue = CDBGlobalSetList::Instance()->GetValueByName(strName);	
	if (!strValue.IsEmpty())
	{
		int nCount = _ttoi(strValue);
		if (nCount>0)
		{
			return nCount;
		}
	}

	return nDef;
}

COLORREF CDBGlobalSetList::GetColorValueByName(CString strName)
{
   CString strValue = CDBGlobalSetList::Instance()->GetValueByName(strName);	
   if (!strValue.IsEmpty())
   {
      strValue.Replace('（','(');
      strValue.Replace('）',')');
      strValue.Replace('，',',');

      int ipos_start = strValue.Find(_T("("));
      if (ipos_start < 0)
      {
            return RGB(0,0,0);
      }
      ipos_start += 1;
      int ipos_end = strValue.Find(_T(","),ipos_start);
      if (ipos_end < 0)
      {
           return RGB(0,0,0);
      }

      CString str_r = strValue.Mid(ipos_start,ipos_end-ipos_start);
      int r = _ttoi(str_r);

      ipos_start = ipos_end;
      ipos_start += 1;
      ipos_end = strValue.Find(_T(","),ipos_start);
      if (ipos_end < 0)
      { 
         return RGB(0,0,0);
      }
      CString str_g = strValue.Mid(ipos_start,ipos_end-ipos_start);
      int g = _ttoi(str_g);

      ipos_start = ipos_end;
      ipos_start += 1;
      ipos_end = strValue.Find(_T(")"),ipos_start);
      if (ipos_end < 0)
      { 
         return RGB(0,0,0);
      }
      CString str_b = strValue.Mid(ipos_start,ipos_end-ipos_start);
      int b = _ttoi(str_b);

      return RGB(r,g,b);
   }
   return RGB(0,0,0);
}

/*
#ifdef USING_GRIDCTRL_MARK
MAP_GridCtrl_AllData CDBGlobalSetList::CreatrGridData()
{
	MAP_GridCtrl_AllData  map_all_data;

	int nIndex = 0,nCount = GetCount();
	int nValidCount = 1;
	for (nIndex = 0;nIndex < nCount;nIndex++)
	{
		CDBGlobalSetData * pData = GetItem(nIndex);
		if (NULL != pData)
		{
			MAP_GridCtrl_RowData map_row_data;

			S_GridCtrl_FieldData s_filed_data_ID;
			s_filed_data_ID.strValue.Format(FORMAT_INT,pData->m_nID);
			s_filed_data_ID.fieldDataType = CB_enum_FieldData_Int;
			s_filed_data_ID.fieldCtrlType = CB_enum_FieldCtrl_Text;
			map_row_data.insert(make_pair(DBGlobalSet_key_ID,s_filed_data_ID));	//自增ID

			S_GridCtrl_FieldData s_filed_TBName;
			s_filed_TBName.strValue = pData->m_strName;
			s_filed_TBName.fieldDataType = CB_enum_FieldData_CString;
			s_filed_TBName.fieldCtrlType = CB_enum_FieldCtrl_Text;
			map_row_data.insert(make_pair(DBGlobalSet_key_Name,s_filed_TBName));//名称

			S_GridCtrl_FieldData s_filed_Field;
			s_filed_Field.strValue = pData->m_strValue;
			s_filed_Field.fieldDataType = CB_enum_FieldData_CString;
			s_filed_Field.fieldCtrlType = CB_enum_FieldCtrl_Text;
			map_row_data.insert(make_pair(DBGlobalSet_key_Value,s_filed_Field));//值

			S_GridCtrl_FieldData s_filed_Show;
			s_filed_Show.strValue = pData->m_strRemark;
			s_filed_Show.fieldDataType = CB_enum_FieldData_CString;
			s_filed_Show.fieldCtrlType = CB_enum_FieldCtrl_Text;
			map_row_data.insert(make_pair(DBGlobalSet_key_Remark,s_filed_Show));//说明

			//写入行数据

			map_all_data.insert(make_pair(nValidCount,map_row_data));
			//行数据插入所有数据中

			nValidCount++;
		}
	}
	return map_all_data;
}
#endif // USING_GRIDCTRL_MARK
*/