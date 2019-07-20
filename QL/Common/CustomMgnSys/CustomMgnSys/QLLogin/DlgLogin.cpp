// DlgLogin.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "../CustomMgnSys.h"
#include "DlgLogin.h"
//#include "DBPersonInfo.h"
#include "Base64Code.h"
#include "../ClassEx/ADOConnEx.h"
#include "CDBFieldDefine.h"

#define MSG_WARMINFORMATION(sTip) (MessageBox(sTip,_T("��ܰ��ʾ"),MB_OK|MB_ICONINFORMATION))
#define MSG_WARNTIPWARNING(sTip) (MessageBox(sTip,_T("��ܰ��ʾ"),MB_OK|MB_ICONWARNING))
#define MSG_WARNTIPSELECT(sTip) (MessageBox(sTip,_T("��ܰ��ʾ"),MB_YESNO|MB_ICONQUESTION))



// CLoginDlg �Ի���

IMPLEMENT_DYNAMIC(CDlgLogin, CBCGPDialog)

CDlgLogin::CDlgLogin(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CDlgLogin::IDD, pParent)
{
	m_bExpandDlg = FALSE;
	m_bCheckSvr = TRUE;

	m_bTipSQL = TRUE;
	m_enType = RETURN_SUCCESS;
}

CDlgLogin::~CDlgLogin()
{
}

void CDlgLogin::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_STATIC_ACT, m_ctrStAct);
	//DDX_Control(pDX, IDC_STATIC_PWD, m_ctrStPwd);
	//DDX_Control(pDX, IDC_STATIC_SVRIP, m_ctrSvrip);
	//DDX_Control(pDX, IDC_STATIC_DBNAME, m_ctrDBName);
	//DDX_Control(pDX, IDC_STATIC_DBLGNAME, m_ctrDBLgName);
	//DDX_Control(pDX, IDC_STATIC_DBLGPWD, m_ctrDBLgPwd);
}

BEGIN_MESSAGE_MAP(CDlgLogin, CBCGPDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDOK_LOGINDLG, &CDlgLogin::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_CONFIG_LOGINDLG, &CDlgLogin::OnBnClickedConfig)
	ON_BN_CLICKED(IDC_BTN_EMPTY_LOGINDLG, &CDlgLogin::OnBnClickedEmpty)
	ON_BN_CLICKED(IDC_BTN_DBSAVE_LOGINDLG, &CDlgLogin::OnBnClickedDBSave)
	ON_BN_CLICKED(IDC_CHK_ACT_LOGINDLG, &CDlgLogin::OnBnClickedChkAct)
	ON_BN_CLICKED(IDC_CHK_APPLY_LOGINDLG, &CDlgLogin::OnBnClickedChkApply)
	ON_EN_CHANGE(IDC_EDIT_USERID_LOGINDLG, &CDlgLogin::OnEnChangeEditActname)
	//ON_MESSAGE(WM_QL_FTP_DOWNLOAD, &CDlgLogin::OnQlFtpDownload)
	ON_MESSAGE(WM_ADOCONN_MSG,&CDlgLogin::OnAdocommMsg)
	ON_BN_CLICKED(IDC_BTN_CHECKSVR, &CDlgLogin::OnBnClickedBtnChecksvr)
	ON_CBN_SELCHANGE(IDC_IPADDRESS_LOGINDLG, &CDlgLogin::OnCbnSelchangeIpaddressLogindlg)
	ON_BN_CLICKED(IDCANCEL, &CDlgLogin::OnBnClickedCancel)
END_MESSAGE_MAP()


// CLoginDlg ��Ϣ�������


BOOL CDlgLogin::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	CString strSysTitle;
	strSysTitle.LoadString(IDS_FRAME_TITLE);
	strSysTitle += _T("-��¼");
	SetWindowText(strSysTitle);

	GetWindowRect(m_rcMain);
	//m_ctrStAct.m_clrText = CLR_WARNING_TIP;
	//m_ctrStPwd.m_clrText = CLR_WARNING_TIP;
	//m_ctrSvrip.m_clrText = CLR_WARNING_TIP;
	//m_ctrDBName.m_clrText = CLR_WARNING_TIP;
	//m_ctrDBLgName.m_clrText = CLR_WARNING_TIP;
	//m_ctrDBLgPwd.m_clrText = CLR_WARNING_TIP;

	//�Ƿ�����Ӧ��������˺�
