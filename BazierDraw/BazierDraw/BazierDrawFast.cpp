#include "stdafx.h"
#include "BazierDrawFast.h"
#include <list>

#define NEARINTEGER(x) double(int(x+0.5)) 

static void GetLinePoints(int x1, int y1, int x2, int y2, std::list<CPoint> *pPtList)
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

static void BezierLineAllPoint(CPoint* point,std::list<CPoint>* pPtList)
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

CBazierDrawFast::CBazierDrawFast()
{

}

int CBazierDrawFast::funcGetYByX(int x)
{
//    auto Iter = m_mapYByX.find(x);
//    if (Iter != m_mapYByX.end())
//    {
//       return Iter->second;
//    }
//    return 0;
   return m_mapYByX[x];
}

int CBazierDrawFast::funcGetXByY(int y)
{
//    auto Iter = m_mapXByY.find(y);
//    if (Iter != m_mapXByY.end())
//    {
//       return Iter->second;
//    }
//   return 0;
   return m_mapXByY[y];
}

BOOL CBazierDrawFast::Init(CPoint point[4])
{
   m_nMostY = point[0].y;
   m_nMostX = point[3].x;
   std::list<CPoint> lstPoints;
   BezierLineAllPoint(point, &lstPoints);

   m_mapYByX.assign(m_nMostX + 1, 0);
   m_mapXByY.assign(m_nMostY + 1, 0);

   for (auto Iter = lstPoints.begin(); Iter != lstPoints.end(); ++Iter)
   {
      if (Iter->x <= m_nMostX && Iter->x >= 0)
      {
         if (Iter->y > m_nMostY)
         {
            m_mapYByX[Iter->x] = m_nMostY;
         }
         else if (Iter->y >= 0)
         {
            m_mapYByX[Iter->x] = Iter->y;
         }
         else
         {
            m_mapYByX[Iter->x] = 0;
         }
      }

      if (Iter->y <= m_nMostY && Iter->y >= 0)
      {
         if (Iter->x > m_nMostX)
         {
            m_mapXByY[Iter->y] = m_nMostX;
         }
         else if (Iter->x >= 0)
         {
            m_mapXByY[Iter->y] = Iter->x;
         }
         else
         {
            m_mapXByY[Iter->y] = 0;
         }
      }
   }
   return TRUE;
}