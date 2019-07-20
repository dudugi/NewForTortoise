#include "StdAfx.h"
#include "DBProcessRecords.h"
#include "DBKeyDef.h"
#include "DBKeyDef_V.h"

IMPLEMENT_SERIAL(CDBProcessRecordsData,  CDataMid, 1)
IMPLEMENT_SERIAL(CDBProcessRecordsList,  CDataListMid, 1)

CDBProcessRecordsData::CDBProcessRecordsData(void)
{
   ResetData();
}

CDBProcessRecordsData::~CDBProcessRecordsData(void)
{
}

void CDBProcessRecordsData::ResetData()
{
   m_nID                = 0;
   m_strCode            = _T("");
   m_strGXName          = _T("");
   m_strPersonCode      = _T("");
   m_strMemo            = _T("");
   m_nState             = 0;
   m_fPieceWeight       = 0;
   m_fDuration          = 0;
   m_fGongjia           = 0;
   m_strRecordTime      = _T("");
   m_strToPerson = _T("");
   SetDataType(DAT_ASSIGN);
}

void CDBProcessRecordsData::Copy( CDBProcessRecordsData *pData )
{
   ASSERT(pData != NULL);
   CDataMid::Copy(pData);

   m_nID                = pData->m_nID               ;
   m_strCode            = pData->m_strCode           ;
   m_strGXName          = pData->m_strGXName         ;
   m_strPersonCode      = pData->m_strPersonCode     ;
   m_strMemo            = pData->m_strMemo           ;
   m_nState             = pData->m_nState            ;
   m_fPieceWeight       = pData->m_fPieceWeight      ;
   m_fDuration          = pData->m_fDuration         ;
   m_fGongjia           = pData->m_fGongjia          ;
   m_strRecordTime      = pData->m_strRecordTime     ;
   m_strToPerson        = pData->m_strToPerson       ;
}

BOOL CDBProcessRecordsData::GetAllDBInfo( CADOConn *pADOConn)
{
   BOOL bRet = FALSE;
   ASSERT(NULL != pADOConn);
   if (NULL != pADOConn)
   {
      m_nID                = pADOConn->GetValueInt64 (DBProcessRecords_Key_ID              );
      m_strCode            = pADOConn->GetValueString(DBProcessRecords_Key_cCode           );
      m_strGXName          = pADOConn->GetValueString(DBProcessRecords_Key_cGXName         );
      m_strPersonCode      = pADOConn->GetValueString(DBProcessRecords_Key_cPersonCode     );
      m_strMemo            = pADOConn->GetValueString(DBProcessRecords_Key_cMemo           );
      m_nState             = pADOConn->GetValueInt(DBProcessRecords_Key_iState             );
      m_fPieceWeight       = pADOConn->GetValueFloat(DBProcessRecords_Key_iPieceWeight     );
      m_fDuration          = pADOConn->GetValueFloat(DBProcessRecords_Key_iDuration        );
      m_fGongjia           = pADOConn->GetValueFloat(DBProcessRecords_Key_iGongjia         );
      m_strRecordTime      = pADOConn->GetValueString(DBProcessRecords_Key_dRecordTime     );
      m_strToPerson        = pADOConn->GetValueString(DBProcessRecords_Key_cToPerson       );
      bRet = TRUE;
   }

   return bRet;
}

