// CreateFileTransPathSettingXml.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <tinyxml\tinyxml.h>
#include <CommonAPI.h>
#include <vector>


CCommonAPI QLCOMAPI;

typedef struct S_SUBITEM_INFO{
   char sKey[50];//Key
   char sPath[256];//Path
   bool bUploadZip;//UploadZip
   bool bDownDelZip;//DownDelZip
   bool bUnZipFailRename;//UnZipFailRename
}SubItemInfo;


inline void     UNICODE_TO_UTF8(const std::wstring& uni_str, std::string& utf8_str);

std::string     UNICODE_TO_UTF8(CStringW strIn);

//UTF8编码转unicode
inline void     UTF8_TO_UNICODE(const std::string utf8_str,std::wstring& uni_str);

CString         UTF8_TO_UNICODE(const std::string utf8_str);

inline void ACP_TO_UNICODE(const std::string acp_str,std::wstring& uni_str);

inline void UNICODE_TO_ACP(const std::wstring& uni_str,std::string& acp_str);

inline void ACP_TO_UTF8(const std::string acp_str,std::string& utf8_str);
inline void UTF8_TO_ACP(const std::string utf8_str,std::string& acp_str);

#ifndef _UNICODE
std::string     ACP_TO_UTF8(CString strIn);
CString         UTF8_TO_ACP(const std::string utf8_str);
#endif // _UNICODE

S_SUBITEM_INFO SetSubItemInfo(const CString & strKey,const CString & strPath,bool bUploadZip = true,
   bool bDownDelZip = true,bool bUnZipFailName = false);
std::vector<SubItemInfo> GetSubItemInfo();

TiXmlElement* LinkTextElement(TiXmlElement * pParrentElecment,CString sElementValue,CString sTextValue)
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

int _tmain(int argc, _TCHAR* argv[])
{
   TiXmlDocument doc;
   TiXmlDeclaration* declaration = new TiXmlDeclaration("1.0", "UTF-8", "yes");
   if(!declaration)
      return 0;
   doc.LinkEndChild(declaration);

   TiXmlElement* root = new TiXmlElement("Root");
   doc.LinkEndChild(root);

   auto vec_SubItem = GetSubItemInfo();

   for (auto it = vec_SubItem.begin();it != vec_SubItem.end();++it)
   {
      auto pSubItem = LinkTextElement(root,_T("SubItem"),_T(""));
      LinkTextElement(pSubItem,_T("Key"),CString(it->sKey));
      LinkTextElement(pSubItem,_T("Path"),CString(it->sPath));
      LinkTextElement(pSubItem,_T("UploadZip"),it->bUploadZip ? _T("1") : _T("0"));
      LinkTextElement(pSubItem,_T("DownDelZip"),it->bDownDelZip ? _T("1") : _T("0"));
      LinkTextElement(pSubItem,_T("UnZipFailRename"),it->bUnZipFailRename ? _T("1") : _T("0"));
   }

   CString strXmlFile = _T("FileTransPathSetting.xml");

   char szFarFilePath[256] = {0};
   QLCOMAPI.WCharToMByte(strXmlFile,szFarFilePath,sizeof(szFarFilePath)/sizeof(szFarFilePath[0]));
   doc.SaveFile(szFarFilePath);

	return 0;
}

S_SUBITEM_INFO SetSubItemInfo(const CString & strKey,const CString & strPath,bool bUploadZip /*= true*/, bool bDownDelZip /*= true*/,bool bUnZipFailName /*= false*/)
{
   S_SUBITEM_INFO s_ValueInfo;
   memset(s_ValueInfo.sKey,0,sizeof(s_ValueInfo.sKey));
   memset(s_ValueInfo.sPath,0,sizeof(s_ValueInfo.sPath));
   QLCOMAPI.WCharToMByte(strKey,s_ValueInfo.sKey,sizeof(s_ValueInfo.sKey)/sizeof(s_ValueInfo.sKey[0]));
   QLCOMAPI.WCharToMByte(strPath,s_ValueInfo.sPath,sizeof(s_ValueInfo.sPath)/sizeof(s_ValueInfo.sPath[0]));

   s_ValueInfo.bUploadZip = bUploadZip;
   s_ValueInfo.bDownDelZip = bDownDelZip;
   s_ValueInfo.bUnZipFailRename = bUnZipFailName;
   return s_ValueInfo;
}

