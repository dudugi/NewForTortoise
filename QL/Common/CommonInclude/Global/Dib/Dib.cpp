// Dib.cpp : implementation file
//

#include "stdafx.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <windowsx.h>		// especially for GlobalAllocPtr

#include "Dib.h"
#include <GdiplusImaging.h>
using namespace Gdiplus;


IMPLEMENT_SERIAL(CDib, CObject, 0)

////////////////////////////////////////////////////////////////////////////
CDib::CDib()
{
	m_hDib		= NULL;
	m_hBitmap   = NULL;
	m_pPalette  = NULL;
	m_pBitmap   = NULL;
	m_FloatPoint=CPoint(0,0);//060420
	m_sPZDibName="";
}           
                                      
CDib::~CDib()
{
	Destroy();
	if (m_pBitmap != NULL)
	{
		delete m_pBitmap;
		m_pBitmap = NULL;
	}
	if (m_pPalette != NULL)
	{
		delete m_pPalette;
		m_pPalette = NULL;
	}
}

void CDib::Destroy()
{
	if (m_hDib != NULL)
	{
		DestroyDIB(m_hDib);
		m_hDib = NULL;
	}
}

BOOL CDib::Create(DWORD dwWidth, DWORD dwHeight)
{
	HDIB hDib = CreateDefaultDIB(dwWidth, dwHeight);
	if (! hDib)
		return FALSE;

	Destroy();
	m_hDib = hDib;
	return UpdateInternal();
}

BOOL CDib::Create(DWORD dwWidth, DWORD dwHeight, WORD wBitCount)
{
	HDIB hDib = CreateDIB(dwWidth, dwHeight, wBitCount);
	if (! hDib)
		return FALSE;

	Destroy();
	m_hDib = hDib;
	return UpdateInternal();
}

BOOL CDib::Create(LPBYTE lpDIB)
{
	if (lpDIB == NULL)
		return FALSE;
	
	DWORD dwSize = DIBlockSize(lpDIB);

    HDIB hDib  = GlobalAlloc(GHND, dwSize); 
    // Check that DIB handle is valid 
    if (! hDib) 
        return FALSE; 
 
    LPBYTE lpbi  = (LPBYTE)GlobalLock(hDib); 
	if (! lpbi)
        return FALSE; 
		
	CopyMemory(lpbi, lpDIB, dwSize);
	GlobalUnlock(hDib);

	Destroy();
	m_hDib = hDib;
	return UpdateInternal();
}

BOOL CDib::Create(LPBYTE lpDIB,
				  WORD  wBitCount)		// bits/pixel 
{
	if (lpDIB == NULL)
		return FALSE;
	if (! Create(lpDIB))
		return FALSE;

	WORD wBits = ((LPBITMAPINFOHEADER)lpDIB)->biBitCount;
	if (wBitCount == wBits)
		return TRUE;

	HDIB hNewDib = ConvertDIBFormat(m_hDib, wBitCount, NULL); 
	if (! hNewDib)
		return FALSE;

	Destroy();
	m_hDib = hNewDib;
	return UpdateInternal();
}

BOOL CDib::Create(HBITMAP hBitmap)		// DIB Section
{
	if (! hBitmap)
        return FALSE; 

	HDIB hDib = DIBSectionToDIB(hBitmap); 
    if (! hDib) 
        return FALSE; 

	Destroy();
	m_hDib = hDib;
	return UpdateInternal();
}

BOOL CDib::Create(HBITMAP hBitmap,		// DIB Section
				  WORD  wBitCount)		// bits/pixel 
{
	HDIB hNewDib;

	if (! hBitmap)
        return FALSE; 

	HDIB hDib = DIBSectionToDIB(hBitmap); 
    if (! hDib) 
        return FALSE; 

	DIBSECTION ds;
	GetObject(hBitmap, sizeof(DIBSECTION), &ds);

	if (wBitCount == ds.dsBmih.biBitCount)
		hNewDib = hDib;
	else
	{
		hNewDib = ConvertDIBFormat(hDib, wBitCount, NULL); 
		// cleanup hDib
		GlobalFree(hDib);
	}
	if (! hNewDib)
		return FALSE;

	Destroy();
	m_hDib = hNewDib;
	return UpdateInternal();
}

BOOL CDib::Create(HBITMAP hBitmap,		// DDB bitmap
			      HPALETTE hPalette)	// DDB palette
{
	if (! hBitmap)
        return FALSE; 

	HDIB hDib = BitmapToDIB(hBitmap, hPalette); 
    if (! hDib) 
        return FALSE; 

	Destroy();
	m_hDib = hDib;
	return UpdateInternal();
}

BOOL CDib::Create(HBITMAP hBitmap,		// DDB bitmap
			      HPALETTE hPalette,	// DDB palette
				  WORD  wBitCount)		// bits/pixel 
{
	if (! hBitmap)
        return FALSE; 

	HDIB hDib = BitmapToDIB(hBitmap, hPalette, wBitCount); 
    if (! hDib) 
        return FALSE; 

	Destroy();
	m_hDib = hDib;
	return UpdateInternal();
}

BOOL CDib::Create(CRect rcScreen)
{
	HDIB hDib = CopyScreenToDIB(rcScreen); 
    if (! hDib) 
        return FALSE; 

	Destroy();
	m_hDib = hDib;
	return UpdateInternal();
}

BOOL CDib::Create(HWND hWnd, WORD fPrintArea)
{
	HDIB hDib = CopyWindowToDIB(hWnd, fPrintArea); 
    if (! hDib) 
        return FALSE; 

	Destroy();
	m_hDib = hDib;
	return UpdateInternal();
}

BOOL CDib::Create(HWND hWnd, CRect rcClientArea)
{
	HDIB hDib = CopyClientRectToDIB(hWnd, rcClientArea); 
    if (! hDib) 
        return FALSE; 

	Destroy();
	m_hDib = hDib;
	return UpdateInternal();
}
BOOL CDib::CutRect(CRect rc)
{
	HDIB hNewDib = CutDIB(m_hDib, rc);
	if (! hNewDib)
		return FALSE;

	// set to m_hDib
	Destroy();
	m_hDib = hNewDib;

	// return
	return UpdateInternal();
}

