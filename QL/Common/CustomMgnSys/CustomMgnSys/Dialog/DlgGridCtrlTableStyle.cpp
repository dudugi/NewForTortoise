// DlgGridCtrlTableStyle.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "../CustomMgnSys.h"
#include "DlgGridCtrlTableStyle.h"

//#include "DBDataColSet.h"
#include "DlgBCGGrid.h"
#include <algorithm>
#include "CDataTableAttrFileAndFieldDefine.h"


// CDlgGridCtrlTableStyle �Ի���
#define ROWHEGIHT_MIN 20
#define ROWHEGIHT_MAX 200

#define FONT_MIN 9
#define FONT_MAX 100

IMPLEMENT_DYNAMIC(CDlgGridCtrlTableStyle, CBCGPDialog)

CDlgGridCtrlTableStyle::CDlgGridCtrlTableStyle(CWnd* pParent /*=NULL*/)
   : CBCGPDialog(CDlgGridCtrlTableStyle::IDD, pParent)
   , m_iRowHeight(0)
   , m_iFont(0)
   , m_iPageRows(50)
   ,m_backupPageRows(50)
{
   m_pDlgComGrid = NULL;

   //m_strDBTableName = _T("");
   m_bHasAddShowField = FALSE;			//�Ƿ�����������ʾ��	by WangZY 2018/02/01
}

CDlgGridCtrlTableStyle::~CDlgGridCtrlTableStyle()
{
   if (nullptr != m_pDlgComGrid)
   {
      delete m_pDlgComGrid;
      m_pDlgComGrid = nullptr;
   }
}

void CDlgGridCtrlTableStyle::DoDataExchange(CDataExchange* pDX)
{
   CBCGPDialog::DoDataExchange(pDX);
   DDX_Control(pDX, IDC_CHECK_SHOW_FILTERBAR, m_CheckShowFilterBar);
   DDX_Control(pDX, IDC_CHECK_ALLOWSORT, m_CheckAllowSort);
   DDX_Control(pDX, IDC_CHECK_WHOLEROWSELECT, m_CheckWholeRowSelect);
   DDX_Control(pDX, IDC_CHECK_SHOW_TOTALBAR, m_CheckShowTotalBar);
   DDX_Control(pDX, IDC_CHECK_MULTILINESELECT, m_CheckMultiLineSelect);
   DDX_Control(pDX, IDC_CHECK_MULTILINESELECT_NOFOCUS, m_CheckMultiLineSelectNoLoseFocus);
   DDX_Control(pDX, IDC_EDIT_ROWHEIGHT, m_EditRowHeight);
   DDX_Control(pDX, IDC_EDIT_FONT, m_EditFont);
   DDX_Control(pDX, IDC_CHECK_ALLSHOW, m_CheckAllShow);
   DDX_Control(pDX, IDC_CHECK_ALLEDIT, m_CheckAllEdit);
   DDX_Control(pDX, IDC_CHECK_TITLEFILTER, m_CheckTitleFilter);
   DDX_Control(pDX, IDC_SPIN_ROW_HEIGHT, m_SpinRowHeight);
   DDX_Control(pDX, IDC_SPIN_FONT, m_SpinFont);
   DDX_Text(pDX, IDC_EDIT_ROWHEIGHT, m_iRowHeight);
   DDX_Text(pDX, IDC_EDIT_FONT, m_iFont);
   DDX_Control(pDX, IDC_CHECK_ISENABLEDRAGCOL, m_Check_IsEnableDragCol);
   DDX_Control(pDX, IDC_CHECK_PRINTHEXIANG, m_CheckPrintHeXiang);
   DDX_Control(pDX, IDC_BTN_INITSYSSTYLE, m_BTN_InitSysStyle);
   DDX_Control(pDX, IDC_BTN_INITUSERSTYLE, m_BTN_InitUserStyle);
   DDX_Control(pDX, IDC_CHECK_UPDATESERVERSTYLE, m_Check_UpdateServerStyle);
   DDX_Control(pDX, IDC_EDIT_PAGEROWS, m_Edit_PageRows);
   DDX_Text(pDX, IDC_EDIT_PAGEROWS, m_iPageRows);
}


BEGIN_MESSAGE_MAP(CDlgGridCtrlTableStyle, CBCGPDialog)
   ON_BN_CLICKED(IDOK, &CDlgGridCtrlTableStyle::OnBnClickedOk)
   ON_BN_CLICKED(IDC_CHECK_ALLSHOW, &CDlgGridCtrlTableStyle::OnBnClickedCheckAllshow)
   ON_BN_CLICKED(IDC_CHECK_ALLEDIT, &CDlgGridCtrlTableStyle::OnBnClickedCheckAlledit)
   ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_ROW_HEIGHT, &CDlgGridCtrlTableStyle::OnDeltaposSpinRowHeight)
   ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_FONT, &CDlgGridCtrlTableStyle::OnDeltaposSpinFont)
   ON_EN_KILLFOCUS(IDC_EDIT_ROWHEIGHT, &CDlgGridCtrlTableStyle::OnEnKillfocusEditRowheight)
   ON_EN_KILLFOCUS(IDC_EDIT_FONT, &CDlgGridCtrlTableStyle::OnEnKillfocusEditFont)
   ON_BN_CLICKED(IDC_BUTTON_SAVEAS, &CDlgGridCtrlTableStyle::OnBnClickedButtonSaveas)
   ON_BN_CLICKED(IDC_BTN_INITSYSSTYLE, &CDlgGridCtrlTableStyle::OnBnClickedBtnInitsysstyle)
   ON_BN_CLICKED(IDC_BTN_INITUSERSTYLE, &CDlgGridCtrlTableStyle::OnBnClickedBtnInituserstyle)
   //ON_BN_CLICKED(IDC_BTN_READCOLNAME, &CDlgGridCtrlTableStyle::OnBnClickedBtnReadcolname)
   ON_BN_CLICKED(IDC_CHECK_ALREADY_SHOW, &CDlgGridCtrlTableStyle::OnBnClickedCheckShow)
   ON_BN_CLICKED(IDC_CHECK_NO_SHOW, &CDlgGridCtrlTableStyle::OnBnClickedCheckShow)
END_MESSAGE_MAP()

