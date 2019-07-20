// LocalConfigureDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "QLSvrMgn.h"
#include "LocalConfigureDlg.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "MyADOConnEx.h"


// CLocalConfigureDlg �Ի���

IMPLEMENT_DYNAMIC(CLocalConfigureDlg, CDialogEx)

CLocalConfigureDlg::CLocalConfigureDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLocalConfigureDlg::IDD, pParent)
	, m_strIP(_T(""))
	, m_strDatabaseName(_T(""))
	, m_strDatabaseAccount(_T(""))
	, m_strDatabasePassword(_T(""))
{

}

CLocalConfigureDlg::~CLocalConfigureDlg()
{
}

void CLocalConfigureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_IP, m_strIP);
	DDX_Text(pDX, IDC_EDIT_DATABASE_NAME, m_strDatabaseName);
	DDX_Text(pDX, IDC_EDIT_DATABASE_ACCOUNT, m_strDatabaseAccount);
	DDX_Text(pDX, IDC_EDIT_DATABASE_PASSWORD, m_strDatabasePassword);
}


BEGIN_MESSAGE_MAP(CLocalConfigureDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CLocalConfigureDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CLocalConfigureDlg ��Ϣ�������


void CLocalConfigureDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(m_strDatabaseAccount.IsEmpty() || m_strDatabaseName.IsEmpty() || m_strDatabasePassword.IsEmpty() || m_strIP.IsEmpty())
	{
		AfxMessageBox(_T("��Ϣ������,��������д!"));
		return;
	}

   CMyADOConnEx ADOConnEx;
   if (BST_CHECKED == ((CButton *)(GetDlgItem(IDC_CHK_STEUPDB)))->GetCheck())
   {
      if(!ADOConnEx.CreateConnectSql(m_strIP,_T("master"),m_strDatabaseAccount,m_strDatabasePassword))
      {
         AfxMessageBox(_T("��Ϣ����!"));
         return;
      }
   }
   else
   {
      if(!ADOConnEx.CreateConnectSql(m_strIP,m_strDatabaseName,m_strDatabaseAccount,m_strDatabasePassword))
      {
         AfxMessageBox(_T("��Ϣ����!"));
         return;
      }
   }   

   if(theApp.GetStateConnectDB(&ADOConnEx))
   {
      theApp.OnShowDesktopAlert(_T("�������ݿ�ɹ�"),COLOR_TIP_SUC);

      theApp.OnWriteIni(_T("ConfigureInfo"), _T("DatabaseIP"), m_strIP,INI_SQLSVR);
      theApp.OnWriteIni(_T("ConfigureInfo"), _T("DatabaseName"), m_strDatabaseName,INI_SQLSVR);
      theApp.OnWriteIni(_T("ConfigureInfo"), _T("DatabaseAccount"), m_strDatabaseAccount,INI_SQLSVR);
      theApp.OnWriteIni(_T("ConfigureInfo"), _T("DatabasePassword"), m_strDatabasePassword,INI_SQLSVR);

      CMainFrame *pMainFrame = (CMainFrame *)AfxGetMainWnd();
      if (pMainFrame)
      {
         CString strStatusBar = _T("");
         strStatusBar.Format(_T("��ǰ���ݿ⣺%s"),m_strDatabaseName);
         pMainFrame->SetStatusBarPane(1,strStatusBar);
      }


      CDialogEx::OnOK();
   }
   else
   {
      theApp.OnShowDesktopAlert(_T("�޷����ӵ����ݿ�"),COLOR_TIP_FAIL);
   }
}


BOOL CLocalConfigureDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CString strSvr=_T("127.0.0.1,1433"),strDB=_T("QLPLM"),strUID=_T(""),strPWD=_T("");
	CString strFilePath = theApp.m_strAppPath +_T("\\SQLSVR.ini");//���������ļ�·��

	if(PathFileExists(strFilePath))
	{
		theApp.OnReadIni(_T("ConfigureInfo"), _T("DatabaseIP"), strSvr,INI_SQLSVR);
		theApp.OnReadIni(_T("ConfigureInfo"), _T("DatabaseName"), strDB,INI_SQLSVR);
		theApp.OnReadIni(_T("ConfigureInfo"), _T("DatabaseAccount"), strUID,INI_SQLSVR);
		theApp.OnReadIni(_T("ConfigureInfo"), _T("DatabasePassword"), strPWD,INI_SQLSVR);
	}

	SetDlgItemText(IDC_EDIT_IP, strSvr);
	SetDlgItemText(IDC_EDIT_DATABASE_NAME, strDB);
	SetDlgItemText(IDC_EDIT_DATABASE_ACCOUNT, strUID);
	SetDlgItemText(IDC_EDIT_DATABASE_PASSWORD, strPWD);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}