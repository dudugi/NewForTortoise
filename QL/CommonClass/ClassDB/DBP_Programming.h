/*************************************************
// <文件>: DBP_Programming.h
// <说明>: 商品规划表
// <作者>: wangzl
// <日期>: 2019/02/22
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 
#pragma once
#include "DataMid.h"
#include "DBKeyDef.h"


class CADOConn;

class CDBP_ProgrammingData  : public CDataMid
{
   DECLARE_SERIAL( CDBP_ProgrammingData)//序列化（串行化）需要添加的声明
public:
   __int64  m_nID                    ;//
   CString  m_strBrand              ;//品牌
   int      m_nYears                ;//年份
   CString  m_strSeason             ;//季节
   CString  m_strTradeFairTime      ;//订货会
   CString  m_strArea               ;//区域
   __int64  m_nAssociatedPlanningID ;//关联的主题ID
   CString  m_strCreateUserID       ;//创建人

public:
   CDBP_ProgrammingData();
   ~CDBP_ProgrammingData();
   void ResetData();
   void Copy(CDBP_ProgrammingData *pData);
   BOOL GetAllDBInfo(CADOConn *pADOConn);
   BOOL GetAllDBInfoByID(CADOConn *pADOConn);
   BOOL GetIDByCondition(CADOConn *pADOConn);
   BOOL DelAllDBInfoByID(CADOConn *pADOConn);
   BOOL UpdateAllDBInfoByID(CADOConn *pADOConn);
   BOOL InsertAllDBInfo(CADOConn *pADOConn);

   void Trim();

};

class CDBP_ProgrammingList : public CDataListMid
{
   DECLARE_SERIAL(CDBP_ProgrammingList)
public:
   CDBP_ProgrammingList();
   ~CDBP_ProgrammingList();
   CDBP_ProgrammingData*  GetItem(int nIndex);
   void    AddItem(CDBP_ProgrammingData* pItem);
   void    DeleteItem(int nIndex);

   static CDBP_ProgrammingList * Instance();//获取（指针）实例

private:
   static std::shared_ptr<CDBP_ProgrammingList> sm_inst;
};