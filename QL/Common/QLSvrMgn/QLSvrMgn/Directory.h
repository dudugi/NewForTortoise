#pragma once


// CDirectory
//by zhangyx 2017/12/3 拷贝目录文件
class CDirectory : public CWnd
{
	DECLARE_DYNAMIC(CDirectory)

public:
	CDirectory();
	virtual ~CDirectory();

	/*
	 * @brief	浏览选择目录
	 * @author	zhangt 2018/01/30
	 * @param	strRetPath 选择获取的目录
	 * @param	strDefPath 默认打开的目录
	 * @return	TRUE获取成功 FALSE获取失败
	 */
	BOOL OpenDirectory(CString &strRetPath,CString strDefPath);


	BOOL OpenDirFile(CString &strRetPath,CString strDefPath,CString strDefFile,CString strFilter,BOOL bOpen=TRUE);

	/*
	 * @brief	拷贝目录
	 */
	BOOL CopyDirectory(CString strSrcPath, CString strDesPath);

	/*
	 * @brief	拷贝文件
	 */
	BOOL CopyDirFileAPI(CString strSrcPath, CString strDesPath);

protected:
	DECLARE_MESSAGE_MAP()
};


