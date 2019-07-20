// LoginDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "QlFileTransferEx.h"
#include "LoginDlg.h"
#include "afxdialogex.h"

#include "QlFileTransferEx.h"
#include "ADOConnEx.h"
#include "ClassDB\DBCustomInfo.h"
#include "Base64Code.h"


// CLoginDlg �Ի���

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(int nLoginType /*= En_Login_User*/,CWnd* pParent /*=NULL*/)
	: CDialogEx(CLoginDlg::IDD, pParent)
{
	m_bExpandDlg = FALSE;
	m_nLoginType = nLoginType;
}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCEDIT_DBPATH, m_EditBrawoer);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_CONFIG_LOGINDLG, &CLoginDlg::OnBnClickedBtnConfigLogindlg)
	ON_BN_CLICKED(IDOK, &CLoginDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CHK_ACT_LOGINDLG, &CLoginDlg::OnBnClickedChkActLogindlg)
	ON_BN_CLICKED(IDC_CHK_APPLY_LOGINDLG, &CLoginDlg::OnBnClickedChkApplyLogindlg)
	ON_BN_CLICKED(IDC_BTN_EMPTY_LOGINDLG, &CLoginDlg::OnBnClickedBtnEmptyLogindlg)
	ON_BN_CLICKED(IDC_BTN_DBSAVE_LOGINDLG, &CLoginDlg::OnBnClickedBtnDbsaveLogindlg)
	ON_MESSAGE(WM_ADOCONN_MSG, &CLoginDlg::OnAdoconnMsg)
END_MESSAGE_MAP()


// CLoginDlg ��Ϣ�������


BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	GetWindowRect(m_rcMain);

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	CString strChkApply;
	theApp.GetIniKeyValue(_T("Setting"),_T("LG_CHK_APPLY"),strChkApply,theApp.m_strSvrPath);
	BOOL bApply = FALSE;
	if (_T("TRUE") == strChkApply)
	{
		bApply = TRUE;
	}
	((CButton *)GetDlgItem(IDC_CHK_APPLY_LOGINDLG))->SetCheck(bApply);
	SetCtrState(!bApply);

	CADOConnEx ADOConn;
	m_bExpandDlg = ADOConn.GetConncetSqlStr().IsEmpty();

	SetSvrConfigValue();
	SetActValue();

	SetDlgPos(m_bExpandDlg);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CLoginDlg::SetSvrConfigValue()
{
	CString strIPport;
	CString strDBName;
	CString strDBAccount;
	CString strDBPwd;
	CString strFilePort;
	CString strDBPath = _T("");
	CString strIP = _T("");
	CString strPort = _T("");
	CString strDBAccessFielPath;
	CString strFilePath = theApp.m_strSvrPath;//���������ļ�·��
   CString strFtpIP  =_T("");
	theApp.GetIniKeyValue(_T("SQLSVR"),_T("SVR"),strIPport,strFilePath);
	theApp.GetIniKeyValue(_T("SQLSVR"),_T("DB"),strDBName,strFilePath);
	theApp.GetIniKeyValue(_T("SQLSVR"),_T("UID"),strDBAccount,strFilePath);
	theApp.GetIniKeyValue(_T("SQLSVR"),_T("PWD"),strDBPwd,strFilePath);
	theApp.GetIniKeyValue(_T("SQLSVR"),_T("FILEPORT"),strFilePort,strFilePath);
	theApp.GetIniKeyValue(_T("SQLSVR"),_T("LOCAL_DB_PATH"),strDBPath,strFilePath);
   theApp.GetIniKeyValue(_T("SQLSVR"),_T("SVRLOCAL"),strFtpIP,strFilePath);//����Ftp��ַ��ȡ
   CString strValue;
   theApp.GetIniKeyValue(_T("SQLSVR"),_T("HTTPMODE"),strValue,strFilePath);
   BOOL bHttpMode = strValue == _T("TRUE") ? TRUE : FALSE;

	strIPport = theApp.OnDecodeStr(strIPport,WORD_PWD_KEY);
	int nPos = strIPport.Find(',');
	if (nPos<0)
	{
		strIP = strIPport;
		//strPort = _T("1433");
	}
	else
	{
		strIP = strIPport.Left(nPos);
		strPort = strIPport.Right(strIPport.GetLength()-nPos-1);
	}

	SetDlgItemText(IDC_IPADDRESS_LOGINDLG,strIP);
	SetDlgItemText(IDC_EDIT_PORT_LOGINDLG,strPort);
	SetDlgItemText(IDC_EDIT_DBNAME_LOGINDLG,theApp.OnDecodeStr(strDBName,WORD_PWD_KEY));
	SetDlgItemText(IDC_EDIT_DBACT_LOGINDLG,theApp.OnDecodeStr(strDBAccount,WORD_PWD_KEY));
	SetDlgItemText(IDC_EDIT_DBPWD_LOGINDLG,theApp.OnDecodeStr(strDBPwd,WORD_PWD_KEY));
	SetDlgItemText(IDC_EDIT_PORT_FILE,theApp.OnDecodeStr(strFilePort,WORD_PWD_KEY));
	SetDlgItemText(IDC_MFCEDIT_DBPATH,strDBPath);
   SetDlgItemText(IDC_EDT_FTP_ADDRESS,strFtpIP);

   ((CButton *)GetDlgItem(IDC_RADIO_MODE_FTP))->SetCheck(!bHttpMode);
   ((CButton *)GetDlgItem(IDC_RADIO_MODE_HTTP))->SetCheck(bHttpMode);
	BOOL bShowState = FALSE;

	GetDlgItem(IDC_STATIC_DBPATH_LOGINDLG)->ShowWindow(bShowState ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_MFCEDIT_DBPATH)->ShowWindow(bShowState ? SW_SHOW : SW_HIDE);

	GetDlgItem(IDC_STATIC_DBNAME_LOGINDLG)->ShowWindow(bShowState ? SW_HIDE : SW_SHOW);
	GetDlgItem(IDC_EDIT_DBNAME_LOGINDLG)->ShowWindow(bShowState ? SW_HIDE : SW_SHOW);
	GetDlgItem(IDC_STATIC_PORT2_LOGINDLG)->ShowWindow(bShowState ? SW_HIDE : SW_SHOW);
	GetDlgItem(IDC_STATIC_DBNAME)->ShowWindow(bShowState ? SW_HIDE : SW_SHOW);
	GetDlgItem(IDC_EDIT_PORT_FILE)->ShowWindow(bShowState ? SW_HIDE : SW_SHOW);
	GetDlgItem(IDC_CHK_APPLY_LOGINDLG)->ShowWindow(bShowState ? SW_HIDE : SW_SHOW);
   GetDlgItem(IDC_RADIO_MODE_FTP)->ShowWindow(bShowState ? SW_HIDE : SW_SHOW);
   GetDlgItem(IDC_RADIO_MODE_HTTP)->ShowWindow(bShowState ? SW_HIDE : SW_SHOW);
}

