/*************************************************
// <�ļ�>: DBStyleInfo.h
// <˵��>: ��ʽ�Լ���Ӧ��ɴ����Ϣ
// <����>: wangzl
// <����>: 2019/01/30 10:26:38
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
#pragma once

#include "DataMid.h"
#include <map>
class CADOConn;

//�������  ���ڴ�������ʱ���Ϊ�յ����ݽ��еĴ���
#define ANY_STYLE_NO		_T("0000")

class CDBStyleInfoData  : public CDataMid
{
	DECLARE_SERIAL( CDBStyleInfoData)//���л������л�����Ҫ��ӵ�����
public:
	int            m_nID;               //����ID
	COleDateTime   m_oleTimeUpdate;     //����ʱ��
   CString        m_strTypeName;       //����
   CString        m_strStyleNo;        //��ʽ��
   CString        m_strStyleName;      //��ʽ����
   CString        m_strYarnCate;       //ɴ�����
	CString        m_strStyleIntro;     //��ʽ˵��
	COleDateTime   m_oleTimeCreate;     //��������ʱ��
   CString        m_strKsYears;        //��ݼ���
   int            m_nColorNum;          //��ɫ��
   int            m_nColorSuitNum;     //��ɫ����
   CString        m_strBasicNum;       //����
   int            m_nIncreaceNum;      //������������
   CString        m_strPinMing;        //Ʒ�� yangjr2018/5/11
   // �淿������ʽ������-----start liuhw 2019/05/08
   CString m_dtExpireTime;    //��������
   CString m_strCreator;        //������
   CString m_strCreateType;     //��������
   CString m_strTheme;          //����
   CString m_strCusCode;       //�ͻ�
   CString m_strCusKuanhao;     //�ͻ����
   CString m_strProcessStatus;  //����״̬
   CString m_strEdition;        //�汾

   CString m_dtMakingOrdTime; //��������
   CString m_strMainMaterial;   //��ԭ��
   CString m_strVersionNum;     //�浥��
   CString m_strSinglePerson;   //�Ƶ���
   CString m_strMainPic;      //��ʽ��ͼ 	by WangZY 2019/05/16
   int     m_iUpOrDownShell;  //���¼� 1�ϼ� 0�¼�
   int     m_iFollow;         //��ע 1��ע 0����ע
   // �淿������ʽ������-----end liuhw 2019/05/08
   int    m_bIsDeleted;//��ʽ�Ƿ�ɾ�� yangjr 2019/05/20
   CString  m_strState;//״̬
   CString  m_strFangAnName;
   CString  m_strPrority;  //���ȼ�
   CString  m_strNeedleType;  //����
   CString  m_strModelMainPic;//չʾͼ��ͼ
   int  m_nSortIndex;//չʾͼ��ͼ����˳��
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

   int      m_nGXSortID       ;//��ǰ��������ID
   CString  m_strGxPersonCode ;//����ִ����

   //�������ݿ��ֶ���
   CString        m_strActLog;   //������־���ݵ����
public:
	CDBStyleInfoData();
	~CDBStyleInfoData();
	void ResetData();
	void Copy(CDBStyleInfoData *pData);
	//void Serialize(CArchive& ar);
	BOOL GetAllDBInfo(CADOConn *pADOConn);		//��ȡ����������Ϣ
	BOOL InsertAllDBInfoByStyleNo(CADOConn *pADOConn);	//���롾�����������¼�¼
	BOOL UpdateAllDBInfoByStyleNo(CADOConn *pADOConn);	//���ݿ�ʽ�źŸ��¡���������¼
   BOOL UpdateBasicInfoByStyleNo(CADOConn *pADOConn);// ���»�����Ϣ���� liuhw 2019/05/22
   BOOL UpdateShellDBInfoByStyleNo(CADOConn *pADOConn,int iShell,CString strStyleNo);// ���ݿ�Ÿ������¼� liuhw 2019/05/20
   BOOL UpdateFollowDBInfoByStyleNo(CADOConn *pADOConn,int iFollow,CString strStyleNo);// ���ݿ�Ÿ������¼� liuhw 2019/05/20
   CString GetUpdateSizeInfoToBasicSize(CString strStyleNo,CString strBasicSize);// ���¿�ʽ�Ļ������� liuhw 2019/05/26
	BOOL DelAllDBInfoByStyleNo(CADOConn *pADOConn);		//���ݿ�ʽ�ź�ɾ������������¼
   CString GetDelAllDBInfoByStyleNoSql(CString strStyleNo);
   BOOL IsRepeatStyleNo(CADOConn *pADOConn);//�жϿ���Ƿ��ظ�
   //�Ƚ��޸�ǰ�����ݣ����޸��˵����ݱ�������
   CString SetDBEquals_Log(CDBStyleInfoData &pOldData);

	void DestroyAllLinkInfo(CADOConn *pADOConn);


   BOOL GetAllDBInfoByKuanHao(CADOConn *pADOConn,CString strKuanhao);		//��ȡ����������Ϣ yangjr 2018-3-29
	void Trim();
	static CDBStyleInfoData * Instance();//��ȡ��ָ�룩ʵ��

   //���ݿ�ʽ��������ͼ��Ϣ  	by WangZY 2019/05/16
   static BOOL UpdateSetNewMainPicByStyleNo(CADOConn *pADOConn,CString strStyleNo, CString strMainPicName);
   static BOOL UpdateSetNewModelMainPicByStyleNo(CADOConn *pADOConn,const CString & strStyleNo,const CString & strMainPicName);
   CString GetDelSqlString(int nID,int nIsDeleted=1);
   CString GetDelSqlByStyleNo(CString strStyleNo,int nIsDeleted);
private:
	static std::shared_ptr<CDBStyleInfoData> sm_inst;
};

class CDBStyleInfoList : public CDataListMid
{
	DECLARE_SERIAL(CDBStyleInfoList)
public:
	CDBStyleInfoList();
	~CDBStyleInfoList();
	CDBStyleInfoData*  GetItem(int nIndex);
	CDBStyleInfoData*  GetItemByStyleNo(CString strStyleNo);//���ݿ�ʽ�źŻ�ȡ��ȡItem
	int  GetIndexByStyleNo(CString strStyleNo);			//���ݶ����Ż�ȡ��ȡ����
	void    AddItem(CDBStyleInfoData* pItem);
	void    DeleteItem(int nIndex);

	void GetListFromDB(CADOConn *pADOConn);//�����ݿ��ȡ����
	int GetStyleSaleCount();	//��ȡ�ϼܿ�ʽ��Ŀ
	void ResetData();

	BOOL GetStyleInfoByStyleNo(CADOConn *pADOConn,CString strStyleNo,__out CDBStyleInfoData& pData);

   BOOL GetKuanShi(CADOConn* pADOConn,vector<CString>& vecKS);

   BOOL GetKS_TreeName_KM(CADOConn* pADOConn,CString strKS,CString& strTreeName,CString& strKM,CString& strKouZhong);   //��ȡ��ʽ���࣬���� add by lida 2018/04/04

   BOOL CheckKsIsExists(CADOConn* pADOConn,CString strKsCode);  //������Ƿ����

   static BOOL GetBaseSizeAndWeightPercent(CADOConn* pADOConn,CString strKsCode,CString& strBaseSize,CString& strWeightPercent);

   static BOOL UpdateWeightPercent(CADOConn* pADOConn,CString strKsCode,CString& strWeightPercent);

	static CDBStyleInfoList * Instance();//��ȡ��ָ�룩ʵ��
private:
	static std::shared_ptr<CDBStyleInfoList> sm_inst;
	int m_nSaleCount;
};


typedef struct my_ks_info
{
   my_ks_info()
   {
      m_iClassID = -1;          //ϵ��ID    add by lida 2018/05/11
      m_strTypeName = _T("");			//��������(���������ֵ�)
      m_strStyleNo = _T("");			//��ʽ��
      m_strStyleName = _T("");		//��ʽ����
      m_strYarnCate = _T("");       //ɴ�����
      m_strIngredient = _T("");		//�ɷ�
      m_strJinXian = _T("");			//����
      m_strColorNo = _T("");			//ɫ��
      m_strMatchColor = _T("");		//��ɫ
      m_strStyleIntro = _T("");		//��ʽ˵��
      m_strBarCode = _T("");			//��Ʒ����
      m_fLessWeight = -1;			//����      
      m_strIntro = _T("")	;			//˵��
      m_nDefine = -1;				//����   <---------------------------Ԥ����ɴ����
      m_strDefine1 = _T("");			//����1   <--------- ����Ϊ���ͻ�����, 2018-03-23
      m_strDefine2 = _T("");			//����2  <--------- ����Ϊ��������۸�, 2018-03-23
      m_strDefine3 = _T("");			//����3  <--------- ����Ϊ�����۸�, 2018-03-23
      m_strDefine4 = _T("");			//����4  <--------- ����Ϊ�����Ƽ۸�, 2018-03-23
      m_strNeedleType = _T("");		//����
      m_strFindKey  = _T("");			//�ؼ���
      m_fWeight = -1;				//����
      m_bExec3D = -1;				//�Ƿ����3Dģ��ı�ʶ
      m_dwAttriEx = -1;         //��չ����
      m_strLingXing = _T("");       //����
      m_strDiBian = _T("");         //�ױ�
      m_strXiuKou = _T("");         //���
      m_strPinMing = _T("");        //Ʒ�� yangjr2018/5/11
      m_strHouDaoInfo = _T("");     //�����Ϣ yangjr2018/5/11
      m_strPinPai = _T("");         //Ʒ��
      m_strKsYears = _T("");        //��ݼ���
      m_iFanLiFlag = -1;
      m_strGYPerson = _T("");    
      m_strZBPerson = _T("");
      m_strCeLiang = _T("");
      m_strPinLei = _T("");
      m_strMacType = _T("");
      m_strSizeList = _T("");       //���뱸ѡ
      m_strYarnList = _T("");       //ɴ�߱�ѡ
      m_strLingxingList = _T("");   //���ͱ�ѡ
      m_strNeedleTypeList = _T("");     //���ͱ�ѡ
      m_strDiBianList = _T("");     //�ױ߱�ѡ
      m_strXiuBianList = _T("");    //��߱�ѡ
      m_strMainColor1 = _T("");     //6����ɫ����
      m_strMatchColor1 = _T("");
      m_strMainColor2 = _T("");
      m_strMatchColor2 = _T("");
      m_strMainColor3 = _T("");
      m_strMatchColor3 = _T("");
      m_strMainColor4 = _T("");
      m_strMatchColor4 = _T("");
      m_strMainColor5 = _T("");
      m_strMatchColor5 = _T("");
      m_strMainColor6 = _T("");
      m_strMatchColor6 = _T("");
      m_cIsStyle_Warning = _T("1");

      m_dtExpireTime = _T("");    //��������
      m_cCreator = _T("");        //������
      m_cCreateType = _T("");     //��������
      m_cTheme = _T("");          //����
      m_cCusCode = _T("");       //�ͻ�
      m_cCusKuanhao = _T("");     //�ͻ����
      m_cProcessStatus = _T("");  //����״̬
      m_cEdition = _T("");        //�汾
      m_cDesigner = _T("");       //���ʦ
      m_dtMakingOrdTime = _T(""); //��������
      m_cMainMaterial = _T("");   //��ԭ��
      m_cVersionNum = _T("");     //�浥��
      m_cCraftsmen = _T("");      //����ʦ
      m_cPatternMaker = _T("");   //�ư�ʦ
      m_cSinglePerson = _T("");   //�Ƶ���
   };

   CString GetUpdateSql(BOOL bIgnoreNull = TRUE);     //���Ը��¿��ֶΣ�
  
   CString GetInsertSql();

   int         m_iClassID;          //ϵ��ID    add by lida 2018/05/11
   CString			m_strTypeName;			//��������(���������ֵ�)
   CString			m_strStyleNo;			//��ʽ��
   CString			m_strStyleName;		//��ʽ����
   CString         m_strYarnCate;       //ɴ�����
   CString			m_strIngredient;		//�ɷ�
   CString			m_strJinXian;			//����
   CString			m_strColorNo;			//ɫ��
   CString			m_strMatchColor;		//��ɫ
   CString			m_strStyleIntro;		//��ʽ˵��
   CString			m_strBarCode;			//��Ʒ����
   double			m_fLessWeight;			//����      
   CString			m_strIntro;				//˵��
   int		   m_nDefine;				//����   <---------------------------Ԥ����ɴ����
   CString			m_strDefine1;			//����1   <--------- ����Ϊ���ͻ�����, 2018-03-23
   CString			m_strDefine2;			//����2  <--------- ����Ϊ��������۸�, 2018-03-23
   CString			m_strDefine3;			//����3  <--------- ����Ϊ�����۸�, 2018-03-23
   CString			m_strDefine4;			//����4  <--------- ����Ϊ�����Ƽ۸�, 2018-03-23
   CString        m_cIsStyle_Warning; //�ÿ�ʽ�Ƿ�Ԥ�� liuhw 2019/1/4

   CString			m_strNeedleType;		//����
   CString			m_strFindKey;			//�ؼ���
   double				m_fWeight;				//����
   int				   m_bExec3D;				//�Ƿ����3Dģ��ı�ʶ
   int				m_dwAttriEx;         //��չ����
   CString			m_strLingXing;       //����
   CString			m_strDiBian;         //�ױ�
   CString			m_strXiuKou;         //���
   CString			m_strPinMing;        //Ʒ�� yangjr2018/5/11
   CString			m_strHouDaoInfo;     //�����Ϣ yangjr2018/5/11
   CString        m_strPinPai;         //Ʒ��
   CString        m_strKsYears;        //��ݼ���
   int            m_iFanLiFlag;        //����ͳ�Ʊ�� 0��ͳ�ƣ�1ͳ��
   CString        m_strGYPerson;       //����ʦ
   CString        m_strZBPerson;       //�ư�ʦ
   CString        m_strCeLiang;        //����
   CString        m_strPinLei;         //Ʒ�࣬�·�������
   CString        m_strMacType;        //����
   CString        m_strSizeList;       //���뱸ѡ
   CString        m_strYarnList;       //ɴ�߱�ѡ
   CString        m_strLingxingList;   //���ͱ�ѡ
   CString        m_strNeedleTypeList;     //���ͱ�ѡ
   CString        m_strDiBianList;     //�ױ߱�ѡ
   CString        m_strXiuBianList;    //��߱�ѡ

   CString        m_strMainColor1;     //6����ɫ����
   CString        m_strMatchColor1;
   CString        m_strMainColor2;
   CString        m_strMatchColor2;
   CString        m_strMainColor3;
   CString        m_strMatchColor3;
   CString        m_strMainColor4;
   CString        m_strMatchColor4;
   CString        m_strMainColor5;
   CString        m_strMatchColor5;
   CString        m_strMainColor6;
   CString        m_strMatchColor6;

   CString        m_dtExpireTime;    //��������
   CString        m_cCreator;        //������
   CString        m_cCreateType;     //��������
   CString        m_cTheme;          //����
   CString        m_cCusCode;       //�ͻ�
   CString        m_cCusKuanhao;     //�ͻ����
   CString        m_cProcessStatus;  //����״̬
   CString        m_cEdition;        //�汾
   CString        m_cDesigner;       //���ʦ
   CString        m_dtMakingOrdTime; //��������
   CString        m_cMainMaterial;   //��ԭ��
   CString        m_cVersionNum;     //�浥��
   CString        m_cCraftsmen;      //����ʦ
   CString        m_cPatternMaker;   //�ư�ʦ
   CString        m_cSinglePerson;   //�Ƶ���
}s_my_ks_info;