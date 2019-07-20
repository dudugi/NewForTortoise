
#pragma once

/*************************************************
// <�ļ�>: DBCustomInfo.h
// <˵��>: �ͻ���Ϣ��
// <����>: wangzl
// <����>: 2019/02/22
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 

#include "DataMid.h"
class CADOConn;

#include "DBKeyDef.h"
#include "DBKeyDef_V.h"
#include "DBKeyDef_Cust.h"

typedef enum {
   Enum_Customer_None = 0, //Ĭ�ϲ�
   Enum_Customer_ZanBuHeZuo, //�ͻ�״ֵ̬Ϊ�ݲ�����
	Enum_Customer_FinancialLedger, //�ͻ�������ϸ�Ŀͻ�
	Enum_Customer_OrderOutWork,	//������ѯ:ί��ӹ�
	Enum_Customer_JinZhiOrder,	//2017/08/11 zhangt ��ֹ�µ��ͻ�����ֹ�µ����ݲ�������
}Enum_Customer_State;//�ͻ�״̬ö��ֵ yangjr 2017-7-26

class CDBCustomInfoData  : public CDataMid
{
	DECLARE_SERIAL( CDBCustomInfoData)//���л������л�����Ҫ��ӵ�����
public:
	int					m_nID;					//����ID
	COleDateTime		m_oleUpdateTime;		//��������
	CString				m_strCate;				//����
	CString				m_strCusCate;			//�ͻ�����---->�������ֵ�ɸѡ �ͻ�����ѡ��
	CString				m_strCusCode;			//�ͻ�����
	CString				m_strCusName;			//�ͻ�����
	CString				m_strCusAbbrevName;		//�ͻ����
	CString				m_strCusAddr;			//�ͻ���ַ
	CString				m_strCusPerson;			//�ͻ���ϵ��
	CString				m_strCusPhone;			//�ͻ��绰
	CString				m_strCusFax;			//�ͻ�����
	CString				m_strMobile;			//�ͻ��ֻ�
	CString				m_strWeChat;			//�ͻ�΢��
	CString				m_strRemark;			//��ע
	CString				m_strVenWeb;			//�ҵ��µ�ƽ̨
	CString				m_strVenCode;			//�ҵ��µ��ʺ�
	CString				m_strVenPwd;			//�ҵ��µ�����
	CString				m_strCusPwd;			//��¼����
	double				m_fArrears;				//�ڳ����
	double				m_fDeposit;				//��֤��
	double				m_fLimit;				//Ƿ������
	CString				m_strProvince;			//ʡ
	CString				m_strCity;				//��
	CString				m_strArea;				//����
	CString				m_strState;				//״̬
	int					m_nDeliveryDays;		//��������
	int					m_nNum;					//����
	int					m_nLoss;				//���
	CString				m_strEMS;				//���
	CString				m_strParrentCode;		//�ϼ�����
	CString				m_strClerkCode;			//ҵ��Ա���
	CString				m_strRebate;			//����
	CString				m_strWorkDoc;			//Ĭ�ϼӹ���
	CString				m_strTag;				//Ĭ�ϵ���
	CString				m_strDeliveryDoc;		//Ĭ�Ϸ�����
	CString				m_strDepotPos;			//��λ
	CString				m_strSign;				//ǩ��
	CString				m_strCusUnit;			//��λ
	int					m_nCusLv;				//�ȼ�
   CString				m_strNewCusName;			//��ƴ���Ŀͻ�����
   int               m_iTreeGroupID;      //��������ID
   int					m_iJijiaType;				//���ۼۼƼ۷�ʽ��0����ʾ���ۿۣ�1��ʾ������ yangjr 2018/4/18
   double             m_fAddinPrice;       //���ۼۼӼ�        add by lida 2018/05/24
   int               m_bPrintDiaoPai;     //�Ƿ��ӡ����    add by lida 2018/05/24
   int               m_bPrintYuE;         //�Ƿ��ӡ���    add by lida 2018/05/24
   double            m_fZMZheKou; //ר���ۿ� yangjr 2018/8/7
   CString           m_strSalesID;  //ҵ��ԱID add by lida 2018/09/01
public:
	CDBCustomInfoData();
	~CDBCustomInfoData();
	void ResetData();
	void Trim();

	void Copy(CDBCustomInfoData *pData);
	void Serialize(CArchive& ar);
	BOOL GetAllDBInfo(CADOConn *pADOConn);			//��ȡ����������Ϣ
	BOOL InsertAllDBInfo(CADOConn *pADOConn);		//���롾�����������¼�¼
	BOOL UpdateAllDBInfoByID(CADOConn *pADOConn);	//�����˻����¡���������¼
	BOOL DelAllDBInfoByID(CADOConn *pADOConn);		//�����˻�ɾ������������¼
	static CDBCustomInfoData * Instance();			//��ȡ��ָ�룩ʵ��
   BOOL GetAllDBInfoByCusCode(CADOConn *pADOConn,CString strCusCode);//���ݿͻ���Ż�ȡ����������Ϣ yangjr 2018-3-27
   BOOL UpdateStorageZMJ(CADOConn *pADOConn);//���ݿͻ���Ÿ��¶�Ӧ�ͻ���ר���� yangjr 2018/8/22
private:
	static std::shared_ptr<CDBCustomInfoData> sm_inst;
};

class CDBCustomInfoList : public CDataListMid
{
	DECLARE_SERIAL(CDBCustomInfoList)
public:
	CDBCustomInfoList();
	~CDBCustomInfoList();
	CDBCustomInfoData*  GetItem(int nIndex);
	CDBCustomInfoData*  GetItemByCustomID(CString strCustomID);	//���ݿͻ�ID��ȡ��Ӧ��Item
   CDBCustomInfoData*  GetItemByCustomName(CString strCustomName);	//���ݿͻ����ƻ�ȡ��һ����Ӧ��Item 
	int  GetIndexByCustomID(CString strCustomID);				//���ݶ����Ż�ȡ��ȡ����
	void AddItem(CDBCustomInfoData* pItem);
	void DeleteItem(int nIndex);
	void GetListFromDB(CADOConn *pADOConn);						//�����ݿ��ȡ����
	static CDBCustomInfoList * Instance();						//��ȡ��ָ�룩ʵ��

	static void GetCustmerInfo(CADOConn *pADOConn,CDBCustomInfoData* pData);

   //�ж϶�Ӧ������Ա�Ƿ��пͻ� Yangjr 2018-9-1
   BOOL IsSalesHaveCus(CADOConn *pADOConn,CString strSalesID);

#ifdef USING_GRIDCTRL_MARK

   //strSaleID:ҵ��ԱID��bLimitSale:�Ƿ������ƣ����Ʋ鿴��ǰҵ��Ա�Ŀͻ���
	MAP_GridCtrl_AllData CreateGridData(std::vector<int> treeGroupIDLst,CString strSaleID,BOOL bLimitSale = FALSE);
   MAP_GridCtrl_AllData CreateGridData(std::vector<int> treeGroupIDLst,CString strSaleID,CString strCusName,BOOL bLimitSale = FALSE);

   MAP_GridCtrl_AllData CreateGridData(CString strSaleID,BOOL bLimitSale = FALSE);
   BOOL CreateDropPopGridData(const CDBCustomInfoData* pData,MAP_GridCtrl_RowData& row_data);

   BOOL CreateGridData(const CDBCustomInfoData* pData,MAP_GridCtrl_RowData& row_data);
	
	//����һ���յ�������		by WangZY 2017/08/24
	BOOL GetEmptyRowData(__out MAP_GridCtrl_RowData &mapEmptyRowData);
	
	//�����ύ�����޸�		by WangZY 2017/08/24
	BOOL SaveMultiModifyData(__in CADOConn *pADOConn, __in MAP_GridCtrl_AllData &mapAddData,
		__in MAP_GridCtrl_AllData &mapModifyData, __in MAP_GridCtrl_AllData &mapDeleteData,
		__in CString strMaker);

	//��ȡ��Ӧ����Ϣ, add by lida 2017/06/15
	MAP_GridCtrl_AllData CreateGridData_Cumstomer(CADOConn *pADOConn,CString strFilter,Enum_Customer_State stateType);
	//��ȡ��Ӧ����Ϣ1, add by lida 2017/07/03
   // ���Ӱ�����ƽӿ� Ĭ�ϰ��� 2018-6-11 wangzl
	MAP_GridCtrl_AllData CreateGridData_Cumstomer_1(CADOConn *pADOConn,BOOL bHasAbbreviation = TRUE);
	//��ȡ��Ӧ����Ϣ2��add by lida 2017/08/29 -- ��������¼��
	MAP_GridCtrl_AllData CreateGridData_Cumstomer_OrderEntry(CADOConn *pADOConn,__out map<CString/*CusCode*/,CString/*iDays*/>& map_CusDays);

   //��ȡ��Ӧ�ͻ����͵����ų��ݲ����������пͻ����� yangjr 2017-12-12
   MAP_GridCtrl_AllData CreateGridData_CumstomerByCate(CADOConn *pADOConn,CString strFilterCusCate);

   CString GetQianKuanJinEr(CADOConn *pADOConn,CString cusCode);//��ȡ��ǰ�ͻ����ۻ�Ƿ���� yangjr 2017-07-28
   //��ȡ��ǰǷ��Ӧ�̵Ľ�� yangjr 2018/1/9
   CString GetQianGongYingShangKuanJinEr(CADOConn *pADOConn,CString cusCode);

   CString GetCusQKLimit(CADOConn *pADOConn,CString cusCode);	//��ȡ��ǰ�ͻ���Ƿ������ add by lida 2017/08/09
   CString GetNewCusCode(CADOConn* pADOConn);					//��������һ���ͻ���ţ������ϴα���Ŀͻ�����
   //sqr��ʽ ��ȡ��ǰ�ͻ����ۻ�Ƿ���� yangjr 2018-4-9
   CString GetNewQianKuanJinEr(CADOConn *pADOConn,CString cusCode);

   BOOL GetKeHuDuiZhang(CADOConn* pADOConn,CString strBegTime,CString strEndTime,MAP_GridCtrl_AllData& map_all_data);

   BOOL GetCusPrintFlag(CADOConn* pADOConn,CString strCusCode,__out int& iPrintDp,__out int& iPrintYE); //��ȡ�ͻ���ӡ��ʶ


