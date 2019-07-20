// DlgPane3Item3.cpp : 实现文件
//
#include "stdafx.h"
#include "QLSvrMgn.h"
#include "DlgPane1Item3.h"
#include "MyADOConnEx.h"
#include "DBDatabaseFields.h"
#include "ADOConn\ADOConn.h"


// CDlgPane1Item3 对话框

IMPLEMENT_DYNAMIC(CDlgPane1Item3, CTabDialog)

CDlgPane1Item3::CDlgPane1Item3(CWnd* pParent /*=NULL*/)
	: CTabDialog(CDlgPane1Item3::IDD, pParent)
{
	m_pADOConn = new CMyADOConnEx(TRUE);
	/*m_strDatabase = _T("");*/
}

CDlgPane1Item3::~CDlgPane1Item3()
{
	if(nullptr != m_pADOConn)
	{
	    delete m_pADOConn;
		m_pADOConn = nullptr;
	}
}

void CDlgPane1Item3::DoDataExchange(CDataExchange* pDX)
{
   CDialogEx::DoDataExchange(pDX);
   DDX_Control(pDX, IDC_SAVE_DATABASE_TRIGGER, m_edit_trigger);
}


BEGIN_MESSAGE_MAP(CDlgPane1Item3, CTabDialog)
	ON_BN_CLICKED(IDC_SAVE_DATABASE_BUTTON, &CDlgPane1Item3::OnBnClickedSaveDir)
	ON_BN_CLICKED(IDC_UPDATE_DATABASE_BUTTON, &CDlgPane1Item3::OnBnClickedUpdateDatabaseButton)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CDlgPane1Item3::OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_UPDATE, &CDlgPane1Item3::OnBnClickedBtnUpdate)
	ON_BN_CLICKED(IDC_UPDATE_FUNCTION_BUTTON, &CDlgPane1Item3::OnBnClickedUpdateFunctionButton)
	ON_BN_CLICKED(IDC_BTN_UPDATE_FUNCTION, &CDlgPane1Item3::OnBnClickedBtnUpdateFunction)
   ON_BN_CLICKED(IDC_BTN_SAVE_TRIGGER, &CDlgPane1Item3::OnBnClickedBtnSaveTrigger)
   ON_BN_CLICKED(IDC_BTN_DIR_TRIGGER, &CDlgPane1Item3::OnBnClickedBtnDirTrigger)
   ON_BN_CLICKED(IDC_UPDATE_TRIGGER_BUTTON, &CDlgPane1Item3::OnBnClickedUpdateTriggerButton)
   ON_BN_CLICKED(IDC_BTN_UPDATE_TRIGGER, &CDlgPane1Item3::OnBnClickedBtnUpdateTrigger)
END_MESSAGE_MAP()


// CDlgPane3Item3 消息处理程序
void CDlgPane1Item3::OnBnClickedSaveDir()
{
	CString strDefPath = _T("");
	GetDlgItemText(IDC_SAVE_DATABASE_EDIT,strDefPath);

	CString strFilter = _T("文件(*.qlf)|*.qlf||");
	CString strNewPath =_T("");
	COleDateTime CurrentTime=COleDateTime::GetCurrentTime();
	CString strFile = _T("");
	strFile.Format(_T("%d_%d_%d_%d时%d分.qlf") ,CurrentTime.GetYear(), CurrentTime.GetMonth(),CurrentTime.GetDay(), CurrentTime.GetHour(), CurrentTime.GetMinute());  

	if (m_CDirectroy.OpenDirFile(strNewPath,strDefPath,strFile,strFilter,FALSE))
	{
		SetDlgItemText(IDC_SAVE_DATABASE_EDIT, strNewPath);
		theApp.OnWriteIni(_T("UpdateDatabasePath"), _T("SaveDatabase"), strNewPath,INI_SQLSVR);
	}
}


void CDlgPane1Item3::OnBnClickedBtnSave()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strFilePath = _T("");
	GetDlgItemText(IDC_SAVE_DATABASE_EDIT,strFilePath);
	strFilePath.Trim();
	int nPos = strFilePath.ReverseFind('\\');
	CString strPath = _T("");
	if (nPos>-1)
	{
		strPath = strFilePath.Left(nPos);
	}

	if (strFilePath.IsEmpty()||(!PathFileExists(strPath)))
	{
		theApp.OnShowDesktopAlert(_T("请选择保存路径!"),COLOR_TIP_WARN,2,AfxGetMainWnd());
	}
	else
	{
      if (!theApp.GetStateConnectDB())
      {
         theApp.OnShowDesktopAlert(_T("无法连接到数据库"),COLOR_TIP_WARN,2,AfxGetMainWnd());
         return;
      }

		if(IDOK == MessageBox(_T("确定【保存数据表】文件吗？"),_T("提示"),MB_OKCANCEL|MB_ICONQUESTION))
		{
			CString strDatabase = _T("");
			theApp.OnReadIni(_T("ConfigureInfo"), _T("DatabaseName"), strDatabase,INI_SQLSVR);//获取数据库名称

			SaveDatabaseToFile(strFilePath, strDatabase);
		}	
	}
}


