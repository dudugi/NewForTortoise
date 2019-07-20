#pragma once
/********************************************************************
//  作者:           linyp
//  CopyRight(c)    2014 Burnon All Rights Reserved 
//  创建时间:       2014/04/09 11:16
//  类描述:         string 类型操作相关公共函数
//  修改时间:       
//  修改目的:       
*********************************************************************/
#include <string>
#include <rnmacro.h>

//空字符串
#define  TNULL   _T("")
#define  ANULL	  ""
#define  SZNULL   ''

//点号
#define  STR_POINT	_T(".")
//斜杠号
#define  STR_SLANT	_T("\\")


#ifdef _UNICODE
typedef	std::wstring  tstring;
#else
typedef	std::string   tstring;
#endif

//语句转化为字符串
#define Change2Str(e) #e

/*
   1. CoverVectorToStr 将vector<UINT>类型的数据转换为 字符串“1,2,2,3”的形式
   2. CoverStrToVector 将字符串“1,2,2,3”的形式转换为vector<UINT>类型的数据格式
   3. CoverBIT16ToStr  将16位的二进制数转换为对应的10进制数据字符串   
*/


#define TO_NAME_W_(str) L#str
#define TO_NAME_A_(str) #str

#ifdef UNICODE
#define _VARIABLE_TO_NAME  TO_NAME_W_
#else
#define _VARIABLE_TO_NAME  TO_NAME_A_
#endif // !UNICODE


namespace RnString
{//字符串操作的命名空间

    //************************************
   // 函数名:  [CoverVectorToStr]
   // 返回值:  [CString]   
   // 参数:    [const VEC_UNITS & ndata]    
   // 函数描述:将vector<UINT>类型的数据转换为 字符串“1,2,2,3”的形式
   // 作者:    linyp 2011/10/08 17:58
   // 修改时间:
   // 修改目的:
   //************************************
   inline CString CoverVectorToStr(const VEC_UNITS &ndata)
   {
      CString strTemp = _T("");   
      if (ndata.empty())
      {
         return strTemp;
      }
      VEC_UNITS::const_iterator iter;
      iter = ndata.begin();
      for (;iter != ndata.end();++iter)
      {
         CString strData;
         strData.Format(_T("%d"),(*iter));
         strTemp += strData;
         if (iter+1 != ndata.end())
         {
            strTemp +=_T(",");
         }
      } 
      return strTemp;
   };


   //************************************
   // 函数名:  [CoverStrToVector]
   // 返回值:  [VEC_UNITS]   
   // 参数:    [CString strTemp]    
   // 函数描述::将字符串“1,2,2,3”的形式转换为vector<UINT>类型的数据格式
   // 作者:    linyp 2011/10/08 17:59
   // 修改时间:
   // 修改目的:
   //************************************
   inline VEC_UNITS CoverStrToVector(CString strTemp)
   {
      VEC_UNITS ndata;
      while(strTemp.Find(',') !=-1)
      {
         int nFind = strTemp.Find(',');
         if(strTemp.Left(nFind)!=_T(""))
            ndata.push_back(_ttoi(strTemp.Left(nFind)));
         strTemp=strTemp.Mid(nFind+1);
      }
      ndata.push_back(_ttoi(strTemp));
      return ndata;
   }

   //************************************
   // 函数名:  [CoverBIT16ToStr]
   // 返回值:  [CString]   
   // 参数:    [BIT16 nbit]    
   // 函数描述:将16位的二进制数转换为对应的10进制数据字符串
   // 作者:    linyp 2011/10/08 18:00
   // 修改时间:
   // 修改目的:
   //************************************
   inline CString CoverBIT16ToStr(BIT16 nbit)
   {
      CString strTemp = L"";
      int bitvalue = 0;
      for(int j = 0;j < 16; ++j)
      {
         int ibitv = 1;
         for(int k = 0 ;k < j;++k) ibitv *= 2;
         bitvalue += (int)nbit[j]* ibitv;
      }
      strTemp.Format(L"%d",bitvalue);
      return strTemp;
   }

