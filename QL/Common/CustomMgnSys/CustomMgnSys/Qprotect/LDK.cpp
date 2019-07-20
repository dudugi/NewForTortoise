// SFNT.cpp: implementation of the CLDK class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "CustomMgnSys.h"

#include "LDK.h"
// #include "Qprotect/Sntl_CheckDLL.h"
// #include "Qprotect/emulatordetect.h"
// #include "Qprotect/sntl_licgen.h"

#include "atlconv.h"

#define   RWDATALEN     8


//#define NETDOG

/* HASP vendor code for demo keys */
const unsigned char vendorCode[] =
"F3c6wB+McAHggyVF0zlkHABqdkpRl20chkCU6A9ZL9YgGYn1vQgBYfwWImvvLs11+6wjEHtLFWLWnKYZ"
"YXpOWiKHNhxzyfkaLeyqC6rUG51bwqfMrv8JNED9B3zgeVRZ709PWs595QC0h8QBco5mZNWfk/A2EzsJ"
"yccey4cFBwJX85kVILgBrzeDzP2E/Zkmj51w847Fl7Z+vwIU7oI3hShDDOrDBFgd3xqhpKC12IfbTKKm"
"fMp9Fh02+A2MmTrfoS1EBOlpNSc/Iato8E9PRhuA0CmkViRBc/Exve0/e70umEwX2aXmk0GVhNo8sdwe"
"JjUz3q8PdUvGG7awy+jsTGRjytBcTgh6kqYmRo2PEanfEBnvbz4c0B1V8eJFfCrqhNbXXX7w2LjF4PQd"
"QCFdq2Yo9tDvqjOTLv7/V/Y4GHw9atLtSl5gemo+AyM9o0779uumsdpryH7F4D67xe+6subTtZswgCBE"
"U1PpBRERsKrWvScEaIY+QUUbrKQXZGV7gZiVzsqP2CPf1w+YANm6HF+fTf5qaa9ieAoA0u03HNcdRyG9"
"qz/3Nz4LAFz9h0zajzLCABa33i+RgSj8OhPyxg//cP/SGdxhzXWfpXS73X/zxJdyAoxeNLE3JiuEz9Mx"
"sR+4W7M1k46Ga9dlzIzuz0oCT2kdxZaxouwEP5Z2QK1yoZ+eW4Z08cKRfge5zgRNsGrOwHQWFddfLg+i"
"EDzIEpINS4TobDVbTlWMV7f1plkTGEoQahYs90PD7Rnz0HJ0xasHae6yRrJyLd3t5cyF1lA2W6TLrHSB"
"vcKo6tLcJQY89jpsScfUG/Id1ze7+Y9cnowoSqYXJ3zgur6JrumWD7uRnC6QYbxb6LY+HjCQFwg/unoP"
"eZOd7yyiSz86aXRPxTiThSQ/K8pbAkDLAFRlDAAVZCrr3ZLahl6/LUoyLxJj4K//8Jx1pHuY9YWJsheH"
"IK6kmVvr6QbczLU/7Qadlw==";

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLDK::CLDK()
{


	m_errorMap.insert(StatusMap::value_type(HASP_STATUS_OK, ""));
	m_errorMap.insert(StatusMap::value_type(HASP_MEM_RANGE,"提示代码：H-2001" ));//"Invalid memory address"
	m_errorMap.insert(StatusMap::value_type(HASP_INV_PROGNUM_OPT,"提示代码：H-3052" ));//"Unknown/invalid Feature ID option"
	m_errorMap.insert(StatusMap::value_type(HASP_INSUF_MEM,"提示代码：H-0765" ));//"Memory allocation failed"
	m_errorMap.insert(StatusMap::value_type(HASP_TMOF,"提示代码：H-9532" ));//"Too many open Features"
	m_errorMap.insert(StatusMap::value_type(HASP_ACCESS_DENIED,"提示代码：H-5298" ));//"Feature access denied"
	m_errorMap.insert(StatusMap::value_type(HASP_INCOMPAT_FEATURE,"提示代码：H-3758" ));//"Incompatible Feature"
	m_errorMap.insert(StatusMap::value_type(HASP_HASP_NOT_FOUND,"提示代码：H-5688"));// "HASP Key not found"
	m_errorMap.insert(StatusMap::value_type(HASP_TOO_SHORT,"提示代码：H-7541" ));//"Encryption/decryption length too short"
	m_errorMap.insert(StatusMap::value_type(HASP_INV_HND,"提示代码：H-7791" ));//"Invalid handle"
	m_errorMap.insert(StatusMap::value_type(HASP_INV_FILEID,"提示代码：H-8016" ));//"Invalid file ID / memory descriptor"
	m_errorMap.insert(StatusMap::value_type(HASP_OLD_DRIVER,"提示代码：H-6879" ));//"Driver or support daemon version too old"
	m_errorMap.insert(StatusMap::value_type(HASP_OLD_DRIVER,"提示代码：H-5628" ));//"Driver or support daemon version too old"
	m_errorMap.insert(StatusMap::value_type(HASP_OLD_DRIVER,"提示代码：H-8524" ));//"Driver or support daemon version too old"
	m_errorMap.insert(StatusMap::value_type(HASP_NO_TIME,"提示代码：H-6785" ));//"Real time support not available"
	m_errorMap.insert(StatusMap::value_type(HASP_SYS_ERR,"提示代码：H-7014" ));//"Generic error from host system call"
	m_errorMap.insert(StatusMap::value_type(HASP_NO_DRIVER,"提示代码：H-6853" ));//"HASP driver not found"
	m_errorMap.insert(StatusMap::value_type(HASP_INV_FORMAT,"提示代码：H-2586" ));//"Unrecognized info format"
	m_errorMap.insert(StatusMap::value_type(HASP_REQ_NOT_SUPP,"提示代码：H-0285" ));//"Request not supported"
	m_errorMap.insert(StatusMap::value_type(HASP_INV_UPDATE_OBJ,"提示代码：H-1423")); //"Invalid update object"
	m_errorMap.insert(StatusMap::value_type(HASP_KEYID_NOT_FOUND,"提示代码：H-3586"));//"Key with specified ID was not found"
	m_errorMap.insert(StatusMap::value_type(HASP_INV_UPDATE_DATA,"提示代码：H-4652" ));//"Update data consistency check failed"
	m_errorMap.insert(StatusMap::value_type(HASP_INV_UPDATE_NOTSUPP, "提示代码：H-8543"));//"Update not supported by this key"
	m_errorMap.insert(StatusMap::value_type(HASP_INV_UPDATE_CNTR,"提示代码：H-7689"));// "Update counter mismatch"
	m_errorMap.insert(StatusMap::value_type(HASP_INV_VCODE,"提示代码：H-6587" ));//"Invalid Vendor Code"
	m_errorMap.insert(StatusMap::value_type(HASP_ENC_NOT_SUPP,"提示代码：H-5689")); //"Requested encryption algorithm not supported"
	m_errorMap.insert(StatusMap::value_type(HASP_INV_TIME,"提示代码：H-4569")); //"Invalid date/time"
	m_errorMap.insert(StatusMap::value_type(HASP_NO_BATTERY_POWER,"提示代码：H-2385" ));//"Clock has no power"
	m_errorMap.insert(StatusMap::value_type(HASP_NO_ACK_SPACE,"提示代码：H-8721" ));//"Update requested ack., but no area to return it"
	m_errorMap.insert(StatusMap::value_type(HASP_TS_DETECTED,"提示代码：H-1254" ));//"Terminal services (remote terminal) detected"
	m_errorMap.insert(StatusMap::value_type(HASP_FEATURE_TYPE_NOT_IMPL,"提示代码：H-8546" ));//"Feature type not implemented"
	m_errorMap.insert(StatusMap::value_type(HASP_UNKNOWN_ALG,"提示代码：H-4237"));// "Unknown algorithm"
	m_errorMap.insert(StatusMap::value_type(HASP_INV_SIG,"提示代码：H-8567" ));//"Signature check failed"
	m_errorMap.insert(StatusMap::value_type(HASP_FEATURE_NOT_FOUND,"提示代码：H-7589"));//"Feature not found"
	m_errorMap.insert(StatusMap::value_type(HASP_NO_LOG,"提示代码：H-1358"  ));//"Trace log is not enabled"
	m_errorMap.insert(StatusMap::value_type(HASP_LOCAL_COMM_ERR, "提示代码：H-4785" ));//"Communication error between application and local LM"
	m_errorMap.insert(StatusMap::value_type(HASP_UNKNOWN_VCODE,"提示代码：H-3587" ));//"Vendor Code not recognized by API)" 
	m_errorMap.insert(StatusMap::value_type(HASP_INV_SPEC, "提示代码：H-6689" ));//"Invalid XML spec"
	m_errorMap.insert(StatusMap::value_type(HASP_INV_SCOPE, "提示代码：H-7510" ));//"Invalid XML scope"
	m_errorMap.insert(StatusMap::value_type(HASP_TOO_MANY_KEYS,"提示代码：H-0025" ));//"Too many keys connected"

	m_errorMap.insert(StatusMap::value_type(HASP_TOO_MANY_USERS, "提示代码：H-7505" ));//"Too many users"
	m_errorMap.insert(StatusMap::value_type(HASP_BROKEN_SESSION,"提示代码：H-3205"  ));//"Broken session"
	m_errorMap.insert(StatusMap::value_type(HASP_REMOTE_COMM_ERR, "提示代码：H-0245" ));//"Communication error between local and remote License Manager"
	m_errorMap.insert(StatusMap::value_type(HASP_FEATURE_EXPIRED, "提示代码：H-1285" ));//"The feature is expired"
	m_errorMap.insert(StatusMap::value_type(HASP_OLD_LM,"提示代码：H-2345"  ));//"HASP LM version is too old"
	m_errorMap.insert(StatusMap::value_type(HASP_DEVICE_ERR,"提示代码：H-1687"  ));//"HASP SL secure storage I/O error or USB request error"
	m_errorMap.insert(StatusMap::value_type(HASP_UPDATE_BLOCKED, "提示代码：H-4568" ));//"Update installation not allowed"
	m_errorMap.insert(StatusMap::value_type(HASP_TIME_ERR,"提示代码：H-4396"  ));//"System time has been tampered"
	m_errorMap.insert(StatusMap::value_type(HASP_SCHAN_ERR, "提示代码：H-6685" ));//"Secure channel communication error"
	m_errorMap.insert(StatusMap::value_type(HASP_STORAGE_CORRUPT,"提示代码：H-9586"  ));//"Secure storage contains garbage"
	m_errorMap.insert(StatusMap::value_type(HASP_NO_VLIB,"提示代码：H-3358"  ));//"Vendor lib cannot be found"
	m_errorMap.insert(StatusMap::value_type(HASP_INV_VLIB,"提示代码：H-7523"  ));//"Vendor lib cannot be loaded"
	m_errorMap.insert(StatusMap::value_type(HASP_SCOPE_RESULTS_EMPTY,"提示代码：H-1145"  ));//"No feature matching scope found"
	m_errorMap.insert(StatusMap::value_type(HASP_VM_DETECTED, "提示代码：H-8726" ));//"Virtual machine detected"
	m_errorMap.insert(StatusMap::value_type(HASP_HARDWARE_MODIFIED,"提示代码：H-8832"  ));//"HASP update incompatible with this hardware; HASP key is locked to other hardware"
	m_errorMap.insert(StatusMap::value_type(HASP_USER_DENIED,"提示代码：H-3250"  ));//"Login denied because of user restrictions"
	m_errorMap.insert(StatusMap::value_type(HASP_UPDATE_TOO_OLD,"提示代码：H-0359"  ));//"Update was already installed"
	m_errorMap.insert(StatusMap::value_type(HASP_UPDATE_TOO_NEW,"提示代码：H-8539"  ));//"Another update must be installed first"
	m_errorMap.insert(StatusMap::value_type(HASP_OLD_VLIB,"提示代码：H-8805"  ));//"Vendor lib is too old"
	m_errorMap.insert(StatusMap::value_type(HASP_UPLOAD_ERROR,"提示代码：H-6807"  ));//"Upload via ACC failed, e.g. because of illegal format"

	m_errorMap.insert(StatusMap::value_type(HASP_INV_RECIPIENT,"提示代码：H-7706"  ));//"Invalid XML \"recipient\" parameter"
	m_errorMap.insert(StatusMap::value_type(HASP_INV_DETACH_ACTION,"提示代码：H-8003"  ));//"Invalid XML \"action\" parameter"
	m_errorMap.insert(StatusMap::value_type(HASP_TOO_MANY_PRODUCTS,"提示代码：H-3334"  ));//"Scope does not specify a unique Product"
	m_errorMap.insert(StatusMap::value_type(HASP_INV_PRODUCT,"提示代码：H-4468"  ));//"Invalid Product information"
	m_errorMap.insert(StatusMap::value_type(HASP_UNKNOWN_RECIPIENT,"提示代码：H-6638"  ));//"Unknown Recipient; update can only be applied to the Recipient specified in hasp_detach(), and not to this computer"
	m_errorMap.insert(StatusMap::value_type(HASP_INV_DURATION,"提示代码：H-8552"  ));//"Invalid duration specified"
	m_errorMap.insert(StatusMap::value_type(HASP_CLONE_DETECTED,"提示代码：H-6687"  ));//"Cloned HASP SL secure storage detected"

	m_errorMap.insert(StatusMap::value_type(HASP_NO_API_DYLIB,"提示代码：H-8639"  ));//"A required API dynamic library was not found"
	m_errorMap.insert(StatusMap::value_type(HASP_INV_API_DYLIB,"提示代码：H-7563"  ));//"The found and assigned API dynamic library could not verified"

	m_errorMap.insert(StatusMap::value_type(HASP_INVALID_OBJECT,"提示代码：H-9935"  ));//"Object incorrectly initialized"
	m_errorMap.insert(StatusMap::value_type(HASP_INVALID_PARAMETER,"提示代码：H-8806"  ));//"Invalid function parameter"
	m_errorMap.insert(StatusMap::value_type(HASP_ALREADY_LOGGED_IN,"提示代码：H-8709"  ));//"Logging in twice to the same object"
	m_errorMap.insert(StatusMap::value_type(HASP_ALREADY_LOGGED_OUT, "提示代码：H-8309" ));//"Logging out twice from the same object"

	m_errorMap.insert(StatusMap::value_type(HASP_NOT_IMPL,"提示代码：H-7095"  ));//"Capability isn't available"
	m_errorMap.insert(StatusMap::value_type(HASP_INT_ERR,"提示代码：H-9800"  ));//"Internal API error"



	m_Key=0;

	m_errorStatus=HASP_STATUS_OK;
	
}

