/*************************************************
// <�ļ�>: DBUserStylePermission_V.h
// <˵��>: �û���ʽȨ����ͼDB�� ���ڱ��Ա���Կ�ʽ��Ȩ��
// <����>: wangzl
// <����>: 2019/05/06
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
#pragma once
#include "DataMid.h"
#include <tuple>

class CDBKuanshi_NextProInfo_VData : public CDataMid
{
   DECLARE_SERIAL( CDBKuanshi_NextProInfo_VData)//���л������л�����Ҫ��ӵ�����
public:
   CDBKuanshi_NextProInfo_VData(void);
   ~CDBKuanshi_NextProInfo_VData(void);

   CString m_strStyleNo    ;//���
   CString m_strProcessName;//������
   CString m_strNextUserID ;//��һ�������Ӧ��ִ����

public:
   void ResetData();
   void Copy(CDBKuanshi_NextProInfo_VData *pData);
   BOOL GetAllDBInfo(CADOConn *pADOConn);				//��ȡ����������Ϣ
};

class CDBKuanshi_NextProInfo_VList :public CDataListMid
{
   DECLARE_SERIAL( CDBKuanshi_NextProInfo_VList)//���л������л�����Ҫ��ӵ�����
public:
   CDBKuanshi_NextProInfo_VList(void);
   ~CDBKuanshi_NextProInfo_VList(void);
public:
   void Copy(CDBKuanshi_NextProInfo_VList *pList);
   CDBKuanshi_NextProInfo_VData*  GetItem(int nIndex);
   void AddItem(CDBKuanshi_NextProInfo_VData *pItem);
   void DeleteItemByIndex(int nIndex);
};
