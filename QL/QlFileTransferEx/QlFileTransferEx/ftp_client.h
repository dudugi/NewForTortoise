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
	/* 设置需要接收   WM_FTP_PROGRESS  消息的句柄   进度数在WPARAM参数中 
	* 当WPARAM=100且LPARAM=1 表示Load完成
	*/
	void Ftp_ProcessMsg(HWND hWnd);

	/**
	* @brief:与ftp服务器建立连接
	* @param:pHost:服务器IP,pUser:登入用户名，pPass:登入密码
	* @return 0:failed;1:success.
	* @example:
	Ftp_Open("192.168.33.139","zhangt", "123456")
	*/
	int Ftp_Open(const char *pHost,const char *pUser, const char *pPass);

	/**
	* @brief:与ftp服务器建立连接，增加与主机连通判断
	* @param:pHost:服务器IP,pUser:登入用户名，pPass:登入密码
	* @return 0:failed;1:success;2:disconnected
	* @example:
	*/
	int Ftp_OpenEx(const char *pHost,const char *pUser, const char *pPass);

	/**
	* @brief:删除服务器上的文件
	* @param:pServerFileName:要删除的文件名
	* @return 0:failed;1:success.
	* @example:
	Ftp_Delete("秒传/msvci70.dll");
	*/
	int Ftp_Delete(const char *pServerFileName);

	/**
	* @brief:获取远程目录下文件列表
	* @param :
	* @return 0:failed;1:success.
	*/
	int Ftp_Getlist(const char *pPath,FileMsg **ppItems,int *num);
   
	/**
	* @brief:获取远程目录下所有文件（包含子目录）列表
	* @param :dwStyle 是否忽略文件夹
	* @return 0:failed;1:success.
	*/
	int Ftp_Getlist(const char *pPath,FileMsg **ppItems,int *num,DWORD dwStyle);

	/**
	* @brief:下载文件到服务器
	* @param:output:要下载的文件名路径,path:服务器的路径
	* @return 0:failed;1:success.
	* @example:
	Ftp_Download("D:/上中西合同.doc","秒传/新建文件夹1/上中西合同.doc");
	*/
	int Ftp_Download(const char *pOutput, const char *pPath);

   /**
   * @brief:服务器内部复制文件，通过先下载后上传实现
   * @param:pszOrgPath:源服务器的路径,pszDstPath:目标服务器的路径
   * @return 0:failed;1:success.
   * @example:
   Ftp_RemoteCopyFile("秒传/新建文件夹1/上中西合同.doc","秒传/新建文件夹1/上中西合同2.doc");
   */
   int Ftp_RemoteCopyFile(const char *pszOrgPath, const char *pszDstPath);

   //下载函数 与原函数Ftp_Download功能相同 返回值不同（增加返回值2）
   //return 0 failed ;1 success;2 file not Exists;
   int Ftp_DownloadEx(const char *pOutput, const char *pPath);


	/**
	* @brief:上传文件到服务器
	* @param:input:要上传的文件名路径,path:服务器的路径
	* @return 0:failed;1:success.
	* @example:
	Ftp_Upload("D:/msvci70.dll","秒传/msvci70.dll");
	*/
	int Ftp_Upload(const char *pInput, const char *pPath);


	/**
	* @brief:在服务器上新建文件夹
	* @param :dirName:要新建的文件夹名
	* @return 0:failed;1:success.
	*/
	int Ftp_MkDir(const char *dirName);


	/**
	* @brief:在服务器上删除文件夹
	* @param :dirName:要删除的文件夹名(此不存在子文件夹)
	* @return 0:failed;1:success.
	*/
	int Ftp_DelDir(const char *dirName);

   	/**
	* @brief:在服务器重命名（移动）文件
	* @param :szOrgPath原文件名 szDstPath目标文件名
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
   * @brief:远程复制服务器文件夹,递归复制，有则覆盖
   * @author : dc
   * @date : 2018/9/14 9:11
   * @param : 
   * @example : 
   * @return : 1:成功 2:dirName文件夹不存在 0:其他
   */
   int Ftp_CopyDir(const char *pszTargetDirName, const char *dirName);
	
	//bNoDir 下载时不会新建文件夹 将所有文件下载到指定目录下
	int Ftp_DownDirEx(const char *pOutput, const char *dirName,int *fileNum, int *dirNum,HWND hWnd,DWORD wpMsg,int nFlag,BOOL bNoDir,BOOL bZipDel,BOOL bUnZipFailRename);
   //根据后缀下载对应的文件
   //0 失败 1成功 2对应的目录不存在

	/**
	* @brief : 根据目标文件夹中文件的后缀名下载相关的文件
	* @author : 
	* @date : 
	* @param : 
	* @example : 
	* @return : 返回成功的文件个数
	*/
	int Ftp_DownByEx( const char *pOutput, const char *dirName, char *pExtension,FilePathMsg ** szFilePath,int *fileNum,BOOL bDir,HWND hWnd,DWORD wpMsg,int nFlag,BOOL bNoDir,BOOL bZipDel,BOOL bUnZipFailRename);

	/**
	* @brief:上传文件夹到服务器上
	* @param:dirFullName:要上传的文件夹绝对路径，dirName:文件夹名，svrPath:服务器当前目录
	* @return 0:failed;1:success.
	*/
	int Ftp_UpLoadDir(const char *dirFullName,const char *dirName,const char *svrPath);

	/**
	* @brief:上传文件夹到服务器上
	* @param:dirFullName:要上传的文件夹绝对路径，svrDirFulllPath:服务器文件夹的全路径
	* @return 0:failed;1:success.
	*/
	int Ftp_UpLoadDir(const char *dirFullName,const char *svrDirFulllPath,HWND hWnd,DWORD wpMsg,int nFlag);

	/**
	* @brief:关闭连接
	*/
	void Ftp_Close();

   void Ftp_ClearResponse();

   int Ftp_IsResponseDirectoryNotFound();

   int Ftp_IsResponseDirectoryAlreadyExists();
private:
	netbuf *DefaultNetbuf;
	HWND m_hProcess;
};
