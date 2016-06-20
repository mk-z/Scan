// ClientDemo3Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "ClientDemo3.h"
#include "ClientDemo3Dlg.h"
#include "MessageText.h"
#include "dhplay.h"
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
// CClientDemo3Dlg dialog

CClientDemo3Dlg::CClientDemo3Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClientDemo3Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CClientDemo3Dlg)
	m_strUserName = _T("admin");
	m_strPwd = _T("admin");
	m_nPort = 37777;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_LoginID = 0;
	m_nChannelCount = 0;
	m_hPlayBack = 0;
	m_dwTotalSize = 0;
	m_dwCurValue = 0;
	m_nTimer = 0;
	m_pDownLoadFile = 0;
	m_pDownLoadByTime = 0;
	m_PlayBackType = EM_FILEBACK;
	m_ePlayMode = EM_DIRECTMODE;
	m_bSpeedCtrl = FALSE;
	m_nChannelID =  -1;
    m_eSpeed = SPEED_NORMAL;
    m_PlayBackDirection = EM_PLAYBACK_DIRECTION_FORWARD;
}

void CClientDemo3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClientDemo3Dlg)
	DDX_Control(pDX, IDC_TAB1, m_Tab);
	DDX_Control(pDX, IDC_IPADDRESS_DVRIP, m_ctlDvrIP);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_strUserName);
	DDX_Text(pDX, IDC_EDIT_DVRPWD, m_strPwd);
	DDX_Text(pDX, IDC_EDIT_PORT, m_nPort);
	DDX_Control(pDX, IDC_DAYTIMEPICKSDKCTRL1, m_DayTimePickSdk);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CClientDemo3Dlg, CDialog)
	//{{AFX_MSG_MAP(CClientDemo3Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_LOGIN, OnBtnLogin)
	ON_BN_CLICKED(IDC_BTN_LOGOUT, OnBtnLogout)
	ON_WM_DESTROY()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, OnSelchangeTab1)
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_PLAY, OnButtonPlay)
	ON_BN_CLICKED(IDC_BUTTON_SLOW, OnButtonSlow)
	ON_BN_CLICKED(IDC_BUTTON_FAST, OnButtonFast)
	ON_BN_CLICKED(IDC_BUTTON_FRAMETO, OnButtonFrameto)
	ON_BN_CLICKED(IDC_BUTTON_RESET, OnButtonReset)
	ON_BN_CLICKED(IDC_BUTTON_NORMALSPEED, OnButtonNormalspeed)
	ON_BN_CLICKED(IDC_BUTTON_CAPTURE_PICTURE, OnButtonCapturePicture)
	ON_BN_CLICKED(IDC_BUTTON_PLAYREVERSE, OnButtonPlayreverse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientDemo3Dlg message handlers

BOOL CClientDemo3Dlg::OnInitDialog()
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
	//Device default IP
    m_ctlDvrIP.SetAddress(171, 35, 0, 130);
	InitTabControl();
	InitNetSDK();
    /*
    if (0 == m_nTimer)
    {
	    m_nTimer = SetTimer(1, 500, NULL);
    }
    */
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CClientDemo3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CClientDemo3Dlg::OnPaint() 
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
HCURSOR CClientDemo3Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//Log in user to the device
void CClientDemo3Dlg::OnBtnLogin() 
{
	// TODO: Add your control notification handler code here
	BOOL bValid = UpdateData(TRUE);
	if(bValid)
	{
		int err=0;	//Storage the possible returned errror value
		char *pchDVRIP;
		CString strDvrIP = GetDvrIP();
		pchDVRIP = (LPSTR)(LPCSTR)strDvrIP;
		WORD wDVRPort=(WORD)m_nPort;
		char *pchUserName=(LPSTR)(LPCSTR)m_strUserName;
		char *pchPassword=(LPSTR)(LPCSTR)m_strPwd;
		//Device message
		NET_DEVICEINFO deviceInfo;
		//Call log in interface
		long lRet = CLIENT_Login(pchDVRIP,wDVRPort,pchUserName,pchPassword,&deviceInfo,&err);
		if(0 == lRet)
		{
			//Display log in failed reason
			ShowLoginErrorReason(err);
		}
		else
		{
			m_LoginID = lRet;
			int nRetLen = 0;
			NET_DEV_CHN_COUNT_INFO stuChn = { sizeof(NET_DEV_CHN_COUNT_INFO) };
			stuChn.stuVideoIn.dwSize = sizeof(stuChn.stuVideoIn);
			stuChn.stuVideoOut.dwSize = sizeof(stuChn.stuVideoOut);
			CLIENT_QueryDevState(m_LoginID, DH_DEVSTATE_DEV_CHN_COUNT, (char*)&stuChn, stuChn.dwSize, &nRetLen);
	        m_nChannelCount = __max(deviceInfo.byChanNum,stuChn.stuVideoIn.nMaxTotal);
			//m_nChannelCount = deviceInfo.byChanNum;
			//Set channel menu
            //m_pTabMultyDlg->SetTotalChannel(m_nChannelCount);
			m_pTabFileDlg->InitComboBox(m_nChannelCount,m_LoginID);
			m_pTabTimeDlg->InitComboBox(m_nChannelCount,m_LoginID);
            //m_pTabMultyDlg->InitComboBox(m_nChannelCount);

			GetDlgItem(IDC_BTN_LOGIN)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_LOGOUT)->EnableWindow(TRUE);  

			DH_DEV_ENABLE_INFO stuEnableInfo = {0};
			nRetLen = 0;
			BOOL bRet = CLIENT_QuerySystemInfo(m_LoginID, ABILITY_DEVALL_INFO, (char*)&stuEnableInfo, sizeof(DH_DEV_ENABLE_INFO), &nRetLen);
			if (bRet)
			{
				if(stuEnableInfo.IsFucEnable[EN_PLAYBACK_SPEED_CTRL] != 0)
				{
					m_bSpeedCtrl = TRUE;
				}
			}

            int nSelect = m_Tab.GetCurSel();
            if(nSelect>=0)
            {
                DoTab(nSelect);
	        }
		}
	}
}

//Log off device user
void CClientDemo3Dlg::OnBtnLogout() 
{
	// TODO: Add your control notification handler code here
	OnButtonStop();
	//Close playback

	//Reset process bar
	m_dwTotalSize = 0;
	m_dwCurValue = 0;
	//Close download
	if(0 != m_pDownLoadFile)
	{
		CLIENT_StopDownload(m_pDownLoadFile);
		m_pDownLoadFile = 0;
	}

	if(0 != m_pDownLoadByTime)
	{
		CLIENT_StopDownload(m_pDownLoadByTime);
		m_pDownLoadByTime = 0;
	}

	

	BOOL bRet = CLIENT_Logout(m_LoginID);
	//Log off and then clear log in handle
	if(bRet)
	{
		m_LoginID=0;
		m_nChannelCount = 0;
		//Set channel menu 
		m_pTabFileDlg->InitComboBox(m_nChannelCount,m_LoginID);
		m_pTabTimeDlg->InitComboBox(m_nChannelCount,m_LoginID);
        m_pTabMultyDlg->DisableComboBox();

        //Log off and then clear
        m_pTabFileDlg->Clean();
        m_pTabTimeDlg->Clean();
        //m_pTabMultyDlg->Clean();

		GetDlgItem(IDC_BTN_LOGIN)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_LOGOUT)->EnableWindow(FALSE);
        GetDlgItem(IDC_BUTTON_CAPTURE_PICTURE)->EnableWindow(FALSE);
        
	}
	else
	{
		MessageBox(ConvertString("Logout failed!"), ConvertString("Prompt"));
	}
}

//Initialize net SDK
void CClientDemo3Dlg::InitNetSDK()
{
	BOOL ret = CLIENT_Init(DisConnectFunc, (DWORD)this);
	if (!ret)
	{
		MessageBox(ConvertString("Initialize SDK failed!"), ConvertString("Prompt"));
	}
    
}

//Callback function when device disconnected
void CALLBACK DisConnectFunc(LONG lLoginID, char *pchDVRIP, LONG nDVRPort, DWORD dwUser)
{
	if(dwUser == 0)
	{
		return;
	}
	CClientDemo3Dlg *dlg = (CClientDemo3Dlg *)dwUser;
	dlg->DeviceDisConnect(lLoginID, pchDVRIP,nDVRPort);
}

//Process when device disconnected.
void CClientDemo3Dlg::DeviceDisConnect(LONG lLoginID, char *sDVRIP, LONG nDVRPort)
{
	//Add device disconnection process code
	MessageBox(ConvertString("Network disconnected!"), ConvertString("Prompt"));
	
}

void CClientDemo3Dlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	if(0 != m_hPlayBack)
	{
		CLIENT_StopPlayBack(m_hPlayBack);
	}

	if(0 != m_pDownLoadFile)
	{
		//Close download
		CLIENT_StopDownload(m_pDownLoadFile);
	}
	if(0 != m_pDownLoadByTime)
	{
		CLIENT_StopDownload(m_pDownLoadByTime);
	}

	//Log off
	if(0 != m_LoginID)
	{
		BOOL bLogout = CLIENT_Logout(m_LoginID);
	}
	
	//Clear SDK and then release occupied resources.
	CLIENT_Cleanup();

	if (m_pTabFileDlg)
	{
		m_pTabFileDlg->DestroyWindow();
		delete m_pTabFileDlg;
	}

	if (m_pTabTimeDlg)
	{
		m_pTabTimeDlg->DestroyWindow();
		delete m_pTabTimeDlg;
	}
}

//Get DVR IP address
CString CClientDemo3Dlg::GetDvrIP()
{
	CString strRet="";
	BYTE nField0,nField1,nField2,nField3;
	m_ctlDvrIP.GetAddress(nField0,nField1,nField2,nField3);
	strRet.Format("%d.%d.%d.%d",nField0,nField1,nField2,nField3);
	return strRet;
}

//Display log in failure reason
void CClientDemo3Dlg::ShowLoginErrorReason(int nError)
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

//Initialize TabControl 
void CClientDemo3Dlg::InitTabControl()
{
	m_pTabFileDlg = new CPlaybackByFile();
	m_pTabTimeDlg = new CPlaybackByTime();
    m_pTabMultyDlg = new CPlaybackMulty(this, m_LoginID);

	//Create no-mode dialogue box. Specified tag control is the main window of the no-mode dialogue box.
	m_pTabFileDlg->Create(IDD_PLAYBACK_RECORDFILE,&m_Tab);
	m_pTabTimeDlg->Create(IDD_PLAYBACK_BYTIME,&m_Tab);
	m_pTabMultyDlg->Create(IDD_PLAYBACK_MULTY, &m_Tab);

	m_Tab.InsertItem(0, ConvertString("Playback by file"));
	m_Tab.InsertItem(1, ConvertString("Playback by time"));
    m_Tab.InsertItem(2, ConvertString("Playback by multy"));
	
	m_Tab.SetMinTabWidth(-1);
	m_Tab.SetPadding(CSize(15,4));
	m_Tab.SetCurSel(0);
	DoTab(0);
}

void CClientDemo3Dlg::DoTab(int nTab)
{
	//Confirm nTab value is within the threshold.
	if (nTab < 0 || nTab > 3)
    {
        nTab = 0;
    }

    if (2 == nTab)
    {
        m_pTabMultyDlg->EnableComboBox(m_nChannelCount);
    }

    BOOL bTab[3];
    for (int i = 0; i < 3; ++i)
    {
        if (i == nTab)
        {
            bTab[i]=TRUE;
        }
        else
        {
            bTab[i]=FALSE;
        }
    }
	
	//Display or hide dialogue box
	SetDlgState(m_pTabFileDlg,bTab[0]);
	SetDlgState(m_pTabTimeDlg,bTab[1]);
    SetDlgState(m_pTabMultyDlg,bTab[2]);
}

