#pragma once
/*************************************************
// <�ļ�>: DataMid.h
// <˵��>: DB���������
// <����>: yangjr
// <����>: 2019/02/20 15:50:42
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
#include "ADOConn/ADOConn.h"
#include "MySerial.h"
#include <memory>
#ifdef USING_GRIDCTRL_MARK
#include "CDataTableDlgDefine.h"
#include "CDataTableAttrFileAndFieldDefine.h"
#endif // USING_GRIDCTRL_MARK
using namespace std;
#include "DBDef.h"
#include "CFormatDefine.h"

#define DBS_GETDATE		_T("GetDate()")
#define DBS_GETDATESTR	_T("CONVERT(varchar(50), GETDATE(), 20)")			//��ʽ��yyyy-mm-dd hh:mm:ss
#define DBS_GETDATASTR_23	_T("CONVERT(varchar(50), GETDATE(),  23)")		//��ʽ��yyyy-mm-dd



class CDataMid :public CObject
{
	DECLARE_SERIAL(CDataMid)
public:
	CDataMid();
	virtual ~CDataMid();



	/*
	 * @brief	��������
	 * @author	
	 */
	virtual void ResetData(){};

	/*
	 * @brief	���л�
	 * @author	
	 */
	virtual void Serialize(CArchive& ar);

	/*
	 * @brief	����
	 * @author	
	 */
	virtual void Copy(CDataMid *pData);	


	/*
	 * @brief	���õ�ǰ��������������
	 * @author	
	 */
	void SetDataType(int nDataType);

	/*
	 * @brief	��ȡ��ǰ��������������
	 * @author	
	 */
	int GetDataType();


#ifdef USING_GRIDCTRL_MARK
	/*
	 * @brief	ָ�����ݰ��̶���ʽ����������
	 * @author	
	 */
	static void InsertRowData(CString strFiedID,MAP_GridCtrl_RowData& map_row_data,_In_z_ _FormatMessage_format_string_ LPCTSTR pszFormat,...);
	
	/*
	 * @brief	ָ�����ݰ��̶���ʽ����������
	 * @author	
	 */
	static void InsertRowData(CString strFiedID,MAP_GridCtrl_RowData& map_row_data,ENUM_FIELDTYPE_DATA nFieldType,ENUM_FIELDTYPE_CONTROL nFieldTypeCtr,_In_z_ _FormatMessage_format_string_ LPCTSTR pszFormat,...);
	
	/*
	 * @brief	ָ�����ݰ��̶���ʽ����������
	 * @author	
	 */
	static void InsertRowData(CString strFiedID,CString strValue,MAP_GridCtrl_RowData& map_row_data,
						ENUM_FIELDTYPE_DATA nFieldType= CB_enum_FieldData_CString,
						ENUM_FIELDTYPE_CONTROL nFieldTypeCtr= CB_enum_FieldCtrl_Text,
						vector<int> cellBackgroundClrVec = vector<int>(),
						vector<CString> normalComboxData = vector<CString>(),
                  int nNum = -1,CRuntimeClass * pRTI = NULL,UINT nIDRes = 0,
                  DWORD dwDefaultValue = 0);

   static void SetRowBackgroundColor(MAP_GridCtrl_RowData& row_data,COLORREF bkcolor);

   virtual vector<S_FieldCol_Data> CreateTitleData(){ vector<S_FieldCol_Data> oRetData;  return oRetData;};

   
#endif // USING_GRIDCTRL_MARK

private:
	int m_nDataType;	//��������
};

class CDataListMid :public CObList
{
	DECLARE_SERIAL(CDataListMid)
public:
	CDataListMid();

	virtual ~CDataListMid();


	/*
	 * @brief	���л�
	 * @author	
	 */
	virtual void Serialize(CArchive& ar);

	/*
	 * @brief	�����
	 * @author	
	 */
	void Empty();

	/*
	 * @brief	���õ�ǰ����������������
	 * @author	
	 */
	void SetDataListType(int nDataListType);

	/*
	 * @brief	��ȡ��ǰ����������������
	 * @author	
	 */
	int GetDataListType();

	/*
	 * @brief	����ǰ�������ࣨ�ڴ棩д�����ļ�
	 * @author	
	 */
	BOOL OnWriteFile(CString strFilePath);

	/*
	 * @brief	�������ļ���ȡ����ǰ���������У��ڴ棩
	 * @author	
	 */
	BOOL OnReadFile(CString strFilePath);

#ifdef USING_GRIDCTRL_MARK
	/*
	 * @brief	����ָ�����ݰ��̶���ʽ����������
	 * @author	
	 */
	void InsertRowData(CString strFiedID,MAP_GridCtrl_RowData& map_row_data,_In_z_ _FormatMessage_format_string_ LPCTSTR pszFormat,...);
	
