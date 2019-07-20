#pragma once
#include "stdafx.h"
#include <map>

//ģʽ�������ļ����͵�
enum {
   FTP_MODE_TYPE_PATTERN = 0     ,//�ư��ļ�
   FTP_MODE_TYPE_PROCESS         ,//�����ļ�
   FTP_MODE_TYPE_DESIGN          ,//����ļ�
   FTP_MODE_TYPE_ONLINE          ,//�ϻ��ļ�
   FTP_MODE_TYPE_OTHER           ,//�����ļ�
   FTP_MODE_TYPE_SIZE            ,//�ߴ��ļ�
   FTP_MODE_TYPE_PIC             ,//����ͼƬ�ļ���ģʽ    ��ָ����ͼ �����ǿ�ʽ�Ŀ�ʽͼ ����һ����
   FTP_MODE_TYPE_PIC_STYLE       ,//�ֻ�ͼƬ���ļ��� 
   FTP_MODE_TYPE_CHATFILE        ,//�����ļ����ϴ�
   FTP_MODE_TYPE_PIC_PRODETAIL   ,//��������ͼ            ��ָƽ��ͼ��
   FTP_MODE_TYPE_PIC_MODEL       ,//ģ��ͼ                ��PDM ��ģ��ͼƬ �� 
};

//���ʶ
enum{
	FTP_LIB_TYPE_BMP = 0,
	FTP_LIB_TYPE_STYLE,
	FTP_LIB_TYPE_PROCESS,
	FTP_LIB_TYPE_DENSITY,//�ܶȿ�
	FTP_LIB_TYPE_COMPONENT,//������
	FTP_LIB_TYPE_PATTERNCONFIG,//�ư����ÿ�
	FTP_LIB_TYPE_MODFILE,//�ư�Сͼ��
};

enum{
	FTP_WHOLE_TYPE_FILE = 0,
	FTP_WHOLE_TYPE_LIB,
	FTP_WHOLE_TYPE_EXCHANGE,//�����ļ���wholetyoe
	FTP_WHOLE_TYPE_COMMUNICATION,//Ⱥ��
	FTP_WHOLE_TYPE_WEB,//web��
};


class CFileTransferEx
{
public:
	CFileTransferEx(CString strWorkPath,HWND hProcessHwnd = NULL,S_FileTrans_LoginType nLoginType = En_Login_User);
	~CFileTransferEx();
public:
	//�ϴ��ļ����ļ�ȫ·���б�
	CStringList m_UploadList;
	//ɾ���ļ����ļ������б�
	CStringList m_DelList;

	std::map<CString,CString> m_DownMsg;

	//�����ļ��е��б� pair�зֱ���org��Դ�ļ����� dst��Ŀ���ļ�����
	std::vector<pair<CString,CString>> m_vecCopyList;
public:

	void Init(CString strOrderNo,int nFileType,int nWholeType = 0);

	int Upload(int nFlag = UNDESIGN_FLAG,BOOL bDelSrc = FALSE);

    /*******************************************************************
	 * @brief : ���غ����Ľӿ�
	 * @author : wzl
	 * @date : 2016/12/20 17:10
	 * @param : 
	 * @example : 
	 * @return : 
	 *******************************************************************/
	int DownLoad(int nFlag = UNDESIGN_FLAG);

	  /*******************************************************************
   * @brief : ����ͬDownLoad��������ָ���汾���ļ�
   * @author : dc
   * @date : 2018/9/13 10:02
   * @param : 
   * @example : 
   * @return : 
   *******************************************************************/
   int DownLoadbyVersion(int nVersion, int nFlag = UNDESIGN_FLAG);

	/*******************************************************************
	* @brief : �ϴ�����������ͬUpload������ָ���ϴ����ĸ������ļ���
	* @author : dc
	* @date : 2018/9/13 8:52
	* @param : nVersion: �汾�ţ�-1ʱͬUpload, bDelSrc: �Ƿ�ɾ��Դ�ļ��ı�ʶ
	* @example : 
	* @return : (0-9)
	0-�ϴ��ļ��б��ǿյ�
	*******************************************************************/

	int UploadToVersion(int nVersion, int nFlag = UNDESIGN_FLAG,BOOL bDelSrc = FALSE);

