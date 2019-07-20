/*************************************************
// <�ļ�>: DBUserStylePermission_V.h
// <˵��>: �û���ʽȨ����ͼDB�� ���ڱ��Ա���Կ�ʽ��Ȩ��
// <����>: wangzl
// <����>: 2019/05/06
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
#pragma once
#include "DataMid.h"

class CDBConfig_TagNameData : public CDataMid
{
   DECLARE_SERIAL( CDBConfig_TagNameData)//���л������л�����Ҫ��ӵ�����
public:
   CDBConfig_TagNameData(void);
   ~CDBConfig_TagNameData(void);

   CString m_strTagName    ;//��ǩ����
   CString m_strDisplayName;//��ʾ����
   int     m_nHide;//�Ƿ����� yangjr 2019/07/09    
public:
   void ResetData();
   void Copy(CDBConfig_TagNameData *pData);
   BOOL GetAllDBInfo(CADOConn *pADOConn);				//��ȡ����������Ϣ
   BOOL UpdateAllDBInfo(CADOConn * pADOConn);

   CString GetUpdateSQL();
   CString GetInsertSQL();

   BOOL InsertAllDBInfo(CADOConn * pADOConn);
};

class CDBConfig_TagNameList :public CDataListMid
{
   DECLARE_SERIAL( CDBConfig_TagNameList)//���л������л�����Ҫ��ӵ�����
public:
   CDBConfig_TagNameList(void);
   ~CDBConfig_TagNameList(void);
public:
   void Copy(CDBConfig_TagNameList *pList);
   CDBConfig_TagNameData*  GetItem(int nIndex);
   CDBConfig_TagNameData*  GetItemByTagName(const CString & strTagName);
   void AddItem(CDBConfig_TagNameData *pItem);
   void DeleteItemByIndex(int nIndex);
   //��ȡ��Ӧ��ǩ����ʾ����
   CString GetItemDisplayName(const CString & strTagName);

   BOOL GetListFromDB(CADOConn *);

   static CDBConfig_TagNameList * Instance();//��ȡ��ָ�룩ʵ��
private:
   static std::shared_ptr<CDBConfig_TagNameList> sm_inst;
};
