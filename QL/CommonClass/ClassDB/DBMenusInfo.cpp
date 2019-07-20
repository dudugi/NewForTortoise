#include "StdAfx.h"
#include "DBMenusInfo.h"

IMPLEMENT_SERIAL(CDBMenusInfo,  CDataMid, 1)
IMPLEMENT_SERIAL(CDBMenusInfoList,  CDataListMid, 1)

std::shared_ptr<CDBMenusInfo> CDBMenusInfo::sm_inst;
std::shared_ptr<CDBMenusInfoList> CDBMenusInfoList::sm_inst;

CDBMenusInfo::CDBMenusInfo()
{
	ResetData();
}

CDBMenusInfo::~CDBMenusInfo(void)
{
}

void CDBMenusInfo::ResetData()
{
	m_nAutoID = -1;
	m_nID = -1;
	m_nPID = -1;
	m_nSortID = -1;
	m_strItemName = _T("");
	m_nShowLeft = -1;
	m_nLeftImg = -1;
	m_nImgIndex = -1;
	m_nImgCate = -1;
	m_strFrmName = _T("");
	m_strDllName = _T("");
	m_strItemShow = _T("");
   m_dwBKColor = RGB(0,0,0);
	SetDataType(DAT_MENUS);
}

void CDBMenusInfo::Copy( CDBMenusInfo *pData )
{
	ASSERT(pData != NULL);
	CDataMid::Copy(pData);

	m_nAutoID = pData->m_nAutoID;
	m_nID = pData->m_nID;
	m_nPID = pData->m_nPID;
	m_nSortID = pData->m_nSortID;
	m_strItemName = pData->m_strItemName;
	m_nShowLeft = pData->m_nShowLeft;
	m_nLeftImg = pData->m_nLeftImg;
	m_nImgIndex = pData->m_nImgIndex;
	m_nImgCate = pData->m_nImgCate;
	m_strFrmName = pData->m_strFrmName;
	m_strDllName = pData->m_strDllName;
	m_strItemShow = pData->m_strItemShow;
   m_dwBKColor = pData->m_dwBKColor;
}

