#pragma once

//���ݿ���ֶ�,��ͼ��������ͨ��		add by lida 2018/02/05

/*==============================�� dbo.V_Kuanshi ==============================*/
//��ͼ����ص������ֶ�

#define DBVStyle_key_cCusName			_T("cCusName")		//->�ͻ���		DBCustomer_key_Name
#define DBVStyle_key_cCusAbbName		_T("cCusAbbName")	//�ͻ���		DBCustomer_key_Abbrev
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
#define DBVStyle_key_bIsDeleted   _T("bIsDeleted") //��ʽ�Ƿ�ɾ�� yangjr 2019/05/20
#define DBVStyle_key_iGXSortID       _T("iGXSortID")//��ǰ�����ID
#define DBVStyle_key_cGXPersonCode   _T("cGXPersonCode")//��ǰ�����ִ����ID
#define DBVStyle_key_cState         _T("cState")//��ǰ�����ִ����ID
#define DBVStyle_key_cDesigner      _T("cDesigner")
#define DBVStyle_key_cCraftsmen     _T("cCraftsmen")
#define DBVStyle_key_cPatternMaker  _T("cPatternMaker")
#define DBVStyle_key_cFangAnName    _T("cFangAnName")

#define DBVStyle_key_cCustomField1          _T("cCustomField1")           //�Զ����ֶ�1     wangzl 2019/07/02
#define DBVStyle_key_cCustomField2          _T("cCustomField2")           //�Զ����ֶ�2     wangzl 2019/07/02
#define DBVStyle_key_cCustomField3          _T("cCustomField3")           //�Զ����ֶ�3     wangzl 2019/07/02
#define DBVStyle_key_cCustomField4          _T("cCustomField4")           //�Զ����ֶ�4     wangzl 2019/07/02
#define DBVStyle_key_cCustomField5          _T("cCustomField5")           //�Զ����ֶ�5     wangzl 2019/07/02
#define DBVStyle_key_cCustomField6          _T("cCustomField6")           //�Զ����ֶ�6     wangzl 2019/07/02
#define DBVStyle_key_cCustomField7          _T("cCustomField7")           //�Զ����ֶ�7     wangzl 2019/07/02
#define DBVStyle_key_cCustomField8          _T("cCustomField8")           //�Զ����ֶ�8     wangzl 2019/07/02
#define DBVStyle_key_cCustomField9          _T("cCustomField9")           //�Զ����ֶ�9     wangzl 2019/07/02
#define DBVStyle_key_cCustomField10         _T("cCustomField10")          //�Զ����ֶ�10    wangzl 2019/07/02

#define DBVStyle_key_cHelpSeekerID          _T("cHelpSeeker")             //������ID        duc    2019/07/18
/*==============================BandProgramming��ͼ dbo. ==============================*/
#define DBV_BANDPROGRAMMING_Key_ID                                 _T("ID")
#define DBV_BANDPROGRAMMING_Key_cSeriaNum                          _T("cSeriaNum")               //���
#define DBV_BANDPROGRAMMING_Key_cName                              _T("cName")                   //����
#define DBV_BANDPROGRAMMING_Key_cBindStartTime                     _T("cBandStartTime")          //���ο�ʼʱ��
#define DBV_BANDPROGRAMMING_Key_cDesignEndTime                     _T("cDesignEndTime")          //������ʱ��
#define DBV_BANDPROGRAMMING_Key_cPatternEndTime                    _T("cPatternEndTime")         //ֽ�����ʱ��
#define DBV_BANDPROGRAMMING_Key_cReviewEndTime                     _T("cReviewEndTime")          //��������ʱ��
#define DBV_BANDPROGRAMMING_Key_cBandEndTime                       _T("cBandEndTime")            //���ν���ʱ��
#define DBV_BANDPROGRAMMING_Key_cDeliveryStartTime                 _T("cDeliveryStartTime")      //������ʼʱ��
#define DBV_BANDPROGRAMMING_Key_cDeliveryEndTime                   _T("cDeliveryEndTime")        //���ڽ���ʱ��
#define DBV_BANDPROGRAMMING_Key_cShelvesTime                       _T("cShelvesTime")            //�ϻ���
#define DBV_BANDPROGRAMMING_Key_cStylish                           _T("cStylish")                //���
#define DBV_BANDPROGRAMMING_Key_cColor                             _T("cColor")                  //ɫϵ
#define DBV_BANDPROGRAMMING_Key_cCreateUserID                      _T("cCreateUserID")           //������
#define DBV_BANDPROGRAMMING_Key_cCreateUserTime                    _T("cCreateUserTime")         //����ʱ��
#define DBV_BANDPROGRAMMING_Key_bCheckState                        _T("bCheckState")             //��˱�ʶ
#define DBV_BANDPROGRAMMING_Key_cCheckUserID                       _T("cCheckUserID")            //�����
#define DBV_BANDPROGRAMMING_Key_cCheckTime                         _T("cCheckTime")              //���ʱ��
#define DBV_BANDPROGRAMMING_Key_cRemark                            _T("cRemark")                 //��ע
#define DBV_BANDPROGRAMMING_Key_nAssociatedProgrammingID           _T("nAssociatedProgrammingID")// ������Ʒ�滮��ID
#define DBV_BANDPROGRAMMING_Key_ProgrammingID                      _T("ProgrammingID")           //��ƷID
#define DBV_BANDPROGRAMMING_Key_cBrand                             _T("cBrand")                   //Ʒ��
#define DBV_BANDPROGRAMMING_Key_nYears                             _T("nYears")                   //���
#define DBV_BANDPROGRAMMING_Key_cSeason                            _T("cSeason")                  //����
#define DBV_BANDPROGRAMMING_Key_cTradeFairTime                     _T("cTradeFairTime")           //������ʱ��
#define DBV_BANDPROGRAMMING_Key_cArea                              _T("cArea")                    //����
#define DBV_BANDPROGRAMMING_Key_nAssociatedPlanningID              _T("nAssociatedPlanningID")    //������ID
#define DBV_BANDPROGRAMMING_Key_cProgrammingCreateUserID           _T("cProgrammingCreateUserID") //��Ʒ������ID   

