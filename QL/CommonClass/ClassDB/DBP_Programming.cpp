#include "StdAfx.h"
#include "DBP_Programming.h"
#include "DBKeyDef.h"

///////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CDBP_ProgrammingData,  CDataMid, 1)
IMPLEMENT_SERIAL(CDBP_ProgrammingList,  CDataListMid, 1)

std::shared_ptr<CDBP_ProgrammingList> CDBP_ProgrammingList::sm_inst;

CDBP_ProgrammingData::CDBP_ProgrammingData()
{
   ResetData(); 
} 

CDBP_ProgrammingData::~CDBP_ProgrammingData()
{
}

void CDBP_ProgrammingData::ResetData()
{
   
   m_nID                   = 0;
   m_strBrand              = _T("");
   m_nYears                = 0;
   m_strSeason             = _T("");
   m_strTradeFairTime      = _T("");
   m_strArea               = _T("");
   m_nAssociatedPlanningID = 0;
   m_strCreateUserID       = _T("");

   SetDataType(DAT_PROGRAMMING);
}

void CDBP_ProgrammingData:: Copy(CDBP_ProgrammingData *pData)
{
   ASSERT(pData != NULL);
   CDataMid::Copy(pData);
   m_nID                   = pData->m_nID                   ;
   m_strBrand              = pData->m_strBrand             ;
   m_nYears                = pData->m_nYears               ;
   m_strSeason             = pData->m_strSeason            ;
   m_strTradeFairTime      = pData->m_strTradeFairTime     ;
   m_strArea               = pData->m_strArea              ;
   m_nAssociatedPlanningID = pData->m_nAssociatedPlanningID;
   m_strCreateUserID       = pData->m_strCreateUserID      ;
}

BOOL CDBP_ProgrammingData::GetAllDBInfo(CADOConn *pADOConn)
{
   ASSERT(pADOConn != NULL);

   BOOL bRet = FALSE;
   if (NULL != pADOConn)
   {
      m_nID                   = pADOConn->GetValueInt64(DBP_Programming_Key_ID                    );
      m_strBrand              = pADOConn->GetValueString(DBP_Programming_Key_cBrand               );
      m_nYears                = pADOConn->GetValueInt(DBP_Programming_Key_nYears                  );
      m_strSeason             = pADOConn->GetValueString(DBP_Programming_Key_cSeason              );
      m_strTradeFairTime      = pADOConn->GetValueString(DBP_Programming_Key_cTradeFairTime       );
      m_strArea               = pADOConn->GetValueString(DBP_Programming_Key_cArea                );
      m_nAssociatedPlanningID = pADOConn->GetValueInt64(DBP_Programming_Key_nAssociatedPlanningID );
      m_strCreateUserID       = pADOConn->GetValueString(DBP_Programming_Key_cCreateUserID        );

      bRet = TRUE;
   }

   return bRet;
}

BOOL CDBP_ProgrammingData::DelAllDBInfoByID(CADOConn *pADOConn)
{
   ASSERT(NULL != pADOConn);
   CString strSQL = _T("");
   strSQL.Format(_T("delete from %s where %s = '%lld';"),DB_TABLE_PROGRAMMING,DBP_Programming_Key_ID,m_nID);

   return pADOConn->ExecuteSQL(strSQL);
}

BOOL CDBP_ProgrammingData::UpdateAllDBInfoByID( CADOConn *pADOConn )
{
   ASSERT(NULL != pADOConn);
   CString strSQL = _T(""),strKeyValue = _T("");
   //关联企划ID 和 创建人 禁止修改

   strKeyValue.Format(_T("%s = '%s',%s = '%d',%s = '%s',%s = '%s',%s = '%s'"),
      DBP_Programming_Key_cBrand               ,m_strBrand             ,
      DBP_Programming_Key_nYears               ,m_nYears               ,
      DBP_Programming_Key_cSeason              ,m_strSeason            ,
      DBP_Programming_Key_cTradeFairTime       ,m_strTradeFairTime     ,
      DBP_Programming_Key_cArea                ,m_strArea              
      );

   //更新时不需要更新其它的关联信息  
   strSQL.Format(_T("update %s set %s where %s = '%lld';"),DB_TABLE_PROGRAMMING,
      strKeyValue,DBP_Programming_Key_ID,m_nID);

   return pADOConn->ExecuteSQL(strSQL);
}

