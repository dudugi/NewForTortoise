#pragma once

#include "CtrlInfo.h"
/************************************************************************
 * �������ڣ�2015-11-02     ���ߣ�zhangtao
 * �Ի����м���
 * ���ࣺCDialogEx
 * Ŀ�ģ������ڴ���CDialogExMid����Ķ���
 ************************************************************************/


#ifdef USING_LIB_BCGP
#include <BCGCBProInc.h>	// BCGControlBar Pro
#else
//...
#endif // USING_LIB_BCGP
using namespace std;
#include <map>
#include <deque>


#ifdef USING_LIB_BCGP
class CDialogExMid : public CBCGPDialog
#else
class CDialogExMid : public CDialogEx
#endif // USING_LIB_BCGP
{
public:
	CDialogExMid(UINT nIDD,CWnd* pParent = NULL);	// ��׼���캯��
	~CDialogExMid();
	UINT m_nIDD;// �Ի���ID����

protected:
	BOOL m_bMoveParent;//2017/05/23 zhangt �Ƿ��ƶ�������
   int m_nDlgFlag;//2019-2-21 wangzl �Ի����־ ��������ͬ������ԴID���ǲ�ͬ�ĶԻ���Ĭ�ϱ�־Ϊ0

   //���������ض��� yangjr 2019/04/09
   CString        m_LanTableName;         //��Ӧ����洢�������ʱ�ı���
   bool           m_flagUsed;          //�Ի��򱻳�ʼ����
   bool           m_isAllwaysChangeWhenInit;
   int            m_language;          // ����   
   bool           m_isUINeedTranslate;   //�Ƿ���Ҫ���봦��
   std::map<UINT,UINT> m_unLanguageCTRLID;  //����Ҫ�����ID  
   BOOL                   m_bTranslateDlgTitle;  //�Ƿ��Զ�����Ի������
protected:
	DECLARE_MESSAGE_MAP()
	/*
	 * @brief	��ֹ�ڶԻ����а�Enter���Ի�����ʧ
	 * @author	
	 */
	afx_msg LRESULT OnGetDefID(WPARAM wParam,LPARAM lParam); 

	/*
	 * @brief	��Ӧ�ͻ���������������Ϣ
	 * @author	
	 */
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	/*
	 * @brief	��Ӧ�ǿͻ���������������Ϣ
	 * @author	
	 */
	afx_msg void OnNcLButtonUp(UINT nHitTest, CPoint point);

   //��ȡ��Ӧ�ؼ�id�Ŀؼ������ַ��� yangjr 2017-12-14
   CString GetControlType(UINT nCtrlID);

   //���ļ��л�ȡ����ˢ�¿ؼ�ֵ yangjr 2017-12-14
   void RefreshDefValue(int index);

   afx_msg void OnDestroy();
   
   void ClearCtrlInfo();

   void ResizeCtrl(const CRect rt);

   void UpdateControlsPermission();

private:
   std::map<int/*row*/,map<int/*index*/,ctrl_info*>>      m_map_ctrl_info;
   std::map<UINT,UINT> m_mapNewComboTranslation;	//comboBox������������Ҫ�µķ��뷽ʽ�Ŀؼ�ID
//����λ�ü������ yangjr 2018/5/22
private:  
   //��¼����λ����ر���	by yangjr 2018/05/22
   int		m_nWndPosX;					   //�Ի��򴰿�Xλ��
   int		m_nWndPosY;					   //�Ի��򴰿�Yλ��
   bool		m_bIsRecordWndPos;			//�Ƿ��¼�Ի��򴰿�λ��
   CString	m_strRecordWndPosCfgPath;	//��¼�Ի��򴰿�λ�õ������ļ�·��
   bool		m_bCenterWnd;				   //�Ƿ��һ�δ򿪴���ʱ��������ʾ
   bool		m_bIsRecordWndSize;			//�Ƿ��¼���ڴ�С
   int		m_nWndCx;						//��¼���ڴ�С
   int		m_nWndCy;						//��¼���ڴ�С 
   bool		m_bRecordMinimizeState;		//�Ƿ��¼��С��״̬  
   bool		m_bRecordMaximizeState;		//�Ƿ��¼���״̬	
   DWORD		m_dwTickCount;					//��¼��ʼ����ʱ���
   int		m_nDefaultWndCx;				//Ĭ�ϴ��ڿ��
   int		m_nDefaultWndCy;				//Ĭ�ϴ��ڸ߶�

   void InitWndPosRecordVariable();	//��ʼ������λ�ü�¼���ܵ���ر���
   bool ReadWindowPosCfg();			//��ȡ����λ����Ϣ����
   void SaveWindowPosCfg();			//���洰��λ����Ϣ����
   void SetWindowPosByRecord();		//���ݼ�¼��Ϣ���ô���λ��
   void GetWindowPosRecord();			//��ȡ����λ����Ϣ����¼  
   void SaveWindowMaximizeState();	//��¼�������״̬
   bool ReadWindowMaximizeState();	//��ȡ�������״̬

   void SaveWindowMinimizeState();	//��¼������С��״̬
   bool ReadWindowMinimizeState();	//��ȡ������С��״̬

   //��õ�ǰ�Ӵ�������CDialogExMid���ڵ�����Ǹ����ڣ�˳�����м����д��ڵ�IDD
   static CDialogExMid *GetTopParentWindowAndChildIDDs(CDialogExMid *pCurDlg, std::deque<int> *pdeqChildIDDs);
   CDialogExMid *GetTopParentWindowAndChildIDDs(std::deque<int> *pdeqChildIDDs);
   static CDialogExMid const* GetChildWindowByIDDs(const CDialogExMid *pWndParent, const std::deque<int> &deqIDDs);
   static CDialogExMid *GetChildWindowByIDD(const CDialogExMid *pWndParent, int nIDD);
protected:
   //�������ڼ�¼���ؽӿ�
   void EnableRecordWndPos(CString strRecordCfgPath, bool bRecord = true);
   //��������������ʾ�ӿڣ�����������Ҵ���Ϊ��һ�δ򿪣��򴰿�������ʾ����
   void EnableInitCenterWnd(bool bCenterWnd = true);

   void EnableRecordWndSize(bool bRecordSize = true);
   //����Ĭ�ϴ��ڴ�С		
   void SetDefaultWndSize(int nWidth, int nHeight);   
   //������¼��С��״̬ �Ľӿ�
   void EnableRecordMinimizeState(bool bRecordMinimizeState = true);
   //������¼���״̬
   void EnableRecordMaximizeState(bool bRecordMaximizeState = true);

   void AddNewTranslationComboBoxID(UINT combID);
   void AddUnLanguageCTRLID(UINT combID);//����Ҫ��ȡ���ݿ��л�������ԵĿؼ�ID,һ����combox yangjr 2019/04/09
public:
	virtual BOOL OnInitDialog();
   virtual void OnCancel();
   virtual void OnClose();
   virtual void OnOK();
   virtual BOOL ShowWindow(int nCmdShow);

   int GetDlgFlag(){return m_nDlgFlag;}
	/*
	 * @brief	���� ��������Ӧ����һ��˵�
	 * @author	
	 */
	virtual ULONG GetGestureStatus(CPoint ptTouch){return 0;}

	/*
	 * @brief	������Ϣ
	 * @author	
	 */
	virtual BOOL PreTranslateMessage(MSG* pMsg);

#ifdef USING_LIB_BCGP
   virtual void SetActiveMenu (CBCGPPopupMenu* pMenu);
#else
   void SetActiveMenu(CMFCPopupMenu* pMenu);
#endif //USING_LIB_BCGP
   afx_msg void OnInitMenu(CMenu* pMenu);
	/*
	 * @brief	����MenuPopup�˵�״̬
	 * @author	
	 */
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);

   afx_msg void OnSize(UINT nType, int cx, int cy);

   /*
	 * @brief	ͨ����ǰ�Ի���ؼ�ID��ȡ�ؼ���Ĭ��ֵֵ
	 * ��ǰ֧��CEdit,CComboBox,CButton(CheckBox,RadioButton),CRichEditCtrl
	 * @author	2017/12/13 zhangt
	 * @note	1:CheckBox��RadioButton ��ȡֵ1��ʾѡ�� 0��ʾδѡ��
	 */
	CString GetDefValueByID(UINT nCtrlID);

	/*
	 * @brief	ͨ����ǰ�Ի���ؼ�ID��ע�᡿�ؼ���Ĭ��ֵֵ
	 * ��ǰ֧��CEdit,CComboBox,CButton(CheckBox,RadioButton),CRichEditCtrl
	 * @author	2017/12/13 zhangt
	 * @note	1:CheckBox��RadioButton ��ȡֵ1��ʾѡ�� 0��ʾδѡ��
	 */
	BOOL RegDefValueByID(UINT nCtrlID,CString strDefText);

   BOOL AddCtrlInfo(ctrl_info* p_ctl);

   //************************************
   // Parameter: UINT ID
   // Parameter: int irow     �ؼ��ڵڼ���
   // Parameter: int index    ��ǰ�пؼ���ʾ��˳��
   // Parameter: int width
   // Parameter: int height
   // Parameter: int ideltx      ���Ҽ��
   // Parameter: int idelt_y     ���¼��
   //************************************
   BOOL AddCtrlInfo(HWND hwnd,int irow,int index,int width,int height,int ideltx = 0,int idelty = 0,float iXBeilv=1,float iYBeilv=1);
   //************************************
   // ������˳���Զ�����
   // Parameter: UINT ID
   // Parameter: int irow     �ؼ��ڵڼ���
   // Parameter: int width
   // Parameter: int height
   // Parameter: int ideltx      ���Ҽ��
   // Parameter: int idelt_y     ���¼��
   //************************************
   BOOL AddCtrlInfo_auto_sort(HWND hwnd,int irow,int width,int height,int ideltx = 0,int idelty = 0,float iXBeilv=1,float iYBeilv=1);

   //************************************
   // Method:    ReplaceCtrlInfo
   // Parameter: int irow_old       �ɵ��к�     --��������
   // Parameter: int index_old      �ɵ�index    --��������
   // Parameter: HWND hwnd          �µĴ��ھ��
   // Parameter: int width
   // Parameter: int height
   // Parameter: int ideltx
   // Parameter: int idelty
   //************************************
   BOOL ReplaceCtrlInfo(int irow_old,int index_old,HWND hwnd_new,int width_new,int height_new,int ideltx_new = 0,int idelty_new = 0,float iXBeilv=1,float iYBeilv=1);

   //************************************
   // Method:    ReplaceCtrlInfo
   // Parameter: HWND hwnd_old      �ɴ��ھ��
   // Parameter: HWND hwnd_new      �´��ھ��
   // Parameter: int width_new      -1000��ʾʹ�þɵĳߴ� 
   // Parameter: int height_new     -1000��ʾʹ�þɵĳߴ� 
   // Parameter: int ideltx_new     -1000��ʾʹ�þɵĳߴ� 
   // Parameter: int idelty_new     -1000��ʾʹ�þɵĳߴ� 
   //************************************
   BOOL ReplaceCtrlInfo(HWND hwnd_old,HWND hwnd_new,int width_new = ctrl_info::iUseOldSize,int height_new =ctrl_info::iUseOldSize
      ,int ideltx_new = ctrl_info::iUseOldSize,int idelty_new = ctrl_info::iUseOldSize,float iXBeilv=1,float iYBeilv=1);
#ifdef USING_TAB_MANAGER
   //ͨ��XML�����ļ��ƶ�����
   static BOOL LeaveFocusByXML(WPARAM wParamKey, CWnd *pControl);
#endif /*USING_TAB_MANAGER*/

   virtual BOOL OnLanguageChange();  //���Ա仯ʱˢ�½�����ʾ   
   void ChangeLanguageWhenInit();//���˺��������ã���ÿ��OnInitDialogʱ�������ٴε���OnLanguageChange�ӿڣ���ȡ��������

    CString m_DlgName;//�Ի����ʶ 
};