/*==============================BandProgramming��ͼ dbo. ==============================*/

/*==============================��Ʒ������ͼ dbo.V_ProductProcess wangzl 2018/08/25==============================*/
#define DBV_ProductProcess_Key_ID                                   _T("ID")                           //
#define DBV_ProductProcess_Key_cClassification                      _T("cClassification")              //����    
#define DBV_ProductProcess_Key_cCategory                            _T("cCategory")                    //Ʒ��    
#define DBV_ProductProcess_Key_nPieceNum                            _T("nPieceNum")                    //����    
#define DBV_ProductProcess_Key_cColor                               _T("cColor")                       //ɫ��    
#define DBV_ProductProcess_Key_cSize                                _T("cSize")                        //����    
#define DBV_ProductProcess_Key_cFabric                              _T("cFabric")                      //����    
#define DBV_ProductProcess_Key_cFashion                             _T("cFashion")                     //���ͷ��
#define DBV_ProductProcess_Key_cContour                             _T("cContour")                     //����    
#define DBV_ProductProcess_Key_fPrice_Ceiling                       _T("fPrice_Ceiling")               //�۸�����
#define DBV_ProductProcess_Key_fPrice_Floor                         _T("fPrice_Floor")                 //�۸�����
#define DBV_ProductProcess_Key_fPrice_Tag                           _T("fPrice_Tag")                   //���Ƽ�  
#define DBV_ProductProcess_Key_cRemark                              _T("cRemark")                      //��ע    
#define DBV_ProductProcess_Key_cBand_Name                           _T("cBand_Name")                   //����
#define DBV_ProductProcess_Key_cBand_BandStartTime                  _T("cBand_BandStartTime")          //���ο�ʼʱ��   
#define DBV_ProductProcess_Key_cBand_DesignEndTime                  _T("cBand_DesignEndTime")          //������ʱ��   
#define DBV_ProductProcess_Key_cBand_PatternEndTime                 _T("cBand_PatternEndTime")         //ֽ�����ʱ��   
#define DBV_ProductProcess_Key_cBand_ReviewEndTime                  _T("cBand_ReviewEndTime")          //��������ʱ��
#define DBV_ProductProcess_Key_cBand_BandEndTime                    _T("cBand_BandEndTime")            //���ν���ʱ��
#define DBV_ProductProcess_Key_cBand_DeliveryStartTime              _T("cBand_DeliveryStartTime")      //������ʼʱ��
#define DBV_ProductProcess_Key_cBand_DeliveryEndTime                _T("cBand_DeliveryEndTime")        //���ڽ���ʱ��
#define DBV_ProductProcess_Key_cBand_ShelvesTime                    _T("cBand_ShelvesTime")            //�ϻ���
#define DBV_ProductProcess_Key_cBand_Stylish                        _T("cBand_Stylish")                //���
#define DBV_ProductProcess_Key_cBand_Color                          _T("cBand_Color")                  //ɫϵ
#define DBV_ProductProcess_Key_cCreateUserID                        _T("cCreateUserID")                //������
#define DBV_ProductProcess_Key_cCreateTime                          _T("cCreateTime")                  //����ʱ��
#define DBV_ProductProcess_Key_nCreateFlag                          _T("nCreateFlag")                  //������Դ  ���ڼ�¼��ֱ�Ӵ����Ĳ�Ʒ  ����ͨ�����δ����Ĳ�Ʒ
#define DBV_ProductProcess_Key_cProgramming_Brand                   _T("cProgramming_Brand")           //Ʒ��
#define DBV_ProductProcess_Key_cProgramming_Years                   _T("cProgramming_Years")           //���
#define DBV_ProductProcess_Key_cProgramming_Season                  _T("cProgramming_Season")          //����
#define DBV_ProductProcess_Key_cProgramming_TradeFairTime           _T("cProgramming_TradeFairTime")   //������ʱ��
#define DBV_ProductProcess_Key_cProgramming_Area                    _T("cProgramming_Area")            //����
#define DBV_ProductProcess_Key_cPlanning_SubjectName                _T("cPlanning_SubjectName")        //������
#define DBV_ProductProcess_Key_cCheckUserID                         _T("cCheckUserID")                 //�����
#define DBV_ProductProcess_Key_cCheckTime                           _T("cCheckTime")                   //���ʱ��
#define DBV_ProductProcess_Key_bCheckState                          _T("bCheckState")                  //���״̬

