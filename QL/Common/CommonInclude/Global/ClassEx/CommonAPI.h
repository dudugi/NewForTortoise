#pragma once
#include <set>
#include <vector>
class CCommonAPI
{
public:
	CCommonAPI(void);
	~CCommonAPI(void);

	/*******************************************************************
	 * @brief : ��鲢�����ļ���
	 * @author : wzl
	 * @date : 2017/3/6
	 * @param : 
	 * @example : 
	 * @return : 
	 *******************************************************************/
	BOOL MakeDirByCheck(CString strDir);

	/*******************************************************************
	 * @brief : ɾ��ָ���ļ���
	 * @author : wzl
	 * @date : 2017/3/28
	 * @param : strPath  ��Ҫɾ���ļ��е�·��
	 * @example : 
	 * @return : 
	 *******************************************************************/
	BOOL DeleteDirectory(const CString &strPath);

	//�����ļ��ؼ��ֻ�ȡ
	void GetIniKeyValue(CString strSection,CString strKeyName,CString &strKeyValue,CString strPathFile);
	void SetIniKeyValue(CString strSection,CString strKeyName,CString strKeyValue,CString strPathFile);

	/*******************************************************************
	 * @brief : д�����ļ���־
	 * @author : wzl
	 * @date : 2017/2/17
	 * @param :strFilePath д���ļ���λ�� strAction ��Ҫд�����ݵ��ַ��� bEnter �Ƿ���
	 * @example : 
	 * @return : 
	 *******************************************************************/
	void WriteLocalLogData(const char * strFilePath,const char * strContent,BOOL bEnter = FALSE);
	
	/*******************************************************************
	 * @brief : ��ȡ����ǰ�����ļ��е�·��
	 * @author : wzl
	 * @date : 2017/3/28
	 * @param : 
	 * @example : m_strWorkPath = GetWorkPath();//->����F:\Work_SVN\QlFileTransfer\Debug
	 * @return : 
	 *******************************************************************/
	CString GetWorkPath();

	/*
	 * @brief	�����ַ���ӳ��Ϊ���ַ���
	 *
	 * @param	lpcwszStr: [in] ��Ҫת�����ַ�����ָ��
	 * @param	lpszStr: [out] ��Ҫ�����ַ����Ļ�������ָ��.
	 * @param	dwSize: [in] �������Ĵ�С
	 *
	 * @return	TRUE: Succeed
	 *			FALSE: Failed

	 * @example	WCharToMByte(szW,szA,sizeof(szA)/sizeof(szA[0]));
	 */
	BOOL WCharToMByte(LPCWSTR lpcwszStr, LPSTR lpszStr, DWORD dwSize);

	/*
	 * @brief	���ַ���תΪunicode�ַ���
	 *
	 * @param	lpcszStr: [in] Ҫת�����ַ�����ָ��
	 * @param	lpwszStr: [out] ָ�����ת������ַ����Ļ�����.
	 * @param	dwSize: [in] ��������С
	 *
	 * @return	TRUE: �ɹ�
	 *			FALSE: ʧ��

	 * @example	MByteToWChar(szA,szW,sizeof(szW)/sizeof(szW[0]));
	 */
	/*
	  wchar_t wText[10] = {L"����ʾ��"};
	  char sText[20]= {0};
	  WCharToMByte(wText,sText,sizeof(sText)/sizeof(sText[0]));
	  MByteToWChar(sText,wText,sizeof(wText)/sizeof(wText[0]));
	*/
	BOOL MByteToWChar(LPCSTR lpcszStr, LPWSTR lpwszStr, DWORD dwSize);

	/*******************************************************************
	 * @brief : ����CCombox�б����ı��в��ҵ�һ��ƥ����ı�����Ϊ��ǰѡ��
	 * @author : wzl
	 * @date : 2017/5/27
	 * @param : 
	 * @example : 
	 * @return : 
	 *******************************************************************/
	static void SetCboselByName(CComboBox *pCbo,CString strName,BOOL bMatchUpperLower=TRUE);

