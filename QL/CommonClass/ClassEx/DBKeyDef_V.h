#pragma once

//数据库表字段,视图表，不包普通表		add by lida 2018/02/05

/*==============================表 dbo.V_Kuanshi ==============================*/
//视图中相关的数据字段

#define DBVStyle_key_cCusName			_T("cCusName")		//->客户表		DBCustomer_key_Name
#define DBVStyle_key_cCusAbbName		_T("cCusAbbName")	//客户表		DBCustomer_key_Abbrev
#define DBVStyle_key_ID					_T("ID")
#define DBVStyle_key_dDate				_T("dDate")	
#define DBVStyle_key_cCusCode			_T("cCusCode")
#define DBVStyle_key_cTreeName			_T("cTreeName")
#define DBVStyle_key_cKuanhao			_T("cKuanhao")
#define DBVStyle_key_cKuanming			_T("cKuanming")
#define DBVStyle_key_cKSMemo			_T("cKSMemo")
#define DBVStyle_key_cContent			_T("cContent")
#define DBVStyle_key_cNeedleType		_T("cNeedleType")
#define DBVStyle_key_cFindKey			_T("cFindKey")
#define DBVStyle_key_dtCreatTime		_T("dtCreatTime")
#define DBVStyle_key_cCheckState		_T("cCheckState")
#define DBVStyle_key_cCheckPerson   _T("cCheckPerson")
#define DBVStyle_key_nVersionState  _T("nVersionState")
#define DBVStyle_key_cVersionPerson _T("cVersionPerson")
#define DBVStyle_key_bIsDeleted   _T("bIsDeleted") //款式是否删除 yangjr 2019/05/20
#define DBVStyle_key_iGXSortID       _T("iGXSortID")//当前工序的ID
#define DBVStyle_key_cGXPersonCode   _T("cGXPersonCode")//当前工序的执行人ID
#define DBVStyle_key_cState         _T("cState")//当前工序的执行人ID
#define DBVStyle_key_cDesigner      _T("cDesigner")
#define DBVStyle_key_cCraftsmen     _T("cCraftsmen")
#define DBVStyle_key_cPatternMaker  _T("cPatternMaker")
#define DBVStyle_key_cFangAnName    _T("cFangAnName")

#define DBVStyle_key_cCustomField1          _T("cCustomField1")           //自定义字段1     wangzl 2019/07/02
#define DBVStyle_key_cCustomField2          _T("cCustomField2")           //自定义字段2     wangzl 2019/07/02
#define DBVStyle_key_cCustomField3          _T("cCustomField3")           //自定义字段3     wangzl 2019/07/02
#define DBVStyle_key_cCustomField4          _T("cCustomField4")           //自定义字段4     wangzl 2019/07/02
#define DBVStyle_key_cCustomField5          _T("cCustomField5")           //自定义字段5     wangzl 2019/07/02
#define DBVStyle_key_cCustomField6          _T("cCustomField6")           //自定义字段6     wangzl 2019/07/02
#define DBVStyle_key_cCustomField7          _T("cCustomField7")           //自定义字段7     wangzl 2019/07/02
#define DBVStyle_key_cCustomField8          _T("cCustomField8")           //自定义字段8     wangzl 2019/07/02
#define DBVStyle_key_cCustomField9          _T("cCustomField9")           //自定义字段9     wangzl 2019/07/02
#define DBVStyle_key_cCustomField10         _T("cCustomField10")          //自定义字段10    wangzl 2019/07/02

#define DBVStyle_key_cHelpSeekerID          _T("cHelpSeeker")             //求助人ID        duc    2019/07/18
/*==============================BandProgramming视图 dbo. ==============================*/
#define DBV_BANDPROGRAMMING_Key_ID                                 _T("ID")
#define DBV_BANDPROGRAMMING_Key_cSeriaNum                          _T("cSeriaNum")               //序号
#define DBV_BANDPROGRAMMING_Key_cName                              _T("cName")                   //名称
#define DBV_BANDPROGRAMMING_Key_cBindStartTime                     _T("cBandStartTime")          //波段开始时间
#define DBV_BANDPROGRAMMING_Key_cDesignEndTime                     _T("cDesignEndTime")          //设计完成时间
#define DBV_BANDPROGRAMMING_Key_cPatternEndTime                    _T("cPatternEndTime")         //纸样完成时间
#define DBV_BANDPROGRAMMING_Key_cReviewEndTime                     _T("cReviewEndTime")          //内审会完成时间
#define DBV_BANDPROGRAMMING_Key_cBandEndTime                       _T("cBandEndTime")            //波段结束时间
#define DBV_BANDPROGRAMMING_Key_cDeliveryStartTime                 _T("cDeliveryStartTime")      //货期起始时间
#define DBV_BANDPROGRAMMING_Key_cDeliveryEndTime                   _T("cDeliveryEndTime")        //货期结束时间
#define DBV_BANDPROGRAMMING_Key_cShelvesTime                       _T("cShelvesTime")            //上货日
#define DBV_BANDPROGRAMMING_Key_cStylish                           _T("cStylish")                //风格
#define DBV_BANDPROGRAMMING_Key_cColor                             _T("cColor")                  //色系
#define DBV_BANDPROGRAMMING_Key_cCreateUserID                      _T("cCreateUserID")           //创建人
#define DBV_BANDPROGRAMMING_Key_cCreateUserTime                    _T("cCreateUserTime")         //创建时间
#define DBV_BANDPROGRAMMING_Key_bCheckState                        _T("bCheckState")             //审核标识
#define DBV_BANDPROGRAMMING_Key_cCheckUserID                       _T("cCheckUserID")            //审核人
#define DBV_BANDPROGRAMMING_Key_cCheckTime                         _T("cCheckTime")              //审核时间
#define DBV_BANDPROGRAMMING_Key_cRemark                            _T("cRemark")                 //备注
#define DBV_BANDPROGRAMMING_Key_nAssociatedProgrammingID           _T("nAssociatedProgrammingID")// 所属商品规划的ID
#define DBV_BANDPROGRAMMING_Key_ProgrammingID                      _T("ProgrammingID")           //商品ID
#define DBV_BANDPROGRAMMING_Key_cBrand                             _T("cBrand")                   //品牌
#define DBV_BANDPROGRAMMING_Key_nYears                             _T("nYears")                   //年度
#define DBV_BANDPROGRAMMING_Key_cSeason                            _T("cSeason")                  //季节
#define DBV_BANDPROGRAMMING_Key_cTradeFairTime                     _T("cTradeFairTime")           //订货会时间
#define DBV_BANDPROGRAMMING_Key_cArea                              _T("cArea")                    //区域
#define DBV_BANDPROGRAMMING_Key_nAssociatedPlanningID              _T("nAssociatedPlanningID")    //所属企划ID
#define DBV_BANDPROGRAMMING_Key_cProgrammingCreateUserID           _T("cProgrammingCreateUserID") //商品创建人ID   