void CDlgPane1Item3::SaveDatabaseToFile(CString strFile, CString strDatabase /*= _T("[QLPLM]")*/)
{
   
	theApp.ShowLoading();
	BOOL bRet = TRUE;
	m_DBDatabaseTableList.Empty();
	CString strSQL = _T(""), strTemp = _T("");
	strSQL.Format(_T("use [%s] select name from sysobjects where xtype='U'"), strDatabase);
	m_pADOConn->GetTableName(strSQL);
   auto it = m_pADOConn->m_vecCString.begin();
   while(it != m_pADOConn->m_vecCString.end())
   {
      CString strTable = _T("");
      GetFieldsName(&m_DBDatabaseTableList, strDatabase, *it);
      if(m_DBDatabaseTableList.IsEmpty())
      {
         theApp.OnShowDesktopAlert(_T("该表格没有字段!"),COLOR_TIP_FAIL,2,AfxGetMainWnd());
         return;
      }
      it++;
   }
   bRet = m_DBDatabaseTableList.OnWriteFile(strFile);
	if(bRet)
	{
		theApp.OnShowDesktopAlert(_T("保存成功!"),COLOR_TIP_SUC,2,AfxGetMainWnd());
	}
	else
	{
		theApp.OnShowDesktopAlert(_T("保存文件失败!"),COLOR_TIP_FAIL,2,AfxGetMainWnd());
	}
	theApp.CloseLoading();
}

void CDlgPane1Item3::GetFieldsName(CDBDatabaseTableList *pDBDatabaseTableList,CString strDatabase, CString strTable)
{
	CDBDatabaseTable* pDBDatabaseTable = new CDBDatabaseTable;
	pDBDatabaseTable->m_listFields.Empty();
	CString strQuery = _T("");
	strQuery.Format(_T("sp_pkeys [%s] use [%s]"), strTable, strDatabase);//获取主键字段
	m_pADOConn->GetRecordSet(strQuery);
   CString strFieldsPrimary = _T("");
   if (!m_pADOConn->adoEOF())
   {
      strFieldsPrimary = m_pADOConn->GetValueString(_T("COLUMN_NAME")); 
   }
	strQuery.Format(_T("sp_mshelpcolumns [%s] use [%s]"), strTable, strDatabase);
	m_pADOConn->GetRecordSet(strQuery);
	CDBDatabaseFields* pDBDatabaseFields = new CDBDatabaseFields;
	while(!m_pADOConn->adoEOF())
	{
		pDBDatabaseFields->m_strFieldsName = m_pADOConn->GetValueString(DBDatabaseFields_Key_Name);
		if(strFieldsPrimary == pDBDatabaseFields->m_strFieldsName)
		{
			pDBDatabaseFields->m_bFieldsPrimary = TRUE;
		}
		else
		{
			pDBDatabaseFields->m_bFieldsPrimary = FALSE;
		}
		pDBDatabaseFields->m_strFieldsType = m_pADOConn->GetValueString(DBDatabaseFields_Key_Type);
		pDBDatabaseFields->m_nFieldsLength = m_pADOConn->GetValueInt(DBDatabaseFields_Key_Length);
      if (pDBDatabaseFields->m_nFieldsLength == 0) //nvarchar = 0 标识max
      {
         pDBDatabaseFields->m_nFieldsLength = -1;
      }
		pDBDatabaseFields->m_nFieldsPrec = m_pADOConn->GetValueInt(DBDatabaseFields_Key_Prec);
		pDBDatabaseFields->m_nFieldsScale = m_pADOConn->GetValueInt(DBDatabaseFields_Key_Scale);
		pDBDatabaseFields->m_nFieldsSeed = m_pADOConn->GetValueInt(DBDatabaseFields_Key_Seed);
		pDBDatabaseFields->m_nFieldsIncrement = m_pADOConn->GetValueInt(DBDatabaseFields_Key_Increment);

		pDBDatabaseTable->m_listFields.AddItem(pDBDatabaseFields);

		m_pADOConn->MoveNext();
	}
	pDBDatabaseTable->m_strTableName = strTable;

	pDBDatabaseTableList->AddItem(pDBDatabaseTable);

	if(pDBDatabaseTable)
	{
		delete pDBDatabaseTable;
		pDBDatabaseTable = nullptr;
	}
	if(pDBDatabaseFields)
	{
		delete pDBDatabaseFields;
		pDBDatabaseFields = nullptr;
	}
}


void CDlgPane1Item3::SaveTriggerToFile(CString strFile)
{
   theApp.ShowLoading();
   BOOL bRet = TRUE;
   
   if(GetTrigger(strFile))
   {
      theApp.OnShowDesktopAlert(_T("保存成功!"),COLOR_TIP_SUC,2,AfxGetMainWnd());
   }
   else
   {
      theApp.OnShowDesktopAlert(_T("保存文件失败!"),COLOR_TIP_FAIL,2,AfxGetMainWnd());
   }
   theApp.CloseLoading();
}