void CClientDemo3Dlg::SetDlgState(CWnd *pWnd, BOOL bShow)
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

void CClientDemo3Dlg::OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int nSelect = m_Tab.GetCurSel();
	if(nSelect>=0)
	{
		DoTab(nSelect);
	}
	*pResult = 0;
}

//Play in file mode
void CClientDemo3Dlg::PlayBackByFile(NET_RECORDFILE_INFO fileInfo, int nChannelId)
{
    if (0 != m_LoginID)
    {
        if(0 == m_nTimer)
        {
            m_nTimer = SetTimer(1, 500, NULL);
        }
        
        InitTimeOcx(fileInfo);
        
		int recordStreamType = fileInfo.bRecType == 0 ? 1 : 2;
		if (!CLIENT_SetDeviceMode(m_LoginID, DH_RECORD_STREAM_TYPE, &recordStreamType))
		{
			MessageBox(ConvertString("Set stream type failed"), ConvertString("Prompt"));
		}

        HWND hPlayBack = GetDlgItem(IDC_SCREEN_PLAYBACK)->m_hWnd;
        long lHandle = CLIENT_PlayBackByTime(m_LoginID,nChannelId,&m_PlayBackByTimeStart
            ,&m_PlayBackByTimeEnd,hPlayBack,PlayCallBack,(DWORD)this);
        if(0 != lHandle)
        {
            m_nChannelID = nChannelId;
            m_hPlayBack = lHandle;
            m_ePlayMode = EM_DIRECTMODE;
            SetDlgItemText(IDC_BUTTON_PLAY, ConvertString("Pause"));
            m_PlayBackType = EM_FILEBACK;
            m_PlayBackDirection = EM_PLAYBACK_DIRECTION_FORWARD;
            m_nReverseMode = 0;
            ChangeSpeedStatus(0);
            SetPlayControlButton(TRUE);
        }
        else
        {
            MessageBox(ConvertString("Playback failed!"), ConvertString("Prompt"));
	    }

        CString strTest;
        GetDlgItemText(IDC_BUTTON_PLAYREVERSE, strTest);
        if (strTest != ConvertString("PlayReverse"))
        {
            SetDlgItemText(IDC_BUTTON_PLAYREVERSE, ConvertString("PlayReverse"));
        }

    }

}

//Process status callback
void CALLBACK PlayCallBack(LONG lPlayHandle, DWORD dwTotalSize, DWORD dwDownLoadSize, DWORD dwUser)
{
	if(0 != dwUser)
	{
		CClientDemo3Dlg *dlg = (CClientDemo3Dlg *)dwUser;
		dlg->ReceivePlayPos(lPlayHandle, dwTotalSize, dwDownLoadSize);
	}
}

//Process status process 
void CClientDemo3Dlg::ReceivePlayPos(LONG lPlayHandle, DWORD dwTotalSize, DWORD dwDownLoadSize)
{
	//TRACE("%.1f%%, %d   %d\n", (float)dwDownLoadSize/dwTotalSize*100, dwTotalSize, dwDownLoadSize);
	if(lPlayHandle == m_hPlayBack)
	{
		m_dwTotalSize = dwTotalSize;
		m_dwCurValue = dwDownLoadSize;
	}
	else if(lPlayHandle == m_pDownLoadFile)
	{
		//Download process in file mode
		if(-1 != dwDownLoadSize)
		{
			m_pTabFileDlg->m_dwTotalSize = dwTotalSize;
			m_pTabFileDlg->m_dwCurValue = dwDownLoadSize;
		}
		else
		{
			m_pTabFileDlg->m_dwTotalSize = 0;
			m_pTabFileDlg->m_dwCurValue = 0;
			if(0 != m_pDownLoadFile)
			{
				CLIENT_StopDownload(m_pDownLoadFile);
				m_pDownLoadFile = 0;
			}
			m_pTabFileDlg->SetDlgItemText(IDC_BUTTON_DOWNLOADBYFILE,ConvertString("Download"));
		}
	}
}

void CClientDemo3Dlg::SetPlayControlButton(BOOL bFlag)
{
    GetDlgItem(IDC_BUTTON_PLAY)->EnableWindow(bFlag);
    GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(bFlag);
    GetDlgItem(IDC_BUTTON_CAPTURE_PICTURE)->EnableWindow(bFlag);

    if (EM_FILEBACK == m_PlayBackType || EM_TIMEBACK == m_PlayBackType)
    {
        GetDlgItem(IDC_BUTTON_SLOW)->EnableWindow(bFlag);
        GetDlgItem(IDC_BUTTON_NORMALSPEED)->EnableWindow(bFlag);
        GetDlgItem(IDC_BUTTON_FAST)->EnableWindow(bFlag);
        GetDlgItem(IDC_BUTTON_RESET)->EnableWindow(bFlag);
        GetDlgItem(IDC_BUTTON_FRAMETO)->EnableWindow(bFlag);
    }

    if (EM_SERVERMODE == m_ePlayMode)
    {
        GetDlgItem(IDC_BUTTON_PLAYREVERSE)->EnableWindow(bFlag);
    }
}

//Stop play
void CClientDemo3Dlg::OnButtonStop() 
{
	// TODO: Add your control notification handler code here
	if(0 != m_hPlayBack)
	{
		ClosePlayBack();
		m_hPlayBack = 0;
		GetDlgItem(IDC_SCREEN_PLAYBACK)->Invalidate();
		m_DayTimePickSdk.SetCurrentTime(m_StartTime);
        SetPlayControlButton(FALSE);
	}

    if (EM_FILEBACK == m_PlayBackType && EM_SERVERMODE == m_ePlayMode)
    {
        SetDlgItemText(IDC_BUTTON_PLAY,ConvertString("PlayForward"));
    }
    else
    {
        SetDlgItemText(IDC_BUTTON_PLAY,ConvertString("Play"));
    }
	
	m_dwTotalSize = 0;
	m_dwCurValue = 0;

	if(0 != m_nTimer)
	{
		KillTimer(m_nTimer);
		m_nTimer = 0;
	}
}

void CClientDemo3Dlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent == m_nTimer)
	{
		if (m_dwTotalSize != 0 && m_dwCurValue != -1)
		{
			int nIndex = m_pTabTimeDlg->m_ctlPlayMode.GetCurSel();
		    //PlayBackMode ePlayMode = (PlayBackMode)(m_pTabTimeDlg->m_ctlPlayMode.GetItemData(nIndex));
			if (m_ePlayMode == EM_DIRECTMODE)
			{
				NET_TIME ntTime = {0};
				NET_TIME ntTimeStart = {0};
				NET_TIME ntTimeEnd = {0};
				BOOL bRet = CLIENT_GetPlayBackOsdTime(m_hPlayBack, &ntTime, &ntTimeStart, &ntTimeEnd);
				DWORD dw = CLIENT_GetLastError();
				if (bRet)
				{
					if (ntTime.dwDay == m_PlayBackByTimeStart.dwDay)
					{
						LONG lCurrentTime = ntTime.dwHour*3600 
							+ ntTime.dwMinute*60 
							+ ntTime.dwSecond;
						TRACE("%d H,%d M,%d S\n",ntTime.dwHour,ntTime.dwMinute,ntTime.dwSecond);
						
						long lEndTime = m_PlayBackByTimeEnd.dwHour*3600
							+ m_PlayBackByTimeEnd.dwMinute*60
							+ m_PlayBackByTimeEnd.dwSecond;
						if (lCurrentTime >= lEndTime)
						{
							//m_DayTimePickSdk.SetCurrentTime(m_StartTime);
                            TRACE("CClientDemo3Dlg::OnTimer(UINT nIDEvent)  currenttime > endtime, stop playback\n");
							OnButtonStop();
							return;
						}
						m_DayTimePickSdk.SetCurrentTime(lCurrentTime);
					}
				}
			}
			else
			{
				NET_TIME nettime = {0};
				int nReturnLen = 0;
				int nsize = sizeof(NET_TIME);
				BOOL bRet = PLAY_QueryInfo(1, PLAY_CMD_GetTime, (char *)&nettime, sizeof(NET_TIME), &nReturnLen);
				if (bRet)
				{
					if (nettime.dwDay == m_PlayBackByTimeStart.dwDay)
					{
						LONG lCurrentTime = nettime.dwHour*3600 + nettime.dwMinute*60 + nettime.dwSecond;
						
						long lEndTime = m_PlayBackByTimeEnd.dwHour*3600
							+ m_PlayBackByTimeEnd.dwMinute*60
							+ m_PlayBackByTimeEnd.dwSecond;
						if (lCurrentTime >= lEndTime)
						{
							//m_DayTimePickSdk.SetCurrentTime(m_StartTime);
                            TRACE("CClientDemo3Dlg::OnTimer(UINT nIDEvent)  currenttime > endtime, stop playback\n");
							OnButtonStop();
							return;
						}
						m_DayTimePickSdk.SetCurrentTime(lCurrentTime);
                        //TRACE("CClientDemo3Dlg::OnTimer(UINT nIDEvent)  SetCurrentTime, lCurrentTime2\n");
					}
				}
			}
		}
		else if (m_dwTotalSize != 0 && m_dwCurValue == -1)
		{
			BOOL bPlayEnd = FALSE;
	//		if (m_ePlayMode == EM_DIRECTMODE)
	//		{
	//			bPlayEnd = TRUE;
	//		}

            if (m_PlayBackDirection == EM_PLAYBACK_DIRECTION_REVERSE)
            {
                // 倒放模式下，放到文件起始位置，由于播放库实现无法知道播放结束，总会出现几十帧数据无法播放出来
                // 所以不判断 PLAY_GetBufferValue(1, BUF_VIDEO_RENDER)
                if (PLAY_GetSourceBufferRemain(1) == 0)
                {
                    bPlayEnd = TRUE;
                }
            }
            else
            {
                if (PLAY_GetSourceBufferRemain(1) == 0 && PLAY_GetBufferValue(1, BUF_VIDEO_RENDER) == 0)
                {
                    bPlayEnd = TRUE;
                }
            }

			if (bPlayEnd)
			{
				m_dwTotalSize = 0;
				m_dwCurValue = 0;
                if (EM_FILEBACK == m_PlayBackType && EM_SERVERMODE == m_ePlayMode)
                {
                    SetDlgItemText(IDC_BUTTON_PLAY,ConvertString("PlayForward"));
                }
                else
                {
                    SetDlgItemText(IDC_BUTTON_PLAY,ConvertString("Play"));
                }

                if (0 != m_hPlayBack)
				{
					OnButtonStop();
				}
			}
		}
		else
		{

		}
	}
	
	CDialog::OnTimer(nIDEvent);
}

