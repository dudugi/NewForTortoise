/*************************************************
// <文件>: DBP_TextBoard.h
// <说明>: 文字板
// <作者>: wangzl
// <日期>: 2019/02/22
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 
#pragma once
#include "DataMid.h"
#include "DBKeyDef.h"
#include "DBProofingAssociatedInfo.h"

class CADOConn;

class CDBP_TextBoardData  : public CDBProofingAssociatedData
{
   DECLARE_SERIAL( CDBP_TextBoardData)//序列化（串行化）需要添加的声明
public:
   CString     m_strTextInfo     ;//文字板

public:
   CDBP_TextBoardData();
   ~CDBP_TextBoardData();
   void ResetData();
   void Copy(CDBP_TextBoardData *pData);
   BOOL GetAllDBInfo(CADOConn *pADOConn);          //获取所有信息
   BOOL GetAllDBInfoBynAssociatedID(CADOConn *pADOConn,__int64 nAssociatedID);
   BOOL DelAllDBInfoByID(CADOConn *pADOConn);      //根据ID删除整条记录
   BOOL UpdateAllDBInfoByID(CADOConn *pADOConn);   //根据ID 更新文字板信息  没有ID类型的更新
   BOOL InsertAllDBInfo(CADOConn *pADOConn);   //插入数据信息

   void Trim();

};

class CDBP_TextBoardList : public CDataListMid
{
   DECLARE_SERIAL(CDBP_TextBoardList)
public:
   CDBP_TextBoardList();
   ~CDBP_TextBoardList();
   CDBP_TextBoardData*  GetItem(int nIndex);
   void    AddItem(CDBP_TextBoardData* pItem);
   void    DeleteItem(int nIndex);

   static CDBP_TextBoardList * Instance();//获取（指针）实例

private:
   static std::shared_ptr<CDBP_TextBoardList> sm_inst;
};