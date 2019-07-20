/*************************************************
// <文件>: DBP_MatetialInfo.h
// <说明>: 打样-物料信息表
// <作者>: wangzl
// <日期>: 2019/02/22
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/
#pragma once
#include "DataMid.h"
#include "DBKeyDef.h"
#include "DBDef.h"
#include "stdafx.h"
#include "DBProofingAssociatedInfo.h"
 
class CDBP_MatetialInfoData : public CDBProofingAssociatedData
{
   DECLARE_SERIAL( CDBP_MatetialInfoData)//序列化（串行化）需要添加的声明
public:
   CDBP_MatetialInfoData(void);
   ~CDBP_MatetialInfoData(void);
public:
   CString              m_strAssociatedMaterialID ;

   void ResetData();
   void Copy(CDBP_MatetialInfoData *pData);
   BOOL GetAllDBInfoByID(CADOConn *pADOConn,int nID);				//获取【整条】信息
   BOOL InsertAllDBInfo(CADOConn *pADOConn);	//插入【整条】新记录
   BOOL UpdateAllDBInfoByID(CADOConn *pADOConn);	//根据用户账户更新【整条】记录
   BOOL DelAllDBInfoByID(CADOConn *pADOConn);		//根据用户账户删除【整条】记录
};

class CDBP_MatetialInfoList :public CDataListMid
{
   DECLARE_SERIAL( CDBP_MatetialInfoList)//序列化（串行化）需要添加的声明
public:
   CDBP_MatetialInfoList(void);
   ~CDBP_MatetialInfoList(void);
public:
   void Copy(CDBP_MatetialInfoList *pList);
   void AddItem(CDBP_MatetialInfoData *pItem);
   void DeleteItemByIndex(int nIndex);
};