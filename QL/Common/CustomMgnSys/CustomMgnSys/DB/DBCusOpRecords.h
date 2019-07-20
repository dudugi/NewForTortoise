//�ͻ���Ϣ
#pragma once

#include <map>
#include <memory>
#ifdef USING_GRIDCTRL_MARK
#include "ClassData\CDataTableDlgDefine.h"
#endif // USING_GRIDCTRL_MARK

class CADOConn;
class CLDK;
class CDBVCustomerInfoData;
class CDBCusOpRecordsData :public CObject
{
	DECLARE_SERIAL( CDBCusOpRecordsData)//���л������л�����Ҫ��ӵ�����
public:
   int				   m_nID;	
   CString			m_strCusCode;	//�ͻ����
   CString			m_strCusName;	//�ͻ�����
   CString			m_strCusAddress;	//�ͻ���ַ
   CString			m_strCusPhone;	//�绰
   CString			m_strCusContacts;	//��ϵ��
   CString			m_strcPDMVersion;	//PDM�汾
   CString			m_strProvince;	//�ͻ���ַ
   int            m_isLocalDB;		//���ݿ��Ƿ����ڱ���
   CString        m_strServerPerson;//������Ա
   int            m_iClientNum;//�ͻ�������
   CString        m_strMemo;//��ע

   CString			m_cDbServerName;	//���ݿ�����
   CString			m_cDbServerIP;	//���ݿ�IP
   int			   m_iDbServerPort;	//���ݿ�˿�
   CString			m_cDbAccount;	//��¼�˻�
   CString			m_cDbPassword;	//��¼����

   CString			m_cBeginTime;	//��ʼʱ��
   CString			m_cTime;	//����ʱ��
   CString			m_cPerson;	//�����Ϣ
   CString			m_cModeData;	//����ģ�� 
   double         m_fChongZhiJE;//���γ�ֵ���
   CString        m_cOpType;//�������� 
public:
	CDBCusOpRecordsData();
	~CDBCusOpRecordsData();
	void operator = (CDBCusOpRecordsData *pData);
	void ResetData();
	void Copy(CDBCusOpRecordsData *pData);	
   void Copy(CDBVCustomerInfoData *pData);	
	BOOL GetAllDBInfo(CADOConn *pADOConn);				//��ȡ����������Ϣ	
	BOOL GetAllDBInfoByID(CADOConn *pADOConn);		//����ID��ȡ����������Ϣ 
   BOOL InsertDBInfo(CADOConn *pADOConn);
	static CDBCusOpRecordsData * Instance();				//��ȡ��ָ�룩ʵ��

private:
	static std::shared_ptr<CDBCusOpRecordsData> sm_inst;
};


class CDBCusOpRecordsList  : public CObList //CDataListMid
{
	DECLARE_SERIAL(CDBCusOpRecordsList)
public:
	CDBCusOpRecordsList();
	~CDBCusOpRecordsList();
	CDBCusOpRecordsData* GetItem(int nIndex);					//����������ȡItem
	CDBCusOpRecordsData* GetItemByID(int nID);	//����ID��ȡItem
	int GetIndexByID(int nID);				//����ID��ȡ����
	void AddItem(CDBCusOpRecordsData* pItem);					//���Item
	void DeleteItem(int nIndex);							//ɾ���̶�����Item

	void GetListFromDB(CADOConn *pADOConn);					//�����ݿ��ȡ����
	static CDBCusOpRecordsList * Instance();					//��ȡ��ָ�룩ʵ��

  BOOL GetGridDataByCusCode(__in CADOConn* pADOConn,__in CString strCusCode,__out MAP_GridCtrl_AllData& map_data);
  void ConvertDataToMap(const CDBCusOpRecordsData &oData,MAP_GridCtrl_RowData &row_data);

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
	static std::shared_ptr<CDBCusOpRecordsList> sm_inst;

};