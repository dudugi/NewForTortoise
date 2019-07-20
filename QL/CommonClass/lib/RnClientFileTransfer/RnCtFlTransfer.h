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
	string userId;	//用户账号
	string userPwd;	//用户密码

	string ip_Port;	//IP地址+端口号
};

struct Send_Param
{
	//Param
	string version;		//版本型号
	string identification;//唯一识别码
	bool sendequip;		//是否发送机器
	string equipments;	//发送机器列表
	string refno;		//作业参考号
	string refuser;		//相关责任人
	int refnum;			//作业件数
	int singletime;		//单片编织时间
	string memo;		//备注
	string filetype;	//此处固定只能发送花型文件
	string filepath;	//文件全路径+名称
	bool bCover;		//是否覆盖服务端同名文件

	Account_Param stu_accParam;
};



/*****结果返回值*****/
enum Transfer_ResValue
{
	/**Return:KDS_Rn_SendFile**/
	en_KDS_TRAMSFER_RES_OK = 0,		//上传成功
	en_KDS_TRAMSFER_RES_FAILED,		//上传失败
	en_KDS_TRAMSFER_RES_FILE_EXIST,	//存在同名文件
	en_KDS_TRAMSFER_RES_FILE_UPING,	//同名文件正在上传中...
	en_KDS_TRAMSFER_RES_ERR_UNKNOWN,//未知错误
	en_KDS_TRAMSFER_RES_ERR_ACCOUNT,//账户错误
	en_KDS_TRAMSFER_RES_ERR_GETDATA,//获取数据异常
	en_KDS_TRAMSFER_RES_ERR_DISNET,	//网络不通

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
         Memo = "";           //STATE ID 对应的报警信息
         fileName = "";       //正在编织
         WarnInfo = "";       //这台机器报警历史
      }
      string StateID;
      string Memo;      
      string fileName;
      string WarnInfo;
   }S_MACHINE_STATE;//机器状态
   typedef std::map<std::string,S_MACHINE_STATE> MAP_MACHINE_STATE;

	/*
	 * @brief	发送文件到终端（服务端）
	 * @param	Send_Param [in]
	 * @example	
	 Send_Param sendParam;
	 sendParam.version = "V1.0";					//版本型号 固定
	 sendParam.identification = "46rt34g345y5g";	//唯一识别码
	 sendParam.sendequip = true;					//是否发送机器
	 sendParam.equipments = "1";					//发送机器列表
	 sendParam.refno = "1";						//作业参考号
	 sendParam.refuser = "test";					//相关责任人
	 sendParam.refnum = 1;						//作业件数
	 sendParam.singletime = 1;					//单片编织时间
	 sendParam.memo = "备注";					//备注
	 sendParam.filetype = "001";					//此处【固定】只能发送花型文件
	 sendParam.filepath = "C:\\test.001";		//文件全路径+名称
	 sendParam.bCover = true;					//是否覆盖服务端同名文件

	 sendParam.stu_accParam.userId = "user";
	 sendParam.stu_accParam.userPwd = "123456";
	 sendParam.stu_accParam.ip_Port = "192.168.9.100:8008";
	 */
	KDSCTFLSRANS Transfer_ResValue KDS_Rn_SendFile(Send_Param *pSendParam);


	/*
	 * @brief	获取当前在线机器列表
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
	 * @brief	判断文件服务器是否有该文件
	 * @param
    std::string serviceIp_Port:服务器ip+端口;
    std::string userName:用户名;
    std::string userPw:用户密码;
    std::string fileName:文件名称（含后缀名，但不含路径名）;
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
	 * @brief	发送文件到终端（服务端）
	 * @param	Send_Param [in]
	 * @example	
	 Send_Param sendParam;
	 sendParam.version = "V1.0";					//版本型号 固定
	 sendParam.identification = "46rt34g345y5g";	//唯一识别码
	 sendParam.sendequip = true;					//是否发送机器
	 sendParam.equipments = "1";					//发送机器列表
	 sendParam.refno = "1";						//作业参考号
	 sendParam.refuser = "test";					//相关责任人
	 sendParam.refnum = 1;						//作业件数
	 sendParam.singletime = 1;					//单片编织时间
	 sendParam.memo = "备注";					//备注
	 sendParam.filetype = "001";					//此处【固定】只能发送花型文件
	 sendParam.filepath = "C:\\test.001";		//文件全路径+名称
	 sendParam.bCover = true;					//是否覆盖服务端同名文件

	 sendParam.stu_accParam.userId = "user";
	 sendParam.stu_accParam.userPwd = "123456";
	 sendParam.stu_accParam.ip_Port = "192.168.9.100:8008";
    std::string ftpPath = "12\\" ,其中12是服务器的knit目录下的子文件夹
	 */
	KDSCTFLSRANS Transfer_ResValue KDS_Rn_SendFile_NewPath(Send_Param *pSendParam,std::string ftpPath);
};

#endif