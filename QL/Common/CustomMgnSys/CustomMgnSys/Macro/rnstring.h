#pragma once
/********************************************************************
//  ����:           linyp
//  CopyRight(c)    2014 Burnon All Rights Reserved 
//  ����ʱ��:       2014/04/09 11:16
//  ������:         string ���Ͳ�����ع�������
//  �޸�ʱ��:       
//  �޸�Ŀ��:       
*********************************************************************/
#include <string>
#include <rnmacro.h>

//���ַ���
#define  TNULL   _T("")
#define  ANULL	  ""
#define  SZNULL   ''

//���
#define  STR_POINT	_T(".")
//б�ܺ�
#define  STR_SLANT	_T("\\")


#ifdef _UNICODE
typedef	std::wstring  tstring;
#else
typedef	std::string   tstring;
#endif

//���ת��Ϊ�ַ���
#define Change2Str(e) #e

/*
   1. CoverVectorToStr ��vector<UINT>���͵�����ת��Ϊ �ַ�����1,2,2,3������ʽ
   2. CoverStrToVector ���ַ�����1,2,2,3������ʽת��Ϊvector<UINT>���͵����ݸ�ʽ
   3. CoverBIT16ToStr  ��16λ�Ķ�������ת��Ϊ��Ӧ��10���������ַ���   
*/


#define TO_NAME_W_(str) L#str
#define TO_NAME_A_(str) #str

#ifdef UNICODE
#define _VARIABLE_TO_NAME  TO_NAME_W_
#else
#define _VARIABLE_TO_NAME  TO_NAME_A_
#endif // !UNICODE


namespace RnString
{//�ַ��������������ռ�

    //************************************
   // ������:  [CoverVectorToStr]
   // ����ֵ:  [CString]   
   // ����:    [const VEC_UNITS & ndata]    
   // ��������:��vector<UINT>���͵�����ת��Ϊ �ַ�����1,2,2,3������ʽ
   // ����:    linyp 2011/10/08 17:58
   // �޸�ʱ��:
   // �޸�Ŀ��:
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
   // ������:  [CoverStrToVector]
   // ����ֵ:  [VEC_UNITS]   
   // ����:    [CString strTemp]    
   // ��������::���ַ�����1,2,2,3������ʽת��Ϊvector<UINT>���͵����ݸ�ʽ
   // ����:    linyp 2011/10/08 17:59
   // �޸�ʱ��:
   // �޸�Ŀ��:
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
   // ������:  [CoverBIT16ToStr]
   // ����ֵ:  [CString]   
   // ����:    [BIT16 nbit]    
   // ��������:��16λ�Ķ�������ת��Ϊ��Ӧ��10���������ַ���
   // ����:    linyp 2011/10/08 18:00
   // �޸�ʱ��:
   // �޸�Ŀ��:
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
	-@brief [�����ַ����Ĺ淶��������0011-->11��11.100 ->11.1  .1100->0.11]
	-
	-[������ϸ����]
	-@n<b>��������</b>      : RegularNumberStr
	-@n@param CString & str : [�����ַ���]
	-@return                  [����ֵ����]
	-@see                     [�μ�����]
	-@n<b>����</b>          :  
	-@n<b>����ʱ��</b>      : 2009-4-13 13:54:31
	-@version    �޸���        ʱ��        ����@n
	-@n                     2009-04-13  [����]
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
			//ֱ����һ������0���ַ�
			if( m_strInput[i] != '0' ) 
			{
				break;
			}
		}
		
		if( i < nLen ) 
		{//����ȫ0�����
			// ����һ����0�ַ�ǰ���0ȥ��
			m_strInput = m_strInput.Mid(i); 
			nLen = m_strInput.GetLength();
			int nDotPos = m_strInput.Find('.'); 

			//����С����
			if( nDotPos != -1 ) 
			{
				for( i = nLen - 1; i >= 0; i-- )
				{
					if( m_strInput[i] != '0' )
					{
						break;
					}
				}

				//ȥ��С�������0
				m_strInput = m_strInput.Left(i + 1); 
			}

			//�����ַ����ĳ���
			nLen = m_strInput.GetLength();

			//С���������
			if( nDotPos == nLen - 1 ) 
			{
				m_strInput = m_strInput.Left(nLen - 1);
			}
			//С�������ʼ
			if( nDotPos == 0 ) 
			{
				m_strInput = _T("0") + m_strInput;
			}
		}
		else 
		{//ȫ0�����
			m_strInput = _T("0");
		}//end of if( i < nLen ) 	

	}//end of func


	/*-------------------------------------------------------------------
	-@brief [���֮���λ��]
	-
	-[������ϸ����]
	-@n<b>��������</b>    : CountAfterPoint
	-@n@param CString str : [��ֵ�ַ���]
	-@return                [-1��ʾ�޵�ţ� ����0ֵΪ��ź����λ��]
	-@see                   [�μ�����]
	-@n<b>����</b>        :  
	-@n<b>����ʱ��</b>    : 2009-4-14 10:27:13
	-@version    �޸���        ʱ��        ����@n
	-@n                     2009-04-14  [����]
	--------------------------------------------------------------------*/
	inline int CountAfterPoint(CString str)
	{
		//Ĭ���޵��
		int nResult(-1);
		
		//�����0���е�λ��
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
	-@brief [���֮ǰ��λ��]
	-
	-[������ϸ����]
	-@n<b>��������</b>    : CountBeforePoint
	-@n@param CString str : [��ֵ�ַ���]
	-@return                [���֮ǰ��λ����Ŀ]
	-@see                   [�μ�����]
	-@n<b>����</b>        :  
	-@n<b>����ʱ��</b>    : 2009-4-14 10:42:46
	-@version    �޸���        ʱ��        ����@n
	-@n                     2009-04-14  [����]
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
   -@brief [UTF8�ַ�ת��ΪUnicode�ַ�]
   -
   -[������ϸ����]
   -@n<b>��������</b> : UTF8_TO_UNICODE
   -@n@param const std::string utf8_str : [��Ҫת�����ַ���]
   -@param   std::wstring &     uni_str : [ת������ַ���]
   -@see                [�μ�����]
   -@n<b>����</b>     :  
   -@n<b>����ʱ��</b> : 2009-1-21 16:20:04
   -@version    �޸���        ʱ��        ����@n
   -@n                     2009-01-21  [����]
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

      // ����洢Unicode������ַ�������Ҫ���ڴ�
      wchar_t*  l_p_afterchange = new wchar_t[l_l_Len+1];

      // ת���ַ��������ʽ��UTF8��Unicode
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
   -@brief [ACP�ַ�ת��ΪUnicode�ַ�]
   -
   -[������ϸ����]
   -@n<b>��������</b> : ACP_TO_UNICODE
   -@n@param const std::string acp_str : [��Ҫת�����ַ���]
   -@param   std::wstring &    uni_str : [ת������ַ���]
   -@see                [�μ�����]
   -@n<b>����</b>     :lixf
   -@n<b>����ʱ��</b> : 2008.08.12
   -@version    �޸���        ʱ��        ����@n
   -@n                     2009-01-21  [����]
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

      // ����洢Unicode������ַ�������Ҫ���ڴ�
      wchar_t*  l_p_afterchange = new wchar_t[l_l_Len+1];

      // ת���ַ��������ʽ��UTF8��Unicode
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
   -@brief [Unicode�ַ�ת��ΪUTF8�ַ�]
   -
   -[������ϸ����]
   -@n<b>��������</b> : UNICODE_TO_UTF8
   -@n@param const std::wstring & uni_str : [��Ҫת�����ַ���]
   -@param   std::string &       utf8_str : [ת������ַ���]
   -@see                [�μ�����]
   -@n<b>����</b>     :lixf
   -@n<b>����ʱ��</b> : 2008.08.12
   -@version    �޸���        ʱ��        ����@n
   -@n                     2009-01-21  [����]
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

      // ����洢Unicode������ַ�������Ҫ���ڴ�
      char*  l_p_afterchange = new char[l_l_Len+1];

      // ת���ַ��������ʽ��UTF8��Unicode
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
   -@brief [Unicode�ַ�ת��ΪACP�ַ�]
   -
   -[������ϸ����]
   -@n<b>��������</b> : UNICODE_TO_ACP
   -@n@param const std::wstring & uni_str : [��Ҫת�����ַ���]
   -@param   std::string &        acp_str : [ת������ַ���]
   -@see                [�μ�����]
   -@n<b>����</b>     :lixf
   -@n<b>����ʱ��</b> : 2008.08.12
   -@version    �޸���        ʱ��        ����@n
   -@n                     2009-01-21  [����]
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

      // ����洢Unicode������ַ�������Ҫ���ڴ�
      char* l_p_afterchange = new char[l_l_Len+1];

      // ת���ַ��������ʽ��UTF8��Unicode
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
   -@brief [ACP�ַ�ת��ΪUTF8�ַ�]
   -
   -[������ϸ����]
   -@n<b>��������</b> : ACP_TO_UTF8
   -@n@param const std::string acp_str : [��Ҫת�����ַ���]
   -@param  std::string &     utf8_str : [ת������ַ���]
   -@see                [�μ�����]
   -@n<b>����</b>     :lixf
   -@n<b>����ʱ��</b> : 2008.08.12
   -@version    �޸���        ʱ��        ����@n
   -@n                     2009-01-21  [����]
   --------------------------------------------------------------------*/
   inline void ACP_TO_UTF8(const std::string acp_str,std::string& utf8_str)
   {
      std::wstring uni_str;
      ACP_TO_UNICODE(acp_str,uni_str);
      UNICODE_TO_UTF8(uni_str,utf8_str);
   }

   /*-------------------------------------------------------------------
   -@brief [STL���ַ��� ת��Ϊ STLխACP�ַ���]
   -
   -[������ϸ����]
   -@n<b>��������</b>: Wstr2Str
   -@n@param std::wstring & wstr : [STL���ַ���]
   -@return            [STLխACP�ַ���]
   -@see               [�μ�����]
   -@n<b>����</b>    :  
   -@n<b>����ʱ��</b>: 2009-2-9 15:13:57
   -@version    �޸���        ʱ��        ����@n
   -@n                     2009-02-09  [����]
   --------------------------------------------------------------------*/
   inline std::string Wstr2Str( std::wstring& wstr )
   {
      std::string strA = ANULL;
      UNICODE_TO_ACP( wstr, strA );

      return strA;
   }

   /*-------------------------------------------------------------------
   -@brief [STL���ַ��� ת��Ϊ STLխUTF8�ַ���]
   -
   -[������ϸ����]
   -@n<b>��������</b>: Wstr2StrUTF8
   -@n@param std::wstring & wstr : [STL���ַ���]
   -@return            [STLխUTF8�ַ���]
   -@see               [�μ�����]
   -@n<b>����</b>    :  
   -@n<b>����ʱ��</b>: 2009-2-9 15:24:27
   -@version    �޸���        ʱ��        ����@n
   -@n                     2009-02-09  [����]
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

#pragma region //�����ַ�����ת
    /*-------------------------------------------------------------------
   -@brief [intת��ΪCString]
   -
   -[������ϸ����]
   -@n<b>��������</b> : IntToCStr
   -@n@param int nVal : [Ҫת��Ϊ�ַ�����intֵ]
   -@return             [����ַ���]
   -@see                [�μ�����]
   -@n<b>����</b>     :  
   -@n<b>����ʱ��</b> : 2009-1-21 17:07:51
   -@version    �޸���        ʱ��        ����@n
   -@n                     2009-01-21  [����]
   --------------------------------------------------------------------*/
   inline CString IntToCStr( int nVal )
   {
      CString str = _T("");
      str.Format( _T("%d"), nVal );

      return str;
   }

   /*-------------------------------------------------------------------
   -@brief [doubleת��ΪCString]
   -
   -[������ϸ����]
   -@n<b>��������</b>                 : DouToCStr
   -@n@param double       dVal        : [Ҫת��Ϊ�ַ�����doubleֵ]
   -@param   unsigned int nAll        : [����ַ����ĳ���]
   -@param   unsigned int nAfterPoint : [����ַ���С������λ��]
   -@return                             [����ַ���]
   -@see                                [�μ�����]
   -@n<b>����</b>                     :  
   -@n<b>����ʱ��</b>                 : 2009-1-21 17:08:31
   -@version    �޸���        ʱ��        ����@n
   -@n                     2009-01-21  [����]
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
         //�������
         strAll = strUnit + strAll + strPoint + strAfterPoint + strFormat;
      } else {
         //�������
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
      int nBytes=0;//UFT8����1-6���ֽڱ���,ASCII��һ���ֽ�
      unsigned char chr;
      bool bAllAscii=true; //���ȫ������ASCII, ˵������UTF-8
      for(i=0;i<length;i++)
      {
         chr= *(str+i);
         if( (chr&0x80) != 0 ) // �ж��Ƿ�ASCII����,�������,˵���п�����UTF-8,ASCII��7λ����,����һ���ֽڴ�,���λ���Ϊ0,o0xxxxxxx
            bAllAscii= false;
         if(nBytes==0) //�������ASCII��,Ӧ���Ƕ��ֽڷ�,�����ֽ���
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
         else //���ֽڷ��ķ����ֽ�,ӦΪ 10xxxxxx
         {
            if( (chr&0xC0) != 0x80 )
            {
               return false;
            }
            nBytes--;
         }
      }

      if( nBytes > 0 ) //Υ������
      {
         return false;
      }

      if( bAllAscii ) //���ȫ������ASCII, ˵������UTF-8
      {
         return false;
      }
      return true;
   }

	//��ȡGUID�ַ���		by WangZY 2016/06/21
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
   //ɾ���ַ���ĩβû�õ�0 yangjr 2018/7/25
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
         else if ('.' == tmpStr[i])// С����֮��ȫΪ��
         {
            tmpStr.SetAt(i,'\0');
            break;
         }
         else// С������з�������
         {
            break;
         }
      }
      return tmpStr;
   }

#pragma endregion
}//end of namespace MyString

