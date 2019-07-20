/*************************************************
// <�ļ�>: DBP_ProductProcess.h
// <˵��>: ���� �����
// <����>: wangzl
// <����>: 2019/02/22
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
#pragma once
#include "DataMid.h"
class CADOConn;

class CDBP_ProductProcessData  : public CDataMid
{
   DECLARE_SERIAL( CDBP_ProductProcessData)//���л������л�����Ҫ��ӵ�����

   typedef enum {
      En_ProcessType_Begin = 1,

      En_ProcessType_Design = En_ProcessType_Begin,//���
      En_ProcessType_Pattern   ,//���

      En_ProcessType_End       ,
   }EN_ProcessType;

public:
   __int64  m_nID             ;
   CString  m_strProcessName  ;//������
   int      m_nSortID         ;//����ID
   EN_ProcessType      m_nProcessType    ;//һ����¼����Ӧ�Ĺ�������  

public:
   CDBP_ProductProcessData();
   ~CDBP_ProductProcessData();
   void ResetData();
   void Copy(CDBP_ProductProcessData *pData);
   BOOL GetAllDBInfo(CADOConn *pADOConn);          //��ȡ������Ϣ
   BOOL DelAllDBInfoByID(CADOConn *pADOConn);      //����IDɾ��������¼
   BOOL UpdateAllDBInfoByID(CADOConn *pADOConn);   //����ID �������ְ���Ϣ  û��ID���͵ĸ���
   BOOL InsertAllDBInfo(CADOConn *pADOConn);   //����������Ϣ

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

   static CDBP_ProductProcessList * Instance();//��ȡ��ָ�룩ʵ��

private:
   static std::shared_ptr<CDBP_ProductProcessList> sm_inst;
};