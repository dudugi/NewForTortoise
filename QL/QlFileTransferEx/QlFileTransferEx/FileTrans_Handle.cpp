#include "stdafx.h"
#include "FileTrans_Handle.h"
#include "QlFileTransferEx.h"
#include "FileTransData.h"
#include "Base64Code.h"
#include "FT_String.inl"
#include "ThreadFileTrans.h"
#include "QL_HttpClient.h"


FileTransCode CKDBLogin(FILETRANS *pData)
{
   if (!theApp.CheckNetState())
   {
      return FILETRANS_WRONG_NETSTATE;
   }

   //数据库IP是空的 或者 用户名是空的 或者 （密码为空 且登录方式为用户）
   if (pData->strDBIP.IsEmpty() || pData->strUserID.IsEmpty() || (pData->strUserPassword.IsEmpty() && pData->nLoginType == En_Login_User))
   {
      AfxMessageBox(_T("请在登录成功后重复本次操作！"));

      PopLogin(pData->strWorkPath,pData->nLoginType);
      return FILETRANS_WRONG_CONFIG;
   }

   //数据库名为空 或 IP为空 或 数据库连接密码为空 或数据库连接账户为空 则提示登录
   if (pData->strDBName.IsEmpty() || pData->strDBIP.IsEmpty() || pData->strDBPassword.IsEmpty() || pData->strDBID.IsEmpty())
   {
      //数据库信息异常
      AfxMessageBox(_T("请在登录成功后重复本次操作！"));

      PopLogin(pData->strWorkPath,pData->nLoginType);
      return FILETRANS_WRONG_DBMSG;
   }

   if (!Login(pData))
   {
      AfxMessageBox(_T("请在登录成功后重复本次操作！"));

     PopLogin(pData->strWorkPath,pData->nLoginType);

      return FILETRANS_WRONG_LOGIN;
   }

   return FILETRANS_OK;
}

CString GetSqlConnectStr(FILETRANS *pData)
{
   CString strRet = _T("");
   CString strProvide = _T("SQL Server");//SQL2008
   strRet.Format(_T("Driver={%s};Server=%s;Database=%s;UID=%s;PWD=%s")
      ,strProvide
      ,pData->strDBIP
      ,pData->strDBName
      ,pData->strDBID
      ,pData->strDBPassword
      );

   return strRet;
}

BOOL Login(FILETRANS *pData)
{
   //连接数据库 并检查登录
   CADOConnEx ADOConn;

   CString strConnectSql = GetSqlConnectStr(pData);

   ADOConn.SetConnecetSqlStr(strConnectSql);

   CString strSQL = _T("");
   switch (pData->nLoginType)
   {
   case En_Login_User:
      {
         CBase64Code Base64Code;
         strSQL.Format(_T("select %s from %s where %s='%s'and %s='%s'"),DBPerson_key_OutFlag,DB_TABLE_PERSON,DBPerson_key_UserID,pData->strUserID,DBPerson_key_Pwd,Base64Code.base64Encode(pData->strUserPassword));
      }
      break;
   case En_Login_Custom:
      {
         strSQL.Format(_T("select * from %s where %s='%s'and %s='%s'"),DB_TABLE_CUSTOM,DBCustomer_key_Code,pData->strUserID,DBCustomer_key_Pwd,pData->strUserPassword);
      }
      break;
   }

   auto Rret = ADOConn.GetRecordSet(strSQL);
   if (!ADOConn.adoEOF())//存在此用户名
   {
      if (En_Login_User == pData->nLoginType)
      {
         int nOutFlag =  _ttoi(ADOConn.GetValueString(DBPerson_key_OutFlag));
         if (0 == pData->strUserID.CompareNoCase(_T("admin")))
         {
            nOutFlag = 0;
         }

         if (nOutFlag == 1)
         {
            return FALSE;
         }
      }

      return TRUE;
   }

   return FALSE;
}

BOOL PopLogin(const CString & strWorkPath,int nLoginType)
{
   theApp.m_strKdsPath = strWorkPath;
   theApp.m_strSvrPath = theApp.m_strKdsPath + STR_PATH_INI_CONFIGSVR;
   theApp.m_strMgnPath = theApp.m_strKdsPath + STR_PATH_INI_FILEMGN;

   AFX_MANAGE_STATE(AfxGetStaticModuleState());
   CLoginDlg dlg(nLoginType);
   if (IDOK == dlg.DoModal())
   {
      return TRUE;
   }
   else
   {
      return FALSE;
   }//2017/03/29_end
}

FileTransCode GetActionPath(FILETRANS * pData,CString & strPath)
{
   return GetActionPath(pData->map_Key_Path,pData->strAction_ParamKey,pData->strOrderNo,pData->strSize,pData->nVersion,strPath);
}

FileTransCode GetActionPath(/*const*/ map<CString,S_PathParam> & map_KeyPath, const CString & strActionParam
   ,const CString & strOrderNo, const CString & strSize,
   int nVersion,CString & strPath)
{
   strPath = _T("");
   //如果没有key 则提示相关配置没有并返回错误
   if ( 0 >= map_KeyPath.count(strActionParam))
   {
      return FILETRANS_WRONG_BAD_FUNCTION_ARGUMENT;
   }

   auto s_Key = map_KeyPath[strActionParam];
   CString strConfigPath = (s_Key.m_strPath);//获取配置文件对应的路径
   //因为是多次替换 避免替换后会出现相关关键词 因此不用replace

   CString strTmpKey;
   //遍历所有的字符 
   int nCount = strConfigPath.GetLength();
   for (int nIndex = 0;nIndex < nCount;++nIndex)
   {
      //依次取出每一个字符
      auto cValue = strConfigPath.GetAt(nIndex);
      //判断缓存的key是否为空
      BOOL bTmpKeyEmpty = strTmpKey.IsEmpty();
      if (!bTmpKeyEmpty || cValue == '$')//缓存的key不是空的 或者当前字符为$
      {//如果缓存的key不是空的
         if (cValue == '$' && !bTmpKeyEmpty)//当前值为$ 且缓存的key不是空的
         {
            strTmpKey.AppendChar(cValue);//追加$补全key
            BOOL bExistInKey = TRUE;
            //检测相关key
            if (strTmpKey == _T("$OrderNo$"))
            {
               strPath.Append(strOrderNo);
            }
            else if (strTmpKey == _T("$Size$"))
            {
               strPath.Append(strSize);
            }
            else if (strTmpKey == _T("$Version$"))
            {
               if (-1 != nVersion)
               {
                  strPath.AppendFormat(_T("%d"),nVersion);
               }
            }
            else
            {//如果以上都不是 则追加$符号到tmpkey里面作为下一个的起始 避免出现 $...$OrderNo$... 的情况
               strPath.Append(strTmpKey.Left(strTmpKey.GetLength() - 1));
               strTmpKey = _T("$");
               bExistInKey = FALSE;
            }
            if (bExistInKey)
            {//如果相关key存在 则清空对应的信息 并进行替换
               strTmpKey = _T("");
            }

         }
         else
         {//如果不是$符号 则向缓存的key后面追加
            strTmpKey.AppendChar(cValue);
         }
      }
      else
      {
         strPath.AppendChar(cValue);
      }
   }
   if (!strTmpKey.IsEmpty())
   {
      strPath.Append(strTmpKey);
   }

   if (!strPath.IsEmpty())
   {
      if (strPath.GetAt(strPath.GetLength()) != '\\')
      {
         strPath.AppendChar('\\');
      }
   }

   //将 '/' 转为 '\\'
   strPath.Replace('/','\\');
   while (-1 != strPath.Find( _T("\\\\")))
   {
      strPath.Replace(_T("\\\\"),_T("\\"));
   }

   return FILETRANS_OK;
}

FileTransCode GetInfo(FILETRANS * pData,FILETRANSINFO info,void * pParam)
{
   FileTransCode result = FILETRANS_OK;
   switch (info)
   {
   case FILETRANSINFO_USER_ID:
      result = GetInfo_UserID(pData,pParam);
      break;
   case FILETRANSINFO_USER_NAME:
      result = GetInfo_UserName(pData,pParam);
      break;
   case FILETRANSINFO_DLL_VERSION:
      result = GetInfo_DllVersion(pData,pParam);
      break;
   case FILETRANSINFO_HTTP_MODE:
      result = GetInfo_HttpMode(pData,pParam);
      break;
   case FILETRANSINFO_ORDER_EXISTS:
      result = GetInfo_OrderExists(pData,pParam);
      break;
   case FILETRANSINFO_CAN_LOGIN:
      result = GetInfo_CanLogin(pData,pParam);
      break;
   case FILETRANSINFO_SAMPLE_ORDER:
      result = GetInfo_SampleOrder(pData,pParam);
      break;
   case FILETRANSINFO_FILE_EXISTS:
      result = GetInfo_FileExists(pData,pParam);
      break;
   case FILETRANSINFO_POPUPLOGIN:
      result = GetInfo_PopupLogin(pData,pParam);
         break;
   default:
      result = FILETRANS_WRONG_UNKNOWN_OPTION;
      break;
   }

   return result;
}