std::vector<SubItemInfo> GetSubItemInfo()
{
   std::vector<SubItemInfo> vecRet;

   //Order_Process
   //订单库/$OrderNo$/工艺文件/$Size$/
   vecRet.push_back(SetSubItemInfo(_T("File_Pattern")             ,_T("订单库/$OrderNo$/制版文件/$Size$/")));
   vecRet.push_back(SetSubItemInfo(_T("File_Process")             ,_T("订单库/$OrderNo$/工艺文件/$Size$/")));
   vecRet.push_back(SetSubItemInfo(_T("File_Design")              ,_T("订单库/$OrderNo$/设计文件/$Size$/")));
   vecRet.push_back(SetSubItemInfo(_T("File_Mac")                 ,_T("订单库/$OrderNo$/上机文件/$Size$/")));
   vecRet.push_back(SetSubItemInfo(_T("File_Order")               ,_T("订单库/$OrderNo$/订单文件/$Size$/")));
   vecRet.push_back(SetSubItemInfo(_T("File_Thc")                 ,_T("订单库/$OrderNo$/$Size$/")));
   vecRet.push_back(SetSubItemInfo(_T("File_Picture")             ,_T("订单库/$OrderNo$/图片文件/$Size$/"),false,false,true));
   vecRet.push_back(SetSubItemInfo(_T("File_Thumbnail")           ,_T("订单库/$OrderNo$/图片文件/缩略图/"),false,false,true));
   vecRet.push_back(SetSubItemInfo(_T("File_StyleImage")          ,_T("订单库/$OrderNo$/StyleImage/$Size$/")));
   vecRet.push_back(SetSubItemInfo(_T("File_ChatFile")            ,_T("订单库/$OrderNo$/ChatFile/$Size$/"),false,false,true));
   vecRet.push_back(SetSubItemInfo(_T("File_ImgProDetail")        ,_T("订单库/$OrderNo$/ImgProDetail/$Size$/"),false,false,true));
   vecRet.push_back(SetSubItemInfo(_T("File_ImgModel")            ,_T("订单库/$OrderNo$/ImgModel/$Size$/"),false,false,true));
   vecRet.push_back(SetSubItemInfo(_T("File_ImgModelThumbnail")   ,_T("订单库/$OrderNo$/ImgModel/缩略图/"),false,false,true));
   vecRet.push_back(SetSubItemInfo(_T("File_Video")               ,_T("订单库/$OrderNo$/视频文件/"),false,false,true));

   vecRet.push_back(SetSubItemInfo(_T("File_BackUp_Pattern")       ,_T("订单库/$OrderNo$/BackUpFile/制版文件/$Version$/$Size$/")));
   vecRet.push_back(SetSubItemInfo(_T("File_BackUp_Process")       ,_T("订单库/$OrderNo$/BackUpFile/工艺文件/$Version$/$Size$/")));
   vecRet.push_back(SetSubItemInfo(_T("File_BackUp_Design")        ,_T("订单库/$OrderNo$/BackUpFile/设计文件/$Version$/$Size$/")));
   vecRet.push_back(SetSubItemInfo(_T("File_BackUp_Mac")           ,_T("订单库/$OrderNo$/BackUpFile/上机文件/$Version$/$Size$/")));
   vecRet.push_back(SetSubItemInfo(_T("File_BackUp_Order")         ,_T("订单库/$OrderNo$/BackUpFile/订单文件/$Version$/$Size$/")));
   vecRet.push_back(SetSubItemInfo(_T("File_BackUp_Picture")       ,_T("订单库/$OrderNo$/BackUpFile/图片文件/$Version$/$Size$/"),false,false,true));
   vecRet.push_back(SetSubItemInfo(_T("File_BackUP_Thumbnail")     ,_T("订单库/$OrderNo$/BackUpFile/图片文件/缩略图/"),false,false,true));
   vecRet.push_back(SetSubItemInfo(_T("File_BackUp_StyleImage")    ,_T("订单库/$OrderNo$/BackUpFile/StyleImage/$Version$/$Size$/")));
   vecRet.push_back(SetSubItemInfo(_T("File_BackUp_ChatFile")      ,_T("订单库/$OrderNo$/BackUpFile/ChatFile/$Version$/$Size$/"),false,false,true));
   vecRet.push_back(SetSubItemInfo(_T("File_BackUp_ImgProDetail")  ,_T("订单库/$OrderNo$/BackUpFile/ImgProDetail/$Version$/$Size$/"),false,false,true));
   vecRet.push_back(SetSubItemInfo(_T("File_BackUp_ImgModel")      ,_T("订单库/$OrderNo$/BackUpFile/ImgModel/$Version$/$Size$/"),false,false,true));

   vecRet.push_back(SetSubItemInfo(_T("Lib_Bmp")            ,_T("共享库/底图库/")));
   vecRet.push_back(SetSubItemInfo(_T("Lib_Style")          ,_T("共享库/款式库/")));
   vecRet.push_back(SetSubItemInfo(_T("Lib_Process")        ,_T("共享库/工艺库/")));
   vecRet.push_back(SetSubItemInfo(_T("Lib_Density")        ,_T("共享库/工艺/密度表/")));
   vecRet.push_back(SetSubItemInfo(_T("Lib_Component")      ,_T("共享库/工艺/部件库/")));
   vecRet.push_back(SetSubItemInfo(_T("Lib_PatternConfig")  ,_T("共享库/小图库/")));
   vecRet.push_back(SetSubItemInfo(_T("Lib_Modfile")        ,_T("共享库/配置库/")));

   vecRet.push_back(SetSubItemInfo(_T("Other_Exchange")     ,_T("交互文件/"),false,false,true));
   vecRet.push_back(SetSubItemInfo(_T("Other_GlobalChat")   ,_T("GlobalChat/"),false,false,true));
   vecRet.push_back(SetSubItemInfo(_T("Other_WebImage")     ,_T("Web库/订单库/"),false,false,true));

   return vecRet;
}

