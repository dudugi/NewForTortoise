
// XmlToFuncDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "XmlToFunc.h"
#include "XmlToFuncDlg.h"
#include "afxdialogex.h"
#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

struct S_INDEX_STR{
   int nColIndex;
   CString strColInfo;
   S_INDEX_STR(const int & nCol,const CString & strColInfo_in)
   {
      nColIndex = nCol;
      strColInfo = strColInfo_in;
   }
};

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CXmlToFuncDlg �Ի���




CXmlToFuncDlg::CXmlToFuncDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CXmlToFuncDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CXmlToFuncDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

CString CXmlToFuncDlg::GetTinyXmlNodeString(TiXmlElement * pElement)
{
   CString strRet = _T("");
   if(pElement)
   {
      auto pNode = pElement->FirstChild();
      if (pNode)
      {
         string sValue = pNode->ToText()->Value();

         strRet = theApp.UTF8_TO_UNICODE(sValue);
      }
   }
   return strRet;
}

CString CXmlToFuncDlg::GetTinyXmlNodeAttribute(TiXmlElement * pElement,const char * name)
{
   CString strRet = _T("");
   string sName = pElement->Attribute(name);//��λ����

   strRet = theApp.UTF8_TO_UNICODE(sName);
   return strRet;
}

CString CXmlToFuncDlg::ParseElementToStr(__in TiXmlElement * pSrcElement,
   __in const char * name ,
   __in const CString & strDefaultValue,/*Ĭ�ϵ�ֵ */
   __in const CString & strRetValue ,/* �����Ҫ����ʱӦ�÷��ص�ֵ */
   __inout BOOL & bHasShow ,/*֮ǰ�Ѿ��й���ʾ�� */
   __inout int & nMaxLength, /*����ֵ���������*/
   __in const CString & strIncludeBy)
{
   CString strRet = _T("");
   auto pAttriElement = pSrcElement->FirstChildElement(name);
   if (NULL != pAttriElement)
   {
      CString strGetValue = GetTinyXmlNodeString(pAttriElement);
      CString strTmpGetValue = strGetValue;
      if (!strIncludeBy.IsEmpty())
      {
         CString strCache = strIncludeBy;
         strCache.Replace(_T("%%"),strGetValue);
         strGetValue = strCache;
      }

      if (!bHasShow)
      {
         if (0 != strTmpGetValue.CompareNoCase(strDefaultValue))
         {
            if (strRetValue.IsEmpty())
            {
               nMaxLength = GetStringMyLength(strGetValue);
               strRet = _T(",") + strGetValue;
            }
            else
            {
               nMaxLength = 6;
               strRet = _T(",") + strRetValue;
            }
            bHasShow = TRUE;
         }
      }
      else
      {
         if (strTmpGetValue.IsEmpty())
         {
            strGetValue = _T("_T(\"\")");
         }

         nMaxLength = GetStringMyLength(strGetValue);

         strRet = _T(",") + strGetValue;
      }
   }
   else
   {
      CString strCache = strDefaultValue;
      if (!strIncludeBy.IsEmpty())
      {
         strCache = strIncludeBy;
         strCache.Replace(_T("%%"),strDefaultValue);
      }

      nMaxLength = GetStringMyLength(strCache);
      strRet = _T(",") + strCache;
   }

   return strRet;
}

