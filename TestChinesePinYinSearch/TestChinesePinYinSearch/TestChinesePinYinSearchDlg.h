
// TestChinesePinYinSearchDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "lycombox.h"
#include "afxcmn.h"
#include "LY2ComBox.h"
#include <MutiSelComboBox\MutiSelComboBoxBCGDlg.h>
//#include "PinYinComboBox\PinYinComboBox.h"

class CPinYinComboBox;

// CTestChinesePinYinSearchDlg 对话框
class CTestChinesePinYinSearchDlg : public CDialogEx
{
// 构造
public:
	CTestChinesePinYinSearchDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CTestChinesePinYinSearchDlg();

// 对话框数据
	enum { IDD = IDD_TESTCHINESEPINYINSEARCH_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
   CEdit m_edit1;
   afx_msg void OnBnClickedButton1();
   afx_msg void OnBnClickedBtnDelusertext();
   CLY2ComBox m_cbo1;
   afx_msg void OnBnSetfocusButton1();
   afx_msg void OnSetFocus(CWnd* pOldWnd);
   afx_msg void OnKillFocus(CWnd* pNewWnd);
   afx_msg void OnCbnSetfocusCombo1();
   CComboBox m_cboBox2;
   CComboBoxEx m_cboExt;
   afx_msg void OnBnClickedButton2();
   CMutiSelComboBoxBCGDlg *m_pPinYinCombobox;
   //CPinYinComboBox *m_pPinYinCombobox;
   afx_msg void OnBnClickedBtnClear();
   CEdit m_edit3;
   afx_msg void OnBnClickedButton3();

   int m_nEditCount;
   int m_nSelCount;
   CString m_sTextPinYin;
   afx_msg void OnBnClickedBtnUpdate();
   afx_msg void OnEnChangeMfceditbrowseName();
   afx_msg void OnBnClickedBtnSeldlg();
   afx_msg void OnBnClickedButton4();
   afx_msg void OnBnClickedButton5();
   afx_msg void OnBnClickedButton6();
   afx_msg void OnBnClickedButton7();
   CString m_sCBOBox2;
   afx_msg void OnBnClickedButton8();
   CEdit m_editContents;
   virtual void OnOK();
};