void CDlgGridCtrlTableStyle::InitDlg()
{
   m_CheckShowFilterBar.SetCheck(m_TableAtrriData.isShowSortBar);
   m_CheckAllowSort.SetCheck(m_TableAtrriData.isAllowSort);
   m_CheckWholeRowSelect.SetCheck(m_TableAtrriData.isWholeRowSelect);
   m_CheckShowTotalBar.SetCheck(m_TableAtrriData.isShowSumBar);
   m_CheckMultiLineSelect.SetCheck(m_TableAtrriData.isMultiRowSelect);
   m_CheckMultiLineSelectNoLoseFocus.SetCheck(m_TableAtrriData.IsMultiRowSelectNoLoseFocus);
   m_iRowHeight = m_TableAtrriData.nDataRowHeight;
   m_iFont = m_TableAtrriData.iDataRowFont;
   m_CheckAllShow.SetCheck(0);
   m_CheckAllEdit.SetCheck(0);
   m_CheckTitleFilter.SetCheck(m_TableAtrriData.isShowTitleFilter);
   m_SpinFont.SetRange(FONT_MIN,FONT_MAX);
   m_SpinFont.SetBuddy(&m_EditFont);
   m_SpinRowHeight.SetRange(ROWHEGIHT_MIN,ROWHEGIHT_MAX);
   m_SpinRowHeight.SetBuddy(&m_EditRowHeight);
   m_Check_IsEnableDragCol.SetCheck(m_TableAtrriData.isEnableDragCol);//��λ���ܷ��϶� yangjr 2017-6-13
   m_CheckPrintHeXiang.SetCheck(m_TableAtrriData.isPrintHengXiang);
   m_Check_UpdateServerStyle.SetCheck(!m_TableAtrriData.isNoUpdateServerStyle);
   m_CheckShowFilterBar.SetCheck(m_TableAtrriData.isShowSortBar);
   m_iPageRows = m_TableAtrriData.iPageRows;
   if (m_iPageRows<50)
   {
      m_iPageRows = 50;
   }
   
   UpdateData(FALSE);
}
// CDlgGridCtrlTableStyle ��Ϣ�������
BOOL CDlgGridCtrlTableStyle::OnInitDialog()
{
   CBCGPDialog::OnInitDialog();

   InitGrid();
   InitDlg();	
   m_backupPageRows = m_iPageRows;

   // CString strIsBeta;
   //theApp.GetIniKeyValue(NAME_SECTION,NAME_KEY_CLOSEBETA,strIsBeta);
   /*if (theApp.m_objSysSetData.m_bBetaVer)
   {
   GetDlgItem(IDC_BUTTON_SAVEAS)->ShowWindow(SW_SHOW);
   m_BTN_InitSysStyle.ShowWindow(SW_SHOW);
   //m_BTN_InitUserStyle.ShowWindow(SW_SHOW);
   GetDlgItem(IDC_BTN_READCOLNAME)->ShowWindow(SW_SHOW);
   }else*/ //�⼸����ťȫ������
   {
      GetDlgItem(IDC_BUTTON_SAVEAS)->ShowWindow(SW_HIDE);
      m_BTN_InitSysStyle.ShowWindow(SW_HIDE);
      //m_BTN_InitUserStyle.ShowWindow(SW_HIDE);
      GetDlgItem(IDC_BTN_READCOLNAME)->ShowWindow(SW_HIDE);
   }

   //GetDlgItem(IDC_BTN_READCOLNAME)->ShowWindow(SW_HIDE);
   //m_BTN_InitSysStyle.ShowWindow(SW_HIDE);
   m_BTN_InitUserStyle.ShowWindow(SW_SHOW);
   //���δ���ñ����ʽ����·����ʱ�򣬱�������ʽ����������		by WangZY 2017/12/12
   /*if (m_strFileName.IsEmpty())
   {
   GetDlgItem(IDOK)->ShowWindow(SW_HIDE);
   }*/

   return TRUE;
}

void CDlgGridCtrlTableStyle::CreateTableAttri( CString strFileName,CStringList& strlFieldName )
{
   m_strFileName = strFileName;
   CGridCtrlTableAttributeOp::Instance()->CreateEmptyFieldAttri(m_TableAtrriData,strlFieldName);
}

//�ж��Ƿ���������ʾ�ֶ�		by WangZY 2018/02/01
BOOL CDlgGridCtrlTableStyle::HasAddShowField()
{
   return m_bHasAddShowField;
}

void CDlgGridCtrlTableStyle::OnBnClickedOk()
{
   // TODO: �ڴ���ӿؼ�֪ͨ����������
   GetDataFromDlg();
   BOOL ret = CGridCtrlTableAttributeOp::Instance()->WriteTableAttri(m_strFileName,m_TableAtrriData);
   if (!ret)
   {
      AfxMessageBox(_T("��������ʽʧ�ܣ�"));
   }
   if (!m_bHasAddShowField)
   {
      //���ʼ��¼��ʾ���ֶ����ȶ�		by WangZY 2018/02/01
      for (auto it=m_TableAtrriData.mapFeildAtrri.begin();
         it!=m_TableAtrriData.mapFeildAtrri.end(); ++it)
      {
         if (it->second.isShow)
         {
            auto itAddShow = std::find(m_vecOldShowFieldId.begin(),
               m_vecOldShowFieldId.end(),it->first);
            if (itAddShow == m_vecOldShowFieldId.end())
            {
               m_bHasAddShowField = TRUE;

               break;
            }
         }
         else
         {
            auto itAddShow = std::find(m_vecOldShowFieldId.begin(),
               m_vecOldShowFieldId.end(),it->first);
            if (itAddShow != m_vecOldShowFieldId.end())
            {
               m_bHasAddShowField = TRUE;

               break;
            }
         }
      }
   }

   if (!m_bHasAddShowField)
   {
      if (m_backupPageRows != m_iPageRows)
      {
         m_bHasAddShowField = TRUE;//ÿҳ�����б仯��֪ͨ����ˢ�½��� yangjr 2018/7/6
      }
   }

   CBCGPDialog::OnOK();
}

void CDlgGridCtrlTableStyle::SetTableAttriFileNameAndData(CString strFileName,const S_GridCtrl_TableAttri &tableAtrriData/*,CString strDBTableName=_T("")*/)
{
   strFileName.Trim();
   //strDBTableName.Trim();

   m_strFileName = strFileName;
   m_TableAtrriData = tableAtrriData;
   //m_strDBTableName = strDBTableName;

   //��¼��ʼ��ʾ���ֶ�		by WangZY 2018/02/01
   m_vecOldShowFieldId.clear();
   for (auto it=m_TableAtrriData.mapFeildAtrri.begin();
      it!=m_TableAtrriData.mapFeildAtrri.end(); ++it)
   {
      if (it->second.isShow)
      {
         m_vecOldShowFieldId.push_back(it->first);
      }
   }
}

