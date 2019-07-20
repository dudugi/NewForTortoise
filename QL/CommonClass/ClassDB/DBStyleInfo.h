/*************************************************
// <文件>: DBStyleInfo.h
// <说明>: 款式以及对应的纱线信息
// <作者>: wangzl
// <日期>: 2019/01/30 10:26:38
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 
#pragma once

#include "DataMid.h"
#include <map>
class CADOConn;

//任意款款号  对于创建订单时款号为空的数据进行的处理
#define ANY_STYLE_NO		_T("0000")

class CDBStyleInfoData  : public CDataMid
{
	DECLARE_SERIAL( CDBStyleInfoData)//序列化（串行化）需要添加的声明
public:
	int            m_nID;               //自增ID
	COleDateTime   m_oleTimeUpdate;     //更新时间
   CString        m_strTypeName;       //款型
   CString        m_strStyleNo;        //款式号
   CString        m_strStyleName;      //款式名称
   CString        m_strYarnCate;       //纱线类别
	CString        m_strStyleIntro;     //款式说明
	COleDateTime   m_oleTimeCreate;     //订单创建时间
   CString        m_strKsYears;        //年份季度
   int            m_nColorNum;          //配色数
   int            m_nColorSuitNum;     //配色套数
   CString        m_strBasicNum;       //基码
   int            m_nIncreaceNum;      //尺码重量递增
   CString        m_strPinMing;        //品名 yangjr2018/5/11
   // 版房新增款式表数据-----start liuhw 2019/05/08
   CString m_dtExpireTime;    //到期日期
   CString m_strCreator;        //创建人
   CString m_strCreateType;     //创建类型
   CString m_strTheme;          //主题
   CString m_strCusCode;       //客户
   CString m_strCusKuanhao;     //客户款号
   CString m_strProcessStatus;  //工序状态
   CString m_strEdition;        //版本

   CString m_dtMakingOrdTime; //定版日期
   CString m_strMainMaterial;   //主原料
   CString m_strVersionNum;     //版单号
   CString m_strSinglePerson;   //制单人
   CString m_strMainPic;      //款式主图 	by WangZY 2019/05/16
   int     m_iUpOrDownShell;  //上下架 1上架 0下架
   int     m_iFollow;         //关注 1关注 0不关注
   // 版房新增款式表数据-----end liuhw 2019/05/08
   int    m_bIsDeleted;//款式是否删除 yangjr 2019/05/20
   CString  m_strState;//状态
   CString  m_strFangAnName;
   CString  m_strPrority;  //优先级
   CString  m_strNeedleType;  //针型
   CString  m_strModelMainPic;//展示图主图
   int  m_nSortIndex;//展示图主图索引顺序
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

   int      m_nGXSortID       ;//当前工序排序ID
   CString  m_strGxPersonCode ;//工序执行人

   //不在数据库字段中
   CString        m_strActLog;   //操作日志内容的组合
public:
	CDBStyleInfoData();
	~CDBStyleInfoData();
	void ResetData();
	void Copy(CDBStyleInfoData *pData);
	//void Serialize(CArchive& ar);
	BOOL GetAllDBInfo(CADOConn *pADOConn);		//获取【整条】信息
	BOOL InsertAllDBInfoByStyleNo(CADOConn *pADOConn);	//插入【整条】订单新记录
	BOOL UpdateAllDBInfoByStyleNo(CADOConn *pADOConn);	//根据款式号号更新【整条】记录
   BOOL UpdateBasicInfoByStyleNo(CADOConn *pADOConn);// 更新基础信息数据 liuhw 2019/05/22
   BOOL UpdateShellDBInfoByStyleNo(CADOConn *pADOConn,int iShell,CString strStyleNo);// 根据款号更新上下架 liuhw 2019/05/20
   BOOL UpdateFollowDBInfoByStyleNo(CADOConn *pADOConn,int iFollow,CString strStyleNo);// 根据款号更新上下架 liuhw 2019/05/20
   CString GetUpdateSizeInfoToBasicSize(CString strStyleNo,CString strBasicSize);// 更新款式的基本尺码 liuhw 2019/05/26
	BOOL DelAllDBInfoByStyleNo(CADOConn *pADOConn);		//根据款式号号删除【整条】记录
   CString GetDelAllDBInfoByStyleNoSql(CString strStyleNo);
   BOOL IsRepeatStyleNo(CADOConn *pADOConn);//判断款号是否重复
   //比较修改前后数据，将修改了的数据保存起来
   CString SetDBEquals_Log(CDBStyleInfoData &pOldData);

	void DestroyAllLinkInfo(CADOConn *pADOConn);


   BOOL GetAllDBInfoByKuanHao(CADOConn *pADOConn,CString strKuanhao);		//获取【整条】信息 yangjr 2018-3-29
	void Trim();
	static CDBStyleInfoData * Instance();//获取（指针）实例

   //根据款式号设置主图信息  	by WangZY 2019/05/16
   static BOOL UpdateSetNewMainPicByStyleNo(CADOConn *pADOConn,CString strStyleNo, CString strMainPicName);
   static BOOL UpdateSetNewModelMainPicByStyleNo(CADOConn *pADOConn,const CString & strStyleNo,const CString & strMainPicName);
   CString GetDelSqlString(int nID,int nIsDeleted=1);
   CString GetDelSqlByStyleNo(CString strStyleNo,int nIsDeleted);
private:
	static std::shared_ptr<CDBStyleInfoData> sm_inst;
};

class CDBStyleInfoList : public CDataListMid
{
	DECLARE_SERIAL(CDBStyleInfoList)
public:
	CDBStyleInfoList();
	~CDBStyleInfoList();
	CDBStyleInfoData*  GetItem(int nIndex);
	CDBStyleInfoData*  GetItemByStyleNo(CString strStyleNo);//根据款式号号获取获取Item
	int  GetIndexByStyleNo(CString strStyleNo);			//根据订单号获取获取索引
	void    AddItem(CDBStyleInfoData* pItem);
	void    DeleteItem(int nIndex);

	void GetListFromDB(CADOConn *pADOConn);//从数据库获取链表
	int GetStyleSaleCount();	//获取上架款式数目
	void ResetData();

	BOOL GetStyleInfoByStyleNo(CADOConn *pADOConn,CString strStyleNo,__out CDBStyleInfoData& pData);

   BOOL GetKuanShi(CADOConn* pADOConn,vector<CString>& vecKS);

   BOOL GetKS_TreeName_KM(CADOConn* pADOConn,CString strKS,CString& strTreeName,CString& strKM,CString& strKouZhong);   //获取款式分类，款名 add by lida 2018/04/04

   BOOL CheckKsIsExists(CADOConn* pADOConn,CString strKsCode);  //检查款号是否存在

   static BOOL GetBaseSizeAndWeightPercent(CADOConn* pADOConn,CString strKsCode,CString& strBaseSize,CString& strWeightPercent);

   static BOOL UpdateWeightPercent(CADOConn* pADOConn,CString strKsCode,CString& strWeightPercent);

	static CDBStyleInfoList * Instance();//获取（指针）实例
private:
	static std::shared_ptr<CDBStyleInfoList> sm_inst;
	int m_nSaleCount;
};


typedef struct my_ks_info
{
   my_ks_info()
   {
      m_iClassID = -1;          //系列ID    add by lida 2018/05/11
      m_strTypeName = _T("");			//类型名称(来自数据字典)
      m_strStyleNo = _T("");			//款式号
      m_strStyleName = _T("");		//款式名称
      m_strYarnCate = _T("");       //纱线类别
      m_strIngredient = _T("");		//成分
      m_strJinXian = _T("");			//进线
      m_strColorNo = _T("");			//色号
      m_strMatchColor = _T("");		//配色
      m_strStyleIntro = _T("");		//款式说明
      m_strBarCode = _T("");			//商品条码
      m_fLessWeight = -1;			//扣重      
      m_strIntro = _T("")	;			//说明
      m_nDefine = -1;				//备用   <---------------------------预估棉纱用量
      m_strDefine1 = _T("");			//备用1   <--------- 借用为：客户工价, 2018-03-23
      m_strDefine2 = _T("");			//备用2  <--------- 借用为：订货会价格, 2018-03-23
      m_strDefine3 = _T("");			//备用3  <--------- 借用为：会后价格, 2018-03-23
      m_strDefine4 = _T("");			//备用4  <--------- 借用为：吊牌价格, 2018-03-23
      m_strNeedleType = _T("");		//针型
      m_strFindKey  = _T("");			//关键词
      m_fWeight = -1;				//重量
      m_bExec3D = -1;				//是否调用3D模块的标识
      m_dwAttriEx = -1;         //扩展属性
      m_strLingXing = _T("");       //领型
      m_strDiBian = _T("");         //底边
      m_strXiuKou = _T("");         //袖口
      m_strPinMing = _T("");        //品名 yangjr2018/5/11
      m_strHouDaoInfo = _T("");     //后道信息 yangjr2018/5/11
      m_strPinPai = _T("");         //品牌
      m_strKsYears = _T("");        //年份季度
      m_iFanLiFlag = -1;
      m_strGYPerson = _T("");    
      m_strZBPerson = _T("");
      m_strCeLiang = _T("");
      m_strPinLei = _T("");
      m_strMacType = _T("");
      m_strSizeList = _T("");       //尺码备选
      m_strYarnList = _T("");       //纱线备选
      m_strLingxingList = _T("");   //领型备选
      m_strNeedleTypeList = _T("");     //针型备选
      m_strDiBianList = _T("");     //底边备选
      m_strXiuBianList = _T("");    //袖边备选
      m_strMainColor1 = _T("");     //6个配色方案
      m_strMatchColor1 = _T("");
      m_strMainColor2 = _T("");
      m_strMatchColor2 = _T("");
      m_strMainColor3 = _T("");
      m_strMatchColor3 = _T("");
      m_strMainColor4 = _T("");
      m_strMatchColor4 = _T("");
      m_strMainColor5 = _T("");
      m_strMatchColor5 = _T("");
      m_strMainColor6 = _T("");
      m_strMatchColor6 = _T("");
      m_cIsStyle_Warning = _T("1");

      m_dtExpireTime = _T("");    //到期日期
      m_cCreator = _T("");        //创建人
      m_cCreateType = _T("");     //创建类型
      m_cTheme = _T("");          //主题
      m_cCusCode = _T("");       //客户
      m_cCusKuanhao = _T("");     //客户款号
      m_cProcessStatus = _T("");  //工序状态
      m_cEdition = _T("");        //版本
      m_cDesigner = _T("");       //设计师
      m_dtMakingOrdTime = _T(""); //定版日期
      m_cMainMaterial = _T("");   //主原料
      m_cVersionNum = _T("");     //版单号
      m_cCraftsmen = _T("");      //工艺师
      m_cPatternMaker = _T("");   //制版师
      m_cSinglePerson = _T("");   //制单人
   };

   CString GetUpdateSql(BOOL bIgnoreNull = TRUE);     //忽略更新空字段？
  
   CString GetInsertSql();

   int         m_iClassID;          //系列ID    add by lida 2018/05/11
   CString			m_strTypeName;			//类型名称(来自数据字典)
   CString			m_strStyleNo;			//款式号
   CString			m_strStyleName;		//款式名称
   CString         m_strYarnCate;       //纱线类别
   CString			m_strIngredient;		//成分
   CString			m_strJinXian;			//进线
   CString			m_strColorNo;			//色号
   CString			m_strMatchColor;		//配色
   CString			m_strStyleIntro;		//款式说明
   CString			m_strBarCode;			//商品条码
   double			m_fLessWeight;			//扣重      
   CString			m_strIntro;				//说明
   int		   m_nDefine;				//备用   <---------------------------预估棉纱用量
   CString			m_strDefine1;			//备用1   <--------- 借用为：客户工价, 2018-03-23
   CString			m_strDefine2;			//备用2  <--------- 借用为：订货会价格, 2018-03-23
   CString			m_strDefine3;			//备用3  <--------- 借用为：会后价格, 2018-03-23
   CString			m_strDefine4;			//备用4  <--------- 借用为：吊牌价格, 2018-03-23
   CString        m_cIsStyle_Warning; //该款式是否预警 liuhw 2019/1/4

   CString			m_strNeedleType;		//针型
   CString			m_strFindKey;			//关键词
   double				m_fWeight;				//重量
   int				   m_bExec3D;				//是否调用3D模块的标识
   int				m_dwAttriEx;         //扩展属性
   CString			m_strLingXing;       //领型
   CString			m_strDiBian;         //底边
   CString			m_strXiuKou;         //袖口
   CString			m_strPinMing;        //品名 yangjr2018/5/11
   CString			m_strHouDaoInfo;     //后道信息 yangjr2018/5/11
   CString        m_strPinPai;         //品牌
   CString        m_strKsYears;        //年份季度
   int            m_iFanLiFlag;        //返利统计标记 0不统计，1统计
   CString        m_strGYPerson;       //工艺师
   CString        m_strZBPerson;       //制版师
   CString        m_strCeLiang;        //测量
   CString        m_strPinLei;         //品类，衣服、裤子
   CString        m_strMacType;        //机型
   CString        m_strSizeList;       //尺码备选
   CString        m_strYarnList;       //纱线备选
   CString        m_strLingxingList;   //领型备选
   CString        m_strNeedleTypeList;     //针型备选
   CString        m_strDiBianList;     //底边备选
   CString        m_strXiuBianList;    //袖边备选

   CString        m_strMainColor1;     //6个配色方案
   CString        m_strMatchColor1;
   CString        m_strMainColor2;
   CString        m_strMatchColor2;
   CString        m_strMainColor3;
   CString        m_strMatchColor3;
   CString        m_strMainColor4;
   CString        m_strMatchColor4;
   CString        m_strMainColor5;
   CString        m_strMatchColor5;
   CString        m_strMainColor6;
   CString        m_strMatchColor6;

   CString        m_dtExpireTime;    //到期日期
   CString        m_cCreator;        //创建人
   CString        m_cCreateType;     //创建类型
   CString        m_cTheme;          //主题
   CString        m_cCusCode;       //客户
   CString        m_cCusKuanhao;     //客户款号
   CString        m_cProcessStatus;  //工序状态
   CString        m_cEdition;        //版本
   CString        m_cDesigner;       //设计师
   CString        m_dtMakingOrdTime; //定版日期
   CString        m_cMainMaterial;   //主原料
   CString        m_cVersionNum;     //版单号
   CString        m_cCraftsmen;      //工艺师
   CString        m_cPatternMaker;   //制版师
   CString        m_cSinglePerson;   //制单人
}s_my_ks_info;