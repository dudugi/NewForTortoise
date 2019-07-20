#pragma once

//�ļ�·����ص��ַ���
#define STR_PATH_CONFIG          _T("\\�û��ļ�\\����")//�����ļ����ڵ��ļ��������Ϣ
#define STR_PATH_CONFIG_SETTING  _T("\\�û��ļ�\\����\\FileTransSetting.xml")//Ĭ�����ݶ˿ڶ�Ӧ����Ϣ
#define STR_PATH_CONFIG_PATH     _T("\\�û��ļ�\\����\\FileTransPathSetting.xml")//Ĭ�����ݶ˿ڶ�Ӧ����Ϣ
#define STR_PATH_CONFIG_PATH_DEFAULT     _T("\\�û��ļ�\\����\\FileTransPathSetting.default")//Ĭ�����ݶ˿ڶ�Ӧ����Ϣ
#define STR_PATH_INI_CONFIGSVR   _T("\\���п�\\����ģ��\\ConfigSvr.ini")
#define STR_PATH_INI_FILEMGN     _T("\\�û��ļ�\\����\\KDSFileMgn.ini")


//Ĭ�϶˿�map��key��ֵ
#define STR_MAP_KEY_PORT_FTP     _T("FTP_PORT")
#define STR_MAP_KEY_PORT_HTTP    _T("HTTP_PORT")
//Ĭ�϶˿�map��value��Ĭ��ֵ
#define STR_MAP_VALUE_PORT_DB    _T("1433")//��ֵΪ�̶�ֵ ���ٵ���
#define STR_MAP_VALUE_PORT_FTP   _T("21")
#define STR_MAP_VALUE_PORT_HTTP  _T("8088")

//��Դ�����Ͷ�Ӧ���ַ���
#define STR_RESOURCE_TYPE_XML    _T("XML")


//INI�ļ��ж�Ӧ���ַ���
#define STR_INI_CONFIGSVR_APP_SETTING     _T("Setting")
#define STR_INI_CONFIGSVR_APP_SQLSVR      _T("SQLSVR")

#define STR_INI_CONFIGSVR_KEY_APPLY       _T("LG_CHK_APPLY")
#define STR_INI_CONFIGSVR_KEY_SVR         _T("SVR")
#define STR_INI_CONFIGSVR_KEY_SVR_LOCAL   _T("SVRLOCAL")
#define STR_INI_CONFIGSVR_KEY_HTTPMODE    _T("HTTPMODE")
#define STR_INI_CONFIGSVR_KEY_FILEPORT    _T("FILEPORT")
#define STR_INI_CONFIGSVR_KEY_DB          _T("DB")
#define STR_INI_CONFIGSVR_KEY_DBUID       _T("UID")
#define STR_INI_CONFIGSVR_KEY_DBPWD       _T("PWD")

#define STR_INI_FILEMGN_APP_ACT           _T("ACT")
#define STR_INI_FILEMGN_APP_CUSACT        _T("CUSACT")

#define STR_INI_FILEMGN_KEY_USERID        _T("USERID")
#define STR_INI_FILEMGN_KEY_USERPWD       _T("USERPWD")


#define STR_INI_VALUE_EMPTY               _T("")
#define STR_INI_VALUE_TRUE                _T("TRUE")
#define STR_INI_VALUE_FALSE               _T("FALSE")


//Ĭ�϶˿�����xml����ص�keyֵ
/*�ṹ����
<FileTransSetting>
    <Port>
        <DBPort>
            <Default>1433</Default>
            <Description>���ݿ�˿�Ĭ��ֵ</Description>
        </DBPort>
        <FilePort>
            <FTP>
                <Default>21</Default>
                <Description>FTP�ļ��˿ڵ�Ĭ��ֵ</Description>
            </FTP>
            <HTTP>
                <Default>8080</Default>
                <Description>HTTPģʽ���ļ��˿�Ĭ��ֵ</Description>
            </HTTP>
        </FilePort>
    </Port>
</FileTransSetting>
*/
#define XML_PARAM_DEFAULTPORT_SETTTING_ROOT                 "FileTransSetting"      //���ڵ�
#define XML_PARAM_DEFAULTPORT_SETTTING_PORT                 "Port"                  //�˿ڽڵ�
#define XML_PARAM_DEFAULTPORT_SETTTING_FILEPORT             "FilePort"              //�˿ڽڵ��µ��ļ��˿�
#define XML_PARAM_DEFAULTPORT_SETTTING_PORT_FTP             "FTP"                   //�ļ��˿ڽڵ��µ�FTPģʽ�˿�
#define XML_PARAM_DEFAULTPORT_SETTTING_PORT_HTTP            "HTTP"                  //�ļ��˿ڽڵ��µ�HTTPģʽ�˿�
#define XML_PARAM_DEFAULTPORT_SETTTING_PORT_VALUE_DEFAULT   "Default"               //�����µ�Ĭ����ֵ 

//·�����õ���ز���

#define XML_PARAM_PATH_SETTTING_ROOT                        "Root"                  //���ڵ�
#define XML_PARAM_PATH_SETTTING_SUBITEM                     "SubItem"               //����
#define XML_PARAM_PATH_SETTTING_KEY                         "Key"                   //keyֵ
#define XML_PARAM_PATH_SETTTING_PATH                        "Path"                  //���õ�·��
#define XML_PARAM_PATH_SETTTING_UPLOADZIP                   "UploadZip"             //�ϴ�ʱ�Ƿ�ѹ���Ĳ���
#define XML_PARAM_PATH_SETTTING_DOWNDelZIP                  "DownDelZip"            //���ص��ļ���ѹ���Ƿ�ɾ�����ص���ʱ�ļ�
#define XML_PARAM_PATH_SETTTING_UNZIPFAILRENAME             "UnZipFailRename"      //��ѹʧ�ܵĻ���ԭΪԭ�ļ���
