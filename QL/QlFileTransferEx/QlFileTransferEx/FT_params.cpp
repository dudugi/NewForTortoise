#include "stdafx.h"
#include "FT_params.h"
#include "CommonAPI.h"
#include "QlFileTransferEx.h"
#include "FT_String.inl"
#include "FileTransferDef.inl"


void CFT_params::InitDataParams(FileTrans_easy * pData,const CString & strWorkPath)
{
   if (NULL == pData)
   {
      return;
   }

   pData->strWorkPath = strWorkPath;
   pData->nFlag = UNDESIGN_FLAG;//传输时的配置信息默认为0

   pData->bDelSrcFile = FALSE;//默认不删除源文件
   pData->hProcessWnd = NULL;//默认接收消息句柄为空
   pData->nAction = en_Action_UnDefine;//操作行为默认为未定义
   pData->nVersion = -1;
   pData->nDstVersion = -1;
   pData->bPtLog = FALSE;
   pData->bPtLog = FALSE;
   pData->bTraversingDir = FALSE;
   pData->dwStyle = FS_DEFAULT;
   pData->funcUpload = NULL;
   pData->funcDelete = NULL;
   pData->funcBeforeDownload = NULL;
   pData->pUserCallBackData = NULL;

   //初始化默认数据信息 检测配置文件是否存在 （如果不存在 则从资源中生成到相关路径下
   InitConfigInfo(pData,strWorkPath);

   //从本地路径中读取相关信息并初始化该类
   InitParamInfoFromConfig(pData,strWorkPath);
}

void CFT_params::InitConfigInfo(FileTrans_easy * pData,const CString & strWorkPath)
{
   
   pData->map_Default[STR_MAP_KEY_PORT_FTP] = STR_MAP_VALUE_PORT_FTP;
   pData->map_Default[STR_MAP_KEY_PORT_HTTP] = STR_MAP_VALUE_PORT_HTTP;

   //如果配置文件中的文件存在则读取该文件 否则释放资源文件过去
   QLCOMAPI.MakeDirByCheck(strWorkPath + STR_PATH_CONFIG);
   //默认端口的xml
   CString strSettingFile = strWorkPath + STR_PATH_CONFIG_SETTING;
   if (!PathFileExists(strSettingFile))
   {//如果文件不存在  释放资源文件过去
      theApp.FreeResourceToFile(IDR_XML_SETTING,STR_RESOURCE_TYPE_XML,strSettingFile);
   }


   TiXmlDocument doc;
   char szXmlFile[MAX_PATH] = {};
   memset(szXmlFile, 0, sizeof(szXmlFile));
#ifdef _UNICODE
   QLCOMAPI.WCharToMByte(strSettingFile,szXmlFile,sizeof(szXmlFile)/sizeof(szXmlFile[0]));
#else
   strncpy_s(szXmlFile,(LPSTR)(LPCTSTR)strSettingFile, sizeof(szXmlFile) - 1);
#endif
   doc.LoadFile(szXmlFile,TIXML_ENCODING_UTF8);
   TiXmlHandle docHandle( &doc );
   TiXmlElement* pRootElement = 0;
   pRootElement = docHandle.FirstChild( XML_PARAM_DEFAULTPORT_SETTTING_ROOT ).ToElement();//获取根节点
   if (pRootElement)
   {
      TiXmlElement* pPortElement = pRootElement->FirstChildElement(XML_PARAM_DEFAULTPORT_SETTTING_PORT);
      if (NULL != pPortElement)
      {
         TiXmlElement* pFilePortElement = pPortElement->FirstChildElement(XML_PARAM_DEFAULTPORT_SETTTING_FILEPORT);
         if (NULL != pFilePortElement)
         {
            TiXmlElement* pFTPPortElement = pFilePortElement->FirstChildElement(XML_PARAM_DEFAULTPORT_SETTTING_PORT_FTP);
            if (NULL != pFTPPortElement)
            {
               pData->map_Default[STR_MAP_KEY_PORT_FTP] = theApp.GetTinyXmlNodeString(pFTPPortElement->FirstChildElement(XML_PARAM_DEFAULTPORT_SETTTING_PORT_VALUE_DEFAULT));
            }

            TiXmlElement* pHTTPPortElement = pFilePortElement->FirstChildElement(XML_PARAM_DEFAULTPORT_SETTTING_PORT_HTTP);
            if (NULL != pHTTPPortElement)
            {
               pData->map_Default[STR_MAP_KEY_PORT_HTTP] = theApp.GetTinyXmlNodeString(pHTTPPortElement->FirstChildElement(XML_PARAM_DEFAULTPORT_SETTTING_PORT_VALUE_DEFAULT));
            }
         }
      }
   }

   //路径配置不设置默认参数 如果没有配置 那就是没有配置  所有的key值应与实际应用模块一一对应

   //读取路径相关的信息
   strSettingFile = strWorkPath + STR_PATH_CONFIG_PATH;
   if (!PathFileExists(strSettingFile))
   {//如果文件不存在  释放资源文件过去
      theApp.FreeResourceToFile(IDR_XML_PATH_SETTING,STR_RESOURCE_TYPE_XML,strSettingFile);
   }

   //加载默认数据
   CString strDefaultSettingPath = strWorkPath + STR_PATH_CONFIG_PATH_DEFAULT;
   DeleteFile(strDefaultSettingPath);
   theApp.FreeResourceToFile(IDR_XML_PATH_SETTING,STR_RESOURCE_TYPE_XML,strDefaultSettingPath);
   map<CString,S_PathParam> map_ResourceData;//资源中的数据
   ParsePathSetting_byFile(strDefaultSettingPath,map_ResourceData);
   DeleteFile(strDefaultSettingPath);

   ParsePathSetting_byFile(strSettingFile,pData->map_Key_Path);

   //整合默认数据和用户配置数据
   CombinePathSetting(map_ResourceData,pData->map_Key_Path);
}

