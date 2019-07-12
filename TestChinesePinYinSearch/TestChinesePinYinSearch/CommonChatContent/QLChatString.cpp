#include "stdafx.h"
#include "QLChatString.h"
#include <string>
#include <list>
namespace QLChat
{
   CString GetPathExtUpper(const CString &sPath)
   {
      CString sRet = PathFindExtension(sPath);
      sRet.MakeUpper();
      return sRet;
   }

   CString GetPathFolderUpper(const CString &sPath)
   {
      TCHAR Drive[_MAX_DRIVE] = {0};
      TCHAR Folder[_MAX_DIR] = {0};
      _tsplitpath(sPath, Drive, Folder, NULL, NULL);
      CString sRet(Drive);
      sRet.Append(Folder);
      sRet.MakeUpper();
      return sRet;
   }

   void GetPathExtAndNameUpper(const CString &sPath, CString *psExt, CString *psName)
   {
      TCHAR fname[_MAX_FNAME] = {0};
      TCHAR ext[_MAX_EXT] = {0};
      _tsplitpath(sPath, NULL, NULL, fname, ext);
      *psExt = ext;
      psExt->MakeUpper();
      *psName = fname;
      psName->MakeUpper();
   }

   CString GetPathExtNameUpper(const CString &sPath)
   {
      CString sExt;
      CString sName;
      GetPathExtAndNameUpper(sPath, &sExt, &sName);
      return sName + sExt;
   }

   void GetPathWithOutExtUpper(const CString &sPath, CString *psName)
   {
      TCHAR fname[_MAX_FNAME] = {0};
      TCHAR Drive[_MAX_DRIVE] = {0};
      TCHAR Folder[_MAX_DIR] = {0};
      _tsplitpath(sPath, Drive, Folder, fname, NULL);
      psName->Format(_T("%s%s%s"), Drive, Folder, fname);
      psName->MakeUpper();
   }

   CString FormatStringPadRight(const CString &sText, int nTotalTabLength)
   {
      int nTotalCount = 0; //全角算2个
      for(LPCTSTR p= sText; p != NULL && p[0] != 0; p = CharNext(p))
      {
         if(p[0] > 0 && p[0] <= 127)
         {
            if(p[0] >= 0x30 && p[0] <= 0x39)
            {
               //是数字
               ++nTotalCount;
            }
            else if((p[0] >= 0x41 && p[0] <= 0x5a) || (p[0] >= 0x61 && p[0] <= 0x7a))
            {
               //是字母
               ++nTotalCount;
            }
            else
            {
               ++nTotalCount;
            }
         }
         else 
         {
            //是中文文字
            nTotalCount += 2;
         }
      }

      int nDiff = nTotalTabLength * 6 - nTotalCount;
      if (nDiff <= 0)
      {
         return sText;
      }

      int nTabDiff = nDiff / 6;

      if ((nDiff % 6) || nTotalCount > 0)
      {
         ++nTabDiff;
      }

      std::string sEmpty(nTabDiff, '\t');
      CString sTail;
      sTail = sEmpty.c_str();
      return sText + sTail;
   }

   BOOL IsSoundFileExtName(const CString &sExtName)
   {
      if (sExtName == _T(".WAV") || sExtName == _T(".QLWAV") || sExtName == _T(".AMR"))
      {
         return TRUE;
      }

      return FALSE;
   }

   CString FormatStringPadRightWithSpace(const CString &sText, int nTotalTabLength)
   {
      int nTotalCount = 0; //全角算2个
      for(LPCTSTR p= sText; p != NULL && p[0] != 0; p = CharNext(p))
      {
         if(p[0] > 0 && p[0] <= 127)
         {
            if(p[0] >= 0x30 && p[0] <= 0x39)
            {
               //是数字
               ++nTotalCount;
            }
            else if((p[0] >= 0x41 && p[0] <= 0x5a) || (p[0] >= 0x61 && p[0] <= 0x7a))
            {
               //是字母
               ++nTotalCount;
            }
            else
            {
               ++nTotalCount;
            }
         }
         else 
         {
            //是中文文字
            nTotalCount += 2;
         }
      }

      int nDiff = nTotalTabLength - nTotalCount;
      if (nDiff == 0)
      {
         return sText;
      }
      else if (nDiff < 0)
      {
         CString sNewString;
         
         int nPotCount = 3;
         if (nTotalTabLength <= 3)
         {
            nPotCount = 0;
         }
         int nShrinkedLength = nTotalTabLength - nPotCount;
         int nTotalCount = 0; //全角算2个
            
         for(LPCTSTR p= sText; p != NULL && p[0] != 0 && nTotalCount < nShrinkedLength; p = CharNext(p))
         {
            int nAddCount = 0;
            if(p[0] > 0 && p[0] <= 127)
            {
               if(p[0] >= 0x30 && p[0] <= 0x39)
               {
                  //是数字
                  nAddCount = 1;
               }
               else if((p[0] >= 0x41 && p[0] <= 0x5a) || (p[0] >= 0x61 && p[0] <= 0x7a))
               {
                  //是字母
                  nAddCount = 1;
               }
               else
               {
                  nAddCount = 1;
               }
            }
            else 
            {
               //是中文文字
               nAddCount = 2;
            }
            if (nTotalCount + nAddCount > nShrinkedLength)
            {
               break;
            }
            nTotalCount += nAddCount;
            sNewString.AppendChar(p[0]);
         }

         for (int i = 0; i < nPotCount; ++i)
         {
            sNewString.AppendChar(_T('.'));
         }
         //sNewString.Append(_T("..."));
         nTotalCount += nPotCount;

         int nStillDiff = nTotalTabLength - nTotalCount;
         //ASSERT(nStillDiff >= 0);
         while (nStillDiff > 0)
         {
            sNewString.AppendChar(_T(' '));
            --nStillDiff;
         }
         
         return sNewString;
      }

      std::string sEmpty(nDiff, ' ');
      CString sTail;
      sTail = sEmpty.c_str();
      return sText + sTail;
   }

