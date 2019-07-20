#pragma once
#include "DataMid.h"
#include "DBPersonInfo.h"
#include <GdiplusHeaders.h>
#include <afxstr.h>

/********************************************************************
***	<�ļ�>: DBPowerFangAnInfoData.h
***	<˵��>:	Ȩ�޷�����ز���
***	<����>:	anjie
***	<����>:	2019/2/22
*** Copyright (C), 2016-2020, �������. Co., Ltd.
*********************************************************************/
class CDBPowerFangAnInfoData :   public CDataMid
{
public:
   CDBPowerFangAnInfoData(void);
   ~CDBPowerFangAnInfoData(void);
public:
   __int64        m_nID                   ;  //ID
   CString			m_strcFangAnName			;//Ȩ�޷�����
   CString			m_strcFangAnPower			;//����Ȩ��	
   __int64        m_nNum                  ;//���
   virtual void ResetData(void);

   virtual void Copy(CDBPowerFangAnInfoData * pData);

   void ToDBData(CDBPowerFangAnInfoData &);

   BOOL GetAllDBInfo(CADOConn *pADOConn);		//��ȡ����������Ϣ

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
   BOOL GetListFromDB(CADOConn *pADOConn);//�����ݿ��ȡ��������
   static CDBPowerFangAnInfoDataList * Instance();//��ȡ��ָ�룩ʵ��

#ifdef USING_GRIDCTRL_MARK

#endif // USING_GRIDCTRL_MARK

private:
   static std::shared_ptr<CDBPowerFangAnInfoDataList> sm_inst;
};

/*Ա��Ȩ�޷���---anjie-2018-06-03 --end*/