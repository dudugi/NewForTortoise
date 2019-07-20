#pragma once
/********************************************************************
//  作者:           linyp
//  CopyRight(c)    2014 Burnon All Rights Reserved 
//  创建时间:       2014/04/10 9:09
//  类描述:         常用宏
//  修改时间:       
//  修改目的:       
*********************************************************************/


#include <vector>
#include <bitset>

//无字符整型容器
typedef std::vector<UINT>  VEC_UNITS;
typedef std::vector<UINT>::iterator  VEC_UNITS_ITER;

//BYTE 0-255
typedef std::vector<BYTE> VEC_BYTE;
typedef std::vector<BYTE>::iterator VEC_BYTE_ITER;

typedef std::bitset<16> BIT16;



//常用宏定义
//memcpy替代函数 防止越界访问出现特殊异常
//头三个参数同原memcpy  后四个参数 sizeofDst 总长度，_bgnOfDst目标开始拷贝位置，_sizeOfSrc 源总长度，_bgnOfSrc源开始位置
#define raymemcpy(_dst,_src, _sizeOfCopy, _sizeOfDst, _bgnOfDst, _sizeOfSrc, _bgnOfSrc) \
	if(_sizeOfCopy <= 0 || _sizeOfDst <= 0 || _bgnOfDst < 0 || _sizeOfSrc<= 0 ||  _bgnOfSrc< 0 )\
	{ ASSERT(0); LOGBUG(_T("memcpy out of range!!! _sizeOfCopy <= 0 || _sizeOfDst <= 0 || _bgnOfDst < 0 || _sizeOfSrc<= 0 ||  _bgnOfSrc< 0 ")); }\
	else if(_bgnOfSrc+_sizeOfCopy > _sizeOfSrc)\
	{ ASSERT(0); LOGBUG(_T("memcpy out of range!!! _bgnOfSrc+_sizeOfCopy>_sizeOfSrc"));}\
	else if(_bgnOfDst+_sizeOfCopy > _sizeOfDst)\
	{ ASSERT(0); LOGBUG(_T("memcpy out of range!!! _bgnOfDst+_sizeOfCopy>_sizeOfSrc"));}\
	else{ memcpy(_dst, _src, _sizeOfCopy); }

//内测期间开启
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
   {ASSERT(0);LOGBUG(n);AfxMessageBox(L"系统错误，请联系开发商，务必保持花样或数据。System error!!!");throw 0;}

#define LOGBUGT(x)\
   if(x){ LOGBUG(L"");}
//描述:测试某段代码所花的时间
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

//忽略编译器警告
#pragma  warning(disable:4018)		//“<”: 有符号/无符号不匹配
#pragma  warning(disable:4244)		//从“double/float”转换到“int/long”，可能丢失数据
//--------------------------------------------------------------
//输出声明
#define  OUT

//引用参数声明
#define  REF

//虚函数重载
#define  _OverLoad

//线程函数体内，检测是否应该函数返回
#define  THREAD_OUT_CHECK(_bOUT) \
	if (_bOUT) \
	{ \
		return; \
	}

//相等性判断
#define EQUAL(left, right) \
	((left) == (right)) 

//不等性判断
#define NOT_EQUAL(left, right) \
	((left) != (right))

//等于NULL
#define  EQUAL_NULL(var) \
	EQUAL(NULL, var)

//不等于NULL
#define  NOT_NULL(var) \
	NOT_EQUAL(NULL, var)

//不等于0
#define NOT_ZERO(var) \
	(0 != (var))

//等于0
#define  IS_ZERO(var) \
	( (0) == (var) )

//删除动态创建的CDialog
#define  SAFE_DELETE_DLG(pDlg) \
	if ( pDlg ) \
	{ \
		if (pDlg->GetSafeHwnd()) \
		{ \
			pDlg->DestroyWindow(); \
		} \
	}

//VC中debug模式下声明了但却未初始化的指针
#define  DEBUG_NOT_INIT_POINTER   reinterpret_cast<void*>( static_cast<long>( 0xcdcdcdcd ) )
//VC中debug模式下的野指针（删除了但是未赋空值）
#define  DEBUG_WILD_POINTER   reinterpret_cast<void*>( static_cast<long>( 0xfeeefeee ) )

//安全释放指针宏
#define SAFE_DELETE(p) {if (NULL != p) {delete p;p = NULL;}}
#define SAFE_DELETE_ARRAY(p) { if (NULL != p) { delete []p; p = NULL; } }
#define SAFE_DELETE_CHARS(p) {if (NULL != p) {delete [] p;p = NULL;}}
#define SAFE_FREE(p) { if (NULL != p) { free(p); p = NULL; } }

