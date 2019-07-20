/*
 * 创建时间：2016‎年0‎2‎月‎24‎日		作者：zhangtao
 * 作用：
 *	方便访问数据库，无需进行ODBC配置数据库
 *	在配置文件ConfigSvr.ini中修改关键字
 *	ConfigSvr.ini文件存放的路径可修改函数GetConncetSqlStr()中代码
 */

#pragma once
#include <vector>

#pragma warning(disable:4146)//消除4146警告
//#import "C:\Program Files\Common Files\System\ADO\msado15.dll" no_namespace rename("EOF", "adoEOF")  
#ifdef ADO_ENUM_ERR//2017-07-18 wangzl ADO枚举冲定义解决方案  在属性-C/C++-预处理器-预处理器定义 中定义ADO_ENUM_ERR
#import "msado15.dll" no_namespace \
	rename("EOF","adoEOF") rename("DataTypeEnum","adoDataTypeEnum") \
	rename("FieldAttributeEnum", "adoFielAttributeEnum") rename("EditModeEnum", "adoEditModeEnum") \
	rename("LockTypeEnum", "adoLockTypeEnum") rename("RecordStatusEnum", "adoRecordStatusEnum") \
	rename("ParameterDirectionEnum", "adoParameterDirectionEnum")
#else
#import "msado15.dll" no_namespace rename("EOF", "adoEOF")//2017/03/16 zhangt 兼容XP及以上Win系统 
#endif // ADOERR

//向主窗口发消息
#define WM_ADOCONN_MSG	WM_USER+0x80

class CADOConn
{
public:
	CADOConn(void);
	~CADOConn(void);

	/*
	 * @brief	记录集移向开头
	 */
	BOOL MoveFirst();

	/*
	 * @brief	记录集向下移动
	 */
	BOOL MoveNext();

	/*
	 * @brief	判断记录集是否结束
	 */
	BOOL adoEOF();

	/*
	 * @brief	执行SQL语句(Insert Update delete)
	 * @example
	            UINT64 i = 0xFFFFFFFF;
	            CString str = _T("所有权限");
	            strSQL.Format(_T("insert into dbo.Table_Permission(PS_Value,PS_Name) values('%llu','%s')"),i,str);插入数据
	            //strSQL.Format(_T("delete from dbo.Table_Permission"));删除表格dbo.Table_Permission中所有数据
	            CADOConn ADOConn;
	            ADOConn.ExecuteSQL(strSQL);
	 */
	BOOL ExecuteSQL(CString strSQL);

	/*
	 * @brief	基本同ExecuteSQL, 可以执行多条语句, 添加了事物处理，要么全部执行成功，要么全部执行失败
	 */
   BOOL ExecuteSQLWithTrans(const CString &strSQL);

	/*
	 * @brief	执行Select查询，返回查询结果集
	 */
	_RecordsetPtr& GetRecordSet(CString strSQL);

	/*
	 * @brief	返回数据集数，执行GetRecordSet后再调用
	 */
	long GetRecordCount();

	/*
	 * @brief	返回字段数量，执行GetRecordSet后再调用
	 */
	int GetFeildsCount();

	/*
	 * @brief	返回字段名字，执行GetRecordSet后再调用
	 * @param	index 从0开始
	 */
	CString GetFieldsName(int index);

	/*
	 * @brief	返回记录集中某字段的字节，执行GetRecordSet后再调用
	 * @param	index 字段集中的索引，从0开始
	 */
	byte GetValueByte(int index);

	/*
	 * @brief	返回记录集中某字段的短整数，执行GetRecordSet后再调用
	 * @param	index 字段集中的索引，从0开始
	 */
	int GetValueInt(int index);

	/*
	 * @brief	返回记录集中某字段的短整数，执行GetRecordSet后再调用
	 * @param	strField 表中字段名称
	 */
	int GetValueInt(CString strField);

	/*
	 * @brief	返回记录集中某字段的64位整形数，执行GetRecordSet后再调用
	 * @param	index 字段集中的索引，从0开始
	 */
	__int64 GetValueInt64(int index);

