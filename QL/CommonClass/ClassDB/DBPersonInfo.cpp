#include "StdAfx.h"
#include "DBPersonInfo.h"
#include "DBKeyDef.h"

IMPLEMENT_SERIAL(CDBPersonInfoData,  CDataMid, 1)
IMPLEMENT_SERIAL(CDBPersonInfoList,  CDataListMid, 1)

std::shared_ptr<CDBPersonInfoData> CDBPersonInfoData::sm_inst;
std::shared_ptr<CDBPersonInfoList> CDBPersonInfoList::sm_inst;

CDBPersonInfoData::CDBPersonInfoData()
{
	ResetData();
} 

CDBPersonInfoData::~CDBPersonInfoData()
{
}

void CDBPersonInfoData::operator=( CDBPersonInfoData *pData )
{
	Copy(pData);
}

BOOL CDBPersonInfoData::HasWebPermission(long nWebPermission) const
{
   return HasWebPermission(m_dwAttriEx,nWebPermission);
}

BOOL CDBPersonInfoData::HasWebPermission(const DWORD & dwAttri,long nWebPermission)
{
   long lWebPermission = nWebPermission & PERSON_ATTRI_WEB_AND;
   return (dwAttri & lWebPermission) != PERSON_ATTRI_NONE;
}

BOOL CDBPersonInfoData::HasTagPermission(const DWORD & dwAttri,long nPermission)
{
   long lPermission = nPermission & PERSON_TAG_PERMISSON_ALL;
   return (dwAttri & lPermission) != PERSON_ATTRI_NONE;
}

BOOL CDBPersonInfoData::HasFilePermission(const DWORD & dwAttri,long nPermission)
{
   long lPermission = nPermission & PERSON_FILE_PERMISSON_ALL;
   return (dwAttri & lPermission) != PERSON_ATTRI_NONE;
}

CDBPersonInfoData * CDBPersonInfoData::Instance()
{
	if(sm_inst.get() == 0)
		sm_inst = shared_ptr<CDBPersonInfoData>(new CDBPersonInfoData);
	return sm_inst.get();
}

void CDBPersonInfoData::ResetData()
{
	m_nID = -1;
	m_strTreeCode = _T("");
	m_strUserID = _T("");
	m_strUserPwd = _T("");
	m_strUserName = _T("");
	m_strUserPower = _T("");
	m_strUserTel = _T("");
	m_tUserDate = COleDateTime::GetCurrentTime();
	m_tUserBorn = COleDateTime::GetCurrentTime();
	m_strUserMemo = _T("");
	m_strUserSFZ = _T("");
	//Photo
	m_strUserSale = _T("");
	m_strUserDuty = _T("");
	m_strAddr = _T("");
	m_tInTime = COleDateTime::GetCurrentTime();
	m_tOutTime = COleDateTime::GetCurrentTime();
	m_nOutFlag = 0;
	m_nPermission = PS_ADMIN_ALL;

   m_dwAttriEx		= PERSON_ATTRI_NONE;
   m_iSalesman = 0;
   m_strUserControlsPermission = _T("");

   m_dwTagPermission    = PERSON_ATTRI_NONE;
   m_dwFilePermission   = PERSON_ATTRI_NONE;
   m_strUserRole = _T("");
   m_strGroup = _T("");

	SetDataType(DAT_PERSON);
}

void CDBPersonInfoData::Copy(CDBPersonInfoData *pData)
{
	ASSERT(pData != NULL);
	CDataMid::Copy(pData);

	m_nID = pData->m_nID;
	m_strTreeCode = pData->m_strTreeCode;
	m_strUserID = pData->m_strUserID;
	m_strUserPwd = pData->m_strUserPwd;
	m_strUserName = pData->m_strUserName;
	m_strUserPower = pData->m_strUserPower;
	m_strUserTel = pData->m_strUserTel;
	m_tUserDate = pData->m_tUserDate;
	m_tUserBorn = pData->m_tUserBorn;
	m_strUserMemo = pData->m_strUserMemo;
	m_strUserSFZ = pData->m_strUserSFZ;
	//Photo
	m_strUserSale = pData->m_strUserSale;
	m_strUserDuty = pData->m_strUserDuty;
	m_strAddr = pData->m_strAddr;
	m_tInTime = pData->m_tInTime;
	m_tOutTime = pData->m_tOutTime;
	m_nOutFlag = pData->m_nOutFlag;

   m_dwAttriEx = pData->m_dwAttriEx;
   m_iSalesman = pData->m_iSalesman;
   m_strUserControlsPermission = pData->m_strUserControlsPermission;

   m_dwTagPermission    = pData->m_dwTagPermission ;
   m_dwFilePermission   = pData->m_dwFilePermission;
   m_strUserRole        = pData->m_strUserRole;
   m_strGroup           = pData->m_strGroup;
}

