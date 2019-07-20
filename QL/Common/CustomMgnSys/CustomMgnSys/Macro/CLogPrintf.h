#pragma once
/********************************************************************
//  作者:           LiJY
//  CopyRight(c)    2010 Burnon All Rights Reserved 
//  创建时间:       2010/05/17 10:04
//  类描述:         printf的内容写入文件中：主要用于线程打印调试信息。
//  修改时间:       
//  修改目的:       
*********************************************************************/

////也可自己修改log文件名
////用例  LOGPRINTF("hello %d,%u",10,12);
#ifdef _DEBUG
   #define LOGTRACE CLogPrintf(L"Trace.log",_T(__FILE__), __LINE__,_T(__FUNCTION__))
#else
   #define LOGTRACE
#endif

#define LOGBUG CLogPrintf(L"Bug.log",_T(__FILE__), __LINE__,_T(__FUNCTION__))

//写编译过程log yangjr 2016-2-16
//#define _RELEASEDEBUG //这个后续需注释掉，目前先全部开启
#ifdef _RELEASEDEBUG
#define COMPLIERLOG CLogPrintf(L"Compiler.log",_T(__FILE__), __LINE__,_T(__FUNCTION__))
#define COMPLIERLOGCLEAR {CLogPrintf logPrintf(L"Compiler.log",_T(__FILE__), __LINE__,_T(__FUNCTION__));logPrintf.Clear();}
#else
#define COMPLIERLOG
#define COMPLIERLOGCLEAR
#endif

//va相关头文件
#include <fcntl.h>
#include <sys/stat.h>
#include <stdarg.h>

//其它
#include <stdio.h>
#include <string>
#include <fstream>
#include <assert.h>
#include <time.h> 
#include <rnstring.h>
#include <rnfile.h>

#include <locale.h>
#include <xlocale>

class CLogPrintf
{
public:
   //************************************
   // 函数名:  [CLogPrintf]
   // 返回值:  []   
   // 参数:    [const char * logFileName]    log的文件名
   // 参数:    [const char * curFileName]    调用log时的位置的文件名
   // 参数:    [int lineNo]    调用log位置的文件行数
   // 函数描述:
   // 作者:    LiJY 2010/05/17 11:11
   // 修改时间:
   // 修改目的:
   //************************************
   CLogPrintf(LPCTSTR logFileName,LPCTSTR curFileName, int lineNo,LPCTSTR curFuctionName)
      :m_logFileName(logFileName)
      ,m_curFileName(curFileName)
      ,m_lineNo(lineNo)
      ,m_curFuctionName(curFuctionName)
   {}

   ~CLogPrintf(void)
   {}
public:
   //************************************
   // 函数名:  [operator()]
   // 返回值:  [void __cdecl]   
   // 参数:    [const char * format]    
   // 参数:    [...]    
   // 函数描述:类似于printf，只是写的对象变成文件,目前支持的类型有 %d,%s,%c,类型要对应正确
   // 作者:    LiJY 2010/05/17 10:53
   // 修改时间:
   // 修改目的:
   //************************************
   //void operator()(const char *format ,...);
   void operator()(const wchar_t *format ,...)
   {
      assert(! m_logFileName.empty());
      CString strFileName = RnFile::GetModulePathFile(m_logFileName.c_str());
      std::locale &loc=std::locale::global(std::locale(std::locale(),"",LC_CTYPE)); //防止输出宽字符中文异常 yangjr 2016-2-17
      std::wofstream file;      
      file.open(strFileName.GetBuffer(),std::ios::out | std::ios::app);  
      std::locale::global(loc);
      strFileName.ReleaseBuffer();
      time_t t = time( 0 ); 
      char strTime[64]; 
      strftime( strTime, sizeof(strTime), "%#c",localtime(&t) ); 
      std::wstring strwTime = RnString::Str2WStrUTF8(std::string(strTime));  

      std::wstring content;//内容

      int d;
      wchar_t c,*s;
      wchar_t ch,prevCh='0',temp[100];
      va_list ap;
      va_start(ap,format);
      while(*format)
      {
         ch = *format++;
         if(prevCh == '%')
         {
            switch(ch)
            {
            case 's':
               content.erase(content.end()-1);//去除 %
               s = va_arg(ap,wchar_t *);				
               content+=s;
               break;
            case 'd':
               content.erase(content.end()-1);//去除 %
               d = va_arg(ap,int);
               //LOGBUG wprintf使用错误 start Duchen 2016/05/03 10:05 dc160502
               wsprintf(temp, L"%d", d);
               //wprintf(temp,"%d",d);
               //LOGBUG wprintf使用错误 end   Duchen 2016/05/03 10:05       
               content+=temp;
               break;
            case 'c':
               content.erase(content.end()-1);//去除 %
               c = (wchar_t) va_arg(ap,int);
               content+=c;
               break;
            default:
               assert(0);//出现未能处理的类型
               break;
            }
         }
         else
         {
            content+=ch;
         }
         prevCh = ch;
      }
      va_end(ap);
      
      file<<std::endl;      
      file<<L"时间:"<<strwTime<<std::endl;     
      file<<L"文件:"<<m_curFileName<<std::endl;
      file<<L"行号:"<<m_lineNo<<std::endl;
      file<<L"函数:"<<m_curFuctionName<<std::endl;
      file<<L"内容:"<<content<<std::endl;      
      file.close();
   }