void CFT_params::ParsePathSetting_byFile(const CString & strSettingFile, map<CString,S_PathParam> & map_PathSetting)
{
   TiXmlDocument doc;
   char szXmlFile[MAX_PATH] = {};
   memset(szXmlFile, 0, sizeof(szXmlFile));
#ifdef _UNICODE
   QLCOMAPI.WCharToMByte(strSettingFile,szXmlFile,sizeof(szXmlFile)/sizeof(szXmlFile[0]));
#else
   strncpy_s(szXmlFile,(LPSTR)(LPCTSTR)strSettingFile, sizeof(szXmlFile) - 1);
#endif
   doc.LoadFile(szXmlFile,TIXML_ENCODING_UTF8);
   ParsePathSetting(doc, map_PathSetting);
}

void CFT_params::ParsePathSetting(TiXmlDocument & doc, map<CString, S_PathParam> &map_PathSetting)
{
   TiXmlHandle docHandle( &doc );
   TiXmlElement* pRootElement = 0;
   docHandle = TiXmlHandle(&doc);
   pRootElement = 0;
   pRootElement = docHandle.FirstChild( XML_PARAM_PATH_SETTTING_ROOT ).ToElement();//获取根节点
   if (pRootElement)
   {
      CString strKey,strPath;
      bool bZip = true,bDelZip = true,bUnZipFailRename = false;//默认所有都压缩 默认下载后删除压缩文件 默认解压失败后不重命名

      TiXmlElement* pSubItemElement = pRootElement->FirstChildElement(XML_PARAM_PATH_SETTTING_SUBITEM);
      while(NULL != pSubItemElement)
      {
         strKey = theApp.GetTinyXmlNodeString(pSubItemElement->FirstChildElement(XML_PARAM_PATH_SETTTING_KEY));
         strPath = theApp.GetTinyXmlNodeString(pSubItemElement->FirstChildElement(XML_PARAM_PATH_SETTTING_PATH));

         CString strTemp = theApp.GetTinyXmlNodeString(pSubItemElement->FirstChildElement(XML_PARAM_PATH_SETTTING_UPLOADZIP));
         if(!strTemp.IsEmpty())
            bZip = _ttoi(strTemp);
         strTemp = theApp.GetTinyXmlNodeString(pSubItemElement->FirstChildElement(XML_PARAM_PATH_SETTTING_DOWNDelZIP));
         if(!strTemp.IsEmpty())
            bDelZip = _ttoi(strTemp);
         strTemp = theApp.GetTinyXmlNodeString(pSubItemElement->FirstChildElement(XML_PARAM_PATH_SETTTING_UNZIPFAILRENAME));
         if(!strTemp.IsEmpty())
            bUnZipFailRename = _ttoi(strTemp);

         if (!strKey.IsEmpty())
         {//如果有重复的数据 则以后面的信息替换前面的数据
            map_PathSetting[strKey] = S_PathParam(strPath,bZip,bDelZip,bUnZipFailRename);
         }

         pSubItemElement = pSubItemElement->NextSiblingElement();
      }
   }
}

