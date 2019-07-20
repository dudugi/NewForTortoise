#pragma once
/*************************************************
// <�ļ�>: ScreenShotDrawOption.h
// <˵��>: ����������ѡ���
// <����>: duchen
// <����>: 2019/02/22
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
#include <functional>

class CScreenShotDrawOption : public CWnd
{
	DECLARE_DYNAMIC(CScreenShotDrawOption)

public:
	CScreenShotDrawOption();   // ��׼���캯��
	virtual ~CScreenShotDrawOption();

   BOOL MyCreate(HWND hParent); //�������ڣ�������Դ�ļ�
   void SetShowStatus(BOOL bShowFontSize, int nColorIndex, int nSizeIndex); //������ʾ״̬���Ƿ�����ʾ�����С����ɫ���ʴ�/�����С��

   std::function<void (int nPenWidth, int nSizeIndex)> m_funcChangePenWidth; //�ʴֱ仯�ص�����
   std::function<void (COLORREF NewColor, int nColorIndex)> m_funcChangeColor; //��ɫ�仯�ص�����
   std::function<void (int nSize, int nSizeIndex)> m_funcSizeChange; //�����С�仯�ص�����
protected:
	DECLARE_MESSAGE_MAP()
private:
   int m_nPenWidth; //��ǰ�ʴ�
   COLORREF m_curColor; //��ǰ��ɫ
   CComboBox m_cboFontSize; //��ǰ�����С
   BOOL m_bShowFontSize; //�Ƿ�����ʾ�����С
   afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
   afx_msg void OnPaint();
   afx_msg int OnCreate(LPCREATESTRUCT p);
   afx_msg void OnCbnSelchangeComboFontSize();
   afx_msg BOOL OnEraseBkgnd(CDC* pDC); //����ɫͿ��
   afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
};
