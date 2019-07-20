#pragma once

//--------------------------------------------------------------------
#pragma region 数据库表名
#define DB_TABLE_CLIENT_VARIFY_INFO          _T("ClientVarifyInfo")            //登录信息表
#define DB_TABLE_MATERIEL_INFO               _T("MaterielInfo")                //物料信息表
#define DB_TABLE_COLORMAINTAIN_INFO          _T("ColorMaintain")               //颜色维护表  by liuhw 2018/08/20
#define DB_TABLE_OFF_FACTORY_REWORK_RECORDS	_T("RdOffFactoryRework")	       //厂外返工记录表		by WangZY 2018/04/03
#define DB_TABLE_PERSON                      _T("Userinfo")			             //人员信息表（内部员工）
#define DB_TABLE_COMMONPROINFO               _T("CommonProIntro")              //工序信息类别表
#define DB_TABLE_CUSTOM                      _T("Customer")			             //客户信息表
#define DB_TABLE_FILE                        _T("Table_File")                  //文件表
#define DB_TABLE_SIZE                        _T("Size_Order")                  //尺码表
#define DB_TABLE_STYLE                       _T("Kuanshi")			             //款式表
#define DB_TABLE_YARN                        _T("Color")				             //纱线表
#define DB_TABLE_YARNINDEX                   _T("Table_YarnIndex_Order")       //纱线索引表
#define DB_TABLE_LOG                         _T("WorkLog")			             //日志表
#define DB_TABLE_YARNINDEX_STYLE             _T("Table_YarnIndex_Style")       //纱线索引表
#define DB_TABLE_SIZE_STYLE                  _T("Size_Order")		             //款式尺寸表
#define DB_TABLE_SIZEPART                    _T("SizePart")			             //部位表
#define DB_TABLE_PROCESS                     _T("Gongxu")			             //工序表
#define DB_TABLE_DENSITY                     _T("DesDensity")			          //密度表
#define DB_TABLE_DESFACECODE                 _T("DesFaceCode")			          //面子码表
#define DB_TABLE_DES_DENSITY                 _T("SampleDesDensity")			    //密度表
#define DB_TABLE_FACECODE                    _T("SampleDesFaceCode")			    //面子码表
#define DB_TABLE_CLOTHPIECE                  _T("ClothPiece")			          //衣片信息表
#define DB_TABLE_PIECEWEIGHT                 _T("PieceWeight")			          //衣片重量表
#define DB_TABLE_SIZEPART_ORDER               _T("SizePart_Order")			    //尺寸部位表
#define DB_TABLE_SIZEPART_VALUE               _T("SizePart_Value")			    //尺寸部位的数值表
#define DB_TABLE_PROCESSBIND                 _T("UserGongxu")		             //工序绑定表
#define DB_TABLE_DATADICTIONARY              _T("TreeClass")			          //数据字典表
#define DB_TABLE_PRODETAIL                   _T("ProDetail")			          //工序详情表
#define DB_TABLE_CODERULE                    _T("CodeRule")			             //编码命名规则表
#define DB_TABLE_MENUS                       _T("Menus")				             //导航菜单表
#define DB_TABLE_YARNRECORD                  _T("OtherRecord")		             //纱线出入库记录表
#define DB_TABLE_YARNRECORDS                 _T("OtherRecords")		          //纱线出入库表
#define DB_TABLE_CONFIG                      _T("Config")			             //全局配置
#define DB_TABLE_COLORPRICE                  _T("ColorPrice")		             //价格设置表 add by yangjr 2017-7-13
#define DB_TABLE_VARIOUSSTYLE                _T("VariousStyle")		          //一款多样板对应信息表
#define DB_TABLE_ACTMAP                      _T("ActMap")			             //
#define DB_TABLE_SMS                         _T("SMS")				             //发送短信记录表 add by yangjr 2017-9-18
#define DB_TABLE_PROSET_STYLE                _T("ProSet_Style")		          //款式工序配置表 wangzl 2017-11-08
#define DB_TABLE_PROSET_ORDER                _T("ProSet_Order")                //订单工序配置表 wangzl 2018-05-03
#define DB_TABLE_ORDER_SIZE_ATTRIBUTE        _T("Attribute_Size_Order")        //订单的规格的属性表 wangzl 2017-11-14
#define DB_TABLE_MAC                         _T("Mac_Mgn")			             //机器表 add by lida 2017/11/20
#define DB_TABLE_PLANT                       _T("Plant_Mgn")			          //工厂表 add by lida 2017/11/20
#define DB_TABLE_MACFILE                     _T("MacFile_Mgn")		             //横机文件管理 add by lida 2017/12/01
#define DB_TABLE_PANDIANRECORDS              _T("PanDianRecords")	             //盘点记录表  by yangjr2018/1/9
#define DB_TABLE_SCHEDULE                    _T("Schedule")			             //班次表 add by lida 2018/01/08
#define DB_TABLE_FANGANGONGXU                _T("FangAnGongxu")		          //工序方案表 add by wuzhihua 2018/01/16
#define DB_TABLE_ORDERFILE                   _T("OrderFile")				       //工序方案表 add by wuzhihua 2018/01/16
#define DB_TABLE_COMPANY_INFO                _T("dbo.CompanyInfo")	          //公司信息表 add by zhangyx 2018/01/22
#define DB_TABLE_COLNAME_SET                 _T("ColNameSet")		             //字段名设置表 add by wuzhihua 2018/02/03
//#define DB_TABLE_TABLENAME_SET             _T("TableNameSet")		          //表中文名设置表 add by wuzhihua 2018/02/03
//#define DB_TABLE_STYLE_SET                 _T("TableStyleSet")		          //样式表属性设置 add by wuzhihua 2018/02/03
//#define DB_TABLE_MAOSHA                    _T("Maosha")		                //回丝 毛纱表 yangjr 2018/2/28
#define DB_TABLE_PIECEINFO                   _T("PieceInfo")                   //衣片信息表 用于存储xx衣片是手摇还是电脑 以及后续统计工价
#define DB_TABLE_DEMAND_ORDER                _T("Demand_Order")                //订单备注信息表
#define DB_TABLE_ORDER_INSTORAGE             _T("OrderInStorage")	             //订单入库表 add by lida 2018/03/20
#define DB_TABLE_JIASHA_RECORDS              _T("JiaShaRecords")               //加毛明细表 add by wuzhihua 2018/03/20
#define DB_TABLE_DEDUCTMONEY_RECORDS         _T("DebitRecords")                //扣款明细表 add by wuzhihua 2018/03/22
#define DB_TABLE_CYRECORDS                   _T("CYRecords")                   //成衣出入库表 add by lida 2018/03/23
#define DB_TABLE_CYRECORD                    _T("CYRecord")                    //成衣出入库明细表 add by lida 2018/03/23
#define DB_TABLE_FAHUORECORD                 _T("FahuoRecord")	                //发货记录总表 by yangjr2018/3/26
#define DB_TABLE_FAHUORECORDS                _T("FahuoRecords")	             //发货记录明细表 by yangjr2018/3/26
#define DB_TABLE_ClIENTTREEGROUP             _T("ClientTreeGroup")             //客户树形分组表 add by wuzhihua 2018/3/28
#define DB_TABLE_INPLANT_REWORK_RECORDS      _T("InPlantReworkRecords")        //厂内返工 add by wuzhihua 2018/4/4
#define DB_TABLE_STYLE_GLOBAL_SET            _T("TableStyleGlobalSet")         //表格样式全局设置 add by wuzhihua 2018/4/13
#define DB_TABLE_WL_KUANSHI                  _T("WLKuanshi")                   //外来款式 add by lida 2018/04/18
#define DB_TABLE_WL_KUANSHI_DETAIL_INFO      _T("WLKuanshi_Detail_info")       //外来款式详情 add by lida 2018/06/12
#define DB_TABLE_PINZHONGSETTING             _T("PinZhongSetting")             //品种维护 add by yangjr 2018/04/17
#define DB_TABLE_TUIHUOSTATE                 _T("TuihuoState")                 //退货状态 add by yangjr 2018/04/21
#define DB_TABLE_ORDER_TYPE_PRICE_SET        _T("OrderTypePriceSet")           //订货类型价格维护 add by wuzhihua 2018/4/22
#define DB_TABLE_FINDKEY_STYLE               _T("FindKey_Style")               //款式的关键词表
#define DB_TABLE_KUANSHI_CLASS               _T("KuanshiClass")                //款式系列表
#define DB_TABLE_FANGANMACTYPE               _T("FangAnMacType")               //工序方案绑定机种类型表		by WangZY 2018/05/15
#define DB_TABLE_FANGANPOWER                 _T("FangAnPower")                 // 自定义权限方案表    add by anjie 2018/06/04
#define DB_INVENTORY_CHECK_FLAG              _T("inventory_check_flag")        //库存盘点标识    add by lida 2018/06/04
#define DB_INVENTORY_CHECK_PERIOD            _T("inventory_check_period")      //盘点期数标识    add by lida 2018/06/04
#define DB_INVENTORY_CHECK_RECORDS           _T("inventory_check_records")     //库存盘点记录    add by lida 2018/06/04
//#define DB_TABLE_ORDER_ENTRY_PICNAME         _T("OrderEntry_PicName")      //订单录入订单款式图片表   add by anjie 2018/06/06
#define DB_TABLE_ORDERTRACK                  _T("OrderTrack")                  //订单跟踪 add by yangjr 2018/06/07
#define DB_TABLE_STYLEMETARIAL               _T("StyleMetarial")               //生产款式-原料信息 add by lida 2018/06/20
#define DB_TABLE_STYLESUPMETARIAL            _T("StyleSupMetarial")            //生产款式-辅料信息 add by huangym 2018/12/24
#define DB_TABLE_STYLECOLORPERCENT           _T("StyleColorPercent")           //生产款式-颜色比重信息 add by huangym 2018/12/28
#define DB_TABLE_STYLEGOODSINFO              _T("StyleGoodsInfo")              //生产款式-商品信息 add by lida 2018/06/20
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
#define DB_TABLE_SALESPRODUCTINFO           _T("SalesProductInfo")             //销售生产订单对应表 yangjr 2018-09-06
#define DB_TABLE_SALESORDERDETAIL           _T("SalesOrderDetail")             //销售订单明细表 yangjr 2018-09-06
#define DB_TABLE_CUSTOMERBRANCH              _T("CustomerBranch")              //客户分店标识  wangzl 2018-09-18
#define DB_TABLE_RDRECORDS1ST                _T("RdRecords1st")
#define DB_TABLE_RDRECORDS2ND                _T("RdRecords2nd")
#define DB_TABLE_PROCESSRECORDS              _T("ProcessRecords")              //子单工序记录表 wangzl 2018-10-08
#define DB_TABLE_PROCESSRECORDS_MAIN         _T("ProcessRecords_Main")         //主单工序记录表 wangzl 2018-10-08
#define DB_TABLE_PROCESSRECORDSDETAILS       _T("ProcessRecordsDetails")       //子单工序记录详情 wangzl 2018-10-08
#define DB_TABLE_OUTREWORKGXRECORDS	         _T("OutReworkGXRecords")	       //厂外返工工序记录表		by Yangjr 2018/10/11
#define DB_TABLE_WEB_CONFIGURATION           _T("WebConfig")                   //网页录入配置  by huangym 2018-11-7
#define DB_TABLE_SMALLPIC		               _T("SmallPic")                    //小图管理  by huangym 2018-12-3
#define DB_TABLE_DESIGNDATALIB		         _T("DesignData_Lib")                  // 部件库管理表
#define DB_TABLE_DESIGNDATA		             _T("DesignData")                  // 制版配置表
#define DB_TABLE_STANDARDSIZE  		         _T("StandardSize")                // 标准尺码表
#define DB_TABLE_STANDARDSIZEMODIFY  		   _T("StandardSizeModify")          // 标准尺码详情表
#define DB_TABLE_STANDARDSIZE_PINMING		   _T("StandardSize_PinMing")        // 标准尺码-品名表
#define DB_TABLE_FOCUS_CUSTOMER              _T("Focus_Customer")              // 关注客户表 liuhw 2018/11/29
#define DB_TABLE_TABLE_MAX_SERIAL_COUNT      _T("Table_Max_Serial_Count")      //不同组的最大流水号表 wangzl 2018-12-20
#define DB_TABLE_BATCHSALESCODE              _T("Table_BatchSalesCode")        //批量打印订单号存储表 yangjr 2018/12/20
#define DB_TABLE_TUIHUO_REGISTER             _T("TuihuoRegister")       //退货登记 add by lida 2018/12/29
#define DB_TABLE_ORDERWARNINGCONDITION       _T("OrderWarningCondition") //订单预警控件状态表
#define DB_TABLE_WEB_IMAGE_ORDER             _T("WebImageOrder") //网络传单  huangym 2019/1/15
#define DB_VIEW_CYRECORDS                    _T("V_CYRecords")
#define DB_VIEW_ORDER_INSTORAGE              _T("V_OrderInStorage")	//订单入库视图 add by lida 2018/03/20
#define DB_VIEW_COLORPRICE                   _T("V_ColorPrice")		//纱线价格视图
//#define DB_VIEW_CUSTUSERINFO                 _T("V_CustUserInfo")	//客户信息视图(直营店)
//#define DB_VIEW_GONGXURECORDS                _T("V_GongxuRecords")	//工序记录视图 add by yangjr 2017-7-5
#define DB_VIEW_KUANSHI                      _T("V_Kuanshi")			//款式视图
//#define DB_VIEW_KUANSHIPRICE                 _T("V_KuanshiPrice")	//
#define DB_VIEW_MEMBER                       _T("V_Member")			//
#define DB_VIEW_OTHERRECORD                  _T("V_OtherRecord")		//
#define DB_VIEW_OTHERRECORDS                 _T("V_OtherRecords")		//
//#define DB_VIEW_ORDER                        _T("V_RdRecords")		//订单视图
#define DB_VIEW_ORDERCHILD                   _T("V_RdRecordsChild")		//生产订单视图
#define DB_VIEW_ORDERSALES                   _T("V_RdRecordsSales")		//主订单视图
//#define DB_VIEW_RDRECORDS1                   _T("V_RdRecords1")		//
#define DB_VIEW_SHOPRECORD                   _T("V_ShopRecord")
#define DB_VIEW_SHOPRECORDS                  _T("V_ShopRecords")
#define DB_VIEW_SHOPRECORDS1                 _T("V_ShopRecords1")
#define DB_VIEW_USERINFO                     _T("V_UserInfo")
#define DB_VIEW_MACMGN                       _T("V_MacMgn")			//机器管理视图	add by lida 2017/11/20
#define DB_VIEW_FAHUORECORDS                 _T("V_FahuoRecords")	//发货记录视图 by yangjr2018/3/26
#define DB_VIEW_BANDPROGRAMMINGVIEW          _T("V_BandProgramming") //波段商品信息视图  add anjie by 2018/08/28