FileTransCode DistributionAction(FILETRANS * pData)
{
   FileTransCode result = FILETRANS_OK;
   switch(pData->nAction)
   {
   case en_Action_Upload:
      result = HandleFunction_Upload(pData);
      break;
   case en_Action_Down:
      result = HandleFunction_Download(pData);
      break;
   case en_Action_DownDir:
      result = HandleFunction_DownDir(pData);
      break;
   case en_Action_DownDirMsg:
      result = HandleFunction_DownDirMsg(pData);
      break;
   case en_Action_DownByEx:
      result = HandleFunction_DownByEx(pData);
      break;
   case en_Action_GetList:
      result = HandleFunction_GetList(pData);
      break;
   case en_Action_GetListEx:
      result = HandleFunction_GetListEx(pData);
      break;
   case en_Action_Delete:
      result = HandleFunction_Delete(pData);
      break;
   case en_Action_DeleteDir:
      result = HandleFunction_DeleteDir(pData);
      break;
   case en_Action_Copy :
      result = HandleFunction_Copy(pData);
      break;
   case en_Action_BackupFile_Move:
      result = HandleFunction_BackupFile_Move(pData);
      break;
   case en_Action_BackupFile_Copy:
      result = HandleFunction_BackupFile_Copy(pData);
      break;
   case en_Action_CopyVersionToCurVersion:
      result = HandleFunction_CopyVersionToCurVersion(pData);
      break;
   case en_Action_SetSampleOrder:
      result = HandleFunction_SetSampleOrder(pData);
      break;
   default:
      result = FILETRANS_WRONG_BAD_FUNCTION_ARGUMENT;
      break;
   }
   return result;
}

TransferMsg * PrepareTransferMsg(FILETRANS * pData)
{
   TransferMsg *pTransferMsg = NULL;
   pTransferMsg = new TransferMsg;
   pTransferMsg->hWnd = pData->hProcessWnd;
   pTransferMsg->nSpecFlag = pData->nFlag;
   pTransferMsg->nLoginType = pData->nLoginType;
   pTransferMsg->bUseHttp = pData->bHttpMode;

   auto s_Key = pData->map_Key_Path[pData->strAction_ParamKey];
   pTransferMsg->bZip = s_Key.m_bZip;
   pTransferMsg->bDelZip = s_Key.m_bDelZip;
   pTransferMsg->bUnZipFailRename = s_Key.m_bUnZipFailRename;

   memset(pTransferMsg->strIP, 0, sizeof(pTransferMsg->strIP));
   memset(pTransferMsg->strName, 0, sizeof(pTransferMsg->strName));
   memset(pTransferMsg->strPwd, 0, sizeof(pTransferMsg->strPwd));

   memset(pTransferMsg->strOrderNo,0,sizeof(pTransferMsg->strOrderNo));

   memset(pTransferMsg->strDBIP, 0, sizeof(pTransferMsg->strDBIP));
   memset(pTransferMsg->strDB, 0, sizeof(pTransferMsg->strDB));
   memset(pTransferMsg->strDBID, 0, sizeof(pTransferMsg->strDBID));
   memset(pTransferMsg->strDBPWD, 0, sizeof(pTransferMsg->strDBPWD));
   memset(pTransferMsg->strUserID, 0, sizeof(pTransferMsg->strUserID));

   HandleFTPConnectInfo(pData,pTransferMsg);

#ifdef _UNICODE
   //单号
   QLCOMAPI.WCharToMByte(pData->strOrderNo,pTransferMsg->strOrderNo,sizeof(pTransferMsg->strOrderNo)/sizeof(pTransferMsg->strOrderNo[0]));

   //数据库IP 名称 连接账户 密码 登录人
   QLCOMAPI.WCharToMByte(pData->strDBIP,pTransferMsg->strDBIP,sizeof(pTransferMsg->strDBIP)/sizeof(pTransferMsg->strDBIP[0]));
   QLCOMAPI.WCharToMByte(pData->strDBName,pTransferMsg->strDB,sizeof(pTransferMsg->strDB)/sizeof(pTransferMsg->strDB[0]));
   QLCOMAPI.WCharToMByte(pData->strDBID,pTransferMsg->strDBID,sizeof(pTransferMsg->strDBID)/sizeof(pTransferMsg->strDBID[0]));
   QLCOMAPI.WCharToMByte(pData->strDBPassword,pTransferMsg->strDBPWD,sizeof(pTransferMsg->strDBPWD)/sizeof(pTransferMsg->strDBPWD[0]));
   QLCOMAPI.WCharToMByte(pData->strUserID,pTransferMsg->strUserID,sizeof(pTransferMsg->strUserID)/sizeof(pTransferMsg->strUserID[0]));
#else
   strncpy_s(pTransferMsg->strOrderNo,(LPSTR)(LPCTSTR)pData->strOrderNo, sizeof(pTransferMsg->strOrderNo) - 1);

   strncpy_s(pTransferMsg->strDBIP,(LPSTR)(LPCTSTR)pData->strDBIP, sizeof(pTransferMsg->strDBIP) - 1);
   strncpy_s(pTransferMsg->strDB,(LPSTR)(LPCTSTR)pData->strDBName, sizeof(pTransferMsg->strDB) - 1);
   strncpy_s(pTransferMsg->strDBID,(LPSTR)(LPCTSTR)pData->strDBID, sizeof(pTransferMsg->strDBID) - 1);
   strncpy_s(pTransferMsg->strDBPWD,(LPSTR)(LPCTSTR)pData->strDBPassword, sizeof(pTransferMsg->strDBPWD) - 1);
   strncpy_s(pTransferMsg->strUserID,(LPSTR)(LPCTSTR)pData->strUserID, sizeof(pTransferMsg->strUserID) - 1);

#endif // _UNICODE

   return pTransferMsg;
}

void GetFtpConnnectInfo(FILETRANS * pData,CString & strIP,CString & strName,CString & strPwd)
{
   strIP = pData->strFTPFarTrans;
   strName = pData->strFTPFarlName;
   strPwd = pData->strFTPFarPwd;

   if (!pData->strLocalTransIP.IsEmpty())
   {
      strIP = pData->strLocalTransIP;//当工艺制版时 使用暂时搁置 全部都用数据库一样的IP
      strName = FTP_DEFAULT_NAME;
      strPwd = FTP_DEFAULT_PWD;
   }
}

void HandleFTPConnectInfo(FILETRANS * pData,TransferMsg * pTransferMsg)
{
   CString strIP,strName,strPwd;
   GetFtpConnnectInfo(pData,strIP,strName,strPwd);
#ifdef _UNICODE
   //文件传输的IP 用户名 密码
   QLCOMAPI.WCharToMByte(strIP,pTransferMsg->strIP,sizeof(pTransferMsg->strIP)/sizeof(pTransferMsg->strIP[0]));
   QLCOMAPI.WCharToMByte(strName,pTransferMsg->strName,sizeof(pTransferMsg->strName)/sizeof(pTransferMsg->strName[0]));
   QLCOMAPI.WCharToMByte(strPwd,pTransferMsg->strPwd,sizeof(pTransferMsg->strPwd)/sizeof(pTransferMsg->strPwd[0]));
#else
   strncpy_s(pTransferMsg->strIP,(LPSTR)(LPCTSTR)strIP, sizeof(pTransferMsg->strIP) - 1);
   strncpy_s(pTransferMsg->strName,(LPSTR)(LPCTSTR)strName, sizeof(pTransferMsg->strName) - 1);
   strncpy_s(pTransferMsg->strPwd,(LPSTR)(LPCTSTR)strPwd, sizeof(pTransferMsg->strPwd) - 1);
#endif // _UNICODE

}

