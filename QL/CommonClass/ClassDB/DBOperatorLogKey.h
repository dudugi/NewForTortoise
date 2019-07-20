#pragma once
//pdm 日志操作类 add by lida 2018/03/07
using namespace std;
#define Log_Type_Num		12		//操作类型 数量
#define Log_Cate_Num		77	//表名	数量
#define TABLE_NAME_MAX_LEN	50

typedef enum Em_WorkLog_Type		//操作类型
{   
   enLog_Type_Del = 0,		//删除		0
   enLog_Type_Upadate,		//更新		1
   enLog_Type_Add,			//添加		2
   enLog_Type_Login,		//登入		3
   enLog_Type_Logout,		//退出		4
   enLog_Type_UpLoad,		//上传		5
   enLog_Type_DownLoad,	//下载		6
   enLog_Type_Search,		//查询		7
   enLog_Type_View,		//查看		8
   enLog_Type_Print,		//打印		9
   enLog_Type_Export,		//导出		10
   enLog_Type_Inport		//导入		11
};

static TCHAR g_LogType[Log_Type_Num][TABLE_NAME_MAX_LEN] = {
   {_T("删除")},
   {_T("更新")},
   {_T("添加")},
   {_T("登入")},
   {_T("退出")},
   {_T("上传")},
   {_T("下载")}, 
   {_T("查询")},
   {_T("查看")},
   {_T("打印")},
   {_T("导出")},
   {_T("导入")},
};

typedef enum Em_WorkLog_Cate		//表名
{
   enLog_Cate_TableName_Null = 0,
   enLog_Cate_SQL_Transaction = 1,           //数据库事物
   enLog_Cate_TableName_Color = 2,					//	色号维护
   enLog_Cate_TableName_ColorPrice,				//	价格设置
   enLog_Cate_TableName_Config,					//	全局配置
  
   enLog_Cate_TableName_CompanyInfo,				//	公司信息	
   enLog_Cate_TableName_MacFile_Mgn,				//	横机文件管理			
   enLog_Cate_TableName_Mac_Mgn,					//	机器表	

   enLog_Cate_TableName_Chat_MsgMgn,				//	Chat_MsgMgn								
   enLog_Cate_TableName_SizePart,					//	部位表								
   enLog_Cate_TableName_Chat_MsgRecv,				//	Chat_MsgRecv								
   enLog_Cate_TableName_Size_Style,				//	Size_Style

   enLog_Cate_TableName_PanDianRecords,			//	盘点记录	
   enLog_Cate_TableName_Schedule,					//	班次
   enLog_Cate_TableName_Order_Flag,				//	订单标记次数
   enLog_Cate_TableName_ProSet_Style,				//	款式工序 20

   enLog_Cate_TableName_FangAnGongxu,				//	工序方案								
   enLog_Cate_TableName_ProPrice_Style,			//	订单工序价格
   enLog_Cate_TableName_Plant_Mgn,					//	工厂表								
   enLog_Cate_TableName_DesFaceCode,				//面子码	 25

   enLog_Cate_TableName_DesDensity,				//密度表
   enLog_Cate_TableName_V_MacMgn,					//	机器管理视图										
   enLog_Cate_TableName_V_MacMacFileMgn,			//	横机文件管理视图 30

   enLog_Cate_TableName_VariousStyle,				//	一款多样板对应信息
   enLog_Cate_TableName_Customer,					//	客户管理	
   enLog_Cate_TableName_Gongxu,					//	工序管理	
   enLog_Cate_TableName_Kuanshi,					//	款式维护							
   enLog_Cate_TableName_Menus,						//	菜单管理		35   									
	
   enLog_Cate_TableName_OtherRecord,				//	纱线出入库记录										
   enLog_Cate_TableName_OtherRecords,				//	纱线出、入、领、退详情					
   enLog_Cate_TableName_SMS,						//	短信记录								
   enLog_Cate_TableName_TreeClass,					//	数据字典

   enLog_Cate_TableName_Userinfo,					//	员工管理	
   enLog_Cate_TableName_V_Kuanshi,					//	款式维护视图
   enLog_Cate_TableName_V_OtherRecord,				//	纱线出入库记录视图										
   enLog_Cate_TableName_V_OtherRecords,			//	纱线出、入、领、退详情视图	 45	
								
   enLog_Cate_TableName_V_Userinfo,				//	员工管理视图										
   enLog_Cate_TableName_WorkLog,					//	操作日志	
   enLog_Cate_TableName_DebitRecords,        // 扣款记录
   enLog_Cate_TableName_OrderInStorage,      //订单库存表
   enLog_Cate_TableName_CYRecord,            //订单出入库表 50

   enLog_Cate_TableName_CYRecords,           //订单出入库明细表
   enLog_Cate_TableName_V_CYRecords,         //出入库表视图
   enLog_Cate_TableName_V_OrderInStorage,    //库存表视图
   enLog_Cate_TableName_V_FahuoRecords,      // 综合发货视图记录
   enLog_Cate_TableName_FahuoRecord,      // 综合发货表 55

   enLog_Cate_TableName_FahuoRecords,      // 综合发货明显表
   enLog_Cate_TableName_RdOffFactoryRework,      // 厂外返工登记表
   enLog_Cate_TableName_PINZHONGSETTING,					//	品种维护
   enLog_Cate_TableName_TUIHUOSTATE,					//	退货状态
   enLog_Cate_TableName_InPlantReworkRecords, //厂内返工录入 60

   enLog_Cate_TableName_WLKuanshi,     //商品款式表
   enLog_Cate_TableName_WLKuanshi_Detail_info,  //商品款式条码表
   enLog_Cate_TableName_MATERIEL_INFO, //物料维护
   enLog_Cate_TableName_FANGANMACTYPE, //工序方案绑定机种类型表 65

   enLog_Cate_TableName_ORDER_TYPE_PRICE_SET,  //订货类型价格维护 
   enLog_Cate_TableName_ProcessRecords,				//新工序记录--子表1表 70

   enLog_Cate_TableName_ProcessRecordsDetails,		//新工序记录--子表2表
   enLog_Cate_TableName_ProcessRecords_Main,		//新工序记录--主单表
   enLog_Cate_TableName_OutReworkGXRecords,//厂外返工工序表 75

   enLog_Cate_TableName_Chat_MsgMgn_History,//聊天记录归档
};

