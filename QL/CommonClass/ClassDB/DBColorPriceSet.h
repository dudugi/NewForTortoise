#pragma once
/*************************************************
// <文件>: DBColorPriceSet.h
// <说明>: 数据操作类-价格设置数据表
// <作者>: yangjr
// <日期>: 2017-7-13 15:59:15
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 

#include "DataMid.h"
#include <map>
#include <vector>

class CADOConn;
class CDBDataColorPriceSet :public CDataMid
{
   DECLARE_SERIAL( CDBDataColorPriceSet)//序列化（串行化）需要添加的声明
public:
   CDBDataColorPriceSet(void);
   ~CDBDataColorPriceSet(void);
public:
   CString		m_str_dDate      ;  //日期
   CString		m_str_iSunhao    ;  //损耗
   CString		m_str_iSalePrice ;  //销售单价
   CString		m_str_iPrice     ;  //单价
   CString		m_str_cDaihao    ;  //品种代号
   CString		m_str_cCate      ;  //品种
   CString		m_str_cCusCode   ;  //客户编号
   CString		m_str_ID         ;  //ID
   CString		m_str_cCusCate   ;  //客户类型
   CString		m_str_cCusName   ;  //客户全称
   //CString		m_str_cCusAbbName;  //客户简称
   //CString		m_str_vCusAbbName;  //客户
   CString		m_str_fZMDSalePrice;  //专卖店零售单价
   CString		m_str_fZhekou;  //折扣
	CString		m_str_cChenfen;	//成份
   CString     m_str_fBeiLv ;   //倍率    add anjie by 2018/10/25

public:
   static CDBDataColorPriceSet * Instance();//获取（指针）实例
   BOOL GetAllDBInfo(CADOConn *pADOConn);		//获取【整条】信息 

   void ResetData();
   void Copy(CDBDataColorPriceSet *pData);
   void Serialize(CArchive& ar);
   //比较修改前后数据，将修改了的数据保存起来
   CString SetDBEquals_Log(CDBDataColorPriceSet &pOldData);
#ifdef USING_GRIDCTRL_MARK
   void ToGridDB(MAP_GridCtrl_RowData *pRowData); //表格转换为DB数据 liuhw 2018/09/15
#endif // USING_GRIDCTRL_MARK
	//根据品种的客户获取价格信息		by WangZY 2018/04/22
	BOOL GetInfoByCateAndCusCode(CADOConn *pADOConn,
		CString strColorCate,CString strCusCode);
private:
   static std::shared_ptr<CDBDataColorPriceSet> sm_inst;
};

class CDBDataColorPriceSetInfoList : public CDataListMid
{
   DECLARE_SERIAL(CDBDataColorPriceSetInfoList)

public:
   CDBDataColorPriceSetInfoList();
   ~CDBDataColorPriceSetInfoList();

   //add by lida 2018/09/20 获取客户成分
   CString GetChengfen(CADOConn* pADOconn,CString strCusCode,CString strSehao);
   void AddItem(CDBDataColorPriceSet* pItem);
   //add by lida 2017/08/29 获取色号单价，订单批量录入相关
   CString GetClrPriceDataInfo(CADOConn* pADOConn,CString strSehao,CString strCusCode);

   static CDBDataColorPriceSetInfoList * Instance();		//获取（指针）实例  
   BOOL GetListFromDB(CADOConn * pADOConn);   
   static std::shared_ptr<CDBDataColorPriceSetInfoList> sm_inst;
   BOOL DeleteOneByID(CADOConn *pADOConn,CString strID);
#ifdef USING_GRIDCTRL_MARK
   BOOL GetDataFromDB(CADOConn *pADOConn,MAP_GridCtrl_AllData &allData);
   BOOL UpdateOneByID(CADOConn *pADOConn,const MAP_GridCtrl_RowData &oneRow);
   BOOL InsertOne(CADOConn *pADOConn,const MAP_GridCtrl_RowData &oneRow); 
	//获取一行空行数据		by WangZY 2017/08/22
	BOOL GetEmptyRowData(__out MAP_GridCtrl_RowData &mapEmptyRowData);

	//批量提交数据修改		by WangZY 2017/08/23
	BOOL MultiModifyData(__in CADOConn *pADOConn, __in MAP_GridCtrl_AllData &mapAddData,
		__in MAP_GridCtrl_AllData &mapModifyData, __in MAP_GridCtrl_AllData &mapDeleteData,
		__in CString strMaker);
	
	//生成网格数据的接口		by WangZY 2017/08/27
	MAP_GridCtrl_AllData CreateGridData();

#endif  // USING_GRIDCTRL_MARK
   //对应客户、品种代码在价格设置表中是否存在不等于对应id的相同数据 yangjr 2017-8-9
   BOOL IsExitSameDataModify(CADOConn *pADOConn,CString strCusCode,CString strDaihao,CString strID,CString strPinZhong);
   //对应客户、品种代码在价格设置表中是否存在相同数据 yangjr 2017-8-9
   BOOL IsExitSameDataAdd(CADOConn *pADOConn,CString strCusCode,CString strDaihao,CString strPinZhong);
   //float GetSalePrice(CString m_str_cCusCode,CString cDaiHao);
   //根据(客户+品种+代号)、(客户+品种)、(品种+代号)、来获取价格，找不到返回NULL yangjr 2018/4/22
   CDBDataColorPriceSet *GetPriceData( CString str_cCusCode,CString strCate,CString cDaiHao);
   BOOL GetPriceDataNew(CString strCate,CString strCf,CString& strPrice);
   //CString GetYarnSalePrice(CString strCusCode,CString strCate);
   BOOL GetTodayDate(CADOConn *pADOConn,CString &date);//获取当前时间年-月-日yangjr 2017-8-9
   //add by lida 2017/07/28
   //获取品种代号 -- 订单排名分析
   vector<CString>	GetDaiHao(CADOConn *pADOConn);
   static BOOL UpdateYarnZMJ(CADOConn *pADOConn,std::vector<CString>vecID,double fBeilv,BOOL bBeilv = TRUE);
private:
#ifdef USING_GRIDCTRL_MARK
   void InsertRowData(CString strFiedID,CString strValue,MAP_GridCtrl_RowData& map_row_data,ENUM_FIELDTYPE_DATA nFieldType= CB_enum_FieldData_CString,ENUM_FIELDTYPE_CONTROL nFieldTypeCtr= CB_enum_FieldCtrl_Text);
#endif  // USING_GRIDCTRL_MARK
   CDBDataColorPriceSet*  GetItem(int nIndex);			//根据索引获取Item
   void DeleteItem(int nIndex); 
  
};


typedef struct my_ColorPriceSet
{
   my_ColorPriceSet()
   {
      ResetData();
   };

   void ResetData();
   CString GetInsertSql();
   CString GetUpdateSql();
   CString GetLog();
   void CheckData();

   CString		m_str_ID         ;  //ID
   CString		m_str_dDate      ;  //日期
   CString		m_str_iSunhao    ;  //损耗
   CString		m_str_iSalePrice ;  //销售单价
   CString		m_str_iPrice     ;  //单价
   CString		m_str_cDaihao    ;  //品种代号
   CString		m_str_cCate      ;  //品种
   CString		m_str_cCusCode   ;  //客户编号
   CString		m_str_cCusName   ;  //客户名称
   CString		m_str_fZMDSalePrice;  //专卖店零售单价
   CString		m_str_fZhekou;  //折扣
   CString		m_str_cChenfen;	//成份
   CString      m_str_fBeiLv ;   //倍率    add anjie by 2018/10/25
}s_my_ColorPriceSet;
