#pragma once


enum{
   en_Pro_Prepare = 0,//即将操作
   en_Pro_Running,//正在进行中的
};

//用户当前所需要操作的款式的相关信息
typedef struct S_PRO_USER_STYLE_INFO
{
   CString  m_strStyleNo;//款号
   int      m_nInfoType;//类型
}S_ProUserStyleInfo;





