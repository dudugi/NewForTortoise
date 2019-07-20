#pragma once
#include "MyCtrlEx\TabDlg\TabDialog.h"
#include "DBDatabaseFields.h"
#include "MyADOConnEx.h"
#include "FileTxt.h"
#include "Directory.h"
#include "afxwin.h"


// CDlgPane1Item3 �Ի���

class CDlgPane1Item3 : public CTabDialog
{
	DECLARE_DYNAMIC(CDlgPane1Item3)

public:
	CDlgPane1Item3(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgPane1Item3();
	

	/*******************************
	*************
		* @brief�������ݿⱣ�浽�ļ���
		* @author��zhangyx 2017/12/20
		* @example��
		* @return��
		  **************************
	********************************/
	void SaveDatabaseToFile(CString strFile, CString strDatabase = _T("[QLPLM]")); 
   
		/*******************************
	*************
		* @brief����ȡ�ֶ���
		* @author��zhangyx 2017/12/20
		* @example��
		* @return��
		  **************************
	********************************/
	void GetFieldsName(CDBDatabaseTableList *pDBDatabaseTableList,CString strDatabase, CString strTable);   

	/*******************************
	*************
		* @brief�����ͻ����ݿ���Ϣ��ȡ��������
		* @author��zhangyx 2017/12/20
		* @example��
		* @return��
		  **************************
	********************************/
	void PutClientDatabaseToClist(CDBDatabaseTableList &DBDatabaseTableListClient, CString strDatabase);	


	/*******************************
	*************
		* @brief���Ƚ����ݿ���Ϣ�����¿ͻ����ݿ�
		* @author��zhangyx 2017/12/20
		* @example��
		* @return��BOOL
					TRUE�����¿ͻ����ݿ�ɹ�
					FALSE�����¿ͻ����ݿ�ʧ��
		  **************************
	********************************/
	BOOL CompareDatabase(CDBDatabaseTableList &DBDatabaseTableList, CDBDatabaseTableList &DBDatabaseTableListClient, CString strDatabase);	


	/*******************************
		*************
		* @brief���Ƚ��������ݿ�ı��ֶ���
		* @author��zhangyx 2017/12/20
		* @example��
		* @return��BOOL
		TRUE���Ƚϳɹ�
		FALSE���Ƚ�ʧ��
		**************************
		********************************/
	BOOL CompareTableFields(CDBDatabaseTable* pDBDatabaseTable, CDBDatabaseTable* pDBDatabaseTableClient, CString strDatabase);		

	/*******************************
	*************
		* @brief�����ݱ�����ļ������ݿ���Ϣ�������ݿ�
		* @author��zhangyx 2017/12/20
		* @example��
		* @return��
		  **************************
	********************************/
	void CreateDatabaseFromFile(CString strDatabase, BOOL &bRet);			

		/*******************************
	*************
		* @brief����ȡ���ļ�ʱ�������ݿ��ֶ���Ϣ���
		* @author��zhangyx 2017/12/20
		* @example��
		* @return��CString�����ش������ݿ����
		  **************************
	********************************/
	CString GetFieldsInfoFromReadFile(CDBDatabaseTable *pDBDatabaseTable);			

	/*******************************
	*************
		* @brief���������ݱ�
		* @author��zhangyx 2017/12/20
		* @example��
		* @return��BOOL
					TRUE�������ɹ�
					FALSE������ʧ��
		  **************************
	********************************/
	BOOL CreateDataBaseTable(CString strDatabase, CString strTable, CString strlist);  

		/*******************************
	*************
		* @brief�����������ֶ����ͳ���
		* @author��zhangyx 2017/12/20
		* @example��
		* @return��
		  **************************
	********************************/
	void FilterFieldsLength(CString &strFieldsType, CString &strFieldsLength);		

		/*******************************
		*************
		* @brief����ӿͻ������ݿ�û�е���Ϣ
		* @author��zhangyx 2017/12/20
		* @example��
		* @return��BOOL
		TRUE����ӿͻ����ݿ�ɹ�
		FALSE����ӿͻ����ݿ�ʧ��
		**************************
		********************************/
	BOOL AddFieldsToDatabase(CString strDatabase, CString strTable, CDBDatabaseFields* pDBDatabaseFields);	

   //���������
   void SaveTriggerToFile(CString strFile); 
   BOOL GetTrigger(CString strFile);


// �Ի�������
	enum { IDD = IDD_DLG_PANE1_ITEM3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

private:
	CDBDatabaseTableList m_DBDatabaseTableList;  //�洢�������ݿ���Ϣ��
	//���ݿ����
	CMyADOConnEx *m_pADOConn;
	/*CString m_strDatabase;*/
	CFileTxt m_FileTxt;
	CDirectory m_CDirectroy;
	CStringList m_strList;
   CEdit m_edit_trigger;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSaveDir();
	afx_msg void OnBnClickedUpdateDatabaseButton();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnSave();
	afx_msg void OnBnClickedBtnUpdate();
	afx_msg void OnBnClickedUpdateFunctionButton();
	afx_msg void OnBnClickedBtnUpdateFunction();

   CString CompareDataName(CString strPath);
   
   //���������
   afx_msg void OnBnClickedBtnSaveTrigger();
   afx_msg void OnBnClickedBtnDirTrigger();
   afx_msg void OnBnClickedUpdateTriggerButton();
   afx_msg void OnBnClickedBtnUpdateTrigger();
};
