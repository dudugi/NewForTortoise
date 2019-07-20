#pragma once

#include "DataMid.h" 


//by zhangyx 2017/12/12

////////////////////////���ݿ�����ֶθ�ʽ///////////////////////////////////////

#define DBDatabaseFields_Key_Name		_T("col_name")
#define DBDatabaseFields_Key_Type		_T("col_typename")
#define DBDatabaseFields_Key_Length		_T("col_len")
#define DBDatabaseFields_Key_Prec	    _T("col_prec")
#define DBDatabaseFields_Key_Scale		_T("col_scale")
#define DBDatabaseFields_Key_Seed       _T("col_seed")
#define DBDatabaseFields_Key_Increment	_T("col_increment")

class CDBDatabaseFields : public CDataMid
{
	DECLARE_SERIAL( CDBDatabaseFields)//���л������л�����Ҫ��ӵ�����
public:
	CString m_strFieldsName;
	CString m_strFieldsType;
	int m_nFieldsLength; //һ�����ͳ���
	int m_nFieldsPrec;	//�������͵�����λ��
	int m_nFieldsScale;	//�������͵�С��λ��
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
	DECLARE_SERIAL( CDBDatabaseFieldsList)//���л������л�����Ҫ��ӵ�����
public:
	CDBDatabaseFieldsList(void);
	~CDBDatabaseFieldsList(void);
	CDBDatabaseFields* GetItem(int nIndex);	//����������ȡItem
	void AddItem(CDBDatabaseFields* pItem);	//���Item
	void DeleteItem(int nIndex);			//ɾ���̶�����Item
};


////////////////////////���ݿ������///////////////////////////////////////
class CDBDatabaseTable : public CDataMid
{
	DECLARE_SERIAL( CDBDatabaseTable)//���л������л�����Ҫ��ӵ�����
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
	DECLARE_SERIAL( CDBDatabaseTableList)//���л������л�����Ҫ��ӵ�����

public:
	CDBDatabaseTableList(void);
	~CDBDatabaseTableList(void);
	CDBDatabaseTable* GetItem(int nIndex);	//����������ȡItem
	CDBDatabaseTable* GetItem(CString strTableName);	//�������ƻ�ȡItem
	void AddItem(CDBDatabaseTable* pItem);	//���Item
	void DeleteItem(int nIndex);			//ɾ���̶�����Item
};

