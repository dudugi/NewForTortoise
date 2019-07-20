#pragma once
#include "FileTransferDef.inl"
#include "FileTrans_Handle.h"
#include "curl\curl.h"
#include "QL_HttpErrorCode.h"

//QLʹ�õ�http�ͻ���
/*
   IP:http://192.168.2.77:8080
   �����˶Խ����ӽӿڣ�

   ͨ��ͷ
      userName:qildoc
      token:password   �˴����뾭��AES����  
      randKey:         �˴�Ϊ���ܵ�key
      ��Կ  woshijiamisuijis

   Ҫ���жϷ�����  403��ʾ�û��������������

   ��ȡ�б�
      /file/get/dir?path=$$     ·��Ҫ�󾭹�URL����

   �ϴ�
      /file/upload?cFileName=$$  POST  ���� file �ļ�·��   remoteFileName �ƶ��ļ�����  ·�� �ƶ��ļ���Ҫ�󾭹�URL����
   ����
      /file/download?cFileName=$$  POST ����Ҫ�󾭹�url����
   ɾ��
      /file/delete/dir POST ���� cFileName=$$  ����Ҫ�󾭹�url����
   �����ļ��� ��Ϊ��������Ŀ¼������ʱ���Զ�������ӦĿ¼ ���Ŀǰû���ṩ��Ӧ�ӿ�
   �ƶ� ����
      /file/command POST 
      JSON�����ʽ {"command":"move/copy","params":[{"srcFile":"123","desFile":"456"}*N]}
      ��ʵ��Ҳ����
      Ҫ��srcFile desFile ����������URL����
*/

class QL_HttpClient
{
public:
   //************************************
   // ��������: QL_HttpClient
   // ����Ȩ��: public 
   // ��������: 2019/01/04
   // �� �� ��: wangzl
   // ����˵��: 
   // �� �� ֵ: 
   // ��������: const CString & strIP
   // ��������: const CString & strUser
   // ��������: const CString & strPassword
   //************************************
   QL_HttpClient(const CString & strIP,const CString & strUser, const CString & strPassword);
   ~QL_HttpClient(void);

   void Http_ProcessMsg(HWND hWnd);
public:

   //************************************
   // ��������: Http_Delete
   // ����Ȩ��: public 
   // ��������: 2019/01/04
   // �� �� ��: wangzl
   // ����˵��: ɾ��������Ӧ���ļ������ļ���
   // �� �� ֵ: int
   // ��������: const CString & strServerFileName
   //************************************
   int Http_Delete(const CString & strServerFileName);

   //************************************
   // ��������: Http_Getlist
   // ����Ȩ��: public 
   // ��������: 2019/01/04
   // �� �� ��: wangzl
   // ����˵��: ��ȡԶ��Ŀ¼���ļ��б�
   // �� �� ֵ: int 0:ʧ��;1:�ɹ�.
   // ��������: const CString & strPath
   // ��������: FileMsg * * ppItems
   // ��������: int * num
   // ��������: DWORD dwStyle �Ƿ�����ļ��� FS_NODIR �����ļ���
   //************************************
   int Http_Getlist(const CString & strPath,FileMsg **ppItems,int *num,DWORD dwStyle);

   //************************************
   // ��������: Http_Download
   // ����Ȩ��: public 
   // ��������: 2019/01/04
   // �� �� ��: wangzl
   // ����˵��: �����ļ�������
   // �� �� ֵ: int 0 ʧ�� ;1 �ɹ�;2 �ļ�������;
   // ��������: const CString & strLocalPath ���ص��ļ�·��
   // ��������: const CString & strServerPath ������·��
   //************************************
   int Http_Download(const CString &strLocalPath, const CString & strServerPath);

   //************************************
   // ��������: Http_DownDir
   // ����Ȩ��: public 
   // ��������: 2019/01/04
   // �� �� ��: wangzl
   // ����˵��: �����ļ����е����ݵ�ָ��·��
   // �� �� ֵ: int 0ʧ�� 1�ɹ�
   // ��������: const CString & strLocalDir �����ļ�·��
   // ��������: const CString & strServerDirName �������ļ�·��
   // ��������: int & nFileNum �ļ�����
   // ��������: int & nDirNum �ļ�������
   // ��������: HWND hWnd ������Ϣ�õľ��  ÿ���ļ�
   // ��������: DWORD wpMsg  ��Ϣ
   // ��������: int nFlag ��־
   // ��������: BOOL bNoDir  �������ļ���ʱ�Ƿ����ļ���  TRUE ���������ļ��н������ļ������ص�ָ����Ŀ¼
   // ��������: BOOL bZipDel ��ѹ�ɹ����Ƿ�ɾ��
   // ��������: BOOL bUnZipFailRename ��ѹʧ�ܺ��Ƿ�������
   //************************************
   int Http_DownDir(const CString & strLocalDir, const CString &strServerDirName,int &nFileNum, int &nDirNum,HWND hWnd,DWORD wpMsg,int nFlag,BOOL bNoDir,BOOL bZipDel,BOOL bUnZipFailRename);

