#pragma once
#include "FileTransferDef.inl"
#include "CPtLog.h"
#include "ftp_client.h"
#include "base64.h"
#include "Base64Code.h"
#include "ClassDB/DBStyleInfo.h"
#include "ClassDB/DBYarnInfo.h"
#include "ClassDB/DBSizeInfo.h"
#include "ClassDB/DBDesDensity.h"
#include "ClassDB/DBCustomInfo.h"
#include "ClassDB/DBDataDictionary.h"
#include "ClassDB/DBVariousStyleInfo.h"
#include "FileTransData.h"


#define STR_NORMAL_PATH_0	_T("制版文件")
#define STR_NORMAL_PATH_1	_T("工艺文件")
#define STR_NORMAL_PATH_2	_T("设计文件")
#define STR_NORMAL_PATH_3	_T("上机文件")
#define STR_NORMAL_PATH_4	_T("订单文件")
#define STR_NORMAL_PATH_5	_T("图片文件")
#define STR_NORMAL_PATH_6	_T("StyleImage")
#define STR_NORMAL_PATH_7  _T("ChatFile")//聊天的文件夹名称
#define STR_NORMAL_PATH_8  _T("ImgProDetail")//工序流程图
#define STR_NORMAL_PATH_9  _T("ImgModel")//PDM模特图
#define STR_NORMAL_PATH_10  _T("BackUpFile")//备份文件

#define STR_LIB_PATH_0	_T("底图库")
#define STR_LIB_PATH_1	_T("款式库")
#define STR_LIB_PATH_2	_T("工艺库")
#define STR_LIB_PATH_3	_T("密度表")
#define STR_LIB_PATH_4	_T("部件库")
#define STR_LIB_PATH_5	_T("小图库")
#define STR_LIB_PATH_6	_T("配置库")

typedef struct UPDATEORDR_SIZE_INFO
{
   char *xml;
   BOOL bPtLog;
   CString strConn;
}UpdateOrder_Size_Info;

//上传线程
DWORD WINAPI ThreadUpLoad(LPVOID lpParam);
//下载线程
DWORD WINAPI ThreadDownLoad(LPVOID lpParam);
//删除线程
DWORD WINAPI ThreadDel(LPVOID lpParam);

//创建文件夹线程
DWORD WINAPI ThreadMkDir(LPVOID lpParam);
//下载文件夹线程
DWORD WINAPI ThreadDownDir(LPVOID lpParam);
//下载文件夹时每个文件都给句柄发送消息
DWORD WINAPI ThreadDownDirMsg(LPVOID lpParam);
//获取文件夹列表线程
DWORD WINAPI ThreadGetDirList(LPVOID lpParam);
DWORD WINAPI ThreadGetDirListEx(LPVOID lpParam);

//删除文件夹线程
DWORD WINAPI ThreadDelDir(LPVOID lpParam);
//备份文件
BOOL ThreadMoveFileSub(TransferMsg *pBackupFileMsg, TransferFileMsg *pTransFileMsg, LpMsg_QLtransEx *pLpMsg);
DWORD WINAPI ThreadMoveFile(LPVOID lpParam);
BOOL ThreadCopyFilesSub(TransferMsg *pBackupFileMsg, TransferFileMsg *pTransFileMsg, LpMsg_QLtransEx *pLpMsg);
DWORD WINAPI ThreadCopyFiles(LPVOID lpParam);
DWORD WINAPI ThreadCopyVersionToNewCreatedOne(LPVOID lpParam);
//根据后缀下载文件线程
DWORD WINAPI ThreadDownByEx(LPVOID lpParam);

DWORD WINAPI ThreadLogFileToCloud(LPVOID lpParam);

enum {
   En_Loading_Marquee = 0,
};

typedef struct tag_S_Loading
{
   int nLoadingType;
   tag_S_Loading()
   {
      nLoadingType = En_Loading_Marquee;
   }
}S_Loading;

//启动加载对话框
DWORD WINAPI ThreadShowLoading(LPVOID lpParam);