/*==============================BandProgramming视图 dbo. ==============================*/

/*==============================产品工序视图 dbo.V_ProductProcess wangzl 2018/08/25==============================*/
#define DBV_ProductProcess_Key_ID                                   _T("ID")                           //
#define DBV_ProductProcess_Key_cClassification                      _T("cClassification")              //分类    
#define DBV_ProductProcess_Key_cCategory                            _T("cCategory")                    //品类    
#define DBV_ProductProcess_Key_nPieceNum                            _T("nPieceNum")                    //件数    
#define DBV_ProductProcess_Key_cColor                               _T("cColor")                       //色号    
#define DBV_ProductProcess_Key_cSize                                _T("cSize")                        //尺码    
#define DBV_ProductProcess_Key_cFabric                              _T("cFabric")                      //面料    
#define DBV_ProductProcess_Key_cFashion                             _T("cFashion")                     //造型风格
#define DBV_ProductProcess_Key_cContour                             _T("cContour")                     //廓形    
#define DBV_ProductProcess_Key_fPrice_Ceiling                       _T("fPrice_Ceiling")               //价格上限
#define DBV_ProductProcess_Key_fPrice_Floor                         _T("fPrice_Floor")                 //价格下限
#define DBV_ProductProcess_Key_fPrice_Tag                           _T("fPrice_Tag")                   //吊牌价  
#define DBV_ProductProcess_Key_cRemark                              _T("cRemark")                      //备注    
#define DBV_ProductProcess_Key_cBand_Name                           _T("cBand_Name")                   //名称
#define DBV_ProductProcess_Key_cBand_BandStartTime                  _T("cBand_BandStartTime")          //波段开始时间   
#define DBV_ProductProcess_Key_cBand_DesignEndTime                  _T("cBand_DesignEndTime")          //设计完成时间   
#define DBV_ProductProcess_Key_cBand_PatternEndTime                 _T("cBand_PatternEndTime")         //纸样完成时间   
#define DBV_ProductProcess_Key_cBand_ReviewEndTime                  _T("cBand_ReviewEndTime")          //内审会完成时间
#define DBV_ProductProcess_Key_cBand_BandEndTime                    _T("cBand_BandEndTime")            //波段结束时间
#define DBV_ProductProcess_Key_cBand_DeliveryStartTime              _T("cBand_DeliveryStartTime")      //货期起始时间
#define DBV_ProductProcess_Key_cBand_DeliveryEndTime                _T("cBand_DeliveryEndTime")        //货期结束时间
#define DBV_ProductProcess_Key_cBand_ShelvesTime                    _T("cBand_ShelvesTime")            //上货日
#define DBV_ProductProcess_Key_cBand_Stylish                        _T("cBand_Stylish")                //风格
#define DBV_ProductProcess_Key_cBand_Color                          _T("cBand_Color")                  //色系
#define DBV_ProductProcess_Key_cCreateUserID                        _T("cCreateUserID")                //创建人
#define DBV_ProductProcess_Key_cCreateTime                          _T("cCreateTime")                  //创建时间
#define DBV_ProductProcess_Key_nCreateFlag                          _T("nCreateFlag")                  //创建来源  用于记录是直接创建的产品  还是通过波段创建的产品
#define DBV_ProductProcess_Key_cProgramming_Brand                   _T("cProgramming_Brand")           //品牌
#define DBV_ProductProcess_Key_cProgramming_Years                   _T("cProgramming_Years")           //年度
#define DBV_ProductProcess_Key_cProgramming_Season                  _T("cProgramming_Season")          //季节
#define DBV_ProductProcess_Key_cProgramming_TradeFairTime           _T("cProgramming_TradeFairTime")   //订货会时间
#define DBV_ProductProcess_Key_cProgramming_Area                    _T("cProgramming_Area")            //区域
#define DBV_ProductProcess_Key_cPlanning_SubjectName                _T("cPlanning_SubjectName")        //主题名
#define DBV_ProductProcess_Key_cCheckUserID                         _T("cCheckUserID")                 //审核人
#define DBV_ProductProcess_Key_cCheckTime                           _T("cCheckTime")                   //审核时间
#define DBV_ProductProcess_Key_bCheckState                          _T("bCheckState")                  //审核状态

#define DBV_ProductProcess_Key_cAssignUserID                        _T("cAssignUserID")                     //指派的人的ID
#define DBV_ProductProcess_Key_nPersonType                          _T("nPersonType")                       //被指派的人的人员类型

#define DBV_ProductProcess_Key_ProcessID                             _T("ProcessRecordsID")                 //
#define DBV_ProductProcess_Key_nAssociatedProductID                  _T("nAssociatedProductID")             //关联的产品ID
#define DBV_ProductProcess_Key_cReceiveUserID                        _T("cReceiveUserID")                   //接收人
#define DBV_ProductProcess_Key_cSponsorID                            _T("cSponsorID")                       //任务发起人
#define DBV_ProductProcess_Key_nProcessType                          _T("nProcessType")                     //对应的工序
#define DBV_ProductProcess_Key_cInitiateTime                         _T("cInitiateTime")                    //任务发起时间
#define DBV_ProductProcess_Key_cRealStartTime                        _T("cRealStartTime")                   //任务实际开始时间
#define DBV_ProductProcess_Key_cFinishTime                           _T("cFinishTime")                      //任务完成时间
#define DBV_ProductProcess_Key_nState                                _T("nState")                           //状态
#define DBV_ProductProcess_Key_nCheckState                           _T("nCheckState")                      //审核