void HandleFTPConnectInfo(FILETRANS * pData,TransferListMsg * pTransferMsg)
{
   CString strIP,strName,strPwd;

   GetFtpConnnectInfo(pData,strIP,strName,strPwd);

#ifdef _UNICODE
   //文件传输的IP 用户名 密码
   QLCOMAPI.WCharToMByte(strIP,pTransferMsg->strIP,sizeof(pTransferMsg->strIP)/sizeof(pTransferMsg->strIP[0]));
   QLCOMAPI.WCharToMByte(strName,pTransferMsg->strName,sizeof(pTransferMsg->strName)/sizeof(pTransferMsg->strName[0]));
   QLCOMAPI.WCharToMByte(strPwd,pTransferMsg->strPwd,sizeof(pTransferMsg->strPwd)/sizeof(pTransferMsg->strPwd[0]));
#else
   strncpy_s(pTransferMsg->strIP,(LPSTR)(LPCTSTR)strIP, sizeof(pTransferMsg->strIP) - 1);
   strncpy_s(pTransferMsg->strName,(LPSTR)(LPCTSTR)strName, sizeof(pTransferMsg->strName) - 1);
   strncpy_s(pTransferMsg->strPwd,(LPSTR)(LPCTSTR)strPwd, sizeof(pTransferMsg->strPwd) - 1);
#endif // _UNICODE
}

FileTransCode HandleFunction_Upload(FILETRANS * pData)
{
   if (pData->vec_ActParam_OneParam.empty())
   {
      return FILETRANS_UPLOADZERO;
   }
   //准备上传路径
   CString strUploadPath;
   FileTransCode result = GetActionPath(pData,strUploadPath);
   if(FILETRANS_OK != result)
   {
      return result;
   }

   int nCount = static_cast<int>(pData->vec_ActParam_OneParam.size());

   TransferFileMsg *pTransFileMsg = new TransferFileMsg[nCount];
   memset(pTransFileMsg,0,sizeof(TransferFileMsg) * nCount);

   //准备上传参数
   //上传使用的是单个变量列表的相关参数
   int nAddCount = 0;
   for (auto it = pData->vec_ActParam_OneParam.begin();it != pData->vec_ActParam_OneParam.end();++it)
   {
      CString strFarPath = strUploadPath,strLocalPath = *it;
      CString strFileName = _T("");
      if (!strLocalPath.IsEmpty())
      {
         strFileName = PathFindFileName(strLocalPath);
         strFarPath += strFileName;
         memset(pTransFileMsg[nAddCount].strLocalPath, 0, sizeof(pTransFileMsg[nAddCount].strLocalPath));
         memset(pTransFileMsg[nAddCount].strFarPath, 0, sizeof(pTransFileMsg[nAddCount].strFarPath));
#ifdef _UNICODE
         QLCOMAPI.WCharToMByte(strFarPath,pTransFileMsg[nAddCount].strFarPath,sizeof(pTransFileMsg[nAddCount].strFarPath)/sizeof(pTransFileMsg[nAddCount].strFarPath[0]));
         QLCOMAPI.WCharToMByte(strLocalPath,pTransFileMsg[nAddCount].strLocalPath,sizeof(pTransFileMsg[nAddCount].strLocalPath)/sizeof(pTransFileMsg[nAddCount].strLocalPath[0]));
#else
         strncpy_s(pTransFileMsg[nAddCount].strFarPath,(LPSTR)(LPCTSTR)strFarPath, sizeof(pTransFileMsg[nAddCount].strFarPath) - 1);
         strncpy_s(pTransFileMsg[nAddCount].strLocalPath,(LPSTR)(LPCTSTR)strLocalPath, sizeof(pTransFileMsg[nAddCount].strLocalPath) - 1);
#endif
         nAddCount++;
      }
   }
   //获取上传的指针相关的信息
   auto pTransMsg = PrepareTransferMsg(pData);

   //填写上传对应的相关信息
   //pTransMsg->bZip = pData->b
   pTransMsg->bDelSrc = pData->bDelSrcFile;
   pTransMsg->pTransFileMsg = pTransFileMsg;
   pTransMsg->nTransFileNum = nAddCount;
   pTransMsg->funcUpload = pData->funcUpload;
   pTransMsg->pUserCallBackData = pData->pUserCallBackData;
   
   //换个参数传  暂未定
   /*pUpLoadMsg->nType = m_nFileType;
   pUpLoadMsg->nWholeType = m_nWholeFileType;*/
   //

   memset(pTransMsg->strFarPath, 0, sizeof(pTransMsg->strFarPath));
   //上传的路径 主要用于建对应的文件夹处理
#ifdef _UNICODE
   QLCOMAPI.WCharToMByte(strUploadPath,pTransMsg->strFarPath,sizeof(pTransMsg->strFarPath)/sizeof(pTransMsg->strFarPath[0]));
#else
   strncpy_s(pTransMsg->strFarPath,(LPSTR)(LPCTSTR)strUploadPath, sizeof(pTransMsg->strFarPath) - 1);
#endif
   //线程走起
   HANDLE handle;
   handle = ::CreateThread(NULL, 0, ThreadUpLoad, (LPVOID)pTransMsg, 0, NULL);
   CloseHandle(handle);

   //清空缓存
   pData->vec_ActParam_OneParam.clear();

   return FILETRANS_OK;
}

FileTransCode HandleFunction_Download(FILETRANS * pData)
{
   if (pData->vec_ActParam_TwoParam.empty())
   {
      return FILETRANS_DOWNLOADZERO;
   }

   //准备路径
   CString strDownloadPath;
   FileTransCode result = GetActionPath(pData,strDownloadPath);
   if(FILETRANS_OK != result)
   {
      return result;
   }

   int nCount = static_cast<int>(pData->vec_ActParam_TwoParam.size());

   TransferFileMsg *pTransFileMsg = new TransferFileMsg[nCount];
   memset(pTransFileMsg,0,sizeof(TransferFileMsg) * nCount);

   int nAddIndex = 0;
   for (auto it = pData->vec_ActParam_TwoParam.begin();it != pData->vec_ActParam_TwoParam.end();++it)
   {
      CString strFarPath = strDownloadPath + it->first;
      CString strLocalPath = it->second;

      if (!strFarPath.IsEmpty() && !strLocalPath.IsEmpty())
      {
         memset(pTransFileMsg[nAddIndex].strLocalPath, 0, sizeof(pTransFileMsg[nAddIndex].strLocalPath));
         memset(pTransFileMsg[nAddIndex].strFarPath, 0, sizeof(pTransFileMsg[nAddIndex].strFarPath));
#ifdef _UNICODE
         QLCOMAPI.WCharToMByte(strFarPath,pTransFileMsg[nAddIndex].strFarPath,sizeof(pTransFileMsg[nAddIndex].strFarPath)/sizeof(pTransFileMsg[nAddIndex].strFarPath[0]));
         QLCOMAPI.WCharToMByte(strLocalPath,pTransFileMsg[nAddIndex].strLocalPath,sizeof(pTransFileMsg[nAddIndex].strLocalPath)/sizeof(pTransFileMsg[nAddIndex].strLocalPath[0]));
#else
         strncpy_s(pTransFileMsg[nAddIndex].strFarPath,(LPSTR)(LPCTSTR)strFarPath, sizeof(pTransFileMsg[nAddIndex].strFarPath) - 1);
         strncpy_s(pTransFileMsg[nAddIndex].strLocalPath,(LPSTR)(LPCTSTR)strLocalPath, sizeof(pTransFileMsg[nAddIndex].strLocalPath) - 1);

#endif // _UNICODE

         nAddIndex++;
      }
   }

   //获取上传的指针相关的信息
   auto pTransMsg = PrepareTransferMsg(pData);

   //填写上传对应的相关信息
   pTransMsg->pTransFileMsg = pTransFileMsg;
   pTransMsg->nTransFileNum = nAddIndex;
   pTransMsg->funcBeforeDownload = pData->funcBeforeDownload;
   pTransMsg->pUserCallBackData = pData->pUserCallBackData;
   
   //换个参数传  暂未定
   /*pUpLoadMsg->nType = m_nFileType;
   pUpLoadMsg->nWholeType = m_nWholeFileType;*/
   //


   //线程走起
   HANDLE handle;
   handle = ::CreateThread(NULL, 0, ThreadDownLoad, (LPVOID)pTransMsg, 0, NULL);
   CloseHandle(handle);

   //清空缓存

   pData->vec_ActParam_TwoParam.clear();

   return FILETRANS_OK;
}

