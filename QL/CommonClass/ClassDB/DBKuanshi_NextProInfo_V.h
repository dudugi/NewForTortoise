/*************************************************
// <文件>: DBUserStylePermission_V.h
// <说明>: 用户款式权限视图DB类 用于标记员工对款式的权限
// <作者>: wangzl
// <日期>: 2019/05/06
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 
#pragma once
#include "DataMid.h"
#include <tuple>

class CDBKuanshi_NextProInfo_VData : public CDataMid
{
   DECLARE_SERIAL( CDBKuanshi_NextProInfo_VData)//序列化（串行化）需要添加的声明
public:
   CDBKuanshi_NextProInfo_VData(void);
   ~CDBKuanshi_NextProInfo_VData(void);

   CString m_strStyleNo    ;//款号
   CString m_strProcessName;//工序名
   CString m_strNextUserID ;//下一个工序对应的执行人

public:
   void ResetData();
   void Copy(CDBKuanshi_NextProInfo_VData *pData);
   BOOL GetAllDBInfo(CADOConn *pADOConn);				//获取【整条】信息
};

class CDBKuanshi_NextProInfo_VList :public CDataListMid
{
   DECLARE_SERIAL( CDBKuanshi_NextProInfo_VList)//序列化（串行化）需要添加的声明
public:
   CDBKuanshi_NextProInfo_VList(void);
   ~CDBKuanshi_NextProInfo_VList(void);
public:
   void Copy(CDBKuanshi_NextProInfo_VList *pList);
   CDBKuanshi_NextProInfo_VData*  GetItem(int nIndex);
   void AddItem(CDBKuanshi_NextProInfo_VData *pItem);
   void DeleteItemByIndex(int nIndex);
};
