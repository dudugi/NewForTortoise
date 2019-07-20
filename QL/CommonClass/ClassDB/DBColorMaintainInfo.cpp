#include "StdAfx.h"
#include "DBColorMaintainInfo.h"
#include "DBKeyDef.h"

#if MATERIEL_IMAGE
#include "..\ClassEx\ADOConn\DBImage.h"
#endif

using namespace Gdiplus;

///////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CDBColorMaintainInfo,  CDataMid, 1)
IMPLEMENT_SERIAL(CDBColorMaintainInfoList,  CDataListMid, 1)

std::shared_ptr<CDBColorMaintainInfo> CDBColorMaintainInfo::sm_inst;
std::shared_ptr<CDBColorMaintainInfoList> CDBColorMaintainInfoList::sm_inst;

CDBColorMaintainInfo::CDBColorMaintainInfo()
{
	ResetData(); 
} 

CDBColorMaintainInfo::~CDBColorMaintainInfo()
{
}


void CDBColorMaintainInfo::ResetData()
{
   m_strID	    = _T("");		//颜色ID
   m_strClrName	 = _T("");		//颜色名称
   m_strClrCode		 = _T("");		//颜色编号
   m_strClrRGB	    = _T("");	   //颜色RGB
   m_strClrMemo	 = _T("");	   //颜色说明
	SetDataType(DAT_YARN);
}

void CDBColorMaintainInfo:: Copy(CDBColorMaintainInfo *pData)
{
	ASSERT(pData != NULL);
	CDataMid::Copy(pData);

   m_strID	          = pData->m_strID;		//颜色ID
   m_strClrName	    = pData->m_strClrName;		//颜色名称
   m_strClrCode		 = pData->m_strClrCode;		//颜色编号
   m_strClrRGB	       = pData->m_strClrRGB;	   //颜色RGB
   m_strClrMemo	    = pData->m_strClrMemo;	   //颜色说明
}

