#include "StdAfx.h"
#include "DBUserInfo.h"
#include "CDBFieldDefine.h"
#include "ADOConn/ADOConn.h"




IMPLEMENT_SERIAL(CDBUserInfoData,  CObject, 1)
IMPLEMENT_SERIAL(CDBUserInfoList,  CObList, 1)

std::shared_ptr<CDBUserInfoData> CDBUserInfoData::sm_inst;
std::shared_ptr<CDBUserInfoList> CDBUserInfoList::sm_inst;

CDBUserInfoData::CDBUserInfoData()
{
	ResetData();
} 

CDBUserInfoData::~CDBUserInfoData()
{
}

void CDBUserInfoData::operator=( CDBUserInfoData *pData )
{
	Copy(pData);
}

CDBUserInfoData * CDBUserInfoData::Instance()
{
	if(sm_inst.get() == 0)
		sm_inst = std::shared_ptr<CDBUserInfoData>(new CDBUserInfoData);
	return sm_inst.get();
}

void CDBUserInfoData::ResetData()
{
	m_nID = -1;	
	m_strUserID = _T("");
	m_strUserPwd = _T("");
	m_strUserName = _T("");	
	m_tUserDate = COleDateTime::GetCurrentTime();	
	m_tLastLoadTime = COleDateTime::GetCurrentTime();
	m_nUserState = 0;
}

void CDBUserInfoData::Copy(CDBUserInfoData *pData)
{
	ASSERT(pData != NULL);
	//CDataMid::Copy(pData);

	m_nID = pData->m_nID;	
	m_strUserID = pData->m_strUserID;
	m_strUserPwd = pData->m_strUserPwd;
	m_strUserName = pData->m_strUserName;	
	m_tUserDate = pData->m_tUserDate;	
	m_tLastLoadTime = pData->m_tLastLoadTime;
	m_nUserState = pData->m_nUserState;	
}

BOOL CDBUserInfoData::GetAllDBInfoByUserID(CADOConn *pADOConn)
{
	ASSERT(pADOConn != NULL);
	ASSERT(!m_strUserID.IsEmpty());

	BOOL bRet = FALSE;

	CString strSQL = _T("");
	strSQL.Format(_T("select * from %s where %s='%s'"),
      DB_TABLE_USERINFO,DBUser_key_cUserID,m_strUserID);
	pADOConn->GetRecordSet(strSQL);
	if (!pADOConn->adoEOF())
	{
		bRet = GetAllDBInfo(pADOConn);
	}

	return bRet;
}

BOOL CDBUserInfoData::GetAllDBInfo(CADOConn *pADOConn)
{
	ASSERT(pADOConn != NULL);

	BOOL bRet = TRUE;

	if (NULL == pADOConn)
	{
		bRet = FALSE;
	}
	else
	{
		m_nID = pADOConn->GetValueInt(DBUser_key_ID);		
		m_strUserID = pADOConn->GetValueString(DBUser_key_cUserID);
		m_strUserPwd = pADOConn->GetValueString(DBUser_key_cPassword);
		m_strUserName = pADOConn->GetValueString(DBUser_key_cUserName);	
		m_tUserDate = pADOConn->GetValueDate(DBUser_key_cUserDate);		
		m_tLastLoadTime = pADOConn->GetValueDate(DBUser_key_dtLastLoadTime);		
		m_nUserState= pADOConn->GetValueInt(DBUser_key_iUserState);
		bRet = TRUE;
	}

	return bRet;
}

