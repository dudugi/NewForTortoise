/*************************************************
// <文件>: DBStyle_FileInfo.h
// <说明>: 款式的文件属性DB类
// <作者>: wangzl
// <日期>: 2019/05/28
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 
#pragma once
#include "DataMid.h"

class CDBSampleClothing_FileInfo_VData : public CDataMid
{
   DECLARE_SERIAL( CDBSampleClothing_FileInfo_VData)//序列化（串行化）需要添加的声明
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
   BOOL GetAllDBInfo(CADOConn *pADOConn);				//获取【整条】信息
};

class CDBSampleClothing_FileInfo_VList :public CDataListMid
{
   DECLARE_SERIAL( CDBSampleClothing_FileInfo_VList)//序列化（串行化）需要添加的声明
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
