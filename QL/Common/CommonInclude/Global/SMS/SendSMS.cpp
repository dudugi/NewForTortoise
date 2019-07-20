#include "StdAfx.h"
#include "KDS-FileMgn.h"
#include "SendSMS.h"
#include <string.h>

CSendSMS::CSendSMS(void)
{
   CString strIniFile = theApp.m_strKdsWorkPath + _T("\\�û��ļ�\\����\\SMSConfig.ini");
   theApp.GetIniKeyValue(SMS_INI_SEG_NAME,SMS_INI_VALUE_NAME_SMSGATEWAY,m_smsGateway,strIniFile);//���Ͷ�������
   theApp.GetIniKeyValue(SMS_INI_SEG_NAME,SMS_INI_VALUE_NAME_YEGATEWAY,m_yeGateway,strIniFile);//�����������
   theApp.GetIniKeyValue(SMS_INI_SEG_NAME,SMS_INI_VALUE_NAME_CONTENT,m_strContent,strIniFile);//Ĭ�Ϸ�����������
}

CSendSMS::~CSendSMS(void)
{
}

//���Ͷ��� 
//Content:_T("���ã�������֤����884192��������ͨ�š�");
BOOL CSendSMS::SendMsg(CString phoneNum,CString Content,SENDMSG_RESULT &resultData)
{
   CString strUrl = m_smsGateway;  
   strUrl.Replace(_T("�����ֻ���"),phoneNum);
   strUrl.Replace(_T("��������"),Content);
   CString strrRet; 
   int ret = m_httpClient.HttpGet(strUrl, _T(""),strrRet);
   if (ret == SUCCESS)
   {
      CString tempStr = strrRet;

      int pos = tempStr.Find('/');
      resultData.strState = tempStr.Left(pos);
      tempStr = tempStr.Right(tempStr.GetLength()-pos-1);      

      pos = tempStr.Find('/');
      CString strSendNum = tempStr.Left(pos);
      strSendNum = strSendNum.Right(strSendNum.GetLength()-strSendNum.Find(':')-1);
      resultData.iSendNum = _ttoi(strSendNum);
      tempStr = tempStr.Right(tempStr.GetLength()-pos-1);

      pos = tempStr.Find('/');
      CString strSendJE = tempStr.Left(pos);
      strSendJE = strSendJE.Right(strSendJE.GetLength()-strSendJE.Find(':')-1);
      resultData.fSendJE = _ttof(strSendJE);
      tempStr = tempStr.Right(tempStr.GetLength()-pos-1);

      pos = tempStr.Find('/');
      CString strYE = tempStr.Left(pos);
      strYE = strYE.Right(strYE.GetLength()-strYE.Find(':')-1);
      resultData.fYE = _ttof(strYE);
      tempStr = tempStr.Right(tempStr.GetLength()-pos-1);

      resultData.strSSID = tempStr.Right(strYE.GetLength()-strYE.Find(':')-1);
      CString infoStr = _T("");
      if (_T("-01") == resultData.strState)
      {
         infoStr = _T("���ŷ���ʧ�ܣ��˻����㣡");
      }else if (_T("-02") == resultData.strState)
      {
         infoStr = _T("���ŷ���ʧ�ܣ�δ��ͨ�ӿ���Ȩ��");
      }else if (_T("-03") == resultData.strState)
      {
         infoStr = _T("���ŷ���ʧ�ܣ��˺��������");
      }else if (_T("-04") == resultData.strState)
      {
         infoStr = _T("���ŷ���ʧ�ܣ������������Ի��߲������ʹ���");
      }else if (_T("-110") == resultData.strState)
      {
         infoStr = _T("���ŷ���ʧ�ܣ�IP�����ƣ�");
      }else if (_T("-12") == resultData.strState)
      {
         infoStr = _T("���ŷ���ʧ�ܣ���������");
      }else if (_T("000") == resultData.strState)
      {
         infoStr.Format(_T("���ŷ��ͳɹ�����������:%d,���ͽ��:%.2f,�˻����:%.2f��"),
            resultData.iSendNum,resultData.fSendJE,resultData.fYE);
      }else
      {
         infoStr = _T("���ŷ���ʧ�ܣ���������");
      }
      resultData.info = infoStr;
      if (_T("000") == resultData.strState)
      {
         return TRUE;
      }
      else
      {
         return FALSE;
      }      
   }else
   {
      resultData.info =  _T("���ŷ���ʧ�ܣ���������");
      return FALSE;
   }
}

//��ȡ���
BOOL CSendSMS::GetAccountBalance(CString &strYE)
{   
   //_T("http://service.winic.org/webservice/public/remoney.asp?uid=�˺�&pwd=����")
   int ret = m_httpClient.HttpGet(m_yeGateway,_T(""),strYE);
   if (ret == SUCCESS)
   {
      if (_T("-02") == strYE)
      {
         strYE = _T("��ȡ�˻����ʧ�ܣ�δ��ͨ�ӿ���Ȩ��");
         return FALSE;
      }else if (_T("-03") == strYE)
      {
         strYE = _T("��ȡ�˻����ʧ�ܣ��˺��������");
         return FALSE;
      }else if (_T("-04") == strYE)
      {
         strYE = _T("��ȡ�˻����ʧ�ܣ������������Ի��߲������ʹ���");
         return FALSE;
      }else if (_T("-110") == strYE)
      {
         strYE = _T("��ȡ�˻����ʧ�ܣ�IP�����ƣ�");
         return FALSE;
      }else if (_T("-12") == strYE)
      {
         strYE = _T("��ȡ�˻����ʧ�ܣ���������");
         return FALSE;
      }
      return TRUE;
   }else
   {
      return FALSE;
   }
}