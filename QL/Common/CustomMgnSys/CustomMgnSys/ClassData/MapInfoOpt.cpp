#include "StdAfx.h"
#include "MapInfoOpt.h"




CMapInfoOpt::CMapInfoOpt(void)
{
}


CMapInfoOpt::~CMapInfoOpt(void)
{
}

void CMapInfoOpt::InsertRowData(CString strFiedID,CString strValue, MAP_GridCtrl_RowData& map_row_data,ENUM_FIELDTYPE_DATA nFieldType/*= CB_enum_FieldData_CString*/, ENUM_FIELDTYPE_CONTROL nFieldTypeCtr/*= CB_enum_FieldCtrl_Text*/)
{
   S_GridCtrl_FieldData s_data;		//¶©µ¥×´Ì¬
   s_data.strValue = strValue;
   s_data.fieldDataType = nFieldType;
   s_data.fieldCtrlType = nFieldTypeCtr;
   map_row_data.insert(make_pair(strFiedID,s_data));
}