#endif // USING_GRIDCTRL_MARK
   void GetAllDBInfoCusName_BasicInfo(vector<CString> &vecCusName);// ��ȡ���еĿͻ����ƣ�������Ϣר�� liuhw 2019/05/21

private:
	static std::shared_ptr<CDBCustomInfoList> sm_inst;
};

//�ͻ�excel����
typedef struct my_customer_info
{
   my_customer_info()
   {
      m_nID = -1;				
      m_nDeliveryDays = -1;
      m_nCusLv = -1;			
      m_iTreeGroupID = -1; 
      m_iJijiaType = -1;		
      m_bPrintDiaoPai = -1;
      m_bPrintYuE = -1;    
      m_fZMZheKou = -1;    
      m_fAddinPrice = -1;  
      m_fArrears = _T("");		
      m_fDeposit = -1;		
      m_fLimit = -1;			
      m_oleUpdateTime  = COleDateTime::GetCurrentTime();
      m_strCate = _T("");			
      m_strCusCate = _T("");		
      m_strCusCode = _T("");		
      m_strCusName = _T("");		
      m_strCusAddr = _T("");		
      m_strCusPerson = _T("");	
      m_strCusPhone = _T("");		
      m_strCusFax = _T("");		
      m_strMobile = _T("");		
      m_strRemark = _T("");		
      m_strVenWeb = _T("");		
      m_strCusPwd = _T("");		
      m_strProvince = _T("");		
      m_strCity = _T("");			
      m_strEMS = _T("");			
      m_strClerkCode = _T("");	
      m_strSalesID = _T("");
      m_strCusAbbrevName = _T("");
   };

   CString GetUpdateSql(BOOL bIgnoreNull = TRUE);
   

   CString GetInsertSql();
   

   int            m_nID;					//����ID
   int            m_nDeliveryDays;		//��������
   int            m_nCusLv;				//�ȼ�
   int            m_iTreeGroupID;      //��������ID
   int            m_iJijiaType;			  //���ۼۼƼ۷�ʽ��0����ʾ���ۿۣ�1��ʾ������ yangjr 2018/4/18  
   int            m_bPrintDiaoPai;        //�Ƿ��ӡ����    add by lida 2018/05/24
   int            m_bPrintYuE;            //�Ƿ��ӡ���    add by lida 2018/05/24
   double         m_fZMZheKou;            //ר���ۿ� yangjr 2018/8/7
   double         m_fAddinPrice;          //���ۼۼӼ�        add by lida 2018/05/24
   CString         m_fArrears;				//�ڳ����
   double         m_fDeposit;				//��֤��
   double         m_fLimit;				   //Ƿ������
   COleDateTime   m_oleUpdateTime;		//��������
   CString        m_strCate;				//����
   CString        m_strCusCate;			//�ͻ�����---->�������ֵ�ɸѡ �ͻ�����ѡ��
   CString        m_strCusCode;			//�ͻ�����
   CString        m_strCusAbbrevName;  //�ͻ����
   CString        m_strCusName;			//�ͻ�����
   CString        m_strCusAddr;			//�ͻ���ַ
   CString        m_strCusPerson;			//�ͻ���ϵ��
   CString        m_strCusPhone;			//�ͻ��绰
   CString        m_strCusFax;			//�ͻ�����
   CString        m_strMobile;			//�ͻ��ֻ�
   CString        m_strRemark;			//��ע
   CString        m_strVenWeb;			//�ҵ��µ�ƽ̨
   CString        m_strCusPwd;			//��¼����
   CString        m_strProvince;			//ʡ
   CString        m_strCity;				//�� 
   CString        m_strEMS;				//���
   CString        m_strClerkCode;			//ҵ��Ա���
   CString        m_strSalesID;        //ҵ��ԱID add by lida 2018/09/01 
}s_my_customer_info;
