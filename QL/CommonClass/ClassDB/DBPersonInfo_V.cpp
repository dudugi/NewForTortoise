#include "StdAfx.h"
#include "DBPersonInfo_V.h"
#include "DBDataDictionary.h"
#include "ADOConn\DBImage.h"

#include "DBKeyDef.h"
#include "DBKeyDef_V.h"
#include "DBKeyDef_Cust.h"
#include <algorithm>

std::shared_ptr<CDBPersonInfoList_V> CDBPersonInfoList_V::sm_inst;

CDBPersonInfoData_V::CDBPersonInfoData_V(void)
{
	m_pUserPhoto = NULL;
	ResetData();
}

CDBPersonInfoData_V::~CDBPersonInfoData_V(void)
{
	ClearPhoto();
}

void CDBPersonInfoData_V::ResetData()
{
	m_nID					=	0;
	m_strcTreeCode			=	_T("");
	m_strcUserID			=	_T("");
	m_strcPassword			=	_T("");
	m_strcUserName			=	_T("");
	m_strcUserPower			=	_T("");
	m_strcUserTel			=	_T("");
	m_oledtUserDate			=	COleDateTime::GetCurrentTime();
	m_oledtUserBorn			=	COleDateTime::GetCurrentTime();
	m_strcUserMemo			=	_T("");
	m_strcUserSFZ			=	_T("");
	m_strcUserSale			=	_T("");
	m_strcUserDuty			=	_T("");
	m_strcAddr				=	_T("");
	m_oledtInTime			=	COleDateTime::GetCurrentTime();
	m_oledtOutTime			=	COleDateTime::GetCurrentTime();
	m_niOutFlag				=	0;
	m_strcTreeName			=	_T("");
   m_iSalesman = 0;

   m_dwAttriEx          =  PERSON_ATTRI_NONE;
   m_strUserControlsPermission = _T("");

   m_dwTagPermission    = PERSON_ATTRI_NONE;
   m_dwFilePermission   = PERSON_ATTRI_NONE;
   m_strUserRole = _T("");
   m_strGroup = _T("");
	ClearPhoto();

	SetDataType(DAT_VPERSON);
}

void CDBPersonInfoData_V::Copy( CDBPersonInfoData_V * pData )
{
	ASSERT(NULL != pData);
	CDataMid::Copy(pData);

	m_nID					=	pData->m_nID					;
	m_strcTreeCode			=	pData->m_strcTreeCode			;
	m_strcUserID			=	pData->m_strcUserID				;
	m_strcPassword			=	pData->m_strcPassword			;
	m_strcUserName			=	pData->m_strcUserName			;
	m_strcUserPower			=	pData->m_strcUserPower			;
	m_strcUserTel			=	pData->m_strcUserTel			;
	m_oledtUserDate			=	pData->m_oledtUserDate			;
	m_oledtUserBorn			=	pData->m_oledtUserBorn			;
	m_strcUserMemo			=	pData->m_strcUserMemo			;
	m_strcUserSFZ			=	pData->m_strcUserSFZ			;

	m_strcUserSale			=	pData->m_strcUserSale			;
	m_strcUserDuty			=	pData->m_strcUserDuty			;
	m_strcAddr				=	pData->m_strcAddr				;
	m_oledtInTime			=	pData->m_oledtInTime			;
	m_oledtOutTime			=	pData->m_oledtOutTime			;
	m_niOutFlag				=	pData->m_niOutFlag				;

	m_strcTreeName			=	pData->m_strcTreeName			;

   m_dwAttriEx          =  pData->m_dwAttriEx         ;
   m_iSalesman = pData->m_iSalesman;
   m_strUserControlsPermission = pData->m_strUserControlsPermission;

   m_dwTagPermission    =  pData->m_dwTagPermission   ;
   m_dwFilePermission   =  pData->m_dwFilePermission  ;
   m_strUserRole = pData->m_strUserRole;
   m_strGroup = pData->m_strGroup;

	ClearPhoto();
	if (pData->m_pUserPhoto)
	{
		m_pUserPhoto			=	pData->m_pUserPhoto->Clone()	;
	}
}

