// QlFileTransferEx.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "QlFileTransferEx.h"
#include "ClassEx/MySerial.h"
#include "Zip/zip.h"
#include "Zip/unzip.h"
#include "Base64Code.h"
#include "base64.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//
//TODO: 如果此 DLL 相对于 MFC DLL 是动态链接的，
//		则从此 DLL 导出的任何调入
//		MFC 的函数必须将 AFX_MANAGE_STATE 宏添加到
//		该函数的最前面。
//
//		例如:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 此处为普通函数体
//		}
//
//		此宏先于任何 MFC 调用
//		出现在每个函数中十分重要。这意味着
//		它必须作为函数中的第一个语句
//		出现，甚至先于所有对象变量声明，
//		这是因为它们的构造函数可能生成 MFC
//		DLL 调用。
//
//		有关其他详细信息，
//		请参阅 MFC 技术说明 33 和 58。
//

// CQlFileTransferExApp

BEGIN_MESSAGE_MAP(CQlFileTransferExApp, CWinApp)
END_MESSAGE_MAP()


// CQlFileTransferExApp 构造

CQlFileTransferExApp::CQlFileTransferExApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
	m_strKdsPath = _T("");

	m_strSvrPath = _T("");
	m_strMgnPath = _T("");
	m_strMacPath = _T("");
	m_nGdiplusToken = 0;
}


// 唯一的一个 CQlFileTransferExApp 对象

CQlFileTransferExApp theApp;
CMySerial MySerial;
CCommonAPI QLCOMAPI;

//int g_nAdoAccess = 1;

// CQlFileTransferExApp 初始化

BOOL CQlFileTransferExApp::InitInstance()
{
	CWinApp::InitInstance();

	// GDI+系统资源初始化
	GdiplusStartupInput nGdiplusStartupInput;
	GdiplusStartup(&m_nGdiplusToken, &nGdiplusStartupInput, NULL);


	return TRUE;
}


int CQlFileTransferExApp::ExitInstance()
{
	// TODO: 在此添加专用代码和/或调用基类


	CMFCVisualManager::DestroyInstance(TRUE);

	return CWinApp::ExitInstance();
}


void CQlFileTransferExApp::GetIniKeyValue( CString strSection,CString strKeyName,CString &strKeyValue,CString strPathFile/*=_T("")*/ )
{
	strPathFile.Trim();
	ASSERT(!strPathFile.IsEmpty());

	TCHAR temp[MAX_PATH];
	GetPrivateProfileString(strSection,strKeyName,_T(""),temp,MAX_PATH,strPathFile);
	strKeyValue.Format(_T("%s"),temp);
	strKeyValue.Trim();
}

void CQlFileTransferExApp::SetIniKeyValue( CString strSection,CString strKeyName,CString strKeyValue,CString strPathFile/*=_T("")*/ )
{
	strPathFile.Trim();
	ASSERT(!strPathFile.IsEmpty());

	strKeyValue.Trim();
	WritePrivateProfileString(strSection,strKeyName,strKeyValue,strPathFile);
}

/**********************************************************************
*OnEncodeStr：字符串加密
*参数：	strData	需要加密的源字符串（明文）
*			nKey	秘钥
*返回值：	加密后的字符串（密文）
**********************************************************************/
CString CQlFileTransferExApp::OnEncodeStr( CString strData, WORD nKey/* = WORD_PWD_KEY*/ )
{
	strData.Trim();
	CString strRet = _T("");
	if(strData.IsEmpty())
	{
		return strRet;
	}
	else
	{
		CBase64Code Base64Code;
		strRet = Base64Code.base64Encode(strData);
	}

	return strRet;
}

/**********************************************************************
*OnDecodeStrr：字符串解密
*参数：	strData	需要解密的源字符串（密文）
*			nKey	秘钥
*返回值：	解密后的字符串（明文）
**********************************************************************/
CString CQlFileTransferExApp::OnDecodeStr( CString strData, WORD nKey/* = WORD_PWD_KEY*/ )
{
	strData.Trim();
	CString strRet = _T("");
	if(strData.IsEmpty())
	{
		return strRet;
	}
	else
	{
		CBase64Code Base64Code;
		strRet = Base64Code.base64Decode(strData);
	}

	return strRet;
}

