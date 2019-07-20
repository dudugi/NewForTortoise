#pragma once
#include <afxstr.h>
#include <afxdd_.h>
#include "ConfigInfo.h"


typedef enum EnLoginReturn_Type
{
	RETURN_SUCCESS,				//��½�ɹ�
	RETURN_EMPTY_ACCOUNT,		//�˻�Ϊ��
	RETURN_EMPTY_PASSWD,			//����Ϊ��
	RETURN_WRITTEN_OFF,			//�˻���ע��
	RETURN_POWER_ERROR,			//Ȩ�޳���
	RETURN_ERROR_ACCOUNT_PWD,	//�˺Ż��������
	RETURN_EXIT,					//�˳�
	RETURN_ILLEGAL_INPUT,		//�Ƿ�����
}En_LoginReturn_Type;

class CDBPersonInfo
{
public:
	int				m_nID;
	CString			m_strTreeCode;
	CString			m_strUserID;	//�û�ID
	CString			m_strUserPwd;	//����
	CString			m_strUserName;
	CString			m_strUserPower;
	CString			m_strUserTel;
	COleDateTime    m_tUserDate;
	COleDateTime    m_tUserBorn;
	CString			m_strUserMemo;
	CString			m_strUserSFZ;
	//Photo
	CString			m_strUserSale;
	CString			m_strUserDuty;
	CString			m_strAddr;
	COleDateTime   m_tInTime;
	COleDateTime   m_tOutTime;
	int            m_nOutFlag;	//ע����ʶ 0==����,1==ע��
   DWORD          m_dwAttriEx;//��չ���� 2018-03-19 wangzl 
   int            m_iSalesman;   //����Ա add by lida 2018/09/12
	UINT64			m_nPermission;	//Ȩ��(����)
};

class _declspec(dllexport) CQLLoginEx
{
public:
	CQLLoginEx();
	~CQLLoginEx();
	/*
	*@brief: ��ʾ��¼��
	*@RETURN_SUCCESS  		//��½�ɹ�
	*@RETURN_EMPTY_ACCOUNT  //�˻�Ϊ��
	*@RETURN_EMPTY_PASSWD   //����Ϊ��
	*@RETURN_WRITTEN_OFF 	//�˻���ע��
	*@RETURN_POWER_ERROR 	//Ȩ�޳���
	*@RETURN_ACCOUNT_PWD 	//�˺Ż��������
	*@RETURN_EXIT				//�˳�
	*@RETURN_ILLEGAL_INPUT	//�Ƿ�����
	*/
	En_LoginReturn_Type ShowDlg(__in CString strPath/*���ݰ�װ·��Ŀ¼*/);	

   En_LoginReturn_Type ShowDlg(__in CString strPath,__out CConfigInfoList &configList);

   En_LoginReturn_Type ShowDlg(__in CString strPath,__in CString strIP
      ,__in CString strDBName,__in CString strUserID,__out CConfigInfoList &configList);
	/*
	**@brief:�õ���ǰ��¼�û���Ϣ
	*/
	CDBPersonInfo GetCurLogInfo();

	/*
	**@brief:����·��
	*/
	void SetKdsPath(__in CString strPath/*���ݰ�װ·��Ŀ¼*/);

	/*
	**@brief:ע����¼����Ϣ
	*/
	void LogOutPsInfo();
};