FileTransCode HandleFunction_DownDir(FILETRANS * pData)
{
   if(pData->vec_ActParam_TwoParam.empty())
   {
      return FILETRANS_DOWNLOADZERO;
   }

   CString strDownDir;
   FileTransCode result = GetActionPath(pData,strDownDir);
   if(FILETRANS_OK != result)
   {
      return result;
   }
   //获取下载的本地文件夹路径
   CString strLocalDir = pData->vec_ActParam_TwoParam[0].second;
   //去除云端文件夹的名称
   strDownDir.Replace('/','\\');
   strDownDir.TrimRight('\\');
   //拼接本地路径
   CString strDirName = PathFindFileName(strDownDir);
   strLocalDir += _T("\\") + strDirName;

   strLocalDir.Replace('/','\\');
   QLCOMAPI.MakeDirByCheck(strLocalDir);

   int nFileCount = 1;
   TransferFileMsg * pTransFileMsg = new TransferFileMsg[nFileCount];
   memset(pTransFileMsg,0,sizeof(TransferFileMsg) * nFileCount);

#ifdef _UNICODE
   QLCOMAPI.WCharToMByte(strDownDir,pTransFileMsg[0].strFarPath,sizeof(pTransFileMsg[0].strFarPath)/sizeof(pTransFileMsg[0].strFarPath[0]));
   QLCOMAPI.WCharToMByte(strLocalDir,pTransFileMsg[0].strLocalPath,sizeof(pTransFileMsg[0].strLocalPath)/sizeof(pTransFileMsg[0].strLocalPath[0]));
#else
   strncpy_s(pTransFileMsg[0].strFarPath,(LPSTR)(LPCTSTR)strDownDir, sizeof(pTransFileMsg[0].strFarPath) - 1);
   strncpy_s(pTransFileMsg[0].strLocalPath,(LPSTR)(LPCTSTR)strLocalDir, sizeof(pTransFileMsg[0].strLocalPath) - 1);
#endif // _UNICODE

   auto pTransMsg = PrepareTransferMsg(pData);
   //填写对应的相关信息
   pTransMsg->pTransFileMsg = pTransFileMsg;
   pTransMsg->nTransFileNum = nFileCount;

   HANDLE handle;
   handle = ::CreateThread(NULL, 0, ThreadDownDir, (LPVOID)pTransMsg, 0, NULL);
   CloseHandle(handle);


   return FILETRANS_OK;
}

FileTransCode HandleFunction_DownDirMsg(FILETRANS * pData)
{
   if(pData->vec_ActParam_TwoParam.empty())
   {
      return FILETRANS_DOWNLOADZERO;
   }

   CString strDownDir;
   FileTransCode result = GetActionPath(pData,strDownDir);
   if(FILETRANS_OK != result)
   {
      return result;
   }

   //获取下载的本地文件夹路径
   CString strLocalDir = pData->vec_ActParam_TwoParam[0].second;
   //去除云端文件夹的名称
   strDownDir.Replace('/','\\');
   strDownDir.TrimRight('\\');
   //拼接本地路径
   CString strDirName = PathFindFileName(strDownDir);
   strLocalDir += _T("\\") + strDirName;

   strLocalDir.Replace('/','\\');
   QLCOMAPI.MakeDirByCheck(strLocalDir);

   int nFileCount = 1;
   TransferFileMsg * pTransFileMsg = new TransferFileMsg[nFileCount];
   memset(pTransFileMsg,0,sizeof(TransferFileMsg) * nFileCount);

#ifdef _UNICODE
   QLCOMAPI.WCharToMByte(strDownDir,pTransFileMsg[0].strFarPath,sizeof(pTransFileMsg[0].strFarPath)/sizeof(pTransFileMsg[0].strFarPath[0]));
   QLCOMAPI.WCharToMByte(strLocalDir,pTransFileMsg[0].strLocalPath,sizeof(pTransFileMsg[0].strLocalPath)/sizeof(pTransFileMsg[0].strLocalPath[0]));
#else
   strncpy_s(pTransFileMsg[0].strFarPath,(LPSTR)(LPCTSTR)strDownDir, sizeof(pTransFileMsg[0].strFarPath) - 1);
   strncpy_s(pTransFileMsg[0].strLocalPath,(LPSTR)(LPCTSTR)strLocalDir, sizeof(pTransFileMsg[0].strLocalPath) - 1);
#endif // _UNICODE

   auto pTransMsg = PrepareTransferMsg(pData);
   //填写对应的相关信息
   pTransMsg->pTransFileMsg = pTransFileMsg;
   pTransMsg->nTransFileNum = nFileCount;
   pTransMsg->dwStyle = pData->dwStyle;
   /*pTransMsg->funcBeforeDownload = pData->funcBeforeDownload;
   pTransMsg->pUserCallBackData = pData->pUserCallBackData;*/

   HANDLE handle;
   handle = ::CreateThread(NULL, 0, ThreadDownDirMsg, (LPVOID)pTransMsg, 0, NULL);
   CloseHandle(handle);


   return FILETRANS_OK;
}

FileTransCode HandleFunction_DownByEx(FILETRANS * pData)
{
   //两个参数列表中的数据被设置为 key: 后缀  value:本地下载路径

   if(pData->vec_ActParam_TwoParam.empty())
   {
      return FILETRANS_DOWNLOADZERO;
   }
   CString strDownDir;
   FileTransCode result = GetActionPath(pData,strDownDir);
   if(FILETRANS_OK != result)
   {
      return result;
   }
   CString strLocalDir = pData->vec_ActParam_TwoParam[0].second;
   CString strExtension = pData->vec_ActParam_TwoParam[0].first;

   strDownDir.TrimRight('/');

   strLocalDir.Replace('/','\\');
   QLCOMAPI.MakeDirByCheck(strLocalDir);

   int nFileCount = 1;
   TransferFileMsg * pTransFileMsg = new TransferFileMsg[nFileCount];
   memset(pTransFileMsg,0,sizeof(TransferFileMsg) * nFileCount);

   memset(pTransFileMsg[0].strFarPath, 0, sizeof(pTransFileMsg[0].strFarPath));
   memset(pTransFileMsg[0].strLocalPath, 0, sizeof(pTransFileMsg[0].strLocalPath));
   memset(pTransFileMsg[0].strExtension, 0, sizeof(pTransFileMsg[0].strExtension));
#ifdef _UNICODE
   QLCOMAPI.WCharToMByte(strDownDir,pTransFileMsg[0].strFarPath,sizeof(pTransFileMsg[0].strFarPath)/sizeof(pTransFileMsg[0].strFarPath[0]));
   QLCOMAPI.WCharToMByte(strLocalDir,pTransFileMsg[0].strLocalPath,sizeof(pTransFileMsg[0].strLocalPath)/sizeof(pTransFileMsg[0].strLocalPath[0]));
   QLCOMAPI.WCharToMByte(strExtension,pTransFileMsg[0].strExtension,sizeof(pTransFileMsg[0].strExtension)/sizeof(pTransFileMsg[0].strExtension[0]));
#else
   strncpy_s(pTransFileMsg[0].strFarPath,(LPSTR)(LPCTSTR)strDownDir, sizeof(pTransFileMsg[0].strFarPath) - 1);
   strncpy_s(pTransFileMsg[0].strLocalPath,(LPSTR)(LPCTSTR)strLocalDir, sizeof(pTransFileMsg[0].strLocalPath) - 1);
   strncpy_s(pTransFileMsg[0].strExtension,(LPSTR)(LPCTSTR)strExtension,sizeof(pTransFileMsg[0].strExtension) - 1);
#endif // _UNICODE

   auto pTransMsg = PrepareTransferMsg(pData);
   //填写对应的相关信息
   pTransMsg->pTransFileMsg = pTransFileMsg;
   pTransMsg->nTransFileNum = nFileCount;

   pTransMsg->bDir = pData->bTraversingDir;
   pTransMsg->dwStyle = pData->dwStyle;
   /*pTransMsg->funcBeforeDownload = pData->funcBeforeDownload;
   pTransMsg->pUserCallBackData = pData->pUserCallBackData;*/

   HANDLE handle;
   handle = ::CreateThread(NULL, 0, ThreadDownByEx, (LPVOID)pTransMsg, 0, NULL);
   CloseHandle(handle);

   return FILETRANS_OK;
}

