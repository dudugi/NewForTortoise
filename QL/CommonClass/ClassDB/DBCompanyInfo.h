/*************************************************
// <�ļ�>: DBCompanyInfo.h
// <˵��>: ��˾��Ϣ����DB��
// <����>: WangZY
// <����>: 2019/02/22 17:33:36
// Copyright (C), 2016-2020, �������. Co., Ltd.
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
	DECLARE_SERIAL( CDBCompanyInfo)//���л������л�����Ҫ��ӵ�����
public:
	int m_nID; 
	CString m_strCompanyName;		//��˾����
	CString m_strCompanyTel;		//��˾�绰
	CString m_strCompanyFax;		//��˾����
	CString m_strCompanyAddress;	//��˾��ַ
#if COMPANYSIGN_IMAGE
	Image*				m_pCompanySign;//��˾��־ͼƬ
#endif
public:
	CDBCompanyInfo(void);
	~CDBCompanyInfo(void);
	void Trim();
	void ResetData();
	void Copy(CDBCompanyInfo *pData);
	void Serialize(CArchive& ar);
	BOOL GetAllDBInfo(CADOConn *pADOConn);		//��ȡ��˾����������Ϣ
	BOOL InsertAllDBInfo( CADOConn *pADOConn );
	BOOL UpdateAllDBInfo(CADOConn *pADOConn);	//���¹�˾һ����Ϣ,����ֻ��һ����¼
	BOOL UpdateAllDBInfoByID(CADOConn *pADOConn);
	static CDBCompanyInfo * Instance();//��ȡ��ָ�룩ʵ��

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
	static CDBCompanyInfoList * Instance();//��ȡ��ָ�룩ʵ��
private:
	static std::shared_ptr<CDBCompanyInfoList> sm_inst;
};
