// BazierDrawDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BazierDraw.h"
#include "BazierDrawDlg.h"
#include "afxdialogex.h"
#include <vector>
#include "CArcItem.h"
#include "CArcItemExt.h"
#include "BazierFunc.h"
#include "BazierDrawFast.h"
#include <list>
#include <math.h>
#include <algorithm>

enum
{
   MAX_SECTION_COUNT = 8
};

void BeizerDraw(CDC *pDC, CPoint point[4]);

void CombineSameSection(std::vector<CArcItem> *pvecTempArcItems);

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBazierDrawDlg 对话框




CBazierDrawDlg::CBazierDrawDlg(CWnd* pParent /*=NULL*/)
   : CDialogEx(CBazierDrawDlg::IDD, pParent)
{
   m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBazierDrawDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialogEx::DoDataExchange(pDX);
   DDX_Control(pDX, IDC_EDIT_RESULT, m_editResult);
   DDX_Control(pDX, IDC_CHK_REDUCE_FIRST, m_chkReduceFirst);
   DDX_Control(pDX, IDC_ET_FZ_COUNT, m_editFZCount);
   DDX_Control(pDX, IDC_ET_TOTAL_NEEDLE, m_editTotalNeedle);
   DDX_Control(pDX, IDC_ET_TOTAL_REVOLUTION, m_editTotalRevolution);
   DDX_Control(pDX, IDC_ET_TOLERANCE, m_editTolerance);
   DDX_Control(pDX, IDC_ET_PIXEL_PER_SQUARE, m_editPixelPerSquare);
   DDX_Control(pDX, IDC_ET_PIXEL_PER_SQUARE_Y, m_editPixelPerY);
   DDX_Control(pDX, IDC_CHK_SEG_LIMIT, m_chkSegLimit);
   DDX_Control(pDX, IDC_ET_SEG_LIMIT, m_editSegLimit);
   DDX_Control(pDX, IDC_ET_FIX_X, m_editFixX);
   DDX_Control(pDX, IDC_ET_FIX_Y, m_editFixY);
   DDX_Control(pDX, IDC_CHK_FIX_POS, m_chkFixPos);
}

BEGIN_MESSAGE_MAP(CBazierDrawDlg, CDialogEx)
   ON_WM_PAINT()
   ON_WM_QUERYDRAGICON()
   ON_WM_MOUSEMOVE()
   ON_WM_LBUTTONUP()
   ON_BN_CLICKED(IDC_CHK_REDUCE_FIRST, &CBazierDrawDlg::OnBnClickedChkReduceFirst)
   ON_BN_CLICKED(IDC_CHK_SEG_LIMIT, &CBazierDrawDlg::OnBnClickedChkSegLimit)
   ON_BN_CLICKED(IDC_CHK_FIX_POS, &CBazierDrawDlg::OnBnClickedChkFixPos)
END_MESSAGE_MAP()


// CBazierDrawDlg 消息处理程序

