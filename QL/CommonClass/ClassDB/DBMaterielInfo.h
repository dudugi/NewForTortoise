/*************************************************
// <�ļ�>: DBMaterielInfo.h
// <˵��>: ������Ϣ�����ݲ���DB��
// <����>: WangZY
// <����>: 2019/02/22 17:39:26
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
#pragma once
#ifndef MATERIEL_IMAGE
#define MATERIEL_IMAGE	1
#endif

#include <map>
#include "DataMid.h"
#include "DBKeyDef.h"

class CADOConn;

class CMaterielTypeInfo
{
public:
   CMaterielTypeInfo()
   {
      m_strName = _T("");
      Clear();

   }
   ~CMaterielTypeInfo()
   {
      Clear();
   }

   void Clear()
   {
      m_vecChildType.clear();
   }

   CMaterielTypeInfo* Find(CString strName)
   {
      for (auto it=m_vecChildType.begin();
         it!=m_vecChildType.end(); ++it)
      {
         if (it->m_strName==strName)
         {
            return &(*it);
         }
      }

      return nullptr;
   }

   BOOL AddItem(CString strName, CString *pStrSubName= nullptr)
   {
      if (strName.IsEmpty())
      {
         return FALSE;
      }

      auto pInfo = Find(strName);
      if (nullptr != pInfo)
      {
         if (nullptr != pStrSubName)
         {
            pInfo->AddItem(*pStrSubName);
         }  
      }
      else
      {
         CMaterielTypeInfo info;

         info.m_strName = strName;
         if (nullptr != pStrSubName)
         {
            info.AddItem(*pStrSubName);
         } 
         m_vecChildType.push_back(info);    
      }

      return TRUE;
   }

public:
   CString m_strName;
   std::vector<CMaterielTypeInfo> m_vecChildType;
};

class CMateriel5LevelInfo
{
public:
   CMateriel5LevelInfo()
   {

   }
   ~CMateriel5LevelInfo()
   {
      Clear();
   }

   void Clear()
   {
      m_infoLevel1_2.Clear();
      m_infoLevel2_3.Clear();
      m_infoLevel3_4.Clear();
      m_infoLevel4_5.Clear();
   }

public:
   CMaterielTypeInfo m_infoLevel1_2;
   CMaterielTypeInfo m_infoLevel2_3;
   CMaterielTypeInfo m_infoLevel3_4;
   CMaterielTypeInfo m_infoLevel4_5;

};



class CDBMaterielInfoData  : public CDataMid
{
	DECLARE_SERIAL( CDBMaterielInfoData)//���л������л�����Ҫ��ӵ�����
public:
	CString				m_strID;			   //���ϱ��
	CString	         m_strName;		   //��������
	CString			   m_strLevel1Type;	//һ�����
   CString			   m_strLevel2Type;	//������� 
   CString			   m_strLevel3Type;	//������� 
   CString			   m_strLevel4Type;	//�ļ���� 
   CString			   m_strLevel5Type;	//�弶��� 
	CString			   m_strUnit;		   //���ϵ�λ
	CString			   m_strChengfen;	   //���ϲ���(�ɷ�)
   CString			   m_strMemo;	      //����˵��
   double   	      m_nPrice;	      //���ϵ���
   CString			   m_strBrand;	      //����Ʒ��
   CString           m_strSupplier;    //��Ӧ��
	//�������ݿ���
   CString           m_strActLog;      //������־ liuhw 2018/09/07
#if MATERIEL_IMAGE
	Gdiplus::Image*		m_pMaterielPic;   //ͼƬ
#endif

	CString			   m_strCurResv;	 //��ǰ��� ɴ�߿��Ԥ�������õ��������ݿ��޹�����add by lida 2017/06/15
   bool              m_bHaveDownPic;//ͼƬ�Ƿ������� yangjr 2017/1/30
public:
	CDBMaterielInfoData();
	~CDBMaterielInfoData();
	void ResetData();
	void Copy(CDBMaterielInfoData *pData);
	void Serialize(CArchive& ar);
	BOOL GetAllDBInfo(CADOConn *pADOConn,bool bNeedColorCard=false);		//��ȡɴ�ߡ���������Ϣ
   BOOL GetAllDBInfoByID(CADOConn *pADOConn,bool bNeedColorCard=false);		//��ȡɴ�ߡ���������Ϣ
	BOOL DelAllDBInfoByID(CADOConn *pADOConn);		//ɾ������������¼
	BOOL UpdateAllDBInfoByID(CADOConn *pADOConn);	//����ɴ�ߺŸ��¡���������¼
	BOOL InsertAllDBInfoByID(CADOConn *pADOConn);	//����ɴ�ߺŲ��롾��������¼
   
   //�Ƚ��޸�ǰ�����ݣ����޸��˵����ݱ�������
   CString SetDBEquals_Log(CDBMaterielInfoData &pOldData);

   BOOL GetPictureDataByID(CADOConn *pADOConn,
      CString strID, Gdiplus::Image *&pPic);	//����ID��ȡͼƬ

   void Trim();
	static CDBMaterielInfoData * Instance();//��ȡ��ָ�룩ʵ��

#ifdef MATERIEL_IMAGE
private:
	inline void ClearColorImage();
#endif // YARN_IMAGE
private:
	static std::shared_ptr<CDBMaterielInfoData> sm_inst;
};

class CDBMaterielInfoList : public CDataListMid
{
	DECLARE_SERIAL(CDBMaterielInfoList)
public:
	CDBMaterielInfoList();
	~CDBMaterielInfoList();
	CDBMaterielInfoData*  GetItem(int nIndex);
	void    AddItem(CDBMaterielInfoData* pItem);
	void    DeleteItem(int nIndex);
	CDBMaterielInfoData* GetItemByMaterielId(CString strId);
	int GetIndexByMaterielId(CString strId);

	void GetListFromDB(CADOConn *pADOConn,bool bNeedPic = false);//�����ݿ��ȡ����
	static CDBMaterielInfoList * Instance();//��ȡ��ָ�룩ʵ��

   void SetAllItemDownPic(bool bDownPic);//���������������ͼƬ��־
   void SetDownPicFlagById(CString strID,bool bDownPic); //��������ͼƬ��־ 
   void SetPicDataById(CString strID, Gdiplus::Image* pPic); //����ͼƬ����

  
   BOOL GetInfoByMaterielId(__in CADOConn *pADOConn,__in CString strId,
      __out CDBMaterielInfoData* pObj);

   //��ȡ��㼶��������Ϣ			by WangZY 2018/08/07
   BOOL GetLevelTypeInfo(__in CADOConn *pADOConn, __out CMateriel5LevelInfo &info);

   //��ȡ���㼶��������Ϣ		by WangZY 2018/08/07
   BOOL Get3LevelTypeInfo(__in CADOConn *pADOConn, __out CMateriel5LevelInfo &info);

   BOOL operator = (CDBMaterielInfoList &pData);  // anjie 2018/09/15
#ifdef USING_GRIDCTRL_MARK
	MAP_GridCtrl_AllData CreatrGridData();

	//����һ���յ�������		by WangZY 2017/08/24
	BOOL GetEmptyRowData(__out MAP_GridCtrl_RowData &mapEmptyRowData);

#endif // USING_GRIDCTRL_MARK
	

private:
	static std::shared_ptr<CDBMaterielInfoList> sm_inst;
};