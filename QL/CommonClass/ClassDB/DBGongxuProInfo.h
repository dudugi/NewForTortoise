/*************************************************
// <文件>: DBGongxuProInfo.h
// <说明>: 数据操作类-工序方案表
// <作者>: yangjr
// <日期>: 2019/02/20 16:09:37
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 
#pragma once

#include "DataMid.h"
#include "DBKeyDef.h"
#include "DBKeyDef_V.h"
#include "DBKeyDef_Cust.h"


class CADOConn;
//工序方案
class CDBGongxuProInfoData  : public CDataMid
{
	DECLARE_SERIAL( CDBGongxuProInfoData)//序列化（串行化）需要添加的声明
public:
	CString					m_ID;		//主键
	CString			m_strProName;		//方案名
	CString   m_strProcedureName;		//工序名
   CString   m_strZhiPaiPerson;     //指派人
public:
	CDBGongxuProInfoData();
	~CDBGongxuProInfoData();
	void ResetData();
	void Copy(CDBGongxuProInfoData *pData);

	//获取工序方案【整条】信息
	BOOL GetAllDBInfo(CADOConn *pADOConn);
	//删除【整条】记录		
	BOOL DelAllDBInfo(CADOConn *pADOConn);
	//增加【整条】记录		
	BOOL InsertAllDBInfo(CADOConn *pADOConn);
	//更新【整条】记录	
	BOOL UpdateAllDBInfo(CADOConn *pADOConn);	
};


class CDBGongxuProInfoDataList : public CDataListMid
{
	DECLARE_SERIAL(CDBGongxuProInfoDataList)
public:
	CDBGongxuProInfoDataList();
	~CDBGongxuProInfoDataList();

	BOOL GetListFromDB( CADOConn *pADOConn );
	CDBGongxuProInfoData*  GetItem(int nIndex);
	void    AddItem(CDBGongxuProInfoData* pItem);
	void    DeleteItem(int nIndex);
	CDBGongxuProInfoData*  GetItemByID(CString strID);
	int GetIndexByID(CString strID);

   void CreateGridStyleGX(CADOConn *pADOConn,MAP_GridCtrl_AllData &allData,vector<CString> &vecGXField);
	// 获取工序方案列表
	void GetGongxuProNameLst(std::vector<CString> &nameLst);
	// 根据工序方案名获取工序列表
	void GetGongxuProByGongxuProName(std::vector<CString> &productionLst , CString proName);
   //根据工序方案名获取工序列表和指派人
   void GetGongxuProAndZhipaiPersonByGongxuProName(std::vector<pair<CString,CString>> &productionLst , CString proName);
	// 添加工序方案
	BOOL AddGongxuProByGongxuProName(std::vector<CString> productionLst , CString proName);
   BOOL AddGongxuProAndZhipaiPersonByGongxuProName(std::vector<pair<CString,CString>> productionLst , CString proName);
	// 更新工序方案
	BOOL UpdateGongxuProByGongxuProName(std::vector<CString> productionLst , CString proName , CString oldProName);
   BOOL UpdateGongxuProAndZhipaiPersonByGongxuProName(std::vector<pair<CString,CString>> productionLst , CString proName , CString oldProName);
	// 删除工序方案
	BOOL DeleteGongxuProByGongxuProName(CString proName);

	static CDBGongxuProInfoDataList * Instance();//获取（指针）实例
private:
	static std::shared_ptr<CDBGongxuProInfoDataList> sm_inst;
	CADOConn *m_pADOConn;
};