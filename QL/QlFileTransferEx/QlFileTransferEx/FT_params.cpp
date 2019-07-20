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
   pData->nFlag = UNDESIGN_FLAG;//����ʱ��������ϢĬ��Ϊ0

   pData->bDelSrcFile = FALSE;//Ĭ�ϲ�ɾ��Դ�ļ�
   pData->hProcessWnd = NULL;//Ĭ�Ͻ�����Ϣ���Ϊ��
   pData->nAction = en_Action_UnDefine;//������ΪĬ��Ϊδ����
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

   //��ʼ��Ĭ��������Ϣ ��������ļ��Ƿ���� ����������� �����Դ�����ɵ����·����
   InitConfigInfo(pData,strWorkPath);

   //�ӱ���·���ж�ȡ�����Ϣ����ʼ������
   InitParamInfoFromConfig(pData,strWorkPath);
}

void CFT_params::InitConfigInfo(FileTrans_easy * pData,const CString & strWorkPath)
{
   
   pData->map_Default[STR_MAP_KEY_PORT_FTP] = STR_MAP_VALUE_PORT_FTP;
   pData->map_Default[STR_MAP_KEY_PORT_HTTP] = STR_MAP_VALUE_PORT_HTTP;

   //��������ļ��е��ļ��������ȡ���ļ� �����ͷ���Դ�ļ���ȥ
   QLCOMAPI.MakeDirByCheck(strWorkPath + STR_PATH_CONFIG);
   //Ĭ�϶˿ڵ�xml
   CString strSettingFile = strWorkPath + STR_PATH_CONFIG_SETTING;
   if (!PathFileExists(strSettingFile))
   {//����ļ�������  �ͷ���Դ�ļ���ȥ
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
   pRootElement = docHandle.FirstChild( XML_PARAM_DEFAULTPORT_SETTTING_ROOT ).ToElement();//��ȡ���ڵ�
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

   //·�����ò�����Ĭ�ϲ��� ���û������ �Ǿ���û������  ���е�keyֵӦ��ʵ��Ӧ��ģ��һһ��Ӧ

   //��ȡ·����ص���Ϣ
   strSettingFile = strWorkPath + STR_PATH_CONFIG_PATH;
   if (!PathFileExists(strSettingFile))
   {//����ļ�������  �ͷ���Դ�ļ���ȥ
      theApp.FreeResourceToFile(IDR_XML_PATH_SETTING,STR_RESOURCE_TYPE_XML,strSettingFile);
   }

   //����Ĭ������
   CString strDefaultSettingPath = strWorkPath + STR_PATH_CONFIG_PATH_DEFAULT;
   DeleteFile(strDefaultSettingPath);
   theApp.FreeResourceToFile(IDR_XML_PATH_SETTING,STR_RESOURCE_TYPE_XML,strDefaultSettingPath);
   map<CString,S_PathParam> map_ResourceData;//��Դ�е�����
   ParsePathSetting_byFile(strDefaultSettingPath,map_ResourceData);
   DeleteFile(strDefaultSettingPath);

   ParsePathSetting_byFile(strSettingFile,pData->map_Key_Path);

   //����Ĭ�����ݺ��û���������
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
   pRootElement = docHandle.FirstChild( XML_PARAM_PATH_SETTTING_ROOT ).ToElement();//��ȡ���ڵ�
   if (pRootElement)
   {
      CString strKey,strPath;
      bool bZip = true,bDelZip = true,bUnZipFailRename = false;//Ĭ�����ж�ѹ�� Ĭ�����غ�ɾ��ѹ���ļ� Ĭ�Ͻ�ѹʧ�ܺ�������

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
         {//������ظ������� ���Ժ������Ϣ�滻ǰ�������
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
   //�������
   //�����ļ���·��
   CString strSvrIniMsg = _T(""),strFileMgnIni = _T("");
   strSvrIniMsg= strWorkPath + STR_PATH_INI_CONFIGSVR;
   strFileMgnIni= strWorkPath + STR_PATH_INI_FILEMGN;
   //��ȡ���ݿ� �ļ���������˻�������Ϣ
   GetSvrIniMsg(strSvrIniMsg,pData);
   //��ȡ��¼���û��� ����
   GetFileMgnIniMsg(strFileMgnIni,pData);
}

void CFT_params::GetSvrIniMsg( _In_ const CString & strSvrIniPath ,
   FileTrans_easy * pData)
{
   //���������Ϣ
   pData->strDBIP          = _T("");//���ݿ��ַ+�˿�
   pData->strDBName        = _T("");//���ݿ�����
   pData->strDBID          = _T("");//���ݿ������˻���
   pData->strDBPassword    = _T("");//���ݿ���������

   pData->strLocalTransIP  = _T("");//���ش����ַ
   pData->strFTPFarTrans   = _T("");//FTP��ַ
   pData->strFTPFarlName   = _T("");//FTP��¼��
   pData->strFTPFarPwd     = _T("");//FTP��¼����
   pData->bHttpMode        = FALSE;
   //Ĭ�ϲ�������������˻�
   BOOL bApply = FALSE;
   if (strSvrIniPath.IsEmpty())
   {
      return;
   }

   //��ȡ�Ƿ������˺�
   TCHAR temp[MAX_PATH] = {0};
   CString strTmp = _T("");
   //�Ƿ��򿪷��������˺�
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

   //�����˿�
   GetPrivateProfileString(STR_INI_CONFIGSVR_APP_SQLSVR,STR_INI_CONFIGSVR_KEY_FILEPORT,STR_INI_VALUE_EMPTY,temp,MAX_PATH,strSvrIniPath);//���ݿ�

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

   //���ݿ�����
   GetPrivateProfileString(STR_INI_CONFIGSVR_APP_SQLSVR,STR_INI_CONFIGSVR_KEY_DB,STR_INI_VALUE_EMPTY,temp,MAX_PATH,strSvrIniPath);//���ݿ�

   strTmp.Format(_T("%s"),temp);
   strTmp.Trim();
   pData->strDBName = theApp.OnDecodeStr(strTmp,FTP_WORD_PWD_KEY);

   if (bApply)
   {
      //ʹ�÷������ṩ���˻�/���ݿ�

      //�˻�������أ�
      if(!pData->strDBName.IsEmpty())
      {//FTP���˻�����
         pData->strFTPFarlName = pData->strDBName + _T("321ql");
         pData->strFTPFarPwd   = pData->strDBName + _T("654321ql");
      }

      if (!pData->strDBName.IsEmpty())
      {//���ݿ���˻�����
         pData->strDBID       = pData->strDBName + _T("123QL");
         pData->strDBPassword = pData->strDBName + _T("123456QL");
      }
   }
   else
   {
      //Ĭ���˻�
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
   //�����Ϣ
   pData->strUserID        = _T("");
   pData->strUserPassword  = _T("");

   if (strFileMgnIniPath.IsEmpty())
   {
      return;
   }

   TCHAR temp[MAX_PATH] = {0};
   CString strTmp = _T("");
   //��FileMgn.ini�л�ȡ��¼���˻�,����

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

   GetPrivateProfileString(strKey,STR_INI_FILEMGN_KEY_USERID,STR_INI_VALUE_EMPTY,temp,MAX_PATH,strFileMgnIniPath);//���ݿ�
   strTmp.Format(_T("%s"),temp);
   strTmp.Trim();
   pData->strUserID = theApp.OnDecodeStr(strTmp,FTP_WORD_PWD_KEY);

   GetPrivateProfileString(strKey,STR_INI_FILEMGN_KEY_USERPWD,STR_INI_VALUE_EMPTY,temp,MAX_PATH,strFileMgnIniPath);//���ݿ�
   strTmp.Format(_T("%s"),temp);
   strTmp.Trim();
   pData->strUserPassword = theApp.OnDecodeStr(strTmp,FTP_WORD_PWD_KEY);
}