	inline LPTSTR _tCharAlloc(UINT uSize)
   {
      return (LPTSTR)malloc(sizeof(TCHAR) * uSize);
   }
   inline VOID _tCharFree(LPVOID p)
   {
      free(p);
   }

	/*-------------------------------------------------------------------
	-@brief [数字字符串的规范化，比如0011-->11、11.100 ->11.1  .1100->0.11]
	-
	-[函数详细描述]
	-@n<b>函数名称</b>      : RegularNumberStr
	-@n@param CString & str : [数字字符串]
	-@return                  [返回值描述]
	-@see                     [参见函数]
	-@n<b>作者</b>          :  
	-@n<b>创建时间</b>      : 2009-4-13 13:54:31
	-@version    修改者        时间        描述@n
	-@n                     2009-04-13  [描述]
	--------------------------------------------------------------------*/
	inline void RegularNumberStr(CString& m_strInput)
	{
		int nLen = m_strInput.GetLength();
		if(nLen == 0)
		{
			return;
		}

		int i = 0;

		for( i = 0; i < nLen; i++ )
		{
			//直到第一个不是0的字符
			if( m_strInput[i] != '0' ) 
			{
				break;
			}
		}
		
		if( i < nLen ) 
		{//不是全0的情况
			// 将第一个非0字符前面的0去掉
			m_strInput = m_strInput.Mid(i); 
			nLen = m_strInput.GetLength();
			int nDotPos = m_strInput.Find('.'); 

			//含有小数点
			if( nDotPos != -1 ) 
			{
				for( i = nLen - 1; i >= 0; i-- )
				{
					if( m_strInput[i] != '0' )
					{
						break;
					}
				}

				//去掉小数后面的0
				m_strInput = m_strInput.Left(i + 1); 
			}

			//更新字符串的长度
			nLen = m_strInput.GetLength();

			//小数点在最后
			if( nDotPos == nLen - 1 ) 
			{
				m_strInput = m_strInput.Left(nLen - 1);
			}
			//小数点在最开始
			if( nDotPos == 0 ) 
			{
				m_strInput = _T("0") + m_strInput;
			}
		}
		else 
		{//全0的情况
			m_strInput = _T("0");
		}//end of if( i < nLen ) 	

	}//end of func


	/*-------------------------------------------------------------------
	-@brief [点号之后的位数]
	-
	-[函数详细描述]
	-@n<b>函数名称</b>    : CountAfterPoint
	-@n@param CString str : [数值字符串]
	-@return                [-1表示无点号， 大于0值为点号后面的位数]
	-@see                   [参见函数]
	-@n<b>作者</b>        :  
	-@n<b>创建时间</b>    : 2009-4-14 10:27:13
	-@version    修改者        时间        描述@n
	-@n                     2009-04-14  [描述]
	--------------------------------------------------------------------*/
	inline int CountAfterPoint(CString str)
	{
		//默认无点号
		int nResult(-1);
		
		//点号在0序中的位置
		int nPointer = str.Find('.');
		bool bFind = NOT_EQUAL(-1, nPointer);

		if (bFind)
		{
			int nLength = str.GetLength();
			ASSERT(nLength > nPointer);
			nResult = nLength - nPointer - 1;
		}

		return nResult;
	}//end of func


