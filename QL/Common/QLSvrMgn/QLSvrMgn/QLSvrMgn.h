// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// (��Fluent UI��)����ʾ�������ο���
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������  
// http://msdn.microsoft.com/officeui��
//
// ��Ȩ����(C) Microsoft Corporation
// ��������Ȩ����

// QLSvrMgn.h : QLSvrMgn Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������
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
// �йش����ʵ�֣������ QLSvrMgn.cpp
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
		* @brief���õ���ǰ�ļ���·��
		* @author��zhangyx 2017/12/20
		* @example��
		* @return��
		*************************/
	void GetCurrentFilePath();


	/*******************************************************************
	 * @brief : ��ȡ��Ŀ¼�µ��ļ��б�
	 * @author : zhangt 2017/06/20
	 * @param : pListPath ��ȡ�ļ��б���
	 * @param : strRootPath ��Ŀ¼
	 * @param : nFlag:
				0x0001 ��ǰĿ¼���ļ�
				0x0002 ��ǰĿ¼���ļ���
				0x0004 ������Ŀ¼�ļ�
				0x0008 ������Ŀ¼�ļ���
	 * @example : 
	 * @return : 
	 *******************************************************************/
	BOOL GetFileNameByRoot(__out CStringList *pListPath,__in CString strRootPath,__in DWORD nFlag=0x0001);


	/*******************************************************************
	 * @brief : ��ʾ��ʾ��Ϣ
	 * @author : zhangt 2017/04/19
	 * @param : strTip ��ʾ����
	 * @param : clrTip ��ʾ������ɫ
	 * @param : nDelayTime ��ʾ���Զ��ر�ʱ�䵥λs (0��ʾ���ر�)
	 * @param : pWndParent �����ڣ�NULL��ʾAfxGetMainWnd()��
	 * @param : ptPos ��ʾ��λ�ã�CPoint(-1,-1)��ʾ���½ǣ�
	 * @param : strTitle ��ʾ�����
	 * @param : wParam ��ϢWM_DESKTOP_DBCLICK������˫���Ի��������ϢWM_DESKTOP_DBCLICK��CMainFrame��
	 * @param : lParam ��ϢWM_DESKTOP_DBCLICK������˫���Ի��������ϢWM_DESKTOP_DBCLICK��CMainFrame��
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
	 * @brief : ������չ��ɸѡ��ǰ�ļ��Ƿ����Ҫ��
	 * @author : zhangt 2018/01/15
	 * @param : strFilePath
	 * @param : strNameEx �ļ���չ��
	 * @example : 
	 * @return : 
	 *******************************************************************/
	BOOL FilterPathToFileName(CString &strFilePath,CString strNameEx=_T("bak"));

   /*******************************************************************
	 * @brief : ��ȡ�����ݿ�����״̬
	 * @author : zhangt 2018/04/12
	 * @param : CADOConn *pADOConn
	 * @example : 
	 * @return : 
	 *******************************************************************/
   BOOL GetStateConnectDB(CADOConn *pADOConn);
   BOOL GetStateConnectDB(BOOL bCreateDB=FALSE);

   /******************************************************************
      * @brief : �������̳߳�ʼ��
      * @author : anjie 2018/07/20
      * @param : 
      * @example : 
   * @return : 
   *******************************************************************/
   void InitMontiorThread();

   /*******************************
	*************
		* @brief���������ݿ�
		* @author��anjie 2018/07/21
		* @example��
		* @return��
      * @parameter: btype �������ͣ�TRUE ���屸�� FALSE ���챸��
		  **************************
	********************************/
   BOOL BackupDatabase(CString strDirectory,BOOL btype);

   //�����̴߳���
   static UINT DealMontior(LPVOID pParam);
   static UINT DealWork(LPVOID pParam);
   static UINT DealAutoDelete(LPVOID pParam);
   /******************************************************************
      * @brief : ��־��ӡ����̨����
      * @author : anjie 2018/07/21
      * @param : 
      * @example : 
   * @return : 
   *******************************************************************/
   BOOL ContrlCreate();

   /******************************************************************
      * @brief : bak�ļ����
      * @author : anjie 2018/07/24
      * @param : 
      * @example : 
   * @return : 
   *******************************************************************/
   BOOL FindBackupFile(CString strPath);

   //��ʼ�������ͳɹ������
   void InitTaskInfo();

   //��ʼ������
   void InitTray();
   //���������
     void SaveTaskInfo();

     //ɾ���ļ���
     BOOL RemoveDir(CString strDirName);
// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;
   BOOL OnlyInstance();
   int GetAppPathFromHwnd(HWND hWnd, CString& ExePath); 
	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();
public:
	CString m_strAppPath;
	CDlgLoading m_dlgLoading;	               //���ضԻ���
   CDBTaskInfoList m_TaskList;               //�����б�
   CDBTaskInfoList m_TaskSuccessList;        //��¼�ɹ�����
   int m_nTaskID;                            //����ID
   CWinThread *m_pMonitorThread ;            //�������߳�
   CWinThread *m_pAutoDeleteThread ;         //���������߳�
   BOOL m_bTaskMark;                         //�����־
   BOOL m_MutexMark;                         //�����־//��������ǿ��ɾ��ִ������ʱ���ڴ�ͬʱ��������
   CMutex m_Mutex;                           //�̻߳�����
   BOOL m_bLastTaskMark;                     //�����־
   int m_nTaskSucessfullCount;               //�ɹ��������
   int m_nTaskCount;                         //������ִ���������
   map<int,CString> m_mapTaskSuccessfullID;  //�ɹ����������ֶ�
    map<int,CString> m_mapTaskID;            //���������ֶ�
   CWinThread *m_pWorkThread ;               //�������߳�
   int m_nCrt;                               //����̨��ʶ
   CMyADOConnEx *m_pADOConn;                 
   CDirectory m_CDirectroy;
   CDBDatabaseTableList m_DBDatabaseTableList;  //�洢�������ݿ���Ϣ��
   CString m_strXbackUpFileTime;  //�ϴβ�ֱ����ļ���ʱ��
   CDBTaskInfo DBExTask;
   HANDLE m_hSem;						//��ʵ���ź������
   int m_nWorkType;              //��������

   //���������
   BOOL    m_bAutoStart;         //������
   BOOL    m_bStartHide;         //����������

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()	
};

BOOL WINAPI Routine( DWORD dwCtrlType );
extern CQLSvrMgnApp theApp;
extern CMySerial MySerial;