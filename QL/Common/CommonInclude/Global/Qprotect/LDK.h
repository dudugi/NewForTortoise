// LDK.h: interface for the LDK class.
//
//////////////////////////////////////////////////////////////////////
#include "hasp_api.h"
#if !defined(AFX_LDK_H__AD762456_1F7E_4E1C_9D10_2610FE059CD8__INCLUDED_)
#define AFX_LDK_H__AD762456_1F7E_4E1C_9D10_2610FE059CD8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// #include "sentinelkeyslicense.h"//

#define HASP_SHELL				 100
#define HASP_BASEVERSION         110
#define HASP_PREMIUMVERSION      120 
#define HASP_ULTIMATEVERSION     130
#define HASP_3DVERSION			 300
#define HASP_PLMVERSION			 350
#define HASP_ERPVERSION			 400

#define HASP_DECRYPTID1          151
#define HASP_DECRYPTID2          152
#define HASP_DECRYPTID3          153
#define HASP_DECRYPTID4          154
#define HASP_DECRYPTID5          155
#define HASP_DECRYPTID6          156
#define HASP_DECRYPTID7          157
#define HASP_DECRYPTID8          158
#define HASP_DECRYPTID9          159
#define HASP_DECRYPTID10         160
#define HASP_DECRYPTID11         161
#define HASP_DECRYPTID12         162

#define HASP_NEIBUUSE            230

//���ܹ��ڴ��ַλ�� ����*16Ϊʵ�ʵ�Ѱַ�ռ�λ�ã�rwΪ��д�ڴ����ڼ�¼ʹ�õ���� roΪֻ���ڴ�������������ʱ��ʹ���
// time��ʾ��¼��ʱ�䣬use��ʾ��¼ʹ�õĴ�������һ���ط�ʹ��ͬһ����׺���ֵĵ�ַMEMORY_RW_TIME1 MEMORY_RO_TIME1������
#define MEMORY_RW_TIME1					 3     //EdittextDlg  
#define MEMORY_RW_TIME2					 6     //   PBDlg
#define MEMORY_RW_TIME3					 9     //ExcelTemplateSetDlg  SamdwichColorDlg
#define MEMORY_RW_TIME4					 12    //SelArcDlg FsDisTextDlg
#define MEMORY_RW_TIME5					 15    //FsMatNewDlg  SetSystemDlg
#define MEMORY_RW_TIME6					 18    //FsPieceView
#define MEMORY_RW_TIME7					 21    //FsSetGGDlg
#define MEMORY_RW_TIME8					 24    //KDSDoc
#define MEMORY_RW_TIME9					 27    //MeasreBillDlg
#define MEMORY_RW_TIME10				 30    //NWDDlg
#define MEMORY_RW_TIME11				 33    //NWDLZ
#define MEMORY_RW_TIME12				 36    //EnterPcsDlgpinyon



#define MEMORY_RO_TIME1					 3
#define MEMORY_RO_TIME2					 6
#define MEMORY_RO_TIME3					 9
#define MEMORY_RO_TIME4					 12
#define MEMORY_RO_TIME5					 15
#define MEMORY_RO_TIME6					 18
#define MEMORY_RO_TIME7					 21
#define MEMORY_RO_TIME8					 24
#define MEMORY_RO_TIME9					 27
#define MEMORY_RO_TIME10				 30
#define MEMORY_RO_TIME11				 33
#define MEMORY_RO_TIME12				 36




#define MEMORY_RW_USE1					 5
#define MEMORY_RW_USE2					 7
#define MEMORY_RW_USE3					 11
#define MEMORY_RW_USE4					 13
#define MEMORY_RW_USE5					 17
#define MEMORY_RW_USE6					 19
#define MEMORY_RW_USE7					 23
#define MEMORY_RW_USE8					 25
#define MEMORY_RW_USE9					 28
#define MEMORY_RW_USE10					 32
#define MEMORY_RW_USE11				     35
#define MEMORY_RW_USE12				     37




#define MEMORY_RO_USE1					 5
#define MEMORY_RO_USE2					 7
#define MEMORY_RO_USE3					 11
#define MEMORY_RO_USE4					 13
#define MEMORY_RO_USE5					 17
#define MEMORY_RO_USE6					 19
#define MEMORY_RO_USE7					 23
#define MEMORY_RO_USE8					 25
#define MEMORY_RO_USE9					 28
#define MEMORY_RO_USE10					 32
#define MEMORY_RO_USE11				     35
#define MEMORY_RO_USE12				     37

//��Ź̶��ı�־�������ȡ�������жϳ���
#define MEMORY_RO_TEXT11				 39  //true
#define MEMORY_RO_TEXT12				 41  //false
#define MEMORY_RO_TEXT13				 43  //error
#define MEMORY_RO_TEXT14				 45  //checkin
#define MEMORY_RO_TEXT15				 47  //checkout
#define MEMORY_RO_TEXT16				 49  //turnon
#define MEMORY_RO_TEXT17				 51  //turnoff
#define MEMORY_RO_TEXT18				 53  //trust
#define MEMORY_RO_TEXT19				 56  //chect



//��Ź̶��ı�־�������ȡ�������жϳ���
#define MEMORY_RW_TEXT1				 39  //ROW39
#define MEMORY_RW_TEXT2				 41  //ROW41
#define MEMORY_RW_TEXT3				 43  //ROW43
#define MEMORY_RW_TEXT4				 45  //ROW45
#define MEMORY_RW_TEXT5				 47  //ROW47
#define MEMORY_RW_TEXT6				 49  //ROW49


#include <map>
typedef std::map<hasp_status_t, const char*> StatusMap;


