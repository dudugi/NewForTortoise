#include "StdAfx.h"
#include "ftp_client.h"

#include "ftplib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <math.h>
#include <map>
#include <sys/stat.h>
#include "Network/MyNetwork.h"

//#define  FTPLISTFILE  "Qltrans.dat"

struct REMFILE {
	struct REMFILE *next;
	int fsz;
	char *fnm;
	HWND hProcess; //2017/09/08 zhangt 进度条句柄
};

//处理格式 nFormat:0 -rw-r--r-- 1 ftp ftp             18 Dec 19 14:23 test.txt
//		   nFormat:1 -rw-r--r-- 1 ftp ftp             18 Dec 19 2016 test.txt
static void  HandLine2FileMsg(const char * line,s_FILEMSG &FileMsg,int nFormat)
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
	nSize = atoi(szSize);
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
	CString strFind = _T("");
#ifdef _UNICODE
	USES_CONVERSION;
	strFind = A2W( month );
#else
	strFind.Format(_T("%s"),month);
#endif // _UNICODE

	strFind.MakeLower();
	auto iter = m_MonthNamesMap.find(strFind);
	if (iter != m_MonthNamesMap.end())
		nMonth = iter->second;
	CTime Time(nYear,nMonth,nDay,nHour,nMin,0);
	FileMsg.tTime = Time;


	FileMsg.nConnect = nConnect;
	FileMsg.nFileSize = nSize;

	strncpy_s(FileMsg.filename,szFileName,strlen(szFileName) - 1);

	
}

static int log_progress(netbuf *ctl, int xfered, void *arg)
{
	struct REMFILE *f = (struct REMFILE *) arg;
	int pct = (int)(xfered*1.0/f->fsz*100);
	HWND hProcess = f->hProcess;
	if (NULL != hProcess)
	{
		::PostMessage(hProcess,WM_QL_FTP_PROGRESS,pct,0);
	}
	return 1;
}

zt_FtpComm::zt_FtpComm()
{
	DefaultNetbuf = NULL;
	m_hProcess = NULL;
}

zt_FtpComm::~zt_FtpComm()
{

}

void zt_FtpComm::Ftp_ProcessMsg(HWND hWnd)
{
	m_hProcess = hWnd;
}

/**
 * 函数功能：与ftp服务器建立连接
 * 参数说明:pHost:服务器IP,pUser:登入用户名，pPass:登入密码
 * return 0:failed;1:success.
 */
int zt_FtpComm::Ftp_Open(const char *pHost,const char *pUser, const char *pPass)
{
	FtpInit();
	if(0 == FtpConnect(pHost, &DefaultNetbuf)){
		printf("connect server error!");
		return 0;
	}

	if(0 == FtpLogin(pUser, pPass, DefaultNetbuf)){
		printf("username or password error!");
		return 0;
	}
	return 1;
}

int zt_FtpComm::Ftp_OpenEx(const char *pHost,const char *pUser, const char *pPass)
{
	//2018/03/01 zhangt 增加对当前网络的判断
	CMyNetwork myNetwork;
	CString strUrl = _T("");
#ifdef _UNICODE
	USES_CONVERSION;
	strUrl = A2W( pHost );
#else
	strUrl.Format(_T("%s"),pHost);
#endif // _UNICODE
	int nPos = strUrl.Find(':');
	if (nPos>0) strUrl = strUrl.Left(nPos);
	myNetwork.SetDesAdress(strUrl);
	if(myNetwork.OnConnectNet())
	{
		//connected
		FtpInit();
		if(0 == FtpConnect(pHost, &DefaultNetbuf)){
			printf("connect server error!");
			return 0;
		}

		if(0 == FtpLogin(pUser, pPass, DefaultNetbuf)){
			printf("username or password error!");
			return 0;
		}
		return 1;
	}
	else
	{
		//disconnected
		return 2;
	}
}

/**
 * 函数功能：删除服务器上的文件
 * 参数说明:pServerFileName:要删除的文件名
 * return 0:failed;1:success.
 */
int zt_FtpComm::Ftp_Delete(const char *pServerFileName)
{
	return FtpDelete(pServerFileName, DefaultNetbuf);
}

int zt_FtpComm::Ftp_Getlist( const char *pPath,FileMsg **ppItems,int *num )
{
	char szFile[260];
	sprintf(szFile,"%ld.tmp",this);
	*num =0;
	*ppItems=NULL;
	if(0 == FtpDir(szFile/*FTPLISTFILE*/, pPath, DefaultNetbuf))
	{
		remove(szFile);//2017/09/08 zhangt 删除临时文件
		return 0;
	}
	FILE *fp = NULL;
	char line[1024] = {0};
	memset(line, 0, 1024);
	if (NULL == (fp = fopen(szFile/*FTPLISTFILE*/, "r+")))
	{
		remove(szFile);//2017/09/08 zhangt 删除临时文件
		return 0;
	}
	int linenum = 0;
	while (fgets(line, 1024, fp) !=NULL)
	{
		int len = strlen(line);
		if(len<40){
			fclose(fp);
			remove(szFile);//2017/09/08 zhangt 删除临时文件
			return 0;
		}
		linenum++;
	}
	if(linenum == 0){
		fclose(fp);
		remove(szFile);//2017/09/08 zhangt 删除临时文件
		return 1;
	}

	*ppItems = (FileMsg*)malloc(sizeof(FileMsg)*linenum);
	if(*ppItems == NULL){
		fclose(fp);
		remove(szFile);//2017/09/08 zhangt 删除临时文件
		return 0;
	}
	memset(*ppItems,0,sizeof(FileMsg)*linenum);
	fseek(fp,0,0);
	int i =0;

	while (fgets(line, 1024, fp) !=NULL)
	{
		int len = strlen(line);
		if(len<40){
			fclose(fp);
			remove(szFile);//2017/09/08 zhangt 删除临时文件
			return 0;
		}

		//line数据处理
#ifdef _UNICODE
		USES_CONVERSION;
		CString strTmp = A2W( line );
#else
		CString strTmp = _T("");
		strTmp.Format(_T("%s"),line);
#endif // _UNICODE
		
		int nFind = strTmp.Find(':');

		if (-1 != nFind)
		{
			HandLine2FileMsg(line,(*ppItems)[i],0);
		}
		else
			HandLine2FileMsg(line,(*ppItems)[i],1);

		i++;
		if(i>linenum){
			fclose(fp);
			remove(szFile);//2017/09/08 zhangt 删除临时文件
			return 0;
		}
		memset(line, 0, 1024);
	}

	fclose(fp);
	remove(szFile);//2017/09/08 zhangt 删除临时文件
	*num = linenum;

	return 1;
}

