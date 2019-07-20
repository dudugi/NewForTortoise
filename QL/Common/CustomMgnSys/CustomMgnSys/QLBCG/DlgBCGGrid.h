#pragma once

//#include "ClassEx/TabDialog.h"
#include "afxwin.h"
#include <BCGPDialog.h>
#include "CDataTableDlgDefine.h"
#include "QLBCG\QLBCGMESSAGE.h"


#define START_MY_OUTPUT_LOG_
#ifndef START_MY_OUTPUT_LOG_
#define START_MY_OUTPUT_LOG_ CString strLog;\
   DWORD dwTime = GetTickCount();\
   DWORD dwTmp;
#endif

#define MY_OUTPUT_LOG_
#ifndef MY_OUTPUT_LOG_
#define MY_OUTPUT_LOG_ dwTmp = GetTickCount();\
   strLog.Format(_T("TM:%d(ms)LN(%d)(%d)-%s:%s \n"),dwTmp-dwTime,__LINE__,dwTmp,__FUNCTIONW__,__FILEW__);\
   OutputDebugString(strLog);\
   dwTime = dwTmp;
#endif



extern UINT UM_EXPORT_DATA_TO_EXCEL_MSG;


class CQLBCGGridCtrl;


//��ȡCPUʱ���,(��λ:���뼶)		by WangZY 2017/09/28
//inline unsigned __int64 GetCycleCount()   
//{   
//	__asm   _emit   0x0F   
//	__asm   _emit   0x31   
//}


class CPageInfo
{
public:
   CPageInfo()
   {
      m_nTotalCount = 100;
      m_nPerPageCount = 100;
      m_nCurPage = 1;
      m_nTotalPage = 1;
   }
   ~CPageInfo()
   {

   }

public:
   int m_nTotalCount;
   int m_nPerPageCount;
   int m_nCurPage;
   int m_nTotalPage;
};

// CDlgBCGGrid �Ի���

class CDlgBCGGrid : public CBCGPDialog
{
	DECLARE_DYNAMIC(CDlgBCGGrid)

public:
	CDlgBCGGrid(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgBCGGrid();

// �Ի�������
	enum { IDD = IDD_DLGBCGGRID };

	enum EM_SEL_TYPE
	{
		emNull = 0,	
		emSel,					//�ı�ѡ���е�����	
		emJudgeHasSel,			//�ж��Ƿ���ѡ���У����������޸�
		emAllOnGrid,			//�ı������������е�����
		emUnSel,					//�ı�������δѡ�е��е�����
		emAllData,				//�ı��������ݣ������������ϺͲ��������ϵģ�
	};

   enum EM_REFRESH_DB_MODE
   {
      emRDM_Restart = 0,   //���²�ѯ
      emRDM_CurPage,       //��ѯ��ǰҳ
      emRDM_PrePage,       //��ѯ��һҳ
      emRDM_NextPage,      //��ѯ��һҳ
   };

	//�ⲿ��Ӧ����Ϣ		by WangZY 2017/06/13
	enum EM_MSG_OUTSIDE
	{
		UM_RCLICK_GRID = (WM_USER + 20/* + NM_RCLICK*/),	//����Ҽ�����Grid��Ϣ
		UM_DBLCLK_GRID,/* = (WM_USER + 20 + NM_DBLCLK),*/	//������˫��Grid��Ϣ
		UM_LCLICK_GRID,/* = (WM_USER + 20 + NM_CLICK),*/	//����������Grid��Ϣ

		UM_UPDATE_DATA_CHANGED,							//������Ϣ�����仯
		UM_ATTRI_FIELD_HAS_ADD_MSG,			//������Ե��ֶ������������ʾ		by WangZY 2018/02/01
      UM_PAGINATION_REFRESH_DATA_MSG,     //֪ͨ�ⲿ��Ҫˢ�����ݵ���Ϣ		by WangZY 2018/06/06

	};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

	void InitBCGGridCtrl();

private:
	BOOL m_bShowLeftHeaderColumn;					//�Ƿ���ʾ��������		by WangZY 2017/11/21
	BOOL m_bShowLineNumber;						//�Ƿ�����������ʾ�к�		by WangZY 2017/11/21
	int  m_nLeftHeaderColumnWidth;				//�������еĿ��		by WangZY 2017/11/21
	BOOL m_bUserPaginationMode;					//ʹ���Զ����ҳģʽ		by WangZY 2017/11/08
	CBCGPButton m_btnPageUp;								//��һҳ��ť		by WangZY 2017/10/30
	CBCGPButton m_btnPageDown;							//��һҳ��ť		by WangZY 2017/10/30
	CBCGPStatic m_textPageInfo;							//��ҳ��Ϣ		by WangZY 2017/10/30
	BOOL		m_bShowPageInfo;						//�Ƿ���ʾ��ҳ�ؼ�	by WangZY 2017/10/30
   EM_PAGINATION_MODE m_emPMPaginationModeFlag;     //��ҳģʽ��־
   CPageInfo m_infoPage;   //��ҳģʽ�µķ�ҳ��Ϣ
	CQLBCGGridCtrl*		m_pBCGGrid;
	//CProgressCtrl			m_progressCtrl;

	S_GridCtrl_TableAttri		m_tableAttri;		//����������
	MAP_GridCtrl_AllData		m_tableData;		//�������

	//_RecordsetPtr m_dbRecordSetPtr;			//�������ݼ�¼��ָ��

	map<CString,BOOL>			m_mapColEdit;		//<���ݿ��ֶΣ��Ƿ�ɱ༭>
	map<CString,int>			m_mapColID;			//<���ݿ��ֶΣ���id>
	map<int,CString>			m_mapColWithFieldId;	//<��id, ���ݿ��ֶ�ID>
	map<int,CString>			m_mapColName;		//<��id,��ʾ����>
	map<CString,CString>		m_mapCol_Name_ID;	//<���ݿ�ID����ʾ����>

	map<CString/*FieldId*/, CString /*FilterInfo*/>	m_mapFilterInfo;	//ɸѡ��Ϣ

	vector<int>		m_vecFrozenIndex;			//������index

	CString m_strSortInfo;		//�������Ϣ

	std::map<int/*colIndex*/,CString/*strFieldId*/> m_mapShowCol;	//		by WangZY 2018/01/31
	BOOL m_bUseNewAttri;						//�µı����Է�ʽ	by WangZY 2018/01/31

	// wangzl 2017-12-11 �б���˵�����
	BOOL						m_bEnableColHeadMenu;//�Ƿ������е���˵�
	int							m_nRClickHeadCol;//�Ҽ��������
	// wangzl 2017-12-11 �б���˵����� end
   CString m_tableStyleFileName;//�����ʽ��xml�ļ��� yangjr 2017-12-13

   BOOL		m_bKeyShiftDown;	//shift ����	add by lida 2018/01/31
   BOOL		m_bKeyCtrlDown;		//ctrl	����	add by lida 2018/01/31
	std::vector<CString> m_vecNeedfulFieldId;	//��Ҫ���ֶ�	by WangZY 2018/02/01
	std::vector<CString> m_vecNeedfulPackageFieldId;	//��Ҫ������ݵ��ֶ�	by WangZY 2018/02/01

	int		m_nCheckRowCount;			//��ѡ��������
	int		m_lastShowCheckRowCount;	//�ϴ���ʾ�Ĺ�ѡ����������

	//�б���������б���Ϣ 		by WangZY 2018/03/07
	std::map<CString/* strFieldId*/,vector<CString>> m_mapFilterListInfo;

	//ʹ���б������������ 		by WangZY 2018/03/07
	std::vector<CString /*strFieldId*/> m_vecFilterId;

   std::map<CString,CString> m_mapTongJiValue;/*ͳ������*/
	 
protected:
	//�ڲ��õĽӿ�,ǧ��Ҫ������:����Cell��item��ֵ		by WangZY 2018/02/01
	BOOL _in_SetGridItemValue(__in CBCGPGridItem *pItem, __in CString &strValue);
	//���ɱ������������ֶ�		by WangZY 2018/02/01
	BOOL CreateNeedfulPackageFieldId();
	//������ɱ����еĴ�ӡ��Ҫxml��Ϣ		by WangZY 2017/06/28
	BOOL CreatePrintFieldXml(__out CString &strFieldXml);

	//������������еĴ�ӡ��Ҫxml��Ϣ		by WangZY 2017/06/28
	BOOL CreatePrintDataXml(__out CString &strDataXml);

	//�����ҳģʽ�����������еĴ�ӡ��Ҫxml��Ϣ		by WangZY 2018/01/19
	BOOL CreateUsedPaginationModePrintDataXml(__out CString &strDataXml);

	//������ɺϼ��еĴ�ӡ��Ҫxml��Ϣ		by WangZY 2017/06/28
	BOOL CreatePrintStatisticRowXml(__out CString &strStatisticRowXml);

	BOOL GetShowColID(vector<int>& vecShowCol);

	//���ݵ���ֵ����ĳ��ֵ
	BOOL AddDataValue(__in const CString &strValue, __inout S_GridCtrl_FieldData &data);  

	//ˢ�����ݵ�������		by WangZY 2017/10/31
	void RefreshDataInfoToGrid(int nPageType =0,BOOL bGoFirstPage = TRUE);

	//ˢ�·�ҳ�ؼ���Ϣ		by WangZY 2017/10/31
	void RefreshPageInfo(int nPageCount,int nCurPage, int nPageSize);

	//ˢ��������Ϣ
	void RefreshDataBySort();

	//ˢ��ɸѡ������Ϣ		by WangZY 2017/11/02
	void RefreshDataByFilter();

	//ˢ��ͳ������Ϣ		by WangZY 2017/11/23
   //bFenYeModeSvrGridTongJi �Ƿ������ݿ��ҳģʽ����ͳ�������б���ڲ�����
	BOOL RefreshGridStatisticRow(CQLBCGGridCtrl* pGrid,BOOL bFenYeModeSvrGridTongJi = FALSE);

   //�������Ե�xml
   BOOL SaveAtrriToXml(CString strXmlName);

   //����ѡ��ʱ������check box ��״̬
   void SetMulRowSelectCheck(BOOL bCheck);

   //ͳ������ʾ��ѡ���� add by lida 
   void SetFootValue_CheckNum(int k);	

   BOOL GetTongJiDataByAttri(const S_GridCtrl_TableAttri &tableAttri,__out std::map<CString/*strFieldId*/,ENUM_COLSUMTYPE> &mapTongJiData);
public:
   //���÷�����ű���		by WangZY 2018/06/14
   void SetScale(double dblScale = 1.0f);

   // �����ⲿ����������ɫ 2018-5-29 wangzl
   const CBCGPGridColors& GetColorTheme () const;
   void SetColorTheme (const CBCGPGridColors& theme, BOOL bRedraw = TRUE, BOOL bFullCopy = FALSE);

   //������Ŀ���� wangzl 2018-06-11
   void ScrollToRow(__in const int & nRow);

   // �����ⲿ���ñ���ڲ�����ɫ 2018-5-29 wangzl
   BOOL SetCustomColors (			// Use (COLORREF)-1 for the default color
      COLORREF	clrBackground,
      COLORREF	clrText,
      COLORREF	clrGroupBackground,
      COLORREF	clrGroupText,
      COLORREF	clrLeftOffset,
      COLORREF	clrLine);
   // ���ñ������ 2018-6-14 wangzl
   void SetGridFont(CFont* pFont, BOOL bRedraw = TRUE);
   // �༭������ 2018-6-14 wangzl
   BOOL EditGridItem (const int & nRow,const int & nCol);

   void SetRowBackgroundColor(int iRow,MAP_GridCtrl_RowData& row_data,COLORREF bkcolor);

	//���ñ�Ҫ���ֶ�	by WangZY 2018/02/01
	void SetNeedfulFieldId(std::vector<CString /*strFieldId*/> vecNeedfulFieldId);

	void RefreshBCGGridCtrl();		//ˢ��

	//������ʾ��������(�ýӿڱ����ڶԻ��򴰿ڴ���֮ǰ����)		by WangZY 2017/11/21
	void SetShowLeftHeaderColumn(BOOL bShowLeftHeaderColumn = TRUE);

	//��������������ʾ�к�	(�ýӿڱ����ڶԻ��򴰿ڴ���֮ǰ����)	by WangZY 2017/11/21
	void SetShowLeftLineNumber(BOOL bShowLineNumber = TRUE);

	//������ʾ�������еĿ��(�ýӿڱ����ڶԻ��򴰿ڴ���֮ǰ����)		by WangZY 2017/11/21
	void SetShowLeftHeaderColumnWidth(int nWidth=35);

   void SetAndRefreshPageInfo(CPageInfo &info);

	//����ʹ���û��Զ����ҳģʽ��־(�ýӿڱ����ڶԻ��򴰿ڴ���֮ǰ����)		by WangZY 2017/11/08
	void SetUserPaginationMode(BOOL bUserPaginationMode = TRUE,EM_PAGINATION_MODE emPMPaginationMode = emPM_Local);
	
	//��ȡʹ���û��Զ����ҳģʽ��־		by WangZY 2017/11/08
	BOOL GetUserPaginationMode() const;

	//ͨ�����ݼ�������������		by WangZY 2017/10/25
//	void SetGridDataInfoByRecordSetPtr(_RecordsetPtr &dbRecordSetPtr);

	void PrintTime_Test(CString strTitle = _T(""));	//��ӡ����ʱ��

	//��������ɱ༭		
	void SetGridEnableEdit(BOOL bEnableEdit = TRUE);

	//��������������Ϣ����ͷ�������Ϣ��������������Ϣ,ע����Create֮����ã�
	BOOL SetGridAttriAndDatas(__in const S_GridCtrl_TableAttri &tableAttri,__in const MAP_GridCtrl_AllData &data,int iShowColAlign = HDF_CENTER);

	//��������������Ϣ����ͷ�������Ϣ��, bClear = �Ƿ��������, iShowColAlign = ���У�������ʾ
	BOOL SetGridAttriInfo(__in const S_GridCtrl_TableAttri &tableAttri,
		int iShowColAlign = HDF_CENTER);

	//��������������Ϣ
	BOOL SetGridDataInfo(__in const MAP_GridCtrl_AllData &data);

	//��ȡ����������Ϣ
	BOOL GetGridAttriInfo(__out S_GridCtrl_TableAttri &tableAttri);

	//��ȡ����������Ϣ
	BOOL GetGridDataInfo(__out MAP_GridCtrl_AllData &data);

	//ˢ������ؼ�����Ϣ
	void RefreshGridCtrlInfo(__in BOOL bEnsureVisableFirstDataRow = TRUE);

	//�ı�ĳһ�е�������Ϣ ,Ŀǰֻ֧���޸ĵ�Ԫ�������ݣ��ݲ�֧�������б������	
	int ChangeDataInfoByFieldId(__in const CString &strFieldId,__in const S_GridCtrl_FieldData &dataInfo,__in const EM_SEL_TYPE &nSelType = emSel);

	//�ı�ĳһ�е�����ֵ		
	int ChangeDataInfoByFieldId(__in const CString &strFieldId,__in const CString &strValue,__in const EM_SEL_TYPE &nSelType = emSel);

	//�µ���������������Ϣ����ͷ�������Ϣ��, bClear = �Ƿ��������, iShowColAlign = ���У�������ʾ
	BOOL SetGridAttriInfoNew(__in const S_GridCtrl_TableAttri &infoTableAttri,
		__in int iShowColAlign = HDF_CENTER);

   //������:CBCGPGridCtrl::Direction������
   void SetEnterGoDirection(UINT nDirection,BOOL bEnable = TRUE);      //����������س���ת���� add by lida 2018/05/29

	//�µ�ˢ������ؼ�����Ϣ�Ľӿ�		by WangZY 2018/01/31
	void RefreshGridCtrlInfoNew(__in BOOL bEnsureVisableFirstDataRow = TRUE);

public:		//����Ϊ��ȡ���ݵĽӿ�:
   
   //��ȡɸѡ��Ϣ		by WangZY 2018/06/06
   BOOL GetFilterFieldInfo(__out std::map<CString/*strFieldId*/,CString /*strFilter*/> &mapFilterInfo);

   BOOL SetFilterFieldInfo(__in std::map<CString/*strFieldId*/,CString /*strFilter*/> &mapFilterInfo);

   //��ȡ������Ϣ		by WangZY 2018/06/07
   BOOL GetSortFieldInfo(__out CString &strFieldId, __out BOOL &bAscening);
   
   //����������Ϣ		by WangZY 2018/06/07
   BOOL SetSortFieldInfo(__in CString strFieldId, __in BOOL bAscening);
	
   //��ȡ�������������ֶ�		by WangZY 2018/02/01
	BOOL GetNeedfulPackageFieldId(
		__out std::vector<CString/*strFieldId*/> &vecFieldId,
		__in BOOL bNewCreate = FALSE);

   BOOL GetShowFieldId(__out std::vector<CString> &vecShowFieldId,
      __out std::vector<CString> &vecFieldName);

   //BOOL GetShowFieldInfo(__out std::vector<>)
	//��ȡ���������һ�����ݵ���������
	BOOL GetLastRowIndex(__out int &nIndex);

	//��ȡѡ�е�����,����ֵΪѡ�������������		 
	int GetSelectData(__out MAP_GridCtrl_AllData &mapSelectData);

	//��ȡ��ʾ������,����ֵΪ��ʾ������������
	int GetShowData(__out MAP_GridCtrl_AllData &mapShowData);

	//��ȡ��ʾ�����ݶ�Ӧ�����������ֵ,����ֵΪ��ʾ������������
	int GetShowDataIndex(__out std::vector<int/*dataIndex*/> &vecShowIndex);

	int GetShowDataSelIndex(__out std::vector<int/*dataIndex*/> &vecShowSelIndex);

	//��ȡѡ��check = true ������������	 
	int GetSelectDataIndex(__out std::vector<int/*dataIndex*/> &vecSelectIndex);

	int GetSelectDataIndex();

	//��ȡѡ�е����ݶ�Ӧ����ؼ��ϵ��к�,����ֵΪѡ�������������		 
	int GetSelectRowNo(__out std::vector<int/*rowIndex*/> &vecSelectIndex);

	//����������кŻ�ȡĳһ�е����ݵ�����
	BOOL GetRowIndexofDataInfo(__out int &nDataRowIndex, __in int nGridRow);

	//����������кŻ�ȡĳһ�е�����
	BOOL GetRowIndexofDataInfo(__out MAP_GridCtrl_RowData& data_row, __in int nGridRow);

	//����������к����кŻ�ȡһ�����ֵ
	BOOL GetValueByGridRowAndCol(__out CString &strValue,__in int nGridRow,__in int nGridCol);

	//����������к����кŻ�ȡһ�������
	BOOL GetValueByGridRowAndCol(__out S_GridCtrl_FieldData &data,__in int nGridRow, __in int nGridCol);

	//����������к������ֶ�Id��ȡһ�����ֵ
	BOOL GetValueByGridRowAndFieldId(__out CString &strValue,__in int nGridRow,__in CString strFieldId);

	//����������к������ֶ�Id�Ż�ȡһ�������
	BOOL GetValueByGridRowAndFieldId(__out S_GridCtrl_FieldData &data,__in int nGridRow, __in CString strFieldId);

	//�����ֶ�ID�Լ���Ӧ���ַ�����ֵ ��ȡ��Ҫ�ֶε�ֵ
	BOOL GetValuebyFieldIdAndValue(__in CString strFieldId,__in CString strValue,__in CString strTarField,__out CString& strTarValue);

	//��ȡԤ��ӡ���ݵ�xml��Ϣ		
	BOOL GetPrintDataXmlText(__out CString &strFieldXml, __out CString &strDataXml,__out CString &strStatisticRowXml);

	//������������ȡһ�����ݵĴ�ӡ���ݵ�xml��Ϣ		
	BOOL GetRowPrintDateXmlTextDataIndex(__in int nDataIndex, __out CString &strDataXml);

	//��ȡѡ�����ݵ�ȫ�ֶεĴ�ӡ���ݵ�xml��Ϣ������ѡ�����ӡ��ѡ�ģ��Ƕ���ѡ�����ӡ��ǰѡ���е�		
	BOOL GetSelectedAllFieldPrintDataXmlText(__out CString &strDataXml);

	//��ȡȫ�ֶε��б����xml��Ϣ		
	BOOL GetAllFieldXml(__out CString &strFieldXml);

	// ��ȡ������
	int GetFocusRow();

	// ��ȡ����������
	BOOL GetFocusRowData(MAP_GridCtrl_RowData & rowdata);

	// ��ȡ������ָ���ֶε����� 
	BOOL GetFocusRowValue(__out CString & strValue,__in CString strFieldId);

	//��ȡ�����е���������	
	BOOL GetFocusRowDataIndex(__out int &nDataIndex);

	//�����ֶ�id��ȡ������ɸѡ�Ĺ�����Ϣ�Լ��Ƿ�ʹ�ù�����Ϣ��״̬
	BOOL GetFilterInfoByFieldId(__out BOOL &bUseFilter, __out SERCH_DATA &infoFilter, __in const CString &strFieldId);

	CString GetColShowName(int nCol);		//��ʾ������

	CString GetColName(int nCol);			//���ݿ��ֶ�����

	int GetCheckRowNum();		//��ȡ��ѡ������

   //��ȡ��ҳģʽÿҳ���� yangjr 2018/7/6
   int GetFenYePageRows();

   BOOL GetExportExcelData(std::vector<std::vector<CString>> &vecDatas);

public:	//����Ϊ�������ݵĽӿ�:

	//ĳһ�е���ֵ����һ����ֵ
	BOOL AddFieldValueByFieldId(__in CString strValue,__in const CString &strFieldId, __in const EM_SEL_TYPE &nSelType = emSel);

	//���������к����÷Ƕ���ѡ��״̬�µ��н���״̬		
	BOOL SetFocusRowByGridRow(__in int nRowNo);

	//���������������÷Ƕ���ѡ��״̬�µ��н���״̬	
	BOOL SetFocusRowByDataIndex(__in int nDataIndex);

   //�����ֶ�+ֵ�趨������ yangjr 2018/6/12
   BOOL SetFocusRowByFieldIdAndValue(__in CString strFieldId, __in CString strFieldValue);

	//���÷�ѡ add by lida 2018/03/15
	BOOL SetMultiSelectTurnOver();

	//����ѡ���ȫѡ/ȡ��ȫѡ��bVisibleOnly �Ƿ�ֻ��Կɼ����в���
	BOOL SetMultiSelectCheckAll(BOOL bCheck = TRUE,BOOL bVisibleOnly = FALSE);

	//���������к����ö���ѡ��״̬�µ��й�ѡ״̬		
	BOOL SetMultSelectCheckByGridRows(__in const std::vector<int/*RowNo*/> &vecRowNo,__in BOOL bCheck = TRUE);

	//�������ֶ�Id���ö���ѡ��״̬�µ��й�ѡ״̬
	BOOL SetMultiSelectCheckByFieldId(__in CString strFieldId, __in CString strFieldValue, __in BOOL bCheck = TRUE);

	//����������к������ֶ�Id����һ�����ֵ
	BOOL SetValuebyGridRowAndFieldId(__in CString &strValue,__in int nGridRow,__in CString strFieldId);

	//����������к������ֶ�Id����һ�����ֵ
	BOOL SetValuebyGridRowAndFieldId(__in S_GridCtrl_FieldData &data,__in int nGridRow,__in CString strFieldId);

	//����������к����к�����һ�����ֵ
	BOOL SetValueByGridRowAndCol(__in CString &strValue,__in int nGridRow,__in int nGridCol);

	//�������ݵ������������ֶ�Id����һ�����ֵ
	BOOL SetValuebyDataRowIndexAndFieldId(__in CString &strValue,__in int nDataRowIndex,__in CString strFieldId);

	//�����ֶ�ID�Լ���Ӧ���ַ�����ֵ ������Ҫ�����ֶε�ֵ
	BOOL SetValuebyFieldIdAndValue(__in CString strFieldIdIndex,__in CString &strValueIndex,__in CString strTarFieldID,__in CString strTarValue);

	//�ж�������Ƿ���������Ч��
	BOOL IsValidDataRgn();//TRUE��Ч

	//�ж��������Ƿ��и��ֶ�ֵ������
	static BOOL IsInfoInMapByFieldId(__in const MAP_GridCtrl_AllData &mapData,__in const CString &strFieldId,__in const CString &strValue);

	//����������кŻ�ȡ���ֶ�ID
	BOOL GetFieldIdByGridCol(__out CString &strFieldId, __in int nGridCol);

	//�������ֶ�ID��ȡ������к�
	BOOL GetGridColByFieldId(__out int &nGridCol, __in CString strFieldId);

	//�����ֶ�id����ɸѡ�Ĺ�����Ϣ		
	BOOL SetFilterInfoByFieldId(__in const std::vector<CString> &vecFilter,__in const CString &strFieldId);

	//�����ֶ�id���ü����Ĺ�����Ϣ	
	BOOL SetFilterInfoByFieldId(__in const CString &strFilter, __in const CString &strFieldId);

	//����ĳ�ֶ�Id�н�������		
	BOOL SortByFieldId(__in const CString &strFieldId, BOOL bAscending = TRUE);

	//���ø����кŽ�������		
	BOOL SortByColumn(__in const int nColumn, BOOL bAscending = TRUE);

	//�ж�ĳ���Ƿ���Ա༭		
	BOOL IsCanEdit(int nRow, int nColumn);

	//�Ƿ�����Ч�������У���������һЩ�¼������絯������ 
	BOOL IsValidRow(__in int nRow);

	BOOL SetSelWholeRow(int iRow,int iCol,BOOL bLeftDown = TRUE);		//ѡ��һ��,Ĭ�����

	//�Ƿ������б���˵� wangzl 2017-12-11
	void EnableColHeadMenu(BOOL bEnable = TRUE){m_bEnableColHeadMenu = bEnable;}
   	
	//��յ�ǰ������״̬		by WangZY 2017/12/12
	BOOL ClearSortState();

   //�����ʽ��xml�ļ��� yangjr 2017-12-13
   void SetTableStyleFileName(CString tableStyleFileName){m_tableStyleFileName = tableStyleFileName;}

   //���������ͷ checkbox ״̬ add by lida 2018/02/02
   void SetHeaderCheckBoxState(BOOL bCheck);

   //��ȡ�С�������
   void GetRow_Col_Num(int& iRow,int& iCol);

	//����ĳ�б���ͷ����		by WangZY 2018/03/07
	BOOL EnableFilterColumns(__in vector<CString/*strFieldId*/> vecFieldIds,
		__in BOOL bEnable=TRUE );

	//���ñ�������Զ����б�Ľӿ�		by WangZY 2018/03/07
	BOOL SetColumnFilterList(__in CString strFieldId, __in const vector<CString> &vecLst);

	//���ɷ�ҳģʽ�µı���ͷ���˵�����ִ���Ϣ		by WangZY 2018/03/12
	CString DealCalcTitleFilter();

   //��ȡ����ͳ���ֶ����� yangjr 2018/6/20
   BOOL GetTongJiData(__out std::map<CString/*strFieldId*/,ENUM_COLSUMTYPE> &mapTongJiData);

   //���ñ���ͳ���ֶ���ʾ���� yangjr 2018/6/21
   void SetTongJiData(__in const std::map<CString,CString> &mapTongJiValue/*ͳ������*/);

   //����������ݵ�excel yangjr 2018/7/19
   BOOL ExportExcel();
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	
	afx_msg LRESULT OnGrid_BeginPlaceEdit(WPARAM wParam,LPARAM lParam);			//BCGM_GRID_ITEM_BEGININPLACEEDIT
	afx_msg LRESULT OnGrid_EndPlaceEdit(WPARAM wParam,LPARAM lParam);			//BCGM_GRID_ITEM_ENDINPLACEEDIT
	afx_msg LRESULT OnGrid_SelectChanged(WPARAM wParam,LPARAM lParam);			//BCGM_GRID_SEL_CHANGED
	afx_msg LRESULT OnGrid_HideColunmChooser(WPARAM wParam,LPARAM lParam);		//BCGM_GRID_ON_HIDE_COLUMNCHOOSER
	afx_msg LRESULT OnGrid_BeginDrag(WPARAM wParam,LPARAM lParam);				//BCGM_GRID_BEGINDRAG
	afx_msg LRESULT OnGrid_ColumnClick(WPARAM wParam,LPARAM lParam);			//BCGM_GRID_COLUMN_CLICK
	
	//��Ӧÿ�е�����CheckBox�ĵ����Ϣ		by WangZY 2017/11/22
	afx_msg LRESULT OnGrid_RowCheckBoxClick(WPARAM wParam,LPARAM lParam);		//BCGM_GRID_ROW_CHECKBOX_CLICK
	//��Ӧ����ͷ������CheckBox�ĵ����Ϣ			by WangZY 2017/11/22
	afx_msg LRESULT OnGrid_HeaderCheckBoxClick(WPARAM wParam,LPARAM lParam);	//BCGM_GRID_HEADERCHECKBOX_CLICK
	afx_msg LRESULT OnGrid_AdjustLayout(WPARAM wParam,LPARAM lParam);			//BCGM_GRID_ADJUST_LAYOUT
	afx_msg LRESULT OnGrid_FindResult(WPARAM wParam,LPARAM lParam);				//BCGM_GRID_FIND_RESULT
	afx_msg LRESULT OnGrid_ColumnBtnClick(WPARAM wParam,LPARAM lParam);			//BCGM_GRID_COLUMN_BTN_CLICK
	afx_msg LRESULT OnGrid_ScaleChanged(WPARAM wParam,LPARAM lParam);			//BCGM_GRID_SCALE_CHANGED

	afx_msg LRESULT OnGrid_ItemLClick(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnGrid_ItemRClick(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnGrid_ItemDBLClick(WPARAM wParam,LPARAM lParam);			//BCGM_GRID_ITEM_DBLCLICK
	afx_msg LRESULT OnGrid_ItemChanged(WPARAM wParam,LPARAM lParam);			//BCGM_GRID_ITEM_CHANGED
	afx_msg LRESULT OnGrid_ItemHeadRClick(WPARAM wParam,LPARAM lParam);			//BCGM_GRID_ITEM_HEADRCLICK

	//��Ӧͷ������Ϣ BCGM_GRID_HEADER_SORT		by WangZY 2017/11/02
	afx_msg LRESULT OnGridHeaderSort(WPARAM wParam, LPARAM lParam);	

	//��Ӧɸѡ�иı����Ϣ BCGM_GRID_FILTER_BAR_CHANGED		by WangZY 2017/11/02
	afx_msg LRESULT OnGridFilterBarChanged(WPARAM wParam, LPARAM lParam);

   afx_msg LRESULT OnGridFilterBarEnterMsg(WPARAM wParam, LPARAM lParam);

   afx_msg LRESULT OnGridFilterBarClearBtnMsg(WPARAM wParam, LPARAM lParam);

  
	afx_msg LRESULT OnGridTitleFilterChanged(WPARAM wParam, LPARAM lParam);

	afx_msg void OnBnClickedBtnPageup();
	afx_msg void OnBnClickedBtnPagedown();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	//�б���˵��������
	afx_msg void OnGridHeadMenu(UINT id);

   afx_msg void OnDestroy();//����ʱ��������ʽ yangjr 2017-12-20
   virtual BOOL PreTranslateMessage(MSG* pMsg);
  
};
