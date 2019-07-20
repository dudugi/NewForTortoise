/*************************************************
// <文件>: DBStyle_CheckRecords.h
// <说明>: 记录单号对应的文件数量
// <作者>: wangzl
// <日期>: 2019/02/22
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 
#pragma once

#include "DataMid.h"

class CDBStyle_CheckRecordsData : public CDataMid
{
   DECLARE_SERIAL( CDBStyle_CheckRecordsData )//序列化（串行化）需要添加的声明
public:
   CDBStyle_CheckRecordsData(void);
   ~CDBStyle_CheckRecordsData(void);   
public:
   enum {
      en_CheckIn = 0,//检入 -- 锁定审核
      en_CheckOut,//检出  --修改
   };
public:
   INT64    m_nID          ;//ID
   int      m_nStyleID     ;//款式ID
   CString  m_strPerson    ;//操作人
   int      m_nState       ;//检入检出状态
   CString  m_strRecordTime;//操作时间

public:
   void ResetData();
   void Copy(CDBStyle_CheckRecordsData *);
   BOOL GetAllDBInfo(CADOConn *pADOConn);

   BOOL InsertAllDBInfo(CADOConn * pADOConn);


   CString GetInsertSQL() const;
};

class CDBStyle_CheckRecordsList : public CDataListMid
{
   DECLARE_SERIAL(CDBStyle_CheckRecordsList)
public:
   CDBStyle_CheckRecordsList();
   ~CDBStyle_CheckRecordsList(); 
};

