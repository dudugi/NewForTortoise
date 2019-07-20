#include "StdAfx.h"
#include "UserLocalText.h"
#include "MySerial.h"


IMPLEMENT_SERIAL(CUserCtrlDefValue,  CDataMid, 1)
IMPLEMENT_SERIAL(CUserCtrlDefValueList,  CDataListMid, 1)

std::shared_ptr<CUserCtrlDefValue> CUserCtrlDefValue::sm_inst;
std::shared_ptr<CUserCtrlDefValueList> CUserCtrlDefValueList::sm_inst;

CUserCtrlDefValue::CUserCtrlDefValue()
{
	ResetData();
}

CUserCtrlDefValue::~CUserCtrlDefValue()
{

}

void CUserCtrlDefValue::ResetData()
{
	m_nDlgID = -1;		//对话框ID
	m_nCtrlID = -1;		//控件ID
	m_strCtrlType = _T("");
	m_strDefValue = _T("");	
}


CUserCtrlDefValue * CUserCtrlDefValue::Instance()
{
	if(sm_inst.get() == 0)
		sm_inst = shared_ptr<CUserCtrlDefValue>(new CUserCtrlDefValue);
	return sm_inst.get();
}

void CUserCtrlDefValue::Copy(CUserCtrlDefValue *pData)
{
	pData->m_nDlgID = m_nDlgID;			//对话框ID
	pData->m_nCtrlID = m_nCtrlID;		//控件ID
	pData->m_strCtrlType = m_strCtrlType;
	pData->m_strDefValue = m_strDefValue;
}