//Download in file mode 
BOOL CClientDemo3Dlg::DownLoadByFile(NET_RECORDFILE_INFO fileInfo,BOOL bLoad)
{
	BOOL bRet = FALSE;
	if(bLoad)
	{
		//Download 
		if(0 != m_LoginID)
		{
			if(0 != m_pDownLoadFile)
			{
				//Close download
				BOOL bSuccess = CLIENT_StopDownload(m_pDownLoadFile);
				if(bSuccess)
				{
					m_pDownLoadFile = 0;
				}
				else
				{
					MessageBox(ConvertString("Stop download failed!"), ConvertString("Prompt"));
				}
			}
			
			CFileDialog dlg(FALSE,"*.dav","download.dav",OFN_OVERWRITEPROMPT|OFN_HIDEREADONLY,
				"dav(*.dav)|*.dav|All File(*.dav)|*.*||",this);
			if(dlg.DoModal() == IDOK)
			{
				CString strFilePathName = dlg.GetPathName();
				long lRet = CLIENT_DownloadByRecordFile(m_LoginID, &fileInfo, 
					(LPSTR)(LPCSTR)strFilePathName,PlayCallBack, (DWORD)this);
				if(0 != lRet)
				{
					m_pDownLoadFile = lRet;
					bRet = TRUE;
				}
				else
				{
					LastError();
					MessageBox(ConvertString("Download failed!"), ConvertString("Prompt"));
					DeleteFile(strFilePathName);
				}
			}
		}
	}
	else
	{
		//Stop download
		if(0 != m_pDownLoadFile)
		{
			BOOL bSuccess = CLIENT_StopDownload(m_pDownLoadFile);
			if(bSuccess)
			{
				m_pDownLoadFile = 0;
				bRet = TRUE;
			}
			else
			{
				MessageBox(ConvertString("Stop download failed!"), ConvertString("Prompt"));
			}
		}
	}
	return bRet;
}

//Display function execution failure reason
void CClientDemo3Dlg::LastError()
{
DWORD dwError = CLIENT_GetLastError();
	switch(dwError)
	{
	case NET_NOERROR:					GetDlgItem(IDC_LAST_ERROR)->SetWindowText(ConvertString(ERROR_NET_NOERROR));
		break;
	case NET_ERROR:						GetDlgItem(IDC_LAST_ERROR)->SetWindowText(ConvertString(ERROR_NET_ERROR));
		break;
	case NET_SYSTEM_ERROR:				GetDlgItem(IDC_LAST_ERROR)->SetWindowText(ConvertString(ERROR_NET_SYSTEM_ERROR));
		break;
	case NET_NETWORK_ERROR:				GetDlgItem(IDC_LAST_ERROR)->SetWindowText(ConvertString(ERROR_NET_NETWORK_ERROR));
		break;
	case NET_DEV_VER_NOMATCH:			GetDlgItem(IDC_LAST_ERROR)->SetWindowText(ConvertString(ERROR_NET_DEV_VER_NOMATCH));
		break;
	case NET_INVALID_HANDLE:			GetDlgItem(IDC_LAST_ERROR)->SetWindowText(ConvertString(ERROR_NET_INVALID_HANDLE));
		break;
	case NET_OPEN_CHANNEL_ERROR:		GetDlgItem(IDC_LAST_ERROR)->SetWindowText(ConvertString(ERROR_NET_OPEN_CHANNEL_ERROR));
		break;
	case NET_CLOSE_CHANNEL_ERROR:		GetDlgItem(IDC_LAST_ERROR)->SetWindowText(ConvertString(ERROR_NET_CLOSE_CHANNEL_ERROR));
		break;
	case NET_ILLEGAL_PARAM:				GetDlgItem(IDC_LAST_ERROR)->SetWindowText(ConvertString(ERROR_NET_ILLEGAL_PARAM));
		break;
	case NET_SDK_INIT_ERROR:			GetDlgItem(IDC_LAST_ERROR)->SetWindowText(ConvertString(ERROR_NET_SDK_INIT_ERROR));
		break;
	case NET_SDK_UNINIT_ERROR:			GetDlgItem(IDC_LAST_ERROR)->SetWindowText(ConvertString(ERROR_NET_SDK_UNINIT_ERROR));
		break;
	case NET_RENDER_OPEN_ERROR:			GetDlgItem(IDC_LAST_ERROR)->SetWindowText(ConvertString(ERROR_NET_RENDER_OPEN_ERROR));
		break;
	case NET_DEC_OPEN_ERROR:			GetDlgItem(IDC_LAST_ERROR)->SetWindowText(ConvertString(ERROR_NET_DEC_OPEN_ERROR));
		break;
	case NET_DEC_CLOSE_ERROR:			GetDlgItem(IDC_LAST_ERROR)->SetWindowText(ConvertString(ERROR_NET_DEC_CLOSE_ERROR));
		break;
	case NET_MULTIPLAY_NOCHANNEL:		GetDlgItem(IDC_LAST_ERROR)->SetWindowText(ConvertString(ERROR_NET_MULTIPLAY_NOCHANNEL));
		break;
	case NET_TALK_INIT_ERROR:			GetDlgItem(IDC_LAST_ERROR)->SetWindowText(ConvertString(ERROR_NET_TALK_INIT_ERROR));
		break;
	case NET_TALK_NOT_INIT:				GetDlgItem(IDC_LAST_ERROR)->SetWindowText(ConvertString(ERROR_NET_TALK_NOT_INIT));
		break;	
	case NET_TALK_SENDDATA_ERROR:		GetDlgItem(IDC_LAST_ERROR)->SetWindowText(ConvertString(ERROR_NET_TALK_SENDDATA_ERROR));
		break;
	case NET_NO_TALK_CHANNEL:			GetDlgItem(IDC_LAST_ERROR)->SetWindowText(ConvertString(ERROR_NET_NO_TALK_CHANNEL));
		break;
	case NET_NO_AUDIO:					GetDlgItem(IDC_LAST_ERROR)->SetWindowText(ConvertString(ERROR_NET_NO_AUDIO));
		break;								
	case NET_REAL_ALREADY_SAVING:		GetDlgItem(IDC_LAST_ERROR)->SetWindowText(ConvertString(ERROR_NET_REAL_ALREADY_SAVING));
		break;
	case NET_NOT_SAVING:				GetDlgItem(IDC_LAST_ERROR)->SetWindowText(ConvertString(ERROR_NET_NOT_SAVING));
		break;
	case NET_OPEN_FILE_ERROR:			GetDlgItem(IDC_LAST_ERROR)->SetWindowText(ConvertString(ERROR_NET_OPEN_FILE_ERROR));
		break;
	case NET_PTZ_SET_TIMER_ERROR:		GetDlgItem(IDC_LAST_ERROR)->SetWindowText(ConvertString(ERROR_NET_PTZ_SET_TIMER_ERROR));
		break;
	case NET_RETURN_DATA_ERROR:			GetDlgItem(IDC_LAST_ERROR)->SetWindowText(ConvertString(ERROR_NET_RETURN_DATA_ERROR));
		break;
	case NET_INSUFFICIENT_BUFFER:		GetDlgItem(IDC_LAST_ERROR)->SetWindowText(ConvertString(ERROR_NET_INSUFFICIENT_BUFFER));
		break;
	case NET_NOT_SUPPORTED:				GetDlgItem(IDC_LAST_ERROR)->SetWindowText(ConvertString(ERROR_NET_NOT_SUPPORTED));
		break;
	case NET_NO_RECORD_FOUND:			GetDlgItem(IDC_LAST_ERROR)->SetWindowText(ConvertString(ERROR_NET_NO_RECORD_FOUND));
		break;	
	case NET_LOGIN_ERROR_PASSWORD:		GetDlgItem(IDC_LAST_ERROR)->SetWindowText(ConvertString(ERROR_NET_LOGIN_ERROR_PASSWORD));
		break;
	case NET_LOGIN_ERROR_USER:			GetDlgItem(IDC_LAST_ERROR)->SetWindowText(ConvertString(ERROR_NET_LOGIN_ERROR_USER));
		break;
	case NET_LOGIN_ERROR_TIMEOUT:		GetDlgItem(IDC_LAST_ERROR)->SetWindowText(ConvertString(ERROR_NET_LOGIN_ERROR_TIMEOUT));
		break;
	case NET_LOGIN_ERROR_RELOGGIN:		GetDlgItem(IDC_LAST_ERROR)->SetWindowText(ConvertString(ERROR_NET_LOGIN_ERROR_RELOGGIN));
		break;
	case NET_LOGIN_ERROR_LOCKED:		GetDlgItem(IDC_LAST_ERROR)->SetWindowText(ConvertString(ERROR_NET_LOGIN_ERROR_LOCKED));
		break;
	case NET_LOGIN_ERROR_BLACKLIST:		GetDlgItem(IDC_LAST_ERROR)->SetWindowText(ConvertString(ERROR_NET_LOGIN_ERROR_BLACKLIST));
		break;
	case NET_LOGIN_ERROR_BUSY:			GetDlgItem(IDC_LAST_ERROR)->SetWindowText(ConvertString(ERROR_NET_LOGIN_ERROR_BUSY));
		break;
	case NET_LOGIN_ERROR_CONNECT:		GetDlgItem(IDC_LAST_ERROR)->SetWindowText(ConvertString(ERROR_NET_LOGIN_ERROR_CONNECT));
		break;
	case NET_LOGIN_ERROR_NETWORK:		GetDlgItem(IDC_LAST_ERROR)->SetWindowText(ConvertString(ERROR_NET_LOGIN_ERROR_NETWORK));
		break;								
	case NET_RENDER_SOUND_ON_ERROR:		GetDlgItem(IDC_LAST_ERROR)->SetWindowText(ConvertString(ERROR_NET_RENDER_SOUND_ON_ERROR));
		break;
	case NET_RENDER_SOUND_OFF_ERROR:	GetDlgItem(IDC_LAST_ERROR)->SetWindowText(ConvertString(ERROR_NET_RENDER_SOUND_OFF_ERROR));
		break;
	case NET_RENDER_SET_VOLUME_ERROR:	GetDlgItem(IDC_LAST_ERROR)->SetWindowText(ConvertString(ERROR_NET_RENDER_SET_VOLUME_ERROR));
		break;
	case NET_RENDER_ADJUST_ERROR:		GetDlgItem(IDC_LAST_ERROR)->SetWindowText(ConvertString(ERROR_NET_RENDER_ADJUST_ERROR));
		break;
	case NET_RENDER_PAUSE_ERROR:		GetDlgItem(IDC_LAST_ERROR)->SetWindowText(ConvertString(ERROR_NET_RENDER_PAUSE_ERROR));
		break;
	case NET_RENDER_SNAP_ERROR:			GetDlgItem(IDC_LAST_ERROR)->SetWindowText(ConvertString(ERROR_NET_RENDER_SNAP_ERROR));
		break;
	case NET_RENDER_STEP_ERROR:			GetDlgItem(IDC_LAST_ERROR)->SetWindowText(ConvertString(ERROR_NET_RENDER_STEP_ERROR));
		break;
	case NET_RENDER_FRAMERATE_ERROR:	GetDlgItem(IDC_LAST_ERROR)->SetWindowText(ConvertString(ERROR_NET_RENDER_FRAMERATE_ERROR));
		break;
	case NET_CONFIG_DEVBUSY:			GetDlgItem(IDC_LAST_ERROR)->SetWindowText(ConvertString(ERROR_NET_CONFIG_DEVBUSY));
		break;
	case NET_CONFIG_DATAILLEGAL:		GetDlgItem(IDC_LAST_ERROR)->SetWindowText(ConvertString(ERROR_NET_CONFIG_DATAILLEGAL));
		break;							
	case NET_NO_INIT:					GetDlgItem(IDC_LAST_ERROR)->SetWindowText(ConvertString(ERROR_NET_NO_INIT));
		break;
	case NET_DOWNLOAD_END:				GetDlgItem(IDC_LAST_ERROR)->SetWindowText(ConvertString(ERROR_NET_DOWNLOAD_END));
		break;
	default:							GetDlgItem(IDC_LAST_ERROR)->SetWindowText(ConvertString(ERROR_NET_ERROR));						
	}
}