	// ����CCombox�б����ı��в��ҵ�һ��ƥ����ı�����Ϊ��ǰѡ��		by WangZY 2018/05/25
	void SetCboselByNameAssociateMatch(CComboBox *pCbo,CString strName,BOOL bMatchUpperLower=TRUE);

	void SetCtrlString( _In_ HWND hDlg,_In_ int nID,_In_z_ _FormatMessage_format_string_ LPCTSTR pszFormat,...);

	//************************************
	// Method:    ����תƴ��
	// FullName:  CCommenAPI::ConvertChineseUnicodeToPyt
	// Access:    public 
	// Returns:   char*
	// Author:	  lida 2017/06/15
	// Parameter: wchar_t * chrstr
	//************************************
	CString ConvertChineseUnicodeToPyt(wchar_t* chrstr);

   /********************************************************************
   @author: wangzl
   @brief: ����ת��ƴ
   @Date:2018/09/03
   @param:
   @return:
   @example:
   ********************************************************************/
   CString ConvertChineseToShorthand(wchar_t* chrstr);


	//�ַ���ת��
	COleDateTime CString2OleDateTime(CString strValue);//�ַ�����ʽ��2016/07/07 00:00:00

	//��ȡ���а���ı�		by WangZY 2018/05/22
	void GetClipboard(CString &strGet);
	/*******************************************************************
	 * @brief : ���ü��а��ı�
	 * @author : wangzl
	 * @date : 2017/7/5
	 * @param : strClicpboardText ��Ҫ���õļ��а��ı�
	 * @example : 
	 * @return : 
	 *******************************************************************/
	void SetClipboard(CString strClicpboardText);

   //�����а��е�ͼƬת��Ϊ�ļ�  ���سɹ���ʧ��  wangzl 2018-09-17
   BOOL SaveClipboardToBmp(const CString & strFilePath);

   //�����а��е�ͼƬת���ڴ�  ���سɹ���ʧ��  duchen 2018-09-26
   BOOL SaveClipboardBmpToBuf(std::vector<BYTE> *pvecBuf, int *pnWidth = nullptr, int *pnHeight = nullptr);

   /********************************************************************
	@brief:	���ַ����ָ�
	@author:	Duc
	@param:	strOrgԭ�ַ��� delim�ָ��
	@return:	���ؼ���
	//duc��д��ʱ������׺�����  ���ÿ���ַ�ǰ������.  �ؼӸ���������
	@example:	
	*********************************************************************/
   std::set<CString> SplitStrToSet(const CString &strOrg, const TCHAR *delim,BOOL bWithSpot = TRUE);

   BOOL IsFloatEqual(float f1,float f2);


   //���ϵͳ�汾�Ƿ���Vista����ߵİ汾  
   bool   IsOsVersionVistaOrGreater();
   
   //��鲢����ϵͳ�汾ѡ��򿪳���ʽ  
   bool    ShellExecuteExOpen(CString appName, CString appPath);

   DWORD GetDirSize(CString strDirPath);

   /********************************************************************
   @author: wangzl
   @brief: ��ȡ�ַ���2�����ַ���1ƥ�������ַ���
   @Date:2018/09/05
   @param:
   @return:
   @example:
   ********************************************************************/
   CString GetMaxCommonSubstrFromStr2(CString strSrc1,CString strSrc2);

   //��ȡMAC��ַ
   bool GetMacByNetBIOS(CString& strMacOUT);
   bool GetAdapterInfo(int adapterNum, std::string& macOUT);

private:
   //���ͼƬ
   BOOL SaveBitmap(const BITMAP &bm,HDC hDC,HBITMAP hBitmap,LPCTSTR szFileName);
   //���ͼƬ���ڴ�
   BOOL SaveBitmapToBuf(const BITMAP &bm,HDC hDC,HBITMAP hBitmap,std::vector<BYTE> *pvecBuf);
};

extern CCommonAPI QLCOMAPI;