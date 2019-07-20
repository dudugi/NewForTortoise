#pragma once
#include "DataMid.h"
#include "DBKeyDef.h"

using namespace std;

/*************************************************
// <�ļ�>: DBOrdFlag.h
// <˵��>: ������ӡ������
// <����>: lida
// <����>: 2019/02/22 15:49:09
// Copyright (C), 2016-2020, �������. Co., Ltd.
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

	static CDBOrdFlagInfo * Instance();//��ȡ��ָ�룩ʵ��

public:
	int			m_ID;
	CString		m_strOrdCode;
	int			m_iPrint_GYD;		//���յ���ӡ����
	int			m_iPrint_XSM;		//ϴˮ���ӡ����
	int			m_iPrint_SCZSD;		//����ָʾ����ӡ����
	int			m_iPrint_File;		//�ϻ��ļ����ش���

private:
	static std::shared_ptr<CDBOrdFlagInfo> sm_inst;
};

class CDBOrdFlagInfo_List : public CDataListMid
{
public:
	CDBOrdFlagInfo_List();
	~CDBOrdFlagInfo_List();
	static CDBOrdFlagInfo_List * Instance();//��ȡ��ָ�룩ʵ��

private:
	static std::shared_ptr<CDBOrdFlagInfo_List> sm_inst;

public:
	BOOL WriteOrderFlag(__in CADOConn *pADOConn,__in vector<CString>& vecOrder,__in BOOL bGYD,__in BOOL bXSM,__in BOOL bSCZSD,__in BOOL bFile,__out CString& strErr);

   BOOL GetPrintCount(__in CADOConn *pADOConn,__in CString& strOrder,__out CDBOrdFlagInfo* pData);
#ifdef USING_GRIDCTRL_MARK

#endif // USING_GRIDCTRL_MARK
};