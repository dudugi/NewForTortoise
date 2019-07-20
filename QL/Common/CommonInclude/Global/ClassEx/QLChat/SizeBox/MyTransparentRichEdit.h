#pragma once
/*************************************************
// <文件>: MyTransparentRichEdit.h
// <说明>: 透明富文本框
// <作者>: duchen
// <日期>: 2019/02/22
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 
#include <functional>

class CMyTransparentRichEdit:public CRichEditCtrl
{
public:
   CMyTransparentRichEdit(){}
   ~CMyTransparentRichEdit();
   std::function<void(const CRect &RectInScreen, const CRect &RectInClient, CDC *pTargetDC)> m_funcDrawBackground; //画背景图案的回调函数
private:
   DECLARE_MESSAGE_MAP()
private:
   afx_msg BOOL OnEraseBkgnd(CDC* pDC); //画背景图案
};