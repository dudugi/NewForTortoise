#pragma  once
/*************************************************
// <文件>: QLChatString.h
// <说明>: qlchat字符串相关通用接口
// <作者>: duchen
// <日期>: 2019/02/22
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 

#include "stdafx.h"
#include <string>
#include <vector>
namespace QLChat
{
   CString GetPathExtUpper(const CString &sPath); //获取路径后缀名并转成大写
   CString GetPathFolderUpper(const CString &sPath); //获取路径的文件夹并转成大写
   void GetPathExtAndNameUpper(const CString &sPath, CString *psExt, CString *psName); //获取路径的后缀名和文件名并转成大写
   CString GetPathExtNameUpper(const CString &sPath); //获取路径文件名并转成大写
   void GetPathWithOutExtUpper(const CString &sPath, CString *psName); //获取路径的去除后缀的部分

   template <typename TIter>
   extern CString JoinString(TIter IterBegin, TIter IterEnd, TCHAR cSeparator = _T('|')); //用cSeparator连接迭代器中的字符串
   template <typename TIter>
   CString JoinString(TIter IterBegin, TIter IterEnd, const CString &sSeparator);

   CString FormatStringPadRight(const CString &sText, int nTotalLength); //格式化字符串到nTotalLength个半角字符的长度，用制表符补充
   CString FormatStringPadRightWithSpace(const CString &sText, int nTotalTabLength); //格式化字符串到nTotalLength个半角字符的长度，用制表符补充
   CString FormatStringWithinChar(const CString &sText, TCHAR cOuterChar, int nTotalTabLength); //格式化字符串到nTotalLength个半角字符的长度，用空格补充
   BOOL IsSoundFileExtName(const CString &sExtName); //判断是不是声音文件的后缀名（带.)
   void UNICODE_TO_UTF8(const std::wstring& uni_str, std::vector<char>& utf8_str); //unicode转utf8
   std::vector<char> UNICODE_TO_UTF8(CStringW strIn); //unicode转utf-8
   void UTF8_TO_UNICODE(const char *utf8_str,std::vector<WCHAR> &uni_str); //utf8转unicode
   CStringW UTF8_TO_UNICODE(const char *utf8_str); //utf8转unicode

   template <typename TIter>
   CString JoinString(TIter IterBegin, TIter IterEnd, TCHAR cSeparator) //用cSeparator连接迭代器中的字符串
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

   template <typename TIter>
   CString JoinString(TIter IterBegin, TIter IterEnd, const CString &sSeparator) //用cSeparator连接迭代器中的字符串
   {
      CString sResult;
      for (auto Iter = IterBegin; Iter != IterEnd; ++Iter)
      {
         if (Iter != IterBegin)
         {
            sResult.Append(sSeparator);
         }
         sResult.Append(*Iter);
      }
      return sResult;
   }
}