#define DBV_ProductProcess_Key_cAssignUserID                        _T("cAssignUserID")                     //ָ�ɵ��˵�ID
#define DBV_ProductProcess_Key_nPersonType                          _T("nPersonType")                       //��ָ�ɵ��˵���Ա����

#define DBV_ProductProcess_Key_ProcessID                             _T("ProcessRecordsID")                 //
#define DBV_ProductProcess_Key_nAssociatedProductID                  _T("nAssociatedProductID")             //�����Ĳ�ƷID
#define DBV_ProductProcess_Key_cReceiveUserID                        _T("cReceiveUserID")                   //������
#define DBV_ProductProcess_Key_cSponsorID                            _T("cSponsorID")                       //��������
#define DBV_ProductProcess_Key_nProcessType                          _T("nProcessType")                     //��Ӧ�Ĺ���
#define DBV_ProductProcess_Key_cInitiateTime                         _T("cInitiateTime")                    //������ʱ��
#define DBV_ProductProcess_Key_cRealStartTime                        _T("cRealStartTime")                   //����ʵ�ʿ�ʼʱ��
#define DBV_ProductProcess_Key_cFinishTime                           _T("cFinishTime")                      //�������ʱ��
#define DBV_ProductProcess_Key_nState                                _T("nState")                           //״̬
#define DBV_ProductProcess_Key_nCheckState                           _T("nCheckState")                      //���

/*==============================��Ʒ�汾������ͼ dbo.V_ProductVersionOrders wangzl 2018/08/30==============================*/
#define DBV_ProductVersionOrders_Key_ID                              _T("ID")                               //
#define DBV_ProductVersionOrders_Key_cClassification                 _T("cClassification")                  //����    
#define DBV_ProductVersionOrders_Key_cCategory                       _T("cCategory")                        //Ʒ��    
#define DBV_ProductVersionOrders_Key_nPieceNum                       _T("nPieceNum")                        //����    
#define DBV_ProductVersionOrders_Key_cColor                          _T("cColor")                           //ɫ��    
#define DBV_ProductVersionOrders_Key_cSize                           _T("cSize")                            //����    
#define DBV_ProductVersionOrders_Key_cFabric                         _T("cFabric")                          //����    
#define DBV_ProductVersionOrders_Key_cFashion                        _T("cFashion")                         //���ͷ��
#define DBV_ProductVersionOrders_Key_cContour                        _T("cContour")                         //����    
#define DBV_ProductVersionOrders_Key_fPrice_Ceiling                  _T("fPrice_Ceiling")                   //�۸�����
#define DBV_ProductVersionOrders_Key_fPrice_Floor                    _T("fPrice_Floor")                     //�۸�����
#define DBV_ProductVersionOrders_Key_fPrice_Tag                      _T("fPrice_Tag")                       //���Ƽ�  
#define DBV_ProductVersionOrders_Key_cRemark                         _T("cRemark")                          //��ע    
#define DBV_ProductVersionOrders_Key_cBand_Name                      _T("cBand_Name")                       //����
#define DBV_ProductVersionOrders_Key_cBand_BandStartTime             _T("cBand_BandStartTime")              //���ο�ʼʱ��   
#define DBV_ProductVersionOrders_Key_cBand_DesignEndTime             _T("cBand_DesignEndTime")              //������ʱ��   
#define DBV_ProductVersionOrders_Key_cBand_PatternEndTime            _T("cBand_PatternEndTime")             //ֽ�����ʱ��   
#define DBV_ProductVersionOrders_Key_cBand_ReviewEndTime             _T("cBand_ReviewEndTime")              //��������ʱ��
#define DBV_ProductVersionOrders_Key_cBand_BandEndTime               _T("cBand_BandEndTime")                //���ν���ʱ��
#define DBV_ProductVersionOrders_Key_cBand_DeliveryStartTime         _T("cBand_DeliveryStartTime")          //������ʼʱ��
#define DBV_ProductVersionOrders_Key_cBand_DeliveryEndTime           _T("cBand_DeliveryEndTime")            //���ڽ���ʱ��
#define DBV_ProductVersionOrders_Key_cBand_ShelvesTime               _T("cBand_ShelvesTime")                //�ϻ���
#define DBV_ProductVersionOrders_Key_cBand_Stylish                   _T("cBand_Stylish")                    //���
#define DBV_ProductVersionOrders_Key_cBand_Color                     _T("cBand_Color")                      //ɫϵ
#define DBV_ProductVersionOrders_Key_cCreateUserID                   _T("cCreateUserID")                    //������
#define DBV_ProductVersionOrders_Key_cCreateTime                     _T("cCreateTime")                      //����ʱ��
#define DBV_ProductVersionOrders_Key_nCreateFlag                     _T("nCreateFlag")                      //������Դ  ���ڼ�¼��ֱ��
#define DBV_ProductVersionOrders_Key_cProgramming_Brand              _T("cProgramming_Brand")               //Ʒ��
#define DBV_ProductVersionOrders_Key_cProgramming_Years              _T("cProgramming_Years")               //���
#define DBV_ProductVersionOrders_Key_cProgramming_Season             _T("cProgramming_Season")              //����
#define DBV_ProductVersionOrders_Key_cProgramming_TradeFairTime      _T("cProgramming_TradeFairTime")       //������ʱ��
#define DBV_ProductVersionOrders_Key_cProgramming_Area               _T("cProgramming_Area")                //����
#define DBV_ProductVersionOrders_Key_cPlanning_SubjectName           _T("cPlanning_SubjectName")            //������
#define DBV_ProductVersionOrders_Key_cCheckUserID                    _T("cCheckUserID")                     //�����
#define DBV_ProductVersionOrders_Key_cCheckTime                      _T("cCheckTime")                       //���ʱ��
#define DBV_ProductVersionOrders_Key_bCheckState                     _T("bCheckState")                      //���״̬
#define DBV_ProductVersionOrders_Key_nCurProSort                     _T("nCurProSort")                      //��ǰ����ID
#define DBV_ProductVersionOrders_Key_bRevision                       _T("bRevision")                        //�Ƿ���Ҫ�İ�
#define DBV_ProductVersionOrders_Key_cRevisionReason                 _T("cRevisionReason")                  //�İ�ԭ��
#define DBV_ProductVersionOrders_Key_VersionID                       _T("VersionID")                        //�汾ID
#define DBV_ProductVersionOrders_Key_cVersion                        _T("cVersion")                         //�汾
#define DBV_ProductVersionOrders_Key_RdRecordsID                     _T("RdRecordsID")                      //������ID
#define DBV_ProductVersionOrders_Key_cCate                           _T("cCate")                            //����
#define DBV_ProductVersionOrders_Key_cCode                           _T("cCode")                            //����
#define DBV_ProductVersionOrders_Key_dDate                           _T("dDate")                            //�µ�����
#define DBV_ProductVersionOrders_Key_cMaker                          _T("cMaker")                           //�Ƶ���
#define DBV_ProductVersionOrders_Key_cInvSehao                       _T("cInvSehao")                        //��ɫ
#define DBV_ProductVersionOrders_Key_cInvPeise                       _T("cInvPeise")                        //��ɫ
#define DBV_ProductVersionOrders_Key_cInvKuanhao                     _T("cInvKuanhao")                      //���
#define DBV_ProductVersionOrders_Key_cInvUnitCost                    _T("cInvUnitCost")                     //����
#define DBV_ProductVersionOrders_Key_cLastPerson                     _T("cLastPerson")                      //��������
#define DBV_ProductVersionOrders_Key_dLastTime                       _T("dLastTime")                        //������ʱ��
#define DBV_ProductVersionOrders_Key_cInvState2                      _T("cInvState2")                       //״̬2
#define DBV_ProductVersionOrders_Key_dTrueTime                       _T("dTrueTime")                        //��ʵ¼��ʱ��
#define DBV_ProductVersionOrders_Key_iOrdCreateFlag                  _T("iOrdCreateFlag")                   //����������ʶ
#define DBV_ProductVersionOrders_Key_cJianshu                        _T("cJianshu")                         //����
#define DBV_ProductVersionOrders_Key_cInvMemo                        _T("cInvMemo")                         //��ע
#define DBV_ProductVersionOrders_Key_cInvState                       _T("cInvState")                        //״̬
#define DBV_ProductVersionOrders_Key_cZuoFeiMemo                     _T("cZuoFeiMemo")                      //����˵��

/*==============================��Ʒ�İ���ͼ dbo.V_ProductRevisionRecords wangzl 2018/09/03==============================*/
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


/*==============================�Ӷ�����ͼ�� dbo.V_RdRecordsChild yangjr 2018/9/26==============================*/
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
#define  DBOrderChild_V_key_cBarCode			_T("cBarCode") //��Ʒ����
#define  DBOrderChild_V_key_cContent			_T("cContent")
#define  DBOrderChild_V_key_cSheng			   _T("cSheng")
#define  DBOrderChild_V_key_cShi				_T("cShi")
#define  DBOrderChild_V_key_iDay				_T("iDay")  //�µ��뵱ǰ������
#define  DBOrderChild_V_key_iDays			_T("iDays") //���µ������뽻�������� �ͻ�����
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
#define  DBOrderChild_V_key_cSexType			_T("cSexType") //�п�Ů��
#define  DBOrderChild_V_key_cShouYao			_T("cShouYao")//����
#define  DBOrderChild_V_key_cTiRong			_T("cTiRong") //����
#define  DBOrderChild_V_key_cZhiYiCode			_T("cZhiYiCode") //���µ���
#define  DBOrderChild_V_key_dJiaoDate		   _T("dJiaoDate") //����
#define  DBOrderChild_V_key_dTrueTime		   _T("dTrueTime") //��ʵ¼��ʱ��
#define  DBOrderChild_V_key_iPrint_XSM	   _T("Print_XSM")      //��ӡ���������order_flag �� print_xsm by lida 2018/07/04
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
#define  DBOrderChild_V_key_MacType         _T("cMacType")	//2018-01-24 zhangt �������ͣ���ҡ ����
#define  DBOrderChild_V_key_ClassType       _T("cClassType")	//2018-01-24 zhangt �������ࣺ�·� ����
#define  DBOrderChild_V_key_AmountType      _T("cAmountType")//2018-01-24 zhangt �������ͣ����壬���룩
#define  DBOrderChild_V_key_GoodsType       _T("cGoodsType")	//2018-03-20 zhangt �������ͣ��ͻ������������ᶩ������������£����ʦ���£��ﶬ������Ķ����ᣩ
#define  DBOrderChild_V_key_iFilesNum       _T("iFilesNum")	//2018-01-25 yangjr �ļ�����
#define  DBOrderChild_V_key_cFactoryMemo    _T("cFactoryMemo")	//���ڱ�ע yangjr 2018/6/15
#define DBOrderChild_V_key_cWeb_Materials   _T("cWeb_Materials")    //web�µ�������
#define DBOrderChild_V_key_iCurProSort       _T("iCurProSort") //DB��δ���� �������жϹ����߼���ز���
#define DBOrderChild_V_key_iCurProState      _T("iCurProState")//DB��δ����
#define DBOrderChild_V_key_cProOrder         _T("cProOrder")   //DB��δ����
#define DBOrderChild_V_key_cGongyishi        _T("cGongyishi")    //����ʦ
#define DBOrderChild_V_key_cZuoFeiMemo        _T("cZuoFeiMemo")    //����˵�� yangjr 2018/7/14
#define DBOrderChild_V_key_fTuanGouJia        _T("fTuanGouJia")    //�Ź��� yangjr 2018/7/17
#define DBOrderChild_V_ColorState             _T("ColorState") //������״̬��ɫ
#define DBOrderChild_V_key_iFanLiFlag        _T("iFanLiFlag") //������־ yangjr 2018/8/7
#define DBOrderChild_V_key_fDiaoPaiJia       _T("fDiaoPaiJia") //���Ƽ� yangjr 2018/8/8
#define DBOrderChild_V_key_cSalesID           _T("cSalesID")   //ҵ��ԱID yangjr 2018/9/1
#define DBOrderChild_V_key_cSalesCode       _T("cSalesCode")   //���۵��� yangjr 2018/9/6
#define DBOrderChild_V_key_cChenfen2         _T("cChenfen2")   //�ɷ�2 yangjr 2018/9/26
#define DBOrderChild_V_key_cChenfen3         _T("cChenfen3")   //�ɷ�3:ɴ��Ʒ�ֳɷ�   	by WangZY 2019/03/07
#define DBOrderChild_V_key_cCusAddress		_T("cCusAddress")			//�ͻ���ַ
#define DBOrderChild_V_key_fZMDLingShouDanJia       _T("fZMDLingShouDanJia")   //ר�������۵��� lida 2018/11/09
#define DBOrderChild_V_key_iCurBaoIndex         _T("iCurBaoIndex")      //��ǰ���� lida 2018/11/15
#define DBOrderChild_V_key_JiajiPrice        _T("cJiaJiPrice")          //�Ӽ����� anjie 2019/03/29
/*==============================��������ͼ�� dbo.V_RdRecordsSales yangjr 2018/9/27==============================*/
#define  DBOrderSales_V_key_CustomercCate	_T("CustomercCate")
#define  DBOrderSales_V_key_cCusCate		_T("cCusCate")
#define  DBOrderSales_V_key_cCusName		_T("cCusName")
#define  DBOrderSales_V_key_cTreeName		   _T("cTreeName")
#define  DBOrderSales_V_key_cKuanming		   _T("cKuanming")
#define  DBOrderSales_V_key_cKSChengfen		_T("cKSChengfen")
#define  DBOrderSales_V_key_cBarCode			_T("cBarCode") //��Ʒ����
#define  DBOrderSales_V_key_cContent			_T("cContent")
#define  DBOrderSales_V_key_cSheng			   _T("cSheng")
#define  DBOrderSales_V_key_cShi				_T("cShi")
#define  DBOrderSales_V_key_iDay				_T("iDay")  //�µ��뵱ǰ������
#define  DBOrderSales_V_key_iDays			_T("iDays") //���µ������뽻�������� �ͻ�����
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
#define  DBOrderSales_V_key_cSexType			_T("cSexType") //�п�Ů��
#define  DBOrderSales_V_key_cShouYao			_T("cShouYao")//����
#define  DBOrderSales_V_key_cTiRong			_T("cTiRong") //����
#define  DBOrderSales_V_key_cZhiYiCode			_T("cZhiYiCode") //���µ���
#define  DBOrderSales_V_key_dJiaoDate		   _T("dJiaoDate") //����
#define  DBOrderSales_V_key_dTrueTime		   _T("dTrueTime") //��ʵ¼��ʱ��
#define  DBOrderSales_V_key_iPrint_XSM	   _T("Print_XSM")      //��ӡ���������order_flag �� print_xsm by lida 2018/07/04
#define  DBOrderSales_V_key_cCusMobile		_T("cCusMobile")
#define  DBOrderSales_V_key_cSehao			   _T("cSehao")
#define  DBOrderSales_V_key_cPeise			   _T("cPeise")
#define  DBOrderSales_V_key_cJinxian			_T("cJinxian")
#define  DBOrderSales_V_key_cNeedleType     _T("cNeedleType")
#define  DBOrderSales_V_key_cRunPerson      _T("cRunPerson")
#define  DBOrderSales_V_key_cOutNo          _T("cOutNo")
#define  DBOrderSales_V_key_iOtherFlag      _T("iOtherFlag")
#define  DBOrderSales_V_key_iOrdCreateFlag  _T("iOrdCreateFlag") 
#define  DBOrderSales_V_key_MacType         _T("cMacType")	//2018-01-24 zhangt �������ͣ���ҡ ����
#define  DBOrderSales_V_key_ClassType       _T("cClassType")	//2018-01-24 zhangt �������ࣺ�·� ����
#define  DBOrderSales_V_key_AmountType      _T("cAmountType")//2018-01-24 zhangt �������ͣ����壬���룩
#define  DBOrderSales_V_key_GoodsType       _T("cGoodsType")	//2018-03-20 zhangt �������ͣ��ͻ������������ᶩ������������£����ʦ���£��ﶬ������Ķ����ᣩ
#define  DBOrderSales_V_key_iFilesNum       _T("iFilesNum")	//2018-01-25 yangjr �ļ�����
#define  DBOrderSales_V_key_cFactoryMemo    _T("cFactoryMemo")	//���ڱ�ע yangjr 2018/6/15
#define DBOrderSales_V_key_cWeb_Materials   _T("cWeb_Materials")    //web�µ�������
#define DBOrderSales_V_key_iCurProSort       _T("iCurProSort") //DB��δ���� �������жϹ����߼���ز���
#define DBOrderSales_V_key_iCurProState      _T("iCurProState")//DB��δ����
#define DBOrderSales_V_key_cProOrder         _T("cProOrder")   //DB��δ����
#define DBOrderSales_V_key_cGongyishi        _T("cGongyishi")    //����ʦ
#define DBOrderSales_V_key_cZuoFeiMemo        _T("cZuoFeiMemo")    //����˵�� yangjr 2018/7/14
#define DBOrderSales_V_key_fTuanGouJia        _T("fTuanGouJia")    //�Ź��� yangjr 2018/7/17
#define DBOrderSales_V_ColorState             _T("ColorState") //������״̬��ɫ
#define DBOrderSales_V_key_iFanLiFlag        _T("iFanLiFlag") //������־ yangjr 2018/8/7
#define DBOrderSales_V_key_fDiaoPaiJia       _T("fDiaoPaiJia") //���Ƽ� yangjr 2018/8/8
#define DBOrderSales_V_key_cSalesID           _T("cSalesID")   //ҵ��ԱID yangjr 2018/9/1
#define DBOrderSales_V_key_cSalesCode       _T("cSalesCode")   //���۵��� yangjr 2018/9/6
#define DBOrderSales_V_key_fZMDLingShouDanJia       _T("fZMDLingShouDanJia")   //ר�������۵��� lida 2018/11/09

