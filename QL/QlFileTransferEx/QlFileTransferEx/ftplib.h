/****************************************************************************/
/*																			*/
/* ftplib.h - header file for callable ftp access routines					*/
/* Copyright (C) 1996, 1997 Thomas Pfau, pfau@cnj.digex.net					*/
/*	73 Catherine Street, South Bound Brook, NJ, 08880						*/
/*																			*/
/* This library is free software; you can redistribute it and/or			*/
/* modify it under the terms of the GNU Library General Public				*/
/* License as published by the Free Software Foundation; either				*/
/* version 2 of the License, or (at your option) any later version.			*/
/* 																			*/
/* This library is distributed in the hope that it will be useful,			*/
/* but WITHOUT ANY WARRANTY; without even the implied warranty of			*/
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU	    */
/* Library General Public License for more details.							*/
/* 																			*/
/* You should have received a copy of the GNU Library General Public	    */
/* License along with this progam; if not, write to the						*/
/* Free Software Foundation, Inc., 59 Temple Place - Suite 330,				*/
/* Boston, MA 02111-1307, USA.												*/
/*																			*/
/****************************************************************************/

#if !defined(__FTPLIB_H)
#define __FTPLIB_H


#if defined(__unix__) || defined(VMS)
#define GLOBALDEF
#define GLOBALREF extern
#elif defined(_WIN32)
#if defined BUILDING_LIBRARY
#define GLOBALDEF __declspec(dllexport)
#define GLOBALREF __declspec(dllexport)
#else
#define GLOBALREF __declspec(dllimport)
#endif
#endif

/* FtpAccess() type codes */
#define FTPLIB_DIR			1
#define FTPLIB_DIR_VERBOSE	2
#define FTPLIB_FILE_READ	3
#define FTPLIB_FILE_WRITE	4

/* FtpAccess() mode codes */
#define FTPLIB_ASCII		'A'
#define FTPLIB_IMAGE		'I'
#define FTPLIB_TEXT			FTPLIB_ASCII
#define FTPLIB_BINARY		FTPLIB_IMAGE

/* connection modes连接模式：被动 主动*/
#define FTPLIB_PASSIVE		1
#define FTPLIB_PORT			2

/* connection option names */
#define FTPLIB_CONNMODE		1
#define FTPLIB_CALLBACK		2
#define FTPLIB_IDLETIME		3
#define FTPLIB_CALLBACKARG	4
#define FTPLIB_CALLBACKBYTES 5

