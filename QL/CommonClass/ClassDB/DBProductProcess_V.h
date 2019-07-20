/*************************************************
// <�ļ�>: DBProductProcess_V.h
// <˵��>: ����������ͼ ����ͼ��¼��ÿһ����Ʒ�����һ�������¼��ʲô �Լ���Ӧ����Ϣ
// <����>: wangzl
// <����>: 2019/02/22
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
#pragma once
#include "DataMid.h"
#include "DBP_ProductStructurePlanning.h"
#include "DBP_ProcessRecords.h"


class CADOConn;
class CDBProductProcess_VData  : public CDataMid
{
   DECLARE_SERIAL( CDBProductProcess_VData)//���л������л�����Ҫ��ӵ�����
public:
   CDBP_ProductStructurePlanningData m_ProductSPData     ;//��Ʒ��Ϣ
   CDBP_ProcessRecordsData           m_ProcessRecordsData;//�����¼��Ϣ

   CString                           m_strAssignUserID   ;//�Ĳ�Ʒ��һ��Ӧ��ִ�й���Ķ�Ӧ��Ա
   int                               m_nPersonType       ;//�ò�Ʒ��һ��Ӧ��ִ�й����Ӧ����Ա����

public:
   CDBProductProcess_VData();
   ~CDBProductProcess_VData();
   void ResetData();
   void Copy(CDBProductProcess_VData *pData);
   BOOL GetAllDBInfo(CADOConn *pADOConn);

   void Trim();


#ifdef USING_GRIDCTRL_MARK
   //������
   MAP_GridCtrl_RowData CreateGridRowData(CADOConn * pADOConn);//2017/08/31
#endif // USING_GRIDCTRL_MARK

};

class CDBProductProcess_VList : public CDataListMid
{
   DECLARE_SERIAL(CDBProductProcess_VList)
public:
   CDBProductProcess_VList();
   ~CDBProductProcess_VList();
   CDBProductProcess_VData*  GetItem(int nIndex);
   void    AddItem(CDBProductProcess_VData* pItem);
   void    DeleteItem(int nIndex);

   static CDBProductProcess_VList * Instance();//��ȡ��ָ�룩ʵ��

private:
   static std::shared_ptr<CDBProductProcess_VList> sm_inst;
};