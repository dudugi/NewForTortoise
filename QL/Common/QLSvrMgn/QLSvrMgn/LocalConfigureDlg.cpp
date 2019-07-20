// LocalConfigureDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "QLSvrMgn.h"
#include "LocalConfigureDlg.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "MyADOConnEx.h"


// CLocalConfigureDlg 对话框

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


// CLocalConfigureDlg 消息处理程序


void CLocalConfigureDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(m_strDatabaseAccount.IsEmpty() || m_strDatabaseName.IsEmpty() || m_strDatabasePassword.IsEmpty() || m_strIP.IsEmpty())
	{
		AfxMessageBox(_T("信息不完整,请重新填写!"));
		return;
	}

   CMyADOConnEx ADOConnEx;
   if (BST_CHECKED == ((CButton *)(GetDlgItem(IDC_CHK_STEUPDB)))->GetCheck())
   {
      if(!ADOConnEx.CreateConnectSql(m_strIP,_T("master"),m_strDatabaseAccount,m_strDatabasePassword))
      {
         AfxMessageBox(_T("信息错误!"));
         return;
      }
   }
   else
   {
      if(!ADOConnEx.CreateConnectSql(m_strIP,m_strDatabaseName,m_strDatabaseAccount,m_strDatabasePassword))
      {
         AfxMessageBox(_T("信息错误!"));
         return;
      }
   }   

   if(theApp.GetStateConnectDB(&ADOConnEx))
   {
      theApp.OnShowDesktopAlert(_T("连接数据库成功"),COLOR_TIP_SUC);

      theApp.OnWriteIni(_T("ConfigureInfo"), _T("DatabaseIP"), m_strIP,INI_SQLSVR);
      theApp.OnWriteIni(_T("ConfigureInfo"), _T("DatabaseName"), m_strDatabaseName,INI_SQLSVR);
      theApp.OnWriteIni(_T("ConfigureInfo"), _T("DatabaseAccount"), m_strDatabaseAccount,INI_SQLSVR);
      theApp.OnWriteIni(_T("ConfigureInfo"), _T("DatabasePassword"), m_strDatabasePassword,INI_SQLSVR);

      CMainFrame *pMainFrame = (CMainFrame *)AfxGetMainWnd();
      if (pMainFrame)
      {
         CString strStatusBar = _T("");
         strStatusBar.Format(_T("当前数据库：%s"),m_strDatabaseName);
         pMainFrame->SetStatusBarPane(1,strStatusBar);
      }


      CDialogEx::OnOK();
   }
   else
   {
      theApp.OnShowDesktopAlert(_T("无法链接到数据库"),COLOR_TIP_FAIL);
   }
}


BOOL CLocalConfigureDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CString strSvr=_T("127.0.0.1,1433"),strDB=_T("QLPLM"),strUID=_T(""),strPWD=_T("");
	CString strFilePath = theApp.m_strAppPath +_T("\\SQLSVR.ini");//设置配置文件路径

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
	// 异常: OCX 属性页应返回 FALSE
}