//Playback in accordance with time
void CClientDemo3Dlg::PlayBackByTime(int nChannelID)
{
    if (0 != m_LoginID)
    {
        if(0 == m_nTimer)
        {
            m_nTimer = SetTimer(1, 500, NULL);
        }

        ClosePlayBack();
		m_hPlayBack = 0;

        HWND hPlayBack = GetDlgItem(IDC_SCREEN_PLAYBACK)->m_hWnd;
        long lHandle = CLIENT_PlayBackByTime(m_LoginID,nChannelID,&m_PlayBackByTimeStart
            ,&m_PlayBackByTimeEnd,hPlayBack,PlayCallBack,(DWORD)this);
        if(0 != lHandle)
        {
            m_nChannelID = nChannelID;
            m_hPlayBack = lHandle;
            m_ePlayMode = EM_DIRECTMODE;
            SetDlgItemText(IDC_BUTTON_PLAY, ConvertString("Pause"));
            m_PlayBackType = EM_TIMEBACK;
            m_PlayBackDirection = EM_PLAYBACK_DIRECTION_FORWARD;
            m_nReverseMode = 0;
            ChangeSpeedStatus(0);
            SetPlayControlButton(TRUE);
        }
        else
        {
            MessageBox(ConvertString("Playback failed!"), ConvertString("Prompt"));
	    }

        CString strTest;
        GetDlgItemText(IDC_BUTTON_PLAYREVERSE, strTest);
        if (strTest != ConvertString("PlayReverse"))
        {
            SetDlgItemText(IDC_BUTTON_PLAYREVERSE, ConvertString("PlayReverse"));
        }
    }
}


//Playback in accordance with time in data callback mode.
void CClientDemo3Dlg::PlayBackMultyServerMode()
{
    //m_ePlayMode = EM_SERVERMODE;
    if(0 != m_LoginID)
    {
        if(0 == m_nTimer)
        {
            m_nTimer = SetTimer(1, 500, NULL);
	    }
        //First close video 
        ClosePlayBack();
        m_hPlayBack = 0;
        
        //Set stream play mode
        BOOL bOpenRet = PLAY_SetStreamOpenMode(1, STREAME_FILE);
        //Open stream
        bOpenRet = PLAY_OpenStream(1,0,0,1024*900);
        if(bOpenRet)
        {
            //Begin play
            HWND hPlayBack = GetDlgItem(IDC_SCREEN_PLAYBACK)->m_hWnd;
            BOOL bPlayRet = PLAY_Play(1,hPlayBack);
            if(bPlayRet)
            {
                //m_MultyPlayBackParam.hWnd = hPlayBack;
                m_MultyPlayBackParam.fDownLoadDataCallBack = DataCallBack;
                m_MultyPlayBackParam.dwDataUser = (DWORD)this;

                long lHandle = CLIENT_MultiPlayBack(m_LoginID,&m_MultyPlayBackParam);
                if(0 != lHandle)
                {
                    m_hPlayBack = lHandle;
                    m_ePlayMode = EM_SERVERMODE;
                    m_dwTotalSize = 1;//add by wuy for 时间条动态显示
                    m_dwCurValue = 0;
                    SetDlgItemText(IDC_BUTTON_PLAY, ConvertString("Pause"));
                    m_PlayBackType = EM_MULTYBACK;
                    m_PlayBackDirection = EM_PLAYBACK_DIRECTION_FORWARD;
                    ChangeSpeedStatus(0);
                    SetPlayControlButton(TRUE);
                }
                else
                {
                    PLAY_Stop(1);
                    PLAY_CloseStream(1);
                    MessageBox(ConvertString("Playback failed!"), ConvertString("Prompt"));
                }
            }
            else
            {
                PLAY_CloseStream(1);
            }
        }

        CString strTest;
        GetDlgItemText(IDC_BUTTON_PLAYREVERSE, strTest);
        if (strTest != ConvertString("PlayReverse"))
        {
            SetDlgItemText(IDC_BUTTON_PLAYREVERSE, ConvertString("PlayReverse"));
        }
    }
    else
    {
        MessageBox(ConvertString("Please login first!"), ConvertString("Prompt"));
    }
}

//Playback in accordance with time
void CClientDemo3Dlg::PlayBackMulty()
{
    if(0 != m_LoginID)
    {
        if(0 == m_nTimer)
        {
            m_nTimer = SetTimer(1, 500, NULL);
	    }
        //First close video 
        ClosePlayBack();
        m_hPlayBack = 0;
        
        HWND hPlayBack = GetDlgItem(IDC_SCREEN_PLAYBACK)->m_hWnd;
        m_MultyPlayBackParam.hWnd = hPlayBack;
        
        long lHandle = CLIENT_MultiPlayBack(m_LoginID,&m_MultyPlayBackParam);
        if(0 != lHandle)
        {
            m_hPlayBack = lHandle;
            m_ePlayMode = EM_DIRECTMODE;
            SetDlgItemText(IDC_BUTTON_PLAY, ConvertString("Pause"));
            m_dwTotalSize = 1;//add by wuy for 时间条动态显示
            m_dwCurValue = 0;
            m_PlayBackType = EM_MULTYBACK;
            m_PlayBackDirection = EM_PLAYBACK_DIRECTION_FORWARD;
            ChangeSpeedStatus(0);
            SetPlayControlButton(TRUE);
        }
        else
        {
            MessageBox(ConvertString("Playback failed!"), ConvertString("Prompt"));
        }

        CString strTest;
        GetDlgItemText(IDC_BUTTON_PLAYREVERSE, strTest);
        if (strTest != ConvertString("PlayReverse"))
        {
            SetDlgItemText(IDC_BUTTON_PLAYREVERSE, ConvertString("PlayReverse"));
        }
    }
    else
    {
        MessageBox(ConvertString("Please login first!"), ConvertString("Prompt"));
    }
}

//Turn NET_TIME type to CTime
CTime CClientDemo3Dlg::ConvertNetTimeToCTime(LPNET_TIME lpNetTime)
{
	int nYear = (int)lpNetTime->dwYear;
	int nMonth = (int)lpNetTime->dwMonth;
	int nDay = (int)lpNetTime->dwDay;
	int nHour = (int)lpNetTime->dwHour;
	int nMinute = (int)lpNetTime->dwMinute;
	int nSecond = (int)lpNetTime->dwSecond;
	CTime time(nYear,nMonth,nDay,nHour,nMinute,nSecond);
	return time;
}

//Download callback in time mode
void CALLBACK TimeDownLoadPos(LONG lPlayHandle, DWORD dwTotalSize, DWORD dwDownLoadSize, int index, NET_RECORDFILE_INFO recordfileinfo, DWORD dwUser)
{
	CClientDemo3Dlg * dlg = (CClientDemo3Dlg *)dwUser;
	dlg->TimeDownLoadCallBack(lPlayHandle, dwTotalSize, dwDownLoadSize, index, recordfileinfo,dwUser);
}

//Download process in time mode 
void CClientDemo3Dlg::TimeDownLoadCallBack(LONG lPlayHandle, DWORD dwTotalSize, DWORD dwDownLoadSize, int index, NET_RECORDFILE_INFO recordfileinfo,DWORD dwUser)
{
	if(lPlayHandle == m_pDownLoadByTime)
	{
		if(-1 != dwDownLoadSize)
		{
			m_pTabTimeDlg->m_dwTotalSize = dwTotalSize;
			m_pTabTimeDlg->m_dwCurValue = dwDownLoadSize;
		}
		else
		{
			m_pTabTimeDlg->m_dwTotalSize = 0;
			m_pTabTimeDlg->m_dwCurValue = 0;

			CClientDemo3Dlg * dlg = (CClientDemo3Dlg *)dwUser;
			if(0 != m_pDownLoadByTime)
			{
				CLIENT_StopDownload(m_pDownLoadByTime);
				m_pDownLoadByTime = 0;
			}
			m_pTabTimeDlg->SetDlgItemText(IDC_BUTTON_DOWNLOAD, ConvertString("Download"));
		}
	}
}


//Download in accordance with time
BOOL CClientDemo3Dlg::DownLoadByTime(int nChannelId, LPNET_TIME tmStart, LPNET_TIME tmEnd, BOOL bLoad)
{
	BOOL bRet =FALSE;
	if(0 == m_LoginID)
	{
		MessageBox(ConvertString("Please login first"), ConvertString("Prompt"));
		return bRet;
	}
	if(bLoad)
	{
		//Download
		if(0 != m_LoginID)
		{
			if(0 != m_pDownLoadByTime)
			{
				//Close download
				BOOL bSuccess = CLIENT_StopDownload(m_pDownLoadByTime);
				if(bSuccess)
				{
					m_pDownLoadByTime = 0;
				}
				else
				{
					MessageBox(ConvertString("Stop download failed!"), ConvertString("Prompt"));
				}
			}
			
			CFileDialog dlg(FALSE,"*.dav","download.dav",OFN_OVERWRITEPROMPT|OFN_HIDEREADONLY,
				"All File(*.dav)|*.*||",this);
			if(dlg.DoModal() == IDOK)
			{
				CString strFilePathName = dlg.GetPathName();
				long lRet = CLIENT_DownloadByTime(m_LoginID, nChannelId, 0, 
					tmStart, tmEnd, (LPSTR)(LPCSTR)strFilePathName,TimeDownLoadPos, (DWORD)this);
				if(0 != lRet)
				{
					m_pDownLoadByTime = lRet;
					bRet = TRUE;
				}
				else
				{
					LastError();
                    MessageBox(ConvertString("Download failed!"), ConvertString("Prompt"));
				}
			}
		}
	}
	else
	{
		//Stop download
		if(0 != m_pDownLoadByTime)
		{
			BOOL bSuccess = CLIENT_StopDownload(m_pDownLoadByTime);
			if(bSuccess)
			{
				m_pDownLoadByTime = 0;
				bRet = TRUE;
			}
			else
			{
				MessageBox(ConvertString("Stop download failed!"), ConvertString("Prompt"));
			}
		}
	}
	return bRet;
}

