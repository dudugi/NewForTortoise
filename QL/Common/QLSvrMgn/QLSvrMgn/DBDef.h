#pragma once

//--------------------------------------------------------------------
#pragma region ���ݿ����
#define DB_TABLE_CLIENT_VARIFY_INFO          _T("ClientVarifyInfo")            //��¼��Ϣ��
#define DB_TABLE_MATERIEL_INFO               _T("MaterielInfo")                //������Ϣ��
#define DB_TABLE_COLORMAINTAIN_INFO          _T("ColorMaintain")               //��ɫά����  by liuhw 2018/08/20
#define DB_TABLE_OFF_FACTORY_REWORK_RECORDS	_T("RdOffFactoryRework")	       //���ⷵ����¼��		by WangZY 2018/04/03
#define DB_TABLE_PERSON                      _T("Userinfo")			             //��Ա��Ϣ���ڲ�Ա����
#define DB_TABLE_COMMONPROINFO               _T("CommonProIntro")              //������Ϣ����
#define DB_TABLE_CUSTOM                      _T("Customer")			             //�ͻ���Ϣ��
#define DB_TABLE_FILE                        _T("Table_File")                  //�ļ���
#define DB_TABLE_SIZE                        _T("Size_Order")                  //�����
#define DB_TABLE_STYLE                       _T("Kuanshi")			             //��ʽ��
#define DB_TABLE_YARN                        _T("Color")				             //ɴ�߱�
#define DB_TABLE_YARNINDEX                   _T("Table_YarnIndex_Order")       //ɴ��������
#define DB_TABLE_LOG                         _T("WorkLog")			             //��־��
#define DB_TABLE_YARNINDEX_STYLE             _T("Table_YarnIndex_Style")       //ɴ��������
#define DB_TABLE_SIZE_STYLE                  _T("Size_Order")		             //��ʽ�ߴ��
#define DB_TABLE_SIZEPART                    _T("SizePart")			             //��λ��
#define DB_TABLE_PROCESS                     _T("Gongxu")			             //�����
#define DB_TABLE_DENSITY                     _T("DesDensity")			          //�ܶȱ�
#define DB_TABLE_DESFACECODE                 _T("DesFaceCode")			          //�������
#define DB_TABLE_DES_DENSITY                 _T("SampleDesDensity")			    //�ܶȱ�
#define DB_TABLE_FACECODE                    _T("SampleDesFaceCode")			    //�������
#define DB_TABLE_CLOTHPIECE                  _T("ClothPiece")			          //��Ƭ��Ϣ��
#define DB_TABLE_PIECEWEIGHT                 _T("PieceWeight")			          //��Ƭ������
#define DB_TABLE_SIZEPART_ORDER               _T("SizePart_Order")			    //�ߴ粿λ��
#define DB_TABLE_SIZEPART_VALUE               _T("SizePart_Value")			    //�ߴ粿λ����ֵ��
#define DB_TABLE_PROCESSBIND                 _T("UserGongxu")		             //����󶨱�
#define DB_TABLE_DATADICTIONARY              _T("TreeClass")			          //�����ֵ��
#define DB_TABLE_PRODETAIL                   _T("ProDetail")			          //���������
#define DB_TABLE_CODERULE                    _T("CodeRule")			             //�������������
#define DB_TABLE_MENUS                       _T("Menus")				             //�����˵���
#define DB_TABLE_YARNRECORD                  _T("OtherRecord")		             //ɴ�߳�����¼��
#define DB_TABLE_YARNRECORDS                 _T("OtherRecords")		          //ɴ�߳�����
#define DB_TABLE_CONFIG                      _T("Config")			             //ȫ������
#define DB_TABLE_COLORPRICE                  _T("ColorPrice")		             //�۸����ñ� add by yangjr 2017-7-13
#define DB_TABLE_VARIOUSSTYLE                _T("VariousStyle")		          //һ��������Ӧ��Ϣ��
#define DB_TABLE_ACTMAP                      _T("ActMap")			             //
#define DB_TABLE_SMS                         _T("SMS")				             //���Ͷ��ż�¼�� add by yangjr 2017-9-18
#define DB_TABLE_PROSET_STYLE                _T("ProSet_Style")		          //��ʽ�������ñ� wangzl 2017-11-08
#define DB_TABLE_PROSET_ORDER                _T("ProSet_Order")                //�����������ñ� wangzl 2018-05-03
#define DB_TABLE_ORDER_SIZE_ATTRIBUTE        _T("Attribute_Size_Order")        //�����Ĺ������Ա� wangzl 2017-11-14
#define DB_TABLE_MAC                         _T("Mac_Mgn")			             //������ add by lida 2017/11/20
#define DB_TABLE_PLANT                       _T("Plant_Mgn")			          //������ add by lida 2017/11/20
#define DB_TABLE_MACFILE                     _T("MacFile_Mgn")		             //����ļ����� add by lida 2017/12/01
#define DB_TABLE_PANDIANRECORDS              _T("PanDianRecords")	             //�̵��¼��  by yangjr2018/1/9
#define DB_TABLE_SCHEDULE                    _T("Schedule")			             //��α� add by lida 2018/01/08
#define DB_TABLE_FANGANGONGXU                _T("FangAnGongxu")		          //���򷽰��� add by wuzhihua 2018/01/16
#define DB_TABLE_ORDERFILE                   _T("OrderFile")				       //���򷽰��� add by wuzhihua 2018/01/16
#define DB_TABLE_COMPANY_INFO                _T("dbo.CompanyInfo")	          //��˾��Ϣ�� add by zhangyx 2018/01/22
#define DB_TABLE_COLNAME_SET                 _T("ColNameSet")		             //�ֶ������ñ� add by wuzhihua 2018/02/03
//#define DB_TABLE_TABLENAME_SET             _T("TableNameSet")		          //�����������ñ� add by wuzhihua 2018/02/03
//#define DB_TABLE_STYLE_SET                 _T("TableStyleSet")		          //��ʽ���������� add by wuzhihua 2018/02/03
//#define DB_TABLE_MAOSHA                    _T("Maosha")		                //��˿ ëɴ�� yangjr 2018/2/28
#define DB_TABLE_PIECEINFO                   _T("PieceInfo")                   //��Ƭ��Ϣ�� ���ڴ洢xx��Ƭ����ҡ���ǵ��� �Լ�����ͳ�ƹ���
#define DB_TABLE_DEMAND_ORDER                _T("Demand_Order")                //������ע��Ϣ��
#define DB_TABLE_ORDER_INSTORAGE             _T("OrderInStorage")	             //�������� add by lida 2018/03/20
#define DB_TABLE_JIASHA_RECORDS              _T("JiaShaRecords")               //��ë��ϸ�� add by wuzhihua 2018/03/20
#define DB_TABLE_DEDUCTMONEY_RECORDS         _T("DebitRecords")                //�ۿ���ϸ�� add by wuzhihua 2018/03/22
#define DB_TABLE_CYRECORDS                   _T("CYRecords")                   //���³����� add by lida 2018/03/23
#define DB_TABLE_CYRECORD                    _T("CYRecord")                    //���³������ϸ�� add by lida 2018/03/23
#define DB_TABLE_FAHUORECORD                 _T("FahuoRecord")	                //������¼�ܱ� by yangjr2018/3/26
#define DB_TABLE_FAHUORECORDS                _T("FahuoRecords")	             //������¼��ϸ�� by yangjr2018/3/26
#define DB_TABLE_ClIENTTREEGROUP             _T("ClientTreeGroup")             //�ͻ����η���� add by wuzhihua 2018/3/28
#define DB_TABLE_INPLANT_REWORK_RECORDS      _T("InPlantReworkRecords")        //���ڷ��� add by wuzhihua 2018/4/4
#define DB_TABLE_STYLE_GLOBAL_SET            _T("TableStyleGlobalSet")         //�����ʽȫ������ add by wuzhihua 2018/4/13
#define DB_TABLE_WL_KUANSHI                  _T("WLKuanshi")                   //������ʽ add by lida 2018/04/18
#define DB_TABLE_WL_KUANSHI_DETAIL_INFO      _T("WLKuanshi_Detail_info")       //������ʽ���� add by lida 2018/06/12
#define DB_TABLE_PINZHONGSETTING             _T("PinZhongSetting")             //Ʒ��ά�� add by yangjr 2018/04/17
#define DB_TABLE_TUIHUOSTATE                 _T("TuihuoState")                 //�˻�״̬ add by yangjr 2018/04/21
#define DB_TABLE_ORDER_TYPE_PRICE_SET        _T("OrderTypePriceSet")           //�������ͼ۸�ά�� add by wuzhihua 2018/4/22
#define DB_TABLE_FINDKEY_STYLE               _T("FindKey_Style")               //��ʽ�Ĺؼ��ʱ�
#define DB_TABLE_KUANSHI_CLASS               _T("KuanshiClass")                //��ʽϵ�б�
#define DB_TABLE_FANGANMACTYPE               _T("FangAnMacType")               //���򷽰��󶨻������ͱ�		by WangZY 2018/05/15
#define DB_TABLE_FANGANPOWER                 _T("FangAnPower")                 // �Զ���Ȩ�޷�����    add by anjie 2018/06/04
#define DB_INVENTORY_CHECK_FLAG              _T("inventory_check_flag")        //����̵��ʶ    add by lida 2018/06/04
#define DB_INVENTORY_CHECK_PERIOD            _T("inventory_check_period")      //�̵�������ʶ    add by lida 2018/06/04
#define DB_INVENTORY_CHECK_RECORDS           _T("inventory_check_records")     //����̵��¼    add by lida 2018/06/04
//#define DB_TABLE_ORDER_ENTRY_PICNAME         _T("OrderEntry_PicName")      //����¼�붩����ʽͼƬ��   add by anjie 2018/06/06
#define DB_TABLE_ORDERTRACK                  _T("OrderTrack")                  //�������� add by yangjr 2018/06/07
#define DB_TABLE_STYLEMETARIAL               _T("StyleMetarial")               //������ʽ-ԭ����Ϣ add by lida 2018/06/20
#define DB_TABLE_STYLESUPMETARIAL            _T("StyleSupMetarial")            //������ʽ-������Ϣ add by huangym 2018/12/24
#define DB_TABLE_STYLECOLORPERCENT           _T("StyleColorPercent")           //������ʽ-��ɫ������Ϣ add by huangym 2018/12/28
#define DB_TABLE_STYLEGOODSINFO              _T("StyleGoodsInfo")              //������ʽ-��Ʒ��Ϣ add by lida 2018/06/20
#define DB_TABLE_FILEINFO                    _T("F_FileInfo")                  //�ļ���Ϣ wangzl 2018-08-20
#define DB_TABLE_BANDINFO                    _T("P_BandInfo")                  //����-������Ϣ wangzl 2018-08-20
#define DB_TABLE_COLORINFO                   _T("P_ColorInfo")                 //����-��ɫ��Ϣ wangzl 2018-08-20
#define DB_TABLE_MATERIALINFO                _T("P_MatetialInfo")              //����-������Ϣ wangzl 2018-08-20
#define DB_TABLE_PICTUREINFO                 _T("P_PictureInfo")               //����-ͼƬ��Ϣ wangzl 2018-08-20
#define DB_TABLE_PLANNING                    _T("P_Planning")                  //����-�󻮱� wangzl 2018-08-20
#define DB_TABLE_PRODUCTSP                   _T("P_ProductStructurePlanning")  //����-��Ʒ�ṹ�滮 wangzl 2018-08-20
#define DB_TABLE_PROGRAMMING                 _T("P_Programming")               //����-��Ʒ�滮�� wangzl 2018-08-20
#define DB_TABLE_TEXTBOARD                   _T("P_TextBoard")                 //����-���ְ� wangzl 2018-08-20
#define DB_TABLE_PRODUCTVERSION              _T("P_ProductVersions")           //���� ��Ʒ��Ϣ�� wangzl 2018-08-21
#define DB_TABLE_P_PROCESSRECORDS             _T("P_ProcessRecords")           //���� ���̼�¼�� wangzl 2018-08-21
#define DB_TABLE_PRODUCTTASKASSIGN           _T("P_ProductTaskAssign")         //���� ��Ʒ������ wangzl 2018-08-25
#define DB_TABLE_PRODUCTPROCESS              _T("P_ProductProcess")            //���� ���� wangzl 2018-08-27
#define DB_TABLE_PRODUCTREVISIONRECORDS      _T("P_ProductRevisionRecords")    //���� ��Ʒ�İ��¼ wangzl 2018-08-31
#define DB_TABLE_SALESPRODUCTINFO           _T("SalesProductInfo")             //��������������Ӧ�� yangjr 2018-09-06
#define DB_TABLE_SALESORDERDETAIL           _T("SalesOrderDetail")             //���۶�����ϸ�� yangjr 2018-09-06
#define DB_TABLE_CUSTOMERBRANCH              _T("CustomerBranch")              //�ͻ��ֵ��ʶ  wangzl 2018-09-18
#define DB_TABLE_RDRECORDS1ST                _T("RdRecords1st")
#define DB_TABLE_RDRECORDS2ND                _T("RdRecords2nd")
#define DB_TABLE_PROCESSRECORDS              _T("ProcessRecords")              //�ӵ������¼�� wangzl 2018-10-08
#define DB_TABLE_PROCESSRECORDS_MAIN         _T("ProcessRecords_Main")         //���������¼�� wangzl 2018-10-08
#define DB_TABLE_PROCESSRECORDSDETAILS       _T("ProcessRecordsDetails")       //�ӵ������¼���� wangzl 2018-10-08
#define DB_TABLE_OUTREWORKGXRECORDS	         _T("OutReworkGXRecords")	       //���ⷵ�������¼��		by Yangjr 2018/10/11
#define DB_TABLE_WEB_CONFIGURATION           _T("WebConfig")                   //��ҳ¼������  by huangym 2018-11-7
#define DB_TABLE_SMALLPIC		               _T("SmallPic")                    //Сͼ����  by huangym 2018-12-3
#define DB_TABLE_DESIGNDATALIB		         _T("DesignData_Lib")                  // ����������
#define DB_TABLE_DESIGNDATA		             _T("DesignData")                  // �ư����ñ�
#define DB_TABLE_STANDARDSIZE  		         _T("StandardSize")                // ��׼�����
#define DB_TABLE_STANDARDSIZEMODIFY  		   _T("StandardSizeModify")          // ��׼���������
#define DB_TABLE_STANDARDSIZE_PINMING		   _T("StandardSize_PinMing")        // ��׼����-Ʒ����
#define DB_TABLE_FOCUS_CUSTOMER              _T("Focus_Customer")              // ��ע�ͻ��� liuhw 2018/11/29
#define DB_TABLE_TABLE_MAX_SERIAL_COUNT      _T("Table_Max_Serial_Count")      //��ͬ��������ˮ�ű� wangzl 2018-12-20
#define DB_TABLE_BATCHSALESCODE              _T("Table_BatchSalesCode")        //������ӡ�����Ŵ洢�� yangjr 2018/12/20
#define DB_TABLE_TUIHUO_REGISTER             _T("TuihuoRegister")       //�˻��Ǽ� add by lida 2018/12/29
#define DB_TABLE_ORDERWARNINGCONDITION       _T("OrderWarningCondition") //����Ԥ���ؼ�״̬��
#define DB_TABLE_WEB_IMAGE_ORDER             _T("WebImageOrder") //���紫��  huangym 2019/1/15
#define DB_VIEW_CYRECORDS                    _T("V_CYRecords")
#define DB_VIEW_ORDER_INSTORAGE              _T("V_OrderInStorage")	//���������ͼ add by lida 2018/03/20
#define DB_VIEW_COLORPRICE                   _T("V_ColorPrice")		//ɴ�߼۸���ͼ
//#define DB_VIEW_CUSTUSERINFO                 _T("V_CustUserInfo")	//�ͻ���Ϣ��ͼ(ֱӪ��)
//#define DB_VIEW_GONGXURECORDS                _T("V_GongxuRecords")	//�����¼��ͼ add by yangjr 2017-7-5
#define DB_VIEW_KUANSHI                      _T("V_Kuanshi")			//��ʽ��ͼ
//#define DB_VIEW_KUANSHIPRICE                 _T("V_KuanshiPrice")	//
#define DB_VIEW_MEMBER                       _T("V_Member")			//
#define DB_VIEW_OTHERRECORD                  _T("V_OtherRecord")		//
#define DB_VIEW_OTHERRECORDS                 _T("V_OtherRecords")		//
//#define DB_VIEW_ORDER                        _T("V_RdRecords")		//������ͼ
#define DB_VIEW_ORDERCHILD                   _T("V_RdRecordsChild")		//����������ͼ
#define DB_VIEW_ORDERSALES                   _T("V_RdRecordsSales")		//��������ͼ
//#define DB_VIEW_RDRECORDS1                   _T("V_RdRecords1")		//
#define DB_VIEW_SHOPRECORD                   _T("V_ShopRecord")
#define DB_VIEW_SHOPRECORDS                  _T("V_ShopRecords")
#define DB_VIEW_SHOPRECORDS1                 _T("V_ShopRecords1")
#define DB_VIEW_USERINFO                     _T("V_UserInfo")
#define DB_VIEW_MACMGN                       _T("V_MacMgn")			//����������ͼ	add by lida 2017/11/20
#define DB_VIEW_FAHUORECORDS                 _T("V_FahuoRecords")	//������¼��ͼ by yangjr2018/3/26
#define DB_VIEW_BANDPROGRAMMINGVIEW          _T("V_BandProgramming") //������Ʒ��Ϣ��ͼ  add anjie by 2018/08/28

