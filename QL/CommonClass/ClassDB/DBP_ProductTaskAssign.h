/*************************************************
// <文件>: DBP_ProductTaskAssign.h
// <说明>: 打样-任务安排信息表
// <作者>: wangzl
// <日期>: 2019/02/22
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 
#pragma once
#include "DataMid.h"
#include "DBKeyDef.h"
#include "DBP_ProductProcess.h"


class CADOConn;

class CDBP_ProductTaskAssignData  : public CDataMid
{
   DECLARE_SERIAL( CDBP_ProductTaskAssignData)//序列化（串行化）需要添加的声明
public:

   __int64 m_nID                    ;//
   __int64 m_nAssociatedProductID   ;//关联的产品ID
   int     m_nPersonType            ;//人员类型   与工序的类型保持一致
   CString m_strAssignUserID        ;//被指派人的ID
   CString m_strAllotUserID         ;//安排人的ID
   CString m_strAllotTime           ;//安排时间

public:
   CDBP_ProductTaskAssignData();
   ~CDBP_ProductTaskAssignData();
   void ResetData();
   void Copy(CDBP_ProductTaskAssignData *pData);
   BOOL GetAllDBInfo(CADOConn *pADOConn);          //获取所有信息
   BOOL DelAllDBInfoByID(CADOConn *pADOConn);      //根据ID删除整条记录
   BOOL UpdateAllDBInfoByID(CADOConn *pADOConn);   //根据ID 更新文字板信息  没有ID类型的更新
   BOOL InsertAllDBInfo(CADOConn *pADOConn);   //插入数据信息

   CString GetTypeString();
   CString GetTypeString(CDBP_ProductProcessData::EN_ProcessType nAssignType);

   CDBP_ProductProcessData::EN_ProcessType GetTypeByTypeString(const CString & strTypeString);

   BOOL GetInsertSQL(CString & strSQL);

   void Trim();

};

class CDBP_ProductTaskAssignList : public CDataListMid
{
   DECLARE_SERIAL(CDBP_ProductTaskAssignList)
public:
   CDBP_ProductTaskAssignList();
   ~CDBP_ProductTaskAssignList();
   CDBP_ProductTaskAssignData*  GetItem(int nIndex);
   CDBP_ProductTaskAssignData*  GetItemByPersonType(CDBP_ProductProcessData::EN_ProcessType);
   void    AddItem(CDBP_ProductTaskAssignData* pItem);
   void    DeleteItem(int nIndex);

   static CDBP_ProductTaskAssignList * Instance();//获取（指针）实例

private:
   static std::shared_ptr<CDBP_ProductTaskAssignList> sm_inst;
};