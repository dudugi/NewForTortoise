#pragma once
/********************************************************************
//  ����:           linyp
//  CopyRight(c)    2014 Burnon All Rights Reserved 
//  ����ʱ��:       2014/04/10 9:09
//  ������:         ���ú�
//  �޸�ʱ��:       
//  �޸�Ŀ��:       
*********************************************************************/


#include <vector>
#include <bitset>

//���ַ���������
typedef std::vector<UINT>  VEC_UNITS;
typedef std::vector<UINT>::iterator  VEC_UNITS_ITER;

//BYTE 0-255
typedef std::vector<BYTE> VEC_BYTE;
typedef std::vector<BYTE>::iterator VEC_BYTE_ITER;

typedef std::bitset<16> BIT16;



//���ú궨��
//memcpy������� ��ֹԽ����ʳ��������쳣
//ͷ��������ͬԭmemcpy  ���ĸ����� sizeofDst �ܳ��ȣ�_bgnOfDstĿ�꿪ʼ����λ�ã�_sizeOfSrc Դ�ܳ��ȣ�_bgnOfSrcԴ��ʼλ��
#define raymemcpy(_dst,_src, _sizeOfCopy, _sizeOfDst, _bgnOfDst, _sizeOfSrc, _bgnOfSrc) \
	if(_sizeOfCopy <= 0 || _sizeOfDst <= 0 || _bgnOfDst < 0 || _sizeOfSrc<= 0 ||  _bgnOfSrc< 0 )\
	{ ASSERT(0); LOGBUG(_T("memcpy out of range!!! _sizeOfCopy <= 0 || _sizeOfDst <= 0 || _bgnOfDst < 0 || _sizeOfSrc<= 0 ||  _bgnOfSrc< 0 ")); }\
	else if(_bgnOfSrc+_sizeOfCopy > _sizeOfSrc)\
	{ ASSERT(0); LOGBUG(_T("memcpy out of range!!! _bgnOfSrc+_sizeOfCopy>_sizeOfSrc"));}\
	else if(_bgnOfDst+_sizeOfCopy > _sizeOfDst)\
	{ ASSERT(0); LOGBUG(_T("memcpy out of range!!! _bgnOfDst+_sizeOfCopy>_sizeOfSrc"));}\
	else{ memcpy(_dst, _src, _sizeOfCopy); }

//�ڲ��ڼ俪��
#ifdef _DEBUG
#define CHECKVALUE(_value,_maxvalue)
#else
#define CHECKVALUE(_value,_maxvalue)\
   if (_value > _maxvalue)\
{\
   ASSERTLOG(L"");\
}
#endif

#define ASSERTLOG(n) \
   {ASSERT(0);LOGBUG(n);AfxMessageBox(L"ϵͳ��������ϵ�����̣���ر��ֻ��������ݡ�System error!!!");throw 0;}

#define LOGBUGT(x)\
   if(x){ LOGBUG(L"");}
//����:����ĳ�δ���������ʱ��
#ifdef _DEBUG
#define COUNT_TIME(num)    DWORD bTime_##num = ::GetTickCount();
#else
#define COUNT_TIME(num)
#endif

#ifdef _DEBUG
#define TRACE_COUNT_TIME(num)    TRACE(_T("\nTime_%s: %d ms\n"),#num,::GetTickCount()-bTime_##num);
#else
#define TRACE_COUNT_TIME(num)
#endif

//���Ա���������
#pragma  warning(disable:4018)		//��<��: �з���/�޷��Ų�ƥ��
#pragma  warning(disable:4244)		//�ӡ�double/float��ת������int/long�������ܶ�ʧ����
//--------------------------------------------------------------
//�������
#define  OUT

//���ò�������
#define  REF

//�麯������
#define  _OverLoad

//�̺߳������ڣ�����Ƿ�Ӧ�ú�������
#define  THREAD_OUT_CHECK(_bOUT) \
	if (_bOUT) \
	{ \
		return; \
	}

//������ж�
#define EQUAL(left, right) \
	((left) == (right)) 

