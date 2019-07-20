#include "StdAfx.h"
#include "FileTransferEx.h"


CFileTransferEx::CFileTransferEx( CString strWorkPath,HWND hProcessHwnd/* = NULL*/,S_FileTrans_LoginType nLoginType /*= En_Login_User*/ )
{
   m_pFileTrans = filetrans_easy_init(strWorkPath,nLoginType);
   filetrans_easy_setopt(m_pFileTrans,FTOPT_HWND,hProcessHwnd);
}

CFileTransferEx::~CFileTransferEx()
{
   FileTrans_easy_cleanup(m_pFileTrans);
}

void CFileTransferEx::Init(CString strOrderNo,int nFileType,int nWholeType )
{
   filetrans_easy_setopt(m_pFileTrans,FTOPT_ORDER,strOrderNo);
   m_strOrderNo = strOrderNo;
   CString strKey;
   strKey =GetStr(nWholeType,nFileType);
   filetrans_easy_setopt(m_pFileTrans,FTOPT_ACTION_KEY,strKey);
}

int CFileTransferEx::Upload(int nFlag /*= UNDESIGN_FLAG*/,BOOL bDelSrc /*= FALSE*/)
{
   return UploadToVersion(-1, nFlag, bDelSrc);
}

int CFileTransferEx::UploadToVersion(int nVersion, int nFlag ,BOOL bDelSrc)
{
   filetrans_easy_setopt(m_pFileTrans,FTOPT_VERSION,nVersion);
   filetrans_easy_setopt(m_pFileTrans,FTOPT_FLAG,nFlag);
   filetrans_easy_setopt(m_pFileTrans,FTOPT_DELSRC,bDelSrc);
   filetrans_easy_setopt(m_pFileTrans,FTOPT_ACTION,en_Action_Upload);

   vector<CString> vec_OneParam;
   int nIndex = 0,nCount = m_UploadList.GetCount();
   CString strParam;
   for (;nIndex < nCount;++nIndex)
   {
      strParam = m_UploadList.GetAt(m_UploadList.FindIndex(nIndex));
      vec_OneParam.push_back(strParam);
   }
   filetrans_easy_setopt(m_pFileTrans,FTOPT_VEC_ONEPARAM,vec_OneParam);

   return filetrans_easy_perform(m_pFileTrans);
}

int CFileTransferEx::DownLoad(int nFlag/* = UNDESIGN_FLAG*/)
{
   return DownLoadbyVersion(-1, nFlag);
}

int CFileTransferEx::DownLoadbyVersion(int nVersion, int nFlag/* = UNDESIGN_FLAG*/)
{
   filetrans_easy_setopt(m_pFileTrans,FTOPT_ACTION,en_Action_Down);
   filetrans_easy_setopt(m_pFileTrans,FTOPT_VERSION,nVersion);
   filetrans_easy_setopt(m_pFileTrans,FTOPT_FLAG,nFlag);

   vector<pair<CString,CString>> vec_TwoParam;
   for (auto it = m_DownMsg.begin();it != m_DownMsg.end();it++)
   {
      vec_TwoParam.push_back(make_pair( it->first, it->second));
   }
   filetrans_easy_setopt(m_pFileTrans,FTOPT_VEC_TWOPARAM,vec_TwoParam);

   return filetrans_easy_perform(m_pFileTrans);
}

int CFileTransferEx::DownLoadDir( CString strLocalDir,int nFlag /*= UNDESIGN_FLAG*/ )
{
   return DownLoadDir(strLocalDir,m_strOrderNo,nFlag);
}

int CFileTransferEx::DownLoadDir( CString strLocalDir,CString strOrderNo,int nFlag /*= UNDESIGN_FLAG*/ )
{
   return DownLoadDirByVersion(-1, strLocalDir, strOrderNo, nFlag);
}

