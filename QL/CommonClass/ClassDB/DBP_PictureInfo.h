/*************************************************
// <文件>: DBP_PictureInfo.h
// <说明>: 打样-图片信息
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

class CDBP_PictureInfoData : public CDBProofingAssociatedData
{
   DECLARE_SERIAL( CDBP_PictureInfoData)//序列化（串行化）需要添加的声明
public:
   CDBP_PictureInfoData(void);
   ~CDBP_PictureInfoData(void);
public:
   int                  m_nPicType           ;
   __int64              m_nAssociatedFileID  ;
   CString              m_strcRemark         ;

   void ResetData();
   void Copy(CDBP_PictureInfoData *pData);
   BOOL GetAllDBInfoByID(CADOConn *pADOConn,int nID);				//获取【整条】信息
   BOOL InsertAllDBInfo(CADOConn *pADOConn);	//插入【整条】新记录
   BOOL UpdateAllDBInfoByID(CADOConn *pADOConn);	//根据用户账户更新【整条】记录
   BOOL DelAllDBInfoByID(CADOConn *pADOConn);		//根据用户账户删除【整条】记录
};

class CDBP_PictureInfoList :public CDataListMid
{
   DECLARE_SERIAL( CDBP_PictureInfoList)//序列化（串行化）需要添加的声明
public:
   CDBP_PictureInfoList(void);
   ~CDBP_PictureInfoList(void);
public:
   void Copy(CDBP_PictureInfoList *pList);
   void AddItem(CDBP_PictureInfoData *pItem);
   void DeleteItemByIndex(int nIndex);
};