#define DB_VIEW_PRODUCTPROCESS               _T("V_ProductProcess")	//��ƷӦ��ִ�еĹ��� ����Ӧ�Ĺ����¼��ͼ wangzl 2018-08-30
#define DB_VIEW_PRODUCTVERSIONORDERS         _T("V_ProductVersionOrders") //�����浥��ͼ
#define DB_VIEW_PRODUCTREVISIONRECORDS       _T("V_ProductRevisionRecords") //�����浥�İ�������ͼ wangzl 2018-09-03

#define DB_VIEW_PROCESSRECORDSDETAILS        _T("V_ProcessRecordsDetails")    //�����¼��������� �����¼ + ��ӦƬ�� ���� ����Ϣ  wangzl 2018-10-08
#define DB_VIEW_PROCESSRECORDS               _T("V_ProcessRecords")           //�Ӷ�������صĹ����¼��������Ϣ wangzl 2018-10-08
#define DB_VIEW_PROCESSRECORDS_MAINDETAILS   _T("V_ProcessRecords_MainDetails")//�������򼰶�Ӧ����Ա��Ϣ
#define DB_VIEW_PROCESSRECORDS_MAIN          _T("V_ProcessRecords_Main") //�������Ĺ����¼�Ͷ�����������Ϣ
#define DB_VIEW_OUTREWORKRECORDS             _T("V_OutReworkRecords")	//���ⷵ��������ͼ -- �ֶθ�DB_VIEW_PROCESSRECORDSһ�� add by yangjr 2018-11-15
#define DB_VIEW_OUTREWORKRECORDS_MAIN        _T("V_OutReworkRecords_Main")	//���ⷵ��������ͼ���� -- �ֶθ�DB_VIEW_PROCESSRECORDS_MAINһ�� add by yangjr 2018-11-15

