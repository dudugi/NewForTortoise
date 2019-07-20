/*************************************************
// <�ļ�>: DBUserStylePermission_V.h
// <˵��>: �û���ʽȨ����ͼDB�� ���ڱ��Ա���Կ�ʽ��Ȩ��
// <����>: wangzl
// <����>: 2019/05/06
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
#pragma once
#include "DataMid.h"

class CDBUserStylePermission_VData : public CDataMid
{
   DECLARE_SERIAL( CDBUserStylePermission_VData)//���л������л�����Ҫ��ӵ�����
public:
   CDBUserStylePermission_VData(void);
   ~CDBUserStylePermission_VData(void);

   CString        m_strUserID;//�û�ID
   CString        m_strStyleNo;//���
   int            m_nPermission;//���õ�Ȩ��
   int            m_nFixPermission;//��ͬ��ݶ�Ӧ�Ĺ���Ȩ��
   int            m_nUserType;//�û����� 1�Ǵ����� 0�����õ�Ȩ��  2�ǹ���ִ���˵�Ȩ��
   CString        m_cPermissionTime; //Ȩ�޽���ʱ��,Ĭ��������Ϊһ��
public:
   void ResetData();
   void Copy(CDBUserStylePermission_VData *pData);
   BOOL GetAllDBInfo(CADOConn *pADOConn);				//��ȡ����������Ϣ
};

class CDBUserStylePermission_VList :public CDataListMid
{
   DECLARE_SERIAL( CDBUserStylePermission_VList)//���л������л�����Ҫ��ӵ�����
public:
   CDBUserStylePermission_VList(void);
   ~CDBUserStylePermission_VList(void);
public:
   void Copy(CDBUserStylePermission_VList *pList);
   CDBUserStylePermission_VData*  GetItem(int nIndex);
   CDBUserStylePermission_VData*  GetItemByUserID(const CString & strUserID);
   int  GetIndexByUserID(const CString & strUserID);
   void AddItem(CDBUserStylePermission_VData *pItem);
   void DeleteItemByIndex(int nIndex);
   void DeleteItemByUserID(CString strUserID);
   BOOL IsStyleHaveDeletePermission(CADOConn *pADOConn,CString strLoadUserID,std::vector<CString>vecKuanhao);//��Ӧ��ʽ�Ƿ���ɾ��Ȩ�� yangjr 2019/05/20
   BOOL GetDataByStyleNo(CADOConn *pADOConn,CString strStyleNo);//���ݿ�Ż�ȡȨ��list yangjr 2019/05/22
   BOOL SimpleHasPermision(CADOConn *pADOConn, const CString &strStyleNo, const CString &strLoadUserID); //�򵥵��ж�һ���Ƿ���Ȩ�ޣ�ֻҪ������PDM�Ҳ��б���㣩
};
