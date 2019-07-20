/*************************************************
// <�ļ�>: DBP_ProcessRecords.h
// <˵��>: �������̼�¼��
// <����>: wangzl
// <����>: 2019/02/22
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
#pragma once
#include "DataMid.h"
#include "DBKeyDef.h"

class CADOConn;
class CDBP_ProcessRecordsData  : public CDataMid
{
   DECLARE_SERIAL( CDBP_ProcessRecordsData)//���л������л�����Ҫ��ӵ�����
public:
   typedef enum {
      En_UnBegin = -1,
      En_Run = 0,
      En_Finish ,
   }En_Process_State;

public:
   __int64  m_nID                   ;
   __int64  m_nAssociatedProductID  ;//������ƷID
   CString  m_strReceiveUserID      ;//������
   CString  m_strSponsorID          ;//��������
   int      m_nProcessType          ;//��Ӧ�Ĺ���   �˴���ID ��ʾ ��Ҫ������� �� ���� 
   CString  m_strInitiateTime       ;//������ʱ��
   CString  m_strRealStartTime      ;//����ʵ�ʿ�ʼʱ��
   CString  m_strFinishTime         ;//�������ʱ��
   int      m_nState                ;//״̬        δ��ʼ ������ �����
   BOOL     m_bCheckState           ;//���
   
public:
   CDBP_ProcessRecordsData();
   ~CDBP_ProcessRecordsData();
   void ResetData();
   void Copy(CDBP_ProcessRecordsData *pData);
   BOOL GetAllDBInfo(CADOConn *pADOConn);
   BOOL DelAllDBInfoByID(CADOConn *pADOConn);
   BOOL UpdateAllDBInfoByID(CADOConn *pADOConn);
   BOOL InsertAllDBInfo(CADOConn *pADOConn);

   void Trim();

};

typedef struct workcontent
{
   CString strGXName;
   CString strPersonCode;
   CString strPersonName;
   CString	strNum_today;
   CString	strNum_month;
   CString strNum_Year;
   CString strNum_Complete;	//�������
   CString	strNum_UnComplete;	//δ�������
}wct;

//��������ͳ�� add by lida 2018/01/22
class CDBWorkStatistics
{
public:
   CDBWorkStatistics()
   {
      strOrderNo = _T("");		//������
      strGXName = _T("");			//��������
      strStaffID = _T("");		//����
      strStaffName = _T("");		//����
      strDirName = _T("");		//��׼��Ŀ¼
      iPian = 0; 					//Ƭ
      iFlag = 0;				
   };
   ~CDBWorkStatistics(){};

   CString		strOrderNo;		//������
   CString		strGXName;		//��������
   CString		strStaffID;		//����
   CString		strStaffName;	//����
   CString		strDirName;		//��׼��Ŀ¼
   int			iPian;			//Ƭ
   int			iFlag;			//��ʶ
};

typedef enum
{
   enum_SearchTime_ZhuanRu=0,
   enum_SearchTime_FaChu,
   enum_SearchTime_NoShouHui,
   enum_SearchTime_ShouHui,
   enum_SearchTime_QuanBu,
}ENUM_TIME_SHEARCHTYPE;

class CDBP_ProcessRecordsList : public CDataListMid
{
   DECLARE_SERIAL(CDBP_ProcessRecordsList)
public:
   CDBP_ProcessRecordsList();
   ~CDBP_ProcessRecordsList();
   CDBP_ProcessRecordsData*  GetItem(int nIndex);
   void    AddItem(CDBP_ProcessRecordsData* pItem);
   void    DeleteItem(int nIndex);

   static CDBP_ProcessRecordsList * Instance();//��ȡ��ָ�룩ʵ��

private:
   static std::shared_ptr<CDBP_ProcessRecordsList> sm_inst;
};