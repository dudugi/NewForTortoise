#include "StdAfx.h"
#include "DBSizeInfo.h"
#include "DBKeyDef.h"

//部位表

IMPLEMENT_SERIAL(CDBSizePartInfoData,  CDataMid, 1)
IMPLEMENT_SERIAL(CDBSizePartInfoList,  CDataListMid, 1)

std::shared_ptr<CDBSizePartInfoData> CDBSizePartInfoData::sm_inst;
std::shared_ptr<CDBSizePartInfoList> CDBSizePartInfoList::sm_inst;

CDBSizePartInfoData::CDBSizePartInfoData()
{
	ResetData();
}

CDBSizePartInfoData::~CDBSizePartInfoData()
{

}

void CDBSizePartInfoData::ResetData()
{
	m_nSizePartID = 0;
	m_strName = _T("");
	m_nDefault = En_PART_DEFAULT_NULL;
   m_nUserSort =  0;
   m_cMemo = _T("");//部位说明 yangjr 2019/07/14
	SetDataType(DAT_SIZEPART);
}

void CDBSizePartInfoData::Copy(CDBSizePartInfoData *pData)
{
	ASSERT(pData != NULL);
	CDataMid::Copy(pData);

   m_nSizePartID  =  pData->m_nSizePartID ;
   m_strName      =  pData->m_strName     ;
   m_nDefault     =  pData->m_nDefault    ;
   m_nUserSort    =  pData->m_nUserSort   ;
   m_cMemo = pData->m_cMemo;//部位说明 yangjr 2019/07/14
}

