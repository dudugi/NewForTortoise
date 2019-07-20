/*************************************************
// <文件>: DBP_ProductProcess.h
// <说明>: 打样 工序表
// <作者>: wangzl
// <日期>: 2019/02/22
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 
#pragma once
#include "DataMid.h"
class CADOConn;

class CDBP_ProductProcessData  : public CDataMid
{
   DECLARE_SERIAL( CDBP_ProductProcessData)//序列化（串行化）需要添加的声明

   typedef enum {
      En_ProcessType_Begin = 1,

      En_ProcessType_Design = En_ProcessType_Begin,//设计
      En_ProcessType_Pattern   ,//打板

      En_ProcessType_End       ,
   }EN_ProcessType;

public:
   __int64  m_nID             ;
   CString  m_strProcessName  ;//工序名
   int      m_nSortID         ;//排序ID
   EN_ProcessType      m_nProcessType    ;//一条记录所对应的工序类型  

public:
   CDBP_ProductProcessData();
   ~CDBP_ProductProcessData();
   void ResetData();
   void Copy(CDBP_ProductProcessData *pData);
   BOOL GetAllDBInfo(CADOConn *pADOConn);          //获取所有信息
   BOOL DelAllDBInfoByID(CADOConn *pADOConn);      //根据ID删除整条记录
   BOOL UpdateAllDBInfoByID(CADOConn *pADOConn);   //根据ID 更新文字板信息  没有ID类型的更新
   BOOL InsertAllDBInfo(CADOConn *pADOConn);   //插入数据信息

   void Trim();

};

class CDBP_ProductProcessList : public CDataListMid
{
   DECLARE_SERIAL(CDBP_ProductProcessList)
public:
   CDBP_ProductProcessList();
   ~CDBP_ProductProcessList();
   CDBP_ProductProcessData*  GetItem(int nIndex);
   void    AddItem(CDBP_ProductProcessData* pItem);
   void    DeleteItem(int nIndex);

   static CDBP_ProductProcessList * Instance();//获取（指针）实例

private:
   static std::shared_ptr<CDBP_ProductProcessList> sm_inst;
};