#define DB_VIEW_PRODUCTPROCESS               _T("V_ProductProcess")	//产品应该执行的工序 及对应的工序记录视图 wangzl 2018-08-30
#define DB_VIEW_PRODUCTVERSIONORDERS         _T("V_ProductVersionOrders") //打样版单视图
#define DB_VIEW_PRODUCTREVISIONRECORDS       _T("V_ProductRevisionRecords") //打样版单改版请求视图 wangzl 2018-09-03

#define DB_VIEW_PROCESSRECORDSDETAILS        _T("V_ProcessRecordsDetails")    //工序记录及其详情表 工序记录 + 对应片重 批号 等信息  wangzl 2018-10-08
#define DB_VIEW_PROCESSRECORDS               _T("V_ProcessRecords")           //子订单及相关的工序记录和详情信息 wangzl 2018-10-08
#define DB_VIEW_PROCESSRECORDS_MAINDETAILS   _T("V_ProcessRecords_MainDetails")//主单工序及对应的人员信息
#define DB_VIEW_PROCESSRECORDS_MAIN          _T("V_ProcessRecords_Main") //主订单的工序记录和订单的详情信息
#define DB_VIEW_OUTREWORKRECORDS             _T("V_OutReworkRecords")	//厂外返工工序视图 -- 字段跟DB_VIEW_PROCESSRECORDS一样 add by yangjr 2018-11-15
#define DB_VIEW_OUTREWORKRECORDS_MAIN        _T("V_OutReworkRecords_Main")	//厂外返工工序视图主单 -- 字段跟DB_VIEW_PROCESSRECORDS_MAIN一样 add by yangjr 2018-11-15

