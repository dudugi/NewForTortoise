#pragma once
#ifndef MATERIEL_IMAGE
#define MATERIEL_IMAGE	1
#endif

#include <map>
#include "DataMid.h"
#include "DBKeyDef.h"

/*************************************************
// <�ļ�>: DBColorMaintainInfo.h
// <˵��>: ɴ����Ϣ��
// <����>: wangzl
// <����>: 2019/02/22
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 

class CADOConn;

class CColorMaintainInfo
{
public:
   CColorMaintainInfo()
   {
      m_strName = ("");
      Clear();

   }
   ~CColorMaintainInfo()
   {
      Clear();
   }

   void Clear()
   {
      m_vecChildType.clear();
   }

   CColorMaintainInfo* Find(CString strName)
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
         CColorMaintainInfo info;

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
   std::vector<CColorMaintainInfo> m_vecChildType;
};

class CDBColorMaintainInfo  : public CDataMid
{
	DECLARE_SERIAL( CDBColorMaintainInfo)//���л������л�����Ҫ��ӵ�����
public:
	CString				m_strID;			      //��ɫID
	CString	         m_strClrName;		   //��ɫ����
	CString			   m_strClrCode;	      //��ɫ���
   CString			   m_strClrRGB;	      //��ɫRGB
	CString			   m_strClrMemo;	      //��ɫ˵��
public:
	CDBColorMaintainInfo();
	~CDBColorMaintainInfo();
	void ResetData();
	void Copy(CDBColorMaintainInfo *pData);
	void Serialize(CArchive& ar);
	BOOL GetAllDBInfo(CADOConn *pADOConn,bool bNeedColorCard=false);		//��ȡɴ�ߡ���������Ϣ
   BOOL GetAllDBInfoByID(CADOConn *pADOConn,bool bNeedColorCard=false);		//��ȡɴ�ߡ���������Ϣͨ��ID   add anjie by 2018/09/20
	BOOL DelAllDBInfoByID(CADOConn *pADOConn);		//ɾ������������¼
	BOOL UpdateAllDBInfoByID(CADOConn *pADOConn);	//����ɴ�ߺŸ��¡���������¼
	BOOL InsertAllDBInfoByID(CADOConn *pADOConn);	//����ɴ�ߺŲ��롾��������¼
   void Trim();
	static CDBColorMaintainInfo * Instance();//��ȡ��ָ�룩ʵ��
   COLORREF StrConvertToColor();    //
private:
	static std::shared_ptr<CDBColorMaintainInfo> sm_inst;
};

class CDBColorMaintainInfoList : public CDataListMid
{
	DECLARE_SERIAL(CDBColorMaintainInfoList)
public:
	CDBColorMaintainInfoList();
	~CDBColorMaintainInfoList();
	CDBColorMaintainInfo*  GetItem(int nIndex);
	void    AddItem(CDBColorMaintainInfo* pItem);
	void    DeleteItem(int nIndex);
	CDBColorMaintainInfo* GetItemByColorCode(CString strCode);
	int GetIndexByColorId(CString strId);
	void GetListFromDB(CADOConn *pADOConn,bool bNeedPic = false);//�����ݿ��ȡ����
	static CDBColorMaintainInfoList * Instance();//��ȡ��ָ�룩ʵ��

   BOOL GetInfoByColorId(__in CADOConn *pADOConn,__in CString strId,
      __out CDBColorMaintainInfo* pObj);

   BOOL operator = (CDBColorMaintainInfoList &pData);  // ��������� anjie 2018/09/15
#ifdef USING_GRIDCTRL_MARK
	MAP_GridCtrl_AllData CreatrGridData();
   //����һ���յ�����
	BOOL GetEmptyRowData(__out MAP_GridCtrl_RowData &mapEmptyRowData);

#endif // USING_GRIDCTRL_MARK
	

private:
	static std::shared_ptr<CDBColorMaintainInfoList> sm_inst;
};