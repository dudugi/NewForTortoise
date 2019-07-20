#pragma once
   //add by lida 2018/09/04

   //--һ���޸��ֶ�Ĭ��ֵ

   //alter table ���� drop constraint Լ������   ------˵����ɾ������ֶε�ԭ��Լ��

   //alter table ���� add constraint Լ������ DEFAULT Ĭ��ֵ for �ֶ����� -------˵�������һ������ֶε�Լ����ָ��Ĭ��ֵ

   //--�����޸��ֶ�����

   //alter table ���� rename column A to B

   //--�����޸��ֶ����ͣ�

   //alter table ���� alter column UnitPrice decimal(18, 4) not null 

   //--�ġ��޸������ֶΣ�

   //alter table ���� ADD �ֶ� ���� NOT NULL Default 0

   //--�塢ɾ����

   //alter table tableName drop column columnName

   //�ж��Ƿ����Լ������
   //IF  EXISTS (SELECT t.name AS tName,c.name AS cName,ep.* FROM sys.default_constraints AS ep
   //INNER JOIN sys.columns AS c ON ep.parent_object_id = c.object_id
   //INNER JOIN sys.tables AS t ON t.object_id = c.object_id AND ep.parent_column_id = c.column_id WHERE 
   //t.name='Table_1' and c.name = 'test3')

   //�ж��Ƿ�����ֶ�˵��
   //SELECT t.[name] AS ����,c.[name] AS �ֶ���,cast(ep.[value] 
   //as varchar(100)) AS [�ֶ�˵��]
   //FROM sys.tables AS t
   //INNER JOIN sys.columns 
   //AS c ON t.object_id = c.object_id
   //LEFT JOIN sys.extended_properties AS ep 
   //ON ep.major_id = c.object_id AND ep.minor_id = c.column_id WHERE ep.class =1 
   //AND t.name='Table_1'

#define SQL_SELECT  _T("SELECT\
   ����       = (case when a.colorder > 0 then d.name else ''end),\
   ��˵��     = case when a.colorder=1 then isnull(f.value,'') else '' end,\
   �ֶ����   = a.colorder,\
   �ֶ���     = a.name,\
   ��ʶ       = case when COLUMNPROPERTY( a.id,a.name,'IsIdentity')=1 then '1'else '' end,\
   ����       = case when exists(SELECT 1 FROM sysobjects where xtype='PK' and parent_obj=a.id and name in (\
            SELECT name FROM sysindexes WHERE indid in( SELECT indid FROM sysindexkeys WHERE id = a.id AND colid=a.colid))) then '1' else '' end,\
   ����       = b.name,\
   ռ���ֽ��� = a.length,\
   ����       = COLUMNPROPERTY(a.id,a.name,'PRECISION'),\
   С��λ��   = isnull(COLUMNPROPERTY(a.id,a.name,'Scale'),0),\
   �����     = case when a.isnullable=1 then '1'else '' end,\
   Ĭ��ֵ     = isnull(e.text,''),\
   �ֶ�˵��   = isnull(g.[value],''),\
   ��������	=isnull(i.name,'')\
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

#define FIELD_TABLE_NAME      _T("����")
#define FIELD_TABLE_DESC      _T("��˵��")
#define FIELD_COL_ORDER       _T("�ֶ����")
#define FIELD_COL_NAME        _T("�ֶ���")
#define FIELD_PRI_KEY         _T("����")
#define FIELD_IDENTITY        _T("��ʶ")
#define FIELD_COL_TYPE        _T("����")
#define FIELD_COL_BYTES       _T("ռ���ֽ���")
#define FIELD_COL_LENGTH      _T("����")
#define FIELD_COL_SACLE       _T("С��λ��")
#define FIELD_COL_NULLABLE    _T("�����")
#define FIELD_DEFAULT_VALUE   _T("Ĭ��ֵ")
#define FIELD_COL_DESC        _T("�ֶ�˵��")
#define FIELD_INDEX_NAME      _T("��������")

#pragma region �ֶ�����
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

#pragma endregion �ֶ�����
                      
