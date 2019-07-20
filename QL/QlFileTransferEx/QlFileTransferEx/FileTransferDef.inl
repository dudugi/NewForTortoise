/*************************************************
// <文件>: FileTransferDef.inl
// <说明>: 传输库中的一些声明
// <作者>: wangzl
// <日期>: 2019/02/28
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 
#pragma once
using namespace std;
#include <vector>


#ifndef QLFILTTRANS_MARK
#define QLFILTTRANS_MARK
#endif

#ifndef QLFILETRANS_VERSION
#define QLFILETRANS_VERSION		_T("0.0.1.0")//关于数据库接口的调整避免工艺制版接口不一致导致的崩溃问题
#endif

#define FTP_TYPE_FILE 0		//文件
#define FTP_TYPE_DIR  1		//文件夹
#define FTP_TYPE_OTHER	2	//其它

//接收上传下载当前文件进度的消息
#define WM_QL_FTP_PROGRESS		WM_USER + 0x1000
//用于接收当前上传的文件名称的消息
#define WM_QL_FTP_UPLOAD		WM_USER + 0x1001
//用于接收当前删除的文件名称的消息
#define WM_QL_FTP_DEL			WM_USER + 0x1002
//用于接收当前下载的文件名称的消息
#define WM_QL_FTP_DOWNLOAD		WM_USER + 0x1003
//用于接收当前创建文件夹结果的消息
#define WM_QL_FTP_MKDIR			WM_USER + 0x1004
//用于接收当前获取文件列表结果的消息
#define WM_QL_FTP_GETLIST		WM_USER + 0x1005
//用于接收当前删除文件夹结果的消息
#define WM_QL_FTP_DELDIR		WM_USER + 0x1006
//用于接收当前删除文件夹结果的消息
#define WM_QL_FTP_DOWNDIR		WM_USER + 0x1007
//用于接收根据文件扩展名下载文件的消息
#define WM_QL_FTP_DOWNBYEX		WM_USER + 0x1008
//下载文件夹时各个文件下载成功失败的消息
#define WM_QL_FTP_DOWNDIRMSG	WM_USER + 0X1009
//用于接收上传文件夹结果的消息
#define WM_QL_FTP_UPDIR			WM_USER + 0X1010
//上传文件夹时各个文件上传结果的消息
#define WM_QL_FTP_UPDIRMSG		WM_USER + 0X1011
//根据后缀名下载文件时 对每个文件的下载状态给使用者一个消息反馈
#define WM_QL_FTP_DOWNBYEXMSG	WM_USER + 0X1012
//用于备份订单文件的消息
#define WM_QL_FTP_BACKUPFILE  WM_USER + 0x1013
#define WM_QL_FTP_BACKUPFILEMSG  WM_USER + 0x1014
#define WM_QL_FTP_COPY_VERSION_TO_NEW  (WM_USER + 0x1015)

#define FTP_MSG_MAX_COUNT		0x1015		//用于其它模块设置消息时附加的参数  与上面的消息同步添加 

//未定义的标志，在调用本类时若没有设置任何信号，则在发送消息时返回此标识
#define UNDESIGN_FLAG	0

//线程处理行为
#define FTP_ACTION_START			0//操作开始
#define FTP_ACTION_SUC				1//操作成功
#define FTP_ACTION_FAIL				2//操作失败
#define FTP_ACTION_OPENFAIL			3//打开连接失败
#define FTP_ACTION_NOFILE			4//文件不存在的标识 仅针对单文件下载生效
#define FTP_ACTION_DISCONNECTED		5//与主机连接失败

#define FTP_DEFAULT_NAME	_T("qildoc")
#define FTP_DEFAULT_PWD		_T("qildocqildoc")

//登录界面变量同步更新
typedef enum S_FileTrans_LoginType{
   En_Login_Null = -1,//没有员工登录（不进行数据库操作）
   En_Login_User = 0,//员工登录
   En_Login_Custom,//客户登录
}S_FILETRANS_LOGINTYPE;

//转换字符串到文件属性相关
typedef struct s_FILEMSG{
   //文件类型0-文件夹 1-文件 2-其它
   int nFileType;
   //文件权限,类型777  8进制 rwx类型
   int nFileLimit;
   //连接数
   int nConnect;
   //文件大小
   UINT nFileSize;
   //文件的时间
   CTime tTime;
   //文件名
   char filename[MAX_PATH];
}FileMsg;

//转换字符串到文件属性相关
typedef struct s_FILEPATHMSG{
   //文件名
   char filePath[MAX_PATH];
}FilePathMsg;

typedef struct s_LPMSG_QLTRANSEX{
   int nFlag;//用户发送的标志
   int nAction;//进程执行的行为标志
   UINT64	nFileSize_Upload;//用户上传文件大小的字节数
   int nNum;
   void *pVoid;//无类型的指针根据不同的情况传递不同的指针
}LpMsg_QLtransEx;

//自动创建订单所需纱线结构体
typedef struct s_YarnMSG{
   char YarnID[50];//纱线ID
   int nPrimary;//是否是主纱1=主纱,0 = 副纱
}YarnMsg;

#define FS_DEFAULT	0x0000//默认无任何特殊
#define FS_NODIR	0x0001//下载时忽略文件夹

typedef std::vector<YarnMsg> VECYarn;

#ifdef FILETRNAS_BUILDING
typedef struct FileTrans_easy FILETRANS;
#else
typedef void FILETRANS;
#endif

#ifdef FILETRNAS_BUILDING
#define FILETRANS_EXTERN  __declspec(dllexport)
#else
#define FILETRANS_EXTERN  __declspec(dllimport)
#endif 

#define FILETRANS_OPTTYPE_LONG          0
#define FILETRANS_OPTTYPE_OBJECTPOINT   10000
#define FILETRANS_OPTTYPE_STRINGPOINT   10000
#define FILETRANS_OPTTYPE_FUNCTIONPOINT 20000
#define FILETRANS_OPTTYPE_OFF_T         30000

#define FINIT(na,t,nu) FTOPT_ ## na = FILETRANS_OPTTYPE_ ## t + nu

//配置参数的定义
typedef enum {
   //单号 通常适用于string
   FINIT(ORDER,STRINGPOINT,1),
   //接受消息的句柄
   FINIT(HWND,LONG,2),
   //操作类型 上传 下载 登录等
   FINIT(ACTION,LONG,3),
   //操作类型所对应的key  用于确认远程路径
   FINIT(ACTION_KEY,STRINGPOINT,4),
   //尺码
   FINIT(SIZE,STRINGPOINT,5),
   //版本
   FINIT(VERSION,LONG,6),
   //标志 用于操作 后回传的信息标志
   FINIT(FLAG,LONG,7),
   //标志 用于操作 后回传的信息标志
   FINIT(DELSRC,LONG,8),
   //是否遍历文件夹的参数 仅根据后缀下载时使用
   FINIT(TRAVERSINGDIR,LONG,9),
   //dword的参数 部分功能使用 如下载后忽略文件夹功能
   FINIT(STYLE,LONG,10),

   //仅当拷贝时才会使用的参数
   FINIT(DST_ORDER,STRINGPOINT,11),
   FINIT(DST_ACTION_KEY,STRINGPOINT,12),
   FINIT(DST_SIZE,STRINGPOINT,13),
   FINIT(DST_VERSION,LONG,14),

   //传递的参数
   FINIT(VEC_ONEPARAM,OBJECTPOINT,15),
   FINIT(VEC_TWOPARAM,OBJECTPOINT,16),

   //回调函数
   FINIT(FUNC_UPLOAD,FUNCTIONPOINT,17),
   FINIT(FUNC_DELETE,FUNCTIONPOINT,18),
   FINIT(FUNC_BEFORE_DOWNLOAD,FUNCTIONPOINT,19),
   //用户数据
   FINIT(FUNC_USER_DATA,OBJECTPOINT,20),

   FTOPT_LASTENTRY /* 最后一个 无用 */
}FileTransOption;

