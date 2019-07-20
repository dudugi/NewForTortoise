#pragma once
/*************************************************
// <�ļ�>: SizeBoxEdit.h
// <˵��>: ͸���ҿɵ�����С���ı��༭��
// <����>: duchen
// <����>: 2019/02/22
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
#include "SizeBox.h"
#include "MyTransparentRichEdit.h"

class CSizeBoxEdit: public CSizeBox
{
public:
   CSizeBoxEdit();
   virtual BOOL Create(int nX, int nY, int nWidth, int nHeight,
      HWND hParent, const CString &sText) override;
   virtual BOOL Show() override; //��ʾ���� ��ʹ�ñ༭���ý���
   BOOL GetCurText(CString *psText, CRect *pRect); //��ȡ��ǰ�ܿ���������
   BOOL SetEditFontHeight(int nHeight, int nFontSize = 0); //���ñ༭���ָ߶� nHeight�Ǵ��������õĸ߶ȣ�nFontSize����ʱ���������Ϣ��ͨ��GetEditFontSize��ȡ
   int GetEditFontSize(){return m_nFontSize;} //��ȡSetEditFontHeightʱ��ĵڶ�������nFontSize
   BOOL SetEditColor(COLORREF color); //���ñ༭��������ɫ
   void SetEditDrawBackgroundFunc(std::function<void(const CRect &RectInScreen, const CRect &RectInClient, CDC *pTargetDC)> funcBackGround); //���û�����ͼ�Ļص�����
   void SetBottomY(int nBottomY){m_nBottomY = nBottomY;} //�������·�y���꣬�������������ʱ����ֹ���ݳ�����Ļ
   BOOL SetEditText(const CString &sText); //��������
   BOOL ReplaceSelEditText(const CString &sText); //�滻ѡ�е�����ΪsText
private:
   DECLARE_MESSAGE_MAP()
private:
   CMyTransparentRichEdit m_RichTransparent; //͸���ı��༭��
   int m_nFontHeight;   //����߶�
   int m_nFontSize;     //��ʱ�������߶���Ϣ
   int m_nBottomY;      //����������·�y���꣬�������������ʱ����ֹ���ݳ�����Ļ
   afx_msg void OnSize(UINT nType, int cx, int cy); //ͬʱ�ƶ��ڲ���͸�����ı��༭��
   void OnMove(int x, int y);    //û��
   void OnEnChangeRichedit21();  //���ֱ仯������������࣬�򴰿ڸ߶�Ҳ���
   afx_msg BOOL OnEraseBkgnd(CDC* pDC); //û��
};