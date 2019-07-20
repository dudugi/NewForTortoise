#pragma once

//数据库表字段,普通表，不包含视图		add by lida 2018/02/05

/*==============================生产款式-原料信息 dbo.StyleGoodsInfo add by lida 2018/06/20==============================*/
//#define DBStyleMetarial_iIsPrimary        _T("iIsPrimary")
//#define DBStyleMetarial_iSortId           _T("iSortId") 
#define DBStyleMetarial_ID                           _T("ID")
#define DBStyleMetarial_cStyleNo                     _T("cStyleNo")
#define DBStyleMetarial_cMaterialNo                  _T("cMaterialNo")
#define DBStyleMetarial_cName                        _T("cName")
#define DBStyleMetarial_cLevel1Type                  _T("cLevel1Type")
#define DBStyleMetarial_cLevel2Type                  _T("cLevel2Type")
#define DBStyleMetarial_cLevel3Type                  _T("cLevel3Type")
#define DBStyleMetarial_cUnit                        _T("cUnit")
#define DBStyleMetarial_fCount                       _T("fCount")
#define DBStyleMetarial_cMemo                        _T("cMemo")
#define DBStyleMetarial_cSupplier                    _T("cSupplier")
#define DBStyleMetarial_fPrice                       _T("fPrice")
#define DBStyleMetarial_fTotalPrice                  _T("fTotalPrice")
#define DBStyleMetarial_cBrand                       _T("cBrand")
#define DBStyleMetarial_cChengFen                    _T("cChengFen")
#define DBStyleMetarial_cPic                         _T("cPic")



/*==============================生产款式-辅料信息 dbo.StyleSupMetarial add by huangym 2018/12/24==============================*/
#define DBStyleSupMetarial_ID                  _T("ID")
#define DBStyleSupMetarial_cName               _T("cName")
#define DBStyleSupMetarial_cStyleNo            _T("cStyleNo")
#define DBStyleSupMetarial_nNumber             _T("nNumber")
#define DBStyleSupMetarial_nPrice              _T("nPrice")
#define DBStyleSupMetarial_nSumPrice           _T("nSumPrice")
#define DBStyleSupMetarial_cMemo               _T("cMemo")

/*==============================生产款式-颜色比重信息 dbo.StyleSupMetarial add by huangym 2018/12/28==============================*/
#define DBStyleColor_ID                    _T("ID")
#define DBStyleColor_nRowNo                   _T("nRowNo")
#define DBStyleColor_nPeiSeNum               _T("nPeiSeNum")
#define DBStyleColor_cStyleNo              _T("cStyleNo")
#define DBStyleColor_cMainClr              _T("cMainClr")
#define DBStyleColor_cFirst               _T("cFirst")
#define DBStyleColor_cSecond               _T("cSecond")
#define DBStyleColor_cThird                _T("cThird")
#define DBStyleColor_cFourth               _T("cFourth")
#define DBStyleColor_cFifth                _T("cFifth")
#define DBStyleColor_cSixth                _T("cSixth")
#define DBStyleColor_nWeight               _T("isWeight")
#define DBStyleColor_cSizeInfo               _T("cSizeInfo")

#define DBStyleColor_RowName              _T("RowName")     //行名称
#define DBStyleColor_ColorName            _T("ColorName")   //色名
#define DBStyleColor_cFirst_Name          _T("cFirstName")
#define DBStyleColor_cSecond_Name          _T("cSecondName")
#define DBStyleColor_cThird_Name           _T("cThirdName")
#define DBStyleColor_cFourth_Name          _T("cFourthName")
#define DBStyleColor_cFifth_Name           _T("cFifthName")
#define DBStyleColor_cSixth_Name           _T("cSixthName")

/*==============================生产款式-商品信息 dbo.StyleGoodsInfo add by lida 2018/06/20==============================*/
#define DBStyleGoosInfo_ID                _T("ID")
#define DBStyleGoosInfo_cStyleNo          _T("cStyleNo")
#define DBStyleGoosInfo_cSizeList         _T("cSizeList")
#define DBStyleGoosInfo_cYarnList         _T("cYarnList")
#define DBStyleGoosInfo_cLingXingList     _T("cLingXingList")
#define DBStyleGoosInfo_cNeedleTypeList   _T("cNeedleTypeList")
#define DBStyleGoosInfo_cDiBianList       _T("cDiBianList")
#define DBStyleGoosInfo_cXiuBianList      _T("cXiuBianList")

/*==============================工序记录详情 dbo.GongxuRecordsDetails ==============================*/
#define DBGongxuRecordsDetails_ID                              _T("ID")
#define DBGongxuRecordsDetails_iAssociatedGongxuRecordsID      _T("iAssociatedGongxuRecordsID")
#define DBGongxuRecordsDetails_iChuguan                        _T("iChuguan")
#define DBGongxuRecordsDetails_iChuweight                      _T("iChuweight")
#define DBGongxuRecordsDetails_iHuiguan                        _T("iHuiguan")
#define DBGongxuRecordsDetails_iHuiweight                      _T("iHuiweight")
#define DBGongxuRecordsDetails_iPianweight                     _T("iPianweight")
#define DBGongxuRecordsDetails_iGuanweight                     _T("iGuanweight")
#define DBGongxuRecordsDetails_cPihao                          _T("cPihao")

/*==============================工序信息分类表 dbo.CommonProInfo ==============================*/
#define CommonProInfo_key_ID			_T("ID")		//ID
#define CommonProInfo_key_Name			_T("cProName")	//工序名称
#define CommonProInfo_key_Intro			_T("cIntro")	//工序信息
#define CommonProInfo_key_Type			_T("cType")		//工序类别

/*==============================价格设置表 dbo.ColorPrice ==============================*/
#define DBPRICESET_KEY_dDate          _T("dDate")       //日期
#define DBPRICESET_KEY_iSunhao        _T("iSunhao")     //损耗
#define DBPRICESET_KEY_iSalePrice     _T("iSalePrice")  //销售单价
#define DBPRICESET_KEY_iPrice         _T("iPrice")      //单价
#define DBPRICESET_KEY_cDaihao        _T("cDaihao")     //品种代号
#define DBPRICESET_KEY_cCate          _T("cCate")       //品种
#define DBPRICESET_KEY_cCusCode       _T("cCusCode")    //客户编号
#define DBPRICESET_KEY_ID             _T("ID")          //ID
#define DBPRICESET_KEY_fZMDSalePrice  _T("fZMDSalePrice") //专卖店零售单价
#define DBPRICESET_KEY_fZhekou        _T("fZhekou")     //折扣
#define DBPRICESET_KEY_cChenfen			  _T("cChenfen")		//成份
#define DBPRICESET_KEY_fBeiLv        _T("fBeiLv")     //倍率   add anjie by 2018/10/25
/*==============================公司信息表 dbo.CompanyInfo ==============================*/
#define DBCompanyInfo_key_Id				_T("ID")
#define DBCompanyInfo_key_Name				_T("Name")
#define DBCompanyInfo_key_Tel				_T("Telephone")
#define DBCompanyInfo_key_Fax				_T("Fax")
#define DBCompanyInfo_key_Address			_T("Address")
#define DBCompanyInfo_key_Sign				_T("Sign")

/*==============================客户信息表 dbo.Customer ==============================*/
#define  DBCustomer_key_ID			_T("ID")					//自增ID
#define  DBCustomer_key_UpdateTime	_T("dDate")					//更新日期
#define  DBCustomer_key_Cate		_T("cCate")					//分类
#define  DBCustomer_key_CusCate		_T("cCusCate")				//客户分类---->从数据
#define  DBCustomer_key_Code		_T("cCusCode")				//客户编码
#define  DBCustomer_key_Name		_T("cCusName")				//客户名称
#define  DBCustomer_key_Abbrev		_T("cCusAbbName")			//客户简称
#define  DBCustomer_key_Addr		_T("cCusAddress")			//客户地址
#define  DBCustomer_key_Person		_T("cCusPerson")			//客户联系人
#define  DBCustomer_key_Phone		_T("cCusPhone")				//客户电话
#define  DBCustomer_key_Fax			_T("cCusFax")				//客户传真
#define  DBCustomer_key_Mobile		_T("cCusMobile")			//客户手机
#define  DBCustomer_key_WeChat		_T("cCusWeixin")			//客户微信
#define  DBCustomer_key_Remark		_T("cCusMemo")				//备注
#define  DBCustomer_key_VenWeb		_T("cVenWeb")				//我的下单平台
#define  DBCustomer_key_VenCode		_T("cVenCode")				//我的下单帐号
#define  DBCustomer_key_VenPwd		_T("cVenPassword")			//我的下单密码
#define  DBCustomer_key_Pwd			_T("cCusPassword")			//登录密码
#define  DBCustomer_key_Arrears		_T("iMoney")				//期初余额
#define  DBCustomer_key_Deposit		_T("iDingjin")				//保证金
#define  DBCustomer_key_Limit		_T("iShangxian")			//欠款上限
#define  DBCustomer_key_Province	_T("cSheng")				//省
#define  DBCustomer_key_City		_T("cShi")					//市
#define  DBCustomer_key_Area		_T("cQuhao")				//区号
#define  DBCustomer_key_State		_T("cState")				//状态
#define  DBCustomer_key_DeliveDays	_T("iDays")					//交货天数
#define  DBCustomer_key_Num			_T("iJianshu")				//件数
#define  DBCustomer_key_Loss		_T("iSunhao")				//损耗
#define  DBCustomer_key_EMS			_T("cKuaidi")				//快递
#define  DBCustomer_key_ParrentCode	_T("cParentCode")			//上级代号
#define  DBCustomer_key_ClerkCode	_T("cUserCode")				//业务员编号
#define  DBCustomer_key_Rebate		_T("cFandian")				//返点
#define  DBCustomer_key_WorkDoc		_T("cJGD")					//默认加工单
#define  DBCustomer_key_Tag			_T("cDP")					//默认吊牌
#define  DBCustomer_key_DeliveDoc	_T("cSHD")					//默认发货单
#define  DBCustomer_key_DepotPos	_T("cCangwei")				//仓位
#define  DBCustomer_key_Sign		_T("cSign")					//签名
#define  DBCustomer_key_Unit		_T("cCusUnit")				//单位
#define  DBCustomer_key_LV			_T("iCusLv")				//等级
#define  DBCustomer_key_iTreeGroupID _T("iTreeGroupID")  //地区分组ID
#define  DBCustomer_key_iJijiaType  _T("iJijiaType")  //销售价计价方式0：表示按折扣；1表示按重量
#define  DBCustomer_key_fAddinPrice    _T("fAddinPrice")    //零售价加价     add by lida 2018/05/24
#define  DBCustomer_key_bPrintDiaoPai  _T("bPrintDiaoPai")  //是否打印吊牌   add by lida 2018/05/24
#define  DBCustomer_key_bPrintYuE      _T("bPrintYuE")      //是否打印余额   add by lida 2018/05/24
#define  DBCustomer_key_fZMZheKou      _T("fZMZheKou")      //专卖折扣 yangjr 2018/8/7
#define  DBCustomer_key_cSalesID       _T("cSalesID")       //业务员ID  add by lida  2018/09/01
/*==============================表 dbo.FieldName ==============================*/
//2017/06/29 zhangt Create 数据库中字段
#define DBDataCol_key_ID			_T("ID")
#define DBDataCol_key_TBName		_T("TableName")
#define DBDataCol_key_Field			_T("FieldName")
#define DBDataCol_key_Show			_T("ShowName")
#define DBDataCol_key_Type			_T("cType")
#define DBDataCol_key_Width			_T("ShowWidth")
#define DBDataCol_key_Fmt			_T("DisplayFormat")
#define DBDataCol_key_LeftShow		_T("ShowLeft")
#define DBDataCol_key_Edit			_T("CanEdit")
#define DBDataCol_key_Sum			_T("SumType")
#define DBDataCol_key_Valid			_T("CanShow")

