#pragma once
/*************************************************
// <�ļ�>: ScreenShotDialog.h
// <˵��>: �������ڣ��ⲿ��ScreenShot�ӿڵ��ý�������
// <����>: duchen
// <����>: 2019/02/22
// Copyright (C), 2016-2020, �������. Co., Ltd.
*************************************************/ 
#include "ScreenShotBar.h"
#include "ScreenShotDrawOption.h"
#include "..\SizeBox\SizeBoxEdit.h"
#include <list>


// CScreenShotDialog �Ի���
class IScreenShotSetting;
class CScreenShotDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CScreenShotDialog)

public:
   //************************************
   // Method:    ScreenShot
   // FullName:  CScreenShotDialog::ScreenShot
   // Access:    public static 
   // Returns:   BOOL
   // Qualifier:
   // Parameter: BOOL bHideWindow �Ƿ����ص�ǰ����
   // Parameter: CWnd * pMainWnd ԭ����������
   // Parameter: const CString & sOutputPath ��ͼ�����ɵ��ļ���·��
   // Parameter: IScreenShotSetting * pScreenShotSetting ��ͼ���ã�������¼�û�����ϰ�ߣ�û�п��Դ���
   //************************************
   static BOOL ScreenShot(BOOL bHideWindow, CWnd *pMainWnd, const CString &sOutputPath, IScreenShotSetting *pScreenShotSetting);
	CScreenShotDialog(IScreenShotSetting *pScreenShotSetting, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CScreenShotDialog();

// �Ի�������
   void AttachHBitmap(HBITMAP hBitmap){m_hBitmap = hBitmap;} //�������Ļ���Ƶ�λͼ�ľ��
   BOOL SetJPGOutputPath(const CString &sPath); //��������ļ���·��
private:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
   virtual BOOL OnInitDialog(); //��ʼ�������ô��ڴ�СΪ��Ļ��С�����ù��������ں͹�����ѡ��ڵĻص�����
   IScreenShotSetting *m_pScreenShotSetting; //�����û�����ϰ�ߵĽӿ�
   CRect m_ScreenRect; //��Ļ��Χ
   CRect m_SelectedRect; //ѡ��Ľ�ͼ���η�Χ
   CRect m_BarRect; //���������ھ��η�Χ
   CRect m_DrawOptionRect; //������ѡ��ھ��η�Χ
   HBITMAP m_hBitmap;  //����Ĵ���Ļ���Ƶ�λͼ�ľ��
   CDC m_memDC; //������Ļ���棨�༭ǰ�����ڴ�dc
   CDC m_GrayDC; //��δѡ�������ã���ɫ����
   CPoint m_oldMouseMovePoint; //ѡ����η�Χǰ���ϻ�mouse moveʱ��������� ����������ʮ���߻ָ���ԭ��ͼ��ɫ��
   CPoint m_MouseDownPoint; //ѡ����η�Χǰ��mouse downʱ�����꣬������ȡѡ�еľ��η�Χ��һ����
   CPoint m_oldRectMouseMovePoint; //ѡ����η�Χ�ڶ�����ʱ��mouse move����
   BOOL m_bMemDCPrepared; //m_memDC�Ƿ񱻴����ı�־λ

   CPoint m_DrawFirstPoint; //��������Բ�ȵĵ�һ����
   CPoint m_DrawSecondPoint; //��������Բ�ȵĵڶ�����
   CPoint m_oldDrawSecondPoint; //��������Բ�ȵĵڶ����㣨old), �����ָ��ϴ��ƶ���껭���ϵľ��η�Χ�ڵĶ���

   HCURSOR m_hCursorDraw; //�滭״̬���������

   enum EditStatus //����״̬
   {
      START_UP, //��ʼ״̬ ��δѡ�н�ͼ���η�Χ��
      RECT_FIRST_POINT_SELECTED, //ѡ���˽�ͼ���η�Χ�ĵ�һ����
      RECT_SELECTED, //ѡ���˽�ͼ���η�Χ
      DRAW_RECT, //������ͼ��
      DRAW_ELLIPSE, //����Բͼ��
      DRAW_TEXT, //������
      DRAW_ARROW, //����ͷͼ��
   };

   struct CDrawObject //ͼ������
   {
      enum DrawType //ͼ������
      {
         DRAW_TYPE_NULL, //��
         RECT, //����
         ELLIPSE, //��Բ
         ARROW, //��ͷ
         TEXT, //����
      };
      CDrawObject(): m_eDrawType(DRAW_TYPE_NULL), m_nPenWidth(1), m_Color(RGB(0, 0, 0)), m_nFontSize(10){}
      DrawType m_eDrawType; //ͼ������
      CRect m_Rect; //�����η�Χ
      int m_nPenWidth; //�ʴ�
      COLORREF m_Color; //��ɫ

      //����ר��
      CString m_sText; //����
      int m_nFontSize; //�����С

      //��ͷר��
      CPoint m_StartPoint; //��ʼ��
      CPoint m_EndPoint; //������
   };
   std::list<CDrawObject> m_lstDrawObjects; //����ͼ������
   //BOOL m_bLButtonDown;
   EditStatus m_eEditStatus; //��ǰ����״̬
   CString m_sOutputPath; //�ļ����·��
   CScreenShotBar m_ScreenShotBar; //����������
   CScreenShotDrawOption m_ScreenShotDrawOption; //������ѡ���

   std::vector<std::shared_ptr<CSizeBoxEdit>> m_vecSizeBoxEdit; //���ֿؼ������������༭���֣�ÿһ�����ֶ�Ӧһ�������е�Ԫ��
   int m_nCurEditIndex; //��ǰ��������ֿؼ���m_vecSizeBoxEdit�������
   CRect m_DarkRect; //ѡ�����ֱ༭��Χʱ�ľ��η�Χ
   static const CPoint NULL_POINT; //��Ϊ�յĵ����꣬��������ʼ��������CPoint
   int m_nPenWidth; //��ǰ�ʴ�
   COLORREF m_Color; //��ǰ��ɫ
   CPoint m_DrawTextFirstPoint; //�����ֵĵ�һ����
   CPoint m_DrawTextMovePoint; //�������ƶ��ĵڶ�����
   int m_nFontSize; //�����ֵ������С
   std::vector<WORD> m_vecTemplate; //ʹ����������Դ�ļ�
   BOOL CorrectPointInRect(const CRect &Rect, CPoint *pPoint); //ʹ��pPoint������Rect��Χ��
   void DrawCrossLine(CDC *pDC, const CPoint &pt); //��ʮ����
   void DrawSelectedRect(const CRect &Rect); //�ú���������
   BOOL InvalidateDiffRect(const CRect &RectOld, const CRect &RectNew); //Ŀǰ��ˢ����������ʵ�ֵ�
   CRect GetTrueRect(const CRect &Rect); //Rect����������������ɣ����ɲ�����һ����ȷ�ľ��Σ��������½�+1
   BOOL SaveFinalBmp(const CRect &Rect); //�����ս������bmp�ļ�
   BOOL DrawDrawObjects(CDC *pDC, int nX = 0, int nY = 0); //������Сͼ������ָ��dc�ϡ�nX �� nY ��ʾ�����Ͻ�ƫ�Ƶ�����Ϊ������͸���༭���ڲ������ӵĲ�����
   void ShowDrawOptionDialog(BOOL bShowFont); //��ʾ������ѡ��ڣ������ҵ��������������߼�
   BOOL PutCurEditOnBitmap(); //��ǰ�༭��������ͼ���������ش˱༭��
   void DrawArrow(const CPoint &BeginPoint, const CPoint &EndPoint, CPoint *pNewPoint1, CPoint *pNewPoint2); //����ͷ����������С���ĵ㣬�����ֲ�ˢ�»���
   void DrawMultLineText(CDC *pDC, CRect rect, int nRowDis, UINT nFromat, CString strText); //���������ֵ�ָ�����η�Χ
   void Withdraw(); //����
   afx_msg void OnPaint(); //����ɫ���򣬻���ǰ����Сͼ������֮ǰ��������Сͼ����
   afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message); //���ݵ�ǰ����״̬���������
   afx_msg void OnMouseMove(UINT nFlags, CPoint point);
   afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
   afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
   afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
   virtual BOOL PreTranslateMessage(MSG* pMsg); //Ŀǰ��������ctrl-z��ESC����ݼ�
   afx_msg BOOL OnEraseBkgnd(CDC* pDC); //�������ã�������Ҫ�ǻ��༭ǰ��������Ļ�Ľ�ͼ
};

