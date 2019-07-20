#pragma once

/*********************************人员信息表 begin********************************************/
#define DB_TABLE_USERINFO                      _T("UserInfo")			//人员信息表名

//人员信息表字段
#define DBUser_key_ID				   _T("ID")			//ID 自增
#define DBUser_key_cUserID			   _T("cUserID")		//用户ID
#define DBUser_key_cPassword		   _T("cPassword")		//用户密码
#define DBUser_key_cUserName		   _T("cUserName")		//用户姓名
#define DBUser_key_cUserDate		   _T("cUserDate")		//用户注册时间
#define DBUser_key_dtLastLoadTime	_T("dtLastLoadTime")		//最后一次登录时间
#define DBUser_key_iUserState		   _T("iUserState")		//用户状态 是否注销
/*********************************人员信息表 end********************************************/


/*********************************客户信息基础表 begin********************************************/
#define DB_TABLE_CUSTOMERBASEDATA                      _T("CustomerBaseData")			//客户信息基础表名

//客户信息基础表字段
#define DBCusBase_key_ID				   _T("ID")			      //ID 自增
#define DBCusBase_key_cCusCode			_T("cCusCode")		   //客户编号
#define DBCusBase_key_cCusName			_T("cCusName")		   //客户名称
#define DBCusBase_key_cCusAddress		_T("cCusAddress")		//客户地址
#define DBCusBase_key_cCusPhone			_T("cCusPhone")		//联系人
#define DBCusBase_key_cCusContacts		_T("cCusContacts")	//版本号
#define DBCusBase_key_cPDMVersion		_T("cPDMVersion")		//客户地址
#define DBCusBase_key_cProvince			_T("cProvince")		//省
#define DBCusBase_key_isLocalDB			_T("isLocalDB")		//数据库是否部署在本地
#define DBCusBase_key_cServerPerson		_T("cServerPerson")		//服务人员
#define DBCusBase_key_iClientNum			_T("iClientNum")		//客户端数量
#define DBCusBase_key_cMemo			   _T("cMemo")		//备注
/*********************************客户信息基础表 end********************************************/

/*********************************客户数据库配置表 begin********************************************/
#define DB_TABLE_CUSTOMERDBDATA                      _T("CustomerDbData")			//客户数据库配置表--名称

//客户数据库配置表--字段
#define DBCusDb_key_cCusCode			_T("cCusCode")		   //客户编号
#define DBCusDb_key_cDbServerName	_T("cDbServerName")	//数据库名称
#define DBCusDb_key_iDbServerPort	_T("iDbServerPort")	//数据库端口
#define DBCusDb_key_cDbAccount		_T("cDbAccount")		//登录账户
#define DBCusDb_key_cDbPassword		_T("cDbPassword")		//登录密码
#define DBCusDb_key_cDbServerIP	   _T("cDbServerIP")	   //数据库IP
/*********************************客户数据库配置表 end********************************************/

/*********************************客户加密数据表 begin********************************************/
#define DB_TABLE_CUSTOMERENCRYPTDATA                      _T("CustomerEncryptData")			//客户加密数据表--名称

//客户加密数据表--字段
#define DBCusEncrypt_key_cCusCode		_T("cCusCode")		//客户编号
#define DBCusEncrypt_key_cData1		   _T("cData1")	   //加密数据1
#define DBCusEncrypt_key_cData2	      _T("cData2")	   //加密数据2
#define DBCusEncrypt_key_cData3		   _T("cData3")	   //加密数据3
#define DBCusEncrypt_key_cData4		   _T("cData4")	   //加密数据4
/*********************************客户加密数据表 end********************************************/


/*==============================日志表 dbo.WorkLog ==============================*/
#define DBWorkLog_key_ID		_T("ID")
#define DBWorkLog_key_Cate		_T("cCate")
#define DBWorkLog_key_Code		_T("cCode")
#define DBWorkLog_key_Date		_T("dDate")
#define DBWorkLog_key_Maker		_T("cMaker")
#define DBWorkLog_key_Type		_T("cType")
#define DBWorkLog_key_Detail	_T("cMemo")
#define DBWorkLog_key_InterFace	_T("cInterFaceName")
#define DBWorkLog_key_ProjectName _T("cProjectName")


/*********************************客户数据操作记录表 begin********************************************/
#define DB_TABLE_CUSOPRECORDS                      _T("CusOpRecords")			//客户数据操作记录表--名称

//客户数据操作记录表--字段
#define DBCusOpRds_key_ID				   _T("ID")			      //ID 自增
#define DBCusOpRds_key_cOpType			_T("cOpType")			//操作类型
#define DBCusOpRds_key_cCusCode			_T("cCusCode")		   //客户编号
#define DBCusOpRds_key_cCusName			_T("cCusName")		   //客户名称
#define DBCusOpRds_key_cCusAddress		_T("cCusAddress")		//客户地址
#define DBCusOpRds_key_cCusPhone			_T("cCusPhone")		//联系人
#define DBCusOpRds_key_cCusContacts		_T("cCusContacts")	//版本号
#define DBCusOpRds_key_cPDMVersion		_T("cPDMVersion")		//客户地址
#define DBCusOpRds_key_cProvince			_T("cProvince")		//省
#define DBCusOpRds_key_isLocalDB			_T("isLocalDB")		//数据库是否部署在本地
#define DBCusOpRds_key_cServerPerson	_T("cServerPerson")		//服务人员
#define DBCusOpRds_key_iClientNum		_T("iClientNum")		//客户端数量
#define DBCusOpRds_key_cMemo			   _T("cMemo")		//备注

#define DBCusOpRds_key_cDbServerName	_T("cDbServerName")	//数据库名称
#define DBCusOpRds_key_iDbServerPort	_T("iDbServerPort")	//数据库端口
#define DBCusOpRds_key_cDbAccount		_T("cDbAccount")		//登录账户
#define DBCusOpRds_key_cDbPassword		_T("cDbPassword")		//登录密码
#define DBCusOpRds_key_cDbServerIP	   _T("cDbServerIP")	   //数据库IP

#define DBCusOpRds_key_cBeginTime	   _T("cBeginTime")	//开始时间
#define DBCusOpRds_key_cTime	         _T("cTime")	      //到期时间
#define DBCusOpRds_key_cModeData	      _T("cModeData")	//功能模块
#define DBCusOpRds_key_cPerson	      _T("cPerson")	   //身份信息
#define DBCusOpRds_key_fChongZhiJE	   _T("fChongZhiJE")	//充值金额
/*********************************客户数据操作记录表 end********************************************/
