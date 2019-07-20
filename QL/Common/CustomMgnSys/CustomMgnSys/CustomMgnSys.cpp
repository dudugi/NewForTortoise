
// CustomMgnSys.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "CustomMgnSys.h"
#include "CustomMgnSysDlg.h"
#include "Base64Code.h"
#include "QLLogin\DlgLogin.h"
#include "rnfile.h"
#include "CMFCDesktopAlert\CMFCDesktopAlertMid.h"
#include "DlgDesktop.h"
#include "WorkLog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif




/******************字符串加密 秘钥常量*************************/
const UINT WORD_PWD_KEY	=		52369;
const UINT CONST_PWD_C1	=		52845;
const UINT CONST_PWD_C2	=		22719;
//秘钥常量 end wzl

//--------------------------------------------------------------------
#pragma region 提示窗窗口相关参数
const COLORREF SKIN_COLOR_DEFAULT =	RGB(223,237,255);
const COLORREF TIP_COLOR_WARNING	 =	RGB(255,0,0);
const COLORREF TIP_COLOR_SUC		 =	RGB(0,0,255);
const COLORREF TIP_COLOR_NOMAL	 =	RGB(0,0,0);
const CPoint TIP_POSTION			 =	CPoint(-1,-1);
const int TIP_TIME_DELAY			 = 2;
#pragma endregion 提示窗窗口相关参数
//--------------------------------------------------------------------

CMySerial MySerial;


// CCustomMgnSysApp

BEGIN_MESSAGE_MAP(CCustomMgnSysApp, CExAPP)
	ON_COMMAND(ID_HELP, &CExAPP::OnHelp)
END_MESSAGE_MAP()


// CCustomMgnSysApp 构造

CCustomMgnSysApp::CCustomMgnSysApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
   m_pADOConn = nullptr;
}


// 唯一的一个 CCustomMgnSysApp 对象

CCustomMgnSysApp theApp;


// CCustomMgnSysApp 初始化

BOOL CCustomMgnSysApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CExAPP::InitInstance();

   

	AfxEnableControlContainer();
   AfxInitRichEdit2();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

   SetVisualTheme(BCGP_VISUAL_THEME_VS_2010);

   m_LDK.GetHaspKey(HASP_PLMVERSION);

   m_LDK.GetHaspKey(HASP_SHELL);
    CString keyInfo =  m_LDK.GetKeyInfo();
/*
获取加密狗信息
 CString keyInfo =  m_LDK.GetKeyInfo();
  


   //test encrypt
   //最小长度不小于16，小于16，补
  char cContent[] = "12345678";
  char* inBuffer;
  int nLen = sizeof(cContent);
  if( nLen < 16 )
  {
	  nLen = 16;
  }
  inBuffer = new char[nLen];
  memset(inBuffer,0,nLen);
  memcpy(inBuffer,cContent,sizeof(cContent));
   
  BOOL bRet = FALSE;
  //加密
   bRet = m_LDK.EncryptString( inBuffer , nLen );
   if(bRet )
   {

   }else
   {
	   //报错：请插入加密锁（对客户端来说也是这样
   }
   
  //解密
   bRet = m_LDK.DecryptString( inBuffer , nLen );
   if(bRet )
   {

   }else
   {
	   //报错：请插入加密锁（对客户端来说也是这样
   }

   delete []inBuffer;
//获取加密狗时间
   unsigned int year,month,day,hour,min,sec;
   bRet = m_LDK.GetHaspTime(year,month,day,hour,min,sec);
   if(bRet )
   {

   }else
   {
	   //报错：请插入加密锁（对客户端来说也是这样
   }

   */
   InitPath();
 
   if (!OnlyInstance())//只允许只有一个订单管理实例在运行
   {
      return FALSE;
   }
   
   if (!CheckUserLogin())
   {
      return FALSE;
   }

   //读取数据库数据到缓存 
   m_pADOConn = new CADOConnEx(); //new 数据库连接
   //登录日志
   CString strSysTitle = _T("登入管理中心");
   WorkLog::InsertOneWorkLog(enLog_Cate_TableName_Null,enLog_Type_Login,
      m_objDBPerson.m_strUserID,strSysTitle,_T("登入"));

   //CString strSQL;
   //strSQL = CADOConnEx::CreateConncetSqlStrByEncodeParam()
   //m_pADOConn->SetConnectSqlStr(strSQL);

   ReadDBList();  

	CCustomMgnSysDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}