int zt_FtpComm::Ftp_Getlist(const char *pPath,FileMsg **ppItems,int *num,DWORD dwStyle)
{
   char szFile[260];
   sprintf(szFile,"%ld.tmp",this);
   *num =0;
   *ppItems=NULL;//清空传入的指针
   //获取指定文件夹的列表到文件里面  此时不遍历子文件夹
   if(0 == FtpDir(szFile/*FTPLISTFILE*/, pPath, DefaultNetbuf))
   {
      remove(szFile);//2017/09/08 zhangt 删除临时文件
      return 0;
   }

   //对文件列表的扩展
   struct s_FileMsgEx{
      int nFileNum;
      char szParrentName[MAX_PATH];
      FileMsg * pItem;
      s_FileMsgEx (){
         nFileNum = 0;
         memset(szParrentName,0,MAX_PATH);
         pItem = NULL;
      }
   };

   vector<s_FileMsgEx> vec_FileMsgEx;//建立标准容器 包含所有的文件信息
   s_FileMsgEx oFileMsg;//构建当前的容器信息

   //解析
   FILE *fp = NULL;
   char line[1024] = {0};
   memset(line, 0, 1024);
   if (NULL == (fp = fopen(szFile/*FTPLISTFILE*/, "r+")))
   {
      remove(szFile);//2017/09/08 zhangt 删除临时文件
      return 0;
   }
   int linenum = 0;
   while (fgets(line, 1024, fp) !=NULL)
   {
      int len = strlen(line);
      if(len<40){
         fclose(fp);
         remove(szFile);//2017/09/08 zhangt 删除临时文件
         return 0;
      }
      linenum++;
   }
   if(linenum == 0){
      fclose(fp);
      remove(szFile);//2017/09/08 zhangt 删除临时文件
      return 1;
   }

   oFileMsg.pItem = (FileMsg*)malloc(sizeof(FileMsg)*linenum);//构建空间获取列表信息
   //*ppItems = (FileMsg*)malloc(sizeof(FileMsg)*linenum);
   if(NULL == oFileMsg.pItem){
      fclose(fp);
      remove(szFile);//2017/09/08 zhangt 删除临时文件

      delete oFileMsg.pItem;//删除占用的空间
      oFileMsg.pItem = NULL;
      
      return 0;
   }
   memset(oFileMsg.pItem,0,sizeof(FileMsg)*linenum);//清空信息
   fseek(fp,0,0);
   int i =0;

   while (fgets(line, 1024, fp) !=NULL)
   {
      int len = strlen(line);
      if(len<40){
         fclose(fp);
         remove(szFile);//2017/09/08 zhangt 删除临时文件

         delete oFileMsg.pItem;//删除占用的空间
         oFileMsg.pItem = NULL;

         return 0;
      }

      //line数据处理
#ifdef _UNICODE
      USES_CONVERSION;
      CString strTmp = A2W( line );
#else
      CString strTmp = _T("");
      strTmp.Format(_T("%s"),line);
#endif // _UNICODE

      int nFind = strTmp.Find(':');

      if (-1 != nFind)
      {
         HandLine2FileMsg(line,oFileMsg.pItem[i],0);
      }
      else
         HandLine2FileMsg(line,oFileMsg.pItem[i],1);

      i++;
      if(i>linenum){
         fclose(fp);
         remove(szFile);//2017/09/08 zhangt 删除临时文件

         delete oFileMsg.pItem;//删除占用的空间
         oFileMsg.pItem = NULL;

         return 0;
      }
      memset(line, 0, 1024);
   }

   fclose(fp);
   remove(szFile);//2017/09/08 zhangt 删除临时文件

   //将所有的当前获取的数据 写入到容器里面
   oFileMsg.nFileNum = linenum;
   vec_FileMsgEx.push_back(oFileMsg);

   linenum = 0;
   //-------------------------------------------------------
   if (FS_NODIR == dwStyle)//如果是忽略文件夹 
   {
      for (int nFileListIndex = 0;nFileListIndex < oFileMsg.nFileNum;++nFileListIndex)
      {
         ++linenum;//文件数量+1 文件夹也被当做文件处理
         if(FTP_TYPE_DIR == oFileMsg.pItem[nFileListIndex].nFileType)
         {
            //如果是文件夹  则对子文件夹的数据进行遍历 
            s_FileMsgEx oChildFileMsg;
            //设置遍历的子文件夹 
            //拷贝当前的数据
            char pathName[260] = {0};
            sprintf(pathName,"%s/%s",pPath,oFileMsg.pItem[nFileListIndex].filename);

            if(1 == Ftp_Getlist(pathName,&(oChildFileMsg.pItem),&oChildFileMsg.nFileNum,dwStyle))
            {
               sprintf(oChildFileMsg.szParrentName,"%s",oFileMsg.pItem[nFileListIndex].filename);

               vec_FileMsgEx.push_back(oChildFileMsg);

               linenum += oChildFileMsg.nFileNum ;//将子文件夹的列表数量加到当前的数量之上 数量
            }
            else
            {
               //释放所有占用的空间
               for (auto it = vec_FileMsgEx.begin();it != vec_FileMsgEx.end();++it)
               {
                  delete it->pItem;
                  it->pItem = NULL;
               }
               return 0;
            }
         }
      }
   }
   else
   {
      linenum += oFileMsg.nFileNum;
   }

   //new出返回的空间

   *ppItems = (FileMsg*)malloc(sizeof(FileMsg)*linenum);
   if(NULL == *ppItems){
      //申请空间失败 直接返回
      return 0;
   }
   memset(*ppItems,0,sizeof(FileMsg)*linenum);


   //遍历完所有的子文件夹并将其加入到了容器中
   int nIndex = 0;
   for (auto it = vec_FileMsgEx.begin();it != vec_FileMsgEx.end();++it)
   {
      for (int nChildIndex = 0;nChildIndex < it->nFileNum && nIndex < linenum;++nChildIndex)
      {
         if(0 != strlen(it->szParrentName))//父路径的长度不为0 则文件名 = 父文件名 + 当前文件名
         {
            sprintf((*ppItems)[nIndex].filename,("%s/%s"),it->szParrentName,it->pItem[nChildIndex].filename);
         }
         else
         {
            sprintf((*ppItems)[nIndex].filename,("%s"),it->pItem[nChildIndex].filename);
         }
         
         (*ppItems)[nIndex].nFileType  = it->pItem[nChildIndex].nFileType  ;
         (*ppItems)[nIndex].nFileLimit = it->pItem[nChildIndex].nFileLimit ;
         (*ppItems)[nIndex].nConnect   = it->pItem[nChildIndex].nConnect   ;
         (*ppItems)[nIndex].nFileSize  = it->pItem[nChildIndex].nFileSize  ;
         (*ppItems)[nIndex].tTime      = it->pItem[nChildIndex].tTime      ;

         ++nIndex;//索引值增加
      }

      //清空占用空间
      delete it->pItem;
      it->pItem = NULL;
   }

   *num = linenum;

   return 1;
}

