#pragma once
#ifndef MATERIEL_IMAGE
#define MATERIEL_IMAGE	1
#endif

#include <map>
#include "DataMid.h"
#include "DBKeyDef.h"

/*************************************************
// <文件>: DBColorMaintainInfo.h
// <说明>: 纱线信息表
// <作者>: wangzl
// <日期>: 2019/02/22
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
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
	DECLARE_SERIAL( CDBColorMaintainInfo)//序列化（串行化）需要添加的声明
public:
	CString				m_strID;			      //颜色ID
	CString	         m_strClrName;		   //颜色名称
	CString			   m_strClrCode;	      //颜色编号
   CString			   m_strClrRGB;	      //颜色RGB
	CString			   m_strClrMemo;	      //颜色说明
public:
	CDBColorMaintainInfo();
	~CDBColorMaintainInfo();
	void ResetData();
	void Copy(CDBColorMaintainInfo *pData);
	void Serialize(CArchive& ar);
	BOOL GetAllDBInfo(CADOConn *pADOConn,bool bNeedColorCard=false);		//获取纱线【整条】信息
   BOOL GetAllDBInfoByID(CADOConn *pADOConn,bool bNeedColorCard=false);		//获取纱线【整条】信息通过ID   add anjie by 2018/09/20
	BOOL DelAllDBInfoByID(CADOConn *pADOConn);		//删除【整条】记录
	BOOL UpdateAllDBInfoByID(CADOConn *pADOConn);	//根据纱线号更新【整条】记录
	BOOL InsertAllDBInfoByID(CADOConn *pADOConn);	//根据纱线号插入【整条】记录
   void Trim();
	static CDBColorMaintainInfo * Instance();//获取（指针）实例
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
	void GetListFromDB(CADOConn *pADOConn,bool bNeedPic = false);//从数据库获取链表
	static CDBColorMaintainInfoList * Instance();//获取（指针）实例

   BOOL GetInfoByColorId(__in CADOConn *pADOConn,__in CString strId,
      __out CDBColorMaintainInfo* pObj);

   BOOL operator = (CDBColorMaintainInfoList &pData);  // 运算符重载 anjie 2018/09/15
#ifdef USING_GRIDCTRL_MARK
	MAP_GridCtrl_AllData CreatrGridData();
   //生成一个空的数据
	BOOL GetEmptyRowData(__out MAP_GridCtrl_RowData &mapEmptyRowData);

#endif // USING_GRIDCTRL_MARK
	

private:
	static std::shared_ptr<CDBColorMaintainInfoList> sm_inst;
};