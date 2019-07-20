/*************************************************
// <文件>: DBP_Planning.h
// <说明>: 打样-主题企划
// <作者>: wangzl
// <日期>: 2019/02/22
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 
#pragma once
#include "DataMid.h"
#include "DBKeyDef.h"
#include "DBDef.h"
#include "stdafx.h"


class CDBP_PlanningData :public CDataMid
{
   DECLARE_SERIAL( CDBP_PlanningData)//序列化（串行化）需要添加的声明
public:
   CDBP_PlanningData(void);
   ~CDBP_PlanningData(void);
public:
     __int64           m_nID                       ;         //ID
      int              m_nYears                    ;         //年度
      CString          m_strSeason                 ;         //季节
      CString          m_strSubjectName            ;         //主题名
      CString          m_strBrand                  ;         //品牌
      CString          m_strRemark                 ;         //主题备注
      BOOL             m_bCheckState               ;         //审核标识
      CString          m_strCreateUserID           ;         //创建人
      CString          m_strCreateTime             ;         //创建时间
      CString          m_strLastAcTime             ;         //最后操作时间
      CString          m_strCheckUserID            ;         //审核人
      CString          m_strCheckTime              ;         //审核时间
   void ResetData();
   void Copy(CDBP_PlanningData *pData);
   BOOL GetAllDBInfo(CADOConn *pADOConn);				//获取【整条】信息
   BOOL GetAllDBInfoByID(CADOConn *pADOConn);				//获取【整条】信息
   BOOL GetIDByCondition(CADOConn *pADOConn);				//获取【整条】信息

   BOOL InsertAllDBInfo(CADOConn *pADOConn);	//插入【整条】新记录
   BOOL UpdateAllDBInfoByID(CADOConn *pADOConn);	//根据用户账户更新【整条】记录
   BOOL DelAllDBInfoByID(CADOConn *pADOConn);		//根据用户账户删除【整条】记录
};

class CDBP_PlanningList :public CDataListMid
{
   DECLARE_SERIAL( CDBP_PlanningList)//序列化（串行化）需要添加的声明
public:
   CDBP_PlanningList(void);
   ~CDBP_PlanningList(void);
public:
   void Copy(CDBP_PlanningList *pList);
   void AddItem(CDBP_PlanningData *pItem);
   void DeleteItemByIndex(int nIndex);
   #ifdef USING_GRIDCTRL_MARK
   void GetAllDBInfoByCondition(CADOConn *pADO,CString strSQL,MAP_GridCtrl_AllData &mapALLData);    //通过条件获取数据,进行Grid数据填充
   #endif
};
