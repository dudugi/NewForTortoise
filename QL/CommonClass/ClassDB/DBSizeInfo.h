/*************************************************
// <文件>: DBSizeInfo.h
// <说明>: 订单对应的尺码信息表
// <作者>: wangzl
// <日期>: 2019/01/30 10:29:45
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 

#pragma once

#include "DataMid.h"
#include "SpecItem.h"
#include <map>

//数据库中字段
class CADOConn;

class CDBSizePartInfoData  : public CDataMid
{
	DECLARE_SERIAL( CDBSizePartInfoData)//序列化（串行化）需要添加的声明
public:
   __int64           m_nSizePartID     ;//部位表ID
   CString           m_strName         ;//名称(尺码规格)
   WORD              m_nDefault        ;//是否是默认的标志
   int               m_nUserSort       ;//用户自定义排序顺序
   CString           m_cMemo;//部位说明 yangjr 2019/07/14
   enum{
      En_PART_DEFAULT_NULL          = 0,//空
      En_PART_DEFAULT_CLOTHES       = 1,//默认 衣服
      En_PART_DEFAULT_TROUSERS      = 2,//默认 裤子
      En_PART_DEFAULT_BOTH          = 3,//衣服、裤子都有
   };

public:
	CDBSizePartInfoData();
	~CDBSizePartInfoData();
	void ResetData();
	void Copy(CDBSizePartInfoData *pData);
	void Serialize(CArchive& ar);

	//数据库操作函数
	BOOL GetAllDBInfo(CADOConn *pADOConn);			//获取【整条】信息
	BOOL InsertAllDBInfo(CADOConn *pADOConn);		//插入【整条】新记录
	BOOL UpdateAllDBInfoByID(CADOConn *pADOConn);	//根据用户账户更新【整条】记录
	BOOL DelAllDBInfoByID(CADOConn *pADOConn);		//根据用户账户删除【整条】记录
	static CDBSizePartInfoData * Instance();		//获取（指针）实例

private:
	static std::shared_ptr<CDBSizePartInfoData> sm_inst;
};

class CDBSizePartInfoList : public CDataListMid
{
	DECLARE_SERIAL(CDBSizePartInfoList)
public:
	CDBSizePartInfoList();
	~CDBSizePartInfoList();
	CDBSizePartInfoData*  GetItem(int nIndex);
	void    AddItem(CDBSizePartInfoData* pItem);
	void    DeleteItem(int nIndex);

	CString GetItemNameByID(__int64 nPartID);
   CString GetItemMemoByID(__int64 nPartID);
	__int64 GetItemIDByName(CString strPartName);
   CDBSizePartInfoData* GetItemByName(const CString & strPartName);

	void GetListFromDB(CADOConn *pADOConn);		//从数据库获取链表
	static CDBSizePartInfoList * Instance();	//获取（指针）实例

   static BOOL GetPartSort(CADOConn* pAdo,map<CString,CString>& mapData);

private:
	static std::shared_ptr<CDBSizePartInfoList> sm_inst;
};