	/*-------------------------------------------------------------------
	-@brief [点号之前的位数]
	-
	-[函数详细描述]
	-@n<b>函数名称</b>    : CountBeforePoint
	-@n@param CString str : [数值字符串]
	-@return                [点号之前的位数数目]
	-@see                   [参见函数]
	-@n<b>作者</b>        :  
	-@n<b>创建时间</b>    : 2009-4-14 10:42:46
	-@version    修改者        时间        描述@n
	-@n                     2009-04-14  [描述]
	--------------------------------------------------------------------*/
	inline unsigned int CountBeforePoint(CString str)
	{
		unsigned int nResult(str.GetLength());

		int nPointer = str.Find('.');
		bool bFind = NOT_EQUAL(-1, nPointer);

		if (bFind)
		{
			unsigned int nLength = str.GetLength();
			ASSERT(nLength >= nPointer);
			nResult = nPointer;
		}

		return nResult;
	}//end of func

  
   /*-------------------------------------------------------------------
   -@brief [UTF8字符转换为Unicode字符]
   -
   -[函数详细描述]
   -@n<b>函数名称</b> : UTF8_TO_UNICODE
   -@n@param const std::string utf8_str : [需要转换的字符串]
   -@param   std::wstring &     uni_str : [转换后的字符串]
   -@see                [参见函数]
   -@n<b>作者</b>     :  
   -@n<b>创建时间</b> : 2009-1-21 16:20:04
   -@version    修改者        时间        描述@n
   -@n                     2009-01-21  [描述]
   --------------------------------------------------------------------*/
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
   inline CStringW UTF8_TO_UNICODE(const std::string utf8_str)
   {
      std::wstring strOut;
      UTF8_TO_UNICODE(utf8_str,strOut);
      return CStringW(strOut.c_str());
   }
   inline std::wstring Str2WStrUTF8(const std::string utf8_str)
   {
      std::wstring strTemp;
      UTF8_TO_UNICODE(utf8_str,strTemp);
      return strTemp;
   }
   /*-------------------------------------------------------------------
   -@brief [ACP字符转换为Unicode字符]
   -
   -[函数详细描述]
   -@n<b>函数名称</b> : ACP_TO_UNICODE
   -@n@param const std::string acp_str : [需要转换的字符串]
   -@param   std::wstring &    uni_str : [转换后的字符串]
   -@see                [参见函数]
   -@n<b>作者</b>     :lixf
   -@n<b>创建时间</b> : 2008.08.12
   -@version    修改者        时间        描述@n
   -@n                     2009-01-21  [描述]
   --------------------------------------------------------------------*/
   inline void ACP_TO_UNICODE(const std::string acp_str,std::wstring& uni_str)
   {
      long  l_l_Len  = MultiByteToWideChar(
         CP_ACP,
         0,
         acp_str.c_str(),
         static_cast<int>( acp_str.length() ),
         NULL,
         0 ); 

      // 申请存储Unicode代码的字符串所需要的内存
      wchar_t*  l_p_afterchange = new wchar_t[l_l_Len+1];

      // 转换字符集编码格式从UTF8到Unicode
      MultiByteToWideChar(
         CP_ACP,
         0,
         acp_str.c_str(),
         static_cast<int>( acp_str.length() ),
         l_p_afterchange,
         l_l_Len );  

      l_p_afterchange[l_l_Len] = L'\0'; 
      uni_str = std::wstring(l_p_afterchange);
      delete[] l_p_afterchange;
   }

   /*-------------------------------------------------------------------
   -@brief [Unicode字符转换为UTF8字符]
   -
   -[函数详细描述]
   -@n<b>函数名称</b> : UNICODE_TO_UTF8
   -@n@param const std::wstring & uni_str : [需要转换的字符串]
   -@param   std::string &       utf8_str : [转换后的字符串]
   -@see                [参见函数]
   -@n<b>作者</b>     :lixf
   -@n<b>创建时间</b> : 2008.08.12
   -@version    修改者        时间        描述@n
   -@n                     2009-01-21  [描述]
   --------------------------------------------------------------------*/
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
   inline std::string UNICODE_TO_UTF8(CStringW strIn)
   {
      std::wstring strwstr(strIn.GetBuffer());
      std::string strOut;
      UNICODE_TO_UTF8(strwstr,strOut);
      return strOut;
   }
   /*-------------------------------------------------------------------
   -@brief [Unicode字符转换为ACP字符]
   -
   -[函数详细描述]
   -@n<b>函数名称</b> : UNICODE_TO_ACP
   -@n@param const std::wstring & uni_str : [需要转换的字符串]
   -@param   std::string &        acp_str : [转换后的字符串]
   -@see                [参见函数]
   -@n<b>作者</b>     :lixf
   -@n<b>创建时间</b> : 2008.08.12
   -@version    修改者        时间        描述@n
   -@n                     2009-01-21  [描述]
   --------------------------------------------------------------------*/
   inline void UNICODE_TO_ACP(const std::wstring& uni_str,std::string& acp_str)
   {
      long l_l_Len = WideCharToMultiByte(
         CP_ACP,
         NULL,
         uni_str.c_str(),
         -1,
         NULL,
         0,
         NULL,
         FALSE ); 

      // 申请存储Unicode代码的字符串所需要的内存
      char* l_p_afterchange = new char[l_l_Len+1];

      // 转换字符集编码格式从UTF8到Unicode
      WideCharToMultiByte(
         CP_ACP,
         NULL,
         uni_str.c_str(),
         -1,
         l_p_afterchange,
         l_l_Len,
         NULL,
         FALSE );

      l_p_afterchange[l_l_Len] = '\0'; 
      acp_str = std::string(l_p_afterchange);
      delete[] l_p_afterchange;
   }

