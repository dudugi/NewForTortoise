#pragma once
/*************************************************
// <文件>: DBDataDictionary.h
// <说明>: 数据字典信息类
// <作者>: wangzl
// <日期>: 2019/01/30 10:31:05
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 
#include "DataMid.h"
#include "DBKeyDef.h"
#include "DBKeyDef_V.h"
#include "DBKeyDef_Cust.h"

class CADOConn;


class CDBDataDicData :
	public CDataMid
{
	DECLARE_SERIAL( CDBDataDicData)//序列化（串行化）需要添加的声明
public:
	CDBDataDicData(void);
	~CDBDataDicData(void);

public:
	int m_nID;//自增的数据字典对应的ID值
	CString m_strIndex;//索引字符串  -->如:订单类型等
	CString m_strItemCode;//字典对应某项的字典编码
	CString m_strItemName;//字典对应某项的字典名称
   CString m_strItemDescription; //字典对应某项的描述
   CString m_strItemValue; //字典对应某项的值
	CString m_strSysItem;//是否是系统预设项的字符串   _T("1")==表示是订单管理界面添加；_T("")==表示是系统自带
   CString m_strSortCode;//排序编码
public:
	void ResetData();
	void Copy(CDBDataDicData *pData);
	BOOL GetAllDBInfo(CADOConn *pADOConn);			//获取【整条】信息
   BOOL GetAllDBInfoByItemName(CADOConn *pADOCOnn,CString strIndex, vector<CString> &vecItemName);//根据字典索引获取所有字典名称
	BOOL InsertAllDBInfoByID(CADOConn *pADOConn);	//插入【整条】新记录
   BOOL InsertAllDBInfoByAutoCode(CADOConn *pADOConn); //插入【整条】新记录 自动取得合适的编码 如果失败返回ID为1的记录
	BOOL UpdateAllDBInfoByID(CADOConn *pADOConn);	//更新【整条】记录
	BOOL DelAllDBInfoByID(CADOConn *pADOConn);		//删除【整条】记录
	static CDBDataDicData * Instance();		//获取（指针）实例

private:
	static std::shared_ptr<CDBDataDicData> sm_inst;
};

class CDBDataDicList :
	public CDataListMid
{
	DECLARE_SERIAL(CDBDataDicList)
public:
	CDBDataDicList();
	~CDBDataDicList();
	CDBDataDicData* GetItem(int nIndex);			//根据索引获取Item
	CDBDataDicData* GetItemByID(int nID);			//根据ID值获取对应的数据字典的数据
	void AddItem(CDBDataDicData* pItem);			//添加Item
	void DeleteItem(int nIndex);					//删除固定索引Item
	void DeleteItemByID(int nID);					//根据ID值删除对应的项
   void GetAllDBInfoByItemName(CString strIndex, vector<CString> &vecItemName);//根据字典索引获取所有字典名称
	void GetListFromDB(CADOConn *pADOConn);//从数据库获取链表
	static CDBDataDicList * Instance();		//获取（指针）实例


   void GetSizeSortInfo(CADOConn*pAdo,vector<CString>& vecSize);
private:
	static std::shared_ptr<CDBDataDicList> sm_inst;
};

class CDBDicTreeItem : public CDataMid
{
	DECLARE_SERIAL( CDBDicTreeItem)//序列化（串行化）需要添加的声明
public:
	CDBDicTreeItem();
	~CDBDicTreeItem();
public:

   void ResetData();

	void Copy(CDBDicTreeItem *pData);
	CDBDataDicData* GetDataByName(CString strDataName);//根据字典名称获取相关的数据
	CDBDataDicData* GetDataByCode(CString strCode);	//根据字典编码获取相关的数据
	int GetIndexByCode(CString strCode);			//根据字典编码获取想关的索引值 没有找到返回-1

   //************************************
   // <函数>:   AdjustSortCode
   // <说明>:   调整新节点的排序编码
   // <作者>:   wangzl
   // <日期>:   2019/04/12
   // <Access>: public 
   // <Return>: void
   // <参数>:   CDBDataDicData & oNewData 新增的节点 （该节点还不在此链表中
   // <参数>:   const CString & strAfterCode 在哪个编码之后 （对应项的编码  不是排序编码
   //************************************
   void AdjustSortCode(CADOConn * pADOConn,CDBDataDicData & oNewData,const CString & strAfterCode);

	static CDBDicTreeItem * Instance();				//获取（指针）实例

public:
	//一个节点的信息
	CString m_strIndex;
	CDBDataDicList m_DicList;

private:
	static std::shared_ptr<CDBDicTreeItem> sm_inst;
};

class CDBDicTreeItemList : public CDataListMid
{
	DECLARE_SERIAL( CDBDicTreeItemList)//序列化（串行化）需要添加的声明
public:
	CDBDicTreeItemList();
	~CDBDicTreeItemList();
public:
	CDBDicTreeItem* GetItem(int nIndex);			//根据索引获取Item
	CDBDicTreeItem* GetItem(CString strIndex);		//根据索引字符串获取Item
	void AddItem(CDBDicTreeItem* pItem);			//添加Item
	void DeleteItem(int nIndex);					//删除固定索引Item

	void CreateTreeByDicList(CDBDataDicList * pSrcList);//根据所有的数据字典的数据创建数据字典树

	static CDBDicTreeItemList * Instance();			//获取（指针）实例

private:
	static std::shared_ptr<CDBDicTreeItemList> sm_inst;
};