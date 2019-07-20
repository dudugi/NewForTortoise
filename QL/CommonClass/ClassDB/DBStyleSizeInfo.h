/*************************************************
// <�ļ�>: DBStyleSizeInfo.h
// <˵��>: �淿��ʽ����--�ߴ���Ϣ
// <����>: liuhw
// <����>: 2019/05/09 14:16:45
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
#pragma once

#include "DataMid.h"
#include <map>

//���ݿ����ֶ�
class CADOConn;

class CDBStyleChiMaInfoData  : public CDataMid
{
	DECLARE_SERIAL( CDBStyleChiMaInfoData)//���л������л�����Ҫ��ӵ�����
public:
   __int64 m_nID;//ID
   CString m_cKuanhao;//���
   CString m_cChima;//����
   int     m_iBase;//�Ƿ�Ϊ����
public:
	CDBStyleChiMaInfoData();
	~CDBStyleChiMaInfoData();
	void ResetData();
	void Copy(CDBStyleChiMaInfoData *pData);
	void Serialize(CArchive& ar);
   BOOL IsBasicMa(CADOConn *pADOConn);//�ж��Ƿ�Ϊ����
	//���ݿ��������
	BOOL GetAllDBInfo(CADOConn *pADOConn);			//��ȡ����������Ϣ
	BOOL InsertAllDBInfo(CADOConn *pADOConn);		//���롾�������¼�¼
   void GetInsertAllDBSql(CString &strSql);
	BOOL UpdateAllDBInfoByID(CADOConn *pADOConn);	//�����û��˻����¡���������¼
	BOOL DelAllDBInfoByID(CADOConn *pADOConn);		//�����û��˻�ɾ������������¼
   BOOL DelAllDBInfoByStyleNo(CADOConn *pADOConn);
   CString GetDelAllDBInfoByStyleNoSql(CString strStyleNo);
	static CDBStyleChiMaInfoData * Instance();		//��ȡ��ָ�룩ʵ��

private:
	static std::shared_ptr<CDBStyleChiMaInfoData> sm_inst;
};

class CDBStyleChiMaInfoList : public CDataListMid
{
	DECLARE_SERIAL(CDBStyleChiMaInfoList)
public:
	CDBStyleChiMaInfoList();
	~CDBStyleChiMaInfoList();
	CDBStyleChiMaInfoData*  GetItem(int nIndex);
	void    AddItem(CDBStyleChiMaInfoData* pItem);
	void    DeleteItem(int nIndex);
   
	static CDBStyleChiMaInfoList * Instance();	//��ȡ��ָ�룩ʵ��
private:
	static std::shared_ptr<CDBStyleChiMaInfoList> sm_inst;
};

class CDBStyleSizeInfoData  : public CDataMid
{
	DECLARE_SERIAL( CDBStyleSizeInfoData)//���л������л�����Ҫ��ӵ�����
public:
   __int64 m_nID;        //ID
   CString m_cKuanhao;   //���
   CString m_cChima;     //����
   int     m_iPartID;    //��λID
   double  m_fSize;      //�ߴ�
   CString m_strSize;      //�ߴ� �ַ���,ֻ������������͸���
   CString m_cFangAn;  //��ʽ�ĳߴ緽������
public:
	CDBStyleSizeInfoData();
	~CDBStyleSizeInfoData();
	void ResetData();
	void Copy(CDBStyleSizeInfoData *pData);
	void Serialize(CArchive& ar);
	BOOL InsertAllDBInfo(CADOConn *pADOConn);	//���롾�������¼�¼
   BOOL UpdateAllDBInfoByID(CADOConn *pADOConn);	//�����û��˻����¡���������¼
   void GetUpdateAllDBInfoByStyleNo(CString &strSql);
   void GetInsertAllDBInfo(CString &strSQL);
   BOOL DelAllDBInfoByID(CADOConn *pADOConn);
   BOOL DelAllDBInfoByStyleNo(CADOConn *pADOConn);
   CString GetDelAllDBInfoByStyleNoSql(CString strStyleNo);
   void GetAllDBInfo(CADOConn *pADOConn);
	static CDBStyleSizeInfoData * Instance();	//��ȡ��ָ�룩ʵ��
private:
	static std::shared_ptr<CDBStyleSizeInfoData> sm_inst;
};

class CDBStyleSizeInfoList : public CDataListMid
{
	DECLARE_SERIAL(CDBStyleSizeInfoList)
public:
	CDBStyleSizeInfoList();
	~CDBStyleSizeInfoList();
   CDBStyleSizeInfoData*  GetItem(int nIndex);
   void  AddItem(CDBStyleSizeInfoData* pItem);
   void  DeleteItem(int nIndex);
   void  DeleteAllList();
   BOOL  GetStyleNoAllDBInfo(CADOConn *pADOConn,CString strStyleNo,CString &strBasicMa);//��ȡ�ÿ�ʽ��������Ϣ

   BOOL  GetStyleNoAllDBInfo(CADOConn *pADOConn,CString strStyleNo,BOOL bDecimalPoint = FALSE);//��ȡ�ÿ�ʽ��������Ϣ bDecimalPoint Ҫ��ҪС����

   void  CopyList(CDBStyleSizeInfoList* pList);
   BOOL  InsertAllDBListInfo(CADOConn *pADOConn);
   map<int,map<CString,CString>> CreateMapSizeData();//���ز�λΪKEY�����룬���ߴ�Ϊvalue
	static CDBStyleSizeInfoList * Instance();	//��ȡ��ָ�룩ʵ��

private:
	static std::shared_ptr<CDBStyleSizeInfoList> sm_inst;
};



