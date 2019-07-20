//�û���Ϣ
#pragma once

#include "DataMid.h"
#include "DBKeyDef.h"
#include "DBKeyDef_V.h"
#include "DBKeyDef_Cust.h"
#include <map>
#include <vector>

class CADOConn;

class CDBLogInfoData :public CDataMid
{
	DECLARE_SERIAL( CDBLogInfoData)//���л������л�����Ҫ��ӵ�����
public:
	int				m_nID;			//����ID
	CString			m_strCate;		//���
	CString			m_strCode;		//���Ż��ʽ��/����
	COleDateTime	m_dDate;		//����ʱ��
	CString			m_strMaker;		//������
	CString			m_strType;		//��������
	CString			m_strAction;	//����Ĳ�����Ϊ
	CString			m_strInterFace; //��������
	CString         m_strProject;	//��Ŀ����
public:
	CDBLogInfoData();
	~CDBLogInfoData();
	void SetLogData(CString strCate,CString strCode,CString strMaker,CString strType,CString strAction,CString strInterFaceName = _T(""),CString strProjectName = _T(""));
	void ResetData();
	void Copy(CDBLogInfoData *pData);
	void Serialize(CArchive& ar);
	BOOL GetAllDBInfo(CADOConn *pADOConn);			//��ȡһ����¼��Ϣ
	BOOL InsertAllDBInfoByAct(CADOConn *pADOConn);	//����һ���¼�¼
	BOOL InsertAllDBInfoWithLocalTime(CADOConn *pADOConn);
	BOOL DelAllDBInfoByAct(CADOConn *pADOConn);		//�����û��˻�ɾ����¼

	CString GetInsertSQL();//���ز����SQL���

	void SetLogToDB(BOOL bLog);
	static CDBLogInfoData * Instance();			//��ȡ��ָ�룩ʵ��

private:
	static std::shared_ptr<CDBLogInfoData> sm_inst;
	BOOL m_bLog;		//�Ƿ��¼�����ݿ�
};

class CDBLogInfoList  : public CDataListMid
{
	DECLARE_SERIAL(CDBLogInfoList)
public:
	CDBLogInfoList();
	~CDBLogInfoList();
	CDBLogInfoData* GetItem(int nIndex);			//����������ȡItem
	void AddItem(CDBLogInfoData* pItem);			//���Item
	void DeleteItem(int nIndex);					//ɾ���̶�����Item
	static CDBLogInfoList * Instance();			//��ȡ��ָ�룩ʵ��

	//��ȡ������־ ���ݶ�����
	//add by lida 2017/07/11
	std::map<CString,CDBLogInfoData*> GetOrderLogByOrderCode(CADOConn *pADOConn,CString strOrderCode);

	//��ȡlog������Ҫ������
	void GetListData(CADOConn *pADOConn , CString startTime , CString endTime , CString strUser ,
		CString projectName, CString strKey , std::vector<CString> strOpTypeLst);

   void GetLogListData(CADOConn *pADOConn );
#ifdef USING_GRIDCTRL_MARK
	MAP_GridCtrl_AllData CreatrGridData();
#endif
private:
	static std::shared_ptr<CDBLogInfoList> sm_inst;
};
