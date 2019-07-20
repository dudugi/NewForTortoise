#pragma once
   //add by lida 2018/09/04

   //--一、修改字段默认值

   //alter table 表名 drop constraint 约束名字   ------说明：删除表的字段的原有约束

   //alter table 表名 add constraint 约束名字 DEFAULT 默认值 for 字段名称 -------说明：添加一个表的字段的约束并指定默认值

   //--二、修改字段名：

   //alter table 表名 rename column A to B

   //--三、修改字段类型：

   //alter table 表名 alter column UnitPrice decimal(18, 4) not null 

   //--四、修改增加字段：

   //alter table 表名 ADD 字段 类型 NOT NULL Default 0

   //--五、删除列

   //alter table tableName drop column columnName

   //判断是否存在约束条件
   //IF  EXISTS (SELECT t.name AS tName,c.name AS cName,ep.* FROM sys.default_constraints AS ep
   //INNER JOIN sys.columns AS c ON ep.parent_object_id = c.object_id
   //INNER JOIN sys.tables AS t ON t.object_id = c.object_id AND ep.parent_column_id = c.column_id WHERE 
   //t.name='Table_1' and c.name = 'test3')

   //判断是否存在字段说明
   //SELECT t.[name] AS 表名,c.[name] AS 字段名,cast(ep.[value] 
   //as varchar(100)) AS [字段说明]
   //FROM sys.tables AS t
   //INNER JOIN sys.columns 
   //AS c ON t.object_id = c.object_id
   //LEFT JOIN sys.extended_properties AS ep 
   //ON ep.major_id = c.object_id AND ep.minor_id = c.column_id WHERE ep.class =1 
   //AND t.name='Table_1'

#define SQL_SELECT  _T("SELECT\
   表明       = (case when a.colorder > 0 then d.name else ''end),\
   表说明     = case when a.colorder=1 then isnull(f.value,'') else '' end,\
   字段序号   = a.colorder,\
   字段名     = a.name,\
   标识       = case when COLUMNPROPERTY( a.id,a.name,'IsIdentity')=1 then '1'else '' end,\
   主键       = case when exists(SELECT 1 FROM sysobjects where xtype='PK' and parent_obj=a.id and name in (\
            SELECT name FROM sysindexes WHERE indid in( SELECT indid FROM sysindexkeys WHERE id = a.id AND colid=a.colid))) then '1' else '' end,\
   类型       = b.name,\
   占用字节数 = a.length,\
   长度       = COLUMNPROPERTY(a.id,a.name,'PRECISION'),\
   小数位数   = isnull(COLUMNPROPERTY(a.id,a.name,'Scale'),0),\
   允许空     = case when a.isnullable=1 then '1'else '' end,\
   默认值     = isnull(e.text,''),\
   字段说明   = isnull(g.[value],''),\
   索引名称	=isnull(i.name,'')\
   FROM syscolumns a\
   left join systypes b on a.xusertype=b.xusertype\
   inner join sysobjects d on a.id=d.id  and d.xtype='U' and  d.name<>'dtproperties'\
   left join syscomments e on a.cdefault=e.id\
   left join sys.extended_properties g on a.id=g.major_id and a.colid=g.minor_id  \
   left join sys.extended_properties f on d.id=f.major_id and f.minor_id=0\
   left join sysindexkeys h on h.id = a.id and h.colid = a.colid\
   left join sysindexes i on i.id = a.id and i.indid = h.indid and i.indid not in(0,255)\
   --where d.name = 'GongxuRecords'")


#define SCRIPT_HEADER _T("BEGIN TRANSACTION\r\n\
SET QUOTED_IDENTIFIER ON\r\n\
SET NUMERIC_ROUNDABORT OFF\r\n\
SET ARITHABORT ON\r\n\
SET CONCAT_NULL_YIELDS_NULL ON\r\n\
SET ANSI_NULLS ON\r\n\
SET ANSI_PADDING ON\r\n\
SET ANSI_WARNINGS ON\r\n\
COMMIT\r\n\
BEGIN TRANSACTION\r\n\
GO")

#define SCRIPT_BEGIN_TRY _T("BEGIN TRY\r\n")
#define SCRIPT_END_TRY   _T("END TRY\r\n")

#define SCRIPT_COMMIT _T("COMMIT")
#define SCRIPT_TAIL  _T("BEGIN CATCH\r\n RALLBACK\r\n END CATCH")

#define FIELD_TABLE_NAME      _T("表明")
#define FIELD_TABLE_DESC      _T("表说明")
#define FIELD_COL_ORDER       _T("字段序号")
#define FIELD_COL_NAME        _T("字段名")
#define FIELD_PRI_KEY         _T("主键")
#define FIELD_IDENTITY        _T("标识")
#define FIELD_COL_TYPE        _T("类型")
#define FIELD_COL_BYTES       _T("占用字节数")
#define FIELD_COL_LENGTH      _T("长度")
#define FIELD_COL_SACLE       _T("小数位数")
#define FIELD_COL_NULLABLE    _T("允许空")
#define FIELD_DEFAULT_VALUE   _T("默认值")
#define FIELD_COL_DESC        _T("字段说明")
#define FIELD_INDEX_NAME      _T("索引名称")