FileTransCode HandleFunction_GetList(FILETRANS * pData)
{
   //准备上传路径
   CString strGetListPath;
   FileTransCode result = GetActionPath(pData,strGetListPath);
   if(FILETRANS_OK != result)
   {
      return result;
   }

   TransferListMsg *pListMsg = NULL;
   pListMsg = new TransferListMsg;
   if (NULL != pListMsg)
   {
      memset(pListMsg,0,sizeof(TransferListMsg));
   }

   pListMsg->hWnd = pData->hProcessWnd;
   pListMsg->nSpecFlag = pData->nFlag;
   pListMsg->bUseHttp = pData->bHttpMode;

   memset(pListMsg->strIP, 0, sizeof(pListMsg->strIP));
   memset(pListMsg->strName, 0, sizeof(pListMsg->strName));
   memset(pListMsg->strPwd, 0, sizeof(pListMsg->strPwd));
   memset(pListMsg->strListDir, 0, sizeof(pListMsg->strListDir));

   HandleFTPConnectInfo(pData,pListMsg);
#ifdef _UNICODE
   QLCOMAPI.WCharToMByte(strGetListPath,pListMsg->strListDir,sizeof(pListMsg->strListDir)/sizeof(pListMsg->strListDir[0]));
#else
   strncpy_s(pListMsg->strListDir,(LPSTR)(LPCTSTR)strGetListPath, sizeof(pListMsg->strListDir) - 1);
#endif // _UNICODE

   HANDLE handle;
   handle = ::CreateThread(NULL, 0, ThreadGetDirList, (LPVOID)pListMsg, 0, NULL);
   CloseHandle(handle);

   return FILETRANS_OK;
}

FileTransCode HandleFunction_GetListEx(FILETRANS * pData)
{
   CString strGetListPath;
   FileTransCode result = GetActionPath(pData,strGetListPath);
   if(FILETRANS_OK != result)
   {
      return result;
   }

   TransferListMsg *pListMsg = NULL;
   pListMsg = new TransferListMsg;
   if (NULL != pListMsg)
   {
      memset(pListMsg,0,sizeof(TransferListMsg));
   }

   pListMsg->hWnd = pData->hProcessWnd;
   pListMsg->nSpecFlag = pData->nFlag;
   pListMsg->bUseHttp = pData->bHttpMode;

   pListMsg->dwStyle = pData->dwStyle;

   memset(pListMsg->strIP, 0, sizeof(pListMsg->strIP));
   memset(pListMsg->strName, 0, sizeof(pListMsg->strName));
   memset(pListMsg->strPwd, 0, sizeof(pListMsg->strPwd));
   memset(pListMsg->strListDir, 0, sizeof(pListMsg->strListDir));

   HandleFTPConnectInfo(pData,pListMsg);

#ifdef _UNICODE
   QLCOMAPI.WCharToMByte(strGetListPath,pListMsg->strListDir,sizeof(pListMsg->strListDir)/sizeof(pListMsg->strListDir[0]));
#else
   strncpy_s(pListMsg->strListDir,(LPSTR)(LPCTSTR)strGetListPath, sizeof(pListMsg->strListDir) - 1);
#endif // _UNICODE

   HANDLE handle;
   handle = ::CreateThread(NULL, 0, ThreadGetDirListEx, (LPVOID)pListMsg, 0, NULL);
   CloseHandle(handle);

   return FILETRANS_OK;
}

FileTransCode HandleFunction_Delete(FILETRANS * pData)
{
   if (pData->vec_ActParam_OneParam.empty())
   {
      return FILETRANS_DELZERO;
   }
   //准备上传路径
   CString strDeletePath;
   FileTransCode result = GetActionPath(pData,strDeletePath);
   if(FILETRANS_OK != result)
   {
      return result;
   }

   int nCount = static_cast<int>(pData->vec_ActParam_OneParam.size());

   TransferFileMsg *pTransFileMsg = new TransferFileMsg[nCount];
   memset(pTransFileMsg,0,sizeof(TransferFileMsg) * nCount);

   //准备上传参数
   //上传使用的是单个变量列表的相关参数
   int nAddCount = 0;
   for (auto it = pData->vec_ActParam_OneParam.begin();it != pData->vec_ActParam_OneParam.end();++it)
   {
      CString strFarPath = strDeletePath,strLocalPath = *it;
      CString strFileName = _T("");
      if (!strLocalPath.IsEmpty())
      {
         strFileName = PathFindFileName(strLocalPath);
         strFarPath += strFileName;
         memset(pTransFileMsg[nAddCount].strFarPath, 0, sizeof(pTransFileMsg[nAddCount].strFarPath));
#ifdef _UNICODE
         QLCOMAPI.WCharToMByte(strFarPath,pTransFileMsg[nAddCount].strFarPath,sizeof(pTransFileMsg[nAddCount].strFarPath)/sizeof(pTransFileMsg[nAddCount].strFarPath[0]));
#else
         strncpy_s(pTransFileMsg[nAddCount].strFarPath,(LPSTR)(LPCTSTR)strFarPath, sizeof(pTransFileMsg[nAddCount].strFarPath) - 1);
#endif
         nAddCount++;
      }
   }
   //获取上传的指针相关的信息
   auto pTransMsg = PrepareTransferMsg(pData);

   //填写上传对应的相关信息
   pTransMsg->pTransFileMsg = pTransFileMsg;
   pTransMsg->nTransFileNum = nAddCount;
   pTransMsg->funcDelete = pData->funcDelete;
   pTransMsg->pUserCallBackData = pData->pUserCallBackData;
   
   //换个参数传  暂未定
   /*pUpLoadMsg->nType = m_nFileType;
   pUpLoadMsg->nWholeType = m_nWholeFileType;*/
   //

   memset(pTransMsg->strFarPath, 0, sizeof(pTransMsg->strFarPath));
   //上传的路径 主要用于建对应的文件夹处理
#ifdef _UNICODE
   QLCOMAPI.WCharToMByte(strDeletePath,pTransMsg->strFarPath,sizeof(pTransMsg->strFarPath)/sizeof(pTransMsg->strFarPath[0]));
#else
   strncpy_s(pTransMsg->strFarPath,(LPSTR)(LPCTSTR)strDeletePath, sizeof(pTransMsg->strFarPath) - 1);
#endif
   //线程走起
   HANDLE handle;
   handle = ::CreateThread(NULL, 0, ThreadDel, (LPVOID)pTransMsg, 0, NULL);
   CloseHandle(handle);

   //清空缓存
   pData->vec_ActParam_OneParam.clear();
   
   return FILETRANS_OK;
}

FileTransCode HandleFunction_DeleteDir(FILETRANS * pData)
{
   //删除文件夹不涉及参数处理


   CString strDeleteDir;
   FileTransCode result = GetActionPath(pData,strDeleteDir);
   if(FILETRANS_OK != result)
   {
      return result;
   }

   int nFileCount = 1;
   TransferFileMsg *pTransFileMsg = new TransferFileMsg[nFileCount];
   memset(pTransFileMsg,0,sizeof(TransferFileMsg) * nFileCount);

#ifdef _UNICODE
   QLCOMAPI.WCharToMByte(strDeleteDir,pTransFileMsg[0].strFarPath,sizeof(pTransFileMsg[0].strFarPath)/sizeof(pTransFileMsg[0].strFarPath[0]));
#else
   strncpy_s(pTransFileMsg[0].strFarPath,(LPSTR)(LPCTSTR)strDeleteDir, sizeof(pTransFileMsg[0].strFarPath) - 1);
#endif // _UNICODE

   auto pTransMsg = PrepareTransferMsg(pData);

   pTransMsg->pTransFileMsg = pTransFileMsg;
   pTransMsg->nTransFileNum = nFileCount;
   pTransMsg->funcDelete = pData->funcDelete;
   pTransMsg->pUserCallBackData = pData->pUserCallBackData;

   HANDLE handle;
   handle = ::CreateThread(NULL, 0, ThreadDelDir, (LPVOID)pTransMsg, 0, NULL);
   CloseHandle(handle);

   return FILETRANS_OK;
}

