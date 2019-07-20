#include "StdAfx.h"
#include "DBP_TextBoard.h"
#include "DBKeyDef.h"

///////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CDBP_TextBoardData,  CDBProofingAssociatedData, 1)
IMPLEMENT_SERIAL(CDBP_TextBoardList,  CDataListMid, 1)

std::shared_ptr<CDBP_TextBoardList> CDBP_TextBoardList::sm_inst;

CDBP_TextBoardData::CDBP_TextBoardData()
{
   ResetData(); 
} 

CDBP_TextBoardData::~CDBP_TextBoardData()
{
}

void CDBP_TextBoardData::ResetData()
{
   CDBProofingAssociatedData::ResetData();
   m_strTextInfo     =  _T("");
   SetDataType(DAT_TEXTBOARD);
}

void CDBP_TextBoardData:: Copy(CDBP_TextBoardData *pData)
{
   ASSERT(pData != NULL);
   CDBProofingAssociatedData::Copy(pData);

   m_strTextInfo     =  pData->m_strTextInfo  ;
}

BOOL CDBP_TextBoardData::GetAllDBInfo(CADOConn *pADOConn)
{
   ASSERT(pADOConn != NULL);

   BOOL bRet = FALSE;

   return bRet;
}

BOOL CDBP_TextBoardData::DelAllDBInfoByID(CADOConn *pADOConn)
{
   ASSERT(NULL != pADOConn);
   CString strSQL = _T("");
   strSQL.Format(_T("delete from %s where %s = '%lld';"),DB_TABLE_TEXTBOARD,DBP_TextBoard_Key_ID,m_nID);

   return pADOConn->ExecuteSQL(strSQL);
}

BOOL CDBP_TextBoardData::UpdateAllDBInfoByID( CADOConn *pADOConn )
{
   ASSERT(NULL != pADOConn);
   CString strSQL = _T("");
   //更新时不需要更新其它的关联信息  
   strSQL.Format(_T("update %s set %s = '%s' where %s = '%lld';"),DB_TABLE_TEXTBOARD,
      DBP_TextBoard_Key_cTextInfo,m_strTextInfo,
      DBP_TextBoard_Key_ID,m_nID);

   return pADOConn->ExecuteSQL(strSQL);
}

BOOL CDBP_TextBoardData::InsertAllDBInfo( CADOConn *pADOConn )
{
   ASSERT(NULL != pADOConn);
   CString strSQL = _T(""),strParam = _T(""),strValue = _T("");
   strParam.Format(_T("%s,%s,%s"),
      DBP_TextBoard_Key_nType,DBP_TextBoard_Key_nAssociatedID,DBP_TextBoard_Key_cTextInfo);

   strValue.Format(_T("%d,%lld,%s"),m_nType,m_nAssociatedID,m_strTextInfo);

   strSQL.Format(_T("insert into %s (%s) values(%s);"),
      DB_TABLE_TEXTBOARD,strParam,strValue);

   return pADOConn->ExecuteSQL(strSQL);
}

void CDBP_TextBoardData::Trim()
{
   m_strTextInfo.Trim();
}

BOOL CDBP_TextBoardData::GetAllDBInfoBynAssociatedID( CADOConn *pADOConn,__int64 nAssociatedID)
{
   CString strSQL = _T("");
   strSQL.Format(_T("select * from %s where (%s = %lld) and (%s = %d)"),DB_TABLE_TEXTBOARD,DBP_TextBoard_Key_nAssociatedID,nAssociatedID,DBP_TextBoard_Key_nType,m_nType);
   if(nullptr ==pADOConn)
   {
      return FALSE;
   }

   pADOConn->GetRecordSet(strSQL);
   if (!pADOConn->adoEOF())
   {
      m_nID             =  pADOConn->GetValueInt64( DBP_TextBoard_Key_ID           );
      m_nType           =  m_nType;
      m_nAssociatedID   =  pADOConn->GetValueInt(   DBP_TextBoard_Key_nAssociatedID);
      m_strTextInfo     =  pADOConn->GetValueString(DBP_TextBoard_Key_cTextInfo    );
   }

   return TRUE;
}

CDBP_TextBoardList::CDBP_TextBoardList()
{

}
CDBP_TextBoardList::~CDBP_TextBoardList()
{

}

CDBP_TextBoardData* CDBP_TextBoardList::GetItem(int nIndex)
{
   if (nIndex<0||nIndex>=GetCount())
      return NULL;
   return (CDBP_TextBoardData*)GetAt(FindIndex(nIndex));
}

void CDBP_TextBoardList::AddItem(CDBP_TextBoardData* pItem)
{
   CDBP_TextBoardData*pData=new CDBP_TextBoardData;
   pData->Copy(pItem);
   AddTail(pData);
}

void CDBP_TextBoardList::DeleteItem(int nIndex)
{
   if (nIndex<0||nIndex>GetCount())
      return;
   CDBP_TextBoardData *pObject=(CDBP_TextBoardData*)GetItem(nIndex);
   delete pObject;
   pObject=NULL;
   RemoveAt(FindIndex(nIndex));
}

CDBP_TextBoardList * CDBP_TextBoardList::Instance()
{
   if(sm_inst.get() == 0)
      sm_inst = shared_ptr<CDBP_TextBoardList>(new CDBP_TextBoardList);

   return sm_inst.get();
}
