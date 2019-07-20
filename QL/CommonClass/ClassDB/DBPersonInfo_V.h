#pragma once
/*************************************************
// <文件>: DBPersonInfo_V.h
// <说明>: 数据操作类-员工信息视图
// <作者>: yangjr
// <日期>: 2019/02/20 16:19:01
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 

#include "DataMid.h"
#include "DBPersonInfo.h"
#include <GdiplusHeaders.h>
/*

cUserSale								 DBPerson_key_ID				
cUserPhoto								 DBPerson_key_TreeCode		
cUserSFZ								 DBPerson_key_UserID			
cUserBorn								 DBPerson_key_Pwd			
cUserMemo								 DBPerson_key_UserName		
cUserDate								 DBPerson_key_UserPower		
cUserTel								 DBPerson_key_UserTel		
cUserPower								 DBPerson_key_UserDate		
cUserName								 DBPerson_key_UserBorn		
cPassword								 DBPerson_key_UserMemo		
cUserID									 DBPerson_key_UserSFZ		
cTreeCode								 DBPerson_key_UserPhoto		
ID										 DBPerson_key_UserSale		
cUserDuty								 DBPerson_key_UserDuty		
cAddr									 DBPerson_key_Addr		
dtInTime								 DBPerson_key_InTime
dtOutTime								 DBPerson_key_OutTime
iOutFlag								 DBPerson_key_OutFlag

cTreeName								 DBDataDic_key_ItemName
*/

/*员工信息---视图*/
class CDBPersonInfoData_V :
	public CDataMid
{
public:
	CDBPersonInfoData_V(void);
	~CDBPersonInfoData_V(void);

public:
	int				m_nID					;
	CString			m_strcTreeCode			;
	CString			m_strcUserID			;
	CString			m_strcPassword			;
	CString			m_strcUserName			;
	CString			m_strcUserPower			;
	CString			m_strcUserTel			;
	COleDateTime	m_oledtUserDate			;
	COleDateTime	m_oledtUserBorn			;
	CString			m_strcUserMemo			;
	CString			m_strcUserSFZ			;
	Gdiplus::Image *			m_pUserPhoto			;
	CString			m_strcUserSale			;
	CString			m_strcUserDuty			;
	CString			m_strcAddr				;
	COleDateTime	m_oledtInTime			;
	COleDateTime	m_oledtOutTime			;
	int				m_niOutFlag				;

	CString			m_strcTreeName			;

   DWORD          m_dwAttriEx          ;//扩展属性 2018-03-19 wangzl 
   int            m_iSalesman;      //是否业务员，上面那个是跟单员
   CString        m_strUserControlsPermission;

   DWORD          m_dwTagPermission ;//标签页权限 wangzl 2019-6-11
   DWORD          m_dwFilePermission;//文件权限   wangzl 2019-6-11

   CString        m_strUserRole         ;//角色
   CString        m_strGroup            ;//组
public:
	virtual void ResetData();

	virtual void Copy(CDBPersonInfoData_V * pData);

	void ToDBData(CDBPersonInfoData &);

	BOOL GetAllDBInfo(CADOConn *pADOConn);		//获取【整条】信息

   long GetPatternType(){return m_dwAttriEx & PERSON_ATTRI_PATTERN_AND;}
   void SetPatternType(long nPatternType){
      m_dwAttriEx &= PERSON_ATTRI_NONE;
      m_dwAttriEx |= nPatternType;
   }

   //返回是否有传入的网页端权限 wangzl 2019-2-18
   BOOL HasWebPermission(long nWebPermission) const;
   BOOL HasWebPermission(const DWORD & dwAttri,long nWebPermission) const;
   BOOL HasTagPermission(const DWORD & dwAttri,long nPermission) const;
   BOOL HasFilePermission(const DWORD & dwAttri,long nPermission) const;

   void SetWebPermission(long nWebPermission){
      m_dwAttriEx &= (~PERSON_ATTRI_WEB_AND);//移除当前权限
      m_dwAttriEx |= (nWebPermission & PERSON_ATTRI_WEB_AND);//添加新权限中的权限
   }
   void SetTagPermission(long nPermission){
      m_dwTagPermission &= (~PERSON_TAG_PERMISSON_ALL);//移除当前权限
      m_dwTagPermission |= (nPermission & PERSON_TAG_PERMISSON_ALL);//添加新权限中的权限
   }
   void SetFilePermission(long nPermission){
      m_dwFilePermission &= (~PERSON_FILE_PERMISSON_ALL);//移除当前权限
      m_dwFilePermission |= (nPermission & PERSON_FILE_PERMISSON_ALL);//添加新权限中的权限
   }

private:
	inline void ClearPhoto();
};

/*员工信息表---视图*/
class CDBPersonInfoList_V :public CDataListMid
{
public:
	CDBPersonInfoList_V();
	~CDBPersonInfoList_V();

	CDBPersonInfoData_V*  GetItem(int nIndex);
	CDBPersonInfoData_V*  GetItemByUserID(CString strUserID);
   CDBPersonInfoData_V*  GetItemByID(int nID);
	int  GetIndexByUserID(CString strUserID);
	void    AddItem(CDBPersonInfoData_V* pItem);
	void    DeleteItem(int nIndex);

	BOOL GetListFromDB(CADOConn *pADOConn);//从数据库获取所有链表

	BOOL ResetAllPwdExpectAdmin(CADOConn *pADOConn,CString strPwd);		//重置所有员工密码为666666 除admin外

	static CDBPersonInfoList_V * Instance();//获取（指针）实例

#ifdef USING_GRIDCTRL_MARK
   /********************************************************************
   @author: wangzl
   @brief: 生成表格数据 
   @Date:2018/06/11
   @param:strUserDuty  登录人的权限  strTreeCode 过滤的部门(部门编码)  bFilterNoPower 是否过滤无权限账户
   @return:生成的表格数据
   @example:
   ********************************************************************/
	MAP_GridCtrl_AllData CreateGridData(const CString & strUserDuty = _T(""),const CString & strTreeCode = _T(""),BOOL bFilterNoPower = FALSE);

   // 判断某权限用户能否查看另外一个权限用户的 wangzl 2018-06-11
   inline BOOL HasViewAuthority(const CString & strViewerDuty,const CString & strUserDuty);


   //获取工序员工信息		by WangZY 2018/10/30
   static BOOL GetGongxuUserInfo(__in CADOConn* pADOConn,
                                 __out map<int,CString>& map_gx_sort,
                                 __out map<CString,map<CString,CString>>& map_Gongxu_user);



#endif // USING_GRIDCTRL_MARK

   //根据角色获取员工数据 (缓存列表获取) wangzl 2019-5-24
   void GetUsrIDNameGroupCodeByRole(map<CString,map<CString,CString>>& mapUserInfo);
   //获取用户组的信息
   void GetUserGroupInfoByRole(map<CString/*角色*/,vector<CString>/*用户组*/>& mapUserInfo);
private:
	static std::shared_ptr<CDBPersonInfoList_V> sm_inst;
};
