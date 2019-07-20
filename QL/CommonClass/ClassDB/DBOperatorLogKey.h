#pragma once
//pdm ��־������ add by lida 2018/03/07
using namespace std;
#define Log_Type_Num		12		//�������� ����
#define Log_Cate_Num		77	//����	����
#define TABLE_NAME_MAX_LEN	50

typedef enum Em_WorkLog_Type		//��������
{   
   enLog_Type_Del = 0,		//ɾ��		0
   enLog_Type_Upadate,		//����		1
   enLog_Type_Add,			//���		2
   enLog_Type_Login,		//����		3
   enLog_Type_Logout,		//�˳�		4
   enLog_Type_UpLoad,		//�ϴ�		5
   enLog_Type_DownLoad,	//����		6
   enLog_Type_Search,		//��ѯ		7
   enLog_Type_View,		//�鿴		8
   enLog_Type_Print,		//��ӡ		9
   enLog_Type_Export,		//����		10
   enLog_Type_Inport		//����		11
};

static TCHAR g_LogType[Log_Type_Num][TABLE_NAME_MAX_LEN] = {
   {_T("ɾ��")},
   {_T("����")},
   {_T("���")},
   {_T("����")},
   {_T("�˳�")},
   {_T("�ϴ�")},
   {_T("����")}, 
   {_T("��ѯ")},
   {_T("�鿴")},
   {_T("��ӡ")},
   {_T("����")},
   {_T("����")},
};

typedef enum Em_WorkLog_Cate		//����
{
   enLog_Cate_TableName_Null = 0,
   enLog_Cate_SQL_Transaction = 1,           //���ݿ�����
   enLog_Cate_TableName_Color = 2,					//	ɫ��ά��
   enLog_Cate_TableName_ColorPrice,				//	�۸�����
   enLog_Cate_TableName_Config,					//	ȫ������
  
   enLog_Cate_TableName_CompanyInfo,				//	��˾��Ϣ	
   enLog_Cate_TableName_MacFile_Mgn,				//	����ļ�����			
   enLog_Cate_TableName_Mac_Mgn,					//	������	

   enLog_Cate_TableName_Chat_MsgMgn,				//	Chat_MsgMgn								
   enLog_Cate_TableName_SizePart,					//	��λ��								
   enLog_Cate_TableName_Chat_MsgRecv,				//	Chat_MsgRecv								
   enLog_Cate_TableName_Size_Style,				//	Size_Style

   enLog_Cate_TableName_PanDianRecords,			//	�̵��¼	
   enLog_Cate_TableName_Schedule,					//	���
   enLog_Cate_TableName_Order_Flag,				//	������Ǵ���
   enLog_Cate_TableName_ProSet_Style,				//	��ʽ���� 20

   enLog_Cate_TableName_FangAnGongxu,				//	���򷽰�								
   enLog_Cate_TableName_ProPrice_Style,			//	��������۸�
   enLog_Cate_TableName_Plant_Mgn,					//	������								
   enLog_Cate_TableName_DesFaceCode,				//������	 25

   enLog_Cate_TableName_DesDensity,				//�ܶȱ�
   enLog_Cate_TableName_V_MacMgn,					//	����������ͼ										
   enLog_Cate_TableName_V_MacMacFileMgn,			//	����ļ�������ͼ 30

   enLog_Cate_TableName_VariousStyle,				//	һ��������Ӧ��Ϣ
   enLog_Cate_TableName_Customer,					//	�ͻ�����	
   enLog_Cate_TableName_Gongxu,					//	�������	
   enLog_Cate_TableName_Kuanshi,					//	��ʽά��							
   enLog_Cate_TableName_Menus,						//	�˵�����		35   									
	
   enLog_Cate_TableName_OtherRecord,				//	ɴ�߳�����¼										
   enLog_Cate_TableName_OtherRecords,				//	ɴ�߳����롢�졢������					
   enLog_Cate_TableName_SMS,						//	���ż�¼								
   enLog_Cate_TableName_TreeClass,					//	�����ֵ�

   enLog_Cate_TableName_Userinfo,					//	Ա������	
   enLog_Cate_TableName_V_Kuanshi,					//	��ʽά����ͼ
   enLog_Cate_TableName_V_OtherRecord,				//	ɴ�߳�����¼��ͼ										
   enLog_Cate_TableName_V_OtherRecords,			//	ɴ�߳����롢�졢��������ͼ	 45	
								
   enLog_Cate_TableName_V_Userinfo,				//	Ա��������ͼ										
   enLog_Cate_TableName_WorkLog,					//	������־	
   enLog_Cate_TableName_DebitRecords,        // �ۿ��¼
   enLog_Cate_TableName_OrderInStorage,      //��������
   enLog_Cate_TableName_CYRecord,            //���������� 50

   enLog_Cate_TableName_CYRecords,           //�����������ϸ��
   enLog_Cate_TableName_V_CYRecords,         //��������ͼ
   enLog_Cate_TableName_V_OrderInStorage,    //������ͼ
   enLog_Cate_TableName_V_FahuoRecords,      // �ۺϷ�����ͼ��¼
   enLog_Cate_TableName_FahuoRecord,      // �ۺϷ����� 55

   enLog_Cate_TableName_FahuoRecords,      // �ۺϷ������Ա�
   enLog_Cate_TableName_RdOffFactoryRework,      // ���ⷵ���ǼǱ�
   enLog_Cate_TableName_PINZHONGSETTING,					//	Ʒ��ά��
   enLog_Cate_TableName_TUIHUOSTATE,					//	�˻�״̬
   enLog_Cate_TableName_InPlantReworkRecords, //���ڷ���¼�� 60

   enLog_Cate_TableName_WLKuanshi,     //��Ʒ��ʽ��
   enLog_Cate_TableName_WLKuanshi_Detail_info,  //��Ʒ��ʽ�����
   enLog_Cate_TableName_MATERIEL_INFO, //����ά��
   enLog_Cate_TableName_FANGANMACTYPE, //���򷽰��󶨻������ͱ� 65

   enLog_Cate_TableName_ORDER_TYPE_PRICE_SET,  //�������ͼ۸�ά�� 
   enLog_Cate_TableName_ProcessRecords,				//�¹����¼--�ӱ�1�� 70

   enLog_Cate_TableName_ProcessRecordsDetails,		//�¹����¼--�ӱ�2��
   enLog_Cate_TableName_ProcessRecords_Main,		//�¹����¼--������
   enLog_Cate_TableName_OutReworkGXRecords,//���ⷵ������� 75

   enLog_Cate_TableName_Chat_MsgMgn_History,//�����¼�鵵
};

