/*************************************************
// <�ļ�>: FileTransData.h
// <˵��>: �洢��������ݵ���
// <����>: wangzl
// <����>: 2019/02/27
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
#pragma once
#include "FileTransferDef.inl"


#define TypeNameLength	20
//�����ļ������
typedef struct CloudLogMsg
{
   char strLocalPath[MAX_PATH];
   char strSourceFileName[MAX_PATH];
   char strTypeName[TypeNameLength];
}sz_CloudLogMsg;

//�����ļ������
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

   TransferFileMsg* pTransFileMsg;//�ļ�������Ϣ��صĽṹ�� ��������·�� Զ��·��  �ļ���չ��
   int nTransFileNum;

   char strFarPath[MAX_PATH];//�ϴ�ʱ��Զ��·��  ÿ���ϴ��ļ�ʱ�Դ���һ���ļ���

   char strOrderNo[50];

   int nSpecFlag;//�����ʶ���������ֽ��յ�����Ϣ�����Բ�����
   BOOL bDelSrc;//�ϴ��ļ�ʱ�Ƿ�ɾ��Դ�ļ��ı�ʶ
   BOOL bDir;//�Ƿ�����ļ��еı�ʶ (���ݺ�׺�������ļ�ʹ��)
   int nLoginType;//���ݵ�¼��ʽ��ͬд��־ʱ��ѯ��ͬ�ı�  
   DWORD dwStyle;//�߳�ͨ������

   BOOL bUseHttp;//�Ƿ�ʹ��HTTPģʽ

   bool bZip;//�ϴ�ʱ�Ƿ�ѹ���Ĳ��� ���ϴ�ʹ��
   bool bDelZip;//����ʱ�Ƿ�ɾ��ѹ��Դ�ļ��Ĳ���
   bool bUnZipFailRename;//��ѹʧ��������
   //�ص�����
   File_trans_upload_callback funcUpload;//�ϴ�
   File_trans_delete_callback funcDelete;//ɾ��
   File_trans_before_download_callback funcBeforeDownload;//����֮ǰ�Ļص�����
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
      nSpecFlag = 0;//�����ʶ���������ֽ��յ�����Ϣ�����Բ�����
      bDelSrc = FALSE;//�ϴ��ļ�ʱ�Ƿ�ɾ��Դ�ļ��ı�ʶ
      bDir = FALSE;//�Ƿ�����ļ��еı�ʶ (���ݺ�׺�������ļ�ʹ��)
      nLoginType =0;//���ݵ�¼��ʽ��ͬд��־ʱ��ѯ��ͬ�ı�  
      dwStyle = FS_DEFAULT;//�߳�ͨ������

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
   DWORD dwStyle;//�߳�ͨ������
   BOOL bUseHttp;//�Ƿ�ʹ��HTTPģʽ
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
   CString strWorkPath;//��װ������·��

   //���ݿ���ز���
   CString strDBIP               ;//���ݿ��ַ + �˿�
   CString strDBName             ;//���ݿ�����
   CString strDBID               ;//���ݿ������˺�
   CString strDBPassword         ;//���ݿ���������
   //�û���ز���
   CString strUserID             ;//��¼��ID (�û���ID  �����˻�ʱ  һ��Ϊ ���ݿ�����+123QL
   CString strUserPassword       ;//��¼������ (�û������� �����˻�ʱ һ��Ϊ ���ݿ�����+123456QL
   //�ļ�������ز���
   CString strLocalTransIP       ;//�����ļ������ַSVRLOCAL
   CString strFTPFarTrans        ;//Զ���ļ������ַ �����ݹ������ɵĵ�ַ һ������ݿ��ַһ��
   CString strFTPFarlName        ;//Զ���ļ��������ӵ��˻��� �����ݹ������ɵ��û��� һ��Ϊ ���ݿ�����+321ql �������˻�ʱΪĬ������ FTP_DEFAULT_NAME qildoc
   CString strFTPFarPwd          ;//Զ���ļ��������ӵ����� �����ݹ������ɵ����� һ��Ϊ ���ݿ�����+654321ql �������˻�ʱΪĬ������ FTP_DEFAULT_PWD qildocqildoc
   //��Ϣ��ز���
   HWND hProcessWnd              ;//���ڽ�����Ϣ�ľ��
   int nFlag                     ;//������Ϣ����Ӧ�ı�־
   //�ļ��������������Ϣ
   FILETRANSACTION nAction       ;//��������Ϊ
   BOOL bDelSrcFile              ;//�ϴ�ʱ�Ƿ�ɾ�����ļ��Ĳ��� ���ϴ�����

   CString strOrderNo            ;//������
   CString strSize               ;//����
   int nVersion                  ;//�汾�� ������ʱʹ��  ���漰�ļ�����ʱΪ-1
   CString strAction_ParamKey    ;//��Ϊ·������Ӧ��key

   //Ŀ��������� ������������
   CString strDstOrderNo         ;//Ŀ�궩����
   CString strDstSize            ;//Ŀ�����
   int nDstVersion               ;//Ŀ��汾�� ������ʱʹ��  ���漰�ļ�����ʱΪ-1
   CString strDstAction_ParamKey ;//Ŀ����Ϊ·������Ӧ��key
   //��������
   BOOL bHttpMode                ;//�Ƿ�ʹ��HTTPģʽ�Ĳ���
   BOOL bPtLog                   ;//�Ƿ��ӡ��־
   int nLoginType                ;//��¼������ ����ͬS_FILETRANS_LOGINTYPE

   BOOL bTraversingDir           ;//�Ƿ�����ļ��еĲ��� �������ļ���ʱʹ��
   DWORD dwStyle                 ;//�߳�ͨ������  Ŀǰ��; �������ļ���ʱ����������ļ���

   //�����б�
   vector<CString> vec_ActParam_OneParam;//һ�������Ĳ����б� �����ϴ� ɾ��
   //���������Ĳ����б� �������� ���������أ�key1_Զ���ļ���,key2_�����ļ��ľ���·�� �����ļ���
   //��������key1_Զ��Դ�ļ��� key2_Զ��Ŀ���ļ���
   vector<pair<CString,CString>> vec_ActParam_TwoParam;
   //�����ļ�����Ϣ
   map<CString,CString> map_Default;//һЩĬ�ϵ����� �� FTPĬ�϶˿� HTTPĬ�϶˿�һ�� keyΪ�ؼ��� valueΪĬ������
   map<CString,S_PathParam> map_Key_Path;//keyֵ���Ӧ���ϴ�·�� value�а������滻�ַ� ��$OrderNo$�� ��keyΪ�ؼ��� valueΪ·��+�Ƿ�ѹ�� Ĭ��ѹ��

   //�ص�����
   File_trans_upload_callback funcUpload;//�ϴ�
   File_trans_delete_callback funcDelete;//ɾ��
   File_trans_before_download_callback funcBeforeDownload;//����֮ǰ�Ļص�����

   void * pUserCallBackData;
};