class CLDK : public CObject  
{
public:
							CLDK();
	virtual					~CLDK();
	BOOL                    EncryptString(char* inBuffer, int inLen);
	BOOL                    DecryptString(char* inBuffer, int inLen);
	BOOL                    GetHaspTime(unsigned int& year , unsigned int& month, unsigned int& day , unsigned int& hour, unsigned int& min , unsigned int& sec);
	CString					GetKeyInfo();


	BOOL                    GetHaspInfo(char** info);

	BOOL					GetHaspKey(int nFeatureID);
	hasp_status_t			DelHaspKey();
	CString					GetErrorStr();
	BOOL					EncryptRightD(double *pData,char *pchar)/*����ʹ�ü��ܺ��� */;//�ɶ�ʹ��pdata�ܹ���֤����һ�£�����ʹ�ã�pdata���ݱ仯
	BOOL					DecryptRightD(double *pData,char *pchar)/*����ʹ�ü��ܺ��� */;
	BOOL					DecryptRightI(int *pData,char *pchar)/*����ʹ�ý��ܺ��� */;
	BOOL					EncryptRightI(int *pData,char *pchar)/*����ʹ�ü��ܺ��� */;
	CTime					GetTime();
	BOOL					DecryptErrorD(double *pData,char *pchar)/*�쳣ʹ�ý��ܺ��� */;//�ɶ�ʹ��pdata�ܹ���֤����һ�£�����ʹ�ã�pdata���ݱ仯
	BOOL					EncryptErrorD(double *pData,char *pchar)/*�쳣ʹ�ü��ܺ��� */;
	BOOL					EncryptErrorI(int *pData,char *pchar)/*�쳣ʹ�ü��ܺ��� */;
	BOOL					DecryptErrorI(int *pData,char *pchar)/*�쳣ʹ�ý��ܺ��� */;
	int						ReadKey(int offset,CString& sData);/*�����ܹ��ڴ� */;
	int						ReadKey_RO(int offset,CString& sData);/*�����ܹ�ֻ�������ڴ� */;
	int						WriteKey(int offset,CString sData);/*д���ܹ��ڴ� */;
	CTime					StringToTime(CString sData);
	BOOL					ReadKeyFlag1(int nIndex);//nIndex=12,13,15,17,19ʱ���ش����������ȷ��ȡ�˼��ܹ��ı�־��
	BOOL					ReadKeyFlag2(int nIndex);//nIndex=12,13,15,17,19ʱ���ش����������ȷ��ȡ�˼��ܹ��ı�־��
	BOOL					ReadKeyFlag3(int nIndex);//nIndex=12,13,15,17,19ʱ���ش����������ȷ��ȡ�˼��ܹ��ı�־��


	int						WriteRWData1(int nMemPos);//Ŀǰֻ�Ǹ������ã�д���ܹ��Ķ�д�洢����
	int						WriteRWData2(int nMemPos);//Ŀǰֻ�Ǹ������ã�д���ܹ��Ķ�д�洢����
	int						WriteRWData3(int nMemPos);//Ŀǰֻ�Ǹ������ã�д���ܹ��Ķ�д�洢����
	int						WriteRWData4(int nMemPos);//Ŀǰֻ�Ǹ������ã�д���ܹ��Ķ�д�洢����
	int						WriteRWData5(int nMemPos);//Ŀǰֻ�Ǹ������ã�д���ܹ��Ķ�д�洢����
	int						WriteRWData6(int nMemPos);//Ŀǰֻ�Ǹ������ã�д���ܹ��Ķ�д�洢����

	int						ReadRWData1(int nMemPos);//�����ܹ��Ķ�д�洢����������������ã���MEMORY_RW_TEXT1ʵ�ʶ�ȡ��ROW39��������1��
	int						ReadRWData2(int nMemPos);//�����ܹ��Ķ�д�洢����������������ã���MEMORY_RW_TEXT2ʵ�ʶ�ȡ��ROW41��������2��
	int						ReadRWData3(int nMemPos);//�����ܹ��Ķ�д�洢����������������ã���MEMORY_RW_TEXT3ʵ�ʶ�ȡ��ROW43��������3��
	int						ReadRWData4(int nMemPos);//�����ܹ��Ķ�д�洢����������������ã���MEMORY_RW_TEXT4ʵ�ʶ�ȡ��ROW45��������4��
	int						ReadRWData5(int nMemPos);//�����ܹ��Ķ�д�洢����������������ã���MEMORY_RW_TEXT5ʵ�ʶ�ȡ��ROW47��������5��
	int						ReadRWData6(int nMemPos);//�����ܹ��Ķ�д�洢����������������ã���MEMORY_RW_TEXT6ʵ�ʶ�ȡ��ROW49��������6��


// 	int                     CheckDllList();
// 	int                     DetectEmulator();
	int						IsOutTime( CString& strKdsworkPath ,CString& strAppPath ,int& nOuttime );
	int                     CheckData(CString& strKdsworkPath ,CString& strAppPath ,int& nOuttime, int& status);
	int                     CheckData1_3(CString& strKdsworkPath ,CString& strAppPath ,int& nOuttime, int& status );
	int                     CheckData9_12(CString& strKdsworkPath ,CString& strAppPath ,int& nOuttime, int& status  );
	int						CheckDataOnTime( int& status );

	void					WriteOutTimeFile( int nType, CString& strAppPath  );

	hasp_handle_t			m_Key;
	StatusMap				m_errorMap;
	hasp_status_t			m_errorStatus;

	hasp_status_t			m_Status;
    

};

#endif // !defined(AFX_LDK_H__AD762456_1F7E_4E1C_9D10_2610FE059CD8__INCLUDED_)
