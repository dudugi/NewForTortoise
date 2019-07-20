
// XmlToFunc.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CXmlToFuncApp:
// 有关此类的实现，请参阅 XmlToFunc.cpp
//

class CXmlToFuncApp : public CWinApp
{
public:
	CXmlToFuncApp();

   std::string UNICODE_TO_UTF8(CStringW strIn)
   {
      std::wstring strwstr(strIn.GetBuffer());
      std::string strOut;
      UNICODE_TO_UTF8(strwstr,strOut);
      return strOut;
   }

   CString UTF8_TO_UNICODE(const std::string utf8_str)
   {
      std::wstring strOut;
      UTF8_TO_UNICODE(utf8_str,strOut);
      return CString(strOut.c_str());
   }

private:
   inline void UNICODE_TO_UTF8(const std::wstring& uni_str, std::string& utf8_str)
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

      // 申请存储Unicode代码的字符串所需要的内存
      char*  l_p_afterchange = new char[l_l_Len+1];

      // 转换字符集编码格式从UTF8到Unicode
      WideCharToMultiByte(
         CP_UTF8,
         NULL,
         uni_str.c_str(),
         -1,
         l_p_afterchange,
         l_l_Len,
         NULL,
         FALSE );

      l_p_afterchange[l_l_Len] = '\0'; 
      utf8_str = std::string(l_p_afterchange);
      delete[] l_p_afterchange;
   }

   inline void UTF8_TO_UNICODE(const std::string utf8_str,std::wstring& uni_str)
   {
      long  l_l_Len  = MultiByteToWideChar( 
         CP_UTF8,
         0,
         utf8_str.c_str(),
         static_cast<int>( utf8_str.length() ),
         NULL,
         0 ); 

      // 申请存储Unicode代码的字符串所需要的内存
      wchar_t*  l_p_afterchange = new wchar_t[l_l_Len+1];

      // 转换字符集编码格式从UTF8到Unicode
      MultiByteToWideChar(
         CP_UTF8,
         0,
         utf8_str.c_str(),
         static_cast<int>( utf8_str.length() ),
         l_p_afterchange,
         l_l_Len );  

      l_p_afterchange[l_l_Len] = L'\0'; 
      uni_str = std::wstring(l_p_afterchange);
      delete[] l_p_afterchange;
   }

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CXmlToFuncApp theApp;