BOOL CDlgPane1Item3::GetTrigger(CString strFile)
{
   vector<CString> vecTrigger;
   CString strQuery = _T("select name from sysobjects where xtype='TR'");  //所有触发器
   m_pADOConn->GetRecordSet(strQuery);
   while(!m_pADOConn->adoEOF())
   {
      CString strTRName = m_pADOConn->GetValueString(_T("name"));
      vecTrigger.push_back(strTRName);
      m_pADOConn->MoveNext();
   }
   if (vecTrigger.size() <= 0)
   {
      return FALSE;
   }

   vector<CString> vecText;
   for (int i=0;i<(int)vecTrigger.size();++i)
   {
      CString strSql;
      strSql.Format(_T("select text from syscomments where ID = object_ID(N'%s')"),vecTrigger[i]);
      m_pADOConn->GetRecordSet(strSql);
      CString strText;
      if(!m_pADOConn->adoEOF())
      {
         strText.Format(_T("if exists(select name from sysobjects where xtype='TR' and name = N'%s')\r\ndrop trigger %s\r\nGO\r\n"),vecTrigger[i],vecTrigger[i]);
         vecText.push_back(strText);
         strText = m_pADOConn->GetValueString(_T("text")) + _T("\r\n");
         strText.Replace(_T("\r\n\r\n\r\n"),_T("\r\n"));
         strText.Replace(_T("\r\n\r\n"),_T("\r\n"));
         vecText.push_back(strText);
         vecText.push_back(_T("GO\r\n"));
      }
   }

   //设置中文模式，不然无法写入中文
   TCHAR* old_locale = _tcsdup( _tsetlocale(LC_CTYPE,NULL) );  
   _tsetlocale( LC_CTYPE, _T("chs")); 

   BOOL bRet = TRUE;
   CStdioFile mFile;	
   if (mFile.Open (strFile,CFile::modeCreate|CFile::modeWrite|CFile::shareExclusive))
   {
      for (int i=0;i<(int)vecText.size();++i)
      {
         mFile.WriteString(vecText[i]);
      }
      mFile.Close();
   }
   else
      bRet = FALSE;


   //操作完文件后要释放  
   _tsetlocale( LC_CTYPE, old_locale );  
   free( old_locale );
   return TRUE;
}



void CDlgPane1Item3::OnBnClickedUpdateDatabaseButton()
{
	// TODO: 在此添加控件通知处理程序代码	
	CString strDefPath = _T("");
	GetDlgItemText(IDC_CREATE_DATABASE_EDIT,strDefPath);

	CString strFilter = _T("文件(*.qlf)|*.qlf||");
	CString strNewPath =_T("");
	COleDateTime CurrentTime=COleDateTime::GetCurrentTime();
	CString strFile = _T("");

	if (m_CDirectroy.OpenDirFile(strNewPath,strDefPath,strFile,strFilter,TRUE))
	{
		SetDlgItemText(IDC_CREATE_DATABASE_EDIT, strNewPath);
		theApp.OnWriteIni(_T("UpdateDatabasePath"), _T("UpdateDatabase"), strNewPath,INI_SQLSVR);
	}
}


void CDlgPane1Item3::OnBnClickedBtnUpdate()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strFilePath = _T("");
	GetDlgItemText(IDC_CREATE_DATABASE_EDIT,strFilePath);
	if(strFilePath.IsEmpty() || (!PathFileExists(strFilePath)))
	{
		theApp.OnShowDesktopAlert(_T("请选择有效路径!"),COLOR_TIP_WARN,2,AfxGetMainWnd());
	}
	else
	{
      if (!theApp.GetStateConnectDB())
      {
         theApp.OnShowDesktopAlert(_T("无法连接到数据库"),COLOR_TIP_WARN,2,AfxGetMainWnd());
         return;
      }

      //读取数据库脚本，进行数据库名比对
      CString strTip;
      
      strTip.Format(_T("确定【更新数据表】文件吗？"));

		if(IDCANCEL == MessageBox(strTip,_T("提示"),MB_OKCANCEL|MB_ICONQUESTION))
		{
			return;
		}



		m_DBDatabaseTableList.Empty();
		theApp.ShowLoading();
		BOOL bRet = TRUE;
		if(m_DBDatabaseTableList.OnReadFile(strFilePath))
		{
			CString strDatabase = _T("");
			theApp.OnReadIni(_T("ConfigureInfo"), _T("DatabaseName"), strDatabase,INI_SQLSVR);//获取数据库名称
			CDBDatabaseTableList m_DBDatabaseTableListClient;
			int nRet = m_pADOConn->CreateDB(_T("[")+strDatabase+_T("]"));
			if(1 == nRet)
			{
				PutClientDatabaseToClist(m_DBDatabaseTableListClient, strDatabase);
				if(CompareDatabase(m_DBDatabaseTableList, m_DBDatabaseTableListClient, strDatabase))
				{
					theApp.OnShowDesktopAlert(_T("升级数据表成功!"),COLOR_TIP_SUC,2,AfxGetMainWnd());
				}
				else
				{
					theApp.OnShowDesktopAlert(_T("升级数据表失败!"),COLOR_TIP_FAIL,2,AfxGetMainWnd());
				}
			}
			else if(0 == nRet)	//创建数据库
			{
				CreateDatabaseFromFile(strDatabase, bRet);
			}
			else
			{
				theApp.OnShowDesktopAlert(_T("升级数据表失败!"),COLOR_TIP_FAIL,2,AfxGetMainWnd());
			}
			theApp.CloseLoading();
		}	
	}
}


