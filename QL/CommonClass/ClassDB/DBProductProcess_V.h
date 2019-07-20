/*************************************************
// <文件>: DBProductProcess_V.h
// <说明>: 打样流程视图 此视图记录了每一个产品的最后一道工序记录是什么 以及对应的信息
// <作者>: wangzl
// <日期>: 2019/02/22
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 
#pragma once
#include "DataMid.h"
#include "DBP_ProductStructurePlanning.h"
#include "DBP_ProcessRecords.h"


class CADOConn;
class CDBProductProcess_VData  : public CDataMid
{
   DECLARE_SERIAL( CDBProductProcess_VData)//序列化（串行化）需要添加的声明
public:
   CDBP_ProductStructurePlanningData m_ProductSPData     ;//产品信息
   CDBP_ProcessRecordsData           m_ProcessRecordsData;//工序记录信息

   CString                           m_strAssignUserID   ;//改产品下一个应该执行工序的对应人员
   int                               m_nPersonType       ;//该产品下一个应该执行工序对应的人员类型

public:
   CDBProductProcess_VData();
   ~CDBProductProcess_VData();
   void ResetData();
   void Copy(CDBProductProcess_VData *pData);
   BOOL GetAllDBInfo(CADOConn *pADOConn);

   void Trim();


#ifdef USING_GRIDCTRL_MARK
   //行数据
   MAP_GridCtrl_RowData CreateGridRowData(CADOConn * pADOConn);//2017/08/31
#endif // USING_GRIDCTRL_MARK

};

class CDBProductProcess_VList : public CDataListMid
{
   DECLARE_SERIAL(CDBProductProcess_VList)
public:
   CDBProductProcess_VList();
   ~CDBProductProcess_VList();
   CDBProductProcess_VData*  GetItem(int nIndex);
   void    AddItem(CDBProductProcess_VData* pItem);
   void    DeleteItem(int nIndex);

   static CDBProductProcess_VList * Instance();//获取（指针）实例

private:
   static std::shared_ptr<CDBProductProcess_VList> sm_inst;
};