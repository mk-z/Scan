// Video Analyse ConfigurationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Video Analyse Configuration.h"
#include "Video Analyse ConfigurationDlg.h"

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
// CVideoAnalyseConfigurationDlg dialog

CVideoAnalyseConfigurationDlg::CVideoAnalyseConfigurationDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVideoAnalyseConfigurationDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVideoAnalyseConfigurationDlg)
	m_strIP = _T("10.61.3.7");/*10.42.1.150 10.24.1.62*/
	m_strPassWord = _T("admin");
	m_dwPort = 37777;
	m_strUserName = _T("admin");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_lLoginID = 0;
	m_pTrafficSceneDlg = NULL;
	m_pAtmSceneDlg = NULL;
	m_nChannelCount = 0;

	for (int i=0;i<MAX_CHANNEL_NUM;i++)
	{
		m_pDeviceCap[i] = new CFG_CAP_ANALYSE_INFO;
	}
}

void CVideoAnalyseConfigurationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVideoAnalyseConfigurationDlg)
	DDX_Control(pDX, IDC_TAB_ATTRIBUTE, m_ctlMainTab);
	DDX_Text(pDX, IDC_EDIT_IP, m_strIP);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassWord);
	DDX_Text(pDX, IDC_EDIT_PORT, m_dwPort);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_strUserName);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CVideoAnalyseConfigurationDlg, CDialog)
	//{{AFX_MSG_MAP(CVideoAnalyseConfigurationDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, OnButtonLogin)
	ON_BN_CLICKED(IDC_BUTTON_LOGOUT, OnButtonLogout)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_ATTRIBUTE, OnSelchangeTabAttribute)
	ON_COMMAND(WM_USER+1, DeviceDisConnect)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVideoAnalyseConfigurationDlg message handlers

BOOL CVideoAnalyseConfigurationDlg::OnInitDialog()
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
	InitTabControl();
	InitNetSDK();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CVideoAnalyseConfigurationDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CVideoAnalyseConfigurationDlg::OnPaint() 
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
HCURSOR CVideoAnalyseConfigurationDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CVideoAnalyseConfigurationDlg::OnButtonLogin() 
{		
		UpdateData(TRUE);
		int nErr = 0;	//Storage the possible error return value.
		WORD wDVRPort = (WORD)m_dwPort;
		char *pchUserName = (LPSTR)(LPCSTR)m_strUserName;
		char *pchPassword = (LPSTR)(LPCSTR)m_strPassWord;
		NET_DEVICEINFO stuDeviceInfo;
		
		//Call log in interface 
		LLONG lRet = CLIENT_Login(m_strIP.GetBuffer(0),wDVRPort,pchUserName,pchPassword,&stuDeviceInfo,&nErr);
		if(0 != lRet)
		{
			if (stuDeviceInfo.byDVRType != NET_ITC_SERIAL 
				&& stuDeviceInfo.byDVRType != NET_DVR_ATM)
			{
				CLIENT_Logout(lRet);
				AfxMessageBox(ConvertString(_T("This device does't support ITC or ATM!")));
				return;
			}

			m_lLoginID = lRet;
			m_nChannelCount = stuDeviceInfo.byChanNum > MAX_CHANNEL_NUM ? MAX_CHANNEL_NUM : stuDeviceInfo.byChanNum;

			for(int i = 0; i < m_nChannelCount; i++)
			{
				GetCap(i, m_pDeviceCap[i]);
			}

			if (stuDeviceInfo.byDVRType == NET_ITC_SERIAL)
			{
				// add trafficScene
				CConfigTrafficScene* pConfigTrafficScene = new CConfigTrafficScene();
				AddPage(NET_ITC_SERIAL,"TrafficScene", pConfigTrafficScene, IDD_CONFIG_TRAFFICSCENE);
				m_pTrafficSceneDlg->Init(m_nChannelCount);
			}
			else
			{
				// add normal trafficScene
				CConfigAtmScene* pCfgScene = new CConfigAtmScene();
				if (NULL != pCfgScene)
				{
					AddPage(0,"Scene", pCfgScene, IDD_CONFIG_ATM_SCENE);
					m_pAtmSceneDlg->Init(m_nChannelCount);
				}
			}
		
			m_cModuleConfigDlg.Init(m_nChannelCount);
			m_cRulesConfigDlg.Init(m_nChannelCount);

			GetDlgItem(IDC_BUTTON_LOGIN)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON_LOGOUT)->EnableWindow(TRUE);
			m_ctlMainTab.SetCurSel(0);
			DoTab(0);
		}
		else
		{
			// Display log in failure reason 
			MessageBox(ConvertString("Login failed"),ConvertString("Prompt"));
		}
}

