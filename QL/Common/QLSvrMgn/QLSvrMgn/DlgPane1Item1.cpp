// DlgPane1item1.cpp : 实现文件
//

#include "stdafx.h"
#include "QLSvrMgn.h"
#include "MainFrm.h"
#include "DlgPane1Item1.h"
#include <afxdd_.h>
#include "DBTaskInfo.h"
#include <map>
//#include "DlgTask.h"

// CDlgPane1item1 对话框
#define  TIME_ID_BACKUP_START 10001   //备份定时
#define  TIME_ID_BACKUP_WAIT 10002  //备份等待
#define  TIME_ID_KILL   10003   //结束定时

#define  STATIC_CYCLE_DAY   _T("天")

//周期时间类型
#define  CYCLE_DAY _T("d")
#define  CYCLE_WEEK   _T("w")
#define  CYCLE_MONTH   _T("m")


IMPLEMENT_DYNAMIC(CDlgPane1Item1, CTabDialog)

CDlgPane1Item1::CDlgPane1Item1(CWnd* pParent /*=NULL*/)
	: CTabDialog(CDlgPane1Item1::IDD, pParent)
   , m_radioGroup(0)
{
	m_pADOConn = new CMyADOConnEx(TRUE);
   m_pADOConn->SetExceptionHwnd(AfxGetMainWnd()->GetSafeHwnd());
   m_bStopCy = FALSE;
   m_bWait = FALSE;
   m_nImmediately = 0;
   m_pDlgTask = nullptr;
}

CDlgPane1Item1::~CDlgPane1Item1()
{
 	if(nullptr != m_pADOConn)
 	{
 		delete m_pADOConn;
 		m_pADOConn = nullptr;
 	}

   if (nullptr != m_pDlgTask)
   {
      delete m_pDlgTask;
      m_pDlgTask = nullptr;
   }
}

void CDlgPane1Item1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_radioGroup);
	DDX_Control(pDX, IDC_EDT_DELETE_DAY, m_etDeleteDay);
	DDX_Control(pDX, IDC_CHK_AUTO_DELTE, m_btnAutoDelete);
}


BEGIN_MESSAGE_MAP(CDlgPane1Item1, CTabDialog)
	ON_BN_CLICKED(IDC_OLD_PATH_BUTTON, &CDlgPane1Item1::OnBnClickedOldPathButton)
	ON_EN_CHANGE(IDC_OLD_PATH_EDIT, &CDlgPane1Item1::OnEnChangeOldPathEdit)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgPane1Item1::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDlgPane1Item1::OnBnClickedButtonAddTask)
   ON_WM_TIMER()
   ON_BN_CLICKED(IDC_CHECK_AUTO_BACKUP, &CDlgPane1Item1::OnBnClickedCheckAutoBackup)
   ON_BN_CLICKED(IDC_RADIO1, &CDlgPane1Item1::OnBnClickedRadio1)
   ON_BN_CLICKED(IDC_RADIO2, &CDlgPane1Item1::OnBnClickedRadio1)
   ON_BN_CLICKED(IDC_RADIO3, &CDlgPane1Item1::OnBnClickedRadio1)
   ON_BN_CLICKED(IDC_BTN_OPEN_TASKVIEW, &CDlgPane1Item1::OnBnClickedBtnOpenTaskview)
   ON_BN_CLICKED(IDC_BUTTON_ADD_TASK, &CDlgPane1Item1::AddTask)
   ON_EN_KILLFOCUS(IDC_EDIT_CYCLE, &CDlgPane1Item1::OnEnKillfocusEditCycle)
   ON_BN_CLICKED(IDC_MONTH_ALL_CHECK, &CDlgPane1Item1::OnBnClickedMonthAllCheck)
   ON_BN_CLICKED(IDC_DAY_ALL_CHECK, &CDlgPane1Item1::OnBnClickedDayAllCheck)
   ON_BN_CLICKED(IDC_CHK_AUTO_DELTE, &CDlgPane1Item1::OnBnClickedChkAutoDelte)
END_MESSAGE_MAP()


// CDlgPane1item1 消息处理程序