   inline CStringW Char2WChar( const char* szStr )
   {
      CStringW wStr;
      if( NULL == szStr )
      {
         return wStr;
      }
      int nLen = ::MultiByteToWideChar( CP_ACP, 0, szStr, -1, NULL,0);
      wchar_t* p = wStr.GetBuffer( nLen+10 );
      wmemset( p, 0, nLen+10 );
      nLen = ::MultiByteToWideChar( CP_ACP,0,szStr,-1,p,nLen);
      wStr.ReleaseBuffer();
      return wStr;
   }

   /*-------------------------------------------------------------------
   -@brief [ACP字符转换为UTF8字符]
   -
   -[函数详细描述]
   -@n<b>函数名称</b> : ACP_TO_UTF8
   -@n@param const std::string acp_str : [需要转换的字符串]
   -@param  std::string &     utf8_str : [转换后的字符串]
   -@see                [参见函数]
   -@n<b>作者</b>     :lixf
   -@n<b>创建时间</b> : 2008.08.12
   -@version    修改者        时间        描述@n
   -@n                     2009-01-21  [描述]
   --------------------------------------------------------------------*/
   inline void ACP_TO_UTF8(const std::string acp_str,std::string& utf8_str)
   {
      std::wstring uni_str;
      ACP_TO_UNICODE(acp_str,uni_str);
      UNICODE_TO_UTF8(uni_str,utf8_str);
   }

   /*-------------------------------------------------------------------
   -@brief [STL宽字符串 转换为 STL窄ACP字符串]
   -
   -[函数详细描述]
   -@n<b>函数名称</b>: Wstr2Str
   -@n@param std::wstring & wstr : [STL宽字符串]
   -@return            [STL窄ACP字符串]
   -@see               [参见函数]
   -@n<b>作者</b>    :  
   -@n<b>创建时间</b>: 2009-2-9 15:13:57
   -@version    修改者        时间        描述@n
   -@n                     2009-02-09  [描述]
   --------------------------------------------------------------------*/
   inline std::string Wstr2Str( std::wstring& wstr )
   {
      std::string strA = ANULL;
      UNICODE_TO_ACP( wstr, strA );

      return strA;
   }

