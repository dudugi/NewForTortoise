#include "StdAfx.h"
#include "DBDataDictionary.h"
#include <algorithm>

IMPLEMENT_SERIAL(CDBDataDicData,  CDataMid, 1)
IMPLEMENT_SERIAL(CDBDataDicList,  CDataListMid, 1)

std::shared_ptr<CDBDataDicData> CDBDataDicData::sm_inst;
std::shared_ptr<CDBDataDicList> CDBDataDicList::sm_inst;

CDBDataDicData::CDBDataDicData(void)
{
	ResetData();
}


CDBDataDicData::~CDBDataDicData(void)
{
}

void CDBDataDicData::ResetData()
{
	m_nID = -1;
	m_strIndex = _T("");
	m_strItemCode = _T("");
	m_strItemName = _T("");
	m_strSysItem = _T("1");
   m_strSortCode = _T("");

	SetDataType(DAT_DATADICTIONARY);
}

void CDBDataDicData::Copy( CDBDataDicData *pData )
{
	ASSERT(pData != NULL);
	CDataMid::Copy(pData);

	m_nID = pData->m_nID;
	m_strIndex = pData->m_strIndex;
	m_strItemCode = pData->m_strItemCode;
	m_strItemName = pData->m_strItemName;
   m_strItemDescription = pData->m_strItemDescription;
   m_strItemValue = pData->m_strItemValue;
	m_strSysItem = pData->m_strSysItem;
   m_strSortCode = pData->m_strSortCode;
}

CDBDataDicData * CDBDataDicData::Instance()
{
	if(sm_inst.get() == 0)
		sm_inst = shared_ptr<CDBDataDicData>(new CDBDataDicData);

	return sm_inst.get();
}

BOOL CDBDataDicData::GetAllDBInfo( CADOConn *pADOConn )
{
	ASSERT(pADOConn != NULL);

	BOOL bRet = TRUE;

	if (NULL == pADOConn)
	{
		bRet = FALSE;
	}
	else
	{
		m_nID = pADOConn->GetValueInt(DBDataDic_key_ID);
		m_strIndex = pADOConn->GetValueString(DBDataDic_key_Index);
		m_strItemCode = pADOConn->GetValueString(DBDataDic_key_ItemCode);
		m_strItemName = pADOConn->GetValueString(DBDataDic_key_ItemName);
      m_strItemDescription = pADOConn->GetValueString(DBDataDic_key_Description);
      m_strItemValue = pADOConn->GetValueString(DBDataDic_key_Value);
		m_strSysItem =  pADOConn->GetValueString(DBDataDic_key_SysItem);
      m_strSortCode = pADOConn->GetValueString(DBDataDic_key_cSortCode);

		bRet = TRUE;
	}

	return bRet;
}
BOOL CDBDataDicData::GetAllDBInfoByItemName(CADOConn *pADOCOnn,CString strIndex, vector<CString> &vecItemName)//�����ֵ�������ȡ�����ֵ�����
{
   ASSERT(pADOCOnn != NULL);
   vecItemName.clear();
   CString strSql = _T("");
   strSql.Format(_T("select %s from %s where %s = '%s' order by %s "),
     DBDataDic_key_ItemName,
     DB_TABLE_DATADICTIONARY,
     DBDataDic_key_Index,
     strIndex,
     DBDataDic_key_Value
     );
   BOOL bRet = pADOCOnn->GetRecordSet(strSql);
   while (!pADOCOnn->adoEOF())
   {
      vecItemName.push_back(pADOCOnn->GetValueString(DBDataDic_key_ItemName));
      pADOCOnn->MoveNext();
   }
   return bRet;
}