void CLoginDlg::SetActValue()
{
	CString strUserID;
	CString strUserPwd;

	CString strKey = _T("");
	switch(m_nLoginType)
	{
	case En_Login_User:
		strKey = _T("ACT");
		break;
	case En_Login_Custom:
		strKey = _T("CUSACT");
		break;
	}
	
	theApp.GetIniKeyValue(strKey,_T("USERID"),strUserID,theApp.m_strMgnPath);
	theApp.GetIniKeyValue(strKey,_T("USERPWD"),strUserPwd,theApp.m_strMgnPath);

	//�����¼�˻������뵽����
	CString strChkAct;
	theApp.GetIniKeyValue(_T("Setting"),_T("LG_CHK_ACT"),strChkAct,theApp.m_strMgnPath);
	BOOL bSaveLocal = (_T("TRUE") == strChkAct);
	((CButton *)GetDlgItem(IDC_CHK_ACT_LOGINDLG))->SetCheck(bSaveLocal);
	SetDlgItemText(IDC_EDIT_USERID_LOGINDLG,bSaveLocal?theApp.OnDecodeStr(strUserID,WORD_PWD_KEY):_T(""));
	SetDlgItemText(IDC_EDIT_USERPWD_LOGINDLG,bSaveLocal?theApp.OnDecodeStr(strUserPwd,WORD_PWD_KEY):_T(""));
}