int CFileTransferEx::DownLoadDirByVersion(int nVersion, CString strLocalDir, const CString &strOrderNo, int nFlag/* = UNDESIGN_FLAG*/)
{
   filetrans_easy_setopt(m_pFileTrans,FTOPT_VERSION,nVersion);
   filetrans_easy_setopt(m_pFileTrans,FTOPT_FLAG,nFlag);
   filetrans_easy_setopt(m_pFileTrans,FTOPT_ORDER,strOrderNo);

   vector<pair<CString,CString>> vecTwoParam;
   vecTwoParam.push_back(make_pair(_T(""),strLocalDir));//因为远程路径是自动生成的  因此第一个参数为空
   filetrans_easy_setopt(m_pFileTrans,FTOPT_VEC_TWOPARAM,vecTwoParam);

   filetrans_easy_setopt(m_pFileTrans,FTOPT_ACTION,en_Action_DownDir);
   int nRet = filetrans_easy_perform(m_pFileTrans);
   filetrans_easy_setopt(m_pFileTrans,FTOPT_ORDER,m_strOrderNo);
   return nRet;
}

int CFileTransferEx::DownLoadDirMsg(CString strLocalDir,int nFlag /*= UNDESIGN_FLAG*/,DWORD dwStyle /*= FS_DEFAULT*/)
{
   return DownLoadDirMsg(strLocalDir,m_strOrderNo,nFlag,dwStyle);
}

int CFileTransferEx::DownLoadDirMsg(CString strLocalDir,CString strOrderNo,int nFlag /*= UNDESIGN_FLAG*/,DWORD dwStyle /*= FS_DEFAULT*/)
{
   filetrans_easy_setopt(m_pFileTrans,FTOPT_ACTION,en_Action_DownDirMsg);

   filetrans_easy_setopt(m_pFileTrans,FTOPT_VERSION,-1);
   filetrans_easy_setopt(m_pFileTrans,FTOPT_FLAG,nFlag);
   filetrans_easy_setopt(m_pFileTrans,FTOPT_ORDER,strOrderNo);
   filetrans_easy_setopt(m_pFileTrans,FTOPT_STYLE,dwStyle);

   vector<pair<CString,CString>> vecTwoParam;
   vecTwoParam.push_back(make_pair(_T(""),strLocalDir));//因为远程路径是自动生成的  因此第一个参数为空
   filetrans_easy_setopt(m_pFileTrans,FTOPT_VEC_TWOPARAM,vecTwoParam);

   int nRet = filetrans_easy_perform(m_pFileTrans);
   filetrans_easy_setopt(m_pFileTrans,FTOPT_ORDER,m_strOrderNo);
   return nRet;
}

CString CFileTransferEx::GetErrorMsg( int nErrNo )
{
   CString strRet;
   strRet = filetrans_easy_geterror((FileTransCode)nErrNo);
   return strRet;
}

CString CFileTransferEx::GetVersion()
{
   CString strVersion;
   filetrans_easy_getinfo(m_pFileTrans,FILETRANSINFO_DLL_VERSION,&strVersion);
   return strVersion;
}

BOOL CFileTransferEx::IsHttpMode()
{
   BOOL bHttpMode;
   filetrans_easy_getinfo(m_pFileTrans,FILETRANSINFO_HTTP_MODE,&bHttpMode);
   return bHttpMode;
}

int CFileTransferEx::CheckOrderExit( CString strOrderNo )
{
   BOOL bExists = FALSE;

   filetrans_easy_setopt(m_pFileTrans,FTOPT_ORDER,strOrderNo);
   filetrans_easy_getinfo(m_pFileTrans,FILETRANSINFO_ORDER_EXISTS,&bExists);
   //需要还原单号
   filetrans_easy_setopt(m_pFileTrans,FTOPT_ORDER,m_strOrderNo);
   return bExists;
}

CString CFileTransferEx::GetSampleOrder(CString strOrderNo)
{
   CString strSampleOrder;
   filetrans_easy_setopt(m_pFileTrans,FTOPT_ORDER,strOrderNo);
   filetrans_easy_getinfo(m_pFileTrans,FILETRANSINFO_SAMPLE_ORDER,&strSampleOrder);
   filetrans_easy_setopt(m_pFileTrans,FTOPT_ORDER,m_strOrderNo);
   return strSampleOrder;
}