	/*
	 * @brief	返回记录集中某字段的64位整形数，执行GetRecordSet后再调用
	 * @param	strField 表中字段名称
	 */
	__int64 GetValueInt64(CString strField);

	/*
	 * @brief	返回记录集中某字段的双精度数，执行GetRecordSet后再调用
	 * @param	index 字段集中的索引，从0开始
	 */
	double GetValueDouble(int index);

	/*
	 * @brief	返回记录集中某字段的双精度数，执行GetRecordSet后再调用
	 * @param	strField 表中字段名称
	 */
	double GetValueDouble(CString strField);

   /*
	 * @brief	获取记录集某字段的Double值(小数点有位数限定)，并换为CString返回，执行GetRecordSet后再调用
	 * @param	strField 表中字段名称
	 * @param	dotNum (小数部分):返回的小数部分的长度(<=实际:代表全部返回,>实际:右补0)
	 */
	CString GetValueDoubleStr(CString strField,int dotNum);

	/*
	 * @brief	返回记录集中某字段的单精度数，执行GetRecordSet后再调用
	 * @param	index 字段集中的索引，从0开始
	 */
	float GetValueFloat(int index);

	/*
	 * @brief	返回记录集中某字段的单精度数，执行GetRecordSet后再调用
	 * @param	strField 表中字段名称
	 */
	float GetValueFloat(CString strField);

	/*
	 * @brief	返回记录集中某字段的长整型数，执行GetRecordSet后再调用
	 * @param	index 字段集中的索引，从0开始
	 */
	long GetValueLong(int index);//返回记录集中某字段的长整型数

	/*
	 * @brief	返回记录集中某字段的长整型数，执行GetRecordSet后再调用
	 * @param	strField 表中字段名称
	 */
	long GetValueLong(CString strField);

	/*
	 * @brief	返回记录集中某字段的日期时间，执行GetRecordSet后再调用
			      数据库中存的格式为字符串(yyyy-mm-dd HH-MM-SS)或(yyyy/mm/dd HH:MM:SS)
	 * @param	index 字段集中的索引，从0开始
	 */
	COleDateTime GetValueDate(int index);

	/*
	 * @brief	返回记录集中某字段的日期时间，执行GetRecordSet后再调用
				   数据库中存的格式为字符串(yyyy-mm-dd HH-MM-SS)或(yyyy/mm/dd HH:MM:SS)
	 * @param	strField 表中字段名称
	 */
	COleDateTime CADOConn::GetValueDate(CString strField);

	/*
	 * @brief	返回记录集中某字段的字符串，执行GetRecordSet后再调用
	 * @param	index 字段集中的索引，从0开始
	 * @param	strSum 返回的字符的长度(<=实际:代表全部返回,>实际:左补空格)
	 */
	CString GetValueString(int index,int strSum=0);

	/*
	 * @brief	返回记录集中某字段的字符串，执行GetRecordSet后再调用
	 * @param	strField 表中字段名称
	 * @param	strSum 返回的字符的长度(<=实际:代表全部返回,>实际:左补空格)
	 */
	CString GetValueString(CString strField,int strSum=0);

	/*
	 * @brief	获取记录集某字段的BYTE值，并换为CString返回，执行GetRecordSet后再调用
	 * @param	index 字段集中的索引，从0开始
	 * @param	strSum 返回的字符的长度(<=实际:代表全部返回,>实际:左补空格)
	 */
	CString GetValueByteStr(int index,int strSum);

	/*
	 * @brief	获取记录集某字段的INT值，并换为CString返回，执行GetRecordSet后再调用
	 * @param	index 字段集中的索引，从0开始
	 * @param	strSum 返回的字符的长度(<=实际:代表全部返回,>实际:左补空格)
	 */
	CString GetValueIntStr(int index,int strSum);

	/*
	 * @brief	获取记录集某字段的Int64值，并换为CString返回，执行GetRecordSet后再调用
	 * @param	index 字段集中的索引，从0开始
	 * @param	strSum 返回的字符的长度(<=实际:代表全部返回,>实际:左补空格)
	 */
	CString GetValueInt64Str(int index,int strSum);
	
