// Directory.cpp : 实现文件
//

#include "stdafx.h"
#include "QLSvrMgn.h"
#include "Directory.h"
#include <shellapi.h>
#include <string.h>
#include <tchar.h>


// CDirectory

IMPLEMENT_DYNAMIC(CDirectory, CWnd)

CDirectory::CDirectory()
{

}

CDirectory::~CDirectory()
{
}


BEGIN_MESSAGE_MAP(CDirectory, CWnd)
END_MESSAGE_MAP()



// CDirectory 消息处理程序

//选择文件夹对话框回调函数   
int CALLBACK BrowseCallBackFun(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)  
{  
	switch(uMsg)
	{

	case BFFM_INITIALIZED:    //初始化消息BFFM_INITIALIZED
		::SendMessage(hwnd,BFFM_SETSELECTION,TRUE,(LPARAM)lpData);   //传递默认打开路径 
		break;
	case BFFM_SELCHANGED:    //选择路径变化，BFFM_SELCHANGED
		{
			TCHAR curr[MAX_PATH];   
			if(SHGetPathFromIDList((LPCITEMIDLIST)lParam,curr))
			{
				::SendMessage(hwnd,BFFM_SETSTATUSTEXT,0,(LPARAM)&curr[0]);  
			}		
		}
		break;
	default:
		break;
	} 
	return 0;
}  


BOOL CDirectory::OpenDirectory(CString &strRetPath,CString strDefPath)
{
	BOOL  bRet = FALSE;		//函数返回值

	TCHAR pszPath[MAX_PATH];
	TCHAR defPath[MAX_PATH];
	BOOL bCallBack = FALSE;

	strRetPath.Empty();
	strDefPath.Trim();
	if (!strDefPath.IsEmpty())
	{
		bCallBack = TRUE;
		_tcscpy_s(defPath, strDefPath);
	}
	
	BROWSEINFO bi; 
	ZeroMemory(&bi,sizeof(BROWSEINFO));
	bi.ulFlags = BIF_DONTGOBELOWDOMAIN | BIF_RETURNONLYFSDIRS | BIF_STATUSTEXT | BIF_USENEWUI | BIF_NEWDIALOGSTYLE;
	bi.lpszTitle = _T("请选择目录");  
	bi.hwndOwner = this->GetSafeHwnd();
	if(bCallBack)
	{
		bi.lpfn = BrowseCallBackFun;     //回调函数 
		bi.lParam = (LPARAM)(&defPath);
	}

	LPITEMIDLIST pidl = SHBrowseForFolder(&bi); 
	if(pidl != NULL)  
	{  
		SHGetPathFromIDList(pidl,pszPath);
		strRetPath = pszPath;//赋值
		bRet = TRUE;
	}
	
	return bRet;
}

BOOL CDirectory::OpenDirFile(CString &strRetPath,CString strDefPath,CString strDefFile,CString strFilter,BOOL bOpen/*=TRUE*/)
{
	BOOL  bRet = FALSE;		//函数返回值

	strRetPath.Empty();
	strDefPath.Trim();
	strFilter.Trim();
 
	DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	if (bOpen) dwFlags |= OFN_FILEMUSTEXIST;
	
	CFileDialog fileDlg(bOpen,strFilter,strDefFile,dwFlags,strFilter,this);
	fileDlg.m_ofn.lpstrInitialDir =  LPCTSTR(strDefPath);// 默认目录

	if(IDOK == fileDlg.DoModal())
	{
		strRetPath = fileDlg.GetPathName();
		bRet = TRUE;
	}

	return bRet;
}


