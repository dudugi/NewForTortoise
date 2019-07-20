#pragma once



#include "../ClassData/ConfigInfo.h"
//#include "DialogExMid/DialogexMid.h"
//#include "QLLoginEx.h"



// CDlgLogin �Ի���

class CDlgLogin : public CBCGPDialog
{
	DECLARE_DYNAMIC(CDlgLogin)
public:	

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

	//�����û���¼�����
	En_LoginReturn_Type GetLoginState(){return m_enType;}

public:
	CDlgLogin(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgLogin();
	void SetDlgPos(BOOL bExpand = FALSE);
	void SetSvrConfigValue(CConfigInfo *pConfigInfo);
	void SetActValue();
	void SetCtrState(BOOL bEnable = TRUE);
	void CheckSvr();	//�������
	

private:
   CRect m_rcMain;
   BOOL m_bExpandDlg;
	BOOL m_bCheckSvr;	//����־
	BOOL m_bTipSQL;	//�Ƿ���Ҫ��ʾ������ȷ����SQL���ݷ����

	//��¼���
	En_LoginReturn_Type m_enType;

	//zhangyx 2018/1/18
	CConfigInfoList m_listConfigInfo;

private:
	void OnWriteIni();
	void InitIPComboBox();
	void InitDataByIPsel();
	void SaveUserInfo(BOOL bRet = TRUE);

	// �Ի�������
	enum { IDD = IDD_DLG_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	/*CBCGPStatic m_ctrStAct;
	CBCGPStatic m_ctrStPwd;
	CBCGPStatic m_ctrSvrip;
	CBCGPStatic m_ctrDBName;
	CBCGPStatic m_ctrDBLgName;
	CBCGPStatic m_ctrDBLgPwd;*/
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnPaint();
	//afx_msg LRESULT OnQlFtpDownload(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnAdocommMsg(WPARAM wParam,LPARAM lParam);//�������ݿⱨ��Ϣ
	//��ť�¼��������
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedConfig();
	afx_msg void OnBnClickedEmpty();
	afx_msg void OnBnClickedDBSave();
	afx_msg void OnEnChangeEditActname();
	afx_msg void OnBnClickedChkAct();
	afx_msg void OnBnClickedChkApply();
	afx_msg void OnBnClickedBtnChecksvr();
	afx_msg void OnCbnSelchangeIpaddressLogindlg();
	afx_msg void OnBnClickedCancel();
};
