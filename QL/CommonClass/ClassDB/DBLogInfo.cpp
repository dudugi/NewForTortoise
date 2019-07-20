#include "StdAfx.h"
#include "DBLogInfo.h"
#include "DBPersonInfo_V.h"
//#include "DBTableNameSet.h"

IMPLEMENT_SERIAL(CDBLogInfoData,  CDataMid, 1)
IMPLEMENT_SERIAL(CDBLogInfoList,  CDataListMid, 1)

std::shared_ptr<CDBLogInfoData> CDBLogInfoData::sm_inst;
std::shared_ptr<CDBLogInfoList> CDBLogInfoList::sm_inst;

CDBLogInfoData::CDBLogInfoData()
{
	ResetData();
} 

CDBLogInfoData::~CDBLogInfoData()
{
}

void CDBLogInfoData::ResetData()
{
	m_nID = 0;
	m_strCate = _T("");
	m_strCode = _T("");
	m_dDate = COleDateTime::GetCurrentTime();
	m_strMaker = _T("");
	m_strType = _T("");
	m_strAction = _T("");
	m_strInterFace = _T("");
	m_strProject = _T("");
   m_strMacAddr = _T("");
	SetDataType(DAT_LOG);
}
void CDBLogInfoData::EmptyLogAction()
{
   m_strCate = _T("");
   m_strCode = _T("");
   m_strType = _T("");
   m_strAction = _T("");
   m_strInterFace = _T("");
}

void CDBLogInfoData::Copy(CDBLogInfoData *pData)
{
	ASSERT(pData != NULL);
	CDataMid::Copy(pData);
	m_nID		=	pData->m_nID;
	m_strCate	=	pData->m_strCate;	
	m_strCode	=	pData->m_strCode;	
	m_dDate		=	pData->m_dDate;	
	m_strMaker	=	pData->m_strMaker;
	m_strType	=	pData->m_strType;	
	m_strAction	=	pData->m_strAction;
	m_strInterFace = pData->m_strInterFace;
	m_strProject = pData->m_strProject;
   m_strMacAddr = pData->m_strMacAddr;
}

void CDBLogInfoData::SetLogData( CString strCate,CString strCode,CString strMaker,CString strType,CString strAction ,CString strInterFaceName,CString strProjectName,CString strMacAddr)
{
   strMaker.Trim();
   strCate.Trim();
   strCode.Trim();
   strType.Trim();
   strAction.Trim();
   strInterFaceName.Trim();
   strProjectName.Trim();
   strMacAddr.Trim();

   ASSERT(!strMaker.IsEmpty());

   m_strCate	= strCate;
   m_strType	= strType;
   m_strCode	= strCode;
   m_strMaker	= strMaker;
   m_strAction	= strAction;
   m_strInterFace = strInterFaceName;
   m_strProject = strProjectName;
   m_strMacAddr = strMacAddr;
}