BOOL CDBDataDicData::InsertAllDBInfoByID( CADOConn *pADOConn )
{
	ASSERT(pADOConn != NULL);

	BOOL bRet = TRUE;

	CString strSQL = _T("");
	strSQL.Format(_T("insert into %s(%s,%s,%s,%s,%s,%s,%s)\
					values('%s','%s','%s','%s','%s','%s','%s')"),DB_TABLE_DATADICTIONARY,
					DBDataDic_key_Index,DBDataDic_key_ItemCode,DBDataDic_key_ItemName,
               DBDataDic_key_Description, DBDataDic_key_Value,
               DBDataDic_key_SysItem,DBDataDic_key_cSortCode,
					m_strIndex,m_strItemCode,m_strItemName,m_strItemDescription,m_strItemValue,m_strSysItem,m_strSortCode);

	if (pADOConn->ExecuteSQL(strSQL))
	{
		//bRet = TRUE;

		//2017/05/27 zhangt Ҫ�ǻ�ȡ�����ı���m_nID
		strSQL.Format(_T("select * from %s where %s='%s' and %s='%s' "),
			DB_TABLE_DATADICTIONARY,DBDataDic_key_Index,m_strIndex,DBDataDic_key_ItemCode,m_strItemCode);
		pADOConn->GetRecordSet(strSQL);
		if (!pADOConn->adoEOF())
		{
			bRet = GetAllDBInfo(pADOConn);
		}
		else
		{
			bRet = FALSE;
		}
		//��Ҫ�ǻ�ȡ�����ı���m_nID_end
	}
	else
	{
		bRet = FALSE;
	}

	return bRet;
}

BOOL CDBDataDicData::UpdateAllDBInfoByID( CADOConn *pADOConn )
{
	ASSERT(pADOConn != NULL);

	BOOL bRet = TRUE;

	CString strSQL = _T("");
	strSQL.Format(_T("update %s set %s='%s',%s='%s',%s='%s',%s='%s',%s='%s',%s='%s',%s = '%s' where %s='%d'"),DB_TABLE_DATADICTIONARY,
		DBDataDic_key_Index,m_strIndex,
		DBDataDic_key_ItemCode,m_strItemCode,
		DBDataDic_key_ItemName,m_strItemName,
      DBDataDic_key_Description,m_strItemDescription,
      DBDataDic_key_Value,m_strItemValue,
		DBDataDic_key_SysItem,m_strSysItem,
      DBDataDic_key_cSortCode,m_strSortCode,
		DBDataDic_key_ID,m_nID);

	if (pADOConn->ExecuteSQL(strSQL))
	{
		bRet = TRUE;
	}
	else
	{
		bRet = FALSE;
	}

	return bRet;
}

BOOL CDBDataDicData::DelAllDBInfoByID( CADOConn *pADOConn )
{
	ASSERT(pADOConn != NULL);

	BOOL bRet = TRUE;

	CString strSQL = _T("");
	strSQL.Format(_T("delete from %s where %s='%d'"),DB_TABLE_DATADICTIONARY,DBDataDic_key_ID,m_nID);

	if (pADOConn->ExecuteSQL(strSQL))
	{
		bRet = TRUE;
	}
	else
	{
		bRet = FALSE;
	}

	return bRet;
}


CDBDataDicList::CDBDataDicList()
{

}

CDBDataDicList::~CDBDataDicList()
{

}

CDBDataDicData* CDBDataDicList::GetItem( int nIndex )
{
	if (nIndex<0||nIndex>=GetCount())
		return NULL;
	return (CDBDataDicData*)GetAt(FindIndex(nIndex));
}

CDBDataDicData* CDBDataDicList::GetItemByID( int nID )
{
	int nIndex = 0,nCount = GetCount();
	for (nIndex = 0;nIndex < nCount;nIndex++)
	{
		auto pItem = GetItem(nIndex);
		if (NULL != pItem)
		{
			if (pItem->m_nID == nID)
			{
				return pItem;
			}
		}
	}
	return NULL;
}

void CDBDataDicList::AddItem( CDBDataDicData* pItem )
{
	CDBDataDicData*pData = new CDBDataDicData;
	pData->Copy(pItem);
	AddTail(pData);
}

void CDBDataDicList::DeleteItem( int nIndex )
{
	if (nIndex<0||nIndex>GetCount())
		return;
	CDBDataDicData *pObject=(CDBDataDicData*)GetItem(nIndex);
	delete pObject;
	pObject=NULL;
	RemoveAt(FindIndex(nIndex));
}

