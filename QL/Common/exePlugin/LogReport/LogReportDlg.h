
// LogReportDlg.h : 头文件
//

#pragma once


// CLogReportDlg 对话框
class CLogReportDlg : public CDialogEx
{
// 构造
public:
	CLogReportDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_LOGREPORT_DIALOG };

private:
   DWORD m_dwtick;

protected:
   //清空部分数据
   void ClearUp();

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
   afx_msg void OnClose();
protected:
   afx_msg LRESULT OnLogLocalSwap(WPARAM wParam, LPARAM lParam);
public:
   afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
   afx_msg void OnBnClickedBtnClear();
   afx_msg void OnClear();
};
