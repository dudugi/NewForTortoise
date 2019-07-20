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


//获取CPU时间戳,(单位:纳秒级)		by WangZY 2017/09/28
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

// CDlgBCGGrid 对话框

class CDlgBCGGrid : public CBCGPDialog
{
	DECLARE_DYNAMIC(CDlgBCGGrid)

public:
	CDlgBCGGrid(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgBCGGrid();

// 对话框数据
	enum { IDD = IDD_DLGBCGGRID };

	enum EM_SEL_TYPE
	{
		emNull = 0,	
		emSel,					//改变选中行的数据	
		emJudgeHasSel,			//判断是否有选中行，不做数据修改
		emAllOnGrid,			//改变网格上所有行的数据
		emUnSel,					//改变网格上未选中的行的数据
		emAllData,				//改变所有数据（包含在网格上和不在网格上的）
	};

   enum EM_REFRESH_DB_MODE
   {
      emRDM_Restart = 0,   //重新查询
      emRDM_CurPage,       //查询当前页
      emRDM_PrePage,       //查询上一页
      emRDM_NextPage,      //查询下一页
   };

	//外部响应的消息		by WangZY 2017/06/13
	enum EM_MSG_OUTSIDE
	{
		UM_RCLICK_GRID = (WM_USER + 20/* + NM_RCLICK*/),	//鼠标右键单击Grid消息
		UM_DBLCLK_GRID,/* = (WM_USER + 20 + NM_DBLCLK),*/	//鼠标左键双击Grid消息
		UM_LCLICK_GRID,/* = (WM_USER + 20 + NM_CLICK),*/	//鼠标左键单击Grid消息

		UM_UPDATE_DATA_CHANGED,							//数据信息发生变化
		UM_ATTRI_FIELD_HAS_ADD_MSG,			//表格属性的字段数据有添加显示		by WangZY 2018/02/01
      UM_PAGINATION_REFRESH_DATA_MSG,     //通知外部需要刷新数据的消息		by WangZY 2018/06/06

	};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

	void InitBCGGridCtrl();

private:
	BOOL m_bShowLeftHeaderColumn;					//是否显示左侧序号列		by WangZY 2017/11/21
	BOOL m_bShowLineNumber;						//是否左侧序号列显示行号		by WangZY 2017/11/21
	int  m_nLeftHeaderColumnWidth;				//左侧序号列的宽度		by WangZY 2017/11/21
	BOOL m_bUserPaginationMode;					//使用自定义分页模式		by WangZY 2017/11/08
	CBCGPButton m_btnPageUp;								//上一页按钮		by WangZY 2017/10/30
	CBCGPButton m_btnPageDown;							//下一页按钮		by WangZY 2017/10/30
	CBCGPStatic m_textPageInfo;							//分页信息		by WangZY 2017/10/30
	BOOL		m_bShowPageInfo;						//是否显示分页控件	by WangZY 2017/10/30
   EM_PAGINATION_MODE m_emPMPaginationModeFlag;     //分页模式标志
   CPageInfo m_infoPage;   //分页模式下的分页信息
	CQLBCGGridCtrl*		m_pBCGGrid;
	//CProgressCtrl			m_progressCtrl;

	S_GridCtrl_TableAttri		m_tableAttri;		//表格相关属性
	MAP_GridCtrl_AllData		m_tableData;		//表格数据

	//_RecordsetPtr m_dbRecordSetPtr;			//网格数据记录集指针

	map<CString,BOOL>			m_mapColEdit;		//<数据库字段，是否可编辑>
	map<CString,int>			m_mapColID;			//<数据库字段，列id>
	map<int,CString>			m_mapColWithFieldId;	//<列id, 数据库字段ID>
	map<int,CString>			m_mapColName;		//<列id,显示名称>
	map<CString,CString>		m_mapCol_Name_ID;	//<数据库ID，显示名称>

	map<CString/*FieldId*/, CString /*FilterInfo*/>	m_mapFilterInfo;	//筛选信息

	vector<int>		m_vecFrozenIndex;			//冰冻列index

	CString m_strSortInfo;		//排序的信息

	std::map<int/*colIndex*/,CString/*strFieldId*/> m_mapShowCol;	//		by WangZY 2018/01/31
	BOOL m_bUseNewAttri;						//新的表属性方式	by WangZY 2018/01/31

	// wangzl 2017-12-11 列标题菜单处理
	BOOL						m_bEnableColHeadMenu;//是否启用列点击菜单
	int							m_nRClickHeadCol;//右键点击的列
	// wangzl 2017-12-11 列标题菜单处理 end
   CString m_tableStyleFileName;//表格样式的xml文件名 yangjr 2017-12-13

   BOOL		m_bKeyShiftDown;	//shift 按下	add by lida 2018/01/31
   BOOL		m_bKeyCtrlDown;		//ctrl	按下	add by lida 2018/01/31
	std::vector<CString> m_vecNeedfulFieldId;	//必要的字段	by WangZY 2018/02/01
	std::vector<CString> m_vecNeedfulPackageFieldId;	//必要打包数据的字段	by WangZY 2018/02/01

	int		m_nCheckRowCount;			//勾选的行数量
	int		m_lastShowCheckRowCount;	//上次显示的勾选的行数量列

	//列标题过滤器列表信息 		by WangZY 2018/03/07
	std::map<CString/* strFieldId*/,vector<CString>> m_mapFilterListInfo;

	//使用列标题过滤器的列 		by WangZY 2018/03/07
	std::vector<CString /*strFieldId*/> m_vecFilterId;

   std::map<CString,CString> m_mapTongJiValue;/*统计数据*/
	 
protected:
	//内部用的接口,千万不要改外用:设置Cell的item的值		by WangZY 2018/02/01
	BOOL _in_SetGridItemValue(__in CBCGPGridItem *pItem, __in CString &strValue);
	//生成必需打包的数据字段		by WangZY 2018/02/01
	BOOL CreateNeedfulPackageFieldId();
	//打包生成标题行的打印需要xml信息		by WangZY 2017/06/28
	BOOL CreatePrintFieldXml(__out CString &strFieldXml);

	//打包生成数据行的打印需要xml信息		by WangZY 2017/06/28
	BOOL CreatePrintDataXml(__out CString &strDataXml);

	//打包分页模式下生成数据行的打印需要xml信息		by WangZY 2018/01/19
	BOOL CreateUsedPaginationModePrintDataXml(__out CString &strDataXml);

	//打包生成合计行的打印需要xml信息		by WangZY 2017/06/28
	BOOL CreatePrintStatisticRowXml(__out CString &strStatisticRowXml);

	BOOL GetShowColID(vector<int>& vecShowCol);

	//数据的数值加上某数值
	BOOL AddDataValue(__in const CString &strValue, __inout S_GridCtrl_FieldData &data);  

	//刷新数据到网格上		by WangZY 2017/10/31
	void RefreshDataInfoToGrid(int nPageType =0,BOOL bGoFirstPage = TRUE);

	//刷新分页控件信息		by WangZY 2017/10/31
	void RefreshPageInfo(int nPageCount,int nCurPage, int nPageSize);

	//刷新排序信息
	void RefreshDataBySort();

	//刷新筛选过滤信息		by WangZY 2017/11/02
	void RefreshDataByFilter();

	//刷新统计行信息		by WangZY 2017/11/23
   //bFenYeModeSvrGridTongJi 是否是数据库分页模式，且统计数据有表格内部计算
	BOOL RefreshGridStatisticRow(CQLBCGGridCtrl* pGrid,BOOL bFenYeModeSvrGridTongJi = FALSE);

   //保存属性到xml
   BOOL SaveAtrriToXml(CString strXmlName);

   //多行选择时，设置check box 的状态
   void SetMulRowSelectCheck(BOOL bCheck);

   //统计栏显示勾选条数 add by lida 
   void SetFootValue_CheckNum(int k);	

   BOOL GetTongJiDataByAttri(const S_GridCtrl_TableAttri &tableAttri,__out std::map<CString/*strFieldId*/,ENUM_COLSUMTYPE> &mapTongJiData);
public:
   //设置风格缩放比率		by WangZY 2018/06/14
   void SetScale(double dblScale = 1.0f);

   // 允许外部设置主题颜色 2018-5-29 wangzl
   const CBCGPGridColors& GetColorTheme () const;
   void SetColorTheme (const CBCGPGridColors& theme, BOOL bRedraw = TRUE, BOOL bFullCopy = FALSE);

   //滚动到目标行 wangzl 2018-06-11
   void ScrollToRow(__in const int & nRow);

   // 允许外部设置表格内部的颜色 2018-5-29 wangzl
   BOOL SetCustomColors (			// Use (COLORREF)-1 for the default color
      COLORREF	clrBackground,
      COLORREF	clrText,
      COLORREF	clrGroupBackground,
      COLORREF	clrGroupText,
      COLORREF	clrLeftOffset,
      COLORREF	clrLine);
   // 设置表格字体 2018-6-14 wangzl
   void SetGridFont(CFont* pFont, BOOL bRedraw = TRUE);
   // 编辑表格的项 2018-6-14 wangzl
   BOOL EditGridItem (const int & nRow,const int & nCol);

   void SetRowBackgroundColor(int iRow,MAP_GridCtrl_RowData& row_data,COLORREF bkcolor);

	//设置必要的字段	by WangZY 2018/02/01
	void SetNeedfulFieldId(std::vector<CString /*strFieldId*/> vecNeedfulFieldId);

	void RefreshBCGGridCtrl();		//刷新

	//设置显示左侧序号列(该接口必须在对话框窗口创建之前调用)		by WangZY 2017/11/21
	void SetShowLeftHeaderColumn(BOOL bShowLeftHeaderColumn = TRUE);

	//设置左侧序号列显示行号	(该接口必须在对话框窗口创建之前调用)	by WangZY 2017/11/21
	void SetShowLeftLineNumber(BOOL bShowLineNumber = TRUE);

	//设置显示左侧序号列的宽度(该接口必须在对话框窗口创建之前调用)		by WangZY 2017/11/21
	void SetShowLeftHeaderColumnWidth(int nWidth=35);

   void SetAndRefreshPageInfo(CPageInfo &info);

	//设置使用用户自定义分页模式标志(该接口必须在对话框窗口创建之前调用)		by WangZY 2017/11/08
	void SetUserPaginationMode(BOOL bUserPaginationMode = TRUE,EM_PAGINATION_MODE emPMPaginationMode = emPM_Local);
	
	//获取使用用户自定义分页模式标志		by WangZY 2017/11/08
	BOOL GetUserPaginationMode() const;

	//通过数据集设置网格数据		by WangZY 2017/10/25
//	void SetGridDataInfoByRecordSetPtr(_RecordsetPtr &dbRecordSetPtr);

	void PrintTime_Test(CString strTitle = _T(""));	//打印测试时间

	//设置网格可编辑		
	void SetGridEnableEdit(BOOL bEnableEdit = TRUE);

	//设置网格属性信息（表头列相关信息）与网格数据信息,注：在Create之后调用！
	BOOL SetGridAttriAndDatas(__in const S_GridCtrl_TableAttri &tableAttri,__in const MAP_GridCtrl_AllData &data,int iShowColAlign = HDF_CENTER);

	//设置网格属性信息（表头列相关信息）, bClear = 是否清空数据, iShowColAlign = 居中，左，右显示
	BOOL SetGridAttriInfo(__in const S_GridCtrl_TableAttri &tableAttri,
		int iShowColAlign = HDF_CENTER);

	//设置网格数据信息
	BOOL SetGridDataInfo(__in const MAP_GridCtrl_AllData &data);

	//获取网格属性信息
	BOOL GetGridAttriInfo(__out S_GridCtrl_TableAttri &tableAttri);

	//获取网格数据信息
	BOOL GetGridDataInfo(__out MAP_GridCtrl_AllData &data);

	//刷新网格控件的信息
	void RefreshGridCtrlInfo(__in BOOL bEnsureVisableFirstDataRow = TRUE);

	//改变某一列的数据信息 ,目前只支持修改单元格内数据，暂不支持下拉列表等数据	
	int ChangeDataInfoByFieldId(__in const CString &strFieldId,__in const S_GridCtrl_FieldData &dataInfo,__in const EM_SEL_TYPE &nSelType = emSel);

	//改变某一列的数据值		
	int ChangeDataInfoByFieldId(__in const CString &strFieldId,__in const CString &strValue,__in const EM_SEL_TYPE &nSelType = emSel);

	//新的设置网格属性信息（表头列相关信息）, bClear = 是否清空数据, iShowColAlign = 居中，左，右显示
	BOOL SetGridAttriInfoNew(__in const S_GridCtrl_TableAttri &infoTableAttri,
		__in int iShowColAlign = HDF_CENTER);

   //参数见:CBCGPGridCtrl::Direction，例如
   void SetEnterGoDirection(UINT nDirection,BOOL bEnable = TRUE);      //设置启用与回车跳转方向 add by lida 2018/05/29

	//新的刷新网格控件的信息的接口		by WangZY 2018/01/31
	void RefreshGridCtrlInfoNew(__in BOOL bEnsureVisableFirstDataRow = TRUE);

public:		//以下为获取数据的接口:
   
   //获取筛选信息		by WangZY 2018/06/06
   BOOL GetFilterFieldInfo(__out std::map<CString/*strFieldId*/,CString /*strFilter*/> &mapFilterInfo);

   BOOL SetFilterFieldInfo(__in std::map<CString/*strFieldId*/,CString /*strFilter*/> &mapFilterInfo);

   //获取排序信息		by WangZY 2018/06/07
   BOOL GetSortFieldInfo(__out CString &strFieldId, __out BOOL &bAscening);
   
   //设置排序信息		by WangZY 2018/06/07
   BOOL SetSortFieldInfo(__in CString strFieldId, __in BOOL bAscening);
	
   //获取必需打包的数据字段		by WangZY 2018/02/01
	BOOL GetNeedfulPackageFieldId(
		__out std::vector<CString/*strFieldId*/> &vecFieldId,
		__in BOOL bNewCreate = FALSE);

   BOOL GetShowFieldId(__out std::vector<CString> &vecShowFieldId,
      __out std::vector<CString> &vecFieldName);

   //BOOL GetShowFieldInfo(__out std::vector<>)
	//获取网格上最后一行数据的数据索引
	BOOL GetLastRowIndex(__out int &nIndex);

	//获取选中的数据,返回值为选择的数据行数量		 
	int GetSelectData(__out MAP_GridCtrl_AllData &mapSelectData);

	//获取显示的数据,返回值为显示的数据行数量
	int GetShowData(__out MAP_GridCtrl_AllData &mapShowData);

	//获取显示的数据对应数据里的索引值,返回值为显示的数据行数量
	int GetShowDataIndex(__out std::vector<int/*dataIndex*/> &vecShowIndex);

	int GetShowDataSelIndex(__out std::vector<int/*dataIndex*/> &vecShowSelIndex);

	//获取选中check = true 的数据索引号	 
	int GetSelectDataIndex(__out std::vector<int/*dataIndex*/> &vecSelectIndex);

	int GetSelectDataIndex();

	//获取选中的数据对应网格控件上的行号,返回值为选择的数据行数量		 
	int GetSelectRowNo(__out std::vector<int/*rowIndex*/> &vecSelectIndex);

	//根据网格的行号获取某一行的数据的索引
	BOOL GetRowIndexofDataInfo(__out int &nDataRowIndex, __in int nGridRow);

	//根据网格的行号获取某一行的数据
	BOOL GetRowIndexofDataInfo(__out MAP_GridCtrl_RowData& data_row, __in int nGridRow);

	//根据网格的行号与列号获取一格的数值
	BOOL GetValueByGridRowAndCol(__out CString &strValue,__in int nGridRow,__in int nGridCol);

	//根据网格的行号与列号获取一格的数据
	BOOL GetValueByGridRowAndCol(__out S_GridCtrl_FieldData &data,__in int nGridRow, __in int nGridCol);

	//根据网格的行号与列字段Id获取一格的数值
	BOOL GetValueByGridRowAndFieldId(__out CString &strValue,__in int nGridRow,__in CString strFieldId);

	//根据网格的行号与列字段Id号获取一格的数据
	BOOL GetValueByGridRowAndFieldId(__out S_GridCtrl_FieldData &data,__in int nGridRow, __in CString strFieldId);

	//根据字段ID以及对应的字符串数值 获取需要字段的值
	BOOL GetValuebyFieldIdAndValue(__in CString strFieldId,__in CString strValue,__in CString strTarField,__out CString& strTarValue);

	//获取预打印数据的xml信息		
	BOOL GetPrintDataXmlText(__out CString &strFieldXml, __out CString &strDataXml,__out CString &strStatisticRowXml);

	//根据数据索引取一条数据的打印数据的xml信息		
	BOOL GetRowPrintDateXmlTextDataIndex(__in int nDataIndex, __out CString &strDataXml);

	//获取选中数据的全字段的打印数据的xml信息，多行选择则打印勾选的，非多行选择则打印当前选中行的		
	BOOL GetSelectedAllFieldPrintDataXmlText(__out CString &strDataXml);

	//获取全字段的列标题的xml信息		
	BOOL GetAllFieldXml(__out CString &strFieldXml);

	// 获取焦点行
	int GetFocusRow();

	// 获取焦点行数据
	BOOL GetFocusRowData(MAP_GridCtrl_RowData & rowdata);

	// 获取焦点行指定字段的数据 
	BOOL GetFocusRowValue(__out CString & strValue,__in CString strFieldId);

	//获取焦点行的数据索引	
	BOOL GetFocusRowDataIndex(__out int &nDataIndex);

	//根据字段id获取检索与筛选的过虑信息以及是否使用过虑信息的状态
	BOOL GetFilterInfoByFieldId(__out BOOL &bUseFilter, __out SERCH_DATA &infoFilter, __in const CString &strFieldId);

	CString GetColShowName(int nCol);		//显示的名称

	CString GetColName(int nCol);			//数据库字段名称

	int GetCheckRowNum();		//获取勾选的条数

   //获取分页模式每页行数 yangjr 2018/7/6
   int GetFenYePageRows();

   BOOL GetExportExcelData(std::vector<std::vector<CString>> &vecDatas);

public:	//以下为设置数据的接口:

	//某一列的数值加上一个数值
	BOOL AddFieldValueByFieldId(__in CString strValue,__in const CString &strFieldId, __in const EM_SEL_TYPE &nSelType = emSel);

	//根据网格行号设置非多行选择状态下的行焦点状态		
	BOOL SetFocusRowByGridRow(__in int nRowNo);

	//根据数据索引设置非多行选择状态下的行焦点状态	
	BOOL SetFocusRowByDataIndex(__in int nDataIndex);

   //根据字段+值设定焦点行 yangjr 2018/6/12
   BOOL SetFocusRowByFieldIdAndValue(__in CString strFieldId, __in CString strFieldValue);

	//设置反选 add by lida 2018/03/15
	BOOL SetMultiSelectTurnOver();

	//多行选择的全选/取消全选，bVisibleOnly 是否只针对可见的行操作
	BOOL SetMultiSelectCheckAll(BOOL bCheck = TRUE,BOOL bVisibleOnly = FALSE);

	//根据网格行号设置多行选择状态下的行勾选状态		
	BOOL SetMultSelectCheckByGridRows(__in const std::vector<int/*RowNo*/> &vecRowNo,__in BOOL bCheck = TRUE);

	//根据列字段Id设置多行选择状态下的行勾选状态
	BOOL SetMultiSelectCheckByFieldId(__in CString strFieldId, __in CString strFieldValue, __in BOOL bCheck = TRUE);

	//根据网格的行号与列字段Id设置一格的数值
	BOOL SetValuebyGridRowAndFieldId(__in CString &strValue,__in int nGridRow,__in CString strFieldId);

	//根据网格的行号与列字段Id设置一格的数值
	BOOL SetValuebyGridRowAndFieldId(__in S_GridCtrl_FieldData &data,__in int nGridRow,__in CString strFieldId);

	//根据网格的行号与列号设置一格的数值
	BOOL SetValueByGridRowAndCol(__in CString &strValue,__in int nGridRow,__in int nGridCol);

	//根据数据的行索引与列字段Id设置一格的数值
	BOOL SetValuebyDataRowIndexAndFieldId(__in CString &strValue,__in int nDataRowIndex,__in CString strFieldId);

	//根据字段ID以及对应的字符串数值 设置需要设置字段的值
	BOOL SetValuebyFieldIdAndValue(__in CString strFieldIdIndex,__in CString &strValueIndex,__in CString strTarFieldID,__in CString strTarValue);

	//判断鼠标点击是否是数据有效区
	BOOL IsValidDataRgn();//TRUE有效

	//判断数据里是否有该字段值的数据
	static BOOL IsInfoInMapByFieldId(__in const MAP_GridCtrl_AllData &mapData,__in const CString &strFieldId,__in const CString &strValue);

	//根据网格的列号获取列字段ID
	BOOL GetFieldIdByGridCol(__out CString &strFieldId, __in int nGridCol);

	//根据列字段ID获取网格的列号
	BOOL GetGridColByFieldId(__out int &nGridCol, __in CString strFieldId);

	//根据字段id设置筛选的过虑信息		
	BOOL SetFilterInfoByFieldId(__in const std::vector<CString> &vecFilter,__in const CString &strFieldId);

	//根据字段id设置检索的过虑信息	
	BOOL SetFilterInfoByFieldId(__in const CString &strFilter, __in const CString &strFieldId);

	//根据某字段Id列进行排序		
	BOOL SortByFieldId(__in const CString &strFieldId, BOOL bAscending = TRUE);

	//设置根据列号进行排序		
	BOOL SortByColumn(__in const int nColumn, BOOL bAscending = TRUE);

	//判断某格是否可以编辑		
	BOOL IsCanEdit(int nRow, int nColumn);

	//是否是有效的数据行，才允许处理一些事件：比如弹出窗口 
	BOOL IsValidRow(__in int nRow);

	BOOL SetSelWholeRow(int iRow,int iCol,BOOL bLeftDown = TRUE);		//选择一行,默认左键

	//是否启用列标题菜单 wangzl 2017-12-11
	void EnableColHeadMenu(BOOL bEnable = TRUE){m_bEnableColHeadMenu = bEnable;}
   	
	//清空当前的排序状态		by WangZY 2017/12/12
	BOOL ClearSortState();

   //表格样式的xml文件名 yangjr 2017-12-13
   void SetTableStyleFileName(CString tableStyleFileName){m_tableStyleFileName = tableStyleFileName;}

   //设置网格表头 checkbox 状态 add by lida 2018/02/02
   void SetHeaderCheckBoxState(BOOL bCheck);

   //获取行、列数量
   void GetRow_Col_Num(int& iRow,int& iCol);

	//设置某列标题头过滤		by WangZY 2018/03/07
	BOOL EnableFilterColumns(__in vector<CString/*strFieldId*/> vecFieldIds,
		__in BOOL bEnable=TRUE );

	//设置标题过滤自定义列表的接口		by WangZY 2018/03/07
	BOOL SetColumnFilterList(__in CString strFieldId, __in const vector<CString> &vecLst);

	//生成分页模式下的标题头过滤的相关字串信息		by WangZY 2018/03/12
	CString DealCalcTitleFilter();

   //获取表格的统计字段数据 yangjr 2018/6/20
   BOOL GetTongJiData(__out std::map<CString/*strFieldId*/,ENUM_COLSUMTYPE> &mapTongJiData);

   //设置表格的统计字段显示数据 yangjr 2018/6/21
   void SetTongJiData(__in const std::map<CString,CString> &mapTongJiValue/*统计数据*/);

   //导出表格数据到excel yangjr 2018/7/19
   BOOL ExportExcel();
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	
	afx_msg LRESULT OnGrid_BeginPlaceEdit(WPARAM wParam,LPARAM lParam);			//BCGM_GRID_ITEM_BEGININPLACEEDIT
	afx_msg LRESULT OnGrid_EndPlaceEdit(WPARAM wParam,LPARAM lParam);			//BCGM_GRID_ITEM_ENDINPLACEEDIT
	afx_msg LRESULT OnGrid_SelectChanged(WPARAM wParam,LPARAM lParam);			//BCGM_GRID_SEL_CHANGED
	afx_msg LRESULT OnGrid_HideColunmChooser(WPARAM wParam,LPARAM lParam);		//BCGM_GRID_ON_HIDE_COLUMNCHOOSER
	afx_msg LRESULT OnGrid_BeginDrag(WPARAM wParam,LPARAM lParam);				//BCGM_GRID_BEGINDRAG
	afx_msg LRESULT OnGrid_ColumnClick(WPARAM wParam,LPARAM lParam);			//BCGM_GRID_COLUMN_CLICK
	
	//响应每行的左侧的CheckBox的点击消息		by WangZY 2017/11/22
	afx_msg LRESULT OnGrid_RowCheckBoxClick(WPARAM wParam,LPARAM lParam);		//BCGM_GRID_ROW_CHECKBOX_CLICK
	//响应标题头的左侧的CheckBox的点击消息			by WangZY 2017/11/22
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

	//响应头排序消息 BCGM_GRID_HEADER_SORT		by WangZY 2017/11/02
	afx_msg LRESULT OnGridHeaderSort(WPARAM wParam, LPARAM lParam);	

	//响应筛选行改变的消息 BCGM_GRID_FILTER_BAR_CHANGED		by WangZY 2017/11/02
	afx_msg LRESULT OnGridFilterBarChanged(WPARAM wParam, LPARAM lParam);

   afx_msg LRESULT OnGridFilterBarEnterMsg(WPARAM wParam, LPARAM lParam);

   afx_msg LRESULT OnGridFilterBarClearBtnMsg(WPARAM wParam, LPARAM lParam);

  
	afx_msg LRESULT OnGridTitleFilterChanged(WPARAM wParam, LPARAM lParam);

	afx_msg void OnBnClickedBtnPageup();
	afx_msg void OnBnClickedBtnPagedown();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	//列标题菜单点击函数
	afx_msg void OnGridHeadMenu(UINT id);

   afx_msg void OnDestroy();//销毁时保存表格样式 yangjr 2017-12-20
   virtual BOOL PreTranslateMessage(MSG* pMsg);
  
};
