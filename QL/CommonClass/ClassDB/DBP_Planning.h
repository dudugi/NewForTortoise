/*************************************************
// <�ļ�>: DBP_Planning.h
// <˵��>: ����-������
// <����>: wangzl
// <����>: 2019/02/22
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
#pragma once
#include "DataMid.h"
#include "DBKeyDef.h"
#include "DBDef.h"
#include "stdafx.h"


class CDBP_PlanningData :public CDataMid
{
   DECLARE_SERIAL( CDBP_PlanningData)//���л������л�����Ҫ��ӵ�����
public:
   CDBP_PlanningData(void);
   ~CDBP_PlanningData(void);
public:
     __int64           m_nID                       ;         //ID
      int              m_nYears                    ;         //���
      CString          m_strSeason                 ;         //����
      CString          m_strSubjectName            ;         //������
      CString          m_strBrand                  ;         //Ʒ��
      CString          m_strRemark                 ;         //���ⱸע
      BOOL             m_bCheckState               ;         //��˱�ʶ
      CString          m_strCreateUserID           ;         //������
      CString          m_strCreateTime             ;         //����ʱ��
      CString          m_strLastAcTime             ;         //������ʱ��
      CString          m_strCheckUserID            ;         //�����
      CString          m_strCheckTime              ;         //���ʱ��
   void ResetData();
   void Copy(CDBP_PlanningData *pData);
   BOOL GetAllDBInfo(CADOConn *pADOConn);				//��ȡ����������Ϣ
   BOOL GetAllDBInfoByID(CADOConn *pADOConn);				//��ȡ����������Ϣ
   BOOL GetIDByCondition(CADOConn *pADOConn);				//��ȡ����������Ϣ

   BOOL InsertAllDBInfo(CADOConn *pADOConn);	//���롾�������¼�¼
   BOOL UpdateAllDBInfoByID(CADOConn *pADOConn);	//�����û��˻����¡���������¼
   BOOL DelAllDBInfoByID(CADOConn *pADOConn);		//�����û��˻�ɾ������������¼
};

class CDBP_PlanningList :public CDataListMid
{
   DECLARE_SERIAL( CDBP_PlanningList)//���л������л�����Ҫ��ӵ�����
public:
   CDBP_PlanningList(void);
   ~CDBP_PlanningList(void);
public:
   void Copy(CDBP_PlanningList *pList);
   void AddItem(CDBP_PlanningData *pItem);
   void DeleteItemByIndex(int nIndex);
   #ifdef USING_GRIDCTRL_MARK
   void GetAllDBInfoByCondition(CADOConn *pADO,CString strSQL,MAP_GridCtrl_AllData &mapALLData);    //ͨ��������ȡ����,����Grid�������
   #endif
};
