/*************************************************
// <文件>: DBClientInfo.h
// <说明>: 用户信息登录心跳包检测的DB类
// <作者>: WangZY
// <日期>: 2019/02/22 17:25:24
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 
#pragma once

#include <map>
#include "DataMid.h"
#include "DBKeyDef.h"

class CADOConn;

class CDBClientVarifyInfo  : public CDataMid
{
	DECLARE_SERIAL( CDBClientVarifyInfo)//序列化（串行化）需要添加的声明
public:
   CString				m_strID;			   //ID
   CString	         m_strUserId;		//用户ID
   CString			   m_strVarifyTime;	//时间
   CString			   m_strMacInfo;	   //机器信息

   int               m_nOutTime;       //差异时间：分钟

public:
	CDBClientVarifyInfo();
	~CDBClientVarifyInfo();
	void ResetData();
	void Copy(CDBClientVarifyInfo *pData);
	void Serialize(CArchive& ar);
	BOOL GetAllDBInfo(CADOConn *pADOConn);		      //获取纱线【整条】信息
	BOOL DelAllDBInfoByID(CADOConn *pADOConn);		//删除【整条】记录
	BOOL UpdateAllDBInfoByID(CADOConn *pADOConn);	//根据纱线号更新【整条】记录
	BOOL InsertAllDBInfoByID(CADOConn *pADOConn);	//根据纱线号插入【整条】记录
   
   BOOL UpdateHeartbeetTimeById(CADOConn *pADOConn);   //更新心跳时间

   //BOOL UpdateHeartbeetTimeAndUserIdById();

   BOOL InsertAllDBInfoByUserAndMacID(CADOConn *pADOConn);

   static BOOL DeleteDBInfoByUserId(CADOConn *pADOConn,CString strUserId);

   static BOOL DeleteDBInfoByUserAndMacId(CADOConn *pADOConn,CString strUserId,CString strMacId);

   void Trim();
	static CDBClientVarifyInfo * Instance();//获取（指针）实例

private:
	static std::shared_ptr<CDBClientVarifyInfo> sm_inst;
};

class CDBClientVarifyInfoList : public CDataListMid
{
	DECLARE_SERIAL(CDBClientVarifyInfoList)
public:
	CDBClientVarifyInfoList();
	~CDBClientVarifyInfoList();

   static CDBClientVarifyInfoList * Instance();//获取（指针）实例

	CDBClientVarifyInfo*  GetItem(int nIndex);
	void    AddItem(CDBClientVarifyInfo* pItem);
	void    DeleteItem(int nIndex);
	CDBClientVarifyInfo* GetItemById(CString strId);
	int GetIndexById(CString strId);
   int GetIndexByMacIdAndUserId(CString strMacId,CString strUserId);

	void GetListFromDB(CADOConn *pADOConn);//从数据库获取链表
	

   BOOL GetInfoById(__in CADOConn *pADOConn,__in CString strId,
      __out CDBClientVarifyInfo* pObj);

   CDBClientVarifyInfo* GetItemByMacIdAndUserId(CString strMacId,CString strUserId);

   CDBClientVarifyInfo* GetItemByMacId(CString strMacId);
   CDBClientVarifyInfo* GetItemByUserId(CString strUserId);
   


private:
	static std::shared_ptr<CDBClientVarifyInfoList> sm_inst;
};