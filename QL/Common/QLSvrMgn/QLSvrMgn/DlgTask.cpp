// DlgTask.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "QLSvrMgn.h"
#include "DlgTask.h"
#include "afxdialogex.h"
#include "DlgPane1Item1.h"

// CDlgTask �Ի���
IMPLEMENT_DYNAMIC(CDlgTask, CDialogEx)

CDlgTask::CDlgTask(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgTask::IDD, pParent)
{

}

CDlgTask::~CDlgTask()
{
}

void CDlgTask::DoDataExchange(CDataExchange* pDX)
{
   CDialogEx::DoDataExchange(pDX);
   DDX_Control(pDX, IDC_LIST_TASK, m_TaskBackList);
   DDX_Control(pDX, IDC_HISTORY_LIST, m_TaskHistoryList);
}


BEGIN_MESSAGE_MAP(CDlgTask, CDialogEx)
   ON_BN_CLICKED(IDC_BUTTON_SUPEND, &CDlgTask::OnBnClickedButtonSupend)
   ON_BN_CLICKED(IDC_BUTTON2, &CDlgTask::OnBnClickedButton2)
   ON_BN_CLICKED(IDC_BUTTON_START, &CDlgTask::OnBnClickedButtonStart)
   ON_WM_TIMER()
   ON_WM_CONTEXTMENU()
   ON_COMMAND(IDM_DELETE_TASK,&CDlgTask::OnDeleteTask)
END_MESSAGE_MAP()


// CDlgTask ��Ϣ�������


void CDlgTask::OnBnClickedButtonSupend()
{
   // TODO: �ڴ���ӿؼ�֪ͨ����������
   if (theApp.m_pWorkThread)
   {
      theApp.m_pWorkThread->SuspendThread();
      theApp.OnShowDesktopAlert(_T("��ǰִ����������ͣ��"),COLOR_TIP_FAIL,2,AfxGetMainWnd());
       theApp.DBExTask.m_nState = 2;
   }
   else
       theApp.OnShowDesktopAlert(_T("��ǰ��ִ��������ͣʧ�ܣ�"),COLOR_TIP_FAIL,2,AfxGetMainWnd());

    refreshData();
}


void CDlgTask::OnBnClickedButton2()
{
   // TODO: �ڴ���ӿؼ�֪ͨ����������

	CSingleLock sinLock(&theApp.m_Mutex);
   if (!sinLock.IsLocked())
   {
       theApp.OnShowDesktopAlert(_T("��ǰû������ִ�е����񣡽���ʧ��"),COLOR_TIP_FAIL,2,AfxGetMainWnd());
   }
   else
   {
      DWORD exitcode2;
      BOOL bcode = GetExitCodeThread(theApp.m_pWorkThread->m_hThread,&exitcode2);
      if (exitcode2 == STILL_ACTIVE)
      {
         //ExitThread(exitcode2); 
         BOOL bExit = TerminateThread(theApp.m_pWorkThread->m_hThread,exitcode2);
         if (bExit)
         {
            theApp.OnShowDesktopAlert(_T("��������ɹ���"),COLOR_TIP_FAIL,2,AfxGetMainWnd());
            theApp.DBExTask.m_nState = 3;
         }
         else
         {
            theApp.OnShowDesktopAlert(_T("����ʧ�ܣ�"),COLOR_TIP_FAIL,2,AfxGetMainWnd());
         }
      }
      else
         theApp.OnShowDesktopAlert(_T("��ǰû������ִ�е����񣡽���ʧ��"),COLOR_TIP_FAIL,2,AfxGetMainWnd());

   }

   refreshData();
}


void CDlgTask::OnBnClickedButtonStart()
{
   // TODO: �ڴ���ӿؼ�֪ͨ����������
   DWORD dwExitCode = 0;
   GetExitCodeThread(theApp.m_pWorkThread,&dwExitCode);
   if (theApp.m_pWorkThread&&dwExitCode !=STILL_ACTIVE)
   {
      theApp.m_pWorkThread->ResumeThread();
      theApp.OnShowDesktopAlert(_T("���������ɹ�!"),COLOR_TIP_FAIL,2,AfxGetMainWnd());
       theApp.DBExTask.m_nState = 1;
   } 
   else
      theApp.OnShowDesktopAlert(_T("��������ʧ�ܣ�"),COLOR_TIP_FAIL,2,AfxGetMainWnd());
   refreshData();
}


BOOL CDlgTask::OnInitDialog()
{
   CDialogEx::OnInitDialog();

   // TODO:  �ڴ���Ӷ���ĳ�ʼ��
   //2�޸ĳ����񣬻��ߴӿؼ���������
   LONG lStyle;
   lStyle =GetWindowLong(m_TaskBackList.m_hWnd,GWL_STYLE);
   lStyle |= LVS_REPORT;//����Ϊ������
   SetWindowLong(m_TaskBackList.m_hWnd,GWL_STYLE,lStyle);
   //3 ������չ�������ѡ�������ߣ�ǰ���м���
   // m_listctrl.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_CHECKBOXES); 
   DWORD dwStyle = m_TaskBackList.GetExtendedStyle();
   dwStyle |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
   dwStyle |= LVS_EX_GRIDLINES;//�����ߣ�ֻ������report����listctrl��
   //dwStyle |= LVS_EX_CHECKBOXES;//itemǰ����checkbox�ؼ�
   m_TaskBackList.SetExtendedStyle(dwStyle); //������չ

   SetWindowTextW(_T("�����"));
   m_TaskBackList.InsertColumn(0,_T("ID"),LVCFMT_CENTER,50);
   m_TaskBackList.InsertColumn(1,_T("��ʱ����ʱ��"),LVCFMT_CENTER,120);
   m_TaskBackList.InsertColumn(2,_T("Ԥ��ʱ��"),LVCFMT_CENTER,120);
   m_TaskBackList.InsertColumn(3,_T("״̬"),LVCFMT_CENTER,80);
   m_TaskBackList.InsertColumn(4,_T("����"),LVCFMT_CENTER,80);
   m_TaskBackList.InsertColumn(5,_T("��������"),LVCFMT_CENTER,80);
   m_TaskBackList.InsertColumn(6,_T("��������"),LVCFMT_CENTER,120);
   m_TaskBackList.InsertColumn(7,_T("�ϴ����ʱ��"),LVCFMT_CENTER,140);
   refreshData();
   return TRUE;  // return TRUE unless you set the focus to a control
   // �쳣: OCX ����ҳӦ���� FALSE
}

