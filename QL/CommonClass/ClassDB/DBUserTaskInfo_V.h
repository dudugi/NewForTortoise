/*************************************************
// <�ļ�>: DBStyleCost_V.h
// <˵��>: ��ʽ�ɱ���ͼ��
// <����>: wangzl
// <����>: 2019/06/11
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
#pragma once
#include "DataMid.h"

class CDBUserTaskInfoData_V  : public CDataMid
{
   DECLARE_SERIAL(CDBUserTaskInfoData_V)//���л������л�����Ҫ��ӵ�����
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