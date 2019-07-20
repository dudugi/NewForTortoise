#pragma once
#include "DataMid.h"
#include "DBKeyDef.h"

using namespace std;

/*************************************************
// <文件>: DBOrdFlag.h
// <说明>: 订单打印次数类
// <作者>: lida
// <日期>: 2019/02/22 15:49:09
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 
class CADOConn;

class CDBOrdFlagInfo : public CDataMid
{
public:
	CDBOrdFlagInfo();
	~CDBOrdFlagInfo();

	virtual void ResetData();

	virtual void Copy(CDBOrdFlagInfo * pData);

	void GetAllDataInfo(CADOConn *pADOConn);

	static CDBOrdFlagInfo * Instance();//获取（指针）实例

public:
	int			m_ID;
	CString		m_strOrdCode;
	int			m_iPrint_GYD;		//工艺单打印次数
	int			m_iPrint_XSM;		//洗水唛打印次数
	int			m_iPrint_SCZSD;		//生产指示单打印次数
	int			m_iPrint_File;		//上机文件下载次数

private:
	static std::shared_ptr<CDBOrdFlagInfo> sm_inst;
};

class CDBOrdFlagInfo_List : public CDataListMid
{
public:
	CDBOrdFlagInfo_List();
	~CDBOrdFlagInfo_List();
	static CDBOrdFlagInfo_List * Instance();//获取（指针）实例

private:
	static std::shared_ptr<CDBOrdFlagInfo_List> sm_inst;

public:
	BOOL WriteOrderFlag(__in CADOConn *pADOConn,__in vector<CString>& vecOrder,__in BOOL bGYD,__in BOOL bXSM,__in BOOL bSCZSD,__in BOOL bFile,__out CString& strErr);

   BOOL GetPrintCount(__in CADOConn *pADOConn,__in CString& strOrder,__out CDBOrdFlagInfo* pData);
#ifdef USING_GRIDCTRL_MARK

#endif // USING_GRIDCTRL_MARK
};