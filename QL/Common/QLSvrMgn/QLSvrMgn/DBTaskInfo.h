#pragma once
#include "DataMid.h"
class CDBTaskInfo :public CDataMid
{
  DECLARE_SERIAL( CDBTaskInfo)//序列化（串行化）需要添加的声明
public:
   CString m_strID; //任务ID ：唯一性
   CTime m_tStartTime;//启动任务时间 仅用来显示开始时间，实际执行按周期开始时间
   CTime m_tNextStartTime;//周期性实际开始时间（任务顺延时与标准开始时间会不一致）
   CTime m_tStdStartTime;//标准开始时间(预定时间)
   BOOL    m_bFileBackup;    //订单文件备份
   CString m_strCyc;        //任务周期:*标志 取时间
   CString m_strCycType;    //周期类型：d/z/y:天/周/月
   CString m_strOldPath;   //源路径
   CString m_strNewDirPath; //目标路径
   BOOL m_bAutoBackUp;
   int m_nState;   //任务执行状态
   CString m_strTaskType;   //任务类型
   CTime m_tLastExecutionTime;//上次执行成功时间
   int m_nAutoDeleteTime;     //任务清理时间

public:
   CDBTaskInfo(void);
   ~CDBTaskInfo(void);
   void Copy(CDBTaskInfo *pData);
   CDBTaskInfo* operator =(CDBTaskInfo * str)//赋值运算符
   {
      CDataMid::Copy(str);
      m_strID = str->m_strID; 
      m_tStartTime = str->m_tStartTime;
      m_tNextStartTime = str->m_tNextStartTime;
      m_tStdStartTime = str->m_tStdStartTime;
      m_bFileBackup = str->m_bFileBackup;    
      m_strCyc = str->m_strCyc;        
      m_strCycType = str->m_strCycType;    
      m_strOldPath = str->m_strOldPath;   
      m_strNewDirPath = str->m_strNewDirPath; 
      m_bAutoBackUp = str->m_bAutoBackUp;
      m_nState = str->m_nState;
      m_strTaskType = str->m_strTaskType;
      m_tLastExecutionTime = str->m_tLastExecutionTime;
      return this;
   }
   void ResetData();
};

class CDBTaskInfoList :public CDataListMid
{
   DECLARE_SERIAL( CDBTaskInfoList);//序列化（串行化）需要添加的声明
public:
   CDBTaskInfoList(void);
   ~CDBTaskInfoList(void);
   void addItem(CDBTaskInfo *DbTask);
   BOOL deleteItem(int nIndex);
   CDBTaskInfoList& operator =(const CDBTaskInfoList& str)//赋值运算符
   {
     for (int i = 0;i<str.GetCount();i++)
     {
        CDBTaskInfo * pDBTask = (CDBTaskInfo *)str.GetAt(str.FindIndex(i));
        this->addItem(pDBTask);
     }
      return *this;
   }

   BOOL DeleteItemByID(CString strID);
   CString GetPathByLastExceTimeAndIDAnd( CString strID,CTime &tm ,bool bAutoBack);
};

