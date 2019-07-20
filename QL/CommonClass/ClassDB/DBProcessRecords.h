/*************************************************
// <�ļ�>: DBProcessRecords.h
// <˵��>: �ӵ������¼��Ӧ����Ϣ��
// <����>: wangzl
// <����>: 2019/01/26 14:49:24
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
#pragma once
#include <vector>
#include "DataMid.h"
#include "DBDef.h"
#include <map>
#include "WeightUnitOp.h"

class CDBProcessRecordsData : public CDataMid
{
   DECLARE_SERIAL( CDBProcessRecordsData)//���л������л�����Ҫ��ӵ�����
public:
   CDBProcessRecordsData(void);
   ~CDBProcessRecordsData(void);
public:
   
public:
   INT64             m_nID                   ;//ָ�������ID������
   CString           m_strCode               ;//�����š�����
   CString           m_strGXName             ;//��������
   int               m_nState                ;//����״̬   ->  0δ��ʼ   1->������  2->���
   CString           m_strMemo               ;//��ע
   CString           m_strPersonCode         ;//��ָ��������
   double            m_fPieceWeight          ;//Ƭ��
   double            m_fDuration             ;//ʱ��
   double            m_fGongjia              ;//����
   CString           m_strRecordTime         ;//��¼ʱ��
   CString           m_strToPerson           ;//һЩ��������Ӧ��Ա��

   //Ĭ�Ϲ����Ӧ�Ĺ���IDֵ
   typedef enum{
      ASSIGN_ID_NONE = 0,//��ʼ������ID״̬
      ASSIGN_ID_PROCESS = 1,//����
      ASSIGN_ID_DESIGN,//���
      ASSIGN_ID_PATERN,//�ư�
      ASSIGN_ID_MAC,//�ϻ�
   }Assign_Default_ProID;
   //����״̬
   typedef enum{
      ASSIGN_STATE_UNBEG = -1,//����δ��ʼ
      ASSIGN_STATE_RUN,//���������
      ASSIGN_STATE_OVER,//�������
   }Assign_ProState;

   void ResetData();
   void Copy(CDBProcessRecordsData *pData);
   BOOL GetAllDBInfo(CADOConn *pADOConn);//��ȡ����������Ϣ
   BOOL InsertAllDBInfo(CADOConn *pADOConn);//���롾�������¼�¼

   //���ز����SQL��� ��Ҫ��ǰDB��������ص����� wangzl 2018-10-09
   CString GetInsertSQL() const;
   static CString GetDeleteByStyleNoSql(const CString & strStyleNo);

   //ȡ�������ַ����������ߵĿո�
   void Trim();

};

class CDBProcessRecordsList :public CDataListMid
{
   DECLARE_SERIAL( CDBProcessRecordsList)//���л������л�����Ҫ��ӵ�����
public:
   CDBProcessRecordsList(void);
   ~CDBProcessRecordsList(void);
public:
   CDBProcessRecordsData*  GetItem(int nIndex);
   CDBProcessRecordsData*  GetItem(CString strOrderNo);
   void    AddItem(CDBProcessRecordsData* pItem);
   void    DeleteItem(int nIndex);
   void    DeleteItem(CString strOrderNo);
   void    DeleteItemByID(__int64 nID);
};
