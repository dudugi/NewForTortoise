#pragma once

#define ENC_JIANGE_FUHAO (_T("{[;;]}"))  //加密数据之间间隔的符号 

class CLDK;
class CMyEncrypt
{
public:
	CMyEncrypt();
	virtual ~CMyEncrypt();
public:
   //加密，把字符串通过狗加密，并且转换为十六进制字符串输出 
   BOOL Encrypt(__in CLDK *pLdk,__in CString strOrc,__out CString &strDesc);

   //解密，把十六进制字符串通过狗解密，并且转换为正常的字符串输出 
   BOOL Decrypt(__in CLDK *pLdk,__in CString strOrc,__out CString &strDesc);

   //PDM加密使用
   BOOL EncryptString(__in CLDK *pLdk,__in CString strcModeData, __in CString strBeginTime,__in CString strcTime,__in CString strcPerson,
      __in int iClientNum,__out CString &strData1,__out CString &strData2,__out CString &strData3,__out CString &strData4);

   //PDM解密使用
   BOOL DecryptString(__in CLDK *pLdk,__in CString &strData1,__in CString &strData2,__in CString &strData3,__in CString &strData4
      ,__out CString &strcModeData, __out CString &strBeginTime,__out CString &strcTime,__out CString &strcPerson,__out int &iClientNum);
};