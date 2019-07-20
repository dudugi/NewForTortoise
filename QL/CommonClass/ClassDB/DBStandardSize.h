#pragma once

/*************************************************
// <文件>: DBStandardSize.h
// <说明>: 标准尺码表DB类
// <作者>: huangym(头文件注释)
// <日期>: 2019/02/21 16:10:26
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/

#include "DataMid.h"
#include "Resource.h"
#include <afxwin.h>
#ifdef USING_GRIDCTRL_MARK
#include "CDataTableDlgDefine.h"
#endif // USING_GRIDCTRL_MARK
#include "DBSizeInfo.h"
class CADOConn;

enum Enum_ListBox
{
   ListBox_Position = 0,
   ListBox_Size
};

#define STANDARD_SIZEMODIFY_ROWNAME  _T("部位/尺码")
class CDBStandardSizeModifyList;
class CDBStandardSize :
   public CDataMid
{
   DECLARE_SERIAL(CDBStandardSize)                     //序列化（串行化）需要添加的声明
public:
   CDBStandardSize();
   ~CDBStandardSize();;
   static CDBStandardSize * Instance();                // 获取（指针）实例

   void Copy(CDBStandardSize *pData);                  // 拷贝数据
   void ResetData();                                   // 重置数据
   void UpdateDataValue();                             // 刷新旗下数据
   CString GetInsertSQL();                             // 获取插入的SQL语句

   BOOL UpdateDBInfo(CADOConn * pADOConn);             // 更新DB
   BOOL GetAllDBInfo(CADOConn *pADOConn);		          // 获取【整条】信息
   BOOL UpdateAllDBInfoByID(CADOConn * pADOConn);      // 更新数据到数据库
   BOOL InsertAllDBInfoByID(CADOConn * pADOConn);      // 添加数据到数据库
   BOOL GetDataByGrid(CADOConn * pADOConn, const MAP_GridCtrl_AllData& data);            // 根据表格数据创建新数据
   BOOL GetStyleNoByFangAn(CADOConn *pADOConn,CString strStyleNo);
   BOOL GetStyleNoByPingMing(CADOConn *pADOConn,CString strPM);
private:
   static std::shared_ptr<CDBStandardSize> sm_inst;

public:
   __int64		               m_nID;              //自增ID
   CString                    m_strName;          //名称
   CString                    m_strRemark;        //说明
   vector<CString>            m_vecSize;          //尺寸集合
   map<CString,CString>       m_mapPosition;      //部位集合+说明
   vector<CString>            m_vecPinMing;       //品名集合
   CDBStandardSizeModifyList* m_pModifyList;      //对应详情列表
};

class CDBStandardSizeList : public CDataListMid
{
   DECLARE_SERIAL(CDBStandardSizeList)
public:
   CDBStandardSizeList();
   ~CDBStandardSizeList();
   void Copy( CDBStandardSizeList *pList );

   CDBStandardSize*  GetItem(int nIndex);
   void    AddItem(CDBStandardSize* pItem);
   void    DeleteItem(int nIndex);
   BOOL    DeleteUserByUserID(CADOConn * pADOConn, vector<CString> vecUserID);
   BOOL    GetAllDBInfo(CADOConn *pADOConn);// 获取所有数据 liuhw 2019/05/16

   static CDBStandardSizeList * Instance();		//获取（指针）实例
   MAP_GridCtrl_AllData CreateGridData(const CString & strUserDuty = _T(""));//生成表格数据
private:
   static std::shared_ptr<CDBStandardSizeList> sm_inst;
};

class CDBStandardSizeModify :   public CDataMid
{
   DECLARE_SERIAL(CDBStandardSizeModify)                         //序列化（串行化）需要添加的声明
public:
   CDBStandardSizeModify();
   ~CDBStandardSizeModify();;
   static CDBStandardSizeModify * Instance();                // 获取（指针）实例
   
   void ResetData();                                   // 重置数据
   CString GetInsertSQL();                             // 获取插入的SQL语句
   void Copy(CDBStandardSizeModify *pData);            // 拷贝数据
   BOOL UpdateDBInfo(CADOConn * pADOConn);             // 更新DB
   BOOL GetAllDBInfo(CADOConn *pADOConn);		          // 获取【整条】信息

   BOOL UpdateAllDBInfoByID(CADOConn * pADOConn);      // 更新数据到数据库
   BOOL InsertAllDBInfoByID(CADOConn * pADOConn);      // 添加数据到数据库
private:
   static std::shared_ptr<CDBStandardSizeModify> sm_inst;

public:
   __int64		               m_nID;              //自增ID
   __int64		               m_nSizeID;          //外键ID，判定名称
   CString                    m_strSize;          //尺寸
   CString                    m_strPosition;      //部位
   CString                    m_strName;          //名称
   double                     m_nNumber;          //尺寸值
   CString                    m_cMemo;            //说明
};


class CDBStandardSizeModifyList : public CDataListMid
{
   DECLARE_SERIAL(CDBStandardSizeModifyList)
public:
   CDBStandardSizeModifyList();
   ~CDBStandardSizeModifyList();
   void Copy( CDBStandardSizeModifyList *pList );
   CDBStandardSizeModify*  GetItem(int nIndex);
   BOOL GetItemBySize(CString strName);
   BOOL GetItemByPos(CString strName);
   void    AddItem(CDBStandardSizeModify* pItem);
   void    DeleteItem(int nIndex);
   BOOL    DeleteUserByUserID(CADOConn * pADOConn, vector<CString> vecUserID);
   BOOL    GetAllDBInfoByFangAnName(CADOConn *pADOConn,CString strFangAnNmae);// 根据方案名获取所有尺寸数据 liuhw 2019/05/16
   BOOL    GetAllDBInfoByPM(CADOConn *pADOConn,CString strPinMing);// 根据款号的品名获取所有尺寸方案数据 liuhw 2019/05/16

   void    SortList(CDBSizePartInfoList * pSizePartList);

   static CDBStandardSizeModifyList * Instance();		//获取（指针）实例
#ifdef USING_GRIDCTRL_MARK
   MAP_GridCtrl_AllData CreateGridData(map<CString,CString> & map_Size);//生成表格数据
#endif // USING_GRIDCTRL_MARK
private:
   static std::shared_ptr<CDBStandardSizeModifyList> sm_inst;
};
