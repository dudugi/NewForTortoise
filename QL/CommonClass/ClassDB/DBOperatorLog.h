#pragma once
#include "DBLogInfo.h"
#include "ADOConn.h"
/*************************************************
// <�ļ�>: DBOperatorLog.h
// <˵��>: ������־��
// <����>: liuhw
// <����>: 2019/02/14 15:42:54
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/

class DBOperatorLog
{
public:
   DBOperatorLog();
   DBOperatorLog(const DBOperatorLog & oSrcData);
   ~DBOperatorLog();
private:
   CString m_strMaker;    // ������ liuhw 2019/02/14
   CString m_strMacAddr; //Mac ��ַ liuhw 2019/02/14
   CString m_strProject; // ��Ŀ���� liuhw 2019/02/14
public:
   /*******************************************************************
   * @brief : ��ʼ��һЩ�̶���ֵ
   * @author : liuhw 2019/02/14 16:06:00
   * @param : strMark ������
   * @param : strMacAddr �����������ַ
   * @param : strProject ��Ŀ����
   * @example : 
   * @return :  
   *******************************************************************/
   static void InitData(CString strMark,CString strMacAddr,CString strProject);
   /*******************************************************************
   * @brief : д�������־
   * @author : liuhw 2019/02/14 15:45:46
   * @param : strCate:����
   * @param : strType:������
   * @param : strCode:���(��:����)
   * @param : strAction:������־����
   * @param : srInstrFace:��������
   * @example : theApp.WriteLog(g_TableID[enCate],g_LogType[enType],strCode,strMemo,strInterfaceID)
   * @return :  
   *******************************************************************/
   static BOOL WriteLog(CADOConn * pADOConn,CString strCate, CString strType, CString strCode,CString strAction, CString strInterFace = _T(""));
   /*******************************************************************
   * @brief : ��ȡд�������־��Sql
   * @author : liuhw 2019/02/14 15:46:18
   * @param : strCate:����
   * @param : strType:������
   * @param : strCode:���(��:����)
   * @param : strAction:������־����
   * @param : srInstrFace:�������� 
   * @example : theApp.GetWriteLogSQL(g_TableID[enCate],g_LogType[enType],strCode,strMemo,strInterfaceID)
   * @return :  
   *******************************************************************/
   static CString GetWriteLogSQL(CString strCate, CString strType, CString strCode,CString strAction, CString strInterFace = _T(""));
   static DBOperatorLog* Instance();
private:
   static std::shared_ptr<DBOperatorLog> sm_inst;
};