void CDBDataDicList::DeleteItemByID( int nID )
{
	int nIndex = 0,nCount = GetCount();
	for (nIndex = 0;nIndex < nCount;nIndex++)
	{
		auto pItem = GetItem(nIndex);
		if (NULL != pItem)
		{
			if (pItem->m_nID == nID)
			{
				DeleteItem(nIndex);
				break;
			}
		}
	}
}

void CDBDataDicList::GetListFromDB(CADOConn *pADOConn)
{
	ASSERT(pADOConn != NULL);
	
	Empty();
	CString strSQL = _T("");
	strSQL.Format(_T("select * from %s order by %s,%s"),DB_TABLE_DATADICTIONARY,DBDataDic_key_Index,DBDataDic_key_cSortCode);
	pADOConn->GetRecordSet(strSQL);
	while (!pADOConn->adoEOF())
	{
		CDBDataDicData oData;
		if(oData.GetAllDBInfo(pADOConn))
		{
			AddItem(&oData);
		}
		pADOConn->MoveNext();
	}
}
void CDBDataDicList::GetAllDBInfoByItemName(CString strIndex, vector<CString> &vecItemName)//�����ֵ�������ȡ�����ֵ�����
{
   vecItemName.clear();
   for (int i = 0;i < GetCount();++i)
   {
      CDBDataDicData *pData = GetItem(i);
      if (pData != NULL && pData->m_strIndex == strIndex)
      {
        vecItemName.push_back(pData->m_strItemName);
      }
   }
}

CDBDataDicList * CDBDataDicList::Instance()
{
	if(sm_inst.get() == 0)
		sm_inst = shared_ptr<CDBDataDicList>(new CDBDataDicList);

	return sm_inst.get();
}

void CDBDataDicList::GetSizeSortInfo(CADOConn*pAdo,vector<CString>& vecSize)
{
   ASSERT(pAdo != NULL);
   vecSize.clear();
   CString strSql;
   strSql.Format(_T("select cTreeName from TreeClass where cTreeCate = '���³���' order by cSortCode"));
   pAdo->GetRecordSet(strSql);
   while(!pAdo->adoEOF())
   {
      CString strTreeName = pAdo->GetValueString(_T("cTreeName"));
      vecSize.push_back(strTreeName);
      pAdo->MoveNext();
   }
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CDBDicTreeItem,  CDataMid, 1)
IMPLEMENT_SERIAL(CDBDicTreeItemList,  CDataListMid, 1)

std::shared_ptr<CDBDicTreeItem> CDBDicTreeItem::sm_inst;
std::shared_ptr<CDBDicTreeItemList> CDBDicTreeItemList::sm_inst;

CDBDicTreeItem::CDBDicTreeItem()
{
   ResetData();
}

CDBDicTreeItem::~CDBDicTreeItem()
{
	//this;
}

void CDBDicTreeItem::ResetData()
{
   m_strIndex = _T("");
   m_DicList.Empty();

   CDataMid::ResetData();
}

void CDBDicTreeItem::Copy( CDBDicTreeItem *pData )
{
	ASSERT(pData!=NULL);
	m_strIndex = pData->m_strIndex;

	m_DicList.Empty();
	int nIndex = 0,nCount = pData->m_DicList.GetCount();
	for (nIndex = 0;nIndex < nCount;nIndex++)
	{
		auto pDicItem = pData->m_DicList.GetItem(nIndex);
		if (NULL != pDicItem)
		{
			m_DicList.AddItem(pDicItem);
		}
	}
}

CDBDicTreeItem * CDBDicTreeItem::Instance()
{
	if(sm_inst.get() == 0)
		sm_inst = shared_ptr<CDBDicTreeItem>(new CDBDicTreeItem);

	return sm_inst.get();
}

CDBDataDicData* CDBDicTreeItem::GetDataByName( CString strDataName )
{
	ASSERT(!strDataName.IsEmpty());
	int nIndex = 0,nCount = m_DicList.GetCount();
	for (nIndex = 0;nIndex < nCount;nIndex++)
	{
		auto pData = m_DicList.GetItem(nIndex);
		if (NULL != pData)
		{
			if (pData->m_strItemName == strDataName)
			{
				return pData;
			}
		}
	}
	return NULL;
}

