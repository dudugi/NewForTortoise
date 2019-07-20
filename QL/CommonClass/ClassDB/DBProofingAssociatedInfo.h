/*************************************************
// <�ļ�>: DBProofingAssociatedInfo.h
// <˵��>: ���� ������Ϣ�Ļ��� �������ְ� ͼƬ ���� ��ɫ
// <����>: wangzl
// <����>: 2019/02/22
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
#pragma once
#include "DataMid.h"
#include "DBKeyDef.h"
class CADOConn;

class CDBProofingAssociatedData  : public CDataMid
{
   DECLARE_SERIAL( CDBProofingAssociatedData)//���л������л�����Ҫ��ӵ�����
public:

   typedef enum EN_PROOFINGTYPE{
      En_Type_NULL     = -1,//�������Ϣ  ����ʹ�õ�Ĭ��ֵ
      En_Type_Planning = 0 ,//������
      En_Type_Band         ,//������Ϣ
   };
   __int64           m_nID             ;
   EN_PROOFINGTYPE   m_nType           ;//����    �������󻮻��ǲ��ε���Ϣ
   __int64           m_nAssociatedID   ;//����ID

public:
   CDBProofingAssociatedData();
   ~CDBProofingAssociatedData();
   void ResetData();
   void Copy(CDBProofingAssociatedData *pData);

};

