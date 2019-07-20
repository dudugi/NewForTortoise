
// CustomMgnSys.cpp : ����Ӧ�ó��������Ϊ��
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




/******************�ַ������� ��Կ����*************************/
const UINT WORD_PWD_KEY	=		52369;
const UINT CONST_PWD_C1	=		52845;
const UINT CONST_PWD_C2	=		22719;
//��Կ���� end wzl

//--------------------------------------------------------------------
#pragma region ��ʾ��������ز���
const COLORREF SKIN_COLOR_DEFAULT =	RGB(223,237,255);
const COLORREF TIP_COLOR_WARNING	 =	RGB(255,0,0);
const COLORREF TIP_COLOR_SUC		 =	RGB(0,0,255);
const COLORREF TIP_COLOR_NOMAL	 =	RGB(0,0,0);
const CPoint TIP_POSTION			 =	CPoint(-1,-1);
const int TIP_TIME_DELAY			 = 2;
#pragma endregion ��ʾ��������ز���
//--------------------------------------------------------------------

CMySerial MySerial;


// CCustomMgnSysApp

BEGIN_MESSAGE_MAP(CCustomMgnSysApp, CExAPP)
	ON_COMMAND(ID_HELP, &CExAPP::OnHelp)
END_MESSAGE_MAP()


// CCustomMgnSysApp ����

CCustomMgnSysApp::CCustomMgnSysApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
   m_pADOConn = nullptr;
}


// Ψһ��һ�� CCustomMgnSysApp ����

CCustomMgnSysApp theApp;


// CCustomMgnSysApp ��ʼ��

BOOL CCustomMgnSysApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CExAPP::InitInstance();

   

	AfxEnableControlContainer();
   AfxInitRichEdit2();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

   SetVisualTheme(BCGP_VISUAL_THEME_VS_2010);

   m_LDK.GetHaspKey(HASP_PLMVERSION);

   m_LDK.GetHaspKey(HASP_SHELL);
    CString keyInfo =  m_LDK.GetKeyInfo();
/*
��ȡ���ܹ���Ϣ
 CString keyInfo =  m_LDK.GetKeyInfo();
  


   //test encrypt
   //��С���Ȳ�С��16��С��16����
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
  //����
   bRet = m_LDK.EncryptString( inBuffer , nLen );
   if(bRet )
   {

   }else
   {
	   //�����������������Կͻ�����˵Ҳ������
   }
   
  //����
   bRet = m_LDK.DecryptString( inBuffer , nLen );
   if(bRet )
   {

   }else
   {
	   //�����������������Կͻ�����˵Ҳ������
   }

   delete []inBuffer;
//��ȡ���ܹ�ʱ��
   unsigned int year,month,day,hour,min,sec;
   bRet = m_LDK.GetHaspTime(year,month,day,hour,min,sec);
   if(bRet )
   {

   }else
   {
	   //�����������������Կͻ�����˵Ҳ������
   }

   */
   InitPath();
 
   if (!OnlyInstance())//ֻ����ֻ��һ����������ʵ��������
   {
      return FALSE;
   }
   
   if (!CheckUserLogin())
   {
      return FALSE;
   }

   //��ȡ���ݿ����ݵ����� 
   m_pADOConn = new CADOConnEx(); //new ���ݿ�����
   //��¼��־
   CString strSysTitle = _T("�����������");
   WorkLog::InsertOneWorkLog(enLog_Cate_TableName_Null,enLog_Type_Login,
      m_objDBPerson.m_strUserID,strSysTitle,_T("����"));

   //CString strSQL;
   //strSQL = CADOConnEx::CreateConncetSqlStrByEncodeParam()
   //m_pADOConn->SetConnectSqlStr(strSQL);

   ReadDBList();  

	CCustomMgnSysDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

void CCustomMgnSysApp::InitPath()
{
  TCHAR szPath[MAX_PATH];

  GetModuleFileName(NULL, szPath, MAX_PATH);  //��ȡ������·�� eg��E:\Tools\qq.exe

  m_strAppWholePath = szPath;
  
  m_strAppPath = RnFile::GetModulePathFile(_T(""));
  m_strAppIniFile = RnFile::GetModulePathFile(_T("cfgini"));
}

BOOL CCustomMgnSysApp::OnlyInstance()
{
   BOOL bRet = TRUE;

   //m_hSem = CreateSemaphore(NULL, 1, 1, m_pszAppName);
   //CString strPrePath = _T("");

   //// �ź������ڣ����������һ��ʵ������
   //if (GetLastError() == ERROR_ALREADY_EXISTS)
   //{
   //   // Ѱ����ǰʵ���Ĵ���
   //   HWND hWndPrevious = ::GetWindow(::GetDesktopWindow(), GW_CHILD);
   //   while (::IsWindow(hWndPrevious))
   //   {
   //      // ��鴰���Ƿ���Ԥ��ı��
   //      if (::GetProp(hWndPrevious, m_pszAppName))
   //      {
   //         GetAppPathFromHwnd(hWndPrevious,strPrePath);
   //         if (strPrePath == m_strAppWholePath)//·����ȫһ����App
   //         {
   //            bRet = FALSE;

   //            //����������С���������ʾ���������ʾ
   //            if (IsIconic(hWndPrevious)||IsZoomed(hWndPrevious))
   //            {
   //               //ShowWindow(hWndPrevious, SW_RESTORE);//�ָ����С
   //               ShowWindow(hWndPrevious, SW_MAXIMIZE);
   //            }
   //            else
   //            {
   //               ShowWindow(hWndPrevious, SW_NORMAL);
   //            }

   //            //����������
   //            //SetForegroundWindow(hWndPrevious);
   //            BringWindowToTop(hWndPrevious);
   //            //�������ĶԻ��򼤻�
   //            //SetForegroundWindow(GetLastActivePopup(hWndPrevious));		
   //            SetWindowPos(hWndPrevious,HWND_TOPMOST,0,0,0,0, SWP_NOMOVE|SWP_NOSIZE);
   //            SetWindowPos(hWndPrevious,HWND_NOTOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);

   //            //::SendMessage(hWndPrevious,WM_KDSFILEMGN_WORKTYPE,(WPARAM )m_nWorkType,(LPARAM)0);

   //            //�˳���ʵ��
   //            break;
   //         }			
   //      }
   //      // ����Ѱ����һ������
   //      hWndPrevious = ::GetWindow(hWndPrevious, GW_HWNDNEXT);
   //   }		
   //}

   return bRet;
}