void CDlgGridCtrlTableStyle::GetMapData(MAP_GridCtrl_AllData  &map_all_data)
{
#pragma region ����������������
   //����������������
   shared_ptr<vector<CString>> sptr_lockFieldData(new(vector<CString>));
   sptr_lockFieldData->push_back(_T("������"));
   sptr_lockFieldData->push_back(_T("���������"));
   sptr_lockFieldData->push_back(_T("�������Ҳ�"));
#pragma endregion ����������������

#pragma region ��ʽ��������������
   //��ʽ��������������
   shared_ptr<vector<CString>> sptr_formatFieldData(new(vector<CString>));
   sptr_formatFieldData->push_back(_T(""));
   sptr_formatFieldData->push_back(_T("yyy-MM-dd"));
   sptr_formatFieldData->push_back(_T("HH-mm-ss"));
   sptr_formatFieldData->push_back(_T("N0"));
   sptr_formatFieldData->push_back(_T("N1"));
   sptr_formatFieldData->push_back(_T("N2"));
   sptr_formatFieldData->push_back(_T("N3"));
   sptr_formatFieldData->push_back(_T("N4"));
   sptr_formatFieldData->push_back(_T("#"));
   sptr_formatFieldData->push_back(_T("#.0"));
#pragma endregion ��ʽ��������������

#pragma region �ϼƷ�ʽ�е���������
   //�ϼƷ�ʽ�е���������
   shared_ptr<vector<CString>> sptr_sumTypeFieldData(new(vector<CString>));
   sptr_sumTypeFieldData->push_back(_T("��"));
   sptr_sumTypeFieldData->push_back(_T("���"));
   sptr_sumTypeFieldData->push_back(_T("����"));
   sptr_sumTypeFieldData->push_back(_T("��ƽ��ֵ"));
#pragma endregion �ϼƷ�ʽ�е���������

#pragma region �����е���������
   //�����е���������
   shared_ptr<vector<CString>> sptr_searchFieldData(new(vector<CString>));
   sptr_searchFieldData->push_back(_T("����"));
   sptr_searchFieldData->push_back(_T("���"));
#pragma endregion �����е���������	

#pragma region �����С�е���������
   //�����С�е���������
   shared_ptr<vector<CString>> sptr_fontFieldData(new(vector<CString>));
   sptr_fontFieldData->push_back(_T("9"));
   sptr_fontFieldData->push_back(_T("10"));
   sptr_fontFieldData->push_back(_T("11"));
   sptr_fontFieldData->push_back(_T("12"));
   sptr_fontFieldData->push_back(_T("13"));
   sptr_fontFieldData->push_back(_T("14"));
   sptr_fontFieldData->push_back(_T("15"));
#pragma endregion �����С�е���������	


   //��ǰ����ı������
   //��ȡ���ݵ��ض����ݽṹ��

   int rowIndex=0;
   for (MAP_GridCtrl_FieldPos::iterator iterPos=m_TableAtrriData.mapTableFeildPos.begin();
      iterPos!=m_TableAtrriData.mapTableFeildPos.end();++iterPos,++rowIndex)
   {
      MAP_GridCtrl_FieldAtrri::iterator iterFieldAtrri =  m_TableAtrriData.mapFeildAtrri.find(iterPos->second);
      ASSERT(iterFieldAtrri!=m_TableAtrriData.mapFeildAtrri.end());

      MAP_GridCtrl_RowData map_row_data;              
      S_GridCtrl_FieldData s_filed_data0;
      s_filed_data0.strValue = iterFieldAtrri->second.strColID;
      s_filed_data0.fieldDataType = CB_enum_FieldData_CString;
      s_filed_data0.fieldCtrlType = CB_enum_FieldCtrl_Text;      
      map_row_data.insert(make_pair(TABLESTYLE_strColID,s_filed_data0));	//������

      S_GridCtrl_FieldData s_filed_data1;
      s_filed_data1.strValue = iterFieldAtrri->second.strColShowName;
      s_filed_data1.fieldDataType = CB_enum_FieldData_CString;
      s_filed_data1.fieldCtrlType = CB_enum_FieldCtrl_Text;      
      map_row_data.insert(make_pair(TABLESTYLE_strColShowName,s_filed_data1));	//��ʾ����

      S_GridCtrl_FieldData s_filed_data2;
      s_filed_data2.strValue.Format(_T("%d"),iterFieldAtrri->second.iColWidth);
      s_filed_data2.fieldDataType = CB_enum_FieldData_Int;
      s_filed_data2.fieldCtrlType = CB_enum_FieldCtrl_Text;      
      map_row_data.insert(make_pair(TABLESTYLE_iColWidth,s_filed_data2));	//���

      S_GridCtrl_FieldData s_filed_data3;
      s_filed_data3.strValue.Format(_T("%d"),iterFieldAtrri->second.isShow);
      s_filed_data3.fieldDataType = CB_enum_FieldData_Int;
      s_filed_data3.fieldCtrlType = CB_enum_FieldCtrl_Checkbox;      
      map_row_data.insert(make_pair(TABLESTYLE_isShow,s_filed_data3));	//�Ƿ���ʾ

      S_GridCtrl_FieldData s_filed_data4;
      s_filed_data4.strValue.Format(_T("%d"),iterFieldAtrri->second.isEdit);
      s_filed_data4.fieldDataType = CB_enum_FieldData_Int;
      s_filed_data4.fieldCtrlType = CB_enum_FieldCtrl_Checkbox;      
      map_row_data.insert(make_pair(TABLESTYLE_isEdit,s_filed_data4));	//�Ƿ�༭

      S_GridCtrl_FieldData s_filed_data5;
      s_filed_data5.fieldDataType = CB_enum_FieldData_CString;
      s_filed_data5.fieldCtrlType = CB_enum_FieldCtrl_NormalCombox; 
      s_filed_data5.sptr_normalComboxData = sptr_lockFieldData;
      //s_filed_data5.normalComboxData.push_back(_T("������"));
      //s_filed_data5.normalComboxData.push_back(_T("���������"));
      //s_filed_data5.normalComboxData.push_back(_T("�������Ҳ�"));
      BYTE &iLock = iterFieldAtrri->second.iLock;
      if (iLock>=s_filed_data5.sptr_normalComboxData->size())
      {
         iLock =0;
      }
      s_filed_data5.strValue = s_filed_data5.sptr_normalComboxData->at(iLock);
      map_row_data.insert(make_pair(TABLESTYLE_iLock,s_filed_data5));	//������

      S_GridCtrl_FieldData s_filed_data6;
      s_filed_data6.strValue = iterFieldAtrri->second.strColFormat;
      s_filed_data6.fieldDataType = CB_enum_FieldData_CString;
      s_filed_data6.fieldCtrlType = CB_enum_FieldCtrl_NormalCombox;  
      s_filed_data6.sptr_normalComboxData = sptr_formatFieldData;
      //s_filed_data6.normalComboxData.push_back(_T(""));
      //s_filed_data6.normalComboxData.push_back(_T("yyy-MM-dd"));
      //s_filed_data6.normalComboxData.push_back(_T("HH-mm-ss"));
      //s_filed_data6.normalComboxData.push_back(_T("N0"));
      //s_filed_data6.normalComboxData.push_back(_T("N1"));
      //s_filed_data6.normalComboxData.push_back(_T("N2"));
      //s_filed_data6.normalComboxData.push_back(_T("N3"));
      //s_filed_data6.normalComboxData.push_back(_T("N4"));
      //s_filed_data6.normalComboxData.push_back(_T("#"));
      //s_filed_data6.normalComboxData.push_back(_T("#.0"));
      map_row_data.insert(make_pair(TABLESTYLE_strColFormat,s_filed_data6));	//��ʽ��

      S_GridCtrl_FieldData s_filed_data7;      
      s_filed_data7.fieldDataType = CB_enum_FieldData_CString;
      s_filed_data7.fieldCtrlType = CB_enum_FieldCtrl_NormalCombox;
      s_filed_data7.sptr_normalComboxData = sptr_sumTypeFieldData;
      //s_filed_data7.normalComboxData.push_back(_T("��"));
      //s_filed_data7.normalComboxData.push_back(_T("���"));
      //s_filed_data7.normalComboxData.push_back(_T("����"));
      //s_filed_data7.normalComboxData.push_back(_T("��ƽ��ֵ"));
      s_filed_data7.strValue = s_filed_data7.sptr_normalComboxData->at(iterFieldAtrri->second.enColSumType);
      map_row_data.insert(make_pair(TABLESTYLE_enColSumType,s_filed_data7));	//�ϼƷ�ʽ

      S_GridCtrl_FieldData s_filed_data8;
      s_filed_data8.fieldDataType = CB_enum_FieldData_CString;
      s_filed_data8.fieldCtrlType = CB_enum_FieldCtrl_NormalCombox; 
      s_filed_data8.sptr_normalComboxData = sptr_searchFieldData;
      //s_filed_data8.normalComboxData.push_back(_T("����"));
      //s_filed_data8.normalComboxData.push_back(_T("���"));
      s_filed_data8.strValue = s_filed_data8.sptr_normalComboxData->at((int)iterFieldAtrri->second.enSerchType);
      map_row_data.insert(make_pair(TABLESTYLE_enSerchType,s_filed_data8));	//������ʽ

      S_GridCtrl_FieldData s_filed_data9;
      s_filed_data9.strValue.Format(_T("%d"),iterFieldAtrri->second.iColFont);
      s_filed_data9.fieldDataType = CB_enum_FieldData_CString;
      s_filed_data9.fieldCtrlType = CB_enum_FieldCtrl_NormalCombox;
      s_filed_data9.sptr_normalComboxData = sptr_fontFieldData;
      //s_filed_data9.normalComboxData.push_back(_T("9"));
      //s_filed_data9.normalComboxData.push_back(_T("10"));
      //s_filed_data9.normalComboxData.push_back(_T("11"));
      //s_filed_data9.normalComboxData.push_back(_T("12"));
      //s_filed_data9.normalComboxData.push_back(_T("13"));
      //s_filed_data9.normalComboxData.push_back(_T("14"));
      //s_filed_data9.normalComboxData.push_back(_T("15"));
      map_row_data.insert(make_pair(TABLESTYLE_iColFont,s_filed_data9));	//�����С

      S_GridCtrl_FieldData s_filed_data10;
      s_filed_data10.strValue.Format(_T("%d"),iterFieldAtrri->second.IsFontWeight);
      s_filed_data10.fieldDataType = CB_enum_FieldData_Int;
      s_filed_data10.fieldCtrlType = CB_enum_FieldCtrl_Checkbox;      
      map_row_data.insert(make_pair(TABLESTYLE_IsFontWeight,s_filed_data10));	//����Ӵ�

      S_GridCtrl_FieldData s_filed_data11;
      s_filed_data11.strValue.Format(_T("%d"),iterFieldAtrri->second.isEnableFilter);
      s_filed_data11.fieldDataType = CB_enum_FieldData_Int;
      s_filed_data11.fieldCtrlType = CB_enum_FieldCtrl_Checkbox;      
      map_row_data.insert(make_pair(TABLESTYLE_isEnableFilter,s_filed_data11));	//�ܷ�ɸѡ

      S_GridCtrl_FieldData s_filed_data12;
      s_filed_data12.strValue = iterFieldAtrri->second.strColDestribution;
      s_filed_data12.fieldDataType = CB_enum_FieldData_CString;
      s_filed_data12.fieldCtrlType = CB_enum_FieldCtrl_Text;      
      map_row_data.insert(make_pair(TABLESTYLE_strColDestribution,s_filed_data12));	//������

      S_GridCtrl_FieldData s_filed_data13;
      s_filed_data13.strValue = iterFieldAtrri->second.strTableID;
      s_filed_data13.fieldDataType = CB_enum_FieldData_CString;
      s_filed_data13.fieldCtrlType = CB_enum_FieldCtrl_Text;      
      map_row_data.insert(make_pair(TABLESTYLE_strTableID,s_filed_data13));	//������

      map_all_data.insert(make_pair(rowIndex,map_row_data));
   }
}