BOOL CClientDemo3Dlg::PlayBackByDirection(EM_PLAYBACK_DIRECTION emDirection)
{
    BOOL bSuccess = FALSE;

    // PLAY_Pause 播放库暂停播放
    bSuccess = PLAY_Pause(1,TRUE);
    // 获取当前播放画面的时间
    int nRetLen = 0;
    NET_TIME stuPicTime;
    memset(&stuPicTime, 0, sizeof(stuPicTime));
    bSuccess = PLAY_QueryInfo(1, PLAY_CMD_GetTime, (char *)&stuPicTime, sizeof(stuPicTime), &nRetLen);
    if (TRUE != bSuccess)
    {
        MessageBox( ConvertString("Get picture time fail!"), ConvertString("Prompt"));
        CLIENT_PausePlayBack(m_hPlayBack, FALSE);
        PLAY_Pause(1, FALSE);
        return FALSE;
    }

    // 设置播放库回放方向
    bSuccess = PLAY_SetPlayDirection(1, (emDirection == EM_PLAYBACK_DIRECTION_FORWARD) ? 0 : 1);
    if (TRUE != bSuccess)
    {
        MessageBox( ConvertString("Set playback direction fail!"), ConvertString("Prompt"));
        CLIENT_PausePlayBack(m_hPlayBack, FALSE);
        PLAY_Pause(1, FALSE);
        return FALSE;
    }
 
    if (1 == m_nReverseMode)
    {
        bSuccess = CLIENT_StopPlayBack(m_hPlayBack);
        if (TRUE != bSuccess)
        {
            MessageBox( ConvertString("Playback control direction fail!"), ConvertString("Prompt"));
            return FALSE;
        }

        NET_IN_PLAY_BACK_BY_TIME_INFO stIn = {0};
        NET_OUT_PLAY_BACK_BY_TIME_INFO stOut = {0};
        if (EM_PLAYBACK_DIRECTION_FORWARD == emDirection)
        {
            memcpy(&stIn.stStartTime, &stuPicTime, sizeof(NET_TIME));
            memcpy(&stIn.stStopTime, &m_PlayBackByTimeEnd, sizeof(NET_TIME));
        }
        else
        {
            memcpy(&stIn.stStartTime, &m_PlayBackByTimeStart, sizeof(NET_TIME));
            memcpy(&stIn.stStopTime, &stuPicTime, sizeof(NET_TIME));
        }

        // 清空播放库缓存数据
        PLAY_ResetBuffer(1, BUF_VIDEO_SRC);
        PLAY_ResetBuffer(1, BUF_AUDIO_SRC);
        PLAY_ResetBuffer(1, BUF_VIDEO_RENDER);
        PLAY_ResetBuffer(1, BUF_AUDIO_RENDER);

        stIn.fDownLoadDataCallBack = DataCallBack;
        stIn.dwDataUser = (DWORD)this;
        stIn.dwPosUser = NULL;
        stIn.hWnd = NULL;
        stIn.nPlayDirection = emDirection;
        stIn.nWaittime = 10000;
        stIn.cbDownLoadPos = NULL;

        // 播放库开始播放
        PLAY_Pause(1, FALSE);

        //Playback
        LLONG lHandle = CLIENT_PlayBackByTimeEx2(m_LoginID, m_nChannelID, &stIn, &stOut);
        if(0 != lHandle)
        {
            m_hPlayBack = lHandle;
            m_ePlayMode = EM_SERVERMODE;
            m_PlayBackType = EM_FILEBACK;
            m_PlayBackDirection = emDirection;
            m_nReverseMode = 1;
            ChangeSpeedStatus(0);
            SetPlayControlButton(TRUE);
        }
        else
        {
            PLAY_Stop(1);
            PLAY_CloseStream(1);
            MessageBox(ConvertString("Playback failed!"), ConvertString("Prompt"));
            return FALSE;
        }

    }
    else
    {
        if (FALSE == (bSuccess = CLIENT_PausePlayBack(m_hPlayBack,TRUE)))
        {
            MessageBox( ConvertString("Play failed!"), ConvertString("Prompt"));
            return FALSE;
        }

        bSuccess = CLIENT_PlayBackControlDirection(m_hPlayBack, emDirection);
        if (TRUE != bSuccess)
        {
            MessageBox( ConvertString("Playback control direction fail!"), ConvertString("Prompt"));
            CLIENT_PausePlayBack(m_hPlayBack, FALSE);
            PLAY_Pause(1, FALSE);
            return FALSE;
        }

        // 获取当前偏移时间
        int nOffset = GetUTCTimebyNetTime(stuPicTime) - GetUTCTimebyNetTime(m_PlayBackByTimeStart);
        if (nOffset <= 0)
        {
            nOffset = 1;
        }
        else if (nOffset >= GetUTCTimebyNetTime(m_PlayBackByTimeEnd) - GetUTCTimebyNetTime(m_PlayBackByTimeStart))
        {
            nOffset = GetUTCTimebyNetTime(m_PlayBackByTimeEnd) - GetUTCTimebyNetTime(m_PlayBackByTimeStart) - 1;
        }

        // 设置偏移时间
        bSuccess = CLIENT_SeekPlayBack(m_hPlayBack, nOffset, 0xffffffff);
        if (TRUE != bSuccess)
        {
            MessageBox( ConvertString("Seek playback fail!"), ConvertString("Prompt"));
            CLIENT_PausePlayBack(m_hPlayBack, FALSE);
            PLAY_Pause(1, FALSE);
            return FALSE;
        }

        // 清空播放库缓存数据
        PLAY_ResetBuffer(1, BUF_VIDEO_SRC);
        PLAY_ResetBuffer(1, BUF_AUDIO_SRC);
        PLAY_ResetBuffer(1, BUF_VIDEO_RENDER);
        PLAY_ResetBuffer(1, BUF_AUDIO_RENDER);

        // 播放库开始播放
        PLAY_Pause(1, FALSE);

        // 通知设备开始发送倒放/正放数据
        CLIENT_PausePlayBack(m_hPlayBack, FALSE);
    
        m_PlayBackDirection = emDirection;
    }

    return TRUE;
}

//Play and pause
void CClientDemo3Dlg::OnButtonPlay() 
{
	// TODO: Add your control notification handler code here
	if((0 != m_hPlayBack) && (0 != m_LoginID))
	{
		CString strText;
		GetDlgItemText(IDC_BUTTON_PLAY,strText);
		if(strText ==  ConvertString("Play") || strText ==  ConvertString("PlayForward"))
		{
			BOOL bSuccess = FALSE;
			if(m_ePlayMode == EM_DIRECTMODE)
			{
				bSuccess = CLIENT_PausePlayBack(m_hPlayBack,FALSE);
			}
			else if(m_ePlayMode == EM_SERVERMODE)
			{
                if (EM_FILEBACK == m_PlayBackType && EM_PLAYBACK_DIRECTION_REVERSE == m_PlayBackDirection)
                {
                    // 从倒放模式切换到正放模式
                    bSuccess = PlayBackByDirection(EM_PLAYBACK_DIRECTION_FORWARD);
                }
                else
                {
                    bSuccess = PLAY_Pause(1,FALSE);
                }
			}

			if(bSuccess)
			{
				SetDlgItemText(IDC_BUTTON_PLAY, ConvertString("Pause"));
                SetDlgItemText(IDC_BUTTON_PLAYREVERSE, ConvertString("PlayReverse"));
			}
			else
			{
				MessageBox( ConvertString("Play failed!"), ConvertString("Prompt"));
			}
		}
		else
		{
			//Pause
			BOOL bSuccess = FALSE;
			if(m_ePlayMode == EM_DIRECTMODE)
			{
				bSuccess = CLIENT_PausePlayBack(m_hPlayBack,TRUE);
			}
			else if(m_ePlayMode == EM_SERVERMODE)
			{
				bSuccess = PLAY_Pause(1,TRUE);
			}
			if(bSuccess)
			{
                if (EM_FILEBACK == m_PlayBackType && EM_SERVERMODE == m_ePlayMode)
                {
                    SetDlgItemText(IDC_BUTTON_PLAY,ConvertString("PlayForward"));
                }
                else
                {
                    SetDlgItemText(IDC_BUTTON_PLAY,ConvertString("Play"));
                }
			}
			else
			{
				MessageBox(ConvertString("Pause failed!"), ConvertString("Prompt"));
			}
		}
        // 点击正放按钮，界面正放按钮重新显示为倒放
        GetDlgItemText(IDC_BUTTON_PLAYREVERSE,strText);
        if(strText !=  ConvertString("PlayReverse"))
        {
            SetDlgItemText(IDC_BUTTON_PLAYREVERSE,ConvertString("PlayReverse"));
        }

	}
	else
	{
		MessageBox(ConvertString("Please play first!"), ConvertString("Prompt"));
	}
}

static float fSpeed[] = { 1/25.0f, 1/16.0f, 1/8.0f, 1/4.0f, 1/2.0f, 1.0f, 2.0f, 4.0f, 8.0f, 16.0f, 25.0f};

BOOL DoPlayFast( LONG nPort, PlaySpeed nCurSpeed )
{
    return PLAY_SetPlaySpeed(nPort, fSpeed[nCurSpeed + 1]);

    // 16倍速以内调用接口 PLAY_Fast
    // 16倍速以上调用接口 PLAY_SetPlaySpeed
    /*BOOL bRet = FALSE;
    if (nCurSpeed == SPEED_UP_16)
    {
        return PLAY_SetPlaySpeed(nPort, 25.0f);
    }
    else if (nCurSpeed == SPEED_DOWN_25)
    {
        return PLAY_SetPlaySpeed(nPort, 1/16.0f);
    }
    else if (nCurSpeed >= SPEED_DOWN_16 && nCurSpeed < SPEED_UP_16)
    {
        return PLAY_Fast(nPort);
    }
    return FALSE;*/
}

BOOL DoPlaySlow( LONG nPort, PlaySpeed nCurSpeed )
{
    return PLAY_SetPlaySpeed(nPort, fSpeed[nCurSpeed - 1]);

    // 16倍速以内调用接口 PLAY_Slow
    // 16倍速以上调用接口 PLAY_SetPlaySpeed
    /*BOOL bRet = FALSE;
    if (nCurSpeed == SPEED_UP_25)
    {
        return PLAY_SetPlaySpeed(nPort, 16.0f);
    }
    else if (nCurSpeed == SPEED_DOWN_16)
    {
        return PLAY_SetPlaySpeed(nPort, 1/25.0f);
    }
    else if (nCurSpeed > SPEED_DOWN_16 && nCurSpeed <= SPEED_UP_16)
    {
        return PLAY_Slow(nPort);
    }
    return FALSE;*/
}

LPCTSTR ChangeSpeed( int nMode, PlaySpeed& speed )
{
    if (nMode == 0)
    {
        speed = SPEED_NORMAL;
    }
    else if (nMode > 0)	// 加速
    {
        if (speed >= SPEED_MIN && speed < SPEED_MAX)
        {
            speed = (PlaySpeed)((int)speed + 1);
        }
    }
    else if (nMode < 0)	// 减速
    {
        if (speed > SPEED_MIN && speed <= SPEED_MAX)
        {
            speed = (PlaySpeed)((int)speed - 1);
        }
    }
    
    LPCTSTR lpszStr = NULL;
    static LPCTSTR aSpeed[] = { "1/25X", "1/16X", "1/8X", "1/4X", "1/2X", "1X", "2X", "4X", "8X", "16X", "25X", };
    if (speed >= SPEED_MIN && speed <= SPEED_MAX)
    {
        lpszStr = aSpeed[speed - SPEED_MIN];
    }
    return lpszStr;
}

void CClientDemo3Dlg::ChangeSpeedStatus( int nMode )
{
    SetDlgItemText(IDC_STATIC_SPEED, ChangeSpeed(nMode, m_eSpeed));
}

//Slow forward
void CClientDemo3Dlg::OnButtonSlow() 
{
	// TODO: Add your control notification handler code here
	if((0 != m_hPlayBack) && (0 != m_LoginID))
	{
		BOOL bSuccess = TRUE;
		if(m_ePlayMode == EM_DIRECTMODE)
		{
			bSuccess = CLIENT_SlowPlayBack(m_hPlayBack);
		}
		else if(m_ePlayMode == EM_SERVERMODE)
		{
            if (m_eSpeed > SPEED_MIN && m_eSpeed <= SPEED_MAX)
            {
			    bSuccess = DoPlaySlow(1, m_eSpeed);
            }
            else
            {
                bSuccess = FALSE;
            }
			if (bSuccess && m_bSpeedCtrl)
			{
				bSuccess = CLIENT_SlowPlayBack(m_hPlayBack);
			}
			
		}
		if(!bSuccess)
		{
			MessageBox(ConvertString("Slow failed!"), ConvertString("Prompt"));
		}        
        else
        {
            ChangeSpeedStatus(-1);
		}
	}
	else
	{
		MessageBox(ConvertString("Please play first!"), ConvertString("Prompt"));
	}
}

//fast forward
void CClientDemo3Dlg::OnButtonFast() 
{
	// TODO: Add your control notification handler code here
	if((0 != m_hPlayBack) && (0 != m_LoginID))
	{
		BOOL bSuccess = TRUE;
		if(m_ePlayMode == EM_DIRECTMODE)
		{
			bSuccess = CLIENT_FastPlayBack(m_hPlayBack);
		}
		else if(m_ePlayMode == EM_SERVERMODE)
		{
            if (m_eSpeed >= SPEED_MIN && m_eSpeed < SPEED_MAX)
            {
			    bSuccess = DoPlayFast(1, m_eSpeed);
            }
            else
            {
                bSuccess = FALSE;
            }
			if (bSuccess && m_bSpeedCtrl)
			{
				bSuccess = CLIENT_FastPlayBack(m_hPlayBack);
			}
		}
		if(!bSuccess)
		{
			MessageBox(ConvertString("Fast failed!"), ConvertString("Prompt"));
		}
        else
        {
            ChangeSpeedStatus(1);
        }
	}
	else
	{
		MessageBox(ConvertString("Please play first!"), ConvertString("Prompt"));
	}
}

