//宏定义

// CDlgPane1item1 对话框
#define  TIME_ID_BACKUP_START 10001   //备份定时
#define  TIME_ID_BACKUP_WAIT 10002  //备份等待
#define  TIME_ID_KILL   10003   //结束定时

//TaskDlg
#define  TIME_ID_UPDATA 10004 //数据刷新
#define  TIME_ID_SAVEINFO 10005

#define  STATIC_CYCLE_DAY   _T("天")

//周期时间类型
#define  CYCLE_DAY _T("d")
#define  CYCLE_WEEK   _T("w")
#define  CYCLE_MONTH   _T("m")

#define  DAY 24*60*60   
#define  WEEK 7*24*60*60  


//监控任务触发
#define WM_BACKUP WM_USER+1

//本地配置文件类型
#define INI_SQLSVR  0
#define INI_TASKINFO  1
#define INI_TASKVTY  2


#define WM_TRAY WM_USER+1
#define WM_KDSFILEMGN_WORKTYPE		WM_USER + 0x100	//发送工作类型

//任务类型
#define  TASK_NOFILE_BACKUP _T("整体无文件")
#define  TASK_NOFILE_XBACKUP _T("差异无文件")
#define  TASK_FILE_BACKUP _T("整体有文件")
#define  TASK_FILE_XBACKUP _T("差异有文件")