/*	CString strFilePath = theApp.m_strAppPath +_T("\\ConfigSvr.ini");//���������ļ�·��
	CString strChkApply;
	theApp.GetIniKeyValue(_T("Setting"),_T("LG_CHK_APPLY"),strChkApply,strFilePath);
	BOOL bApply = FALSE;
	if (_T("TRUE") == strChkApply)
	{
		bApply = TRUE;
	}
	((CButton *)GetDlgItem(IDC_CHK_APPLY_LOGINDLG))->SetCheck(bApply);
	SetCtrState(!bApply);
	theApp.m_bApplyAskQl = bApply;
*/

	CADOConnEx ADOConn;
	m_bExpandDlg = ADOConn.GetConncetSqlStr().IsEmpty();
	InitIPComboBox();
	InitDataByIPsel();

/*	SetSvrConfigValue();
	SetActValue();

	CString strChkAutoLog = _T("");
	theApp.GetIniKeyValue(_T("Setting"),_T("LG_CHK_AUTOLOG"),strChkAutoLog);
	BOOL bAutoLog = (_T("TRUE") == strChkAutoLog);
	((CButton *)GetDlgItem(IDC_CHK_ACT_AUTOLOGIN))->SetCheck(bAutoLog);
	if (bAutoLog)
	{
		OnBnClickedOk();
	}
*/
	SetDlgPos(m_bExpandDlg);

	//// ����Ѱ�ұ�� ʵ��һ��KDS-Cloud.exe���� ��ֹ��¼����Ե������
	//::SetProp(GetSafeHwnd(), AfxGetApp()->m_pszAppName, (HANDLE)1);
   
   BringWindowToTop();
  // CRect rtClient;
   //GetWindowRect(rtClient);  	
   //ScreenToClient(rtClient);
   //::SetWindowPos(m_hWnd, HWND_TOPMOST, rtClient.left, rtClient.top, rtClient.Width(), rtClient.Height(), SWP_SHOWWINDOW); 
   ::SetWindowPos(m_hWnd,HWND_TOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
   SetWindowPos(&CWnd::wndNoTopMost,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
   //SetForegroundWindow();//����������ǰ̨,��ǿ���ö� 
   SetActiveWindow();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


BOOL CDlgLogin::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN)//ȷ��
		{
			if (m_bExpandDlg)
			{
				OnBnClickedDBSave();
			}
			else
			{
				OnBnClickedOk();
			}
			return TRUE;
		}
	}
	return CBCGPDialog::PreTranslateMessage(pMsg);
}


void CDlgLogin::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CBCGPDialog::OnPaint();
   //CWnd *pWnd = GetDlgItem(IDC_STATIC_LOGO);
   //CRect rect;
   //pWnd->GetWindowRect(&rect);
   //ScreenToClient(&rect);

   CMFCToolBarImages	imgLogo;
   imgLogo.Load (IDB_PNG_LOGOSIMPLE);
   imgLogo.SetTransparentColor (RGB (236, 0, 140));
   imgLogo.SetSingleImage ();
   CAfxDrawState ds;
   imgLogo.PrepareDrawImage (ds);

   imgLogo.Draw (&dc, 20,20,0);

   imgLogo.EndDrawImage (ds);
   
   

	//������Դ��PNG
	//CWnd *pWnd = GetDlgItem(IDC_STATIC_LOGO);
	//CRect rect;
	//pWnd->GetWindowRect(&rect);
	//ScreenToClient(&rect);
	//Graphics graphics(dc); // Create a GDI+ graphics object
	//Image *pImage = NULL; // Construct an image
	//if (theApp.ImageFromIDResource(IDB_PNG_LOGOSIMPLE,_T("PNG"),pImage))
	//{
	//	dc.SetBkMode(TRANSPARENT);
	//	ImageAttributes imAtt;
	//	imAtt.SetColorKey(Color(180,180,180),Color(255,255,255),ColorAdjustTypeDefault);
	//	graphics.SetSmoothingMode(SmoothingModeAntiAlias);
	//	graphics.DrawImage(pImage,Rect(rect.left,rect.top, pImage->GetWidth(), pImage->GetHeight()),  
	//		0, 1,pImage->GetWidth(), pImage->GetHeight(),UnitPixel,&imAtt,NULL,NULL);
	//}

	//if (pImage)
	//{
	//	delete pImage;
	//	pImage = NULL;
	//}
	
}

