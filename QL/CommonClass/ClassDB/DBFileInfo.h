#pragma once

#include "DataMid.h"

/*************************************************
// <�ļ�>: DBFileInfo.h
// <˵��>: �ļ��� ���ڴ洢�ϴ����ļ������Ϣ��Ŀǰ��δʵ�֣�
// <����>: wangzl
// <����>: 2019/02/22
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 

class CDBFileInfoData  : public CDataMid
{
	DECLARE_SERIAL( CDBFileInfoData)//���л������л�����Ҫ��ӵ�����
public:
   __int64     m_nFileID            ;//����ID
   CString     m_strRelativePath    ;//���·��
   CString     m_strUploadUserID    ;//�ϴ���
   CString     m_strUploadTime      ;//�ϴ�ʱ��
   CString     m_strFileMD5         ;//�ļ�MD5��
   CString     m_strFileName        ;//�ļ���
   CString     m_strFileExtension   ;//�ļ���չ��
   __int64     m_nFileSize          ;//�ļ���С
   CString     m_strRemark          ;//�ļ�˵��
   int         m_nParam_FileType    ;//�ϴ�����-�ļ�����
   int         m_nParam_WholeType   ;//�ϴ�����-ȫ������
   CString     m_strParam_Size      ;//�ϴ�����-����

public:
	CDBFileInfoData();
	~CDBFileInfoData();
	void ResetData();
	void Copy(CDBFileInfoData *pData);

   __int64 InsertAllDBInfoByProcess(CADOConn * pADOConn);
   __int64 InsertAllDBInfoByProcess(
      CADOConn * pADOConn,
      const CString & strRelativePath,//�ļ����·��
      const CString & strUploadUserID,//�ϴ���
      const CString & strFileMD5,//�ļ�MD5��
      const __int64 & nFileSize,//�ļ���С
      const CString & strRemark,//�ļ�˵��
      const int & nFileType,//�ϴ�����-�ļ�����
      const CString & strSize,//�ϴ�����-����
      const int & nWholeType//�ϴ�����-ȫ������
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
	static CDBFileInfoList * Instance();			//��ȡ��ָ�룩ʵ��

private:
	static std::shared_ptr<CDBFileInfoList> sm_inst;
};
/*
FileState
	0		=		δ����
	1		=		������
	2		=		�����

	Type
	0		=		������Ϣ�ļ�
	1		=		������Ϣ�ļ�
	2		=		�����Ϣ�ļ�
	3		=		�ư���Ϣ�ļ�
	4		=		�ϻ���Ϣ�ļ�
	5		=		ͼƬ��Ϣ�ļ�
	*/