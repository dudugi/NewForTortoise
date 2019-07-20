/*************************************************
// <文件>: DBStyleMaterial.h
// <说明>: 款式原辅料信息DB类
// <作者>: WangZY
// <日期>: 2019/05/24 11:29:21
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 

#pragma once

#ifndef MATERIEL_IMAGE
#define MATERIEL_IMAGE	1
#endif


#include "DataMid.h"

class CADOConn;
class CDBStyleMaterial :public CDataMid
{
   DECLARE_SERIAL( CDBStyleMaterial)//序列化（串行化）需要添加的声明
public:
   CDBStyleMaterial(void);
   ~CDBStyleMaterial(void);

public:
   int         m_nID;                     //ID
   CString     m_strStyleNo;              //款号
   CString     m_strMaterialNo;           //物料编号
   CString     m_strName;                 //物料名称
   CString     m_strLevel1Type;           //大类别   
   CString     m_strLevel2Type;           //中类别
   CString     m_strLevel3Type;           //小类别
   CString     m_strUnit;                 //物料单位
   double      m_lfCount;                 //物料数量
   CString     m_strMemo;                 //物料说明
   CString     m_strSupplier;             //供应商
   double      m_lfPrice;                 //物料单价
   double      m_lfTotalPrice;            //物料总价
   CString     m_strBrand;                //物料品牌
   CString     m_strChengFen;             //物料材质(成份)

#if MATERIEL_IMAGE
   Gdiplus::Image*		m_pMaterielPic;   //物料图片
#endif
   BOOL        m_bHaveDownPic;            //图片是否已下载



public:

#if MATERIEL_IMAGE
   void ClearColorImage();
#endif

#ifdef USING_GRIDCTRL_MARK
   //数据转换为map列表数据   	by WangZY 2019/05/25
   static BOOL ConvertDataToMapData(__out MAP_GridCtrl_RowData &mapData, __in CDBStyleMaterial *pData);
#endif

   void ResetData();
   void Copy(CDBStyleMaterial *pData);
   void GetAllDBInfo(CADOConn* pADOConn,bool bNeedPic = false);

   void GetImageFromDB(CADOConn* pAdo);

   BOOL InsetAllDBInfo(CADOConn* pADOConn);
   BOOL UpdateAllDBInfo(CADOConn* pADOConn); //根据ID
   BOOL DeleteAllDBInfo(CADOConn* pADOConn); //根据ID
   static CString GetDeleteByStyleNoSql(const CString & strStyleNo);

   CString GetInsertSql();
   CString GetUpdateSql();
   CString GetDeleteSql();
};


class CDBStyleMaterialList :public CDataListMid
{
   DECLARE_SERIAL( CDBStyleMaterialList)//序列化（串行化）需要添加的声明
public:
   CDBStyleMaterialList(void);
   ~CDBStyleMaterialList(void);

   static CDBStyleMaterialList * Instance();//获取（指针）实例

   CDBStyleMaterial* GetItem(int nIndex);			//根据索引获取Item 
   CDBStyleMaterial* GetItemByMaterialNo(const CString & strMaterialNo);			//根据物料编号获取Item  nixf说物料编号是唯一的
   void AddItem(CDBStyleMaterial* pItem);			//添加Item
   void DeleteItem(int nIndex);					//删除固定索引Item
   void DeleteItemByMaterialNo(const CString & strMaterialNo);			//添加Item
   void Copy(CDBStyleMaterialList *);

   //获取款式的原辅料信息	by WangZY 2019/05/25
   int GetStyleMaterialInfo(__in CADOConn* pADOConn, __in const CString &strStyleNo);

   //获取可加入款式的原辅料信息   	by WangZY 2019/05/27
   BOOL GetOrgMaterialInfo(__in CADOConn* pADOConn, 
      __in const CString &strLevel1Type,__in const CString &strLevel2Type,__in const CString &strLevel3Type);

public:
  

#ifdef USING_GRIDCTRL_MARK
   //List列表转换为Map列表  	by WangZY 2019/05/25
   static BOOL ConvertListToMap(__out MAP_GridCtrl_AllData &mapData,__in CDBStyleMaterialList &listData);

   


   BOOL GetStyleMaterialInfo(CADOConn* pADOConn,CString strStyleNo,MAP_GridCtrl_AllData& all_data);

   //保存前删除该款号旧的原料信息，然后依次保存新的，这样处理逻辑比较简单
   BOOL SaveStyleMaterialInfo(CADOConn* pADOConn,CString strStyleNo,MAP_GridCtrl_AllData all_data);      
#endif
   BOOL IsStyleMaterialInfoExist(CADOConn* pADOConn,CString strStyleNo);
   BOOL ClearStyleMaterialInfo(CADOConn* pADOConn,CString strStyleNo);
   BOOL SaveStyleMaterial(CADOConn* pADOConn,CString strStyleNo);
private:
   static std::shared_ptr<CDBStyleMaterialList> sm_inst;
};