void CLoginDlg::SetCtrState(BOOL bEnable)
{
	GetDlgItem(IDC_EDIT_DBACT_LOGINDLG)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_DBPWD_LOGINDLG)->EnableWindow(bEnable);
	CEdit* pEditDB = (CEdit *)GetDlgItem(IDC_EDIT_DBNAME_LOGINDLG);
	if (bEnable)
	{
		GetDlgItem(IDC_STATIC_DBNAME_LOGINDLG)->SetWindowText(_T("���ݿ����ƣ�"));		
		pEditDB->SetReadOnly(TRUE);
		pEditDB->SetWindowText(_T("QLPLM"));
	}
	else
	{
		GetDlgItem(IDC_STATIC_DBNAME_LOGINDLG)->SetWindowText(_T("�����˻���"));
		pEditDB->SetReadOnly(FALSE);
		pEditDB->SetWindowText(_T(""));
	}
}

void CLoginDlg::OnBnClickedBtnConfigLogindlg()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_bExpandDlg = !m_bExpandDlg;
	SetDlgPos(m_bExpandDlg);
}

void CLoginDlg::SetDlgPos(BOOL bExpand)
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

	GetDlgItem(IDOK)->ShowWindow(!bExpand);
	SetDlgItemText(IDC_BTN_CONFIG_LOGINDLG,strText);
	MoveWindow(rcMain);
}


void CLoginDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CADOConnEx ADOConn;
	//�������ļ��ж�ȡ��ص���Ϣ
	
	if (ADOConn.GetConncetSqlStr().IsEmpty())
	{
		MessageBox(_T("����д��������ã�"),_T("��ܰ��ʾ"),MB_ICONINFORMATION);
	}
	else
	{
		//ִ�����ݲ���
		CString strUserID;
		CString strUserPwd;
		GetDlgItemText(IDC_EDIT_USERID_LOGINDLG,strUserID);
		GetDlgItemText(IDC_EDIT_USERPWD_LOGINDLG,strUserPwd);
		strUserID.Trim();
		strUserPwd.Trim();
		if (strUserID.IsEmpty())
		{
			MessageBox(_T("�˻�����Ϊ�գ�"),_T("��ܰ��ʾ"),MB_ICONWARNING);
			return;
		}

		if (strUserPwd.IsEmpty() && En_Login_User == m_nLoginType)
		{
			MessageBox(_T("���벻��Ϊ�գ�"),_T("��ܰ��ʾ"),MB_ICONWARNING);
			return;
		}

		//����ping����
// 		CString strIP = _T("");
// 		GetDlgItemText(IDC_IPADDRESS_LOGINDLG,strIP);
// 		int nPos = strIP.Find(',');
// 		if (nPos>-1)
// 		{
// 			strIP = strIP.Left(nPos);
// 		}
// 		theApp.m_clsMyNetwork.SetDesAdress(strIP);
// 		if (!theApp.m_clsMyNetwork.PingNet())
// 		{
// 			MessageBox(_T("��Ǹ�����������粻��ͨ��"),_T("��ܰ��ʾ"),MB_ICONERROR);
// 			return;
// 		}

		CString strSQL = _T("");
		CBase64Code Base64Code;
		switch(m_nLoginType)
		{
		case En_Login_User:
			{
				strSQL.Format(_T("select * from %s where %s='%s'and %s='%s'"),DB_TABLE_PERSON,DBPerson_key_UserID,strUserID,DBPerson_key_Pwd,Base64Code.base64Encode(strUserPwd));
			}
			break;
		case En_Login_Custom:
			{
				strSQL.Format(_T("select * from %s where %s='%s'and %s='%s'"),DB_TABLE_CUSTOM,DBCustomer_key_Code,strUserID,DBCustomer_key_Pwd,Base64Code.base64Encode(strUserPwd));
			}
			break;
		}
		
		auto Rret = ADOConn.GetRecordSet(strSQL);
		if (!ADOConn.adoEOF())//���ڴ��û���
		{
			if (En_Login_User == m_nLoginType)
			{
				int nOutFlag =  _ttoi(ADOConn.GetValueString(DBPerson_key_OutFlag));
				if (strUserID == _T("admin"))
				{
					nOutFlag = 0;
				}

				if (nOutFlag == 1)
				{
					MessageBox(_T("��Ǹ�����ѱ�ע����"),_T("��ܰ��ʾ"),MB_ICONWARNING);
					CDialogEx::OnCancel();
				}
				else
				{
					//д���������˻�������
					theApp.SetIniKeyValue(_T("ACT"),_T("USERID"),theApp.OnEncodeStr(strUserID),theApp.m_strMgnPath);
					theApp.SetIniKeyValue(_T("ACT"),_T("USERPWD"),theApp.OnEncodeStr(strUserPwd),theApp.m_strMgnPath);

					//MessageBox(_T("��ϲ���ɹ���½��"),_T("��ܰ��ʾ"),MB_ICONINFORMATION);
					CDialogEx::OnOK();
				}
			}
			else
			{
				//д���������˻�������
				theApp.SetIniKeyValue(_T("CUSACT"),_T("USERID"),theApp.OnEncodeStr(strUserID),theApp.m_strMgnPath);
				theApp.SetIniKeyValue(_T("CUSACT"),_T("USERPWD"),theApp.OnEncodeStr(strUserPwd),theApp.m_strMgnPath);

				//MessageBox(_T("��ϲ���ɹ���½��"),_T("��ܰ��ʾ"),MB_ICONINFORMATION);
				CDialogEx::OnOK();
			}
			
		}
		else
		{
			SetDlgItemText(IDC_EDIT_USERPWD_LOGINDLG,_T(""));
			MessageBox(_T("�˻����������"),_T("��ܰ��ʾ"),MB_ICONWARNING);
		}
	}
}


