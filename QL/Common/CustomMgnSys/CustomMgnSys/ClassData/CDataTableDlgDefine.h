#pragma once
#include <map>
#include <vector>

/*
表格相关数据定义头文件 yangjr 2017-6-2
*/

using namespace std;

const BYTE CB_GRIDCTRL_DEFAULT_FONT = 11; //表格控件默认字体大小
const BYTE CB_GRIDCTRL_DEFAULT_ROWHEIGHT = 24; //表格控件默认行高
const CString CS_GRIDCTRL_DEFAULT_DATAFORMAT = _T("%Y-%m-%d");		//表格控件时间默认格式化

//字段数据类型
#pragma region 字段数据类型

typedef BYTE ENUM_FIELDTYPE_DATA;
const ENUM_FIELDTYPE_DATA CB_enum_FieldData_CString = 0;							//字符串
const ENUM_FIELDTYPE_DATA CB_enum_FieldData_Int = 1;								//整形
const ENUM_FIELDTYPE_DATA CB_enum_FieldData_Double2Point = 2;						//浮点数2位小数
const ENUM_FIELDTYPE_DATA CB_enum_FieldData_Double3Point = 3;						//浮点数3位小数
const ENUM_FIELDTYPE_DATA CB_enum_FieldData_Double4Point = 4;						//浮点数4位小数
const ENUM_FIELDTYPE_DATA CB_enum_FieldData_Time = CB_enum_FieldData_CString;		//时间wangzl 2017-7-15
const ENUM_FIELDTYPE_DATA CB_enum_FieldData_TimeLong = CB_enum_FieldData_CString;	//时长wangzl 2017-11-10
const ENUM_FIELDTYPE_DATA CB_enum_FieldData_Button = 6;							//按钮的文字
const ENUM_FIELDTYPE_DATA CB_enum_FieldData_BallColor = 7;                 //色块的信息
#pragma endregion 字段数据类型


//字段控件类型
#pragma region 字段控件类型

typedef BYTE ENUM_FIELDTYPE_CONTROL;
const ENUM_FIELDTYPE_CONTROL CB_enum_FieldCtrl_Text = 0;							//文本
const ENUM_FIELDTYPE_CONTROL CB_enum_FieldCtrl_Checkbox = 1;						//复选框
const ENUM_FIELDTYPE_CONTROL CB_enum_FieldCtrl_NormalCombox = 2;					//普通下拉框控件
const ENUM_FIELDTYPE_CONTROL CB_enum_FieldCtrl_SpecialCombox = 3;					//特殊下拉框控件 下拉为gridctrl
const ENUM_FIELDTYPE_CONTROL CB_enum_FieldCtrl_Radio = 4;							//单选控件 一个表格某个字段只能一行选中时使用 yangjr 2017-6-9
const ENUM_FIELDTYPE_CONTROL CB_enum_FieldCtrl_EditCombox = 5;						//普通可编辑下拉框控件
const ENUM_FIELDTYPE_CONTROL CB_enum_FieldCtrl_DateTime = CB_enum_FieldCtrl_Text;	//时间控件wangzl 2017-7-15
const ENUM_FIELDTYPE_CONTROL CB_enum_FieldCtrl_TimeLong = CB_enum_FieldCtrl_Text;	//时长控件wangzl 2017-11-10
const ENUM_FIELDTYPE_CONTROL CB_enum_FieldCtrl_Button = 6;									//按钮控件		by WangZY 2017/11/21
const ENUM_FIELDTYPE_CONTROL CB_enum_FieldCtrl_BallColor = 7;								//显示两个颜色球的控件      by wangzl 2018/7/23

#pragma endregion 字段控件类型


#pragma region 数据定义
//一个字段数据定义
typedef struct tag_GridCtrl_FieldData
{
	tag_GridCtrl_FieldData()
	{
		strValue = _T("");
		fieldDataType = CB_enum_FieldData_CString;
		fieldCtrlType = CB_enum_FieldCtrl_Text;
		//sptr_normalComboxData->clear();
		//normalComboxData.clear();
		//cellBackgroundClrVec.clear();
		//sptr_cellBackgroundClrVec->clear();
		//sptr_cellBackgroundClrVec.reset();
		byteProgress = 255;	//255为默认不使用,范围0到100为有效值	by WangZY 2017/08/23
	}

   //当控件类型为 CB_enum_FieldCtrl_BallColor 时 被用作不同色块的文本(一般支持两个字符)
	shared_ptr<std::vector<CString>> sptr_normalComboxData;//普通下拉框控件用到的数据
   //当控件类型为 CB_enum_FieldCtrl_BallColor 时 第二个和第三个数据分别被用作相两个颜色的数值
	shared_ptr<std::vector<int>> sptr_cellBackgroundClrVec;//字段单元格背景颜色 vector为空使用内部默认颜色 yangjr 2017-6-13
	//MAP_GridCtrl_AllData specialComboxData;//特殊下拉框控件用到的数据
	CString strValue; //数据值
	int nNum;
	ENUM_FIELDTYPE_DATA fieldDataType;//字段数据类型
	ENUM_FIELDTYPE_CONTROL fieldCtrlType;//字段控件类型
	BYTE	byteProgress;	//背景颜色的宽度比率,255为默认不使用,范围0到100为有效值		by WangZY 2017/08/23

}S_GridCtrl_FieldData;

