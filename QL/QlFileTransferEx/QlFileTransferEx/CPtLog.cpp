#include "Stdafx.h"
#include "CPtLog.h"
#include <queue>

queue<Que_Log_Info> g_Que_LogIngo;//ȫ�ֵĶ�����Ϣ

#define Limit_Que_Count_Log	40	//��¼����־����
/*
void CPtLog::operator()(_In_z_ _FormatMessage_format_string_ LPCTSTR pszFormat,...)
{
	CString strContent = _T("");

	va_list argList;
	va_start( argList, pszFormat );
	strContent.FormatV(pszFormat,argList);

	va_end( argList );

	auto CurTime = COleDateTime::GetCurrentTime();

	Que_Log_Info logInfo;
	logInfo.LogTime = CurTime;
	logInfo.strFileName = m_curFileName;
	logInfo.strCurFuctionName = m_curFuctionName;
	logInfo.nlineNo = m_lineNo;
	logInfo.strContent = strContent;

	while(Limit_Que_Count_Log < g_Que_LogIngo.size())
	{
		g_Que_LogIngo.pop();
	}
	g_Que_LogIngo.push(logInfo);
}*/

void CPtLog::Write()
{
	CString strAppPath = _T("");
	TCHAR szPath[MAX_PATH];
	CString strAppFilePath;	//�ļ�ȫ·��

	GetModuleFileName(NULL, szPath, MAX_PATH);  //��ȡ������·�� eg��E:\Tools\qq.exe
	strAppFilePath = szPath;

	strAppPath = strAppFilePath.Left(strAppFilePath.ReverseFind('\\'));
	CString strFileName = strAppPath +_T("\\")+ m_logFileName;

	std::wofstream owFile(strFileName,std::ios::app|std::ios::out);
	ASSERT(NULL != owFile);

	while(0 < g_Que_LogIngo.size())
	{
		auto logInfo = g_Que_LogIngo.front();

		owFile<<"ʱ��:"<<(LPCTSTR)logInfo.LogTime.Format(_T("%Y-%m-%d %H:%M:%S"))<<std::endl;
		owFile<<"�ļ�:"<<(LPCTSTR)logInfo.strFileName<<std::endl;
		owFile<<"�к�:"<<logInfo.nlineNo<<std::endl;
		owFile<<"����:"<<(LPCTSTR)logInfo.strCurFuctionName<<std::endl;
		owFile<<"����:"<<(LPCTSTR)logInfo.strContent<<std::endl;
		owFile<<std::endl;

		g_Que_LogIngo.pop();
	}

	owFile.close();

}
