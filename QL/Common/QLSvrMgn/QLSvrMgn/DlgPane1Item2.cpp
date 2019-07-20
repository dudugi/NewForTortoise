// DlgPane1Item2.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "QLSvrMgn.h"
#include "DlgPane1Item2.h"

// CDlgPane1Item2 �Ի���

IMPLEMENT_DYNAMIC(CDlgPane1Item2, CTabDialog)

CDlgPane1Item2::CDlgPane1Item2(CWnd* pParent /*=NULL*/)
	: CTabDialog(CDlgPane1Item2::IDD, pParent)
   , m_RadGroup(FALSE)
{
	m_pADOConn = new CMyADOConnEx(TRUE);
/*	m_strDatabase = _T("");*/
	m_FileName = _T("");
	m_strList.RemoveAll();
}

CDlgPane1Item2::~CDlgPane1Item2()
{
 	if(nullptr != m_pADOConn)
 	{
 		delete m_pADOConn;
 		m_pADOConn = nullptr;
 	}
}

void CDlgPane1Item2::DoDataExchange(CDataExchange* pDX)
{
   CDialogEx::DoDataExchange(pDX);
   DDX_Control(pDX, IDC_DIR_LIST, m_listBox);
   DDX_Radio(pDX, IDC_RADIO1, m_RadGroup);
   DDX_Control(pDX, IDC_DIR_LIST2, m_listBox2);
}


BEGIN_MESSAGE_MAP(CDlgPane1Item2, CTabDialog)
	ON_BN_CLICKED(IDC_RESTORE_BUTTON, &CDlgPane1Item2::OnBnClickedRestoreButton)
	ON_BN_CLICKED(IDC_NEW_PATH_BUTTON, &CDlgPane1Item2::OnBnClickedNewPathButton)
	ON_BN_CLICKED(IDC_BUTTON_RESTORE, &CDlgPane1Item2::OnBnClickedButtonRestore)
   ON_BN_CLICKED(IDC_RADIO1, &CDlgPane1Item2::OnBnClickedRadio1)
   ON_BN_CLICKED(IDC_RADIO2, &CDlgPane1Item2::OnBnClickedRadio1)
END_MESSAGE_MAP()


// CDlgPane1Item2 ��Ϣ�������


void CDlgPane1Item2::OnBnClickedRestoreButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strDefPath = _T("");
	GetDlgItemText(IDC_RESTORE_EDIT, strDefPath);

	CString strNewPath = _T("");
	if (m_CDirectroy.OpenDirectory(strNewPath,strDefPath))
	{
		SetDlgItemText(IDC_RESTORE_EDIT, strNewPath);
		theApp.OnWriteIni(_T("RestorePathInfo"), _T("OldPath"), strNewPath,INI_SQLSVR);

		ShowFileListBox(strNewPath);
	}
}

void CDlgPane1Item2::ShowFileListBox(CString strDirPath)
{
	CString strListFile = _T("");
	if(strDirPath.IsEmpty())
	{
		return;
	}
	theApp.GetFileNameByRoot(&m_strList, strDirPath);
	int nCount = m_strList.GetCount();
	int nIndex = 0;
	m_listBox.ResetContent();
	for(nIndex=0; nIndex<nCount; nIndex++)
	{
		strListFile = m_strList.GetAt(m_strList.FindIndex(nIndex));
		if(theApp.FilterPathToFileName(strListFile))
		{
			m_listBox.AddString(strListFile);
		}
	}
	m_listBox.SetCurSel(0);
}


void CDlgPane1Item2::OnBnClickedNewPathButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strDefPath = _T("");
	GetDlgItemText(IDC_NEW_PATH_EDIT, strDefPath);

	CString strNewPath = _T("");
	if (m_CDirectroy.OpenDirectory(strNewPath,strDefPath))
	{
		CString strChildDir = _T("������");
		int nLen = strChildDir.GetLength();
		if (strNewPath.GetLength()>nLen && strNewPath.Right(nLen)==strChildDir)
		{
			SetDlgItemText(IDC_NEW_PATH_EDIT, strNewPath);
			theApp.OnWriteIni(_T("RestorePathInfo"), _T("NewPath"), strNewPath,INI_SQLSVR);
		}
		else
		{
			theApp.OnShowDesktopAlert(_T("����ָ�����������⡿��"),COLOR_TIP_WARN,2);
		}
	}
}