CDBDataDicData* CDBDicTreeItem::GetDataByCode( CString strCode )
{
	ASSERT(!strCode.IsEmpty());
	int nIndex = 0,nCount = m_DicList.GetCount();
	for (nIndex = 0;nIndex < nCount;nIndex++)
	{
		auto pData = m_DicList.GetItem(nIndex);
		if (NULL != pData)
		{
			if (pData->m_strItemCode == strCode)
			{
				return pData;
			}
		}
	}
	return NULL;
}

int CDBDicTreeItem::GetIndexByCode( CString strCode )
{
	ASSERT(!strCode.IsEmpty());
	int nIndex = 0,nCount = m_DicList.GetCount();
	for (nIndex = 0;nIndex < nCount;nIndex++)
	{
		auto pData = m_DicList.GetItem(nIndex);
		if (NULL != pData)
		{
			if (pData->m_strItemCode == strCode)
			{
				return nIndex;
			}
		}
	}
	return -1;
}

void CDBDicTreeItem::AdjustSortCode(CADOConn * pADOConn,CDBDataDicData & oNewData,const CString & strAfterCode)
{
   /*
   û��ѡ��ڵ�  ������
   ѡ���˽ڵ㵫��ѡ��ĸ��ڵ���ѡ��Ľڵ㲻һ�� ������ (������洦����
   ѡ���˽ڵ� �� ѡ��ĸ��ڵ��뵱ǰ�ڵ�һ��

   ��ѡ��Ľڵ����»�ȡ���е������ı��� 
      �������ֵ С��99  �ڵ㷶Χ������ֵ�����һλ �����ڵ�ֵ��Ϊ��ǰֵ��һλ
      �������ֵ = 99
         ��ѡ��Ľڵ����»�ȡ���е������ı���
         ��С����ֵ ����01 �ڵ㷶Χ������ֵ��ǰ��һλ �����ڵ�ֵ ��Ϊѡ��ڵ�
         ��С����ֵ = 01 ������ݲ�������ʱ����������ȷ��
      */
   if (strAfterCode.IsEmpty())
   {
      return;
   }

   auto pInsertAfterData = GetDataByCode(strAfterCode);
   if (NULL == pInsertAfterData)
   {//�����Ҫ����Ľڵ㲻������ ��Ӧ���ش���
      ASSERT(FALSE);
      return;
   }


   std::vector<CString> vecAllCode;
   //ֻ���ͬ��������
   int nIndex = 0,nCount = m_DicList.GetCount();
   for (;nIndex < nCount;++nIndex)
   {
      auto pData = m_DicList.GetItem(nIndex);
      if (NULL != pData)
      {
         vecAllCode.push_back(pData->m_strSortCode);
      }
   }
   std::sort(vecAllCode.begin(),vecAllCode.end());//����ʽʹ���ַ����Լ�������

   CString strMinCode,strMaxCode;//��Ҫ��������С������
   CString strPrevCode = pInsertAfterData->m_strSortCode;
   if (pInsertAfterData->m_strSortCode.Right(2) == _T("99"))
   {//�����ʱ�Ѿ����������� �򲻴����������
      strMaxCode = strPrevCode;
   }
   else
   {
      for (auto it = vecAllCode.begin();it != vecAllCode.end();++it)
      {
         if (*it > strPrevCode )
         {
            if (_ttoi(*it) - _ttoi(strPrevCode) == 1)//�����ֵΪ1
            {
               if (strPrevCode == pInsertAfterData->m_strSortCode && strMinCode.IsEmpty())
               {//�����СֵΪ�� ��ǰһ�������ǲ���ı���  ���¼��Сֵ
                  strMinCode = *it;
               }
               strMaxCode = *it;
            }
            else
            {//���������һ������������  ������
               break;
            }
            strPrevCode = *it;
         }
      }
   }

   CString strSQL,strNewCode = oNewData.m_strSortCode;
   vector<CString> vec_ExecSQL;
   BOOL bIncrease = TRUE;//���ӻ���ٵı�־
   //ȡ������С�ĺ�����
   if (strMaxCode.Right(2) != _T("99"))//�������벻��99
   {
      if (!strMinCode.IsEmpty())//�����С��Ϊ�յ� ��˵����ʱֻ��Ҫ���µ�ǰ������ݼ���
      {
         //���д��ڶ�Ӧ����������ε���1
         int nMinCode = _ttoi(strMinCode.Right(2));//ȡ�����λ����
         int nMaxCode = _ttoi(strMaxCode.Right(2));
         int nCodeCount = nMaxCode - nMinCode + 1;//��Ҫ����������ܸ���
         strSQL.Format(_T("update TreeClass set cSortCode = dt_Src.cTarCode from( \
select '' + stuff(dt_result.num,1,1,'')as cTarCode,'' + stuff(dt_result.num-1,1,1,'')as cSrcCode from ( \
select top 100 num = ROW_NUMBER()over (order by getdate())+100 FROM syscolumns a,syscolumns b )dt_result  \
where dt_result.num > %d and dt_result.num < %d  )dt_Src  \
where len(cTreeCode) = %d and cTreeCate = '%s' \
and cSortCode = dt_Src.cSrcCode"),
            nMinCode + 100,
            nMaxCode + 102,
            strMinCode.GetLength(),
            oNewData.m_strIndex
            );
         vec_ExecSQL.push_back(strSQL);
      }

      CString strNewCodeValue;
      strNewCodeValue.Format(_T("%d"),_ttoi(pInsertAfterData->m_strSortCode.Right(2)) + 101);
      strNewCode.Format(_T("%s%s"),pInsertAfterData->m_strSortCode.Left(pInsertAfterData->m_strSortCode.GetLength() - 2),strNewCodeValue.Right(2));
      strSQL.Format(_T("update %s set %s = '%s' where %s = '%d'"),
         DB_TABLE_DATADICTIONARY,
         DBDataDic_key_cSortCode,strNewCode,
         DBDataDic_key_ID,oNewData.m_nID);

      vec_ExecSQL.push_back(strSQL);
   }
   else
   {//�������99 ����Ȳ���ֵС������
      bIncrease = FALSE;
      strPrevCode = pInsertAfterData->m_strSortCode;
      strMinCode = strMaxCode = _T("");
      for (auto it = vecAllCode.rbegin();it != vecAllCode.rend();++it)
      {
         if (*it <= strPrevCode )
         {
            if (_ttoi(strPrevCode) - _ttoi(*it) == 1 || (*it == pInsertAfterData->m_strSortCode))//�����ֵΪ1 ������������ѡ����һ��
            {
               if (strPrevCode == pInsertAfterData->m_strSortCode && strMaxCode.IsEmpty())
               {//�����СֵΪ�� ��ǰһ�������ǲ���ı���  ���¼��Сֵ
                  strMaxCode = *it;
               }
               strMinCode = *it;
            }
            else
            {//���������һ������������  ������
               break;
            }
            strPrevCode = *it;
         }
      }
      if (strMinCode.Right(2) != _T("01"))//�����С�벻��01
      {
         //���д��ڶ�Ӧ����������ε���1
         int nMinCode = _ttoi(strMinCode.Right(2));//ȡ�����λ����
         int nMaxCode = _ttoi(strMaxCode.Right(2));
         int nCodeCount = nMaxCode - nMinCode + 1;//��Ҫ����������ܸ���
         strSQL.Format(_T("update TreeClass set cSortCode = dt_Src.cTarCode from( \
                          select '' + stuff(dt_result.num,1,1,'')as cSrcCode,'' + stuff(dt_result.num-1,1,1,'')as cTarCode from ( \
                          select top 100 num = ROW_NUMBER()over (order by getdate())+100 FROM syscolumns a,syscolumns b )dt_result  \
                          where dt_result.num > %d and dt_result.num < %d  )dt_Src  \
                          where len(cTreeCode) = %d  and cTreeCate = '%s' \
                          and cSortCode = dt_Src.cSrcCode"),
                          nMinCode + 99, 
                          nMaxCode + 101,
                          strMinCode.GetLength(),
                          oNewData.m_strIndex
                          );
         vec_ExecSQL.push_back(strSQL);


         strSQL.Format(_T("update %s set %s = '%s' where %s = '%d'"),
            DB_TABLE_DATADICTIONARY,
            DBDataDic_key_cSortCode,pInsertAfterData->m_strSortCode,
            DBDataDic_key_ID,oNewData.m_nID);
         strNewCode = pInsertAfterData->m_strSortCode;

         vec_ExecSQL.push_back(strSQL);
      }
   }

   if(pADOConn->ExecuteSQLByTransaction(vec_ExecSQL))
   {
      //ȡ����Ҫ�����ķ�Χ
      //��С�벻�ǿյ��������ӵ�   ����  ��С����� = 01�Ҳ���������
      if ((!strMinCode.IsEmpty() && bIncrease )|| (strMinCode.Right(2) != _T("01") && !bIncrease))
      {
         int nStep = bIncrease ? 1 : -1;
         int nDicIndex = 0,nDicCount = m_DicList.GetCount();
         for (;nDicIndex < nDicCount;++nDicIndex)
         {
            auto pItem = m_DicList.GetItem(nDicIndex);
            if (NULL != pItem)
            {
               if (pItem->m_strSortCode >= strMinCode && pItem->m_strSortCode <= strMaxCode)
               {
                  CString strPrevCode = pItem->m_strSortCode.Left(pItem->m_strSortCode.GetLength() - 2);
                  CString strSort;
                  strSort.Format(_T("%d"), _ttoi(pItem->m_strSortCode.Right(2)) + nStep + 100);
                  pItem->m_strSortCode.Format(_T("%s,%s"),strPrevCode,strSort.Right(2));
               }
            }
         }
      }

      oNewData.m_strSortCode = strNewCode;
      //ִ�гɹ� ����»����е�����
      
   }
   
}

