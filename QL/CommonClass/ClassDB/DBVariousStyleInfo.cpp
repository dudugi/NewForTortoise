#include "StdAfx.h"
#include "DBVariousStyleInfo.h"
#include "DBKeyDef.h"
#include "DBKeyDef_V.h"
CDBVariousStyleInfoData::CDBVariousStyleInfoData(void)
{
	ResetData();
}


CDBVariousStyleInfoData::~CDBVariousStyleInfoData(void)
{
}

void CDBVariousStyleInfoData::ResetData()
{
	m_nID				=	0;
	m_strStyleNo		=	_T("");
	m_strOrderNo		=	_T("");
	m_strDestribution	=	_T("");
	m_nPreferred		=	Ord_UnPerferred;

	m_dtOrdUpdate = COleDateTime::GetCurrentTime();

	SetDataType(DAT_VARIOUSSTYLE);
}

void CDBVariousStyleInfoData::Copy( CDBVariousStyleInfoData *pData )
{
	ASSERT(NULL != pData);

	CDataMid::Copy(pData);

	if (NULL != pData)
	{
		m_nID				=	0						;
		m_strStyleNo		=	pData->m_strStyleNo		;
		m_strOrderNo		=	pData->m_strOrderNo		;
		m_strDestribution	=	pData->m_strDestribution;
		m_nPreferred		=	pData->m_nPreferred		;
		m_dtOrdUpdate		=	pData->m_dtOrdUpdate	;
	}

}

BOOL CDBVariousStyleInfoData::GetAllDBInfo( CADOConn *pADOConn,BOOL bWithOrderInfo /*= FALSE*/ )
{
	ASSERT(NULL != pADOConn);

	BOOL bRet = TRUE;

	if (NULL == pADOConn)
	{
		bRet = FALSE;
	}
	else
	{
		m_nID				=	pADOConn->GetValueInt(DBVarious_key_ID					);
		m_strStyleNo		=	pADOConn->GetValueString(DBVarious_key_StyleNo			);
		m_strOrderNo		=	pADOConn->GetValueString(DBVarious_key_OrderNo			);
		m_strDestribution	=	pADOConn->GetValueString(DBVarious_key_Destribution		);
		m_nPreferred		=	pADOConn->GetValueInt(	DBVarious_key_Perferred			);

		bRet = TRUE;
	}

	return bRet;
}

BOOL CDBVariousStyleInfoData::InsertDBInfo( CADOConn *pADOConn )
{
	ASSERT(pADOConn != NULL);
	BOOL bRet = TRUE;
	ASSERT(!m_strStyleNo.IsEmpty());
	ASSERT(!m_strOrderNo.IsEmpty());
	if (NULL == pADOConn)
	{
		return FALSE;
	}

	if (m_strOrderNo.IsEmpty() || m_strStyleNo.IsEmpty())
	{
		return FALSE;
	}

	CString strSQL = _T(""),strFormat = _T(""),strValue = _T("");
	//                   1 ,2 ,3 ,4 
	strFormat.Format(_T("%s,%s,%s,%s"),
						DBVarious_key_StyleNo		,//1
						DBVarious_key_OrderNo		,//2
						DBVarious_key_Destribution	,//3
						DBVarious_key_Perferred		 //4
						);
	//                  1   ,2   ,3   ,4
	strValue.Format(_T("'%s','%s','%s','%d'"),
					   m_strStyleNo					,//1
					   m_strOrderNo					,//2
					   m_strDestribution			,//3
					   m_nPreferred					 //4
					   );

	if (m_nPreferred == Ord_Perferred)
	{
		//如果插入的是首选记录  则更新其它所有的数据为非首选
		strSQL.Format(_T("update %s set %s = '%d' where %s = '%s'"),DB_TABLE_VARIOUSSTYLE,DBVarious_key_Perferred,Ord_UnPerferred,DBVarious_key_StyleNo,m_strStyleNo);
		pADOConn->AppendBatchSQL(strSQL);
	}

	strSQL.Format(_T("insert into %s(%s) values(%s)"),DB_TABLE_VARIOUSSTYLE,strFormat,strValue);
	pADOConn->AppendBatchSQL(strSQL);
	bRet = pADOConn->ExecuteBatchSQL();

	return bRet;
}

