#include "StdAfx.h"
#include "DBCustomer.h"
#include "CDBFieldDefine.h"
#include "ADOConn/ADOConn.h"
#include "MapInfoOpt.h"
#include "ClassData/CDataTableFieldDefine.h"
#include "rnstring.h"
#include "MyEncrypt.h"

IMPLEMENT_SERIAL(CDBCustomBaseData,  CObject, 1)
   IMPLEMENT_SERIAL(CDBCustomDbData,  CObject, 1)
   IMPLEMENT_SERIAL(CDBCustomEncryptData,  CObject, 1)

   IMPLEMENT_SERIAL(CDBVCustomerInfoData,  CObject, 1)
   IMPLEMENT_SERIAL(CDBVCustomerInfoList,  CObList, 1)

std::shared_ptr<CDBCustomBaseData> CDBCustomBaseData::sm_inst;
std::shared_ptr<CDBCustomDbData> CDBCustomDbData::sm_inst;
std::shared_ptr<CDBCustomEncryptData> CDBCustomEncryptData::sm_inst;

std::shared_ptr<CDBVCustomerInfoData> CDBVCustomerInfoData::sm_inst;
std::shared_ptr<CDBVCustomerInfoList> CDBVCustomerInfoList::sm_inst;
//
#pragma region CDBCustomBaseData
CDBCustomBaseData::CDBCustomBaseData()
{
   ResetData();
} 

CDBCustomBaseData::~CDBCustomBaseData()
{
}

void CDBCustomBaseData::operator=( CDBCustomBaseData *pData )
{
   Copy(pData);
}

CDBCustomBaseData * CDBCustomBaseData::Instance()
{
   if(sm_inst.get() == 0)
      sm_inst = std::shared_ptr<CDBCustomBaseData>(new CDBCustomBaseData);
   return sm_inst.get();
}

void CDBCustomBaseData::ResetData()
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
}

void CDBCustomBaseData::Copy(CDBCustomBaseData *pData)
{
   ASSERT(pData != NULL);

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
}

BOOL CDBCustomBaseData::GetAllDBInfoByCusCode(CADOConn *pADOConn)
{
   ASSERT(pADOConn != NULL);
   ASSERT(!m_strCusCode.IsEmpty());

   BOOL bRet = FALSE;

   CString strSQL = _T("");
   strSQL.Format(_T("select * from %s where %s='%s'"),
      DB_TABLE_CUSTOMERBASEDATA,DBCusBase_key_cCusCode,m_strCusCode);
   pADOConn->GetRecordSet(strSQL);
   if (!pADOConn->adoEOF())
   {
      bRet = GetAllDBInfo(pADOConn);
   }

   return bRet;
}

BOOL CDBCustomBaseData::GetAllDBInfo(CADOConn *pADOConn)
{
   ASSERT(pADOConn != NULL);

   BOOL bRet = TRUE;

   if (NULL == pADOConn)
   {
      bRet = FALSE;
   }
   else
   {
      m_nID = pADOConn->GetValueInt(DBCusBase_key_ID);		
      m_strCusCode = pADOConn->GetValueString(DBCusBase_key_cCusCode);
      m_strCusName = pADOConn->GetValueString(DBCusBase_key_cCusName);
      m_strCusPhone = pADOConn->GetValueString(DBCusBase_key_cCusPhone);	
      m_strCusAddress = pADOConn->GetValueString(DBCusBase_key_cCusAddress);		
      m_strCusContacts = pADOConn->GetValueString(DBCusBase_key_cCusContacts);	
      m_strcPDMVersion = pADOConn->GetValueString(DBCusBase_key_cPDMVersion);
      m_strProvince= pADOConn->GetValueString(DBCusBase_key_cProvince);
      m_isLocalDB = pADOConn->GetValueInt(DBCusBase_key_isLocalDB);
      m_strServerPerson= pADOConn->GetValueString(DBCusBase_key_cServerPerson);
      m_iClientNum = pADOConn->GetValueInt(DBCusBase_key_iClientNum);
      m_strMemo= pADOConn->GetValueString(DBCusBase_key_cMemo);
      bRet = TRUE;
   }

   return bRet;
}

