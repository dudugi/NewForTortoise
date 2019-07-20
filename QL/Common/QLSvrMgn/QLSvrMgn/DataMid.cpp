#include "StdAfx.h"
#include "DataMid.h"

#include "MySerial.h"

CString Func_GetWeightByJingDu(double dFinalWeight,int iNetWeightPointNum)
{
   CString strTemp;
   if (iNetWeightPointNum<1|| iNetWeightPointNum>4)
   {
      iNetWeightPointNum = 4;
   }  

   if (iNetWeightPointNum!=4)
   {
      double fAddValue = 0.5;
      for (int i=0;i<iNetWeightPointNum;++i)
      {
         fAddValue /= 10;
      } 
      dFinalWeight += fAddValue;
      CString strFormat;
      strFormat.Format(_T("%d"),iNetWeightPointNum);

      strTemp.Format(_T("%.")+strFormat+_T("f"),dFinalWeight);
      strTemp.Format(_T("%.4f"),_ttof(strTemp));
   }else
   {
      strTemp.Format(_T("%.4f"),dFinalWeight);
   }   
   return strTemp;
};
//CDataMid
IMPLEMENT_SERIAL(CDataMid,CObject,1)
CDataMid::CDataMid()
{
	m_nDataType = -1;
}


CDataMid::~CDataMid()
{

}

