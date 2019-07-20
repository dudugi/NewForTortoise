#pragma once
/*************************************************
// <�ļ�>: DBPinZhongSetting.h
// <˵��>: ���ݲ�����-ɴ��Ʒ��ά����
// <����>: yangjr
// <����>: 2019/02/20 16:21:05
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 

#include "DataMid.h"
#include "DBKeyDef.h"
#include <set>

using namespace std;

class CADOConn;

class CDBPinZhongSetting : public CDataMid
{
public:
	CDBPinZhongSetting(void);
	~CDBPinZhongSetting(void);

	virtual void ResetData();

	virtual void Copy(CDBPinZhongSetting * pData);

	void GetAllDataInfo(CADOConn *pADOConn);

   BOOL InsertDBInfo(CADOConn *pADOConn);
   
   BOOL UpdateChenfenByID(CADOConn *pADOConn);
   BOOL DelAllDBInfoByID(CADOConn *pADOConn);		//ɾ������������¼
   //�Ƚ��޸�ǰ�����ݣ����޸��˵����ݱ�������
   CString SetDBEquals_Log(CDBPinZhongSetting &pOldData);
	//���� Ʒ������ ��ȡ������Ϣ		by WangZY 2018/04/22
	BOOL GetInfoByCate(CADOConn *pADOConn,CString strCate);
public:
	int			m_ID;
   CString		m_cCate;			//ɴ��Ʒ��
   CString		m_cChenfen;			//�ɷ�
   CString     m_strfSalePrice;//���۵��� 2λС��
   CString		m_cZhiXingBiaoZun;	//ִ�б�׼
   CString     m_strfFahuoSunhao;//������� 2λС��
   CString     m_strfShoufaMaxSunhao;//�շ�������(kg) 4λС��
   CString     m_strisKoukuan;//���������Ŀۿ�
   CString     m_strfZMDSalePrice;//ר�������۵���
   CString     m_strfZhekou;//�ۿ� 2λС��
   CString     m_strfKouKuanPrice;//�ۿ��
   CString     m_strPWeight      ;//ȥƤ����    add anjie by 2018/09/27
   CString     m_cProductName;   ///��Ʒ����    add liuhw by 2018/10/08
   CString     m_strBeiLv;       //����   ��λС��     add anjie by 2018/09/27
   CString     m_strYarnCode;    //ɴ��������  add liuhw by 2018/11/13
   int         m_iCheckOuterYarn;   //����ɴ�� add by lida 2019/03/06
   CString     m_strPrintYarn;      //��ӡɴ�� add anjie by 2019/03/30
   CString     m_strChengbenPrice;  //�ɱ����� add by lida 2019/06/04
};

class CDBPinZhongSettingList: public CDataListMid
{
public:
   CDBPinZhongSettingList();
	~CDBPinZhongSettingList();
	static CDBPinZhongSettingList * Instance();//��ȡ��ָ�룩ʵ��
      
   void  AddItem(CDBPinZhongSetting* pItem);
   CDBPinZhongSetting*  GetItem(int nIndex);
   void DeleteItem(int iID);   
   CDBPinZhongSetting *GetItemByID(int iID);   
   CDBPinZhongSetting *GetItemByCate(CString strCate);
   void GetYarnCF_Cate_Info(__in CADOConn *pADOConn,__in CString strCate,__out CString &strCF);// ����ɴ������ȡɴ�߳ɷ� liuhw 2019/03/01
   void GetListFromDB(CADOConn *pADOConn);//�����ݿ��ȡ����
   static BOOL UpdateYarnZMJ(CADOConn *pADOConn,std::vector<CString>vecID,double fBeilv,BOOL bBeilv = TRUE);
   BOOL GetFahuoSunhao(__in CADOConn *pADOConn,__in CString strYarnCate,__out CString& strFHSH);
   static BOOL GetYarnOuterFlag(__in CADOConn* pAdo,__in CString strYarnCate);   //��ȡ���ɴ������
#ifdef USING_GRIDCTRL_MARK
   MAP_GridCtrl_AllData GetMapGridData();
   MAP_GridCtrl_AllData GetMapGridDataBelLv();
   MAP_GridCtrl_AllData GetMapEasyGridDataBelLv(); //��ȡ����ɴ����Ϣ add anjieby 2019/04/15
#endif //USING_GRIDCTRL_MARK   
protected:
	

private:
	static std::shared_ptr<CDBPinZhongSettingList> sm_inst;

};