#define DB_PROCESS_ORDERONEMOREPIECEINSERT   _T("P_RdRecordsOneMorePieceInsert")//一单多件下单的存储过程 仅针对只有一套配色方案的单子  wangzl 2018-10-22
#define DB_PROCESS_SAVEFILEINFO              _T("P_SaveFileInfo")

#define DB_PROCESS_SALESORDERINSERT          _T("P_SalesRdRecordsInsert") //销售订单新增存储过程

#define DB_PROCESS_FAHUORECORDADD            _T("P_FaHuoRecordAddNew")	//新增发货单的存储过程 yangjr 2018-3-27
#define DB_P_CreateNewInventoryCheckPeriod   _T("P_CreateNewInventoryCheckPeriod")     //创建新的盘点期数 add by lida 2018/06/05
#define DB_P_CreateCYCode                    _T("P_CreateCYCode")    //生成新的成衣入库单号 add by lida 2018/06/05
#define DB_P_CreateCYKSOrdCode               _T("P_CreateCYKSOrdCode")     //生成新的成衣外来款式订单号 add by lida 2018/06/05
#define DB_P_CreateSalesCode              _T("P_CreateSalesCode")  //生产销售单号 add by lida 2018/10/09
#define DB_P_Add_Del_SalesProductOrder       _T("P_Add_Del_SalesProductOrder")   //修改订单件数 add by lida 2018/11/05
#define DB_P_CreateYarnRecordCode            _T("P_CreateYarnRecordCode")     //生成纱线出入库单号 add by lida 2019/02/14

