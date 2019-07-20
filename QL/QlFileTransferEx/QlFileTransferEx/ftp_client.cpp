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
	HWND hProcess; //2017/09/08 zhangt ���������
};

//�����ʽ nFormat:0 -rw-r--r-- 1 ftp ftp             18 Dec 19 14:23 test.txt
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
		//�ļ���
		FileMsg.nFileType = FTP_TYPE_DIR;
	}
	else if ('-' == type)
	{
		//�ļ�
		FileMsg.nFileType = FTP_TYPE_FILE;
	}
	else
	{
		//'c'-�ַ����豸  ��b��-���豸
		FileMsg.nFileType = FTP_TYPE_OTHER;
	}
	//Ȩ�����Σ��û�Ȩ��/�û���Ȩ��/������Ȩ�� 
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

	//������
	//�·ݴ���
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
 * �������ܣ���ftp��������������
 * ����˵��:pHost:������IP,pUser:�����û�����pPass:��������
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
	//2018/03/01 zhangt ���ӶԵ�ǰ������ж�
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
 * �������ܣ�ɾ���������ϵ��ļ�
 * ����˵��:pServerFileName:Ҫɾ�����ļ���
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
		remove(szFile);//2017/09/08 zhangt ɾ����ʱ�ļ�
		return 0;
	}
	FILE *fp = NULL;
	char line[1024] = {0};
	memset(line, 0, 1024);
	if (NULL == (fp = fopen(szFile/*FTPLISTFILE*/, "r+")))
	{
		remove(szFile);//2017/09/08 zhangt ɾ����ʱ�ļ�
		return 0;
	}
	int linenum = 0;
	while (fgets(line, 1024, fp) !=NULL)
	{
		int len = strlen(line);
		if(len<40){
			fclose(fp);
			remove(szFile);//2017/09/08 zhangt ɾ����ʱ�ļ�
			return 0;
		}
		linenum++;
	}
	if(linenum == 0){
		fclose(fp);
		remove(szFile);//2017/09/08 zhangt ɾ����ʱ�ļ�
		return 1;
	}

	*ppItems = (FileMsg*)malloc(sizeof(FileMsg)*linenum);
	if(*ppItems == NULL){
		fclose(fp);
		remove(szFile);//2017/09/08 zhangt ɾ����ʱ�ļ�
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
			remove(szFile);//2017/09/08 zhangt ɾ����ʱ�ļ�
			return 0;
		}

		//line���ݴ���
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
			remove(szFile);//2017/09/08 zhangt ɾ����ʱ�ļ�
			return 0;
		}
		memset(line, 0, 1024);
	}

	fclose(fp);
	remove(szFile);//2017/09/08 zhangt ɾ����ʱ�ļ�
	*num = linenum;

	return 1;
}