BOOL CDlgPane1Item2::OnInitDialog()
{
	CTabDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CString strNewPath = _T(""), strOldPath = _T("");

   m_listBox.ResetContent();
   m_listBox2.ResetContent();

   //��ʼ����������
   for (int i = 0;i<theApp.m_TaskSuccessList.GetCount();i++)
   {
      CString strFile;
      CDBTaskInfo *DBTask = (CDBTaskInfo *)theApp.m_TaskSuccessList.GetAt(theApp.m_TaskSuccessList.FindIndex(i));
      if (DBTask->m_bAutoBackUp)
      {
         strFile = DBTask->m_tNextStartTime.Format(_T("%Y-%m-%d %H:%M:%S"));
         m_listBox.AddString(strFile);
         if (DBTask->m_bFileBackup)
         {
            strFile = DBTask->m_tNextStartTime.Format(_T("%Y-%m-%d %H:%M:%S"));
            m_listBox2.AddString(strFile);
         }
      }
   }
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

BOOL CDlgPane1Item2::RestoreDatabase(const CString &  strDirectory,const CString &  strXDirectory,int nType)
{
	BOOL bRet = TRUE;
	CString strSQL = _T("");
	CString strDatabase = _T("");
	theApp.OnReadIni(_T("ConfigureInfo"), _T("DatabaseName"), strDatabase,INI_SQLSVR);
	strSQL.Format(_T("use [%s]"), strDatabase);
   
      if(m_pADOConn->ExecuteSQL(strSQL))
      {
         strSQL.Format(_T("use master \
                          ALTER DATABASE [%s] SET OFFLINE WITH ROLLBACK IMMEDIATE \
                          restore database [%s] from disk='%s' \
                          with replace \
                          ALTER database [%s] set online "),strDatabase, strDatabase, strDirectory, strDatabase); 
          if(!nType)
          {
             strSQL.Format(_T("use master \
                             ALTER DATABASE [%s] SET OFFLINE WITH ROLLBACK IMMEDIATE \
                             restore database [%s] from disk='%s' \
                             with  replace,NORECOVERY\
                             restore database [%s] from disk='%s' \
                             ALTER database [%s] set online "),strDatabase, strDatabase, strDirectory,strDatabase,strXDirectory, strDatabase); 
          }
      }
      else
      {
         strSQL.Format(_T("use master \
                          restore database [%s] from disk = '%s'"), strDatabase, strDirectory);
         if(!nType)
         {
            strSQL.Format(_T("use master \
                             restore database [%s] from disk='%s' \
                             with  replace,NORECOVERY\
                             restore database [%s] from disk='%s' \
                              "),strDatabase, strDirectory,strDatabase,strXDirectory); 
         }
      }
  

	if(m_pADOConn->ExecuteSQL(strSQL))
	{
		bRet = TRUE;
	}
	else
	{
		bRet = FALSE;
	}
	return bRet;
}

BOOL CDlgPane1Item2::RestoreXDatabase(const CString &  strDirectory)
{
   BOOL bRet = TRUE;
   CString strSQL = _T("");
   CString strDatabase = _T("");
   theApp.OnReadIni(_T("ConfigureInfo"), _T("DatabaseName"), strDatabase,INI_SQLSVR);
   strSQL.Format(_T("use [%s]"), strDatabase);

   if(m_pADOConn->ExecuteSQL(strSQL))
   {
      strSQL.Format(_T("use master \
                       ALTER DATABASE [%s] SET OFFLINE WITH ROLLBACK IMMEDIATE \
                       restore database [%s] from disk='%s' \
                       with RECOVERY \
                       ALTER database [%s] set online "),strDatabase, strDatabase, strDirectory, strDatabase); 
   }
   else
   {
      strSQL.Format(_T("use master \
                       restore database [%s] from disk = '%s'with RECOVERY"), strDatabase, strDirectory);
   }

   // RESTORE DATABASE dbname FROM DISK='c:\MyDB_diff_bak_081218.bak' WITH RECOVERY

   if(m_pADOConn->ExecuteSQL(strSQL))
   {
      bRet = TRUE;
   }
   else
   {
      bRet = FALSE;
   }
   return bRet;
}



void CDlgPane1Item2::OnBnClickedButtonRestore()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
     PTLOG("��ʼ��ԭ\n");
   if (theApp.m_bTaskMark)
   {
      theApp.OnShowDesktopAlert(_T("��ǰ�б�����������ִ��,���Ժ�ԭ!"),COLOR_TIP_SUC,2,AfxGetMainWnd());
      PTLOG("��ԭʧ��\n");
      return;
   }
   CString strDirPath,strNewPath;
   int nCurSel = m_listBox.GetCurSel(); //��ȡ��ǰ������bak�ļ�
   m_listBox.GetText(nCurSel, m_FileName);
   if (!m_FileName.IsEmpty())
   {
     for (int i =0;i<theApp.m_TaskSuccessList.GetCount();i++)
     {
         CDBTaskInfo *DBTask = (CDBTaskInfo *)theApp.m_TaskSuccessList.GetAt(theApp.m_TaskSuccessList.FindIndex(i));
         if (DBTask)
         {
            COleVariant vtime1(m_FileName);
            vtime1.ChangeType(VT_DATE);
            COleDateTime time1=vtime1;
            SYSTEMTIME systime1;
            VariantTimeToSystemTime(time1, &systime1);
            CTime tm1(systime1);   //CString=======>CTime

            if (DBTask->m_tNextStartTime == tm1)
            {
               CString DirName;
               strDirPath = DBTask->m_strNewDirPath;
               strNewPath = DBTask->m_strOldPath;
               if (m_RadGroup)
               {
                  DirName = DBTask->m_tNextStartTime.Format(_T("%Y_%m_%d_%Hʱ%M��"));
                  strDirPath = strDirPath+_T("\\")+ DBTask->m_strID + _T("\\")+ _T("XBackUp") + _T("\\")+DirName;
               }
               else
               {
                  DirName = DBTask->m_tNextStartTime.Format(_T("%Y_%m_%d_%Hʱ%M��"));
                  strDirPath = strDirPath+_T("\\")+ DBTask->m_strID + _T("\\")+ _T("FullBackUp") + _T("\\")+DirName;
               }
               if (!theApp.GetStateConnectDB(m_pADOConn))
               {
                  m_pADOConn->InitConnect();
                  return;
               }

               if(IDOK == MessageBox(_T("ȷ������ԭ������PDM���������"),_T("��ʾ"),MB_OKCANCEL|MB_ICONQUESTION))
               {
                  //У�����ݿ�

                  //�������ݿ�
				  CString strFullBackname = theApp.m_TaskSuccessList.GetPathByLastExceTimeAndIDAnd(DBTask->m_strID,DBTask->m_tLastExecutionTime,TRUE);
                  CString strFilePath = strFullBackname + _T("\\") + _T("backup.bak");
                  theApp.ShowLoading();
                  if (m_RadGroup)
                  {   
					strFullBackname = strFullBackname+_T("\\") + _T("backup.bak");
					//ȷ�������ļ�Ŀ¼������ʹ��
                     CString strXBackDir=strDirPath + _T("\\") + _T("Xbackup.bak");
                     CString strFullBack = strFullBackname;
					 //������ȥ���Σ�û�����α���
					 if (theApp.FindBackupFile(strFilePath))
					 {
						 strFullBack = strFilePath+ _T("\\") + _T("backup.bak");
					 }

                     BOOL bFlag = RestoreDatabase(strFullBack,strXBackDir,0); //��ԭbak�ļ�
                     if (bFlag)
                     { 
                            if (DBTask->m_bFileBackup)
                            {
                               strDirPath = strDirPath + _T("\\������");
							   //�Ƿ���Ի�ԭ�ɹ�
                                  BOOL bRet = m_CDirectroy.CopyDirFileAPI(strDirPath, strNewPath);
                                  if(bRet)
                                  {
                                     theApp.OnShowDesktopAlert(_T("��ԭ�ɹ�!"),COLOR_TIP_SUC,2,AfxGetMainWnd());
                                     PTLOG("�ļ���ԭ�ɹ�\n");
                                  }
                                  else
                                  {
                                     theApp.OnShowDesktopAlert(_T("��ԭĿ¼�ļ�ʧ��!"),COLOR_TIP_FAIL,2,AfxGetMainWnd());
                                       PTLOG("��ԭĿ¼�ļ�ʧ��\n");
                                  }

                            }
                            else
                            {
                               theApp.OnShowDesktopAlert(_T("��ԭ�ɹ�!"),COLOR_TIP_SUC,2,AfxGetMainWnd());
                            }
                          PTLOG("���ݿ⻹ԭ�ɹ�\n");
                     }
                     else
                     {
                        theApp.OnShowDesktopAlert(_T("��ԭʧ��!"),COLOR_TIP_SUC,2,AfxGetMainWnd());
                         PTLOG("��ԭĿ¼�ļ�ʧ��\n");
                         PTLOG("��ԭ���ݿ�ʧ��\n");
                     }
                  }
                  else
                  {
                     BOOL bFlag = RestoreDatabase(strFilePath,_T(""),1); //��ԭbak�ļ�
                     if(bFlag)
                     {
                        
                         PTLOG("��ԭ���ݿ�ɹ�\n");
                        strDirPath = strDirPath + _T("\\������");
                        if(PathFileExists(strNewPath)&&DBTask->m_bFileBackup)
                        {
                           BOOL bRet = m_CDirectroy.CopyDirFileAPI(strDirPath, strNewPath);
                           if(bRet)
                           {
                              theApp.OnShowDesktopAlert(_T("��ԭ�ɹ�!"),COLOR_TIP_SUC,2,AfxGetMainWnd());

                               PTLOG("��ԭ�ļ��ɹ�\n");
                           }
                           else
                           {
                              theApp.OnShowDesktopAlert(_T("��ԭĿ¼�ļ�ʧ��!"),COLOR_TIP_FAIL,2,AfxGetMainWnd());
                               PTLOG("��ԭĿ¼�ļ�ʧ��\n");
                           }
                        }
                        else
                        {
                           theApp.OnShowDesktopAlert(_T("ԴĿ¼��������Ŀ¼�������⡿!"),COLOR_TIP_WARN,2,AfxGetMainWnd());
                            PTLOG("ԴĿ¼��������Ŀ¼�������⡿\n");
                        }
                     }
                     else
                     {
                        theApp.OnShowDesktopAlert(_T("��ԭ���ݿ�����ʧ��!"),COLOR_TIP_FAIL,2,AfxGetMainWnd());
                        PTLOG("��ԭ���ݿ�����ʧ��\n");
                     }
                  }
                  
                   PTLOG("��ԭ����\n");
                   theApp.m_pADOConn->InitConnect();
                  theApp.CloseLoading();
                  break;
               }
            }
            }
         }
     }

}




