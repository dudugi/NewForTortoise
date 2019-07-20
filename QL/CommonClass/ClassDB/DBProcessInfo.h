/*************************************************
// <�ļ�>: DBProcessInfo.h
// <˵��>: ������Ϣ��
// <����>: wangzl
// <����>: 2019/01/30 10:20:57
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
#pragma once
#include "DataMid.h"
#include <map>
#include "DBProcessRecords.h"
class CADOConn;


#define LimitHourDefafult  24//����ʱ��Ĭ��ֵ
class CDBProcessInfoData :
	public CDataMid
{
	DECLARE_SERIAL( CDBProcessInfoData)//���л������л�����Ҫ��ӵ�����

   enum EM_OTHER_STATE_MOD
   {
      emGxOTM_Null = 0x0,           //��ʼ��ֵ:���κα�־
      emGxOTM_Outsourcing = 0x1,    //ί���־;
      emGxOTM_PieceworkInstore = 0x2,  //�Ƽ����   	by WangZY 2019/01/18
      emGxOTM_ShowHintForDelivery = 0x4,  //����ѡ�ͻ�ʱ������ʾ	by WangZY 2019/02/15
      emGxOTM_OtherMore = 0x8,      //�����������ô�
      //emGxOTM_NextDemo = 0x10,     //�����������ô�
      //...��������
   };

public:
   INT64    m_nID          ;//����ID
   CString  m_strProName   ;//��������
   CString  m_strProField  ;//�����ֶ�
   CString  m_strProItem   ;//������Ŀ
   CString  m_strProChoose ;//Ա����ѡ
   UINT     m_nSortID      ;//����ID
   int      m_nGetYarn     ;//�Ƿ�����ɴ��
   int      m_nProCarryOut ;//�Ƿ��ɨ
   int      m_nCanEditCost ;//�Ƿ���Ա༭����
   CString  m_strProUpdate ;//����״̬
   CString  m_strPartLimit ;//���Ʋ���
   CString  m_strPrevPro   ;//ǰ������
   CString  m_strProRemark ;//��ע
   CString  m_strSysItem   ;//�󶨵���Ӧ������ַ���
   int      m_nLimitHour   ;//�������Ƶ�ʱ�������ڳ�ʱ������
   CString  m_strZhipaiPerson   ;//��Ӧ�����Ĭ��ָ����
   CString  m_strDefaultGXGongjia;//����Ĭ�Ϲ���
   int      m_iTipPrice;      //��ʾ��Ҫ�޸Ĺ��� 0:����ʾ��1:��ʾ
   CString  m_strBindRole;//�󶨵Ľ�ɫ  ����ɫ���ƣ�
   ///////////////////////////////
   //��������״̬��ϱ�־(��32λ�ֱ��ʾ32��״̬����ϣ�
   //Ŀǰֻ�õ�0λ��ʾ�Ƿ�ί�⹤��;������������չ��
   //		by WangZY 2018/09/13
   EM_OTHER_STATE_MOD   m_nOtherState;    
public:
   CDBProcessInfoData(void);
   ~CDBProcessInfoData(void);
   void ResetData();
   void Copy(CDBProcessInfoData *pData);
   void Swap(CDBProcessInfoData *pData);
   void Serialize(CArchive& ar);
   BOOL GetAllDBInfo(CADOConn *pADOConn);		//��ȡ����������Ϣ
   BOOL InsertAllDBInfoByName(CADOConn *pADOConn);	//���롾�������¼�¼
   BOOL UpdateAllDBInfoByName(CADOConn *pADOConn,CString strOldName);	//���ݾ����Ƹ��¡���������¼
   BOOL UpdateAllDBInfoByID(CADOConn *pADOConn);
   BOOL DelAllDBInfoByName(CADOConn *pADOConn);		//��������ɾ������������¼
   BOOL GetAllDBInfoByName(CADOConn *pADOConn);		//��ȡ����������Ϣ

   //�Ƚ��޸�ǰ�����ݣ����޸��˵����ݱ�������
   CString SetDBEquals_Log(CDBProcessInfoData &pOldData);

   //��֤�Ƿ������ĳһ��״̬��������������״ֻ̬��ӵ��һ�ַ����棩		by WangZY 2018/09/13
   BOOL TestGXIncludeOtherState (EM_OTHER_STATE_MOD emStateInclude) const;
   BOOL TestGXIncludeOtherState (EM_OTHER_STATE_MOD emStateInclude,EM_OTHER_STATE_MOD emCurState) const;

   //��֤�Ƿ�ӵ��ĳ��״̬��������������״̬����ȫ��ӵ�з����棩		by WangZY 2018/09/13
   BOOL TestGXOtherState(EM_OTHER_STATE_MOD emStateTest);

   //�Ƴ�ĳ��״̬		by WangZY 2018/09/13
   BOOL RemoveOtherState(EM_OTHER_STATE_MOD emStateRemove);

   //���ĳ��״̬		by WangZY 2018/09/13
   BOOL AddOtherState(EM_OTHER_STATE_MOD emStateAdd);

   BOOL GetGongXuSort(CADOConn* pADOConn,__out map<int,CString>& map_gx_sort);
   static CDBProcessInfoData * Instance();	//��ȡ��ָ�룩ʵ��


private:
	static std::shared_ptr<CDBProcessInfoData> sm_inst;
};

class CDBProcessInfoList :
	public CDataListMid
{
DECLARE_SERIAL( CDBProcessInfoList)//���л������л�����Ҫ��ӵ�����
public:
	CDBProcessInfoList();
	~CDBProcessInfoList();

	CDBProcessInfoData* GetItem(int nIndex);			//����������ȡItem
	CDBProcessInfoData* GetItemByName(CString strName);	//�������ƻ�ȡItem
	CDBProcessInfoData* GetItemByID(INT64 nID);			//����ID��ȡItem
   CDBProcessInfoData* GetItemBySortId(int nSortId);//��������IDȡItem
   CDBProcessInfoData* GetSysItem(CDBProcessRecordsData::Assign_Default_ProID nProID);//��ȡ�󶨵�ĳ��CAD�Ĺ���
   CDBProcessInfoData* GetItemByRole(const CString & strRole);//���ݽ�ɫ��ȡ��Ӧ��Item
	int GetIndexByName(CString strName);				//�������ƻ�ȡ����
	int GetIndexByID(INT64 nID);
	void AddItem(CDBProcessInfoData* pItem);			//���Item
	void DeleteItem(int nIndex);						//ɾ���̶�����Item
	void DeleteItemByName(CString strName);				//��������ɾ����ص�item

	void SortBySortID();//���ݹ����SortID�������������
   
	void GetListFromDB(CADOConn *pADOConn);//�����ݿ��ȡ����
	static CDBProcessInfoList * Instance();	//��ȡ��ָ�룩ʵ��


   //************************************
   // Method:    ��ȡ�Ƿ���Ա༭����
   // Author:    wuZhiHua
   // Date : 	  2018/03/26
   // Access:    public 
   // Returns:   BOOL
   // Parameter: CADOConn * pADOConn
   // Parameter: std::map<CString
   // Parameter: bool> & mapProNameCanEditCost
   //************************************
   BOOL GetCanEditCostMap(CADOConn *pADOConn , std::map<CString , bool> &mapProNameCanEditCost);

   static BOOL GetTipPriceFlag(CADOConn* pADo,CString strGXName);

#ifdef USING_GRIDCTRL_MARK
	MAP_GridCtrl_AllData CreateGridData();

#endif // USING_GRIDCTRL_MARK

private:
	static std::shared_ptr<CDBProcessInfoList> sm_inst;
};