	/*******************************************************************
	 * @brief : �����ļ��нӿ�
	 * @author : wzl
	 * @date : 2017/1/18 11:39
	 * @param : 
	 * @example : 
	 * @return : 
	 *******************************************************************/
	int DownLoadDir(CString strLocalDir,int nFlag = UNDESIGN_FLAG);
	int DownLoadDir(CString strLocalDir,CString strOrderNo,int nFlag = UNDESIGN_FLAG);
   int DownLoadDirByVersion(int nVersion, CString strLocalDir, const CString &strOrderNo, int nFlag = UNDESIGN_FLAG);

   /*******************************************************************
	 * @brief : �����ļ���ʱÿ���ļ��������������Ϣ
	 * @author : wzl
	 * @date : 2017/5/15
	 * @param : 
	 * @example : 
	 * @return : 
	 *******************************************************************/
	int DownLoadDirMsg(CString strLocalDir,int nFlag = UNDESIGN_FLAG,DWORD dwStyle = FS_DEFAULT);
	int DownLoadDirMsg(CString strLocalDir,CString strOrderNo,int nFlag = UNDESIGN_FLAG,DWORD dwStyle = FS_DEFAULT);

   /*******************************************************************
	 * @brief : ���ݴ���Ĵ�����ֵ�����ض�Ӧ�Ĵ�����Ϣ
	 * @author : wzl
	 * @date : 2016/12/20 13:45
	 * @param : nerrno Ҫ��ѯ�Ĵ�����ֵ
	 * @example : GetErrorMsg(0);->�����ϴ���δ��ֵ;
	 * @return : ���ػ�ȡ���Ĵ�����Ϣ
	 *******************************************************************/
	CString GetErrorMsg(int nerrno);

   CString GetVersion();

   BOOL IsHttpMode();

   	/*******************************************************************
	 * @brief : ������ݿ����Ƿ��Ѿ����ڸö�������Ϣ
	 * @author : wzl
	 * @date : 2017/3/1 11:31
	 * @param : 
	 * @example : 
	 * @return : 0������  1����
	 *******************************************************************/
	int CheckOrderExit(CString strOrderNo);

	/*******************************************************************
	 * @brief : ��������ļ��е���Ϣ�ܷ��¼���ݿ�
	 * @author : wzl
	 * @date : 2017/2/10 10:31
	 * @param : 
	 * @example : 
	 * @return : 
	 *******************************************************************/
	BOOL CheckDBLogin();

	/*******************************************************************
	 * @brief : ������¼���� ���ص�¼�Ľ��
	 * @author : wzl
	 * @date : 2017/3/31
	 * @param : 
	 * @example : 
	 * @return : TRUE ��¼�ɹ�  FALSE ��¼ʧ��
	 *******************************************************************/
	BOOL PopLogin();

	//��ȡ���Ŷ�Ӧ��ģ�嵥��  
	CString GetSampleOrder(CString strOrderNo);
	//���õ��Ŷ�Ӧ��ģ�嵥��
	int SetOrderSampleOrder(CString strOrderNo,CString strSampleNo);

	void SetHwnd(HWND hProcessHwnd);
	/*******************************************************************
	 * @brief : ���ö�������Ϣ
	 * @author : wzl
	 * @date : 2016/12/20 13:50
	 * @param : strOrderNo �ϴ��ļ���صĶ�����
	 * @example : 
	 * @return : 
	 *******************************************************************/
	void SetOrderInfo(CString strOrderNo);

	/*******************************************************************
	 * @brief : ���ô����ļ�������
	 * @author : wzl
	 * @date : 2017/4/25
	 * @param : 
	 * @example : 
	 * @return : 
	 *******************************************************************/
	void SetSize(CString strSize);

	/*******************************************************************
	 * @brief : ͨ����չ��������Ӧ���ļ� �������̣�
				1.��ȡ����ļ��������е��ļ���Ϣ
				2.��չ���ȶ�
				3.�������ض�������
	 * @author : wzl
	 * @date : 2017/3/30
	 * @param : 
	 * @example : DownLoadByExt(_T(".txt"),0);
	 * @return : 
	 *******************************************************************/
	int DownLoadByExt( CString strLocalDir,CString strOrderNo,CString strExtension,int nFlag = UNDESIGN_FLAG,BOOL bDir = FALSE,DWORD dwStyle = FS_DEFAULT);

	
	int Del(int nFlag = UNDESIGN_FLAG);

