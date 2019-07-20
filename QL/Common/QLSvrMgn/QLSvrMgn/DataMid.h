#pragma once
#include "ADOConn/ADOConn.h"
#include "MySerial.h"
#include <memory>
#ifdef USING_GRIDCTRL_MARK
#include "CDataTableDlgDefine.h"
#endif // USING_GRIDCTRL_MARK
using namespace std;
#include "DBDef.h"


#define DBS_GETDATE		_T("GetDate()")
#define DBS_GETDATESTR	_T("CONVERT(varchar(50), GETDATE(), 20)")			//格式：yyyy-mm-dd hh:mm:ss
#define DBS_GETDATASTR_23	_T("CONVERT(varchar(50), GETDATE(),  23)")		//格式：yyyy-mm-dd

typedef enum
{
   em_TYPE_WEIGHT_NONE,
   em_TYPE_WEIGHT_KG2JIN,
   em_TYPE_WEIGHT_JIN2KG
}EM_TYPE_WEIGHTCONVERT; //重量转换枚举类型 yangjr 2018/12/19


CString Func_GetWeightByJingDu(double dFinalWeight,int iNetWeightPointNum);


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
                  int nNum = -1);

   static void SetRowBackgroundColor(MAP_GridCtrl_RowData& row_data,COLORREF bkcolor);

   virtual vector<S_FieldCol_Data> CreateTitleData(){ vector<S_FieldCol_Data> oRetData;  return oRetData;};

   
#endif // USING_GRIDCTRL_MARK

   EM_TYPE_WEIGHTCONVERT GetWeightConvertInfo(__in CString strDBWeightUnit,__in CString strDlgWeightUnit);
   void ConvertWeight(__in EM_TYPE_WEIGHTCONVERT convertType,double &fValue);
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
						vector<CString> normalComboxData = vector<CString>());

   static void SetRowBackgroundColor(MAP_GridCtrl_RowData& row_data,COLORREF bkcolor);
#endif // USING_GRIDCTRL_MARK

private:
	int m_nDataListType;//数据类型
};