BOOL CDib::ConvertFormat(WORD wBitCount)
{
	if (IsEmpty())
		return FALSE;

	if (GetBitCount() == wBitCount)
		return TRUE;

	HDIB hNewDib = ConvertDIBFormat(m_hDib, wBitCount, NULL); 
	if (! hNewDib)
		return FALSE;

	Destroy();
	m_hDib = hNewDib;
	return UpdateInternal();
}
HDIB CDib::CopyRect(CRect rc)
{
	return CropDIB(m_hDib, rc);
}
void CDib::CopyFromDib(CDib* pDib,CRect SrcRect,CRect DstRect)
{
 	int width = GetWidth();
	int height = GetHeight();
	DWORD dwBytes = GetWidthBytes();
  	int bit = GetBitCount()/8;
	LPBYTE pImage = GetBitsPtr();


 	int width2 = pDib->GetWidth();
	int height2 = pDib->GetHeight();
	DWORD dwBytes2 = pDib->GetWidthBytes();
  	int bit2 = pDib->GetBitCount()/8;
	LPBYTE pImage2 = pDib->GetBitsPtr();
	if(SrcRect.Width()!=DstRect.Width()||SrcRect.Height()!=DstRect.Height()||bit!=bit2)return;


	for(int j=DstRect.top;j<DstRect.bottom;j++)
	{
		if(j==height)continue;
		LPBYTE pImaged = pImage + (height - 1-j)* dwBytes+DstRect.left*bit;
		LPBYTE pImages=pImage2 + (height2 - 1-(j-DstRect.top+SrcRect.top))*dwBytes2+SrcRect.left*bit;
		for(int i=DstRect.left;i<DstRect.right;i++)
		{	
			if(i==width)continue;
			if(bit==3)
			{
				pImaged[2] = pImages[2];
				pImaged[1] = pImages[1];
			}
			pImaged[0] = pImages[0];
			pImages+=bit;
			pImaged+=bit;
		}
	}
}
void CDib::MirrorImage(CRect MirrorRect, BOOL MirrorH, BOOL MirrorV)
{
	if(MirrorRect.IsRectEmpty())return;
	int dwSize=GetWidthBytes()*GetHeight();
	LPBYTE psrcImage=GetBitsPtr();
	LPBYTE pBkImage=new BYTE[dwSize];
	memcpy(pBkImage,psrcImage,dwSize);
	int srcheight=GetHeight();
	int srcwidth=GetWidth();
	int height=MirrorRect.Height();
	int width=MirrorRect.Width();
	int widthbyte=GetWidthBytes();
	int bit=GetBitCount()/8;


	if(MirrorH&&MirrorV)
	{
		LPBYTE pImagetemp1,pImagetemp2;
		for(int i=MirrorRect.top;i<MirrorRect.bottom;i++)
		{
			pImagetemp1=psrcImage+(srcheight-i-1)*widthbyte+MirrorRect.left*bit;
			pImagetemp2=pBkImage+(srcheight-(height-(i-MirrorRect.top)-1+MirrorRect.top)-1)*widthbyte+(MirrorRect.right-1)*bit;
			for(int f=MirrorRect.left;f<MirrorRect.right;f++)
			{
				pImagetemp1[0]=pImagetemp2[0];
				pImagetemp1[1]=pImagetemp2[1];
				pImagetemp1[2]=pImagetemp2[2];
				pImagetemp1+=bit;
				pImagetemp2-=bit;
			}
		}
	}
	else if(MirrorH)
	{
		LPBYTE pImagetemp1,pImagetemp2;
		for(int i=MirrorRect.top;i<MirrorRect.bottom;i++)
		{
			pImagetemp1=psrcImage+(srcheight-i-1)*widthbyte+MirrorRect.left*bit;
			pImagetemp2=pBkImage+(srcheight-i-1)*widthbyte+(MirrorRect.right-1)*bit;
			for(int f=MirrorRect.left;f<MirrorRect.right;f++)
			{
				pImagetemp1[0]=pImagetemp2[0];
				pImagetemp1[1]=pImagetemp2[1];
				pImagetemp1[2]=pImagetemp2[2];
				pImagetemp1+=bit;
				pImagetemp2-=bit;
			}
		}
	}
	else if(MirrorV)
	{
		LPBYTE pImagetemp1,pImagetemp2;
		for(int i=MirrorRect.top;i<MirrorRect.bottom;i++)
		{
			pImagetemp1=psrcImage+(srcheight-i-1)*widthbyte+MirrorRect.left*bit;
			pImagetemp2=pBkImage+(srcheight-(height-(i-MirrorRect.top)-1+MirrorRect.top)-1)*widthbyte+MirrorRect.left*bit;
			for(int f=MirrorRect.left;f<MirrorRect.right;f++)
			{
				pImagetemp1[0]=pImagetemp2[0];
				pImagetemp1[1]=pImagetemp2[1];
				pImagetemp1[2]=pImagetemp2[2];
				pImagetemp1+=bit;
				pImagetemp2+=bit;
			}
		}
	}
	UpdateInternal();
	delete pBkImage;
}

BOOL CDib::MergeDib(HDIB hDib, CPoint ptTopLeft)
{
	POINT pt;
	pt.x = ptTopLeft.x;
	pt.y = ptTopLeft.y;
	HDIB hNewDib = MergeDIB(m_hDib, hDib, pt);
	if (! hNewDib)
		return FALSE;

	// set to m_hDib
	Destroy();
	m_hDib = hNewDib;

	// return
	return UpdateInternal();
}

void CDib::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	ar.Flush();
	if (ar.IsStoring())
	{
		Write(ar.GetFile());
	}
    else
    {
   		Read(ar.GetFile());
    }
}

BOOL CDib::Load(UINT uIDS, LPCTSTR lpszDibType)
{ 
	LPCTSTR lpszDibRes = MAKEINTRESOURCE(uIDS);

	return Load(lpszDibRes, lpszDibType);
}

BOOL CDib::Load(LPCTSTR lpszDibRes, LPCTSTR lpszDibType)
{                                
	HINSTANCE hInst = AfxGetInstanceHandle();
	HRSRC   hRes    = ::FindResource(hInst, lpszDibRes, lpszDibType);
	HGLOBAL hData   = ::LoadResource(hInst, hRes);

	// if resource ok?
	if (hRes == NULL || hData == NULL)
		return FALSE;

	// get resource buffer
	LPBYTE lpBuf = (LPBYTE)::LockResource(hData);
	// is DIB ?
	if (((LPBITMAPFILEHEADER)lpBuf)->bfType != DIB_HEADER_MARKER/*"BM"*/)
		return FALSE;

	// use this buffer to create CDib
	LPBYTE lpDIB = lpBuf + sizeof(BITMAPFILEHEADER);
	return Create(lpDIB);
}

BOOL CDib::Load(LPCTSTR lpszDibFile)
{                                
	TRY
	{
		CFile file(lpszDibFile, CFile::modeRead|CFile::shareDenyNone);

		if (! Read(&file))
			return FALSE;
	}
	CATCH (CException, e)
	{
		return FALSE;
	}
	END_CATCH

	return TRUE;
}     

int CDib::GetEncoderClsid(const WCHAR* format, CLSID* pClsid)  
{  
	UINT  num = 0;          // number of image encoders  
	UINT  size = 0;         // size of the image encoder array in bytes  

	ImageCodecInfo* pImageCodecInfo = NULL;  

	//获取GDI+支持的图像格式编码器种类数以及ImageCodecInfo数组的存放大小  
	GetImageEncodersSize(&num, &size);  
	if(size == 0)  
		return -1;  // Failure  

	//为ImageCodecInfo数组分配足额空间  
	pImageCodecInfo = (ImageCodecInfo*)(malloc(size));  
	if(pImageCodecInfo == NULL)  
		return -1;  // Failure  

	//获取所有的图像编码器信息  
	GetImageEncoders(num, size, pImageCodecInfo);  

	//查找符合的图像编码器的Clsid  
	for(UINT j = 0; j < num; ++j)  
	{  
		if( wcscmp(pImageCodecInfo[j].MimeType, format) == 0 )  
		{  
			*pClsid = pImageCodecInfo[j].Clsid;  
			free(pImageCodecInfo);  
			return j;  // Success  
		}      
	}  

	//释放内存  
	free(pImageCodecInfo);  
	return -1;  // Failure  
}

BOOL CDib::Save(LPCTSTR lpszDibFile,const WCHAR* format)
{
	BOOL bRet = FALSE;
	if (NULL != m_hBitmap)
	{
		CLSID encoderClsid;
		Bitmap bmp(m_hBitmap,NULL);
		int nResult = GetEncoderClsid(format,&encoderClsid);
		if(nResult >= 0)
		{
			//保存图片
			if(Gdiplus::Ok == bmp.Save(lpszDibFile,&encoderClsid))
			{
				bRet = TRUE;
			}
		}
	}
	
	return bRet;
}

BOOL CDib::Save(LPCTSTR lpszDibFile,BOOL bJPGForamt/* = FALSE*/)
{
	if(bJPGForamt)
	{//GDI+
		if (NULL != m_hBitmap)
		{
			CLSID encoderClsid;
			Bitmap bmp(m_hBitmap,NULL);
			int nResult = GetEncoderClsid(_TEXT("image/jpeg"),&encoderClsid);
			if(nResult >= 0)
			{
				//保存图片
				bmp.Save(lpszDibFile,&encoderClsid);
			}
			else
			{
				return FALSE;
			}
		}
		else
		{
			return FALSE;
		}
	}
	else//GDI+_end
	{
		TRY
		{
			CFile file(lpszDibFile, CFile::modeCreate|CFile::modeWrite);

			if (! Write(&file))
				return FALSE;
		}
		CATCH (CException, e)
		{
			return FALSE;
		}
		END_CATCH
	}

	return TRUE;
}

BOOL CDib::LoadByGdiplus(LPCTSTR lpszDibFile)
{
   BOOL bRet = FALSE;

	CT2CW strFilePath(lpszDibFile);
	Bitmap bmp(strFilePath,FALSE);
	HBITMAP hBitmap;
	Status sts = bmp.GetHBITMAP(Color(0,255,255,255),&hBitmap);//ARGB
   if (sts != Ok)
      return FALSE;

	bRet = Create(hBitmap,24);

   DeleteObject( hBitmap );

   return bRet;
}