/*==============================数据字典表 dbo.TreeClass ==============================*/
#define DBDataDic_key_ID			_T("ID")
#define DBDataDic_key_Index			_T("cTreeCate")
#define DBDataDic_key_ItemCode		_T("cTreeCode")
#define DBDataDic_key_ItemName		_T("cTreeName")
#define DBDataDic_key_Description   _T("iMemo1")
#define DBDataDic_key_Value         _T("iMemo2")
#define DBDataDic_key_SysItem		_T("cSysItem") 
#define DBDataDic_key_cSortCode		_T("cSortCode") 

/*==============================全局设置表 dbo.Config ==============================*/
//2017/07/3 zhangt Create 数据库中字段
#define DBGlobalSet_key_ID			_T("ID")
#define DBGlobalSet_key_Name		_T("myName")
#define DBGlobalSet_key_Value		_T("myValue")
#define DBGlobalSet_key_Remark		_T("myMemo")
/*==============================工序方案表 dbo.FangAnGongxu ==============================*/
//工序方案表 数据库中字段
#define	 DBFangAnGongxu_key_ID				_T("ID")			//ID
#define  DBFangAnGongxu_key_cFangAnName		_T("cFangAnName")	//方案名
#define  DBFangAnGongxu_key_cGXName			_T("cGXName")		//工序名
#define  DBFangAnGongxu_key_cZhiPaiPerson _T("cZhiPaiPerson") //指派人
/*==============================日志表 dbo.WorkLog ==============================*/
#define DBWorkLog_key_ID		_T("ID")
#define DBWorkLog_key_Cate		_T("cCate")
#define DBWorkLog_key_Code		_T("cCode")
#define DBWorkLog_key_Date		_T("dDate")
#define DBWorkLog_key_Maker		_T("cMaker")
#define DBWorkLog_key_Type		_T("cType")
#define DBWorkLog_key_Detail	_T("cMemo")
#define DBWorkLog_key_InterFace	_T("cInterFaceName")
#define DBWorkLog_key_ProjectName _T("cProjectName")
#define DBWorkLog_key_MacAddr     _T("cMacAddr")

/*==============================菜单表 dbo.Menus ==============================*/
//数据库中字段
#define DBMenus_key_AutoID			_T("AutoID")
#define DBMenus_key_ID				_T("ID")
#define DBMenus_key_PID				_T("PID")
#define DBMenus_key_SortID			_T("SortID")
#define DBMenus_key_ItemName		_T("ItemName")
#define DBMenus_key_ShowLeft		_T("ShowLeft")
#define DBMenus_key_LeftImg			_T("LeftImg")
#define DBMenus_key_ImgIndex		_T("ImgIndex")
#define DBMenus_key_ImgCate			_T("ImgCate")
#define DBMenus_key_FrmName			_T("FrmName")
#define DBMenus_key_DllName			_T("DllName")
#define DBMenus_key_ItemShow		_T("ItemShow")
#define DBMenus_key_dwTitleBKColor  _T("dwTitleBKColor")

/*==============================表 dbo.Order_Flag ==============================*/
#define	DBORDFLAG_KEY_ID				_T("ID")
#define DBORDFLAG_KEY_OrderCode			_T("OrderCode")
#define DBORDFLAG_KEY_Print_GYD			_T("Print_GYD")
#define DBORDFLAG_KEY_Print_XSM			_T("Print_XSM")
#define DBORDFLAG_KEY_Print_SCZSD		_T("Print_SCZSD")
#define DBORDFLAG_KEY_DownLd_MacFile	_T("DownLd_MacFile")


/*==============================表 dbo.Userinfo ==============================*/
#define DBPerson_key_ID				_T("ID")			//ID 自增
#define DBPerson_key_TreeCode		_T("cTreeCode")		//数据字段对应字段部门编码
#define DBPerson_key_UserID			_T("cUserID")		//用户ID
#define DBPerson_key_Pwd			_T("cPassword")		//用户密码
#define DBPerson_key_UserName		_T("cUserName")		//用户姓名
#define DBPerson_key_UserPower		_T("cUserPower")	//用户权限
#define DBPerson_key_UserTel		_T("cUserTel")		//用户联系方式
#define DBPerson_key_UserDate		_T("cUserDate")		//用户注册时间
#define DBPerson_key_UserBorn		_T("cUserBorn")		//用户生日
#define DBPerson_key_UserMemo		_T("cUserMemo")		//备注
#define DBPerson_key_UserSFZ		_T("cUserSFZ")		//身份证
#define DBPerson_key_UserPhoto		_T("cUserPhoto")	//照片
#define DBPerson_key_UserSale		_T("cUserSale")		//是否跟单员
#define DBPerson_key_UserDuty		_T("cUserDuty")		//身份（员工职位）	
#define DBPerson_key_Addr			_T("cAddr")			//地址
#define DBPerson_key_InTime			_T("dtInTime")		//最后一次登录时间
#define DBPerson_key_OutTime		_T("dtOutTime")		//注销时间
#define DBPerson_key_OutFlag		_T("iOutFlag")		//是否注销
#define DBPerson_key_AttriEx     _T("dwAttriEx")   //扩展属性
#define DBPerson_key_iSalesman   _T("iSalesman")   //业务员
#define DBPerson_key_cUserControlsPermission   _T("cUserControlsPermission")   //用户控件权限
#define DBPerson_key_dwTagPermission            _T("dwTagPermission")//标签权限
#define DBPerson_key_dwFilePermission           _T("dwFilePermission")//文件权限
#define DBPerson_key_cUserRole                  _T("cUserRole")//角色
#define DBPerson_key_cUserGroup                 _T("cUserGroup")//组

