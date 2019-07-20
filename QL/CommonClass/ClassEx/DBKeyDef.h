#pragma once

//���ݿ���ֶ�,��ͨ����������ͼ		add by lida 2018/02/05

/*==============================������ʽ-ԭ����Ϣ dbo.StyleGoodsInfo add by lida 2018/06/20==============================*/
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



/*==============================������ʽ-������Ϣ dbo.StyleSupMetarial add by huangym 2018/12/24==============================*/
#define DBStyleSupMetarial_ID                  _T("ID")
#define DBStyleSupMetarial_cName               _T("cName")
#define DBStyleSupMetarial_cStyleNo            _T("cStyleNo")
#define DBStyleSupMetarial_nNumber             _T("nNumber")
#define DBStyleSupMetarial_nPrice              _T("nPrice")
#define DBStyleSupMetarial_nSumPrice           _T("nSumPrice")
#define DBStyleSupMetarial_cMemo               _T("cMemo")

/*==============================������ʽ-��ɫ������Ϣ dbo.StyleSupMetarial add by huangym 2018/12/28==============================*/
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

#define DBStyleColor_RowName              _T("RowName")     //������
#define DBStyleColor_ColorName            _T("ColorName")   //ɫ��
#define DBStyleColor_cFirst_Name          _T("cFirstName")
#define DBStyleColor_cSecond_Name          _T("cSecondName")
#define DBStyleColor_cThird_Name           _T("cThirdName")
#define DBStyleColor_cFourth_Name          _T("cFourthName")
#define DBStyleColor_cFifth_Name           _T("cFifthName")
#define DBStyleColor_cSixth_Name           _T("cSixthName")

/*==============================������ʽ-��Ʒ��Ϣ dbo.StyleGoodsInfo add by lida 2018/06/20==============================*/
#define DBStyleGoosInfo_ID                _T("ID")
#define DBStyleGoosInfo_cStyleNo          _T("cStyleNo")
#define DBStyleGoosInfo_cSizeList         _T("cSizeList")
#define DBStyleGoosInfo_cYarnList         _T("cYarnList")
#define DBStyleGoosInfo_cLingXingList     _T("cLingXingList")
#define DBStyleGoosInfo_cNeedleTypeList   _T("cNeedleTypeList")
#define DBStyleGoosInfo_cDiBianList       _T("cDiBianList")
#define DBStyleGoosInfo_cXiuBianList      _T("cXiuBianList")

/*==============================�����¼���� dbo.GongxuRecordsDetails ==============================*/
#define DBGongxuRecordsDetails_ID                              _T("ID")
#define DBGongxuRecordsDetails_iAssociatedGongxuRecordsID      _T("iAssociatedGongxuRecordsID")
#define DBGongxuRecordsDetails_iChuguan                        _T("iChuguan")
#define DBGongxuRecordsDetails_iChuweight                      _T("iChuweight")
#define DBGongxuRecordsDetails_iHuiguan                        _T("iHuiguan")
#define DBGongxuRecordsDetails_iHuiweight                      _T("iHuiweight")
#define DBGongxuRecordsDetails_iPianweight                     _T("iPianweight")
#define DBGongxuRecordsDetails_iGuanweight                     _T("iGuanweight")
#define DBGongxuRecordsDetails_cPihao                          _T("cPihao")

/*==============================������Ϣ����� dbo.CommonProInfo ==============================*/
#define CommonProInfo_key_ID			_T("ID")		//ID
#define CommonProInfo_key_Name			_T("cProName")	//��������
#define CommonProInfo_key_Intro			_T("cIntro")	//������Ϣ
#define CommonProInfo_key_Type			_T("cType")		//�������

/*==============================�۸����ñ� dbo.ColorPrice ==============================*/
#define DBPRICESET_KEY_dDate          _T("dDate")       //����
#define DBPRICESET_KEY_iSunhao        _T("iSunhao")     //���
#define DBPRICESET_KEY_iSalePrice     _T("iSalePrice")  //���۵���
#define DBPRICESET_KEY_iPrice         _T("iPrice")      //����
#define DBPRICESET_KEY_cDaihao        _T("cDaihao")     //Ʒ�ִ���
#define DBPRICESET_KEY_cCate          _T("cCate")       //Ʒ��
#define DBPRICESET_KEY_cCusCode       _T("cCusCode")    //�ͻ����
#define DBPRICESET_KEY_ID             _T("ID")          //ID
#define DBPRICESET_KEY_fZMDSalePrice  _T("fZMDSalePrice") //ר�������۵���
#define DBPRICESET_KEY_fZhekou        _T("fZhekou")     //�ۿ�
#define DBPRICESET_KEY_cChenfen			  _T("cChenfen")		//�ɷ�
#define DBPRICESET_KEY_fBeiLv        _T("fBeiLv")     //����   add anjie by 2018/10/25
/*==============================��˾��Ϣ�� dbo.CompanyInfo ==============================*/
#define DBCompanyInfo_key_Id				_T("ID")
#define DBCompanyInfo_key_Name				_T("Name")
#define DBCompanyInfo_key_Tel				_T("Telephone")
#define DBCompanyInfo_key_Fax				_T("Fax")
#define DBCompanyInfo_key_Address			_T("Address")
#define DBCompanyInfo_key_Sign				_T("Sign")

/*==============================�ͻ���Ϣ�� dbo.Customer ==============================*/
#define  DBCustomer_key_ID			_T("ID")					//����ID
#define  DBCustomer_key_UpdateTime	_T("dDate")					//��������
#define  DBCustomer_key_Cate		_T("cCate")					//����
#define  DBCustomer_key_CusCate		_T("cCusCate")				//�ͻ�����---->������
#define  DBCustomer_key_Code		_T("cCusCode")				//�ͻ�����
#define  DBCustomer_key_Name		_T("cCusName")				//�ͻ�����
#define  DBCustomer_key_Abbrev		_T("cCusAbbName")			//�ͻ����
#define  DBCustomer_key_Addr		_T("cCusAddress")			//�ͻ���ַ
#define  DBCustomer_key_Person		_T("cCusPerson")			//�ͻ���ϵ��
#define  DBCustomer_key_Phone		_T("cCusPhone")				//�ͻ��绰
#define  DBCustomer_key_Fax			_T("cCusFax")				//�ͻ�����
#define  DBCustomer_key_Mobile		_T("cCusMobile")			//�ͻ��ֻ�
#define  DBCustomer_key_WeChat		_T("cCusWeixin")			//�ͻ�΢��
#define  DBCustomer_key_Remark		_T("cCusMemo")				//��ע
#define  DBCustomer_key_VenWeb		_T("cVenWeb")				//�ҵ��µ�ƽ̨
#define  DBCustomer_key_VenCode		_T("cVenCode")				//�ҵ��µ��ʺ�
#define  DBCustomer_key_VenPwd		_T("cVenPassword")			//�ҵ��µ�����
#define  DBCustomer_key_Pwd			_T("cCusPassword")			//��¼����
#define  DBCustomer_key_Arrears		_T("iMoney")				//�ڳ����
#define  DBCustomer_key_Deposit		_T("iDingjin")				//��֤��
#define  DBCustomer_key_Limit		_T("iShangxian")			//Ƿ������
#define  DBCustomer_key_Province	_T("cSheng")				//ʡ
#define  DBCustomer_key_City		_T("cShi")					//��
#define  DBCustomer_key_Area		_T("cQuhao")				//����
#define  DBCustomer_key_State		_T("cState")				//״̬
#define  DBCustomer_key_DeliveDays	_T("iDays")					//��������
#define  DBCustomer_key_Num			_T("iJianshu")				//����
#define  DBCustomer_key_Loss		_T("iSunhao")				//���
#define  DBCustomer_key_EMS			_T("cKuaidi")				//���
#define  DBCustomer_key_ParrentCode	_T("cParentCode")			//�ϼ�����
#define  DBCustomer_key_ClerkCode	_T("cUserCode")				//ҵ��Ա���
#define  DBCustomer_key_Rebate		_T("cFandian")				//����
#define  DBCustomer_key_WorkDoc		_T("cJGD")					//Ĭ�ϼӹ���
#define  DBCustomer_key_Tag			_T("cDP")					//Ĭ�ϵ���
#define  DBCustomer_key_DeliveDoc	_T("cSHD")					//Ĭ�Ϸ�����
#define  DBCustomer_key_DepotPos	_T("cCangwei")				//��λ
#define  DBCustomer_key_Sign		_T("cSign")					//ǩ��
#define  DBCustomer_key_Unit		_T("cCusUnit")				//��λ
#define  DBCustomer_key_LV			_T("iCusLv")				//�ȼ�
#define  DBCustomer_key_iTreeGroupID _T("iTreeGroupID")  //��������ID
#define  DBCustomer_key_iJijiaType  _T("iJijiaType")  //���ۼۼƼ۷�ʽ0����ʾ���ۿۣ�1��ʾ������
#define  DBCustomer_key_fAddinPrice    _T("fAddinPrice")    //���ۼۼӼ�     add by lida 2018/05/24
#define  DBCustomer_key_bPrintDiaoPai  _T("bPrintDiaoPai")  //�Ƿ��ӡ����   add by lida 2018/05/24
#define  DBCustomer_key_bPrintYuE      _T("bPrintYuE")      //�Ƿ��ӡ���   add by lida 2018/05/24
#define  DBCustomer_key_fZMZheKou      _T("fZMZheKou")      //ר���ۿ� yangjr 2018/8/7
#define  DBCustomer_key_cSalesID       _T("cSalesID")       //ҵ��ԱID  add by lida  2018/09/01
/*==============================�� dbo.FieldName ==============================*/
//2017/06/29 zhangt Create ���ݿ����ֶ�
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

