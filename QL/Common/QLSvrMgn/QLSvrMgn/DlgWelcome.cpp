// DlgWelcome.cpp : 实现文件
//

#include "stdafx.h"
#include "QLSvrMgn.h"
#include "DlgWelcome.h"


// CDlgWelcome 对话框

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


// CDlgWelcome 消息处理程序


void CDlgWelcome::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CTabDialog::OnPaint()

	ShowWaterMark(&dc);
}

void CDlgWelcome::ShowWaterMark(CDC* pDC)
{
/*	CString string;
	string="琪利软件";
	CFont m_fontLogo;
	m_fontLogo.CreateFont(100, 0, 0, 0, 155, FALSE, FALSE,0,0,0,0,0,0, "Arial");
	//创建字体；
	pDC->SetBkMode(TRANSPARENT);
	CRect rectText;
	GetClientRect(&rectText);
	pDC->DPtoLP(&rectText);  
	rectText.NormalizeRect();
	CFont * OldFont = pDC->SelectObject(&m_fontLogo);
	COLORREF OldColor = pDC->SetTextColor( ::GetSysColor( COLOR_3DSHADOW));
	//阴影状态显示文字；
// 	pDC->DrawText( string, rectText+CPoint(2,2) , 
// 		DT_SINGLELINE | DT_LEFT |DT_VCENTER|DT_CENTER);
// 	pDC->SetTextColor(::GetSysColor( COLOR_3DHILIGHT) );
// 	//高亮状态显示文字；
// 	pDC->DrawText( string, rectText, DT_SINGLELINE | DT_LEFT |DT_VCENTER|DT_CENTER);

	pDC->DrawText( string, rectText+CPoint(2,2) , 
		DT_SINGLELINE | DT_RIGHT | DT_BOTTOM);
	pDC->SetTextColor(::GetSysColor( COLOR_3DHILIGHT) );
	//高亮状态显示文字；
	pDC->DrawText( string, rectText, DT_SINGLELINE | DT_RIGHT | DT_BOTTOM);

	pDC->SetTextColor( OldColor);
	pDC->SelectObject(OldFont);
	m_fontLogo.DeleteObject();*/

/*	LOGFONT lf;
	pDC->GetCurrentFont()->GetLogFont(&lf);
	CFont font;
	CFont *pOldFont; // 保存设备上下文最初使用的字体对象
	lf.lfCharSet=134;
	lf.lfHeight=-150;
	lf.lfHeight=-150;
	lf.lfWidth=0;
	strcpy(lf.lfFaceName, _T("隶书"));
	font.CreateFontIndirect(&lf);
	pOldFont=pDC->SelectObject(&font);
	pDC->SetBkMode(TRANSPARENT); // 更改当前画笔
	CPen pen(PS_SOLID, 1, RGB(255, 0, 0));
	CPen *pOldPen;
	pOldPen=pDC->SelectObject(&pen); // 开始一个路径 
	pDC->BeginPath();
	pDC->TextOut(10, 10, "空心字");
	pDC->EndPath(); 

	// 绘制路径 
	pDC->StrokePath(); 	
	//可以用dc.StrokeAndFillPath()函数来代替，不过该函数会使用当前刷子填充路径的内部。
	//所以你有必要在前面产生自己的刷子，并在最后删除，就象下面 
	//这样：更改当前刷子 
// 	CBrush br(HS_DIAGCROSS, RGB(0, 255, 255)), *pOldBrush; 
// 	pOldBrush=pDC->SelectObject(&br); 
// 	pDC->StrokeAndFillPath();
// 	pOldBrush=pDC->SelectObject(&br); 
// 	pDC->SelectObject(pOldBrush); 

	// 恢复设备上下文的原有设置 
	pDC->SelectObject(pOldFont); 
	pDC->SelectObject(pOldPen); */

	CString str;
	//str = theApp.AnsiToUnicode("琪利软件");
	str = _T("欢迎使用琪利软件");
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
	//strcpy(f.lfFaceName,"楷体_GB2312");
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
