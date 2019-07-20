#pragma once
#include "HttpClient.h"

#define SMS_INI_SEG_NAME _T("SMS") //ini文件中发送短信的段名 
#define SMS_INI_VALUE_NAME_SMSGATEWAY _T("SMSGateway") //ini文件中发送短信的值名--发送短信网关
#define SMS_INI_VALUE_NAME_YEGATEWAY _T("YEGateway") //ini文件中发送短信的值名--短信余额网关
#define SMS_INI_VALUE_NAME_CONTENT _T("Content") //ini文件中发送短信的值名--默认短信内容

//吉信通 发送短信后的返回数据
typedef struct tag_SENDMSG_RESULT
{
   CString strState;//状态码
   int iSendNum;//扣费条数
   double fSendJE;//扣费金额
   double fYE;//余额
   CString strSSID;//编号
   CString info;
   tag_SENDMSG_RESULT()
   {
      strState=_T("");
      int iSendNum = 0;
      fSendJE = 0.0f;
      fYE = 0.0f;
      strSSID=_T("");
      info = _T("");
   }
}SENDMSG_RESULT;

class CSendSMS
{
public: 
   static CSendSMS * GetInstance()    
   {    
      static CSendSMS instance;     
      return &instance;    
   }
   //获取余额
   BOOL GetAccountBalance(CString &strYE);
   //发送短信多个电话号码用,隔开
   BOOL SendMsg(CString phoneNum,CString Content,SENDMSG_RESULT &resultData);
   //获取默认短信发送内容
   CString GetDefaultContent(){return m_strContent;}
private:
   CSendSMS(void);
    ~CSendSMS(void);
private:
   CHttpClient m_httpClient;
   CString m_smsGateway;//发送短信网关
   CString m_yeGateway;//短信余额网关
   CString m_strContent;//默认短信内容
   BOOL m_bShipDefaultCheck;//发货界面短信是否默认勾选
};
