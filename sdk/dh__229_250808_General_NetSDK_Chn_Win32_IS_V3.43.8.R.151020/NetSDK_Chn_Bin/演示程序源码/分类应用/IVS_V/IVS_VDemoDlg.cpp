// IVS_VDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IVS_VDemo.h"
#include "IVS_VDemoDlg.h"
#include "ProfileCfg.h"
#include "TaskCfg.h"
#include "ProjectCfg.h"
#include "GlobalCfg.h"
#include "ListenDiagnosisRes.h"
#include "QueryDiagnosisRes.h"
#include "DeviceListDlg.h"
#include "LoginDlg.h"
#include "SdkCallback.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIVS_VDemoDlg dialog

CIVS_VDemoDlg::CIVS_VDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIVS_VDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIVS_VDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	memset(m_pDlgArr,0x0,sizeof(m_pDlgArr));
	m_pDlgArr[ENUM_DLG_PROFILE] = new CProfileCfg;
	m_pDlgArr[ENUM_DLG_TAST]    = new CTaskCfg(m_pDlgArr[ENUM_DLG_PROFILE]);
	m_pDlgArr[ENUM_DLG_PROJECT] = new CProjectCfg(m_pDlgArr[ENUM_DLG_TAST]);
	m_pDlgArr[ENUM_DLG_LISTEN]  = new CListenDiagnosisRes(m_pDlgArr[ENUM_DLG_PROJECT]);
	m_pDlgArr[ENUM_DLG_QUERY]  = new CQueryDiagnosisRes(m_pDlgArr[ENUM_DLG_PROJECT]);

	m_nCurrentDlg = -1;

	m_pDevLstDlg = new CDeviceListDlg;

	m_hLoginID = 0;

	memset(&m_stCapsInfo, 0x0, sizeof(CFG_VIDEODIAGNOSIS_CAPS_INFO));
}

CIVS_VDemoDlg::~CIVS_VDemoDlg()
{
	for (int i=0; i<SHOW_DLG_COUNT; i++)
	{
		SAFE_DELETE(m_pDlgArr[i]);
	}

	SAFE_DELETE(m_pDevLstDlg);

	CLoginDlg::Logout(m_hLoginID);
}

void CIVS_VDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIVS_VDemoDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CIVS_VDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CIVS_VDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_MPROFILE, OnMprofile)
	ON_BN_CLICKED(IDC_BTN_PROFILE_CFG, OnBtnProfileCfg)
	ON_BN_CLICKED(IDC_BTN_TASK_CFG, OnBtnTaskCfg)
	ON_BN_CLICKED(IDC_BTN_PROJECT_CFG, OnBtnProjectCfg)
	ON_BN_CLICKED(IDC_BTN_LISTEN, OnBtnListen)
	ON_BN_CLICKED(IDC_BTN_QUERY, OnBtnQuery)
	ON_BN_CLICKED(IDC_BTN_LOGIN, OnBtnLogin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIVS_VDemoDlg message handlers

BOOL CIVS_VDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this);

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	//////////////////////////////////////////////////////////////////////////
	/// 网络库初始化
	BOOL bRet = InitNetSDK();
	if (bRet == FALSE)
	{
		printf("InitNetSDK err !");
		int a =0;
		printf("\n please input any key to quit exe !");
		scanf("%d",&a);
		return FALSE;
	}

	//////////////////////////////////////////////////////////////////////////
	/// 资源初始化
	CRect rc;
	GetShowArea(IDC_STATIC_MAIN, rc);
	CRect rc1;
	GetShowArea(IDC_STATIC_DEVLIST, rc1);
	CRect rc2;
	GetShowArea(IDC_STATIC_TEST, rc2);
	int nDlgArr[] = {IDD_DLG_PROFILE, IDD_DLG_TASK, IDD_DLG_PROJECT,IDD_DLG_LISTEN,IDD_DLG_QUERY};
	for (int i=0; i< sizeof(nDlgArr)/sizeof(nDlgArr[0]); i++)
	{
		m_pDlgArr[i]->Create(nDlgArr[i]);
		if (nDlgArr[i] != IDD_DLG_TASK/* && nDlgArr[i] != IDD_DLG_QUERY*/)
		{
			m_pDlgArr[i]->MoveWindow(rc2);
		}
		else
		{
			m_pDlgArr[i]->MoveWindow(rc);
		}
		m_pDlgArr[i]->SetOwner(this);
	}

	m_pDevLstDlg->Create(IDD_DLG_DEVICE);
	m_pDevLstDlg->MoveWindow(rc1);
	m_pDevLstDlg->ShowWindow(SW_SHOW);
	m_pDevLstDlg->SetOwner(this);

	ShowDialog(ENUM_DLG_PROFILE);

	OnBtnLogin();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CIVS_VDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CIVS_VDemoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CIVS_VDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CIVS_VDemoDlg::OnOK() 
{
	//ConfigProfile();
	//listen();
	//find();
	//CDialog::OnOK();
}