#define  DBOrderSales_V_key_cShazhi			_T("cShazhi")
#define  DBOrderSales_V_key_cChenfen		_T("cChenfen")
#define  DBOrderSales_V_key_cSeming			_T("cSeming")
#define  DBOrderSales_V_key_cColorCate		_T("cColorCate")
#define  DBOrderSales_V_key_cChenfen2       _T("cChenfen2")   //�ɷ�2 yangjr 2018/9/26
#define  DBOrderSales_V_key_cChenfen3       _T("cChenfen3")   //�ɷ�3:ɴ��Ʒ�ֳɷ� 	by WangZY 2019/03/07 
#define  DBOrderSales_V_key_cInvSehao		   _T("cInvSehao")
#define  DBOrderSales_V_key_cInvPeise		   _T("cInvPeise")
#define  DBOrderSales_V_key_cChiMa          _T("cChiMa")   
#define  DBOrderSales_V_key_nProcessPercent  _T("nProcessPercent")  

#define DBOrderSales_V_key_dLastOperatorDate _T("dLastOperatorDate") //������ʱ��    	by WangZY 2018/12/11
#define DBOrderSales_V_key_cCusPerson      _T("cCusPerson")   //��ϵ�� liuhw 2018/12/28

#define DBOrderSales_V_key_cOutSourceFactory         _T("cOutSourceFactory") //ί�ⶩ��ί��Ĺ���ID yangjr 2019/02/27
#define DBOrderSales_V_key_dOutSourceDate            _T("dOutSourceDate") //ί�ⶩ��ί���ʱ�� yangjr 2019/02/27
#define DBOrderSales_V_key_cOutSourceFactoryName         _T("cOutSourceFactoryName") //ί�ⶩ��ί��Ĺ����� yang
#define DBOrderSales_V_key_cStorageCode      _T("cStorageCode") //����ƥ���浥��   
#define DBOrderSales_V_key_nPeihuoStorageID      _T("nPeihuoStorageID") //����ƥ����ID yangjr 2019/03/24  
#define DBOrderSales_V_key_cGongyiShiName _T("cGongyiShiName") //����ʦ���� yangjr 2019/03/24
#define DBOrderSales_V_key_cLastOperatorName _T("cLastOperatorName") //�������� yangjr 2019/04/21

