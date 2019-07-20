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
#include<algorithm>

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

   //数字金额字符串转大写字符串
   inline CStringW NumStrToDaXieStr(const CStringW &numStr)
   {
      CString szRMB = _T("");	
      CStringW numStrTmp = numStr;
      BOOL bFuFlag = FALSE;
      if (_ttof(numStrTmp)<0)
      {
         bFuFlag = TRUE;
         numStrTmp.Format(_T("%.2f"),abs(_ttof(numStrTmp)));
      }
      int pos = numStrTmp.Find(_T("."));
      CString szInteger, szFloat;	
      if (pos != -1)	
      {		
         szInteger = numStrTmp.Left(pos);		
         szFloat = numStrTmp.Mid(pos+1);		
         if (szFloat.GetLength() > 2)		
         {			
            szFloat = szFloat.Left(2);		
         }	
      }else
      {
         szInteger = numStrTmp;	
      } 	
      CString szNumberSeed = _T("零壹贰叁肆伍陆柒捌玖");	
      CString szRMBSeed = _T("元拾佰仟万拾佰仟亿拾佰仟万");	
      LPCTSTR lpInteger = (LPCTSTR)szInteger; 	
            
      bool bZeroJiao = false;
      bool bZeroFen = false;
      LPCTSTR lpFloat = (LPCTSTR)szFloat;

      char cNumberJiao = lpFloat[0];		
      int nNumberJiao = atoi(&cNumberJiao);	
      if (0 == nNumberJiao) //0角
      {
         bZeroJiao = true;
      }

      char cNumberFen = lpFloat[1];		
      int nNumberFen = atoi(&cNumberFen);	
      if (0 == nNumberFen) //0分
      {
         bZeroFen = true;
      }
          
      //0.XX的处理返回X角X分
      if (1 == szInteger.GetLength())
      {
         char cNumber = lpInteger[0];		
         int nNumber = atoi(&cNumber);
         if (0 == nNumber)//0元
         {            
            if (bZeroJiao)//0角
            {
               if (bZeroFen)//0分
               {
                  szRMB +=_T("零元整"); //0.00 返回零元整                 
               }else
               {
                  szRMB += szNumberSeed.Mid(nNumberFen, 1) + _T("分"); //0.01 返回壹分
               }   
            }
            else
            {
               szRMB += szNumberSeed.Mid(nNumberJiao, 1) + _T("角");
               if (bZeroFen)//0分
               {
                  szRMB +=_T("整"); //0.30 返回3角整                 
               }else
               {
                  szRMB += szNumberSeed.Mid(nNumberFen, 1) + _T("分");
               }               
            }  
            if (bFuFlag)
            {
               szRMB = _T("负")+szRMB;
            }
            return szRMB;	
         }
      }
      //有元以上金额的处理
      int iAllCount = szInteger.GetLength(); //总位数 
      int iCount = iAllCount-1;
      bool bZeroFlag = false;
      for (int i=0;i<iAllCount;++i)	
      {		
         char cNumber = lpInteger[i];		
         int nNumber = atoi(&cNumber);
         CString strDanWei = szRMBSeed.Mid(iCount,1);//单位
         CString strNumValue = szNumberSeed.Mid(nNumber, 1);
         if (0 == nNumber)
         {
            if (_T("元") ==strDanWei || _T("万") ==strDanWei || _T("亿") ==strDanWei)
            {
               szRMB += strDanWei;
               bZeroFlag = false;
            }else
            {
               bZeroFlag = true;
            }
         }else
         {            
            if (bZeroFlag)
            {//上一个为0,则需要加上零
               szRMB += _T("零");        
            }
            szRMB += strNumValue+strDanWei;
            bZeroFlag = false;
         }         	
         iCount--;	
      }

      if (bZeroJiao)//0角
      {
         if (bZeroFen)//0分
         {
            szRMB +=_T("整"); // 返回整                 
         }else
         {
            szRMB += _T("零") + szNumberSeed.Mid(nNumberFen, 1) + _T("分"); // 返回零X分
         }   
      }
      else
      {
         szRMB += szNumberSeed.Mid(nNumberJiao, 1) + _T("角");
         if (bZeroFen)//0分
         {
            szRMB +=_T("整"); //0.30 返回3角整                 
         }else
         {
            szRMB += szNumberSeed.Mid(nNumberFen, 1) + _T("分");
         }
      }

      if (bFuFlag)
      {
         szRMB = _T("负")+szRMB;
      }
      return szRMB; 	 
   }

   //去除字符串中的符号
   inline string RemoveSymbolFromStr(const string szStr)
   {
      string str_src = szStr;
      str_src.erase( 
         remove_if ( str_src.begin(), str_src.end(), static_cast<int(*)(int)>(&ispunct) ), 
         str_src.end()); 

      str_src.erase( 
         remove_if ( str_src.begin(), str_src.end(), static_cast<int(*)(int)>(&isspace) ), 
         str_src.end());

      return str_src;
   };

   //金额转汉字大写 的接口  	by WangZY 2019/03/20
   inline CString NewMoneyToUpper(CString strLowerMoney)
   {
      std::map<CString,CString> mapValue;
      mapValue[_T(".")] = _T("圆");
      mapValue[_T("0")] = _T("零");
      mapValue[_T("1")] = _T("壹");
      mapValue[_T("2")] = _T("贰");
      mapValue[_T("3")] = _T("叁");
      mapValue[_T("4")] = _T("肆");
      mapValue[_T("5")] = _T("伍");
      mapValue[_T("6")] = _T("陆");
      mapValue[_T("7")] = _T("柒");
      mapValue[_T("8")] = _T("捌");
      mapValue[_T("9")] = _T("玖");


      CString strReturnValue;
      bool IsNegative = false; // 是否是负数
      strLowerMoney.Trim();
      if (strLowerMoney.Left(1) == _T("-"))
      {
         // 是负数则先转为正数
         strLowerMoney.Replace(_T("-"),_T(""));
         IsNegative = true;
      }
      CString strLower;
      CString strUpart;
      CString strUpper;
      int iTemp = 0;
      // 保留两位小数 123.489→123.49　　123.4→123.4
      strLowerMoney.Format(_T("%.2f"),_ttof(strLowerMoney));
      if (strLowerMoney.Find(_T(".")) > 0)
      {
         if (strLowerMoney.Find(_T(".")) == strLowerMoney.GetLength() - 2)
         {
            strLowerMoney = strLowerMoney + _T("0");
         }
      }
      else
      {
         strLowerMoney = strLowerMoney + _T(".00");
      }
      strLower = strLowerMoney;
      iTemp = 1;
      strUpper = "";
      while (iTemp <= strLower.GetLength())
      {
         CString strTmp = strLower.Mid(strLower.GetLength() - iTemp, 1);
         auto it = mapValue.find(strTmp);
         if (it != mapValue.end())
         {
            strUpart = it->second;
         }
         else
         {
            strUpart = _T("");
         }

         switch (iTemp)
         {
         case 1:
            strUpart += _T("分");
            break;
         case 2:
            strUpart += _T("角");
            break;
         case 3:
            strUpart += _T("");
            break;
         case 4:
            strUpart += _T("");
            break;
         case 5:
            strUpart += _T("拾");
            break;
         case 6:
            strUpart += _T("佰");
            break;
         case 7:
            strUpart += _T("仟");
            break;
         case 8:
            strUpart += _T("万");
            break;
         case 9:
            strUpart += _T("拾");
            break;
         case 10:
            strUpart += _T("佰");
            break;
         case 11:
            strUpart += _T("仟");
            break;
         case 12:
            strUpart += _T("亿");
            break;
         case 13:
            strUpart += _T("拾");
            break;
         case 14:
            strUpart += _T("佰");
            break;
         case 15:
            strUpart += _T("仟");
            break;
         case 16:
            strUpart += _T("万");
            break;
         default:
            strUpart += _T("");
            break;
         }

         strUpper = strUpart + strUpper;
         iTemp = iTemp + 1;
      }

      strUpper.Replace(_T("零拾"), _T("零"));
      strUpper.Replace(_T("零佰"), _T("零"));
      strUpper.Replace(_T("零仟"), _T("零"));
      strUpper.Replace(_T("零零零"), _T("零"));
      strUpper.Replace(_T("零零"), _T("零"));
      strUpper.Replace(_T("零角零分"), _T("整"));
      strUpper.Replace(_T("零分"), _T("整"));
      strUpper.Replace(_T("零角"), _T("零"));
      strUpper.Replace(_T("零亿零万零圆"), _T("亿圆"));
      strUpper.Replace(_T("亿零万零圆"), _T("亿圆"));
      strUpper.Replace(_T("零亿零万"), _T("亿"));
      strUpper.Replace(_T("零万零圆"), _T("万圆"));
      strUpper.Replace(_T("零亿"), _T("亿"));
      strUpper.Replace(_T("零万"), _T("万"));
      strUpper.Replace(_T("零圆"), _T("圆"));
      strUpper.Replace(_T("零零"), _T("零"));

      // 对壹圆以下的金额的处理
      if (0 == strUpper.Find(_T("圆")))
      {
         strUpper.Replace(_T("圆"),_T(""));
      }
      if (0 == strUpper.Find(_T("零")))
      {
         strUpper.Replace(_T("零"),_T(""));
      }
      if (0 == strUpper.Find(_T("角")))
      {
         strUpper.Replace(_T("角"),_T(""));
      }
      if (0 == strUpper.Find(_T("分")))
      {
         strUpper.Replace(_T("分"),_T(""));
      }
      if (0 == strUpper.Find(_T("整")))
      {
         strUpper = "零圆整";
         IsNegative = false;
      }

      if (IsNegative)
      {
         strReturnValue = _T("负") + strUpper;
      }
      else
      {
         strReturnValue = strUpper;
      }

      return strReturnValue;
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