void CDlgPane1Item3::PutClientDatabaseToClist(CDBDatabaseTableList &DBDatabaseTableListClient, CString strDatabase)
{
	CString strSQL = _T("");
	strSQL.Format(_T("use [%s] \
					 select name from sysobjects where xtype='U'"), strDatabase);
	m_pADOConn->GetTableName(strSQL);
	auto it = m_pADOConn->m_vecCString.begin();
	while(it != m_pADOConn->m_vecCString.end())
	{
		GetFieldsName(&DBDatabaseTableListClient, strDatabase, *it);
		it++;
	}
}

BOOL CDlgPane1Item3::CompareDatabase(CDBDatabaseTableList &DBDatabaseTableList, CDBDatabaseTableList &DBDatabaseTableListClient, CString strDatabase)
{ 
	int nTabSorCount = DBDatabaseTableList.GetCount();
	int nTabCliCount = DBDatabaseTableListClient.GetCount();
	int nI = 0, nJ = 0;
	for(; nI<nTabSorCount; nI++)
	{
		BOOL bFlag = FALSE;
		CDBDatabaseTable* pDBDatabaseTable  = DBDatabaseTableList.GetItem(nI);
		for(nJ = 0; nJ<nTabCliCount; nJ++)
		{
			CDBDatabaseTable* pDBDatabaseTableClient = DBDatabaseTableListClient.GetItem(nJ);
			if(pDBDatabaseTable->m_strTableName == pDBDatabaseTableClient->m_strTableName)
			{
				if(!CompareTableFields(pDBDatabaseTable, pDBDatabaseTableClient, strDatabase))
				{
					return FALSE;
				}
				bFlag = TRUE;
			}
		}
		if(!bFlag)
		{
			CString strtemp = GetFieldsInfoFromReadFile(pDBDatabaseTable);
			if(strtemp.IsEmpty())
			{
				return FALSE;
			}
				
			if(!CreateDataBaseTable(strDatabase, pDBDatabaseTable->m_strTableName, strtemp))
			{
				return FALSE;
			}
				
		}

	}

 	return TRUE;
}


BOOL CDlgPane1Item3::CompareTableFields(CDBDatabaseTable* pDBDatabaseTable, CDBDatabaseTable* pDBDatabaseTableClient, CString strDatabase)
{
	int nTableFields = pDBDatabaseTable->m_listFields.GetCount();
	int nTableFieldsClient = pDBDatabaseTableClient->m_listFields.GetCount();
	int nI = 0, nJ = 0;
	for(; nI<nTableFields; nI++)
	{
		BOOL Flag = FALSE;
		CDBDatabaseFields* pDBDatabaseFields = pDBDatabaseTable->m_listFields.GetItem(nI);
		for(nJ = 0; nJ<nTableFieldsClient; nJ++)
		{
			CDBDatabaseFields* pDBDatabaseFieldsClient = pDBDatabaseTableClient->m_listFields.GetItem(nJ);
			if(pDBDatabaseFields->m_strFieldsName == pDBDatabaseFieldsClient->m_strFieldsName)
			{
				Flag = TRUE;
            break;
			}
		}
		if(!Flag)
		{
			if(!AddFieldsToDatabase(strDatabase, pDBDatabaseTable->m_strTableName, pDBDatabaseFields))
			{
				return FALSE;
			}
		}
	}

	return TRUE; 
}


void CDlgPane1Item3::CreateDatabaseFromFile(CString strDatabase, BOOL &bRet)
{
	int nTableCount = m_DBDatabaseTableList.GetCount();
	int nIndex = 0;
	CString strtemp = _T("");
	for(; nIndex < nTableCount; nIndex++)
	{
		CDBDatabaseTable* pDBDatabaseTable = m_DBDatabaseTableList.GetItem(nIndex);
		strtemp = GetFieldsInfoFromReadFile(pDBDatabaseTable);
		if(strtemp.IsEmpty())
		{
			return;
		}
			
		bRet = CreateDataBaseTable(strDatabase, pDBDatabaseTable->m_strTableName, strtemp);
	}
	if(bRet)
	{
		theApp.OnShowDesktopAlert(_T("创建数据库成功!"),COLOR_TIP_SUC,2,AfxGetMainWnd());
	}
	else
	{
		theApp.OnShowDesktopAlert(_T("创建数据库失败!"),COLOR_TIP_FAIL,2,AfxGetMainWnd());
	}
	 
}

