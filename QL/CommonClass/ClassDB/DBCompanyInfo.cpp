#include "StdAfx.h"
#include "DBCompanyInfo.h"
#include "ADOConn\DBImage.h"

IMPLEMENT_SERIAL(CDBCompanyInfo,  CDataMid, 1)
IMPLEMENT_SERIAL(CDBCompanyInfoList,  CDataListMid, 1)

std::shared_ptr<CDBCompanyInfo> CDBCompanyInfo::sm_inst;
std::shared_ptr<CDBCompanyInfoList> CDBCompanyInfoList::sm_inst;

CDBCompanyInfo::CDBCompanyInfo(void)
{
#if COMPANYSIGN_IMAGE
	m_pCompanySign = NULL;
#endif // COMPANYSIGN_IMAGE
	ResetData(); 
}


CDBCompanyInfo::~CDBCompanyInfo(void)
{
#if COMPANYSIGN_IMAGE
	ClearCompanySignImage();
#endif // COMPANYSIGN_IMAGE
}

void CDBCompanyInfo::ResetData()
{
	m_nID = -1;
	m_strCompanyName = _T("");
	m_strCompanyTel = _T("");
	m_strCompanyFax = _T("");
	m_strCompanyAddress = _T("");
#if COMPANYSIGN_IMAGE
	ClearCompanySignImage();
#endif // COMPANYSIGN_IMAGE

	SetDataType(DAT_COMPANY_INFO);
}


#if COMPANYSIGN_IMAGE
void CDBCompanyInfo::ClearCompanySignImage()
{
	if (NULL != m_pCompanySign)
	{
		delete m_pCompanySign;
		m_pCompanySign = NULL;
	}
}
#endif // COMPANYSIGN_IMAGE

void CDBCompanyInfo::Copy( CDBCompanyInfo *pData )
{
	ASSERT(pData != NULL);
	CDataMid::Copy(pData);
	m_nID = pData->m_nID;
	m_strCompanyName = pData->m_strCompanyName;
	m_strCompanyTel = pData->m_strCompanyTel;
	m_strCompanyFax = pData->m_strCompanyFax;
	m_strCompanyAddress = pData->m_strCompanyAddress;
#if COMPANYSIGN_IMAGE
	ClearCompanySignImage();
	if (pData->m_pCompanySign)
	{
		m_pCompanySign = pData->m_pCompanySign->Clone();
	}
#endif
}


BOOL CDBCompanyInfo::GetAllDBInfo(CADOConn *pADOConn)		//获取公司【整条】信息
{
	ASSERT(pADOConn != NULL);

	BOOL bRet = TRUE;

	if (NULL == pADOConn)
	{
		bRet = FALSE;
	}
	else
	{
		m_nID						= pADOConn->GetValueInt(DBCompanyInfo_key_Id);
		m_strCompanyName			= pADOConn->GetValueString(DBCompanyInfo_key_Name);
		m_strCompanyTel				= pADOConn->GetValueString(DBCompanyInfo_key_Tel);
		m_strCompanyFax				= pADOConn->GetValueString(DBCompanyInfo_key_Fax);
		m_strCompanyAddress			= pADOConn->GetValueString(DBCompanyInfo_key_Address);
#if COMPANYSIGN_IMAGE
		ClearCompanySignImage();
		CDBImage oImage;
		m_pCompanySign = oImage.NewImageFromDB(DBCompanyInfo_key_Sign,pADOConn->GetRecoPtr());

#endif // COMPANYSIGN_IMAGE

		bRet = TRUE;
	}

	return bRet;
}