void CIVS_VDemoDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CIVS_VDemoDlg::OnMprofile() 
{
	// TODO: Add your command handler code here


	CProfileCfg d;
	d.DoModal();
}

void CIVS_VDemoDlg::GetShowArea(int nId,CRect &rc)
{
	CWnd* pWnd = GetDlgItem(nId);
	if (NULL != pWnd)
	{
		pWnd->GetWindowRect(&rc);
		ScreenToClient(&rc);
		//rc.DeflateRect(10,10);
	}
}

void CIVS_VDemoDlg::ShowDialog(int nDlg)
{
	UpdateData(FALSE);
	for (int i=0; i < sizeof(m_pDlgArr)/sizeof(m_pDlgArr[0]); i++)
	{
		if (NULL != m_pDlgArr[i])
			m_pDlgArr[i]->ShowWindow(SW_HIDE);
	}
	m_nCurrentDlg = nDlg;

	if (NULL != m_pDevLstDlg)
	{
		if (nDlg != ENUM_DLG_TAST /*&& nDlg != ENUM_DLG_QUERY*/)
		{
			m_pDevLstDlg->ShowWindow(SW_HIDE);
			
			//GetDlgItem(IDC_STATIC_DEVLIST)->ShowWindow(SW_HIDE);
			//GetDlgItem(IDC_STATIC_MAIN)->ShowWindow(SW_HIDE);
			//GetDlgItem(IDC_STATIC_TEST)->ShowWindow(SW_SHOW);
		}
		else
		{
			m_pDevLstDlg->ShowWindow(SW_SHOW);
			
			//GetDlgItem(IDC_STATIC_MAIN)->ShowWindow(SW_SHOW);
			//GetDlgItem(IDC_STATIC_DEVLIST)->ShowWindow(SW_SHOW);
			//GetDlgItem(IDC_STATIC_TEST)->ShowWindow(SW_HIDE);
		}
	}

	m_pDlgArr[m_nCurrentDlg]->ShowWindow(SW_SHOW);
	UpdateData(TRUE);
}

void CIVS_VDemoDlg::OnBtnProfileCfg() 
{
	// TODO: Add your control notification handler code here
	ShowDialog(ENUM_DLG_PROFILE);
}

void CIVS_VDemoDlg::OnBtnTaskCfg() 
{
	// TODO: Add your control notification handler code here
	if (m_nCurrentDlg == ENUM_DLG_PROFILE)
	{
		reinterpret_cast<CProfileCfg*>(m_pDlgArr[ENUM_DLG_PROFILE])->OnBtnSavePage();
	}
	ShowDialog(ENUM_DLG_TAST);
	reinterpret_cast<CTaskCfg*>(m_pDlgArr[ENUM_DLG_TAST])->InitTask();
}

void CIVS_VDemoDlg::OnBtnProjectCfg() 
{
	// TODO: Add your control notification handler code here
	if (m_nCurrentDlg == ENUM_DLG_PROFILE)
	{
		reinterpret_cast<CProfileCfg*>(m_pDlgArr[ENUM_DLG_PROFILE])->OnBtnSavePage();
	}
	
	ShowDialog(ENUM_DLG_PROJECT);

	reinterpret_cast<CProjectCfg*>(m_pDlgArr[ENUM_DLG_PROJECT])->GetDefaultProject();
}

void CIVS_VDemoDlg::OnBtnListen() 
{
	// TODO: Add your control notification handler code here
	if (m_nCurrentDlg == ENUM_DLG_PROFILE)
	{
		reinterpret_cast<CProfileCfg*>(m_pDlgArr[ENUM_DLG_PROFILE])->OnBtnSavePage();
	}
	
	ShowDialog(ENUM_DLG_LISTEN);
}

void CIVS_VDemoDlg::OnBtnQuery() 
{
	// TODO: Add your control notification handler code here
	if (m_nCurrentDlg == ENUM_DLG_PROFILE)
	{
		reinterpret_cast<CProfileCfg*>(m_pDlgArr[ENUM_DLG_PROFILE])->OnBtnSavePage();
	}
	
	ShowDialog(ENUM_DLG_QUERY);
}