#pragma region ���ݿ�������Ϣ
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
#pragma endregion ���ݿ�������Ϣ

#pragma region ��ṹ��Ϣ
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

   //�޸ĳ���
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

   //�޸ľ���
   static BOOL AllowModifySacle(__in CString strType)
   {
      if(strType == g_type[t_decimal] || strType == g_type[t_numeric])
      {
         return TRUE;
      }
      return FALSE;
   };

   //�ж��Ƿ�����������
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

   //�ֶ���ȫ���֣������ֵ��ֶ���Ҫ����[]���ţ�����ᱨ��
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

   //�����������ֶ�����
   static BOOL IsIdentityType(__in CString strType,__in int iScale)
   {
      //��ʶ�� 'ID' ���������ͱ����� int��bigint��smallint��tinyint �� decimal��������С��λ��Ϊ 0 �� numeric �������ͣ�����Լ��Ϊ����Ϊ Null��
      if (strType == g_type[t_int] || strType == g_type[t_bigint] || strType == g_type[t_smallint]
      || strType == g_type[t_tinyint] || strType == g_type[t_decimal] || (strType == g_type[t_numeric] && iScale == 0))
      {
         return TRUE;
      }
      return FALSE;
   };

   int         id;                  //id
   CString     strTableName;           //����
   CString     strTableDesc;        //��˵��
   int         iColOrder;          //�ֶ����
   CString     strColName;          //�ֶ���
   int         iIdentity;          //��ʶ
   int         iPrimaryKey;        //����
   CString     strColType;          //����
   int         iBytes;            //ռ���ֽ���
   int         iLen;               //����
   int         iScale;             //С��λ��
   BOOL        bIsNullable;         //�����
   CString     strDefaultValue;     //Ĭ��ֵ
   CString     strColDesc;          //�ֶ�˵��
   CString     strIndexName;        //��������
   BOOL        bFlag;               //������� src:0=add,dst:0=del
   BOOL        bFullNumberColName;  //ȫ���ֵ��ֶ���
   BOOL        bDiff;               //�Ƿ���ڲ��죬�����ڲ���ı������ɽű�
}tag_db_attri;

#pragma endregion ��ṹ��Ϣ

typedef vector<tag_db_attri> vec_db_attri;
typedef map<CString,vec_db_attri> map_db_attri;
typedef map<CString,vector<CString>>   mapSqlScript;      //�ű�

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
      //���� �ֶ�������ͬ���޷��Ƚ�
      return FALSE;
   }
   //��ʶ
   if (tag_src.iIdentity != tag_dst.iIdentity)  
   {
      return TRUE;
   }
   //����
   if (tag_src.iPrimaryKey != tag_dst.iPrimaryKey)
   {
      return TRUE;
   }
   //����
   if (tag_src.strColType != tag_dst.strColType)
   {
      return TRUE;
   }
   //����
   if (tag_src.iLen != tag_dst.iLen)
   {
      return TRUE;
   }
   //С��λ��
   if (tag_src.iScale != tag_dst.iScale)
   {
      return TRUE;
   }
   //�����
   if (tag_src.bIsNullable != tag_dst.bIsNullable)
   {
      return TRUE;
   }
   //Ĭ��ֵ
   if (tag_src.strDefaultValue != tag_dst.strDefaultValue)
   {
      return TRUE;
   }
   //�ֶ�˵��
   if (tag_src.strColDesc != tag_dst.strColDesc)
   {
      return TRUE;
   }
   //����
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
         return FALSE;  //��һ�����޷��ȶ�
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
         return FALSE;  //��һ�����޷��ȶ�
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


//�����޸�Ĭ��ֵsql
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

//�����޸��ֶ�����sql
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
#pragma region �ҳ�������ɾ���ֶΣ������
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
#pragma endregion �ҳ�������ɾ���ֶΣ������

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
            continue;   //������������ֶ�
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
                  //�ҳ�������ͬ��������
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
#define TCHARLEN (sizeof(TCHAR)) // һ���ַ�ռ���ֽ���
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
      AfxMessageBox(strFile+_T("  д�ļ��������⣺")+ strError);
   }//д_end
}