/*==============================产品版本订单视图 dbo.V_ProductVersionOrders wangzl 2018/08/30==============================*/
#define DBV_ProductVersionOrders_Key_ID                              _T("ID")                               //
#define DBV_ProductVersionOrders_Key_cClassification                 _T("cClassification")                  //分类    
#define DBV_ProductVersionOrders_Key_cCategory                       _T("cCategory")                        //品类    
#define DBV_ProductVersionOrders_Key_nPieceNum                       _T("nPieceNum")                        //件数    
#define DBV_ProductVersionOrders_Key_cColor                          _T("cColor")                           //色号    
#define DBV_ProductVersionOrders_Key_cSize                           _T("cSize")                            //尺码    
#define DBV_ProductVersionOrders_Key_cFabric                         _T("cFabric")                          //面料    
#define DBV_ProductVersionOrders_Key_cFashion                        _T("cFashion")                         //造型风格
#define DBV_ProductVersionOrders_Key_cContour                        _T("cContour")                         //廓形    
#define DBV_ProductVersionOrders_Key_fPrice_Ceiling                  _T("fPrice_Ceiling")                   //价格上限
#define DBV_ProductVersionOrders_Key_fPrice_Floor                    _T("fPrice_Floor")                     //价格下限
#define DBV_ProductVersionOrders_Key_fPrice_Tag                      _T("fPrice_Tag")                       //吊牌价  
#define DBV_ProductVersionOrders_Key_cRemark                         _T("cRemark")                          //备注    
#define DBV_ProductVersionOrders_Key_cBand_Name                      _T("cBand_Name")                       //名称
#define DBV_ProductVersionOrders_Key_cBand_BandStartTime             _T("cBand_BandStartTime")              //波段开始时间   
#define DBV_ProductVersionOrders_Key_cBand_DesignEndTime             _T("cBand_DesignEndTime")              //设计完成时间   
#define DBV_ProductVersionOrders_Key_cBand_PatternEndTime            _T("cBand_PatternEndTime")             //纸样完成时间   
#define DBV_ProductVersionOrders_Key_cBand_ReviewEndTime             _T("cBand_ReviewEndTime")              //内审会完成时间
#define DBV_ProductVersionOrders_Key_cBand_BandEndTime               _T("cBand_BandEndTime")                //波段结束时间
#define DBV_ProductVersionOrders_Key_cBand_DeliveryStartTime         _T("cBand_DeliveryStartTime")          //货期起始时间
#define DBV_ProductVersionOrders_Key_cBand_DeliveryEndTime           _T("cBand_DeliveryEndTime")            //货期结束时间
#define DBV_ProductVersionOrders_Key_cBand_ShelvesTime               _T("cBand_ShelvesTime")                //上货日
#define DBV_ProductVersionOrders_Key_cBand_Stylish                   _T("cBand_Stylish")                    //风格
#define DBV_ProductVersionOrders_Key_cBand_Color                     _T("cBand_Color")                      //色系
#define DBV_ProductVersionOrders_Key_cCreateUserID                   _T("cCreateUserID")                    //创建人
#define DBV_ProductVersionOrders_Key_cCreateTime                     _T("cCreateTime")                      //创建时间
#define DBV_ProductVersionOrders_Key_nCreateFlag                     _T("nCreateFlag")                      //创建来源  用于记录是直接
#define DBV_ProductVersionOrders_Key_cProgramming_Brand              _T("cProgramming_Brand")               //品牌
#define DBV_ProductVersionOrders_Key_cProgramming_Years              _T("cProgramming_Years")               //年度
#define DBV_ProductVersionOrders_Key_cProgramming_Season             _T("cProgramming_Season")              //季节
#define DBV_ProductVersionOrders_Key_cProgramming_TradeFairTime      _T("cProgramming_TradeFairTime")       //订货会时间
#define DBV_ProductVersionOrders_Key_cProgramming_Area               _T("cProgramming_Area")                //区域
#define DBV_ProductVersionOrders_Key_cPlanning_SubjectName           _T("cPlanning_SubjectName")            //主题名
#define DBV_ProductVersionOrders_Key_cCheckUserID                    _T("cCheckUserID")                     //审核人
#define DBV_ProductVersionOrders_Key_cCheckTime                      _T("cCheckTime")                       //审核时间
#define DBV_ProductVersionOrders_Key_bCheckState                     _T("bCheckState")                      //审核状态
#define DBV_ProductVersionOrders_Key_nCurProSort                     _T("nCurProSort")                      //当前所在ID
#define DBV_ProductVersionOrders_Key_bRevision                       _T("bRevision")                        //是否需要改版
#define DBV_ProductVersionOrders_Key_cRevisionReason                 _T("cRevisionReason")                  //改版原因
#define DBV_ProductVersionOrders_Key_VersionID                       _T("VersionID")                        //版本ID
#define DBV_ProductVersionOrders_Key_cVersion                        _T("cVersion")                         //版本
#define DBV_ProductVersionOrders_Key_RdRecordsID                     _T("RdRecordsID")                      //订单表ID
#define DBV_ProductVersionOrders_Key_cCate                           _T("cCate")                            //类型
#define DBV_ProductVersionOrders_Key_cCode                           _T("cCode")                            //单号
#define DBV_ProductVersionOrders_Key_dDate                           _T("dDate")                            //下单日期
#define DBV_ProductVersionOrders_Key_cMaker                          _T("cMaker")                           //制单人
#define DBV_ProductVersionOrders_Key_cInvSehao                       _T("cInvSehao")                        //主色
#define DBV_ProductVersionOrders_Key_cInvPeise                       _T("cInvPeise")                        //配色
#define DBV_ProductVersionOrders_Key_cInvKuanhao                     _T("cInvKuanhao")                      //款号
#define DBV_ProductVersionOrders_Key_cInvUnitCost                    _T("cInvUnitCost")                     //单价
#define DBV_ProductVersionOrders_Key_cLastPerson                     _T("cLastPerson")                      //最后操作人
#define DBV_ProductVersionOrders_Key_dLastTime                       _T("dLastTime")                        //最后操作时间
#define DBV_ProductVersionOrders_Key_cInvState2                      _T("cInvState2")                       //状态2
#define DBV_ProductVersionOrders_Key_dTrueTime                       _T("dTrueTime")                        //真实录单时间
#define DBV_ProductVersionOrders_Key_iOrdCreateFlag                  _T("iOrdCreateFlag")                   //订单创建标识
#define DBV_ProductVersionOrders_Key_cJianshu                        _T("cJianshu")                         //件数
#define DBV_ProductVersionOrders_Key_cInvMemo                        _T("cInvMemo")                         //备注
#define DBV_ProductVersionOrders_Key_cInvState                       _T("cInvState")                        //状态
#define DBV_ProductVersionOrders_Key_cZuoFeiMemo                     _T("cZuoFeiMemo")                      //作废说明

