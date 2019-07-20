#pragma once

#include "CDataTableDlgDefine.h"
#include "CDataTableFieldDefine.h"

class TiXmlElement;
//表格属性
//class CDlgTableStyleGlobalSet;
//class DBTableStyleGlobalSetInfoList;

class CGridCtrlTableAttributeOp
{
   //friend CDlgTableStyleGlobalSet;
   //friend DBTableStyleGlobalSetInfoList;
public:
	CGridCtrlTableAttributeOp(void);
	~CGridCtrlTableAttributeOp(void);

private:
   typedef void (CGridCtrlTableAttributeOp::*funcCreateAttri)(S_GridCtrl_TableAttri &tableAttri);
   map<CString, funcCreateAttri> m_mapFunc;//字符串关联的函数表

   typedef void (CGridCtrlTableAttributeOp::*funcCreateAttri2Param)(S_GridCtrl_TableAttri &tableAttri,CString strFileName);
   map<CString, funcCreateAttri2Param> m_mapFunc2Param;//字符串关联的函数表
   //或可用hashmap

   static std::shared_ptr<CGridCtrlTableAttributeOp> sm_inst;

public:
	BOOL ReadTableAttri(CString fileName,S_GridCtrl_TableAttri &tableAttri,BOOL bNoXml=FALSE);//bNoXml是否存在XML文件

	BOOL WriteTableAttri(CString fileName,const S_GridCtrl_TableAttri &tableAttri);
	BOOL WriteTableAttriAsDefault(CString fileName,const S_GridCtrl_TableAttri &tableAttri);//保存表格样式到系统目录下 yangjr2017-6-13 
	//wangzl 根据列名创建一个空的表格列属性列表 2017/6/17 
	void CreateEmptyFieldAttri(S_GridCtrl_TableAttri &tableAttri,CStringList &strlFieldName);

	//初始化系统目录下的表格样式 yangjr 2018-1-15
	BOOL InitDefaultTableAttri(CString fileName);

	//初始化用户目录下的表格样式 yangjr 2018-1-15
	BOOL InitUserTableAttri(CString fileName,S_GridCtrl_TableAttri &tableAttri);

   //************************************
   // Method:    更新表格样式
   // Author:    wuZhiHua
   // Date : 	  2018/04/02
   // Access:    private 
   // Returns:   void
   // Parameter: TiXmlElement * pElement
   //************************************
   BOOL UpdateGridStyleAttriInfo(CString fileName , S_GridCtrl_TableAttri &tableAttri);

   static void LinkIntValueToElement(int iValue,TiXmlElement *pElement);
   static void LinkCStringValueToElement(CString strValue,TiXmlElement *pElement);
   BOOL WriteTableAttriToXml(CString fullName,const S_GridCtrl_TableAttri &tableAttri);
   BOOL ReadTableAttriFromXml(CString fullName,S_GridCtrl_TableAttri &tableAttri);

   static CGridCtrlTableAttributeOp * Instance();

   //************************************
   // Method:    强制读取服务器的表格样式并更新到本地
   // Author:    yangjr
   // Date : 	  2018/05/29
   // Access:    public 
   // Returns:   BOOL
   // Parameter: TiXmlElement * pElement
   //************************************
   //BOOL GetServerStyleAndUpdateLocal(CString fileName , S_GridCtrl_tableAttri &tableAttri);

private:
   BOOL ReadDefaultTableAttri(CString fileName,S_GridCtrl_TableAttri &tableAttri);//创建纱线入库表格属性默认数据

   void CreateTABLESTYLE(S_GridCtrl_TableAttri &tableAttri);
	void Create_StaffMgn(S_GridCtrl_TableAttri &tableAttri);					//员工管理	
	void Create_CusMgn(S_GridCtrl_TableAttri &tableAttri);					//客户管理	
   void Create_LogInfo(S_GridCtrl_TableAttri &tableAttri);					//日志信息

   void Create_CusMgnOpRecords(S_GridCtrl_TableAttri &tableAttri);

	void InsertFeildID(S_GridCtrl_TableAttri &tableAttri, short iColIndex_In,
		CString strColID_In, CString strColShowName_In = _T(""),CString strColDestribution = _T(""),
		CString strTableID_In = _T(""),bool isShow_In = true, bool isEdit_In = true, short iColWidth_In = 75,
		bool isEnableFilter_In = true, BYTE iLock_In = 0, ENUM_COLSUMTYPE enColSumType_In = CB_enum_ColSumType_None,
		BYTE iColFont_In = CB_GRIDCTRL_DEFAULT_FONT, bool IsFontWeight_In = false,
		ENUM_COLSERCHTYPE enSerchType_In = CB_enum_ColSerchType_Contain, CString strColFormat_In=_T(""));//插入一个字段到表格样式中 yangjr2017-6-13

	void InsertOrderViewInfo(S_GridCtrl_TableAttri &tableAttri,int &colIndex);

	CString GetUserTableConfigXmlPath();//用户路径
	CString GetSysTableConfigXmlPath();//系统路径

	void SortFieldToMap(MAP_GridCtrl_FieldAtrri &,S_GridCtrl_TableAttri & tableAttri,int & nBeginIndex);  

   //2017/12/12 zhangt 合并xml文件和代码中的数据添加的字段 不用删除xml文件
	BOOL CombineDefaultTableAttri(CString DefaultFilelName,S_GridCtrl_TableAttri &tableAttri); 

};

