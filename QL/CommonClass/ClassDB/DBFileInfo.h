#pragma once

#include "DataMid.h"

/*************************************************
// <文件>: DBFileInfo.h
// <说明>: 文件表 用于存储上传的文件相关信息（目前暂未实现）
// <作者>: wangzl
// <日期>: 2019/02/22
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 

class CDBFileInfoData  : public CDataMid
{
	DECLARE_SERIAL( CDBFileInfoData)//序列化（串行化）需要添加的声明
public:
   __int64     m_nFileID            ;//自增ID
   CString     m_strRelativePath    ;//相对路径
   CString     m_strUploadUserID    ;//上传人
   CString     m_strUploadTime      ;//上传时间
   CString     m_strFileMD5         ;//文件MD5码
   CString     m_strFileName        ;//文件名
   CString     m_strFileExtension   ;//文件扩展名
   __int64     m_nFileSize          ;//文件大小
   CString     m_strRemark          ;//文件说明
   int         m_nParam_FileType    ;//上传参数-文件类型
   int         m_nParam_WholeType   ;//上传参数-全局类型
   CString     m_strParam_Size      ;//上传参数-尺码

public:
	CDBFileInfoData();
	~CDBFileInfoData();
	void ResetData();
	void Copy(CDBFileInfoData *pData);

   __int64 InsertAllDBInfoByProcess(CADOConn * pADOConn);
   __int64 InsertAllDBInfoByProcess(
      CADOConn * pADOConn,
      const CString & strRelativePath,//文件相对路径
      const CString & strUploadUserID,//上传人
      const CString & strFileMD5,//文件MD5码
      const __int64 & nFileSize,//文件大小
      const CString & strRemark,//文件说明
      const int & nFileType,//上传参数-文件类型
      const CString & strSize,//上传参数-尺码
      const int & nWholeType//上传参数-全局类型
      );
};

class CDBFileInfoList : public CDataListMid
{
	DECLARE_SERIAL(CDBFileInfoList)
public:
	CDBFileInfoList();
	~CDBFileInfoList();
	CDBFileInfoData*  GetItem(int nIndex);
	void    AddItem(CDBFileInfoData* pItem);
	void    DeleteItem(int nIndex);
	static CDBFileInfoList * Instance();			//获取（指针）实例

private:
	static std::shared_ptr<CDBFileInfoList> sm_inst;
};
/*
FileState
	0		=		未制作
	1		=		制作中
	2		=		已完成

	Type
	0		=		订单信息文件
	1		=		工艺信息文件
	2		=		设计信息文件
	3		=		制版信息文件
	4		=		上机信息文件
	5		=		图片信息文件
	*/