static TCHAR g_TableID[Log_Cate_Num][TABLE_NAME_MAX_LEN] = {
   {_T("")},					//0

   {_T("SQL����")},					
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
   {_T("OutReworkGXRecords")},//���ⷵ������� 75

   {_T("Chat_MsgMgn_History")},
};
//���ı���
static TCHAR g_TableID_CN[Log_Cate_Num][TABLE_NAME_MAX_LEN] = {
   {_T("")},					//0

   {_T("SQL����")},					
   {_T("ɫ��ά��")},
   {_T("�۸�����")},
   {_T("ȫ������")},
   {_T("�����ļ�")},  //5

   {_T("��˾��Ϣ")}, 
   {_T("����ļ�����")},
   {_T("������")},   
   {_T("ɴ�߿�ʽ����")},
   {_T("ɴ�߶�������")}, //10

   {_T("������Ϣ�����")},
   {_T("��λ��")},
   {_T("���������Ϣ��")},
   {_T("��ʽ�ߴ�")},
   {_T("�����ߴ�")}, //15

   {_T("�̵��¼")},	
   {_T("���")},
   {_T("������Ǵ���")},
   {_T("��������")},
   {_T("��ʽ����")},//20

   {_T("���򷽰�")},
   {_T("��������۸�")},
   {_T("��������")},
   {_T("������")},
   {_T("������")},	//25

   {_T("�ܶȱ�")},			
   {_T("������������")},
   {_T("�����������")},  
   {_T("����������ͼ")},
   {_T("����ļ�������ͼ")},//30

   {_T("һ��������Ӧ��Ϣ")},
   {_T("�ͻ�����")}, 
   {_T("�������")},  
   {_T("��ʽά��")},
   {_T("�˵�����")}, //35   

   {_T("ɴ�߳�����¼")},
   {_T("ɴ�߳����롢�졢������")},
   {_T("���ż�¼")},
   {_T("�����ֵ�")},
   {_T("�����")}, //40

   {_T("Ա������")},
   {_T("�۸�������ͼ")},
   {_T("��ʽά����ͼ")},
   {_T("ɴ�߳�����¼��ͼ")},
   {_T("ɴ�߳����롢�졢��������ͼ")},//45 

   {_T("Ա��������ͼ")},
   {_T("������־")},
   {_T("�ۿ��¼")},
   {_T("��������")},
   {_T("����������")}, //50

   {_T("�����������ϸ��")},
   {_T("��������ͼ")},
   {_T("������ͼ")}, 
   {_T("�ۺϷ�����ͼ��¼")},
   {_T("�ۺϷ�����")},//55

   {_T("�ۺϷ������Ա�")},
   {_T("���ⷵ���ǼǱ�")},
   {_T("Ʒ��ά��")},
   {_T("�˻�״̬")},
   {_T("���ڷ���¼��")},//60

   {_T("��Ʒ��ʽ��")},
   {_T("��Ʒ��ʽ�����")},
   {_T("����ά��")},  
   {_T("�ͻ����η����")},
   {_T("���򷽰��󶨻������ͱ�")},//65

   {_T("�������ͼ۸�ά��")},
   {_T("��ʽϵ��")},
   {_T("�¶���1��")},
   {_T("�¶���2��")},
   {_T("�¹����¼--�ӱ�1��")},//70

   {_T("�¹����¼--�ӱ�2��")},
   {_T("�¹����¼--������")},
   {_T("������ע��")},
   {_T("��������ϸ��")},
   {_T("���ⷵ�������")},//���ⷵ������� 75
};

