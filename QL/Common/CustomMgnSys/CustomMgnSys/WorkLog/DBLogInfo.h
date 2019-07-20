//用户信息
#pragma once

#include "DataMid.h"
#include "DBKeyDef.h"
#include "DBKeyDef_V.h"
#include "DBKeyDef_Cust.h"
#include <map>
#include <vector>

class CADOConn;

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
public:
	CDBLogInfoData();
	~CDBLogInfoData();
	void SetLogData(CString strCate,CString strCode,CString strMaker,CString strType,CString strAction,CString strInterFaceName = _T(""),CString strProjectName = _T(""));
	void ResetData();
	void Copy(CDBLogInfoData *pData);
	void Serialize(CArchive& ar);
	BOOL GetAllDBInfo(CADOConn *pADOConn);			//获取一条记录信息
	BOOL InsertAllDBInfoByAct(CADOConn *pADOConn);	//插入一条新记录
	BOOL InsertAllDBInfoWithLocalTime(CADOConn *pADOConn);
	BOOL DelAllDBInfoByAct(CADOConn *pADOConn);		//根据用户账户删除记录

	CString GetInsertSQL();//返回插入的SQL语句

	void SetLogToDB(BOOL bLog);
	static CDBLogInfoData * Instance();			//获取（指针）实例

private:
	static std::shared_ptr<CDBLogInfoData> sm_inst;
	BOOL m_bLog;		//是否记录到数据库
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

   void GetLogListData(CADOConn *pADOConn );
#ifdef USING_GRIDCTRL_MARK
	MAP_GridCtrl_AllData CreatrGridData();
#endif
private:
	static std::shared_ptr<CDBLogInfoList> sm_inst;
};