BOOL CDib::LoadByGdiplus_AdaptiveDirection(LPCTSTR lpszDibFile)
{
   BOOL bRet = FALSE;

   CT2CW strFilePath(lpszDibFile);
   Bitmap bmp(strFilePath,FALSE);

   HBITMAP hBitmap;
   Status sts = bmp.GetHBITMAP(Color(0,255,255,255),&hBitmap);//ARGB
   if (sts != Ok)
      return FALSE;

   bRet = Create(hBitmap,24);
   DeleteObject( hBitmap );

   //https://docs.microsoft.com/zh-cn/windows/desktop/gdiplus/-gdiplus-reading-and-writing-metadata-use
   //获取图片方向的信息 wangzl 2019-2-12
   UINT  size = 0;
   UINT  count = 0;
   bmp.GetPropertySize(&size, &count);
   PropertyItem* pPropBuffer =(PropertyItem*)malloc(size);
   bmp.GetAllPropertyItems(size, count, pPropBuffer);

   for(UINT j = 0; j < count; ++j)
   {
      if (PropertyTagOrientation == pPropBuffer[j].id)
      {
         void * pValue = pPropBuffer[j].value;
         unsigned short nValue = *(unsigned short *)pValue;

         switch (nValue)
         {
            //以下所有旋转都是顺时针旋转
         case 1: //"Top, left side (Horizontal / normal)"; 正常
            {
               //正常不处理
               break;
            }
         case 2: //"Top, right side (Mirror horizontal)"; 水平镜像
            {
               CRect rtMirror;
               rtMirror = GetDibRect();
               MirrorImage(rtMirror, TRUE, FALSE);//水平镜像
               break;
            }
         case 3: //"Bottom, right side (Rotate 180)"; 旋转180
            {
               Rotate180();
               break;
            }
         case 4: //"Bottom, left side (Mirror vertical)"; 垂直镜像
            {
               CRect rtMirror;
               rtMirror = GetDibRect();
               MirrorImage(rtMirror, FALSE, TRUE);//垂直镜像
               break;
            }
         case 5: //"Left side, top (Mirror horizontal and rotate 270 CW)"; 水平镜像并旋转270度
            {
               Rotate90();
               CRect rtMirror;
               rtMirror = GetDibRect();
               MirrorImage(rtMirror, TRUE, FALSE);//水平镜像
               break;
            }
         case 6: //"Right side, top (Rotate 90 CW)"; 旋转90度
            {
               Rotate270();
               break;
            }
         case 7: //"Right side, bottom (Mirror horizontal and rotate 90 CW)"; 水平镜像并旋转90度
            {
               Rotate270();
               CRect rtMirror;
               rtMirror = GetDibRect();
               MirrorImage(rtMirror, TRUE, FALSE);//水平镜像
               break;
            }
         case 8: //"Left side, bottom (Rotate 270 CW)"; 旋转270度
            {
               Rotate90();
               break;
            }
         default:
            break;
         }
         break;
      }
   }
   free(pPropBuffer);

   return bRet;
}

CDib* CDib::LimitDibSize(int nMaxSize)
{
	CDib* pDib1=NULL;
	int h1=GetHeight();
	int w1=GetWidth();
	double ratio=max(h1/double(nMaxSize),w1/double(nMaxSize));

	if(ratio>1)
	{
		int h2=	int(h1/ratio);
		int w2=	int(w1/ratio);
		HDIB hDib = ChangeDIBSize(m_hDib,w2,h2);
		if(hDib==NULL)return NULL;
		pDib1=new CDib();
		pDib1->Create(w2,h2);
		pDib1->Attach(hDib);
	}
	return pDib1;
}
BOOL CDib::Read(CFile *pFile)
{
	WaitCursorBegin();

	LPBITMAPINFOHEADER lpbi;
	DWORD dwSize;
	TRY
	{
		// read DIB file header
		BITMAPFILEHEADER bmfHdr;
		pFile->Read(&bmfHdr, sizeof(BITMAPFILEHEADER));
		// is DIB file?
		if (bmfHdr.bfType != DIB_HEADER_MARKER/*"BM"*/)
		{
			WaitCursorEnd();
			return FALSE;
		}
/*		DWORD dwLength = pFile->GetLength();
		if (bmfHdr.bfSize != dwLength)
			bmfHdr.bfSize = dwLength;
*/
		// read DIB buffer
		dwSize = bmfHdr.bfSize - sizeof(BITMAPFILEHEADER);
		lpbi = (LPBITMAPINFOHEADER)GlobalAllocPtr(GHND, dwSize);
		DWORD dwCount = pFile->Read(lpbi, dwSize);
		// read ok?
		if (dwCount != dwSize)
		{
			GlobalFreePtr(lpbi);
			WaitCursorEnd();
			return FALSE;
		}

		// Check to see that it's a Windows DIB -- an OS/2 DIB would cause 
		// strange problems with the rest of the DIB API since the fields 
		// in the header are different and the color table entries are 
		// smaller. 
		// 
		// If it's not a Windows DIB (e.g. if biSize is wrong), return NULL. 
	    if (lpbi->biSize != sizeof(BITMAPINFOHEADER)) 
		{
			GlobalFreePtr(lpbi);
			WaitCursorEnd();
			return FALSE;
		}
		
		// fill color num item
		int nNumColors = (UINT)lpbi->biClrUsed;
		if (nNumColors == 0) 
		{ 
			// no color table for 24-bit, default size otherwise 
	        if (lpbi->biBitCount != 24) 
		        nNumColors = 1 << lpbi->biBitCount; // standard size table 
		} 
 
		// fill in some default values if they are zero 
	    if (lpbi->biClrUsed == 0) 
		    lpbi->biClrUsed = nNumColors; 
		if (lpbi->biSizeImage == 0) 
			lpbi->biSizeImage = ((((lpbi->biWidth * (DWORD)lpbi->biBitCount) + 31) & ~31) >> 3) * lpbi->biHeight; 
 	}
	CATCH (CException, e)
	{
		GlobalFreePtr(lpbi);
		WaitCursorEnd();
		return FALSE;
	}
	END_CATCH

	// create CDib with DIB buffer
	BOOL bSuccess = Create((LPBYTE)lpbi);
	GlobalFreePtr(lpbi);
	WaitCursorEnd();

	return bSuccess;
}