void CDlgGridCtrlTableStyle::InitGrid()
{
   //��ǰ����ı������
   S_GridCtrl_TableAttri tableAttri;
   BOOL ret = CGridCtrlTableAttributeOp::Instance()->ReadTableAttri(TABLE_TABLESTYLE,tableAttri,TRUE);

   //2017/12/12 zhangt ��ǰ���ݿ��ֶ����ļ����ֶν��жԱ�
   /*	if (!m_strDBTableName.IsEmpty())
   {
   CString strSQL = _T("");
   strSQL.Format(_T("sp_mshelpcolumns %s"),m_strDBTableName);

   CStringArray arr;
   theApp.m_pADOConn->GetRecordSet(strSQL);
   while (!theApp.m_pADOConn->adoEOF())
   {
   CString strFileName = theApp.m_pADOConn->GetValueString(_T("col_name"));		//������
   arr.Add(strFileName);
   theApp.m_pADOConn->MoveNext();
   }


   S_GridCtrl_tableAttri tmpTableAtrriData;
   int nCount = m_TableAtrriData.mapTableFeildPos.size();
   tmpTableAtrriData = m_TableAtrriData;
   //ѭ���Ա�
   for (int i=0;i<arr.GetCount();i++)
   {
   CString strFileName = arr.GetAt(i);
   BOOL bExist = FALSE;

   int j = 0;
   for (MAP_GridCtrl_FieldPos::iterator iterPos=tmpTableAtrriData.mapTableFeildPos.begin();
   iterPos!=tmpTableAtrriData.mapTableFeildPos.end();++iterPos,++j)
   {
   MAP_GridCtrl_FieldAtrri::iterator iterFieldAtrri =  tmpTableAtrriData.mapFeildAtrri.find(iterPos->second);
   ASSERT(iterFieldAtrri!=tmpTableAtrriData.mapFeildAtrri.end());

   if (iterFieldAtrri->second.strColID == strFileName)
   {
   bExist = TRUE;
   break;
   }
   }

   if (bExist)
   {
   TRACE(_T("%s Exist\n"),strFileName);
   }
   else
   {
   int nSel = ++nCount;
   m_TableAtrriData.mapTableFeildPos.insert(make_pair(nSel,strFileName));
   S_GridCtrl_FieldAtrri FeildAtrri(strFileName,nSel,strFileName,false,false);      
   m_TableAtrriData.mapFeildAtrri.insert(make_pair(strFileName,FeildAtrri));
   }
   }
   }//2017/12/12_end*/
   MAP_GridCtrl_AllData  map_all_data;
   GetMapData(map_all_data);

   if (nullptr != m_pDlgComGrid)
   {
      delete m_pDlgComGrid;
   }
   m_pDlgComGrid = new CDlgBCGGrid;
   m_pDlgComGrid->EnableColHeadMenu(FALSE);
   if (!IsWindow(m_pDlgComGrid->GetSafeHwnd()))
   {
      m_pDlgComGrid->Create(CDlgBCGGrid::IDD,this);

   }
   m_pDlgComGrid->SetGridAttriAndDatas(tableAttri,map_all_data,HDF_LEFT);

   m_pDlgComGrid->SetGridAttriAndDatas(tableAttri,map_all_data);

   m_pDlgComGrid->RefreshGridCtrlInfo();

   CRect rtComGrid;
   GetDlgItem(IDC_GRID_TABLESTYLE)->GetWindowRect(&rtComGrid);
   ScreenToClient(&rtComGrid);
   m_pDlgComGrid->SetWindowPos(NULL, rtComGrid.left,rtComGrid.top,rtComGrid.Width(),rtComGrid.Height(), SWP_SHOWWINDOW);   
}
void CDlgGridCtrlTableStyle::GetDataFromDlg()
{
   UpdateData(TRUE);
   m_TableAtrriData.isMultiRowSelect = m_CheckMultiLineSelect.GetCheck()?true:false;
   m_TableAtrriData.isAllowSort= m_CheckAllowSort.GetCheck()?true:false;
   m_TableAtrriData.IsMultiRowSelectNoLoseFocus = m_CheckMultiLineSelectNoLoseFocus.GetCheck()?true:false;
   m_TableAtrriData.isShowSortBar = m_CheckShowFilterBar.GetCheck()?true:false;
   m_TableAtrriData.isShowSumBar = m_CheckShowTotalBar.GetCheck()?true:false;
   m_TableAtrriData.isWholeRowSelect = m_CheckWholeRowSelect.GetCheck()?true:false;
   m_TableAtrriData.isShowTitleFilter= m_CheckTitleFilter.GetCheck()?true:false;
   m_TableAtrriData.isEnableDragCol= m_Check_IsEnableDragCol.GetCheck()?true:false;//��λ���ܷ��϶� yangjr 2017-6-13
   m_TableAtrriData.iDataRowFont = m_iFont;
   m_TableAtrriData.nDataRowHeight = m_iRowHeight;
   m_TableAtrriData.isPrintHengXiang = m_CheckPrintHeXiang.GetCheck()?true:false;//�����ӡ yangjr 2017-9-19
   m_TableAtrriData.isNoUpdateServerStyle = m_Check_UpdateServerStyle.GetCheck()?false:true;//���·����������ʽ yangjr 2018/5/29
   m_TableAtrriData.iPageRows = m_iPageRows;//��ҳģʽÿҳ����
   //��ȡ������Ϣ��
   MAP_GridCtrl_FieldPos mapColPos,mapColPosLockL,mapColPosLockR;
   int iMaxIndex = 1;
   for (auto iterField=m_TableAtrriData.mapFeildAtrri.begin();iterField!=m_TableAtrriData.mapFeildAtrri.end();++iterField,++iMaxIndex)
   {
      if (iterField->second.isShow)
      { 
         if(0 == iterField->second.iLock)
         {
            mapColPos.insert(make_pair(iterField->second.iColIndex,iterField->second.strColID));
         }
         else if(1 == iterField->second.iLock)
         {
            mapColPosLockL.insert(make_pair(iterField->second.iColIndex,iterField->second.strColID));
         }
         else //if(2 == iterField->second.iLock)
         {
            mapColPosLockR.insert(make_pair(iterField->second.iColIndex,iterField->second.strColID));
         }         
      }      
   }

   MAP_GridCtrl_AllData  map_all_data,map_shown_data;
   //��ʾ���δ��ʾ�����ݲ�������--add anjie by 2018/06/25
   m_pDlgComGrid->GetGridDataInfo(map_shown_data);//����������
   GetMapData(map_all_data);//�������
   for (MAP_GridCtrl_AllData::iterator iterMapShown = map_shown_data.begin();iterMapShown!=map_shown_data.end();iterMapShown++)//��ʾ��δ��ʾ��
   {
      MAP_GridCtrl_AllData::iterator iterAllShown = map_all_data.begin();
      for(iterAllShown;iterAllShown != map_all_data.end();iterAllShown++)
      {
         MAP_GridCtrl_RowData::iterator iterAllColID =iterAllShown->second.find(TABLESTYLE_strColID);
         MAP_GridCtrl_RowData::iterator iterMapColID =iterMapShown->second.find(TABLESTYLE_strColID);
         ASSERT(iterAllColID!=iterAllShown->second.end());
         ASSERT(iterMapColID!=iterMapShown->second.end());

         if(iterAllColID==iterAllShown->second.end()||iterMapColID==iterMapShown->second.end())
         {
            return;
         }

         if(iterAllColID->second.strValue == iterMapColID->second.strValue)
         {
#pragma region TABLESTYLE_strColShowName
            {
               MAP_GridCtrl_RowData::iterator iterDatAll = iterAllShown->second.find(TABLESTYLE_strColShowName);
               MAP_GridCtrl_RowData::iterator iterDatMap = iterMapShown->second.find(TABLESTYLE_strColShowName);
               ASSERT(iterDatAll!=iterAllShown->second.end());
               ASSERT(iterDatMap!=iterMapShown->second.end());
               if(iterDatAll==iterAllShown->second.end()||iterDatMap==iterMapShown->second.end())
               {
                  return;
               }
               iterDatAll->second.strValue = iterDatMap->second.strValue;
            } 
#pragma endregion TABLESTYLE_strColShowName

#pragma region TABLESTYLE_iColWidth
            {
               MAP_GridCtrl_RowData::iterator iterDatAll = iterAllShown->second.find(TABLESTYLE_iColWidth);
               MAP_GridCtrl_RowData::iterator iterDatMap = iterMapShown->second.find(TABLESTYLE_iColWidth);
               ASSERT(iterDatAll!=iterAllShown->second.end());
               ASSERT(iterDatMap!=iterMapShown->second.end());
               if(iterDatAll==iterAllShown->second.end()||iterDatMap==iterMapShown->second.end())
               {
                  return;
               }
               iterDatAll->second.strValue = iterDatMap->second.strValue;
            }
#pragma endregion TABLESTYLE_iColWidth

#pragma region TABLESTYLE_iLock
            {
               MAP_GridCtrl_RowData::iterator iterDatAll = iterAllShown->second.find(TABLESTYLE_iLock);
               MAP_GridCtrl_RowData::iterator iterDatMap = iterMapShown->second.find(TABLESTYLE_iLock);
               ASSERT(iterDatAll!=iterAllShown->second.end());
               ASSERT(iterDatMap!=iterMapShown->second.end());
               if(iterDatAll==iterAllShown->second.end()||iterDatMap==iterMapShown->second.end())
               {
                  return;
               }
               iterDatAll->second.strValue = iterDatMap->second.strValue;
            }
#pragma endregion TABLESTYLE_iLock

#pragma region TABLESTYLE_isShow
            {
               MAP_GridCtrl_RowData::iterator iterDatAll = iterAllShown->second.find(TABLESTYLE_isShow);
               MAP_GridCtrl_RowData::iterator iterDatMap = iterMapShown->second.find(TABLESTYLE_isShow);
               ASSERT(iterDatAll!=iterAllShown->second.end());
               ASSERT(iterDatMap!=iterMapShown->second.end());
               if(iterDatAll==iterAllShown->second.end()||iterDatMap==iterMapShown->second.end())
               {
                  return;
               }
               iterDatAll->second.strValue = iterDatMap->second.strValue;
            }
#pragma endregion TABLESTYLE_isShow

#pragma region TABLESTYLE_strColFormat
            {
               MAP_GridCtrl_RowData::iterator iterDatAll = iterAllShown->second.find(TABLESTYLE_strColFormat);
               MAP_GridCtrl_RowData::iterator iterDatMap = iterMapShown->second.find(TABLESTYLE_strColFormat);
               ASSERT(iterDatAll!=iterAllShown->second.end());
               ASSERT(iterDatMap!=iterMapShown->second.end());
               if(iterDatAll==iterAllShown->second.end()||iterDatMap==iterMapShown->second.end())
               {
                  return;
               }
               iterDatAll->second.strValue = iterDatMap->second.strValue;
            }
#pragma endregion TABLESTYLE_strColFormat

#pragma region TABLESTYLE_isEdit
            {
               MAP_GridCtrl_RowData::iterator iterDatAll = iterAllShown->second.find(TABLESTYLE_isEdit);
               MAP_GridCtrl_RowData::iterator iterDatMap = iterMapShown->second.find(TABLESTYLE_isEdit);
               ASSERT(iterDatAll!=iterAllShown->second.end());
               ASSERT(iterDatMap!=iterMapShown->second.end());
               if(iterDatAll==iterAllShown->second.end()||iterDatMap==iterMapShown->second.end())
               {
                  return;
               }
               iterDatAll->second.strValue = iterDatMap->second.strValue;
            }
#pragma endregion TABLESTYLE_isEdit

#pragma region TABLESTYLE_enColSumType
            {
               MAP_GridCtrl_RowData::iterator iterDatAll = iterAllShown->second.find(TABLESTYLE_enColSumType);
               MAP_GridCtrl_RowData::iterator iterDatMap = iterMapShown->second.find(TABLESTYLE_enColSumType);
               ASSERT(iterDatAll!=iterAllShown->second.end());
               ASSERT(iterDatMap!=iterMapShown->second.end());
               if(iterDatAll==iterAllShown->second.end()||iterDatMap==iterMapShown->second.end())
               {
                  return;
               }
               iterDatAll->second.strValue = iterDatMap->second.strValue;
            }
#pragma endregion TABLESTYLE_enColSumType
#pragma region TABLESTYLE_enSerchType
            {
               MAP_GridCtrl_RowData::iterator iterDatAll = iterAllShown->second.find(TABLESTYLE_enSerchType);
               MAP_GridCtrl_RowData::iterator iterDatMap = iterMapShown->second.find(TABLESTYLE_enSerchType);
               ASSERT(iterDatAll!=iterAllShown->second.end());
               ASSERT(iterDatMap!=iterMapShown->second.end());
               if(iterDatAll==iterAllShown->second.end()||iterDatMap==iterMapShown->second.end())
               {
                  return;
               }
               iterDatAll->second.strValue = iterDatMap->second.strValue;
            }
#pragma endregion TABLESTYLE_enSerchType

#pragma region TABLESTYLE_iColFont
            {
               MAP_GridCtrl_RowData::iterator iterDatAll = iterAllShown->second.find(TABLESTYLE_iColFont);
               MAP_GridCtrl_RowData::iterator iterDatMap = iterMapShown->second.find(TABLESTYLE_iColFont);
               ASSERT(iterDatAll!=iterAllShown->second.end());
               ASSERT(iterDatMap!=iterMapShown->second.end());
               if(iterDatAll==iterAllShown->second.end()||iterDatMap==iterMapShown->second.end())
               {
                  return;
               }
               iterDatAll->second.strValue = iterDatMap->second.strValue;
            }
            #pragma endregion TABLESTYLE_iColFont

#pragma region TABLESTYLE_IsFontWeight
            {
               MAP_GridCtrl_RowData::iterator iterDatAll = iterAllShown->second.find(TABLESTYLE_IsFontWeight);
               MAP_GridCtrl_RowData::iterator iterDatMap = iterMapShown->second.find(TABLESTYLE_IsFontWeight);
               ASSERT(iterDatAll!=iterAllShown->second.end());
               ASSERT(iterDatMap!=iterMapShown->second.end());
               if(iterDatAll==iterAllShown->second.end()||iterDatMap==iterMapShown->second.end())
               {
                  return;
               }
               iterDatAll->second.strValue = iterDatMap->second.strValue;
            }
#pragma endregion TABLESTYLE_IsFontWeight

#pragma region TABLESTYLE_isEnableFilter
            {
               MAP_GridCtrl_RowData::iterator iterDatAll = iterAllShown->second.find(TABLESTYLE_isEnableFilter);
               MAP_GridCtrl_RowData::iterator iterDatMap = iterMapShown->second.find(TABLESTYLE_isEnableFilter);
               ASSERT(iterDatAll!=iterAllShown->second.end());
               ASSERT(iterDatMap!=iterMapShown->second.end());
               if(iterDatAll==iterAllShown->second.end()||iterDatMap==iterMapShown->second.end())
               {
                  return;
               }
               iterDatAll->second.strValue = iterDatMap->second.strValue;
            }
#pragma endregion TABLESTYLE_isEnableFilter

#pragma region TABLESTYLE_strColDestribution
            {
               MAP_GridCtrl_RowData::iterator iterDatAll = iterAllShown->second.find(TABLESTYLE_strColDestribution);
               MAP_GridCtrl_RowData::iterator iterDatMap = iterMapShown->second.find(TABLESTYLE_strColDestribution);
               ASSERT(iterDatAll!=iterAllShown->second.end());
               ASSERT(iterDatMap!=iterMapShown->second.end());
               if(iterDatAll==iterAllShown->second.end()||iterDatMap==iterMapShown->second.end())
               {
                  return;
               }
               iterDatAll->second.strValue = iterDatMap->second.strValue;
            }
#pragma endregion TABLESTYLE_strColDestribution

            break;
         }
      }
   }

//��ʾ���δ��ʾ�����ݲ�������--add anjie by 2018/06/25--end
   for (MAP_GridCtrl_AllData::iterator iterMap=map_all_data.begin();iterMap!=map_all_data.end();++iterMap)
   {
      MAP_GridCtrl_FieldPos::iterator iterFind = m_TableAtrriData.mapTableFeildPos.find(iterMap->first+1);
      ASSERT(iterFind!=m_TableAtrriData.mapTableFeildPos.end());
      MAP_GridCtrl_FieldAtrri::iterator iterFindAttri = m_TableAtrriData.mapFeildAtrri.find(iterFind->second);
      ASSERT(iterFindAttri!=m_TableAtrriData.mapFeildAtrri.end());
      BYTE backupLock = iterFindAttri->second.iLock;//�ȱ��ݣ���ֹ���޸�
      for (auto iterData=iterMap->second.begin();iterData!=iterMap->second.end();++iterData)
      {
         if (TABLESTYLE_strColID == iterData->first)
         {
            iterFindAttri->second.strColID = iterData->second.strValue;
         }
         else if (TABLESTYLE_strColShowName == iterData->first)
         {
            iterFindAttri->second.strColShowName = iterData->second.strValue;
         }
         else if (TABLESTYLE_iColWidth == iterData->first)
         {
            iterFindAttri->second.iColWidth = _ttoi(iterData->second.strValue);
         }
         else if (TABLESTYLE_isShow == iterData->first)
         {
            bool isShow = _ttoi(iterData->second.strValue)?true:false;
            CString &strValue = iterMap->second.find(TABLESTYLE_iLock)->second.strValue;
            vector<CString> &vecValue = 
               *(iterMap->second.find(TABLESTYLE_iLock)->second.sptr_normalComboxData);
            int iLock = GetPosInVector(strValue, vecValue);
            if (!iterFindAttri->second.isShow && isShow )//�Ӳ���ʾ����ʾ��������ֵ
            {
               if (0 == iLock)
               {    
                  mapColPos.insert(make_pair(iMaxIndex++,iterFindAttri->second.strColID));
               }
               else if (1 == iLock)
               {
                  mapColPosLockL.insert(make_pair(iMaxIndex++,iterFindAttri->second.strColID));
               }
               else //if (2 == iLock)
               {
                  mapColPosLockR.insert(make_pair(iMaxIndex++,iterFindAttri->second.strColID));
               }
            }
            else if (iterFindAttri->second.isShow && !isShow )//����ʾ������ʾ���Ӷ�����ɾ��ֵ
            {
               auto iterTmp = mapColPos.find(iterFindAttri->second.iColIndex);
               if (iterTmp!=mapColPos.end())
               {
                  mapColPos.erase(iterTmp);
               }  
               auto iterTmpL = mapColPosLockL.find(iterFindAttri->second.iColIndex);
               if (iterTmpL!=mapColPosLockL.end())
               {
                  mapColPosLockL.erase(iterTmpL);
               } 
               auto iterTmpR = mapColPosLockR.find(iterFindAttri->second.iColIndex);
               if (iterTmpR!=mapColPosLockR.end())
               {
                  mapColPosLockR.erase(iterTmpR);
               } 
            }
            else if (iterFindAttri->second.isShow && isShow )//����ʾ����ʾ����������
            {
               if (0 == backupLock)//�Ӳ�����
               {                  
                  if(1 == iLock)//���������
                  {
                     mapColPos.erase(mapColPos.find(iterFindAttri->second.iColIndex));
                     mapColPosLockL.insert(make_pair(iMaxIndex++,iterFindAttri->second.strColID));
                  }
                  else if(2 == iLock)//�������ұ�
                  {
                     mapColPos.erase(mapColPos.find(iterFindAttri->second.iColIndex));
                     mapColPosLockR.insert(make_pair(iMaxIndex++,iterFindAttri->second.strColID));
                  } 
               }
               else if (1 == backupLock)//��������
               {                  
                  if(0 == iLock)//��������
                  {
                     mapColPosLockL.erase(mapColPosLockL.find(iterFindAttri->second.iColIndex));
                     mapColPos.insert(make_pair(iMaxIndex++,iterFindAttri->second.strColID));
                  }
                  else if(2 == iLock)//�������ұ�
                  {
                     mapColPosLockL.erase(mapColPosLockL.find(iterFindAttri->second.iColIndex));
                     mapColPosLockR.insert(make_pair(iMaxIndex++,iterFindAttri->second.strColID));
                  } 
               }
               else //if (2 == backupLock)//��������
               {                  
                  if(0 == iLock)//��������
                  {
                     mapColPosLockR.erase(mapColPosLockR.find(iterFindAttri->second.iColIndex));
                     mapColPos.insert(make_pair(iMaxIndex++,iterFindAttri->second.strColID));
                  }
                  else if(1 == iLock)//���������
                  {
                     mapColPosLockR.erase(mapColPosLockR.find(iterFindAttri->second.iColIndex));
                     mapColPosLockL.insert(make_pair(iMaxIndex++,iterFindAttri->second.strColID));
                  } 
               }                          
            }
            iterFindAttri->second.isShow = isShow;
         }
         else if (TABLESTYLE_isEdit == iterData->first)
         {
            iterFindAttri->second.isEdit = _ttoi(iterData->second.strValue)?true:false;
         }
         else if (TABLESTYLE_iLock == iterData->first)
         {
            iterFindAttri->second.iLock = GetPosInVector(iterData->second.strValue,
               *(iterData->second.sptr_normalComboxData));
         }
         else if (TABLESTYLE_strColFormat == iterData->first)
         {
            iterFindAttri->second.strColFormat = iterData->second.strValue;
         }
         else if (TABLESTYLE_enColSumType == iterData->first)
         {
            iterFindAttri->second.enColSumType = 
               (ENUM_COLSUMTYPE)GetPosInVector(iterData->second.strValue,
               *(iterData->second.sptr_normalComboxData));
         }
         else if (TABLESTYLE_enSerchType == iterData->first)
         {
            iterFindAttri->second.enSerchType = 
               (ENUM_COLSERCHTYPE)GetPosInVector(iterData->second.strValue,
               *(iterData->second.sptr_normalComboxData));
         }
         else if (TABLESTYLE_iColFont == iterData->first)
         {
            iterFindAttri->second.iColFont = _ttoi(iterData->second.strValue);
         }
         else if (TABLESTYLE_IsFontWeight == iterData->first)
         {
            iterFindAttri->second.IsFontWeight = _ttoi(iterData->second.strValue)?true:false;
         }
         else if (TABLESTYLE_isEnableFilter == iterData->first)
         {
            iterFindAttri->second.isEnableFilter = _ttoi(iterData->second.strValue)?true:false;
         }
         else if (TABLESTYLE_strColDestribution == iterData->first)
         {
            iterFindAttri->second.strColDestribution = iterData->second.strValue;
         }
         else if (TABLESTYLE_strTableID== iterData->first)
         {
            iterFindAttri->second.strTableID = iterData->second.strValue;
         }
         else
         {
            ASSERT(0);  
         }
      }
   }
   //��������λ��(������)
   int index = 1;
   //����������ʾ�������������
   for (auto iterPos=mapColPosLockL.begin();iterPos!=mapColPosLockL.end();++iterPos,++index)
   {
      auto iterField = m_TableAtrriData.mapFeildAtrri.find(iterPos->second);
      ASSERT(iterField!=m_TableAtrriData.mapFeildAtrri.end());
      iterField->second.iColIndex = index;
   }
   //�ڶ���������ʾ�Ҳ���������
   for (auto iterPos=mapColPos.begin();iterPos!=mapColPos.end();++iterPos,++index)
   {
      auto iterField = m_TableAtrriData.mapFeildAtrri.find(iterPos->second);
      ASSERT(iterField!=m_TableAtrriData.mapFeildAtrri.end());
      iterField->second.iColIndex = index;
   }   
   //������������ʾ�������ұߵ���
   for (auto iterPos=mapColPosLockR.begin();iterPos!=mapColPosLockR.end();++iterPos,++index)
   {
      auto iterField = m_TableAtrriData.mapFeildAtrri.find(iterPos->second);
      ASSERT(iterField!=m_TableAtrriData.mapFeildAtrri.end());
      iterField->second.iColIndex = index;
   }

   //�������û����ʾ����
   for (auto iterMap=m_TableAtrriData.mapFeildAtrri.begin();iterMap!=m_TableAtrriData.mapFeildAtrri.end();++iterMap)
   {//�����鿴�յ���������λ��
      if (FALSE == iterMap->second.isShow)
      {
         iterMap->second.iColIndex = index;
         index++;
      }
   }
}
//��ʾȫ��
void CDlgGridCtrlTableStyle::OnBnClickedCheckAllshow()
{
   // TODO: �ڴ���ӿؼ�֪ͨ����������
   UINT  uState = m_CheckAllShow.GetCheck();
   CString strValue; 
   if (uState == BST_CHECKED)
   {
      strValue = _T("1");
      m_bHasAddShowField = TRUE;
   }
   else
   {
      strValue = _T("0");
      m_bHasAddShowField = FALSE;
   }
   MAP_GridCtrl_AllData  map_all_data;
   m_pDlgComGrid->GetGridDataInfo(map_all_data);  
   for (MAP_GridCtrl_AllData::iterator iterMap=map_all_data.begin();iterMap!=map_all_data.end();++iterMap)
   {
      MAP_GridCtrl_RowData::iterator iterData = iterMap->second.find(TABLESTYLE_isShow);
      ASSERT(iterData!=iterMap->second.end());    
      iterData->second.strValue = strValue;
   }
   m_pDlgComGrid->SetGridDataInfo(map_all_data);
   m_pDlgComGrid->RefreshGridCtrlInfo();
}

