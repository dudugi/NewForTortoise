/*
 * ftpclient.c
 *
 */
#include "stdafx.h"

#include "ftpclient.h"
#include "ftplib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <math.h>
#include <map>
#include <sys/stat.h>


#define  FTPLISTFILE  "ftplist.txt"

static HWND g_FtphWnd = NULL;//通过此句柄发送WM_PROGRESS消息，参数WPARAM代表当前进度

struct REMFILE {
	struct REMFILE *next;
	int fsz;
	char *fnm;
};


//处理格式 nFormat:0 -rw-r--r-- 1 ftp ftp             18 Dec 19 14:23 test.txt
//		   nFormat:1 -rw-r--r-- 1 ftp ftp             18 Dec 19 2016 test.txt
static void HandLine2FileMsg(const char * line,FILEMSG_TRAN &FileMsg,int nFormat)
{
	char type = ' ';
	char limit[10] = {0};
	int nConnect = 0;
	char user[MAX_PATH] = {0};
	char userGroup[MAX_PATH] = {0};
	char szSize[MAX_PATH] = {0};
	int nSize = 0;
	char month[4] = {0};
	int nMonth = 1;
	int nDay = 0;
	int nHour = 0;
	int nMin = 0;
	int nYear = COleDateTime::GetCurrentTime().GetYear();
	char szFileName[MAX_PATH] = {0};
	std::map<CString, int> m_MonthNamesMap;
	m_MonthNamesMap[_T("jan")] = 1;
	m_MonthNamesMap[_T("feb")] = 2;
	m_MonthNamesMap[_T("mar")] = 3;
	m_MonthNamesMap[_T("apr")] = 4;
	m_MonthNamesMap[_T("may")] = 5;
	m_MonthNamesMap[_T("jun")] = 6;
	m_MonthNamesMap[_T("june")] = 6;
	m_MonthNamesMap[_T("jul")] = 7;
	m_MonthNamesMap[_T("july")] = 7;
	m_MonthNamesMap[_T("aug")] = 8;
	m_MonthNamesMap[_T("sep")] = 9;
	m_MonthNamesMap[_T("sept")] = 9;
	m_MonthNamesMap[_T("oct")] = 10;
	m_MonthNamesMap[_T("nov")] = 11;
	m_MonthNamesMap[_T("dec")] = 12;

	switch(nFormat)
	{
	case 0:
		sscanf(line,"%c%s %d %s %s %[^ ] %s %d %d:%d %[^\0]"
			,&type
			,&limit
			,&nConnect
			,&user
			,&userGroup
			,&szSize
			,&month
			,&nDay
			,&nHour
			,&nMin
			,&szFileName);
		break;
	case 1:
		sscanf(line,"%c%s %d %s %s %[^ ] %s %d %d %[^\0]"
			,&type
			,&limit
			,&nConnect
			,&user
			,&userGroup
			,&szSize
			,&month
			,&nDay
			,&nYear
			,&szFileName);
		break;
	default:
		break;
	}

	if ('d' == type)
	{
		//文件夹
		FileMsg.nFileType = FTP_TYPE_DIR;
	}
	else if ('-' == type)
	{
		//文件
		FileMsg.nFileType = FTP_TYPE_FILE;
	}
	else
	{
		//'c'-字符型设备  ‘b’-块设备
		FileMsg.nFileType = FTP_TYPE_OTHER;
	}
	//权限依次：用户权限/用户组权限/其他人权限 
	int nFileLimit = 0;
	for (int i = 0;i < 3;i++)
	{
		int nBeg = i*3 ;
		int nLimit = 0;
		if ('r' == limit[nBeg])
		{
			nLimit += 4;
		}
		else
			nLimit += 0;
		if ('w' == limit[nBeg + 1])
		{
			nLimit += 2;
		}
		else
			nLimit += 0;
		if ('x' == line[nBeg + 2])
		{
			nLimit += 1;
		}
		else
			nLimit += 0;

		nLimit = nLimit * 100 / pow((double)nLimit,(double)i);
		nFileLimit += nLimit;
	}
	FileMsg.nFileLimit = nFileLimit;

	//连接数
	//月份处理
	USES_CONVERSION;
	CString strFind = A2W( month );

	strFind.MakeLower();
	auto iter = m_MonthNamesMap.find(strFind);
	if (iter != m_MonthNamesMap.end())
		nMonth = iter->second;
	CTime Time(nYear,nMonth,nDay,nHour,nMin,0);
	FileMsg.tTime = Time;


	FileMsg.nConnect = nConnect;
	FileMsg.nFileSize = nSize;
	
	strcpy_s(FileMsg.filename,szFileName);
	
}

