// ClientDemo1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "ClientDemo1.h"
#include "ClientDemo1Dlg.h"
#include "resource.h"
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
// CClientDemo1Dlg dialog

CClientDemo1Dlg::CClientDemo1Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClientDemo1Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CClientDemo1Dlg)
	m_dvrPort = 37777;
	m_strDvrUserName = _T("admin");
	m_strDvrPwd = _T("admin");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bIsListen = FALSE;
	memset(&stuTime,0,sizeof(SYSTEMTIME));
	memset(&stuTimeLater,0,sizeof(SYSTEMTIME));
	m_bNewVer =false;
}

void CClientDemo1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClientDemo1Dlg)
	DDX_Control(pDX, IDC_IPADDRESS_DVRIP, m_dvrIP);
	DDX_Control(pDX, IDC_TAB1, m_Tab);
	DDX_Text(pDX, IDC_EDIT_PORT, m_dvrPort);
	DDV_MinMaxInt(pDX, m_dvrPort, 0, 100000);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_strDvrUserName);
	DDX_Text(pDX, IDC_EDIT_DVRPWD, m_strDvrPwd);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CClientDemo1Dlg, CDialog)
	//{{AFX_MSG_MAP(CClientDemo1Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, OnSelchangeTab1)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_LOGIN, OnBtnLogin)
	ON_BN_CLICKED(IDC_BTN_LOGOUT, OnBtnLogout)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientDemo1Dlg message handlers

BOOL CClientDemo1Dlg::OnInitDialog()
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
	//Initialize TabControl
	InitTabControl();
	//Device default IP
	m_dvrIP.SetAddress(20,2,4,2);
	//Initialize net SDK
	InitNetSDK();
	m_nTimer = SetTimer(1, 1000, NULL);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CClientDemo1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CClientDemo1Dlg::OnPaint() 
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
HCURSOR CClientDemo1Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CClientDemo1Dlg::SetDlgState(CWnd *pWnd, BOOL bShow)
{
	if(bShow)
	{
		pWnd->ShowWindow(SW_SHOW);
		//Display in the middle 
		pWnd->CenterWindow();
	}
	else
	{
		pWnd->ShowWindow(SW_HIDE);
	}
}

void CClientDemo1Dlg::DoTab(int nTab)
{
	//Comfirm nTab is within the threshold
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

	//Display or hide dialogue box 
	SetDlgState(m_pTabUsrManageDlg,bTab[0]);
	if(!m_bNewVer)
	{
		SetDlgState(m_pTabAlarmDlg,bTab[1]);
		SetDlgState(m_pTabNewAlarmDlg,false);
	}
	else
	{
		SetDlgState(m_pTabAlarmDlg,false);
		SetDlgState(m_pTabNewAlarmDlg,bTab[1]);
	}
	SetDlgState(m_pTabQueryAlarm,bTab[2]);
}

void CClientDemo1Dlg::OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int nSelect = m_Tab.GetCurSel();
	if(nSelect>=0)
	{
		DoTab(nSelect);
	}
	*pResult = 0;
}

//Initialize TabControl
void CClientDemo1Dlg::InitTabControl()
{
	m_pTabUsrManageDlg = new CTabUserManageDlg();
	m_pTabAlarmDlg = new CTabAlarmDlg();
	m_pTabNewAlarmDlg =new CNewAlarm();
	m_pTabQueryAlarm =new CQueryAlarmState();
	//Create no-mode dialogue box, specify tag control is the father-window of the no-mode dialogue box.
	m_pTabUsrManageDlg->Create(IDD_DIALOG_USERMANAGE,&m_Tab);
	m_pTabAlarmDlg->Create(IDD_DIALOG_EQUIPALARM,&m_Tab);
	m_pTabNewAlarmDlg->Create(IDD_DIALOG_NEW_ALARM,&m_Tab);
	m_pTabQueryAlarm->Create(IDD_DIALOG_QUERYALARMSTATE,&m_Tab);

	m_Tab.InsertItem(0, ConvertString("User Manage"));
	m_Tab.InsertItem(1, ConvertString("Device Alarm"));
	m_Tab.InsertItem(2, ConvertString("Alarm Query"));
	
	m_Tab.SetMinTabWidth(80);
	m_Tab.SetPadding(CSize(15,8));
	m_Tab.SetCurSel(0);
	DoTab(0);
}