BOOL CDib::Write(CFile *pFile)
{
	WaitCursorBegin();

    BITMAPFILEHEADER    bmfHdr;     // Header for Bitmap file 
    LPBITMAPINFOHEADER  lpBI;       // Pointer to DIB info structure 
    DWORD               dwDIBSize; 

	// Get a pointer to the DIB memory, the first of which contains 
    // a BITMAPINFO structure 
    lpBI = (LPBITMAPINFOHEADER)GlobalLock(m_hDib); 
    if (!lpBI) 
	{
		GlobalUnlock(m_hDib);
		WaitCursorEnd();
        return FALSE; 
	}
 
    // Check to see if we're dealing with an OS/2 DIB.  If so, don't 
    // save it because our functions aren't written to deal with these 
    // DIBs. 
    if (lpBI->biSize != sizeof(BITMAPINFOHEADER)) 
    { 
        GlobalUnlock(m_hDib); 
		WaitCursorEnd();
        return FALSE; 
    } 
 
    // Fill in the fields of the file header 
 
    // Fill in file type (first 2 bytes must be "BM" for a bitmap) 
 
    bmfHdr.bfType = DIB_HEADER_MARKER;  // "BM" 
 
    // Calculating the size of the DIB is a bit tricky (if we want to 
    // do it right).  The easiest way to do this is to call GlobalSize() 
    // on our global handle, but since the size of our global memory may have 
    // been padded a few bytes, we may end up writing out a few too 
    // many bytes to the file (which may cause problems with some apps, 
    // like HC 3.0). 
    // 
    // So, instead let's calculate the size manually. 
    // 
    // To do this, find size of header plus size of color table.  Since the 
    // first DWORD in both BITMAPINFOHEADER and BITMAPCOREHEADER conains 
    // the size of the structure, let's use this. 
 
    // Partial Calculation 
 
    dwDIBSize = *(LPDWORD)lpBI + PaletteSize((LPBYTE)lpBI);   
 
    // Now calculate the size of the image 
 
    // It's an RLE bitmap, we can't calculate size, so trust the biSizeImage 
    // field 
 
    if ((lpBI->biCompression == BI_RLE8) || (lpBI->biCompression == BI_RLE4)) 
        dwDIBSize += lpBI->biSizeImage; 
    else 
    { 
        DWORD dwBmBitsSize;  // Size of Bitmap Bits only 
 
        // It's not RLE, so size is Width (DWORD aligned) * Height 
 
        dwBmBitsSize = WIDTHBYTES((lpBI->biWidth)*((DWORD)lpBI->biBitCount)) * 
                lpBI->biHeight; 
 
        dwDIBSize += dwBmBitsSize; 
 
        // Now, since we have calculated the correct size, why don't we 
        // fill in the biSizeImage field (this will fix any .BMP files which  
        // have this field incorrect). 
 
        lpBI->biSizeImage = dwBmBitsSize; 
    } 
 
 
    // Calculate the file size by adding the DIB size to sizeof(BITMAPFILEHEADER) 
                    
    bmfHdr.bfSize = dwDIBSize + sizeof(BITMAPFILEHEADER); 
    bmfHdr.bfReserved1 = 0; 
    bmfHdr.bfReserved2 = 0; 
 
    // Now, calculate the offset the actual bitmap bits will be in 
    // the file -- It's the Bitmap file header plus the DIB header, 
    // plus the size of the color table. 
     
    bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + lpBI->biSize + 
            PaletteSize((LPBYTE)lpBI); 
 
 	TRY
	{
	    // Write the file header 
		pFile->Write(&bmfHdr, sizeof(BITMAPFILEHEADER));
		// write DIB buffer
		pFile->Write(lpBI, dwDIBSize);
	}
	CATCH (CException, e)
	{
        GlobalUnlock(m_hDib); 
		WaitCursorEnd();
		return FALSE;
	}
	END_CATCH

	GlobalUnlock(m_hDib); 
	WaitCursorEnd();
	
	return TRUE;
}
void CDib::DrawFloatDib(CDC *pDC,CRect ShowRect, CRect SrcRect, double dScalex, double dScaley)
{
	// src->drawrect
	CDC SrcMemDC;
	CBitmap Srcbm;
	CBitmap* pBmp1;
	SrcMemDC.CreateCompatibleDC(pDC);
	Srcbm.CreateCompatibleBitmap(pDC, SrcRect.Width(), SrcRect.Height());
	pBmp1=SrcMemDC.SelectObject(&Srcbm);
	LPBITMAPINFOHEADER lpBI = (LPBITMAPINFOHEADER)GlobalLock(m_hDib); 
	StretchDIBits(SrcMemDC.GetSafeHdc(),0, 0,SrcRect.Width(), SrcRect.Height(),
			0, 0, GetWidth(),GetHeight(), 
			GetBitsPtr(), (LPBITMAPINFO)lpBI, DIB_RGB_COLORS, SRCCOPY);

	CRect rects=SrcRect;
	rects.IntersectRect(rects,ShowRect);
	rects.OffsetRect(-ShowRect.TopLeft());
	int left=SrcRect.left>ShowRect.left?0:ShowRect.left-SrcRect.left;
	int top=SrcRect.top>ShowRect.top?0:ShowRect.top-SrcRect.top;

	CRect rect = CRect(int((rects.left)*dScalex),int((rects.top)*dScaley)
		,int((rects.right)*dScalex),int((rects.bottom)*dScaley));


//draw rect
//	CPen pen(PS_SOLID, 1, RGB(188,188,188));
//	CPen* pOldPen = pDC->SelectObject(&pen);
//	rect.OffsetRect(1,1);
//	rect.InflateRect(2,2);
//	rect.InflateRect(-2,-2);
//	rect.OffsetRect(-1,-1);
//
	pDC->StretchBlt(rect.left,rect.top,rect.Width(),rect.Height(),&SrcMemDC,left,top,rects.Width(),rects.Height(),SRCCOPY);
	pDC->FrameRect(rect,&CBrush(RGB(200,0,0)));
//	pDC->SelectObject(pOldPen);
	SrcMemDC.SelectObject(&pBmp1);
	SrcMemDC.DeleteDC();
} 
BOOL CDib::Display(CDC* pDC, int xDest, int yDest, int nWidthDest, int nHeightDest, 
 				   int xSrc, int ySrc, DWORD dwRop)
{
	CDC MemDC;
	MemDC.CreateCompatibleDC(pDC);

	CBitmap* pOldBmp = MemDC.SelectObject(m_pBitmap);

	CPalette* pOldPal = pDC->SelectPalette(m_pPalette, TRUE);
    pDC->RealizePalette();

	BOOL bSuccess = pDC->BitBlt( xDest, yDest, 
							nWidthDest, nHeightDest,
						    &MemDC, 
							xSrc, ySrc, 
							dwRop);

	MemDC.SelectObject(pOldBmp);
	pDC->SelectPalette(pOldPal, TRUE);

	return bSuccess;
}

BOOL CDib::Display(CDC * pDC, int xDest, int yDest, int nWidthDest, int nHeightDest, 
				   int xSrc, int ySrc, int nWidthSrc, int nHeightSrc, DWORD dwRop)
{
	CDC MemDC;
	MemDC.CreateCompatibleDC(pDC);

	CBitmap* pOldBmp = MemDC.SelectObject(m_pBitmap);

	CPalette* pOldPal = pDC->SelectPalette(m_pPalette, TRUE);
    pDC->RealizePalette();

	BOOL bSuccess = pDC->StretchBlt( xDest, yDest, 
								nWidthDest, nHeightDest,
						        &MemDC, 
								xSrc, ySrc, 
								nWidthSrc, nHeightSrc, 
								dwRop);

	MemDC.SelectObject(pOldBmp);
	pDC->SelectPalette(pOldPal, TRUE);

	return bSuccess;
}

BOOL CDib::Display(CDC * pDC, int x, int y, DWORD dwRop)
{
	CDC MemDC;
	MemDC.CreateCompatibleDC(pDC);

	CBitmap* pOldBmp = MemDC.SelectObject(m_pBitmap);

	CPalette* pOldPal = pDC->SelectPalette(m_pPalette, TRUE);
    pDC->RealizePalette();

	BOOL bSuccess = pDC->BitBlt(x, y, 
								GetWidth(), GetHeight(),
								&MemDC, 
								0, 0, 
								dwRop);

	MemDC.SelectObject(pOldBmp);
	pDC->SelectPalette(pOldPal, TRUE);

	return bSuccess;
}

BOOL CDib::Display(CDC* pDC, CRect rcDest, CRect rcSrc, DWORD dwRop)
{
	CDC MemDC;
	MemDC.CreateCompatibleDC(pDC);

	CBitmap* pOldBmp = MemDC.SelectObject(m_pBitmap);

	CPalette* pOldPal = pDC->SelectPalette(m_pPalette, TRUE);
    pDC->RealizePalette();

	BOOL bSuccess = pDC->StretchBlt( rcDest.left, rcDest.top, 
								rcDest.Width(), rcDest.Height(),
						        &MemDC, 
								rcSrc.left, rcSrc.top, 
								rcSrc.Width(), rcSrc.Height(),
								dwRop);

	MemDC.SelectObject(pOldBmp);
	pDC->SelectPalette(pOldPal, TRUE);

	return bSuccess;
}

BOOL CDib::Attach(HDIB hDib)
{
	if (hDib == NULL)
		return FALSE;
	
	Destroy();
	m_hDib = hDib;
	return UpdateInternal();
}

HDIB CDib::Detach()
{
	if (m_hDib == NULL)
		return NULL;
	HDIB hDib = m_hDib;
	m_hDib = NULL;
	if (m_pBitmap != NULL)
	{
		delete m_pBitmap;
		m_pBitmap = NULL;
	}
	if (m_pPalette != NULL)
	{
		delete m_pPalette;
		m_pPalette = NULL;
	}
	return hDib;
}

BOOL CDib::BuildBitmap()
{
	if (m_pBitmap != NULL)
	{
		delete m_pBitmap;
		m_pBitmap = NULL;
		m_hBitmap = NULL;
	}
	m_hBitmap = DIBToDIBSection(m_hDib);
	if (m_hBitmap == NULL)
		return FALSE;
	m_pBitmap = new CBitmap;
	m_pBitmap->Attach(m_hBitmap);

	return TRUE;
}

BOOL CDib::BuildPalette()
{
	if (m_pPalette != NULL)
	{
		delete m_pPalette;
		m_pPalette = NULL;
	}
	HPALETTE hPalette = CreateDIBPalette(m_hDib);
	if (hPalette == NULL)
		return FALSE;
	m_pPalette = new CPalette;
	m_pPalette->Attach(hPalette);

	return TRUE;
}