static int log_progress(netbuf *ctl, int xfered, void *arg)
{
	struct REMFILE *f = (struct REMFILE *) arg;
	int pct = (int)(xfered*1.0/f->fsz*100);
	if (NULL != g_FtphWnd)
	{
		::PostMessage(g_FtphWnd,WM_FTP_PROGRESS,pct,0);
	}
	return 1;
}

_declspec(dllexport) void Ftp_SetProcessHwnd(HWND hWnd)
{
	g_FtphWnd = hWnd;
}

/**
 * 函数功能：与ftp服务器建立连接
 * 参数说明:pHost:服务器IP,pUser:登入用户名，pPass:登入密码
 * return 0:failed;1:success.
 */
int Ftp_Open(const char *pHost,const char *pUser, const char *pPass)
{
	ftpInit();
	if(0 == ftpOpen(pHost)){
		printf("connect server error!");
		return 0;
	}
	if(0 == ftpLogin(pUser,pPass)){
		printf("username or password error!");
		return 0;;
	}
	return 1;
}

/**
 * 函数功能：删除服务器上的文件
 * 参数说明:pServerFileName:要删除的文件名
 * return 0:failed;1:success.
 */
int Ftp_Delete(const char *pServerFileName)
{
	return ftpDelete(pServerFileName);
}

/**
 * 函数功能：获取服务器的文件列表
 * 参数说明:pPath:服务器的文件夹名称,ppItems:包含文件时间、文件名、文件类型的ListData数组,num:文件个数
 * return 0:failed;1:success.
 */
int Ftp_Getlist(const char *pPath,ListData **ppItems,int *num)
{
	*num =0;
	*ppItems=NULL;
	if(0 == ftpDir(FTPLISTFILE,pPath)){
		return 0;
	}
	FILE *fp = NULL;
	char line[1024] = {0};

	if (NULL == (fp = fopen(FTPLISTFILE, "r+")))
	{
		return 0;
	}
	int linenum = 0;
	while (fgets(line, 1024, fp) !=NULL)
	{
		int len = strlen(line);
        if(len<40){
            fclose(fp);
			return 0;
		}
		linenum++;
	}
    if(linenum == 0){
        fclose(fp);
		return 1;
	}

	*ppItems=(ListData*)malloc(sizeof(ListData)*linenum);
    if(*ppItems ==NULL){
        fclose(fp);
		return 0;
	}
	fseek(fp,0,0);
	int i =0;

	memset(line, 0, 1024);
	while (fgets(line, 1024, fp) !=NULL)
	{
		int len = strlen(line);
        if(len<40){
            fclose(fp);
			return 0;
		}

		//line数据处理
		USES_CONVERSION;
		CString strTmp = A2W( line );
		int nFind = strTmp.Find(':');
		FILEMSG_TRAN filemsg;
		if (-1 != nFind)
		{
			HandLine2FileMsg(line,filemsg,0);
		}
		else
			HandLine2FileMsg(line,filemsg,1);
		strcpy_s((*ppItems)[i].fileNameList,filemsg.filename);
		(*ppItems)[i].type = filemsg.nFileType;
		CString strTime = filemsg.tTime.Format(_T("%Y/%m/%d %H:%M"));
		char * pTime=T2A(strTime);
		strcpy_s((*ppItems)[i].fileTimeList,pTime);

		i++;
        if(i>linenum){
            fclose(fp);
			return 0;
		}
		memset(line, 0, 1024);
	}
    fclose(fp);
	*num = linenum;
   return 1;
}

