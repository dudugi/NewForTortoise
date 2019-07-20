/*************************************************
// <文件>: DBCompanyInfo.h
// <说明>: 公司信息表处理DB类
// <作者>: WangZY
// <日期>: 2019/02/22 17:33:36
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 
#pragma once

#ifndef COMPANYSIGN_IMAGE
#define COMPANYSIGN_IMAGE	1
#endif

#include "DataMid.h"

class CADOConn;

#include "DBKeyDef.h"
#include "DBKeyDef_V.h"
#include "DBKeyDef_Cust.h"

class CDBCompanyInfo  : public CDataMid
{
	DECLARE_SERIAL( CDBCompanyInfo)//序列化（串行化）需要添加的声明
public:
	int m_nID; 
	CString m_strCompanyName;		//公司名称
	CString m_strCompanyTel;		//公司电话
	CString m_strCompanyFax;		//公司传真
	CString m_strCompanyAddress;	//公司地址
#if COMPANYSIGN_IMAGE
	Image*				m_pCompanySign;//公司标志图片
#endif
public:
	CDBCompanyInfo(void);
	~CDBCompanyInfo(void);
	void Trim();
	void ResetData();
	void Copy(CDBCompanyInfo *pData);
	void Serialize(CArchive& ar);
	BOOL GetAllDBInfo(CADOConn *pADOConn);		//获取公司【整条】信息
	BOOL InsertAllDBInfo( CADOConn *pADOConn );
	BOOL UpdateAllDBInfo(CADOConn *pADOConn);	//更新公司一条信息,表中只有一条记录
	BOOL UpdateAllDBInfoByID(CADOConn *pADOConn);
	static CDBCompanyInfo * Instance();//获取（指针）实例

#ifdef COMPANYSIGN_IMAGE
private:
	inline void ClearCompanySignImage();
#endif // COMPANYSIGN_IMAGE

private:
	static std::shared_ptr<CDBCompanyInfo> sm_inst;

};

class CDBCompanyInfoList : public  CDataListMid
{
	DECLARE_SERIAL(CDBCompanyInfoList)
public:
	CDBCompanyInfoList();
	~CDBCompanyInfoList();
	CDBCompanyInfo*  GetItem(int nIndex);
	void    AddItem(CDBCompanyInfo* pItem);
	void    DeleteItem(int nIndex);
	void	Serialize(CArchive& ar);
	void    GetListFromDB(CADOConn *pADOConn);
	static CDBCompanyInfoList * Instance();//获取（指针）实例
private:
	static std::shared_ptr<CDBCompanyInfoList> sm_inst;
};