void CDBPersonInfoData_V::ToDBData( CDBPersonInfoData & oDBData)
{
	oDBData.m_nID			=	m_nID			;
	oDBData.m_strTreeCode	=	m_strcTreeCode	;
	oDBData.m_strUserID		=	m_strcUserID	;
	oDBData.m_strUserPwd	=	m_strcPassword	;
	oDBData.m_strUserName	=	m_strcUserName	;
	oDBData.m_strUserPower	=	m_strcUserPower	;
	oDBData.m_strUserTel	=	m_strcUserTel	;
	oDBData.m_tUserDate		=	m_oledtUserDate	;
	oDBData.m_tUserBorn		=	m_oledtUserBorn	;
	oDBData.m_strUserMemo	=	m_strcUserMemo	;
	oDBData.m_strUserSFZ	=	m_strcUserSFZ	;

	oDBData.m_strUserSale	=	m_strcUserSale	;
	oDBData.m_strUserDuty	=	m_strcUserDuty	;
	oDBData.m_strAddr		=	m_strcAddr		;
	oDBData.m_tInTime		=	m_oledtInTime	;
	oDBData.m_tOutTime		=	m_oledtOutTime	;
	oDBData.m_nOutFlag		=	m_niOutFlag		;

   oDBData.m_dwAttriEx     =  m_dwAttriEx;
   oDBData.m_iSalesman = m_iSalesman;
   oDBData.m_strUserControlsPermission = m_strUserControlsPermission;

   oDBData.m_dwTagPermission  = m_dwTagPermission ;
   oDBData.m_dwFilePermission = m_dwFilePermission;
   oDBData.m_strUserRole = m_strUserRole;
   oDBData.m_strGroup = m_strGroup;
}

BOOL CDBPersonInfoData_V::GetAllDBInfo( CADOConn *pADOConn )
{
	ASSERT(NULL != pADOConn);
	BOOL bRet = FALSE;
	if (NULL != pADOConn)
	{
		m_nID				=	pADOConn->GetValueInt(DBPerson_key_ID			);
		m_strcTreeCode		=	pADOConn->GetValueString(DBPerson_key_TreeCode		);
		m_strcUserID		=	pADOConn->GetValueString(DBPerson_key_UserID		);
		m_strcPassword		=	pADOConn->GetValueString(DBPerson_key_Pwd			);
		m_strcUserName		=	pADOConn->GetValueString(DBPerson_key_UserName		);
		m_strcUserPower		=	pADOConn->GetValueString(DBPerson_key_UserPower		);
		m_strcUserTel		=	pADOConn->GetValueString(DBPerson_key_UserTel		);
		//m_oledtUserDate.ParseDateTime(pADOConn->GetValueString(DBPerson_key_UserDate));
		m_oledtUserDate		=	pADOConn->GetValueDate(DBPerson_key_UserDate);
		//m_oledtUserBorn.ParseDateTime(pADOConn->GetValueString(DBPerson_key_UserBorn));
		m_oledtUserBorn		=	pADOConn->GetValueDate(DBPerson_key_UserBorn);
		m_strcUserMemo		=	pADOConn->GetValueString(DBPerson_key_UserMemo		);
		m_strcUserSFZ		=	pADOConn->GetValueString(DBPerson_key_UserSFZ		);

		m_strcUserSale		=	pADOConn->GetValueString(DBPerson_key_UserSale		);
		m_strcUserDuty		=	pADOConn->GetValueString(DBPerson_key_UserDuty		);
		m_strcAddr			=	pADOConn->GetValueString(DBPerson_key_Addr			);
		//m_oledtInTime.ParseDateTime(pADOConn->GetValueString(DBPerson_key_InTime	));
		m_oledtInTime		=	pADOConn->GetValueDate(DBPerson_key_InTime);
		//m_oledtOutTime.ParseDateTime(pADOConn->GetValueString(DBPerson_key_OutTime	));
		m_oledtOutTime		=	pADOConn->GetValueDate(DBPerson_key_OutTime);
		m_niOutFlag			=	pADOConn->GetValueInt(DBPerson_key_OutFlag		);
		m_strcTreeName		=	pADOConn->GetValueString(DBDataDic_key_ItemName		);

      m_dwAttriEx       =  pADOConn->GetValueInt64(DBPerson_key_AttriEx);
		ClearPhoto();
		CDBImage oNewImage;
		m_pUserPhoto		=	oNewImage.NewImageFromDB(DBPerson_key_UserPhoto,pADOConn->GetRecoPtr());
      m_iSalesman = pADOConn->GetValueInt64(DBPerson_key_iSalesman);

      m_strUserControlsPermission = pADOConn->GetValueString(DBPerson_key_cUserControlsPermission);
      m_dwTagPermission  = pADOConn->GetValueInt64(DBPerson_key_dwTagPermission);
      m_dwFilePermission = pADOConn->GetValueInt64(DBPerson_key_dwFilePermission);
      m_strUserRole = pADOConn->GetValueString(DBPerson_key_cUserRole);
      m_strGroup= pADOConn->GetValueString(DBPerson_key_cUserGroup);

		bRet = TRUE;
	}

	return bRet;
}