//Frame
void CClientDemo3Dlg::OnButtonFrameto() 
{
	// TODO: Add your control notification handler code here
	if((0 != m_hPlayBack) && (0 != m_LoginID))
	{
		BOOL bSuccess = TRUE;
		if(m_ePlayMode == EM_DIRECTMODE)
		{
			bSuccess = CLIENT_StepPlayBack(m_hPlayBack,FALSE);
		}
		else if(m_ePlayMode == EM_SERVERMODE)
		{
			bSuccess = PLAY_OneByOne(1);
		}
		if(bSuccess)
		{
			GetDlgItem(IDC_BUTTON_RESET)->EnableWindow(TRUE);
		}
		else
		{
			MessageBox(ConvertString("Play by Single Frame failed!"), ConvertString("Prompt"));
		}
	}
	else
	{
		MessageBox(ConvertString("Please play first!"), ConvertString("Prompt"));
	}
}

//Reset
void CClientDemo3Dlg::OnButtonReset() 
{
	// TODO: Add your control notification handler code here
	if((0 != m_hPlayBack) && (0 != m_LoginID))
	{
		BOOL bSuccess = TRUE;
		if(m_ePlayMode == EM_DIRECTMODE)
		{
			bSuccess = CLIENT_StepPlayBack(m_hPlayBack,TRUE);

			// normal 一下，修复快进状态下的复位点击
			if (bSuccess)
			{
				OnButtonNormalspeed();
			}
		}
		else if(m_ePlayMode == EM_SERVERMODE)
		{
			HWND hPlayBack = GetDlgItem(IDC_SCREEN_PLAYBACK)->m_hWnd;
			bSuccess = PLAY_Play(1,hPlayBack);
			// normal 一下，修复快进状态下的复位点击
			if (bSuccess)
			{
				OnButtonNormalspeed();
			}
		}
		if(bSuccess)
		{
			GetDlgItem(IDC_BUTTON_RESET)->EnableWindow(FALSE);
		}
		else
		{
			MessageBox(ConvertString("Reset failed!"), ConvertString("Prompt"));
		}
	}
	else
	{
		MessageBox(ConvertString("Please play first!"), ConvertString("Prompt"));
	}
}

//Data callback
int CALLBACK DataCallBack(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, DWORD dwUser)
{
	//TRACE("lRealHandle=%d;dwUser=%d\n",lRealHandle,dwUser);
	int nRet = 1;
	if(dwUser == 0)
	{
		return nRet;
	}
	CClientDemo3Dlg *dlg = (CClientDemo3Dlg *)dwUser;
	nRet = dlg->ReceiveRealData(lRealHandle,dwDataType, pBuffer, dwBufSize);
	return nRet;
}
//FILE* pFile = NULL;
//Data callback mode 
int CClientDemo3Dlg::ReceiveRealData(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize)
{
	int nRet = 1;
	if(lRealHandle == m_hPlayBack)
	{	
		BOOL bSuccess = TRUE;
		switch(dwDataType) {
		case 0:
			//Original data 
			bSuccess = PLAY_InputData(1,pBuffer,dwBufSize);
			if(!bSuccess)
			{
				nRet = 0;
			}
			/*
            else
            {
                if (NULL == pFile)
                {
                    pFile = fopen("playback.dav", "wb+");
                }
                else
                {
                    if (EM_PLAYBACK_DIRECTION_REVERSE == m_PlayBackDirection)
                    {
                        if (NULL != pFile)
                        {
                            fwrite(pBuffer, dwBufSize, 1, pFile);
                        }
                    }
                }
            }
			*/
			break;
		case 1:
			//Standard video data 
			
			break;
		case 2:
			//yuv data
			
			break;
		case 3:
			//pcm audio data 
			
			break;
		case 4:
			//Original audio data 
			
			break;
		default:
			break;
		}	
	}
	return nRet;
}

//Playback in accordance with file in data callback mode.
void CClientDemo3Dlg::PlayBackByFileServerMode(NET_RECORDFILE_INFO fileInfo, int nChannelID)
{
///	m_ctlPlayBack.SetSelection(0,0);
///	m_ctlPlayBack.SetPos(0);
	if(0 != m_LoginID)
	{
		if(0 == m_nTimer)
		{
			m_nTimer = SetTimer(1, 500, NULL);
		}
		//First close video 
		ClosePlayBack();
		m_hPlayBack = 0;
		
		//Set stream play mode
		BOOL bOpenRet = PLAY_SetStreamOpenMode(1,STREAME_FILE);
		//Open stream
		bOpenRet = PLAY_OpenStream(1,0,0,1024*900);
		if(bOpenRet)
		{
			//Begin play
			HWND hPlayBack = GetDlgItem(IDC_SCREEN_PLAYBACK)->m_hWnd;
			BOOL bPlayRet = PLAY_Play(1,hPlayBack);
			if(bPlayRet)
			{
				InitTimeOcx(fileInfo);
				
				int recordStreamType = fileInfo.bRecType == 0 ? 1 : 2;
				if (!CLIENT_SetDeviceMode(m_LoginID, DH_RECORD_STREAM_TYPE, &recordStreamType))
				{
					MessageBox(ConvertString("Set stream type failed"), ConvertString("Prompt"));
				}
				//Playabck
				long lHandle = CLIENT_PlayBackByTimeEx(m_LoginID,nChannelID
					,&m_PlayBackByTimeStart,&m_PlayBackByTimeEnd
					,0,PlayCallBack,(DWORD)this,DataCallBack,(DWORD)this);
				if(0 != lHandle)
				{
					m_nChannelID = nChannelID;
					m_hPlayBack = lHandle;
					m_ePlayMode = EM_SERVERMODE;
					SetDlgItemText(IDC_BUTTON_PLAY, ConvertString("Pause"));
					m_PlayBackType = EM_FILEBACK;
                    m_PlayBackDirection = EM_PLAYBACK_DIRECTION_FORWARD;
                    m_nReverseMode = 0;
                    ChangeSpeedStatus(0);
                    SetPlayControlButton(TRUE);
				}
				else
				{
					PLAY_Stop(1);
					PLAY_CloseStream(1);
					MessageBox(ConvertString("Playback failed!"), ConvertString("Prompt"));
				}
			}
			else
			{
				PLAY_CloseStream(1);
			}
		}

        CString strTest;
        GetDlgItemText(IDC_BUTTON_PLAYREVERSE, strTest);
        if (strTest != ConvertString("PlayReverse"))
        {
            SetDlgItemText(IDC_BUTTON_PLAYREVERSE, ConvertString("PlayReverse"));
        }
	}
}

//Playback in accordance with time in data callback mode.
//void CClientDemo3Dlg::PlayBackByTimeServerMode(int nChannelID, LPNET_TIME lpStartTime, LPNET_TIME lpStopTime)
void CClientDemo3Dlg::PlayBackByTimeServerMode(int nChannelID)
{
	//m_ePlayMode = EM_SERVERMODE;
///	m_ctlPlayBack.SetSelection(0,0);
//	m_ctlPlayBack.SetPos(0);
	if(0 != m_LoginID)
	{
		if(0 == m_nTimer)
		{
			m_nTimer = SetTimer(1, 500, NULL);
		}
		//First close video 
		ClosePlayBack();
		m_hPlayBack = 0;

		//Set stream play mode
		BOOL bOpenRet = PLAY_SetStreamOpenMode(1,STREAME_FILE);
		//Open stream
		bOpenRet = PLAY_OpenStream(1,0,0,1024*900);
		if(bOpenRet)
		{
			//Begin play
			HWND hPlayBack = GetDlgItem(IDC_SCREEN_PLAYBACK)->m_hWnd;
			BOOL bPlayRet = PLAY_Play(1,hPlayBack);
			if(bPlayRet)
			{
				//Playback
					long lHandle = CLIENT_PlayBackByTimeEx(m_LoginID,nChannelID
											,&m_PlayBackByTimeStart,&m_PlayBackByTimeEnd
											,0,PlayCallBack,(DWORD)this,DataCallBack,(DWORD)this);
				if(0 != lHandle)
				{
					m_nChannelID = nChannelID;
					m_hPlayBack = lHandle;
					m_ePlayMode = EM_SERVERMODE;
					SetDlgItemText(IDC_BUTTON_PLAY, ConvertString("Pause"));
					m_PlayBackType = EM_TIMEBACK;
                    m_PlayBackDirection = EM_PLAYBACK_DIRECTION_FORWARD;
                    m_nReverseMode = 0;
                    ChangeSpeedStatus(0);
                    SetPlayControlButton(TRUE);
				}
				else
				{
					PLAY_Stop(1);
					PLAY_CloseStream(1);
					MessageBox(ConvertString("Playback failed!"), ConvertString("Prompt"));
				}
			}
			else
			{
				PLAY_CloseStream(1);
			}
		}

        CString strTest;
        GetDlgItemText(IDC_BUTTON_PLAYREVERSE, strTest);
        if (strTest != ConvertString("PlayReverse"))
        {
            SetDlgItemText(IDC_BUTTON_PLAYREVERSE, ConvertString("PlayReverse"));
        }
	}
	else
	{
		MessageBox(ConvertString("Please login first!"), ConvertString("Prompt"));
	}
}

//Close video 
void CClientDemo3Dlg::ClosePlayBack()
{
	if(m_ePlayMode == EM_DIRECTMODE)
	{
		//Close video directly
		if(0 != m_hPlayBack)
		{
			CLIENT_StopPlayBack(m_hPlayBack);
            SetPlayControlButton(FALSE);
			m_hPlayBack = 0;
		}
	}
	else if(m_ePlayMode == EM_SERVERMODE)
	{
		//Close video in data callback mode
		if(0 != m_hPlayBack)
		{
			BOOL bSuccess = CLIENT_StopPlayBack(m_hPlayBack);
			m_hPlayBack = 0;
			//Then close PLAY_Play
			bSuccess = PLAY_Stop(1);
			//At last close PLAY_OpenStream
			bSuccess = PLAY_CloseStream(1);

			bSuccess = PLAY_ResetBuffer(1, BUF_VIDEO_SRC);
			bSuccess = PLAY_ResetBuffer(1, BUF_AUDIO_SRC);
			bSuccess = PLAY_ResetBuffer(1, BUF_VIDEO_RENDER);
			bSuccess = PLAY_ResetBuffer(1, BUF_AUDIO_RENDER);
            SetPlayControlButton(FALSE);
		}
	}
}

//Click mouse event in process bar
void CClientDemo3Dlg::ExSliderButtonDown()
{
	//TRACE("down\n");
	if(0 != m_nTimer)
	{
		KillTimer(m_nTimer);
		m_nTimer = 0;
	}
}

//Mouse release event in process bar
void CClientDemo3Dlg::ExSliderButtonUp()
{
	//TRACE("up\n");
	if(0 == m_nTimer)
	{
		m_nTimer = SetTimer(1, 500, NULL);
	}
}