void CDlgLogin::OnBnClickedOk()
{
	OnWriteIni();

	CADOConnEx ADOConn;
	//�������ļ��ж�ȡ��ص���Ϣ
	if (ADOConn.GetConncetSqlStr().IsEmpty())
	{
		MSG_WARMINFORMATION(_T("����д��������ã�"));

      return;
	}
	
	//ִ�����ݲ���
	CString strUserID;
 	CString strUserPwd;

	GetDlgItemText(IDC_EDIT_USERID_LOGINDLG,strUserID);
	GetDlgItemText(IDC_EDIT_USERPWD_LOGINDLG,strUserPwd);
	strUserID.Trim();
	strUserPwd.Trim();

	if (strUserID.IsEmpty())
	{
		MSG_WARNTIPWARNING(_T("�˻�����Ϊ�գ�"));
		m_enType = RETURN_EMPTY_ACCOUNT;

		return;
	}

	if (strUserPwd.IsEmpty())
	{
		MSG_WARNTIPWARNING(_T("���벻��Ϊ�գ�"));
		m_enType = RETURN_EMPTY_PASSWD;
		
      return;
	}

	m_bTipSQL = TRUE;

	CString strSQL = _T("");
	CBase64Code Base64Code;
	CString strEnCodePwd = Base64Code.base64Encode(strUserPwd);
	//strSQL.Format(_T("select * from %s where %s='%s'and %s='%s'"),
   //   DB_TABLE_USERINFO,DBUser_key_cUserID,strUserID,
   //   DBUser_key_cPassword,strEnCodePwd);


   ADOConn.SetCommandParameter(DBUser_key_cUserID,strUserID);
   ADOConn.SetCommandParameter(DBUser_key_cPassword,strEnCodePwd);

   strSQL.Format(_T("select * from %s where %s=? and %s=? ;"),
      DB_TABLE_USERINFO,DBUser_key_cUserID,DBUser_key_cPassword);
   auto aRet = ADOConn.GetCommandRecordSet(strSQL);
   
   //��ʱ������		by WangZY 2018/08/21
   //if (_T("admin") == strUserID
   //   && strEnCodePwd == Base64Code.base64Encode(_T("123321")))
   //{
   //   SaveUserInfo();
   //   CBCGPDialog::OnOK();

   //   return;
   //}

   if (ADOConn.adoEOF())   //�����ڴ��û���
   {
      SetDlgItemText(IDC_EDIT_USERPWD_LOGINDLG,_T(""));
      m_enType = RETURN_ERROR_ACCOUNT_PWD;

      MSG_WARNTIPWARNING(_T("�˻����������"));

      return;
   }
   

	//��ǿ��¼�ж� 2018/03/01 zhangt ��ֹ��¼ʱSQLע������
	theApp.m_objDBPerson.GetAllDBInfo(&ADOConn);
	if ((0 != theApp.m_objDBPerson.m_strUserID.CompareNoCase(strUserID)) 
		||(0 != theApp.m_objDBPerson.m_strUserPwd.Compare(strEnCodePwd)) )
	{
   
      m_enType = RETURN_ILLEGAL_INPUT;
      MSG_WARNTIPWARNING(_T("�Ƿ����룡"));
      
      return;
   }

	SaveUserInfo();
	//theApp.m_objDBPerson.GetAllDBInfo(&ADOConn);
	if (0 == strUserID.CompareNoCase(_T("admin")))
	{
		//theApp.m_objDBPerson.m_strUserDuty = _T("��������Ա");	
		theApp.m_objDBPerson.m_nUserState = 0;
	}

	if (theApp.m_objDBPerson.m_nUserState == 1)
	{
		MSG_WARNTIPWARNING(_T("��Ǹ�����ѱ�ע����"));
		m_enType = RETURN_WRITTEN_OFF;
		CBCGPDialog::OnCancel();

      return;
	}

	
	////theApp.m_listMenus.GetListFromDB(&ADOConn);

	////2017/07/10 zhangt adminĬ��ӵ�����е�Ȩ��
	//int nCountPower = theApp.m_listMenus.GetChildCount();
	//if (0 == theApp.m_objDBPerson.m_strUserID.CompareNoCase(_T("admin")))//adminϵͳĬ�ϳ�������Ա
	//{
	//	theApp.m_objDBPerson.m_strUserPower.Empty();
	//	for(int i=0;i<nCountPower;i++)
	//		theApp.m_objDBPerson.m_strUserPower += _T("1");
	//}//2017/07/10_end

	////2017/09/11 zhangt ͨ��������ϵͳ��������ݵ���Ȩ���ֶγ��Ⱥ͵�����������������
	////Ϊ�����������´���
	//CString strPower = _T("");
	//if (theApp.m_objDBPerson.m_strUserPower.GetLength()>nCountPower)
	//{
	//	strPower = theApp.m_objDBPerson.m_strUserPower.Left(nCountPower);			
	//}
	//else
	//{
	//	strPower = theApp.m_objDBPerson.m_strUserPower;
	//	int i = theApp.m_objDBPerson.m_strUserPower.GetLength();
	//	for(;i<nCountPower;i++)
	//	{
	//		strPower.AppendChar('0');
	//	}
	//}
	////theApp.m_objDBPerson.m_strUserPower = strPower;
	////2017/09/11_end

	//if(theApp.m_objDBPerson.m_strUserPower.GetLength() != nCountPower)
 //  {
 //     m_enType = RETURN_POWER_ERROR;
 //     MessageBox(_T("Ȩ�޳���"),_T("��ܰ��ʾ"),MB_ICONERROR);

 //     return;
 //  }

	
	//д�˻�������
	//theApp.SetIniKeyValue(_T("ACT"),_T("USERID"),theApp.OnEncodeStr(strUserID));
	//theApp.SetIniKeyValue(_T("ACT"),_T("USERPWD"),theApp.OnEncodeStr(strUserPwd));

	//update���һ�ε�¼ʱ��
	COleDateTime oleCurTime = COleDateTime::GetCurrentTime();
	strSQL.Format(_T("update %s set %s = %s where %s='%s'"),
      DB_TABLE_USERINFO,
		DBUser_key_dtLastLoadTime,DBS_GETDATESTR,
		DBUser_key_cUserID,strUserID);
	ADOConn.ExecuteSQL(strSQL);

	//theApp.m_objDBPerson.m_tInTime = ADOConn.GetSqlTime();
	//��ʼ��app���ݿ������
	//theApp.m_pADOConn = new CADOConnEx;
   //auto pAdoConn = new CADOConnEx;
   //WorkLog::InsertOneWorkLog()
#ifdef _DEBUG
	//_DEBUG�²����������־����־��
	//theApp.m_objDBLog.SetLogToDB(FALSE);
#endif // _DEBUG

	if (BST_CHECKED == ((CButton *)GetDlgItem(IDC_CHK_ACT_AUTOLOGIN))->GetCheck())
	{
		theApp.SetIniKeyValue(_T("Setting"),_T("LG_CHK_AUTOLOG"),_T("TRUE"));
	}
	else
	{
		theApp.SetIniKeyValue(_T("Setting"),_T("LG_CHK_AUTOLOG"),_T("FALSE"));
	}

   m_enType = RETURN_SUCCESS;
	CBCGPDialog::OnOK();
}

