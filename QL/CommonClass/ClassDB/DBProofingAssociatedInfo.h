/*************************************************
// <文件>: DBProofingAssociatedInfo.h
// <说明>: 打样 关联信息的基类 用于文字板 图片 物料 颜色
// <作者>: wangzl
// <日期>: 2019/02/22
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 
#pragma once
#include "DataMid.h"
#include "DBKeyDef.h"
class CADOConn;

class CDBProofingAssociatedData  : public CDataMid
{
   DECLARE_SERIAL( CDBProofingAssociatedData)//序列化（串行化）需要添加的声明
public:

   typedef enum EN_PROOFINGTYPE{
      En_Type_NULL     = -1,//错误的信息  程序使用的默认值
      En_Type_Planning = 0 ,//主题企划
      En_Type_Band         ,//波段信息
   };
   __int64           m_nID             ;
   EN_PROOFINGTYPE   m_nType           ;//类型    区分是企划还是波段的信息
   __int64           m_nAssociatedID   ;//关联ID

public:
   CDBProofingAssociatedData();
   ~CDBProofingAssociatedData();
   void ResetData();
   void Copy(CDBProofingAssociatedData *pData);

};