/*==============================产品改版视图 dbo.V_ProductRevisionRecords wangzl 2018/09/03==============================*/
#define DBV_ProductRevisionRecords_Key_cClassification               _T("cClassification")                  //
#define DBV_ProductRevisionRecords_Key_cCategory                     _T("cCategory")                        //
#define DBV_ProductRevisionRecords_Key_cBand_Name                    _T("cBand_Name")                       //
#define DBV_ProductRevisionRecords_Key_nCurProSort                   _T("nCurProSort")                      //
#define DBV_ProductRevisionRecords_Key_ID                            _T("ID")                               //
#define DBV_ProductRevisionRecords_Key_nAssociatedProductID          _T("nAssociatedProductID")             //
#define DBV_ProductRevisionRecords_Key_cVersion                      _T("cVersion")                         //
#define DBV_ProductRevisionRecords_Key_nVersionNo                    _T("nVersionNo")                       //
#define DBV_ProductRevisionRecords_Key_cCode                         _T("cCode")                            //
#define DBV_ProductRevisionRecords_Key_cAlias                        _T("cAlias")                           //
#define DBV_ProductRevisionRecords_Key_cSponsor                      _T("cSponsor")                         //
#define DBV_ProductRevisionRecords_Key_cRecordTime                   _T("cRecordTime")                      //
#define DBV_ProductRevisionRecords_Key_cRevisionType                 _T("cRevisionType")                    //
#define DBV_ProductRevisionRecords_Key_cRevisionReason               _T("cRevisionReason")                  //
#define DBV_ProductRevisionRecords_Key_cLastRecordProcess            _T("cLastRecordProcess")               //
#define DBV_ProductRevisionRecords_Key_nCheckState                   _T("nCheckState")                      //
#define DBV_ProductRevisionRecords_Key_nCheckResult                  _T("nCheckResult")                     //
#define DBV_ProductRevisionRecords_Key_cCheckUserID                  _T("cCheckUserID")                     //
#define DBV_ProductRevisionRecords_Key_cCheckTime                    _T("cCheckTime")                       //
#define DBV_ProductRevisionRecords_Key_cCheckOpinion                 _T("cCheckOpinion")                    //


