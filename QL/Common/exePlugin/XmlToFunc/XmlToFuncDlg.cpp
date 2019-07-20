
// XmlToFuncDlg.cpp : 实现文件
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

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CXmlToFuncDlg 对话框




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
   string sName = pElement->Attribute(name);//部位名称

   strRet = theApp.UTF8_TO_UNICODE(sName);
   return strRet;
}

CString CXmlToFuncDlg::ParseElementToStr(__in TiXmlElement * pSrcElement,
   __in const char * name ,
   __in const CString & strDefaultValue,/*默认的值 */
   __in const CString & strRetValue ,/* 如果需要返回时应该返回的值 */
   __inout BOOL & bHasShow ,/*之前已经有过显示了 */
   __inout int & nMaxLength, /*返回值的最大数据*/
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


// CXmlToFuncDlg 消息处理程序

BOOL CXmlToFuncDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CXmlToFuncDlg::OnPaint()
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
   //添加
   CString strFileName = _T("");
   CFileDialog fileDlg(true);

   fileDlg.m_ofn.lpstrFilter = LPCTSTR(_T("XML文件(*.xml)\0*.xml\0\0"));
   fileDlg.m_ofn.lpstrTitle = LPCTSTR(_T("选择配置文件"));
   //fileDlg.m_ofn.nFilterIndex = 7;
   fileDlg.m_ofn.Flags |= OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT|OFN_FILEMUSTEXIST;

   //2017/04/10 zhangt 限制最大文件个数500
   fileDlg.m_ofn.nMaxFile = 10*MAX_PATH;
   TCHAR *ch = new TCHAR[fileDlg.m_ofn.nMaxFile];
   fileDlg.m_ofn.lpstrFile = ch;
   ZeroMemory(fileDlg.m_ofn.lpstrFile,sizeof(TCHAR)*fileDlg.m_ofn.nMaxFile);
   //2017/04/10_end


   if(fileDlg.DoModal() != IDOK)
   {
      delete[] ch;//释放 new 变量
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

         //将文件添加到列表中去
         AddXmlToList(PathFindFileName(strFileName));
      }
   }
   delete[] ch;//释放 new 变量

   pListBox->SetRedraw(TRUE);
}

void CXmlToFuncDlg::OnBnClickedBtnDel()
{
   //删除
}

void CXmlToFuncDlg::OnBnClickedBtnEmpty()
{
   //清空
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
   //加载文件
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
         //InsertFeildID(tableAtrri,  colIndex++ ,  DB_YARN_IN_cRdsMemo2		, _T("备注")		,_T(""), DB_VIEW_OTHERRECORDS,TRUE   ); 

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
            ENUM_COLSERCHTYPE enSerchType_In = CB_enum_ColSerchType_Contain, CString strColFormat_In=_T(""));//插入一个字段到表格样式中 yangjr2017-6-13