CString CDlgPane1Item3::GetFieldsInfoFromReadFile(CDBDatabaseTable *pDBDatabaseTable)
{
	CString strtemp = _T("");
	int nFieldsCount = pDBDatabaseTable->m_listFields.GetCount();

	int nIndex = 0;
	CString strFieldsLength = _T(""), strFieldsPrimaryKey = _T(""), strFieldsName = _T(""), strFieldsType = _T(""),strFieldsSeed = _T("");
	CString strFieldsDecimal = _T("");
	for(; nIndex<nFieldsCount; nIndex++)
	{
		CDBDatabaseFields* pDBDatabaseFields = pDBDatabaseTable->m_listFields.GetItem(nIndex);
      if (pDBDatabaseFields->m_nFieldsLength<0)//特殊情况max时小于0
      {
         strFieldsLength = _T("max");
      }
      else
      {
         strFieldsLength.Format(_T("%d"), pDBDatabaseFields->m_nFieldsLength);
      }
		
		FilterFieldsLength(pDBDatabaseFields->m_strFieldsType, strFieldsLength);
		if(pDBDatabaseFields->m_bFieldsPrimary == 0)
		{
			strFieldsPrimaryKey = _T("");
		}
		else
		{
			strFieldsPrimaryKey = _T("not null primary key");
		}

		if (pDBDatabaseFields->m_nFieldsSeed != 0)
		{
			strFieldsSeed.Format(_T("IDENTITY(%d,%d)"), pDBDatabaseFields->m_nFieldsSeed, pDBDatabaseFields->m_nFieldsIncrement);
		}
		else
		{
			strFieldsSeed = _T("");
		}
		
		strFieldsName.Format(_T("[%s]"), pDBDatabaseFields->m_strFieldsName);
		strFieldsType.Format(_T("[%s]"), pDBDatabaseFields->m_strFieldsType);
		CString strFieldsTemp = _T("");
		if(strFieldsLength != _T(""))
		{
			if(pDBDatabaseFields->m_nFieldsScale != 0)
			{
				strFieldsDecimal.Format(_T("(%d, %d)"), pDBDatabaseFields->m_nFieldsPrec, pDBDatabaseFields->m_nFieldsScale);
				strFieldsTemp = strFieldsDecimal;
			}
			else
			{
				strFieldsTemp = _T("(") + strFieldsLength + _T(")");
			}
		}
		if(nIndex == nFieldsCount-1)
		{
			strtemp += strFieldsName + _T(" ") + strFieldsType + _T(" ") + strFieldsSeed + _T(" ") + strFieldsTemp + _T(" ") + strFieldsPrimaryKey;
			return strtemp;
		}
		strtemp += strFieldsName + _T(" ") + strFieldsType + _T(" ") + strFieldsSeed + _T(" ") + strFieldsTemp + _T(" ") + strFieldsPrimaryKey + _T(", ");
	}
	return strtemp;
}

BOOL CDlgPane1Item3::CreateDataBaseTable(CString strDatabase, CString strTable, CString strlist)
{
	CString strSQL = _T("");
	strSQL.Format(_T("use [%s] create table [%s] (%s)"), strDatabase, strTable, strlist);
	if(m_pADOConn->ExecuteSQL(strSQL))
	{
		return TRUE;	
	}
	return FALSE;
}

void CDlgPane1Item3::FilterFieldsLength(CString &strFieldsType, CString &strFieldsLength)
{
	if(!(strFieldsType == _T("binary") || strFieldsType == _T("char") || strFieldsType == _T("datetime2") || strFieldsType == _T("datetimeoffset") \
		|| strFieldsType == _T("decimal") || strFieldsType == _T("nchar") || strFieldsType == _T("numeric") || strFieldsType == _T("nvarchar") || strFieldsType == _T("time") \
		|| strFieldsType == _T("varbinary") || strFieldsType == _T("varchar")))
	{
		strFieldsLength = _T("");
	}
}

