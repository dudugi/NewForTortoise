/*************************************************
// <�ļ�>: DBSizeInfo.h
// <˵��>: ������Ӧ�ĳ�����Ϣ��
// <����>: wangzl
// <����>: 2019/01/30 10:29:45
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 

#pragma once

#include "DataMid.h"
#include "SpecItem.h"
#include <map>

//���ݿ����ֶ�
class CADOConn;

class CDBSizePartInfoData  : public CDataMid
{
	DECLARE_SERIAL( CDBSizePartInfoData)//���л������л�����Ҫ��ӵ�����
public:
   __int64           m_nSizePartID     ;//��λ��ID
   CString           m_strName         ;//����(������)
   WORD              m_nDefault        ;//�Ƿ���Ĭ�ϵı�־
   int               m_nUserSort       ;//�û��Զ�������˳��
   CString           m_cMemo;//��λ˵�� yangjr 2019/07/14
   enum{
      En_PART_DEFAULT_NULL          = 0,//��
      En_PART_DEFAULT_CLOTHES       = 1,//Ĭ�� �·�
      En_PART_DEFAULT_TROUSERS      = 2,//Ĭ�� ����
      En_PART_DEFAULT_BOTH          = 3,//�·������Ӷ���
   };

public:
	CDBSizePartInfoData();
	~CDBSizePartInfoData();
	void ResetData();
	void Copy(CDBSizePartInfoData *pData);
	void Serialize(CArchive& ar);

	//���ݿ��������
	BOOL GetAllDBInfo(CADOConn *pADOConn);			//��ȡ����������Ϣ
	BOOL InsertAllDBInfo(CADOConn *pADOConn);		//���롾�������¼�¼
	BOOL UpdateAllDBInfoByID(CADOConn *pADOConn);	//�����û��˻����¡���������¼
	BOOL DelAllDBInfoByID(CADOConn *pADOConn);		//�����û��˻�ɾ������������¼
	static CDBSizePartInfoData * Instance();		//��ȡ��ָ�룩ʵ��

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

	void GetListFromDB(CADOConn *pADOConn);		//�����ݿ��ȡ����
	static CDBSizePartInfoList * Instance();	//��ȡ��ָ�룩ʵ��

   static BOOL GetPartSort(CADOConn* pAdo,map<CString,CString>& mapData);

private:
	static std::shared_ptr<CDBSizePartInfoList> sm_inst;
};