/*==============================�����ֵ�� dbo.TreeClass ==============================*/
#define DBDataDic_key_ID			_T("ID")
#define DBDataDic_key_Index			_T("cTreeCate")
#define DBDataDic_key_ItemCode		_T("cTreeCode")
#define DBDataDic_key_ItemName		_T("cTreeName")
#define DBDataDic_key_Description   _T("iMemo1")
#define DBDataDic_key_Value         _T("iMemo2")
#define DBDataDic_key_SysItem		_T("cSysItem") 
#define DBDataDic_key_cSortCode		_T("cSortCode") 

/*==============================ȫ�����ñ� dbo.Config ==============================*/
//2017/07/3 zhangt Create ���ݿ����ֶ�
#define DBGlobalSet_key_ID			_T("ID")
#define DBGlobalSet_key_Name		_T("myName")
#define DBGlobalSet_key_Value		_T("myValue")
#define DBGlobalSet_key_Remark		_T("myMemo")
/*==============================���򷽰��� dbo.FangAnGongxu ==============================*/
//���򷽰��� ���ݿ����ֶ�
#define	 DBFangAnGongxu_key_ID				_T("ID")			//ID
#define  DBFangAnGongxu_key_cFangAnName		_T("cFangAnName")	//������
#define  DBFangAnGongxu_key_cGXName			_T("cGXName")		//������
#define  DBFangAnGongxu_key_cZhiPaiPerson _T("cZhiPaiPerson") //ָ����
/*==============================��־�� dbo.WorkLog ==============================*/
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

/*==============================�˵��� dbo.Menus ==============================*/
//���ݿ����ֶ�
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

/*==============================�� dbo.Order_Flag ==============================*/
#define	DBORDFLAG_KEY_ID				_T("ID")
#define DBORDFLAG_KEY_OrderCode			_T("OrderCode")
#define DBORDFLAG_KEY_Print_GYD			_T("Print_GYD")
#define DBORDFLAG_KEY_Print_XSM			_T("Print_XSM")
#define DBORDFLAG_KEY_Print_SCZSD		_T("Print_SCZSD")
#define DBORDFLAG_KEY_DownLd_MacFile	_T("DownLd_MacFile")


/*==============================�� dbo.Userinfo ==============================*/
#define DBPerson_key_ID				_T("ID")			//ID ����
#define DBPerson_key_TreeCode		_T("cTreeCode")		//�����ֶζ�Ӧ�ֶβ��ű���
#define DBPerson_key_UserID			_T("cUserID")		//�û�ID
#define DBPerson_key_Pwd			_T("cPassword")		//�û�����
#define DBPerson_key_UserName		_T("cUserName")		//�û�����
#define DBPerson_key_UserPower		_T("cUserPower")	//�û�Ȩ��
#define DBPerson_key_UserTel		_T("cUserTel")		//�û���ϵ��ʽ
#define DBPerson_key_UserDate		_T("cUserDate")		//�û�ע��ʱ��
#define DBPerson_key_UserBorn		_T("cUserBorn")		//�û�����
#define DBPerson_key_UserMemo		_T("cUserMemo")		//��ע
#define DBPerson_key_UserSFZ		_T("cUserSFZ")		//���֤
#define DBPerson_key_UserPhoto		_T("cUserPhoto")	//��Ƭ
#define DBPerson_key_UserSale		_T("cUserSale")		//�Ƿ����Ա
#define DBPerson_key_UserDuty		_T("cUserDuty")		//��ݣ�Ա��ְλ��	
#define DBPerson_key_Addr			_T("cAddr")			//��ַ
#define DBPerson_key_InTime			_T("dtInTime")		//���һ�ε�¼ʱ��
#define DBPerson_key_OutTime		_T("dtOutTime")		//ע��ʱ��
#define DBPerson_key_OutFlag		_T("iOutFlag")		//�Ƿ�ע��
#define DBPerson_key_AttriEx     _T("dwAttriEx")   //��չ����
#define DBPerson_key_iSalesman   _T("iSalesman")   //ҵ��Ա
#define DBPerson_key_cUserControlsPermission   _T("cUserControlsPermission")   //�û��ؼ�Ȩ��
#define DBPerson_key_dwTagPermission            _T("dwTagPermission")//��ǩȨ��
#define DBPerson_key_dwFilePermission           _T("dwFilePermission")//�ļ�Ȩ��
#define DBPerson_key_cUserRole                  _T("cUserRole")//��ɫ
#define DBPerson_key_cUserGroup                 _T("cUserGroup")//��

/*==============================������Ϣ�� dbo.Gongxu ==============================*/
//���ݿ����ֶ�
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
#define DBProcess_key_cZhipaiPerson  _T("cZhipaiPerson") //Ĭ��ָ���� yangjr 2018/5/9
#define DBProcess_key_nOtherState  _T("nOtherState")     //����״̬��ϱ�־		by WangZY 2018/09/13
#define DBProcess_key_cGXGongJia  _T("cGXGongJia")       //Ĭ�Ϲ��򹤼�   add anjie by 2018/11/20
#define DBProcess_key_iTipPrice     _T("iTipPrice")      //�Ƿ���ʾ�޸Ĺ��� 
#define DBProcess_key_cBindRole     _T("cBindRole")      //�󶨵Ľ�ɫ  ����ɫ���ƣ�
/*==============================������Ϣ�� dbo.SampleDesDensity ==============================*/
//���ݿ��ܶȱ����ֶ�
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

/*==============================������Ϣ�� dbo.SampleDesFaceCode ==============================*/
//���ݿ�����������ֶ�
#define DBSampleDesFceCode_Key_ID			_T("ID")
#define DBSampleDesFceCode_key_Name			_T("cName")
#define DBSampleDesFceCode_key_OldLen	   _T("fOldLen")
#define DBSampleDesFceCode_key_Type	      _T("cType")
#define DBSampleDesFceCode_key_Len	      _T("fLen")
#define DBSampleDesFceCode_key_Unit       _T("cUnit")
#define DBSampleDesFceCode_Key_IDDensity   _T("IDDensity")

/*==============================�� dbo.ProSet_Style ==============================*/
#define DBProSet_Style_key_ID			   _T("ID")    
#define DBProSet_Style_key_StyleNo		_T("cStyleNo")    //���
#define DBProSet_Style_key_ProName		_T("cProName")    //��������
#define DBProSet_Style_key_UserID		_T("cUserID")     //ָ����ID
#define DBProSet_Style_key_ProTime		_T("dwProTime")   //Ĭ��ʱ��
#define DBProSet_Style_key_fPrice		_T("fPrice")      //���򹤼�
#define DBProSet_Style_key_cIntro		_T("cIntro")      //˵��
#define DBProSet_Style_key_cMark		   _T("cMark")       //Ĭ�����ݱ�־   add anjie by 2018/11/22
#define DBProSet_Style_key_cGXMark     _T("cGXMark")     //������ luzw 2018/12/21
#define DBProSet_Style_key_bIsGroup    _T("bIsGroup")     //�Ƿ���ָ�ɸ���ı�ʶ wangzl 2019-7-16

