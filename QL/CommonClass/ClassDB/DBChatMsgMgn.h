//����
#pragma once
#include <afxstr.h>
#include <set>
class CADOConn;
class CDBChatMsgMgn
{
public:
   static BOOL SendSystemMessage(CADOConn *pADOConn, const CString &sOrder, const CString &sContent,const CString & strUserID = _T(""));
   static BOOL SendSystemMessage(CADOConn *pADOConn, int nStyleID, const CString &sContent,const CString & strUserID = _T(""));

   //��ȡsCurrentUserID��δ���Ķ�������˳���ж�sCurOrder�Ƿ�����Щ����������
   static int GetUnreadAtMeOrderCount(CADOConn *pADOConn, const CString &sCurrentUserID, const CString &sCurOrder, BOOL *pbCurOrderExist);
private:
   //��ȡ@�Լ���δ���Ķ�����
   static BOOL GetUnreadAtMeOrders(CADOConn *pADOConn, const CString &sCurrentUserID, std::set<CString> *psetOrders);
};