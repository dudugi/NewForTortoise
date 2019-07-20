#include "StdAfx.h"
#include <math.h>
#include "ADOConn.h"


CADOConn::CADOConn(void)
{
	m_bInitConnect = FALSE;
	m_pConnection = NULL;
	m_pRecordset = NULL;

	m_strBatchSql.Empty();
	m_listBatchSql.RemoveAll();
	m_nBatchLen = 1024;
	m_hWndExceptionMsg = NULL;

   m_pCommand = NULL;
}


CADOConn::~CADOConn(void)
{
	if (m_bInitConnect)
	{
		ExitConnect();//析构时 断开数据库连接
	}
}

BOOL CADOConn::InitConnect()
{
	BOOL bRet = FALSE;

	CloseConnect();//2017/04/28 zhangt

	//初始化OLE/COM库环境
	::CoInitialize(NULL);
	m_pConnection = NULL;
	m_pRecordset = NULL;

	HRESULT hr = m_pConnection.CreateInstance("ADODB.Connection");

	//设置连接字符串，必须是BSTR型或者_bstr_t类型
	_bstr_t vConnect;

	//通过外部配置文件获取连接数据库字符串 
#ifdef _DEBUG
	if (m_strConnectSql.IsEmpty())
	{
		vConnect = _bstr_t("Driver={SQL Server};Server=192.168.3.39,1433;Database=qili;UID=sa;PWD=wzl123456");
	}
	else
	{
		vConnect = _bstr_t(m_strConnectSql);
	}
#else
	vConnect = _bstr_t(m_strConnectSql);
#endif // _DEBUG
	
	try
	{
		if (SUCCEEDED(hr))//创建成功
		{
			m_pConnection->ConnectionTimeout = 5;//连接超时时间
			hr = m_pConnection->Open(vConnect,_bstr_t(""),_bstr_t(""),adModeUnknown);
			if (SUCCEEDED(hr))
			{
				m_bInitConnect = TRUE;
				bRet = TRUE;
			}
		}
	}
	catch(_com_error& e)
	{
		CString strError = e.ErrorMessage();
		CString strDescripion = e.Description();//2017-08-03 wangzl 数据库错误信息描述

      ThrowExceptionMsg(strError,strDescripion);
	}
   catch(...)
   {
      //未知信息
   }

	ASSERT(m_pConnection != NULL);

	if (!bRet)
	{
		::CoUninitialize();//释放环境
	}
	return bRet;
}

void CADOConn::ExitConnect()
{
	try
	{
		CloseConnect();

		::CoUninitialize();//释放环境
	}
	catch(_com_error& e)
	{
		CString strError = e.ErrorMessage();
		CString strDescripion = e.Description();//2017-08-03 wangzl 数据库错误信息描述
		
      ThrowExceptionMsg(strError,strDescripion);
	}
   catch(...)
   {
      //未知信息
   }
}

void CADOConn::CloseConnect()
{
	if(m_pRecordset != NULL)
		m_pRecordset->Close();
	if (m_pConnection != NULL)
		m_pConnection->Close();
}

BOOL CADOConn::MoveFirst()
{
	if(m_pRecordset==NULL) 
		return FALSE;
	else
	{
		m_pRecordset->MoveFirst();
		return TRUE;
	}
}

BOOL CADOConn::MoveNext()
{
	if(m_pRecordset==NULL) 
		return FALSE;
	else
	{
		try
		{
			if (!m_pRecordset->adoEOF)//记录集没指向结束，则下移
			{
				m_pRecordset->MoveNext();
				return TRUE;
			}
			else
			{
				return FALSE;	
			}
		}
		catch (_com_error& e)
		{
         // 当游标移动时如果不能移动到下一个但是又不是尾部导致外部处理时死循环 处理 2018-5-17 wangzl
         if (m_pRecordset)
         {
            m_pRecordset->Close();
            m_pRecordset = NULL;
         }

			CString strDes = e.Description();
         ThrowExceptionMsg(_T(""),strDes);
			
			return FALSE;
		}
      catch(...)
      {
         return FALSE;
      }
	}
}

BOOL CADOConn::adoEOF()
{
	if(m_pRecordset==NULL) 
	{
		//::MessageBox(NULL,_T("抱歉，数据库没有数据！"),_T("温馨提示"),MB_OK|MB_ICONERROR);	
		return TRUE;	
	}
	else
	{
		try
		{
			if(m_pRecordset->adoEOF)
				return TRUE;
			else
				return FALSE;
		}
		catch (_com_error& e)
		{
			CString strDes = e.Description();
         ThrowExceptionMsg(_T(""),strDes);

			return FALSE;
		}
      catch(...)
      {
         return FALSE;
      }
	}
}


BOOL CADOConn::ExecuteSQL(CString strSQL)
{
	try
	{
		if(m_pConnection == NULL)
		{
			//是否已经连接数据库
			if(!InitConnect())//如果Connection对象为空，则重新连接数据库
				return FALSE;
		}
		else
		{
			if(adStateClosed == m_pConnection->State)
			{
				m_pConnection->Close();
				m_pConnection = NULL;

				return ExecuteSQL(strSQL);
			}
		}

		strSQL.Trim();
		_RecordsetPtr ptSet = m_pConnection->Execute(_bstr_t(strSQL),NULL,adCmdText);

		return TRUE;
	}
	catch(_com_error& e)
	{
		//CString strError = e.ErrorMessage();
		CString strDes = e.Description();//2017-08-03 wangzl 数据库错误信息描述
		
      ThrowExceptionMsg(_T(""),strDes);
		
		return FALSE;
	}
   catch(...)
   {
      return FALSE;
   }
}

BOOL CADOConn::ExecuteSQLWithTrans(const CString &strSQL)
{
   CString strSQLTrans;
   strSQLTrans.Format(_T("SET NOCOUNT ON \
BEGIN TRY \
BEGIN TRAN \
%s \
COMMIT TRAN \
END TRY \
BEGIN CATCH \
ROLLBACK TRAN \
select 0 as iSuc \
return \
END CATCH \
select 1 as iSuc"), strSQL);
   _RecordsetPtr &RecordsetPtr = GetRecordSet(strSQLTrans);
   if (!RecordsetPtr)
      return FALSE;
   if (adoEOF())
      return FALSE;
   int nSuc = GetValueInt(_T("iSuc"));
   if (0 == nSuc)
      return FALSE;
   return TRUE;
}

