#pragma once
/*************************************************
// <�ļ�>: DBStyleDescription.h
// <˵��>: ��ʽ������
// <����>: lida
// <����>: 2019/06/11 15:54:26
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
#include "DataMid.h"

class CDBStyleDescription : public CDataMid
{
public:
   CDBStyleDescription();
   ~CDBStyleDescription();

   void ResetData();
   void Copy(CDBStyleDescription *pData);

   BOOL DoInsert(CADOConn *pADOConn);
   BOOL DoUpdate(CADOConn *pADOConn);
   BOOL DoDelete(CADOConn *pADOConn);

   CString GetInsertSql();
   CString GetUpdateSql();
   CString GetDeleteSql();
   static CString GetDeleteByStyleNoSql(const CString & strStyleNo);

   static CDBStyleDescription * Instance();//��ȡ��ָ�룩ʵ��

public:
   int      m_ID;
   CString  m_strKuanhao;
   CString  m_strDesrciption;

#ifdef USING_GRIDCTRL_MARK
#endif // USING_GRIDCTRL_MARK

private:
   static std::shared_ptr<CDBStyleDescription> sm_inst;
};