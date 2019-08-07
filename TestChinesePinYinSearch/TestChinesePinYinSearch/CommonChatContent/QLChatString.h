#pragma once
#include "stdafx.h"
#include <string>
#include <vector>
namespace QLChat
{
   CString GetPathExtUpper(const CString &sPath);
   CString GetPathFolderUpper(const CString &sPath);
   void GetPathExtAndNameUpper(const CString &sPath, CString *psExt, CString *psName);
   CString GetPathExtNameUpper(const CString &sPath);
   void GetPathWithOutExtUpper(const CString &sPath, CString *psName);

   template <typename TIter>
   extern CString JoinString(TIter IterBegin, TIter IterEnd, TCHAR cSeparator = _T('|'));

   CString FormatStringPadRight(const CString &sText, int nTotalLength);
   CString FormatStringPadRightWithSpace(const CString &sText, int nTotalTabLength);
   CString FormatStringWithinChar(const CString &sText, TCHAR cOuterChar, int nTotalTabLength);
   BOOL IsSoundFileExtName(const CString &sExtName);
   void UNICODE_TO_UTF8(const std::wstring& uni_str, std::vector<char>& utf8_str);
   std::vector<char> UNICODE_TO_UTF8(CStringW strIn);
   void UTF8_TO_UNICODE(const char *utf8_str,std::vector<WCHAR> &uni_str);
   CStringW UTF8_TO_UNICODE(const char *utf8_str);

   template <typename TIter>
   CString JoinString(TIter IterBegin, TIter IterEnd, TCHAR cSeparator)
   {
      CString sResult;
      for (auto Iter = IterBegin; Iter != IterEnd; ++Iter)
      {
         if (Iter != IterBegin)
         {
            sResult.AppendChar(cSeparator);
         }
         sResult.Append(*Iter);
      }
      return sResult;
   }
}