BEGIN_MESSAGE_MAP(CXmlToFuncDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
   ON_BN_CLICKED(IDOK, &CXmlToFuncDlg::OnBnClickedOk)
   ON_BN_CLICKED(IDC_BTN_ADD, &CXmlToFuncDlg::OnBnClickedBtnAdd)
   ON_BN_CLICKED(IDC_BTN_DEL, &CXmlToFuncDlg::OnBnClickedBtnDel)
   ON_BN_CLICKED(IDC_BTN_EMPTY, &CXmlToFuncDlg::OnBnClickedBtnEmpty)
END_MESSAGE_MAP()


// CXmlToFuncDlg ��Ϣ�������

BOOL CXmlToFuncDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CXmlToFuncDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CXmlToFuncDlg::OnPaint()
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
HCURSOR CXmlToFuncDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CXmlToFuncDlg::OnBnClickedOk()
{
   int nCount = m_lstXml.GetCount();
   int nIndex = 0;
   for (;nIndex < nCount;++nIndex)
   {
      CString strFilePath = m_lstXml.GetAt(m_lstXml.FindIndex(nIndex));
      ParseXml(strFilePath);
   }
}

void CXmlToFuncDlg::OnBnClickedBtnAdd()
{
   //���
   CString strFileName = _T("");
   CFileDialog fileDlg(true);

   fileDlg.m_ofn.lpstrFilter = LPCTSTR(_T("XML�ļ�(*.xml)\0*.xml\0\0"));
   fileDlg.m_ofn.lpstrTitle = LPCTSTR(_T("ѡ�������ļ�"));
   //fileDlg.m_ofn.nFilterIndex = 7;
   fileDlg.m_ofn.Flags |= OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT|OFN_FILEMUSTEXIST;

   //2017/04/10 zhangt ��������ļ�����500
   fileDlg.m_ofn.nMaxFile = 10*MAX_PATH;
   TCHAR *ch = new TCHAR[fileDlg.m_ofn.nMaxFile];
   fileDlg.m_ofn.lpstrFile = ch;
   ZeroMemory(fileDlg.m_ofn.lpstrFile,sizeof(TCHAR)*fileDlg.m_ofn.nMaxFile);
   //2017/04/10_end


   if(fileDlg.DoModal() != IDOK)
   {
      delete[] ch;//�ͷ� new ����
      return;
   }


   auto pListBox = (CListBox *)GetDlgItem(IDC_LIST_XML);
   pListBox->ResetContent();
   pListBox->SetRedraw(FALSE);

   POSITION   pos = fileDlg.GetStartPosition();
   while(pos)
   {
      strFileName = fileDlg.GetNextPathName(pos);
      if (!strFileName.IsEmpty())
      {
         m_lstXml.AddTail(strFileName);

         //���ļ���ӵ��б���ȥ
         AddXmlToList(PathFindFileName(strFileName));
      }
   }
   delete[] ch;//�ͷ� new ����

   pListBox->SetRedraw(TRUE);
}

void CXmlToFuncDlg::OnBnClickedBtnDel()
{
   //ɾ��
}

void CXmlToFuncDlg::OnBnClickedBtnEmpty()
{
   //���
   m_lstXml.RemoveAll();
   auto pListBox = (CListBox *)GetDlgItem(IDC_LIST_XML);
   pListBox->ResetContent();
}


void CXmlToFuncDlg::AddXmlToList(CString strFileName)
{
   auto pListBox = (CListBox *)GetDlgItem(IDC_LIST_XML);
   if (NULL != pListBox)
   {
      pListBox->AddString(strFileName);
   }
}

void CXmlToFuncDlg::ParseXml(CString strFilePath)
{
   OutputDebugStringW(_T("    --------parse xml : ") + strFilePath + _T("---------------\n"));
   char szFilePath[MAX_PATH] = {0};
   QLCOMAPI.WCharToMByte(strFilePath,szFilePath,MAX_PATH);

   TiXmlDocument doc;
   //�����ļ�
   doc.LoadFile(szFilePath,TIXML_ENCODING_UTF8);

   TiXmlElement* pRootElement = 0;
   pRootElement = doc.FirstChildElement("TableAtrri");

   if (NULL == pRootElement)
   {
      return;
   }

   auto pItemCount = pRootElement->FirstChildElement("ItemCount");
   int nItemCount = _ttoi(GetTinyXmlNodeString(pItemCount));

   CString strItem = _T("");

   std::vector<int> vec_strmaxlen;
   for (int i = 0;i < 14;++i)
   {
      vec_strmaxlen.push_back(0);
   }

   std::vector<S_INDEX_STR> vec_lineStr;

   for (int nItemIndex = 1;nItemIndex <= nItemCount;++nItemIndex)
   {
      strItem.Format(_T("Item%d"),nItemIndex);

      char szItem[MAX_PATH] = {};
      QLCOMAPI.WCharToMByte(strItem,szItem,MAX_PATH);

      auto pItem = pItemCount->FirstChildElement(szItem);
      if (NULL != pItem)
      {
         //InsertFeildID(tableAtrri,  colIndex++ ,  DB_YARN_IN_cRdsMemo2		, _T("��ע")		,_T(""), DB_VIEW_OTHERRECORDS,TRUE   ); 

         CString strFuncStr = _T(""),strCache = _T("");
         int nItemMaxLength = 0;
         int nCurVecPos = 13;
         auto funcCombineStr = [&strFuncStr,&nCurVecPos,&vec_strmaxlen,&nItemMaxLength](CString strCache){
            CString strCache1 = strFuncStr;
            strFuncStr.Format(_T("%s%s"),strCache,strCache1);

            if (vec_strmaxlen.at(nCurVecPos) < nItemMaxLength)
            {
               vec_strmaxlen.at(nCurVecPos) = nItemMaxLength;
            }
            
         };

         BOOL bHasShow = false;

        /* void InsertFeildID(S_GridCtrl_TableAtrri &tableAtrri, short iColIndex_In,
            CString strColID_In, CString strColShowName_In = _T(""),CString strColDestribution = _T(""),
            CString strTableID_In = _T(""),bool isShow_In = true, bool isEdit_In = true, short iColWidth_In = 75,
            bool isEnableFilter_In = true, BYTE iLock_In = 0, ENUM_COLSUMTYPE enColSumType_In = CB_enum_ColSumType_None,
            BYTE iColFont_In = CB_GRIDCTRL_DEFAULT_FONT, bool IsFontWeight_In = false,
            ENUM_COLSERCHTYPE enSerchType_In = CB_enum_ColSerchType_Contain, CString strColFormat_In=_T(""));//����һ���ֶε������ʽ�� yangjr2017-6-13
*/
         /*
         iColIndex = iColIndex_In;//��ǰ�ֶ��ڱ������ʾ�ڵڼ�
         strColID = strColID_In; //������ 
         strColShowName = strColShowName_In;//��ʾ����
         strColDestribution = strColDestribution_In;
         strTableID = strTableID_In;//�ֶ��������ű��� yangjr 2018/2/27
         isShow = isShow_In;//�Ƿ���ʾ
         isEdit = isEdit_In;//�Ƿ�༭
         iColWidth = iColWidth_In;//���
         isEnableFilter = isEnableFilter_In;//��ǰ�ֶ��Ƿ�����ɸѡ
         iLock = iLock_In;//���� 0������ 1������� 2�����ұ�
         enColSumType = enColSumType_In;
         iColFont = iColFont_In;//�����С
         IsFontWeight = IsFontWeight_In;//�����Ƿ�Ӵ�
         enSerchType = enSerchType_In;//������ʽ 0
         strColFormat = strColFormat_In;//��ʽ��*/

         strCache = ParseElementToStr(pItem,"strColFormat"        ,_T("")     ,_T("")                          ,bHasShow,nItemMaxLength,_T("_T(\"%%\")") );funcCombineStr(strCache);nCurVecPos--;//0 ��ʽ�� 
         strCache = ParseElementToStr(pItem,"enSerchType"         ,_T("0")    ,_T("CB_enum_ColSerchType_Equal"),bHasShow,nItemMaxLength,_T("")           );funcCombineStr(strCache);nCurVecPos--;//0 ���� CB_enum_ColSerchType_Contain  1 ��� CB_enum_ColSerchType_Equal
         strCache = ParseElementToStr(pItem,"IsFontWeight"        ,_T("0")    ,_T("true")                      ,bHasShow,nItemMaxLength,_T("")           );funcCombineStr(strCache);nCurVecPos--;//����Ӵ�
         strCache = ParseElementToStr(pItem,"iColFont"            ,_T("11")   ,_T("")                          ,bHasShow,nItemMaxLength,_T("")           );funcCombineStr(strCache);nCurVecPos--;//�����С
         strCache = ParseElementToStr(pItem,"enColSumType"        ,_T("0")    ,_T("")                          ,bHasShow,nItemMaxLength,_T("")           );funcCombineStr(strCache);nCurVecPos--;//��ͷ�ʽ
         strCache = ParseElementToStr(pItem,"iLock"               ,_T("0")    ,_T("")                          ,bHasShow,nItemMaxLength,_T("")           );funcCombineStr(strCache);nCurVecPos--;//������ʽ
         strCache = ParseElementToStr(pItem,"isEnableFilter"      ,_T("1")    ,_T("")                          ,bHasShow,nItemMaxLength,_T("")           );funcCombineStr(strCache);nCurVecPos--;//�ֶ��Ƿ�����ɸѡ
         strCache = ParseElementToStr(pItem,"iColWidth"           ,_T("75")   ,_T("")                          ,bHasShow,nItemMaxLength,_T("")           );funcCombineStr(strCache);nCurVecPos--;//�п��
         strCache = ParseElementToStr(pItem,"isEdit"              ,_T("1")    ,_T("0")                         ,bHasShow,nItemMaxLength,_T("")           );funcCombineStr(strCache);nCurVecPos--;//�Ƿ�༭
         strCache = ParseElementToStr(pItem,"isShow"              ,_T("1")    ,_T("0")                         ,bHasShow,nItemMaxLength,_T("")           );funcCombineStr(strCache);nCurVecPos--;//�Ƿ���ʾ  
         strCache = ParseElementToStr(pItem,"strTableID"          ,_T("")     ,_T("")                          ,bHasShow,nItemMaxLength,_T("_T(\"%%\")") );funcCombineStr(strCache);nCurVecPos--;//�ֶ��������ű���

         if (bHasShow)
         {
            nItemMaxLength = 6;
            strCache = _T(",_T(\"\")");funcCombineStr(strCache);
         }
         nCurVecPos--;

         strCache = ParseElementToStr(pItem,"strColShowName"      ,_T("")     ,_T("")                          ,bHasShow,nItemMaxLength,_T("_T(\"%%\")"));funcCombineStr(strCache);nCurVecPos--;//����ʾ����  
         strCache = ParseElementToStr(pItem,"strColID"            ,_T("")     ,_T("")                          ,bHasShow,nItemMaxLength,_T("_T(\"%%\")"));funcCombineStr(strCache);nCurVecPos--;//������


         auto pIColIndex = pRootElement->FirstChildElement("iColIndex");
         int niColIndex = _ttoi(GetTinyXmlNodeString(pIColIndex));

         CString strFunc = _T("");
         strFunc.Format(_T("InsertFeildID(tableAtrri,  colIndex++  %s);"),strFuncStr);

         vec_lineStr.push_back(S_INDEX_STR(niColIndex,strFuncStr));
      }
   }

   for (auto it = vec_lineStr.begin();it != vec_lineStr.end();++it)
   {
      it->strColInfo.TrimLeft(',');

      CString strHandlestr = it->strColInfo;
      it->strColInfo = _T("");
      int nPos = strHandlestr.Find(',',0);
      int nForat = 0;
      while(-1 != nPos)
      {
         CString strCompletion = strHandlestr.Left(nPos);
         strHandlestr = strHandlestr.Right(strHandlestr.GetLength() - nPos - 1);

         int nShouldComple = vec_strmaxlen.at(nForat) - GetStringMyLength(strCompletion);
         CString strEmpty = _T("");
         for (int nCompleIndex = 0;nCompleIndex < nShouldComple;++nCompleIndex)
         {
            strEmpty += _T(" ");
         }

         strCompletion += strEmpty;
         it->strColInfo += (_T(",") + strCompletion);
         
         nPos = strHandlestr.Find(',',0);
         ++nForat;
      }
      if (!strHandlestr.IsEmpty())
      {
         int nShouldComple = vec_strmaxlen.at(nForat) - strHandlestr.GetLength();
         CString strEmpty = _T("");
         for (int nCompleIndex = 0;nCompleIndex < nShouldComple;++nCompleIndex)
         {
            strEmpty += _T(" ");
         }
         strHandlestr+= strEmpty;
         it->strColInfo += (_T(",") + strHandlestr);
      }

      CString strFunc = _T("");
      strFunc.Format(_T("InsertFeildID(tableAtrri,  colIndex++  %s);"),it->strColInfo);
      OutputDebugStringW(strFunc);TRACE(_T("\n"));
   }


   BOOL bHasShow = FALSE;
   int nItemMaxLength = 0;
   CString strCache = _T("");

   auto funcAtrriStr = [](CString strCache,const char * name){
      if(!strCache.IsEmpty())
      {
         strCache.TrimLeft(',');
         CString strName(name);
         CString strAtrri = _T("");
         strAtrri.Format(_T("tableAtrri.%s   =  %s;"),strName,strCache);
         OutputDebugString(strAtrri);TRACE(_T("\n"));
      }
   };


   strCache = ParseElementToStr(pRootElement,"isShowTitleFilter"            ,_T("0")     ,_T("")  ,bHasShow,nItemMaxLength,_T("")           );bHasShow = FALSE;nItemMaxLength = 0;funcAtrriStr(strCache,"isShowTitleFilter"          );
   strCache = ParseElementToStr(pRootElement,"isShowSortBar"                ,_T("0")     ,_T("")  ,bHasShow,nItemMaxLength,_T("")           );bHasShow = FALSE;nItemMaxLength = 0;funcAtrriStr(strCache,"isShowSortBar"              );
   strCache = ParseElementToStr(pRootElement,"isAllowSort"                  ,_T("0")     ,_T("")  ,bHasShow,nItemMaxLength,_T("")           );bHasShow = FALSE;nItemMaxLength = 0;funcAtrriStr(strCache,"isAllowSort"                );
   strCache = ParseElementToStr(pRootElement,"isWholeRowSelect"             ,_T("0")     ,_T("")  ,bHasShow,nItemMaxLength,_T("")           );bHasShow = FALSE;nItemMaxLength = 0;funcAtrriStr(strCache,"isWholeRowSelect"           );
   strCache = ParseElementToStr(pRootElement,"isShowSumBar"                 ,_T("0")     ,_T("")  ,bHasShow,nItemMaxLength,_T("")           );bHasShow = FALSE;nItemMaxLength = 0;funcAtrriStr(strCache,"isShowSumBar"               );
   strCache = ParseElementToStr(pRootElement,"isMultiRowSelect"             ,_T("0")     ,_T("")  ,bHasShow,nItemMaxLength,_T("")           );bHasShow = FALSE;nItemMaxLength = 0;funcAtrriStr(strCache,"isMultiRowSelect"           );
   strCache = ParseElementToStr(pRootElement,"IsMultiRowSelectNoLoseFocus"  ,_T("0")     ,_T("")  ,bHasShow,nItemMaxLength,_T("")           );bHasShow = FALSE;nItemMaxLength = 0;funcAtrriStr(strCache,"IsMultiRowSelectNoLoseFocus");
   strCache = ParseElementToStr(pRootElement,"DataRowHeight"                ,_T("24")    ,_T("")  ,bHasShow,nItemMaxLength,_T("")           );bHasShow = FALSE;nItemMaxLength = 0;funcAtrriStr(strCache,"nDataRowHeight"             );
   strCache = ParseElementToStr(pRootElement,"iDataRowFont"                 ,_T("11")    ,_T("")  ,bHasShow,nItemMaxLength,_T("")           );bHasShow = FALSE;nItemMaxLength = 0;funcAtrriStr(strCache,"iDataRowFont"               );
   strCache = ParseElementToStr(pRootElement,"isEnableDragCol"              ,_T("1")     ,_T("")  ,bHasShow,nItemMaxLength,_T("")           );bHasShow = FALSE;nItemMaxLength = 0;funcAtrriStr(strCache,"isEnableDragCol"            );
   strCache = ParseElementToStr(pRootElement,"isEnableEdit"                 ,_T("1")     ,_T("")  ,bHasShow,nItemMaxLength,_T("")           );bHasShow = FALSE;nItemMaxLength = 0;funcAtrriStr(strCache,"isEnableEdit"               );
   strCache = ParseElementToStr(pRootElement,"isPrintHengXiang"             ,_T("0")     ,_T("")  ,bHasShow,nItemMaxLength,_T("")           );bHasShow = FALSE;nItemMaxLength = 0;funcAtrriStr(strCache,"isPrintHengXiang"           );
   strCache = ParseElementToStr(pRootElement,"strUpdateTime"                ,_T("")      ,_T("")  ,bHasShow,nItemMaxLength,_T("_T(\"%%\")") );bHasShow = FALSE;nItemMaxLength = 0;funcAtrriStr(strCache,"strUpdateTime"              );
   strCache = ParseElementToStr(pRootElement,"isNoUpdateServerStyle"        ,_T("0")     ,_T("")  ,bHasShow,nItemMaxLength,_T("")           );bHasShow = FALSE;nItemMaxLength = 0;funcAtrriStr(strCache,"isNoUpdateServerStyle"      );



   /*
   tableAtrri��Ĭ������
   isShowTitleFilter             = false;
   isShowSortBar                 = false;
   isAllowSort                   = false;
   isWholeRowSelect              = false;
   isShowSumBar                  = false;
   isMultiRowSelect              = false;
   IsMultiRowSelectNoLoseFocus   = false;
   nDataRowHeight                = CB_GRIDCTRL_DEFAULT_ROWHEIGHT;
   iDataRowFont                  = CB_GRIDCTRL_DEFAULT_FONT;
   isEnableDragCol               = true;
   isEnableEdit                  = true;		//���Ƿ�ɱ༭		by WangZY 2017/06/15
   isPrintHengXiang              = false;
   strUpdateTime                 = _T("");
   isNoUpdateServerStyle         = false;
   */

}

int CXmlToFuncDlg::GetStringMyLength(const CString &sText)
{
   int nTotalCount = 0; //ȫ����2��
   for(LPCTSTR p= sText; p != NULL && p[0] != 0; p = CharNext(p))
   {
      if(p[0] > 0 && p[0] <= 127)
      {
         ++nTotalCount;
      }
      else 
      {
         //����������
         nTotalCount += 2;
      }
   }

   return nTotalCount;
}
