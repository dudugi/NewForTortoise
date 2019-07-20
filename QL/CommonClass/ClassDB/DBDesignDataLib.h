#pragma once
#include "DataMid.h"
class CADOConn;

/*************************************************
// <文件>: DBDesignDataLib.h
// <说明>: 部件库DB类
// <作者>: huangym(头文件注释)
// <日期>: 2019/02/21 16:09:54
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/

#define DBDesignDataLib_nLength                        _T("身长")        // 身长
#define DBDesignDataLib_nBust                          _T("胸围 ")       // 胸围 
#define DBDesignDataLib_nShoulderWidth                 _T("肩宽")        // 肩宽
#define DBDesignDataLib_nCollarWidth                   _T("领宽")        // 领宽
#define DBDesignDataLib_nCollarHeight                  _T("领高")        // 领高
#define DBDesignDataLib_nFront                         _T("前胸宽")       // 前胸宽
#define DBDesignDataLib_nBehind                        _T("后背宽")       // 后背宽
#define DBDesignDataLib_nMidWidth                      _T("中腰宽")       // 中腰宽
#define DBDesignDataLib_nMidHeight                     _T("中腰高")       // 中腰高
#define DBDesignDataLib_nBellowWidth                   _T("下摆宽")       // 下摆宽
#define DBDesignDataLib_nBellowHeight                  _T("下摆高")       // 下摆高
#define DBDesignDataLib_nShoulderSlanting              _T("肩斜")        // 肩斜
#define DBDesignDataLib_nShoulder                      _T("挂肩")        // 挂肩
#define DBDesignDataLib_nShoulderHeight                _T("挂肩收针高")     // 挂肩收针高
#define DBDesignDataLib_nShoudlerHor                   _T("挂肩平收")      // 挂肩平收
#define DBDesignDataLib_nFrontDeep                     _T("前领深")       // 前领深
#define DBDesignDataLib_nBehindDeep                    _T("后领深")       // 后领深
#define DBDesignDataLib_nSleeveLength                  _T("袖长")        // 袖长
#define DBDesignDataLib_nSleeveWidth                   _T("袖宽")        // 袖宽
#define DBDesignDataLib_cTomid                         _T("袋距中")       // 袋距中
#define DBDesignDataLib_cToTop                         _T("袋距顶")       // 袋距顶
#define DBDesignDataLib_cWidth1                        _T("袋宽1")       // 袋宽1
#define DBDesignDataLib_cWidth2                        _T("袋宽2")       // 袋宽2
#define DBDesignDataLib_cHeight1                       _T("袋高1")       // 袋高1
#define DBDesignDataLib_cHeight2                       _T("袋高2")       // 袋高2
#define DBDesignDataLib_cTotalHeight                   _T("总袋高")       // 总袋高
#define DBDesignDataLib_cTotalWidth                    _T("总袋宽")       // 总袋宽

class CDBDesignDataLib :
   public CDataMid
{
   DECLARE_SERIAL(CDBDesignDataLib)                                       // 序列化（串行化）需要添加的声明
public:
   CDBDesignDataLib();
   ~CDBDesignDataLib();;
   void ResetData();                                                      // 重置数据
   BOOL UpdateDBInfo(CADOConn *pADOConn);                                // 更新数据
   BOOL GetAllDBInfo(CADOConn *pADOConn);		                             // 获取【整条】信息
   void Copy(CDBDesignDataLib *pData);                                    // 拷贝数据


   CString GetInsertSQL();                                                // 获取插入的SQL语句
   static CDBDesignDataLib * Instance();                                  // 获取（指针）实例
   BOOL UpdateAllDBInfoByID(CADOConn * pADOConn);                         // 更新数据到数据库
   BOOL InsertAllDBInfoByID(CADOConn * pADOConn);                         // 插入数据到数据库
private:
   static std::shared_ptr<CDBDesignDataLib> sm_inst;

public:                                
   __int64	m_nID;                     // 自增ID
   CString  m_strName;                 // 名称
   CString  m_strSavedUserID;          // 用户ID
   CString  m_strSaveTime;             // 保存时间
   CString  m_strData;                 // 保存数据
   CString  m_strLibType;              // 库名称 衣片 辅助线 形状
   CString  m_strPosition;             // 部位
   bool     m_bSymmetricByHor;         // 水平
   bool     m_bSymmetricByPer;         // 垂直
   bool     m_bUseExpre;               // 应用公式
   bool     m_bUseLine;                // 应用辅助线
   bool     m_bMark;                   // 记号文字
   bool     m_bMatchPiece;             // 配套衣片
   int      m_nLength;                 // 身长
   int      m_nBust;                   // 胸围 
   int      m_nShoulderWidth;          // 肩宽
   int      m_nCollarWidth;            // 领宽
   int      m_nCollarHeight;           // 领高
   int      m_nFront;                  // 前胸宽
   int      m_nBehind;                 // 后背宽
   int      m_nMidWidth;               // 中腰宽
   int      m_nMidHeight;              // 中腰高
   int      m_nBellowWidth;            // 下摆宽
   int      m_nBellowHeight;           // 下摆高
   int      m_nShoulderSlanting;       // 肩斜
   int      m_nShoulder;               // 挂肩
   int      m_nShoulderHeight;         // 挂肩收针高
   int      m_nShoudlerHor;            // 挂肩平收
   int      m_nFrontDeep;              // 前领深
   int      m_nBehindDeep;             // 后领深
   int      m_nSleeveLength;           // 袖长
   int      m_nSleeveWidth;            // 袖宽
   CString  m_strTomid;                // 袋距中
   CString  m_strToTop;                // 袋距顶
   CString  m_strWidth1;               // 袋宽1
   CString  m_strWidth2;               // 袋宽2
   CString  m_strHeight1;              // 袋高1
   CString  m_strHeight2;              // 袋高2
   CString  m_strTotalHeight;          // 总袋高
   CString  m_strTotalWidth;           // 总袋宽
};


class CDBDesignDataLibList : public CDataListMid
{
   DECLARE_SERIAL(CDBDesignDataLibList)
public:
   CDBDesignDataLibList();
   ~CDBDesignDataLibList();
   CDBDesignDataLib*  GetItem(int nIndex);
   void    AddItem(CDBDesignDataLib* pItem);
   void    DeleteItem(int nIndex);
   BOOL    DeleteUserByUserID(CADOConn * pADOConn, vector<CString> vecUserID);

   static CDBDesignDataLibList * Instance();		                          //获取（指针）实例
                                                                          //生成表格数据
   MAP_GridCtrl_AllData CreateGridData(const CString & strUserDuty = _T(""));

private:
   static std::shared_ptr<CDBDesignDataLibList> sm_inst;
};