void CLoginDlg::OnBnClickedChkActLogindlg()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strFilePath = theApp.m_strMgnPath;
	if (BST_CHECKED == ((CButton *)GetDlgItem(IDC_CHK_ACT_LOGINDLG))->GetCheck())
	{
		theApp.SetIniKeyValue(_T("Setting"),_T("LG_CHK_ACT"),_T("TRUE"),strFilePath);
	}
	else
	{
		theApp.SetIniKeyValue(_T("Setting"),_T("LG_CHK_ACT"),_T("FALSE"),strFilePath);
	}
}


void CLoginDlg::OnBnClickedChkApplyLogindlg()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UINT nState = ((CButton *)GetDlgItem(IDC_CHK_APPLY_LOGINDLG))->GetCheck();
	if (BST_CHECKED == nState)
	{
		theApp.SetIniKeyValue(_T("Setting"),_T("LG_CHK_APPLY"),_T("TRUE"),theApp.m_strSvrPath);
		SetCtrState(FALSE);
	}
	else
	{
		theApp.SetIniKeyValue(_T("Setting"),_T("LG_CHK_APPLY"),_T("FALSE"),theApp.m_strSvrPath);
		SetCtrState(TRUE);
	}
}


void CLoginDlg::OnBnClickedBtnEmptyLogindlg()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(IDOK == MessageBox(_T("ȷ�����������"),_T("��ܰ��ʾ��"),MB_ICONQUESTION|MB_OKCANCEL))
	{
		CString strIPport = _T("");
		CString strDBName = _T("");
		CString strDBAccount = _T("");
		CString strDBPwd = _T("");
		CString strFilePort = _T("");
		CString strDBPath = _T("");
      CString strFtpIP = _T("");
		CString strFilePath = theApp.m_strSvrPath;//���������ļ�·��

		theApp.SetIniKeyValue(_T("SQLSVR"),_T("SVR"),strIPport,strFilePath);
		theApp.SetIniKeyValue(_T("SQLSVR"),_T("DB"),strDBName,strFilePath);
		theApp.SetIniKeyValue(_T("SQLSVR"),_T("UID"),strDBAccount,strFilePath);
		theApp.SetIniKeyValue(_T("SQLSVR"),_T("PWD"),strDBPwd,strFilePath);
		theApp.SetIniKeyValue(_T("SQLSVR"),_T("FILEPORT"),strDBPwd,strFilePath);
		theApp.SetIniKeyValue(_T("SQLSVR"),_T("LOCAL_DB_PATH"),strDBPath,strFilePath);
      theApp.SetIniKeyValue(_T("SQLSVR"),_T("SVRLOCAL"),strFtpIP,strFilePath);
      theApp.SetIniKeyValue(_T("SQLSVR"),_T("HTTPMODE"), _T("FALSE"),strFilePath);
		SetDlgItemText(IDC_IPADDRESS_LOGINDLG,strIPport);
		SetDlgItemText(IDC_EDIT_PORT_LOGINDLG,strIPport);
		SetDlgItemText(IDC_EDIT_DBNAME_LOGINDLG,strDBName);
		SetDlgItemText(IDC_EDIT_DBACT_LOGINDLG,strDBAccount);
		SetDlgItemText(IDC_EDIT_DBPWD_LOGINDLG,strDBPwd);
		SetDlgItemText(IDC_EDIT_PORT_FILE,strFilePort);
		SetDlgItemText(IDC_MFCEDIT_DBPATH,strDBPath);
      SetDlgItemText(IDC_EDT_FTP_ADDRESS,strFtpIP);

      auto pRadio = (CButton *)GetDlgItem(IDC_RADIO_MODE_FTP);
      pRadio->SetCheck(1);
      pRadio = (CButton *)GetDlgItem(IDC_RADIO_MODE_HTTP);
      pRadio->SetCheck(0);
	}
}


