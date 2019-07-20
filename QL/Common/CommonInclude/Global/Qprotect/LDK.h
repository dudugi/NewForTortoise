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

//加密狗内存地址位置 数字*16为实际的寻址空间位置，rw为读写内存用于记录使用的情况 ro为只读内存用于设置允许时间和次数
// time表示记录的时间，use表示记录使用的次数，在一个地方使用同一个后缀数字的地址MEMORY_RW_TIME1 MEMORY_RO_TIME1。。。
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

//存放固定的标志，如果读取错误，则判断出错
#define MEMORY_RO_TEXT11				 39  //true
#define MEMORY_RO_TEXT12				 41  //false
#define MEMORY_RO_TEXT13				 43  //error
#define MEMORY_RO_TEXT14				 45  //checkin
#define MEMORY_RO_TEXT15				 47  //checkout
#define MEMORY_RO_TEXT16				 49  //turnon
#define MEMORY_RO_TEXT17				 51  //turnoff
#define MEMORY_RO_TEXT18				 53  //trust
#define MEMORY_RO_TEXT19				 56  //chect



//存放固定的标志，如果读取错误，则判断出错
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
	BOOL					EncryptRightD(double *pData,char *pchar)/*正常使用加密函数 */;//成对使用pdata能够保证数据一致，单独使用，pdata数据变化
	BOOL					DecryptRightD(double *pData,char *pchar)/*正常使用加密函数 */;
	BOOL					DecryptRightI(int *pData,char *pchar)/*正常使用解密函数 */;
	BOOL					EncryptRightI(int *pData,char *pchar)/*正常使用加密函数 */;
	CTime					GetTime();
	BOOL					DecryptErrorD(double *pData,char *pchar)/*异常使用解密函数 */;//成对使用pdata能够保证数据一致，单独使用，pdata数据变化
	BOOL					EncryptErrorD(double *pData,char *pchar)/*异常使用加密函数 */;
	BOOL					EncryptErrorI(int *pData,char *pchar)/*异常使用加密函数 */;
	BOOL					DecryptErrorI(int *pData,char *pchar)/*异常使用解密函数 */;
	int						ReadKey(int offset,CString& sData);/*读加密狗内存 */;
	int						ReadKey_RO(int offset,CString& sData);/*读加密狗只读区域内存 */;
	int						WriteKey(int offset,CString sData);/*写加密狗内存 */;
	CTime					StringToTime(CString sData);
	BOOL					ReadKeyFlag1(int nIndex);//nIndex=12,13,15,17,19时返回错误则代表正确读取了加密狗的标志；
	BOOL					ReadKeyFlag2(int nIndex);//nIndex=12,13,15,17,19时返回错误则代表正确读取了加密狗的标志；
	BOOL					ReadKeyFlag3(int nIndex);//nIndex=12,13,15,17,19时返回错误则代表正确读取了加密狗的标志；


	int						WriteRWData1(int nMemPos);//目前只是干扰作用，写加密狗的读写存储区；
	int						WriteRWData2(int nMemPos);//目前只是干扰作用，写加密狗的读写存储区；
	int						WriteRWData3(int nMemPos);//目前只是干扰作用，写加密狗的读写存储区；
	int						WriteRWData4(int nMemPos);//目前只是干扰作用，写加密狗的读写存储区；
	int						WriteRWData5(int nMemPos);//目前只是干扰作用，写加密狗的读写存储区；
	int						WriteRWData6(int nMemPos);//目前只是干扰作用，写加密狗的读写存储区；

	int						ReadRWData1(int nMemPos);//读加密狗的读写存储区；输入参数无作用，读MEMORY_RW_TEXT1实际读取“ROW39”，返回1；
	int						ReadRWData2(int nMemPos);//读加密狗的读写存储区；输入参数无作用，读MEMORY_RW_TEXT2实际读取“ROW41”，返回2；
	int						ReadRWData3(int nMemPos);//读加密狗的读写存储区；输入参数无作用，读MEMORY_RW_TEXT3实际读取“ROW43”，返回3；
	int						ReadRWData4(int nMemPos);//读加密狗的读写存储区；输入参数无作用，读MEMORY_RW_TEXT4实际读取“ROW45”，返回4；
	int						ReadRWData5(int nMemPos);//读加密狗的读写存储区；输入参数无作用，读MEMORY_RW_TEXT5实际读取“ROW47”，返回5；
	int						ReadRWData6(int nMemPos);//读加密狗的读写存储区；输入参数无作用，读MEMORY_RW_TEXT6实际读取“ROW49”，返回6；


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
