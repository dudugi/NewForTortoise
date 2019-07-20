//用户信息
#pragma once

//#include "DataMid.h"
#include <map>
#include <memory>
#ifdef USING_GRIDCTRL_MARK
#include "ClassData\CDataTableDlgDefine.h"
#endif // USING_GRIDCTRL_MARK

class CADOConn;
class CDBUserInfoData :public CObject
{
	DECLARE_SERIAL( CDBUserInfoData)//序列化（串行化）需要添加的声明
public:
	int				m_nID;	
	CString			m_strUserID;	//用户ID
	CString			m_strUserPwd;	//密码
	CString			m_strUserName;	
	COleDateTime    m_tUserDate;
	COleDateTime    m_tLastLoadTime;
	int             m_nUserState;		//注销标识 0==正常,1==注销

public:
	CDBUserInfoData();
	~CDBUserInfoData();
	void operator = (CDBUserInfoData *pData);
	void ResetData();
	void Copy(CDBUserInfoData *pData);	
	BOOL GetAllDBInfo(CADOConn *pADOConn);				//获取【整条】信息
	BOOL InsertAllDBInfoByUserID(CADOConn *pADOConn);	//插入【整条】新记录
	BOOL UpdateAllDBInfoByUserID(CADOConn *pADOConn);	//根据用户账户更新【整条】记录
	BOOL DelAllDBInfoByUserID(CADOConn *pADOConn);		//根据用户账户删除【整条】记录
	BOOL GetAllDBInfoByUserID(CADOConn *pADOConn);		//根据用户账户获取【整条】信息 

	static CDBUserInfoData * Instance();				//获取（指针）实例

private:
	static std::shared_ptr<CDBUserInfoData> sm_inst;
};

class CDBUserInfoList  : public CObList //CDataListMid
{
	DECLARE_SERIAL(CDBUserInfoList)
public:
	CDBUserInfoList();
	~CDBUserInfoList();
	CDBUserInfoData* GetItem(int nIndex);					//根据索引获取Item
	CDBUserInfoData* GetItemByUserID(CString strUserID);	//根据用户账户获取Item
	int GetIndexByUserID(CString strUserID);				//根据用户账户获取索引
	void AddItem(CDBUserInfoData* pItem);					//添加Item
	void DeleteItem(int nIndex);							//删除固定索引Item

	void GetListFromDB(CADOConn *pADOConn);					//从数据库获取链表
	static CDBUserInfoList * Instance();					//获取（指针）实例
      
	BOOL ModifyUserPassword(CADOConn *pADOConn,CDBUserInfoData* pData);		//修改密码 add by lida 2017/08/04

   CString GetUserNameByUserID(CADOConn *pADOConn,CString userID);//根据员工编号获取员工姓名 yangjr 2017-7-5

   std::map<CString,CString> GetUsrIDAndName(CADOConn *pADOConn);	//获取所有的人员信息 map<UserID,UserName> lida 2017/09/08

#ifdef USING_GRIDCTRL_MARK
   MAP_GridCtrl_AllData CreateGridData();
#endif // USING_GRIDCTRL_MARK

protected:
   inline void Empty()
   {
      for (int j=(GetCount()-1);j>=0;j--)
      {
         CObject *pData =(CObject *)GetAt(FindIndex(j));
         if (pData)
         {
            delete pData;
            pData = NULL;
         }
      }

      RemoveAll();
   }

private:
	static std::shared_ptr<CDBUserInfoList> sm_inst;


};