/*==============================工序信息表 dbo.Gongxu ==============================*/
//数据库中字段
#define DBProcess_Key_ID			_T("ID")
#define DBProcess_key_Name			_T("cGXName")
#define DBProcess_key_Field			_T("cGJField")
#define DBProcess_key_Item			_T("cGongxuList")
#define DBProcess_key_Choose		_T("cPersonList")
#define DBProcess_key_SortID     _T("iSortID")
#define DBProcess_Key_GetYarn    _T("iFasha")
#define DBProcess_key_CarryOut   _T("iMust")
#define DBProcess_key_EditCost   _T("iCanEditGJ")
#define DBProcess_key_Update     _T("cUpdated")
#define DBProcess_key_PartLimt   _T("cTreeCode")
#define DBProcess_key_PrevPro    _T("cGetPersonGXName")
#define DBProcess_key_Remark     _T("cMemo")	
#define DBProcess_key_SysItem    _T("cProSysItem")
#define DBProcess_key_LimitHour  _T("iLimitHour")
#define DBProcess_key_cZhipaiPerson  _T("cZhipaiPerson") //默认指派人 yangjr 2018/5/9
#define DBProcess_key_nOtherState  _T("nOtherState")     //其他状态组合标志		by WangZY 2018/09/13
#define DBProcess_key_cGXGongJia  _T("cGXGongJia")       //默认工序工价   add anjie by 2018/11/20
#define DBProcess_key_iTipPrice     _T("iTipPrice")      //是否提示修改工价 
#define DBProcess_key_cBindRole     _T("cBindRole")      //绑定的角色  （角色名称）
/*==============================工序信息表 dbo.SampleDesDensity ==============================*/
//数据库密度表中字段
#define DBSampleDesDensity_Key_ID			_T("ID")
#define DBSampleDesDensity_key_Name			_T("cName")
#define DBSampleDesDensity_key_HorDesSrc	_T("fHorDesSrc")
#define DBSampleDesDensity_key_VerDesSrc	_T("fVerDesSrc")
#define DBSampleDesDensity_key_HorDesNew	_T("fHorDesNew")
#define DBSampleDesDensity_key_VerDesNew   _T("fVerDesNew")
#define DBSampleDesDensity_Key_Structure   _T("cStructure")
#define DBSampleDesDensity_key_Material    _T("cMaterial")
#define DBSampleDesDensity_key_Pull        _T("fPull")
#define DBSampleDesDensity_key_PullUnit    _T("cPullUnit")
#define DBSampleDesDensity_key_PullType    _T("iPullType")
#define DBSampleDesDensity_key_Needle      _T("cNeedle")
#define DBSampleDesDensity_key_PieceUnit   _T("fPieceUnit")	
#define DBSampleDesDensity_key_PieceTurns   _T("fPieceTurns")
#define DBSampleDesDensity_key_PieceNeedle  _T("fPieceNeedle")
#define DBSampleDesDensity_key_StartTurns   _T("fStartTurns")
#define DBSampleDesDensity_key_RomanType    _T("cRomanType")
#define DBSampleDesDensity_key_Wire         _T("cWire")
#define DBSampleDesDensity_key_WireTurns    _T("fWireTurns")
#define DBSampleDesDensity_key_WireType     _T("iWireType")
#define DBSampleDesDensity_key_PinBottom    _T("cPinBottom")
#define DBSampleDesDensity_key_PinFace      _T("cPinFace")
#define DBSampleDesDensity_key_PinType      _T("iPinType")
#define DBSampleDesDensity_key_Type         _T("cType")
#define DBSampleDesDensity_key_BaseType     _T("cBaseType")
#define DBSampleDesDensity_key_ShowPZ       _T("iShowPZ")
#define DBSampleDesDensity_key_PZName       _T("cPZName")
#define DBSampleDesDensity_key_SavedUserID  _T("cSavedUserID")
#define DBSampleDesDensity_key_SaveTime     _T("cSaveTime")
#define DBSampleDesDensity_key_Remark       _T("cRemark")
#define DBSampleDesDensity_key_OrderNo      _T("cOrderNo")

/*==============================工序信息表 dbo.SampleDesFaceCode ==============================*/
//数据库面字码表中字段
#define DBSampleDesFceCode_Key_ID			_T("ID")
#define DBSampleDesFceCode_key_Name			_T("cName")
#define DBSampleDesFceCode_key_OldLen	   _T("fOldLen")
#define DBSampleDesFceCode_key_Type	      _T("cType")
#define DBSampleDesFceCode_key_Len	      _T("fLen")
#define DBSampleDesFceCode_key_Unit       _T("cUnit")
#define DBSampleDesFceCode_Key_IDDensity   _T("IDDensity")

/*==============================表 dbo.ProSet_Style ==============================*/
#define DBProSet_Style_key_ID			   _T("ID")    
#define DBProSet_Style_key_StyleNo		_T("cStyleNo")    //款号
#define DBProSet_Style_key_ProName		_T("cProName")    //工序名称
#define DBProSet_Style_key_UserID		_T("cUserID")     //指派人ID
#define DBProSet_Style_key_ProTime		_T("dwProTime")   //默认时长
#define DBProSet_Style_key_fPrice		_T("fPrice")      //工序工价
#define DBProSet_Style_key_cIntro		_T("cIntro")      //说明
#define DBProSet_Style_key_cMark		   _T("cMark")       //默认数据标志   add anjie by 2018/11/22
#define DBProSet_Style_key_cGXMark     _T("cGXMark")     //工序标记 luzw 2018/12/21
#define DBProSet_Style_key_bIsGroup    _T("bIsGroup")     //是否是指派给组的标识 wangzl 2019-7-16

/*==============================部位名称表 dbo.[SizePart] ==============================*/
#define DBSizePart_key_ID           _T("ID")
#define DBSizePart_key_Name         _T("cName")
#define DBSizePart_key_Default      _T("iDefault")
#define DBSizePart_key_UserSort     _T("iUserSort")
#define DBSizePart_key_cMemo     _T("cMemo")
/*==============================表 dbo.VariousStyle ==============================*/
#define DBVarious_key_ID				_T("ID")			//自增ID
#define DBVarious_key_StyleNo			_T("cStyleNo")		//款号
#define DBVarious_key_OrderNo			_T("cOrderNo")		//订单号
#define DBVarious_key_Destribution		_T("cDestribution")	//描述
#define DBVarious_key_Perferred			_T("iPreferred")	//是否首选

/*==============================表 dbo.Color 纱线表==============================*/
#define DBColor_key_ID			   _T("ID")       //纱线表自增ID
#define DBColor_key_Date		   _T("dDate")    //更新日期
#define DBColor_key_Cate		   _T("cCate")    //类别   ->来自数据字典
#define DBColor_key_YarnNo		   _T("cSehao")   //纱线号
#define DBColor_key_YarnName	   _T("cSeming") //纱线名称
#define DBColor_key_Ingredient	_T("cChenfen") //纱线成分
#define DBColor_key_ThickNess	   _T("cShazhi")   //支数
#define DBColor_key_Remark		   _T("cMemo")       //备注
#define DBColor_key_Warning		_T("iYujing")     //锁存数量
#define DBColor_key_RGBValue	   _T("cRGBValue")   //颜色值(DWORD)数据库存储为bigint取后4个字节的数值即可
#define DBColor_key_RGBName		_T("cRGBName")    //颜色名称
#define DBColor_key_Kind		   _T("iKind")       //种类(主料/辅料)
#define DBColor_key_ColorCard	   _T("cColorCard")  //色卡
#define DBColor_key_State		   _T("iState")     //上下架的标识
#define DBColor_key_fKucunYujing	_T("fKucunYujing") //库存预警数量
#define DBColor_key_cGroup       _T("cGroup") //色组 by huangym 2018/12/19
/*==============================表 dbo.ColNameSet ==============================*/
//字段
#define DBDataColSet_Key_ID             _T("ID")
#define DBDataColSet_Key_cTableID     _T("cTableID")
#define DBDataColSet_Key_cFieldID		_T("cFieldID")
#define DBDataColSet_Key_cFieldName     _T("cFieldName")


/*==============================表 dbo.Kuanshi ==============================*/
#define DBKuanShi_key_ID                     _T("ID")             //自增ID
#define DBKuanShi_key_UpdateTime             _T("dDate")          //更新日期
#define DBKuanShi_key_KindName               _T("cTreeName")      //分类
#define DBKuanShi_key_StyleNo                _T("cKuanhao")       //款号
#define DBKuanShi_key_StyleName              _T("cKuanming")      //款名
#define DBKuanShi_key_YarnCate               _T("cYarnCate")      //纱线类别
#define DBKuanShi_key_StyleIntro             _T("cKSMemo")        //款式说明
#define DBKuanShi_key_CreateTime             _T("dtCreatTime")    //订单创建时间
#define DBKuanShi_key_KsYears                _T("KsYears")        //年份
#define DBKuanShi_key_nColorNum              _T("nColorNum")      //配色数
#define DBKuanShi_key_nColorSuitNum          _T("nColorSuitNum")  //配色套数
#define DBKuanShi_key_nIncreaseNum           _T("nIncreaseNum")   //尺码重量递增
#define DBKuanShi_key_cBasicSize             _T("cBasicSize")     //基码
#define DBKuanShi_key_cPinMing  _T("cPinMing")  //品名 yangjr 2018/5/11
// 版房新增款式表数据-----start liuhw 2019/05/08
#define DBKuanShi_key_dtExpireTime           _T("dtExpireTime")            //到期日期
#define DBKuanShi_key_cCreator               _T("cCreator")                //创建人
#define DBKuanShi_key_cCreateType            _T("cCreateType")             //创建类型
#define DBKuanShi_key_cTheme                 _T("cTheme")                  //主题
#define DBKuanShi_key_cCusCode               _T("cCusCode")                //客户
#define DBKuanShi_key_cCusKuanHao            _T("cCusKuanHao")             //客户款号
#define DBKuanShi_key_cProcessStatus         _T("cProcessStatus")          //工序状态
#define DBKuanShi_key_cEdition               _T("cEdition")                //版本
#define DBKuanShi_key_dtMakingOrdTime        _T("dtMakingOrdTime")         //定版日期
#define DBKuanShi_key_cMainMaterial          _T("cMainMaterial")           //主原料
#define DBKuanShi_key_cVersionNum            _T("cVersionNum")             //版单号
#define DBKuanShi_key_cSinglePerson          _T("cSinglePerson")           //制单人
#define DBKuanShi_key_iFollow                _T("iFollow")                 //关注
#define DBKuanShi_key_iShell                 _T("iUpOrDownShell")          //上下架
#define DBKuanShi_key_cMainPic               _T("cMainPic")                //款式的主图  	by WangZY 2019/05/16
#define DBKuanShi_key_bIsDeleted             _T("bIsDeleted")              //款式是否删除 yangjr 2019/05/20
#define DBKuanShi_key_cState                 _T("cState")                  //状态字段  wangzl 2019-5-30
#define DBKuanShi_key_cFangAnName            _T("cFangAnName")             //方案名称  wangzl 2019-6-3
#define DBKuanShi_key_cPriority              _T("cPriority")                //优先级
#define DBKuanShi_key_cNeedleType            _T("cNeedleType")            //针型
#define DBKuanShi_key_cModelMainPic          _T("cModelMainPic")           //展示图的主图  	by Wangzl 2019/06/18
#define DBKuanShi_key_nSortIndex             _T("nSortIndex")              //排序的索引      Wangzl 2019/06/18
#define DBKuanShi_key_iGXSortID              _T("iGXSortID")               //工序的顺序      Wangzl 2019/06/18
#define DBKuanShi_key_cBrand                 _T("cBrand")                  //品牌            wangzl 2019/07/02
#define DBKuanShi_key_cCustomField1          _T("cCustomField1")           //自定义字段1     wangzl 2019/07/02
#define DBKuanShi_key_cCustomField2          _T("cCustomField2")           //自定义字段2     wangzl 2019/07/02
#define DBKuanShi_key_cCustomField3          _T("cCustomField3")           //自定义字段3     wangzl 2019/07/02
#define DBKuanShi_key_cCustomField4          _T("cCustomField4")           //自定义字段4     wangzl 2019/07/02
#define DBKuanShi_key_cCustomField5          _T("cCustomField5")           //自定义字段5     wangzl 2019/07/02
#define DBKuanShi_key_cCustomField6          _T("cCustomField6")           //自定义字段6     wangzl 2019/07/02
#define DBKuanShi_key_cCustomField7          _T("cCustomField7")           //自定义字段7     wangzl 2019/07/02
#define DBKuanShi_key_cCustomField8          _T("cCustomField8")           //自定义字段8     wangzl 2019/07/02
#define DBKuanShi_key_cCustomField9          _T("cCustomField9")           //自定义字段9     wangzl 2019/07/02
#define DBKuanShi_key_cCustomField10         _T("cCustomField10")          //自定义字段10    wangzl 2019/07/02
#define DBKuanShi_key_dTotalCost             _T("dTotalCost")              //总成本 lida 2019/07/12
#define DBKuanShi_key_dTotalOffer            _T("dTotalOffer")             //总报价 lida 2019/07/12
#define DBKuanShi_key_cGxPersonCode          _T("cGxPersonCode")           //工序的执行人    Wangzl 2019/07/13
/*==============================表 dbo.TableNameSet ==============================*/
#define DBTableNameSet_Key_ID                _T("ID")
#define DBTableNameSet_Key_cTableName        _T("cTableName")
#define DBTableNameSet_Key_cTableID          _T("cTableID")

