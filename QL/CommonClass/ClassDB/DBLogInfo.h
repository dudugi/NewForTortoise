/*************************************************
// <文件>: DBLogInfo.h
// <说明>: 日志信息类
// <作者>: wangzl
// <日期>: 2019/01/30 10:33:01
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 
#pragma once

#include "DataMid.h"
#include "DBKeyDef.h"
#include "DBKeyDef_V.h"
#include "DBKeyDef_Cust.h"
#include <map>
#include <vector>
class CADOConn;

struct new_and_old
{
   CString strID;         //该字段所在的数据ID
   CString strFiledName;  //字段名字
   CString strOldValue;   //旧的字段的值
   CString strNewValue;   //新的字段的值
};

typedef std::map<CString ,new_and_old> table_log_map_row;
typedef std::map<int , table_log_map_row> table_log_map;

class CDBLogInfoData :public CDataMid
{
	DECLARE_SERIAL( CDBLogInfoData)//序列化（串行化）需要添加的声明
public:
	int				m_nID;			//自增ID
	CString			m_strCate;		//类别
	CString			m_strCode;		//单号或款式号/其它
	COleDateTime	m_dDate;		//操作时间
	CString			m_strMaker;		//操作人
	CString			m_strType;		//操作类型
	CString			m_strAction;	//具体的操作行为
	CString			m_strInterFace; //界面名称
	CString         m_strProject;	//项目名称
   CString        m_strMacAddr; //Mac地址 liuhw 2018/10/21

public:
	CDBLogInfoData();
	~CDBLogInfoData();
   void SetLogData(CString strCate,CString strCode,CString strMaker,CString strType,CString strAction,CString strMacAddr,CString strInterFaceName = _T(""),CString strProjectName = _T(""));
   void ResetData();
   void EmptyLogAction();
	void Copy(CDBLogInfoData *pData);
	void Serialize(CArchive& ar);
	BOOL GetAllDBInfo(CADOConn *pADOConn);			//获取一条记录信息
	BOOL InsertAllDBInfoByAct(CADOConn *pADOConn);	//插入一条新记录
   CString GetSQLInsertAllDBInfoByAct();
	BOOL InsertAllDBInfoWithLocalTime(CADOConn *pADOConn);
   CString GetSQLInsertAllDBInfoWithLocalTime();

	BOOL DelAllDBInfoByAct(CADOConn *pADOConn);		//根据用户账户删除记录
	CString GetInsertSQL();//返回插入的SQL语句
   //修改时候，判断表格内容是否有修改，如果有将字段添加入Map中。 add liuhw 2018/09/17
   static void TestOperatLog(table_log_map &mapLog, int nRowID,CString strID,CString strFiledID,CString strFiledName, CString strNewValue, CString strOldValue);
   //将Map中的内容输出 add liuhw 2018/09/17
   static CString WriteChangeLog(table_log_map &old_map);

	static CDBLogInfoData * Instance();			//获取（指针）实例

   enum              //操作日志的数据库操作类型 liuhw 2018/09/05
   {
      TYPE_ADD,
      TYPE_MODIFY,
   };
   
private:
	static std::shared_ptr<CDBLogInfoData> sm_inst;
};

class CDBLogInfoList  : public CDataListMid
{
	DECLARE_SERIAL(CDBLogInfoList)
public:
	CDBLogInfoList();
	~CDBLogInfoList();
	CDBLogInfoData* GetItem(int nIndex);			//根据索引获取Item
	void AddItem(CDBLogInfoData* pItem);			//添加Item
	void DeleteItem(int nIndex);					//删除固定索引Item
	static CDBLogInfoList * Instance();			//获取（指针）实例

	//获取订单日志 根据订单号
	//add by lida 2017/07/11
	std::map<CString,CDBLogInfoData*> GetOrderLogByOrderCode(CADOConn *pADOConn,CString strOrderCode);

	//获取log界面需要的数据
	void GetListData(CADOConn *pADOConn , CString startTime , CString endTime , CString strUser ,
		CString projectName, CString strKey , std::vector<CString> strOpTypeLst);
   /*******************************************************************
   * @brief :  日志英文表名转中文表名
   * @author : liuhw 2019/02/21 13:41:33
   * @param :   key:英文表名 ，value 中文表名Map
   * @example : 
   * @return :  
   *******************************************************************/
   void SetCateEnglishToChinese(__in std::map<CString , CString> tableNameMap);
#ifdef USING_GRIDCTRL_MARK
	MAP_GridCtrl_AllData CreatrGridData(CADOConn *pADOConn);
#endif
private:
   std::map<CString , CString> m_tableNameMap;// Key:英文表名，value:中文表名 liuhw 2019/02/21
private:
	static std::shared_ptr<CDBLogInfoList> sm_inst;
};