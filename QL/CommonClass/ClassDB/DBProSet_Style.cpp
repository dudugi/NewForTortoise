#include "StdAfx.h"
#include "DBProSet_Style.h"
#include "DBKeyDef.h"

IMPLEMENT_SERIAL(CDBProSet_StyleData,  CDataMid, 1)
IMPLEMENT_SERIAL(CDBProSet_StyleList,  CDataListMid, 1)
CDBProSet_StyleData::CDBProSet_StyleData(void)
{
	ResetData();
}


CDBProSet_StyleData::~CDBProSet_StyleData(void)
{
}

void CDBProSet_StyleData::ResetData()
{
	m_nID			=	0;
	m_strStyleNo	=	_T("");
	m_strProName	=	_T("");
	m_strUserID		=	_T("");
	m_dwProTime		=	0;
   m_strfPrice = _T("0");
   m_strcIntro = _T("");
   m_strMark = _T("");
   m_strGXMark = _T("1");
   m_nIsGroup = en_Person;
	SetDataType(DAT_PROSET_STYLE);
}

void CDBProSet_StyleData::Copy(CDBProSet_StyleData *pData)
{
	ASSERT(NULL != pData);
	CDataMid::Copy(pData);
	m_nID			=		pData->m_nID		;
	m_strStyleNo	=		pData->m_strStyleNo	;
	m_strProName	=		pData->m_strProName	;
	m_strUserID		=		pData->m_strUserID	;
	m_dwProTime		=		pData->m_dwProTime	;
   m_strfPrice =		pData->m_strfPrice;      //工序工价 yangjr 2018/5/3
   m_strcIntro =		pData->m_strcIntro;      //说明 yangjr 2018/5/3
   m_strMark   =     pData->m_strMark;
   m_nIsGroup  =     pData->m_nIsGroup;
   m_strGXMark = pData->m_strGXMark;
}

BOOL CDBProSet_StyleData::GetAllDBInfo(CADOConn *pADOConn)
{
	ASSERT(pADOConn != NULL);

	BOOL bRet = TRUE;

	if (NULL == pADOConn)
	{
		bRet = FALSE;
	}
	else
	{
		m_nID			=	pADOConn->GetValueInt	(DBProSet_Style_key_ID		);
		m_strStyleNo	=	pADOConn->GetValueString(DBProSet_Style_key_StyleNo	);
		m_strProName	=	pADOConn->GetValueString(DBProSet_Style_key_ProName	);
		m_strUserID		=	pADOConn->GetValueString(DBProSet_Style_key_UserID	);
		m_dwProTime		=	pADOConn->GetValueInt64(DBProSet_Style_key_ProTime	);
      m_strfPrice		=	pADOConn->GetValueDoubleStr(DBProSet_Style_key_fPrice,2	);
      m_strcIntro		=	pADOConn->GetValueString(DBProSet_Style_key_cIntro	);
      m_strMark      = pADOConn->GetValueString(DBProSet_Style_key_cMark);
      m_strGXMark = pADOConn->GetValueString(DBProSet_Style_key_cGXMark);
      m_nIsGroup = pADOConn->GetValueInt(DBProSet_Style_key_bIsGroup);
		bRet = TRUE;
	}

	return bRet;
}

