/*************************************************
// <�ļ�>: DBP_ProductTaskAssign.h
// <˵��>: ����-��������Ϣ��
// <����>: wangzl
// <����>: 2019/02/22
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
#pragma once
#include "DataMid.h"
#include "DBKeyDef.h"
#include "DBP_ProductProcess.h"


class CADOConn;

class CDBP_ProductTaskAssignData  : public CDataMid
{
   DECLARE_SERIAL( CDBP_ProductTaskAssignData)//���л������л�����Ҫ��ӵ�����
public:

   __int64 m_nID                    ;//
   __int64 m_nAssociatedProductID   ;//�����Ĳ�ƷID
   int     m_nPersonType            ;//��Ա����   �빤������ͱ���һ��
   CString m_strAssignUserID        ;//��ָ���˵�ID
   CString m_strAllotUserID         ;//�����˵�ID
   CString m_strAllotTime           ;//����ʱ��

public:
   CDBP_ProductTaskAssignData();
   ~CDBP_ProductTaskAssignData();
   void ResetData();
   void Copy(CDBP_ProductTaskAssignData *pData);
   BOOL GetAllDBInfo(CADOConn *pADOConn);          //��ȡ������Ϣ
   BOOL DelAllDBInfoByID(CADOConn *pADOConn);      //����IDɾ��������¼
   BOOL UpdateAllDBInfoByID(CADOConn *pADOConn);   //����ID �������ְ���Ϣ  û��ID���͵ĸ���
   BOOL InsertAllDBInfo(CADOConn *pADOConn);   //����������Ϣ

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

   static CDBP_ProductTaskAssignList * Instance();//��ȡ��ָ�룩ʵ��

private:
   static std::shared_ptr<CDBP_ProductTaskAssignList> sm_inst;
};