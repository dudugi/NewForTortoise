#pragma once
#include "DataMid.h"
#include <tuple>
/*************************************************
// <�ļ�>: DBProductOrderInfo.h
// <˵��>: ���۵�����
// <����>: lida
// <����>: 2019/07/19 15:16:08
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 

class CADOConn;
class CDBSalesOrderInfo :public CDataMid
{
   DECLARE_SERIAL( CDBSalesOrderInfo)//���л������л�����Ҫ��ӵ�����
public:
   CDBSalesOrderInfo(void);
   ~CDBSalesOrderInfo(void);

public:
   int         m_id;                // ����ID
   CString     m_strStyleNo;         //���
   CString     m_strSalesOrder;     //��������
   CString     m_strMainClrNo;
   CString     m_strMainClrCate;
   CString     m_strMainClrName;
   CString     m_strSizeNumInfo;       //����������Ϣ��s(1);m(2);l(3);....       
   CString     m_strDate;           //����ʱ��
   int         m_iTotalNum;         //�ܼ��������Ե���ParaseSizeInfo�Զ����㣬�����Լ��㣬һ��Ҫ��ֵ����Ȼͳ��������

   map<CString,CString> m_mapSizeInfo; //��m_strSizeInfo��������

   enum DataType
   {
      en_null = -1,
      en_add = 0,  
      en_del = 1,
      en_updadte =2,
   };
public:
   void ResetData();
   void Copy(CDBSalesOrderInfo *pData);
   void GetAllDBInfo(CADOConn* pADOConn);

   BOOL InsetAllDBInfo(CADOConn* pADOConn);
   BOOL UpdateAllDBInfo(CADOConn* pADOConn); //����ID
   BOOL DeleteAllDBInfo(CADOConn* pADOConn); //����ID

   CString GetInsertSql();
   CString GetUpdateSql();
   CString GetDeleteSql();
   CString GetDeleteSqlByStyleNo(CString strStyleNo);
   static void ParaseSizeInfo(const CString strSizeInfo,map<CString,CString>& mapSizeInfo);  //str -> map
   static void ParaseSizeInfo(const map<CString,CString> mapSizeInfo,CString& strSizeInfo,int& iTotalNum);  //map -> str
   static void CreateRowData(CDBSalesOrderInfo* pData,MAP_GridCtrl_RowData& row_data);
};


class CDBSalesOrderInfoList :public CDataListMid
{
   DECLARE_SERIAL( CDBSalesOrderInfoList)//���л������л�����Ҫ��ӵ�����
public:
   CDBSalesOrderInfoList(void);
   ~CDBSalesOrderInfoList(void);

   static CDBSalesOrderInfoList * Instance();//��ȡ��ָ�룩ʵ��

   CDBSalesOrderInfo* GetItem(int nIndex);			//����������ȡItem 
   void AddItem(CDBSalesOrderInfo* pItem);			//���Item
   void DeleteItem(int nIndex);					//ɾ���̶�����Item

   //��ȡһ��������¼����
   void GetProductOrderRecords(CADOConn* pAdo,CString strID,__out map<CString,tuple<CString,CString>>& mapColorInfo,__out map<CString,map<CString,CString>>& mapSizeInfo);


public:
#ifdef USING_GRIDCTRL_MARK
   void GetGridDataInfo(CADOConn* pAdo,CString strStyleNo,MAP_GridCtrl_AllData& all_data);
#endif

private:
   static std::shared_ptr<CDBSalesOrderInfoList> sm_inst;
};