BOOL CDib::UpdateInternal()
{
	BuildPalette();
	return BuildBitmap();
}

CPalette* CDib::GetPalette()
{
	return m_pPalette;
}

CBitmap* CDib::GetBitmap()
{
	return m_pBitmap;
}

BOOL CDib::IsEmpty()
{
	if (m_hDib == NULL)
		return TRUE;

	if (! GlobalLock(m_hDib))
		return TRUE;

	GlobalUnlock(m_hDib);
	return FALSE;
}

DWORD CDib::GetCompression()
{
    LPBITMAPINFOHEADER lpBI = (LPBITMAPINFOHEADER)GlobalLock(m_hDib); 
    if (!lpBI) 
	{
		GlobalUnlock(m_hDib);
        return 0; 
	}
 
	DWORD dwCompression = lpBI->biCompression;
	GlobalUnlock(m_hDib);

	return dwCompression;
}

WORD CDib::GetBitCount()
{
    LPBITMAPINFOHEADER lpBI = (LPBITMAPINFOHEADER)GlobalLock(m_hDib); 
    if (!lpBI) 
	{
		GlobalUnlock(m_hDib);
        return 0; 
	}
 
	WORD wBitCount = lpBI->biBitCount;
	GlobalUnlock(m_hDib);

	return wBitCount;
}

LONG CDib::GetWidth()
{
	// get DIB buffer pointer
    LPBYTE lpDIB = (LPBYTE)GlobalLock(m_hDib); 
	if (! lpDIB)
	{
		GlobalUnlock(m_hDib);
		return 0;
	}

	LONG lWidth = (LONG)DIBWidth(lpDIB);
	GlobalUnlock(m_hDib);

	return lWidth; 
}

LONG CDib::GetHeight()
{
	// get DIB buffer pointer
    LPBYTE lpDIB = (LPBYTE)GlobalLock(m_hDib); 
	if (! lpDIB)
	{
		GlobalUnlock(m_hDib);
		return 0;
	}

	LONG lHeight = (LONG)DIBHeight(lpDIB);
	GlobalUnlock(m_hDib);

	return lHeight; 
}

LONG CDib::GetWidthBytes()
{
	return WIDTHBYTES((GetWidth())*((DWORD)GetBitCount()));
}

COLORREF CDib::GetPixel(LONG x, LONG y)
{
	COLORREF cColor;
	int width=GetWidth();
	int height=GetHeight();
	if (x<0||y<0||x>=width||y>=height)
	{
		return -1;
	}
	switch (GetBitCount())
	{
		case 1 :	if (1<<(7-x%8) & 
						*(BYTE*)(GetBitsPtr()+GetPixelOffset(x, y)))
						cColor = RGB(255,255,255);
					else
						cColor = RGB(0,0,0);
					break;
		case 4 :	
				{
					PALETTEENTRY PaletteColors[16];
					m_pPalette->GetPaletteEntries(0, 16, PaletteColors);
					int nIndex = (*(BYTE*)(GetBitsPtr()+GetPixelOffset(x, y)) & 
								   (x%2 ? 0x0f : 0xf0)) >> (x%2 ? 0 : 4);
					cColor = RGB(PaletteColors[nIndex].peRed,
								 PaletteColors[nIndex].peGreen,
								 PaletteColors[nIndex].peBlue);
				}
					break;
		case 8 :	
				{
					PALETTEENTRY PaletteColors[256];
					m_pPalette->GetPaletteEntries(0, 256, PaletteColors);
					int nIndex = *(BYTE*)(GetBitsPtr()+GetPixelOffset(x, y));
					cColor = RGB(PaletteColors[nIndex].peRed,
								 PaletteColors[nIndex].peGreen,
								 PaletteColors[nIndex].peBlue);
				}
					break;
		default:	cColor = RGB(*(BYTE*)(GetBitsPtr()+GetPixelOffset(x, y)+2),
								 *(BYTE*)(GetBitsPtr()+GetPixelOffset(x, y)+1),
								 *(BYTE*)(GetBitsPtr()+GetPixelOffset(x, y)));
					break;
	}
	return cColor;
}

LONG CDib::GetPixelOffset(LONG x, LONG y)
{
	return (GetHeight()-y-1)*GetWidthBytes()+x*GetBitCount()/8;
}

LPBYTE CDib::GetBitsPtr()
{
    LPBYTE lpDIB = (LPBYTE)GlobalLock(m_hDib); 
    if (! lpDIB) 
	{
		GlobalUnlock(m_hDib);
		return NULL;
	}

	LPBYTE lpData = FindDIBBits(lpDIB);
	GlobalUnlock(m_hDib);

	return lpData;
}

HANDLE CDib::GetHandle()
{
	return m_hDib;
}

WORD CDib::GetColorNumber()
{
    LPBYTE lpBI = (LPBYTE)GlobalLock(m_hDib); 
    if (! lpBI) 
	{
		GlobalUnlock(m_hDib);
		return 0;
	}
 
	WORD wColors = DIBNumColors(lpBI);
	GlobalUnlock(m_hDib);

	return wColors;
}

WORD CDib::GetPaletteSize()
{
    LPBYTE lpBI = (LPBYTE)GlobalLock(m_hDib); 
    if (! lpBI) 
	{
		GlobalUnlock(m_hDib);
		return 0;
	}
 
	WORD wPalSize = PaletteSize(lpBI);
	GlobalUnlock(m_hDib);

	return wPalSize;
}

CDC* CDib::BeginPaint(CDC *pDC)
{
	m_pMemDC = new CDC;
	m_pMemDC->CreateCompatibleDC(pDC);
	if(m_pMemDC->m_hDC==NULL)
		return NULL;
	m_pPaletteTmp = m_pMemDC->SelectPalette(m_pPalette, TRUE);
	m_pMemDC->RealizePalette();
	m_pBitmapTmp = (CBitmap *)m_pMemDC->SelectObject(m_pBitmap);
	return m_pMemDC;
}

void CDib::EndPaint()
{
	m_pMemDC->SelectObject(m_pBitmapTmp);
	m_pMemDC->SelectPalette(m_pPaletteTmp, TRUE);
	delete m_pMemDC;

	Create(m_hBitmap);
}

BOOL CDib::DisplayPalette(CDC* pDC, CRect rc)
{
	return ::DisplayPalette(pDC->GetSafeHdc(), &rc, (HPALETTE)m_pPalette->GetSafeHandle());
}
CDib * CDib::CloneRect(CRect CopyRect)
{
	CopyRect.NormalizeRect();
	if(CopyRect.IsRectEmpty())return NULL;
	HDIB hDib = (HDIB)CropDIB(m_hDib, CopyRect);
	LPBYTE lpDIB = (LPBYTE)GlobalLock(hDib); 
	if (!lpDIB)
	{
		GlobalUnlock(hDib);
		return NULL;
	}
	CDib *pDib=new CDib;
	pDib->Create(lpDIB);
	GlobalUnlock(hDib);
	pDib->m_sPZDibName=m_sPZDibName;
	return pDib;
}
CDib * CDib::Clone()
{
	if (m_hDib == NULL)
		return NULL;

	HDIB hDIB = CopyHandle(m_hDib);
	if (hDIB == NULL)
		return NULL;

	CDib *pDib = new CDib;
	pDib->m_hDib = hDIB;
	pDib->BuildPalette();
   if (!pDib->BuildBitmap())
   {
      delete pDib;
      pDib = NULL;
      return pDib;
   }
	pDib->m_sPZDibName=m_sPZDibName;

	return pDib;
}