void CDlgPane1Item1::OnBnClickedOldPathButton()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strDefPath = _T("");
	GetDlgItemText(IDC_OLD_PATH_EDIT, strDefPath);

	CString strNewPath = _T("");
	if (m_CDirectroy.OpenDirectory(strNewPath,strDefPath))
	{
		CString strChildDir = _T("订单库");
		int nLen = strChildDir.GetLength();
		if (strNewPath.GetLength()>nLen && strNewPath.Right(nLen)==strChildDir)
		{
			SetDlgItemText(IDC_OLD_PATH_EDIT, strNewPath);
			theApp.OnWriteIni(_T("BackupPathInfo"), _T("OldPath"), strNewPath,INI_SQLSVR);
		}
		else
		{
			theApp.OnShowDesktopAlert(_T("必须指定到【订单库】！"),COLOR_TIP_WARN,2);
		}
	}
}



BOOL CDlgPane1Item1::OnInitDialog()
{
	CTabDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CString strOldPath = _T(""), strNewPath = _T("");
	theApp.OnReadIni(_T("BackupPathInfo"), _T("OldPath"), strOldPath,INI_SQLSVR);
	SetDlgItemText(IDC_OLD_PATH_EDIT, strOldPath);

	theApp.OnReadIni(_T("BackupPathInfo"), _T("NewPath"), strNewPath,INI_SQLSVR);
	SetDlgItemText(IDC_BACKUP_EDIT, strNewPath);

    CComboBox * pTimeSpan =(CComboBox *)GetDlgItem(IDC_CBO_TIMESPAN);
    for (int i = 0; i<7;i++)
    {
       pTimeSpan->AddString(strWeek[i]);
    }
    pTimeSpan->SetCurSel(0);
    for (int j = 0; j<12;j++)
    {
       m_nCtlIDM[j] = IDC_CKM_1+j;
       GetDlgItem(IDC_CKM_1+j)->ShowWindow(SW_HIDE);
    }
    for (int k = 0; k<30;k++)
    { 
       m_nCtlIDR[k] = IDC_CKR_1+k;
       GetDlgItem(IDC_CKR_1+k)->ShowWindow(SW_HIDE);
    }
    GetDlgItem(IDC_STATIC_MONTH)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_STATIC_DAY)->ShowWindow(SW_HIDE);

    SetDlgItemText(IDC_EDIT_CYCLE,_T("1"));//初始化

	//自动删除控件初始化
	CString strAutodetelDay,strDay;
	theApp.OnReadIni(_T("TaskSuccess"),_T("AutoCheckDelet"),strAutodetelDay,INI_TASKVTY);
	int bCheck =_ttoi(strAutodetelDay.Left(strAutodetelDay.GetLength()-strAutodetelDay.ReverseFind(',')-1));
	 strDay =strAutodetelDay.Right(strAutodetelDay.GetLength()-strAutodetelDay.ReverseFind(',')-1);
	m_etDeleteDay.SetWindowText(strDay);
	m_btnAutoDelete.SetCheck(bCheck);
	OnBnClickedChkAutoDelte();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