int CFileTransferEx::SetOrderSampleOrder( CString strOrderNo,CString strSampleNo )
{
   filetrans_easy_setopt(m_pFileTrans,FTOPT_ACTION,en_Action_SetSampleOrder);

   vector<CString> vec_OneParam;
   vec_OneParam.push_back(strSampleNo);
   filetrans_easy_setopt(m_pFileTrans,FTOPT_VEC_ONEPARAM,vec_OneParam);

   filetrans_easy_setopt(m_pFileTrans,FTOPT_ORDER,strOrderNo);
   int nRet = filetrans_easy_perform(m_pFileTrans);
   //还原单号
   filetrans_easy_setopt(m_pFileTrans,FTOPT_ORDER,m_strOrderNo);
   return nRet;
}

BOOL CFileTransferEx::CheckDBLogin()
{
   BOOL bLogin = FALSE;
   filetrans_easy_getinfo(m_pFileTrans,FILETRANSINFO_CAN_LOGIN,&bLogin);
   return bLogin;
}

BOOL CFileTransferEx::PopLogin()
{
   BOOL bLogin = FALSE;
   filetrans_easy_getinfo(m_pFileTrans,FILETRANSINFO_POPUPLOGIN,&bLogin);
   return bLogin;
}

void CFileTransferEx::SetHwnd(HWND hProcessHwnd)
{
   filetrans_easy_setopt(m_pFileTrans,FTOPT_HWND,hProcessHwnd);
}

void CFileTransferEx::SetOrderInfo( CString strOrderNo )
{
   m_strOrderNo = strOrderNo;
   filetrans_easy_setopt(m_pFileTrans,FTOPT_ORDER,strOrderNo);
}

void CFileTransferEx::SetSize( CString strSize )
{
   m_strSize = strSize;
   filetrans_easy_setopt(m_pFileTrans,FTOPT_SIZE,strSize);
}

int CFileTransferEx::DownLoadByExt( CString strLocalDir,CString strOrderNo,CString strExtension,int nFlag /*= UNDESIGN_FLAG*/,BOOL bDir /*= FALSE*/,DWORD dwStyle /*= FS_DEFAULT*/ )
{
   filetrans_easy_setopt(m_pFileTrans,FTOPT_ORDER,strOrderNo);
   filetrans_easy_setopt(m_pFileTrans,FTOPT_ACTION,en_Action_DownByEx);
   filetrans_easy_setopt(m_pFileTrans,FTOPT_FLAG,nFlag);

   vector<pair<CString,CString>> vec_TwoParam;
   vec_TwoParam.push_back(make_pair(strExtension,strLocalDir));
   filetrans_easy_setopt(m_pFileTrans,FTOPT_VEC_TWOPARAM,vec_TwoParam);

   filetrans_easy_setopt(m_pFileTrans,FTOPT_TRAVERSINGDIR,bDir);
   filetrans_easy_setopt(m_pFileTrans,FTOPT_STYLE,dwStyle);

   int nRet = filetrans_easy_perform(m_pFileTrans);

   //需要还原相关单号
   filetrans_easy_setopt(m_pFileTrans,FTOPT_ORDER,m_strOrderNo);
   return nRet;
}

int CFileTransferEx::Del(int nFlag/* = UNDESIGN_FLAG*/)
{
   filetrans_easy_setopt(m_pFileTrans,FTOPT_ACTION,en_Action_Delete);
   filetrans_easy_setopt(m_pFileTrans,FTOPT_FLAG,nFlag);

   vector<CString> vecOneParam;
   int nIndex = 0,nCount = m_DelList.GetCount();
   for (nIndex = 0;nIndex < nCount;nIndex++)
   {
      auto str = m_DelList.GetAt(m_DelList.FindIndex(nIndex));
      vecOneParam.push_back(str);
   }
   filetrans_easy_setopt(m_pFileTrans,FTOPT_VEC_ONEPARAM,vecOneParam);

   return filetrans_easy_perform(m_pFileTrans);
}

int CFileTransferEx::GetList( int nFlag /*= UNDESIGN_FLAG*/ )
{
   return GetListByVersion(-1, nFlag);
}

