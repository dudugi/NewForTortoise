#pragma once
/*************************************************
// <文件>: ScreenShotDialog.h
// <说明>: 截屏窗口，外部用ScreenShot接口调用截屏功能
// <作者>: duchen
// <日期>: 2019/02/22
// Copyright (C), 2016-2020, 琪利软件. Co., Ltd.
*************************************************/ 
#include "ScreenShotBar.h"
#include "ScreenShotDrawOption.h"
#include "..\SizeBox\SizeBoxEdit.h"
#include <list>


// CScreenShotDialog 对话框
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
   // Parameter: BOOL bHideWindow 是否隐藏当前窗口
   // Parameter: CWnd * pMainWnd 原界面主窗口
   // Parameter: const CString & sOutputPath 截图后生成的文件的路径
   // Parameter: IScreenShotSetting * pScreenShotSetting 截图设置，用来记录用户操作习惯，没有可以传空
   //************************************
   static BOOL ScreenShot(BOOL bHideWindow, CWnd *pMainWnd, const CString &sOutputPath, IScreenShotSetting *pScreenShotSetting);
	CScreenShotDialog(IScreenShotSetting *pScreenShotSetting, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CScreenShotDialog();

// 对话框数据
   void AttachHBitmap(HBITMAP hBitmap){m_hBitmap = hBitmap;} //传入从屏幕复制的位图的句柄
   BOOL SetJPGOutputPath(const CString &sPath); //设置输出文件的路径
private:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
   virtual BOOL OnInitDialog(); //初始化，设置窗口大小为屏幕大小，设置工具条窗口和工具条选项窗口的回调函数
   IScreenShotSetting *m_pScreenShotSetting; //保存用户操作习惯的接口
   CRect m_ScreenRect; //屏幕范围
   CRect m_SelectedRect; //选择的截图矩形范围
   CRect m_BarRect; //工具条窗口矩形范围
   CRect m_DrawOptionRect; //工具条选项窗口矩形范围
   HBITMAP m_hBitmap;  //传入的从屏幕复制的位图的句柄
   CDC m_memDC; //整个屏幕画面（编辑前）的内存dc
   CDC m_GrayDC; //画未选中区域用（灰色区域）
   CPoint m_oldMouseMovePoint; //选择矩形范围前，上回mouse move时的鼠标坐标 用来将画的十字线恢复成原底图颜色用
   CPoint m_MouseDownPoint; //选择矩形范围前，mouse down时的坐标，用来获取选中的矩形范围的一个点
   CPoint m_oldRectMouseMovePoint; //选择矩形范围第二个点时的mouse move坐标
   BOOL m_bMemDCPrepared; //m_memDC是否被创建的标志位

   CPoint m_DrawFirstPoint; //画矩形椭圆等的第一个点
   CPoint m_DrawSecondPoint; //画矩形椭圆等的第二个点
   CPoint m_oldDrawSecondPoint; //画矩形椭圆等的第二个点（old), 用来恢复上次移动鼠标画的老的矩形范围内的东西

   HCURSOR m_hCursorDraw; //绘画状态的鼠标光标句柄

   enum EditStatus //画面状态
   {
      START_UP, //初始状态 （未选中截图矩形范围）
      RECT_FIRST_POINT_SELECTED, //选中了截图矩形范围的第一个点
      RECT_SELECTED, //选中了截图矩形范围
      DRAW_RECT, //画矩形图案
      DRAW_ELLIPSE, //画椭圆图案
      DRAW_TEXT, //画文字
      DRAW_ARROW, //画箭头图案
   };

   struct CDrawObject //图案对象
   {
      enum DrawType //图案类型
      {
         DRAW_TYPE_NULL, //无
         RECT, //矩形
         ELLIPSE, //椭圆
         ARROW, //箭头
         TEXT, //文字
      };
      CDrawObject(): m_eDrawType(DRAW_TYPE_NULL), m_nPenWidth(1), m_Color(RGB(0, 0, 0)), m_nFontSize(10){}
      DrawType m_eDrawType; //图案类型
      CRect m_Rect; //外界矩形范围
      int m_nPenWidth; //笔粗
      COLORREF m_Color; //颜色

      //文字专用
      CString m_sText; //文字
      int m_nFontSize; //字体大小

      //箭头专用
      CPoint m_StartPoint; //起始点
      CPoint m_EndPoint; //结束点
   };
   std::list<CDrawObject> m_lstDrawObjects; //所有图案对象
   //BOOL m_bLButtonDown;
   EditStatus m_eEditStatus; //当前画面状态
   CString m_sOutputPath; //文件输出路径
   CScreenShotBar m_ScreenShotBar; //工具条窗口
   CScreenShotDrawOption m_ScreenShotDrawOption; //工具条选项窗口

   std::vector<std::shared_ptr<CSizeBoxEdit>> m_vecSizeBoxEdit; //文字控件容器，用来编辑文字，每一块文字对应一个容器中的元素
   int m_nCurEditIndex; //当前激活的文字控件在m_vecSizeBoxEdit里的索引
   CRect m_DarkRect; //选择文字编辑框范围时的矩形范围
   static const CPoint NULL_POINT; //作为空的点坐标，可用来初始化或重置CPoint
   int m_nPenWidth; //当前笔粗
   COLORREF m_Color; //当前颜色
   CPoint m_DrawTextFirstPoint; //画文字的第一个点
   CPoint m_DrawTextMovePoint; //画文字移动的第二个点
   int m_nFontSize; //画文字的字体大小
   std::vector<WORD> m_vecTemplate; //使界面脱离资源文件
   BOOL CorrectPointInRect(const CRect &Rect, CPoint *pPoint); //使得pPoint限制在Rect范围内
   void DrawCrossLine(CDC *pDC, const CPoint &pt); //画十字线
   void DrawSelectedRect(const CRect &Rect); //该函数已无用
   BOOL InvalidateDiffRect(const CRect &RectOld, const CRect &RectNew); //目前是刷新两个矩形实现的
   CRect GetTrueRect(const CRect &Rect); //Rect的坐标由两个点组成，生成并返回一个正确的矩形，并且右下角+1
   BOOL SaveFinalBmp(const CRect &Rect); //将最终结果生成bmp文件
   BOOL DrawDrawObjects(CDC *pDC, int nX = 0, int nY = 0); //把所有小图案画到指定dc上。nX 和 nY 表示往左上角偏移的量，为了能在透明编辑框内部画而加的参数。
   void ShowDrawOptionDialog(BOOL bShowFont); //显示工具条选项窗口，含有找到合适坐标的相关逻辑
   BOOL PutCurEditOnBitmap(); //当前编辑框文字上图，并且隐藏此编辑框
   void DrawArrow(const CPoint &BeginPoint, const CPoint &EndPoint, CPoint *pNewPoint1, CPoint *pNewPoint2); //画箭头，返回两个小翅膀的点，用来局部刷新画面
   void DrawMultLineText(CDC *pDC, CRect rect, int nRowDis, UINT nFromat, CString strText); //画多行文字到指定矩形范围
   void Withdraw(); //撤销
   afx_msg void OnPaint(); //画灰色区域，画当前画的小图案，画之前画的所有小图案等
   afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message); //根据当前画面状态设置鼠标光标
   afx_msg void OnMouseMove(UINT nFlags, CPoint point);
   afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
   afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
   afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
   virtual BOOL PreTranslateMessage(MSG* pMsg); //目前用来处理ctrl-z和ESC键快捷键
   afx_msg BOOL OnEraseBkgnd(CDC* pDC); //画背景用，这里主要是画编辑前的整个屏幕的截图
};

//记录截图功能用户上次操作选项用的接口
class IScreenShotSetting
{
public:
   enum ScreenShotToolType //工具类型
   {
      SCREEN_SHOT_TOOL_RECT = 0, //矩形
      SCREEN_SHOT_TOOL_ARROW,    //箭头
      SCREEN_SHOT_TOOL_TEXT,     //文字
      SCREEN_SHOT_TOOL_ELLIPSE,  //椭圆
      SCREENT_SHOT_TOOL_COUNT    //总工具个数
   };

   virtual BOOL SetScreenShotSetting(ScreenShotToolType eTool, int nSizeIndex, int nColorIndex) = 0; //设置工具类型，笔粗或字体大小，颜色索引号
   virtual BOOL SetScreenShotSettingSize(ScreenShotToolType eTool, int nSizeIndex) = 0; //设置工具类型，笔粗或字体大小
   virtual BOOL SetScreenShotSettingColor(ScreenShotToolType eTool, int nColorIndex) = 0; //设置工具类型，颜色索引号
   virtual BOOL GetScreenShotSetting(ScreenShotToolType eTool, int *pnSizeIndex, int *pnColorIndex) = 0; //读取上次操作选项
   virtual ~IScreenShotSetting() = 0{}
};