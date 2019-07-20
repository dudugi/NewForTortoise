/*************************************************
// <文件>: DBStyle_VersionRecords.h
// <说明>: 记录单号对应的文件数量
// <作者>: wangzl
// <日期>: 2019/02/22
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 
#pragma once

#include "DataMid.h"

class CDBStyle_VersionRecordsData : public CDataMid
{
   DECLARE_SERIAL( CDBStyle_VersionRecordsData )//序列化（串行化）需要添加的声明
public:
   CDBStyle_VersionRecordsData(void);
   ~CDBStyle_VersionRecordsData(void);   
public:
   enum {
      en_Working = 0       ,//工作中
      en_FixVersion_Apply  ,//定版申请
      en_FixVersion_Check  ,//定版
      en_ChangeVersion_Apply,//改版申请
   };
public:
   INT64    m_nID          ;//ID
   int      m_nStyleID     ;//款式ID
   CString  m_strPerson    ;//操作人
   int      m_nState       ;//定版改版状态
   CString  m_strRecordTime;//操作时间
   CString  m_strRemark    ;//备注

public:
   void ResetData();
   void Copy(CDBStyle_VersionRecordsData *);
   BOOL GetAllDBInfo(CADOConn *pADOConn);

   BOOL InsertAllDBInfo(CADOConn * pADOConn);


   CString GetInsertSQL() const;
};