BOOL CVideoAnalyseConfigurationDlg::AddPage(DWORD dwDevType,CString strTitle, CDialog* dlgPage, UINT uID)
{
	if(NULL == dlgPage)
	{
		return FALSE;
	}
	

	switch(dwDevType)
	{
	case NET_ITC_SERIAL:
		{
			m_pTrafficSceneDlg = (CConfigTrafficScene* )dlgPage;
			
			CRect childRect;
			m_ctlMainTab.GetClientRect(childRect);
			childRect.top += 20;
			childRect.bottom -= 4;
			childRect.left += 4;
			childRect.right -= 4;
			
			m_pTrafficSceneDlg->Create(uID, &m_ctlMainTab);
			m_pTrafficSceneDlg->MoveWindow(childRect);
			m_ctlMainTab.InsertItem(2, ConvertString(strTitle));
		}
		break;
	case 0:
		{
			m_pAtmSceneDlg = (CConfigAtmScene*)dlgPage;

			CRect childRect;
			m_ctlMainTab.GetClientRect(childRect);
			childRect.top += 20;
			childRect.bottom -= 4;
			childRect.left += 4;
			childRect.right -= 4;
			
			m_pAtmSceneDlg->Create(uID, &m_ctlMainTab);
			m_pAtmSceneDlg->MoveWindow(childRect);
			m_ctlMainTab.InsertItem(2, ConvertString(strTitle));
		}
		break;
	default:
		break;
	}
	
	return TRUE;
}

void CVideoAnalyseConfigurationDlg::OnButtonLogout() 
{
	ClearSource();
}

void CVideoAnalyseConfigurationDlg::ClearSource()
{
	if(m_lLoginID != 0)
	{
		m_cRulesConfigDlg.StopRealPlay();
		
		CLIENT_Logout(m_lLoginID);
		DeletePage();
		m_cModuleConfigDlg.Clear();
		m_cRulesConfigDlg.Clear();
		m_lLoginID = 0;
	}
	
	GetDlgItem(IDC_BUTTON_LOGIN)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_LOGOUT)->EnableWindow(FALSE);
}

void CVideoAnalyseConfigurationDlg::OnClose() 
{
	ClearSource();
	CLIENT_Cleanup(); //ÊÍ·Åsdk×ÊÔ´
	CDialog::OnClose();
}

BOOL CVideoAnalyseConfigurationDlg::DeletePage()
{
	if(NULL != m_pTrafficSceneDlg)
	{
		int nSel = m_ctlMainTab.GetCurSel();
		m_pTrafficSceneDlg->ShowWindow(FALSE);
		m_pTrafficSceneDlg->CloseWindow();
		m_ctlMainTab.DeleteItem(2);
		m_pTrafficSceneDlg->Clear();
		delete m_pTrafficSceneDlg;
		m_pTrafficSceneDlg = NULL;
		
		if(nSel == 2)
		{
			m_ctlMainTab.SetCurSel(1);
			DoTab(1);
		}
		else
		{
			DoTab(nSel);
		}
		Invalidate(TRUE);
		return TRUE;
	}

	if (NULL != m_pAtmSceneDlg)
	{
		int nSel = m_ctlMainTab.GetCurSel();
		m_pAtmSceneDlg->ShowWindow(FALSE);
		m_pAtmSceneDlg->CloseWindow();
		m_ctlMainTab.DeleteItem(2);
		delete m_pAtmSceneDlg;
		m_pAtmSceneDlg = NULL;

		if (nSel == 2)
		{
			m_ctlMainTab.SetCurSel(1);
			DoTab(1);
		}
		else
		{
			DoTab(nSel);
		}
		Invalidate(TRUE);
		return TRUE;
	}
	
	return FALSE;
}

