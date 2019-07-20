#include "Stdafx.h"
#include "SpecItem.h"
#include "ClassEx/MySerial.h"


//CSpecData
IMPLEMENT_SERIAL(CSpecData,CObject,1)
CSpecData::CSpecData()
{
	m_strPartName = _T("");
	m_strPartSize = _T("");
	m_strRelSize = _T("");
	m_strRemark = _T("");
	m_nSizeType = SPECITEM_NORMAL;
}

CSpecData::~CSpecData()
{

}

void CSpecData::Copy(CSpecData *pData)
{
	ASSERT(pData);
	m_strPartName = pData->m_strPartName;
	m_strPartSize = pData->m_strPartSize;
	m_strRelSize = pData->m_strRelSize;
	m_strRemark = pData->m_strRemark;
	m_nSizeType = pData->m_nSizeType;
}

void CSpecData::Serialize(CArchive& ar)
{
	int dateSize = 0;
	int tagsize = 0;
	CString strname = _T("");
	int namesize = 0;
	ar.Flush();
	if (ar.IsStoring())
	{
		MySerial.SaveDataStr(ar,_T("PARTNAME"),m_strPartName);
		MySerial.SaveDataStr(ar,_T("PARTSIZE"),m_strPartSize);
		MySerial.SaveDataStr(ar,_T("TRELSIZE"),m_strRelSize);
		MySerial.SaveDataStr(ar,_T("THREMARK"),m_strRemark);
		MySerial.SaveDataInt(ar,_T("SIZETYPE"),m_nSizeType);
		namesize = 8;
		strname = _T("DENDDEND");
		ar << namesize;
		ar << strname;
	}
	else
	{
		int nNumber=0;
		ar >> namesize;
		ar >> strname;
		if(strname.GetLength()!=namesize)return;

		while(strname != "DENDDEND")
		{
			if(nNumber > 50)
			{
				return;
			}		
			if(strname == _T("PARTNAME"))
			{
				ar >> tagsize >> m_strPartName;
			}
			else if(strname == _T("PARTSIZE"))
			{
				ar >> tagsize >> m_strPartSize;
			}
			else if(strname == _T("TRELSIZE"))
			{
				ar >> tagsize >> m_strRelSize;
			}
			else if (strname == _T("THREMARK"))
			{
				ar >> tagsize >> m_strRemark;
			}
			else if (strname == _T("SIZETYPE"))
			{
				ar >> tagsize >> m_nSizeType;
			}
			else
			{
				ar >> tagsize;
				ar.Flush();
				ar.GetFile()->Seek( tagsize, CFile::current);
			}
			strname = _T("");
			ar >> namesize;
			ar >> strname;
			if(strname.GetLength()!=namesize)
				return;
			nNumber++;
		}
	}
}

//CSpecDataList
IMPLEMENT_SERIAL(CSpecDataList,CObList,1)
CSpecDataList::CSpecDataList()
{

}
CSpecDataList:: ~CSpecDataList()
{
	Empty();
}

CSpecData* CSpecDataList::GetItem(int nIndex)
{
	if(nIndex<0||nIndex>=GetCount())
		return NULL;

	return (CSpecData*)GetAt(FindIndex(nIndex));
}

CSpecData* CSpecDataList::GetItemByPartName(CString strPartName)
{
	for(int i=0; i<GetCount(); i++)
	{
		CSpecData *pObject = GetItem(i);
		if(pObject->m_strPartName == strPartName)
			return pObject;
	}

	return NULL;
}

void CSpecDataList::Copy(CSpecDataList *pDataList)
{
	Empty();
	int ncount = pDataList->GetCount();
	for(int i=0; i<ncount; i++)
	{
		CSpecData *pData = pDataList->GetItem(i);
		CSpecData *pNewData = new CSpecData;
		pNewData->Copy(pData);
		AddTail((CObject *)pNewData);
	}
}

void CSpecDataList::Serialize(CArchive& ar)
{
	int dateSize = 0;
	int tagsize = 0;
	CString strname = _T("");
	int namesize = 0;
	ar.Flush();
	if (ar.IsStoring())
	{
		MySerial.SaveDataObjectList(ar,_T("SPDALIST"),this);

		namesize = 8;
		strname = _T("DENDDEND");
		ar << namesize;
		ar << strname;
	}
	else
	{
		int nNumber=0;
		ar >> namesize;
		ar >> strname;
		if(strname.GetLength()!=namesize)return;

		while(strname != "DENDDEND")
		{
			if(nNumber > 150)
			{
				return;
			}		
			if(strname == _T("SPDALIST"))
			{
				Empty();
				int dateSize;
				ar >> tagsize;
				ar >> dateSize;

				for(int i=0; i<dateSize; i++)
				{
					CObject  *pObject = new CSpecData;
					pObject->Serialize(ar);
					AddTail((CObject *)pObject);
				}
			}		
			else
			{
				ar >> tagsize;
				ar.Flush();
				ar.GetFile()->Seek( tagsize, CFile::current);
			}
			strname = _T("");
			ar >> namesize;
			ar >> strname;
			if(strname.GetLength()!=namesize)
				return;
			nNumber++;
		}
	}
}