BOOL CBazierDrawDlg::OnInitDialog()
{
   CDialogEx::OnInitDialog();

   // 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
   //  执行此操作
   SetIcon(m_hIcon, TRUE);			// 设置大图标
   SetIcon(m_hIcon, FALSE);		// 设置小图标

   // TODO: 在此添加额外的初始化代码
   ShowWindow(SW_MAXIMIZE);

   m_editTotalNeedle.SetWindowText(_T("80"));
   m_editTotalRevolution.SetWindowText(_T("90"));
   m_editFZCount.SetWindowText(_T("2"));
   m_editTolerance.SetWindowText(_T("2"));

   m_editPixelPerSquare.SetWindowText(_T("5"));

   m_editPixelPerY.SetWindowText(_T("5"));

   m_chkSegLimit.SetCheck(FALSE);

   m_editSegLimit.SetWindowText(_T("8"));

   m_editFixX.SetWindowText(_T("300"));
   m_editFixY.SetWindowText(_T("300"));

   m_ptMiddlePoint = CPoint(200, 200);
   Invalidate(TRUE);

   return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

typedef CList<POINT,POINT&>			PTLIST;
#define NEARINTEGER(x) double(int(x+0.5)) 

void BezierLine(CPoint* point,std::list<CPoint>* pPtList)
{
   double dx1=point[0].x;
   double dx2=point[1].x;
   double dx3=point[2].x;
   double dx4=point[3].x;
   double dy1=point[0].y;
   double dy2=point[1].y;
   double dy3=point[2].y;
   double dy4=point[3].y;
   int nCount=max(abs(point[0].x-point[3].x),abs(point[0].y-point[3].y));
   CPoint oldPoint=CPoint(0,0);
   for (int i=0;i<nCount;i++)
   {
      double t=double(i)/nCount;
      double dx=dx1*(1-t)*(1-t)*(1-t)+3*dx2*t*(1-t)*(1-t)+3*dx3*(1-t)*t*t+dx4*t*t*t;
      double dy=dy1*(1-t)*(1-t)*(1-t)+3*dy2*t*(1-t)*(1-t)+3*dy3*(1-t)*t*t+dy4*t*t*t;
      int nx=NEARINTEGER(dx);
      int ny=NEARINTEGER(dy);

      CPoint pt=CPoint(nx,ny);
      if (pt!=oldPoint)
         pPtList->push_back(pt);
      oldPoint=pt;
   }
   pPtList->push_front(point[0]);
   pPtList->push_back(point[3]);
}
void GetLinePoints(int x1, int y1, int x2, int y2, std::list<CPoint> *pPtList)
{
   int dx = x2 - x1;
   int dy = y2 - y1;
   int ux = ((dx > 0) << 1) - 1;//x的增量方向，取或-1
   int uy = ((dy > 0) << 1) - 1;//y的增量方向，取或-1
   int x = x1, y = y1, eps;//eps为累加误差

   eps = 0;dx = abs(dx); dy = abs(dy); 
   if (dx > dy) 
   {
      for (x = x1; x != x2/*+ux*/; x += ux)
      {
         // SetPixel(img, x, y);
         pPtList->push_back(CPoint(x, y));
         eps += dy;
         if ((eps << 1) >= dx)
         {
            y += uy; eps -= dx;
         }
      }
   }
   else
   {
      for (y = y1; y != y2/*+uy*/; y += uy)
      {
         //drawPixel(x, y,color);
         pPtList->push_back(CPoint(x, y));
         eps += dx;
         if ((eps << 1) >= dy)
         {
            x += ux; eps -= dy;
         }
      }
   }
}

void BezierLineAllPoint(CPoint* point,std::list<CPoint>* pPtList)
{
   double dx1=point[0].x;
   double dx2=point[1].x;
   double dx3=point[2].x;
   double dx4=point[3].x;
   double dy1=point[0].y;
   double dy2=point[1].y;
   double dy3=point[2].y;
   double dy4=point[3].y;
   int nCount=max(abs(point[0].x-point[3].x),abs(point[0].y-point[3].y));
   CPoint oldPoint=CPoint(0,0);
   for (int i=0;i<nCount;i++)
   {
      double t=double(i)/nCount;
      double dx=dx1*(1-t)*(1-t)*(1-t)+3*dx2*t*(1-t)*(1-t)+3*dx3*(1-t)*t*t+dx4*t*t*t;
      double dy=dy1*(1-t)*(1-t)*(1-t)+3*dy2*t*(1-t)*(1-t)+3*dy3*(1-t)*t*t+dy4*t*t*t;
      int nx=NEARINTEGER(dx);
      int ny=NEARINTEGER(dy);

      CPoint pt=CPoint(nx,ny);
      if (pt!=oldPoint)
      {
         if (oldPoint != CPoint(0,0))
         {
            std::list<CPoint> lstPoints;
            GetLinePoints(oldPoint.x, oldPoint.y, pt.x, pt.y, &lstPoints);

            lstPoints.pop_front();
            lstPoints.push_back(pt);
            pPtList->splice(pPtList->end(), lstPoints);
         }
         else
         {
            pPtList->push_back(pt);
         }
         //pPtList->push_back(pt);
         oldPoint=pt;
      }
   }
   pPtList->push_front(point[0]);
   pPtList->push_back(point[3]);
}


//合并同样的段
void CombineSameSection(std::vector<CArcItem> *pvecTempArcItems)
{
   if (!pvecTempArcItems)
   {
      ASSERT(0);
      return;
   }
   auto &vecTempArcItems = *pvecTempArcItems;
   std::vector<CArcItem> vecTemp;
   CArcItem *pLast = nullptr;
   for (auto Iter = vecTempArcItems.begin(); Iter != vecTempArcItems.end(); ++Iter)
   {
      if (vecTemp.empty())
      {
         vecTemp.push_back(*Iter);
         continue;
      }
      CArcItem &Item = vecTemp.back();
      if (Iter->m_nPart1 == Item.m_nPart1 
         && Iter->m_nPart2 == Item.m_nPart2)
      {
         Item.m_nPart3 += Iter->m_nPart3;
      }
      else
      {
         vecTemp.push_back(*Iter);
      }
   }
   vecTempArcItems.swap(vecTemp);
}

void CombineSameSection(std::vector<CArcItemExt> *pvecTempArcItemsExt, std::vector<CArcItem> *pvecTempArcItems)
{
   if (!pvecTempArcItems || !pvecTempArcItems)
   {
      ASSERT(0);
      return;
   }
   auto &vecTempArcItems = *pvecTempArcItemsExt;
   std::vector<CArcItem> vecTemp;
   CArcItem *pLast = nullptr;
   for (auto Iter = vecTempArcItems.begin(); Iter != vecTempArcItems.end(); ++Iter)
   {
      if (vecTemp.empty())
      {
         vecTemp.push_back(*Iter);
         continue;
      }
      CArcItem &Item = vecTemp.back();
      if (Iter->m_nPart1 == Item.m_nPart1 
         && Iter->m_nPart2 == Item.m_nPart2)
      {
         ++Item.m_nPart3;
      }
      else
      {
         vecTemp.push_back(*Iter);
      }
   }
   //vecTempArcItems.swap(vecTemp);
   pvecTempArcItems->swap(vecTemp);
}

void PrintAll(const std::vector<CArcItemExt> &vecTempArcItemsExt)
{
   for (auto Iter = vecTempArcItemsExt.begin(); Iter != vecTempArcItemsExt.end(); ++Iter)
   {
      TRACE(_T("row %d needle %d time %d force %d pointx %d pointy %d diff %d\n"), 
         Iter->m_nPart1, Iter->m_nPart2, Iter->m_nPart3,
         Iter->bByForce, Iter->CurrentPoint.x, Iter->CurrentPoint.y, Iter->nDiff);
   }
}

//直角三角形，转方向,必须都是1次
BOOL ChangeAngles(std::vector<CArcItem> *pvecArcItems)
{
   if (!pvecArcItems)
      return FALSE;

   if (pvecArcItems->empty())
      return FALSE;

   if (pvecArcItems->front().m_nPart1 != 0)
      return FALSE;

   for (auto Iter = pvecArcItems->begin(); Iter != pvecArcItems->end(); ++Iter)
   {
      auto Iter2 = Iter;
      ++Iter2;
      if (Iter2 == pvecArcItems->end())
      {
         Iter->m_nPart1 = 0;
      }
      else
      {
         Iter->m_nPart1 = Iter2->m_nPart1;
      }
   }
   return TRUE;
}

BOOL GetNextRevo(BOOL bFastToSlow, int nRevoCountCurrent, int nFZCountCurrent, int *pRevoNew, int *pFZCountNew)
{
   if (!bFastToSlow)
   { //斜率由陡到缓
      if (nRevoCountCurrent > 1)
      {
         --nRevoCountCurrent;
      }
      else
      {
         ++nFZCountCurrent;
      }
   }
   else
   { //斜率由缓到陡
      if (nFZCountCurrent > 1)
      {
         nFZCountCurrent--;
      }
      else
      {
         ++nRevoCountCurrent;
      }
   }

   if (pRevoNew)
   {
      *pRevoNew = nRevoCountCurrent;
   }
   if (pFZCountNew)
   {
      *pFZCountNew = nFZCountCurrent;
   }

   return TRUE;
}

BOOL funcCalcArc3Org(CPoint point[4],  int nTotalNeedle, int nTotalRevolution, int nTolerance,
   int nFZNeedle, BOOL bReduceFirst, std::vector<CArcItem> *pvecArcItems)
{
   int nMinX = point[0].x;
   int nMinY = point[3].y;

   //使得贝塞尔坐标最小从0开始
   for (int i = 0; i < 4; ++i)
   {
      point[i].x -= nMinX;
      point[i].y -= nMinY;
   }

   //    int nX = nMaxX - nMinX; //位图宽度
   //    int nY = nMaxY - nMinY; //位图高度
   int nX = 0;
   int nY = 0;




   int nPixelPerXLine = (int)((double)point[3].x / nTotalNeedle);
   int nPixelPerYLine = (int)((double)point[0].y  / nTotalRevolution);

   //

   CPoint CurrentPoint(point[0].x, point[0].y); // point[0].x == 0
   int nCurRevolutionRemain = nTotalRevolution; //当前转数
   int nNeedleRemain = nTotalNeedle; //当前针数
   nNeedleRemain -= nFZNeedle; //观察了易佳的做法，最后至少要有1次收针，不能平摇，也不能倒退
   int nMaxNeedlePixelX = (int)point[3].x;

   int nMinRevolutionPixelY = (int)point[3].y;
   int nPixelPerXLineFZ = nFZNeedle * nPixelPerXLine; //每分针的像素数
   int nInitialTolerance = nTolerance; //允许误差初始值
   int nToleranceNeedle = nTolerance; //允许误差针数
   int nTolerancePixelX = nToleranceNeedle * nPixelPerXLine; //允许误差像素数

   int nMostY = point[0].y;

   //    auto funcGetYByX = [&vecBytes, nMostY](int x)->int
   //    {
   //       int y = nMostY;
   //       for (; y >= 0; --y)
   //       {
   //          if (vecBytes[y][x] == 1)
   //          {
   //             return y;
   //          }
   //       }
   //       return 0;
   //    };
   // 
   //    auto funcGetXByY = [&vecBytes, nMaxNeedlePixelX](int y)->int
   //    {
   //       for (int x = 0; x < nMaxNeedlePixelX; ++x)
   //       {
   //          if (vecBytes[y][x] == 1)
   //          {
   //             return x;
   //          }
   //       }
   //       return 0;
   //    };

   std::vector<CArcItem> vecTempArcItems;

   enum
   {
      FAKE,
      STEP_BY_STEP_CALC_TOLERANCE_AND_CHECK_GRADIENT_CHECK_LAST_METHOD_AND_CAN_OVER_END_RADIENT, //同上，且可以超过最终斜率  另外还增加了控制点翻转处理

      //STEP_BY_STEP_CALC_TOLERANCE_AND_CHECK_GRADIENT_CHECK_LAST_METHOD_AND_CAN_OVER_END_RADIENT_TWO_DIRECTION, //可以从右算到左，斜率全都是从缓到陡

      STEP_BY_STEP_CALC_TOLERANCE_AND_CHECK_GRADIENT_CHECK_LAST_METHOD_AND_CAN_OVER_END_RADIENT_SAVE_ITEM_ANALYZE,
   } eMethod = STEP_BY_STEP_CALC_TOLERANCE_AND_CHECK_GRADIENT_CHECK_LAST_METHOD_AND_CAN_OVER_END_RADIENT;

   if (eMethod == FAKE)
   {
      //暂时先画4个一样的阶梯
      CArcItem Arc;
      Arc.m_nPart1 = 3;
      Arc.m_nPart2 = 2;
      Arc.m_nPart3 = 2;
      vecTempArcItems.push_back(Arc);
      vecTempArcItems.push_back(Arc);
      vecTempArcItems.push_back(Arc);
      vecTempArcItems.push_back(Arc);

      //再画剩下的部分
      nTotalNeedle -= 2 * 2 * 4;
      nTotalRevolution -= 3 * 2 * 4;
      Arc.m_nPart1 = nTotalRevolution;
      Arc.m_nPart2 = nTotalNeedle;
      Arc.m_nPart3 = 1;
      vecTempArcItems.push_back(Arc);
   }
   else if (eMethod == STEP_BY_STEP_CALC_TOLERANCE_AND_CHECK_GRADIENT_CHECK_LAST_METHOD_AND_CAN_OVER_END_RADIENT)
   {
      enum
      {
         LOOP_BY_COPY_LAST, //重复上一次
         LOOP_BY_ROW_NEEDLE_CHANGE, //改变转针次
         LOOP_BY_ROW_NEEDLE_CHANGE_NO_RETURN_BACKUP, //改变转针,不返回，变化误差值
         LOOP_BY_TOLERANCE_CHANGE, //改变允许误差值
      } eLoopType;

      int nRevoCountFirst = 0;
      int nFZCountFirst = 0;

      double dGradientStart = (double)(point[0].y - point[1].y) / (point[1].x); //斜率
      double dGradientEnd = (double)(point[1].y - point[3].y) / (point[3].x - point[1].x);
      TRACE(_T("dGradientEnd %lf\n"), dGradientEnd);

      double dGradientMiddle = (double)point[0].y / point[3].x;
      BOOL bReverse = FALSE;

      CBazierDrawFast BazerFunc;

      BOOL bFastToSlow = FALSE;

      {
         double dy = - (double)point[1].x * double(point[0].y) / point[3].x + point[0].y;
         if (point[1].y > dy)
         {
            bFastToSlow = TRUE;
         }
      }

      //if ((point[1].x >= 0 || point[1].y > point[0].y) && dGradientStart < dGradientMiddle/* && point[1].x <= point[3].x && point[1].y <= point[0].y*/)
      if (bFastToSlow)
      {
         bReverse = TRUE;
         CPoint pointTemp[4];
         for (int i = 0; i < 4; ++i)
         {
            pointTemp[i] = point[i];
         }
         int nTempX = pointTemp[3].x - pointTemp[1].x;
         pointTemp[1].x = pointTemp[2].x = nTempX;
         int nTempY = pointTemp[0].y - pointTemp[1].y;
         pointTemp[1].y = pointTemp[2].y = nTempY;
         dGradientStart = (double)(pointTemp[0].y - pointTemp[1].y) / (pointTemp[1].x); //斜率
         dGradientEnd = (double)(pointTemp[1].y - pointTemp[3].y) / (pointTemp[3].x - pointTemp[1].x);
         dGradientMiddle = (double)pointTemp[0].y / pointTemp[3].x;

         BazerFunc.Init(nX, nY, pointTemp);

         //for (int i = 0; i < 4; ++i)
         //{
         //   point[i] = pointTemp[i];
         //}

         bFastToSlow = FALSE;
      }
      else
      {
         BazerFunc.Init(nX, nY, point);
      }

      //if (dGradientStart > 1)
      //{
      //   TRACE(_T("dGradientStart %lf\n"), dGradientStart);
      //   b1FZFirst = TRUE;

      //   int nYTouch = BazerFunc.funcGetYByX(nPixelPerXLineFZ * 1);

      //   //一开始多少转
      //   nRevoCountFirst = ((double)(nMaxY - nYTouch))/nPixelPerYLine + 0.5;

      //   nFZCountFirst = 1;

      //   TRACE(_T("nRevoCountFirst %d\n"), nRevoCountFirst);
      //}
      //else if (dGradientStart < 1)
      //{
      //   TRACE(_T("dGradientStart %lf\n"), dGradientStart);
      //   b1FZFirst = FALSE;

      //   int nXTouch = BazerFunc.funcGetXByY(nMostY - nPixelPerYLine);

      //   //一开始多少倍分针数
      //   nFZCountFirst = ((double)nXTouch / nPixelPerXLineFZ) + 0.5;

      //   nRevoCountFirst = 1;

      //   TRACE(_T("nFZCountFirst %d\n"), nFZCountFirst);
      //}

      //if (dGradientStart < 1)
      {
         TRACE(_T("dGradientStart %lf\n"), dGradientStart);

         int nXTouch = BazerFunc.funcGetXByY(nMostY - nPixelPerYLine); //计算1转处的分针数

         TRACE(_T("nXTouch %d\n"), nXTouch);

         //一开始多少倍分针数
         nFZCountFirst = ((double)nXTouch / nPixelPerXLineFZ)/* + 0.5*/;

         if (nFZCountFirst >= 1)
         {
            nRevoCountFirst = 1;

            TRACE(_T("nFZCountFirst %d\n"), nFZCountFirst);
         }
         else
         {
            TRACE(_T("dGradientStart %lf\n"), dGradientStart);

            int ByX = nPixelPerXLineFZ * 1;

            //if (dGradientStart < 1) //一开始缓
            //{
            //   int nLeaveNeedle = nTotalNeedle % nFZNeedle;
            //   if (nLeaveNeedle > 0)
            //   {
            //      //Arc.m_nPart2 += nLeaveNeedle;
            //      ByX += nLeaveNeedle * nPixelPerXLine;
            //   }
            //}

            int nYTouch = BazerFunc.funcGetYByX(ByX);

            //一开始多少转
            nRevoCountFirst = ((double)(nMostY - nYTouch))/nPixelPerYLine + 0.5;

            nFZCountFirst = 1;

            TRACE(_T("nRevoCountFirst %d\n"), nRevoCountFirst);
         }

      }

      //观察了易佳的做法，最后至少要有1次收针，不能平摇，也不能倒退，所以要去除1倍分针的像素数，1倍分针可能相当于收2针或更多针
      nMaxNeedlePixelX -= nPixelPerXLineFZ;

      int nDiv = 0;

      CArcItem Arc;

      if (!bReduceFirst)
      {
         CurrentPoint.y -= nPixelPerYLine * nRevoCountFirst; //先平摇nRevoCountFirst转
         Arc.m_nPart1 = nRevoCountFirst;
         Arc.m_nPart2 = nFZCountFirst * nFZNeedle;

         //if (dGradientStart < 1) //一开始缓
         //{
         //   int nLeaveNeedle = nTotalNeedle % nFZNeedle;
         //   if (nLeaveNeedle > 0)
         //   {
         //      Arc.m_nPart2 += nLeaveNeedle;
         //   }
         //}


         CurrentPoint.x += Arc.m_nPart2 * nPixelPerXLine;
         Arc.m_nPart3 = 1;
         nCurRevolutionRemain -= Arc.m_nPart1 * Arc.m_nPart3;
         nNeedleRemain -= Arc.m_nPart2 * Arc.m_nPart3;
         vecTempArcItems.push_back(Arc);
      }
      else
      {
         Arc.m_nPart1 = 0; //先收, 无转数
         nDiv = 1; //1倍分针数
         Arc.m_nPart2 = nFZCountFirst * nFZNeedle;
         CurrentPoint.x += Arc.m_nPart2 * nPixelPerXLine;
         Arc.m_nPart3 = 1;

         nCurRevolutionRemain -= Arc.m_nPart1 * Arc.m_nPart3;
         nNeedleRemain -= Arc.m_nPart2 * Arc.m_nPart3;
         vecTempArcItems.push_back(Arc);

         //          CurrentPoint.y -= nPixelPerYLine * nRevoCountFirst; //先平摇nRevoCountFirst转
         //          Arc.m_nPart1 = 0; //先收, 无转数
         //          nDiv = 1; //1倍分针数
         //          Arc.m_nPart2 = nFZCountFirst * nFZNeedle;
         //          CurrentPoint.x += nFZCountFirst * nPixelPerXLineFZ;
         //          Arc.m_nPart3 = 1;
         // 
         //          nCurRevolutionRemain -= Arc.m_nPart1 * Arc.m_nPart3;
         //          nNeedleRemain -= Arc.m_nPart2 * Arc.m_nPart3;
         //          vecTempArcItems.push_back(Arc);
      }

      //       BOOL bFastToSlow = FALSE;
      // 
      //       {
      //          double dy = - (double)point[1].x * double(point[0].y) / point[3].x + point[0].y;
      //          if (point[1].y > dy)
      //          {
      //             bFastToSlow = TRUE;
      //          }
      //       }

      int nCount = 0;

      int nRevoCountCurrent = nRevoCountFirst;
      int nFZCountCurrent = nFZCountFirst;
      int nRevoCountBack = nRevoCountCurrent;
      int nFZCountBack = nFZCountCurrent;

      eLoopType = LOOP_BY_COPY_LAST;
      int nLastDiff = INT_MAX;

      while (CurrentPoint.x < nMaxNeedlePixelX)
      {
         ++nCount;
         TRACE(_T("nCount%d\n"), nCount);

         //尝试同样斜率重复一次，再算偏差

         CArcItem ArcTemp = Arc;
         ArcTemp.m_nPart1 = nRevoCountCurrent;
         ArcTemp.m_nPart2 = nFZCountCurrent * nFZNeedle;

         BOOL bOverX = FALSE;
         BOOL bOverY = FALSE;
         if (CurrentPoint.x + ArcTemp.m_nPart2 * nPixelPerXLine > nMaxNeedlePixelX)
         {
            bOverX = TRUE;
            //break; //超出范围
         }

         if (CurrentPoint.y - ArcTemp.m_nPart1 * nPixelPerYLine < nMinRevolutionPixelY)
         {
            bOverY = TRUE;
            //break; //超出范围
         }

         int nNewY;
         int nx;
         int nDiff;

         if (!bOverX && !bOverY)
         {
            nNewY = CurrentPoint.y - ArcTemp.m_nPart1 * ArcTemp.m_nPart3 * nPixelPerYLine;
            nx = BazerFunc.funcGetXByY(nNewY);

            nDiff = nx - (CurrentPoint.x + ArcTemp.m_nPart2 * nPixelPerXLine);

            if (eLoopType == LOOP_BY_ROW_NEEDLE_CHANGE && abs(nDiff) > abs(nLastDiff)) //放 if (!bOver) 后面是否合理？
            {
               //还原数据
               nRevoCountCurrent = nRevoCountBack;
               nFZCountCurrent = nFZCountBack;

               eLoopType = LOOP_BY_TOLERANCE_CHANGE;
               ++nToleranceNeedle; //增加允许误差值
               nTolerancePixelX = nToleranceNeedle * nPixelPerXLine; //允许误差像素数
               continue;
            }

            nLastDiff = nDiff;
            nRevoCountBack = nRevoCountCurrent;
            nFZCountBack = nFZCountCurrent;
         }

         if (!bOverX && !bOverY && abs(nDiff) < nTolerancePixelX)
         { //在误差内
            CurrentPoint.y -= ArcTemp.m_nPart1 * ArcTemp.m_nPart3 * nPixelPerYLine;
            CurrentPoint.x += ArcTemp.m_nPart2 * ArcTemp.m_nPart3 * nPixelPerXLine;

            nCurRevolutionRemain -= ArcTemp.m_nPart1 * ArcTemp.m_nPart3;
            nNeedleRemain -= ArcTemp.m_nPart2 * ArcTemp.m_nPart3;

            if (nCurRevolutionRemain < 0 || nNeedleRemain < 0)
            {
               nCurRevolutionRemain += ArcTemp.m_nPart1 * ArcTemp.m_nPart3;
               nNeedleRemain += ArcTemp.m_nPart2 * ArcTemp.m_nPart3;
               break;
            }

            if (nToleranceNeedle > nInitialTolerance)
            {
               nToleranceNeedle = nInitialTolerance; //恢复初始允许误差值
               nTolerancePixelX = nToleranceNeedle * nPixelPerXLine; //允许误差像素数
            }

            eLoopType = LOOP_BY_COPY_LAST; //将来的一次循环方式为尝试复制当前的转针次

            vecTempArcItems.push_back(ArcTemp); //横向误差内，可重复
         }
         else
         {
            double dGradientEndForCurrentPoint = (double)(CurrentPoint.y) / (nMaxNeedlePixelX + nPixelPerXLineFZ - CurrentPoint.x);

            int nRevoNew = 0;
            int nFZNew = 0;
            BOOL bGetNext = GetNextRevo(bFastToSlow, nRevoCountCurrent, nFZCountCurrent, &nRevoNew, &nFZNew);
            if (!bGetNext)
               break;
            if (!bOverX && !bOverY)
            {
               auto dNew = double(nRevoNew * nPixelPerYLine ) / (nFZNew * nFZNeedle * nPixelPerXLine);

               if (!bFastToSlow)
               {
                  if (dNew < dGradientEnd && dNew < dGradientEndForCurrentPoint)
                  {
                     TRACE(_T("平过头了%lf\n"), dNew);

                     ++nToleranceNeedle; //增加允许误差值
                     nTolerancePixelX = nToleranceNeedle * nPixelPerXLine; //允许误差像素数

                     eLoopType = LOOP_BY_TOLERANCE_CHANGE;
                  }
                  else
                  {
                     nRevoCountCurrent = nRevoNew;
                     nFZCountCurrent = nFZNew;
                     eLoopType = LOOP_BY_ROW_NEEDLE_CHANGE;
                  }
               }
               else
               {
                  if (dNew > dGradientEnd && dNew > dGradientEndForCurrentPoint)
                  {
                     TRACE(_T("陡过头了%lf\n"), dNew);

                     ++nToleranceNeedle; //增加允许误差值
                     nTolerancePixelX = nToleranceNeedle * nPixelPerXLine; //允许误差像素数

                     eLoopType = LOOP_BY_TOLERANCE_CHANGE;
                  }
                  else
                  {
                     nRevoCountCurrent = nRevoNew;
                     nFZCountCurrent = nFZNew;
                     eLoopType = LOOP_BY_ROW_NEEDLE_CHANGE;
                  }
               }
            }
            else //越过矩形范围边界
            {
               if (nRevoNew > nRevoCountCurrent || nFZNew > nFZCountCurrent)
               {
                  break;
               }
               else
               {
                  nRevoCountCurrent = nRevoNew;
                  nFZCountCurrent = nFZNew;
                  eLoopType = LOOP_BY_ROW_NEEDLE_CHANGE_NO_RETURN_BACKUP;
               }
            }
         }
      }

      //再画剩下的部分
      Arc.m_nPart1 = nCurRevolutionRemain;
      TRACE(_T("nCurRevolutionRemain %d\n"), nCurRevolutionRemain);
      TRACE(_T("nNeedleRemain + nFZNeedle %d\n"), nNeedleRemain + nFZNeedle);
      Arc.m_nPart2 = nNeedleRemain + nFZNeedle; //+nFZNeedle 补上分针数 观察了易佳的做法，最后至少要有1次收针，不能平摇，也不能倒退
      Arc.m_nPart3 = 1;

      if (!bFastToSlow && !vecTempArcItems.empty())
         //if ((dGradientStart > dGradientMiddle || point[1].x < 0) && !vecTempArcItems.empty()) //最后收尾处理，防止斜率突然变化回去
      {
         //double d1 = (double)vecTempArcItems.back().m_nPart1 / (double)vecTempArcItems.back().m_nPart2;
         //double d2 = (double)Arc.m_nPart1 / (double)Arc.m_nPart2;
         int n1 = vecTempArcItems.back().m_nPart1 * Arc.m_nPart2;
         int n2 = Arc.m_nPart1 * vecTempArcItems.back().m_nPart2;
         while (n2 > n1)
         {
            BOOL bProcessed = FALSE;
            CArcItem *pLastArc = &vecTempArcItems.back();
            for (auto Iter = vecTempArcItems.rbegin(); Iter != vecTempArcItems.rend(); ++Iter)
            {
               if (Iter->m_nPart1 == pLastArc->m_nPart1 && Iter->m_nPart2 == pLastArc->m_nPart2)
               {
                  pLastArc = &*Iter; //记录最后一个一样的阶梯的地址
               }
               else
               {
                  if (Iter->m_nPart1 > pLastArc->m_nPart1 && Iter->m_nPart2 == pLastArc->m_nPart2 
                     && Arc.m_nPart1 > vecTempArcItems.back().m_nPart1)
                  {
                     ++pLastArc->m_nPart1;
                     --Arc.m_nPart1;
                     bProcessed = TRUE;
                  }
                  else if (Iter->m_nPart1 == pLastArc->m_nPart1 && Iter->m_nPart2 < pLastArc->m_nPart2 
                     && Arc.m_nPart2 - (Arc.m_nPart2 % nFZNeedle) < vecTempArcItems.back().m_nPart2)
                  {
                     pLastArc->m_nPart2 -= nFZNeedle;
                     Arc.m_nPart2 += nFZNeedle;
                     bProcessed = TRUE;
                  }
                  break;
               }
            }

            if (!bProcessed)
               break; //无法处理

            n1 = vecTempArcItems.back().m_nPart1 * Arc.m_nPart2;
            n2 = Arc.m_nPart1 * vecTempArcItems.back().m_nPart2;
         }
      }

      if (bReverse)
      { //将余数合并到前面
         int nMod = Arc.m_nPart2 % nFZNeedle;
         if (nMod > 0 && !vecTempArcItems.empty())
         {
            vecTempArcItems.front().m_nPart2 += nMod;
            Arc.m_nPart2 -= nMod;
         }
      }

      vecTempArcItems.push_back(Arc);



      //先收临时处理
      if (bReduceFirst)
      {
         if (bReverse && !vecTempArcItems.empty())
         {
            //             vecTempArcItems.push_back(vecTempArcItems.front());
            //             vecTempArcItems.erase(vecTempArcItems.begin());
            ChangeAngles(&vecTempArcItems);
         }
      }

      if (bReverse)
      {
         std::reverse(vecTempArcItems.begin(), vecTempArcItems.end());
      }

      if (bReduceFirst && !vecTempArcItems.empty()) //先收 工艺单的显示改成和工艺软件一致
      {
         //vecTempArcItems.size() >= 2
         auto Iter = vecTempArcItems.begin();
         ASSERT(Iter->m_nPart1 == 0);
         auto Iter2 = Iter;
         ++Iter2;
         if (Iter2 != vecTempArcItems.end())
         {
            if (Iter->m_nPart2 == Iter2->m_nPart2)
            {
               Iter->m_nPart1 = Iter2->m_nPart1;
            }
            else
            {
               Iter->m_nPart1 = 1;
            }
         }
         else
         {
            Iter->m_nPart1 = 1;
         }
      }

      //合并同样的段
      CombineSameSection(&vecTempArcItems);
   }
   else if (STEP_BY_STEP_CALC_TOLERANCE_AND_CHECK_GRADIENT_CHECK_LAST_METHOD_AND_CAN_OVER_END_RADIENT_SAVE_ITEM_ANALYZE == eMethod)
   {
      CBazierDrawFast BazerFunc;
      BazerFunc.Init(nX, nY, point);

      enum
      {
         LOOP_BY_COPY_LAST, //重复上一次
         LOOP_BY_ROW_NEEDLE_CHANGE, //改变转针次
         LOOP_BY_ROW_NEEDLE_CHANGE_NO_RETURN_BACKUP, //改变转针,不返回，变化误差值
         LOOP_BY_ROW_NEEDLE_CHANGE_FORCE, //强制改变，不计较误差
         LOOP_BY_TOLERANCE_CHANGE, //改变允许误差值
      } eLoopType;

      std::vector<CArcItemExt> vecTempArcItemsExt;



      int nRevoCountFirst = 0;
      int nFZCountFirst = 0;

      double dGradientStart = (double)(point[0].y - point[1].y) / (point[1].x); //斜率
      double dGradientEnd = (double)(point[1].y - point[3].y) / (point[3].x - point[1].x);
      TRACE(_T("dGradientEnd %lf\n"), dGradientEnd);
      BOOL b1FZFirst = TRUE; //先尝试1倍分针
      //if (dGradientStart > 1)
      //{
      //   TRACE(_T("dGradientStart %lf\n"), dGradientStart);
      //   b1FZFirst = TRUE;

      //   int nYTouch = BazerFunc.funcGetYByX(nPixelPerXLineFZ * 1);

      //   //一开始多少转
      //   nRevoCountFirst = ((double)(nMaxY - nYTouch))/nPixelPerYLine + 0.5;

      //   nFZCountFirst = 1;

      //   TRACE(_T("nRevoCountFirst %d\n"), nRevoCountFirst);
      //}
      //else if (dGradientStart < 1)
      //{
      //   TRACE(_T("dGradientStart %lf\n"), dGradientStart);
      //   b1FZFirst = FALSE;

      //   int nXTouch = BazerFunc.funcGetXByY(nMostY - nPixelPerYLine);

      //   //一开始多少倍分针数
      //   nFZCountFirst = ((double)nXTouch / nPixelPerXLineFZ) + 0.5;

      //   nRevoCountFirst = 1;

      //   TRACE(_T("nFZCountFirst %d\n"), nFZCountFirst);
      //}

      {
         TRACE(_T("dGradientStart %lf\n"), dGradientStart);
         b1FZFirst = FALSE;

         int nXTouch = BazerFunc.funcGetXByY(nMostY - nPixelPerYLine); //计算1转处的分针数

         //一开始多少倍分针数
         nFZCountFirst = ((double)nXTouch / nPixelPerXLineFZ) + 0.5;

         if (nFZCountFirst >= 1)
         {
            nRevoCountFirst = 1;

            TRACE(_T("nFZCountFirst %d\n"), nFZCountFirst);
         }
         else
         {
            TRACE(_T("dGradientStart %lf\n"), dGradientStart);
            b1FZFirst = TRUE;

            int nYTouch = BazerFunc.funcGetYByX(nPixelPerXLineFZ * 1);

            //一开始多少转
            nRevoCountFirst = ((double)(nMostY - nYTouch))/nPixelPerYLine + 0.5;

            nFZCountFirst = 1;

            TRACE(_T("nRevoCountFirst %d\n"), nRevoCountFirst);
         }
      }

      //观察了易佳的做法，最后至少要有1次收针，不能平摇，也不能倒退，所以要去除1倍分针的像素数，1倍分针可能相当于收2针或更多针
      nMaxNeedlePixelX -= nPixelPerXLineFZ;

      int nDiv = 0;

      CArcItemExt Arc;
      Arc.CurrentPoint = CurrentPoint;
      //Arc.bByForce = FALSE;

      if (!bReduceFirst)
      {
         CurrentPoint.y -= nPixelPerYLine * nRevoCountFirst; //先平摇nRevoCountFirst转
         Arc.m_nPart1 = nRevoCountFirst;
         Arc.m_nPart2 = nFZCountFirst * nFZNeedle;
         CurrentPoint.x += Arc.m_nPart2 * nPixelPerXLine;
         Arc.m_nPart3 = 1;
         nCurRevolutionRemain -= Arc.m_nPart1 * Arc.m_nPart3;
         nNeedleRemain -= Arc.m_nPart2 * Arc.m_nPart3;
         vecTempArcItemsExt.push_back(Arc);
      }
      else
      {
         Arc.m_nPart1 = 0; //先收, 无转数
         nDiv = 1; //1倍分针数
         Arc.m_nPart2 = nFZCountFirst * nFZNeedle;
         CurrentPoint.x += Arc.m_nPart2 * nPixelPerXLine;
         Arc.m_nPart3 = 1;

         nCurRevolutionRemain -= Arc.m_nPart1 * Arc.m_nPart3;
         nNeedleRemain -= Arc.m_nPart2 * Arc.m_nPart3;
         vecTempArcItemsExt.push_back(Arc);

         //          CurrentPoint.y -= nPixelPerYLine * nRevoCountFirst; //先平摇nRevoCountFirst转
         //          Arc.m_nPart1 = 0; //先收, 无转数
         //          nDiv = 1; //1倍分针数
         //          Arc.m_nPart2 = nFZCountFirst * nFZNeedle;
         //          CurrentPoint.x += nFZCountFirst * nPixelPerXLineFZ;
         //          Arc.m_nPart3 = 1;
         // 
         //          nCurRevolutionRemain -= Arc.m_nPart1 * Arc.m_nPart3;
         //          nNeedleRemain -= Arc.m_nPart2 * Arc.m_nPart3;
         //          vecTempArcItems.push_back(Arc);
      }

      int nCount = 0;

      int nRevoCountCurrent = nRevoCountFirst;
      int nFZCountCurrent = nFZCountFirst;
      int nRevoCountBack = nRevoCountCurrent;
      int nFZCountBack = nFZCountCurrent;

      eLoopType = LOOP_BY_COPY_LAST;
      int nLastDiff = INT_MAX;

      while (CurrentPoint.x < nMaxNeedlePixelX)
      {
         ++nCount;
         TRACE(_T("nCount%d\n"), nCount);

         //尝试同样斜率重复一次，再算偏差

         CArcItemExt ArcTemp;
         ArcTemp.m_nPart1 = nRevoCountCurrent;
         ArcTemp.m_nPart2 = nFZCountCurrent * nFZNeedle;
         //         ArcTemp.m_nPart3 = 1;
         ArcTemp.CurrentPoint = CurrentPoint;
         //          ArcTemp.bByForce = FALSE;
         //          ArcTemp.nDiff = 0;

         BOOL bOverX = FALSE;
         BOOL bOverY = FALSE;
         if (CurrentPoint.x + ArcTemp.m_nPart2 * nPixelPerXLine > nMaxNeedlePixelX)
         {
            bOverX = TRUE;
            //break; //超出范围
         }

         if (CurrentPoint.y - ArcTemp.m_nPart1 * nPixelPerYLine < nMinRevolutionPixelY)
         {
            TRACE(_T("CurrentPoint.y %d\n"), CurrentPoint.y);
            bOverY = TRUE;
            //break; //超出范围
         }

         int nNewY;
         int nx;
         int nDiff;

         if (!bOverX && !bOverY)
         {
            nNewY = CurrentPoint.y - ArcTemp.m_nPart1 * ArcTemp.m_nPart3 * nPixelPerYLine;
            if (nNewY < 0)
               break;

            nx = BazerFunc.funcGetXByY(nNewY);

            nDiff = nx - (CurrentPoint.x + ArcTemp.m_nPart2 * nPixelPerXLine);

            //int nLastDiff = INT_MAX;

            //             if (!vecTempArcItemsExt.empty())
            //                nLastDiff = vecTempArcItemsExt.back().nDiff;

            BOOL bRowNeedle = FALSE;

            if (eLoopType == LOOP_BY_ROW_NEEDLE_CHANGE
               && abs(nDiff) > abs(nLastDiff)) //误差变大
            {
               bRowNeedle = TRUE;
            }

            BOOL bTolerance = FALSE;
            //if (eLoopType == LOOP_BY_TOLERANCE_CHANGE)
            //{
            //   bTolerance = TRUE;
            //}

            if (
               (bRowNeedle || bTolerance)
               /*&& CurrentPoint.x <= point[1].x*/

               //|| (eLoopType == LOOP_BY_TOLERANCE_CHANGE && CurrentPoint.x <= point[1].x)

               ) //放 if (!bOver) 后面是否合理？
            {
               if (1)
               {
                  //还原数据
                  nRevoCountCurrent = nRevoCountBack;
                  nFZCountCurrent = nFZCountBack;


                  //                   nNewY = CurrentPoint.y - ArcTemp.m_nPart1 * ArcTemp.m_nPart3 * nPixelPerYLine;
                  //                   nx = funcGetXByY(nNewY);

                  int nLoopCount = 1;
                  int nCalcX = 0;
                  int nCalcY = 0;

                  while (nLoopCount < 1000)
                  {
                     nCalcY = CurrentPoint.y - nRevoCountCurrent * nLoopCount * nPixelPerYLine; //y移动一个台阶
                     if (nCalcY < 0)
                     {
                        TRACE(_T("nLoopCount %d nCalcY %d\n"), nLoopCount, nCalcY);
                        break;
                     }
                     nx = BazerFunc.funcGetXByY(nCalcY);

                     nCalcX = CurrentPoint.x + nFZCountCurrent * nLoopCount * nPixelPerXLineFZ; //nFZNeedle * nPixelPerXLine;
                     if (nCalcX > nx)
                     {
                        TRACE(_T("nLoopCount %d nCalcY %d nCalcX %d\n"), nLoopCount, nCalcY, nCalcX);
                        //TRACE(_T("%d\n"), nCalcY);
                        break;
                     }

                     if (nCalcX > nMaxNeedlePixelX)
                     {
                        TRACE(_T("nLoopCount %d nCalcY %d nCalcX %d\n"), nLoopCount, nCalcY, nCalcX);
                        //TRACE(_T("%d\n"), nCalcY);
                        break;
                     }
                     ++nLoopCount;

                  }
                  TRACE(_T("nLoopCount %d \n"), nLoopCount);
                  // double(nCalcX - CurrentPoint.x)/nMaxNeedlePixelX
                  int nLengthX = nCalcX - CurrentPoint.x;
                  double dAAA = double(nLengthX)/nMaxNeedlePixelX;
                  if (nCalcX < nMaxNeedlePixelX && dAAA > 0.25)
                  {
                     TRACE(_T("dAAA %lf\n"), dAAA);

                     //todo 退回之前相同数据  强制加入一段之前斜率的阶梯，宽为总体1/3, 再强制加入一段现在斜率的阶梯，之后再自由处理

                     //todo 退回之前相同数据
                     //vecTempArcItemsExt.pop_back();
                     int nNeedleCountCurrent =  nFZCountCurrent * nFZNeedle;
                     CArcItemExt LastItemExt;
                     BOOL bPoped = FALSE;
                     while (!vecTempArcItemsExt.empty()
                        && vecTempArcItemsExt.back().m_nPart1 == nRevoCountCurrent
                        && vecTempArcItemsExt.back().m_nPart2 == nNeedleCountCurrent)
                     {
                        LastItemExt = vecTempArcItemsExt.back();

                        //      LastArcItem = vecTempArcItemsExt.back();
                        nCurRevolutionRemain += LastItemExt.m_nPart1 * LastItemExt.m_nPart3;
                        nNeedleRemain += LastItemExt.m_nPart2 * LastItemExt.m_nPart3;

                        //      vecTempArcItemsExt.pop_back();
                        bPoped = TRUE;

                        vecTempArcItemsExt.pop_back();
                     }
                     if (bPoped)
                     {
                        CurrentPoint = LastItemExt.CurrentPoint; //恢复
                        //nRevoCountCurrent = LastItemExt.m_nPart1;
                        //nFZCountCurrent = LastItemExt.m_nPart2 / nFZNeedle;
                     }

                     int nLoopFZCount = nFZCountCurrent;
                     int nLoopRevoCount = nRevoCountCurrent;

                     if (dGradientStart > 1) //陡至缓
                     {
                        if (nFZCountCurrent > 1)
                        {

                           nFZCountCurrent--;
                           //if (nFZCountLast != -1 && nFZCountCurrent < nFZCountLast)
                           //{
                           //   nFZCountCurrent++; //只好恢复
                           //}
                        }
                        else
                        {
                           nRevoCountCurrent++;
                           //if (nRevoCountLast != -1 && nRevoCountCurrent > nRevoCountLast)
                           //{
                           //   nRevoCountCurrent--; //只好恢复
                           //}
                        }
                     }
                     else
                     {
                        if (nRevoCountCurrent > 1)
                        {
                           nRevoCountCurrent--;
                           //if (nRevoCountLast != -1 && nRevoCountCurrent < nRevoCountLast)
                           //{
                           //   nRevoCountCurrent++; //只好恢复
                           //}
                        }
                        else
                        {
                           nFZCountCurrent++;
                           //if (nFZCountLast != -1 && nFZCountCurrent > nFZCountLast)
                           //{
                           //   nFZCountCurrent--; //只好恢复
                           //}
                        }
                     }

                     CArcItemExt NewItemExt;
                     NewItemExt.m_nPart1 = nRevoCountCurrent;
                     NewItemExt.m_nPart2 = nFZCountCurrent * nFZNeedle;

                     TRACE(_T("NewItemExt.m_nPart1 %d NewItemExt.m_nPart2 %d\n"), NewItemExt.m_nPart1, NewItemExt.m_nPart2);

                     NewItemExt.m_nPart3 = 1;
                     NewItemExt.CurrentPoint = CurrentPoint;
                     NewItemExt.nDiff = 0; //??? 这个好像没用了
                     NewItemExt.bByForce = TRUE;

                     int nLengthOneThird = nLengthX / 3;
                     int nLengthOneThirdPos = CurrentPoint.x + nLengthOneThird;



                     while (NewItemExt.CurrentPoint.x < nLengthOneThirdPos)
                     {
                        //                         NewItemExt.m_nPart1 = nRevoCountCurrent;
                        //                         NewItemExt.m_nPart2 = nFZCountCurrent * nFZNeedle;
                        //                         NewItemExt.m_nPart3 = 1;
                        //                         NewItemExt.CurrentPoint = CurrentPoint;
                        //                         NewItemExt.nDiff = 0; //??? 这个好像没用了
                        //                         NewItemExt.bByForce = TRUE;
                        vecTempArcItemsExt.push_back(NewItemExt);

                        nCurRevolutionRemain -= NewItemExt.m_nPart1 * NewItemExt.m_nPart3;
                        nNeedleRemain -= NewItemExt.m_nPart2 * NewItemExt.m_nPart3;

                        NewItemExt.CurrentPoint.x += nFZCountCurrent * nFZNeedle * nPixelPerXLine;
                        NewItemExt.CurrentPoint.y -= nRevoCountCurrent * nPixelPerYLine;
                     }

                     int nLengthOneThirdPos2 = nLengthOneThirdPos + nLengthOneThird;

                     //int nLoopFZCount = nFZCountCurrent;
                     //int nLoopRevoCount = nRevoCountCurrent;

                     NewItemExt.m_nPart1 = nLoopRevoCount;
                     NewItemExt.m_nPart2 = nLoopFZCount * nFZNeedle;

                     while (NewItemExt.CurrentPoint.x < nLengthOneThirdPos2)
                     {
                        //                         NewItemExt.m_nPart1 = nRevoCountCurrent;
                        //                         NewItemExt.m_nPart2 = nFZCountCurrent * nFZNeedle;
                        //                         NewItemExt.m_nPart3 = 1;
                        //                         NewItemExt.CurrentPoint = CurrentPoint;
                        //                         NewItemExt.nDiff = 0; //??? 这个好像没用了
                        //                         NewItemExt.bByForce = TRUE;
                        vecTempArcItemsExt.push_back(NewItemExt);

                        nCurRevolutionRemain -= NewItemExt.m_nPart1 * NewItemExt.m_nPart3;
                        nNeedleRemain -= NewItemExt.m_nPart2 * NewItemExt.m_nPart3;

                        NewItemExt.CurrentPoint.x += nLoopFZCount * nFZNeedle * nPixelPerXLine;
                        NewItemExt.CurrentPoint.y -= nLoopRevoCount * nPixelPerYLine;
                     }

                     nFZCountCurrent = nLoopFZCount;
                     nRevoCountCurrent = nLoopRevoCount;
                     eLoopType = LOOP_BY_COPY_LAST;

                     CurrentPoint.x = NewItemExt.CurrentPoint.x;
                     CurrentPoint.y = NewItemExt.CurrentPoint.y;
                     continue;
                  }

                  //CurrentPoint.x + nFZCountCurrent * 

                  eLoopType = LOOP_BY_TOLERANCE_CHANGE;
                  ++nToleranceNeedle; //增加允许误差值
                  nTolerancePixelX = nToleranceNeedle * nPixelPerXLine; //允许误差像素数
                  continue;
               }


               //if (!vecTempArcItemsExt.empty())
               //{
               //   BOOL bPoped = FALSE;
               //   CArcItemExt LastArcItem = vecTempArcItemsExt.back();
               //   while (!vecTempArcItemsExt.empty()
               //      && vecTempArcItemsExt.back().m_nPart1 == LastArcItem.m_nPart1
               //      && vecTempArcItemsExt.back().m_nPart2 == LastArcItem.m_nPart2
               //      && vecTempArcItemsExt.back().m_nPart3 == LastArcItem.m_nPart3
               //      )
               //   {
               //      if (vecTempArcItemsExt.back().bByForce)
               //         break; //只能强制一次
               //      if (vecTempArcItemsExt.back().CurrentPoint.x > point[1].x) //还要额外限制条件：只有当前点在控制点之前时才这么做
               //         break;

               //      bPoped = TRUE;

               //      LastArcItem = vecTempArcItemsExt.back();


               //      nCurRevolutionRemain += LastArcItem.m_nPart1 * LastArcItem.m_nPart3;
               //      nNeedleRemain += LastArcItem.m_nPart2 * LastArcItem.m_nPart3;

               //      vecTempArcItemsExt.pop_back();
               //   }

               //   if (!bPoped)
               //   {
               //      //还原数据
               //      nRevoCountCurrent = nRevoCountBack;
               //      nFZCountCurrent = nFZCountBack;

               //      eLoopType = LOOP_BY_TOLERANCE_CHANGE;
               //      ++nToleranceNeedle; //增加允许误差值
               //      nTolerancePixelX = nToleranceNeedle * nPixelPerXLine; //允许误差像素数
               //      continue;
               //      ;
               //   }
               //   else
               //   {
               //      CurrentPoint = LastArcItem.CurrentPoint; //恢复

               //      nRevoCountCurrent = LastArcItem.m_nPart1;
               //      nFZCountCurrent = LastArcItem.m_nPart2 / nFZNeedle;

               //      int nFZCountLast = -1;
               //      int nRevoCountLast = -1;
               //      if (!vecTempArcItemsExt.empty())
               //      {
               //         nFZCountLast = vecTempArcItemsExt.back().m_nPart2 / nFZNeedle;
               //         nRevoCountLast = vecTempArcItemsExt.back().m_nPart1;
               //      }

               //      if (dGradientStart > 1) //陡至缓
               //      {
               //         if (nFZCountCurrent > 1)
               //         {

               //            nFZCountCurrent--;
               //            if (nFZCountLast != -1 && nFZCountCurrent < nFZCountLast)
               //            {
               //               nFZCountCurrent++; //只好恢复
               //            }
               //         }
               //         else
               //         {
               //            nRevoCountCurrent++;
               //            if (nRevoCountLast != -1 && nRevoCountCurrent > nRevoCountLast)
               //            {
               //               nRevoCountCurrent--; //只好恢复
               //            }
               //         }
               //      }
               //      else
               //      {
               //         if (nRevoCountCurrent > 1)
               //         {
               //            nRevoCountCurrent--;
               //            if (nRevoCountLast != -1 && nRevoCountCurrent < nRevoCountLast)
               //            {
               //               nRevoCountCurrent++; //只好恢复
               //            }
               //         }
               //         else
               //         {
               //            nFZCountCurrent++;
               //            if (nFZCountLast != -1 && nFZCountCurrent > nFZCountLast)
               //            {
               //               nFZCountCurrent--; //只好恢复
               //            }
               //         }
               //      }
               //      //
               //      eLoopType = LOOP_BY_ROW_NEEDLE_CHANGE_FORCE;
               //      continue;
               //   }
               //}
            }

            nLastDiff = nDiff;

            nRevoCountBack = nRevoCountCurrent;
            nFZCountBack = nFZCountCurrent;
         }

         if (!bOverX && !bOverY && (abs(nDiff) < nTolerancePixelX || eLoopType == LOOP_BY_ROW_NEEDLE_CHANGE_FORCE))
         { //在误差内
            CurrentPoint.y -= ArcTemp.m_nPart1 * ArcTemp.m_nPart3 * nPixelPerYLine;
            CurrentPoint.x += ArcTemp.m_nPart2 * ArcTemp.m_nPart3 * nPixelPerXLine;

            nCurRevolutionRemain -= ArcTemp.m_nPart1 * ArcTemp.m_nPart3;
            nNeedleRemain -= ArcTemp.m_nPart2 * ArcTemp.m_nPart3;

            if (nCurRevolutionRemain < 0 || nNeedleRemain < 0)
            {
               nCurRevolutionRemain += ArcTemp.m_nPart1 * ArcTemp.m_nPart3;
               nNeedleRemain += ArcTemp.m_nPart2 * ArcTemp.m_nPart3;
               break;
            }

            if (nToleranceNeedle > nInitialTolerance)
            {
               nToleranceNeedle = nInitialTolerance; //恢复初始允许误差值
               nTolerancePixelX = nToleranceNeedle * nPixelPerXLine; //允许误差像素数
            }
            if (eLoopType == LOOP_BY_ROW_NEEDLE_CHANGE_FORCE)
               ArcTemp.bByForce = TRUE;
            eLoopType = LOOP_BY_COPY_LAST; //将来的一次循环方式为尝试复制当前的转针次

            ArcTemp.nDiff = nDiff;

            BOOL bChanged = FALSE;

            if (vecTempArcItemsExt.back().m_nPart1 != ArcTemp.m_nPart1
               || vecTempArcItemsExt.back().m_nPart2 != ArcTemp.m_nPart2)
            {
               bChanged = TRUE;
            }

            //check 连续相同 是否存在全都是在一边

            //

            vecTempArcItemsExt.push_back(ArcTemp); //横向误差内，可重复



            PrintAll(vecTempArcItemsExt);
            nDiff = ArcTemp.nDiff;
         }
         else
         {
            double dGradientEndForCurrentPoint = (double)(CurrentPoint.y) / (nMaxNeedlePixelX + nPixelPerXLineFZ - CurrentPoint.x);

            if (dGradientStart > 1)
            { //斜率由陡到缓
               if (nRevoCountCurrent > 1)
               {
                  if (!bOverX && !bOverY)
                  {
                     auto dNew = double((nRevoCountCurrent - 1) * nPixelPerYLine ) /  (nFZCountCurrent * nFZNeedle * nPixelPerXLine);

                     TRACE(_T("dGradientEndForCurrentPoint %lf\n"), dGradientEndForCurrentPoint);
                     TRACE(_T("dNew %lf\n"), dNew);
                     TRACE(_T("nRevoCountCurrent %d\n"), nRevoCountCurrent);
                     TRACE(_T("nFZCountCurrent %d\n"), nFZCountCurrent);
                     TRACE(_T("nFZNeedle %d\n"), nFZNeedle);
                     TRACE(_T("CurrentPoint.y %d\n"), CurrentPoint.y);
                     TRACE(_T("CurrentPoint.x %d\n"), CurrentPoint.x);
                     TRACE(_T("nMaxNeedlePixelX %d\n"), nMaxNeedlePixelX);

                     if (dNew < dGradientEnd && dNew < dGradientEndForCurrentPoint)
                     {
                        TRACE(_T("平过头了%lf\n"), dNew);

                        ++nToleranceNeedle; //增加允许误差值
                        nTolerancePixelX = nToleranceNeedle * nPixelPerXLine; //允许误差像素数

                        eLoopType = LOOP_BY_TOLERANCE_CHANGE;
                     }
                     else
                     {
                        nRevoCountCurrent--;
                        eLoopType = LOOP_BY_ROW_NEEDLE_CHANGE;
                     }
                  }
                  else
                  {
                     nRevoCountCurrent--;
                     //eLoopType = LOOP_BY_ROW_NEEDLE_CHANGE;
                     eLoopType = LOOP_BY_ROW_NEEDLE_CHANGE_NO_RETURN_BACKUP;
                  }
               }
               else
               {
                  if (!bOverX && !bOverY)
                  {
                     auto dNew = double(nRevoCountCurrent * nPixelPerYLine ) /  ((nFZCountCurrent + 1) * nFZNeedle * nPixelPerXLine);
                     if (dNew < dGradientEnd && dNew < dGradientEndForCurrentPoint)
                     {
                        TRACE(_T("平过头了2%lf\n"), dNew);

                        ++nToleranceNeedle; //增加允许误差值
                        nTolerancePixelX = nToleranceNeedle * nPixelPerXLine; //允许误差像素数

                        eLoopType = LOOP_BY_TOLERANCE_CHANGE;
                     }
                     else
                     {
                        ++nFZCountCurrent;
                        eLoopType = LOOP_BY_ROW_NEEDLE_CHANGE;
                     }
                  }
                  else
                  {
                     break;
                  }
               }
            }
            else
            { //斜率由缓到陡
               if (nFZCountCurrent > 1)
               {
                  if (!bOverX && !bOverY)
                  {
                     auto dNew = double(nRevoCountCurrent * nPixelPerYLine ) / ((nFZCountCurrent - 1) * nFZNeedle * nPixelPerXLine);
                     if (dNew > dGradientEnd && dNew > dGradientEndForCurrentPoint)
                     {
                        TRACE(_T("陡过头了%lf\n"), dNew);

                        ++nToleranceNeedle; //增加允许误差值
                        nTolerancePixelX = nToleranceNeedle * nPixelPerXLine; //允许误差像素数

                        eLoopType = LOOP_BY_TOLERANCE_CHANGE;
                     }
                     else
                     {
                        nFZCountCurrent--;
                        eLoopType = LOOP_BY_ROW_NEEDLE_CHANGE;
                     }
                  }
                  else
                  {
                     nFZCountCurrent--;
                     //eLoopType = LOOP_BY_ROW_NEEDLE_CHANGE;
                     eLoopType = LOOP_BY_ROW_NEEDLE_CHANGE_NO_RETURN_BACKUP;
                  }
               }
               else
               {
                  if (!bOverX && !bOverY)
                  {
                     auto dNew = (double(nRevoCountCurrent + 1) * nPixelPerYLine ) /  (nFZCountCurrent * nFZNeedle * nPixelPerXLine);
                     if (dNew > dGradientEnd && dNew > dGradientEndForCurrentPoint)
                     {
                        TRACE(_T("陡过头了%lf\n"), dNew);

                        ++nToleranceNeedle; //增加允许误差值
                        nTolerancePixelX = nToleranceNeedle * nPixelPerXLine; //允许误差像素数

                        eLoopType = LOOP_BY_TOLERANCE_CHANGE;
                     }
                     else
                     {
                        ++nRevoCountCurrent;
                        eLoopType = LOOP_BY_ROW_NEEDLE_CHANGE;
                     }
                  }
                  else
                  {
                     break;
                  }
               }
            }
         }
      }

      //再画剩下的部分
      Arc.m_nPart1 = nCurRevolutionRemain;
      TRACE(_T("nCurRevolutionRemain %d\n"), nCurRevolutionRemain);
      TRACE(_T("nNeedleRemain + nFZNeedle %d\n"), nNeedleRemain + nFZNeedle);
      Arc.m_nPart2 = nNeedleRemain + nFZNeedle; //+nFZNeedle 补上分针数 观察了易佳的做法，最后至少要有1次收针，不能平摇，也不能倒退
      Arc.m_nPart3 = 1;
      vecTempArcItemsExt.push_back(Arc);

      PrintAll(vecTempArcItemsExt);

      //合并同样的段
      CombineSameSection(&vecTempArcItemsExt, &vecTempArcItems);
   }

   pvecArcItems->swap(vecTempArcItems);
   return TRUE;
}

//尽力模拟
//point 贝塞尔曲线 起始点 控制点 结束点
//nNeedle 希望一般的收针数，通常是2
//bReduceFirst 先收
//pvecArcItems 返回结果，转，针，次，不会超过8段
BOOL funcCalcArc3(CPoint point[4],  int nTotalNeedle, int nTotalRevolution, int nTolerance,
   int nFZNeedle, BOOL bReduceFirst, int nSegLimit, std::vector<CArcItem> *pvecArcItems)
{
   if(point[3].y>point[0].y)
   {
      CPoint tempPt=point[0];
      point[0]=point[3];
      point[3]=tempPt;
   }
   if(point[3].x<point[0].x)
   {
      point[1].x=point[0].x+(point[0].x-point[1].x);
      point[2].x=point[0].x+(point[0].x-point[2].x);
      point[3].x=point[0].x+(point[0].x-point[3].x);
   }
   point[1].Offset(-CPoint(point[0].x,0));
   point[2].Offset(-CPoint(point[0].x,0));
   point[3].Offset(-CPoint(point[0].x,0));
   point[0].x=0;

   point[0].Offset(-CPoint(0,point[3].y));
   point[1].Offset(-CPoint(0,point[3].y));
   point[2].Offset(-CPoint(0,point[3].y));
   point[3].y=0;
   //int n=50;
   int n = 1;
   point[0]=CPoint(point[0].x*n,point[0].y*n);
   point[1]=CPoint(point[1].x*n,point[1].y*n);
   point[2]=CPoint(point[2].x*n,point[2].y*n);
   point[3]=CPoint(point[3].x*n,point[3].y*n);
   int nModY = point[0].y % nTotalRevolution;
   if (nModY > 0)
   {
      int nYOld = point[0].y;
      point[0].y -= nModY;
      point[1].y = point[1].y * point[0].y / nYOld;
      point[2].y = point[1].y;
   }
   int nModX = point[3].x % nTotalNeedle;
   if (nModX > 0)
   {
      int nXOld = point[3].x;
      point[3].x -= nModX;
      point[1].x = point[1].x * point[3].x / nXOld;
      point[2].x = point[1].x;
   }


   //int nMinX = INT_MAX;
   //int nMaxX = INT_MIN;
   //int nMinY = INT_MAX;
   //int nMaxY = INT_MIN;

   ////求出最大最小XY值
   //for (int i = 0; i < 4; ++i)
   //{
   //   if (point[i].x > nMaxX)
   //      nMaxX = point[i].x;
   //   if (point[i].y > nMaxY)
   //      nMaxY = point[i].y;
   //   if (point[i].x < nMinX)
   //      nMinX = point[i].x;
   //   if (point[i].y < nMinY)
   //      nMinY = point[i].y;
   //}

   //////////////////////////////////////////////////////////
   //BOOL funcCalcArc3(CPoint point[4],  int nTotalNeedle, int nTotalRevolution, int nTolerance,
   //   int nFZNeedle, BOOL bReduceFirst, int nSegLimit, std::vector<CArcItem> *pvecArcItems)

   //    funcCalcArc3Org(point,  nTotalNeedle, nTotalRevolution, nTolerance,
   //       nFZNeedle, bReduceFirst, nSegLimit, vecArcItemsTable, pvecArcItems);
   if (nSegLimit == 0)
   {
      std::vector<CArcItem> vecArcItemsTable;
      funcCalcArc3Org(point,  nTotalNeedle, nTotalRevolution, nTolerance,
         nFZNeedle, bReduceFirst, pvecArcItems);
   }
   else
   {
      std::vector<CArcItem> vecArcItemsTable;
      funcCalcArc3Org(point,  nTotalNeedle, nTotalRevolution, nTolerance,
         nFZNeedle, bReduceFirst, &vecArcItemsTable);
      if (vecArcItemsTable.size() <= nSegLimit)
      {
         pvecArcItems->swap(vecArcItemsTable);
         return TRUE;
      }

      int nRevLeave = 0;
      int nNeedleLeave = 0;

      auto &BackItem = vecArcItemsTable.back();
      if (BackItem.m_nPart3 == 1) //最后一个可能本来就是无奈补上去的，优先去除
      {
         nRevLeave += BackItem.m_nPart1;
         nNeedleLeave += BackItem.m_nPart2;
         vecArcItemsTable.pop_back();
      }

      BOOL bLoop = TRUE;
      if (vecArcItemsTable.size() < nSegLimit)
      {
         ASSERT(0);
         bLoop = FALSE;
      }
      else if (vecArcItemsTable.size() == nSegLimit && (nRevLeave == 0 || nNeedleLeave == 0)) //可合并
      {
         ASSERT(0);
         bLoop = FALSE;
      }

      while (bLoop) // 段数减小到最大段数减1，然后会补上一段
      {
         double dMinLen = INT_MAX;
         int nMaxIndex = -1;
         for (int i = 0; i < vecArcItemsTable.size(); ++i)
         {
            double dLen = sqrt(double(vecArcItemsTable[i].m_nPart1 * vecArcItemsTable[i].m_nPart1
               + vecArcItemsTable[i].m_nPart2 * vecArcItemsTable[i].m_nPart2))
               * vecArcItemsTable[i].m_nPart3;
            if (nMaxIndex == -1 || dLen < dMinLen)
            {
               dMinLen = dLen;
               nMaxIndex = i;
            }
         }
         auto Iter = vecArcItemsTable.begin();
         Iter += nMaxIndex;
         nRevLeave += Iter->m_nPart1 * Iter->m_nPart3;
         nNeedleLeave += Iter->m_nPart2 * Iter->m_nPart3;

         if (nMaxIndex > 0)
         {
            while (nRevLeave - vecArcItemsTable[nMaxIndex - 1].m_nPart1 >= 0
               && nNeedleLeave - vecArcItemsTable[nMaxIndex - 1].m_nPart2 >= 0)
            {
               ++vecArcItemsTable[nMaxIndex - 1].m_nPart3;

               nRevLeave -= vecArcItemsTable[nMaxIndex - 1].m_nPart1;
               nNeedleLeave -= vecArcItemsTable[nMaxIndex - 1].m_nPart2;
            }
         }

         if (nMaxIndex < vecArcItemsTable.size() - 1)
         {
            while (nRevLeave - vecArcItemsTable[nMaxIndex + 1].m_nPart1 >= 0
               && nNeedleLeave - vecArcItemsTable[nMaxIndex + 1].m_nPart2 >= 0)
            {
               ++vecArcItemsTable[nMaxIndex + 1].m_nPart3;

               nRevLeave -= vecArcItemsTable[nMaxIndex + 1].m_nPart1;
               nNeedleLeave -= vecArcItemsTable[nMaxIndex + 1].m_nPart2;
            }
         }

         vecArcItemsTable.erase(Iter);

         bLoop = TRUE;
         if (vecArcItemsTable.size() < nSegLimit)
         {
            //ASSERT(0);
            bLoop = FALSE;
         }
         else if (vecArcItemsTable.size() == nSegLimit) //有可能可合并
         {
            //ASSERT(0);
            if ((nRevLeave == 0 && nNeedleLeave == 0))
            {
               bLoop = FALSE;
            }
            else if (nRevLeave != 0 && nNeedleLeave == 0)
            {
               if (vecArcItemsTable.front().m_nPart1 > vecArcItemsTable.back().m_nPart1)
               {
                  if (vecArcItemsTable.front().m_nPart3 == 1)
                  {
                     vecArcItemsTable.front().m_nPart1 += nRevLeave;
                     nRevLeave = 0;
                     bLoop = FALSE;
                  }
               }
               else
               {
                  if (vecArcItemsTable.back().m_nPart3 == 1)
                  {
                     vecArcItemsTable.back().m_nPart1 += nRevLeave;
                     nRevLeave = 0;
                     bLoop = FALSE;
                  }
               }
            }
            else if (nRevLeave == 0 && nNeedleLeave != 0)
            {
               if (vecArcItemsTable.front().m_nPart2 > vecArcItemsTable.back().m_nPart2)
               {
                  if (vecArcItemsTable.front().m_nPart3 == 1)
                  {
                     vecArcItemsTable.front().m_nPart2 += nNeedleLeave;
                     nNeedleLeave = 0;
                     bLoop = FALSE;
                  }
               }
               else
               {
                  if (vecArcItemsTable.back().m_nPart3 == 1)
                  {
                     vecArcItemsTable.back().m_nPart2 += nNeedleLeave;
                     nNeedleLeave = 0;
                     bLoop = FALSE;
                  }
               }
            }
         }
      }

      if (nRevLeave == 0 || nNeedleLeave == 0)
      {
         if (nRevLeave == 0 && nNeedleLeave == 0)
         {
            ; //消失
         }
         else if (nRevLeave != 0)
         {
            if (vecArcItemsTable.front().m_nPart1 > vecArcItemsTable.back().m_nPart1)
            {
               if (vecArcItemsTable.front().m_nPart3 > 1)
               {
                  vecArcItemsTable.front().m_nPart3--;
                  auto NewItem = vecArcItemsTable.front();
                  NewItem.m_nPart3 = 1;
                  NewItem.m_nPart1 += nRevLeave;
                  vecArcItemsTable.insert(vecArcItemsTable.begin(), NewItem);
               }
               else
               {
                  vecArcItemsTable.front().m_nPart1 += nRevLeave;
               }

               //vecArcItemsTable.front().m_nPart1 += nRevLeave;
            }
            else
            {
               //vecArcItemsTable.back().m_nPart1 += nRevLeave;
               if (vecArcItemsTable.back().m_nPart3 > 1)
               {
                  vecArcItemsTable.back().m_nPart3--;
                  auto NewItem = vecArcItemsTable.back();
                  NewItem.m_nPart3 = 1;
                  NewItem.m_nPart1 += nRevLeave;
                  vecArcItemsTable.insert(vecArcItemsTable.end(), NewItem);
               }
               else
               {
                  vecArcItemsTable.back().m_nPart1 += nRevLeave;
               }
            }
         }
         else if (nNeedleLeave != 0)
         {
            if (vecArcItemsTable.front().m_nPart2 > vecArcItemsTable.back().m_nPart2)
            {
               if (vecArcItemsTable.front().m_nPart3 > 1)
               {
                  vecArcItemsTable.front().m_nPart3--;
                  auto NewItem = vecArcItemsTable.front();
                  NewItem.m_nPart3 = 1;
                  NewItem.m_nPart2 += nNeedleLeave;
                  vecArcItemsTable.insert(vecArcItemsTable.begin(), NewItem);
               }
               else
               {
                  vecArcItemsTable.front().m_nPart2 += nNeedleLeave;
               }
            }
            else
            {
               //vecArcItemsTable.back().m_nPart2 += nNeedleLeave;

               if (vecArcItemsTable.back().m_nPart3 > 1)
               {
                  vecArcItemsTable.back().m_nPart3--;
                  auto NewItem = vecArcItemsTable.back();
                  NewItem.m_nPart3 = 1;
                  NewItem.m_nPart2 += nNeedleLeave;
                  vecArcItemsTable.insert(vecArcItemsTable.end(), NewItem);
               }
               else
               {
                  vecArcItemsTable.back().m_nPart2 += nNeedleLeave;
               }
            }
         }
      }
      else
      {
         CArcItem ArcItemLast;
         ArcItemLast.m_nPart1 = nRevLeave;
         ArcItemLast.m_nPart2 = nNeedleLeave;
         ArcItemLast.m_nPart3 = 1;

         if (nNeedleLeave != nFZNeedle && nRevLeave != 1)
         {
            vecArcItemsTable.push_back(ArcItemLast); //针数如果比较大，且不是1转，就放后面吧，防止突然中间有铲针
         }
         else
         {
            if (vecArcItemsTable.front().m_nPart1 * vecArcItemsTable.back().m_nPart2 > vecArcItemsTable.back().m_nPart1 * vecArcItemsTable.front().m_nPart2)
            {
               auto funcCompare = [](const CArcItem &Item1, const CArcItem &Item2)
               {
                  return Item1.m_nPart1 * Item2.m_nPart2 > Item2.m_nPart1 * Item1.m_nPart2;
               };
               vecArcItemsTable.push_back(ArcItemLast);
               std::sort(vecArcItemsTable.begin(), vecArcItemsTable.end(), funcCompare);
            }
            else
            {
               auto funcCompare = [](const CArcItem &Item1, const CArcItem &Item2)
               {
                  return Item1.m_nPart1 * Item2.m_nPart2 < Item2.m_nPart1 * Item1.m_nPart2;
               };
               vecArcItemsTable.push_back(ArcItemLast);
               std::sort(vecArcItemsTable.begin(), vecArcItemsTable.end(), funcCompare);
            }
         }
      }

      CombineSameSection(&vecArcItemsTable);

      pvecArcItems->swap(vecArcItemsTable);
   }

   return TRUE;
}

void BeizerDraw(CDC *pDC, CPoint point[4])
{
   std::list<CPoint> ptList;
   //    BezierLine(point, &ptList);
   // 
   // 
   //    BOOL bFirst = TRUE;
   //    for (auto Iter = ptList.begin(); Iter != ptList.end(); ++Iter)
   //    {
   //       POINT & yc = (POINT &)*Iter;
   //       if (bFirst)
   //       {
   //          pDC->MoveTo(yc);
   //       }
   //       else
   //       {
   //          pDC->LineTo(yc);
   //       }
   //       bFirst = FALSE;
   //    }
   BezierLineAllPoint(point, &ptList);

   for (auto Iter = ptList.begin(); Iter != ptList.end(); ++Iter)
   {
      pDC->SetPixel(*Iter, RGB(255,0,0));
      //       POINT & yc = (POINT &)*Iter;
      //       if (bFirst)
      //       {
      //          pDC->MoveTo(yc);
      //       }
      //       else
      //       {
      //          pDC->LineTo(yc);
      //       }
      //       bFirst = FALSE;
   }


   //    POINT points[4];
   //    points[0] = point[0];
   //    points[1] = point[1];
   //    points[2] = point[2];
   //    points[3] = point[3];
   // 
   //    pDC->PolyBezier(points, 4);
}

void CBazierDrawDlg::OnPaint()
{
   if (IsIconic())
   {
      CPaintDC dc(this); // 用于绘制的设备上下文

      SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

      // 使图标在工作区矩形中居中
      int cxIcon = GetSystemMetrics(SM_CXICON);
      int cyIcon = GetSystemMetrics(SM_CYICON);
      CRect rect;
      GetClientRect(&rect);
      int x = (rect.Width() - cxIcon + 1) / 2;
      int y = (rect.Height() - cyIcon + 1) / 2;

      // 绘制图标
      dc.DrawIcon(x, y, m_hIcon);
   }
   else
   {
      //CDialogEx::OnPaint();

      int nPixPerSquare = 5;
      CString strPixperSquare;
      m_editPixelPerSquare.GetWindowText(strPixperSquare);
      nPixPerSquare = std::wcstol(strPixperSquare, NULL, 10);

      CString strPixperSquareY;
      m_editPixelPerY.GetWindowText(strPixperSquareY);

      int nPixPerSquareY = 5;
      nPixPerSquareY = std::wcstol(strPixperSquareY, NULL, 10);

      int nSegLimit = 0;

      BOOL bLimit = m_chkSegLimit.GetCheck();
      if (bLimit)
      {
         CString sLimit;
         m_editSegLimit.GetWindowText(sLimit);
         nSegLimit = std::wcstol(sLimit, NULL, 10);
      }

      if (m_chkFixPos.GetCheck())
      {
         CString sX;
         m_editFixX.GetWindowText(sX);
         int nX = std::wcstol(sX, NULL, 10);
         CString sY;
         m_editFixY.GetWindowText(sY);
         int nY = std::wcstol(sY, NULL, 10);
         m_ptMiddlePoint = CPoint(nX, nY);
      }

      CPaintDC dc(this); // 用于绘制的设备上下文



      CPen pen;
      //       CBrush brush;
      //       brush.CreateSolidBrush(RGB(0,0,0));
      pen.CreatePen(PS_SOLID, 1, RGB(0,0,0));
      dc.SelectObject(&pen);

      CPoint point2[4];

      int nTotalNeedle = 76;
      int nTotalRevolution = 63;

      CString strTotalNeedle;
      m_editTotalNeedle.GetWindowText(strTotalNeedle);
      nTotalNeedle = std::wcstol(strTotalNeedle, NULL, 10);

      CString strTotalRevolution;
      m_editTotalRevolution.GetWindowText(strTotalRevolution);
      nTotalRevolution = std::wcstol(strTotalRevolution, NULL, 10);

      CString strTolerance;
      m_editTolerance.GetWindowText(strTolerance);
      int nTolerance = std::wcstol(strTolerance, NULL, 10);

      //tmpduchen
      //m_ptMiddlePoint = CPoint(364, 299);
      //m_ptMiddlePoint = CPoint(268, 464);

      //m_ptMiddlePoint = CPoint(358, 212);

      //m_ptMiddlePoint = CPoint(219, 290); //斜着上去了

      // m_ptMiddlePoint = CPoint(321, 223);
      //m_ptMiddlePoint = CPoint(218, 304);
      //m_ptMiddlePoint = CPoint(61, 104);
      //m_ptMiddlePoint = CPoint(187, 217);

      //m_ptMiddlePoint = CPoint(224, 389);
      enum
      {
         INIT_X = 100,
         INIT_Y = 100,
      };

      point2[0] = CPoint(INIT_X, INIT_Y + nTotalRevolution * nPixPerSquareY);
      point2[1] = m_ptMiddlePoint;
      point2[2] = m_ptMiddlePoint;
      point2[3] = CPoint(INIT_X + nTotalNeedle * nPixPerSquare, INIT_Y);

      int nArcFZ = 2;

      CString strFZCount;
      m_editFZCount.GetWindowText(strFZCount);
      nArcFZ = std::wcstol(strFZCount, NULL, 10);




      //tmpduchen
      //point2[0].x = 1090;
      //point2[1].x = 1108;
      //point2[2].x = 1108;
      //point2[3].x = 1149;
      //point2[0].y = 258;
      //point2[1].y = 306;
      //point2[2].y = 306;
      //point2[3].y = 323;
      //nTotalNeedle = 38;
      //nTotalRevolution = 31;
      //tmpduchen end


      double dPixelPerNeedle = (double)(point2[3].x - point2[0].x) / nTotalNeedle;
      double dPixelPerRevolution = (double)(point2[0].y - point2[3].y) / nTotalRevolution;

      //画网格线
      {
         CPen penB(PS_SOLID, 1, RGB(200, 200, 200));
         dc.SaveDC();
         dc.SelectObject(&penB);
         CRect ClientRect;
         GetClientRect(&ClientRect);
         int nClientHeight = ClientRect.Height();
         int nClientWidth = ClientRect.Width();
         for (double dY = INIT_Y; dY < nClientHeight; dY += dPixelPerRevolution)
         {
            dc.MoveTo(INIT_X, (int)dY);
            dc.LineTo(nClientWidth, (int)dY);
         }
         for (double dX = INIT_X; dX < nClientWidth; dX += dPixelPerNeedle)
         {
            dc.MoveTo(dX, INIT_Y);
            dc.LineTo(dX, nClientHeight);
         }
         dc.RestoreDC(-1);
      }

      CPen penB(PS_SOLID, 1, RGB(255, 0, 0));
      dc.SaveDC();
      dc.SelectObject(&penB);
      BeizerDraw(&dc, point2);

      dc.SetPixel(point2[1].x, point2[1].y, RGB(255, 0, 0)); //画辅助点
      dc.SetPixel(point2[2].x, point2[2].y, RGB(255, 0, 0)); //画辅助点

      TCHAR aaa[256] = {0};
      std::swprintf(aaa, _T("%d,%d"), m_ptMiddlePoint.x, m_ptMiddlePoint.y);
      dc.TextOut(500, 500, CString(aaa));

      dc.RestoreDC(-1);

      std::vector<CArcItem> vecArcItems;


      //BOOL bRet = funcCalcArc2(point2, nTotalNeedle, nTotalRevolution, nArcFZ, TRUE, &vecArcItems);

      BOOL bReduceFirst = m_chkReduceFirst.GetCheck();
      TRACE(_T("bReduceFirst %d\n"), bReduceFirst);

      CPoint point3[4];
      for (int i = 0; i < 4; ++i)
      {
         point3[i] = point2[i];
      }
      BOOL bRet = funcCalcArc3(point2, nTotalNeedle, nTotalRevolution, nTolerance, nArcFZ, bReduceFirst, nSegLimit, &vecArcItems);
      for (int i = 0; i < 4; ++i)
      {
         point2[i] = point3[i];
      }

      if(!bRet)
         return;
      CString strLine;
      TRACE(_T("Result\n"));
      for(auto Iter = vecArcItems.rbegin(); Iter != vecArcItems.rend(); ++Iter)
      {
         TRACE(_T("%d-%d-%d\n"), Iter->m_nPart1, Iter->m_nPart2, Iter->m_nPart3);

         strLine.AppendFormat(_T("%d-%d-%d\r\n"), Iter->m_nPart1, Iter->m_nPart2, Iter->m_nPart3);
      }
      TRACE(_T("End\n"));
      m_editResult.SetWindowText(strLine);

      CPoint CurrentPoint = point2[0];
      dc.MoveTo(CurrentPoint);
      if (bReduceFirst && !vecArcItems.empty())
      {
         CurrentPoint.y += (point2[0].y - INIT_Y) / nTotalRevolution * vecArcItems.front().m_nPart1;
      }

      for(auto Iter = vecArcItems.begin(); Iter != vecArcItems.end(); ++Iter)
      {
         //TRACE(_T("%d-%d-%d\n"), Iter->m_nPart1, Iter->m_nPart2, Iter->m_nPart3);
         for (int i = 0; i < Iter->m_nPart3; ++i)
         {
            CurrentPoint.y -= Iter->m_nPart1 * dPixelPerRevolution;
            dc.LineTo(CurrentPoint);
            CurrentPoint.x += Iter->m_nPart2 * dPixelPerNeedle;
            dc.LineTo(CurrentPoint);
         }
      }
      CPen PenDash(PS_DASHDOT, 1, RGB(100, 0, 0));
      auto *pPen = dc.SelectObject(&PenDash);
      dc.MoveTo(point2[0]);
      dc.LineTo(point2[1]);
      dc.LineTo(point2[3]);
      dc.SelectObject(pPen);
   }
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CBazierDrawDlg::OnQueryDragIcon()
{
   return static_cast<HCURSOR>(m_hIcon);
}



void CBazierDrawDlg::OnMouseMove(UINT nFlags, CPoint point)
{
   // TODO: 在此添加消息处理程序代码和/或调用默认值

   if (nFlags & MK_LBUTTON)
   {
      m_ptMiddlePoint = point;
      Invalidate(TRUE);
   }


   CDialogEx::OnMouseMove(nFlags, point);
}


void CBazierDrawDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
   // TODO: 在此添加消息处理程序代码和/或调用默认值
   m_ptMiddlePoint = point;
   Invalidate(TRUE);

   CDialogEx::OnLButtonUp(nFlags, point);
}


void CBazierDrawDlg::OnBnClickedChkReduceFirst()
{
   // TODO: 在此添加控件通知处理程序代码
   Invalidate(TRUE);
}


void CBazierDrawDlg::OnBnClickedChkSegLimit()
{
   // TODO: 在此添加控件通知处理程序代码
   Invalidate(TRUE);
}


void CBazierDrawDlg::OnBnClickedChkFixPos()
{
   // TODO: 在此添加控件通知处理程序代码
   Invalidate(TRUE);
}
