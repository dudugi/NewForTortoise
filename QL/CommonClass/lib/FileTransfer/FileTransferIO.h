#pragma once
#include "FileTransferDef.inl"

#ifdef __cplusplus
extern "C" {
#endif

//��ʼ���ӿ� ���ز�����Ϣ��ָ��
FILETRANS_EXTERN FILETRANS * filetrans_easy_init(const CString & strWorkPath,S_FileTrans_LoginType nLoginType = En_Login_User);
FILETRANS_EXTERN FILETRANS * filetrans_easy_init2(const CString & strWorkPath,const CString & strIP,const CString & strName,const CString & strPwd,S_FileTrans_LoginType nLoginType = En_Login_User);
//���ò���
FILETRANS_EXTERN FileTransCode filetrans_easy_setopt(FILETRANS * pFileTrans,FileTransOption option,...);

FILETRANS_EXTERN FileTransCode filetrans_easy_getinfo(FILETRANS *pFileTrans, FILETRANSINFO info, ...);
//ִ�нӿ�
FILETRANS_EXTERN FileTransCode filetrans_easy_perform(FILETRANS *pFileTrans);
//�ͷ��ڴ�
FILETRANS_EXTERN void FileTrans_easy_cleanup(FILETRANS *pFileTrans);
//��������
FILETRANS_EXTERN void FileTrans_easy_reset(FILETRANS *pFileTrans);

FILETRANS_EXTERN LPCTSTR filetrans_easy_geterror(FileTransCode nErrorCode);

//����־�ļ��ϴ����ƶ���
FILETRANS_EXTERN void LogFileToCloud(LPCTSTR strLogFilePath,LPCTSTR strTypeName);
//��ʾ�����Ľ�����
FILETRANS_EXTERN void FT_ShowMarquee();
//���ع����Ľ�����
FILETRANS_EXTERN void FT_HideMarquee();

#ifdef __cplusplus
};
#endif