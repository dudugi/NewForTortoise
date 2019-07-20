/*************************************************
// <文件>: DBP_ProcessRecords.h
// <说明>: 打样流程记录表
// <作者>: wangzl
// <日期>: 2019/02/22
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 
#pragma once
#include "DataMid.h"
#include "DBKeyDef.h"

class CADOConn;
class CDBP_ProcessRecordsData  : public CDataMid
{
   DECLARE_SERIAL( CDBP_ProcessRecordsData)//序列化（串行化）需要添加的声明
public:
   typedef enum {
      En_UnBegin = -1,
      En_Run = 0,
      En_Finish ,
   }En_Process_State;

public:
   __int64  m_nID                   ;
   __int64  m_nAssociatedProductID  ;//关联产品ID
   CString  m_strReceiveUserID      ;//接收人
   CString  m_strSponsorID          ;//任务发起人
   int      m_nProcessType          ;//对应的工序   此处用ID 表示 主要区分设计 和 工艺 
   CString  m_strInitiateTime       ;//任务发起时间
   CString  m_strRealStartTime      ;//任务实际开始时间
   CString  m_strFinishTime         ;//任务完成时间
   int      m_nState                ;//状态        未开始 进行中 已完成
   BOOL     m_bCheckState           ;//审核
   
public:
   CDBP_ProcessRecordsData();
   ~CDBP_ProcessRecordsData();
   void ResetData();
   void Copy(CDBP_ProcessRecordsData *pData);
   BOOL GetAllDBInfo(CADOConn *pADOConn);
   BOOL DelAllDBInfoByID(CADOConn *pADOConn);
   BOOL UpdateAllDBInfoByID(CADOConn *pADOConn);
   BOOL InsertAllDBInfo(CADOConn *pADOConn);

   void Trim();

};

typedef struct workcontent
{
   CString strGXName;
   CString strPersonCode;
   CString strPersonName;
   CString	strNum_today;
   CString	strNum_month;
   CString strNum_Year;
   CString strNum_Complete;	//完成数量
   CString	strNum_UnComplete;	//未完成数量
}wct;

//工作内容统计 add by lida 2018/01/22
class CDBWorkStatistics
{
public:
   CDBWorkStatistics()
   {
      strOrderNo = _T("");		//订单号
      strGXName = _T("");			//工序名称
      strStaffID = _T("");		//工号
      strStaffName = _T("");		//姓名
      strDirName = _T("");		//基准码目录
      iPian = 0; 					//片
      iFlag = 0;				
   };
   ~CDBWorkStatistics(){};

   CString		strOrderNo;		//订单号
   CString		strGXName;		//工序名称
   CString		strStaffID;		//工号
   CString		strStaffName;	//姓名
   CString		strDirName;		//基准码目录
   int			iPian;			//片
   int			iFlag;			//标识
};

typedef enum
{
   enum_SearchTime_ZhuanRu=0,
   enum_SearchTime_FaChu,
   enum_SearchTime_NoShouHui,
   enum_SearchTime_ShouHui,
   enum_SearchTime_QuanBu,
}ENUM_TIME_SHEARCHTYPE;

class CDBP_ProcessRecordsList : public CDataListMid
{
   DECLARE_SERIAL(CDBP_ProcessRecordsList)
public:
   CDBP_ProcessRecordsList();
   ~CDBP_ProcessRecordsList();
   CDBP_ProcessRecordsData*  GetItem(int nIndex);
   void    AddItem(CDBP_ProcessRecordsData* pItem);
   void    DeleteItem(int nIndex);

   static CDBP_ProcessRecordsList * Instance();//获取（指针）实例

private:
   static std::shared_ptr<CDBP_ProcessRecordsList> sm_inst;
};