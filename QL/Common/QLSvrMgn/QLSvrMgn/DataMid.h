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
#define DBS_GETDATESTR	_T("CONVERT(varchar(50), GETDATE(), 20)")			//��ʽ��yyyy-mm-dd hh:mm:ss
#define DBS_GETDATASTR_23	_T("CONVERT(varchar(50), GETDATE(),  23)")		//��ʽ��yyyy-mm-dd

typedef enum
{
   em_TYPE_WEIGHT_NONE,
   em_TYPE_WEIGHT_KG2JIN,
   em_TYPE_WEIGHT_JIN2KG
}EM_TYPE_WEIGHTCONVERT; //����ת��ö������ yangjr 2018/12/19


CString Func_GetWeightByJingDu(double dFinalWeight,int iNetWeightPointNum);


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
                  int nNum = -1);

   static void SetRowBackgroundColor(MAP_GridCtrl_RowData& row_data,COLORREF bkcolor);

   virtual vector<S_FieldCol_Data> CreateTitleData(){ vector<S_FieldCol_Data> oRetData;  return oRetData;};

   
#endif // USING_GRIDCTRL_MARK

   EM_TYPE_WEIGHTCONVERT GetWeightConvertInfo(__in CString strDBWeightUnit,__in CString strDlgWeightUnit);
   void ConvertWeight(__in EM_TYPE_WEIGHTCONVERT convertType,double &fValue);
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
						vector<CString> normalComboxData = vector<CString>());

   static void SetRowBackgroundColor(MAP_GridCtrl_RowData& row_data,COLORREF bkcolor);
#endif // USING_GRIDCTRL_MARK

private:
	int m_nDataListType;//��������
};