/*==============================表 dbo.PieceInfo ==============================*/
#define DBPieceInfo_Key_ID                   _T("ID")
#define DBPieceInfo_Key_cCode                _T("cCode")
#define DBPieceInfo_Key_nPieceType           _T("nPieceType")
#define DBPieceInfo_Key_cPieceName           _T("cPieceName")
#define DBPieceInfo_Key_cRemark              _T("cRemark")

//DB_TABLE_STYLE_GLOBAL_SET 表格样式全局设置
/*==============================表 dbo.TableStyleGlobalSet ==============================*/
#define DBTableStyleGlobalSet_key_ID                    _T("ID")
#define DBTableStyleGlobalSet_key_cXmlFileName          _T("cXmlFileName")
#define DBTableStyleGlobalSet_key_cXmlDesc              _T("cXmlDesc")
#define DBTableStyleGlobalSet_key_cInitSettingXmlFile   _T("cInitSettingXmlFile")
#define DBTableStyleGlobalSet_key_cRealTimeXmlFile      _T("cRealTimeXmlFile")
#define DBTableStyleGlobalSet_key_dUpdateTime           _T("dUpdateTime")

/*==============================表 dbo.PinZhongSetting ==============================*/
// add by yangjr 2018/04/17
#define DBPinZhongSetting_ID		      _T("ID")
#define DBPinZhongSetting_cCate	      _T("cCate")	//纱线类别
#define DBPinZhongSetting_cChenfen		_T("cChenfen")	//纱线成份
#define DBPinZhongSetting_fSalePrice		_T("fSalePrice")	//销售单价
#define DBPinZhongSetting_cZhiXingBiaoZun		_T("cZhiXingBiaoZun")	//执行标准
#define DBPinZhongSetting_fFahuoSunhao		_T("fFahuoSunhao")	//发货损耗
#define DBPinZhongSetting_fShoufaMaxSunhao		_T("fShoufaMaxSunhao")	//收发最大损耗(kg)
#define DBPinZhongSetting_isKoukuan		_T("isKoukuan")	//超过最大损耗扣款
#define DBPinZhongSetting_fZMDSalePrice		_T("fZMDSalePrice")	//专卖店销售单价
#define DBPinZhongSetting_fZhekou		_T("fZhekou")	//折扣
#define DBPinZhongSetting_fKouKuanPrice		_T("fKouKuanPrice")	//扣款金额
#define DBPinZhongSetting_fPWeight      _T("fPWeight")         //去皮重量
#define DBPinZhongSetting_cProductName _T("cProductName")      //产品名称
#define DBPinZhongSetting_fBelLv       _T("fBelLv")            //倍率   add anjie by 2018/10/25
#define DBPinZhongSetting_cYarnCode    _T("cYarnCode")         //纱线代号 add liuhw by 2018/11/11
#define DBPinZhongSetting_IsOuterYarn      _T("IsOuterYarn")  //外来纱线 add by lida 2019/03/06
#define DBPinZhongSetting_cPrintYarn    _T("cPrintYarn")      //打印纱线 add anjie by 2019/03/30
#define DBPinZhongSetting_cChengBenPrice    _T("cChengBenPrice")      //成本单价
//DB_TABLE_ORDER_TYPE_PRICE_SET

/*==============================表 dbo.FangAn_Power anjie 2018-06-06==============================*/
#define  DBFangAn_Power_Key_ID          _T("ID")
#define  DBFangAn_Power_Key_FangAnName  _T("cFangAnName")      //方案名
#define  DBFangAn_Power_Key_FangAnPower _T("cFangAnPower")     //方案权限编码
#define  DBFangAn_Power_Key_Num _T("cNum")             //方案排序编号


/*==============================物料表 dbo.MaterielInfo WangZY 2018/08/01==============================*/
#define  DBMateriel_Key_ID                _T("ID")             //物料编号
#define  DBMateriel_Key_cName             _T("cName")             //物类名称
#define  DBMateriel_Key_cLevel1Type       _T("cLevel1Type")       //物料一级类别
#define  DBMateriel_Key_cLevel2Type       _T("cLevel2Type")       //物类二级类别
#define  DBMateriel_Key_cLevel3Type       _T("cLevel3Type")       //物料三级类别
#define  DBMateriel_Key_cLevel4Type       _T("cLevel4Type")       //物类四级类别
#define  DBMateriel_Key_cLevel5Type       _T("cLevel5Type")       //物料五级类别
#define  DBMateriel_Key_cUnit             _T("cUnit")             //物类单位
#define  DBMateriel_Key_cChengFen         _T("cChengFen")         //物料材质(成份)
#define  DBMateriel_Key_cMemo             _T("cMemo")             //物类说明
#define  DBMateriel_Key_cPic              _T("cPic")              //物类图片
#define  DBMateriel_Key_cPrice              _T("nPrice")              //物类图片
#define  DBMateriel_Key_cBrand              _T("cBrand")              //物类图片
#define  DBMateriel_Key_cSupplier         _T("cSupplier")         //供应商
/*==============================文件表 dbo.F_FileInfo Wangzl 2018/08/20==============================*/
#define  DBFileInfo_Key_ID                _T("ID")                //ID
#define  DBFileInfo_Key_cRelativePath     _T("cRelativePath")     //文件的路径
#define  DBFileInfo_Key_cUploadUserID     _T("cUploadUserID")     //上传用户ID
#define  DBFileInfo_Key_cUploadTime       _T("cUploadTime")       //上传时间
#define  DBFileInfo_Key_cFileMD5          _T("cFileMD5")          //MD5值
#define  DBFileInfo_Key_cFileName         _T("cFileName")         //文件名
#define  DBFileInfo_Key_cFileExtension    _T("cFileExtension")    //文件后缀
#define  DBFileInfo_Key_nFileSize         _T("nFileSize")         //文件大小
#define  DBFileInfo_Key_cRemark           _T("cRemark")           //说明/备注

/*============================== 波段信息表 dbo.P_BindInfo anjie 2018/08/21==============================*/
#define DBP_BindInfo_Key_ID                        _T("ID")
#define DBP_BindInfo_Key_cSeriaNum                 _T("cSeriaNum")               //序号
#define DBP_BindInfo_Key_cName                     _T("cName")                   //名称
#define DBP_BandInfo_Key_cBindStartTime            _T("cBandStartTime")          //波段开始时间
#define DBP_BindInfo_Key_cDesignEndTime            _T("cDesignEndTime")          //设计完成时间
#define DBP_BindInfo_Key_cPatternEndTime           _T("cPatternEndTime")         //纸样完成时间
#define DBP_BindInfo_Key_cReviewEndTime            _T("cReviewEndTime")          //内审会完成时间
#define DBP_BindInfo_Key_cBandEndTime              _T("cBandEndTime")            //波段结束时间
#define DBP_BindInfo_Key_cDeliveryStartTime        _T("cDeliveryStartTime")      //货期起始时间
#define DBP_BindInfo_Key_cDeliveryEndTime          _T("cDeliveryEndTime")        //货期结束时间
#define DBP_BindInfo_Key_cShelvesTime              _T("cShelvesTime")            //上货日
#define DBP_BindInfo_Key_cStylish                  _T("cStylish")                //风格
#define DBP_BindInfo_Key_cColor                    _T("cColor")                  //色系
#define DBP_BindInfo_Key_cCreateUserID             _T("cCreateUserID")           //创建人
#define DBP_BindInfo_Key_cCreateUserTime           _T("cCreateUserTime")         //创建时间
#define DBP_BindInfo_Key_bCheckState               _T("bCheckState")             //审核标识
#define DBP_BindInfo_Key_cCheckUserID              _T("cCheckUserID")            //审核人
#define DBP_BindInfo_Key_cCheckTime                _T("cCheckTime")              //审核时间
#define DBP_BindInfo_Key_cRemark                   _T("cRemark")                 //备注
#define DBP_BindInfo_Key_nAssociatedProgrammingID _T("nAssociatedProgrammingID")// 所属商品规划的ID

