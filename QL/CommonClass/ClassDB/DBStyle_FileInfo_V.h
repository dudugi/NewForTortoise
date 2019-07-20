/*************************************************
// <�ļ�>: DBStyle_FileInfo.h
// <˵��>: ��ʽ���ļ�����DB��
// <����>: wangzl
// <����>: 2019/05/28
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
#pragma once
#include "DataMid.h"

class CDBStyle_FileInfo_VData : public CDataMid
{
   DECLARE_SERIAL( CDBStyle_FileInfo_VData)//���л������л�����Ҫ��ӵ�����
public:
   CDBStyle_FileInfo_VData(void);
   ~CDBStyle_FileInfo_VData(void);

   INT64    m_ID              ;
   INT64    m_nFileID         ;
   CString  m_strStyleNo      ;
   int      m_nFileType       ;
   CString  m_strRelativePath ;
   CString  m_strUploadUserID ;
   CString  m_strUploadTime   ;
   CString  m_strFileMD5      ;
   CString  m_strFileName     ;
   CString  m_strFileExtension;
   __int64  m_nFileSize       ;
   CString  m_strRemark       ;
   int      m_nSort           ;
   int      m_nParam_FileType ;
   int      m_nParam_WholeType;
   CString  m_strParam_Size   ;

public:
   void ResetData();
   void Copy(CDBStyle_FileInfo_VData *pData);
   BOOL GetAllDBInfo(CADOConn *pADOConn);				//��ȡ����������Ϣ
};

class CDBStyle_FileInfo_VList : public CTDataListMid<CDBStyle_FileInfo_VList,CDBStyle_FileInfo_VData>
{
public:
   static void GetStyleFileInfo(CADOConn* pAdo,CString strStyleNo,vector<CDBStyle_FileInfo_VData*>& vecFileInfo);
};

