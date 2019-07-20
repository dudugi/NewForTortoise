#pragma once
#include "DataMid.h"
#include "DBKeyDef.h"
#include "DBDef.h"

/********************************************************
*filename: 	DBBindInfo.h
*author:		anjie
*description:������Ϣ�������
*file path:	D:\workspace\PDM\һ�������\CommonClass\ClassDB
*date:	2019/2/18 15:50
********************************************************/

class CADOConn;
class CDBP_BindInfoData :public CDataMid
{
   DECLARE_SERIAL(CDBP_BindInfoData)//���л������л�����Ҫ��ӵ�����
public:
   __int64                   m_nID;
   CString               m_strName;                 //����
   CString               m_oleBandStartTime;        //���ο�ʼʱ��
   CString               m_oleDesignEndTime;        //������ʱ��
   CString               m_olePatternEndTime;       //ֽ�����ʱ��
   CString               m_oleReviewEndTime;        //��������ʱ��
   CString               m_oleBandEndTime;          //���ν���ʱ��
   CString               m_strStylish;              //���
   CString               m_strColor;                //ɫϵ
   BOOL                  m_bCheckState;             //��˱�ʶ
   CString               m_strRemark;               //��ע
   __int64                m_nAssociatedProgrammingID;                 //������Ʒ�滮��ID
   CString               m_strSeriaNum;               //���
   CString               m_strDeliveryStartTime;    //������ʼʱ��
   CString               m_strDeliveryEndTime;      //���ڽ���ʱ��
   CString               m_strShelvesTime;          //�ϻ���
   CString               m_strCheckUserID;          //�����
   CString               m_strCheckTime;            //���ʱ��
   CString               m_strCreateUserID;         //������
   CString               m_strCreateUserTime;       //����ʱ��
public:
   CDBP_BindInfoData(void);
   ~CDBP_BindInfoData(void);
   void ResetData();
   void Copy(CDBP_BindInfoData *pData);
   BOOL GetAllDBInfo(CADOConn *pADOConn);				//��ȡ����������Ϣ
   BOOL GetAllDBInfoByID(CADOConn *pADOConn);
   BOOL InsertAllDBInfo(CADOConn *pADOConn);	//���롾�������¼�¼
   BOOL UpdateAllDBInfoByID(CADOConn *pADOConn);	//�����û��˻����¡���������¼
   BOOL UpdateCheckInfoByID(CADOConn *pADOConn);	
   BOOL DelAllDBInfoByID(CADOConn *pADOConn);		//�����û��˻�ɾ������������¼
};

class CDBP_BindInfoList :public CDataListMid
{
   DECLARE_SERIAL( CDBP_BindInfoList)//���л������л�����Ҫ��ӵ�����
public:
   CDBP_BindInfoList(void);
   ~CDBP_BindInfoList(void);
public:
   void Copy(CDBP_BindInfoList *pList);
   void AddItem(CDBP_BindInfoData *pItem);
   void DeleteItemByIndex(int nIndex);
   BOOL InsertAllDBtoDB(CADOConn *pADO,__int64 nProgrammingID);

#ifdef USING_GRIDCTRL_MARK
   void GetAllDBInfoByProgrammingID( CADOConn *pADO,CString  strProgrammingID,MAP_GridCtrl_AllData &mapALLData );
#endif
};
