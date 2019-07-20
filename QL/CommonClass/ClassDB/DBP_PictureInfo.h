/*************************************************
// <�ļ�>: DBP_PictureInfo.h
// <˵��>: ����-ͼƬ��Ϣ
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

class CDBP_PictureInfoData : public CDBProofingAssociatedData
{
   DECLARE_SERIAL( CDBP_PictureInfoData)//���л������л�����Ҫ��ӵ�����
public:
   CDBP_PictureInfoData(void);
   ~CDBP_PictureInfoData(void);
public:
   int                  m_nPicType           ;
   __int64              m_nAssociatedFileID  ;
   CString              m_strcRemark         ;

   void ResetData();
   void Copy(CDBP_PictureInfoData *pData);
   BOOL GetAllDBInfoByID(CADOConn *pADOConn,int nID);				//��ȡ����������Ϣ
   BOOL InsertAllDBInfo(CADOConn *pADOConn);	//���롾�������¼�¼
   BOOL UpdateAllDBInfoByID(CADOConn *pADOConn);	//�����û��˻����¡���������¼
   BOOL DelAllDBInfoByID(CADOConn *pADOConn);		//�����û��˻�ɾ������������¼
};

class CDBP_PictureInfoList :public CDataListMid
{
   DECLARE_SERIAL( CDBP_PictureInfoList)//���л������л�����Ҫ��ӵ�����
public:
   CDBP_PictureInfoList(void);
   ~CDBP_PictureInfoList(void);
public:
   void Copy(CDBP_PictureInfoList *pList);
   void AddItem(CDBP_PictureInfoData *pItem);
   void DeleteItemByIndex(int nIndex);
};

