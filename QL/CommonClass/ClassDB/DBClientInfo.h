/*************************************************
// <�ļ�>: DBClientInfo.h
// <˵��>: �û���Ϣ��¼����������DB��
// <����>: WangZY
// <����>: 2019/02/22 17:25:24
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
#pragma once

#include <map>
#include "DataMid.h"
#include "DBKeyDef.h"

class CADOConn;

class CDBClientVarifyInfo  : public CDataMid
{
	DECLARE_SERIAL( CDBClientVarifyInfo)//���л������л�����Ҫ��ӵ�����
public:
   CString				m_strID;			   //ID
   CString	         m_strUserId;		//�û�ID
   CString			   m_strVarifyTime;	//ʱ��
   CString			   m_strMacInfo;	   //������Ϣ

   int               m_nOutTime;       //����ʱ�䣺����

public:
	CDBClientVarifyInfo();
	~CDBClientVarifyInfo();
	void ResetData();
	void Copy(CDBClientVarifyInfo *pData);
	void Serialize(CArchive& ar);
	BOOL GetAllDBInfo(CADOConn *pADOConn);		      //��ȡɴ�ߡ���������Ϣ
	BOOL DelAllDBInfoByID(CADOConn *pADOConn);		//ɾ������������¼
	BOOL UpdateAllDBInfoByID(CADOConn *pADOConn);	//����ɴ�ߺŸ��¡���������¼
	BOOL InsertAllDBInfoByID(CADOConn *pADOConn);	//����ɴ�ߺŲ��롾��������¼
   
   BOOL UpdateHeartbeetTimeById(CADOConn *pADOConn);   //��������ʱ��

   //BOOL UpdateHeartbeetTimeAndUserIdById();

   BOOL InsertAllDBInfoByUserAndMacID(CADOConn *pADOConn);

   static BOOL DeleteDBInfoByUserId(CADOConn *pADOConn,CString strUserId);

   static BOOL DeleteDBInfoByUserAndMacId(CADOConn *pADOConn,CString strUserId,CString strMacId);

   void Trim();
	static CDBClientVarifyInfo * Instance();//��ȡ��ָ�룩ʵ��

private:
	static std::shared_ptr<CDBClientVarifyInfo> sm_inst;
};

class CDBClientVarifyInfoList : public CDataListMid
{
	DECLARE_SERIAL(CDBClientVarifyInfoList)
public:
	CDBClientVarifyInfoList();
	~CDBClientVarifyInfoList();

   static CDBClientVarifyInfoList * Instance();//��ȡ��ָ�룩ʵ��

	CDBClientVarifyInfo*  GetItem(int nIndex);
	void    AddItem(CDBClientVarifyInfo* pItem);
	void    DeleteItem(int nIndex);
	CDBClientVarifyInfo* GetItemById(CString strId);
	int GetIndexById(CString strId);
   int GetIndexByMacIdAndUserId(CString strMacId,CString strUserId);

	void GetListFromDB(CADOConn *pADOConn);//�����ݿ��ȡ����
	

   BOOL GetInfoById(__in CADOConn *pADOConn,__in CString strId,
      __out CDBClientVarifyInfo* pObj);

   CDBClientVarifyInfo* GetItemByMacIdAndUserId(CString strMacId,CString strUserId);

   CDBClientVarifyInfo* GetItemByMacId(CString strMacId);
   CDBClientVarifyInfo* GetItemByUserId(CString strUserId);
   


private:
	static std::shared_ptr<CDBClientVarifyInfoList> sm_inst;
};