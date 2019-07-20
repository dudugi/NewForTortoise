#pragma once
#include <map>
#include <vector>
//#include "DialogExMid\DialogExMid.h"

#include "CDataTableDlgDefine.h"
#include "CGridCtrlTableAttributeOp.h"
//#include "afxcmn.h"
//#include "afxwin.h"

//#include "../QLBCG/DlgBCGGrid.h"

/*
// DlgGridCtrlTableStyle �����ʽ�Ի���
*/
class CDlgBCGGrid;
class CDlgGridCtrlTableStyle : public CBCGPDialog
{
	DECLARE_DYNAMIC(CDlgGridCtrlTableStyle)

public:
	CDlgGridCtrlTableStyle(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgGridCtrlTableStyle();

// �Ի�������
	enum { IDD = IDD_DLG_TABLESTYLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
   
	DECLARE_MESSAGE_MAP()
private:
   CDlgBCGGrid* m_pDlgComGrid;
   CString m_strFileName;//����Դ�ļ� 
   S_GridCtrl_TableAttri m_TableAtrriData;
   //CString m_strDBTableName;	//2017/12/12 zhangt ��ѯ����ͼ���߱�����
   
   // ��ʾɸѡ��
   CBCGPButton m_CheckShowFilterBar;
   // ��������
   CBCGPButton m_CheckAllowSort;
   // ����ѡ��
   CBCGPButton m_CheckWholeRowSelect;
   // ��ʾ�ϼ���
   CBCGPButton m_CheckShowTotalBar;
   // ����ѡ��
   CBCGPButton m_CheckMultiLineSelect;
   // ����ѡ��ʧ����
   CBCGPButton m_CheckMultiLineSelectNoLoseFocus;
   // �и�
   CEdit m_EditRowHeight;
   // ����
   CEdit m_EditFont;
   // ��ʾȫѡ
   CBCGPButton m_CheckAllShow;
   // �༭ȫѡ
   CBCGPButton m_CheckAllEdit;
   // �������
   CBCGPButton m_CheckTitleFilter;

   // �и�spin�ؼ�
   CSpinButtonCtrl m_SpinRowHeight;
   // ����spin�ؼ�
   CSpinButtonCtrl m_SpinFont;

   // �����б����϶�
   CBCGPButton m_Check_IsEnableDragCol;
   // �����ӡ
   CBCGPButton m_CheckPrintHeXiang;

   CBCGPButton m_BTN_InitSysStyle;		//��ʼ��ϵͳĿ¼
   CBCGPButton m_BTN_InitUserStyle;		//��ʼ���û�Ŀ¼

   int m_iRowHeight;
   int m_iFont;
	BOOL m_bHasAddShowField;			//�Ƿ�����������ʾ��	by WangZY 2018/02/01
	std::vector<CString/*strFieldId*/> m_vecOldShowFieldId;

   CButton m_Check_UpdateServerStyle;
   CEdit m_Edit_PageRows;
   int m_iPageRows;
   int m_backupPageRows;
private:
   void InitGrid();
   void GetDataFromDlg();
   int GetPosInVector(CString strValue,const std::vector<CString> &vecValue);
   void SetFontToGrid(int iFont);
   void InitDlg();
   void GetMapData(MAP_GridCtrl_AllData  &map_all_data);
public:
   virtual BOOL OnInitDialog();
   //���ñ���ļ����Լ������������
   void SetTableAttriFileNameAndData(CString strFileName,const S_GridCtrl_TableAttri &tableAtrriData/*,CString strDBTableName=_T("")*/);

   void CreateTableAttri(CString strFileName,CStringList& strlFieldName);

   S_GridCtrl_TableAttri &GetTableAttriData(){return m_TableAtrriData;}//��ȡ�����������

	//�ж��Ƿ���������ʾ�ֶ�		by WangZY 2018/02/01
	BOOL HasAddShowField();
public:
   afx_msg void OnBnClickedOk();   
   afx_msg void OnBnClickedCheckAllshow();
   afx_msg void OnBnClickedCheckAlledit();
   afx_msg void OnBnClickedCheckShow();
  
   afx_msg void OnDeltaposSpinRowHeight(NMHDR *pNMHDR, LRESULT *pResult);
   afx_msg void OnDeltaposSpinFont(NMHDR *pNMHDR, LRESULT *pResult);
   afx_msg void OnEnKillfocusEditRowheight();
   afx_msg void OnEnKillfocusEditFont();
   afx_msg void OnBnClickedButtonSaveas();   
  
   afx_msg void OnBnClickedBtnInitsysstyle();
   afx_msg void OnBnClickedBtnInituserstyle();
   //afx_msg void OnBnClickedBtnReadcolname();   
};
