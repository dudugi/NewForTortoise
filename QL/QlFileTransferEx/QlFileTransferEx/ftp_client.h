#pragma once
#include "FileTrans_Handle.h"
#include "QlFileTransferEx.h"
#include "ftplib.h"


static BOOL g_bExitTransferEx_Exit = TRUE;

class zt_FtpComm
{
public:
	zt_FtpComm();
	~zt_FtpComm();

	//pro
	/**
	/* ������Ҫ����   WM_FTP_PROGRESS  ��Ϣ�ľ��   ��������WPARAM������ 
	* ��WPARAM=100��LPARAM=1 ��ʾLoad���
	*/
	void Ftp_ProcessMsg(HWND hWnd);

	/**
	* @brief:��ftp��������������
	* @param:pHost:������IP,pUser:�����û�����pPass:��������
	* @return 0:failed;1:success.
	* @example:
	Ftp_Open("192.168.33.139","zhangt", "123456")
	*/
	int Ftp_Open(const char *pHost,const char *pUser, const char *pPass);

	/**
	* @brief:��ftp�������������ӣ�������������ͨ�ж�
	* @param:pHost:������IP,pUser:�����û�����pPass:��������
	* @return 0:failed;1:success;2:disconnected
	* @example:
	*/
	int Ftp_OpenEx(const char *pHost,const char *pUser, const char *pPass);

	/**
	* @brief:ɾ���������ϵ��ļ�
	* @param:pServerFileName:Ҫɾ�����ļ���
	* @return 0:failed;1:success.
	* @example:
	Ftp_Delete("�봫/msvci70.dll");
	*/
	int Ftp_Delete(const char *pServerFileName);

	/**
	* @brief:��ȡԶ��Ŀ¼���ļ��б�
	* @param :
	* @return 0:failed;1:success.
	*/
	int Ftp_Getlist(const char *pPath,FileMsg **ppItems,int *num);
   
	/**
	* @brief:��ȡԶ��Ŀ¼�������ļ���������Ŀ¼���б�
	* @param :dwStyle �Ƿ�����ļ���
	* @return 0:failed;1:success.
	*/
	int Ftp_Getlist(const char *pPath,FileMsg **ppItems,int *num,DWORD dwStyle);

	/**
	* @brief:�����ļ���������
	* @param:output:Ҫ���ص��ļ���·��,path:��������·��
	* @return 0:failed;1:success.
	* @example:
	Ftp_Download("D:/��������ͬ.doc","�봫/�½��ļ���1/��������ͬ.doc");
	*/
	int Ftp_Download(const char *pOutput, const char *pPath);

   /**
   * @brief:�������ڲ������ļ���ͨ�������غ��ϴ�ʵ��
   * @param:pszOrgPath:Դ��������·��,pszDstPath:Ŀ���������·��
   * @return 0:failed;1:success.
   * @example:
   Ftp_RemoteCopyFile("�봫/�½��ļ���1/��������ͬ.doc","�봫/�½��ļ���1/��������ͬ2.doc");
   */
   int Ftp_RemoteCopyFile(const char *pszOrgPath, const char *pszDstPath);

   //���غ��� ��ԭ����Ftp_Download������ͬ ����ֵ��ͬ�����ӷ���ֵ2��
   //return 0 failed ;1 success;2 file not Exists;
   int Ftp_DownloadEx(const char *pOutput, const char *pPath);


	/**
	* @brief:�ϴ��ļ���������
	* @param:input:Ҫ�ϴ����ļ���·��,path:��������·��
	* @return 0:failed;1:success.
	* @example:
	Ftp_Upload("D:/msvci70.dll","�봫/msvci70.dll");
	*/
	int Ftp_Upload(const char *pInput, const char *pPath);


	/**
	* @brief:�ڷ��������½��ļ���
	* @param :dirName:Ҫ�½����ļ�����
	* @return 0:failed;1:success.
	*/
	int Ftp_MkDir(const char *dirName);


	/**
	* @brief:�ڷ�������ɾ���ļ���
	* @param :dirName:Ҫɾ�����ļ�����(�˲��������ļ���)
	* @return 0:failed;1:success.
	*/
	int Ftp_DelDir(const char *dirName);

   	/**
	* @brief:�ڷ��������������ƶ����ļ�
	* @param :szOrgPathԭ�ļ��� szDstPathĿ���ļ���
	* @return 0:failed;1:success.
	*/
   int Ftp_RenameDir(const char *szOrgPath, const char *szDstPath);

	/**
	* @author : wzl
	* @date : 2017/1/18 13:14
	* @param : 
	* @example : 
	* @return : 
	*/
	int Ftp_DownDir(const char *pOutput, const char *dirName,int *fileNum, int *dirNum,BOOL bZipDel,BOOL bUnZipFailRename);

   /**
   * @brief:Զ�̸��Ʒ������ļ���,�ݹ鸴�ƣ����򸲸�
   * @author : dc
   * @date : 2018/9/14 9:11
   * @param : 
   * @example : 
   * @return : 1:�ɹ� 2:dirName�ļ��в����� 0:����
   */
   int Ftp_CopyDir(const char *pszTargetDirName, const char *dirName);
	
	//bNoDir ����ʱ�����½��ļ��� �������ļ����ص�ָ��Ŀ¼��
	int Ftp_DownDirEx(const char *pOutput, const char *dirName,int *fileNum, int *dirNum,HWND hWnd,DWORD wpMsg,int nFlag,BOOL bNoDir,BOOL bZipDel,BOOL bUnZipFailRename);
   //���ݺ�׺���ض�Ӧ���ļ�
   //0 ʧ�� 1�ɹ� 2��Ӧ��Ŀ¼������

	/**
	* @brief : ����Ŀ���ļ������ļ��ĺ�׺��������ص��ļ�
	* @author : 
	* @date : 
	* @param : 
	* @example : 
	* @return : ���سɹ����ļ�����
	*/
	int Ftp_DownByEx( const char *pOutput, const char *dirName, char *pExtension,FilePathMsg ** szFilePath,int *fileNum,BOOL bDir,HWND hWnd,DWORD wpMsg,int nFlag,BOOL bNoDir,BOOL bZipDel,BOOL bUnZipFailRename);

	/**
	* @brief:�ϴ��ļ��е���������
	* @param:dirFullName:Ҫ�ϴ����ļ��о���·����dirName:�ļ�������svrPath:��������ǰĿ¼
	* @return 0:failed;1:success.
	*/
	int Ftp_UpLoadDir(const char *dirFullName,const char *dirName,const char *svrPath);

	/**
	* @brief:�ϴ��ļ��е���������
	* @param:dirFullName:Ҫ�ϴ����ļ��о���·����svrDirFulllPath:�������ļ��е�ȫ·��
	* @return 0:failed;1:success.
	*/
	int Ftp_UpLoadDir(const char *dirFullName,const char *svrDirFulllPath,HWND hWnd,DWORD wpMsg,int nFlag);

	/**
	* @brief:�ر�����
	*/
	void Ftp_Close();

   void Ftp_ClearResponse();

   int Ftp_IsResponseDirectoryNotFound();

   int Ftp_IsResponseDirectoryAlreadyExists();
private:
	netbuf *DefaultNetbuf;
	HWND m_hProcess;
};
