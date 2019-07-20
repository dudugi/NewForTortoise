#pragma once
/*************************************************
// <�ļ�>: DBColorPriceSet.h
// <˵��>: ���ݲ�����-�۸��������ݱ�
// <����>: yangjr
// <����>: 2017-7-13 15:59:15
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 

#include "DataMid.h"
#include <map>
#include <vector>

class CADOConn;
class CDBDataColorPriceSet :public CDataMid
{
   DECLARE_SERIAL( CDBDataColorPriceSet)//���л������л�����Ҫ��ӵ�����
public:
   CDBDataColorPriceSet(void);
   ~CDBDataColorPriceSet(void);
public:
   CString		m_str_dDate      ;  //����
   CString		m_str_iSunhao    ;  //���
   CString		m_str_iSalePrice ;  //���۵���
   CString		m_str_iPrice     ;  //����
   CString		m_str_cDaihao    ;  //Ʒ�ִ���
   CString		m_str_cCate      ;  //Ʒ��
   CString		m_str_cCusCode   ;  //�ͻ����
   CString		m_str_ID         ;  //ID
   CString		m_str_cCusCate   ;  //�ͻ�����
   CString		m_str_cCusName   ;  //�ͻ�ȫ��
   //CString		m_str_cCusAbbName;  //�ͻ����
   //CString		m_str_vCusAbbName;  //�ͻ�
   CString		m_str_fZMDSalePrice;  //ר�������۵���
   CString		m_str_fZhekou;  //�ۿ�
	CString		m_str_cChenfen;	//�ɷ�
   CString     m_str_fBeiLv ;   //����    add anjie by 2018/10/25

public:
   static CDBDataColorPriceSet * Instance();//��ȡ��ָ�룩ʵ��
   BOOL GetAllDBInfo(CADOConn *pADOConn);		//��ȡ����������Ϣ 

   void ResetData();
   void Copy(CDBDataColorPriceSet *pData);
   void Serialize(CArchive& ar);
   //�Ƚ��޸�ǰ�����ݣ����޸��˵����ݱ�������
   CString SetDBEquals_Log(CDBDataColorPriceSet &pOldData);
#ifdef USING_GRIDCTRL_MARK
   void ToGridDB(MAP_GridCtrl_RowData *pRowData); //���ת��ΪDB���� liuhw 2018/09/15
#endif // USING_GRIDCTRL_MARK
	//����Ʒ�ֵĿͻ���ȡ�۸���Ϣ		by WangZY 2018/04/22
	BOOL GetInfoByCateAndCusCode(CADOConn *pADOConn,
		CString strColorCate,CString strCusCode);
private:
   static std::shared_ptr<CDBDataColorPriceSet> sm_inst;
};

class CDBDataColorPriceSetInfoList : public CDataListMid
{
   DECLARE_SERIAL(CDBDataColorPriceSetInfoList)

public:
   CDBDataColorPriceSetInfoList();
   ~CDBDataColorPriceSetInfoList();

   //add by lida 2018/09/20 ��ȡ�ͻ��ɷ�
   CString GetChengfen(CADOConn* pADOconn,CString strCusCode,CString strSehao);
   void AddItem(CDBDataColorPriceSet* pItem);
   //add by lida 2017/08/29 ��ȡɫ�ŵ��ۣ���������¼�����
   CString GetClrPriceDataInfo(CADOConn* pADOConn,CString strSehao,CString strCusCode);

   static CDBDataColorPriceSetInfoList * Instance();		//��ȡ��ָ�룩ʵ��  
   BOOL GetListFromDB(CADOConn * pADOConn);   
   static std::shared_ptr<CDBDataColorPriceSetInfoList> sm_inst;
   BOOL DeleteOneByID(CADOConn *pADOConn,CString strID);
#ifdef USING_GRIDCTRL_MARK
   BOOL GetDataFromDB(CADOConn *pADOConn,MAP_GridCtrl_AllData &allData);
   BOOL UpdateOneByID(CADOConn *pADOConn,const MAP_GridCtrl_RowData &oneRow);
   BOOL InsertOne(CADOConn *pADOConn,const MAP_GridCtrl_RowData &oneRow); 
	//��ȡһ�п�������		by WangZY 2017/08/22
	BOOL GetEmptyRowData(__out MAP_GridCtrl_RowData &mapEmptyRowData);

	//�����ύ�����޸�		by WangZY 2017/08/23
	BOOL MultiModifyData(__in CADOConn *pADOConn, __in MAP_GridCtrl_AllData &mapAddData,
		__in MAP_GridCtrl_AllData &mapModifyData, __in MAP_GridCtrl_AllData &mapDeleteData,
		__in CString strMaker);
	
	//�����������ݵĽӿ�		by WangZY 2017/08/27
	MAP_GridCtrl_AllData CreateGridData();

#endif  // USING_GRIDCTRL_MARK
   //��Ӧ�ͻ���Ʒ�ִ����ڼ۸����ñ����Ƿ���ڲ����ڶ�Ӧid����ͬ���� yangjr 2017-8-9
   BOOL IsExitSameDataModify(CADOConn *pADOConn,CString strCusCode,CString strDaihao,CString strID,CString strPinZhong);
   //��Ӧ�ͻ���Ʒ�ִ����ڼ۸����ñ����Ƿ������ͬ���� yangjr 2017-8-9
   BOOL IsExitSameDataAdd(CADOConn *pADOConn,CString strCusCode,CString strDaihao,CString strPinZhong);
   //float GetSalePrice(CString m_str_cCusCode,CString cDaiHao);
   //����(�ͻ�+Ʒ��+����)��(�ͻ�+Ʒ��)��(Ʒ��+����)������ȡ�۸��Ҳ�������NULL yangjr 2018/4/22
   CDBDataColorPriceSet *GetPriceData( CString str_cCusCode,CString strCate,CString cDaiHao);
   BOOL GetPriceDataNew(CString strCate,CString strCf,CString& strPrice);
   //CString GetYarnSalePrice(CString strCusCode,CString strCate);
   BOOL GetTodayDate(CADOConn *pADOConn,CString &date);//��ȡ��ǰʱ����-��-��yangjr 2017-8-9
   //add by lida 2017/07/28
   //��ȡƷ�ִ��� -- ������������
   vector<CString>	GetDaiHao(CADOConn *pADOConn);
   static BOOL UpdateYarnZMJ(CADOConn *pADOConn,std::vector<CString>vecID,double fBeilv,BOOL bBeilv = TRUE);
private:
#ifdef USING_GRIDCTRL_MARK
   void InsertRowData(CString strFiedID,CString strValue,MAP_GridCtrl_RowData& map_row_data,ENUM_FIELDTYPE_DATA nFieldType= CB_enum_FieldData_CString,ENUM_FIELDTYPE_CONTROL nFieldTypeCtr= CB_enum_FieldCtrl_Text);
#endif  // USING_GRIDCTRL_MARK
   CDBDataColorPriceSet*  GetItem(int nIndex);			//����������ȡItem
   void DeleteItem(int nIndex); 
  
};


typedef struct my_ColorPriceSet
{
   my_ColorPriceSet()
   {
      ResetData();
   };

   void ResetData();
   CString GetInsertSql();
   CString GetUpdateSql();
   CString GetLog();
   void CheckData();

   CString		m_str_ID         ;  //ID
   CString		m_str_dDate      ;  //����
   CString		m_str_iSunhao    ;  //���
   CString		m_str_iSalePrice ;  //���۵���
   CString		m_str_iPrice     ;  //����
   CString		m_str_cDaihao    ;  //Ʒ�ִ���
   CString		m_str_cCate      ;  //Ʒ��
   CString		m_str_cCusCode   ;  //�ͻ����
   CString		m_str_cCusName   ;  //�ͻ�����
   CString		m_str_fZMDSalePrice;  //ר�������۵���
   CString		m_str_fZhekou;  //�ۿ�
   CString		m_str_cChenfen;	//�ɷ�
   CString      m_str_fBeiLv ;   //����    add anjie by 2018/10/25
}s_my_ColorPriceSet;