/*==============================子订单视图表 dbo.V_RdRecordsChild yangjr 2018/9/26==============================*/
#define  DBOrderChild_V_key_CustomercCate	_T("CustomercCate")
#define  DBOrderChild_V_key_cCusCate		_T("cCusCate")
#define  DBOrderChild_V_key_cCusName		_T("cCusName")
#define  DBOrderChild_V_key_cShazhi			_T("cShazhi")
#define  DBOrderChild_V_key_cChenfen		_T("cChenfen")
#define  DBOrderChild_V_key_cSeming			_T("cSeming")
#define  DBOrderChild_V_key_cColorCate		_T("cColorCate")
#define  DBOrderChild_V_key_cTreeName		   _T("cTreeName")
#define  DBOrderChild_V_key_cKuanming		   _T("cKuanming")
#define  DBOrderChild_V_key_cKSChengfen		_T("cKSChengfen")
#define  DBOrderChild_V_key_cBarCode			_T("cBarCode") //商品条码
#define  DBOrderChild_V_key_cContent			_T("cContent")
#define  DBOrderChild_V_key_cSheng			   _T("cSheng")
#define  DBOrderChild_V_key_cShi				_T("cShi")
#define  DBOrderChild_V_key_iDay				_T("iDay")  //下单离当前多少天
#define  DBOrderChild_V_key_iDays			_T("iDays") //从下单到必须交货的天数 客户表中
#define  DBOrderChild_V_key_cUserCode		_T("cUserCode")
#define  DBOrderChild_V_key_ID				_T("ID")
#define  DBOrderChild_V_key_cCate			_T("cCate")
#define  DBOrderChild_V_key_cCode			   _T("cCode")
#define  DBOrderChild_V_key_dDate			   _T("dDate")
#define  DBOrderChild_V_key_cMaker			   _T("cMaker")
#define  DBOrderChild_V_key_cCusCode			_T("cCusCode")
#define  DBOrderChild_V_key_cInvCustCode		_T("cInvCustCode")
#define  DBOrderChild_V_key_cInvCustName		_T("cInvCustName")
#define  DBOrderChild_V_key_cInvCustTel		_T("cInvCustTel")
#define  DBOrderChild_V_key_iDingjin			_T("iDingjin")
#define  DBOrderChild_V_key_iAllJianshu		_T("iAllJianshu")
#define  DBOrderChild_V_key_iJianshu		   _T("iJianshu")
#define  DBOrderChild_V_key_cInvKuanhao		_T("cInvKuanhao")
#define  DBOrderChild_V_key_cInvSehao		   _T("cInvSehao")
#define  DBOrderChild_V_key_cInvPeise		   _T("cInvPeise")
#define  DBOrderChild_V_key_cInvJinxian		_T("cInvJinxian")
#define  DBOrderChild_V_key_cInvXiukou		_T("cInvXiukou")
#define  DBOrderChild_V_key_cInvLingxing		_T("cInvLingxing")
#define  DBOrderChild_V_key_cInvDibian		_T("cInvDibian")
#define  DBOrderChild_V_key_cInvJiaji		   _T("cInvJiaji")
#define  DBOrderChild_V_key_cInvMemo			_T("cInvMemo")
#define  DBOrderChild_V_key_cKSMemo			_T("cKSMemo")
#define  DBOrderChild_V_key_cInvState		   _T("cInvState")
#define  DBOrderChild_V_key_cInvFahuoDate	_T("cInvFahuoDate")
#define  DBOrderChild_V_key_cInvUnitCost		_T("cInvUnitCost")
#define  DBOrderChild_V_key_cInvJiagongfe	_T("cInvJiagongfei")
#define  DBOrderChild_V_key_cInvFujiafei		_T("cInvFujiafei")
#define  DBOrderChild_V_key_cInvState2		_T("cInvState2")
#define  DBOrderChild_V_key_cSexType			_T("cSexType") //男款女款
#define  DBOrderChild_V_key_cShouYao			_T("cShouYao")//收腰
#define  DBOrderChild_V_key_cTiRong			_T("cTiRong") //提绒
#define  DBOrderChild_V_key_cZhiYiCode			_T("cZhiYiCode") //制衣单号
#define  DBOrderChild_V_key_dJiaoDate		   _T("dJiaoDate") //交期
#define  DBOrderChild_V_key_dTrueTime		   _T("dTrueTime") //真实录单时间
#define  DBOrderChild_V_key_iPrint_XSM	   _T("Print_XSM")      //打印次数变更到order_flag 的 print_xsm by lida 2018/07/04
#define  DBOrderChild_V_key_cCusMobile		_T("cCusMobile")
#define  DBOrderChild_V_key_cSehao			   _T("cSehao")
#define  DBOrderChild_V_key_cPeise			   _T("cPeise")
#define  DBOrderChild_V_key_cJinxian			_T("cJinxian")
#define  DBOrderChild_V_key_cNeedleType     _T("cNeedleType")
#define  DBOrderChild_V_key_cRunPerson      _T("cRunPerson")
#define  DBOrderChild_V_key_cOutNo          _T("cOutNo")
#define  DBOrderChild_V_key_iOtherFlag      _T("iOtherFlag")
#define  DBOrderChild_V_key_iOrdCreateFlag  _T("iOrdCreateFlag")
#define  DBOrderChild_V_key_cChiMa          _T("cChiMa")    
#define  DBOrderChild_V_key_MacType         _T("cMacType")	//2018-01-24 zhangt 机种类型：手摇 电脑
#define  DBOrderChild_V_key_ClassType       _T("cClassType")	//2018-01-24 zhangt 订单种类：衣服 裤子
#define  DBOrderChild_V_key_AmountType      _T("cAmountType")//2018-01-24 zhangt 测量类型（量体，量码）
#define  DBOrderChild_V_key_GoodsType       _T("cGoodsType")	//2018-03-20 zhangt 订货类型（客户订单，订货会订单，订货会成衣，设计师样衣，秋冬补款，春夏订货会）
#define  DBOrderChild_V_key_iFilesNum       _T("iFilesNum")	//2018-01-25 yangjr 文件个数
#define  DBOrderChild_V_key_cFactoryMemo    _T("cFactoryMemo")	//厂内备注 yangjr 2018/6/15
#define DBOrderChild_V_key_cWeb_Materials   _T("cWeb_Materials")    //web下单，材质
#define DBOrderChild_V_key_iCurProSort       _T("iCurProSort") //DB类未处理 仅用于判断工序逻辑相关操作
#define DBOrderChild_V_key_iCurProState      _T("iCurProState")//DB类未处理
#define DBOrderChild_V_key_cProOrder         _T("cProOrder")   //DB类未处理
#define DBOrderChild_V_key_cGongyishi        _T("cGongyishi")    //工艺师
#define DBOrderChild_V_key_cZuoFeiMemo        _T("cZuoFeiMemo")    //作废说明 yangjr 2018/7/14
#define DBOrderChild_V_key_fTuanGouJia        _T("fTuanGouJia")    //团购价 yangjr 2018/7/17
#define DBOrderChild_V_ColorState             _T("ColorState") //订单的状态颜色
#define DBOrderChild_V_key_iFanLiFlag        _T("iFanLiFlag") //返利标志 yangjr 2018/8/7
#define DBOrderChild_V_key_fDiaoPaiJia       _T("fDiaoPaiJia") //吊牌价 yangjr 2018/8/8
#define DBOrderChild_V_key_cSalesID           _T("cSalesID")   //业务员ID yangjr 2018/9/1
#define DBOrderChild_V_key_cSalesCode       _T("cSalesCode")   //销售单号 yangjr 2018/9/6
#define DBOrderChild_V_key_cChenfen2         _T("cChenfen2")   //成份2 yangjr 2018/9/26
#define DBOrderChild_V_key_cChenfen3         _T("cChenfen3")   //成份3:纱线品种成分   	by WangZY 2019/03/07
#define DBOrderChild_V_key_cCusAddress		_T("cCusAddress")			//客户地址
#define DBOrderChild_V_key_fZMDLingShouDanJia       _T("fZMDLingShouDanJia")   //专卖店零售单价 lida 2018/11/09
#define DBOrderChild_V_key_iCurBaoIndex         _T("iCurBaoIndex")      //当前包号 lida 2018/11/15
#define DBOrderChild_V_key_JiajiPrice        _T("cJiaJiPrice")          //加急费用 anjie 2019/03/29
/*==============================主订单视图表 dbo.V_RdRecordsSales yangjr 2018/9/27==============================*/
#define  DBOrderSales_V_key_CustomercCate	_T("CustomercCate")
#define  DBOrderSales_V_key_cCusCate		_T("cCusCate")
#define  DBOrderSales_V_key_cCusName		_T("cCusName")
#define  DBOrderSales_V_key_cTreeName		   _T("cTreeName")
#define  DBOrderSales_V_key_cKuanming		   _T("cKuanming")
#define  DBOrderSales_V_key_cKSChengfen		_T("cKSChengfen")
#define  DBOrderSales_V_key_cBarCode			_T("cBarCode") //商品条码
#define  DBOrderSales_V_key_cContent			_T("cContent")
#define  DBOrderSales_V_key_cSheng			   _T("cSheng")
#define  DBOrderSales_V_key_cShi				_T("cShi")
#define  DBOrderSales_V_key_iDay				_T("iDay")  //下单离当前多少天
#define  DBOrderSales_V_key_iDays			_T("iDays") //从下单到必须交货的天数 客户表中
#define  DBOrderSales_V_key_cUserCode		_T("cUserCode")
#define  DBOrderSales_V_key_ID				_T("ID")
#define  DBOrderSales_V_key_cCate			_T("cCate")
#define  DBOrderSales_V_key_dDate			   _T("dDate")
#define  DBOrderSales_V_key_cMaker			   _T("cMaker")
#define  DBOrderSales_V_key_cCusCode			_T("cCusCode")
#define  DBOrderSales_V_key_cInvCustCode		_T("cInvCustCode")
#define  DBOrderSales_V_key_cInvCustName		_T("cInvCustName")
#define  DBOrderSales_V_key_cInvCustTel		_T("cInvCustTel")
#define  DBOrderSales_V_key_iDingjin			_T("iDingjin")
#define  DBOrderSales_V_key_iAllJianshu		_T("iAllJianshu")
#define  DBOrderSales_V_key_cInvKuanhao		_T("cInvKuanhao")
#define  DBOrderSales_V_key_cInvJinxian		_T("cInvJinxian")
#define  DBOrderSales_V_key_cInvXiukou		_T("cInvXiukou")
#define  DBOrderSales_V_key_cInvLingxing		_T("cInvLingxing")
#define  DBOrderSales_V_key_cInvDibian		_T("cInvDibian")
#define  DBOrderSales_V_key_cInvShenChang		_T("cInvShenchang")
#define  DBOrderSales_V_key_cInvJiaji		   _T("cInvJiaji")
#define  DBOrderSales_V_key_cInvMemo			_T("cInvMemo")
#define  DBOrderSales_V_key_cKSMemo			_T("cKSMemo")
#define  DBOrderSales_V_key_cInvState		   _T("cInvState")
#define  DBOrderSales_V_key_cInvFahuoDate	_T("cInvFahuoDate")
#define  DBOrderSales_V_key_cInvUnitCost		_T("cInvUnitCost")
#define  DBOrderSales_V_key_cInvJiagongfe	_T("cInvJiagongfei")
#define  DBOrderSales_V_key_cInvFujiafei		_T("cInvFujiafei")
#define  DBOrderSales_V_key_cInvState2		_T("cInvState2")
#define  DBOrderSales_V_key_cSexType			_T("cSexType") //男款女款
#define  DBOrderSales_V_key_cShouYao			_T("cShouYao")//收腰
#define  DBOrderSales_V_key_cTiRong			_T("cTiRong") //提绒
#define  DBOrderSales_V_key_cZhiYiCode			_T("cZhiYiCode") //制衣单号
#define  DBOrderSales_V_key_dJiaoDate		   _T("dJiaoDate") //交期
#define  DBOrderSales_V_key_dTrueTime		   _T("dTrueTime") //真实录单时间
#define  DBOrderSales_V_key_iPrint_XSM	   _T("Print_XSM")      //打印次数变更到order_flag 的 print_xsm by lida 2018/07/04
#define  DBOrderSales_V_key_cCusMobile		_T("cCusMobile")
#define  DBOrderSales_V_key_cSehao			   _T("cSehao")
#define  DBOrderSales_V_key_cPeise			   _T("cPeise")
#define  DBOrderSales_V_key_cJinxian			_T("cJinxian")
#define  DBOrderSales_V_key_cNeedleType     _T("cNeedleType")
#define  DBOrderSales_V_key_cRunPerson      _T("cRunPerson")
#define  DBOrderSales_V_key_cOutNo          _T("cOutNo")
#define  DBOrderSales_V_key_iOtherFlag      _T("iOtherFlag")
#define  DBOrderSales_V_key_iOrdCreateFlag  _T("iOrdCreateFlag") 
#define  DBOrderSales_V_key_MacType         _T("cMacType")	//2018-01-24 zhangt 机种类型：手摇 电脑
#define  DBOrderSales_V_key_ClassType       _T("cClassType")	//2018-01-24 zhangt 订单种类：衣服 裤子
#define  DBOrderSales_V_key_AmountType      _T("cAmountType")//2018-01-24 zhangt 测量类型（量体，量码）
#define  DBOrderSales_V_key_GoodsType       _T("cGoodsType")	//2018-03-20 zhangt 订货类型（客户订单，订货会订单，订货会成衣，设计师样衣，秋冬补款，春夏订货会）
#define  DBOrderSales_V_key_iFilesNum       _T("iFilesNum")	//2018-01-25 yangjr 文件个数
#define  DBOrderSales_V_key_cFactoryMemo    _T("cFactoryMemo")	//厂内备注 yangjr 2018/6/15
#define DBOrderSales_V_key_cWeb_Materials   _T("cWeb_Materials")    //web下单，材质
#define DBOrderSales_V_key_iCurProSort       _T("iCurProSort") //DB类未处理 仅用于判断工序逻辑相关操作
#define DBOrderSales_V_key_iCurProState      _T("iCurProState")//DB类未处理
#define DBOrderSales_V_key_cProOrder         _T("cProOrder")   //DB类未处理
#define DBOrderSales_V_key_cGongyishi        _T("cGongyishi")    //工艺师
#define DBOrderSales_V_key_cZuoFeiMemo        _T("cZuoFeiMemo")    //作废说明 yangjr 2018/7/14
#define DBOrderSales_V_key_fTuanGouJia        _T("fTuanGouJia")    //团购价 yangjr 2018/7/17
#define DBOrderSales_V_ColorState             _T("ColorState") //订单的状态颜色
#define DBOrderSales_V_key_iFanLiFlag        _T("iFanLiFlag") //返利标志 yangjr 2018/8/7
#define DBOrderSales_V_key_fDiaoPaiJia       _T("fDiaoPaiJia") //吊牌价 yangjr 2018/8/8
#define DBOrderSales_V_key_cSalesID           _T("cSalesID")   //业务员ID yangjr 2018/9/1
#define DBOrderSales_V_key_cSalesCode       _T("cSalesCode")   //销售单号 yangjr 2018/9/6
#define DBOrderSales_V_key_fZMDLingShouDanJia       _T("fZMDLingShouDanJia")   //专卖店零售单价 lida 2018/11/09