int Ftp_Getlist( const char *pPath,FileMsg **ppItems,int *num )
{
	*num =0;
	*ppItems=NULL;
	if(0 == ftpDir(FTPLISTFILE,pPath)){
		return 0;
	}
	FILE *fp = NULL;
	char line[1024] = {0};
	memset(line, 0, 1024);
	if (NULL == (fp = fopen(FTPLISTFILE, "r+")))
	{
		return 0;
	}
	int linenum = 0;
	while (fgets(line, 1024, fp) !=NULL)
	{
		int len = strlen(line);
		if(len<40){
			fclose(fp);
			return 0;
		}
		linenum++;
	}
	if(linenum == 0){
		fclose(fp);
		return 1;
	}

	*ppItems = (FileMsg*)malloc(sizeof(FileMsg)*linenum);
	if(*ppItems == NULL){
		fclose(fp);
		return 0;
	}
	fseek(fp,0,0);
	int i =0;

	while (fgets(line, 1024, fp) !=NULL)
	{
		int len = strlen(line);
		if(len<40){
			fclose(fp);
			return 0;
		}

		//line数据处理
		USES_CONVERSION;
		CString strTmp = A2W( line );
		int nFind = strTmp.Find(':');
		FILEMSG_TRAN filemsg;
		if (-1 != nFind)
		{
			HandLine2FileMsg(line,*ppItems[i],0);
		}
		else
			HandLine2FileMsg(line,*ppItems[i],1);

		i++;
		if(i>linenum){
			fclose(fp);
			return 0;
		}
		memset(line, 0, 1024);
	}
	fclose(fp);
	*num = linenum;
	return 1;
}

/**
 * 函数功能：下载文件到服务器
 * 参数说明:output:要下载的文件名路径,path:服务器的路径
 * return 0:failed;1:success.
 */
extern int Ftp_Download(const char *pOutput, const char *pPath)
{
	//参考：http://blog.chinaunix.net/uid-23381466-id-58855.html
	int sts=0;
	int fsz;

	FtpOptions(FTPLIB_CALLBACK, (long) NULL,DefaultNetbuf);

	struct REMFILE *f;
	f = (struct REMFILE *) malloc(sizeof(struct REMFILE));
	memset(f,0,sizeof(struct REMFILE));
	f->fnm = strdup(pOutput);
	if (!FtpSize(pPath, &fsz, FTPLIB_IMAGE, DefaultNetbuf))
		fsz = 0;
	f->fsz = fsz;
	fsz = fsz/100;
	if (fsz)
	{
		FtpOptions(FTPLIB_CALLBACK, (long) log_progress, DefaultNetbuf);
		FtpOptions(FTPLIB_IDLETIME, (long) 1000, DefaultNetbuf);
		FtpOptions(FTPLIB_CALLBACKARG, (long) f, DefaultNetbuf);
		FtpOptions(FTPLIB_CALLBACKBYTES, (long) fsz, DefaultNetbuf);
	}
	sts = FtpGet(f->fnm,pPath,FTPLIB_IMAGE,DefaultNetbuf);
	if (sts)
	{
		if (NULL != g_FtphWnd)
		{
			::PostMessage(g_FtphWnd,WM_FTP_PROGRESS,100,1);
		}
	}

	free(f->fnm);
	free(f);

	return sts;
}

/**
 * 函数功能：上传文件到服务器
 * 参数说明:input:要上传的文件名路径,path:服务器的路径
 * return 0:failed;1:success.
 */
int Ftp_Upload(const char *pInput, const char *pPath)
{
	//参考：http://blog.chinaunix.net/uid-23381466-id-58854.html
	int sts=0;
	int fsz;

	FtpOptions(FTPLIB_CALLBACK, (long) NULL, DefaultNetbuf);
	struct REMFILE *f;
	f = (struct REMFILE *) malloc(sizeof(struct REMFILE));
	memset(f,0,sizeof(struct REMFILE));
	f->fnm = strdup(pInput);

	//include <sys/stat.h>
	struct _stat info;
	_stat(f->fnm, &info);
	fsz = info.st_size;
	f->fsz = fsz;
	fsz = fsz/100;
	if (fsz)
	{
		FtpOptions(FTPLIB_CALLBACK, (long) log_progress, DefaultNetbuf);
		FtpOptions(FTPLIB_IDLETIME, (long) 1000, DefaultNetbuf);
		FtpOptions(FTPLIB_CALLBACKARG, (long) f, DefaultNetbuf);
		FtpOptions(FTPLIB_CALLBACKBYTES, (long) fsz, DefaultNetbuf);
	}
	sts = FtpPut(f->fnm,pPath,FTPLIB_IMAGE,DefaultNetbuf);
	if (sts)
	{
		if (NULL != g_FtphWnd)
		{
			::PostMessage(g_FtphWnd,WM_FTP_PROGRESS,100,1);
		}
	}
	free(f->fnm);
	free(f);

	return sts;
}

