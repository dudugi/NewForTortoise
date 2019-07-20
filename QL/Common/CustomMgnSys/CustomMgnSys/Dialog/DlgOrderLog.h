#pragma once
#include "afxwin.h"



class CDlgBCGGrid;
class CDBLogInfoData;
// add by lida 2017/07/11
// CDlgOrderLog ������־�Ի���
/************************************************************************/
/* �鿴ĳ����������־                                                   */
/************************************************************************/

class CDlgOrderLog : public CBCGPDialog
{
	DECLARE_DYNAMIC(CDlgOrderLog)

public:
	CDlgOrderLog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgOrderLog();

	void SetOrderCode(CString strOrderCode);

// �Ի�������
	enum { IDD = IDD_DLG_LOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	void InitComGridDlg();
	MAP_GridCtrl_AllData Package_NewGrid_Data(map<CString,CDBLogInfoData*> mapData);
	void InsertRowData(CString strValue,CString strFiedID,MAP_GridCtrl_RowData& map_row_data);
	DECLARE_MESSAGE_MAP()

private:
	CDlgBCGGrid*					m_pDlgComGrid;				//�±��ؼ�
	S_GridCtrl_TableAttri			m_GridEx_tableAttri;		//�±������

	CString			m_strOrderCode;			//�������

public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	
};
