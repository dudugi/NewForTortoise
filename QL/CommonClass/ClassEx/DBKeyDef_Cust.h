#pragma once

//自定义字段，不在数据库表中	add by lida 2018/02/05

/*==============================工序 dbo.GongxuRecords ==============================*/
#define DBAssign_Key_iSortID		_T("iSortID")	//工序排序ID
#define DBAssign_Key_OrdDate		_T("dDate")		//下单日期
#define DBAssign_Key_Jianshu		_T("cJianshu")	//件数

/*==============================价格设置 dbo.ColorPrice ==============================*/
#define DBPRICESET_KEY_cCusCate       _T("cCusCate")    //客户类型
#define DBPRICESET_KEY_cCusName       _T("cCusName")    //客户全称
//#define DBPRICESET_KEY_cCusAbbName    _T("cCusAbbName") //客户简称
//#define DBPRICESET_KEY_vCusAbbName    _T("vCusAbbName") //客户

/*==============================客户信息 dbo.Customer ==============================*/
#define  CustomerTable_newCusName			_T("newCusName")				//客户名称 不在数据库表中 yangjr 2017-8-16

/*==============================总账信息 dbo. ==============================*/
#define DBFLI_cCate			_T("cCate")				//客户、伙伴、供应商等等
#define DBFLI_cCusCate		_T("cCusCate")			//厂库、直营店等
#define DBFLI_cCusCode		_T("cCusCode")			//客户编码
#define DBFLI_cCusName		_T("cCusName")			//客户名称
#define DBFLI_iMoney		_T("iMoney")			//期初欠款
#define DBFLI_newcCusName	_T("newcCusName")		//
#define DBFLI_YS			_T("YS")				//应收
#define DBFLI_SS			_T("SS")				//实收
#define DBFLI_YE			_T("YE")				//尚欠款

/*==============================其他费用视图表 dbo.V_OtherFei ==============================*/
#define  DBOTHER_key_NewCusName			_T("newcCusName")		//客户名称  视图扩展类使用字段  

/*==============================纱线收发存表 dbo. ==============================*/
#define  DB_RSS_DATA_KEY_iQuantity0		_T("iQuantity0")
#define  DB_RSS_DATA_KEY_iQuantity1		_T("iQuantity1")
#define  DB_RSS_DATA_KEY_iQuantity2	_T("iQuantity2")
#define  DB_RSS_DATA_KEY_iQuantity3	_T("iQuantity3")
#define  DB_RSS_DATA_KEY_iQuantityML	_T("iQuantityML") //领用出库 yangjr 2017-12-29
#define  DB_RSS_DATA_KEY_iQuantityPK	_T("iQuantityPK") //盘亏出库 yangjr 2017-12-29

/*==============================表 dbo.ProSet_Style ==============================*/ 
#define DBProSet_Style_key_UserName		_T("cUserName")

/*==============================收发管理 表 dbo. ==============================*/
#define DBReceiveManage_key_DeliveryPersonCode	_T("cDeliveryPersonCode")		//发货人(核发人工号)	by WangZY 2018/03/20
#define DBReceiveManage_key_ReceivePersonCode	_T("cReceivePersonCode")		//核收人(收纱人工号)	by WangZY 2018/03/20

/*==============================表 dbo.成衣审核入库 ==============================*/
#define DB_CY_IN_CHECK_SCALE_STATE     _T("ScaleState")        //扫描状态

/*==============================表 部门超期预警     ==============================*/
#define DBOVERTIMEWARNING_OVERTIME     _T("OverTime")//超时时间
#define DBOVERTIMEWARNING_PROSTATE     _T("ProState")//工序的状态 
#define DBOVERTIMEWARNING_PERSONFH     _T("PersonFH")//工序的状态 
#define DBOVERTIMEWARNING_PERSONSH     _T("PersonSH")//工序的状态 

/*==============================表 每日收发统计 ==============================*/
#define DBPRODUCTSTATISTICS_SENDINTIME       _T("SendInTime")     //_T("时间段内发出数量") 
#define DBPRODUCTSTATISTICS_RECVINTIME       _T("RecvInTime")     //_T("时间段内收回数量")
#define DBPRODUCTSTATISTICS_DAYOUTCOUNT      _T("DayOutCount")    //当日发出数量
#define DBPRODUCTSTATISTICS_DAYINCOUNT       _T("DayInCount")     //当日收回数量
#define DBPRODUCTSTATISTICS_MONTHOUTCOUNT    _T("MonthOutCount")  //当月发出数量
#define DBPRODUCTSTATISTICS_MONTHINCOUNT     _T("MonthInCount")   //当月收回数量
#define DBPRODUCTSTATISTICS_OUTCOUNT         _T("OutCount")       //全部收发数量
#define DBPRODUCTSTATISTICS_INCOUNT          _T("InCount")        //全部收发数量

/*==============================表 收发记录 ==============================*/



/*==============================表 部门产量分析 ==============================*/
#define DB_DEPARTMENT_PRODUCT_DATE        _T("dDate")   //日期
#define DB_DEPARTMENT_PRODUCT_SEND_COUNT  _T("SendCount")   //发放件数
#define DB_DEPARTMENT_PRODUCT_RECV_COUNT  _T("RecvCount")   //完成件数
#define DB_DEPARTMENT_PRODUCT_REST_COUNT  _T("RestCount")   //剩余件数





/*==============================表 dbo. ==============================*/
#define DBDesDensity_key_Facecode1		                        _T("cFaceCode1")//拉密
#define DBDesDensity_key_Facecode2		                        _T("cFaceCode2")//拉密
#define DBDesDensity_key_Facecode3		                        _T("cFaceCode3")//拉密
#define DBDesDensity_key_Facecode4		                        _T("cFaceCode4")//拉密

/*==============================表 dbo. ==============================*/

/*==============================表 dbo. ==============================*/

/*==============================表 dbo. ==============================*/