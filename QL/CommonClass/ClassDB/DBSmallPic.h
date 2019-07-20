#pragma once

/*************************************************
// <文件>: DBSmallPic.h
// <说明>: 小图库DB类
// <作者>: huangym(头文件注释)
// <日期>: 2019/02/21 16:02:03
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/

#include "DataMid.h"
#include "Dib.h"
#include "ViewCtrl.h"
class CADOConn;

#ifndef Des_IMAGE
#define Des_IMAGE	1
#endif

class CDBSmallPic :
   public CDataMid
{
   DECLARE_SERIAL(CDBSmallPic)                         //序列化（串行化）需要添加的声明
public:
   CDBSmallPic();
   ~CDBSmallPic();;
   void ResetData();                                   // 重置数据
   BOOL UpdateDBInfo(CADOConn * pADOConn);             // 更新DB
   BOOL GetAllDBInfo(CADOConn *pADOConn);		          // 获取【整条】信息
   void Copy(CDBSmallPic *pData);                      // 拷贝数据

   
   CString GetInsertSQL();                             // 获取插入的SQL语句
   static CDBSmallPic * Instance();                    // 获取（指针）实例
   BOOL UpdateAllDBInfoByID(CADOConn * pADOConn);      // 更新数据到数据库
   BOOL InsertAllDBInfoByID(CADOConn * pADOConn);      // 添加数据到数据库
#ifdef Des_IMAGE
private:
   inline void ClearColorImage();
#endif // Des_IMAGE
private:
   static std::shared_ptr<CDBSmallPic> sm_inst;

public:
   __int64		               m_nID;              //自增ID
   CString                    m_strName;          //名称
   int                        m_nWidth;           //宽度
   int                        m_nHeight;          //高度
   bool                       m_bLoop;            //最小循环
   bool                       m_bKeepLine;        //保存功能线
   CString                    m_strContact;       //联系方式
   CString                    m_strType;          //小图自定义类型(类型)
   CString                    m_strSavedUserID;   //用户ID
   CString                    m_strSaveTime;      //保存时间
   CString                    m_strRemark;        //小图说明
#if Des_IMAGE
   Gdiplus::Image*				m_pSmallDetailPic;  //预览图
#endif
};


class CDBSmallPicList : public CDataListMid
{
   DECLARE_SERIAL(CDBSmallPicList)
public:
   CDBSmallPicList();
   ~CDBSmallPicList();
   CDBSmallPic*  GetItem(int nIndex);
   void    AddItem(CDBSmallPic* pItem);
   void    DeleteItem(int nIndex);
   BOOL    DeleteUserByUserID(CADOConn * pADOConn, vector<CString> vecUserID);

   static CDBSmallPicList * Instance();		//获取（指针）实例
   //生成表格数据
   MAP_GridCtrl_AllData CreateGridData(const CString & strUserDuty = _T(""));

private:
   static std::shared_ptr<CDBSmallPicList> sm_inst;
};
