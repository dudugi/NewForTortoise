
// StaffModifyDlg.cpp : ʵ���ļ�
//

#include "StdAfx.h"
#include "CustomMgnSys.h"
#include "DlgStaffModify.h"
#include "CommonAPI.h"
#include "Base64Code.h"
#include "DBUserInfo.h"
#include "CDBFieldDefine.h"
#include "WorkLog/WorkLog.h"


// CStaffModifyDlg �Ի���

IMPLEMENT_DYNAMIC(CDlgStaffModify, CBCGPDialog)

CDlgStaffModify::CDlgStaffModify(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CDlgStaffModify::IDD, pParent)
{
	m_wpData = STAFF_TYPE_ADD;
	m_pObjPerson = NULL;

	m_bShow = TRUE;
   m_strDlgTitle = _T("�û�����");
}

CDlgStaffModify::~CDlgStaffModify()
{

}

void CDlgStaffModify::DoDataExchange(CDataExchange* pDX)
{
   CBCGPDialog::DoDataExchange(pDX);   
}


BEGIN_MESSAGE_MAP(CDlgStaffModify, CBCGPDialog)
	ON_BN_CLICKED(IDOK, &CDlgStaffModify::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlgStaffModify::OnBnClickedCancel)
	ON_WM_SIZE()	
END_MESSAGE_MAP()


// CStaffModifyDlg ��Ϣ�������


BOOL CDlgStaffModify::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();
	RefreshData();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CDlgStaffModify::ResetCtrl()
{
}

void CDlgStaffModify::RefreshData()
{
	CComboBox *pCboState = (CComboBox *)GetDlgItem(IDC_CBO_STATE);	
	pCboState->ResetContent();
	pCboState->SetItemHeight(0,20);
	pCboState->AddString(_T("����"));
	pCboState->SetItemHeight(1,20);
	pCboState->AddString(_T("ע��"));
   
	//ʱ��ռ��ʽ��
	CDateTimeCtrl *pDtCtrlReg = (CDateTimeCtrl *)GetDlgItem(IDC_DATEPK_REG_MODIFY);
	pDtCtrlReg->SetFormat(_T("yyyy-MM-dd"));

	CDateTimeCtrl *pDtCtrLastLoad = (CDateTimeCtrl *)GetDlgItem(IDC_DATEPK_LASTLOAD);
	pDtCtrLastLoad->SetFormat(_T("yyyy-MM-dd HH:mm:ss"));
   
	CEdit *pEtAct = (CEdit *)GetDlgItem(IDC_ET_ACT);
	pEtAct->LimitText(20);

	CEdit *pEtPwd = (CEdit *)GetDlgItem(IDC_ET_PWD);
	pEtPwd->LimitText(20);

	CEdit *pEtName = (CEdit *)GetDlgItem(IDC_ET_NAME);
	pEtName->LimitText(20);
	ResetCtrl();
	if (STAFF_TYPE_ADD == m_wpData)//���
	{
		SetWindowText(_T("����û�"));

		pEtPwd->SetWindowText(_T("666666"));   

		GetDlgItem(IDC_STATIC_LASTLOAD)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_DATEPK_LASTLOAD)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STATIC_STATE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CBO_STATE)->ShowWindow(SW_HIDE);

	}
	else if (STAFF_TYPE_MODIFY == m_wpData)//�޸�
	{
		SetWindowText(_T("�޸��û�"));

		if (m_pObjPerson != NULL)
		{
			pEtAct->SetReadOnly(TRUE);
			pEtAct->SetWindowText(m_pObjPerson->m_strUserID);	
			
			//��Ӳ�����ص����� end wzl
			CBase64Code Base64Code;
			pEtPwd->SetWindowText(Base64Code.base64Decode(m_pObjPerson->m_strUserPwd));

			pDtCtrlReg->SetTime(m_pObjPerson->m_tUserDate);

			pEtName->SetWindowText(m_pObjPerson->m_strUserName);

			pDtCtrLastLoad->EnableWindow(FALSE);
			pDtCtrLastLoad->SetTime(m_pObjPerson->m_tLastLoadTime);		
         			
			if (m_pObjPerson->m_nUserState == 1)
			{
				pCboState->SetCurSel(1);				
			}
			else
			{
				pCboState->SetCurSel(0);				
			}	
      }
   }

}


