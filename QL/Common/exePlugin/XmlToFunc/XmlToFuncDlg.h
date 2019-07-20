
// XmlToFuncDlg.h : ͷ�ļ�
//

#pragma once
#include <tinyxml.h>


// CXmlToFuncDlg �Ի���
class CXmlToFuncDlg : public CDialogEx
{
// ����
public:
	CXmlToFuncDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_XMLTOFUNC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

private:
   CStringList m_lstXml;

private:
   inline CString GetTinyXmlNodeString( TiXmlElement *);

   inline CString GetTinyXmlNodeAttribute(TiXmlElement *,const char * name);

   inline CString ParseElementToStr(__in TiXmlElement * pSrcElement,
      __in const char * name ,
      __in const CString & strDefaultValue,//Ĭ�ϵ�ֵ
      __in const CString & strRetValue ,//�����Ҫ��ʾʱӦ�÷��ص�ֵ
      __inout BOOL & bHasShow, //֮ǰ�Ѿ��й���ʾ��
      __inout int & nMaxLength, //����ֵ���������
      __in const CString & strIncludeBy // ��Ӧ�÷��ص����ݰ����� �滻�ַ��� %
      );

   void AddXmlToList(CString strFileName);

   void ParseXml(CString strFilePath);

   int GetStringMyLength(const CString &sText);

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