#pragma region 字段类型
typedef enum type_index
{
   t_bigint = 0,
   t_binary,
   t_bit,
   t_char,
   t_date,
   t_datetime,
   t_datetime2,
   t_datetimeoffset,
   t_decimal,
   t_float,
   t_geography,
   t_geometry,
   t_hierarchyid,
   t_image,
   t_int,
   t_money,
   t_nchar,
   t_ntext,
   t_numeric,
   t_nvarchar,
   t_real,
   t_smalldatetime,
   t_smallint,
   t_smallmoney,
   t_sql_variant,
   t_text,
   t_time,
   t_timestamp,
   t_tinyint,
   t_uniqueidentifier,
   t_varbinary,
   t_varchar,
   t_xml
}En_Type_Index;

static TCHAR  g_type[100][50]={
   {_T("bigint")},
   {_T("binary")},
   {_T("bit")},
   {_T("char")},
   {_T("date")},
   {_T("datetime")},
   {_T("datetime2")},
   {_T("datetimeoffset")},
   {_T("decimal")},
   {_T("float")},
   {_T("geography")},
   {_T("geometry")},
   {_T("hierarchyid")},
   {_T("image")},
   {_T("int")},
   {_T("money")},
   {_T("nchar")},
   {_T("ntext")},
   {_T("numeric")},
   {_T("nvarchar")},
   {_T("real")},
   {_T("smalldatetime")},
   {_T("smallint")},
   {_T("smallmoney")},
   {_T("sql_variant")},
   {_T("text")},
   {_T("time")},
   {_T("timestamp")},
   {_T("tinyint")},
   {_T("uniqueidentifier")},
   {_T("varbinary")},
   {_T("varchar")},
   {_T("xml")},

};

#pragma endregion 字段类型
                      
#pragma region 数据库连接信息
typedef struct db_connetion_info
{
   db_connetion_info()
   {
      Init();
   };

   void Init()
   {
      strIp = _T("");
      strPort = _T("");
      strDbName = _T("");
      strDbAccount = _T("");
      strDbPassword = _T("");
   };

   CString strIp;
   CString strPort;
   CString strDbName;
   CString strDbAccount;
   CString strDbPassword;
}tag_db_info;
#pragma endregion 数据库连接信息

#pragma region 表结构信息
typedef struct db_attri
{
   db_attri()
   {
      id = 0;            
      strTableName = _T("");      
      strTableDesc = _T("");   
      iColOrder = 0;     
      strColName = _T("");     
      iIdentity = 0;     
      iPrimaryKey = 0;    
      strColType = _T("");     
      iBytes = 0;        
      iLen = 0;          
      iScale = 0;        
      bIsNullable = FALSE;    
      strDefaultValue = _T("");
      strColDesc = _T("");
      strIndexName = _T("");
      bFlag = FALSE;   
      bFullNumberColName = FALSE;
      bDiff = FALSE;
   }

   //修改长度
   static BOOL AllowModifyLength(__in CString strType)
   {
      if (strType == g_type[t_binary] || strType == g_type[t_char] || strType == g_type[t_datetime2] || strType == g_type[t_decimal]
      ||strType == g_type[t_nchar] || strType == g_type[t_numeric] || strType == g_type[t_nvarchar] || strType == g_type[t_time]
      ||strType == g_type[t_varbinary] ||strType == g_type[t_varchar])
      {
         return TRUE;
      }
      return FALSE;
   };

   //修改精度
   static BOOL AllowModifySacle(__in CString strType)
   {
      if(strType == g_type[t_decimal] || strType == g_type[t_numeric])
      {
         return TRUE;
      }
      return FALSE;
   };

   //判断是否是数字类型
   static BOOL TypeIsDigital(__in CString strType)
   {
      if(strType == g_type[t_decimal] || strType == g_type[t_bigint] || strType == g_type[t_binary] || strType == g_type[t_bit]
         || strType == g_type[t_float] || strType == g_type[t_int] || strType == g_type[t_numeric] || strType == g_type[t_smallint]
         || strType == g_type[t_tinyint] || strType == g_type[t_varbinary])
      {
         return TRUE;
      }
      return FALSE;
   };

   //字段名全数字，纯数字的字段名要加上[]括号，否则会报错
   static BOOL ColNameFullNumber(__in CString strColName)
   {
      CString strTemp = strColName.SpanIncluding(_T("0123456789"));
      if (strTemp.GetLength() == strColName.GetLength())
      {
         return TRUE;
      }
      return FALSE;
   };

   //
   static BOOL TypeNeedConvert(__in CString strType)
   {
      if (strType == g_type[t_date] || strType == g_type[t_datetime] || strType == g_type[t_smalldatetime]
      || strType == g_type[t_nchar] || strType == g_type[t_nvarchar] || strType == g_type[t_char] || strType == g_type[t_varchar])
      {
         return TRUE;
      }
      return FALSE;
   };

   //满足主键的字段类型
   static BOOL IsIdentityType(__in CString strType,__in int iScale)
   {
      //标识列 'ID' 的数据类型必须是 int、bigint、smallint、tinyint 或 decimal，或者是小数位数为 0 的 numeric 数据类型，并且约束为不可为 Null。
      if (strType == g_type[t_int] || strType == g_type[t_bigint] || strType == g_type[t_smallint]
      || strType == g_type[t_tinyint] || strType == g_type[t_decimal] || (strType == g_type[t_numeric] && iScale == 0))
      {
         return TRUE;
      }
      return FALSE;
   };

   int         id;                  //id
   CString     strTableName;           //表名
   CString     strTableDesc;        //表说明
   int         iColOrder;          //字段序号
   CString     strColName;          //字段名
   int         iIdentity;          //标识
   int         iPrimaryKey;        //主键
   CString     strColType;          //类型
   int         iBytes;            //占用字节数
   int         iLen;               //长度
   int         iScale;             //小数位数
   BOOL        bIsNullable;         //允许空
   CString     strDefaultValue;     //默认值
   CString     strColDesc;          //字段说明
   CString     strIndexName;        //索引名称
   BOOL        bFlag;               //用来标记 src:0=add,dst:0=del
   BOOL        bFullNumberColName;  //全数字的字段名
   BOOL        bDiff;               //是否存在差异，不存在差异的表将不生成脚本
}tag_db_attri;

