#pragma once
/*************************************************
// <�ļ�>: SizeBox.h
// <˵��>: �ɵ�����С�Ĵ��ڣ����Խ��������ڷ��������棬�Ӷ��������û�ͨ������������С
// <����>: duchen
// <����>: 2019/02/22
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
#include "afxcmn.h"
#include "afxwin.h"
#include <functional>
#include "RectResizeHelper.h"

class CSizeBox: public CWnd
{
public:
   CSizeBox();
   virtual ~CSizeBox();
   virtual BOOL Create(int nX, int nY, int nWidth, int nHeight,
      HWND hParent, const CString &sText); //�������ڣ�sTextû��
   virtual BOOL Show(); //��ʾ����
   BOOL Hide(); //���ش���
   void SetPos(int nX, int nY); //��������
   std::function<void (const CRect &NewRect, BOOL bDontChangeSize)> m_funcOnDragToNewRect; //�����϶��ص����� bDontChangeSize Ϊ TRUE ʱ��ʾƽ��
   std::function<void (CSizeBox *)> m_funcDragOver; //�϶������ص�����
   std::function<void(const CRect &RectInScreen, const CRect &RectInClient, CDC *pTargetDC)> m_funcDrawBackground; //������ɫ�ص���������������ʵ�֡�͸����Ч��
private:
   DECLARE_MESSAGE_MAP()
   void OnPaint(); //û��
   void OnShowWindow(BOOL bShow, UINT nStatus); //û��
   afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message); //�����������ʾ״̬
   afx_msg void OnMouseMove(UINT nFlags, CPoint point);

   void OnLButtonDown(UINT nFlags, CPoint point);
   void OnLButtonUp(UINT nFlags, CPoint point);
   BOOL OnEraseBkgnd(CDC* pDC);
   CRectResizeHelper m_ResizeHelper; //��������϶�״̬�ж��Լ����˸�����߼��ĸ�����
};