   //************************************
   // ��������: Http_DownByEx
   // ����Ȩ��: public 
   // ��������: 2019/01/04
   // �� �� ��: wangzl
   // ����˵��: ���ݺ�׺������ָ���ļ��е��ļ�
   // �� �� ֵ: int 0ʧ�� 1�ɹ� 2Ŀ¼������
   // ��������: const CString & strLocalDir �����ļ���
   // ��������: const CString & strServerDirName �ƶ��ļ�������
   // ��������: const CString & strExtension ��չ��
   // ��������: FilePathMsg * * szFilePath �ļ�����Ϣ
   // ��������: int & nFileNum �ļ��ĸ���
   // ��������: BOOL bDir �Ƿ������ļ��е����ݲ�����  TRUE ���
   // ��������: HWND hWnd ������Ϣ�ľ��
   // ��������: DWORD wpMsg ���յ���Ϣ
   // ��������: int nFlag ��־
   // ��������: BOOL bNoDir �Ƿ������ļ��������洢���ļ��е��ļ� TRUE ʱ ���ļ��е������ļ������ص���ǰ�ļ���
   // ��������: BOOL bZipDel ��ѹ���Ƿ�ɾ���ļ�
   // ��������: BOOL bUnZipFailRename ��ѹʧ�ܺ��Ƿ��������ļ�
   //************************************
   int Http_DownByEx( const CString & strLocalDir, const CString &strServerDirName, const CString & strExtension,FilePathMsg ** szFilePath,int &nFileNum,BOOL bDir,HWND hWnd,DWORD wpMsg,int nFlag,BOOL bNoDir,BOOL bZipDel,BOOL bUnZipFailRename);

   //************************************
   // ��������: Http_Upload
   // ����Ȩ��: public 
   // ��������: 2019/01/04
   // �� �� ��: wangzl
   // ����˵��: �ϴ��ļ�
   // �� �� ֵ: int 0ʧ�� 1�ɹ�
   // ��������: const CString & strLocalPath �ϴ��ı����ļ�
   // ��������: const CString & strServerPath �ϴ����ƶ˵�·��
   // ��������: const CString & strServerFileName �ϴ����ƶ��Ժ��Ӧ���ļ���
   //************************************
   int Http_Upload(const CString & strLocalPath, const CString & strServerPath,const CString & strServerFileName);

   //************************************
   // ��������: Http_Move
   // ����Ȩ��: public 
   // ��������: 2019/01/04
   // �� �� ��: wangzl
   // ����˵��: �ƶ�����
   // �� �� ֵ: int 0ʧ�� 1�ɹ� 
   // ��������: const CString & strOrgPath ��Ҫ�ƶ����ļ������ļ���
   // ��������: const CString & strDstPath ��Ҫ�ƶ������ļ�·����Ŀǰ��֧��·���� ��֧���ļ��ƶ��޸�����
   // ʾ��: Http_Move(_T("������/123/test.txt"),_T("������/456"))   ��֧��Http_Move(_T("������/123/test.txt"),_T("������/123/456.txt")) 
   //************************************
   int Http_Move(const CString & strOrgPath, const CString & strDstPath);

   //************************************
   // ��������: Http_Copy
   // ����Ȩ��: public 
   // ��������: 2019/01/04
   // �� �� ��: wangzl
   // ����˵��: �ļ�����
   // �� �� ֵ: int
   // ��������: const CString & strOrgPath ��Ҫ���Ƶ��ļ������ļ��е�·��
   // ��������: const CString & strDstPath ��Ҫ���Ƶ����ļ���·��
   //************************************
   int Http_Copy(const CString & strOrgPath, const CString & strDstPath);

private:
   //�ڲ�ʹ�õ�һЩ�ӿ�

   //************************************
   // ��������: IsLoginError
   // ����Ȩ��: private 
   // ��������: 2019/01/04
   // �� �� ��: wangzl
   // ����˵��: �ж��ǲ��ǵ�¼ʧ�� Ŀǰ���ֵΪ403״̬��
   // �� �� ֵ: BOOL
   // ��������: CURL * cUrl
   //************************************
   BOOL IsLoginError(CURL * cUrl);

   //************************************
   // ��������: Http_Commond
   // ����Ȩ��: private 
   // ��������: 2019/01/04
   // �� �� ��: wangzl
   // ����˵��: http move copy����Ľӿ�  
   // �� �� ֵ: int 0ʧ�� 1�ɹ�
   // ��������: const char * szCommand
   // ��������: vector<pair<CString,CString>> vec_CommandParams//�����Ӧ�Ĳ�����Ϣ key ��Ӧsrc value��Ӧ dstPath
   //************************************
   int Http_Commond(const char * szCommand,vector<pair<CString,CString>> vec_CommandParams);

   //************************************
   // ��������: AppendUserInfo
   // ����Ȩ��: private 
   // ��������: 2019/01/04
   // �� �� ��: wangzl
   // ����˵��: ׷���û���Ϣ��ͷ��Ϣ�� 
   // �� �� ֵ: curl_slist *
   // ��������: curl_slist * plist ����ΪNULL
   //************************************
   curl_slist * AppendUserInfo(curl_slist * plist);

   //���ܵ�
   void GetEntryString( const CString & strUnEncrypted , CString & strEncodeString, CString & strEncryptKey );
   bool Init(const std::string& key, const std::string& iv);
   std::string Encrypt(const std::string& plainText);
   std::string Decrypt(const std::string& cipherTextHex);

   //URL���� 
   CString EncodeParam(const CString & strParam);
   
private:
   CString m_strIP;//IP��ַ
   CString m_strUserName;//�û���
   CString m_strUserPassword;//����

   HWND m_hProcess;//���ڽ�����Ϣ�ľ��
};

