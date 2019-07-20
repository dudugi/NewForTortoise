#pragma once
#include "DataMid.h"

/*************************************************
// <文件>: DBStyleColorPercent.h
// <说明>: 配色方案，相关
// <作者>: lida
// <日期>: 2019/02/22 15:51:47
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 

#define COLOR_PERCENT_NUM 7 
#define COLOR_PERCENT_CHAR_LENGTH 10
static TCHAR COLOR_PERCENT[COLOR_PERCENT_NUM][COLOR_PERCENT_CHAR_LENGTH] = {
   {_T("主色")},        //0
   {_T("配色1")},        //1
   {_T("配色2")},        //2
   {_T("配色3")},        //3
   {_T("配色4")},        //4
   {_T("配色5")},        //5
   {_T("配色6")},        //5
};
class CADOConn;
class CDBStyleColorPercent :public CDataMid
{
   DECLARE_SERIAL( CDBStyleColorPercent)//序列化（串行化）需要添加的声明
public:
   CDBStyleColorPercent(void);
   ~CDBStyleColorPercent(void);

public:
   int         m_id          ;         // 自增ID
   int         m_nRow;       ;         //行号
   int         m_nPeiSeNum;            //配色数量
   CString     m_strStyleNo  ;         // 款号
   CString     m_strMainClr  ;         //主色
   CString     m_strFirst;             //配色1
   CString     m_strSecond   ;         //配色2
   CString     m_strThird    ;         //配色3
   CString     m_strFourth   ;         //配色4
   CString     m_strFifth    ;         //配色5
   CString     m_strSixth    ;         //配色6
   int         m_isWeight     ;        //是否是重量数据
   CString     m_strSizeInfo;          //尺码数量信息：s(1);m(2);l(3);....

   map<CString,CString> m_mapSizeInfo; //从m_strSizeInfo解析数据
   int         m_nDataType;
   CString     m_strPinZhong;          //主色的品种，从色号表中读取   
   CString     m_strSeMing;            //主色的色名，从色号表中读取  
   CString     m_strShazhi;            //主色的纱支，从色号表中读取  
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
   BOOL UpdateAllDBInfo(CADOConn* pADOConn); //根据ID
   BOOL DeleteAllDBInfo(CADOConn* pADOConn); //根据ID

   CString GetInsertSql();
   CString GetUpdateSql();
   CString GetDeleteSql();
   CString GetDeleteSqlByStyleNo(CString strStyleNo);
   static void ParaseSizeInfo(const CString strSizeInfo,map<CString,CString>& mapSizeInfo);
   static void ParaseSizeInfo(const map<CString,CString> mapSizeInfo,CString& strSizeInfo);
};


class CDBStyleColorPercentList :public CDataListMid
{
   DECLARE_SERIAL( CDBStyleColorPercentList)//序列化（串行化）需要添加的声明
public:
   CDBStyleColorPercentList(void);
   ~CDBStyleColorPercentList(void);

   static CDBStyleColorPercentList * Instance();//获取（指针）实例

   CDBStyleColorPercent* GetItem(int nIndex);			//根据索引获取Item 
   void AddItem(CDBStyleColorPercent* pItem);			//添加Item
   void DeleteItem(int nIndex);					//删除固定索引Item


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