/*************************************************
// <�ļ�>: DBStyle_FileInfo.h
// <˵��>: ��ʽ���ļ�����DB��
// <����>: wangzl
// <����>: 2019/05/28
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
#pragma once
#include "DataMid.h"

class CDBSampleClothing_FileInfo_VData : public CDataMid
{
   DECLARE_SERIAL( CDBSampleClothing_FileInfo_VData)//���л������л�����Ҫ��ӵ�����
public:
   CDBSampleClothing_FileInfo_VData(void);
   ~CDBSampleClothing_FileInfo_VData(void);

   INT64    m_ID              ;
   INT64    m_nFileID         ;
   CString  m_strBarCode      ;
   int      m_nFileType       ;
   CString  m_strRelativePath ;
   CString  m_strUploadUserID ;
   CString  m_strUploadTime   ;
   CString  m_strFileMD5      ;
   CString  m_strFileName     ;
   CString  m_strFileExtension;
   __int64  m_nFileSize       ;
   CString  m_strRemark       ;

public:
   void ResetData();
   void Copy(CDBSampleClothing_FileInfo_VData *pData);
   BOOL GetAllDBInfo(CADOConn *pADOConn);				//��ȡ����������Ϣ
};

class CDBSampleClothing_FileInfo_VList :public CDataListMid
{
   DECLARE_SERIAL( CDBSampleClothing_FileInfo_VList)//���л������л�����Ҫ��ӵ�����
public:
   CDBSampleClothing_FileInfo_VList(void);
   ~CDBSampleClothing_FileInfo_VList(void);
public:
   void Copy(CDBSampleClothing_FileInfo_VList *pList);
   CDBSampleClothing_FileInfo_VData*  GetItem(int nIndex);
   void AddItem(CDBSampleClothing_FileInfo_VData *pItem);
   void DeleteItemByIndex(int nIndex);

   static void GetStyleFileInfo(CADOConn* pAdo,CString strStyleNo,vector<CDBSampleClothing_FileInfo_VData*>& vecFileInfo);
};
