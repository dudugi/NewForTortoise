#pragma once
/*************************************************
// <�ļ�>: DBPersonInfo_V.h
// <˵��>: ���ݲ�����-Ա����Ϣ��ͼ
// <����>: yangjr
// <����>: 2019/02/20 16:19:01
// Copyright (C), 2016-2020, �������. Co., Ltd.
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

/*Ա����Ϣ---��ͼ*/
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

   DWORD          m_dwAttriEx          ;//��չ���� 2018-03-19 wangzl 
   int            m_iSalesman;      //�Ƿ�ҵ��Ա�������Ǹ��Ǹ���Ա
   CString        m_strUserControlsPermission;

   DWORD          m_dwTagPermission ;//��ǩҳȨ�� wangzl 2019-6-11
   DWORD          m_dwFilePermission;//�ļ�Ȩ��   wangzl 2019-6-11

   CString        m_strUserRole         ;//��ɫ
   CString        m_strGroup            ;//��
public:
	virtual void ResetData();

	virtual void Copy(CDBPersonInfoData_V * pData);

	void ToDBData(CDBPersonInfoData &);

	BOOL GetAllDBInfo(CADOConn *pADOConn);		//��ȡ����������Ϣ

   long GetPatternType(){return m_dwAttriEx & PERSON_ATTRI_PATTERN_AND;}
   void SetPatternType(long nPatternType){
      m_dwAttriEx &= PERSON_ATTRI_NONE;
      m_dwAttriEx |= nPatternType;
   }

   //�����Ƿ��д������ҳ��Ȩ�� wangzl 2019-2-18
   BOOL HasWebPermission(long nWebPermission) const;
   BOOL HasWebPermission(const DWORD & dwAttri,long nWebPermission) const;
   BOOL HasTagPermission(const DWORD & dwAttri,long nPermission) const;
   BOOL HasFilePermission(const DWORD & dwAttri,long nPermission) const;

   void SetWebPermission(long nWebPermission){
      m_dwAttriEx &= (~PERSON_ATTRI_WEB_AND);//�Ƴ���ǰȨ��
      m_dwAttriEx |= (nWebPermission & PERSON_ATTRI_WEB_AND);//�����Ȩ���е�Ȩ��
   }
   void SetTagPermission(long nPermission){
      m_dwTagPermission &= (~PERSON_TAG_PERMISSON_ALL);//�Ƴ���ǰȨ��
      m_dwTagPermission |= (nPermission & PERSON_TAG_PERMISSON_ALL);//�����Ȩ���е�Ȩ��
   }
   void SetFilePermission(long nPermission){
      m_dwFilePermission &= (~PERSON_FILE_PERMISSON_ALL);//�Ƴ���ǰȨ��
      m_dwFilePermission |= (nPermission & PERSON_FILE_PERMISSON_ALL);//�����Ȩ���е�Ȩ��
   }

private:
	inline void ClearPhoto();
};

/*Ա����Ϣ��---��ͼ*/
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

	BOOL GetListFromDB(CADOConn *pADOConn);//�����ݿ��ȡ��������

	BOOL ResetAllPwdExpectAdmin(CADOConn *pADOConn,CString strPwd);		//��������Ա������Ϊ666666 ��admin��

	static CDBPersonInfoList_V * Instance();//��ȡ��ָ�룩ʵ��

#ifdef USING_GRIDCTRL_MARK
   /********************************************************************
   @author: wangzl
   @brief: ���ɱ������ 
   @Date:2018/06/11
   @param:strUserDuty  ��¼�˵�Ȩ��  strTreeCode ���˵Ĳ���(���ű���)  bFilterNoPower �Ƿ������Ȩ���˻�
   @return:���ɵı������
   @example:
   ********************************************************************/
	MAP_GridCtrl_AllData CreateGridData(const CString & strUserDuty = _T(""),const CString & strTreeCode = _T(""),BOOL bFilterNoPower = FALSE);

   // �ж�ĳȨ���û��ܷ�鿴����һ��Ȩ���û��� wangzl 2018-06-11
   inline BOOL HasViewAuthority(const CString & strViewerDuty,const CString & strUserDuty);


   //��ȡ����Ա����Ϣ		by WangZY 2018/10/30
   static BOOL GetGongxuUserInfo(__in CADOConn* pADOConn,
                                 __out map<int,CString>& map_gx_sort,
                                 __out map<CString,map<CString,CString>>& map_Gongxu_user);



#endif // USING_GRIDCTRL_MARK

   //���ݽ�ɫ��ȡԱ������ (�����б��ȡ) wangzl 2019-5-24
   void GetUsrIDNameGroupCodeByRole(map<CString,map<CString,CString>>& mapUserInfo);
   //��ȡ�û������Ϣ
   void GetUserGroupInfoByRole(map<CString/*��ɫ*/,vector<CString>/*�û���*/>& mapUserInfo);
private:
	static std::shared_ptr<CDBPersonInfoList_V> sm_inst;
};