BOOL CDlgPane1Item3::AddFieldsToDatabase(CString strDatabase, CString strTable, CDBDatabaseFields* pDBDatabaseFields)
{
	CString strSQL = _T("");
	CString strLength = _T(""), strFieldsTemp = _T(""), strFieldsDecimal = _T(""),strFieldsSeed = _T("");
	CString strPrimaryKey = _T("");
   //针对大值数据类型的处理   既然原函数不判断类型 那改的也不判断
   //大值数据类型为
   /*
   Large value data types: varchar(max), and nvarchar(max)
   Large object data types: text, ntext, image, varbinary(max), and xml
   */
   if (pDBDatabaseFields->m_nFieldsLength<0)//特殊情况max时小于0
   {
      strLength = _T("max");
   }
   else
   {
      strLength.Format(_T("%d"), pDBDatabaseFields->m_nFieldsLength);
   }
	//strLength.Format(_T("%d"), pDBDatabaseFields->m_nFieldsLength);
	FilterFieldsLength(pDBDatabaseFields->m_strFieldsType, strLength);
	if(strLength != _T(""))
	{
		if(pDBDatabaseFields->m_nFieldsScale != 0)
		{
			strFieldsDecimal.Format(_T("(%d, %d)"), pDBDatabaseFields->m_nFieldsPrec, pDBDatabaseFields->m_nFieldsScale);
			strFieldsTemp += strFieldsDecimal;
		}
		else
		{
			strFieldsTemp = _T("(") + strLength + _T(")");
		}
	}
	else
	{
		strFieldsTemp = _T("");
	}
	if(pDBDatabaseFields->m_bFieldsPrimary != 0)
	{
		strPrimaryKey = _T("not null primary key");
	}
	else
	{
		strPrimaryKey = _T("null");
	}

	if (pDBDatabaseFields->m_nFieldsIncrement != 0)
	{
		strFieldsSeed.Format(_T("IDENTITY(%d,%d)"), pDBDatabaseFields->m_nFieldsSeed, pDBDatabaseFields->m_nFieldsIncrement);
	}
	else
	{
		strFieldsSeed = _T("");
	}

	CString strFieldsName = _T(""), strFieldsType = _T("");
	strFieldsName.Format(_T("[%s]"), pDBDatabaseFields->m_strFieldsName);
	strFieldsType.Format(_T("[%s]"), pDBDatabaseFields->m_strFieldsType);
	CString strTemp = strFieldsName + _T(" ") + strFieldsType + _T(" ") + strFieldsSeed + _T(" ") + strFieldsTemp + _T(" ") + strPrimaryKey + _T(" ");
	strSQL.Format(_T("use [%s] \
					 alter table [%s] add  %s"), strDatabase, strTable, strTemp);
	if(m_pADOConn->ExecuteSQL(strSQL))
	{
      AfxMessageBox(strSQL,MB_OK);
		return TRUE;
	}
   else
   {
      AfxMessageBox(strSQL);
   }
	return FALSE;
}


BOOL CDlgPane1Item3::OnInitDialog()
{
	CTabDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CString strSavePath = _T(""), strUpdatePath = _T(""), strUpdateFunctionPath = _T("");
	theApp.OnReadIni(_T("UpdateDatabasePath"), _T("SaveDatabase"), strSavePath,INI_SQLSVR);
	SetDlgItemText(IDC_SAVE_DATABASE_EDIT, strSavePath);
	theApp.OnReadIni(_T("UpdateDatabasePath"), _T("UpdateDatabase"), strUpdatePath,INI_SQLSVR);
	SetDlgItemText(IDC_CREATE_DATABASE_EDIT, strUpdatePath);
	theApp.OnReadIni(_T("UpdateDatabasePath"), _T("UpdateFunction"), strUpdateFunctionPath,INI_SQLSVR);
	SetDlgItemText(IDC_UPDATE_FUNCTION_EDIT, strUpdateFunctionPath);

	CString strBeta = _T("");
	theApp.OnReadIni(_T("ConfigureInfo"), _T("Beta"), strBeta,INI_SQLSVR);
	if (0 == strBeta.CompareNoCase(_T("TRUE")))
	{
		GetDlgItem(IDC_SAVE_DATABASE_EDIT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_SAVE_DATABASE_BUTTON)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTN_SAVE)->ShowWindow(SW_SHOW);

      GetDlgItem(IDC_SAVE_DATABASE_TRIGGER)->ShowWindow(SW_SHOW);
      GetDlgItem(IDC_BTN_DIR_TRIGGER)->ShowWindow(SW_SHOW);
      GetDlgItem(IDC_BTN_SAVE_TRIGGER)->ShowWindow(SW_SHOW);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlgPane1Item3::OnBnClickedUpdateFunctionButton()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strDefPath = _T("");
	GetDlgItemText(IDC_UPDATE_FUNCTION_EDIT,strDefPath);

	CString strFilter = _T("文件(*.sql)|*.sql||");
	CString strNewPath =_T("");
	COleDateTime CurrentTime=COleDateTime::GetCurrentTime();
	CString strFile = _T("");

	if (m_CDirectroy.OpenDirFile(strNewPath,strDefPath,strFile,strFilter,TRUE))
	{
		SetDlgItemText(IDC_UPDATE_FUNCTION_EDIT, strNewPath);
		theApp.OnWriteIni(_T("UpdateDatabasePath"), _T("UpdateFunction"), strNewPath,INI_SQLSVR);
	}
}


