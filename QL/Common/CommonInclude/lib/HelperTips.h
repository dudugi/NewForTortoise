#ifndef __KDSHELPER_H_H__
#define __KDSHELPER_H_H__


#define  KDSHELPERAPI  extern "C++" __declspec(dllimport)
/*******************************************************************************
  =========Version:1.7======��������:2014-12-15====�޸�����:2015-10-10=========
  Summary:����KDSHelper.ini�ļ�����д.help�ļ�

  1 KDSHelper.ini�ļ�˵����
  *��KDSHelper.ini�ļ�������DLL��һ��·���С�
  * ����������������Ӧ�ļ�ֵ˵����
  * FLAG=[0/1]	//0==��ʾֻ��ģʽС��ʿ    1==�༭ģʽС��ʿ
  * SHAREPATH=[�༭ʱ.help�ļ�����·�� eg:C:\\Test]	//��FLAG=1ʱ��SHAREPATH��Ϊ�ղ���Ч

  2 Ϊ��������KDS���������һ�ԣ����飺
  * strFileNameΪ����ֵ��
  * �� KDS-Cloud		//��������	���ݱ����ļ�Ϊ:KDS-Cloud.help
  * �� KDS-Process	//����		���ݱ����ļ�Ϊ:KDS-Design.help
  * �� KDS-Design	//���		���ݱ����ļ�Ϊ:KDS-Design.help
  * �� KDS-Pattern	//�ư�		���ݱ����ļ�Ϊ:KDS-Pattern.help

  3 ������ݶ��ֽ���Unicode��ֻ���޸���Ŀ���Լ��ɣ�

  4 2015-10-20 ����Զ��峬���ӣ����ʽ��[��Ƶ]test.exe[��]
  * ����򿪿ɴ���Ӧ���ļ���������ʽ����λ��ͬһ�У���ʽ��[��Ƶ]�����滻
  * [�ļ�]��[�ĵ�]��[ͼƬ]��[ͼ��]��[PPS]��[PPT]��[PDF]��[AVI]
  * ����ļ�����Լ����Ŀ¼��

  5 �����.help�ļ��ĺϲ���������˵��1�е�FLAGֵ��Ϊ-1����
  * �༭ģʽ�������ɾ������
  * ��Ҫɾ����ǰ�����������е���ʾ�����༭���ֵ��ΪKDS��Ȼ����Del��ť����
*******************************************************************************/

extern "C++" 
{
	//==============================KDSHelper_Show()=================================
	/*
	 *���ܣ�ͨ���ļ���strFileName��ͨ���Ի��򴰿���ʾ���������ӿؼ��Ĺ���˵��
	 *eg:KDSHelper_Show(_T("Sale"),m_nParentID,m_nSubID);
	 */
	KDSHELPERAPI void KDSHelper_Show(CString strFileName,CString strParentID,CString strSubID,CWnd *pWnd=AfxGetMainWnd());
	KDSHELPERAPI void KDSHelper_Show(CString strFileName,UINT nParentID,UINT nSubID,CWnd *pWnd=AfxGetMainWnd());

	//strID = strParentID_strSubID
	//ȷ��strIDֻ��һ�������ַ������»���"_" �������
	//eg:strID = _T("1234_5678")
	KDSHELPERAPI void KDSHelper_Show(CString strFileName,CString strID,CWnd *pWnd=AfxGetMainWnd());


	//================================KDSHelper_GetStep()==============================
	/*
	 *���ܣ����ء������������˵�������ַ���������ʾ�Ի��򴰿�
	 */
	KDSHELPERAPI CString KDSHelper_GetStep(CString strFileName,CString strParentID,CString strSubID);
	KDSHELPERAPI CString KDSHelper_GetStep(CString strFileName,UINT nParentID,UINT nSubID);
	KDSHELPERAPI CString KDSHelper_GetStep(CString strFileName,CString strID);//eg:strID = _T("1234_5678")


	//================================KDSHelper_Refresh()==============================
	/*
	 *���ܣ���������С��ʿ���Ի��򴰿ڴ��ڵ�����½���ˢ��
	 */
	KDSHELPERAPI void KDSHelper_Refresh(CString strFileName,CString strParentID,CString strSubID,CWnd *pWnd=AfxGetMainWnd());
	KDSHELPERAPI void KDSHelper_Refresh(CString strFileName,UINT nParentID,UINT nSubID,CWnd *pWnd=AfxGetMainWnd());
	KDSHELPERAPI void KDSHelper_Refresh(CString strFileName,CString strID,CWnd *pWnd=AfxGetMainWnd());//eg:strID = _T("1234_5678")
}
#endif