BOOL CDBProSet_StyleData::InsertAllDBInfo(CADOConn *pADOConn)
{
	ASSERT(pADOConn != NULL);
	m_strStyleNo.Trim();
	m_strProName.Trim();
	m_strUserID.Trim();
	ASSERT(!m_strStyleNo.IsEmpty());
	ASSERT(!m_strProName.IsEmpty());
	ASSERT(!m_strUserID.IsEmpty());
	BOOL bRet = TRUE;

	if (NULL == pADOConn)
	{
		bRet = FALSE;
	}
	else
	{

		CString strSQL = _T(""),strFormat = _T(""),strValue = _T("");
		//					 1 ,2 ,3 ,4 
		strFormat.Format(_T("%s,%s,%s,%s,%s,%s,%s,%s,%s"),
			DBProSet_Style_key_StyleNo	,//1
			DBProSet_Style_key_ProName	,//2
			DBProSet_Style_key_UserID	,//3
			DBProSet_Style_key_ProTime	 //7
         ,DBProSet_Style_key_fPrice
         ,DBProSet_Style_key_cIntro
         ,DBProSet_Style_key_cMark
         ,DBProSet_Style_key_cGXMark
         ,DBProSet_Style_key_bIsGroup
			);
		//					1   , 2  ,3     ,4
		strValue.Format(_T("'%s','%s','%s','%ld','%s','%s','%s','%s','%d'"),
			m_strStyleNo	,//1
			m_strProName	,//2
			m_strUserID		,//3
			m_dwProTime		 //4
         ,m_strfPrice
         ,m_strcIntro
         ,m_strMark
         ,m_strGXMark
         ,m_nIsGroup
			);

		strSQL.Format(_T("insert into %s(%s) values(%s)"),DB_TABLE_PROSET_STYLE,strFormat,strValue);

		bRet = pADOConn->ExecuteSQL(strSQL);

		bRet = TRUE;
	}

	return bRet;
}

BOOL CDBProSet_StyleData::UpdateAllDBInfoByID(CADOConn *pADOConn)
{
	ASSERT(pADOConn != NULL);
	m_strStyleNo.Trim();
	m_strProName.Trim();
	m_strUserID.Trim();
	ASSERT(!m_strStyleNo.IsEmpty());
	ASSERT(!m_strProName.IsEmpty());
	ASSERT(!m_strUserID.IsEmpty());
	BOOL bRet = TRUE;

	if (NULL == pADOConn)
	{
		bRet = FALSE;
	}
	else
	{
		CString strSQL = _T("");
		//								1		  2			3			4				5
		strSQL.Format(_T("update %s set %s = '%s',%s = '%s',%s = '%s',  %s = '%ld',%s = '%s',%s = '%s',%s = '%s' ,%s = '%s',%s='%d' where %s = '%d'"),
			DB_TABLE_PROSET_STYLE,
			DBProSet_Style_key_StyleNo		,m_strStyleNo,
			DBProSet_Style_key_ProName		,m_strProName,
			DBProSet_Style_key_UserID		,m_strUserID,
			DBProSet_Style_key_ProTime		,m_dwProTime,
         DBProSet_Style_key_fPrice		,m_strfPrice,
         DBProSet_Style_key_cIntro		,m_strcIntro,
         DBProSet_Style_key_cMark      ,m_strMark,
         DBProSet_Style_key_cGXMark    ,m_strGXMark,
         DBProSet_Style_key_bIsGroup   ,m_nIsGroup,
			DBProSet_Style_key_ID			,m_nID
			);

		bRet = pADOConn->ExecuteSQL(strSQL);
		bRet = TRUE;
	}

	return bRet;
}

BOOL CDBProSet_StyleData::DelAllDBInfoByID(CADOConn *pADOConn)
{
	ASSERT(pADOConn != NULL);
	ASSERT(0 != m_nID);
	BOOL bRet = TRUE;

	if (NULL == pADOConn)
	{
		bRet = FALSE;
	}
	else
	{
		CString strSQL = _T("");
		strSQL.Format(_T("delete from %s where %s = '%d'"),DB_TABLE_PROSET_STYLE,DBProSet_Style_key_ID,m_nID);

		bRet = pADOConn->ExecuteSQL(strSQL);
	}

	return bRet;
}

BOOL CDBProSet_StyleData::ClearAllStyleInfo(CADOConn *pADOConn)
{
	ASSERT(pADOConn != NULL);
	m_strStyleNo.Trim();
	ASSERT(!m_strStyleNo.IsEmpty());
	BOOL bRet = TRUE;

	if (NULL == pADOConn)
	{
		bRet = FALSE;
	}
	else
	{
		CString strSQL = _T("");
		strSQL.Format(_T("delete from %s where %s = '%s'"),DB_TABLE_PROSET_STYLE,DBProSet_Style_key_StyleNo,m_strStyleNo);

		bRet = pADOConn->ExecuteSQL(strSQL);
		bRet = TRUE;
	}

	return bRet;
}