void CDlgLogin::SetDlgPos(BOOL bExpand)
{
	CString strText;
	CRect rcMain,rcParam;
	GetWindowRect(&rcMain);
	GetDlgItem(IDC_STATIC_ACCONT)->GetWindowRect(rcParam);
	if (bExpand)
	{
		rcMain.bottom = rcMain.top + m_rcMain.Height();
		strText = _T("���á�");
	}
	else
	{
		rcMain.bottom = rcParam.bottom + 8;
		strText = _T("���á�");	
	}

	GetDlgItem(IDOK_LOGINDLG)->ShowWindow(!bExpand);
	SetDlgItemText(IDC_BTN_CONFIG_LOGINDLG,strText);
	MoveWindow(rcMain);
}

void CDlgLogin::SetCtrState(BOOL bEnable)
{
	GetDlgItem(IDC_EDIT_DBACT_LOGINDLG)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_DBPWD_LOGINDLG)->EnableWindow(bEnable);
	CEdit* pEditDB = (CEdit *)GetDlgItem(IDC_EDIT_DBNAME_LOGINDLG);
	CEdit* pEditAddr = (CEdit *)GetDlgItem(IDC_IPADDRESS_LOGINDLG);

	pEditDB->SetReadOnly(bEnable);
	//pEditAddr->SetReadOnly(!bEnable);

	GetDlgItem(IDC_STATIC_DBNAME_LOGINDLG)->SetWindowText(bEnable?_T("���ݿ����ƣ�"):_T("�����˻���"));
	//pEditDB->SetWindowText(bEnable?_T("QLPDMMGN"):_T(""));
	//pEditAddr->SetWindowText(/*bEnable?_T(""):*/_T("www.qilirj.cn"));	
   pEditDB->SetWindowText(_T("QLPDMMGN"));
   pEditAddr->SetWindowText(_T("www.qilirj.cn"));	
}