_RecordsetPtr& CADOConn::GetRecordSet(CString strSQL)
{
	try
	{
		if(m_pConnection == NULL)
		{
			if(!InitConnect())//如果Connection对象为空，则重新连接数据库
			{
				return m_pRecordset;//m_pRecordset=NULL
			}
		}

		//2017/04/28 zhangt 判断
		if (m_pRecordset)
		{
			m_pRecordset->Close();
			m_pRecordset = NULL;
		}

		strSQL.Trim();

		HRESULT hr = m_pRecordset.CreateInstance(__uuidof(Recordset));//创建记录集对象
		if (SUCCEEDED(hr))
		{
			m_pRecordset->CursorLocation = adUseClient;//设置游标类型：记录集存在客户端的内存中
			hr = m_pRecordset->Open(_bstr_t(strSQL),m_pConnection.GetInterfacePtr(),\
				adOpenStatic/*adOpenDynamic*/,adLockBatchOptimistic,adCmdText);//执行查询，取得表中的记录
			if (SUCCEEDED(hr))
			{
				
			}
			else
			{
				TRACE(_T("Ado Failed\n"));
				m_pRecordset->Close();
				m_pRecordset = NULL;
			}
		}
		
	}
	catch(_com_error& e)//捕捉异常
	{
		CString strError = e.ErrorMessage();
		CString strDescript = e.Description();

		ThrowExceptionMsg(strError,strDescript);

		//m_pRecordset->Close();
		m_pRecordset = NULL;
		if (m_pConnection)
		{
         if (m_pConnection->GetState() == adStateOpen)
         {
            m_pConnection->Close();
         }
         m_pConnection.Release();
			m_pConnection = NULL;
		}
	}
   catch(...)
   {
      //未知错误
      m_pRecordset = NULL;
      if (m_pConnection)
      {
         if (m_pConnection->GetState() == adStateOpen)
         {
            m_pConnection->Close();
         }
         m_pConnection.Release();
         m_pConnection = NULL;
      }
   }

	return m_pRecordset;//返回记录集
}

int CADOConn::GetFeildsCount()
{
	ASSERT(m_pRecordset != NULL);

	if (NULL == m_pRecordset)
	{
		return 0;
	}
	else
	{
		int nRet = m_pRecordset->Fields->Count;
		return nRet;
	}
}

long CADOConn::GetRecordCount()
{
	ASSERT(m_pRecordset != NULL);

	if (NULL == m_pRecordset)
	{
		return 0;
	}
	else
	{
		long lRet;
		m_pRecordset->get_RecordCount(&lRet);
		return lRet;
	}
}

CString CADOConn::GetFieldsName(int index)
{
	ASSERT(m_pRecordset != NULL);

	_variant_t vIndex;
	vIndex.vt = VT_I2;	
	CString strTitle = _T("");
	vIndex.iVal = index;
	strTitle = (LPCTSTR)m_pRecordset->Fields->GetItem(vIndex)->GetName();

	return strTitle;
}

byte CADOConn::GetValueByte(int index)
{
	ASSERT(m_pRecordset != NULL);

	_variant_t vValue;//var型返回值
	_variant_t vIndex;//索引
	byte bValue = 0;//数值返回值
	vIndex.vt = VT_I2;
	vIndex.iVal = index;
//	vValue = m_pRecordset->Fields->GetItem(vIndex)->Value;
   TryGetValueByIndex(vValue,vIndex);

	switch(vValue.vt)
	{
	case VT_NULL:
	case VT_ERROR:
	case VT_EMPTY:
		break;
	case VT_BSTR:
		{
			CString strValue = _T("");		
			strValue = (LPCSTR)_bstr_t(vValue);
			bValue = _ttoi(strValue);
		}
		break;
	default:
		bValue = vValue.bVal;
	}

	return bValue;
}

int CADOConn::GetValueInt(int index)
{
	ASSERT(m_pRecordset != NULL);

	_variant_t vValue;//var型返回值
	_variant_t vIndex;//索引
	int iValue = 0;//数值返回值
	vIndex.vt = VT_I2;
	vIndex.iVal = index;
//	vValue = m_pRecordset->Fields->GetItem(vIndex)->Value;//获取索引字段的值
   TryGetValueByIndex(vValue,vIndex);

	switch(vValue.vt)
	{
	case VT_NULL://为空值
	case VT_ERROR://错误
	case VT_EMPTY://不存在
		break;
	case VT_BSTR:
		{
			CString strValue = _T("");		
			strValue = (LPCSTR)_bstr_t(vValue);
			iValue = _ttoi(strValue);
		}
		break;
	default:
		iValue = vValue.iVal;//获取值
	}

	return iValue;//返回整数值
}

int CADOConn::GetValueInt(CString strField)
{
	ASSERT(m_pRecordset != NULL);

	_variant_t vValue;//var型返回值
   //vValue = m_pRecordset->GetCollect((LPCTSTR)strField);
   TryGetCollect(vValue,(LPCTSTR)strField);

	int iValue = 0;
	switch(vValue.vt)
	{
	case VT_NULL:
	case VT_ERROR:
	case VT_EMPTY:
		break;
	case VT_BSTR:
		{
			CString strValue = _T("");		
			strValue = (LPCSTR)_bstr_t(vValue);
			iValue = _ttoi(strValue);
		}
		break;
	default:
		iValue = (int)vValue;
		break;
	}

	return iValue;//返回整数值
}