/*==============================�ӵ�����Ӧ�Ĺ����¼�Լ�����������ͼ dbo.V_ProcessRecords wangzl 2018/10/08==============================*/
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
#define  DBProcessRecords_V_key_biFlag                 _T("biFlag")     //kdv�鿴״̬

/*==============================�û���ʽȨ����ͼ dbo.V_User_Style_Permission wangzl 2019/05/06==============================*/
#define  DBUserStylePermission_V_key_cUserID                    _T("cUserID")
#define  DBUserStylePermission_V_key_cKuanhao                   _T("cKuanhao")
#define  DBUserStylePermission_V_key_nPermission                _T("nPermission")
#define  DBUserStylePermission_V_key_FixPermission              _T("FixPermission")
#define  DBUserStylePermission_V_key_nUserType                  _T("nUserType")
#define  DBUserStylePermission_V_key_nPermissionTime            _T("nPermissionTime")


/*==============================��ʽ�µ�������Ϣ dbo.V_Kuanshi_NextProInfo wangzl 2019/05/23==============================*/
#define  DBKuanshi_NextProInfo_V_key_cKuanhao                  _T("cKuanhao")
#define  DBKuanshi_NextProInfo_V_key_cGXName                   _T("cGXName")
#define  DBKuanshi_NextProInfo_V_key_cNextUserID               _T("cNextUserID")
#define  DBKuanshi_NextProInfo_V_key_bIsGroup                  _T("bIsGroup")