/*==============================颜色信息表 dbo.P_ColorInfo anjie 2018/08/21==============================*/
#define DBP_ColorInfo_Key_ID                       _T("ID")                 //ID
#define DBP_ColorInfo_Key_nType                    _T("nType")              //类型    区分是企划还是波段的信息
#define DBP_ColorInfo_Key_nAssociatedID            _T("nAssociatedID")      //关联ID
#define DBP_ColorInfo_Key_nColorType               _T("nColorType")         //颜色类型 区分是主色还是配色  都可以拥有多个
#define DBP_ColorInfo_Key_nAssociatedColorID       _T("nAssociatedColorID") //关联的颜色ID

/*==============================物料信息 dbo.P_MatetialInfo anjie 2018/08/21==============================*/
#define DBP_MatetialInfo_Key_ID                       _T("ID")                      //ID
#define DBP_MatetialInfo_Key_nType                    _T("nType")                   //类型    区分是企划还是波段的信息
#define DBP_MatetialInfo_Key_nAssociatedID            _T("nAssociatedID")           //关联ID
#define DBP_MatetialInfo_Key_nAssociatedMaterialID    _T("nAssociatedMaterialID")   //关联物料ID

/*==============================图片信息 dbo.P_PictureInfo anjie 2018/08/21==============================*/
#define DBP_PictureInfo_Key_ID                        _T("ID")                      //ID
#define DBP_PictureInfo_Key_nType                     _T("nType")                   //类型
#define DBP_PictureInfo_Key_nAssociatedID             _T("nAssociatedID")           //关联ID
#define DBP_PictureInfo_Key_nPicType                  _T("nPicType")                // 图片类型    区分是 记录故事版（1）  款式参考图（n） 波段搭配（n）  元素风格工艺（n）
#define DBP_PictureInfo_Key_nAssociatedFileID         _T("nAssociatedFileID")       //关联文件ID
#define DBP_PictureInfo_Key_cRemark                   _T("cRemark")                 //说明

/*==============================主题企划表 dbo.P_Planning anjie 2018/08/21==============================*/
#define DBP_Planning_Key_ID                           _T("ID")                      //ID
#define DBP_Planning_Key_nYears                       _T("nYears")                  //年度
#define DBP_Planning_Key_cSeason                      _T("cSeason")                 //季节
#define DBP_Planning_Key_cSubjectName                 _T("cSubjectName")            //主题名
#define DBP_Planning_Key_cBrand                       _T("cBrand")                  //品牌
#define DBP_Planning_Key_cRemark                      _T("cRemark")                 //主题备注
#define DBP_Planning_Key_bCheckState                  _T("bCheckState")             //审核标识
#define DBP_Planning_Key_cCreateUserID                _T("cCreateUserID")           //创建人
#define DBP_Planning_Key_cCreateTime                  _T("cCreateTime")             //创建时间
#define DBP_Planning_Key_cLastActTime                 _T("cLastActTime")            //最后操作时间
#define DBP_Planning_Key_cCheckUserID                 _T("cCheckUserID")            //审核人
#define DBP_Planning_Key_cCheckTime                   _T("cCheckTime")              //审核时间

/*==============================产品结构规划 dbo.P_ProductStructurePlanning anjie 2018/08/21==============================*/
#define DBP_ProductStructurePlanning_Key_ID                                   _T("ID")                           //
#define DBP_ProductStructurePlanning_Key_cClassification                      _T("cClassification")              //分类    
#define DBP_ProductStructurePlanning_Key_cCategory                            _T("cCategory")                    //品类    
#define DBP_ProductStructurePlanning_Key_nPieceNum                            _T("nPieceNum")                    //件数    
#define DBP_ProductStructurePlanning_Key_cColor                               _T("cColor")                       //色号    
#define DBP_ProductStructurePlanning_Key_cSize                                _T("cSize")                        //尺码    
#define DBP_ProductStructurePlanning_Key_cFabric                              _T("cFabric")                      //面料    
#define DBP_ProductStructurePlanning_Key_cFashion                             _T("cFashion")                     //造型风格
#define DBP_ProductStructurePlanning_Key_cContour                             _T("cContour")                     //廓形    
#define DBP_ProductStructurePlanning_Key_fPrice_Ceiling                       _T("fPrice_Ceiling")               //价格上限
#define DBP_ProductStructurePlanning_Key_fPrice_Floor                         _T("fPrice_Floor")                 //价格下限
#define DBP_ProductStructurePlanning_Key_fPrice_Tag                           _T("fPrice_Tag")                   //吊牌价  
#define DBP_ProductStructurePlanning_Key_cRemark                              _T("cRemark")                      //备注    
#define DBP_ProductStructurePlanning_Key_cBand_Name                           _T("cBand_Name")                   //名称
#define DBP_ProductStructurePlanning_Key_cBand_BandStartTime                  _T("cBand_BandStartTime")          //波段开始时间   
#define DBP_ProductStructurePlanning_Key_cBand_DesignEndTime                  _T("cBand_DesignEndTime")          //设计完成时间   
#define DBP_ProductStructurePlanning_Key_cBand_PatternEndTime                 _T("cBand_PatternEndTime")         //纸样完成时间   
#define DBP_ProductStructurePlanning_Key_cBand_ReviewEndTime                  _T("cBand_ReviewEndTime")          //内审会完成时间
#define DBP_ProductStructurePlanning_Key_cBand_BandEndTime                    _T("cBand_BandEndTime")            //波段结束时间
#define DBP_ProductStructurePlanning_Key_cBand_DeliveryStartTime              _T("cBand_DeliveryStartTime")      //货期起始时间
#define DBP_ProductStructurePlanning_Key_cBand_DeliveryEndTime                _T("cBand_DeliveryEndTime")        //货期结束时间
#define DBP_ProductStructurePlanning_Key_cBand_ShelvesTime                    _T("cBand_ShelvesTime")            //上货日
#define DBP_ProductStructurePlanning_Key_cBand_Stylish                        _T("cBand_Stylish")                //风格
#define DBP_ProductStructurePlanning_Key_cBand_Color                          _T("cBand_Color")                  //色系
#define DBP_ProductStructurePlanning_Key_cCreateUserID                        _T("cCreateUserID")                //创建人
#define DBP_ProductStructurePlanning_Key_cCreateTime                          _T("cCreateTime")                  //创建时间
#define DBP_ProductStructurePlanning_Key_nCreateFlag                          _T("nCreateFlag")                  //创建来源  用于记录是直接创建的产品  还是通过波段创建的产品
#define DBP_ProductStructurePlanning_Key_cProgramming_Brand                   _T("cProgramming_Brand")           //品牌
#define DBP_ProductStructurePlanning_Key_cProgramming_Years                   _T("cProgramming_Years")           //年度
#define DBP_ProductStructurePlanning_Key_cProgramming_Season                  _T("cProgramming_Season")          //季节
#define DBP_ProductStructurePlanning_Key_cProgramming_TradeFairTime           _T("cProgramming_TradeFairTime")   //订货会时间
#define DBP_ProductStructurePlanning_Key_cProgramming_Area                    _T("cProgramming_Area")            //区域
#define DBP_ProductStructurePlanning_Key_cPlanning_SubjectName                _T("cPlanning_SubjectName")        //主题名
#define DBP_ProductStructurePlanning_Key_bSubmitState                         _T("bSubmitState")                 //提交状态
#define DBP_ProductStructurePlanning_Key_cSubmitUserID                        _T("cSubmitUserID")                //提交人
#define DBP_ProductStructurePlanning_Key_cSubmitTime                          _T("cSubmitTime")                  //提交时间
#define DBP_ProductStructurePlanning_Key_cCheckUserID                         _T("cCheckUserID")                 //审核人
#define DBP_ProductStructurePlanning_Key_cCheckTime                           _T("cCheckTime")                   //审核时间
#define DBP_ProductStructurePlanning_Key_bCheckState                          _T("bCheckState")                  //审核状态
#define DBP_ProductStructurePlanning_Key_nCurProSort                          _T("nCurProSort")                  //当前流程所属
#define DBP_ProductStructurePlanning_Key_bRevision                            _T("bRevision")                    //改版标识
#define DBP_ProductStructurePlanning_Key_cRevisionReason                      _T("cRevisionReason")              //改版原因

/*==============================商品规划表 dbo.P_Programming anjie 2018/08/21==============================*/
#define DBP_Programming_Key_ID                             _T("ID")                       //ID
#define DBP_Programming_Key_cBrand                         _T("cBrand")                   //品牌
#define DBP_Programming_Key_nYears                         _T("nYears")                   //年度
#define DBP_Programming_Key_cSeason                        _T("cSeason")                  //季节
#define DBP_Programming_Key_cTradeFairTime                 _T("cTradeFairTime")           //订货会时间
#define DBP_Programming_Key_cArea                          _T("cArea")                    //区域
#define DBP_Programming_Key_nAssociatedPlanningID          _T("nAssociatedPlanningID")    //所属企划ID
#define DBP_Programming_Key_cCreateUserID                  _T("cCreateUserID")            //创建人ID   

/*==============================文字信息表 dbo.P_TextBoard anjie 2018/08/21==============================*/
#define DBP_TextBoard_Key_ID                       _T("ID") 
#define DBP_TextBoard_Key_nType                    _T("nType")                            //类型
#define DBP_TextBoard_Key_nAssociatedID            _T("nAssociatedID")                    //关联ID
#define DBP_TextBoard_Key_cTextInfo                _T("cTextInfo")                        //文字板