void CDlgPane1Item3::OnBnClickedBtnUpdateFunction()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strFilePath = _T("");
	GetDlgItemText(IDC_UPDATE_FUNCTION_EDIT,strFilePath);
	if(strFilePath.IsEmpty() || (!PathFileExists(strFilePath)))
	{
		theApp.OnShowDesktopAlert(_T("请选择有效路径!"),COLOR_TIP_WARN,2,AfxGetMainWnd());
	}
	else
	{
      if (!theApp.GetStateConnectDB())
      {
         theApp.OnShowDesktopAlert(_T("无法连接到数据库"),COLOR_TIP_WARN,2,AfxGetMainWnd());
         return;
      }

      //
      //读取数据库脚本，进行数据库名比对
      CString strDataName,strTip;
      BOOL bUpdate = TRUE;
      strDataName = CompareDataName(strFilePath);
      if (strDataName.IsEmpty())
      {
         bUpdate = FALSE;
         CString strDatabase = _T("");
         theApp.OnReadIni(_T("ConfigureInfo"), _T("DatabaseName"), strDataName,INI_SQLSVR);//获取数据库名称
      }

      strTip.Format(_T("确定【更新%s函数】文件吗？"),strDataName);
		if(IDCANCEL == MessageBox(strTip,_T("提示"),MB_OKCANCEL|MB_ICONQUESTION))
		{
			return;
		}

      if (bUpdate)
      {
         theApp.OnShowDesktopAlert(_T("更新函数失败"),COLOR_TIP_WARN,2);
         return;
      }

		CString strDatabase = _T(""),strFailedSql = _T("");
		theApp.OnReadIni(_T("ConfigureInfo"), _T("DatabaseName"), strDatabase,INI_SQLSVR);
		theApp.ShowLoading();
		BOOL bRet = TRUE;
		bRet = m_FileTxt.ReadFile(strFilePath);
		if (m_FileTxt.ReadFile(strFilePath))
		{
			CString strFunction = _T("");
			auto it = m_FileTxt.m_vecCString.begin();
			while(it != m_FileTxt.m_vecCString.end())
			{
            //修复更新失败，提示上下文被修改为xxx错误 lida 2019/01/14
            if(*(it) == _T("GO"))
            {
               bRet = m_pADOConn->ExecuteSQL(strFunction);
               if (FALSE == bRet)
               {
                  strFailedSql +=strFunction + _T("\r\n");
               }
               strFunction = _T("");
            }
            else
				   strFunction += *(it) +_T("\r\n");
				it++;
			}
			//strFunction.Replace(_T("GO"), _T(""));
			//bRet = m_pADOConn->ExecuteSQL(strFunction);
			if(strFailedSql.IsEmpty())
			{
				theApp.OnShowDesktopAlert(_T("升级函数成功!"),COLOR_TIP_SUC,2,AfxGetMainWnd());
			}
			else
			{
				theApp.OnShowDesktopAlert(_T("升级函数失败!\r\n")+strFailedSql,COLOR_TIP_FAIL,2,AfxGetMainWnd());
			}		
		}
		else
		{
			theApp.OnShowDesktopAlert(_T("升级函数失败!"),COLOR_TIP_FAIL,2,AfxGetMainWnd());
		}
		theApp.CloseLoading();
	}
}

CString CDlgPane1Item3::CompareDataName(CString strPath)
{
   //读取数据库脚本，进行数据库名比对
   CStdioFile file;
   CString str;
   if(file.Open(strPath,CFile::modeRead))
   {
      file.ReadString(str);
      str.Trim();

      int pos =  str.ReverseFind('[');
      CString text =str.Right(str.GetLength()-pos);
      CString strDatabase = _T("");
      theApp.OnReadIni(_T("ConfigureInfo"), _T("DatabaseName"), strDatabase,INI_SQLSVR);//获取数据库名称
      strDatabase= _T("[")+strDatabase+_T("]");
      if (strDatabase != text)
      {
         return text;
      }
      else
      {
         text = _T("");
         return text;
      }

   }
   else
   {
       return FALSE;
   }
}

void CDlgPane1Item3::OnBnClickedBtnSaveTrigger()
{
   CString strFilePath = _T("");
   GetDlgItemText(IDC_SAVE_DATABASE_TRIGGER,strFilePath);
   strFilePath.Trim();
   int nPos = strFilePath.ReverseFind('\\');
   CString strPath = _T("");
   if (nPos>-1)
   {
      strPath = strFilePath.Left(nPos);
   }

   if (strFilePath.IsEmpty()||(!PathFileExists(strPath)))
   {
      theApp.OnShowDesktopAlert(_T("请选择保存路径!"),COLOR_TIP_WARN,2,AfxGetMainWnd());
   }
   else
   {
      if (!theApp.GetStateConnectDB())
      {
         theApp.OnShowDesktopAlert(_T("无法连接到数据库"),COLOR_TIP_WARN,2,AfxGetMainWnd());
         return;
      }

      if(IDOK == MessageBox(_T("确定【保存触发器脚本】文件吗？"),_T("提示"),MB_OKCANCEL|MB_ICONQUESTION))
      {
         CString strDatabase = _T("");
         theApp.OnReadIni(_T("ConfigureInfo"), _T("DatabaseName"), strDatabase,INI_SQLSVR);//获取数据库名称

         SaveTriggerToFile(strFilePath);
      }	
   }
}