//返回值
typedef enum {
   FILETRANS_ERROR_MIN_WRONG = -1,//最小错误值不会比该值更小了

   FILETRANS_UNDEFINED = FILETRANS_ERROR_MIN_WRONG,//未定义错误
   FILETRANS_OK = 1,//执行结束
   FILETRANS_UPLOADZERO,
   FILETRANS_DOWNLOADZERO,	//下载列表为空
   FILETRANS_DELZERO,		//删除列表为空
   FILETRANS_COPYZERO,     //拷贝列表为空
   FILETRANS_ORDEREMPTY,	//订单号是空的
   FILETRANS_WRONG_DWONPATH,		//下载路径设置错误
   FILETRANS_WRONG_CONFIG,			//配置信息设置错误，如IP:账户、密码等错误
   FILETRANS_WRONG_INIMSG,	//获取配置文件信息失败
   FILETRANS_WRONG_DBMSG,	//数据库配置信息异常
   FILETRANS_WRONG_LOGIN,	//文档管理登录失败
   FILETRANS_WRONG_NETSTATE,//网络异常
   FILETRANS_WRONG_FTPCANTOPEN,//ftp服务器连接失败
   FILETRANS_WRONG_XMLERROR,//xml错误
   FILETRANS_WRONG_SQLEXECUERR,//数据库语句执行失败
   FILETRANS_WRONG_UNSUPPORT,//不支持的功能
   FILETRANS_WRONG_NOPERMISSION,//用户没有权限进行此次操作
   FILETRANS_WRONG_UNDEFACTION,//未定义的操作
   FILETRANS_WRONG_MEMORYERROR,//内存错误
   FILETRANS_WRONG_DISCONNECTED,//与主机连接失败
   FILETRANS_WRONG_BAD_FUNCTION_ARGUMENT,//错误的参数
   FILETRANS_WRONG_UNKNOWN_OPTION,//未知的参数

   FILETRANS_WRONG_LAST,//最大错误值 永远不使用
}FileTransCode;


