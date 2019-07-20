#pragma once
/*************************************************
// <文件>: DataMid.h
// <说明>: DB数据类基类
// <作者>: yangjr
// <日期>: 2019/02/20 15:50:42
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
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
#define DBS_GETDATESTR	_T("CONVERT(varchar(50), GETDATE(), 20)")			//格式：yyyy-mm-dd hh:mm:ss
#define DBS_GETDATASTR_23	_T("CONVERT(varchar(50), GETDATE(),  23)")		//格式：yyyy-mm-dd



class CDataMid :public CObject
{
	DECLARE_SERIAL(CDataMid)
public:
	CDataMid();
	virtual ~CDataMid();



	/*
	 * @brief	数据重置
	 * @author	
	 */
	virtual void ResetData(){};

	/*
	 * @brief	序列化
	 * @author	
	 */
	virtual void Serialize(CArchive& ar);

	/*
	 * @brief	复制
	 * @author	
	 */
	virtual void Copy(CDataMid *pData);	


	/*
	 * @brief	设置当前数据类数据类型
	 * @author	
	 */
	void SetDataType(int nDataType);

	/*
	 * @brief	获取当前数据类数据类型
	 * @author	
	 */
	int GetDataType();


#ifdef USING_GRIDCTRL_MARK
	/*
	 * @brief	指定数据按固定格式插入表格行中
	 * @author	
	 */
	static void InsertRowData(CString strFiedID,MAP_GridCtrl_RowData& map_row_data,_In_z_ _FormatMessage_format_string_ LPCTSTR pszFormat,...);
	
	/*
	 * @brief	指定数据按固定格式插入表格行中
	 * @author	
	 */
	static void InsertRowData(CString strFiedID,MAP_GridCtrl_RowData& map_row_data,ENUM_FIELDTYPE_DATA nFieldType,ENUM_FIELDTYPE_CONTROL nFieldTypeCtr,_In_z_ _FormatMessage_format_string_ LPCTSTR pszFormat,...);
	
	/*
	 * @brief	指定数据按固定格式插入表格行中
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
	int m_nDataType;	//数据类型
};

class CDataListMid :public CObList
{
	DECLARE_SERIAL(CDataListMid)
public:
	CDataListMid();

	virtual ~CDataListMid();


	/*
	 * @brief	序列化
	 * @author	
	 */
	virtual void Serialize(CArchive& ar);

	/*
	 * @brief	清空链
	 * @author	
	 */
	void Empty();

	/*
	 * @brief	设置当前数据链类数据类型
	 * @author	
	 */
	void SetDataListType(int nDataListType);

	/*
	 * @brief	获取当前数据链类数据类型
	 * @author	
	 */
	int GetDataListType();

	/*
	 * @brief	将当前数据链类（内存）写磁盘文件
	 * @author	
	 */
	BOOL OnWriteFile(CString strFilePath);

	/*
	 * @brief	将磁盘文件读取到当前数据链类中（内存）
	 * @author	
	 */
	BOOL OnReadFile(CString strFilePath);

#ifdef USING_GRIDCTRL_MARK
	/*
	 * @brief	链中指定数据按固定格式插入表格行中
	 * @author	
	 */
	void InsertRowData(CString strFiedID,MAP_GridCtrl_RowData& map_row_data,_In_z_ _FormatMessage_format_string_ LPCTSTR pszFormat,...);
	
	/*
	 * @brief	链中指定数据按固定格式插入表格行中
	 * @author	
	 */
	void InsertRowData(CString strFiedID,MAP_GridCtrl_RowData& map_row_data,ENUM_FIELDTYPE_DATA nFieldType,ENUM_FIELDTYPE_CONTROL nFieldTypeCtr,_In_z_ _FormatMessage_format_string_ LPCTSTR pszFormat,...);
	
	/*
	 * @brief	链中指定数据按固定格式插入表格行中
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
	int m_nDataListType;//数据类型
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
   int m_nDataListType;//数据类型
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