int CDib::GetDibFileSize()
{
    LPBITMAPINFOHEADER  lpBI;       // Pointer to DIB info structure 
    DWORD               dwDIBSize; 
	
    lpBI = (LPBITMAPINFOHEADER)GlobalLock(m_hDib); 
    if (!lpBI) 
	{
		GlobalUnlock(m_hDib);
		return FALSE; 
	}
	dwDIBSize = *(LPDWORD)lpBI + PaletteSize((LPBYTE)lpBI);   
	
    if ((lpBI->biCompression == BI_RLE8) || (lpBI->biCompression == BI_RLE4)) 
        dwDIBSize += lpBI->biSizeImage; 
    else 
    { 
        DWORD dwBmBitsSize;  // Size of Bitmap Bits only 
        dwBmBitsSize = WIDTHBYTES((lpBI->biWidth)*((DWORD)lpBI->biBitCount)) * 
			lpBI->biHeight; 
		dwDIBSize += dwBmBitsSize; 
		dwDIBSize += sizeof(BITMAPFILEHEADER);
	} 
	GlobalUnlock(m_hDib); 
	return dwDIBSize;
}
COLORREF CDib::SetColorTableEntry(int uIndex,COLORREF rColor)
{
	if(uIndex > 255||GetBitCount()!=8) return 0;
	LPBITMAPINFOHEADER  lpBI = (LPBITMAPINFOHEADER)GlobalLock(m_hDib); 
	LPRGBQUAD pDibQuad = (LPRGBQUAD)((LPBYTE) lpBI + sizeof(BITMAPINFOHEADER));

	for(int i=0;i< uIndex;i++)
	{
		pDibQuad++;
	}
	COLORREF oldColor;
	oldColor =RGB(pDibQuad->rgbRed,pDibQuad->rgbGreen,pDibQuad->rgbBlue);
	
	pDibQuad->rgbRed =GetRValue(rColor);
	pDibQuad->rgbGreen =GetGValue(rColor);
	pDibQuad->rgbBlue =GetBValue(rColor);
	
	return oldColor;
}

void CDib::PasteRect(CDib *pDib, CRect rect)
{
	if(rect.Width()>GetWidth()||rect.Height()>GetHeight())return;
	if(pDib->GetBitCount()!=GetBitCount())return;
	int SrcWidth=GetWidth();
	int SrcHeight=GetHeight();
	int SrcWidthBytes=GetWidthBytes();
	LPBYTE pSrcImage=GetBitsPtr();

	int DstWidth=pDib->GetWidth();
	int DstHeight=pDib->GetHeight();
	int DstWidthBytes=pDib->GetWidthBytes();
	LPBYTE pDstImage=pDib->GetBitsPtr();


	int bit=GetBitCount()/8;
	for(int i=rect.top;i<rect.bottom;i++)
	{
		LPBYTE pImage1=pSrcImage+(SrcHeight-i-1)*SrcWidthBytes+rect.left*bit;
		LPBYTE pImage2=pDstImage+(DstHeight-(i-rect.top)-1)*DstWidthBytes;
		for(int f=rect.left;f<rect.right;f++)
		{
			if(bit==3)
			{
				pImage1[2]=pImage2[2];
				pImage1[1]=pImage2[1];
				pImage1[0]=pImage2[0];
			}
			if(bit==1)
			{
				pImage1[0]=pImage2[0];
			}

			pImage1+=bit;
			pImage2+=bit;
		}
	}
	UpdateInternal();
}


void  CDib::FillDibRect(CRect rect,COLORREF color)
{
    int widthbytes = GetWidthBytes();
    int height= GetHeight();
	int width = GetWidth();
	int bit = GetBitCount()/8;
	LPBYTE pImage = GetBitsPtr();
	for(int i=rect.top;i<rect.bottom;i++)
	{
		if(i==height)continue;
		LPBYTE pImage1=pImage+ (height - 1 - i)*widthbytes + rect.left*bit;
		for(int j=rect.left;j<rect.right;j++)
		{
			pImage1[2] =GetRValue(color);
			pImage1[1] =GetGValue(color);
			pImage1[0] =GetBValue(color);
			pImage1+= bit;
		}
	}	
} 
BOOL CDib::Rotate(double fDegrees, COLORREF clrBack)
{
	HDIB hNewDib = RotateDIB(m_hDib, fDegrees, clrBack);
	if (! hNewDib)
		return FALSE;

	// set to m_hDib
	Destroy();
	m_hDib = hNewDib;

	// return
	return UpdateInternal();
}

BOOL CDib::ColorQuantize(int nColorBits)
{
	HDIB hNewDib;

	if (nColorBits > 8)
		hNewDib = ConvertDIBFormat(m_hDib, nColorBits, NULL); 
	else
	{
		int nColors = 1<<nColorBits;
		hNewDib = ColorQuantizeDIB(m_hDib, nColorBits, nColors);
	}

	if (! hNewDib)
		return FALSE;

	Destroy();
	m_hDib = hNewDib;
	
	return UpdateInternal();
}
BOOL CDib::Rotate90()
{
	HDIB hNewDib = RotateDIB(m_hDib);
	if (! hNewDib)
		return FALSE;

	// set to m_hDib
	Destroy();
	m_hDib = hNewDib;

	// return
	return UpdateInternal();
}

BOOL CDib::Rotate180()
{
	HDIB h = RotateDIB(m_hDib);
	if (! h)
		return FALSE;
	HDIB hNewDib = RotateDIB(h);
	DestroyDIB(h);
	if (! hNewDib)
		return FALSE;

	// set to m_hDib
	Destroy();
	m_hDib = hNewDib;

	// return
	return UpdateInternal();
}

BOOL CDib::Rotate270()
{
	HDIB h1 = RotateDIB(m_hDib);
	if (! h1)
		return FALSE;
	HDIB h2 = RotateDIB(h1);
	DestroyDIB(h1);
	if (! h2)
		return FALSE;
	HDIB hNewDib = RotateDIB(h2);
	DestroyDIB(h2);
	if (! hNewDib)
		return FALSE;

	// set to m_hDib
	Destroy();
	m_hDib = hNewDib;

	// return
	return UpdateInternal();
}


void CDib::FillDib(int color)
{
	int widthbytes = GetWidthBytes();
    int height= GetHeight();
	int width = GetWidth();
	int bit = GetBitCount()/8;
	LPBYTE pImage = GetBitsPtr();
	if(color==0)
	{
		memset(pImage,0x0,height*widthbytes);
		return;
	}

	for(int i=0;i<height;i++)
	{
		LPBYTE pImage1=pImage+ (height - 1 - i)*widthbytes;
		for(int j=0;j<width;j++)
		{
			if(bit>=3)
			{
				pImage1[2] =GetRValue(color);
				pImage1[1] =GetGValue(color);
				pImage1[0] =GetBValue(color);
			}
			if(bit==1)
				pImage1[0] =color;
			pImage1+= bit;
		}
	}
	UpdateInternal();
}

void CDib::DDALine(CPoint pt1, CPoint pt2,COLORREF LineCol)
{

	int bit=GetBitCount();
	int height=GetHeight();
	int width=GetWidth();
	LPBYTE pImage=GetBitsPtr();
	int widthBytes=GetWidthBytes();

	if(pt1.x<0||pt1.x>=width)return;
	if(pt2.x<0||pt2.x>=width)return;
	if(pt1.y<0||pt1.y>=height)return;
	if(pt2.y<0||pt2.y>=height)return;

	int xa=pt1.x;
	int ya=pt1.y;
	int xb=pt2.x;
	int yb=pt2.y;


	float delta_x, delta_y, x, y;

	int dx, dy, steps, k;

	dx=xb-xa;

	dy=yb-ya;

	if (abs(dx)>abs(dy)) 
		steps=abs(dx);
	else 
		steps=abs (dy);

	delta_x=(float)dx / (float)steps;

	delta_y=(float)dy / (float)steps;

	x=(float)xa;

	y=(float)ya;

	LPBYTE pImage1=pImage+(height-int(y+0.5)-1)*widthBytes+int(x+0.5)*bit/8;
	if(bit>=24)
	{
		pImage1[2] =GetRValue(LineCol);
		pImage1[1] =GetGValue(LineCol);
		pImage1[0] =GetBValue(LineCol);
	}		

	for (k=1; k<=steps; k++)

	{

		x+=delta_x;

		y+=delta_y;

		LPBYTE pImage1=pImage+(height-int(y+0.5)-1)*widthBytes+int(x+0.5)*bit/8;
		if(bit>=24)
		{
			pImage1[2] =GetRValue(LineCol);
			pImage1[1] =GetGValue(LineCol);
			pImage1[0] =GetBValue(LineCol);
		}		
	}





   

/*	int xa=pt1.x;
	int ya=pt1.y;
	int xb=pt2.x;
	int yb=pt2.y;
	float a,b,d1,d2,d;
	int x,y;
	a=ya-yb;
	b=xb-xa;
	d=2*a+b;
	d1=2*a;
	d2=2*(a+b);
	x=xa;
	y=ya;

	LPBYTE pImage1=pImage+(height-int(y+0.5)-1)*widthBytes+int(x+0.5)*bit/8;
	if(bit>=24)
	{
		pImage1[2] =GetRValue(LineCol);
		pImage1[1] =GetGValue(LineCol);
		pImage1[0] =GetBValue(LineCol);
	}			
	
	
	
	while(x<xb)
	{
		if (d<0)
		{
			x++;
			y++;
			d+=d2;
		}
		else
		{
			x++;
			d+=d1;
		}
		LPBYTE pImage1=pImage+(height-int(y+0.5)-1)*widthBytes+int(x+0.5)*bit/8;
		if(bit>=24)
		{
			pImage1[2] =GetRValue(LineCol);
			pImage1[1] =GetGValue(LineCol);
			pImage1[0] =GetBValue(LineCol);
		}			
	}

*/
}