/*==============================��λ���Ʊ� dbo.[SizePart] ==============================*/
#define DBSizePart_key_ID           _T("ID")
#define DBSizePart_key_Name         _T("cName")
#define DBSizePart_key_Default      _T("iDefault")
#define DBSizePart_key_UserSort     _T("iUserSort")
#define DBSizePart_key_cMemo     _T("cMemo")
/*==============================�� dbo.VariousStyle ==============================*/
#define DBVarious_key_ID				_T("ID")			//����ID
#define DBVarious_key_StyleNo			_T("cStyleNo")		//���
#define DBVarious_key_OrderNo			_T("cOrderNo")		//������
#define DBVarious_key_Destribution		_T("cDestribution")	//����
#define DBVarious_key_Perferred			_T("iPreferred")	//�Ƿ���ѡ

/*==============================�� dbo.Color ɴ�߱�==============================*/
#define DBColor_key_ID			   _T("ID")       //ɴ�߱�����ID
#define DBColor_key_Date		   _T("dDate")    //��������
#define DBColor_key_Cate		   _T("cCate")    //���   ->���������ֵ�
#define DBColor_key_YarnNo		   _T("cSehao")   //ɴ�ߺ�
#define DBColor_key_YarnName	   _T("cSeming") //ɴ������
#define DBColor_key_Ingredient	_T("cChenfen") //ɴ�߳ɷ�
#define DBColor_key_ThickNess	   _T("cShazhi")   //֧��
#define DBColor_key_Remark		   _T("cMemo")       //��ע
#define DBColor_key_Warning		_T("iYujing")     //��������
#define DBColor_key_RGBValue	   _T("cRGBValue")   //��ɫֵ(DWORD)���ݿ�洢Ϊbigintȡ��4���ֽڵ���ֵ����
#define DBColor_key_RGBName		_T("cRGBName")    //��ɫ����
#define DBColor_key_Kind		   _T("iKind")       //����(����/����)
#define DBColor_key_ColorCard	   _T("cColorCard")  //ɫ��
#define DBColor_key_State		   _T("iState")     //���¼ܵı�ʶ
#define DBColor_key_fKucunYujing	_T("fKucunYujing") //���Ԥ������
#define DBColor_key_cGroup       _T("cGroup") //ɫ�� by huangym 2018/12/19
/*==============================�� dbo.ColNameSet ==============================*/
//�ֶ�
#define DBDataColSet_Key_ID             _T("ID")
#define DBDataColSet_Key_cTableID     _T("cTableID")
#define DBDataColSet_Key_cFieldID		_T("cFieldID")
#define DBDataColSet_Key_cFieldName     _T("cFieldName")


/*==============================�� dbo.Kuanshi ==============================*/
#define DBKuanShi_key_ID                     _T("ID")             //����ID
#define DBKuanShi_key_UpdateTime             _T("dDate")          //��������
#define DBKuanShi_key_KindName               _T("cTreeName")      //����
#define DBKuanShi_key_StyleNo                _T("cKuanhao")       //���
#define DBKuanShi_key_StyleName              _T("cKuanming")      //����
#define DBKuanShi_key_YarnCate               _T("cYarnCate")      //ɴ�����
#define DBKuanShi_key_StyleIntro             _T("cKSMemo")        //��ʽ˵��
#define DBKuanShi_key_CreateTime             _T("dtCreatTime")    //��������ʱ��
#define DBKuanShi_key_KsYears                _T("KsYears")        //���
#define DBKuanShi_key_nColorNum              _T("nColorNum")      //��ɫ��
#define DBKuanShi_key_nColorSuitNum          _T("nColorSuitNum")  //��ɫ����
#define DBKuanShi_key_nIncreaseNum           _T("nIncreaseNum")   //������������
#define DBKuanShi_key_cBasicSize             _T("cBasicSize")     //����
#define DBKuanShi_key_cPinMing  _T("cPinMing")  //Ʒ�� yangjr 2018/5/11
// �淿������ʽ������-----start liuhw 2019/05/08
#define DBKuanShi_key_dtExpireTime           _T("dtExpireTime")            //��������
#define DBKuanShi_key_cCreator               _T("cCreator")                //������
#define DBKuanShi_key_cCreateType            _T("cCreateType")             //��������
#define DBKuanShi_key_cTheme                 _T("cTheme")                  //����
#define DBKuanShi_key_cCusCode               _T("cCusCode")                //�ͻ�
#define DBKuanShi_key_cCusKuanHao            _T("cCusKuanHao")             //�ͻ����
#define DBKuanShi_key_cProcessStatus         _T("cProcessStatus")          //����״̬
#define DBKuanShi_key_cEdition               _T("cEdition")                //�汾
#define DBKuanShi_key_dtMakingOrdTime        _T("dtMakingOrdTime")         //��������
#define DBKuanShi_key_cMainMaterial          _T("cMainMaterial")           //��ԭ��
#define DBKuanShi_key_cVersionNum            _T("cVersionNum")             //�浥��
#define DBKuanShi_key_cSinglePerson          _T("cSinglePerson")           //�Ƶ���
#define DBKuanShi_key_iFollow                _T("iFollow")                 //��ע
#define DBKuanShi_key_iShell                 _T("iUpOrDownShell")          //���¼�
#define DBKuanShi_key_cMainPic               _T("cMainPic")                //��ʽ����ͼ  	by WangZY 2019/05/16
#define DBKuanShi_key_bIsDeleted             _T("bIsDeleted")              //��ʽ�Ƿ�ɾ�� yangjr 2019/05/20
#define DBKuanShi_key_cState                 _T("cState")                  //״̬�ֶ�  wangzl 2019-5-30
#define DBKuanShi_key_cFangAnName            _T("cFangAnName")             //��������  wangzl 2019-6-3
#define DBKuanShi_key_cPriority              _T("cPriority")                //���ȼ�
#define DBKuanShi_key_cNeedleType            _T("cNeedleType")            //����
#define DBKuanShi_key_cModelMainPic          _T("cModelMainPic")           //չʾͼ����ͼ  	by Wangzl 2019/06/18
#define DBKuanShi_key_nSortIndex             _T("nSortIndex")              //���������      Wangzl 2019/06/18
#define DBKuanShi_key_iGXSortID              _T("iGXSortID")               //�����˳��      Wangzl 2019/06/18
#define DBKuanShi_key_cBrand                 _T("cBrand")                  //Ʒ��            wangzl 2019/07/02
#define DBKuanShi_key_cCustomField1          _T("cCustomField1")           //�Զ����ֶ�1     wangzl 2019/07/02
#define DBKuanShi_key_cCustomField2          _T("cCustomField2")           //�Զ����ֶ�2     wangzl 2019/07/02
#define DBKuanShi_key_cCustomField3          _T("cCustomField3")           //�Զ����ֶ�3     wangzl 2019/07/02
#define DBKuanShi_key_cCustomField4          _T("cCustomField4")           //�Զ����ֶ�4     wangzl 2019/07/02
#define DBKuanShi_key_cCustomField5          _T("cCustomField5")           //�Զ����ֶ�5     wangzl 2019/07/02
#define DBKuanShi_key_cCustomField6          _T("cCustomField6")           //�Զ����ֶ�6     wangzl 2019/07/02
#define DBKuanShi_key_cCustomField7          _T("cCustomField7")           //�Զ����ֶ�7     wangzl 2019/07/02
#define DBKuanShi_key_cCustomField8          _T("cCustomField8")           //�Զ����ֶ�8     wangzl 2019/07/02
#define DBKuanShi_key_cCustomField9          _T("cCustomField9")           //�Զ����ֶ�9     wangzl 2019/07/02
#define DBKuanShi_key_cCustomField10         _T("cCustomField10")          //�Զ����ֶ�10    wangzl 2019/07/02
#define DBKuanShi_key_dTotalCost             _T("dTotalCost")              //�ܳɱ� lida 2019/07/12
#define DBKuanShi_key_dTotalOffer            _T("dTotalOffer")             //�ܱ��� lida 2019/07/12
#define DBKuanShi_key_cGxPersonCode          _T("cGxPersonCode")           //�����ִ����    Wangzl 2019/07/13
/*==============================�� dbo.TableNameSet ==============================*/
#define DBTableNameSet_Key_ID                _T("ID")
#define DBTableNameSet_Key_cTableName        _T("cTableName")
#define DBTableNameSet_Key_cTableID          _T("cTableID")

/*==============================�� dbo.PieceInfo ==============================*/
#define DBPieceInfo_Key_ID                   _T("ID")
#define DBPieceInfo_Key_cCode                _T("cCode")
#define DBPieceInfo_Key_nPieceType           _T("nPieceType")
#define DBPieceInfo_Key_cPieceName           _T("cPieceName")
#define DBPieceInfo_Key_cRemark              _T("cRemark")