void CSpecDataList::Empty()
{
	for (int j=(GetCount()-1);j>=0;j--)
	{
		CSpecData *pData =(CSpecData *)GetAt(FindIndex(j));
		if (pData)
		{
			delete pData;
			pData = NULL;
		}
	}

	RemoveAll();
}

void CSpecDataList::AddItem( CSpecData* pItem )
{
	CSpecData*pData=new CSpecData;
	pData->Copy(pItem);
	AddTail(pData);
}

void CSpecDataList::DeleteItem( int nIndex )
{
	if (nIndex<0||nIndex>GetCount())
		return;
	CSpecData *pObject=(CSpecData*)GetItem(nIndex);
	delete pObject;
	pObject=NULL;
	RemoveAt(FindIndex(nIndex));
}

//CSpecItem
IMPLEMENT_SERIAL(CSpecItem,CObject,1)
CSpecItem::CSpecItem()
{
	m_strSpecName = _T("");
	m_nBaseSpec = 0;
}


CSpecItem::~CSpecItem()
{
}

void CSpecItem::Copy(CSpecItem *pItem)
{
	ASSERT(pItem);
	m_strSpecName = pItem->m_strSpecName;
	m_nBaseSpec = pItem->m_nBaseSpec;
	m_listSpecData.Copy(&pItem->m_listSpecData);
}

void CSpecItem::Serialize(CArchive& ar)
{
	int dateSize = 0;
	int tagsize = 0;
	CString strname = _T("");
	int namesize = 0;
	ar.Flush();
	if (ar.IsStoring())
	{
		MySerial.SaveDataStr(ar,_T("SPECNAME"),m_strSpecName);
		MySerial.SaveDataInt(ar,_T("SPECBASE"),m_nBaseSpec);
		MySerial.SaveDataObjectList(ar,_T("SCPTLIST"),&m_listSpecData);

		namesize = 8;
		strname = _T("DENDDEND");
		ar << namesize;
		ar << strname;
	}
	else
	{
		int nNumber=0;
		ar >> namesize;
		ar >> strname;
		if(strname.GetLength()!=namesize)return;

		while(strname != "DENDDEND")
		{
			if(nNumber > 100)
			{
				return;
			}		
			if(strname == _T("SPECNAME"))
			{
				ar >> tagsize >> m_strSpecName;
			}
			else if(strname == _T("SPECBASE"))
			{
				ar >> tagsize >> m_nBaseSpec;
			}
			else if(strname == _T("SCPTLIST"))
			{
				int dateSize = 0;
				ar >> tagsize;
				ar >> dateSize;
				for(int i=0; i<dateSize; i++)
				{
					CSpecData* pData = new CSpecData;
					pData->Serialize(ar);
					m_listSpecData.AddTail(pData);
				}
			}		
			else
			{
				ar >> tagsize;
				ar.Flush();
				ar.GetFile()->Seek( tagsize, CFile::current);
			}
			strname = _T("");
			ar >> namesize;
			ar >> strname;
			if(strname.GetLength()!=namesize)
				return;
			nNumber++;
		}
	}
}

//CSpecItemList
IMPLEMENT_SERIAL(CSpecItemList,CObList,1)
CSpecItemList::CSpecItemList()
{

}

CSpecItemList::~CSpecItemList()
{
	Empty();
}

void CSpecItemList::Copy(CSpecItemList *pItemList)
{
	Empty();
	int ncount = pItemList->GetCount();
	for(int i=0; i<ncount; i++)
	{
		CSpecItem *pItem =(CSpecItem *)pItemList->GetItem(i);
		if(pItem==NULL)break;
		CSpecItem *pNewItem = new CSpecItem;
		pNewItem->Copy(pItem);
		AddTail((CObject *)pNewItem);
	}
}

CSpecItem* CSpecItemList::GetItem(int nIndex)
{
	if(nIndex<0||nIndex>=GetCount())
		return NULL;

	return (CSpecItem*)GetAt(FindIndex(nIndex));
}