//��¼��ͼ�����û��ϴβ���ѡ���õĽӿ�
class IScreenShotSetting
{
public:
   enum ScreenShotToolType //��������
   {
      SCREEN_SHOT_TOOL_RECT = 0, //����
      SCREEN_SHOT_TOOL_ARROW,    //��ͷ
      SCREEN_SHOT_TOOL_TEXT,     //����
      SCREEN_SHOT_TOOL_ELLIPSE,  //��Բ
      SCREENT_SHOT_TOOL_COUNT    //�ܹ��߸���
   };

   virtual BOOL SetScreenShotSetting(ScreenShotToolType eTool, int nSizeIndex, int nColorIndex) = 0; //���ù������ͣ��ʴֻ������С����ɫ������
   virtual BOOL SetScreenShotSettingSize(ScreenShotToolType eTool, int nSizeIndex) = 0; //���ù������ͣ��ʴֻ������С
   virtual BOOL SetScreenShotSettingColor(ScreenShotToolType eTool, int nColorIndex) = 0; //���ù������ͣ���ɫ������
   virtual BOOL GetScreenShotSetting(ScreenShotToolType eTool, int *pnSizeIndex, int *pnColorIndex) = 0; //��ȡ�ϴβ���ѡ��
   virtual ~IScreenShotSetting() = 0{}
};