#pragma once
#include "FileTransferDef.inl"

#ifdef __cplusplus
extern "C" {
#endif

//初始化接口 返回操作信息的指针
FILETRANS_EXTERN FILETRANS * filetrans_easy_init(const CString & strWorkPath,S_FileTrans_LoginType nLoginType = En_Login_User);
FILETRANS_EXTERN FILETRANS * filetrans_easy_init2(const CString & strWorkPath,const CString & strIP,const CString & strName,const CString & strPwd,S_FileTrans_LoginType nLoginType = En_Login_User);
//设置参数
FILETRANS_EXTERN FileTransCode filetrans_easy_setopt(FILETRANS * pFileTrans,FileTransOption option,...);

FILETRANS_EXTERN FileTransCode filetrans_easy_getinfo(FILETRANS *pFileTrans, FILETRANSINFO info, ...);
//执行接口
FILETRANS_EXTERN FileTransCode filetrans_easy_perform(FILETRANS *pFileTrans);
//释放内存
FILETRANS_EXTERN void FileTrans_easy_cleanup(FILETRANS *pFileTrans);
//重置数据
FILETRANS_EXTERN void FileTrans_easy_reset(FILETRANS *pFileTrans);

FILETRANS_EXTERN LPCTSTR filetrans_easy_geterror(FileTransCode nErrorCode);

//将日志文件上传到云端中
FILETRANS_EXTERN void LogFileToCloud(LPCTSTR strLogFilePath,LPCTSTR strTypeName);
//显示滚动的进度条
FILETRANS_EXTERN void FT_ShowMarquee();
//隐藏滚动的进度条
FILETRANS_EXTERN void FT_HideMarquee();

#ifdef __cplusplus
};
#endif