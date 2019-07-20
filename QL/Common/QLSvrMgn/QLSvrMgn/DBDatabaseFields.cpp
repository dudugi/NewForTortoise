#include "StdAfx.h"
#include "DBDatabaseFields.h"

IMPLEMENT_SERIAL(CDBDatabaseFields,  CDataMid, 1)
IMPLEMENT_SERIAL(CDBDatabaseFieldsList,  CDataListMid, 1)
// 
// std::shared_ptr<CDBDatabaseFields> CDBGlobalSetData::sm_inst;
// std::shared_ptr<CDBDatabaseFieldsList> CDBGlobalSetList::sm_inst;

#define FIELDSNAME			_T("FIELNAME")
#define FIELDSTYPE			_T("FIELTYPE")
#define FIELDSLENGTH		_T("FILENGTH")
#define FIELDSPREC			_T("FIELPREC")
#define FIELDSSCALE			_T("FIELSCAL")
#define FIELDSEED			_T("FIELSEED")
#define FIELDSINCREMENT		_T("FIELINCR")
#define FIELDSPRIMARYKEY	_T("FIPRMARY")

#define TABLENAME			_T("TABLENAM")
#define TABLELIST			_T("LISTTABL")


CDBDatabaseFields::CDBDatabaseFields(void)
{
	ResetData();
}


CDBDatabaseFields::~CDBDatabaseFields(void)
{
}


void CDBDatabaseFields::ResetData()
{
	m_strFieldsName = _T("");
	m_strFieldsType = _T("");
	m_nFieldsLength = 0;
	m_nFieldsPrec = 0;
	m_nFieldsScale = 0;
	m_nFieldsSeed = 0;
	m_nFieldsIncrement = 0;
	m_bFieldsPrimary = FALSE;

	SetDataType(DAT_CONFIG);
}

void CDBDatabaseFields::Copy(CDBDatabaseFields *pData)
{
	ASSERT(pData != NULL);
	CDataMid::Copy(pData);

	m_strFieldsName = pData->m_strFieldsName;
	m_strFieldsType = pData->m_strFieldsType;
	m_nFieldsLength = pData->m_nFieldsLength;
	m_nFieldsPrec = pData->m_nFieldsPrec;
	m_nFieldsScale = pData->m_nFieldsScale;
	m_nFieldsSeed = pData->m_nFieldsSeed;
	m_nFieldsIncrement = pData->m_nFieldsIncrement;
	m_bFieldsPrimary = pData->m_bFieldsPrimary;
}