void CDBSizePartInfoData::Serialize(CArchive& ar)
{

	CDataMid::Serialize(ar);//父类函数

	int nTagSize = 0;
	CString strName;
	int nNameSize;

	ar.Flush();
	if (ar.IsStoring())
	{
		MySerial.SaveDataInt64(ar,_T("THSIZEID"),m_nSizePartID);
		MySerial.SaveDataStr(ar,_T("THENAMES"),m_strName);
		MySerial.SaveDataInt(ar,_T("TDEFAULT"),m_nDefault);
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
			else if (strName == _T("THSIZEID"))
			{
				ar >>nTagSize >> m_nSizePartID;
			}
			else if (strName == _T("THENAMES"))
			{
				ar >>nTagSize >> m_strName;
			}
			else if (strName == _T("TDEFAULT"))
			{
				ar >> nTagSize >> m_nDefault;
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

CDBSizePartInfoData * CDBSizePartInfoData::Instance()
{
	if(sm_inst.get() == 0)
		sm_inst = shared_ptr<CDBSizePartInfoData>(new CDBSizePartInfoData);

	return sm_inst.get();
}

BOOL CDBSizePartInfoData::GetAllDBInfo(CADOConn *pADOConn)
{
	ASSERT(pADOConn!= NULL);
	BOOL bRet= FALSE;

	if(NULL != pADOConn)
	{
		m_nSizePartID = _ttoi64(pADOConn->GetValueString(DBSizePart_key_ID));
		m_strName = pADOConn->GetValueString(DBSizePart_key_Name);
		m_nDefault = _ttoi(pADOConn->GetValueString(DBSizePart_key_Default));
      m_nUserSort =  pADOConn->GetValueInt(DBSizePart_key_UserSort);
      m_cMemo = pADOConn->GetValueString(DBSizePart_key_cMemo);
		bRet = TRUE;
	}
	return bRet;
}

BOOL CDBSizePartInfoData::InsertAllDBInfo(CADOConn *pADOConn)
{
	ASSERT(pADOConn!= NULL);
	BOOL bRet= FALSE;

	if (pADOConn!=NULL)
	{
		CString strSQL = _T("");
		strSQL.Format(_T("insert into %s(%s,%s,%s,%s) values('%s','%d','%d','%s')")
         ,DB_TABLE_SIZEPART,DBSizePart_key_Name,DBSizePart_key_Default,DBSizePart_key_UserSort,DBSizePart_key_cMemo
         ,m_strName,m_nDefault,m_nUserSort,m_cMemo);
		bRet = pADOConn->ExecuteSQL(strSQL);		
	}
	return bRet;
}

BOOL CDBSizePartInfoData::UpdateAllDBInfoByID(CADOConn *pADOConn)
{
	ASSERT(pADOConn!= NULL);
	BOOL bRet= FALSE;

	if (pADOConn!=NULL)
	{
		CString strSQL = _T("");
		strSQL.Format(_T("update %s set %s = '%s',%s = '%d',%s = '%d',%s = '%s' where %s = %d"),DB_TABLE_SIZEPART
			,DBSizePart_key_Name,m_strName
			,DBSizePart_key_Default,m_nDefault
         ,DBSizePart_key_UserSort,m_nUserSort
         ,DBSizePart_key_cMemo,m_cMemo
			,DBSizePart_key_ID,m_nSizePartID
			);
		bRet = pADOConn->ExecuteSQL(strSQL);		
	}
	return bRet;
}

BOOL CDBSizePartInfoData::DelAllDBInfoByID(CADOConn *pADOConn)
{
	ASSERT(pADOConn!= NULL);
	BOOL bRet= FALSE;

	if (NULL != pADOConn)
	{
		CString strSQL = _T("");
		strSQL.Format(_T("delete from %s where %s = %d"),DB_TABLE_SIZEPART,DBSizePart_key_ID,m_nSizePartID);
		bRet = pADOConn->ExecuteSQL(strSQL);
	}

	return bRet;
}


CDBSizePartInfoList::CDBSizePartInfoList()
{

}

CDBSizePartInfoList::~CDBSizePartInfoList()
{
	Empty();
}

CDBSizePartInfoData* CDBSizePartInfoList::GetItem(int nIndex)
{
	if (nIndex<0||nIndex>=GetCount())
		return NULL;
	return (CDBSizePartInfoData*)GetAt(FindIndex(nIndex));
}

void CDBSizePartInfoList::AddItem(CDBSizePartInfoData* pItem)
{
	CDBSizePartInfoData*pData=new CDBSizePartInfoData;
	pData->Copy(pItem);
	AddTail(pData);
}

void CDBSizePartInfoList::DeleteItem(int nIndex)
{
	if (nIndex<0||nIndex>GetCount())
		return;
	CDBSizePartInfoData *pObject=(CDBSizePartInfoData*)GetItem(nIndex);
	delete pObject;
	pObject=NULL;
	RemoveAt(FindIndex(nIndex));
}

CString CDBSizePartInfoList::GetItemNameByID(__int64 nPartID)
{
   CString strRet = _T("");

   int nIndex = 0,nCount = GetCount();
   for (nIndex = 0;nIndex < nCount;nIndex++)
   {
      auto pData = GetItem(nIndex);
      if (NULL != pData)
      {
         if (pData->m_nSizePartID == nPartID)
         {
            strRet = pData->m_strName;
            break;
         }
      }
   }

   return strRet;
}

CString CDBSizePartInfoList::GetItemMemoByID(__int64 nPartID)
{
   CString strRet = _T("");

   int nIndex = 0,nCount = GetCount();
   for (nIndex = 0;nIndex < nCount;nIndex++)
   {
      auto pData = GetItem(nIndex);
      if (NULL != pData)
      {
         if (pData->m_nSizePartID == nPartID)
         {
            strRet = pData->m_cMemo;
            break;
         }
      }
   }

   return strRet;
}

__int64 CDBSizePartInfoList::GetItemIDByName(CString strPartName)
{
	__int64 nRet = 0;

	int nIndex = 0,nCount = GetCount();
	for (nIndex = 0;nIndex < nCount;nIndex++)
	{
		auto pData = GetItem(nIndex);
		if (NULL != pData)
		{
			if (pData->m_strName == strPartName)
			{
				nRet = pData->m_nSizePartID;
				break;
			}
		}
	}

	return nRet;
}

CDBSizePartInfoData* CDBSizePartInfoList::GetItemByName(const CString & strPartName)
{
   CDBSizePartInfoData * pRet = NULL;

   int nIndex = 0,nCount = GetCount();
   for (nIndex = 0;nIndex < nCount;nIndex++)
   {
      auto pData = GetItem(nIndex);
      if (NULL != pData)
      {
         if (pData->m_strName == strPartName)
         {
            pRet = pData;
            break;
         }
      }
   }

   return pRet;
}

void CDBSizePartInfoList::GetListFromDB(CADOConn *pADOConn)
{
	ASSERT(pADOConn != NULL);
	
	Empty();
	CString strSQL = _T("");
	strSQL.Format(_T("select * from %s order by %s,%s"),DB_TABLE_SIZEPART,DBSizePart_key_UserSort,DBSizePart_key_ID);

	pADOConn->GetRecordSet(strSQL);
	while (!pADOConn->adoEOF())
	{
		CDBSizePartInfoData oData;
		if(oData.GetAllDBInfo(pADOConn))
		{
			AddItem(&oData);
		}
		pADOConn->MoveNext();
	}
}


CDBSizePartInfoList * CDBSizePartInfoList::Instance()
{
	if(sm_inst.get() == 0)
		sm_inst = shared_ptr<CDBSizePartInfoList>(new CDBSizePartInfoList);

	return sm_inst.get();
}

BOOL CDBSizePartInfoList::GetPartSort(CADOConn* pAdo,map<CString,CString>& mapData)
{
   mapData.clear();
   ASSERT(pAdo != NULL);
   CString strSql;
   //获取的ID应该是数据库的ID 而不是用户可以调整的显示ID
   strSql.Format(_T("select %s,%s from %s order by %s"),
      DBSizePart_key_Name,
      DBSizePart_key_ID,
      DB_TABLE_SIZEPART,
      DBSizePart_key_UserSort);

   pAdo->GetRecordSet(strSql);
   while(!pAdo->adoEOF())
   {
      mapData.insert(make_pair(pAdo->GetValueString(DBSizePart_key_Name),pAdo->GetValueString(DBSizePart_key_ID)));
      pAdo->MoveNext();
   }
   return TRUE;
}