void CDlgPane1Item2::OnBnClickedRadio1()
{
   // TODO: �ڴ���ӿؼ�֪ͨ����������
    UpdateData(TRUE);
   switch(m_RadGroup)
   {
   case  0:
      {
         //ˢ�»�ԭ���ݿ⣨���ر��ݳɹ��ģ�list�Ͷ����ļ�list
         m_listBox2.ResetContent();
         m_listBox.ResetContent();
         for (int i = 0;i<theApp.m_TaskSuccessList.GetCount();i++)
         {
            CString strFile;
            CDBTaskInfo *DBTask = (CDBTaskInfo *)theApp.m_TaskSuccessList.GetAt(theApp.m_TaskSuccessList.FindIndex(i));
            if (DBTask->m_bAutoBackUp)
            {
               strFile = DBTask->m_tNextStartTime.Format(_T("%Y-%m-%d %H:%M:%S"));
               m_listBox.AddString(strFile);
               if (DBTask->m_bFileBackup)
               {
                  strFile = DBTask->m_tNextStartTime.Format(_T("%Y-%m-%d %H:%M:%S"));
                  m_listBox2.AddString(strFile);
				  
               }
            }
         }
         break;
      }
   case 1:
      {
         m_listBox2.ResetContent();
         m_listBox.ResetContent();
         for (int i = 0;i<theApp.m_TaskSuccessList.GetCount();i++)
         {
            CString strFile;
            CDBTaskInfo *DBTask = (CDBTaskInfo *)theApp.m_TaskSuccessList.GetAt(theApp.m_TaskSuccessList.FindIndex(i));
            if (!DBTask->m_bAutoBackUp)
            {
               strFile = DBTask->m_tNextStartTime.Format(_T("%Y-%m-%d %H:%M:%S"));
               m_listBox.AddString(strFile);
            }
            if (DBTask->m_bFileBackup)
            {
               strFile = DBTask->m_tNextStartTime.Format(_T("%Y-%m-%d %H:%M:%S"));
               m_listBox2.AddString(strFile);
            }
         }
         break;
      }
   default:
      break;
   }
}