void CDlgLogin::SetSvrConfigValue(CConfigInfo *pConfigInfo)
{
	if (pConfigInfo)
	{
		SetDlgItemText(IDC_IPADDRESS_LOGINDLG,theApp.OnDecodeStr(pConfigInfo->m_strIPAddress, WORD_PWD_KEY));
		SetDlgItemText(IDC_EDIT_PORT_LOGINDLG,theApp.OnDecodeStr(pConfigInfo->m_strPort1, WORD_PWD_KEY));
		SetDlgItemText(IDC_EDIT_DBNAME_LOGINDLG,theApp.OnDecodeStr(pConfigInfo->m_strDatabaseName,WORD_PWD_KEY));
		SetDlgItemText(IDC_EDIT_DBACT_LOGINDLG,theApp.OnDecodeStr(pConfigInfo->m_strDatabaseAccount,WORD_PWD_KEY));
		SetDlgItemText(IDC_EDIT_DBPWD_LOGINDLG,theApp.OnDecodeStr(pConfigInfo->m_strDatabasePassword,WORD_PWD_KEY));
		SetDlgItemText(IDC_EDIT_PORT_FILE,theApp.OnDecodeStr(pConfigInfo->m_strPort2, WORD_PWD_KEY));

		BOOL bSaveLocal = pConfigInfo->m_bRememberPassword;
		((CButton *)GetDlgItem(IDC_CHK_ACT_LOGINDLG))->SetCheck(bSaveLocal);
		CString strUserID = theApp.OnDecodeStr(pConfigInfo->m_strUserID,WORD_PWD_KEY);
		CString strUsePWD = theApp.OnDecodeStr(pConfigInfo->m_strUserPassword,WORD_PWD_KEY);
		SetDlgItemText(IDC_EDIT_USERID_LOGINDLG,strUserID);
		SetDlgItemText(IDC_EDIT_USERPWD_LOGINDLG,bSaveLocal?strUsePWD:_T(""));
		BOOL bAutoLog = pConfigInfo->m_bAutomaticLogon;
		((CButton *)GetDlgItem(IDC_CHK_ACT_AUTOLOGIN))->SetCheck(bAutoLog);

		UpdateWindow();
		if (bAutoLog)
		{
			OnBnClickedOk();
		}
	}
}

void CDlgLogin::SetActValue()
{
	CString strUserID;
	CString strUserPwd;

	theApp.GetIniKeyValue(_T("ACT"),_T("USERID"),strUserID);
	theApp.GetIniKeyValue(_T("ACT"),_T("USERPWD"),strUserPwd);

	//�����¼�˻������뵽����
	CString strChkAct;
	theApp.GetIniKeyValue(_T("Setting"),_T("LG_CHK_ACT"),strChkAct);
	BOOL bSaveLocal = (_T("TRUE") == strChkAct);
	((CButton *)GetDlgItem(IDC_CHK_ACT_LOGINDLG))->SetCheck(bSaveLocal);
	SetDlgItemText(IDC_EDIT_USERID_LOGINDLG,bSaveLocal?theApp.OnDecodeStr(strUserID,WORD_PWD_KEY):_T(""));
	SetDlgItemText(IDC_EDIT_USERPWD_LOGINDLG,bSaveLocal?theApp.OnDecodeStr(strUserPwd,WORD_PWD_KEY):_T(""));
}

void CDlgLogin::OnBnClickedConfig()
{
	m_bExpandDlg = !m_bExpandDlg;
	SetDlgPos(m_bExpandDlg);
}

void CDlgLogin::InitIPComboBox()
{
	CString strFilePath;// = theApp.m_strAppPath + _T("\\�û��ļ�\\����\\ConfigSvr.dat");//���������ļ�·��
	
   //�޸Ľ�PDM��¼��Ϣ�洢���û��ļ��Ķ����У����ָ��Ŀ¼�ļ������ڵ�ԭĿ¼�¶�ȡ��Ϣ
	//if (!PathFileExists(strFilePath))
	{
		strFilePath = theApp.m_strAppPath + _T("ConfigSvr.dat");
	}
	CComboBox *pComboBoxIP = (CComboBox *)GetDlgItem(IDC_IPADDRESS_LOGINDLG);
	m_listConfigInfo.Empty();
	m_listConfigInfo.OnReadFile(strFilePath);
	int nCount = m_listConfigInfo.GetCount();
	for(int nIndex = nCount-1; nIndex >= 0; nIndex--)
	{
		CConfigInfo *pConfigInfo = m_listConfigInfo.GetItem(nIndex);
		if(pConfigInfo)
		{
			pComboBoxIP->AddString(theApp.OnDecodeStr(pConfigInfo->m_strIPAddress,WORD_PWD_KEY));
		}
	}

	if((nCount > 0) && (pComboBoxIP->GetCurSel()<0))
   {
      pComboBoxIP->SetCurSel(0);
   }
}

