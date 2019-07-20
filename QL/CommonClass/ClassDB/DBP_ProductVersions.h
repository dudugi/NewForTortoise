/*************************************************
// <�ļ�>: DBP_ProductVersions.h
// <˵��>: ��Ʒ�汾��Ϣ��
// <����>: wangzl
// <����>: 2019/02/22
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
#pragma once
#include "DataMid.h"
#include "DBKeyDef.h"

class CADOConn;

class CDBP_ProductVersionsData  : public CDataMid
{
   DECLARE_SERIAL( CDBP_ProductVersionsData)//���л������л�����Ҫ��ӵ�����
public:
   __int64  m_nID                ;//
   __int64  m_nProductID         ;//��Ʒ
   CString  m_strVersion         ;//�汾
   int      m_nVersionNo         ;//�汾��
   CString  m_strCode            ;//������
   CString  m_strAlias           ;//����
public:
   CDBP_ProductVersionsData();
   ~CDBP_ProductVersionsData();
   void ResetData();
   void Copy(CDBP_ProductVersionsData *pData);
   BOOL GetAllDBInfo(CADOConn *pADOConn);
   BOOL DelAllDBInfoByID(CADOConn *pADOConn);
   BOOL UpdateAllDBInfoByID(CADOConn *pADOConn);
   BOOL InsertAllDBInfo(CADOConn *pADOConn);

   void Trim();

};

class CDBP_ProductVersionsList : public CDataListMid
{
   DECLARE_SERIAL(CDBP_ProductVersionsList)
public:
   CDBP_ProductVersionsList();
   ~CDBP_ProductVersionsList();
   CDBP_ProductVersionsData*  GetItem(int nIndex);
   void    AddItem(CDBP_ProductVersionsData* pItem);
   void    DeleteItem(int nIndex);

   static CDBP_ProductVersionsList * Instance();//��ȡ��ָ�룩ʵ��

private:
   static std::shared_ptr<CDBP_ProductVersionsList> sm_inst;
};