#include "StdAfx.h"
#include "DBClientInfo.h"
#include "DBKeyDef.h"



const CString CS_DIFF_OUTTIME = _T("OUTTIME");

///////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CDBClientVarifyInfo,  CDataMid, 1)
IMPLEMENT_SERIAL(CDBClientVarifyInfoList,  CDataListMid, 1)

std::shared_ptr<CDBClientVarifyInfo> CDBClientVarifyInfo::sm_inst;
std::shared_ptr<CDBClientVarifyInfoList> CDBClientVarifyInfoList::sm_inst;

CDBClientVarifyInfo::CDBClientVarifyInfo()
{
	ResetData(); 
} 

CDBClientVarifyInfo::~CDBClientVarifyInfo()
{

}

void CDBClientVarifyInfo::ResetData()
{
   m_strID           = _T("");	//ID
   m_strUserId       = _T("");	//用户ID
   m_strVarifyTime   = _T("");	//时间
   m_strMacInfo      = _T("");	//机器信息

   m_nOutTime = 0;
   
	//SetDataType(DAT_YARN);
}

void CDBClientVarifyInfo:: Copy(CDBClientVarifyInfo *pData)
{
	ASSERT(pData != NULL);
	CDataMid::Copy(pData);

   m_strID         = pData->m_strID;        	//ID
   m_strUserId     = pData->m_strUserId;     //用户ID
   m_strVarifyTime = pData->m_strVarifyTime;	//时间
   m_strMacInfo    = pData->m_strMacInfo   ;	//机器信息
   m_nOutTime = pData->m_nOutTime;

}

void CDBClientVarifyInfo::Serialize(CArchive& ar)
{
	CDataMid::Serialize(ar);//父类函数

	int nTagSize = 0;
	CString strName;
	int nNameSize;

	ar.Flush();
	if (ar.IsStoring())
	{
      MySerial.SaveDataStr(ar,_T("ID"),         m_strID        );
      MySerial.SaveDataStr(ar,_T("UserId"),     m_strUserId    );
      MySerial.SaveDataStr(ar,_T("VarifyTime"), m_strVarifyTime);
      MySerial.SaveDataStr(ar,_T("MacInfo"),    m_strMacInfo   );

		nNameSize = 8;
		strName = _T("DENDDEND");
		ar << nNameSize;
		ar << strName;
	}
	else
	{
		int nNumber = 0;
		ar >> nNameSize;
		ar >> strName;

		if(strName.GetLength()!=nNameSize)
		{
         return;
      }

		while(strName != _T("DENDDEND"))
		{
			if(nNumber > 200)
			{
				return;
			}
         else if (strName == _T("ID"))
         {         
            ar >> nTagSize >>m_strID;   
         }   
         else if (strName == _T("UserId"))      
         {         
            ar >> nTagSize >>m_strUserId;   
         }   
         else if (strName == _T("VarifyTime"))      
         {         
            ar >> nTagSize >>m_strVarifyTime;   
         }   
         else if (strName == _T("MacInfo"))      
         {         
            ar >> nTagSize >>m_strMacInfo;   
         }   
			else
			{
				ar >> nTagSize;
				ar.Flush();
				ar.GetFile()->Seek(nTagSize, CFile::current);
			}
			/////////////////////////////////////////////
			strName = _T("");
			ar >> nNameSize;
			ar >> strName;
			if(strName.GetLength() != nNameSize)
			{
            return;
         }
			nNumber++;
		}
	}
}

CDBClientVarifyInfo * CDBClientVarifyInfo::Instance()
{
	if(sm_inst.get() == 0)
	{
      sm_inst = shared_ptr<CDBClientVarifyInfo>(new CDBClientVarifyInfo);
   }

	return sm_inst.get();
}

BOOL CDBClientVarifyInfo::GetAllDBInfo(CADOConn *pADOConn)
{
	ASSERT(pADOConn != NULL);

	BOOL bRet = TRUE;

	if (NULL == pADOConn)
	{
		bRet = FALSE;
	}
	else
	{
      m_strID  		 = pADOConn->GetValueString(DB_ClientVarifyIno_Key_ID         );
      m_strUserId		 = pADOConn->GetValueString(DB_ClientVarifyIno_Key_UserId      );
      m_strVarifyTime = pADOConn->GetValueString(DB_ClientVarifyIno_Key_VarifyTime);
      m_strMacInfo    = pADOConn->GetValueString(DB_ClientVarifyIno_Key_MacInfo);
      m_nOutTime      = pADOConn->GetValueInt(CS_DIFF_OUTTIME);

		bRet = TRUE;
	}

	return bRet;
}