CString CDBProSet_StyleData::GetGongJiaByStyleNoAndProName(CADOConn *pADOConn,CString strStyleNo,CString strProName)
{
   ASSERT(NULL != pADOConn);
   ASSERT(!strStyleNo.IsEmpty());
   ASSERT(!strProName.IsEmpty());

   CString strSQL = _T("");
   strSQL.Format(_T("select %s from %s where %s = '%s' and %s = '%s'"),
      DBProSet_Style_key_fPrice,
      DB_TABLE_PROSET_STYLE,
      DBProSet_Style_key_StyleNo,strStyleNo,
      DBProSet_Style_key_ProName,strProName
      );

   pADOConn->GetRecordSet(strSQL);
   CString strGongJia = _T("0.00");
   if (!pADOConn->adoEOF())
   {
      strGongJia = pADOConn->GetValueDoubleStr(DBProSet_Style_key_fPrice,2);
   }
   return strGongJia;
}

CString CDBProSet_StyleData::GetInsertStr()
{
	CString strSQL = _T("");

	m_strStyleNo.Trim();
	m_strUserID.Trim();
	m_strProName.Trim();
	ASSERT(!m_strStyleNo.IsEmpty());
	//ASSERT(!m_strUserID.IsEmpty());
	ASSERT(!m_strProName.IsEmpty());
	strSQL.Format(_T("insert into %s(%s,%s,%s,%s,%s,%s,%s,%s,%s) \
					 values('%s','%s','%s','%ld','%s','%s','%s','%s','%d')"),
					 DB_TABLE_PROSET_STYLE,
					 DBProSet_Style_key_StyleNo, DBProSet_Style_key_ProName,DBProSet_Style_key_UserID,DBProSet_Style_key_ProTime,DBProSet_Style_key_fPrice,DBProSet_Style_key_cIntro,DBProSet_Style_key_cMark, DBProSet_Style_key_cGXMark,DBProSet_Style_key_bIsGroup
					 ,m_strStyleNo,m_strProName,m_strUserID,m_dwProTime,m_strfPrice,m_strcIntro,m_strMark,m_strGXMark,m_nIsGroup);

	return strSQL;
}

CString CDBProSet_StyleData::GetUpdateStr(CString fieldStr,CString valueStr)
{
   CString strSQL = _T("");

   m_strStyleNo.Trim();
   m_strUserID.Trim();
   m_strProName.Trim();
   ASSERT(!m_strStyleNo.IsEmpty());
   //ASSERT(!m_strUserID.IsEmpty());
   ASSERT(!m_strProName.IsEmpty());
   strSQL.Format(_T("update %s set %s='%s' where %s='%s' and %s='%s'"),
                    DB_TABLE_PROSET_STYLE,fieldStr,valueStr                
                    ,DBProSet_Style_key_StyleNo,m_strStyleNo,DBProSet_Style_key_ProName,m_strProName);

   return strSQL;
}

CString CDBProSet_StyleData::GetUpdateStr2()
{
   CString strSQL = _T("");
   strSQL.Format(_T("update  %s set %s='%s',%s='%s' where %s=%d;"),DB_TABLE_PROSET_STYLE,
      DBProSet_Style_key_fPrice		,m_strfPrice,
      DBProSet_Style_key_cMark      ,m_strMark,
      DBProSet_Style_key_ID			,m_nID);
   return strSQL;
}
CString CDBProSet_StyleData::GetDeleteByStyleNoSql(CString strStyleNo)
{
   CString strSQL = _T("");
   strSQL.Format(_T("delete from %s where %s='%s';"),DB_TABLE_PROSET_STYLE,     
      DBProSet_Style_key_StyleNo,strStyleNo);
   return strSQL;
}
CDBProSet_StyleList::CDBProSet_StyleList()
{

}