//输出参数宏
#define OUTPUT

#define  DLG_BKGND_COLOR		RGB(128, 128, 128)
#define  DLG_BKGND_COLOR_PLUS   Gdiplus::Color::LightGray

//数组大小
#define NUM(arr) (sizeof(arr) / sizeof(arr[0]))

//指针有效（不为空）
#define PointerValid(p) \
	MyASSERT( NOT_NULL(p) \
	&& NOT_EQUAL(p, DEBUG_NOT_INIT_POINTER) \
	&& NOT_EQUAL(p, DEBUG_WILD_POINTER) )

//指针有效（不为空）,否则返回
#define PointerValid_R(p) \
	MyASSERT_R( NOT_NULL(p) \
	&& NOT_EQUAL(p, DEBUG_NOT_INIT_POINTER) \
	&& NOT_EQUAL(p, DEBUG_WILD_POINTER) )

//指针有效（不为空）,否则返回NULL
#define PointerValid_R_NULL(p) \
	MyASSERT_R_NULL( NOT_NULL(p) \
	&& NOT_EQUAL(p, DEBUG_NOT_INIT_POINTER) \
	&& NOT_EQUAL(p, DEBUG_WILD_POINTER) )

//指针有效（不为空）,否则返回FALSE
#define PointerValid_R_FALSE(p) \
	MyASSERT_R_FALSE( NOT_NULL(p) \
	&& NOT_EQUAL(p, DEBUG_NOT_INIT_POINTER) \
	&& NOT_EQUAL(p, DEBUG_WILD_POINTER) )

//窗体有效
#define  WndValid(p)  MyASSERT( (NULL != p) && (p)->GetSafeHwnd() )
#define  WndValid_R(p)  MyASSERT_R( (NULL != p) && (p)->GetSafeHwnd() )
#define  WndValid_R_NULL(p)  MyASSERT_R_NULL( (NULL != p) && (p)->GetSafeHwnd() )
#define  WndValid_R_FALSE(p)  MyASSERT_R_FALSE( (NULL != p) && (p)->GetSafeHwnd() )


//UI对象指针有效(同时检测句柄）
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

//跟踪当前时间
#define  TIME_TRACE(strText) \
	{ \
	CString strFlag = _T("----------"); \
	CString strVal = NULL; \
	strVal.Format( _T(": %d\n"), GetTickCount() ); \
	TRACE( strFlag + strText + strVal ); \
	}

//遍历容器
#define FOREACH(itr, contain) for( (itr) = (contain)->begin(); itr != (contain)->end(); ++(itr) )


//空矩形
#define  RectNULL  CRect(0, 0, 0, 0)



//--------------------------
//写烦了switch中的case/break
//--------------------------
//第一个case语句
#define  CASE_BEGIN  case

//其他case语句
#define  CASE_DO \
	break; \
	case 

//default语句
#define  DEFAULT_END \
	break; \
	default:

//debug情况下运行
#ifdef _DEBUG
    #define DebugCode(code_fragment) { code_fragment }
#else    
    #define DebugCode(code_fragment) 
#endif

//是否为调试版本
inline BOOL IsDebug()
{
#ifdef _DEBUG 
	return TRUE;
#endif 

	return FALSE;
}

//语句转化为字符串
#define Change2Str(e) #e

//自定义断言:log版
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

//自定义断言：return版
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

//自定义断言：return NULL版
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

//自定义断言：return FALSE版
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
//如果formula表达式为真则进行中断
#define  DbgBreak(formula) \
	if ( (formula) ) \
	{ \
		DebugBreak(); \
	} \

//---------------------------------------------
//如果formula表达式为真则进行中断，之后返回
#define  DbgBreak_R(formula) \
	if ( (formula) ) \
	{ \
		DebugBreak(); \
		return; \
	} \

//-----------------------------------------------
//由于使用MyASSERT_R_FALSE容易让人有种在断言内运行程序段的嫌疑,
//因此此种情况时，更名为Check.而Assert内部只做判断而不执行代码段。
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


//交换2个整型值
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

//限制值在一定范围内
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


//判断是否管理员模式运行   chenjw   15/12/22 LINYP位置迁移
inline BOOL IsAdministrator() {  

   BOOL bIsElevated = FALSE;  
   HANDLE hToken = NULL;  
   UINT16 uWinVer = LOWORD(GetVersion());  
   uWinVer = MAKEWORD(HIBYTE(uWinVer),LOBYTE(uWinVer));  

   if (uWinVer < 0x0600)//不是VISTA、Windows7  
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