#define  DBOrderSales_V_key_cShazhi			_T("cShazhi")
#define  DBOrderSales_V_key_cChenfen		_T("cChenfen")
#define  DBOrderSales_V_key_cSeming			_T("cSeming")
#define  DBOrderSales_V_key_cColorCate		_T("cColorCate")
#define  DBOrderSales_V_key_cChenfen2       _T("cChenfen2")   //成份2 yangjr 2018/9/26
#define  DBOrderSales_V_key_cChenfen3       _T("cChenfen3")   //成份3:纱线品种成分 	by WangZY 2019/03/07 
#define  DBOrderSales_V_key_cInvSehao		   _T("cInvSehao")
#define  DBOrderSales_V_key_cInvPeise		   _T("cInvPeise")
#define  DBOrderSales_V_key_cChiMa          _T("cChiMa")   
#define  DBOrderSales_V_key_nProcessPercent  _T("nProcessPercent")  

#define DBOrderSales_V_key_dLastOperatorDate _T("dLastOperatorDate") //最后操作时间    	by WangZY 2018/12/11
#define DBOrderSales_V_key_cCusPerson      _T("cCusPerson")   //联系人 liuhw 2018/12/28

#define DBOrderSales_V_key_cOutSourceFactory         _T("cOutSourceFactory") //委外订单委外的工厂ID yangjr 2019/02/27
#define DBOrderSales_V_key_dOutSourceDate            _T("dOutSourceDate") //委外订单委外的时间 yangjr 2019/02/27
#define DBOrderSales_V_key_cOutSourceFactoryName         _T("cOutSourceFactoryName") //委外订单委外的工厂名 yang
#define DBOrderSales_V_key_cStorageCode      _T("cStorageCode") //成衣匹配库存单号   
#define DBOrderSales_V_key_nPeihuoStorageID      _T("nPeihuoStorageID") //成衣匹配库存ID yangjr 2019/03/24  
#define DBOrderSales_V_key_cGongyiShiName _T("cGongyiShiName") //工艺师名称 yangjr 2019/03/24
#define DBOrderSales_V_key_cLastOperatorName _T("cLastOperatorName") //最后操作人 yangjr 2019/04/21

