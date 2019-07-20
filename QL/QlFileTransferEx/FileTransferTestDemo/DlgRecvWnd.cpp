// DlgRecvWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "FileTransferTestDemo.h"
#include "DlgRecvWnd.h"
#include "afxdialogex.h"


// CDlgRecvWnd 对话框

IMPLEMENT_DYNAMIC(CDlgRecvWnd, CDialogEx)

CDlgRecvWnd::CDlgRecvWnd(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgRecvWnd::IDD, pParent)
{

}

CDlgRecvWnd::~CDlgRecvWnd()
{
}

void CDlgRecvWnd::ClearLog()
{
   auto pListBox = (CListBox*)GetDlgItem(IDC_LIST_RECVLOG);
   if (pListBox && IsWindow(pListBox->GetSafeHwnd()))
   {
      pListBox->ResetContent();
   }
}

void CDlgRecvWnd::ResizeCtrl()
{
   CRect rcClient;
   GetClientRect(rcClient);

   auto pWnd = GetDlgItem(IDC_LIST_RECVLOG);
   if (NULL != pWnd && IsWindow(pWnd->GetSafeHwnd()))
   {
      //ScreenToClient(rcClient);
      pWnd->MoveWindow(rcClient);
   }
}

void CDlgRecvWnd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgRecvWnd, CDialogEx)
   ON_WM_SIZE()
   ON_MESSAGE(WM_QL_FTP_GETLIST, &CDlgRecvWnd::OnQlFtpGetlist)
   ON_MESSAGE(WM_QL_FTP_UPLOAD, &CDlgRecvWnd::OnQlFtpUpload)
   ON_MESSAGE(WM_QL_FTP_PROGRESS, &CDlgRecvWnd::OnQlFtpProgress)
   ON_MESSAGE(WM_QL_FTP_DEL, &CDlgRecvWnd::OnQlFtpDel)
   ON_MESSAGE(WM_QL_FTP_DOWNLOAD, &CDlgRecvWnd::OnQlFtpDownload)
   ON_MESSAGE(WM_QL_FTP_MKDIR, &CDlgRecvWnd::OnQlFtpMkdir)
   ON_MESSAGE(WM_QL_FTP_DELDIR, &CDlgRecvWnd::OnQlFtpDeldir)
   ON_MESSAGE(WM_QL_FTP_DOWNDIR, &CDlgRecvWnd::OnQlFtpDowndir)
   ON_MESSAGE(WM_QL_FTP_DOWNBYEX, &CDlgRecvWnd::OnQlFtpDownbyex)
   ON_MESSAGE(WM_QL_FTP_DOWNDIRMSG, &CDlgRecvWnd::OnQlFtpDowndirmsg)
   ON_MESSAGE(WM_QL_FTP_DOWNBYEXMSG, &CDlgRecvWnd::OnQlFtpDownbyexmsg)
   ON_MESSAGE(WM_QL_FTP_BACKUPFILE, &CDlgRecvWnd::OnQlFtpBackupfile)
   ON_MESSAGE(WM_QL_FTP_BACKUPFILEMSG, &CDlgRecvWnd::OnQlFtpBackupfilemsg)
   ON_MESSAGE(WM_QL_FTP_COPY_VERSION_TO_NEW, &CDlgRecvWnd::OnQlFtpCopyVersionToNew)
END_MESSAGE_MAP()


// CDlgRecvWnd 消息处理程序

BOOL CDlgRecvWnd::OnInitDialog()
{
   CDialogEx::OnInitDialog();

   ResizeCtrl();

   return TRUE;  // return TRUE unless you set the focus to a control
   // 异常: OCX 属性页应返回 FALSE
}

void CDlgRecvWnd::OnSize(UINT nType, int cx, int cy)
{
   CDialogEx::OnSize(nType, cx, cy);

   ResizeCtrl();
   
}

void CDlgRecvWnd::AddMsgToLog(const CString & strLog)
{
   auto pListBox = (CListBox*)GetDlgItem(IDC_LIST_RECVLOG);
   int nSel = pListBox->AddString(strLog);
   pListBox->SetCurSel(nSel);
}

void CDlgRecvWnd::LogActionResult(int nAction)
{
   CString strLog;
   switch(nAction)
   {
   case FTP_ACTION_START       :
      strLog = _T("FTP_ACTION_START");
      break;
   case FTP_ACTION_SUC         :
      strLog = _T("FTP_ACTION_SUC");
      break;
   case FTP_ACTION_FAIL        :
      strLog = _T("FTP_ACTION_FAIL");
      break;
   case FTP_ACTION_OPENFAIL    :
      strLog = _T("FTP_ACTION_OPENFAIL");
      break;
   case FTP_ACTION_NOFILE      :
      strLog = _T("FTP_ACTION_NOFILE");
      break;
   case FTP_ACTION_DISCONNECTED:
      strLog = _T("FTP_ACTION_DISCONNECTED");
      break;
   }

   strLog = _T("Message Action : ") + strLog;
   AddMsgToLog(strLog);
}