//表格一行数据定义
typedef std::map<CString/*strColID 列名称ID*/,S_GridCtrl_FieldData/*列数据*/> MAP_GridCtrl_RowData;

//表格所有行数据定义
typedef std::map<int/*行号*/,MAP_GridCtrl_RowData/*表格一行数据*/> MAP_GridCtrl_AllData;

#pragma endregion 数据定义


/************************表格内部使用数据 begin*********************************/

#pragma region 合计方式(统计类型)

typedef BYTE ENUM_COLSUMTYPE;		//合计方式
const ENUM_COLSUMTYPE CB_enum_ColSumType_None = 0;		//无
const ENUM_COLSUMTYPE CB_enum_ColSumType_Sum = 1;		//求和
const ENUM_COLSUMTYPE CB_enum_ColSumType_Count = 2;	//计数
const ENUM_COLSUMTYPE CB_enum_ColSumType_Average = 3;	//求平均值

#pragma endregion 合计方式(统计类型)

#pragma region 检索类型

typedef BYTE ENUM_COLSERCHTYPE;
const ENUM_COLSERCHTYPE	CB_enum_ColSerchType_Contain = 0;			//包含
const ENUM_COLSERCHTYPE	CB_enum_ColSerchType_Equal = 1;				//相等

#pragma endregion 检索类型


#pragma region 字段属性

//gridctrl 字段属性
typedef struct tag_GridCtrl_FieldAtrri 
{
	CString strColID; //列名称
	CString strColShowName;//显示名称
	CString strColFormat;//格式化

	short iColWidth;//宽度
	short iColIndex;//当前字段在表格中显示在第几列 

	BYTE iColFont;//字体大小
	bool IsFontWeight;//字体是否加粗
	bool isEnableFilter;//当前字段是否允许筛选
	bool isShow;//是否显示

	bool isEdit;//是否编辑
	BYTE iLock;//锁定 0不锁定 1锁定左侧 2锁定右侧
	ENUM_COLSUMTYPE enColSumType;//合计方式 0无 1求和 2计数 3求平均值
	ENUM_COLSERCHTYPE enSerchType;//检索方式 0包含 1相等

   CString strColDestribution;//字段说明（程序员给出的中文描述） wangzl
   CString strTableID;//字段是在哪张表中 yangjr 2018/2/27
	tag_GridCtrl_FieldAtrri()
	{
		strColID = _T(""); //列名称
		strColShowName = _T("");//显示名称
		iColWidth = 75;//宽度
		isShow = true;//是否显示
		isEdit = true;//是否编辑
		iLock = 0;//锁定 0不锁定 1锁定左侧
		strColFormat = _T("");//格式化
		enColSumType = CB_enum_ColSumType_None;//合计方式 0无
		enSerchType = CB_enum_ColSerchType_Contain;//检索方式 0
		iColFont = CB_GRIDCTRL_DEFAULT_FONT;//字体大小
		IsFontWeight = false;//字体是否加粗
		iColIndex = -1;//当前字段在表格中显示在第几
		isEnableFilter = true;//当前字段是否允许筛选
      strColDestribution = _T("");
      strTableID = _T("");//字段是在哪张表中 yangjr 2018/2/27
	}

	tag_GridCtrl_FieldAtrri(CString strColID_In,short iColIndex_In,CString strColShowName_In = _T(""),
		bool isShow_In = true,bool isEdit_In = true,short iColWidth_In = 75,
		bool isEnableFilter_In = true,BYTE iLock_In = 0,ENUM_COLSUMTYPE enColSumType_In = CB_enum_ColSumType_None,
		BYTE iColFont_In = CB_GRIDCTRL_DEFAULT_FONT, bool IsFontWeight_In = false,
		ENUM_COLSERCHTYPE enSerchType_In = CB_enum_ColSerchType_Contain,CString strColFormat_In=_T(""),CString strColDestribution_In = _T("")
      ,CString strTableID_In = _T(""))
	{
		strColID = strColID_In; //列名称 
		iColIndex = iColIndex_In;//当前字段在表格中显示在第几
		strColShowName = strColShowName_In;//显示名称
		isShow = isShow_In;//是否显示
		isEdit = isEdit_In;//是否编辑
		iColWidth = iColWidth_In;//宽度
		isEnableFilter = isEnableFilter_In;//当前字段是否允许筛选
		iLock = iLock_In;//锁定 0不锁定 1锁定左侧 2锁定右边
		enColSumType = enColSumType_In;
		IsFontWeight = IsFontWeight_In;//字体是否加粗
		iColFont = iColFont_In;//字体大小
		enSerchType = enSerchType_In;//检索方式 0
		strColFormat = strColFormat_In;//格式化
      strColDestribution = strColDestribution_In;
      strTableID = strTableID_In;//字段是在哪张表中 yangjr 2018/2/27
	}   
}S_GridCtrl_FieldAtrri;