	/*
	 * @brief	����ָ�����ݰ��̶���ʽ����������
	 * @author	
	 */
	void InsertRowData(CString strFiedID,MAP_GridCtrl_RowData& map_row_data,ENUM_FIELDTYPE_DATA nFieldType,ENUM_FIELDTYPE_CONTROL nFieldTypeCtr,_In_z_ _FormatMessage_format_string_ LPCTSTR pszFormat,...);
	
	/*
	 * @brief	����ָ�����ݰ��̶���ʽ����������
	 * @author	
	 */
	void InsertRowData(CString strFiedID,CString strValue,MAP_GridCtrl_RowData& map_row_data,
						ENUM_FIELDTYPE_DATA nFieldType= CB_enum_FieldData_CString,
						ENUM_FIELDTYPE_CONTROL nFieldTypeCtr= CB_enum_FieldCtrl_Text,
						vector<int> cellBackgroundClrVec = vector<int>(),
                  vector<CString> normalComboxData = vector<CString>(),
                  int nNum = -1,CRuntimeClass * pRTI = NULL,UINT nIDRes = 0,
                  DWORD dwDefaultValue = 0);

   static void SetRowBackgroundColor(MAP_GridCtrl_RowData& row_data,COLORREF bkcolor);
#endif // USING_GRIDCTRL_MARK

private:
	int m_nDataListType;//��������
};

class CTObList : public CObList
{
public:
   CTObList(){m_nDataListType = -1;}
   ~CTObList(){Empty();}
   void SetDataListType(int nDataListType)
   {m_nDataListType = nDataListType;}

   int GetDataListType() {return m_nDataListType;}

   void Empty();

   BOOL OnWriteFile(CString strFilePath);

   BOOL OnReadFile(CString strFilePath);

#ifdef USING_GRIDCTRL_MARK
   void InsertRowData(CString strFiedID,MAP_GridCtrl_RowData& map_row_data,_In_z_ _FormatMessage_format_string_ LPCTSTR pszFormat,...);

   void InsertRowData(CString strFiedID,MAP_GridCtrl_RowData& map_row_data,ENUM_FIELDTYPE_DATA nFieldType,ENUM_FIELDTYPE_CONTROL nFieldTypeCtr,_In_z_ _FormatMessage_format_string_ LPCTSTR pszFormat,...);

   void InsertRowData(CString strFiedID,CString strValue,MAP_GridCtrl_RowData& map_row_data,
      ENUM_FIELDTYPE_DATA nFieldType= CB_enum_FieldData_CString,
      ENUM_FIELDTYPE_CONTROL nFieldTypeCtr= CB_enum_FieldCtrl_Text,
      vector<int> cellBackgroundClrVec = vector<int>(),
      vector<CString> normalComboxData = vector<CString>(),
      int nNum = -1,CRuntimeClass * pRTI = NULL,UINT nIDRes = 0,
      DWORD dwDefaultValue = 0);

   static void SetRowBackgroundColor(MAP_GridCtrl_RowData& row_data,COLORREF bkcolor);
#endif // USING_GRIDCTRL_MARK
private:
   int m_nDataListType;//��������
};


template <class T,typename DATA_TYPE>
class CTDataListMid :public CTObList
{
public:
   CTDataListMid(){}

   virtual ~CTDataListMid(){}
   void Copy(T *pList);
   DATA_TYPE*  GetItem(int nIndex);
   void    AddItem(DATA_TYPE* pItem);
   void    DeleteItem(int nIndex);

};

template <class T,typename DATA_TYPE>
void CTDataListMid<T, DATA_TYPE>::Copy(T *pList)
{
   Empty();
   if (pList != NULL)
   {
      for (int nIndex = 0;nIndex < pList->GetCount();nIndex++)
      {
         DATA_TYPE *pData =(DATA_TYPE *)pList->GetAt(pList->FindIndex(nIndex));
         if (pData != NULL)
         {
            AddItem(pData);
         }
      }
   }
}

template <class T,typename DATA_TYPE>
void CTDataListMid<T,DATA_TYPE>::DeleteItem(int nIndex)
{
   if (nIndex<0||nIndex>GetCount())
      return;
   DATA_TYPE *pObject=(DATA_TYPE*)GetItem(nIndex);
   delete pObject;
   pObject=NULL;
   RemoveAt(FindIndex(nIndex));
}

template <class T,typename DATA_TYPE>
void CTDataListMid<T,DATA_TYPE>::AddItem(DATA_TYPE* pItem)
{
   DATA_TYPE*pData=new DATA_TYPE;
   pData->Copy(pItem);
   AddTail(pData);
}

template <class T,typename DATA_TYPE>
DATA_TYPE* CTDataListMid<T,DATA_TYPE>::GetItem(int nIndex)
{
   if (nIndex<0||nIndex>=GetCount())
      return NULL;
   return (DATA_TYPE*)GetAt(FindIndex(nIndex));
}

