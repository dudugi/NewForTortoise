/*************************************************
// <文件>: DBStyle_DesFaceCode.h
// <说明>: 款式面子码
// <作者>: wangzl
// <日期>: 2019/06/19
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 
#pragma once
#include "DataMid.h"
class CADOConn;

class CDBStyle_DesFaceCodeData  : public CDataMid
{
   DECLARE_SERIAL(CDBStyle_DesFaceCodeData)//序列化（串行化）需要添加的声明
public:
   __int64  m_nID          ;//自增ID
   CString  m_strName      ;//名称 eg:面字码
   CString  m_sOldLen      ;//
   CString  m_strType      ;//类型 eg:支拉
   CString  m_sLen         ;//长度
   CString  m_strUnit      ;//单位 eg:里面
   __int64  m_nIDDensity   ;//密度关联字段自增ID

public:
   CDBStyle_DesFaceCodeData();
   ~CDBStyle_DesFaceCodeData();
   void ResetData();
   void Copy(CDBStyle_DesFaceCodeData *pData);
   BOOL GetAllDBInfo(CADOConn *pADOConn);
   CString GetSQLFormat();
   //获取插入数据的格式化
   CString GetValueFormat(
      const CString & strName,
      const CString & strOldLen,
      const CString & strType,
      const CString & strLen,
      const CString & strUnit,
      const __int64 nIDDensity
      );
};

class CDBStyle_DesFaceCodeList : public CTDataListMid<CDBStyle_DesFaceCodeList,CDBStyle_DesFaceCodeData>
{
public:
   CDBStyle_DesFaceCodeList();
   ~CDBStyle_DesFaceCodeList();
};