BOOL CDlgPane1Item1::BackupDatabase(CString strDirectory,BOOL btype)
{
	BOOL bRet = TRUE;
	CString strSQL = _T("");
	CString strDatabase = _T("");
	theApp.OnReadIni(_T("ConfigureInfo"), _T("DatabaseName"), strDatabase,INI_SQLSVR);
   if(btype)
	   strSQL.Format(_T("BACKUP DATABASE [%s] TO disk = '%s'"), strDatabase, strDirectory);
   else
      strSQL.Format(_T("BACKUP DATABASE [%s] TO disk = '%s' WITH  DIFFERENTIAL,init"),strDatabase,strDirectory);
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

void CDlgPane1Item1::OnEnChangeOldPathEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CTabDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


afx_msg void CDlgPane1Item1::AddTask()
{
   //任务添加
   //路径条件判断
   CString strOldDirPath = _T(""), strNewDirPath = _T("");
   GetDlgItemText(IDC_OLD_PATH_EDIT, strOldDirPath);
   GetDlgItemText(IDC_BACKUP_EDIT, strNewDirPath);
   if(strOldDirPath.IsEmpty() || (!PathFileExists(strOldDirPath)))
   {
      theApp.OnShowDesktopAlert(_T("源目录不存在,无法完成备份!"),COLOR_TIP_FAIL,2,AfxGetMainWnd());
      return;
   }
   if(strNewDirPath.IsEmpty() || (!PathFileExists(strNewDirPath)))
   {
      theApp.OnShowDesktopAlert(_T("目标目录不存在,无法完成备份!"),COLOR_TIP_FAIL,2,AfxGetMainWnd());
      return;
   }
   //路径条件判断_end

   //任务数据录入

   CString strEdit;
   CDBTaskInfo DBTaskInfo;
   CDBTaskInfoList DBTaskList;
   CButton *pFileBack = (CButton *)GetDlgItem(IDC_CHECK_FILE_BACKUP);
   CButton *pAutoBack = (CButton *)GetDlgItem(IDC_CHECK_AUTO_BACKUP);
   CDateTimeCtrl *pStartDate = (CDateTimeCtrl *)GetDlgItem(IDC_DATETIME_ENDDATE);
   CDateTimeCtrl *pStartTime = (CDateTimeCtrl *)GetDlgItem(IDC_DATETIME_ENDTIME);
   CTime ttTime1,ttTime2,ttTime3,ttTime4;
   DWORD dWord1 = pStartDate->GetTime(ttTime1);
   DWORD dWord2 = pStartTime->GetTime(ttTime4);
   ttTime3 = CTime(ttTime1.GetYear(),ttTime1.GetMonth(),ttTime1.GetDay(),ttTime4.GetHour(),ttTime4.GetMinute(),ttTime4.GetSecond());
   ttTime2 = CTime::GetCurrentTime();
   CTimeSpan ttTimeSpan = ttTime3- ttTime2;
   //源文件校验
   if (pFileBack->GetCheck())
   {
      if(strOldDirPath.IsEmpty() || (!PathFileExists(strOldDirPath)))
      {
         theApp.OnShowDesktopAlert(_T("源目录文件不存在"),COLOR_TIP_WARN,2,AfxGetMainWnd());
         return;
      }
   }

   DBTaskInfo.m_strID.Format(_T("%d"),theApp.m_nTaskID);
   DBTaskInfo.m_bFileBackup = pFileBack->GetCheck();
   DBTaskInfo.m_bAutoBackUp = pAutoBack->GetCheck();
   DBTaskInfo.m_nState = 0;
   DBTaskInfo.m_strOldPath = strOldDirPath;
   DBTaskInfo.m_strNewDirPath = strNewDirPath;
   DBTaskInfo.m_tLastExecutionTime = NULL;
   if (m_btnAutoDelete.GetCheck())
   {
	    CString strDay;
		m_etDeleteDay.GetWindowText(strDay);
		if (_ttoi(strDay)>0)
		{
			DBTaskInfo.m_nAutoDeleteTime = _ttoi(strDay);
		}
		else
		{
			DBTaskInfo.m_nAutoDeleteTime = 1;
		}
   }
   else
   {
	   DBTaskInfo.m_nAutoDeleteTime = 0;
   }

   //任务类型判断
   if (DBTaskInfo.m_bFileBackup)
   {
      DBTaskInfo.m_bAutoBackUp ? DBTaskInfo.m_strTaskType = TASK_FILE_BACKUP : DBTaskInfo.m_strTaskType = TASK_FILE_XBACKUP;

   }
   else
   {
      DBTaskInfo.m_bAutoBackUp ? DBTaskInfo.m_strTaskType = TASK_NOFILE_BACKUP : DBTaskInfo.m_strTaskType = TASK_NOFILE_XBACKUP;
   }

   switch(m_radioGroup)
   {
   case 0:
      {
         CEdit *pCycle = (CEdit *)GetDlgItem(IDC_EDIT_CYCLE);
         pCycle->GetWindowText(strEdit);
         if (m_nImmediately)
         {
            DBTaskInfo.m_strCyc = _T("");//周期为空
         }
         else
         {
            DBTaskInfo.m_strCyc = _T("*")+strEdit;
            int nday = _ttoi(strEdit);
            LONG64 nd = nday *60*60*24;
            CTimeSpan tims(nd);
            //时间开始判断  add anjie by 2018/08/20
            if (ttTime2>=ttTime3)
            {
               ttTime3+=tims;
            }
         }
         DBTaskInfo.m_strCycType = CYCLE_DAY;
         DBTaskInfo.m_tStartTime = ttTime3;//任务开始时间
         DBTaskInfo.m_tNextStartTime = ttTime3;
         DBTaskInfo.m_tStdStartTime = ttTime3;
         break;
      }
   case 1:
      {
        CComboBox *pTimeSpan = (CComboBox*)GetDlgItem(IDC_CBO_TIMESPAN);
        int nIndex = pTimeSpan->GetCurSel();
        for (int i =0 ; i<7;i++)
        {
            if (nIndex == i)
            {
                DBTaskInfo.m_strCyc.Format(_T("*%d"),nIndex);//周期为空
                int nWeek=ttTime3.GetDayOfWeek();
                if (nWeek>(nIndex+1))//是否星期是否在开始时间的前面
                {
                   int nDay = 7-nWeek+nIndex+1;
                   CTime tTime(ttTime3.GetYear(),ttTime3.GetMonth(),ttTime3.GetDay()+nDay,ttTime3.GetHour(),ttTime3.GetMinute(),ttTime3.GetSecond());
                   DBTaskInfo.m_tStartTime = ttTime3;
                   DBTaskInfo.m_tNextStartTime = tTime;
                   DBTaskInfo.m_tStdStartTime = tTime;
                }
                else
                {
                   int nDay = nIndex+1 - nWeek;
                   CTime tTime(ttTime3.GetYear(),ttTime3.GetMonth(),ttTime3.GetDay()+nDay,ttTime3.GetHour(),ttTime3.GetMinute(),ttTime3.GetSecond());
                   if (ttTime2<=ttTime3)
                   {
                      DBTaskInfo.m_tStartTime = ttTime3;
                      DBTaskInfo.m_tNextStartTime = ttTime3;
                      DBTaskInfo.m_tStdStartTime = ttTime3;
                   }
                   else
                   {
                      DBTaskInfo.m_tStartTime = ttTime3;
                      DBTaskInfo.m_tNextStartTime = tTime;
                      DBTaskInfo.m_tStdStartTime = tTime;
                   }
                }
            }
        }
        DBTaskInfo.m_strCycType = CYCLE_WEEK;
         break;
      }
   case 2:
      {
       DBTaskInfo.m_strCycType = CYCLE_MONTH;
        DBTaskInfo.m_tStartTime = ttTime3;
         for (int i = 0;i < 12;i++)
         {
            CButton *pCheckM = (CButton *)GetDlgItem(m_nCtlIDM[i]);
            if (pCheckM->GetCheck())
            {
               for (int j = 0;j<30;j++)
               {
                   CButton *pCheckR = (CButton *)GetDlgItem(m_nCtlIDR[j]);
                   if (pCheckR->GetCheck())
                   {
                      CString strMon;
                      strMon.Format(_T("*%d#%d"),i+1,j+1);
                      if(((ttTime3.GetYear()%4==0)&&(ttTime3.GetYear()%100!=0))||((ttTime3.GetYear()%100==0)&&(ttTime3.GetYear()%400==0)))
                      {
                         if (i == 1 && j >28)
                         {
                            
                            continue;
                         }
                      }
                      else
                      {
                         if (i == 1 && j >=28)
                         {
                            
                            continue;
                         }
                      }
                      CTime tTime(ttTime3.GetYear(),i+1,j+1,ttTime3.GetHour(),ttTime3.GetMinute(),ttTime3.GetSecond());
                      CTime tTimeT(ttTime3.GetYear()+1,i+1,j+1,ttTime3.GetHour(),ttTime3.GetMinute(),ttTime3.GetSecond());
                      CDBTaskInfo DBTaskInfoLin;
                     DBTaskInfoLin.Copy(&DBTaskInfo);
                     DBTaskInfoLin.m_strID.Format(_T("%d"),theApp.m_nTaskID);
                     //月份时间调整
                     if (ttTime2>tTime)
                     {
                        DBTaskInfoLin.m_tNextStartTime = tTimeT;
                        DBTaskInfoLin.m_tStdStartTime = tTimeT;
                     }
                     else
                     {
                        DBTaskInfoLin.m_tNextStartTime = tTime;
                        DBTaskInfoLin.m_tStdStartTime = tTime;
                     }
                     DBTaskInfoLin.m_strCyc = strMon;
                     DBTaskList.addItem(&DBTaskInfoLin);
                     DBTaskInfo.m_strCyc+=strMon;
                     theApp.m_nTaskID++;
                   }
               }
            }
         }
  
         break;
      }
   default:
      break;
   }

   //备份类型检查
   if (m_nImmediately)
   {
	   DBTaskInfo.m_tStartTime = ttTime2;
	   DBTaskInfo.m_tNextStartTime = ttTime2;
	   DBTaskInfo.m_tStdStartTime = ttTime2;
   }

   //是否是分解为多任务
   if (DBTaskList.GetCount()>0)
   {
      PTLOG("多任务处理");
      theApp.m_TaskList = DBTaskList;
   }
   else if (DBTaskInfo.m_strCycType != CYCLE_MONTH || m_nImmediately)
   {
      PTLOG("新增任务");
      theApp.m_TaskList.addItem(&DBTaskInfo);
   }
   theApp.m_nTaskID++;
   int ncount = theApp.m_TaskList.GetCount();

   //立即任务不添加写到相关数据中
   if (!m_nImmediately)
   {
      theApp.SaveTaskInfo();//数据写入
   }

   //控件记忆简单填写
   CString strTemp,strDeteDay;
   m_etDeleteDay.GetWindowTextW(strDeteDay);
   strTemp.Format(_T("%d,%s"),m_btnAutoDelete.GetCheck(),strDeteDay);
   theApp.OnWriteIni(_T("TaskSuccess"),_T("AutoCheckDelet"),strTemp,INI_TASKVTY);

   m_nImmediately = 0;


}


BOOL CDlgPane1Item1::RunBackUp()
{
	CString strOldDirPath = _T(""), strNewDirPath = _T("");
	GetDlgItemText(IDC_OLD_PATH_EDIT, strOldDirPath);
	GetDlgItemText(IDC_BACKUP_EDIT, strNewDirPath);
   CButton *pCheckAuto =(CButton *) GetDlgItem(IDC_CHECK_AUTO_BACKUP);
    CButton *pCheckFile =(CButton *) GetDlgItem(IDC_CHECK_FILE_BACKUP);
	if(strOldDirPath.IsEmpty() || (!PathFileExists(strOldDirPath)))
	{
		theApp.OnShowDesktopAlert(_T("源目录不存在,无法完成备份!"),COLOR_TIP_FAIL,2,AfxGetMainWnd());
	}

	if(strNewDirPath.IsEmpty() || (!PathFileExists(strNewDirPath)))
	{
		theApp.OnShowDesktopAlert(_T("目标目录不存在,无法完成备份!"),COLOR_TIP_FAIL,2,AfxGetMainWnd());
      theApp.CloseLoading();
		return FALSE;
	}
	//路径条件判断_end

   if (!theApp.GetStateConnectDB())
   {
      theApp.OnShowDesktopAlert(_T("无法连接到备份的数据库"),COLOR_TIP_WARN,2,AfxGetMainWnd());
      theApp.CloseLoading();
       theApp.m_pADOConn->InitConnect();
      return FALSE;
   }

   //自动备份不提示

      if(IDCANCEL == MessageBox(_T("确定【备份】琪利PDM相关数据吗？"),_T("提示"),MB_OKCANCEL|MB_ICONQUESTION))
      {
         theApp.CloseLoading();
         return FALSE;
      }	
	   COleDateTime CurrentTime=COleDateTime::GetCurrentTime();
	   CString strTime;
      strTime = CurrentTime.Format(_T("%Y_%m_%d_%H时%M分"));
	   //strTime.Format(_T("%d_%d_%d_%d时%d分") ,CurrentTime.GetYear(), CurrentTime.GetMonth(),CurrentTime.GetDay(), CurrentTime.GetHour(), CurrentTime.GetMinute()); 
	   CString strDirPath = strNewDirPath + _T("\\") + strTime;
	   if(!PathFileExists(strDirPath))
	   {
		   theApp.MakeDirByCheck(strDirPath);
	   }

	   //开始备份
	   theApp.ShowLoading();
      BOOL bFlag = FALSE;
      BOOL bXFlag = FALSE;

      //检索本地是否存在完整备份从而进行差异备份
      CString strFullBackUpDirPath = strNewDirPath + _T("\\") +_T("FullBackUp") +_T("\\")  +strTime;
      CString strDifferentialDirPath = strNewDirPath + _T("\\") +strTime;
      if(!PathFileExists(strFullBackUpDirPath))
      {
         theApp.MakeDirByCheck(strFullBackUpDirPath);
      }
      if(!PathFileExists(strDifferentialDirPath))
      {
         theApp.MakeDirByCheck(strDifferentialDirPath);
      }

      if(!theApp.FindBackupFile(strNewDirPath))
      {
         bFlag = BackupDatabase(strFullBackUpDirPath + _T("\\backup.bak"),TRUE);//整体备份
         if(bFlag)
         {
            if(strFullBackUpDirPath.IsEmpty() || (!PathFileExists(strFullBackUpDirPath)))
            {
               theApp.CloseLoading();
               return 0;
            }
            
            TRACE("%d:%s::数据库完整备份成功!\n",__LINE__,__FILE__);
            BOOL bRet = theApp.m_CDirectroy.CopyDirFileAPI(strOldDirPath, strFullBackUpDirPath+_T("\\订单库"));
            if(bRet)
            {
               TRACE("%d:%s::完整备份文件成功!\n",__LINE__,__FILE__);
               theApp.m_strXbackUpFileTime = strTime;
            }
            else
            {
               TRACE("%d:%s::完整备份文件失败!\n",__LINE__,__FILE__);
               theApp.CloseLoading();
               return 0;
            }		
         }
         else
         {
            TRACE("%d:%s::完整备份数据库失败!\n",__LINE__,__FILE__);
            TRACE("%d:%s::完整备份文件失败!\n",__LINE__,__FILE__);
            theApp.CloseLoading();
            return 0;
         }
      }

      if (pCheckAuto->GetCheck())
      {
         bFlag = BackupDatabase(strFullBackUpDirPath + _T("\\backup.bak"),TRUE);//整体备份
         if(bFlag)
         {
            if(strFullBackUpDirPath.IsEmpty() || (!PathFileExists(strFullBackUpDirPath)))
            {
               theApp.CloseLoading();
               return 0;
            }
            TRACE("%d:%s::数据库完整备份成功!\n",__LINE__,__FILE__);
            BOOL bRet = theApp.m_CDirectroy.CopyDirFileAPI(strOldDirPath, strFullBackUpDirPath+_T("\\订单库"));
            if(bRet)
            {
               TRACE("%d:%s::完整备份文件成功!\n",__LINE__,__FILE__);
               theApp.m_strXbackUpFileTime = strTime;
            }
            else
            {
               TRACE("%d:%s::完整备份文件失败!\n",__LINE__,__FILE__);
               return 0;
            }		
         }
         else
         {
            TRACE("%d:%s::完整备份数据库失败!\n",__LINE__,__FILE__);
            TRACE("%d:%s::完整备份文件失败!\n",__LINE__,__FILE__);
            return 0;
         }
      }

   bXFlag = BackupDatabase(strDifferentialDirPath + _T("\\Xbackup.bak"),FALSE);//差异备份

   if(bXFlag)
   {
      CString strDifferentialDirFilePath = strDifferentialDirPath+_T("\\订单库");
      if(strDifferentialDirPath.IsEmpty() || (!PathFileExists(strDifferentialDirPath)))
      {
         theApp.CloseLoading();
         return 0;
      }
      if(strDifferentialDirFilePath.IsEmpty() || (!PathFileExists(strDifferentialDirFilePath)))
      {
         theApp.MakeDirByCheck(strDifferentialDirFilePath);
      }
      TRACE("%d:%s::数据库差分备份成功!\n",__LINE__,__FILE__);
      //文件差异备份
      if (pCheckFile->GetCheck())
      {
         CString str;

         str.Format(_T("/c %s\\xcopyAdd %s %s /e /k /d:%s"),theApp.m_strAppPath,strOldDirPath,strDifferentialDirFilePath,theApp.m_strXbackUpFileTime);

         HINSTANCE n=ShellExecute(NULL,L"open",L"cmd.exe",str,NULL,SW_HIDE);
         int a = (int)n;
         if(a<=32)
         {
            TRACE("%d:%s::差分备份文件失败!\n",__LINE__,__FILE__);
         }
         else
         {
            TRACE("%d:%s::差分备份文件成功!\n",__LINE__,__FILE__);
         }
      }
   }
   else
   {
      TRACE("%d:%s::差异备份数据库失败!\n",__LINE__,__FILE__);
      TRACE("%d:%s::差异备份文件失败!\n",__LINE__,__FILE__);
      return 0;
   }

	theApp.CloseLoading();
   return TRUE;
}

void CDlgPane1Item1::OnBnClickedButton1()
{
   CString strDefPath = _T("");
   GetDlgItemText(IDC_BACKUP_EDIT, strDefPath);

   CString strNewPath = _T("");
   if (m_CDirectroy.OpenDirectory(strNewPath,strDefPath))
   {
      SetDlgItemText(IDC_BACKUP_EDIT, strNewPath);
      theApp.OnWriteIni(_T("BackupPathInfo"), _T("NewPath"), strNewPath,INI_SQLSVR);
   }
}


void CDlgPane1Item1::OnTimer(UINT_PTR nIDEvent)
{
  if (nIDEvent == TIME_ID_BACKUP_START)
  {
     if(!m_bStopCy)
     {
         AddTask();
     }

  }
  else if (nIDEvent == TIME_ID_BACKUP_WAIT)
  {
     CString strEdit,strStc;
     m_bWait = TRUE;
     KillTimer(TIME_ID_BACKUP_WAIT);
     CEdit *pCycle = (CEdit *)GetDlgItem(IDC_EDIT_CYCLE);
     CStatic *pStatCycle = (CStatic *)GetDlgItem(IDC_STATIC_CYC);
     pCycle->GetWindowText(strEdit);
     pStatCycle->GetWindowText(strStc);
     int nSpan = 0;
     if (strStc == STATIC_CYCLE_DAY)
     {
        nSpan =_ttoi(strEdit);
        nSpan = nSpan * 60000*60*24;
     }
     
     SetTimer(TIME_ID_BACKUP_START,5000,NULL);//启动备份定时器 add anjie by 2018/07/17
  }
   CTabDialog::OnTimer(nIDEvent);
}


void CDlgPane1Item1::OnBnClickedCheckAutoBackup()
{
   // TODO: 在此添加控件通知处理程序代码
   CButton *pAuto = (CButton *)GetDlgItem(IDC_CHECK_AUTO_BACKUP);
   if (!pAuto->GetCheck())
   {
      KillTimer(TIME_ID_BACKUP_WAIT);//清除自动定时
      KillTimer(TIME_ID_BACKUP_START);//清除自动定时
      m_bStopCy = TRUE;
      m_bWait = FALSE;
      reset(m_bStopCy);
   }
   else
      m_bStopCy = FALSE;
}

void CDlgPane1Item1::reset(BOOL bStopCy)
{
   CButton *pBackUpBtn = (CButton *)GetDlgItem(IDC_OLD_PATH_BUTTON);
   pBackUpBtn->EnableWindow(bStopCy);
   CButton *pBtn1 = (CButton *)GetDlgItem(IDC_BUTTON1);
   pBtn1->EnableWindow(bStopCy);
   CButton *pBackUp = (CButton *)GetDlgItem(IDC_BUTTON2);
   pBackUp->EnableWindow(bStopCy);
   CEdit *pOldPath = (CEdit *)GetDlgItem(IDC_OLD_PATH_EDIT);
   pOldPath->EnableWindow(bStopCy);
   CEdit *pBackUpEdit = (CEdit *)GetDlgItem(IDC_BACKUP_EDIT);
   pBackUpEdit->EnableWindow(bStopCy);
}

void CDlgPane1Item1::OnBnClickedRadio1()
{
  CComboBox *pTimeSpan = (CComboBox *)GetDlgItem(IDC_CBO_TIMESPAN);
  CEdit *pCycle = (CEdit *)GetDlgItem(IDC_EDIT_CYCLE);
   CStatic *pStatCycle = (CStatic *)GetDlgItem(IDC_STATIC_CYC);
  UpdateData(TRUE);
  switch(m_radioGroup)
  {
  case 0:
     {
        pTimeSpan->ShowWindow(SW_HIDE);
        pCycle->ShowWindow(SW_SHOW);
        pStatCycle->ShowWindow(SW_SHOW);
        pStatCycle->SetWindowText(_T("天"));
        GetDlgItem(IDC_STATIC_MONTH)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_DAY)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_MONTH_ALL_CHECK)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_DAY_ALL_CHECK)->ShowWindow(SW_HIDE);
        for (int i = 0;i < 12;i++)
        {
           GetDlgItem(m_nCtlIDM[i])->ShowWindow(SW_HIDE);
        }
        for (int i = 0;i < 30;i++)
        {
           GetDlgItem(m_nCtlIDR[i])->ShowWindow(SW_HIDE);
        }
        break;
     }
  case 1:
     {
        pTimeSpan->ShowWindow(SW_SHOW);
        pCycle->ShowWindow(SW_HIDE);
        pStatCycle->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_MONTH)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_DAY)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_MONTH_ALL_CHECK)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_DAY_ALL_CHECK)->ShowWindow(SW_HIDE);
        for (int i = 0;i < 12;i++)
        {
           GetDlgItem(m_nCtlIDM[i])->ShowWindow(SW_HIDE);
        }
        for (int i = 0;i < 30;i++)
        {
           GetDlgItem(m_nCtlIDR[i])->ShowWindow(SW_HIDE);
        }
        break;
     }
  case 2:
     {
        pTimeSpan->ShowWindow(SW_HIDE);
        pCycle->ShowWindow(SW_HIDE);
        pStatCycle->ShowWindow(SW_HIDE);
        pStatCycle->SetWindowText(_T("天"));
        GetDlgItem(IDC_STATIC_MONTH)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_DAY)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_MONTH_ALL_CHECK)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_DAY_ALL_CHECK)->ShowWindow(SW_SHOW);
        for (int i = 0;i < 12;i++)
        {
           GetDlgItem(m_nCtlIDM[i])->ShowWindow(SW_SHOW);
        }
        for (int i = 0;i < 30;i++)
        {
           GetDlgItem(m_nCtlIDR[i])->ShowWindow(SW_SHOW);
        }
     }
  default:
     {
        break;
     }
  }
}


