#pragma once
/*************************************************
// <�ļ�>: RectResizeHelper.h
// <˵��>: ���η�Χͨ���������ĸ����ࣨͨ��8���������
// <����>: duchen
// <����>: 2019/02/22
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
#include "afxcmn.h"
#include "afxwin.h"
#include <functional>

class CRectResizeHelper
{
public:
   //************************************
   // Method:    CRectResizeHelper
   // FullName:  CRectResizeHelper::CRectResizeHelper
   // Access:    public 
   // Returns:   
   // Qualifier:
   // Parameter: int nFrameWidth ���ο��ϸ
   // Parameter: int nFrameWidthMouse ����������ж�ʱ�õľ��δ�ϸ
   // Parameter: int nMinWindowHeight ������С���ڸ߶�
   // Parameter: int nMinWindowWidth ������С���ڿ��
   //************************************
   CRectResizeHelper(int nFrameWidth = 5, int nFrameWidthMouse = 8, int nMinWindowHeight = 20, int nMinWindowWidth = 40);
   virtual ~CRectResizeHelper();
   enum MouseDragType //����϶�����
   {
      MOUSE_POS_OUTER, //�����ھ������棨�޷��϶���
      MOUSE_POS_OTHER, //���������ط�
      MOUSE_POS_LEFT_TOP, //���Ͻ�
      MOUSE_POS_LEFT_MIDDLE, //����в�
      MOUSE_POS_LEFT_BOTTOM, //���½�
      MOUSE_POS_MIDDLE_TOP, //�м��Ϸ�
      MOUSE_POS_MIDDLE_BOTTOM, //�м��·�
      MOUSE_POS_RIGHT_TOP, //���Ͻ�
      MOUSE_POS_RIGHT_MIDDLE, //�Ҳ��м�
      MOUSE_POS_RIGHT_BOTTOM, //���½�
      MOUSE_POS_LINE, //���ھ��ε��������
   };

   MouseDragType SetMouseDownPos(const CPoint &MousePt, const CRect &WindowRect); //�����������;��η�Χ�������϶�����
   LPTSTR GetCursorResourceID(const CPoint &MousePt, const CRect &WindowRect); //�����������;��η�Χ�����������ʾ�õ���Դ��Ϣ
   void NewPointMove(const CRect &OrgRect, const CPoint &NewPoint, CRect *pNewRect, BOOL *pbDontChangeSize); //����ƶ�������¾��Σ���Ҫ����SetMouseDownPos
   bool IsDownInRect() {return m_eMouseDownPos != MOUSE_POS_OUTER;} //�ж��Ƿ���ھ����ڲ�����Ҫ����SetMouseDownPos
   BOOL PaintResizeRect(CDC *pDC, const CRect &Rect); //�����а˸���Ͷ϶������ߵľ���
private:
   MouseDragType m_eMouseDownPos; //����϶�����
   CPoint m_MouseDownPointInRect; //���down������
   int m_nFrameWidth; //���������
   int m_nFrameWidthHalf; //��������ȵ�һ��
   int m_nFrameWidthMouse; //����������ж����
   int m_nFrameWidthMouseHalf; //����������ж���ȵ�һ��
   int m_nMinWindowHeight; //��С���ڸ߶�
   int m_nMinWindowWidth; //��С���ڿ��
};