CDBDicTreeItemList::CDBDicTreeItemList()
{

}

CDBDicTreeItemList::~CDBDicTreeItemList()
{
	//Empty();
}

CDBDicTreeItem* CDBDicTreeItemList::GetItem( int nIndex )
{
	if (nIndex<0||nIndex>=GetCount())
		return NULL;
	return (CDBDicTreeItem*)GetAt(FindIndex(nIndex));
}

CDBDicTreeItem* CDBDicTreeItemList::GetItem( CString strIndex )
{
	ASSERT(!strIndex.IsEmpty());

	int nIndex = 0,nCount = GetCount();
	for (nIndex = 0;nIndex < nCount;nIndex++)
	{
		auto pData = GetItem(nIndex);
		if (NULL != pData)
		{
			if (pData->m_strIndex == strIndex)
			{
				return pData;
			}
		}
	}
	return NULL;
}

void CDBDicTreeItemList::AddItem( CDBDicTreeItem* pItem )
{
	CDBDicTreeItem*pData = new CDBDicTreeItem;
	pData->Copy(pItem);
	AddTail(pData);
}

void CDBDicTreeItemList::DeleteItem( int nIndex )
{
	if (nIndex<0||nIndex>GetCount())
		return;
	CDBDicTreeItem *pObject=(CDBDicTreeItem*)GetItem(nIndex);
	delete pObject;
	pObject=NULL;
	RemoveAt(FindIndex(nIndex));
}