__int64 CADOConn::GetValueInt64(int index)
{
	ASSERT(m_pRecordset != NULL);

	_variant_t vValue;//var型返回值
	_variant_t vIndex;//索引
	__int64 llValue = 0;//数值返回值
	vIndex.vt = VT_I2;
	//vIndex.vt = VT_I8;
	vIndex.iVal = index;
	//vValue = m_pRecordset->Fields->GetItem(vIndex)->Value;//获取索引字段的值
   TryGetValueByIndex(vValue,vIndex);
	switch(vValue.vt)
	{
	case VT_NULL://为空值
	case VT_ERROR://错误
	case VT_EMPTY://不存在
		break;
	case VT_BSTR:
		{
			CString strValue = _T("");		
			strValue = (LPCSTR)_bstr_t(vValue);
			llValue = _ttoi64(strValue);
		}
		break;
	default:
		llValue = vValue.llVal;//获取值
	}

	return llValue;//返回64位整数值
}

__int64 CADOConn::GetValueInt64(CString strField)
{
	ASSERT(m_pRecordset != NULL);

	_variant_t vValue;//var型返回值
	//vValue = m_pRecordset->GetCollect((LPCTSTR)strField);
   TryGetCollect(vValue,(LPCTSTR)strField);

	__int64 llValue = 0;//数值返回值
	switch(vValue.vt)
	{
	case VT_NULL:
	case VT_ERROR:
	case VT_EMPTY:
		break;
	case VT_BSTR:
		{
			CString strValue = _T("");		
			strValue = (LPCSTR)_bstr_t(vValue);
			llValue = _ttoi64(strValue);
		}
		break;
	default:
		llValue = (__int64)vValue;//获取值
	}

	return llValue;//返回64位整数值
}

double CADOConn::GetValueDouble(int index)
{
	ASSERT(m_pRecordset != NULL);

	_variant_t vValue;//var型返回值
	_variant_t vIndex;//索引
	double dValue = 0;//数值返回值
	vIndex.vt = VT_I2;
	vIndex.iVal = index;
	//vValue = m_pRecordset->Fields->GetItem(vIndex)->Value;
   TryGetValueByIndex(vValue,vIndex);
	switch(vValue.vt)
	{
	case VT_NULL:
	case VT_ERROR:
	case VT_EMPTY:
		break;
	case VT_BSTR:
		{
			CString strValue = _T("");		
			strValue = (LPCSTR)_bstr_t(vValue);
			dValue = _ttof(strValue);
		}
		break;
	default:
		dValue = vValue.dblVal;
	}

	return dValue;
}

double CADOConn::GetValueDouble(CString strField)
{
	ASSERT(m_pRecordset != NULL);

	_variant_t vValue;//var型返回值
	//vValue = m_pRecordset->GetCollect((LPCTSTR)strField);
   TryGetCollect(vValue,(LPCTSTR)strField);

	double dValue = 0;//数值返回值
	switch(vValue.vt)
	{
	case VT_NULL:
	case VT_ERROR:
	case VT_EMPTY:
		break;
	case VT_BSTR:
		{
			CString strValue = _T("");		
			strValue = (LPCSTR)_bstr_t(vValue);
			dValue = _ttof(strValue);
		}
		break;
	default:
		dValue = (double)vValue;
	}

	return dValue;
}


CString CADOConn::GetValueDoubleStr(CString strField,int dotNum)
{
   ASSERT(m_pRecordset != NULL);

   _variant_t vValue;//var型返回值
   //vValue = m_pRecordset->GetCollect((LPCTSTR)strField);
   TryGetCollect(vValue,(LPCTSTR)strField);

   double dValue = 0;//数值返回值
   switch(vValue.vt)
   {
   case VT_NULL:
   case VT_ERROR:
   case VT_EMPTY:
      break;
   case VT_BSTR:
	   {
		   CString strValue = _T("");		
		   strValue = (LPCSTR)_bstr_t(vValue);
		   dValue = _ttof(strValue);
	   }
	   break;
   default:
      dValue = (double)vValue;
   }

   CString strValue,strType;//strValue:字符串返回值 strType:格式化字符串
   strType.Format(_T(".%d"),dotNum);
   strType = _T("%")+strType+_T("f");
   strValue.Format(strType,dValue);

   return strValue;
}

float CADOConn::GetValueFloat(int index)
{
	ASSERT(m_pRecordset != NULL);

	_variant_t vValue;//var型返回值
	_variant_t vIndex;//索引
	float fValue = 0;//数值返回值
	vIndex.vt = VT_I2;
	vIndex.iVal = index;
	//vValue = m_pRecordset->Fields->GetItem(vIndex)->Value;
   TryGetValueByIndex(vValue,vIndex);
	switch(vValue.vt)
	{
	case VT_NULL:
	case VT_ERROR:
	case VT_EMPTY:
		break;
	case VT_BSTR:
		{
			CString strValue = _T("");		
			strValue = (LPCSTR)_bstr_t(vValue);
			fValue = _ttof(strValue);
		}
		break;
	default:
		fValue = vValue.fltVal;
	}

	return fValue;
}

float CADOConn::GetValueFloat(CString strField)
{
	ASSERT(m_pRecordset != NULL);

	_variant_t vValue;//var型返回值
	//vValue = m_pRecordset->GetCollect((LPCTSTR)strField);
   TryGetCollect(vValue,(LPCTSTR)strField);

	float fValue = 0;//数值返回值
	switch(vValue.vt)
	{
	case VT_NULL:
	case VT_ERROR:
	case VT_EMPTY:
		break;
	case VT_BSTR:
		{
			CString strValue = _T("");		
			strValue = (LPCSTR)_bstr_t(vValue);
			fValue = _ttof(strValue);
		}
		break;
	default:
		{
			fValue = (float)vValue;			
		}	
	}

	return fValue;
}

long CADOConn::GetValueLong(int index)
{
	ASSERT(m_pRecordset != NULL);

	_variant_t vValue;//var型返回值
	_variant_t vIndex;//索引
	long lValue = 0;//数值返回值
	vIndex.vt = VT_I2;
	vIndex.iVal = index;
	//vValue = m_pRecordset->Fields->GetItem(vIndex)->Value;
   TryGetValueByIndex(vValue,vIndex);
	switch(vValue.vt)
	{
	case VT_NULL:
	case VT_ERROR:
	case VT_EMPTY:
		break;
	case VT_BSTR:
		{
			CString strValue = _T("");		
			strValue = (LPCSTR)_bstr_t(vValue);
			lValue = _ttol(strValue);
		}
		break;
	default:
		lValue = vValue.lVal;
	}

	return lValue;
}