   void Clear()
   {
      assert(! m_logFileName.empty());
      CString strFileName = RnFile::GetModulePathFile(m_logFileName.c_str());
      CFile file;
      if (file.Open(strFileName,CFile::modeCreate))
      {
         file.Close();
      }      
   }

private:
   const std::wstring m_logFileName; //log文件名
   const std::wstring m_curFileName; //调用log时的位置的文件名
   const int m_lineNo;              //调用log位置的文件行数
   const std::wstring m_curFuctionName; //调用log时的位置的函数名 yangjr 2016-2-17
};

#if 1 //tmpduchen

class CLogPrintf2
{
public:
   //************************************
   // 函数名:  [CLogPrintf]
   // 返回值:  []   
   // 参数:    [const char * logFileName]    log的文件名
   // 参数:    [const char * curFileName]    调用log时的位置的文件名
   // 参数:    [int lineNo]    调用log位置的文件行数
   // 函数描述:
   // 作者:    LiJY 2010/05/17 11:11
   // 修改时间:
   // 修改目的:
   //************************************
   CLogPrintf2(LPCTSTR logFileName,LPCTSTR curFileName, int lineNo,LPCTSTR curFuctionName)
      :m_logFileName(logFileName)
      ,m_curFileName(curFileName)
      ,m_lineNo(lineNo)
      ,m_curFuctionName(curFuctionName)
   {}

   ~CLogPrintf2(void)
   {}
public:
   //************************************
   // 函数名:  [operator()]
   // 返回值:  [void __cdecl]   
   // 参数:    [const char * format]    
   // 参数:    [...]    
   // 函数描述:类似于printf，只是写的对象变成文件,目前支持的类型有 %d,%s,%c,类型要对应正确
   // 作者:    LiJY 2010/05/17 10:53
   // 修改时间:
   // 修改目的:
   //************************************
   //void operator()(const char *format ,...);
   void operator()(const wchar_t *format ,...)
   {
      assert(! m_logFileName.empty());
      CString strFileName = RnFile::GetModulePathFile(m_logFileName.c_str());
      std::locale &loc=std::locale::global(std::locale(std::locale(),"",LC_CTYPE)); //防止输出宽字符中文异常 yangjr 2016-2-17
      std::wofstream file;      
      file.open(strFileName.GetBuffer(),std::ios::out | std::ios::app);  
      std::locale::global(loc);
      strFileName.ReleaseBuffer();
      time_t t = time( 0 ); 
      char strTime[64]; 
      strftime( strTime, sizeof(strTime), "%#c",localtime(&t) ); 
      std::wstring strwTime = RnString::Str2WStrUTF8(std::string(strTime));  

      std::wstring content;//内容

      int d;
      wchar_t c,*s;
      wchar_t ch,prevCh='0',temp[100];
      va_list ap;
      va_start(ap,format);
      while(*format)
      {
         ch = *format++;
         if(prevCh == '%')
         {
            switch(ch)
            {
            case 's':
               content.erase(content.end()-1);//去除 %
               s = va_arg(ap,wchar_t *);				
               content+=s;
               break;
            case 'd':
               content.erase(content.end()-1);//去除 %
               d = va_arg(ap,int);
               //LOGBUG wprintf使用错误 start Duchen 2016/05/03 10:05 dc160502
               wsprintf(temp, L"%d", d);
               //wprintf(temp,"%d",d);
               //LOGBUG wprintf使用错误 end   Duchen 2016/05/03 10:05       
               content+=temp;
               break;
            case 'u':
               content.erase(content.end()-1);//去除 %
               d = va_arg(ap,int);
               //LOGBUG wprintf使用错误 start Duchen 2016/05/03 10:05 dc160502
               wsprintf(temp, L"%u", d);
               //wprintf(temp,"%d",d);
               //LOGBUG wprintf使用错误 end   Duchen 2016/05/03 10:05       
               content+=temp;
               break;
            case 'c':
               content.erase(content.end()-1);//去除 %
               c = (wchar_t) va_arg(ap,int);
               content+=c;
               break;
            default:
               assert(0);//出现未能处理的类型
               break;
            }
         }
         else
         {
            content+=ch;
         }
         prevCh = ch;
      }
      va_end(ap);
      
      file<<std::endl;
      file<<L"内容:"<<content; 
	        
      file<<L" 时间:"<<strwTime;     
      file<<L" 文件:"<<m_curFileName;
      file<<L" 行号:"<<m_lineNo;
      file<<L" 函数:"<<m_curFuctionName;
		file<<std::endl;    
      file.close();
   }

