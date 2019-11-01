
// CreateThumbFileDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CreateThumbFile.h"
#include "CreateThumbFileDlg.h"
#include "afxdialogex.h"
#include <GdiplusImaging.h>

using namespace Gdiplus;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCreateThumbFileDlg 对话框




CCreateThumbFileDlg::CCreateThumbFileDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCreateThumbFileDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCreateThumbFileDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialogEx::DoDataExchange(pDX);
   DDX_Control(pDX, IDC_EDIT_TARGET_SIZE, m_editTargetSize);
   DDX_Control(pDX, IDC_STATIC_SIZE, m_StaticSize);
}

BEGIN_MESSAGE_MAP(CCreateThumbFileDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
   ON_BN_CLICKED(IDC_BUTTON1, &CCreateThumbFileDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CCreateThumbFileDlg 消息处理程序

BOOL CCreateThumbFileDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCreateThumbFileDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCreateThumbFileDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
   UINT  num = 0;          // 图像编码器数量
   UINT  size = 0;         // 图像编码器数组大小

   ImageCodecInfo* pImageCodecInfo = NULL;

   GetImageEncodersSize(&num, &size);    // 获取编码器数量
   if (size == 0)
      return -1;  

   pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
   if (pImageCodecInfo == NULL)
      return -1;

   GetImageEncoders(num, size, pImageCodecInfo);    // 获取本机支持的编码器

   for (UINT j = 0; j < num; ++j)
   {
      if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)    // 找到该格式就将对应的CLSID给*pClsid
      {
         *pClsid = pImageCodecInfo[j].Clsid;
         free(pImageCodecInfo);
         return j;
      }
   }

   free(pImageCodecInfo);
   return -1;
}

bool CompressImageToJpgByQuality( 
   const WCHAR* pszOriFilePath, 
   const WCHAR* pszDestFilePah,
   ULONG quality )
{
   //GdiplusStartupInput gdiplusStartupInput;
   //ULONG_PTR gdiplusToken;
   //Status stat = GenericError;
   //stat = GdiplusStartup( &gdiplusToken, &gdiplusStartupInput, NULL );
   //if ( Ok != stat ) {
   //   return false;
   //}

   // 重置状态
   Status stat = GenericError;

   // Get an image from the disk.
   Image* pImage = Image::FromFile(pszOriFilePath);//new Image(pszOriFilePath);

   do {
      if ( NULL == pImage ) {
         break;
      }

      // 获取长宽
      UINT ulHeight = pImage->GetHeight();
      UINT ulWidth = pImage->GetWidth();
      if ( ulWidth < 1 || ulHeight < 1 ) {
         break;
      }

      // Get the CLSID of the JPEG encoder.
      CLSID encoderClsid;
      if ( !GetEncoderClsid(L"image/jpeg", &encoderClsid) ) {
         break;
      }

      // The one EncoderParameter object has an array of values.
      // In this case, there is only one value (of type ULONG)
      // in the array. We will let this value vary from 0 to 100.
      EncoderParameters encoderParameters;
      encoderParameters.Count = 1;
      encoderParameters.Parameter[0].Guid = EncoderQuality;
      encoderParameters.Parameter[0].Type = EncoderParameterValueTypeLong;
      encoderParameters.Parameter[0].NumberOfValues = 1;
      encoderParameters.Parameter[0].Value = &quality;
      stat = pImage->Save(pszDestFilePah, &encoderClsid, &encoderParameters);
   } while(0);

   //if ( pImage ) {
   //   delete pImage;
   //   pImage = NULL;
   //}

   //GdiplusShutdown(gdiplusToken);

   return ( ( stat == Ok )?  true : false );
}

bool CompressImagePixel( 
   const WCHAR* pszOriFilePath, 
   const WCHAR* pszDestFilePah, 
   int nMaxSize)
{
   // Initialize GDI+.
   UINT ulNewHeigth = 0;
   UINT ulNewWidth = 0;

   Status stat = GenericError;

   // Get an image from the disk.
   Image* pImage = Image::FromFile(pszOriFilePath);

   do {
      if ( NULL == pImage ) {
         break;
      }

      // 获取长宽
      UINT unOriHeight = pImage->GetHeight();
      UINT unOriWidth = pImage->GetWidth();

      double ratio = max(unOriHeight/double(nMaxSize),unOriWidth/double(nMaxSize));

      if(ratio<=1)
      {
         break;
      }
         ulNewHeigth = int(unOriHeight/ratio);
         ulNewWidth = int(unOriWidth/ratio);

      do {
         CLSID encoderClsid;
         if ( unOriWidth < 1 || unOriHeight < 1 ) {
            break;
         }

         // Get the CLSID of the JPEG encoder.
         if ( !GetEncoderClsid(L"image/jpeg", &encoderClsid) ) {
            break;
         }

         REAL fSrcX = 0.0f;
         REAL fSrcY = 0.0f;
         REAL fSrcWidth = (REAL) unOriWidth;
         REAL fSrcHeight = (REAL) unOriHeight ;
         RectF RectDest( 0.0f, 0.0f, (REAL)ulNewWidth, (REAL)ulNewHeigth);


         Bitmap TempBitmap( ulNewWidth, ulNewHeigth );
         Graphics* graphics = NULL;

         do {

            graphics = Graphics::FromImage( &TempBitmap );
            if ( !graphics ) {
               break;
            }

            stat = graphics->SetInterpolationMode(Gdiplus::InterpolationModeHighQuality);
            if ( Ok != stat ) {
               break;
            }

            stat = graphics->SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);
            if ( Ok != stat ) {
               break;
            }

            stat = graphics->DrawImage( pImage, RectDest, fSrcX, fSrcY, fSrcWidth, fSrcHeight,
               UnitPixel, NULL, NULL, NULL);
            if ( Ok != stat ) {
               break;
            }

            stat = TempBitmap.Save( pszDestFilePah, &encoderClsid, NULL );
            if ( Ok != stat ) {
               break;
            }

         } while(0);

         if ( NULL != graphics ) {
            delete graphics;
            graphics = NULL;
         }
      } while(0);
   } while (0);

   //if ( pImage ) {
   //   delete pImage;
   //   pImage = NULL;
   //}

   return ( ( Ok == stat ) ? true : false );
}

