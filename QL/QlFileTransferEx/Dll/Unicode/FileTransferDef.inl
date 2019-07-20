/*************************************************
// <�ļ�>: FileTransferDef.inl
// <˵��>: ������е�һЩ����
// <����>: wangzl
// <����>: 2019/02/28
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
#pragma once
using namespace std;
#include <vector>


#ifndef QLFILTTRANS_MARK
#define QLFILTTRANS_MARK
#endif

#ifndef QLFILETRANS_VERSION
#define QLFILETRANS_VERSION		_T("0.0.1.0")//�������ݿ�ӿڵĵ������⹤���ư�ӿڲ�һ�µ��µı�������
#endif

#define FTP_TYPE_FILE 0		//�ļ�
#define FTP_TYPE_DIR  1		//�ļ���
#define FTP_TYPE_OTHER	2	//����

//�����ϴ����ص�ǰ�ļ����ȵ���Ϣ
#define WM_QL_FTP_PROGRESS		WM_USER + 0x1000
//���ڽ��յ�ǰ�ϴ����ļ����Ƶ���Ϣ
#define WM_QL_FTP_UPLOAD		WM_USER + 0x1001
//���ڽ��յ�ǰɾ�����ļ����Ƶ���Ϣ
#define WM_QL_FTP_DEL			WM_USER + 0x1002
//���ڽ��յ�ǰ���ص��ļ����Ƶ���Ϣ
#define WM_QL_FTP_DOWNLOAD		WM_USER + 0x1003
//���ڽ��յ�ǰ�����ļ��н������Ϣ
#define WM_QL_FTP_MKDIR			WM_USER + 0x1004
//���ڽ��յ�ǰ��ȡ�ļ��б�������Ϣ
#define WM_QL_FTP_GETLIST		WM_USER + 0x1005
//���ڽ��յ�ǰɾ���ļ��н������Ϣ
#define WM_QL_FTP_DELDIR		WM_USER + 0x1006
//���ڽ��յ�ǰɾ���ļ��н������Ϣ
#define WM_QL_FTP_DOWNDIR		WM_USER + 0x1007
//���ڽ��ո����ļ���չ�������ļ�����Ϣ
#define WM_QL_FTP_DOWNBYEX		WM_USER + 0x1008
//�����ļ���ʱ�����ļ����سɹ�ʧ�ܵ���Ϣ
#define WM_QL_FTP_DOWNDIRMSG	WM_USER + 0X1009
//���ڽ����ϴ��ļ��н������Ϣ
#define WM_QL_FTP_UPDIR			WM_USER + 0X1010
//�ϴ��ļ���ʱ�����ļ��ϴ��������Ϣ
#define WM_QL_FTP_UPDIRMSG		WM_USER + 0X1011
//���ݺ�׺�������ļ�ʱ ��ÿ���ļ�������״̬��ʹ����һ����Ϣ����
#define WM_QL_FTP_DOWNBYEXMSG	WM_USER + 0X1012
//���ڱ��ݶ����ļ�����Ϣ
#define WM_QL_FTP_BACKUPFILE  WM_USER + 0x1013
#define WM_QL_FTP_BACKUPFILEMSG  WM_USER + 0x1014
#define WM_QL_FTP_COPY_VERSION_TO_NEW  (WM_USER + 0x1015)

#define FTP_MSG_MAX_COUNT		0x1015		//��������ģ��������Ϣʱ���ӵĲ���  ���������Ϣͬ����� 

//δ����ı�־���ڵ��ñ���ʱ��û�������κ��źţ����ڷ�����Ϣʱ���ش˱�ʶ
#define UNDESIGN_FLAG	0

//�̴߳�����Ϊ
#define FTP_ACTION_START			0//������ʼ
#define FTP_ACTION_SUC				1//�����ɹ�
#define FTP_ACTION_FAIL				2//����ʧ��
#define FTP_ACTION_OPENFAIL			3//������ʧ��
#define FTP_ACTION_NOFILE			4//�ļ������ڵı�ʶ ����Ե��ļ�������Ч
#define FTP_ACTION_DISCONNECTED		5//����������ʧ��

#define FTP_DEFAULT_NAME	_T("qildoc")
#define FTP_DEFAULT_PWD		_T("qildocqildoc")

//��¼�������ͬ������
typedef enum S_FileTrans_LoginType{
   En_Login_Null = -1,//û��Ա����¼�����������ݿ������
   En_Login_User = 0,//Ա����¼
   En_Login_Custom,//�ͻ���¼
}S_FILETRANS_LOGINTYPE;

//ת���ַ������ļ��������
typedef struct s_FILEMSG{
   //�ļ�����0-�ļ��� 1-�ļ� 2-����
   int nFileType;
   //�ļ�Ȩ��,����777  8���� rwx����
   int nFileLimit;
   //������
   int nConnect;
   //�ļ���С
   UINT nFileSize;
   //�ļ���ʱ��
   CTime tTime;
   //�ļ���
   char filename[MAX_PATH];
}FileMsg;

//ת���ַ������ļ��������
typedef struct s_FILEPATHMSG{
   //�ļ���
   char filePath[MAX_PATH];
}FilePathMsg;

typedef struct s_LPMSG_QLTRANSEX{
   int nFlag;//�û����͵ı�־
   int nAction;//����ִ�е���Ϊ��־
   UINT64	nFileSize_Upload;//�û��ϴ��ļ���С���ֽ���
   int nNum;
   void *pVoid;//�����͵�ָ����ݲ�ͬ��������ݲ�ͬ��ָ��
}LpMsg_QLtransEx;

//�Զ�������������ɴ�߽ṹ��
typedef struct s_YarnMSG{
   char YarnID[50];//ɴ��ID
   int nPrimary;//�Ƿ�����ɴ1=��ɴ,0 = ��ɴ
}YarnMsg;

#define FS_DEFAULT	0x0000//Ĭ�����κ�����
#define FS_NODIR	0x0001//����ʱ�����ļ���

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

//���ò����Ķ���
typedef enum {
   //���� ͨ��������string
   FINIT(ORDER,STRINGPOINT,1),
   //������Ϣ�ľ��
   FINIT(HWND,LONG,2),
   //�������� �ϴ� ���� ��¼��
   FINIT(ACTION,LONG,3),
   //������������Ӧ��key  ����ȷ��Զ��·��
   FINIT(ACTION_KEY,STRINGPOINT,4),
   //����
   FINIT(SIZE,STRINGPOINT,5),
   //�汾
   FINIT(VERSION,LONG,6),
   //��־ ���ڲ��� ��ش�����Ϣ��־
   FINIT(FLAG,LONG,7),
   //��־ ���ڲ��� ��ش�����Ϣ��־
   FINIT(DELSRC,LONG,8),
   //�Ƿ�����ļ��еĲ��� �����ݺ�׺����ʱʹ��
   FINIT(TRAVERSINGDIR,LONG,9),
   //dword�Ĳ��� ���ֹ���ʹ�� �����غ�����ļ��й���
   FINIT(STYLE,LONG,10),

   //��������ʱ�Ż�ʹ�õĲ���
   FINIT(DST_ORDER,STRINGPOINT,11),
   FINIT(DST_ACTION_KEY,STRINGPOINT,12),
   FINIT(DST_SIZE,STRINGPOINT,13),
   FINIT(DST_VERSION,LONG,14),

   //���ݵĲ���
   FINIT(VEC_ONEPARAM,OBJECTPOINT,15),
   FINIT(VEC_TWOPARAM,OBJECTPOINT,16),

   //�ص�����
   FINIT(FUNC_UPLOAD,FUNCTIONPOINT,17),
   FINIT(FUNC_DELETE,FUNCTIONPOINT,18),
   FINIT(FUNC_BEFORE_DOWNLOAD,FUNCTIONPOINT,19),
   //�û�����
   FINIT(FUNC_USER_DATA,OBJECTPOINT,20),

   FTOPT_LASTENTRY /* ���һ�� ���� */
}FileTransOption;

