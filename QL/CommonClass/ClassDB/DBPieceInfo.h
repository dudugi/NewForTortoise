/*************************************************
// <文件>: DBPieceInfo.h
// <说明>: 记录单号对应的衣片类型以及衣片名称的信息
// <作者>: wangzl
// <日期>: 2019/02/22
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 
#pragma once
#include "DataMid.h"


class CDBPieceInfoData : public CDataMid
{
public:
   int         m_nID                ;//自增ID
   CString     m_strcCode           ;//订单号
   int         m_nPieceType         ;//衣片类型
   CString     m_strcPieceName      ;//衣片名称
   CString     m_strcRemark         ;//备注 预留

   enum {
      En_PieceComputer = 0 ,//电脑
      En_PeiceHand         ,//手摇
   };
public:
   CDBPieceInfoData(void);
   ~CDBPieceInfoData(void);

   void ResetData();
   void Copy(CDBPieceInfoData *pData);
   BOOL GetAllDBInfo(CADOConn *pADOConn);			//获取一条记录信息
   BOOL InsertAllDBInfo(CADOConn *pADOConn);
};


class CDBPieceInfoList  : public CDataListMid
{
public:
   CDBPieceInfoList();
   ~CDBPieceInfoList();
   CDBPieceInfoData* GetItem(int nIndex);//根据索引获取Item
   CDBPieceInfoData* GetItemByPieceName(const CString & strPieceName);//根据索引获取Item
   void AddItem(CDBPieceInfoData* pItem);//添加Item
   void DeleteItem(int nIndex);		//删除固定索引Item
   //根据订单号获取一个订单的所有备注
   BOOL GetListFromDB(CADOConn *pADOConn,const CString & strcCode);
   BOOL InsetAllDBInfo(CADOConn * pADOConn);
};