//DB_TABLE_STYLE_GLOBAL_SET �����ʽȫ������
/*==============================�� dbo.TableStyleGlobalSet ==============================*/
#define DBTableStyleGlobalSet_key_ID                    _T("ID")
#define DBTableStyleGlobalSet_key_cXmlFileName          _T("cXmlFileName")
#define DBTableStyleGlobalSet_key_cXmlDesc              _T("cXmlDesc")
#define DBTableStyleGlobalSet_key_cInitSettingXmlFile   _T("cInitSettingXmlFile")
#define DBTableStyleGlobalSet_key_cRealTimeXmlFile      _T("cRealTimeXmlFile")
#define DBTableStyleGlobalSet_key_dUpdateTime           _T("dUpdateTime")

/*==============================�� dbo.PinZhongSetting ==============================*/
// add by yangjr 2018/04/17
#define DBPinZhongSetting_ID		      _T("ID")
#define DBPinZhongSetting_cCate	      _T("cCate")	//ɴ�����
#define DBPinZhongSetting_cChenfen		_T("cChenfen")	//ɴ�߳ɷ�
#define DBPinZhongSetting_fSalePrice		_T("fSalePrice")	//���۵���
#define DBPinZhongSetting_cZhiXingBiaoZun		_T("cZhiXingBiaoZun")	//ִ�б�׼
#define DBPinZhongSetting_fFahuoSunhao		_T("fFahuoSunhao")	//�������
#define DBPinZhongSetting_fShoufaMaxSunhao		_T("fShoufaMaxSunhao")	//�շ�������(kg)
#define DBPinZhongSetting_isKoukuan		_T("isKoukuan")	//���������Ŀۿ�
#define DBPinZhongSetting_fZMDSalePrice		_T("fZMDSalePrice")	//ר�������۵���
#define DBPinZhongSetting_fZhekou		_T("fZhekou")	//�ۿ�
#define DBPinZhongSetting_fKouKuanPrice		_T("fKouKuanPrice")	//�ۿ���
#define DBPinZhongSetting_fPWeight      _T("fPWeight")         //ȥƤ����
#define DBPinZhongSetting_cProductName _T("cProductName")      //��Ʒ����
#define DBPinZhongSetting_fBelLv       _T("fBelLv")            //����   add anjie by 2018/10/25
#define DBPinZhongSetting_cYarnCode    _T("cYarnCode")         //ɴ�ߴ��� add liuhw by 2018/11/11
#define DBPinZhongSetting_IsOuterYarn      _T("IsOuterYarn")  //����ɴ�� add by lida 2019/03/06
#define DBPinZhongSetting_cPrintYarn    _T("cPrintYarn")      //��ӡɴ�� add anjie by 2019/03/30
#define DBPinZhongSetting_cChengBenPrice    _T("cChengBenPrice")      //�ɱ�����
//DB_TABLE_ORDER_TYPE_PRICE_SET

/*==============================�� dbo.FangAn_Power anjie 2018-06-06==============================*/
#define  DBFangAn_Power_Key_ID          _T("ID")
#define  DBFangAn_Power_Key_FangAnName  _T("cFangAnName")      //������
#define  DBFangAn_Power_Key_FangAnPower _T("cFangAnPower")     //����Ȩ�ޱ���
#define  DBFangAn_Power_Key_Num _T("cNum")             //����������


/*==============================���ϱ� dbo.MaterielInfo WangZY 2018/08/01==============================*/
#define  DBMateriel_Key_ID                _T("ID")             //���ϱ��
#define  DBMateriel_Key_cName             _T("cName")             //��������
#define  DBMateriel_Key_cLevel1Type       _T("cLevel1Type")       //����һ�����
#define  DBMateriel_Key_cLevel2Type       _T("cLevel2Type")       //����������
#define  DBMateriel_Key_cLevel3Type       _T("cLevel3Type")       //�����������
#define  DBMateriel_Key_cLevel4Type       _T("cLevel4Type")       //�����ļ����
#define  DBMateriel_Key_cLevel5Type       _T("cLevel5Type")       //�����弶���
#define  DBMateriel_Key_cUnit             _T("cUnit")             //���൥λ
#define  DBMateriel_Key_cChengFen         _T("cChengFen")         //���ϲ���(�ɷ�)
#define  DBMateriel_Key_cMemo             _T("cMemo")             //����˵��
#define  DBMateriel_Key_cPic              _T("cPic")              //����ͼƬ
#define  DBMateriel_Key_cPrice              _T("nPrice")              //����ͼƬ
#define  DBMateriel_Key_cBrand              _T("cBrand")              //����ͼƬ
#define  DBMateriel_Key_cSupplier         _T("cSupplier")         //��Ӧ��
/*==============================�ļ��� dbo.F_FileInfo Wangzl 2018/08/20==============================*/
#define  DBFileInfo_Key_ID                _T("ID")                //ID
#define  DBFileInfo_Key_cRelativePath     _T("cRelativePath")     //�ļ���·��
#define  DBFileInfo_Key_cUploadUserID     _T("cUploadUserID")     //�ϴ��û�ID
#define  DBFileInfo_Key_cUploadTime       _T("cUploadTime")       //�ϴ�ʱ��
#define  DBFileInfo_Key_cFileMD5          _T("cFileMD5")          //MD5ֵ
#define  DBFileInfo_Key_cFileName         _T("cFileName")         //�ļ���
#define  DBFileInfo_Key_cFileExtension    _T("cFileExtension")    //�ļ���׺
#define  DBFileInfo_Key_nFileSize         _T("nFileSize")         //�ļ���С
#define  DBFileInfo_Key_cRemark           _T("cRemark")           //˵��/��ע

/*============================== ������Ϣ�� dbo.P_BindInfo anjie 2018/08/21==============================*/
#define DBP_BindInfo_Key_ID                        _T("ID")
#define DBP_BindInfo_Key_cSeriaNum                 _T("cSeriaNum")               //���
#define DBP_BindInfo_Key_cName                     _T("cName")                   //����
#define DBP_BandInfo_Key_cBindStartTime            _T("cBandStartTime")          //���ο�ʼʱ��
#define DBP_BindInfo_Key_cDesignEndTime            _T("cDesignEndTime")          //������ʱ��
#define DBP_BindInfo_Key_cPatternEndTime           _T("cPatternEndTime")         //ֽ�����ʱ��
#define DBP_BindInfo_Key_cReviewEndTime            _T("cReviewEndTime")          //��������ʱ��
#define DBP_BindInfo_Key_cBandEndTime              _T("cBandEndTime")            //���ν���ʱ��
#define DBP_BindInfo_Key_cDeliveryStartTime        _T("cDeliveryStartTime")      //������ʼʱ��
#define DBP_BindInfo_Key_cDeliveryEndTime          _T("cDeliveryEndTime")        //���ڽ���ʱ��
#define DBP_BindInfo_Key_cShelvesTime              _T("cShelvesTime")            //�ϻ���
#define DBP_BindInfo_Key_cStylish                  _T("cStylish")                //���
#define DBP_BindInfo_Key_cColor                    _T("cColor")                  //ɫϵ
#define DBP_BindInfo_Key_cCreateUserID             _T("cCreateUserID")           //������
#define DBP_BindInfo_Key_cCreateUserTime           _T("cCreateUserTime")         //����ʱ��
#define DBP_BindInfo_Key_bCheckState               _T("bCheckState")             //��˱�ʶ
#define DBP_BindInfo_Key_cCheckUserID              _T("cCheckUserID")            //�����
#define DBP_BindInfo_Key_cCheckTime                _T("cCheckTime")              //���ʱ��
#define DBP_BindInfo_Key_cRemark                   _T("cRemark")                 //��ע
#define DBP_BindInfo_Key_nAssociatedProgrammingID _T("nAssociatedProgrammingID")// ������Ʒ�滮��ID

/*==============================��ɫ��Ϣ�� dbo.P_ColorInfo anjie 2018/08/21==============================*/
#define DBP_ColorInfo_Key_ID                       _T("ID")                 //ID
#define DBP_ColorInfo_Key_nType                    _T("nType")              //����    �������󻮻��ǲ��ε���Ϣ
#define DBP_ColorInfo_Key_nAssociatedID            _T("nAssociatedID")      //����ID
#define DBP_ColorInfo_Key_nColorType               _T("nColorType")         //��ɫ���� ��������ɫ������ɫ  ������ӵ�ж��
#define DBP_ColorInfo_Key_nAssociatedColorID       _T("nAssociatedColorID") //��������ɫID

