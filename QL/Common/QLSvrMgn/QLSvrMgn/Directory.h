#pragma once


// CDirectory
//by zhangyx 2017/12/3 ����Ŀ¼�ļ�
class CDirectory : public CWnd
{
	DECLARE_DYNAMIC(CDirectory)

public:
	CDirectory();
	virtual ~CDirectory();

	/*
	 * @brief	���ѡ��Ŀ¼
	 * @author	zhangt 2018/01/30
	 * @param	strRetPath ѡ���ȡ��Ŀ¼
	 * @param	strDefPath Ĭ�ϴ򿪵�Ŀ¼
	 * @return	TRUE��ȡ�ɹ� FALSE��ȡʧ��
	 */
	BOOL OpenDirectory(CString &strRetPath,CString strDefPath);


	BOOL OpenDirFile(CString &strRetPath,CString strDefPath,CString strDefFile,CString strFilter,BOOL bOpen=TRUE);

	/*
	 * @brief	����Ŀ¼
	 */
	BOOL CopyDirectory(CString strSrcPath, CString strDesPath);

	/*
	 * @brief	�����ļ�
	 */
	BOOL CopyDirFileAPI(CString strSrcPath, CString strDesPath);

protected:
	DECLARE_MESSAGE_MAP()
};


