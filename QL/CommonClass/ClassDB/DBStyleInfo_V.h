#pragma once
/*************************************************
// <�ļ�>: DBStyleInfo_V.h
// <˵��>: ���ݿ������-��ʽ��ͼ
// <����>: yangjr
// <����>: 2019/02/20 16:34:46
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
#include "DataMid.h"
#include "DBStyleInfo.h"

using namespace std;

class CADOConn;

typedef struct filter_data
{
   int iClassID;           //ϵ��ID, ID=-1ʱ��ʾȫ����ϵ��
   CString strClassName;   //ϵ������
   CString strKsYears;     //��ݼ���
   CString strKsPinPai;    //Ʒ��
   CString strKsCode;      //��� -- ��ʽ�޸Ľ�����

   //���Ŀ�ʽϵ��ʱ������ʽ����Ϣ���أ�ˢ�¿�ʽϵ������Ϣ
   int iClassID_old_Modify;   
   int iClassID_new_Modify;
   CString strKsCode_Modify;


   CString strDateType;      //��������   	by WangZY 2019/05/17
   CString strDateBegin;     
   CString strDateEnd;
   CString strTheme;          //����   by WangZY 2019/05/17 
   CString strStyleType;      //����   by WangZY 2019/05/17 
   CString strClothType;      //Ʒ��   by WangZY 2019/05/17 
   CString strFinishState;    //������   by WangZY 2019/05/17
   CString strCusId;          //�ͻ�ID	by WangZY 2019/05/17
   CString strGongyishiId;    //����ʦID  by WangZY 2019/05/17
   CString strShejishiId;     //���ʦID  by WangZY 2019/05/17
   CString strZhibanshiId;    //�ư�ʦID   by WangZY 2019/05/17
   CString strShell;          // ���¼� liuhw 2019/05/22
   CString strStyleFollow;    // ��ע liuhw 2019/05/22
   CString strVersion;//�汾
   CString strNeedle;   //����

   enum{
      en_Null= 0,//������ɸѡ
      en_ToBeProcessed ,//������
      en_PendingSubmission,//���ύ
      en_Completed,//�����
   };

   int     nFilterType;       //���˵�����  ������ ���ύ �����
   int     nCurGxSortID;     //��ǰ����ID
   CString strMainRawMaterial;//��ԭ�� yangjr 2019/07/10

   filter_data()
   {
      iClassID = 0;
      strClassName = _T("");
      strKsYears = _T("");
      strKsPinPai = _T("");
      strKsCode = _T("");

      iClassID_old_Modify = 0;
      iClassID_new_Modify = 0;
      strKsCode_Modify = _T("");
      nFilterType = en_Null;
      nCurGxSortID = 0;
      strMainRawMaterial = _T("");
   };

}s_filter_data;

//wangzl ��ʽ��ͼ�� 2017/7/14 
class CDBStyleInfoData_V :
	public CDataMid
{
public:
	CDBStyleInfoData_V(void);
	~CDBStyleInfoData_V(void);

	virtual void ResetData();

	virtual void Copy(CDBStyleInfoData_V * pData);

	void ToDBData(CDBStyleInfoData &);
   //������������Ϣ
   void CopyBasicInfo(CDBStyleInfoData_V * pData);

	BOOL GetAllDBInfo(CADOConn *pADOConn);		//��ȡ����������Ϣ

	//ֻ��ȡ��Ҫ���ֶ���Ϣ		by WangZY 2018/05/29
	BOOL GetAllDBInfoWithNecessaryField(CADOConn *pADOConn );
public:
	int				m_nID				;//
	COleDateTime	m_oleUpdateTime		;//
	CString			m_strTypeName		;//
	CString			m_strStyleNo		;//
	CString			m_strStyleName		;//
   CString        m_strYarnCate;    //ɴ�����
	CString			m_strStyleIntro		;//
	COleDateTime	m_oledtCreatTime	;//
   CString        m_strKsYears;        //��ݼ���

   CString        m_strCraftsmen;    //����ʦ
   CString        m_strPatternMaker;    //�ư�ʦ
   CString        m_strClassType;   //�·�������

   // �淿������ʽ������-----start liuhw 2019/05/08
   CString        m_dtExpireTime;    //��������
   CString        m_strCreator;        //������
   CString        m_strCreateType;     //��������
   CString        m_strTheme;          //����
   CString        m_strCusCode;       //�ͻ�
   CString        m_strCusKuanhao;     //�ͻ����
   CString        m_strProcessStatus;  //����״̬
   CString        m_strEdition;        //�汾

   CString        m_strDesigner;       //���ʦ
   CString        m_dtMakingOrdTime; //��������
   CString        m_strMainMaterial;   //��ԭ��
   CString        m_strVersionNum;     //�浥��
   CString        m_strSinglePerson;   //�Ƶ���
   int            m_nCheckState     ;//�������״̬
   CString        m_strCheckPerson  ;//������������

   int            m_nVersionState   ;
   CString        m_strVersionPerson;

   int            m_iUpOrDownShell;  //���¼� 1�ϼ� 0�¼�
   int            m_iFollow;         //��ע 1��ע 0����ע

   CString        m_strMainPic;      //��ʽ��ͼ 

   // �淿������ʽ������-----end liuhw 2019/05/08
   CString			m_strPinMing			;//Ʒ�� yangjr2018/5/11
   int    m_bIsDeleted;//��ʽ�Ƿ�ɾ�� yangjr 2019/05/20

   int           m_nGXSortID       ;
   CString       m_strGXPersonCode ;
   CString       m_strState        ;
   CString       m_strFangAnName   ;
   CString  m_strPrority;  //���ȼ�
   CString  m_strNeedleType;  //����
   CString  m_strStyleDescription;  //����
   CString  m_strModelMainPic;//չʾͼ��ͼ
   int m_nSortIndex;
   CString  m_strBrand        ;//Ʒ��
   CString  m_strCustomField1 ;//�Զ����ֶ�1 
   CString  m_strCustomField2 ;//�Զ����ֶ�2 
   CString  m_strCustomField3 ;//�Զ����ֶ�3 
   CString  m_strCustomField4 ;//�Զ����ֶ�4 
   CString  m_strCustomField5 ;//�Զ����ֶ�5 
   CString  m_strCustomField6 ;//�Զ����ֶ�6 
   CString  m_strCustomField7 ;//�Զ����ֶ�7 
   CString  m_strCustomField8 ;//�Զ����ֶ�8 
   CString  m_strCustomField9 ;//�Զ����ֶ�9 
   CString  m_strCustomField10;//�Զ����ֶ�10

   double   m_dTotalCost;     //�ܳɱ�
   double   m_dTotalOffer;    //�ܱ���

   CString  m_strHelpSeekerID; //���Ŀǰ������״̬����Ϊ������ID������Ϊ���ַ��� by duchen

   //��ǣ��������ݿ���
   BOOL  m_bCostAndOfferChanged; //�ɱ��ͼ۸��Ƿ��޸�
};

class CDBStyleInfoList_V:public CDataListMid
{
public:
	CDBStyleInfoList_V();
	~CDBStyleInfoList_V();

	CDBStyleInfoData_V*  GetItem(int nIndex);
	CDBStyleInfoData_V*  GetItemByStyleNo(CString strStyleNo);//���ݿ�ʽ�źŻ�ȡ��ȡItem
   CDBStyleInfoData_V*  GetItemByID(int nStyleID);//���ݿ�ʽ�źŻ�ȡ��ȡItem
	int  GetIndexByStyleNo(CString strStyleNo);			//���ݶ����Ż�ȡ��ȡ����
	void    AddItem(CDBStyleInfoData_V* pItem);
	void    DeleteItem(int nIndex);

    BOOL GetStyleInfo(CADOConn* pADOConn,CString strKuanhao,__out CDBStyleInfoData_V* pObj);
   
   //���ݿ�Ż�ȡ�޸�ʱ��		by WangZY 2018/08/31
   static BOOL GetStyleUpdateDateByStyleNo(__in CADOConn* pADOConn,
      __in CString strKuanhao, __out CString &strDate);


   enum ks_show_type
   {
      ks_type_show_all = -1,     //��ʾ���п�ʽ
      ks_type_show_no_class = 0,   //��ʾδ��ϵ�п�ʽ
   };

	//ֻ��ȡ��Ҫ���ֶ���Ϣ		by WangZY 2018/05/29
	BOOL GetListFromDBWithNecessaryField(CADOConn *pADOConn);//�����ݿ��ȡ��������

   //����ID�Ż�ȡ����������Ϣ yangjr2017-9-20
   BOOL GetListFromDBByID(CADOConn *pADOConn,CString strID,CDBStyleInfoData_V &data);
	static CDBStyleInfoList_V * Instance();//��ȡ��ָ�룩ʵ��

   static BOOL GetStyleCostAndOffer(CADOConn* pAdo,CDBStyleInfoData_V *data);  //���»�ȡ��ʽ�ĳɱ�������

#ifdef USING_GRIDCTRL_MARK
	MAP_GridCtrl_AllData CreatrGridData();
   MAP_GridCtrl_AllData CreatrGridData_Kuanhao();

   
   MAP_GridCtrl_RowData GetRowData(CDBStyleInfoData_V* pData);

	//����һ���յ�������		by WangZY 2017/08/24
	BOOL GetEmptyRowData(__out MAP_GridCtrl_RowData &mapEmptyRowData);

	//�����ύ�����޸�		by WangZY 2017/08/24
	BOOL SaveMultiModifyData(__in CADOConn *pADOConn, __in MAP_GridCtrl_AllData &mapAddData,
		__in MAP_GridCtrl_AllData &mapModifyData, __in MAP_GridCtrl_AllData &mapDeleteData,
		__in CString strMaker);

#endif // USING_GRIDCTRL_MARK

private:
	static std::shared_ptr<CDBStyleInfoList_V> sm_inst;

};