/*==============================产品版本信息表 dbo.P_ProductVersions wangzl 2018/08/22==============================*/
#define DBP_ProductVersions_Key_ID                 _T("ID")
#define DBP_ProductVersions_Key_nProductID         _T("nProductID")                       //产品
#define DBP_ProductVersions_Key_cVersion           _T("cVersion")                         //版本
#define DBP_ProductVersions_Key_nVersionNo         _T("nVersionNo")                       //版本号
#define DBP_ProductVersions_Key_cCode              _T("cCode")                            //订单号
#define DBP_ProductVersions_Key_cAlias             _T("cAlias")                           //别名

/*==============================打样工序流程表 dbo.P_ProcessRecords wangzl 2018/08/22==============================*/
#define DBP_ProcessRecords_Key_ID                     _T("ID")                               //
#define DBP_ProcessRecords_Key_nAssociatedProductID   _T("nAssociatedProductID")             //关联的产品ID
#define DBP_ProcessRecords_Key_cReceiveUserID         _T("cReceiveUserID")                   //接收人
#define DBP_ProcessRecords_Key_cSponsorID             _T("cSponsorID")                       //任务发起人
#define DBP_ProcessRecords_Key_nProcessType           _T("nProcessType")                     //对应的工序
#define DBP_ProcessRecords_Key_cInitiateTime          _T("cInitiateTime")                    //任务发起时间
#define DBP_ProcessRecords_Key_cRealStartTime         _T("cRealStartTime")                   //任务实际开始时间
#define DBP_ProcessRecords_Key_cFinishTime            _T("cFinishTime")                      //任务完成时间
#define DBP_ProcessRecords_Key_nState                 _T("nState")                           //状态
#define DBP_ProcessRecords_Key_nCheckState            _T("nCheckState")                      //审核

/*==============================颜色维护表 dbo.ColorMaintain liuhw 2018/08/20==============================*/
#define  DBColorMaintain_Key_ID                _T("ID")             //颜色ID
#define  DBColorMaintain_Key_cClrName             _T("cClrName")          //颜色名称
#define  DBColorMaintain_Key_cClrCode              _T("cClrCode")           //颜色编号
#define  DBColorMaintain_Key_cClrRGB              _T("cClrRGB")           //颜色RGB
#define  DBColorMaintain_Key_cMemo             _T("cMemo")          //物类说明

/*==============================产品任务安排表 dbo.P_ProductTaskAssign wangzl 2018/08/25==============================*/
#define  DBP_ProductTaskAssign_Key_ID                       _T("ID")                   //
#define  DBP_ProductTaskAssign_Key_nAssociatedProductID     _T("nAssociatedProductID") //关联产品ID
#define  DBP_ProductTaskAssign_Key_nPersonType              _T("nPersonType")          //人员的类型
#define  DBP_ProductTaskAssign_Key_cAssignUserID            _T("cAssignUserID")        //被指派人的ID
#define  DBP_ProductTaskAssign_Key_cAllotUserID             _T("cAllotUserID")         //安排人的ID
#define  DBP_ProductTaskAssign_Key_cAllotTime               _T("cAllotTime")           //安排时间

/*==============================打样工序表 dbo.P_ProductProcess wangzl 2018/08/27==============================*/
#define  DBP_ProductProcess_Key_ID                          _T("ID")                   //
#define  DBP_ProductProcess_Key_cProcessName                _T("cProcessName")         //工序名
#define  DBP_ProductProcess_Key_nSortID                     _T("nSortID")              //排序ID
#define  DBP_ProductProcess_Key_nProcessType                _T("nProcessType")         //该记录所对应的工序类型

/*==============================改版记录表 dbo.P_ProductRevisionRecords wangzl 2018/08/31==============================*/
#define  DBP_ProductRevisionRecords_Key_ID                       _T("ID")                     //
#define  DBP_ProductRevisionRecords_Key_nAssociatedProductID     _T("nAssociatedProductID")   //关联产品ID
#define  DBP_ProductRevisionRecords_Key_cVersion                 _T("cVersion")               //大版本号
#define  DBP_ProductRevisionRecords_Key_nVersionNo               _T("nVersionNo")             //版本号
#define  DBP_ProductRevisionRecords_Key_cCode                    _T("cCode")                  //关联单号
#define  DBP_ProductRevisionRecords_Key_cAlias                   _T("cAlias")                 //版本别名
#define  DBP_ProductRevisionRecords_Key_cSponsor                 _T("cSponsor")               //发起人
#define  DBP_ProductRevisionRecords_Key_cRecordTime              _T("cRecordTime")            //发起时间
#define  DBP_ProductRevisionRecords_Key_cRevisionType            _T("cRevisionType")          //改版类型
#define  DBP_ProductRevisionRecords_Key_cRevisionReason          _T("cRevisionReason")        //改版原因
#define  DBP_ProductRevisionRecords_Key_cLastRecordProcess       _T("cLastRecordProcess")     //最后操作工序
#define  DBP_ProductRevisionRecords_Key_nCheckState              _T("nCheckState")            //审核状态
#define  DBP_ProductRevisionRecords_Key_nCheckResult             _T("nCheckResult")           //审核结果
#define  DBP_ProductRevisionRecords_Key_cCheckUserID             _T("cCheckUserID")           //审核人
#define  DBP_ProductRevisionRecords_Key_cCheckTime               _T("cCheckTime")             //审核时间
#define  DBP_ProductRevisionRecords_Key_cCheckOpinion            _T("cCheckOpinion")          //审核意见

/*===================用户登录信息表 dbo.ClientVarifyIno WangZY 2018/09/04==============================*/
#define DB_ClientVarifyIno_Key_ID               _T("ID")             //ID
#define DB_ClientVarifyIno_Key_UserId           _T("UserId")         //用户ID
#define DB_ClientVarifyIno_Key_VarifyTime       _T("VarifyTime")     //时间
#define DB_ClientVarifyIno_Key_MacInfo          _T("MacInfo")        //机器信息


/*==============================子单工序记录表 dbo.ProcessRecords  wangzl 2018-10-08==============================*/
#define DBProcessRecords_Key_ID                _T("ID")
#define DBProcessRecords_Key_cCode             _T("cCode")
#define DBProcessRecords_Key_cGXName           _T("cGXName")
#define DBProcessRecords_Key_cPersonCode       _T("cPersonCode")
#define DBProcessRecords_Key_cMemo             _T("cMemo")
#define DBProcessRecords_Key_iState            _T("iState")

#define DBProcessRecords_Key_iPieceWeight       _T("iPieceWeight")//片重
#define DBProcessRecords_Key_iDuration          _T("iDuration")//时长 小时（1位小数）
#define DBProcessRecords_Key_iGongjia           _T("iGongjia")//工价
#define DBProcessRecords_Key_dRecordTime        _T("dRecordTime")//记录的时间
#define DBProcessRecords_Key_cToPerson          _T("cToPerson")//一些操作锁对应的人员

/*==============================标准尺码表 dbo.StandardSize ==============================*/
#define DBStandardSize_key_ID			                                      _T("ID")		                            // 自增ID
#define DBStandardSize_key_cName			                                   _T("cName")		                         // 名称
#define DBStandardSize_key_cSavetime			                             _T("cSaveTime")		                      // 保存时间
#define DBStandardSize_key_cMark			                                   _T("cMark")		                         // 说明

/*==============================标准尺码表 dbo.StandardSizeModify ==============================*/
#define DBStandardSizeModify_key_ID			                                _T("ID")		                               // 自增ID
#define DBStandardSizeModify_key_nSizeID			                          _T("nID")		                               // 名称ID
#define DBStandardSizeModify_key_cSize			                             _T("cSize")		                            // 尺寸
#define DBStandardSizeModify_key_cPosition			                       _T("cPosition")		                         // 部位
#define DBStandardSizeModify_key_nNumber			                          _T("nNumber")		                         // 数值
#define DBStandardSizeModify_key_cMemo			                             _T("cMemo")		                         // 说明
/*==============================标准尺码表 dbo.StandardSize_Pinming ==============================*/
#define DBStandardSizePinming_key_ID			                                _T("ID")		                            // 自增ID
#define DBStandardSizePinming_key_cStandardSize		                          _T("cStandardSize")		                // 方案名
#define DBStandardSizePinming_key_cPinMing			                          _T("cPinMing")		                      // 品名

/*==============================小图管理表 dbo.SmallPic ==============================*/
#define DBSmallPic_key_ID			          _T("ID")		            //自增ID
#define DBSmallPic_key_Name	    	       _T("cName")		         //名称
#define DBSmallPic_key_iWidth	             _T("iWidth")              //宽度
#define DBSmallPic_key_iHeight	          _T("iHeight")             //高度
#define DBSmallPic_key_Type		          _T("cModelType")			   //小图自定义类型
#define DBSmallPic_key_cSavedUserID        _T("cSavedUserID")        //保存人
#define DBSmallPic_key_cSaveTime           _T("cSaveTime")           //保存时间
#define DBSmallPic_key_cRemark             _T("cRemark")             //说明
#define DBSmallPic_key_cSmallDetailPic     _T("cSmallDetailPic")     //预览图片
#define DBSmallPic_key_bLoop               _T("bLoop")               //最小循环
#define DBSmallPic_key_bKeepLine           _T("bKeepLine")           //保存辅助线
#define DBSmallPic_key_cContact            _T("cContact")            //联系方式

