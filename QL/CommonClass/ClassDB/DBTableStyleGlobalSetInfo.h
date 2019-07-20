/*************************************************
// <�ļ�>: DBTableStyleGlobalSetInfo.h
// <˵��>: ���ݿ������-�����ʽȫ�����ñ�
// <����>: yangjr
// <����>: 2019/02/20 16:35:46
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
#pragma once

#include <vector>
#include "DataMid.h"

class CADOConn;
class DBTableStyleAttrSetLst;

class DBTableStyleGlobalSetInfo :public CDataMid
{
	DECLARE_SERIAL( DBTableStyleGlobalSetInfo)//���л������л�����Ҫ��ӵ�����
public:
	int				m_nID;			   //����ID
   CString        m_cXmlFileName;   //xml�ļ���
   CString        m_cXmlDesc;       //xml˵��
   CString        m_cInitSettingXml;//��������XML����
   CString        m_cRealTimeXml;   //ʵʱ��xml����
   CString        m_cUpdateTime;    //ʵʱ����ʱ��

   void ResetData();
   
   void Copy(DBTableStyleGlobalSetInfo *pData);

   BOOL GetAllDBInfo(CADOConn *pADOConn);

   BOOL InsertAllDBInfo( CADOConn *pADOConn );

   CString GetInsertSQL();

   BOOL DeleteInfoByID(CADOConn *pADOConn);
      
   BOOL UpdateInfoByID(CADOConn *pADOConn);

public:
	DBTableStyleGlobalSetInfo();
   ~DBTableStyleGlobalSetInfo();
};

class DBTableStyleGlobalSetInfoList  : public CDataListMid
{
	DECLARE_SERIAL(DBTableStyleGlobalSetInfoList)
public:
	DBTableStyleGlobalSetInfoList();
	~DBTableStyleGlobalSetInfoList();
	DBTableStyleGlobalSetInfo* GetItem(int nIndex);			//����������ȡItem
	void AddItem(DBTableStyleGlobalSetInfo* pItem);			//���Item
	void DeleteItem(int nIndex);					            //ɾ���̶�����Item
	static DBTableStyleGlobalSetInfoList * Instance();		//��ȡ��ָ�룩ʵ��


   //************************************
   // Method:    �ñ������� ����ʵʱXML����  
   // Author:    wuZhiHua
   // Date : 	  2018/04/17
   // Access:    public 
   // Returns:   BOOL
   // Parameter: CString fileName
   //************************************
   BOOL UpdateCurrentTimeXmlDataFromLocalData(CADOConn *pADOConn,CString fileName , CString strTime);


   //************************************
   // Method:    �ó�ʼ������ ����ʵʱXML���� 
   // Author:    wuZhiHua
   // Date : 	  2018/04/17
   // Access:    public 
   // Returns:   BOOL
   // Parameter: CString fileName
   //************************************
   BOOL UpdateCurrentTimeXmlDataFromInitData(CADOConn *pADOConn,CString fileName, CString strTime , CString &updateXmlstr);


   //************************************
   // Method:    ���³������� �Ḳ��ʵʱ����
   // Author:    wuZhiHua
   // Date : 	  2018/04/17
   // Access:    public 
   // Returns:   BOOL
   // Parameter: CString fileName
   //************************************
   BOOL UpdateInitSetXmlData(CADOConn *pADOConn,CString fileName, CString strTime);

   
   //************************************
   // Method:    �ϲ���������  ��ʵʱXML����  �ָ�������������
   // Author:    wuZhiHua
   // Date : 	  2018/04/18
   // Access:    public 
   // Returns:   BOOL
   // Parameter: CADOConn * pADOConn
   // Parameter: CString fileName
   // Parameter: CString strTime
   //************************************
   BOOL CombineDefaultTableAtrri(CADOConn *pADOConn,CString fileName, CString strTime);


   ////************************************
   //// Method:    ����������  ������������
   //// Author:    wuZhiHua
   //// Date : 	  2018/04/18
   //// Access:    public 
   //// Returns:   BOOL
   //// Parameter: CADOConn * pADOConn
   //// Parameter: CString strTime
   ////************************************
   //BOOL UpdateColSetAndStyleAttrSet(CADOConn *pADOConn , CString strTime);



   ////************************************
   //// Method:    ����������  ������������ ��������
   //// Author:    wuZhiHua
   //// Date : 	  2018/04/18
   //// Access:    public 
   //// Returns:   void
   //// Parameter: S_GridCtrl_TableAtrri & tableAtrri
   ////************************************
   //void UpdateColSetAndStyleAttrSet(CADOConn *pADOConn, DBTableStyleAttrSetLst *pStyleAttrSet , S_GridCtrl_TableAtrri& tableAtrri);

   //************************************
   // Method:    ���ݿ�XML�ַ���ת �����ʽ���Խṹ��
   // Author:    wuZhiHua
   // Date : 	  2018/04/17
   // Access:    private 
   // Returns:   S_GridCtrl_TableAtrri
   // Parameter: CString attriStr
   //************************************
   S_GridCtrl_TableAtrri AttriStrToAttriStruct(CString attriStr);


   //************************************
   // Method:    �����ʽ���Խṹ�� ת���ݿ�XML�ַ���
   // Author:    wuZhiHua
   // Date : 	  2018/04/18
   // Access:    public 
   // Returns:   CString
   // Parameter: S_GridCtrl_TableAtrri attri
   //************************************
   CString AttriStructToAttriStr(S_GridCtrl_TableAtrri tableAtrri);

   //************************************
   // Method:    �����ļ�����ȡ ���ݿ�����ʽʵʱ����
   // Author:    wuZhiHua
   // Date : 	  2018/04/18
   // Access:    public 
   // Returns:   CString
   // Parameter: CADOConn * pADOConn
   // Parameter: CString fileName
   //************************************
   CString GetStyleInfoByFileName(CADOConn *pADOConn, CString fileName  , CString &updateTime);

#ifdef USING_GRIDCTRL_MARK
   //************************************
   // Method:    ��ȡ���
   // Author:    wuZhiHua
   // Date : 	  2018/04/16
   // Access:    private 
   // Returns:   void
   // Parameter: MAP_GridCtrl_AllData & allData
   //************************************
   void GetGridData(CADOConn *pADOConn, __out MAP_GridCtrl_AllData& mapAllData);

   //************************************
   // Method:    ��������ʵʱXML����
   // Author:    yangjr
   // Date : 	  2018/05/29
   // Access:    public 
   // Returns:   BOOL
   // Parameter: CString fileName xml�ļ����� S_GridCtrl_TableAtrri &tableAtrri �����ʽ
   BOOL InsertOrUpdateStyle(CADOConn *pADOConn,CString fileName,const S_GridCtrl_TableAtrri &tableAtrri);

   //************************************
   // Method:    ��ȡ��������XML����
   // Author:    yangjr
   // Date : 	  2018/05/29
   // Access:    public 
   // Returns:   BOOL��S_GridCtrl_TableAtrri &tableAtrri �����ʽ
   // Parameter: CString fileName xml�ļ���
   BOOL GetServerStyle(CADOConn *pADOConn,CString fileName,S_GridCtrl_TableAtrri &tableAtrri);
#endif

private:
	static std::shared_ptr<DBTableStyleGlobalSetInfoList> sm_inst;
};