void CDBLogInfoData::Serialize(CArchive& ar)
{
	CDataMid::Serialize(ar);//父类函数

	int nTagSize = 0;
	CString strName;
	int nNameSize;

	ar.Flush();
	if (ar.IsStoring())
	{

		MySerial.SaveDataInt(ar,_T("THELOGID"),m_nID);
		MySerial.SaveDataStr(ar,_T("TLOGCATE"),m_strCate);
		MySerial.SaveDataStr(ar,_T("TLOGTYPE"),m_strType);
		MySerial.SaveColeDateTime(ar,_T("TLOGDATE"),m_dDate);
		MySerial.SaveDataStr(ar,_T("TLOGCODE"),m_strCode);
		MySerial.SaveDataStr(ar,_T("LOGMAKER"),m_strMaker);
		MySerial.SaveDataStr(ar,_T("LOACTION"),m_strAction);

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
			else if (strName == _T("THELOGID"))
			{
				ar >> nTagSize >> m_nID;
			}
			else if (strName == _T("TLOGCATE"))
			{
				ar >>nTagSize >> m_strCate;
			}
			else if (strName == _T("TLOGTYPE"))
			{
				ar >>nTagSize >> m_strCode;
			}
			else if (strName == _T("TLOGDATE"))
			{
				ar >>nTagSize >> m_dDate;
			}
			else if (strName == _T("TLOGCODE"))
			{
				ar >>nTagSize >> m_strMaker;
			}
			else if (strName == _T("LOGMAKER"))
			{
				ar >>nTagSize >> m_strType;
			}
			else if (strName == _T("LOACTION"))
			{
				ar >>nTagSize >> m_strAction;
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

BOOL CDBLogInfoData::GetAllDBInfo(CADOConn *pADOConn)
{
	ASSERT(pADOConn != NULL);

	BOOL bRet = TRUE;

	if (NULL == pADOConn)
	{
		bRet = FALSE;
	}
	else
	{
		m_nID			=	pADOConn->GetValueInt(DBWorkLog_key_ID);
		m_strCate		=	pADOConn->GetValueString(DBWorkLog_key_Cate);
		m_strCode		=	pADOConn->GetValueString(DBWorkLog_key_Code);
		m_dDate			=	pADOConn->GetValueDate(DBWorkLog_key_Date);
		m_strMaker		=	pADOConn->GetValueString(DBWorkLog_key_Maker);
		m_strType		=	pADOConn->GetValueString(DBWorkLog_key_Type);
		m_strAction		=	pADOConn->GetValueString(DBWorkLog_key_Detail);
		m_strInterFace		=	pADOConn->GetValueString(DBWorkLog_key_InterFace);
		m_strProject		=	pADOConn->GetValueString(DBWorkLog_key_ProjectName);
      m_strMacAddr   = pADOConn->GetValueString(DBWorkLog_key_MacAddr);

		bRet = TRUE;
	}

	return bRet;
}

BOOL CDBLogInfoData::InsertAllDBInfoByAct(CADOConn *pADOConn)
{
	ASSERT(pADOConn != NULL);
	ASSERT(!m_strMaker.IsEmpty());

	BOOL bRet = TRUE;

	CString strSQL = _T(""),strFormat = _T(""),strValue = _T("");
   //					 1 ,2 ,3 ,4 ,5 ,6, 7, 8
   strFormat.Format(_T("%s,%s,%s,%s,%s,%s,%s,%s,%s"),
      DBWorkLog_key_Cate	,//1
      DBWorkLog_key_Code	,//2
      DBWorkLog_key_Date	,//3
      DBWorkLog_key_Maker	,//4
      DBWorkLog_key_Type	,//5
      DBWorkLog_key_Detail, //6
      DBWorkLog_key_InterFace,//7
      DBWorkLog_key_ProjectName,//8
      DBWorkLog_key_MacAddr    //9
      );
   //					1   , 2  ,3 ,4   ,5   ,6,   7, 8
   strValue.Format(_T("'%s','%s',%s,'%s','%s','%s','%s','%s','%s'"),
      m_strCate,		//1
      m_strCode,		//2
      DBS_GETDATESTR,	//3
      m_strMaker,		//4
      m_strType,		//5
      m_strAction,	//6
      m_strInterFace,//7
      m_strProject,//8
      m_strMacAddr
      );

	strSQL.Format(_T("insert into %s(%s) values(%s)"),DB_TABLE_LOG,strFormat,strValue);

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

CString CDBLogInfoData::GetSQLInsertAllDBInfoByAct()
{
   ASSERT(!m_strMaker.IsEmpty());

   CString strSQL = _T(""),strFormat = _T(""),strValue = _T("");
   //					 1 ,2 ,3 ,4 ,5 ,6, 7, 8
   strFormat.Format(_T("%s,%s,%s,%s,%s,%s,%s,%s,%s"),
      DBWorkLog_key_Cate	,//1
      DBWorkLog_key_Code	,//2
      DBWorkLog_key_Date	,//3
      DBWorkLog_key_Maker	,//4
      DBWorkLog_key_Type	,//5
      DBWorkLog_key_Detail, //6
      DBWorkLog_key_InterFace,//7
      DBWorkLog_key_ProjectName,//8
      DBWorkLog_key_MacAddr    //9
      );
   //					1   , 2  ,3 ,4   ,5   ,6,   7, 8
   strValue.Format(_T("'%s','%s',%s,'%s','%s','%s','%s','%s','%s'"),
      m_strCate,		//1
      m_strCode,		//2
      DBS_GETDATESTR,	//3
      m_strMaker,		//4
      m_strType,		//5
      m_strAction,	//6
      m_strInterFace,//7
      m_strProject,//8
      m_strMacAddr
      );

   strSQL.Format(_T("insert into %s(%s) values(%s)"),DB_TABLE_LOG,strFormat,strValue);

   
   return strSQL;
}
BOOL CDBLogInfoData::InsertAllDBInfoWithLocalTime( CADOConn *pADOConn )
{
	ASSERT(pADOConn != NULL);
	ASSERT(!m_strMaker.IsEmpty());

	BOOL bRet = TRUE;

	CString strSQL = _T(""),strFormat = _T(""),strValue = _T("");
   //					 1 ,2 ,3 ,4 ,5 ,6
   strFormat.Format(_T("%s,%s,%s,%s,%s,%s,%s,%s,'%s'"),
      DBWorkLog_key_Cate	,//1
      DBWorkLog_key_Code	,//2
      DBWorkLog_key_Date	,//3
      DBWorkLog_key_Maker	,//4
      DBWorkLog_key_Type	,//5
      DBWorkLog_key_Detail, //6
      DBWorkLog_key_InterFace,//7
      DBWorkLog_key_ProjectName,//8
      DBWorkLog_key_MacAddr
      );
   //					
   strValue.Format(_T("'%s','%s','%s','%s','%s','%s','%s','%s','%s','%s'"),
      m_strCate,	//1
      m_strCode,	//2
      m_dDate.Format(_T("%Y-%m-%d %H:%M:%S")),	//3
      m_strMaker,	//4
      m_strType,	//5
      m_strAction,	//6
      m_strInterFace,//7
      m_strProject,//8
      m_strMacAddr
      );
	strSQL.Format(_T("insert into %s(%s) values(%s)"),DB_TABLE_LOG,strFormat,strValue);

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
CString CDBLogInfoData::GetSQLInsertAllDBInfoWithLocalTime()
{
   ASSERT(!m_strMaker.IsEmpty());

   CString strSQL = _T(""),strFormat = _T(""),strValue = _T("");
   //					 1 ,2 ,3 ,4 ,5 ,6
   strFormat.Format(_T("%s,%s,%s,%s,%s,%s,%s,%s,'%s'"),
      DBWorkLog_key_Cate	,//1
      DBWorkLog_key_Code	,//2
      DBWorkLog_key_Date	,//3
      DBWorkLog_key_Maker	,//4
      DBWorkLog_key_Type	,//5
      DBWorkLog_key_Detail, //6
      DBWorkLog_key_InterFace,//7
      DBWorkLog_key_ProjectName,//8
      DBWorkLog_key_MacAddr
      );
   //					
   strValue.Format(_T("'%s','%s','%s','%s','%s','%s','%s','%s','%s','%s'"),
      m_strCate,	//1
      m_strCode,	//2
      m_dDate.Format(_T("%Y-%m-%d %H:%M:%S")),	//3
      m_strMaker,	//4
      m_strType,	//5
      m_strAction,	//6
      m_strInterFace,//7
      m_strProject,//8
      m_strMacAddr
      );
   strSQL.Format(_T("insert into %s(%s) values(%s)"),DB_TABLE_LOG,strFormat,strValue);      
   return strSQL;
}

BOOL CDBLogInfoData::DelAllDBInfoByAct(CADOConn *pADOConn)
{
	//ASSERT(pADOConn != NULL);
	//ASSERT(!m_strMaker.IsEmpty());

	//BOOL bRet = TRUE;

	//CString strSQL = _T("");
	//strSQL.Format(_T("delete from %s where %s='%s'"),DB_TABLE_LOG,DBWorkLog_key_Maker,m_strMaker);

	//if (pADOConn->ExecuteSQL(strSQL))
	//{
	//	bRet = TRUE;
	//}
	//else
	//{
	//	bRet = FALSE;
	//}

	return FALSE;
}

void CDBLogInfoData::TestOperatLog(table_log_map &mapLog, int nRowID,CString strID,CString strFiledID, CString strFiledName,CString strNewValue, CString strOldValue)
{
   if ( strNewValue == strOldValue) //判断新修改的字段的值是否跟旧字段的值相等
   {
      return;
   }
   auto itr = mapLog.find(nRowID); //在map中寻找是否有当前修改的行。
   if (itr == mapLog.end())        //没有就将新的内容加入到map中
   {
      table_log_map_row newMap;
      new_and_old structNew;
      structNew.strOldValue = strOldValue;
      structNew.strNewValue = strNewValue;
      structNew.strFiledName = strFiledName;
      structNew.strID = strID;
      newMap[strFiledID] = structNew;
      mapLog[nRowID] = newMap;
   }     
   else                             
   {
      auto itr_field = itr->second.find(strFiledID);//找到了该条数据，要判断该字段是否在这条数据中
      if (itr_field == itr->second.end())           //如果该字段不存在，加入该字段
      {
         new_and_old structNew;
         structNew.strOldValue = strOldValue;
         structNew.strNewValue = strNewValue;
         structNew.strFiledName = strFiledName;
         structNew.strID = strID;
         itr->second[strFiledID] = structNew;
      }
      else
      {
         if (strNewValue == itr_field->second.strOldValue)//如果该字段存在，判断新的值跟旧的值是否相等，相等就在map中删除该条数据
         {
            itr->second.erase(itr_field);
         }
         else
         {
            itr_field->second.strNewValue = strNewValue; //不相等就修改字段的值。
         }
      }
   }
}
CString CDBLogInfoData::WriteChangeLog(table_log_map &map_change)
{
   CString strActLog = _T("");
   auto itr_all = map_change.begin();
   for (;itr_all != map_change.end(); ++itr_all)
   {
      table_log_map_row row_map = itr_all->second;
      auto itr_row = row_map.begin();
      strActLog += _T("(ID:")+itr_row->second.strID + _T(")");
      for (;itr_row != row_map.end(); ++itr_row)
      {
         CString str;
         str.Format(_T("%s:%s,"),itr_row->second.strFiledName,itr_row->second.strNewValue);
         strActLog += str;
      }
   }
   return strActLog;
}

CString CDBLogInfoData::GetInsertSQL()
{
	CString strSQL = _T(""),strFormat = _T(""),strValue = _T("");
   //					 1 ,2 ,3 ,4 ,5 ,6
   strFormat.Format(_T("%s,%s,%s,%s,%s,%s,%s,%s,%s"),
      DBWorkLog_key_Cate	,//1
      DBWorkLog_key_Code	,//2
      DBWorkLog_key_Date	,//3
      DBWorkLog_key_Maker	,//4
      DBWorkLog_key_Type	,//5
      DBWorkLog_key_Detail, //6
      DBWorkLog_key_InterFace,//7
      DBWorkLog_key_ProjectName,//8
      DBWorkLog_key_MacAddr   //9
      );
   //					1   , 2  ,3 ,4   ,5   ,6
   strValue.Format(_T("'%s','%s',%s,'%s','%s','%s','%s','%s','%s'"),
      m_strCate,		//1
      m_strCode,		//2
      DBS_GETDATESTR,	//3
      m_strMaker,		//4
      m_strType,		//5
      m_strAction,	//6
      m_strInterFace,//7
      m_strProject,//8
      m_strMacAddr //9
      );

	strSQL.Format(_T("insert into %s(%s) values(%s)"),DB_TABLE_LOG,strFormat,strValue);

	return strSQL;
}

CDBLogInfoData * CDBLogInfoData::Instance()
{
	if(sm_inst.get() == 0)
		sm_inst = shared_ptr<CDBLogInfoData>(new CDBLogInfoData);

	return sm_inst.get();
}

//CDBLogInfoList
CDBLogInfoList::CDBLogInfoList()
{
}

CDBLogInfoList::~CDBLogInfoList()
{
}

CDBLogInfoData*  CDBLogInfoList::GetItem(int nIndex)
{
	if (nIndex<0||nIndex>=GetCount())
		return NULL;
	return (CDBLogInfoData*)GetAt(FindIndex(nIndex));
}

void CDBLogInfoList:: AddItem(CDBLogInfoData* pItem)
{
	CDBLogInfoData*pData=new CDBLogInfoData;
	pData->Copy(pItem);
	AddTail(pData);
}

void CDBLogInfoList::DeleteItem(int nIndex)
{
	if (nIndex<0||nIndex>GetCount())
		return;
	CDBLogInfoData *pObject=(CDBLogInfoData*)GetItem(nIndex);
	delete pObject;
	pObject=NULL;
	RemoveAt(FindIndex(nIndex));
}


CDBLogInfoList * CDBLogInfoList::Instance()
{
	if(sm_inst.get() == 0)
		sm_inst = shared_ptr<CDBLogInfoList>(new CDBLogInfoList);

	return sm_inst.get();
}

std::map<CString,CDBLogInfoData*> CDBLogInfoList::GetOrderLogByOrderCode(CADOConn *pADOConn,CString strOrderCode)
{
	ASSERT(pADOConn != NULL);
	if (strOrderCode == _T(""))
		return map<CString,CDBLogInfoData*>();

	map<CString,CDBLogInfoData*> mapData;
	CString strSQL;
	strSQL.Format(_T("select * from %s where %s = '%s';"),DB_TABLE_LOG,DBWorkLog_key_Code,strOrderCode);
	pADOConn->GetRecordSet(strSQL);
	int nIndex = 0;
	while (!pADOConn->adoEOF())
	{
		CDBLogInfoData* pData = new CDBLogInfoData;
		pData->GetAllDBInfo(pADOConn);
		pADOConn->MoveNext();
		CString strIndex;
		strIndex.Format(FORMAT_INT,nIndex++);
		mapData.insert(make_pair(strIndex,pData));
	}
	return mapData;
}

//获取log界面需要的数据
void CDBLogInfoList::GetListData(CADOConn *pADOConn , CString startTime , CString endTime , CString strUser , CString projectName, CString strKey , std::vector<CString> strOpTypeLst)
{
	CString strUserSql = _T("") , strSQL = _T("") , strKeySql = _T("") , strOpTypeSql = _T("");
	if (strUser != _T("全部"))
	{
		strUserSql.Format(_T(" and cMaker = '%s' ") , strUser); 
	}

	if (!strKey.IsEmpty())
	{
      strKeySql.Format(_T(" and ((%s like '%%%s%%') or \
                          (%s like '%%%s%%') or \
                          (%s like '%%%s%%') or \
                          (%s like '%%%s%%') or \
                          (%s like '%%%s%%') or \
                          (%s like '%%%s%%') or \
                          (%s like '%%%s%%') or \
                          (%s like '%%%s%%'))") , 
                          DBWorkLog_key_Cate ,strKey ,  
                          DBWorkLog_key_Code ,strKey ,  
                          DBWorkLog_key_Date ,strKey ,  
                          DBWorkLog_key_Maker ,strKey ,  
                          DBWorkLog_key_Type ,strKey ,  
                          DBWorkLog_key_Detail ,strKey ,  
                          DBWorkLog_key_InterFace ,strKey ,
                          DBWorkLog_key_MacAddr , strKey);
   }


	if ( !strOpTypeLst.empty())
	{
		CString str = _T("");
		for (size_t i = 0; i < strOpTypeLst.size(); i++)
		{
			str += _T("'") + strOpTypeLst[i] + _T("'");
			
			if (i != (strOpTypeLst.size() - 1))
			{
				str += + _T(" , ");
			}
		}
		strOpTypeSql.Format(_T(" and ( %s in ( %s ) )") , DBWorkLog_key_Type , str);
	}

	strSQL.Format(_T("select * from %s where %s between '%s' and '%s' %s %s %s and cProjectName = '%s' order by %s desc")
		,DB_TABLE_LOG
		,DBWorkLog_key_Date
		,startTime
		,endTime
		,strUserSql
		,strKeySql
		,strOpTypeSql
		,projectName
		,DBWorkLog_key_Date);

	pADOConn->GetRecordSet(strSQL);
	while(!/*theApp.m_pADOConn*/pADOConn->adoEOF())
	{
		CDBLogInfoData oData;
		oData.GetAllDBInfo(/*theApp.m_pADOConn*/pADOConn);
		AddItem(&oData);
		pADOConn->MoveNext();
	}
}
void CDBLogInfoList::SetCateEnglishToChinese(__in std::map<CString , CString> tableNameMap)
{
   m_tableNameMap = tableNameMap;
}
#ifdef USING_GRIDCTRL_MARK
MAP_GridCtrl_AllData CDBLogInfoList::CreatrGridData(CADOConn *pADOConn)
{
	MAP_GridCtrl_AllData  map_all_data;

	std::map<CString , CString> nameMap;
	CDBPersonInfoList_V *pLst = CDBPersonInfoList_V::Instance();
	for (int i = 0; i < pLst->GetCount();i++)
	{
		CDBPersonInfoData_V *pObjPerson = pLst->GetItem(i);
		nameMap[pObjPerson->m_strcUserID] = pObjPerson->m_strcUserName;
	}

	int nValidCount = 1;
	for (int i = 0; i < GetCount(); i++)
	{
		CDBLogInfoData * pData = GetItem(i);
		if (NULL != pData)
		{
			CString userName;
			MAP_GridCtrl_RowData map_row_data;
			if (nameMap[pData->m_strMaker].IsEmpty() )
			{
				userName = pData->m_strMaker;
			}
			else
			{
				userName.Format( _T("%s(%s)") , nameMap[pData->m_strMaker] , pData->m_strMaker);
			}

			S_GridCtrl_FieldData s_filed_UserName;
			s_filed_UserName.strValue = userName;
			s_filed_UserName.fieldDataType = CB_enum_FieldData_CString;
			s_filed_UserName.fieldCtrlType = CB_enum_FieldCtrl_Text;
			map_row_data.insert(make_pair(DBWorkLog_key_Maker,s_filed_UserName));

			S_GridCtrl_FieldData s_filed_Type;
			s_filed_Type.strValue = pData->m_strType;
			s_filed_Type.fieldDataType = CB_enum_FieldData_CString;
			s_filed_Type.fieldCtrlType = CB_enum_FieldCtrl_Text;
			map_row_data.insert(make_pair(DBWorkLog_key_Type,s_filed_Type));

         if (m_tableNameMap.size() > 0)
         {
            auto it = m_tableNameMap.find(pData->m_strCate);
            if (it != m_tableNameMap.end())
            {
               pData->m_strCate = it->second;
            }
         }

			S_GridCtrl_FieldData s_filed_Cate;
			s_filed_Cate.strValue = pData->m_strCate;
			s_filed_Cate.fieldDataType = CB_enum_FieldData_CString;
			s_filed_Cate.fieldCtrlType = CB_enum_FieldCtrl_Text;
			map_row_data.insert(make_pair(DBWorkLog_key_Cate,s_filed_Cate));


			S_GridCtrl_FieldData s_filed_Interface;
			s_filed_Interface.strValue = pData->m_strInterFace;
			s_filed_Interface.fieldDataType = CB_enum_FieldData_CString;
			s_filed_Interface.fieldCtrlType = CB_enum_FieldCtrl_Text;
			map_row_data.insert(make_pair(DBWorkLog_key_InterFace,s_filed_Interface));

			S_GridCtrl_FieldData s_filed_Code;
			s_filed_Code.strValue = pData->m_strCode;
			s_filed_Code.fieldDataType = CB_enum_FieldData_CString;
			s_filed_Code.fieldCtrlType = CB_enum_FieldCtrl_Text;
			map_row_data.insert(make_pair(DBWorkLog_key_Code,s_filed_Code));



			S_GridCtrl_FieldData s_filed_Detail;
			s_filed_Detail.strValue = pData->m_strAction;
			s_filed_Detail.fieldDataType = CB_enum_FieldData_CString;
			s_filed_Detail.fieldCtrlType = CB_enum_FieldCtrl_Text;
			map_row_data.insert(make_pair(DBWorkLog_key_Detail,s_filed_Detail));

			S_GridCtrl_FieldData s_filed_Date;
			s_filed_Date.strValue = pData->m_dDate.Format(_T("%Y-%m-%d %H:%M:%S"));
			s_filed_Date.fieldDataType = CB_enum_FieldData_CString;
			s_filed_Date.fieldCtrlType = CB_enum_FieldCtrl_Text;
			map_row_data.insert(make_pair(DBWorkLog_key_Date , s_filed_Date));

         S_GridCtrl_FieldData s_filed_MacAddr;
         s_filed_MacAddr.strValue = pData->m_strMacAddr;
         s_filed_MacAddr.fieldDataType = CB_enum_FieldData_CString;
         s_filed_MacAddr.fieldCtrlType = CB_enum_FieldCtrl_Text;
         map_row_data.insert(make_pair(DBWorkLog_key_MacAddr , s_filed_MacAddr));

			//行数据插入所有数据中
			map_all_data.insert(make_pair(nValidCount,map_row_data));		

			nValidCount++;
		}
	}
	return map_all_data;
}

#endif
