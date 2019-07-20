#include "StdAfx.h"
#include "LogCommandLineInfo.h"


CLogCommandLineInfo::CLogCommandLineInfo(void)
{
   m_nLogShellCommand = LogNothing;
}


CLogCommandLineInfo::~CLogCommandLineInfo(void)
{
}

void CLogCommandLineInfo::ParseParam(const TCHAR* pszParam, BOOL bFlag, BOOL bLast)
{
   if (bFlag)
   {
      const CStringA strParam(pszParam);
      ParseParamFlag(strParam.GetString());
   }
   else
      ParseParamNotFlag(pszParam);

   ParseLast(bLast);
}
#ifdef UNICODE
void CLogCommandLineInfo::ParseParam(const char* pszParam, BOOL bFlag, BOOL bLast)
{
   if (bFlag)
      ParseParamFlag(pszParam);
   else
      ParseParamNotFlag(pszParam);

   ParseLast(bLast);
}
#endif // UNICODE

void CLogCommandLineInfo::ParseParamFlag(const char* pszParam)
{
   // OLE command switches are case insensitive, while
   // shell command switches are case sensitive

   if (lstrcmpA(pszParam, "n") == 0)
      m_nLogShellCommand = LogNew;
   else
      m_nLogShellCommand = LogNothing;
}

void CLogCommandLineInfo::ParseParamNotFlag(const TCHAR* pszParam)
{
   if (m_nLogShellCommand == LogNew)
   {
      m_strLog = pszParam;
   }
}


#ifdef UNICODE
void CLogCommandLineInfo::ParseParamNotFlag(const char* pszParam)
{
   if (m_nLogShellCommand == LogNew)
   {
      m_strLog += pszParam;
   }
}

#endif

void CLogCommandLineInfo::ParseLast(BOOL bLast)
{
   if (bLast)
   {
      /*if (m_nLogShellCommand == LogNew && !m_strLog.IsEmpty())
         m_nLogShellCommand = LogNothing;*/
   }
}