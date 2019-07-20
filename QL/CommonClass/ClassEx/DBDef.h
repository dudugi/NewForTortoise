#pragma once
/*************************************************
// <文件>: DBDef.h
// <说明>: 数据库表名、视图名、函数名、存储过程名称定义头文件
// <作者>: yangjr
// <日期>: 2019/02/20 16:05:08
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 

//--------------------------------------------------------------------
#pragma region 数据库表名
#define DB_TABLE_CLIENT_VARIFY_INFO          _T("ClientVarifyInfo")            //登录信息表
#define DB_TABLE_MATERIEL_INFO               _T("MaterielInfo")                //物料信息表
#define DB_TABLE_COLORMAINTAIN_INFO          _T("ColorMaintain")               //颜色维护表  by liuhw 2018/08/20
#define DB_TABLE_PERSON                      _T("Userinfo")			             //人员信息表（内部员工）
#define DB_TABLE_CUSTOM                      _T("Customer")			             //客户信息表
#define DB_TABLE_FILE                        _T("Table_File")                  //文件表
#define DB_TABLE_STYLE                       _T("Kuanshi")			             //款式表
#define DB_TABLE_YARN                        _T("Color")				             //纱线表
#define DB_TABLE_LOG                         _T("WorkLog")			             //日志表
#define DB_TABLE_SIZEPART                    _T("SizePart")			             //部位表
#define DB_TABLE_PROCESS                     _T("Gongxu")			             //工序表
#define DB_TABLE_DENSITY                     _T("DesDensity")			          //密度表
#define DB_TABLE_DESFACECODE                 _T("DesFaceCode")			          //面子码表
#define DB_TABLE_DES_DENSITY                 _T("SampleDesDensity")			    //密度表
#define DB_TABLE_FACECODE                    _T("SampleDesFaceCode")			    //面子码表
#define DB_TABLE_PIECEWEIGHT                 _T("PieceWeight")			          //衣片重量表
#define DB_TABLE_SIZEPART_ORDER               _T("SizePart_Order")			    //尺寸部位表
#define DB_TABLE_SIZEPART_VALUE               _T("SizePart_Value")			    //尺寸部位的数值表
#define DB_TABLE_DATADICTIONARY              _T("TreeClass")			          //数据字典表
#define DB_TABLE_MENUS                       _T("Menus")				             //导航菜单表
#define DB_TABLE_CONFIG                      _T("Config")			             //全局配置
#define DB_TABLE_COLORPRICE                  _T("ColorPrice")		             //价格设置表 add by yangjr 2017-7-13
#define DB_TABLE_VARIOUSSTYLE                _T("VariousStyle")		          //一款多样板对应信息表
#define DB_TABLE_PROSET_STYLE                _T("ProSet_Style")		          //款式工序配置表 wangzl 2017-11-08
#define DB_TABLE_FANGANGONGXU                _T("FangAnGongxu")		          //工序方案表 add by wuzhihua 2018/01/16
#define DB_TABLE_COMPANY_INFO                _T("CompanyInfo")                 //公司信息表 add by zhangyx 2018/01/22
#define DB_TABLE_COLNAME_SET                 _T("ColNameSet")		             //字段名设置表 add by wuzhihua 2018/02/03
#define DB_TABLE_PIECEINFO                   _T("PieceInfo")                   //衣片信息表 用于存储xx衣片是手摇还是电脑 以及后续统计工价
#define DB_TABLE_STYLE_GLOBAL_SET            _T("TableStyleGlobalSet")         //表格样式全局设置 add by wuzhihua 2018/4/13
#define DB_TABLE_PINZHONGSETTING             _T("PinZhongSetting")             //品种维护 add by yangjr 2018/04/17
#define DB_TABLE_FANGANPOWER                 _T("FangAnPower")                 // 自定义权限方案表    add by anjie 2018/06/04
#define DB_TABLE_STYLEMATERIAL               _T("StyleMaterial")               //款式-原辅料信息    	by WangZY 2019/05/24
#define DB_TABLE_STYLECOLORPERCENT           _T("StyleColorPercent")           //生产款式-颜色比重信息 add by huangym 2018/12/28
#define DB_TABLE_FILEINFO                    _T("F_FileInfo")                  //文件信息 wangzl 2018-08-20
#define DB_TABLE_BANDINFO                    _T("P_BandInfo")                  //打样-波段信息 wangzl 2018-08-20
#define DB_TABLE_COLORINFO                   _T("P_ColorInfo")                 //打样-颜色信息 wangzl 2018-08-20
#define DB_TABLE_MATERIALINFO                _T("P_MatetialInfo")              //打样-物料信息 wangzl 2018-08-20
#define DB_TABLE_PICTUREINFO                 _T("P_PictureInfo")               //打样-图片信息 wangzl 2018-08-20
#define DB_TABLE_PLANNING                    _T("P_Planning")                  //打样-企划表 wangzl 2018-08-20
#define DB_TABLE_PRODUCTSP                   _T("P_ProductStructurePlanning")  //打样-产品结构规划 wangzl 2018-08-20
#define DB_TABLE_PROGRAMMING                 _T("P_Programming")               //打样-商品规划表 wangzl 2018-08-20
#define DB_TABLE_TEXTBOARD                   _T("P_TextBoard")                 //打样-文字版 wangzl 2018-08-20
#define DB_TABLE_PRODUCTVERSION              _T("P_ProductVersions")           //打样 产品信息表 wangzl 2018-08-21
#define DB_TABLE_P_PROCESSRECORDS             _T("P_ProcessRecords")           //打样 流程记录表 wangzl 2018-08-21
#define DB_TABLE_PRODUCTTASKASSIGN           _T("P_ProductTaskAssign")         //打样 产品任务安排 wangzl 2018-08-25
#define DB_TABLE_PRODUCTPROCESS              _T("P_ProductProcess")            //打样 工序 wangzl 2018-08-27
#define DB_TABLE_PRODUCTREVISIONRECORDS      _T("P_ProductRevisionRecords")    //打样 产品改版记录 wangzl 2018-08-31


#define DB_TABLE_PROCESSRECORDS              _T("ProcessRecords")              //子单工序记录表 wangzl 2018-10-08
#define DB_TABLE_SMALLPIC		               _T("SmallPic")                    //小图管理  by huangym 2018-12-3
#define DB_TABLE_DESIGNDATALIB		         _T("DesignData_Lib")                  // 部件库管理表
#define DB_TABLE_DESIGNDATA		             _T("DesignData")                  // 制版配置表
#define DB_TABLE_STANDARDSIZE  		         _T("StandardSize")                // 标准尺码表
#define DB_TABLE_STANDARDSIZEMODIFY  		   _T("StandardSizeModify")          // 标准尺码详情表
#define DB_TABLE_STANDARDSIZE_PINMING		   _T("StandardSize_PinMing")        // 标准尺码-品名表
#define DB_TABLE_CONTROLSPERMISSION          _T("ControlsPermission")//控件权限表 wangzl 2019-2-18
#define DB_TABLE_USER_STYLEPERMISSION        _T("User_StylePermission")//用户款式权限表 wangzl 2019-05-06
#define DB_TABLE_STYLE_SIZE                  _T("Style_Size") // 版房款式尺寸信息表 liuhw 2019/05/06
#define DB_TABLE_STYLE_CHIMA                 _T("Style_Chima") // 版房款式尺码信息表 liuhw 2019/05/06
#define DB_TABLE_STYLE_CHECKRECORDS          _T("Style_CheckRecords") // 款式检入检出记录表 liuhw 2019/05/06
#define DB_TABLE_STYLE_COST                  _T("Style_Cost")      //款式成本信息表    anjie 20190523
#define DB_TABLE_STYLE_FILEINFO              _T("Style_FileInfo")  //款式文件信息表    wangzl 2019/05/28
#define DB_TABLE_STYLE_VERSIONRECORDS        _T("Style_VersionRecords")  //款式版本记录表    wangzl 2019/06/05
#define DB_TABLE_STYLE_DESCRIPTION           _T("Style_Description")    //款式描述表     lida 2019/06/11
#define DB_TABLE_CONFIG_TAGNAME              _T("Config_TagName")    //标签名称 wangzl 2019-6-12
#define DB_TABLE_STYLE_DESDENISITY           _T("Style_DesDenisity")    //款式密度表 wangzl 2019-6-19
#define DB_TABLE_STYLE_DESFACECODE           _T("Style_DesFaceCode")    //款式面子码表 wangzl 2019-6-19
#define DB_TABLE_STYLE_BASIC_FIELDSET        _T("Style_Basic_FieldSet")    //款式基本字段设置表
#define DB_TABLE_SAMPLE_CLOTHING_INFO        _T("SampleClothingInfo")   //样衣 lida 2019/07/01
#define DB_TABLE_SAMPLE_CLOTHING_RECORDS     _T("SampleClothingRecords")   //样衣收发记录 lida 2019/07/01
#define DB_TABLE_STYLESIZEEXTRA              _T("Style_SizeExtra")			   //款式尺寸额外信息表 yangjr 2019/07/14 
#define DB_TABLE_PRODUCTORDERINFO            _T("ProductOrderInfo")        //版房生产单信息表 lida 2019/07/17
#define DB_TABLE_SALESORDERINFO            _T("SalesOrderInfo")        //版房生产单信息表 lida 2019/07/17

#define DB_VIEW_KUANSHI                      _T("V_Kuanshi")			//款式视图
#define DB_VIEW_ORDERCHILD                   _T("V_RdRecordsChild")		//生产订单视图
#define DB_VIEW_ORDERSALES                   _T("V_RdRecordsSales")		//主订单视图
#define DB_VIEW_USERINFO                     _T("V_UserInfo")
#define DB_VIEW_BANDPROGRAMMINGVIEW          _T("V_BandProgramming") //波段商品信息视图  add anjie by 2018/08/28

#define DB_VIEW_PRODUCTPROCESS               _T("V_ProductProcess")	//产品应该执行的工序 及对应的工序记录视图 wangzl 2018-08-30
#define DB_VIEW_PRODUCTVERSIONORDERS         _T("V_ProductVersionOrders") //打样版单视图
#define DB_VIEW_PRODUCTREVISIONRECORDS       _T("V_ProductRevisionRecords") //打样版单改版请求视图 wangzl 2018-09-03

#define DB_VIEW_PROCESSRECORDSDETAILS        _T("V_ProcessRecordsDetails")    //工序记录及其详情表 工序记录 + 对应片重 批号 等信息  wangzl 2018-10-08
#define DB_VIEW_PROCESSRECORDS               _T("V_ProcessRecords")           //子订单及相关的工序记录和详情信息 wangzl 2018-10-08
#define DB_VIEW_PROCESSRECORDS_MAINDETAILS   _T("V_ProcessRecords_MainDetails")//主单工序及对应的人员信息
#define DB_VIEW_PROCESSRECORDS_MAIN          _T("V_ProcessRecords_Main") //主订单的工序记录和订单的详情信息
#define DB_VIEW_USERSTYLE_PERMISSION         _T("V_User_Style_Permission")//用户款式权限
#define DB_VIEW_KUANSHI_NEXTPROINFO          _T("V_Kuanshi_NextProInfo")//款式下个工序信息视图
#define DB_VIEW_STYLEFILEINFO                _T("V_StyleFileInfo")//款式的文件信息视图

#define DB_VIEW_CLOUD_MODULE_INFO            _T("V_CloudModuleInfo")      //云模块信息视图表     	by WangZY 2019/06/04
#define DB_VIEW_STYLE_COST                   _T("V_Style_Cost")         //款式成本视图     	by wangzl 2019/06/11
#define DB_VIEW_USERTASKINFO                 _T("V_UserTaskInfo")         //用户任务信息视图     	by wangzl 2019/06/14

#define DB_PROCESS_ORDERONEMOREPIECEINSERT   _T("P_RdRecordsOneMorePieceInsert")//一单多件下单的存储过程 仅针对只有一套配色方案的单子  wangzl 2018-10-22
#define DB_PROCESS_SAVEFILEINFO              _T("P_SaveFileInfo")
#define DB_PROCESS_CreateSampleClothingBarCode  _T("P_CreateSampleClothingBarCode") //样衣单流水号 lida 2019/07/02

#define DB_P_CreateSalesCode              _T("P_CreateSalesCode")  //生产销售单号 add by lida 2018/10/09

#define DB_P_ImportProductKSInfo             _T("P_ImportProductKSInfo")      //导入款式基本信息到商品维护中 add by lida 2018/06/15
#define DB_P_ImportProductKSInfo_Single      _T("P_ImportProductKSInfo_single")      //导入当款式基本信息到商品维护中 add by lida 2018/07/20
#define DB_P_UpdateOrdPrintCount             _T("P_UpdateOrdPrintCount")      //更新订单打印洗水唛次数

#define DB_P_GetCanInboundChildCode          _T("P_GetCanInboundChildCode")    //根据主单获取最小能够入库的子单 yangjr 2018/11/23
#define DB_P_GetSalesCodeBatch              _T("P_GetSalesCodeBatch")  //批量打印订单号获取单号 add by yangjr 2018/12/20
#define DB_P_GetBatchCode                    _T("P_GetBatchCode")    //批量生成订单号的存储过程	by WangZY 2019/01/03

#define DB_P_UPDATE_STYLE_COST               _T("P_UpdateStyleCost")    //更新款式总成本和总报价 by lida 2019/07/12

#define DB_FUNCTION_GETPY                    _T("dbo.getPY")
#define DB_FUNCTION_GETSTRARRAYSTROFINDEX    _T("dbo.getStrArrayStrOfIndex")//根据分隔符和索引值获取当前字符串数组的对应位置的字符串索引从1开始
#define DB_FUNCTION_GETSTRARRAYLENGTH        _T("dbo.getStrArrayLength")//根据分隔符获取整个字符串数组的个数



#pragma endregion 数据库表名
//--------------------------------------------------------------------
#pragma region 数据类类型定义
//CDataMid::m_nDataType
typedef enum EnDBDataType
{
	DAT_PERSON			= 10,
	DAT_ORDER			= 11,
	DAT_ASSIGN              ,
	DAT_CUSTOM              ,
	DAT_FILE                ,
	DAT_STYLEFIND			,
	DAT_STYLE               ,
	DAT_YARNFIND            ,
	DAT_YARN                ,
   DAT_COLOR            ,
	DAT_LOG					,
	DAT_SIZE				,
	DAT_STYLE_SIZE			,
	DAT_SIZEPART			,
	DAT_PROCESS				,
	DAT_PROCESSBIND			,
	DAT_DATADICTIONARY		,
	DAT_MENUS				,
	DAT_VORDER				,
	DAT_FIELD				,
	DAT_VOTHERFEI			,
	DAT_CONFIG				,
	DAT_VSTYLE				,
	DAT_VPERSON				,
	DAT_VARIOUSSTYLE		,//多订单表类型
	DAT_ACTMAP				,
	DAT_PROPRICE_STYLE   ,//款式工序价格表
	DAT_PROSET_STYLE     ,//款式工序配置表
   DAT_ORDER_FILE       ,//订单文件
   DAT_COMPANY_INFO     ,//公司信息
   DAT_VGONGXURDRECORDS ,
   DAT_PIECEINFO        ,//衣片信息
   DAT_BINDINFO         ,//波段信息
   DAT_TEXTBOARD        ,//文字板
   DAT_PROGRAMMING      ,//商品规划表
   DAT_PRODUCTSTRUCTUREPLANNINGDATA,//产品结构规划表
   DAT_PLANNING,          //主题企划
   DAT_COLORINFO,             //颜色
   DAT_PICTURE,           //图片
   DAT_MATETIALINfO,      //物料
   DAT_PRODUCTVERSIONS  ,//打样-产品版本信息
   DAT_PROCESSRECORDS   ,//打样 流程记录
   DAT_PRODUCTTASKASSIGN,//打样-任务安排
   DAT_BANKPROGRAMMING,//打样-bankprogramming视图
   DAT_PRODUCTPROCESS   ,//打样-工序
   DAT_PRODUCTREVISIONRECORDS,//打样-改版记录
   DAT_PROCESSRECORDS_MAIN,//主单工序记录
   DAT_WEBIMAGEORDER,//网络传单用图片信息类
   DAT_CONTROLSPERMISSION,//控件权限定义
   DAT_USERSTYLE_PERMISSION,//用户款式权限
   DAT_STYLE_CHIMA,//版房款式尺码
   DAT_STYLE_CHECKRECORDS,//款式检入检出记录
   DAT_STYLE_NEXTPROINFO,//款式的下个工序信息
   DAT_STYLE_COST ,//款式成本
   DAT_STYLE_FILEINFO ,//款式成本
   DAT_STYLE_VERSIONRECORDS,//款式版本定版改版记录
   DAT_V_STYLE_COST,//款式成本视图
   DAT_CONFIG_TAGNAME,//标签名称
   DAT_V_USER_TASKINFO,//用户信息视图
   DAT_STYLE_DESDENISITY ,//款式密度
   DAT_STYLE_DESFACECODE ,//款式面子码
   DAT_STYLE_BASIC_FIELDSET,//款式基础信息
}En_KDSFG_DBDataType;
#pragma endregion 数据类类型定义

typedef enum EnSelect_Time
{
	STM_CUSTOM			= 0,	//用户自定义
	STM_TODAY			= 10,	//当天
	STM_CURWEEK             ,	//11 本周
	STM_CURMONTH            ,	//12 本月
	DAT_CURQUARTER          ,	//13 本季度
	DAT_CURYEAR				,	//14 本年

}En_KDSFG_Select_Time;

#define SampleOrderCate	_T("1样衣")
#define NormalOrderCate	_T("1普通")
