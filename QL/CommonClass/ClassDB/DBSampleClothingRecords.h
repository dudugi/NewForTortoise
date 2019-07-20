/*************************************************
// <�ļ�>: DBSamepleClothingRecords.h
// <˵��>: �����շ���¼��
// <����>: lida
// <����>: 2019/07/01 15:52:15
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
#pragma once
#include "DataMid.h"

class CDBSampleClothingRecords  : public CDataMid
{
   DECLARE_SERIAL(CDBSampleClothingRecords)//���л������л�����Ҫ��ӵ�����
public:
      int         m_ID;
      CString     m_strcBarCode;
      CString     m_strcKuanhao;
      int         m_LendReturnState;
      CString     m_strLendReturnPerson;
      CString     m_strLendReturnTime;
      CString     m_strConfirmMan;
      CString     m_strLocation;
      CString     m_strReason;
      CString     m_strMemo;
public:
   CDBSampleClothingRecords();
   ~CDBSampleClothingRecords();
   void ResetData();
   void Copy(CDBSampleClothingRecords *pData);
   BOOL GetAllDBInfo(CADOConn *pADOConn);
   
   BOOL InsertData(CADOConn *pADOConn);
   BOOL UpdateData(CADOConn *pADOConn);
   BOOL DeleteData(CADOConn *pADOConn);

   CString GetInsertSql();
   CString GetUpdateSql();
   CString GetDeleteSql();
};

class CDBSampleClothingRecordsList : public CDataListMid
{
   DECLARE_SERIAL(CDBSampleClothingRecordsList)
public:
   CDBSampleClothingRecordsList();
   ~CDBSampleClothingRecordsList();
   void Copy(CDBSampleClothingRecordsList *pList);
   CDBSampleClothingRecords*  GetItem(int nIndex);
   void    AddItem(CDBSampleClothingRecords* pItem);
   BOOL DeleteItem(int nIndex);

   static CDBSampleClothingRecordsList * Instance();//��ȡ��ָ�룩ʵ��

private:
   static std::shared_ptr<CDBSampleClothingRecordsList> sm_inst;
public:

#ifdef USING_GRIDCTRL_MARK
   static void CreateRowData(CDBSampleClothingRecords*pData,__out MAP_GridCtrl_RowData& row_data);
   static BOOL GetRecordsGridData(CADOConn *pADOConn,CString strBarCode,__out MAP_GridCtrl_AllData& all_data);
   static BOOL GetRecordsGridDataByStyleNo(CADOConn *pADOConn,CString strStyleNo,__out MAP_GridCtrl_AllData& all_data);   //��ȡ��ʽ���������¼�¼
#endif

};