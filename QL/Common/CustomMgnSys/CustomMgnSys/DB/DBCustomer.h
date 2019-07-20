//�ͻ���Ϣ
#pragma once

#include <map>
#include <memory>
#ifdef USING_GRIDCTRL_MARK
#include "ClassData\CDataTableDlgDefine.h"
#endif // USING_GRIDCTRL_MARK

class CADOConn;
class CLDK;
//�ͻ��������ݱ�
class CDBCustomBaseData :public CObject
{
   DECLARE_SERIAL( CDBCustomBaseData)//���л������л�����Ҫ��ӵ�����
public:
   int				m_nID;	
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
public:
   CDBCustomBaseData();
   ~CDBCustomBaseData();
   void operator = (CDBCustomBaseData *pData);
   void ResetData();
   void Copy(CDBCustomBaseData *pData);	
   BOOL GetAllDBInfo(CADOConn *pADOConn);				//��ȡ����������Ϣ
   BOOL InsertAllDBInfo(CADOConn *pADOConn);	//���롾�������¼�¼
   BOOL UpdateAllDBInfoByCusCode(CADOConn *pADOConn);	//���ݿͻ���Ÿ��¡���������¼
   BOOL DelAllDBInfoByCusCode(CADOConn *pADOConn);		//���ݿͻ����ɾ������������¼
   BOOL GetAllDBInfoByCusCode(CADOConn *pADOConn);		//���ݿͻ���Ż�ȡ����������Ϣ 

   static CDBCustomBaseData * Instance();				//��ȡ��ָ�룩ʵ��

private:
   static std::shared_ptr<CDBCustomBaseData> sm_inst;
};

//�ͻ����ݿ����ñ�
class CDBCustomDbData :public CObject
{
   DECLARE_SERIAL( CDBCustomDbData)//���л������л�����Ҫ��ӵ�����
public:  
   CString			m_strCusCode;	   //�ͻ����
   CString			m_cDbServerName;	//���ݿ�����
   CString			m_cDbServerIP;	//���ݿ�IP
   int			   m_iDbServerPort;	//���ݿ�˿�
   CString			m_cDbAccount;	//��¼�˻�
   CString			m_cDbPassword;	//��¼����
 
public:
   CDBCustomDbData();
   ~CDBCustomDbData();
   void operator = (CDBCustomDbData *pData);
   void ResetData();
   void Copy(CDBCustomDbData *pData);	
   BOOL GetAllDBInfo(CADOConn *pADOConn);				//��ȡ����������Ϣ
   BOOL InsertAllDBInfo(CADOConn *pADOConn);	//���롾�������¼�¼
   BOOL UpdateAllDBInfoByCusCode(CADOConn *pADOConn);	//���ݿͻ���Ÿ��¡���������¼
   BOOL DelAllDBInfoByCusCode(CADOConn *pADOConn);		//���ݿͻ����ɾ������������¼
   BOOL GetAllDBInfoByCusCode(CADOConn *pADOConn);		//���ݿͻ���Ż�ȡ����������Ϣ 

   static CDBCustomDbData * Instance();				//��ȡ��ָ�룩ʵ��

private:
   static std::shared_ptr<CDBCustomDbData> sm_inst;
};

//�ͻ��������ݱ�
class CDBCustomEncryptData :public CObject
{
   DECLARE_SERIAL( CDBCustomEncryptData)//���л������л�����Ҫ��ӵ�����
public:  
   CString			m_strCusCode;	//�ͻ����
   CString			m_cData1;	//��������1
   CString			m_cData2;	//��������2
   CString			m_cData3;	//��������3
   CString			m_cData4;	//��������4
public:
   CDBCustomEncryptData();
   ~CDBCustomEncryptData();
   void operator = (CDBCustomEncryptData *pData);
   void ResetData();
   void Copy(CDBCustomEncryptData *pData);	
   BOOL GetAllDBInfo(CADOConn *pADOConn);				//��ȡ����������Ϣ
   BOOL InsertAllDBInfo(CADOConn *pADOConn);	//���롾�������¼�¼
   BOOL UpdateAllDBInfoByCusCode(CADOConn *pADOConn);	//���ݿͻ���Ÿ��¡���������¼
   BOOL DelAllDBInfoByCusCode(CADOConn *pADOConn);		//���ݿͻ����ɾ������������¼
   BOOL GetAllDBInfoByCusCode(CADOConn *pADOConn);		//���ݿͻ���Ż�ȡ����������Ϣ 