#define DB_PROCESS_ORDERONEMOREPIECEINSERT   _T("P_RdRecordsOneMorePieceInsert")//һ������µ��Ĵ洢���� �����ֻ��һ����ɫ�����ĵ���  wangzl 2018-10-22
#define DB_PROCESS_SAVEFILEINFO              _T("P_SaveFileInfo")

#define DB_PROCESS_SALESORDERINSERT          _T("P_SalesRdRecordsInsert") //���۶��������洢����

#define DB_PROCESS_FAHUORECORDADD            _T("P_FaHuoRecordAddNew")	//�����������Ĵ洢���� yangjr 2018-3-27
#define DB_P_CreateNewInventoryCheckPeriod   _T("P_CreateNewInventoryCheckPeriod")     //�����µ��̵����� add by lida 2018/06/05
#define DB_P_CreateCYCode                    _T("P_CreateCYCode")    //�����µĳ�����ⵥ�� add by lida 2018/06/05
#define DB_P_CreateCYKSOrdCode               _T("P_CreateCYKSOrdCode")     //�����µĳ���������ʽ������ add by lida 2018/06/05
#define DB_P_CreateSalesCode              _T("P_CreateSalesCode")  //�������۵��� add by lida 2018/10/09
#define DB_P_Add_Del_SalesProductOrder       _T("P_Add_Del_SalesProductOrder")   //�޸Ķ������� add by lida 2018/11/05
#define DB_P_CreateYarnRecordCode            _T("P_CreateYarnRecordCode")     //����ɴ�߳���ⵥ�� add by lida 2019/02/14

