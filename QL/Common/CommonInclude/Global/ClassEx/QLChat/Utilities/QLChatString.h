#pragma  once
/*************************************************
// <�ļ�>: QLChatString.h
// <˵��>: qlchat�ַ������ͨ�ýӿ�
// <����>: duchen
// <����>: 2019/02/22
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 

#include "stdafx.h"
#include <string>
#include <vector>
namespace QLChat
{
   CString GetPathExtUpper(const CString &sPath); //��ȡ·����׺����ת�ɴ�д
   CString GetPathFolderUpper(const CString &sPath); //��ȡ·�����ļ��в�ת�ɴ�д
   void GetPathExtAndNameUpper(const CString &sPath, CString *psExt, CString *psName); //��ȡ·���ĺ�׺�����ļ�����ת�ɴ�д
   CString GetPathExtNameUpper(const CString &sPath); //��ȡ·���ļ�����ת�ɴ�д
   void GetPathWithOutExtUpper(const CString &sPath, CString *psName); //��ȡ·����ȥ����׺�Ĳ���

   template <typename TIter>
   extern CString JoinString(TIter IterBegin, TIter IterEnd, TCHAR cSeparator = _T('|')); //��cSeparator���ӵ������е��ַ���
   template <typename TIter>
   CString JoinString(TIter IterBegin, TIter IterEnd, const CString &sSeparator);

   CString FormatStringPadRight(const CString &sText, int nTotalLength); //��ʽ���ַ�����nTotalLength������ַ��ĳ��ȣ����Ʊ������
   CString FormatStringPadRightWithSpace(const CString &sText, int nTotalTabLength); //��ʽ���ַ�����nTotalLength������ַ��ĳ��ȣ����Ʊ������
   CString FormatStringWithinChar(const CString &sText, TCHAR cOuterChar, int nTotalTabLength); //��ʽ���ַ�����nTotalLength������ַ��ĳ��ȣ��ÿո񲹳�
   BOOL IsSoundFileExtName(const CString &sExtName); //�ж��ǲ��������ļ��ĺ�׺������.)
   void UNICODE_TO_UTF8(const std::wstring& uni_str, std::vector<char>& utf8_str); //unicodeתutf8
   std::vector<char> UNICODE_TO_UTF8(CStringW strIn); //unicodeתutf-8
   void UTF8_TO_UNICODE(const char *utf8_str,std::vector<WCHAR> &uni_str); //utf8תunicode
   CStringW UTF8_TO_UNICODE(const char *utf8_str); //utf8תunicode

   template <typename TIter>
   CString JoinString(TIter IterBegin, TIter IterEnd, TCHAR cSeparator) //��cSeparator���ӵ������е��ַ���
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
   CString JoinString(TIter IterBegin, TIter IterEnd, const CString &sSeparator) //��cSeparator���ӵ������е��ַ���
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