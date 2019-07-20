#pragma once
#include "DataMid.h"
class CADOConn;

#define DB_TABLE_DesignData		            _T("DesignData")          // �ư�����
                                                                          
#define DBDesignData_key_ID			         _T("ID")		              // ����ID
#define DBDesignData_key_Name	    	         _T("cName")		           // ����
#define DBDesignData_key_cSavedUserID        _T("cSavedUserID")        // ������
#define DBDesignData_key_cSaveTime           _T("cSaveTime")           // ����ʱ��
#define DBDesignData_key_cData               _T("cData")               // ����ʱ��

/*************************************************
// <�ļ�>: DBDesignData.h
// <˵��>: �ư����DB��
// <����>: huangym(ͷ�ļ�ע��)
// <����>: 2019/02/21 16:09:22
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/

class CDBDesignData :
   public CDataMid
{
   DECLARE_SERIAL(CDBDesignData)                                       // ���л������л�����Ҫ��ӵ�����
public:
   CDBDesignData();
   ~CDBDesignData();;
   void ResetData();                                                   // ��������
   BOOL UpdateDBInfo(CADOConn * pADOConn);                             // ��������
   BOOL GetAllDBInfo(CADOConn *pADOConn);		                          // ��ȡ����������Ϣ
   void Copy(CDBDesignData *pData);                                    // ��������

   
   CString GetInsertSQL();                                             // ��ȡ�����SQL���
   static CDBDesignData * Instance();                                  // ��ȡ��ָ�룩ʵ��
   BOOL UpdateAllDBInfoByID(CADOConn * pADOConn);                      // �������ݵ����ݿ�
   BOOL InsertAllDBInfoByID(CADOConn * pADOConn);                      // �������ݵ����ݿ�
private:
   static std::shared_ptr<CDBDesignData> sm_inst;

public:
   __int64		               m_nID;                                   // ����ID
   CString                    m_strName;                               // ����
   CString                    m_strSavedUserID;                        // �û�ID
   CString                    m_strSaveTime;                           // ����ʱ��
   CString                    m_strData;                                 // ����
};


class CDBDesignDataList : public CDataListMid
{
   DECLARE_SERIAL(CDBDesignDataList)
public:
   CDBDesignDataList();
   ~CDBDesignDataList();
   CDBDesignData*  GetItem(int nIndex);
   void    AddItem(CDBDesignData* pItem);
   void    DeleteItem(int nIndex);
   BOOL    DeleteUserByUserID(CADOConn * pADOConn, vector<CString> vecUserID);

   static CDBDesignDataList * Instance();		                          //��ȡ��ָ�룩ʵ��
                                                                       //���ɱ������
   MAP_GridCtrl_AllData CreateGridData(const CString & strUserDuty = _T(""));

private:
   static std::shared_ptr<CDBDesignDataList> sm_inst;
};