void CVideoAnalyseConfigurationDlg::OnSelchangeTabAttribute(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int nSelect = m_ctlMainTab.GetCurSel();
	if(nSelect>=0)
	{
		DoTab(nSelect);
	}
	
	*pResult = 0;
}

//Initialize SDK
void CVideoAnalyseConfigurationDlg::InitNetSDK()
{
	BOOL bSuccess = CLIENT_Init(DisConnectFunc, (DWORD)this);
	if (bSuccess)
	{
		CLIENT_SetDVRMessCallBack(MessCallBackFunc, (DWORD)this);
	}
	else
	{
		MessageBox(ConvertString("Initialize SDK failed!"), ConvertString("Prompt"));
	}
}

//Call function when device disconnected
void CALLBACK DisConnectFunc(LLONG lLoginID, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser)
{
	if(dwUser == 0)
	{
		return;
	}
	CVideoAnalyseConfigurationDlg *dlg = (CVideoAnalyseConfigurationDlg *)dwUser;
	dlg->PostMessage(WM_COMMAND, WM_USER+1, 0);
}

//Disposal when device disconnected 
void CVideoAnalyseConfigurationDlg::DeviceDisConnect()
{
	//Add device disconnection process code 
	MessageBox(ConvertString("Network disconnected!"), ConvertString("Prompt"));
	
}


BOOL CALLBACK MessCallBackFunc(LONG lCommand, LLONG lLoginID, char *pBuf, DWORD dwBufLen, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser)
{
	return TRUE;
}

void CVideoAnalyseConfigurationDlg::GetCap(int nChannel, CFG_CAP_ANALYSE_INFO *pstuChannelCap)
{
	// get device cap
	memset(pstuChannelCap, 0, sizeof(CFG_CAP_ANALYSE_INFO));
	char *szOutBuffer = new char[1024*1024];
	int nErr = 0;
	
	BOOL bSuccess = CLIENT_QueryNewSystemInfo(m_lLoginID, CFG_CAP_CMD_VIDEOANALYSE, nChannel, szOutBuffer, 32*1024, &nErr);
	if (bSuccess)
	{
		int nRetLen = 0;
		BOOL bRet = CLIENT_ParseData(CFG_CAP_CMD_VIDEOANALYSE, szOutBuffer, (char*)pstuChannelCap, sizeof(CFG_CAP_ANALYSE_INFO), &nRetLen);
		if (bRet == FALSE)
		{
			MessageBox(ConvertString("Parser data error"), ConvertString("Prompt"));
			return;
		}
	}
	else
	{
		MessageBox(ConvertString("get device cap failed!"), ConvertString("Prompt"));
	}

	delete szOutBuffer;
	szOutBuffer = NULL;
}

void CVideoAnalyseConfigurationDlg::InitTabControl()
{
	CRect childRect;
	m_ctlMainTab.GetClientRect(&childRect);
 	childRect.top += 20;
 	childRect.bottom -= 4;
 	childRect.left += 4;
 	childRect.right -= 4;
	
	//Create non-mode dialogue box. Specified tag is non-mode dialogue box father window.
	m_cModuleConfigDlg.Create(IDD_CONFIG_MODULE, &m_ctlMainTab);
	m_cModuleConfigDlg.MoveWindow(childRect);
	m_cRulesConfigDlg.Create(IDD_CONFIG_RULES, &m_ctlMainTab);
	m_cRulesConfigDlg.MoveWindow(childRect);

	m_ctlMainTab.InsertItem(0, ConvertString("Module Configuration"));
	m_ctlMainTab.InsertItem(1, ConvertString("Rule Configuration"));
	
	m_ctlMainTab.SetCurSel(0);
	DoTab(0);
}