void CDlgPane1Item1::OnBnClickedBtnOpenTaskview()
{
   if (!m_pDlgTask)
   {
      m_pDlgTask = new CDlgTask;
   }
   int iRet=m_pDlgTask->DoModal(); 
 
}



void CDlgPane1Item1::OnBnClickedButtonAddTask()
{
   m_nImmediately = 1;//立即备份标志
   AddTask();
}


void CDlgPane1Item1::OnEnKillfocusEditCycle()
{
   // TODO: 在此添加控件通知处理程序代码
   CString strText = _T("");
   GetDlgItemText(IDC_EDIT_CYCLE,strText);
   if (strText.IsEmpty())
   {
      SetDlgItemText(IDC_EDIT_CYCLE,_T("1"));
   }
   else
   {
      int nText = _ttoi(strText);
      if (nText)
      {
         CString strLText;
         strLText.Format(_T("%d"),nText);
        SetDlgItemText(IDC_EDIT_CYCLE,strLText);
      }
      else
      {
          SetDlgItemText(IDC_EDIT_CYCLE,_T("1"));
      }
   }
}


void CDlgPane1Item1::OnBnClickedMonthAllCheck()
{
   // TODO: 在此添加控件通知处理程序代码
   CButton *pMon = (CButton *)GetDlgItem(IDC_MONTH_ALL_CHECK);
   BOOL bCheck = FALSE;
   if(pMon && pMon->GetCheck())
   {
      bCheck = TRUE;
   }

   for (int i = 0;i < 12;i++)
   {
      CButton *pCheck = (CButton *)GetDlgItem(m_nCtlIDM[i]);
      if (pCheck !=nullptr)
      {
         pCheck->SetCheck(bCheck);
      }
   }
}


void CDlgPane1Item1::OnBnClickedDayAllCheck()
{
   // TODO: 在此添加控件通知处理程序代码
   CButton *pDay = (CButton *)GetDlgItem(IDC_DAY_ALL_CHECK);
   BOOL bCheck = FALSE;
   if(pDay && pDay->GetCheck())
   {
      bCheck = TRUE;
   }

   for (int i = 0;i < 30;i++)
   {
      CButton *pCheck = (CButton *)GetDlgItem(m_nCtlIDR[i]);
      if (pCheck !=nullptr)
      {
         pCheck->SetCheck(bCheck);
      }
   }
}

extern CString strWeek[7]= {
   _T("周日"),
   _T("周一"),
   _T("周二"),
   _T("周三"),
   _T("周四"),
   _T("周五"),
   _T("周六"),
};

void CDlgPane1Item1::OnBnClickedChkAutoDelte()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_btnAutoDelete.GetCheck())
	{
		//m_etDeleteDay.EnableWindow(TRUE);
		m_etDeleteDay.SetReadOnly(FALSE);
	}
	else
	{
		//m_etDeleteDay.EnableWindow(FALSE);
		m_etDeleteDay.SetReadOnly(TRUE);
	}
}
