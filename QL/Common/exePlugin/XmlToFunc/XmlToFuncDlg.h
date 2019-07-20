
// XmlToFuncDlg.h : 头文件
//

#pragma once
#include <tinyxml.h>


// CXmlToFuncDlg 对话框
class CXmlToFuncDlg : public CDialogEx
{
// 构造
public:
	CXmlToFuncDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_XMLTOFUNC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

private:
   CStringList m_lstXml;

private:
   inline CString GetTinyXmlNodeString( TiXmlElement *);

   inline CString GetTinyXmlNodeAttribute(TiXmlElement *,const char * name);

   inline CString ParseElementToStr(__in TiXmlElement * pSrcElement,
      __in const char * name ,
      __in const CString & strDefaultValue,//默认的值
      __in const CString & strRetValue ,//如果需要显示时应该返回的值
      __inout BOOL & bHasShow, //之前已经有过显示了
      __inout int & nMaxLength, //返回值的最大数据
      __in const CString & strIncludeBy // 将应该返回的数据包起来 替换字符： %
      );

   void AddXmlToList(CString strFileName);

   void ParseXml(CString strFilePath);

   int GetStringMyLength(const CString &sText);

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
   afx_msg void OnBnClickedOk();
   afx_msg void OnBnClickedBtnAdd();
   afx_msg void OnBnClickedBtnDel();
   afx_msg void OnBnClickedBtnEmpty();
};
