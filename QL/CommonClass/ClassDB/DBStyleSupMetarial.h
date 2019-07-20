#pragma once
#include "DataMid.h"

class CADOConn;
class CDBStyleSupMetarial :public CDataMid
{
   DECLARE_SERIAL( CDBStyleSupMetarial)//���л������л�����Ҫ��ӵ�����
public:
   CDBStyleSupMetarial(void);
   ~CDBStyleSupMetarial(void);

public:
   int         m_id;
   CString     m_strStyleNo;
   CString     m_strName;
   int         m_nNumber;
   double      m_nPrice;
   double      m_nSumPrice;
   CString     m_strMemo;
public:
   void ResetData();
   void Copy(CDBStyleSupMetarial *pData);
   void GetAllDBInfo(CADOConn* pADOConn);

   BOOL InsetAllDBInfo(CADOConn* pADOConn);
   BOOL UpdateAllDBInfo(CADOConn* pADOConn); //����ID
   BOOL DeleteAllDBInfo(CADOConn* pADOConn); //����ID

   CString GetInsertSql();
   CString GetUpdateSql();
   CString GetDeleteSql();
};


class CDBStyleSupMetarialList :public CDataListMid
{
   DECLARE_SERIAL( CDBStyleSupMetarialList)//���л������л�����Ҫ��ӵ�����
public:
   CDBStyleSupMetarialList(void);
   ~CDBStyleSupMetarialList(void);

   static CDBStyleSupMetarialList * Instance();//��ȡ��ָ�룩ʵ��

   CDBStyleSupMetarial* GetItem(int nIndex);			//����������ȡItem 
   void AddItem(CDBStyleSupMetarial* pItem);			//���Item
   void DeleteItem(int nIndex);					//ɾ���̶�����Item
   
public:
#ifdef USING_GRIDCTRL_MARK
   BOOL GetStyleMetarialInfo(CADOConn* pADOConn,CString strStyleNo,MAP_GridCtrl_AllData& all_data);

   //����ǰɾ���ÿ�žɵ�ԭ����Ϣ��Ȼ�����α����µģ����������߼��Ƚϼ�
   BOOL SaveStyleMetarialInfo(CADOConn* pADOConn,CString strStyleNo,MAP_GridCtrl_AllData all_data);      
#endif
   BOOL IsStyleMetarialInfoExist(CADOConn* pADOConn,CString strStyleNo);
   BOOL ClearStyleMetarialInfo(CADOConn* pADOConn,CString strStyleNo);
   BOOL SaveStyleMetarial(CADOConn* pADOConn,CString strStyleNo);
   void GetDBInfoFromDB(CADOConn *pADOConn);
private:
   static std::shared_ptr<CDBStyleSupMetarialList> sm_inst;
};