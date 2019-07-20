// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE 类
#include <afxodlgs.h>       // MFC OLE 对话框类
#include <afxdisp.h>        // MFC 自动化类
#endif // _AFX_NO_OLE_SUPPORT

#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>                      // MFC ODBC 数据库类
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>                     // MFC DAO 数据库类
#endif // _AFX_NO_DAO_SUPPORT

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#pragma warning(disable:4244)
#pragma warning(disable:4995)
#pragma warning(disable:4996)
#pragma warning(disable:4099)//pdb未找到屏蔽


#include "SpecItem.h"
#include <afxcontrolbars.h>

//添加判断网络状态函数需要包含头文件
#include <Sensapi.h>
#pragma comment(lib, "Sensapi.lib")

//加载GDI+
#include "gdiplus.h"  
using namespace Gdiplus;
#pragma comment(lib, "gdiplus.lib") 

#include "../Lib_ProgressLoading/Lib_ProcessIO.h"
#ifdef _UNICODE
#ifdef _DEBUG
#pragma comment(lib,"Libs/Lib_ProgressLoading_ud.lib")
#else
#pragma comment(lib,"Libs/Lib_ProgressLoading_u.lib")
#endif // _DEBUG
#else
#ifdef _DEBUG
#pragma comment(lib,"Libs/Lib_ProgressLoading_d.lib")
#else
#pragma comment(lib,"Libs/Lib_ProgressLoading.lib")
#endif // _DEBUG
#endif // _UNICODE

//数据库中字段

#define DBWorkLog_key_Cate		_T("cCate")				//类别
#define DBWorkLog_key_Code		_T("cCode")				//单号
#define DBWorkLog_key_Date		_T("dDate")				//日期
#define DBWorkLog_key_Maker		_T("cMaker")			//操作人
#define DBWorkLog_key_Type		_T("cType")				//类型
#define DBWorkLog_key_Detail	_T("cMemo")				//具体行为



/******************字符串加密 秘钥常量*************************/
#define FTP_WORD_PWD_KEY			52369
#define FTP_CONST_PWD_C1			52845
#define FTP_CONST_PWD_C2			22719

#define STR_ZIP_CACH_QLTRANSFEREX	_T("QLtransUpload")
#define STR_UNZIP_CACH_QLTRANSFEREX	_T("QLtransDownload")


#include "CDBPtLogInfo.h"

//#define YARN_IMAGE 0
#define ORDER_IMAGE 0
#define Des_IMAGE 0
#include <map>
#include <string>
#include <vector>
using namespace std;


#define TIME_LIMIT CTime sTime(2018, 8, 01, 22, 15, 0); \
CTime eTime(2022, 8, 01, 22, 15, 0); \
CTime cTime =	CTime::GetCurrentTime( );


#ifdef _UNICODE
#ifdef _DEBUG
#define _FILETRANS_LIBNAME_  _T("QlFileTransferEx_ud.dll")
#else
#define _FILETRANS_LIBNAME_  _T("QlFileTransferEx_u.dll")
#endif // _DEBUG
#else
#ifdef _DEBUG
#define _FILETRANS_LIBNAME_  _T("QlFileTransferEx_d.dll")
#else
#define _FILETRANS_LIBNAME_  _T("QlFileTransferEx.dll")
#endif // _DEBUG
#endif


