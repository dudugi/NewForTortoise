#ifndef KDS_CLIENT_FILE_TRANS_H_H___
#define KDS_CLIENT_FILE_TRANS_H_H___


#define  KDSCTFLSRANS  extern "C++" __declspec(dllexport)

#include <string>
using namespace std;

#ifdef _UNICODE
typedef wstring tstring;
#else
typedef string tstring;
#endif

struct Account_Param
{
	//Account
	string userId;	//�û��˺�
	string userPwd;	//�û�����

	string ip_Port;	//IP��ַ+�˿ں�
};

struct Send_Param
{
	//Param
	string version;		//�汾�ͺ�
	string identification;//Ψһʶ����
	bool sendequip;		//�Ƿ��ͻ���
	string equipments;	//���ͻ����б�
	string refno;		//��ҵ�ο���
	string refuser;		//���������
	int refnum;			//��ҵ����
	int singletime;		//��Ƭ��֯ʱ��
	string memo;		//��ע
	string filetype;	//�˴��̶�ֻ�ܷ��ͻ����ļ�
	string filepath;	//�ļ�ȫ·��+����
	bool bCover;		//�Ƿ񸲸Ƿ����ͬ���ļ�

	Account_Param stu_accParam;
};



/*****�������ֵ*****/
enum Transfer_ResValue
{
	/**Return:KDS_Rn_SendFile**/
	en_KDS_TRAMSFER_RES_OK = 0,		//�ϴ��ɹ�
	en_KDS_TRAMSFER_RES_FAILED,		//�ϴ�ʧ��
	en_KDS_TRAMSFER_RES_FILE_EXIST,	//����ͬ���ļ�
	en_KDS_TRAMSFER_RES_FILE_UPING,	//ͬ���ļ������ϴ���...
	en_KDS_TRAMSFER_RES_ERR_UNKNOWN,//δ֪����
	en_KDS_TRAMSFER_RES_ERR_ACCOUNT,//�˻�����
	en_KDS_TRAMSFER_RES_ERR_GETDATA,//��ȡ�����쳣
	en_KDS_TRAMSFER_RES_ERR_DISNET,	//���粻ͨ

	/**Return:KDS_Rn_GetOnlineMacList**/
};

extern "C++" 
{
#include <map>

   typedef struct tag_S_MACHINE_STATE
   {  
      tag_S_MACHINE_STATE()
      {
         StateID = "";        
         Memo = "";           //STATE ID ��Ӧ�ı�����Ϣ
         fileName = "";       //���ڱ�֯
         WarnInfo = "";       //��̨����������ʷ
      }
      string StateID;
      string Memo;      
      string fileName;
      string WarnInfo;
   }S_MACHINE_STATE;//����״̬
   typedef std::map<std::string,S_MACHINE_STATE> MAP_MACHINE_STATE;

	/*
	 * @brief	�����ļ����նˣ�����ˣ�
	 * @param	Send_Param [in]
	 * @example	
	 Send_Param sendParam;
	 sendParam.version = "V1.0";					//�汾�ͺ� �̶�
	 sendParam.identification = "46rt34g345y5g";	//Ψһʶ����
	 sendParam.sendequip = true;					//�Ƿ��ͻ���
	 sendParam.equipments = "1";					//���ͻ����б�
	 sendParam.refno = "1";						//��ҵ�ο���
	 sendParam.refuser = "test";					//���������
	 sendParam.refnum = 1;						//��ҵ����
	 sendParam.singletime = 1;					//��Ƭ��֯ʱ��
	 sendParam.memo = "��ע";					//��ע
	 sendParam.filetype = "001";					//�˴����̶���ֻ�ܷ��ͻ����ļ�
	 sendParam.filepath = "C:\\test.001";		//�ļ�ȫ·��+����
	 sendParam.bCover = true;					//�Ƿ񸲸Ƿ����ͬ���ļ�

	 sendParam.stu_accParam.userId = "user";
	 sendParam.stu_accParam.userPwd = "123456";
	 sendParam.stu_accParam.ip_Port = "192.168.9.100:8008";
	 */
	KDSCTFLSRANS Transfer_ResValue KDS_Rn_SendFile(Send_Param *pSendParam);


	/*
	 * @brief	��ȡ��ǰ���߻����б�
	 * @param	
	 * @return	"00000033|00000034|00000035"

	 * @example	
	 Account_Param accParam;
	 accParam.userId = "user";
	 accParam.userPwd = "123456";
	 accParam.ip_Port = "121.40.222.128:8008";
	 */
	KDSCTFLSRANS tstring KDS_Rn_GetOnlineMacList(Account_Param *pAccParam);

   /*
	 * @brief	�ж��ļ��������Ƿ��и��ļ�
	 * @param
    std::string serviceIp_Port:������ip+�˿�;
    std::string userName:�û���;
    std::string userPw:�û�����;
    std::string fileName:�ļ����ƣ�����׺����������·������;
	 * @example	
    serviceIp_Port = "121.40.222.128:8008";
	 auserName = "user";
	 userPw = "123456";	 
    fileName = "test.001";
	 */
   KDSCTFLSRANS Transfer_ResValue KDS_Rn_IsFileExist(std::string serviceIp_Port,std::string userName,std::string userPw,std::string fileName);

   KDSCTFLSRANS Transfer_ResValue KDS_Rn_SendFileFromServiceToMachine(std::string serviceIp_Port,std::string userName,std::string userPw,std::string ftpFileName,std::string macid);

   KDSCTFLSRANS Transfer_ResValue KDS_Rn_GetCurMachineState(std::string serviceIp_Port,std::string userName,std::string userPw,int iLanguage,std::string macids,MAP_MACHINE_STATE &mapState);

   	/*
	 * @brief	�����ļ����նˣ�����ˣ�
	 * @param	Send_Param [in]
	 * @example	
	 Send_Param sendParam;
	 sendParam.version = "V1.0";					//�汾�ͺ� �̶�
	 sendParam.identification = "46rt34g345y5g";	//Ψһʶ����
	 sendParam.sendequip = true;					//�Ƿ��ͻ���
	 sendParam.equipments = "1";					//���ͻ����б�
	 sendParam.refno = "1";						//��ҵ�ο���
	 sendParam.refuser = "test";					//���������
	 sendParam.refnum = 1;						//��ҵ����
	 sendParam.singletime = 1;					//��Ƭ��֯ʱ��
	 sendParam.memo = "��ע";					//��ע
	 sendParam.filetype = "001";					//�˴����̶���ֻ�ܷ��ͻ����ļ�
	 sendParam.filepath = "C:\\test.001";		//�ļ�ȫ·��+����
	 sendParam.bCover = true;					//�Ƿ񸲸Ƿ����ͬ���ļ�

	 sendParam.stu_accParam.userId = "user";
	 sendParam.stu_accParam.userPwd = "123456";
	 sendParam.stu_accParam.ip_Port = "192.168.9.100:8008";
    std::string ftpPath = "12\\" ,����12�Ƿ�������knitĿ¼�µ����ļ���
	 */
	KDSCTFLSRANS Transfer_ResValue KDS_Rn_SendFile_NewPath(Send_Param *pSendParam,std::string ftpPath);
};

#endif