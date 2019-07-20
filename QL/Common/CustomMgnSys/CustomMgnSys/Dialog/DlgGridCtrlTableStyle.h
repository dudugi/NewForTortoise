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
// DlgGridCtrlTableStyle 表格样式对话框
*/
class CDlgBCGGrid;
class CDlgGridCtrlTableStyle : public CBCGPDialog
{
	DECLARE_DYNAMIC(CDlgGridCtrlTableStyle)

public:
	CDlgGridCtrlTableStyle(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgGridCtrlTableStyle();

// 对话框数据
	enum { IDD = IDD_DLG_TABLESTYLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
   
	DECLARE_MESSAGE_MAP()
private:
   CDlgBCGGrid* m_pDlgComGrid;
   CString m_strFileName;//数据源文件 
   S_GridCtrl_TableAttri m_TableAtrriData;
   //CString m_strDBTableName;	//2017/12/12 zhangt 查询的视图或者表名称
   
   // 显示筛选栏
   CBCGPButton m_CheckShowFilterBar;
   // 允许排序
   CBCGPButton m_CheckAllowSort;
   // 整行选择
   CBCGPButton m_CheckWholeRowSelect;
   // 显示合计栏
   CBCGPButton m_CheckShowTotalBar;
   // 多行选择
   CBCGPButton m_CheckMultiLineSelect;
   // 多行选择不失焦点
   CBCGPButton m_CheckMultiLineSelectNoLoseFocus;
   // 行高
   CEdit m_EditRowHeight;
   // 字体
   CEdit m_EditFont;
   // 显示全选
   CBCGPButton m_CheckAllShow;
   // 编辑全选
   CBCGPButton m_CheckAllEdit;
   // 标题过滤
   CBCGPButton m_CheckTitleFilter;

   // 行高spin控件
   CSpinButtonCtrl m_SpinRowHeight;
   // 字体spin控件
   CSpinButtonCtrl m_SpinFont;

   // 允许列标题拖动
   CBCGPButton m_Check_IsEnableDragCol;
   // 横向打印
   CBCGPButton m_CheckPrintHeXiang;

   CBCGPButton m_BTN_InitSysStyle;		//初始化系统目录
   CBCGPButton m_BTN_InitUserStyle;		//初始化用户目录

   int m_iRowHeight;
   int m_iFont;
	BOOL m_bHasAddShowField;			//是否有新增的显示列	by WangZY 2018/02/01
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
   //设置表格文件名以及表格属性数据
   void SetTableAttriFileNameAndData(CString strFileName,const S_GridCtrl_TableAttri &tableAtrriData/*,CString strDBTableName=_T("")*/);

   void CreateTableAttri(CString strFileName,CStringList& strlFieldName);

   S_GridCtrl_TableAttri &GetTableAttriData(){return m_TableAtrriData;}//获取表格属性数据

	//判断是否有新增显示字段		by WangZY 2018/02/01
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
