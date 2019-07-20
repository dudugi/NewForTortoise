/*************************************************
// <文件>: DBStyle_DesDenisity.h
// <说明>: 款式密度数据
// <作者>: wangzl
// <日期>: 2019/06/19
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
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
   __int64 m_nIDDensity;//密度关联字段自增ID
public:
   void ResetData();
   void Copy(CDBStyle_DensityFaceCodeData * pData);
   void AddItem(CDBStyle_DesFaceCodeData * pData);
};

class CDBStyle_DesDenisityData  : public CDataMid
{
   DECLARE_SERIAL(CDBStyle_DesDenisityData)//序列化（串行化）需要添加的声明
public:
   CDBStyle_DensityFaceCodeData m_faceData         ;//面子码数据
   __int64                m_nID              ;//自增ID
   int                    m_nStyleID         ;//款式ID
   CString                m_strName          ;//名称
   double                 m_fHorDesSrc       ;//横密
   double                 m_fVerDesSrc       ;//直密
   double                 m_fHorDesNew       ;//横密
   double                 m_fVerDesNew       ;//直密
   CString                m_strStructure     ;//坯布结构
   CString                m_strMaterial      ;//毛料

   double	              m_fPull            ;//拉力
   CString                m_strPullUnit      ;//单位
   int		              m_nPullType        ;//eg:全长拉 or 领下拉
   CString                m_strNeedle        ;//针型

   //小片重量
   double                 m_fPieceUnit       ;//100克
   double                 m_fPieceTurns      ;//100转
   double                 m_fPieceNeedle     ;//100针

   //起头空转
   double                 m_fStartTurns      ;

   //罗文排列
   CString                m_strRomanType     ;
   //加丝转数
   CString                m_strWire          ;//加丝
   double                 m_fWireTurns       ;//转
   int                    m_nWireType        ;//是否全加丝

   //排针
   CString                m_strPinBottom     ;//底
   CString                m_strPinFace       ;//面
   int                    m_nPinType         ;//排针类型

   CString                m_strType          ;//密度自定义类型
   CString                m_strBaseType      ;//大身密度 or 罗文密度

   BOOL                   m_bShowPZ          ;//是否显示排针
   CString                m_strPZName        ;//排针名称

   CString                m_strSavedUserID   ;//用户ID
   CString                m_strSaveTime      ;//保存时间
   CString                m_strRemark        ;//密度说明
   CString                m_strPieceName     ;//衣片名称
   CString                m_strMatName       ;//坯布名称

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

   BOOL GetDataByStyleID(CADOConn *pADOConn,int nStyleID);//根据款式ID获取列表 wangzl 2019-6-24
#ifdef USING_GRIDCTRL_MARK
   //生成表格数据
   MAP_GridCtrl_AllData CreateGridData();
#endif // USING_GRIDCTRL_MARK
};