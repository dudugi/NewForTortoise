// DlgPane1Item2.cpp : 实现文件
//

#include "stdafx.h"
#include "QLSvrMgn.h"
#include "DlgPane1Item2.h"

// CDlgPane1Item2 对话框

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


// CDlgPane1Item2 消息处理程序


void CDlgPane1Item2::OnBnClickedRestoreButton()
{
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
	CString strDefPath = _T("");
	GetDlgItemText(IDC_NEW_PATH_EDIT, strDefPath);

	CString strNewPath = _T("");
	if (m_CDirectroy.OpenDirectory(strNewPath,strDefPath))
	{
		CString strChildDir = _T("订单库");
		int nLen = strChildDir.GetLength();
		if (strNewPath.GetLength()>nLen && strNewPath.Right(nLen)==strChildDir)
		{
			SetDlgItemText(IDC_NEW_PATH_EDIT, strNewPath);
			theApp.OnWriteIni(_T("RestorePathInfo"), _T("NewPath"), strNewPath,INI_SQLSVR);
		}
		else
		{
			theApp.OnShowDesktopAlert(_T("必须指定到【订单库】！"),COLOR_TIP_WARN,2);
		}
	}
}


BOOL CDlgPane1Item2::OnInitDialog()
{
	CTabDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CString strNewPath = _T(""), strOldPath = _T("");

   m_listBox.ResetContent();
   m_listBox2.ResetContent();

   //初始化整体数据
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
	// 异常: OCX 属性页应返回 FALSE
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
	// TODO: 在此添加控件通知处理程序代码
     PTLOG("开始还原\n");
   if (theApp.m_bTaskMark)
   {
      theApp.OnShowDesktopAlert(_T("当前有备份任务正在执行,请稍后还原!"),COLOR_TIP_SUC,2,AfxGetMainWnd());
      PTLOG("还原失败\n");
      return;
   }
   CString strDirPath,strNewPath;
   int nCurSel = m_listBox.GetCurSel(); //获取当前索引的bak文件
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
                  DirName = DBTask->m_tNextStartTime.Format(_T("%Y_%m_%d_%H时%M分"));
                  strDirPath = strDirPath+_T("\\")+ DBTask->m_strID + _T("\\")+ _T("XBackUp") + _T("\\")+DirName;
               }
               else
               {
                  DirName = DBTask->m_tNextStartTime.Format(_T("%Y_%m_%d_%H时%M分"));
                  strDirPath = strDirPath+_T("\\")+ DBTask->m_strID + _T("\\")+ _T("FullBackUp") + _T("\\")+DirName;
               }
               if (!theApp.GetStateConnectDB(m_pADOConn))
               {
                  m_pADOConn->InitConnect();
                  return;
               }

               if(IDOK == MessageBox(_T("确定【还原】琪利PDM相关数据吗？"),_T("提示"),MB_OKCANCEL|MB_ICONQUESTION))
               {
                  //校验数据库

                  //检验数据库
				  CString strFullBackname = theApp.m_TaskSuccessList.GetPathByLastExceTimeAndIDAnd(DBTask->m_strID,DBTask->m_tLastExecutionTime,TRUE);
                  CString strFilePath = strFullBackname + _T("\\") + _T("backup.bak");
                  theApp.ShowLoading();
                  if (m_RadGroup)
                  {   
					strFullBackname = strFullBackname+_T("\\") + _T("backup.bak");
					//确定备份文件目录，优先使用
                     CString strXBackDir=strDirPath + _T("\\") + _T("Xbackup.bak");
                     CString strFullBack = strFullBackname;
					 //本次有去本次，没有依次便利
					 if (theApp.FindBackupFile(strFilePath))
					 {
						 strFullBack = strFilePath+ _T("\\") + _T("backup.bak");
					 }

                     BOOL bFlag = RestoreDatabase(strFullBack,strXBackDir,0); //还原bak文件
                     if (bFlag)
                     { 
                            if (DBTask->m_bFileBackup)
                            {
                               strDirPath = strDirPath + _T("\\订单库");
							   //是否可以还原成功
                                  BOOL bRet = m_CDirectroy.CopyDirFileAPI(strDirPath, strNewPath);
                                  if(bRet)
                                  {
                                     theApp.OnShowDesktopAlert(_T("还原成功!"),COLOR_TIP_SUC,2,AfxGetMainWnd());
                                     PTLOG("文件还原成功\n");
                                  }
                                  else
                                  {
                                     theApp.OnShowDesktopAlert(_T("还原目录文件失败!"),COLOR_TIP_FAIL,2,AfxGetMainWnd());
                                       PTLOG("还原目录文件失败\n");
                                  }

                            }
                            else
                            {
                               theApp.OnShowDesktopAlert(_T("还原成功!"),COLOR_TIP_SUC,2,AfxGetMainWnd());
                            }
                          PTLOG("数据库还原成功\n");
                     }
                     else
                     {
                        theApp.OnShowDesktopAlert(_T("还原失败!"),COLOR_TIP_SUC,2,AfxGetMainWnd());
                         PTLOG("还原目录文件失败\n");
                         PTLOG("还原数据库失败\n");
                     }
                  }
                  else
                  {
                     BOOL bFlag = RestoreDatabase(strFilePath,_T(""),1); //还原bak文件
                     if(bFlag)
                     {
                        
                         PTLOG("还原数据库成功\n");
                        strDirPath = strDirPath + _T("\\订单库");
                        if(PathFileExists(strNewPath)&&DBTask->m_bFileBackup)
                        {
                           BOOL bRet = m_CDirectroy.CopyDirFileAPI(strDirPath, strNewPath);
                           if(bRet)
                           {
                              theApp.OnShowDesktopAlert(_T("还原成功!"),COLOR_TIP_SUC,2,AfxGetMainWnd());

                               PTLOG("还原文件成功\n");
                           }
                           else
                           {
                              theApp.OnShowDesktopAlert(_T("还原目录文件失败!"),COLOR_TIP_FAIL,2,AfxGetMainWnd());
                               PTLOG("还原目录文件失败\n");
                           }
                        }
                        else
                        {
                           theApp.OnShowDesktopAlert(_T("源目录不存在子目录【订单库】!"),COLOR_TIP_WARN,2,AfxGetMainWnd());
                            PTLOG("源目录不存在子目录【订单库】\n");
                        }
                     }
                     else
                     {
                        theApp.OnShowDesktopAlert(_T("还原数据库数据失败!"),COLOR_TIP_FAIL,2,AfxGetMainWnd());
                        PTLOG("还原数据库数据失败\n");
                     }
                  }
                  
                   PTLOG("还原结束\n");
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
   // TODO: 在此添加控件通知处理程序代码
    UpdateData(TRUE);
   switch(m_RadGroup)
   {
   case  0:
      {
         //刷新还原数据库（本地备份成功的）list和订单文件list
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