#define DB_P_ImportProductKSInfo             _T("P_ImportProductKSInfo")      //�����ʽ������Ϣ����Ʒά���� add by lida 2018/06/15
#define DB_P_ImportProductKSInfo_Single      _T("P_ImportProductKSInfo_single")      //���뵱��ʽ������Ϣ����Ʒά���� add by lida 2018/07/20
#define DB_P_UpdateOrdPrintCount             _T("P_UpdateOrdPrintCount")      //���¶�����ӡϴˮ�����
#define DB_PROCESS_FAHUORECORDSINSERT        _T("P_FahuoRecordsInsert")//������ϸ����� Yangjr 2018/8/15
#define DB_PROCESS_ImportOrderKuCunToFahuo   _T("P_ImportOrderKuCunToFahuo")//���붩�����п�浽���� Yangjr 2018/9/20
#define DB_P_CreateOutReworkCode                 _T("P_CreateOutReworkCode")    //���ɳ��ⷵ������ yangjr 2018/11/15
#define DB_P_GetCanInboundChildCode          _T("P_GetCanInboundChildCode")    //����������ȡ��С�ܹ������ӵ� yangjr 2018/11/23
#define DB_P_DelCYKucunRollBackState          _T("P_DelCYKucunRollBackState")    //ɾ�����¿���ʱ��ع�����״̬ yangjr 2018/11/25
#define DB_P_UpdateYarnPriceNoRuKun           _T("P_UpdateYarnPriceNoRuKun")     //����δ���Ķ���ɴ�ߵ��� yangjr 2018/12/3
#define DB_P_ChangeZhuSe                      _T("P_ChangeZhuSe")     //�������⴦�������ɫ�洢���� yangjr 2018/12/11
#define DB_P_GetSalesCodeBatch              _T("P_GetSalesCodeBatch")  //������ӡ�����Ż�ȡ���� add by yangjr 2018/12/20
#define DB_P_GetBatchCode                    _T("P_GetBatchCode")    //�������ɶ����ŵĴ洢����	by WangZY 2019/01/03



