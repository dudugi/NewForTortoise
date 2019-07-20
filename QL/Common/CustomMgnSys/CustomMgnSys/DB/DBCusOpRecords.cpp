#include "StdAfx.h"
#include "DBCusOpRecords.h"
#include "CDBFieldDefine.h"
#include "ADOConn/ADOConn.h"
#include "MapInfoOpt.h"
#include "ClassData/CDataTableFieldDefine.h"
#include "rnstring.h"
#include "MyEncrypt.h"
#include "DBCustomer.h"

IMPLEMENT_SERIAL(CDBCusOpRecordsData,  CObject, 1)
IMPLEMENT_SERIAL(CDBCusOpRecordsList,  CObList, 1)

std::shared_ptr<CDBCusOpRecordsData> CDBCusOpRecordsData::sm_inst;
std::shared_ptr<CDBCusOpRecordsList> CDBCusOpRecordsList::sm_inst;


CDBCusOpRecordsData::CDBCusOpRecordsData()
{
	ResetData();
} 

CDBCusOpRecordsData::~CDBCusOpRecordsData()
{
}

void CDBCusOpRecordsData::operator=( CDBCusOpRecordsData *pData )
{
	Copy(pData);
}

CDBCusOpRecordsData * CDBCusOpRecordsData::Instance()
{
	if(sm_inst.get() == 0)
		sm_inst = std::shared_ptr<CDBCusOpRecordsData>(new CDBCusOpRecordsData);
	return sm_inst.get();
}

void CDBCusOpRecordsData::ResetData()
{
   m_nID = 0;	
   m_strCusCode = _T("");	//客户ID
   m_strCusName= _T("");	//客户名称
   m_strCusAddress= _T("");	//客户地址
   m_strCusPhone= _T("");	//电话
   m_strCusContacts= _T("");	//联系人
   m_strcPDMVersion= _T("");	//PDM版本
   m_strProvince= _T("");	//客户地址
   m_isLocalDB = 0;
   m_strServerPerson= _T("");//服务人员
   m_iClientNum = 0;//客户端数量
   m_strMemo= _T("");//备注

   m_cDbServerName= _T("");	//数据库名称
   m_cDbServerIP= _T("");	//数据库IP
   m_iDbServerPort=0;	//数据库端口
   m_cDbAccount= _T("");	//登录账户
   m_cDbPassword= _T("");	//登录密码

   m_strCusCode= _T("");	   //客户编号
   
   m_cBeginTime= _T("");	//开始时间
   m_cTime= _T("");	//到期时间
   m_cPerson= _T("");	//身份信息
   m_cModeData= _T("");	//功能模块

   m_fChongZhiJE = 0;
   m_cOpType = _T("");
}

void CDBCusOpRecordsData::Copy(CDBCusOpRecordsData *pData)
{
	ASSERT(pData != NULL);
	//CDataMid::Copy(pData);

   m_nID = pData->m_nID;	
   m_strCusCode= pData->m_strCusCode;	//客户ID
   m_strCusName= pData->m_strCusName;	//客户名称
   m_strCusAddress= pData->m_strCusAddress;	//客户地址
   m_strCusPhone= pData->m_strCusPhone;	//电话
   m_strCusContacts= pData->m_strCusContacts;	//联系人
   m_strcPDMVersion= pData->m_strcPDMVersion;	//PDM版本
   m_strProvince= pData->m_strProvince;	//客户地址   
   m_isLocalDB = pData->m_isLocalDB;
   m_strServerPerson = pData->m_strServerPerson;//服务人员
   m_iClientNum = pData->m_iClientNum;//客户端数量
   m_strMemo = pData->m_strMemo;//备注

   m_cDbServerName= pData->m_cDbServerName;	//数据库名称
   m_cDbServerIP= pData->m_cDbServerIP;	//数据库IP
   m_iDbServerPort= pData->m_iDbServerPort;	//数据库端口
   m_cDbAccount= pData->m_cDbAccount;	//登录账户
   m_cDbPassword= pData->m_cDbPassword;	//登录密码


   m_cBeginTime=  pData->m_cBeginTime;	//开始时间
   m_cTime=  pData->m_cTime;	//到期时间
   m_cPerson=  pData->m_cPerson;	//身份信息
   m_cModeData=  pData->m_cModeData;	//功能模块

   m_fChongZhiJE = pData->m_fChongZhiJE;
   m_cOpType = pData->m_cOpType;
}

