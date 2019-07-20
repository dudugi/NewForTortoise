#pragma once
/*************************************************
// <�ļ�>: FrequentlyChatContentFile.h
// <˵��>: �����������ݣ�xml�����ļ���д��
// <����>: duchen
// <����>: 2019/02/22
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
#include <vector>
#include <afxstr.h>

class CFrequentlyChatContentFile
{
public:
   BOOL ReadFile(const CString &sFilePath); //���ļ�
   BOOL WriteFile(const CString &sFilePath); //д�ļ�
   std::vector<CString> m_vecContent; //����������������

   static const char *const SZ_XML_ELEMENT_CHAT; //xmlԪ���ַ��� chat
   static const char *const SZ_XML_ELEMENT_CONTENT; //xmlԪ���ַ��� content
};