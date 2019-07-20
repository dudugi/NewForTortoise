/*************************************************
// <文件>: DBProductVersionOrders_V.h
// <说明>: 打样版单查询视图
// <作者>: wangzl
// <日期>: 2019/02/22
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 
#pragma once
#include "DataMid.h"
#include "DBP_ProductStructurePlanning.h"

class CADOConn;
class CDBProductVersionOrders_VData  : public CDataMid
{
   DECLARE_SERIAL( CDBProductVersionOrders_VData)//序列化（串行化）需要添加的声明
public:
   CDBP_ProductStructurePlanningData m_ProductSPData     ;//产品信息

   __int64 m_nVersionID          ;//版本ID
   CString m_strVersion          ;//版本
   __int64 m_nRdRecordsID        ;//订单表ID
   CString m_strCate             ;//类型
   CString m_strCode             ;//单号
   CString m_strDate             ;//下单日期
   CString m_strMaker            ;//制单人
   CString m_strInvSehao         ;//主色
   CString m_strInvPeise         ;//配色
   CString m_strInvKuanhao       ;//款号
   CString m_strInvUnitCost      ;//单价
   CString m_strLastPerson       ;//最后操作人
   CString m_strLastTime         ;//最后操作时间
   CString m_strInvState2        ;//状态2
   CString m_strTrueTime         ;//真实录单时间
   int     m_nOrdCreateFlag      ;//订单创建标识
   CString m_strJianshu          ;//件数
   CString m_strInvMemo          ;//备注
   CString m_strInvState         ;//状态
   CString m_strZuoFeiMemo       ;//作废说明


public:
   CDBProductVersionOrders_VData();
   ~CDBProductVersionOrders_VData();
   void ResetData();
   void Copy(CDBProductVersionOrders_VData *pData);
   BOOL GetAllDBInfo(CADOConn *pADOConn);

#ifdef USING_GRIDCTRL_MARK

   MAP_GridCtrl_RowData CreateGridRowData(CADOConn * pADOConn);//2017/08/30
#endif // USING_GRIDCTRL_MARK

   void Trim();

};

class CDBProductVersionOrders_VList : public CDataListMid
{
   DECLARE_SERIAL(CDBProductVersionOrders_VList)
public:
   CDBProductVersionOrders_VList();
   ~CDBProductVersionOrders_VList();
   CDBProductVersionOrders_VData*  GetItem(int nIndex);
   void    AddItem(CDBProductVersionOrders_VData* pItem);
   void    DeleteItem(int nIndex);

#ifdef USING_GRIDCTRL_MARK
   MAP_GridCtrl_AllData    GetAllDBInfotoList(CADOConn *pADOConn,MAP_GridCtrl_AllData mapAllData);//获取所有数据信息
#endif // USING_GRIDCTRL_MARK

   static CDBProductVersionOrders_VList * Instance();//获取（指针）实例

private:
   static std::shared_ptr<CDBProductVersionOrders_VList> sm_inst;
};