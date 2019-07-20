/*************************************************
// <文件>: DBPersonInfo.h
// <说明>: 数据操作类-员工信息表 
// <作者>: yangjr
// <日期>: 2019/02/20 16:19:01
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 
#pragma once

#include "DataMid.h"
#include <map>
#include <vector>
class CADOConn;

//数据库中字段

#define PS_ADMIN_ALL				0xFFFFFFFF	//老版本遗留：权限

#define PERSON_ATTRI_NONE      0x0000      //无任何权限

//---------------------------------------------------------------
//制版类型组合值  max = 8     0000  -  1110 
//默认 非以下值的是默认的琪利版
#define PERSON_ATTRI_PATTERN_AND     0x000F      //与值   与值等于以下的任何一个 则为其类型
#define PERSON_ATTRI_QL              0x0001      //琪利
#define PERSON_ATTRI_STOLL           0x0002      //Stoll标识 
#define PERSON_ATTRI_HENGQ           0x0004      //恒强
#define PERSON_ATTRI_DAOJ            0x0006      //岛精
//-------------------------------

//员工网页端权限 可以多权限共存
#define PERSON_ATTRI_WEB_AND               0x00F0     //与值
#define PERSON_ATTRI_WEB_ORDER_SEARCH      0x0010     //订单查询
#define PERSON_ATTRI_WEB_PAYMENT_RECORD    0x0020     //货款记录
#define PERSON_ATTRI_WEB_REMITTANCE_RECORD 0x0040     //汇款记录
#define PERSON_ATTRI_WEB_MESSAGE           0x0080     //我的消息

//员工标签页权限
#define PERSON_TAG_PERMISSON_PIC           0X0001
#define PERSON_TAG_PERMISSON_COLOR         0X0002
#define PERSON_TAG_PERMISSON_MATERIAL      0X0004
#define PERSON_TAG_PERMISSON_COST          0X0008
#define PERSON_TAG_PERMISSON_FANGANGX      0X0010
#define PERSON_TAG_PERMISSON_BASIC         0X0020
#define PERSON_TAG_PERMISSON_SIZE          0X0040
#define PERSON_TAG_PERMISSON_FILE          0X0080
#define PERSON_TAG_PERMISSON_PERMISSION    0X0100
#define PERSON_TAG_DESCRIPTION             0X0200
#define PERSON_TAG_ViedeoInfo              0X0400
#define PERSON_TAG_PicShowInfo             0X0800
#define PERSON_TAG_DesDenisity             0X01000
#define PERSON_TAG_ProcessRecord           0X02000
#define PERSON_TAG_SampleClothInfo         0X04000
#define PERSON_TAG_ProductOrderInfo         0X08000
#define PERSON_TAG_SalesOrderInfo         0X010000

#define PERSON_TAG_PERMISSON_ALL (PERSON_TAG_PERMISSON_PIC|PERSON_TAG_PERMISSON_COLOR|PERSON_TAG_PERMISSON_MATERIAL|\
   PERSON_TAG_PERMISSON_COST|PERSON_TAG_PERMISSON_FANGANGX|PERSON_TAG_PERMISSON_BASIC|PERSON_TAG_PERMISSON_SIZE|PERSON_TAG_PERMISSON_FILE|\
   PERSON_TAG_PERMISSON_PERMISSION|PERSON_TAG_DESCRIPTION |PERSON_TAG_ViedeoInfo|PERSON_TAG_PicShowInfo|PERSON_TAG_DesDenisity|PERSON_TAG_ProcessRecord\
|PERSON_TAG_SampleClothInfo)
//员工查看文件权限
#define PERSON_FILE_PERMISSON_DESIGN      0X0001
#define PERSON_FILE_PERMISSON_PROCESS     0X0002
#define PERSON_FILE_PERMISSON_PATTERN     0X0004
#define PERSON_FILE_PERMISSON_MAC         0X0008
#define PERSON_FILE_PERMISSON_PICTURE     0X0010
#define PERSON_FILE_PERMISSON_OTHER       0X0020

#define PERSON_FILE_PERMISSON_ALL         (PERSON_FILE_PERMISSON_DESIGN|PERSON_FILE_PERMISSON_PROCESS|\
   PERSON_FILE_PERMISSON_PATTERN|PERSON_FILE_PERMISSON_MAC|PERSON_FILE_PERMISSON_PICTURE|PERSON_FILE_PERMISSON_OTHER)

class CDBPersonInfoData :public CDataMid
{
	DECLARE_SERIAL( CDBPersonInfoData)//序列化（串行化）需要添加的声明
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
	COleDateTime    m_tInTime;
	COleDateTime    m_tOutTime;
	int             m_nOutFlag;		//注销标识 0==正常,1==注销

	UINT64			m_nPermission;	//权限

   DWORD          m_dwAttriEx          ;//扩展属性 2018-03-19 wangzl 

   DWORD          m_dwTagPermission ;//标签页权限 wangzl 2019-6-11
   DWORD          m_dwFilePermission;//文件权限   wangzl 2019-6-11

   CString        m_strUserRole         ;//角色
   CString        m_strGroup            ;//组
   int         m_iSalesman;      //是否业务员，上面那个是跟单员
   CString        m_strUserControlsPermission;

public:
	CDBPersonInfoData();
	~CDBPersonInfoData();
	void operator = (CDBPersonInfoData *pData);
	void ResetData();
	void Copy(CDBPersonInfoData *pData);
	void Serialize(CArchive& ar);
	BOOL GetAllDBInfo(CADOConn *pADOConn);				//获取【整条】信息
	BOOL InsertAllDBInfoByUserID(CADOConn *pADOConn);	//插入【整条】新记录
	BOOL UpdateAllDBInfoByUserID(CADOConn *pADOConn);	//根据用户账户更新【整条】记录
	BOOL DelAllDBInfoByUserID(CADOConn *pADOConn);		//根据用户账户删除【整条】记录
	BOOL GetAllDBInfoByUserID(CADOConn *pADOConn);		//根据用户账户获取【整条】信息
   //返回制版的类型值 2018-03-19 wangzl
   long GetPatternType(){return m_dwAttriEx & PERSON_ATTRI_PATTERN_AND;}
   void SetPatternType(long nPatternType){
      m_dwAttriEx &= (~PERSON_ATTRI_PATTERN_AND);//移除当前制版的所有权限
      m_dwAttriEx |= (nPatternType & PERSON_ATTRI_PATTERN_AND);//添加新权限中的所有制版权限
   }

   //返回是否有传入的网页端权限 wangzl 2019-2-18
   BOOL HasWebPermission(long nWebPermission) const;
   static BOOL HasWebPermission(const DWORD & dwAttri,long nWebPermission);
   static BOOL HasTagPermission(const DWORD & dwAttri,long nPermission);
   static BOOL HasFilePermission(const DWORD & dwAttri,long nPermission);

   void SetWebPermission(long nWebPermission){
      m_dwAttriEx &= (~PERSON_ATTRI_WEB_AND);//移除当前的权限
      m_dwAttriEx |= (nWebPermission & PERSON_ATTRI_WEB_AND);//添加新权限中的权限
   }

	static CDBPersonInfoData * Instance();				//获取（指针）实例

private:
	static std::shared_ptr<CDBPersonInfoData> sm_inst;
};
class CDBPersonInfoList  : public CDataListMid
{
	DECLARE_SERIAL(CDBPersonInfoList)
public:
	CDBPersonInfoList();
	~CDBPersonInfoList();
	CDBPersonInfoData* GetItem(int nIndex);					//根据索引获取Item
	CDBPersonInfoData* GetItemByUserID(CString strUserID);	//根据用户账户获取Item
	int GetIndexByUserID(CString strUserID);				//根据用户账户获取索引
	void AddItem(CDBPersonInfoData* pItem);					//添加Item
	void DeleteItem(int nIndex);							//删除固定索引Item

	void GetListFromDB(CADOConn *pADOConn);					//从数据库获取链表
	static CDBPersonInfoList * Instance();					//获取（指针）实例

	BOOL ResetAllPwdExpectAdmin(CADOConn *pADOConn);		//重置所有员工密码为666666 除admin外
   
	BOOL ModifyUserPassword(CADOConn *pADOConn,CDBPersonInfoData* pData);		//修改密码 add by lida 2017/08/04

   CString GetUserNameByUserID(CADOConn *pADOConn,CString userID);//根据员工编号获取员工姓名 yangjr 2017-7-5

   map<CString,CString> GetUsrIDAndName(CADOConn *pADOConn);	//获取所有的人员信息 map<UserID,UserName> lida 2017/09/08

   map<CString,CString> GetUsrIDAndName(CADOConn *pADOConn , CString treeCode);	//获取某部门人员信息 map<UserID,UserName> wuzhihua 2018/3/19

   BOOL DeleteUserByUserID(CADOConn* pADOConn, std::vector<CString> vecUserID);

   //更新用户权限接口 wangzl 2019-2-21 map<用户ID，权限>
   BOOL UpdateUserPermission(CADOConn * pADOConn,std::map<CString,CString> map_UserID_Permission);

   void GetAllDBInfoByRole(map<CString,vector<CString>> &mapPersonInfo);//根据角色分类 liuhw 2019/05/21


#ifdef USING_GRIDCTRL_MARK
   MAP_GridCtrl_AllData CreateGridData();
#endif // USING_GRIDCTRL_MARK

private:
	static std::shared_ptr<CDBPersonInfoList> sm_inst;
};

struct stc_staff_info
{
   CString Get_Update_SQL(BOOL bIgnoreNum /*TRUE*/);
   CString Get_Insert_SQL();
   CString strTreeCode;       //部门编号
   CString strUserID;         //用户ID
   CString strUserPwd;        //用户密码
   CString strUserName;       //用户名
   CString strUserPower;      //用户权限
   CString strUserTel;        //用户联系方式
   CString strUserDate;       //用户注册时间
   CString strUserBorn;       //用户生日
   CString strUserMemo;       //备注
   CString strUserSFZ;        //身份证
   CString strUserSale;       //是否跟单员
   CString strUserDuty;       //职位
   CString strAddr;           //地址
   //CString strOutTime;        //注销时间
   CString strAttriEx;        //扩展属性
   CString strSalesman;       //业务员
};