//����ֵ
typedef enum {
   FILETRANS_ERROR_MIN_WRONG = -1,//��С����ֵ����ȸ�ֵ��С��

   FILETRANS_UNDEFINED = FILETRANS_ERROR_MIN_WRONG,//δ�������
   FILETRANS_OK = 1,//ִ�н���
   FILETRANS_UPLOADZERO,
   FILETRANS_DOWNLOADZERO,	//�����б�Ϊ��
   FILETRANS_DELZERO,		//ɾ���б�Ϊ��
   FILETRANS_COPYZERO,     //�����б�Ϊ��
   FILETRANS_ORDEREMPTY,	//�������ǿյ�
   FILETRANS_WRONG_DWONPATH,		//����·�����ô���
   FILETRANS_WRONG_CONFIG,			//������Ϣ���ô�����IP:�˻�������ȴ���
   FILETRANS_WRONG_INIMSG,	//��ȡ�����ļ���Ϣʧ��
   FILETRANS_WRONG_DBMSG,	//���ݿ�������Ϣ�쳣
   FILETRANS_WRONG_LOGIN,	//�ĵ������¼ʧ��
   FILETRANS_WRONG_NETSTATE,//�����쳣
   FILETRANS_WRONG_FTPCANTOPEN,//ftp����������ʧ��
   FILETRANS_WRONG_XMLERROR,//xml����
   FILETRANS_WRONG_SQLEXECUERR,//���ݿ����ִ��ʧ��
   FILETRANS_WRONG_UNSUPPORT,//��֧�ֵĹ���
   FILETRANS_WRONG_NOPERMISSION,//�û�û��Ȩ�޽��д˴β���
   FILETRANS_WRONG_UNDEFACTION,//δ����Ĳ���
   FILETRANS_WRONG_MEMORYERROR,//�ڴ����
   FILETRANS_WRONG_DISCONNECTED,//����������ʧ��
   FILETRANS_WRONG_BAD_FUNCTION_ARGUMENT,//����Ĳ���
   FILETRANS_WRONG_UNKNOWN_OPTION,//δ֪�Ĳ���

   FILETRANS_WRONG_LAST,//������ֵ ��Զ��ʹ��
}FileTransCode;


