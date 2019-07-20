#pragma once
#include "HttpClient.h"

#define SMS_INI_SEG_NAME _T("SMS") //ini�ļ��з��Ͷ��ŵĶ��� 
#define SMS_INI_VALUE_NAME_SMSGATEWAY _T("SMSGateway") //ini�ļ��з��Ͷ��ŵ�ֵ��--���Ͷ�������
#define SMS_INI_VALUE_NAME_YEGATEWAY _T("YEGateway") //ini�ļ��з��Ͷ��ŵ�ֵ��--�����������
#define SMS_INI_VALUE_NAME_CONTENT _T("Content") //ini�ļ��з��Ͷ��ŵ�ֵ��--Ĭ�϶�������

//����ͨ ���Ͷ��ź�ķ�������
typedef struct tag_SENDMSG_RESULT
{
   CString strState;//״̬��
   int iSendNum;//�۷�����
   double fSendJE;//�۷ѽ��
   double fYE;//���
   CString strSSID;//���
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
   //��ȡ���
   BOOL GetAccountBalance(CString &strYE);
   //���Ͷ��Ŷ���绰������,����
   BOOL SendMsg(CString phoneNum,CString Content,SENDMSG_RESULT &resultData);
   //��ȡĬ�϶��ŷ�������
   CString GetDefaultContent(){return m_strContent;}
private:
   CSendSMS(void);
    ~CSendSMS(void);
private:
   CHttpClient m_httpClient;
   CString m_smsGateway;//���Ͷ�������
   CString m_yeGateway;//�����������
   CString m_strContent;//Ĭ�϶�������
   BOOL m_bShipDefaultCheck;//������������Ƿ�Ĭ�Ϲ�ѡ
};