LRESULT CDlgRecvWnd::OnQlFtpGetlist(WPARAM wParam, LPARAM lParam)
{
   AddMsgToLog(_T("Message: WM_QL_FTP_GETLIST"));
   char *szpath = (char *)wParam;
   LpMsg_QLtransEx *pLpMsg = (LpMsg_QLtransEx *)lParam;
   int nAction = pLpMsg->nAction;//行为的返回值
   int nNum = pLpMsg->nNum;
   FileMsg *pItem = (FileMsg *)pLpMsg->pVoid;
   int nFlag = pLpMsg->nFlag;//返回发送的标识
   static int s_nAlreadGetCount = 0;
   
   if (FTP_ACTION_SUC == (int)nAction)
   {
      LogActionResult(nAction);
      int nIndex = 0;

      AddMsgToLog(_T("Files Info:"));
      for (nIndex = 0;nIndex < nNum;nIndex++)
      {
         CString strFileName(pItem[nIndex].filename);
         if (strFileName == _T(".") || strFileName == _T(".."))
         {
            continue;
         }

         CString strValue;
         AddMsgToLog(_T("FileName:") + CString(pItem[nIndex].filename));
         strValue.Format(_T("FileSize:%u"),pItem[nIndex].nFileSize);
         AddMsgToLog(strValue);
         strValue = pItem[nIndex].nFileType == FTP_TYPE_FILE ? _T("File") : _T("Dir");
         AddMsgToLog(strValue);
         strValue = _T("time:") + pItem[nIndex].tTime.Format(_T("%Y-%m-%d %H:%M:%S"));
         AddMsgToLog(strValue);
      }
   }
   else 
   {
      LogActionResult(nAction);
   }

   return 0;
}

LRESULT CDlgRecvWnd::OnQlFtpUpload(WPARAM wParam, LPARAM lParam)
{
   char *szLocal = (char *)wParam;
   LpMsg_QLtransEx *pLpMsg = (LpMsg_QLtransEx *)lParam;
   int nAction = pLpMsg->nAction;//行为的返回值
   int nFlag = pLpMsg->nFlag;//返回发送的标识
   UINT64 nSize = pLpMsg->nFileSize_Upload;

   CString strLocal(szLocal);
   LogActionResult(nAction);

   return 0;
}

LRESULT CDlgRecvWnd::OnQlFtpProgress(WPARAM wParam, LPARAM lParam)
{
   HWND hParent = GetParent()->GetSafeHwnd();

   ::SendMessage(hParent,WM_QL_FTP_PROGRESS,wParam,lParam);

   return 0;
}

LRESULT CDlgRecvWnd::OnQlFtpDel(WPARAM wParam, LPARAM lParam)
{
   char *szFarPath = (char *)wParam;
   LpMsg_QLtransEx *pLpMsg = (LpMsg_QLtransEx *)lParam;
   int nAction = pLpMsg->nAction;//行为的返回值
   int nFlag = pLpMsg->nFlag;//返回发送的标识
   UINT64 nSize = pLpMsg->nFileSize_Upload;
   LogActionResult(nAction);
   return 0;
}

LRESULT CDlgRecvWnd::OnQlFtpDownload(WPARAM wParam, LPARAM lParam)
{
   char *szLocal = (char *)wParam;
   LpMsg_QLtransEx *pLpMsg = (LpMsg_QLtransEx *)lParam;
   int nAction = pLpMsg->nAction;//行为的返回值
   int nFlagLparam = pLpMsg->nFlag;//返回发送的标识

   CString strLocal(szLocal);

   LogActionResult(nAction);

   if (FTP_ACTION_START == nAction)
   {
      HWND hParent = GetParent()->GetSafeHwnd();

      ::SendMessage(hParent,WM_QL_FTP_PROGRESSINFO,0,0);
   }

   return 0;
}

LRESULT CDlgRecvWnd::OnQlFtpMkdir(WPARAM wParam, LPARAM lParam)
{
   return 0;
}

LRESULT CDlgRecvWnd::OnQlFtpDeldir(WPARAM wParam, LPARAM lParam)
{
   char *szOrder = (char *)wParam;
   LpMsg_QLtransEx *pLpMsg = (LpMsg_QLtransEx *)lParam;
   int nAction = pLpMsg->nAction;//行为的返回值
   int nFlag = pLpMsg->nFlag;//返回发送的标识

   LogActionResult(nAction);

   return 0;
}