//�������ж�
#define NOT_EQUAL(left, right) \
	((left) != (right))

//����NULL
#define  EQUAL_NULL(var) \
	EQUAL(NULL, var)

//������NULL
#define  NOT_NULL(var) \
	NOT_EQUAL(NULL, var)

//������0
#define NOT_ZERO(var) \
	(0 != (var))

//����0
#define  IS_ZERO(var) \
	( (0) == (var) )

//ɾ����̬������CDialog
#define  SAFE_DELETE_DLG(pDlg) \
	if ( pDlg ) \
	{ \
		if (pDlg->GetSafeHwnd()) \
		{ \
			pDlg->DestroyWindow(); \
		} \
	}

//VC��debugģʽ�������˵�ȴδ��ʼ����ָ��
#define  DEBUG_NOT_INIT_POINTER   reinterpret_cast<void*>( static_cast<long>( 0xcdcdcdcd ) )
//VC��debugģʽ�µ�Ұָ�루ɾ���˵���δ����ֵ��
#define  DEBUG_WILD_POINTER   reinterpret_cast<void*>( static_cast<long>( 0xfeeefeee ) )

//��ȫ�ͷ�ָ���
#define SAFE_DELETE(p) {if (NULL != p) {delete p;p = NULL;}}
#define SAFE_DELETE_ARRAY(p) { if (NULL != p) { delete []p; p = NULL; } }
#define SAFE_DELETE_CHARS(p) {if (NULL != p) {delete [] p;p = NULL;}}
#define SAFE_FREE(p) { if (NULL != p) { free(p); p = NULL; } }

//���������
#define OUTPUT

#define  DLG_BKGND_COLOR		RGB(128, 128, 128)
#define  DLG_BKGND_COLOR_PLUS   Gdiplus::Color::LightGray

//�����С
#define NUM(arr) (sizeof(arr) / sizeof(arr[0]))

//ָ����Ч����Ϊ�գ�
#define PointerValid(p) \
	MyASSERT( NOT_NULL(p) \
	&& NOT_EQUAL(p, DEBUG_NOT_INIT_POINTER) \
	&& NOT_EQUAL(p, DEBUG_WILD_POINTER) )

//ָ����Ч����Ϊ�գ�,���򷵻�
#define PointerValid_R(p) \
	MyASSERT_R( NOT_NULL(p) \
	&& NOT_EQUAL(p, DEBUG_NOT_INIT_POINTER) \
	&& NOT_EQUAL(p, DEBUG_WILD_POINTER) )

//ָ����Ч����Ϊ�գ�,���򷵻�NULL
#define PointerValid_R_NULL(p) \
	MyASSERT_R_NULL( NOT_NULL(p) \
	&& NOT_EQUAL(p, DEBUG_NOT_INIT_POINTER) \
	&& NOT_EQUAL(p, DEBUG_WILD_POINTER) )

//ָ����Ч����Ϊ�գ�,���򷵻�FALSE
#define PointerValid_R_FALSE(p) \
	MyASSERT_R_FALSE( NOT_NULL(p) \
	&& NOT_EQUAL(p, DEBUG_NOT_INIT_POINTER) \
	&& NOT_EQUAL(p, DEBUG_WILD_POINTER) )

//������Ч
#define  WndValid(p)  MyASSERT( (NULL != p) && (p)->GetSafeHwnd() )
#define  WndValid_R(p)  MyASSERT_R( (NULL != p) && (p)->GetSafeHwnd() )
#define  WndValid_R_NULL(p)  MyASSERT_R_NULL( (NULL != p) && (p)->GetSafeHwnd() )
#define  WndValid_R_FALSE(p)  MyASSERT_R_FALSE( (NULL != p) && (p)->GetSafeHwnd() )


//UI����ָ����Ч(ͬʱ�������
#define  UIPointerValid(p) \
	PointerValid(p); \
	WndValid(p);

#define UIPointerValid_R(p) \
	UIPointerValid(p); \
	if(NULL==(p) || !(p)->GetSafeHwnd()) \
	{ \
		return; \
	}