bool CompressImageToJpgBySize(const WCHAR *pszOriFilePath, const WCHAR *pszDestFilePath, ULONGLONG ullNeedSize, 
   ULONGLONG *pullResultSize)
{
   CFileStatus fileStatus;
   if (!CFile::GetStatus(pszOriFilePath, fileStatus))
      return false;

   if (fileStatus.m_size < ullNeedSize)
   {
      CopyFile(pszOriFilePath, pszDestFilePath, FALSE);
      if (pullResultSize)
      {
         *pullResultSize = fileStatus.m_size;
      }
      return false;
   }
   int nMax = 100;
   int nMin = 0;

   int nMid = 0;
   while (1)
   {
      nMid = (nMax + nMin) / 2;

      bool bCompress = CompressImageToJpgByQuality(pszOriFilePath, pszDestFilePath, nMid);
      if (!bCompress)
         return false;

      if (!CFile::GetStatus(pszDestFilePath, fileStatus))
         return false;

      if (fileStatus.m_size < ullNeedSize)
      {
         nMin = nMid + 1;
         if (nMin > nMax)
         {
            if (pullResultSize)
            {
               *pullResultSize = fileStatus.m_size;
            }
            return true;
         }
      }
      else if (fileStatus.m_size > ullNeedSize)
      {
         nMax = nMid - 1;
         if (nMin > nMax)
         {
            --nMid;
            for (;nMid >= 0; --nMid)
            {
               bool bCompress = CompressImageToJpgByQuality(pszOriFilePath, pszDestFilePath, nMid);
               if (!bCompress)
                  return false;
               if (!CFile::GetStatus(pszDestFilePath, fileStatus))
                  return false;
               if (fileStatus.m_size <= ullNeedSize)
               {
                  if (pullResultSize)
                  {
                     *pullResultSize = fileStatus.m_size;
                  }
                  return true;
               }
            }
            if (pullResultSize)
            {
               *pullResultSize = fileStatus.m_size;
            }
            return false;
         }
      }
      else
      {
         if (pullResultSize)
         {
            *pullResultSize = fileStatus.m_size;
         }
         return true;
      }
   }

   return false;
}

void CCreateThumbFileDlg::OnBnClickedButton1()
{
   // TODO: 在此添加控件通知处理程序代码
   auto psz = _T("E:\\myProject2\\NewForTortoise\\CreateThumbFile\\Debug\\女款平收肩圆领套绞花.bmp");

   auto pszDst = _T("E:\\myProject2\\NewForTortoise\\CreateThumbFile\\Debug\\女款平收肩圆领套绞花4-26.jpg");

   //We will let this value vary from 0 to 100.
   CString sText;
   m_editTargetSize.GetWindowText(sText);
   ULONGLONG ullNeedSize = wcstol(sText, NULL, 10);
   ullNeedSize *= 1024;

   ULONGLONG ullResultSize  =  0;

   auto pszDst2 = _T("E:\\myProject2\\NewForTortoise\\CreateThumbFile\\Debug\\女款平收肩圆领套绞花4-26000.jpg");
   CompressImagePixel(psz, pszDst2, 300);

   CompressImageToJpgBySize(pszDst2, pszDst, ullNeedSize, &ullResultSize);

   CString sSize;
   sSize.Format(_T("%d"), ullResultSize);
   m_StaticSize.SetWindowText(sSize);

   
   //Gdiplus::Image *pImg = Gdiplus::Image::FromFile(psz);
   //CLSID encoderClsid;
   ////Gdiplus::Bitmap bmp(m_hBitmap,NULL);
   ////GetEncoderClsid(L"image/jpeg",&encoderClsid);//确定编码格式是格式：jpeg

   //int nResult = GetEncoderClsid(L"image/jpeg", &encoderClsid);

   ////int nResult = GetEncoderClsid(L"image/jpeg", &encoderClsid);
   //pImg->Save(pszDst, &encoderClsid);
}
