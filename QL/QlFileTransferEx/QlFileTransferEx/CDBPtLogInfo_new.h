#pragma once
#include "stdafx.h"
#include "ADOConnEx.h"
#include "ClassDB\DBPersonInfo.h"
#include "DBDef.h"
#include "ClassDB\DBCustomInfo.h"
#include "CommonAPI.h"

class CDBPtLogInfo_New
{
//����
public:
   int m_nTheardEndFlag;//�߳̽���������־
   CString m_strConnectSql;
private:
   typedef struct STRUCT_LogInfo{
      STRUCT_LogInfo()
      {
          m_strCate = _T("");
          m_strCode = _T("");
          m_strMemo = _T("");
          m_strType = _T("");
          m_strMaker= _T("");
      }
      CString m_strCate;      //���
      CString m_strCode;      //����
      CString m_strMemo;      //��ע
      CString m_strType;      //����
      CString m_strMaker;     //������
   }STRUCT_LOGINFO;

   map<int, STRUCT_LOGINFO> m_LogInfo; //��־��Ϣ
   CString m_strMacAddr; //Mac��ַ
protected:
//����
public:
   CDBPtLogInfo_New();

   ~CDBPtLogInfo_New();
   void Clear();
   void ResetData();
   void SetDataLogInfo(CADOConnEx *pADOConn,CString strCate, CString strCode ,CString strMemo,CString strType,CString strMakerID,int nLoginType); //������־����
   BOOL InsertSQL_LogInfo(CADOConnEx *pADOConn);//��־��Ϣ

   static CDBPtLogInfo_New *Instance();
private:
   typedef enum S_FileTrans_LoginType{
      En_Login_User = 0,//Ա����¼
      En_Login_Custom,//�ͻ���¼
   }S_FILETRANS_LOGINTYPE;

   static std::shared_ptr<CDBPtLogInfo_New> sm_inst;
   BOOL m_bLog;		//�Ƿ��¼�����ݿ�
};