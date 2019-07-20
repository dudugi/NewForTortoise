/*************************************************
// <�ļ�>: FileTrans_Handle.h
// <˵��>: ����ӿ��к�������ع���
// <����>: wangzl
// <����>: 2019/02/28
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 

#pragma once
#include "FileTransferDef.inl"
#include "LoginDlg.h"
#include "FileTransData.h"

int TransferEx_ZipFile(CString &strSrc);
int TransferEx_UnzipFile(CString &strSrc,BOOL bDel /* = FALSE */);

//������õ���Ϣ�Ƿ���Ե�¼���ݿ�
FileTransCode CKDBLogin(FILETRANS *pData);

//���ص�ǰ�ṹ������Ϣ�������õ��ַ���
CString GetSqlConnectStr(FILETRANS *pData);

//ʹ�õ�ǰ����Ϣ���е�¼  �����¼�ɹ��򷵻�TRUE ���򷵻�FALSE
BOOL Login(FILETRANS *pData);

//������¼���ڵ�¼
BOOL PopLogin(const CString & strWorkPath,int nLoginType);

FileTransCode GetActionPath(/*const*/ map<CString,S_PathParam> & map_KeyPath,
   const CString & strActionParam,const CString & strOrderNo,
   const CString & strSize,int nVersion,CString & strPath);
FileTransCode GetActionPath(FILETRANS * pData,CString & strPath);

//��ȡ��ؽ�� pParam Ϊ��Ӧ������ָ��
FileTransCode GetInfo(FILETRANS * pData,FILETRANSINFO info,void * pParam);

//������Ϊ �ַ���������
FileTransCode DistributionAction(FILETRANS * pData);

//׼�������̴߳�������ݽṹ���ָ��
TransferMsg * PrepareTransferMsg(FILETRANS * pData);

//����FTP/Http������Ϣ
void GetFtpConnnectInfo(FILETRANS * pData,CString & strIP,CString & strName,CString & strPwd);

void HandleFTPConnectInfo(FILETRANS * pData,TransferMsg * pTransMsg);
void HandleFTPConnectInfo(FILETRANS * pData,TransferListMsg * pTransMsg);

//�����������غ���
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

//��ȡ��Ϣ����غ���
FileTransCode GetInfo_FileExists(FILETRANS * pData,void *);//�ļ��Ƿ���� BOOL
FileTransCode GetInfo_UserID(FILETRANS * pData,void *);//�������ļ��л�ȡ�û�ID CString ��ָ��
FileTransCode GetInfo_UserName(FILETRANS * pData,void *);//�����û�ID��ȡ�û����� ��������vec_oneparam
FileTransCode GetInfo_DllVersion(FILETRANS * pData,void *);//��ȡ��İ汾��
FileTransCode GetInfo_HttpMode(FILETRANS * pData,void *);//��ȡ��ǰ�Ƿ�ΪHTTPģʽ
FileTransCode GetInfo_OrderExists(FILETRANS * pData,void *);//��ⶩ���Ƿ����
FileTransCode GetInfo_CanLogin(FILETRANS * pData,void *);//��⵱ǰ�������ܲ��ܵ�¼
FileTransCode GetInfo_SampleOrder(FILETRANS * pData,void *);//��ȡ��ǰ���ŵ�ģ�嵥��
FileTransCode GetInfo_PopupLogin(FILETRANS * pData,void *);//��ȡ��ǰ���ŵ�ģ�嵥��
