#include "StdAfx.h"
#include "DBTaskInfo.h"

IMPLEMENT_SERIAL(CDBTaskInfo,  CDataMid, 1)
IMPLEMENT_SERIAL(CDBTaskInfoList,  CDataListMid, 1)

CDBTaskInfo::CDBTaskInfo(void)
{
}


CDBTaskInfo::~CDBTaskInfo(void)
{

}

void CDBTaskInfo::Copy(CDBTaskInfo *pData)
{
   ASSERT(pData != NULL);
   CDataMid::Copy(pData);

   m_strID = pData->m_strID; 
   m_tStartTime = pData->m_tStartTime;
   m_tNextStartTime = pData->m_tNextStartTime;
   m_bFileBackup = pData->m_bFileBackup;    
   m_strCyc = pData->m_strCyc;        
   m_strCycType = pData->m_strCycType;    
   m_strOldPath = pData->m_strOldPath;   
   m_strNewDirPath = pData->m_strNewDirPath; 
   m_tStdStartTime = pData->m_tStdStartTime;
   m_bAutoBackUp  = pData->m_bAutoBackUp;
   m_nState =  pData->m_nState;
   m_strTaskType = pData->m_strTaskType;
   m_tLastExecutionTime = pData->m_tLastExecutionTime;
   m_nAutoDeleteTime  = pData->m_nAutoDeleteTime;
}

void CDBTaskInfo::ResetData()
{
   m_strID = _T(""); 
   m_tStartTime = NULL;
   m_tNextStartTime = NULL;
   m_tStdStartTime = NULL;
   m_bFileBackup = FALSE;    
   m_strCyc = _T("");        
   m_strCycType = _T("");    
   m_strOldPath = _T("");   
   m_strNewDirPath = _T(""); 
   m_bAutoBackUp = FALSE;
   m_nState = 0;
   m_strTaskType = _T("");
   m_tLastExecutionTime = NULL;
   m_nAutoDeleteTime = 0;
}

CDBTaskInfoList::CDBTaskInfoList(void)
{

}

CDBTaskInfoList::~CDBTaskInfoList(void)
{

}

void CDBTaskInfoList::addItem(CDBTaskInfo *DbTask)
{
   CDBTaskInfo *DBTask= new CDBTaskInfo;
   DBTask->Copy(DbTask);
   int nCount = this->GetCount();
   BOOL bMark = FALSE;
   for(int nIndex = 0;nIndex<nCount;nIndex++)
   {
      CDBTaskInfo *DBTaskInfo =(CDBTaskInfo *)GetAt(FindIndex(nIndex));
      if (DBTaskInfo->m_tNextStartTime>= DBTask->m_tNextStartTime)//依据开始时间排序
      {
         POSITION pos = FindIndex(nIndex);
         InsertBefore(pos,DBTask);
         bMark = TRUE;
         break;
      }

   }

   if (!bMark)
   {
      AddTail(DBTask);
   }
}

BOOL CDBTaskInfoList::deleteItem(int nIndex)
{
   if (nIndex<0||nIndex>GetCount())
      return FALSE;
   CDBTaskInfo *pObject=(CDBTaskInfo*)GetAt(FindIndex(nIndex));
   delete pObject;
   pObject=NULL;
   RemoveAt(FindIndex(nIndex));
   return TRUE;
}

BOOL CDBTaskInfoList::DeleteItemByID( CString strID )
{
   if (strID.IsEmpty())
   {
      return FALSE;
   }
   for (int i =0;i<GetCount();i++)
   {
      CDBTaskInfo *pDBTask = ( CDBTaskInfo *)GetAt(FindIndex(i));
      if (pDBTask)
      {
         if (pDBTask->m_strID == strID)
         {
          deleteItem(i);
          return TRUE;
         }
      }
      else
      {
         return FALSE;
      }
   }

   return FALSE;
}

CString  CDBTaskInfoList::GetPathByLastExceTimeAndIDAnd( CString strID,CTime &tm ,bool bAutoBack)
{
	CString str;
	for (int nIndex = 0;nIndex < GetCount();++nIndex)
	{
		CDBTaskInfo *pDbTask = (CDBTaskInfo *)GetAt(this->FindIndex(nIndex));
		if (pDbTask != NULL && pDbTask->m_strID == strID && pDbTask->m_tLastExecutionTime.GetYear()== tm.GetYear() && pDbTask->m_tLastExecutionTime.GetMonth() == tm.GetMonth()
			&& pDbTask->m_tLastExecutionTime.GetDay() == tm.GetDay() && pDbTask->m_tLastExecutionTime.GetHour() == tm.GetHour() && pDbTask->m_tLastExecutionTime.GetMinute() == tm.GetMinute() && pDbTask->m_bAutoBackUp == TRUE)
		{
			if (pDbTask->m_bAutoBackUp)
			{
				CString strTime;
				strTime = pDbTask->m_tLastExecutionTime.Format(_T("%Y_%m_%d_%H时%M分"));
			    str =pDbTask->m_strNewDirPath+_T("\\")+pDbTask->m_strID+_T("\\")+_T("FullBackUp")+_T("\\")+strTime;
			}
			else
			{
				CString strTime;
				strTime = pDbTask->m_tLastExecutionTime.Format(_T("%Y_%m_%d_%H时%M分"));
				str =pDbTask->m_strNewDirPath+_T("\\")+pDbTask->m_strID+_T("\\")+_T("XBackUp")+_T("\\")+strTime;
			}
		}
	}

	return str;
}
