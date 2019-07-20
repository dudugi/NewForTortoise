/*************************************************
// <�ļ�>: DBStyleMaterial.h
// <˵��>: ��ʽԭ������ϢDB��
// <����>: WangZY
// <����>: 2019/05/24 11:29:21
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 

#pragma once

#ifndef MATERIEL_IMAGE
#define MATERIEL_IMAGE	1
#endif


#include "DataMid.h"

class CADOConn;
class CDBStyleMaterial :public CDataMid
{
   DECLARE_SERIAL( CDBStyleMaterial)//���л������л�����Ҫ��ӵ�����
public:
   CDBStyleMaterial(void);
   ~CDBStyleMaterial(void);

public:
   int         m_nID;                     //ID
   CString     m_strStyleNo;              //���
   CString     m_strMaterialNo;           //���ϱ��
   CString     m_strName;                 //��������
   CString     m_strLevel1Type;           //�����   
   CString     m_strLevel2Type;           //�����
   CString     m_strLevel3Type;           //С���
   CString     m_strUnit;                 //���ϵ�λ
   double      m_lfCount;                 //��������
   CString     m_strMemo;                 //����˵��
   CString     m_strSupplier;             //��Ӧ��
   double      m_lfPrice;                 //���ϵ���
   double      m_lfTotalPrice;            //�����ܼ�
   CString     m_strBrand;                //����Ʒ��
   CString     m_strChengFen;             //���ϲ���(�ɷ�)

#if MATERIEL_IMAGE
   Gdiplus::Image*		m_pMaterielPic;   //����ͼƬ
#endif
   BOOL        m_bHaveDownPic;            //ͼƬ�Ƿ�������



public:

#if MATERIEL_IMAGE
   void ClearColorImage();
#endif

#ifdef USING_GRIDCTRL_MARK
   //����ת��Ϊmap�б�����   	by WangZY 2019/05/25
   static BOOL ConvertDataToMapData(__out MAP_GridCtrl_RowData &mapData, __in CDBStyleMaterial *pData);
#endif

   void ResetData();
   void Copy(CDBStyleMaterial *pData);
   void GetAllDBInfo(CADOConn* pADOConn,bool bNeedPic = false);

   void GetImageFromDB(CADOConn* pAdo);

   BOOL InsetAllDBInfo(CADOConn* pADOConn);
   BOOL UpdateAllDBInfo(CADOConn* pADOConn); //����ID
   BOOL DeleteAllDBInfo(CADOConn* pADOConn); //����ID
   static CString GetDeleteByStyleNoSql(const CString & strStyleNo);

   CString GetInsertSql();
   CString GetUpdateSql();
   CString GetDeleteSql();
};


class CDBStyleMaterialList :public CDataListMid
{
   DECLARE_SERIAL( CDBStyleMaterialList)//���л������л�����Ҫ��ӵ�����
public:
   CDBStyleMaterialList(void);
   ~CDBStyleMaterialList(void);

   static CDBStyleMaterialList * Instance();//��ȡ��ָ�룩ʵ��

   CDBStyleMaterial* GetItem(int nIndex);			//����������ȡItem 
   CDBStyleMaterial* GetItemByMaterialNo(const CString & strMaterialNo);			//�������ϱ�Ż�ȡItem  nixf˵���ϱ����Ψһ��
   void AddItem(CDBStyleMaterial* pItem);			//���Item
   void DeleteItem(int nIndex);					//ɾ���̶�����Item
   void DeleteItemByMaterialNo(const CString & strMaterialNo);			//���Item
   void Copy(CDBStyleMaterialList *);

   //��ȡ��ʽ��ԭ������Ϣ	by WangZY 2019/05/25
   int GetStyleMaterialInfo(__in CADOConn* pADOConn, __in const CString &strStyleNo);

   //��ȡ�ɼ����ʽ��ԭ������Ϣ   	by WangZY 2019/05/27
   BOOL GetOrgMaterialInfo(__in CADOConn* pADOConn, 
      __in const CString &strLevel1Type,__in const CString &strLevel2Type,__in const CString &strLevel3Type);

public:
  

#ifdef USING_GRIDCTRL_MARK
   //List�б�ת��ΪMap�б�  	by WangZY 2019/05/25
   static BOOL ConvertListToMap(__out MAP_GridCtrl_AllData &mapData,__in CDBStyleMaterialList &listData);

   


   BOOL GetStyleMaterialInfo(CADOConn* pADOConn,CString strStyleNo,MAP_GridCtrl_AllData& all_data);

   //����ǰɾ���ÿ�žɵ�ԭ����Ϣ��Ȼ�����α����µģ����������߼��Ƚϼ�
   BOOL SaveStyleMaterialInfo(CADOConn* pADOConn,CString strStyleNo,MAP_GridCtrl_AllData all_data);      
#endif
   BOOL IsStyleMaterialInfoExist(CADOConn* pADOConn,CString strStyleNo);
   BOOL ClearStyleMaterialInfo(CADOConn* pADOConn,CString strStyleNo);
   BOOL SaveStyleMaterial(CADOConn* pADOConn,CString strStyleNo);
private:
   static std::shared_ptr<CDBStyleMaterialList> sm_inst;
};