#pragma once

#include "DataMid.h" 


//by zhangyx 2017/12/12

////////////////////////数据库表中字段格式///////////////////////////////////////

#define DBDatabaseFields_Key_Name		_T("col_name")
#define DBDatabaseFields_Key_Type		_T("col_typename")
#define DBDatabaseFields_Key_Length		_T("col_len")
#define DBDatabaseFields_Key_Prec	    _T("col_prec")
#define DBDatabaseFields_Key_Scale		_T("col_scale")
#define DBDatabaseFields_Key_Seed       _T("col_seed")
#define DBDatabaseFields_Key_Increment	_T("col_increment")

class CDBDatabaseFields : public CDataMid
{
	DECLARE_SERIAL( CDBDatabaseFields)//序列化（串行化）需要添加的声明
public:
	CString m_strFieldsName;
	CString m_strFieldsType;
	int m_nFieldsLength; //一般类型长度
	int m_nFieldsPrec;	//特殊类型的整数位数
	int m_nFieldsScale;	//特殊类型的小数位数
	int m_nFieldsSeed;	
	int m_nFieldsIncrement;
	BOOL m_bFieldsPrimary;



public:
	CDBDatabaseFields(void);
	~CDBDatabaseFields(void);
	void ResetData();
	void Copy(CDBDatabaseFields *pData);
	void Serialize(CArchive& ar);
};

class CDBDatabaseFieldsList : public CDataListMid
{
	DECLARE_SERIAL( CDBDatabaseFieldsList)//序列化（串行化）需要添加的声明
public:
	CDBDatabaseFieldsList(void);
	~CDBDatabaseFieldsList(void);
	CDBDatabaseFields* GetItem(int nIndex);	//根据索引获取Item
	void AddItem(CDBDatabaseFields* pItem);	//添加Item
	void DeleteItem(int nIndex);			//删除固定索引Item
};


////////////////////////数据库表名称///////////////////////////////////////
class CDBDatabaseTable : public CDataMid
{
	DECLARE_SERIAL( CDBDatabaseTable)//序列化（串行化）需要添加的声明
public:
	CString m_strTableName;
	CDBDatabaseFieldsList m_listFields;

public:
	CDBDatabaseTable(void);
	~CDBDatabaseTable(void);
	void ResetData();
	void Copy(CDBDatabaseTable *pData);
	void Serialize(CArchive& ar);
};

class CDBDatabaseTableList : public CDataListMid
{
	DECLARE_SERIAL( CDBDatabaseTableList)//序列化（串行化）需要添加的声明

public:
	CDBDatabaseTableList(void);
	~CDBDatabaseTableList(void);
	CDBDatabaseTable* GetItem(int nIndex);	//根据索引获取Item
	CDBDatabaseTable* GetItem(CString strTableName);	//根据名称获取Item
	void AddItem(CDBDatabaseTable* pItem);	//添加Item
	void DeleteItem(int nIndex);			//删除固定索引Item
};