void CDBColorMaintainInfo::Serialize(CArchive& ar)
{
	CDataMid::Serialize(ar);//父类函数

	int nTagSize = 0;
	CString strName;
	int nNameSize;

	ar.Flush();
	if (ar.IsStoring())
	{
      MySerial.SaveDataStr(ar,_T("ID"),   m_strID);
      MySerial.SaveDataStr(ar,_T("Name"), m_strClrName);
      MySerial.SaveDataStr(ar,_T("Num"),  m_strClrCode);
      MySerial.SaveDataStr(ar,_T("RGB"),  m_strClrRGB);
      MySerial.SaveDataStr(ar,_T("Memo"), m_strClrMemo);

		nNameSize = 5;
		strName = ("DENDDEND");
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

		while(strName != ("DENDDEND"))
		{
			if(nNumber > 200)
			{
				return;
			}
         else if (strName == ("ID"))
         {         
            ar >> nTagSize >>m_strID;   
         }   
         else if (strName == ("Name"))      
         {         
            ar >> nTagSize >>m_strClrName;   
         }
         else if (strName == ("Num"))      
         {         
            ar >> nTagSize >>m_strClrCode;   
         }   
         else if (strName == ("RGB"))      
         {         
            ar >> nTagSize >>m_strClrRGB;   
         }   
         else if (strName == ("Memo"))      
         {         
            ar >> nTagSize >>m_strClrMemo;
			}
			else
			{
				ar >> nTagSize;
				ar.Flush();
				ar.GetFile()->Seek(nTagSize, CFile::current);
			}
			/////////////////////////////////////////////
			strName = ("");
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

CDBColorMaintainInfo * CDBColorMaintainInfo::Instance()
{
	if(sm_inst.get() == 0)
	{
      sm_inst = shared_ptr<CDBColorMaintainInfo>(new CDBColorMaintainInfo);
   }

	return sm_inst.get();
}

BOOL CDBColorMaintainInfo::GetAllDBInfo(CADOConn *pADOConn,bool bNeedPic)
{
	ASSERT(pADOConn != NULL);

	BOOL bRet = TRUE;

	if (NULL == pADOConn)
	{
		bRet = FALSE;
	}
	else
	{
      m_strID  		    = pADOConn->GetValueString(DBColorMaintain_Key_ID);
      m_strClrName		 = pADOConn->GetValueString(DBColorMaintain_Key_cClrName);
      m_strClrRGB        = pADOConn->GetValueString(DBColorMaintain_Key_cClrRGB);
      m_strClrCode       = pADOConn->GetValueString(DBColorMaintain_Key_cClrCode);
      m_strClrMemo       = pADOConn->GetValueString(DBColorMaintain_Key_cMemo);
   }
	return bRet;
}




BOOL CDBColorMaintainInfo::DelAllDBInfoByID(CADOConn *pADOConn)
{
	ASSERT(pADOConn != NULL);
	m_strID.Trim();
	ASSERT(!m_strID.IsEmpty());

	BOOL bRet = TRUE;

	CString strSQL = _T("");
	strSQL.Format(_T("delete from %s where %s='%s'"),
      DB_TABLE_COLORMAINTAIN_INFO,
      DBColorMaintain_Key_ID,m_strID);

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

BOOL CDBColorMaintainInfo::UpdateAllDBInfoByID( CADOConn *pADOConn )
{
	ASSERT(pADOConn != NULL);
	m_strClrCode.Trim();
	ASSERT(!m_strClrCode.IsEmpty());

	BOOL bRet = TRUE;
	CString strSQL = _T("");
	//								 1         2         3       4  
	strSQL.Format(_T("update %s set \
                    %s='%s', %s ='%s', %s = '%s'\
						  where %s = '%s'"),
						DB_TABLE_COLORMAINTAIN_INFO,

                  DBColorMaintain_Key_cClrName,  m_strClrName, //1
                  DBColorMaintain_Key_cClrRGB,   m_strClrRGB, //2
                  DBColorMaintain_Key_cMemo,  m_strClrMemo, //3

                  DBColorMaintain_Key_cClrCode,   m_strClrCode
									);

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

BOOL CDBColorMaintainInfo::InsertAllDBInfoByID( CADOConn *pADOConn )
{
	ASSERT(pADOConn != NULL);
	m_strClrCode.Trim();
	ASSERT(!m_strClrCode.IsEmpty());

	BOOL bRet = TRUE;

	CString strSQL = _T(""),strFormat = _T(""),strValue = _T("");
	strFormat.Format(_T("%s,%s,%s,%s"),

      DBColorMaintain_Key_cClrName,   //1
      DBColorMaintain_Key_cClrCode,    //2
      DBColorMaintain_Key_cClrRGB,    //3
      DBColorMaintain_Key_cMemo   //4
		);
	//					       1 ,  2 ,  3 ,  4 
	strValue.Format(_T("'%s','%s','%s','%s'"),
      m_strClrName,
      m_strClrCode,
      m_strClrRGB,
      m_strClrMemo
		);

	strSQL.Format(_T("insert into %s (%s) values(%s)"),
      DB_TABLE_COLORMAINTAIN_INFO,
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

void CDBColorMaintainInfo::Trim()
{
	m_strClrName.Trim();
   m_strID.Trim();
   m_strClrRGB.Trim();
   m_strClrCode.Trim();
	m_strClrMemo.Trim();
	
}

BOOL CDBColorMaintainInfo::GetAllDBInfoByID( CADOConn *pADOConn,bool bNeedColorCard/*=false*/ )
{
   BOOL bRet = FALSE;
   CString strSQL = _T("");
   strSQL.Format(_T("select * from %s where %s = '%s'"),DB_TABLE_COLORMAINTAIN_INFO,DBColorMaintain_Key_ID,m_strID);
   if (pADOConn != nullptr)
   {
      bRet = TRUE;
      pADOConn->GetRecordSet(strSQL);
      if (!pADOConn->adoEOF())
      {
         m_strID  		    = pADOConn->GetValueString(DBColorMaintain_Key_ID);
         m_strClrName		 = pADOConn->GetValueString(DBColorMaintain_Key_cClrName);
         m_strClrRGB        = pADOConn->GetValueString(DBColorMaintain_Key_cClrRGB);
         m_strClrCode       = pADOConn->GetValueString(DBColorMaintain_Key_cClrCode);
         m_strClrMemo       = pADOConn->GetValueString(DBColorMaintain_Key_cMemo);
      }
   }
   return bRet;
}

CDBColorMaintainInfoList::CDBColorMaintainInfoList()
{

}
CDBColorMaintainInfoList::~CDBColorMaintainInfoList()
{

}

CDBColorMaintainInfo*  CDBColorMaintainInfoList::GetItem(int nIndex)
{
	if (nIndex<0
      ||nIndex>=GetCount())
	{	
      return nullptr;
   }
	return (CDBColorMaintainInfo*)GetAt(FindIndex(nIndex));
}

CDBColorMaintainInfo* CDBColorMaintainInfoList::GetItemByColorCode(CString strCode)
{
   CDBColorMaintainInfo * pItem = nullptr;
   strCode.Trim();
   if (!strCode.IsEmpty())
   {
      for(int i=0;i< GetCount();i++)
      {
         CDBColorMaintainInfo * pObject = GetItem(i);
         if(strCode==pObject->m_strClrCode)
         {
            pItem = pObject;
            break;
         }
      }
   }

   return pItem;
}

void CDBColorMaintainInfoList::AddItem(CDBColorMaintainInfo* pItem)
{
	CDBColorMaintainInfo*pData=new CDBColorMaintainInfo;
	pData->Copy(pItem);
	AddTail(pData);
}
//删除一个项
void CDBColorMaintainInfoList::DeleteItem(int nIndex)
{
	if (nIndex<0||nIndex>GetCount())
	{
      return;
   }
	CDBColorMaintainInfo *pObject=(CDBColorMaintainInfo*)GetItem(nIndex);
	delete pObject;
	pObject=nullptr;
	RemoveAt(FindIndex(nIndex));
}
//根据颜色id获得索引
int CDBColorMaintainInfoList::GetIndexByColorId(CString strId)
{
	int nSel = -1;
	strId.Trim();
	if (!strId.IsEmpty())
	{
		for(int i=0;i< GetCount();i++)
		{
			CDBColorMaintainInfo * pObject = GetItem(i);
			if(strId==pObject->m_strID)
			{
				nSel = i;
				break;
			}
		}
	}

	return nSel;
}

void CDBColorMaintainInfoList::GetListFromDB(CADOConn *pADOConn,bool bNeedPic)
{
	ASSERT(pADOConn != NULL);
	
	Empty();
	CString strSQL = _T("");
   if (bNeedPic)
   {
      strSQL.Format(_T("select * from %s"),
         DB_TABLE_COLORMAINTAIN_INFO);
   }
   else
   {
      strSQL.Format(_T("select %s,%s,%s,%s,%s from %s"),
         DBColorMaintain_Key_ID		     ,//1
         DBColorMaintain_Key_cClrName       ,//2
         DBColorMaintain_Key_cClrCode        ,//3
         DBColorMaintain_Key_cClrRGB        ,//4
         DBColorMaintain_Key_cMemo       ,//5

         DB_TABLE_COLORMAINTAIN_INFO);
   }	
	pADOConn->GetRecordSet(strSQL);

	while (!pADOConn->adoEOF())
	{
		CDBColorMaintainInfo oData;
		oData.GetAllDBInfo(pADOConn,bNeedPic);
		AddItem(&oData);
		pADOConn->MoveNext();
	}
}


CDBColorMaintainInfoList * CDBColorMaintainInfoList::Instance()
{
	if(sm_inst.get() == 0)
		sm_inst = shared_ptr<CDBColorMaintainInfoList>(new CDBColorMaintainInfoList);

	return sm_inst.get();
}

#ifdef USING_GRIDCTRL_MARK
MAP_GridCtrl_AllData CDBColorMaintainInfoList::CreatrGridData()
{
	MAP_GridCtrl_AllData  map_all_data;

	int nIndex = 0,nCount = GetCount();
	int nValidCount = 1;
	for (nIndex = 0;nIndex < nCount;nIndex++)
	{
		CDBColorMaintainInfo * pData = GetItem(nIndex);
		if (nullptr != pData)
		{
			MAP_GridCtrl_RowData map_row_data;

         InsertRowData(DBColorMaintain_Key_ID	  ,map_row_data, pData->m_strID );  //颜色ID
         InsertRowData(DBColorMaintain_Key_cClrName  ,map_row_data, pData->m_strClrName );  //颜色名称
         InsertRowData(DBColorMaintain_Key_cClrCode   ,map_row_data, pData->m_strClrCode );  //颜色编号
         InsertRowData(DBColorMaintain_Key_cClrRGB   ,map_row_data, pData->m_strClrRGB );  //颜色RGB
         InsertRowData(DBMateriel_Key_cMemo       ,map_row_data, pData->m_strClrMemo );  //颜色说明
			//写入行数据
			map_all_data.insert(make_pair(nValidCount,map_row_data));
			//行数据插入所有数据中

			nValidCount++;
		}
	}

	return map_all_data;
}

BOOL CDBColorMaintainInfoList::GetEmptyRowData(
   __out MAP_GridCtrl_RowData &mapEmptyRowData)
{
	mapEmptyRowData.clear();

   InsertRowData(DBColorMaintain_Key_ID	  ,_T(""), mapEmptyRowData);
   InsertRowData(DBColorMaintain_Key_cClrName  ,_T(""), mapEmptyRowData);
   InsertRowData(DBColorMaintain_Key_cClrCode   ,_T(""), mapEmptyRowData);
   InsertRowData(DBColorMaintain_Key_cClrRGB   ,_T(""), mapEmptyRowData);
   InsertRowData(DBMateriel_Key_cMemo       ,_T(""), mapEmptyRowData);
   
	return TRUE;

}
BOOL CDBColorMaintainInfoList::GetInfoByColorId(__in CADOConn *pADOConn,
   __in CString strId,__out CDBColorMaintainInfo* pObj)
{
   if (pObj == nullptr)
   {
      ASSERT(pObj != nullptr);
      return FALSE;
   }
   ASSERT(pADOConn != NULL);
   CString strSQL = _T("");

   strSQL.Format(_T("select * from %s where %s = '%s'"),
      DB_TABLE_COLORMAINTAIN_INFO,
      DBColorMaintain_Key_ID,
      strId);

   pADOConn->GetRecordSet(strSQL);
   if (!pADOConn->adoEOF())
   {
      pObj->GetAllDBInfo(pADOConn,true);
      
      return TRUE;
   }

   return FALSE;
}
#endif // USING_GRIDCTRL_MARK

BOOL CDBColorMaintainInfoList::operator= (CDBColorMaintainInfoList &pData)
{
   for (int i = 0;i<pData.GetCount();i++)
   {
      CDBColorMaintainInfo *pMate = (CDBColorMaintainInfo *) pData.GetAt(pData.FindIndex(i));
      if (NULL != pMate)
      {
         if(GetIndexByColorId(pMate->m_strID) == -1)
         {
            AddItem(pMate);
         }
      }
   }

   return TRUE;
}

COLORREF CDBColorMaintainInfo::StrConvertToColor()
{
   if (!m_strClrRGB.IsEmpty())
   {
      m_strClrRGB.Replace('(','(');
      m_strClrRGB.Replace(')',')');
      m_strClrRGB.Replace(',',',');

      int ipos_start = m_strClrRGB.Find(_T("("));
      if (ipos_start < 0)
      {
         return RGB(0,0,0);
      }
      ipos_start += 1;
      int ipos_end = m_strClrRGB.Find(_T(","),ipos_start);
      if (ipos_end < 0)
      {
         return RGB(0,0,0);
      }

      CString str_r = m_strClrRGB.Mid(ipos_start,ipos_end-ipos_start);
      int r = _ttoi(str_r);

      ipos_start = ipos_end;
      ipos_start += 1;
      ipos_end = m_strClrRGB.Find(_T(","),ipos_start);
      if (ipos_end < 0)
      { 
         return RGB(0,0,0);
      }
      CString str_g = m_strClrRGB.Mid(ipos_start,ipos_end-ipos_start);
      int g = _ttoi(str_g);

      ipos_start = ipos_end;
      ipos_start += 1;
      ipos_end = m_strClrRGB.Find(_T(")"),ipos_start);
      if (ipos_end < 0)
      { 
         return RGB(0,0,0);
      }
      CString str_b = m_strClrRGB.Mid(ipos_start,ipos_end-ipos_start);
      int b = _ttoi(str_b);
      COLORREF color = RGB(r,g,b);
      return RGB(r,g,b);
   }
   return RGB(0,0,0);
}