#pragma endregion 表结构信息

typedef vector<tag_db_attri> vec_db_attri;
typedef map<CString,vec_db_attri> map_db_attri;
typedef map<CString,vector<CString>>   mapSqlScript;      //脚本

static BOOL TableHasIdentityFlag(vec_db_attri& vec_db)
{
   for (int i=0; i<(int)vec_db.size(); ++i)
   {
      if (vec_db[i].iIdentity == 1 && vec_db[i].iPrimaryKey == 1)
      {
         return TRUE;
      }
   }
   return FALSE;
};

static BOOL IsDiffFieldAttri(tag_db_attri tag_src,tag_db_attri tag_dst)
{
   if (tag_src.strTableName != tag_dst.strTableName || tag_src.strColName != tag_src.strColName)
   {
      //表明 字段名不相同，无法比较
      return FALSE;
   }
   //标识
   if (tag_src.iIdentity != tag_dst.iIdentity)  
   {
      return TRUE;
   }
   //主键
   if (tag_src.iPrimaryKey != tag_dst.iPrimaryKey)
   {
      return TRUE;
   }
   //类型
   if (tag_src.strColType != tag_dst.strColType)
   {
      return TRUE;
   }
   //长度
   if (tag_src.iLen != tag_dst.iLen)
   {
      return TRUE;
   }
   //小数位数
   if (tag_src.iScale != tag_dst.iScale)
   {
      return TRUE;
   }
   //允许空
   if (tag_src.bIsNullable != tag_dst.bIsNullable)
   {
      return TRUE;
   }
   //默认值
   if (tag_src.strDefaultValue != tag_dst.strDefaultValue)
   {
      return TRUE;
   }
   //字段说明
   if (tag_src.strColDesc != tag_dst.strColDesc)
   {
      return TRUE;
   }
   //索引
   if (tag_src.strIndexName != tag_dst.strIndexName)
   {
      return TRUE;
   }
   return FALSE;
};

static BOOL IsDiffTableAttri(vec_db_attri& vec_db_src,vec_db_attri& vec_db_dst)
{
   CString strTableName1,strTableName2;
   if (vec_db_src.size() != vec_db_dst.size())
   {
      if (vec_db_src.size() > 0)
      {
         strTableName1 = vec_db_src.begin()->strTableName;
      }
      if (vec_db_dst.size() > 0)
      {
         strTableName2 = vec_db_dst.begin()->strTableName;
      }
      if (strTableName1 != strTableName2)
      {
         return FALSE;  //表不一样，无法比对
      }
      else
         return TRUE;
   }
   else
   {
      if (vec_db_src.size() > 0)
      {
         strTableName1 = vec_db_src.begin()->strTableName;
      }
      if (vec_db_dst.size() > 0)
      {
         strTableName2 = vec_db_dst.begin()->strTableName;
      }
      if (strTableName1 != strTableName2)
      {
         return FALSE;  //表不一样，无法比对
      }
      for(int isrc = 0; isrc<(int)vec_db_src.size(); ++isrc)
      {
         for (int idst = 0; idst<(int)vec_db_dst.size();++idst)
         {
            if (vec_db_src[isrc].strColName == vec_db_dst[idst].strColName)
            {
               if (IsDiffFieldAttri(vec_db_src[isrc],vec_db_dst[idst]))
               {
                  return TRUE;
               }
               break;
            }
         }
      }
      return FALSE;
   }
};