long CADOConn::GetValueLong(CString strField)
{
	ASSERT(m_pRecordset != NULL);

	_variant_t vValue;//var型返回值
	//vValue = m_pRecordset->GetCollect((LPCTSTR)strField);
   TryGetCollect(vValue,(LPCTSTR)strField);

	long lValue = 0;//数值返回值
	switch(vValue.vt)
	{
	case VT_NULL:
	case VT_ERROR:
	case VT_EMPTY:
		break;
	case VT_BSTR:
		{
			CString strValue = _T("");		
			strValue = (LPCSTR)_bstr_t(vValue);
			lValue = _ttol(strValue);
		}
		break;
	default:
		lValue = (long)vValue;
	}

	return lValue;
}

COleDateTime CADOConn::Var2OleDateTime(_variant_t vDate)
{
	COleDateTime oleRet = COleDateTime::GetCurrentTime();

	switch(vDate.vt)
	{
	case VT_NULL:
	case VT_ERROR:
	case VT_EMPTY:
		break;
	default:
		oleRet = COleDateTime(vDate);
	}

	return oleRet;
}

void CADOConn::TryGetValueByIndex(_variant_t & varValue,_variant_t & varIndex)
{
   try
   {
      varValue = m_pRecordset->Fields->GetItem(varIndex)->Value;//获取索引字段的值
   }
   catch(_com_error& e)//捕捉异常
   {
      CString strError = e.ErrorMessage();
      CString strDescript = e.Description();
      ThrowExceptionMsg(strError,strDescript);
   }
   catch(...)
   {

   }
}

void CADOConn::TryGetCollect(_variant_t & varValue,LPCTSTR lpszField)
{
   try
   {
      varValue = m_pRecordset->GetCollect(lpszField);
   }
   catch(_com_error& e)//捕捉异常
   {
      CString strError = e.ErrorMessage();
      CString strDescript = e.Description();
      ThrowExceptionMsg(strError,strDescript);
   }
   catch(...)
   {

   }
}

COleDateTime CADOConn::Str2OleDateTime(CString strDate)
{
	COleDateTime oleRet = COleDateTime::GetCurrentTime();
	strDate.Trim();
	if (!strDate.IsEmpty())
	{
		CString strYear,strMonth,strDay,strHour,strMin,strSec;
		strYear = strDate.Mid(0,4);		//截取 年
		strMonth = strDate.Mid(5,2);	//截取 月
		strDay = strDate.Mid(8,2);		//截取 日
		if(strDate.GetLength()>10)
		{
			strHour = strDate.Mid(11,2);//截取 时
			strMin = strDate.Mid(14,2);	//截取 分
			strSec = strDate.Mid(17,2);	//截取 秒
		}
		else
		{
			strHour = _T("0");
			strMin = _T("0");
			strSec = _T("0");
		}

		COleDateTime TValue(_ttoi(strYear),_ttoi(strMonth),_ttoi(strDay),_ttoi(strHour),_ttoi(strMin),_ttoi(strSec));
		oleRet = TValue;
	}


	return oleRet;
}

COleDateTime CADOConn::GetValueDate(CString strField)
{
	ASSERT(m_pRecordset != NULL);

	_variant_t vValue;//var型返回值
	_variant_t vIndex;//索引

	//vValue = m_pRecordset->GetCollect((LPCTSTR)strField);
   TryGetCollect(vValue,(LPCTSTR)strField);

	COleDateTime TValue = COleDateTime::GetCurrentTime();
	switch(vValue.vt)
	{
	case VT_NULL:
	case VT_ERROR:
	case VT_EMPTY:
		break;
// 	case VT_BSTR:
// 		{
// 			CString strDate = _T("");
// 			strDate = (LPCSTR)_bstr_t(vValue);
// 			TValue = Str2OleDateTime(strDate);
// 		}
// 		break;
	default:
		TValue = COleDateTime(vValue);
		break;
	}

	return TValue;
}

COleDateTime CADOConn::GetValueDate(int index)
{
	ASSERT(m_pRecordset != NULL);

	_variant_t vValue;//var型返回值
	_variant_t vIndex;//索引
	
	COleDateTime TValue = COleDateTime::GetCurrentTime();

	vIndex.vt = VT_I2;
	vIndex.iVal = index;
	//vValue = m_pRecordset->Fields->GetItem(vIndex)->Value;
   TryGetValueByIndex(vValue,vIndex);
	switch(vValue.vt)
	{
	case VT_NULL:
	case VT_ERROR:
	case VT_EMPTY:
		break;
// 	case VT_BSTR:
// 		{
// 			CString strDate = _T("");
// 			strDate = (LPCSTR)_bstr_t(vValue);
// 			TValue = Str2OleDateTime(strDate);
// 		}
// 		break;
	default:
		TValue = COleDateTime(vValue);
	}

	return TValue;
}

CString CADOConn::GetValueString(int index,int strSum)
{
	ASSERT(m_pRecordset != NULL);

	_variant_t vValue;//var型返回值
	_variant_t vIndex;//索引
	CString strValue,strType,str = _T("");//strValue:初始返回值 strType:格式化字符串 str:最终返回值
	vIndex.vt = VT_I2;
	vIndex.iVal = index;
	//vValue = m_pRecordset->Fields->GetItem(vIndex)->Value;
   TryGetValueByIndex(vValue,vIndex);

	switch(vValue.vt)
	{
	case VT_NULL:
	case VT_ERROR:
	case VT_EMPTY:
		break;
	case VT_DATE:
		str = COleDateTime(vValue).Format(_T("%Y-%m-%d %H:%M:%S"));
		break;
	case VT_BOOL:
		{
			//布尔值 真返回字符串1 假返回字符串0
			str = _T("0");
			if (vValue.boolVal)
			{
				str = _T("1");
			}
		}
		break;
	default:
		str = (LPCSTR)_bstr_t(vValue);
	}

	strType.Format(_T("%d"),strSum);
	strType = _T("%")+strType+_T("s");
	strValue.Format(strType,str);

	return strValue;
}