/*==============================������Ϣ dbo.P_MatetialInfo anjie 2018/08/21==============================*/
#define DBP_MatetialInfo_Key_ID                       _T("ID")                      //ID
#define DBP_MatetialInfo_Key_nType                    _T("nType")                   //����    �������󻮻��ǲ��ε���Ϣ
#define DBP_MatetialInfo_Key_nAssociatedID            _T("nAssociatedID")           //����ID
#define DBP_MatetialInfo_Key_nAssociatedMaterialID    _T("nAssociatedMaterialID")   //��������ID

/*==============================ͼƬ��Ϣ dbo.P_PictureInfo anjie 2018/08/21==============================*/
#define DBP_PictureInfo_Key_ID                        _T("ID")                      //ID
#define DBP_PictureInfo_Key_nType                     _T("nType")                   //����
#define DBP_PictureInfo_Key_nAssociatedID             _T("nAssociatedID")           //����ID
#define DBP_PictureInfo_Key_nPicType                  _T("nPicType")                // ͼƬ����    ������ ��¼���°棨1��  ��ʽ�ο�ͼ��n�� ���δ��䣨n��  Ԫ�ط���գ�n��
#define DBP_PictureInfo_Key_nAssociatedFileID         _T("nAssociatedFileID")       //�����ļ�ID
#define DBP_PictureInfo_Key_cRemark                   _T("cRemark")                 //˵��

/*==============================�����󻮱� dbo.P_Planning anjie 2018/08/21==============================*/
#define DBP_Planning_Key_ID                           _T("ID")                      //ID
#define DBP_Planning_Key_nYears                       _T("nYears")                  //���
#define DBP_Planning_Key_cSeason                      _T("cSeason")                 //����
#define DBP_Planning_Key_cSubjectName                 _T("cSubjectName")            //������
#define DBP_Planning_Key_cBrand                       _T("cBrand")                  //Ʒ��
#define DBP_Planning_Key_cRemark                      _T("cRemark")                 //���ⱸע
#define DBP_Planning_Key_bCheckState                  _T("bCheckState")             //��˱�ʶ
#define DBP_Planning_Key_cCreateUserID                _T("cCreateUserID")           //������
#define DBP_Planning_Key_cCreateTime                  _T("cCreateTime")             //����ʱ��
#define DBP_Planning_Key_cLastActTime                 _T("cLastActTime")            //������ʱ��
#define DBP_Planning_Key_cCheckUserID                 _T("cCheckUserID")            //�����
#define DBP_Planning_Key_cCheckTime                   _T("cCheckTime")              //���ʱ��

/*==============================��Ʒ�ṹ�滮 dbo.P_ProductStructurePlanning anjie 2018/08/21==============================*/
#define DBP_ProductStructurePlanning_Key_ID                                   _T("ID")                           //
#define DBP_ProductStructurePlanning_Key_cClassification                      _T("cClassification")              //����    
#define DBP_ProductStructurePlanning_Key_cCategory                            _T("cCategory")                    //Ʒ��    
#define DBP_ProductStructurePlanning_Key_nPieceNum                            _T("nPieceNum")                    //����    
#define DBP_ProductStructurePlanning_Key_cColor                               _T("cColor")                       //ɫ��    
#define DBP_ProductStructurePlanning_Key_cSize                                _T("cSize")                        //����    
#define DBP_ProductStructurePlanning_Key_cFabric                              _T("cFabric")                      //����    
#define DBP_ProductStructurePlanning_Key_cFashion                             _T("cFashion")                     //���ͷ��
#define DBP_ProductStructurePlanning_Key_cContour                             _T("cContour")                     //����    
#define DBP_ProductStructurePlanning_Key_fPrice_Ceiling                       _T("fPrice_Ceiling")               //�۸�����
#define DBP_ProductStructurePlanning_Key_fPrice_Floor                         _T("fPrice_Floor")                 //�۸�����
#define DBP_ProductStructurePlanning_Key_fPrice_Tag                           _T("fPrice_Tag")                   //���Ƽ�  
#define DBP_ProductStructurePlanning_Key_cRemark                              _T("cRemark")                      //��ע    
#define DBP_ProductStructurePlanning_Key_cBand_Name                           _T("cBand_Name")                   //����
#define DBP_ProductStructurePlanning_Key_cBand_BandStartTime                  _T("cBand_BandStartTime")          //���ο�ʼʱ��   
#define DBP_ProductStructurePlanning_Key_cBand_DesignEndTime                  _T("cBand_DesignEndTime")          //������ʱ��   
#define DBP_ProductStructurePlanning_Key_cBand_PatternEndTime                 _T("cBand_PatternEndTime")         //ֽ�����ʱ��   
#define DBP_ProductStructurePlanning_Key_cBand_ReviewEndTime                  _T("cBand_ReviewEndTime")          //��������ʱ��
#define DBP_ProductStructurePlanning_Key_cBand_BandEndTime                    _T("cBand_BandEndTime")            //���ν���ʱ��
#define DBP_ProductStructurePlanning_Key_cBand_DeliveryStartTime              _T("cBand_DeliveryStartTime")      //������ʼʱ��
#define DBP_ProductStructurePlanning_Key_cBand_DeliveryEndTime                _T("cBand_DeliveryEndTime")        //���ڽ���ʱ��
#define DBP_ProductStructurePlanning_Key_cBand_ShelvesTime                    _T("cBand_ShelvesTime")            //�ϻ���
#define DBP_ProductStructurePlanning_Key_cBand_Stylish                        _T("cBand_Stylish")                //���
#define DBP_ProductStructurePlanning_Key_cBand_Color                          _T("cBand_Color")                  //ɫϵ
#define DBP_ProductStructurePlanning_Key_cCreateUserID                        _T("cCreateUserID")                //������
#define DBP_ProductStructurePlanning_Key_cCreateTime                          _T("cCreateTime")                  //����ʱ��
#define DBP_ProductStructurePlanning_Key_nCreateFlag                          _T("nCreateFlag")                  //������Դ  ���ڼ�¼��ֱ�Ӵ����Ĳ�Ʒ  ����ͨ�����δ����Ĳ�Ʒ
#define DBP_ProductStructurePlanning_Key_cProgramming_Brand                   _T("cProgramming_Brand")           //Ʒ��
#define DBP_ProductStructurePlanning_Key_cProgramming_Years                   _T("cProgramming_Years")           //���
#define DBP_ProductStructurePlanning_Key_cProgramming_Season                  _T("cProgramming_Season")          //����
#define DBP_ProductStructurePlanning_Key_cProgramming_TradeFairTime           _T("cProgramming_TradeFairTime")   //������ʱ��
#define DBP_ProductStructurePlanning_Key_cProgramming_Area                    _T("cProgramming_Area")            //����
#define DBP_ProductStructurePlanning_Key_cPlanning_SubjectName                _T("cPlanning_SubjectName")        //������
#define DBP_ProductStructurePlanning_Key_bSubmitState                         _T("bSubmitState")                 //�ύ״̬
#define DBP_ProductStructurePlanning_Key_cSubmitUserID                        _T("cSubmitUserID")                //�ύ��
#define DBP_ProductStructurePlanning_Key_cSubmitTime                          _T("cSubmitTime")                  //�ύʱ��
#define DBP_ProductStructurePlanning_Key_cCheckUserID                         _T("cCheckUserID")                 //�����
#define DBP_ProductStructurePlanning_Key_cCheckTime                           _T("cCheckTime")                   //���ʱ��
#define DBP_ProductStructurePlanning_Key_bCheckState                          _T("bCheckState")                  //���״̬
#define DBP_ProductStructurePlanning_Key_nCurProSort                          _T("nCurProSort")                  //��ǰ��������
#define DBP_ProductStructurePlanning_Key_bRevision                            _T("bRevision")                    //�İ��ʶ
#define DBP_ProductStructurePlanning_Key_cRevisionReason                      _T("cRevisionReason")              //�İ�ԭ��

/*==============================��Ʒ�滮�� dbo.P_Programming anjie 2018/08/21==============================*/
#define DBP_Programming_Key_ID                             _T("ID")                       //ID
#define DBP_Programming_Key_cBrand                         _T("cBrand")                   //Ʒ��
#define DBP_Programming_Key_nYears                         _T("nYears")                   //���
#define DBP_Programming_Key_cSeason                        _T("cSeason")                  //����
#define DBP_Programming_Key_cTradeFairTime                 _T("cTradeFairTime")           //������ʱ��
#define DBP_Programming_Key_cArea                          _T("cArea")                    //����
#define DBP_Programming_Key_nAssociatedPlanningID          _T("nAssociatedPlanningID")    //������ID
#define DBP_Programming_Key_cCreateUserID                  _T("cCreateUserID")            //������ID   

/*==============================������Ϣ�� dbo.P_TextBoard anjie 2018/08/21==============================*/
#define DBP_TextBoard_Key_ID                       _T("ID") 
#define DBP_TextBoard_Key_nType                    _T("nType")                            //����
#define DBP_TextBoard_Key_nAssociatedID            _T("nAssociatedID")                    //����ID
#define DBP_TextBoard_Key_cTextInfo                _T("cTextInfo")                        //���ְ�

/*==============================��Ʒ�汾��Ϣ�� dbo.P_ProductVersions wangzl 2018/08/22==============================*/
#define DBP_ProductVersions_Key_ID                 _T("ID")
#define DBP_ProductVersions_Key_nProductID         _T("nProductID")                       //��Ʒ
#define DBP_ProductVersions_Key_cVersion           _T("cVersion")                         //�汾
#define DBP_ProductVersions_Key_nVersionNo         _T("nVersionNo")                       //�汾��
#define DBP_ProductVersions_Key_cCode              _T("cCode")                            //������
#define DBP_ProductVersions_Key_cAlias             _T("cAlias")                           //����

/*==============================�����������̱� dbo.P_ProcessRecords wangzl 2018/08/22==============================*/
#define DBP_ProcessRecords_Key_ID                     _T("ID")                               //
#define DBP_ProcessRecords_Key_nAssociatedProductID   _T("nAssociatedProductID")             //�����Ĳ�ƷID
#define DBP_ProcessRecords_Key_cReceiveUserID         _T("cReceiveUserID")                   //������
#define DBP_ProcessRecords_Key_cSponsorID             _T("cSponsorID")                       //��������
#define DBP_ProcessRecords_Key_nProcessType           _T("nProcessType")                     //��Ӧ�Ĺ���
#define DBP_ProcessRecords_Key_cInitiateTime          _T("cInitiateTime")                    //������ʱ��
#define DBP_ProcessRecords_Key_cRealStartTime         _T("cRealStartTime")                   //����ʵ�ʿ�ʼʱ��
#define DBP_ProcessRecords_Key_cFinishTime            _T("cFinishTime")                      //�������ʱ��
#define DBP_ProcessRecords_Key_nState                 _T("nState")                           //״̬
#define DBP_ProcessRecords_Key_nCheckState            _T("nCheckState")                      //���

/*==============================��ɫά���� dbo.ColorMaintain liuhw 2018/08/20==============================*/
#define  DBColorMaintain_Key_ID                _T("ID")             //��ɫID
#define  DBColorMaintain_Key_cClrName             _T("cClrName")          //��ɫ����
#define  DBColorMaintain_Key_cClrCode              _T("cClrCode")           //��ɫ���
#define  DBColorMaintain_Key_cClrRGB              _T("cClrRGB")           //��ɫRGB
#define  DBColorMaintain_Key_cMemo             _T("cMemo")          //����˵��

/*==============================��Ʒ�����ű� dbo.P_ProductTaskAssign wangzl 2018/08/25==============================*/
#define  DBP_ProductTaskAssign_Key_ID                       _T("ID")                   //
#define  DBP_ProductTaskAssign_Key_nAssociatedProductID     _T("nAssociatedProductID") //������ƷID
#define  DBP_ProductTaskAssign_Key_nPersonType              _T("nPersonType")          //��Ա������
#define  DBP_ProductTaskAssign_Key_cAssignUserID            _T("cAssignUserID")        //��ָ���˵�ID
#define  DBP_ProductTaskAssign_Key_cAllotUserID             _T("cAllotUserID")         //�����˵�ID
#define  DBP_ProductTaskAssign_Key_cAllotTime               _T("cAllotTime")           //����ʱ��

/*==============================��������� dbo.P_ProductProcess wangzl 2018/08/27==============================*/
#define  DBP_ProductProcess_Key_ID                          _T("ID")                   //
#define  DBP_ProductProcess_Key_cProcessName                _T("cProcessName")         //������
#define  DBP_ProductProcess_Key_nSortID                     _T("nSortID")              //����ID
#define  DBP_ProductProcess_Key_nProcessType                _T("nProcessType")         //�ü�¼����Ӧ�Ĺ�������

/*==============================�İ��¼�� dbo.P_ProductRevisionRecords wangzl 2018/08/31==============================*/
#define  DBP_ProductRevisionRecords_Key_ID                       _T("ID")                     //
#define  DBP_ProductRevisionRecords_Key_nAssociatedProductID     _T("nAssociatedProductID")   //������ƷID
#define  DBP_ProductRevisionRecords_Key_cVersion                 _T("cVersion")               //��汾��
#define  DBP_ProductRevisionRecords_Key_nVersionNo               _T("nVersionNo")             //�汾��
#define  DBP_ProductRevisionRecords_Key_cCode                    _T("cCode")                  //��������
#define  DBP_ProductRevisionRecords_Key_cAlias                   _T("cAlias")                 //�汾����
#define  DBP_ProductRevisionRecords_Key_cSponsor                 _T("cSponsor")               //������
#define  DBP_ProductRevisionRecords_Key_cRecordTime              _T("cRecordTime")            //����ʱ��
#define  DBP_ProductRevisionRecords_Key_cRevisionType            _T("cRevisionType")          //�İ�����
#define  DBP_ProductRevisionRecords_Key_cRevisionReason          _T("cRevisionReason")        //�İ�ԭ��
#define  DBP_ProductRevisionRecords_Key_cLastRecordProcess       _T("cLastRecordProcess")     //����������
#define  DBP_ProductRevisionRecords_Key_nCheckState              _T("nCheckState")            //���״̬
#define  DBP_ProductRevisionRecords_Key_nCheckResult             _T("nCheckResult")           //��˽��
#define  DBP_ProductRevisionRecords_Key_cCheckUserID             _T("cCheckUserID")           //�����
#define  DBP_ProductRevisionRecords_Key_cCheckTime               _T("cCheckTime")             //���ʱ��
#define  DBP_ProductRevisionRecords_Key_cCheckOpinion            _T("cCheckOpinion")          //������

/*===================�û���¼��Ϣ�� dbo.ClientVarifyIno WangZY 2018/09/04==============================*/
#define DB_ClientVarifyIno_Key_ID               _T("ID")             //ID
#define DB_ClientVarifyIno_Key_UserId           _T("UserId")         //�û�ID
#define DB_ClientVarifyIno_Key_VarifyTime       _T("VarifyTime")     //ʱ��
#define DB_ClientVarifyIno_Key_MacInfo          _T("MacInfo")        //������Ϣ


/*==============================�ӵ������¼�� dbo.ProcessRecords  wangzl 2018-10-08==============================*/
#define DBProcessRecords_Key_ID                _T("ID")
#define DBProcessRecords_Key_cCode             _T("cCode")
#define DBProcessRecords_Key_cGXName           _T("cGXName")
#define DBProcessRecords_Key_cPersonCode       _T("cPersonCode")
#define DBProcessRecords_Key_cMemo             _T("cMemo")
#define DBProcessRecords_Key_iState            _T("iState")

#define DBProcessRecords_Key_iPieceWeight       _T("iPieceWeight")//Ƭ��
#define DBProcessRecords_Key_iDuration          _T("iDuration")//ʱ�� Сʱ��1λС����
#define DBProcessRecords_Key_iGongjia           _T("iGongjia")//����
#define DBProcessRecords_Key_dRecordTime        _T("dRecordTime")//��¼��ʱ��
#define DBProcessRecords_Key_cToPerson          _T("cToPerson")//һЩ��������Ӧ����Ա

/*==============================��׼����� dbo.StandardSize ==============================*/
#define DBStandardSize_key_ID			                                      _T("ID")		                            // ����ID
#define DBStandardSize_key_cName			                                   _T("cName")		                         // ����
#define DBStandardSize_key_cSavetime			                             _T("cSaveTime")		                      // ����ʱ��
#define DBStandardSize_key_cMark			                                   _T("cMark")		                         // ˵��

