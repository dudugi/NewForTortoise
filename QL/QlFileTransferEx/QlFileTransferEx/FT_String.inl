#pragma once

//文件路径相关的字符串
#define STR_PATH_CONFIG          _T("\\用户文件\\订单")//配置文件所在的文件夹相关信息
#define STR_PATH_CONFIG_SETTING  _T("\\用户文件\\订单\\FileTransSetting.xml")//默认数据端口对应的信息
#define STR_PATH_CONFIG_PATH     _T("\\用户文件\\订单\\FileTransPathSetting.xml")//默认数据端口对应的信息
#define STR_PATH_CONFIG_PATH_DEFAULT     _T("\\用户文件\\订单\\FileTransPathSetting.default")//默认数据端口对应的信息
#define STR_PATH_INI_CONFIGSVR   _T("\\运行库\\订单模块\\ConfigSvr.ini")
#define STR_PATH_INI_FILEMGN     _T("\\用户文件\\订单\\KDSFileMgn.ini")


//默认端口map中key的值
#define STR_MAP_KEY_PORT_FTP     _T("FTP_PORT")
#define STR_MAP_KEY_PORT_HTTP    _T("HTTP_PORT")
//默认端口map中value的默认值
#define STR_MAP_VALUE_PORT_DB    _T("1433")//该值为固定值 不再调整
#define STR_MAP_VALUE_PORT_FTP   _T("21")
#define STR_MAP_VALUE_PORT_HTTP  _T("8088")

//资源中类型对应的字符串
#define STR_RESOURCE_TYPE_XML    _T("XML")


//INI文件中对应的字符串
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


//默认端口配置xml中相关的key值
/*结构如下
<FileTransSetting>
    <Port>
        <DBPort>
            <Default>1433</Default>
            <Description>数据库端口默认值</Description>
        </DBPort>
        <FilePort>
            <FTP>
                <Default>21</Default>
                <Description>FTP文件端口的默认值</Description>
            </FTP>
            <HTTP>
                <Default>8080</Default>
                <Description>HTTP模式的文件端口默认值</Description>
            </HTTP>
        </FilePort>
    </Port>
</FileTransSetting>
*/
#define XML_PARAM_DEFAULTPORT_SETTTING_ROOT                 "FileTransSetting"      //根节点
#define XML_PARAM_DEFAULTPORT_SETTTING_PORT                 "Port"                  //端口节点
#define XML_PARAM_DEFAULTPORT_SETTTING_FILEPORT             "FilePort"              //端口节点下的文件端口
#define XML_PARAM_DEFAULTPORT_SETTTING_PORT_FTP             "FTP"                   //文件端口节点下的FTP模式端口
#define XML_PARAM_DEFAULTPORT_SETTTING_PORT_HTTP            "HTTP"                  //文件端口节点下的HTTP模式端口
#define XML_PARAM_DEFAULTPORT_SETTTING_PORT_VALUE_DEFAULT   "Default"               //配置下的默认数值 

//路径配置的相关参数

#define XML_PARAM_PATH_SETTTING_ROOT                        "Root"                  //根节点
#define XML_PARAM_PATH_SETTTING_SUBITEM                     "SubItem"               //子项
#define XML_PARAM_PATH_SETTTING_KEY                         "Key"                   //key值
#define XML_PARAM_PATH_SETTTING_PATH                        "Path"                  //配置的路径
#define XML_PARAM_PATH_SETTTING_UPLOADZIP                   "UploadZip"             //上传时是否压缩的参数
#define XML_PARAM_PATH_SETTTING_DOWNDelZIP                  "DownDelZip"            //下载的文件解压后是否删除下载的临时文件
#define XML_PARAM_PATH_SETTTING_UNZIPFAILRENAME             "UnZipFailRename"      //解压失败的话还原为原文件名