#define DB_FUNCTION_GETPY                    _T("dbo.getPY")
//#define DB_FUNCTION_GETLastGXNameAndState    _T("dbo.getLastGongxuState") //��ȡ��һ������Ĺ��������Լ�״̬ yangjr 2018/1/17
#define DB_FUNCTION_GETSTRARRAYSTROFINDEX    _T("dbo.getStrArrayStrOfIndex")//���ݷָ���������ֵ��ȡ��ǰ�ַ�������Ķ�Ӧλ�õ��ַ���������1��ʼ
#define DB_FUNCTION_GETSTRARRAYLENGTH        _T("dbo.getStrArrayLength")//���ݷָ�����ȡ�����ַ�������ĸ���
//#define DB_FUNCTION_ISYARNLOCK _T("dbo.IsYarnLock") //ɴ�߿���Ƿ��㣬�Ƿ����¼� 0��ʾ����δ������1����ʾɴ����������2��ʾɴ�����¼� yangjr 2017-12-11 ��ʱ������2018/1/6
//#define DB_FUNCTION_IsYarnStockLowThenYuJing _T("dbo.IsYarnStockLowThenYuJing") //ɴ�߿���Ƿ���  0��ʾ������1����ʾɴ�ߵ���Ԥ��ֵ yangjr 2017-12-11 ��ʱ������2018/1/6
#define DB_WEB_CONFIGURATION                 _T("WebConfiguration")//��ҳ¼������
#define DB_FUNCTION_GETORDERPRINTEXTRASIZEREMARK  _T("dbo.GetOrderPrintExtraSizeRemark")
#pragma endregion ���ݿ����
//--------------------------------------------------------------------
#pragma region ���������Ͷ���
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
	DAT_VARIOUSSTYLE		,//�ඩ��������
	DAT_ACTMAP				,
	DAT_PROPRICE_STYLE   ,//��ʽ����۸��
	DAT_PROSET_STYLE     ,//��ʽ�������ñ�
   DAT_ORDER_FILE       ,//�����ļ�
   DAT_COMPANY_INFO     ,//��˾��Ϣ
   DAT_VGONGXURDRECORDS ,
   DAT_DEMAND_ORDER     ,//������ע�� ���ֲ�ͬ�Ĺ��� ��������Ա
   DAT_PIECEINFO        ,//��Ƭ��Ϣ
   DAT_FINDKEY_STYLE    ,//��ʽ�Ĺؼ���
   DAT_BINDINFO         ,//������Ϣ
   DAT_TEXTBOARD        ,//���ְ�
   DAT_PROGRAMMING      ,//��Ʒ�滮��
   DAT_PRODUCTSTRUCTUREPLANNINGDATA,//��Ʒ�ṹ�滮��
   DAT_PLANNING,          //������
   DAT_COLORINFO,             //��ɫ
   DAT_PICTURE,           //ͼƬ
   DAT_MATETIALINfO,      //����
   DAT_PRODUCTVERSIONS  ,//����-��Ʒ�汾��Ϣ
   DAT_PROCESSRECORDS   ,//���� ���̼�¼
   DAT_PRODUCTTASKASSIGN,//����-������
   DAT_BANKPROGRAMMING,//����-bankprogramming��ͼ
   DAT_PRODUCTPROCESS   ,//����-����
   DAT_PRODUCTREVISIONRECORDS,//����-�İ��¼
   DAT_CUSTOMERBRANCH,    //�ͻ��ֵ��
   DAT_PROCESSRECORDS_MAIN,//���������¼
   DAT_TABLE_MAX_SERIAL_COUNT,//���������ˮ��
   DAT_WEBIMAGEORDER,//���紫����ͼƬ��Ϣ��
}En_KDSFG_DBDataType;
#pragma endregion ���������Ͷ���

typedef enum EnSelect_Time
{
	STM_CUSTOM			= 0,	//�û��Զ���
	STM_TODAY			= 10,	//����
	STM_CURWEEK             ,	//11 ����
	STM_CURMONTH            ,	//12 ����
	DAT_CURQUARTER          ,	//13 ������
	DAT_CURYEAR				,	//14 ����

}En_KDSFG_Select_Time;

#define SampleOrderCate	_T("1����")
#define NormalOrderCate	_T("1��ͨ")
