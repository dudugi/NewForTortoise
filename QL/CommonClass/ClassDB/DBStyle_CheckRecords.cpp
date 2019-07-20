#include "StdAfx.h"
#include "DBStyle_CheckRecords.h"
#include "DBKeyDef.h"

IMPLEMENT_SERIAL(CDBStyle_CheckRecordsData,  CDataMid, 1)

CDBStyle_CheckRecordsData::CDBStyle_CheckRecordsData(void)
{
   ResetData();
}


CDBStyle_CheckRecordsData::~CDBStyle_CheckRecordsData(void)
{
}

void CDBStyle_CheckRecordsData::ResetData()
{
   m_nID             = 0;
   m_nStyleID        = 0;
   m_strPerson       = _T("");
   m_nState          = 0;
   m_strRecordTime   = _T("");

   SetDataType(DAT_STYLE_CHECKRECORDS);
}

void CDBStyle_CheckRecordsData::Copy(CDBStyle_CheckRecordsData *pData)
{
	ASSERT(pData != NULL);
	CDataMid::Copy(pData);

    m_nID            = pData-> m_nID          ;
    m_nStyleID       = pData-> m_nStyleID     ;
    m_strPerson      = pData-> m_strPerson    ;
    m_nState         = pData-> m_nState       ;
    m_strRecordTime  = pData-> m_strRecordTime;
}

BOOL CDBStyle_CheckRecordsData::GetAllDBInfo( CADOConn *pADOConn )
{
	BOOL bRet = FALSE;
	ASSERT(pADOConn != NULL);

	if (NULL == pADOConn)
	{
		bRet = FALSE;
	}
	else
	{
      m_nID           = pADOConn->GetValueInt64 (DBStyle_CheckRecords_ID     );
      m_nStyleID      = pADOConn->GetValueInt   (DBStyle_CheckRecords_SID    );
      m_strPerson     = pADOConn->GetValueString(DBStyle_CheckRecords_cPerson);
      m_nState        = pADOConn->GetValueInt   (DBStyle_CheckRecords_nState );
      m_strRecordTime = pADOConn->GetValueString(DBStyle_CheckRecords_cTime  );

		bRet = TRUE;
	}

	return bRet;
}

BOOL CDBStyle_CheckRecordsData::InsertAllDBInfo( CADOConn *pADOConn )
{
	ASSERT(pADOConn != NULL);

	BOOL bRet = FALSE;
	CString strSQL = GetInsertSQL();
	if(pADOConn->ExecuteSQL(strSQL))
	{
		bRet = TRUE;
	}
	else
	{
		bRet = FALSE;
	}

	return bRet;
}

CString CDBStyle_CheckRecordsData::GetInsertSQL() const
{
   CString strSQL;
   strSQL.Format(_T("insert into %s (%s,%s,%s,%s) values('%d','%s','%d',%s)"),
      DB_TABLE_STYLE_CHECKRECORDS,
      DBStyle_CheckRecords_SID    ,
      DBStyle_CheckRecords_cPerson,
      DBStyle_CheckRecords_nState ,
      DBStyle_CheckRecords_cTime  ,
      m_nStyleID,
      m_strPerson,
      m_nState,
      DBS_GETDATESTR
      );
   return strSQL;
}

IMPLEMENT_SERIAL(CDBStyle_CheckRecordsList,  CDataListMid, 1)



CDBStyle_CheckRecordsList::CDBStyle_CheckRecordsList()
{

}
CDBStyle_CheckRecordsList::~CDBStyle_CheckRecordsList()
{

}

