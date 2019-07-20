// DlgWelcome.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "QLSvrMgn.h"
#include "DlgWelcome.h"


// CDlgWelcome �Ի���

IMPLEMENT_DYNAMIC(CDlgWelcome, CTabDialog)

CDlgWelcome::CDlgWelcome(CWnd* pParent /*=NULL*/)
	: CTabDialog(CDlgWelcome::IDD, pParent)
{

}

CDlgWelcome::~CDlgWelcome()
{
}

void CDlgWelcome::DoDataExchange(CDataExchange* pDX)
{
	CTabDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgWelcome, CTabDialog)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CDlgWelcome ��Ϣ�������


void CDlgWelcome::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CTabDialog::OnPaint()

	ShowWaterMark(&dc);
}

void CDlgWelcome::ShowWaterMark(CDC* pDC)
{
/*	CString string;
	string="�������";
	CFont m_fontLogo;
	m_fontLogo.CreateFont(100, 0, 0, 0, 155, FALSE, FALSE,0,0,0,0,0,0, "Arial");
	//�������壻
	pDC->SetBkMode(TRANSPARENT);
	CRect rectText;
	GetClientRect(&rectText);
	pDC->DPtoLP(&rectText);  
	rectText.NormalizeRect();
	CFont * OldFont = pDC->SelectObject(&m_fontLogo);
	COLORREF OldColor = pDC->SetTextColor( ::GetSysColor( COLOR_3DSHADOW));
	//��Ӱ״̬��ʾ���֣�
// 	pDC->DrawText( string, rectText+CPoint(2,2) , 
// 		DT_SINGLELINE | DT_LEFT |DT_VCENTER|DT_CENTER);
// 	pDC->SetTextColor(::GetSysColor( COLOR_3DHILIGHT) );
// 	//����״̬��ʾ���֣�
// 	pDC->DrawText( string, rectText, DT_SINGLELINE | DT_LEFT |DT_VCENTER|DT_CENTER);

	pDC->DrawText( string, rectText+CPoint(2,2) , 
		DT_SINGLELINE | DT_RIGHT | DT_BOTTOM);
	pDC->SetTextColor(::GetSysColor( COLOR_3DHILIGHT) );
	//����״̬��ʾ���֣�
	pDC->DrawText( string, rectText, DT_SINGLELINE | DT_RIGHT | DT_BOTTOM);

	pDC->SetTextColor( OldColor);
	pDC->SelectObject(OldFont);
	m_fontLogo.DeleteObject();*/

/*	LOGFONT lf;
	pDC->GetCurrentFont()->GetLogFont(&lf);
	CFont font;
	CFont *pOldFont; // �����豸���������ʹ�õ��������
	lf.lfCharSet=134;
	lf.lfHeight=-150;
	lf.lfHeight=-150;
	lf.lfWidth=0;
	strcpy(lf.lfFaceName, _T("����"));
	font.CreateFontIndirect(&lf);
	pOldFont=pDC->SelectObject(&font);
	pDC->SetBkMode(TRANSPARENT); // ���ĵ�ǰ����
	CPen pen(PS_SOLID, 1, RGB(255, 0, 0));
	CPen *pOldPen;
	pOldPen=pDC->SelectObject(&pen); // ��ʼһ��·�� 
	pDC->BeginPath();
	pDC->TextOut(10, 10, "������");
	pDC->EndPath(); 

	// ����·�� 
	pDC->StrokePath(); 	
	//������dc.StrokeAndFillPath()���������棬�����ú�����ʹ�õ�ǰˢ�����·�����ڲ���
	//�������б�Ҫ��ǰ������Լ���ˢ�ӣ��������ɾ������������ 
	//���������ĵ�ǰˢ�� 
// 	CBrush br(HS_DIAGCROSS, RGB(0, 255, 255)), *pOldBrush; 
// 	pOldBrush=pDC->SelectObject(&br); 
// 	pDC->StrokeAndFillPath();
// 	pOldBrush=pDC->SelectObject(&br); 
// 	pDC->SelectObject(pOldBrush); 

	// �ָ��豸�����ĵ�ԭ������ 
	pDC->SelectObject(pOldFont); 
	pDC->SelectObject(pOldPen); */

	CString str;
	//str = theApp.AnsiToUnicode("�������");
	str = _T("��ӭʹ���������");
	CFont newFont,*oldFont;
	COLORREF oldColor;
	LOGFONT f;
	f.lfCharSet = DEFAULT_CHARSET;
	f.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	f.lfEscapement = 0;
	f.lfHeight = 84;
	f.lfItalic = 0;
	f.lfOrientation = 0;
	f.lfOutPrecision = OUT_DEFAULT_PRECIS;
	f.lfPitchAndFamily = FIXED_PITCH | FF_ROMAN;
	f.lfQuality = DEFAULT_QUALITY;
	f.lfStrikeOut = FALSE;
	f.lfUnderline = FALSE;
	f.lfWeight = FW_BOLD;
	f.lfWidth = 0;
	//strcpy(f.lfFaceName,"����_GB2312");
	_tcscpy(f.lfFaceName, _T("Arial"));
	newFont.CreateFontIndirect(&f);
	oldColor = pDC->SetTextColor(RGB(0,0,0));
	oldFont = (CFont*)pDC->SelectObject(&newFont);
	CRect rectText;
	GetClientRect(&rectText);
	pDC->DPtoLP(&rectText);  
	rectText.NormalizeRect();
	pDC->SetBkMode(TRANSPARENT);
	pDC->DrawText(str,rectText,DT_SINGLELINE /*| DT_VCENTER */| DT_CENTER);
	pDC->SetTextColor(::GetSysColor(COLOR_3DHILIGHT)); 
	pDC->DrawText(str,rectText+CPoint(2,2),DT_SINGLELINE /*| DT_VCENTER */| DT_CENTER);
	pDC->SelectObject(oldFont);
	pDC->SetTextColor(oldColor);
}
