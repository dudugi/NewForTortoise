#pragma once
/*************************************************
// <�ļ�>: DBDataDictionary.h
// <˵��>: �����ֵ���Ϣ��
// <����>: wangzl
// <����>: 2019/01/30 10:31:05
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
#include "DataMid.h"
#include "DBKeyDef.h"
#include "DBKeyDef_V.h"
#include "DBKeyDef_Cust.h"

class CADOConn;


class CDBDataDicData :
	public CDataMid
{
	DECLARE_SERIAL( CDBDataDicData)//���л������л�����Ҫ��ӵ�����
public:
	CDBDataDicData(void);
	~CDBDataDicData(void);

public:
	int m_nID;//�����������ֵ��Ӧ��IDֵ
	CString m_strIndex;//�����ַ���  -->��:�������͵�
	CString m_strItemCode;//�ֵ��Ӧĳ����ֵ����
	CString m_strItemName;//�ֵ��Ӧĳ����ֵ�����
   CString m_strItemDescription; //�ֵ��Ӧĳ�������
   CString m_strItemValue; //�ֵ��Ӧĳ���ֵ
	CString m_strSysItem;//�Ƿ���ϵͳԤ������ַ���   _T("1")==��ʾ�Ƕ������������ӣ�_T("")==��ʾ��ϵͳ�Դ�
   CString m_strSortCode;//�������
public:
	void ResetData();
	void Copy(CDBDataDicData *pData);
	BOOL GetAllDBInfo(CADOConn *pADOConn);			//��ȡ����������Ϣ
   BOOL GetAllDBInfoByItemName(CADOConn *pADOCOnn,CString strIndex, vector<CString> &vecItemName);//�����ֵ�������ȡ�����ֵ�����
	BOOL InsertAllDBInfoByID(CADOConn *pADOConn);	//���롾�������¼�¼
   BOOL InsertAllDBInfoByAutoCode(CADOConn *pADOConn); //���롾�������¼�¼ �Զ�ȡ�ú��ʵı��� ���ʧ�ܷ���IDΪ1�ļ�¼
	BOOL UpdateAllDBInfoByID(CADOConn *pADOConn);	//���¡���������¼
	BOOL DelAllDBInfoByID(CADOConn *pADOConn);		//ɾ������������¼
	static CDBDataDicData * Instance();		//��ȡ��ָ�룩ʵ��

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
	CDBDataDicData* GetItem(int nIndex);			//����������ȡItem
	CDBDataDicData* GetItemByID(int nID);			//����IDֵ��ȡ��Ӧ�������ֵ������
	void AddItem(CDBDataDicData* pItem);			//���Item
	void DeleteItem(int nIndex);					//ɾ���̶�����Item
	void DeleteItemByID(int nID);					//����IDֵɾ����Ӧ����
   void GetAllDBInfoByItemName(CString strIndex, vector<CString> &vecItemName);//�����ֵ�������ȡ�����ֵ�����
	void GetListFromDB(CADOConn *pADOConn);//�����ݿ��ȡ����
	static CDBDataDicList * Instance();		//��ȡ��ָ�룩ʵ��


   void GetSizeSortInfo(CADOConn*pAdo,vector<CString>& vecSize);
private:
	static std::shared_ptr<CDBDataDicList> sm_inst;
};

class CDBDicTreeItem : public CDataMid
{
	DECLARE_SERIAL( CDBDicTreeItem)//���л������л�����Ҫ��ӵ�����
public:
	CDBDicTreeItem();
	~CDBDicTreeItem();
public:

   void ResetData();

	void Copy(CDBDicTreeItem *pData);
	CDBDataDicData* GetDataByName(CString strDataName);//�����ֵ����ƻ�ȡ��ص�����
	CDBDataDicData* GetDataByCode(CString strCode);	//�����ֵ�����ȡ��ص�����
	int GetIndexByCode(CString strCode);			//�����ֵ�����ȡ��ص�����ֵ û���ҵ�����-1

   //************************************
   // <����>:   AdjustSortCode
   // <˵��>:   �����½ڵ���������
   // <����>:   wangzl
   // <����>:   2019/04/12
   // <Access>: public 
   // <Return>: void
   // <����>:   CDBDataDicData & oNewData �����Ľڵ� ���ýڵ㻹���ڴ�������
   // <����>:   const CString & strAfterCode ���ĸ�����֮�� ����Ӧ��ı���  �����������
   //************************************
   void AdjustSortCode(CADOConn * pADOConn,CDBDataDicData & oNewData,const CString & strAfterCode);

	static CDBDicTreeItem * Instance();				//��ȡ��ָ�룩ʵ��

public:
	//һ���ڵ����Ϣ
	CString m_strIndex;
	CDBDataDicList m_DicList;

private:
	static std::shared_ptr<CDBDicTreeItem> sm_inst;
};

class CDBDicTreeItemList : public CDataListMid
{
	DECLARE_SERIAL( CDBDicTreeItemList)//���л������л�����Ҫ��ӵ�����
public:
	CDBDicTreeItemList();
	~CDBDicTreeItemList();
public:
	CDBDicTreeItem* GetItem(int nIndex);			//����������ȡItem
	CDBDicTreeItem* GetItem(CString strIndex);		//���������ַ�����ȡItem
	void AddItem(CDBDicTreeItem* pItem);			//���Item
	void DeleteItem(int nIndex);					//ɾ���̶�����Item

	void CreateTreeByDicList(CDBDataDicList * pSrcList);//�������е������ֵ�����ݴ��������ֵ���

	static CDBDicTreeItemList * Instance();			//��ȡ��ָ�룩ʵ��

private:
	static std::shared_ptr<CDBDicTreeItemList> sm_inst;
};