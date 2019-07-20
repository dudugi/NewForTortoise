#pragma once
/*************************************************
// <文件>: ScreenShotBar.h
// <说明>: 截屏编辑工具条窗口
// <作者>: duchen
// <日期>: 2019/02/22
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 
#include "Resource.h"
#include <functional>
#include "afxwin.h"
#include <vector>


// CScreenShotBar 对话框

class CScreenShotBar : public CDialogEx
{
public:
   CScreenShotBar(CWnd* pParent = NULL);
   ~CScreenShotBar();
   BOOL CreateBarIndirect(CWnd* pParent); //创建窗口（不依赖资源文件）
   std::function<void(void)> m_funFinish; //完成
   std::function<void(void)> m_funAbort; //退出
   std::function<void(void)> m_funDrawRect; //画矩形
   std::function<void(void)> m_funDrawEllipse; //画椭圆
   std::function<void(void)> m_funDrawText; //画文字
   std::function<void(void)> m_funDrawArrow; //画箭头
   std::function<void(void)> m_funWithdraw; //撤销
private:
	DECLARE_DYNAMIC(CScreenShotBar)


// 对话框数据
private:
	DECLARE_MESSAGE_MAP()
private:

   CButton m_BtnWithDraw; //撤销按钮
   CButton m_BtnAbort; //终止按钮
   CButton m_BtnFinish; //完成按钮

   CRect m_RectRect; //“矩形”按钮坐标
   CRect m_RectEllipse; //“椭圆”按钮坐标
   CRect m_RectText; //“文字”按钮坐标
   CRect m_RectArrow; //“箭头”按钮坐标

   int m_nCurBottonIndex; //记录选中了那个按钮，在OnPaint里读取

   std::vector<WORD> m_vecTemplate; //界面布局等信息，代替资源文件

   afx_msg void OnBnClickedBtnFinish(); //完成
   afx_msg void OnBnClickedBtnAbort(); //退出
   virtual void OnCancel(); //取消
   virtual BOOL OnInitDialog(); //初始化
   afx_msg void OnPaint(); //画按钮和选中状态
   afx_msg void OnLButtonDown(UINT nFlags, CPoint point); //点击按钮的判断
   afx_msg void OnBnClickedBtnWithdraw(); //撤销按钮按下
   virtual BOOL PreTranslateMessage(MSG* pMsg); //目前用来快捷键ctrl-z（撤销）处理
};
