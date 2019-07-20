/*************************************************
// <�ļ�>: DBStyleSizeExtra.h
// <˵��>: ��ʽ�ߴ����������
// <����>: yangjr
// <����>: 2019/07/14 14:29:45
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 

#pragma once

#include "DataMid.h"
#include <map>

//���ݿ����ֶ�
class CADOConn;
class CDBStyleSizeExtraData  : public CDataMid
{
	DECLARE_SERIAL( CDBStyleSizeExtraData)//���л������л�����Ҫ��ӵ�����
public:
   int               m_nID;  
   CString           m_cStyleNo         ;//���
   int               m_iPartID        ;//�ߴ粿λ
   CString           m_cMemo;//��λ˵��
   double            m_fCeLiangBeforeSize;//����ǰ�ߴ�
   double            m_fCeLiangCusSize;//�ͻ������ߴ�
   double            m_fWaterBeforeSize;//ϴˮǰ�ߴ�
   double            m_fWaterAfterSize;//ϴˮ��ߴ�
public:
	CDBStyleSizeExtraData();
	~CDBStyleSizeExtraData();
	void ResetData();
	void Copy(CDBStyleSizeExtraData *pData);
	void Serialize(CArchive& ar);

	//���ݿ��������
	BOOL GetAllDBInfo(CADOConn *pADOConn);			//��ȡ����������Ϣ
	BOOL InsertAllDBInfo(CADOConn *pADOConn);		//���롾�������¼�¼
	BOOL UpdateAllDBInfoByID(CADOConn *pADOConn);	//�����û��˻����¡���������¼
	BOOL DelAllDBInfoByID(CADOConn *pADOConn);		//�����û��˻�ɾ������������¼
   BOOL DelAllDBInfoByStyleNo(CADOConn *pADOConn);
   CString GetDelAllDBInfoByStyleNo(CString strStyleNo);
   CString GetInsertAllDBInfoSql();
	static CDBStyleSizeExtraData * Instance();		//��ȡ��ָ�룩ʵ��

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
	void GetListFromDB(CADOConn *pADOConn);		//�����ݿ��ȡ����
	static CDBStyleSizeExtraList * Instance();	//��ȡ��ָ�룩ʵ��
   void GetListFromDBByStyleNo(CADOConn *pADOConn,CString strStyleNo);

private:
	static std::shared_ptr<CDBStyleSizeExtraList> sm_inst;
};



