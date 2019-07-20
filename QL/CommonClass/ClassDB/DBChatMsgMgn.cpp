#include "StdAfx.h"
#include <afxdd_.h>
#include "DBChatMsgMgn.h"
#include "ADOConn\ADOConn.h"
#include "DBKeyDef.h"
#include "DBDef.h"
#include "DataMid.h"

BOOL CDBChatMsgMgn::SendSystemMessage(CADOConn *pADOConn, const CString &sOrder, const CString &sContent,const CString & strUserID /*= _T("")*/)
{
   CString strSQL;

   strSQL.Format(_T("insert into Chat_MsgMgn (cOrderNo,cSendUserID,dSendTime,cContent,cFile,iMsgType) \
                    values('%s','%s', GETDATE(),'%s',NULL, -1) "),
                    sOrder,strUserID, sContent);

   if (!pADOConn->ExecuteSQL(strSQL))
   {
      return FALSE;
   }

   return TRUE;
}

BOOL CDBChatMsgMgn::SendSystemMessage(CADOConn *pADOConn, int nStyleID, const CString &sContent,const CString & strUserID /*= _T("")*/)
{
   CString strSQL;

   strSQL.Format(_T("insert into Chat_MsgMgn (cOrderNo,cSendUserID,dSendTime,cContent,cFile,iMsgType) \
                    select %s,%s, %s,'%s',NULL, -1 from %s where %s = '%d' "),
                    DBKuanShi_key_StyleNo,strUserID,DBS_GETDATESTR, sContent,
                    DB_TABLE_STYLE,DBKuanShi_key_ID,nStyleID
                    );

   if (!pADOConn->ExecuteSQL(strSQL))
   {
      return FALSE;
   }

   return TRUE;
}

//获取@自己的未读的订单数
BOOL CDBChatMsgMgn::GetUnreadAtMeOrders(CADOConn *pADOConn, const CString &sCurrentUserID, std::set<CString> *psetOrders)
{
   if (!psetOrders)
      return FALSE;
   if (!pADOConn)
      return FALSE;
   set<CString> setOrders;
   CString strSQL;
   strSQL.Format(_T("SELECT   A.cOrderNo \
      FROM      Chat_MsgMgn AS A LEFT OUTER JOIN \
      (SELECT   cOrderNo, cRecvUserID, dLastReadMsgTime AS dSendTime \
      FROM      Chat_OrderLastRead \
      WHERE   (cRecvUserID = '%s')) AS B ON A.cOrderNo = B.cOrderNo LEFT OUTER JOIN \
      Chat_MsgRecv AS C ON A.AutoID = C.MsgID \
      WHERE   (C.cRecvUserID = '%s' OR A.cSendUserID = '%s') AND (A.dSendTime > B.dSendTime OR B.dSendTime IS NULL) \
      GROUP BY A.cOrderNo"), sCurrentUserID, sCurrentUserID, sCurrentUserID);

   pADOConn->GetRecordSet(strSQL);
   while (!pADOConn->adoEOF())
   {
      CString sOrderNo = pADOConn->GetValueString(_T("cOrderNo"));
      if (!sOrderNo.IsEmpty())
         setOrders.insert(sOrderNo);
      pADOConn->MoveNext();
   }
   psetOrders->swap(setOrders);
   return TRUE;
}

//获取sCurrentUserID的未读的订单数，顺便判断sCurOrder是否在这些订单号里面
int CDBChatMsgMgn::GetUnreadAtMeOrderCount(CADOConn *pADOConn, const CString &sCurrentUserID, const CString &sCurOrder, BOOL *pbCurOrderExist)
{
   if (!pADOConn)
      return 0;

   std::set<CString> setOrders;
   if (!GetUnreadAtMeOrders(pADOConn, sCurrentUserID, &setOrders))
      return 0;

   if (pbCurOrderExist && !sCurOrder.IsEmpty())
   {
      if (setOrders.count(sCurOrder) > 0)
      {
         *pbCurOrderExist = TRUE;
      }
      else
      {
         *pbCurOrderExist = FALSE;
      }
   }

   return setOrders.size();
}