void  UNICODE_TO_UTF8(const std::wstring& uni_str, std::string& utf8_str)
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

std::string UNICODE_TO_UTF8(CStringW strIn)
{
   std::wstring strwstr(strIn.GetBuffer());
   std::string strOut;
   UNICODE_TO_UTF8(strwstr,strOut);
   return strOut;
}

void UTF8_TO_UNICODE( const std::string utf8_str,std::wstring& uni_str )
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

CString UTF8_TO_UNICODE( const std::string utf8_str )
{
   std::wstring strOut;
   UTF8_TO_UNICODE(utf8_str,strOut);
   return CString(strOut.c_str());
}

void ACP_TO_UNICODE(const std::string acp_str,std::wstring& uni_str)
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

void UNICODE_TO_ACP(const std::wstring& uni_str,std::string& acp_str)
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

void ACP_TO_UTF8(const std::string acp_str,std::string& utf8_str)
{
   std::wstring uni_str;
   ACP_TO_UNICODE(acp_str,uni_str);
   UNICODE_TO_UTF8(uni_str,utf8_str);
}

void UTF8_TO_ACP(const std::string utf8_str,std::string& acp_str)
{
   std::wstring uni_str;
   UTF8_TO_UNICODE(utf8_str,uni_str);
   UNICODE_TO_ACP(uni_str,acp_str);
}

#ifndef _UNICODE
std::string ACP_TO_UTF8(CString strIn)
{
   std::string strstr(strIn);
   std::string strOut;
   ACP_TO_UTF8(strstr,strOut);
   return strOut;
}

CString UTF8_TO_ACP(const std::string utf8_str)
{
   std::wstring strOut;
   UTF8_TO_UNICODE(utf8_str,strOut);
   return CString(strOut.c_str());
}
#endif