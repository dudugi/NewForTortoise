#include "StdAfx.h"
#include "KDS-FileMgn.h"
#include "SendSMS.h"
#include <string.h>

CSendSMS::CSendSMS(void)
{
   CString strIniFile = theApp.m_strKdsWorkPath + _T("\\用户文件\\订单\\SMSConfig.ini");
   theApp.GetIniKeyValue(SMS_INI_SEG_NAME,SMS_INI_VALUE_NAME_SMSGATEWAY,m_smsGateway,strIniFile);//发送短信网关
   theApp.GetIniKeyValue(SMS_INI_SEG_NAME,SMS_INI_VALUE_NAME_YEGATEWAY,m_yeGateway,strIniFile);//短信余额网关
   theApp.GetIniKeyValue(SMS_INI_SEG_NAME,SMS_INI_VALUE_NAME_CONTENT,m_strContent,strIniFile);//默认发货短信内容
}

CSendSMS::~CSendSMS(void)
{
}

//发送短信 
//Content:_T("您好，您的验证码是884192【中正云通信】");
BOOL CSendSMS::SendMsg(CString phoneNum,CString Content,SENDMSG_RESULT &resultData)
{
   CString strUrl = m_smsGateway;  
   strUrl.Replace(_T("接收手机号"),phoneNum);
   strUrl.Replace(_T("短信内容"),Content);
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
         infoStr = _T("短信发送失败：账户余额不足！");
      }else if (_T("-02") == resultData.strState)
      {
         infoStr = _T("短信发送失败：未开通接口授权！");
      }else if (_T("-03") == resultData.strState)
      {
         infoStr = _T("短信发送失败：账号密码错误！");
      }else if (_T("-04") == resultData.strState)
      {
         infoStr = _T("短信发送失败：参数个数不对或者参数类型错误！");
      }else if (_T("-110") == resultData.strState)
      {
         infoStr = _T("短信发送失败：IP被限制！");
      }else if (_T("-12") == resultData.strState)
      {
         infoStr = _T("短信发送失败：其他错误！");
      }else if (_T("000") == resultData.strState)
      {
         infoStr.Format(_T("短信发送成功：发送条数:%d,发送金额:%.2f,账户余额:%.2f！"),
            resultData.iSendNum,resultData.fSendJE,resultData.fYE);
      }else
      {
         infoStr = _T("短信发送失败：其他错误！");
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
      resultData.info =  _T("短信发送失败：其他错误！");
      return FALSE;
   }
}

//获取余额
BOOL CSendSMS::GetAccountBalance(CString &strYE)
{   
   //_T("http://service.winic.org/webservice/public/remoney.asp?uid=账号&pwd=密码")
   int ret = m_httpClient.HttpGet(m_yeGateway,_T(""),strYE);
   if (ret == SUCCESS)
   {
      if (_T("-02") == strYE)
      {
         strYE = _T("获取账户余额失败：未开通接口授权！");
         return FALSE;
      }else if (_T("-03") == strYE)
      {
         strYE = _T("获取账户余额失败：账号密码错误！");
         return FALSE;
      }else if (_T("-04") == strYE)
      {
         strYE = _T("获取账户余额失败：参数个数不对或者参数类型错误！");
         return FALSE;
      }else if (_T("-110") == strYE)
      {
         strYE = _T("获取账户余额失败：IP被限制！");
         return FALSE;
      }else if (_T("-12") == strYE)
      {
         strYE = _T("获取账户余额失败：其他错误！");
         return FALSE;
      }
      return TRUE;
   }else
   {
      return FALSE;
   }
}