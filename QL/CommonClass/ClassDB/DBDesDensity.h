#pragma once

#ifndef Des_IMAGE
#define Des_IMAGE	1
#endif

/*************************************************
// <�ļ�>: DBDesDensity.h
// <˵��>: ��������ܶ���Ϣ�� ��Ҫ�����빤�նԽ�
// <����>: wangzl
// <����>: 2019/01/30 10:32:14
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 

//2017/11/28 zhangt Create
#include "DataMid.h"

#if Des_IMAGE
#include "Dib.h"
#include "ViewCtrl.h"
#endif // Des_IMAGE

class CADOConn;

#define DBDesFaceCode_key_ID			   _T("ID")		      //����ID
#define DBDesFaceCode_key_NAME			_T("cName")		   //���� eg:������
#define DBDesFaceCode_key_LENOLD		   _T("fOldLen")	   //
#define DBDesFaceCode_key_TYPE			_T("cType")		   //���� eg:֧��
#define DBDesFaceCode_key_LEN			   _T("fLen")		   //����
#define DBDesFaceCode_key_UNIT			_T("cUnit")		   //��λ eg:����
#define DBDesFaceCode_key_IDDENSITY		_T("IDDensity")	//�ܶȹ����ֶ�����ID


//������
class CDBFaceCode : public CDataMid
{
	DECLARE_SERIAL( CDBFaceCode)           //���л������л�����Ҫ��ӵ�����

public:
	CDBFaceCode();
	~CDBFaceCode();
	void ResetData();

	BOOL GetAllDBInfo(CADOConn *pADOConn);	//��ȡ����������Ϣ
	void Copy(CDBFaceCode *pData);

                                          //��ȡ�������ĸ�ʽ��
	CString GetSQLFormat();
                                          //��ȡ�������ݵĸ�ʽ��
   CString GetValueFormat(
      const CString & strName,
      const CString & strOldLen,
      const CString & strType,
      const CString & strLen,
      const CString & strUnit,
      const __int64 nIDDensity
      );

	static CDBFaceCode * Instance();		   //��ȡ��ָ�룩ʵ��

private:
	static std::shared_ptr<CDBFaceCode> sm_inst;

public:
	int		m_nID		;                    //����ID
	CString m_strName	;                    //���� eg:������
	CString	m_sOldLen;                    //
	CString m_strType	;                    //���� eg:֧��
	CString	m_sLen	;                    //����
	CString m_strUnit	;                    //��λ eg:����

	__int64 m_nIDDensity;		            //�ܶȹ����ֶ�����ID
};

class CDBFaceCodeList : public CDataListMid
{
	DECLARE_SERIAL(CDBFaceCodeList)
public:
	CDBFaceCodeList();
	~CDBFaceCodeList();
	CDBFaceCode*  GetItem(int nIndex);
	void    AddItem(CDBFaceCode* pItem);
	void    DeleteItem(int nIndex);

	static CDBFaceCodeList * Instance();		//��ȡ��ָ�룩ʵ��

private:
	static std::shared_ptr<CDBFaceCodeList> sm_inst;
};

//����һ�����������������
class CDBDensityFaceCodeData : public CDataMid
{
	DECLARE_SERIAL(CDBDensityFaceCodeData)
public:
	CDBDensityFaceCodeData();
	virtual ~CDBDensityFaceCodeData();
public:
	CDBFaceCodeList m_lstFaceCode;
	__int64 m_nIDDensity;		//�ܶȹ����ֶ�����ID
public:
	void Copy(CDBDensityFaceCodeData * pData);
	void AddItem(CDBFaceCode * pData);
};

class CDBDensityFaceCodeList : public CDataListMid
{
	DECLARE_SERIAL(CDBDensityFaceCodeList)
public:
	CDBDensityFaceCodeList();
	virtual ~CDBDensityFaceCodeList();
public:
	CDBDensityFaceCodeData*  GetItem(int nIndex);
	CDBDensityFaceCodeData*  GetItemByIDDensity(int nID);
	void    AddItem(CDBDensityFaceCodeData* pItem);
	void    DeleteItem(int nIndex);
};


//�ܶȱ�
#define DB_TABLE_DESDENSITY		      _T("DesDensity")
                                       
#define DBDesDensity_key_ID			   _T("ID")		                       //����ID
#define DBDesDensity_key_Name	    	   _T("cName")		                    //����
#define DBDesDensity_key_HorDesSrc	   _T("fHorDesSrc")                   //����
#define DBDesDensity_key_VerDesSrc	   _T("fVerDesSrc")                   //ֱ��
#define DBDesDensity_key_HorDesNew	   _T("fHorDesNew")                   //����
#define DBDesDensity_key_VerDesNew	   _T("fVerDesNew")                   //ֱ��
#define DBDesDensity_key_Structure	   _T("cStructure")                   //�����ṹ
#define DBDesDensity_key_Material	   _T("cMaterial")	                 //ë��
#define DBDesDensity_key_Pull		      _T("fPull")		                    //����
#define DBDesDensity_key_PullUnit	   _T("cPullUnit")	                 //��λ
#define DBDesDensity_key_PullType	   _T("iPullType")	                 //eg:ȫ���� or ������
#define DBDesDensity_key_Needle		   _T("cNeedle")	                    //����
                                       
                                                                          //СƬ����                             
#define DBDesDensity_key_PieceUnit	   _T("fPieceUnit")	                 //100��
#define DBDesDensity_key_PieceTurns	   _T("fPieceTurns")	                 //100ת
#define DBDesDensity_key_PieceNeedle   _T("fPieceNeedle")	              //100��

                                                                          //��ͷ��ת
#define DBDesDensity_key_StartTurns		_T("fStartTurns")

                                                                          //��������
#define DBDesDensity_key_RomanType		_T("cRomanType")

                                                                          //��˿ת��
#define DBDesDensity_key_Wire		      _T("cWire")	                       //��˿
#define DBDesDensity_key_WireTurns	   _T("fWireTurns")	                 //ת
#define DBDesDensity_key_WireType	   _T("iWireType")		              //�Ƿ�ȫ��˿

                                                                          //����
#define DBDesDensity_key_ShowPZ        _T("iShowPZ")                      //�Ƿ���ʾ����
#define DBDesDensity_key_PZName		   _T("cPZName")                      //��������
#define DBDesDensity_key_PinBottom	   _T("cPinBottom")	                 //��
#define DBDesDensity_key_PinFace	      _T("cPinFace")		                 //��
#define DBDesDensity_key_PinType     	_T("iPinType")		                 //��������

#define DBDesDensity_key_Type		      _T("cType")			                 //�ܶ��Զ�������
#define DBDesDensity_key_BaseType	   _T("cBaseType")		              //�����ܶ� or �����ܶ�

#define DBDesDensity_key_cSavedUserID  _T("cSavedUserID")                 //������
#define DBDesDensity_key_cSaveTime     _T("cSaveTime")                    //����ʱ��
#define DBDesDensity_key_cRemark       _T("cRemark")                      //�ܶ�˵��
#define DBDesDensity_key_cOrderNo      _T("cOrderNo")                     //������ ���� 

#define DBDesDensity_key_cPieceName    _T("cPieceName")                   //��Ƭ����
#define DBDesDensity_key_cMatName      _T("cMatName")                     //�������� 

#define DBDesDensity_key_cFlowerPatternPic    _T("cFlowerPatternPic")     //����ͼƬ
//�������ݿ�
#define DBDesDensity_key_cSavedUserName _T("cSavedUserName")              //����������

class CDBDensity : public CDataMid
{
	DECLARE_SERIAL(CDBDensity)//���л������л�����Ҫ��ӵ�����

public:
	CDBDensity();
	~CDBDensity();
	void ResetData();
   BOOL UpdateDBInfo(CADOConn * pADOConn);
	BOOL GetAllDBInfo(CADOConn *pADOConn);		//��ȡ����������Ϣ
	void Copy(CDBDensity *pData);

	//��ȡ�����SQL���
	CString GetInsertSQL();
	static CDBDensity * Instance();//��ȡ��ָ�룩ʵ��
   void SetFaceData(CDBFaceCode* data);
   BOOL UpdateAllDBInfoByID(CADOConn * pADOConn);
   BOOL InsertAllDBInfoByID(CADOConn * pADOConn);
#if Des_IMAGE
private:
   inline void ClearColorImage();
#endif // Des_IMAGE
private:
	static std::shared_ptr<CDBDensity> sm_inst;


public:
   CDBDensityFaceCodeData m_faceData         ;
	__int64		           m_nID              ;//����ID
	CString                m_strName          ;//����
	double	              m_fHorDesSrc       ;//����
   double	              m_fVerDesSrc       ;//ֱ��
   double	              m_fHorDesNew       ;//����
   double	              m_fVerDesNew       ;//ֱ��
	CString                m_strStructure     ;//�����ṹ
	CString                m_strMaterial      ;//ë��

   double	              m_fPull            ;//����
	CString                m_strPullUnit      ;//��λ
	int		              m_nPullType        ;//eg:ȫ���� or ������
	CString                m_strNeedle        ;//����

	//СƬ����
	double                 m_fPieceUnit		   ;//100��
	double                 m_fPieceTurns		;//100ת
	double                 m_fPieceNeedle	   ;//100��

	//��ͷ��ת
   double                 m_fStartTurns		;

	//��������
	CString                m_strRomanType	   ;

	//��˿ת��
	CString                m_strWire		      ;//��˿
   double	              m_fWireTurns	      ;//ת
	int		              m_nWireType		   ;//�Ƿ�ȫ��˿


	//����
	BOOL	                 m_bShowPZ		      ;//�Ƿ���ʾ����
	CString                m_strPZName		   ;//��������
	CString                m_strPinBottom	   ;//��
	CString                m_strPinFace	      ;//��
	int		              m_nPinType		   ;//��������

	CString                m_strType		      ;//�ܶ��Զ�������
	CString                m_strBaseType	   ;//�����ܶ� or �����ܶ�

   CString                m_strSavedUserID   ;//�û�ID
   CString                m_strSaveTime      ;//����ʱ��
   CString                m_strRemark        ;//�ܶ�˵��
   CString                m_strOrderNo       ;//������
   CString                m_strPieceName     ;//��Ƭ����
   CString                m_strMatName       ;//��������


#if Des_IMAGE
   Gdiplus::Image*		  m_pFlowerPatternPic;//����ͼ
#endif

   //�������ݿ�
   CString m_strSavedUserName;//�û���
};

class CDBDensityList : public CDataListMid
{
	DECLARE_SERIAL(CDBDensityList)
public:
	CDBDensityList();
	~CDBDensityList();
	CDBDensity*  GetItem(int nIndex);
   CDBDensity*  GetItemByName(const CString & strName);
	void    AddItem(CDBDensity* pItem);
	void    DeleteItem(int nIndex);
   void    MatchData(CDBFaceCode* data);
   BOOL    DeleteUserByUserID(CADOConn * pADOConn, vector<CString> vecUserID);

   static CDBDensityList * Instance();		//��ȡ��ָ�룩ʵ��
   
#ifdef USING_GRIDCTRL_MARK
   //���ɱ������
   MAP_GridCtrl_AllData CreateGridData(const CString & strUserDuty = _T(""));
#endif // USING_GRIDCTRL_MARK

private:
   CDBDensityFaceCodeData m_FaceData;
	static std::shared_ptr<CDBDensityList> sm_inst;
};