/*==============================部件库管理表 dbo.DesignDataLib ==============================*/
#define DBDesignDataLib_key_ID			                    _T("ID")		             // 自增ID
#define DBDesignDataLib_key_Name	    	                    _T("cName")		          // 名称
#define DBDesignDataLib_key_cSavedUserID                   _T("cSavedUserID")        // 保存人
#define DBDesignDataLib_key_cSaveTime                      _T("cSaveTime")           // 保存时间
#define DBDesignDataLib_key_cData                          _T("cData")               // 保存数据（留给文件名）
#define DBDesignDataLib_key_cLibType                       _T("cLibType")            // 库名称 衣片 辅助线 形状
#define DBDesignDataLib_key_cPosition                      _T("cPosition")           // 部位
#define DBDesignDataLib_key_bSymmetricByHor                _T("bSymmetricByHor")     // 水平
#define DBDesignDataLib_key_bSymmetricByPer                _T("bSymmetricByPer")     // 垂直
#define DBDesignDataLib_key_bUseExpre                      _T("bUseExpre")           // 应用公式
#define DBDesignDataLib_key_bUseLine                       _T("bUseLine")            // 应用辅助线
#define DBDesignDataLib_key_bMark                          _T("bMark")               // 记号文字
#define DBDesignDataLib_key_bMatchPiece                    _T("bMatchPiece")         // 配套衣片
#define DBDesignDataLib_key_nLength                        _T("nLength")             // 身长
#define DBDesignDataLib_key_nBust                          _T("nBust")               // 胸围 
#define DBDesignDataLib_key_nShoulderWidth                 _T("nShoulderWidth")      // 肩宽
#define DBDesignDataLib_key_nCollarWidth                   _T("nCollarWidth")        // 领宽
#define DBDesignDataLib_key_nCollarHeight                  _T("nCollarHeight")       // 领高
#define DBDesignDataLib_key_nFront                         _T("nFront")              // 前胸宽
#define DBDesignDataLib_key_nBehind                        _T("nBehind")             // 后背宽
#define DBDesignDataLib_key_nMidWidth                      _T("nMidWidth")           // 中腰宽
#define DBDesignDataLib_key_nMidHeight                     _T("nMidHeight")          // 中腰高
#define DBDesignDataLib_key_nBellowWidth                   _T("nBellowWidth")        // 下摆宽
#define DBDesignDataLib_key_nBellowHeight                  _T("nBellowHeight")       // 下摆高
#define DBDesignDataLib_key_nShoulderSlanting              _T("nShoulderSlanting")   // 肩斜
#define DBDesignDataLib_key_nShoulder                      _T("nShoulder")           // 挂肩
#define DBDesignDataLib_key_nShoulderHeight                _T("nShoulderHeight")     // 挂肩收针高
#define DBDesignDataLib_key_nShoudlerHor                   _T("nShoudlerHor")        // 挂肩平收
#define DBDesignDataLib_key_nFrontDeep                     _T("nFrontDeep")          // 前领深
#define DBDesignDataLib_key_nBehindDeep                    _T("nBehindDeep")         // 后领深
#define DBDesignDataLib_key_nSleeveLength                  _T("nSleeveLength")       // 袖长
#define DBDesignDataLib_key_nSleeveWidth                   _T("nSleeveWidth")        // 袖宽
#define DBDesignDataLib_key_cTomid                         _T("cTomid")              // 袋距中
#define DBDesignDataLib_key_cToTop                         _T("cToTop")              // 袋距顶
#define DBDesignDataLib_key_cWidth1                        _T("cWidth1")             // 袋宽1
#define DBDesignDataLib_key_cWidth2                        _T("cWidth2")             // 袋宽2
#define DBDesignDataLib_key_cHeight1                       _T("cHeight1")            // 袋高1
#define DBDesignDataLib_key_cHeight2                       _T("cHeight2")            // 袋高2
#define DBDesignDataLib_key_cTotalHeight                   _T("cTotalHeight")        // 总袋高
#define DBDesignDataLib_key_cTotalWidth                    _T("cTotalWidth")         // 总袋宽

/*==============================控件权限表 dbo.ControlsPermission wangzl 2019-2-18==============================*/
#define DBControlsPermission_Key_ID             _T("ID")
#define DBControlsPermission_Key_nDlgID         _T("nDlgID")//对话框ID
#define DBControlsPermission_Key_nDlgFlag       _T("nDlgFlag")//对话框自定义标志
#define DBControlsPermission_Key_nControlID     _T("nControlID")//控件ID
#define DBControlsPermission_Key_nControlType   _T("nControlType")//控件类型
#define DBControlsPermission_Key_cDescription   _T("cDescription")//说明

/*==============================用户款式权限表 dbo.User_StylePermission wangzl 2019-05-06==============================*/
#define DBUserStylePermission_Key_ID               _T("ID")
#define DBUserStylePermission_Key_UID              _T("UID")         //用户ID
#define DBUserStylePermission_Key_SID              _T("SID")         //款式ID
#define DBUserStylePermission_Key_nPermission      _T("nPermission") //权限
#define DBUserStylePermission_Key_cPermissionTime  _T("cPermissionTime") //权限有效期

/*==============================款式原辅料表    表名未知：：dbo.StyleMaterielInfo WangZY 2019/05/06==============================*/
#define DBStyleMaterial_Key_ID                _T("ID")                    //ID
#define DBStyleMaterial_Key_cStyleNo          _T("cStyleNo")              //款号
#define DBStyleMaterial_Key_cMaterialNo       _T("cMaterialNo")           //物料编号
#define DBStyleMaterial_Key_cName             _T("cName")                 //物料名称
#define DBStyleMaterial_Key_cLevel1Type       _T("cLevel1Type")           //大类别   
#define DBStyleMaterial_Key_cLevel2Type       _T("cLevel2Type")           //中类别
#define DBStyleMaterial_Key_cLevel3Type       _T("cLevel3Type")           //小类别
#define DBStyleMaterial_Key_cUnit             _T("cUnit")                 //物料单位
#define DBStyleMaterial_Key_fCount            _T("fCount")                //物料数量
#define DBStyleMaterial_Key_cMemo             _T("cMemo")                 //物料说明
#define DBStyleMaterial_Key_cSupplier         _T("cSupplier")             //供应商
#define DBStyleMaterial_Key_cPic              _T("cPic")                  //物料图片
#define DBStyleMateriel_Key_fPrice            _T("fPrice")                //物料单价
#define DBStyleMateriel_Key_fTotalPrice       _T("fTotalPrice")           //物料总价
#define DBStyleMaterial_Key_cBrand            _T("cBrand")                //物料品牌
#define DBStyleMaterial_Key_cChengFen         _T("cChengFen")             //物料材质(成份)


/*==============================款式尺寸信息表  dbo.Style_Size liuhw 2019/05/06==============================*/
#define DBStyleSize_Key_ID       _T("ID")
#define DBStyleSize_Key_cKuanhao _T("cKuanhao")
#define DBStyleSize_Key_cChima   _T("cChima")
#define DBStyleSize_Key_iPartID  _T("iPartID") //部位ID
#define DBStyleSize_Key_fSize    _T("fSize")   //尺寸数据
#define DBStyelSize_Key_cFangAn  _T("cFangAn")//尺寸方案名
/*==============================款式尺码信息表  dbo.Style_Chima liuhw 2019/05/06==============================*/
#define DBStyleChiMa_Key_ID       _T("ID")
#define DBStyleChiMa_Key_cKuanhao _T("cKuanhao")
#define DBStyleChiMa_Key_cChima   _T("cChima")
#define DBStyleChiMa_Key_iBase    _T("iBase")   //是否为基码

/*==============================款式检入检出记录表  dbo.Style_CheckRecords wantzl 2019/05/19==============================*/
#define DBStyle_CheckRecords_ID           _T("ID")
#define DBStyle_CheckRecords_SID          _T("SID")
#define DBStyle_CheckRecords_cPerson      _T("cPerson")
#define DBStyle_CheckRecords_nState       _T("nState")
#define DBStyle_CheckRecords_cTime        _T("cTime")

/*==============================款式成本信息表  dbo.Style_Cost anjie 2019/05/24==============================*/
#define DBStyleCost_ID                _T("ID")
#define DBStyleCost_cStyleNo          _T("cStyleNo")
#define DBStyleCost_cCostItem         _T("cCostItem")
#define DBStyleCost_cCostType         _T("cCostType")
#define DBStyleCost_cCostJinE         _T("cCostJinE")
#define DBStyleCost_fCostPrice        _T("fCostPrice")
#define DBStyleCost_fCostAddedValue   _T("fCostAddedValue")
#define DBStyleCost_fSalesPrice       _T("fSalesPrice")
#define DBStyleCost_fSalesAddedValue  _T("fSalesAddedValue")
#define DBStyleCost_fCalculatedValue  _T("fCalculatedValue")
/*==============================款式文件信息表  dbo.Style_FileInfo wangzl 2019/05/28==============================*/
#define DBStyle_FileInfo_ID                 _T("ID")
#define DBStyle_FileInfo_nFileID            _T("nFileID")
#define DBStyle_FileInfo_cStyleNo           _T("cStyleNo")
#define DBStyle_FileInfo_nFileType          _T("nFileType")
#define DBStyle_FileInfo_nSort             _T("nSort")

/*==============================样衣文件信息表  dbo.Style_FileInfo wangzl 2019/05/28==============================*/
#define DBSampleClothing_FileInfo_ID                 _T("ID")
#define DBSampleClothing_FileInfo_nFileID            _T("nFileID")
#define DBSampleClothing_FileInfo_cBarCode           _T("cBarCode")
#define DBSampleClothing_FileInfo_nFileType          _T("nFileType")
#define DBSampleClothing_FileInfo_nSort             _T("nSort")