FileTransCode HandleFunction_Copy(FILETRANS * pData)
{
   if (pData->vec_ActParam_TwoParam.empty())
   {
      return FILETRANS_COPYZERO;
   }

   int nFileCount = static_cast<int>(pData->vec_ActParam_TwoParam.size());
   TransferFileMsg *pTransFileMsg = new TransferFileMsg[nFileCount];
   memset(pTransFileMsg,0,sizeof(TransferFileMsg) * nFileCount);

   //准备路径
   CString strOrgPath,strDstPath;
   FileTransCode result = GetActionPath(pData,strOrgPath);
   if(FILETRANS_OK != result)
   {
      return result;
   }

   result = GetActionPath(pData->map_Key_Path,pData->strDstAction_ParamKey,pData->strDstOrderNo,pData->strDstSize,pData->nDstVersion,strDstPath);
   if(FILETRANS_OK != result)
   {
      return result;
   }

   int nAddIndex = 0;
   for (auto it = pData->vec_ActParam_TwoParam.begin();it != pData->vec_ActParam_TwoParam.end();++it)
   {
      CString strOrgFileName = strOrgPath + it->first;
      CString strDstFileName = strDstPath + it->second;

      if (!strOrgPath.IsEmpty() && !strDstPath.IsEmpty())
      {
         memset(pTransFileMsg[nAddIndex].strLocalPath, 0, sizeof(pTransFileMsg[nAddIndex].strLocalPath));
         memset(pTransFileMsg[nAddIndex].strFarPath, 0, sizeof(pTransFileMsg[nAddIndex].strFarPath));

#ifdef _UNICODE
         QLCOMAPI.WCharToMByte(strOrgFileName,pTransFileMsg[nAddIndex].strLocalPath,sizeof(pTransFileMsg[0].strLocalPath)/sizeof(pTransFileMsg[0].strLocalPath[0]));
         QLCOMAPI.WCharToMByte(strDstFileName,pTransFileMsg[nAddIndex].strFarPath,sizeof(pTransFileMsg[0].strFarPath)/sizeof(pTransFileMsg[0].strFarPath[0]));
#else
         strncpy_s(pTransFileMsg[nAddIndex].strLocalPath,(LPSTR)(LPCTSTR)strOrgFileName, sizeof(pTransFileMsg[0].strLocalPath) - 1);
         strncpy_s(pTransFileMsg[nAddIndex].strFarPath,(LPSTR)(LPCTSTR)strDstFileName, sizeof(pTransFileMsg[0].strFarPath) - 1);
#endif // _UNICODE

         nAddIndex++;
      }
   }

   //获取上传的指针相关的信息
   auto pTransMsg = PrepareTransferMsg(pData);

   //填写上传对应的相关信息
   pTransMsg->pTransFileMsg = pTransFileMsg;
   pTransMsg->nTransFileNum = nAddIndex;

   HANDLE handle = ::CreateThread(NULL, 0, ThreadCopyFiles, (LPVOID)pTransMsg, 0, NULL);
   CloseHandle(handle);

   return FILETRANS_OK;
}

FileTransCode HandleFunction_BackupFile_Move(FILETRANS * pData)
{
   return HandleFunction_BackupFile(pData,TRUE);
}

FileTransCode HandleFunction_BackupFile_Copy(FILETRANS * pData)
{
   return HandleFunction_BackupFile(pData,FALSE);
}

FileTransCode HandleFunction_BackupFile(FILETRANS * pData,BOOL bMove)
{
   if (pData->strOrderNo.IsEmpty() || pData->strDstOrderNo.IsEmpty())
   {
      //返回订单号未设置错误
      return FILETRANS_WRONG_BAD_FUNCTION_ARGUMENT;
   }

   if (pData->vec_ActParam_TwoParam.empty())
   {
      return FILETRANS_COPYZERO;
   }

   int nError = -1;

   int nFileCount = static_cast<int>(pData->vec_ActParam_TwoParam.size()); 
   TransferFileMsg *pTransFileMsg = new TransferFileMsg[nFileCount];
   memset(pTransFileMsg,0,sizeof(TransferFileMsg) * nFileCount);
   int nIndex = 0;
   for (auto it = pData->vec_ActParam_TwoParam.begin();it != pData->vec_ActParam_TwoParam.end();++it,++nIndex)
   {
      CString sPath,sPathBackup;
      GetActionPath(pData->map_Key_Path,it->first,pData->strOrderNo,pData->strSize,pData->nVersion,sPath);
      GetActionPath(pData->map_Key_Path,it->second,pData->strDstOrderNo,pData->strDstSize,pData->nDstVersion,sPathBackup);

      memset(pTransFileMsg[nIndex].strLocalPath, 0, sizeof(pTransFileMsg[nIndex].strLocalPath)); //strLocalPath用来存源路径
      memset(pTransFileMsg[nIndex].strFarPath, 0, sizeof(pTransFileMsg[nIndex].strFarPath)); //strFarPath用来存目标路径

#ifdef _UNICODE
      QLCOMAPI.WCharToMByte(sPath,pTransFileMsg[nIndex].strLocalPath,sizeof(pTransFileMsg[0].strLocalPath)/sizeof(pTransFileMsg[0].strLocalPath[0]));
      QLCOMAPI.WCharToMByte(sPathBackup,pTransFileMsg[nIndex].strFarPath,sizeof(pTransFileMsg[0].strFarPath)/sizeof(pTransFileMsg[0].strFarPath[0]));
#else
      strncpy_s(pTransFileMsg[nIndex].strLocalPath,(LPSTR)(LPCTSTR)sPath, sizeof(pTransFileMsg[0].strLocalPath) - 1);
      strncpy_s(pTransFileMsg[nIndex].strFarPath,(LPSTR)(LPCTSTR)sPathBackup, sizeof(pTransFileMsg[0].strFarPath) - 1);
#endif // _UNICODE
   }

   auto pTransMsg = PrepareTransferMsg(pData);

   //填写上传对应的相关信息
   pTransMsg->pTransFileMsg = pTransFileMsg;
   pTransMsg->nTransFileNum = nFileCount;

   HANDLE handle;
   if (bMove)
   {
      handle = ::CreateThread(NULL, 0, ThreadMoveFile, (LPVOID)pTransMsg, 0, NULL);
   }
   else
   {
      handle = ::CreateThread(NULL, 0, ThreadCopyFiles, (LPVOID)pTransMsg, 0, NULL);
   }
   CloseHandle(handle);

   return FILETRANS_OK;
}