   /*-------------------------------------------------------------------
   -@brief [STL宽字符串 转换为 STL窄UTF8字符串]
   -
   -[函数详细描述]
   -@n<b>函数名称</b>: Wstr2StrUTF8
   -@n@param std::wstring & wstr : [STL宽字符串]
   -@return            [STL窄UTF8字符串]
   -@see               [参见函数]
   -@n<b>作者</b>    :  
   -@n<b>创建时间</b>: 2009-2-9 15:24:27
   -@version    修改者        时间        描述@n
   -@n                     2009-02-09  [描述]
   --------------------------------------------------------------------*/
   inline std::string Wstr2StrUTF8_1( std::wstring& wstr )
   {
      std::string strUTF8 = ANULL;
      UNICODE_TO_UTF8( wstr, strUTF8 );

      return strUTF8;
   }
   inline std::string WCStr2StrACP( const CString & wstr )
   {
      CString strTemp = wstr;
      std::wstring strw = strTemp.GetBuffer();
      strTemp.ReleaseBuffer();
      std::string strUTF8 = ANULL;
      UNICODE_TO_ACP(strw, strUTF8 );
      return strUTF8;
   }
   inline CStringA WChar2Char( const wchar_t* wszStr )
   {
      CStringA cStr;
      if( NULL == wszStr )
      {
         return cStr;
      }
      int iSize = ::WideCharToMultiByte(  CP_ACP, 0, wszStr, -1, NULL, 0, NULL,NULL );
      char* p = cStr.GetBuffer( iSize + 10 );
      memset( p, 0, iSize+10);
      iSize = ::WideCharToMultiByte( CP_ACP, 0, wszStr, -1, p, iSize,  NULL, NULL);
      cStr.ReleaseBuffer();
      return cStr;
   }

   inline CStringW Char2WCharACP( const char* szStr )
   {
      CStringW wStr;
      if( NULL == szStr )
      {
         return wStr;
      }
      int nLen = ::MultiByteToWideChar( CP_ACP, 0, szStr, -1, NULL,0);
      wchar_t* p = wStr.GetBuffer( nLen+10 );
      wmemset( p, 0, nLen+10 );
      nLen = ::MultiByteToWideChar( CP_ACP,0,szStr,-1,p,nLen);
      wStr.ReleaseBuffer();
      return wStr;
   }
   inline CStringW Char2WCharUTF8( const char* szStr )
   {
      CStringW wStr;
      if( NULL == szStr )
      {
         return wStr;
      }
      int nLen = ::MultiByteToWideChar( CP_UTF8, 0, szStr, -1, NULL,0);
      wchar_t* p = wStr.GetBuffer( nLen+10 );
      wmemset( p, 0, nLen+10 );
      nLen = ::MultiByteToWideChar( CP_UTF8,0,szStr,-1,p,nLen);
      wStr.ReleaseBuffer();
      return wStr;
   }

#pragma region //数字字符串互转
    /*-------------------------------------------------------------------
   -@brief [int转换为CString]
   -
   -[函数详细描述]
   -@n<b>函数名称</b> : IntToCStr
   -@n@param int nVal : [要转换为字符串的int值]
   -@return             [结果字符串]
   -@see                [参见函数]
   -@n<b>作者</b>     :  
   -@n<b>创建时间</b> : 2009-1-21 17:07:51
   -@version    修改者        时间        描述@n
   -@n                     2009-01-21  [描述]
   --------------------------------------------------------------------*/
   inline CString IntToCStr( int nVal )
   {
      CString str = _T("");
      str.Format( _T("%d"), nVal );

      return str;
   }

   /*-------------------------------------------------------------------
   -@brief [double转换为CString]
   -
   -[函数详细描述]
   -@n<b>函数名称</b>                 : DouToCStr
   -@n@param double       dVal        : [要转换为字符串的double值]
   -@param   unsigned int nAll        : [结果字符串的长度]
   -@param   unsigned int nAfterPoint : [结果字符串小数点后的位数]
   -@return                             [结果字符串]
   -@see                                [参见函数]
   -@n<b>作者</b>                     :  
   -@n<b>创建时间</b>                 : 2009-1-21 17:08:31
   -@version    修改者        时间        描述@n
   -@n                     2009-01-21  [描述]
   --------------------------------------------------------------------*/
   inline CString DouToCStr(				
      double dVal,  
      unsigned int nAll = 4, 
      int nAfterPoint = 2
      )
   {
      CString str = TNULL;
      CString strAll = TNULL;
      CString strAfterPoint = TNULL;
      strAll.Format( _T("%d"), nAll );
      strAfterPoint.Format( _T("%d"), nAfterPoint );

      CString strPoint = _T(".");
      CString strUnit = _T("%");
      CString strFormat = _T("lf");

      if (nAfterPoint >=  0) {
         //浮点输出
         strAll = strUnit + strAll + strPoint + strAfterPoint + strFormat;
      } else {
         //整型输出
         strAll = strUnit + strAll + _T(".0lf");
      }

      str.Format( strAll, dVal );

      if ( IS_ZERO(nAfterPoint) )
      {
         str = str + STR_POINT;
      }

      return str;
   }