CString CADOConn::GetValueString(CString strField,int strSum)
{
	ASSERT(m_pRecordset != NULL);

	_variant_t vValue;//var型返回值
	CString strValue,strType,str = _T("");//strValue:初始返回值 strType:格式化字符串 str:最终返回值
	//vValue = m_pRecordset->GetCollect((LPCTSTR)strField);
   TryGetCollect(vValue,(LPCTSTR)strField);

	switch(vValue.vt)
	{
	case VT_NULL:
	case VT_ERROR:
	case VT_EMPTY:
		break;
	case VT_DATE:
		str = COleDateTime(vValue).Format(_T("%Y-%m-%d %H:%M:%S"));
		break;
	case VT_BOOL:
		{
			//布尔值 真返回字符串1 假返回字符串0
			str = _T("0");
			if (vValue.boolVal)
			{
				str = _T("1");
			}
		}
		break;
	case VT_DECIMAL:
      {
         //str.Format(_T("%g"),(double)vValue);

         //解决bigint 转 cstring 时数据错误 by lida 2018/04/27
         double val = vValue.decVal.Lo64;
         val *= (vValue.decVal.sign == 128)? -1 : 1;
         val /= pow(10.0, vValue.decVal.scale); 
         CString strFormat;
         strFormat.Format(_T("%d"),vValue.decVal.scale);
         strFormat = _T("%.") + strFormat+ _T("f");
         str.Format(strFormat, val);
      }
		break;
	default:
		str = (LPCSTR)_bstr_t(vValue);
	}

	strType.Format(_T("%d"),strSum);
	strType = _T("%")+strType+_T("s");
	strValue.Format(strType,str);

	return strValue;
}

CString CADOConn::GetValueByteStr(int index,int strSum)
{
	ASSERT(m_pRecordset != NULL);

	_variant_t vValue;//var型返回值
	_variant_t vIndex;//索引
	byte bValue = 0;//数值返回值
	CString strValue,strType;//strValue:字符串返回值 strType:格式化字符串
	vIndex.vt = VT_I2;
	vIndex.iVal = index;
	//vValue = m_pRecordset->Fields->GetItem(vIndex)->Value;
   TryGetValueByIndex(vValue,vIndex);
	switch(vValue.vt)
	{
	case VT_NULL:
	case VT_ERROR:
	case VT_EMPTY:
		break;
	default:
		bValue = vValue.bVal;
	}

	strType.Format(_T("%d"),strSum);
	strType = _T("%")+strType+_T("d");
	strValue.Format(strType,bValue);

	return strValue;
}

CString CADOConn::GetValueIntStr(int index,int strSum)
{
	ASSERT(m_pRecordset != NULL);

	_variant_t vValue;//var型返回值
	_variant_t vIndex;//索引
	int iValue = 0;//数值返回值
	CString strValue,strType;//strValue:字符串返回值 strType:格式化字符串
	vIndex.vt = VT_I2;
	vIndex.iVal = index;
	//vValue = m_pRecordset->Fields->GetItem(vIndex)->Value;
   TryGetValueByIndex(vValue,vIndex);
	switch(vValue.vt)
	{
	case VT_NULL:
	case VT_ERROR:
	case VT_EMPTY:
		break;
	default:
		iValue = vValue.iVal;
	}
	strType.Format(_T("%d"),strSum);
	strType = _T("%")+strType+_T("d");
	strValue.Format(strType,iValue);

	return strValue;	
}

CString CADOConn::GetValueInt64Str(int index,int strSum)
{
	ASSERT(m_pRecordset != NULL);

	_variant_t vValue;//var型返回值
	_variant_t vIndex;//索引
	__int64 llValue = 0;//数值返回值
	CString strValue,strType;//strValue:字符串返回值 strType:格式化字符串
	vIndex.vt = VT_I2;
	vIndex.iVal = index;
   //vValue = m_pRecordset->Fields->GetItem(vIndex)->Value;
   TryGetValueByIndex(vValue,vIndex);
   switch(vValue.vt)
	{
	case VT_NULL:
	case VT_ERROR:
	case VT_EMPTY:
		break;
	default:
		llValue = vValue.llVal;
	}

	strType.Format(_T("%d"),strSum);
	strType = _T("%")+strType+_T("lld");//格式化：%lld    无符号：llu
	strValue.Format(strType,llValue);

	return strValue;
}

CString CADOConn::GetValueDoubleStr(int index,int strLSum,int strRSum)
{
	ASSERT(m_pRecordset != NULL);

	_variant_t vValue;//var型返回值
	_variant_t vIndex;//索引
	double dValue = 0;//数值返回值
	CString strValue,strType;//strValue:字符串返回值 strType:格式化字符串
	vIndex.vt = VT_I2;
	vIndex.iVal = index;
	//vValue = m_pRecordset->Fields->GetItem(vIndex)->Value;
   TryGetValueByIndex(vValue,vIndex);
	switch(vValue.vt)
	{
	case VT_NULL:
	case VT_ERROR:
	case VT_EMPTY:
		break;
	default:
		dValue = vValue.dblVal;
	}

	strType.Format(_T("%d.%d"),strLSum,strRSum);
	strType = _T("%")+strType+_T("f");
	strValue.Format(strType,dValue);

	return strValue;
}


CString CADOConn::GetValueFloatStr(int index,int strLSum,int strRSum)
{
	ASSERT(m_pRecordset != NULL);

	_variant_t vValue;//var型返回值
	_variant_t vIndex;//索引
	float fValue = 0;//数值返回值
	CString strValue,strType;//strValue:字符串返回值 strType:格式化字符串
	vIndex.vt = VT_I2;
	vIndex.iVal = index;
	//vValue = m_pRecordset->Fields->GetItem(vIndex)->Value;
   TryGetValueByIndex(vValue,vIndex);
	switch(vValue.vt)
	{
	case VT_NULL:
	case VT_ERROR:
	case VT_EMPTY:
		break;
	default:
		fValue = vValue.fltVal;
	}

	strType.Format(_T("%d.%d"),strLSum,strRSum);
	strType = _T("%")+strType+_T("f");
	strValue.Format(strType,fValue);

	return strValue;
}

