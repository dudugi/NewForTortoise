#pragma once
/*************************************************
// <文件>: RectResizeHelper.h
// <说明>: 矩形范围通过鼠标调整的辅助类（通过8个点调整）
// <作者>: duchen
// <日期>: 2019/02/22
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
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
   // Parameter: int nFrameWidth 矩形框粗细
   // Parameter: int nFrameWidthMouse 鼠标点击命中判断时用的矩形粗细
   // Parameter: int nMinWindowHeight 允许最小窗口高度
   // Parameter: int nMinWindowWidth 允许最小窗口宽度
   //************************************
   CRectResizeHelper(int nFrameWidth = 5, int nFrameWidthMouse = 8, int nMinWindowHeight = 20, int nMinWindowWidth = 40);
   virtual ~CRectResizeHelper();
   enum MouseDragType //鼠标拖动类型
   {
      MOUSE_POS_OUTER, //鼠标点在矩形外面（无法拖动）
      MOUSE_POS_OTHER, //点在其他地方
      MOUSE_POS_LEFT_TOP, //左上角
      MOUSE_POS_LEFT_MIDDLE, //左侧中部
      MOUSE_POS_LEFT_BOTTOM, //左下角
      MOUSE_POS_MIDDLE_TOP, //中间上方
      MOUSE_POS_MIDDLE_BOTTOM, //中间下方
      MOUSE_POS_RIGHT_TOP, //右上角
      MOUSE_POS_RIGHT_MIDDLE, //右侧中间
      MOUSE_POS_RIGHT_BOTTOM, //右下角
      MOUSE_POS_LINE, //点在矩形的外框线上
   };

   MouseDragType SetMouseDownPos(const CPoint &MousePt, const CRect &WindowRect); //传入鼠标坐标和矩形范围，返回拖动类型
   LPTSTR GetCursorResourceID(const CPoint &MousePt, const CRect &WindowRect); //传入鼠标坐标和矩形范围，返回鼠标显示用的资源信息
   void NewPointMove(const CRect &OrgRect, const CPoint &NewPoint, CRect *pNewRect, BOOL *pbDontChangeSize); //鼠标移动，获得新矩形，先要调用SetMouseDownPos
   bool IsDownInRect() {return m_eMouseDownPos != MOUSE_POS_OUTER;} //判断是否点在矩形内部，先要调用SetMouseDownPos
   BOOL PaintResizeRect(CDC *pDC, const CRect &Rect); //画带有八个点和断断续续线的矩形
private:
   MouseDragType m_eMouseDownPos; //鼠标拖动类型
   CPoint m_MouseDownPointInRect; //鼠标down的坐标
   int m_nFrameWidth; //矩形外框宽度
   int m_nFrameWidthHalf; //矩形外框宽度的一半
   int m_nFrameWidthMouse; //矩形鼠标点击判定宽度
   int m_nFrameWidthMouseHalf; //矩形鼠标点击判定宽度的一半
   int m_nMinWindowHeight; //最小窗口高度
   int m_nMinWindowWidth; //最小窗口宽度
};