void CDBCusOpRecordsData::Copy(CDBVCustomerInfoData *pData)
{
   ASSERT(pData != NULL);
   m_strCusCode= pData->m_strCusCode;	//客户ID
   m_strCusName= pData->m_strCusName;	//客户名称
   m_strCusAddress= pData->m_strCusAddress;	//客户地址
   m_strCusPhone= pData->m_strCusPhone;	//电话
   m_strCusContacts= pData->m_strCusContacts;	//联系人
   m_strcPDMVersion= pData->m_strcPDMVersion;	//PDM版本
   m_strProvince= pData->m_strProvince;	//客户地址   
   m_isLocalDB = pData->m_isLocalDB;
   m_strServerPerson = pData->m_strServerPerson;//服务人员
   m_iClientNum = pData->m_iClientNum;//客户端数量
   m_strMemo = pData->m_strMemo;//备注

   m_cDbServerName= pData->m_cDbServerName;	//数据库名称
   m_cDbServerIP= pData->m_cDbServerIP;	//数据库IP
   m_iDbServerPort= pData->m_iDbServerPort;	//数据库端口
   m_cDbAccount= pData->m_cDbAccount;	//登录账户
   m_cDbPassword= pData->m_cDbPassword;	//登录密码

   m_cBeginTime=  pData->m_cBeginTime;	//开始时间
   m_cTime=  pData->m_cTime;	//到期时间
   m_cPerson=  pData->m_cPerson;	//身份信息
   m_cModeData=  pData->m_cModeData;	//功能模块
   m_fChongZhiJE = pData->m_fChongZhiJE;  
}

BOOL CDBCusOpRecordsData::GetAllDBInfoByID(CADOConn *pADOConn)
{
	ASSERT(pADOConn != NULL);

	BOOL bRet = FALSE;
	CString strSQL = _T("");
   strSQL.Format(_T("select * from %s where %s=%d")
      ,DB_TABLE_CUSOPRECORDS,DBCusOpRds_key_ID,m_nID);
	pADOConn->GetRecordSet(strSQL);
	if (!pADOConn->adoEOF())
	{
		bRet = GetAllDBInfo(pADOConn);
	}

	return bRet;
}

BOOL CDBCusOpRecordsData::GetAllDBInfo(CADOConn *pADOConn)
{
	ASSERT(pADOConn != NULL);

	BOOL bRet = TRUE;

	if (NULL == pADOConn)
	{
		bRet = FALSE;
	}
	else
	{
      m_nID = pADOConn->GetValueInt(DBCusOpRds_key_ID);		
      m_strCusCode = pADOConn->GetValueString(DBCusOpRds_key_cCusCode);
      m_strCusName = pADOConn->GetValueString(DBCusOpRds_key_cCusName);
      m_strCusPhone = pADOConn->GetValueString(DBCusOpRds_key_cCusPhone);	
      m_strCusAddress = pADOConn->GetValueString(DBCusOpRds_key_cCusAddress);		
      m_strCusContacts = pADOConn->GetValueString(DBCusOpRds_key_cCusContacts);	
      m_strcPDMVersion = pADOConn->GetValueString(DBCusOpRds_key_cPDMVersion);
      m_strProvince= pADOConn->GetValueString(DBCusOpRds_key_cProvince);
      m_isLocalDB = pADOConn->GetValueInt(DBCusOpRds_key_isLocalDB);
      m_strServerPerson= pADOConn->GetValueString(DBCusOpRds_key_cServerPerson);
      m_iClientNum = pADOConn->GetValueInt(DBCusOpRds_key_iClientNum);
      m_strMemo= pADOConn->GetValueString(DBCusOpRds_key_cMemo);

      m_cDbServerName = pADOConn->GetValueString(DBCusOpRds_key_cDbServerName);
      m_cDbServerIP = pADOConn->GetValueString(DBCusOpRds_key_cDbServerIP);	
      m_iDbServerPort = pADOConn->GetValueInt(DBCusOpRds_key_iDbServerPort);		
      m_cDbAccount = pADOConn->GetValueString(DBCusOpRds_key_cDbAccount);	
      m_cDbPassword = pADOConn->GetValueString(DBCusOpRds_key_cDbPassword);

      m_cBeginTime = pADOConn->GetValueString(DBCusOpRds_key_cBeginTime);
      m_cTime = pADOConn->GetValueString(DBCusOpRds_key_cTime);	      
      m_cPerson = pADOConn->GetValueString(DBCusOpRds_key_cPerson);
      m_cModeData = pADOConn->GetValueString(DBCusOpRds_key_cModeData);
      m_fChongZhiJE = pADOConn->GetValueDouble(DBCusOpRds_key_fChongZhiJE);
      m_cOpType = pADOConn->GetValueString(DBCusOpRds_key_cOpType);
		bRet = TRUE;
	}

	return bRet;
}