void CIVS_VDemoDlg::EnableWindowArr(const DWORD dwIDArr[], int nIDCount, BOOL bEnable)
{
	for (int i=0; i<nIDCount; i++)
	{
		if (NULL != GetDlgItem(dwIDArr[i]))
		{
			GetDlgItem(dwIDArr[i])->EnableWindow(bEnable);
		}
	}
}
void CIVS_VDemoDlg::OnBtnLogin() 
{
	const DWORD dwIDArr[] = { IDC_BTN_LOGIN, 
		IDC_BTN_PROFILE_CFG, 
		IDC_BTN_TASK_CFG, 
		IDC_BTN_PROJECT_CFG,
		IDC_BTN_LISTEN,
		IDC_BTN_QUERY
	};
	// TODO: Add your control notification handler code here
	if (m_hLoginID > 0)
	{
		CLIENT_Logout(m_hLoginID);
		GetDlgItem(IDC_BTN_LOGIN)->SetWindowText(ConvertString("LogIn"));
		m_hLoginID = 0;

		// 控件不使能
		EnableWindowArr(dwIDArr, sizeof(dwIDArr)/sizeof(dwIDArr[0]), FALSE);
		GetDlgItem(IDC_BTN_LOGIN)->EnableWindow(TRUE);

		OnBtnLogin();
		return;
	}
	else
	{
		std::vector<BYTE> vecDvrType;
		vecDvrType.push_back(VIDEO_IVS_V);
		CLoginDlg dlg(&vecDvrType, NULL);
		DWORD dwRet = dlg.DoModal();
		if (dwRet == IDOK)
		{
			// 获取登陆句柄
			m_hLoginID = dlg.GetLoginHandle();
			// 控件使能
			EnableWindowArr(dwIDArr, sizeof(dwIDArr)/sizeof(dwIDArr[0]), TRUE);
			GetDlgItem(IDC_BTN_LOGIN)->SetWindowText(ConvertString("Logout"));

			//////////////////////////////////////////////////////////////////////////
			/// 获取诊断服务器能力集
			int nErr = 0;
			char szJson[1024] = {0};
			char szCmd[] = {CFG_CAP_CMD_VIDEODIAGNOSIS_SERVER};
			BOOL bSuccess = CLIENT_QueryNewSystemInfo(
				m_hLoginID, 
				szCmd,
				0, szJson, 
				sizeof(szJson), 
				&nErr,3000);
			printf("(0x%x) CLIENT_QueryNewSystemInfo %s return %s LastError:0x%x !",
				m_hLoginID, szCmd, bSuccess == TRUE ? "successfully":"failure",CLIENT_GetLastError());
			if (bSuccess)
			{
				int nRet = 0;
				memset(&m_stCapsInfo, 0x0, sizeof(m_stCapsInfo));
				BOOL bRet = CLIENT_ParseData(szCmd,szJson,&m_stCapsInfo,sizeof(m_stCapsInfo),&nRet);
				printf("CLIENT_ParseData %s return %s !",szCmd,bRet==TRUE?"successfully":"failure");
				if (bRet)
				{
					reinterpret_cast<CProfileCfg*>(m_pDlgArr[ENUM_DLG_PROFILE])->GetData();
				}
			}
		}
		else if (IDCANCEL == dwRet)
		{
			// 控件不使能
			EnableWindowArr(dwIDArr, sizeof(dwIDArr)/sizeof(dwIDArr[0]), FALSE);
			GetDlgItem(IDC_BTN_LOGIN)->EnableWindow(TRUE);		
		}
		else
		{
			OnCancel();
		}
	}
}

void CIVS_VDemoDlg::GetCmdMembers(std::vector<std::string> & v, char* szInCmd, int nTotalNameCount)
{
	if (m_hLoginID <= 0)
	{
		return;
	}
	BOOL bSuccess = FALSE;
	NET_IN_MEMBERNAME    stInParam = {0}; 
	stInParam.dwSize = sizeof(NET_IN_MEMBERNAME);
	stInParam.szCommand = szInCmd;
	NET_OUT_MEMBERNAME   stOutParam = {0};
	stOutParam.nTotalNameCount = nTotalNameCount;
	stOutParam.pstNames = new NET_ARRAY[stOutParam.nTotalNameCount];
	if (NULL == stOutParam.pstNames)
	{
		goto _clear;
	}
	memset(stOutParam.pstNames, 0, sizeof(NET_ARRAY) * nTotalNameCount);
	stOutParam.dwSize = sizeof(NET_OUT_MEMBERNAME);
	{
		for (int i=0; i< stOutParam.nTotalNameCount;i++)
		{
			stOutParam.pstNames[i].dwSize = sizeof(NET_ARRAY);
			stOutParam.pstNames[i].dwArrayLen = 32;
			stOutParam.pstNames[i].pArray = new char[stOutParam.pstNames[i].dwArrayLen];
			if (NULL == stOutParam.pstNames[i].pArray)
			{
				goto _clear;
			}
			memset(stOutParam.pstNames[i].pArray, 0x0, stOutParam.pstNames[i].dwArrayLen);
		}
	}
	
	bSuccess = CLIENT_GetMemberNames(m_hLoginID, &stInParam, &stOutParam, 3000);
	printf("(0x%x) CLIENT_GetMemberNames %s return %s !",m_hLoginID, stInParam.szCommand, bSuccess == TRUE ? "successfully":"failure");
	if (bSuccess == TRUE)
	{
		for (int i=0; i<stOutParam.nRetNameCount; i++)
		{
			v.push_back(stOutParam.pstNames[i].pArray);
		}
	}

_clear:
	for (int i = 0; i < stOutParam.nTotalNameCount; i++)
	{
		SAFE_DELETE_A(stOutParam.pstNames[i].pArray);
	}
	
	SAFE_DELETE_A(stOutParam.pstNames);
}