int CFileTransferEx::GetListByVersion(int nVersion, int nFlag/* = UNDESIGN_FLAG*/)
{
   filetrans_easy_setopt(m_pFileTrans,FTOPT_ACTION,en_Action_GetList);
   filetrans_easy_setopt(m_pFileTrans,FTOPT_FLAG,nFlag);
   filetrans_easy_setopt(m_pFileTrans,FTOPT_VERSION,nVersion);

   return filetrans_easy_perform(m_pFileTrans);
}

int CFileTransferEx::GetListEx( int nFlag /*= UNDESIGN_FLAG*/,DWORD dwStyle /*= FS_DEFAULT*/ )
{
   filetrans_easy_setopt(m_pFileTrans,FTOPT_FLAG,nFlag);
   filetrans_easy_setopt(m_pFileTrans,FTOPT_STYLE,dwStyle);

   filetrans_easy_setopt(m_pFileTrans,FTOPT_ACTION,en_Action_GetListEx);
   return filetrans_easy_perform(m_pFileTrans);
}

int CFileTransferEx::DelDir( int nFlag /*= UNDESIGN_FLAG*/ )
{
   return DelDir(m_strOrderNo,nFlag);
}

int CFileTransferEx::DelDir( CString strOrderNo, int nFlag /*= UNDESIGN_FLAG*/ )
{
   filetrans_easy_setopt(m_pFileTrans,FTOPT_ORDER,strOrderNo);
   filetrans_easy_setopt(m_pFileTrans,FTOPT_ACTION,en_Action_DeleteDir);
   filetrans_easy_setopt(m_pFileTrans,FTOPT_FLAG,nFlag);

   int nRet = filetrans_easy_perform(m_pFileTrans);
   filetrans_easy_setopt(m_pFileTrans,FTOPT_ORDER,m_strOrderNo);
   return nRet;
}

int CFileTransferEx::IsFileExist(CString strFileName)
{
   vector<CString> vecOneParam;
   vecOneParam.push_back(strFileName);
   filetrans_easy_setopt(m_pFileTrans,FTOPT_VEC_ONEPARAM,vecOneParam);
   BOOL bExists = FALSE;
   auto nRetCode = filetrans_easy_getinfo(m_pFileTrans,FILETRANSINFO_FILE_EXISTS,&bExists);

   //之前的返回值中 1 表示存在  0 表示不存在  其他表示错误
   return bExists ? 1 : (nRetCode == FILETRANS_OK ? 0 : nRetCode);
}

int CFileTransferEx::BackupFile(const CString &strVersionName, CString strOrderNo, int nFlag/* = UNDESIGN_FLAG*/,BOOL bMove /*= FALSE*/)
{
   //根据文件类型判断是移动还是拷贝  
   filetrans_easy_setopt(m_pFileTrans,FTOPT_ORDER,strOrderNo);
   filetrans_easy_setopt(m_pFileTrans,FTOPT_FLAG,nFlag);
   filetrans_easy_setopt(m_pFileTrans,FTOPT_VERSION,-1);//版本应强制为-1
   filetrans_easy_setopt(m_pFileTrans,FTOPT_ACTION, bMove/*移动还是拷贝*/ ? en_Action_BackupFile_Move : en_Action_BackupFile_Copy);

   //需要备份的文件为工艺 制版 上机三种文件
   vector<pair<CString,CString>> vec_TwoParam;
   vec_TwoParam.push_back(make_pair(_T("File_Process"),_T("File_BackUp_Process")));
   vec_TwoParam.push_back(make_pair(_T("File_Pattern"),_T("File_BackUp_Pattern")));
   vec_TwoParam.push_back(make_pair(_T("File_Mac"),_T("File_BackUp_Mac")));
   filetrans_easy_setopt(m_pFileTrans,FTOPT_VEC_TWOPARAM, vec_TwoParam);

   filetrans_easy_setopt(m_pFileTrans,FTOPT_DST_VERSION, _ttoi(strVersionName));
   filetrans_easy_setopt(m_pFileTrans,FTOPT_DST_SIZE, _T(""));//尺码为空的
   filetrans_easy_setopt(m_pFileTrans,FTOPT_DST_ORDER, strOrderNo);

   int nRet = filetrans_easy_perform(m_pFileTrans);

   //还原一些相关的信息
   filetrans_easy_setopt(m_pFileTrans,FTOPT_ORDER,m_strOrderNo);

   return nRet;
}

