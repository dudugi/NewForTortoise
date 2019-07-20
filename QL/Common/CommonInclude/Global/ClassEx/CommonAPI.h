#pragma once
#include <set>
#include <vector>
class CCommonAPI
{
public:
	CCommonAPI(void);
	~CCommonAPI(void);

	/*******************************************************************
	 * @brief : 检查并创建文件夹
	 * @author : wzl
	 * @date : 2017/3/6
	 * @param : 
	 * @example : 
	 * @return : 
	 *******************************************************************/
	BOOL MakeDirByCheck(CString strDir);

	/*******************************************************************
	 * @brief : 删除指定文件夹
	 * @author : wzl
	 * @date : 2017/3/28
	 * @param : strPath  需要删除文件夹的路径
	 * @example : 
	 * @return : 
	 *******************************************************************/
	BOOL DeleteDirectory(const CString &strPath);

	//配置文件关键字获取
	void GetIniKeyValue(CString strSection,CString strKeyName,CString &strKeyValue,CString strPathFile);
	void SetIniKeyValue(CString strSection,CString strKeyName,CString strKeyValue,CString strPathFile);

	/*******************************************************************
	 * @brief : 写本地文件日志
	 * @author : wzl
	 * @date : 2017/2/17
	 * @param :strFilePath 写入文件的位置 strAction 需要写入内容的字符串 bEnter 是否换行
	 * @example : 
	 * @return : 
	 *******************************************************************/
	void WriteLocalLogData(const char * strFilePath,const char * strContent,BOOL bEnter = FALSE);
	
	/*******************************************************************
	 * @brief : 获取程序当前所在文件夹的路径
	 * @author : wzl
	 * @date : 2017/3/28
	 * @param : 
	 * @example : m_strWorkPath = GetWorkPath();//->返回F:\Work_SVN\QlFileTransfer\Debug
	 * @return : 
	 *******************************************************************/
	CString GetWorkPath();

	/*
	 * @brief	将宽字符串映射为新字符串
	 *
	 * @param	lpcwszStr: [in] 需要转换的字符串的指针
	 * @param	lpszStr: [out] 需要接受字符串的缓冲区的指针.
	 * @param	dwSize: [in] 缓冲区的大小
	 *
	 * @return	TRUE: Succeed
	 *			FALSE: Failed

	 * @example	WCharToMByte(szW,szA,sizeof(szA)/sizeof(szA[0]));
	 */
	BOOL WCharToMByte(LPCWSTR lpcwszStr, LPSTR lpszStr, DWORD dwSize);

	/*
	 * @brief	将字符串转为unicode字符串
	 *
	 * @param	lpcszStr: [in] 要转换的字符串的指针
	 * @param	lpwszStr: [out] 指向接收转换后的字符串的缓冲区.
	 * @param	dwSize: [in] 缓冲区大小
	 *
	 * @return	TRUE: 成功
	 *			FALSE: 失败

	 * @example	MByteToWChar(szA,szW,sizeof(szW)/sizeof(szW[0]));
	 */
	/*
	  wchar_t wText[10] = {L"函数示例"};
	  char sText[20]= {0};
	  WCharToMByte(wText,sText,sizeof(sText)/sizeof(sText[0]));
	  MByteToWChar(sText,wText,sizeof(wText)/sizeof(wText[0]));
	*/
	BOOL MByteToWChar(LPCSTR lpcszStr, LPWSTR lpwszStr, DWORD dwSize);

	/*******************************************************************
	 * @brief : 根据CCombox列表框的文本中查找第一个匹配的文本并设为当前选项
	 * @author : wzl
	 * @date : 2017/5/27
	 * @param : 
	 * @example : 
	 * @return : 
	 *******************************************************************/
	static void SetCboselByName(CComboBox *pCbo,CString strName,BOOL bMatchUpperLower=TRUE);

	// 根据CCombox列表框的文本中查找第一个匹配的文本并设为当前选项		by WangZY 2018/05/25
	void SetCboselByNameAssociateMatch(CComboBox *pCbo,CString strName,BOOL bMatchUpperLower=TRUE);

	void SetCtrlString( _In_ HWND hDlg,_In_ int nID,_In_z_ _FormatMessage_format_string_ LPCTSTR pszFormat,...);

	//************************************
	// Method:    汉子转拼音
	// FullName:  CCommenAPI::ConvertChineseUnicodeToPyt
	// Access:    public 
	// Returns:   char*
	// Author:	  lida 2017/06/15
	// Parameter: wchar_t * chrstr
	//************************************
	CString ConvertChineseUnicodeToPyt(wchar_t* chrstr);

   /********************************************************************
   @author: wangzl
   @brief: 汉字转简拼
   @Date:2018/09/03
   @param:
   @return:
   @example:
   ********************************************************************/
   CString ConvertChineseToShorthand(wchar_t* chrstr);


	//字符串转化
	COleDateTime CString2OleDateTime(CString strValue);//字符串格式：2016/07/07 00:00:00

	//获取剪切板的文本		by WangZY 2018/05/22
	void GetClipboard(CString &strGet);
	/*******************************************************************
	 * @brief : 设置剪切板文本
	 * @author : wangzl
	 * @date : 2017/7/5
	 * @param : strClicpboardText 需要设置的剪切板文本
	 * @example : 
	 * @return : 
	 *******************************************************************/
	void SetClipboard(CString strClicpboardText);

   //将剪切板中的图片转存为文件  返回成功或失败  wangzl 2018-09-17
   BOOL SaveClipboardToBmp(const CString & strFilePath);

   //将剪切板中的图片转到内存  返回成功或失败  duchen 2018-09-26
   BOOL SaveClipboardBmpToBuf(std::vector<BYTE> *pvecBuf, int *pnWidth = nullptr, int *pnHeight = nullptr);

   /********************************************************************
	@brief:	将字符串分割
	@author:	Duc
	@param:	strOrg原字符串 delim分割符
	@return:	返回集合
	//duc在写的时候当做后缀处理的  因此每个字符前都加了.  特加个参数处理
	@example:	
	*********************************************************************/
   std::set<CString> SplitStrToSet(const CString &strOrg, const TCHAR *delim,BOOL bWithSpot = TRUE);

   BOOL IsFloatEqual(float f1,float f2);


   //检查系统版本是否是Vista或更高的版本  
   bool   IsOsVersionVistaOrGreater();
   
   //检查并根据系统版本选择打开程序方式  
   bool    ShellExecuteExOpen(CString appName, CString appPath);

   DWORD GetDirSize(CString strDirPath);

   /********************************************************************
   @author: wangzl
   @brief: 获取字符串2中与字符串1匹配的最长的字符串
   @Date:2018/09/05
   @param:
   @return:
   @example:
   ********************************************************************/
   CString GetMaxCommonSubstrFromStr2(CString strSrc1,CString strSrc2);

   //获取MAC地址
   bool GetMacByNetBIOS(CString& strMacOUT);
   bool GetAdapterInfo(int adapterNum, std::string& macOUT);

private:
   //存个图片
   BOOL SaveBitmap(const BITMAP &bm,HDC hDC,HBITMAP hBitmap,LPCTSTR szFileName);
   //存个图片到内存
   BOOL SaveBitmapToBuf(const BITMAP &bm,HDC hDC,HBITMAP hBitmap,std::vector<BYTE> *pvecBuf);
};

extern CCommonAPI QLCOMAPI;