void CClientDemo1Dlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	if(m_pTabUsrManageDlg) delete m_pTabUsrManageDlg;
	if(m_pTabAlarmDlg) delete m_pTabAlarmDlg;
	if(m_pTabNewAlarmDlg) delete m_pTabNewAlarmDlg;
	if(m_pTabQueryAlarm) delete m_pTabQueryAlarm;
	KillTimer(m_nTimer);
	//Stop listening device message 
	if(m_bIsListen)
	{
		m_bIsListen = FALSE;
		CLIENT_StopListen(m_LoginID);
	}
	
	//Log off 
	if(0 != m_LoginID)
	{
		BOOL bLogout = CLIENT_Logout(m_LoginID);
	}
	//Clear SDK and then release occupied resources 
	CLIENT_Cleanup();
}

BOOL CClientDemo1Dlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message == WM_KEYDOWN)
	{
		//Enter
		if(pMsg->wParam == VK_RETURN) return TRUE;
		//ESC
		if(pMsg->wParam == VK_ESCAPE) return TRUE;
	}

	return CDialog::PreTranslateMessage(pMsg);
}

//Initialize net SDK
void CClientDemo1Dlg::InitNetSDK()
{
	BOOL ret = CLIENT_Init(DisConnectFunc, (DWORD)this);
	if (ret)
	{
		//Set message callback function. It is to receive all device messages by default.
		CLIENT_SetDVRMessCallBack(MessCallBack, (DWORD)this);
	}
	else
	{
		MessageBox(ConvertString("Initialize SDK failed!"), ConvertString("Prompt"));
	}
}

//Callback function when device disconnected 
void CALLBACK DisConnectFunc(LLONG lLoginID, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser)
{
	if(dwUser == 0)
	{
		return;
	}
	CClientDemo1Dlg *dlg = (CClientDemo1Dlg *)dwUser;
	dlg->DeviceDisConnect(lLoginID, pchDVRIP,nDVRPort);
}

//Message callback process function. It is a callback of the whole SDK.
BOOL CALLBACK MessCallBack(LONG lCommand, LLONG lLoginID, char *pBuf,
						   DWORD dwBufLen, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser)
{
	if(!dwUser) return FALSE;

	CClientDemo1Dlg *dlg = (CClientDemo1Dlg *)dwUser;
	if(!dlg->NewVer())//Callback function when device version is lower than V2.6.
	{
		return dlg ->ReceiveMessage(lLoginID, lCommand, pchDVRIP, nDVRPort,pBuf, dwBufLen);
	}
	else//Callback fucntion when device version is more than V2.6.
	{
		return dlg ->ReceiveMessageEx(lLoginID, lCommand, pchDVRIP, nDVRPort,pBuf, dwBufLen);
	}
}

//Process when device disconnected 
void CClientDemo1Dlg::DeviceDisConnect(LLONG lLoginID, char *sDVRIP, LONG nDVRPort)
{
	//Add process code when device disconnected 
	MessageBox(ConvertString("Network disconnected!"), ConvertString("Prompt"));
}

