/*************************************************
// <�ļ�>: DBP_TextBoard.h
// <˵��>: ���ְ�
// <����>: wangzl
// <����>: 2019/02/22
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
#pragma once
#include "DataMid.h"
#include "DBKeyDef.h"
#include "DBProofingAssociatedInfo.h"

class CADOConn;

class CDBP_TextBoardData  : public CDBProofingAssociatedData
{
   DECLARE_SERIAL( CDBP_TextBoardData)//���л������л�����Ҫ��ӵ�����
public:
   CString     m_strTextInfo     ;//���ְ�

public:
   CDBP_TextBoardData();
   ~CDBP_TextBoardData();
   void ResetData();
   void Copy(CDBP_TextBoardData *pData);
   BOOL GetAllDBInfo(CADOConn *pADOConn);          //��ȡ������Ϣ
   BOOL GetAllDBInfoBynAssociatedID(CADOConn *pADOConn,__int64 nAssociatedID);
   BOOL DelAllDBInfoByID(CADOConn *pADOConn);      //����IDɾ��������¼
   BOOL UpdateAllDBInfoByID(CADOConn *pADOConn);   //����ID �������ְ���Ϣ  û��ID���͵ĸ���
   BOOL InsertAllDBInfo(CADOConn *pADOConn);   //����������Ϣ

   void Trim();

};

class CDBP_TextBoardList : public CDataListMid
{
   DECLARE_SERIAL(CDBP_TextBoardList)
public:
   CDBP_TextBoardList();
   ~CDBP_TextBoardList();
   CDBP_TextBoardData*  GetItem(int nIndex);
   void    AddItem(CDBP_TextBoardData* pItem);
   void    DeleteItem(int nIndex);

   static CDBP_TextBoardList * Instance();//��ȡ��ָ�룩ʵ��

private:
   static std::shared_ptr<CDBP_TextBoardList> sm_inst;
};