//�༭ȫ��
void CDlgGridCtrlTableStyle::OnBnClickedCheckAlledit()
{
   UINT  uState = m_CheckAllEdit.GetCheck();
   CString strValue; 
   if (uState == BST_CHECKED)
   {
      strValue = _T("1");
   }else
   {
      strValue = _T("0");
   }
   MAP_GridCtrl_AllData  map_all_data;
   m_pDlgComGrid->GetGridDataInfo(map_all_data);  
   for (MAP_GridCtrl_AllData::iterator iterMap=map_all_data.begin();iterMap!=map_all_data.end();++iterMap)
   {
      MAP_GridCtrl_RowData::iterator iterData = iterMap->second.find(TABLESTYLE_isEdit);
      ASSERT(iterData!=iterMap->second.end());    
      iterData->second.strValue = strValue;
   }
   m_pDlgComGrid->SetGridDataInfo(map_all_data);
   m_pDlgComGrid->RefreshGridCtrlInfo();
}

int CDlgGridCtrlTableStyle::GetPosInVector(CString strValue,const std::vector<CString> &vecValue)
{
   ASSERT(!vecValue.empty());
   int index = 0;
   int size = vecValue.size();
   for (int i=0;i<size;++i)
   {
      if (vecValue[i] == strValue)
      {
         return i;
      }
   }
   return 0;
}

