#pragma once
#include "afxwin.h"
class CLogCommandLineInfo :
   public CCommandLineInfo
{
public:
   CLogCommandLineInfo(void);
   ~CLogCommandLineInfo(void);
public:
   //日志的类型
   enum {LogNothing , LogNew , } m_nLogShellCommand;

   //vaild only for LogNew
   CString m_strLog;

public:
   // plain char* version on UNICODE for source-code backwards compatibility
   virtual void ParseParam(const TCHAR* pszParam, BOOL bFlag, BOOL bLast);
#ifdef _UNICODE
   virtual void ParseParam(const char* pszParam, BOOL bFlag, BOOL bLast);
#endif

protected:
   void ParseParamFlag(const char* pszParam);
   void ParseParamNotFlag(const TCHAR* pszParam);
#ifdef _UNICODE
   void ParseParamNotFlag(const char* pszParam);
#endif
   void ParseLast(BOOL bLast);

};

