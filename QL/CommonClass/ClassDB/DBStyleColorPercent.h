#pragma once
#include "DataMid.h"

/*************************************************
// <�ļ�>: DBStyleColorPercent.h
// <˵��>: ��ɫ���������
// <����>: lida
// <����>: 2019/02/22 15:51:47
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 

#define COLOR_PERCENT_NUM 7 
#define COLOR_PERCENT_CHAR_LENGTH 10
static TCHAR COLOR_PERCENT[COLOR_PERCENT_NUM][COLOR_PERCENT_CHAR_LENGTH] = {
   {_T("��ɫ")},        //0
   {_T("��ɫ1")},        //1
   {_T("��ɫ2")},        //2
   {_T("��ɫ3")},        //3
   {_T("��ɫ4")},        //4
   {_T("��ɫ5")},        //5
   {_T("��ɫ6")},        //5
};
class CADOConn;
class CDBStyleColorPercent :public CDataMid
{
   DECLARE_SERIAL( CDBStyleColorPercent)//���л������л�����Ҫ��ӵ�����
public:
   CDBStyleColorPercent(void);
   ~CDBStyleColorPercent(void);

public:
   int         m_id          ;         // ����ID
   int         m_nRow;       ;         //�к�
   int         m_nPeiSeNum;            //��ɫ����
   CString     m_strStyleNo  ;         // ���
   CString     m_strMainClr  ;         //��ɫ
   CString     m_strFirst;             //��ɫ1
   CString     m_strSecond   ;         //��ɫ2
   CString     m_strThird    ;         //��ɫ3
   CString     m_strFourth   ;         //��ɫ4
   CString     m_strFifth    ;         //��ɫ5
   CString     m_strSixth    ;         //��ɫ6
   int         m_isWeight     ;        //�Ƿ�����������
   CString     m_strSizeInfo;          //����������Ϣ��s(1);m(2);l(3);....

   map<CString,CString> m_mapSizeInfo; //��m_strSizeInfo��������
   int         m_nDataType;
   CString     m_strPinZhong;          //��ɫ��Ʒ�֣���ɫ�ű��ж�ȡ   
   CString     m_strSeMing;            //��ɫ��ɫ������ɫ�ű��ж�ȡ  
   CString     m_strShazhi;            //��ɫ��ɴ֧����ɫ�ű��ж�ȡ  
   enum DataType
   {
      en_null = -1,
      en_add = 0,  
      en_del = 1,
      en_updadte =2,
   };
public:
   void ResetData();
   void Copy(CDBStyleColorPercent *pData);
   void GetAllDBInfo(CADOConn* pADOConn);

   BOOL InsetAllDBInfo(CADOConn* pADOConn);
   BOOL UpdateAllDBInfo(CADOConn* pADOConn); //����ID
   BOOL DeleteAllDBInfo(CADOConn* pADOConn); //����ID

   CString GetInsertSql();
   CString GetUpdateSql();
   CString GetDeleteSql();
   CString GetDeleteSqlByStyleNo(CString strStyleNo);
   static void ParaseSizeInfo(const CString strSizeInfo,map<CString,CString>& mapSizeInfo);
   static void ParaseSizeInfo(const map<CString,CString> mapSizeInfo,CString& strSizeInfo);
};


class CDBStyleColorPercentList :public CDataListMid
{
   DECLARE_SERIAL( CDBStyleColorPercentList)//���л������л�����Ҫ��ӵ�����
public:
   CDBStyleColorPercentList(void);
   ~CDBStyleColorPercentList(void);

   static CDBStyleColorPercentList * Instance();//��ȡ��ָ�룩ʵ��

   CDBStyleColorPercent* GetItem(int nIndex);			//����������ȡItem 
   void AddItem(CDBStyleColorPercent* pItem);			//���Item
   void DeleteItem(int nIndex);					//ɾ���̶�����Item


   static BOOL GetStyleColorPercentData(CADOConn* pADOConn,CString strStyleNo,CDBStyleColorPercentList& oList);
   static BOOL DelStyleColorPercentData(CADOConn* pADOConn,CString strStyleNo);
   static BOOL InsertStyleColorPercentData(CADOConn* pADOConn,CDBStyleColorPercentList& oList);

public:
#ifdef USING_GRIDCTRL_MARK
   static BOOL GetStyleColorPercentInfo(CADOConn* pADOConn,CString strStyleNo,MAP_GridCtrl_AllData& all_data,int& nPSNum,int& nSZNum,map<CString,CString>& mapSize=map<CString,CString>());
#endif

private:
   static std::shared_ptr<CDBStyleColorPercentList> sm_inst;
};