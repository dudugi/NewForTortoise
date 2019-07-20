/*************************************************
// <文件>: DBP_ProductStructurePlanning.h
// <说明>: 产品表留存有波段和主题的绝大部分数据
// <作者>: wangzl
// <日期>: 2019/02/22
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 
#pragma once
#include "DataMid.h"
#include "DBKeyDef.h"
#include "DBP_Programming.h"
#include "DBBindInfo.h"
#include "DBP_Planning.h"
class CADOConn;

class CDBP_ProductStructurePlanningData  : public CDataMid
{
   DECLARE_SERIAL( CDBP_ProductStructurePlanningData)//序列化（串行化）需要添加的声明
public:

   __int64  m_nID                         ;
   CString  m_strClassification           ;//分类
   CString  m_strCategory                 ;//品类
   CString  m_strPieceNum                 ;//件数
   CString  m_strColor                    ;//色号
   CString  m_strSize                     ;//尺码
   CString  m_strFabric                   ;//面料
   CString  m_strFashion                  ;//造型风格
   CString  m_strContour                  ;//廓形
   double   m_fPrice_Ceiling              ;//价格上限
   double   m_fPrice_Floor                ;//价格下限
   double   m_fPrice_Tag                  ;//吊牌价
   CString  m_strRemark                   ;//备注
   CString  m_strBand_Name                ;//名称
   CString  m_strBand_BandStartTime       ;//波段开始时间
   CString  m_strBand_DesignEndTime       ;//设计完成时间
   CString  m_strBand_PatternEndTime      ;//纸样完成时间
   CString  m_strBand_ReviewEndTime       ;//内审会完成时间
   CString  m_strBand_BandEndTime         ;//波段结束时间
   CString  m_strBand_DeliveryStartTime   ;//货期起始时间
   CString  m_strBand_DeliveryEndTime     ;//货期结束时间
   CString  m_strBand_ShelvesTime         ;//上货日
   CString  m_strBand_Stylish             ;//风格
   CString  m_strBand_Color               ;//色系
   CString  m_strCreateUserID             ;//创建人
   CString  m_strCreateTime               ;//创建时间
   int      m_nCreateFlag                 ;//创建标识
   CString  m_strProgramming_Brand        ;//品牌
   CString  m_strProgramming_Years        ;//年度
   CString  m_strProgramming_Season       ;//季节
   CString  m_strProgramming_TradeFairTime;//订货会时间
   CString  m_strProgramming_Area         ;//区域
   CString  m_strPlanning_SubjectName     ;//主题名
   BOOL     m_bSubmitState                ;//提交状态
   CString  m_strSubmitUserID             ;//提交人
   CString  m_strSubmitTime               ;//提交时间
   CString  m_strCheckUserID              ;//审核人
   CString  m_strCheckTime                ;//审核时间
   BOOL     m_bCheckState                 ;//审核状态
   int      m_nCurProSort                 ;//当前流程所属
   BOOL     m_bRevision                   ;//改版标识
   CString  m_strRevisionReason           ;//改版原因

public:
   CDBP_ProductStructurePlanningData();
   ~CDBP_ProductStructurePlanningData();
   void ResetData();
   void Copy(CDBP_ProductStructurePlanningData *pData);
   BOOL GetAllDBInfo(CADOConn *pADOConn);
   BOOL DelAllDBInfoByID(CADOConn *pADOConn);
   BOOL UpdateAllDBInfoByID(CADOConn *pADOConn);
   BOOL InsertAllDBInfo(CADOConn *pADOConn);
   BOOL CopyToDBProgrammingAndBindPlanningID(CDBP_ProgrammingData *pProgrammingData,__int64 nID); // 拷贝商品企划信息到企划表,绑定主题ID
   BOOL CopyToDBBandAndBindProgrammingID(CDBP_BindInfoData *pDBBandInfo,__int64 nID); // 拷贝波段信息到波段表，绑定企划ID
   BOOL CopyToDBPlanning(CDBP_PlanningData *pDBPlanningInfo); // 拷贝主题信息到主题表
   void Trim();

};

class CDBP_ProductStructurePlanningList : public CDataListMid
{
   DECLARE_SERIAL(CDBP_ProductStructurePlanningList)
public:
   CDBP_ProductStructurePlanningList();
   ~CDBP_ProductStructurePlanningList();
   CDBP_ProductStructurePlanningData*  GetItem(int nIndex);
   CDBP_ProductStructurePlanningData*  GetItemByID(__int64 nID);
   void    AddItem(CDBP_ProductStructurePlanningData* pItem);
   void    DeleteItem(int nIndex);

   static CDBP_ProductStructurePlanningList * Instance();//获取（指针）实例

private:
   static std::shared_ptr<CDBP_ProductStructurePlanningList> sm_inst;
};