FileTransCode HandleFunction_CopyVersionToCurVersion(FILETRANS * pData)
{
   //当前版本 -1 拷贝到新版本里面去 pData->nDstVersion
   // 旧版本 pData->nVersion 拷贝到当前版本去 -1
   
   if (pData->strOrderNo.IsEmpty() || pData->strDstOrderNo.IsEmpty())
   {
      //返回订单号未设置错误
      return FILETRANS_WRONG_BAD_FUNCTION_ARGUMENT;
   }

   int nError = -1;
   int nFileCount = static_cast<int>(pData->vec_ActParam_TwoParam.size());
   if (0 == nFileCount)
   {
      return FILETRANS_COPYZERO;
   }

   TransferFileMsg *pTransFileMsg = new TransferFileMsg[nFileCount];
   if (NULL != pTransFileMsg)
   {
      memset(pTransFileMsg,0,sizeof(TransferFileMsg) * nFileCount);
   }
   else
   {
      return FILETRANS_WRONG_MEMORYERROR;
   }
   int nIndex = 0;
   for (auto it = pData->vec_ActParam_TwoParam.begin();it != pData->vec_ActParam_TwoParam.end();++it,++nIndex)
   {
      CString sPath,sPathBackup;
      GetActionPath(pData->map_Key_Path,it->first,pData->strOrderNo,pData->strSize,-1,sPath);
      GetActionPath(pData->map_Key_Path,it->second,pData->strDstOrderNo,pData->strDstSize,pData->nDstVersion,sPathBackup);

      memset(pTransFileMsg[nIndex].strLocalPath, 0, sizeof(pTransFileMsg[nIndex].strLocalPath)); //strLocalPath用来存源路径
      memset(pTransFileMsg[nIndex].strFarPath, 0, sizeof(pTransFileMsg[nIndex].strFarPath)); //strFarPath用来存目标路径
#ifdef _UNICODE
      QLCOMAPI.WCharToMByte(sPath,pTransFileMsg[nIndex].strLocalPath,sizeof(pTransFileMsg[0].strLocalPath)/sizeof(pTransFileMsg[0].strLocalPath[0]));
      QLCOMAPI.WCharToMByte(sPathBackup,pTransFileMsg[nIndex].strFarPath,sizeof(pTransFileMsg[0].strFarPath)/sizeof(pTransFileMsg[0].strFarPath[0]));
#else
      strncpy_s(pTransFileMsg[nIndex].strLocalPath,(LPSTR)(LPCTSTR)sPath, sizeof(pTransFileMsg[0].strLocalPath) - 1);
      strncpy_s(pTransFileMsg[nIndex].strFarPath,(LPSTR)(LPCTSTR)sPathBackup, sizeof(pTransFileMsg[0].strFarPath) - 1);
#endif // _UNICODE
   }

   TransferMsg *pBackupFileMsg = NULL;
   pBackupFileMsg = new TransferMsg[2];
   if (NULL != pBackupFileMsg)
   {
      memset(pBackupFileMsg,0,sizeof(TransferMsg));
   }
   else
   {
      return FILETRANS_WRONG_MEMORYERROR;
   }

   pBackupFileMsg->hWnd = pData->hProcessWnd;
   pBackupFileMsg->nSpecFlag = pData->nFlag;
   pBackupFileMsg->nLoginType = pData->nLoginType;
   pBackupFileMsg->bUseHttp = pData->bHttpMode;

   pBackupFileMsg->pTransFileMsg = pTransFileMsg;
   pBackupFileMsg->nTransFileNum = nFileCount;

   memset(pBackupFileMsg->strIP, 0, sizeof(pBackupFileMsg->strIP));
   memset(pBackupFileMsg->strName, 0, sizeof(pBackupFileMsg->strName));
   memset(pBackupFileMsg->strPwd, 0, sizeof(pBackupFileMsg->strPwd));

   memset(pBackupFileMsg->strOrderNo,0,sizeof(pBackupFileMsg->strOrderNo));

   memset(pBackupFileMsg->strDBIP, 0, sizeof(pBackupFileMsg->strDBIP));
   memset(pBackupFileMsg->strDB, 0, sizeof(pBackupFileMsg->strDB));
   memset(pBackupFileMsg->strDBID, 0, sizeof(pBackupFileMsg->strDBID));
   memset(pBackupFileMsg->strDBPWD, 0, sizeof(pBackupFileMsg->strDBPWD));
   memset(pBackupFileMsg->strUserID, 0, sizeof(pBackupFileMsg->strUserID));

   HandleFTPConnectInfo(pData,pBackupFileMsg);
#ifdef _UNICODE
//单号
   QLCOMAPI.WCharToMByte(pData->strOrderNo,pBackupFileMsg->strOrderNo,sizeof(pBackupFileMsg->strOrderNo)/sizeof(pBackupFileMsg->strOrderNo[0]));
#else
   strncpy_s(pBackupFileMsg->strOrderNo,(LPSTR)(LPCTSTR)pData->strOrderNo, sizeof(pBackupFileMsg->strOrderNo) - 1);
#endif // _UNICODE


   TransferFileMsg * pOldTransFileMsg = pTransFileMsg;
   { //从老版本复制到主目录
      TransferFileMsg *pTransFileMsg = new TransferFileMsg[nFileCount];
      if (NULL != pTransFileMsg)
      {
         memset(pTransFileMsg,0,sizeof(TransferFileMsg) * nFileCount);
      }
      else
      {
         delete [] pOldTransFileMsg;
         delete [] pBackupFileMsg;
         return FILETRANS_WRONG_MEMORYERROR;
      }

      int nIndex = 0;
      for (auto it = pData->vec_ActParam_TwoParam.begin();it != pData->vec_ActParam_TwoParam.end();++it,++nIndex)
      {
         CString sPath,sPathBackup;
         GetActionPath(pData->map_Key_Path,it->second,pData->strOrderNo,pData->strSize,pData->nVersion,sPath);
         GetActionPath(pData->map_Key_Path,it->first,pData->strDstOrderNo,pData->strDstSize,-1,sPathBackup);

         memset(pTransFileMsg[nIndex].strLocalPath, 0, sizeof(pTransFileMsg[nIndex].strLocalPath)); //strLocalPath用来存源路径
         memset(pTransFileMsg[nIndex].strFarPath, 0, sizeof(pTransFileMsg[nIndex].strFarPath)); //strFarPath用来存目标路径
#ifdef _UNICODE
         QLCOMAPI.WCharToMByte(sPath,pTransFileMsg[nIndex].strLocalPath,sizeof(pTransFileMsg[0].strLocalPath)/sizeof(pTransFileMsg[0].strLocalPath[0]));
         QLCOMAPI.WCharToMByte(sPathBackup,pTransFileMsg[nIndex].strFarPath,sizeof(pTransFileMsg[0].strFarPath)/sizeof(pTransFileMsg[0].strFarPath[0]));
#else
         strncpy_s(pTransFileMsg[nIndex].strLocalPath,(LPSTR)(LPCTSTR)sPath, sizeof(pTransFileMsg[0].strLocalPath) - 1);
         strncpy_s(pTransFileMsg[nIndex].strFarPath,(LPSTR)(LPCTSTR)sPathBackup, sizeof(pTransFileMsg[0].strFarPath) - 1);
#endif // _UNICODE
      }
      ++pBackupFileMsg;

      pBackupFileMsg->hWnd = pData->hProcessWnd;
      pBackupFileMsg->nSpecFlag = pData->nFlag;
      pBackupFileMsg->nLoginType = pData->nLoginType;
      pBackupFileMsg->bUseHttp = pData->bHttpMode;

      pBackupFileMsg->pTransFileMsg = pTransFileMsg;
      pBackupFileMsg->nTransFileNum = nFileCount;

      memset(pBackupFileMsg->strIP, 0, sizeof(pBackupFileMsg->strIP));
      memset(pBackupFileMsg->strName, 0, sizeof(pBackupFileMsg->strName));
      memset(pBackupFileMsg->strPwd, 0, sizeof(pBackupFileMsg->strPwd));

      memset(pBackupFileMsg->strOrderNo,0,sizeof(pBackupFileMsg->strOrderNo));

      memset(pBackupFileMsg->strDBIP, 0, sizeof(pBackupFileMsg->strDBIP));
      memset(pBackupFileMsg->strDB, 0, sizeof(pBackupFileMsg->strDB));
      memset(pBackupFileMsg->strDBID, 0, sizeof(pBackupFileMsg->strDBID));
      memset(pBackupFileMsg->strDBPWD, 0, sizeof(pBackupFileMsg->strDBPWD));
      memset(pBackupFileMsg->strUserID, 0, sizeof(pBackupFileMsg->strUserID));

      HandleFTPConnectInfo(pData,pBackupFileMsg);
#ifdef _UNICODE
      //单号
      QLCOMAPI.WCharToMByte(pData->strOrderNo,pBackupFileMsg->strOrderNo,sizeof(pBackupFileMsg->strOrderNo)/sizeof(pBackupFileMsg->strOrderNo[0]));
#else
      strncpy_s(pBackupFileMsg->strOrderNo,(LPSTR)(LPCTSTR)pData->strOrderNo, sizeof(pBackupFileMsg->strOrderNo) - 1);
#endif // _UNICODE

      --pBackupFileMsg; //再指向第一个
   }

   HANDLE handle = ::CreateThread(NULL, 0, ThreadCopyVersionToNewCreatedOne, (LPVOID)pBackupFileMsg, 0, NULL);
   CloseHandle(handle);

   return FILETRANS_OK;
}

FileTransCode HandleFunction_SetSampleOrder(FILETRANS * pData)
{
   if(pData->vec_ActParam_OneParam.empty())
   {
      return FILETRANS_WRONG_BAD_FUNCTION_ARGUMENT;
   }
   if(pData->strOrderNo.IsEmpty())
   {
      return FILETRANS_WRONG_BAD_FUNCTION_ARGUMENT;
   }

   CString strSampleOrder = pData->vec_ActParam_OneParam[0];

   CADOConnEx ADOConn;

   CString strConnectSql = GetSqlConnectStr(pData);

   ADOConn.SetConnecetSqlStr(strConnectSql);

   /*CString strSQL =_T("");
   strSQL.Format(_T("update %s set %s = '%s' where %s = '%s'")
      ,DB_TABLE_RDRECORDS1ST
      ,DBRdRecords1st_key_cSampleOrder ,strSampleOrder
      ,DBRdRecords1st_key_cSalesCode,pData->strOrderNo);
   if(ADOConn.ExecuteSQL(strSQL))
   {*/
      return FILETRANS_OK;
   /*}*/

   return FILETRANS_WRONG_SQLEXECUERR;
}

