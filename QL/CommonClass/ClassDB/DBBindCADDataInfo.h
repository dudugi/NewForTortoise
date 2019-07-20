#pragma once
#include "DataMid.h"

class CADOConn;

/********************************************************************
***	<�ļ�>: DBBindCADDataInfo.h
***	<˵��>:	CAD���������ݲ�����
***	<����>:	anjie
***	<����>:	2019/5/15
*** Copyright (C), 2016-2020, �������. Co., Ltd.
*********************************************************************/

class CDBBindCADDataInfo :
   public CDataMid
{
   //���л�
    DECLARE_SERIAL(CDBBindCADDataInfo)
public:
   CString m_strAppPath           ;//������·��
   CString m_strAppName           ;//�������
   CString m_strFileSuffix        ;//�ļ���׺
   CString m_strFileType          ;//�ļ�����
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
