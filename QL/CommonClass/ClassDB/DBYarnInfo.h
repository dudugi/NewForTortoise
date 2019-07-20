//ɴ��������ɴ�߱�

#pragma once
#ifndef YARN_IMAGE
#define YARN_IMAGE	1
#endif

#include <map>
#include "DataMid.h"
#include "DBKeyDef.h"
#define ALL_COLOR_GROUP _T("ȫ��")
#define NO_COLOR_GROUP _T("��ɫ��")

/*************************************************
// <�ļ�>: DBYarnInfo.h
// <˵��>: ɴ����Ϣ�Լ�ɴ��������
// <����>: wangzl
// <����>: 2019/02/22
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 

class CADOConn;
class CDBYarnInfoData  : public CDataMid
{
	DECLARE_SERIAL( CDBYarnInfoData)//���л������л�����Ҫ��ӵ�����
public:
	typedef enum En_YarnState
	{
		State_InValid = 0,//��Чɴ��
		State_Vilid ,
	};

	int				   m_nID;			 //����ID
	COleDateTime	   m_oleData;		 //��������
	CString			   m_strCate;		 //���   ->���������ֵ�
	CString			   m_strYarnNo;		 //ɴ�ߺ�
	CString			   m_strYarnName;	 //ɴ������
	CString			   m_strIngredient;	 //ɴ�߳ɷ�
	CString			   m_strThickNess;	 //֧��
	CString			   m_strRemark;		 //��ע
	double			   m_fWarning;		 //��������
	COLORREF		   m_RGBValue;		 //��ɫֵ(DWORD)���ݿ�洢Ϊbigintȡ��4���ֽڵ���ֵ����
	CString			   m_strRGBName;	 //��ɫ����
	int				   m_nKind;			 //����(0==����/1==����)
	int				   m_nState;		 //1==��  0==�¼ܵı�ʶ
   double			      m_fKucunYujing;		 //���Ԥ������
   CString           m_strColorGroup;//ɫ�� huangym   2018/12/19
#if YARN_IMAGE
	Gdiplus::Image*				m_pYarnColorCard;//ɫ��
#endif

	CString			   m_strCurResv;	 //��ǰ��� ɴ�߿��Ԥ�������õ��������ݿ��޹�����add by lida 2017/06/15
   bool              m_bHaveDownPic;//ͼƬ�Ƿ������� yangjr 2017/1/30

public:
	CDBYarnInfoData();
	~CDBYarnInfoData();
	void ResetData();
	void Copy(CDBYarnInfoData *pData);
	void Serialize(CArchive& ar);
	BOOL GetAllDBInfo(CADOConn *pADOConn,bool bNeedColorCard=false);		//��ȡɴ�ߡ���������Ϣ

	BOOL DelAllDBInfoByID(CADOConn *pADOConn);		//����IDɾ������������¼
   BOOL DelAllDBInfoByYarnNoAndCate(CADOConn *pADOConn);		//����ɫ�Ÿ����ɾ������������¼

	BOOL UpdateAllDBInfoByID(CADOConn *pADOConn);	//����ID���¡�������
   BOOL UpdateAllDBInfoByYarnNoAndCate(CADOConn *pADOConn);	//����ɫ�Ÿ������¡���������¼
	BOOL InsertAllDBInfoByYarnID(CADOConn *pADOConn);	//����ɴ�ߺŲ��롾��������¼
   BOOL UpdateStateByYarnNoAndCate(CADOConn *pADOConn,CString strSehao,CString strYarnCate,int iState);	//����ɴ�ߺŸ����ϼ�״̬��¼ yangjr 2017-12-11
   BOOL GetStateByYarnNoAndCate(CADOConn *pADOConn,CString strSehao,CString strYarnCate,int &iState);	//����ɴ�ߺŻ�ȡ�ϼ�״̬��¼ yangjr 2017-12-11
   BOOL GetPictureDataByYarnNoAndCate(CADOConn *pADOConn,CString strSehao,CString strYarnCate, Gdiplus::Image *&pYarnColorCard);	//����ɴ�ߺŻ�ȡɫ��ͼƬ yangjr 2018/1/30
   //����ɴ�ߺŸ�������ֵ yangjr 2018/1/9
   BOOL UpdateWarnValueByYarnNoAndCate(CADOConn *pADOConn,CString strSehao,CString strYarnCate,double fWarnValue);
   //����ɴ�ߺŸ��¿��Ԥ��ֵ yangjr 2018/4/24
   BOOL UpdateKucunYujingByYarnNoAndCate(CADOConn *pADOConn,CString strSehao,CString strYarnCate,double fKucunYujing);
   //�Ƚ��޸�ǰ�����ݣ����޸��˵����ݱ�������
   CString SetDBEquals_Log(CDBYarnInfoData &pOldData);
   //BOOL GetYarnCateBySehao(CADOConn *pADOConn,CString strSehao,CString &strYarnCate);
	void Trim();
	static CDBYarnInfoData * Instance();//��ȡ��ָ�룩ʵ��

#ifdef YARN_IMAGE
private:
	inline void ClearColorImage();
#endif // YARN_IMAGE
private:
	static std::shared_ptr<CDBYarnInfoData> sm_inst;
};

class CDBYarnInfoList : public CDataListMid
{
	DECLARE_SERIAL(CDBYarnInfoList)
public:
	CDBYarnInfoList();
	~CDBYarnInfoList();
	CDBYarnInfoData*  GetItem(int nIndex);
	void    AddItem(CDBYarnInfoData* pItem);
	void    DeleteItem(int nIndex);
   BOOL    DeleteItemByID(int ID);
	CDBYarnInfoData* GetItemByID(int nID);
   //��ȡ��Ӧɫ�����е�ɴ������ ͬɫ�ŵ�ʱ�򷵻ض��� yangjr 2019/03/01
   std::vector<CDBYarnInfoData*> GetItemsByYarnNo(CString strYarnNo);
   CDBYarnInfoData* GetItemByYarnNo_NoCase(CString strYarnNo); //���Դ�Сд
   //��ȡ��Ӧɫ��(�����ִ�Сд)���е�ɴ������ ͬɫ�ŵ�ʱ�򷵻ض��� yangjr 2019/03/01
   std::vector<CDBYarnInfoData*> GetItemsByYarnNo_NoCase(CString strYarnNo);
	int GetIndexByID(int nID);
   CDBYarnInfoData* GetItemByYarnNoAndCate_NoCase(CString strYarnNo,CString strYarnCate); //���Դ�Сд
   void GetListFromDB(CADOConn *pADOConn, bool bNeedColorCard = false);//�����ݿ��ȡ����
	static CDBYarnInfoList * Instance();//��ȡ��ָ�룩ʵ��

   void SetAllItemDownPic(bool bDownPic);//���������������ͼƬ��־ yangjr 2018/1/30  
   void SetDownPicFlagByYarnNoAndCate(CString strYarnNo,CString strYarnCate,bool bDownPic); //���ö�Ӧɫ�ŵ�����ͼƬ��־ yangjr 2018/1/30
   void SetPicDataByYarnNoAndCate(CString strYarnNo,CString strYarnCate, Gdiplus::Image* pYarnColorCard); //���ö�Ӧɫ�ŵ�ͼƬ���� yangjr 2018/1/30

   void GetYarn_Cate_CF_Info(CADOConn *pADOConn,CString strYarnNo,CString& strYarnCate,CString& strCF);//��ȡɴ����𡢳ɷ���Ϣ

   void GetYarnCateCF(CADOConn *pADOConn,map<CString,CString>& mapData);

   BOOL GetYarnInfoBySehao(__in CADOConn *pADOConn,__in CString strSehao,__out CDBYarnInfoData* pObj);

   BOOL GetYarnColor(__in CADOConn *pADOConn,__in CString strSehao,__in CString strYarnCate,__out CString& strColor); //��ȡɫ����ɫ by lida 2018/07/26

   static BOOL CheckSeHaoIsExists(__in CADOConn *pADOConn,__in CString strSehao);    //���ɫ���Ƿ����
	//2017/6/9 8:57 wzl ���ɱ���������
#ifdef USING_GRIDCTRL_MARK
	MAP_GridCtrl_AllData CreatrGridData();
   MAP_GridCtrl_AllData CreatrGridData_Sehao();

	//����һ���յ�������		by WangZY 2017/08/24
	BOOL GetEmptyRowData(__out MAP_GridCtrl_RowData &mapEmptyRowData);

	//�����ύ�����޸�		by WangZY 2017/08/24
	BOOL SaveMultiModifyData(__in CADOConn *pADOConn, __in MAP_GridCtrl_AllData &mapAddData,
		__in MAP_GridCtrl_AllData &mapModifyData, __in MAP_GridCtrl_AllData &mapDeleteData,
		__in CString strMaker);

	//ɴ��Ԥ�����ѣ���ȡ�¼ܡ�����ʾ��ɫ��
	BOOL GetRssWarningSehao(__in CADOConn* pADOConn,__in CString strData,__out vector<CString>& vecSehao,__out CString& strCurDate);	
	
	//��Ʒ����Ϣ��ʼ��ָ��id��ɫ�ŵĳɷ���Ϣ		by WangZY 2018/05/07
	static BOOL InitChenfenInfo(__in CADOConn* pADOConn,__in CString strIDFilter);
#endif // USING_GRIDCTRL_MARK
	//���ɱ��������� end wzl

private:
	static std::shared_ptr<CDBYarnInfoList> sm_inst;
};


typedef struct my_sehao_info
{
   my_sehao_info()
   {
      //m_nID = 0;
      //m_oleData = COleDateTime::GetCurrentTime();
      m_strCate = _T("");
      m_strYarnNo = _T("");
      m_strYarnName = _T("");
      m_strIngredient = _T("");
      m_strThickNess = _T("");
      m_strRemark = _T("");
      m_fWarning = -1;
      m_RGBValue = -1;
      m_strRGBName = _T("");
      m_nKind = -1;
      m_nState = -1;
      m_fKucunYujing = -1;		 //���Ԥ��ֵ
   };

   CString GetUpdateSql(BOOL bIgnoreNull = TRUE)     //���Ը��¿��ֶΣ�
   {
      if (m_strYarnNo.IsEmpty())
      {
         return _T("");
      }
      CString strSql = _T("");
      CString strText;

      //if (!m_strCate.IsEmpty() || !bIgnoreNull)
      //{
      //   strText.Format(_T("%s = '%s',"),DBColor_key_Cate,m_strCate);
      //   strSql += strText;
      //}

      if (!m_strYarnName.IsEmpty() || !bIgnoreNull)
      {
         strText.Format(_T("%s = '%s',"),DBColor_key_YarnName,m_strYarnName);
         strSql += strText;
      }

      if (!m_strIngredient.IsEmpty() || !bIgnoreNull)
      {
         strText.Format(_T("%s = '%s',"),DBColor_key_Ingredient,m_strIngredient);
         strSql += strText;
      }

      if (!m_strThickNess.IsEmpty() || !bIgnoreNull)
      {
         strText.Format(_T("%s = '%s',"),DBColor_key_ThickNess,m_strThickNess);
         strSql += strText;
      }

      if (!m_strRemark.IsEmpty() || !bIgnoreNull)
      {
         strText.Format(_T("%s = '%s',"),DBColor_key_Remark,m_strRemark);
         strSql += strText;
      }

      if (m_fWarning >0 || !bIgnoreNull)
      {
         strText.Format(_T("%s = '%lf',"),DBColor_key_Warning,m_fWarning);
         strSql += strText;
      }

      if (m_RGBValue!=-1 || !bIgnoreNull)
      {
         strText.Format(_T("%s = '%d',"),DBColor_key_RGBValue,m_RGBValue);
         strSql += strText;
      }

      if (!m_strRGBName.IsEmpty() || !bIgnoreNull)
      {
         strText.Format(_T("%s = '%s',"),DBColor_key_RGBName,m_strRGBName);
         strSql += strText;
      }

      if (m_nKind!=-1 || !bIgnoreNull)
      {
         strText.Format(_T("%s = '%d',"),DBColor_key_Kind,m_nKind);
         strSql += strText;
      }

      if (m_nState!=-1 || !bIgnoreNull)
      {
         strText.Format(_T("%s = '%d',"),DBColor_key_State,m_nState);
         strSql += strText;
      }

      if (m_fKucunYujing>0 || !bIgnoreNull)
      {
         strText.Format(_T("%s = '%lf',"),DBColor_key_fKucunYujing,m_fKucunYujing);
         strSql += strText;
      }

      //����ʱ��
      CString strGetDateStr = DBS_GETDATESTR;
      strText.Format(_T("%s = %s,"),DBColor_key_Date,strGetDateStr);
      strSql += strText;

      if (!strSql.IsEmpty())
      {
         strSql = strSql.Left(strSql.GetLength() - 1);// ȡ�����һ��,
         CString strRetSql;  
         strRetSql.Format(_T("update %s set %s where %s = '%s' and %s = '%s'"),DB_TABLE_YARN,strSql,DBColor_key_YarnNo,m_strYarnNo,DBColor_key_Cate,m_strCate);
         return strRetSql;
      }
      return _T("");
   };

   CString GetInsertSql()
   {
      CString strFormat;
      strFormat.Format(_T("%s,%s,%s,%s,%s, %s,%s,%s,%s,%s, %s,%s,%s"),
         DBColor_key_Date,DBColor_key_Cate,DBColor_key_YarnNo,DBColor_key_YarnName,DBColor_key_Ingredient,	
         DBColor_key_ThickNess,DBColor_key_Remark,DBColor_key_Warning,DBColor_key_RGBValue,DBColor_key_RGBName,
         DBColor_key_Kind,DBColor_key_State,DBColor_key_fKucunYujing              
         );
      CString strFormat1;
      if (m_fWarning < 0) m_fWarning = 0;
      if (m_RGBValue < 0) m_RGBValue = 0;
      if (m_nKind < 0) m_nKind = 0;
      if (m_nState < 0) m_nState = 0;
      if (m_fKucunYujing < 0) m_fKucunYujing = 0;

      strFormat1.Format(_T("%s,'%s','%s','%s','%s', '%s','%s',%f,%d,'%s', %d,%d,%f"),
         DBS_GETDATESTR,m_strCate,m_strYarnNo,m_strYarnName,m_strIngredient,
         m_strThickNess,m_strRemark,m_fWarning,m_RGBValue,m_strRGBName,
         m_nKind,m_nState,m_fKucunYujing);

      CString strSql;
      strSql.Format(_T("insert into %s (%s) values (%s);"),DB_TABLE_YARN,strFormat,strFormat1);
      return strSql;
   };

   //int				   m_nID;			 //����ID
   //COleDateTime	   m_oleData;		 //��������
   CString			   m_strCate;		 //���   ->���������ֵ�
   CString			   m_strYarnNo;		 //ɴ�ߺ�
   CString			   m_strYarnName;	 //ɴ������
   CString			   m_strIngredient;	 //ɴ�߳ɷ�
   CString			   m_strThickNess;	 //֧��
   CString			   m_strRemark;		 //��ע
   double			      m_fWarning;		 //��������
   COLORREF		      m_RGBValue;		 //��ɫֵ(DWORD)���ݿ�洢Ϊbigintȡ��4���ֽڵ���ֵ����
   CString			   m_strRGBName;	 //��ɫ����
   int				      m_nKind;			 //����(0==����/1==����)
   int				      m_nState;		 //1==��  0==�¼ܵı�ʶ
   double			      m_fKucunYujing;		 //���Ԥ������
}s_my_sehao_info;