//Process when receiving device message.Now it defined alarm message callback only.
BOOL CClientDemo1Dlg::ReceiveMessage(LLONG lLoginID, LONG lCommand, char *pchDVRIP, LONG nDVRPort, char *pBuf, DWORD dwBufLen)
{
	BOOL bRet = FALSE;
	BOOL bIsTimeOut = m_cs.Lock();
	//	GetSystemTime(&stuTimeLater);
	//	int nTimePassed =stuTimeLater.wSecond-stuTime.wSecond;
	//	if(nTimePassed < 0)
	//	{
	//		nTimePassed+= 60;
	//	}
	//	stuTime = stuTimeLater;
	//	char szDebug[128] ={0};
	//	sprintf(szDebug,"command : %x -------Passed time : %d\n\t",lCommand,nTimePassed);
	//	OutputDebugString(szDebug);
	//lCommand = 0x1101;
	if(bIsTimeOut)
	{
		switch(lCommand) {
		case DH_COMM_ALARM:			//General alarm information 
			{
			CommAlarm(pBuf,dwBufLen);
			bRet = TRUE;
			}
			break;
		case DH_SHELTER_ALARM:		//Camera masking alarm 
		//	char pbuf[16];
			//			memset(pbuf,0,16);
			//			memset(pbuf,1,8);
			//			dwBufLen =16;
			
			ShelterAlarm(pBuf,dwBufLen);
			bRet = TRUE;
			break;
		case DH_DISK_FULL_ALARM:	//HDD full alarm 
			DiskFullAlarm(pBuf,dwBufLen);
			bRet = TRUE;
			break;
		case DH_DISK_ERROR_ALARM:	//HDD malfunction alarm 
			DiskError(pBuf,dwBufLen);
			bRet = TRUE;
			break;
		case DH_SOUND_DETECT_ALARM:		//Audio detection alarm 
			SoundAlarm(pBuf,dwBufLen);
			bRet = TRUE;
			break;
		case DH_ALARM_DECODER_ALARM:	//Alarm decoder alarm 
			bRet = TRUE;
			break;
		default:
			break;
		}
		m_cs.Unlock();
	}
	return bRet;
}
//Process when receiving device message. Now it defined alarm message alarm(New section).
BOOL CClientDemo1Dlg::ReceiveMessageEx(LLONG lLoginID, LONG lCommand, char *pchDVRIP, LONG nDVRPort, char *pBuf, DWORD dwBufLen)
{
	BOOL bRet = FALSE;
	BOOL bIsTimeOut = m_cs.Lock();
	CAlarmInfoEx alarmAlarm;
	memset(&alarmAlarm,0,sizeof(CAlarmInfoEx));
	if(bIsTimeOut)
	{
		switch(lCommand)
		{
		case DH_ALARM_ALARM_EX:			//0x2101	//External alarm 
			{
				alarmAlarm.m_AlarmCommand = VIDEO_ALARM_ALARMEX;
				memcpy(&alarmAlarm.m_dwAlarm,pBuf,min(dwBufLen, sizeof(alarmAlarm.m_dwAlarm)));
				bRet = TRUE;
			}
			break;
		case DH_MOTION_ALARM_EX:		//	0x2102	//Motion detection alarm 
			{
				alarmAlarm.m_AlarmCommand = VIDEO_MOTIONDETECT_ALARMEX;
				memcpy(&alarmAlarm.m_dwAlarm,pBuf,min(dwBufLen, sizeof(alarmAlarm.m_dwAlarm)));
				
				bRet = TRUE;
			}
			break;
		case DH_VIDEOLOST_ALARM_EX:		//0x2103	//Video loss alarm 
			{
				alarmAlarm.m_AlarmCommand = VIDEO_VEDIOSHELTER_ALARMEX;
				memcpy(&alarmAlarm.m_dwAlarm,pBuf,min(dwBufLen, sizeof(alarmAlarm.m_dwAlarm)));
				bRet = TRUE;
			}
			break;
		case DH_SHELTER_ALARM_EX:		//	0x2104	//Camera masking alarm 
			{
				alarmAlarm.m_AlarmCommand = VIDEO_SHELTER_ALARMEX;
				memcpy(&alarmAlarm.m_dwAlarm,pBuf,min(dwBufLen, sizeof(alarmAlarm.m_dwAlarm)));
				bRet = TRUE;
			}
			break;
		case DH_SOUND_DETECT_ALARM_EX:	//0x2105	//Audio detection alarm 
			{
				alarmAlarm.m_AlarmCommand = VIDEO_SOUNDDETECT_ALARMEX;
				memcpy(&alarmAlarm.m_stuNewSound,pBuf,min(dwBufLen, sizeof(alarmAlarm.m_stuNewSound)));
				bRet = TRUE;
			}
			break;
		case DH_DISKFULL_ALARM_EX:		//0x2106	//HDD full alarm 
			{
				alarmAlarm.m_AlarmCommand = VIDEO_DISKFULL_ALARMEX;
				memcpy(&alarmAlarm.m_dwAlarm,pBuf,min(dwBufLen, sizeof(alarmAlarm.m_dwAlarm)));
				bRet = TRUE;
			}
			break;
		case DH_DISKERROR_ALARM_EX:		//0x2107	//HDD malfunction alarm 
			{
				alarmAlarm.m_AlarmCommand = VIDEO_DISKERROR_ALARMEX;
				memcpy(&alarmAlarm.m_dwAlarm,pBuf,min(dwBufLen, sizeof(alarmAlarm.m_dwAlarm)));
				bRet = TRUE;
			}
			break;
		case DH_ENCODER_ALARM_EX:		//	0x210A	//Encoder alarm 
			{
				alarmAlarm.m_AlarmCommand = VIDEO_ENCODER_ALARMEX;
				memcpy(&alarmAlarm.m_dwAlarm,pBuf,min(dwBufLen, sizeof(alarmAlarm.m_dwAlarm)));
				bRet = TRUE;
			}
			break;
		case DH_URGENCY_ALARM_EX:		//	0x210B	//Emergency alarm 
			{
				alarmAlarm.m_AlarmCommand = VIDEO_URGENCY_ALARMEX;
				memcpy(&alarmAlarm.m_dwAlarm,pBuf,min(dwBufLen, sizeof(alarmAlarm.m_dwAlarm)));
				bRet = TRUE;
			}
			break;
		case DH_WIRELESS_ALARM_EX:		//0x210C	//Wireless alarm 
			{
				alarmAlarm.m_AlarmCommand = VIDEO_WIRELESS_ALARMEX;
				memcpy(&alarmAlarm.m_dwAlarm,pBuf,min(dwBufLen, sizeof(alarmAlarm.m_dwAlarm)));
				bRet = TRUE;
			}
			break;
		case DH_ALARM_DECODER_ALARM_EX: //0x210E	//Alarm decoder alarm 
			{
				alarmAlarm.m_AlarmCommand = VIDEO_ALARM_DECODER_ALARMEX;
				memcpy(&alarmAlarm.m_stuAlarmDecoderAlarm, pBuf, min(dwBufLen, sizeof(alarmAlarm.m_stuAlarmDecoderAlarm)));
				bRet = TRUE;
			}
			break;
		case DH_STATIC_ALARM_EX:
			{
				alarmAlarm.m_AlarmCommand = VIDEO_STATIC_ALARMEX;
				memcpy(&alarmAlarm.m_dwAlarm, pBuf, min(dwBufLen, sizeof(alarmAlarm.m_dwAlarm)));
				bRet = TRUE;
			}
		case DH_ALARM_ARM_DISARM_STATE:
			{
				alarmAlarm.m_AlarmCommand = VIDEO_ALARM_ARM_DISARMSTATE;
				memcpy(&alarmAlarm.m_stuAlarmArmDisarmstate, pBuf, min(dwBufLen, sizeof(alarmAlarm.m_stuAlarmArmDisarmstate)));
				bRet = TRUE;
			}
		default:
			break;
		}
		
	}
	if (bRet)
	{
		m_ListAlarmInfoEx.AddTail(alarmAlarm);
	}

	m_cs.Unlock();
	return bRet;
}
//Register user to Device 
void CClientDemo1Dlg::OnBtnLogin() 
{
	// TODO: Add your control notification handler code here
	BOOL bValid = UpdateData(TRUE);
	if(bValid)
	{
		int err=0;	//Storage the possible returned error
		char *pchDVRIP;
		CString strDvrIP = GetDvrIP();
		pchDVRIP = (LPSTR)(LPCSTR)strDvrIP;
		WORD wDVRPort=(WORD)m_dvrPort;
		char *pchUserName=(LPSTR)(LPCSTR)m_strDvrUserName;
		char *pchPassword=(LPSTR)(LPCSTR)m_strDvrPwd;
		m_nInAlarmCount = 0;
		//Device information
		NET_DEVICEINFO deviceInfo;
		//Call log in interface 
		m_LoginID = CLIENT_Login(pchDVRIP,wDVRPort,pchUserName,pchPassword,&deviceInfo,&err);
		if(0 == m_LoginID)
		{
			//Display log in failure reason 
			ShowLoginErrorReason(err);
		}
		else
		{
			m_nInAlarmCount = 32;//deviceInfo.byAlarmInPortNum;
			//Initialize user management information 
			m_pTabUsrManageDlg->InitUserManageInfo(m_LoginID);
			GetDlgItem(IDC_BTN_LOGIN)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_LOGOUT)->EnableWindow(TRUE);
			//Search device version£º
			int nProtoVer;
			int nRet;
			BOOL bSuccess = CLIENT_QueryDevState(m_LoginID, DH_DEVSTATE_PROTOCAL_VER, (char*)&nProtoVer, sizeof(int), &nRet, 1000);
			if (bSuccess)
			{
				if (nProtoVer >= 5)		//Current device is V2.6 baseline or higher.
				{
					m_bNewVer = true;
				}
				else
				{
					m_bNewVer =false;
				}
			}
			int nSelect = m_Tab.GetCurSel();
			if(nSelect>=0)
			{
				DoTab(nSelect);
			}
			BOOL bRet;
			//Begin listening device callback information 
			if(!m_bNewVer)//User old interface if device version is below 2.6.
			{
				 bRet = CLIENT_StartListen(m_LoginID);
			}
			else  //If device version is 2.6 or higher then use new interface.
			{
				 bRet = CLIENT_StartListenEx(m_LoginID);
			}
			if(bRet)
			{
				m_bIsListen = TRUE;
			}
		}
	}
}
//Log off device user 
void CClientDemo1Dlg::OnBtnLogout() 
{
	// TODO: Add your control notification handler code here
	//Stop listening device message 
	if(m_bIsListen)
	{
		m_bIsListen = FALSE;
		CLIENT_StopListen(m_LoginID);
	}
	
	BOOL bRet = CLIENT_Logout(m_LoginID);
	//Clear log in handle after logged off 
	if(bRet)
	{
		m_LoginID=0;
		GetDlgItem(IDC_BTN_LOGIN)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_LOGOUT)->EnableWindow(FALSE);
		if ( m_pTabUsrManageDlg!=NULL)
		{
			m_pTabUsrManageDlg->CleanUserManageInfo();
		}
		if ( m_pTabNewAlarmDlg!=NULL)
		{
			m_pTabNewAlarmDlg->CleanAllInfo();
		}
		if ( m_pTabQueryAlarm!=NULL)
		{
			m_pTabQueryAlarm->CleanAllInfo();
		}
		if (m_pTabAlarmDlg != NULL)
		{
			m_pTabAlarmDlg->CleanAllInfo();
		}
		
	}
	else
	{
		MessageBox(ConvertString("Logout failed!"), ConvertString("Prompt"));
	}
}