/*==============================��ʽ��Ӧ���ļ���Ϣ dbo.V_StyleFileInfo wangzl 2019/05/23==============================*/
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

/*==============================���µ��ļ���Ϣ dbo.V_StyleFileInfo wangzl 2019/05/23==============================*/
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

/*==============================��ģ�������ͼ��  dbo.V_CloudModuleInfo   WangZY 2019/06/03==============================*/
#define DBCloudModuleInfo_V_Key_ID                    _T("ID")                      //ģ���ļ�ID
#define DBCloudModuleInfo_V_Key_cOldFileName          _T("cOldFileName")            //ģ���ļ���
#define DBCloudModuleInfo_V_Key_cFileSavePath         _T("cFileSavePath")           //ģ���ļ�·��
#define DBCloudModuleInfo_V_Key_nFileType             _T("nFileType")               //ģ���ļ�����:(Ŀǰ�Ǽ�¼ģ���Ƿ���ѣ�0Ϊ���ܣ�1Ϊ��ѣ�
#define DBCloudModuleInfo_V_Key_bUploadSuccess        _T("bUploadSuccess")          //ģ���ļ��Ƿ��ϴ����
#define DBCloudModuleInfo_V_Key_dwState               _T("dwState")                 //ģ���ļ�״̬
#define DBCloudModuleInfo_V_Key_cDescription          _T("cDescription")            //ģ���ļ�����
#define DBCloudModuleInfo_V_Key_cVerifyComment        _T("cVerifyComment")          //ģ���ļ����������
#define DBCloudModuleInfo_V_Key_cCheckCode            _T("cCheckCode")              //ģ���ļ�У����(MD5ֵ)
#define DBCloudModuleInfo_V_Key_cModType              _T("cModType")                //ģ������(����)
#define DBCloudModuleInfo_V_Key_cProvider             _T("cProvider")               //ģ���ļ��Ĺ�Ӧ��
#define DBCloudModuleInfo_V_Key_cTelPhone             _T("cTelPhone")               //ģ���ļ���ϵ�绰
#define DBCloudModuleInfo_V_Key_nDownLoadNum          _T("nDownLoadNum")            //ģ���ļ����ش���
#define DBCloudModuleInfo_V_Key_cUserID               _T("cUserID")                 //�ϴ���ID
#define DBCloudModuleInfo_V_Key_cUserName             _T("cUserName")               //�ϴ�������
#define DBCloudModuleInfo_V_Key_cUserPower            _T("cUserPower")              //�ϴ���Ȩ��
#define DBCloudModuleInfo_V_Key_dtRegeditTime         _T("dtRegeditTime")           //�ϴ���ע��ʱ��
#define DBCloudModuleInfo_V_Key_dwUserState           _T("dwUserState")             //�ϴ���״̬
#define DBCloudModuleInfo_V_Key_cWechat               _T("cWechat")                 //�ϴ���΢��
#define DBCloudModuleInfo_V_Key_cQQ                   _T("cQQ")                     //�ϴ���QQ
#define DBCloudModuleInfo_V_Key_cRemark               _T("cRemark")                 //�ϴ��߱�ע
#define DBCloudModuleInfo_V_Key_cSignature            _T("cSignature")              //�ϴ����޸�ǩ��
#define DBCloudModuleInfo_V_Key_cPhoneNum             _T("cPhoneNum")               //�ϴ��ߵ绰����

/*==============================��ʽ�ɱ���ͼ  dbo.V_Style_Cost   wangl 2019/06/11==============================*/
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

/*==============================�û�������Ϣ��ͼ  dbo.V_UserTaskInfo   wangl 2019/06/14==============================*/
#define DBUserTaskInfo_V_cUserID            _T("cUserID")
#define DBUserTaskInfo_V_cKuanhao           _T("cKuanhao")
#define DBUserTaskInfo_V_nTaskType          _T("nTaskType")
#define DBUserTaskInfo_V_bIsGroup           _T("bIsGroup")

