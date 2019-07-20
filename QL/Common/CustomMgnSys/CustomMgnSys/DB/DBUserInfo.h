//�û���Ϣ
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
	DECLARE_SERIAL( CDBUserInfoData)//���л������л�����Ҫ��ӵ�����
public:
	int				m_nID;	
	CString			m_strUserID;	//�û�ID
	CString			m_strUserPwd;	//����
	CString			m_strUserName;	
	COleDateTime    m_tUserDate;
	COleDateTime    m_tLastLoadTime;
	int             m_nUserState;		//ע����ʶ 0==����,1==ע��

public:
	CDBUserInfoData();
	~CDBUserInfoData();
	void operator = (CDBUserInfoData *pData);
	void ResetData();
	void Copy(CDBUserInfoData *pData);	
	BOOL GetAllDBInfo(CADOConn *pADOConn);				//��ȡ����������Ϣ
	BOOL InsertAllDBInfoByUserID(CADOConn *pADOConn);	//���롾�������¼�¼
	BOOL UpdateAllDBInfoByUserID(CADOConn *pADOConn);	//�����û��˻����¡���������¼
	BOOL DelAllDBInfoByUserID(CADOConn *pADOConn);		//�����û��˻�ɾ������������¼
	BOOL GetAllDBInfoByUserID(CADOConn *pADOConn);		//�����û��˻���ȡ����������Ϣ 

	static CDBUserInfoData * Instance();				//��ȡ��ָ�룩ʵ��

private:
	static std::shared_ptr<CDBUserInfoData> sm_inst;
};

class CDBUserInfoList  : public CObList //CDataListMid
{
	DECLARE_SERIAL(CDBUserInfoList)
public:
	CDBUserInfoList();
	~CDBUserInfoList();
	CDBUserInfoData* GetItem(int nIndex);					//����������ȡItem
	CDBUserInfoData* GetItemByUserID(CString strUserID);	//�����û��˻���ȡItem
	int GetIndexByUserID(CString strUserID);				//�����û��˻���ȡ����
	void AddItem(CDBUserInfoData* pItem);					//���Item
	void DeleteItem(int nIndex);							//ɾ���̶�����Item

	void GetListFromDB(CADOConn *pADOConn);					//�����ݿ��ȡ����
	static CDBUserInfoList * Instance();					//��ȡ��ָ�룩ʵ��
      
	BOOL ModifyUserPassword(CADOConn *pADOConn,CDBUserInfoData* pData);		//�޸����� add by lida 2017/08/04

   CString GetUserNameByUserID(CADOConn *pADOConn,CString userID);//����Ա����Ż�ȡԱ������ yangjr 2017-7-5

   std::map<CString,CString> GetUsrIDAndName(CADOConn *pADOConn);	//��ȡ���е���Ա��Ϣ map<UserID,UserName> lida 2017/09/08

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