void CCustomMgnSysApp::InitPath()
{
  TCHAR szPath[MAX_PATH];

  GetModuleFileName(NULL, szPath, MAX_PATH);  //获取到完整路径 eg：E:\Tools\qq.exe

  m_strAppWholePath = szPath;
  
  m_strAppPath = RnFile::GetModulePathFile(_T(""));
  m_strAppIniFile = RnFile::GetModulePathFile(_T("cfgini"));
}

BOOL CCustomMgnSysApp::OnlyInstance()
{
   BOOL bRet = TRUE;

   //m_hSem = CreateSemaphore(NULL, 1, 1, m_pszAppName);
   //CString strPrePath = _T("");

   //// 信号量存在，则程序已有一个实例运行
   //if (GetLastError() == ERROR_ALREADY_EXISTS)
   //{
   //   // 寻找先前实例的窗口
   //   HWND hWndPrevious = ::GetWindow(::GetDesktopWindow(), GW_CHILD);
   //   while (::IsWindow(hWndPrevious))
   //   {
   //      // 检查窗口是否有预设的标记
   //      if (::GetProp(hWndPrevious, m_pszAppName))
   //      {
   //         GetAppPathFromHwnd(hWndPrevious,strPrePath);
   //         if (strPrePath == m_strAppWholePath)//路径完全一样的App
   //         {
   //            bRet = FALSE;

   //            //主窗口已最小化或最大化显示，则最大化显示
   //            if (IsIconic(hWndPrevious)||IsZoomed(hWndPrevious))
   //            {
   //               //ShowWindow(hWndPrevious, SW_RESTORE);//恢复其大小
   //               ShowWindow(hWndPrevious, SW_MAXIMIZE);
   //            }
   //            else
   //            {
   //               ShowWindow(hWndPrevious, SW_NORMAL);
   //            }

   //            //将主窗激活
   //            //SetForegroundWindow(hWndPrevious);
   //            BringWindowToTop(hWndPrevious);
   //            //将主窗的对话框激活
   //            //SetForegroundWindow(GetLastActivePopup(hWndPrevious));		
   //            SetWindowPos(hWndPrevious,HWND_TOPMOST,0,0,0,0, SWP_NOMOVE|SWP_NOSIZE);
   //            SetWindowPos(hWndPrevious,HWND_NOTOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);

   //            //::SendMessage(hWndPrevious,WM_KDSFILEMGN_WORKTYPE,(WPARAM )m_nWorkType,(LPARAM)0);

   //            //退出本实例
   //            break;
   //         }			
   //      }
   //      // 继续寻找下一个窗口
   //      hWndPrevious = ::GetWindow(hWndPrevious, GW_HWNDNEXT);
   //   }		
   //}

   return bRet;
}