//生成修改默认值sql
static CString CreateDefaultValueSql(tag_db_attri tag_src)
{
   CString strSql_1,strSql_2,strSql_3;
   strSql_2.Format(_T("alter table %s drop constraint DF_%s_%s"),tag_src.strTableName,tag_src.strTableName,tag_src.strColName);

   if (tag_db_attri::TypeIsDigital(tag_src.strColType))
   {
      if (tag_src.bFullNumberColName)
      {
         strSql_3.Format(_T("alter table %s add constraint DF_%s_%s DEFAULT %s for [%s]"),tag_src.strTableName,tag_src.strTableName,tag_src.strColName,tag_src.strDefaultValue,tag_src.strColName);
      }
      else
         strSql_3.Format(_T("alter table %s add constraint DF_%s_%s DEFAULT %s for [%s]"),tag_src.strTableName,tag_src.strTableName,tag_src.strColName,tag_src.strDefaultValue,tag_src.strColName);
   }
   else
   {
      if (tag_src.bFullNumberColName)
      {
         strSql_3.Format(_T("alter table %s add constraint DF_%s_%s DEFAULT N'%s' for [%s]"),tag_src.strTableName,tag_src.strTableName,tag_src.strColName,tag_src.strDefaultValue,tag_src.strColName);
      }
      else
         strSql_3.Format(_T("alter table %s add constraint DF_%s_%s DEFAULT N'%s' for [%s]"),tag_src.strTableName,tag_src.strTableName,tag_src.strColName,tag_src.strDefaultValue,tag_src.strColName);
   }

   strSql_1.Format(_T("IF EXISTS (SELECT t.name AS tName,c.name AS cName,ep.* FROM sys.default_constraints AS ep \r\n\
                      INNER JOIN sys.columns AS c ON ep.parent_object_id = c.object_id \r\n\
                      INNER JOIN sys.tables AS t ON t.object_id = c.object_id AND ep.parent_column_id = c.column_id WHERE \r\n\
                      t.name='%s' and c.name = '%s')\r\n\
                      begin\r\n\
                      %s\r\n\
                      %s\r\n\
                      end\r\n\
                      else\r\n\
                      begin \r\n\
                      %s \r\n\
                      end\r\n"),
                    tag_src.strTableName,tag_src.strColName,strSql_2,strSql_3,strSql_3);
   strSql_1.Replace(_T("   "),_T(""));
   strSql_1.Replace(_T("  "),_T(""));
   return strSql_1;
};

//生成修改字段描述sql
static CString CreateDescriptionSql(tag_db_attri tag_src)
{
   CString strAdd,strModify,strSql;
   strAdd.Format(_T("EXECUTE sp_addextendedproperty N'MS_Description', N'%s', N'user', N'dbo', N'table', N'%s', N'column', N'%s'"),
                  tag_src.strColDesc,tag_src.strTableName,tag_src.strColName);
   strModify.Format(_T("EXEC sp_updateextendedproperty 'MS_Description',N'%s',N'user',N'dbo',N'table',N'%s',N'column',N'%s'"),
                  tag_src.strColDesc,tag_src.strTableName,tag_src.strColName);
   strSql.Format(_T("if exists(\
                    SELECT t.name AS tName,c.name AS cName,cast(ep.[value] as varchar(100)) AS cValue\r\n\
                    FROM sys.tables AS t\r\n\
                    INNER JOIN sys.columns\r\n\
                    AS c ON t.object_id = c.object_id\r\n\
                    LEFT JOIN sys.extended_properties AS ep\r\n\
                    ON ep.major_id = c.object_id AND ep.minor_id = c.column_id WHERE ep.class =1\r\n\
                    AND t.name='%s' and c.name = '%s')\
                    begin\r\n\
                    %s\r\n\
                    end\r\n\
                    else\r\n\
                    begin\r\n\
                    %s\r\n\
                    end"),tag_src.strTableName,tag_src.strColName,strModify,strAdd);
   strSql.Replace(_T("   "),_T(" "));
   strSql.Replace(_T("  "),_T(" "));
   return strSql;
}

