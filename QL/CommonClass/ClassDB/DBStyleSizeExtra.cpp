#include "StdAfx.h"
#include "DBStyleSizeExtra.h"
#include "DBKeyDef.h"

//部位表

IMPLEMENT_SERIAL(CDBStyleSizeExtraData,  CDataMid, 1)
IMPLEMENT_SERIAL(CDBStyleSizeExtraList,  CDataListMid, 1)

std::shared_ptr<CDBStyleSizeExtraData> CDBStyleSizeExtraData::sm_inst;
std::shared_ptr<CDBStyleSizeExtraList> CDBStyleSizeExtraList::sm_inst;

CDBStyleSizeExtraData::CDBStyleSizeExtraData()
{
	ResetData();
}

CDBStyleSizeExtraData::~CDBStyleSizeExtraData()
{

}

void CDBStyleSizeExtraData::ResetData()
{
   m_nID = 0;  
   m_cStyleNo  =_T("")       ;//款号
   m_iPartID =0       ;//尺寸部位
   m_cMemo =_T("") ;//部位说明
   m_fCeLiangBeforeSize=0;//测量前尺寸
   m_fCeLiangCusSize=0;//客户测量尺寸
   m_fWaterBeforeSize=0;//洗水前尺寸
   m_fWaterAfterSize=0;//洗水后尺寸
}

void CDBStyleSizeExtraData::Copy(CDBStyleSizeExtraData *pData)
{
	ASSERT(pData != NULL);
	CDataMid::Copy(pData);

   m_nID=  pData->m_nID;  
   m_cStyleNo=  pData->m_cStyleNo         ;//款号
   m_iPartID=  pData->m_iPartID        ;//尺寸部位
   m_cMemo=  pData->m_cMemo;//部位说明
   m_fCeLiangBeforeSize=  pData->m_fCeLiangBeforeSize;//测量前尺寸
   m_fCeLiangCusSize=  pData->m_fCeLiangCusSize;//客户测量尺寸
   m_fWaterBeforeSize=  pData->m_fWaterBeforeSize;//洗水前尺寸
   m_fWaterAfterSize=  pData->m_fWaterAfterSize;//洗水后尺寸
}

void CDBStyleSizeExtraData::Serialize(CArchive& ar)
{
	CDataMid::Serialize(ar);//父类函数	
}

CDBStyleSizeExtraData * CDBStyleSizeExtraData::Instance()
{
	if(sm_inst.get() == 0)
		sm_inst = shared_ptr<CDBStyleSizeExtraData>(new CDBStyleSizeExtraData);

	return sm_inst.get();
}

BOOL CDBStyleSizeExtraData::GetAllDBInfo(CADOConn *pADOConn)
{
	ASSERT(pADOConn!= NULL);
	BOOL bRet= FALSE;

	if(NULL != pADOConn)
	{
		m_nID = pADOConn->GetValueInt(DBStyleSizeExtra_key_ID);
		m_cStyleNo = pADOConn->GetValueString(DBStyleSizeExtra_key_cStyleNo);
		m_iPartID = pADOConn->GetValueInt(DBStyleSizeExtra_key_iPartID);  
      m_cMemo = pADOConn->GetValueString(DBStyleSizeExtra_key_cMemo);
      m_fCeLiangBeforeSize= pADOConn->GetValueDouble(DBStyleSizeExtra_key_fCeLiangBeforeSize);
      m_fCeLiangCusSize=  pADOConn->GetValueDouble(DBStyleSizeExtra_key_fCeLiangCusSize);
      m_fWaterBeforeSize= pADOConn->GetValueDouble(DBStyleSizeExtra_key_fWaterBeforeSize); 
      m_fWaterAfterSize=  pADOConn->GetValueDouble(DBStyleSizeExtra_key_fWaterAfterSize);
		bRet = TRUE;
	}
	return bRet;
}

BOOL CDBStyleSizeExtraData::InsertAllDBInfo(CADOConn *pADOConn)
{
	ASSERT(pADOConn!= NULL);
	BOOL bRet= FALSE;

	if (pADOConn!=NULL)
	{
		CString strSQL = GetInsertAllDBInfoSql();		
		bRet = pADOConn->ExecuteSQL(strSQL);		
	}
	return bRet;
}

CString CDBStyleSizeExtraData::GetInsertAllDBInfoSql()
{
   CString strSQL = _T("");
   strSQL.Format(_T("insert into %s(%s,%s,%s,%s,%s,%s,%s) values('%s','%d','%s','%.2f','%.2f','%.2f','%.2f')")
      ,DB_TABLE_STYLESIZEEXTRA,DBStyleSizeExtra_key_cStyleNo,DBStyleSizeExtra_key_iPartID,DBStyleSizeExtra_key_cMemo,DBStyleSizeExtra_key_fCeLiangBeforeSize
      ,DBStyleSizeExtra_key_fCeLiangCusSize,DBStyleSizeExtra_key_fWaterBeforeSize,DBStyleSizeExtra_key_fWaterAfterSize
      ,m_cStyleNo,m_iPartID,m_cMemo,m_fCeLiangBeforeSize,m_fCeLiangCusSize,m_fWaterBeforeSize,m_fWaterAfterSize);
   return strSQL;
}