#define UIPointerValid_R_FALSE(p) \
	UIPointerValid(p); \
	if(NULL==(p) || !(p)->GetSafeHwnd()) \
	{ \
		return FALSE; \
	}

#define UIPointerValid_R_NULL(p) \
	UIPointerValid(p); \
	if(NULL==(p) || !(p)->GetSafeHwnd()) \
	{ \
		return NULL; \
	}

//���ٵ�ǰʱ��
#define  TIME_TRACE(strText) \
	{ \
	CString strFlag = _T("----------"); \
	CString strVal = NULL; \
	strVal.Format( _T(": %d\n"), GetTickCount() ); \
	TRACE( strFlag + strText + strVal ); \
	}

//��������
#define FOREACH(itr, contain) for( (itr) = (contain)->begin(); itr != (contain)->end(); ++(itr) )


//�վ���
#define  RectNULL  CRect(0, 0, 0, 0)



//--------------------------
//д����switch�е�case/break
//--------------------------
//��һ��case���
#define  CASE_BEGIN  case

//����case���
#define  CASE_DO \
	break; \
	case 

//default���
#define  DEFAULT_END \
	break; \
	default:

//debug���������
#ifdef _DEBUG
    #define DebugCode(code_fragment) { code_fragment }
#else    
    #define DebugCode(code_fragment) 
#endif

//�Ƿ�Ϊ���԰汾
inline BOOL IsDebug()
{
#ifdef _DEBUG 
	return TRUE;
#endif 

	return FALSE;
}

//���ת��Ϊ�ַ���
#define Change2Str(e) #e

//�Զ������:log��
#define  MyASSERT(formula) \
	if ( IsDebug() ) \
	{ \
		ASSERT(formula); \
	} \
	else \
	{ \
		if ( !(formula) ) \
		{ \
			CString str( Change2Str(formula) ); \
			str = L"MyASSERT! " + str; \
			LogEasy0(str, LogWarn, FALSE); \
		} \
	}

//�Զ�����ԣ�return��
#define  MyASSERT_R(formula) \
	if ( IsDebug() ) \
	{ \
		ASSERT(formula); \
		if ( !(formula) ) \
		{ \
			return; \
		} \
	} \
	else \
	{ \
		if ( !(formula) ) \
		{ \
			CString str( Change2Str(formula) ); \
			str = L"MyASSERT_R! " + str; \
			LogEasy0(str, LogWarn, FALSE); \
			return; \
		} \
	}

//�Զ�����ԣ�return NULL��
#define  MyASSERT_R_NULL(formula) \
	if ( IsDebug() ) \
	{ \
		ASSERT(formula); \
		if ( formula ) \
		{ \
		} \
		else \
		{ \
			return NULL; \
		} \
	} \
	else \
	{ \
		if ( formula ) \
		{ \
		} \
		else \
		{ \
			CString str( Change2Str(formula) ); \
			str = L"MyASSERT_R_NULL! " + str; \
			LogEasy0(str, LogWarn, FALSE); \
			return NULL; \
		} \
	}

//�Զ�����ԣ�return FALSE��
#define  MyASSERT_R_FALSE(formula) \
	if ( IsDebug() ) \
	{ \
		ASSERT(formula); \
		if ( !(formula) ) \
		{ \
			return FALSE; \
		} \
	} \
	else \
	{ \
		if ( !(formula) ) \
		{ \
			CString str( Change2Str(formula) ); \
			str = L"MyASSERT_R_FALSE! " + str; \
			LogEasy0(str, LogWarn, FALSE); \
			return FALSE; \
		} \
	}

//---------------------------------------------
//���formula���ʽΪ��������ж�
#define  DbgBreak(formula) \
	if ( (formula) ) \
	{ \
		DebugBreak(); \
	} \

//---------------------------------------------
//���formula���ʽΪ��������жϣ�֮�󷵻�
#define  DbgBreak_R(formula) \
	if ( (formula) ) \
	{ \
		DebugBreak(); \
		return; \
	} \