void CDlgStaffModify::OnBnClickedOk()
{
	CString nameStr;
	CEdit * pEtName = (CEdit *)GetDlgItem(IDC_ET_NAME);
	pEtName->GetWindowText(nameStr);
	nameStr.Trim();
	if (nameStr.IsEmpty())
	{
		theApp.OnShowDesktopAlert(_T("Ա����������Ϊ�գ�"),TIP_COLOR_WARNING,TIP_TIME_DELAY);
		return;
	}

	CBase64Code Base64Code;
	if (STAFF_TYPE_ADD == m_wpData)
	{
		CString strAct = _T("");
		CString strPwd = _T("");
		GetDlgItemText(IDC_ET_ACT,strAct);
		strAct.Trim();
		if (strAct.IsEmpty())
		{
			theApp.OnShowDesktopAlert(_T("�û�������Ϊ�գ�"),TIP_COLOR_WARNING,TIP_TIME_DELAY);
			return;
		}
		if (0 == strAct.CompareNoCase(_T("admin")))
		{
			theApp.OnShowDesktopAlert(_T("�û���������admin��ͬ�����ƣ�"),TIP_COLOR_WARNING,TIP_TIME_DELAY);
			return;
		}

		GetDlgItemText(IDC_ET_PWD,strPwd);
		strPwd.Trim();
		if (strPwd.IsEmpty())
		{
			theApp.OnShowDesktopAlert(_T("���벻��Ϊ�գ�"),TIP_COLOR_WARNING,TIP_TIME_DELAY);
			return;
		}

		CString strSQL = _T("");
		strSQL.Format(_T("select * from %s where %s='%s'"),DB_TABLE_USERINFO,DBUser_key_cUserID,strAct);
		theApp.m_pADOConn->GetRecordSet(strSQL);
		if (!theApp.m_pADOConn->adoEOF())//���ڴ˶�����
		{
			theApp.OnShowDesktopAlert(_T("��Ǹ�����û����Ѵ��ڣ����޸��û�����"),TIP_COLOR_WARNING,TIP_TIME_DELAY);
			return;
		}

		if (m_pObjPerson != NULL)
		{
			delete m_pObjPerson;
			m_pObjPerson = NULL;
		}
		m_pObjPerson = new CDBUserInfoData;
		m_pObjPerson->m_strUserID = strAct;
		m_pObjPerson->m_strUserPwd = Base64Code.base64Encode(strPwd);

		CString strName;
		GetDlgItemText(IDC_ET_NAME,strName);
		strName.Trim();
		m_pObjPerson->m_strUserName= strName;

		m_pObjPerson->m_nUserState = 0;//����û���ע��)ʱ �û�״̬Ϊ������

		//����û���ע��)ʱ��ע��ʱ�䡢���һ�ε�¼ʱ����ͬ
		m_pObjPerson->m_tLastLoadTime
			= m_pObjPerson->m_tUserDate
			= COleDateTime::GetCurrentTime();	

      WorkLog::InsertOneWorkLog(enLog_Cate_SQL_Transaction,enLog_Type_Add,_T(""),_T("������������"),m_strDlgTitle);
      theApp.m_pADOConn->BeginTrans();
      WorkLog::InsertOneWorkLog(enLog_Cate_TableName_Userinfo,enLog_Type_Add,m_pObjPerson->m_strUserID,_T("����û���Ϣ"),m_strDlgTitle);
		if(m_pObjPerson->InsertAllDBInfoByUserID(theApp.m_pADOConn))
		{ 
         WorkLog::InsertOneWorkLog(enLog_Cate_SQL_Transaction,enLog_Type_Add,_T(""),_T("�����û���Ϣ�ɹ����ύ��������"),m_strDlgTitle);
         theApp.m_pADOConn->CommitTrans();
			CDBUserInfoList * pLst = CDBUserInfoList::Instance();
			if (NULL != pLst)
			{
				pLst->AddItem(m_pObjPerson);
			}
         auto pWnd = this->GetParent()->GetSafeHwnd();
         ::PostMessage(pWnd,WM_MSG_STAFFMODIFY,STAFFMODIFY_TYPE_SAVE,0);

			theApp.OnShowDesktopAlert(_T("��ϲ��������û��ɹ���"),TIP_COLOR_SUC,TIP_TIME_DELAY);

			CString str;
			str.Format(_T("���Ա��,���� %s,��� %s") , m_pObjPerson->m_strUserName , m_pObjPerson->m_strUserID);
		}
		else
		{
         WorkLog::InsertOneWorkLog(enLog_Cate_SQL_Transaction,enLog_Type_Add,_T(""),_T("�����û���Ϣʧ�ܣ��ع�����"),m_strDlgTitle);
         theApp.m_pADOConn->RollbackTrans();
			theApp.OnShowDesktopAlert(_T("��Ǹ������û�ʧ�ܣ����ݿ�ִ��ʧ�ܣ���"),TIP_COLOR_WARNING,TIP_TIME_DELAY);
		}

		//�ͷ�ָ��
		if (m_pObjPerson != NULL)
		{
			delete m_pObjPerson;
			m_pObjPerson = NULL;
		}
	}
	else if (STAFF_TYPE_MODIFY == m_wpData)
	{
		CString strPwd = _T("");
		GetDlgItemText(IDC_ET_PWD,strPwd);
		strPwd.Trim();
		if (strPwd.IsEmpty())
		{
			theApp.OnShowDesktopAlert(_T("���벻��Ϊ�գ�"),TIP_COLOR_WARNING,TIP_TIME_DELAY);
			return;
		}
		if(!m_pObjPerson) return;

		m_pObjPerson->m_strUserPwd = Base64Code.base64Encode(strPwd);
		
		CString strName;
		GetDlgItemText(IDC_ET_NAME,strName);
		strName.Trim();
		m_pObjPerson->m_strUserName = strName;	

		CDateTimeCtrl *pDtCtrlReg = (CDateTimeCtrl *)GetDlgItem(IDC_DATEPK_REG_MODIFY);
		pDtCtrlReg->GetTime(m_pObjPerson->m_tUserDate);

		CDateTimeCtrl *pDtCtrLastLoad = (CDateTimeCtrl *)GetDlgItem(IDC_DATEPK_LASTLOAD);
		pDtCtrLastLoad->GetTime(m_pObjPerson->m_tLastLoadTime);

		CComboBox *pCboState = (CComboBox *)GetDlgItem(IDC_CBO_STATE);	
		m_pObjPerson->m_nUserState = pCboState->GetCurSel();		
      	
      theApp.m_pADOConn->BeginTrans();
      WorkLog::InsertOneWorkLog(enLog_Cate_SQL_Transaction,enLog_Type_Add,_T(""),_T("������������"),m_strDlgTitle);
		if(m_pObjPerson->UpdateAllDBInfoByUserID(theApp.m_pADOConn))
		{
         WorkLog::InsertOneWorkLog(enLog_Cate_TableName_Userinfo,enLog_Type_Add,m_pObjPerson->m_strUserID,_T("�޸��û���Ϣ�ɹ�"),m_strDlgTitle);
         WorkLog::InsertOneWorkLog(enLog_Cate_SQL_Transaction,enLog_Type_Add,_T(""),_T("����ɹ����ύ��������"),m_strDlgTitle);
         theApp.m_pADOConn->CommitTrans();
         auto pWnd = this->GetParent()->GetSafeHwnd();
         ::PostMessage(pWnd,WM_MSG_STAFFMODIFY,STAFFMODIFY_TYPE_SAVE,0);
			theApp.OnShowDesktopAlert(_T("��ϲ�����޸��û���Ϣ�ɹ���"),TIP_COLOR_SUC,TIP_TIME_DELAY);
			CString str;
			str.Format(_T("����Ա��,���� %s,��� %s") , m_pObjPerson->m_strUserName , m_pObjPerson->m_strUserID);
		}
		else
		{
         WorkLog::InsertOneWorkLog(enLog_Cate_SQL_Transaction,enLog_Type_Add,_T(""),_T("����ʧ�ܣ��ع�����"),m_strDlgTitle);
         theApp.m_pADOConn->RollbackTrans();
			theApp.OnShowDesktopAlert(_T("��Ǹ���޸��û���Ϣʧ�ܣ����ݿ�ִ��ʧ�ܣ���"),TIP_COLOR_WARNING,TIP_TIME_DELAY);
		}
	}  
}

void CDlgStaffModify::OnBnClickedCancel()
{
   auto pWnd = this->GetParent()->GetSafeHwnd();
   ::PostMessage(pWnd,WM_MSG_STAFFMODIFY,STAFFMODIFY_TYPE_EXIT,0);
}

void CDlgStaffModify::OnSize(UINT nType, int cx, int cy)
{
	CBCGPDialog::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	CRect cRt;
	GetClientRect(cRt);
	ResizeCtrl(cRt);
}

void  CDlgStaffModify::ResizeCtrl(CRect rt)
{

}

void CDlgStaffModify::MyShowWindow(BOOL bShow)
{
	m_bShow = bShow;
	if (m_bShow)
	{
		ShowWindow(SW_SHOW);
	}
	else
	{
		ShowWindow(SW_HIDE);
	}
}