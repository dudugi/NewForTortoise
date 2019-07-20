
// CustomMgnSys.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif



#include "resource.h"		// ������
#include "ClassEx/CUserMsgDefine.h"
#include "ClassEx/ADOConnEx.h"
#include "DBUserInfo.h"


extern const UINT WORD_PWD_KEY;
extern const UINT CONST_PWD_C1;
extern const UINT CONST_PWD_C2;



#pragma region ��ʾ��������ز���
extern const COLORREF SKIN_COLOR_DEFAULT;
extern const COLORREF TIP_COLOR_WARNING;
extern const COLORREF TIP_COLOR_SUC		 ;
extern const COLORREF TIP_COLOR_NOMAL	 ;
extern const CPoint TIP_POSTION			 ;
extern const int TIP_TIME_DELAY			 ;
#pragma endregion ��ʾ��������ز���


typedef CBCGPWinApp CExAPP;

// CCustomMgnSysApp:
// �йش����ʵ�֣������ CustomMgnSys.cpp
//

class CCustomMgnSysApp : public CExAPP
{
public:
	CCustomMgnSysApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()


public:
   CString m_strAppWholePath;	//��ǰAppȫ·��
   CString m_strAppPath;		//��ǰApp()·��
   CString m_strAppIniFile;	//��ǰApp�����ļ���ini��
   CDBUserInfoData m_objDBPerson;
   //���ݿ����
   CADOConnEx *m_pADOConn; 

   // ���ܹ����
   CLDK				m_LDK;
   CString				m_sLDKErrorInfo1;
   CString				m_sLDKErrorInfo2;
   CString				m_sLDKErrorInfo3;
   //_end
   
private:
   HANDLE m_hSem;						//��ʵ���ź������
  void ReadDBList();
public:

   /**********************************************************************
   *OnEncodeStr���ַ�������
   *������	strData	��Ҫ���ܵ�Դ�ַ��������ģ�
   *			nKey	��Կ
   *����ֵ��	���ܺ���ַ��������ģ�
   **********************************************************************/
   CString OnEncodeStr( CString strData, WORD nKey= WORD_PWD_KEY );

   /**********************************************************************
   *OnDecodeStrr���ַ�������
   *������	strData	��Ҫ���ܵ�Դ�ַ��������ģ�
   *			nKey	��Կ
   *����ֵ��	���ܺ���ַ��������ģ�
   **********************************************************************/
   CString OnDecodeStr( CString strData, WORD nKey = WORD_PWD_KEY );

   void GetIniKeyValue( CString strSection,CString strKeyName,
      CString &strKeyValue,CString strPathFile =_T("") );

   void SetIniKeyValue( CString strSection,CString strKeyName,
      CString strKeyValue,CString strPathFile =_T("") );

   COleDateTime CString2OleDateTime( CString strValue );
   
   BOOL MakeDirByCheck( CString strDir );

   BOOL OnlyInstance();

   BOOL CheckUserLogin();

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


   	/*******************************************************************
	 * @brief : ����MFC�˵���������ϵͳ��
	 * @author : zhangt 2017/07/14
	 * @param : pWndParent ������ʵ��
	 * @param : pPopup
	 * @param : point ������
	 * @return : 
	 *******************************************************************/
	BOOL OnShowCMFCPopupMenu(__in CWnd *pWndParent,__in CMenu* pPopup,
      __in CPoint point);

   void InitPath();


   virtual int ExitInstance();

   //��ȡ���ܹ�ʱ��
   BOOL GetLDKCurTime(unsigned int &year,unsigned int &month,unsigned int &day,unsigned int &hour,unsigned int &min,unsigned int &sec);

   //��ȡ���ܹ�ID
   CString GetLDKID();
};

extern CCustomMgnSysApp theApp;

