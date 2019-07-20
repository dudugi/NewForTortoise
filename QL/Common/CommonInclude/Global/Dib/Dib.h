#pragma once

#include "DIBAPI.H"


////////////////////////////////////////////////////////////////////////////
// CDib
class CDib : public CObject
{                          
	DECLARE_SERIAL(CDib)

// Public member function
public: 
	// constructor
	CDib();
	HDIB	Detach(void); 
	BOOL	Attach(HDIB hDib);
	// create
	BOOL	Create(DWORD dwWidth, DWORD dwHeight);
	BOOL	Create(DWORD dwWidth, DWORD dwHeight, WORD wBitCount);
	BOOL	Create(LPBYTE lpDIB);
	BOOL	Create(LPBYTE lpDIB,		// DIB pointer
				   WORD  wBitCount);	// bits/pixel 
	BOOL	Create(HBITMAP hBitmap);	// DIBSection
	BOOL	Create(HBITMAP hBitmap,		// DIBSection
				   WORD  wBitCount);	// bits/pixel 
	BOOL	Create(HBITMAP hBitmap,		// Bitmap handle
				   HPALETTE hPalette);	// Palette handle
	BOOL	Create(HBITMAP hBitmap,		// Bitmap handle
				   HPALETTE hPalette,	// Palette handle
				   WORD  wBitCount);	// bits/pixel 
	BOOL	Create(CRect rcScreen);
	BOOL	Create(HWND hWnd, WORD fPrintArea);
	BOOL	Create(HWND hWnd, CRect rcClientArea);
	// load/save
    BOOL	Load(UINT uIDS, LPCTSTR lpszDibType);
    BOOL	Load(LPCTSTR lpszDibRes, LPCTSTR lpszDibType);
    BOOL	Load(LPCTSTR lpszDibFile);
    BOOL	Save(LPCTSTR lpszDibFile,BOOL bJPGForamt = FALSE);
	BOOL	Read(CFile *pFile);
	BOOL	Write(CFile *pFile);

	/*
	 * @brief	加载任何格式的图片文件
	 * @author	2016/12/28 21:59 zhangt
	 * @param	lpszDibFile 文件全路径
	 * @param	是否加载成功(TRUE成功)
	 */
	BOOL    LoadByGdiplus(LPCTSTR lpszDibFile);//GDI+

   /*
    * @brief	加载任何格式的图片文件并自动调整图片方向
    * @author	2019/2/12 wangzl
    * @param	lpszDibFile 文件全路径
    * @param	是否加载成功(TRUE成功)
    */
   BOOL    LoadByGdiplus_AdaptiveDirection(LPCTSTR lpszDibFile);//GDI+


	/***************************
	 * @brief 获取图片文件的编码方式，支持bmp、jpg、jpeg、gif、tiff和png等格式图片
	 * @author	zhangt 2017/08/03
	 * @param [in]  format 图片格式 值可以为以下几种
	 * @"image/bmp"
	 * @"image/jpeg"
	 * @"image/gif"
	 * @"image/tiff"
	 * @"image/png"
	 * @param [in]  pClsid
	 * @return  成功则返回值 >= 0，失败则返回值为-1
	 ***************************/
	int		GetEncoderClsid(const WCHAR* format, CLSID* pClsid);//GDI+

	BOOL	Save(LPCTSTR lpszDibFile,const WCHAR* format);//GDI+

	// clone
	HDIB	CopyRect(CRect rc);
	BOOL	CutRect(CRect rc);
	BOOL	MergeDib(HDIB hDib, CPoint ptTopLeft);
	CDib *  Clone();
	CDib *	CloneRect(CRect CopyRect);
	BOOL	ConvertFormat(WORD wBitCount);
	void	MirrorImage(CRect MirrorRect, BOOL MirrorH, BOOL MirrorV);
	// deconstructor
	virtual ~CDib();
	// destroy
	void	Destroy();

	// overlaying Serialize
	virtual void Serialize(CArchive &ar);
    
