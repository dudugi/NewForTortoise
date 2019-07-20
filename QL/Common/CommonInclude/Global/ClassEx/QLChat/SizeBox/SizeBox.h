#pragma once
/*************************************************
// <文件>: SizeBox.h
// <说明>: 可调整大小的窗口，可以将其它窗口放在它里面，从而可以让用户通过点来调整大小
// <作者>: duchen
// <日期>: 2019/02/22
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
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
      HWND hParent, const CString &sText); //创建窗口，sText没用
   virtual BOOL Show(); //显示窗口
   BOOL Hide(); //隐藏窗口
   void SetPos(int nX, int nY); //设置坐标
   std::function<void (const CRect &NewRect, BOOL bDontChangeSize)> m_funcOnDragToNewRect; //窗口拖动回调函数 bDontChangeSize 为 TRUE 时表示平移
   std::function<void (CSizeBox *)> m_funcDragOver; //拖动结束回调函数
   std::function<void(const CRect &RectInScreen, const CRect &RectInClient, CDC *pTargetDC)> m_funcDrawBackground; //画背景色回调函数，可以用来实现“透明”效果
private:
   DECLARE_MESSAGE_MAP()
   void OnPaint(); //没用
   void OnShowWindow(BOOL bShow, UINT nStatus); //没用
   afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message); //设置鼠标光标显示状态
   afx_msg void OnMouseMove(UINT nFlags, CPoint point);

   void OnLButtonDown(UINT nFlags, CPoint point);
   void OnLButtonUp(UINT nFlags, CPoint point);
   BOOL OnEraseBkgnd(CDC* pDC);
   CRectResizeHelper m_ResizeHelper; //负责鼠标拖动状态判断以及画八个点等逻辑的辅助类
};