void CDib::FillRgn(CRgn rgn, COLORREF color)
{
    int widthbytes = GetWidthBytes();
    int height= GetHeight();
	int width = GetWidth();
	int bit = GetBitCount()/8;
	LPBYTE pImage = GetBitsPtr();
	for(int i=0;i<height;i++)
	{
		LPBYTE pImage1=pImage+ (height - 1 - i)*widthbytes;

		for(int j=0;j<width;j++)
		{
			if(rgn.PtInRegion(CPoint(j,i)))
			{
				pImage1[2] =GetRValue(color);
				pImage1[1] =GetGValue(color);
				pImage1[0] =GetBValue(color);
			}
			pImage1+= bit;
		}
	}	
}

//仅用于放码图保存
void CDib::FillRgn(CRgn *rgn,int rgncount, COLORREF *color)
{
//     int widthbytes = GetWidthBytes();
//     int height= GetHeight();
// 	int width = GetWidth();
// 	int bit = GetBitCount()/8;
// 	LPBYTE pImage = GetBitsPtr();
// 
// 	int red[8],blue[8],green[8];
// 	for(int f=0;f<rgncount;f++)
// 	{
// 		red[f]=GetRValue(color[f]);
// 		green[f]=GetGValue(color[f]);
// 		blue[f]=GetBValue(color[f]);
// 	}
// 
// 	for(int i=0;i<height;i++)
// 	{
// 		LPBYTE pImage1=pImage+ (height - 1 - i)*widthbytes;
// 
// 		for(int j=0;j<width;j++)
// 		{
// 			CPoint pt=CPoint(j,i);
// 			for(int k=0;k<rgncount;k++)
// 			{
// 				if(rgn[k].IsEmpty())continue;
// 				if(rgn[k].PtInRegion(pt))
// 				{
// 					pImage1[2] =red[k];
// 					pImage1[1] =green[k];
// 					pImage1[0] =blue[k];
// 					break;
// 				}
// 			}
// 			
// 			pImage1+= bit;
// 		}
// 	}	
}
CRect  CDib::GetDibRect()
{
 	return CRect(0,0,GetWidth(),GetHeight());
}
int  CDib::GetColors(COLORREF *color)
{
    int widthbytes = GetWidthBytes();
    int height= GetHeight();
	int width = GetWidth();
	int bit = GetBitCount()/8;
	LPBYTE pImage = GetBitsPtr();
	LPBYTE pImage0=pImage + (height - 1)*widthbytes;
	COLORREF curColor;
	color[0] = RGB(pImage0[2],pImage0[1],pImage0[0]);
	int nFlag;
	int ncount=0;
	for(int i=0;i<height;i++)
	{
		LPBYTE pImage1=pImage + (height - 1 - i)*widthbytes;
		for(int j=0;j<width;j++)
		{
			curColor = RGB(pImage1[2],pImage1[1],pImage1[0]);
			nFlag = 1;
			for(int k=0;k<ncount;k++)
			{
				if(color[k] == curColor)
				{
					nFlag = 0;
					break;
				}
			}
			if(nFlag == 1)
			{
				color[ncount++] = curColor;
			}
			pImage1+= bit;

			if(ncount>=256)
			{
				break;
			}

		}
		if(ncount>=256)
		{
			break;
		}
	}
	return ncount;
}
void CDib::ConvertToDib8(CDib *pDib8,RGBQUAD* pe)
{
    if (pDib8==NULL)return;
  

	int widthbyte=GetWidthBytes();
	int height=GetHeight();
	int width=GetWidth();
	int bit=GetBitCount()/8;
	LPBYTE psrcImage=GetBitsPtr();

	int widthbyte2=pDib8->GetWidthBytes();
	LPBYTE psrcImage2=pDib8->GetBitsPtr();


	COLORREF dibColor[256];
	int ncount = GetColors(dibColor);

	int dibindex[256];
	int x,xx;
	for(x=0;x<ncount;x++)
	{
		for(xx=0;xx<256;xx++)
		{
			COLORREF curColor = RGB( pe[xx].rgbRed, pe[xx].rgbGreen, pe[xx].rgbBlue);
			if(curColor==dibColor[x])break;
		}
		dibindex[x]=xx;		
	}
	
	for(x=0;x<256;x++)
	{
		pDib8->SetColorTableEntry(x,RGB( pe[x].rgbRed, pe[x].rgbGreen, pe[x].rgbBlue));
	}
	for(int i=0;i<height;i++)
	{
		LPBYTE pImage=psrcImage+i*widthbyte;
		LPBYTE pImage2=psrcImage2+i*widthbyte2;
		for(int j=0;j<width;j++)
		{
			COLORREF curColor = RGB(pImage[2],pImage[1],pImage[0]);
			int n;
			for(n=0;n<ncount;n++)
			{
				if(curColor==dibColor[n])break;
			}
			pImage2[0]=dibindex[n];			
			pImage+=bit;
			pImage2++;
		}
	} 
}
//直线
void CDib::DrawLine(CPoint pt1, CPoint pt2, COLORREF LineCol)
{
	int bit=GetBitCount()/8;
	int height=GetHeight();
	int width=GetWidth();
	LPBYTE pImage=GetBitsPtr();
	int widthBytes=GetWidthBytes();
	if(pt1.y!=pt2.y&&pt1.x!=pt1.x)
		return;
	if(pt1.x<0||pt1.x>=width)return;
	if(pt2.x<0||pt2.x>=width)return;
	if(pt1.y<0||pt1.y>=height)return;
	if(pt2.y<0||pt2.y>=height)return;

	if(pt1.x==pt2.x)
	{
		int p1=pt1.y<pt2.y?pt1.y:pt2.y;
		int p2=pt1.y>pt2.y?pt1.y:pt2.y;

		LPBYTE pImage1=pImage+(height-p1-1)*widthBytes+pt1.x*bit;
		for(int i=p1;i<=p2;i++)
		{
			if(bit==3)
			{
				pImage1[2]=GetRValue(LineCol);
				pImage1[1]=GetGValue(LineCol);
				pImage1[0]=GetBValue(LineCol);
			}
			else
				pImage1[0]=int(LineCol);
			pImage1-=widthBytes;

		}
	}
	else
	{
		int p1=pt1.x<pt2.x?pt1.x:pt2.x;
		int p2=pt1.x>pt2.x?pt1.x:pt2.x;

		LPBYTE pImage1=pImage+(height-pt1.y-1)*widthBytes+p1*bit;
		for(int i=p1;i<=p2;i++)
		{
			if(bit==3)
			{
				pImage1[2]=GetRValue(LineCol);
				pImage1[1]=GetGValue(LineCol);
				pImage1[0]=GetBValue(LineCol);
			}
			else
				pImage1[0]=int(LineCol);
			pImage1+=bit;

		}
	}
}