BOOL CDBCusOpRecordsData::InsertDBInfo(CADOConn *pADOConn)
{
   if (!pADOConn)
   {
      return FALSE;
   }
   CString strSQL = _T("");   
   strSQL.Format(_T("insert into %s \
                    (%s,%s,%s,%s,%s,  %s,%s,%s,%s,%s,\
                     %s,%s,%s,%s,%s,   %s,%s,%s,%s,%s,\
                     %s,%s)\
                    values \
                    ('%s','%s','%s','%s','%s',   '%s','%s','%d','%s','%d',\
                    '%s','%s','%s','%d','%s',    '%s','%s','%s','%s','%s'\
                    ,'%.2f','%s');"),DB_TABLE_CUSOPRECORDS,
      DBCusOpRds_key_cCusCode,DBCusOpRds_key_cCusName,DBCusOpRds_key_cCusPhone,DBCusOpRds_key_cCusAddress,DBCusOpRds_key_cCusContacts,
      DBCusOpRds_key_cPDMVersion,DBCusOpRds_key_cProvince,DBCusOpRds_key_isLocalDB,DBCusOpRds_key_cServerPerson,DBCusOpRds_key_iClientNum,
      DBCusOpRds_key_cMemo,DBCusOpRds_key_cDbServerName,DBCusOpRds_key_cDbServerIP,DBCusOpRds_key_iDbServerPort,DBCusOpRds_key_cDbAccount,
      DBCusOpRds_key_cDbPassword,DBCusOpRds_key_cBeginTime,DBCusOpRds_key_cTime,DBCusOpRds_key_cModeData,DBCusOpRds_key_cPerson,
      DBCusOpRds_key_fChongZhiJE,DBCusOpRds_key_cOpType,
      m_strCusCode,m_strCusName,m_strCusPhone,m_strCusAddress,m_strCusContacts,
      m_strcPDMVersion,m_strProvince,m_isLocalDB,m_strServerPerson,m_iClientNum,
      m_strMemo,m_cDbServerName,m_cDbServerIP,m_iDbServerPort,m_cDbAccount,
      m_cDbPassword,m_cBeginTime,m_cTime,m_cModeData,m_cPerson,
      m_fChongZhiJE,m_cOpType);

   return pADOConn->ExecuteSQL(strSQL);
}

//CDBCusOpRecordsList
CDBCusOpRecordsList::CDBCusOpRecordsList()
{
}

CDBCusOpRecordsList::~CDBCusOpRecordsList()
{
}

CDBCusOpRecordsData*  CDBCusOpRecordsList::GetItem(int nIndex)
{
	if (nIndex<0||nIndex>=GetCount())
		return NULL;
	return (CDBCusOpRecordsData*)GetAt(FindIndex(nIndex));
}

CDBCusOpRecordsData* CDBCusOpRecordsList::GetItemByID(int nID)
{
	CDBCusOpRecordsData * pItem = NULL;
   for(int i=0;i< GetCount();i++)
   {
      CDBCusOpRecordsData * pObject = GetItem(i);
      if(nID==pObject->m_nID)
      {
         pItem = pObject;
         break;
      }
   }

	return pItem;
}

int CDBCusOpRecordsList::GetIndexByID(int nID)
{
	int nSel = -1;
   for(int i=0;i< GetCount();i++)
   {
      CDBCusOpRecordsData * pObject = GetItem(i);
      if(nID==pObject->m_nID)
      {
         nSel = i;
         break;
      }
   }

	return nSel;
}

void CDBCusOpRecordsList:: AddItem(CDBCusOpRecordsData* pItem)
{
	CDBCusOpRecordsData*pData = new CDBCusOpRecordsData;
	pData->Copy(pItem);
	AddTail(pData);
}

void CDBCusOpRecordsList::DeleteItem(int nIndex)
{
	if (nIndex<0||nIndex>GetCount())
		return;
	CDBCusOpRecordsData *pObject=(CDBCusOpRecordsData*)GetItem(nIndex);
	delete pObject;
	pObject=NULL;
	RemoveAt(FindIndex(nIndex));
}

void CDBCusOpRecordsList::GetListFromDB(CADOConn *pADOConn)
{
	ASSERT(pADOConn != NULL);

	Empty();
	CString strSQL = _T("");
   strSQL.Format(_T("select * from %s"),DB_TABLE_CUSOPRECORDS);
	pADOConn->GetRecordSet(strSQL);
	while (!pADOConn->adoEOF())
	{
		CDBCusOpRecordsData oData;
		oData.GetAllDBInfo(pADOConn);
		AddItem(&oData);
		pADOConn->MoveNext();
	}
}

CDBCusOpRecordsList * CDBCusOpRecordsList::Instance()
{
	if(sm_inst.get() == 0)
		sm_inst = std::shared_ptr<CDBCusOpRecordsList>(new CDBCusOpRecordsList);

	return sm_inst.get();
}

