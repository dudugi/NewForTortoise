/********************************************************************
***	<�ļ�>: DBStyleCostData.h
***	<˵��>:	��ʽ�ɱ����ݲ�����
***	<����>:	anjie
***	<����>:	2019/5/23
*** Copyright (C), 2016-2020, �������. Co., Ltd.
*********************************************************************/
#pragma once
#include "DataMid.h"
class CADOConn;

class CDBStyleCostData  : public CDataMid
{
   DECLARE_SERIAL(CDBStyleCostData)//���л������л�����Ҫ��ӵ�����
public:
   int               m_ID                        ;//ID 
   CString           m_strStyleNo                ;//���      
   CString           m_strCostItem               ;//�ɱ���
   CString           m_strCostType               ;//�ɱ����
   CString           m_strCostJinE               ;//�ɱ����  ������ wangzl 2019-6-11  �ɱ�Ϊ��������  ��ͼ���ݽ��в�ѯ
   double            m_fCostPrice                ;//�ɱ�����
   double            m_fCostAddedValue           ;//�ɱ�����ֵ
   double            m_fSalesPrice               ;//���۵���
   double            m_fSalesAddedValue          ;//���۸���ֵ
   double            m_fCalculatedValue          ;//������ֵ
public:
   CDBStyleCostData();
   ~CDBStyleCostData();

   void Serialize(CArchive& ar);
   void ResetData();
   void Copy(CDBStyleCostData *pData);
   BOOL GetAllDBInfo(CADOConn *pADOConn);
   static CString GetDeleteByStyleNoSql(const CString & strStyleNo);
};

class CDBStyleCostList : public CDataListMid
{
   DECLARE_SERIAL(CDBStyleCostList)
public:
   CDBStyleCostList();
   ~CDBStyleCostList();
   void Serialize(CArchive& ar);
   void Copy(CDBStyleCostList *pList);
   CDBStyleCostData*  GetItem(int nIndex);
   CDBStyleCostData*  GetItemByCostItem(CString strCostItem);
   void    AddItem(CDBStyleCostData* pItem);
   BOOL DeleteItem(int nIndex);
   BOOL DeleteItemByCostItem(CString strCostItem);
   BOOL    BatchInsertDataToDB(CADOConn *pADOConn);//�����������ݵ����ݿ�(�������ݻ���ɾ�������)
   void   GetDBDataByStyleNo(CADOConn *pADOConn,CString strStyleNo);
   static CDBStyleCostList * Instance();//��ȡ��ָ�룩ʵ��
#ifdef USING_GRIDCTRL_MARK
   void   CreateGridData(MAP_GridCtrl_AllData & map_allData);
#endif
private:
   static std::shared_ptr<CDBStyleCostList> sm_inst;
};