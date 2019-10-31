
// CreateThumbFileDlg.cpp : ʵ���ļ�
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


// CCreateThumbFileDlg �Ի���




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


// CCreateThumbFileDlg ��Ϣ�������

BOOL CCreateThumbFileDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCreateThumbFileDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CCreateThumbFileDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
   UINT  num = 0;          // ͼ�����������
   UINT  size = 0;         // ͼ������������С

   ImageCodecInfo* pImageCodecInfo = NULL;

   GetImageEncodersSize(&num, &size);    // ��ȡ����������
   if (size == 0)
      return -1;  

   pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
   if (pImageCodecInfo == NULL)
      return -1;

   GetImageEncoders(num, size, pImageCodecInfo);    // ��ȡ����֧�ֵı�����

   for (UINT j = 0; j < num; ++j)
   {
      if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)    // �ҵ��ø�ʽ�ͽ���Ӧ��CLSID��*pClsid
      {
         *pClsid = pImageCodecInfo[j].Clsid;
         free(pImageCodecInfo);
         return j;
      }
   }

   free(pImageCodecInfo);
   return -1;
}

bool CompressImageQuality( 
   const WCHAR* pszOriFilePath, 
   const WCHAR* pszDestFilePah,
   ULONG quality )
{
   // copy from http://msdn.microsoft.com/en-us/library/ms533844(v=VS.85).aspx
   // Initialize GDI+.
   GdiplusStartupInput gdiplusStartupInput;
   ULONG_PTR gdiplusToken;
   Status stat = GenericError;
   stat = GdiplusStartup( &gdiplusToken, &gdiplusStartupInput, NULL );
   if ( Ok != stat ) {
      return false;
   }

   // ����״̬
   stat = GenericError;

   // Get an image from the disk.
   Image* pImage = Image::FromFile(pszOriFilePath);//new Image(pszOriFilePath);

   do {
      if ( NULL == pImage ) {
         break;
      }

      // ��ȡ����
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

   GdiplusShutdown(gdiplusToken);

   return ( ( stat == Ok )?  true : false );
}

void CCreateThumbFileDlg::OnBnClickedButton1()
{
   // TODO: �ڴ���ӿؼ�֪ͨ����������
   auto psz = _T("I:\\ͼƬ\\�ο�ͼƬ\\Ů��ƽ�ռ�Բ���׽ʻ�.png");
   

   auto pszDst = _T("I:\\ͼƬ\\�ο�ͼƬ\\Ů��ƽ�ռ�Բ���׽ʻ�4-24.jpg");

   CompressImageQuality(psz, pszDst, 24);

   
   //Gdiplus::Image *pImg = Gdiplus::Image::FromFile(psz);
   //CLSID encoderClsid;
   ////Gdiplus::Bitmap bmp(m_hBitmap,NULL);
   ////GetEncoderClsid(L"image/jpeg",&encoderClsid);//ȷ�������ʽ�Ǹ�ʽ��jpeg

   //int nResult = GetEncoderClsid(L"image/jpeg", &encoderClsid);

   ////int nResult = GetEncoderClsid(L"image/jpeg", &encoderClsid);
   //pImg->Save(pszDst, &encoderClsid);
}
