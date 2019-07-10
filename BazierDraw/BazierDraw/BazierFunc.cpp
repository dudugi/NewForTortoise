#include "stdafx.h"
#include "BazierFunc.h"

CBazierFunc::CBazierFunc()
{

}

static void BeizerDraw(CDC *pDC, CPoint point[4])
{
  /* pDC->Arc(point[0].x, point[0].y,
      point[1].x, point[1].y,
      point[2].x, point[2].y,
      point[3].x, point[3].y);*/
   POINT points[4];
   points[0] = point[0];
   points[1] = point[1];
   points[2] = point[2];
   points[3] = point[3];

   pDC->PolyBezier(points, 4);
}

int CBazierFunc::funcGetYByX(int x)
{
   int y = m_nMostY;
   for (; y >= 0; --y)
   {
      if (m_vecBytes[y][x] == 1)
      {
         return y;
      }
   }
   return 0;
}

int CBazierFunc::funcGetXByY(int y)
{
   for (int x = 0; x < m_nMostX; ++x)
   {
      if (m_vecBytes[y][x] == 1)
      {
         return x;
      }
   }
   return 0;
}

BOOL CBazierFunc::Init(int nX, int nY, CPoint point[4])
{
   m_nMostY = point[0].y;
   m_nMostX = point[3].x;

   std::vector<BYTE> vecBytesPer(nX); //nX是原本宽度

   std::vector<std::vector<BYTE> > vecBytes(nY + 1, vecBytesPer);
   {
      CDC Memdc; //内存dc
      CBitmap MemBitmap; //位图对象
      BYTE* pBmpBits = NULL;

      {
         Memdc.CreateCompatibleDC(NULL);

         int cb = ((nX + 3) & (-4)) * nY;

         std::vector<BYTE> bufBmpInfo;
         bufBmpInfo.resize(sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD));

         LPBITMAPINFO lpbi = (LPBITMAPINFO)&bufBmpInfo[0];
         lpbi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
         lpbi->bmiHeader.biWidth = nX;
         lpbi->bmiHeader.biHeight = nY;
         lpbi->bmiHeader.biPlanes = 1;
         lpbi->bmiHeader.biBitCount = 8;
         lpbi->bmiHeader.biCompression = BI_RGB;
         lpbi->bmiHeader.biSizeImage = (DWORD)cb;
         lpbi->bmiHeader.biXPelsPerMeter = 0;
         lpbi->bmiHeader.biYPelsPerMeter = 0;
         lpbi->bmiHeader.biClrUsed = 0;
         lpbi->bmiHeader.biClrImportant = 0;
         //CKnitPaletteBase* pPalette = CKnitPaletteSingleton::InstancePalette();
         RGBQUAD tmp;
         tmp.rgbBlue = 255;
         tmp.rgbGreen = 255;
         tmp.rgbRed = 255;
         tmp.rgbReserved = 0;
         std::vector<RGBQUAD> vecRgbQuad(256, tmp);
         //vecRgbQuad[1].rg
         vecRgbQuad[1].rgbBlue = 0;
         vecRgbQuad[1].rgbGreen = 0;
         vecRgbQuad[1].rgbRed = 0;
         vecRgbQuad[1].rgbReserved = 0;

         memcpy(&bufBmpInfo[sizeof(BITMAPINFOHEADER)], vecRgbQuad.data(), sizeof(RGBQUAD)*256);
         HBITMAP hbmp = CreateDIBSection(Memdc.GetSafeHdc(), lpbi, DIB_RGB_COLORS, (void **)&pBmpBits, NULL, 0);
         ASSERT(hbmp);
         MemBitmap.Attach(hbmp);
      }
      Memdc.SaveDC();

      Memdc.SelectObject(&MemBitmap);

      CPen MemPen;
      MemPen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));

      CBrush MemBrush;
      MemBrush.CreateSolidBrush(RGB(255, 255, 255));

      Memdc.SelectObject(&MemPen);
      Memdc.SelectObject(&MemBrush);

      BeizerDraw(&Memdc, point);

      Memdc.RestoreDC(-1);

      int bm_width = (nX + 3) & (-4); 
      int bm_height = nY;

      for (int iy = bm_height - 1; iy >= 0; --iy)
      {
         memcpy(&vecBytes[bm_height - 1 - iy][0], pBmpBits + iy * bm_width, nX);
      }
   }

   m_vecBytes.swap(vecBytes);
   return TRUE;
}