CString CADOConn::GetValueLongStr(int index,int strSum)
{
	ASSERT(m_pRecordset != NULL);

	_variant_t vValue;//var型返回值
	_variant_t vIndex;//索引
	long lValue = 0;//数值返回值
	CString strValue,strType;//strValue:字符串返回值 strType:格式化字符串
	vIndex.vt = VT_I2;
	vIndex.iVal = index;
	//vValue = m_pRecordset->Fields->GetItem(vIndex)->Value;
   TryGetValueByIndex(vValue,vIndex);
	switch(vValue.vt)
	{
	case VT_NULL:
	case VT_ERROR:
	case VT_EMPTY:
		break;
	default:
		lValue = vValue.lVal;
	}

	strType.Format(_T("%d"),strSum);
	strType = _T("%")+strType+_T("d");
	strValue.Format(strType,lValue);

	return strValue;	
}

CString CADOConn::GetValueDateStr(int index,CString strType)
{
	ASSERT(m_pRecordset != NULL);

	_variant_t vValue;//var型返回值
	_variant_t vIndex;//索引
	vIndex.vt = VT_I2;
	vIndex.iVal = index;

	COleDateTime TValue = COleDateTime::GetCurrentTime();

	//vValue = m_pRecordset->Fields->GetItem(vIndex)->Value;
   TryGetValueByIndex(vValue,vIndex);
	switch(vValue.vt)
	{
	case VT_NULL:
	case VT_ERROR:
	case VT_EMPTY:
		break;
// 	case VT_BSTR:
// 		{
// 			CString strDate = _T("");
// 			strDate = (LPCSTR)_bstr_t(vValue);
// 			TValue = Str2OleDateTime(strDate);
// 		}
// 		break;	
	default:
		TValue = COleDateTime(vValue);
		break;
	}

	CString strRet = TValue.Format(strType);
	return strRet;	
}


BOOL CADOConn::QueryTableFields(CString strTable,CString strField)
{
	BOOL bRet = FALSE;

	strTable.Trim();
	strField.Trim();
	ASSERT(!strTable.IsEmpty());
	ASSERT(!strField.IsEmpty());

	CString strSQL = _T("");
	strSQL.Format(_T("Select name from SYSCOLUMNS where ID=OBJECT_ID('%s') and name= '%s'"),strTable,strField);

	GetRecordSet(strSQL);

	if(0 == GetRecordCount())
	{
		bRet = FALSE;
	}
	else
	{
		bRet = TRUE;
	}


	return bRet;
}

/*
int CADOConn::CreateTableFields(CString strTable,CString strField)
{
	int nRet = 0;

	strTable.Trim();
	strField.Trim();
	ASSERT(!strTable.IsEmpty());
	ASSERT(!strField.IsEmpty());
	
	CString strSQL = _T("");
	if (QueryTable(strTable))
	{
		if (QueryTableFields(strTable,strField))
		{
			nRet = 1;//存在
		}
		else
		{

		}
	}
	else
	{
		;
	}

	return nRet;
}
*/

BOOL CADOConn::QueryTable(CString strTable)
{
	strTable.Trim();
	ASSERT(!strTable.IsEmpty());

	//方法①
/*	if (strTable.GetLength()>4)
	{
		CString strPre = strTable.Left(4);
		if(0 == _tcsicmp(strPre,_T("dbo.")))
		{
			strTable = strTable.Right(strTable.GetLength()-4);
		}
	}

	try
	{
		//是否已经连接数据库
		if(!InitConnect())//如果Connection对象为空，则重新连接数据库
			return FALSE;

		HRESULT hr = m_pRecordset.CreateInstance(__uuidof(Recordset));//创建记录集对象
		if (SUCCEEDED(hr))
		{
			m_pRecordset = m_pConnection->OpenSchema(adSchemaTables);
			while(!m_pRecordset->adoEOF) 
			{
				CString strDBTable = _T("");
				strDBTable = (LPCSTR)_bstr_t(m_pRecordset->Fields->GetItem("TABLE_NAME")->Value); 
				if(0 == _tcsicmp(strTable,strDBTable))
				{
					return TRUE;
					//break;
				}

				m_pRecordset->MoveNext();
			}

			return FALSE;
		}
		else
		{
			m_pRecordset->Close();
			m_pRecordset = NULL;
			return FALSE;
		}
	}
	catch(_com_error& e)
	{
		CString strError = e.ErrorMessage();
		ThrowExceptionMsg(strError,_T(""));
		return FALSE;
	}
   catch(...)
   {
		//未知错误
		bRet = FALSE;
   }
*/

	//方法②
	try
	{
		//是否已经连接数据库
		if(!InitConnect())//如果Connection对象为空，则重新连接数据库
			return FALSE;

		HRESULT hr = m_pRecordset.CreateInstance(__uuidof(Recordset));//创建记录集对象
		if (SUCCEEDED(hr))
		{
			HRESULT hr = m_pRecordset->Open(_variant_t(strTable),_variant_t((IDispatch *)m_pConnection,true), 
				adOpenKeyset,adLockOptimistic, adCmdTable);
			if (SUCCEEDED(hr))
			{
				return TRUE;
			}
			else
			{
				m_pRecordset->Close();
				m_pRecordset = NULL;
				return FALSE;
			}
		}
		else
		{
			return FALSE;
		}
	}
	catch(_com_error& e)
	{
		m_pRecordset = NULL;
      auto s = e.ErrorMessage();
		TRACE(_T("%s"),e.ErrorMessage());
		return FALSE;
	}
   catch(...)
   {
      m_pRecordset = NULL;
      return FALSE;
   }
}

