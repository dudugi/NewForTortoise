/*************************************************
// <�ļ�>: DBStyle_CheckRecords.h
// <˵��>: ��¼���Ŷ�Ӧ���ļ�����
// <����>: wangzl
// <����>: 2019/02/22
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
#pragma once

#include "DataMid.h"

class CDBStyle_CheckRecordsData : public CDataMid
{
   DECLARE_SERIAL( CDBStyle_CheckRecordsData )//���л������л�����Ҫ��ӵ�����
public:
   CDBStyle_CheckRecordsData(void);
   ~CDBStyle_CheckRecordsData(void);   
public:
   enum {
      en_CheckIn = 0,//���� -- �������
      en_CheckOut,//���  --�޸�
   };
public:
   INT64    m_nID          ;//ID
   int      m_nStyleID     ;//��ʽID
   CString  m_strPerson    ;//������
   int      m_nState       ;//������״̬
   CString  m_strRecordTime;//����ʱ��

public:
   void ResetData();
   void Copy(CDBStyle_CheckRecordsData *);
   BOOL GetAllDBInfo(CADOConn *pADOConn);

   BOOL InsertAllDBInfo(CADOConn * pADOConn);


   CString GetInsertSQL() const;
};

class CDBStyle_CheckRecordsList : public CDataListMid
{
   DECLARE_SERIAL(CDBStyle_CheckRecordsList)
public:
   CDBStyle_CheckRecordsList();
   ~CDBStyle_CheckRecordsList(); 
};

