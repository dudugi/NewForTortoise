#pragma once
/*************************************************
// <�ļ�>: ListBoxHover.h
// <˵��>: �����������ͣ��item��ʱ��ʾ��������ɫ��Listbox
// <����>: duchen
// <����>: 2019/02/22
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
#include <afxwin.h>
#include <map>
#include <afxdd_.h>
#include <functional>

class CListBoxHover:public CListBox
{

public:
   CListBoxHover();
   ~CListBoxHover();
   std::function<void (int nIndex)> m_funcEditItem; //���ĳ��item�Ҳ�ͼ��ʱ�Ļص�����
protected:
   virtual void DrawItem(LPDRAWITEMSTRUCT lpDIS) override; //�Ի�item
   virtual void MeasureItem(LPMEASUREITEMSTRUCT) override;
   virtual BOOL SetHoverIndex(int nIndex, BOOL bPenHeight, const CRect &PenRect) ; //ָ���������֮ǰ��������ָ�
   virtual BOOL ClearHoverIndex(); //ȡ�����и���
   enum
   {
      enClearHoverIndex = -2
   };
   int  m_nHoverIndex; //��ǰ��������ΪenClearHoverIndex���ʾ�޸���
   DECLARE_MESSAGE_MAP()
private:
   CRect GetPenRectByItemIndex(int nIndex); //ĳ��item�Ҳ�ͼ������귶Χ

   afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam); //����뿪listbox����Ҫ�������
   afx_msg void OnMouseMove(UINT nFlags, CPoint point);        //�������Ƹ�����ȡ������������뿪ǰ����ʱ���
   void OnLButtonDown(UINT nFlags, CPoint point);              //�����ĳ��item�Ҳ�ͼ��ʱ�Ĵ���

   bool m_bIsPressed;      //Ŀǰû��
   BOOL m_bIsMouseTrack;   // ���׷��
   BOOL m_bPenHeight;      //ĳ��item�Ҳ�ͼ��(һ֧��)�Ƿ������highlight)
   HICON m_hIconHighlight; //����ͼ��icon���
   HICON m_hIconNormal;    //��ͨͼ��icon���
};