*/
         /*
         iColIndex = iColIndex_In;//当前字段在表格中显示在第几
         strColID = strColID_In; //列名称 
         strColShowName = strColShowName_In;//显示名称
         strColDestribution = strColDestribution_In;
         strTableID = strTableID_In;//字段是在哪张表中 yangjr 2018/2/27
         isShow = isShow_In;//是否显示
         isEdit = isEdit_In;//是否编辑
         iColWidth = iColWidth_In;//宽度
         isEnableFilter = isEnableFilter_In;//当前字段是否允许筛选
         iLock = iLock_In;//锁定 0不锁定 1锁定左侧 2锁定右边
         enColSumType = enColSumType_In;
         iColFont = iColFont_In;//字体大小
         IsFontWeight = IsFontWeight_In;//字体是否加粗
         enSerchType = enSerchType_In;//检索方式 0
         strColFormat = strColFormat_In;//格式化*/

         strCache = ParseElementToStr(pItem,"strColFormat"        ,_T("")     ,_T("")                          ,bHasShow,nItemMaxLength,_T("_T(\"%%\")") );funcCombineStr(strCache);nCurVecPos--;//0 格式化 
         strCache = ParseElementToStr(pItem,"enSerchType"         ,_T("0")    ,_T("CB_enum_ColSerchType_Equal"),bHasShow,nItemMaxLength,_T("")           );funcCombineStr(strCache);nCurVecPos--;//0 包含 CB_enum_ColSerchType_Contain  1 相等 CB_enum_ColSerchType_Equal
         strCache = ParseElementToStr(pItem,"IsFontWeight"        ,_T("0")    ,_T("true")                      ,bHasShow,nItemMaxLength,_T("")           );funcCombineStr(strCache);nCurVecPos--;//字体加粗
         strCache = ParseElementToStr(pItem,"iColFont"            ,_T("11")   ,_T("")                          ,bHasShow,nItemMaxLength,_T("")           );funcCombineStr(strCache);nCurVecPos--;//字体大小
         strCache = ParseElementToStr(pItem,"enColSumType"        ,_T("0")    ,_T("")                          ,bHasShow,nItemMaxLength,_T("")           );funcCombineStr(strCache);nCurVecPos--;//求和方式
         strCache = ParseElementToStr(pItem,"iLock"               ,_T("0")    ,_T("")                          ,bHasShow,nItemMaxLength,_T("")           );funcCombineStr(strCache);nCurVecPos--;//锁定方式
         strCache = ParseElementToStr(pItem,"isEnableFilter"      ,_T("1")    ,_T("")                          ,bHasShow,nItemMaxLength,_T("")           );funcCombineStr(strCache);nCurVecPos--;//字段是否允许筛选
         strCache = ParseElementToStr(pItem,"iColWidth"           ,_T("75")   ,_T("")                          ,bHasShow,nItemMaxLength,_T("")           );funcCombineStr(strCache);nCurVecPos--;//列宽度
         strCache = ParseElementToStr(pItem,"isEdit"              ,_T("1")    ,_T("0")                         ,bHasShow,nItemMaxLength,_T("")           );funcCombineStr(strCache);nCurVecPos--;//是否编辑
         strCache = ParseElementToStr(pItem,"isShow"              ,_T("1")    ,_T("0")                         ,bHasShow,nItemMaxLength,_T("")           );funcCombineStr(strCache);nCurVecPos--;//是否显示  
         strCache = ParseElementToStr(pItem,"strTableID"          ,_T("")     ,_T("")                          ,bHasShow,nItemMaxLength,_T("_T(\"%%\")") );funcCombineStr(strCache);nCurVecPos--;//字段是在哪张表中

         if (bHasShow)
         {
            nItemMaxLength = 6;
            strCache = _T(",_T(\"\")");funcCombineStr(strCache);
         }
         nCurVecPos--;

         strCache = ParseElementToStr(pItem,"strColShowName"      ,_T("")     ,_T("")                          ,bHasShow,nItemMaxLength,_T("_T(\"%%\")"));funcCombineStr(strCache);nCurVecPos--;//列显示名称  
         strCache = ParseElementToStr(pItem,"strColID"            ,_T("")     ,_T("")                          ,bHasShow,nItemMaxLength,_T("_T(\"%%\")"));funcCombineStr(strCache);nCurVecPos--;//列名称


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
   tableAtrri的默认属性
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
   isEnableEdit                  = true;		//表是否可编辑		by WangZY 2017/06/15
   isPrintHengXiang              = false;
   strUpdateTime                 = _T("");
   isNoUpdateServerStyle         = false;
   */

}

int CXmlToFuncDlg::GetStringMyLength(const CString &sText)
{
   int nTotalCount = 0; //全角算2个
   for(LPCTSTR p= sText; p != NULL && p[0] != 0; p = CharNext(p))
   {
      if(p[0] > 0 && p[0] <= 127)
      {
         ++nTotalCount;
      }
      else 
      {
         //是中文文字
         nTotalCount += 2;
      }
   }

   return nTotalCount;
}
