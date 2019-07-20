// FileTxt.cpp : 实现文件
//

#include "stdafx.h"
#include "QLSvrMgn.h"
#include "FileTxt.h"
#include <string.h>
#include <afx.h>

// CFileTxt

IMPLEMENT_DYNAMIC(CFileTxt, CWnd)

CFileTxt::CFileTxt()
{

}

CFileTxt::~CFileTxt()
{
}


BEGIN_MESSAGE_MAP(CFileTxt, CWnd)
END_MESSAGE_MAP()



// CFileTxt 消息处理程序


void CFileTxt::SetFileTitle(CString strFileTitle)
{
	m_FileTitle = strFileTitle;
}

BOOL CFileTxt::ReadFile(CString strFileTitle)
{
	BOOL bRet = TRUE;
	if(strFileTitle.IsEmpty())
	{
		bRet = FALSE;
		OutputDebugString(_T("文件名为空，无法进行读取!"));
		return bRet;
	}
	SetFileTitle(strFileTitle);
	m_vecCString.clear();
	CStdioFile myFile;
	if(myFile.Open(m_FileTitle, CFile::modeRead))
	{
		char* old_locale = _strdup( setlocale(LC_CTYPE,NULL) );
		setlocale( LC_CTYPE, "chs" );
		while(myFile.ReadString(m_FileContent))
		{
       
			m_vecCString.push_back(m_FileContent);
         
		}
		setlocale( LC_CTYPE, old_locale );
		free( old_locale );
	}
	else
	{
		bRet = FALSE;
	}
	myFile.Close();
	return bRet;
}

BOOL CFileTxt::WriteFile(CString strFileTitle, CString strFileContent,BOOL bNewFile/*=TRUE*/)
{
	BOOL bRet = TRUE;
	if(strFileTitle.IsEmpty())
	{
		bRet = FALSE;
		OutputDebugString(_T("文件名为空，无法进行写入!"));
		return bRet;
	}
	SetFileTitle(strFileTitle);
	CStdioFile myFile;
	int iFileSelect = CFile::modeCreate|CFile::modeWrite|CFile::modeNoTruncate | CFile::typeBinary;
	if(bNewFile)
	{
		iFileSelect &= ~CFile::modeNoTruncate;
	}
	if(myFile.Open(m_FileTitle, iFileSelect))
	{
		char* old_locale = _strdup( setlocale(LC_CTYPE,NULL) );
		setlocale( LC_CTYPE, "chs" );
		myFile.SeekToEnd();
		myFile.WriteString(strFileContent+_T("\n"));
		setlocale( LC_CTYPE, old_locale );
		free( old_locale );
	}
	myFile.Close();
	return bRet;
}