BOOL CQlFileTransferExApp::CheckNetState()
{
	BOOL bNetState = FALSE;
	DWORD dwFlags;	

	if (IsNetworkAlive(&dwFlags))
	{
		bNetState = TRUE;
	}
	else
	{
		bNetState = FALSE;
	}

	return bNetState;
}

int CQlFileTransferExApp::LoadImageStringFromDB(CString strField,_RecordsetPtr ptSet,wstring & sBase64)
{
	int nRet = 0;
	LPVOID Data = NULL;
	char* pBuf = NULL;
	long lDataSize = ptSet->GetFields()->GetItem((LPCTSTR)strField)->ActualSize; //数据库中图像数据长度
	if (lDataSize > 0)
	{
		_variant_t varBLOB;
		varBLOB = ptSet->GetFields()->GetItem((LPCTSTR)strField)->GetChunk(lDataSize);
		Data = new char[lDataSize+1];
		if (varBLOB.vt == (VT_ARRAY|VT_UI1))//判断数据类型是否正确
		{
			SafeArrayAccessData(varBLOB.parray, (void **)&pBuf);
			memcpy(Data, pBuf, lDataSize);//拷贝数据中数据到Data
			SafeArrayUnaccessData(varBLOB.parray);
		}
	}

	//Data转IStream
	IStream* pStm;
	LONGLONG cb = lDataSize;
	HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, cb);
	LPVOID pvData;
	CImage image;
	if (hGlobal != NULL)
	{
		pvData = GlobalLock(hGlobal);
		memcpy(pvData, Data, cb);
		GlobalUnlock(hGlobal);
		CreateStreamOnHGlobal(hGlobal, TRUE, &pStm);

		image.Save(pStm,ImageFormatJPEG);
		GetHGlobalFromStream(pStm, &hGlobal); // 获取 IStream 的内存句柄

		LPBYTE pBits = (LPBYTE)GlobalLock(hGlobal); // pBits 就是存储JPEG内容的内存指针
		
		Base64 oBase64;
		nRet = oBase64.Encode(pBits, GlobalSize(hGlobal),sBase64);

		if (NULL != Data)
		{
			delete Data;
			Data = NULL;
		}
	}
	return nRet;
}

CString CQlFileTransferExApp::GetTinyXmlNodeString(TiXmlElement * pElement)
{
	CString strRet = _T("");
	if(pElement)
	{
		auto pNode = pElement->FirstChild();
		if (pNode)
		{
			string sValue = pNode->ToText()->Value();
#ifdef _UNICODE
			strRet = UTF8_TO_UNICODE(sValue);
#else
			strRet = UTF8_TO_ACP(sValue);
#endif // _UNICODE
		}
	}
	return strRet;

}

CString CQlFileTransferExApp::GetTinyXmlAttriString(TiXmlElement * pElement,const char * Attri)
{
	CString strRet = _T("");
	if(pElement)
	{
		string sValue = pElement->Attribute(Attri);
#ifdef _UNICODE
		strRet = UTF8_TO_UNICODE(sValue);
#else
		strRet = UTF8_TO_ACP(sValue);
#endif // _UNICODE
	}
	return strRet;
}

TiXmlElement* CQlFileTransferExApp::LinkTextElement(TiXmlElement * pParrentElecment,CString sElementValue,CString sTextValue)
{
#ifdef _UNICODE
	CStringW sw(sTextValue),sValueW(sElementValue);
	TiXmlElement* pChild = new TiXmlElement(UNICODE_TO_UTF8(sValueW).c_str());
	pParrentElecment->LinkEndChild(pChild);
	TiXmlText * text = new TiXmlText(UNICODE_TO_UTF8(sw).c_str());  ///文本
	pChild->LinkEndChild(text);
#else
	TiXmlElement* pChild = new TiXmlElement(ACP_TO_UTF8(sElementValue).c_str());
	pParrentElecment->LinkEndChild(pChild);
	TiXmlText * text = new TiXmlText(ACP_TO_UTF8(sTextValue).c_str());  ///文本
	pChild->LinkEndChild(text);
#endif // _UNICODE

	return pChild;
}