void CClientDemo3Dlg::OnButtonNormalspeed() 
{
	// TODO: Add your control notification handler code here
	if((0 != m_LoginID) && (0 != m_hPlayBack))
	{
		BOOL bSuccess = TRUE;
		if(m_ePlayMode == EM_DIRECTMODE)
		{
			bSuccess = CLIENT_NormalPlayBack(m_hPlayBack);
		}
		else if(m_ePlayMode == EM_SERVERMODE)
		{
			HWND hPlayBack = GetDlgItem(IDC_SCREEN_PLAYBACK)->m_hWnd;
			bSuccess = PLAY_Play(1, hPlayBack);
			if (bSuccess && m_bSpeedCtrl)
			{
				bSuccess = CLIENT_NormalPlayBack(m_hPlayBack);
			}
			
		}
		if(!bSuccess)
		{
			MessageBox(ConvertString("Recover normal speed failed!"), ConvertString("Prompt"));
		}
        else
        {
            ChangeSpeedStatus(0);
		}
	}
	else
	{
		MessageBox(ConvertString("Please play first!"), ConvertString("Prompt"));
	}
}

int Compare( const NET_TIME *pSrcTime, const NET_TIME *pDestTime)
{
	SYSTEMTIME srcTime={0}, destTime={0};
	srcTime.wYear     =    (unsigned short)pSrcTime->dwYear;
	srcTime.wMonth  =    (unsigned short)pSrcTime->dwMonth;
	srcTime.wDay       =   (unsigned short)pSrcTime->dwDay;
	srcTime.wHour     =   (unsigned short)pSrcTime->dwHour;
	srcTime.wMinute   =  (unsigned short)pSrcTime->dwMinute;
	srcTime.wSecond  =   (unsigned short)pSrcTime->dwSecond;
    /// dest
	destTime.wYear     =    (unsigned short)pDestTime->dwYear;
	destTime.wMonth  =    (unsigned short)pDestTime->dwMonth;
	destTime.wDay       =   (unsigned short)pDestTime->dwDay;
	destTime.wHour     =   (unsigned short)pDestTime->dwHour;
	destTime.wMinute   =  (unsigned short)pDestTime->dwMinute;
	destTime.wSecond  =   (unsigned short)pDestTime->dwSecond;
	FILETIME   srcFileTime={0}, destFileTime={0};
	SystemTimeToFileTime(&srcTime, &srcFileTime);
	SystemTimeToFileTime(&destTime, &destFileTime);
	return CompareFileTime(&srcFileTime, &destFileTime);
}

void UpdateNetTime(NET_TIME& ntStart,  NET_TIME ntCur)
{
	if (Compare(&ntStart, &ntCur) == 1)
	{
		ntStart = ntCur;
	}
/*	if (ntStart.dwHour > ntCur.dwHour)
	{
		ntStart.dwHour = ntCur.dwHour;
		ntStart.dwMinute = ntCur.dwMinute;
		ntStart.dwSecond = ntCur.dwSecond;
	}
	else if (ntStart.dwHour == ntCur.dwHour)
	{
		if (ntStart.dwMinute > ntCur.dwMinute)
		{
			ntStart.dwMinute = ntCur.dwMinute;
		}
		else if (ntStart.dwMinute == ntCur.dwMinute)
		{
			if (ntStart.dwSecond > ntCur.dwSecond)
			{
				ntStart.dwSecond = ntCur.dwSecond;
			}
		}
	}*/
}

void UpdateNetTime2(NET_TIME& ntEnd, NET_TIME ntCur)
{
	if (ntCur.dwYear > ntEnd.dwYear
		|| ntCur.dwMonth > ntEnd.dwMonth 
		|| ntCur.dwDay > ntEnd.dwDay )
	{
		ntEnd.dwHour = 23;
		ntEnd.dwMinute = 59;
		ntEnd.dwSecond = 59;
	}
	else
	{
		/*if (ntCur.dwHour > ntEnd.dwHour
			|| ntCur.dwMinute > ntEnd.dwMinute
			|| ntCur.dwSecond > ntEnd.dwSecond)
		{
			ntEnd = ntCur;
		}*/
		if (Compare(&ntEnd, &ntCur) == -1)
		{
			ntEnd = ntCur;
		}
	}
}

void CClientDemo3Dlg::StopPlay()
{
    OnButtonStop();
}

void CClientDemo3Dlg::AddTimeToDateTimeCtl_Multy(NET_RECORDFILE_INFO fileInfo[2000], int nFileCount)
{
    OnButtonStop();

    bool bRecordFlag = false;
    LONG lStartTime = 0;
    LONG lEndTime = 0;
    m_DayTimePickSdk.ClearTimeBlock();
    //TRACE("CClientDemo3Dlg::AddTimeToDateTimeCtl_Multy  ClearTimeBlock\n");
    NET_TIME ntStart = m_PlayBackByTimeStart;
    ntStart.dwHour = fileInfo[0].starttime.dwHour;
    ntStart.dwMinute = fileInfo[0].starttime.dwMinute;
    ntStart.dwSecond = fileInfo[0].starttime.dwSecond;
    NET_TIME ntEnd = m_PlayBackByTimeEnd;
    ntEnd.dwHour = fileInfo[0].endtime.dwHour;
    ntEnd.dwMinute = fileInfo[0].endtime.dwMinute;
    ntEnd.dwSecond = fileInfo[0].endtime.dwSecond;
    
    for (int i = 0;i < nFileCount;i++)
    {
        
        if (fileInfo[i].starttime.dwDay != m_PlayBackByTimeStart.dwDay)
        {
            if (true == bRecordFlag)
            {
                continue;
            }
        }
		
        bRecordFlag = true;
            
        lStartTime = fileInfo[i].starttime.dwHour*3600 + fileInfo[i].starttime.dwMinute*60 + fileInfo[i].starttime.dwSecond;
        if (fileInfo[i].endtime.dwYear == fileInfo[i].starttime.dwYear + 1
            || fileInfo[i].endtime.dwMonth == fileInfo[i].starttime.dwMonth + 1
            || fileInfo[i].endtime.dwDay == fileInfo[i].starttime.dwDay + 1)
        {
            lEndTime = 24*3600;
        }
        else
        {
            lEndTime = fileInfo[i].endtime.dwHour*3600 + fileInfo[i].endtime.dwMinute*60 + fileInfo[i].endtime.dwSecond;
        }
        m_DayTimePickSdk.AddTimeBlock(lStartTime, lEndTime, RGB(0,255,0));
        
        UpdateNetTime(ntStart, fileInfo[i].starttime);
        UpdateNetTime2(ntEnd, fileInfo[i].endtime);
        
    }
    
    m_pCurrentTime = ntStart.dwHour*3600 + ntStart.dwMinute*60 + ntStart.dwSecond;
    m_StartTime = m_pCurrentTime;
    m_DayTimePickSdk.SetCurrentTime(m_StartTime);
    
    m_PlayBackByTimeStart.dwHour = ntStart.dwHour;
    m_PlayBackByTimeStart.dwMinute = ntStart.dwMinute;
    m_PlayBackByTimeStart.dwSecond = ntStart.dwSecond;
    
    m_PlayBackByTimeEnd.dwHour = ntEnd.dwHour;
    m_PlayBackByTimeEnd.dwMinute = ntEnd.dwMinute;
    m_PlayBackByTimeEnd.dwSecond = ntEnd.dwSecond;

    m_DayTimePickSdk.Invalidate(FALSE);
}

void CClientDemo3Dlg::AddTimeToDateTimeCtl(NET_RECORDFILE_INFO fileInfo[2000], int nFileCount)
{
	OnButtonStop();

	LONG lStartTime = 0;
	LONG lEndTime = 0;
	m_DayTimePickSdk.ClearTimeBlock();
	NET_TIME ntStart = m_PlayBackByTimeStart;
	ntStart.dwHour = fileInfo[0].starttime.dwHour;
	ntStart.dwMinute = fileInfo[0].starttime.dwMinute;
	ntStart.dwSecond = fileInfo[0].starttime.dwSecond;
	NET_TIME ntEnd = m_PlayBackByTimeEnd;
	ntEnd.dwHour = fileInfo[0].endtime.dwHour;
	ntEnd.dwMinute = fileInfo[0].endtime.dwMinute;
	ntEnd.dwSecond = fileInfo[0].endtime.dwSecond;

	for (int i = 0;i < nFileCount;i++)
	{
		
		if (fileInfo[i].starttime.dwDay != m_PlayBackByTimeStart.dwDay)
		{
			continue;
		}
		lStartTime = fileInfo[i].starttime.dwHour*3600 + fileInfo[i].starttime.dwMinute*60 + fileInfo[i].starttime.dwSecond;
		if (fileInfo[i].endtime.dwYear == fileInfo[i].starttime.dwYear + 1
			|| fileInfo[i].endtime.dwMonth == fileInfo[i].starttime.dwMonth + 1
			|| fileInfo[i].endtime.dwDay == fileInfo[i].starttime.dwDay + 1)
		{
			lEndTime = 24*3600;
		}
		else
		{
			lEndTime = fileInfo[i].endtime.dwHour*3600 + fileInfo[i].endtime.dwMinute*60 + fileInfo[i].endtime.dwSecond;
		}
		m_DayTimePickSdk.AddTimeBlock(lStartTime, lEndTime, RGB(0,255,0));
		UpdateNetTime(ntStart, fileInfo[i].starttime);
		UpdateNetTime2(ntEnd, fileInfo[i].endtime);
		
	}

	m_pCurrentTime = ntStart.dwHour*3600 + ntStart.dwMinute*60 + ntStart.dwSecond;
	m_StartTime = m_pCurrentTime;
	m_DayTimePickSdk.SetCurrentTime(m_StartTime);

	m_PlayBackByTimeStart.dwHour = ntStart.dwHour;
    m_PlayBackByTimeStart.dwMinute = ntStart.dwMinute;
	m_PlayBackByTimeStart.dwSecond = ntStart.dwSecond;
	
	m_PlayBackByTimeEnd.dwHour = ntEnd.dwHour;
    m_PlayBackByTimeEnd.dwMinute = ntEnd.dwMinute;
	m_PlayBackByTimeEnd.dwSecond = ntEnd.dwSecond;

	m_DayTimePickSdk.Invalidate(FALSE);

    m_pTabTimeDlg->OnButtonPlay();
}

