#pragma once
#include "DataMid.h"
#include "DBKeyDef.h"
#include "DBDef.h"
#include "stdafx.h"
#include "DBProofingAssociatedInfo.h"

/*************************************************
// <�ļ�>: DBColorInfo.h
// <˵��>: ����-��ɫ��ɫ��Ϣ�������
// <����>: anj
// <����>: 2019/02/22
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
class CDBColorInfoData : public CDBProofingAssociatedData
{
   DECLARE_SERIAL( CDBColorInfoData)//���л������л�����Ҫ��ӵ�����
public:
   CDBColorInfoData(void);
   ~CDBColorInfoData(void);
   enum EM_COLOR
   {
      EM_COLOR_Z,
      EM_COLOR_P,
   };
public:
   EM_COLOR                  m_nColorType         ;
   __int64               m_nAssociatedColorID ;

   void ResetData();
   void Copy(CDBColorInfoData *pData);
   BOOL GetAllDBInfoByID(CADOConn *pADOConn,int nID);				//��ȡ����������Ϣ
   BOOL InsertAllDBInfo(CADOConn *pADOConn);	//���롾�������¼�¼
   BOOL UpdateAllDBInfoByID(CADOConn *pADOConn);	//�����û��˻����¡���������¼
   BOOL DelAllDBInfoByID(CADOConn *pADOConn);		//�����û��˻�ɾ������������¼
};

class CDBColorInfoList :public CDataListMid
{
   DECLARE_SERIAL( CDBColorInfoList)//���л������л�����Ҫ��ӵ�����
public:
   CDBColorInfoList(void);
   ~CDBColorInfoList(void);
public:
   void Copy(CDBColorInfoList *pList);
   void AddItem(CDBColorInfoData *pItem);
   void DeleteItemByIndex(int nIndex);
};
