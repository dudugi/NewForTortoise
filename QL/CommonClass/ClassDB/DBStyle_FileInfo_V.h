/*************************************************
// <文件>: DBStyle_FileInfo.h
// <说明>: 款式的文件属性DB类
// <作者>: wangzl
// <日期>: 2019/05/28
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 
#pragma once
#include "DataMid.h"

class CDBStyle_FileInfo_VData : public CDataMid
{
   DECLARE_SERIAL( CDBStyle_FileInfo_VData)//序列化（串行化）需要添加的声明
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
   BOOL GetAllDBInfo(CADOConn *pADOConn);				//获取【整条】信息
};

class CDBStyle_FileInfo_VList : public CTDataListMid<CDBStyle_FileInfo_VList,CDBStyle_FileInfo_VData>
{
public:
   static void GetStyleFileInfo(CADOConn* pAdo,CString strStyleNo,vector<CDBStyle_FileInfo_VData*>& vecFileInfo);
};

