#pragma once
/********************************************************************
//  ����:           LiJY
//  CopyRight(c)    2010 Burnon All Rights Reserved 
//  ����ʱ��:       2010/05/17 10:04
//  ������:         printf������д���ļ��У���Ҫ�����̴߳�ӡ������Ϣ��
//  �޸�ʱ��:       
//  �޸�Ŀ��:       
*********************************************************************/

////Ҳ���Լ��޸�log�ļ���
////����  LOGPRINTF("hello %d,%u",10,12);
#ifdef _DEBUG
   #define LOGTRACE CLogPrintf(L"Trace.log",_T(__FILE__), __LINE__,_T(__FUNCTION__))
#else
   #define LOGTRACE
#endif

#define LOGBUG CLogPrintf(L"Bug.log",_T(__FILE__), __LINE__,_T(__FUNCTION__))

//д�������log yangjr 2016-2-16
//#define _RELEASEDEBUG //���������ע�͵���Ŀǰ��ȫ������
#ifdef _RELEASEDEBUG
#define COMPLIERLOG CLogPrintf(L"Compiler.log",_T(__FILE__), __LINE__,_T(__FUNCTION__))
#define COMPLIERLOGCLEAR {CLogPrintf logPrintf(L"Compiler.log",_T(__FILE__), __LINE__,_T(__FUNCTION__));logPrintf.Clear();}
#else
#define COMPLIERLOG
#define COMPLIERLOGCLEAR
#endif

//va���ͷ�ļ�
#include <fcntl.h>
#include <sys/stat.h>
#include <stdarg.h>

//����
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
   // ������:  [CLogPrintf]
   // ����ֵ:  []   
   // ����:    [const char * logFileName]    log���ļ���
   // ����:    [const char * curFileName]    ����logʱ��λ�õ��ļ���
   // ����:    [int lineNo]    ����logλ�õ��ļ�����
   // ��������:
   // ����:    LiJY 2010/05/17 11:11
   // �޸�ʱ��:
   // �޸�Ŀ��:
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
   // ������:  [operator()]
   // ����ֵ:  [void __cdecl]   
   // ����:    [const char * format]    
   // ����:    [...]    
   // ��������:������printf��ֻ��д�Ķ������ļ�,Ŀǰ֧�ֵ������� %d,%s,%c,����Ҫ��Ӧ��ȷ
   // ����:    LiJY 2010/05/17 10:53
   // �޸�ʱ��:
   // �޸�Ŀ��:
   //************************************
   //void operator()(const char *format ,...);
   void operator()(const wchar_t *format ,...)
   {
      assert(! m_logFileName.empty());
      CString strFileName = RnFile::GetModulePathFile(m_logFileName.c_str());
      std::locale &loc=std::locale::global(std::locale(std::locale(),"",LC_CTYPE)); //��ֹ������ַ������쳣 yangjr 2016-2-17
      std::wofstream file;      
      file.open(strFileName.GetBuffer(),std::ios::out | std::ios::app);  
      std::locale::global(loc);
      strFileName.ReleaseBuffer();
      time_t t = time( 0 ); 
      char strTime[64]; 
      strftime( strTime, sizeof(strTime), "%#c",localtime(&t) ); 
      std::wstring strwTime = RnString::Str2WStrUTF8(std::string(strTime));  

      std::wstring content;//����

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
               content.erase(content.end()-1);//ȥ�� %
               s = va_arg(ap,wchar_t *);				
               content+=s;
               break;
            case 'd':
               content.erase(content.end()-1);//ȥ�� %
               d = va_arg(ap,int);
               //LOGBUG wprintfʹ�ô��� start Duchen 2016/05/03 10:05 dc160502
               wsprintf(temp, L"%d", d);
               //wprintf(temp,"%d",d);
               //LOGBUG wprintfʹ�ô��� end   Duchen 2016/05/03 10:05       
               content+=temp;
               break;
            case 'c':
               content.erase(content.end()-1);//ȥ�� %
               c = (wchar_t) va_arg(ap,int);
               content+=c;
               break;
            default:
               assert(0);//����δ�ܴ��������
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
      file<<L"ʱ��:"<<strwTime<<std::endl;     
      file<<L"�ļ�:"<<m_curFileName<<std::endl;
      file<<L"�к�:"<<m_lineNo<<std::endl;
      file<<L"����:"<<m_curFuctionName<<std::endl;
      file<<L"����:"<<content<<std::endl;      
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
   const std::wstring m_logFileName; //log�ļ���
   const std::wstring m_curFileName; //����logʱ��λ�õ��ļ���
   const int m_lineNo;              //����logλ�õ��ļ�����
   const std::wstring m_curFuctionName; //����logʱ��λ�õĺ����� yangjr 2016-2-17
};

