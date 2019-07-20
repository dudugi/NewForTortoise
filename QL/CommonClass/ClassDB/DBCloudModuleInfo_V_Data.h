/*************************************************
// <文件>: DBCloudModuleInfo_V_Data.h
// <说明>: 云模块信息视图DB类
// <作者>: WangZY
// <日期>: 2019/06/04 11:09:55
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 

#pragma once
#include "datamid.h"
class CDBCloudModuleInfo_V_Data :
   public CDataMid
{
   DECLARE_SERIAL( CDBCloudModuleInfo_V_Data)//序列化（串行化）需要添加的声明
public:
   CDBCloudModuleInfo_V_Data(void);
   ~CDBCloudModuleInfo_V_Data(void);

public:
   int      m_nID;                        //模块文件ID
   CString  m_strOldFileName;             //模块文件名
   CString  m_strFileSavePath;            //模块文件路径
   int      m_nFileType;                  //模块文件类型:(目前是记录模块是否免费，0为加密，1为免费）
   int      m_nUploadSuccess;             //模块文件是否上传完成
   int      m_nState;                     //模块文件状态
   CString  m_strDescription;             //模块文件描述
   CString  m_strVerifyComment;           //模块文件审核人评语
   CString  m_strCheckCode;               //模块文件校验码(MD5值)
   CString  m_strModType;                 //模块类型(分类)
   CString  m_strProvider;                //模块文件的供应商
   CString  m_strTelPhone;                //模块文件联系电话
   int      m_nDownLoadNum;               //模块文件下载次数
   CString  m_strUserID;                  //上传者ID
   CString  m_strUserName;                //上传者名称
   CString  m_strUserPower;               //上传者权限
   CString  m_strRegeditTime;             //上传者注册时间
   int      m_nUserState;                 //上传者状态
   CString  m_strWechat;                  //上传者微信
   CString  m_strQQ;                      //上传者QQ
   CString  m_strRemark;                  //上传者备注
   CString  m_strSignature;               //上传者修改签名
   CString  m_strPhoneNum;                //上传者电话号码



public:
   void ResetData();
   void Copy(CDBCloudModuleInfo_V_Data *pData);
   BOOL GetAllDBInfo(CADOConn *pADOConn);				//获取【整条】信息

   //获取模块更新审核的SQL语句，参数默认值为-1即按审核标识生成，否则按传输的参数生成; 	by WangZY 2019/06/04
   CString GetUpdateCheckModuleInfoSQL(int nCheck=-1); 

   //获取模块更新删除标志的SQL语句，参数默认值为-1即按上传的标识生成，否则按传输的参数生成;
   CString GetUpdateModuleInfoDeleteFlagSQL(int nDeleteFlag =-1); 

#ifdef USING_GRIDCTRL_MARK
   //数据转换为map列表数据   	by WangZY 2019/06/04
   static BOOL ConvertDataToMapData(__out MAP_GridCtrl_RowData &mapData, __in CDBCloudModuleInfo_V_Data *pData);
#endif


};


class CDBCloudModuleInfo_V_List :public CDataListMid
{
   DECLARE_SERIAL( CDBCloudModuleInfo_V_List)//序列化（串行化）需要添加的声明
public:
   CDBCloudModuleInfo_V_List(void);
   ~CDBCloudModuleInfo_V_List(void);
public:
   void Copy(CDBCloudModuleInfo_V_List *pList);
   CDBCloudModuleInfo_V_Data*  GetItem(int nIndex);
   CDBCloudModuleInfo_V_Data*  GetItemByID(const CString & strID);
   CDBCloudModuleInfo_V_Data*  GetItemByID(const int & nID);
   int  GetIndexByID(const int & nID);
   int  GetIndexByID(const CString & strID);
   void AddItem(CDBCloudModuleInfo_V_Data *pItem);
   void DeleteItemByIndex(int nIndex);
   void DeleteItemByID(CString strID);
   void DeleteItemByID(int nID);

   //从数据库获取云模块信息  	by WangZY 2019/06/04
   BOOL GetCloudModuleInfo(CADOConn *pADOConn, const CString &strFilter);

#ifdef USING_GRIDCTRL_MARK
   //List列表转换为Map列表     	by WangZY 2019/06/04
   static BOOL ConvertListToGridMap(__out MAP_GridCtrl_AllData &mapData,__in CDBCloudModuleInfo_V_List &listData);
#endif


};

