#include "Stdafx.h"
#include "CPtLog.h"
#include <queue>

queue<Que_Log_Info> g_Que_LogIngo;//全局的队列信息

#define Limit_Que_Count_Log	40	//记录的日志个数
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
	CString strAppFilePath;	//文件全路径

	GetModuleFileName(NULL, szPath, MAX_PATH);  //获取到完整路径 eg：E:\Tools\qq.exe
	strAppFilePath = szPath;

	strAppPath = strAppFilePath.Left(strAppFilePath.ReverseFind('\\'));
	CString strFileName = strAppPath +_T("\\")+ m_logFileName;

	std::wofstream owFile(strFileName,std::ios::app|std::ios::out);
	ASSERT(NULL != owFile);

	while(0 < g_Que_LogIngo.size())
	{
		auto logInfo = g_Que_LogIngo.front();

		owFile<<"时间:"<<(LPCTSTR)logInfo.LogTime.Format(_T("%Y-%m-%d %H:%M:%S"))<<std::endl;
		owFile<<"文件:"<<(LPCTSTR)logInfo.strFileName<<std::endl;
		owFile<<"行号:"<<logInfo.nlineNo<<std::endl;
		owFile<<"函数:"<<(LPCTSTR)logInfo.strCurFuctionName<<std::endl;
		owFile<<"内容:"<<(LPCTSTR)logInfo.strContent<<std::endl;
		owFile<<std::endl;

		g_Que_LogIngo.pop();
	}

	owFile.close();

}