/**
 * 函数功能：在服务器上新建文件夹
 * 参数说明:dirName:要新建的文件夹名
 * return 0:failed;1:success.
 */
int Ftp_MkDir(const char *dirName)
{
	return ftpMkdir(dirName);
}

/**
 * 函数功能：上传文件夹到服务器上
 * 参数说明:dirFullName:要上传的文件夹绝对路径，dirName:文件夹名，svrPath:服务器当前目录
 * return 0:failed;1:success.
 */
int Ftp_UpLoadDir(const char *dirFullName,const char *dirName,const char *svrPath){
	char svrFullDirName[260];
	sprintf(svrFullDirName,("%s/%s"),svrPath,dirName);
	if(0 == Ftp_MkDir(svrFullDirName))
		return 0;
	CFileFind tempFind;
	char sTempFileFind[260] ; 
	sprintf(sTempFileFind,("%s\\*.*"),dirFullName); 
	CString ss;
	ss += sTempFileFind;
	BOOL IsFinded = tempFind.FindFile(ss);	
	while (IsFinded)  //目录下有文件
	{  
		IsFinded = tempFind.FindNextFile(); 
		if (!tempFind.IsDots())  //不是“.”“..”
		{  
#ifdef _UNICODE
			USES_CONVERSION;
			char * sFoundFileName = T2A(tempFind.GetFileName());
#else
			char sFoundFileName[260];
			strcpy(sFoundFileName,(LPSTR)(LPCSTR)tempFind.GetFileName().GetBuffer());
#endif // _UNICODE

			if (tempFind.IsDirectory())  //是文件夹
			{  
				char sTempDir[260];  
				sprintf(sTempDir,("%s\\%s"),dirFullName,sFoundFileName);  
				char svrTempFullDirName[260];
				sprintf(svrTempFullDirName,("%s/%s"),svrPath,dirName);
				if(0 == Ftp_UpLoadDir(sTempDir,sFoundFileName,svrTempFullDirName)){  // 嵌套函数
					tempFind.Close(); 
					return 0;
				}
			}  
			else
			{ 						
				char sTempFileName[260];  
				sprintf(sTempFileName,("%s/%s"),dirFullName,sFoundFileName);  
				char svrTempFullFileName[260];
				sprintf(svrTempFullFileName,("%s/%s/%s"),svrPath,dirName,sFoundFileName);
				if (0 == Ftp_Upload(sTempFileName,svrTempFullFileName)){
					tempFind.Close(); 
					return 0;
				}
			}
		}
	}
	tempFind.Close();
	return 1;
}

/**
 * 函数功能：在服务器上删除文件夹
 * 参数说明:dirFullName:要删除的文件夹名
 * return 0:failed;1:success.
 */
int Ftp_DelDir(const char *dirFullName)
{
	ListData *pData = NULL;
	int num = 0;
	if(0 == Ftp_Getlist(dirFullName,&pData,&num)){
		printf(("get list error!\n"));
		return 0;
	}

	if(pData && num>0)
	{ //文件夹非空
		for(int i=0;i<num;i++)
		{
			//zhangtao 2016-02-18_start 过滤.和..
			int nLen = strlen(pData[i].fileNameList);
			if('.' == pData[i].fileNameList[nLen-1])//.和..跳过
				continue;
			//zhangtao 2016-02-18_end

			char pathName[260];
			sprintf(pathName,("%s/%s"),dirFullName,pData[i].fileNameList);	
			if(pData[i].type == FTP_TYPE_FILE)
			{	//若是文件，则直接删除
				if( 0 == Ftp_Delete(pathName)){//删除失败，则退出
					free(pData);pData=NULL;
					return 0;
				}
			}
			else{
				//sprintf(pathName,("%s/"),pathName);
 				if( 0 == Ftp_DelDir(pathName)){//若是文件夹，则递归删除
					free(pData);pData=NULL;
					return 0;	
				}
			}
		}
	}
	if(pData){
		free(pData);
		pData=NULL;
	}	
	return ftpRmdir(dirFullName);
}

/**
 * 函数功能：关闭连接
 */
void Ftp_Close()
{
	ftpQuit();
}
