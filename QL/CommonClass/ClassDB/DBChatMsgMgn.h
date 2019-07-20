//聊天
#pragma once
#include <afxstr.h>
#include <set>
class CADOConn;
class CDBChatMsgMgn
{
public:
   static BOOL SendSystemMessage(CADOConn *pADOConn, const CString &sOrder, const CString &sContent,const CString & strUserID = _T(""));
   static BOOL SendSystemMessage(CADOConn *pADOConn, int nStyleID, const CString &sContent,const CString & strUserID = _T(""));

   //获取sCurrentUserID的未读的订单数，顺便判断sCurOrder是否在这些订单号里面
   static int GetUnreadAtMeOrderCount(CADOConn *pADOConn, const CString &sCurrentUserID, const CString &sCurOrder, BOOL *pbCurOrderExist);
private:
   //获取@自己的未读的订单们
   static BOOL GetUnreadAtMeOrders(CADOConn *pADOConn, const CString &sCurrentUserID, std::set<CString> *psetOrders);
};