static TCHAR g_TableID[Log_Cate_Num][TABLE_NAME_MAX_LEN] = {
   {_T("")},					//0

   {_T("SQL事务")},					
   {_T("Color")},
   {_T("ColorPrice")},
   {_T("Config")},

   {_T("CompanyInfo")}, 
   {_T("MacFile_Mgn")},
   {_T("Mac_Mgn")},   
   
   {_T("Chat_MsgMgn")},
   {_T("SizePart")},
   {_T("Chat_MsgRecv")},
   {_T("Size_Style")},

   {_T("PanDianRecords")},	
   {_T("Schedule")},
   {_T("Order_Flag")},
   {_T("ProSet_Style")},//20

   {_T("FangAnGongxu")},
   {_T("ProPrice_Style")},
   {_T("Plant_Mgn")},
   {_T("DesFaceCode")},	//25

   {_T("DesDensity")},
   {_T("V_MacMgn")},
   {_T("V_MacMacFileMgn")},//30

   {_T("VariousStyle")},
   {_T("Customer")}, 
   {_T("Gongxu")},  
   {_T("Kuanshi")},
   {_T("Menus")}, //35   

   {_T("OtherRecord")},
   {_T("OtherRecords")},
   {_T("SMS")},
   {_T("TreeClass")},

   {_T("Userinfo")},
   {_T("V_Kuanshi")},
   {_T("V_OtherRecord")},
   {_T("V_OtherRecords")},//45 
  
   {_T("V_Userinfo")},
   {_T("WorkLog")},
   {_T("DebitRecords")},
   {_T("OrderInStorage")},
   {_T("CYRecord")}, //50

   {_T("CYRecords")},
   {_T("V_CYRecords")},
   {_T("V_OrderInStorage")}, 
   {_T("V_FahuoRecords")},
   {_T("FahuoRecord")},//55

   {_T("FahuoRecords")},
   {_T("RdOffFactoryRework")},
   {_T("PinZhongSetting")},
   {_T("TuihuoState")},
   {_T("InPlantReworkRecords")},//60

   {_T("WLKuanshi")},
   {_T("WLKuanshi_Detail_info")},
   {_T("MaterielInfo")},
   {_T("FangAnMacType")},//65

   {_T("OrderTypePriceSet")},
   {_T("ProcessRecords")},//70

   {_T("ProcessRecordsDetails")},
   {_T("ProcessRecords_Main")},
   {_T("OutReworkGXRecords")},//厂外返工工序表 75

   {_T("Chat_MsgMgn_History")},
};
//中文表名
static TCHAR g_TableID_CN[Log_Cate_Num][TABLE_NAME_MAX_LEN] = {
   {_T("")},					//0

   {_T("SQL事务")},					
   {_T("色号维护")},
   {_T("价格设置")},
   {_T("全局配置")},
   {_T("订单文件")},  //5

   {_T("公司信息")}, 
   {_T("横机文件管理")},
   {_T("机器表")},   
   {_T("纱线款式索引")},
   {_T("纱线订单索引")}, //10

   {_T("聊天信息管理表")},
   {_T("部位表")},
   {_T("聊天接收信息表")},
   {_T("款式尺寸")},
   {_T("订单尺寸")}, //15

   {_T("盘点记录")},	
   {_T("班次")},
   {_T("订单标记次数")},
   {_T("订单工序")},
   {_T("款式工序")},//20

   {_T("工序方案")},
   {_T("订单工序价格")},
   {_T("工序详情")},
   {_T("工厂表")},
   {_T("面子码")},	//25

   {_T("密度表")},			
   {_T("编码命名规则")},
   {_T("订单规格属性")},  
   {_T("机器管理视图")},
   {_T("横机文件管理视图")},//30

   {_T("一款多样板对应信息")},
   {_T("客户管理")}, 
   {_T("工序管理")},  
   {_T("款式维护")},
   {_T("菜单管理")}, //35   

   {_T("纱线出入库记录")},
   {_T("纱线出、入、领、退详情")},
   {_T("短信记录")},
   {_T("数据字典")},
   {_T("工序绑定")}, //40

   {_T("员工管理")},
   {_T("价格设置视图")},
   {_T("款式维护视图")},
   {_T("纱线出入库记录视图")},
   {_T("纱线出、入、领、退详情视图")},//45 

   {_T("员工管理视图")},
   {_T("操作日志")},
   {_T("扣款记录")},
   {_T("订单库存表")},
   {_T("订单出入库表")}, //50

   {_T("订单出入库明细表")},
   {_T("出入库表视图")},
   {_T("库存表视图")}, 
   {_T("综合发货视图记录")},
   {_T("综合发货表")},//55

   {_T("综合发货明显表")},
   {_T("厂外返工登记表")},
   {_T("品种维护")},
   {_T("退货状态")},
   {_T("厂内返工录入")},//60

   {_T("商品款式表")},
   {_T("商品款式条码表")},
   {_T("物料维护")},  
   {_T("客户树形分组表")},
   {_T("工序方案绑定机种类型表")},//65

   {_T("订货类型价格维护")},
   {_T("款式系列")},
   {_T("新订单1表")},
   {_T("新订单2表")},
   {_T("新工序记录--子表1表")},//70

   {_T("新工序记录--子表2表")},
   {_T("新工序记录--主单表")},
   {_T("订单备注表")},
   {_T("生产单明细表")},
   {_T("厂外返工工序表")},//厂外返工工序表 75
};

