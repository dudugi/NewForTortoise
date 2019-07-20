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


#define STR_NORMAL_PATH_0	_T("�ư��ļ�")
#define STR_NORMAL_PATH_1	_T("�����ļ�")
#define STR_NORMAL_PATH_2	_T("����ļ�")
#define STR_NORMAL_PATH_3	_T("�ϻ��ļ�")
#define STR_NORMAL_PATH_4	_T("�����ļ�")
#define STR_NORMAL_PATH_5	_T("ͼƬ�ļ�")
#define STR_NORMAL_PATH_6	_T("StyleImage")
#define STR_NORMAL_PATH_7  _T("ChatFile")//������ļ�������
#define STR_NORMAL_PATH_8  _T("ImgProDetail")//��������ͼ
#define STR_NORMAL_PATH_9  _T("ImgModel")//PDMģ��ͼ
#define STR_NORMAL_PATH_10  _T("BackUpFile")//�����ļ�

#define STR_LIB_PATH_0	_T("��ͼ��")
#define STR_LIB_PATH_1	_T("��ʽ��")
#define STR_LIB_PATH_2	_T("���տ�")
#define STR_LIB_PATH_3	_T("�ܶȱ�")
#define STR_LIB_PATH_4	_T("������")
#define STR_LIB_PATH_5	_T("Сͼ��")
#define STR_LIB_PATH_6	_T("���ÿ�")

typedef struct UPDATEORDR_SIZE_INFO
{
   char *xml;
   BOOL bPtLog;
   CString strConn;
}UpdateOrder_Size_Info;

//�ϴ��߳�
DWORD WINAPI ThreadUpLoad(LPVOID lpParam);
//�����߳�
DWORD WINAPI ThreadDownLoad(LPVOID lpParam);
//ɾ���߳�
DWORD WINAPI ThreadDel(LPVOID lpParam);

//�����ļ����߳�
DWORD WINAPI ThreadMkDir(LPVOID lpParam);
//�����ļ����߳�
DWORD WINAPI ThreadDownDir(LPVOID lpParam);
//�����ļ���ʱÿ���ļ��������������Ϣ
DWORD WINAPI ThreadDownDirMsg(LPVOID lpParam);
//��ȡ�ļ����б��߳�
DWORD WINAPI ThreadGetDirList(LPVOID lpParam);
DWORD WINAPI ThreadGetDirListEx(LPVOID lpParam);

//ɾ���ļ����߳�
DWORD WINAPI ThreadDelDir(LPVOID lpParam);
//�����ļ�
BOOL ThreadMoveFileSub(TransferMsg *pBackupFileMsg, TransferFileMsg *pTransFileMsg, LpMsg_QLtransEx *pLpMsg);
DWORD WINAPI ThreadMoveFile(LPVOID lpParam);
BOOL ThreadCopyFilesSub(TransferMsg *pBackupFileMsg, TransferFileMsg *pTransFileMsg, LpMsg_QLtransEx *pLpMsg);
DWORD WINAPI ThreadCopyFiles(LPVOID lpParam);
DWORD WINAPI ThreadCopyVersionToNewCreatedOne(LPVOID lpParam);
//���ݺ�׺�����ļ��߳�
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

//�������ضԻ���
DWORD WINAPI ThreadShowLoading(LPVOID lpParam);