BOOL CDBCusOpRecordsList::GetGridDataByCusCode(__in CADOConn* pADOConn,__in CString strCusCode,__out MAP_GridCtrl_AllData& map_data)
{
   map_data.clear();
   ASSERT(pADOConn!=NULL);
   CString strSQL = _T("");
   strSQL.Format(_T("select * from %s where %s = '%s'"),DB_TABLE_CUSOPRECORDS,DBCusOpRds_key_cCusCode,strCusCode);
   pADOConn->GetRecordSet(strSQL);
   while (!pADOConn->adoEOF())
   {
      CDBCusOpRecordsData oData;
      oData.GetAllDBInfo(pADOConn);      
      MAP_GridCtrl_RowData row_data;
      ConvertDataToMap(oData,row_data);      
      map_data.insert(make_pair(map_data.size(),row_data));

      pADOConn->MoveNext();
   }
   return TRUE;
}

void CDBCusOpRecordsList::ConvertDataToMap(const CDBCusOpRecordsData &oData,MAP_GridCtrl_RowData &row_data)
{
   CString strID,strPort;
   strID.Format(_T("%d"),oData.m_nID);
   strPort.Format(_T("%d"),oData.m_iDbServerPort);
   CMapInfoOpt::InsertRowData(DBCusOpRds_key_ID,         strID,row_data,CB_enum_FieldData_Int);
   CMapInfoOpt::InsertRowData(DBCusOpRds_key_cCusCode,    oData.m_strCusCode,row_data);
   CMapInfoOpt::InsertRowData(DBCusOpRds_key_cCusName,    oData.m_strCusName,row_data);
   CMapInfoOpt::InsertRowData(DBCusOpRds_key_cCusAddress, oData.m_strCusAddress,row_data);
   CMapInfoOpt::InsertRowData(DBCusOpRds_key_cCusPhone,   oData.m_strCusPhone,row_data);
   CMapInfoOpt::InsertRowData(DBCusOpRds_key_cCusContacts,oData.m_strCusContacts,row_data);
   CMapInfoOpt::InsertRowData(DBCusOpRds_key_cPDMVersion, oData.m_strcPDMVersion,row_data);
   CMapInfoOpt::InsertRowData(DBCusOpRds_key_cProvince,   oData.m_strProvince,row_data);
   CMapInfoOpt::InsertRowData(DBCusOpRds_key_cServerPerson,oData.m_strServerPerson,row_data);
   CString strClientNum;
   strClientNum.Format(_T("%d"),oData.m_iClientNum);
   CMapInfoOpt::InsertRowData(DBCusOpRds_key_iClientNum, strClientNum  ,row_data,CB_enum_FieldData_Int);
   CMapInfoOpt::InsertRowData(DBCusOpRds_key_cMemo,   oData.m_strMemo,row_data);

   CMapInfoOpt::InsertRowData(DBCusOpRds_key_isLocalDB,   oData.m_isLocalDB==1?_T("是"):_T("否"),row_data);
   CMapInfoOpt::InsertRowData(DBCusOpRds_key_cDbServerName, oData.m_cDbServerName,row_data);
   CMapInfoOpt::InsertRowData(DBCusOpRds_key_iDbServerPort, strPort,row_data,CB_enum_FieldData_Int);
   CMapInfoOpt::InsertRowData(DBCusOpRds_key_cDbAccount,    oData.m_cDbAccount,row_data);
   CMapInfoOpt::InsertRowData(DBCusOpRds_key_cDbPassword,   oData.m_cDbPassword,row_data);
   CMapInfoOpt::InsertRowData(DBCusOpRds_key_cDbServerIP,   oData.m_cDbServerIP,row_data);
      
   CMapInfoOpt::InsertRowData(DBCusOpRds_key_cBeginTime,oData.m_cBeginTime,row_data);
   CMapInfoOpt::InsertRowData(DBCusOpRds_key_cTime,oData.m_cTime,row_data);
   CMapInfoOpt::InsertRowData(DBCusOpRds_key_cPerson,oData.m_cPerson,row_data);
   CMapInfoOpt::InsertRowData(DBCusOpRds_key_cModeData,oData.m_cModeData,row_data);

   CString strfChongZhiJE;
   strfChongZhiJE.Format(_T("%.2f"),oData.m_fChongZhiJE);
   CMapInfoOpt::InsertRowData(DBCusOpRds_key_fChongZhiJE,strfChongZhiJE,row_data,CB_enum_FieldData_Double2Point);
   CMapInfoOpt::InsertRowData(DBCusOpRds_key_cOpType,oData.m_cOpType,row_data);
   
}