void CDlgTask::refreshData()
{
   DWORD dT1 = GetTickCount();
   TRACE(_T("%ld\n"),dT1);
   m_TaskBackList.DeleteAllItems();
   int nColmunCount =m_TaskBackList.GetHeaderCtrl()->GetItemCount();
   int nRowCount = theApp.m_TaskList.GetCount();
   if (theApp.m_bTaskMark)
   {
      nRowCount = theApp.m_TaskList.GetCount()+1;
   }
   for (int i = 0;i<nRowCount;i++)
   {
      CDBTaskInfo *task;
      CString str1;
      str1.Format(_T("%d"),i);
	  CSingleLock sinLock(&theApp.m_Mutex);
	  if (sinLock.IsLocked())
      {   
       if (i>0)
      {
         task = (CDBTaskInfo *)theApp.m_TaskList.GetAt(theApp.m_TaskList.FindIndex(i-1));
      }
      }
      else
      {
         task = (CDBTaskInfo *)theApp.m_TaskList.GetAt(theApp.m_TaskList.FindIndex(i));
      }
      m_TaskBackList.InsertItem(i,str1);
      for (int j = 0;j<nColmunCount;j++)
      {
         CString str;
         switch(j)
         {
         case 0:
            {
               if (sinLock.IsLocked() && !i)
               {
                  m_TaskBackList.SetItemText(i,j,theApp.DBExTask.m_strID);
               }
               else
                  m_TaskBackList.SetItemText(i,j,task->m_strID);
               break;
            }
         case 1:
            {
               if (sinLock.IsLocked() && !i)
               {
                  str = theApp.DBExTask.m_tStartTime.Format("%Y/%m/%d/%H:%M:%S");
               }
               else
               {
                  str = task->m_tStartTime.Format("%Y/%m/%d/%H:%M:%S");
               }
               m_TaskBackList.SetItemText(i,j,str);
               break;
            }
         case 2:
            {
               if (sinLock.IsLocked() && !i)
               {
                  str = theApp.DBExTask.m_tStdStartTime.Format("%Y/%m/%d/%H:%M:%S");
               }
               else
               {
                  str = task->m_tStdStartTime.Format("%Y/%m/%d/%H:%M:%S");
               }
               m_TaskBackList.SetItemText(i,j,str);
               break;
            }
         case 3:
            {
               if ((sinLock.IsLocked() && !i))
               {
                 
                  str.Format(_T("%d"),theApp.DBExTask.m_nState);
                  if (theApp.DBExTask.m_nState)
                  {
                     str = _T("ִ����");
                  }
                  m_TaskBackList.SetItemText(i,j,str);
               }
               else
               {
                  str.Format(_T("%d"),task->m_nState);
                  if (task->m_nState)
                  {
                     str = _T("ִ����");
                  }
                  else
                  {
                     str = _T("��ִ��");
                  }
                  m_TaskBackList.SetItemText(i,j,str);
               }
               break;
            }
         case 4:
            {
               if (sinLock.IsLocked() && !i)
               {
                  str = theApp.DBExTask.m_strCyc.Right(theApp.DBExTask.m_strCyc.GetLength()-1);
               }
               else
               {
                  str = task->m_strCyc.Right(task->m_strCyc.GetLength()-1);
               }

               if (task->m_strCycType == CYCLE_DAY)
               {
                  str+=_T("��");
               }
               else if(task->m_strCycType == CYCLE_MONTH)
               {
                  int nIndex = str.FindOneOf(_T("#"));
                  if (nIndex)
                  {
                     str.Replace(_T("#"),_T("��"));
                     str.Append(_T("��"));
                  }
               }
               else if(task->m_strCycType == CYCLE_WEEK)
               {
                  int nCycle = _ttoi(str);
                  str = strWeek[nCycle];
               }
               m_TaskBackList.SetItemText(i,j,str);
               break;
            }
         case 5:
            {
               if (sinLock.IsLocked() && !i)
               {
                  CString strCycType;
                  if (theApp.DBExTask.m_strCycType == CYCLE_WEEK)
                  {
                     strCycType = _T("��");
                  }
                  else if (theApp.DBExTask.m_strCycType == CYCLE_DAY)
                  {
                     strCycType = _T("��");
                  }
                  else if (theApp.DBExTask.m_strCycType == CYCLE_MONTH)
                  {
                     strCycType = _T("����");
                  }
                  m_TaskBackList.SetItemText(i,j,strCycType);
               }
               else
               {
                  CString strCycType;
                  if (task->m_strCycType == CYCLE_WEEK)
                  {
                     strCycType = _T("��");
                  }
                  else if (task->m_strCycType == CYCLE_DAY)
                  {
                     strCycType = _T("��");
                  }
                  else if (task->m_strCycType == CYCLE_MONTH)
                  {
                     strCycType = _T("����");
                  }
                  m_TaskBackList.SetItemText(i,j,strCycType);
               }
               break;
            }
         case 6:
            {
               if (sinLock.IsLocked() && !i)
               {
                  m_TaskBackList.SetItemText(i,j,theApp.DBExTask.m_strTaskType);
               }
               else
               {
                  m_TaskBackList.SetItemText(i,j,task->m_strTaskType);
               }
               break;
            }
         case 7:
            {
               if (sinLock.IsLocked() && !i)
               {
                  if (theApp.DBExTask.m_tLastExecutionTime != NULL)
                  {
                     CString strExecutTime = theApp.DBExTask.m_tLastExecutionTime.Format(_T("%Y/%m/%d %H:%M:%S"));
                     m_TaskBackList.SetItemText(i,j,strExecutTime);
                  }
               }
               else
               {
                  if (task->m_tLastExecutionTime != NULL)
                  {
                     CString strExecutTime = task->m_tLastExecutionTime.Format(_T("%Y/%m/%d %H:%M:%S"));
                     m_TaskBackList.SetItemText(i,j,strExecutTime);
                  }
               }
               break;
            }
         default:
            break;
         }

      }

   }

   TRACE(_T("%ld\n"),(GetTickCount()-dT1));
   dT1 = GetTickCount();
}


