/*************************************************
// <文件>: DBStyle_FileInfo.h
// <说明>: 款式的文件属性DB类
// <作者>: wangzl
// <日期>: 2019/05/28
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 
#pragma once
#include "DataMid.h"

#define PIC_SHOW_DX   15  //图片间隔
#define PAGE_BTN_WIDTH  30 //上下页按钮宽度
#define PIC_SHOW_WIDTH 138  //图片宽度
#define PIC_SHOW_HEIGHT  115  //图片高度
#define PIC_TEXTSIZE  12  //图片文字高度


class CDBSampleClothing_FileInfoData : public CDataMid
{
   DECLARE_SERIAL( CDBSampleClothing_FileInfoData)//序列化（串行化）需要添加的声明
public:
   CDBSampleClothing_FileInfoData(void);
   ~CDBSampleClothing_FileInfoData(void);

   typedef enum{
      en_Order = 0,//订单
      en_Design,//设计
      en_Process,//工艺
      en_Pattern,//制版
      en_Mac,//上机
      en_Picture,//图片文件
      en_Thumbnail,//缩略图
      en_video,   //视频
      en_ModelPicture,//展示图图片文件
      en_ModelThumbnail,//展示图缩略图
   };

   INT64    m_nID       ;//ID
   INT64    m_nFileID   ;//关联的文件ID
   CString  m_strBarCode;//款号
   int      m_nFileType ;//文件类型
   int      m_nSortID;     //文件排序 - 显示时用来排序 by lida 2019/06/27

public:
   void ResetData();
   void Copy(CDBSampleClothing_FileInfoData *pData);
   BOOL GetAllDBInfo(CADOConn *pADOConn);				//获取【整条】信息
   BOOL InsertAllDBInfo(CADOConn *pADOConn);	//插入【整条】新记录
   BOOL UpdateAllDBInfoByID(CADOConn *pADOConn);	//根据用户账户更新【整条】记录
   BOOL SaveDBInfo(CADOConn * pADOConn);//保存信息  插入或者更新
};

class CDBSampleClothing_FileInfoList :public CDataListMid
{
   DECLARE_SERIAL( CDBSampleClothing_FileInfoList)//序列化（串行化）需要添加的声明
public:
   CDBSampleClothing_FileInfoList(void);
   ~CDBSampleClothing_FileInfoList(void);
public:
   void Copy(CDBSampleClothing_FileInfoList *pList);
   CDBSampleClothing_FileInfoData*  GetItem(int nIndex);
   void AddItem(CDBSampleClothing_FileInfoData *pItem);
   void DeleteItemByIndex(int nIndex);
};