/**********************************************************************
*OnEncodeStr：字符串加密
*参数：	strData	需要加密的源字符串（明文）
*			nKey	秘钥
*返回值：	加密后的字符串（密文）
**********************************************************************/
CString CCustomMgnSysApp::OnEncodeStr( CString strData, WORD nKey/* = WORD_PWD_KEY*/ )
{
	strData.Trim();
	CString strRet = _T("");
	if(strData.IsEmpty())
	{
		return strRet;
	}
	else
	{
		CBase64Code Base64Code;
		strRet = Base64Code.base64Encode(strData);
	}


/*	strData.Trim();
	CString strRet,strTmp;
	int i,j;
	strRet = strData; // 初始化结果字符串
	if(strData.IsEmpty())
	{
		return strRet;
	}

	///////////////////
	for(i=0; i<strData.GetLength(); i++) // 依次对字符串中各字符进行操作
	{
		strRet.SetAt(i, strData.GetAt(i)^(nKey>>8)); // 将密钥移位后与字符异或
		nKey = ((BYTE)strRet.GetAt(i)+nKey)*CONST_PWD_C1+CONST_PWD_C2; // 产生下一个密钥
	}
	strData = strRet; // 保存结果
	strRet.Empty(); // 清除结果
	for(i=0; i<strData.GetLength(); i++) // 对加密结果进行转换
	{
		j=(BYTE)strData.GetAt(i); // 提取字符
		// 将字符转换为两个字母保存
		strTmp = _T("12"); // 设置strTmp长度为2
		strTmp.SetAt(0, 65+j/26);
		strTmp.SetAt(1, 65+j%26);
		strRet += strTmp;
	}*/

	return strRet;
}

/**********************************************************************
*OnDecodeStrr：字符串解密
*参数：	strData	需要解密的源字符串（密文）
*			nKey	秘钥
*返回值：	解密后的字符串（明文）
**********************************************************************/
CString CCustomMgnSysApp::OnDecodeStr( CString strData, WORD nKey/* = WORD_PWD_KEY*/ )
{
	strData.Trim();
	CString strRet = _T("");
	if(strData.IsEmpty())
	{
		return strRet;
	}
	else
	{
		CBase64Code Base64Code;
		strRet = Base64Code.base64Decode(strData);
	}
	/*CString strRet=_T(""),strTmp;
	int i,j;
	strRet.Empty(); // 清楚结果
	if (strData.IsEmpty())
	{
		return strRet;
	}

	/////////////////////////////
	for(i=0; i < strData.GetLength()/2; i++) // 将字符串两个字母一组进行处理
	{
		j = ((BYTE)strData.GetAt(2*i)-65)*26;
		j += (BYTE)strData.GetAt(2*i+1)-65;
		strTmp = _T("1"); // 设置strTmp长度为1
		strTmp.SetAt(0, j);
		strRet += strTmp; // 追加字符，还原字符串
	}
	strData = strRet; // 保存中间结果
	for(i=0; i<strData.GetLength(); i++) // 依次对字符串中各字符进行操作
	{
		strRet.SetAt(i, (BYTE)strData.GetAt(i)^(nKey>>8)); // 将密钥移位后与字符异或
		nKey = ((BYTE)strData.GetAt(i)+nKey)*CONST_PWD_C1+CONST_PWD_C2; // 产生下一个密钥
	}*/

	return strRet;
}

void CCustomMgnSysApp::GetIniKeyValue( CString strSection,CString strKeyName,
   CString &strKeyValue,CString strPathFile/*=_T("")*/ )
{
	strPathFile.Trim();
	if (strPathFile.IsEmpty())
	{
		strPathFile = m_strAppIniFile;
	}

	TCHAR temp[MAX_PATH];
	GetPrivateProfileString(strSection,strKeyName,_T(""),temp,MAX_PATH,strPathFile);
	strKeyValue.Format(_T("%s"),temp);
	strKeyValue.Trim();
}

void CCustomMgnSysApp::SetIniKeyValue( CString strSection,CString strKeyName,
   CString strKeyValue,CString strPathFile/*=_T("")*/ )
{
	strPathFile.Trim();
	if (strPathFile.IsEmpty())
	{
		strPathFile = m_strAppIniFile;
	}

	strKeyValue.Trim();
	WritePrivateProfileString(strSection,strKeyName,strKeyValue,strPathFile);
}

