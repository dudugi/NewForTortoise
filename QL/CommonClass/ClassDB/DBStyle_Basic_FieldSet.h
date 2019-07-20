/*************************************************
// <文件>: DBStyle_Basic_FieldSet.h
// <说明>: 款式基本信息字段表
// <作者>: wangzl
// <日期>: 2019/07/01
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 
#pragma once
#include "DataMid.h"
class CADOConn;

class CDBStyle_Basic_FieldSetData  : public CDataMid
{
   DECLARE_SERIAL(CDBStyle_Basic_FieldSetData)//序列化（串行化）需要添加的声明
public:
   CString  m_strColID        ;//列ID
   CString  m_strDisplayName  ;//显示名称
   BOOL     m_bShow           ;//是否显示
   int      m_nSortIndex      ;//排序索引
   BOOL     m_bOnPanel        ;//是否显示在面板上


public:
   CDBStyle_Basic_FieldSetData();
   ~CDBStyle_Basic_FieldSetData();
   void ResetData();
   void Copy(CDBStyle_Basic_FieldSetData *pData);
   BOOL GetAllDBInfo(CADOConn *pADOConn);
   CString GetInsertSQL() const;
};

class CDBStyle_Basic_FieldSetList : public CTDataListMid<CDBStyle_Basic_FieldSetList,CDBStyle_Basic_FieldSetData>
{
public:
   CDBStyle_Basic_FieldSetList();
   ~CDBStyle_Basic_FieldSetList();

   BOOL GetListFromDB(CADOConn *);

   std::vector<pair<CString/*Field*/,CString/*oldName*/>> & GetDefineBasicFieldInfo();

   static CDBStyle_Basic_FieldSetList * Instance();					//获取（指针）实例
private:
   static std::shared_ptr<CDBStyle_Basic_FieldSetList> sm_inst;
};