//Get DVR IP address
CString CClientDemo1Dlg::GetDvrIP()
{
	CString strRet="";
	BYTE nField0,nField1,nField2,nField3;
	m_dvrIP.GetAddress(nField0,nField1,nField2,nField3);
	strRet.Format("%d.%d.%d.%d",nField0,nField1,nField2,nField3);
	return strRet;
}

//Display failure reason 
void CClientDemo1Dlg::ShowLoginErrorReason(int nError)
{
	if(1 == nError)		MessageBox(ConvertString("Invalid password!"), ConvertString("Prompt"));
	else if(2 == nError)	MessageBox(ConvertString("Invalid account!"), ConvertString("Prompt"));
	else if(3 == nError)	MessageBox(ConvertString("Timeout!"), ConvertString("Prompt"));
	else if(4 == nError)	MessageBox(ConvertString("The user has logged in!"), ConvertString("Prompt"));
	else if(5 == nError)	MessageBox(ConvertString("The user has been locked!"), ConvertString("Prompt"));
	else if(6 == nError)	MessageBox(ConvertString("The user has listed into illegal!"), ConvertString("Prompt"));
	else if(7 == nError)	MessageBox(ConvertString("The system is busy!"), ConvertString("Prompt"));
	else if(9 == nError)	MessageBox(ConvertString("You Can't find the network server!"), ConvertString("Prompt"));
	else	MessageBox(ConvertString("Login failed!"), ConvertString("Prompt"));
}

