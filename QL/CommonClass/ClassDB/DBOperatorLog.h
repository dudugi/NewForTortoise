#pragma once
#include "DBLogInfo.h"
#include "ADOConn.h"
/*************************************************
// <文件>: DBOperatorLog.h
// <说明>: 操作日志类
// <作者>: liuhw
// <日期>: 2019/02/14 15:42:54
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/

class DBOperatorLog
{
public:
   DBOperatorLog();
   DBOperatorLog(const DBOperatorLog & oSrcData);
   ~DBOperatorLog();
private:
   CString m_strMaker;    // 操作人 liuhw 2019/02/14
   CString m_strMacAddr; //Mac 地址 liuhw 2019/02/14
   CString m_strProject; // 项目名称 liuhw 2019/02/14
public:
   /*******************************************************************
   * @brief : 初始化一些固定的值
   * @author : liuhw 2019/02/14 16:06:00
   * @param : strMark 操作人
   * @param : strMacAddr 操作人物理地址
   * @param : strProject 项目名称
   * @example : 
   * @return :  
   *******************************************************************/
   static void InitData(CString strMark,CString strMacAddr,CString strProject);
   /*******************************************************************
   * @brief : 写入操作日志
   * @author : liuhw 2019/02/14 15:45:46
   * @param : strCate:表名
   * @param : strType:操作名
   * @param : strCode:编号(如:单号)
   * @param : strAction:操作日志内容
   * @param : srInstrFace:界面名称
   * @example : theApp.WriteLog(g_TableID[enCate],g_LogType[enType],strCode,strMemo,strInterfaceID)
   * @return :  
   *******************************************************************/
   static BOOL WriteLog(CADOConn * pADOConn,CString strCate, CString strType, CString strCode,CString strAction, CString strInterFace = _T(""));
   /*******************************************************************
   * @brief : 获取写入操作日志的Sql
   * @author : liuhw 2019/02/14 15:46:18
   * @param : strCate:表名
   * @param : strType:操作名
   * @param : strCode:编号(如:单号)
   * @param : strAction:操作日志内容
   * @param : srInstrFace:界面名称 
   * @example : theApp.GetWriteLogSQL(g_TableID[enCate],g_LogType[enType],strCode,strMemo,strInterfaceID)
   * @return :  
   *******************************************************************/
   static CString GetWriteLogSQL(CString strCate, CString strType, CString strCode,CString strAction, CString strInterFace = _T(""));
   static DBOperatorLog* Instance();
private:
   static std::shared_ptr<DBOperatorLog> sm_inst;
};