void CDlgTask::OnTimer(UINT_PTR nIDEvent)
{
   // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
   if (nIDEvent == TIME_ID_UPDATA)
   {
	   CSingleLock sinLock(&theApp.m_Mutex);
      if (sinLock.IsLocked() != theApp.m_bLastTaskMark)
      {
         theApp.m_bLastTaskMark = sinLock.IsLocked();
          refreshData();
      }
   }
   else if(nIDEvent == TIME_ID_SAVEINFO)
   {
      theApp.SaveTaskInfo();
   }
   CDialogEx::OnTimer(nIDEvent);
}


void CDlgTask::OnContextMenu(CWnd *, CPoint point)
{
   // TODO: �ڴ˴������Ϣ����������
   CPoint Point = point;
   CMenu menu,*popMenu;
   popMenu = nullptr;
   //ScreenToClient(&Point);
   menu.LoadMenu(IDR_MENU_TASK);  

   //�Ӳ˵���  
   //�Ҽ���� �������Ӳ˵���
   popMenu=menu.GetSubMenu(0);  
   popMenu->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN,Point.x,Point.y,this);
}

void CDlgTask::OnDeleteTask()
{
   theApp.ShowLoading();
   int nRowCount = m_TaskBackList.GetItemCount();
   for (int i =0;i < nRowCount;i++)
   {
      if ( m_TaskBackList.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED )
      {
         if(i)
         {
            CString strID;
            strID = m_TaskBackList.GetItemText(i,0);
            BOOL bdelet = theApp.m_TaskList.DeleteItemByID(strID);
            if (bdelet)
            {
               m_TaskBackList.DeleteItem(i);
               theApp.OnShowDesktopAlert(_T("ɾ���ɹ�!"),COLOR_TIP_SUC,4,AfxGetMainWnd());
            } 
            else
            {
               theApp.OnShowDesktopAlert(_T("ɾ��ʧ��!"),COLOR_TIP_FAIL,4,AfxGetMainWnd());
            }
            break;
         } 
         else
         {
			 CSingleLock sinLock(&theApp.m_Mutex);
            if(sinLock.IsLocked())
            {
               if(IDOK == MessageBox(_T("ȷ����ֹ��ǰִ��������"),_T("��ʾ"),MB_OKCANCEL|MB_ICONQUESTION))
               {
                  OnBnClickedButton2();
                  m_TaskBackList.DeleteItem(i);
               }
            }
            else
            {
               CString strID;
               strID = m_TaskBackList.GetItemText(i,0);
               theApp.m_MutexMark = TRUE;
               BOOL bdelet = theApp.m_TaskList.DeleteItemByID(strID);
               if (bdelet)
               {
                  m_TaskBackList.DeleteItem(i);
                  theApp.OnShowDesktopAlert(_T("ɾ���ɹ�!"),COLOR_TIP_SUC,4,AfxGetMainWnd());
                  theApp.m_MutexMark = FALSE;
               } 
               else
               {
                  theApp.OnShowDesktopAlert(_T("ɾ��ʧ��!"),COLOR_TIP_FAIL,4,AfxGetMainWnd());
               }
               break;
            }
         }
      }
   }

   //SetTimer(TIME_ID_SAVEINFO,1000,NULL);
   theApp.SaveTaskInfo();
   theApp.CloseLoading();
}