//getinfo �ӿ�ʹ�õ���ز���
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
  FILETRANSINFO_USER_ID,//�������ļ��л�ȡ�û���
  FILETRANSINFO_USER_NAME,//�����û�ID��ȡ�û���
  FILETRANSINFO_DLL_VERSION,//��İ汾��
  FILETRANSINFO_HTTP_MODE,//HTTPģʽ
  FILETRANSINFO_ORDER_EXISTS,//�������Ƿ����
  FILETRANSINFO_CAN_LOGIN,//�����ļ��е���Ϣ�Ƿ��ܵ�¼
  FILETRANSINFO_SAMPLE_ORDER,//һ��������ģ�嵥��
  FILETRANSINFO_FILE_EXISTS,//�ļ��Ƿ����
  FILETRANSINFO_POPUPLOGIN,//������¼���ڲ����ص�¼���ڵĵ�¼���

  FILETRANSINFO_LASTONE          = 56
} FILETRANSINFO;


typedef enum{
   en_Action_UnDefine = 0,//δ����
   en_Action_Upload     ,//�ϴ�
   en_Action_Down       ,//����
   en_Action_DownDir    ,//�����ļ���
   en_Action_DownDirMsg ,//�����ļ���ʱÿ���ļ��������������Ϣ
   en_Action_DownByEx   ,//���ݺ�׺����
   en_Action_GetList    ,//��ȡ�б�
   en_Action_GetListEx  ,//��ȡ�б�ex
   en_Action_Delete     ,//ɾ��
   en_Action_DeleteDir  ,//ɾ���ļ���
   en_Action_Copy       ,//�����ļ� ���ļ���
   en_Action_BackupFile_Move ,//�ƶ�ʽ�����ļ� Դ�ļ��ᱻɾ��
   en_Action_BackupFile_Copy ,//����ʽ�����ļ� Դ�ļ��ᱣ��
   en_Action_CopyVersionToCurVersion    ,//����ָ���汾����ǰ�汾
   en_Action_SetSampleOrder    ,//����ģ�嵥�� ����ΪoneParam�ĵ�һ��
}FILETRANSACTION;

//�ϴ����ļ��ṹ��
typedef struct s_UploadFileMsg{
   char szLocalPath[MAX_PATH];//���صľ���·��
   char szRelativePath[MAX_PATH];//���·��
   ULONGLONG  nSize;//�ļ���С
   char szFileName[MAX_PATH];//�ļ���
   char szMD5[129];//MD5��
   bool bSuccess;//�Ƿ��ϴ��ɹ��ı�־
} FILEUPLOADMSG;

//�ϴ��Ļص����� �ϴ��ɹ������  ����Ϣ��ͬ
//bUserDataNoUse �����Ƿ��������Ȼ����Ҫʹ���û����� TRUE��ʾ��Ҫʹ��
typedef void (*File_trans_upload_callback)(FILEUPLOADMSG* pUploadMsg,void * pUserStruct,BOOL bUserDataNoUse);

//ɾ���Ļص�����  ɾ������  ����Ϣ��ͬ
//szRelativePath �ļ������·�� �����ļ��� 
//���Ϊ//��ʾ���ļ���
typedef void (*File_trans_delete_callback)(bool bSuccess,char * szRelativePath,void * pUserStruct,BOOL bUserDataNoUse);

//���صĻص�����  ����֮ǰ����  ����ֵ�����Ƿ������ļ�
//szRelativePath �ļ������·�� �����ļ���
//szTarLocalPath ���ص��ı���·��
//�����//��ʾ���ļ���
typedef BOOL (*File_trans_before_download_callback)(char * szRelativePath,char * szTarLocalPath,void * pUserStruct,BOOL bUserDataNoUse);

