#include "StdAfx.h"
#include "FileTransferIO.h"
#include "LoginDlg.h"
#include "QlFileTransferEx.h"
#include "ADOConnEx.h"
#include "ThreadFileTrans.h"
#include "tinyxml/tinyxml.h"
#include "CDBPtLogInfo_new.h"
#include "QL_HttpClient.h"

#include "FileTransData.h"
#include "FT_params.h"
#include <stdarg.h>
#include "FT_Option.h"
#include "FileTrans_Handle.h"



FILETRANS * filetrans_easy_init(const CString & strWorkPath,S_FileTrans_LoginType nLoginType)
{
   struct FileTrans_easy *pData = new FileTrans_easy;
   pData->nLoginType = nLoginType;

   //��ȡ��·���µ����������Ϣ
   CFT_params oParams;
   oParams.InitDataParams(pData,strWorkPath);

   return pData;
}

FILETRANS_EXTERN FILETRANS * filetrans_easy_init2(const CString & strWorkPath,const CString & strIP,const CString & strName,const CString & strPwd,S_FileTrans_LoginType nLoginType /*= En_Login_User*/)
{
   struct FileTrans_easy *pData = filetrans_easy_init(strWorkPath,nLoginType);

   pData->strDBIP          = _T("");//���ݿ��ַ+�˿�
   pData->strDBName        = _T("");//���ݿ�����
   pData->strDBID          = _T("");//���ݿ������˻���
   pData->strDBPassword    = _T("");//���ݿ���������

   pData->strLocalTransIP  = _T("");//���ش����ַ
   pData->strFTPFarTrans   = strIP;//FTP��ַ
   pData->strFTPFarlName   = strName;//FTP��¼��
   pData->strFTPFarPwd     = strPwd;//FTP��¼����
   pData->bHttpMode        = FALSE;

   pData->strUserID        = _T("");
   pData->strUserPassword  = _T("");

   return pData;
}

FILETRANS_EXTERN FileTransCode filetrans_easy_setopt(FILETRANS * pFileTrans,FileTransOption option,...)
{
   va_list arg;
   FileTransCode result;

   if(!pFileTrans)
      return FILETRANS_WRONG_BAD_FUNCTION_ARGUMENT;

   va_start(arg, option);

   result = vsetopt(pFileTrans, option, arg);

   va_end(arg);
   return result;
}

FILETRANS_EXTERN FileTransCode filetrans_easy_getinfo(FILETRANS *pFileTrans, FILETRANSINFO info, ...)
{
   FileTransCode result = FILETRANS_OK;

   va_list arg;
   void *paramp;

   va_start(arg, info);
   paramp = va_arg(arg, void *);

   result = GetInfo(pFileTrans, info, paramp);

   va_end(arg);

   return result;
}

FILETRANS_EXTERN FileTransCode filetrans_easy_perform(FILETRANS *pData)
{
   //ִ�в���
   FileTransCode result = FILETRANS_OK;

   if(!pData)
      return FILETRANS_WRONG_BAD_FUNCTION_ARGUMENT;

   if (pData->nLoginType != En_Login_Null)
   {//��֤��¼
      result = CKDBLogin(pData);
      if( FILETRANS_OK != result)
      {
         //��¼ʧ�ܾͷ���
         return result;
      }
   }
   
   //ʱ����֤

   //������Ϊ�ַ�����

   result = DistributionAction(pData);

   //������Ϊƴ�Ӳ���·��
   //���ɲ�������
   //���������߳�
   //��ջ�������
   return result;
}

FILETRANS_EXTERN void FileTrans_easy_cleanup(FILETRANS *pFileTrans)
{
   if (NULL != pFileTrans)
   {
      delete pFileTrans;
   }
}

FILETRANS_EXTERN void FileTrans_easy_reset(FILETRANS *pFileTrans)
{
   CFT_params oParams;
   oParams.InitDataParams(pFileTrans,pFileTrans->strWorkPath);
}