void CDlgLogin::OnBnClickedEmpty()
{
	if(IDOK == MessageBox(_T("ȷ�����������"),_T("��ܰ��ʾ��"),MB_ICONQUESTION|MB_OKCANCEL))
	{
		CString strIPport = _T("");
		CString strDBName = _T("");
		CString strDBAccount = _T("");
		CString strDBPwd = _T("");
		CString strFilePort = _T("");

		CString strFilePath = theApp.m_strAppPath +_T("ConfigSvr.ini");//���������ļ�·��

		theApp.SetIniKeyValue(_T("SQLSVR"),_T("SVR"),strIPport,strFilePath);
		theApp.SetIniKeyValue(_T("SQLSVR"),_T("DB"),strDBName,strFilePath);
		theApp.SetIniKeyValue(_T("SQLSVR"),_T("UID"),strDBAccount,strFilePath);
		theApp.SetIniKeyValue(_T("SQLSVR"),_T("PWD"),strDBPwd,strFilePath);
		theApp.SetIniKeyValue(_T("SQLSVR"),_T("FILEPORT"),strDBPwd,strFilePath);

		SetDlgItemText(IDC_IPADDRESS_LOGINDLG,strIPport);
		SetDlgItemText(IDC_EDIT_PORT_LOGINDLG,strIPport);
		SetDlgItemText(IDC_EDIT_DBNAME_LOGINDLG,strDBName);
		SetDlgItemText(IDC_EDIT_DBACT_LOGINDLG,strDBAccount);
		SetDlgItemText(IDC_EDIT_DBPWD_LOGINDLG,strDBPwd);
		SetDlgItemText(IDC_EDIT_PORT_FILE,strFilePort);

		m_listConfigInfo.Empty();
		//strFilePath = theApp.m_strAppPath +_T("\\ConfigSvr.dat");//���������ļ�·��
		strFilePath = theApp.m_strAppPath + _T("\\�û��ļ�\\����\\ConfigSvr.dat");


		DeleteFile(strFilePath);
		CComboBox *pComboBoxIP = (CComboBox *)GetDlgItem(IDC_IPADDRESS_LOGINDLG);
		pComboBoxIP->ResetContent();
	}
}

void CDlgLogin::OnBnClickedDBSave()
{
	//OnWriteIni();
	m_bExpandDlg = FALSE;
	SetDlgPos(m_bExpandDlg);

	//MessageBox(_T("���ñ���ɹ�"),_T("��ܰ��ʾ��"),MB_ICONINFORMATION);
	OnBnClickedOk();
}

void CDlgLogin::OnWriteIni()
{
	CString strIPport = _T("");
	CString strDBName;
	CString strDBAccount;
	CString strDBPwd;
	CString strIP;
	CString strPort;
	CString strFilePort = _T("");

	GetDlgItemText(IDC_IPADDRESS_LOGINDLG,strIP);
	GetDlgItemText(IDC_EDIT_PORT_LOGINDLG,strPort);
	GetDlgItemText(IDC_EDIT_DBNAME_LOGINDLG,strDBName);
	GetDlgItemText(IDC_EDIT_DBACT_LOGINDLG,strDBAccount);
	GetDlgItemText(IDC_EDIT_DBPWD_LOGINDLG,strDBPwd);
	GetDlgItemText(IDC_EDIT_PORT_FILE,strFilePort);

	strIP.Trim();
	strPort.Trim();
	strIPport = strIP;
	if (!strPort.IsEmpty())
	{
		strIPport += _T(",");
		strIPport += strPort;
	}	

	CString strFilePath = theApp.m_strAppPath +_T("ConfigSvr.ini");//���������ļ�·��

	theApp.SetIniKeyValue(_T("SQLSVR"),_T("SVR"),theApp.OnEncodeStr(strIPport,WORD_PWD_KEY),strFilePath);
	theApp.SetIniKeyValue(_T("SQLSVR"),_T("DB"),theApp.OnEncodeStr(strDBName,WORD_PWD_KEY),strFilePath);
	theApp.SetIniKeyValue(_T("SQLSVR"),_T("UID"),theApp.OnEncodeStr(strDBAccount,WORD_PWD_KEY),strFilePath);
	theApp.SetIniKeyValue(_T("SQLSVR"),_T("PWD"),theApp.OnEncodeStr(strDBPwd,WORD_PWD_KEY),strFilePath);
	theApp.SetIniKeyValue(_T("SQLSVR"),_T("FILEPORT"),theApp.OnEncodeStr(strFilePort,WORD_PWD_KEY),strFilePath);

	UINT nState = ((CButton *)GetDlgItem(IDC_CHK_APPLY_LOGINDLG))->GetCheck();
	if (BST_CHECKED == nState)
	{
		theApp.SetIniKeyValue(_T("Setting"),_T("LG_CHK_APPLY"),_T("TRUE"),strFilePath);
	}
	else
	{
		theApp.SetIniKeyValue(_T("Setting"),_T("LG_CHK_APPLY"),_T("FALSE"),strFilePath);
	}
}

