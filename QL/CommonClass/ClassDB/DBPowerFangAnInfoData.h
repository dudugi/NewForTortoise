#pragma once
#include "DataMid.h"
#include "DBPersonInfo.h"
#include <GdiplusHeaders.h>
#include <afxstr.h>

/********************************************************************
***	<文件>: DBPowerFangAnInfoData.h
***	<说明>:	权限方案相关操作
***	<作者>:	anjie
***	<日期>:	2019/2/22
*** Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*********************************************************************/
class CDBPowerFangAnInfoData :   public CDataMid
{
public:
   CDBPowerFangAnInfoData(void);
   ~CDBPowerFangAnInfoData(void);
public:
   __int64        m_nID                   ;  //ID
   CString			m_strcFangAnName			;//权限方案名
   CString			m_strcFangAnPower			;//方案权限	
   __int64        m_nNum                  ;//编号
   virtual void ResetData(void);

   virtual void Copy(CDBPowerFangAnInfoData * pData);

   void ToDBData(CDBPowerFangAnInfoData &);

   BOOL GetAllDBInfo(CADOConn *pADOConn);		//获取【整条】信息

   BOOL UpdateToDB(CADOConn * pADo);
};

class CDBPowerFangAnInfoDataList :public CDataListMid
{
public:
   CDBPowerFangAnInfoDataList();
   ~CDBPowerFangAnInfoDataList();

   CDBPowerFangAnInfoData*  GetItem(int nIndex);
   CDBPowerFangAnInfoData*  GetItemByName(CString strUserID);
   int  GetIndexByUserID(CString strUserID);
   void    AddItem(CDBPowerFangAnInfoData* pItem);
   void    DeleteItem(int nIndex);
   void deletebyName(CString strname,CADOConn *pAdo);
   BOOL GetListFromDB(CADOConn *pADOConn);//从数据库获取所有链表
   static CDBPowerFangAnInfoDataList * Instance();//获取（指针）实例

#ifdef USING_GRIDCTRL_MARK

#endif // USING_GRIDCTRL_MARK

private:
   static std::shared_ptr<CDBPowerFangAnInfoDataList> sm_inst;
};

/*员工权限方案---anjie-2018-06-03 --end*/