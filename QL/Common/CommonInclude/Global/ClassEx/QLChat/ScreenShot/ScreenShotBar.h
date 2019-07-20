#pragma once
/*************************************************
// <�ļ�>: ScreenShotBar.h
// <˵��>: �����༭����������
// <����>: duchen
// <����>: 2019/02/22
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
#include "Resource.h"
#include <functional>
#include "afxwin.h"
#include <vector>


// CScreenShotBar �Ի���

class CScreenShotBar : public CDialogEx
{
public:
   CScreenShotBar(CWnd* pParent = NULL);
   ~CScreenShotBar();
   BOOL CreateBarIndirect(CWnd* pParent); //�������ڣ���������Դ�ļ���
   std::function<void(void)> m_funFinish; //���
   std::function<void(void)> m_funAbort; //�˳�
   std::function<void(void)> m_funDrawRect; //������
   std::function<void(void)> m_funDrawEllipse; //����Բ
   std::function<void(void)> m_funDrawText; //������
   std::function<void(void)> m_funDrawArrow; //����ͷ
   std::function<void(void)> m_funWithdraw; //����
private:
	DECLARE_DYNAMIC(CScreenShotBar)


// �Ի�������
private:
	DECLARE_MESSAGE_MAP()
private:

   CButton m_BtnWithDraw; //������ť
   CButton m_BtnAbort; //��ֹ��ť
   CButton m_BtnFinish; //��ɰ�ť

   CRect m_RectRect; //�����Ρ���ť����
   CRect m_RectEllipse; //����Բ����ť����
   CRect m_RectText; //�����֡���ť����
   CRect m_RectArrow; //����ͷ����ť����

   int m_nCurBottonIndex; //��¼ѡ�����Ǹ���ť����OnPaint���ȡ

   std::vector<WORD> m_vecTemplate; //���沼�ֵ���Ϣ��������Դ�ļ�

   afx_msg void OnBnClickedBtnFinish(); //���
   afx_msg void OnBnClickedBtnAbort(); //�˳�
   virtual void OnCancel(); //ȡ��
   virtual BOOL OnInitDialog(); //��ʼ��
   afx_msg void OnPaint(); //����ť��ѡ��״̬
   afx_msg void OnLButtonDown(UINT nFlags, CPoint point); //�����ť���ж�
   afx_msg void OnBnClickedBtnWithdraw(); //������ť����
   virtual BOOL PreTranslateMessage(MSG* pMsg); //Ŀǰ������ݼ�ctrl-z������������
};
