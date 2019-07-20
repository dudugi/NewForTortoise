// QlFileTransferEx.cpp : ���� DLL �ĳ�ʼ�����̡�
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
//TODO: ����� DLL ����� MFC DLL �Ƕ�̬���ӵģ�
//		��Ӵ� DLL �������κε���
//		MFC �ĺ������뽫 AFX_MANAGE_STATE ����ӵ�
//		�ú�������ǰ�档
//
//		����:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �˴�Ϊ��ͨ������
//		}
//
//		�˺������κ� MFC ����
//		������ÿ��������ʮ����Ҫ������ζ��
//		��������Ϊ�����еĵ�һ�����
//		���֣������������ж������������
//		������Ϊ���ǵĹ��캯���������� MFC
//		DLL ���á�
//
//		�й�������ϸ��Ϣ��
//		����� MFC ����˵�� 33 �� 58��
//

// CQlFileTransferExApp

BEGIN_MESSAGE_MAP(CQlFileTransferExApp, CWinApp)
END_MESSAGE_MAP()


// CQlFileTransferExApp ����

CQlFileTransferExApp::CQlFileTransferExApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
	m_strKdsPath = _T("");

	m_strSvrPath = _T("");
	m_strMgnPath = _T("");
	m_strMacPath = _T("");
	m_nGdiplusToken = 0;
}


// Ψһ��һ�� CQlFileTransferExApp ����

CQlFileTransferExApp theApp;
CMySerial MySerial;
CCommonAPI QLCOMAPI;

//int g_nAdoAccess = 1;

// CQlFileTransferExApp ��ʼ��

BOOL CQlFileTransferExApp::InitInstance()
{
	CWinApp::InitInstance();

	// GDI+ϵͳ��Դ��ʼ��
	GdiplusStartupInput nGdiplusStartupInput;
	GdiplusStartup(&m_nGdiplusToken, &nGdiplusStartupInput, NULL);


	return TRUE;
}


int CQlFileTransferExApp::ExitInstance()
{
	// TODO: �ڴ����ר�ô����/����û���


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
*OnEncodeStr���ַ�������
*������	strData	��Ҫ���ܵ�Դ�ַ��������ģ�
*			nKey	��Կ
*����ֵ��	���ܺ���ַ��������ģ�
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
*OnDecodeStrr���ַ�������
*������	strData	��Ҫ���ܵ�Դ�ַ��������ģ�
*			nKey	��Կ
*����ֵ��	���ܺ���ַ��������ģ�
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
	long lDataSize = ptSet->GetFields()->GetItem((LPCTSTR)strField)->ActualSize; //���ݿ���ͼ�����ݳ���
	if (lDataSize > 0)
	{
		_variant_t varBLOB;
		varBLOB = ptSet->GetFields()->GetItem((LPCTSTR)strField)->GetChunk(lDataSize);
		Data = new char[lDataSize+1];
		if (varBLOB.vt == (VT_ARRAY|VT_UI1))//�ж����������Ƿ���ȷ
		{
			SafeArrayAccessData(varBLOB.parray, (void **)&pBuf);
			memcpy(Data, pBuf, lDataSize);//�������������ݵ�Data
			SafeArrayUnaccessData(varBLOB.parray);
		}
	}

	//DataתIStream
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
		GetHGlobalFromStream(pStm, &hGlobal); // ��ȡ IStream ���ڴ���

		LPBYTE pBits = (LPBYTE)GlobalLock(hGlobal); // pBits ���Ǵ洢JPEG���ݵ��ڴ�ָ��
		
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
	TiXmlText * text = new TiXmlText(UNICODE_TO_UTF8(sw).c_str());  ///�ı�
	pChild->LinkEndChild(text);
#else
	TiXmlElement* pChild = new TiXmlElement(ACP_TO_UTF8(sElementValue).c_str());
	pParrentElecment->LinkEndChild(pChild);
	TiXmlText * text = new TiXmlText(ACP_TO_UTF8(sTextValue).c_str());  ///�ı�
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
         //�ͷ��ļ�
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
      case ERROR_SUCCESS://�����ɹ�
         bRet = TRUE;
         break;
      case ERROR_BAD_PATHNAME://pszPath ����Ϊ���·��
         bRet = FALSE;
         break;
      case ERROR_FILENAME_EXCED_RANGE://pszPath ����̫��
         bRet = FALSE;
         break;
      case ERROR_PATH_NOT_FOUND://����ʱϵͳ�Ҳ���ָ��·��������·���а����Ƿ���ڡ�(��Z:\,��������Z�̡�)
         bRet = FALSE;
         break;
      case ERROR_FILE_EXISTS://�ļ��Ѿ�����
         bRet = TRUE;
         break;
      case ERROR_ALREADY_EXISTS://·���Ѿ�����
         bRet = TRUE;
         break;
      case ERROR_CANCELLED://�û�ȡ���˲���
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