void CDlgLogin::OnEnChangeEditActname()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CBCGPDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	SetDlgItemText(IDC_EDIT_USERPWD_LOGINDLG,_T(""));
}

void CDlgLogin::OnBnClickedChkAct()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (BST_CHECKED == ((CButton *)GetDlgItem(IDC_CHK_ACT_LOGINDLG))->GetCheck())
	{
		theApp.SetIniKeyValue(_T("Setting"),_T("LG_CHK_ACT"),_T("TRUE"));
	}
	else
	{
		theApp.SetIniKeyValue(_T("Setting"),_T("LG_CHK_ACT"),_T("FALSE"));
	}
}

void CDlgLogin::OnBnClickedChkApply()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strFilePath = theApp.m_strAppPath +_T("ConfigSvr.ini");//���������ļ�·��
	/*CString strFilePath = theApp.m_strKdsWorkPath + _T("\\�û��ļ�\\����\\ConfigSvr.ini");*/
	UINT nState = ((CButton *)GetDlgItem(IDC_CHK_APPLY_LOGINDLG))->GetCheck();
	if (BST_CHECKED == nState)
	{
		theApp.SetIniKeyValue(_T("Setting"),_T("LG_CHK_APPLY"),_T("TRUE"),strFilePath);
		SetCtrState(FALSE);
	}
	else
	{
		theApp.SetIniKeyValue(_T("Setting"),_T("LG_CHK_APPLY"),_T("FALSE"),strFilePath);
		SetCtrState(TRUE);
	}
}


void CDlgLogin::OnBnClickedBtnChecksvr()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnWriteIni();

	CheckSvr();
}


void CDlgLogin::CheckSvr()
{
	CADOConnEx ADOConn;
	m_bCheckSvr = TRUE;
	m_bTipSQL = TRUE;
	//�������ļ��ж�ȡ��ص���Ϣ
	if (ADOConn.GetConncetSqlStr().IsEmpty())
	{
		MSG_WARMINFORMATION(_T("����д��������ã�"));
	}
	else
	{
		//������ݿ�����
		ADOConn.SetExceptionHwnd(GetSafeHwnd());
		CString strSQL = _T("");
		strSQL.Format(_T("select * from %s where %s='%s'"),
         DB_TABLE_USERINFO,DBUser_key_cUserID,_T("admin"));
		auto rRet = ADOConn.GetRecordSet(strSQL);
		if (!ADOConn.adoEOF())//���ڴ��û���
		{
			TRACE(_T("Exist"));
		}

		////����ļ������ ���⹹�������ļ�
		//CString strDirPath = _T("������");
		//CString strOrderNo = _T("test000");
		/*CFileTransferEx cFileTransfer(theApp.m_strKdsWorkPath,GetSafeHwnd(),CFileTransferEx::En_Login_Null);
		cFileTransfer.Init(strOrderNo,FTP_MODE_TYPE_OTHER);
		cFileTransfer.m_DownMsg[_T("test000.tmp")] = theApp.m_strKdsWorkPath+_T("\\�û��ļ�\\test000.tmp");
		cFileTransfer.DownLoad();*/

		if (m_bCheckSvr)
		{
			MessageBox(_T("��ϲ��������������"),_T("��ܰ��ʾ"),MB_ICONINFORMATION);
		}
	}
}

LRESULT CDlgLogin::OnAdocommMsg(WPARAM wParam,LPARAM lParam)
{
	LPCTSTR pMsg = (LPCTSTR)lParam;
	if (pMsg)
	{
		m_bCheckSvr = FALSE;
		if(m_bTipSQL)
		{
			m_bTipSQL = FALSE;
			MessageBox(_T("����ȷ����SQL���ݷ����"),_T("��ܰ��ʾ"),MB_ICONWARNING);
		}	
	}

	return 0L;
}

void CDlgLogin::OnCbnSelchangeIpaddressLogindlg()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	InitDataByIPsel();
}

void CDlgLogin::InitDataByIPsel()
{
	int nSel = 0;
	CString strIP = _T("");
	CComboBox *pComboBoxIP = (CComboBox *)GetDlgItem(IDC_IPADDRESS_LOGINDLG);
	nSel = pComboBoxIP->GetCurSel();

	if(nSel >= 0)
	{
		pComboBoxIP->GetLBText(nSel, strIP);
		int nFlag = 0;
		int nCount = m_listConfigInfo.GetCount();
		for(int nIndex = nCount-1; nIndex >= 0; nIndex--)
		{
			CConfigInfo *pConfigInfo = m_listConfigInfo.GetItem(nIndex);
			if(pConfigInfo)
			{
				if(nFlag == nSel)
				{
					((CButton *)GetDlgItem(IDC_CHK_APPLY_LOGINDLG))->SetCheck(pConfigInfo->m_bApplyAccount);
					SetCtrState(!(pConfigInfo->m_bApplyAccount));
					SetSvrConfigValue(pConfigInfo);
					break;
				}

				nFlag++;
			}
		}
	}
}