TiXmlElement* CQlFileTransferExApp::LinkTextElementFormat(TiXmlElement * pParrentElecment,CString sElementValue,_In_z_ _FormatMessage_format_string_ LPCTSTR pszFormat,...)
{
	CString strValue = _T("");
	va_list argList;
	va_start( argList, pszFormat );
	strValue.FormatV(pszFormat,argList);
	va_end( argList );

	return LinkTextElement(pParrentElecment,sElementValue,strValue);
}

TiXmlElement* CQlFileTransferExApp::LinkAttributeElement(TiXmlElement * pParrentElecment,CString sElementValue,CString sAttributeDestribution,CString sAttributeValue)
{
#ifdef _UNICODE
	CStringW sw(sAttributeValue),sValueW(sElementValue),sDestributionW(sAttributeDestribution);
	TiXmlElement* pChild = new TiXmlElement(UNICODE_TO_UTF8(sValueW).c_str());
	pParrentElecment->LinkEndChild(pChild);
	pChild->SetAttribute(UNICODE_TO_UTF8(sDestributionW).c_str(),UNICODE_TO_UTF8(sw).c_str());
#else
	TiXmlElement* pChild = new TiXmlElement(ACP_TO_UTF8(sElementValue).c_str());
	pParrentElecment->LinkEndChild(pChild);
	pChild->SetAttribute(ACP_TO_UTF8(sAttributeDestribution).c_str(),ACP_TO_UTF8(sAttributeValue).c_str());
#endif // _UNICODE

	return pChild;
}

void  CQlFileTransferExApp::UNICODE_TO_UTF8(const std::wstring& uni_str, std::string& utf8_str)
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

std::string CQlFileTransferExApp::UNICODE_TO_UTF8(CStringW strIn)
{
	std::wstring strwstr(strIn.GetBuffer());
	std::string strOut;
	UNICODE_TO_UTF8(strwstr,strOut);
	return strOut;
}

void CQlFileTransferExApp::UTF8_TO_UNICODE( const std::string utf8_str,std::wstring& uni_str )
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

CString CQlFileTransferExApp::UTF8_TO_UNICODE( const std::string utf8_str )
{
	std::wstring strOut;
	UTF8_TO_UNICODE(utf8_str,strOut);
	return CString(strOut.c_str());
}

void CQlFileTransferExApp::ACP_TO_UNICODE(const std::string acp_str,std::wstring& uni_str)
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

void CQlFileTransferExApp::UNICODE_TO_ACP(const std::wstring& uni_str,std::string& acp_str)
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



void CQlFileTransferExApp::ACP_TO_UTF8(const std::string acp_str,std::string& utf8_str)
{
	std::wstring uni_str;
	ACP_TO_UNICODE(acp_str,uni_str);
	UNICODE_TO_UTF8(uni_str,utf8_str);
}

void CQlFileTransferExApp::UTF8_TO_ACP(const std::string utf8_str,std::string& acp_str)
{
	std::wstring uni_str;
	UTF8_TO_UNICODE(utf8_str,uni_str);
	UNICODE_TO_ACP(uni_str,acp_str);
}

#ifndef _UNICODE
std::string CQlFileTransferExApp::ACP_TO_UTF8(CString strIn)
{
	std::string strstr(strIn);
	std::string strOut;
	ACP_TO_UTF8(strstr,strOut);
	return strOut;
}

CString CQlFileTransferExApp::UTF8_TO_ACP(const std::string utf8_str)
{
	std::wstring strOut;
	UTF8_TO_UNICODE(utf8_str,strOut);
	return CString(strOut.c_str());
}
#endif

