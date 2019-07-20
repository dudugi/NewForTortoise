#ifndef FTPCLIENT_H_H_
#define FTPCLIENT_H_H_


#ifdef __cplusplus
extern "C" {
#endif

#define FTP_TYPE_FILE 0		//�ļ�
#define FTP_TYPE_DIR  1		//�ļ���
#define FTP_TYPE_OTHER	2	//����

typedef struct s_ListData{
	char   fileNameList[256];
	char   fileTimeList[256];
	int type;   //�ļ����ͣ�0Ϊ�ļ���1Ϊ�ļ���
}ListData;


//ת���ַ������ļ��������
typedef struct FILEMSG_TRAN{
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

//2016-05-27�Զ��������Ϣ Ftp_Upload��Ftp_Download���н�����ʾ
#define WM_FTP_PROGRESS		7001

/************************************************************************/
/* ������Ҫ����   WM_FTP_PROGRESS  ��Ϣ�ľ��   ��������WPARAM������ 
 * ��WPARAM=100��LPARAM=1 ��ʾLoad���
 */
/************************************************************************/
_declspec(dllexport) void Ftp_SetProcessHwnd(HWND hWnd);

/**
 * �������ܣ���ftp��������������
 * ����˵��:pHost:������IP,pUser:�����û�����pPass:��������
 * return 0:failed;1:success.
 * eg:
	Ftp_Open("192.168.33.139","zhangt", "123456")
 */
_declspec(dllexport) int Ftp_Open(const char *pHost,const char *pUser, const char *pPass);


/**
 * �������ܣ�ɾ���������ϵ��ļ�
 * ����˵��:pServerFileName:Ҫɾ�����ļ���
 * return 0:failed;1:success.
 *eg:
	Ftp_Delete("�봫/msvci70.dll");
 */
_declspec(dllexport) int Ftp_Delete(const char *pServerFileName);

/**
 * �������ܣ���ȡ���������ļ��б�
 * ����˵��:pPath:���������ļ�������,ppItems:�����ļ�ʱ�䡢�ļ������ļ����͵�ListData��������,num:�ļ�����
 * return 0:failed;1:success.
 * eg: 		
	ListData *data = NULL;
	int num = 0;
	Ftp_Getlist("",&data,&num);//��Ŀ¼��""  ����Ŀ¼��"�봫/"
	for(int i=0;i<num;i++)
	{		
		CString strName;
		strName.Format(_T("%s"),data[i].fileNameList);
	}
	if (data)//ע�⣺�ͷ�
	{
		delete data;
		data = NULL;
		//free(data);
	}
*/
_declspec(dllexport) int Ftp_Getlist(const char *pPath,ListData **ppItems,int *num);

_declspec(dllexport) int Ftp_Getlist(const char *pPath,FileMsg **ppItems,int *num);
/**
 * �������ܣ������ļ���������
 * ����˵��:output:Ҫ���ص��ļ���·��,path:��������·��
 * return 0:failed;1:success.
 * eg:
	Ftp_Download("D:/��������ͬ.doc","�봫/�½��ļ���1/��������ͬ.doc");
 */
_declspec(dllexport) int Ftp_Download(const char *pOutput, const char *pPath);


/**
 * �������ܣ��ϴ��ļ���������
 * ����˵��:input:Ҫ�ϴ����ļ���·��,path:��������·��
 * return 0:failed;1:success.
 * eg:
	Ftp_Upload("D:/msvci70.dll","�봫/msvci70.dll");
 */
_declspec(dllexport) int Ftp_Upload(const char *pInput, const char *pPath);


/**
 * �������ܣ��ڷ��������½��ļ���
 * ����˵��:dirName:Ҫ�½����ļ�����
 * return 0:failed;1:success.
 */
_declspec(dllexport) int Ftp_MkDir(const char *dirName);


/**
 * �������ܣ��ڷ�������ɾ���ļ���
 * ����˵��:dirName:Ҫɾ�����ļ�����(�˲��������ļ���)
 * return 0:failed;1:success.
 */
_declspec(dllexport) int Ftp_DelDir(const char *dirName);


/**
 * �������ܣ��ϴ��ļ��е���������
 * ����˵��:dirFullName:Ҫ�ϴ����ļ��о���·����dirName:�ļ�������svrPath:��������ǰĿ¼
 * return 0:failed;1:success.
 */
_declspec(dllexport) int Ftp_UpLoadDir(const char *dirFullName,const char *dirName,const char *svrPath);


/**
 * �������ܣ��ر�����
 */
_declspec(dllexport) void Ftp_Close();

#ifdef __cplusplus
};
#endif

#endif /* FTPCLIENT_H_ */
