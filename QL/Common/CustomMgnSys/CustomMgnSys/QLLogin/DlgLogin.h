#pragma once



#include "../ClassData/ConfigInfo.h"
//#include "DialogExMid/DialogexMid.h"
//#include "QLLoginEx.h"



// CDlgLogin 对话框

class CDlgLogin : public CBCGPDialog
{
	DECLARE_DYNAMIC(CDlgLogin)
public:	

   typedef enum EnLoginReturn_Type
   {
      RETURN_SUCCESS,				//登陆成功
      RETURN_EMPTY_ACCOUNT,		//账户为空
      RETURN_EMPTY_PASSWD,			//密码为空
      RETURN_WRITTEN_OFF,			//账户被注销
      RETURN_POWER_ERROR,			//权限出错
      RETURN_ERROR_ACCOUNT_PWD,	//账号或密码出错
      RETURN_EXIT,					//退出
      RETURN_ILLEGAL_INPUT,		//非法输入
   }En_LoginReturn_Type;

	//返回用户登录的情况
	En_LoginReturn_Type GetLoginState(){return m_enType;}

public:
	CDlgLogin(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgLogin();
	void SetDlgPos(BOOL bExpand = FALSE);
	void SetSvrConfigValue(CConfigInfo *pConfigInfo);
	void SetActValue();
	void SetCtrState(BOOL bEnable = TRUE);
	void CheckSvr();	//检测服务端
	

private:
   CRect m_rcMain;
   BOOL m_bExpandDlg;
	BOOL m_bCheckSvr;	//检测标志
	BOOL m_bTipSQL;	//是否需要提示：请正确配置SQL数据服务端

	//登录情况
	En_LoginReturn_Type m_enType;

	//zhangyx 2018/1/18
	CConfigInfoList m_listConfigInfo;

private:
	void OnWriteIni();
	void InitIPComboBox();
	void InitDataByIPsel();
	void SaveUserInfo(BOOL bRet = TRUE);

	// 对话框数据
	enum { IDD = IDD_DLG_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
	afx_msg LRESULT OnAdocommMsg(WPARAM wParam,LPARAM lParam);//弹出数据库报信息
	//按钮事件处理程序
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
