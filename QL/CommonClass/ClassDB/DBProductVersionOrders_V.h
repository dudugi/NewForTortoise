/*************************************************
// <�ļ�>: DBProductVersionOrders_V.h
// <˵��>: �����浥��ѯ��ͼ
// <����>: wangzl
// <����>: 2019/02/22
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
#pragma once
#include "DataMid.h"
#include "DBP_ProductStructurePlanning.h"

class CADOConn;
class CDBProductVersionOrders_VData  : public CDataMid
{
   DECLARE_SERIAL( CDBProductVersionOrders_VData)//���л������л�����Ҫ��ӵ�����
public:
   CDBP_ProductStructurePlanningData m_ProductSPData     ;//��Ʒ��Ϣ

   __int64 m_nVersionID          ;//�汾ID
   CString m_strVersion          ;//�汾
   __int64 m_nRdRecordsID        ;//������ID
   CString m_strCate             ;//����
   CString m_strCode             ;//����
   CString m_strDate             ;//�µ�����
   CString m_strMaker            ;//�Ƶ���
   CString m_strInvSehao         ;//��ɫ
   CString m_strInvPeise         ;//��ɫ
   CString m_strInvKuanhao       ;//���
   CString m_strInvUnitCost      ;//����
   CString m_strLastPerson       ;//��������
   CString m_strLastTime         ;//������ʱ��
   CString m_strInvState2        ;//״̬2
   CString m_strTrueTime         ;//��ʵ¼��ʱ��
   int     m_nOrdCreateFlag      ;//����������ʶ
   CString m_strJianshu          ;//����
   CString m_strInvMemo          ;//��ע
   CString m_strInvState         ;//״̬
   CString m_strZuoFeiMemo       ;//����˵��


public:
   CDBProductVersionOrders_VData();
   ~CDBProductVersionOrders_VData();
   void ResetData();
   void Copy(CDBProductVersionOrders_VData *pData);
   BOOL GetAllDBInfo(CADOConn *pADOConn);

#ifdef USING_GRIDCTRL_MARK

   MAP_GridCtrl_RowData CreateGridRowData(CADOConn * pADOConn);//2017/08/30
#endif // USING_GRIDCTRL_MARK

   void Trim();

};

class CDBProductVersionOrders_VList : public CDataListMid
{
   DECLARE_SERIAL(CDBProductVersionOrders_VList)
public:
   CDBProductVersionOrders_VList();
   ~CDBProductVersionOrders_VList();
   CDBProductVersionOrders_VData*  GetItem(int nIndex);
   void    AddItem(CDBProductVersionOrders_VData* pItem);
   void    DeleteItem(int nIndex);

#ifdef USING_GRIDCTRL_MARK
   MAP_GridCtrl_AllData    GetAllDBInfotoList(CADOConn *pADOConn,MAP_GridCtrl_AllData mapAllData);//��ȡ����������Ϣ
#endif // USING_GRIDCTRL_MARK

   static CDBProductVersionOrders_VList * Instance();//��ȡ��ָ�룩ʵ��

private:
   static std::shared_ptr<CDBProductVersionOrders_VList> sm_inst;
};