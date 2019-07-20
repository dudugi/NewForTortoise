/*************************************************
// <文件>: DBStyleSizeExtra.h
// <说明>: 款式尺寸额外数据类
// <作者>: yangjr
// <日期>: 2019/07/14 14:29:45
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 

#pragma once

#include "DataMid.h"
#include <map>

//数据库中字段
class CADOConn;
class CDBStyleSizeExtraData  : public CDataMid
{
	DECLARE_SERIAL( CDBStyleSizeExtraData)//序列化（串行化）需要添加的声明
public:
   int               m_nID;  
   CString           m_cStyleNo         ;//款号
   int               m_iPartID        ;//尺寸部位
   CString           m_cMemo;//部位说明
   double            m_fCeLiangBeforeSize;//测量前尺寸
   double            m_fCeLiangCusSize;//客户测量尺寸
   double            m_fWaterBeforeSize;//洗水前尺寸
   double            m_fWaterAfterSize;//洗水后尺寸
public:
	CDBStyleSizeExtraData();
	~CDBStyleSizeExtraData();
	void ResetData();
	void Copy(CDBStyleSizeExtraData *pData);
	void Serialize(CArchive& ar);

	//数据库操作函数
	BOOL GetAllDBInfo(CADOConn *pADOConn);			//获取【整条】信息
	BOOL InsertAllDBInfo(CADOConn *pADOConn);		//插入【整条】新记录
	BOOL UpdateAllDBInfoByID(CADOConn *pADOConn);	//根据用户账户更新【整条】记录
	BOOL DelAllDBInfoByID(CADOConn *pADOConn);		//根据用户账户删除【整条】记录
   BOOL DelAllDBInfoByStyleNo(CADOConn *pADOConn);
   CString GetDelAllDBInfoByStyleNo(CString strStyleNo);
   CString GetInsertAllDBInfoSql();
	static CDBStyleSizeExtraData * Instance();		//获取（指针）实例

private:
	static std::shared_ptr<CDBStyleSizeExtraData> sm_inst;
};

class CDBStyleSizeExtraList : public CDataListMid
{
	DECLARE_SERIAL(CDBStyleSizeExtraList)
public:
	CDBStyleSizeExtraList();
	~CDBStyleSizeExtraList();
	CDBStyleSizeExtraData*  GetItem(int nIndex);
	void    AddItem(CDBStyleSizeExtraData* pItem);
	void    DeleteItem(int nIndex);

   CDBStyleSizeExtraData* GetItemNameByPartID(__int64 nPartID);
	void GetListFromDB(CADOConn *pADOConn);		//从数据库获取链表
	static CDBStyleSizeExtraList * Instance();	//获取（指针）实例
   void GetListFromDBByStyleNo(CADOConn *pADOConn,CString strStyleNo);

private:
	static std::shared_ptr<CDBStyleSizeExtraList> sm_inst;
};