#define DB_P_ImportProductKSInfo             _T("P_ImportProductKSInfo")      //导入款式基本信息到商品维护中 add by lida 2018/06/15
#define DB_P_ImportProductKSInfo_Single      _T("P_ImportProductKSInfo_single")      //导入当款式基本信息到商品维护中 add by lida 2018/07/20
#define DB_P_UpdateOrdPrintCount             _T("P_UpdateOrdPrintCount")      //更新订单打印洗水唛次数
#define DB_PROCESS_FAHUORECORDSINSERT        _T("P_FahuoRecordsInsert")//发货明细表插入 Yangjr 2018/8/15
#define DB_PROCESS_ImportOrderKuCunToFahuo   _T("P_ImportOrderKuCunToFahuo")//导入订单所有库存到发货 Yangjr 2018/9/20
#define DB_P_CreateOutReworkCode                 _T("P_CreateOutReworkCode")    //生成厂外返工单号 yangjr 2018/11/15
#define DB_P_GetCanInboundChildCode          _T("P_GetCanInboundChildCode")    //根据主单获取最小能够入库的子单 yangjr 2018/11/23
#define DB_P_DelCYKucunRollBackState          _T("P_DelCYKucunRollBackState")    //删除成衣库存的时候回滚订单状态 yangjr 2018/11/25
#define DB_P_UpdateYarnPriceNoRuKun           _T("P_UpdateYarnPriceNoRuKun")     //更新未入库的订单纱线单价 yangjr 2018/12/3
#define DB_P_ChangeZhuSe                      _T("P_ChangeZhuSe")     //订单特殊处理更改主色存储过程 yangjr 2018/12/11
#define DB_P_GetSalesCodeBatch              _T("P_GetSalesCodeBatch")  //批量打印订单号获取单号 add by yangjr 2018/12/20
#define DB_P_GetBatchCode                    _T("P_GetBatchCode")    //批量生成订单号的存储过程	by WangZY 2019/01/03