//getinfo 接口使用的相关参数
#define FILETRANSINFO_STRING   0x100000
#define FILETRANSINFO_LONG     0x200000
#define FILETRANSINFO_DOUBLE   0x300000
#define FILETRANSINFO_SLIST    0x400000
#define FILETRANSINFO_PTR      0x400000 /* same as SLIST */
#define FILETRANSINFO_SOCKET   0x500000
#define FILETRANSINFO_OFF_T    0x600000
#define FILETRANSINFO_MASK     0x0fffff
#define FILETRANSINFO_TYPEMASK 0xf00000

typedef enum {
  FILETRANSINFO_NONE, /* first, never use this */
  FILETRANSINFO_USER_ID,//从配置文件中获取用户名
  FILETRANSINFO_USER_NAME,//根据用户ID获取用户名
  FILETRANSINFO_DLL_VERSION,//库的版本号
  FILETRANSINFO_HTTP_MODE,//HTTP模式
  FILETRANSINFO_ORDER_EXISTS,//订单号是否存在
  FILETRANSINFO_CAN_LOGIN,//配置文件中的信息是否能登录
  FILETRANSINFO_SAMPLE_ORDER,//一个订单的模板单号
  FILETRANSINFO_FILE_EXISTS,//文件是否存在
  FILETRANSINFO_POPUPLOGIN,//弹出登录窗口并返回登录窗口的登录结果

  FILETRANSINFO_LASTONE          = 56
} FILETRANSINFO;


typedef enum{
   en_Action_UnDefine = 0,//未定义
   en_Action_Upload     ,//上传
   en_Action_Down       ,//下载
   en_Action_DownDir    ,//下载文件夹
   en_Action_DownDirMsg ,//下载文件夹时每个文件都给句柄发送消息
   en_Action_DownByEx   ,//根据后缀下载
   en_Action_GetList    ,//获取列表
   en_Action_GetListEx  ,//获取列表ex
   en_Action_Delete     ,//删除
   en_Action_DeleteDir  ,//删除文件夹
   en_Action_Copy       ,//拷贝文件 或文件夹
   en_Action_BackupFile_Move ,//移动式备份文件 源文件会被删除
   en_Action_BackupFile_Copy ,//复制式备份文件 源文件会保留
   en_Action_CopyVersionToCurVersion    ,//复制指定版本到当前版本
   en_Action_SetSampleOrder    ,//设置模板单号 参数为oneParam的第一个
}FILETRANSACTION;

//上传的文件结构体
typedef struct s_UploadFileMsg{
   char szLocalPath[MAX_PATH];//本地的绝对路径
   char szRelativePath[MAX_PATH];//相对路径
   ULONGLONG  nSize;//文件大小
   char szFileName[MAX_PATH];//文件名
   char szMD5[129];//MD5码
   bool bSuccess;//是否上传成功的标志
} FILEUPLOADMSG;

//上传的回调函数 上传成功后调用  与消息不同
//bUserDataNoUse 返回是否接下来仍然还需要使用用户数据 TRUE表示需要使用
typedef void (*File_trans_upload_callback)(FILEUPLOADMSG* pUploadMsg,void * pUserStruct,BOOL bUserDataNoUse);

//删除的回调函数  删除调用  与消息不同
//szRelativePath 文件的相对路径 包含文件名 
//最后为//表示是文件夹
typedef void (*File_trans_delete_callback)(bool bSuccess,char * szRelativePath,void * pUserStruct,BOOL bUserDataNoUse);

//下载的回调函数  下载之前调用  返回值区分是否下载文件
//szRelativePath 文件的相对路径 包含文件名
//szTarLocalPath 下载到的本地路径
//最后是//表示是文件夹
typedef BOOL (*File_trans_before_download_callback)(char * szRelativePath,char * szTarLocalPath,void * pUserStruct,BOOL bUserDataNoUse);