int CFileTransferEx::CopyVersionToNewCreatedOne(const CString &strNewVersionName, 
   const CString &strOldVersionName, CString strOrderNo, int nFlag/* = UNDESIGN_FLAG*/)
{
   //以前的拷贝为
   //当前版本 (有尺码) -> 新版本(无尺码)
   //旧版本（无尺码）->当前版本（有尺码）

   //当前拷贝为
   //当前版本 (版本-1 尺码： FTOPT_SIZE) -> 新版本 DST_VERSION 有尺码 FTOPT_DST_SIZE
   //旧版本 ( _VERSION 尺码： FTOPT_DST_SIZE)  -> 当前版本 ( 有尺码 FTOPT_SIZE)

   filetrans_easy_setopt(m_pFileTrans,FTOPT_ACTION, en_Action_CopyVersionToCurVersion);
   filetrans_easy_setopt(m_pFileTrans,FTOPT_ORDER,strOrderNo);
   filetrans_easy_setopt(m_pFileTrans,FTOPT_VERSION,_ttoi(strOldVersionName));
   filetrans_easy_setopt(m_pFileTrans,FTOPT_FLAG,nFlag);

   filetrans_easy_setopt(m_pFileTrans,FTOPT_DST_ORDER,strOrderNo);
   filetrans_easy_setopt(m_pFileTrans,FTOPT_DST_VERSION,_ttoi(strNewVersionName));
   //目标不设尺码  

   vector<pair<CString,CString>> vec_TwoParam;
   vec_TwoParam.push_back(make_pair(_T("File_Process"),_T("File_BackUp_Process")));
   vec_TwoParam.push_back(make_pair(_T("File_Pattern"),_T("File_BackUp_Pattern")));
   vec_TwoParam.push_back(make_pair(_T("File_Mac"),_T("File_BackUp_Mac")));
   filetrans_easy_setopt(m_pFileTrans,FTOPT_VEC_TWOPARAM, vec_TwoParam);

   int nRet = filetrans_easy_perform(m_pFileTrans);
   filetrans_easy_setopt(m_pFileTrans,FTOPT_ORDER,m_strOrderNo);
   filetrans_easy_setopt(m_pFileTrans,FTOPT_DST_ORDER,_T(""));
   filetrans_easy_setopt(m_pFileTrans,FTOPT_DST_VERSION,-1);
   return nRet;
}

int CFileTransferEx::RemoteCopyFile(const CString &sOrgOrder, int nOrgVersion, int nOrgFileType, const CString &sOrgSize,  
   const CString &sDstOrder, int nDstVersion, int nDstFileType,  const CString &sDstSize, 
   int nFlag /*= UNDESIGN_FLAG*/)
{
   return RemoteCopyFile(sOrgOrder,nOrgVersion,nOrgFileType,sOrgSize,FTP_WHOLE_TYPE_FILE,
      sDstOrder,nDstVersion,nDstFileType,sDstSize,FTP_WHOLE_TYPE_FILE,nFlag);
}

