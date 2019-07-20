/*************************************************
// <�ļ�>: DBP_MatetialInfo.h
// <˵��>: ����-������Ϣ��
// <����>: wangzl
// <����>: 2019/02/22
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/
#pragma once
#include "DataMid.h"
#include "DBKeyDef.h"
#include "DBDef.h"
#include "stdafx.h"
#include "DBProofingAssociatedInfo.h"
 
class CDBP_MatetialInfoData : public CDBProofingAssociatedData
{
   DECLARE_SERIAL( CDBP_MatetialInfoData)//���л������л�����Ҫ��ӵ�����
public:
   CDBP_MatetialInfoData(void);
   ~CDBP_MatetialInfoData(void);
public:
   CString              m_strAssociatedMaterialID ;

   void ResetData();
   void Copy(CDBP_MatetialInfoData *pData);
   BOOL GetAllDBInfoByID(CADOConn *pADOConn,int nID);				//��ȡ����������Ϣ
   BOOL InsertAllDBInfo(CADOConn *pADOConn);	//���롾�������¼�¼
   BOOL UpdateAllDBInfoByID(CADOConn *pADOConn);	//�����û��˻����¡���������¼
   BOOL DelAllDBInfoByID(CADOConn *pADOConn);		//�����û��˻�ɾ������������¼
};

class CDBP_MatetialInfoList :public CDataListMid
{
   DECLARE_SERIAL( CDBP_MatetialInfoList)//���л������л�����Ҫ��ӵ�����
public:
   CDBP_MatetialInfoList(void);
   ~CDBP_MatetialInfoList(void);
public:
   void Copy(CDBP_MatetialInfoList *pList);
   void AddItem(CDBP_MatetialInfoData *pItem);
   void DeleteItemByIndex(int nIndex);
};