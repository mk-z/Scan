// IVSFDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IVSFDemo.h"
#include "IVSFDemoDlg.h"
#include "LoginDlg.h"
#include "AlarmOnDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "PlayApi.h"

CPlayAPI g_PlayAPI;

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
// CIVSFDemoDlg dialog

CIVSFDemoDlg::CIVSFDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIVSFDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIVSFDemoDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_pdlgPreview= NULL;
	m_pdlgConfig = NULL;
	m_lDevLogHandle = 0;
	m_nChannelCount = 0;

	g_PlayAPI.LoadPlayDll();
	memset(m_lAlarmLoadHandle, 0, sizeof(m_lAlarmLoadHandle));
}

void CIVSFDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIVSFDemoDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CIVSFDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CIVSFDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_LOG, OnButtonLog)
	ON_BN_CLICKED(IDC_BUTTON_CONFIG, OnButtonConfig)
	ON_BN_CLICKED(IDC_BUTTON_PREVIWE, OnButtonPreviwe)
	ON_BN_CLICKED(IDC_BUTTON_ALARMON, OnButtonAlarmon)
	ON_MESSAGE(WM_USER_ALAMR_COME, OnAlarmCome)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIVSFDemoDlg message handlers

BOOL CIVSFDemoDlg::OnInitDialog()
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

	// init dlgs
	CRect cBackGroundRect;
	GetDlgItem(IDC_STATIC_BACKGROUND)->GetWindowRect(&cBackGroundRect);
	ScreenToClient(&cBackGroundRect);
	
	m_pdlgPreview = new CPreviewDlg;
	if (m_pdlgPreview != NULL)
	{
		m_pdlgPreview->Create(CPreviewDlg::IDD, this);
		m_pdlgPreview->MoveWindow(&cBackGroundRect, TRUE);
		m_pdlgPreview->ShowWindow(SW_SHOW);
		m_pdlgPreview->Init(this, m_lDevLogHandle);
	}
	m_pdlgConfig = new CConfigDlg;
	if (m_pdlgConfig != NULL)
	{
		m_pdlgConfig->Create(CConfigDlg::IDD, this);
		m_pdlgConfig->MoveWindow(&cBackGroundRect, TRUE);
		m_pdlgConfig->ShowWindow(SW_HIDE);
		m_pdlgConfig->Init(m_lDevLogHandle);
	}

	// sdk init
	CLIENT_Init(CIVSFDemoDlg::OnDisConnect, (LDWORD)this);

	// show login dlg
	LogInDev();

	// createDir
	char szFolder[1024] = {0};
	bool bRet = GetModulePath("dhnetsdk.dll", szFolder);
	if (bRet)
	{
		sprintf(szFolder+strlen(szFolder), "PCStore\\");
	}
	//Create direct any way
	::CreateDirectory(szFolder, NULL);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CIVSFDemoDlg::OnDisConnect(LLONG lLoginID, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser)
{
	CIVSFDemoDlg *pdlg =  (CIVSFDemoDlg*)dwUser;
	pdlg->LogOutDev();
	pdlg->MessageBox(ConvertString("device disconnect!"), ConvertString("Prompt"));
	return;
}

void CIVSFDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CIVSFDemoDlg::OnPaint() 
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
HCURSOR CIVSFDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

////////////////////////////////////// log device////////////////////////////////////
void CIVSFDemoDlg::OnButtonLog() 
{
	CString strButton;
	GetDlgItem(IDC_BUTTON_LOG)->GetWindowText(strButton);
	if (ConvertString(strButton) == ConvertString(LOGOUT))
	{
		LogOutDev();	
	}
	else if (ConvertString(strButton) == ConvertString(LOGIN))
	{
		BOOL bret = LogInDev();
		if (bret)
		{
			if (m_pdlgPreview)
			{
				m_pdlgPreview->ShowWindow(SW_SHOW);
			}
		}
	}
}