BOOL CDBClientVarifyInfo::DelAllDBInfoByID(CADOConn *pADOConn)
{
	ASSERT(pADOConn != NULL);
	m_strID.Trim();
	ASSERT(!m_strID.IsEmpty());

	BOOL bRet = TRUE;

	CString strSQL = _T("");
	strSQL.Format(_T("delete from %s where %s='%s'"),
      DB_TABLE_CLIENT_VARIFY_INFO,
      DB_ClientVarifyIno_Key_ID,m_strID);

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

BOOL CDBClientVarifyInfo::UpdateAllDBInfoByID( CADOConn *pADOConn )
{
	ASSERT(pADOConn != NULL);
	m_strID.Trim();
	ASSERT(!m_strID.IsEmpty());

	BOOL bRet = TRUE;
	CString strSQL = _T("");
	//								 1         2         3       4         5
	strSQL.Format(_T("update %s set \
                    %s='%s', %s='%s', %s ='%s' \
						  where %s = '%s'"),
						DB_TABLE_CLIENT_VARIFY_INFO,

                  DB_ClientVarifyIno_Key_UserId,      m_strUserId,
                  DB_ClientVarifyIno_Key_VarifyTime,  m_strVarifyTime,
                  DB_ClientVarifyIno_Key_MacInfo,     m_strMacInfo,

                  DB_ClientVarifyIno_Key_ID,          m_strID);  		

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


BOOL CDBClientVarifyInfo::InsertAllDBInfoByID( CADOConn *pADOConn )
{
	ASSERT(pADOConn != NULL);
	m_strID.Trim();
	ASSERT(!m_strID.IsEmpty());

	BOOL bRet = TRUE;

	CString strSQL = _T(""),strFormat = _T(""),strValue = _T("");
	strFormat.Format(_T("%s,%s,%s"),

      DB_ClientVarifyIno_Key_UserId,    
      DB_ClientVarifyIno_Key_VarifyTime,
      DB_ClientVarifyIno_Key_MacInfo
		);
	//					1 ,2   ,3   ,4   ,5   ,6   ,7   ,8  ,9  ,10  ,11
	strValue.Format(_T("'%s','%s','%s'"),
		
      m_strUserId,
      m_strVarifyTime,
      m_strMacInfo
		);

   
   
	strSQL.Format(_T("insert into %s (%s) values(%s)"),
      DB_TABLE_CLIENT_VARIFY_INFO,
      strFormat,
      strValue);

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

//		by WangZY 2018/09/04
BOOL CDBClientVarifyInfo::UpdateHeartbeetTimeById(CADOConn *pADOConn)
{
   ASSERT(pADOConn != NULL);
   m_strID.Trim();
   ASSERT(!m_strID.IsEmpty());

   BOOL bRet = TRUE;
   CString strSQL = _T("");
   //								 1         2         3       4         5
   strSQL.Format(_T("update %s set \
                    %s=%s \
                    where %s = '%s'"),
                    DB_TABLE_CLIENT_VARIFY_INFO,

                    DB_ClientVarifyIno_Key_VarifyTime,  DBS_GETDATE,
                    
                    DB_ClientVarifyIno_Key_ID,          m_strID);  		

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

//		by WangZY 2018/09/04
BOOL CDBClientVarifyInfo::InsertAllDBInfoByUserAndMacID(CADOConn *pADOConn)
{
   ASSERT(pADOConn != NULL);
   m_strID.Trim();
   //ASSERT(!m_strID.IsEmpty());

   BOOL bRet = TRUE;

   CString strSQL = _T(""),strFormat = _T(""),strValue = _T("");
   strFormat.Format(_T("%s,%s,%s"),

      DB_ClientVarifyIno_Key_UserId,    
      DB_ClientVarifyIno_Key_VarifyTime,
      DB_ClientVarifyIno_Key_MacInfo
      );
   //					1 ,2   ,3   ,4   ,5   ,6   ,7   ,8  ,9  ,10  ,11
   strValue.Format(_T("'%s',%s,'%s'"),

      m_strUserId,
      DBS_GETDATE,
      m_strMacInfo
      );



   strSQL.Format(_T("insert into %s (%s) values(%s)"),
      DB_TABLE_CLIENT_VARIFY_INFO,
      strFormat,
      strValue);

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

//		by WangZY 2018/09/04
BOOL CDBClientVarifyInfo::DeleteDBInfoByUserId(CADOConn *pADOConn,CString strUserId)
{
   ASSERT(pADOConn != NULL);
   BOOL bRet = TRUE;

   CString strSQL = _T("");
   strSQL.Format(_T("delete from %s where %s='%s'"),
      DB_TABLE_CLIENT_VARIFY_INFO,
      DB_ClientVarifyIno_Key_UserId,strUserId);

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

//		by WangZY 2018/09/04
BOOL CDBClientVarifyInfo::DeleteDBInfoByUserAndMacId(CADOConn *pADOConn,CString strUserId,CString strMacId)
{
   ASSERT(pADOConn != NULL);
   BOOL bRet = TRUE;

   CString strSQL = _T("");
   strSQL.Format(_T("delete from %s where %s='%s' and %s='%s'"),
      DB_TABLE_CLIENT_VARIFY_INFO,
      DB_ClientVarifyIno_Key_UserId,strUserId,
      DB_ClientVarifyIno_Key_MacInfo,strMacId);

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

void CDBClientVarifyInfo::Trim()
{
	m_strUserId.Trim();
	m_strVarifyTime.Trim();
   m_strMacInfo.Trim();
   
	
}



CDBClientVarifyInfoList::CDBClientVarifyInfoList()
{

}
CDBClientVarifyInfoList::~CDBClientVarifyInfoList()
{

}

CDBClientVarifyInfo*  CDBClientVarifyInfoList::GetItem(int nIndex)
{
	if (nIndex<0
      ||nIndex>=GetCount())
	{	
      return nullptr;
   }
	return (CDBClientVarifyInfo*)GetAt(FindIndex(nIndex));
}

CDBClientVarifyInfo* CDBClientVarifyInfoList::GetItemById(CString strId)
{
   CDBClientVarifyInfo * pItem = nullptr;
   strId.Trim();
   if (!strId.IsEmpty())
   {
      for(int i=0;i< GetCount();i++)
      {
         CDBClientVarifyInfo * pObject = GetItem(i);
         if(strId==pObject->m_strID)
         {
            pItem = pObject;
            break;
         }
      }
   }

   return pItem;
}


void CDBClientVarifyInfoList::AddItem(CDBClientVarifyInfo* pItem)
{
	CDBClientVarifyInfo*pData=new CDBClientVarifyInfo;
	pData->Copy(pItem);
	AddTail(pData);
}

void CDBClientVarifyInfoList::DeleteItem(int nIndex)
{
	if (nIndex<0||nIndex>GetCount())
	{
      return;
   }
	CDBClientVarifyInfo *pObject=(CDBClientVarifyInfo*)GetItem(nIndex);
	delete pObject;
	pObject=nullptr;
	RemoveAt(FindIndex(nIndex));
}

int CDBClientVarifyInfoList::GetIndexById(CString strId)
{
	int nSel = -1;
	strId.Trim();
	if (!strId.IsEmpty())
	{
		for(int i=0;i< GetCount();i++)
		{
			CDBClientVarifyInfo * pObject = GetItem(i);
			if(strId==pObject->m_strID)
			{
				nSel = i;
				break;
			}
		}
	}

	return nSel;
}



void CDBClientVarifyInfoList::GetListFromDB(CADOConn *pADOConn)
{
	ASSERT(pADOConn != NULL);
	
	Empty();
	CString strSQL = _T("");
  
   strSQL.Format(_T("select %s,%s,%s,%s,DATEDIFF(MINUTE, %s, GetDate()) as %s \
      from %s"),
      DB_ClientVarifyIno_Key_ID		      ,//1
      DB_ClientVarifyIno_Key_UserId       ,//2
      DB_ClientVarifyIno_Key_VarifyTime   ,//3
      DB_ClientVarifyIno_Key_MacInfo      ,//4
      DB_ClientVarifyIno_Key_VarifyTime,
      CS_DIFF_OUTTIME,

      DB_TABLE_CLIENT_VARIFY_INFO);
   	
	pADOConn->GetRecordSet(strSQL);

	while (!pADOConn->adoEOF())
	{
		CDBClientVarifyInfo oData;
		oData.GetAllDBInfo(pADOConn);
		AddItem(&oData);
		pADOConn->MoveNext();
	}
}


CDBClientVarifyInfoList * CDBClientVarifyInfoList::Instance()
{
	if(sm_inst.get() == 0)
		sm_inst = shared_ptr<CDBClientVarifyInfoList>(new CDBClientVarifyInfoList);

	return sm_inst.get();
}


BOOL CDBClientVarifyInfoList::GetInfoById(__in CADOConn *pADOConn,
   __in CString strId,__out CDBClientVarifyInfo* pObj)
{
   if (pObj == nullptr)
   {
      ASSERT(pObj != nullptr);
      return FALSE;
   }
   ASSERT(pADOConn != NULL);
   CString strSQL = _T("");

   strSQL.Format(_T("select *, DATEDIFF(MINUTE, %s, GetDate()) as %s \
                    from %s where %s = '%s'"),
      DB_ClientVarifyIno_Key_VarifyTime,
      CS_DIFF_OUTTIME,
      DB_TABLE_CLIENT_VARIFY_INFO,
      DB_ClientVarifyIno_Key_ID,
      strId);

   pADOConn->GetRecordSet(strSQL);
   if (!pADOConn->adoEOF())
   {
      pObj->GetAllDBInfo(pADOConn);
      
      return TRUE;
   }

   return FALSE;
}

//		by WangZY 2018/09/04
CDBClientVarifyInfo* CDBClientVarifyInfoList::GetItemByMacIdAndUserId(
   CString strMacId,CString strUserId)
{
   CDBClientVarifyInfo * pItem = nullptr;
   strMacId.Trim();
   strUserId.Trim();
   if (!strMacId.IsEmpty()
      &&!strUserId.IsEmpty())
   {
      for(int i=0;i< GetCount();i++)
      {
         CDBClientVarifyInfo * pObject = GetItem(i);
         if(strMacId==pObject->m_strMacInfo
            &&strUserId==pObject->m_strUserId)
         {
            pItem = pObject;
            break;
         }
      }
   }

   return pItem;
}

//		by WangZY 2018/09/04
CDBClientVarifyInfo* CDBClientVarifyInfoList::GetItemByMacId(CString strMacId)
{
   CDBClientVarifyInfo * pItem = nullptr;
   strMacId.Trim();
   if (!strMacId.IsEmpty())
   {
      for(int i=0;i< GetCount();i++)
      {
         CDBClientVarifyInfo * pObject = GetItem(i);
         if(strMacId==pObject->m_strMacInfo)
         {
            pItem = pObject;
            break;
         }
      }
   }

   return pItem;
}

//		by WangZY 2018/09/04
CDBClientVarifyInfo* CDBClientVarifyInfoList::GetItemByUserId(CString strMacId)
{
   CDBClientVarifyInfo * pItem = nullptr;
   strMacId.Trim();
   if (!strMacId.IsEmpty())
   {
      for(int i=0;i< GetCount();i++)
      {
         CDBClientVarifyInfo * pObject = GetItem(i);
         if(strMacId==pObject->m_strUserId)
         {
            pItem = pObject;
            break;
         }
      }
   }

   return pItem;
}

int CDBClientVarifyInfoList::GetIndexByMacIdAndUserId(
   CString strMacId,CString strUserId)
{   
   strMacId.Trim();
   strUserId.Trim();
   if (!strMacId.IsEmpty()
      &&!strUserId.IsEmpty())
   {
      for(int i=0;i< GetCount();i++)
      {
         CDBClientVarifyInfo * pObject = GetItem(i);
         if(strMacId==pObject->m_strMacInfo
            &&strUserId==pObject->m_strUserId)
         {
           return i;
         }
      }
   }

   return -1;
}