static BOOL CreateSqlScript(__in CString strDstDbName,__in map_db_attri& db_attri_src,__in map_db_attri& db_attri_dst,__out mapSqlScript& map_sql_script)
{
   map_sql_script.clear();
#pragma region 找出新增、删除字段，并标记
   for (auto itr_src = db_attri_src.begin(); itr_src != db_attri_src.end(); ++itr_src)
   {
      for (int isrc = 0; isrc <(int)itr_src->second.size(); ++isrc)
      {
         auto itr_dst = db_attri_dst.find(itr_src->first);
         if (itr_dst != db_attri_dst.end())
         {
            for (int idst = 0; idst < (int)itr_dst->second.size();++idst)
            {
               if (itr_src->second[isrc].strColName == itr_dst->second[idst].strColName)
               {
                  itr_src->second[isrc].bFlag = 1;
                  itr_dst->second[idst].bFlag = 1;
                  break;
               }
            }
         }
      }
   }
#pragma endregion 找出新增、删除字段，并标记

   vector<CString> vecSqlScript;
   for (auto itr_src = db_attri_src.begin(); itr_src != db_attri_src.end(); ++itr_src)
   {
      auto itr_dst = db_attri_dst.find(itr_src->first);
      if (itr_dst != db_attri_dst.end())
      {
         if (FALSE == IsDiffTableAttri(itr_src->second,itr_dst->second))
         {
            continue;
         }
      }
      vecSqlScript.push_back(_T("USE ")+ strDstDbName +_T("\r\nGO"));
      vecSqlScript.push_back(SCRIPT_HEADER);
#pragma region DROP CONSTRAINT
      auto itr_dst0 = db_attri_dst.find(itr_src->first);
      if (itr_dst0 != db_attri_dst.end())
      {
         for (int idst = 0; idst < (int)itr_dst0->second.size();++idst)
         {
            if (itr_dst0->second[idst].iPrimaryKey == 0 && !itr_dst0->second[idst].strDefaultValue.IsEmpty())
            {
               CString strSql;
               strSql.Format(_T("IF EXISTS (SELECT t.name AS tName,c.name AS cName,ep.* FROM sys.default_constraints AS ep\r\n\
                                INNER JOIN sys.columns AS c ON ep.parent_object_id = c.object_id\r\n\
                                INNER JOIN sys.tables AS t ON t.object_id = c.object_id AND ep.parent_column_id = c.column_id WHERE\r\n\
                                t.name='%s' and c.name = '%s')\r\n\
                                BEGIN\r\n\
                                ALTER TABLE dbo.%s DROP CONSTRAINT DF_%s_%s\r\n\
                                END\r\n\
                                GO"),
                                itr_src->first,itr_dst0->second[idst].strColName,itr_src->first,itr_src->first,itr_dst0->second[idst].strColName);
               strSql.Replace(_T("   "),_T(""));
               strSql.Replace(_T("  "),_T(""));
               vecSqlScript.push_back(strSql);
            }
         }
      }
#pragma endregion DROP CONSTRAINT

#pragma region Create Field Sql
      CString strField;
      BOOL bMax = FALSE;
      vector<CString> vecField;
      for (int isrc = 0; isrc<(int)itr_src->second.size(); ++isrc)
      {
         auto itr_field = std::find(vecField.begin(),vecField.end(),itr_src->second[isrc].strColName);
         if (itr_field != vecField.end())
         {
            continue;
         }
         vecField.push_back(itr_src->second[isrc].strColName);
         CString strTemp,strColName,strType,strNull,strPrimary;
         strColName = itr_src->second[isrc].strColName;
         if (db_attri::AllowModifySacle(itr_src->second[isrc].strColType))
         {
            strType.Format(_T("%s(%d,%d)"),itr_src->second[isrc].strColType,itr_src->second[isrc].iLen,itr_src->second[isrc].iScale);
         }
         else if (db_attri::AllowModifyLength(itr_src->second[isrc].strColType))
         {
            if (itr_src->second[isrc].iLen == -1)    //MAX
            {
               strType.Format(_T("%s(MAX)"),itr_src->second[isrc].strColType);
               bMax = TRUE;
            }
            else
               strType.Format(_T("%s(%d)"),itr_src->second[isrc].strColType,itr_src->second[isrc].iLen);
         }
         else
         {
            strType = itr_src->second[isrc].strColType;
         }
         strNull = itr_src->second[isrc].bIsNullable == 1?_T("NULL"):_T("NOT NULL");
         if (itr_src->second[isrc].iPrimaryKey == 1 && db_attri::IsIdentityType(itr_src->second[isrc].strColType,itr_src->second[isrc].iScale))
         {
            strPrimary.Format(_T("IDENTITY (1, %d)"),itr_src->second[isrc].iIdentity);
         }
         else
            strPrimary = _T("");

         //ID bigint NOT NULL IDENTITY (1, 1),
         if (isrc +1 == itr_src->second.size())
            strTemp.Format(_T("%s %s %s %s\r\n"),strColName,strType,strNull,strPrimary);
         else
            strTemp.Format(_T("%s %s %s %s,\r\n"),strColName,strType,strNull,strPrimary);
         strField += strTemp;
      }
#pragma endregion Create Field Sql

#pragma region CREATE TABLE
      CString strSql_CreateTmpTable;
      if (bMax)
      {
         strSql_CreateTmpTable.Format(_T("CREATE TABLE dbo.Tmp_%s\r\n (%s) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY] \r\nGO"),itr_src->first,strField);
      }
      else
      {
         strSql_CreateTmpTable.Format(_T("CREATE TABLE dbo.Tmp_%s\r\n (%s) ON [PRIMARY] \r\nGO"),itr_src->first,strField);
      }
      vecSqlScript.push_back(strSql_CreateTmpTable);
#pragma endregion CREATE TABLE

#pragma region LOCK_ESCALATION
      CString strSetLock;
      strSetLock.Format(_T("ALTER TABLE dbo.Tmp_%s SET (LOCK_ESCALATION = TABLE)\r\n GO"),itr_src->first);
      vecSqlScript.push_back(strSetLock);
#pragma endregion LOCK_ESCALATION

#pragma region MS_DESCRIPTION
      vecField.clear();
      for (int isrc = 0; isrc<(int)itr_src->second.size(); ++isrc)
      {
         auto itr_field = std::find(vecField.begin(),vecField.end(),itr_src->second[isrc].strColName);
         if (itr_field != vecField.end())
         {
            continue;
         }
         vecField.push_back(itr_src->second[isrc].strColName);
         if (!itr_src->second[isrc].strColDesc.IsEmpty())
         {
            CString strDescription;
            strDescription.Format(_T("DECLARE @v sql_variant\r\n\
                                     SET @v = N'%s'\r\n\
                                     EXECUTE sp_addextendedproperty N'MS_Description', @v, N'SCHEMA', N'dbo', N'TABLE', N'Tmp_%s', N'COLUMN', N'%s'\r\n\
                                     GO"),
                                     itr_src->second[isrc].strColDesc,itr_src->first,itr_src->second[isrc].strColName);
            strDescription.Replace(_T("   "),_T(""));
            strDescription.Replace(_T("  "),_T(""));
            vecSqlScript.push_back(strDescription);
         }
      }
#pragma endregion MS_DESCRIPTION

#pragma region CONSTRAINT DEFAULT
      vecField.clear();
      for (int isrc = 0; isrc<(int)itr_src->second.size(); ++isrc)
      {
         auto itr_field = std::find(vecField.begin(),vecField.end(),itr_src->second[isrc].strColName);
         if (itr_field != vecField.end())
         {
            continue;
         }
         vecField.push_back(itr_src->second[isrc].strColName);
         if (itr_src->second[isrc].iPrimaryKey == 0 && !itr_src->second[isrc].strDefaultValue.IsEmpty())
         {
            CString strConstraint;
            if (db_attri::TypeIsDigital(itr_src->second[isrc].strColType))
            {
               strConstraint.Format(_T("ALTER TABLE dbo.Tmp_%s ADD CONSTRAINT\r\n DF_%s_%s DEFAULT %s FOR [%s]\r\nGO"),
                  itr_src->second[isrc].strTableName,itr_src->second[isrc].strTableName,itr_src->second[isrc].strColName,
                  itr_src->second[isrc].strDefaultValue,itr_src->second[isrc].strColName);
            }
            else
            {
               strConstraint.Format(_T("ALTER TABLE dbo.Tmp_%s ADD CONSTRAINT\r\n DF_%s_%s DEFAULT '%s' FOR [%s]\r\nGO"),
                  itr_src->second[isrc].strTableName,itr_src->second[isrc].strTableName,itr_src->second[isrc].strColName,
                  itr_src->second[isrc].strDefaultValue,itr_src->second[isrc].strColName);
            }
            vecSqlScript.push_back(strConstraint);
         }
      }
#pragma endregion CONSTRAINT DEFAULT

#pragma region SET IDENTITY_INSERT dbo.Tmp_WLKuanshi_Detail_info ON
      int iSetIdentityInsertOn = -1;
      if (TableHasIdentityFlag(itr_src->second))
      {
         CString strSetiDenttity_ON;
         strSetiDenttity_ON.Format(_T("SET IDENTITY_INSERT dbo.Tmp_%s ON\r\nGO"),itr_src->first);
         iSetIdentityInsertOn = vecSqlScript.size();
         vecSqlScript.push_back(strSetiDenttity_ON);
      }
#pragma endregion SET IDENTITY_INSERT dbo.Tmp_WLKuanshi_Detail_info ON

#pragma region INSERT VALUE
      BOOL bInsertValue = FALSE;
      CString strField1,strField2;
      vecField.clear();
      for (int isrc = 0; isrc<(int)itr_src->second.size(); ++isrc)
      {
         auto itr_field = std::find(vecField.begin(),vecField.end(),itr_src->second[isrc].strColName);
         if (itr_field != vecField.end())
         {
            continue;
         }
         vecField.push_back(itr_src->second[isrc].strColName);
         strField1 += itr_src->second[isrc].strColName + _T(",");
         if (itr_src->second[isrc].bFlag == 0)
         {
            continue;   //如果是新增的字段
         }
         if (itr_src->second[isrc].iLen == -1)
         {
            CString strTemp2;
            strTemp2.Format(_T("CONVERT(%s(MAX),%s)"),itr_src->second[isrc].strColType,itr_src->second[isrc].strColName);
            strField2 += strTemp2;
         }
         else
         {
            CString strTemp2;
            if (db_attri::TypeNeedConvert(itr_src->second[isrc].strColType))
            {
               strTemp2.Format(_T("%s,"),itr_src->second[isrc].strColType);
            }
            else
            {
               if (db_attri::AllowModifySacle(itr_src->second[isrc].strColType))
               {
                  strTemp2.Format(_T("CONVERT(%s(%d,%d),%s)"),itr_src->second[isrc].strColType,itr_src->second[isrc].iLen,
                     itr_src->second[isrc].iScale,itr_src->second[isrc].strColName);
               }
               else if (db_attri::AllowModifyLength(itr_src->second[isrc].strColType))
               {
                  strTemp2.Format(_T("CONVERT(%s(%d),%s)"),itr_src->second[isrc].strColType,itr_src->second[isrc].iLen,
                     itr_src->second[isrc].strColName);
               }
               else
               {
                  strTemp2.Format(_T("CONVERT(%s,%s)"),itr_src->second[isrc].strColType,itr_src->second[isrc].strColName);
               }
            }
            strField2 += strTemp2;
         }
      }
      strField1.TrimRight(_T(","));
      if (!strField1.IsEmpty() && !strField2.IsEmpty())
      {
         CString strInsert;
         strInsert.Format(_T("IF EXISTS(SELECT * FROM dbo.sysobjects where id = object_id(N'[dbo].[%s]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)\r\n\
                             IF EXISTS(SELECT * FROM dbo.%s)\r\n\
                             EXEC('INSERT INTO dbo.Tmp_%s (%s)\r\n\
                             SELECT %s FROM dbo.WLKuanshi_Detail_info WITH (HOLDLOCK TABLOCKX)')\r\nGO"),
                             itr_src->first,itr_src->first,itr_src->first,strField1,strField2);
         strInsert.Replace(_T("   "),_T(""));
         strInsert.Replace(_T("  "),_T(""));
         vecSqlScript.push_back(strInsert);
         bInsertValue = TRUE;
      }
      
#pragma endregion INSERT VALUE

#pragma region SET IDENTITY_INSERT dbo.Tmp_WLKuanshi_Detail_info OFF GO
      int iSetIdentityInsertOff = -1;
      if (TableHasIdentityFlag(itr_src->second))
      {
         CString strSetiDenttity_OFF;
         strSetiDenttity_OFF.Format(_T("SET IDENTITY_INSERT dbo.Tmp_%s OFF\r\nGO"),itr_src->first);
         iSetIdentityInsertOff = vecSqlScript.size();
         vecSqlScript.push_back(strSetiDenttity_OFF);
      }
#pragma endregion SET IDENTITY_INSERT dbo.Tmp_WLKuanshi_Detail_info OFF GO

      if (FALSE == bInsertValue)
      {
         if (iSetIdentityInsertOff > iSetIdentityInsertOn)
         {
            if (iSetIdentityInsertOff > 0)
            {
               vecSqlScript.erase(vecSqlScript.begin()+iSetIdentityInsertOff);
            }
            if (iSetIdentityInsertOn > 0)
            {
               vecSqlScript.erase(vecSqlScript.begin()+iSetIdentityInsertOn);
            }
         }
         else
         {
            if (iSetIdentityInsertOn > 0)
            {
               vecSqlScript.erase(vecSqlScript.begin()+iSetIdentityInsertOn);
            }
            if (iSetIdentityInsertOff > 0)
            {
               vecSqlScript.erase(vecSqlScript.begin()+iSetIdentityInsertOff);
            }
         }
      }

#pragma region DROP TABLE dbo.WLKuanshi_Detail_info  GO
      CString strDropTable;
      strDropTable.Format(_T("IF EXISTS(SELECT * FROM dbo.sysobjects where id = object_id(N'[dbo].[%s]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)\r\n\
                               DROP TABLE dbo.%s \r\nGO"),itr_src->first,itr_src->first);
      vecSqlScript.push_back(strDropTable);
#pragma endregion DROP TABLE dbo.WLKuanshi_Detail_info  GO

#pragma region rename table name
      CString strReName;
      strReName.Format(_T("EXECUTE sp_rename N'dbo.Tmp_%s', N'%s', 'OBJECT' "),itr_src->first,itr_src->first);
      vecSqlScript.push_back(strReName);
#pragma endregion rename table name

#pragma region ADD INDEX
      vector<CString> vecIndexName;
      for (int isrc = 0; isrc<(int)itr_src->second.size(); ++isrc)
      {
         if (!itr_src->second[isrc].strIndexName.IsEmpty())
         {
            auto itr_index = std::find(vecIndexName.begin(),vecIndexName.end(),itr_src->second[isrc].strIndexName);
            if (itr_index == vecIndexName.end())
            {
               CString strIndex=_T("");
               if (itr_src->second[isrc].strIndexName.Find(_T("PK__"))>=0 && itr_src->second[isrc].iPrimaryKey == 1)
               {
                  strIndex.Format(_T("ALTER TABLE dbo.%s ADD CONSTRAINT\r\n\
                                     %s PRIMARY KEY CLUSTERED\r\n(%s)\r\n\
                                     WITH( STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]\r\nGO"),
                                     itr_src->first,itr_src->second[isrc].strIndexName,itr_src->second[isrc].strColName);
               }
               else
               {
                  //找出具有相同索引的列
                  CString strField;
                  for (int itmp = 0;itmp<(int)itr_src->second.size(); ++itmp)
                  {
                     if (!itr_src->second[itmp].strIndexName.IsEmpty() && itr_src->second[itmp].strIndexName == itr_src->second[isrc].strIndexName)
                     {
                        strField += itr_src->second[itmp].strColName + _T(",");
                     }
                  }
                  strField.TrimRight(_T(","));
                  strIndex.Format(_T("CREATE NONCLUSTERED INDEX %s ON dbo.%s\r\n\
                                     (%s) \r\n\
                                     WITH( STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]\r\n\
                                     GO"),itr_src->second[isrc].strIndexName,itr_src->first,strField);
               }
               strIndex.Replace(_T("   "),_T(""));
               strIndex.Replace(_T("  "),_T(""));
               vecSqlScript.push_back(strIndex);
               vecIndexName.push_back(itr_src->second[isrc].strIndexName);
            }
         }
      }
#pragma endregion ADD INDEX

//#pragma region ADD COL
//      vecField.clear();
//      for (int isrc = 0; isrc<(int)itr_src->second.size(); ++isrc)
//      {
//         auto itr_field = std::find(vecField.begin(),vecField.end(),itr_src->second[isrc].strColName);
//         if (itr_field != vecField.end())
//         {
//            continue;
//         }
//         vecField.push_back(itr_src->second[isrc].strColName);
//         if (itr_src->second[isrc].bFlag == 0)
//         {
//            CString strSql;
//            if (db_attri::AllowModifySacle(itr_src->second[isrc].strColType))
//            {
//               strSql.Format(_T("ALTER TABLE dbo.%s ADD [%s] %s(%d,%d) %s\r\n GO"),
//                  itr_src->first,itr_src->second[isrc].strColName,itr_src->second[isrc].strColType,
//                  itr_src->second[isrc].iLen,itr_src->second[isrc].iScale,itr_src->second[isrc].bIsNullable?_T("NULL"):_T("NOT NULL"));
//            }
//            else if (db_attri::AllowModifyLength(itr_src->second[isrc].strColType))
//            {
//               strSql.Format(_T("ALTER TABLE dbo.%s ADD [%s] %s(%d) %s\r\n GO"),
//                  itr_src->first,itr_src->second[isrc].strColName,itr_src->second[isrc].strColType,
//                  itr_src->second[isrc].iLen,itr_src->second[isrc].bIsNullable?_T("NULL"):_T("NOT NULL"));
//            }
//            else
//            {
//               strSql.Format(_T("ALTER TABLE dbo.%s ADD [%s] %s %s\r\n GO"),
//                  itr_src->first,itr_src->second[isrc].strColName,itr_src->second[isrc].strColType,itr_src->second[isrc].bIsNullable?_T("NULL"):_T("NOT NULL"));
//            }
//            vecSqlScript.push_back(strSql);
//         }
//      }
//#pragma endregion ADD COL

#pragma region DROP COL
      auto itr_dst1 = db_attri_dst.find(itr_src->first);
      if (itr_dst1 != db_attri_dst.end())
      {
         vecField.clear();
         for (int idst = 0; idst < (int)itr_dst1->second.size();++idst)
         {
            auto itr_field = std::find(vecField.begin(),vecField.end(),itr_dst1->second[idst].strColName);
            if (itr_field != vecField.end())
            {
               continue;
            }
            vecField.push_back(itr_dst1->second[idst].strColName);
            if (itr_dst1->second[idst].bFlag == 0)
            {
               CString strSql;
               strSql.Format(_T("alter table %s drop column [%s]\r\nGO"),itr_src->first,itr_dst1->second[idst].strColName);
               vecSqlScript.push_back(strSql);
            }
         }
      }
#pragma endregion DROP COL

      vecSqlScript.push_back(SCRIPT_COMMIT);
      map_sql_script.insert(make_pair(itr_src->first,vecSqlScript));
   }

   return TRUE;
};

static void WriteSql2File(__in CString strFile,__in map<CString,vector<CString>> mapSql)
{
#define TCHARLEN (sizeof(TCHAR)) // 一个字符占的字节数
   CFile mFile;	
   try
   {
      WORD unicode = 0xFEFF;
      CString strEnter = _T("\r\n");
      if (mFile.Open (strFile,CFile::modeCreate|CFile::modeWrite|CFile::shareExclusive))
      {
         mFile.Write(&unicode,sizeof(unicode));
         for (auto itr_ = mapSql.begin(); itr_ != mapSql.end(); ++itr_)
         {
            for (int i=0; i<(int)itr_->second.size(); ++i)
            {
               mFile.Write(itr_->second[i],itr_->second[i].GetLength()*TCHARLEN);
               mFile.Write(strEnter,strEnter.GetLength()*TCHARLEN);
               mFile.Write(strEnter,strEnter.GetLength()*TCHARLEN);
            }
         }
         mFile.Close();
      }
   }
   catch( CException* e )
   {
      TCHAR szError[1024];
      CString strError = _T("");
      e->GetErrorMessage(szError,1024);
      strError.Format(_T("%s"),szError);
      AfxMessageBox(strFile+_T("  写文件出现问题：")+ strError);
   }//写_end
}
