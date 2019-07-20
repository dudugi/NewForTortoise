/*************************************************
// <文件>: DBUserStylePermission_V.h
// <说明>: 用户款式权限视图DB类 用于标记员工对款式的权限
// <作者>: wangzl
// <日期>: 2019/05/06
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 
#pragma once
#include "DataMid.h"

class CDBUserStylePermission_VData : public CDataMid
{
   DECLARE_SERIAL( CDBUserStylePermission_VData)//序列化（串行化）需要添加的声明
public:
   CDBUserStylePermission_VData(void);
   ~CDBUserStylePermission_VData(void);

   CString        m_strUserID;//用户ID
   CString        m_strStyleNo;//款号
   int            m_nPermission;//设置的权限
   int            m_nFixPermission;//不同身份对应的固有权限
   int            m_nUserType;//用户类型 1是创建人 0是设置的权限  2是工序执行人的权限
   CString        m_cPermissionTime; //权限截至时间,默认有限期为一年
public:
   void ResetData();
   void Copy(CDBUserStylePermission_VData *pData);
   BOOL GetAllDBInfo(CADOConn *pADOConn);				//获取【整条】信息
};

class CDBUserStylePermission_VList :public CDataListMid
{
   DECLARE_SERIAL( CDBUserStylePermission_VList)//序列化（串行化）需要添加的声明
public:
   CDBUserStylePermission_VList(void);
   ~CDBUserStylePermission_VList(void);
public:
   void Copy(CDBUserStylePermission_VList *pList);
   CDBUserStylePermission_VData*  GetItem(int nIndex);
   CDBUserStylePermission_VData*  GetItemByUserID(const CString & strUserID);
   int  GetIndexByUserID(const CString & strUserID);
   void AddItem(CDBUserStylePermission_VData *pItem);
   void DeleteItemByIndex(int nIndex);
   void DeleteItemByUserID(CString strUserID);
   BOOL IsStyleHaveDeletePermission(CADOConn *pADOConn,CString strLoadUserID,std::vector<CString>vecKuanhao);//对应款式是否有删除权限 yangjr 2019/05/20
   BOOL GetDataByStyleNo(CADOConn *pADOConn,CString strStyleNo);//根据款号获取权限list yangjr 2019/05/22
   BOOL SimpleHasPermision(CADOConn *pADOConn, const CString &strStyleNo, const CString &strLoadUserID); //简单地判断一下是否有权限（只要出现在PDM右侧列表就算）
};