BOOL CDBUserInfoData::InsertAllDBInfoByUserID(CADOConn *pADOConn)
{
	ASSERT(pADOConn != NULL);
	
	m_strUserID.Trim();
	ASSERT(!m_strUserID.IsEmpty());

	BOOL bRet = TRUE;

	CString strSQL = _T("");
	strSQL.Format(_T("insert into %s(%s,%s,%s,%s,%s,%s)\
					 values('%s','%s','%s','%s','%s','%d')"),DB_TABLE_USERINFO,
					 DBUser_key_cUserID,DBUser_key_cPassword,DBUser_key_cUserName,\
					 DBUser_key_cUserDate,DBUser_key_dtLastLoadTime,DBUser_key_iUserState,\
					 m_strUserID,m_strUserPwd,m_strUserName,m_tUserDate.Format(_T("%Y-%m-%d %H:%M:%S")),\
					 m_tLastLoadTime.Format(_T("%Y-%m-%d %H:%M:%S")),m_nUserState);

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

BOOL CDBUserInfoData::UpdateAllDBInfoByUserID(CADOConn *pADOConn)
{
	ASSERT(pADOConn != NULL);
	m_strUserID.Trim();
	ASSERT(!m_strUserID.IsEmpty());

	BOOL bRet = TRUE;

	CString strSQL = _T("");

	strSQL.Format(_T("update %s set %s='%s',%s='%s',%s='%s',%s='%s',%s ='%d' where %s='%s'"),DB_TABLE_USERINFO,		
		DBUser_key_cPassword,m_strUserPwd,
		DBUser_key_cUserName,m_strUserName,		
		DBUser_key_cUserDate,m_tUserDate.Format(_T("%Y-%m-%d %H:%M:%S")),		
		DBUser_key_dtLastLoadTime,m_tLastLoadTime.Format(_T("%Y-%m-%d %H:%M:%S")),
		DBUser_key_iUserState,m_nUserState,
		DBUser_key_cUserID,m_strUserID);

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

BOOL CDBUserInfoData::DelAllDBInfoByUserID(CADOConn *pADOConn)
{
	ASSERT(pADOConn != NULL);
	m_strUserID.Trim();
	ASSERT(!m_strUserID.IsEmpty());

	BOOL bRet = TRUE;

	CString strSQL = _T("");
	strSQL.Format(_T("delete from %s where %s='%s'"),DB_TABLE_USERINFO,DBUser_key_cUserID,m_strUserID);

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

//CDBUserInfoList
CDBUserInfoList::CDBUserInfoList()
{
}

CDBUserInfoList::~CDBUserInfoList()
{
}

CDBUserInfoData*  CDBUserInfoList::GetItem(int nIndex)
{
	if (nIndex<0||nIndex>=GetCount())
		return NULL;
	return (CDBUserInfoData*)GetAt(FindIndex(nIndex));
}

CDBUserInfoData* CDBUserInfoList::GetItemByUserID(CString strUserID)
{
	CDBUserInfoData * pItem = NULL;
	strUserID.Trim();
	if (!strUserID.IsEmpty())
	{
		for(int i=0;i< GetCount();i++)
		{
			CDBUserInfoData * pObject = GetItem(i);
			if(strUserID==pObject->m_strUserID)
			{
				pItem = pObject;
				break;
			}
		}
	}

	return pItem;
}

int CDBUserInfoList::GetIndexByUserID(CString strUserID)
{
	int nSel = -1;
	strUserID.Trim();
	if (!strUserID.IsEmpty())
	{
		for(int i=0;i< GetCount();i++)
		{
			CDBUserInfoData * pObject = GetItem(i);
			if(strUserID==pObject->m_strUserID)
			{
				nSel = i;
				break;
			}
		}
	}

	return nSel;
}

void CDBUserInfoList:: AddItem(CDBUserInfoData* pItem)
{
	CDBUserInfoData*pData = new CDBUserInfoData;
	pData->Copy(pItem);
	AddTail(pData);
}

void CDBUserInfoList::DeleteItem(int nIndex)
{
	if (nIndex<0||nIndex>GetCount())
		return;
	CDBUserInfoData *pObject=(CDBUserInfoData*)GetItem(nIndex);
	delete pObject;
	pObject=NULL;
	RemoveAt(FindIndex(nIndex));
}

void CDBUserInfoList::GetListFromDB(CADOConn *pADOConn)
{
	ASSERT(pADOConn != NULL);

	Empty();
	CString strSQL = _T("");
	strSQL.Format(_T("select * from %s order by %s desc"),
      DB_TABLE_USERINFO,DBUser_key_cUserDate);
	pADOConn->GetRecordSet(strSQL);
	while (!pADOConn->adoEOF())
	{
		CDBUserInfoData oData;
		oData.GetAllDBInfo(pADOConn);
		AddItem(&oData);
		pADOConn->MoveNext();
	}
}

//根据员工编号获取员工姓名 yangjr 2017-7-5
CString CDBUserInfoList::GetUserNameByUserID(CADOConn *pADOConn,CString userID)
{
	ASSERT(pADOConn != NULL);
   CString strSQL = _T("");
   strSQL.Format(_T("SELECT %s FROM %s where %s = '%s'")
      ,DBUser_key_cUserName,DB_TABLE_USERINFO,DBUser_key_cUserID,userID
      );
   pADOConn->GetRecordSet(strSQL);
   CString strName = _T("");
   while (!pADOConn->adoEOF())
   {
      strName =pADOConn->GetValueString(DBUser_key_cUserName);  //员工名称
      break;
   }
   return strName;
}

CDBUserInfoList * CDBUserInfoList::Instance()
{
	if(sm_inst.get() == 0)
		sm_inst = std::shared_ptr<CDBUserInfoList>(new CDBUserInfoList);

	return sm_inst.get();
}

std::map<CString,CString> CDBUserInfoList::GetUsrIDAndName(CADOConn *pADOConn)
{
	ASSERT(pADOConn != NULL);
	CString strSQL = _T("");
	strSQL.Format(_T("select %s,%s from  %s"),DBUser_key_cUserID,DBUser_key_cUserName,DB_TABLE_USERINFO);
	pADOConn->GetRecordSet(strSQL);
	std::map<CString,CString> map_data;
	while(!pADOConn->adoEOF())
	{
		CString strUsrID = pADOConn->GetValueString(DBUser_key_cUserID);
		CString strUsrName = pADOConn->GetValueString(DBUser_key_cUserName);
		map_data.insert(std::make_pair(strUsrID,strUsrName));
		pADOConn->MoveNext();
	}
	return map_data;
}

#ifdef USING_GRIDCTRL_MARK
MAP_GridCtrl_AllData CDBUserInfoList::CreateGridData()
{
	MAP_GridCtrl_AllData  map_all_data;

	int nIndex = 0,nCount = GetCount();
	int nValidCount = 1;
	for (nIndex = 0;nIndex < nCount;++nIndex)
	{
		CDBUserInfoData * pData = GetItem(nIndex);
		if (NULL != pData)
		{         
			MAP_GridCtrl_RowData map_row_data;
			S_GridCtrl_FieldData s_filed_data_ID;
			s_filed_data_ID.strValue.Format(_T("%d"),pData->m_nID);
			s_filed_data_ID.fieldDataType = CB_enum_FieldData_Int;
			s_filed_data_ID.fieldCtrlType = CB_enum_FieldCtrl_Text;
			map_row_data.insert(make_pair(DBUser_key_ID,s_filed_data_ID));	//自增ID         		

			S_GridCtrl_FieldData s_filed_UserID;
			s_filed_UserID.strValue = pData->m_strUserID;
			s_filed_UserID.fieldDataType = CB_enum_FieldData_CString;
			s_filed_UserID.fieldCtrlType = CB_enum_FieldCtrl_Text;
			map_row_data.insert(make_pair(DBUser_key_cUserID,s_filed_UserID));//用户ID
         
			S_GridCtrl_FieldData s_filed_Name;
			s_filed_Name.strValue = pData->m_strUserName;
			s_filed_Name.fieldDataType = CB_enum_FieldData_CString;
			s_filed_Name.fieldCtrlType = CB_enum_FieldCtrl_Text;
			map_row_data.insert(make_pair(DBUser_key_cUserName,s_filed_Name));//姓名

			S_GridCtrl_FieldData s_filed_Reg;
			s_filed_Reg.strValue = pData->m_tUserDate.Format(_T("%Y-%m-%d"));
			s_filed_Reg.fieldDataType = CB_enum_FieldData_CString;
			s_filed_Reg.fieldCtrlType = CB_enum_FieldCtrl_Text;
			map_row_data.insert(make_pair(DBUser_key_cUserDate,s_filed_Reg));//用户注册时间

         S_GridCtrl_FieldData s_filed_LastLoad;
         s_filed_LastLoad.strValue = pData->m_tLastLoadTime.Format(_T("%Y-%m-%d"));
         s_filed_LastLoad.fieldDataType = CB_enum_FieldData_CString;
         s_filed_LastLoad.fieldCtrlType = CB_enum_FieldCtrl_Text;
         map_row_data.insert(make_pair(DBUser_key_dtLastLoadTime,s_filed_LastLoad));//最后一次登入时间


			//写入行数据
			map_all_data.insert(make_pair(nValidCount,map_row_data));
			//行数据插入所有数据中

			nValidCount++;
		}
	}
	return map_all_data;
}

BOOL CDBUserInfoList::ModifyUserPassword(CADOConn *pADOConn,CDBUserInfoData* pData)
{
	ASSERT(pADOConn != NULL);
	ASSERT(pData != NULL);
	CString strSQL = _T("");
	strSQL.Format(_T("Update  %s set %s='%s' where %s='%s'"),DB_TABLE_USERINFO,
		DBUser_key_cPassword,pData->m_strUserPwd,DBUser_key_cUserID,pData->m_strUserID);
	if(pADOConn->ExecuteSQL(strSQL))
	{
		return TRUE;
	}
	return FALSE;
}



#endif // USING_GRIDCTRL_MARK