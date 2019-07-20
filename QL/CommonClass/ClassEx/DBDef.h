#pragma once
/*************************************************
// <�ļ�>: DBDef.h
// <˵��>: ���ݿ��������ͼ�������������洢�������ƶ���ͷ�ļ�
// <����>: yangjr
// <����>: 2019/02/20 16:05:08
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 

//--------------------------------------------------------------------
#pragma region ���ݿ����
#define DB_TABLE_CLIENT_VARIFY_INFO          _T("ClientVarifyInfo")            //��¼��Ϣ��
#define DB_TABLE_MATERIEL_INFO               _T("MaterielInfo")                //������Ϣ��
#define DB_TABLE_COLORMAINTAIN_INFO          _T("ColorMaintain")               //��ɫά����  by liuhw 2018/08/20
#define DB_TABLE_PERSON                      _T("Userinfo")			             //��Ա��Ϣ���ڲ�Ա����
#define DB_TABLE_CUSTOM                      _T("Customer")			             //�ͻ���Ϣ��
#define DB_TABLE_FILE                        _T("Table_File")                  //�ļ���
#define DB_TABLE_STYLE                       _T("Kuanshi")			             //��ʽ��
#define DB_TABLE_YARN                        _T("Color")				             //ɴ�߱�
#define DB_TABLE_LOG                         _T("WorkLog")			             //��־��
#define DB_TABLE_SIZEPART                    _T("SizePart")			             //��λ��
#define DB_TABLE_PROCESS                     _T("Gongxu")			             //�����
#define DB_TABLE_DENSITY                     _T("DesDensity")			          //�ܶȱ�
#define DB_TABLE_DESFACECODE                 _T("DesFaceCode")			          //�������
#define DB_TABLE_DES_DENSITY                 _T("SampleDesDensity")			    //�ܶȱ�
#define DB_TABLE_FACECODE                    _T("SampleDesFaceCode")			    //�������
#define DB_TABLE_PIECEWEIGHT                 _T("PieceWeight")			          //��Ƭ������
#define DB_TABLE_SIZEPART_ORDER               _T("SizePart_Order")			    //�ߴ粿λ��
#define DB_TABLE_SIZEPART_VALUE               _T("SizePart_Value")			    //�ߴ粿λ����ֵ��
#define DB_TABLE_DATADICTIONARY              _T("TreeClass")			          //�����ֵ��
#define DB_TABLE_MENUS                       _T("Menus")				             //�����˵���
#define DB_TABLE_CONFIG                      _T("Config")			             //ȫ������
#define DB_TABLE_COLORPRICE                  _T("ColorPrice")		             //�۸����ñ� add by yangjr 2017-7-13
#define DB_TABLE_VARIOUSSTYLE                _T("VariousStyle")		          //һ��������Ӧ��Ϣ��
#define DB_TABLE_PROSET_STYLE                _T("ProSet_Style")		          //��ʽ�������ñ� wangzl 2017-11-08
#define DB_TABLE_FANGANGONGXU                _T("FangAnGongxu")		          //���򷽰��� add by wuzhihua 2018/01/16
#define DB_TABLE_COMPANY_INFO                _T("CompanyInfo")                 //��˾��Ϣ�� add by zhangyx 2018/01/22
#define DB_TABLE_COLNAME_SET                 _T("ColNameSet")		             //�ֶ������ñ� add by wuzhihua 2018/02/03
#define DB_TABLE_PIECEINFO                   _T("PieceInfo")                   //��Ƭ��Ϣ�� ���ڴ洢xx��Ƭ����ҡ���ǵ��� �Լ�����ͳ�ƹ���
#define DB_TABLE_STYLE_GLOBAL_SET            _T("TableStyleGlobalSet")         //�����ʽȫ������ add by wuzhihua 2018/4/13
#define DB_TABLE_PINZHONGSETTING             _T("PinZhongSetting")             //Ʒ��ά�� add by yangjr 2018/04/17
#define DB_TABLE_FANGANPOWER                 _T("FangAnPower")                 // �Զ���Ȩ�޷�����    add by anjie 2018/06/04
#define DB_TABLE_STYLEMATERIAL               _T("StyleMaterial")               //��ʽ-ԭ������Ϣ    	by WangZY 2019/05/24
#define DB_TABLE_STYLECOLORPERCENT           _T("StyleColorPercent")           //������ʽ-��ɫ������Ϣ add by huangym 2018/12/28
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


#define DB_TABLE_PROCESSRECORDS              _T("ProcessRecords")              //�ӵ������¼�� wangzl 2018-10-08
#define DB_TABLE_SMALLPIC		               _T("SmallPic")                    //Сͼ����  by huangym 2018-12-3
#define DB_TABLE_DESIGNDATALIB		         _T("DesignData_Lib")                  // ����������
#define DB_TABLE_DESIGNDATA		             _T("DesignData")                  // �ư����ñ�
#define DB_TABLE_STANDARDSIZE  		         _T("StandardSize")                // ��׼�����
#define DB_TABLE_STANDARDSIZEMODIFY  		   _T("StandardSizeModify")          // ��׼���������
#define DB_TABLE_STANDARDSIZE_PINMING		   _T("StandardSize_PinMing")        // ��׼����-Ʒ����
#define DB_TABLE_CONTROLSPERMISSION          _T("ControlsPermission")//�ؼ�Ȩ�ޱ� wangzl 2019-2-18
#define DB_TABLE_USER_STYLEPERMISSION        _T("User_StylePermission")//�û���ʽȨ�ޱ� wangzl 2019-05-06
#define DB_TABLE_STYLE_SIZE                  _T("Style_Size") // �淿��ʽ�ߴ���Ϣ�� liuhw 2019/05/06
#define DB_TABLE_STYLE_CHIMA                 _T("Style_Chima") // �淿��ʽ������Ϣ�� liuhw 2019/05/06
#define DB_TABLE_STYLE_CHECKRECORDS          _T("Style_CheckRecords") // ��ʽ��������¼�� liuhw 2019/05/06
#define DB_TABLE_STYLE_COST                  _T("Style_Cost")      //��ʽ�ɱ���Ϣ��    anjie 20190523
#define DB_TABLE_STYLE_FILEINFO              _T("Style_FileInfo")  //��ʽ�ļ���Ϣ��    wangzl 2019/05/28
#define DB_TABLE_STYLE_VERSIONRECORDS        _T("Style_VersionRecords")  //��ʽ�汾��¼��    wangzl 2019/06/05
#define DB_TABLE_STYLE_DESCRIPTION           _T("Style_Description")    //��ʽ������     lida 2019/06/11
#define DB_TABLE_CONFIG_TAGNAME              _T("Config_TagName")    //��ǩ���� wangzl 2019-6-12
#define DB_TABLE_STYLE_DESDENISITY           _T("Style_DesDenisity")    //��ʽ�ܶȱ� wangzl 2019-6-19
#define DB_TABLE_STYLE_DESFACECODE           _T("Style_DesFaceCode")    //��ʽ������� wangzl 2019-6-19
#define DB_TABLE_STYLE_BASIC_FIELDSET        _T("Style_Basic_FieldSet")    //��ʽ�����ֶ����ñ�
#define DB_TABLE_SAMPLE_CLOTHING_INFO        _T("SampleClothingInfo")   //���� lida 2019/07/01
#define DB_TABLE_SAMPLE_CLOTHING_RECORDS     _T("SampleClothingRecords")   //�����շ���¼ lida 2019/07/01
#define DB_TABLE_STYLESIZEEXTRA              _T("Style_SizeExtra")			   //��ʽ�ߴ������Ϣ�� yangjr 2019/07/14 
#define DB_TABLE_PRODUCTORDERINFO            _T("ProductOrderInfo")        //�淿��������Ϣ�� lida 2019/07/17
#define DB_TABLE_SALESORDERINFO            _T("SalesOrderInfo")        //�淿��������Ϣ�� lida 2019/07/17

#define DB_VIEW_KUANSHI                      _T("V_Kuanshi")			//��ʽ��ͼ
#define DB_VIEW_ORDERCHILD                   _T("V_RdRecordsChild")		//����������ͼ
#define DB_VIEW_ORDERSALES                   _T("V_RdRecordsSales")		//��������ͼ
#define DB_VIEW_USERINFO                     _T("V_UserInfo")
#define DB_VIEW_BANDPROGRAMMINGVIEW          _T("V_BandProgramming") //������Ʒ��Ϣ��ͼ  add anjie by 2018/08/28

#define DB_VIEW_PRODUCTPROCESS               _T("V_ProductProcess")	//��ƷӦ��ִ�еĹ��� ����Ӧ�Ĺ����¼��ͼ wangzl 2018-08-30
#define DB_VIEW_PRODUCTVERSIONORDERS         _T("V_ProductVersionOrders") //�����浥��ͼ
#define DB_VIEW_PRODUCTREVISIONRECORDS       _T("V_ProductRevisionRecords") //�����浥�İ�������ͼ wangzl 2018-09-03

#define DB_VIEW_PROCESSRECORDSDETAILS        _T("V_ProcessRecordsDetails")    //�����¼��������� �����¼ + ��ӦƬ�� ���� ����Ϣ  wangzl 2018-10-08
#define DB_VIEW_PROCESSRECORDS               _T("V_ProcessRecords")           //�Ӷ�������صĹ����¼��������Ϣ wangzl 2018-10-08
#define DB_VIEW_PROCESSRECORDS_MAINDETAILS   _T("V_ProcessRecords_MainDetails")//�������򼰶�Ӧ����Ա��Ϣ
#define DB_VIEW_PROCESSRECORDS_MAIN          _T("V_ProcessRecords_Main") //�������Ĺ����¼�Ͷ�����������Ϣ
#define DB_VIEW_USERSTYLE_PERMISSION         _T("V_User_Style_Permission")//�û���ʽȨ��
#define DB_VIEW_KUANSHI_NEXTPROINFO          _T("V_Kuanshi_NextProInfo")//��ʽ�¸�������Ϣ��ͼ
#define DB_VIEW_STYLEFILEINFO                _T("V_StyleFileInfo")//��ʽ���ļ���Ϣ��ͼ

#define DB_VIEW_CLOUD_MODULE_INFO            _T("V_CloudModuleInfo")      //��ģ����Ϣ��ͼ��     	by WangZY 2019/06/04
#define DB_VIEW_STYLE_COST                   _T("V_Style_Cost")         //��ʽ�ɱ���ͼ     	by wangzl 2019/06/11
#define DB_VIEW_USERTASKINFO                 _T("V_UserTaskInfo")         //�û�������Ϣ��ͼ     	by wangzl 2019/06/14

#define DB_PROCESS_ORDERONEMOREPIECEINSERT   _T("P_RdRecordsOneMorePieceInsert")//һ������µ��Ĵ洢���� �����ֻ��һ����ɫ�����ĵ���  wangzl 2018-10-22
#define DB_PROCESS_SAVEFILEINFO              _T("P_SaveFileInfo")
#define DB_PROCESS_CreateSampleClothingBarCode  _T("P_CreateSampleClothingBarCode") //���µ���ˮ�� lida 2019/07/02

#define DB_P_CreateSalesCode              _T("P_CreateSalesCode")  //�������۵��� add by lida 2018/10/09

#define DB_P_ImportProductKSInfo             _T("P_ImportProductKSInfo")      //�����ʽ������Ϣ����Ʒά���� add by lida 2018/06/15
#define DB_P_ImportProductKSInfo_Single      _T("P_ImportProductKSInfo_single")      //���뵱��ʽ������Ϣ����Ʒά���� add by lida 2018/07/20
#define DB_P_UpdateOrdPrintCount             _T("P_UpdateOrdPrintCount")      //���¶�����ӡϴˮ�����

#define DB_P_GetCanInboundChildCode          _T("P_GetCanInboundChildCode")    //����������ȡ��С�ܹ������ӵ� yangjr 2018/11/23
#define DB_P_GetSalesCodeBatch              _T("P_GetSalesCodeBatch")  //������ӡ�����Ż�ȡ���� add by yangjr 2018/12/20
#define DB_P_GetBatchCode                    _T("P_GetBatchCode")    //�������ɶ����ŵĴ洢����	by WangZY 2019/01/03

#define DB_P_UPDATE_STYLE_COST               _T("P_UpdateStyleCost")    //���¿�ʽ�ܳɱ����ܱ��� by lida 2019/07/12

#define DB_FUNCTION_GETPY                    _T("dbo.getPY")
#define DB_FUNCTION_GETSTRARRAYSTROFINDEX    _T("dbo.getStrArrayStrOfIndex")//���ݷָ���������ֵ��ȡ��ǰ�ַ�������Ķ�Ӧλ�õ��ַ���������1��ʼ
#define DB_FUNCTION_GETSTRARRAYLENGTH        _T("dbo.getStrArrayLength")//���ݷָ�����ȡ�����ַ�������ĸ���



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
   DAT_PIECEINFO        ,//��Ƭ��Ϣ
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
   DAT_PROCESSRECORDS_MAIN,//���������¼
   DAT_WEBIMAGEORDER,//���紫����ͼƬ��Ϣ��
   DAT_CONTROLSPERMISSION,//�ؼ�Ȩ�޶���
   DAT_USERSTYLE_PERMISSION,//�û���ʽȨ��
   DAT_STYLE_CHIMA,//�淿��ʽ����
   DAT_STYLE_CHECKRECORDS,//��ʽ��������¼
   DAT_STYLE_NEXTPROINFO,//��ʽ���¸�������Ϣ
   DAT_STYLE_COST ,//��ʽ�ɱ�
   DAT_STYLE_FILEINFO ,//��ʽ�ɱ�
   DAT_STYLE_VERSIONRECORDS,//��ʽ�汾����İ��¼
   DAT_V_STYLE_COST,//��ʽ�ɱ���ͼ
   DAT_CONFIG_TAGNAME,//��ǩ����
   DAT_V_USER_TASKINFO,//�û���Ϣ��ͼ
   DAT_STYLE_DESDENISITY ,//��ʽ�ܶ�
   DAT_STYLE_DESFACECODE ,//��ʽ������
   DAT_STYLE_BASIC_FIELDSET,//��ʽ������Ϣ
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
