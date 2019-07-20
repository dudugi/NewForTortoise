/*************************************************
// <�ļ�>: DBP_Programming.h
// <˵��>: ��Ʒ�滮��
// <����>: wangzl
// <����>: 2019/02/22
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
#pragma once
#include "DataMid.h"
#include "DBKeyDef.h"


class CADOConn;

class CDBP_ProgrammingData  : public CDataMid
{
   DECLARE_SERIAL( CDBP_ProgrammingData)//���л������л�����Ҫ��ӵ�����
public:
   __int64  m_nID                    ;//
   CString  m_strBrand              ;//Ʒ��
   int      m_nYears                ;//���
   CString  m_strSeason             ;//����
   CString  m_strTradeFairTime      ;//������
   CString  m_strArea               ;//����
   __int64  m_nAssociatedPlanningID ;//����������ID
   CString  m_strCreateUserID       ;//������

public:
   CDBP_ProgrammingData();
   ~CDBP_ProgrammingData();
   void ResetData();
   void Copy(CDBP_ProgrammingData *pData);
   BOOL GetAllDBInfo(CADOConn *pADOConn);
   BOOL GetAllDBInfoByID(CADOConn *pADOConn);
   BOOL GetIDByCondition(CADOConn *pADOConn);
   BOOL DelAllDBInfoByID(CADOConn *pADOConn);
   BOOL UpdateAllDBInfoByID(CADOConn *pADOConn);
   BOOL InsertAllDBInfo(CADOConn *pADOConn);

   void Trim();

};

class CDBP_ProgrammingList : public CDataListMid
{
   DECLARE_SERIAL(CDBP_ProgrammingList)
public:
   CDBP_ProgrammingList();
   ~CDBP_ProgrammingList();
   CDBP_ProgrammingData*  GetItem(int nIndex);
   void    AddItem(CDBP_ProgrammingData* pItem);
   void    DeleteItem(int nIndex);

   static CDBP_ProgrammingList * Instance();//��ȡ��ָ�룩ʵ��

private:
   static std::shared_ptr<CDBP_ProgrammingList> sm_inst;
};