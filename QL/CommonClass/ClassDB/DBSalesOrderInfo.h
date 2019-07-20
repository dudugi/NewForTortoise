#pragma once
#include "DataMid.h"
#include <tuple>
/*************************************************
// <文件>: DBProductOrderInfo.h
// <说明>: 销售单数据
// <作者>: lida
// <日期>: 2019/07/19 15:16:08
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 

class CADOConn;
class CDBSalesOrderInfo :public CDataMid
{
   DECLARE_SERIAL( CDBSalesOrderInfo)//序列化（串行化）需要添加的声明
public:
   CDBSalesOrderInfo(void);
   ~CDBSalesOrderInfo(void);

public:
   int         m_id;                // 自增ID
   CString     m_strStyleNo;         //款号
   CString     m_strSalesOrder;     //生产单号
   CString     m_strMainClrNo;
   CString     m_strMainClrCate;
   CString     m_strMainClrName;
   CString     m_strSizeNumInfo;       //尺码数量信息：s(1);m(2);l(3);....       
   CString     m_strDate;           //操作时间
   int         m_iTotalNum;         //总件数，可以调用ParaseSizeInfo自动计算，否则自己算，一定要给值，不然统计有问题

   map<CString,CString> m_mapSizeInfo; //从m_strSizeInfo解析数据

   enum DataType
   {
      en_null = -1,
      en_add = 0,  
      en_del = 1,
      en_updadte =2,
   };
public:
   void ResetData();
   void Copy(CDBSalesOrderInfo *pData);
   void GetAllDBInfo(CADOConn* pADOConn);

   BOOL InsetAllDBInfo(CADOConn* pADOConn);
   BOOL UpdateAllDBInfo(CADOConn* pADOConn); //根据ID
   BOOL DeleteAllDBInfo(CADOConn* pADOConn); //根据ID

   CString GetInsertSql();
   CString GetUpdateSql();
   CString GetDeleteSql();
   CString GetDeleteSqlByStyleNo(CString strStyleNo);
   static void ParaseSizeInfo(const CString strSizeInfo,map<CString,CString>& mapSizeInfo);  //str -> map
   static void ParaseSizeInfo(const map<CString,CString> mapSizeInfo,CString& strSizeInfo,int& iTotalNum);  //map -> str
   static void CreateRowData(CDBSalesOrderInfo* pData,MAP_GridCtrl_RowData& row_data);
};


class CDBSalesOrderInfoList :public CDataListMid
{
   DECLARE_SERIAL( CDBSalesOrderInfoList)//序列化（串行化）需要添加的声明
public:
   CDBSalesOrderInfoList(void);
   ~CDBSalesOrderInfoList(void);

   static CDBSalesOrderInfoList * Instance();//获取（指针）实例

   CDBSalesOrderInfo* GetItem(int nIndex);			//根据索引获取Item 
   void AddItem(CDBSalesOrderInfo* pItem);			//添加Item
   void DeleteItem(int nIndex);					//删除固定索引Item

   //获取一条操作记录数据
   void GetProductOrderRecords(CADOConn* pAdo,CString strID,__out map<CString,tuple<CString,CString>>& mapColorInfo,__out map<CString,map<CString,CString>>& mapSizeInfo);


public:
#ifdef USING_GRIDCTRL_MARK
   void GetGridDataInfo(CADOConn* pAdo,CString strStyleNo,MAP_GridCtrl_AllData& all_data);
#endif

private:
   static std::shared_ptr<CDBSalesOrderInfoList> sm_inst;
};