void CDBDatabaseFields::Serialize(CArchive& ar)
{
	CDataMid::Serialize(ar);//父类函数

	int nTagSize = 0;
	CString strName = _T("");
	int nNameSize = 0;


	ar.Flush();
	if (ar.IsStoring())
	{

		MySerial.SaveDataStr(ar, FIELDSNAME, m_strFieldsName);
		MySerial.SaveDataStr(ar, FIELDSTYPE, m_strFieldsType);
		MySerial.SaveDataInt(ar, FIELDSLENGTH, m_nFieldsLength);
		MySerial.SaveDataInt(ar, FIELDSPREC, m_nFieldsPrec);
		MySerial.SaveDataInt(ar, FIELDSSCALE, m_nFieldsScale);
		MySerial.SaveDataInt(ar, FIELDSEED, m_nFieldsSeed);
		MySerial.SaveDataInt(ar, FIELDSINCREMENT, m_nFieldsIncrement);
		MySerial.SaveDataInt(ar, FIELDSPRIMARYKEY, m_bFieldsPrimary);
		
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
			else if (strName == FIELDSNAME)
			{
				ar >> nTagSize >> m_strFieldsName;
			}
			else if (strName == FIELDSTYPE)
			{
				ar >>nTagSize >> m_strFieldsType;
			}
			else if(strName == FIELDSLENGTH)
			{
				ar >>nTagSize >> m_nFieldsLength;
			}
			else if(strName == FIELDSPREC)
			{
				ar >>nTagSize >> m_nFieldsPrec;
			}
			else if(strName == FIELDSSCALE)
			{
				ar >>nTagSize >> m_nFieldsScale;
			}
			else if (strName == FIELDSEED)
			{
				ar >>nTagSize >> m_nFieldsSeed;
			}
			else if (strName == FIELDSINCREMENT)
			{
				ar >>nTagSize >> m_nFieldsIncrement;
			}
			else if (strName == FIELDSPRIMARYKEY)
			{
				ar >>nTagSize >> m_bFieldsPrimary;
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


//CDBDatabaseFieldsList
CDBDatabaseFieldsList::CDBDatabaseFieldsList()
{
}

CDBDatabaseFieldsList::~CDBDatabaseFieldsList()
{
}

CDBDatabaseFields* CDBDatabaseFieldsList::GetItem(int nIndex)	//根据索引获取Item
{
	if (nIndex<0||nIndex>=GetCount())
		return NULL;
	return (CDBDatabaseFields*)GetAt(FindIndex(nIndex));
}

void CDBDatabaseFieldsList::AddItem(CDBDatabaseFields* pItem)	//添加Item
{
	CDBDatabaseFields* pData=new CDBDatabaseFields;
	pData->Copy(pItem);
	AddTail(pData);

}

void CDBDatabaseFieldsList::DeleteItem(int nIndex)			//删除固定索引Item
{
	if (nIndex<0||nIndex>GetCount())
		return;
	CDBDatabaseFields *pObject=(CDBDatabaseFields*)GetItem(nIndex);
	delete pObject;
	pObject=NULL;
	RemoveAt(FindIndex(nIndex));
}


////////////////////////数据库表名称///////////////////////////////////////
IMPLEMENT_SERIAL(CDBDatabaseTable,  CDataMid, 1)
IMPLEMENT_SERIAL(CDBDatabaseTableList,  CDataListMid, 1)

CDBDatabaseTable::CDBDatabaseTable()
{
	ResetData();
}

CDBDatabaseTable::~CDBDatabaseTable()
{
	//this;
}

void CDBDatabaseTable::ResetData()
{
	m_strTableName = _T("");

	m_listFields.Empty();
}


void CDBDatabaseTable::Copy(CDBDatabaseTable *pData)
{
	ASSERT(pData!=NULL);
	m_strTableName = pData->m_strTableName;

	m_listFields.Empty();
	int nIndex = 0,nCount = pData->m_listFields.GetCount();
	for (nIndex = 0;nIndex < nCount;nIndex++)
	{
		auto pDicItem = pData->m_listFields.GetItem(nIndex);
		if (NULL != pDicItem)
		{
			m_listFields.AddItem(pDicItem);
		}
	}
}

void CDBDatabaseTable::Serialize(CArchive& ar)
{
	CDataMid::Serialize(ar);//父类函数
	int nTagSize;
	CString strName;
	int nNameSize;

	ar.Flush();
	if (ar.IsStoring())
	{
		MySerial.SaveDataStr(ar,TABLENAME,m_strTableName);
		MySerial.SaveDataObjectList(ar,TABLELIST,&m_listFields);

		nNameSize = 8;
		strName = _T("DENDDEND");
		ar << nNameSize;
		ar << strName;
	}
	else
	{
		int nNumber=0;
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
			else if (strName == TABLENAME)
			{
				ar >>nTagSize >> m_strTableName;
			}
			else if(strName == TABLELIST)
			{
				m_listFields.Empty();
				int nDataSize;
				ar >> nTagSize;
				ar >> nDataSize;

				for(int i=0; i<nDataSize; i++)
				{
					CDBDatabaseFields *pdbDatabaseFields = new CDBDatabaseFields;
					pdbDatabaseFields->Serialize(ar);
					m_listFields.AddTail(pdbDatabaseFields);
				}
			}
			else
			{
				ar >> nTagSize;
				ar.Flush();
				char *buf = new char[nTagSize];
				ar.GetFile()->Read(buf,nTagSize);
				delete[] buf;
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

CDBDatabaseTableList::CDBDatabaseTableList()
{

}

CDBDatabaseTableList::~CDBDatabaseTableList()
{
	//Empty();
}

CDBDatabaseTable* CDBDatabaseTableList::GetItem( int nIndex )
{
	if (nIndex<0||nIndex>=GetCount())
		return NULL;
	return (CDBDatabaseTable*)GetAt(FindIndex(nIndex));
}

CDBDatabaseTable* CDBDatabaseTableList::GetItem(CString strTableName)	//根据名称获取Item
{
	ASSERT(!strTableName.IsEmpty());

	int nIndex = 0,nCount = GetCount();
	for (nIndex = 0;nIndex < nCount;nIndex++)
	{
		auto pData = GetItem(nIndex);
		if (NULL != pData)
		{
			if (pData->m_strTableName == strTableName)
			{
				return pData;
			}
		}
	}
	return NULL;
}

void CDBDatabaseTableList::AddItem(CDBDatabaseTable* pItem)	//添加Item
{
	CDBDatabaseTable*pData = new CDBDatabaseTable;
	pData->Copy(pItem);
	AddTail(pData);
}

void CDBDatabaseTableList::DeleteItem(int nIndex)			//删除固定索引Item
{
	if (nIndex<0||nIndex>GetCount())
		return;
	CDBDatabaseTable *pObject=(CDBDatabaseTable*)GetItem(nIndex);
	delete pObject;
	pObject=NULL;
	RemoveAt(FindIndex(nIndex));
}