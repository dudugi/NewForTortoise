/*************************************************
// <�ļ�>: DBSamepleClothingInfo.h
// <˵��>: ���¹����
// <����>: lida
// <����>: 2019/07/01 15:52:00
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
#pragma once
#include "DataMid.h"
#include <set>

class CDBSampleClothingInfo  : public CDataMid
{
   DECLARE_SERIAL(CDBSampleClothingInfo)//���л������л�����Ҫ��ӵ�����
public:
   int         m_ID;
   CString     m_strKuanhao;
   CString     m_strMainColor;      //��ɫ
   CString     m_strSize;           //����
   CString     m_strBarCode;        //����
   CString     m_strCreator;        //������
   CString     m_strMakeTime;       //����ʱ��
   CString     m_strKeeper;         //������
   CString     m_strKeepLocation;   //���ܵص�
   CString     m_strMemo;           //���±�ע
   int         m_LendReturnState;   //��ǰ����״̬ 0�����1�黹,Ĭ�Ϲ黹״̬
   CString     m_strCate;           //����

public:
   CDBSampleClothingInfo();
   ~CDBSampleClothingInfo();
   void ResetData();
   void Copy(CDBSampleClothingInfo *pData);
   BOOL GetAllDBInfo(CADOConn *pADOConn);
   
   BOOL Insert(CADOConn *pADOConn);
   BOOL Update(CADOConn *pADOConn);
   BOOL Del(CADOConn *pADOConn);

   CString GetInsertSql();
   CString GetUpdateSql();
   CString GetDelSql();
};

class CDBSampleClothingInfoList : public CDataListMid
{
   DECLARE_SERIAL(CDBSampleClothingInfoList)
public:
   CDBSampleClothingInfoList();
   ~CDBSampleClothingInfoList();
   void Copy(CDBSampleClothingInfoList *pList);
   CDBSampleClothingInfo*  GetItem(int nIndex);
   void    AddItem(CDBSampleClothingInfo* pItem);
   BOOL DeleteItem(int nIndex);

   static CDBSampleClothingInfoList * Instance();	//��ȡ��ָ�룩ʵ��
private:
   static std::shared_ptr<CDBSampleClothingInfoList> sm_inst;

public:
   static BOOL GetSampleClothingDataByBarCode(__in CADOConn* pAdo,__in CString strBarCode,__out CDBSampleClothingInfo* pData);

#ifdef USING_GRIDCTRL_MARK
   BOOL GetSampleClothingListGridData(__in CADOConn* pAdo,__in CString strStyleNo,__out MAP_GridCtrl_AllData& all_data,__out set<CString>& setBarCode);
#endif
};