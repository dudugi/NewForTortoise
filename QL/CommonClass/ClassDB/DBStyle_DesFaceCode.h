/*************************************************
// <�ļ�>: DBStyle_DesFaceCode.h
// <˵��>: ��ʽ������
// <����>: wangzl
// <����>: 2019/06/19
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
#pragma once
#include "DataMid.h"
class CADOConn;

class CDBStyle_DesFaceCodeData  : public CDataMid
{
   DECLARE_SERIAL(CDBStyle_DesFaceCodeData)//���л������л�����Ҫ��ӵ�����
public:
   __int64  m_nID          ;//����ID
   CString  m_strName      ;//���� eg:������
   CString  m_sOldLen      ;//
   CString  m_strType      ;//���� eg:֧��
   CString  m_sLen         ;//����
   CString  m_strUnit      ;//��λ eg:����
   __int64  m_nIDDensity   ;//�ܶȹ����ֶ�����ID

public:
   CDBStyle_DesFaceCodeData();
   ~CDBStyle_DesFaceCodeData();
   void ResetData();
   void Copy(CDBStyle_DesFaceCodeData *pData);
   BOOL GetAllDBInfo(CADOConn *pADOConn);
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
};

class CDBStyle_DesFaceCodeList : public CTDataListMid<CDBStyle_DesFaceCodeList,CDBStyle_DesFaceCodeData>
{
public:
   CDBStyle_DesFaceCodeList();
   ~CDBStyle_DesFaceCodeList();
};