FILETRANS_EXTERN LPCTSTR filetrans_easy_geterror(FileTransCode nErrorCode)
{
   CString strRet;
   switch (nErrorCode)
   {
   case FILETRANS_UNDEFINED                  :strRet = _T("δ�������")              ;break;
   case FILETRANS_OK                         :strRet = _T("ִ�н���")                ;break;
   case FILETRANS_UPLOADZERO                 :strRet = _T("�ϴ��б�Ϊ��")            ;break;
   case FILETRANS_DOWNLOADZERO               :strRet = _T("�����б�Ϊ��")            ;break;
   case FILETRANS_DELZERO                    :strRet = _T("ɾ���б�Ϊ��")            ;break;
   case FILETRANS_COPYZERO                   :strRet = _T("�����б�Ϊ��")            ;break;
   case FILETRANS_ORDEREMPTY                 :strRet = _T("�������ǿյ�")            ;break;
   case FILETRANS_WRONG_DWONPATH             :strRet = _T("����·�����ô���")        ;break;
   case FILETRANS_WRONG_CONFIG               :strRet = _T("������Ϣ���ô���")        ;break;
   case FILETRANS_WRONG_INIMSG               :strRet = _T("��ȡ�����ļ���Ϣʧ��")    ;break;
   case FILETRANS_WRONG_DBMSG                :strRet = _T("���ݿ�������Ϣ�쳣")      ;break;
   case FILETRANS_WRONG_LOGIN                :strRet = _T("�ĵ������¼ʧ��")        ;break;
   case FILETRANS_WRONG_NETSTATE             :strRet = _T("�����쳣")                ;break;
   case FILETRANS_WRONG_FTPCANTOPEN          :strRet = _T("ftp����������ʧ��")       ;break;
   case FILETRANS_WRONG_XMLERROR             :strRet = _T("xml����")                 ;break;
   case FILETRANS_WRONG_SQLEXECUERR          :strRet = _T("���ݿ����ִ��ʧ��")      ;break;
   case FILETRANS_WRONG_UNSUPPORT            :strRet = _T("��֧�ֵĹ���")            ;break;
   case FILETRANS_WRONG_NOPERMISSION         :strRet = _T("�û�û��Ȩ�޽��д˴β���");break;
   case FILETRANS_WRONG_UNDEFACTION          :strRet = _T("δ����Ĳ���")            ;break;
   case FILETRANS_WRONG_MEMORYERROR          :strRet = _T("�ڴ����")                ;break;
   case FILETRANS_WRONG_DISCONNECTED         :strRet = _T("����������ʧ��")          ;break;
   case FILETRANS_WRONG_BAD_FUNCTION_ARGUMENT:strRet = _T("����Ĳ���")              ;break;
   case FILETRANS_WRONG_UNKNOWN_OPTION       :strRet = _T("δ֪�Ĳ���")              ;break;
   default:strRet = _T("δ֪������");break;
   }
   return strRet;
}

FILETRANS_EXTERN void LogFileToCloud(LPCTSTR sLogFilePath,LPCTSTR sTypeName)
{
   CString strLogFilePath(sLogFilePath),strTypeName(sTypeName);
   //����־�ļ��ϴ����ƶ�  Ҫ�� TypeName����Ϊ��

   if ((TypeNameLength < strTypeName.GetLength() - 1) || 0 == strTypeName.GetLength())
   {
      strTypeName = _T("UnKnown");
   }

   CString strFileName = PathFindFileName(strLogFilePath);

   CString strEx = PathFindExtension(strLogFilePath);
   CString strCacheFile = strLogFilePath.Left(strLogFilePath.GetLength() - strEx.GetLength() );
   strCacheFile += _T(".QlCache");

   CopyFile(strLogFilePath,strCacheFile,TRUE);
   DeleteFile(strLogFilePath);

   CloudLogMsg * pCloudLogMsg = NULL;
   pCloudLogMsg = new CloudLogMsg;
   if (NULL != pCloudLogMsg)
   {
      memset(pCloudLogMsg,0,sizeof(CloudLogMsg));
   }

   memset(pCloudLogMsg->strLocalPath,0,sizeof(pCloudLogMsg->strLocalPath));
   memset(pCloudLogMsg->strTypeName,0,sizeof(pCloudLogMsg->strTypeName));
   memset(pCloudLogMsg->strSourceFileName,0,sizeof(pCloudLogMsg->strSourceFileName));

#ifdef _UNICODE
   QLCOMAPI.WCharToMByte(strCacheFile,pCloudLogMsg->strLocalPath,sizeof(pCloudLogMsg->strLocalPath)/sizeof(pCloudLogMsg->strLocalPath[0]));
   QLCOMAPI.WCharToMByte(strTypeName,pCloudLogMsg->strTypeName,sizeof(pCloudLogMsg->strTypeName)/sizeof(pCloudLogMsg->strTypeName[0]));
   QLCOMAPI.WCharToMByte(strFileName,pCloudLogMsg->strSourceFileName,sizeof(pCloudLogMsg->strSourceFileName)/sizeof(pCloudLogMsg->strSourceFileName[0]));
#else
   strncpy_s(pCloudLogMsg->strLocalPath,(LPSTR)(LPCTSTR)strCacheFile, sizeof(pCloudLogMsg->strLocalPath) - 1);
   strncpy_s(pCloudLogMsg->strTypeName,(LPSTR)(LPCTSTR)strTypeName, sizeof(pCloudLogMsg->strTypeName) - 1);
   strncpy_s(pCloudLogMsg->strSourceFileName,(LPSTR)(LPCTSTR)strFileName, sizeof(pCloudLogMsg->strSourceFileName) - 1);
#endif // _UNICODE
   HANDLE handle;
   handle = ::CreateThread(NULL, 0, ThreadLogFileToCloud, (LPVOID)pCloudLogMsg, 0, NULL);
   CloseHandle(handle);
}

void FT_ShowMarquee()
{
   S_Loading *pLoadingMsg = NULL;
   pLoadingMsg = new S_Loading;

   pLoadingMsg->nLoadingType = En_Loading_Marquee;

   HANDLE hThrLoading = ::CreateThread(NULL,0,
      (LPTHREAD_START_ROUTINE)ThreadShowLoading,(LPVOID)pLoadingMsg,0,NULL);
}

void FT_HideMarquee()
{
   AFX_MANAGE_STATE(AfxGetStaticModuleState());
   HideMarquee();
}