BOOL CIVSFDemoDlg::LogInDev()
{
	CLoginDlg dlgLogin;
	if (dlgLogin.DoModal() == IDOK)
	{
		//get device's info
		m_lDevLogHandle = dlgLogin.GetLogHandle();
		if (m_lDevLogHandle == 0)
		{
			return FALSE;
		}
		// tell the device type
		BYTE byDevType = dlgLogin.GetDevType();
		if (byDevType != NET_IVS_F)
		{
			MessageBox(ConvertString("this device is not a ivs-f!"), ConvertString("Prompt"));
			LogOutDev();
			return TRUE;
		}
		
		m_nChannelCount = dlgLogin.GetChannelCount();

		if (m_pdlgPreview != NULL)
		{
			m_pdlgPreview->Init(this, m_lDevLogHandle);
			m_pdlgPreview->SetChannelCount(m_nChannelCount);
		}

		if (m_pdlgConfig)
		{
			m_pdlgConfig->Init(m_lDevLogHandle);
			m_pdlgConfig->SetChannelNum(m_nChannelCount);
		}
		
		// enable button
		GetDlgItem(IDC_BUTTON_LOG)->SetWindowText(ConvertString(LOGOUT));
		GetDlgItem(IDC_BUTTON_PREVIWE)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_CONFIG)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_ALARMON)->EnableWindow(TRUE);
	}

	return TRUE;
}

void CIVSFDemoDlg::LogOutDev()
{
	for (int i = 0; i < m_nChannelCount; i++)
	{
		if (m_lAlarmLoadHandle[i])
		{
			CLIENT_StopLoadPic(m_lAlarmLoadHandle[i]);
			m_lAlarmLoadHandle[i] = 0;
		}
	}

	if (m_pdlgPreview)
	{
		m_pdlgPreview->Clean();
	}

	// 登出设备，取消其它操作
	if(m_lDevLogHandle != 0)
	{
		BOOL bRet =CLIENT_Logout(m_lDevLogHandle);
		if (!bRet)
		{
			MessageBox(ConvertString("Log out device failed"), ConvertString("Prompt"));
		}
	}


	GetDlgItem(IDC_BUTTON_LOG)->SetWindowText(ConvertString(LOGIN));
	GetDlgItem(IDC_BUTTON_PREVIWE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CONFIG)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_ALARMON)->EnableWindow(FALSE);

	if(m_pdlgConfig)
	{
		m_pdlgConfig->ShowWindow(SW_HIDE);
	}
	if (m_pdlgPreview)
	{
		m_pdlgPreview->ShowWindow(SW_HIDE);
	}
}


///////////////////////////////face recognition config///////////////////////////////////////////
 
void CIVSFDemoDlg::OnButtonConfig() 
{
	if (m_pdlgPreview)
	{
		m_pdlgPreview->ShowWindow(SW_HIDE);
		m_pdlgPreview->OperateStream(FALSE);
	}

	if (m_pdlgConfig)
	{
		m_pdlgConfig->ShowWindow(SW_SHOW);
     	m_pdlgConfig->OpenChannelStream();
	    m_pdlgConfig->GetConfigInfo();
	}

}

/////////////////////////////////////video preview/////////////////////////////////////
 
void CIVSFDemoDlg::OnButtonPreviwe() 
{
	if (m_pdlgConfig)
	{
		m_pdlgConfig->ShowWindow(SW_HIDE);
		m_pdlgConfig->CloseStream();
	}

	if (m_pdlgPreview)
	{
		m_pdlgPreview->ShowWindow(SW_SHOW);
		m_pdlgPreview->OperateStream(TRUE);
	}

}

//////////////////////////////////Subscribe picture////////////////////////////////////////

void CIVSFDemoDlg::OnButtonAlarmon() 
{
	CAlarmOnDlg dlgAlarmOn;
	dlgAlarmOn.Init(m_nChannelCount, this, m_lAlarmLoadHandle);
	if (dlgAlarmOn.DoModal() == IDOK)
	{
	}
}

