/*************************************************
// <�ļ�>: DBPersonInfo.h
// <˵��>: ���ݲ�����-Ա����Ϣ�� 
// <����>: yangjr
// <����>: 2019/02/20 16:19:01
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
#pragma once

#include "DataMid.h"
#include <map>
#include <vector>
class CADOConn;

//���ݿ����ֶ�

#define PS_ADMIN_ALL				0xFFFFFFFF	//�ϰ汾������Ȩ��

#define PERSON_ATTRI_NONE      0x0000      //���κ�Ȩ��

//---------------------------------------------------------------
//�ư��������ֵ  max = 8     0000  -  1110 
//Ĭ�� ������ֵ����Ĭ�ϵ�������
#define PERSON_ATTRI_PATTERN_AND     0x000F      //��ֵ   ��ֵ�������µ��κ�һ�� ��Ϊ������
#define PERSON_ATTRI_QL              0x0001      //����
#define PERSON_ATTRI_STOLL           0x0002      //Stoll��ʶ 
#define PERSON_ATTRI_HENGQ           0x0004      //��ǿ
#define PERSON_ATTRI_DAOJ            0x0006      //����
//-------------------------------

//Ա����ҳ��Ȩ�� ���Զ�Ȩ�޹���
#define PERSON_ATTRI_WEB_AND               0x00F0     //��ֵ
#define PERSON_ATTRI_WEB_ORDER_SEARCH      0x0010     //������ѯ
#define PERSON_ATTRI_WEB_PAYMENT_RECORD    0x0020     //�����¼
#define PERSON_ATTRI_WEB_REMITTANCE_RECORD 0x0040     //����¼
#define PERSON_ATTRI_WEB_MESSAGE           0x0080     //�ҵ���Ϣ

//Ա����ǩҳȨ��
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
//Ա���鿴�ļ�Ȩ��
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
	DECLARE_SERIAL( CDBPersonInfoData)//���л������л�����Ҫ��ӵ�����
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
	COleDateTime    m_tInTime;
	COleDateTime    m_tOutTime;
	int             m_nOutFlag;		//ע����ʶ 0==����,1==ע��

	UINT64			m_nPermission;	//Ȩ��

   DWORD          m_dwAttriEx          ;//��չ���� 2018-03-19 wangzl 

   DWORD          m_dwTagPermission ;//��ǩҳȨ�� wangzl 2019-6-11
   DWORD          m_dwFilePermission;//�ļ�Ȩ��   wangzl 2019-6-11

   CString        m_strUserRole         ;//��ɫ
   CString        m_strGroup            ;//��
   int         m_iSalesman;      //�Ƿ�ҵ��Ա�������Ǹ��Ǹ���Ա
   CString        m_strUserControlsPermission;

public:
	CDBPersonInfoData();
	~CDBPersonInfoData();
	void operator = (CDBPersonInfoData *pData);
	void ResetData();
	void Copy(CDBPersonInfoData *pData);
	void Serialize(CArchive& ar);
	BOOL GetAllDBInfo(CADOConn *pADOConn);				//��ȡ����������Ϣ
	BOOL InsertAllDBInfoByUserID(CADOConn *pADOConn);	//���롾�������¼�¼
	BOOL UpdateAllDBInfoByUserID(CADOConn *pADOConn);	//�����û��˻����¡���������¼
	BOOL DelAllDBInfoByUserID(CADOConn *pADOConn);		//�����û��˻�ɾ������������¼
	BOOL GetAllDBInfoByUserID(CADOConn *pADOConn);		//�����û��˻���ȡ����������Ϣ
   //�����ư������ֵ 2018-03-19 wangzl
   long GetPatternType(){return m_dwAttriEx & PERSON_ATTRI_PATTERN_AND;}
   void SetPatternType(long nPatternType){
      m_dwAttriEx &= (~PERSON_ATTRI_PATTERN_AND);//�Ƴ���ǰ�ư������Ȩ��
      m_dwAttriEx |= (nPatternType & PERSON_ATTRI_PATTERN_AND);//�����Ȩ���е������ư�Ȩ��
   }

   //�����Ƿ��д������ҳ��Ȩ�� wangzl 2019-2-18
   BOOL HasWebPermission(long nWebPermission) const;
   static BOOL HasWebPermission(const DWORD & dwAttri,long nWebPermission);
   static BOOL HasTagPermission(const DWORD & dwAttri,long nPermission);
   static BOOL HasFilePermission(const DWORD & dwAttri,long nPermission);

   void SetWebPermission(long nWebPermission){
      m_dwAttriEx &= (~PERSON_ATTRI_WEB_AND);//�Ƴ���ǰ��Ȩ��
      m_dwAttriEx |= (nWebPermission & PERSON_ATTRI_WEB_AND);//�����Ȩ���е�Ȩ��
   }

	static CDBPersonInfoData * Instance();				//��ȡ��ָ�룩ʵ��

private:
	static std::shared_ptr<CDBPersonInfoData> sm_inst;
};
class CDBPersonInfoList  : public CDataListMid
{
	DECLARE_SERIAL(CDBPersonInfoList)
public:
	CDBPersonInfoList();
	~CDBPersonInfoList();
	CDBPersonInfoData* GetItem(int nIndex);					//����������ȡItem
	CDBPersonInfoData* GetItemByUserID(CString strUserID);	//�����û��˻���ȡItem
	int GetIndexByUserID(CString strUserID);				//�����û��˻���ȡ����
	void AddItem(CDBPersonInfoData* pItem);					//���Item
	void DeleteItem(int nIndex);							//ɾ���̶�����Item

	void GetListFromDB(CADOConn *pADOConn);					//�����ݿ��ȡ����
	static CDBPersonInfoList * Instance();					//��ȡ��ָ�룩ʵ��

	BOOL ResetAllPwdExpectAdmin(CADOConn *pADOConn);		//��������Ա������Ϊ666666 ��admin��
   
	BOOL ModifyUserPassword(CADOConn *pADOConn,CDBPersonInfoData* pData);		//�޸����� add by lida 2017/08/04

   CString GetUserNameByUserID(CADOConn *pADOConn,CString userID);//����Ա����Ż�ȡԱ������ yangjr 2017-7-5

   map<CString,CString> GetUsrIDAndName(CADOConn *pADOConn);	//��ȡ���е���Ա��Ϣ map<UserID,UserName> lida 2017/09/08

   map<CString,CString> GetUsrIDAndName(CADOConn *pADOConn , CString treeCode);	//��ȡĳ������Ա��Ϣ map<UserID,UserName> wuzhihua 2018/3/19

   BOOL DeleteUserByUserID(CADOConn* pADOConn, std::vector<CString> vecUserID);

   //�����û�Ȩ�޽ӿ� wangzl 2019-2-21 map<�û�ID��Ȩ��>
   BOOL UpdateUserPermission(CADOConn * pADOConn,std::map<CString,CString> map_UserID_Permission);

   void GetAllDBInfoByRole(map<CString,vector<CString>> &mapPersonInfo);//���ݽ�ɫ���� liuhw 2019/05/21


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
   CString strTreeCode;       //���ű��
   CString strUserID;         //�û�ID
   CString strUserPwd;        //�û�����
   CString strUserName;       //�û���
   CString strUserPower;      //�û�Ȩ��
   CString strUserTel;        //�û���ϵ��ʽ
   CString strUserDate;       //�û�ע��ʱ��
   CString strUserBorn;       //�û�����
   CString strUserMemo;       //��ע
   CString strUserSFZ;        //���֤
   CString strUserSale;       //�Ƿ����Ա
   CString strUserDuty;       //ְλ
   CString strAddr;           //��ַ
   //CString strOutTime;        //ע��ʱ��
   CString strAttriEx;        //��չ����
   CString strSalesman;       //ҵ��Ա
};