void CSpecItemList::Serialize(CArchive& ar)
{
	int dateSize = 0;
	int tagsize = 0;
	CString strname = _T("");
	int namesize = 0;
	ar.Flush();
	if (ar.IsStoring())
	{
		MySerial.SaveDataObjectList(ar,_T("SPIMLIST"),this);

		namesize = 8;
		strname = _T("DENDDEND");
		ar << namesize;
		ar << strname;
	}
	else
	{
		int nNumber=0;
		ar >> namesize;
		ar >> strname;
		if(strname.GetLength()!=namesize)return;

		while(strname != "DENDDEND")
		{
			if(nNumber > 150)
			{
				return;
			}		
			if(strname == _T("SPIMLIST"))
			{
				Empty();
				int dateSize;
				ar >> tagsize;
				ar >> dateSize;

				for(int i=0; i<dateSize; i++)
				{
					CObject  *pObject = new CSpecItem;
					pObject->Serialize(ar);
					AddTail((CObject *)pObject);
				}
			}		
			else
			{
				ar >> tagsize;
				ar.Flush();
				ar.GetFile()->Seek( tagsize, CFile::current);
			}
			strname = _T("");
			ar >> namesize;
			ar >> strname;
			if(strname.GetLength()!=namesize)
				return;
			nNumber++;
		}
	}
}

void CSpecItemList::Empty()
{
	for (int j=(GetCount()-1);j>=0;j--)
	{
		CSpecItem *pItem =(CSpecItem *)GetAt(FindIndex(j));
		if (pItem)
		{
			delete pItem;
			pItem = NULL;
		}	
	}

	RemoveAll();
}

CSpecItem* CSpecItemList::GetItemBySpecName(CString strSpecName)
{
	for(int i=0; i<GetCount(); i++)
	{
		CSpecItem *pObject = GetItem(i);
		if(pObject->m_strSpecName == strSpecName)
			return pObject;
	}

	return NULL;
}

BOOL CSpecItemList::OnWriteFile(CString strFilePath,BOOL bDelOldFile)
{
	BOOL bRet = TRUE;

	if (strFilePath.IsEmpty()||this == NULL)
	{
		bRet = FALSE;
	}
	else
	{
		if (bDelOldFile)
		{
			DeleteFile(strFilePath);
		}
		
		//写
		CFile mFile;	
		try
		{
			if (mFile.Open (strFilePath,CFile::modeCreate|CFile::modeWrite))
			{
				CArchive saveArchive(&mFile, CArchive::store);
				this->Serialize(saveArchive);
				saveArchive.Close();
				mFile.Close();
			}
			else
			{
				bRet = FALSE;
			}
		}
		catch( CException* e )
		{
         auto s = e->GetRuntimeClass();
			AfxMessageBox(strFilePath+_T("  写文件出现问题"));
		}//写_end
	}

	return bRet;
}

BOOL CSpecItemList::OnReadFile(CString strFilePath,BOOL bDelFile)
{
	BOOL bRet = TRUE;

	if (strFilePath.IsEmpty()||this == NULL)
	{
		bRet = FALSE;
	}
	else
	{
		//读
		CFile mFile;
		try
		{
			if(mFile.Open(strFilePath,CFile::modeRead))
			{
				this->Empty();
				CArchive loadArchive(&mFile, CArchive::load);
				loadArchive.m_bForceFlat = FALSE;
				if (mFile.GetLength() != 0)
				{
					this->Serialize(loadArchive);
					loadArchive.Close();
				}
				mFile.Close();	

				if (bDelFile)
				{
					DeleteFile(strFilePath);
				}
			}
			else
			{
				bRet = FALSE;
			}
		}
		catch( CException* e )
		{
			TCHAR   szError[1024];   
			e->GetErrorMessage(szError,1024);
		}//读_end
	}

	return bRet;
}

void CSpecItemList::AddItem( CSpecItem *pItem )
{
	CSpecItem *pData = new CSpecItem;
	pData->Copy(pItem);
	AddTail(pData);
}

void CSpecItemList::DeleteItem( int nIndex )
{
	if (nIndex<0||nIndex>GetCount())
		return;
	CSpecItem *pObject=(CSpecItem*)GetItem(nIndex);
	delete pObject;
	pObject=NULL;
	RemoveAt(FindIndex(nIndex));
}

CSpecItem* CSpecItemList::GetBaseItem()
{
	for(int i=0; i<GetCount(); i++)
	{
		CSpecItem *pObject = GetItem(i);
		if(1 == pObject->m_nBaseSpec)
			return pObject;
	}

	return NULL;
}

int CSpecItemList::GetIndexBySpecName( CString strSpecName )
{
	for(int i=0; i<GetCount(); i++)
	{
		CSpecItem *pObject = GetItem(i);
		if(pObject->m_strSpecName == strSpecName)
			return i;
	}

	return -1;
}