   void Clear()
   {
      assert(! m_logFileName.empty());
      CString strFileName = RnFile::GetModulePathFile(m_logFileName.c_str());
      CFile file;
      if (file.Open(strFileName,CFile::modeCreate))
      {
         file.Close();
      }      
   }

private:
   const std::wstring m_logFileName; //log文件名
   const std::wstring m_curFileName; //调用log时的位置的文件名
   const int m_lineNo;              //调用log位置的文件行数
   const std::wstring m_curFuctionName; //调用log时的位置的函数名 yangjr 2016-2-17
};

class CGetTickCount2
{
   DWORD m_dwFirstTick;
   CString m_sTickName;
   DWORD m_dwLastTick;
public:
   CGetTickCount2(const CString &sTickName)
   {
      m_sTickName = sTickName;
      m_dwFirstTick = GetTickCount();
      m_dwLastTick = m_dwFirstTick;
   }
   
   static CGetTickCount2 &GetInstance()
   {
		static CGetTickCount2 Gtc(L"Log");
		return Gtc;
   }

//    void Get(CString sName = _T(""))
//    {
//       DWORD dwTickCount = GetTickCount();
// #ifdef _DEBUG
//       TRACE(_T("GetTickCount:Name=%s Count=%d Diff=%d CurPosName=%s\n"), m_sTickName, dwTickCount - m_dwFirstTick, dwTickCount - m_dwLastTick, sName);
// #else
//       LOGBUG(_T("GetTickCount:Name=%s Count=%d Diff=%d CurPosName=%s\n"), m_sTickName, dwTickCount - m_dwFirstTick, dwTickCount - m_dwLastTick, sName);
// #endif
//       m_dwLastTick = dwTickCount;
//    }
   
   void Get(CString sName, LPCTSTR logFileName,LPCTSTR curFileName, int lineNo,LPCTSTR curFuctionName)
   {
		DWORD dwTickCount = GetTickCount();
		
		CLogPrintf2(logFileName, curFileName, lineNo, curFuctionName)(_T("CurPosName=%s Diff=%d Name=%s Count=%d"), sName, dwTickCount - m_dwLastTick, m_sTickName, dwTickCount - m_dwFirstTick);
		
		m_dwLastTick = dwTickCount;
   }
};

#define LOGBUGTICK(x) (CGetTickCount2::GetInstance().Get((x), L"Bug2.log",_T(__FILE__), __LINE__,_T(__FUNCTION__)))
#endif //tmpduchen

//#4171 多尺码RNF套针法底图 提示内存不足 导致崩溃 start Duchen 2017/05/18 15:34 dc160515
#pragma once

