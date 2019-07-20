#pragma once

/*************************************************
// <文件>: DBControlsPermission.h
// <说明>: 用户控件权限数据类
// <作者>: wangzl
// <日期>: 2019/02/21
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 

#include "DataMid.h"
class CADOConn;

class CDBControlsPermissionData  : public CDataMid
{
   DECLARE_SERIAL( CDBControlsPermissionData)//序列化（串行化）需要添加的声明
public:
   typedef enum EM_CONTROL_TYPE
   {
      en_Control_Normal = 1,//普通控件如按钮 编辑框 静态文本 等
      en_Control_Menu = 2,//菜单
   };
public:
   INT64       m_nID          ;//自增ID
   int         m_nDlgID       ;//对话框ID
   int         m_nDlgFlag     ;//对话框自定义标志
   int         m_nControlID   ;//控件ID
   int         m_nControlType ;//控件类型
   CString     m_strDescription;//控件说明

public:
   CDBControlsPermissionData();
   ~CDBControlsPermissionData();
   void ResetData();
   void Copy(CDBControlsPermissionData *pData);

   BOOL GetAllDBInfo(CADOConn *pADOConn);    //获取【整条】信息
   //BOOL UpdateAllDBInfo(CADOConn *pADOConn); //更新【整条】信息
   BOOL DelAllDBInfo(CADOConn *pADOConn);    //删除【整条】记录
   BOOL InsertAllDBIno(CADOConn *pADOConn);  //增加整【整条】记录

   CString GetInsertSQL() const;
};


class CDBControlsPermissionList  : public CDataListMid
{
   DECLARE_SERIAL(CDBControlsPermissionList)
public:
   CDBControlsPermissionList();
   ~CDBControlsPermissionList();
   CDBControlsPermissionData* GetItem(int nIndex);       //根据索引获取Item
   void AddItem(CDBControlsPermissionData* pItem);       //添加Item
   void DeleteItem(int nIndex);                          //删除固定索引Item

   //获取所有的用户权限列表
   void GetListFromDB(CADOConn *pADOConn);
   //根据用户的权限生成没有权限的列表
   void GetListFromDB(CADOConn *pADOConn,const CString & strUserPermission);//从数据库获取链表 strUserPermission是用户的权限字符串

   //处理对话框上面普通控件的权限
   void HandleWindowNormalControlPermission(CWnd * pWnd,UINT nIDTemplete,int nDlgFlag);

   //处理对话框上面菜单的权限
   void HandleWindowMenuControlPermission(CMenu* pPopup,UINT nIDTemplete,int nDlgFlag);

   //判断对应项是否在链表中
   BOOL HasItemInControlPermission(UINT nIDTemplete,int nDlgFlag,UINT nControlID,CDBControlsPermissionData::EM_CONTROL_TYPE nControlType);

   //使用当前链表中的数据初始化系统的数据
   BOOL InitDBControlPermission(CADOConn * pADOConn);

   static CDBControlsPermissionList * Instance();        //获取（指针）实例

private:
   static std::shared_ptr<CDBControlsPermissionList> sm_inst;
};



