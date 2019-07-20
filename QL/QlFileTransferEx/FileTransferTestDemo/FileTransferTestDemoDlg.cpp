
// FileTransferTestDemoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FileTransferTestDemo.h"
#include "FileTransferTestDemoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CFileTransferTestDemoDlg �Ի���




CFileTransferTestDemoDlg::CFileTransferTestDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFileTransferTestDemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFileTransferTestDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

HWND CFileTransferTestDemoDlg::GetRecvMsgHwnd()
{
   auto pCheck = (CButton *) GetDlgItem(IDC_RADIO_RECVMSG_1);
   return pCheck->GetCheck()== 1? m_wndRecvWnd1.GetSafeHwnd() : m_wndRecvWnd2.GetSafeHwnd();
}

void CFileTransferTestDemoDlg::AddMsgToLog(const CString & strLog)
{
   auto pListBox = (CListBox *) GetDlgItem(IDC_LIST_LOG);
   int nCurSel = pListBox->AddString(strLog);
   pListBox->SetCurSel(nCurSel);
}

BEGIN_MESSAGE_MAP(CFileTransferTestDemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
   ON_BN_CLICKED(IDC_BTN_UPLOAD, &CFileTransferTestDemoDlg::OnBnClickedBtnUpload)
   ON_BN_CLICKED(IDC_BTN_POPUP, &CFileTransferTestDemoDlg::OnBnClickedBtnPopup)
   ON_BN_CLICKED(IDC_BTN_ORDEREXISTS, &CFileTransferTestDemoDlg::OnBnClickedBtnOrderexists)
   ON_BN_CLICKED(IDC_BTN_GETLIST, &CFileTransferTestDemoDlg::OnBnClickedBtnGetlist)
   ON_BN_CLICKED(IDC_BTN_DOWNLOAD, &CFileTransferTestDemoDlg::OnBnClickedBtnDownload)
   ON_BN_CLICKED(IDC_BTN_DOWNLOAD_DIR, &CFileTransferTestDemoDlg::OnBnClickedBtnDownloadDir)
   ON_BN_CLICKED(IDC_BTN_DOWN_BY_EX, &CFileTransferTestDemoDlg::OnBnClickedBtnDownByEx)
   ON_BN_CLICKED(IDC_BTN_DELETE, &CFileTransferTestDemoDlg::OnBnClickedBtnDelete)
   ON_BN_CLICKED(IDC_BTN_DELETE_DIR, &CFileTransferTestDemoDlg::OnBnClickedBtnDeleteDir)
   ON_BN_CLICKED(IDC_BTN_COPYFILE, &CFileTransferTestDemoDlg::OnBnClickedBtnCopyfile)
   ON_BN_CLICKED(IDC_BTN_COPYDIR, &CFileTransferTestDemoDlg::OnBnClickedBtnCopydir)
   ON_BN_CLICKED(IDC_BTN_CLEARRECVLOG, &CFileTransferTestDemoDlg::OnBnClickedBtnClearrecvlog)
   //ON_BN_CLICKED(IDC_BTN_DEL_ORDER_DIR, &CFileTransferTestDemoDlg::OnBnClickedBtnDelOrderDir)
   ON_BN_CLICKED(IDC_BTN_IS_FILE_EXISTS, &CFileTransferTestDemoDlg::OnBnClickedBtnIsFileExists)
   ON_BN_CLICKED(IDC_BTN_BACKUP, &CFileTransferTestDemoDlg::OnBnClickedBtnBackup)

   ON_BN_CLICKED(IDC_BTN_COPY_VERSION_TO_NEW_ONE, &CFileTransferTestDemoDlg::OnBnClickedBtnCopyVersionToNewOne)
   ON_MESSAGE(WM_QL_FTP_PROGRESS, &CFileTransferTestDemoDlg::OnQlFtpProgress)
END_MESSAGE_MAP()


// CFileTransferTestDemoDlg ��Ϣ�������

BOOL CFileTransferTestDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
   CRect rc1,rc2;
   CWnd * pRectWnd = GetDlgItem(IDC_STATIC_RECT1);
   pRectWnd->GetWindowRect(rc1);
   ScreenToClient(rc1);

   pRectWnd = GetDlgItem(IDC_STATIC_RECT2);
   pRectWnd->GetWindowRect(rc2);
   ScreenToClient(rc2);

   m_wndRecvWnd1.Create(CDlgRecvWnd::IDD,this);
   m_wndRecvWnd1.MoveWindow(rc1);
   m_wndRecvWnd1.ShowWindow(SW_SHOW);
   m_wndRecvWnd2.Create(CDlgRecvWnd::IDD,this);
   m_wndRecvWnd2.MoveWindow(rc2);
   m_wndRecvWnd2.ShowWindow(SW_SHOW);

   //��ʼ������
   auto pCheck  = (CButton *)GetDlgItem(IDC_RADIO_RECVMSG_1);
   pCheck->SetCheck(1);

   //����ʱ���Ե����˴�����Ĭ��·��
   SetDlgItemText(IDC_ET_WORKPATH,_T("D:\svnD\BF-PDM"));

   /*CFileTransferEx oFileTrans(_T(""),_T(""),_T(""));
   CString strVersion = oFileTrans.GetVersion();
   SetWindowText(_T("�������Գ���   �汾��:") + strVersion);*/

#ifdef _DEBUG
   SetDlgItemText(IDC_ET_KEY,_T("File_BackUp_Process"));
   SetDlgItemText(IDC_ET_ORDER,_T("�ⷨɭ"));
#endif // _DEBUG


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

CString CFileTransferTestDemoDlg::GetActionKey()
{
   CString strActionKey = _T("");

   GetDlgItemText(IDC_ET_KEY,strActionKey);

   return strActionKey;
}

void CFileTransferTestDemoDlg::GetParamList(CStringList & strParamList)
{
   strParamList.RemoveAll();
   CString strParam;
   GetDlgItemText(IDC_ET_PARAM,strParam);
   strParam.Trim();
   if (strParam.IsEmpty())
   {
      return;
   }

   int nPos = strParam.Find('\n');
   while(-1 != nPos)
   {
      CString strParamInfo = strParam.Left(nPos);
      strParamInfo.Trim();

      if (!strParamInfo.IsEmpty())
      {
         strParamList.AddTail(strParamInfo);
      }

      strParam = strParam.Right(strParam.GetLength() - nPos - 1);

      nPos = strParam.Find('\n');
   }
   strParam.Trim();
   if (!strParam.IsEmpty())
   {
      strParamList.AddTail(strParam);
   }
}

void CFileTransferTestDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CFileTransferTestDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CFileTransferTestDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CFileTransferTestDemoDlg::OnBnClickedBtnClearrecvlog()
{
   m_wndRecvWnd1.ClearLog();
   m_wndRecvWnd2.ClearLog();
}

void CFileTransferTestDemoDlg::OnBnClickedBtnPopup()
{
   auto pFileTrans = PrepareFileTrans();
   if (!pFileTrans)
      return;

   BOOL bExists = FALSE;
   auto nRetCode = filetrans_easy_getinfo(pFileTrans,FILETRANSINFO_POPUPLOGIN,&bExists);

   if (nRetCode == FILETRANS_OK)
   {
      if (bExists)
      {
         AddMsgToLog(_T("��¼�ɹ�"));
      }
      else
      {
         AddMsgToLog(_T("��¼ʧ��"));
      }
   }
   else
   {
      AddMsgToLog(_T("ִ��ʧ�ܣ�"));
   }

   ClearFileTrans(pFileTrans);
}

void CFileTransferTestDemoDlg::OnBnClickedBtnOrderexists()
{
   CString strOrder;
   GetDlgItemText(IDC_ET_ORDER,strOrder);
   if (strOrder.IsEmpty())
   {
      return;
   }


   auto pFileTrans = PrepareFileTrans();
   if (!pFileTrans)
      return;

   filetrans_easy_setopt(pFileTrans,FTOPT_ORDER,strOrder);
   //�ٸ�key

   BOOL bExists = FALSE;
   auto nRetCode = filetrans_easy_getinfo(pFileTrans,FILETRANSINFO_ORDER_EXISTS,&bExists);

   if (nRetCode == FILETRANS_OK)
   {
      if (bExists)
      {
         AddMsgToLog(_T("��������"));
      }
      else
      {
         AddMsgToLog(_T("����������"));
      }
   }
   else
   {
      AddMsgToLog(_T("ִ��ʧ�ܣ�"));
   }

   ClearFileTrans(pFileTrans);
}

void CFileTransferTestDemoDlg::OnBnClickedBtnGetlist()
{
   CString strOrder,strSize;
   GetDlgItemText(IDC_ET_ORDER,strOrder);
   GetDlgItemText(IDC_ET_SIZE,strSize);

   auto pFileTrans = PrepareFileTrans();
   if (!pFileTrans)
      return;
   filetrans_easy_setopt(pFileTrans,FTOPT_FLAG,0);
   filetrans_easy_setopt(pFileTrans,FTOPT_ORDER,strOrder);
   filetrans_easy_setopt(pFileTrans,FTOPT_SIZE,strSize);
   filetrans_easy_setopt(pFileTrans,FTOPT_VERSION,-1);
   //�ٸ�key
   filetrans_easy_setopt(pFileTrans,FTOPT_ACTION,en_Action_GetList);
   filetrans_easy_setopt(pFileTrans,FTOPT_ACTION_KEY,GetActionKey());//����Ӧ�÷��ö�Ӧkey�Ĳ���
   filetrans_easy_perform(pFileTrans);
   ClearFileTrans(pFileTrans);

}

void CFileTransferTestDemoDlg::OnBnClickedBtnUpload()
{
   CString strOrder;
   GetDlgItemText(IDC_ET_ORDER,strOrder);
   if (strOrder.IsEmpty())
   {
      return;
   }

   //2.��ȡ�����ļ�·��
   CString strFileName = _T("");
   CFileDialog fileDlg(true);
   fileDlg.m_ofn.lpstrFilter = LPCTSTR(_T("ALL File(*.*)\0*.*\0\0"));
   fileDlg.m_ofn.lpstrTitle = LPCTSTR(_T("�ϴ��ļ�"));
   fileDlg.m_ofn.Flags |= OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT|OFN_FILEMUSTEXIST;

   //2017/04/10 zhangt ��������ļ�����500
   fileDlg.m_ofn.nMaxFile = 500*MAX_PATH;
   TCHAR *ch = new TCHAR[fileDlg.m_ofn.nMaxFile];
   fileDlg.m_ofn.lpstrFile = ch;
   ZeroMemory(fileDlg.m_ofn.lpstrFile,sizeof(TCHAR)*fileDlg.m_ofn.nMaxFile);
   //2017/04/10_end

   if(fileDlg.DoModal() != IDOK)
   {
      delete[] ch;//�ͷ� new ����
      return;
   }

   POSITION   pos = fileDlg.GetStartPosition();
   CStringList strListImport;
   while(pos)
   {
      strFileName = fileDlg.GetNextPathName(pos);
      if (!strFileName.IsEmpty())
      {
         strListImport.AddTail(strFileName);
      }
   }
   delete[] ch;//�ͷ� new ����


   int nVersion = -1;
   CString strVersion;
   GetDlgItemText(IDC_ET_VERSION,strVersion);
   if (!strVersion.IsEmpty())
   {
      nVersion = _ttoi(strVersion);
   }
   

   auto pFileTrans = PrepareFileTrans();
   if (!pFileTrans)
      return;

   filetrans_easy_setopt(pFileTrans,FTOPT_ORDER,strOrder);
   //�ٸ�key
   filetrans_easy_setopt(pFileTrans,FTOPT_ACTION,en_Action_Upload);
   filetrans_easy_setopt(pFileTrans,FTOPT_ACTION_KEY,GetActionKey());//����Ӧ�÷��ö�Ӧkey�Ĳ���

   vector<CString> vecOneParam;
   int nIndex = 0,nCount = strListImport.GetCount();
   for (nIndex = 0;nIndex < nCount;nIndex++)
   {
      auto str = strListImport.GetAt(strListImport.FindIndex(nIndex));
      vecOneParam.push_back(str);
   }
   filetrans_easy_setopt(pFileTrans,FTOPT_VEC_ONEPARAM,vecOneParam);

   auto pCheck = (CButton *) GetDlgItem(IDC_CK_UPLOAD_DELSRC);
   filetrans_easy_setopt(pFileTrans,FTOPT_DELSRC,1 == pCheck->GetCheck());

   filetrans_easy_setopt(pFileTrans,FTOPT_FLAG,0);

   filetrans_easy_perform(pFileTrans);

   ClearFileTrans(pFileTrans);
}

FILETRANS * CFileTransferTestDemoDlg::PrepareFileTrans()
{
   CString strWorkPath;
   GetDlgItemText(IDC_ET_WORKPATH,strWorkPath);

   if (strWorkPath.IsEmpty())
   {
      MessageBox(_T("����һ�°�װ��·����"));
      return nullptr;
   }

   FILETRANS * pFileTrans = filetrans_easy_init(strWorkPath,En_Login_User);


   auto pCheck = (CButton *)GetDlgItem(IDC_CK_LOG);
   //filetrans_easy_setopt(pFileTrans,FTOPT_,1 == pCheck->GetCheck());

   CString strSize;
   GetDlgItemText(IDC_ET_SIZE,strSize);

   filetrans_easy_setopt(pFileTrans,FTOPT_SIZE,strSize);
   filetrans_easy_setopt(pFileTrans,FTOPT_HWND,GetRecvMsgHwnd());

   return pFileTrans;
}

void CFileTransferTestDemoDlg::ClearFileTrans(FILETRANS * pFileTrans)
{
   FileTrans_easy_cleanup(pFileTrans);
}

void CFileTransferTestDemoDlg::OnBnClickedBtnDownload()
{
   CString strParam,strOrder;
   GetDlgItemText(IDC_ET_ORDER,strOrder);
   if (strOrder.IsEmpty())
   {
      return;
   }

   CStringList strParamList;
   GetParamList(strParamList);

   CString strExportFilePath;

   BROWSEINFO bi; 
   ZeroMemory(&bi,sizeof(BROWSEINFO));
   bi.ulFlags = BIF_BROWSEINCLUDEFILES; 
   bi.ulFlags = BIF_NEWDIALOGSTYLE;
   bi.ulFlags = BIF_RETURNONLYFSDIRS;
   bi.ulFlags = BIF_NEWDIALOGSTYLE;    //���ڿ��Ե�����С�����½��ļ��а�ť
   bi.lpszTitle = _T("��ѡ�񵼳���Ŀ¼");  
   bi.hwndOwner = GetSafeHwnd();
   LPITEMIDLIST pidl = SHBrowseForFolder(&bi); 
   TCHAR * path = new TCHAR[MAX_PATH];  
   if(pidl != NULL)  
   {  
      SHGetPathFromIDList(pidl,path);
      strExportFilePath = path;
      if(NULL != path)
      {
         delete path;
         path = NULL;
      }
      if (strExportFilePath.IsEmpty())
      {
         return;
      }
      strExportFilePath = strExportFilePath;
   }
   else
   {
      if(NULL != path)
      {
         delete path;
         path = NULL;
      }
      return ;
   }
   if (strExportFilePath.IsEmpty())
   {
      return;
   }


   auto pFileTrans = PrepareFileTrans();
   if (!pFileTrans)
      return;

   filetrans_easy_setopt(pFileTrans,FTOPT_ORDER,strOrder);
   //�ٸ�key
   filetrans_easy_setopt(pFileTrans,FTOPT_ACTION,en_Action_Down);
   filetrans_easy_setopt(pFileTrans,FTOPT_ACTION_KEY,GetActionKey());//����Ӧ�÷��ö�Ӧkey�Ĳ���

   vector<pair<CString,CString>> vecTwoParam;
   int nIndex  = 0,nCount = strParamList.GetCount();
   for (nIndex = 0;nIndex < nCount;++nIndex)
   {
      strParam = strParamList.GetAt(strParamList.FindIndex(nIndex));
      CString strDownPath = strExportFilePath + _T("\\") + strParam;

      vecTwoParam.push_back(make_pair(strParam,strDownPath));
   }
   filetrans_easy_setopt(pFileTrans,FTOPT_VEC_TWOPARAM,vecTwoParam);

   /*auto pCheck = (CButton *) GetDlgItem(IDC_CK_UPLOAD_DELSRC);
   filetrans_easy_setopt(pFileTrans,FTOPT_DELSRC,1 == pCheck->GetCheck());*/

   filetrans_easy_setopt(pFileTrans,FTOPT_FLAG,0);

   filetrans_easy_perform(pFileTrans);

   ClearFileTrans(pFileTrans);
}

void CFileTransferTestDemoDlg::OnBnClickedBtnDelete()
{
   CString strParam,strOrder;
   GetDlgItemText(IDC_ET_ORDER,strOrder);

   CStringList strParamList;
   GetParamList(strParamList);


   auto pFileTrans = PrepareFileTrans();
   if (!pFileTrans)
      return;

   filetrans_easy_setopt(pFileTrans,FTOPT_ORDER,strOrder);
   //�ٸ�key
   filetrans_easy_setopt(pFileTrans,FTOPT_ACTION,en_Action_Delete);
   filetrans_easy_setopt(pFileTrans,FTOPT_ACTION_KEY,GetActionKey());//����Ӧ�÷��ö�Ӧkey�Ĳ���

   vector<CString> vecOneParam;
   int nIndex = 0,nCount = strParamList.GetCount();
   for (nIndex = 0;nIndex < nCount;nIndex++)
   {
      auto str = strParamList.GetAt(strParamList.FindIndex(nIndex));
      vecOneParam.push_back(str);
   }
   filetrans_easy_setopt(pFileTrans,FTOPT_VEC_ONEPARAM,vecOneParam);

   /*auto pCheck = (CButton *) GetDlgItem(IDC_CK_UPLOAD_DELSRC);
   filetrans_easy_setopt(pFileTrans,FTOPT_DELSRC,1 == pCheck->GetCheck());*/

   filetrans_easy_setopt(pFileTrans,FTOPT_FLAG,0);

   filetrans_easy_perform(pFileTrans);

   ClearFileTrans(pFileTrans);
}

void CFileTransferTestDemoDlg::OnBnClickedBtnDownloadDir()
{
   CString strParam,strOrder;
   GetDlgItemText(IDC_ET_ORDER,strOrder);

   CStringList strParamList;
   GetParamList(strParamList);
   
   CString strExportFilePath;

   BROWSEINFO bi; 
   ZeroMemory(&bi,sizeof(BROWSEINFO));
   bi.ulFlags = BIF_BROWSEINCLUDEFILES; 
   bi.ulFlags = BIF_NEWDIALOGSTYLE;
   bi.ulFlags = BIF_RETURNONLYFSDIRS;
   bi.ulFlags = BIF_NEWDIALOGSTYLE;    //���ڿ��Ե�����С�����½��ļ��а�ť
   bi.lpszTitle = _T("��ѡ�񵼳���Ŀ¼");  
   bi.hwndOwner = GetSafeHwnd();
   LPITEMIDLIST pidl = SHBrowseForFolder(&bi); 
   TCHAR * path = new TCHAR[MAX_PATH];  
   if(pidl != NULL)  
   {  
      SHGetPathFromIDList(pidl,path);
      strExportFilePath = path;
      if(NULL != path)
      {
         delete path;
         path = NULL;
      }
      if (strExportFilePath.IsEmpty())
      {
         return;
      }
      strExportFilePath = strExportFilePath;
   }
   else
   {
      if(NULL != path)
      {
         delete path;
         path = NULL;
      }
      return ;
   }
   if (strExportFilePath.IsEmpty())
   {
      return;
   }

   auto pFileTrans = PrepareFileTrans();
   if (!pFileTrans)
      return;

   int nVersion = -1;
   CString strVersion;
   GetDlgItemText(IDC_ET_VERSION,strVersion);
   if (!strVersion.IsEmpty())
   {
      nVersion = _ttoi(strVersion);
   }

   filetrans_easy_setopt(pFileTrans,FTOPT_ORDER,strOrder);
   filetrans_easy_setopt(pFileTrans,FTOPT_DST_VERSION,nVersion);
   //�ٸ�key
   filetrans_easy_setopt(pFileTrans,FTOPT_ACTION,en_Action_DownDir);
   filetrans_easy_setopt(pFileTrans,FTOPT_ACTION_KEY,GetActionKey());//����Ӧ�÷��ö�Ӧkey�Ĳ���


   CString strSize,strSizeParam;
   GetDlgItemText(IDC_ET_SIZE,strSize);
   int nIndex  = 0,nCount = strParamList.GetCount();

   for (nIndex = 0;nIndex < nCount;++nIndex)
   {
      strParam = strParamList.GetAt(strParamList.FindIndex(nIndex));

      if (strSize.IsEmpty())
      {
         strSizeParam = strParam;
      }
      else
      {
         strSizeParam.Format(_T("%s/%s"),strSize,strParam);
      }
      filetrans_easy_setopt(pFileTrans,FTOPT_SIZE,strSizeParam);

      vector<pair<CString,CString>> vecTwoParam;
      vecTwoParam.push_back(make_pair(_T(""),strExportFilePath));//��ΪԶ��·�����Զ����ɵ�  ��˵�һ������Ϊ��
      filetrans_easy_setopt(pFileTrans,FTOPT_VEC_TWOPARAM,vecTwoParam);

      filetrans_easy_perform(pFileTrans);
      
      filetrans_easy_setopt(pFileTrans,FTOPT_SIZE,_T(""));
   }

   if (0 == nCount)
   {//���û�����ò����Ļ�  
      vector<pair<CString,CString>> vecTwoParam;
      vecTwoParam.push_back(make_pair(_T(""),strExportFilePath));//��ΪԶ��·�����Զ����ɵ�  ��˵�һ������Ϊ��
      filetrans_easy_setopt(pFileTrans,FTOPT_VEC_TWOPARAM,vecTwoParam);
      filetrans_easy_perform(pFileTrans);
   }

   ClearFileTrans(pFileTrans);
}

void CFileTransferTestDemoDlg::OnBnClickedBtnDeleteDir()
{
   CString strParam,strOrder;
   GetDlgItemText(IDC_ET_ORDER,strOrder);
   if (strOrder.IsEmpty())
   {
      return;
   }

   CStringList strParamList;
   GetParamList(strParamList);


   auto pFileTrans = PrepareFileTrans();
   if (!pFileTrans)
      return;

   filetrans_easy_setopt(pFileTrans,FTOPT_ORDER,strOrder);
   //�ٸ�key
   filetrans_easy_setopt(pFileTrans,FTOPT_ACTION,en_Action_DeleteDir);
   filetrans_easy_setopt(pFileTrans,FTOPT_ACTION_KEY,GetActionKey());//����Ӧ�÷��ö�Ӧkey�Ĳ���
   filetrans_easy_setopt(pFileTrans,FTOPT_FLAG,0);

   CString strSize,strSizeParam;
   GetDlgItemText(IDC_ET_SIZE,strSize);
   int nIndex  = 0,nCount = strParamList.GetCount();
   for (nIndex = 0;nIndex < nCount;++nIndex)
   {
      strParam = strParamList.GetAt(strParamList.FindIndex(nIndex));

      if (strSize.IsEmpty())
      {
         strSizeParam = strParam;
      }
      else
      {
         strSizeParam.Format(_T("%s/%s"),strSize,strParam);
      }

      filetrans_easy_setopt(pFileTrans,FTOPT_SIZE,strSizeParam);
      filetrans_easy_perform(pFileTrans);
      filetrans_easy_setopt(pFileTrans,FTOPT_SIZE,_T(""));
   }

   if(0 == nCount)
   {
      filetrans_easy_perform(pFileTrans);
   }

   ClearFileTrans(pFileTrans);
}

void CFileTransferTestDemoDlg::OnBnClickedBtnDownByEx()
{
   CString strParam,strOrder;
   GetDlgItemText(IDC_ET_ORDER,strOrder);
   if (strOrder.IsEmpty())
   {
      return;
   }
   CStringList strParamList;
   GetParamList(strParamList);

   CString strExportFilePath;
   BROWSEINFO bi; 
   ZeroMemory(&bi,sizeof(BROWSEINFO));
   bi.ulFlags = BIF_BROWSEINCLUDEFILES; 
   bi.ulFlags = BIF_NEWDIALOGSTYLE;
   bi.ulFlags = BIF_RETURNONLYFSDIRS;
   bi.ulFlags = BIF_NEWDIALOGSTYLE;    //���ڿ��Ե�����С�����½��ļ��а�ť
   bi.lpszTitle = _T("��ѡ�񵼳���Ŀ¼");  
   bi.hwndOwner = GetSafeHwnd();
   LPITEMIDLIST pidl = SHBrowseForFolder(&bi); 
   TCHAR * path = new TCHAR[MAX_PATH];  
   if(pidl != NULL)  
   {  
      SHGetPathFromIDList(pidl,path);
      strExportFilePath = path;
      if(NULL != path)
      {
         delete path;
         path = NULL;
      }
      if (strExportFilePath.IsEmpty())
      {
         return;
      }
      strExportFilePath = strExportFilePath;
   }
   else
   {
      if(NULL != path)
      {
         delete path;
         path = NULL;
      }
      return ;
   }
   if (strExportFilePath.IsEmpty())
   {
      return;
   }


   auto pFileTrans = PrepareFileTrans();
   if (!pFileTrans)
      return;

   filetrans_easy_setopt(pFileTrans,FTOPT_ORDER,strOrder);
   //�ٸ�key
   filetrans_easy_setopt(pFileTrans,FTOPT_ACTION,en_Action_DownByEx);
   filetrans_easy_setopt(pFileTrans,FTOPT_ACTION_KEY,GetActionKey());//����Ӧ�÷��ö�Ӧkey�Ĳ���
   filetrans_easy_setopt(pFileTrans,FTOPT_FLAG,0);
   auto pCheck = (CButton *)GetDlgItem(IDC_CK_DOWN_BY_EX_DIR);
   BOOL bDir = 1 == pCheck->GetCheck();
   filetrans_easy_setopt(pFileTrans,FTOPT_TRAVERSINGDIR,bDir);

   pCheck = (CButton *)GetDlgItem(IDC_CK_DOWN_BY_EX_NODIR);
   DWORD dwStyle = 1 == pCheck->GetCheck() ? FS_NODIR : FS_DEFAULT;
   filetrans_easy_setopt(pFileTrans,FTOPT_STYLE,dwStyle);

   strParam = strParamList.GetAt(strParamList.FindIndex(0));
   vector<pair<CString,CString>> vecTwoParam;
   vecTwoParam.push_back(make_pair(strParam,strExportFilePath));

   filetrans_easy_setopt(pFileTrans,FTOPT_VEC_TWOPARAM,vecTwoParam);

   filetrans_easy_perform(pFileTrans);

   ClearFileTrans(pFileTrans);
}

/*void CFileTransferTestDemoDlg::OnBnClickedBtnDelOrderDir()
{
   CString strOrder;
   GetDlgItemText(IDC_ET_ORDER,strOrder);
   if (strOrder.IsEmpty())
   {
      return;
   }
   CFileTransferEx * pFileTrans = NULL;
   if (!PrepareFileTrans(pFileTrans))
      return;

   pFileTrans->DelOrderDir(strOrder,0);

   / * ��һ��ʵ�ַ���
   pFileTrans->Init(strOrder,GetFileType(),GetWholeType());
   pFileTrans->DelOrderDir(0);
   * /

   delete pFileTrans;
}*/

void CFileTransferTestDemoDlg::OnBnClickedBtnIsFileExists()
{
   CString strParam,strOrder,strSize;
   GetDlgItemText(IDC_ET_ORDER,strOrder);
   if (strOrder.IsEmpty())
   {
      return;
   }

   CStringList strParamList;
   GetParamList(strParamList);

   if (0 == strParamList.GetCount())
   {
      return;
   }

   GetDlgItemText(IDC_ET_SIZE,strSize);
   int nVersion = -1;
   CString strVersion;
   GetDlgItemText(IDC_ET_VERSION,strVersion);
   if (!strVersion.IsEmpty())
   {
      nVersion = _ttoi(strVersion);
   }

   auto pFileTrans = PrepareFileTrans();
   if (!pFileTrans)
      return;

   filetrans_easy_setopt(pFileTrans,FTOPT_ORDER,strOrder);
   filetrans_easy_setopt(pFileTrans,FTOPT_SIZE,strSize);
   filetrans_easy_setopt(pFileTrans,FTOPT_VERSION,nVersion);
   filetrans_easy_setopt(pFileTrans,FTOPT_ACTION_KEY,GetActionKey());//����Ӧ�÷��ö�Ӧkey�Ĳ���

   vector<CString> vecOneParam;
   int nIndex = 0,nCount = strParamList.GetCount();
   for (nIndex = 0;nIndex < nCount && nIndex < 1;nIndex++)//ֻȡ��һ������
   {
      auto str = strParamList.GetAt(strParamList.FindIndex(nIndex));
      vecOneParam.push_back(str);
   }
   filetrans_easy_setopt(pFileTrans,FTOPT_VEC_ONEPARAM,vecOneParam);

   BOOL bFileExists = FALSE;
   auto nRetCode = filetrans_easy_getinfo(pFileTrans,FILETRANSINFO_FILE_EXISTS,&bFileExists);

   if (nRetCode == FILETRANS_OK)
   {
      AddMsgToLog(bFileExists ? _T("�ļ�����") : _T("�ļ�������"));
   }
   else
   {
      AddMsgToLog(_T("ִ��ʧ��"));
   }

   ClearFileTrans(pFileTrans);
}


void CFileTransferTestDemoDlg::OnBnClickedBtnBackup()
{
#ifndef _UNICODE

   MessageBox(_T("��Unicode�ݲ�֧�ָù���"));
   return;
#endif // _UNICODE

   CString strParam,strOrder;
   GetDlgItemText(IDC_ET_ORDER,strOrder);
   if (strOrder.IsEmpty())
   {
      return;
   }

   CString strSize;
   GetDlgItemText(IDC_ET_SIZE,strSize);

   //Ҫ��汾�Ų�����
   int nVersion = -1;
   CString strVersion;
   GetDlgItemText(IDC_ET_VERSION,strVersion);
   if (!strVersion.IsEmpty())
   {
      nVersion = _ttoi(strVersion);
   }
   if(-1 == nVersion)
   {
      return;
   }
   auto pFileTrans = PrepareFileTrans();
   if (!pFileTrans)
      return;


   filetrans_easy_setopt(pFileTrans,FTOPT_ORDER,strOrder);
   filetrans_easy_setopt(pFileTrans,FTOPT_SIZE,strSize);
   //filetrans_easy_setopt(pFileTrans,FTOPT_VERSION,nVersion);


   filetrans_easy_setopt(pFileTrans,FTOPT_ACTION, FALSE/*�ƶ����ǿ���*/ ? en_Action_BackupFile_Move : en_Action_BackupFile_Copy);
   vector<pair<CString,CString>> vec_TwoParam;

   vec_TwoParam.push_back(make_pair(_T("File_Process"),_T("File_BackUp_Process")));
   vec_TwoParam.push_back(make_pair(_T("File_Pattern"),_T("File_BackUp_Pattern")));
   vec_TwoParam.push_back(make_pair(_T("File_Mac"),_T("File_BackUp_Mac")));
   filetrans_easy_setopt(pFileTrans,FTOPT_VEC_TWOPARAM, vec_TwoParam);

   filetrans_easy_setopt(pFileTrans,FTOPT_DST_VERSION, nVersion);
   filetrans_easy_setopt(pFileTrans,FTOPT_DST_ORDER, strOrder);

   int nRetCode = filetrans_easy_perform(pFileTrans);
   ClearFileTrans(pFileTrans);

   if (FILETRANS_OK != nRetCode)
   {
      MessageBox(_T("����ʧ��"));
   }
}

void CFileTransferTestDemoDlg::OnBnClickedBtnCopyfile()
{
   //�����ļ�
   CString strParam,strOrder;
   GetDlgItemText(IDC_ET_ORDER,strOrder);
   
   CStringList strParamList;
   GetParamList(strParamList);
   int nVersion = -1;

   CString strSize;
   GetDlgItemText(IDC_ET_SIZE,strSize);


   auto pFileTrans = PrepareFileTrans();
   if (!pFileTrans)
      return;

   filetrans_easy_setopt(pFileTrans,FTOPT_ORDER,strOrder);
   filetrans_easy_setopt(pFileTrans,FTOPT_SIZE,strSize);
   filetrans_easy_setopt(pFileTrans,FTOPT_VERSION,-1);
   //�ٸ�key
   filetrans_easy_setopt(pFileTrans,FTOPT_ACTION,en_Action_Copy);
   filetrans_easy_setopt(pFileTrans,FTOPT_ACTION_KEY,_T("File_Process"));//����Ӧ�÷��ö�Ӧkey�Ĳ���
   filetrans_easy_setopt(pFileTrans,FTOPT_FLAG,0);

   //����ʱ  ��1 ���ư� ������2�汾�Ĺ���  ��������1�汾
   filetrans_easy_setopt(pFileTrans,FTOPT_DST_ACTION_KEY,/*_T("File_Process")*/_T("File_BackUp_Pattern"));
   filetrans_easy_setopt(pFileTrans,FTOPT_DST_ORDER,strOrder);
   filetrans_easy_setopt(pFileTrans,FTOPT_DST_SIZE,_T(""));
   filetrans_easy_setopt(pFileTrans,FTOPT_DST_VERSION,1);

   vector<pair<CString,CString>> vecTwoParam;
   int nIndex  = 0,nCount = strParamList.GetCount();
   for (nIndex = 0;nIndex < nCount;++nIndex)
   {
      strParam = strParamList.GetAt(strParamList.FindIndex(nIndex));

      vecTwoParam.push_back(make_pair(strParam,strParam));
   }

   filetrans_easy_setopt(pFileTrans,FTOPT_VEC_TWOPARAM,vecTwoParam);

   filetrans_easy_perform(pFileTrans);

   ClearFileTrans(pFileTrans);
}

void CFileTransferTestDemoDlg::OnBnClickedBtnCopydir()
{
   //�����ļ�
   CString strParam,strOrder;
   GetDlgItemText(IDC_ET_ORDER,strOrder);
   if (strOrder.IsEmpty())
   {
      return;
   }
   
   CStringList strParamList;
   GetParamList(strParamList);

   CString strSize;
   GetDlgItemText(IDC_ET_SIZE,strSize);

   auto pFileTrans = PrepareFileTrans();
   if (!pFileTrans)
      return;

   filetrans_easy_setopt(pFileTrans,FTOPT_ORDER,strOrder);
   filetrans_easy_setopt(pFileTrans,FTOPT_SIZE,strSize);
   filetrans_easy_setopt(pFileTrans,FTOPT_VERSION,1);
   //�ٸ�key
   filetrans_easy_setopt(pFileTrans,FTOPT_ACTION,en_Action_Copy);
   filetrans_easy_setopt(pFileTrans,FTOPT_ACTION_KEY,_T("File_BackUp_Pattern"));//����Ӧ�÷��ö�Ӧkey�Ĳ���
   filetrans_easy_setopt(pFileTrans,FTOPT_FLAG,0);

   //����ʱ  ��1 ���ư� ������2�汾�Ĺ���  ��������1�汾
   filetrans_easy_setopt(pFileTrans,FTOPT_DST_ACTION_KEY,_T("File_BackUp_Process"));
   filetrans_easy_setopt(pFileTrans,FTOPT_DST_ORDER,strOrder);
   filetrans_easy_setopt(pFileTrans,FTOPT_DST_SIZE,_T(""));
   filetrans_easy_setopt(pFileTrans,FTOPT_DST_VERSION,2);

   vector<pair<CString,CString>> vecTwoParam;
   int nIndex  = 0,nCount = strParamList.GetCount();
   for (nIndex = 0;nIndex < nCount;++nIndex)
   {
      strParam = strParamList.GetAt(strParamList.FindIndex(nIndex));
      strParam += _T("\\");

      vecTwoParam.push_back(make_pair(strParam,strParam));
   }

   filetrans_easy_setopt(pFileTrans,FTOPT_VEC_TWOPARAM,vecTwoParam);

   filetrans_easy_perform(pFileTrans);

   ClearFileTrans(pFileTrans);
}

void CFileTransferTestDemoDlg::OnBnClickedBtnCopyVersionToNewOne()
{
#ifndef _UNICODE
   MessageBox(_T("��Unicode�ݲ�֧�ָù���"));
   return;
#endif // _UNICODE
   //����ָ���汾���µ�ǰ�汾
   CString strParam,strOrder;
   GetDlgItemText(IDC_ET_ORDER,strOrder);
   if (strOrder.IsEmpty())
   {
      return;
   }

   auto pFileTrans = PrepareFileTrans();
   if (!pFileTrans)
      return;

   filetrans_easy_setopt(pFileTrans,FTOPT_ACTION, en_Action_CopyVersionToCurVersion);
   filetrans_easy_setopt(pFileTrans,FTOPT_ORDER,strOrder);
   //filetrans_easy_setopt(pFileTrans,FTOPT_SIZE,strSize);
   filetrans_easy_setopt(pFileTrans,FTOPT_VERSION,1);

   filetrans_easy_setopt(pFileTrans,FTOPT_DST_ORDER,strOrder);
   //filetrans_easy_setopt(pFileTrans,FTOPT_DST_SIZE,strSize);
   filetrans_easy_setopt(pFileTrans,FTOPT_DST_VERSION,2);

   vector<pair<CString,CString>> vec_TwoParam;
   vec_TwoParam.push_back(make_pair(_T("File_Process"),_T("File_BackUp_Process")));
   vec_TwoParam.push_back(make_pair(_T("File_Pattern"),_T("File_BackUp_Pattern")));
   vec_TwoParam.push_back(make_pair(_T("File_Mac"),_T("File_BackUp_Mac")));
   filetrans_easy_setopt(pFileTrans,FTOPT_VEC_TWOPARAM, vec_TwoParam);

   filetrans_easy_setopt(pFileTrans,FTOPT_ACTION_KEY,GetActionKey());//����Ӧ�÷��ö�Ӧkey�Ĳ���

   filetrans_easy_perform(pFileTrans);

   ClearFileTrans(pFileTrans);

}

LRESULT CFileTransferTestDemoDlg::OnQlFtpProgress(WPARAM wParam, LPARAM lParam)
{
   auto pWnd =  (CProgressCtrl *)GetDlgItem(IDC_TRANS_PROCESS);

   pWnd->ShowWindow( 0 == lParam ? SW_SHOW : SW_HIDE);
   pWnd->SetPos(wParam);

   return 0;
}


