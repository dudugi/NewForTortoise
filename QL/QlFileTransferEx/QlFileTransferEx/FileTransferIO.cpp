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

   //读取该路径下的相关配置信息
   CFT_params oParams;
   oParams.InitDataParams(pData,strWorkPath);

   return pData;
}

FILETRANS_EXTERN FILETRANS * filetrans_easy_init2(const CString & strWorkPath,const CString & strIP,const CString & strName,const CString & strPwd,S_FileTrans_LoginType nLoginType /*= En_Login_User*/)
{
   struct FileTrans_easy *pData = filetrans_easy_init(strWorkPath,nLoginType);

   pData->strDBIP          = _T("");//数据库地址+端口
   pData->strDBName        = _T("");//数据库名称
   pData->strDBID          = _T("");//数据库连接账户名
   pData->strDBPassword    = _T("");//数据库连接密码

   pData->strLocalTransIP  = _T("");//本地传输地址
   pData->strFTPFarTrans   = strIP;//FTP地址
   pData->strFTPFarlName   = strName;//FTP登录名
   pData->strFTPFarPwd     = strPwd;//FTP登录密码
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
   //执行操作
   FileTransCode result = FILETRANS_OK;

   if(!pData)
      return FILETRANS_WRONG_BAD_FUNCTION_ARGUMENT;

   if (pData->nLoginType != En_Login_Null)
   {//验证登录
      result = CKDBLogin(pData);
      if( FILETRANS_OK != result)
      {
         //登录失败就返回
         return result;
      }
   }
   
   //时间验证

   //根据行为分发操作

   result = DistributionAction(pData);

   //根据行为拼接操作路径
   //生成操作数据
   //创建操作线程
   //清空缓存链表
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
   case FILETRANS_UNDEFINED                  :strRet = _T("未定义错误")              ;break;
   case FILETRANS_OK                         :strRet = _T("执行结束")                ;break;
   case FILETRANS_UPLOADZERO                 :strRet = _T("上传列表为空")            ;break;
   case FILETRANS_DOWNLOADZERO               :strRet = _T("下载列表为空")            ;break;
   case FILETRANS_DELZERO                    :strRet = _T("删除列表为空")            ;break;
   case FILETRANS_COPYZERO                   :strRet = _T("拷贝列表为空")            ;break;
   case FILETRANS_ORDEREMPTY                 :strRet = _T("订单号是空的")            ;break;
   case FILETRANS_WRONG_DWONPATH             :strRet = _T("下载路径设置错误")        ;break;
   case FILETRANS_WRONG_CONFIG               :strRet = _T("配置信息设置错误")        ;break;
   case FILETRANS_WRONG_INIMSG               :strRet = _T("获取配置文件信息失败")    ;break;
   case FILETRANS_WRONG_DBMSG                :strRet = _T("数据库配置信息异常")      ;break;
   case FILETRANS_WRONG_LOGIN                :strRet = _T("文档管理登录失败")        ;break;
   case FILETRANS_WRONG_NETSTATE             :strRet = _T("网络异常")                ;break;
   case FILETRANS_WRONG_FTPCANTOPEN          :strRet = _T("ftp服务器连接失败")       ;break;
   case FILETRANS_WRONG_XMLERROR             :strRet = _T("xml错误")                 ;break;
   case FILETRANS_WRONG_SQLEXECUERR          :strRet = _T("数据库语句执行失败")      ;break;
   case FILETRANS_WRONG_UNSUPPORT            :strRet = _T("不支持的功能")            ;break;
   case FILETRANS_WRONG_NOPERMISSION         :strRet = _T("用户没有权限进行此次操作");break;
   case FILETRANS_WRONG_UNDEFACTION          :strRet = _T("未定义的操作")            ;break;
   case FILETRANS_WRONG_MEMORYERROR          :strRet = _T("内存错误")                ;break;
   case FILETRANS_WRONG_DISCONNECTED         :strRet = _T("与主机连接失败")          ;break;
   case FILETRANS_WRONG_BAD_FUNCTION_ARGUMENT:strRet = _T("错误的参数")              ;break;
   case FILETRANS_WRONG_UNKNOWN_OPTION       :strRet = _T("未知的参数")              ;break;
   default:strRet = _T("未知错误码");break;
   }
   return strRet;
}

FILETRANS_EXTERN void LogFileToCloud(LPCTSTR sLogFilePath,LPCTSTR sTypeName)
{
   CString strLogFilePath(sLogFilePath),strTypeName(sTypeName);
   //将日志文件上传到云端  要求 TypeName不能为空

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