	/*******************************************************************
	 * @brief : ���ݴ���Ķ����ź��ļ����ͷ��ض�Ӧ�ļ����µ��ļ��б�
	 * @author : wzl
	 * @date : 2016/12/21 9:31
	 * @param : strOrderNo  ������  nType  �ļ�����0-�ư� 1-����
	 * @example : 
	 * @return : 
	 *******************************************************************/
	int GetList(int nFlag = UNDESIGN_FLAG);
   int GetListEx(int nFlag = UNDESIGN_FLAG,DWORD dwStyle = FS_DEFAULT);

   /*******************************************************************
	 * @brief : ���ݴ���汾�ź͵�ǰ������ȡ�ļ��б�
	 * @author : dc
	 * @date : 2018/9/12 16:05
	 * @param : nVersion �汾�ţ� -1ʱͬGetList
	 * @example : 
	 * @return : 
	 *******************************************************************/
   int GetListByVersion(int nVersion, int nFlag = UNDESIGN_FLAG);

	/*******************************************************************
	 * @brief : ɾ���ļ���
	 * @author : wzl
	 * @date : 2017/5/12
	 * @param : 
	 * @example : 
	 * @return : 
	 *******************************************************************/
	int DelDir(int nFlag = UNDESIGN_FLAG);
	int DelDir(CString strOrderNo,int nFlag = UNDESIGN_FLAG);

	//�ж��ļ��Ƿ����
	int IsFileExist(CString strFileName);


   /*******************************************************************
   * @brief : ���ݵ�ǰ�������ļ�������ǹ��գ������ƶ��ļ���������ư棬�����ļ�
   * @author : dc
   * @date : 2018/9/5 13:54
   * @param : bMove ��ʾ���ƶ����Ǹ��Ʋ���  �ڲ������� �ⲿ�Լ�����
   * @example : 
   * @return : 
   *******************************************************************/
   int BackupFile(const CString &strVersionName, CString strOrderNo, int nFlag = UNDESIGN_FLAG,BOOL bMove = FALSE);

   /*******************************************************************
   * @brief : ����ָ���汾���µ�ǰ�汾�������ƶ���ǰ�ļ��������ļ��У�
   * @author : dc
   * @date : 2018/10/18 16:02
   * @param : 
   * @example : 
   * @return : 
   *******************************************************************/
   int CopyVersionToNewCreatedOne(const CString &strNewVersionName, const CString &strOldVersionName, CString strOrderNo, int nFlag = UNDESIGN_FLAG);

   /*******************************************************************
   * @brief : Զ�̸����ļ����ļ��У�/��β�������ļ��У�
   * @author : dc
   * @date : 2018/9/5 13:54
   * @param : OrgΪ����Դ DstΪ����Ŀ��
   * @example : 
   * @return : 
   *******************************************************************/
   int RemoteCopyFile(const CString &sOrgOrder, int nOrgVersion, int nOrgFileType, const CString &sOrgSize,  
      const CString &sDstOrder, int nDstVersion, int nDstFileType,  const CString &sDstSize, 
      int nFlag = UNDESIGN_FLAG);

   /*******************************************************************
   * @brief : Զ�̸����ļ����ļ��У�/��β�������ļ��У�
   * @author : dc
   * @date : 2018/9/5 13:54
   * @param : OrgΪ����Դ DstΪ����Ŀ�� ���ӿ�����
   * @example : 
   * @return : 
   *******************************************************************/
   int RemoteCopyFile(const CString &sOrgOrder, int nOrgVersion, int nOrgFileType, const CString &sOrgSize,int nOrgWholeType ,  
      const CString &sDstOrder, int nDstVersion, int nDstFileType,  const CString &sDstSize ,int nDstWholeType  , 
      int nFlag = UNDESIGN_FLAG);

   CString GetStr(int nWholeType, int nFileType);

private:
	FILETRANS * m_pFileTrans;
   //һЩ��Ҫ�������Ϣ 
	CString m_strOrderNo;//����
   //����
   CString m_strSize;
};

