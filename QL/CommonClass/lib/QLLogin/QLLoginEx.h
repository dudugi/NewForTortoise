#pragma once
#include <afxstr.h>
#include <afxdd_.h>
#include "ConfigInfo.h"


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

class CDBPersonInfo
{
public:
	int				m_nID;
	CString			m_strTreeCode;
	CString			m_strUserID;	//用户ID
	CString			m_strUserPwd;	//密码
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
	int            m_nOutFlag;	//注销标识 0==正常,1==注销
   DWORD          m_dwAttriEx;//扩展属性 2018-03-19 wangzl 
   int            m_iSalesman;   //跟单员 add by lida 2018/09/12
	UINT64			m_nPermission;	//权限(废弃)
};

class _declspec(dllexport) CQLLoginEx
{
public:
	CQLLoginEx();
	~CQLLoginEx();
	/*
	*@brief: 显示登录框
	*@RETURN_SUCCESS  		//登陆成功
	*@RETURN_EMPTY_ACCOUNT  //账户为空
	*@RETURN_EMPTY_PASSWD   //密码为空
	*@RETURN_WRITTEN_OFF 	//账户被注销
	*@RETURN_POWER_ERROR 	//权限出错
	*@RETURN_ACCOUNT_PWD 	//账号或密码出错
	*@RETURN_EXIT				//退出
	*@RETURN_ILLEGAL_INPUT	//非法输入
	*/
	En_LoginReturn_Type ShowDlg(__in CString strPath/*传递安装路径目录*/);	

   En_LoginReturn_Type ShowDlg(__in CString strPath,__out CConfigInfoList &configList);

   En_LoginReturn_Type ShowDlg(__in CString strPath,__in CString strIP
      ,__in CString strDBName,__in CString strUserID,__out CConfigInfoList &configList);
	/*
	**@brief:得到当前登录用户信息
	*/
	CDBPersonInfo GetCurLogInfo();

	/*
	**@brief:设置路径
	*/
	void SetKdsPath(__in CString strPath/*传递安装路径目录*/);

	/*
	**@brief:注销登录人信息
	*/
	void LogOutPsInfo();
};

