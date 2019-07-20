/*************************************************
// <�ļ�>: DBStyle_Basic_FieldSet.h
// <˵��>: ��ʽ������Ϣ�ֶα�
// <����>: wangzl
// <����>: 2019/07/01
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
#pragma once
#include "DataMid.h"
class CADOConn;

class CDBStyle_Basic_FieldSetData  : public CDataMid
{
   DECLARE_SERIAL(CDBStyle_Basic_FieldSetData)//���л������л�����Ҫ��ӵ�����
public:
   CString  m_strColID        ;//��ID
   CString  m_strDisplayName  ;//��ʾ����
   BOOL     m_bShow           ;//�Ƿ���ʾ
   int      m_nSortIndex      ;//��������
   BOOL     m_bOnPanel        ;//�Ƿ���ʾ�������


public:
   CDBStyle_Basic_FieldSetData();
   ~CDBStyle_Basic_FieldSetData();
   void ResetData();
   void Copy(CDBStyle_Basic_FieldSetData *pData);
   BOOL GetAllDBInfo(CADOConn *pADOConn);
   CString GetInsertSQL() const;
};

class CDBStyle_Basic_FieldSetList : public CTDataListMid<CDBStyle_Basic_FieldSetList,CDBStyle_Basic_FieldSetData>
{
public:
   CDBStyle_Basic_FieldSetList();
   ~CDBStyle_Basic_FieldSetList();

   BOOL GetListFromDB(CADOConn *);

   std::vector<pair<CString/*Field*/,CString/*oldName*/>> & GetDefineBasicFieldInfo();

   static CDBStyle_Basic_FieldSetList * Instance();					//��ȡ��ָ�룩ʵ��
private:
   static std::shared_ptr<CDBStyle_Basic_FieldSetList> sm_inst;
};