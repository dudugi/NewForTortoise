/*************************************************
// <文件>: DBStyleCost_V.h
// <说明>: 款式成本视图类
// <作者>: wangzl
// <日期>: 2019/06/11
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 
#pragma once
#include "DataMid.h"

class CDBStyleCostData_V  : public CDataMid
{
   DECLARE_SERIAL(CDBStyleCostData_V)//序列化（串行化）需要添加的声明
public:
   int               m_ID                        ;//ID 
   CString           m_strStyleNo                ;//款号      
   CString           m_strCostItem               ;//成本项
   CString           m_strCostType               ;//成本类别
   double            m_fCostPrice                ;//成本单价
   double            m_fCostAddedValue           ;//成本附加值
   double            m_fSalesPrice               ;//销售单价
   double            m_fSalesAddedValue          ;//销售附加值
   double            m_fCalculatedValue          ;//计算数值
   double            m_fCost                     ;//成本
   double            m_fQuotedPrice              ;//报价
public:
   CDBStyleCostData_V();
   ~CDBStyleCostData_V();
   void ResetData();
   void Copy(CDBStyleCostData_V *pData);
   BOOL GetAllDBInfo(CADOConn *pADOConn);
   //根据当前数据计算成本 报价
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