//General alarm information 
void CClientDemo1Dlg::CommAlarm(char *pBuf, DWORD dwBufLen)
{
	NET_CLIENT_STATE *pState = (NET_CLIENT_STATE *)pBuf;
	if (dwBufLen != sizeof(NET_CLIENT_STATE) || pState == NULL)
	{
		return;
	}
	CAlarmInfo alarmInfo;
	alarmInfo.m_nChannelCount = pState->channelcount;
	alarmInfo.m_nAlarmInputCount = pState->alarminputcount;
	alarmInfo.m_AlarmCommand = VIDEO_COMMON_ALARM;
	int i = 0;
	double x = 2;
	//External alarm 
	for(i=0;i<alarmInfo.m_nAlarmInputCount;i++)
	{
		if(1 == pState->alarm[i])
		{
			WORD wAlarmChannel = (WORD)pow(x,i);
			alarmInfo.m_InputAlarm = alarmInfo.m_InputAlarm | wAlarmChannel;
		}
	
	}
	//Video loss 
	for(i=0;i<alarmInfo.m_nChannelCount;i++)
	{
		if(1 == pState->videolost[i])
		{
			WORD wAlarmChannel = (WORD)pow(x,i);
			alarmInfo.m_VideoLost = alarmInfo.m_VideoLost | wAlarmChannel;
		}
	
	}
	//Motion detection 
	for(i=0;i<alarmInfo.m_nChannelCount;i++)
	{
		if(1 == pState->motiondection[i])
		{
			WORD wAlarmChannel = (WORD)pow(x,i);
			alarmInfo.m_MotionDetect = alarmInfo.m_MotionDetect | wAlarmChannel;
		}
		
	}
	//TRACE("wInputAlarm=%d  wVideoLost=%d  wMotionAlarm=%d\n",alarmInfo.m_InputAlarm,alarmInfo.m_VideoLost,alarmInfo.m_MotionDetect);
	m_listAlarmInfo.AddTail(alarmInfo);
}