BOOL CDBStyleSizeExtraData::UpdateAllDBInfoByID(CADOConn *pADOConn)
{
	ASSERT(pADOConn!= NULL);
	BOOL bRet= FALSE;

	if (pADOConn!=NULL)
	{
		CString strSQL = _T("");
		strSQL.Format(_T("update %s set %s = '%s',%s = '%d',%s = '%s',\
         %s = '%.2f',%s = '%.2f',%s = '%.2f',%s = '%.2f' where %s = %d"),DB_TABLE_STYLESIZEEXTRA
			,DBStyleSizeExtra_key_cStyleNo,m_cStyleNo
			,DBStyleSizeExtra_key_iPartID,m_iPartID
         ,DBStyleSizeExtra_key_cMemo,m_cMemo
         ,DBStyleSizeExtra_key_fCeLiangBeforeSize,m_fCeLiangBeforeSize
         ,DBStyleSizeExtra_key_fCeLiangCusSize,m_fCeLiangCusSize
         ,DBStyleSizeExtra_key_fWaterBeforeSize,m_fWaterBeforeSize
         ,DBStyleSizeExtra_key_fWaterAfterSize,m_fWaterAfterSize
			,DBStyleSizeExtra_key_ID,m_nID
			);
		bRet = pADOConn->ExecuteSQL(strSQL);		
	}
	return bRet;
}

BOOL CDBStyleSizeExtraData::DelAllDBInfoByID(CADOConn *pADOConn)
{
	ASSERT(pADOConn!= NULL);
	BOOL bRet= FALSE;

	if (NULL != pADOConn)
	{
		CString strSQL = _T("");
		strSQL.Format(_T("delete from %s where %s = %d"),DB_TABLE_STYLESIZEEXTRA,DBStyleSizeExtra_key_ID,m_nID);
		bRet = pADOConn->ExecuteSQL(strSQL);
	}

	return bRet;
}

BOOL CDBStyleSizeExtraData::DelAllDBInfoByStyleNo(CADOConn *pADOConn)
{
   ASSERT(pADOConn!= NULL);
   BOOL bRet= FALSE;

   if (NULL != pADOConn)
   {
      CString strSQL = GetDelAllDBInfoByStyleNo(m_cStyleNo);      
      bRet = pADOConn->ExecuteSQL(strSQL);
   }

   return bRet;
}

CString CDBStyleSizeExtraData::GetDelAllDBInfoByStyleNo(CString strStyleNo)
{
   CString strSQL = _T("");
   strSQL.Format(_T("delete from %s where %s = '%s'"),DB_TABLE_STYLESIZEEXTRA,DBStyleSizeExtra_key_cStyleNo,strStyleNo);

   return strSQL;
}

CDBStyleSizeExtraList::CDBStyleSizeExtraList()
{

}

CDBStyleSizeExtraList::~CDBStyleSizeExtraList()
{
	Empty();
}

CDBStyleSizeExtraData* CDBStyleSizeExtraList::GetItem(int nIndex)
{
	if (nIndex<0||nIndex>=GetCount())
		return NULL;
	return (CDBStyleSizeExtraData*)GetAt(FindIndex(nIndex));
}

void CDBStyleSizeExtraList::AddItem(CDBStyleSizeExtraData* pItem)
{
	CDBStyleSizeExtraData*pData=new CDBStyleSizeExtraData;
	pData->Copy(pItem);
	AddTail(pData);
}

void CDBStyleSizeExtraList::DeleteItem(int nIndex)
{
	if (nIndex<0||nIndex>GetCount())
		return;
	CDBStyleSizeExtraData *pObject=(CDBStyleSizeExtraData*)GetItem(nIndex);
	delete pObject;
	pObject=NULL;
	RemoveAt(FindIndex(nIndex));
}

CDBStyleSizeExtraData*CDBStyleSizeExtraList::GetItemNameByPartID(__int64 nPartID)
{
   int nIndex = 0,nCount = GetCount();
   for (nIndex = 0;nIndex < nCount;nIndex++)
   {
      auto pData = GetItem(nIndex);
      if (NULL != pData)
      {
         if (pData->m_iPartID == nPartID)
         {
           return pData;
         }
      }
   }

   return nullptr;
}

void CDBStyleSizeExtraList::GetListFromDB(CADOConn *pADOConn)
{
	ASSERT(pADOConn != NULL);
	
	Empty();
	CString strSQL = _T("");
	strSQL.Format(_T("select * from %s order by %s"),DB_TABLE_STYLESIZEEXTRA,DBStyleSizeExtra_key_iPartID);

	pADOConn->GetRecordSet(strSQL);
	while (!pADOConn->adoEOF())
	{
		CDBStyleSizeExtraData oData;
		if(oData.GetAllDBInfo(pADOConn))
		{
			AddItem(&oData);
		}
		pADOConn->MoveNext();
	}
}

void CDBStyleSizeExtraList::GetListFromDBByStyleNo(CADOConn *pADOConn,CString strStyleNo)
{
   ASSERT(pADOConn != NULL);

   Empty();
   CString strSQL = _T("");
   strSQL.Format(_T("select * from %s where %s='%s' order by %s"),
      DB_TABLE_STYLESIZEEXTRA
      ,DBStyleSizeExtra_key_cStyleNo,strStyleNo,DBStyleSizeExtra_key_iPartID);

   pADOConn->GetRecordSet(strSQL);
   while (!pADOConn->adoEOF())
   {
      CDBStyleSizeExtraData oData;
      if(oData.GetAllDBInfo(pADOConn))
      {
         AddItem(&oData);
      }
      pADOConn->MoveNext();
   }
}


CDBStyleSizeExtraList * CDBStyleSizeExtraList::Instance()
{
	if(sm_inst.get() == 0)
		sm_inst = shared_ptr<CDBStyleSizeExtraList>(new CDBStyleSizeExtraList);

	return sm_inst.get();
}