FileTransCode GetInfo_FileExists(FILETRANS * pData,void * pFileExists)
{
   CString strFarPath = _T("");

   FileTransCode result = GetActionPath(pData,strFarPath);
   if(FILETRANS_OK != result)
   {
      return result;
   }

   if (0 >= static_cast<int>(pData->vec_ActParam_OneParam.size()))
   {
      result = FILETRANS_WRONG_BAD_FUNCTION_ARGUMENT;
      return result;
   }
   //取单个参数的第一个作为文件名
   CString strFileName = pData->vec_ActParam_OneParam[0];

   *((BOOL *)pFileExists) = FALSE;

   FileMsg *pItem = NULL;
   int nNum = 0;

   BOOL bHttpMode = pData->bHttpMode;

   CString strSetingIP,strSettingName,strSettingPwd;
   GetFtpConnnectInfo(pData,strSetingIP,strSettingName,strSettingPwd);

   if (!bHttpMode)
   {
#ifdef _UNICODE
      char szFarPath[MAX_PATH] = {0};
      char szIp[50] = {0};
      char szName[50] = {0};
      char szPwd[50] = {0};

      QLCOMAPI.WCharToMByte(strSetingIP,szIp,sizeof(szIp)/sizeof(szIp[0]));
      QLCOMAPI.WCharToMByte(strSettingName,szName,sizeof(szName)/sizeof(szName[0]));
      QLCOMAPI.WCharToMByte(strSettingPwd,szPwd,sizeof(szPwd)/sizeof(szPwd[0]));
      QLCOMAPI.WCharToMByte(strFarPath,szFarPath,sizeof(szFarPath)/sizeof(szFarPath[0]));
#else
      CString strIP = strSetingIP;
      CString strName = strSettingName;
      CString strPwd = strSettingPwd;
#endif // _UNICODE

      zt_FtpComm objFtpComm;
      int nOpenFtp = 0;
#ifdef _UNICODE
      nOpenFtp = objFtpComm.Ftp_OpenEx(szIp,szName, szPwd);
#else
      nOpenFtp = objFtpComm.Ftp_OpenEx(strIP,strName, strPwd);
#endif // _UNICODE

      if (1 == nOpenFtp)
      {
         objFtpComm.Ftp_ProcessMsg(pData->hProcessWnd);
         //开启服务成功，执行上传动作

#ifdef  _UNICODE 
         if(1 == objFtpComm.Ftp_Getlist(szFarPath,&pItem,&nNum))
         {
#else
         if(1 == objFtpComm.Ftp_Getlist(strFarPath,&pItem,&nNum))
         {
#endif
            if (0 != nNum)
            {
               for (int nIndex = 0;nIndex < nNum;nIndex++)
               {
                  CString strFarFileName(pItem[nIndex].filename);

                  if (0 == strFarFileName.CompareNoCase(strFileName))
                  {
                     result = FILETRANS_OK;
                     *((BOOL *)pFileExists) = TRUE;
                     break;
                  }
               }
            }
         }
      }
      else
      {
         if (2 == nOpenFtp) result = FILETRANS_WRONG_DISCONNECTED;
         else result = FILETRANS_WRONG_FTPCANTOPEN;
      }

      if (1 == nOpenFtp) objFtpComm.Ftp_Close();//关闭
   }
   else
   {
      QL_HttpClient objHttpClient(strSetingIP,strSettingName,strSettingPwd);

      if(HTTP_RET_CODE_SUCCESS == objHttpClient.Http_Getlist(strFarPath,&pItem,&nNum,FS_DEFAULT))
      {
         for (int nIndex = 0;nIndex < nNum;nIndex++)
         {
            CString strFarFileName(pItem[nIndex].filename);

            if (0 == strFarFileName.CompareNoCase(strFileName))
            {
               result = FILETRANS_OK;
               *((BOOL *)pFileExists) = TRUE;
               break;
            }
         }
      }
   }

   if (NULL != pItem)
   {
      delete pItem;
      pItem = NULL;
   }

   return result;
}

FileTransCode GetInfo_UserID(FILETRANS * pData,void * pString)
{
   *((CString *)pString) = pData->strUserID;

   return FILETRANS_OK;
}

FileTransCode GetInfo_UserName(FILETRANS * pData,void * pUserName)
{
   FileTransCode nResult = CKDBLogin(pData);
   if(FILETRANS_OK != nResult)
   {
      return nResult;
   }

   CString strSQL = _T("");

   strSQL.Format(_T("select %s,%s from %s where %s = '%s'"),
      DBPerson_key_UserID,DBPerson_key_UserName,
      DB_TABLE_PERSON,
      DBPerson_key_UserID,pData->strUserID);

   CADOConnEx ADOConn;
   CString strConnectSql = GetSqlConnectStr(pData);
   ADOConn.SetConnecetSqlStr(strConnectSql);

   ADOConn.GetRecordSet(strSQL);
   if (!ADOConn.adoEOF())
   {
      *((CString *)pUserName) = ADOConn.GetValueString(DBPerson_key_UserName);

      nResult = FILETRANS_OK;
   }
   else
   {
      nResult = FILETRANS_WRONG_SQLEXECUERR;
   }

   return nResult;
}

FileTransCode GetInfo_DllVersion(FILETRANS * pData,void * pVersion)
{
   *((CString *)pVersion) = QLFILETRANS_VERSION;
   return FILETRANS_OK;
}

FileTransCode GetInfo_HttpMode(FILETRANS * pData,void * pHttpMode)
{
   *((BOOL *)pHttpMode) = pData->bHttpMode;
   return FILETRANS_OK;
}

FileTransCode GetInfo_OrderExists(FILETRANS * pData,void * pOrderExists)
{
   if (pData->strOrderNo.IsEmpty())
   {
      return FILETRANS_ORDEREMPTY;
   }

   FileTransCode nResult = CKDBLogin(pData);
   if (FILETRANS_OK != nResult)
   {
      return nResult;
   }

   CADOConnEx ADOConn;

   CString strConnectSql = GetSqlConnectStr(pData);

   ADOConn.SetConnecetSqlStr(strConnectSql);

   CString strSQL = _T("");
   //检测数据库中是否已经有对应的文件
   strSQL.Format(_T("select %s from %s where %s = '%s'") ,DBKuanShi_key_ID,DB_TABLE_STYLE ,DBKuanShi_key_StyleNo ,pData->strOrderNo);
   ADOConn.GetRecordSet(strSQL);
   if (!ADOConn.adoEOF())
   {
      *((BOOL *)pOrderExists) = TRUE;
   }
   else
   {
      *((BOOL *)pOrderExists) = FALSE;
   }

   return FILETRANS_OK;
}

FileTransCode GetInfo_CanLogin(FILETRANS * pData,void * pLoginResult)
{
   *((BOOL *)pLoginResult) = Login(pData);
   return FILETRANS_OK;
}

FileTransCode GetInfo_SampleOrder(FILETRANS * pData,void * pSampleOrder)
{
   if (pData->strOrderNo.IsEmpty())
   {
      return FILETRANS_ORDEREMPTY;
   }

   FileTransCode result = FILETRANS_OK;

   CADOConnEx ADOConn;

   CString strConnectSql = GetSqlConnectStr(pData);

   ADOConn.SetConnecetSqlStr(strConnectSql);

   CString strSQL =_T("");
   /*strSQL.Format(_T("select %s,%s from %s where %s = '%s'"),DBRdRecords1st_key_cSampleOrder,DBRdRecords1st_key_cInvKuanhao,DB_TABLE_RDRECORDS1ST ,DBRdRecords1st_key_cSalesCode ,pData->strOrderNo);
   ADOConn.GetRecordSet(strSQL);
   if (!ADOConn.adoEOF())
   {
      *((CString *)pSampleOrder) = ADOConn.GetValueString( DBRdRecords1st_key_cSampleOrder );
      if (((CString *)pSampleOrder)->IsEmpty())
      {
         CString strStyleNo = ADOConn.GetValueString(DBRdRecords1st_key_cInvKuanhao);
         //获取款式号 然后通过款式号 获取对应的首选单号
         strSQL.Format(_T("select top 1 %s  from %s where %s = '%s' and %s = '%d'")
            ,DBVarious_key_OrderNo
            ,DB_TABLE_VARIOUSSTYLE
            ,DBVarious_key_StyleNo,strStyleNo
            ,DBVarious_key_Perferred,CDBVariousStyleInfoData::Ord_Perferred);

         ADOConn.GetRecordSet(strSQL);
         if (!ADOConn.adoEOF())
         {
            *((CString *)pSampleOrder) = ADOConn.GetValueString(DBVarious_key_OrderNo);
         }
      }
   }*/

   return result;
}

FileTransCode GetInfo_PopupLogin(FILETRANS * pData,void * pParam)
{
   *((BOOL *)pParam) = PopLogin(pData->strWorkPath,pData->nLoginType);
   return FILETRANS_OK;
}

