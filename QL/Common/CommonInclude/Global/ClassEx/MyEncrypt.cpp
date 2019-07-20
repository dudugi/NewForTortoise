#include "StdAfx.h"
#include "MyEncrypt.h"
#include "LDK.h"
#include "rnstring.h"

CMyEncrypt::CMyEncrypt()
{
}


CMyEncrypt::~CMyEncrypt()
{
}

//加密，把字符串通过狗加密，并且转换为十六进制字符串输出 
BOOL CMyEncrypt::Encrypt(__in CLDK *pLdk,__in CString strOrc,__out CString &strDesc)
{
   if (!pLdk)
   {
      return FALSE;
   } 
   CStringA valueCSA = RnString::WChar2Char(strOrc.GetBuffer());
   strOrc.ReleaseBuffer();
   int nLen = valueCSA.GetLength();
   char *pInOutBuffer = new char[nLen+1];
   strcpy(pInOutBuffer,valueCSA.GetBuffer());
   pInOutBuffer[nLen] = '\0';
   valueCSA.ReleaseBuffer();
   if(!pLdk->EncryptString(pInOutBuffer , nLen ))
   {
      delete []pInOutBuffer;
      return FALSE;
   }
   CString strTmp;
   for (int i=0;i<nLen;++i)
   {
      strTmp.Format(_T("%02X"),(unsigned char)pInOutBuffer[i]);
      strDesc += strTmp;
   }  
   delete []pInOutBuffer;
   return TRUE;
}

//解密，把十六进制字符串通过狗解密，并且转换为正常的字符串输出 
BOOL CMyEncrypt::Decrypt(__in CLDK *pLdk,__in CString strOrc,__out CString &strDesc)
{
   if (!pLdk)
   {
      return FALSE;
   }
   int nLen = strOrc.GetLength()/2;
   int tempChar =0;
   char *pInOutBuffer = new char[nLen+1];
   int i=0;
   for(;i<nLen;++i)
   {
      CString tempStr = strOrc.Mid(i*2,2);      
      CStringA tempStrCSA = RnString::WChar2Char(tempStr.GetBuffer());
      tempStr.ReleaseBuffer();      
      sscanf(tempStrCSA.GetBuffer(), "%x", &tempChar);
      tempStrCSA.ReleaseBuffer();
      pInOutBuffer[i] = (char)tempChar;
   } 

   pInOutBuffer[nLen] = '\0';
   if(!pLdk->DecryptString(pInOutBuffer , nLen ))
   {     
      delete []pInOutBuffer;    
      return FALSE;
   }  
   strDesc = RnString::Char2WChar(pInOutBuffer); 
   delete []pInOutBuffer;   
   return TRUE;
}

BOOL CMyEncrypt::EncryptString(__in CLDK *pLdk,__in CString strcModeData, __in CString strBeginTime,__in CString strcTime,__in CString strcPerson,
  __in int iClientNum,__out CString &strData1,__out CString &strData2,__out CString &strData3,__out CString &strData4)
{
   CString strClientNum;
   strClientNum.Format(_T("%d"),iClientNum);
   CString strOrcValue = strcModeData+ENC_JIANGE_FUHAO+strBeginTime+ENC_JIANGE_FUHAO+strcTime+ENC_JIANGE_FUHAO+strcPerson+ENC_JIANGE_FUHAO+strClientNum; 
   CString strEncData;
   if(!Encrypt(pLdk,strOrcValue,strEncData))
   {
      return FALSE;
   }
   int nLen = strEncData.GetLength();
   int nLenPer = nLen/4;
   int nLenLast = nLenPer;
   if (nLen%4>0)
   {
      nLenLast += nLen%4;
   }
   //1+4+3+2
   strData1 = strEncData.Left(nLenPer);
   strData4 = strEncData.Mid(nLenPer,nLenPer);
   strData3 = strEncData.Mid(nLenPer*2,nLenPer);
   strData2 = strEncData.Right(nLenLast);
   return TRUE;
}

BOOL CMyEncrypt::DecryptString(__in CLDK *pLdk,__in CString &strData1,__in CString &strData2,__in CString &strData3,__in CString &strData4
   ,__out CString &strcModeData, __out CString &strBeginTime,__out CString &strcTime,__out CString &strcPerson,__out int &iClientNum)
{
   if (!pLdk)
   {
      return FALSE;
   }
   CString strOrcValue = strData1+strData4+strData3+strData2;//1+4+3+2   
   CString strDecrypt;
   if(!Decrypt(pLdk,strOrcValue,strDecrypt))
   {
      return FALSE;
   }
   CString strTmp = strDecrypt;

   //功能模块
   int iPos = strTmp.Find(ENC_JIANGE_FUHAO);
   if (-1 == iPos)
   {
      return FALSE;
   }
   strcModeData = strTmp.Left(iPos);

   //开始时间
   CString strFuhao = ENC_JIANGE_FUHAO;
   int lenFuhao = strFuhao.GetLength();
   strTmp = strTmp.Right(strTmp.GetLength()-iPos-lenFuhao);
   iPos = strTmp.Find(ENC_JIANGE_FUHAO);
   if (-1 == iPos)
   {
      return FALSE;
   }
   strBeginTime= strTmp.Left(iPos);

   //到期时间
   strTmp = strTmp.Right(strTmp.GetLength()-iPos-lenFuhao);
   iPos = strTmp.Find(ENC_JIANGE_FUHAO);
   if (-1 == iPos)
   {
      return FALSE;
   }
   strcTime= strTmp.Left(iPos);

   iClientNum = 0;
   //身份信息
   strTmp = strTmp.Right(strTmp.GetLength()-iPos-lenFuhao);
   iPos = strTmp.Find(ENC_JIANGE_FUHAO);
   if (-1 == iPos)
   {
      strcPerson = strTmp;
      return TRUE;
   }
   strcPerson = strTmp.Left(iPos);
   strTmp = strTmp.Right(strTmp.GetLength()-iPos-lenFuhao);
   iPos = strTmp.Find(ENC_JIANGE_FUHAO);
   if (-1 == iPos)
   {
      //客户端数量
      iClientNum = _ttoi(strTmp);
      return TRUE;
   }
   //客户端数量
   iClientNum = _ttoi(strTmp.Left(iPos));
   strTmp = strTmp.Right(strTmp.GetLength()-iPos-lenFuhao);
   return TRUE;
}
   
