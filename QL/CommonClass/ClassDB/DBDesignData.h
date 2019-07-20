#pragma once
#include "DataMid.h"
class CADOConn;

#define DB_TABLE_DesignData		            _T("DesignData")          // 制版管理表
                                                                          
#define DBDesignData_key_ID			         _T("ID")		              // 自增ID
#define DBDesignData_key_Name	    	         _T("cName")		           // 名称
#define DBDesignData_key_cSavedUserID        _T("cSavedUserID")        // 保存人
#define DBDesignData_key_cSaveTime           _T("cSaveTime")           // 保存时间
#define DBDesignData_key_cData               _T("cData")               // 保存时间

/*************************************************
// <文件>: DBDesignData.h
// <说明>: 制版管理DB类
// <作者>: huangym(头文件注释)
// <日期>: 2019/02/21 16:09:22
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/

class CDBDesignData :
   public CDataMid
{
   DECLARE_SERIAL(CDBDesignData)                                       // 序列化（串行化）需要添加的声明
public:
   CDBDesignData();
   ~CDBDesignData();;
   void ResetData();                                                   // 重置数据
   BOOL UpdateDBInfo(CADOConn * pADOConn);                             // 更新数据
   BOOL GetAllDBInfo(CADOConn *pADOConn);		                          // 获取【整条】信息
   void Copy(CDBDesignData *pData);                                    // 拷贝数据

   
   CString GetInsertSQL();                                             // 获取插入的SQL语句
   static CDBDesignData * Instance();                                  // 获取（指针）实例
   BOOL UpdateAllDBInfoByID(CADOConn * pADOConn);                      // 更新数据到数据库
   BOOL InsertAllDBInfoByID(CADOConn * pADOConn);                      // 插入数据到数据库
private:
   static std::shared_ptr<CDBDesignData> sm_inst;

public:
   __int64		               m_nID;                                   // 自增ID
   CString                    m_strName;                               // 名称
   CString                    m_strSavedUserID;                        // 用户ID
   CString                    m_strSaveTime;                           // 保存时间
   CString                    m_strData;                                 // 数据
};


class CDBDesignDataList : public CDataListMid
{
   DECLARE_SERIAL(CDBDesignDataList)
public:
   CDBDesignDataList();
   ~CDBDesignDataList();
   CDBDesignData*  GetItem(int nIndex);
   void    AddItem(CDBDesignData* pItem);
   void    DeleteItem(int nIndex);
   BOOL    DeleteUserByUserID(CADOConn * pADOConn, vector<CString> vecUserID);

   static CDBDesignDataList * Instance();		                          //获取（指针）实例
                                                                       //生成表格数据
   MAP_GridCtrl_AllData CreateGridData(const CString & strUserDuty = _T(""));

private:
   static std::shared_ptr<CDBDesignDataList> sm_inst;
};
