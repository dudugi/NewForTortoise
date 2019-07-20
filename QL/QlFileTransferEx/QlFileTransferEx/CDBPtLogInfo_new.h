#pragma once
#include "stdafx.h"
#include "ADOConnEx.h"
#include "ClassDB\DBPersonInfo.h"
#include "DBDef.h"
#include "ClassDB\DBCustomInfo.h"
#include "CommonAPI.h"

class CDBPtLogInfo_New
{
//变量
public:
   int m_nTheardEndFlag;//线程结束反馈标志
   CString m_strConnectSql;
private:
   typedef struct STRUCT_LogInfo{
      STRUCT_LogInfo()
      {
          m_strCate = _T("");
          m_strCode = _T("");
          m_strMemo = _T("");
          m_strType = _T("");
          m_strMaker= _T("");
      }
      CString m_strCate;      //类别
      CString m_strCode;      //单号
      CString m_strMemo;      //备注
      CString m_strType;      //类型
      CString m_strMaker;     //操作人
   }STRUCT_LOGINFO;

   map<int, STRUCT_LOGINFO> m_LogInfo; //日志信息
   CString m_strMacAddr; //Mac地址
protected:
//函数
public:
   CDBPtLogInfo_New();

   ~CDBPtLogInfo_New();
   void Clear();
   void ResetData();
   void SetDataLogInfo(CADOConnEx *pADOConn,CString strCate, CString strCode ,CString strMemo,CString strType,CString strMakerID,int nLoginType); //设置日志数据
   BOOL InsertSQL_LogInfo(CADOConnEx *pADOConn);//日志信息

   static CDBPtLogInfo_New *Instance();
private:
   typedef enum S_FileTrans_LoginType{
      En_Login_User = 0,//员工登录
      En_Login_Custom,//客户登录
   }S_FILETRANS_LOGINTYPE;

   static std::shared_ptr<CDBPtLogInfo_New> sm_inst;
   BOOL m_bLog;		//是否记录到数据库
};