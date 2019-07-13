
// Base64Dlg.cpp : ʵ���ļ�
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


// CBase64Dlg �Ի���




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


// CBase64Dlg ��Ϣ�������

BOOL CBase64Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

   CWnd *pEdit1 = GetDlgItem(IDC_EDIT1);
   CString str1;
   pEdit1->SetWindowText(_T("NjY2ODg4"));


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CBase64Dlg::OnPaint()
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