BOOL CDBVariousStyleInfoData::InsertDBInfoIfNotExists(CADOConn *pADOConn)
{
	ASSERT(pADOConn != NULL);
	BOOL bRet = TRUE;
	ASSERT(!m_strStyleNo.IsEmpty());
	ASSERT(!m_strOrderNo.IsEmpty());
	if (NULL == pADOConn)
	{
		return FALSE;
	}

	if (m_strOrderNo.IsEmpty() || m_strStyleNo.IsEmpty())
	{
		return FALSE;
	}

	CString strSQL = _T(""),strFormat = _T(""),strValue = _T("");
	//                   1 ,2 ,3 ,4 
	strFormat.Format(_T("%s,%s,%s,%s"),
		DBVarious_key_StyleNo		,//1
		DBVarious_key_OrderNo		,//2
		DBVarious_key_Destribution	,//3
		DBVarious_key_Perferred		 //4
		);
	//                  1   ,2   ,3   ,4
	strValue.Format(_T("'%s','%s','%s','%d'"),
		m_strStyleNo					,//1
		m_strOrderNo					,//2
		m_strDestribution			,//3
		m_nPreferred					 //4
		);

	if (m_nPreferred == Ord_Perferred)
	{
		//如果插入的是首选记录  则更新其它所有的数据为非首选
		strSQL.Format(_T("update %s set %s = '%d' where %s = '%s'"),DB_TABLE_VARIOUSSTYLE,DBVarious_key_Perferred,Ord_UnPerferred,DBVarious_key_StyleNo,m_strStyleNo);

		pADOConn->AppendBatchSQL(strSQL);
	}

	strSQL.Format(_T("if not exists(select * from %s where %s = '%s' and %s = '%s')\
						insert into %s(%s) values(%s)\
					 else\
						update %s set %s = '%d' \
						where %s = '%s' and %s = '%s'")
					 ,DB_TABLE_VARIOUSSTYLE,DBVarious_key_StyleNo,m_strStyleNo,DBVarious_key_OrderNo,m_strOrderNo
					 ,DB_TABLE_VARIOUSSTYLE,strFormat,strValue
					 ,DB_TABLE_VARIOUSSTYLE,DBVarious_key_Perferred,m_nPreferred
					 ,DBVarious_key_StyleNo,m_strStyleNo,DBVarious_key_OrderNo,m_strOrderNo);

	pADOConn->AppendBatchSQL(strSQL);
	bRet = pADOConn->ExecuteBatchSQL();


	return bRet;
}

BOOL CDBVariousStyleInfoData::UpdateDestribution( CADOConn *pADOConn )
{
	BOOL bRet = FALSE;
	ASSERT(pADOConn != NULL);
	if(NULL == pADOConn)
	{
		return FALSE;
	}

	CString strSQL = _T("");
	strSQL.Format(_T("update %s set %s = '%s' where %s = '%s' and %s = '%s'")
		,DB_TABLE_VARIOUSSTYLE
		,DBVarious_key_Destribution,m_strDestribution
		,DBVarious_key_StyleNo,m_strStyleNo
		,DBVarious_key_OrderNo,m_strOrderNo
		);

	bRet = pADOConn->ExecuteSQL(strSQL);

	return bRet;
}

