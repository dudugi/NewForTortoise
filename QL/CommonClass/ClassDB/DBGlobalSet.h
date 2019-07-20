/*************************************************
// <文件>: DBGlobalSet.h
// <说明>: 全局配置信息表
// <作者>: wangzl
// <日期>: 2019/01/30 10:32:46
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/
#pragma once

#include "DataMid.h"
#include "DBKeyDef.h"
#include "DBKeyDef_V.h"
#include "DBKeyDef_Cust.h"

class CADOConn;

#define DBGlobalSet_DelOrder					_T("订单删除")		//不恢复  可恢复
//标题过滤器上限限制开关		by WangZY 2018/03/09
#define DBGlogalSet_TitleFilter_OrderLimitCount				_T("标题过滤器的数据记录数上限数据量")
#define DBGlogalSet_TitleFilter_ContentLimitCount			_T("标题过滤器的列表项上限数据量")
#define DBGlobalSet_AbleProAutoFinish        _T("允许自动完成未扫工序")  //add by wangzl 2018-7-16
#define DBGlobalSet_FirstForbidSubmitProcess _T("禁止任务表提交的首个工序") //add by duchen 2018-10-29
#define DBGlobalSet_AbleMustProcessAutoFinish   _T("允许必扫工序自动完成") //add by wangzl 2018-7-16 默认否
#define DBGlobalSet_TaskReworkEffectProcess  _T("任务表返工影响工序流程") //add by wangzl 2018-7-18 默认否

#define DBGlobalSet_ColorState_CheckIn          _T("订单颜色状态显示-检入")          //add by wangzl 2019-5-24
#define DBGlobalSet_ColorState_CheckoutEdit     _T("订单颜色状态显示-检出可编辑")    //add by wangzl 2019-5-24
#define DBGlobalSet_ColorState_CheckoutRead     _T("订单颜色状态显示-检出不可编辑")  //add by wangzl 2019-5-24
#define DBGlobalSet_ColorState_FixVersion       _T("订单颜色状态显示-款式定版")      //add by wangzl 2019-5-24

#define DBGlobalSet_PictureMaxSize        _T("图片上传最大尺寸限制")   //add by anjie 2018-8-3
#define DBGlobalset_DisableOrder          _T("上机后允许作废订单")     //add by wangzl 2018/09/12
#define DBGlobalset_VERSION_NAME          _T("版本名称")              //add by liuhw 2018/09/30
#define DBGlobalset_AbleUnExistsStyleOrder _T("款式未维护允许下单")  //add by wangzl 2019/04-04
#define DBGlobalset_ShowPicNum            _T("显示款式图片数量/页")  // add by lida 2019/05/23
#define DBGlobalset_RefreshTime           _T("款式管理自动刷新时间")  // add by wangzl 2019/07/19

#define ID_DEFAULT		-1
#define MAX_SIZE  600

struct tag_sql_data
{
	tag_sql_data()
	{
		nID = ID_DEFAULT;
		strName = _T("");
		strValue = _T("");
		strRemark = _T("");
	}
	int				nID;			//自增ID
	CString			strName;		//名称
	CString			strValue;		//值
	CString			strRemark;	//备注
};
class CDBGlobalSetData :public CDataMid
{
	DECLARE_SERIAL( CDBGlobalSetData)//序列化（串行化）需要添加的声明
public:
	int				m_nID;			//自增ID
	CString			m_strName;		//名称
	CString			m_strValue;		//值
	CString			m_strRemark;	//备注

public:
	CDBGlobalSetData();
	~CDBGlobalSetData();
	void ResetData();
	void Copy(CDBGlobalSetData *pData);
	void Serialize(CArchive& ar);
	BOOL GetAllDBInfo(CADOConn *pADOConn);			//获取一条记录信息
	BOOL UpdateAllDBInfoByID(CADOConn *pADOConn);	//通过ID更新一条记录信息
	BOOL InsertAllDBInfo(CADOConn *pADOConn);		//插入【整条】新记录
	CString GetTextUpdateAllDBInfoByID();
   CString GetTextInsertAllDBInfoByID();//获取插入语句的操作
	BOOL SetData_By_Key(CString strKey, CString strValue);
	CString GetDBValueByName(CADOConn* pADOConn,CString strName);//从数据库获取信息
	tag_sql_data GetDBAllValueByName(CADOConn* pADOConn,CString strName);//从数据库获取某个数据的ID
	static CDBGlobalSetData * Instance();			//获取（指针）实例

#ifdef USING_GRIDCTRL_MARK
	MAP_GridCtrl_RowData CreateGridRowData();
#endif// USING_GRIDCTRL_MARK

private:
	static std::shared_ptr<CDBGlobalSetData> sm_inst;
};

class CDBGlobalSetList  : public CDataListMid
{
	DECLARE_SERIAL(CDBGlobalSetList)
public:
	CDBGlobalSetList();
	~CDBGlobalSetList();
	CDBGlobalSetData* GetItem(int nIndex);	//根据索引获取Item
	void AddItem(CDBGlobalSetData* pItem);	//添加Item
	void DeleteItem(int nIndex);			//删除固定索引Item
	static CDBGlobalSetList * Instance();	//获取（指针）实例
	void GetListFromDB(CADOConn *pADOConn);	//从数据中获取数据到链中

	//根据需要的名称从链表中获取相关的值
	CString GetValueByName(CString strName);

   COLORREF GetColorValueByName(CString strName);     //读取颜色值
	
	//根据需要的名称从链表中获取相关的数值		by WangZY 2018/03/09
	int GetIntValueByName(CString strName, int nDef);

   //根据名称获取对应的项  
   CDBGlobalSetData* GetItemByName(CString strName);	//根据索引获取Item

// #ifdef USING_GRIDCTRL_MARK
// 	MAP_GridCtrl_AllData CreatrGridData();
// #endif // USING_GRIDCTRL_MARK

private:
	static std::shared_ptr<CDBGlobalSetList> sm_inst;
};
