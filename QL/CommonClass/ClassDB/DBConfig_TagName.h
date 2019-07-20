/*************************************************
// <文件>: DBUserStylePermission_V.h
// <说明>: 用户款式权限视图DB类 用于标记员工对款式的权限
// <作者>: wangzl
// <日期>: 2019/05/06
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 
#pragma once
#include "DataMid.h"

class CDBConfig_TagNameData : public CDataMid
{
   DECLARE_SERIAL( CDBConfig_TagNameData)//序列化（串行化）需要添加的声明
public:
   CDBConfig_TagNameData(void);
   ~CDBConfig_TagNameData(void);

   CString m_strTagName    ;//标签名称
   CString m_strDisplayName;//显示名称
   int     m_nHide;//是否隐藏 yangjr 2019/07/09    
public:
   void ResetData();
   void Copy(CDBConfig_TagNameData *pData);
   BOOL GetAllDBInfo(CADOConn *pADOConn);				//获取【整条】信息
   BOOL UpdateAllDBInfo(CADOConn * pADOConn);

   CString GetUpdateSQL();
   CString GetInsertSQL();

   BOOL InsertAllDBInfo(CADOConn * pADOConn);
};

class CDBConfig_TagNameList :public CDataListMid
{
   DECLARE_SERIAL( CDBConfig_TagNameList)//序列化（串行化）需要添加的声明
public:
   CDBConfig_TagNameList(void);
   ~CDBConfig_TagNameList(void);
public:
   void Copy(CDBConfig_TagNameList *pList);
   CDBConfig_TagNameData*  GetItem(int nIndex);
   CDBConfig_TagNameData*  GetItemByTagName(const CString & strTagName);
   void AddItem(CDBConfig_TagNameData *pItem);
   void DeleteItemByIndex(int nIndex);
   //获取对应标签的显示名称
   CString GetItemDisplayName(const CString & strTagName);

   BOOL GetListFromDB(CADOConn *);

   static CDBConfig_TagNameList * Instance();//获取（指针）实例
private:
   static std::shared_ptr<CDBConfig_TagNameList> sm_inst;
};