void CDlgGridCtrlTableStyle::OnDeltaposSpinRowHeight(NMHDR *pNMHDR, LRESULT *pResult)
{
   LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
   // TODO: �ڴ���ӿؼ�֪ͨ����������
   UpdateData(true);
   if(pNMUpDown->iDelta == -1) // �����ֵΪ-1 , ˵�������Spin�����µļ�ͷ
   {
      if(m_iRowHeight <= ROWHEGIHT_MIN)// ����С�����ķ�Χ
      {
         m_iRowHeight = ROWHEGIHT_MIN;
         UpdateData(false);
         return;
      }
      m_iRowHeight--;      
   }
   else if(pNMUpDown->iDelta == 1) // �����ֵΪ1, ˵�������Spin�����ϵļ�ͷ
   {
      if( m_iRowHeight >=ROWHEGIHT_MAX)//���ܴ������ķ�Χ
      {
         m_iRowHeight = ROWHEGIHT_MAX;
         UpdateData(false);
         return;
      }
      m_iRowHeight++;
   }
   UpdateData(false);
   *pResult = 0;
}

void CDlgGridCtrlTableStyle::OnDeltaposSpinFont(NMHDR *pNMHDR, LRESULT *pResult)
{
   LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
   // TODO: �ڴ���ӿؼ�֪ͨ����������
   int iFont = m_iFont;
   UpdateData(true);
   if(pNMUpDown->iDelta == -1) // �����ֵΪ-1 , ˵�������Spin�����µļ�ͷ
   {
      if(m_iFont <= FONT_MIN)// ����С�����ķ�Χ
      {
         m_iFont = FONT_MIN;
         UpdateData(false);
         if (iFont != m_iFont)
         {
            SetFontToGrid(m_iFont);
         }
         return;
      }
      m_iFont--;      
   }
   else if(pNMUpDown->iDelta == 1) // �����ֵΪ1, ˵�������Spin�����ϵļ�ͷ
   {
      if( m_iFont >=FONT_MAX)//���ܴ������ķ�Χ
      {
         m_iFont = FONT_MAX;
         UpdateData(false);
         if (iFont != m_iFont)
         {
            SetFontToGrid(m_iFont);
         }
         return;
      }
      m_iFont++;
   }
   UpdateData(false);
   if (iFont != m_iFont)
   {
      SetFontToGrid(m_iFont);
   }
   *pResult = 0;
}

