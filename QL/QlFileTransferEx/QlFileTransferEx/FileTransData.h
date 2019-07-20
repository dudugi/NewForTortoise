/*************************************************
// <文件>: FileTransData.h
// <说明>: 存储传输库数据的类
// <作者>: wangzl
// <日期>: 2019/02/27
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 
#pragma once
#include "FileTransferDef.inl"


#define TypeNameLength	20
//定义文件传输的
typedef struct CloudLogMsg
{
   char strLocalPath[MAX_PATH];
   char strSourceFileName[MAX_PATH];
   char strTypeName[TypeNameLength];
}sz_CloudLogMsg;

//定义文件传输的
typedef struct TRANSFER_FILE_MSG
{
   char strFarPath[MAX_PATH];
   char strLocalPath[MAX_PATH];
   char strExtension[10];
   TRANSFER_FILE_MSG()
   {
      memset(strFarPath,0,MAX_PATH);
      memset(strLocalPath,0,MAX_PATH);
      memset(strExtension,0,10);
   }
}TransferFileMsg;

typedef struct TRANSFER_MSG
{
   char strIP[50];
   char strName[50];
   char strPwd[50];

   char strDBIP[50];
   char strDB[50];
   char strDBID[50];
   char strDBPWD[50];
   char strUserID[50];

   HWND hWnd;

   TransferFileMsg* pTransFileMsg;//文件传输信息相关的结构体 包含本地路径 远程路径  文件扩展名
   int nTransFileNum;

   char strFarPath[MAX_PATH];//上传时的远程路径  每次上传文件时对创建一次文件夹

   char strOrderNo[50];

   int nSpecFlag;//特殊标识，用于区分接收到的消息，可以不设置
   BOOL bDelSrc;//上传文件时是否删除源文件的标识
   BOOL bDir;//是否遍历文件夹的标识 (根据后缀名下载文件使用)
   int nLoginType;//根据登录方式不同写日志时查询不同的表  
   DWORD dwStyle;//线程通用属性

   BOOL bUseHttp;//是否使用HTTP模式

   bool bZip;//上传时是否压缩的参数 仅上传使用
   bool bDelZip;//下载时是否删除压缩源文件的参数
   bool bUnZipFailRename;//解压失败重命名
   //回调函数
   File_trans_upload_callback funcUpload;//上传
   File_trans_delete_callback funcDelete;//删除
   File_trans_before_download_callback funcBeforeDownload;//下载之前的回调函数
   void * pUserCallBackData;

   TRANSFER_MSG()
   {
      memset(strIP,0,50);
      memset(strName,0,50);
      memset(strPwd,0,50);

      memset(strDBIP,0,50);
      memset(strDB,0,50);
      memset(strDBID,0,50);
      memset(strDBPWD,0,50);
      memset(strUserID,0,50);
      hWnd = nullptr;
      pTransFileMsg = nullptr;
      nTransFileNum = 0;
      memset(strFarPath,0,MAX_PATH);

      memset(strOrderNo,0,50);
      nSpecFlag = 0;//特殊标识，用于区分接收到的消息，可以不设置
      bDelSrc = FALSE;//上传文件时是否删除源文件的标识
      bDir = FALSE;//是否遍历文件夹的标识 (根据后缀名下载文件使用)
      nLoginType =0;//根据登录方式不同写日志时查询不同的表  
      dwStyle = FS_DEFAULT;//线程通用属性

      bUseHttp = FALSE;

      bZip = true;
      bDelZip = true;
      bUnZipFailRename = false;
      funcUpload = NULL;
      funcDelete = NULL;
      funcBeforeDownload = NULL;
      pUserCallBackData = NULL;
   }
}TransferMsg; 

typedef struct TRANSFER_LIST_MSG
{
   char strIP[50];
   char strName[50];
   char strPwd[50];
   HWND hWnd;
   char strListDir[MAX_PATH];
   int nSpecFlag;
   DWORD dwStyle;//线程通用属性
   BOOL bUseHttp;//是否使用HTTP模式
   TRANSFER_LIST_MSG()
   {
      memset(strIP,0,50);
      memset(strName,0,50);
      memset(strPwd,0,50);
      hWnd = nullptr;
      memset(strListDir,0,MAX_PATH);
      nSpecFlag = 0;
      dwStyle = FS_DEFAULT;
      bUseHttp = FALSE;
   }
}TransferListMsg; 

struct S_PathParam{
   CString m_strPath;
   bool m_bZip;
   bool m_bDelZip;
   bool m_bUnZipFailRename;
   S_PathParam(const CString & strFilePath = _T(""),bool bNeedZip = true,bool bDelZip = true,bool bUnZipFailRename = false)
   {
      m_strPath = strFilePath;
      m_bZip = bNeedZip;
      m_bDelZip = bDelZip;
      m_bUnZipFailRename = bUnZipFailRename;
   }
};

struct FileTrans_easy {
   CString strWorkPath;//安装包所在路径

   //数据库相关参数
   CString strDBIP               ;//数据库地址 + 端口
   CString strDBName             ;//数据库名称
   CString strDBID               ;//数据库连接账号
   CString strDBPassword         ;//数据库连接密码
   //用户相关参数
   CString strUserID             ;//登录人ID (用户表ID  申请账户时  一般为 数据库名称+123QL
   CString strUserPassword       ;//登录人密码 (用户表密码 申请账户时 一般为 数据库名称+123456QL
   //文件传输相关参数
   CString strLocalTransIP       ;//本地文件传输地址SVRLOCAL
   CString strFTPFarTrans        ;//远程文件传输地址 （根据规则生成的地址 一般和数据库地址一致
   CString strFTPFarlName        ;//远程文件传输链接的账户名 （根据规则生成的用户名 一般为 数据库名称+321ql 不申请账户时为默认数据 FTP_DEFAULT_NAME qildoc
   CString strFTPFarPwd          ;//远程文件传输链接的密码 （根据规则生成的密码 一般为 数据库名称+654321ql 不申请账户时为默认数据 FTP_DEFAULT_PWD qildocqildoc
   //消息相关参数
   HWND hProcessWnd              ;//用于接收消息的句柄
   int nFlag                     ;//传输消息所对应的标志
   //文件服务相关配置信息
   FILETRANSACTION nAction       ;//操作的行为
   BOOL bDelSrcFile              ;//上传时是否删除的文件的参数 仅上传适用

   CString strOrderNo            ;//订单号
   CString strSize               ;//尺码
   int nVersion                  ;//版本号 （备份时使用  不涉及文件备份时为-1
   CString strAction_ParamKey    ;//行为路径所对应的key

   //目标相关配置 仅当拷贝有用
   CString strDstOrderNo         ;//目标订单号
   CString strDstSize            ;//目标尺码
   int nDstVersion               ;//目标版本号 （备份时使用  不涉及文件备份时为-1
   CString strDstAction_ParamKey ;//目标行为路径所对应的key
   //其他参数
   BOOL bHttpMode                ;//是否使用HTTP模式的参数
   BOOL bPtLog                   ;//是否打印日志
   int nLoginType                ;//登录的类型 类型同S_FILETRANS_LOGINTYPE

   BOOL bTraversingDir           ;//是否遍历文件夹的参数 仅下载文件夹时使用
   DWORD dwStyle                 ;//线程通用属性  目前用途 遍历子文件夹时不生成相关文件夹

   //操作列表
   vector<CString> vec_ActParam_OneParam;//一个参数的操作列表 用于上传 删除
   //两个参数的操作列表 用于下载 拷贝（下载：key1_远程文件名,key2_本地文件的绝对路径 包含文件名
   //（拷贝：key1_远程源文件名 key2_远程目标文件名
   vector<pair<CString,CString>> vec_ActParam_TwoParam;
   //配置文件的信息
   map<CString,CString> map_Default;//一些默认的数据 如 FTP默认端口 HTTP默认端口一类 key为关键词 value为默认数据
   map<CString,S_PathParam> map_Key_Path;//key值与对应的上传路径 value中包含可替换字符 如$OrderNo$等 （key为关键词 value为路径+是否压缩 默认压缩

   //回调函数
   File_trans_upload_callback funcUpload;//上传
   File_trans_delete_callback funcDelete;//删除
   File_trans_before_download_callback funcBeforeDownload;//下载之前的回调函数

   void * pUserCallBackData;
};