void CUserCtrlDefValue::Serialize(CArchive& ar)
{
	CDataMid::Serialize(ar);

	int nTagSize = 0;
	CString strName;
	int nNameSize;

	ar.Flush();
	if (ar.IsStoring())
	{
		MySerial.SaveDataInt(ar,_T("CTRLDGID"),m_nDlgID);
		MySerial.SaveDataInt(ar,_T("CTRLCRID"),m_nCtrlID);
		MySerial.SaveDataStr(ar,_T("CTRLTYPE"),m_strCtrlType);
		MySerial.SaveDataStr(ar,_T("CTRLVAUE"),m_strDefValue);

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
			return;

		while(strName != _T("DENDDEND"))
		{
			if(nNumber > 200)
			{
				return;
			}
			else if (strName == _T("CTRLDGID"))
			{
				ar >>nTagSize >> m_nDlgID;
			}
			else if (strName == _T("CTRLCRID"))
			{
				ar >>nTagSize >> m_nCtrlID;
			}
			else if (strName == _T("CTRLTYPE"))
			{
				ar >>nTagSize >> m_strCtrlType;
			}
			else if (strName == _T("CTRLVAUE"))
			{
				ar >>nTagSize >> m_strDefValue;
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
				return;

			nNumber++;
		}
	}
}

//
CUserCtrlDefValueList::CUserCtrlDefValueList()
{

}

CUserCtrlDefValueList::~CUserCtrlDefValueList()
{

}


CUserCtrlDefValueList * CUserCtrlDefValueList::Instance()
{
	if(sm_inst.get() == 0)
		sm_inst = shared_ptr<CUserCtrlDefValueList>(new CUserCtrlDefValueList);

	return sm_inst.get();
}

void CUserCtrlDefValueList::Serialize(CArchive& ar)
{
	//不需调用基类Serialize

	int nTagSize = 0;
	CString strName;
	int nNameSize;

	ar.Flush();
	if (ar.IsStoring())
	{
		MySerial.SaveDataObjectList(ar,_T("CTRLLIST"),this);

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
			return;

		while(strName != _T("DENDDEND"))
		{
			if(nNumber > 200)
			{
				return;
			}
			else if (strName == _T("CTRLLIST"))
			{
				Empty();
				int dateSize;
				ar >> nTagSize;
				ar >> dateSize;
				for(int i=0; i<dateSize; i++)
				{
					CObject  *pObject = new CUserCtrlDefValue;
					pObject->Serialize(ar);
					AddTail((CObject *)pObject);
				}
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
				return;
			nNumber++;
		}
	}
}

CUserCtrlDefValue* CUserCtrlDefValueList::GetItem(int nIndex)
{
	if (nIndex<0||nIndex>=GetCount())
		return NULL;

	return (CUserCtrlDefValue*)GetAt(FindIndex(nIndex));
}

void CUserCtrlDefValueList::DeleteItem(int nIndex)
{
	if (nIndex<0||nIndex>GetCount())
		return;

	CUserCtrlDefValue *pObject  =(CUserCtrlDefValue*)GetItem(nIndex);
	delete pObject;
	pObject = NULL;
	RemoveAt(FindIndex(nIndex));
}

void CUserCtrlDefValueList::DeleteItem(int nDlgID,int nCtrlID,CString strCtrlType/*=_T("")*/)
{
	int nCount= GetCount()-1;

	for(int i=nCount; i>=0; i--)
	{
		CUserCtrlDefValue *pUserText = GetItem(i);
		if(pUserText->m_nDlgID==nDlgID
			&&pUserText->m_nCtrlID==nCtrlID
			&&pUserText->m_strCtrlType==strCtrlType)
		{
			DeleteItem(i);
		}
	}
}

CString CUserCtrlDefValueList::FindDefVaule(int nDlgID,int nCtrlID,CString strCtrlType/*=_T("")*/)
{
	CString strValue = _T("");

	for(int i=0; i<GetCount(); i++)
	{
		CUserCtrlDefValue *pUserText = GetItem(i);
		if(pUserText->m_nDlgID==nDlgID
			&&pUserText->m_nCtrlID==nCtrlID
			&&pUserText->m_strCtrlType==strCtrlType)
		{
			strValue = pUserText->m_strDefValue;
			break;
		}
	}

	return strValue;
}

int CUserCtrlDefValueList::FindDefVauleSel(int nDlgID,int nCtrlID,CString strCtrlType/*=_T("")*/)
{
	int nSel = -1;
	for(int i=0; i<GetCount(); i++)
	{
		CUserCtrlDefValue *pUserText = GetItem(i);
		if(pUserText->m_nDlgID==nDlgID
			&&pUserText->m_nCtrlID==nCtrlID
			&&pUserText->m_strCtrlType==strCtrlType)
		{
			nSel = i;
			break;
		}
	}

	return nSel;
}

int CUserCtrlDefValueList::FindDefVauleSelNoCtrlType(int nDlgID,int nCtrlID)
{
   int nSel = -1;
   for(int i=0; i<GetCount(); i++)
   {
      CUserCtrlDefValue *pUserText = GetItem(i);
      if(pUserText->m_nDlgID==nDlgID
         &&pUserText->m_nCtrlID==nCtrlID)
      {
         nSel = i;
         break;
      }
   }

   return nSel;
}

BOOL CUserCtrlDefValueList::AddDefVaule(int nDlgID,int nCtrlID,CString strDefValue,CString strCtrlType/*=_T("")*/)
{
	strDefValue.Trim();
	//ASSERT(!strDefValue.IsEmpty());

	BOOL bRet = FALSE;
	int nSel = FindDefVauleSelNoCtrlType(nDlgID,nCtrlID);
	if (-1 == nSel)	
	{
		//add
		CUserCtrlDefValue *pUserText = new CUserCtrlDefValue;
		pUserText->m_nDlgID = nDlgID;
		pUserText->m_nCtrlID = nCtrlID;
		pUserText->m_strCtrlType = strCtrlType;
		pUserText->m_strDefValue = strDefValue;

		AddHead(pUserText);

		bRet = TRUE;
	}
	else
	{
		//update
		CUserCtrlDefValue *pData = GetItem(nSel);
		if (pData)
		{
			pData->m_nDlgID = nDlgID;
			pData->m_nCtrlID = nCtrlID;
			pData->m_strCtrlType = strCtrlType;
			pData->m_strDefValue = strDefValue;
		}
	}

	return bRet;
}

/////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CUserLocalText,  CDataMid, 1)
IMPLEMENT_SERIAL(CUserLocalTextList,  CDataListMid, 1)

std::shared_ptr<CUserLocalText> CUserLocalText::sm_inst;
std::shared_ptr<CUserLocalTextList> CUserLocalTextList::sm_inst;

CUserLocalText::CUserLocalText()
{
	ResetData();
}


CUserLocalText::~CUserLocalText()
{
}

void CUserLocalText::ResetData()
{
	m_nDlgID = 0;
	m_nCboID = 0;
	m_strText = _T("");
	m_strType = _T("");
	m_strName = _T("");

	SetDataType(-10);//用户数据类型-10
}

void CUserLocalText::Copy(CUserLocalText *pData)
{
	ASSERT(pData != NULL);
	CDataMid::Copy(pData);

	m_nDlgID = pData->m_nDlgID;
	m_nCboID = pData->m_nCboID;
	m_strText = pData->m_strText;
	m_strType = pData->m_strType;
	m_strName = pData->m_strName;
}

void CUserLocalText::Serialize(CArchive& ar)
{
	CDataMid::Serialize(ar);

	int nTagSize = 0;
	CString strName;
	int nNameSize;

	ar.Flush();
	if (ar.IsStoring())
	{
		MySerial.SaveDataInt(ar,_T("USERDGID"),m_nDlgID);
		MySerial.SaveDataInt(ar,_T("USERCRID"),m_nCboID);
		MySerial.SaveDataStr(ar,_T("USERTEXT"),m_strText);
		MySerial.SaveDataStr(ar,_T("USERTYPE"),m_strType);
		MySerial.SaveDataStr(ar,_T("USERNAME"),m_strName);

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
			return;

		while(strName != _T("DENDDEND"))
		{
			if(nNumber > 200)
			{
				return;
			}
			else if (strName == _T("USERDGID"))
			{
				ar >>nTagSize >> m_nDlgID;
			}
			else if (strName == _T("USERCRID"))
			{
				ar >>nTagSize >> m_nCboID;
			}
			else if (strName == _T("USERTEXT"))
			{
				ar >>nTagSize >> m_strText;
			}
			else if (strName == _T("USERTYPE"))
			{
				ar >>nTagSize >> m_strType;
			}
			else if (strName == _T("USERNAME"))
			{
				ar >>nTagSize >> m_strName;
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
				return;

			nNumber++;
		}
	}
}


CUserLocalText * CUserLocalText::Instance()
{
	if(sm_inst.get() == 0)
		sm_inst = shared_ptr<CUserLocalText>(new CUserLocalText);
	return sm_inst.get();
}

/////////////////////
CUserLocalTextList::CUserLocalTextList()
{

}

CUserLocalTextList::~CUserLocalTextList()
{
	//Empty();//基类析构时已调用
}

void CUserLocalTextList::Copy(CUserLocalTextList* pList)
{
	int nCount = pList->GetCount();
	Empty();
	for(int i=0; i<nCount; i++)
	{
		CUserLocalText *pObject = pList->GetItem(i);
		CUserLocalText *pObjectBK = new CUserLocalText;
		pObjectBK->Copy(pObject);
		AddTail((CObject *)pObjectBK);
	}

}

void CUserLocalTextList::Serialize(CArchive& ar)
{
	//不需调用基类Serialize

	int nTagSize = 0;
	CString strName;
	int nNameSize;

	ar.Flush();
	if (ar.IsStoring())
	{
		MySerial.SaveDataObjectList(ar,_T("USERLIST"),this);

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
			return;

		while(strName != _T("DENDDEND"))
		{
			if(nNumber > 200)
			{
				return;
			}
			else if (strName == _T("USERLIST"))
			{
				Empty();
				int dateSize;
				ar >> nTagSize;
				ar >> dateSize;
				for(int i=0; i<dateSize; i++)
				{
					CObject  *pObject = new CUserLocalText;
					pObject->Serialize(ar);
					AddTail((CObject *)pObject);
				}
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
				return;
			nNumber++;
		}
	}
}

CUserLocalText*	CUserLocalTextList::GetItem(int nIndex)
{
	if (nIndex<0||nIndex>=GetCount())
		return NULL;

	return (CUserLocalText*)GetAt(FindIndex(nIndex));
}


void CUserLocalTextList::DeleteItem(int nIndex)
{
	if (nIndex<0||nIndex>GetCount())
		return;
	CUserLocalText *pObject=(CUserLocalText*)GetItem(nIndex);
	delete pObject;
	pObject = NULL;
	RemoveAt(FindIndex(nIndex));
}

void CUserLocalTextList::DeleteItem(int nDlgID,int nComboID)
{
	int nCount= GetCount()-1;

	for(int i=nCount; i>=0; i--)
	{
		CUserLocalText *pUserText = GetItem(i);
		if(pUserText->m_nDlgID==nDlgID&&pUserText->m_nCboID==nComboID)
			DeleteItem(i);
	}
}

int	CUserLocalTextList::FindTextSel(int nDlgID,int nComboID,CString strText)
{
	strText.Trim();
	int nSel = -1;
	for(int i=0; i<GetCount(); i++)
	{
		CUserLocalText *pUserText = GetItem(i);
		if(pUserText->m_nDlgID==nDlgID&&
			pUserText->m_nCboID==nComboID&&
			pUserText->m_strText==strText)
		{
			nSel = i;
			break;
		}
	}

	return nSel;
}

BOOL CUserLocalTextList::AddText(int nDlgID,int nComboID,CString strText)
{
	strText.Trim();
	ASSERT(!strText.IsEmpty());

	BOOL bRet = FALSE;
	//if (FindTextSel(nDlgID,nComboID,strText)>-1)
		//2017/4/26 19:08 wzl 添加错误
	if (-1 == FindTextSel(nDlgID,nComboID,strText))	
		//添加错误 end wzl
	{
		CUserLocalText *pUserText = new CUserLocalText;
		pUserText->m_nDlgID = nDlgID;
		pUserText->m_nCboID = nComboID;
		pUserText->m_strText = strText;

		AddHead(pUserText);

		bRet = TRUE;
	}

	return bRet;
}

void CUserLocalTextList::GetText(int nDlgID,int nComboID,CUserLocalTextList *pList)
{
	ASSERT(pList != NULL);

	pList->Empty();
	for(int i=0; i<GetCount(); i++)
	{
		CUserLocalText *pUserText = GetItem(i);
		if(pUserText->m_nDlgID==nDlgID&&pUserText->m_nCboID==nComboID)
		{
			pList->AddText(nDlgID,nComboID,pUserText->m_strText);
		}
	}
}

void CUserLocalTextList::UpdateText(int nDlgID,int nComboID,CUserLocalTextList *pList)
{
	DeleteItem(nDlgID,nComboID);
	ASSERT(pList != NULL);
	for(int i=0; i<pList->GetCount(); i++)
	{
		CUserLocalText *pUserText = pList->GetItem(i);
		if (NULL != pUserText)
		{
			AddText(pUserText->m_nDlgID,pUserText->m_nCboID,pUserText->m_strText);
		}
	}
}

CUserLocalTextList * CUserLocalTextList::Instance()
{
	if(sm_inst.get() == 0)
		sm_inst = shared_ptr<CUserLocalTextList>(new CUserLocalTextList);

	return sm_inst.get();
}