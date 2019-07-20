#include "StdAfx.h"
#include "MySerial.h"


CMySerial::CMySerial()
{
}


CMySerial::~CMySerial()
{
}

void CMySerial::SaveDataDouble(CArchive& ar,CString str,double data)
{
	int nNameSize = str.GetLength();
	int nTagSize = sizeof(data);
	ar << nNameSize;
	ar << str;
	ar << nTagSize;
	ar << data;
}

void CMySerial::SaveDataInt(CArchive& ar,CString str,int data)
{
	int nNameSize = str.GetLength();
	int nTagSize = sizeof(data);
	ar << nNameSize;
	ar << str;
	ar << nTagSize;
	ar << data;
}

void CMySerial::SaveDataInt64(CArchive& ar,CString str,__int64 date)
{
	int nNameSize = str.GetLength();
	int nTagSize = sizeof(date);
	ar << nNameSize;
	ar << str;
	ar << nTagSize;
	ar << date;
}

void CMySerial::SaveDataStr(CArchive& ar,CString str,CString data)
{
	int nNameSize = str.GetLength();
	int nTagSize = data.GetLength()+1;
	ar << nNameSize;
	ar << str;
	ar << nTagSize;
	ar << data;
}

void CMySerial::SaveDataFloat(CArchive& ar,CString str,float data)
{
	int nNameSize = str.GetLength();
	int nTagSize = sizeof(data);
	ar << nNameSize;
	ar << str;
	ar << nTagSize;
	ar << data;
}

void CMySerial::SaveDataObject(CArchive& ar,CString str,CObject* pObject)
{
	if(pObject == NULL)
		return;

	int nNameSize = 8;
	int nTagSize = 0;
	ar << nNameSize;
	ar << str;
	ar.Flush();
	ULONGLONG dwPosition = ar.GetFile()->GetPosition();
	ar << nTagSize;
	pObject->Serialize(ar);
	ar.Flush();
	ULONGLONG dwPosition1 = ar.GetFile()->GetPosition();
	nTagSize = int(dwPosition1-dwPosition);
	ar.GetFile()->Seek(-nTagSize, CFile::current);
	nTagSize -= sizeof(int);
	ar.GetFile()->Write(&nTagSize,sizeof(int));
	ar.GetFile()->Seek(nTagSize, CFile::current);
}

void CMySerial::SaveDataStrList(CArchive& ar,CString str,CObject* pObject)
{
	if(pObject == NULL)
		return;

	CStringList *pList = (CStringList *)pObject;
	int nDataSize = pList->GetCount();
	int nNameSize = 8;
	int nTagSize = 0;
	ar << nNameSize;
	ar << str;
	ar.Flush();
	ULONGLONG dwPosition = ar.GetFile()->GetPosition();
	ar << nTagSize;
	ar << nDataSize;
	for(int j=0;j<nDataSize;j++)
	{
		CString pObject=pList->GetAt(pList->FindIndex(j));
		ar << pObject;
	}
	ar.Flush();
	ULONGLONG dwPosition1 = ar.GetFile()->GetPosition();
	nTagSize = int(dwPosition1-dwPosition);
	ar.GetFile()->Seek(-nTagSize, CFile::current);
	nTagSize -= sizeof(int);
	ar.GetFile()->Write(&nTagSize,sizeof(int));
	ar.GetFile()->Seek(nTagSize, CFile::current);
}

void CMySerial::SaveDataObjectList(CArchive& ar,CString str,CObject* pObject)
{
	if(pObject == NULL)
		return;

	CObList *pList = (CObList *)pObject;
	int nDataSize = pList->GetCount();
	int nNameSize = 8;
	int nTagSize = 0;
	ar << nNameSize;
	ar << str;
	ar.Flush();
	ULONGLONG dwPosition = ar.GetFile()->GetPosition();
	ar << nTagSize;
	ar << nDataSize;
	for(int j=0;j<nDataSize;j++)
	{
		CObject* pObject=(CObject*)pList->GetAt(pList->FindIndex(j));
		pObject->Serialize(ar);
	}
	ar.Flush();
	ULONGLONG dwPosition1 = ar.GetFile()->GetPosition();
	nTagSize = int(dwPosition1-dwPosition);
	ar.GetFile()->Seek(-nTagSize, CFile::current);
	nTagSize -= sizeof(int);
	ar.GetFile()->Write(&nTagSize,sizeof(int));
	ar.GetFile()->Seek(nTagSize, CFile::current);
}

void CMySerial::SaveColeDateTime(CArchive& ar,CString str,COleDateTime& date)
{
	int namesize=str.GetLength();
	int tagsize=sizeof(date);
	ar << namesize;
	ar << str;
	ar << tagsize;
	ar << date;
}

void CMySerial::SaveDataRect(CArchive& ar,CString str,CRect& rc)
{
	int namesize=str.GetLength();
	int tagsize = sizeof(rc);
	ar << namesize;
	ar << str;
	ar << tagsize;
	ar << rc;
}

void CMySerial::SaveDataSize(CArchive& ar,CString str,CSize& sz)
{
	int namesize=str.GetLength();
	int tagsize = sizeof(sz);
	ar << namesize;
	ar << str;
	ar << tagsize;
	ar << sz;
}

void CMySerial::SaveDataPoint(CArchive& ar,CString str,CPoint& pt)
{
	int namesize=str.GetLength();
	int tagsize = sizeof(pt);
	ar << namesize;
	ar << str;
	ar << tagsize;
	ar << pt;
}

void CMySerial::SaveDataBuf(CArchive &ar, CString str, BYTE *pBuf, size_t nSize)
{
   if(pBuf == NULL)
      return;

   int nNameSize = 8;
   int nTagSize = nSize;
   ar << nNameSize;
   ar << str;
   ar.Flush();
   ULONGLONG dwPosition = ar.GetFile()->GetPosition();
   ar << nTagSize;
   ar.Flush();
   ar.GetFile()->Write(pBuf, nSize);

   ar.Flush();
}