COleDateTime CCustomMgnSysApp::CString2OleDateTime( CString strValue )
{
	if (strValue.IsEmpty())
	{
		return COleDateTime::GetCurrentTime();
	}

	CString strYear,strMonth,strDay,strHour,strMin,strSec;
	strYear = strValue.Mid(0,4);	//截取 年
	strMonth = strValue.Mid(5,2);	//截取 月
	strDay = strValue.Mid(8,2);		//截取 日
	if(strValue.GetLength()>10)
	{
		strHour = strValue.Mid(11,2);	//截取 时
		strMin = strValue.Mid(14,2);	//截取 分
		strSec = strValue.Mid(17,2);	//截取 秒
	}
	else
	{
		strHour = _T("0");
		strMin = _T("0");
		strSec = _T("0");
	}

	COleDateTime TValue(_ttoi(strYear),_ttoi(strMonth),_ttoi(strDay),
      _ttoi(strHour),_ttoi(strMin),_ttoi(strSec));

	return TValue;
}

BOOL CCustomMgnSysApp::MakeDirByCheck( CString strDir )
{
	BOOL bRet = TRUE;
   
	strDir.Trim();
	if (strDir.IsEmpty())
	{
		bRet = FALSE;
	}
	else
	{
		int nRet = SHCreateDirectoryEx(NULL,strDir,NULL);
		switch(nRet)
		{
		default:
		case ERROR_SUCCESS://创建成功
			bRet = TRUE;
			break;
		case ERROR_BAD_PATHNAME://pszPath 参数为相对路径
			bRet = FALSE;
			break;
		case ERROR_FILENAME_EXCED_RANGE://pszPath 参数太长
			bRet = FALSE;
			break;
		case ERROR_PATH_NOT_FOUND://创建时系统找不到指定路径，可能路径中包含非法入口。(如Z:\,但不存在Z盘。)
			bRet = FALSE;
			break;
		case ERROR_FILE_EXISTS://文件已经存在
			bRet = TRUE;
			break;
		case ERROR_ALREADY_EXISTS://路径已经存在
			bRet = TRUE;
			break;
		case ERROR_CANCELLED://用户取消了操作
			bRet = FALSE;
			break;	
		}
	}

	return bRet;
}

BOOL CCustomMgnSysApp::CheckUserLogin()
{
	BOOL bRet = TRUE;

   CDlgLogin Logindlg;
   UINT uRet = Logindlg.DoModal();
   if (IDOK!=uRet)
   {
      return FALSE;
   }

   CDlgLogin::En_LoginReturn_Type enType = Logindlg.GetLoginState();//.ShowDlg(m_strKdsWorkPath);

	if (enType == CDlgLogin::RETURN_SUCCESS)
	{
      bRet = TRUE;
   }

	return bRet;
}



//		by WangZY 2018/08/21
void CCustomMgnSysApp::OnShowDesktopAlert(
   __in CString strTip, 
   __in COLORREF clrTip/*=RGB(255,0,0)*/, 
   __in int nDelayTime/*=1 */,
   __in CWnd *pWndParent/*=NULL*/, 
   __in CPoint ptPos/*=(0,0)*/,
   __in CString strTitle/*=_T("")*/,
   __in WPARAM wParam/*=0*/, 
   __in LPARAM lParam/*=0 */)
{
   if (pWndParent == NULL) pWndParent = AfxGetMainWnd();
   BOOL bCusTile = FALSE;
   if (strTitle.IsEmpty())
   {
      bCusTile = FALSE;
      strTitle =  _T("温馨提示：");
   }
   else
   {
      bCusTile = TRUE;
   }

   CMFCDesktopAlertMid* pPopup = new CMFCDesktopAlertMid;
   pPopup->SetAnimationType (CBCGPPopupMenu::SYSTEM_DEFAULT_ANIMATION);
   pPopup->SetAnimationSpeed (10);
   pPopup->SetTransparency (230);//0-255
   pPopup->SetSmallCaption (!bCusTile);
   pPopup->SetAutoCloseTime(nDelayTime * 1000);//1000ms

   HICON hIcon = (HICON) ::LoadImage (::AfxGetResourceHandle (), 
      MAKEINTRESOURCE (IDR_MAINFRAME),
      IMAGE_ICON, ::GetSystemMetrics (SM_CXSMICON), ::GetSystemMetrics (SM_CYSMICON), 0);

   CPoint ptShowPos = ptPos;
   if (ptPos == CPoint(0,0))
   {
      CRect rc;
      AfxGetMainWnd()->GetClientRect(&rc);
      AfxGetMainWnd()->ClientToScreen(&rc);
      ptShowPos.x = rc.right/2-50;
      ptShowPos.y = rc.top;
   }

   pPopup->Create(pWndParent, CDlgDesktop::IDD, NULL, 
      ptShowPos, RUNTIME_CLASS(CDlgDesktop));
   if(::IsWindow(pPopup->GetSafeHwnd()))
   {
      CDlgDesktop *pDlgDesktop = (CDlgDesktop *)pPopup->GetRuntimeDlg();
      if (pDlgDesktop)
      {
         pDlgDesktop->m_strText = strTip;
         pDlgDesktop->m_clrText = clrTip;
         pDlgDesktop->wParam = wParam;
         pDlgDesktop->lParam = lParam;
         pDlgDesktop->pOwerWnd = AfxGetMainWnd();
      }

      pPopup->SetIcon(hIcon, FALSE);
      pPopup->SetWindowText(strTitle);
   }
}