int  CIVSFDemoDlg::RealLoadPicCallback (LLONG lAnalyzerHandle, DWORD dwAlarmType, void* pAlarmInfo, BYTE *pBuffer, DWORD dwBufSize, LDWORD dwUser, int nSequence, void *userdata)
{
	int nAlarmInfoSize = 0;
	if (dwAlarmType == EVENT_IVS_FACERECOGNITION)
	{
		nAlarmInfoSize = sizeof(DEV_EVENT_FACERECOGNITION_INFO);
	}
	else
	{
		return 0;
	}

	EventPara* eventData = new EventPara;
	if (eventData == NULL)
	{
		return 0;
	}

	eventData->lAnalyzerHandle = lAnalyzerHandle;
	eventData->dwAlarmType = dwAlarmType;
	eventData->dwBufSize = dwBufSize;
	eventData->nSequence = nSequence;

	eventData->pBuffer = new BYTE[dwBufSize];
	if (eventData->pBuffer == NULL)
	{
		delete eventData;
		return 0;
	}
	memcpy(eventData->pBuffer, pBuffer, dwBufSize);
	
	eventData->pAlarmInfo = new char[nAlarmInfoSize];
	if (eventData->pAlarmInfo == NULL)
	{
		delete []eventData->pBuffer;
		delete eventData;
		return 0;
	}
	memcpy(eventData->pAlarmInfo, pAlarmInfo, nAlarmInfoSize);

	CIVSFDemoDlg* This = (CIVSFDemoDlg*)dwUser;
	HWND hwnd = This->GetSafeHwnd();
	::PostMessage(hwnd, WM_USER_ALAMR_COME, (DWORD)(eventData), 0);
	return 0;
}

LRESULT CIVSFDemoDlg::OnAlarmCome(WPARAM wParam, LPARAM lParam)
{
	EventPara* ep = (EventPara*)wParam;
	if (ep != NULL)
	{
		this->OnReceiveEvent(ep->lAnalyzerHandle, ep->dwAlarmType, ep->pAlarmInfo, ep->pBuffer, ep->dwBufSize, ep->nSequence);
		if (ep->pBuffer)
		{
			delete[] ep->pBuffer;
		}
		if (ep->pAlarmInfo)
		{
			delete[] ep->pAlarmInfo;
		}
		delete ep;
	}

	return 0;
}

void CIVSFDemoDlg::OnReceiveEvent(LONG lAnalyzerHandle, DWORD dwAlarmType, void* pAlarmInfo, BYTE *pBuffer, DWORD dwBufSize, int nSequence)
{
	if (m_pdlgPreview)
	{
		m_pdlgPreview->ShowAlarmInfo(dwAlarmType, pAlarmInfo, pBuffer, dwBufSize);
	}
	
}

void CIVSFDemoDlg::AlarmLoad(int* pChannelSel, BOOL bStart)
{
	if (bStart)
	{
		for (int i = 0; i < m_nChannelCount; i++)
		{
			if (pChannelSel[i] != 0)
			{
				m_lAlarmLoadHandle[i] = CLIENT_RealLoadPictureEx(m_lDevLogHandle, i, EVENT_IVS_FACERECOGNITION, TRUE, CIVSFDemoDlg::RealLoadPicCallback, (DWORD)this, NULL);
				if (m_lAlarmLoadHandle[i] == 0)
				{
					MessageBox(ConvertString("Subscribe picture failed!"), ConvertString("Prompt"));
				}
			}
		}
	}
	else
	{
		BOOL bRet = FALSE;
		for (int i = 0; i < m_nChannelCount; i++)
		{
			if (pChannelSel[i] != 0 && m_lAlarmLoadHandle[i] != 0)
			{
				bRet = CLIENT_StopLoadPic(m_lAlarmLoadHandle[i]);
				if (!bRet)
				{
					MessageBox(ConvertString("Stop Subscribe picture failed!"), ConvertString("Prompt"));
				}
				m_lAlarmLoadHandle[i] = 0;
			}
		}
	}

}

//////////////////////////////////////////clean up sdk////////////////////////////////
void CIVSFDemoDlg::OnDestroy() 
{
	CDialog::OnDestroy();

	for (int i = 0; i < m_nChannelCount; i++)
	{
		if (m_lAlarmLoadHandle[i])
		{
			CLIENT_StopLoadPic(m_lAlarmLoadHandle[i]);
		}
	}

	if (m_pdlgConfig)
	{
		if (m_pdlgConfig->GetSafeHwnd())
		{
			m_pdlgConfig->DestroyWindow();
		}
		delete m_pdlgConfig;
	}
	if (m_pdlgPreview)
	{
		if (m_pdlgPreview->GetSafeHwnd())
		{
			m_pdlgPreview->DestroyWindow();
		}
		delete m_pdlgPreview;
	}

	if(m_lDevLogHandle != 0)
	{
		CLIENT_Logout(m_lDevLogHandle);
	}
	CLIENT_Cleanup(); 
}