#define DB_FUNCTION_GETPY                    _T("dbo.getPY")
//#define DB_FUNCTION_GETLastGXNameAndState    _T("dbo.getLastGongxuState") //获取上一道工序的工序名称以及状态 yangjr 2018/1/17
#define DB_FUNCTION_GETSTRARRAYSTROFINDEX    _T("dbo.getStrArrayStrOfIndex")//根据分隔符和索引值获取当前字符串数组的对应位置的字符串索引从1开始
#define DB_FUNCTION_GETSTRARRAYLENGTH        _T("dbo.getStrArrayLength")//根据分隔符获取整个字符串数组的个数
//#define DB_FUNCTION_ISYARNLOCK _T("dbo.IsYarnLock") //纱线库存是否不足，是否已下架 0表示正常未锁定，1、表示纱线已锁定，2表示纱线已下架 yangjr 2017-12-11 暂时不用了2018/1/6
//#define DB_FUNCTION_IsYarnStockLowThenYuJing _T("dbo.IsYarnStockLowThenYuJing") //纱线库存是否不足  0表示正常，1、表示纱线低于预警值 yangjr 2017-12-11 暂时不用了2018/1/6
#define DB_WEB_CONFIGURATION                 _T("WebConfiguration")//网页录入配置
#define DB_FUNCTION_GETORDERPRINTEXTRASIZEREMARK  _T("dbo.GetOrderPrintExtraSizeRemark")
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
	DAT_PRODETAIL			,
	DAT_CODERULE			,
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
   DAT_DEMAND_ORDER     ,//订单备注类 区分不同的工序 不区分人员
   DAT_PIECEINFO        ,//衣片信息
   DAT_FINDKEY_STYLE    ,//款式的关键词
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
   DAT_CUSTOMERBRANCH,    //客户分店表
   DAT_PROCESSRECORDS_MAIN,//主单工序记录
   DAT_TABLE_MAX_SERIAL_COUNT,//分组最大流水号
   DAT_WEBIMAGEORDER,//网络传单用图片信息类
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