void CDib::FillMutiRgn(COLORREF color, CRgn *pRgn,int count,BOOL bFillIn)
{
// 	CRect    Rect[100];
// 	int width = GetWidth();
// 	int height = GetHeight();
// 	int bit = GetBitCount()/8;
// 	LPBYTE pImage = GetBitsPtr();
// 	int widthbytes = GetWidthBytes();
// 
// 	for(int i=0;i<count;i++)
// 		pRgn[i].(Rect[i]);
// 	if(bFillIn)
// 	{
// 		for(int i=0;i<height;i++)
// 		{
// 			LPBYTE pImage1=pImage + (height - 1 - i)*widthbytes;
// 			for(int j=0;j<width;j++)
// 			{
// 				CPoint pt = CPoint(j,i);
// 				for(int r=0;r<count;r++)
// 				{
// 					if(!Rect[r].PtInRect(pt))continue;
// 					if(pRgn[r].PtInRegion(pt))
// 					{
// 						pImage1[2]=GetRValue(color);
// 						pImage1[1]=GetGValue(color);
// 						pImage1[0]=GetBValue(color);
// 						break;
// 					}
// 				}
// 
// 				pImage1+= bit;
// 			}
// 		}	
// 	}
// 	else
// 	{
// 		for(int i=0;i<height;i++)
// 		{
// 			LPBYTE pImage1=pImage + (height - 1 - i)*widthbytes;
// 			for(int j=0;j<width;j++)
// 			{
// 				CPoint pt = CPoint(j,i);
// 
// 	/*			for(int r=0;r<count;r++)
// 				{
// 					Rect[r].InflateRect(20,20);
// 					if(!Rect[r].PtInRect(pt))continue;
// 
// 					if(!pRgn[r].PtInRegion(pt))
// 					{
// 						pImage1[2]=GetRValue(color);
// 						pImage1[1]=GetGValue(color);
// 						pImage1[0]=GetBValue(color);
// 						break;
// 					}
// 				}*/
// 				BOOL bFlag=true;
// 				for(int r=0;r<count;r++)
// 				{
// 					if(pRgn[r].PtInRegion(pt))
// 					{
// 						bFlag=false;
// 						break;
// 					}
// 				}
// 				if(bFlag)
// 				{
// 					pImage1[2]=GetRValue(color);
// 					pImage1[1]=GetGValue(color);
// 					pImage1[0]=GetBValue(color);
// 				}
// 
// 				pImage1+= bit;
// 			}
// 		}	
// 	}
// 	UpdateInternal();
}
void CDib::SetCtrlDib(BOOL bIni)
{
 	int height=GetHeight()-1;
	COLORREF color=RGB(0,0,0);
// 	if(bIni)
// 		FillDib(color);
// 	color=m_PalColorsRN[201];
// 	DrawLine(CPoint(0,0),CPoint(0,height),color);
// 	color=m_PalColorsRN[202];
// 	DrawLine(CPoint(8,0),CPoint(8,height),color);
// 	color=m_PalColorsRN[203];
// 	DrawLine(CPoint(11,0),CPoint(11,height),color);
// 	color=m_PalColorsRN[204];
// 	DrawLine(CPoint(14,0),CPoint(14,height),color);
// 	color=m_PalColorsRN[205];
// 	DrawLine(CPoint(17,0),CPoint(17,height),color);
// 	color=m_PalColorsRN[206];
// 	DrawLine(CPoint(20,0),CPoint(20,height),color);
// 	color=m_PalColorsRN[207];
// 	DrawLine(CPoint(23,0),CPoint(23,height),color);
// 	color=m_PalColorsRN[208];
// 	DrawLine(CPoint(27,0),CPoint(27,height),color);
// 	color=m_PalColorsRN[209];
// 	DrawLine(CPoint(34,0),CPoint(34,height),color);
// 	color=m_PalColorsRN[210];
// 	DrawLine(CPoint(38,0),CPoint(38,height),color);
// 	color=m_PalColorsRN[211];
// 	DrawLine(CPoint(42,0),CPoint(42,height),color);
// 	color=m_PalColorsRN[212];
// 	DrawLine(CPoint(46,0),CPoint(46,height),color);
// 	color=m_PalColorsRN[213];
// 	DrawLine(CPoint(50,0),CPoint(50,height),color);
// 	color=m_PalColorsRN[214];
// 	DrawLine(CPoint(53,0),CPoint(53,height),color);
// 	color=m_PalColorsRN[215];
// 	DrawLine(CPoint(58,0),CPoint(58,height),color);
// 	color=m_PalColorsRN[216];
// 	DrawLine(CPoint(66,0),CPoint(66,height),color);
// 	color=m_PalColorsRN[217];
// 	DrawLine(CPoint(74,0),CPoint(74,height),color);
// 	color=m_PalColorsRN[218];
// 	DrawLine(CPoint(82,0),CPoint(82,height),color);
// 	color=m_PalColorsRN[219];
// 	DrawLine(CPoint(90,0),CPoint(90,height),color);
// 	color=m_PalColorsRN[220];
// 	DrawLine(CPoint(94,0),CPoint(94,height),color);
// 	color=m_PalColorsRN[221];
// 	DrawLine(CPoint(97,0),CPoint(97,height),color);
// 	color=m_PalColorsRN[222];
// 	DrawLine(CPoint(100,0),CPoint(100,height),color);
// 	color=m_PalColorsRN[223];
// 	DrawLine(CPoint(103,0),CPoint(103,height),color);
// 	color=m_PalColorsRN[224];
// 	DrawLine(CPoint(107,0),CPoint(107,height),color);
// 	color=m_PalColorsRN[225];
// 	DrawLine(CPoint(111,0),CPoint(111,height),color);
// 	color=m_PalColorsRN[226];
// 	DrawLine(CPoint(114,0),CPoint(114,height),color);
// 	color=m_PalColorsRN[227];
// 	DrawLine(CPoint(118,0),CPoint(118,height),color);
// 	color=m_PalColorsRN[228];
// 	DrawLine(CPoint(121,0),CPoint(121,height),color);
// 	color=m_PalColorsRN[229];
// 	DrawLine(CPoint(124,0),CPoint(124,height),color);
// 	color=m_PalColorsRN[230];
// 	DrawLine(CPoint(127,0),CPoint(127,height),color);
	UpdateInternal();
}
CRect CDib::FitDibRect(CRect ShowRect,CRect DibRect,BOOL bZoom) //等比例放缩rect,目的是适合showrect显示
{
	CRect rect=DibRect;
	double ratio1=double(DibRect.Width())/double(ShowRect.Width());
	double ratio2=double(DibRect.Height())/double(ShowRect.Height());
	double ratio=ratio1>ratio2?ratio1:ratio2;
    int width =	int(DibRect.Width()/ ratio+0.5);
	int height= int(DibRect.Height()/ ratio+0.5);
	int offx= (width-ShowRect.Width())/2;
	int offy= (height-ShowRect.Height())/2;
	int left=ShowRect.left-offx;
	int top =ShowRect.top-offy;
	rect=CRect(left,top,left+width,top+height);
	if(!bZoom)
	{
		if(DibRect.Width()<width&&DibRect.Height()<height)
		{
			left=ShowRect.left+ShowRect.Width()/2-DibRect.Width()/2;
			top=ShowRect.top+ShowRect.Height()/2-DibRect.Height()/2;
			return CRect(left,top,left+DibRect.Width(),top+DibRect.Height());
		}
	}
  
	return rect;

}
int CDib::GetPixelIndex(int PosX,int PosY,COLORREF *ColorTable,int ColorNum) 
{

   COLORREF color=GetPixel(PosX,PosY);
   if (color==-1)
   {
	   return 0;
   }
   for (int i=0;i<ColorNum;i++)
   {
	   if (color==ColorTable[i])
	   {
		   return i;
	   }
   }
  
   return 0;

}

BOOL CDib::Crop(CRect rc)
{
   HDIB hNewDib = CropDIB(m_hDib, rc);
   if (!hNewDib)
      return FALSE;

   // set to m_hDib
   Destroy();
   m_hDib = hNewDib;

   // return
   return UpdateInternal();
}

/*************************************************************************
   Function:	ChangeImageSize
   Description:	 修改图像大小
   Input:
         int nWidth : 修改宽度
         int nHeight: 修改高度
         int nStrechMode: 尺寸修改模式（默认：COLORONCOLOR）
   Return:	成功返回TRUE，否则返回FALSE
*****************************************************************************/
BOOL CDib::ChangeImageSize(int nWidth, int nHeight, int nStrechMode)
{
   if (nWidth <= 0 || nHeight <= 0 || nWidth * nHeight > 5000 * 5000)
      return FALSE;
   if (m_hDib == NULL)
      return FALSE;

   HDIB hNewDib = ChangeDIBSize(m_hDib, nWidth, nHeight, nStrechMode);
   if (!hNewDib)
      return FALSE;

   // set to m_hDib
   Destroy();
   m_hDib = hNewDib;

   // return
   return UpdateInternal();
}