/*==============================��׼����� dbo.StandardSizeModify ==============================*/
#define DBStandardSizeModify_key_ID			                                _T("ID")		                               // ����ID
#define DBStandardSizeModify_key_nSizeID			                          _T("nID")		                               // ����ID
#define DBStandardSizeModify_key_cSize			                             _T("cSize")		                            // �ߴ�
#define DBStandardSizeModify_key_cPosition			                       _T("cPosition")		                         // ��λ
#define DBStandardSizeModify_key_nNumber			                          _T("nNumber")		                         // ��ֵ
#define DBStandardSizeModify_key_cMemo			                             _T("cMemo")		                         // ˵��
/*==============================��׼����� dbo.StandardSize_Pinming ==============================*/
#define DBStandardSizePinming_key_ID			                                _T("ID")		                            // ����ID
#define DBStandardSizePinming_key_cStandardSize		                          _T("cStandardSize")		                // ������
#define DBStandardSizePinming_key_cPinMing			                          _T("cPinMing")		                      // Ʒ��

/*==============================Сͼ����� dbo.SmallPic ==============================*/
#define DBSmallPic_key_ID			          _T("ID")		            //����ID
#define DBSmallPic_key_Name	    	       _T("cName")		         //����
#define DBSmallPic_key_iWidth	             _T("iWidth")              //���
#define DBSmallPic_key_iHeight	          _T("iHeight")             //�߶�
#define DBSmallPic_key_Type		          _T("cModelType")			   //Сͼ�Զ�������
#define DBSmallPic_key_cSavedUserID        _T("cSavedUserID")        //������
#define DBSmallPic_key_cSaveTime           _T("cSaveTime")           //����ʱ��
#define DBSmallPic_key_cRemark             _T("cRemark")             //˵��
#define DBSmallPic_key_cSmallDetailPic     _T("cSmallDetailPic")     //Ԥ��ͼƬ
#define DBSmallPic_key_bLoop               _T("bLoop")               //��Сѭ��
#define DBSmallPic_key_bKeepLine           _T("bKeepLine")           //���渨����
#define DBSmallPic_key_cContact            _T("cContact")            //��ϵ��ʽ

/*==============================���������� dbo.DesignDataLib ==============================*/
#define DBDesignDataLib_key_ID			                    _T("ID")		             // ����ID
#define DBDesignDataLib_key_Name	    	                    _T("cName")		          // ����
#define DBDesignDataLib_key_cSavedUserID                   _T("cSavedUserID")        // ������
#define DBDesignDataLib_key_cSaveTime                      _T("cSaveTime")           // ����ʱ��
#define DBDesignDataLib_key_cData                          _T("cData")               // �������ݣ������ļ�����
#define DBDesignDataLib_key_cLibType                       _T("cLibType")            // ������ ��Ƭ ������ ��״
#define DBDesignDataLib_key_cPosition                      _T("cPosition")           // ��λ
#define DBDesignDataLib_key_bSymmetricByHor                _T("bSymmetricByHor")     // ˮƽ
#define DBDesignDataLib_key_bSymmetricByPer                _T("bSymmetricByPer")     // ��ֱ
#define DBDesignDataLib_key_bUseExpre                      _T("bUseExpre")           // Ӧ�ù�ʽ
#define DBDesignDataLib_key_bUseLine                       _T("bUseLine")            // Ӧ�ø�����
#define DBDesignDataLib_key_bMark                          _T("bMark")               // �Ǻ�����
#define DBDesignDataLib_key_bMatchPiece                    _T("bMatchPiece")         // ������Ƭ
#define DBDesignDataLib_key_nLength                        _T("nLength")             // ��
#define DBDesignDataLib_key_nBust                          _T("nBust")               // ��Χ 
#define DBDesignDataLib_key_nShoulderWidth                 _T("nShoulderWidth")      // ���
#define DBDesignDataLib_key_nCollarWidth                   _T("nCollarWidth")        // ���
#define DBDesignDataLib_key_nCollarHeight                  _T("nCollarHeight")       // ���
#define DBDesignDataLib_key_nFront                         _T("nFront")              // ǰ�ؿ�
#define DBDesignDataLib_key_nBehind                        _T("nBehind")             // �󱳿�
#define DBDesignDataLib_key_nMidWidth                      _T("nMidWidth")           // ������
#define DBDesignDataLib_key_nMidHeight                     _T("nMidHeight")          // ������
#define DBDesignDataLib_key_nBellowWidth                   _T("nBellowWidth")        // �°ڿ�
#define DBDesignDataLib_key_nBellowHeight                  _T("nBellowHeight")       // �°ڸ�
#define DBDesignDataLib_key_nShoulderSlanting              _T("nShoulderSlanting")   // ��б
#define DBDesignDataLib_key_nShoulder                      _T("nShoulder")           // �Ҽ�
#define DBDesignDataLib_key_nShoulderHeight                _T("nShoulderHeight")     // �Ҽ������
#define DBDesignDataLib_key_nShoudlerHor                   _T("nShoudlerHor")        // �Ҽ�ƽ��
#define DBDesignDataLib_key_nFrontDeep                     _T("nFrontDeep")          // ǰ����
#define DBDesignDataLib_key_nBehindDeep                    _T("nBehindDeep")         // ������
#define DBDesignDataLib_key_nSleeveLength                  _T("nSleeveLength")       // �䳤
#define DBDesignDataLib_key_nSleeveWidth                   _T("nSleeveWidth")        // ���
#define DBDesignDataLib_key_cTomid                         _T("cTomid")              // ������
#define DBDesignDataLib_key_cToTop                         _T("cToTop")              // ���ඥ
#define DBDesignDataLib_key_cWidth1                        _T("cWidth1")             // ����1
#define DBDesignDataLib_key_cWidth2                        _T("cWidth2")             // ����2
#define DBDesignDataLib_key_cHeight1                       _T("cHeight1")            // ����1
#define DBDesignDataLib_key_cHeight2                       _T("cHeight2")            // ����2
#define DBDesignDataLib_key_cTotalHeight                   _T("cTotalHeight")        // �ܴ���
#define DBDesignDataLib_key_cTotalWidth                    _T("cTotalWidth")         // �ܴ���

/*==============================�ؼ�Ȩ�ޱ� dbo.ControlsPermission wangzl 2019-2-18==============================*/
#define DBControlsPermission_Key_ID             _T("ID")
#define DBControlsPermission_Key_nDlgID         _T("nDlgID")//�Ի���ID
#define DBControlsPermission_Key_nDlgFlag       _T("nDlgFlag")//�Ի����Զ����־
#define DBControlsPermission_Key_nControlID     _T("nControlID")//�ؼ�ID
#define DBControlsPermission_Key_nControlType   _T("nControlType")//�ؼ�����
#define DBControlsPermission_Key_cDescription   _T("cDescription")//˵��

/*==============================�û���ʽȨ�ޱ� dbo.User_StylePermission wangzl 2019-05-06==============================*/
#define DBUserStylePermission_Key_ID               _T("ID")
#define DBUserStylePermission_Key_UID              _T("UID")         //�û�ID
#define DBUserStylePermission_Key_SID              _T("SID")         //��ʽID
#define DBUserStylePermission_Key_nPermission      _T("nPermission") //Ȩ��
#define DBUserStylePermission_Key_cPermissionTime  _T("cPermissionTime") //Ȩ����Ч��

/*==============================��ʽԭ���ϱ�    ����δ֪����dbo.StyleMaterielInfo WangZY 2019/05/06==============================*/
#define DBStyleMaterial_Key_ID                _T("ID")                    //ID
#define DBStyleMaterial_Key_cStyleNo          _T("cStyleNo")              //���
#define DBStyleMaterial_Key_cMaterialNo       _T("cMaterialNo")           //���ϱ��
#define DBStyleMaterial_Key_cName             _T("cName")                 //��������
#define DBStyleMaterial_Key_cLevel1Type       _T("cLevel1Type")           //�����   
#define DBStyleMaterial_Key_cLevel2Type       _T("cLevel2Type")           //�����
#define DBStyleMaterial_Key_cLevel3Type       _T("cLevel3Type")           //С���
#define DBStyleMaterial_Key_cUnit             _T("cUnit")                 //���ϵ�λ
#define DBStyleMaterial_Key_fCount            _T("fCount")                //��������
#define DBStyleMaterial_Key_cMemo             _T("cMemo")                 //����˵��
#define DBStyleMaterial_Key_cSupplier         _T("cSupplier")             //��Ӧ��
#define DBStyleMaterial_Key_cPic              _T("cPic")                  //����ͼƬ
#define DBStyleMateriel_Key_fPrice            _T("fPrice")                //���ϵ���
#define DBStyleMateriel_Key_fTotalPrice       _T("fTotalPrice")           //�����ܼ�
#define DBStyleMaterial_Key_cBrand            _T("cBrand")                //����Ʒ��
#define DBStyleMaterial_Key_cChengFen         _T("cChengFen")             //���ϲ���(�ɷ�)


