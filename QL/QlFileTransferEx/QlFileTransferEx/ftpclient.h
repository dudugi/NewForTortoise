#ifndef FTPCLIENT_H_H_
#define FTPCLIENT_H_H_


#ifdef __cplusplus
extern "C" {
#endif

#define FTP_TYPE_FILE 0		//文件
#define FTP_TYPE_DIR  1		//文件夹
#define FTP_TYPE_OTHER	2	//其它

typedef struct s_ListData{
	char   fileNameList[256];
	char   fileTimeList[256];
	int type;   //文件类型：0为文件，1为文件夹
}ListData;


//转换字符串到文件属性相关
typedef struct FILEMSG_TRAN{
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

//2016-05-27自定义进度消息 Ftp_Upload和Ftp_Download具有进度提示
#define WM_FTP_PROGRESS		7001

/************************************************************************/
/* 设置需要接收   WM_FTP_PROGRESS  消息的句柄   进度数在WPARAM参数中 
 * 当WPARAM=100且LPARAM=1 表示Load完成
 */
/************************************************************************/
_declspec(dllexport) void Ftp_SetProcessHwnd(HWND hWnd);

/**
 * 函数功能：与ftp服务器建立连接
 * 参数说明:pHost:服务器IP,pUser:登入用户名，pPass:登入密码
 * return 0:failed;1:success.
 * eg:
	Ftp_Open("192.168.33.139","zhangt", "123456")
 */
_declspec(dllexport) int Ftp_Open(const char *pHost,const char *pUser, const char *pPass);


/**
 * 函数功能：删除服务器上的文件
 * 参数说明:pServerFileName:要删除的文件名
 * return 0:failed;1:success.
 *eg:
	Ftp_Delete("秒传/msvci70.dll");
 */
_declspec(dllexport) int Ftp_Delete(const char *pServerFileName);

/**
 * 函数功能：获取服务器的文件列表
 * 参数说明:pPath:服务器的文件夹名称,ppItems:包含文件时间、文件名、文件类型的ListData连续数组,num:文件个数
 * return 0:failed;1:success.
 * eg: 		
	ListData *data = NULL;
	int num = 0;
	Ftp_Getlist("",&data,&num);//根目录：""  其他目录："秒传/"
	for(int i=0;i<num;i++)
	{		
		CString strName;
		strName.Format(_T("%s"),data[i].fileNameList);
	}
	if (data)//注意：释放
	{
		delete data;
		data = NULL;
		//free(data);
	}
*/
_declspec(dllexport) int Ftp_Getlist(const char *pPath,ListData **ppItems,int *num);

_declspec(dllexport) int Ftp_Getlist(const char *pPath,FileMsg **ppItems,int *num);
/**
 * 函数功能：下载文件到服务器
 * 参数说明:output:要下载的文件名路径,path:服务器的路径
 * return 0:failed;1:success.
 * eg:
	Ftp_Download("D:/上中西合同.doc","秒传/新建文件夹1/上中西合同.doc");
 */
_declspec(dllexport) int Ftp_Download(const char *pOutput, const char *pPath);


/**
 * 函数功能：上传文件到服务器
 * 参数说明:input:要上传的文件名路径,path:服务器的路径
 * return 0:failed;1:success.
 * eg:
	Ftp_Upload("D:/msvci70.dll","秒传/msvci70.dll");
 */
_declspec(dllexport) int Ftp_Upload(const char *pInput, const char *pPath);


/**
 * 函数功能：在服务器上新建文件夹
 * 参数说明:dirName:要新建的文件夹名
 * return 0:failed;1:success.
 */
_declspec(dllexport) int Ftp_MkDir(const char *dirName);


/**
 * 函数功能：在服务器上删除文件夹
 * 参数说明:dirName:要删除的文件夹名(此不存在子文件夹)
 * return 0:failed;1:success.
 */
_declspec(dllexport) int Ftp_DelDir(const char *dirName);


/**
 * 函数功能：上传文件夹到服务器上
 * 参数说明:dirFullName:要上传的文件夹绝对路径，dirName:文件夹名，svrPath:服务器当前目录
 * return 0:failed;1:success.
 */
_declspec(dllexport) int Ftp_UpLoadDir(const char *dirFullName,const char *dirName,const char *svrPath);


/**
 * 函数功能：关闭连接
 */
_declspec(dllexport) void Ftp_Close();

#ifdef __cplusplus
};
#endif

#endif /* FTPCLIENT_H_ */