//-----------------------------------------------
//����ʹ��MyASSERT_R_FALSE�������������ڶ��������г���ε�����,
//��˴������ʱ������ΪCheck.��Assert�ڲ�ֻ���ж϶���ִ�д���Ρ�
//-----------------------------------------------
#define  DOCHECK(formula) \
	if ( IsDebug() ) \
	{ \
		ASSERT(formula); \
	} \
	else \
	{ \
		if ( !(formula) ) \
		{ \
			CString str( Change2Str(formula) ); \
			str = L"DOCHECK! " + str; \
			LogEasy0(str, LogWarn, FALSE); \
		} \
	}

//---------------------------------
#define  DOCHECK_R(formula) \
	if ( IsDebug() ) \
	{ \
		BOOL bOK = formula; \
		ASSERT(bOK); \
		if ( !bOK ) \
		{ \
			return; \
		} \
	} \
	else \
	{ \
		BOOL bOK = formula; \
		if ( !bOK ) \
		{ \
			CString str( Change2Str(formula) ); \
			str = L"DOCHECK_R! " + str; \
			LogEasy0(str, LogWarn, FALSE); \
			return; \
		} \
	}

//--------------------------------
#define  DOCHECK_R_NULL(formula) \
	if ( IsDebug() ) \
	{ \
		ASSERT(formula); \
		if ( formula ) \
		{ \
		} \
		else \
		{ \
			return NULL; \
		} \
	} \
	else \
	{ \
		if ( formula ) \
		{ \
		} \
		else \
		{ \
			CString str( Change2Str(formula) ); \
			str = L"DOCHECK_R_NULL! " + str; \
			LogEasy0(str, LogWarn, FALSE); \
			return NULL; \
		} \
	}

//---------------------------------
#define  DOCHECK_R_FALSE(formula) \
	if ( IsDebug() ) \
	{ \
		BOOL bOK = formula; \
		ASSERT(bOK); \
		if ( !(bOK) ) \
		{ \
			return FALSE; \
		} \
	} \
	else \
	{ \
		BOOL bOK = formula; \
		if ( !(bOK) ) \
		{ \
			CString str( Change2Str(formula) ); \
			str = L"DOCHECK_R_FALSE! " + str; \
			LogEasy0(str, LogWarn, FALSE); \
			return FALSE; \
		} \
	}


//����2������ֵ
inline void Swap2Int(int& l, int& r)
{
	int temp(l);
	l = r;
	r = temp;
}

template<typename T>
inline void Swap2Val(T& l, T& r)
{
	T temp(l);
	l = r;
	r = temp;
}

//����ֵ��һ����Χ��
template<typename T>
inline void LimitRange( T &nLeft, T nMIN, T nMAX )
{
	if ( nLeft < nMIN )
	{
		nLeft = nMIN;
	}

	if ( nMAX < nLeft )
	{
		nLeft = nMAX;
	}
}


//�ж��Ƿ����Աģʽ����   chenjw   15/12/22 LINYPλ��Ǩ��
inline BOOL IsAdministrator() {  

   BOOL bIsElevated = FALSE;  
   HANDLE hToken = NULL;  
   UINT16 uWinVer = LOWORD(GetVersion());  
   uWinVer = MAKEWORD(HIBYTE(uWinVer),LOBYTE(uWinVer));  

   if (uWinVer < 0x0600)//����VISTA��Windows7  
      return(FALSE);  

   if (OpenProcessToken(GetCurrentProcess(),TOKEN_QUERY,&hToken)) {  

      struct {  
         DWORD TokenIsElevated;  
      } /*TOKEN_ELEVATION*/te;  
      DWORD dwReturnLength = 0;  

      if (GetTokenInformation(hToken,/*TokenElevation*/(_TOKEN_INFORMATION_CLASS)20,&te,sizeof(te),&dwReturnLength)) {  
         if (dwReturnLength == sizeof(te))  
            bIsElevated = te.TokenIsElevated;  
      }  
      CloseHandle( hToken );  
   }  
   return bIsElevated;  
}  

//--------------------------------------------------------------
//end of