BOOL CDBVariousStyleInfoData::SetPreferred( CADOConn *pADOConn )
{
	ASSERT(pADOConn != NULL);
	BOOL bRet = TRUE;

	ASSERT(!m_strStyleNo.IsEmpty());
	ASSERT(!m_strOrderNo.IsEmpty());
	if (m_strOrderNo.IsEmpty() || m_strStyleNo.IsEmpty())
	{
		return FALSE;
	}

	if (NULL == pADOConn)
	{
		return FALSE;
	}
	CString strSQL = _T("");

	strSQL.Format(_T("update %s set %s = '%d' where %s = '%s'"),DB_TABLE_VARIOUSSTYLE
		,DBVarious_key_Perferred,Ord_UnPerferred
		,DBVarious_key_StyleNo,m_strStyleNo
		);

	pADOConn->AppendBatchSQL(strSQL);

	strSQL.Format(_T("update %s set %s = '%d' where %s = '%s' and %s = '%s'"),DB_TABLE_VARIOUSSTYLE
		,DBVarious_key_Perferred,Ord_Perferred
		,DBVarious_key_StyleNo,m_strStyleNo
		,DBVarious_key_OrderNo,m_strOrderNo
		);
	
	pADOConn->AppendBatchSQL(strSQL);
	bRet = pADOConn->ExecuteBatchSQL();

	return bRet;
}

BOOL CDBVariousStyleInfoData::DelDBInfoByStyleAndOrder( CADOConn *pADOConn )
{
	BOOL bRet = FALSE;
	ASSERT(NULL != pADOConn);
	if (NULL == pADOConn)
	{
		return FALSE;
	}

	ASSERT(!m_strStyleNo.IsEmpty());
	ASSERT(!m_strOrderNo.IsEmpty());
	if (m_strOrderNo.IsEmpty() || m_strStyleNo.IsEmpty())
	{
		return FALSE;
	}

	CString strSQL = _T("");
	strSQL.Format(_T("delete from %s where %s = '%s' and %s = '%s'"),DB_TABLE_VARIOUSSTYLE
		,DBVarious_key_StyleNo,m_strStyleNo
		,DBVarious_key_OrderNo,m_strOrderNo
		);

	bRet = pADOConn->ExecuteSQL(strSQL);
	return bRet;
}

CString CDBVariousStyleInfoData::GetPreferredOrderNoByStyleNo(CADOConn *pADOConn)
{
	return GetPreferredOrderNoByStyleNo(pADOConn,m_strStyleNo);
}

CString CDBVariousStyleInfoData::GetPreferredOrderNoByStyleNo(CADOConn *pADOConn,CString strStyleNo)
{
	CString strPreferredOrderNo = _T("");
	ASSERT(NULL != pADOConn);
	ASSERT(!strStyleNo.IsEmpty());
	if (pADOConn && (!strStyleNo.IsEmpty()))
	{
		CString strSQL = _T("");
		//strSQL.Format(_T("select top 1 * from %s where %s = '%s' and %s = '%d'"),DB_TABLE_VARIOUSSTYLE,DBVarious_key_StyleNo,strStyleNo,DBVarious_key_Perferred,CDBVariousStyleInfoData::Ord_Perferred);
		strSQL.Format(_T("select * from %s where %s = '%s' and %s = '%d'"),DB_TABLE_VARIOUSSTYLE,DBVarious_key_StyleNo,strStyleNo,DBVarious_key_Perferred,CDBVariousStyleInfoData::Ord_Perferred);
		pADOConn->GetRecordSet(strSQL);
		if (!pADOConn->adoEOF())
		{
			strPreferredOrderNo = pADOConn->GetValueString(DBVarious_key_OrderNo);
		}
	}

	return strPreferredOrderNo;
}

CDBVariousStyleInfoList::CDBVariousStyleInfoList()
{

}

CDBVariousStyleInfoList::~CDBVariousStyleInfoList()
{

}

CDBVariousStyleInfoData* CDBVariousStyleInfoList::GetItem( int nIndex )
{
	if (nIndex<0||nIndex>=GetCount())
		return NULL;
	return (CDBVariousStyleInfoData*)GetAt(FindIndex(nIndex));
}

CDBVariousStyleInfoData* CDBVariousStyleInfoList::GetPerferredItem()
{
	CDBVariousStyleInfoData * pItem = NULL;
	
	for(int i=0;i< GetCount();i++)
	{
		CDBVariousStyleInfoData * pObject = GetItem(i);
		if(CDBVariousStyleInfoData::Ord_Perferred == pObject->m_nPreferred)
		{
			pItem = pObject;
			break;
		}
	}

	return pItem;
}