	/*
	 * @brief	获取记录集某字段的Double值，并换为CString返回，执行GetRecordSet后再调用
	 * @param	index 字段集中的索引，从0开始
	 * @param	strLSum (整数部分):返回的整数部分的长度(<=实际:代表全部返回,>实际:左补空格)
	 * @param	strRSum (小数部分):返回的小数部分的长度(<=实际:代表全部返回,>实际:右补空格)
	 */
	CString GetValueDoubleStr(int index,int strLSum,int strRSum);
	
	/*
	 * @brief	获取记录集某字段的Float值，并换为CString返回，执行GetRecordSet后再调用
	 * @param	index 字段集中的索引，从0开始
	 * @param	strLSum (整数部分):返回的整数部分的长度(<=实际:代表全部返回,>实际:左补空格)
	 * @param	strRSum (小数部分):返回的小数部分的长度(<=实际:代表全部返回,>实际:右补空格)
	 */
	CString GetValueFloatStr(int index,int strLSum,int strRSum);
	
	/*
	 * @brief	获取记录集某字段的Long值，并换为CString返回，执行GetRecordSet后再调用
	 * @param	index 字段集中的索引，从0开始
	 * @param	strSum 返回的字符的长度(<=实际:代表全部返回,>实际:左补空格)
	 */
	CString GetValueLongStr(int index,int strSum);
	
	/*
	 * @brief	获取记录集某字段的COleDateTime值，并换为CString返回，执行GetRecordSet后再调用
				   数据库中存的格式为字符串(yyyy-mm-dd HH:MM:SS)
	 * @param	index 字段集中的索引，从0开始
	 * @param	strType 日期格式化类型 "%Y-%m-%d %H:%M:%S"
	 */
	CString GetValueDateStr(int index,CString strType=_T("%Y-%m-%d %H:%M:%S"));


	/*
	 * @brief	查询固定表中是否存在指定字段
	 * @author	zhangt 2017/04/12
	 * @param	strTable 固定表名称
	 * @param	strField 查询的字段
	 * @return	TRUE     存在
				   FALSE		不存在
	 */
	BOOL QueryTableFields(CString strTable,CString strField);


	//BOOL GetTableFieldInfo(CString strTable,CString strField,CADOFieldInfo &info);

	/*
	 * @brief	创建固定表中指定字段
	 * @author	zhangt 2017/04/12
	 * @param	strTable 固定表名称
	 * @param	strField 创建的字段
	 * @return	int
				   0 创建指定字段成功
				   1 指定字段存在
				   2 初始化失败				
				   3 创建指定字段失败
	 */
//	int CreateTableFields(CString strTable,CString strField);

	/*
	 * @brief	查询数据库是否存在指定表
	 * @author	zhangt 2017/04/12
	 * @param	strTable 指定表名称
	 * @return	TRUE		存在
				   FALSE		不存在
	 */
	BOOL QueryTable(CString strTable);


	/*
	 * @brief	根据指定系统数据库创建用户数据库(只针对SQL数据库)
	 * @author	zhangt 2017/04/12
	 * @param	strDBName	创建用户数据库名称
	 * @param	strSysDB	指定系统数据库
	 * @return	int
				   0 创建用户数据库成功
				   1 用户数据库存在
				   2 初始化失败				
				   3 创建用户数据库失败
               4 未知错误
	 */
	int	CreateDB(CString strDBName,CString strSysDB = _T("master"));


	/*
	 * @brief	追加批量SQL语句，与函数ExecuteBatchSQL一起使用
	 * @author	zhangt 2017/05/02
	 * @param	strSQL	需要指出的SQL语句
	 */
	void AppendBatchSQL(CString strSQL);
	/*
	 * @brief	批量执行SQL语句，必须先执行函数AppendBatchSQL
	 * @author	zhangt 2017/05/02
	 * @return	BOOL
				   TRUE	执行批量SQL语句成功
				   FALSE	执行批量SQL语句失败
	 */
	BOOL ExecuteBatchSQL();

