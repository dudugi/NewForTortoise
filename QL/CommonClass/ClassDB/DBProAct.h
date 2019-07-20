/*************************************************
// <�ļ�>: DBProAct.h
// <˵��>: ���������  ���ڴ��������Ĳ����߼�
// <����>: wangzl 
// <����>: 2019/02/22 
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
#pragma once

#include "DBProSearchInfo.h"
#include <vector>

class CADOConn;

class CDBProAct
{
public:
	CDBProAct(void);
	~CDBProAct(void);

   //************************************
   // <����>:   CompareStyleProOrder
   // <˵��>:   �ȶԿ�ʽ�ĵ�ǰ����˳�������˳��
   // <����>:   wangzl
   // <����>:   2019/05/23
   // <Access>: public 
   // <Return>: int -1������<��ʽ�� 0 ������=��ʽ�� 1������>��ʽ��
   // <����>:   CADOConn * pADOConn ���ݿ����ָ��
   // <����>:   const CString & strStyleNo ���
   // <����>:   int nCurProOrder ��ǰ�����˳��
   //************************************
   int CompareStyleProOrder(CADOConn * pADOConn,const CString & strStyleNo,int nCurProOrder);

   //************************************
   // <����>:   HasMustRunningPro
   // <˵��>:   �ڿ�ʽ�ĵ�ǰ����״̬�봫���״̬֮���Ƿ����κα�����ת�Ĺ���
   // <����>:   wangzl
   // <����>:   2019/05/23
   // <Access>: public 
   // <Return>: BOOL
   // <����>:   CADOConn * pADOConn ���ݿ����ָ��
   // <����>:   const CString & strStyleNo ���
   // <����>:   int nCurProOrder ��ǰ����Ĺ���˳��
   //************************************
   BOOL HasMustRunningPro(CADOConn * pADOConn,const CString & strStyleNo,int nCurProOrder);
};




class CDBProSearch 
{
public:
   CDBProSearch();
   ~CDBProSearch();

public:
   static std::vector<S_ProUserStyleInfo> GetUserProStyleInfo(CADOConn * pADOConn,const CString & strUserID,const CString & strGroup);

   static std::vector<S_ProUserStyleInfo> GetUserProStyleInfoFinished(CADOConn * pADOConn,
      const CString & strUserID, UINT uSortID,const CString & strUserDuty,const CString & strTreeCode); //����� by duchen
};