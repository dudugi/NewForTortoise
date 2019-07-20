/*************************************************
// <�ļ�>: DBP_ProductRevisionRecords.h
// <˵��>: ��Ʒ�汾��Ϣ��
// <����>: wangzl
// <����>: 2019/02/22
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
#pragma once
#include "DataMid.h"
#include "DBKeyDef.h"

class CADOConn;
class CDBP_ProductRevisionRecordsData  : public CDataMid
{
   DECLARE_SERIAL( CDBP_ProductRevisionRecordsData)//���л������л�����Ҫ��ӵ�����

public:
   typedef enum{
      En_Refuse = 0,//�˻�
      En_Pass,//ͨ��
   }En_CheckResult;
public:
   __int64 m_nID                    ;
   __int64 m_nAssociatedProductID   ;//������ƷID
   CString m_strVersion             ;//��汾
   int     m_nVersionNo             ;//С�汾��
   CString m_strCode                ;//��Ӧ�ĵ���
   CString m_strAlias               ;//����
   CString m_strSponsor             ;//������
   CString m_strRecordTime          ;//����ʱ��
   CString m_strRevisionType        ;//�İ�����
   CString m_strRevisionReason      ;//�İ�ԭ��
   CString m_strLastRecordProcess   ;//��������¼�Ĺ���
   BOOL    m_bCheckState            ;//���״̬
   int     m_nCheckResult           ;//��˽��
   CString m_strCheckUserID         ;//�����
   CString m_strCheckTime           ;//���ԭ��
   CString m_strCheckOpinion        ;//�����ע

public:
   CDBP_ProductRevisionRecordsData();
   ~CDBP_ProductRevisionRecordsData();
   void ResetData();
   void Copy(CDBP_ProductRevisionRecordsData *pData);
   BOOL GetAllDBInfo(CADOConn *pADOConn);
   BOOL DelAllDBInfoByID(CADOConn *pADOConn);
   BOOL UpdateAllDBInfoByID(CADOConn *pADOConn);
   BOOL InsertAllDBInfo(CADOConn *pADOConn);

   void Trim();

};

class CDBP_ProductRevisionRecordsList : public CDataListMid
{
   DECLARE_SERIAL(CDBP_ProductRevisionRecordsList)
public:
   CDBP_ProductRevisionRecordsList();
   ~CDBP_ProductRevisionRecordsList();
   CDBP_ProductRevisionRecordsData*  GetItem(int nIndex);
   void    AddItem(CDBP_ProductRevisionRecordsData* pItem);
   void    DeleteItem(int nIndex);

   static CDBP_ProductRevisionRecordsList * Instance();//��ȡ��ָ�룩ʵ��

private:
   static std::shared_ptr<CDBP_ProductRevisionRecordsList> sm_inst;
};