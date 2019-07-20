#pragma once
#include "DataMid.h"
#include "DBKeyDef.h"
#include "DBDef.h"

/********************************************************
*filename: 	DBBindInfo.h
*author:		anjie
*description:波段信息操作相关
*file path:	D:\workspace\PDM\一单多件版\CommonClass\ClassDB
*date:	2019/2/18 15:50
********************************************************/

class CADOConn;
class CDBP_BindInfoData :public CDataMid
{
   DECLARE_SERIAL(CDBP_BindInfoData)//序列化（串行化）需要添加的声明
public:
   __int64                   m_nID;
   CString               m_strName;                 //名称
   CString               m_oleBandStartTime;        //波段开始时间
   CString               m_oleDesignEndTime;        //设计完成时间
   CString               m_olePatternEndTime;       //纸样完成时间
   CString               m_oleReviewEndTime;        //内审会完成时间
   CString               m_oleBandEndTime;          //波段结束时间
   CString               m_strStylish;              //风格
   CString               m_strColor;                //色系
   BOOL                  m_bCheckState;             //审核标识
   CString               m_strRemark;               //备注
   __int64                m_nAssociatedProgrammingID;                 //所属商品规划的ID
   CString               m_strSeriaNum;               //序号
   CString               m_strDeliveryStartTime;    //货期起始时间
   CString               m_strDeliveryEndTime;      //货期结束时间
   CString               m_strShelvesTime;          //上货日
   CString               m_strCheckUserID;          //审核人
   CString               m_strCheckTime;            //审核时间
   CString               m_strCreateUserID;         //创建人
   CString               m_strCreateUserTime;       //创建时间
public:
   CDBP_BindInfoData(void);
   ~CDBP_BindInfoData(void);
   void ResetData();
   void Copy(CDBP_BindInfoData *pData);
   BOOL GetAllDBInfo(CADOConn *pADOConn);				//获取【整条】信息
   BOOL GetAllDBInfoByID(CADOConn *pADOConn);
   BOOL InsertAllDBInfo(CADOConn *pADOConn);	//插入【整条】新记录
   BOOL UpdateAllDBInfoByID(CADOConn *pADOConn);	//根据用户账户更新【整条】记录
   BOOL UpdateCheckInfoByID(CADOConn *pADOConn);	
   BOOL DelAllDBInfoByID(CADOConn *pADOConn);		//根据用户账户删除【整条】记录
};

class CDBP_BindInfoList :public CDataListMid
{
   DECLARE_SERIAL( CDBP_BindInfoList)//序列化（串行化）需要添加的声明
public:
   CDBP_BindInfoList(void);
   ~CDBP_BindInfoList(void);
public:
   void Copy(CDBP_BindInfoList *pList);
   void AddItem(CDBP_BindInfoData *pItem);
   void DeleteItemByIndex(int nIndex);
   BOOL InsertAllDBtoDB(CADOConn *pADO,__int64 nProgrammingID);

#ifdef USING_GRIDCTRL_MARK
   void GetAllDBInfoByProgrammingID( CADOConn *pADO,CString  strProgrammingID,MAP_GridCtrl_AllData &mapALLData );
#endif
};
