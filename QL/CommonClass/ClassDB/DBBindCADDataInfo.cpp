#include "StdAfx.h"
#include "DBBindCADDataInfo.h"

IMPLEMENT_SERIAL(CDBBindCADDataInfo,CDataMid,1)
IMPLEMENT_SERIAL(CDBBindCADList,CDataListMid,1)
CDBBindCADDataInfo::CDBBindCADDataInfo(void)
{
}


CDBBindCADDataInfo::~CDBBindCADDataInfo(void)
{
}

void CDBBindCADDataInfo::Serialize( CArchive& ar )
{
   	CDataMid::Serialize(ar);//父类函数

	int nTagSize = 0;
	CString strName;
	int nNameSize = 0;

	ar.Flush();
	if (ar.IsStoring())
	{
		MySerial.SaveDataStr(ar,_T("APP_PATH"),m_strAppPath);
      MySerial.SaveDataStr(ar,_T("APP_NAME"),m_strAppName);
      MySerial.SaveDataStr(ar,_T("FILE_HOU"),m_strFileSuffix);
      MySerial.SaveDataStr(ar,_T("FILETYPE"),m_strFileType);
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
			else if (strName == _T("APP_PATH"))
			{
				ar >> nTagSize >> m_strAppPath;
			}
			else if (strName == _T("APP_NAME"))
			{
				ar >> nTagSize >> m_strAppName;
			}
         else if (strName == _T("FILE_HOU"))
         {
            ar >> nTagSize >> m_strFileSuffix;
         }
         else if (strName == _T("FILETYPE"))
         {
            ar >> nTagSize >> m_strFileType;
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

void CDBBindCADDataInfo::Copy( CDBBindCADDataInfo *pData )
{
   ASSERT(pData!=NULL);
   CDataMid::Copy(pData);

   m_strAppPath = pData->m_strAppPath;
   m_strAppName = pData->m_strAppName;
   m_strFileSuffix = pData->m_strFileSuffix;
   m_strFileType = pData->m_strFileType;
}

CDBBindCADList::CDBBindCADList( void )
{

}

CDBBindCADList::~CDBBindCADList( void )
{

}


void CDBBindCADList::Serialize(CArchive& ar)
{
   //不需调用基类Serialize

   int nTagSize = 0;
   CString strName;
   int nNameSize;

   ar.Flush();
   if (ar.IsStoring())
   {
      MySerial.SaveDataObjectList(ar,_T("CAD_LIST"),this);

      nNameSize = 8;
      strName = _T("DENDDENG");
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

      while(strName != _T("DENDDENG"))
      {
         if(nNumber > 200)
         {
            return;
         }
         else if (strName == _T("CAD_LIST"))
         {
            Empty();
            int dateSize;
            ar >> nTagSize;
            ar >> dateSize;
            for(int i=0; i<dateSize; i++)
            {
               CDBBindCADDataInfo  *pObject = new CDBBindCADDataInfo;
               pObject->Serialize(ar);
               AddTail(pObject);
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

void CDBBindCADList::AddItem( CDBBindCADDataInfo *pItem )
{
   ASSERT(pItem!=NULL);
   CDBBindCADDataInfo *pData = new CDBBindCADDataInfo;
   pData->Copy(pItem);

   AddTail(pData);
}

BOOL CDBBindCADList::DeleteItemByPath( CString strPath )
{
   for (int nIndex = 0;nIndex<GetCount();nIndex++)
   {
      auto pAuto = GetItem(nIndex);
      if (pAuto !=NULL&&pAuto->m_strAppPath == strPath)
      {
         DeleteItem(nIndex);
         return TRUE;
      }
   }
   return FALSE;
}

int CDBBindCADList::IsHasBind( CString strPath )
{
   for (int nIndex = 0;nIndex<GetCount();nIndex++)
   {
      auto pAuto = GetItem(nIndex);
      if (pAuto !=NULL&&pAuto->m_strAppPath == strPath)
      {
         return nIndex;
      }
   }

   return -1;
}

CDBBindCADDataInfo* CDBBindCADList::GetItem( int nIndex )
{
   if (nIndex<0||nIndex>=GetCount())
      return NULL;
   return (CDBBindCADDataInfo*)GetAt(FindIndex(nIndex));
}

void CDBBindCADList::DeleteItem( int nIndex )
{
   if (nIndex<0||nIndex>GetCount())
      return;
   CDBBindCADDataInfo *pObject=(CDBBindCADDataInfo*)GetItem(nIndex);
   delete pObject;
   pObject=NULL;
   RemoveAt(FindIndex(nIndex));
}

#ifdef USING_GRIDCTRL_MARK

void CDBBindCADList::CreateGridData( MAP_GridCtrl_AllData &mapAllData )
{
   for (int nIndex =0;nIndex <GetCount();nIndex++)
   {
      MAP_GridCtrl_RowData rowData;
      auto pAuto = GetItem(nIndex);
      if (pAuto != NULL)
      {
          //主程序名称
          InsertRowData(_T("cAppName"),rowData,FORMAT_STRING,pAuto->m_strAppName);
          InsertRowData(_T("cAppPath"),rowData,FORMAT_STRING,pAuto->m_strAppPath);
          InsertRowData(_T("cFileSuffix"),rowData,FORMAT_STRING,pAuto->m_strFileSuffix);
          InsertRowData(_T("cFileType"),rowData,FORMAT_STRING,pAuto->m_strFileType);

          mapAllData.insert(make_pair(nIndex,rowData));
      }
   }
}

#endif // USING_GRIDCTRL_MARK
