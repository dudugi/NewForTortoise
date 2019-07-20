#pragma once
/*************************************************
// <文件>: DBPinZhongSetting.h
// <说明>: 数据操作类-纱线品种维护表
// <作者>: yangjr
// <日期>: 2019/02/20 16:21:05
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 

#include "DataMid.h"
#include "DBKeyDef.h"
#include <set>

using namespace std;

class CADOConn;

class CDBPinZhongSetting : public CDataMid
{
public:
	CDBPinZhongSetting(void);
	~CDBPinZhongSetting(void);

	virtual void ResetData();

	virtual void Copy(CDBPinZhongSetting * pData);

	void GetAllDataInfo(CADOConn *pADOConn);

   BOOL InsertDBInfo(CADOConn *pADOConn);
   
   BOOL UpdateChenfenByID(CADOConn *pADOConn);
   BOOL DelAllDBInfoByID(CADOConn *pADOConn);		//删除【整条】记录
   //比较修改前后数据，将修改了的数据保存起来
   CString SetDBEquals_Log(CDBPinZhongSetting &pOldData);
	//根据 品种类型 获取数据信息		by WangZY 2018/04/22
	BOOL GetInfoByCate(CADOConn *pADOConn,CString strCate);
public:
	int			m_ID;
   CString		m_cCate;			//纱线品种
   CString		m_cChenfen;			//成份
   CString     m_strfSalePrice;//销售单价 2位小数
   CString		m_cZhiXingBiaoZun;	//执行标准
   CString     m_strfFahuoSunhao;//发货损耗 2位小数
   CString     m_strfShoufaMaxSunhao;//收发最大损耗(kg) 4位小数
   CString     m_strisKoukuan;//超过最大损耗扣款
   CString     m_strfZMDSalePrice;//专卖店销售单价
   CString     m_strfZhekou;//折扣 2位小数
   CString     m_strfKouKuanPrice;//扣款单价
   CString     m_strPWeight      ;//去皮重量    add anjie by 2018/09/27
   CString     m_cProductName;   ///产品名称    add liuhw by 2018/10/08
   CString     m_strBeiLv;       //倍率   两位小数     add anjie by 2018/09/27
   CString     m_strYarnCode;    //纱线类别代号  add liuhw by 2018/11/13
   int         m_iCheckOuterYarn;   //外来纱线 add by lida 2019/03/06
   CString     m_strPrintYarn;      //打印纱线 add anjie by 2019/03/30
   CString     m_strChengbenPrice;  //成本单价 add by lida 2019/06/04
};

class CDBPinZhongSettingList: public CDataListMid
{
public:
   CDBPinZhongSettingList();
	~CDBPinZhongSettingList();
	static CDBPinZhongSettingList * Instance();//获取（指针）实例
      
   void  AddItem(CDBPinZhongSetting* pItem);
   CDBPinZhongSetting*  GetItem(int nIndex);
   void DeleteItem(int iID);   
   CDBPinZhongSetting *GetItemByID(int iID);   
   CDBPinZhongSetting *GetItemByCate(CString strCate);
   void GetYarnCF_Cate_Info(__in CADOConn *pADOConn,__in CString strCate,__out CString &strCF);// 根据纱线类别获取纱线成份 liuhw 2019/03/01
   void GetListFromDB(CADOConn *pADOConn);//从数据库获取链表
   static BOOL UpdateYarnZMJ(CADOConn *pADOConn,std::vector<CString>vecID,double fBeilv,BOOL bBeilv = TRUE);
   BOOL GetFahuoSunhao(__in CADOConn *pADOConn,__in CString strYarnCate,__out CString& strFHSH);
   static BOOL GetYarnOuterFlag(__in CADOConn* pAdo,__in CString strYarnCate);   //读取外带纱线属性
#ifdef USING_GRIDCTRL_MARK
   MAP_GridCtrl_AllData GetMapGridData();
   MAP_GridCtrl_AllData GetMapGridDataBelLv();
   MAP_GridCtrl_AllData GetMapEasyGridDataBelLv(); //获取简易纱线信息 add anjieby 2019/04/15
#endif //USING_GRIDCTRL_MARK   
protected:
	

private:
	static std::shared_ptr<CDBPinZhongSettingList> sm_inst;

};

