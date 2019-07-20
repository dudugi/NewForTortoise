/*************************************************
// <文件>: DBStyleSizeInfo.h
// <说明>: 版房款式管理--尺寸信息
// <作者>: liuhw
// <日期>: 2019/05/09 14:16:45
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 
#pragma once

#include "DataMid.h"
#include <map>

//数据库中字段
class CADOConn;

class CDBStyleChiMaInfoData  : public CDataMid
{
	DECLARE_SERIAL( CDBStyleChiMaInfoData)//序列化（串行化）需要添加的声明
public:
   __int64 m_nID;//ID
   CString m_cKuanhao;//款号
   CString m_cChima;//尺码
   int     m_iBase;//是否为基码
public:
	CDBStyleChiMaInfoData();
	~CDBStyleChiMaInfoData();
	void ResetData();
	void Copy(CDBStyleChiMaInfoData *pData);
	void Serialize(CArchive& ar);
   BOOL IsBasicMa(CADOConn *pADOConn);//判断是否为基码
	//数据库操作函数
	BOOL GetAllDBInfo(CADOConn *pADOConn);			//获取【整条】信息
	BOOL InsertAllDBInfo(CADOConn *pADOConn);		//插入【整条】新记录
   void GetInsertAllDBSql(CString &strSql);
	BOOL UpdateAllDBInfoByID(CADOConn *pADOConn);	//根据用户账户更新【整条】记录
	BOOL DelAllDBInfoByID(CADOConn *pADOConn);		//根据用户账户删除【整条】记录
   BOOL DelAllDBInfoByStyleNo(CADOConn *pADOConn);
   CString GetDelAllDBInfoByStyleNoSql(CString strStyleNo);
	static CDBStyleChiMaInfoData * Instance();		//获取（指针）实例

private:
	static std::shared_ptr<CDBStyleChiMaInfoData> sm_inst;
};

class CDBStyleChiMaInfoList : public CDataListMid
{
	DECLARE_SERIAL(CDBStyleChiMaInfoList)
public:
	CDBStyleChiMaInfoList();
	~CDBStyleChiMaInfoList();
	CDBStyleChiMaInfoData*  GetItem(int nIndex);
	void    AddItem(CDBStyleChiMaInfoData* pItem);
	void    DeleteItem(int nIndex);
   
	static CDBStyleChiMaInfoList * Instance();	//获取（指针）实例
private:
	static std::shared_ptr<CDBStyleChiMaInfoList> sm_inst;
};

class CDBStyleSizeInfoData  : public CDataMid
{
	DECLARE_SERIAL( CDBStyleSizeInfoData)//序列化（串行化）需要添加的声明
public:
   __int64 m_nID;        //ID
   CString m_cKuanhao;   //款号
   CString m_cChima;     //尺码
   int     m_iPartID;    //部位ID
   double  m_fSize;      //尺寸
   CString m_strSize;      //尺寸 字符串,只读，不做插入和更新
   CString m_cFangAn;  //款式的尺寸方案名称
public:
	CDBStyleSizeInfoData();
	~CDBStyleSizeInfoData();
	void ResetData();
	void Copy(CDBStyleSizeInfoData *pData);
	void Serialize(CArchive& ar);
	BOOL InsertAllDBInfo(CADOConn *pADOConn);	//插入【整条】新记录
   BOOL UpdateAllDBInfoByID(CADOConn *pADOConn);	//根据用户账户更新【整条】记录
   void GetUpdateAllDBInfoByStyleNo(CString &strSql);
   void GetInsertAllDBInfo(CString &strSQL);
   BOOL DelAllDBInfoByID(CADOConn *pADOConn);
   BOOL DelAllDBInfoByStyleNo(CADOConn *pADOConn);
   CString GetDelAllDBInfoByStyleNoSql(CString strStyleNo);
   void GetAllDBInfo(CADOConn *pADOConn);
	static CDBStyleSizeInfoData * Instance();	//获取（指针）实例
private:
	static std::shared_ptr<CDBStyleSizeInfoData> sm_inst;
};

class CDBStyleSizeInfoList : public CDataListMid
{
	DECLARE_SERIAL(CDBStyleSizeInfoList)
public:
	CDBStyleSizeInfoList();
	~CDBStyleSizeInfoList();
   CDBStyleSizeInfoData*  GetItem(int nIndex);
   void  AddItem(CDBStyleSizeInfoData* pItem);
   void  DeleteItem(int nIndex);
   void  DeleteAllList();
   BOOL  GetStyleNoAllDBInfo(CADOConn *pADOConn,CString strStyleNo,CString &strBasicMa);//获取该款式的所有信息

   BOOL  GetStyleNoAllDBInfo(CADOConn *pADOConn,CString strStyleNo,BOOL bDecimalPoint = FALSE);//获取该款式的所有信息 bDecimalPoint 要不要小数点

   void  CopyList(CDBStyleSizeInfoList* pList);
   BOOL  InsertAllDBListInfo(CADOConn *pADOConn);
   map<int,map<CString,CString>> CreateMapSizeData();//返回部位为KEY，尺码，跟尺寸为value
	static CDBStyleSizeInfoList * Instance();	//获取（指针）实例

private:
	static std::shared_ptr<CDBStyleSizeInfoList> sm_inst;
};