/**
 * 函数功能：下载文件到服务器
 * 参数说明:output:要下载的文件名路径,path:服务器的路径
 * return 0:failed;1:success.
 */
int zt_FtpComm::Ftp_Download(const char *pOutput, const char *pPath)
{
	//参考：http://blog.chinaunix.net/uid-23381466-id-58855.html
	int sts=0;
	int fsz;

	FtpOptions(FTPLIB_CALLBACK, (long) NULL,DefaultNetbuf);

	struct REMFILE *f;
	f = (struct REMFILE *) malloc(sizeof(struct REMFILE));
	memset(f,0,sizeof(struct REMFILE));
	f->fnm = strdup(pOutput);
	f->hProcess = m_hProcess;//进度条句柄赋值
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
		if (NULL != m_hProcess)
		{
			::PostMessage(m_hProcess,WM_QL_FTP_PROGRESS,100,1);
		}
	}

	free(f->fnm);
	free(f);

	return sts;
}

int zt_FtpComm::Ftp_DownloadEx(const char *pOutput, const char *pPath)
{
   //参考：http://blog.chinaunix.net/uid-23381466-id-58855.html
   int sts=0;
   int fsz;

   FtpOptions(FTPLIB_CALLBACK, (long) NULL,DefaultNetbuf);

   struct REMFILE *f;
   f = (struct REMFILE *) malloc(sizeof(struct REMFILE));
   memset(f,0,sizeof(struct REMFILE));
   f->fnm = strdup(pOutput);
   f->hProcess = m_hProcess;//进度条句柄赋值
   if (!FtpSize(pPath, &fsz, FTPLIB_IMAGE, DefaultNetbuf))
   {
      free(f->fnm);
      free(f);
      return 2;
   }

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
      if (NULL != m_hProcess)
      {
         ::PostMessage(m_hProcess,WM_QL_FTP_PROGRESS,100,1);
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
int zt_FtpComm::Ftp_Upload(const char *pInput, const char *pPath)
{
	//参考：http://blog.chinaunix.net/uid-23381466-id-58854.html
	int sts=0;
	int fsz;

	FtpOptions(FTPLIB_CALLBACK, (long) NULL, DefaultNetbuf);
	struct REMFILE *f;
	f = (struct REMFILE *) malloc(sizeof(struct REMFILE));
	memset(f,0,sizeof(struct REMFILE));
	f->fnm = strdup(pInput);
	f->hProcess = m_hProcess;//进度条句柄赋值

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
		if (NULL != m_hProcess)
		{
			::PostMessage(m_hProcess,WM_QL_FTP_PROGRESS,100,1);
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
int zt_FtpComm::Ftp_MkDir(const char *dirName)
{
	return FtpMkdir(dirName, DefaultNetbuf);
}

/**
 * 函数功能：上传文件夹到服务器上
 * 参数说明:dirFullName:要上传的文件夹绝对路径，dirName:文件夹名，svrPath:服务器当前目录
 * return 0:failed;1:success.
 */
int zt_FtpComm::Ftp_UpLoadDir(const char *dirFullName,const char *dirName,const char *svrPath)
{
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


int zt_FtpComm::Ftp_UpLoadDir( const char *dirFullName,const char *svrDirFulllPath,HWND hWnd,DWORD wpMsg,int nFlag )
{
	Ftp_MkDir(svrDirFulllPath);

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
				sprintf(svrTempFullDirName,("%s/%s"),svrDirFulllPath,sFoundFileName);
				if(0 == Ftp_UpLoadDir(sTempDir,svrTempFullDirName,hWnd,wpMsg,nFlag)){  // 嵌套函数
					tempFind.Close(); 
					return 0;
				}
			}  
			else
			{
				char sTempFileName[260];  
				sprintf(sTempFileName,("%s/%s"),dirFullName,sFoundFileName);  
				char svrTempFullFileName[260];
				sprintf(svrTempFullFileName,("%s/%s"),svrDirFulllPath,sFoundFileName);

				CString strOutTmpFile(sTempFileName);

				TransferEx_ZipFile(strOutTmpFile);
#ifdef _UNICODE
				char * szZipFile = T2A(strOutTmpFile);
#else
				char szZipFile[MAX_PATH] = {0};
				strncpy_s(szZipFile,(LPSTR)(LPCTSTR)strOutTmpFile, sizeof(szZipFile) - 1);
#endif
				LpMsg_QLtransEx *pLpMsg = new LpMsg_QLtransEx;
				ZeroMemory(pLpMsg,sizeof(LpMsg_QLtransEx));

				if (0 == Ftp_Upload(szZipFile,svrTempFullFileName)){
					tempFind.Close(); 

					if (NULL != hWnd)
					{
						pLpMsg->nFlag = nFlag;
						pLpMsg->nAction = FTP_ACTION_FAIL;
						SendMessage(hWnd,wpMsg,(WPARAM)sTempFileName,(LPARAM)pLpMsg);
					}
					DeleteFile(strOutTmpFile);
					delete pLpMsg;

					return 0;
				}
				else
				{
					if (NULL != hWnd)
					{
						pLpMsg->nFlag = nFlag;
						pLpMsg->nAction = FTP_ACTION_SUC;

						SendMessage(hWnd,wpMsg,(WPARAM)svrTempFullFileName,(LPARAM)pLpMsg);
					}
					DeleteFile(strOutTmpFile);
				}
				delete pLpMsg;
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
int zt_FtpComm::Ftp_DelDir(const char *dirFullName)
{
	FileMsg *pData = NULL;
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
			int nLen = strlen(pData[i].filename);
			if('.' == pData[i].filename[nLen-1])//.和..跳过
				continue;
			//zhangtao 2016-02-18_end
			
			char pathName[260] = {0};
			sprintf(pathName,("%s/%s"),dirFullName,pData[i].filename);
			if(pData[i].nFileType == FTP_TYPE_FILE)
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
	return FtpRmdir(dirFullName, DefaultNetbuf);
}

/**
 * 函数功能：关闭连接
 */
void zt_FtpComm::Ftp_Close()
{
	FtpQuit(DefaultNetbuf);
}

/**
* 函数功能：清空服务器回复信息
*/
void zt_FtpComm::Ftp_ClearResponse()
{
   FtpClearResponse(DefaultNetbuf);
}

/**
* 函数功能：通过服务器回复信息查看是否是目录不存在
* 返回值：1确实不存在 0不是不存在
*/
int zt_FtpComm::Ftp_IsResponseDirectoryNotFound()
{
   if (FtpIsResponseMatch(DefaultNetbuf, "550 Directory not found."))
   {
      return 1;
   }
   return 0;
}

int zt_FtpComm::Ftp_IsResponseDirectoryAlreadyExists()
{
   if (FtpIsResponseMatch(DefaultNetbuf, "550 Directory already exists"))
   {
      return 1;
   }
   return 0;
}

/**
 * 函数功能：下载文件夹
 * 参数说明：pOutput 输出的文件路径 dirName要下载的文件夹名称 dirNum 下载的文件夹的个数
 * 返回值：返回成功的文件个数
 */
int zt_FtpComm::Ftp_DownDir( const char *pOutput, const char *dirName, int *fileNum, int *dirNum,BOOL bZipDel,BOOL bUnZipFailRename )
{
	//1.新建文件夹到本地
#ifdef _UNICODE
	CString strOutPath = _T("");
	USES_CONVERSION;
	strOutPath = A2T(pOutput);
	strOutPath += _T("/");
	if (!PathFileExists(strOutPath))
	{
		if (!::CreateDirectory(strOutPath,NULL))
		{
			return 0;
		}
	}
#else
	char pOutputDirCreat[260] = {0};
	sprintf(pOutputDirCreat,("%s/"),pOutput);
	if (!PathFileExists(pOutputDirCreat))
	{
		if (!::CreateDirectory(pOutputDirCreat,NULL))
		{
			return 0;
		}
	}
#endif // _UNICODE

	
	//2.获取文件夹下文件列表
	FileMsg *pData = NULL;
	int num = 0;
	if(0 == Ftp_Getlist(dirName,&pData,&num)){
		printf(("get list error!\n"));
		return 0;
	}

	if(pData && num>0)
	{ //文件夹非空
		for(int i=0;i<num;i++)
		{
			//zhangtao 2016-02-18_start 过滤.和..
			int nLen = strlen(pData[i].filename);
			if('.' == pData[i].filename[nLen-1])//.和..跳过
				continue;
			//zhangtao 2016-02-18_end

			char pathName[260] = {0};
			sprintf(pathName,("%s/%s"),dirName,pData[i].filename);

			char outPathName[260] = {0};
			char outNoZipPathName[260] = {0};
			if(pData[i].nFileType == FTP_TYPE_FILE)
			{	//若是文件，则直接下载
				//2017/4/28 13:10 wzl 修改下载文件夹带有QLtransDownload的问题
				
				sprintf(outPathName,("%s/%sQLtransDownload"),pOutput,pData[i].filename);
				sprintf(outNoZipPathName,("%s/%s"),pOutput,pData[i].filename);
				//修改下载文件夹带有QLtransDownload的问题 end wzl

				if( 0 == Ftp_Download(outPathName,pathName)){//下载失败，则退出
					free(pData);pData=NULL;
					return 0;
				}
				else
				{
#ifdef _UNICODE
					CString strOutTmpFile = _T("");
					USES_CONVERSION;
					strOutTmpFile = A2T(outPathName);
					if(-1 == TransferEx_UnzipFile(strOutTmpFile,bZipDel))
					{
						if (bUnZipFailRename)
						{
							CString strNoZipPath = A2T(outNoZipPathName);
							MoveFileEx(strOutTmpFile,strNoZipPath,MOVEFILE_REPLACE_EXISTING|MOVEFILE_COPY_ALLOWED);
						}
					}
#else
					CString strOutTmpFile = _T(""),strNoZipPath = _T("");
					strOutTmpFile.Format(_T("%s"),outPathName);
					strNoZipPath.Format(_T("%s"),outNoZipPathName);
					if(-1 == TransferEx_UnzipFile(strOutTmpFile,bZipDel))
					{
						if (bUnZipFailRename)
						{
							MoveFileEx(strOutTmpFile,strNoZipPath,MOVEFILE_REPLACE_EXISTING|MOVEFILE_COPY_ALLOWED);
						}
					}
#endif // _UNICODE
				}
				
				
				*fileNum++;
			}
			else{
				//2017/4/28 13:10 wzl 修改下载文件夹带有QLtransDownload的问题

				sprintf(outPathName,("%s/%s"),pOutput,pData[i].filename);

				//修改下载文件夹带有QLtransDownload的问题 end wzl

				//sprintf(pathName,("%s/"),pathName);
				if( 0 == Ftp_DownDir(outPathName,pathName,fileNum,dirNum,bZipDel,bUnZipFailRename)){//若是文件夹，则递归下载
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
	return 1;
}

/**
* @brief:服务器内部复制文件，通过先下载后上传实现
* @param:pszOrgPath:源服务器的路径,pszDstPath:目标服务器的路径
* @return 0:failed;1:success.
* @example:
Ftp_RemoteCopyFile("秒传/新建文件夹1/上中西合同.doc","秒传/新建文件夹1/上中西合同2.doc");
*/
int zt_FtpComm::Ftp_RemoteCopyFile(const char *pszOrgPath, const char *pszDstPath)
{
#ifndef _UNICODE
   return 0;
#endif
   char outPathName[260] = {0};

   sprintf(outPathName,"%ld.tmp",this);
   auto hProcessBak = m_hProcess;
   m_hProcess = 0; //屏蔽 WM_QL_FTP_PROGRESS
   if( 0 == Ftp_Download(outPathName, pszOrgPath))
   {
      m_hProcess = hProcessBak;
      return 0; //下载失败，则退出
   }

#ifdef _UNICODE
   if (1 != Ftp_Upload(outPathName, pszDstPath))
   {
      remove(outPathName);
      //free(pData);pData=NULL;
      m_hProcess = hProcessBak;
      return 0;
   }
   remove(outPathName);
#endif // _UNICODE
   m_hProcess = hProcessBak;
   return 1;
}

int zt_FtpComm::Ftp_CopyDir(const char *pszTargetDirName, const char *dirName)
{
#ifndef _UNICODE //暂不支持非unicode
   return 0;
#endif

   Ftp_ClearResponse();
   int nMKDir = Ftp_MkDir(pszTargetDirName);
   if (nMKDir == 0)
   {
      if (!Ftp_IsResponseDirectoryAlreadyExists())
      {
         return 0;
      }
   }

   //2.获取文件夹下文件列表
   FileMsg *pData = NULL;
   int num = 0;
   Ftp_ClearResponse();
   int nGetList = Ftp_Getlist(dirName,&pData,&num);
   if(0 == nGetList)
   {
      if (1 == Ftp_IsResponseDirectoryNotFound())
      {
         return 2;
      }
      printf(("get list error!\n"));
      return 0;
   }

   if(pData && num>0)
   { //文件夹非空
      for(int i=0;i<num;i++)
      {
         int nLen = strlen(pData[i].filename);
         if('.' == pData[i].filename[nLen-1])//.和..跳过
            continue;

         char pathName[260] = {0};

         //char outNoZipPathName[260] = {0};
         if(pData[i].nFileType == FTP_TYPE_FILE)
         {	//若是文件，则直接下载
            sprintf(pathName,("%s%s"),dirName,pData[i].filename);

            char szRemotePath[260] = {0};
            sprintf(szRemotePath,("%s%s"),pszTargetDirName, pData[i].filename);
            if (0 == Ftp_RemoteCopyFile(pathName, szRemotePath))
            {
               free(pData);pData=NULL;
               return 0;
            }
         }
         else
         {
            char outPathName[260] = {0};
            sprintf(pathName,("%s%s/"),dirName,pData[i].filename);
            sprintf(outPathName,("%s%s/"),pszTargetDirName, pData[i].filename);

            int nCopyDir = Ftp_CopyDir(outPathName,pathName); //若是文件夹，则递归复制
            if( 0 == nCopyDir)
            {
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
   return 1;
}

int zt_FtpComm::Ftp_DownDirEx( const char *pOutput, const char *dirName,int *fileNum, int *dirNum,HWND hWnd,DWORD wpMsg,int nFlag,BOOL bNoDir,BOOL bZipDel,BOOL bUnZipFailRename )
{
	//1.新建文件夹到本地
#ifdef _UNICODE
	CString strOutPath(pOutput);

	if (!PathFileExists(strOutPath))
	{
		if (!::CreateDirectory(strOutPath,NULL))
		{
			return 0;
		}
	}
   strOutPath += _T("\\");

#else
	char pOutputDirCreat[260] = {0};
	sprintf(pOutputDirCreat,("%s/"),pOutput);
	if (!PathFileExists(pOutputDirCreat))
	{
		if (!::CreateDirectory(pOutputDirCreat,NULL))
		{
			return 0;
		}
	}
#endif // _UNICODE


	//2.获取文件夹下文件列表
	FileMsg *pData = NULL;
	int num = 0;
	if(0 == Ftp_Getlist(dirName,&pData,&num)){
		printf(("get list error!\n"));
		return 0;
	}

	if(pData && num>0)
	{ //文件夹非空
		for(int i=0;i<num;i++)
		{
			//zhangtao 2016-02-18_start 过滤.和..
			int nLen = strlen(pData[i].filename);
			if('.' == pData[i].filename[nLen-1])//.和..跳过
				continue;
			//zhangtao 2016-02-18_end

			char pathName[260] = {0};
			sprintf(pathName,("%s/%s"),dirName,pData[i].filename);

			char outPathName[260] = {0};
			char outNoZipPathName[260] = {0};
			if(pData[i].nFileType == FTP_TYPE_FILE)
			{	//若是文件，则直接下载
				//2017/4/28 13:10 wzl 修改下载文件夹带有QLtransDownload的问题

				sprintf(outPathName,("%s/%sQLtransDownload"),pOutput,pData[i].filename);
				sprintf(outNoZipPathName,("%s/%s"),pOutput,pData[i].filename);
				//修改下载文件夹带有QLtransDownload的问题 end wzl
				LpMsg_QLtransEx *pLpMsg = new LpMsg_QLtransEx;
				ZeroMemory(pLpMsg,sizeof(LpMsg_QLtransEx));

				if( 0 == Ftp_Download(outPathName,pathName)){//下载失败，则退出
					if (NULL != hWnd)
					{
						pLpMsg->nFlag = nFlag;
						pLpMsg->nAction = FTP_ACTION_FAIL;
						//转char *
						char szLocalPath[MAX_PATH];
						sprintf(szLocalPath,("%s/%s"),pOutput,pData[i].filename);
						SendMessage(hWnd,WM_QL_FTP_DOWNDIRMSG,(WPARAM)szLocalPath,(LPARAM)pLpMsg);
					}
					free(pData);pData=NULL;
					return 0;
				}
				else
				{
#ifdef _UNICODE
					CString strOutTmpFile(outPathName);
				

					if(-1 == TransferEx_UnzipFile(strOutTmpFile,bZipDel))
					{
						if (bUnZipFailRename)
						{
							CString strNoZipPath(outNoZipPathName);
							MoveFileEx(strOutTmpFile,strNoZipPath,MOVEFILE_REPLACE_EXISTING|MOVEFILE_COPY_ALLOWED);
						}
					}
#else
					CString strOutTmpFile = _T(""),strNoZipPath = _T("");
					strOutTmpFile.Format(_T("%s"),outPathName);
					strNoZipPath.Format(_T("%s"),outNoZipPathName);
					if(-1 == TransferEx_UnzipFile(strOutTmpFile,bZipDel))
					{
						if (bUnZipFailRename)
						{
							MoveFileEx(strOutTmpFile,strNoZipPath,MOVEFILE_REPLACE_EXISTING|MOVEFILE_COPY_ALLOWED);
						}
					}
#endif // _UNICODE

					if (NULL != hWnd)
					{
						pLpMsg->nFlag = nFlag;
						pLpMsg->nAction = FTP_ACTION_SUC;

						//转char *
						char szLocalPath[MAX_PATH];
						sprintf(szLocalPath,("%s/%s"),pOutput,pData[i].filename);

						SendMessage(hWnd,WM_QL_FTP_DOWNDIRMSG,(WPARAM)szLocalPath,(LPARAM)pLpMsg);
					}
				}

				delete pLpMsg;

				*fileNum++;
			}
			else{
				//2017-08-23 下载文件时子文件夹的内容下载到目标路径下  不考虑重名问题  即重名即覆盖文件
				if(bNoDir)
				{
					if( 0 == Ftp_DownDirEx(pOutput,pathName,fileNum,dirNum,hWnd,wpMsg,nFlag,bNoDir,bZipDel,bUnZipFailRename)){//若是文件夹，则递归下载
						free(pData);pData=NULL;
						return 0;	
					}
				}
				else
				{
					//2017/4/28 13:10 wzl 修改下载文件夹带有QLtransDownload的问题

					sprintf(outPathName,("%s/%s"),pOutput,pData[i].filename);

					//修改下载文件夹带有QLtransDownload的问题 end wzl
					if( 0 == Ftp_DownDirEx(outPathName,pathName,fileNum,dirNum,hWnd,wpMsg,nFlag,bNoDir,bZipDel,bUnZipFailRename)){//若是文件夹，则递归下载
						free(pData);pData=NULL;
						return 0;	
					}
				}
			}
		}
	}
	if(pData){
		free(pData);
		pData=NULL;
	}
	return 1;
}

/**
 * 函数功能：根据目标文件夹中文件的后缀名下载相关的文件
 * 参数说明：
 * 返回值：返回成功的文件个数
 */
int zt_FtpComm::Ftp_DownByEx( const char *pOutput, const char *dirName, char *pExtension,FilePathMsg ** ppPathRecv,int *fileNum,BOOL bDir,HWND hWnd,DWORD wpMsg,int nFlag,BOOL bNoDir,BOOL bZipDel,BOOL bUnZipFailRename)
{
	//1.新建文件夹到本地
#ifdef _UNICODE
	CString strOutPath = _T("");
	wchar_t wcOutPath[MAX_PATH];
	QLCOMAPI.MByteToWChar(pOutput,wcOutPath,MAX_PATH);
	strOutPath.Format(_T("%s/"),wcOutPath);
	if (!PathFileExists(strOutPath))
	{
		if (!::CreateDirectory(strOutPath,NULL))
		{
			return 0;
		}
	}
#else
	char pOutputDirCreat[260] = {0};
	sprintf(pOutputDirCreat,("%s/"),pOutput);
	if (!PathFileExists(pOutputDirCreat))
	{
		if (!::CreateDirectory(pOutputDirCreat,NULL))
		{
			return 0;
		}
	}
#endif // _UNICODE

	//2.获取文件夹下文件列表
	FileMsg *pData = NULL;
	int num = 0;
	if(0 == Ftp_Getlist(dirName,&pData,&num)){
		printf(("get list error!\n"));
		return 2;
	}

	if(pData && num>0)
	{ //文件夹非空
		CStringList oStrList;
		for(int i=0;i<num;i++)
		{
			//zhangtao 2016-02-18_start 过滤.和..
			int nLen = strlen(pData[i].filename);
			if('.' == pData[i].filename[nLen-1])//.和..跳过
				continue;
			//zhangtao 2016-02-18_end

			char pathName[260] = {0};
			sprintf(pathName,("%s/%s"),dirName,pData[i].filename);

			char outPathName[260] = {0};
			sprintf(outPathName,("%s\\%sQLtransDownload"),pOutput,pData[i].filename);

			char outFileName[MAX_PATH] = {0};
			sprintf(outFileName,("%s\\%s"),pOutput,pData[i].filename);

			if(pData[i].nFileType == FTP_TYPE_FILE)
			{	//若是文件，则直接下载
				//比较文件后缀名 若相同则下载,否则跳过

				CString strFileName = CString(pData[i].filename);
				CString strExtension = CString(pExtension);
				CString strNameEx = _T(""),strExtensionEx = _T("");
				strNameEx = PathFindExtension(strFileName);
				strExtensionEx = PathFindExtension(strExtension);
				if (0 == strNameEx.CompareNoCase(strExtensionEx))
				{
					//每个下载的文件都给使用者发送个消息  2017-07-31
					LpMsg_QLtransEx *pLpMsg = new LpMsg_QLtransEx;
					ZeroMemory(pLpMsg,sizeof(LpMsg_QLtransEx));

					if( 0 == Ftp_Download(outPathName,pathName)){//下载失败，则退出
						free(pData);pData=NULL;
						//每个下载的文件都给使用者发送个消息  2017-07-31
						if (NULL != hWnd)
						{
							pLpMsg->nFlag = nFlag;
							pLpMsg->nAction = FTP_ACTION_FAIL;
							
							SendMessage(hWnd,wpMsg,(WPARAM)outFileName,(LPARAM)pLpMsg);
						}

						return 0;
					}
					else
					{
#ifdef _UNICODE
						CString strOutTmpFile = _T("");
						wchar_t wcTmp[MAX_PATH] = {0};
						QLCOMAPI.MByteToWChar(outPathName,wcTmp,MAX_PATH);
						strOutTmpFile.Format(_T("%s"),wcTmp);
						if(-1 == TransferEx_UnzipFile(strOutTmpFile,bZipDel))
						{
							if (bUnZipFailRename)
							{
								CString strOutFileName(outFileName);

								MoveFileEx(strOutTmpFile,strOutFileName,MOVEFILE_REPLACE_EXISTING|MOVEFILE_COPY_ALLOWED);
							}
						}

						QLCOMAPI.MByteToWChar(outFileName,wcTmp,MAX_PATH);
						strOutTmpFile.Format(_T("%s"),wcTmp);
#else
						CString strOutTmpFile = _T("");
						strOutTmpFile.Format(_T("%s"),outPathName);
						if(-1 == TransferEx_UnzipFile(strOutTmpFile,bZipDel))
						{
							if (bUnZipFailRename)
							{
								CString strOutFileName(outFileName);
								MoveFileEx(strOutTmpFile,strOutFileName,MOVEFILE_REPLACE_EXISTING|MOVEFILE_COPY_ALLOWED);
							}
						}

						strOutTmpFile.Format(_T("%s"),outFileName);
#endif // _UNICODE
						oStrList.AddTail(strOutTmpFile);
						//每个下载的文件都给使用者发送个消息  2017-07-31
						if (NULL != hWnd)
						{
							pLpMsg->nFlag = nFlag;
							pLpMsg->nAction = FTP_ACTION_SUC;
							
							SendMessage(hWnd,wpMsg,(WPARAM)outFileName,(LPARAM)pLpMsg);
						}

					}
					(*fileNum)++;
				}
			}
			else if (pData[i].nFileType == FTP_TYPE_DIR)
			{
				if (!bDir)
				{
					continue;
				}

				FilePathMsg * szDirPathRecv = NULL;
				int nDirFileNum = 0;
				if(bNoDir)
				{
					if( 1 != Ftp_DownByEx( pOutput,pathName, pExtension,&szDirPathRecv,&nDirFileNum, bDir,hWnd,wpMsg,nFlag,bNoDir,bZipDel,bUnZipFailRename)){//下载失败，则退出
						free(pData);pData=NULL;
						return 0;
					}
				}
				else
				{
					sprintf(outPathName,("%s/%s"),pOutput,pData[i].filename);
					if( 1 != Ftp_DownByEx( outPathName,pathName, pExtension,&szDirPathRecv,&nDirFileNum, bDir,hWnd,wpMsg,nFlag,bNoDir,bZipDel,bUnZipFailRename)){//下载失败，则退出
						free(pData);pData=NULL;
						return 0;
					}
				}
				
				//下载成功  将所有数据拷贝到strList当中
				int nDirFileIndex = 0;
				for (nDirFileIndex = 0;nDirFileIndex < nDirFileNum;nDirFileIndex++)
				{
					CString strFilePath(szDirPathRecv[nDirFileIndex].filePath);

					oStrList.AddTail(strFilePath);
				}
				*fileNum += nDirFileNum;

				//释放内存
				if (NULL != szDirPathRecv)
				{
					free(szDirPathRecv);
					szDirPathRecv = NULL;
				}
			}
		}

		*ppPathRecv = (FilePathMsg *)malloc(sizeof(FilePathMsg) * (*fileNum));//二维的字符串数组指针   
		memset( *ppPathRecv,0,sizeof(FilePathMsg) * (*fileNum));
		int nIndex = 0,nCount = oStrList.GetCount();
		for (nIndex = 0;nIndex < (*fileNum);nIndex++)
		{
#ifdef _UNICODE
			QLCOMAPI.WCharToMByte(oStrList.GetAt(oStrList.FindIndex(nIndex)),(*ppPathRecv)[nIndex].filePath,MAX_PATH);
#else
			strncpy_s((*ppPathRecv)[nIndex].filePath,(LPSTR)(LPCTSTR)oStrList.GetAt(oStrList.FindIndex(nIndex)), MAX_PATH - 1);
#endif // _UNICODE
		}
	}
	if(pData){
		free(pData);
		pData=NULL;
	}
	return 1;
}

   	/**
	* @brief:在服务器重命名（移动）文件
	* @param :szOrgPath源文件，szDstPath目标文件
	* @return 0:failed;1:success;2:orgFile not exist
	*/
int zt_FtpComm::Ftp_RenameDir(const char *szOrgPath, const char *szDstPath)
{
   netbuf *nData = NULL;
   int nRet = FtpAccess(szOrgPath, FTPLIB_DIR, FTPLIB_ASCII, DefaultNetbuf, &nData);
   if (0 == nRet)
      return 2;
   FtpClose(nData);
   nData = NULL;

   int nDstLen = strlen(szDstPath);
   std::vector<char> vecDstPath;
   vecDstPath.reserve(nDstLen + 1);
   vecDstPath.assign(szDstPath, szDstPath + nDstLen);
   if (vecDstPath.back() == '\\')
   {
      vecDstPath.pop_back();
   }

   int nStartPos = vecDstPath.size() - 1;
   std::vector<int> vecPos;
   int nCount = 0;
   while (nCount < 3)
   {
      int nPos = -2;
      for (int n = nStartPos; n >= 0; --n)
      {
         if (vecDstPath[n] == '\\')
         {
            nPos = n;
            break;
         }
      }

      if (nPos > 0)
      {
         vecDstPath[nPos] = '\0';
         char *pPath = vecDstPath.data();
         int nRet = FtpAccess(pPath, FTPLIB_DIR, FTPLIB_ASCII, DefaultNetbuf, &nData);
         if (1 == nRet)
         {//上级文件夹存在
            FtpClose(nData);
            nData = NULL;
            vecDstPath[nPos] = '\\'; //恢复
            break;
         }

         //上级文件夹不存在
         nStartPos = nPos;
         vecPos.push_back(nPos);
      }
      ++nCount;
   }
   
   if (nCount == 3)
   {
      ASSERT(0);
      return 0; //订单文件夹不存在（一般不会）
   }

   for (int n = nCount - 1; n >= 0; --n)
   {
      char *pPath = vecDstPath.data();
      if (0 == Ftp_MkDir(pPath))
      {
         return 0; //创建文件夹失败
      }
      vecDstPath[vecPos[n]] = '\\';
   }

   nRet = FtpRename(szOrgPath, szDstPath, DefaultNetbuf);
   return nRet;
}