CDBProSet_StyleList::~CDBProSet_StyleList()
{

}

void CDBProSet_StyleList::Copy(CDBProSet_StyleList *pList)
{
   if (pList != NULL)
   {
      for (int nIndex = 0;nIndex < pList->GetCount();nIndex++)
      {
         CDBProSet_StyleData *pData =(CDBProSet_StyleData *)pList->GetAt(pList->FindIndex(nIndex));
         if (pData != NULL)
         {
            AddItem(pData);
         }
      }
   }
}

CDBProSet_StyleData* CDBProSet_StyleList::GetItem(int nIndex)
{
	if (nIndex<0||nIndex>=GetCount())
		return NULL;
	return (CDBProSet_StyleData*)GetAt(FindIndex(nIndex));
}

CDBProSet_StyleData* CDBProSet_StyleList::GetItemByName(CString strProName)
{
	int nIndex = 0,nCount = GetCount();
	for (nIndex = 0;nIndex < nCount;nIndex++)
	{
		auto pData = GetItem(nIndex);
		if (NULL != pData)
		{
			if (0 == strProName.CompareNoCase(pData->m_strProName))
			{
				return pData;
			}
		}
	}
	return NULL;
}

void CDBProSet_StyleList::AddItem(CDBProSet_StyleData* pItem)
{
	CDBProSet_StyleData*pData=new CDBProSet_StyleData;
	pData->Copy(pItem);
	AddTail(pData);
}

void CDBProSet_StyleList::AddItem_Before(int position, CDBProSet_StyleData* pItem)
{
   CDBProSet_StyleData*pData=new CDBProSet_StyleData;
   pData->Copy(pItem);
   InsertBefore(FindIndex(position),pData);
}

void CDBProSet_StyleList::AddItem_After(int position, CDBProSet_StyleData* pItem)
{
   CDBProSet_StyleData*pData=new CDBProSet_StyleData;
   pData->Copy(pItem);
   InsertAfter(FindIndex(position),pItem);
}

void CDBProSet_StyleList::DeleteItem(int nIndex)
{
	if (nIndex<0||nIndex>GetCount())
		return;
	CDBProSet_StyleData *pObject=(CDBProSet_StyleData*)GetItem(nIndex);
	delete pObject;
	pObject=NULL;
	RemoveAt(FindIndex(nIndex));
}

BOOL CDBProSet_StyleList::InsertAllDBInfo(CADOConn * pADOConn,CString strStyleNo)
{
	ASSERT(pADOConn != NULL);

	BOOL bRet = FALSE;
	CString strSQL = _T(""),strSQLTmp = _T("");

	int nIndex = 0,nCount = GetCount();
	for (nIndex = 0;nIndex < nCount;nIndex++)
	{
		auto pData = GetItem(nIndex);
		if (NULL != pData)
		{
			pData->m_strStyleNo = strStyleNo;
			strSQLTmp = pData->GetInsertStr();
			if (!strSQL.IsEmpty())
			{
				strSQL += _T("\n");
			}
			strSQL += strSQLTmp;
		}
	}

	if (!strSQL.IsEmpty())
	{
		bRet = pADOConn->ExecuteSQL(strSQL);
	}
	return bRet;
}

BOOL CDBProSet_StyleList::UpdateZhiPaiPerson(CADOConn * pADOConn,CString strStyleNo)
{
   ASSERT(pADOConn != NULL);

   BOOL bRet = FALSE;
   CString strSQL = _T(""),strSQLTmp = _T("");

   int nIndex = 0,nCount = GetCount();
   for (nIndex = 0;nIndex < nCount;nIndex++)
   {
      auto pData = GetItem(nIndex);
      if (NULL != pData)
      {
         pData->m_strStyleNo = strStyleNo;
         strSQLTmp = pData->GetUpdateStr(DBProSet_Style_key_UserID ,pData->m_strUserID );
         if (!strSQL.IsEmpty())
         {
            strSQL += _T("\n");
         }
         strSQL += strSQLTmp;
      }
   }

   if (!strSQL.IsEmpty())
   {
      bRet = pADOConn->ExecuteSQL(strSQL);
   }
   return bRet;
}