void CDlgGridCtrlTableStyle::OnEnKillfocusEditRowheight()
{
   // TODO: �ڴ���ӿؼ�֪ͨ����������
   UpdateData(TRUE);
   if (m_iRowHeight>ROWHEGIHT_MAX)
   {
      m_iRowHeight = ROWHEGIHT_MAX;
      UpdateData(FALSE);
   }else if (m_iRowHeight<ROWHEGIHT_MIN)
   {
      m_iRowHeight = ROWHEGIHT_MIN;
      UpdateData(FALSE);
   }   
}


void CDlgGridCtrlTableStyle::OnEnKillfocusEditFont()
{
   // TODO: �ڴ���ӿؼ�֪ͨ����������
   int iFont = m_iFont;
   UpdateData(TRUE);
   if (m_iFont>FONT_MAX)
   {
      m_iFont = FONT_MAX;
      UpdateData(FALSE);
   }else if (m_iFont<FONT_MIN)
   {
      m_iFont = FONT_MIN;
      UpdateData(FALSE);
   }  
   if (iFont != m_iFont)
   {
      SetFontToGrid(m_iFont);
   }
}
void CDlgGridCtrlTableStyle::SetFontToGrid(int iFont)
{
   MAP_GridCtrl_AllData  map_all_data;
   m_pDlgComGrid->GetGridDataInfo(map_all_data);  
   CString strValue;
   strValue.Format(_T("%d"),iFont);
   for (MAP_GridCtrl_AllData::iterator iterMap=map_all_data.begin();iterMap!=map_all_data.end();++iterMap)
   {
      MAP_GridCtrl_RowData::iterator iterData = iterMap->second.find(TABLESTYLE_iColFont);
      ASSERT(iterData!=iterMap->second.end());    
      iterData->second.strValue = strValue;
   }
   m_pDlgComGrid->SetGridDataInfo(map_all_data);
   m_pDlgComGrid->RefreshGridCtrlInfo();
}

