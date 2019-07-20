#pragma once

/*********************************��Ա��Ϣ�� begin********************************************/
#define DB_TABLE_USERINFO                      _T("UserInfo")			//��Ա��Ϣ����

//��Ա��Ϣ���ֶ�
#define DBUser_key_ID				   _T("ID")			//ID ����
#define DBUser_key_cUserID			   _T("cUserID")		//�û�ID
#define DBUser_key_cPassword		   _T("cPassword")		//�û�����
#define DBUser_key_cUserName		   _T("cUserName")		//�û�����
#define DBUser_key_cUserDate		   _T("cUserDate")		//�û�ע��ʱ��
#define DBUser_key_dtLastLoadTime	_T("dtLastLoadTime")		//���һ�ε�¼ʱ��
#define DBUser_key_iUserState		   _T("iUserState")		//�û�״̬ �Ƿ�ע��
/*********************************��Ա��Ϣ�� end********************************************/


/*********************************�ͻ���Ϣ������ begin********************************************/
#define DB_TABLE_CUSTOMERBASEDATA                      _T("CustomerBaseData")			//�ͻ���Ϣ��������

//�ͻ���Ϣ�������ֶ�
#define DBCusBase_key_ID				   _T("ID")			      //ID ����
#define DBCusBase_key_cCusCode			_T("cCusCode")		   //�ͻ����
#define DBCusBase_key_cCusName			_T("cCusName")		   //�ͻ�����
#define DBCusBase_key_cCusAddress		_T("cCusAddress")		//�ͻ���ַ
#define DBCusBase_key_cCusPhone			_T("cCusPhone")		//��ϵ��
#define DBCusBase_key_cCusContacts		_T("cCusContacts")	//�汾��
#define DBCusBase_key_cPDMVersion		_T("cPDMVersion")		//�ͻ���ַ
#define DBCusBase_key_cProvince			_T("cProvince")		//ʡ
#define DBCusBase_key_isLocalDB			_T("isLocalDB")		//���ݿ��Ƿ����ڱ���
#define DBCusBase_key_cServerPerson		_T("cServerPerson")		//������Ա
#define DBCusBase_key_iClientNum			_T("iClientNum")		//�ͻ�������
#define DBCusBase_key_cMemo			   _T("cMemo")		//��ע
/*********************************�ͻ���Ϣ������ end********************************************/

/*********************************�ͻ����ݿ����ñ� begin********************************************/
#define DB_TABLE_CUSTOMERDBDATA                      _T("CustomerDbData")			//�ͻ����ݿ����ñ�--����

//�ͻ����ݿ����ñ�--�ֶ�
#define DBCusDb_key_cCusCode			_T("cCusCode")		   //�ͻ����
#define DBCusDb_key_cDbServerName	_T("cDbServerName")	//���ݿ�����
#define DBCusDb_key_iDbServerPort	_T("iDbServerPort")	//���ݿ�˿�
#define DBCusDb_key_cDbAccount		_T("cDbAccount")		//��¼�˻�
#define DBCusDb_key_cDbPassword		_T("cDbPassword")		//��¼����
#define DBCusDb_key_cDbServerIP	   _T("cDbServerIP")	   //���ݿ�IP
/*********************************�ͻ����ݿ����ñ� end********************************************/

/*********************************�ͻ��������ݱ� begin********************************************/
#define DB_TABLE_CUSTOMERENCRYPTDATA                      _T("CustomerEncryptData")			//�ͻ��������ݱ�--����

//�ͻ��������ݱ�--�ֶ�
#define DBCusEncrypt_key_cCusCode		_T("cCusCode")		//�ͻ����
#define DBCusEncrypt_key_cData1		   _T("cData1")	   //��������1
#define DBCusEncrypt_key_cData2	      _T("cData2")	   //��������2
#define DBCusEncrypt_key_cData3		   _T("cData3")	   //��������3
#define DBCusEncrypt_key_cData4		   _T("cData4")	   //��������4
/*********************************�ͻ��������ݱ� end********************************************/


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


/*********************************�ͻ����ݲ�����¼�� begin********************************************/
#define DB_TABLE_CUSOPRECORDS                      _T("CusOpRecords")			//�ͻ����ݲ�����¼��--����

//�ͻ����ݲ�����¼��--�ֶ�
#define DBCusOpRds_key_ID				   _T("ID")			      //ID ����
#define DBCusOpRds_key_cOpType			_T("cOpType")			//��������
#define DBCusOpRds_key_cCusCode			_T("cCusCode")		   //�ͻ����
#define DBCusOpRds_key_cCusName			_T("cCusName")		   //�ͻ�����
#define DBCusOpRds_key_cCusAddress		_T("cCusAddress")		//�ͻ���ַ
#define DBCusOpRds_key_cCusPhone			_T("cCusPhone")		//��ϵ��
#define DBCusOpRds_key_cCusContacts		_T("cCusContacts")	//�汾��
#define DBCusOpRds_key_cPDMVersion		_T("cPDMVersion")		//�ͻ���ַ
#define DBCusOpRds_key_cProvince			_T("cProvince")		//ʡ
#define DBCusOpRds_key_isLocalDB			_T("isLocalDB")		//���ݿ��Ƿ����ڱ���
#define DBCusOpRds_key_cServerPerson	_T("cServerPerson")		//������Ա
#define DBCusOpRds_key_iClientNum		_T("iClientNum")		//�ͻ�������
#define DBCusOpRds_key_cMemo			   _T("cMemo")		//��ע

#define DBCusOpRds_key_cDbServerName	_T("cDbServerName")	//���ݿ�����
#define DBCusOpRds_key_iDbServerPort	_T("iDbServerPort")	//���ݿ�˿�
#define DBCusOpRds_key_cDbAccount		_T("cDbAccount")		//��¼�˻�
#define DBCusOpRds_key_cDbPassword		_T("cDbPassword")		//��¼����
#define DBCusOpRds_key_cDbServerIP	   _T("cDbServerIP")	   //���ݿ�IP

#define DBCusOpRds_key_cBeginTime	   _T("cBeginTime")	//��ʼʱ��
#define DBCusOpRds_key_cTime	         _T("cTime")	      //����ʱ��
#define DBCusOpRds_key_cModeData	      _T("cModeData")	//����ģ��
#define DBCusOpRds_key_cPerson	      _T("cPerson")	   //�����Ϣ
#define DBCusOpRds_key_fChongZhiJE	   _T("fChongZhiJE")	//��ֵ���
/*********************************�ͻ����ݲ�����¼�� end********************************************/
