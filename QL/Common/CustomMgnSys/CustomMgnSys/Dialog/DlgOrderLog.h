#pragma once
#include "afxwin.h"



class CDlgBCGGrid;
class CDBLogInfoData;
// add by lida 2017/07/11
// CDlgOrderLog 订单日志对话框
/************************************************************************/
/* 查看某个订单的日志                                                   */
/************************************************************************/

class CDlgOrderLog : public CBCGPDialog
{
	DECLARE_DYNAMIC(CDlgOrderLog)

public:
	CDlgOrderLog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgOrderLog();

	void SetOrderCode(CString strOrderCode);

// 对话框数据
	enum { IDD = IDD_DLG_LOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	void InitComGridDlg();
	MAP_GridCtrl_AllData Package_NewGrid_Data(map<CString,CDBLogInfoData*> mapData);
	void InsertRowData(CString strValue,CString strFiedID,MAP_GridCtrl_RowData& map_row_data);
	DECLARE_MESSAGE_MAP()

private:
	CDlgBCGGrid*					m_pDlgComGrid;				//新表格控件
	S_GridCtrl_TableAttri			m_GridEx_tableAttri;		//新表格属性

	CString			m_strOrderCode;			//订单编号

public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	
};