void CDBPersonInfoData::Serialize(CArchive& ar)
{
	CDataMid::Serialize(ar);//父类函数

	int nTagSize = 0;
	CString strName;
	int nNameSize;

	ar.Flush();
	if (ar.IsStoring())
	{
		MySerial.SaveDataInt(ar,_T("ATOADDID"),m_nID);
		MySerial.SaveDataStr(ar,_T("TREECODE"),m_strTreeCode);
		MySerial.SaveDataStr(ar,_T("USERIDCD"),m_strUserID);
		MySerial.SaveDataStr(ar,_T("USERPWD0"),m_strUserPwd);
		MySerial.SaveDataStr(ar,_T("USERNAME"),m_strUserName);
		MySerial.SaveDataStr(ar,_T("USERPOWR"),m_strUserPower);	
		MySerial.SaveDataStr(ar,_T("USERTEL0"),m_strUserTel);	
		MySerial.SaveColeDateTime(ar,_T("REGETIME"),m_tUserDate);
		MySerial.SaveColeDateTime(ar,_T("USERBORN"),m_tUserBorn);
		MySerial.SaveDataStr(ar,_T("USERMEMO"),m_strUserMemo);
		MySerial.SaveDataStr(ar,_T("USERSZF0"),m_strUserSFZ);
		//Photo
		MySerial.SaveDataStr(ar,_T("USERSALE"),m_strUserSale);
		MySerial.SaveDataStr(ar,_T("USERDUTY"),m_strUserDuty);
		MySerial.SaveDataStr(ar,_T("USERADDR"),m_strAddr);
		MySerial.SaveColeDateTime(ar,_T("LASTTIME"),m_tInTime);
		MySerial.SaveColeDateTime(ar,_T("TOUTTIME"),m_tOutTime);
		MySerial.SaveDataInt(ar,_T("TOUTFLAG"),m_nOutFlag);

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
			else if (strName == _T("ATOADDID"))
			{
				ar >>nTagSize >> m_nID;
			}
			else if (strName == _T("TREECODE"))
			{
				ar >>nTagSize >> m_strTreeCode;
			}
			else if (strName == _T("USERIDCD"))
			{
				ar >>nTagSize >> m_strUserID;
			}
			else if (strName == _T("USERPWD0"))
			{
				ar >>nTagSize >> m_strUserPwd;
			}
			else if (strName == _T("USERNAME"))
			{
				ar >>nTagSize >> m_strUserName;
			}
			else if (strName == _T("USERPOWR"))
			{
				ar >>nTagSize >> m_strUserPower;
			}
			else if (strName == _T("USERTEL0"))
			{
				ar >>nTagSize >> m_strUserTel;
			}
			else if (strName == _T("REGETIME"))
			{
				ar >>nTagSize >> m_tUserDate;
			}
			else if (strName == _T("USERBORN"))
			{
				ar >>nTagSize >> m_tUserBorn;
			}
			else if (strName == _T("USERMEMO"))
			{
				ar >>nTagSize >> m_strUserMemo;
			}
			else if (strName == _T("USERSZF0"))
			{
				ar >>nTagSize >> m_strUserSFZ;
			}
			//Photo
			else if (strName == _T("USERSALE"))
			{
				ar >>nTagSize >> m_strUserSale;
			}
			else if (strName == _T("USERDUTY"))
			{
				ar >>nTagSize >> m_strUserDuty;
			}
			else if (strName == _T("USERADDR"))
			{
				ar >>nTagSize >> m_strAddr;
			}
			else if (strName == _T("LASTTIME"))
			{
				ar >> nTagSize >> m_tInTime;
			}
			else if (strName == _T("TOUTTIME"))
			{
				ar >> nTagSize >> m_tOutTime;
			}
			else if (strName == _T("TOUTFLAG"))
			{
				ar >> nTagSize >> m_nOutFlag;
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

BOOL CDBPersonInfoData::GetAllDBInfoByUserID(CADOConn *pADOConn)
{
	ASSERT(pADOConn != NULL);
	ASSERT(!m_strUserID.IsEmpty());

	BOOL bRet = FALSE;

	CString strSQL = _T("");
	strSQL.Format(_T("select * from %s where %s='%s'"),DB_TABLE_PERSON,DBPerson_key_UserID,m_strUserID);
	pADOConn->GetRecordSet(strSQL);
	if (!pADOConn->adoEOF())
	{
		bRet = GetAllDBInfo(pADOConn);
	}

	return bRet;
}

BOOL CDBPersonInfoData::GetAllDBInfo(CADOConn *pADOConn)
{
	ASSERT(pADOConn != NULL);

	BOOL bRet = TRUE;

	if (NULL == pADOConn)
	{
		bRet = FALSE;
	}
	else
	{
		m_nID = pADOConn->GetValueInt(DBPerson_key_ID);
		m_strTreeCode = pADOConn->GetValueString(DBPerson_key_TreeCode);
		m_strUserID = pADOConn->GetValueString(DBPerson_key_UserID);
		m_strUserPwd = pADOConn->GetValueString(DBPerson_key_Pwd);
		m_strUserName = pADOConn->GetValueString(DBPerson_key_UserName);
		m_strUserPower = pADOConn->GetValueString(DBPerson_key_UserPower);
		m_strUserTel = pADOConn->GetValueString(DBPerson_key_UserTel);
		m_tUserDate = pADOConn->GetValueDate(DBPerson_key_UserDate);
		m_tUserBorn = pADOConn->GetValueDate(DBPerson_key_UserBorn);
		m_strUserMemo = pADOConn->GetValueString(DBPerson_key_UserMemo);
		m_strUserSFZ = pADOConn->GetValueString(DBPerson_key_UserSFZ);
		//Photo
		m_strUserSale = pADOConn->GetValueString(DBPerson_key_UserSale);
		m_strUserDuty = pADOConn->GetValueString(DBPerson_key_UserDuty);
		m_strAddr = pADOConn->GetValueString(DBPerson_key_Addr);
		m_tInTime = pADOConn->GetValueDate(DBPerson_key_InTime);
		m_tOutTime = pADOConn->GetValueDate(DBPerson_key_OutTime);
		m_nOutFlag = pADOConn->GetValueInt(DBPerson_key_OutFlag);

      m_dwAttriEx = pADOConn->GetValueInt64(DBPerson_key_AttriEx);
      m_iSalesman = pADOConn->GetValueInt(DBPerson_key_iSalesman);
      m_strUserControlsPermission = pADOConn->GetValueString(DBPerson_key_cUserControlsPermission);

      m_dwTagPermission  = pADOConn->GetValueInt64(DBPerson_key_dwTagPermission  );
      m_dwFilePermission = pADOConn->GetValueInt64(DBPerson_key_dwFilePermission );
      m_strUserRole = pADOConn->GetValueString(DBPerson_key_cUserRole);
      m_strGroup    = pADOConn->GetValueString(DBPerson_key_cUserGroup);

		bRet = TRUE;
	}

	return bRet;
}

BOOL CDBPersonInfoData::InsertAllDBInfoByUserID(CADOConn *pADOConn)
{
	ASSERT(pADOConn != NULL);
	
	m_strUserID.Trim();
	ASSERT(!m_strUserID.IsEmpty());

	BOOL bRet = TRUE;

	CString strSQL = _T("");
	strSQL.Format(_T("insert into %s(%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s)\
                    values('%s','%s','%s','%s','%s', '%s','%s','%s','%s','%s', '%s','%s','%s','%s','%s', '%d','%ld','%d','%s','%ld','%ld','%s','%s')"),DB_TABLE_PERSON,
                    DBPerson_key_TreeCode,DBPerson_key_UserID,DBPerson_key_Pwd,DBPerson_key_UserName,DBPerson_key_UserPower,
                    DBPerson_key_UserTel, DBPerson_key_UserDate,DBPerson_key_UserBorn,DBPerson_key_UserMemo,DBPerson_key_UserSFZ,
                    DBPerson_key_UserSale,DBPerson_key_UserDuty,DBPerson_key_Addr,DBPerson_key_InTime,DBPerson_key_OutTime,DBPerson_key_OutFlag,DBPerson_key_AttriEx,
                DBPerson_key_iSalesman,DBPerson_key_cUserControlsPermission,
                DBPerson_key_dwTagPermission  ,DBPerson_key_dwFilePermission ,DBPerson_key_cUserRole,
                DBPerson_key_cUserGroup,
                m_strTreeCode,m_strUserID,m_strUserPwd,m_strUserName,m_strUserPower,
                m_strUserTel,m_tUserDate.Format(_T("%Y-%m-%d %H:%M:%S")),m_tUserBorn.Format(_T("%Y-%m-%d %H:%M:%S")),m_strUserMemo,m_strUserSFZ,
                m_strUserSale,m_strUserDuty,m_strAddr,m_tInTime.Format(_T("%Y-%m-%d %H:%M:%S")),m_tOutTime.Format(_T("%Y-%m-%d %H:%M:%S")),
                m_nOutFlag,m_dwAttriEx,m_iSalesman,m_strUserControlsPermission,m_dwTagPermission,m_dwFilePermission,m_strUserRole,m_strGroup );

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

BOOL CDBPersonInfoData::UpdateAllDBInfoByUserID(CADOConn *pADOConn)
{
	ASSERT(pADOConn != NULL);
	m_strUserID.Trim();
	ASSERT(!m_strUserID.IsEmpty());

	BOOL bRet = TRUE;

	CString strSQL = _T("");

	strSQL.Format(_T("update %s set %s='%s',%s='%s',%s='%s',%s='%s',%s='%s',%s='%s',%s='%s',%s='%s',%s='%s',%s ='%s',%s ='%s',%s ='%s',%s ='%s',%s ='%s',%s ='%d',%s = '%ld',%s = '%d',%s='%s',%s = '%ld',%s = '%ld',%s = '%s',%s='%s' where %s='%s'"),DB_TABLE_PERSON,
		DBPerson_key_TreeCode,m_strTreeCode,
		DBPerson_key_Pwd,m_strUserPwd,
		DBPerson_key_UserName,m_strUserName,
		DBPerson_key_UserPower,m_strUserPower,
		DBPerson_key_UserTel,m_strUserTel,
		DBPerson_key_UserDate,m_tUserDate.Format(_T("%Y-%m-%d %H:%M:%S")),
		DBPerson_key_UserBorn,m_tUserBorn.Format(_T("%Y-%m-%d %H:%M:%S")),
		DBPerson_key_UserMemo,m_strUserMemo,
		DBPerson_key_UserSFZ,m_strUserSFZ,
		//DBPerson_key_UserPhoto,
		DBPerson_key_UserSale,m_strUserSale,
		DBPerson_key_UserDuty,m_strUserDuty,
		DBPerson_key_Addr,m_strAddr,
		DBPerson_key_InTime,m_tInTime.Format(_T("%Y-%m-%d %H:%M:%S")),
		DBPerson_key_OutTime,m_tOutTime.Format(_T("%Y-%m-%d %H:%M:%S")),
		DBPerson_key_OutFlag,m_nOutFlag,
      DBPerson_key_AttriEx,m_dwAttriEx,
      DBPerson_key_iSalesman,m_iSalesman,
      DBPerson_key_cUserControlsPermission,m_strUserControlsPermission,
      DBPerson_key_dwTagPermission  ,m_dwTagPermission,
      DBPerson_key_dwFilePermission ,m_dwFilePermission,
      DBPerson_key_cUserRole,m_strUserRole,
      DBPerson_key_cUserGroup,m_strGroup,
		DBPerson_key_UserID,m_strUserID);

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

BOOL CDBPersonInfoData::DelAllDBInfoByUserID(CADOConn *pADOConn)
{
	ASSERT(pADOConn != NULL);
	m_strUserID.Trim();
	ASSERT(!m_strUserID.IsEmpty());

	BOOL bRet = TRUE;

	CString strSQL = _T("");
	strSQL.Format(_T("delete from %s where %s='%s'"),DB_TABLE_PERSON,DBPerson_key_UserID,m_strUserID);

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

//CDBPersonInfoList
CDBPersonInfoList::CDBPersonInfoList()
{
}

CDBPersonInfoList::~CDBPersonInfoList()
{
}

CDBPersonInfoData*  CDBPersonInfoList::GetItem(int nIndex)
{
	if (nIndex<0||nIndex>=GetCount())
		return NULL;
	return (CDBPersonInfoData*)GetAt(FindIndex(nIndex));
}

CDBPersonInfoData* CDBPersonInfoList::GetItemByUserID(CString strUserID)
{
	CDBPersonInfoData * pItem = NULL;
	strUserID.Trim();
	if (!strUserID.IsEmpty())
	{
		for(int i=0;i< GetCount();i++)
		{
			CDBPersonInfoData * pObject = GetItem(i);
			if(strUserID==pObject->m_strUserID)
			{
				pItem = pObject;
				break;
			}
		}
	}

	return pItem;
}

int CDBPersonInfoList::GetIndexByUserID(CString strUserID)
{
	int nSel = -1;
	strUserID.Trim();
	if (!strUserID.IsEmpty())
	{
		for(int i=0;i< GetCount();i++)
		{
			CDBPersonInfoData * pObject = GetItem(i);
			if(strUserID==pObject->m_strUserID)
			{
				nSel = i;
				break;
			}
		}
	}

	return nSel;
}

void CDBPersonInfoList:: AddItem(CDBPersonInfoData* pItem)
{
	CDBPersonInfoData*pData = new CDBPersonInfoData;
	pData->Copy(pItem);
	AddTail(pData);
}

void CDBPersonInfoList::DeleteItem(int nIndex)
{
	if (nIndex<0||nIndex>GetCount())
		return;
	CDBPersonInfoData *pObject=(CDBPersonInfoData*)GetItem(nIndex);
	delete pObject;
	pObject=NULL;
	RemoveAt(FindIndex(nIndex));
}

void CDBPersonInfoList::GetListFromDB(CADOConn *pADOConn)
{
	ASSERT(pADOConn != NULL);

	Empty();
	CString strSQL = _T("");
	strSQL.Format(_T("select * from %s order by %s desc"),DB_TABLE_PERSON,DBPerson_key_UserDate);
	pADOConn->GetRecordSet(strSQL);
	while (!pADOConn->adoEOF())
	{
		CDBPersonInfoData oData;
		oData.GetAllDBInfo(pADOConn);
		AddItem(&oData);
		pADOConn->MoveNext();
	}
}

BOOL CDBPersonInfoList::ResetAllPwdExpectAdmin(CADOConn *pADOConn)
{
	ASSERT(pADOConn != NULL);
	BOOL bRet = TRUE;

	CString strSQL = _T("");
	strSQL.Format(_T("update %s set %s='666666' where %s<>'%s'"),DB_TABLE_PERSON,DBPerson_key_Pwd,DBPerson_key_UserID,_T("admin"));

	if (pADOConn->ExecuteSQL(strSQL))
	{
		bRet = TRUE;

		for (int i=0;i<GetCount();i++)
		{
			CDBPersonInfoData *pData = GetItem(i);
			if (pData && 0 != pData->m_strUserID.CompareNoCase(_T("admin")))
			{
				pData->m_strUserPwd = _T("666666");
			}
		}
	}
	else
	{
		bRet = FALSE;
	}

	return bRet;
}


//根据员工编号获取员工姓名 yangjr 2017-7-5
CString CDBPersonInfoList::GetUserNameByUserID(CADOConn *pADOConn,CString userID)
{
	ASSERT(pADOConn != NULL);
   CString strSQL = _T("");
   strSQL.Format(_T("SELECT %s FROM %s where %s = '%s'")
      ,DBPerson_key_UserName,DB_TABLE_PERSON,DBPerson_key_UserID,userID
      );
   pADOConn->GetRecordSet(strSQL);
   CString strName = _T("");
   while (!pADOConn->adoEOF())
   {
      strName =pADOConn->GetValueString(DBPerson_key_UserName);  //员工名称
      break;
   }
   return strName;
}

CDBPersonInfoList * CDBPersonInfoList::Instance()
{
	if(sm_inst.get() == 0)
		sm_inst = shared_ptr<CDBPersonInfoList>(new CDBPersonInfoList);

	return sm_inst.get();
}

map<CString,CString> CDBPersonInfoList::GetUsrIDAndName(CADOConn *pADOConn)
{
	ASSERT(pADOConn != NULL);
	CString strSQL = _T("");
	strSQL.Format(_T("select %s,%s from  %s"),DBPerson_key_UserID,DBPerson_key_UserName,DB_TABLE_PERSON);
	pADOConn->GetRecordSet(strSQL);
	map<CString,CString> map_data;
	while(!pADOConn->adoEOF())
	{
		CString strUsrID = pADOConn->GetValueString(DBPerson_key_UserID);
		CString strUsrName = pADOConn->GetValueString(DBPerson_key_UserName);
		map_data.insert(make_pair(strUsrID,strUsrName));
		pADOConn->MoveNext();
	}
	return map_data;
}

//获取某部门人员信息 map<UserID,UserName> wuzhihua 2018/3/19
map<CString,CString> CDBPersonInfoList::GetUsrIDAndName(CADOConn *pADOConn , CString treeCode)
{
	CString strSQL = _T("");
	strSQL.Format(_T("select %s,%s from  %s where %s = '%s' and %s <> '%d'"),DBPerson_key_UserID,DBPerson_key_UserName,DB_TABLE_PERSON ,
		DBPerson_key_TreeCode , treeCode,DBPerson_key_OutFlag,1);
	pADOConn->GetRecordSet(strSQL);
	map<CString,CString> map_data;
	while(!pADOConn->adoEOF())
	{
		CString strUsrID = pADOConn->GetValueString(DBPerson_key_UserID);
		CString strUsrName = pADOConn->GetValueString(DBPerson_key_UserName);
		map_data.insert(make_pair(strUsrID,strUsrName));
		pADOConn->MoveNext();
	}
	return map_data;
}

BOOL CDBPersonInfoList::DeleteUserByUserID(CADOConn* pADOConn,vector<CString>vecUserID)
{
   ASSERT(pADOConn != NULL);
   if (vecUserID.size() <=0)
      return FALSE;

   CString strUserID;
   for (int i=0; i<(int)vecUserID.size(); ++i)
   {
      strUserID += _T("'")+vecUserID[i]+_T("',");
   }
   strUserID.TrimRight(_T(","));
   CString strSql;
   strSql.Format(_T("delete %s where %s in (%s)"),DB_TABLE_PERSON,DBPerson_key_UserID,strUserID);
   return pADOConn->ExecuteSQL(strSql);
}

BOOL CDBPersonInfoList::UpdateUserPermission(CADOConn * pADOConn,std::map<CString,CString> map_UserID_Permission)
{
   CString strSQL = _T("");

   vector<CString> vecExecSQL;
   for (auto it = map_UserID_Permission.begin();it != map_UserID_Permission.end();++it)
   {
      strSQL.Format(_T("update %s set %s = '%s' where %s = '%s'"),DB_TABLE_PERSON,
         DBPerson_key_cUserControlsPermission,it->second,
         DBPerson_key_UserID,it->first);

      vecExecSQL.push_back(strSQL);
   }

   return pADOConn->ExecuteSQLByTransaction(vecExecSQL);
}

#ifdef USING_GRIDCTRL_MARK
MAP_GridCtrl_AllData CDBPersonInfoList::CreateGridData()
{
	MAP_GridCtrl_AllData  map_all_data;

	int nIndex = 0,nCount = GetCount();
	int nValidCount = 1;
	for (nIndex = 0;nIndex < nCount;nIndex++)
	{
		CDBPersonInfoData * pData = GetItem(nIndex);
		if (NULL != pData)
		{
			MAP_GridCtrl_RowData map_row_data;
         InsertRowData(DBPerson_key_ID,map_row_data,CB_enum_FieldData_Int,CB_enum_FieldCtrl_Text,FORMAT_INT,pData->m_nID);
         InsertRowData(DBPerson_key_TreeCode,map_row_data,CB_enum_FieldData_CString,CB_enum_FieldCtrl_Text,FORMAT_STRING,pData->m_strTreeCode);
         InsertRowData(DBPerson_key_UserID,map_row_data,CB_enum_FieldData_CString,CB_enum_FieldCtrl_Text,FORMAT_STRING,pData->m_strUserID);
         InsertRowData(DBPerson_key_UserName,map_row_data,CB_enum_FieldData_CString,CB_enum_FieldCtrl_Text,FORMAT_STRING,pData->m_strUserName);
         InsertRowData(DBPerson_key_UserPower,map_row_data,CB_enum_FieldData_CString,CB_enum_FieldCtrl_Text,FORMAT_STRING,pData->m_strUserPower);
         InsertRowData(DBPerson_key_UserTel,map_row_data,CB_enum_FieldData_CString,CB_enum_FieldCtrl_Text,FORMAT_STRING,pData->m_strUserTel);
         InsertRowData(DBPerson_key_UserDate,map_row_data,CB_enum_FieldData_CString,CB_enum_FieldCtrl_Text,FORMAT_STRING,pData->m_tUserDate.Format(_T("%Y-%m-%d")));
         InsertRowData(DBPerson_key_UserBorn,map_row_data,CB_enum_FieldData_CString,CB_enum_FieldCtrl_Text,FORMAT_STRING,pData->m_tUserBorn.Format(_T("%Y-%m-%d")));
         InsertRowData(DBPerson_key_UserMemo,map_row_data,CB_enum_FieldData_CString,CB_enum_FieldCtrl_Text,FORMAT_STRING,pData->m_strUserMemo);
         InsertRowData(DBPerson_key_UserSFZ,map_row_data,CB_enum_FieldData_CString,CB_enum_FieldCtrl_Text,FORMAT_STRING,pData->m_strUserSFZ);
         InsertRowData(DBPerson_key_UserSale,map_row_data,CB_enum_FieldData_CString,CB_enum_FieldCtrl_Text,FORMAT_STRING,pData->m_strUserSale);
         InsertRowData(DBPerson_key_UserDuty,map_row_data,CB_enum_FieldData_CString,CB_enum_FieldCtrl_Text,FORMAT_STRING,pData->m_strUserDuty);
         InsertRowData(DBPerson_key_AttriEx,map_row_data,CB_enum_FieldData_CString,CB_enum_FieldCtrl_Text,_T("%ld"),pData->m_dwAttriEx);
         InsertRowData(DBPerson_key_iSalesman,map_row_data,CB_enum_FieldData_CString,CB_enum_FieldCtrl_Text,FORMAT_STRING,pData->m_iSalesman == 1?_T("是"):_T("否"));

			//写入行数据
			map_all_data.insert(make_pair(nValidCount,map_row_data));
			//行数据插入所有数据中

			nValidCount++;
		}
	}
	return map_all_data;
}

BOOL CDBPersonInfoList::ModifyUserPassword(CADOConn *pADOConn,CDBPersonInfoData* pData)
{
	ASSERT(pADOConn != NULL);
	ASSERT(pData != NULL);
	CString strSQL = _T("");
	strSQL.Format(_T("Update  %s set %s='%s' where %s='%s'"),DB_TABLE_PERSON,
		DBPerson_key_Pwd,pData->m_strUserPwd,DBPerson_key_UserID,pData->m_strUserID);
	if(pADOConn->ExecuteSQL(strSQL))
	{
		return TRUE;
	}
	return FALSE;
}
void CDBPersonInfoList::GetAllDBInfoByRole(map<CString,vector<CString>> &mapPersonInfo)//根据角色分类 liuhw 2019/05/21
{
   for(int i = 0;i < GetCount();i++)
   {
      CDBPersonInfoData *pData = GetItem(i);
      if (pData != NULL)
      {
         CString strName = pData->m_strUserName;
         CString strRole = pData->m_strUserDuty;

         auto itr_find = mapPersonInfo.find(strRole);
         if (itr_find != mapPersonInfo.end())
         {
            itr_find->second.push_back(strName);
         }
         else
         {
            vector<CString> vecName;
            vecName.push_back(strName);
            mapPersonInfo.insert(make_pair(strRole,vecName));
         }

      }

   }
}
CString stc_staff_info::Get_Update_SQL(BOOL bIgnoreNum)
{
   CString strText = _T("");
   CString strUpdateSql = _T("");
   if (!strUserPower.IsEmpty()|| !bIgnoreNum)
   {
      strText.Format(_T("%s = '%s',"), DBPerson_key_UserPower, strUserPower);
      strUpdateSql += strText;
   }
   if (!strUserPwd.IsEmpty()|| !bIgnoreNum)
   {
      strText.Format(_T("%s = '%s',"), DBPerson_key_Pwd, strUserPwd);
      strUpdateSql += strText;
   }
   if (!strUserTel.IsEmpty()|| !bIgnoreNum)
   {
      strText.Format(_T("%s = '%s',"), DBPerson_key_UserTel, strUserTel);
      strUpdateSql += strText;
   }
   if(!strUserDate.IsEmpty()|| !bIgnoreNum)
   {
      strText.Format(_T("%s = '%s',"), DBPerson_key_UserDate, strUserDate);
      strUpdateSql += strText;
   }
   if(!strUserBorn.IsEmpty()|| !bIgnoreNum)
   {
      strText.Format(_T("%s = '%s',"), DBPerson_key_UserBorn, strUserBorn);
      strUpdateSql += strText;
   }
   if(!strUserMemo.IsEmpty()|| !bIgnoreNum)
   {
      strText.Format(_T("%s = '%s',"), DBPerson_key_UserMemo, strUserMemo);
      strUpdateSql += strText;
   }
   if(!strUserSFZ.IsEmpty()|| !bIgnoreNum)
   {
      strText.Format(_T("%s = '%s',"), DBPerson_key_UserSFZ, strUserSFZ);
      strUpdateSql += strText;
   }
   if (!strUserSale.IsEmpty()|| !bIgnoreNum)
   {
      strText.Format(_T("%s = '%s',"), DBPerson_key_UserSale, strUserSale);
      strUpdateSql += strText;
   }

   if(!strUserDuty.IsEmpty()|| !bIgnoreNum)
   {
      strText.Format(_T("%s = '%s',"), DBPerson_key_UserDuty, strUserDuty);
      strUpdateSql += strText;
   }
   if(!strAddr.IsEmpty()|| !bIgnoreNum)
   {
      strText.Format(_T("%s = '%s',"), DBPerson_key_Addr, strAddr);
      strUpdateSql += strText;
   }
   //if (!strOutTime.IsEmpty()|| !bIgnoreNum)
   //{
   //   strText.Format(_T("%s = '%s',"), DBPerson_key_OutTime, strOutTime);
   //   strUpdateSql += strText;
   //}
   if (!strAttriEx.IsEmpty()|| !bIgnoreNum)
   {
      strText.Format(_T("%s = '%s',"), DBPerson_key_AttriEx, strAttriEx);
      strUpdateSql += strText;
   }
   if (!strSalesman.IsEmpty()|| !bIgnoreNum)
   {
      strText.Format(_T("%s = '%s',"), DBPerson_key_iSalesman, strSalesman);
      strUpdateSql += strText;
   }
   if (!strTreeCode.IsEmpty() || !bIgnoreNum)
   {
      strText.Format(_T("%s = '%s',"), DBPerson_key_TreeCode, strTreeCode);
      strUpdateSql += strText;
   }
   if (!strUserName.IsEmpty()|| !bIgnoreNum)
   {
      strText.Format(_T("%s = '%s'"), DBPerson_key_UserName, strUserName);
      strUpdateSql += strText;
   }
   if (!strUpdateSql.IsEmpty())
   {
      CString strSql = _T("");
      strSql.Format(_T("update %s set %s where %s = '%s'"),DB_TABLE_PERSON, strUpdateSql, DBPerson_key_UserID, strUserID);
      return strSql;
   }
   return _T("");
}
CString stc_staff_info::Get_Insert_SQL()
{
   CString strColumnName = _T("");
   CString strValue = _T("");
   CString strSql = _T("");
   strColumnName.Format(_T("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s"),
      DBPerson_key_TreeCode,
      DBPerson_key_UserID,
      DBPerson_key_Pwd,
      DBPerson_key_UserName,
      DBPerson_key_UserPower,
      DBPerson_key_UserTel,
      DBPerson_key_UserDate,
      DBPerson_key_UserBorn,
      DBPerson_key_UserMemo,
      DBPerson_key_UserSFZ,
      DBPerson_key_UserSale,
      DBPerson_key_UserDuty,
      DBPerson_key_Addr,
      DBPerson_key_OutFlag,
      DBPerson_key_AttriEx,
      DBPerson_key_iSalesman
      );
                     // 1     2    3   4     5    6   7     8    9   10   11   12   13   14   15   16 
   strValue.Format(_T("'%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s'"),
      strTreeCode,       //1
      strUserID,         //2
      strUserPwd,        //3
      strUserName,       //4
      strUserPower,      //5
      strUserTel,        //6
      strUserDate,       //7
      strUserBorn,       //8
      strUserMemo,       //9
      strUserSFZ,        //10
      strUserSale,       //11
      strUserDuty,       //12
      strAddr,           //13
      _T("0"),        //14
      strAttriEx,        //15
      strSalesman        //16
      );
   strSql.Format(_T("insert into %s(%s) values(%s)"), DB_TABLE_PERSON, strColumnName, strValue);

   return strSql;
}
#endif // USING_GRIDCTRL_MARK