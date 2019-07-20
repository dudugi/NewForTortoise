#pragma once
#include "DataMid.h"

/************************************************************************
 * �������ڣ�2017/05/24     ���ߣ�zhangtao
 * CDBMenusInfo
 * Ŀ�ģ������ݿ�˵�����н���
 ************************************************************************/

class CADOConn;

#include "DBKeyDef.h"
#include "DBKeyDef_V.h"
#include "DBKeyDef_Cust.h"

class CDBMenusInfo :public CDataMid
{
	DECLARE_SERIAL( CDBMenusInfo)//���л������л�����Ҫ��ӵ�����

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
	static CDBMenusInfo * Instance();//��ȡ��ָ�룩ʵ��

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
   COLORREF m_dwBKColor;//����ҳ��ť����ɫ
};

class CDBMenusInfoList : public CDataListMid
{
	DECLARE_SERIAL(CDBMenusInfoList)
public:
	CDBMenusInfoList();
	~CDBMenusInfoList();
public:
	void	Serialize(CArchive& ar);
	CDBMenusInfo* GetItem(int nIndex);			//����������ȡItem
	CDBMenusInfo* GetItemByID(int nID);			//�����û��˻���ȡItem
	CDBMenusInfo* GetItemByItemName(CString strItemName);
	int GetIndexByID(int nID);		
	void AddItem(CDBMenusInfo* pItem);			//���Item
	void DeleteItem(int nIndex);				//ɾ���̶�����Item

	int GetParentCount();
	int GetChildCount();

	void GetListFromDB(CADOConn *pADOConn);//�����ݿ��ȡ����
	static CDBMenusInfoList * Instance();//��ȡ��ָ�룩ʵ��

private:
	static std::shared_ptr<CDBMenusInfoList> sm_inst;
	int m_nParentCount;
	int m_nChildCount;
	void ResetData();
};