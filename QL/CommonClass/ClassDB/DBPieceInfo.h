/*************************************************
// <�ļ�>: DBPieceInfo.h
// <˵��>: ��¼���Ŷ�Ӧ����Ƭ�����Լ���Ƭ���Ƶ���Ϣ
// <����>: wangzl
// <����>: 2019/02/22
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
#pragma once
#include "DataMid.h"


class CDBPieceInfoData : public CDataMid
{
public:
   int         m_nID                ;//����ID
   CString     m_strcCode           ;//������
   int         m_nPieceType         ;//��Ƭ����
   CString     m_strcPieceName      ;//��Ƭ����
   CString     m_strcRemark         ;//��ע Ԥ��

   enum {
      En_PieceComputer = 0 ,//����
      En_PeiceHand         ,//��ҡ
   };
public:
   CDBPieceInfoData(void);
   ~CDBPieceInfoData(void);

   void ResetData();
   void Copy(CDBPieceInfoData *pData);
   BOOL GetAllDBInfo(CADOConn *pADOConn);			//��ȡһ����¼��Ϣ
   BOOL InsertAllDBInfo(CADOConn *pADOConn);
};


class CDBPieceInfoList  : public CDataListMid
{
public:
   CDBPieceInfoList();
   ~CDBPieceInfoList();
   CDBPieceInfoData* GetItem(int nIndex);//����������ȡItem
   CDBPieceInfoData* GetItemByPieceName(const CString & strPieceName);//����������ȡItem
   void AddItem(CDBPieceInfoData* pItem);//���Item
   void DeleteItem(int nIndex);		//ɾ���̶�����Item
   //���ݶ����Ż�ȡһ�����������б�ע
   BOOL GetListFromDB(CADOConn *pADOConn,const CString & strcCode);
   BOOL InsetAllDBInfo(CADOConn * pADOConn);
};