#ifdef __cplusplus
extern "C" {
#endif

typedef struct NetBuf netbuf;
typedef int (*FtpCallback)(netbuf *nControl, int xfered, void *arg);

/* v1 compatibility stuff */
//#if !defined(_FTPLIB_NO_COMPAT)
//extern netbuf *DefaultNetbuf;
/*
GLOBALREF  netbuf *DefaultNetbuf;


#define ftplib_lastresp FtpLastResponse(DefaultNetbuf)
#define ftpInit FtpInit
#define ftpOpen(x) FtpConnect(x, &DefaultNetbuf)
#define ftpLogin(x,y) FtpLogin(x, y, DefaultNetbuf)
#define ftpSite(x) FtpSite(x, DefaultNetbuf)
#define ftpMkdir(x) FtpMkdir(x, DefaultNetbuf)
#define ftpChdir(x) FtpChdir(x, DefaultNetbuf)
#define ftpRmdir(x) FtpRmdir(x, DefaultNetbuf)
#define ftpNlst(x, y) FtpNlst(x, y, DefaultNetbuf)
#define ftpDir(x, y) FtpDir(x, y, DefaultNetbuf)
#define ftpGet(x, y, z) FtpGet(x, y, z, DefaultNetbuf)
#define ftpPut(x, y, z) FtpPut(x, y, z, DefaultNetbuf)
#define ftpRename(x, y) FtpRename(x, y, DefaultNetbuf)
#define ftpDelete(x) FtpDelete(x, DefaultNetbuf)
#define ftpQuit() FtpQuit(DefaultNetbuf)*/
//#endif /* (_FTPLIB_NO_COMPAT) */
/* end v1 compatibility stuff */

/*
FTPlib客户端FTP库
	这些描述适用于FTPlib V4.0。

杂项功能
	FtpInit（） - 初始化库
	FtpSite（） - 发送“SITE”命令
	FtpLastResponse（） - 检索最后一个服务器响应
	FtpSysType（） - 确定远程系统类型
	FtpSize（） - 确定远程文件的大小
	FtpSizeLong（） - 确定远程文件的大小
	FtpModDate（） - 确定文件的修改时间
	FtpSetCallback（） - 建立回调函数
	FtpClearCallback（） - 删除回调函数

服务器连接
	FtpConnect（） - 连接到远程服务器
	FtpLogin（） - 登录到远程机器
	FtpQuit（） - 断开与远程服务器的连接
	FtpOptions（） - 设置连接选项

目录功能
	FtpChdir（） - 更改工作目录
	FtpMkdir（） - 创建一个目录
	FtpRmdir（） - 删除目录
	FtpDir（） - 列出远程目录
	FtpNlst（） - 列出远程目录
	FtpCDUp（） - 切换到父目录
	FtpPwd（） - 确定当前工作目录

文件到文件传输
	FtpGet（） - 恢复远程文件
	FtpPut（） - 发送本地文件到远程
	FtpDelete（） - 删除远程文件
	FtpRename（） - 重命名远程文件

文件到程序传输
	这些例程允许程序访问连接到远程文件和目录的数据流。

	FtpAccess（） - 打开远程文件或目录
	FtpRead（） - 从远程文件或目录中读取
	FtpWrite（） - 写入远程文件
	FtpClose（） - 关闭数据连接

公用事业
	qftp - 命令行ftp实用程序
*/

GLOBALREF void FtpInit(void);
GLOBALREF char *FtpLastResponse(netbuf *nControl);
GLOBALREF int FtpConnect(const char *host, netbuf **nControl);
GLOBALREF int FtpOptions(int opt, long val, netbuf *nControl);
GLOBALREF int FtpLogin(const char *user, const char *pass, netbuf *nControl);
GLOBALREF int FtpAccess(const char *path, int typ, int mode, netbuf *nControl,
    netbuf **nData);
GLOBALREF int FtpRead(void *buf, int max, netbuf *nData);
GLOBALREF int FtpWrite(void *buf, int len, netbuf *nData);
GLOBALREF int FtpClose(netbuf *nData);
GLOBALREF int FtpSite(const char *cmd, netbuf *nControl);
GLOBALREF int FtpSysType(char *buf, int max, netbuf *nControl);
GLOBALREF int FtpMkdir(const char *path, netbuf *nControl);
GLOBALREF int FtpChdir(const char *path, netbuf *nControl);
GLOBALREF int FtpCDUp(netbuf *nControl);
GLOBALREF int FtpRmdir(const char *path, netbuf *nControl);
GLOBALREF int FtpPwd(char *path, int max, netbuf *nControl);
GLOBALREF int FtpNlst(const char *output, const char *path, netbuf *nControl);
GLOBALREF int FtpDir(const char *output, const char *path, netbuf *nControl);
GLOBALREF int FtpSize(const char *path, int *size, char mode, netbuf *nControl);
GLOBALREF int FtpModDate(const char *path, char *dt, int max, netbuf *nControl);
GLOBALREF int FtpGet(const char *output, const char *path, char mode,
	netbuf *nControl);
GLOBALREF int FtpPut(const char *input, const char *path, char mode,
	netbuf *nControl);
GLOBALREF int FtpRename(const char *src, const char *dst, netbuf *nControl);
GLOBALREF int FtpDelete(const char *fnm, netbuf *nControl);
GLOBALREF void FtpQuit(netbuf *nControl);

GLOBALREF void FtpClearResponse(netbuf *nControl);
GLOBALREF int FtpIsResponseMatch(netbuf *nControl, const char *pszResponse);

#ifdef __cplusplus
};
#endif

#endif /* __FTPLIB_H */
