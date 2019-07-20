/*************************************************
// <文件>: DBProcessRecords.h
// <说明>: 子单工序记录对应的信息类
// <作者>: wangzl
// <日期>: 2019/01/26 14:49:24
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 
#pragma once
#include <vector>
#include "DataMid.h"
#include "DBDef.h"
#include <map>
#include "WeightUnitOp.h"

class CDBProcessRecordsData : public CDataMid
{
   DECLARE_SERIAL( CDBProcessRecordsData)//序列化（串行化）需要添加的声明
public:
   CDBProcessRecordsData(void);
   ~CDBProcessRecordsData(void);
public:
   
public:
   INT64             m_nID                   ;//指派任务的ID、主键
   CString           m_strCode               ;//订单号、不空
   CString           m_strGXName             ;//工序名称
   int               m_nState                ;//工序状态   ->  0未开始   1->进行中  2->完成
   CString           m_strMemo               ;//备注
   CString           m_strPersonCode         ;//被指派人名称
   double            m_fPieceWeight          ;//片重
   double            m_fDuration             ;//时长
   double            m_fGongjia              ;//工价
   CString           m_strRecordTime         ;//记录时间
   CString           m_strToPerson           ;//一些操作所对应的员工

   //默认工序对应的工序ID值
   typedef enum{
      ASSIGN_ID_NONE = 0,//初始化工序ID状态
      ASSIGN_ID_PROCESS = 1,//工艺
      ASSIGN_ID_DESIGN,//设计
      ASSIGN_ID_PATERN,//制版
      ASSIGN_ID_MAC,//上机
   }Assign_Default_ProID;
   //工序状态
   typedef enum{
      ASSIGN_STATE_UNBEG = -1,//工序未开始
      ASSIGN_STATE_RUN,//工序进行中
      ASSIGN_STATE_OVER,//工序完成
   }Assign_ProState;

   void ResetData();
   void Copy(CDBProcessRecordsData *pData);
   BOOL GetAllDBInfo(CADOConn *pADOConn);//获取【整条】信息
   BOOL InsertAllDBInfo(CADOConn *pADOConn);//插入【整条】新记录

   //返回插入的SQL语句 需要当前DB类中有相关的数据 wangzl 2018-10-09
   CString GetInsertSQL() const;
   static CString GetDeleteByStyleNoSql(const CString & strStyleNo);

   //取出所有字符串变量两边的空格
   void Trim();

};

class CDBProcessRecordsList :public CDataListMid
{
   DECLARE_SERIAL( CDBProcessRecordsList)//序列化（串行化）需要添加的声明
public:
   CDBProcessRecordsList(void);
   ~CDBProcessRecordsList(void);
public:
   CDBProcessRecordsData*  GetItem(int nIndex);
   CDBProcessRecordsData*  GetItem(CString strOrderNo);
   void    AddItem(CDBProcessRecordsData* pItem);
   void    DeleteItem(int nIndex);
   void    DeleteItem(CString strOrderNo);
   void    DeleteItemByID(__int64 nID);
};