void CDBMenusInfo::Serialize( CArchive& ar )
{
	CDataMid::Serialize(ar);//父类函数

	int nTagSize = 0;
	CString strName;
	int nNameSize = 0;

	ar.Flush();
	if (ar.IsStoring())
	{
		/*MySerial.SaveDataInt64(ar,_T("CODECOID"),m_nCodeID);
		MySerial.SaveDataStr(ar,_T("CODECKEY"),m_strCodeKey);
		MySerial.SaveDataStr(ar,_T("CODENAME"),m_strCodeName);
		MySerial.SaveDataStr(ar,_T("COPERFIX"),m_strCodePrefix);
		MySerial.SaveDataStr(ar,_T("YEARTYPE"),m_strCodeYearType);
		MySerial.SaveDataInt(ar,_T("SERICOUN"),m_nCodeSerialCount);
		MySerial.SaveDataStr(ar,_T("COSUFFIX"),m_strCodeSuffix);
		MySerial.SaveDataInt(ar,_T("POSITION"),m_nCodeSerialPosition);
		MySerial.SaveDataInt(ar,_T("DESIGNLE"),m_nDesignLength);
		MySerial.SaveDataStr(ar,_T("CODESORT"),m_strCodeSort);*/
		MySerial.SaveDataInt(ar,_T("ITEMIDEN"),m_nID);
		MySerial.SaveDataStr(ar,_T("ITEMNAME"),m_strItemName);

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
			/*else if (strName == _T("CODECOID"))
			{
				ar >>nTagSize >> m_nCodeID;
			}
			else if (strName == _T("CODECKEY"))
			{
				ar >>nTagSize >> m_strCodeKey;
			}
			else if (strName == _T("CODENAME"))
			{
				ar >>nTagSize >> m_strCodeName;
			}
			else if (strName == _T("COPERFIX"))
			{
				ar >>nTagSize >> m_strCodePrefix;
			}
			else if (strName == _T("YEARTYPE"))
			{
				ar >>nTagSize >> m_strCodeYearType;
			}
			else if (strName == _T("SERICOUN"))
			{
				ar >>nTagSize >> m_nCodeSerialCount;
			}
			else if (strName == _T("COSUFFIX"))
			{
				ar >>nTagSize >> m_strCodeSuffix;
			}
			else if (strName == _T("POSITION"))
			{
				ar >>nTagSize >> m_nCodeSerialPosition;
			}
			else if (strName == _T("DESIGNLE"))
			{
				ar >>nTagSize >> m_nDesignLength;
			}
			else if (strName == _T("CODESORT"))
			{
				ar >> nTagSize >> m_strCodeSort;
			}*/
			else if (strName == _T("ITEMIDEN"))
			{
				ar >> nTagSize >> m_nID;
			}
			else if (strName == _T("ITEMNAME"))
			{
				ar >> nTagSize >> m_strItemName;
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

BOOL CDBMenusInfo::GetAllDBInfo(CADOConn *pADOConn)
{
	ASSERT(NULL != pADOConn);

	BOOL bRet = TRUE;

	if (NULL == pADOConn)
	{
		bRet = FALSE;
	}
	else
	{
		m_nAutoID = pADOConn->GetValueInt(DBMenus_key_AutoID);
		m_nID = pADOConn->GetValueInt(DBMenus_key_ID);
		m_nPID = pADOConn->GetValueInt(DBMenus_key_PID);
		m_nSortID = pADOConn->GetValueInt(DBMenus_key_SortID);
		m_strItemName = pADOConn->GetValueString(DBMenus_key_ItemName);
		m_nShowLeft = pADOConn->GetValueInt(DBMenus_key_ShowLeft);
		m_nLeftImg = pADOConn->GetValueInt(DBMenus_key_LeftImg);
		m_nImgIndex = pADOConn->GetValueInt(DBMenus_key_ImgIndex);
		m_nImgCate = pADOConn->GetValueInt(DBMenus_key_ImgCate);
		m_strFrmName = pADOConn->GetValueString(DBMenus_key_FrmName);
		m_strDllName = pADOConn->GetValueString(DBMenus_key_DllName);
		m_strItemShow = pADOConn->GetValueString(DBMenus_key_ItemShow);
      m_dwBKColor = (COLORREF)pADOConn->GetValueInt64(DBMenus_key_dwTitleBKColor);

		bRet = TRUE;
	}

	return bRet;
}

BOOL CDBMenusInfo::InsertAllDBInfo(CADOConn *pADOConn)
{
	ASSERT(NULL != pADOConn);
	CString strSQL = _T(""),strKey = _T(""),strValue = _T("");
	//插入一条记录进去
	
	//                1  2  3  4  5  6  7  8  9  10
	strKey.Format(_T("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s")
					 ,DBMenus_key_ID			//1
					 ,DBMenus_key_PID			//2
					 ,DBMenus_key_SortID		//3
					 ,DBMenus_key_ItemName		//4
					 ,DBMenus_key_ShowLeft		//5
					 ,DBMenus_key_LeftImg		//6
					 ,DBMenus_key_ImgIndex		//7
					 ,DBMenus_key_ImgCate		//8
					 ,DBMenus_key_FrmName		//9
					 ,DBMenus_key_DllName		//10
					 ,DBMenus_key_ItemShow		//11
                ,DBMenus_key_dwTitleBKColor//12
					 );
	//                   1    2    3    4    5    6    7    8    9    10
	strValue.Format(_T("'%d','%d','%d','%s','%d','%d','%d','%d','%s','%s','%s',%lu")
		,m_nID				//1  ****
		,m_nPID				//2  ****
		,m_nSortID			//3  ****
		,m_strItemName		//4  
		,m_nShowLeft		//5  ****
		,m_nLeftImg			//6  ****
		,m_nImgIndex		//7  ****
		,m_nImgCate			//8  ****
		,m_strFrmName		//9  
		,m_strDllName		//10 
		,m_strItemShow		//11 
      ,m_dwBKColor      //12
		);

	strSQL.Format(_T("insert into %s(%s) \
					 values(%s)")
					 ,DB_TABLE_MENUS
					 ,strKey
					 ,strValue
					);

	BOOL bRet = pADOConn->ExecuteSQL(strSQL);

	return bRet;
}

BOOL CDBMenusInfo::DelAllDBInfoByID(CADOConn *pADOConn)
{
	ASSERT(NULL != pADOConn);

	BOOL bRet = FALSE;
	if ( (NULL == pADOConn) || (m_nID < 0))
	{
		bRet = FALSE;
	}
	else
	{
		CString strSQL = _T("");
		strSQL.Format(_T("delete from %s where %s = '%d'"),DB_TABLE_MENUS,DBMenus_key_ID,m_nID);

		bRet = pADOConn->ExecuteSQL(strSQL);
	}
	
	return bRet;
}

BOOL CDBMenusInfo::UpdateAllDBInfoByID( CADOConn *pADOConn )
{
	ASSERT(NULL != pADOConn);
	BOOL bRet = FALSE;
	if ( (NULL == pADOConn) || (m_nID < 0))
	{
		bRet = FALSE;
	}
	else
	{
		CString strSQL = _T("");
		//                              1         2         3         4         5         6         7         8         9         10			  11
		strSQL.Format(_T("update %s set %s = '%d',%s = '%d',%s = '%s',%s = '%d',%s = '%d',%s = '%d',%s = '%d',%s = '%s',%s = '%s',%s = '%s',%s = %lu where %s = '%d'"),\
			DB_TABLE_MENUS,
			DBMenus_key_PID,m_nPID,				//1
			DBMenus_key_SortID,m_nSortID,		//2
			DBMenus_key_ItemName,m_strItemName,	//3
			DBMenus_key_ShowLeft,m_nShowLeft,	//4
			DBMenus_key_LeftImg,m_nLeftImg,		//5
			DBMenus_key_ImgIndex,m_nImgIndex,	//6
			DBMenus_key_ImgCate,m_nImgCate,		//7
			DBMenus_key_FrmName,m_strFrmName,	//8
			DBMenus_key_DllName,m_strDllName,	//9
			DBMenus_key_ItemShow,m_strItemShow, //10
         DBMenus_key_dwTitleBKColor,m_dwBKColor,//11
			DBMenus_key_ID,m_nID				//12
			);

		bRet = pADOConn->ExecuteSQL(strSQL);
	}

	return bRet;
}

void CDBMenusInfo::Swap(CDBMenusInfo *pData)
{
	CDBMenusInfo tmpData;
	tmpData.Copy(this);
	Copy(pData);
	pData->Copy(&tmpData);
}

CDBMenusInfo * CDBMenusInfo::Instance()
{
	if(sm_inst.get() == 0)
		sm_inst = shared_ptr<CDBMenusInfo>(new CDBMenusInfo);

	return sm_inst.get();
}


///////////////////////
CDBMenusInfoList::CDBMenusInfoList()
{
	ResetData();
}

CDBMenusInfoList::~CDBMenusInfoList()
{

}

void CDBMenusInfoList::ResetData()
{
	m_nParentCount = 0;
	m_nChildCount = 0;
}

CDBMenusInfo* CDBMenusInfoList::GetItem( int nIndex )
{
	if (nIndex<0||nIndex>=GetCount())
		return NULL;
	return (CDBMenusInfo*)GetAt(FindIndex(nIndex));
}

CDBMenusInfo* CDBMenusInfoList::GetItemByID(int nID)
{
	CDBMenusInfo * pItem = NULL;

	if (nID>-1)
	{
		for(int i=0;i< GetCount();i++)
		{
			CDBMenusInfo * pObject = GetItem(i);
			if(nID==pObject->m_nID)
			{
				pItem = pObject;
				break;
			}
		}
	}

	return pItem;
}

int CDBMenusInfoList::GetIndexByID(int nID)
{
	int nSel = -1;
	if (nID>-1)
	{
		for(int i=0;i< GetCount();i++)
		{
			CDBMenusInfo * pObject = GetItem(i);
			if(nID==pObject->m_nID)
			{
				nSel = i;
				break;
			}
		}
	}

	return nSel;
}

CDBMenusInfo* CDBMenusInfoList::GetItemByItemName(CString strItemName)
{
	CDBMenusInfo * pItem = NULL;

	strItemName.Trim();
	if (!strItemName.IsEmpty())
	{
		for(int i=0;i< GetCount();i++)
		{
			CDBMenusInfo * pObject = GetItem(i);
			if(strItemName==pObject->m_strItemName)
			{
				pItem = pObject;
				break;
			}
		}
	}

	return pItem;
}


void CDBMenusInfoList::AddItem( CDBMenusInfo* pItem )
{
	CDBMenusInfo*pData = new CDBMenusInfo;
	pData->Copy(pItem);
	AddTail(pData);
}

void CDBMenusInfoList::DeleteItem( int nIndex )
{
	if (nIndex<0||nIndex>GetCount())
		return;
	CDBMenusInfo *pObject=(CDBMenusInfo*)GetItem(nIndex);
	delete pObject;
	pObject=NULL;
	RemoveAt(FindIndex(nIndex));
}

void CDBMenusInfoList::GetListFromDB(CADOConn *pADOConn)
{
	ASSERT(pADOConn != NULL);
	Empty();
	ResetData();
	CString strSQL = _T("");
	strSQL.Format(_T("select * from %s order by PID,SortID"),DB_TABLE_MENUS);

	pADOConn->GetRecordSet(strSQL);
	while (!pADOConn->adoEOF())
	{
		CDBMenusInfo oData;
		if(oData.GetAllDBInfo(pADOConn))
		{
			if (oData.m_nPID == 0)
			{
				m_nParentCount++;
			}
			else
			{
				m_nChildCount++;
			}

			AddItem(&oData);
		}
		pADOConn->MoveNext();
	}
}

int CDBMenusInfoList::GetParentCount()
{
	return m_nParentCount;
}

int CDBMenusInfoList::GetChildCount()
{
	return m_nChildCount;
}


CDBMenusInfoList * CDBMenusInfoList::Instance()
{
	if(sm_inst.get() == 0)
		sm_inst = shared_ptr<CDBMenusInfoList>(new CDBMenusInfoList);

	return sm_inst.get();
}

void CDBMenusInfoList::Serialize(CArchive& ar)
{
	//不需调用基类Serialize

	int nTagSize = 0;
	CString strName;
	int nNameSize;

	ar.Flush();
	if (ar.IsStoring())
	{
		MySerial.SaveDataObjectList(ar,_T("MENULIST"),this);

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
			else if (strName == _T("MENULIST"))
			{
				Empty();
				int dateSize;
				ar >> nTagSize;
				ar >> dateSize;
				for(int i=0; i<dateSize; i++)
				{
					CObject  *pObject = new CDBMenusInfo;
					pObject->Serialize(ar);
					AddTail((CObject *)pObject);
				}
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