#pragma once
#include "DataMid.h"
#include "DBKeyDef.h"
#include "DBDef.h"
#include "stdafx.h"
#include "DBProofingAssociatedInfo.h"

/*************************************************
// <文件>: DBColorInfo.h
// <说明>: 打样-主色配色信息表相关类
// <作者>: anj
// <日期>: 2019/02/22
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 
class CDBColorInfoData : public CDBProofingAssociatedData
{
   DECLARE_SERIAL( CDBColorInfoData)//序列化（串行化）需要添加的声明
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
   BOOL GetAllDBInfoByID(CADOConn *pADOConn,int nID);				//获取【整条】信息
   BOOL InsertAllDBInfo(CADOConn *pADOConn);	//插入【整条】新记录
   BOOL UpdateAllDBInfoByID(CADOConn *pADOConn);	//根据用户账户更新【整条】记录
   BOOL DelAllDBInfoByID(CADOConn *pADOConn);		//根据用户账户删除【整条】记录
};

class CDBColorInfoList :public CDataListMid
{
   DECLARE_SERIAL( CDBColorInfoList)//序列化（串行化）需要添加的声明
public:
   CDBColorInfoList(void);
   ~CDBColorInfoList(void);
public:
   void Copy(CDBColorInfoList *pList);
   void AddItem(CDBColorInfoData *pItem);
   void DeleteItemByIndex(int nIndex);
};