   inline int CStr2Int(CStringA &strInt)
   {
      return atoi(strInt);
   }

   inline int CStr2Int(CStringW &strInt)
   {
      return _wtoi(strInt);
   }

   inline float CStr2Float(CStringA &strInt)
   {
      return atof(strInt);
   }

   inline float CStr2Float(CStringW &strInt)
   {
      return _wtof(strInt);
   }



   inline bool IsTextUTF8(const char* str,long length)
   {
      int i;
      int nBytes=0;//UFT8可用1-6个字节编码,ASCII用一个字节
      unsigned char chr;
      bool bAllAscii=true; //如果全部都是ASCII, 说明不是UTF-8
      for(i=0;i<length;i++)
      {
         chr= *(str+i);
         if( (chr&0x80) != 0 ) // 判断是否ASCII编码,如果不是,说明有可能是UTF-8,ASCII用7位编码,但用一个字节存,最高位标记为0,o0xxxxxxx
            bAllAscii= false;
         if(nBytes==0) //如果不是ASCII码,应该是多字节符,计算字节数
         {
            if(chr>=0x80)
            {
               if(chr>=0xFC&&chr<=0xFD)
                  nBytes=6;
               else if(chr>=0xF8)
                  nBytes=5;
               else if(chr>=0xF0)
                  nBytes=4;
               else if(chr>=0xE0)
                  nBytes=3;
               else if(chr>=0xC0)
                  nBytes=2;
               else
               {
                  return false;
               }
               nBytes--;
            }
         }
         else //多字节符的非首字节,应为 10xxxxxx
         {
            if( (chr&0xC0) != 0x80 )
            {
               return false;
            }
            nBytes--;
         }
      }

      if( nBytes > 0 ) //违返规则
      {
         return false;
      }

      if( bAllAscii ) //如果全部都是ASCII, 说明不是UTF-8
      {
         return false;
      }
      return true;
   }

	//获取GUID字符串		by WangZY 2016/06/21
	inline CString GetGuidString(CString strFormat = _T("{%X-%X-%x-%X%X-%X%X%X%X%X%X}"))
	{
		CString strBuf;
		GUID guid;
		
		if (strFormat.IsEmpty())
		{
			strFormat = _T("{%X-%X-%x-%X%X-%X%X%X%X%X%X}");
		}
		
		if (S_OK == ::CoCreateGuid(&guid))
		{
			strBuf.Format(strFormat
				, guid.Data1
				, guid.Data2
				, guid.Data3
				, guid.Data4[0], guid.Data4[1]
			, guid.Data4[2], guid.Data4[3], guid.Data4[4], guid.Data4[5]
			, guid.Data4[6], guid.Data4[7]);
		}

		return strBuf;
	}
   //删除字符串末尾没用的0 yangjr 2018/7/25
   inline CString RemoveLastZero(CString numstr)
   {
      CString tmpStr = numstr;
      if ( -1 == tmpStr.Find('.'))
      {
         return tmpStr;
      } 
      int length = tmpStr.GetLength();
      for (int i = length - 1; i > 0; --i)
      {
         if ('\0' == tmpStr[i])
         {
            continue;
         }
         else if ('0' == tmpStr[i])
         {
            tmpStr.SetAt(i,'\0');
         }
         else if ('.' == tmpStr[i])// 小数点之后全为零
         {
            tmpStr.SetAt(i,'\0');
            break;
         }
         else// 小数点后有非零数字
         {
            break;
         }
      }
      return tmpStr;
   }

#pragma endregion
}//end of namespace MyString