/*==============================子单所对应的工序记录以及相关详情的视图 dbo.V_ProcessRecords wangzl 2018/10/08==============================*/
#define  DBProcessRecords_V_key_ID                     _T("ID")
#define  DBProcessRecords_V_key_cCode                  _T("cCode")
#define  DBProcessRecords_V_key_cGXName                _T("cGXName")
#define  DBProcessRecords_V_key_dDate1                 _T("dDate1")
#define  DBProcessRecords_V_key_dDate3                 _T("dDate3")
#define  DBProcessRecords_V_key_cPersonCode            _T("cPersonCode")
#define  DBProcessRecords_V_key_iGongjia               _T("iGongjia")
#define  DBProcessRecords_V_key_iFujia                 _T("iFujia")
#define  DBProcessRecords_V_key_cMemo                  _T("cMemo")
#define  DBProcessRecords_V_key_iState                 _T("iState")
#define  DBProcessRecords_V_key_cAllotPersonCode       _T("cAllotPersonCode")
#define  DBProcessRecords_V_key_iPriority              _T("iPriority")
#define  DBProcessRecords_V_key_iFlag                  _T("iFlag")
#define  DBProcessRecords_V_key_iCurProcess            _T("iCurProcess")
#define  DBProcessRecords_V_key_dDateAssign            _T("dDateAssign")
#define  DBProcessRecords_V_key_iChecked               _T("iChecked")
#define  DBProcessRecords_V_key_nRewindNum             _T("nRewindNum")
#define  DBProcessRecords_V_key_nRewindFrom            _T("nRewindFrom")
#define  DBProcessRecords_V_key_cCate                  _T("cCate")
#define  DBProcessRecords_V_key_dDate                  _T("dDate")
#define  DBProcessRecords_V_key_cMaker                 _T("cMaker")
#define  DBProcessRecords_V_key_cCusCode               _T("cCusCode")
#define  DBProcessRecords_V_key_cInvCustCode           _T("cInvCustCode")
#define  DBProcessRecords_V_key_cInvCustName           _T("cInvCustName")
#define  DBProcessRecords_V_key_iAllJianshu            _T("iAllJianshu")
#define  DBProcessRecords_V_key_cInvKuanhao            _T("cInvKuanhao")
#define  DBProcessRecords_V_key_cInvJinxian            _T("cInvJinxian")
#define  DBProcessRecords_V_key_cInvLingxing           _T("cInvLingxing")
#define  DBProcessRecords_V_key_cInvDibian             _T("cInvDibian")
#define  DBProcessRecords_V_key_cInvJiagongfei         _T("cInvJiagongfei")
#define  DBProcessRecords_V_key_cInvFujiafei           _T("cInvFujiafei")
#define  DBProcessRecords_V_key_cSexType               _T("cSexType")
#define  DBProcessRecords_V_key_cShouYao               _T("cShouYao")
#define  DBProcessRecords_V_key_cZhiYiCode             _T("cZhiYiCode")
#define  DBProcessRecords_V_key_dJiaoDate              _T("dJiaoDate")
#define  DBProcessRecords_V_key_dTrueTime              _T("dTrueTime")
#define  DBProcessRecords_V_key_cNeedleType            _T("cNeedleType")
#define  DBProcessRecords_V_key_iOtherFlag             _T("iOtherFlag")
#define  DBProcessRecords_V_key_iOrdCreateFlag         _T("iOrdCreateFlag")
#define  DBProcessRecords_V_key_cMacType               _T("cMacType")
#define  DBProcessRecords_V_key_cClassType             _T("cClassType")
#define  DBProcessRecords_V_key_cAmountType            _T("cAmountType")
#define  DBProcessRecords_V_key_cGoodsType             _T("cGoodsType")
#define  DBProcessRecords_V_key_cInvXiukou             _T("cInvXiukou")
#define  DBProcessRecords_V_key_cInvJiaji              _T("cInvJiaji")
#define  DBProcessRecords_V_key_cInvMemo               _T("cInvMemo")
#define  DBProcessRecords_V_key_cInvState              _T("cInvState")
#define  DBProcessRecords_V_key_cInvFahuoDate          _T("cInvFahuoDate")
#define  DBProcessRecords_V_key_cInvState2             _T("cInvState2")
#define  DBProcessRecords_V_key_cInvSehao              _T("cInvSehao")
#define  DBProcessRecords_V_key_cInvPeise              _T("cInvPeise")
#define  DBProcessRecords_V_key_cCusName               _T("cCusName")
#define  DBProcessRecords_V_key_cCusMobile             _T("cCusMobile")
#define  DBProcessRecords_V_key_cKuanming              _T("cKuanming")
#define  DBProcessRecords_V_key_cTreeName              _T("cTreeName")
#define  DBProcessRecords_V_key_cChenfen               _T("cChenfen")
#define  DBProcessRecords_V_key_cColorCate             _T("cColorCate")
#define  DBProcessRecords_V_key_cCusCate               _T("cCusCate")
#define  DBProcessRecords_V_key_iChuguan               _T("iChuguan")
#define  DBProcessRecords_V_key_iChuweight             _T("iChuweight")
#define  DBProcessRecords_V_key_iHuiguan               _T("iHuiguan")
#define  DBProcessRecords_V_key_iHuiweight             _T("iHuiweight")
#define  DBProcessRecords_V_key_iPianweight            _T("iPianweight")
#define  DBProcessRecords_V_key_iGuanweight            _T("iGuanweight")
#define  DBProcessRecords_V_key_iMakeNum               _T("iMakeNum")
#define  DBProcessRecords_V_key_iScrapWeight           _T("iScrapWeight")
#define  DBProcessRecords_V_key_cPihao                 _T("cPihao")
#define  DBProcessRecords_V_key_cPersonName            _T("cPersonName")
#define  DBProcessRecords_V_key_cAllotPersonName       _T("cAllotPersonName")
#define  DBProcessRecords_V_key_biFlag                 _T("biFlag")     //kdv查看状态

/*==============================用户款式权限视图 dbo.V_User_Style_Permission wangzl 2019/05/06==============================*/
#define  DBUserStylePermission_V_key_cUserID                    _T("cUserID")
#define  DBUserStylePermission_V_key_cKuanhao                   _T("cKuanhao")
#define  DBUserStylePermission_V_key_nPermission                _T("nPermission")
#define  DBUserStylePermission_V_key_FixPermission              _T("FixPermission")
#define  DBUserStylePermission_V_key_nUserType                  _T("nUserType")
#define  DBUserStylePermission_V_key_nPermissionTime            _T("nPermissionTime")


/*==============================款式下道工序信息 dbo.V_Kuanshi_NextProInfo wangzl 2019/05/23==============================*/
#define  DBKuanshi_NextProInfo_V_key_cKuanhao                  _T("cKuanhao")
#define  DBKuanshi_NextProInfo_V_key_cGXName                   _T("cGXName")
#define  DBKuanshi_NextProInfo_V_key_cNextUserID               _T("cNextUserID")
#define  DBKuanshi_NextProInfo_V_key_bIsGroup                  _T("bIsGroup")