//Camera masking alarm 
void CClientDemo1Dlg::ShelterAlarm(char *pBuf, DWORD dwBufLen)
{
	if (dwBufLen != 16)
	{
		return;
	}
	CAlarmInfo alarmInfo;
	double x = 2;
	alarmInfo.m_AlarmCommand = VIDEO_VIDEOSHELTER_ALARM;
	for(int i=0;i<16;i++)
	{
		char c = pBuf[i];
		if(1 == c)
		{
			WORD wAlarmChannel = (WORD)pow(x,i);
			alarmInfo.m_ShelterAlarm = alarmInfo.m_ShelterAlarm | wAlarmChannel;
		}
	}
	m_listAlarmInfo.AddTail(alarmInfo);
}

//HDD full alarm 
void CClientDemo1Dlg::DiskFullAlarm(char *pBuf, DWORD dwBufLen)
{
	if (dwBufLen != sizeof(DWORD))
	{
		return;
	}
	CAlarmInfo alarmInfo;
	alarmInfo.m_AlarmCommand = VIDEO_DISKFULL_ALARM;
	DWORD dwDiskFull = *(DWORD*)pBuf;
	if(1 == dwDiskFull)
	{
		alarmInfo.m_DiskFull = TRUE;
	}
	m_listAlarmInfo.AddTail(alarmInfo);
}

//HDD malfunction alarm 
void CClientDemo1Dlg::DiskError(char *pBuf, DWORD dwBufLen)
{
	if (dwBufLen != sizeof(DWORD))
	{
		return;
	}
	CAlarmInfo alarmInfo;
	alarmInfo.m_AlarmCommand = VIDEO_DISKERROR_ALARM;
	alarmInfo.m_DiskError = *(DWORD*)pBuf;
	m_listAlarmInfo.AddTail(alarmInfo);
}

//Video detection alarm 
void CClientDemo1Dlg::SoundAlarm(char *pBuf, DWORD dwBufLen)
{
	if (dwBufLen != 16)
	{
		return;
	}
	CAlarmInfo alarmInfo;	
	double x = 2;
	alarmInfo.m_AlarmCommand = VIDEO_SOUNDDETECT_ALARM;
	for(int i=0;i<16;i++)
	{
		char c = pBuf[i];
		if(1 == c)
		{
			WORD wAlarmChannel = (WORD)pow(x,i);
			alarmInfo.m_SoundDetect = alarmInfo.m_SoundDetect | wAlarmChannel;
		}
	}
	m_listAlarmInfo.AddTail(alarmInfo);
}

