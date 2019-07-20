/*************************************************
// <文件>: DBMaterielInfo.h
// <说明>: 物料信息表数据操作DB类
// <作者>: WangZY
// <日期>: 2019/02/22 17:39:26
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
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
	DECLARE_SERIAL( CDBMaterielInfoData)//序列化（串行化）需要添加的声明
public:
	CString				m_strID;			   //物料编号
	CString	         m_strName;		   //物料名称
	CString			   m_strLevel1Type;	//一级类别
   CString			   m_strLevel2Type;	//二级类别 
   CString			   m_strLevel3Type;	//三级类别 
   CString			   m_strLevel4Type;	//四级类别 
   CString			   m_strLevel5Type;	//五级类别 
	CString			   m_strUnit;		   //物料单位
	CString			   m_strChengfen;	   //物料材质(成份)
   CString			   m_strMemo;	      //物料说明
   double   	      m_nPrice;	      //物料单价
   CString			   m_strBrand;	      //物料品牌
   CString           m_strSupplier;    //供应商
	//不在数据库中
   CString           m_strActLog;      //操作日志 liuhw 2018/09/07
#if MATERIEL_IMAGE
	Gdiplus::Image*		m_pMaterielPic;   //图片
#endif

	CString			   m_strCurResv;	 //当前库存 纱线库存预警界面用到，和数据库无关联，add by lida 2017/06/15
   bool              m_bHaveDownPic;//图片是否已下载 yangjr 2017/1/30
public:
	CDBMaterielInfoData();
	~CDBMaterielInfoData();
	void ResetData();
	void Copy(CDBMaterielInfoData *pData);
	void Serialize(CArchive& ar);
	BOOL GetAllDBInfo(CADOConn *pADOConn,bool bNeedColorCard=false);		//获取纱线【整条】信息
   BOOL GetAllDBInfoByID(CADOConn *pADOConn,bool bNeedColorCard=false);		//获取纱线【整条】信息
	BOOL DelAllDBInfoByID(CADOConn *pADOConn);		//删除【整条】记录
	BOOL UpdateAllDBInfoByID(CADOConn *pADOConn);	//根据纱线号更新【整条】记录
	BOOL InsertAllDBInfoByID(CADOConn *pADOConn);	//根据纱线号插入【整条】记录
   
   //比较修改前后数据，将修改了的数据保存起来
   CString SetDBEquals_Log(CDBMaterielInfoData &pOldData);

   BOOL GetPictureDataByID(CADOConn *pADOConn,
      CString strID, Gdiplus::Image *&pPic);	//根据ID获取图片

   void Trim();
	static CDBMaterielInfoData * Instance();//获取（指针）实例

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

	void GetListFromDB(CADOConn *pADOConn,bool bNeedPic = false);//从数据库获取链表
	static CDBMaterielInfoList * Instance();//获取（指针）实例

   void SetAllItemDownPic(bool bDownPic);//设置所有项的下载图片标志
   void SetDownPicFlagById(CString strID,bool bDownPic); //设置下载图片标志 
   void SetPicDataById(CString strID, Gdiplus::Image* pPic); //设置图片数据

  
   BOOL GetInfoByMaterielId(__in CADOConn *pADOConn,__in CString strId,
      __out CDBMaterielInfoData* pObj);

   //获取五层级别分类的信息			by WangZY 2018/08/07
   BOOL GetLevelTypeInfo(__in CADOConn *pADOConn, __out CMateriel5LevelInfo &info);

   //获取三层级别分类的信息		by WangZY 2018/08/07
   BOOL Get3LevelTypeInfo(__in CADOConn *pADOConn, __out CMateriel5LevelInfo &info);

   BOOL operator = (CDBMaterielInfoList &pData);  // anjie 2018/09/15
#ifdef USING_GRIDCTRL_MARK
	MAP_GridCtrl_AllData CreatrGridData();

	//生成一条空的行数据		by WangZY 2017/08/24
	BOOL GetEmptyRowData(__out MAP_GridCtrl_RowData &mapEmptyRowData);

#endif // USING_GRIDCTRL_MARK
	

private:
	static std::shared_ptr<CDBMaterielInfoList> sm_inst;
};