BOOL CDBProSet_StyleList::UpdateMemo(CADOConn * pADOConn,CString strStyleNo)
{
   ASSERT(pADOConn != NULL);

   BOOL bRet = FALSE;
   CString strSQL = _T(""),strSQLTmp = _T("");

   int nIndex = 0,nCount = GetCount();
   for (nIndex = 0;nIndex < nCount;nIndex++)
   {
      auto pData = GetItem(nIndex);
      if (NULL != pData)
      {
         pData->m_strStyleNo = strStyleNo;
         strSQLTmp = pData->GetUpdateStr(DBProSet_Style_key_cIntro ,pData->m_strcIntro);
         if (!strSQL.IsEmpty())
         {
            strSQL += _T("\n");
         }
         strSQL += strSQLTmp;
      }
   }

   if (!strSQL.IsEmpty())
   {
      bRet = pADOConn->ExecuteSQL(strSQL);
   }
   return bRet;
}

//根据款式号获取对应工序 yangjr 2018/5/4
BOOL CDBProSet_StyleList::GetProSetStyleData(CADOConn * pADOConn,CString strStyleNo)
{
   Empty();
   ASSERT(pADOConn != NULL); 
   CString strSQL = _T("");
   strSQL.Format(_T("select a.* from ProSet_Style as a\
                    left join Gongxu as b on a.cProName = b.cGXName\
                    where cStyleNo = '%s' order by b.iSortID"),strStyleNo);
   pADOConn->GetRecordSet(strSQL);   

   while (!pADOConn->adoEOF())
   {
      CDBProSet_StyleData oneData;
      oneData.GetAllDBInfo(pADOConn);
      AddItem(&oneData);
      pADOConn->MoveNext();
   }

   return TRUE;
}

CString CDBProSet_StyleList::GetGongJiaByStyleNoAndProName(CADOConn *pADOConn,CString strStyleNo,CString strProName)
{
   ASSERT(NULL != pADOConn);
   ASSERT(!strStyleNo.IsEmpty());
   ASSERT(!strProName.IsEmpty());

   CString strSQL = _T("");
   strSQL.Format(_T("select %s from %s where %s = '%s' and %s = '%s'"),
      DBProSet_Style_key_fPrice,
      DB_TABLE_PROSET_STYLE,
      DBProSet_Style_key_StyleNo,strStyleNo,
      DBProSet_Style_key_ProName,strProName
      );

   pADOConn->GetRecordSet(strSQL);
   CString strGongJia = _T("0.00");
   if (!pADOConn->adoEOF())
   {
      strGongJia = pADOConn->GetValueDoubleStr(DBProSet_Style_key_fPrice,2);
   }
   return strGongJia;
}

//根据款式号获取所有的工序价格 yangjr 2018-1-17
BOOL CDBProSet_StyleList::GetGongJiaMapByStyle(CADOConn *pADOConn,CString strStyleNo,std::map<CString,double> &mapData)
{
   ASSERT(NULL != pADOConn);
   ASSERT(!strStyleNo.IsEmpty());

   CString strSQL = _T("");
   strSQL.Format(_T("select %s,%s from %s where %s = '%s'"),
      DBProSet_Style_key_ProName,
      DBProSet_Style_key_fPrice,
      DB_TABLE_PROSET_STYLE,
      DBProSet_Style_key_StyleNo,strStyleNo
      );

   pADOConn->GetRecordSet(strSQL); 
   while (!pADOConn->adoEOF())
   { 
      mapData.insert(make_pair(pADOConn->GetValueString(DBProSet_Style_key_ProName),pADOConn->GetValueDouble(DBProSet_Style_key_fPrice)));
      pADOConn->MoveNext();
   }
   return TRUE;
}

