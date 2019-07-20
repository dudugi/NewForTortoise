/*************************************************
// <文件>: DBProductRevisionRecords_V.h
// <说明>: 打样改版记录视图
// <作者>: wangzl
// <日期>: 2019/02/22
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 
#pragma once
#include "DataMid.h"
#include "DBP_ProductRevisionRecords.h"

class CADOConn;
class CDBProductRevisionRecords_VData  : public CDataMid
{
   DECLARE_SERIAL( CDBProductRevisionRecords_VData)//序列化（串行化）需要添加的声明
public:

   CString  m_strClassification              ;
   CString  m_strCategory                    ;
   CString  m_strBand_Name                   ;
   int      m_nCurProSort                    ;

   CDBP_ProductRevisionRecordsData m_ProductRevisionData;

public:
   CDBProductRevisionRecords_VData();
   ~CDBProductRevisionRecords_VData();
   void ResetData();
   void Copy(CDBProductRevisionRecords_VData *pData);
   BOOL GetAllDBInfo(CADOConn *pADOConn);

   void Trim();


#ifdef USING_GRIDCTRL_MARK
   //行数据
   MAP_GridCtrl_RowData CreateGridRowData(CADOConn * pADOConn);//2017/08/31
#endif // USING_GRIDCTRL_MARK

};

class CDBProductRevisionRecords_VList : public CDataListMid
{
   DECLARE_SERIAL(CDBProductRevisionRecords_VList)
public:
   CDBProductRevisionRecords_VList();
   ~CDBProductRevisionRecords_VList();
   CDBProductRevisionRecords_VData*  GetItem(int nIndex);
   void    AddItem(CDBProductRevisionRecords_VData* pItem);
   void    DeleteItem(int nIndex);

   static CDBProductRevisionRecords_VList * Instance();//获取（指针）实例

private:
   static std::shared_ptr<CDBProductRevisionRecords_VList> sm_inst;
};