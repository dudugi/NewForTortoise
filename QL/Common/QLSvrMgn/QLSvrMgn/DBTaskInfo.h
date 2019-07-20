#pragma once
#include "DataMid.h"
class CDBTaskInfo :public CDataMid
{
  DECLARE_SERIAL( CDBTaskInfo)//���л������л�����Ҫ��ӵ�����
public:
   CString m_strID; //����ID ��Ψһ��
   CTime m_tStartTime;//��������ʱ�� ��������ʾ��ʼʱ�䣬ʵ��ִ�а����ڿ�ʼʱ��
   CTime m_tNextStartTime;//������ʵ�ʿ�ʼʱ�䣨����˳��ʱ���׼��ʼʱ��᲻һ�£�
   CTime m_tStdStartTime;//��׼��ʼʱ��(Ԥ��ʱ��)
   BOOL    m_bFileBackup;    //�����ļ�����
   CString m_strCyc;        //��������:*��־ ȡʱ��
   CString m_strCycType;    //�������ͣ�d/z/y:��/��/��
   CString m_strOldPath;   //Դ·��
   CString m_strNewDirPath; //Ŀ��·��
   BOOL m_bAutoBackUp;
   int m_nState;   //����ִ��״̬
   CString m_strTaskType;   //��������
   CTime m_tLastExecutionTime;//�ϴ�ִ�гɹ�ʱ��
   int m_nAutoDeleteTime;     //��������ʱ��

public:
   CDBTaskInfo(void);
   ~CDBTaskInfo(void);
   void Copy(CDBTaskInfo *pData);
   CDBTaskInfo* operator =(CDBTaskInfo * str)//��ֵ�����
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
   DECLARE_SERIAL( CDBTaskInfoList);//���л������л�����Ҫ��ӵ�����
public:
   CDBTaskInfoList(void);
   ~CDBTaskInfoList(void);
   void addItem(CDBTaskInfo *DbTask);
   BOOL deleteItem(int nIndex);
   CDBTaskInfoList& operator =(const CDBTaskInfoList& str)//��ֵ�����
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

