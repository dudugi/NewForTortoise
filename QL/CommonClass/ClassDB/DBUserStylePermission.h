/*************************************************
// <文件>: DBUserStylePermission.h
// <说明>: 用户款式权限DB类 用于标记员工对款式的权限
// <作者>: wangzl
// <日期>: 2019/05/06
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 
#pragma once
#include "DataMid.h"
#include "DBKeyDef.h"

//权限最大值为 7 

class CDBUserStylePermissionData : public CDataMid
{
   DECLARE_SERIAL( CDBUserStylePermissionData)//序列化（串行化）需要添加的声明
public:
   CDBUserStylePermissionData(void);
   ~CDBUserStylePermissionData(void);

   typedef enum EM_PERMISSION
   {
      en_Read = 1,//可读
      en_Edit = 2,//可编辑
      en_Del  = 4,//可删除
      en_All  = 7,//所有权限
   };

   INT64       m_nID          ;//
   int         m_nUserID      ;//员工ID
   int         m_nStyleID     ;//款式ID
   int         m_nPermission  ;//权限 参照unix的文件权限
   CString     m_cPermissionTime ;//权限有效期限
public:
   void ResetData();
   void Copy(CDBUserStylePermissionData *pData);
   BOOL GetAllDBInfo(CADOConn *pADOConn);				//获取【整条】信息
   BOOL InsertAllDBInfo(CADOConn *pADOConn);	//插入【整条】新记录
   BOOL UpdateAllDBInfoByID(CADOConn *pADOConn);	//根据用户账户更新【整条】记录
   BOOL DelAllDBInfoByID(CADOConn *pADOConn);		//根据用户账户删除【整条】记录
};

class CDBUserStylePermissionList :public CDataListMid
{
   DECLARE_SERIAL( CDBUserStylePermissionList)//序列化（串行化）需要添加的声明
public:
   CDBUserStylePermissionList(void);
   ~CDBUserStylePermissionList(void);
public:
   void Copy(CDBUserStylePermissionList *pList);
   CDBUserStylePermissionData*  GetItem(int nIndex);
   void AddItem(CDBUserStylePermissionData *pItem);
   void DeleteItemByIndex(int nIndex);
};
