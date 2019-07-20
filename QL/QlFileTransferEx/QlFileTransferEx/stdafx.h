// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE ��
#include <afxodlgs.h>       // MFC OLE �Ի�����
#include <afxdisp.h>        // MFC �Զ�����
#endif // _AFX_NO_OLE_SUPPORT

#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>                      // MFC ODBC ���ݿ���
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>                     // MFC DAO ���ݿ���
#endif // _AFX_NO_DAO_SUPPORT

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#pragma warning(disable:4244)
#pragma warning(disable:4995)
#pragma warning(disable:4996)
#pragma warning(disable:4099)//pdbδ�ҵ�����


#include "SpecItem.h"
#include <afxcontrolbars.h>

//����ж�����״̬������Ҫ����ͷ�ļ�
#include <Sensapi.h>
#pragma comment(lib, "Sensapi.lib")

//����GDI+
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

//���ݿ����ֶ�

#define DBWorkLog_key_Cate		_T("cCate")				//���
#define DBWorkLog_key_Code		_T("cCode")				//����
#define DBWorkLog_key_Date		_T("dDate")				//����
#define DBWorkLog_key_Maker		_T("cMaker")			//������
#define DBWorkLog_key_Type		_T("cType")				//����
#define DBWorkLog_key_Detail	_T("cMemo")				//������Ϊ



/******************�ַ������� ��Կ����*************************/
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


