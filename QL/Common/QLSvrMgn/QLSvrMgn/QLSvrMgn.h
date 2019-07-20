// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// (“Fluent UI”)。该示例仅供参考，
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问  
// http://msdn.microsoft.com/officeui。
//
// 版权所有(C) Microsoft Corporation
// 保留所有权利。

// QLSvrMgn.h : QLSvrMgn 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号
//#include "MySerial.h"
#include "MySerial.h"
#include "DlgLoading.h"
#include "DBTaskInfo.h"
#include <queue>
#include "MyADOConnEx.h"
#include "Macrodefine.h"
#include "Directory.h"
#include "DBDatabaseFields.h"
#include <map>
// CQLSvrMgnApp:
// 有关此类的实现，请参阅 QLSvrMgn.cpp
//
class CADOConn;

class CQLSvrMgnApp : public CWinAppEx
{
public:
	CQLSvrMgnApp();
	void OnReadIni(CString strSection,CString strKey,CString &strKeyValue,int nType);
	void OnWriteIni(CString strSection,CString strKey,CString strKeyValue,int nType);
	void ShowLoading();
	void CloseLoading();
	/***********************************
		* @brief：得到当前文件的路径
		* @author：zhangyx 2017/12/20
		* @example：
		* @return：
		*************************/
	void GetCurrentFilePath();


	/*******************************************************************
	 * @brief : 获取根目录下的文件列表
	 * @author : zhangt 2017/06/20
	 * @param : pListPath 获取文件列表链
	 * @param : strRootPath 根目录
	 * @param : nFlag:
				0x0001 当前目录下文件
				0x0002 当前目录下文件夹
				0x0004 包括子目录文件
				0x0008 包括子目录文件夹
	 * @example : 
	 * @return : 
	 *******************************************************************/
	BOOL GetFileNameByRoot(__out CStringList *pListPath,__in CString strRootPath,__in DWORD nFlag=0x0001);


	/*******************************************************************
	 * @brief : 显示提示信息
	 * @author : zhangt 2017/04/19
	 * @param : strTip 提示内容
	 * @param : clrTip 提示内容颜色
	 * @param : nDelayTime 显示后自动关闭时间单位s (0表示不关闭)
	 * @param : pWndParent 父窗口（NULL表示AfxGetMainWnd()）
	 * @param : ptPos 显示的位置（CPoint(-1,-1)表示右下角）
	 * @param : strTitle 提示框标题
	 * @param : wParam 消息WM_DESKTOP_DBCLICK参数（双击对话框产生消息WM_DESKTOP_DBCLICK给CMainFrame）
	 * @param : lParam 消息WM_DESKTOP_DBCLICK参数（双击对话框产生消息WM_DESKTOP_DBCLICK给CMainFrame）
	 * @example : 
	 * @return : 
	 *******************************************************************/
	void OnShowDesktopAlert(
		__in CString strTip,
		__in COLORREF clrTip=RGB(255,0,0),
		__in int nDelayTime=1
		,__in CWnd *pWndParent=NULL,
		__in CPoint ptPos=(0,0),
		__in CString strTitle=_T(""),
		__in WPARAM wParam=0,
		__in LPARAM lParam=0
		);


	BOOL MakeDirByCheck(CString strDir);

	/*******************************************************************
	 * @brief : 根据扩展名筛选当前文件是否符合要求
	 * @author : zhangt 2018/01/15
	 * @param : strFilePath
	 * @param : strNameEx 文件扩展名
	 * @example : 
	 * @return : 
	 *******************************************************************/
	BOOL FilterPathToFileName(CString &strFilePath,CString strNameEx=_T("bak"));

   /*******************************************************************
	 * @brief : 获取与数据库连接状态
	 * @author : zhangt 2018/04/12
	 * @param : CADOConn *pADOConn
	 * @example : 
	 * @return : 
	 *******************************************************************/
   BOOL GetStateConnectDB(CADOConn *pADOConn);
   BOOL GetStateConnectDB(BOOL bCreateDB=FALSE);

   /******************************************************************
      * @brief : 任务监控线程初始化
      * @author : anjie 2018/07/20
      * @param : 
      * @example : 
   * @return : 
   *******************************************************************/
   void InitMontiorThread();

   /*******************************
	*************
		* @brief：备份数据库
		* @author：anjie 2018/07/21
		* @example：
		* @return：
      * @parameter: btype 备份类型：TRUE 整体备份 FALSE 差异备份
		  **************************
	********************************/
   BOOL BackupDatabase(CString strDirectory,BOOL btype);

   //任务线程处理
   static UINT DealMontior(LPVOID pParam);
   static UINT DealWork(LPVOID pParam);
   static UINT DealAutoDelete(LPVOID pParam);
   /******************************************************************
      * @brief : 日志打印控制台启动
      * @author : anjie 2018/07/21
      * @param : 
      * @example : 
   * @return : 
   *******************************************************************/
   BOOL ContrlCreate();

   /******************************************************************
      * @brief : bak文件检测
      * @author : anjie 2018/07/24
      * @param : 
      * @example : 
   * @return : 
   *******************************************************************/
   BOOL FindBackupFile(CString strPath);

   //初始化任务表和成功任务表
   void InitTaskInfo();

   //初始化托盘
   void InitTray();
   //保存任务表
     void SaveTaskInfo();

     //删除文件夹
     BOOL RemoveDir(CString strDirName);
// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;
   BOOL OnlyInstance();
   int GetAppPathFromHwnd(HWND hWnd, CString& ExePath); 
	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();
public:
	CString m_strAppPath;
	CDlgLoading m_dlgLoading;	               //加载对话框
   CDBTaskInfoList m_TaskList;               //任务列表
   CDBTaskInfoList m_TaskSuccessList;        //记录成功任务
   int m_nTaskID;                            //任务ID
   CWinThread *m_pMonitorThread ;            //任务监控线程
   CWinThread *m_pAutoDeleteThread ;         //任务清理线程
   BOOL m_bTaskMark;                         //任务标志
   BOOL m_MutexMark;                         //互斥标志//解决任务表强制删除执行任务时，内存同时访问问题
   CMutex m_Mutex;                           //线程互斥锁
   BOOL m_bLastTaskMark;                     //任务标志
   int m_nTaskSucessfullCount;               //成功任务计数
   int m_nTaskCount;                         //任务表待执行任务计数
   map<int,CString> m_mapTaskSuccessfullID;  //成功任务配置字段
    map<int,CString> m_mapTaskID;            //任务配置字段
   CWinThread *m_pWorkThread ;               //任务工作线程
   int m_nCrt;                               //控制台标识
   CMyADOConnEx *m_pADOConn;                 
   CDirectory m_CDirectroy;
   CDBDatabaseTableList m_DBDatabaseTableList;  //存储本地数据库信息链
   CString m_strXbackUpFileTime;  //上次差分备份文件的时间
   CDBTaskInfo DBExTask;
   HANDLE m_hSem;						//单实例信号量句柄
   int m_nWorkType;              //工作类型

   //自启动相关
   BOOL    m_bAutoStart;         //自启动
   BOOL    m_bStartHide;         //自启动隐藏

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()	
};

BOOL WINAPI Routine( DWORD dwCtrlType );
extern CQLSvrMgnApp theApp;
extern CMySerial MySerial;