#include "StdAfx.h"
#include "DBPieceInfo.h"
#include "DBKeyDef.h"


CDBPieceInfoData::CDBPieceInfoData(void)
{
   ResetData();
}

CDBPieceInfoData::~CDBPieceInfoData(void)
{
}

void CDBPieceInfoData::ResetData()
{
   m_nID             = 0                  ;
   m_strcCode        = _T("")             ;
   m_nPieceType      = En_PieceComputer   ;
   m_strcPieceName   = _T("")             ;
   m_strcRemark      = _T("")             ;

   SetDataType(DAT_PIECEINFO);
}

void CDBPieceInfoData::Copy(CDBPieceInfoData *pData)
{
   ASSERT(pData != NULL);
   CDataMid::Copy(pData);

   m_nID             =  pData->m_nID          ;//自增ID
   m_strcCode        =  pData->m_strcCode     ;//订单号
   m_nPieceType      =  pData->m_nPieceType   ;//类型
   m_strcPieceName   =  pData->m_strcPieceName;//备注的详情
   m_strcRemark      =  pData->m_strcRemark   ;//备注的详情
}

BOOL CDBPieceInfoData::GetAllDBInfo(CADOConn *pADOConn)
{
   ASSERT(pADOConn != NULL);
   BOOL bRet = TRUE;
   if (NULL == pADOConn)
   {
      bRet = FALSE;
   }
   else
   {
      m_nID                = pADOConn->GetValueInt    (DBPieceInfo_Key_ID           );
      m_strcCode           = pADOConn->GetValueString (DBPieceInfo_Key_cCode        );
      m_nPieceType         = pADOConn->GetValueInt    (DBPieceInfo_Key_nPieceType   );
      m_strcPieceName      = pADOConn->GetValueString (DBPieceInfo_Key_cPieceName   );
      m_strcRemark         = pADOConn->GetValueString (DBPieceInfo_Key_cRemark      );

      bRet = TRUE;
   }

   return bRet;
}

BOOL CDBPieceInfoData::InsertAllDBInfo(CADOConn *pADOConn)
{
   ASSERT(pADOConn != NULL);
   BOOL bRet = TRUE;

   if (NULL == pADOConn)
   {
      bRet = FALSE;
   }
   else
   {
      CString strSQL = _T("");
      strSQL.Format(_T("Insert into %s (%s,%s,%s,%s)\
                       values('%s','%d','%s','%s')"),
         DB_TABLE_PIECEINFO,
         DBPieceInfo_Key_cCode,DBPieceInfo_Key_nPieceType,DBPieceInfo_Key_cPieceName,DBPieceInfo_Key_cRemark,
         m_strcCode,m_nPieceType,m_strcPieceName,m_strcRemark
         );

      bRet = pADOConn->ExecuteSQL(strSQL);
   }

   return bRet;

}

CDBPieceInfoList::CDBPieceInfoList()
{

}

CDBPieceInfoList::~CDBPieceInfoList()
{
   Empty();
}

CDBPieceInfoData* CDBPieceInfoList::GetItem(int nIndex)
{
   if (nIndex<0||nIndex>=GetCount())
      return NULL;
   return (CDBPieceInfoData*)GetAt(FindIndex(nIndex));
}

CDBPieceInfoData* CDBPieceInfoList::GetItemByPieceName(const CString & strPieceName)
{
   ASSERT(!strPieceName.IsEmpty());
   if (!strPieceName.IsEmpty())
   {
      int nIndex = 0,nCount = GetCount();
      for (nIndex = 0;nIndex < nCount;++nIndex)
      {
         auto pData = GetItem(nIndex);
         if (NULL != pData && (0 == strPieceName.CompareNoCase(pData->m_strcPieceName)))
         {
            return pData;
         }
      }
   }
   return NULL;
}

void CDBPieceInfoList::AddItem(CDBPieceInfoData* pItem)
{
   CDBPieceInfoData*pData=new CDBPieceInfoData;
   pData->Copy(pItem);
   AddTail(pData);
}

void CDBPieceInfoList::DeleteItem(int nIndex)
{
   if (nIndex<0||nIndex>GetCount())
      return;
   CDBPieceInfoData *pObject=(CDBPieceInfoData*)GetItem(nIndex);
   delete pObject;
   pObject=NULL;
   RemoveAt(FindIndex(nIndex));
}

BOOL CDBPieceInfoList::GetListFromDB(CADOConn *pADOConn,const CString & strcCode)
{
   BOOL bRet = FALSE;

   ASSERT(pADOConn != NULL);
   ASSERT(!strcCode.IsEmpty());
   Empty();
   if (strcCode.IsEmpty() || NULL == pADOConn)
   {
      bRet = FALSE;
   }
   else
   {
      CString strSQL = _T("");
      strSQL.Format(_T("select * from %s where %s = '%s'"),DB_TABLE_PIECEINFO,DBPieceInfo_Key_cCode,strcCode);

      bRet = pADOConn->GetRecordSet(strSQL);

      while (!pADOConn->adoEOF())
      {
         CDBPieceInfoData oData;
         oData.GetAllDBInfo(pADOConn);

         AddItem(&oData);
         pADOConn->MoveNext();
      }
   }

   return bRet;
}

BOOL CDBPieceInfoList::InsetAllDBInfo(CADOConn * pADOConn)
{
   BOOL bRet = FALSE;

   CString strSQL = _T("");
   int nPieceIndex = 0,nPieceCount = GetCount();
   for (nPieceIndex = 0;nPieceIndex < nPieceCount;++nPieceIndex)
   {
      auto pPieceData = GetItem(nPieceIndex);
      if (NULL != pPieceData)
      {
         strSQL.Format(_T("Insert into %s (%s,%s,%s,%s)\
                          values('%s','%d','%s','%s')"),
                          DB_TABLE_PIECEINFO,
                          DBPieceInfo_Key_cCode,DBPieceInfo_Key_nPieceType,DBPieceInfo_Key_cPieceName,DBPieceInfo_Key_cRemark,
                          pPieceData->m_strcCode,pPieceData->m_nPieceType,pPieceData->m_strcPieceName,pPieceData->m_strcRemark
                          );

         pADOConn->AppendBatchSQL(strSQL);
      }
   }

   bRet = pADOConn->ExecuteBatchSQL();

   return bRet;

}