void CDBDicTreeItemList::CreateTreeByDicList( CDBDataDicList * pSrcList )
{
	Empty();
	int nIndex = 0,nCount = pSrcList->GetCount();
	for (nIndex = 0;nIndex < nCount;nIndex++)
	{
		auto pData = pSrcList->GetItem(nIndex);
		if (NULL != pData)
		{
			auto pItem = GetItem(pData->m_strIndex);
			if (NULL == pItem)
			{
				CDBDicTreeItem *pNewItem = new CDBDicTreeItem;
				pNewItem->m_strIndex = pData->m_strIndex;
				pNewItem->m_DicList.AddItem(pData);
				AddTail(pNewItem);
			}
			else
			{
				pItem->m_DicList.AddItem(pData);
			}
		}
	}
}

CDBDicTreeItemList * CDBDicTreeItemList::Instance()
{
	if(sm_inst.get() == 0)
		sm_inst = shared_ptr<CDBDicTreeItemList>(new CDBDicTreeItemList);

	return sm_inst.get();
}

BOOL CDBDataDicData::InsertAllDBInfoByAutoCode(CADOConn *pADOConn)
{
   ASSERT(pADOConn != NULL);
   CString strSQL;
   strSQL.Format(_T("SET NOCOUNT ON declare @n int\
                    declare @newCode VARCHAR(50)\
                    declare @newText VARCHAR(50)\
                    declare @TREECATE VARCHAR(50)\
                    declare @MemoDetail VARCHAR(50)\
                    declare @MemoValue VARCHAR(50)\
                    \
                    SET @newText = '%s'\
                    declare @perCodeLen int\
                    SET @perCodeLen = 2\
                    declare @ParentCode VARCHAR(50)\
                    SET @ParentCode = '%s'\
                    if ((LEN(@ParentCode) %% @perCodeLen <> 0))\
                    begin\
                    select * from TreeClass where ID = 1 \
                    return\
                    end\
                    SET @TREECATE = '%s'\
                    SET @MemoDetail = '%s'\
                    SET @MemoValue = '%s'\
                    \
                    declare @CodeLen int\
                    SET @CodeLen = LEN(@ParentCode) + @perCodeLen\
                    \
                    declare @i int\
                    set @i = 1\
                    \
                    declare y_curr cursor for  \
                    SELECT convert(int,RIGHT(cTreeCode,@perCodeLen) ) as LastCode        FROM TreeClass     WHERE cTreeCate = @TREECATE and LEN(cTreeCode) = @CodeLen  AND LEFT(cTreeCode, @CodeLen - @perCodeLen) = @ParentCode order by LastCode asc\
                    open y_curr \
                    \
                    fetch next from Y_curr into @n \
                    while(@@fetch_status=0)\
                    begin\
                    \
                    if (@n > @i)\
                      break\
                    if (@n <> 0)\
                      set @i = @i + 1\
                    \
                    fetch next from y_curr into @n \
                    end\
                    \
                    close y_curr\
                    deallocate y_curr \
                    \
                    \
                    if (@i >= power(10, @perCodeLen))\
                    begin\
                      select  * from TreeClass where ID = 1 \
                      return\
                    end\
                    set @newCode = @ParentCode + RIGHT(replicate('0',@perCodeLen) + cast(@i as varchar(100)) , @perCodeLen)\
                    \
                    declare @thecount int\
                    \
                    set @thecount = (select count(0) as COUNT from TreeClass where cTreeCate = @TREECATE           \
                    and (cTreeCode = @newCode  or            \
                    (len(cTreeCode) = @CodeLen            and left(cTreeCode, @CodeLen - @perCodeLen) = @ParentCode             and cTreeName = @newText)))\
                    \
                    if (@thecount <> 0)\
                    begin\
                    \
                    select  * from TreeClass where ID = 1 \
                    \
                    end\
                    else\
                    begin\
                    insert into TreeClass\
                    (cTreeCate,cTreeCode,cTreeName,iMemo1,iMemo2,cSysItem,%s)\
                    values(@TREECATE, @newCode ,@newText,@MemoDetail,@MemoValue,'1',@newCode)\
                    if (@@ROWCOUNT = 1)\
                    select  * from TreeClass where ID = @@IDENTITY\
                    else\
                    select  * from TreeClass where ID = 1 \
                    end"), m_strItemName,
                    m_strItemCode.Left(m_strItemCode.GetLength() - 2), 
                    m_strIndex, m_strItemDescription, m_strItemValue,
                    DBDataDic_key_cSortCode
                    );

   pADOConn->GetRecordSet(strSQL);

   if (pADOConn->adoEOF())
      return FALSE;

   if (!GetAllDBInfo(pADOConn))
      return FALSE;

   if (m_nID <= 1)
      return FALSE;
   
   return TRUE;
}