int	CADOConn::CreateDB(CString strDBName,CString strSysDB/* = _T("master")*/)
{
	int nRet = 0;

	if (!m_strConnectSql.IsEmpty())
	{
		//此方法创建数据库，只针对SQL数据库
		//m_strConnectSql = _T("Driver={SQL Server};Server=192.168.3.39,1433;Database=qili;UID=sa;PWD=wzl123456");
		if (m_strConnectSql.Find(_T("SQL Server"))>-1)
		{
			CString strConnetSql = m_strConnectSql;

			int nPosStart = m_strConnectSql.Find(_T("Database="));
			int nPosEnd = m_strConnectSql.Find(_T(";UID="));

			m_strConnectSql = m_strConnectSql.Left(nPosStart+9) + strSysDB + m_strConnectSql.Right(m_strConnectSql.GetLength()-nPosEnd);

			if(!InitConnect())//如果Connection对象为空，则重新连接数据库
			{
				nRet = 2;//2 初始化失败
			}
			else
			{
				try
				{
					CString strUse = _T("USE ") + strDBName;
					m_pConnection->Execute(_bstr_t(strUse),NULL,adCmdText|adExecuteNoRecords);
					nRet = 1;//1 数据库存在
				}
				catch(_com_error& e)
				{
					CString strDescription = e.Description();
					CString strSQL = _T("");
					strSQL.Format(_T("create database %s"),strDBName);
					if(!ExecuteSQL(strSQL))
					{
						nRet = 3;//3 创建数据库失败
					}
				}
            catch(...)
            {
               nRet = 4;//4 未知错误
            }
			}

			m_strConnectSql = strConnetSql;
		}
		else
		{
			nRet = 3;//3 创建数据库失败
		}
		
	}
	
	return nRet;
}

//事务开始
BOOL CADOConn::BeginTrans()
{
	BOOL bRet = TRUE;
	if (m_pConnection == NULL)
	{
		//bRet = FALSE;
		if(!InitConnect())
		{
			bRet = FALSE;
		}
	}
	
	try
	{
		m_pConnection->BeginTrans();
	}
	catch (_com_error e) 
	{
		TRACE(_T("%s"),e.Description());
		bRet = FALSE;
	}
   catch(...)
   {
      //未知错误
      bRet = FALSE;
   }

	 
	return bRet;
}

//递交事务
BOOL CADOConn::CommitTrans()
{
	BOOL bRet = TRUE;
	if (m_pConnection == NULL)
	{
		//bRet = FALSE;
		if(!InitConnect())
		{
			bRet = FALSE;
		}
	}
	
	try
	{
		m_pConnection->CommitTrans();
	}
	catch (_com_error e)
	{
		TRACE(_T("%s"),e.Description());
		bRet = FALSE;
	}
   catch(...)
   {
      //未知错误
      bRet = FALSE;
   }
	
	return bRet;
}
//事务回滚
BOOL CADOConn::RollbackTrans()
{
	BOOL bRet = TRUE;
	if (m_pConnection == NULL)
	{
		//bRet = FALSE;
		if(!InitConnect())
		{
			bRet = FALSE;
		}
	}
	
	try
	{
		m_pConnection->RollbackTrans();
	}
	catch (_com_error e)
	{
		TRACE(_T("%s"),e.Description());
		bRet = FALSE;
	}
   catch(...)
   {
      //未知错误
      bRet = FALSE;
   }
	
	return bRet;
}


void CADOConn::AppendBatchSQL(CString strSQL)
{
	strSQL.Trim();
	if (!strSQL.IsEmpty())
	{
		int nLenTmp = strSQL.GetLength();
		if ((nLenTmp+m_strBatchSql.GetLength())>m_nBatchLen)//暂定每个SQL语句长度：m_nBatchLen
		{
			m_listBatchSql.AddTail(m_strBatchSql);
			m_strBatchSql.Empty();
		}

		if (!m_strBatchSql.IsEmpty())
		{
			m_strBatchSql += _T("\n");
		}

		m_strBatchSql += strSQL;
	}	
}

BOOL CADOConn::ExecuteBatchSQL()
{
	BOOL bRet = TRUE;

	for (int i=0;i<m_listBatchSql.GetCount();i++)
	{
		CString strSQL = m_listBatchSql.GetAt(m_listBatchSql.FindIndex(i));
      if (!strSQL.IsEmpty())
      {
         if(!ExecuteSQL(strSQL))
         {
            bRet = FALSE;
            break;
         }
      }
	}

	if (bRet && (!m_strBatchSql.IsEmpty()))
	{
		if(!ExecuteSQL(m_strBatchSql))
		{
			bRet = FALSE;
		}
	}

	//清空
	m_strBatchSql.Empty();
	m_listBatchSql.RemoveAll();

	return bRet;
}

void CADOConn::SetExceptionHwnd(HWND hWndExceptionMsg)
{
	m_hWndExceptionMsg = hWndExceptionMsg;
}

void CADOConn::ThrowExceptionMsg(CString strErrorType,CString strDescripion)
{
   if (strErrorType.IsEmpty()) strErrorType = _T("NULL");
   if (strDescripion.IsEmpty()) strDescripion = _T("NULL");

   //::MessageBox(NULL,_T("数据库连接异常："+strErrorType + "\n描述" + strDescripion),_T("温馨提示"),MB_OK|MB_ICONERROR);
   if(!m_hWndExceptionMsg) m_hWndExceptionMsg = AfxGetMainWnd()->GetSafeHwnd();
   if(m_hWndExceptionMsg)
   {
      CString strMsg = _T("");
      strMsg.Format(_T("数据库异常：%s\n描述：%s"),strErrorType,strDescripion);
      SendMessage(m_hWndExceptionMsg,WM_ADOCONN_MSG, NULL, (LPARAM)(LPCTSTR)strMsg);
   }
   else
   {
      TRACE(_T("handle=NULL and connect DB failed!\n"));
   }
}


