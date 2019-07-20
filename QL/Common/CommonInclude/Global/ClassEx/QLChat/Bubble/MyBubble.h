#pragma once
/*************************************************
// <�ļ�>: MyBubble.h
// <˵��>: ����״���ڣ�һ��Բ�Ǿ����м�����֣�
// <����>: duchen
// <����>: 2019/02/22
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
#include "afxcmn.h"
#include "afxwin.h"

class CMyBubble: public CWnd
{
public:
   CMyBubble();
   BOOL Create(int nX, int nY, HWND hParent, const CString &sText); //����������
   BOOL Show(); //��ʾ
   BOOL Hide(); //����
   void SetPos(int nX, int nY); //��������
   void SetText(const CString &sText); //������ʾ����
   void SetBrush(int nBrush){m_nBrush = nBrush;} //���û�ˢ��ͨ��GetStockObject(m_nBrush)��þ��
private:
   DECLARE_MESSAGE_MAP()
   void OnPaint(); //�����ֺ�Բ�Ǿ���
   void OnShowWindow(BOOL bShow, UINT nStatus); //Ŀǰû��
   void OnTimer(UINT_PTR nIDEvent); //ʱ�䵽�����ر�����
   CFont m_Font; //��ʾ����
   CString m_sText; //��ʾ����
   int m_nWindowWidth; //���ô��ڿ��
   int m_nBrush; //ͨ��GetStockObject(m_nBrush)��þ��
};