   static CDBCustomEncryptData * Instance();				//��ȡ��ָ�룩ʵ��

private:
   static std::shared_ptr<CDBCustomEncryptData> sm_inst;
};

class CDBVCustomerInfoData :public CObject
{
	DECLARE_SERIAL( CDBVCustomerInfoData)//���л������л�����Ҫ��ӵ�����
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
   CString        m_strMemo;//��ע

   CString			m_cDbServerName;	//���ݿ�����
   CString			m_cDbServerIP;	//���ݿ�IP
   int			   m_iDbServerPort;	//���ݿ�˿�
   CString			m_cDbAccount;	//��¼�˻�
   CString			m_cDbPassword;	//��¼����

   CString			m_cData1;	//��������1
   CString			m_cData2;	//��������2
   CString			m_cData3;	//��������3
   CString			m_cData4;	//��������4 

   //�������ݿ������ yangjr 2018/8/30
   CString			m_cBeginTime;	//��ʼʱ��
   CString			m_cTime;	//����ʱ��
   CString			m_cPerson;	//�����Ϣ
   CString			m_cModeData;	//����ģ�� 
   int            m_iClientNum;//�ͻ�������

   double         m_fChongZhiJE;//���γ�ֵ���
public:
	CDBVCustomerInfoData();
	~CDBVCustomerInfoData();
	void operator = (CDBVCustomerInfoData *pData);
	void ResetData();
	void Copy(CDBVCustomerInfoData *pData);	
	BOOL GetAllDBInfo(CADOConn *pADOConn);				//��ȡ����������Ϣ	
	BOOL GetAllDBInfoByCusCode(CADOConn *pADOConn);		//���ݿͻ���ȡ����������Ϣ 

   CString GetInsertSql();
   CString GetUpdateSql();

   BOOL EncryptString(__in CLDK *pLdk);
   BOOL DecryptString(__in CLDK *pLdk);
	static CDBVCustomerInfoData * Instance();				//��ȡ��ָ�룩ʵ��

private:
	static std::shared_ptr<CDBVCustomerInfoData> sm_inst;
};


class CDBVCustomerInfoList  : public CObList //CDataListMid
{
	DECLARE_SERIAL(CDBVCustomerInfoList)
public:
	CDBVCustomerInfoList();
	~CDBVCustomerInfoList();
	CDBVCustomerInfoData* GetItem(int nIndex);					//����������ȡItem
	CDBVCustomerInfoData* GetItemByCusCode(CString strCusCode);	//���ݿͻ������ȡItem
	int GetIndexByCusCode(CString strCusCode);				//���ݿͻ������ȡ����
	void AddItem(CDBVCustomerInfoData* pItem);					//���Item
	void DeleteItem(int nIndex);							//ɾ���̶�����Item

	void GetListFromDB(CADOConn *pADOConn);					//�����ݿ��ȡ����
	static CDBVCustomerInfoList * Instance();					//��ȡ��ָ�룩ʵ��

   BOOL GetAllCustomerGridData(__in CADOConn* pADOConn,__in CLDK *pLdk,__out MAP_GridCtrl_AllData& map_data);

   BOOL GetExpiringCustomerGridData(__in CADOConn* pADOConn,__in int iDays,__in CLDK *pLdk,__out MAP_GridCtrl_AllData& map_data); //��������

   BOOL GetExpiredCustomerGridData(__in CADOConn* pADOConn,__in CLDK *pLdk,__out MAP_GridCtrl_AllData& map_data);  //�ѹ���

   void ConvertDataToMap(const CDBVCustomerInfoData &oData,MAP_GridCtrl_RowData &row_data);

   BOOL GetCustomerDataByID(__in CADOConn* pADOConn,__in int iID,__in CLDK *pLdk,__out CDBVCustomerInfoData* pData);

   CString GetDelSql_CustomerDataByCusCode(__in vector<CString> vecCusCode);

   BOOL CheckCusCodeExists(__in CADOConn* pADOConn,__in CString strCusCode);

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
	static std::shared_ptr<CDBVCustomerInfoList> sm_inst;

};