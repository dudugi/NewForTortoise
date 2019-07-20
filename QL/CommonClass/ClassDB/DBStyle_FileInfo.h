/*************************************************
// <�ļ�>: DBStyle_FileInfo.h
// <˵��>: ��ʽ���ļ�����DB��
// <����>: wangzl
// <����>: 2019/05/28
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
#pragma once
#include "DataMid.h"

#define PIC_SHOW_DX   15  //ͼƬ���
#define PAGE_BTN_WIDTH  30 //����ҳ��ť���
#define PIC_SHOW_WIDTH 138  //ͼƬ���
#define PIC_SHOW_HEIGHT  115  //ͼƬ�߶�
#define PIC_TEXTSIZE  12  //ͼƬ���ָ߶�


class CDBStyle_FileInfoData : public CDataMid
{
   DECLARE_SERIAL( CDBStyle_FileInfoData)//���л������л�����Ҫ��ӵ�����
public:
   CDBStyle_FileInfoData(void);
   ~CDBStyle_FileInfoData(void);

   typedef enum{
      en_Order = 0,//����
      en_Design,//���
      en_Process,//����
      en_Pattern,//�ư�
      en_Mac,//�ϻ�
      en_Picture,//ͼƬ�ļ� 5
      en_Thumbnail,//����ͼ 6
      en_video,   //��Ƶ
      en_ModelPicture,//չʾͼͼƬ�ļ�
      en_ModelThumbnail,//չʾͼ����ͼ
   };

   INT64    m_nID       ;//ID
   INT64    m_nFileID   ;//�������ļ�ID
   CString  m_strStyleNo;//���
   int      m_nFileType ;//�ļ�����
   int      m_nSortID;     //�ļ����� - ��ʾʱ�������� by lida 2019/06/27

public:
   void ResetData();
   void Copy(CDBStyle_FileInfoData *pData);
   BOOL GetAllDBInfo(CADOConn *pADOConn);				//��ȡ����������Ϣ
   BOOL InsertAllDBInfo(CADOConn *pADOConn);	//���롾�������¼�¼
   BOOL UpdateAllDBInfoByID(CADOConn *pADOConn);	//�����û��˻����¡���������¼
   BOOL SaveDBInfo(CADOConn * pADOConn);//������Ϣ  ������߸���
};

class CDBStyle_FileInfoList :public CDataListMid
{
   DECLARE_SERIAL( CDBStyle_FileInfoList)//���л������л�����Ҫ��ӵ�����
public:
   CDBStyle_FileInfoList(void);
   ~CDBStyle_FileInfoList(void);
public:
   void Copy(CDBStyle_FileInfoList *pList);
   CDBStyle_FileInfoData*  GetItem(int nIndex);
   void AddItem(CDBStyle_FileInfoData *pItem);
   void DeleteItemByIndex(int nIndex);
};
