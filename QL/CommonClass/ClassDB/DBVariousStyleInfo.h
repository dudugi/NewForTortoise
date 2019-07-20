#pragma once
/*************************************************
// <�ļ�>: DBVariousStyleInfo.h
// <˵��>: ���ݿ������-��ʽ��Ӧ��ѡ����
// <����>: yangjr
// <����>: 2019/02/20 16:52:29
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
#include "DataMid.h"

class CADOConn;


//#define  DBOrder_key_LastTime		  _T("dLastTime")//������������ʱ��


class CDBVariousStyleInfoData :
	public CDataMid
{
public:
	CDBVariousStyleInfoData(void);
	virtual ~CDBVariousStyleInfoData(void);

	typedef enum En_Ord_Perferred
	{
		Ord_UnPerferred = 0,//����ѡ
		Ord_Perferred,//��ѡ
	}EN_ORD_PERFERRED;

	int				m_nID				;//����ID
	CString			m_strStyleNo		;//���
	CString			m_strOrderNo		;//������
	CString			m_strDestribution	;//����
	int				m_nPreferred		;//�Ƿ���ѡ
	
	COleDateTime	m_dtOrdUpdate		;//�����ĸ���ʱ�� ֮ǰ���������  һ������޸�ʱû���˸���ʱ��  ��ȡ���Ƕ�������ʵ�µ�ʱ�� wangzl 2018-10-29

	void ResetData();
	void Copy(CDBVariousStyleInfoData *pData);
	BOOL GetAllDBInfo(CADOConn *pADOConn,BOOL bWithOrderInfo = FALSE);		//��ȡ����������Ϣ

	//����һ������
	BOOL InsertDBInfo(CADOConn *pADOConn);
	BOOL InsertDBInfoIfNotExists(CADOConn *pADOConn);
	//����һ����¼������
	BOOL UpdateDestribution(CADOConn *pADOConn);
	//����ǰ��ʽ��Ӧ�ĵ�ǰ������Ϊ��ѡ
	BOOL SetPreferred(CADOConn *pADOConn);
	//���ݿ�ʽ�� ������ɾ��һ����¼
	BOOL DelDBInfoByStyleAndOrder(CADOConn *pADOConn);
	
	//2017/11/20 zhangt ���ݿ�Ż�ȡ��ѡ����
	CString GetPreferredOrderNoByStyleNo(CADOConn *pADOConn);
	CString GetPreferredOrderNoByStyleNo(CADOConn *pADOConn,CString strStyleNo);
};

class CDBVariousStyleInfoList : public CDataListMid
{
public:
	CDBVariousStyleInfoList();
	~CDBVariousStyleInfoList();

	CDBVariousStyleInfoData*  GetItem(int nIndex);				//����������ȡItem
	CDBVariousStyleInfoData*  GetPerferredItem();				//��ȡ��ѡ��
	CDBVariousStyleInfoData*  GetItemByOrderNo(CString strOrderNo);
	BOOL SetPerferredItem(CADOConn *pADOConn,CString strOrderNo);
	void AddItem(CDBVariousStyleInfoData* pItem);				//
	void DeleteItem(int nIndex);
	void DeleteItemByOrderNo(CString strOrderNo);

	void GetListFromDB(CADOConn * pADOConn,CString strStyleNo);

protected:
	
private:
};