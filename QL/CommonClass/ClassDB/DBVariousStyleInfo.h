#pragma once
/*************************************************
// <文件>: DBVariousStyleInfo.h
// <说明>: 数据库操作类-款式对应首选单表
// <作者>: yangjr
// <日期>: 2019/02/20 16:52:29
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 
#include "DataMid.h"

class CADOConn;


//#define  DBOrder_key_LastTime		  _T("dLastTime")//订单的最后操作时间


class CDBVariousStyleInfoData :
	public CDataMid
{
public:
	CDBVariousStyleInfoData(void);
	virtual ~CDBVariousStyleInfoData(void);

	typedef enum En_Ord_Perferred
	{
		Ord_UnPerferred = 0,//非首选
		Ord_Perferred,//首选
	}EN_ORD_PERFERRED;

	int				m_nID				;//自增ID
	CString			m_strStyleNo		;//款号
	CString			m_strOrderNo		;//订单号
	CString			m_strDestribution	;//描述
	int				m_nPreferred		;//是否首选
	
	COleDateTime	m_dtOrdUpdate		;//订单的更新时间 之前用于任务表  一单多件修改时没有了更新时间  获取的是订单的真实下单时间 wangzl 2018-10-29

	void ResetData();
	void Copy(CDBVariousStyleInfoData *pData);
	BOOL GetAllDBInfo(CADOConn *pADOConn,BOOL bWithOrderInfo = FALSE);		//获取【整条】信息

	//插入一条数据
	BOOL InsertDBInfo(CADOConn *pADOConn);
	BOOL InsertDBInfoIfNotExists(CADOConn *pADOConn);
	//更新一条记录的描述
	BOOL UpdateDestribution(CADOConn *pADOConn);
	//将当前款式对应的当前单号设为首选
	BOOL SetPreferred(CADOConn *pADOConn);
	//根据款式号 订单号删除一条记录
	BOOL DelDBInfoByStyleAndOrder(CADOConn *pADOConn);
	
	//2017/11/20 zhangt 根据款号获取首选单号
	CString GetPreferredOrderNoByStyleNo(CADOConn *pADOConn);
	CString GetPreferredOrderNoByStyleNo(CADOConn *pADOConn,CString strStyleNo);
};

class CDBVariousStyleInfoList : public CDataListMid
{
public:
	CDBVariousStyleInfoList();
	~CDBVariousStyleInfoList();

	CDBVariousStyleInfoData*  GetItem(int nIndex);				//根据索引获取Item
	CDBVariousStyleInfoData*  GetPerferredItem();				//获取首选项
	CDBVariousStyleInfoData*  GetItemByOrderNo(CString strOrderNo);
	BOOL SetPerferredItem(CADOConn *pADOConn,CString strOrderNo);
	void AddItem(CDBVariousStyleInfoData* pItem);				//
	void DeleteItem(int nIndex);
	void DeleteItemByOrderNo(CString strOrderNo);

	void GetListFromDB(CADOConn * pADOConn,CString strStyleNo);

protected:
	
private:
};