CLDK::~CLDK()
{

	if (m_Key!=0)
	{
		DelHaspKey();
		m_Key=0;
	}
}

CString CLDK::GetErrorStr()
{
	USES_CONVERSION;

	StatusMap::const_iterator error = m_errorMap.find(m_errorStatus);
	if(error == m_errorMap.end())
		return _T("Unknown error");
	else
	{
		CString str;	

		#ifdef _UNICODE
			str = A2T( error->second );
		#else
			str = error->second;
		#endif
			return str;
	}
}
BOOL CLDK::GetHaspKey(int nFeatureID)
{
	DelHaspKey();
	hasp_feature_t feature_id=nFeatureID;
	m_Status= hasp_login(feature_id,vendorCode,&m_Key);
	if (m_Status!=HASP_STATUS_OK)
		m_errorStatus=m_Status;
	return m_Status==HASP_STATUS_OK;
}
hasp_status_t CLDK::DelHaspKey()
{
	if (m_Key!=0)
	{
		m_Status= hasp_logout(m_Key);
		if (m_Status!=HASP_STATUS_OK)
			m_errorStatus=m_Status;
		m_Key=0;
	}
	return m_Status;
}



BOOL CLDK::EncryptRightD(double *pData,char *pchar)//正常使用加密函数
{

	hasp_feature_t  featureID;
	unsigned char   plainBuffer[ ] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	unsigned char   cipherBuffer[16]={ 0x32, 0x35, 0x37, 0x38, 0x33, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

	int nreturn=1;


	char pchar1[16]; 
	sprintf(pchar1, "%lf ",*pData); 
	for(int i=0;i<16;i++)plainBuffer[i]	=pchar1[i];

	CTime timeCurrent = CTime::GetCurrentTime();
	int QueryFun=((timeCurrent.GetHour()/2)%6);
	switch(QueryFun)
	{
	case 0:
		featureID=HASP_DECRYPTID2;
		break;
	case 1:
		featureID=HASP_DECRYPTID5;
		break;
	case 2:
		featureID=HASP_DECRYPTID3;
		break;
	case 3:
		featureID=HASP_DECRYPTID7;
		break;
	case 4:
		featureID=HASP_DECRYPTID8;
		break;
	case 5:
		featureID=HASP_DECRYPTID6;
		break;
	case 6:
		featureID=HASP_DECRYPTID1;
		break;

	}

	if(!GetHaspKey(featureID))
	{
		return FALSE;
	}

	//	_SFNT_Z65;
	m_Status=hasp_encrypt(m_Key, plainBuffer, 16);


	if (m_Status != HASP_STATUS_OK)
	{ 
		// If featureID is invalid, then this API will return error.
		m_errorStatus=m_Status;
		nreturn=0;
	}

	for(int i=0;i<16;i++)pchar[i]=plainBuffer[i];
	double result=atof(pchar);
//	sscanf(pchar, "%lf", &result);

	if(result==*pData)
	{
		*pData=32;
		nreturn=0;
	}
	//	_SFNT_Z325;
	*pData=result;

	return nreturn;

}
BOOL CLDK::DecryptRightD(double *pData,char *pchar)//正常使用解密函数
{

	int nreturn=1;
	hasp_handle_t   featureID;
	unsigned char   plainBuffer[16 ];

	for(int i=0;i<16;i++)plainBuffer[i]	=pchar[i];



	CTime timeCurrent = CTime::GetCurrentTime();
	int QueryFun=((timeCurrent.GetHour()/2)%6);
	switch(QueryFun)
	{
	case 0:
		featureID=HASP_DECRYPTID2;
		break;
	case 1:
		featureID=HASP_DECRYPTID5;
		break;
	case 2:
		featureID=HASP_DECRYPTID3;
		break;
	case 3:
		featureID=HASP_DECRYPTID7;
		break;
	case 4:
		featureID=HASP_DECRYPTID8;
		break;
	case 5:
		featureID=HASP_DECRYPTID6;
		break;
	case 6:
		featureID=HASP_DECRYPTID1;
		break;

	}

	if(!GetHaspKey(featureID))
	{
		return FALSE;
	}

	//	_SFNT_Z65;
	m_Status=hasp_decrypt(m_Key, plainBuffer, 16);

	if (m_Status != HASP_STATUS_OK)
	{ 
		// If featureID is invalid, then this API will return error.
		nreturn=0;m_errorStatus=m_Status;
	}


	for(int i=0;i<16;i++)pchar[i]=plainBuffer[i];
	double result=atof(pchar);
//	sscanf(pchar, "%lf", &result);
	if(result==*pData)
	{
		*pData=32;
		nreturn=0;
	}
	//	_SFNT_Z325;
	*pData=result;

	return nreturn;

}




BOOL CLDK::EncryptErrorD(double *pData,char *pchar)//异常使用加密函数
{




	char pchar1[16]; 
	char plainBuffer[16];
	sprintf(pchar1, "%lf ",*pData+322); 
	for(int i=0;i<16;i++)plainBuffer[i]	=pchar1[i];

	GetHaspKey(222);
	m_Status=hasp_encrypt(m_Key, plainBuffer, 16);
	m_errorStatus=HASP_STATUS_OK;




	bool flag=0;
	for(int i=0;i<16;i++)
	{
		if(pchar1[i]!=plainBuffer[i])
			flag=1;
	}
	if(flag) //函数被hook
	{
		for(int i=0;i<16;i++)pchar[i]=plainBuffer[i];
	}
	//	_SFNT_Z65;


	for(int i=0;i<16;i++)pchar[i]=pchar1[i];
	double result=atof(pchar);
//	sscanf(pchar, "%lf", &result);
	if(result==*pData)
	{
		*pData=32;
	}
	//	_SFNT_Z325;
	*pData=result;

	return 0;

}
BOOL CLDK::DecryptErrorD(double *pData,char *pchar)//异常使用解密函数
{

	int nreturn=1;


	char    cipherBuffer1[16];
	//	_SFNT_Z65;

	for(int i=0;i<16;i++)cipherBuffer1[i]	=pchar[i];

	GetHaspKey(333);

	m_Status=hasp_decrypt(m_Key, cipherBuffer1, 16);
	m_errorStatus=HASP_STATUS_OK;


	bool flag=0;
	for(int i=0;i<16;i++)
	{
		if(cipherBuffer1[i]!=pchar[i])
			flag=1;
	}
	if(flag) //函数被hook
	{
		for(int i=0;i<16;i++)pchar[i]=cipherBuffer1[i];
		nreturn=0;
	}
	double result=atof(pchar);
//	sscanf(pchar, "%lf", &result);
	*pData=result-322;

	return nreturn;

}

BOOL CLDK::EncryptRightI(int *pData,char *pchar)//正常使用加密函数
{

	hasp_handle_t   featureID;
	unsigned char   plainBuffer[ ] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	unsigned char   cipherBuffer[16]={ 0x32, 0x35, 0x37, 0x38, 0x33, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

	int nreturn=1;


	char pchar1[16]; 
	sprintf(pchar1, "%d ",*pData); 
	for(int i=0;i<16;i++)plainBuffer[i]	=pchar1[i];

	CTime timeCurrent = CTime::GetCurrentTime();
	int QueryFun=((timeCurrent.GetHour()/2)%6);
	switch(QueryFun)
	{
	case 0:
		featureID=HASP_DECRYPTID1;
		break;
	case 1:
		featureID=HASP_DECRYPTID4;
		break;
	case 2:
		featureID=HASP_DECRYPTID3;
		break;
	case 3:
		featureID=HASP_DECRYPTID6;
		break;
	case 4:
		featureID=HASP_DECRYPTID8;
		break;
	case 5:
		featureID=HASP_DECRYPTID11;
		break;
	case 6:
		featureID=HASP_DECRYPTID12;
		break;

	}

	if(!GetHaspKey(featureID))
	{
			return FALSE;
	}

	//	_SFNT_Z65;
	m_Status=hasp_encrypt(m_Key, plainBuffer, 16);



	if (m_Status != HASP_STATUS_OK)
	{ 
		// If featureID is invalid, then this API will return error.
		nreturn=0;m_errorStatus=m_Status;
	}

	for(int i=0;i<16;i++)pchar[i]=plainBuffer[i];
	int result=atoi(pchar);
//	sscanf(pchar, "%d", &result);
	if(result==*pData)
	{
		*pData=32;
		nreturn=0;
	}
	//	_SFNT_Z325;
	*pData=result;

	return nreturn;

}
BOOL CLDK::DecryptRightI(int *pData,char *pchar)//正常使用解密函数
{

	int nreturn=1;
	hasp_handle_t   featureID;
	unsigned char   plainBuffer[16 ];

	for(int i=0;i<16;i++)plainBuffer[i]	=pchar[i];



	CTime timeCurrent = CTime::GetCurrentTime();
	int QueryFun=((timeCurrent.GetHour()/2)%6);
	switch(QueryFun)
	{
	case 0:
		featureID=HASP_DECRYPTID1;
		break;
	case 1:
		featureID=HASP_DECRYPTID4;
		break;
	case 2:
		featureID=HASP_DECRYPTID3;
		break;
	case 3:
		featureID=HASP_DECRYPTID6;
		break;
	case 4:
		featureID=HASP_DECRYPTID8;
		break;
	case 5:
		featureID=HASP_DECRYPTID11;
		break;
	case 6:
		featureID=HASP_DECRYPTID12;
		break;

	}
	if(!GetHaspKey(featureID))
	{
		return FALSE;
	}

	//	_SFNT_Z65;
	m_Status=hasp_decrypt(m_Key, plainBuffer, 16);



	if (m_Status != HASP_STATUS_OK)
	{ 
		// If featureID is invalid, then this API will return error.
		nreturn=0;m_errorStatus=m_Status;
	}

 
	for(int i=0;i<16;i++)pchar[i]=plainBuffer[i];
	int result=atoi(pchar);
//	sscanf(pchar, "%d", &result);
	if(result==*pData)
	{
		*pData=32;
		nreturn=0;
	}
	//	_SFNT_Z325;
	*pData=result;

	return nreturn;

}




BOOL CLDK::EncryptErrorI(int *pData,char *pchar)//异常使用加密函数
{

	


	char pchar1[16]; 
	char plainBuffer[16];
	sprintf(pchar1, "%d ",*pData+322); 
	for(int i=0;i<16;i++)plainBuffer[i]	=pchar1[i];

	GetHaspKey(222);
	m_Status=hasp_encrypt(m_Key, plainBuffer, 16);
	m_errorStatus=HASP_STATUS_OK;




	bool flag=0;
	for(int i=0;i<16;i++)
	{
		if(pchar1[i]!=plainBuffer[i])
			flag=1;
	}
	if(flag) //函数被hook
	{
		for(int i=0;i<16;i++)pchar[i]=plainBuffer[i];
	}
	//	_SFNT_Z65;


	for(int i=0;i<16;i++)pchar[i]=pchar1[i];
	int result=atoi(pchar);
//	sscanf(pchar, "%d", &result);
	if(result==*pData)
	{
		*pData=32;
	}
	//	_SFNT_Z325;
	*pData=result;

	return 0;
	
}
BOOL CLDK::DecryptErrorI(int *pData,char *pchar)//异常使用解密函数
{

	int nreturn=1;


	char    cipherBuffer1[16];
	//	_SFNT_Z65;

	for(int i=0;i<16;i++)cipherBuffer1[i]	=pchar[i];

	GetHaspKey(333);

	m_Status=hasp_decrypt(m_Key, cipherBuffer1, 16);
	m_errorStatus=HASP_STATUS_OK;


	bool flag=0;
	for(int i=0;i<16;i++)
	{
		if(cipherBuffer1[i]!=pchar[i])
			flag=1;
	}
	if(flag) //函数被hook
	{
		for(int i=0;i<16;i++)pchar[i]=cipherBuffer1[i];
		nreturn=0;
	}
	int result=atoi(pchar);
//	sscanf(pchar, "%d", &result);
	*pData=result-322;

	return nreturn;

}






CTime CLDK::GetTime()
{
	CTime time2;
	if(!GetHaspKey(HASP_SHELL))
	{
		AfxMessageBox(GetErrorStr());
		return FALSE;
	}
	hasp_time_t time;
	m_Status = hasp_get_rtc(m_Key,&time);
	int ranvalue = abs( rand() )%2;

	if (m_Status!=HASP_STATUS_OK || ranvalue == 0)
	{
		time2=CTime::GetCurrentTime();
// 		AfxMessageBox(GetErrorStr());
	}
	else
	{

	unsigned int day;
	unsigned int month;
	unsigned int year;
	unsigned int hour;
	unsigned int minute;
	unsigned int second;

	hasp_hasptime_to_datetime(time,&day,&month,&year,&hour,&minute,&second);

	time2=CTime(int(year),int(month),int(day),int(hour),int(minute),int(second));
	}
	return time2;
}
int CLDK::ReadKey_RO(int offset,CString& sData) // offset==10 out_time ==11 out_use
{
	char pchar[RWDATALEN];
	memset(pchar,0,RWDATALEN);
	if (m_Key==0)
		GetHaspKey(0);
	m_Status = hasp_read(m_Key, HASP_FILEID_RO, (hasp_size_t)offset*16, (hasp_size_t)RWDATALEN, pchar);
	if (m_Status!=HASP_STATUS_OK)
		m_errorStatus=m_Status;

	sData="";
	for(int i=0;i<RWDATALEN;i++)
		if(pchar[i]!=' ')sData+=pchar[i];

	return m_Status;
}
int CLDK::ReadKey(int offset,CString& sData)// offset==10 recordtime ==11 usetimes
{
	char pchar[RWDATALEN];
	memset(pchar,0,RWDATALEN);
	if (m_Key==0)
		GetHaspKey(0);
	m_Status = hasp_read(m_Key, HASP_FILEID_RW, (hasp_size_t)offset*16, (hasp_size_t)RWDATALEN, pchar);
	if (m_Status!=HASP_STATUS_OK)
		m_errorStatus=m_Status;
	sData="";
	for(int i=0;i<RWDATALEN;i++)
		if(pchar[i]!=' ')sData+=pchar[i];
	return m_Status;
}

int CLDK::WriteKey(int offset,CString sData)
{
	USES_CONVERSION;

	char pchar[RWDATALEN];
	memset(pchar,0,RWDATALEN);
	sData=sData.Left(RWDATALEN);

	char* sPchar;
#ifdef _UNICODE
	sPchar = T2A(sData);
#else
	sPchar = sData.GetBuffer(sData.GetLength());
#endif

	strncpy(pchar,sPchar,sizeof(pchar));



	if (m_Key==0)
		GetHaspKey(0);

	m_Status= hasp_write(m_Key, HASP_FILEID_RW, (hasp_size_t)offset*16, (hasp_size_t)RWDATALEN, pchar);
	if (m_Status!=HASP_STATUS_OK)
		m_errorStatus=m_Status;

	return m_Status;

}



int CLDK::WriteRWData1(int nMemPos)
{
	int featureID;
	CTime timeCurrent = CTime::GetCurrentTime();
	int QueryFun=((timeCurrent.GetHour()/2)%6);
	switch(QueryFun)
	{
	case 0:
		featureID=HASP_DECRYPTID1;
		break;
	case 1:
		featureID=HASP_DECRYPTID2;
		break;
	case 2:
		featureID=HASP_DECRYPTID3;
		break;
	case 3:
		featureID=HASP_DECRYPTID5;
		break;
	case 4:
		featureID=HASP_DECRYPTID8;
		break;
	case 5:
		featureID=HASP_DECRYPTID10;
		break;
	case 6:
		featureID=HASP_DECRYPTID6;
		break;

	}
	if(!GetHaspKey(featureID))
		return -1;
	CString sData;
	sData.Format(_T("%d%d"),QueryFun,featureID);
	WriteKey(MEMORY_RW_TEXT1+1,sData);
	return QueryFun;
}
int CLDK::WriteRWData2(int nMemPos)
{
	int featureID;
	CTime timeCurrent = CTime::GetCurrentTime();
	int QueryFun=((timeCurrent.GetHour()/2)%6);
	switch(QueryFun)
	{
	case 0:
		featureID=HASP_DECRYPTID3;
		break;
	case 1:
		featureID=HASP_DECRYPTID2;
		break;
	case 2:
		featureID=HASP_DECRYPTID3;
		break;
	case 3:
		featureID=HASP_DECRYPTID2;
		break;
	case 4:
		featureID=HASP_DECRYPTID8;
		break;
	case 5:
		featureID=HASP_DECRYPTID10;
		break;
	case 6:
		featureID=HASP_DECRYPTID8;
		break;

	}
	if(!GetHaspKey(featureID))
		return -1;
	CString sData;
	sData.Format(_T("%d%d"),QueryFun,featureID);
	WriteKey(MEMORY_RW_TEXT2+1,sData);
	return QueryFun;
}
int CLDK::WriteRWData3(int nMemPos)
{
	int featureID;
	CTime timeCurrent = CTime::GetCurrentTime();
	int QueryFun=((timeCurrent.GetHour()/2)%6);
	switch(QueryFun)
	{
	case 0:
		featureID=HASP_DECRYPTID2;
		break;
	case 1:
		featureID=HASP_DECRYPTID2;
		break;
	case 2:
		featureID=HASP_DECRYPTID3;
		break;
	case 3:
		featureID=HASP_DECRYPTID6;
		break;
	case 4:
		featureID=HASP_DECRYPTID8;
		break;
	case 5:
		featureID=HASP_DECRYPTID10;
		break;
	case 6:
		featureID=HASP_DECRYPTID6;
		break;

	}
	if(!GetHaspKey(featureID))
		return -1;
	CString sData;
	sData.Format(_T("%d%d"),QueryFun,featureID);
	WriteKey(MEMORY_RW_TEXT3+1,sData);
	return QueryFun;
}
int CLDK::WriteRWData4(int nMemPos)
{
	int featureID;
	CTime timeCurrent = CTime::GetCurrentTime();
	int QueryFun=((timeCurrent.GetHour()/2)%6);
	switch(QueryFun)
	{
	case 0:
		featureID=HASP_DECRYPTID1;
		break;
	case 1:
		featureID=HASP_DECRYPTID8;
		break;
	case 2:
		featureID=HASP_DECRYPTID3;
		break;
	case 3:
		featureID=HASP_DECRYPTID5;
		break;
	case 4:
		featureID=HASP_DECRYPTID2;
		break;
	case 5:
		featureID=HASP_DECRYPTID10;
		break;
	case 6:
		featureID=HASP_DECRYPTID6;
		break;

	}
	if(!GetHaspKey(featureID))
		return -1;
	CString sData;
	sData.Format(_T("%d%d"),QueryFun,featureID);
	WriteKey(MEMORY_RW_TEXT4+1,sData);
	return QueryFun;
}
int CLDK::WriteRWData5(int nMemPos)
{
	int featureID;
	CTime timeCurrent = CTime::GetCurrentTime();
	int QueryFun=((timeCurrent.GetHour()/2)%6);
	switch(QueryFun)
	{
	case 0:
		featureID=HASP_DECRYPTID1;
		break;
	case 1:
		featureID=HASP_DECRYPTID2;
		break;
	case 2:
		featureID=HASP_DECRYPTID9;
		break;
	case 3:
		featureID=HASP_DECRYPTID5;
		break;
	case 4:
		featureID=HASP_DECRYPTID8;
		break;
	case 5:
		featureID=HASP_DECRYPTID10;
		break;
	case 6:
		featureID=HASP_DECRYPTID7;
		break;

	}
	if(!GetHaspKey(featureID))
		return -1;
	CString sData;
	sData.Format(_T("%d%d"),QueryFun,featureID);
	WriteKey(MEMORY_RW_TEXT5+1,sData);
	return QueryFun;
}
int CLDK::WriteRWData6(int nMemPos)
{
	int featureID;
	CTime timeCurrent = CTime::GetCurrentTime();
	int QueryFun=((timeCurrent.GetHour()/2)%6);
	switch(QueryFun)
	{
	case 0:
		featureID=HASP_DECRYPTID6;
		break;
	case 1:
		featureID=HASP_DECRYPTID2;
		break;
	case 2:
		featureID=HASP_DECRYPTID3;
		break;
	case 3:
		featureID=HASP_DECRYPTID8;
		break;
	case 4:
		featureID=HASP_DECRYPTID11;
		break;
	case 5:
		featureID=HASP_DECRYPTID10;
		break;
	case 6:
		featureID=HASP_DECRYPTID5;
		break;

	}
	if(!GetHaspKey(featureID))
		return -1;
	CString sData;
	sData.Format(_T("%d%d"),QueryFun,featureID);
	WriteKey(MEMORY_RW_TEXT6+1,sData);
	return QueryFun;
}

CTime CLDK::StringToTime(CString sData)
{
	if (sData=="")
	{
		return CTime(0);
	}

	int nYear;
	int nMonth;
	int nDate;
	int nHour;
	int nMin;
	int nSec;
#ifdef _UNICODE
	nYear=_wtoi(sData.Left(4));
	nMonth=_wtoi(sData.Mid(4,2));
	nDate=_wtoi(sData.Mid(6,2));
	nHour=_wtoi(sData.Mid(8,2));
	nMin=_wtoi(sData.Mid(10,2));
	nSec=_wtoi(sData.Mid(12,2));
#else
	nYear=atoi(sData.Left(4));
	nMonth=atoi(sData.Mid(4,2));
	nDate=atoi(sData.Mid(6,2));
	nHour=atoi(sData.Mid(8,2));
	nMin=atoi(sData.Mid(10,2));
	nSec=atoi(sData.Mid(12,2));
#endif

	return CTime(nYear,   nMonth,   nDate,   nHour,   nMin,   nSec);

}

/*
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


*/
BOOL CLDK::ReadKeyFlag1(int nIndex)//nIndex=12,13,15,17,19时返回错误则代表正确读取了加密狗的标志；
{
	
	CString str;
	if(nIndex==11)
	{
		ReadKey_RO(MEMORY_RO_TEXT11,str);
		if (str=="true")
		{
			return TRUE;
		}
	}
	if(nIndex==12)
	{
		ReadKey_RO(MEMORY_RO_TEXT12,str);
		if (str=="false")
		{
			return FALSE;
		}
	}
	if(nIndex==13)
	{
		ReadKey_RO(MEMORY_RO_TEXT13,str);
		if (str=="error")
		{
			return FALSE;
		}
	}
	if(nIndex==14)
	{
		ReadKey_RO(MEMORY_RO_TEXT14,str);
		if (str=="checkin")
		{
			return TRUE;
		}
	}
	if(nIndex==15)
	{
		ReadKey_RO(MEMORY_RO_TEXT15,str);
		if (str=="checkout")
		{
			return FALSE;
		}
	}
	if(nIndex==16)
	{
		ReadKey_RO(MEMORY_RO_TEXT16,str);
		if (str=="turnon")
		{
			return TRUE;
		}
	}
	if(nIndex==17)
	{
		ReadKey_RO(MEMORY_RO_TEXT17,str);
		if (str=="turnoff")
		{
			return FALSE;
		}
	}
	if(nIndex==18)
	{
		ReadKey_RO(MEMORY_RO_TEXT18,str);
		if (str=="trust")
		{
			return TRUE;
		}
	}
	if(nIndex==19)
	{
		ReadKey_RO(MEMORY_RO_TEXT19,str);
		if (str=="chect")
		{
			return FALSE;
		}
	}
	return TRUE;
}
BOOL CLDK::ReadKeyFlag2(int nIndex)//nIndex=12,13,15,17,19时返回错误则代表正确读取了加密狗的标志；
{
	CString str;
	if(nIndex==11)
	{
		ReadKey_RO(MEMORY_RO_TEXT11,str);
		if (str=="true")
		{
			return TRUE;
		}
	}
	if(nIndex==12)
	{
		ReadKey_RO(MEMORY_RO_TEXT12,str);
		if (str=="false")
		{
			return FALSE;
		}
	}
	if(nIndex==13)
	{
		ReadKey_RO(MEMORY_RO_TEXT13,str);
		if (str=="error")
		{
			return FALSE;
		}
	}
	if(nIndex==14)
	{
		ReadKey_RO(MEMORY_RO_TEXT14,str);
		if (str=="checkin")
		{
			return TRUE;
		}
	}
	if(nIndex==15)
	{
		ReadKey_RO(MEMORY_RO_TEXT15,str);
		if (str=="checkout")
		{
			return FALSE;
		}
	}
	if(nIndex==16)
	{
		ReadKey_RO(MEMORY_RO_TEXT16,str);
		if (str=="turnon")
		{
			return TRUE;
		}
	}
	if(nIndex==17)
	{
		ReadKey_RO(MEMORY_RO_TEXT17,str);
		if (str=="turnoff")
		{
			return FALSE;
		}
	}
	if(nIndex==18)
	{
		ReadKey_RO(MEMORY_RO_TEXT18,str);
		if (str=="trust")
		{
			return TRUE;
		}
	}
	if(nIndex==19)
	{
		ReadKey_RO(MEMORY_RO_TEXT19,str);
		if (str=="chect")
		{
			return FALSE;
		}
	}
	return TRUE;
}
BOOL CLDK::ReadKeyFlag3(int nIndex)//nIndex=12,13,15,17,19时返回错误则代表正确读取了加密狗的标志；
{
	CString str;
	if(nIndex==11)
	{
		ReadKey_RO(MEMORY_RO_TEXT11,str);
		if (str=="true")
		{
			return TRUE;
		}
	}
	if(nIndex==12)
	{
		ReadKey_RO(MEMORY_RO_TEXT12,str);
		if (str=="false")
		{
			return FALSE;
		}
	}
	if(nIndex==13)
	{
		ReadKey_RO(MEMORY_RO_TEXT13,str);
		if (str=="error")
		{
			return FALSE;
		}
	}
	if(nIndex==14)
	{
		ReadKey_RO(MEMORY_RO_TEXT14,str);
		if (str=="checkin")
		{
			return TRUE;
		}
	}
	if(nIndex==15)
	{
		ReadKey_RO(MEMORY_RO_TEXT15,str);
		if (str=="checkout")
		{
			return FALSE;
		}
	}
	if(nIndex==16)
	{
		ReadKey_RO(MEMORY_RO_TEXT16,str);
		if (str=="turnon")
		{
			return TRUE;
		}
	}
	if(nIndex==17)
	{
		ReadKey_RO(MEMORY_RO_TEXT17,str);
		if (str=="turnoff")
		{
			return FALSE;
		}
	}
	if(nIndex==18)
	{
		ReadKey_RO(MEMORY_RO_TEXT18,str);
		if (str=="trust")
		{
			return TRUE;
		}
	}
	if(nIndex==19)
	{
		ReadKey_RO(MEMORY_RO_TEXT19,str);
		if (str=="chect")
		{
			return FALSE;
		}
	}
	return TRUE;
}

int CLDK::ReadRWData1(int nMemPos)//读加密狗的读写存储区；输入参数无作用，固定读MEMORY_RW_TEXT1实际读取“ROW39”，返回1正确；
{
	CString sData;
	ReadKey(nMemPos,sData);
	if (sData=="ROW39")
		return 1;

	return nMemPos;
}

int CLDK::ReadRWData2(int nMemPos)//读加密狗的读写存储区；输入参数无作用，固定读MEMORY_RW_TEXT1实际读取“ROW41”，返回2正确；
{
	CString sData;
	ReadKey(nMemPos,sData);
	if (sData=="ROW41")
		return 2;

	return nMemPos;
}

int CLDK::ReadRWData3(int nMemPos)//读加密狗的读写存储区；输入参数无作用，固定读MEMORY_RW_TEXT1实际读取“ROW39”，返回1正确；
{
	CString sData;
	ReadKey(nMemPos,sData);
	if (sData=="ROW43")
		return 3;

	return nMemPos;
}

int CLDK::ReadRWData4(int nMemPos)//读加密狗的读写存储区；输入参数无作用，固定读MEMORY_RW_TEXT1实际读取“ROW39”，返回1正确；
{
	CString sData;
	ReadKey(nMemPos,sData);
	if (sData=="ROW45")
		return 4;

	return nMemPos;
}

int CLDK::ReadRWData5(int nMemPos)//读加密狗的读写存储区；输入参数无作用，固定读MEMORY_RW_TEXT1实际读取“ROW39”，返回1正确；
{
	CString sData;
	ReadKey(nMemPos,sData);
	if (sData=="ROW47")
		return 5;

	return nMemPos;
}

int CLDK::ReadRWData6(int nMemPos)//读加密狗的读写存储区；输入参数无作用，固定读MEMORY_RW_TEXT1实际读取“ROW49”，返回6正确；
{
	CString sData;
	ReadKey(nMemPos,sData);
	if (sData=="ROW49")
		return 6;

	return nMemPos;
}
// int	CLDK::CheckDllList()
// {
// 	int nRet = 0;
// 
// 	hasp_handle_t handle = HASP_INVALID_HANDLE_VALUE;
// 	hasp_status_t status;
// 
// 	sntl_lg_handle_t handle2 = SNTL_LG_INVALID_HANDLE_VALUE;
// 	sntl_lg_status_t status2;
// 
// 	char* init_param = NULL;    
// 
// 	//just use for calling hasp_windows_x64_demo.dll
// 	status = hasp_login(HASP_SHELL, vendorCode, &handle);
// 
// 	//just use for sntl_licgen_windows_x64.dll
// 	status2 = sntl_lg_initialize(init_param, &handle2); 
// 
// 	char strList[] = "QLFileSvrLib_u.dll;QlFileTransferEx_u.dll;KDS_CSharpReport.dll";
// 	//call interface in the static library
// 	nRet = SntlCheckDLL(strList);    
// 	
// 	return nRet;
// }
// 
// int CLDK::DetectEmulator()
// {
// 	int nRet = 0;
// 	int status;
// 	char scope[] = "12345678";
// 	nRet = detect_emulator( vendorCode , scope, &status);
// 	return nRet;
// }

int CLDK::IsOutTime()
{
	//xq define 20170823 ============================================== 
/*	CString strEndTime;
	CString strFilePath = theApp.m_strKdsWorkPath +_T("\\运行库\\共用插件\\ordersvr.plw");//设置配置文件路径
 #ifdef _DEBUG
	if (!PathFileExists(strFilePath))
	{
		strFilePath = theApp.m_strAppPath +_T("\\ordersvr.plw");//设置配置文件路径
	}
 	
 #endif
	
	CFile file;
	if (!file.Open(strFilePath,CFile::modeRead))
	{
		theApp.m_nOuttime = 1;		
		return 0;
	}
	int len=32;
	char temp[33];
	temp[32] = 0;

	file.Read(temp,len);
	file.Close();
	GetHaspKey(HASP_SHELL);
	m_Status = hasp_decrypt(m_Key, temp, len);
	
	if (m_Status != HASP_STATUS_OK)
	{ 
		// If featureID is invalid, then this API will return error.
		theApp.m_nOuttime = 1;		
	}

	USES_CONVERSION;
	strEndTime= A2T(temp);

	CString stime1=strEndTime.Left(16);
	CString stime2=strEndTime.Right(16);

	CTime sTime=StringToTime(stime1);; // 10:15PM Aug 01, 2018
	CTime eTime=StringToTime(stime2);; // 10:15PM Aug 01, 2018

	CTime cTime = GetTime();
	CTimeSpan eTimeSpan = eTime - cTime;
	int day=rand()%27;

	CTimeSpan sTimeSpan = cTime - sTime;

	if( eTimeSpan.GetDays()<day || sTimeSpan.GetDays() < -10 )
	{
		theApp.m_nOuttime = 1;
	}
	*/
	//xq end  20170823 ===================================================
	return 0;
}
int   CLDK::CheckData( )
{
/*	theApp.m_Status = 0;

	GetHaspKey(HASP_PLMVERSION);

	IsOutTime();

	char data[16];
	double data2=2.3;
	int   data3 = 91;
	if((CTime::GetCurrentTime().GetSecond()+1)%5==0)
	{
		EncryptRightD(&data2,data);
		data2 = 5;
		DecryptRightD(&data2,data);

	}else
	{
		EncryptRightI(&data3,data);
		data3 = 5;
		DecryptRightI(&data3,data);
	}

	if(data2!=2.3)
	{
		theApp.m_Status = 1;
	}
	if(data3!=91)
	{
		theApp.m_Status = 1;
	}
	*/
	return 0;
}

int   CLDK::CheckData1_3( )
{
	CTime cTime = GetTime();
	if( cTime.GetMonth() >=1 && cTime.GetMonth() <= 3)
	{
		CheckData( );
	}
	return 0;
}

int   CLDK::CheckData9_12( )
{
	CTime cTime = GetTime();
	if( cTime.GetMonth() >=9 && cTime.GetMonth() <= 12)
	{
		CheckData( );
	}
	return 0;
}

int   CLDK::CheckDataOnTime( )
{
/*	CTime cTime = GetTime();
	int nHour = rand()%3 + 1;		
	if( cTime.GetHour()%nHour )
	{
		GetHaspKey(HASP_PLMVERSION);

		theApp.m_Status = 0;
		char data[16];
		double data2=2.3;
		if((CTime::GetCurrentTime().GetSecond()+1)%2==0)
		{
			EncryptRightD(&data2,data);
			data2 = 5;
			DecryptRightD(&data2,data);

		}
		if(data2!=2.3)
		{
			theApp.m_Status = 1;
		}		
	}*/
	return 0;
}

void CLDK::WriteOutTimeFile( int nType )
{
	GetHaspKey(HASP_SHELL);
	
	int len=32;
	unsigned char data[] = "20170907111111112018101111111111";

	m_Status = hasp_encrypt(m_Key, data, len);
	if (m_Status != HASP_STATUS_OK)
	{ 
		return;	
	}

	CFile file;
	CString strFilePath = theApp.m_strAppPath +_T("\\UpDatasvr.kdw");//设置配置文件路径
	if( nType == 1)//PLM
	{		
		strFilePath = theApp.m_strAppPath +_T("\\ordersvr.plw");//设置配置文件路径
	}

	DeleteFile(strFilePath);

	file.Open(strFilePath,CFile::modeWrite| CFile::modeCreate);
	file.Write(data,len);
	file.Close();

	/*
	file.Open(strFilePath,CFile::modeRead);
	TCHAR temp1[33];
	temp1[32]=0;
	file.Read(temp1,len);
	file.Close();

	m_Status = hasp_decrypt(m_Key, temp1, len);

	AfxMessageBox(temp1);
	*/
}

//不支持小于16的长度 返回值为FALSE 加密失败
BOOL   CLDK::EncryptString( char* inBuffer, int inLen)
{

	BOOL bRet = FALSE;
	GetHaspKey(HASP_SHELL);

	m_Status = hasp_encrypt(m_Key, inBuffer, inLen);

	if( m_Status == HASP_STATUS_OK )
	{

		bRet = TRUE;
	}

	return bRet;	
}

// 返回false 解密失败
BOOL   CLDK::DecryptString( char* inBuffer , int inLen)
{
	BOOL bRet = FALSE;

	GetHaspKey(HASP_SHELL);

	m_Status = hasp_decrypt(m_Key, inBuffer, inLen);

	if( m_Status == HASP_STATUS_OK )
	{

		bRet = TRUE;
	}

	return bRet;
}

//返回值false表示获取时间失败
BOOL   CLDK::GetHaspTime(unsigned int& year ,unsigned int& month,unsigned int& day , unsigned int& hour,unsigned int& min ,unsigned int& sec)
{
	BOOL bRet = FALSE;

	GetHaspKey(HASP_SHELL);

	hasp_time_t time;
	
	m_Status = hasp_get_rtc(m_Key, &time);

	m_Status = hasp_hasptime_to_datetime(time, &day, &month, &year, &hour, &min, &sec);

	if(m_Status  == HASP_STATUS_OK)
	{
		bRet = TRUE;
	}
	return bRet;
}

BOOL    CLDK::GetHaspInfo(char** info)
{
	BOOL bRet = FALSE;

	const char* scope = 
		"<?xml version=\"1.0\" encoding=\"UTF-8\" ?>"
		"<haspscope/>";

	const char* format = 
		"<?xml version=\"1.0\" encoding=\"UTF-8\" ?>"
		"<haspformat root=\"hasp_info\">"
		"    <hasp>"
		"        <attribute name=\"id\" />"
		"        <attribute name=\"type\" />"
		"        <feature>"
		"            <attribute name=\"id\" />"
		"        </feature>"
		"    </hasp>"
		"</haspformat>";


	m_Status = hasp_get_info(scope, format, vendorCode, info);

	/* check if operation was successful */
	if(m_Status  == HASP_STATUS_OK)
	{
		bRet = TRUE;
	}
	return bRet;
}

CString CLDK::GetKeyInfo()
{	
	CString sInfo;

	if(!GetHaspKey(HASP_BASEVERSION))
		return sInfo;
		
	char *info = 0;

	const char* format = 
		"<?xml version=\"1.0\" encoding=\"UTF-8\" ?>"
		"<haspformat root=\"haspscope\">"
		"    <hasp>"
		"        <attribute name=\"id\" />"
		"    </hasp>"
		"</haspformat>";

	hasp_status_t status = hasp_get_sessioninfo(m_Key, format, &info);

	USES_CONVERSION;

#ifdef _UNICODE
	sInfo = A2T( info);
#else
	sInfo=info;
#endif

	
	hasp_free(info);
	int n=sInfo.Find(_T("id="));
	int n1=sInfo.GetLength()-n-4;

	CString sInfo1 = sInfo.Right(n1);
	int n2=sInfo1.Find(_T("/"));
	sInfo = sInfo1.Left(n2-2);

	return sInfo;
}
