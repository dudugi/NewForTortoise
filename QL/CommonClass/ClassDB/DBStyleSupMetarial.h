#pragma once
#include "DataMid.h"

class CADOConn;
class CDBStyleSupMetarial :public CDataMid
{
   DECLARE_SERIAL( CDBStyleSupMetarial)//序列化（串行化）需要添加的声明
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
   BOOL UpdateAllDBInfo(CADOConn* pADOConn); //根据ID
   BOOL DeleteAllDBInfo(CADOConn* pADOConn); //根据ID

   CString GetInsertSql();
   CString GetUpdateSql();
   CString GetDeleteSql();
};


class CDBStyleSupMetarialList :public CDataListMid
{
   DECLARE_SERIAL( CDBStyleSupMetarialList)//序列化（串行化）需要添加的声明
public:
   CDBStyleSupMetarialList(void);
   ~CDBStyleSupMetarialList(void);

   static CDBStyleSupMetarialList * Instance();//获取（指针）实例

   CDBStyleSupMetarial* GetItem(int nIndex);			//根据索引获取Item 
   void AddItem(CDBStyleSupMetarial* pItem);			//添加Item
   void DeleteItem(int nIndex);					//删除固定索引Item
   
public:
#ifdef USING_GRIDCTRL_MARK
   BOOL GetStyleMetarialInfo(CADOConn* pADOConn,CString strStyleNo,MAP_GridCtrl_AllData& all_data);

   //保存前删除该款号旧的原料信息，然后依次保存新的，这样处理逻辑比较简单
   BOOL SaveStyleMetarialInfo(CADOConn* pADOConn,CString strStyleNo,MAP_GridCtrl_AllData all_data);      
#endif
   BOOL IsStyleMetarialInfoExist(CADOConn* pADOConn,CString strStyleNo);
   BOOL ClearStyleMetarialInfo(CADOConn* pADOConn,CString strStyleNo);
   BOOL SaveStyleMetarial(CADOConn* pADOConn,CString strStyleNo);
   void GetDBInfoFromDB(CADOConn *pADOConn);
private:
   static std::shared_ptr<CDBStyleSupMetarialList> sm_inst;
};