void CDlgPane1Item3::OnBnClickedBtnDirTrigger()
{
   CString strDefPath = _T("");
   GetDlgItemText(IDC_SAVE_DATABASE_EDIT,strDefPath);

   CString strFilter = _T("文件(*.sql)|*.sql||");
   CString strNewPath =_T("");
   COleDateTime CurrentTime=COleDateTime::GetCurrentTime();
   CString strFile = _T("");
   strFile.Format(_T("Trigger_%d_%d_%d_%d时%d分.sql") ,CurrentTime.GetYear(), CurrentTime.GetMonth(),CurrentTime.GetDay(), CurrentTime.GetHour(), CurrentTime.GetMinute());  

   if (m_CDirectroy.OpenDirFile(strNewPath,strDefPath,strFile,strFilter,FALSE))
   {
      SetDlgItemText(IDC_SAVE_DATABASE_TRIGGER, strNewPath);
      //theApp.OnWriteIni(_T("UpdateDatabasePath"), _T("SaveDatabase"), strNewPath,INI_SQLSVR);
   }
}


void CDlgPane1Item3::OnBnClickedUpdateTriggerButton()
{
   CString strDefPath = _T("");
   GetDlgItemText(IDC_UPDATE_TRIGGER_EDIT,strDefPath);

   CString strFilter = _T("文件(*.sql)|*.sql||");
   CString strNewPath =_T("");
   COleDateTime CurrentTime=COleDateTime::GetCurrentTime();
   CString strFile = _T("");

   if (m_CDirectroy.OpenDirFile(strNewPath,strDefPath,strFile,strFilter,TRUE))
   {
      SetDlgItemText(IDC_UPDATE_TRIGGER_EDIT, strNewPath);
      //theApp.OnWriteIni(_T("UpdateDatabasePath"), _T("UpdateFunction"), strNewPath,INI_SQLSVR);
   }
}


void CDlgPane1Item3::OnBnClickedBtnUpdateTrigger()
{
   CString strFilePath = _T("");
   GetDlgItemText(IDC_UPDATE_TRIGGER_EDIT,strFilePath);
   if(strFilePath.IsEmpty() || (!PathFileExists(strFilePath)))
   {
      theApp.OnShowDesktopAlert(_T("请选择有效路径!"),COLOR_TIP_WARN,2,AfxGetMainWnd());
   }
   else
   {
      if (!theApp.GetStateConnectDB())
      {
         theApp.OnShowDesktopAlert(_T("无法连接到数据库"),COLOR_TIP_WARN,2,AfxGetMainWnd());
         return;
      }
      CString strTip;
      strTip.Format(_T("确定【更新触发器脚本】文件吗？"));
      if(IDCANCEL == MessageBox(strTip,_T("提示"),MB_OKCANCEL|MB_ICONQUESTION))
      {
         return;
      }

      if(strFilePath.IsEmpty())
      {
         OutputDebugString(_T("文件名为空，无法进行读取!"));
         return ;
      }

      //设置中文模式，不然无法写入中文
      TCHAR* old_locale = _tcsdup( _tsetlocale(LC_CTYPE,NULL) );  
      _tsetlocale( LC_CTYPE, _T("chs")); 

      vector<CString> vecCString;
      CStdioFile myFile;
      if(myFile.Open(strFilePath, CFile::modeRead))
      {
         char* old_locale = _strdup( setlocale(LC_CTYPE,NULL) );
         setlocale( LC_CTYPE, "chs" );
         CString strText;
         while(myFile.ReadString(strText))
         {
            vecCString.push_back(strText);
         }
         setlocale( LC_CTYPE, old_locale );
         free( old_locale );
         myFile.Close();
      }
      //操作完文件后要释放  
      _tsetlocale( LC_CTYPE, old_locale );  
      free( old_locale );

      if (!theApp.GetStateConnectDB())
      {
         theApp.OnShowDesktopAlert(_T("无法连接到数据库"),COLOR_TIP_WARN,2,AfxGetMainWnd());
         return;
      }
      m_pADOConn->BeginTrans();
      CString strsql;
      for (int i=0;i<(int)vecCString.size(); ++i)
      {
         if (vecCString[i].Find(_T("GO")) <0)
         {
            strsql += vecCString[i] + _T(" ");
         }
         else
         {
            if (!strsql.IsEmpty())
            {
               if (!m_pADOConn->ExecuteSQL(strsql))
               {
                  theApp.OnShowDesktopAlert(_T("更新失败")+strsql,COLOR_TIP_SUC);
                  m_pADOConn->RollbackTrans();
                  return;
               }
            }            
            strsql = _T("");
         }
      }
      m_pADOConn->CommitTrans();
      theApp.OnShowDesktopAlert(_T("更新成功！"),COLOR_TIP_SUC);
   }
}
