
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


void CCreateThumbFileDlg::OnBnClickedButton1()
{
   // TODO: 在此添加控件通知处理程序代码
   auto psz = _T("I:\\图片\\参考图片\\女款平收肩圆领套绞花.png");
   Gdiplus::Image *pImg = Gdiplus::Image::FromFile(psz);

   auto pszDst = _T("I:\\图片\\参考图片\\女款平收肩圆领套绞花2.jpg");

   CLSID encoderClsid;
   //Gdiplus::Bitmap bmp(m_hBitmap,NULL);
   //GetEncoderClsid(L"image/jpeg",&encoderClsid);//确定编码格式是格式：jpeg

   int nResult = GetEncoderClsid(L"image/jpeg", &encoderClsid);

   //int nResult = GetEncoderClsid(L"image/jpeg", &encoderClsid);
   pImg->Save(pszDst, &encoderClsid);
}