CDBVariousStyleInfoData* CDBVariousStyleInfoList::GetItemByOrderNo( CString strOrderNo )
{
	ASSERT(!strOrderNo.IsEmpty());
	if (strOrderNo.IsEmpty())
	{
		return NULL;
	}
	CDBVariousStyleInfoData * pItem = NULL;

	for(int i=0;i< GetCount();i++)
	{
		CDBVariousStyleInfoData * pObject = GetItem(i);
		if(strOrderNo == pObject->m_strOrderNo)
		{
			pItem = pObject;
			break;
		}
	}

	return pItem;
}

BOOL CDBVariousStyleInfoList::SetPerferredItem( CADOConn *pADOConn,CString strOrderNo )
{
	ASSERT(NULL != pADOConn);
	BOOL bRet = FALSE;
	if(NULL == pADOConn)
	{
		return bRet;
	}
	
	auto pPerferredItem = GetPerferredItem();
	if (NULL != pPerferredItem && pPerferredItem->m_strOrderNo == strOrderNo)
	{
		return TRUE;
	}

	auto pItem = GetItemByOrderNo(strOrderNo);
	if (NULL != pItem)
	{
		if(pItem->SetPreferred(pADOConn))
		{
			if (NULL != pPerferredItem)
			{
				pPerferredItem->m_nPreferred = CDBVariousStyleInfoData::Ord_UnPerferred;
			}
			pItem->m_nPreferred = CDBVariousStyleInfoData::Ord_Perferred;
			bRet = TRUE;
		}
	}
	return bRet;
}

void CDBVariousStyleInfoList::AddItem( CDBVariousStyleInfoData* pItem )
{
	ASSERT(NULL != pItem);
	CDBVariousStyleInfoData*pData=new CDBVariousStyleInfoData;
	pData->Copy(pItem);
	AddTail(pData);
}

void CDBVariousStyleInfoList::DeleteItem( int nIndex )
{
	if (nIndex<0||nIndex>GetCount())
		return;
	CDBVariousStyleInfoData *pObject=(CDBVariousStyleInfoData*)GetItem(nIndex);
	delete pObject;
	pObject=NULL;
	RemoveAt(FindIndex(nIndex));
}

void CDBVariousStyleInfoList::DeleteItemByOrderNo( CString strOrderNo )
{
	ASSERT(!strOrderNo.IsEmpty());
	if (strOrderNo.IsEmpty())
	{
		return;
	}

	for(int i=0;i< GetCount();i++)
	{
		CDBVariousStyleInfoData * pObject = GetItem(i);
		if(strOrderNo == pObject->m_strOrderNo)
		{
			delete pObject;
			pObject=NULL;
			RemoveAt(FindIndex(i));
			break;
		}
	}
}

void CDBVariousStyleInfoList::GetListFromDB( CADOConn * pADOConn,CString strStyleNo )
{
	ASSERT(pADOConn != NULL);
	ASSERT(!strStyleNo.IsEmpty());
	Empty();//清空操作
	if (NULL == pADOConn)
	{
		return;
	}
	else
	{
		CString strSQL = _T("");
      //因为订单表中的最后操作时间已经被移除掉了....  所以这里用当前时间代替更新时间   wangzl 2018-10-22
		strSQL.Format(_T("select a.* from %s a  where a.%s = '%s'"),
         DB_TABLE_VARIOUSSTYLE
			,DBVarious_key_StyleNo,strStyleNo);

		if (pADOConn->GetRecordSet(strSQL))
		{
			while (!pADOConn->adoEOF())
			{
				CDBVariousStyleInfoData *pData = new CDBVariousStyleInfoData;
				if(pData->GetAllDBInfo(pADOConn,TRUE))
				{
					AddHead(pData);
				}
				else
				{
					delete pData;
				}

				pADOConn->MoveNext();
			}
		}
	}
}