BOOL CDBPersonInfoData_V::HasWebPermission(long nWebPermission) const
{
   return HasWebPermission(m_dwAttriEx,nWebPermission);
}

BOOL CDBPersonInfoData_V::HasWebPermission(const DWORD & dwAttri,long nWebPermission) const
{
   long lWebPermission = nWebPermission & PERSON_ATTRI_WEB_AND;
   return (dwAttri & lWebPermission) != PERSON_ATTRI_NONE;
}

BOOL CDBPersonInfoData_V::HasTagPermission(const DWORD & dwAttri,long nPermission) const
{
   long lPermission = nPermission & PERSON_TAG_PERMISSON_ALL;
   return (dwAttri & lPermission) != PERSON_ATTRI_NONE;
}

BOOL CDBPersonInfoData_V::HasFilePermission(const DWORD & dwAttri,long nPermission) const
{
   long lPermission = nPermission & PERSON_FILE_PERMISSON_ALL;
   return (dwAttri & lPermission) != PERSON_ATTRI_NONE;
}

void CDBPersonInfoData_V::ClearPhoto()
{
	if (m_pUserPhoto)
	{
		delete m_pUserPhoto;
		m_pUserPhoto = NULL;
	}
}

CDBPersonInfoList_V::CDBPersonInfoList_V()
{

}

CDBPersonInfoList_V::~CDBPersonInfoList_V()
{

}

CDBPersonInfoData_V* CDBPersonInfoList_V::GetItem( int nIndex )
{
	if (nIndex<0||nIndex>=GetCount())
		return NULL;
	return (CDBPersonInfoData_V*)GetAt(FindIndex(nIndex));
}

CDBPersonInfoData_V* CDBPersonInfoList_V::GetItemByUserID( CString strUserID )
{
	CDBPersonInfoData_V * pItem = NULL;
	strUserID.Trim();
	if (!strUserID.IsEmpty())
	{
		for(int i=0;i< GetCount();i++)
		{
			CDBPersonInfoData_V * pObject = GetItem(i);
			if(0 == strUserID.CompareNoCase(pObject->m_strcUserID))
			{
				pItem = pObject;
				break;
			}
		}
	}

	return pItem;
}

CDBPersonInfoData_V* CDBPersonInfoList_V::GetItemByID(int nID)
{
   CDBPersonInfoData_V * pItem = NULL;
   if (0 != nID)
   {
      for(int i=0;i< GetCount();i++)
      {
         CDBPersonInfoData_V * pObject = GetItem(i);
         if(pObject && nID == pObject->m_nID)
         {
            pItem = pObject;
            break;
         }
      }
   }

   return pItem;
}

