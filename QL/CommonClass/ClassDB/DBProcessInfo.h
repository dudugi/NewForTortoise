/*************************************************
// <文件>: DBProcessInfo.h
// <说明>: 工序信息类
// <作者>: wangzl
// <日期>: 2019/01/30 10:20:57
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 
#pragma once
#include "DataMid.h"
#include <map>
#include "DBProcessRecords.h"
class CADOConn;


#define LimitHourDefafult  24//限制时长默认值
class CDBProcessInfoData :
	public CDataMid
{
	DECLARE_SERIAL( CDBProcessInfoData)//序列化（串行化）需要添加的声明

   enum EM_OTHER_STATE_MOD
   {
      emGxOTM_Null = 0x0,           //初始化值:无任何标志
      emGxOTM_Outsourcing = 0x1,    //委外标志;
      emGxOTM_PieceworkInstore = 0x2,  //计件入库   	by WangZY 2019/01/18
      emGxOTM_ShowHintForDelivery = 0x4,  //发货选客户时弹窗提示	by WangZY 2019/02/15
      emGxOTM_OtherMore = 0x8,      //样例，暂无用处
      //emGxOTM_NextDemo = 0x10,     //样例，暂无用处
      //...更多其他
   };

public:
   INT64    m_nID          ;//工序ID
   CString  m_strProName   ;//工序名称
   CString  m_strProField  ;//工价字段
   CString  m_strProItem   ;//工序项目
   CString  m_strProChoose ;//员工可选
   UINT     m_nSortID      ;//排序ID
   int      m_nGetYarn     ;//是否领用纱线
   int      m_nProCarryOut ;//是否必扫
   int      m_nCanEditCost ;//是否可以编辑工价
   CString  m_strProUpdate ;//更新状态
   CString  m_strPartLimit ;//限制部门
   CString  m_strPrevPro   ;//前道工序
   CString  m_strProRemark ;//备注
   CString  m_strSysItem   ;//绑定到对应工序的字符串
   int      m_nLimitHour   ;//工序限制的时长（用于超时警报）
   CString  m_strZhipaiPerson   ;//对应工序的默认指派人
   CString  m_strDefaultGXGongjia;//工序默认工价
   int      m_iTipPrice;      //提示需要修改工价 0:不提示，1:提示
   CString  m_strBindRole;//绑定的角色  （角色名称）
   ///////////////////////////////
   //工序其他状态组合标志(共32位分别表示32种状态的组合，
   //目前只用到0位表示是否委外工序;其他供后期拓展用
   //		by WangZY 2018/09/13
   EM_OTHER_STATE_MOD   m_nOtherState;    
public:
   CDBProcessInfoData(void);
   ~CDBProcessInfoData(void);
   void ResetData();
   void Copy(CDBProcessInfoData *pData);
   void Swap(CDBProcessInfoData *pData);
   void Serialize(CArchive& ar);
   BOOL GetAllDBInfo(CADOConn *pADOConn);		//获取【整条】信息
   BOOL InsertAllDBInfoByName(CADOConn *pADOConn);	//插入【整条】新记录
   BOOL UpdateAllDBInfoByName(CADOConn *pADOConn,CString strOldName);	//根据旧名称更新【整条】记录
   BOOL UpdateAllDBInfoByID(CADOConn *pADOConn);
   BOOL DelAllDBInfoByName(CADOConn *pADOConn);		//根据名称删除【整条】记录
   BOOL GetAllDBInfoByName(CADOConn *pADOConn);		//获取【整条】信息

   //比较修改前后数据，将修改了的数据保存起来
   CString SetDBEquals_Log(CDBProcessInfoData &pOldData);

   //验证是否包含有某一个状态（参数如果是组合状态只需拥有一种返回真）		by WangZY 2018/09/13
   BOOL TestGXIncludeOtherState (EM_OTHER_STATE_MOD emStateInclude) const;
   BOOL TestGXIncludeOtherState (EM_OTHER_STATE_MOD emStateInclude,EM_OTHER_STATE_MOD emCurState) const;

   //验证是否拥有某个状态（参数如果是组合状态必须全部拥有返回真）		by WangZY 2018/09/13
   BOOL TestGXOtherState(EM_OTHER_STATE_MOD emStateTest);

   //移除某个状态		by WangZY 2018/09/13
   BOOL RemoveOtherState(EM_OTHER_STATE_MOD emStateRemove);

   //添加某个状态		by WangZY 2018/09/13
   BOOL AddOtherState(EM_OTHER_STATE_MOD emStateAdd);

   BOOL GetGongXuSort(CADOConn* pADOConn,__out map<int,CString>& map_gx_sort);
   static CDBProcessInfoData * Instance();	//获取（指针）实例


private:
	static std::shared_ptr<CDBProcessInfoData> sm_inst;
};

class CDBProcessInfoList :
	public CDataListMid
{
DECLARE_SERIAL( CDBProcessInfoList)//序列化（串行化）需要添加的声明
public:
	CDBProcessInfoList();
	~CDBProcessInfoList();

	CDBProcessInfoData* GetItem(int nIndex);			//根据索引获取Item
	CDBProcessInfoData* GetItemByName(CString strName);	//根据名称获取Item
	CDBProcessInfoData* GetItemByID(INT64 nID);			//根据ID获取Item
   CDBProcessInfoData* GetItemBySortId(int nSortId);//根据排序ID取Item
   CDBProcessInfoData* GetSysItem(CDBProcessRecordsData::Assign_Default_ProID nProID);//获取绑定到某个CAD的工序
   CDBProcessInfoData* GetItemByRole(const CString & strRole);//根据角色获取对应的Item
	int GetIndexByName(CString strName);				//根据名称获取索引
	int GetIndexByID(INT64 nID);
	void AddItem(CDBProcessInfoData* pItem);			//添加Item
	void DeleteItem(int nIndex);						//删除固定索引Item
	void DeleteItemByName(CString strName);				//根据名称删除相关的item

	void SortBySortID();//根据工序的SortID对链表进行排序
   
	void GetListFromDB(CADOConn *pADOConn);//从数据库获取链表
	static CDBProcessInfoList * Instance();	//获取（指针）实例


   //************************************
   // Method:    获取是否可以编辑工价
   // Author:    wuZhiHua
   // Date : 	  2018/03/26
   // Access:    public 
   // Returns:   BOOL
   // Parameter: CADOConn * pADOConn
   // Parameter: std::map<CString
   // Parameter: bool> & mapProNameCanEditCost
   //************************************
   BOOL GetCanEditCostMap(CADOConn *pADOConn , std::map<CString , bool> &mapProNameCanEditCost);

   static BOOL GetTipPriceFlag(CADOConn* pADo,CString strGXName);

#ifdef USING_GRIDCTRL_MARK
	MAP_GridCtrl_AllData CreateGridData();

#endif // USING_GRIDCTRL_MARK

private:
	static std::shared_ptr<CDBProcessInfoList> sm_inst;
};