#pragma endregion 字段属性

#pragma region 字段及其对应的示例

//wangzl 2017-1-2 字段列对应信息
typedef struct tag_FieldCol_Data
{
   CString strColID; //列名称
   CString strColDestribution;//字段说明（程序员给出的中文描述） wangzl
   CString strTableID;//字段归属表名 yangjr 2018/3/1
   tag_FieldCol_Data(CString strColID_In,CString strColDestribution_In,CString strTableID_In)
   {
      strColID = strColID_In;
      strColDestribution = strColDestribution_In;
      strTableID = strTableID_In;
   }

}S_FieldCol_Data;

#pragma endregion 字段及其对应的示例


typedef std::map<CString/*strColID 列名称*/,S_GridCtrl_FieldAtrri> MAP_GridCtrl_FieldAtrri;

typedef std::map<int/*表格样式显示的行*/,CString/*strColID 列名称*/> MAP_GridCtrl_FieldPos;


#pragma region 表格属性

//gridctrl 表格属性
typedef struct tag_GridCtrl_TableAttri 
{
	MAP_GridCtrl_FieldAtrri mapFeildAtrri;//一个表格的所有字段属性
	MAP_GridCtrl_FieldPos mapTableFeildPos;//当前字段在表格样式中显示中第几行
	
	BYTE	nDataRowHeight;				//数据的行高
	BYTE  iDataRowFont;				//数据的字体 yangjr 2017-6-7
	bool isShowTitleFilter;	//是否显示列标题筛选器		by WangZY 2017/06/07
	bool isShowSortBar; //是否显示筛选栏

	bool isAllowSort;//是否允许排序
	bool isWholeRowSelect;//整行选择
	bool isShowSumBar;//是否显示合计栏
	bool isMultiRowSelect;//多行选择  

	bool IsMultiRowSelectNoLoseFocus;//多行选择不失焦点 ===> 这个改为多行选择单击选中功能 by lida 2018/01/31
	bool isEnableDragCol;  //列位置能否拖动 yangjr 2017-6-13
	bool isEnableEdit;	  //表是否可编辑		by WangZY 2017/06/15
	bool isPrintHengXiang; //是否横向打印		by yangjr 2017/09/19
   CString strUpdateTime; //更新日期
   bool isNoUpdateServerStyle; //是否不更新服务器样式	by yangjr 2018/5/29
   int  iPageRows;
	tag_GridCtrl_TableAttri()
	{
		isShowTitleFilter = false;
		isShowSortBar = false;
		isAllowSort = false;
		isWholeRowSelect = false;
		isShowSumBar = false;
		isMultiRowSelect = false;
		IsMultiRowSelectNoLoseFocus = false;
		nDataRowHeight = CB_GRIDCTRL_DEFAULT_ROWHEIGHT;
		iDataRowFont = CB_GRIDCTRL_DEFAULT_FONT;
		isEnableDragCol = true;
		isEnableEdit = true;		//表是否可编辑		by WangZY 2017/06/15
		isPrintHengXiang = false;
      strUpdateTime = _T("");
      isNoUpdateServerStyle = false;
      iPageRows = 50;
	}
}S_GridCtrl_TableAttri;

#pragma endregion 表格属性


//标题栏筛选数据定义
typedef struct tag_SHAIXUAN_DATA
{
   CString strText;//文本
   BOOL isChecked; //是否勾选
}SHAIXUAN_DATA;

typedef std::vector<SHAIXUAN_DATA> VEC_SHAIXUAN_DATA;//所有的筛选数据

typedef struct tag_SERCH_DATA
{
   VEC_SHAIXUAN_DATA vecShaiXuanData; //标题筛选数据
   CString strText;//筛选栏数据文本   
}SERCH_DATA;

//对应列ID在GridCtrl中的筛选信息
typedef std::map<CString/*strColID 列名称*/,SERCH_DATA/*筛选栏数据*/> MAP_SERCH_DATAS;
/**********************表格内部使用数据 end*********************************/





