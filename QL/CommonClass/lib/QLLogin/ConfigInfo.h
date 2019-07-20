#pragma once
#include "DataMid.h"

/************************************************************************
 * �������ڣ�2018/01/15     ���ߣ�zhangyx
 * CConfigInfo
 * Ŀ�ģ��洢�û���������Ϣ
 ************************************************************************/


//���öԻ������Ϣ
#define USERDEFINED							_T("�û��Զ���")
#define USERNAME							_T("�û���")
#define USERPASSWORD						_T("�û�����")
#define REMEMBERPASSWORD					_T("��ס����")
#define AUTOMATICLOGON						_T("�Զ���¼")
#define	IPADDRESS							_T("IP��ַ��URL")
#define PORTONE                             _T("�˿�1")
#define PORTTWO								_T("�˿�2")
#define DATABASENAME						_T("���ݿ�����")
#define DATABASEACCOUNT						_T("���ݿ��˻�")
#define DATABASEPASSWORD					_T("���ݿ�����")
#define APPLYACCOUNT						_T("�򿪷��������˺�")


class CConfigInfo : public CDataMid
{
	DECLARE_SERIAL(CConfigInfo)//���л������л�����Ҫ��ӵ�����
public:
	CConfigInfo(void);
	~CConfigInfo(void);
	void ResetData();
	void Serialize(CArchive& ar);
	void Copy(CConfigInfo *pData);

public:
	CString m_strUserDefinedName;	//�Զ���
	CString m_strUserID;			//�û�ID
	CString m_strUserPassword;		//�û�����
	BOOL m_bRememberPassword;		//�Ƿ��ס����
	BOOL m_bAutomaticLogon;			//�Ƿ��Զ���¼
	CString m_strIPAddress;			//IP��ַ
	CString m_strPort1;				//�˿�1
	CString m_strPort2;				//�˿�2
	CString m_strDatabaseName;		//���ݿ�����
	CString m_strDatabaseAccount;	//���ݿ��˻�
	CString m_strDatabasePassword;	//���ݿ�����
	BOOL    m_bApplyAccount;		//�Ƿ��򿪷�������
   CString m_strFtpIP;           //����Ftp��ַ    add anjie by 2018/09/27
   BOOL    m_bHttpMode;          //�Ƿ�ʹ����HTTPģʽ Ĭ��ΪFALSE
};

class CConfigInfoList: public CDataListMid
{
	DECLARE_SERIAL(CConfigInfoList)
public:
	CConfigInfoList();
	~CConfigInfoList();
public:
	void	Serialize(CArchive& ar);
	CConfigInfo* GetItemByIP(CString strIP);	//�����û�IP��ȡItem
	CConfigInfo* GetItem(int nIndex);			//����������ȡItem
	void AddItem(CConfigInfo* pItem);			//���Item
	void DeleteItem(int nIndex);				//ɾ���̶�����Item
   CConfigInfo* GetItemByApply(CString strstrUserDefinedName,CString strIPAddress,CString strDatabaseName);	//�����û�IP��ȡItem
   void Copy(CConfigInfoList *pList);
};
