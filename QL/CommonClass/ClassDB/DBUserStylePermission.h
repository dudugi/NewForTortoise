/*************************************************
// <�ļ�>: DBUserStylePermission.h
// <˵��>: �û���ʽȨ��DB�� ���ڱ��Ա���Կ�ʽ��Ȩ��
// <����>: wangzl
// <����>: 2019/05/06
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
#pragma once
#include "DataMid.h"
#include "DBKeyDef.h"

//Ȩ�����ֵΪ 7 

class CDBUserStylePermissionData : public CDataMid
{
   DECLARE_SERIAL( CDBUserStylePermissionData)//���л������л�����Ҫ��ӵ�����
public:
   CDBUserStylePermissionData(void);
   ~CDBUserStylePermissionData(void);

   typedef enum EM_PERMISSION
   {
      en_Read = 1,//�ɶ�
      en_Edit = 2,//�ɱ༭
      en_Del  = 4,//��ɾ��
      en_All  = 7,//����Ȩ��
   };

   INT64       m_nID          ;//
   int         m_nUserID      ;//Ա��ID
   int         m_nStyleID     ;//��ʽID
   int         m_nPermission  ;//Ȩ�� ����unix���ļ�Ȩ��
   CString     m_cPermissionTime ;//Ȩ����Ч����
public:
   void ResetData();
   void Copy(CDBUserStylePermissionData *pData);
   BOOL GetAllDBInfo(CADOConn *pADOConn);				//��ȡ����������Ϣ
   BOOL InsertAllDBInfo(CADOConn *pADOConn);	//���롾�������¼�¼
   BOOL UpdateAllDBInfoByID(CADOConn *pADOConn);	//�����û��˻����¡���������¼
   BOOL DelAllDBInfoByID(CADOConn *pADOConn);		//�����û��˻�ɾ������������¼
};

class CDBUserStylePermissionList :public CDataListMid
{
   DECLARE_SERIAL( CDBUserStylePermissionList)//���л������л�����Ҫ��ӵ�����
public:
   CDBUserStylePermissionList(void);
   ~CDBUserStylePermissionList(void);
public:
   void Copy(CDBUserStylePermissionList *pList);
   CDBUserStylePermissionData*  GetItem(int nIndex);
   void AddItem(CDBUserStylePermissionData *pItem);
   void DeleteItemByIndex(int nIndex);
};