//		by WangZY 2018/08/21
BOOL CCustomMgnSysApp::OnShowCMFCPopupMenu(__in CWnd *pWndParent,
   __in CMenu* pPopup, __in CPoint point)
{
   BOOL bRet = FALSE;

   if (pPopup)
   {
      //bRet = TRUE;
      //GetContextMenuManager()->ShowPopupMenu(pPopup->GetSafeHmenu(),point.x, point.y, pWndParent, TRUE,TRUE);
      CBCGPPopupMenu* pPopupMenu = new CBCGPPopupMenu;
      pPopupMenu->SetAutoDestroy(TRUE); 
      pPopupMenu->SetAnimationSpeed(100);
      pPopupMenu->SetAnimationType(CBCGPPopupMenu::NO_ANIMATION);
      pPopupMenu->SetForceShadow(TRUE);
      pPopupMenu->m_bAutoMenuEnable = FALSE; //2017/11/16 zhangt FALSE使EnableMenuItem()有效
      if (pPopupMenu)
      {
         bRet = TRUE;
         pPopupMenu->Create(pWndParent, point.x, point.y, pPopup->Detach(),TRUE,TRUE);

         //计算弹出点
         CRect rc,rcDesk;
         pPopupMenu->GetWindowRect(&rc);
         //int nScreenHeight = GetSystemMetrics(SM_CYFULLSCREEN);
         SystemParametersInfo(SPI_GETWORKAREA,0,&rcDesk,0);
         int nScreenHeight = rcDesk.Height();
         int nAbs = nScreenHeight-point.y;
         if (point.y<rc.Height() && rc.Height()>nAbs)
         {
            point.y = nScreenHeight-rc.Height();
            pPopupMenu->MoveTo(point);
         }		
         pPopupMenu->SetForegroundWindow();
      }
   }
   else
   {
      bRet = FALSE;
   }

   return bRet;
}

int CCustomMgnSysApp::ExitInstance()
{
   // TODO: Add your specialized code here and/or call the base class
   CloseHandle(m_hSem);
   if (NULL != m_pADOConn)
   {
      delete m_pADOConn;
      m_pADOConn = NULL;
   }
   return CExAPP::ExitInstance();
}

void CCustomMgnSysApp::ReadDBList()
{

}

//获取加密狗时间
BOOL CCustomMgnSysApp::GetLDKCurTime(unsigned int &year,unsigned int &month,unsigned int &day,unsigned int &hour,unsigned int &min,unsigned int &sec)
{
   return m_LDK.GetHaspTime(year,month,day,hour,min,sec);
}
//获取加密狗ID
CString CCustomMgnSysApp::GetLDKID()
{
    CString keyInfo =  m_LDK.GetKeyInfo();
    return keyInfo;
}

