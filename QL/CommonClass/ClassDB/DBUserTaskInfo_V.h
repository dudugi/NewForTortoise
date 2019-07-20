/*************************************************
// <文件>: DBStyleCost_V.h
// <说明>: 款式成本视图类
// <作者>: wangzl
// <日期>: 2019/06/11
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 
#pragma once
#include "DataMid.h"

class CDBUserTaskInfoData_V  : public CDataMid
{
   DECLARE_SERIAL(CDBUserTaskInfoData_V)//序列化（串行化）需要添加的声明
public:
   CString  m_strUserID          ;
   CString  m_strKuanhao         ;
   int      m_nTaskType          ;
   int      m_nIsGroup           ;

   enum{
      en_ToBeProcessed = 1,
      en_PedingSubmission,
      en_Completed,
   };

public:
   CDBUserTaskInfoData_V();
   ~CDBUserTaskInfoData_V();
   void ResetData();
   void Copy(CDBUserTaskInfoData_V *pData);
   BOOL GetAllDBInfo(CADOConn *pADOConn);
};

class CDBUserTaskInfoList_V : public CTDataListMid<CDBUserTaskInfoList_V,CDBUserTaskInfoData_V>
{
public:
   CDBUserTaskInfoList_V();
   ~CDBUserTaskInfoList_V();
};