#pragma once

#include "CDataTableDlgDefine.h"
#include "CDataTableFieldDefine.h"

class TiXmlElement;
//�������
//class CDlgTableStyleGlobalSet;
//class DBTableStyleGlobalSetInfoList;

class CGridCtrlTableAttributeOp
{
   //friend CDlgTableStyleGlobalSet;
   //friend DBTableStyleGlobalSetInfoList;
public:
	CGridCtrlTableAttributeOp(void);
	~CGridCtrlTableAttributeOp(void);

private:
   typedef void (CGridCtrlTableAttributeOp::*funcCreateAttri)(S_GridCtrl_TableAttri &tableAttri);
   map<CString, funcCreateAttri> m_mapFunc;//�ַ��������ĺ�����

   typedef void (CGridCtrlTableAttributeOp::*funcCreateAttri2Param)(S_GridCtrl_TableAttri &tableAttri,CString strFileName);
   map<CString, funcCreateAttri2Param> m_mapFunc2Param;//�ַ��������ĺ�����
   //�����hashmap

   static std::shared_ptr<CGridCtrlTableAttributeOp> sm_inst;

public:
	BOOL ReadTableAttri(CString fileName,S_GridCtrl_TableAttri &tableAttri,BOOL bNoXml=FALSE);//bNoXml�Ƿ����XML�ļ�

	BOOL WriteTableAttri(CString fileName,const S_GridCtrl_TableAttri &tableAttri);
	BOOL WriteTableAttriAsDefault(CString fileName,const S_GridCtrl_TableAttri &tableAttri);//��������ʽ��ϵͳĿ¼�� yangjr2017-6-13 
	//wangzl ������������һ���յı���������б� 2017/6/17 
	void CreateEmptyFieldAttri(S_GridCtrl_TableAttri &tableAttri,CStringList &strlFieldName);

	//��ʼ��ϵͳĿ¼�µı����ʽ yangjr 2018-1-15
	BOOL InitDefaultTableAttri(CString fileName);

	//��ʼ���û�Ŀ¼�µı����ʽ yangjr 2018-1-15
	BOOL InitUserTableAttri(CString fileName,S_GridCtrl_TableAttri &tableAttri);

   //************************************
   // Method:    ���±����ʽ
   // Author:    wuZhiHua
   // Date : 	  2018/04/02
   // Access:    private 
   // Returns:   void
   // Parameter: TiXmlElement * pElement
   //************************************
   BOOL UpdateGridStyleAttriInfo(CString fileName , S_GridCtrl_TableAttri &tableAttri);

   static void LinkIntValueToElement(int iValue,TiXmlElement *pElement);
   static void LinkCStringValueToElement(CString strValue,TiXmlElement *pElement);
   BOOL WriteTableAttriToXml(CString fullName,const S_GridCtrl_TableAttri &tableAttri);
   BOOL ReadTableAttriFromXml(CString fullName,S_GridCtrl_TableAttri &tableAttri);

   static CGridCtrlTableAttributeOp * Instance();

   //************************************
   // Method:    ǿ�ƶ�ȡ�������ı����ʽ�����µ�����
   // Author:    yangjr
   // Date : 	  2018/05/29
   // Access:    public 
   // Returns:   BOOL
   // Parameter: TiXmlElement * pElement
   //************************************
   //BOOL GetServerStyleAndUpdateLocal(CString fileName , S_GridCtrl_tableAttri &tableAttri);

private:
   BOOL ReadDefaultTableAttri(CString fileName,S_GridCtrl_TableAttri &tableAttri);//����ɴ�����������Ĭ������

   void CreateTABLESTYLE(S_GridCtrl_TableAttri &tableAttri);
	void Create_StaffMgn(S_GridCtrl_TableAttri &tableAttri);					//Ա������	
	void Create_CusMgn(S_GridCtrl_TableAttri &tableAttri);					//�ͻ�����	
   void Create_LogInfo(S_GridCtrl_TableAttri &tableAttri);					//��־��Ϣ

   void Create_CusMgnOpRecords(S_GridCtrl_TableAttri &tableAttri);

	void InsertFeildID(S_GridCtrl_TableAttri &tableAttri, short iColIndex_In,
		CString strColID_In, CString strColShowName_In = _T(""),CString strColDestribution = _T(""),
		CString strTableID_In = _T(""),bool isShow_In = true, bool isEdit_In = true, short iColWidth_In = 75,
		bool isEnableFilter_In = true, BYTE iLock_In = 0, ENUM_COLSUMTYPE enColSumType_In = CB_enum_ColSumType_None,
		BYTE iColFont_In = CB_GRIDCTRL_DEFAULT_FONT, bool IsFontWeight_In = false,
		ENUM_COLSERCHTYPE enSerchType_In = CB_enum_ColSerchType_Contain, CString strColFormat_In=_T(""));//����һ���ֶε������ʽ�� yangjr2017-6-13

	void InsertOrderViewInfo(S_GridCtrl_TableAttri &tableAttri,int &colIndex);

	CString GetUserTableConfigXmlPath();//�û�·��
	CString GetSysTableConfigXmlPath();//ϵͳ·��

	void SortFieldToMap(MAP_GridCtrl_FieldAtrri &,S_GridCtrl_TableAttri & tableAttri,int & nBeginIndex);  

   //2017/12/12 zhangt �ϲ�xml�ļ��ʹ����е�������ӵ��ֶ� ����ɾ��xml�ļ�
	BOOL CombineDefaultTableAttri(CString DefaultFilelName,S_GridCtrl_TableAttri &tableAttri); 

};

