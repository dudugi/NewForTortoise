/********************************************************************
***	<文件>: DBStyleCostData.h
***	<说明>:	款式成本数据操作类
***	<作者>:	anjie
***	<日期>:	2019/5/23
*** Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*********************************************************************/
#pragma once
#include "DataMid.h"
class CADOConn;

class CDBStyleCostData  : public CDataMid
{
   DECLARE_SERIAL(CDBStyleCostData)//序列化（串行化）需要添加的声明
public:
   int               m_ID                        ;//ID 
   CString           m_strStyleNo                ;//款号      
   CString           m_strCostItem               ;//成本项
   CString           m_strCostType               ;//成本类别
   CString           m_strCostJinE               ;//成本金额  已弃用 wangzl 2019-6-11  成本为计算所得  视图数据进行查询
   double            m_fCostPrice                ;//成本单价
   double            m_fCostAddedValue           ;//成本附加值
   double            m_fSalesPrice               ;//销售单价
   double            m_fSalesAddedValue          ;//销售附加值
   double            m_fCalculatedValue          ;//计算数值
public:
   CDBStyleCostData();
   ~CDBStyleCostData();

   void Serialize(CArchive& ar);
   void ResetData();
   void Copy(CDBStyleCostData *pData);
   BOOL GetAllDBInfo(CADOConn *pADOConn);
   static CString GetDeleteByStyleNoSql(const CString & strStyleNo);
};

class CDBStyleCostList : public CDataListMid
{
   DECLARE_SERIAL(CDBStyleCostList)
public:
   CDBStyleCostList();
   ~CDBStyleCostList();
   void Serialize(CArchive& ar);
   void Copy(CDBStyleCostList *pList);
   CDBStyleCostData*  GetItem(int nIndex);
   CDBStyleCostData*  GetItemByCostItem(CString strCostItem);
   void    AddItem(CDBStyleCostData* pItem);
   BOOL DeleteItem(int nIndex);
   BOOL DeleteItemByCostItem(CString strCostItem);
   BOOL    BatchInsertDataToDB(CADOConn *pADOConn);//批量插入数据到数据库(已有数据会先删，后插入)
   void   GetDBDataByStyleNo(CADOConn *pADOConn,CString strStyleNo);
   static CDBStyleCostList * Instance();//获取（指针）实例
#ifdef USING_GRIDCTRL_MARK
   void   CreateGridData(MAP_GridCtrl_AllData & map_allData);
#endif
private:
   static std::shared_ptr<CDBStyleCostList> sm_inst;
};