void CLoginDlg::OnBnClickedBtnDbsaveLogindlg()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strIPport = _T("");
	CString strDBName;
	CString strDBAccount;
	CString strDBPwd;
	CString strIP;
	CString strPort;
	CString strFilePort = _T("");
	CString strDBPath = _T("");
   CString strFtpIP = _T("");

	GetDlgItemText(IDC_IPADDRESS_LOGINDLG,strIP);
	GetDlgItemText(IDC_EDIT_PORT_LOGINDLG,strPort);
	GetDlgItemText(IDC_EDIT_DBNAME_LOGINDLG,strDBName);
	GetDlgItemText(IDC_EDIT_DBACT_LOGINDLG,strDBAccount);
	GetDlgItemText(IDC_EDIT_DBPWD_LOGINDLG,strDBPwd);
	GetDlgItemText(IDC_EDIT_PORT_FILE,strFilePort);
	GetDlgItemText(IDC_MFCEDIT_DBPATH,strDBPath);
   GetDlgItemText(IDC_EDT_FTP_ADDRESS,strFtpIP);

   auto pFtpRadio = (CButton *)GetDlgItem(IDC_RADIO_MODE_FTP);
   BOOL bHttpMode = pFtpRadio->GetCheck();

   strFtpIP.Trim();
	strIP.Trim();
	strPort.Trim();
	strIPport = strIP;
	if (!strPort.IsEmpty())
	{
		strIPport += _T(",");
		strIPport += strPort;
	}

	CString strFilePath = theApp.m_strSvrPath;//���������ļ�·��

	theApp.SetIniKeyValue(_T("SQLSVR"),_T("SVR"),theApp.OnEncodeStr(strIPport,WORD_PWD_KEY),strFilePath);
	theApp.SetIniKeyValue(_T("SQLSVR"),_T("UID"),theApp.OnEncodeStr(strDBAccount,WORD_PWD_KEY),strFilePath);
	theApp.SetIniKeyValue(_T("SQLSVR"),_T("PWD"),theApp.OnEncodeStr(strDBPwd,WORD_PWD_KEY),strFilePath);
   theApp.SetIniKeyValue(_T("SQLSVR"),_T("FILEPORT"),theApp.OnEncodeStr(strFilePort,WORD_PWD_KEY),strFilePath);
	theApp.SetIniKeyValue(_T("SQLSVR"),_T("DB"),theApp.OnEncodeStr(strDBName,WORD_PWD_KEY),strFilePath);
   theApp.SetIniKeyValue(_T("SQLSVR"),_T("SVRLOCAL"),strFtpIP,strFilePath);

   theApp.SetIniKeyValue(_T("SQLSVR"),_T("HTTPMODE"),!bHttpMode ? _T("TRUE") : _T("FALSE"),strFilePath);


	m_bExpandDlg = FALSE;
	SetDlgPos(m_bExpandDlg);

	//MessageBox(_T("���ñ���ɹ�"),_T("��ܰ��ʾ��"),MB_ICONINFORMATION);
	OnBnClickedOk();
}

LRESULT CLoginDlg::OnAdoconnMsg(WPARAM wParam, LPARAM lParam)
{
#ifdef _UNICODE
   CString strTip((LPCTSTR)lParam);
#else
   CString strTip((char *)lParam);
#endif

	MessageBox(strTip,_T("��ܰ��ʾ"),MB_OK);

	return 0;
}


BOOL CLoginDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN)//ȷ��
		{
			if (m_bExpandDlg)
			{
				OnBnClickedBtnDbsaveLogindlg();
			}
			else
			{
				OnBnClickedOk();
			}
			return TRUE;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
