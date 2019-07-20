/*************************************************
// <�ļ�>: DBStyle_VersionRecords.h
// <˵��>: ��¼���Ŷ�Ӧ���ļ�����
// <����>: wangzl
// <����>: 2019/02/22
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
#pragma once

#include "DataMid.h"

class CDBStyle_VersionRecordsData : public CDataMid
{
   DECLARE_SERIAL( CDBStyle_VersionRecordsData )//���л������л�����Ҫ��ӵ�����
public:
   CDBStyle_VersionRecordsData(void);
   ~CDBStyle_VersionRecordsData(void);   
public:
   enum {
      en_Working = 0       ,//������
      en_FixVersion_Apply  ,//��������
      en_FixVersion_Check  ,//����
      en_ChangeVersion_Apply,//�İ�����
   };
public:
   INT64    m_nID          ;//ID
   int      m_nStyleID     ;//��ʽID
   CString  m_strPerson    ;//������
   int      m_nState       ;//����İ�״̬
   CString  m_strRecordTime;//����ʱ��
   CString  m_strRemark    ;//��ע

public:
   void ResetData();
   void Copy(CDBStyle_VersionRecordsData *);
   BOOL GetAllDBInfo(CADOConn *pADOConn);

   BOOL InsertAllDBInfo(CADOConn * pADOConn);


   CString GetInsertSQL() const;
};


