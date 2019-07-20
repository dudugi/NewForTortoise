#pragma once
#include "DataMid.h"

/************************************************************************
 * 创建日期：2017/05/24     作者：zhangtao
 * CDBMenusInfo
 * 目的：与数据库菜单表进行交互
 ************************************************************************/

class CADOConn;

#include "DBKeyDef.h"
#include "DBKeyDef_V.h"
#include "DBKeyDef_Cust.h"

class CDBMenusInfo :public CDataMid
{
	DECLARE_SERIAL( CDBMenusInfo)//序列化（串行化）需要添加的声明

public:
	CDBMenusInfo();
	~CDBMenusInfo(void);
	void ResetData();
	void Serialize(CArchive& ar);
	BOOL GetAllDBInfo(CADOConn *pADOConn);
	BOOL InsertAllDBInfo(CADOConn *pADOConn);
	BOOL DelAllDBInfoByID(CADOConn *pADOConn);
	BOOL UpdateAllDBInfoByID(CADOConn *pADOConn);
	void Copy(CDBMenusInfo *pData);
	void Swap(CDBMenusInfo *pData);
	static CDBMenusInfo * Instance();//获取（指针）实例

private:
	static std::shared_ptr<CDBMenusInfo> sm_inst;

public:
	int m_nAutoID;
	int m_nID;
	int m_nPID;
	int m_nSortID;
	CString m_strItemName;
	int m_nShowLeft;
	int m_nLeftImg;
	int m_nImgIndex;
	int m_nImgCate;
	CString m_strFrmName;
	CString m_strDllName;
	CString m_strItemShow;
   COLORREF m_dwBKColor;//导航页按钮背景色
};

class CDBMenusInfoList : public CDataListMid
{
	DECLARE_SERIAL(CDBMenusInfoList)
public:
	CDBMenusInfoList();
	~CDBMenusInfoList();
public:
	void	Serialize(CArchive& ar);
	CDBMenusInfo* GetItem(int nIndex);			//根据索引获取Item
	CDBMenusInfo* GetItemByID(int nID);			//根据用户账户获取Item
	CDBMenusInfo* GetItemByItemName(CString strItemName);
	int GetIndexByID(int nID);		
	void AddItem(CDBMenusInfo* pItem);			//添加Item
	void DeleteItem(int nIndex);				//删除固定索引Item

	int GetParentCount();
	int GetChildCount();

	void GetListFromDB(CADOConn *pADOConn);//从数据库获取链表
	static CDBMenusInfoList * Instance();//获取（指针）实例

private:
	static std::shared_ptr<CDBMenusInfoList> sm_inst;
	int m_nParentCount;
	int m_nChildCount;
	void ResetData();
};