/**********************************************************************
*OnEncodeStr���ַ�������
*������	strData	��Ҫ���ܵ�Դ�ַ��������ģ�
*			nKey	��Կ
*����ֵ��	���ܺ���ַ��������ģ�
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
	strRet = strData; // ��ʼ������ַ���
	if(strData.IsEmpty())
	{
		return strRet;
	}

	///////////////////
	for(i=0; i<strData.GetLength(); i++) // ���ζ��ַ����и��ַ����в���
	{
		strRet.SetAt(i, strData.GetAt(i)^(nKey>>8)); // ����Կ��λ�����ַ����
		nKey = ((BYTE)strRet.GetAt(i)+nKey)*CONST_PWD_C1+CONST_PWD_C2; // ������һ����Կ
	}
	strData = strRet; // ������
	strRet.Empty(); // ������
	for(i=0; i<strData.GetLength(); i++) // �Լ��ܽ������ת��
	{
		j=(BYTE)strData.GetAt(i); // ��ȡ�ַ�
		// ���ַ�ת��Ϊ������ĸ����
		strTmp = _T("12"); // ����strTmp����Ϊ2
		strTmp.SetAt(0, 65+j/26);
		strTmp.SetAt(1, 65+j%26);
		strRet += strTmp;
	}*/

	return strRet;
}

/**********************************************************************
*OnDecodeStrr���ַ�������
*������	strData	��Ҫ���ܵ�Դ�ַ��������ģ�
*			nKey	��Կ
*����ֵ��	���ܺ���ַ��������ģ�
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
	strRet.Empty(); // ������
	if (strData.IsEmpty())
	{
		return strRet;
	}

	/////////////////////////////
	for(i=0; i < strData.GetLength()/2; i++) // ���ַ���������ĸһ����д���
	{
		j = ((BYTE)strData.GetAt(2*i)-65)*26;
		j += (BYTE)strData.GetAt(2*i+1)-65;
		strTmp = _T("1"); // ����strTmp����Ϊ1
		strTmp.SetAt(0, j);
		strRet += strTmp; // ׷���ַ�����ԭ�ַ���
	}
	strData = strRet; // �����м���
	for(i=0; i<strData.GetLength(); i++) // ���ζ��ַ����и��ַ����в���
	{
		strRet.SetAt(i, (BYTE)strData.GetAt(i)^(nKey>>8)); // ����Կ��λ�����ַ����
		nKey = ((BYTE)strData.GetAt(i)+nKey)*CONST_PWD_C1+CONST_PWD_C2; // ������һ����Կ
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
	strYear = strValue.Mid(0,4);	//��ȡ ��
	strMonth = strValue.Mid(5,2);	//��ȡ ��
	strDay = strValue.Mid(8,2);		//��ȡ ��
	if(strValue.GetLength()>10)
	{
		strHour = strValue.Mid(11,2);	//��ȡ ʱ
		strMin = strValue.Mid(14,2);	//��ȡ ��
		strSec = strValue.Mid(17,2);	//��ȡ ��
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
		case ERROR_SUCCESS://�����ɹ�
			bRet = TRUE;
			break;
		case ERROR_BAD_PATHNAME://pszPath ����Ϊ���·��
			bRet = FALSE;
			break;
		case ERROR_FILENAME_EXCED_RANGE://pszPath ����̫��
			bRet = FALSE;
			break;
		case ERROR_PATH_NOT_FOUND://����ʱϵͳ�Ҳ���ָ��·��������·���а����Ƿ���ڡ�(��Z:\,��������Z�̡�)
			bRet = FALSE;
			break;
		case ERROR_FILE_EXISTS://�ļ��Ѿ�����
			bRet = TRUE;
			break;
		case ERROR_ALREADY_EXISTS://·���Ѿ�����
			bRet = TRUE;
			break;
		case ERROR_CANCELLED://�û�ȡ���˲���
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
      strTitle =  _T("��ܰ��ʾ��");
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
      pPopupMenu->m_bAutoMenuEnable = FALSE; //2017/11/16 zhangt FALSEʹEnableMenuItem()��Ч
      if (pPopupMenu)
      {
         bRet = TRUE;
         pPopupMenu->Create(pWndParent, point.x, point.y, pPopup->Detach(),TRUE,TRUE);

         //���㵯����
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

//��ȡ���ܹ�ʱ��
BOOL CCustomMgnSysApp::GetLDKCurTime(unsigned int &year,unsigned int &month,unsigned int &day,unsigned int &hour,unsigned int &min,unsigned int &sec)
{
   return m_LDK.GetHaspTime(year,month,day,hour,min,sec);
}
//��ȡ���ܹ�ID
CString CCustomMgnSysApp::GetLDKID()
{
    CString keyInfo =  m_LDK.GetKeyInfo();
    return keyInfo;
}

