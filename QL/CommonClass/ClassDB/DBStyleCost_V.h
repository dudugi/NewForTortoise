/*************************************************
// <�ļ�>: DBStyleCost_V.h
// <˵��>: ��ʽ�ɱ���ͼ��
// <����>: wangzl
// <����>: 2019/06/11
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
#pragma once
#include "DataMid.h"

class CDBStyleCostData_V  : public CDataMid
{
   DECLARE_SERIAL(CDBStyleCostData_V)//���л������л�����Ҫ��ӵ�����
public:
   int               m_ID                        ;//ID 
   CString           m_strStyleNo                ;//���      
   CString           m_strCostItem               ;//�ɱ���
   CString           m_strCostType               ;//�ɱ����
   double            m_fCostPrice                ;//�ɱ�����
   double            m_fCostAddedValue           ;//�ɱ�����ֵ
   double            m_fSalesPrice               ;//���۵���
   double            m_fSalesAddedValue          ;//���۸���ֵ
   double            m_fCalculatedValue          ;//������ֵ
   double            m_fCost                     ;//�ɱ�
   double            m_fQuotedPrice              ;//����
public:
   CDBStyleCostData_V();
   ~CDBStyleCostData_V();
   void ResetData();
   void Copy(CDBStyleCostData_V *pData);
   BOOL GetAllDBInfo(CADOConn *pADOConn);
   //���ݵ�ǰ���ݼ���ɱ� ����
   void CalculatedPrice();
};

class CDBStyleCostList_V : public CDataListMid
{
   DECLARE_SERIAL(CDBStyleCostList_V)
public:
   CDBStyleCostList_V();
   ~CDBStyleCostList_V();
   void Copy(CDBStyleCostList_V *pList);
   CDBStyleCostData_V*  GetItem(int nIndex);
   CDBStyleCostData_V*  GetItemByCostItem(CString strCostItem);
   void    AddItem(CDBStyleCostData_V* pItem);
   BOOL DeleteItem(int nIndex);
   BOOL DeleteItemByCostItem(CString strCostItem);
   void   GetDBDataByStyleNo(CADOConn *pADOConn,CString strStyleNo);
};