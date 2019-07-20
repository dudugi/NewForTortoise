/*************************************************
// <文件>: DBProAct.h
// <说明>: 工序操作类  用于处理工序对外的操作逻辑
// <作者>: wangzl 
// <日期>: 2019/02/22 
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 
#pragma once

#include "DBProSearchInfo.h"
#include <vector>

class CADOConn;

class CDBProAct
{
public:
	CDBProAct(void);
	~CDBProAct(void);

   //************************************
   // <函数>:   CompareStyleProOrder
   // <说明>:   比对款式的当前工序顺序与操作顺序
   // <作者>:   wangzl
   // <日期>:   2019/05/23
   // <Access>: public 
   // <Return>: int -1操作的<款式的 0 操作的=款式的 1操作的>款式的
   // <参数>:   CADOConn * pADOConn 数据库操作指针
   // <参数>:   const CString & strStyleNo 款号
   // <参数>:   int nCurProOrder 当前工序的顺序
   //************************************
   int CompareStyleProOrder(CADOConn * pADOConn,const CString & strStyleNo,int nCurProOrder);

   //************************************
   // <函数>:   HasMustRunningPro
   // <说明>:   在款式的当前工序状态与传入的状态之间是否有任何必须流转的工序
   // <作者>:   wangzl
   // <日期>:   2019/05/23
   // <Access>: public 
   // <Return>: BOOL
   // <参数>:   CADOConn * pADOConn 数据库操作指针
   // <参数>:   const CString & strStyleNo 款号
   // <参数>:   int nCurProOrder 当前工序的工序顺序
   //************************************
   BOOL HasMustRunningPro(CADOConn * pADOConn,const CString & strStyleNo,int nCurProOrder);
};




class CDBProSearch 
{
public:
   CDBProSearch();
   ~CDBProSearch();

public:
   static std::vector<S_ProUserStyleInfo> GetUserProStyleInfo(CADOConn * pADOConn,const CString & strUserID,const CString & strGroup);

   static std::vector<S_ProUserStyleInfo> GetUserProStyleInfoFinished(CADOConn * pADOConn,
      const CString & strUserID, UINT uSortID,const CString & strUserDuty,const CString & strTreeCode); //已完成 by duchen
};