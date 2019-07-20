/*************************************************
// <文件>: DBP_ProductVersions.h
// <说明>: 产品版本信息表
// <作者>: wangzl
// <日期>: 2019/02/22
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 
#pragma once
#include "DataMid.h"
#include "DBKeyDef.h"

class CADOConn;

class CDBP_ProductVersionsData  : public CDataMid
{
   DECLARE_SERIAL( CDBP_ProductVersionsData)//序列化（串行化）需要添加的声明
public:
   __int64  m_nID                ;//
   __int64  m_nProductID         ;//产品
   CString  m_strVersion         ;//版本
   int      m_nVersionNo         ;//版本号
   CString  m_strCode            ;//订单号
   CString  m_strAlias           ;//别名
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

   static CDBP_ProductVersionsList * Instance();//获取（指针）实例

private:
   static std::shared_ptr<CDBP_ProductVersionsList> sm_inst;
};