#pragma once

#define ENC_JIANGE_FUHAO (_T("{[;;]}"))  //��������֮�����ķ��� 

class CLDK;
class CMyEncrypt
{
public:
	CMyEncrypt();
	virtual ~CMyEncrypt();
public:
   //���ܣ����ַ���ͨ�������ܣ�����ת��Ϊʮ�������ַ������ 
   BOOL Encrypt(__in CLDK *pLdk,__in CString strOrc,__out CString &strDesc);

   //���ܣ���ʮ�������ַ���ͨ�������ܣ�����ת��Ϊ�������ַ������ 
   BOOL Decrypt(__in CLDK *pLdk,__in CString strOrc,__out CString &strDesc);

   //PDM����ʹ��
   BOOL EncryptString(__in CLDK *pLdk,__in CString strcModeData, __in CString strBeginTime,__in CString strcTime,__in CString strcPerson,
      __in int iClientNum,__out CString &strData1,__out CString &strData2,__out CString &strData3,__out CString &strData4);

   //PDM����ʹ��
   BOOL DecryptString(__in CLDK *pLdk,__in CString &strData1,__in CString &strData2,__in CString &strData3,__in CString &strData4
      ,__out CString &strcModeData, __out CString &strBeginTime,__out CString &strcTime,__out CString &strcPerson,__out int &iClientNum);
};