//���浽ϵͳĿ¼��
void CDlgGridCtrlTableStyle::OnBnClickedButtonSaveas()
{
   GetDataFromDlg();
   BOOL ret = CGridCtrlTableAttributeOp::Instance()->WriteTableAttriAsDefault(m_strFileName,m_TableAtrriData);
   if (!ret)
   {
      AfxMessageBox(_T("��������ʽʧ�ܣ�"));
   }
}


void CDlgGridCtrlTableStyle::OnBnClickedBtnInitsysstyle()
{
   BOOL ret = CGridCtrlTableAttributeOp::Instance()->InitDefaultTableAttri(m_strFileName);
   if (!ret)
   {
      theApp.OnShowDesktopAlert(_T("��ʼ��ϵͳ�����ʽʧ�ܣ�"),TIP_COLOR_WARNING,3);
   }else
   {
      theApp.OnShowDesktopAlert(_T("��ʼ��ϵͳ�����ʽ�ɹ���"),TIP_COLOR_SUC,3);
   }
}


void CDlgGridCtrlTableStyle::OnBnClickedBtnInituserstyle()
{   
   S_GridCtrl_TableAttri TableAtrriData;
   BOOL ret = CGridCtrlTableAttributeOp::Instance()->InitUserTableAttri(m_strFileName,TableAtrriData);
   if (!ret)
   {
      theApp.OnShowDesktopAlert(_T("��ʼ���û������ʽʧ�ܣ�"),TIP_COLOR_WARNING,3);
   }else
   {
      if (m_pDlgComGrid)
      {
         TableAtrriData.strUpdateTime = m_TableAtrriData.strUpdateTime;//����ʱ�ڲ�Ҫ��ʼ���� yangjr 2018/6/12
         m_TableAtrriData = TableAtrriData;
         InitDlg();
         MAP_GridCtrl_AllData  map_all_data;
         GetMapData(map_all_data);
         m_pDlgComGrid->SetGridDataInfo(map_all_data);
         m_pDlgComGrid->RefreshGridCtrlInfo();
         theApp.OnShowDesktopAlert(_T("��ʼ���û������ʽ�ɹ���"),TIP_COLOR_SUC,TIP_TIME_DELAY);
      }else
      {
         theApp.OnShowDesktopAlert(_T("��ʼ���û������ʽʧ�ܣ�"),TIP_COLOR_WARNING,3);
      }
   }
}

//�����������ݿ��ȡ��Ӧ����Ӧ�ֶε���ʾ���� yangjr2018/3/1
//void CDlgGridCtrlTableStyle::OnBnClickedBtnReadcolname()
//{
//   MAP_GridCtrl_AllData  map_all_data;
//   m_pDlgComGrid->GetGridDataInfo(map_all_data);  
//   std::map<CString,std::set<CString>> mapTableAndCol;
//   for (MAP_GridCtrl_AllData::iterator iterMap=map_all_data.begin();iterMap!=map_all_data.end();++iterMap)
//   {
//      MAP_GridCtrl_RowData::iterator iterTableID = iterMap->second.find(TABLESTYLE_strTableID);
//      MAP_GridCtrl_RowData::iterator iterColID = iterMap->second.find(TABLESTYLE_strColID);
//      ASSERT(iterTableID!=iterMap->second.end() && iterColID!=iterMap->second.end());    
//      if (!iterTableID->second.strValue.IsEmpty())
//      {
//         std::map<CString,std::set<CString>>::iterator iterFindTable = mapTableAndCol.find(iterTableID->second.strValue);
//         if (iterFindTable!=mapTableAndCol.end())
//         {
//            iterFindTable->second.insert(iterColID->second.strValue);
//         }else
//         {
//            std::set<CString> setColID;
//            setColID.insert(iterColID->second.strValue);
//            mapTableAndCol.insert(make_pair(iterTableID->second.strValue,setColID));
//         }
//      }
//   }
//   std::map<CString,std::map<CString,CString>> mapTableAndColRead;
//   DBDataColSetLst dbColSet;
//   mapTableAndColRead = dbColSet.GetShowNameByMapWithTableAndCol(theApp.m_pADOConn , mapTableAndCol );
//
//   for (MAP_GridCtrl_AllData::iterator iterMap=map_all_data.begin();iterMap!=map_all_data.end();++iterMap)
//   {
//      MAP_GridCtrl_RowData::iterator iterTableID = iterMap->second.find(TABLESTYLE_strTableID);
//      MAP_GridCtrl_RowData::iterator iterColID = iterMap->second.find(TABLESTYLE_strColID);
//      MAP_GridCtrl_RowData::iterator iterShowName = iterMap->second.find(TABLESTYLE_strColShowName);
//      ASSERT(iterTableID!=iterMap->second.end() && iterColID!=iterMap->second.end() && iterShowName!=iterMap->second.end());    
//      if (!iterTableID->second.strValue.IsEmpty())
//      {
//         std::map<CString,std::map<CString,CString>>::iterator iterFindTable = mapTableAndColRead.find(iterTableID->second.strValue);
//         if (iterFindTable!=mapTableAndColRead.end())
//         {
//            auto iterFindCol = iterFindTable->second.find(iterColID->second.strValue);
//            if (iterFindCol != iterFindTable->second.end())
//            {
//               iterShowName->second.strValue = iterFindCol->second;
//            }
//         }
//      }
//   }
//   m_pDlgComGrid->SetGridDataInfo(map_all_data);
//   m_pDlgComGrid->RefreshGridCtrlInfo();
//
//}

void CDlgGridCtrlTableStyle::OnBnClickedCheckShow()
{
   CButton *pCheckShow = (CButton*)GetDlgItem(IDC_CHECK_ALREADY_SHOW);
   CButton *pNoCheckShow = (CButton*)GetDlgItem(IDC_CHECK_NO_SHOW);
   int nShowCheckState = pCheckShow->GetCheck();
   int nNoShowCheckState = pNoCheckShow->GetCheck();

   if(nNoShowCheckState == nShowCheckState)
   {
      MAP_GridCtrl_AllData  map_all_data;
      GetMapData(map_all_data);
      m_pDlgComGrid->SetGridDataInfo(map_all_data);
      m_pDlgComGrid->RefreshGridCtrlInfo();
   }
   else
   {
      if(1 == nNoShowCheckState)
      {  
         int nMapIndex = 0;
         MAP_GridCtrl_AllData  map_all_data,map_show_data;
         GetMapData(map_all_data); 
         for (MAP_GridCtrl_AllData::iterator iterMap=map_all_data.begin();iterMap!=map_all_data.end();++iterMap)
         {
            MAP_GridCtrl_RowData::iterator iterData = iterMap->second.find(TABLESTYLE_isShow);
            ASSERT(iterData!=iterMap->second.end());    
            if(iterData->second.strValue.Compare(_T("0")) == 0)
            {
               map_show_data.insert(pair<int,MAP_GridCtrl_RowData>(nMapIndex,iterMap->second));
               nMapIndex++;
            }
         }
         m_pDlgComGrid->SetGridDataInfo(map_show_data);
         m_pDlgComGrid->RefreshGridCtrlInfo();
      }
      else if(1 == nShowCheckState)
      {
         int nMapIndex = 0;
         MAP_GridCtrl_AllData  map_all_data,map_show_data;
         GetMapData(map_all_data); 
         for (MAP_GridCtrl_AllData::iterator iterMap=map_all_data.begin();iterMap!=map_all_data.end();++iterMap)
         {
            MAP_GridCtrl_RowData::iterator iterData = iterMap->second.find(TABLESTYLE_isShow);
            ASSERT(iterData!=iterMap->second.end());    
            if(iterData->second.strValue.Compare(_T("1")) == 0)
            {
               map_show_data.insert(pair<int,MAP_GridCtrl_RowData>(nMapIndex,iterMap->second));
               nMapIndex++;
            }
         }
         m_pDlgComGrid->SetGridDataInfo(map_show_data);
         m_pDlgComGrid->RefreshGridCtrlInfo();
      }
   }
}