BOOL CDirectory::CopyDirectory(CString strSrcPath, CString strDesPath)
{
	if(strSrcPath.IsEmpty() )
	{      
		OutputDebugString(_T("源文件名为空，无法进行拷贝!"));   
		return FALSE;
	}
	CreateDirectory(strDesPath,NULL); //创建目标文件夹     
    CFileFind finder;  
    CString srcSubPath;    
    BOOL rRet = FALSE;  
    srcSubPath.Format(_T("%s\\*.*"),strSrcPath);      
    BOOL bWorking = finder.FindFile(srcSubPath);    
    while(bWorking)  
    {    
        bWorking = finder.FindNextFile();    
        if(finder.IsDirectory() && !finder.IsDots())//是文件夹 而且 名称不含 . 或 ..    
        {   
            //递归创建文件夹+"/"+finder.GetFileName()  
            CopyDirectory(finder.GetFilePath(),strDesPath+_T("\\")+finder.GetFileName());     
        }    
        else//是文件 则直接复制   
        {    
            CString stSrcFile = finder.GetFilePath();  
            BOOL result=(GetFileAttributes(stSrcFile) & FILE_ATTRIBUTE_DIRECTORY);  
            if (!result)  
            {  
               rRet = CopyFile(finder.GetFilePath(),strDesPath+_T("\\")+finder.GetFileName(),FALSE);    
// 				WCHAR src[256] = {0};
// 				WCHAR des[256] = {0};
// 
// 
// 
// 
// 				memset(src, 0, 256*sizeof(WCHAR));
// 				memset(des, 0, 256*sizeof(WCHAR));
// 				_tcscpy(src, finder.GetFilePath());//注意这里，之前copy不成功就是因为这里
// 				_tcscpy(des, (strDesPath+_T("\\")+finder.GetFileName()));
// 
// 			SHFILEOPSTRUCT FileOp;
// 			FileOp.hwnd = this->m_hWnd;
// 			FileOp.wFunc = FO_COPY; //执行文件拷贝
// 			CString strTitle = _T("正在拷贝文件,请稍候...");
// 			FileOp.pFrom = (WCHAR *)src;
// 			FileOp.pTo = (WCHAR *)des;
// 			FileOp.fFlags = FOF_ALLOWUNDO | FOF_NOCONFIRMATION;
// 			FileOp.hNameMappings = NULL;
// 			FileOp.lpszProgressTitle = strTitle;
// 			SHFileOperation(&FileOp);
            }  
        }    
    }    
    return rRet;  
}

BOOL CDirectory::CopyDirFileAPI(CString strSrcPath, CString strDesPath)
{
	//拷贝文件
	if(strSrcPath.IsEmpty())
	{
		OutputDebugString(_T("源文件名不能为空!"));
		return FALSE;
	}
	if(strDesPath.IsEmpty())
	{
		OutputDebugString(_T("目标文件名不能为空!"));
		return FALSE;
	}
	if(!PathFileExists(strDesPath))
	{
		 CreateDirectory(strDesPath, NULL);
	}
   if (strSrcPath.GetAt(strSrcPath.GetLength()-1) == '\\' || strSrcPath.GetAt(strSrcPath.GetLength()-1) == '/')
   {
     strSrcPath = strSrcPath.Left(strSrcPath.GetLength()-1);
   }
   if (strDesPath.GetAt(strDesPath.GetLength()-1) == '\\' || strDesPath.GetAt(strDesPath.GetLength()-1) == '/')
   {
     strDesPath = strDesPath.Left(strDesPath.GetLength()-1);
   }
   strSrcPath = strSrcPath + _T("\\*.*");
     			/*strcpy(szFrom, (LPCTSTR)strSrcPath);*/
  /* szFrom[strSrcPath.GetLength()+1]='\0';*/
     			//strDes=strDes+"\\*.*";
     			/*strcpy(szTo,(LPCTSTR)strDesPath);*/
  /* szTo[strDesPath.GetLength()+1]='\0';*/
   int nOk = 2000;
   CString strTitle = _T("正在拷贝文件,请稍候...");
   SHFILEOPSTRUCT FileOp;
//    const char * From = (const char *)szFrom;
//    const char * To = (const char *)szTo;
   WCHAR src[256] = {0};
   WCHAR des[256] = {0};
   memset(src, 0, 256*sizeof(WCHAR));
   memset(des, 0, 256*sizeof(WCHAR));
   _tcscpy(src, strSrcPath);//注意这里，之前copy不成功就是因为这里
   _tcscpy(des, strDesPath);
//    FileOp.hwnd = this->m_hWnd
//    FileOp.wFunc = FO_COPY; //执行文件拷贝
//    FileOp.pFrom = src;
//    FileOp.pTo = des;
//    FileOp.fFlags = FOF_ALLOWUNDO | FOF_WANTNUKEWARNING | FOF_NOCONFIRMATION;
//    FileOp.hNameMappings = NULL;
//    FileOp.lpszProgressTitle = strTitle;
   FileOp.fFlags = FOF_NOCONFIRMATION | FOF_SILENT;
   FileOp.hNameMappings = NULL;
   FileOp.hwnd = NULL;
   FileOp.lpszProgressTitle = NULL;
   FileOp.pFrom = src;
   FileOp.pTo = des;
   FileOp.wFunc = FO_COPY;
   nOk = SHFileOperation(&FileOp);
   if (FileOp.fAnyOperationsAborted) //防止出现低配置光驱BUG
   {
     nOk=1;
   }
   if (nOk==1)
   {
    return FALSE;
   }
   Sleep(200);
   return TRUE;
}