int CFileTransferEx::RemoteCopyFile(const CString &sOrgOrder, int nOrgVersion, int nOrgFileType, const CString &sOrgSize,int nOrgWholeType ,  
   const CString &sDstOrder, int nDstVersion, int nDstFileType,  const CString &sDstSize ,int nDstWholeType  , 
   int nFlag /*= UNDESIGN_FLAG*/)
{
   CString strKey;
   filetrans_easy_setopt(m_pFileTrans,FTOPT_ORDER,sOrgOrder);
   filetrans_easy_setopt(m_pFileTrans,FTOPT_SIZE,sOrgSize);
   filetrans_easy_setopt(m_pFileTrans,FTOPT_VERSION,nOrgVersion);
   filetrans_easy_setopt(m_pFileTrans,FTOPT_ACTION,en_Action_Copy);
   filetrans_easy_setopt(m_pFileTrans,FTOPT_FLAG,nFlag);
   strKey =GetStr(nOrgWholeType,nOrgFileType);
   filetrans_easy_setopt(m_pFileTrans,FTOPT_ACTION_KEY,strKey);

   filetrans_easy_setopt(m_pFileTrans,FTOPT_DST_ORDER,sDstOrder);
   filetrans_easy_setopt(m_pFileTrans,FTOPT_DST_SIZE,sDstSize);
   filetrans_easy_setopt(m_pFileTrans,FTOPT_DST_VERSION,nDstVersion);
   strKey =GetStr(nDstWholeType,nDstFileType);
   filetrans_easy_setopt(m_pFileTrans,FTOPT_DST_ACTION_KEY,strKey);

   int nRet = filetrans_easy_perform(m_pFileTrans);
   //还原数据
   filetrans_easy_setopt(m_pFileTrans,FTOPT_ORDER,m_strOrderNo);
   filetrans_easy_setopt(m_pFileTrans,FTOPT_DST_ORDER,_T(""));
   filetrans_easy_setopt(m_pFileTrans,FTOPT_DST_SIZE,_T(""));
   filetrans_easy_setopt(m_pFileTrans,FTOPT_DST_VERSION,-1);
   filetrans_easy_setopt(m_pFileTrans,FTOPT_DST_ACTION_KEY,_T(""));

   return nRet;
}


CString CFileTransferEx::GetStr(int nWholeType, int nFileType)
{
   CString strRet = _T("");

   switch(nWholeType)
   {
   case FTP_WHOLE_TYPE_FILE:
      {
         //处理普通文件
         switch(nFileType)
         {
            //根据当前文件类型获取对应的模块路径
         case FTP_MODE_TYPE_PATTERN:
            strRet = _T("File_Pattern");
            break;
         case FTP_MODE_TYPE_PROCESS:
            strRet = _T("File_Process");
            break;
         case FTP_MODE_TYPE_DESIGN:
            strRet = _T("File_Design");
            break;
         case FTP_MODE_TYPE_ONLINE:
            strRet = _T("File_Mac");
            break;
         case FTP_MODE_TYPE_OTHER:
            strRet = _T("File_Order");
            break;
         case FTP_MODE_TYPE_SIZE:
            strRet = _T("File_Thc");
            break;
         case FTP_MODE_TYPE_PIC:
            strRet = _T("File_Picture");
            break;
         case FTP_MODE_TYPE_PIC_STYLE:
            strRet = _T("File_StyleImage");
            break;
         case FTP_MODE_TYPE_CHATFILE:
            strRet = _T("File_ChatFile");
            break;
         case FTP_MODE_TYPE_PIC_PRODETAIL:
            strRet = _T("File_ImgProDetail");
            break;
         case FTP_MODE_TYPE_PIC_MODEL:
            strRet = _T("File_ImgModel");
            break;
         default:
            break;
         }
      }
      break;
   case FTP_WHOLE_TYPE_LIB:
      //处理库文件
      {
         switch(nFileType)
         {
         case FTP_LIB_TYPE_BMP:
            strRet = _T("Lib_Bmp");
            break;
         case FTP_LIB_TYPE_STYLE:
            strRet = _T("Lib_Style");
            break;
         case FTP_LIB_TYPE_PROCESS:
            strRet = _T("Lib_Process");
            break;
         case FTP_LIB_TYPE_DENSITY:
            strRet = _T("Lib_Density");
            break;
         case FTP_LIB_TYPE_COMPONENT:
            strRet = _T("Lib_Component");
            break;
         case FTP_LIB_TYPE_PATTERNCONFIG:
            strRet = _T("Lib_PatternConfig");
            break;
         case FTP_LIB_TYPE_MODFILE:
            strRet = _T("Lib_Modfile");
            break;
         default:
            break;
         }
      }
      break;
   case FTP_WHOLE_TYPE_EXCHANGE:
      {
         strRet = _T("Other_Exchange");
      }
      break;
   case FTP_WHOLE_TYPE_COMMUNICATION:
      {
         strRet = _T("Other_GlobalChat");
      }
      break;
   case FTP_WHOLE_TYPE_WEB:
      {
         strRet = _T("Other_WebImage");
      }
      break;
   default:
      break;
   }

   return strRet;
}