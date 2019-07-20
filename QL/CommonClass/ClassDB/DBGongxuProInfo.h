/*************************************************
// <�ļ�>: DBGongxuProInfo.h
// <˵��>: ���ݲ�����-���򷽰���
// <����>: yangjr
// <����>: 2019/02/20 16:09:37
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
#pragma once

#include "DataMid.h"
#include "DBKeyDef.h"
#include "DBKeyDef_V.h"
#include "DBKeyDef_Cust.h"


class CADOConn;
//���򷽰�
class CDBGongxuProInfoData  : public CDataMid
{
	DECLARE_SERIAL( CDBGongxuProInfoData)//���л������л�����Ҫ��ӵ�����
public:
	CString					m_ID;		//����
	CString			m_strProName;		//������
	CString   m_strProcedureName;		//������
   CString   m_strZhiPaiPerson;     //ָ����
public:
	CDBGongxuProInfoData();
	~CDBGongxuProInfoData();
	void ResetData();
	void Copy(CDBGongxuProInfoData *pData);

	//��ȡ���򷽰�����������Ϣ
	BOOL GetAllDBInfo(CADOConn *pADOConn);
	//ɾ������������¼		
	BOOL DelAllDBInfo(CADOConn *pADOConn);
	//���ӡ���������¼		
	BOOL InsertAllDBInfo(CADOConn *pADOConn);
	//���¡���������¼	
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
	// ��ȡ���򷽰��б�
	void GetGongxuProNameLst(std::vector<CString> &nameLst);
	// ���ݹ��򷽰�����ȡ�����б�
	void GetGongxuProByGongxuProName(std::vector<CString> &productionLst , CString proName);
   //���ݹ��򷽰�����ȡ�����б��ָ����
   void GetGongxuProAndZhipaiPersonByGongxuProName(std::vector<pair<CString,CString>> &productionLst , CString proName);
	// ��ӹ��򷽰�
	BOOL AddGongxuProByGongxuProName(std::vector<CString> productionLst , CString proName);
   BOOL AddGongxuProAndZhipaiPersonByGongxuProName(std::vector<pair<CString,CString>> productionLst , CString proName);
	// ���¹��򷽰�
	BOOL UpdateGongxuProByGongxuProName(std::vector<CString> productionLst , CString proName , CString oldProName);
   BOOL UpdateGongxuProAndZhipaiPersonByGongxuProName(std::vector<pair<CString,CString>> productionLst , CString proName , CString oldProName);
	// ɾ�����򷽰�
	BOOL DeleteGongxuProByGongxuProName(CString proName);

	static CDBGongxuProInfoDataList * Instance();//��ȡ��ָ�룩ʵ��
private:
	static std::shared_ptr<CDBGongxuProInfoDataList> sm_inst;
	CADOConn *m_pADOConn;
};