BOOL CADOConn::SetCommandParameter(CString strField,CString strValue)
{
   BOOL bRet = FALSE;

   try
   {
      if(m_pConnection == NULL)
      {
         //是否已经连接数据库
         if(!InitConnect())//如果Connection对象为空，则重新连接数据库
            return FALSE;
      }
      else
      {
         if(adStateClosed == m_pConnection->State)
         {
            m_pConnection->Close();
            m_pConnection = NULL;

            return SetCommandParameter(strField,strValue);
         }
      }

      HRESULT hr = S_OK;
      if (m_pCommand == NULL)
      {
         hr = m_pCommand.CreateInstance("ADODB.Command"); 
      }
      
      if (SUCCEEDED(hr)) 
      {
         int nDataLen = strValue.GetLength();
#ifdef _UNICODE
         DWORD dwMinSize;
         dwMinSize = WideCharToMultiByte(CP_OEMCP,NULL,strValue,-1,NULL,0,NULL,FALSE);
         nDataLen = dwMinSize;
#endif // _DEBUG
         _ParameterPtr pParameter;
         pParameter = m_pCommand->CreateParameter((_bstr_t)strField,adVarChar,adParamInput,nDataLen,(_variant_t)strValue);
         m_pCommand->Parameters->Append(pParameter);
         m_pCommand->Parameters->Refresh();  

         bRet = TRUE;
      }
   }
   catch(_com_error& e)//捕捉异常
   {
      CString strError = e.ErrorMessage();
      CString strDescript = e.Description();
      ThrowExceptionMsg(strError,strDescript);
      
      if (m_pCommand)
      {
         m_pCommand->Cancel();
         m_pCommand = NULL;
      }

      bRet = FALSE;
   }
   catch(...)
   {
      if (m_pCommand)
      {
         m_pCommand->Cancel();
         m_pCommand = NULL;
      }

      bRet = FALSE;
   }
   

   return bRet;
}

BOOL CADOConn::ExecuteCommandSQL(CString strSQL)
{
   BOOL bRet = FALSE;

   try
   {
      if(m_pConnection == NULL)
      {
         //是否已经连接数据库
         if(!InitConnect())//如果Connection对象为空，则重新连接数据库
            return FALSE;
      }
      else
      {
         if(adStateClosed == m_pConnection->State)
         {
            m_pConnection->Close();
            m_pConnection = NULL;

            ExecuteCommandSQL(strSQL);
         }
      }

      strSQL.Trim();
      if (m_pCommand == NULL)
      {
         m_pCommand.CreateInstance("ADODB.Command"); 
      }
      m_pConnection->CursorLocation =adUseClient;

      _variant_t vNULL;   
      vNULL.vt = VT_ERROR;   
      vNULL.scode = DISP_E_PARAMNOTFOUND;             //定义为无参数   
      m_pCommand->ActiveConnection = m_pConnection;   //非常关键的一句，将建立的连接赋值给它   
      m_pCommand->CommandText = (_bstr_t)strSQL;      //命令字串   
      m_pCommand->Execute(&vNULL,&vNULL,adCmdText);   //执行命令
      m_pCommand->Cancel();
      //m_pCommand->Release();
      m_pCommand = NULL;

      return TRUE;
   }
   catch(_com_error& e)
   {
      CString strErr = e.ErrorMessage();
      CString strDes = e.Description();
      ThrowExceptionMsg(_T(""),strDes);

      return FALSE;
   }
   catch(...)
   {
      return FALSE;
   }

   return bRet;
}

_RecordsetPtr& CADOConn::GetCommandRecordSet(CString strSQL)
{
   try
   {
      if(m_pConnection == NULL)
      {
         if(!InitConnect())//如果Connection对象为空，则重新连接数据库
         {
            return m_pRecordset;//m_pRecordset=NULL
         }
      }

      //2017/04/28 zhangt 判断
      if (m_pRecordset)
      {
         m_pRecordset->Close();
         m_pRecordset = NULL;
      }
     

      strSQL.Trim();

      HRESULT hr = m_pRecordset.CreateInstance(__uuidof(Recordset));//创建记录集对象
      if (SUCCEEDED(hr))
      {
         if (m_pCommand == NULL)
         {
            hr = m_pCommand.CreateInstance("ADODB.Command"); 
         }
         m_pRecordset->CursorLocation = adUseClient;
         m_pConnection->CursorLocation =adUseClient;
        
         _variant_t vNULL;   
         vNULL.vt = VT_ERROR;   
         vNULL.scode = DISP_E_PARAMNOTFOUND;             //定义为无参数   
         m_pCommand->ActiveConnection = m_pConnection;   //非常关键的一句，将建立的连接赋值给它   
         m_pCommand->CommandText = (_bstr_t)strSQL;      //命令字串   
         m_pRecordset = m_pCommand->Execute(&vNULL,&vNULL,adCmdText);//执行命令，取得记录集 
         m_pCommand->Cancel();
         //m_pCommand->Release();
         m_pCommand = NULL;
      }
   }
   catch(_com_error& e)//捕捉异常
   {
      CString strError = e.ErrorMessage();
      CString strDescript = e.Description();
      ThrowExceptionMsg(strError,strDescript);

      m_pRecordset = NULL;
      if (m_pConnection)
      {
         m_pConnection->Close();
         m_pConnection = NULL;
      }
   }
   catch(...)
   {
      m_pRecordset = NULL;
      if (m_pConnection)
      {
         m_pConnection->Close();
         m_pConnection = NULL;
      }
   }

   return m_pRecordset;//返回记录集
}

//事务批量处理，失败撤回接口 yangjr 2018/11/25
BOOL CADOConn::ExecuteSQLByTransaction(const std::vector<CString> &vecSQL,int nOneCommintSqlNum)
{
   if (vecSQL.empty())
   {
      return FALSE;
   }
   BOOL bRet = TRUE;
   BeginTrans();
   int nSqlNum = 1;
   CString strSql = _T("");
   for (std::vector<CString>::const_iterator iterVec=vecSQL.begin();iterVec!=vecSQL.end();++iterVec)
   {      
      if (!iterVec->IsEmpty())
      {
         if (!strSql.IsEmpty())
         {
            strSql += _T(";");
         }
         strSql += *iterVec;
         if (nSqlNum == nOneCommintSqlNum)
         {
            if(!ExecuteSQL(strSql))
            {
               bRet = FALSE;
               break;
            }
            nSqlNum = 1;
            strSql = _T("");
         }else
         {
            ++nSqlNum;
         }        
      }
   }
   if (bRet && !strSql.IsEmpty())
   {
      if(!ExecuteSQL(strSql))
      {
         bRet = FALSE;;
      }
   }

   if (bRet)
   {
      CommitTrans();
   }else
   {
      RollbackTrans();
   }
   return bRet;
}