   static std::list<CString> SplitStringToLines(const CString &sText, int nTotalTabLength)
   {
      std::list<CString> lstRet;
      CString strTemp = sText;
      while(!strTemp.IsEmpty())
      {
         CString strItem = strTemp.SpanExcluding(_T("\r\n"));
         
         lstRet.push_back(strItem);

         strTemp = strTemp.Right(strTemp.GetLength() - strItem.GetLength() - 2);
      }

      return lstRet;
   }

   static CString FormatStringWithinCharSingleLine(const CString &sText, TCHAR cOuterChar, int nTotalTabLength)
   {
      CString sRetFormat;

      int nCurLineCount = 0; //全角算2个
      CString sCurLine;
      for(LPCTSTR p= sText; p != NULL && p[0] != 0; p = CharNext(p))
      {
         int nAddCount;
         if(p[0] > 0 && p[0] <= 127)
         {
            nAddCount = 1;
         }
         else 
         {
            //是中文文字
            nAddCount = 2;
         }

         if (nCurLineCount + nAddCount > nTotalTabLength)
         {
            if (!sRetFormat.IsEmpty())
               sRetFormat.AppendChar(_T('\n'));
            sRetFormat.AppendChar(cOuterChar);
            sRetFormat.Append(sCurLine);

            int nRightSpace = nTotalTabLength - nCurLineCount;
            while(nRightSpace > 0)
            {
               sRetFormat.AppendChar(_T(' '));
               --nRightSpace;
            }

            sRetFormat.AppendChar(cOuterChar);

            sCurLine.Empty();
            nCurLineCount = 0;
         }
         nCurLineCount += nAddCount;
         sCurLine.AppendChar(p[0]);
      }

      if (!sCurLine.IsEmpty())
      {
         if (!sRetFormat.IsEmpty())
            sRetFormat.AppendChar(_T('\n'));
         sRetFormat.AppendChar(cOuterChar);
         sRetFormat.Append(sCurLine);

         int nRightSpace = nTotalTabLength - nCurLineCount;
         while(nRightSpace > 0)
         {
            sRetFormat.AppendChar(_T(' '));
            --nRightSpace;
         }

         sRetFormat.AppendChar(cOuterChar);
      }

      return sRetFormat;
   }

   CString FormatStringWithinChar(const CString &sText, TCHAR cOuterChar, int nTotalTabLength)
   {
      CString sRet;
      auto lst = SplitStringToLines(sText, nTotalTabLength);
      for (auto Iter = lst.begin(); Iter != lst.end(); ++Iter)
      {
         if (!sRet.IsEmpty())
            sRet += _T("\n");
         sRet += FormatStringWithinCharSingleLine(*Iter, cOuterChar, nTotalTabLength);
      }
      return sRet;
   }

   void UNICODE_TO_UTF8(const std::wstring& uni_str, std::vector<char>& utf8_str)
   {
      long  l_l_Len  = WideCharToMultiByte(
         CP_UTF8,
         NULL,
         uni_str.c_str(),
         -1,
         NULL,
         0,
         NULL,
         FALSE ); 

      utf8_str.assign(l_l_Len+1, 0);

      // 转换字符集编码格式从UTF8到Unicode
      WideCharToMultiByte(
         CP_UTF8,
         NULL,
         uni_str.c_str(),
         -1,
         utf8_str.data(),
         l_l_Len,
         NULL,
         FALSE );

      utf8_str[l_l_Len] = '\0'; 
   }

   std::vector<char> UNICODE_TO_UTF8(CStringW strIn)
   {
      std::wstring strwstr(strIn.GetBuffer());
      std::vector<char> strOut;
      QLChat::UNICODE_TO_UTF8(strwstr,strOut);
      return strOut;
   }

   void UTF8_TO_UNICODE(const char *utf8_str, std::vector<WCHAR> &uni_str)
   {
      int nUTF8Len = strlen(utf8_str);
      long  l_l_Len  = MultiByteToWideChar( 
         CP_UTF8,
         0,
         utf8_str,
         nUTF8Len,
         NULL,
         0 ); 

      // 申请存储Unicode代码的字符串所需要的内存
      //wchar_t*  l_p_afterchange = new wchar_t[l_l_Len+1];
      uni_str.assign(l_l_Len+1, 0);

      // 转换字符集编码格式从UTF8到Unicode
      MultiByteToWideChar(
         CP_UTF8,
         0,
         utf8_str,
         nUTF8Len,
         uni_str.data(),
         l_l_Len );  

      uni_str[l_l_Len] = L'\0'; 
   }

   CStringW UTF8_TO_UNICODE(const char *utf8_str)
   {
      std::vector<WCHAR> strOut;
      UTF8_TO_UNICODE(utf8_str, strOut);
      return CStringW(strOut.data());
   }
}