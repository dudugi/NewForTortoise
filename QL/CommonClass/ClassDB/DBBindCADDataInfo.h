#pragma once
#include "DataMid.h"

class CADOConn;

/********************************************************************
***	<文件>: DBBindCADDataInfo.h
***	<说明>:	CAD绑定设置数据操作类
***	<作者>:	anjie
***	<日期>:	2019/5/15
*** Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*********************************************************************/

class CDBBindCADDataInfo :
   public CDataMid
{
   //序列化
    DECLARE_SERIAL(CDBBindCADDataInfo)
public:
   CString m_strAppPath           ;//主程序路径
   CString m_strAppName           ;//软件名称
   CString m_strFileSuffix        ;//文件后缀
   CString m_strFileType          ;//文件类型
public:
   CDBBindCADDataInfo(void);
   ~CDBBindCADDataInfo(void);
    void Serialize(CArchive& ar);
    void Copy(CDBBindCADDataInfo *pData);
};

class CDBBindCADList :
   public CDataListMid
{
   DECLARE_SERIAL(CDBBindCADList)
public:
   CDBBindCADList(void);
   ~CDBBindCADList(void);
   void Serialize(CArchive& ar);

   void AddItem(CDBBindCADDataInfo *pItem);
   BOOL DeleteItemByPath(CString strPath);;
   int IsHasBind(CString strPath);
   CDBBindCADDataInfo* GetItem( int nIndex );
   void DeleteItem( int nIndex );
   BOOL operator = (CDBBindCADList *pLst)
   {
      this->RemoveAll();
      for (int nIndex =0;nIndex<pLst->GetCount();nIndex++)
      {
         auto pAuto = pLst->GetItem(nIndex);
         if (pAuto != NULL)
         {
            AddItem(pAuto);
         }
      }
      return TRUE;
   }

#ifdef USING_GRIDCTRL_MARK
   void CreateGridData(MAP_GridCtrl_AllData &mapAllData);
#endif // USING_GRIDCTRL_MARK
};
