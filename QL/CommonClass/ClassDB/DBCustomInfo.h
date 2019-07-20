
#pragma once

/*************************************************
// <文件>: DBCustomInfo.h
// <说明>: 客户信息表
// <作者>: wangzl
// <日期>: 2019/02/22
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 

#include "DataMid.h"
class CADOConn;

#include "DBKeyDef.h"
#include "DBKeyDef_V.h"
#include "DBKeyDef_Cust.h"

typedef enum {
   Enum_Customer_None = 0, //默认不
   Enum_Customer_ZanBuHeZuo, //客户状态值为暂不合作
	Enum_Customer_FinancialLedger, //客户总账明细的客户
	Enum_Customer_OrderOutWork,	//订单查询:委外加工
	Enum_Customer_JinZhiOrder,	//2017/08/11 zhangt 禁止下单客户（禁止下单和暂不合作）
}Enum_Customer_State;//客户状态枚举值 yangjr 2017-7-26

class CDBCustomInfoData  : public CDataMid
{
	DECLARE_SERIAL( CDBCustomInfoData)//序列化（串行化）需要添加的声明
public:
	int					m_nID;					//自增ID
	COleDateTime		m_oleUpdateTime;		//更新日期
	CString				m_strCate;				//分类
	CString				m_strCusCate;			//客户分类---->从数据字典筛选 客户分类选项
	CString				m_strCusCode;			//客户编码
	CString				m_strCusName;			//客户名称
	CString				m_strCusAbbrevName;		//客户简称
	CString				m_strCusAddr;			//客户地址
	CString				m_strCusPerson;			//客户联系人
	CString				m_strCusPhone;			//客户电话
	CString				m_strCusFax;			//客户传真
	CString				m_strMobile;			//客户手机
	CString				m_strWeChat;			//客户微信
	CString				m_strRemark;			//备注
	CString				m_strVenWeb;			//我的下单平台
	CString				m_strVenCode;			//我的下单帐号
	CString				m_strVenPwd;			//我的下单密码
	CString				m_strCusPwd;			//登录密码
	double				m_fArrears;				//期初余额
	double				m_fDeposit;				//保证金
	double				m_fLimit;				//欠款上限
	CString				m_strProvince;			//省
	CString				m_strCity;				//市
	CString				m_strArea;				//区号
	CString				m_strState;				//状态
	int					m_nDeliveryDays;		//交货天数
	int					m_nNum;					//件数
	int					m_nLoss;				//损耗
	CString				m_strEMS;				//快递
	CString				m_strParrentCode;		//上级代号
	CString				m_strClerkCode;			//业务员编号
	CString				m_strRebate;			//返点
	CString				m_strWorkDoc;			//默认加工单
	CString				m_strTag;				//默认吊牌
	CString				m_strDeliveryDoc;		//默认发货单
	CString				m_strDepotPos;			//仓位
	CString				m_strSign;				//签名
	CString				m_strCusUnit;			//单位
	int					m_nCusLv;				//等级
   CString				m_strNewCusName;			//加拼音的客户名称
   int               m_iTreeGroupID;      //地区分组ID
   int					m_iJijiaType;				//销售价计价方式：0：表示按折扣；1表示按重量 yangjr 2018/4/18
   double             m_fAddinPrice;       //零售价加价        add by lida 2018/05/24
   int               m_bPrintDiaoPai;     //是否打印吊牌    add by lida 2018/05/24
   int               m_bPrintYuE;         //是否打印余额    add by lida 2018/05/24
   double            m_fZMZheKou; //专卖折扣 yangjr 2018/8/7
   CString           m_strSalesID;  //业务员ID add by lida 2018/09/01
public:
	CDBCustomInfoData();
	~CDBCustomInfoData();
	void ResetData();
	void Trim();

	void Copy(CDBCustomInfoData *pData);
	void Serialize(CArchive& ar);
	BOOL GetAllDBInfo(CADOConn *pADOConn);			//获取【整条】信息
	BOOL InsertAllDBInfo(CADOConn *pADOConn);		//插入【整条】订单新记录
	BOOL UpdateAllDBInfoByID(CADOConn *pADOConn);	//根据账户更新【整条】记录
	BOOL DelAllDBInfoByID(CADOConn *pADOConn);		//根据账户删除【整条】记录
	static CDBCustomInfoData * Instance();			//获取（指针）实例
   BOOL GetAllDBInfoByCusCode(CADOConn *pADOConn,CString strCusCode);//根据客户编号获取【整条】信息 yangjr 2018-3-27
   BOOL UpdateStorageZMJ(CADOConn *pADOConn);//根据客户编号更新对应客户的专卖价 yangjr 2018/8/22
private:
	static std::shared_ptr<CDBCustomInfoData> sm_inst;
};

class CDBCustomInfoList : public CDataListMid
{
	DECLARE_SERIAL(CDBCustomInfoList)
public:
	CDBCustomInfoList();
	~CDBCustomInfoList();
	CDBCustomInfoData*  GetItem(int nIndex);
	CDBCustomInfoData*  GetItemByCustomID(CString strCustomID);	//依据客户ID获取对应的Item
   CDBCustomInfoData*  GetItemByCustomName(CString strCustomName);	//依据客户名称获取第一个对应的Item 
	int  GetIndexByCustomID(CString strCustomID);				//根据订单号获取获取索引
	void AddItem(CDBCustomInfoData* pItem);
	void DeleteItem(int nIndex);
	void GetListFromDB(CADOConn *pADOConn);						//从数据库获取链表
	static CDBCustomInfoList * Instance();						//获取（指针）实例

	static void GetCustmerInfo(CADOConn *pADOConn,CDBCustomInfoData* pData);

   //判断对应销售人员是否有客户 Yangjr 2018-9-1
   BOOL IsSalesHaveCus(CADOConn *pADOConn,CString strSalesID);

#ifdef USING_GRIDCTRL_MARK

   //strSaleID:业务员ID，bLimitSale:是否开启限制（限制查看当前业务员的客户）
	MAP_GridCtrl_AllData CreateGridData(std::vector<int> treeGroupIDLst,CString strSaleID,BOOL bLimitSale = FALSE);
   MAP_GridCtrl_AllData CreateGridData(std::vector<int> treeGroupIDLst,CString strSaleID,CString strCusName,BOOL bLimitSale = FALSE);

   MAP_GridCtrl_AllData CreateGridData(CString strSaleID,BOOL bLimitSale = FALSE);
   BOOL CreateDropPopGridData(const CDBCustomInfoData* pData,MAP_GridCtrl_RowData& row_data);

   BOOL CreateGridData(const CDBCustomInfoData* pData,MAP_GridCtrl_RowData& row_data);
	
	//生成一条空的行数据		by WangZY 2017/08/24
	BOOL GetEmptyRowData(__out MAP_GridCtrl_RowData &mapEmptyRowData);
	
	//批量提交数据修改		by WangZY 2017/08/24
	BOOL SaveMultiModifyData(__in CADOConn *pADOConn, __in MAP_GridCtrl_AllData &mapAddData,
		__in MAP_GridCtrl_AllData &mapModifyData, __in MAP_GridCtrl_AllData &mapDeleteData,
		__in CString strMaker);

	//获取供应商信息, add by lida 2017/06/15
	MAP_GridCtrl_AllData CreateGridData_Cumstomer(CADOConn *pADOConn,CString strFilter,Enum_Customer_State stateType);
	//获取供应商信息1, add by lida 2017/07/03
   // 增加包含简称接口 默认包含 2018-6-11 wangzl
	MAP_GridCtrl_AllData CreateGridData_Cumstomer_1(CADOConn *pADOConn,BOOL bHasAbbreviation = TRUE);
	//获取供应商信息2，add by lida 2017/08/29 -- 订单批量录入
	MAP_GridCtrl_AllData CreateGridData_Cumstomer_OrderEntry(CADOConn *pADOConn,__out map<CString/*CusCode*/,CString/*iDays*/>& map_CusDays);

   //获取对应客户类型的且排除暂不合作的所有客户数据 yangjr 2017-12-12
   MAP_GridCtrl_AllData CreateGridData_CumstomerByCate(CADOConn *pADOConn,CString strFilterCusCate);

   CString GetQianKuanJinEr(CADOConn *pADOConn,CString cusCode);//获取当前客户的累积欠款金额 yangjr 2017-07-28
   //获取当前欠供应商的金额 yangjr 2018/1/9
   CString GetQianGongYingShangKuanJinEr(CADOConn *pADOConn,CString cusCode);

   CString GetCusQKLimit(CADOConn *pADOConn,CString cusCode);	//获取当前客户的欠款上限 add by lida 2017/08/09
   CString GetNewCusCode(CADOConn* pADOConn);					//生成最新一个客户编号，根据上次保存的客户编码
   //sqr方式 获取当前客户的累积欠款金额 yangjr 2018-4-9
   CString GetNewQianKuanJinEr(CADOConn *pADOConn,CString cusCode);

   BOOL GetKeHuDuiZhang(CADOConn* pADOConn,CString strBegTime,CString strEndTime,MAP_GridCtrl_AllData& map_all_data);

   BOOL GetCusPrintFlag(CADOConn* pADOConn,CString strCusCode,__out int& iPrintDp,__out int& iPrintYE); //读取客户打印标识