void CDataMid::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);//父类函数

	int nTagSize = 0;
	CString strName = _T("");
	int nNameSize = 0;

	ar.Flush();
	if (ar.IsStoring())
	{
		MySerial.SaveDataInt(ar,_T("DTAMIDTP"),m_nDataType);

		nNameSize = 8;
		strName = _T("DENDDEND");
		ar << nNameSize;
		ar << strName;
	}
	else
	{
		int nNumber=0;
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
			if (strName == _T("DTAMIDTP"))
			{
				ar >>nTagSize >> m_nDataType;
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

void CDataMid::Copy(CDataMid *pData)
{
	ASSERT(pData != NULL);

	m_nDataType = pData->m_nDataType;
}

void CDataMid::SetDataType(int nDataType)
{
	m_nDataType = nDataType;
}

int CDataMid::GetDataType()
{
	return m_nDataType;
}

#ifdef USING_GRIDCTRL_MARK
void CDataMid::InsertRowData( CString strFiedID,MAP_GridCtrl_RowData& map_row_data,_In_z_ _FormatMessage_format_string_ LPCTSTR pszFormat,... )
{
	CString strContent = _T("");
	va_list argList;
	va_start( argList, pszFormat );
	strContent.FormatV(pszFormat,argList);

	va_end( argList );

	InsertRowData(strFiedID,strContent,map_row_data);
}

void CDataMid::InsertRowData( CString strFiedID,MAP_GridCtrl_RowData& map_row_data,ENUM_FIELDTYPE_DATA nFieldType,ENUM_FIELDTYPE_CONTROL nFieldTypeCtr,_In_z_ _FormatMessage_format_string_ LPCTSTR pszFormat,... )
{
	CString strContent = _T("");
	va_list argList;
	va_start( argList, pszFormat );
	strContent.FormatV(pszFormat,argList);

	va_end( argList );
	InsertRowData(strFiedID,strContent,map_row_data,nFieldType,nFieldTypeCtr);
}

void CDataMid::InsertRowData( CString strFiedID,CString strValue,MAP_GridCtrl_RowData& map_row_data,
								ENUM_FIELDTYPE_DATA nFieldType/*= enum_FieldData_CString*/,
								ENUM_FIELDTYPE_CONTROL nFieldTypeCtr/*= enum_FieldCtrl_Text*/,
								vector<int> cellBackgroundClrVec /*= vector<int>()*/,
                        vector<CString> normalComboxData /*= vector<CString>()*/,
                        int nNum /*=-1*/)
{
	S_GridCtrl_FieldData s_data;
	s_data.strValue = strValue;
	s_data.fieldDataType = nFieldType;
	s_data.fieldCtrlType = nFieldTypeCtr;
   s_data.nNum = nNum; 
   if (cellBackgroundClrVec.size()>0)
	{
		shared_ptr<vector<int>> sptr_bgd(new vector<int>);
		*sptr_bgd = cellBackgroundClrVec;
		s_data.sptr_cellBackgroundClrVec = sptr_bgd;
	}

	if (normalComboxData.size()>0)
	{
		shared_ptr<vector<CString>> sptr_comboData(new(vector<CString>));
		*sptr_comboData = normalComboxData;
		s_data.sptr_normalComboxData = sptr_comboData;
	}

	map_row_data.insert(make_pair(strFiedID,s_data));
}

void CDataMid::SetRowBackgroundColor(MAP_GridCtrl_RowData& row_data,COLORREF bkcolor)
{
   for (auto itr_col = row_data.begin(); itr_col != row_data.end(); ++itr_col)
   {
      if (nullptr == itr_col->second.sptr_cellBackgroundClrVec)
      {
         itr_col->second.sptr_cellBackgroundClrVec = shared_ptr<vector<int>>(new(vector<int>));
      }
      else
      {
         itr_col->second.sptr_cellBackgroundClrVec->clear();
      }
      itr_col->second.sptr_cellBackgroundClrVec->push_back(bkcolor);//背景色数据
   }
}

#endif // USING_GRIDCTRL_MARK

EM_TYPE_WEIGHTCONVERT CDataMid::GetWeightConvertInfo( __in CString strDBWeightUnit,__in CString strDlgWeightUnit)
{
   if (strDBWeightUnit == strDlgWeightUnit)
   {
      return em_TYPE_WEIGHT_NONE;
   }
   if (strDBWeightUnit == _T("斤") && strDlgWeightUnit == _T("千克(kg)"))
   {
      return em_TYPE_WEIGHT_JIN2KG;
   }
   if (strDBWeightUnit == _T("千克(kg)") && strDlgWeightUnit == _T("斤"))
   {
      return em_TYPE_WEIGHT_KG2JIN;
   }
   return em_TYPE_WEIGHT_NONE;
}

void CDataMid::ConvertWeight( __in EM_TYPE_WEIGHTCONVERT convertType,double &fValue)
{
   if (em_TYPE_WEIGHT_JIN2KG == convertType)
   {
      fValue /=2; 
   }else if (em_TYPE_WEIGHT_KG2JIN == convertType)
   {
      fValue *=2; 
   }
}


//
IMPLEMENT_SERIAL(CDataListMid,CObList,1)
CDataListMid::CDataListMid()
{
	m_nDataListType = -1;
}


CDataListMid::~CDataListMid()
{
	Empty();
}

void CDataListMid::Serialize(CArchive& ar)
{
	CObList::Serialize(ar);//父类函数

	//...
}

void CDataListMid::Empty()
{
	for (int j=(GetCount()-1);j>=0;j--)
	{
		CObject *pData =(CObject *)GetAt(FindIndex(j));
		if (pData)
		{
			delete pData;
			pData = NULL;
		}
	}

	RemoveAll();
}

void CDataListMid::SetDataListType(int nDataListType)
{
	m_nDataListType = nDataListType;
}

int CDataListMid::GetDataListType()
{
	return m_nDataListType;
}

BOOL CDataListMid::OnWriteFile(CString strFilePath)
{
	BOOL bRet = TRUE;

	if (strFilePath.IsEmpty()||this == NULL)
	{
		bRet = FALSE;
	}
	else
	{
		//SetFileAttributes(strFilePath,FILE_ATTRIBUTE_NORMAL);//恢复文件一般属性
		//写
		CFile mFile;	
		try
		{
			if (mFile.Open (strFilePath,CFile::modeCreate|CFile::modeWrite|CFile::shareExclusive))
			{
				CArchive saveArchive(&mFile, CArchive::store);
				this->Serialize(saveArchive);
				saveArchive.Close();
				mFile.Close();
			}
			else
			{
				bRet = FALSE;
			}
		}
		catch( CException* e )
		{
			TCHAR szError[1024];
			CString strError = _T("");
			e->GetErrorMessage(szError,1024);
			strError.Format(_T("%s"),szError);
			AfxMessageBox(strFilePath+_T("  写文件出现问题：")+ strError);
		}//写_end

		//SetFileAttributes(strFilePath,FILE_ATTRIBUTE_HIDDEN);//设置文件属性：隐藏
	}

	return bRet;
}

BOOL CDataListMid::OnReadFile(CString strFilePath)
{
	BOOL bRet = TRUE;

	if (strFilePath.IsEmpty()||this == NULL)
	{
		bRet = FALSE;
	}
	else
	{
		//读
		CFile mFile;
		try
		{
			if(mFile.Open(strFilePath,CFile::modeRead))
			{
				this->Empty();
				CArchive loadArchive(&mFile, CArchive::load);
				loadArchive.m_bForceFlat = FALSE;
				if (mFile.GetLength() != 0)
				{
					this->Serialize(loadArchive);
					loadArchive.Close();
				}
				mFile.Close();		
			}
			else
			{
				bRet = FALSE;
			}
		}
		catch( CException* e )
		{
			TCHAR szError[1024];
			CString strError = _T("");
			e->GetErrorMessage(szError,1024);
			strError.Format(_T("%s"),szError);
			AfxMessageBox(strFilePath+_T("  写文件出现问题：")+ strError);
		}//读_end
	}

	return bRet;
}

#ifdef USING_GRIDCTRL_MARK
void CDataListMid::InsertRowData( CString strFiedID,MAP_GridCtrl_RowData& map_row_data,_In_z_ _FormatMessage_format_string_ LPCTSTR pszFormat,... )
{
	CString strContent = _T("");
	va_list argList;
	va_start( argList, pszFormat );
	strContent.FormatV(pszFormat,argList);

	va_end( argList );

	InsertRowData(strFiedID,strContent,map_row_data);
}

void CDataListMid::InsertRowData( CString strFiedID,MAP_GridCtrl_RowData& map_row_data,ENUM_FIELDTYPE_DATA nFieldType,ENUM_FIELDTYPE_CONTROL nFieldTypeCtr,_In_z_ _FormatMessage_format_string_ LPCTSTR pszFormat,... )
{
	CString strContent = _T("");
	va_list argList;
	va_start( argList, pszFormat );
	strContent.FormatV(pszFormat,argList);

	va_end( argList );
	InsertRowData(strFiedID,strContent,map_row_data,nFieldType,nFieldTypeCtr);
}

void CDataListMid::InsertRowData( CString strFiedID,CString strValue,MAP_GridCtrl_RowData& map_row_data,ENUM_FIELDTYPE_DATA nFieldType/*= enum_FieldData_CString*/,
									ENUM_FIELDTYPE_CONTROL nFieldTypeCtr/*= enum_FieldCtrl_Text*/,
									vector<int> cellBackgroundClrVec/* = vector<int>()*/,
									vector<CString> normalComboxData /*= vector<CString>()*/)
{
	S_GridCtrl_FieldData s_data;
	s_data.strValue = strValue;
	s_data.fieldDataType = nFieldType;
	s_data.fieldCtrlType = nFieldTypeCtr;

	if (cellBackgroundClrVec.size()>0)
	{
		shared_ptr<vector<int>> sptr_bgd(new vector<int>);
		*sptr_bgd = cellBackgroundClrVec;
		s_data.sptr_cellBackgroundClrVec = sptr_bgd;
	}

	if (normalComboxData.size()>0)
	{
		shared_ptr<vector<CString>> sptr_comboData(new(vector<CString>));
		*sptr_comboData = normalComboxData;
		s_data.sptr_normalComboxData = sptr_comboData;
	}
	map_row_data.insert(make_pair(strFiedID,s_data));
}

void CDataListMid::SetRowBackgroundColor(MAP_GridCtrl_RowData& row_data,COLORREF bkcolor)
{
   for (auto itr_col = row_data.begin(); itr_col != row_data.end(); ++itr_col)
   {
      if (nullptr == itr_col->second.sptr_cellBackgroundClrVec)
      {
         itr_col->second.sptr_cellBackgroundClrVec = shared_ptr<vector<int>>(new(vector<int>));
      }
      else
      {
         itr_col->second.sptr_cellBackgroundClrVec->clear();
      }
      itr_col->second.sptr_cellBackgroundClrVec->push_back(bkcolor);//背景色数据
   }
}

#endif // USING_GRIDCTRL_MARK