void CClientDemo1Dlg::OnTimer(UINT_PTR nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(!m_bNewVer)
	{
		BOOL bIsTimeOut = m_cs.Lock();
		if(bIsTimeOut)
		{
			if(!(m_listAlarmInfo.IsEmpty()))
			{
				//TRACE("%dAAAAAAAAAAAAAAAAAAA\n",m_listAlarmInfo.GetCount());
				POSITION pos = m_listAlarmInfo.GetHeadPosition();
				WORD wInputAlarm = 0;
				WORD wVideoLost = 0;
				WORD wMotionAlarm = 0;
				WORD wVideoShelter = 0;
				WORD wSoundAlarm = 0;
				for(int i=0;i<m_listAlarmInfo.GetCount();i++)
				{
					CAlarmInfo& alarmInfo = m_listAlarmInfo.GetNext(pos);
					EN_DVR_ALARMTYPE enAlarmType = alarmInfo.m_AlarmCommand;
					//TRACE("%dBBBBBBBBBBBBBBBBBBBBB\n",enAlarmType);
					switch(enAlarmType) {
					case VIDEO_COMMON_ALARM:		//General alarm 
						wInputAlarm = m_curAlarmInfo.m_InputAlarm ^ alarmInfo.m_InputAlarm;
						wVideoLost = m_curAlarmInfo.m_VideoLost ^ alarmInfo.m_VideoLost;
						wMotionAlarm = m_curAlarmInfo.m_MotionDetect ^ alarmInfo.m_MotionDetect;
						//TRACE("alarmInfo.wInputAlarm=%d  wVideoLost=%d  wMotionAlarm=%d\n",alarmInfo.m_InputAlarm,alarmInfo.m_VideoLost,alarmInfo.m_MotionDetect);
						//TRACE("VIDEO_COMMON_ALARM.wInputAlarm=%d  wVideoLost=%d  wMotionAlarm=%d\n",wInputAlarm,wVideoLost,wMotionAlarm);
						//Display alarm 
						m_pTabAlarmDlg->SetCommonAlarmInfo(wInputAlarm,wVideoLost,wMotionAlarm,
							alarmInfo.m_nChannelCount,alarmInfo.m_nAlarmInputCount);
						//Save current information 
						m_curAlarmInfo.m_InputAlarm = alarmInfo.m_InputAlarm;
						m_curAlarmInfo.m_VideoLost = alarmInfo.m_VideoLost;
						m_curAlarmInfo.m_MotionDetect = alarmInfo.m_MotionDetect;
						m_curAlarmInfo.m_nAlarmInputCount = alarmInfo.m_nAlarmInputCount;
						m_curAlarmInfo.m_nChannelCount = alarmInfo.m_nChannelCount;
						break;
					case VIDEO_VIDEOSHELTER_ALARM:		//Camera masking alarm 
						wVideoShelter = m_curAlarmInfo.m_ShelterAlarm ^ alarmInfo.m_ShelterAlarm;
						//Display camera masking alarm 
						m_pTabAlarmDlg->SetShelterAlarmInfo(wVideoShelter);
						//Save current information 
						m_curAlarmInfo.m_ShelterAlarm = alarmInfo.m_ShelterAlarm;
						break;
					case VIDEO_SOUNDDETECT_ALARM:		//Audio alarm 
						wSoundAlarm = m_curAlarmInfo.m_SoundDetect ^ alarmInfo.m_SoundDetect;
						//Display audio alarm 
						m_pTabAlarmDlg->SetSoundAlarmInfo(wSoundAlarm);
						//Save current message 
						m_curAlarmInfo.m_SoundDetect = alarmInfo.m_SoundDetect;
						break;
					case VIDEO_DISKFULL_ALARM:			//Alarm when HDD capacity is insufficient
						//Display insufficient HDD capacity alarm 
						m_pTabAlarmDlg->SetDiskFullAlarmInfo(alarmInfo.m_DiskFull);
						//Save current message 
						m_curAlarmInfo.m_DiskFull = alarmInfo.m_DiskFull;
						break;
					case VIDEO_DISKERROR_ALARM:		//HDD malfunction alarm 
						//Display HDD malfunction alarm 
						m_pTabAlarmDlg->SetDiskErrorAlarmInfo(alarmInfo.m_DiskError);
						//Save current message 
						m_curAlarmInfo.m_DiskError = alarmInfo.m_DiskError;
						break;
					default:
						break;
					}
				}
				m_listAlarmInfo.RemoveAll();
			}
			m_cs.Unlock();
		}
	}
	else
	{  //define VER_2_600_0
		//////////////////////////////////////////////////////////////////////////
		//		new alarm section
		//////////////////////////////////////////////////////////////////////////
		BOOL bIsTimeOut = m_cs.Lock();
		if(bIsTimeOut)
		{
			if(!(m_ListAlarmInfoEx.IsEmpty()))
			{
				//TRACE("%dAAAAAAAAAAAAAAAAAAA\n",m_listAlarmInfo.GetCount());
				POSITION pos = m_ListAlarmInfoEx.GetHeadPosition();
				for(int i=0;i<m_ListAlarmInfoEx.GetCount();i++)
				{
					CAlarmInfoEx& alarmInfoEx = m_ListAlarmInfoEx.GetNext(pos);
					EN_DVR_ALARMTYPE_EX enAlarmType = alarmInfoEx.m_AlarmCommand;
					//TRACE("%dBBBBBBBBBBBBBBBBBBBBB\n",enAlarmType);
					switch(enAlarmType) 
					{
					case VIDEO_ALARM_ALARMEX://External alarm 
						m_pTabNewAlarmDlg->SetAlarmInfo(alarmInfoEx.m_dwAlarm, &(m_pTabNewAlarmDlg->m_dlgOutput), m_nInAlarmCount);
						break;
					case VIDEO_MOTIONDETECT_ALARMEX://Motion detection alarm 
						m_pTabNewAlarmDlg->SetAlarmInfo(alarmInfoEx.m_dwAlarm, &(m_pTabNewAlarmDlg->m_dlgDynamic), m_nInAlarmCount);
						break;
					case VIDEO_VEDIOSHELTER_ALARMEX://Video loss alarm 
						m_pTabNewAlarmDlg->SetAlarmInfo(alarmInfoEx.m_dwAlarm, &(m_pTabNewAlarmDlg->m_dlgVideoLost), m_nInAlarmCount);
						break;
					case VIDEO_SHELTER_ALARMEX://Camera masking alarm 
						m_pTabNewAlarmDlg->SetAlarmInfo(alarmInfoEx.m_dwAlarm, &(m_pTabNewAlarmDlg->m_dlgShelter), m_nInAlarmCount);
						break;
					case VIDEO_ENCODER_ALARMEX://encoder alarm 
						m_pTabNewAlarmDlg->SetAlarmInfo(alarmInfoEx.m_dwAlarm, &(m_pTabNewAlarmDlg->m_dlgCoder), m_nInAlarmCount);
						break;	
					case VIDEO_URGENCY_ALARMEX://Emergency alarm 
						m_pTabNewAlarmDlg->SetAlarmInfo(alarmInfoEx.m_dwAlarm, &(m_pTabNewAlarmDlg->m_dlgUrgency), m_nInAlarmCount);
						break;
					case VIDEO_WIRELESS_ALARMEX://Wireless alarm 
						m_pTabNewAlarmDlg->SetAlarmInfo(alarmInfoEx.m_dwAlarm, &(m_pTabNewAlarmDlg->m_dlgWireless), m_nInAlarmCount);
						break;
					case VIDEO_SOUNDDETECT_ALARMEX://Audio detection alarm 
						m_pTabNewAlarmDlg->SetSoundAlarmInfo(alarmInfoEx.m_stuNewSound,IDC_EDIT_SOUND_DETECT);
						break;
					case VIDEO_DISKFULL_ALARMEX://HDD full alarm 
						m_pTabNewAlarmDlg->SetAlarmInfo(alarmInfoEx.m_dwAlarm, &(m_pTabNewAlarmDlg->m_dlgDiskFull), m_nInAlarmCount);
						break; 
					case VIDEO_DISKERROR_ALARMEX://HDD malfunction alarm 
						m_pTabNewAlarmDlg->SetAlarmInfo(alarmInfoEx.m_dwAlarm, &(m_pTabNewAlarmDlg->m_dlgDiskError), m_nInAlarmCount);
						break; 
					case VIDEO_STATIC_ALARMEX://HDD malfunction alarm 
						m_pTabNewAlarmDlg->SetAlarmInfo(alarmInfoEx.m_dwAlarm, &(m_pTabNewAlarmDlg->m_dlgStatic), m_nInAlarmCount);
						break; 
					case VIDEO_ALARM_DECODER_ALARMEX://Alarm decoder alarm
						m_pTabNewAlarmDlg->SetAlarmDecoderAlarm(alarmInfoEx.m_stuAlarmDecoderAlarm);
						break;
					case VIDEO_ALARM_ARM_DISARMSTATE://Alarm decoder alarm
						m_pTabNewAlarmDlg->SetAlarmAlarmArmDisarmState(alarmInfoEx.m_stuAlarmArmDisarmstate);
						break;
					default :
						break;
					}
				}
			}
		}
		m_ListAlarmInfoEx.RemoveAll();
		m_cs.Unlock();
	}
	CDialog::OnTimer(nIDEvent);
}























































































































































































































































