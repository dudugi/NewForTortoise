
// CustomMgnSys.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif



#include "resource.h"		// 主符号
#include "ClassEx/CUserMsgDefine.h"
#include "ClassEx/ADOConnEx.h"
#include "DBUserInfo.h"


extern const UINT WORD_PWD_KEY;
extern const UINT CONST_PWD_C1;
extern const UINT CONST_PWD_C2;



#pragma region 提示窗窗口相关参数
extern const COLORREF SKIN_COLOR_DEFAULT;
extern const COLORREF TIP_COLOR_WARNING;
extern const COLORREF TIP_COLOR_SUC		 ;
extern const COLORREF TIP_COLOR_NOMAL	 ;
extern const CPoint TIP_POSTION			 ;
extern const int TIP_TIME_DELAY			 ;
#pragma endregion 提示窗窗口相关参数


typedef CBCGPWinApp CExAPP;

// CCustomMgnSysApp:
// 有关此类的实现，请参阅 CustomMgnSys.cpp
//

class CCustomMgnSysApp : public CExAPP
{
public:
	CCustomMgnSysApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()


public:
   CString m_strAppWholePath;	//当前App全路径
   CString m_strAppPath;		//当前App()路径
   CString m_strAppIniFile;	//当前App配置文件（ini）
   CDBUserInfoData m_objDBPerson;
   //数据库变量
   CADOConnEx *m_pADOConn; 

   // 加密狗相关
   CLDK				m_LDK;
   CString				m_sLDKErrorInfo1;
   CString				m_sLDKErrorInfo2;
   CString				m_sLDKErrorInfo3;
   //_end
   
private:
   HANDLE m_hSem;						//单实例信号量句柄
  void ReadDBList();
public:

   /**********************************************************************
   *OnEncodeStr：字符串加密
   *参数：	strData	需要加密的源字符串（明文）
   *			nKey	秘钥
   *返回值：	加密后的字符串（密文）
   **********************************************************************/
   CString OnEncodeStr( CString strData, WORD nKey= WORD_PWD_KEY );

   /**********************************************************************
   *OnDecodeStrr：字符串解密
   *参数：	strData	需要解密的源字符串（密文）
   *			nKey	秘钥
   *返回值：	解密后的字符串（明文）
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


   	/*******************************************************************
	 * @brief : 弹出MFC菜单（风格跟随系统）
	 * @author : zhangt 2017/07/14
	 * @param : pWndParent 父窗口实例
	 * @param : pPopup
	 * @param : point 弹出点
	 * @return : 
	 *******************************************************************/
	BOOL OnShowCMFCPopupMenu(__in CWnd *pWndParent,__in CMenu* pPopup,
      __in CPoint point);

   void InitPath();


   virtual int ExitInstance();

   //获取加密狗时间
   BOOL GetLDKCurTime(unsigned int &year,unsigned int &month,unsigned int &day,unsigned int &hour,unsigned int &min,unsigned int &sec);

   //获取加密狗ID
   CString GetLDKID();
};

extern CCustomMgnSysApp theApp;