	// display
	void	DrawFloatDib(CDC*pDC,CRect ShowRect,CRect SrcRect,double dScalex,double dScaley);
	BOOL	Display(CDC * pDC, int xDest, int yDest, int nWidthDest, int nHeightDest, 
 				   int xSrc, int ySrc, DWORD dwRop=SRCCOPY);
	BOOL	Display(CDC * pDC, int xDest, int yDest, int nWidthDest, int nHeightDest, 
				    int xSrc, int ySrc, int nWidthSrc, int nHeightSrc, DWORD dwRop=SRCCOPY);
    BOOL	Display(CDC* pDC, int x, int y, DWORD dwRop=SRCCOPY);
	BOOL	Display(CDC* pDC, CRect rcDest, CRect rcSrc,DWORD dwRop=SRCCOPY);
	BOOL	DisplayPalette(CDC* pDC, CRect rc);

	// DC for modify DIB
	CDC*	BeginPaint(CDC *pDC);
	void	EndPaint();

	// DDB and palette
	BOOL	BuildBitmap();
	BOOL	BuildPalette();

	// attributes
	BOOL	IsEmpty();
	DWORD	GetCompression();
    WORD	GetBitCount();
    LONG	GetWidth();
    LONG	GetHeight();    
	LONG	GetWidthBytes();
    WORD	GetColorNumber();
	WORD	GetPaletteSize();
    CBitmap*  GetBitmap();
	CPalette* GetPalette();
	HANDLE	GetHandle();
	LPBYTE	GetBitsPtr();
	COLORREF GetPixel(LONG x, LONG y);
	int		GetPixelIndex(int PosX,int PosY,COLORREF *ColorTable,int ColorNum);
	LONG    GetPixelOffset(LONG x, LONG y);
	BOOL	UpdateInternal();
	COLORREF	SetColorTableEntry(int uIndex,COLORREF rColor);

	void        FillDibRect(CRect rect,COLORREF color);
	BOOL		Rotate(double fDegrees, COLORREF clrBack);
	BOOL		ColorQuantize(int nColorBits);
	BOOL		Rotate90();
	BOOL		Rotate180();
	BOOL		Rotate270();
	void		DDALine(CPoint pt1,CPoint pt2,COLORREF LineCol);
	void		FillDib(int color);
	void		PasteRect(CDib* pDib,CRect rect);
	int			GetDibFileSize();

	void        FillRgn(CRgn rgn, COLORREF color);
	void        FillRgn(CRgn *rgn,int rgncount, COLORREF *color);
	int			GetColors(COLORREF *color);
	void		ConvertToDib8(CDib *pDib8,RGBQUAD* pe);
	void		FillMutiRgn(COLORREF color,CRgn* pRgn,int count,BOOL bFillIn);
	void		DrawLine(CPoint pt1,CPoint pt2,COLORREF LineCol);
	void		CopyFromDib(CDib* pDib,CRect SrcRect,CRect DstRect);
	void		SetCtrlDib(BOOL bIni);
	CRect		FitDibRect(CRect ShowRect,CRect DibRect,BOOL bZoom=1); //等比例放缩rect,目的是适合showrect显示) 
	CRect		GetDibRect();
	CDib*		LimitDibSize(int nMaxSize);
   BOOL	   Crop(CRect rc);
   BOOL	ChangeImageSize(int nWidth, int nHeight, int nStrechMode = COLORONCOLOR);

	// private member function
private:

// public member data
public:
	HDIB		m_hDib;
	HBITMAP		m_hBitmap;	// handle of DIBSection
	CPalette* 	m_pPalette;
	CBitmap*	m_pBitmap;
	CPoint      m_FloatPoint;//060420

	CString     m_sPZDibName;

// private member data
private:
	// for drawing in DIB
	CDC *		m_pMemDC;
	CBitmap*	m_pBitmapTmp;
	CPalette*	m_pPaletteTmp;
};
