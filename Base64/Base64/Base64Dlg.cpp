
// Base64Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Base64.h"
#include "Base64Dlg.h"
#include "afxdialogex.h"
#include <string>
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBase64Dlg 对话框




CBase64Dlg::CBase64Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBase64Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBase64Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBase64Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
   ON_BN_CLICKED(IDC_BUTTON1, &CBase64Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CBase64Dlg 消息处理程序

BOOL CBase64Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

   CWnd *pEdit1 = GetDlgItem(IDC_EDIT1);
   CString str1;
   pEdit1->SetWindowText(_T("NjY2ODg4"));


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CBase64Dlg::OnPaint()
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
HCURSOR CBase64Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

inline bool is_base64(unsigned char c) 
{
   return (isalnum(c) || (c == '+') || (c == '/'));
};

std::string base64_decode(std::string const& encoded_string) 
{
   std::string base64_chars;
   base64_chars = 
      "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
      "abcdefghijklmnopqrstuvwxyz"
      "0123456789+/";

   int in_len = encoded_string.size();
   int i = 0;
   int j = 0;
   int in_ = 0;
   unsigned char char_array_4[4], char_array_3[3];
   std::string ret;

   while (in_len-- && ( encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
      char_array_4[i++] = encoded_string[in_]; in_++;
      if (i ==4) {
         for (i = 0; i <4; i++)
            char_array_4[i] = base64_chars.find(char_array_4[i]);

         char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
         char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
         char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

         for (i = 0; (i < 3); i++)
            ret += char_array_3[i];
         i = 0;
      }
   }

   if (i) {
      for (j = i; j <4; j++)
         char_array_4[j] = 0;

      for (j = 0; j <4; j++)
         char_array_4[j] = base64_chars.find(char_array_4[j]);

      char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
      char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
      char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

      for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
   }

   return ret;
}

std::string base64_encode(unsigned char const* bytes_to_encode) 
{
   std::string base64_chars;
   base64_chars = 
      "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
      "abcdefghijklmnopqrstuvwxyz"
      "0123456789+/";

   unsigned int in_len = strlen((char *)bytes_to_encode);
   std::string ret;
   int i = 0;
   int j = 0;
   unsigned char char_array_3[3];
   unsigned char char_array_4[4];

   while (in_len--) {
      char_array_3[i++] = *(bytes_to_encode++);
      if (i == 3) {
         char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
         char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
         char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
         char_array_4[3] = char_array_3[2] & 0x3f;

         for(i = 0; (i <4) ; i++)
            ret += base64_chars[char_array_4[i]];
         i = 0;
      }
   }

   if (i)
   {
      for(j = i; j < 3; j++)
         char_array_3[j] = '0';

      char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
      char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
      char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
      char_array_4[3] = char_array_3[2] & 0x3f;

      for (j = 0; (j < i + 1); j++)
         ret += base64_chars[char_array_4[j]];

      while((i++ < 3))
         ret += '=';

   }

   return ret;
}

void CBase64Dlg::OnBnClickedButton1()
{
   CWnd *pEdit1 = GetDlgItem(IDC_EDIT1);
   CString str1;
   pEdit1->GetWindowText(str1);

   CStringA str1A(str1);
   std::string str1std = str1A;
   std::string str = base64_decode(str1std);

   if (str.empty())
      return;

   CString str2(str.c_str());
   CWnd *pEdit2 = GetDlgItem(IDC_EDIT2);
   pEdit2->SetWindowText(str2);
}