/*==============================款式版本申请记录表  dbo.Style_VersionRecords wantzl 2019/06/05==============================*/
#define DBStyle_VersionRecords_ID           _T("ID")
#define DBStyle_VersionRecords_SID          _T("SID")
#define DBStyle_VersionRecords_cPerson      _T("cPerson")
#define DBStyle_VersionRecords_nState       _T("nState")
#define DBStyle_VersionRecords_cTime        _T("cTime")
#define DBStyle_VersionRecords_cRemark      _T("cRemark")

/*==============================款式描述  dbo.Style_Description 2019/06/11==============================*/
#define DBStyle_Description_Key_ID            _T("ID")
#define DBStyle_Description_Key_cKuanhao      _T("cKuanhao")
#define DBStyle_Description_Key_cDescription  _T("cDescription")

/*==============================标签名称  dbo.Config_TagName wangzl 2019/06/12==============================*/
#define DBConfig_TagName_Key_cTagName      _T("cTagName")
#define DBConfig_TagName_Key_cDisplayName  _T("cDisplayName")
#define DBConfig_TagName_Key_nHide  _T("nHide") //是否隐藏 yangjr 2019/07/09
/*==============================款式密度信息表  dbo.Style_DesDenisity wangzl 2019/06/19==============================*/
#define DBStyle_DesDenisity_Key_ID                 _T("ID")
#define DBStyle_DesDenisity_Key_nStyleID           _T("nStyleID")
#define DBStyle_DesDenisity_Key_cName              _T("cName")
#define DBStyle_DesDenisity_Key_fHorDesSrc         _T("fHorDesSrc")
#define DBStyle_DesDenisity_Key_fVerDesSrc         _T("fVerDesSrc")
#define DBStyle_DesDenisity_Key_fHorDesNew         _T("fHorDesNew")
#define DBStyle_DesDenisity_Key_fVerDesNew         _T("fVerDesNew")
#define DBStyle_DesDenisity_Key_cStructure         _T("cStructure")
#define DBStyle_DesDenisity_Key_cMaterial          _T("cMaterial")
#define DBStyle_DesDenisity_Key_fPull              _T("fPull")
#define DBStyle_DesDenisity_Key_cPullUnit          _T("cPullUnit")
#define DBStyle_DesDenisity_Key_iPullType          _T("iPullType")
#define DBStyle_DesDenisity_Key_cNeedle            _T("cNeedle")
#define DBStyle_DesDenisity_Key_fPieceUnit         _T("fPieceUnit")
#define DBStyle_DesDenisity_Key_fPieceTurns        _T("fPieceTurns")
#define DBStyle_DesDenisity_Key_fPieceNeedle       _T("fPieceNeedle")
#define DBStyle_DesDenisity_Key_fStartTurns        _T("fStartTurns")
#define DBStyle_DesDenisity_Key_cRomanType         _T("cRomanType")
#define DBStyle_DesDenisity_Key_cWire              _T("cWire")
#define DBStyle_DesDenisity_Key_fWireTurns         _T("fWireTurns")
#define DBStyle_DesDenisity_Key_iWireType          _T("iWireType")
#define DBStyle_DesDenisity_Key_cPinBottom         _T("cPinBottom")
#define DBStyle_DesDenisity_Key_cPinFace           _T("cPinFace")
#define DBStyle_DesDenisity_Key_iPinType           _T("iPinType")
#define DBStyle_DesDenisity_Key_cType              _T("cType")
#define DBStyle_DesDenisity_Key_cBaseType          _T("cBaseType")
#define DBStyle_DesDenisity_Key_iShowPZ            _T("iShowPZ")
#define DBStyle_DesDenisity_Key_cPZName            _T("cPZName")
#define DBStyle_DesDenisity_Key_cSavedUserID       _T("cSavedUserID")
#define DBStyle_DesDenisity_Key_cSaveTime          _T("cSaveTime")
#define DBStyle_DesDenisity_Key_cRemark            _T("cRemark")
#define DBStyle_DesDenisity_Key_cPieceName         _T("cPieceName")
#define DBStyle_DesDenisity_Key_cMatName           _T("cMatName")

/*==============================款式面子码信息表  dbo.Style_DesFaceCode wangzl 2019/06/19==============================*/
#define DBStyle_DesFaceCode_Key_ID                 _T("ID")
#define DBStyle_DesFaceCode_Key_cName              _T("cName")
#define DBStyle_DesFaceCode_Key_fOldLen            _T("fOldLen")
#define DBStyle_DesFaceCode_Key_cType              _T("cType")
#define DBStyle_DesFaceCode_Key_fLen               _T("fLen")
#define DBStyle_DesFaceCode_Key_cUnit              _T("cUnit")
#define DBStyle_DesFaceCode_Key_IDDensity          _T("IDDensity")


/*==============================样衣管理表  dbo.SampleClotingInfo   lida 2019/07/01==============================*/
#define DBSampleClothingInfo_Key_ID                _T("ID")
#define DBSampleClothingInfo_Key_cKuanhao          _T("cKuanhao")
#define DBSampleClothingInfo_Key_cMainColor        _T("cMainColor")
#define DBSampleClothingInfo_Key_cSize             _T("cSize")
#define DBSampleClothingInfo_Key_cBarCode          _T("cBarCode")
#define DBSampleClothingInfo_Key_Creator           _T("Creator")
#define DBSampleClothingInfo_Key_MakeTime          _T("MakeTime")
#define DBSampleClothingInfo_Key_Keeper            _T("Keeper")
#define DBSampleClothingInfo_Key_KeepLocation       _T("KeepLocation")
#define DBSampleClothingInfo_Key_Memo              _T("Memo")
#define DBSampleClothingInfo_Key_LendReturnState    _T("LendReturnState")
#define DBSampleClothingInfo_Key_cCate             _T("cCate")

/*==============================样衣收发记录表  dbo.SampleClothingRecords   lida 2019/07/01==============================*/
#define DBSampleClothingRecords_Key_ID                    _T("ID")
#define DBSampleClothingRecords_Key_cBarCode               _T("cBarCode")
#define DBSampleClothingRecords_Key_cKuanhao               _T("cKuanhao")
#define DBSampleClothingRecords_Key_LendReturnState         _T("LendReturnState")
#define DBSampleClothingRecords_Key_LendReturnPerson        _T("LendReturnPerson")
#define DBSampleClothingRecords_Key_LendReturnTime          _T("LendReturnTime")
#define DBSampleClothingRecords_Key_ConfirmMan              _T("ConfirmMan")
#define DBSampleClothingRecords_Key_Location                _T("Location")
#define DBSampleClothingRecords_Key_Reason                 _T("Reason")
#define DBSampleClothingRecords_Key_Memo                   _T("Memo")
/*==============================款式基本字段信息表  dbo.Style_Basic_FieldSet wangzl 2019/07/01==============================*/
#define DBStyle_Basic_FieldSet_Key_cColID          _T("cColID")
#define DBStyle_Basic_FieldSet_Key_cDisplayName    _T("cDisplayName")
#define DBStyle_Basic_FieldSet_Key_bShow           _T("bShow")
#define DBStyle_Basic_FieldSet_Key_nSortIndex      _T("nSortIndex")
#define DBStyle_Basic_FieldSet_Key_bOnPanel        _T("bOnPanel")

/*==============================款式尺寸额外信息表 dbo.[StyleSizeExtra] yangjr 2019/07/14==============================*/
#define DBStyleSizeExtra_key_ID           _T("ID")
#define DBStyleSizeExtra_key_cStyleNo     _T("cStyleNo")//款号
#define DBStyleSizeExtra_key_iPartID     _T("iPartID")   //尺寸部位
#define DBStyleSizeExtra_key_cMemo     _T("cMemo") //部位说明
#define DBStyleSizeExtra_key_fCeLiangBeforeSize    _T("fCeLiangBeforeSize") //测量前尺寸
#define DBStyleSizeExtra_key_fCeLiangCusSize     _T("fCeLiangCusSize") //客户测量尺寸
#define DBStyleSizeExtra_key_fWaterBeforeSize     _T("fWaterBeforeSize")//洗水前尺寸
#define DBStyleSizeExtra_key_fWaterAfterSize     _T("fWaterAfterSize")//洗水后尺寸



/*==============================生产单信息表 dbo.[ProductOrderInfo] lida 2019/07/17==============================*/
#define  DBProductOrderInfo_Key_ID              _T("ID")
#define  DBProductOrderInfo_Key_MakeDate         _T("MakeDate")
#define  DBProductOrderInfo_Key_ProductOrder     _T("ProductOrder")
#define  DBProductOrderInfo_Key_MainClrNo        _T("MainClrNo")
#define  DBProductOrderInfo_Key_MainClrCate      _T("MainClrCate")
#define  DBProductOrderInfo_Key_MainClrName      _T("MainClrName")
#define  DBProductOrderInfo_Key_SizeNumInfo      _T("SizeNumInfo")
#define  DBProductOrderInfo_Key_StyleNo        _T("StyleNo")
#define  DBProductOrderInfo_Key_TotalNum        _T("TotalNum")

/*==============================销售单信息表 dbo.[SalesOrderInfo] lida 2019/07/18==============================*/
#define  DBSalesOrderInfo_Key_ID              _T("ID")
#define  DBSalesOrderInfo_Key_MakeDate         _T("MakeDate")
#define  DBSalesOrderInfo_Key_SalesOrder     _T("SalesOrder")
#define  DBSalesOrderInfo_Key_MainClrNo        _T("MainClrNo")
#define  DBSalesOrderInfo_Key_MainClrCate      _T("MainClrCate")
#define  DBSalesOrderInfo_Key_MainClrName      _T("MainClrName")
#define  DBSalesOrderInfo_Key_SizeNumInfo      _T("SizeNumInfo")
#define  DBSalesOrderInfo_Key_StyleNo        _T("StyleNo")
#define  DBSalesOrderInfo_Key_TotalNum        _T("TotalNum")