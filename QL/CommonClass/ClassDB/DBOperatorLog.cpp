#include "stdafx.h"
#include "DBOperatorLog.h"

std::shared_ptr<DBOperatorLog> DBOperatorLog::sm_inst;

DBOperatorLog::DBOperatorLog()
{
   m_strMaker = _T("");    // 操作人 liuhw 2019/02/14
   m_strMacAddr = _T(""); //Mac 地址 liuhw 2019/02/14
   m_strProject = _T(""); // 项目名称 liuhw 2019/02/14
}

DBOperatorLog::DBOperatorLog(const DBOperatorLog & oSrcData)
{
   m_strMaker = oSrcData.m_strMaker;
   m_strMacAddr = oSrcData.m_strMacAddr;
   m_strProject = oSrcData.m_strProject; 
}

DBOperatorLog::~DBOperatorLog()
{
}

DBOperatorLog* DBOperatorLog::Instance()
{
   if(sm_inst.get() == 0)
      sm_inst = shared_ptr<DBOperatorLog>(new DBOperatorLog);

   return sm_inst.get();
}
void DBOperatorLog::InitData(CString strMaker,CString strMacAddr,CString strProject)
{
   DBOperatorLog::Instance()->m_strMaker = strMaker;
   DBOperatorLog::Instance()->m_strMacAddr = strMacAddr;
   DBOperatorLog::Instance()->m_strProject = strProject;
}
BOOL DBOperatorLog::WriteLog(CADOConn * pADOConn,CString strCate, CString strType, CString strCode,CString strAction, CString strInterFace)
{
   BOOL bRet;
   CDBLogInfoData::Instance()->SetLogData(strCate,strCode,DBOperatorLog::Instance()->m_strMaker,strType,strAction,strInterFace,
      DBOperatorLog::Instance()->m_strProject,DBOperatorLog::Instance()->m_strMacAddr);
   bRet = CDBLogInfoData::Instance()->InsertAllDBInfoByAct(pADOConn);
   CDBLogInfoData::Instance()->EmptyLogAction();
   return bRet;

}

CString DBOperatorLog::GetWriteLogSQL(CString strCate, CString strType, CString strCode,CString strAction, CString strInterFace)
{
   CString strSQL = _T("");
   CDBLogInfoData::Instance()->SetLogData(strCate,strCode,DBOperatorLog::Instance()->m_strMaker,strType,strAction,strInterFace
      ,DBOperatorLog::Instance()->m_strProject,DBOperatorLog::Instance()->m_strMacAddr);
   strSQL = CDBLogInfoData::Instance()->GetSQLInsertAllDBInfoByAct();
   CDBLogInfoData::Instance()->EmptyLogAction();
   return strSQL;
}