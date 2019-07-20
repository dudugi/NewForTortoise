#pragma once
#include "DataMid.h"
#include <map>
#include <vector>
#include <set>
#include "DBKeyDef_V.h"
#include "DBDef.h"

/*************************************************
// <�ļ�>: DBBandProgramming_V.h
// <˵��>: ������Ʒ��Ϣ��ͼ��Ӧ��Ϣ�༴����
// <����>: wangzl
// <����>: 2019/02/22
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 

using namespace std;
class CADOConn;
class CDBViewBandProgrammingInfoData : public CDataMid
{
    DECLARE_SERIAL(CDBViewBandProgrammingInfoData)//���л������л�����Ҫ��ӵ�����
public:
   CDBViewBandProgrammingInfoData(void);
   ~CDBViewBandProgrammingInfoData(void);
public:
   __int64               m_nID                   ;
   CString               m_strName                   ;//����
   CString               m_oleBandStartTime          ;//���ο�ʼʱ��
   CString               m_oleDesignEndTime          ;//������ʱ��
   CString               m_olePatternEndTime         ;//ֽ�����ʱ��
   CString               m_oleReviewEndTime          ;//��������ʱ��
   CString               m_oleBandEndTime            ;//���ν���ʱ��
   CString               m_strStylish                ;//���
   CString               m_strColor                  ;//ɫϵ
   BOOL                  m_bCheckState               ;//��˱�ʶ
   CString               m_strRemark                 ;//��ע
   __int64               m_nAssociatedProgrammingID  ;//������Ʒ�滮��ID
   CString               m_strSeriaNum               ;//���
   CString               m_strDeliveryStartTime      ;//������ʼʱ��
   CString               m_strDeliveryEndTime        ;//���ڽ���ʱ��
   CString               m_strShelvesTime            ;//�ϻ���
   CString               m_strCheckUserID            ;//�����
   CString               m_strCheckTime              ;//���ʱ��
   CString               m_strCreateUserID;         //������
   CString               m_strCreateUserTime;       //����ʱ��
   __int64               m_nProgrammingID            ;// 
   CString               m_strBrand                  ;//Ʒ��
   int                   m_nYears                    ;//���
   CString               m_strSeason                 ;//����
   CString               m_strTradeFairTime          ;//������
   CString               m_strArea                   ;//����
   __int64               m_nAssociatedPlanningID     ;//����������ID
   CString               m_strProgrammingCreateUserID;//������
public:
   virtual void ResetData();
   virtual void Copy(CDBViewBandProgrammingInfoData * pData);
   BOOL GetAllDBInfo(CADOConn *pADOConn);				//��ȡ����������Ϣ
};

class CDBViewBandProgrammingInfoList : public CDataListMid
{
    DECLARE_SERIAL( CDBViewBandProgrammingInfoList)//���л������л�����Ҫ��ӵ�����
public:
	CDBViewBandProgrammingInfoList();
   ~CDBViewBandProgrammingInfoList();

   void Copy(CDBViewBandProgrammingInfoList *pList);
   void AddItem(CDBViewBandProgrammingInfoData *pItem);
   void DeleteItemByIndex(int nIndex);
#ifdef USING_GRIDCTRL_MARK
   void GetAllDBInfoByCondition(CADOConn *pADO,CString strSQL,MAP_GridCtrl_AllData &mapALLData);    //ͨ��������ȡ����,����Grid�������
#endif
	static CDBViewBandProgrammingInfoList * Instance();
private:
	static std::shared_ptr<CDBViewBandProgrammingInfoList> sm_inst;
};