void CVideoAnalyseConfigurationDlg::DoTab(int nTab)
{
	//Check nTab value is within the threshold
	if(nTab>2)
	{
		nTab=2;
	}
	if(nTab<0)
	{
		nTab=0;
	}
	
	BOOL bTab[3];
	bTab[0]=bTab[1]=bTab[2]=FALSE;
	bTab[nTab]=TRUE;
	if (m_lLoginID != 0)
	{
		m_cRulesConfigDlg.StopRealPlay();
	}
	
	if (nTab  == 1 && m_lLoginID != 0)
	{
		m_cRulesConfigDlg.StartRealPay();
	}

	
	//Display or hide dialogue box 
	SetDlgState(&m_cModuleConfigDlg,bTab[0]);
	SetDlgState(&m_cRulesConfigDlg,bTab[1]);
	if (m_pTrafficSceneDlg != NULL)
	{
		SetDlgState(m_pTrafficSceneDlg,bTab[2]);
	}
	if (m_pAtmSceneDlg != NULL)
	{
		SetDlgState(m_pAtmSceneDlg,bTab[2]);
	}
}

void CVideoAnalyseConfigurationDlg::SetDlgState(CWnd *pWnd, BOOL bShow)
{
	if (pWnd == NULL)
	{
		return;
	}

	if(bShow)
	{
		pWnd->ShowWindow(SW_SHOW);
	}
	else
	{
		pWnd->ShowWindow(SW_HIDE);
	}
}

CFG_CAP_ANALYSE_INFO* CVideoAnalyseConfigurationDlg::GetChannelCapInfo(int nChannel)
{
	return m_pDeviceCap[nChannel];
}

long CVideoAnalyseConfigurationDlg::GetLoginID()
{
	return m_lLoginID;
}

BOOL CVideoAnalyseConfigurationDlg::GetTrafficScene(int nChannel, CFG_ANALYSEGLOBAL_INFO &stuAnalysGlobalInfo)
{
	int nErr = 0;
	char szOutBuffer[32*1024] = {0};
	
	// get global info
	BOOL bSuccess = CLIENT_GetNewDevConfig(m_lLoginID, CFG_CMD_ANALYSEGLOBAL, nChannel,
		szOutBuffer, 32*1024, &nErr);
	if (bSuccess)
	{
		int nRetLen = 0;
		BOOL bRet = CLIENT_ParseData(CFG_CMD_ANALYSEGLOBAL, szOutBuffer, (char*)&stuAnalysGlobalInfo, 
			sizeof(CFG_ANALYSEGLOBAL_INFO), &nRetLen);
		if (bRet == FALSE)
		{
			MessageBox(ConvertString("Parser data error"), ConvertString("Prompt"));
			return FALSE;
		}
	}//if(bSuccess)
	else
	{
		MessageBox(ConvertString("Get TrafficScene failed"), ConvertString("Prompt"));
		return FALSE;
	}

	return TRUE;
}

void CVideoAnalyseConfigurationDlg::SetTrafficScene(int nChannelId, CFG_ANALYSEGLOBAL_INFO &stuAnalysGlobalInfo)
{
	int nRestart = 0;
	int nError = 0;
	char szOutBuffer[32*1024] = {0};

	// save global info
	BOOL bRet = CLIENT_PacketData(CFG_CMD_ANALYSEGLOBAL, (char*)&stuAnalysGlobalInfo, 
		sizeof(CFG_ANALYSEGLOBAL_INFO), szOutBuffer, 32*1024);
	
	if (bRet == FALSE)
	{
		MessageBox(ConvertString("Pack data failed!"), ConvertString("Prompt"));
	}
	else
	{
		BOOL bSuccess = CLIENT_SetNewDevConfig(m_lLoginID, CFG_CMD_ANALYSEGLOBAL, nChannelId, szOutBuffer, 32*1024, &nError, &nRestart, 3000);		
		if (bSuccess)
		{

			MessageBox(ConvertString("Save successfully!"), ConvertString("Prompt"));
		}
		else
		{
			MessageBox(ConvertString("Save TrafficScene failed!"), ConvertString("Prompt"));
		}		
	}
}