class CGetTickCount3
{
   DWORD m_dwFirstTickUser;
   DWORD m_dwFirstTickGdi;
   CString m_sTickName;
   DWORD m_dwLastTickUser;
   DWORD m_dwLastTickGdi;
   BOOL  m_bFirstTime;

   /* 临界区访问控制 */
   LPCRITICAL_SECTION   m_csLock;
public:
   CGetTickCount3(const CString &sTickName)
      :m_bFirstTime(TRUE),m_csLock(NULL)
   {
      m_csLock = new CRITICAL_SECTION;
      InitializeCriticalSection(m_csLock);
      m_sTickName = sTickName;
      HANDLE hCurrProcess = GetCurrentProcess();
      DWORD dwUserObjectsCount = GetGuiResources(hCurrProcess, GR_USEROBJECTS);
      DWORD dwGdiObjectsCount = GetGuiResources(hCurrProcess, GR_GDIOBJECTS);

      if(0 != m_csLock){ EnterCriticalSection(m_csLock);}

      m_dwFirstTickUser = dwUserObjectsCount;
      m_dwFirstTickGdi = dwGdiObjectsCount;
      m_dwLastTickUser = m_dwFirstTickUser;
      m_dwLastTickGdi = m_dwFirstTickGdi;

      if(0 != m_csLock){ LeaveCriticalSection(m_csLock);}
   }

   ~CGetTickCount3()
   {
      if (m_csLock != NULL)
      {
         DeleteCriticalSection(m_csLock);
         delete m_csLock;
         m_csLock = NULL;
      }
   }

   static CGetTickCount3 &GetInstance()
   {
      static CGetTickCount3 Gtc(L"Log");
      return Gtc;
   }

   void Get(CString sName, LPCTSTR logFileName,LPCTSTR curFileName, int lineNo,LPCTSTR curFuctionName)
   {
      //DWORD dwTickCount = GetTickCount();
      HANDLE hCurrProcess = GetCurrentProcess();
      DWORD dwUserObjectsCount = GetGuiResources(hCurrProcess, GR_USEROBJECTS);
      DWORD dwGdiObjectsCount = GetGuiResources(hCurrProcess, GR_GDIOBJECTS);

      MEMORYSTATUS status;
      status.dwLength = sizeof(status);
      ZeroMemory(&status, sizeof(status));
      GlobalMemoryStatus(&status);

      

      if(0 != m_csLock){ EnterCriticalSection(m_csLock);}


      if (m_bFirstTime)
      {
         CLogPrintf2(logFileName, curFileName, lineNo, curFuctionName)
            (_T("LOGSTART --- CurPosName=%s dwTotalPhys=%u dwTotalPageFile=%u dwTotalVirtual=%u -------------------"), 
            sName, status.dwTotalPhys,status.dwTotalPageFile, status.dwTotalVirtual)
            ;
         m_bFirstTime = FALSE;
      }

      CLogPrintf2(logFileName, curFileName, lineNo, curFuctionName)
         (_T("CurPosName=%s Diff_User=%d Diff_GDI=%d Name=%s Count_User=%d Count_Gdi=%d dwMemoryLoad=%u dwAvailPhys=%u dwAvailPageFile=%u dwAvailVirtual=%u"), 
         sName, dwUserObjectsCount - m_dwLastTickUser, dwGdiObjectsCount - m_dwLastTickGdi,
         m_sTickName, dwUserObjectsCount/* - m_dwFirstTickUser*/, dwGdiObjectsCount/* - m_dwFirstTickGdi*/
         ,
         status.dwMemoryLoad, status.dwTotalPhys, status.dwAvailPageFile, status.dwAvailVirtual)
         ;


      m_dwLastTickUser = dwUserObjectsCount;
      m_dwLastTickGdi = dwGdiObjectsCount;

      if(0 != m_csLock){ LeaveCriticalSection(m_csLock);}
   }
};

#define LOGBUGHANDLE2(x) (CGetTickCount3::GetInstance().Get((x), L"Bug.log",_T(__FILE__), __LINE__,_T(__FUNCTION__)))
//#4171 多尺码RNF套针法底图 提示内存不足 导致崩溃 end   Duchen 2017/05/18 15:34