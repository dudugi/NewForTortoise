#pragma once
/*************************************************
// <�ļ�>: DlgCommonChatContent.h
// <˵��>: ������������ ����ѡ���ѡ�������� ���Ա༭��ѡ��
// <����>: duchen
// <����>: 2019/02/22
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
#include "afxwin.h"
#include <functional>
#include <deque>
#include "ListBoxHover.h"
#include "..\Bubble\MyBubble.h"


// CDlgCommonChatContent �Ի���

class CDlgCommonChatContent : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgCommonChatContent)

public:
	CDlgCommonChatContent(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgCommonChatContent();

// �Ի�������

   std::function<void(const CString &sText)> m_funcOutputText; //������ֵĻص�����
   std::function<void(const CString &sText)> m_funcCreateText; //Ŀǰû��
   void SetSettingPath(const CString &sPath); //���ü�¼��ѡ��������ļ���·��
   BOOL CreateDlgIndirect(CWnd* pParent); //�����Ի����õĽӿ� ���Բ�������Դ�ļ�����
   void Init(int nXLeft = -1, int nYBottom = -1); //��ʼ������
protected:
	DECLARE_MESSAGE_MAP()
private:
   CListBoxHover m_lstBox; //��ѡ��Listbox�ؼ� ���Ҳ�ġ��ʡ�ͼ����Խ���༭����
   CEdit m_EditFilter; //���������ؼ� ��������ɸѡ��ѡ��
   enum Status //����״̬
   {
      SELECT_CONTENT, //ѡ�������ֻ���
      CREATE_CONTENT, //�����������ֻ���
      EDIT_CONTENT,   //�༭�������ֻ���
      DELETE_CONFIRM, //ɾ����������ȷ�ϻ���
   };
   Status m_eStatus; //����״̬

   CButton m_btnAdd; //��Ӱ�ť
   CButton m_btnReturn; //���ذ�ť
   CButton m_btnDeleteConfirm; //ɾ��ȷ�ϰ�ť
   CStatic m_staticTitleCreate; //����������ʾ����
   CFont m_ListFont; //�б�����
   CFont m_HintFont; //˵����������
   CFont m_BigHintFont; //��˵����������
   std::deque<CString> m_deqContents; //���г�����������
   CButton m_btnCreateOK; //��������ȷ����ť
   CEdit m_editNew; //�����������ֱ༭�ؼ�
   CButton m_btnDelete; //ɾ����ť
   CButton m_btnEditFinish; //�༭��ɰ�ť
   CString m_sEditItemStringOld; //�༭ǰ�ַ��� �����жϱ༭ǰ�����ޱ仯
   CMyBubble m_Bubble; //С��ʾ��������״��
   int m_nXLeft; //�������������
   int m_nYBottom; //�������·�����
   CString m_sSettingFilePath; //�����ļ���·�������泣�����ֵĵط���
   void ShowEditWindow(BOOL bNew, const CString &sInitText); //����༭���棨�������޸ģ�
   void TurnBack(); //����ǰ����
   BOOL WriteFile(); //д�������ļ�
   afx_msg void OnBnClickedBtnReturn(); //���ذ�ť
   afx_msg void OnLbnSelchangeListContent(); //ѡ������
   afx_msg void OnEnChangeEditSearch(); //���ֱ仯
   afx_msg void OnBnClickedBtnAdd(); //��Ӱ�ť
   virtual void OnOK(); //��ֹ�س��˳������Ը���������麯��
   afx_msg void OnBnClickedBtnCreateOk(); //������������ȷ����ť����
   virtual BOOL OnInitDialog(); //��ʼ��������������������ڲ��ؼ��Ļص������������ڲ��ؼ������
   afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized); //���������������������ʱ���ش���
   afx_msg BOOL OnEraseBkgnd(CDC* pDC); //���ݻ���״̬��ʾ��ͬ���ֵ�
   afx_msg void OnShowWindow(BOOL bShow, UINT nStatus); //Ŀǰû��
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
   afx_msg void OnBnClickedBtnEditFinish(); //�༭���
   afx_msg void OnBnClickedBtnDelete(); //ɾ��
   afx_msg void OnBnClickedBtnDeleteConfirm(); //ȷ��ɾ��
   virtual BOOL PreTranslateMessage(MSG* pMsg); //�������ڹ����¼������ڲ�listbox����listbox���¹���
};