BEGIN_EVENTSINK_MAP(CClientDemo3Dlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CClientDemo3Dlg)
	ON_EVENT(CClientDemo3Dlg, IDC_DAYTIMEPICKSDKCTRL1, 1 /* OnTimeClick */, OnOnTimeClickDaytimepicksdkctrl1, VTS_I4 VTS_I4 VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()


void CClientDemo3Dlg::InitTimeOcx(NET_RECORDFILE_INFO & fileInfo)
{
	ClosePlayBack();
	m_DayTimePickSdk.ClearTimeBlock();
//	m_DayTimePickSdk.AddTimeBlock(0, 60*60*24, RGB(0,0,0));
	
	m_PlayBackByTimeStart = fileInfo.starttime;
	m_PlayBackByTimeEnd = fileInfo.endtime;
	
	
	long lStartTime = fileInfo.starttime.dwHour*3600 + fileInfo.starttime.dwMinute*60 + fileInfo.starttime.dwSecond;
	long lEndTime = fileInfo.endtime.dwHour*3600 + fileInfo.endtime.dwMinute*60 + fileInfo.endtime.dwSecond;
	if (fileInfo.endtime.dwYear > fileInfo.starttime.dwYear
		|| fileInfo.endtime.dwMonth > fileInfo.starttime.dwMonth
		|| fileInfo.endtime.dwDay > fileInfo.starttime.dwDay)
	{
		m_PlayBackByTimeEnd = m_PlayBackByTimeStart;
		m_PlayBackByTimeEnd.dwHour = 23;
		m_PlayBackByTimeEnd.dwMinute = 59;
		m_PlayBackByTimeEnd.dwSecond = 59;
		lEndTime = 24*60*60;
	}
	
	m_DayTimePickSdk.AddTimeBlock(lStartTime, lEndTime, RGB(0,255,0));
	m_TotalTime = lEndTime - lStartTime;
	m_StartTime = lStartTime;
	m_DayTimePickSdk.SetCurrentTime(lStartTime);
}


void CClientDemo3Dlg::OnOnTimeClickDaytimepicksdkctrl1(long nHour, long nMinute, long nSecond) 
{
	// TODO: Add your control notification handler code here
	if (0 != m_hPlayBack)
	{
		DWORD dwCurrent = m_DayTimePickSdk.GetCurrentTimeOfSecond();
		DWORD dwHour = dwCurrent / 3600 ;
		DWORD dwMin = (dwCurrent % 3600) / 60;
		DWORD dwSec = dwCurrent % 60;

		BOOL bIfExit = m_DayTimePickSdk.IsTimeExist(dwHour,dwMin,dwSec);
		if(bIfExit)
		{
			if(0 != m_nTimer)
			{
				KillTimer(m_nTimer);
				m_nTimer = 0;
			}

			ClosePlayBack();

			m_PlayBackByTimeStart.dwHour = dwHour;
			m_PlayBackByTimeStart.dwMinute = dwMin;
			m_PlayBackByTimeStart.dwSecond = dwSec;

			if(m_ePlayMode == EM_DIRECTMODE)
			{
                if (EM_MULTYBACK == m_PlayBackType)
                {
                    m_MultyPlayBackParam.stStartTime = m_PlayBackByTimeStart;
                    PlayBackMulty();
                }
                else
                {
                    PlayBackByTime(m_nChannelID);
                }
				
			}
			else
			{
                if (EM_MULTYBACK == m_PlayBackType)
                {
                    m_MultyPlayBackParam.stStartTime = m_PlayBackByTimeStart;
                    PlayBackMultyServerMode();
                }
                else
                {
				    PlayBackByTimeServerMode(m_nChannelID);
                }

			}
		}
		else
		{
			return;
			//ClosePlayBack();
		}
/*
		unsigned int nOffsetTime = dwCurrent - m_StartTime;
		BOOL bSuccess = CLIENT_SeekPlayBack(m_hPlayBack, nOffsetTime, 0xFFFFFFFF);
		if (bSuccess == FALSE)
		{
			MessageBox(ConvertString("Seek Fail!"), ConvertString("Prompt"));
		}
		
		if(m_ePlayMode == EM_SERVERMODE)
		{
			PLAY_ResetBuffer(1, BUF_VIDEO_SRC);
			PLAY_ResetBuffer(1, BUF_AUDIO_SRC);
			PLAY_ResetBuffer(1, BUF_VIDEO_RENDER);
			PLAY_ResetBuffer(1, BUF_AUDIO_RENDER);
		}

		if(0 == m_nTimer)
		{
			m_nTimer = SetTimer(1, 500, NULL);
		}
*/
	}	
}

void CClientDemo3Dlg::OnButtonCapturePicture() 
{
	// TODO: Add your control notification handler code here
    DWORD dwCurrent = m_DayTimePickSdk.GetCurrentTimeOfSecond();
    DWORD dwHour = dwCurrent / 3600 ;
    DWORD dwMin = (dwCurrent % 3600) / 60;
	DWORD dwSec = dwCurrent % 60;
    if((0 != m_hPlayBack) && (0 != m_LoginID))
    {
        BOOL bSuccess = TRUE;
        int nError = 0;
        int nDirectoryLength = 64;
        char* pDirectory = NULL;
        while(1)
        {
            if (NULL == pDirectory)
            {
                pDirectory = new char[nDirectoryLength];
            }

            if (NULL == pDirectory)
            {
                MessageBox(ConvertString("System error!"), ConvertString("Prompt"));
                return;
            }
            memset(pDirectory, 0, nDirectoryLength);

            int Ret = GetModuleFileName(NULL,  pDirectory, nDirectoryLength);
            char* pLastPos = NULL;
            for (int i = 0; pDirectory[i]; ++i)
            {
                if ('\\' == pDirectory[i])
                {
                    pLastPos = pDirectory + i;
                }
            }

            if (NULL == pLastPos)
            {
                MessageBox(ConvertString("System error!"), ConvertString("Prompt"));
                return;
            }
            else
            {
                *(pLastPos + 1) = 0;
            }

            if (Ret >= nDirectoryLength)   // 缓冲区不够
            {
                delete [] pDirectory;
                pDirectory = NULL;
                nDirectoryLength = nDirectoryLength * 2;
            }
            else
            {
                break;
            }
        }

        int nPictureNameLength = nDirectoryLength + 50;
        char* pPictureName = new char[nPictureNameLength];
        if (NULL == pPictureName)
        {
            MessageBox(ConvertString("System error!"), ConvertString("Prompt"));
            return;
        }

        memset(pPictureName, 0, nPictureNameLength);

        _snprintf(pPictureName, nPictureNameLength - 1, "%s%s_%2d_%2d_%2d.bmp", pDirectory, (m_ePlayMode == EM_DIRECTMODE)?"Picture_Direct":"Picture_Server", dwHour, dwMin, dwSec);
        if (NULL != pDirectory)
        {
            delete [] pDirectory;
            pDirectory = NULL;
        }

        if(m_ePlayMode == EM_DIRECTMODE)
        {
            //bSuccess = CLIENT_CapturePictureEx(m_hPlayBack, "D://Picture_Direct_6_5_3.bmp", NET_CAPTURE_BMP);
            bSuccess = CLIENT_CapturePictureEx(m_hPlayBack, pPictureName, NET_CAPTURE_BMP);
        }
        else if(m_ePlayMode == EM_SERVERMODE)
        {
            //bSuccess = PLAY_CatchPicEx(1, "D://Picture_Direct_6_5_3.bmp", PicFormat_BMP);
            bSuccess = PLAY_CatchPicEx(1, pPictureName, PicFormat_BMP);
        }

        if (NULL != pPictureName)
        {
            delete [] pPictureName;
            pPictureName = NULL;
        }

        if(!bSuccess)
        {
            nError = CLIENT_GetLastError();
            MessageBox(ConvertString("Capture picture failed!"), ConvertString("Prompt"));
        }
    }
    else
    {
        MessageBox(ConvertString("Please play first!"), ConvertString("Prompt"));
	}
	
}

long CClientDemo3Dlg::GetUTCTimebyNetTime(const NET_TIME& stTime)
{
    struct tm when = {0};
    when.tm_year = stTime.dwYear - 1900;
    when.tm_mon = stTime.dwMonth - 1;
    when.tm_mday = stTime.dwDay;
    when.tm_hour = stTime.dwHour;
    when.tm_min = stTime.dwMinute;
    when.tm_sec = stTime.dwSecond;
    when.tm_isdst = -1;
    
    long UTC = mktime(&when);
    return UTC < 0 ? 0 : UTC;
}

void CClientDemo3Dlg::OnButtonPlayreverse() 
{
	// TODO: Add your control notification handler code here
    if((0 != m_hPlayBack) && (0 != m_LoginID))
    {
        CString strText;
        GetDlgItemText(IDC_BUTTON_PLAYREVERSE,strText);
        if(strText ==  ConvertString("PlayReverse"))
        {
            BOOL bSuccess = FALSE;
            if(m_ePlayMode == EM_SERVERMODE)
            {
                if (EM_PLAYBACK_DIRECTION_FORWARD == m_PlayBackDirection)
                {
                    // 从正放模式切换到倒放模式
                    bSuccess = PlayBackByDirection(EM_PLAYBACK_DIRECTION_REVERSE);
                }
                else
                {
                    bSuccess = PLAY_Pause(1,FALSE);
                }
            }
            
            if(bSuccess)
            {
                SetDlgItemText(IDC_BUTTON_PLAYREVERSE, ConvertString("Pause"));
            }
            else
            {
                MessageBox( ConvertString("Play failed!"), ConvertString("Prompt"));
            }
        }
        else
        {
            //Pause
            BOOL bSuccess = FALSE;
            if(m_ePlayMode == EM_SERVERMODE)
            {
                bSuccess = PLAY_Pause(1,TRUE);
            }

            if(bSuccess)
            {
                SetDlgItemText(IDC_BUTTON_PLAYREVERSE,ConvertString("PlayReverse"));
            }
            else
            {
                MessageBox(ConvertString("Pause failed!"), ConvertString("Prompt"));
            }
        }
        // 点击倒放按钮，界面正放按钮重新显示为正放
        GetDlgItemText(IDC_BUTTON_PLAY,strText);
        if (strText !=  ConvertString("PlayForward"))
        {
            SetDlgItemText(IDC_BUTTON_PLAY,ConvertString("PlayForward"));
        }
    }
    else
    {
        MessageBox(ConvertString("Please play first!"), ConvertString("Prompt"));
    }
}


LLONG  CClientDemo3Dlg::PlayBackByTimeEx2(int nChannel, NET_IN_PLAY_BACK_BY_TIME_INFO *pstIn, NET_OUT_PLAY_BACK_BY_TIME_INFO*pstOut)
{
    //First close video 
    ClosePlayBack();
    m_hPlayBack = 0;
    LLONG lHandle = 0;
    
    //Set stream play mode
    BOOL bOpenRet = PLAY_SetStreamOpenMode(1,STREAME_FILE);
    //Open stream
    bOpenRet = PLAY_OpenStream(1,0,0,1024*900);
    if(bOpenRet)
    {
        pstIn->fDownLoadDataCallBack = DataCallBack;
        pstIn->dwDataUser = (DWORD)this;
        memcpy(&m_PlayBackByTimeStart, &pstIn->stStartTime, sizeof(NET_TIME));
        memcpy(&m_PlayBackByTimeEnd, &pstIn->stStopTime, sizeof(NET_TIME));


        BOOL bPlayRet = PLAY_Play(1,GetDlgItem(IDC_SCREEN_PLAYBACK)->m_hWnd);
        if(bPlayRet)
        {
            BOOL bSuccess = PLAY_SetPlayDirection(1, 1);
            if (FALSE == bSuccess)
            {
                PLAY_Stop(1);
                PLAY_CloseStream(1);
                MessageBox(ConvertString("Set playback direction failed!"), ConvertString("Prompt"));
            }

            //Playback
            lHandle = CLIENT_PlayBackByTimeEx2(m_LoginID, nChannel, pstIn, pstOut);
            if(0 != lHandle)
            {
                m_nChannelID = nChannel;
                m_hPlayBack = lHandle;
                m_ePlayMode = EM_SERVERMODE;
                m_PlayBackType = EM_FILEBACK;
                m_PlayBackDirection = EM_PLAYBACK_DIRECTION_REVERSE;
                m_nReverseMode = 1;
                ChangeSpeedStatus(0);
                SetPlayControlButton(TRUE);
            }
            else
            {
                PLAY_Stop(1);
                PLAY_CloseStream(1);
                MessageBox(ConvertString("Playback failed!"), ConvertString("Prompt"));
            }
        }
        else
        {
            PLAY_CloseStream(1);
        }
    }
    
    CString strTest;
    GetDlgItemText(IDC_BUTTON_PLAYREVERSE, strTest);
    if (strTest != ConvertString("PlayReverse"))
    {
        SetDlgItemText(IDC_BUTTON_PLAYREVERSE, ConvertString("PlayReverse"));
    }

    strTest.Empty();
    GetDlgItemText(IDC_BUTTON_PLAY, strTest);
    if (strTest != ConvertString("Play"))
    {
        SetDlgItemText(IDC_BUTTON_PLAY, ConvertString("Play"));
    }

    return lHandle;

}