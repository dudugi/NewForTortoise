#include "StdAfx.h"
#include "DBOrdFlag.h"

//>>>>>>>>>>>>>>>>>>>>>>>CDBOrdFlagInfo<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<//

std::shared_ptr<CDBOrdFlagInfo> CDBOrdFlagInfo::sm_inst;

CDBOrdFlagInfo::CDBOrdFlagInfo()
{
	ResetData();
}

CDBOrdFlagInfo::~CDBOrdFlagInfo()
{
	ResetData();
}

void CDBOrdFlagInfo::ResetData()
{
	m_ID			= 0;
	m_strOrdCode	= _T("");
	m_iPrint_GYD	= 0;		//工艺单打印次数
	m_iPrint_XSM	= 0;		//洗水唛打印次数
	m_iPrint_SCZSD	= 0;		//生产指示单打印次数
	m_iPrint_File	= 0;		//上机文件下载次数
}

void CDBOrdFlagInfo::Copy(CDBOrdFlagInfo * pData)
{
	ASSERT(NULL != pData);
	CDataMid::Copy(pData);

	m_ID			=	pData->m_ID;
	m_strOrdCode	=	pData->m_strOrdCode;
	m_iPrint_GYD	=	pData->m_iPrint_GYD;		//工艺单打印次数
	m_iPrint_XSM	=	pData->m_iPrint_XSM;		//洗水唛打印次数
	m_iPrint_SCZSD	=	pData->m_iPrint_SCZSD;		//生产指示单打印次数
	m_iPrint_File	=	pData->m_iPrint_File;		//上机文件下载次数
}

void CDBOrdFlagInfo::GetAllDataInfo(CADOConn *pADOConn)
{
	ASSERT(NULL != pADOConn);

	m_ID = pADOConn->GetValueInt(DBORDFLAG_KEY_ID);
	m_strOrdCode = pADOConn->GetValueString(DBORDFLAG_KEY_OrderCode);
	m_iPrint_GYD = pADOConn->GetValueInt(DBORDFLAG_KEY_Print_GYD);
	m_iPrint_XSM = pADOConn->GetValueInt(DBORDFLAG_KEY_Print_XSM);
	m_iPrint_SCZSD = pADOConn->GetValueInt(DBORDFLAG_KEY_Print_SCZSD);
	m_iPrint_File = pADOConn->GetValueInt(DBORDFLAG_KEY_DownLd_MacFile);
}

CDBOrdFlagInfo * CDBOrdFlagInfo::Instance()
{
	if(sm_inst.get() == 0)
		sm_inst = shared_ptr<CDBOrdFlagInfo>(new CDBOrdFlagInfo);

	return sm_inst.get();
}


//>>>>>>>>>>>>>>>>>>>>>>>CDBOrdFlagInfo_List<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<//

std::shared_ptr<CDBOrdFlagInfo_List> CDBOrdFlagInfo_List::sm_inst;

CDBOrdFlagInfo_List::CDBOrdFlagInfo_List()
{

}

CDBOrdFlagInfo_List::~CDBOrdFlagInfo_List()
{

}

CDBOrdFlagInfo_List * CDBOrdFlagInfo_List::Instance()
{
	if(sm_inst.get() == 0)
		sm_inst = shared_ptr<CDBOrdFlagInfo_List>(new CDBOrdFlagInfo_List);

	return sm_inst.get();
}

BOOL CDBOrdFlagInfo_List::WriteOrderFlag(__in CADOConn *pADOConn,__in vector<CString>& vecOrder,__in BOOL bGYD,__in BOOL bXSM,__in BOOL bSCZSD,__in BOOL bFile,__out CString& strErr)
{
	ASSERT(NULL != pADOConn);
	CString strSQL_Final;
	int iGYD = bGYD?1:0;
	int iXSM = bXSM?1:0;
	int iSCZSD = bSCZSD?1:0;
	int iFile = bFile?1:0;
	CString strOrder;
	for (int i=0; i<(int)vecOrder.size(); ++i)
	{
		strOrder = vecOrder[i];
		CString strSQL2 = _T("");
      strSQL2.Format(_T("exec P_UpdateOrderFlag '%s';"),strOrder);

		if (pADOConn->ExecuteSQL(strSQL2) == FALSE )
		{
			strErr += strOrder + _T("保存数据时失败;\n");
		}
	}

	return TRUE;
}

BOOL CDBOrdFlagInfo_List::GetPrintCount(__in CADOConn *pADOConn,__in CString& strOrder,__out CDBOrdFlagInfo* pData)
{
   ASSERT(NULL != pADOConn);
   if (strOrder.IsEmpty())
   {
      return FALSE;
   }
   if (pData == NULL)
   {
      pData = new CDBOrdFlagInfo;
   }
   pData->ResetData();
   CString strSql = _T("");
   strSql.Format(_T("exec P_GetOrderFlagInfo '%s';"),strOrder);
   pADOConn->GetRecordSet(strSql);
   if (!pADOConn->adoEOF())
   {
      pData->m_strOrdCode = strOrder;
      pData->m_iPrint_GYD = pADOConn->GetValueInt(_T("gyd"));
      pData->m_iPrint_XSM = pADOConn->GetValueInt(_T("xsm"));
      pData->m_iPrint_SCZSD = pADOConn->GetValueInt(_T("sczsd"));
      pData->m_iPrint_File = pADOConn->GetValueInt(_T("macfile"));
   }
   return TRUE;
}
