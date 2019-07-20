/*************************************************
// <�ļ�>: DBStyle_DesDenisity.h
// <˵��>: ��ʽ�ܶ�����
// <����>: wangzl
// <����>: 2019/06/19
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
#pragma once
#include "DataMid.h"
#include "DBStyle_DesFaceCode.h"
class CADOConn;

class CDBStyle_DensityFaceCodeData : public CDataMid
{
public:
   CDBStyle_DensityFaceCodeData();
   virtual ~CDBStyle_DensityFaceCodeData();
public:
   CDBStyle_DesFaceCodeList m_lstFaceCode;
   __int64 m_nIDDensity;//�ܶȹ����ֶ�����ID
public:
   void ResetData();
   void Copy(CDBStyle_DensityFaceCodeData * pData);
   void AddItem(CDBStyle_DesFaceCodeData * pData);
};

class CDBStyle_DesDenisityData  : public CDataMid
{
   DECLARE_SERIAL(CDBStyle_DesDenisityData)//���л������л�����Ҫ��ӵ�����
public:
   CDBStyle_DensityFaceCodeData m_faceData         ;//����������
   __int64                m_nID              ;//����ID
   int                    m_nStyleID         ;//��ʽID
   CString                m_strName          ;//����
   double                 m_fHorDesSrc       ;//����
   double                 m_fVerDesSrc       ;//ֱ��
   double                 m_fHorDesNew       ;//����
   double                 m_fVerDesNew       ;//ֱ��
   CString                m_strStructure     ;//�����ṹ
   CString                m_strMaterial      ;//ë��

   double	              m_fPull            ;//����
   CString                m_strPullUnit      ;//��λ
   int		              m_nPullType        ;//eg:ȫ���� or ������
   CString                m_strNeedle        ;//����

   //СƬ����
   double                 m_fPieceUnit       ;//100��
   double                 m_fPieceTurns      ;//100ת
   double                 m_fPieceNeedle     ;//100��

   //��ͷ��ת
   double                 m_fStartTurns      ;

   //��������
   CString                m_strRomanType     ;
   //��˿ת��
   CString                m_strWire          ;//��˿
   double                 m_fWireTurns       ;//ת
   int                    m_nWireType        ;//�Ƿ�ȫ��˿

   //����
   CString                m_strPinBottom     ;//��
   CString                m_strPinFace       ;//��
   int                    m_nPinType         ;//��������

   CString                m_strType          ;//�ܶ��Զ�������
   CString                m_strBaseType      ;//�����ܶ� or �����ܶ�

   BOOL                   m_bShowPZ          ;//�Ƿ���ʾ����
   CString                m_strPZName        ;//��������

   CString                m_strSavedUserID   ;//�û�ID
   CString                m_strSaveTime      ;//����ʱ��
   CString                m_strRemark        ;//�ܶ�˵��
   CString                m_strPieceName     ;//��Ƭ����
   CString                m_strMatName       ;//��������

public:
   CDBStyle_DesDenisityData();
   ~CDBStyle_DesDenisityData();
   void ResetData();
   void Copy(CDBStyle_DesDenisityData *pData);
   BOOL GetAllDBInfo(CADOConn *pADOConn);
   void SetFaceData(CDBStyle_DesFaceCodeData* data);

   BOOL InsertAllDBInfoByID(CADOConn * pADOConn);

};

class CDBStyle_DesDenisityList : public CTDataListMid<CDBStyle_DesDenisityList,CDBStyle_DesDenisityData>
{
public:
   CDBStyle_DesDenisityList();
   ~CDBStyle_DesDenisityList();
   void DeleteItemByName(const CString & strName);
   CDBStyle_DesDenisityData * GetItemByName(const CString & strName);
   void    MatchData(CDBStyle_DesFaceCodeData* data);

   BOOL GetDataByStyleID(CADOConn *pADOConn,int nStyleID);//���ݿ�ʽID��ȡ�б� wangzl 2019-6-24
#ifdef USING_GRIDCTRL_MARK
   //���ɱ������
   MAP_GridCtrl_AllData CreateGridData();
#endif // USING_GRIDCTRL_MARK
};