#endif // USING_GRIDCTRL_MARK
   void GetAllDBInfoCusName_BasicInfo(vector<CString> &vecCusName);// 获取所有的客户名称，基础信息专用 liuhw 2019/05/21

private:
	static std::shared_ptr<CDBCustomInfoList> sm_inst;
};

//客户excel导入
typedef struct my_customer_info
{
   my_customer_info()
   {
      m_nID = -1;				
      m_nDeliveryDays = -1;
      m_nCusLv = -1;			
      m_iTreeGroupID = -1; 
      m_iJijiaType = -1;		
      m_bPrintDiaoPai = -1;
      m_bPrintYuE = -1;    
      m_fZMZheKou = -1;    
      m_fAddinPrice = -1;  
      m_fArrears = _T("");		
      m_fDeposit = -1;		
      m_fLimit = -1;			
      m_oleUpdateTime  = COleDateTime::GetCurrentTime();
      m_strCate = _T("");			
      m_strCusCate = _T("");		
      m_strCusCode = _T("");		
      m_strCusName = _T("");		
      m_strCusAddr = _T("");		
      m_strCusPerson = _T("");	
      m_strCusPhone = _T("");		
      m_strCusFax = _T("");		
      m_strMobile = _T("");		
      m_strRemark = _T("");		
      m_strVenWeb = _T("");		
      m_strCusPwd = _T("");		
      m_strProvince = _T("");		
      m_strCity = _T("");			
      m_strEMS = _T("");			
      m_strClerkCode = _T("");	
      m_strSalesID = _T("");
      m_strCusAbbrevName = _T("");
   };

   CString GetUpdateSql(BOOL bIgnoreNull = TRUE);
   

   CString GetInsertSql();
   

   int            m_nID;					//自增ID
   int            m_nDeliveryDays;		//交货天数
   int            m_nCusLv;				//等级
   int            m_iTreeGroupID;      //地区分组ID
   int            m_iJijiaType;			  //销售价计价方式：0：表示按折扣；1表示按重量 yangjr 2018/4/18  
   int            m_bPrintDiaoPai;        //是否打印吊牌    add by lida 2018/05/24
   int            m_bPrintYuE;            //是否打印余额    add by lida 2018/05/24
   double         m_fZMZheKou;            //专卖折扣 yangjr 2018/8/7
   double         m_fAddinPrice;          //零售价加价        add by lida 2018/05/24
   CString         m_fArrears;				//期初余额
   double         m_fDeposit;				//保证金
   double         m_fLimit;				   //欠款上限
   COleDateTime   m_oleUpdateTime;		//更新日期
   CString        m_strCate;				//分类
   CString        m_strCusCate;			//客户分类---->从数据字典筛选 客户分类选项
   CString        m_strCusCode;			//客户编码
   CString        m_strCusAbbrevName;  //客户简称
   CString        m_strCusName;			//客户名称
   CString        m_strCusAddr;			//客户地址
   CString        m_strCusPerson;			//客户联系人
   CString        m_strCusPhone;			//客户电话
   CString        m_strCusFax;			//客户传真
   CString        m_strMobile;			//客户手机
   CString        m_strRemark;			//备注
   CString        m_strVenWeb;			//我的下单平台
   CString        m_strCusPwd;			//登录密码
   CString        m_strProvince;			//省
   CString        m_strCity;				//市 
   CString        m_strEMS;				//快递
   CString        m_strClerkCode;			//业务员编号
   CString        m_strSalesID;        //业务员ID add by lida 2018/09/01 
}s_my_customer_info;
