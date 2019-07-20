#ifndef __KDSHELPER_H_H__
#define __KDSHELPER_H_H__


#define  KDSHELPERAPI  extern "C++" __declspec(dllimport)
/*******************************************************************************
  =========Version:1.7======创建日期:2014-12-15====修改日期:2015-10-10=========
  Summary:关联KDSHelper.ini文件及读写.help文件

  1 KDSHelper.ini文件说明：
  *【KDSHelper.ini文件存放与此DLL在一个路径中】
  * 对以下两个键及对应的键值说明：
  * FLAG=[0/1]	//0==显示只读模式小贴士    1==编辑模式小贴士
  * SHAREPATH=[编辑时.help文件共享路径 eg:C:\\Test]	//当FLAG=1时且SHAREPATH不为空才有效

  2 为了与我们KDS软件保持整一性，建议：
  * strFileName为下列值：
  * ① KDS-Cloud		//订单管理	数据保存文件为:KDS-Cloud.help
  * ② KDS-Process	//工艺		数据保存文件为:KDS-Design.help
  * ③ KDS-Design	//设计		数据保存文件为:KDS-Design.help
  * ④ KDS-Pattern	//制版		数据保存文件为:KDS-Pattern.help

  3 代码兼容多字节与Unicode（只需修改项目属性即可）

  4 2015-10-20 添加自定义超链接，如格式：[视频]test.exe[打开]
  * 点击打开可打开相应的文件，上述格式必须位于同一行，格式中[视频]可以替换
  * [文件]或[文档]或[图片]或[图像]或[PPS]或[PPT]或[PDF]或[AVI]
  * 相关文件放在约定的目录中

  5 添加了.help文件的合并操作，将说明1中的FLAG值改为-1即可
  * 编辑模式下添加了删除操作
  * 若要删除当前父窗口下所有的提示，将编辑框的值改为KDS，然后点击Del按钮即可
*******************************************************************************/

extern "C++" 
{
	//==============================KDSHelper_Show()=================================
	/*
	 *功能：通过文件名strFileName，通过对话框窗口显示父窗口下子控件的功能说明
	 *eg:KDSHelper_Show(_T("Sale"),m_nParentID,m_nSubID);
	 */
	KDSHELPERAPI void KDSHelper_Show(CString strFileName,CString strParentID,CString strSubID,CWnd *pWnd=AfxGetMainWnd());
	KDSHELPERAPI void KDSHelper_Show(CString strFileName,UINT nParentID,UINT nSubID,CWnd *pWnd=AfxGetMainWnd());

	//strID = strParentID_strSubID
	//确保strID只存一个连接字符串的下划线"_" 否则出错
	//eg:strID = _T("1234_5678")
	KDSHELPERAPI void KDSHelper_Show(CString strFileName,CString strID,CWnd *pWnd=AfxGetMainWnd());


	//================================KDSHelper_GetStep()==============================
	/*
	 *功能：返回“具体操作步骤说明”的字符串，不显示对话框窗口
	 */
	KDSHELPERAPI CString KDSHelper_GetStep(CString strFileName,CString strParentID,CString strSubID);
	KDSHELPERAPI CString KDSHelper_GetStep(CString strFileName,UINT nParentID,UINT nSubID);
	KDSHELPERAPI CString KDSHelper_GetStep(CString strFileName,CString strID);//eg:strID = _T("1234_5678")


	//================================KDSHelper_Refresh()==============================
	/*
	 *功能：当“帮助小贴士”对话框窗口存在的情况下进行刷新
	 */
	KDSHELPERAPI void KDSHelper_Refresh(CString strFileName,CString strParentID,CString strSubID,CWnd *pWnd=AfxGetMainWnd());
	KDSHELPERAPI void KDSHelper_Refresh(CString strFileName,UINT nParentID,UINT nSubID,CWnd *pWnd=AfxGetMainWnd());
	KDSHELPERAPI void KDSHelper_Refresh(CString strFileName,CString strID,CWnd *pWnd=AfxGetMainWnd());//eg:strID = _T("1234_5678")
}
#endif