/*==============================��ʽ�ߴ���Ϣ��  dbo.Style_Size liuhw 2019/05/06==============================*/
#define DBStyleSize_Key_ID       _T("ID")
#define DBStyleSize_Key_cKuanhao _T("cKuanhao")
#define DBStyleSize_Key_cChima   _T("cChima")
#define DBStyleSize_Key_iPartID  _T("iPartID") //��λID
#define DBStyleSize_Key_fSize    _T("fSize")   //�ߴ�����
#define DBStyelSize_Key_cFangAn  _T("cFangAn")//�ߴ緽����
/*==============================��ʽ������Ϣ��  dbo.Style_Chima liuhw 2019/05/06==============================*/
#define DBStyleChiMa_Key_ID       _T("ID")
#define DBStyleChiMa_Key_cKuanhao _T("cKuanhao")
#define DBStyleChiMa_Key_cChima   _T("cChima")
#define DBStyleChiMa_Key_iBase    _T("iBase")   //�Ƿ�Ϊ����

/*==============================��ʽ��������¼��  dbo.Style_CheckRecords wantzl 2019/05/19==============================*/
#define DBStyle_CheckRecords_ID           _T("ID")
#define DBStyle_CheckRecords_SID          _T("SID")
#define DBStyle_CheckRecords_cPerson      _T("cPerson")
#define DBStyle_CheckRecords_nState       _T("nState")
#define DBStyle_CheckRecords_cTime        _T("cTime")

/*==============================��ʽ�ɱ���Ϣ��  dbo.Style_Cost anjie 2019/05/24==============================*/
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
/*==============================��ʽ�ļ���Ϣ��  dbo.Style_FileInfo wangzl 2019/05/28==============================*/
#define DBStyle_FileInfo_ID                 _T("ID")
#define DBStyle_FileInfo_nFileID            _T("nFileID")
#define DBStyle_FileInfo_cStyleNo           _T("cStyleNo")
#define DBStyle_FileInfo_nFileType          _T("nFileType")
#define DBStyle_FileInfo_nSort             _T("nSort")

/*==============================�����ļ���Ϣ��  dbo.Style_FileInfo wangzl 2019/05/28==============================*/
#define DBSampleClothing_FileInfo_ID                 _T("ID")
#define DBSampleClothing_FileInfo_nFileID            _T("nFileID")
#define DBSampleClothing_FileInfo_cBarCode           _T("cBarCode")
#define DBSampleClothing_FileInfo_nFileType          _T("nFileType")
#define DBSampleClothing_FileInfo_nSort             _T("nSort")

/*==============================��ʽ�汾�����¼��  dbo.Style_VersionRecords wantzl 2019/06/05==============================*/
#define DBStyle_VersionRecords_ID           _T("ID")
#define DBStyle_VersionRecords_SID          _T("SID")
#define DBStyle_VersionRecords_cPerson      _T("cPerson")
#define DBStyle_VersionRecords_nState       _T("nState")
#define DBStyle_VersionRecords_cTime        _T("cTime")
#define DBStyle_VersionRecords_cRemark      _T("cRemark")

/*==============================��ʽ����  dbo.Style_Description 2019/06/11==============================*/
#define DBStyle_Description_Key_ID            _T("ID")
#define DBStyle_Description_Key_cKuanhao      _T("cKuanhao")
#define DBStyle_Description_Key_cDescription  _T("cDescription")

/*==============================��ǩ����  dbo.Config_TagName wangzl 2019/06/12==============================*/
#define DBConfig_TagName_Key_cTagName      _T("cTagName")
#define DBConfig_TagName_Key_cDisplayName  _T("cDisplayName")
#define DBConfig_TagName_Key_nHide  _T("nHide") //�Ƿ����� yangjr 2019/07/09
/*==============================��ʽ�ܶ���Ϣ��  dbo.Style_DesDenisity wangzl 2019/06/19==============================*/
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

/*==============================��ʽ��������Ϣ��  dbo.Style_DesFaceCode wangzl 2019/06/19==============================*/
#define DBStyle_DesFaceCode_Key_ID                 _T("ID")
#define DBStyle_DesFaceCode_Key_cName              _T("cName")
#define DBStyle_DesFaceCode_Key_fOldLen            _T("fOldLen")
#define DBStyle_DesFaceCode_Key_cType              _T("cType")
#define DBStyle_DesFaceCode_Key_fLen               _T("fLen")
#define DBStyle_DesFaceCode_Key_cUnit              _T("cUnit")
#define DBStyle_DesFaceCode_Key_IDDensity          _T("IDDensity")


/*==============================���¹����  dbo.SampleClotingInfo   lida 2019/07/01==============================*/
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

/*==============================�����շ���¼��  dbo.SampleClothingRecords   lida 2019/07/01==============================*/
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
/*==============================��ʽ�����ֶ���Ϣ��  dbo.Style_Basic_FieldSet wangzl 2019/07/01==============================*/
#define DBStyle_Basic_FieldSet_Key_cColID          _T("cColID")
#define DBStyle_Basic_FieldSet_Key_cDisplayName    _T("cDisplayName")
#define DBStyle_Basic_FieldSet_Key_bShow           _T("bShow")
#define DBStyle_Basic_FieldSet_Key_nSortIndex      _T("nSortIndex")
#define DBStyle_Basic_FieldSet_Key_bOnPanel        _T("bOnPanel")

/*==============================��ʽ�ߴ������Ϣ�� dbo.[StyleSizeExtra] yangjr 2019/07/14==============================*/
#define DBStyleSizeExtra_key_ID           _T("ID")
#define DBStyleSizeExtra_key_cStyleNo     _T("cStyleNo")//���
#define DBStyleSizeExtra_key_iPartID     _T("iPartID")   //�ߴ粿λ
#define DBStyleSizeExtra_key_cMemo     _T("cMemo") //��λ˵��
#define DBStyleSizeExtra_key_fCeLiangBeforeSize    _T("fCeLiangBeforeSize") //����ǰ�ߴ�
#define DBStyleSizeExtra_key_fCeLiangCusSize     _T("fCeLiangCusSize") //�ͻ������ߴ�
#define DBStyleSizeExtra_key_fWaterBeforeSize     _T("fWaterBeforeSize")//ϴˮǰ�ߴ�
#define DBStyleSizeExtra_key_fWaterAfterSize     _T("fWaterAfterSize")//ϴˮ��ߴ�



/*==============================��������Ϣ�� dbo.[ProductOrderInfo] lida 2019/07/17==============================*/
#define  DBProductOrderInfo_Key_ID              _T("ID")
#define  DBProductOrderInfo_Key_MakeDate         _T("MakeDate")
#define  DBProductOrderInfo_Key_ProductOrder     _T("ProductOrder")
#define  DBProductOrderInfo_Key_MainClrNo        _T("MainClrNo")
#define  DBProductOrderInfo_Key_MainClrCate      _T("MainClrCate")
#define  DBProductOrderInfo_Key_MainClrName      _T("MainClrName")
#define  DBProductOrderInfo_Key_SizeNumInfo      _T("SizeNumInfo")
#define  DBProductOrderInfo_Key_StyleNo        _T("StyleNo")
#define  DBProductOrderInfo_Key_TotalNum        _T("TotalNum")

/*==============================���۵���Ϣ�� dbo.[SalesOrderInfo] lida 2019/07/18==============================*/
#define  DBSalesOrderInfo_Key_ID              _T("ID")
#define  DBSalesOrderInfo_Key_MakeDate         _T("MakeDate")
#define  DBSalesOrderInfo_Key_SalesOrder     _T("SalesOrder")
#define  DBSalesOrderInfo_Key_MainClrNo        _T("MainClrNo")
#define  DBSalesOrderInfo_Key_MainClrCate      _T("MainClrCate")
#define  DBSalesOrderInfo_Key_MainClrName      _T("MainClrName")
#define  DBSalesOrderInfo_Key_SizeNumInfo      _T("SizeNumInfo")
#define  DBSalesOrderInfo_Key_StyleNo        _T("StyleNo")
#define  DBSalesOrderInfo_Key_TotalNum        _T("TotalNum")