void CDBCompanyInfo::Serialize( CArchive& ar )
{
	CDataMid::Serialize(ar);//父类函数

	int nTagSize = 0;
	CString strName;
	int nNameSize = 0;

	ar.Flush();
	if (ar.IsStoring())
	{
		MySerial.SaveDataInt(ar, _T("COMPANID"), m_nID);
		MySerial.SaveDataStr(ar, _T("COMYNAME"), m_strCompanyName);
		MySerial.SaveDataStr(ar, _T("COMYTELE"), m_strCompanyTel);
		MySerial.SaveDataStr(ar, _T("COMAYFAX"), m_strCompanyFax);
		MySerial.SaveDataStr(ar, _T("COMYADDR"), m_strCompanyAddress);

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
			else if(strName == _T("COMPANID"))
			{
				ar >>nTagSize >> m_nID;
			}
			else if (strName == _T("COMYNAME"))
			{
				ar >>nTagSize >> m_strCompanyName;
			}
			else if (strName == _T("COMYTELE"))
			{
				ar >>nTagSize >> m_strCompanyTel;
			}
			else if (strName == _T("COMAYFAX"))
			{
				ar >>nTagSize >> m_strCompanyFax;
			}
			else if (strName == _T("COMYADDR"))
			{
				ar >>nTagSize >> m_strCompanyAddress;
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


void CDBCompanyInfo::Trim()
{
	m_strCompanyName.Trim();
	m_strCompanyTel.Trim();
	m_strCompanyFax.Trim();
	m_strCompanyAddress.Trim();
}

BOOL CDBCompanyInfo::InsertAllDBInfo( CADOConn *pADOConn )
{
	ASSERT(pADOConn != NULL);

	BOOL bRet = TRUE;

	CString strSQL = _T(""),strFormat = _T(""),strValue = _T("");
	strFormat.Format(_T("%s,%s,%s,%s"),
		DBCompanyInfo_key_Name		,//1
		DBCompanyInfo_key_Tel		,//2
		DBCompanyInfo_key_Fax		,//3
		DBCompanyInfo_key_Address
		);
	//					1 ,2   ,3   ,4  
	strValue.Format(_T("'%s','%s','%s','%s'"),
		m_strCompanyName		,//1
		m_strCompanyTel			,//2
		m_strCompanyFax			,//3
		m_strCompanyAddress		//4
		);

	strSQL.Format(_T("insert into %s (%s) values(%s)"),DB_TABLE_COMPANY_INFO,strFormat,strValue);

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

BOOL CDBCompanyInfo::UpdateAllDBInfo(CADOConn *pADOConn)
{
	ASSERT(pADOConn != NULL);

	BOOL bRet = TRUE;

	CString strSQL = _T("");
	strSQL.Format(_T("update %s set %s = '%s' ,%s = '%s', %s = '%s',%s = '%s' "), DB_TABLE_COMPANY_INFO, \
					DBCompanyInfo_key_Name, m_strCompanyName,DBCompanyInfo_key_Tel, m_strCompanyTel, DBCompanyInfo_key_Fax, m_strCompanyFax, \
					DBCompanyInfo_key_Address, m_strCompanyAddress);
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

BOOL CDBCompanyInfo::UpdateAllDBInfoByID(CADOConn *pADOConn)
{
	ASSERT(pADOConn != NULL);

	BOOL bRet = TRUE;

	CString strSQL = _T("");
	strSQL.Format(_T("update %s set %s = '%s' ,%s = '%s', %s = '%s',%s = '%s' where %s = '%d'"), DB_TABLE_COMPANY_INFO, \
		DBCompanyInfo_key_Name, m_strCompanyName,DBCompanyInfo_key_Tel, m_strCompanyTel, DBCompanyInfo_key_Fax, m_strCompanyFax, \
		DBCompanyInfo_key_Address, m_strCompanyAddress, DBCompanyInfo_key_Id, m_nID);
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
CDBCompanyInfo * CDBCompanyInfo::Instance()
{
	if(sm_inst.get() == 0)
		sm_inst = shared_ptr<CDBCompanyInfo>(new CDBCompanyInfo);

	return sm_inst.get();
}

///////////////////////
CDBCompanyInfoList::CDBCompanyInfoList()
{

}
CDBCompanyInfoList::~CDBCompanyInfoList()
{

}
CDBCompanyInfo* CDBCompanyInfoList::GetItem( int nIndex )
{
	if (nIndex<0||nIndex>=GetCount())
		return NULL;
	return (CDBCompanyInfo*)GetAt(FindIndex(nIndex));
}

void CDBCompanyInfoList::AddItem( CDBCompanyInfo* pItem )
{
	CDBCompanyInfo*pData = new CDBCompanyInfo;
	pData->Copy(pItem);
	AddTail(pData);
}

void CDBCompanyInfoList::DeleteItem( int nIndex )
{
	if (nIndex<0||nIndex>GetCount())
		return;
	CDBCompanyInfo *pObject=(CDBCompanyInfo*)GetItem(nIndex);
	delete pObject;
	pObject=NULL;
	RemoveAt(FindIndex(nIndex));
}


CDBCompanyInfoList * CDBCompanyInfoList::Instance()
{
	if(sm_inst.get() == 0)
		sm_inst = shared_ptr<CDBCompanyInfoList>(new CDBCompanyInfoList);

	return sm_inst.get();
}

void CDBCompanyInfoList::Serialize(CArchive& ar)
{
	//不需调用基类Serialize

	int nTagSize = 0;
	CString strName;
	int nNameSize;

	ar.Flush();
	if (ar.IsStoring())
	{
		MySerial.SaveDataObjectList(ar,_T("COMYINFO"),this);

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
			else if (strName == _T("COMYINFO"))
			{
				Empty();
				int dateSize;
				ar >> nTagSize;
				ar >> dateSize;
				for(int i=0; i<dateSize; i++)
				{
					CObject  *pObject = new CDBCompanyInfo;
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

void CDBCompanyInfoList::GetListFromDB(CADOConn *pADOConn)
{
	ASSERT(pADOConn != NULL);

	Empty();
	CString strSQL = _T("");
	strSQL.Format(_T("select * from %s"),DB_TABLE_COMPANY_INFO);

	pADOConn->GetRecordSet(strSQL);
	while (!pADOConn->adoEOF())
	{
		CDBCompanyInfo oData;
		oData.GetAllDBInfo(pADOConn);
		AddItem(&oData);
		pADOConn->MoveNext();
	}
}