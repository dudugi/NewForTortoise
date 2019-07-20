/*************************************************
// <文件>: DBP_ProductRevisionRecords.h
// <说明>: 产品版本信息表
// <作者>: wangzl
// <日期>: 2019/02/22
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 
#pragma once
#include "DataMid.h"
#include "DBKeyDef.h"

class CADOConn;
class CDBP_ProductRevisionRecordsData  : public CDataMid
{
   DECLARE_SERIAL( CDBP_ProductRevisionRecordsData)//序列化（串行化）需要添加的声明

public:
   typedef enum{
      En_Refuse = 0,//退回
      En_Pass,//通过
   }En_CheckResult;
public:
   __int64 m_nID                    ;
   __int64 m_nAssociatedProductID   ;//关联产品ID
   CString m_strVersion             ;//大版本
   int     m_nVersionNo             ;//小版本号
   CString m_strCode                ;//对应的单号
   CString m_strAlias               ;//别名
   CString m_strSponsor             ;//发起人
   CString m_strRecordTime          ;//发起时间
   CString m_strRevisionType        ;//改版类型
   CString m_strRevisionReason      ;//改版原因
   CString m_strLastRecordProcess   ;//最后操作记录的工序
   BOOL    m_bCheckState            ;//审核状态
   int     m_nCheckResult           ;//审核结果
   CString m_strCheckUserID         ;//审核人
   CString m_strCheckTime           ;//审核原因
   CString m_strCheckOpinion        ;//审核批注

public:
   CDBP_ProductRevisionRecordsData();
   ~CDBP_ProductRevisionRecordsData();
   void ResetData();
   void Copy(CDBP_ProductRevisionRecordsData *pData);
   BOOL GetAllDBInfo(CADOConn *pADOConn);
   BOOL DelAllDBInfoByID(CADOConn *pADOConn);
   BOOL UpdateAllDBInfoByID(CADOConn *pADOConn);
   BOOL InsertAllDBInfo(CADOConn *pADOConn);

   void Trim();

};

class CDBP_ProductRevisionRecordsList : public CDataListMid
{
   DECLARE_SERIAL(CDBP_ProductRevisionRecordsList)
public:
   CDBP_ProductRevisionRecordsList();
   ~CDBP_ProductRevisionRecordsList();
   CDBP_ProductRevisionRecordsData*  GetItem(int nIndex);
   void    AddItem(CDBP_ProductRevisionRecordsData* pItem);
   void    DeleteItem(int nIndex);

   static CDBP_ProductRevisionRecordsList * Instance();//获取（指针）实例

private:
   static std::shared_ptr<CDBP_ProductRevisionRecordsList> sm_inst;
};