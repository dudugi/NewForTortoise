/*************************************************
// <文件>: DBProSet_Style.h
// <说明>: 款式的工序方案表
// <作者>: wangzl
// <日期>: 2019/01/30 10:28:22
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 
#pragma once
#include "DataMid.h"
#include <map>

class CADOConn;

//款式工序配置表  该表配置款式对应的工序默认指派人 2017-11-08 wangzl
class CDBProSet_StyleData : public CDataMid
{
	DECLARE_SERIAL( CDBProSet_StyleData)//序列化（串行化）需要添加的声明
public:
   enum{
      en_Person = 0,//是人员
      en_Group,//是组
   };
public:
	int			m_nID			;//自增ID
	CString		m_strStyleNo	;//款式号
	CString		m_strProName	;//工序名称
	CString		m_strUserID		;//用户ID
	DWORD		   m_dwProTime		;//工序时长
   CString     m_strfPrice;      //工序工价 yangjr 2018/5/3
   CString     m_strcIntro;      //说明 yangjr 2018/5/3
   CString     m_strMark  ;      //默认工价数据标志位   用于工序工价数据修改是辨别是否位默认工序工价   add anjie by 2018/11/22
   CString     m_strGXMark; // 工序标记 luzw 2018/12/21
   int         m_nIsGroup     ;//是否是指派给组的标识
public:
	CDBProSet_StyleData(void);
	~CDBProSet_StyleData(void);

	void ResetData();

	void Copy(CDBProSet_StyleData *pData);

	BOOL GetAllDBInfo(CADOConn *pADOConn);			//获取一条记录信息
	BOOL InsertAllDBInfo(CADOConn *pADOConn);		//插入一条新记录
	BOOL UpdateAllDBInfoByID(CADOConn *pADOConn);	//更新一条信息
	BOOL DelAllDBInfoByID(CADOConn *pADOConn);		//根据用户账户删除记录

	BOOL ClearAllStyleInfo(CADOConn *pADOConn);//清空款式对应的所有记录

   CString GetGongJiaByStyleNoAndProName(CADOConn *pADOConn,CString strStyleNo,CString strProName);		//根据工序名称以及款式号获取对应的工序价格

	CString GetInsertStr();
   CString GetUpdateStr(CString fieldStr,CString valueStr);
   CString GetUpdateStr2();   //更新工价和标志位字段
   CString GetDeleteByStyleNoSql(CString strStyleNo);  
   
};
typedef struct  
{
   int			m_nID			;//自增ID   
   CString		m_strUserID		;//用户ID
   DWORD		m_dwProTime		;//工序时长
}S_ONE_STYLEPROSET;
typedef std::map<CString,S_ONE_STYLEPROSET> MAP_OneStyleProSet;//一个款式对应工序的工序记录；
class CDBProSet_StyleList  : public CDataListMid
{
	DECLARE_SERIAL(CDBProSet_StyleList)
public:
	CDBProSet_StyleList();
	~CDBProSet_StyleList();

   void Copy(CDBProSet_StyleList *pList);
	CDBProSet_StyleData* GetItem(int nIndex);			//根据索引获取Item
	CDBProSet_StyleData* GetItemByName(CString strProName);
	void AddItem(CDBProSet_StyleData* pItem);			//添加Item
   void AddItem_Before(int nIndex, CDBProSet_StyleData* pItem);
   void AddItem_After(int nIndex, CDBProSet_StyleData* pItem);
	void DeleteItem(int nIndex);					//删除固定索引Item

	BOOL InsertAllDBInfo(CADOConn * pADOConn,CString strStyleNo);
   //根据款式号获取对应工序 yangjr 2018/5/4
   BOOL GetProSetStyleData(CADOConn * pADOConn,CString strStyleNo);

   BOOL GetGongJiaMapByStyle(CADOConn *pADOConn,CString strStyleNo,std::map<CString,double> &mapData);		//根据款式号获取所有的工序价格 yangjr 2018-1-17
   CString GetGongJiaByStyleNoAndProName(CADOConn *pADOConn,CString strStyleNo,CString strProName);		//根据工序名称以及款式号获取对应的工序价格

   BOOL UpdateZhiPaiPerson(CADOConn * pADOConn,CString strStyleNo);
   BOOL UpdateMemo(CADOConn * pADOConn,CString strStyleNo);

   //根据款号，工序获取对应的备注信息，工序为空则获取全部的信息 add by lida 2018/05/22
   CString GetStyleInfo(__in CADOConn * pADOConn,__in CString strStyleNo,__in vector<CString> vecGX=vector<CString>(),BOOL bWithProName = TRUE);
};


//工序工价excel导入
typedef struct my_proset_style_info
{
   my_proset_style_info()
   {  
      m_strStyleNo	= _T("");
      m_strProName	= _T("");
      m_strUserID	= _T("");
      m_strfPrice = _T(""); 
   };

   CString GetUpdateSql(BOOL bIgnoreNull = TRUE);

   CString GetInsertSql();

   CString		m_strStyleNo	;//款式号
   CString		m_strProName	;//工序名称
   CString		m_strUserID;//用户ID
   CString      m_strfPrice;   //工序工价 
   CString      m_strMark;    //工价更新标志（用于确定是否更新默认工序工价） add anjie by 2019/03/26
}s_my_proset_style_info;