BOOL CDBCustomBaseData::InsertAllDBInfo(CADOConn *pADOConn)
{
   ASSERT(pADOConn != NULL);

   m_strCusCode.Trim();
   ASSERT(!m_strCusCode.IsEmpty());

   BOOL bRet = TRUE;

   CString strSQL = _T("");
   strSQL.Format(_T("insert into %s(%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s)\
                    values('%s','%s','%s','%s','%s','%s','%s','%d','%s','%d','%s')"),DB_TABLE_CUSTOMERBASEDATA,
                    DBCusBase_key_cCusCode,DBCusBase_key_cCusName,DBCusBase_key_cCusPhone,DBCusBase_key_cCusAddress,
                    DBCusBase_key_cCusContacts,DBCusBase_key_cPDMVersion,DBCusBase_key_cProvince,DBCusBase_key_isLocalDB,
                    DBCusBase_key_cServerPerson,DBCusBase_key_iClientNum,DBCusBase_key_cMemo,
                    m_strCusCode,m_strCusName,m_strCusPhone,m_strCusAddress,
                    m_strCusContacts,m_strcPDMVersion,m_strProvince,m_isLocalDB
                    ,m_strServerPerson,m_iClientNum,m_strMemo);

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

BOOL CDBCustomBaseData::UpdateAllDBInfoByCusCode(CADOConn *pADOConn)
{
   ASSERT(pADOConn != NULL);
   m_strCusCode.Trim();
   ASSERT(!m_strCusCode.IsEmpty());

   BOOL bRet = TRUE;

   CString strSQL = _T("");

   strSQL.Format(_T("update %s set %s='%s',%s='%s',%s='%s',%s='%s',%s='%s',%s='%s',%s ='%d'\
                    ,%s='%s',%s ='%d',%s='%s' where %s='%s'"),DB_TABLE_CUSTOMERBASEDATA,		
      DBCusBase_key_cCusName,m_strCusName,
      DBCusBase_key_cCusPhone,m_strCusPhone,		
      DBCusBase_key_cCusAddress,m_strCusAddress,		
      DBCusBase_key_cCusContacts,m_strCusContacts,
      DBCusBase_key_cPDMVersion,m_strcPDMVersion,
      DBCusBase_key_cProvince,m_strProvince,
      DBCusBase_key_isLocalDB,m_isLocalDB,
      DBCusBase_key_cServerPerson,m_strServerPerson,
      DBCusBase_key_iClientNum,m_iClientNum,
      DBCusBase_key_cMemo,m_strMemo,
      DBCusBase_key_cCusCode,m_strCusCode);

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

BOOL CDBCustomBaseData::DelAllDBInfoByCusCode(CADOConn *pADOConn)
{
   ASSERT(pADOConn != NULL);
   m_strCusCode.Trim();
   ASSERT(!m_strCusCode.IsEmpty());

   BOOL bRet = TRUE;

   CString strSQL = _T("");
   strSQL.Format(_T("delete from %s where %s='%s'"),DB_TABLE_CUSTOMERBASEDATA,DBCusBase_key_cCusCode,m_strCusCode);

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
#pragma endregion CDBCustomBaseData

#pragma region CDBCustomDbData

CDBCustomDbData::CDBCustomDbData()
{
   ResetData();
} 

CDBCustomDbData::~CDBCustomDbData()
{
}

void CDBCustomDbData::operator=( CDBCustomDbData *pData )
{
   Copy(pData);
}

CDBCustomDbData * CDBCustomDbData::Instance()
{
   if(sm_inst.get() == 0)
      sm_inst = std::shared_ptr<CDBCustomDbData>(new CDBCustomDbData);
   return sm_inst.get();
}

void CDBCustomDbData::ResetData()
{
   m_strCusCode= _T("");	   //客户编号
   m_cDbServerName= _T("");	//数据库名称
   m_cDbServerIP= _T("");	//数据库IP
   m_iDbServerPort=0;	//数据库端口
   m_cDbAccount= _T("");	//登录账户
   m_cDbPassword= _T("");	//登录密码
}

void CDBCustomDbData::Copy(CDBCustomDbData *pData)
{
   ASSERT(pData != NULL);

   m_strCusCode= pData->m_strCusCode;	//客户编号
   m_cDbServerName= pData->m_cDbServerName;	//数据库名称
   m_cDbServerIP= pData->m_cDbServerIP;	//数据库IP
   m_iDbServerPort= pData->m_iDbServerPort;	//数据库端口
   m_cDbAccount= pData->m_cDbAccount;	//登录账户
   m_cDbPassword= pData->m_cDbPassword;	//登录密码
}

BOOL CDBCustomDbData::GetAllDBInfoByCusCode(CADOConn *pADOConn)
{
   ASSERT(pADOConn != NULL);
   ASSERT(!m_strCusCode.IsEmpty());

   BOOL bRet = FALSE;

   CString strSQL = _T("");
   strSQL.Format(_T("select * from %s where %s='%s'"),
      DB_TABLE_CUSTOMERDBDATA,DBCusDb_key_cCusCode,m_strCusCode);
   pADOConn->GetRecordSet(strSQL);
   if (!pADOConn->adoEOF())
   {
      bRet = GetAllDBInfo(pADOConn);
   }

   return bRet;
}

BOOL CDBCustomDbData::GetAllDBInfo(CADOConn *pADOConn)
{
   ASSERT(pADOConn != NULL);

   BOOL bRet = TRUE;

   if (NULL == pADOConn)
   {
      bRet = FALSE;
   }
   else
   {
      m_strCusCode = pADOConn->GetValueString(DBCusDb_key_cCusCode);
      m_cDbServerName = pADOConn->GetValueString(DBCusDb_key_cDbServerName);
      m_cDbServerIP = pADOConn->GetValueString(DBCusDb_key_cDbServerIP);	
      m_iDbServerPort = pADOConn->GetValueInt(DBCusDb_key_iDbServerPort);		
      m_cDbAccount = pADOConn->GetValueString(DBCusDb_key_cDbAccount);	
      m_cDbPassword = pADOConn->GetValueString(DBCusDb_key_cDbPassword);
      bRet = TRUE;
   }

   return bRet;
}

BOOL CDBCustomDbData::InsertAllDBInfo(CADOConn *pADOConn)
{
   ASSERT(pADOConn != NULL);

   m_strCusCode.Trim();
   ASSERT(!m_strCusCode.IsEmpty());

   BOOL bRet = TRUE;

   CString strSQL = _T("");
   strSQL.Format(_T("insert into %s(%s,%s,%s,%s,%s,%s)\
                    values('%s','%s','%s','%d','%s','%s')"),DB_TABLE_CUSTOMERDBDATA,
                    DBCusDb_key_cCusCode,DBCusDb_key_cDbServerName,DBCusDb_key_cDbServerIP,DBCusDb_key_iDbServerPort,
                    DBCusDb_key_cDbAccount,DBCusDb_key_cDbPassword,                  
                    m_strCusCode,m_cDbServerName,m_cDbServerIP,m_iDbServerPort,
                    m_cDbAccount,m_cDbPassword);

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

BOOL CDBCustomDbData::UpdateAllDBInfoByCusCode(CADOConn *pADOConn)
{
   ASSERT(pADOConn != NULL);
   m_strCusCode.Trim();
   ASSERT(!m_strCusCode.IsEmpty());

   BOOL bRet = TRUE;

   CString strSQL = _T("");

   strSQL.Format(_T("update %s set %s='%s',%s='%s',%s='%d',%s='%s',%s='%s' where %s='%s'"),DB_TABLE_CUSTOMERDBDATA,		
      DBCusDb_key_cDbServerName,m_cDbServerName,
      DBCusDb_key_cDbServerIP,m_cDbServerIP,		
      DBCusDb_key_iDbServerPort,m_iDbServerPort,		
      DBCusDb_key_cDbAccount,m_cDbAccount,
      DBCusDb_key_cDbPassword,m_cDbPassword,
      DBCusDb_key_cCusCode,m_strCusCode);

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

BOOL CDBCustomDbData::DelAllDBInfoByCusCode(CADOConn *pADOConn)
{
   ASSERT(pADOConn != NULL);
   m_strCusCode.Trim();
   ASSERT(!m_strCusCode.IsEmpty());

   BOOL bRet = TRUE;

   CString strSQL = _T("");
   strSQL.Format(_T("delete from %s where %s='%s'"),DB_TABLE_CUSTOMERDBDATA,DBCusDb_key_cCusCode,m_strCusCode);

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
#pragma endregion CDBCustomDbData

#pragma region CDBCustomEncryptData
CDBCustomEncryptData::CDBCustomEncryptData()
{
   ResetData();
} 

CDBCustomEncryptData::~CDBCustomEncryptData()
{
}

void CDBCustomEncryptData::operator=( CDBCustomEncryptData *pData )
{
   Copy(pData);
}

CDBCustomEncryptData * CDBCustomEncryptData::Instance()
{
   if(sm_inst.get() == 0)
      sm_inst = std::shared_ptr<CDBCustomEncryptData>(new CDBCustomEncryptData);
   return sm_inst.get();
}

void CDBCustomEncryptData::ResetData()
{
   m_strCusCode= _T("");	   //客户编号
   m_cData1= _T("");	//加密数据1
   m_cData2= _T("");	//加密数据2
   m_cData3= _T("");	//加密数据3
   m_cData4= _T("");	//加密数据4
}

void CDBCustomEncryptData::Copy(CDBCustomEncryptData *pData)
{
   ASSERT(pData != NULL);

   m_strCusCode= pData->m_strCusCode;	//客户编号
   m_cData1= pData->m_cData1;	
   m_cData2= pData->m_cData2;	
   m_cData3= pData->m_cData3;	
   m_cData4 = pData->m_cData4;
}

BOOL CDBCustomEncryptData::GetAllDBInfoByCusCode(CADOConn *pADOConn)
{
   ASSERT(pADOConn != NULL);
   ASSERT(!m_strCusCode.IsEmpty());

   BOOL bRet = FALSE;

   CString strSQL = _T("");
   strSQL.Format(_T("select * from %s where %s='%s'"),
      DB_TABLE_CUSTOMERENCRYPTDATA,DBCusDb_key_cCusCode,m_strCusCode);
   pADOConn->GetRecordSet(strSQL);
   if (!pADOConn->adoEOF())
   {
      bRet = GetAllDBInfo(pADOConn);
   }

   return bRet;
}

BOOL CDBCustomEncryptData::GetAllDBInfo(CADOConn *pADOConn)
{
   ASSERT(pADOConn != NULL);

   BOOL bRet = TRUE;

   if (NULL == pADOConn)
   {
      bRet = FALSE;
   }
   else
   {
      m_strCusCode = pADOConn->GetValueString(DBCusEncrypt_key_cCusCode);
      m_cData1 = pADOConn->GetValueString(DBCusEncrypt_key_cData1);
      m_cData2 = pADOConn->GetValueString(DBCusEncrypt_key_cData2);	      
      m_cData3 = pADOConn->GetValueString(DBCusEncrypt_key_cData3);	
      m_cData4 = pADOConn->GetValueString(DBCusEncrypt_key_cData4);	
      bRet = TRUE;
   }

   return bRet;
}

BOOL CDBCustomEncryptData::InsertAllDBInfo(CADOConn *pADOConn)
{
   ASSERT(pADOConn != NULL);

   m_strCusCode.Trim();
   ASSERT(!m_strCusCode.IsEmpty());

   BOOL bRet = TRUE;

   CString strSQL = _T("");
   strSQL.Format(_T("insert into %s(%s,%s,%s,%s,%s)\
                    values('%s','%s','%s','%s','%s')"),DB_TABLE_CUSTOMERENCRYPTDATA,
                    DBCusEncrypt_key_cCusCode,DBCusEncrypt_key_cData1,DBCusEncrypt_key_cData2,DBCusEncrypt_key_cData3,DBCusEncrypt_key_cData4,                            
                    m_strCusCode,m_cData1,m_cData2,m_cData3,m_cData4);

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

BOOL CDBCustomEncryptData::UpdateAllDBInfoByCusCode(CADOConn *pADOConn)
{
   ASSERT(pADOConn != NULL);
   m_strCusCode.Trim();
   ASSERT(!m_strCusCode.IsEmpty());

   BOOL bRet = TRUE;

   CString strSQL = _T("");

   strSQL.Format(_T("update %s set %s='%s',%s='%s',%s='%s',%s='%s' where %s='%s'"),DB_TABLE_CUSTOMERENCRYPTDATA,		
      DBCusEncrypt_key_cData1,m_cData1,
      DBCusEncrypt_key_cData2,m_cData2,
      DBCusEncrypt_key_cData3,m_cData3,
      DBCusEncrypt_key_cData4,m_cData4,
      DBCusEncrypt_key_cCusCode,m_strCusCode);

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

BOOL CDBCustomEncryptData::DelAllDBInfoByCusCode(CADOConn *pADOConn)
{
   ASSERT(pADOConn != NULL);
   m_strCusCode.Trim();
   ASSERT(!m_strCusCode.IsEmpty());

   BOOL bRet = TRUE;

   CString strSQL = _T("");
   strSQL.Format(_T("delete from %s where %s='%s'"),DB_TABLE_CUSTOMERENCRYPTDATA,DBCusEncrypt_key_cCusCode,m_strCusCode);

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
#pragma endregion CDBCustomEncryptData

#pragma region CDBVCustomerInfoData
CDBVCustomerInfoData::CDBVCustomerInfoData()
{
	ResetData();
} 

CDBVCustomerInfoData::~CDBVCustomerInfoData()
{
}

void CDBVCustomerInfoData::operator=( CDBVCustomerInfoData *pData )
{
	Copy(pData);
}

CDBVCustomerInfoData * CDBVCustomerInfoData::Instance()
{
	if(sm_inst.get() == 0)
		sm_inst = std::shared_ptr<CDBVCustomerInfoData>(new CDBVCustomerInfoData);
	return sm_inst.get();
}

void CDBVCustomerInfoData::ResetData()
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
   m_strMemo= _T("");//备注

   m_cDbServerName= _T("");	//数据库名称
   m_cDbServerIP= _T("");	//数据库IP
   m_iDbServerPort=0;	//数据库端口
   m_cDbAccount= _T("");	//登录账户
   m_cDbPassword= _T("");	//登录密码

   m_strCusCode= _T("");	   //客户编号
   m_cData1= _T("");	
   m_cData2= _T("");	
   m_cData3= _T("");	
   m_cData4 = _T("");

   //不在数据库的数据 yangjr 2018/8/30
   m_cBeginTime= _T("");	//开始时间
   m_cTime= _T("");	//到期时间
   m_cPerson= _T("");	//身份信息
   m_cModeData= _T("");	//功能模块
   m_iClientNum = 0;//客户端数量
   m_fChongZhiJE = 0;
}

void CDBVCustomerInfoData::Copy(CDBVCustomerInfoData *pData)
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
   m_strMemo = pData->m_strMemo;//备注

   m_cDbServerName= pData->m_cDbServerName;	//数据库名称
   m_cDbServerIP= pData->m_cDbServerIP;	//数据库IP
   m_iDbServerPort= pData->m_iDbServerPort;	//数据库端口
   m_cDbAccount= pData->m_cDbAccount;	//登录账户
   m_cDbPassword= pData->m_cDbPassword;	//登录密码

   m_cData1= pData->m_cData1;	
   m_cData2= pData->m_cData2;	
   m_cData3= pData->m_cData3;	
   m_cData4 = pData->m_cData4;

   //不在数据库的数据 yangjr 2018/8/30
   m_cBeginTime=  pData->m_cBeginTime;	//开始时间
   m_cTime=  pData->m_cTime;	//到期时间
   m_cPerson=  pData->m_cPerson;	//身份信息
   m_cModeData=  pData->m_cModeData;	//功能模块
   m_iClientNum = pData->m_iClientNum;//客户端数量
   m_fChongZhiJE = pData->m_fChongZhiJE;
}

BOOL CDBVCustomerInfoData::GetAllDBInfoByCusCode(CADOConn *pADOConn)
{
	ASSERT(pADOConn != NULL);
	ASSERT(!m_strCusCode.IsEmpty());

	BOOL bRet = FALSE;

	CString strSQL = _T("");
   strSQL.Format(_T("select CA.*,CB.*,CC.* from %s CA \
      left join %s CB on CB.cCusCode = CA.cCusCode \
      left join %s CC on CC.cCusCode = CA.cCusCode\
      where CA.%s='%s'"),DB_TABLE_CUSTOMERBASEDATA,DB_TABLE_CUSTOMERDBDATA
      ,DB_TABLE_CUSTOMERENCRYPTDATA,DBCusBase_key_cCusCode,m_strCusCode);
	pADOConn->GetRecordSet(strSQL);
	if (!pADOConn->adoEOF())
	{
		bRet = GetAllDBInfo(pADOConn);
	}

	return bRet;
}

BOOL CDBVCustomerInfoData::GetAllDBInfo(CADOConn *pADOConn)
{
	ASSERT(pADOConn != NULL);

	BOOL bRet = TRUE;

	if (NULL == pADOConn)
	{
		bRet = FALSE;
	}
	else
	{
      m_nID = pADOConn->GetValueInt(DBCusBase_key_ID);		
      m_strCusCode = pADOConn->GetValueString(DBCusBase_key_cCusCode);
      m_strCusName = pADOConn->GetValueString(DBCusBase_key_cCusName);
      m_strCusPhone = pADOConn->GetValueString(DBCusBase_key_cCusPhone);	
      m_strCusAddress = pADOConn->GetValueString(DBCusBase_key_cCusAddress);		
      m_strCusContacts = pADOConn->GetValueString(DBCusBase_key_cCusContacts);	
      m_strcPDMVersion = pADOConn->GetValueString(DBCusBase_key_cPDMVersion);
      m_strProvince= pADOConn->GetValueString(DBCusBase_key_cProvince);
      m_isLocalDB = pADOConn->GetValueInt(DBCusBase_key_isLocalDB);
      m_strServerPerson= pADOConn->GetValueString(DBCusBase_key_cServerPerson);
      //m_iClientNum = pADOConn->GetValueInt(DBCusBase_key_iClientNum); //移动到加密数据中了
      m_strMemo= pADOConn->GetValueString(DBCusBase_key_cMemo);

      m_cDbServerName = pADOConn->GetValueString(DBCusDb_key_cDbServerName);
      m_cDbServerIP = pADOConn->GetValueString(DBCusDb_key_cDbServerIP);	
      m_iDbServerPort = pADOConn->GetValueInt(DBCusDb_key_iDbServerPort);		
      m_cDbAccount = pADOConn->GetValueString(DBCusDb_key_cDbAccount);	
      m_cDbPassword = pADOConn->GetValueString(DBCusDb_key_cDbPassword);

      m_cData1 = pADOConn->GetValueString(DBCusEncrypt_key_cData1);
      m_cData2 = pADOConn->GetValueString(DBCusEncrypt_key_cData2);	      
      m_cData3 = pADOConn->GetValueString(DBCusEncrypt_key_cData3);
      m_cData4 = pADOConn->GetValueString(DBCusEncrypt_key_cData4);

		bRet = TRUE;
	}

	return bRet;
}

CString CDBVCustomerInfoData::GetInsertSql()
{
   CString strTemp1,strTemp2,strTemp3;
   strTemp1.Format(_T("insert into %s (%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s) values ('%s','%s','%s','%s','%s','%s','%s','%d','%s','%d','%s');"),DB_TABLE_CUSTOMERBASEDATA,
                  DBCusBase_key_cCusCode,DBCusBase_key_cCusName,DBCusBase_key_cCusPhone,DBCusBase_key_cCusAddress,DBCusBase_key_cCusContacts,
                  DBCusBase_key_cPDMVersion,DBCusBase_key_cProvince,DBCusBase_key_isLocalDB,
                  DBCusBase_key_cServerPerson,DBCusBase_key_iClientNum,DBCusBase_key_cMemo,
                  m_strCusCode,m_strCusName,m_strCusPhone,m_strCusAddress,m_strCusContacts,
                  m_strcPDMVersion,m_strProvince,m_isLocalDB,
                  m_strServerPerson,m_iClientNum,m_strMemo);

   strTemp2.Format(_T("insert into %s (%s,%s,%s,%s,%s,%s) values ('%s','%s','%s',%d,'%s','%s');"),DB_TABLE_CUSTOMERDBDATA,
                  DBCusDb_key_cCusCode,DBCusDb_key_cDbServerName,DBCusDb_key_cDbServerIP,DBCusDb_key_iDbServerPort,DBCusDb_key_cDbAccount,DBCusDb_key_cDbPassword,
                  m_strCusCode,m_cDbServerName,m_cDbServerIP,m_iDbServerPort,m_cDbAccount,m_cDbPassword);

   strTemp3.Format(_T("insert into %s (%s,%s,%s,%s,%s) values ('%s','%s','%s','%s','%s');"),DB_TABLE_CUSTOMERENCRYPTDATA,
                  DBCusEncrypt_key_cCusCode,DBCusEncrypt_key_cData1,DBCusEncrypt_key_cData2,DBCusEncrypt_key_cData3,DBCusEncrypt_key_cData4,
                  m_strCusCode,m_cData1,m_cData2,m_cData3,m_cData4);
   return strTemp1 + strTemp2 + strTemp3;
}

CString CDBVCustomerInfoData::GetUpdateSql()
{
   CString strTemp1,strTemp2,strTemp3;
   strTemp1.Format(_T("update %s set %s = '%s',%s = '%s',%s = '%s',%s = '%s',%s = '%s',%s = '%s',%s = '%s',%s = %d\
                      ,%s = '%s',%s = %d,%s = '%s' where %s = %d;"),
                  DB_TABLE_CUSTOMERBASEDATA,
                  DBCusBase_key_cCusCode,m_strCusCode,
                  DBCusBase_key_cCusName,m_strCusName,
                  DBCusBase_key_cCusPhone,m_strCusPhone,
                  DBCusBase_key_cCusAddress,m_strCusAddress,
                  DBCusBase_key_cCusContacts,m_strCusContacts,
                  DBCusBase_key_cPDMVersion,m_strcPDMVersion,
                  DBCusBase_key_cProvince,m_strProvince,
                  DBCusBase_key_isLocalDB,m_isLocalDB,
                  DBCusBase_key_cServerPerson,m_strServerPerson,
                  DBCusBase_key_iClientNum,m_iClientNum,
                  DBCusBase_key_cMemo,m_strMemo,
                  DBCusBase_key_ID,m_nID);
   strTemp2.Format(_T("update %s set %s = '%s',%s = '%s',%s = '%s',%s = '%s',%s = %d where %s = '%s';"),
                  DB_TABLE_CUSTOMERDBDATA,
                  DBCusDb_key_cDbServerName,m_cDbServerName,
                  DBCusDb_key_cDbServerIP,m_cDbServerIP,
                  DBCusDb_key_cDbAccount,m_cDbAccount,
                  DBCusDb_key_cDbPassword,m_cDbPassword,
                  DBCusDb_key_iDbServerPort,m_iDbServerPort,
                  DBCusDb_key_cCusCode,m_strCusCode);
   strTemp3.Format(_T("update %s set %s = '%s',%s = '%s',%s = '%s',%s = '%s' where %s = '%s';"),
                  DB_TABLE_CUSTOMERENCRYPTDATA,
                  DBCusEncrypt_key_cData1,m_cData1,
                  DBCusEncrypt_key_cData2,m_cData2,
                  DBCusEncrypt_key_cData3,m_cData3,
                  DBCusEncrypt_key_cData4,m_cData4,
                  DBCusEncrypt_key_cCusCode,m_strCusCode);
   return strTemp1 + strTemp2 + strTemp3;
}

BOOL CDBVCustomerInfoData::EncryptString(__in CLDK *pLdk)
{
   CMyEncrypt MyEncrypt;   
   return MyEncrypt.EncryptString(pLdk,m_cModeData,m_cBeginTime,m_cTime,m_cPerson,m_iClientNum,m_cData1,m_cData2,m_cData3,m_cData4);
}

BOOL CDBVCustomerInfoData::DecryptString(__in CLDK *pLdk)
{
  CMyEncrypt MyEncrypt;
  return MyEncrypt.DecryptString(pLdk,m_cData1,m_cData2,m_cData3,m_cData4,m_cModeData,m_cBeginTime,m_cTime,m_cPerson,m_iClientNum);
}

#pragma endregion CDBVCustomerInfoData

//CDBVCustomerInfoList
CDBVCustomerInfoList::CDBVCustomerInfoList()
{
}

CDBVCustomerInfoList::~CDBVCustomerInfoList()
{
}

CDBVCustomerInfoData*  CDBVCustomerInfoList::GetItem(int nIndex)
{
	if (nIndex<0||nIndex>=GetCount())
		return NULL;
	return (CDBVCustomerInfoData*)GetAt(FindIndex(nIndex));
}

CDBVCustomerInfoData* CDBVCustomerInfoList::GetItemByCusCode(CString strCusCode)
{
	CDBVCustomerInfoData * pItem = NULL;
	strCusCode.Trim();
	if (!strCusCode.IsEmpty())
	{
		for(int i=0;i< GetCount();i++)
		{
			CDBVCustomerInfoData * pObject = GetItem(i);
			if(strCusCode==pObject->m_strCusCode)
			{
				pItem = pObject;
				break;
			}
		}
	}

	return pItem;
}

int CDBVCustomerInfoList::GetIndexByCusCode(CString strCusCode)
{
	int nSel = -1;
	strCusCode.Trim();
	if (!strCusCode.IsEmpty())
	{
		for(int i=0;i< GetCount();i++)
		{
			CDBVCustomerInfoData * pObject = GetItem(i);
			if(strCusCode==pObject->m_strCusCode)
			{
				nSel = i;
				break;
			}
		}
	}

	return nSel;
}

void CDBVCustomerInfoList:: AddItem(CDBVCustomerInfoData* pItem)
{
	CDBVCustomerInfoData*pData = new CDBVCustomerInfoData;
	pData->Copy(pItem);
	AddTail(pData);
}

void CDBVCustomerInfoList::DeleteItem(int nIndex)
{
	if (nIndex<0||nIndex>GetCount())
		return;
	CDBVCustomerInfoData *pObject=(CDBVCustomerInfoData*)GetItem(nIndex);
	delete pObject;
	pObject=NULL;
	RemoveAt(FindIndex(nIndex));
}

void CDBVCustomerInfoList::GetListFromDB(CADOConn *pADOConn)
{
	ASSERT(pADOConn != NULL);

	Empty();
	CString strSQL = _T("");
   strSQL.Format(_T("select CA.*,CB.*,CC.* from %s CA \
                    left join %s CB on CB.cCusCode = CA.cCusCode \
                    left join %s CC on CC.cCusCode = CA.cCusCode")
                    ,DB_TABLE_CUSTOMERBASEDATA,DB_TABLE_CUSTOMERDBDATA,DB_TABLE_CUSTOMERENCRYPTDATA);
	pADOConn->GetRecordSet(strSQL);
	while (!pADOConn->adoEOF())
	{
		CDBVCustomerInfoData oData;
		oData.GetAllDBInfo(pADOConn);
		AddItem(&oData);
		pADOConn->MoveNext();
	}
}

CDBVCustomerInfoList * CDBVCustomerInfoList::Instance()
{
	if(sm_inst.get() == 0)
		sm_inst = std::shared_ptr<CDBVCustomerInfoList>(new CDBVCustomerInfoList);

	return sm_inst.get();
}

BOOL CDBVCustomerInfoList::GetAllCustomerGridData(__in CADOConn* pADOConn,__in CLDK *pLdk,__out MAP_GridCtrl_AllData& map_data)
{
   map_data.clear();
   ASSERT(pADOConn!=NULL);
   CString strSQL = _T("");
   strSQL.Format(_T("select CA.*,\
      CB.cDbPassword,CB.cDbAccount,CB.cDbServerName,CB.iDbServerPort,CB.cDbServerIP,\
      CC.cData1,CC.cData2,CC.cData3,CC.cData4 from CustomerBaseData CA \
      left join CustomerDbData CB on CB.cCusCode = CA.cCusCode \
      left join CustomerEncryptData CC on CC.cCusCode = CA.cCusCode"));

   pADOConn->GetRecordSet(strSQL);
   while (!pADOConn->adoEOF())
   {
      CDBVCustomerInfoData oData;
      oData.GetAllDBInfo(pADOConn);
      if(!oData.DecryptString(pLdk))
      {
         map_data.clear();
         return FALSE;
      }
      MAP_GridCtrl_RowData row_data;
      ConvertDataToMap(oData,row_data);      
      map_data.insert(make_pair(map_data.size(),row_data));

      pADOConn->MoveNext();
   }
   return TRUE;
}

BOOL CDBVCustomerInfoList::GetCustomerDataByID(__in CADOConn* pADOConn,__in int iID,__in CLDK *pLdk,__out CDBVCustomerInfoData* pData)
{
   ASSERT(pADOConn!=NULL);
   ASSERT(pData != NULL);
   CString strSQL = _T("");
   strSQL.Format(_T("select CA.*,\
                    CB.cDbPassword,CB.cDbAccount,CB.cDbServerName,CB.iDbServerPort,CB.cDbServerIP,\
                    CC.cData1,CC.cData2,CC.cData3,CC.cData4 from CustomerBaseData CA \
                    left join CustomerDbData CB on CB.cCusCode = CA.cCusCode \
                    left join CustomerEncryptData CC on CC.cCusCode = CA.cCusCode\
                    where CA.ID = %d;"),iID);
   pADOConn->GetRecordSet(strSQL);
   if (!pADOConn->adoEOF())
   {
      pData->GetAllDBInfo(pADOConn);
      if(!pData->DecryptString(pLdk))
      {        
         return FALSE;
      }
      return TRUE;
   }
   return FALSE;
}

CString CDBVCustomerInfoList::GetDelSql_CustomerDataByCusCode(__in vector<CString> vecCusCode)
{
   if (vecCusCode.size() <=0)
   {
      return _T("");
   }
   CString strSQL = _T(""),strWhere = _T(""),strTemp1 = _T(""),strTemp2 = _T(""),strTemp3 = _T("");
   for (int i=0; i<(int)vecCusCode.size(); ++i)
   {
      strWhere +=_T("'")+vecCusCode[i]+_T("',");
   }
   strWhere.TrimRight(_T(","));
   strTemp1.Format(_T("delete from %s where %s in (%s);"),DB_TABLE_CUSTOMERBASEDATA,DBCusBase_key_cCusCode,strWhere);
   strTemp2.Format(_T("delete from %s where %s in (%s);"),DB_TABLE_CUSTOMERDBDATA,DBCusDb_key_cCusCode,strWhere);
   strTemp3.Format(_T("delete from %s where %s in (%s);"),DB_TABLE_CUSTOMERENCRYPTDATA,DBCusEncrypt_key_cCusCode,strWhere);
   return strTemp1 + strTemp2 + strTemp3;
}

BOOL CDBVCustomerInfoList::CheckCusCodeExists(__in CADOConn* pADOConn,__in CString strCusCode)
{
   ASSERT(pADOConn!=NULL);
   int iNum = 0;
   CString strSql;
   strSql.Format(_T("select sum(a+b+c) as num from \
      (select count(*)as a from CustomerBaseData where cCusCode = '%s') as T1,\
      (select count(*)as b from CustomerDbData where cCusCode = '%s') as T2,\
      (select count(*)as c from CustomerEncryptData where cCusCode = '%s') as T3"),strCusCode,strCusCode,strCusCode);
   pADOConn->GetRecordSet(strSql);
   if (!pADOConn->adoEOF())
   {
      iNum = pADOConn->GetValueInt(_T("num"));
      if (iNum <=0)
      {
         return FALSE;
      }
   }

   return TRUE;
}

BOOL CDBVCustomerInfoList::GetExpiringCustomerGridData(__in CADOConn* pADOConn,__in int iDays,__in CLDK *pLdk,__out MAP_GridCtrl_AllData& map_data)
{
   map_data.clear();
   ASSERT(pADOConn!=NULL);
   CString strSQL = _T("");
   //先取数据库时间   
   strSQL.Format(_T("select CONVERT(varchar(50),GETDATE(),23) as Date,CONVERT(varchar(50),dateadd(day, %d, GETDATE()) ,23) as Date2;"),iDays);
   pADOConn->GetRecordSet(strSQL);
   CString strDate = _T("");
   CString strDateLast = _T("");
   if (!pADOConn->adoEOF())
   {
      strDate = pADOConn->GetValueString(_T("Date"));
      strDateLast = pADOConn->GetValueString(_T("Date2"));
   }else
   {
      return FALSE;
   }
   strSQL.Format(_T("select CA.*,\
                    CB.cDbPassword,CB.cDbAccount,CB.cDbServerName,CB.iDbServerPort,CB.cDbServerIP,\
                    CC.cData1,CC.cData2,CC.cData3,CC.cData4 from CustomerBaseData CA \
                    left join CustomerDbData CB on CB.cCusCode = CA.cCusCode \
                    left join CustomerEncryptData CC on CC.cCusCode = CA.cCusCode"));

   pADOConn->GetRecordSet(strSQL);   
   while (!pADOConn->adoEOF())
   {
      CDBVCustomerInfoData oData;
      oData.GetAllDBInfo(pADOConn);
      if(!oData.DecryptString(pLdk))
      {
         map_data.clear();
         return FALSE;
      }
      //到期时间>=当前时间且到期时间<=当前时间的后几天
      if (oData.m_cTime.Compare(strDate)>=0 && oData.m_cTime.Compare(strDateLast)<=0)
      {
         MAP_GridCtrl_RowData row_data;      
         ConvertDataToMap(oData,row_data);
         map_data.insert(make_pair(map_data.size(),row_data));
      }

      pADOConn->MoveNext();
   }
   return TRUE;
}

BOOL CDBVCustomerInfoList::GetExpiredCustomerGridData(__in CADOConn* pADOConn,__in CLDK *pLdk,__out MAP_GridCtrl_AllData& map_data)
{
   map_data.clear();
   ASSERT(pADOConn!=NULL);
   CString strSQL = _T("");
   //先取数据库时间   
   strSQL = _T("select CONVERT(varchar(50),GETDATE(),23) as Date;");
   pADOConn->GetRecordSet(strSQL);
   CString strDate = _T("");
   if (!pADOConn->adoEOF())
   {
      strDate = pADOConn->GetValueString(_T("Date"));
   }else
   {
      return FALSE;
   }
   strSQL.Format(_T("select CA.*,\
                    CB.cDbPassword,CB.cDbAccount,CB.cDbServerName,CB.iDbServerPort,CB.cDbServerIP,\
                    CC.cData1,CC.cData2,CC.cData3,CC.cData4 from CustomerBaseData CA \
                    left join CustomerDbData CB on CB.cCusCode = CA.cCusCode \
                    left join CustomerEncryptData CC on CC.cCusCode = CA.cCusCode"));

   pADOConn->GetRecordSet(strSQL);
   while (!pADOConn->adoEOF())
   {
      CDBVCustomerInfoData oData;
      oData.GetAllDBInfo(pADOConn);
      if (!oData.DecryptString(pLdk))
      {
         map_data.clear();
         return FALSE;
      }
      //到期时间<当前时间 说明已经到期
      if (oData.m_cTime.Compare(strDate)<0)
      {
         MAP_GridCtrl_RowData row_data;
         ConvertDataToMap(oData,row_data);
         map_data.insert(make_pair(map_data.size(),row_data));
      } 
      pADOConn->MoveNext();
   }
   return TRUE;
}

void CDBVCustomerInfoList::ConvertDataToMap(const CDBVCustomerInfoData &oData,MAP_GridCtrl_RowData &row_data)
{
   CString strID,strPort;
   strID.Format(_T("%d"),oData.m_nID);
   strPort.Format(_T("%d"),oData.m_iDbServerPort);
   CMapInfoOpt::InsertRowData(DBCusBase_key_ID,         strID,row_data,CB_enum_FieldData_Int);
   CMapInfoOpt::InsertRowData(DBCusBase_key_cCusCode,    oData.m_strCusCode,row_data);
   CMapInfoOpt::InsertRowData(DBCusBase_key_cCusName,    oData.m_strCusName,row_data);
   CMapInfoOpt::InsertRowData(DBCusBase_key_cCusAddress, oData.m_strCusAddress,row_data);
   CMapInfoOpt::InsertRowData(DBCusBase_key_cCusPhone,   oData.m_strCusPhone,row_data);
   CMapInfoOpt::InsertRowData(DBCusBase_key_cCusContacts,oData.m_strCusContacts,row_data);
   CMapInfoOpt::InsertRowData(DBCusBase_key_cPDMVersion, oData.m_strcPDMVersion,row_data);
   CMapInfoOpt::InsertRowData(DBCusBase_key_cProvince,   oData.m_strProvince,row_data);
   CMapInfoOpt::InsertRowData(DBCusBase_key_cServerPerson,oData.m_strServerPerson,row_data);   
   CMapInfoOpt::InsertRowData(DBCusBase_key_cMemo,   oData.m_strMemo,row_data);

   CMapInfoOpt::InsertRowData(DBCusBase_key_isLocalDB,   oData.m_isLocalDB==1?_T("是"):_T("否"),row_data);
   CMapInfoOpt::InsertRowData(DBCusDb_key_cDbServerName, oData.m_cDbServerName,row_data);
   CMapInfoOpt::InsertRowData(DBCusDb_key_iDbServerPort, strPort,row_data,CB_enum_FieldData_Int);
   CMapInfoOpt::InsertRowData(DBCusDb_key_cDbAccount,    oData.m_cDbAccount,row_data);
   CMapInfoOpt::InsertRowData(DBCusDb_key_cDbPassword,   oData.m_cDbPassword,row_data);
   CMapInfoOpt::InsertRowData(DBCusDb_key_cDbServerIP,   oData.m_cDbServerIP,row_data);
      
   CMapInfoOpt::InsertRowData(XML_CUSMGN_FIELD_cBeginTime,oData.m_cBeginTime,row_data);
   CMapInfoOpt::InsertRowData(XML_CUSMGN_FIELD_cTime,oData.m_cTime,row_data);
   CMapInfoOpt::InsertRowData(XML_CUSMGN_FIELD_cPerson,oData.m_cPerson,row_data);
   CMapInfoOpt::InsertRowData(XML_CUSMGN_FIELD_cModeData,oData.m_cModeData,row_data);
   CString strClientNum;
   strClientNum.Format(_T("%d"),oData.m_iClientNum);
   CMapInfoOpt::InsertRowData(DBCusBase_key_iClientNum, strClientNum  ,row_data);
}