int CDBPersonInfoList_V::GetIndexByUserID( CString strUserID )
{
	int nSel = -1;
	strUserID.Trim();
	if (!strUserID.IsEmpty())
	{
		for(int i=0;i< GetCount();i++)
		{
			auto pObject = GetItem(i);
			if(strUserID==pObject->m_strcUserID)
			{
				nSel = i;
				break;
			}
		}
	}

	return nSel;
}

void CDBPersonInfoList_V::AddItem( CDBPersonInfoData_V* pItem )
{
	CDBPersonInfoData_V*pData=new CDBPersonInfoData_V;
	pData->Copy(pItem);
	AddHead(pData);
}

void CDBPersonInfoList_V::DeleteItem( int nIndex )
{
	if (nIndex<0||nIndex>GetCount())
		return;
	CDBPersonInfoData_V *pObject=(CDBPersonInfoData_V*)GetItem(nIndex);
	delete pObject;
	pObject=NULL;
	RemoveAt(FindIndex(nIndex));
}

BOOL CDBPersonInfoList_V::GetListFromDB( CADOConn *pADOConn )
{
	BOOL bRet = FALSE;

	ASSERT(pADOConn != NULL);
	Empty();
	if (NULL == pADOConn)
	{
		bRet = FALSE;
	}
	else
	{
		CString strSQL = _T("");
		strSQL.Format(_T("select * from %s"),DB_VIEW_USERINFO);

		bRet = pADOConn->GetRecordSet(strSQL);

		while (!pADOConn->adoEOF())
		{
			CDBPersonInfoData_V oData;
			oData.GetAllDBInfo(pADOConn);

			AddItem(&oData);
			pADOConn->MoveNext();
		}
	}

	return bRet;
}

