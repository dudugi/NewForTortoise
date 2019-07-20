#include "StdAfx.h"
#include "DBStyle_VersionRecords.h"
#include "DBKeyDef.h"

IMPLEMENT_SERIAL(CDBStyle_VersionRecordsData,  CDataMid, 1)

CDBStyle_VersionRecordsData::CDBStyle_VersionRecordsData(void)
{
   ResetData();
}


CDBStyle_VersionRecordsData::~CDBStyle_VersionRecordsData(void)
{
}

void CDBStyle_VersionRecordsData::ResetData()
{
   m_nID             = 0;
   m_nStyleID        = 0;
   m_strPerson       = _T("");
   m_nState          = 0;
   m_strRecordTime   = _T("");
   m_strRecordTime   = _T("");

   SetDataType(DAT_STYLE_VERSIONRECORDS);
}

void CDBStyle_VersionRecordsData::Copy(CDBStyle_VersionRecordsData *pData)
{
	ASSERT(pData != NULL);
	CDataMid::Copy(pData);

    m_nID            = pData-> m_nID          ;
    m_nStyleID       = pData-> m_nStyleID     ;
    m_strPerson      = pData-> m_strPerson    ;
    m_nState         = pData-> m_nState       ;
    m_strRecordTime  = pData-> m_strRecordTime;
    m_strRemark      = pData->m_strRemark     ;
}

BOOL CDBStyle_VersionRecordsData::GetAllDBInfo( CADOConn *pADOConn )
{
	BOOL bRet = FALSE;
	ASSERT(pADOConn != NULL);

	if (NULL == pADOConn)
	{
		bRet = FALSE;
	}
	else
	{
      m_nID           = pADOConn->GetValueInt64 (DBStyle_VersionRecords_ID     );
      m_nStyleID      = pADOConn->GetValueInt   (DBStyle_VersionRecords_SID    );
      m_strPerson     = pADOConn->GetValueString(DBStyle_VersionRecords_cPerson);
      m_nState        = pADOConn->GetValueInt   (DBStyle_VersionRecords_nState );
      m_strRecordTime = pADOConn->GetValueString(DBStyle_VersionRecords_cTime  );
      m_strRemark     = pADOConn->GetValueString(DBStyle_VersionRecords_cRemark);

		bRet = TRUE;
	}

	return bRet;
}

BOOL CDBStyle_VersionRecordsData::InsertAllDBInfo( CADOConn *pADOConn )
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

CString CDBStyle_VersionRecordsData::GetInsertSQL() const
{
   CString strSQL;
   strSQL.Format(_T("insert into %s (%s,%s,%s,%s,%s) values('%d','%s','%d',%s,'%s')"),
      DB_TABLE_STYLE_VERSIONRECORDS,
      DBStyle_VersionRecords_SID    ,
      DBStyle_VersionRecords_cPerson,
      DBStyle_VersionRecords_nState ,
      DBStyle_VersionRecords_cTime  ,
      DBStyle_VersionRecords_cRemark,
      m_nStyleID,
      m_strPerson,
      m_nState,
      DBS_GETDATESTR,
      m_strRemark
      );
   return strSQL;
}