BOOL CDBP_ProgrammingData::InsertAllDBInfo( CADOConn *pADOConn )
{
   ASSERT(NULL != pADOConn);
   CString strSQL = _T(""),strParam = _T(""),strValue = _T("");
   strParam.Format(_T("%s,%s,%s,%s,%s,%s,%s"),
      DBP_Programming_Key_cBrand,
      DBP_Programming_Key_nYears,DBP_Programming_Key_cSeason,
      DBP_Programming_Key_cTradeFairTime,DBP_Programming_Key_cArea,
      DBP_Programming_Key_nAssociatedPlanningID,DBP_Programming_Key_cCreateUserID);

   strValue.Format(_T("'%s',%d,'%s','%s','%s',%lld,'%s'"),
      m_strBrand ,
      m_nYears ,m_strSeason ,
      m_strTradeFairTime ,m_strArea ,
      m_nAssociatedPlanningID,m_strCreateUserID );

   strSQL.Format(_T("insert into %s (%s) values(%s)"),
      DB_TABLE_PROGRAMMING,strParam,strValue);

   return pADOConn->ExecuteSQL(strSQL);
}

void CDBP_ProgrammingData::Trim()
{
   m_strBrand.Trim();
   m_strSeason.Trim();
   m_strTradeFairTime.Trim();
   m_strArea.Trim();
   m_strCreateUserID.Trim();
}

BOOL CDBP_ProgrammingData::GetAllDBInfoByID( CADOConn *pADOConn )
{
   CString strSQL = _T("");
   strSQL.Format(_T("select * from %s where %s = %d"),DB_TABLE_PROGRAMMING,DBP_Programming_Key_ID,m_nID);
   if (pADOConn != nullptr)
   {
      pADOConn->GetRecordSet(strSQL);
      while(!pADOConn->adoEOF())
      {
        BOOL bValue = GetAllDBInfo(pADOConn);
        if (bValue)
        {
           return TRUE;
        }
         pADOConn->MoveNext();
      }
   }
   return FALSE;
}

BOOL CDBP_ProgrammingData::GetIDByCondition( CADOConn *pADOConn )
{
   ASSERT(pADOConn != nullptr);
   CString strSQL;
   strSQL.Format(_T("select ID from %s \
                    where %s = %d and %s = '%s' and %s = '%s';"),
                    DB_TABLE_PROGRAMMING,
                    DBP_Programming_Key_nYears,m_nYears,
                    DBP_Programming_Key_cSeason,m_strSeason,
                    DBP_Programming_Key_cBrand,m_strBrand
                    );
   pADOConn->GetRecordSet(strSQL);

   if (!pADOConn->adoEOF())
   {
      m_nID = pADOConn->GetValueInt64(DBP_Programming_Key_ID);
      return TRUE;
   }
   return FALSE;
}

CDBP_ProgrammingList::CDBP_ProgrammingList()
{

}
CDBP_ProgrammingList::~CDBP_ProgrammingList()
{

}

CDBP_ProgrammingData* CDBP_ProgrammingList::GetItem(int nIndex)
{
   if (nIndex<0||nIndex>=GetCount())
      return NULL;
   return (CDBP_ProgrammingData*)GetAt(FindIndex(nIndex));
}

void CDBP_ProgrammingList::AddItem(CDBP_ProgrammingData* pItem)
{
   CDBP_ProgrammingData*pData=new CDBP_ProgrammingData;
   pData->Copy(pItem);
   AddTail(pData);
}

void CDBP_ProgrammingList::DeleteItem(int nIndex)
{
   if (nIndex<0||nIndex>GetCount())
      return;
   CDBP_ProgrammingData *pObject=(CDBP_ProgrammingData*)GetItem(nIndex);
   delete pObject;
   pObject=NULL;
   RemoveAt(FindIndex(nIndex));
}

CDBP_ProgrammingList * CDBP_ProgrammingList::Instance()
{
   if(sm_inst.get() == 0)
      sm_inst = shared_ptr<CDBP_ProgrammingList>(new CDBP_ProgrammingList);

   return sm_inst.get();
}