BOOL CQlFileTransferExApp::LoadResourceToContent(UINT uID, const CString & strType, CString& strContent)
{
   AFX_MANAGE_STATE(AfxGetStaticModuleState());
   /*HMODULE hModule=GetModuleHandle(NULL);   */
   HMODULE hModule=GetModuleHandle((LPCTSTR)_FILETRANS_LIBNAME_);
   HRSRC hRes = FindResource(hModule,MAKEINTRESOURCE(uID),strType);
   if(hRes == NULL)
   {
      FreeResource(hRes);
   }
   else
   {
      /*DWORD nLength = ::SizeofResource(hModule, hRes);
      if (nLength == 0)
      {
         return FALSE;
      }*/

      HGLOBAL hglobal = LoadResource(hModule,hRes);
      if(hglobal == NULL)
      {
         FreeResource(hglobal);
         return false;
      }

      LPTSTR lpszXML = NULL;
      //UTF8ToString((LPCSTR)::LockResource (hglobal),lpszXML,nLength);
      strContent = UTF8_TO_UNICODE((LPCSTR)::LockResource (hglobal));

      ::UnlockResource (hglobal);
      ::FreeResource (hglobal);
   }
   return true;
}

BOOL CQlFileTransferExApp::FreeResourceToFile(UINT uID, const CString & strType, const CString & strOutputPath)
{
   AFX_MANAGE_STATE(AfxGetStaticModuleState());
   
   CFile file;
   HMODULE hModule=GetModuleHandle((LPCTSTR)_FILETRANS_LIBNAME_);   
   HRSRC hRes = FindResource(hModule,MAKEINTRESOURCE(uID),strType);
   if(hRes == NULL)
   {
      FreeResource(hRes);
   }
   else
   {
      HGLOBAL hglobal = LoadResource(hModule,hRes);
      if(hglobal == NULL)
      {
         FreeResource(hglobal);
         return false;
      }
      else
      {
         //释放文件
         LPBYTE lpByte=(LPBYTE)LockResource(hglobal);   
         DWORD dwRcSize=SizeofResource(hModule,hRes);
         file.Open(strOutputPath,CFile::modeCreate | CFile::modeWrite);
         file.Write(lpByte,dwRcSize);
         file.Close();
      }
   }
   return true;
}

BOOL CQlFileTransferExApp::CreateFolder(LPCTSTR szFolder)
{
   BOOL bRet = TRUE;

   int nLen = _tcslen(szFolder);
   if (0 == nLen)
   {
      bRet = FALSE;
   }
   else
   {
      int nRet = SHCreateDirectoryEx(NULL,szFolder,NULL);
      switch(nRet)
      {
      default:
      case ERROR_SUCCESS://创建成功
         bRet = TRUE;
         break;
      case ERROR_BAD_PATHNAME://pszPath 参数为相对路径
         bRet = FALSE;
         break;
      case ERROR_FILENAME_EXCED_RANGE://pszPath 参数太长
         bRet = FALSE;
         break;
      case ERROR_PATH_NOT_FOUND://创建时系统找不到指定路径，可能路径中包含非法入口。(如Z:\,但不存在Z盘。)
         bRet = FALSE;
         break;
      case ERROR_FILE_EXISTS://文件已经存在
         bRet = TRUE;
         break;
      case ERROR_ALREADY_EXISTS://路径已经存在
         bRet = TRUE;
         break;
      case ERROR_CANCELLED://用户取消了操作
         bRet = FALSE;
         break;	
      }
   }

   return bRet;
}

CString CQlFileTransferExApp::GetFileParentFolder(LPCTSTR szFilePath)
{
   int nLen = _tcslen(szFilePath);
   if (0 == nLen)
   {
      return _T("");
   }
   else
   {
      TCHAR Drive[_MAX_DRIVE] = {0};
      TCHAR Folder[_MAX_DIR] = {0};
      _tsplitpath(szFilePath,Drive, Folder, NULL,NULL);
      CString sRet(Drive);
      sRet.Append(Folder);

      return sRet;
   } 
}