#pragma once
#include <vector>
#include <afxstr.h>

class CFrequentlyChatContentFile
{
public:
   BOOL ReadFile(const CString &sFilePath);
   BOOL WriteFile(const CString &sFilePath);
   std::vector<CString> m_vecContent;

   static const char *const SZ_XML_ELEMENT_CHAT;
   static const char *const SZ_XML_ELEMENT_CONTENT;
};