void CFT_params::CombinePathSetting(const map<CString,S_PathParam> & map_DefaultSetting,map<CString,S_PathParam> & map_UserSetting)
{
   for (auto it = map_DefaultSetting.begin();it != map_DefaultSetting.end();++it)
   {
      if(0 == map_UserSetting.count(it->first))
      {
         map_UserSetting[it->first] = it->second;
      }
   }
}

void CFT_params::InitParamInfoFromConfig(FileTrans_easy * pData,const CString & strWorkPath)
{
   //清空数据
   //配置文件的路径
   CString strSvrIniMsg = _T(""),strFileMgnIni = _T("");
   strSvrIniMsg= strWorkPath + STR_PATH_INI_CONFIGSVR;
   strFileMgnIni= strWorkPath + STR_PATH_INI_FILEMGN;
   //获取数据库 文件传输相关账户密码信息
   GetSvrIniMsg(strSvrIniMsg,pData);
   //获取登录人用户名 密码
   GetFileMgnIniMsg(strFileMgnIni,pData);
}

void CFT_params::GetSvrIniMsg( _In_ const CString & strSvrIniPath ,
   FileTrans_easy * pData)
{
   //清空所有信息
   pData->strDBIP          = _T("");//数据库地址+端口
   pData->strDBName        = _T("");//数据库名称
   pData->strDBID          = _T("");//数据库连接账户名
   pData->strDBPassword    = _T("");//数据库连接密码

   pData->strLocalTransIP  = _T("");//本地传输地址
   pData->strFTPFarTrans   = _T("");//FTP地址
   pData->strFTPFarlName   = _T("");//FTP登录名
   pData->strFTPFarPwd     = _T("");//FTP登录密码
   pData->bHttpMode        = FALSE;
   //默认不想服务器申请账户
   BOOL bApply = FALSE;
   if (strSvrIniPath.IsEmpty())
   {
      return;
   }

   //获取是否申请账号
   TCHAR temp[MAX_PATH] = {0};
   CString strTmp = _T("");
   //是否向开发商申请账号
   GetPrivateProfileString(STR_INI_CONFIGSVR_APP_SETTING,STR_INI_CONFIGSVR_KEY_APPLY,STR_INI_VALUE_EMPTY,temp,MAX_PATH,strSvrIniPath);
   strTmp.Format(_T("%s"),temp);
   if (STR_INI_VALUE_TRUE == strTmp)
   {
      bApply = TRUE;
   }

   //IP
   GetPrivateProfileString(STR_INI_CONFIGSVR_APP_SQLSVR,STR_INI_CONFIGSVR_KEY_SVR,STR_INI_VALUE_EMPTY,temp,MAX_PATH,strSvrIniPath);//IP
   strTmp.Format(_T("%s"),temp);
   strTmp.Trim();
   strTmp = theApp.OnDecodeStr(strTmp,FTP_WORD_PWD_KEY);

   int nPos = strTmp.Find(',');
   if (-1 != nPos)
   {
      pData->strFTPFarTrans = strTmp.Left(nPos);
      pData->strDBIP = strTmp;
   }
   else
   {
      pData->strFTPFarTrans = strTmp;
      pData->strDBIP.Format(_T("%s,%s"),strTmp,STR_MAP_VALUE_PORT_DB);//1433
   }

   GetPrivateProfileString(STR_INI_CONFIGSVR_APP_SQLSVR,STR_INI_CONFIGSVR_KEY_SVR_LOCAL,STR_INI_VALUE_EMPTY,temp,MAX_PATH,strSvrIniPath);//Addr+Port 127.0.0.1:21
   strTmp.Format(_T("%s"),temp);
   strTmp.Trim();
   pData->strLocalTransIP =  strTmp;

   GetPrivateProfileString(STR_INI_CONFIGSVR_APP_SQLSVR,STR_INI_CONFIGSVR_KEY_HTTPMODE,STR_INI_VALUE_FALSE,temp,MAX_PATH,strSvrIniPath);//HTTPMODE
   strTmp.Format(_T("%s"),temp);
   strTmp.Trim();
   pData->bHttpMode = STR_INI_VALUE_TRUE == strTmp;

   //传输库端口
   GetPrivateProfileString(STR_INI_CONFIGSVR_APP_SQLSVR,STR_INI_CONFIGSVR_KEY_FILEPORT,STR_INI_VALUE_EMPTY,temp,MAX_PATH,strSvrIniPath);//数据库

   strTmp.Format(_T("%s"),temp);
   strTmp.Trim();

   if (strTmp.IsEmpty())
   {
      strTmp = pData->bHttpMode ? pData->map_Default[STR_MAP_KEY_PORT_HTTP] : pData->map_Default[STR_MAP_KEY_PORT_FTP];//8088 : 21
   }
   else
   {
      strTmp = theApp.OnDecodeStr(strTmp,FTP_WORD_PWD_KEY);
   }

   if (!pData->strFTPFarTrans.IsEmpty())
   {
      pData->strFTPFarTrans += _T(":") + strTmp;
   }

   //数据库名称
   GetPrivateProfileString(STR_INI_CONFIGSVR_APP_SQLSVR,STR_INI_CONFIGSVR_KEY_DB,STR_INI_VALUE_EMPTY,temp,MAX_PATH,strSvrIniPath);//数据库

   strTmp.Format(_T("%s"),temp);
   strTmp.Trim();
   pData->strDBName = theApp.OnDecodeStr(strTmp,FTP_WORD_PWD_KEY);

   if (bApply)
   {
      //使用服务商提供的账户/数据库

      //账户密码相关：
      if(!pData->strDBName.IsEmpty())
      {//FTP的账户密码
         pData->strFTPFarlName = pData->strDBName + _T("321ql");
         pData->strFTPFarPwd   = pData->strDBName + _T("654321ql");
      }

      if (!pData->strDBName.IsEmpty())
      {//数据库的账户密码
         pData->strDBID       = pData->strDBName + _T("123QL");
         pData->strDBPassword = pData->strDBName + _T("123456QL");
      }
   }
   else
   {
      //默认账户
      pData->strFTPFarlName = FTP_DEFAULT_NAME;
      pData->strFTPFarPwd   = FTP_DEFAULT_PWD;

      GetPrivateProfileString(STR_INI_CONFIGSVR_APP_SQLSVR,STR_INI_CONFIGSVR_KEY_DBUID,STR_INI_VALUE_EMPTY,temp,MAX_PATH,strSvrIniPath);//ID

      strTmp.Format(_T("%s"),temp);
      strTmp.Trim();
      pData->strDBID = theApp.OnDecodeStr(strTmp,FTP_WORD_PWD_KEY);

      GetPrivateProfileString(STR_INI_CONFIGSVR_APP_SQLSVR,STR_INI_CONFIGSVR_KEY_DBPWD,STR_INI_VALUE_EMPTY,temp,MAX_PATH,strSvrIniPath);//PWD
      strTmp.Format(_T("%s"),temp);
      strTmp.Trim();
      pData->strDBPassword = theApp.OnDecodeStr(strTmp,FTP_WORD_PWD_KEY);
   }
}