CString CDBProSet_StyleList::GetStyleInfo(__in CADOConn * pADOConn,__in CString strStyleNo,__in vector<CString> vecGX/*=vector<CString>()*/,BOOL bWithProName /*= TRUE*/)
{
   ASSERT(NULL != pADOConn);
   ASSERT(!strStyleNo.IsEmpty());
   CString strRetValue = _T("");
   CString strSQL = _T("");

   if (vecGX.size() <= 0)     //全部工序
   {
      strSQL.Format(_T("select cProName,cIntro from ProSet_Style where cStyleNo = '%s' and cIntro <> ''"),strStyleNo);
   }
   else
   {
      CString strFilter = _T("");
      for (int i=0; i<(int)vecGX.size(); ++i)
      {
         if (i == 0)
         {
            strFilter.Format(_T("cProName = '%s' "),vecGX[i]);
         }
         else
         {
            strFilter.Format(_T("or cProName = '%s' "),vecGX[i]);
         }
      }
      strSQL.Format(_T("select cProName,cIntro from ProSet_Style where cStyleNo = '%s' and cIntro <> '' and (%s)"),strStyleNo,strFilter);
   }
   pADOConn->GetRecordSet(strSQL);
   while(!pADOConn->adoEOF())
   {
      CString cProName = pADOConn->GetValueString(_T("cProName"));
      CString cIntro = pADOConn->GetValueString(_T("cIntro"));

      if (bWithProName)
      {
         strRetValue+= cProName + _T(":") + cIntro + _T("\r\n");
      }
      else
         strRetValue = cIntro ;

      pADOConn->MoveNext();
   }
   return strRetValue;
}



CString my_proset_style_info::GetInsertSql()
{
   CString strSQL = _T(""),strFormat = _T(""),strValue = _T("");

   strFormat.Format(_T("%s,%s,%s,%s,%s,%s"),
      DBProSet_Style_key_StyleNo	,
      DBProSet_Style_key_ProName	,
      DBProSet_Style_key_UserID	,
      DBProSet_Style_key_ProTime	, 
      DBProSet_Style_key_fPrice,
      DBProSet_Style_key_cIntro);

   strValue.Format(_T("'%s','%s','%s',ld,'%s','%s'"),
      m_strStyleNo,
      m_strProName,
      m_strUserID,
      0,	
      m_strfPrice,
      _T(""));

   strSQL.Format(_T("insert into %s(%s) values(%s)"),DB_TABLE_PROSET_STYLE,strFormat,strValue);
   return strSQL;
};

CString my_proset_style_info::GetUpdateSql(BOOL bIgnoreNull /*= TRUE*/)
{
   CString strSql = _T(""),strText = _T("");

   if (!m_strUserID.IsEmpty() || !bIgnoreNull)
   {
      strText.Format(_T("%s = '%s',"),DBProSet_Style_key_UserID,m_strUserID);
      strSql += strText;
   }
   if (!m_strfPrice.IsEmpty() || !bIgnoreNull)
   {
      strText.Format(_T("%s = '%s',"),DBProSet_Style_key_fPrice,m_strfPrice);
      strSql += strText;
   }
   if (!m_strMark.IsEmpty() || !bIgnoreNull)
   {
	   strText.Format(_T("%s = '%s',"),DBProSet_Style_key_cMark,m_strMark);
	   strSql += strText;
   }

   if (!strSql.IsEmpty())
   {
      strSql = strSql.Left(strSql.GetLength() - 1);// 取掉最后一个,
      CString strRetSql;  
      strRetSql.Format(_T("update %s set %s where %s = '%s' and %s = '%s'"),DB_TABLE_PROSET_STYLE,strSql,
         DBProSet_Style_key_StyleNo,m_strStyleNo,
         DBProSet_Style_key_ProName,m_strProName);
      return strRetSql;
   }
   return _T("");
};