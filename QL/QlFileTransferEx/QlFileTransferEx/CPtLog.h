#pragma once
#include <afxstr.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <stdarg.h>

#include <afx.h>
#include <fstream>
#include <time.h> 
using namespace std;


#define LOGBUG CPtLog(_T("FileTrans.log"),_T(__FILE__), __LINE__,_T(__FUNCTION__))

typedef struct QUELOGINFO
{
	int nlineNo;              //����logλ�õ��ļ�����
	COleDateTime LogTime;
	CString strContent;
	CString strFileName;
	CString strCurFuctionName; //����logʱ��λ�õĺ�����
}Que_Log_Info;

class CPtLog
{
public:
	CPtLog(LPCTSTR logFileName,LPCTSTR curFileName, int lineNo,LPCTSTR curFuctionName)
		:m_logFileName(logFileName)
		,m_curFileName(curFileName)
		,m_lineNo(lineNo)
		,m_curFuctionName(curFuctionName)
	{}
	~CPtLog(void){}

	//void operator()(_In_z_ _FormatMessage_format_string_ LPCTSTR pszFormat,...);


	void operator()(_In_z_ _FormatMessage_format_string_ LPCTSTR pszFormat,...)
	{
		CString strAppPath = _T("");
		TCHAR szPath[MAX_PATH];
		CString strAppFilePath;	//�ļ�ȫ·��

		GetModuleFileName(NULL, szPath, MAX_PATH);  //��ȡ������·�� eg��E:\Tools\qq.exe
		strAppFilePath = szPath;

		strAppPath = strAppFilePath.Left(strAppFilePath.ReverseFind('\\'));
		CString strFileName = strAppPath +_T("\\")+ m_logFileName;

		std::wofstream owFile(strFileName,std::ios::app|std::ios::out);
 		//std::ofstream file("Bug.log",std::ios::app|std::ios::out);

		//owFile.open(strFileName,std::ios::out | std::ios::app);
		ASSERT(NULL != owFile);
		CString strContent = _T("");

		va_list argList;
		va_start( argList, pszFormat );
		strContent.FormatV(pszFormat,argList);

		va_end( argList );

		auto CurTime = COleDateTime::GetCurrentTime();

		owFile<<std::endl;
		owFile<<"ʱ��:"<<(LPCTSTR)CurTime.Format(_T("%Y-%m-%d %H:%M:%S"))<<std::endl;
		owFile<<"�ļ�:"<<(LPCTSTR)m_curFileName<<std::endl;
		owFile<<"�к�:"<<m_lineNo<<std::endl;
		owFile<<"����:"<<(LPCTSTR)m_curFuctionName<<std::endl;
		owFile<<"����:"<<(LPCTSTR)strContent<<std::endl;

		owFile.close();
	}

	void Write();

	void Clear()
	{
		ASSERT(!m_logFileName.IsEmpty());
		
		CString strAppPath = _T("");
		TCHAR szPath[MAX_PATH];
		CString strAppFilePath;	//�ļ�ȫ·��

		GetModuleFileName(NULL, szPath, MAX_PATH);  //��ȡ������·�� eg��E:\Tools\qq.exe
		strAppFilePath = szPath;

		strAppPath = strAppFilePath.Left(strAppFilePath.ReverseFind('\\'));
		CString strFileName = strAppPath +_T("\\") + m_logFileName;

		CFile file;
		if (file.Open(strFileName,CFile::modeCreate))
		{
			file.Close();
		}
	}
private:
	const CString m_logFileName; //log�ļ���
	const CString m_curFileName; //����logʱ��λ�õ��ļ���
	const int m_lineNo;              //����logλ�õ��ļ�����
	const CString m_curFuctionName; //����logʱ��λ�õĺ����� yangjr 2016-2-17

};