void CDlgLogin::SaveUserInfo(BOOL bRet /*= TRUE */)
{
	CString strUseID = _T("");
	CString strUserPwd = _T("");
	BOOL bRemePwd = FALSE;
	BOOL bAutoLogon = FALSE;
	CString strIP = _T("");
	CString strDBName = _T("");
	CString strDBAccount = _T("");
	CString strDBPwd = _T("");
	BOOL bApply = FALSE;
	CString strPort1 = _T("");
	CString strPort2 = _T("");

	GetDlgItemText(IDC_EDIT_USERID_LOGINDLG, strUseID);
	GetDlgItemText(IDC_EDIT_USERPWD_LOGINDLG, strUserPwd);
	bRemePwd = ((CButton *)GetDlgItem(IDC_CHK_ACT_LOGINDLG))->GetCheck();
	bAutoLogon = ((CButton *)GetDlgItem(IDC_CHK_ACT_AUTOLOGIN))->GetCheck();
	GetDlgItemText(IDC_IPADDRESS_LOGINDLG, strIP);
	GetDlgItemText(IDC_EDIT_DBNAME_LOGINDLG,strDBName);
	GetDlgItemText(IDC_EDIT_DBACT_LOGINDLG,strDBAccount);
	GetDlgItemText(IDC_EDIT_DBPWD_LOGINDLG,strDBPwd);
	GetDlgItemText(IDC_EDIT_PORT_LOGINDLG, strPort1);
	GetDlgItemText(IDC_EDIT_PORT_FILE, strPort2);

	bApply = ((CButton *)GetDlgItem(IDC_CHK_APPLY_LOGINDLG))->GetCheck();

	if(strIP.IsEmpty() || strDBName.IsEmpty())
	{
		/*theApp.OnShowDesktopAlert(_T("��Ϣ������!"),TIP_COLOR_WARNING,TIP_TIME_DELAY);*/
		MSG_WARMINFORMATION(_T("��Ϣ��������"));
		return;
	}

	CConfigInfo cConfigInfo;
	cConfigInfo.m_strUserID = theApp.OnEncodeStr(strUseID,WORD_PWD_KEY);
	cConfigInfo.m_strUserPassword = theApp.OnEncodeStr(strUserPwd,WORD_PWD_KEY);
	cConfigInfo.m_bRememberPassword = bRemePwd;
	cConfigInfo.m_bAutomaticLogon = bAutoLogon;
	cConfigInfo.m_strIPAddress = theApp.OnEncodeStr(strIP,WORD_PWD_KEY);
	cConfigInfo.m_strDatabaseName = theApp.OnEncodeStr(strDBName,WORD_PWD_KEY);
	cConfigInfo.m_strDatabaseAccount = theApp.OnEncodeStr(strDBAccount,WORD_PWD_KEY);
	cConfigInfo.m_strDatabasePassword = theApp.OnEncodeStr(strDBPwd,WORD_PWD_KEY);
	cConfigInfo.m_strPort1 = theApp.OnEncodeStr(strPort1,WORD_PWD_KEY);
	cConfigInfo.m_strPort2 = theApp.OnEncodeStr(strPort2,WORD_PWD_KEY);
	cConfigInfo.m_bApplyAccount = bApply;

	CString strFilePath = theApp.m_strAppPath +_T("\\ConfigSvr.dat");//���������ļ�·��
	//CString strFilePath = theApp.m_strAppPath + _T("\\�û��ļ�\\����\\ConfigSvr.dat");
	int nCount = m_listConfigInfo.GetCount();

	for(int nIndex = 0; nIndex < nCount; nIndex++)
	{
		CConfigInfo *pConfigInfo = m_listConfigInfo.GetItem(nIndex);
		if(pConfigInfo && cConfigInfo.m_strUserDefinedName==pConfigInfo->m_strUserDefinedName \
			&& cConfigInfo.m_strIPAddress == pConfigInfo->m_strIPAddress && cConfigInfo.m_strDatabaseName == pConfigInfo->m_strDatabaseName)
		{
			m_listConfigInfo.DeleteItem(nIndex);
			break;
		}
	}
	
	m_listConfigInfo.AddItem(&cConfigInfo);

	m_listConfigInfo.OnWriteFile(strFilePath);
}

void CDlgLogin::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_enType = RETURN_EXIT;

	//EndDialog(IDCANCEL);
   CBCGPDialog::OnCancel();
}
