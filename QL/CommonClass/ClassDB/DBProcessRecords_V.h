/*************************************************
// <�ļ�>: DBProcessRecords_V.h
// <˵��>: �ӵ��Ĺ���������Ϣ��ͼ ��������ɴ��Ϣ
// <����>: wangzl
// <����>: 2019/01/30 10:25:29
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
#pragma once
#include "DataMid.h"
#include "DBKeyDef.h"
#include "DBProcessRecords.h"

class CADOConn;
//�ӵ��Ĺ���������Ϣ��ͼ
class CDBProcessRecords_VData  : public CDataMid
{
   DECLARE_SERIAL( CDBProcessRecords_VData)//���л������л�����Ҫ��ӵ�����
public:
   __int64 m_nID                ;
   CString m_strCode            ;
   CString m_strGXName          ;
   CString m_strDate1           ;
   CString m_strDate3           ;
   CString m_strPersonCode      ;
   double  m_fGongjia           ;
   double  m_fFujia             ;
   CString m_strMemo            ;
   int     m_nState             ;
   CString m_strAllotPersonCode ;
   int     m_nPriority          ;
   int     m_nFlag              ;
   int     m_nCurProcess        ;
   CString m_strDateAssign      ;
   int     m_nChecked           ;
   int     m_nRewindNum         ;
   __int64 m_nRewindFrom        ;
   CString m_strCate            ;
   CString m_strDate            ;
   CString m_strMaker           ;
   CString m_strCusCode         ;
   CString m_strInvCustCode     ;
   CString m_strInvCustName     ;
   int     m_nAllJianshu        ;
   CString m_strInvKuanhao      ;
   CString m_strInvJinxian      ;
   CString m_strInvLingxing     ;
   CString m_strInvDibian       ;
   CString m_strInvJiagongfei   ;
   CString m_strInvFujiafei     ;
   CString m_strSexType         ;
   CString m_strShouYao         ;
   CString m_strZhiYiCode       ;
   CString m_strJiaoDate        ;
   CString m_strTrueTime        ;
   CString m_strNeedleType      ;
   int     m_nOtherFlag         ;
   int     m_nOrdCreateFlag     ;
   CString m_strMacType         ;
   CString m_strClassType       ;
   CString m_strAmountType      ;
   CString m_strGoodsType       ;
   CString m_strInvXiukou       ;
   CString m_strInvJiaji        ;
   CString m_strInvMemo         ;
   CString m_strInvState        ;
   CString m_strInvFahuoDate    ;
   CString m_strInvState2       ;
   CString m_strInvSehao        ;
   CString m_strInvPeise        ;
   CString m_strCusName         ;
   CString m_strCusMobile       ;
   CString m_strKuanming        ;
   CString m_strTreeName        ;
   CString m_strChenfen         ;
   CString m_strColorCate       ;
   CString m_strCusCate         ;
   int     m_nChuguan           ;
   double  m_fChuweight         ;
   int     m_nHuiguan           ;
   double  m_fHuiweight         ;
   double  m_fPianweight        ;
   double  m_fGuanweight        ;
   CString m_strPihao           ;
   CString m_strPersonName      ;
   CString m_strAllotPersonName ;
   CString m_strbiflag;
public:
   CDBProcessRecords_VData();
   ~CDBProcessRecords_VData();
   void ResetData();
   void Copy(CDBProcessRecords_VData *pData);
   BOOL GetAllDBInfo(CADOConn *pADOConn);

};

class CDBProcessRecords_VList : public CDataListMid
{
   DECLARE_SERIAL(CDBProcessRecords_VList)
public:
   CDBProcessRecords_VList();
   ~CDBProcessRecords_VList();
   CDBProcessRecords_VData*  GetItem(int nIndex);
   void    AddItem(CDBProcessRecords_VData* pItem);
   void    DeleteItem(int nIndex);

   static CDBProcessRecords_VList * Instance();//��ȡ��ָ�룩ʵ��


private:
   static std::shared_ptr<CDBProcessRecords_VList> sm_inst;



};