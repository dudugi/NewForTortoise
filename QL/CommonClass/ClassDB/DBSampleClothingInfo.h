/*************************************************
// <文件>: DBSamepleClothingInfo.h
// <说明>: 样衣管理表
// <作者>: lida
// <日期>: 2019/07/01 15:52:00
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 
#pragma once
#include "DataMid.h"
#include <set>

class CDBSampleClothingInfo  : public CDataMid
{
   DECLARE_SERIAL(CDBSampleClothingInfo)//序列化（串行化）需要添加的声明
public:
   int         m_ID;
   CString     m_strKuanhao;
   CString     m_strMainColor;      //主色
   CString     m_strSize;           //尺码
   CString     m_strBarCode;        //条码
   CString     m_strCreator;        //创建人
   CString     m_strMakeTime;       //成衣时间
   CString     m_strKeeper;         //保管人
   CString     m_strKeepLocation;   //保管地点
   CString     m_strMemo;           //样衣备注
   int         m_LendReturnState;   //当前样衣状态 0借出，1归还,默认归还状态
   CString     m_strCate;           //类型

public:
   CDBSampleClothingInfo();
   ~CDBSampleClothingInfo();
   void ResetData();
   void Copy(CDBSampleClothingInfo *pData);
   BOOL GetAllDBInfo(CADOConn *pADOConn);
   
   BOOL Insert(CADOConn *pADOConn);
   BOOL Update(CADOConn *pADOConn);
   BOOL Del(CADOConn *pADOConn);

   CString GetInsertSql();
   CString GetUpdateSql();
   CString GetDelSql();
};

class CDBSampleClothingInfoList : public CDataListMid
{
   DECLARE_SERIAL(CDBSampleClothingInfoList)
public:
   CDBSampleClothingInfoList();
   ~CDBSampleClothingInfoList();
   void Copy(CDBSampleClothingInfoList *pList);
   CDBSampleClothingInfo*  GetItem(int nIndex);
   void    AddItem(CDBSampleClothingInfo* pItem);
   BOOL DeleteItem(int nIndex);

   static CDBSampleClothingInfoList * Instance();	//获取（指针）实例
private:
   static std::shared_ptr<CDBSampleClothingInfoList> sm_inst;

public:
   static BOOL GetSampleClothingDataByBarCode(__in CADOConn* pAdo,__in CString strBarCode,__out CDBSampleClothingInfo* pData);

#ifdef USING_GRIDCTRL_MARK
   BOOL GetSampleClothingListGridData(__in CADOConn* pAdo,__in CString strStyleNo,__out MAP_GridCtrl_AllData& all_data,__out set<CString>& setBarCode);
#endif
};