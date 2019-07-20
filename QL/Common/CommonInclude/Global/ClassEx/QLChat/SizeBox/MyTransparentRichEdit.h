#pragma once
/*************************************************
// <�ļ�>: MyTransparentRichEdit.h
// <˵��>: ͸�����ı���
// <����>: duchen
// <����>: 2019/02/22
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
#include <functional>

class CMyTransparentRichEdit:public CRichEditCtrl
{
public:
   CMyTransparentRichEdit(){}
   ~CMyTransparentRichEdit();
   std::function<void(const CRect &RectInScreen, const CRect &RectInClient, CDC *pTargetDC)> m_funcDrawBackground; //������ͼ���Ļص�����
private:
   DECLARE_MESSAGE_MAP()
private:
   afx_msg BOOL OnEraseBkgnd(CDC* pDC); //������ͼ��
};