/*==============================款式对应的文件信息 dbo.V_StyleFileInfo wangzl 2019/05/23==============================*/
#define  DBStyleFileInfo_V_key_ID                              _T("ID")
#define  DBStyleFileInfo_V_key_nFileID                         _T("nFileID")
#define  DBStyleFileInfo_V_key_cStyleNo                        _T("cStyleNo")
#define  DBStyleFileInfo_V_key_nFileType                       _T("nFileType")
#define  DBStyleFileInfo_V_key_cRelativePath                   _T("cRelativePath")
#define  DBStyleFileInfo_V_key_cUploadUserID                   _T("cUploadUserID")
#define  DBStyleFileInfo_V_key_cUploadTime                     _T("cUploadTime")
#define  DBStyleFileInfo_V_key_cFileMD5                        _T("cFileMD5")
#define  DBStyleFileInfo_V_key_cFileName                       _T("cFileName")
#define  DBStyleFileInfo_V_key_cFileExtension                  _T("cFileExtension")
#define  DBStyleFileInfo_V_key_nFileSize                       _T("nFileSize")
#define  DBStyleFileInfo_V_key_cRemark                         _T("cRemark")
#define  DBStyleFileInfo_V_key_nSort                           _T("nSort")
#define  DBStyleFileInfo_V_key_nParam_FileType                 _T("nParam_FileType")
#define  DBStyleFileInfo_V_key_nParam_WholeType                _T("nParam_WholeType")
#define  DBStyleFileInfo_V_key_cParam_Size                     _T("cParam_Size")

/*==============================样衣的文件信息 dbo.V_StyleFileInfo wangzl 2019/05/23==============================*/
#define  DBSampleClothing_V_key_ID                              _T("ID")
#define  DBSampleClothing_V_key_nFileID                         _T("nFileID")
#define  DBSampleClothing_V_key_cBarCode                        _T("cBarCode")
#define  DBSampleClothing_V_key_nFileType                       _T("nFileType")
#define  DBSampleClothing_V_key_cRelativePath                   _T("cRelativePath")
#define  DBSampleClothing_V_key_cUploadUserID                   _T("cUploadUserID")
#define  DBSampleClothing_V_key_cUploadTime                     _T("cUploadTime")
#define  DBSampleClothing_V_key_cFileMD5                        _T("cFileMD5")
#define  DBSampleClothing_V_key_cFileName                       _T("cFileName")
#define  DBSampleClothing_V_key_cFileExtension                  _T("cFileExtension")
#define  DBSampleClothing_V_key_nFileSize                       _T("nFileSize")
#define  DBSampleClothing_V_key_cRemark                         _T("cRemark")

/*==============================云模块管理视图表  dbo.V_CloudModuleInfo   WangZY 2019/06/03==============================*/
#define DBCloudModuleInfo_V_Key_ID                    _T("ID")                      //模块文件ID
#define DBCloudModuleInfo_V_Key_cOldFileName          _T("cOldFileName")            //模块文件名
#define DBCloudModuleInfo_V_Key_cFileSavePath         _T("cFileSavePath")           //模块文件路径
#define DBCloudModuleInfo_V_Key_nFileType             _T("nFileType")               //模块文件类型:(目前是记录模块是否免费，0为加密，1为免费）
#define DBCloudModuleInfo_V_Key_bUploadSuccess        _T("bUploadSuccess")          //模块文件是否上传完成
#define DBCloudModuleInfo_V_Key_dwState               _T("dwState")                 //模块文件状态
#define DBCloudModuleInfo_V_Key_cDescription          _T("cDescription")            //模块文件描述
#define DBCloudModuleInfo_V_Key_cVerifyComment        _T("cVerifyComment")          //模块文件审核人评语
#define DBCloudModuleInfo_V_Key_cCheckCode            _T("cCheckCode")              //模块文件校验码(MD5值)
#define DBCloudModuleInfo_V_Key_cModType              _T("cModType")                //模块类型(分类)
#define DBCloudModuleInfo_V_Key_cProvider             _T("cProvider")               //模块文件的供应商
#define DBCloudModuleInfo_V_Key_cTelPhone             _T("cTelPhone")               //模块文件联系电话
#define DBCloudModuleInfo_V_Key_nDownLoadNum          _T("nDownLoadNum")            //模块文件下载次数
#define DBCloudModuleInfo_V_Key_cUserID               _T("cUserID")                 //上传者ID
#define DBCloudModuleInfo_V_Key_cUserName             _T("cUserName")               //上传者名称
#define DBCloudModuleInfo_V_Key_cUserPower            _T("cUserPower")              //上传者权限
#define DBCloudModuleInfo_V_Key_dtRegeditTime         _T("dtRegeditTime")           //上传者注册时间
#define DBCloudModuleInfo_V_Key_dwUserState           _T("dwUserState")             //上传者状态
#define DBCloudModuleInfo_V_Key_cWechat               _T("cWechat")                 //上传者微信
#define DBCloudModuleInfo_V_Key_cQQ                   _T("cQQ")                     //上传者QQ
#define DBCloudModuleInfo_V_Key_cRemark               _T("cRemark")                 //上传者备注
#define DBCloudModuleInfo_V_Key_cSignature            _T("cSignature")              //上传者修改签名
#define DBCloudModuleInfo_V_Key_cPhoneNum             _T("cPhoneNum")               //上传者电话号码

/*==============================款式成本视图  dbo.V_Style_Cost   wangl 2019/06/11==============================*/
#define DBStyleCost_V_ID                _T("ID")
#define DBStyleCost_V_cStyleNo          _T("cStyleNo")
#define DBStyleCost_V_cCostItem         _T("cCostItem")
#define DBStyleCost_V_cCostType         _T("cCostType")
#define DBStyleCost_V_fCostPrice        _T("fCostPrice")
#define DBStyleCost_V_fCostAddedValue   _T("fCostAddedValue")
#define DBStyleCost_V_fSalesPrice       _T("fSalesPrice")
#define DBStyleCost_V_fSalesAddedValue  _T("fSalesAddedValue")
#define DBStyleCost_V_fCalculatedValue  _T("fCalculatedValue")
#define DBStyleCost_V_fCost             _T("fCost")
#define DBStyleCost_V_fQuotedPrice      _T("fQuotedPrice")

/*==============================用户任务信息视图  dbo.V_UserTaskInfo   wangl 2019/06/14==============================*/
#define DBUserTaskInfo_V_cUserID            _T("cUserID")
#define DBUserTaskInfo_V_cKuanhao           _T("cKuanhao")
#define DBUserTaskInfo_V_nTaskType          _T("nTaskType")
#define DBUserTaskInfo_V_bIsGroup           _T("bIsGroup")

