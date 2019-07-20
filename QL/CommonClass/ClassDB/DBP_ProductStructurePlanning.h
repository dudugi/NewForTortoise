/*************************************************
// <�ļ�>: DBP_ProductStructurePlanning.h
// <˵��>: ��Ʒ�������в��κ�����ľ��󲿷�����
// <����>: wangzl
// <����>: 2019/02/22
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
#pragma once
#include "DataMid.h"
#include "DBKeyDef.h"
#include "DBP_Programming.h"
#include "DBBindInfo.h"
#include "DBP_Planning.h"
class CADOConn;

class CDBP_ProductStructurePlanningData  : public CDataMid
{
   DECLARE_SERIAL( CDBP_ProductStructurePlanningData)//���л������л�����Ҫ��ӵ�����
public:

   __int64  m_nID                         ;
   CString  m_strClassification           ;//����
   CString  m_strCategory                 ;//Ʒ��
   CString  m_strPieceNum                 ;//����
   CString  m_strColor                    ;//ɫ��
   CString  m_strSize                     ;//����
   CString  m_strFabric                   ;//����
   CString  m_strFashion                  ;//���ͷ��
   CString  m_strContour                  ;//����
   double   m_fPrice_Ceiling              ;//�۸�����
   double   m_fPrice_Floor                ;//�۸�����
   double   m_fPrice_Tag                  ;//���Ƽ�
   CString  m_strRemark                   ;//��ע
   CString  m_strBand_Name                ;//����
   CString  m_strBand_BandStartTime       ;//���ο�ʼʱ��
   CString  m_strBand_DesignEndTime       ;//������ʱ��
   CString  m_strBand_PatternEndTime      ;//ֽ�����ʱ��
   CString  m_strBand_ReviewEndTime       ;//��������ʱ��
   CString  m_strBand_BandEndTime         ;//���ν���ʱ��
   CString  m_strBand_DeliveryStartTime   ;//������ʼʱ��
   CString  m_strBand_DeliveryEndTime     ;//���ڽ���ʱ��
   CString  m_strBand_ShelvesTime         ;//�ϻ���
   CString  m_strBand_Stylish             ;//���
   CString  m_strBand_Color               ;//ɫϵ
   CString  m_strCreateUserID             ;//������
   CString  m_strCreateTime               ;//����ʱ��
   int      m_nCreateFlag                 ;//������ʶ
   CString  m_strProgramming_Brand        ;//Ʒ��
   CString  m_strProgramming_Years        ;//���
   CString  m_strProgramming_Season       ;//����
   CString  m_strProgramming_TradeFairTime;//������ʱ��
   CString  m_strProgramming_Area         ;//����
   CString  m_strPlanning_SubjectName     ;//������
   BOOL     m_bSubmitState                ;//�ύ״̬
   CString  m_strSubmitUserID             ;//�ύ��
   CString  m_strSubmitTime               ;//�ύʱ��
   CString  m_strCheckUserID              ;//�����
   CString  m_strCheckTime                ;//���ʱ��
   BOOL     m_bCheckState                 ;//���״̬
   int      m_nCurProSort                 ;//��ǰ��������
   BOOL     m_bRevision                   ;//�İ��ʶ
   CString  m_strRevisionReason           ;//�İ�ԭ��

public:
   CDBP_ProductStructurePlanningData();
   ~CDBP_ProductStructurePlanningData();
   void ResetData();
   void Copy(CDBP_ProductStructurePlanningData *pData);
   BOOL GetAllDBInfo(CADOConn *pADOConn);
   BOOL DelAllDBInfoByID(CADOConn *pADOConn);
   BOOL UpdateAllDBInfoByID(CADOConn *pADOConn);
   BOOL InsertAllDBInfo(CADOConn *pADOConn);
   BOOL CopyToDBProgrammingAndBindPlanningID(CDBP_ProgrammingData *pProgrammingData,__int64 nID); // ������Ʒ����Ϣ���󻮱�,������ID
   BOOL CopyToDBBandAndBindProgrammingID(CDBP_BindInfoData *pDBBandInfo,__int64 nID); // ����������Ϣ�����α�����ID
   BOOL CopyToDBPlanning(CDBP_PlanningData *pDBPlanningInfo); // ����������Ϣ�������
   void Trim();

};

class CDBP_ProductStructurePlanningList : public CDataListMid
{
   DECLARE_SERIAL(CDBP_ProductStructurePlanningList)
public:
   CDBP_ProductStructurePlanningList();
   ~CDBP_ProductStructurePlanningList();
   CDBP_ProductStructurePlanningData*  GetItem(int nIndex);
   CDBP_ProductStructurePlanningData*  GetItemByID(__int64 nID);
   void    AddItem(CDBP_ProductStructurePlanningData* pItem);
   void    DeleteItem(int nIndex);

   static CDBP_ProductStructurePlanningList * Instance();//��ȡ��ָ�룩ʵ��

private:
   static std::shared_ptr<CDBP_ProductStructurePlanningList> sm_inst;
};