void CFT_params::GetFileMgnIniMsg( _In_ const CString & strFileMgnIniPath 
   ,_Inout_ FileTrans_easy * pData)
{
   //清空信息
   pData->strUserID        = _T("");
   pData->strUserPassword  = _T("");

   if (strFileMgnIniPath.IsEmpty())
   {
      return;
   }

   TCHAR temp[MAX_PATH] = {0};
   CString strTmp = _T("");
   //从FileMgn.ini中获取登录的账户,密码

   CString strKey = _T("");
   switch(pData->nLoginType)
   {
   case En_Login_User:
      strKey = STR_INI_FILEMGN_APP_ACT;
      break;
   case En_Login_Custom:
      strKey = STR_INI_FILEMGN_APP_CUSACT;
      break;
   }

   GetPrivateProfileString(strKey,STR_INI_FILEMGN_KEY_USERID,STR_INI_VALUE_EMPTY,temp,MAX_PATH,strFileMgnIniPath);//数据库
   strTmp.Format(_T("%s"),temp);
   strTmp.Trim();
   pData->strUserID = theApp.OnDecodeStr(strTmp,FTP_WORD_PWD_KEY);

   GetPrivateProfileString(strKey,STR_INI_FILEMGN_KEY_USERPWD,STR_INI_VALUE_EMPTY,temp,MAX_PATH,strFileMgnIniPath);//数据库
   strTmp.Format(_T("%s"),temp);
   strTmp.Trim();
   pData->strUserPassword = theApp.OnDecodeStr(strTmp,FTP_WORD_PWD_KEY);
}