#if 1 //tmpduchen

class CLogPrintf2
{
public:
   //************************************
   // ������:  [CLogPrintf]
   // ����ֵ:  []   
   // ����:    [const char * logFileName]    log���ļ���
   // ����:    [const char * curFileName]    ����logʱ��λ�õ��ļ���
   // ����:    [int lineNo]    ����logλ�õ��ļ�����
   // ��������:
   // ����:    LiJY 2010/05/17 11:11
   // �޸�ʱ��:
   // �޸�Ŀ��:
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
   // ������:  [operator()]
   // ����ֵ:  [void __cdecl]   
   // ����:    [const char * format]    
   // ����:    [...]    
   // ��������:������printf��ֻ��д�Ķ������ļ�,Ŀǰ֧�ֵ������� %d,%s,%c,����Ҫ��Ӧ��ȷ
   // ����:    LiJY 2010/05/17 10:53
   // �޸�ʱ��:
   // �޸�Ŀ��:
   //************************************
   //void operator()(const char *format ,...);
   void operator()(const wchar_t *format ,...)
   {
      assert(! m_logFileName.empty());
      CString strFileName = RnFile::GetModulePathFile(m_logFileName.c_str());
      std::locale &loc=std::locale::global(std::locale(std::locale(),"",LC_CTYPE)); //��ֹ������ַ������쳣 yangjr 2016-2-17
      std::wofstream file;      
      file.open(strFileName.GetBuffer(),std::ios::out | std::ios::app);  
      std::locale::global(loc);
      strFileName.ReleaseBuffer();
      time_t t = time( 0 ); 
      char strTime[64]; 
      strftime( strTime, sizeof(strTime), "%#c",localtime(&t) ); 
      std::wstring strwTime = RnString::Str2WStrUTF8(std::string(strTime));  

      std::wstring content;//����

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
               content.erase(content.end()-1);//ȥ�� %
               s = va_arg(ap,wchar_t *);				
               content+=s;
               break;
            case 'd':
               content.erase(content.end()-1);//ȥ�� %
               d = va_arg(ap,int);
               //LOGBUG wprintfʹ�ô��� start Duchen 2016/05/03 10:05 dc160502
               wsprintf(temp, L"%d", d);
               //wprintf(temp,"%d",d);
               //LOGBUG wprintfʹ�ô��� end   Duchen 2016/05/03 10:05       
               content+=temp;
               break;
            case 'u':
               content.erase(content.end()-1);//ȥ�� %
               d = va_arg(ap,int);
               //LOGBUG wprintfʹ�ô��� start Duchen 2016/05/03 10:05 dc160502
               wsprintf(temp, L"%u", d);
               //wprintf(temp,"%d",d);
               //LOGBUG wprintfʹ�ô��� end   Duchen 2016/05/03 10:05       
               content+=temp;
               break;
            case 'c':
               content.erase(content.end()-1);//ȥ�� %
               c = (wchar_t) va_arg(ap,int);
               content+=c;
               break;
            default:
               assert(0);//����δ�ܴ��������
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
      file<<L"����:"<<content; 
	        
      file<<L" ʱ��:"<<strwTime;     
      file<<L" �ļ�:"<<m_curFileName;
      file<<L" �к�:"<<m_lineNo;
      file<<L" ����:"<<m_curFuctionName;
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
   const std::wstring m_logFileName; //log�ļ���
   const std::wstring m_curFileName; //����logʱ��λ�õ��ļ���
   const int m_lineNo;              //����logλ�õ��ļ�����
   const std::wstring m_curFuctionName; //����logʱ��λ�õĺ����� yangjr 2016-2-17
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

//#4171 �����RNF���뷨��ͼ ��ʾ�ڴ治�� ���±��� start Duchen 2017/05/18 15:34 dc160515
#pragma once

class CGetTickCount3
{
   DWORD m_dwFirstTickUser;
   DWORD m_dwFirstTickGdi;
   CString m_sTickName;
   DWORD m_dwLastTickUser;
   DWORD m_dwLastTickGdi;
   BOOL  m_bFirstTime;

   /* �ٽ������ʿ��� */
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
//#4171 �����RNF���뷨��ͼ ��ʾ�ڴ治�� ���±��� end   Duchen 2017/05/18 15:34