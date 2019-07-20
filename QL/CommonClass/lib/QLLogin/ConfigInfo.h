#pragma once
#include "DataMid.h"

/************************************************************************
 * 创建日期：2018/01/15     作者：zhangyx
 * CConfigInfo
 * 目的：存储用户的配置信息
 ************************************************************************/


//配置对话框的信息
#define USERDEFINED							_T("用户自定义")
#define USERNAME							_T("用户名")
#define USERPASSWORD						_T("用户密码")
#define REMEMBERPASSWORD					_T("记住密码")
#define AUTOMATICLOGON						_T("自动登录")
#define	IPADDRESS							_T("IP地址或URL")
#define PORTONE                             _T("端口1")
#define PORTTWO								_T("端口2")
#define DATABASENAME						_T("数据库名称")
#define DATABASEACCOUNT						_T("数据库账户")
#define DATABASEPASSWORD					_T("数据库密码")
#define APPLYACCOUNT						_T("向开发商申请账号")


class CConfigInfo : public CDataMid
{
	DECLARE_SERIAL(CConfigInfo)//序列化（串行化）需要添加的声明
public:
	CConfigInfo(void);
	~CConfigInfo(void);
	void ResetData();
	void Serialize(CArchive& ar);
	void Copy(CConfigInfo *pData);

public:
	CString m_strUserDefinedName;	//自定义
	CString m_strUserID;			//用户ID
	CString m_strUserPassword;		//用户密码
	BOOL m_bRememberPassword;		//是否记住密码
	BOOL m_bAutomaticLogon;			//是否自动登录
	CString m_strIPAddress;			//IP地址
	CString m_strPort1;				//端口1
	CString m_strPort2;				//端口2
	CString m_strDatabaseName;		//数据库名称
	CString m_strDatabaseAccount;	//数据库账户
	CString m_strDatabasePassword;	//数据库密码
	BOOL    m_bApplyAccount;		//是否向开发商申请
   CString m_strFtpIP;           //本地Ftp地址    add anjie by 2018/09/27
   BOOL    m_bHttpMode;          //是否使用了HTTP模式 默认为FALSE
};

class CConfigInfoList: public CDataListMid
{
	DECLARE_SERIAL(CConfigInfoList)
public:
	CConfigInfoList();
	~CConfigInfoList();
public:
	void	Serialize(CArchive& ar);
	CConfigInfo* GetItemByIP(CString strIP);	//根据用户IP获取Item
	CConfigInfo* GetItem(int nIndex);			//根据索引获取Item
	void AddItem(CConfigInfo* pItem);			//添加Item
	void DeleteItem(int nIndex);				//删除固定索引Item
   CConfigInfo* GetItemByApply(CString strstrUserDefinedName,CString strIPAddress,CString strDatabaseName);	//根据用户IP获取Item
   void Copy(CConfigInfoList *pList);
};