BOOL CDBProcessRecordsData::InsertAllDBInfo( CADOConn *pADOConn )
{
   ASSERT(pADOConn != NULL);
   CString strSQL = GetInsertSQL();
   BOOL bRet = FALSE;
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

CString CDBProcessRecordsData::GetInsertSQL() const
{
   ASSERT(!m_strCode.IsEmpty());
   ASSERT(!m_strPersonCode.IsEmpty());

   CString strSQL = _T(""),strFormat = _T(""),strValue = _T("");

   CString strGetDateStr = _T("");
   strGetDateStr = DBS_GETDATESTR;

   CString strEmpty = _T("");
   CString strEmptyTime = _T("''");
   //                    1 ,2 ,3 ,4 ,5 ,6 ,7 ,8 ,9 ,10
   strFormat.Format(_T("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s"),
                       DBProcessRecords_Key_cCode             ,//1
                       DBProcessRecords_Key_cGXName           ,//2
                       DBProcessRecords_Key_cPersonCode       ,//3
                       DBProcessRecords_Key_cMemo             ,//4
                       DBProcessRecords_Key_iState            ,//5
                       DBProcessRecords_Key_iPieceWeight      ,//6
                       DBProcessRecords_Key_iDuration         ,//7
                       DBProcessRecords_Key_iGongjia          ,//8
                       DBProcessRecords_Key_dRecordTime       ,//9
                       DBProcessRecords_Key_cToPerson
                       );
   //                    1   ,2   ,3  ,4   ,5     6     7      8      9     10
   strValue.Format(_T("'%s','%s','%s','%s' ,'%d','%.2f','%.2f','%.1f',%s,'%s'"),
                      m_strCode                       ,//1
                      m_strGXName                     ,//2
                      m_strPersonCode                 ,//3
                      m_strMemo                       ,//4
                      m_nState                        ,//5
                      m_fPieceWeight                  ,//6
                      m_fDuration                     ,//7
                      m_fGongjia                      ,//8
                      DBS_GETDATESTR                  ,//9
                      m_strToPerson
                      );


   strSQL.Format(_T("insert into %s(%s) values(%s)"),DB_TABLE_PROCESSRECORDS,strFormat,strValue);
   return strSQL;
}

CString CDBProcessRecordsData::GetDeleteByStyleNoSql(const CString & strStyleNo)
{
   CString strSQL = _T("");
   strSQL.Format(_T("delete from %s where %s='%s';"),DB_TABLE_PROCESSRECORDS,
      DBProcessRecords_Key_cCode,strStyleNo);
   return strSQL;
}

void CDBProcessRecordsData::Trim()
{
   m_strCode .Trim();
   m_strGXName .Trim();
   m_strPersonCode .Trim();
   m_strMemo .Trim();
   m_strRecordTime.Trim();
}

CDBProcessRecordsList::CDBProcessRecordsList( void )
{

}

CDBProcessRecordsList::~CDBProcessRecordsList( void )
{

}

CDBProcessRecordsData* CDBProcessRecordsList::GetItem(int nIndex)
{
   if (nIndex<0||nIndex>=GetCount())
      return NULL;
   return (CDBProcessRecordsData*)GetAt(FindIndex(nIndex));
}

CDBProcessRecordsData* CDBProcessRecordsList::GetItem(CString strOrderNo)
{
   ASSERT(!strOrderNo.IsEmpty());
   CDBProcessRecordsData * pRet = NULL;
   int nIndex = 0,nCount = GetCount();
   for (nIndex = 0;nIndex < nCount;nIndex++)
   {
      auto pData = GetItem(nIndex);
      if (pData->m_strCode == strOrderNo)
      {
         pRet = pData;
         break;
      }
   }
   return pRet;
}

void CDBProcessRecordsList::AddItem( CDBProcessRecordsData *pItem )
{
   CDBProcessRecordsData * pData = new CDBProcessRecordsData;
   pData->Copy(pItem);
   AddTail(pData);
}

void CDBProcessRecordsList::DeleteItem(int nIndex)
{
   if (nIndex<0||nIndex>GetCount())
      return;
   CDBProcessRecordsData *pObject=(CDBProcessRecordsData*)GetItem(nIndex);
   delete pObject;
   pObject=NULL;
   RemoveAt(FindIndex(nIndex));
}

void CDBProcessRecordsList::DeleteItem(CString strOrderNo)
{
   ASSERT(!strOrderNo.IsEmpty());
   int nIndex = 0,nCount = GetCount();
   for (nIndex = 0;nIndex < nCount;nIndex++)
   {
      auto pData = GetItem(nIndex);
      if (pData->m_strCode == strOrderNo)
      {
         delete pData;
         pData=NULL;
         RemoveAt(FindIndex(nIndex));
         break;
      }
   }
}

void CDBProcessRecordsList::DeleteItemByID(__int64 nID)
{
   ASSERT(nID != 0);
   int nIndex = 0,nCount = GetCount();
   for (nIndex = 0;nIndex < nCount;nIndex++)
   {
      auto pData = GetItem(nIndex);
      if (pData->m_nID == nID)
      {
         delete pData;
         pData=NULL;
         RemoveAt(FindIndex(nIndex));
         break;
      }
   }
}

