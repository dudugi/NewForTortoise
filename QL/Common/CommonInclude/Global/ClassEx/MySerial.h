#pragma once
/*************************************************
// <文件>: MySerial.h
// <说明>: 序列化的接口
// <作者>: wangzl
// <日期>: 2019/02/22
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 
class CMySerial
{
public:
	CMySerial();
	virtual ~CMySerial();

	void	SaveDataDouble(CArchive& ar,CString str,double data);
	void	SaveDataInt(CArchive& ar,CString str,int data);
	void	SaveDataInt64(CArchive& ar,CString str,__int64 date);
	void	SaveDataStr(CArchive& ar,CString str,CString data);
	void	SaveDataFloat(CArchive& ar,CString str,float data);
	void	SaveDataObject(CArchive& ar,CString str,CObject* pObject);
	void	SaveDataStrList(CArchive& ar,CString str,CObject* pObject);
	void	SaveDataObjectList(CArchive& ar,CString str,CObject* pObject);

	void	SaveColeDateTime(CArchive& ar,CString str,COleDateTime& date);
	void	SaveDataRect(CArchive& ar,CString str,CRect& rc);
	void	SaveDataSize(CArchive& ar,CString str,CSize& sz);
	void	SaveDataPoint(CArchive& ar,CString str,CPoint& pt);

   template<typename FwdIt>
   void              SaveSerializeList(CArchive& ar, CString str, FwdIt begin, FwdIt end);

   void SaveDataBuf(CArchive &ar, CString str, BYTE *pBuf, size_t nSize);
};

template<typename FwdIt>
void CMySerial::SaveSerializeList(CArchive& ar, CString str, FwdIt begin, FwdIt end)
{
   int dateSize = std::distance(begin, end);
   int namesize = str.GetLength();
   int tagsize = 0;
   ar << namesize;
   CString strname = str;
   ar << strname;
   ar.Flush();
   ULONGLONG dwPosition = ar.GetFile()->GetPosition();
   ar << tagsize;
   ar << dateSize;
   for(FwdIt it = begin;it != end; ++it)
   {
      it->Serialize(ar);
   }
   ar.Flush();
   ULONGLONG dwPosition1 = ar.GetFile()->GetPosition();
   tagsize=int(dwPosition1-dwPosition);
   ar.GetFile()->Seek( -tagsize, CFile::current);
   tagsize-=sizeof(int);
   ar.GetFile()->Write(&tagsize,sizeof(int));
   ar.GetFile()->Flush();
   ar.GetFile()->Seek( tagsize, CFile::current);
}

extern CMySerial MySerial;
