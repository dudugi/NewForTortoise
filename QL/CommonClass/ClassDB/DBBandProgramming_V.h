#pragma once
#include "DataMid.h"
#include <map>
#include <vector>
#include <set>
#include "DBKeyDef_V.h"
#include "DBDef.h"

/*************************************************
// <文件>: DBBandProgramming_V.h
// <说明>: 波段商品信息视图对应信息类即链表
// <作者>: wangzl
// <日期>: 2019/02/22
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 

using namespace std;
class CADOConn;
class CDBViewBandProgrammingInfoData : public CDataMid
{
    DECLARE_SERIAL(CDBViewBandProgrammingInfoData)//序列化（串行化）需要添加的声明
public:
   CDBViewBandProgrammingInfoData(void);
   ~CDBViewBandProgrammingInfoData(void);
public:
   __int64               m_nID                   ;
   CString               m_strName                   ;//名称
   CString               m_oleBandStartTime          ;//波段开始时间
   CString               m_oleDesignEndTime          ;//设计完成时间
   CString               m_olePatternEndTime         ;//纸样完成时间
   CString               m_oleReviewEndTime          ;//内审会完成时间
   CString               m_oleBandEndTime            ;//波段结束时间
   CString               m_strStylish                ;//风格
   CString               m_strColor                  ;//色系
   BOOL                  m_bCheckState               ;//审核标识
   CString               m_strRemark                 ;//备注
   __int64               m_nAssociatedProgrammingID  ;//所属商品规划的ID
   CString               m_strSeriaNum               ;//序号
   CString               m_strDeliveryStartTime      ;//货期起始时间
   CString               m_strDeliveryEndTime        ;//货期结束时间
   CString               m_strShelvesTime            ;//上货日
   CString               m_strCheckUserID            ;//审核人
   CString               m_strCheckTime              ;//审核时间
   CString               m_strCreateUserID;         //创建人
   CString               m_strCreateUserTime;       //创建时间
   __int64               m_nProgrammingID            ;// 
   CString               m_strBrand                  ;//品牌
   int                   m_nYears                    ;//年份
   CString               m_strSeason                 ;//季节
   CString               m_strTradeFairTime          ;//订货会
   CString               m_strArea                   ;//区域
   __int64               m_nAssociatedPlanningID     ;//关联的主题ID
   CString               m_strProgrammingCreateUserID;//创建人
public:
   virtual void ResetData();
   virtual void Copy(CDBViewBandProgrammingInfoData * pData);
   BOOL GetAllDBInfo(CADOConn *pADOConn);				//获取【整条】信息
};

class CDBViewBandProgrammingInfoList : public CDataListMid
{
    DECLARE_SERIAL( CDBViewBandProgrammingInfoList)//序列化（串行化）需要添加的声明
public:
	CDBViewBandProgrammingInfoList();
   ~CDBViewBandProgrammingInfoList();

   void Copy(CDBViewBandProgrammingInfoList *pList);
   void AddItem(CDBViewBandProgrammingInfoData *pItem);
   void DeleteItemByIndex(int nIndex);
#ifdef USING_GRIDCTRL_MARK
   void GetAllDBInfoByCondition(CADOConn *pADO,CString strSQL,MAP_GridCtrl_AllData &mapALLData);    //通过条件获取数据,进行Grid数据填充
#endif
	static CDBViewBandProgrammingInfoList * Instance();
private:
	static std::shared_ptr<CDBViewBandProgrammingInfoList> sm_inst;
};
