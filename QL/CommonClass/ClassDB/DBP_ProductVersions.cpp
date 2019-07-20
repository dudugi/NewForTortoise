#include "StdAfx.h"
#include "DBP_ProductVersions.h"
#include "DBKeyDef.h"

///////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CDBP_ProductVersionsData,  CDataMid, 1)
IMPLEMENT_SERIAL(CDBP_ProductVersionsList,  CDataListMid, 1)

std::shared_ptr<CDBP_ProductVersionsList> CDBP_ProductVersionsList::sm_inst;

CDBP_ProductVersionsData::CDBP_ProductVersionsData()
{
   ResetData(); 
} 

CDBP_ProductVersionsData::~CDBP_ProductVersionsData()
{
}

void CDBP_ProductVersionsData::ResetData()
{
   
   m_nID                   = 0;
   m_nProductID            = 0;
   m_strVersion            = _T("");
   m_nVersionNo            = 0;
   m_strCode               = _T("");
   m_strAlias              = _T("");

   SetDataType(DAT_PRODUCTVERSIONS);
}

void CDBP_ProductVersionsData:: Copy(CDBP_ProductVersionsData *pData)
{
   ASSERT(pData != NULL);
   CDataMid::Copy(pData);
   m_nID        = pData->m_nID       ;
   m_nProductID = pData->m_nProductID;
   m_strVersion = pData->m_strVersion;
   m_nVersionNo = pData->m_nVersionNo;
   m_strCode    = pData->m_strCode   ;
   m_strAlias   = pData->m_strAlias  ;
}

BOOL CDBP_ProductVersionsData::GetAllDBInfo(CADOConn *pADOConn)
{
   ASSERT(pADOConn != NULL);

   BOOL bRet = FALSE;
   if (NULL != pADOConn)
   {
      m_nID        = pADOConn->GetValueInt64(DBP_ProductVersions_Key_ID        );
      m_nProductID = pADOConn->GetValueInt64(DBP_ProductVersions_Key_nProductID);
      m_strVersion = pADOConn->GetValueString(DBP_ProductVersions_Key_cVersion  );
      m_nVersionNo = pADOConn->GetValueInt   (DBP_ProductVersions_Key_nVersionNo);
      m_strCode    = pADOConn->GetValueString(DBP_ProductVersions_Key_cCode     );
      m_strAlias   = pADOConn->GetValueString(DBP_ProductVersions_Key_cAlias    );

      bRet = TRUE;
   }

   return bRet;
}

BOOL CDBP_ProductVersionsData::DelAllDBInfoByID(CADOConn *pADOConn)
{
   ASSERT(NULL != pADOConn);
   CString strSQL = _T("");
   strSQL.Format(_T("delete from %s where %s = '%lld';"),DB_TABLE_PRODUCTVERSION,DBP_ProductVersions_Key_ID,m_nID);

   return pADOConn->ExecuteSQL(strSQL);
}

BOOL CDBP_ProductVersionsData::UpdateAllDBInfoByID( CADOConn *pADOConn )
{
   ASSERT(NULL != pADOConn);
   CString strSQL = _T(""),strKeyValue = _T("");
   //关联企划ID 和 创建人 禁止修改

   strKeyValue.Format(_T("%s = '%s',%s = '%s',%s = '%s'"),
      DBP_ProductVersions_Key_cVersion         ,m_strVersion     ,
      DBP_ProductVersions_Key_cCode            ,m_strCode        ,
      DBP_ProductVersions_Key_cAlias           ,m_strAlias
      );

   //更新时不需要更新其它的关联信息  
   strSQL.Format(_T("update %s set %s where %s = '%lld';"),DB_TABLE_PRODUCTVERSION,
      strKeyValue,DBP_ProductVersions_Key_ID,m_nID);

   return pADOConn->ExecuteSQL(strSQL);
}

BOOL CDBP_ProductVersionsData::InsertAllDBInfo( CADOConn *pADOConn )
{
   ASSERT(NULL != pADOConn);
   CString strSQL = _T(""),strParam = _T(""),strValue = _T("");
   strParam.Format(_T("%s,%s,%s,%s,%s"),
      DBP_ProductVersions_Key_nProductID,
      DBP_ProductVersions_Key_cVersion  ,
      DBP_ProductVersions_Key_nVersionNo,
      DBP_ProductVersions_Key_cCode     ,
      DBP_ProductVersions_Key_cAlias    
      );

   strValue.Format(_T("'%d','%s','%d','%s','%s'"),
      m_nProductID,m_strVersion,m_nVersionNo,m_strCode,m_strAlias);

   strSQL.Format(_T("insert into %s (%s) values(%s);"),
      DB_TABLE_PRODUCTVERSION,strParam,strValue);

   return pADOConn->ExecuteSQL(strSQL);
}

void CDBP_ProductVersionsData::Trim()
{
   m_strCode.Trim();
   m_strVersion.Trim();
   m_strAlias.Trim();
}

CDBP_ProductVersionsList::CDBP_ProductVersionsList()
{

}
CDBP_ProductVersionsList::~CDBP_ProductVersionsList()
{

}

CDBP_ProductVersionsData* CDBP_ProductVersionsList::GetItem(int nIndex)
{
   if (nIndex<0||nIndex>=GetCount())
      return NULL;
   return (CDBP_ProductVersionsData*)GetAt(FindIndex(nIndex));
}

void CDBP_ProductVersionsList::AddItem(CDBP_ProductVersionsData* pItem)
{
   CDBP_ProductVersionsData*pData=new CDBP_ProductVersionsData;
   pData->Copy(pItem);
   AddTail(pData);
}

void CDBP_ProductVersionsList::DeleteItem(int nIndex)
{
   if (nIndex<0||nIndex>GetCount())
      return;
   CDBP_ProductVersionsData *pObject=(CDBP_ProductVersionsData*)GetItem(nIndex);
   delete pObject;
   pObject=NULL;
   RemoveAt(FindIndex(nIndex));
}

CDBP_ProductVersionsList * CDBP_ProductVersionsList::Instance()
{
   if(sm_inst.get() == 0)
      sm_inst = shared_ptr<CDBP_ProductVersionsList>(new CDBP_ProductVersionsList);

   return sm_inst.get();
}
