#include "StdAfx.h"
#include "ConfigInfo.h"

IMPLEMENT_SERIAL(CConfigInfo,  CDataMid, 1)
	IMPLEMENT_SERIAL(CConfigInfoList,  CDataListMid, 1)


	CConfigInfo::CConfigInfo(void)
{
	ResetData();
}


CConfigInfo::~CConfigInfo(void)
{
}

void CConfigInfo::ResetData()
{
	m_strUserDefinedName = _T("");
	m_strUserID = _T("");
	m_strUserPassword = _T("");
	m_bRememberPassword = FALSE;
	m_bAutomaticLogon = FALSE;
	m_strIPAddress = _T("");
	m_strPort1 = _T("");
	m_strPort2 = _T("");
	m_strDatabaseName = _T("");
	m_strDatabaseAccount = _T("");
	m_strDatabasePassword = _T("");
	m_bApplyAccount = FALSE;
   m_strFtpIP     = _T("");
   m_bHttpMode = FALSE;
}

void CConfigInfo::Serialize( CArchive& ar )
{
	CDataMid::Serialize(ar);//父类函数

	int nTagSize = 0;
	CString strName;
	int nNameSize = 0;

	ar.Flush();
	if (ar.IsStoring())
	{
		MySerial.SaveDataStr(ar,_T("USERDEFI"),m_strUserDefinedName);
		MySerial.SaveDataStr(ar,_T("USERNAME"),m_strUserID);
		MySerial.SaveDataStr(ar,_T("USERPWSD"),m_strUserPassword);
		MySerial.SaveDataInt(ar,_T("REMEPWSD"),m_bRememberPassword);
		MySerial.SaveDataInt(ar,_T("AUTOLOGO"),m_bAutomaticLogon);
		MySerial.SaveDataStr(ar,_T("IPADDRES"),m_strIPAddress);
		MySerial.SaveDataStr(ar,_T("SPORTONE"),m_strPort1);
		MySerial.SaveDataStr(ar,_T("SPORTTWO"),m_strPort2);
		MySerial.SaveDataStr(ar,_T("DATANAME"),m_strDatabaseName);
		MySerial.SaveDataStr(ar,_T("DATAACCO"),m_strDatabaseAccount);
		MySerial.SaveDataStr(ar,_T("DATAPASS"),m_strDatabasePassword);
		MySerial.SaveDataInt(ar,_T("APPLYACC"),m_bApplyAccount);
      MySerial.SaveDataStr(ar,_T("FTPADDRE"),m_strFtpIP);
      MySerial.SaveDataInt(ar,_T("HTTPMODE"),m_bHttpMode);
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
			else if (strName == _T("USERDEFI"))
			{
				ar >>nTagSize >> m_strUserDefinedName;
			}
			else if (strName == _T("USERNAME"))
			{
				ar >>nTagSize >> m_strUserID;
			}
			else if (strName == _T("USERPWSD"))
			{
				ar >>nTagSize >> m_strUserPassword;
			}
			else if (strName == _T("REMEPWSD"))
			{
				ar >>nTagSize >> m_bRememberPassword;
			}
			else if (strName == _T("AUTOLOGO"))
			{
				ar >>nTagSize >> m_bAutomaticLogon;
			}
			else if (strName == _T("IPADDRES"))
			{
				ar >>nTagSize >> m_strIPAddress;
			}
			else if (strName == _T("SPORTONE"))
			{
				ar >>nTagSize >> m_strPort1;
			}
			else if (strName == _T("SPORTTWO"))
			{
				ar >>nTagSize >> m_strPort2;
			}
			else if (strName == _T("DATANAME"))
			{
				ar >>nTagSize >> m_strDatabaseName;
			}
			else if (strName == _T("DATAACCO"))
			{
				ar >>nTagSize >> m_strDatabaseAccount;
			}
			else if (strName == _T("DATAPASS"))
			{
				ar >>nTagSize >> m_strDatabasePassword;
			}
			else if (strName == _T("APPLYACC"))
			{
				ar >>nTagSize >> m_bApplyAccount;
			}
         else if (strName == _T("FTPADDRE"))
         {
            ar >>nTagSize >> m_strFtpIP;
         }
         else if (strName == _T("HTTPMODE"))
         {
            ar >>nTagSize >> m_bHttpMode;
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

void CConfigInfo::Copy( CConfigInfo *pData )
{
	ASSERT(pData != NULL);
	CDataMid::Copy(pData);

	m_strUserDefinedName = pData->m_strUserDefinedName;
	m_strUserID = pData->m_strUserID;
	m_strUserPassword = pData->m_strUserPassword;
	m_bRememberPassword = pData->m_bRememberPassword;
	m_bAutomaticLogon = pData->m_bAutomaticLogon;
	m_strIPAddress = pData->m_strIPAddress;
	m_strPort1 = pData->m_strPort1;
	m_strPort2 = pData->m_strPort2;
	m_strDatabaseName = pData->m_strDatabaseName;
	m_strDatabaseAccount = pData->m_strDatabaseAccount;
	m_strDatabasePassword = pData->m_strDatabasePassword;
	m_bApplyAccount = pData->m_bApplyAccount;
   m_strFtpIP     = pData->m_strFtpIP;
   m_bHttpMode    = pData->m_bHttpMode;
}

/////////////////////////////////////////////////////////////////////
CConfigInfoList::CConfigInfoList()
{
	
}

CConfigInfoList::~CConfigInfoList()
{

}

CConfigInfo* CConfigInfoList::GetItem( int nIndex )
{
	if (nIndex<0||nIndex>=GetCount())
		return NULL;
	return (CConfigInfo*)GetAt(FindIndex(nIndex));
}


void CConfigInfoList::AddItem(CConfigInfo* pItem)
{
	CConfigInfo *pData = new CConfigInfo;
	pData->Copy(pItem);
	AddTail(pData);
}

void CConfigInfoList::DeleteItem( int nIndex )
{
	if (nIndex<0||nIndex>GetCount())
		return;
	CConfigInfo *pObject=(CConfigInfo*)GetItem(nIndex);
	delete pObject;
	pObject=NULL;
	RemoveAt(FindIndex(nIndex));
}

void CConfigInfoList::Serialize(CArchive& ar)
{
	//不需调用基类Serialize

	int nTagSize = 0;
	CString strName;
	int nNameSize;

	ar.Flush();
	if (ar.IsStoring())
	{
		MySerial.SaveDataObjectList(ar,_T("CONGLIST"),this);

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
			else if (strName == _T("CONGLIST"))
			{
				Empty();
				int dateSize;
				ar >> nTagSize;
				ar >> dateSize;
				for(int i=0; i<dateSize; i++)
				{
					CObject  *pObject = new CConfigInfo;
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

CConfigInfo* CConfigInfoList::GetItemByIP(CString strIP)
{
	CConfigInfo * pItem = NULL;

	strIP.Trim();
	if (!strIP.IsEmpty())
	{
		for(int i=0;i< GetCount();i++)
		{
			CConfigInfo * pObject = GetItem(i);
			if(strIP==pObject->m_strIPAddress)
			{
				pItem = pObject;
				break;
			}
		}
	}

	return pItem;
}


CConfigInfo* CConfigInfoList::GetItemByApply(CString strstrUserDefinedName,CString strIPAddress,CString strDatabaseName)
{
	CConfigInfo * pItem = NULL;
	strstrUserDefinedName.Trim();
	strIPAddress.Trim();
	strDatabaseName.Trim();

	for(int i=0;i< GetCount();i++)
	{
		CConfigInfo * pObject = GetItem(i);
		if((strstrUserDefinedName == pObject->m_strUserDefinedName) && 
			(strIPAddress == pObject->m_strIPAddress) && 
			(strDatabaseName == pObject->m_strDatabaseName))
		{
			pItem = pObject;
			break;
		}
	}

	return pItem;
}

void CConfigInfoList::Copy(CConfigInfoList *pList)
{
   Empty();
   if (!pList)
   {
      return;
   }
   int iCount = pList->GetCount();
   for (int i=0;i<iCount;++i)
   {
      CConfigInfo *pItem = pList->GetItem(i);
      if (pItem)
      {
         AddItem(pItem);
      }
   }
}