/*************************************************
// <文件>: FileTrans_Handle.h
// <说明>: 处理接口中函数的相关功能
// <作者>: wangzl
// <日期>: 2019/02/28
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 

#pragma once
#include "FileTransferDef.inl"
#include "LoginDlg.h"
#include "FileTransData.h"

int TransferEx_ZipFile(CString &strSrc);
int TransferEx_UnzipFile(CString &strSrc,BOOL bDel /* = FALSE */);

//检测配置的信息是否可以登录数据库
FileTransCode CKDBLogin(FILETRANS *pData);

//返回当前结构体中信息连接所用的字符串
CString GetSqlConnectStr(FILETRANS *pData);

//使用当前的信息进行登录  如果登录成功则返回TRUE 否则返回FALSE
BOOL Login(FILETRANS *pData);

//弹出登录窗口登录
BOOL PopLogin(const CString & strWorkPath,int nLoginType);

FileTransCode GetActionPath(/*const*/ map<CString,S_PathParam> & map_KeyPath,
   const CString & strActionParam,const CString & strOrderNo,
   const CString & strSize,int nVersion,CString & strPath);
FileTransCode GetActionPath(FILETRANS * pData,CString & strPath);

//获取相关结果 pParam 为对应参数的指针
FileTransCode GetInfo(FILETRANS * pData,FILETRANSINFO info,void * pParam);

//根据行为 分发函数处理
FileTransCode DistributionAction(FILETRANS * pData);

//准备交给线程处理的数据结构体的指针
TransferMsg * PrepareTransferMsg(FILETRANS * pData);

//处理FTP/Http连接信息
void GetFtpConnnectInfo(FILETRANS * pData,CString & strIP,CString & strName,CString & strPwd);

void HandleFTPConnectInfo(FILETRANS * pData,TransferMsg * pTransMsg);
void HandleFTPConnectInfo(FILETRANS * pData,TransferListMsg * pTransMsg);

//处理操作的相关函数
FileTransCode HandleFunction_Upload(FILETRANS * pData);
FileTransCode HandleFunction_Download(FILETRANS * pData);
FileTransCode HandleFunction_DownDir(FILETRANS * pData);
FileTransCode HandleFunction_DownDirMsg(FILETRANS * pData);
FileTransCode HandleFunction_DownByEx(FILETRANS * pData);
FileTransCode HandleFunction_GetList(FILETRANS * pData);
FileTransCode HandleFunction_GetListEx(FILETRANS * pData);
FileTransCode HandleFunction_Delete(FILETRANS * pData);
FileTransCode HandleFunction_DeleteDir(FILETRANS * pData);
FileTransCode HandleFunction_Copy(FILETRANS * pData);
FileTransCode HandleFunction_BackupFile_Move(FILETRANS * pData);
FileTransCode HandleFunction_BackupFile_Copy(FILETRANS * pData);
FileTransCode HandleFunction_BackupFile(FILETRANS * pData,BOOL bMove);
FileTransCode HandleFunction_CopyVersionToCurVersion(FILETRANS * pData);
FileTransCode HandleFunction_SetSampleOrder(FILETRANS * pData);

//获取信息的相关函数
FileTransCode GetInfo_FileExists(FILETRANS * pData,void *);//文件是否存在 BOOL
FileTransCode GetInfo_UserID(FILETRANS * pData,void *);//从配置文件中获取用户ID CString 的指针
FileTransCode GetInfo_UserName(FILETRANS * pData,void *);//根据用户ID获取用户名称 参数来自vec_oneparam
FileTransCode GetInfo_DllVersion(FILETRANS * pData,void *);//获取库的版本号
FileTransCode GetInfo_HttpMode(FILETRANS * pData,void *);//获取当前是否为HTTP模式
FileTransCode GetInfo_OrderExists(FILETRANS * pData,void *);//检测订单是否存在
FileTransCode GetInfo_CanLogin(FILETRANS * pData,void *);//检测当前的配置能不能登录
FileTransCode GetInfo_SampleOrder(FILETRANS * pData,void *);//获取当前单号的模板单号
FileTransCode GetInfo_PopupLogin(FILETRANS * pData,void *);//获取当前单号的模板单号