	/*
	 * @brief	设置每次批量执行语句的长度
	 * @author	zhangt 2017/05/02
	 */
	void SetBatchLen(int nBatchLen);


	_ConnectionPtr& GetConnPtr()    {return m_pConnection;}
	_RecordsetPtr& GetRecoPtr()     {return m_pRecordset;}

	/*
	 * @brief	事务回滚
	 * @author	zhangt 2017/04/14
	 */
	BOOL RollbackTrans();

	/*
	 * @brief	递交事务
	 * @author	zhangt 2017/04/14
	 */
	BOOL CommitTrans();

	/*
	 * @brief	事务开始
	 * @author	zhangt 2017/04/14
	 */
	BOOL BeginTrans();

	/*
	 * @brief	发送异常消息窗口句柄
	 * @author	zhangt 2017/10/31
	 */
	void SetExceptionHwnd(HWND hWndExceptionMsg);
	////////////////////////////////////////////////


   /*
	 * @brief	防注入 设置参数
	 * @author	zhangt 2018/03/23
    * @example SetCommandParameter(DBPerson_key_UserID,strUserID);
	 */
   BOOL SetCommandParameter(CString strField,CString strValue);

   /*
	 * @brief	防注入 执行语句
	 * @author	zhangt 2018/03/23
    * @example 
               strSQL.Format(_T("update %s set %s =? where %s=?"),DB_TABLE_PERSON,DBPerson_key_InTime,DBPerson_key_UserID);
                BOOL bRet = ADOConn.ExecuteCommandSQL(strSQL);
	 */
   BOOL ExecuteCommandSQL(CString strSQL);

   /*
	 * @brief	防注入 获取查询记录集
	 * @author	zhangt 2018/03/23
    * @example 
               strSQL.Format(_T("select * from %s where %s=? and %s=?"),DB_TABLE_PERSON,DBPerson_key_UserID,DBPerson_key_Pwd);
               ADOConn.GetCommandRecordSet(strSQL);
	 */
   _RecordsetPtr& GetCommandRecordSet(CString strSQL);

   //事务批量处理，失败撤回接口 yangjr 2018/11/25
   //nOneCommintSqlNum:每次提交的sql语句个数
   BOOL ExecuteSQLByTransaction(const std::vector<CString> &vecSQL,int nOneCommintSqlNum=1);

protected:
	_ConnectionPtr m_pConnection; //指向Connection对象指针
	_RecordsetPtr m_pRecordset;   //指向Recordset对象的指针

   _CommandPtr m_pCommand;       //zhangt 2018/03/23 防注入

	CString m_strConnectSql;      //2016-02-28 连接数据库字符串
	BOOL m_bInitConnect;

   //wangzl 2018-5-10   如果你自己知道何时连接 何时关闭
public:
	/*
	 * @brief	初始化连接数据库
	 */
	virtual BOOL InitConnect();

	/*
	 * @brief	断开连接数据库
	 */
	void ExitConnect();

	void CloseConnect();

protected:

	/*
	 * @brief	Str2OleDateTime
	 */
	COleDateTime Str2OleDateTime(CString strDate);

	/*
	 * @brief	Var2OleDateTime
	 */
	COleDateTime Var2OleDateTime(_variant_t vDate);

   inline void TryGetValueByIndex(_variant_t & varValue,_variant_t & varIndex);
   inline void TryGetCollect(_variant_t & varValue,LPCTSTR lpszField);

   void ThrowExceptionMsg(CString strErrorType,CString strDescripion);

	CString m_strBatchSql;		   //批量处理变量 zhangt 2017/05/02
	CStringList m_listBatchSql;	//批量处理变量 zhangt 2017/05/02
	int m_nBatchLen;			      //批量处理变量 zhangt 2017/05/02
	HWND m_hWndExceptionMsg;		//2017/10/31 zhangt 发送异常消息窗口句柄
};

