#pragma once
/*************************************************
// <文件>: DBStyleInfo_V.h
// <说明>: 数据库操作类-款式视图
// <作者>: yangjr
// <日期>: 2019/02/20 16:34:46
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 
#include "DataMid.h"
#include "DBStyleInfo.h"

using namespace std;

class CADOConn;

typedef struct filter_data
{
   int iClassID;           //系列ID, ID=-1时显示全部的系列
   CString strClassName;   //系列名称
   CString strKsYears;     //年份季度
   CString strKsPinPai;    //品牌
   CString strKsCode;      //款号 -- 款式修改界面用

   //更改款式系列时，将款式的信息带回，刷新款式系列树信息
   int iClassID_old_Modify;   
   int iClassID_new_Modify;
   CString strKsCode_Modify;


   CString strDateType;      //日期类型   	by WangZY 2019/05/17
   CString strDateBegin;     
   CString strDateEnd;
   CString strTheme;          //主题   by WangZY 2019/05/17 
   CString strStyleType;      //款型   by WangZY 2019/05/17 
   CString strClothType;      //品类   by WangZY 2019/05/17 
   CString strFinishState;    //完成情况   by WangZY 2019/05/17
   CString strCusId;          //客户ID	by WangZY 2019/05/17
   CString strGongyishiId;    //工艺师ID  by WangZY 2019/05/17
   CString strShejishiId;     //设计师ID  by WangZY 2019/05/17
   CString strZhibanshiId;    //制版师ID   by WangZY 2019/05/17
   CString strShell;          // 上下架 liuhw 2019/05/22
   CString strStyleFollow;    // 关注 liuhw 2019/05/22
   CString strVersion;//版本
   CString strNeedle;   //针型

   enum{
      en_Null= 0,//无类型筛选
      en_ToBeProcessed ,//待处理
      en_PendingSubmission,//待提交
      en_Completed,//已完成
   };

   int     nFilterType;       //过滤的类型  待处理 待提交 已完成
   int     nCurGxSortID;     //当前工序ID
   CString strMainRawMaterial;//主原料 yangjr 2019/07/10

   filter_data()
   {
      iClassID = 0;
      strClassName = _T("");
      strKsYears = _T("");
      strKsPinPai = _T("");
      strKsCode = _T("");

      iClassID_old_Modify = 0;
      iClassID_new_Modify = 0;
      strKsCode_Modify = _T("");
      nFilterType = en_Null;
      nCurGxSortID = 0;
      strMainRawMaterial = _T("");
   };

}s_filter_data;

//wangzl 款式视图类 2017/7/14 
class CDBStyleInfoData_V :
	public CDataMid
{
public:
	CDBStyleInfoData_V(void);
	~CDBStyleInfoData_V(void);

	virtual void ResetData();

	virtual void Copy(CDBStyleInfoData_V * pData);

	void ToDBData(CDBStyleInfoData &);
   //仅拷贝基础信息
   void CopyBasicInfo(CDBStyleInfoData_V * pData);

	BOOL GetAllDBInfo(CADOConn *pADOConn);		//获取【整条】信息

	//只获取必要的字段信息		by WangZY 2018/05/29
	BOOL GetAllDBInfoWithNecessaryField(CADOConn *pADOConn );
public:
	int				m_nID				;//
	COleDateTime	m_oleUpdateTime		;//
	CString			m_strTypeName		;//
	CString			m_strStyleNo		;//
	CString			m_strStyleName		;//
   CString        m_strYarnCate;    //纱线类别
	CString			m_strStyleIntro		;//
	COleDateTime	m_oledtCreatTime	;//
   CString        m_strKsYears;        //年份季度

   CString        m_strCraftsmen;    //工艺师
   CString        m_strPatternMaker;    //制版师
   CString        m_strClassType;   //衣服、裤子

   // 版房新增款式表数据-----start liuhw 2019/05/08
   CString        m_dtExpireTime;    //到期日期
   CString        m_strCreator;        //创建人
   CString        m_strCreateType;     //创建类型
   CString        m_strTheme;          //主题
   CString        m_strCusCode;       //客户
   CString        m_strCusKuanhao;     //客户款号
   CString        m_strProcessStatus;  //工序状态
   CString        m_strEdition;        //版本

   CString        m_strDesigner;       //设计师
   CString        m_dtMakingOrdTime; //定版日期
   CString        m_strMainMaterial;   //主原料
   CString        m_strVersionNum;     //版单号
   CString        m_strSinglePerson;   //制单人
   int            m_nCheckState     ;//检出检入状态
   CString        m_strCheckPerson  ;//检出检入操作人

   int            m_nVersionState   ;
   CString        m_strVersionPerson;

   int            m_iUpOrDownShell;  //上下架 1上架 0下架
   int            m_iFollow;         //关注 1关注 0不关注

   CString        m_strMainPic;      //款式主图 

   // 版房新增款式表数据-----end liuhw 2019/05/08
   CString			m_strPinMing			;//品名 yangjr2018/5/11
   int    m_bIsDeleted;//款式是否删除 yangjr 2019/05/20

   int           m_nGXSortID       ;
   CString       m_strGXPersonCode ;
   CString       m_strState        ;
   CString       m_strFangAnName   ;
   CString  m_strPrority;  //优先级
   CString  m_strNeedleType;  //针型
   CString  m_strStyleDescription;  //描述
   CString  m_strModelMainPic;//展示图主图
   int m_nSortIndex;
   CString  m_strBrand        ;//品牌
   CString  m_strCustomField1 ;//自定义字段1 
   CString  m_strCustomField2 ;//自定义字段2 
   CString  m_strCustomField3 ;//自定义字段3 
   CString  m_strCustomField4 ;//自定义字段4 
   CString  m_strCustomField5 ;//自定义字段5 
   CString  m_strCustomField6 ;//自定义字段6 
   CString  m_strCustomField7 ;//自定义字段7 
   CString  m_strCustomField8 ;//自定义字段8 
   CString  m_strCustomField9 ;//自定义字段9 
   CString  m_strCustomField10;//自定义字段10

   double   m_dTotalCost;     //总成本
   double   m_dTotalOffer;    //总报价

   CString  m_strHelpSeekerID; //如果目前在求助状态，则为求助人ID，否则为空字符串 by duchen

   //标记，不在数据库中
   BOOL  m_bCostAndOfferChanged; //成本和价格是否被修改
};

class CDBStyleInfoList_V:public CDataListMid
{
public:
	CDBStyleInfoList_V();
	~CDBStyleInfoList_V();

	CDBStyleInfoData_V*  GetItem(int nIndex);
	CDBStyleInfoData_V*  GetItemByStyleNo(CString strStyleNo);//根据款式号号获取获取Item
   CDBStyleInfoData_V*  GetItemByID(int nStyleID);//根据款式号号获取获取Item
	int  GetIndexByStyleNo(CString strStyleNo);			//根据订单号获取获取索引
	void    AddItem(CDBStyleInfoData_V* pItem);
	void    DeleteItem(int nIndex);

    BOOL GetStyleInfo(CADOConn* pADOConn,CString strKuanhao,__out CDBStyleInfoData_V* pObj);
   
   //根据款号获取修改时间		by WangZY 2018/08/31
   static BOOL GetStyleUpdateDateByStyleNo(__in CADOConn* pADOConn,
      __in CString strKuanhao, __out CString &strDate);


   enum ks_show_type
   {
      ks_type_show_all = -1,     //显示所有款式
      ks_type_show_no_class = 0,   //显示未有系列款式
   };

	//只获取必要的字段信息		by WangZY 2018/05/29
	BOOL GetListFromDBWithNecessaryField(CADOConn *pADOConn);//从数据库获取所有链表

   //根据ID号获取【整条】信息 yangjr2017-9-20
   BOOL GetListFromDBByID(CADOConn *pADOConn,CString strID,CDBStyleInfoData_V &data);
	static CDBStyleInfoList_V * Instance();//获取（指针）实例

   static BOOL GetStyleCostAndOffer(CADOConn* pAdo,CDBStyleInfoData_V *data);  //重新获取款式的成本及报价

#ifdef USING_GRIDCTRL_MARK
	MAP_GridCtrl_AllData CreatrGridData();
   MAP_GridCtrl_AllData CreatrGridData_Kuanhao();

   
   MAP_GridCtrl_RowData GetRowData(CDBStyleInfoData_V* pData);

	//生成一条空的行数据		by WangZY 2017/08/24
	BOOL GetEmptyRowData(__out MAP_GridCtrl_RowData &mapEmptyRowData);

	//批量提交数据修改		by WangZY 2017/08/24
	BOOL SaveMultiModifyData(__in CADOConn *pADOConn, __in MAP_GridCtrl_AllData &mapAddData,
		__in MAP_GridCtrl_AllData &mapModifyData, __in MAP_GridCtrl_AllData &mapDeleteData,
		__in CString strMaker);

#endif // USING_GRIDCTRL_MARK

private:
	static std::shared_ptr<CDBStyleInfoList_V> sm_inst;

};