BOOL CDBPersonInfoList_V::ResetAllPwdExpectAdmin( CADOConn *pADOConn,CString strPwd)
{
	ASSERT(pADOConn != NULL);
	BOOL bRet = TRUE;

	CString strSQL = _T("");
	strSQL.Format(_T("update %s set %s='%s' where lower(%s)<>'%s'"),DB_TABLE_PERSON,DBPerson_key_Pwd,strPwd,DBPerson_key_UserID,_T("admin"));

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

CDBPersonInfoList_V * CDBPersonInfoList_V::Instance()
{
	if(sm_inst.get() == 0)
		sm_inst = shared_ptr<CDBPersonInfoList_V>(new CDBPersonInfoList_V);

	return sm_inst.get();
}

#ifdef USING_GRIDCTRL_MARK
MAP_GridCtrl_AllData CDBPersonInfoList_V::CreateGridData(const CString & strUserDuty/*=_T("")*/,const CString & strTreeCode /*= _T("")*/,BOOL bFilterNoPower /*= FALSE*/)
{
	MAP_GridCtrl_AllData map_all_data;

	int nIndex = 0,nCount = GetCount();
	int nValidCount = 1;
	for (nIndex = 0;nIndex < nCount;nIndex++)
	{
		CDBPersonInfoData_V * pData = GetItem(nIndex);
		if (NULL != pData)
		{
/*
         用一个函数替代了
			//2017/09/06 zhangt 根据权限来显示
			if (strUserDuty == _T("管理员"))
			{
				if (pData->m_strcUserDuty == _T("超级管理员"))
				{
					continue;
				}
			}
			else if (strUserDuty == _T("部门主管"))
			{
				if (pData->m_strcUserDuty == _T("超级管理员")
					||pData->m_strcUserDuty == _T("管理员"))
				{
					continue;
				}
			}
			else if (strUserDuty == _T("办公室职员"))
			{
				if (pData->m_strcUserDuty == _T("超级管理员")
					||pData->m_strcUserDuty == _T("管理员")
					||pData->m_strcUserDuty == _T("部门主管"))
				{
					continue;
				}
			}
			else if (strUserDuty == _T("普通员工"))
			{
				if (pData->m_strcUserDuty == _T("超级管理员")
					||pData->m_strcUserDuty == _T("管理员")
					||pData->m_strcUserDuty == _T("部门主管")
					||pData->m_strcUserDuty == _T("办公室职员"))
				{
					continue;
				}
			}
			//2017/09/06_end
*/

         if (!strTreeCode.IsEmpty() && pData->m_strcTreeCode != strTreeCode)
         {//如果编码不一致  则跳过该数据
            continue;
         }

         if (!HasViewAuthority(strUserDuty,pData->m_strcUserDuty))
         {//如果没有权限查看 则跳过该数据
            continue;
         }

         if (bFilterNoPower)
         {//需要过滤没有权限的用户
            int nFindPos = pData->m_strcUserPower.Find('1');
            if (-1 == nFindPos)
            {
               continue;
            }
         }

			MAP_GridCtrl_RowData map_row_data;
			CString strIndex = _T("");
			strIndex.Format(FORMAT_INT,nValidCount);

			pData->InsertRowData(DBPerson_key_ID			,map_row_data,CB_enum_FieldData_Int,CB_enum_FieldCtrl_Text,FORMAT_INT	,pData->m_nID					);
			pData->InsertRowData(DBPerson_key_TreeCode		,map_row_data, CB_enum_FieldData_Int, CB_enum_FieldCtrl_Text,FORMAT_STRING	,pData->m_strcTreeCode			);
			pData->InsertRowData(DBPerson_key_UserID		,map_row_data,FORMAT_STRING	,pData->m_strcUserID			);
			pData->InsertRowData(DBPerson_key_Pwd			,map_row_data,FORMAT_STRING	,pData->m_strcPassword			);
			pData->InsertRowData(DBPerson_key_UserName		,map_row_data,FORMAT_STRING	,pData->m_strcUserName			);
			pData->InsertRowData(DBPerson_key_UserPower		,map_row_data,FORMAT_STRING	,pData->m_strcUserPower			);
			pData->InsertRowData(DBPerson_key_UserTel		,map_row_data,FORMAT_STRING	,pData->m_strcUserTel			);

			if(pData->m_oledtUserDate.m_status == COleDateTime::valid)
				pData->InsertRowData(DBPerson_key_UserDate		,map_row_data,CB_enum_FieldData_Time,CB_enum_FieldCtrl_DateTime,FORMAT_STRING	,pData->m_oledtUserDate.Format(_T("%Y-%m-%d"))			);// %H:%M:%S
			else
				pData->InsertRowData(DBPerson_key_UserDate		,map_row_data,CB_enum_FieldData_Time,CB_enum_FieldCtrl_DateTime,FORMAT_STRING	,_T(""));
			if(pData->m_oledtUserBorn.m_status == COleDateTime::valid)
				pData->InsertRowData(DBPerson_key_UserBorn		,map_row_data,CB_enum_FieldData_Time,CB_enum_FieldCtrl_DateTime,FORMAT_STRING	,pData->m_oledtUserBorn.Format(_T("%Y-%m-%d"))			);
			else
				pData->InsertRowData(DBPerson_key_UserBorn		,map_row_data,CB_enum_FieldData_Time,CB_enum_FieldCtrl_DateTime,FORMAT_STRING	,_T(""));

			pData->InsertRowData(DBPerson_key_UserMemo		,map_row_data,FORMAT_STRING	,pData->m_strcUserMemo			);
			pData->InsertRowData(DBPerson_key_UserSFZ		,map_row_data,FORMAT_STRING	,pData->m_strcUserSFZ			);
			//pData->InsertRowData(DBPerson_key_UserPhoto	,map_row_data,FORMAT_STRING	,pData->						);
			pData->InsertRowData(DBPerson_key_UserSale		,map_row_data,FORMAT_STRING	,pData->m_strcUserSale			);
			pData->InsertRowData(DBPerson_key_UserDuty		,map_row_data,FORMAT_STRING	,pData->m_strcUserDuty			);
			pData->InsertRowData(DBPerson_key_Addr			,map_row_data,FORMAT_STRING	,pData->m_strcAddr				);

			if(pData->m_oledtInTime.m_status == COleDateTime::valid)
				pData->InsertRowData(DBPerson_key_InTime		,map_row_data,CB_enum_FieldData_Time,CB_enum_FieldCtrl_DateTime,FORMAT_STRING	,pData->m_oledtInTime.Format(_T("%Y-%m-%d"))			);
			else
				pData->InsertRowData(DBPerson_key_InTime		,map_row_data,CB_enum_FieldData_Time,CB_enum_FieldCtrl_DateTime,FORMAT_STRING	,_T(""));
			

			if(0 == pData->m_niOutFlag)
			{
				//pData->InsertRowData(DBPerson_key_OutFlag		,map_row_data,enum_FieldData_Int,enum_FieldCtrl_Text	,FORMAT_INT	,pData->m_niOutFlag				);
				pData->InsertRowData(DBPerson_key_OutFlag			,map_row_data,FORMAT_STRING	,_T("正常"));
				pData->InsertRowData(DBPerson_key_OutTime		,map_row_data,CB_enum_FieldData_Time,CB_enum_FieldCtrl_DateTime,FORMAT_STRING	,_T(""));
			}
			else
			{
				pData->InsertRowData(DBPerson_key_OutFlag			,map_row_data,FORMAT_STRING	,_T("注销"));

				if(pData->m_oledtOutTime.m_status == COleDateTime::valid)
					pData->InsertRowData(DBPerson_key_OutTime		,map_row_data,CB_enum_FieldData_Time,CB_enum_FieldCtrl_DateTime,FORMAT_STRING	,pData->m_oledtOutTime.Format(_T("%Y-%m-%d"))			);
				else
					pData->InsertRowData(DBPerson_key_OutTime		,map_row_data,CB_enum_FieldData_Time,CB_enum_FieldCtrl_DateTime,FORMAT_STRING	,_T(""));
			}
			
			pData->InsertRowData(DBDataDic_key_ItemName		,map_row_data,FORMAT_STRING	,pData->m_strcTreeName			);

         pData->InsertRowData(DBPerson_key_AttriEx		,map_row_data,_T("%ld")	,pData->m_dwAttriEx			);
         pData->InsertRowData(DBPerson_key_iSalesman		,map_row_data,FORMAT_STRING	,pData->m_iSalesman==1?_T("是"):_T("否"));
         pData->InsertRowData(DBPerson_key_cUserRole		,map_row_data,FORMAT_STRING	,pData->m_strUserRole);
         pData->InsertRowData(DBPerson_key_cUserGroup		,map_row_data,FORMAT_STRING	,pData->m_strGroup);

			map_all_data.insert(make_pair(nValidCount,map_row_data));
			//行数据插入所有数据中

			nValidCount++;
		}
	}


	return map_all_data;
}

BOOL CDBPersonInfoList_V::HasViewAuthority(const CString & strViewerDuty,const CString & strUserDuty)
{
   BOOL bAuthority = TRUE;
   if (strViewerDuty == _T("管理员"))
   {
      if (strUserDuty == _T("超级管理员"))
      {
         bAuthority = FALSE;
      }
   }
   else if (strViewerDuty == _T("部门主管"))
   {
      if (strUserDuty == _T("超级管理员")
         ||strUserDuty == _T("管理员"))
      {
         bAuthority = FALSE;
      }
   }
   else if (strViewerDuty == _T("办公室职员"))
   {
      if (strUserDuty == _T("超级管理员")
         ||strUserDuty == _T("管理员")
         ||strUserDuty == _T("部门主管"))
      {
         bAuthority = FALSE;
      }
   }
   else if (strViewerDuty == _T("普通员工"))
   {
      if (strUserDuty == _T("超级管理员")
         ||strUserDuty == _T("管理员")
         ||strUserDuty == _T("部门主管")
         ||strUserDuty == _T("办公室职员"))
      {
         bAuthority = FALSE;
      }
   }

   return bAuthority;
}

//获取工序员工信息		by WangZY 2018/10/30
BOOL CDBPersonInfoList_V::GetGongxuUserInfo(__in CADOConn* pADOConn, 
   __out map<int,CString>& map_gx_sort, 
   __out map<CString,map<CString,CString>>& map_Gongxu_user)
{
   ASSERT(pADOConn != NULL);
   map_gx_sort.clear();
   map_Gongxu_user.clear();
   CString strSql = _T("select c.iSortID,c.cGXName,a.cUserID,a.cUserName from Userinfo as a\
                       inner join TreeClass as b on a.cTreeCode = b.cTreeCode\
                       inner join Gongxu as c on c.cTreeCode = a.cTreeCode\
                       where b.cTreeCate = '部门分类'\
                       order by c.iSortID");

   pADOConn->GetRecordSet(strSql);
   while(!pADOConn->adoEOF())
   {
      int iSortID = pADOConn->GetValueInt(_T("iSortID"));
      CString strGx = pADOConn->GetValueString(_T("cGXName"));
      CString strcUserID = pADOConn->GetValueString(_T("cUserID"));
      CString strcUserName = pADOConn->GetValueString(_T("cUserName"));

      map_gx_sort.insert(make_pair(iSortID,strGx));

      auto itr_gx = map_Gongxu_user.find(strGx);
      if (itr_gx == map_Gongxu_user.end())
      {
         map_Gongxu_user.insert(make_pair(strGx,map<CString,CString>()));
         itr_gx = map_Gongxu_user.find(strGx);
      }
      else
      {
         auto itr_usr = itr_gx->second.find(strcUserID);
         if (itr_usr == itr_gx->second.end())
         {
            itr_gx->second.insert(make_pair(strcUserID,strcUserName));
         }
      }
      pADOConn->MoveNext();
   }
   return TRUE;
}

#endif // 3

void CDBPersonInfoList_V::GetUsrIDNameGroupCodeByRole(map<CString,map<CString,CString>>& mapUserInfo)
{
   mapUserInfo.clear();
   int nIndex = 0,nCount = GetCount();
   for (;nIndex < nCount;++nIndex)
   {
      auto pItem = GetItem(nIndex);
      if (NULL != pItem)
      {
         auto itr_treeCode = mapUserInfo.find(pItem->m_strUserRole);
         if (itr_treeCode == mapUserInfo.end())
         {
            map<CString,CString> map_user_id;
            mapUserInfo.insert(make_pair(pItem->m_strUserRole,map_user_id));
            itr_treeCode = mapUserInfo.find(pItem->m_strUserRole);
         }
         itr_treeCode->second.insert(make_pair(pItem->m_strcUserID,pItem->m_strcUserName));
      }
   }
}

void CDBPersonInfoList_V::GetUserGroupInfoByRole(map<CString/*角色*/,vector<CString>/*用户组*/>& mapUserInfo)
{
   mapUserInfo.clear();
   int nIndex = 0,nCount = GetCount();
   for (;nIndex < nCount;++nIndex)
   {
      auto pItem = GetItem(nIndex);
      if (NULL != pItem && !pItem->m_strGroup.IsEmpty())
      {
         auto itr_treeCode = mapUserInfo.find(pItem->m_strUserRole);
         if (itr_treeCode == mapUserInfo.end())
         {
            vector<CString> vecUser;
            mapUserInfo.insert(make_pair(pItem->m_strUserRole,vecUser));
            itr_treeCode = mapUserInfo.find(pItem->m_strUserRole);
         }
         itr_treeCode->second.push_back(pItem->m_strGroup);
      }
   }
   //因为本来就要排序所以放在外面处理了
   for (auto it = mapUserInfo.begin();it != mapUserInfo.end();++it)
   {
      //排序 去重
      std::sort(it->second.begin(),it->second.end());
      auto itUni = std::unique(it->second.begin(),it->second.end());
      it->second.erase(itUni,it->second.end());
   }
}