BOOL CVideoAnalyseConfigurationDlg::GetModule(int nChannel, CFG_ANALYSEMODULES_INFO &stuAnalysModuleInfo)
{
	int nErr = 0;
	char szOutBuffer[32*1024] = {0};
	
	// get module info
	BOOL bSuccess = CLIENT_GetNewDevConfig(m_lLoginID, CFG_CMD_ANALYSEMODULE, nChannel,
		szOutBuffer, 32*1024, &nErr);
	if (bSuccess)
	{
		int nRetLen = 0;
		BOOL bRet = CLIENT_ParseData(CFG_CMD_ANALYSEMODULE, szOutBuffer, (char*)&stuAnalysModuleInfo, 
			sizeof(CFG_ANALYSEMODULES_INFO), &nRetLen);
		if (bRet == FALSE)
		{
			MessageBox(ConvertString("Parser data error"), ConvertString("Prompt"));
			return FALSE;
		}
	}//if(bSuccess)
	else
	{
		MessageBox(ConvertString("Get Module info failed!"), ConvertString("Prompt"));
		return FALSE;
	}
	
	return TRUE;
}

void CVideoAnalyseConfigurationDlg::SetModule(int nChannelId, CFG_ANALYSEMODULES_INFO &stuAnalysModuleInfo)
{
	int nRestart = 0;
	int nError = 0;
	char szOutBuffer[32*1024] = {0};
	
	// save module info
	BOOL bRet = CLIENT_PacketData(CFG_CMD_ANALYSEMODULE, (char*)&stuAnalysModuleInfo, 
		sizeof(CFG_ANALYSEMODULES_INFO), szOutBuffer, 32*1024);
	
	if (bRet == FALSE)
	{
		MessageBox(ConvertString("Pack data failed!"), ConvertString("Prompt"));
	}
	else
	{
		BOOL bSuccess = CLIENT_SetNewDevConfig(m_lLoginID, CFG_CMD_ANALYSEMODULE, nChannelId, szOutBuffer, 32*1024, &nError, &nRestart, 3000);		
		if (bSuccess)
		{
			MessageBox(ConvertString("Save successfully!"), ConvertString("Prompt"));
		}
		else
		{
			MessageBox(ConvertString("Save Module info failed!"), ConvertString("Prompt"));
		}		
	}
}

BOOL CVideoAnalyseConfigurationDlg::GetRule(int nChannel, CFG_ANALYSERULES_INFO &stuAnalysRuleInfo)
{
	int nErr = 0;
	char szOutBuffer[32*1024] = {0};
	
	// get module info
	BOOL bSuccess = CLIENT_GetNewDevConfig(m_lLoginID, CFG_CMD_ANALYSERULE, nChannel,
		szOutBuffer, 32*1024, &nErr, 2000);
	if (bSuccess)
	{
		int nRetLen = 0;
		BOOL bRet = CLIENT_ParseData(CFG_CMD_ANALYSERULE, szOutBuffer, (char*)&stuAnalysRuleInfo, 
			sizeof(CFG_ANALYSERULES_INFO), &nRetLen);
		if (bRet == FALSE)
		{
			MessageBox(ConvertString("Parser data error"), ConvertString("Prompt"));
			return FALSE;
		}
	}//if(bSuccess)
	else
	{
		MessageBox(ConvertString("Get Rule info error!"), ConvertString("Prompt"));
		return FALSE;
	}
	
	return TRUE;
}

void CVideoAnalyseConfigurationDlg::SetRule(int nChannelId, CFG_ANALYSERULES_INFO stuAnalysRuleInfo)
{
	int nRestart = 0;
	int nError = 0;
	char szOutBuffer[32*1024] = {0};
	
	// save module info
	BOOL bRet = CLIENT_PacketData(CFG_CMD_ANALYSERULE, (char*)&stuAnalysRuleInfo, 
		sizeof(CFG_ANALYSERULES_INFO), szOutBuffer, 32*1024);
	
	if (bRet == FALSE)
	{
		MessageBox(ConvertString("Pack data failed!"), ConvertString("Prompt"));
	}
	else
	{
		BOOL bSuccess = CLIENT_SetNewDevConfig(m_lLoginID, CFG_CMD_ANALYSERULE, nChannelId, szOutBuffer, 32*1024, &nError, &nRestart, 3000);		
		if (bSuccess)
		{
			MessageBox(ConvertString("Save successfully!"), ConvertString("Prompt"));
		}
		else
		{
			MessageBox(ConvertString("Save Rule info failed!"), ConvertString("Prompt"));
		}		
	}
}
