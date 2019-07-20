// DlgPane2Item1.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "QLSvrMgn.h"
#include "DlgPane2Item1.h"
#include "MyADOConnEx.h"


// CDlgPane2Item1 �Ի���

IMPLEMENT_DYNAMIC(CDlgPane2Item1, CTabDialog)

CDlgPane2Item1::CDlgPane2Item1(CWnd* pParent /*=NULL*/)
	: CTabDialog(CDlgPane2Item1::IDD, pParent)
{
	/*m_strDatabase = _T("");*/
}

CDlgPane2Item1::~CDlgPane2Item1()
{
}

void CDlgPane2Item1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DIR_LIST, m_listBox);
}


BEGIN_MESSAGE_MAP(CDlgPane2Item1, CTabDialog)
	ON_BN_CLICKED(IDC_INSTALL_DATABASE_BUTTON, &CDlgPane2Item1::OnBnClickedInstallDatabaseButton)
	ON_BN_CLICKED(IDC_BTN_INSTALL, &CDlgPane2Item1::OnBnClickedBtnInstall)
END_MESSAGE_MAP()


// CDlgPane2Item1 ��Ϣ�������

void CDlgPane2Item1::OnBnClickedInstallDatabaseButton()
{
	CString strDefPath = _T("");
	GetDlgItemText(IDC_INSTALL_DATABASE_EDIT, strDefPath);

	CString strNewPath = _T("");
	if (m_CDirectroy.OpenDirectory(strNewPath,strDefPath))
	{
		SetDlgItemText(IDC_INSTALL_DATABASE_EDIT, strNewPath);
		theApp.OnWriteIni(_T("InstallDatabasePathInfo"), _T("InstallDatabasePath"), strNewPath,INI_SQLSVR);

		RefreshFileList(strNewPath);
	}
}

void CDlgPane2Item1::RefreshFileList(CString strDirPath)
{
	if(!strDirPath.IsEmpty())
	{	
		theApp.GetFileNameByRoot(&m_strList, strDirPath);
		int nCount = m_strList.GetCount();
		m_listBox.ResetContent();
		for(int nIndex=0; nIndex<nCount; nIndex++)
		{
			CString strListFile = m_strList.GetAt(m_strList.FindIndex(nIndex));
			if(theApp.FilterPathToFileName(strListFile,_T("sql")))
			{
				m_listBox.AddString(strListFile);
			}
		}
	}	
}

BOOL CDlgPane2Item1::OnInitDialog()
{
	CTabDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CString strDirPath = _T("");
	theApp.OnReadIni(_T("InstallDatabasePathInfo"), _T("InstallDatabasePath"), strDirPath,INI_SQLSVR);
	SetDlgItemText(IDC_INSTALL_DATABASE_EDIT, strDirPath);
	RefreshFileList(strDirPath);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDlgPane2Item1::OnBnClickedBtnInstall()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strDirPath = _T("");
	GetDlgItemText(IDC_INSTALL_DATABASE_EDIT, strDirPath);
	if(strDirPath.IsEmpty() || !PathFileExists(strDirPath))
	{
		theApp.OnShowDesktopAlert(_T("��ѡ����Ч·��!"),COLOR_TIP_WARN,2,AfxGetMainWnd());
	}
	else
	{
      if (!theApp.GetStateConnectDB(TRUE))
      {
         theApp.OnShowDesktopAlert(_T("�޷����ӵ����ݿ�"),COLOR_TIP_WARN,2,AfxGetMainWnd());
         return;
      }

		if(IDCANCEL == MessageBox(_T("ȷ������װ���ݿ⡿��"),_T("��ʾ"),MB_OKCANCEL|MB_ICONQUESTION))
		{
			return;
		}

		BOOL bRet = TRUE;
		theApp.ShowLoading();
		theApp.GetFileNameByRoot(&m_strList, strDirPath);
		int nCount = m_strList.GetCount();
		int nIndex = 0;
		CString strListFile = _T("");
		for(nIndex=0; nIndex<nCount; nIndex++)
		{
			strListFile = m_strList.GetAt(m_strList.FindIndex(nIndex));
			if(0 == nIndex)
			{
				bRet = CreateDatabase();
				if(!bRet)
				{
					theApp.OnShowDesktopAlert(_T("���ݿ��Ѵ���!"),COLOR_TIP_SUC,2,AfxGetMainWnd());
					break;
				}
			}
			else if(1 == nIndex)
			{
				bRet = CreateTablesFromFile(strListFile);
				if(!bRet)
				{
					theApp.OnShowDesktopAlert(_T("��װ���ݿ�ʧ��!"),COLOR_TIP_FAIL,2,AfxGetMainWnd());
					break;
				}
			}
			else if(2 == nIndex)
			{
				bRet = CreateTablesFromFile(strListFile);
				if(!bRet)
				{
					theApp.OnShowDesktopAlert(_T("��ʼ�����ݿ�Ĭ������ʧ��!"),COLOR_TIP_FAIL,2,AfxGetMainWnd());
					break;
				}
				else
				{
					theApp.OnShowDesktopAlert(_T("��ʼ�����ݿ�Ĭ�����ݳɹ�!"),COLOR_TIP_SUC,2,AfxGetMainWnd());
					break;
				}
			}
		}
		theApp.CloseLoading();
	}
	
}

BOOL CDlgPane2Item1::CreateDatabase()
{
	CMyADOConnEx myADOConnEx(FALSE);
	CString strSQL = _T("");
	CString strDatabase = _T("");
	theApp.OnReadIni(_T("ConfigureInfo"), _T("DatabaseName"), strDatabase,INI_SQLSVR);
	strSQL.Format(_T("create database [%s]"), strDatabase);
	BOOL bRet = TRUE;
 	bRet = myADOConnEx.ExecuteSQL(strSQL);
	return bRet;
}

BOOL CDlgPane2Item1::CreateTablesFromFile(CString strFilePath)
{
	BOOL bRet = m_FileTxt.ReadFile(strFilePath);
	if(!bRet)
		return bRet;
	CString strTableCreate = _T("");
	auto it = m_FileTxt.m_vecCString.begin();
	while(it != m_FileTxt.m_vecCString.end())
	{
		strTableCreate += *(it) + _T("\r\n");
		it++;
	}
	strTableCreate.Replace(_T("GO"), _T(""));
	CMyADOConnEx mMyADOConnEx;
	bRet = mMyADOConnEx.ExecuteSQL(strTableCreate);
	return bRet;
}