int zt_FtpComm::Ftp_Getlist(const char *pPath,FileMsg **ppItems,int *num,DWORD dwStyle)
{
   char szFile[260];
   sprintf(szFile,"%ld.tmp",this);
   *num =0;
   *ppItems=NULL;//��մ����ָ��
   //��ȡָ���ļ��е��б��ļ�����  ��ʱ���������ļ���
   if(0 == FtpDir(szFile/*FTPLISTFILE*/, pPath, DefaultNetbuf))
   {
      remove(szFile);//2017/09/08 zhangt ɾ����ʱ�ļ�
      return 0;
   }

   //���ļ��б����չ
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

   vector<s_FileMsgEx> vec_FileMsgEx;//������׼���� �������е��ļ���Ϣ
   s_FileMsgEx oFileMsg;//������ǰ��������Ϣ

   //����
   FILE *fp = NULL;
   char line[1024] = {0};
   memset(line, 0, 1024);
   if (NULL == (fp = fopen(szFile/*FTPLISTFILE*/, "r+")))
   {
      remove(szFile);//2017/09/08 zhangt ɾ����ʱ�ļ�
      return 0;
   }
   int linenum = 0;
   while (fgets(line, 1024, fp) !=NULL)
   {
      int len = strlen(line);
      if(len<40){
         fclose(fp);
         remove(szFile);//2017/09/08 zhangt ɾ����ʱ�ļ�
         return 0;
      }
      linenum++;
   }
   if(linenum == 0){
      fclose(fp);
      remove(szFile);//2017/09/08 zhangt ɾ����ʱ�ļ�
      return 1;
   }

   oFileMsg.pItem = (FileMsg*)malloc(sizeof(FileMsg)*linenum);//�����ռ��ȡ�б���Ϣ
   //*ppItems = (FileMsg*)malloc(sizeof(FileMsg)*linenum);
   if(NULL == oFileMsg.pItem){
      fclose(fp);
      remove(szFile);//2017/09/08 zhangt ɾ����ʱ�ļ�

      delete oFileMsg.pItem;//ɾ��ռ�õĿռ�
      oFileMsg.pItem = NULL;
      
      return 0;
   }
   memset(oFileMsg.pItem,0,sizeof(FileMsg)*linenum);//�����Ϣ
   fseek(fp,0,0);
   int i =0;

   while (fgets(line, 1024, fp) !=NULL)
   {
      int len = strlen(line);
      if(len<40){
         fclose(fp);
         remove(szFile);//2017/09/08 zhangt ɾ����ʱ�ļ�

         delete oFileMsg.pItem;//ɾ��ռ�õĿռ�
         oFileMsg.pItem = NULL;

         return 0;
      }

      //line���ݴ���
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
         remove(szFile);//2017/09/08 zhangt ɾ����ʱ�ļ�

         delete oFileMsg.pItem;//ɾ��ռ�õĿռ�
         oFileMsg.pItem = NULL;

         return 0;
      }
      memset(line, 0, 1024);
   }

   fclose(fp);
   remove(szFile);//2017/09/08 zhangt ɾ����ʱ�ļ�

   //�����еĵ�ǰ��ȡ������ д�뵽��������
   oFileMsg.nFileNum = linenum;
   vec_FileMsgEx.push_back(oFileMsg);

   linenum = 0;
   //-------------------------------------------------------
   if (FS_NODIR == dwStyle)//����Ǻ����ļ��� 
   {
      for (int nFileListIndex = 0;nFileListIndex < oFileMsg.nFileNum;++nFileListIndex)
      {
         ++linenum;//�ļ�����+1 �ļ���Ҳ�������ļ�����
         if(FTP_TYPE_DIR == oFileMsg.pItem[nFileListIndex].nFileType)
         {
            //������ļ���  ������ļ��е����ݽ��б��� 
            s_FileMsgEx oChildFileMsg;
            //���ñ��������ļ��� 
            //������ǰ������
            char pathName[260] = {0};
            sprintf(pathName,"%s/%s",pPath,oFileMsg.pItem[nFileListIndex].filename);

            if(1 == Ftp_Getlist(pathName,&(oChildFileMsg.pItem),&oChildFileMsg.nFileNum,dwStyle))
            {
               sprintf(oChildFileMsg.szParrentName,"%s",oFileMsg.pItem[nFileListIndex].filename);

               vec_FileMsgEx.push_back(oChildFileMsg);

               linenum += oChildFileMsg.nFileNum ;//�����ļ��е��б������ӵ���ǰ������֮�� ����
            }
            else
            {
               //�ͷ�����ռ�õĿռ�
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

   //new�����صĿռ�

   *ppItems = (FileMsg*)malloc(sizeof(FileMsg)*linenum);
   if(NULL == *ppItems){
      //����ռ�ʧ�� ֱ�ӷ���
      return 0;
   }
   memset(*ppItems,0,sizeof(FileMsg)*linenum);


   //���������е����ļ��в�������뵽��������
   int nIndex = 0;
   for (auto it = vec_FileMsgEx.begin();it != vec_FileMsgEx.end();++it)
   {
      for (int nChildIndex = 0;nChildIndex < it->nFileNum && nIndex < linenum;++nChildIndex)
      {
         if(0 != strlen(it->szParrentName))//��·���ĳ��Ȳ�Ϊ0 ���ļ��� = ���ļ��� + ��ǰ�ļ���
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

         ++nIndex;//����ֵ����
      }

      //���ռ�ÿռ�
      delete it->pItem;
      it->pItem = NULL;
   }

   *num = linenum;

   return 1;
}

/**
 * �������ܣ������ļ���������
 * ����˵��:output:Ҫ���ص��ļ���·��,path:��������·��
 * return 0:failed;1:success.
 */
int zt_FtpComm::Ftp_Download(const char *pOutput, const char *pPath)
{
	//�ο���http://blog.chinaunix.net/uid-23381466-id-58855.html
	int sts=0;
	int fsz;

	FtpOptions(FTPLIB_CALLBACK, (long) NULL,DefaultNetbuf);

	struct REMFILE *f;
	f = (struct REMFILE *) malloc(sizeof(struct REMFILE));
	memset(f,0,sizeof(struct REMFILE));
	f->fnm = strdup(pOutput);
	f->hProcess = m_hProcess;//�����������ֵ
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
   //�ο���http://blog.chinaunix.net/uid-23381466-id-58855.html
   int sts=0;
   int fsz;

   FtpOptions(FTPLIB_CALLBACK, (long) NULL,DefaultNetbuf);

   struct REMFILE *f;
   f = (struct REMFILE *) malloc(sizeof(struct REMFILE));
   memset(f,0,sizeof(struct REMFILE));
   f->fnm = strdup(pOutput);
   f->hProcess = m_hProcess;//�����������ֵ
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
 * �������ܣ��ϴ��ļ���������
 * ����˵��:input:Ҫ�ϴ����ļ���·��,path:��������·��
 * return 0:failed;1:success.
 */
int zt_FtpComm::Ftp_Upload(const char *pInput, const char *pPath)
{
	//�ο���http://blog.chinaunix.net/uid-23381466-id-58854.html
	int sts=0;
	int fsz;

	FtpOptions(FTPLIB_CALLBACK, (long) NULL, DefaultNetbuf);
	struct REMFILE *f;
	f = (struct REMFILE *) malloc(sizeof(struct REMFILE));
	memset(f,0,sizeof(struct REMFILE));
	f->fnm = strdup(pInput);
	f->hProcess = m_hProcess;//�����������ֵ

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
 * �������ܣ��ڷ��������½��ļ���
 * ����˵��:dirName:Ҫ�½����ļ�����
 * return 0:failed;1:success.
 */
int zt_FtpComm::Ftp_MkDir(const char *dirName)
{
	return FtpMkdir(dirName, DefaultNetbuf);
}

/**
 * �������ܣ��ϴ��ļ��е���������
 * ����˵��:dirFullName:Ҫ�ϴ����ļ��о���·����dirName:�ļ�������svrPath:��������ǰĿ¼
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
	while (IsFinded)  //Ŀ¼�����ļ�
	{  
		IsFinded = tempFind.FindNextFile(); 
		if (!tempFind.IsDots())  //���ǡ�.����..��
		{  
#ifdef _UNICODE
			USES_CONVERSION;
			char * sFoundFileName = T2A(tempFind.GetFileName());
#else
			char sFoundFileName[260];
			strcpy(sFoundFileName,(LPSTR)(LPCSTR)tempFind.GetFileName().GetBuffer());
#endif // _UNICODE

			if (tempFind.IsDirectory())  //���ļ���
			{  
				char sTempDir[260];  
				sprintf(sTempDir,("%s\\%s"),dirFullName,sFoundFileName);  
				char svrTempFullDirName[260];
				sprintf(svrTempFullDirName,("%s/%s"),svrPath,dirName);
				if(0 == Ftp_UpLoadDir(sTempDir,sFoundFileName,svrTempFullDirName)){  // Ƕ�׺���
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
	while (IsFinded)  //Ŀ¼�����ļ�
	{  
		IsFinded = tempFind.FindNextFile(); 
		if (!tempFind.IsDots())  //���ǡ�.����..��
		{  
#ifdef _UNICODE
			USES_CONVERSION;
			char * sFoundFileName = T2A(tempFind.GetFileName());
#else
			char sFoundFileName[260];
			strcpy(sFoundFileName,(LPSTR)(LPCSTR)tempFind.GetFileName().GetBuffer());
#endif // _UNICODE

			if (tempFind.IsDirectory())  //���ļ���
			{  
				char sTempDir[260];  
				sprintf(sTempDir,("%s\\%s"),dirFullName,sFoundFileName);  
				char svrTempFullDirName[260];
				sprintf(svrTempFullDirName,("%s/%s"),svrDirFulllPath,sFoundFileName);
				if(0 == Ftp_UpLoadDir(sTempDir,svrTempFullDirName,hWnd,wpMsg,nFlag)){  // Ƕ�׺���
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
 * �������ܣ��ڷ�������ɾ���ļ���
 * ����˵��:dirFullName:Ҫɾ�����ļ�����
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
	{ //�ļ��зǿ�
		for(int i=0;i<num;i++)
		{
			//zhangtao 2016-02-18_start ����.��..
			int nLen = strlen(pData[i].filename);
			if('.' == pData[i].filename[nLen-1])//.��..����
				continue;
			//zhangtao 2016-02-18_end
			
			char pathName[260] = {0};
			sprintf(pathName,("%s/%s"),dirFullName,pData[i].filename);
			if(pData[i].nFileType == FTP_TYPE_FILE)
			{	//�����ļ�����ֱ��ɾ��
				if( 0 == Ftp_Delete(pathName)){//ɾ��ʧ�ܣ����˳�
					free(pData);pData=NULL;
					return 0;
				}
			}
			else{
				//sprintf(pathName,("%s/"),pathName);
				if( 0 == Ftp_DelDir(pathName)){//�����ļ��У���ݹ�ɾ��
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
 * �������ܣ��ر�����
 */
void zt_FtpComm::Ftp_Close()
{
	FtpQuit(DefaultNetbuf);
}

/**
* �������ܣ���շ������ظ���Ϣ
*/
void zt_FtpComm::Ftp_ClearResponse()
{
   FtpClearResponse(DefaultNetbuf);
}

/**
* �������ܣ�ͨ���������ظ���Ϣ�鿴�Ƿ���Ŀ¼������
* ����ֵ��1ȷʵ������ 0���ǲ�����
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
 * �������ܣ������ļ���
 * ����˵����pOutput ������ļ�·�� dirNameҪ���ص��ļ������� dirNum ���ص��ļ��еĸ���
 * ����ֵ�����سɹ����ļ�����
 */
int zt_FtpComm::Ftp_DownDir( const char *pOutput, const char *dirName, int *fileNum, int *dirNum,BOOL bZipDel,BOOL bUnZipFailRename )
{
	//1.�½��ļ��е�����
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

	
	//2.��ȡ�ļ������ļ��б�
	FileMsg *pData = NULL;
	int num = 0;
	if(0 == Ftp_Getlist(dirName,&pData,&num)){
		printf(("get list error!\n"));
		return 0;
	}

	if(pData && num>0)
	{ //�ļ��зǿ�
		for(int i=0;i<num;i++)
		{
			//zhangtao 2016-02-18_start ����.��..
			int nLen = strlen(pData[i].filename);
			if('.' == pData[i].filename[nLen-1])//.��..����
				continue;
			//zhangtao 2016-02-18_end

			char pathName[260] = {0};
			sprintf(pathName,("%s/%s"),dirName,pData[i].filename);

			char outPathName[260] = {0};
			char outNoZipPathName[260] = {0};
			if(pData[i].nFileType == FTP_TYPE_FILE)
			{	//�����ļ�����ֱ������
				//2017/4/28 13:10 wzl �޸������ļ��д���QLtransDownload������
				
				sprintf(outPathName,("%s/%sQLtransDownload"),pOutput,pData[i].filename);
				sprintf(outNoZipPathName,("%s/%s"),pOutput,pData[i].filename);
				//�޸������ļ��д���QLtransDownload������ end wzl

				if( 0 == Ftp_Download(outPathName,pathName)){//����ʧ�ܣ����˳�
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
				//2017/4/28 13:10 wzl �޸������ļ��д���QLtransDownload������

				sprintf(outPathName,("%s/%s"),pOutput,pData[i].filename);

				//�޸������ļ��д���QLtransDownload������ end wzl

				//sprintf(pathName,("%s/"),pathName);
				if( 0 == Ftp_DownDir(outPathName,pathName,fileNum,dirNum,bZipDel,bUnZipFailRename)){//�����ļ��У���ݹ�����
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
* @brief:�������ڲ������ļ���ͨ�������غ��ϴ�ʵ��
* @param:pszOrgPath:Դ��������·��,pszDstPath:Ŀ���������·��
* @return 0:failed;1:success.
* @example:
Ftp_RemoteCopyFile("�봫/�½��ļ���1/��������ͬ.doc","�봫/�½��ļ���1/��������ͬ2.doc");
*/
int zt_FtpComm::Ftp_RemoteCopyFile(const char *pszOrgPath, const char *pszDstPath)
{
#ifndef _UNICODE
   return 0;
#endif
   char outPathName[260] = {0};

   sprintf(outPathName,"%ld.tmp",this);
   auto hProcessBak = m_hProcess;
   m_hProcess = 0; //���� WM_QL_FTP_PROGRESS
   if( 0 == Ftp_Download(outPathName, pszOrgPath))
   {
      m_hProcess = hProcessBak;
      return 0; //����ʧ�ܣ����˳�
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
#ifndef _UNICODE //�ݲ�֧�ַ�unicode
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

   //2.��ȡ�ļ������ļ��б�
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
   { //�ļ��зǿ�
      for(int i=0;i<num;i++)
      {
         int nLen = strlen(pData[i].filename);
         if('.' == pData[i].filename[nLen-1])//.��..����
            continue;

         char pathName[260] = {0};

         //char outNoZipPathName[260] = {0};
         if(pData[i].nFileType == FTP_TYPE_FILE)
         {	//�����ļ�����ֱ������
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

            int nCopyDir = Ftp_CopyDir(outPathName,pathName); //�����ļ��У���ݹ鸴��
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
	//1.�½��ļ��е�����
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


	//2.��ȡ�ļ������ļ��б�
	FileMsg *pData = NULL;
	int num = 0;
	if(0 == Ftp_Getlist(dirName,&pData,&num)){
		printf(("get list error!\n"));
		return 0;
	}

	if(pData && num>0)
	{ //�ļ��зǿ�
		for(int i=0;i<num;i++)
		{
			//zhangtao 2016-02-18_start ����.��..
			int nLen = strlen(pData[i].filename);
			if('.' == pData[i].filename[nLen-1])//.��..����
				continue;
			//zhangtao 2016-02-18_end

			char pathName[260] = {0};
			sprintf(pathName,("%s/%s"),dirName,pData[i].filename);

			char outPathName[260] = {0};
			char outNoZipPathName[260] = {0};
			if(pData[i].nFileType == FTP_TYPE_FILE)
			{	//�����ļ�����ֱ������
				//2017/4/28 13:10 wzl �޸������ļ��д���QLtransDownload������

				sprintf(outPathName,("%s/%sQLtransDownload"),pOutput,pData[i].filename);
				sprintf(outNoZipPathName,("%s/%s"),pOutput,pData[i].filename);
				//�޸������ļ��д���QLtransDownload������ end wzl
				LpMsg_QLtransEx *pLpMsg = new LpMsg_QLtransEx;
				ZeroMemory(pLpMsg,sizeof(LpMsg_QLtransEx));

				if( 0 == Ftp_Download(outPathName,pathName)){//����ʧ�ܣ����˳�
					if (NULL != hWnd)
					{
						pLpMsg->nFlag = nFlag;
						pLpMsg->nAction = FTP_ACTION_FAIL;
						//תchar *
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

						//תchar *
						char szLocalPath[MAX_PATH];
						sprintf(szLocalPath,("%s/%s"),pOutput,pData[i].filename);

						SendMessage(hWnd,WM_QL_FTP_DOWNDIRMSG,(WPARAM)szLocalPath,(LPARAM)pLpMsg);
					}
				}

				delete pLpMsg;

				*fileNum++;
			}
			else{
				//2017-08-23 �����ļ�ʱ���ļ��е��������ص�Ŀ��·����  ��������������  �������������ļ�
				if(bNoDir)
				{
					if( 0 == Ftp_DownDirEx(pOutput,pathName,fileNum,dirNum,hWnd,wpMsg,nFlag,bNoDir,bZipDel,bUnZipFailRename)){//�����ļ��У���ݹ�����
						free(pData);pData=NULL;
						return 0;	
					}
				}
				else
				{
					//2017/4/28 13:10 wzl �޸������ļ��д���QLtransDownload������

					sprintf(outPathName,("%s/%s"),pOutput,pData[i].filename);

					//�޸������ļ��д���QLtransDownload������ end wzl
					if( 0 == Ftp_DownDirEx(outPathName,pathName,fileNum,dirNum,hWnd,wpMsg,nFlag,bNoDir,bZipDel,bUnZipFailRename)){//�����ļ��У���ݹ�����
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
 * �������ܣ�����Ŀ���ļ������ļ��ĺ�׺��������ص��ļ�
 * ����˵����
 * ����ֵ�����سɹ����ļ�����
 */
int zt_FtpComm::Ftp_DownByEx( const char *pOutput, const char *dirName, char *pExtension,FilePathMsg ** ppPathRecv,int *fileNum,BOOL bDir,HWND hWnd,DWORD wpMsg,int nFlag,BOOL bNoDir,BOOL bZipDel,BOOL bUnZipFailRename)
{
	//1.�½��ļ��е�����
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

	//2.��ȡ�ļ������ļ��б�
	FileMsg *pData = NULL;
	int num = 0;
	if(0 == Ftp_Getlist(dirName,&pData,&num)){
		printf(("get list error!\n"));
		return 2;
	}

	if(pData && num>0)
	{ //�ļ��зǿ�
		CStringList oStrList;
		for(int i=0;i<num;i++)
		{
			//zhangtao 2016-02-18_start ����.��..
			int nLen = strlen(pData[i].filename);
			if('.' == pData[i].filename[nLen-1])//.��..����
				continue;
			//zhangtao 2016-02-18_end

			char pathName[260] = {0};
			sprintf(pathName,("%s/%s"),dirName,pData[i].filename);

			char outPathName[260] = {0};
			sprintf(outPathName,("%s\\%sQLtransDownload"),pOutput,pData[i].filename);

			char outFileName[MAX_PATH] = {0};
			sprintf(outFileName,("%s\\%s"),pOutput,pData[i].filename);

			if(pData[i].nFileType == FTP_TYPE_FILE)
			{	//�����ļ�����ֱ������
				//�Ƚ��ļ���׺�� ����ͬ������,��������

				CString strFileName = CString(pData[i].filename);
				CString strExtension = CString(pExtension);
				CString strNameEx = _T(""),strExtensionEx = _T("");
				strNameEx = PathFindExtension(strFileName);
				strExtensionEx = PathFindExtension(strExtension);
				if (0 == strNameEx.CompareNoCase(strExtensionEx))
				{
					//ÿ�����ص��ļ�����ʹ���߷��͸���Ϣ  2017-07-31
					LpMsg_QLtransEx *pLpMsg = new LpMsg_QLtransEx;
					ZeroMemory(pLpMsg,sizeof(LpMsg_QLtransEx));

					if( 0 == Ftp_Download(outPathName,pathName)){//����ʧ�ܣ����˳�
						free(pData);pData=NULL;
						//ÿ�����ص��ļ�����ʹ���߷��͸���Ϣ  2017-07-31
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
						//ÿ�����ص��ļ�����ʹ���߷��͸���Ϣ  2017-07-31
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
					if( 1 != Ftp_DownByEx( pOutput,pathName, pExtension,&szDirPathRecv,&nDirFileNum, bDir,hWnd,wpMsg,nFlag,bNoDir,bZipDel,bUnZipFailRename)){//����ʧ�ܣ����˳�
						free(pData);pData=NULL;
						return 0;
					}
				}
				else
				{
					sprintf(outPathName,("%s/%s"),pOutput,pData[i].filename);
					if( 1 != Ftp_DownByEx( outPathName,pathName, pExtension,&szDirPathRecv,&nDirFileNum, bDir,hWnd,wpMsg,nFlag,bNoDir,bZipDel,bUnZipFailRename)){//����ʧ�ܣ����˳�
						free(pData);pData=NULL;
						return 0;
					}
				}
				
				//���سɹ�  ���������ݿ�����strList����
				int nDirFileIndex = 0;
				for (nDirFileIndex = 0;nDirFileIndex < nDirFileNum;nDirFileIndex++)
				{
					CString strFilePath(szDirPathRecv[nDirFileIndex].filePath);

					oStrList.AddTail(strFilePath);
				}
				*fileNum += nDirFileNum;

				//�ͷ��ڴ�
				if (NULL != szDirPathRecv)
				{
					free(szDirPathRecv);
					szDirPathRecv = NULL;
				}
			}
		}

		*ppPathRecv = (FilePathMsg *)malloc(sizeof(FilePathMsg) * (*fileNum));//��ά���ַ�������ָ��   
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
	* @brief:�ڷ��������������ƶ����ļ�
	* @param :szOrgPathԴ�ļ���szDstPathĿ���ļ�
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
         {//�ϼ��ļ��д���
            FtpClose(nData);
            nData = NULL;
            vecDstPath[nPos] = '\\'; //�ָ�
            break;
         }

         //�ϼ��ļ��в�����
         nStartPos = nPos;
         vecPos.push_back(nPos);
      }
      ++nCount;
   }
   
   if (nCount == 3)
   {
      ASSERT(0);
      return 0; //�����ļ��в����ڣ�һ�㲻�ᣩ
   }

   for (int n = nCount - 1; n >= 0; --n)
   {
      char *pPath = vecDstPath.data();
      if (0 == Ftp_MkDir(pPath))
      {
         return 0; //�����ļ���ʧ��
      }
      vecDstPath[vecPos[n]] = '\\';
   }

   nRet = FtpRename(szOrgPath, szDstPath, DefaultNetbuf);
   return nRet;
}