#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <locale> 
using namespace std;
// CFileTxt

//by zhangyx 2017//11//30 ÉèÖÃ¶ÁÐ´txtÎÄ¼þ
class CFileTxt : public CWnd
{
	DECLARE_DYNAMIC(CFileTxt)

public:
	CFileTxt();
	virtual ~CFileTxt();
	void SetFileTitle(CString strFileTitle);
	BOOL ReadFile(CString strFileTitle);
	BOOL WriteFile(CString strFileTitle, CString strFileContent,BOOL bNewFile=TRUE);
	vector<CString> m_vecCString;
private:
	CString m_FileTitle;
	CString m_FileContent;
protected:
	DECLARE_MESSAGE_MAP()
};