LRESULT CDlgRecvWnd::OnQlFtpDowndir(WPARAM wParam, LPARAM lParam)
{
   char *szLocal = (char *)wParam;
   LpMsg_QLtransEx *pLpMsg = (LpMsg_QLtransEx *)lParam;
   int nAction = pLpMsg->nAction;//行为的返回值
   int nFlagLparam = pLpMsg->nFlag;//返回发送的标识

   CString strLocal(szLocal);
   LogActionResult(nAction);

   if (FTP_ACTION_START == nAction)
   {
      HWND hParent = GetParent()->GetSafeHwnd();

      ::SendMessage(hParent,WM_QL_FTP_PROGRESSINFO,0,0);
   }

   return 0;
}

LRESULT CDlgRecvWnd::OnQlFtpDownbyex(WPARAM wParam, LPARAM lParam)
{
   char *szLocal = (char *)wParam;
   LpMsg_QLtransEx *pLpMsg = (LpMsg_QLtransEx *)lParam;
   int nAction = pLpMsg->nAction;//行为的返回值
   int nFlagLparam = pLpMsg->nFlag;//返回发送的标识

   CString strLocal(szLocal);
   AddMsgToLog(_T("OnQlFtpDownbyex:"));
   LogActionResult(nAction);

   if (FTP_ACTION_START == nAction)
   {
      HWND hParent = GetParent()->GetSafeHwnd();

      ::SendMessage(hParent,WM_QL_FTP_PROGRESSINFO,0,0);
   }
   return 0;
}

LRESULT CDlgRecvWnd::OnQlFtpDowndirmsg(WPARAM wParam, LPARAM lParam)
{
   char *szLocal = (char *)wParam;
   LpMsg_QLtransEx *pLpMsg = (LpMsg_QLtransEx *)lParam;
   int nAction = pLpMsg->nAction;//行为的返回值
   int nFlagLparam = pLpMsg->nFlag;//返回发送的标识

   CString strLocal(szLocal);
   LogActionResult(nAction);
   AddMsgToLog(_T("OnQlFtpDowndirmsg :") + strLocal);

   return 0;
}

LRESULT CDlgRecvWnd::OnQlFtpDownbyexmsg(WPARAM wParam, LPARAM lParam)
{
   char *szLocal = (char *)wParam;
   LpMsg_QLtransEx *pLpMsg = (LpMsg_QLtransEx *)lParam;
   int nAction = pLpMsg->nAction;//行为的返回值
   int nFlagLparam = pLpMsg->nFlag;//返回发送的标识

   CString strLocal(szLocal);
   AddMsgToLog(_T("OnQlFtpDownbyexmsg:"));
   LogActionResult(nAction);


   return 0;
}

LRESULT CDlgRecvWnd::OnQlFtpBackupfile(WPARAM wParam, LPARAM lParam)
{
   char *szLocal = (char *)wParam;
   LpMsg_QLtransEx *pLpMsg = (LpMsg_QLtransEx *)lParam;
   int nAction = pLpMsg->nAction;//行为的返回值
   int nFlagLparam = pLpMsg->nFlag;//返回发送的标识

   CString strLocal(szLocal);
   AddMsgToLog(_T("OnQlFtpBackupfile:"));
   LogActionResult(nAction);
   return 0;
}

LRESULT CDlgRecvWnd::OnQlFtpBackupfilemsg(WPARAM wParam, LPARAM lParam)
{
   char *szLocal = (char *)wParam;
   LpMsg_QLtransEx *pLpMsg = (LpMsg_QLtransEx *)lParam;
   int nAction = pLpMsg->nAction;//行为的返回值
   int nFlagLparam = pLpMsg->nFlag;//返回发送的标识

   CString strLocal(szLocal);
   AddMsgToLog(_T("OnQlFtpBackupfilemsg:"));
   LogActionResult(nAction);
   return 0;
}

LRESULT CDlgRecvWnd::OnQlFtpCopyVersionToNew(WPARAM wParam, LPARAM lParam)
{
   char *szLocal = (char *)wParam;
   LpMsg_QLtransEx *pLpMsg = (LpMsg_QLtransEx *)lParam;
   int nAction = pLpMsg->nAction;//行为的返回值
   int nFlagLparam = pLpMsg->nFlag;//返回发送的标识

   CString strLocal(szLocal);
   AddMsgToLog(_T("OnQlFtpCopyVersionToNew:"));
   LogActionResult(nAction);
   return 0;
}
