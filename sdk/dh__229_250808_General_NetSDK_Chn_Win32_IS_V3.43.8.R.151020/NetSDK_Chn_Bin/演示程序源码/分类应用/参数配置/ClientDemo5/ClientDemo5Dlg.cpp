// ClientDemo5Dlg.cpp : implementation file
//

#include "stdafx.h"
#pragma warning(disable:4786)
#include "ClientDemo5.h"
#include "ClientDemo5Dlg.h"
#include "DlgDVR.h"
#include <map>



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

// 参数配置返回信息
CString g_strRetInfo[5] = {
	ConvertString("succeed"),
	ConvertString("failed"),
	ConvertString("Invalid data"),
	ConvertString("device is busy"),
	ConvertString("no power")
};
std::map<DWORD, CString> g_oPerationTypeMap;
/////////////////////////////////////////////////////////////////////////////
// CClientDemo5Dlg dialog

CClientDemo5Dlg::CClientDemo5Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClientDemo5Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CClientDemo5Dlg)
	//m_strDvrIP= "10.64.3.71";
	//m_strDvrIP= "10.42.1.150";
	//m_strDvrIP= "10.61.5.141";
	//m_strDvrIP= "172.30.1.112";
    //m_strDvrIP = "172.11.2.131";
    m_strDvrIP = "172.23.2.103";
	m_nPort = 37777;
	m_strUserName = _T("admin");
	m_strPwd = _T("admin");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_LoginID = 0;
	m_nDevProtoVer = 4;
	m_dlgDeviceType = NULL;
	m_nVideoStandard = 0; 
	memset(&m_stuEncodeInfo, 0, sizeof(CFG_ENCODE_INFO));
	memset(&m_PTZInfo, 0, sizeof(CFG_PTZ_INFO));
	memset(&m_RecordInfo, 0, sizeof(CFG_RECORD_INFO));
	memset(&m_CommGroupInfo, 0, sizeof(CFG_COMMGROUP_INFO));
	//memset(&m_AlarmInfo, 0, sizeof(CFG_ALARMIN_INFO));
	m_AlarmInfo = new CFG_ALARMIN_INFO();
	if (m_AlarmInfo)
	{
		memset(m_AlarmInfo, 0, sizeof(CFG_ALARMIN_INFO));
	}
	m_MotionInfo = new CFG_MOTION_INFO();
	if (m_MotionInfo)
	{
		memset(m_MotionInfo, 0, sizeof(CFG_MOTION_INFO));
	}
	m_BlindInfo = new CFG_SHELTER_INFO;
	if (m_BlindInfo)
	{
		memset(m_BlindInfo, 0, sizeof(CFG_SHELTER_INFO));
	}
	m_VideoLostInfo = new CFG_VIDEOLOST_INFO;
	if (m_VideoLostInfo)
	{
		memset(m_VideoLostInfo, 0, sizeof(CFG_VIDEOLOST_INFO));
	}
	memset(&m_VideoCoveInfo, 0, sizeof(CFG_VIDEO_COVER));
	// 初始化需异步上报结果的操作类型（setConfig）
	g_oPerationTypeMap.clear();
	g_oPerationTypeMap[DH_DEV_DEVICECFG] = ConvertString("Set Device Attribute");
    g_oPerationTypeMap[DH_DEV_NETCFG] = ConvertString("Set Device NetConfig");
	g_oPerationTypeMap[DH_DEV_MAIL_CFG] = ConvertString("Set Mail Config");

}

CClientDemo5Dlg::~CClientDemo5Dlg()
{
	if (m_AlarmInfo)
	{
		delete m_AlarmInfo;
	}
	if (m_MotionInfo)
	{
		delete m_MotionInfo;
	}
	if (m_BlindInfo)
	{
		delete m_BlindInfo;
	}
	if (m_VideoLostInfo)
	{
		delete m_VideoLostInfo;
	}
	g_oPerationTypeMap.clear();
};

void CClientDemo5Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClientDemo5Dlg)
	DDX_Control(pDX, IDC_COMBO_CONFIGTYPE, m_ctlRevertType);
	DDX_Control(pDX, IDC_TAB_MAIN, m_ctlMainTab);
	DDX_Text(pDX, IDC_IPADDRESS_DVRIP, m_strDvrIP);
	DDX_Text(pDX, IDC_EDIT_PORT, m_nPort);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_strUserName);
	DDX_Text(pDX, IDC_EDIT_DVRPWD, m_strPwd);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CClientDemo5Dlg, CDialog)
	//{{AFX_MSG_MAP(CClientDemo5Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_LOGIN, OnBtnLogin)
	ON_BN_CLICKED(IDC_BTN_LOGOUT, OnBtnLogout)
	ON_WM_DESTROY()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MAIN, OnSelchangeTabMain)
	ON_BN_CLICKED(IDC_BUTTON_REVERT, OnButtonRevert)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientDemo5Dlg message handlers

BOOL CClientDemo5Dlg::OnInitDialog()
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
	
	//Initialize TabControl control
	InitTabControl();
	InitCombo();
	//Initialize SDK
	InitNetSDK();

//	SetTimer(1, 10000, NULL);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CClientDemo5Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CClientDemo5Dlg::OnPaint() 
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
HCURSOR CClientDemo5Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CClientDemo5Dlg::AddPage(CString strTitle, CDialog* dlgPage, UINT uID)
{
	if(NULL == dlgPage)
	{
		return FALSE;
	}
	
	DeletePage();

	m_dlgDeviceType = dlgPage;
	
	CRect childRect;
	m_ctlMainTab.GetClientRect(childRect);
	childRect.top += 20;
	childRect.bottom -= 4;
	childRect.left += 4;
	childRect.right -= 4;

	m_dlgDeviceType->Create(uID, &m_ctlMainTab);
	m_dlgDeviceType->MoveWindow(childRect);
	m_ctlMainTab.InsertItem(11, ConvertString(strTitle));

	return TRUE;
}

BOOL CClientDemo5Dlg::DeletePage()
{
	if(NULL != m_dlgDeviceType)
	{
		int nSel = m_ctlMainTab.GetCurSel();
		m_dlgDeviceType->ShowWindow(FALSE);
		m_dlgDeviceType->CloseWindow();
		m_ctlMainTab.DeleteItem(11);
		delete m_dlgDeviceType;
		m_dlgDeviceType = NULL;

		if(nSel == 11)
		{
			m_ctlMainTab.SetCurSel(10);
			DoTab(10);
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

//Register user to device 
#define TYPEMAP(a,b) case a:return (b)

CClientDemo5Dlg::PAGETYPE CClientDemo5Dlg::FromDeviceType(NET_DEVICE_TYPE eDeviceType)
{
	switch(eDeviceType)
	{
		TYPEMAP(NET_PRODUCT_NONE, NONE);
		TYPEMAP(NET_DVR_NONREALTIME_MACE, NONE);			// 非实时MACE
		TYPEMAP(NET_DVR_NONREALTIME, NONE);					// 非实时
		TYPEMAP(NET_NVS_MPEG1, NONE);						// 网络视频服务器
		TYPEMAP(NET_DVR_MPEG1_2, DVR);						// MPEG1二路录像机
		TYPEMAP(NET_DVR_MPEG1_8, DVR);						// MPEG1八路录像机
		TYPEMAP(NET_DVR_MPEG4_8, DVR);						// MPEG4八路录像机
		TYPEMAP(NET_DVR_MPEG4_16, DVR);					// MPEG4十六路录像机
		TYPEMAP(NET_DVR_MPEG4_SX2, DVR);					// LB系列录像机
		TYPEMAP(NET_DVR_MEPG4_ST2, DVR);					// GB系列录像机
		TYPEMAP(NET_DVR_MEPG4_SH2, DVR);					// HB系列录像机
		TYPEMAP(NET_DVR_MPEG4_GBE, DVR);			    	// GBE系列录像机
		TYPEMAP(NET_DVR_MPEG4_NVSII, DVR);					// II代网络视频服务器
		TYPEMAP(NET_DVR_STD_NEW, DVR);						// 新标准配置协议
		TYPEMAP(NET_DVR_DDNS, DVR);						// DDNS服务器
		TYPEMAP(NET_DVR_ATM, DVR);							// ATM机
		TYPEMAP(NET_NB_SERIAL, NONE);						// 二代非实时NB系列机器
		TYPEMAP(NET_LN_SERIAL, NONE);						// LN系列产品
		TYPEMAP(NET_BAV_SERIAL, NONE);						// BAV系列产品
		TYPEMAP(NET_SDIP_SERIAL, NONE);						// SDIP系列产品
		TYPEMAP(NET_IPC_SERIAL, IPC);						// IPC系列产品
		TYPEMAP(NET_NVS_B, NONE);							// NVS B系列
		TYPEMAP(NET_NVS_C, NONE);							// NVS H系列
		TYPEMAP(NET_NVS_S, NONE);							// NVS S系列
		TYPEMAP(NET_NVS_E, NONE);							// NVS E系列
		TYPEMAP(NET_DVR_NEW_PROTOCOL, DVR);				// 从QueryDevState中查询设备类型, NONE);以字符串格式
		TYPEMAP(NET_NVD_SERIAL, NONE);						// 解码器
		TYPEMAP(NET_DVR_N5, DVR);							// N5
		TYPEMAP(NET_DVR_MIX_DVR, DVR);						// 混合DVR
		TYPEMAP(NET_SVR_SERIAL, NONE);						// SVR系列
		TYPEMAP(NET_SVR_BS, NONE);							// SVR-BS
		default:return NONE;
	}
}
void CClientDemo5Dlg::OnBtnLogin() 
{
	// TODO: Add your control notification handler code here
	BOOL bValid = UpdateData(TRUE);
	if(bValid)
	{
		int err=0;	//Stroage the returned error value
		char *pchDVRIP;
	//	CString strDvrIP = GetDvrIP();
		pchDVRIP = (LPSTR)(LPCSTR)m_strDvrIP;
		WORD wDVRPort=(WORD)m_nPort;
		char *pchUserName=(LPSTR)(LPCSTR)m_strUserName;
		char *pchPassword=(LPSTR)(LPCSTR)m_strPwd;
		//Device informaiton
		NET_DEVICEINFO deviceInfo;

		// 分配内存失败，直接返回
		if (!m_recordDlg.InitRecordInfo())
		{
			m_LoginID = 0;
			//Display log in failure reason 
			MessageBox(ConvertString("Memory is not enough!"), ConvertString("Prompt"));
			return;
		}

		//Call log in interface
		LLONG lRet = CLIENT_Login(pchDVRIP,wDVRPort,pchUserName,pchPassword,&deviceInfo,&err);
		if(0 != lRet)
		{
			m_LoginID = lRet;
			int nRetLen = 0;
			NET_DEV_CHN_COUNT_INFO stuChn = { sizeof(NET_DEV_CHN_COUNT_INFO) };
			stuChn.stuVideoIn.dwSize = sizeof(stuChn.stuVideoIn);
			stuChn.stuVideoOut.dwSize = sizeof(stuChn.stuVideoOut);
			CLIENT_QueryDevState(m_LoginID, DH_DEVSTATE_DEV_CHN_COUNT, (char*)&stuChn, stuChn.dwSize, &nRetLen);
	        m_nChannel = __max(deviceInfo.byChanNum,stuChn.stuVideoIn.nMaxTotal);
			//m_nChannel = deviceInfo.byChanNum;
			GetDlgItem(IDC_BTN_LOGIN)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_LOGOUT)->EnableWindow(TRUE);

			//判断是否为三代协议设备
			int len = 0;
			DH_DEV_ENABLE_INFO stDevEn = {0};
			BOOL bRet = CLIENT_QuerySystemInfo(m_LoginID, ABILITY_DEVALL_INFO, (char*)&stDevEn, sizeof(DH_DEV_ENABLE_INFO), &len);
			if (bRet && len == sizeof(DH_DEV_ENABLE_INFO))
			{
				if (stDevEn.IsFucEnable[EN_JSON_CONFIG]!=0 || deviceInfo.byChanNum >= 32)
				{
					m_b3ProDev = TRUE;
				}
				else
				{
					m_b3ProDev = FALSE;
				}
			}
			else
			{
				m_b3ProDev = FALSE;
			}

			//Get protocol version number 
			int nProtoVer = 0;
			int nRet = 0;
			BOOL bSuccess = CLIENT_QueryDevState(m_LoginID, DH_DEVSTATE_PROTOCAL_VER, (char*)&nProtoVer, sizeof(int), &nRet, 1000);
			if (bSuccess)
			{
				if (nProtoVer >= 5)		//This device is 2.6 basic line or higher 
				{
					m_nDevProtoVer = nProtoVer;
				}
			}

			//Device property 
			GetDeviceConfigInfo();
			//Video channel property 		
			GetChannelConfigInfo();
			//Video in property
			GetVideoInputOption();
			//COM property 
			GetCommConfigInfo();
			//Record configuration 
 			GetRecordConfigInfo();
			//Network configuration 
			GetNetWorkConfigInfo();
			//Alarm property 
  	    	GetAlarmConfigInfo();
			//Multiple privacy mask zones 
			GetCoverConfigInfo();
			//Strategy configuraiton
			GetStrategyConfigInfo();
			//ftp configuration
 			//GetFTPInfo();
			GetFtpExInfo();
            GetChannelConfigInfoEx();
			PAGETYPE pageType = FromDeviceType((NET_DEVICE_TYPE)deviceInfo.byDVRType);
			if(pageType == IPC)
			{
				CDlgIPC* dlgIPC = new CDlgIPC;
				this->AddPage("IPC configure", dlgIPC, IDD_DIALOG_IPC);
				dlgIPC->PostMessage(WM_COMMAND, IDC_BUTTON_READ, 0);
				dlgIPC->SetLoginHandle(lRet, m_b3ProDev);
			}
			else if(pageType == DVR)
			{
				CDlgDVR* dlgDVR = new CDlgDVR;
				this->AddPage("DVR configure", dlgDVR, IDD_DIALOG_DVR);
				dlgDVR->PostMessage(WM_COMMAND, IDC_BUTTON_READ, 0);
				dlgDVR->SetLoginHandle(lRet, m_b3ProDev);
			}
		}
		else
		{
			m_LoginID = 0;
			//Display log in failure reason 
			ShowLoginErrorReason(err);
		}
	}
}

//Logout device user 
void CClientDemo5Dlg::OnBtnLogout() 
{
	// TODO: Add your control notification handler code here
	DeletePage();
	BOOL bRet = CLIENT_Logout(m_LoginID);
	//Clear handle as o after logout 
	if(bRet)
	{
		m_LoginID=0;
		GetDlgItem(IDC_BTN_LOGIN)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_LOGOUT)->EnableWindow(FALSE);
		//Device property 
		m_serverDlg.CleanAll();
		//Video channel property 
		m_channelDlg.CleanAll();
		//Video In property
		m_VideoInDlg.CleanAll();
		//COM property 
		m_commDlg.CleanAll();
		//Record configuration 
		m_recordDlg.CleanAll();
		//Network configuration 
		m_networkDlg.CleanAll();
		//Alarm property 
		m_alarmDlg.CleanAll();
		//Multiple privacy mask zones 
		m_coverDlg.CleanAll();
		//Configuration strategy 
		m_StrategyDlg.CleanAll();
		// ftp
//		m_configFTP.CleanAll();
		// ftpex
		//m_configFTPEX.CleanAll();
        m_configFTPMain.CleanAll();

	}	
	else
	{
		MessageBox(ConvertString("Logout failed!"), ConvertString("Prompt"));
	}
}

BOOL CALLBACK MessCallBackFunc(LONG lCommand, LLONG lLoginID, char *pBuf, DWORD dwBufLen, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser)
{
	if (NULL == pBuf)
	{
		return FALSE;
	}
	CString str;
	switch(lCommand)
	{
		// 处理异步接口返回结果
		case DH_CONFIG_RESULT_EVENT_EX:
			{
				DEV_SET_RESULT *pSetRet =(DEV_SET_RESULT *)pBuf;
				CString strOperation = g_oPerationTypeMap[pSetRet->dwType];
				if (strOperation.IsEmpty() 
					|| 0 > pSetRet->wResultCode 
					|| 4 < pSetRet->wResultCode)
				{
					break;
				}
                if( pSetRet->dwType == DH_DEV_NETCFG && pSetRet->wResultCode  == 0)
                {
                    break;
                }
				str.Format(ConvertString("operation:%s, result:%s"), 
					strOperation, g_strRetInfo[pSetRet->wResultCode]);
				if (pSetRet->wRebootSign)
				{
					str.Insert(str.GetLength(),ConvertString(",devide need restart!"));
				}
			}
			break;
		default:
			break;
	}
	if (!str.IsEmpty())
	{
        CClientDemo5Dlg* pClientDlg = (CClientDemo5Dlg*)dwUser;
        if (NULL != pClientDlg)
        {
            pClientDlg->MessageBox(str, ConvertString("Prompt"));
        }
        //::MessageBox(NULL, str, ConvertString("Prompt"),MB_OK);
	}
	return TRUE;
}

//Initialize SDK
void CClientDemo5Dlg::InitNetSDK()
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
	CClientDemo5Dlg *dlg = (CClientDemo5Dlg *)dwUser;
	dlg->DeviceDisConnect(lLoginID, pchDVRIP,nDVRPort);
}

//Disposal when device disconnected 
void CClientDemo5Dlg::DeviceDisConnect(LLONG lLoginID, char *sDVRIP, LONG nDVRPort)
{
	//Add device disconnection process code 
	MessageBox(ConvertString("Network disconnected!"), ConvertString("Prompt"));
	
}

void CClientDemo5Dlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	// Logout 
	if(0 != m_LoginID)
	{
		DeletePage();
		BOOL bLogout = CLIENT_Logout(m_LoginID);
		m_LoginID=0;
		GetDlgItem(IDC_BTN_LOGIN)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_LOGOUT)->EnableWindow(FALSE);
		//Device property 
		m_serverDlg.CleanAll();
		//Video channel property 
		m_channelDlg.CleanAll();
		//Video option  property
		m_VideoInDlg.CleanAll();
		//COM property 
		m_commDlg.CleanAll();
		//Record configuration 
		m_recordDlg.CleanAll();
		//Network configuration 
		m_networkDlg.CleanAll();
		//Alarm property 
		m_alarmDlg.CleanAll();
		//Multiple privacy mask zones 
		m_coverDlg.CleanAll();
		//Configuration strategy 
		m_StrategyDlg.CleanAll();
		// ftp
//		m_configFTP.CleanAll();
		// ftpex
		m_configFTPMain.CleanAll();
        m_channelDlgEx.CleanAll();


	}
	//Clear SDK, release resources  
	CLIENT_Cleanup();
}

//Get DVR IP
/*CString CClientDemo5Dlg::GetDvrIP()
{
	CString strRet="";
	BYTE nField0,nField1,nField2,nField3;
	m_strDvrIP.GetAddress(nField0,nField1,nField2,nField3);
	strRet.Format("%d.%d.%d.%d",nField0,nField1,nField2,nField3);
	return strRet;
}*/

//Display log in failure reason 
void CClientDemo5Dlg::ShowLoginErrorReason(int nError)
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

//Initialize TabControl control
void CClientDemo5Dlg::InitTabControl()
{
	CRect childRect;
	m_ctlMainTab.GetClientRect(childRect);
	childRect.top += 20;
	childRect.bottom -= 4;
	childRect.left += 4;
	childRect.right -= 4;

	//Create non-mode dialogue box. Specified tag is non-mode dialogue box father window.
	m_serverDlg.Create(IDD_CONFIG_SERVER, &m_ctlMainTab);
	m_serverDlg.MoveWindow(childRect);
	m_channelDlg.Create(IDD_CONFIG_CHANNEL, &m_ctlMainTab);
	m_channelDlg.MoveWindow(childRect);
	m_commDlg.Create(IDD_CONFIG_COMM, &m_ctlMainTab);
	m_commDlg.MoveWindow(childRect);
	m_alarmDlg.Create(IDD_CONFIG_ALARM, &m_ctlMainTab);
	m_alarmDlg.MoveWindow(childRect);
	m_recordDlg.Create(IDD_CONFIG_RECORD, &m_ctlMainTab);
	m_recordDlg.MoveWindow(childRect);
	m_networkDlg.Create(IDD_CONFIG_NETWORK, &m_ctlMainTab);
	m_networkDlg.MoveWindow(childRect);
	m_coverDlg.Create(IDD_CONFIG_COVER, &m_ctlMainTab);
	m_coverDlg.MoveWindow(childRect);
	m_StrategyDlg.Create(IDD_CONFIG_STRATEGY,&m_ctlMainTab);
	m_StrategyDlg.MoveWindow(childRect);
	m_configFile.Create(IDD_DIALOG_CONFIG_FILE,&m_ctlMainTab);
	m_configFile.MoveWindow(childRect);
//	m_configFTP.Create(IDD_CONFIG_FTP, &m_ctlMainTab);
//	m_configFTP.MoveWindow(childRect);
	m_VideoInDlg.Create(IDD_CONFIG_VIDEOIN, &m_ctlMainTab);
	m_VideoInDlg.MoveWindow(childRect);
	//m_configFTPEX.Create(IDD_CONFIG_FTPEX, &m_ctlMainTab);
	//m_configFTPEX.MoveWindow(childRect);
    m_configFTPMain.Create(IDD_CONFIG_FTPMAIN, &m_ctlMainTab);
	m_configFTPMain.MoveWindow(childRect);
    m_channelDlgEx.Create(IDD_CONFIG_CHANNEL_EX, &m_ctlMainTab);
	m_channelDlgEx.MoveWindow(childRect);

	m_ctlMainTab.InsertItem(0, ConvertString("Device Attribute"));
	m_ctlMainTab.InsertItem(1, ConvertString("Image Channel Attribute"));
	m_ctlMainTab.InsertItem(2, ConvertString("VideoInpuOption"));	
	m_ctlMainTab.InsertItem(3, ConvertString("COM Attribute"));
	m_ctlMainTab.InsertItem(4, ConvertString("Record Config"));
	m_ctlMainTab.InsertItem(5, ConvertString("Network Config"));
	m_ctlMainTab.InsertItem(6, ConvertString("Alarm Attribute"));
	m_ctlMainTab.InsertItem(7, ConvertString("Multi-area Shelter"));
	m_ctlMainTab.InsertItem(8, ConvertString("strategy"));
	m_ctlMainTab.InsertItem(9, ConvertString("FTP Config"));
    m_ctlMainTab.InsertItem(10, ConvertString("Image Channel AttributeEx"));

	m_ctlMainTab.SetCurSel(0);
	DoTab(0);
}

void CClientDemo5Dlg::DoTab(int nTab)
{
	//Check nTab value is within the threshold
	if(nTab>11)
	{
		nTab=11;
	}
	if(nTab<0)
	{
		nTab=0;
	}
	
	BOOL bTab[12];
	bTab[0]=bTab[1]=bTab[2]=bTab[3]=bTab[4]=bTab[5]=bTab[6]=bTab[7]=bTab[8]=bTab[9]=bTab[10]=bTab[11]= FALSE;
	bTab[nTab]=TRUE;
	
	//Display or hide dialogue box 
	SetDlgState(&m_serverDlg,bTab[0]);
	SetDlgState(&m_channelDlg,bTab[1]);
	SetDlgState(&m_VideoInDlg,bTab[2]);
	SetDlgState(&m_commDlg,bTab[3]);
	SetDlgState(&m_recordDlg,bTab[4]);
	SetDlgState(&m_networkDlg,bTab[5]);
	SetDlgState(&m_alarmDlg,bTab[6]);
	SetDlgState(&m_coverDlg,bTab[7]);
	SetDlgState(&m_StrategyDlg,bTab[8]);
	SetDlgState(&m_configFTPMain,bTab[9]);
    SetDlgState(&m_channelDlgEx,bTab[10]);
	
	if(NULL != m_dlgDeviceType)
	{
		SetDlgState(m_dlgDeviceType,bTab[11]);
	}
	

}

void CClientDemo5Dlg::SetDlgState(CWnd *pWnd, BOOL bShow)
{
	if(bShow)
	{
		pWnd->ShowWindow(SW_SHOW);
	}
	else
	{
		pWnd->ShowWindow(SW_HIDE);
	}
}

void CClientDemo5Dlg::OnSelchangeTabMain(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int nSelect = m_ctlMainTab.GetCurSel();
	if(nSelect>=0)
	{
		DoTab(nSelect);
	}
	*pResult = 0;
}

//Get device property configuration information 
void CClientDemo5Dlg::GetDeviceConfigInfo()
{
	if(0 != m_LoginID)
	{
		DWORD dwRetLen = 0;
		int nWaitTime = 1000;
		DH_QUICK_QUERY_CFG_EN stQuickQueryEn = {0};
		BOOL bSuccess = CLIENT_QuerySystemInfo(m_LoginID, ABILITY_QUICK_QUERY_CFG, (char *)&stQuickQueryEn, sizeof(DH_QUICK_QUERY_CFG_EN), (int *)&dwRetLen);
		if (bSuccess && dwRetLen == sizeof(DH_QUICK_QUERY_CFG_EN)) 
		{
			if (stQuickQueryEn.IsQuickQueryEnable == 1) 
			{
				nWaitTime = 60000;
			}
		}
		DHDEV_SYSTEM_ATTR_CFG sysConfigInfo = {0};
		bSuccess = CLIENT_GetDevConfig(m_LoginID, DH_DEV_DEVICECFG, 0,
			&sysConfigInfo, sizeof(DHDEV_SYSTEM_ATTR_CFG), &dwRetLen, nWaitTime);
		if (bSuccess && dwRetLen == sizeof(DHDEV_SYSTEM_ATTR_CFG))
		{
			if (sysConfigInfo.stVersion.dwSoftwareVersion == 131282 
				&& sysConfigInfo.byDevType == NET_IPC_SERIAL)
			{
				m_b3ProDev = FALSE;
			}

	
			//Initialize dialogue box
			m_serverDlg.InitDlgInfo(&sysConfigInfo, m_nChannel);
		}
	}
	else
	{
		MessageBox(ConvertString("Login first!"), ConvertString("Prompt"));
	}
}

//Set device property configuration information 
void CClientDemo5Dlg::SetDeviceConfigInfo(LPDHDEV_SYSTEM_ATTR_CFG sysConfigInfo)
{
	if(0 != m_LoginID && sysConfigInfo != NULL)
	{
		//First read informaiton 
		DWORD dwRetLen = 0;
		int nWaitTime = 1000;
		DH_QUICK_QUERY_CFG_EN stQuickQueryEn = {0};
		BOOL bSuccess = CLIENT_QuerySystemInfo(m_LoginID, ABILITY_QUICK_QUERY_CFG, (char *)&stQuickQueryEn, sizeof(DH_QUICK_QUERY_CFG_EN), (int *)&dwRetLen);
		if (bSuccess && dwRetLen == sizeof(DH_QUICK_QUERY_CFG_EN)) 
		{
			if (stQuickQueryEn.IsQuickQueryEnable == 1) 
			{
				nWaitTime = 60000;
			}
		}
		DHDEV_SYSTEM_ATTR_CFG sysDevInfo = {0};
		bSuccess = CLIENT_GetDevConfig(m_LoginID, DH_DEV_DEVICECFG, 0,
			&sysDevInfo, sizeof(DHDEV_SYSTEM_ATTR_CFG), &dwRetLen, nWaitTime);
		if (bSuccess && dwRetLen == sizeof(DHDEV_SYSTEM_ATTR_CFG))
		{
			//Modify information 
			sysDevInfo.wDevNo = sysConfigInfo->wDevNo;
			sysDevInfo.byOverWrite = sysConfigInfo->byOverWrite;
			sysDevInfo.byRecordLen = sysConfigInfo->byRecordLen;
			sysDevInfo.byVideoStandard = sysConfigInfo->byVideoStandard;
			sysDevInfo.byDateFormat = sysConfigInfo->byDateFormat;
			sysDevInfo.byDateSprtr = sysConfigInfo->byDateSprtr;
			sysDevInfo.byTimeFmt = sysConfigInfo->byTimeFmt;

			//Save information 
			BOOL bSuccess = CLIENT_SetDevConfig(m_LoginID, DH_DEV_DEVICECFG, 0,
				&sysDevInfo, sizeof(DHDEV_SYSTEM_ATTR_CFG));

		}
	}
	else
	{
		MessageBox(ConvertString("Login first!"), ConvertString("Prompt"));
	}
}

//Get video channel property 
void CClientDemo5Dlg::GetChannelConfigInfo()
{
	if(0 != m_LoginID)
	{
		DWORD dwRetLen = 0;
		int nWaitTime = 1000;
		DH_QUICK_QUERY_CFG_EN stQuickQueryEn = {0};
		BOOL bSuccess = CLIENT_QuerySystemInfo(m_LoginID, ABILITY_QUICK_QUERY_CFG, (char *)&stQuickQueryEn, sizeof(DH_QUICK_QUERY_CFG_EN), (int *)&dwRetLen);
		if (bSuccess && dwRetLen == sizeof(DH_QUICK_QUERY_CFG_EN)) 
		{
			if (stQuickQueryEn.IsQuickQueryEnable == 1) 
			{
				nWaitTime = 60000;
			}
		}
		DHDEV_SYSTEM_ATTR_CFG sysConfigInfo = {0};
		bSuccess = CLIENT_GetDevConfig(m_LoginID, DH_DEV_DEVICECFG, 0,
			&sysConfigInfo, sizeof(DHDEV_SYSTEM_ATTR_CFG), &dwRetLen, nWaitTime);
		if (bSuccess && dwRetLen == sizeof(DHDEV_SYSTEM_ATTR_CFG))
		{
			int nChannelCount = m_nChannel > CHANNEL_NUM_LIMIT ? CHANNEL_NUM_LIMIT : m_nChannel;
			m_nVideoStandard = sysConfigInfo.byVideoStandard;
			
			CString str = (LPCSTR)(sysConfigInfo.szDevType);
			if (0 == str.Compare("NVR") || 0 == str.Compare("EVS5000"))
			{
				char  szTmpBuff[128 * 1024] = {0};
				BOOL bRet = FALSE;
				int iLen = 0;
				bRet = CLIENT_QueryNewSystemInfo(m_LoginID,CFG_CMD_ENCODE_GETCAPS, 0,szTmpBuff,128 * 1024,&iLen,1000);
				if (bRet)
				{
					bRet = CLIENT_ParseData(CFG_CMD_ENCODE_GETCAPS, szTmpBuff, m_channelDlg.GetEncodeCap(),sizeof(CFG_ENCODECAP), &iLen);
					if (bRet)
					{
						m_channelDlg.m_bShowFpsRange = TRUE;
					}
				}
			}
			

			m_channelDlg.InitDlgInfo(nChannelCount, sysConfigInfo.byVideoStandard, m_nDevProtoVer, m_b3ProDev);

		}
	}
	else
	{
		MessageBox(ConvertString("Login first!"), ConvertString("Prompt"));
	}
}
void CClientDemo5Dlg::GetVideoInputOption()
{
	if(0 != m_LoginID)
	{
		int nChannelCount = m_nChannel > CHANNEL_NUM_LIMIT ? CHANNEL_NUM_LIMIT : m_nChannel;
		m_VideoInDlg.InitDlgInfo(nChannelCount);
	}
	else
	{
		MessageBox(ConvertString("Login first!"), ConvertString("Prompt"));
	}
}



void CClientDemo5Dlg::GetOneChannelDspConfig(int nCurChannel, DHDEV_DSP_ENCODECAP &stDspInfo, CFG_DSPENCODECAP_INFO &stDspEncodeCapInfo, NET_OUT_ENCODE_CFG_CAPS& stEncodeCfgCaps,  BOOL& bShowPix)
{
	
	bShowPix = FALSE;
	int nRetLen = 0;
	BOOL isQueryDevStateSucceeded = CLIENT_QueryDevState(m_LoginID, DH_DEVSTATE_DSP, (char*)&stDspInfo, sizeof(DHDEV_DSP_ENCODECAP), &nRetLen, 3000);

	int nerror;
	int nBufLen =  100*1024;
	char *szOutBuffer = new char[nBufLen];
	if (szOutBuffer == NULL)
	{
		return;
	}
	
	BOOL isGetNewDevConfigSucceeded = CLIENT_GetNewDevConfig(m_LoginID, CFG_CMD_HDVR_DSP, nCurChannel, szOutBuffer, nBufLen, &nerror, 3000);		
	if (isGetNewDevConfigSucceeded)
	{
		//解析
		BOOL bRet = CLIENT_ParseData(CFG_CMD_HDVR_DSP, szOutBuffer, (char*)&stDspEncodeCapInfo, sizeof(CFG_DSPENCODECAP_INFO), &nRetLen);
		if (bRet)
		{
			bShowPix = TRUE;
			if (!isQueryDevStateSucceeded || !stDspInfo.dwImageSizeMask || !stDspInfo.dwEncodeModeMask)
			{
				stDspInfo.dwImageSizeMask = stDspEncodeCapInfo.dwImageSizeMask;
				{
					for(int i=0;i<sizeof(stDspInfo.dwImageSizeMask_Assi)/sizeof(stDspInfo.dwImageSizeMask_Assi[0]);i++)
						stDspInfo.dwImageSizeMask_Assi[i] = stDspEncodeCapInfo.dwImageSizeMask_Assi[i];
				}
				stDspInfo.dwEncodeModeMask = stDspEncodeCapInfo.dwEncodeModeMask;
				stDspInfo.bEncodeCap = stDspEncodeCapInfo.bEncodeCap;
				{
					for (int i=0;i<sizeof(stDspInfo.bMaxFrameOfImageSize)/sizeof(stDspInfo.bMaxFrameOfImageSize[0]);i++)
						stDspInfo.bMaxFrameOfImageSize[i] = stDspEncodeCapInfo.bMaxFrameOfImageSize[i];	
				}
				stDspInfo.dwMaxEncodePower = stDspEncodeCapInfo.dwMaxEncodePower;
				stDspInfo.dwStreamCap = stDspEncodeCapInfo.dwStreamCap ;
				stDspInfo.dwVideoStandardMask = stDspEncodeCapInfo.dwVideoStandardMask;
				stDspInfo.wChannelMaxSetSync = stDspEncodeCapInfo.wChannelMaxSetSync;
				stDspInfo.wMaxSupportChannel = stDspEncodeCapInfo.wMaxSupportChannel;
			}
		}
	}
	
	CFG_ENCODE_INFO encInfo = {0};
	std::string jsonBuf(32*1024, 0);
    CLIENT_PacketData(CFG_CMD_ENCODE, &encInfo, sizeof(encInfo), &jsonBuf[0], jsonBuf.size()); // need a null json string...
	NET_IN_ENCODE_CFG_CAPS encCapIn = {sizeof(encCapIn), nCurChannel, 0, &jsonBuf[0]};
	MEM_ZERO(stEncodeCfgCaps);
	SET_SIZE(stEncodeCfgCaps);
	NET_STREAM_CFG_CAPS& mainCaps = stEncodeCfgCaps.stuMainFormatCaps[0];
    // 需要获取该项，则dwSize必须填写
	// 注意此处仅获取了主码流一般录像的配置能力，如果日后有需要则要添加辅码流和其他录像类型
    SET_SIZE(mainCaps);

    if (CLIENT_GetDevCaps(m_LoginID, NET_ENCODE_CFG_CAPS, &encCapIn, &stEncodeCfgCaps, 3000))
    {
		if (!isGetNewDevConfigSucceeded || !isQueryDevStateSucceeded || !stDspInfo.dwImageSizeMask || !stDspInfo.dwEncodeModeMask)
		{
			stDspInfo.dwEncodeModeMask = mainCaps.dwEncodeModeMask;

			for (int i(0); i < mainCaps.nResolutionTypeNum; ++i)
			{
				stDspInfo.dwImageSizeMask |= 1<<ResolutionInttoSize(mainCaps.stuResolutionTypes[i].snWidth, mainCaps.stuResolutionTypes[i].snHight);
			}
		}
    }
	if (szOutBuffer)
	{
		delete[]szOutBuffer;
	}
}

void CClientDemo5Dlg::GetOneChannelDspConfigF6(int nCurChannel, CFG_ENCODE_INFO& encInfo, NET_OUT_ENCODE_CFG_CAPS& stEncodeCfgCaps, BOOL& bShowPix)
{
    bShowPix = FALSE;
    std::string jsonBuf(32*1024, 0);
    CLIENT_PacketData(CFG_CMD_ENCODE, &encInfo, sizeof(encInfo), &jsonBuf[0], jsonBuf.size()); // need a null json string...
    NET_IN_ENCODE_CFG_CAPS encCapIn = {sizeof(encCapIn), nCurChannel, 0, &jsonBuf[0]};
    MEM_ZERO(stEncodeCfgCaps);
    SET_SIZE(stEncodeCfgCaps);
    NET_STREAM_CFG_CAPS& mainCaps = stEncodeCfgCaps.stuMainFormatCaps[0];
    // 需要获取该项，则dwSize必须填写
    SET_SIZE(mainCaps);
    SET_SIZE(stEncodeCfgCaps.stuExtraFormatCaps[0]);
    SET_SIZE(stEncodeCfgCaps.stuSnapFormatCaps[0]);
    if (CLIENT_GetDevCaps(m_LoginID, NET_ENCODE_CFG_CAPS, &encCapIn, &stEncodeCfgCaps, 3000))
    {
        bShowPix = TRUE;
    }
}

void CClientDemo5Dlg::GetOneChannelConfigInfo(CFG_ENCODE_INFO *pstEncodeInfo, int nCurChannel)
{
	if(0 != m_LoginID)
	{
		if (pstEncodeInfo == NULL)
		{
			return;
		}
		
		char *szOutBuffer = new char[32*1024];
		if (szOutBuffer == NULL)
		{
			return;	
		}
		if (nCurChannel < 0 || nCurChannel >= CHANNEL_NUM_LIMIT)
		{
			return;
		}
		
		int i = nCurChannel;
		int nerror = 0;
		
		BOOL bSuccess = CLIENT_GetNewDevConfig(m_LoginID, CFG_CMD_ENCODE, i, szOutBuffer, 32*1024, &nerror, 5000);		
		if (bSuccess)
		{

			memset(pstEncodeInfo, 0, sizeof(CFG_ENCODE_INFO));
			memset(&m_stuEncodeInfo, 0, sizeof(CFG_ENCODE_INFO));


			int nRetLen = 0;
			
			//解析
			BOOL bRet = CLIENT_ParseData(CFG_CMD_ENCODE, (char *)szOutBuffer, &m_stuEncodeInfo, sizeof(CFG_ENCODE_INFO), &nRetLen);
			if (bRet)
			{
				memcpy(pstEncodeInfo, &m_stuEncodeInfo, sizeof(CFG_ENCODE_INFO));
			}
			else
			{
				MessageBox(ConvertString("Parse data error"), ConvertString("Prompt"));
			}
		}
		else
		{
			MessageBox(ConvertString("Get encode data failed!"), ConvertString("Prompt"));

		}
		if (szOutBuffer)
		{
			delete []szOutBuffer;
			szOutBuffer = NULL;
		}
	}
	else
	{
		MessageBox(ConvertString("Login first!"), ConvertString("Prompt"));
	}	

}

void CClientDemo5Dlg::SetOneChannelConfigInfo(CFG_ENCODE_INFO *pstEncodeInfo, int nCurChannel)
{
	if(0 != m_LoginID && pstEncodeInfo != NULL)
	{	
		int nerror = 0;
		int nFailCount = 0;
		int nrestart = 0;
		int i = nCurChannel;
		DWORD deTime = GetTickCount();

		char *szOutBuffer = new char[32*1024];
		if (szOutBuffer == NULL)
		{
			return;	
		}

		BOOL bRet = CLIENT_PacketData(CFG_CMD_ENCODE, (char *)pstEncodeInfo, sizeof(CFG_ENCODE_INFO), szOutBuffer, 32*1024);
		if (bRet == FALSE)
		{
			MessageBox(ConvertString("Pack data failed!"), ConvertString("Prompt"));
		}
		else
		{
			BOOL bSuccess = CLIENT_SetNewDevConfig(m_LoginID, CFG_CMD_ENCODE, i, szOutBuffer, 32*1024, &nerror, &nrestart, 5000);		
			if (bSuccess)
			{
				if (nrestart == 1)
				{
					MessageBox(ConvertString("Save config info successfully!devide need restart!"), ConvertString("Prompt"));
				}
			}
			else
			{
				if (CLIENT_GetLastError() == NET_RETURN_DATA_ERROR)
				{
					MessageBox(ConvertString("Invalid config, please ensure that all values (bitrate, framerate, etc.) are in available range!"), ConvertString("Prompt"));
				}
				else
				{
					MessageBox(ConvertString("Save encode info failed!"), ConvertString("Prompt"));
				}
			}		
		}

		if (szOutBuffer)
		{
			delete []szOutBuffer;
			szOutBuffer = NULL;
		}	
	}
	else
	{
		MessageBox(ConvertString("Login first!"), ConvertString("Prompt"));
	}
}

//Get COM property configuration information
void CClientDemo5Dlg::GetCommConfigInfo()
{
	if(0 != m_LoginID)
	{
		DWORD dwRetLen = 0;
		int nWaitTime = 1000;
		DH_QUICK_QUERY_CFG_EN stQuickQueryEn = {0};
		BOOL bSuccess = CLIENT_QuerySystemInfo(m_LoginID, ABILITY_QUICK_QUERY_CFG, (char *)&stQuickQueryEn, sizeof(DH_QUICK_QUERY_CFG_EN), (int *)&dwRetLen);
		if (bSuccess && dwRetLen == sizeof(DH_QUICK_QUERY_CFG_EN)) 
		{
			if (stQuickQueryEn.IsQuickQueryEnable == 1) 
			{
				nWaitTime = 60000;
			}
		}
		
		DHDEV_SYSTEM_ATTR_CFG sysConfigInfo = {0};
		bSuccess = CLIENT_GetDevConfig(m_LoginID, DH_DEV_DEVICECFG, 0,
			&sysConfigInfo, sizeof(DHDEV_SYSTEM_ATTR_CFG), &dwRetLen, nWaitTime);
		if (bSuccess && dwRetLen == sizeof(DHDEV_SYSTEM_ATTR_CFG))
		{

			DEV_COMM_CFG_EX CommExInfo = {0};
			//COM amount
			BYTE nCommCount = sysConfigInfo.byComIONum > 2 ? 2 : sysConfigInfo.byComIONum;
			//Channel amount
			int nChannelCount = m_nChannel > CHANNEL_NUM_LIMIT ? CHANNEL_NUM_LIMIT : m_nChannel;
			
			//COM property
			DHDEV_COMM_CFG CommInfo = {0};
			bSuccess = CLIENT_GetDevConfig(m_LoginID, DH_DEV_COMMCFG, 0,
				&CommInfo, sizeof(DHDEV_COMM_CFG), &dwRetLen);
			if (bSuccess && dwRetLen == sizeof(DHDEV_COMM_CFG))
			{
				int i = 0;
				for (i = 0; i < DH_MAX_DECPRO_LIST_SIZE; i++)
				{
					strcpy((char *)&CommExInfo.DecProName[i], (char *)&CommInfo.DecProName[i]);
				}
				for (i = 0; i < DH_MAX_232FUNCS; i++)
				{
					strcpy((char *)&CommExInfo.s232FuncName[i], (char *)&CommInfo.s232FuncName[i]);
				}
				
				CommExInfo.dw232FuncNameNum = CommInfo.dw232FuncNameNum;
				CommExInfo.dwDecProListNum = CommInfo.dwDecProListNum;
				memcpy(CommExInfo.st232, CommInfo.st232, DH_MAX_232_NUM*sizeof(DH_RS232_CFG));
				memcpy(CommExInfo.stDecoder, CommInfo.stDecoder, DH_MAX_DECODER_NUM*sizeof(DH_485_CFG));			
			}
			
			if (m_b3ProDev == TRUE)
			{
				int nerror = 0;
				int nRetLen = 0;
				int i = 0;
				BOOL bSuccess = FALSE;
				BOOL bRet = FALSE;
				char *szOutBuffer = new char[32*1024];
				if (szOutBuffer == NULL)
				{
					return;	
				}
				
				bSuccess = CLIENT_GetNewDevConfig(m_LoginID, CFG_CMD_COMM, i, szOutBuffer, 32*1024, &nerror, 3000);
				if(bSuccess)
				{
					bRet = CLIENT_ParseData(CFG_CMD_COMM, szOutBuffer, &m_CommGroupInfo, sizeof(CFG_COMMGROUP_INFO), &nRetLen);
					if(bRet)
					{
				
					}
					else
					{
						MessageBox(ConvertString("Parse data failed!"), ConvertString("Prompt"));
					}
				}
				else
				{
					MessageBox(ConvertString("GetConfig failed(Comm232)!"), ConvertString("Prompt"));
				}

				int iFailCount = 0;
				for (i = 0; i < nChannelCount; i++)
				{
					bSuccess = CLIENT_GetNewDevConfig(m_LoginID, CFG_CMD_PTZ, i, szOutBuffer, 32*1024, &nerror, 3000);		
					if (bSuccess)
					{
						//解析
						bRet = CLIENT_ParseData(CFG_CMD_PTZ, (char *)szOutBuffer, &m_PTZInfo, sizeof(CFG_PTZ_INFO), &nRetLen);
						if (bRet)
						{
							//CommExInfo.stDecoder[i].wProtocol = m_PTZInfo.nProName;
							CommExInfo.stDecoder[i].wDecoderAddress = m_PTZInfo.nDecoderAddress;	
							CommExInfo.stDecoder[i].bPTZType = m_PTZInfo.nPTZType;	
							CommExInfo.stDecoder[i].byMartixID = m_PTZInfo.nMartixID;	
							CommExInfo.stDecoder[i].struComm.byBaudRate = m_PTZInfo.struComm.byBaudRate;	
							CommExInfo.stDecoder[i].struComm.byDataBit = m_PTZInfo.struComm.byDataBit;	
							CommExInfo.stDecoder[i].struComm.byStopBit = m_PTZInfo.struComm.byStopBit;	
							CommExInfo.stDecoder[i].struComm.byParity = m_PTZInfo.struComm.byParity;

//							memcpy(&m_PTZInfo2[i], &m_PTZInfo, sizeof(CFG_PTZ_INFO));
						}
						else
						{
							iFailCount++;
						}
					}
					else
					{
						iFailCount++;
					}
				}	
				if (0 < iFailCount)
				{
					MessageBox(ConvertString("GetConfig failed(Comm)!"), ConvertString("Prompt"));
				}
				if (szOutBuffer)
				{
					delete []szOutBuffer;
					szOutBuffer = NULL;
				}
			}

			//Initialize dialogue box
			m_commDlg.InitDlgInfo(&CommExInfo,nCommCount,nChannelCount);
		}
	}
	else
	{
		MessageBox(ConvertString("Login first!"), ConvertString("Prompt"));
	}
}

//Save COM property configuration information 
void CClientDemo5Dlg::SetCommConfigInfo(DEV_COMM_CFG_EX *pCommInfo, int nCurChannel)
{
	if(0 != m_LoginID && pCommInfo != NULL)
	{
		DHDEV_COMM_CFG CommInfo = {0};
		int i = 0;
		for (i = 0; i < DH_MAX_DECPRO_LIST_SIZE; i++)
		{
			strcpy((char *)&CommInfo.DecProName[i], (char *)&pCommInfo->DecProName[i]);
		}
		for (i = 0; i < DH_MAX_232FUNCS; i++)
		{
			strcpy((char *)&CommInfo.s232FuncName[0], (char *)&pCommInfo->s232FuncName[0]);
		}
		
		CommInfo.dw232FuncNameNum = pCommInfo->dw232FuncNameNum;
		CommInfo.dwDecProListNum = pCommInfo->dwDecProListNum;
		memcpy(CommInfo.st232, pCommInfo->st232, DH_MAX_232_NUM*sizeof(DH_RS232_CFG));
		// m_b3ProDev为TRUE: CFG_CMD_PTZ会保存stDecoder,不需要再保存一次
        if (FALSE == m_b3ProDev)
		{
            memcpy(CommInfo.stDecoder, pCommInfo->stDecoder, DH_MAX_DECODER_NUM*sizeof(DH_485_CFG));
		}
		
		//Save information 
		BOOL bSuccess = CLIENT_SetDevConfig(m_LoginID, DH_DEV_COMMCFG, 0,
			&CommInfo, sizeof(DHDEV_COMM_CFG));
		if (bSuccess)
		{
			MessageBox(ConvertString("Save config info successfully!"), ConvertString("Prompt"));
		}
		else
		{
			MessageBox(ConvertString("Save config info failed!"), ConvertString("Prompt"));
		}
		
		if (m_b3ProDev == TRUE)
		{
			int nerror = 0;
			int nrestart = 0;
			int i = nCurChannel;

			char *szOutBuffer = new char[32*1024];
			if (szOutBuffer == NULL)
			{
				return;	
			}
			
			//	for (int i = 0; i < 32; i++)
			{
				//组包

				m_PTZInfo.nChannelID = nCurChannel;
				int nProtocolIndex = pCommInfo->stDecoder[nCurChannel].wProtocol;
				strncpy( m_PTZInfo.szProName ,pCommInfo->DecProName[nProtocolIndex] , MAX_NAME_LEN );
				//m_PTZInfo.nProName = pCommInfo->stDecoder[nCurChannel].wProtocol;
				m_PTZInfo.nDecoderAddress = pCommInfo->stDecoder[nCurChannel].wDecoderAddress;	
				m_PTZInfo.nPTZType = pCommInfo->stDecoder[nCurChannel].bPTZType;	
				m_PTZInfo.nMartixID = pCommInfo->stDecoder[nCurChannel].byMartixID;	
				m_PTZInfo.struComm.byBaudRate = pCommInfo->stDecoder[nCurChannel].struComm.byBaudRate;	
				m_PTZInfo.struComm.byDataBit = pCommInfo->stDecoder[nCurChannel].struComm.byDataBit;	
				m_PTZInfo.struComm.byStopBit = pCommInfo->stDecoder[nCurChannel].struComm.byStopBit;	
				m_PTZInfo.struComm.byParity = pCommInfo->stDecoder[nCurChannel].struComm.byParity;

				BOOL bRet = CLIENT_PacketData(CFG_CMD_PTZ, (char *)&m_PTZInfo, sizeof(CFG_PTZ_INFO), szOutBuffer, 32*1024);
				if (bRet == FALSE)
				{
					MessageBox(ConvertString("Pack data error"), ConvertString("Prompt"));
				}
				else
				{
					BOOL bSuccess = CLIENT_SetNewDevConfig(m_LoginID, CFG_CMD_PTZ, i, szOutBuffer, 32*1024, &nerror, &nrestart, 3000);		
					if (bSuccess)
					{
						if (nrestart == 1)
						{
							MessageBox(ConvertString("Save config info successfully!devide need restart!"), ConvertString("Prompt"));
						}
					}
					else
					{
						MessageBox(ConvertString("SetConfig failed"), ConvertString("Prompt"));	
					}
					
				}

				if (szOutBuffer)
				{
					delete []szOutBuffer;
					szOutBuffer = NULL;
				}	
			}
		}
	}
	else
	{
		MessageBox(ConvertString("Login first!"), ConvertString("Prompt"));
	}
}

//Get record configuration information 
void CClientDemo5Dlg::GetRecordConfigInfo()
{
	if(0 != m_LoginID)
	{
		DWORD dwRetLen = 0;
		int nWaitTime = 3000;
		//Channel amount 
		int nChannelCount = m_nChannel > CHANNEL_NUM_LIMIT ? CHANNEL_NUM_LIMIT : m_nChannel;
		//Record property 
		DHDEV_RECORD_CFG *pRecordInfo = new DHDEV_RECORD_CFG[nChannelCount];

		if(m_b3ProDev == FALSE)
		{
			BOOL bSuccess = CLIENT_GetDevConfig(m_LoginID, DH_DEV_RECORDCFG, -1/*all channel*/,
				pRecordInfo, nChannelCount*sizeof(DHDEV_RECORD_CFG), &dwRetLen, nWaitTime);

			if (bSuccess && dwRetLen == nChannelCount * sizeof(DHDEV_RECORD_CFG))
			{
				//Initialize dialogue box 
				m_recordDlg.InitDlgInfo(pRecordInfo,nChannelCount, m_nDevProtoVer, m_b3ProDev);
			}
		}
		else
		{
			m_recordDlg.InitDlgInfo(pRecordInfo,nChannelCount, m_nDevProtoVer, m_b3ProDev);
		}
		delete[] pRecordInfo;
	}
	else
	{
		MessageBox(ConvertString("Login first!"), ConvertString("Prompt"));
	}
}

void CClientDemo5Dlg::GetOneRecordConfigInfo(DHDEV_RECORD_CFG *pInfo, int nCurChannel)
{
	if(0 != m_LoginID || pInfo != NULL)
	{
		int nerror = 0;
		int i = nCurChannel;

		char *szOutBuffer = new char[32*1024];
		if (szOutBuffer == NULL)
		{
			return;	
		}
		memset(szOutBuffer, 0, 32*1024);
		//	for (int i = 0; i < nChannelCount; i++)
		{
			int nRetLen = 0;
			BOOL bSuccess = CLIENT_GetNewDevConfig(m_LoginID, CFG_CMD_RECORD, i, szOutBuffer, 32 * 1024, &nerror, 3000);		
			if (bSuccess)
			{
				BOOL bRet = CLIENT_ParseData(CFG_CMD_RECORD, szOutBuffer, (char *)&m_RecordInfo, sizeof(CFG_RECORD_INFO), &nRetLen);
				if (bRet == FALSE)
				{
					MessageBox(ConvertString("Parse data error"), ConvertString("Prompt"));
				}
				else
				{
					memset(pInfo, 0, sizeof(DHDEV_RECORD_CFG));
					//解析
					
					pInfo->byPreRecordLen = m_RecordInfo.nPreRecTime;
					pInfo->byRedundancyEn = m_RecordInfo.bRedundancyEn;	
					pInfo->byRecordType = m_RecordInfo.nStreamType;	
					
					for (int w = 0; w < DH_N_WEEKS; w++)
					{
						for (int t = 0; t < DH_N_TSECT; t++)
						{
							memcpy(&pInfo->stSect[w][t], &m_RecordInfo.stuTimeSection[w][t], sizeof(CFG_TIME_SECTION));
						}
					}		
				}
			}
			else
			{
				MessageBox(ConvertString("GetConfig failed(record)!"), ConvertString("Prompt"));	
			}
		}
		if (szOutBuffer)
		{
			delete []szOutBuffer;
			szOutBuffer = NULL;
		}	
	}
	else
	{
		MessageBox(ConvertString("Login first!"), ConvertString("Prompt"));
	}
}


//Set record configuration information 
void CClientDemo5Dlg::SetRecordConfigInfo(DHDEV_RECORD_CFG *pRecordInfo, BYTE nLength)
{
	if(0 != m_LoginID && pRecordInfo != NULL)
	{
		//Save information 
		BOOL bSuccess = FALSE;
		if(m_b3ProDev == FALSE)
		{
			bSuccess = CLIENT_SetDevConfig(m_LoginID, DH_DEV_RECORDCFG, -1,
				pRecordInfo, nLength*sizeof(DHDEV_RECORD_CFG));
			
			if (bSuccess)
			{
				MessageBox(ConvertString("Save config info successfully!"), ConvertString("Prompt"));
			}
			else
			{
				MessageBox(ConvertString("Save config info failed!"), ConvertString("Prompt"));
			}
		}
	}
	else
	{
		MessageBox(ConvertString("Login first!"), ConvertString("Prompt"));
	}
}

void CClientDemo5Dlg::SetOneRecordConfigInfo(DHDEV_RECORD_CFG *pInfo, int nCurChannel)
{
	if(0 != m_LoginID && pInfo != NULL)
	{
		//Save information 
		
		char *szInBuffer = new char[32*1024];
		if (szInBuffer == NULL)
		{
			return;	
		}
		memset(szInBuffer, 0, 32*1024);
		
		int nerror = 0;
		int nrestart = 0;
		int i = nCurChannel;
		//	for (int i = 0; i < nLength; i++)
		{	
			memset(szInBuffer, 0, 32*1024);
			
			DWORD deTime = GetTickCount();
			//组包
			m_RecordInfo.nChannelID = nCurChannel;
			m_RecordInfo.nPreRecTime = pInfo->byPreRecordLen;
			m_RecordInfo.bRedundancyEn = pInfo->byRedundancyEn;	
			m_RecordInfo.nStreamType = pInfo->byRecordType;	
			
			for (int w = 0; w < DH_N_WEEKS; w++)
			{
				for (int t = 0; t < DH_N_TSECT; t++)
				{
					memcpy(&m_RecordInfo.stuTimeSection[w][t], &pInfo->stSect[w][t], sizeof(CFG_TIME_SECTION));
				}
			}
			BOOL bRet = CLIENT_PacketData(CFG_CMD_RECORD, (char *)&m_RecordInfo, sizeof(CFG_RECORD_INFO), szInBuffer, 32*1024);
			if (bRet == FALSE)
			{
				MessageBox(ConvertString("Pack data error"), ConvertString("Prompt"));
			}
			else
			{
				BOOL bSuccess = CLIENT_SetNewDevConfig(m_LoginID, CFG_CMD_RECORD, i, szInBuffer, 32*1024, &nerror, &nrestart, 3000);		
				if (bSuccess)
				{
					if (nrestart == 1)
					{
						MessageBox(ConvertString("Save config info successfully!devide need restart!"), ConvertString("Prompt"));
					}
				}
				else
				{
					MessageBox(ConvertString("SetConfig failed"), ConvertString("Prompt"));	
				}	
			}	
		}
		
		if (szInBuffer)
		{
			delete []szInBuffer;
			szInBuffer = NULL;
		}
	}
	else
	{
		MessageBox(ConvertString("Login first!"), ConvertString("Prompt"));
	}
	
}
//Get network configuration information 
void CClientDemo5Dlg::GetNetWorkConfigInfo()
{
	if(0 != m_LoginID)
	{
		DWORD dwRetLen = 0;
		int nWaitTime = 1000;
		DH_QUICK_QUERY_CFG_EN stQuickQueryEn = {0};
		BOOL bSuccess = CLIENT_QuerySystemInfo(m_LoginID, ABILITY_QUICK_QUERY_CFG, (char *)&stQuickQueryEn, sizeof(DH_QUICK_QUERY_CFG_EN), (int *)&dwRetLen);
		if (bSuccess && dwRetLen == sizeof(DH_QUICK_QUERY_CFG_EN)) 
		{
			if (stQuickQueryEn.IsQuickQueryEnable == 1) 
			{
				nWaitTime = 60000;
			}
		}
		DHDEV_SYSTEM_ATTR_CFG sysConfigInfo = {0};
		bSuccess = CLIENT_GetDevConfig(m_LoginID, DH_DEV_DEVICECFG, 0,
			&sysConfigInfo, sizeof(DHDEV_SYSTEM_ATTR_CFG), &dwRetLen, nWaitTime);
		if (bSuccess && dwRetLen == sizeof(DHDEV_SYSTEM_ATTR_CFG))
		{
			//Network port amount	limit the amount to 9
			BYTE nNetIOCount = sysConfigInfo.byNetIONum  > MAX_ETHERNET_LIMIT ? MAX_ETHERNET_LIMIT :sysConfigInfo.byNetIONum;
			if (2 <= sysConfigInfo.byNetIONum)
			{
				m_networkDlg.m_bDBEthernet = TRUE;
			}
			//Network configuration
			DHDEV_NET_CFG_EX NetIOInfo = {0};
			bSuccess = CLIENT_GetDevConfig(m_LoginID, DH_DEV_NETCFG_EX, 0,
				&NetIOInfo, sizeof(DHDEV_NET_CFG_EX), &dwRetLen);
			if (bSuccess && dwRetLen == sizeof(DHDEV_NET_CFG_EX))
			{
                CFG_EMAIL_INFO stuMailInfo = {0};
                bSuccess = GetMailConfig(stuMailInfo);
				if (bSuccess)
				{
					//Initialize dialogue box 
					m_networkDlg.InitDlgInfo(&NetIOInfo, nNetIOCount, &stuMailInfo);
				}
			}
		}

		//////////////////////////////////////////////////////////////////////////
		// if has specail multicast configuration
		
		//判断是否为三代协议设备
		BOOL bIsSupported = FALSE;
		int len = 0;
		DH_DEV_ENABLE_INFO stDevEn = {0};
		BOOL bRet = CLIENT_QuerySystemInfo(m_LoginID, ABILITY_DEVALL_INFO, (char*)&stDevEn, sizeof(DH_DEV_ENABLE_INFO), &len);
		if (bRet && len == sizeof(DH_DEV_ENABLE_INFO))
		{
			if (stDevEn.IsFucEnable[EN_JSON_CONFIG] != 0)
			{
				bIsSupported = TRUE;
			}
			else
			{
				bIsSupported = FALSE;
			}
		}
		else
		{
			bIsSupported = FALSE;
		}

		if (bIsSupported)
		{
			char* pszJsonBuf = new char[32 * 1024];
			if (!pszJsonBuf)
			{
				return;
			}
			memset(pszJsonBuf, 0, 32 * 1024);
			
			CFG_MULTICASTS_INFO_OUT* pstuOut = new CFG_MULTICASTS_INFO_OUT;
			if (!pstuOut)
			{
				delete pszJsonBuf;
				pszJsonBuf = NULL;
				return;
			}
			memset(pstuOut, 0, sizeof(*pstuOut));

			int nLen = 0;
			bSuccess = ::CLIENT_GetNewDevConfig(m_LoginID,
												CFG_CMD_MULTICAST,
												0,
												pszJsonBuf,
												32 * 1024,
												&nLen);
			if (bSuccess)
			{					
				bSuccess = ::CLIENT_ParseData(CFG_CMD_MULTICAST,
											pszJsonBuf,
											pstuOut,
											sizeof(*pstuOut),
											NULL);
				if (bSuccess)
				{
					// initialization of multicast
					m_networkDlg.InitDlgInfo(pstuOut, m_nChannel);
				}
			}

			// step out
			if (pstuOut)
			{
				delete []pstuOut;
				pstuOut = NULL;
			}

			if (pszJsonBuf)
			{
				delete []pszJsonBuf;
				pszJsonBuf = NULL;
			}
		}
	}
	else
	{
		MessageBox(ConvertString("Login first!"), ConvertString("Prompt"));
	}
}

//Save network configuration information 
void CClientDemo5Dlg::SetNetWorkConfigInfo(DHDEV_NET_CFG_EX *pNetIOInfo, CFG_EMAIL_INFO& stuMailInfo, CFG_MULTICASTS_INFO_IN* pMultiIn)
{
	if(0 != m_LoginID && pNetIOInfo != NULL)
	{
		//Save information
		BOOL bSuccess = SetMailConfig(stuMailInfo);
		if (bSuccess)
		{
			pNetIOInfo->struMail.wReserved = 1;// 表示不保存邮件配置，上面已经保存了。
			bSuccess = CLIENT_SetDevConfig(m_LoginID, DH_DEV_NETCFG_EX, 0,
											pNetIOInfo, sizeof(DHDEV_NET_CFG_EX), SDK_DEMO_WAITTIME);

			if (!bSuccess)
			{
				MessageBox(ConvertString("Save net config info failed!"), ConvertString("Prompt"));
			}
			if (pMultiIn)
			{
				char szJsonBuf[32 * 1024] = {0};
				bSuccess = ::CLIENT_PacketData(CFG_CMD_MULTICAST,
					pMultiIn,
					sizeof(*pMultiIn),
					szJsonBuf,
					32 * 1024);

				if (bSuccess)
				{
					int nLen = 0;
					int nRes = 0;
					bSuccess = ::CLIENT_SetNewDevConfig(m_LoginID,
														CFG_CMD_MULTICAST,
														0,
														szJsonBuf,
														32 * 1024,
														&nLen,
														&nRes,
														SDK_DEMO_WAITTIME);
				}
			}

			if (bSuccess)
			{
				MessageBox(ConvertString("Save multicast config successfully!"), ConvertString("Prompt"));
			}
			else
			{
				MessageBox(ConvertString("Save multicast config info failed!"), ConvertString("Prompt"));
			}
		}
		else
		{
			//MessageBox(ConvertString("Save mail config info failed!"), ConvertString("Prompt"));
		}
	}
	else
	{
		MessageBox(ConvertString("Login first!"), ConvertString("Prompt"));
	}
}

//Get alarm property configuration information 
void CClientDemo5Dlg::GetAlarmConfigInfo()
{	
	if(0 != m_LoginID)	
	{
		DWORD dwRetLen = 0;
		int nWaitTime = 1000;
		DH_QUICK_QUERY_CFG_EN stQuickQueryEn = {0};
		BOOL bSuccess = CLIENT_QuerySystemInfo(m_LoginID, ABILITY_QUICK_QUERY_CFG, (char *)&stQuickQueryEn, sizeof(DH_QUICK_QUERY_CFG_EN), (int *)&dwRetLen);
		if (bSuccess && dwRetLen == sizeof(DH_QUICK_QUERY_CFG_EN)) 
		{
			if (stQuickQueryEn.IsQuickQueryEnable == 1) 
			{
				nWaitTime = 60000;
			}
		}
		DHDEV_SYSTEM_ATTR_CFG sysConfigInfo = {0};
	
	    bSuccess = CLIENT_GetDevConfig(m_LoginID, DH_DEV_DEVICECFG, 0,
			&sysConfigInfo, sizeof(DHDEV_SYSTEM_ATTR_CFG), &dwRetLen, nWaitTime);
		if (bSuccess && dwRetLen == sizeof(DHDEV_SYSTEM_ATTR_CFG))
		{
			//Alarm input channel amount 
			BYTE nAlarmInCount = sysConfigInfo.byAlarmInNum>32?32:sysConfigInfo.byAlarmInNum;
			//Alarm output channel amount 
			BYTE nAlarmOutCount = sysConfigInfo.byAlarmOutNum>32?32:sysConfigInfo.byAlarmOutNum;
			//Channel amount 
			int nChannelCount = m_nChannel > CHANNEL_NUM_LIMIT ? CHANNEL_NUM_LIMIT : m_nChannel;


			DHDEV_ALARM_SCHEDULE_EX *pAlarmInfo = new DHDEV_ALARM_SCHEDULE_EX;
			if (pAlarmInfo == NULL)
			{
				return;
			}

			DHDEV_ALARM_SCHEDULE_EX &AlarmInfo = *pAlarmInfo;
			memset(&AlarmInfo, 0, sizeof(DHDEV_ALARM_SCHEDULE_EX));
			
			// 获取设备的报警名称
			InitAlarmName(&AlarmInfo);
			m_alarmDlg.InitDlgInfo(&AlarmInfo,nAlarmInCount,nAlarmOutCount,nChannelCount);	

			if (pAlarmInfo != NULL)
			{
				delete pAlarmInfo;
				pAlarmInfo = NULL;
			}
		}

		//////////////////////////////////////////////////////////////////////////
		// get motiondetect if json is supported
	}
	else
	{
		MessageBox(ConvertString("Login first!"), ConvertString("Prompt"));
	}
	
}

void CClientDemo5Dlg::GetAlarmInConfigInfo(CFG_ALARMIN_INFO *pAlarmIn, int nCurChannel)
{
	if(pAlarmIn == NULL)
	{
		return;
	}

	
	char *szOutBuffer = new char[32*1024];
	if (szOutBuffer == NULL)
	{
		return;	
	}
	memset(szOutBuffer, 0, 32*1024);

	if (nCurChannel < 0 || nCurChannel >= 32)
	{
		return;
	}
	
	int nalarmerror = 0;
//	int i = nCurChannel;
	//	for (i = 0; i < nAlarmInCount; i++)
	{

		//alarm
		BOOL bSuccess = CLIENT_GetNewDevConfig(m_LoginID, CFG_CMD_ALARMINPUT, nCurChannel, szOutBuffer, 32*1024, &nalarmerror, 3000);		
		if (bSuccess)
		{
			int nRetLen = 0;
			BOOL bRet = CLIENT_ParseData(CFG_CMD_ALARMINPUT, szOutBuffer, (char *)m_AlarmInfo, sizeof(CFG_ALARMIN_INFO), &nRetLen);
			int ncqs = sizeof(m_AlarmInfo);
			if (bRet == FALSE)
			{
				MessageBox(ConvertString("Parse data error"), ConvertString("Prompt"));
			}
			else
			{
				memcpy(pAlarmIn, m_AlarmInfo, sizeof(CFG_ALARMIN_INFO));
			}	
		}
		else
		{
			MessageBox(ConvertString("GetConfig failed(Alarm)!"), ConvertString("Prompt"));	
		}
	}	
	
	if (szOutBuffer)
	{
		delete []szOutBuffer;
		szOutBuffer = NULL;
	}
}


void CClientDemo5Dlg::GetMotionAlarmConfigInfo(CFG_MOTION_INFO *pMotionInfo, int nCurChannel)
{
	
	if(pMotionInfo == NULL)
	{
		return;
	}

	
	char *szOutBuffer = new char[32*1024];
	if (szOutBuffer == NULL)
	{
		return;	
	}
	if (nCurChannel < 0 || nCurChannel >= CHANNEL_NUM_LIMIT)
	{
		return;
	}
	
	int nalarmerror = 0;
	int i = nCurChannel;
	//	for (i = 0; i < nAlarmInCount; i++)
	{
		//motionalarm
		BOOL bSuccess = CLIENT_GetNewDevConfig(m_LoginID, CFG_CMD_MOTIONDETECT, i, szOutBuffer, 32*1024, &nalarmerror, 10000);		
		if (bSuccess)
		{
			int nRetLen = 0;

			BOOL bRet = CLIENT_ParseData(CFG_CMD_MOTIONDETECT, szOutBuffer, m_MotionInfo, sizeof(CFG_MOTION_INFO), &nRetLen);
			if (bRet == FALSE)
			{
				MessageBox(ConvertString("Parse data error"), ConvertString("Prompt"));
			}
			else
			{
				memcpy(pMotionInfo, m_MotionInfo, sizeof(CFG_MOTION_INFO));
			}
		}
		else
		{
			MessageBox(ConvertString("GetConfig failed(MotionAlarm)!"), ConvertString("Prompt"));	
		}
	}

	if (szOutBuffer)
	{
		delete []szOutBuffer;
		szOutBuffer = NULL;
	}
	
}

void CClientDemo5Dlg::GetBlindAlarmConfigInfo(CFG_SHELTER_INFO *pShelterInfo, int nCurChannel)
{
	if(pShelterInfo == NULL)
	{
		return;
	}
	
	char *szOutBuffer = new char[32*1024];
	if (szOutBuffer == NULL)
	{
		return;	
	}
	if (nCurChannel < 0 || nCurChannel >= CHANNEL_NUM_LIMIT)
	{
		return;
	}

	int nalarmerror = 0;
	//	for (i = 0; i < nChannelCount; i++)
	{
		//blindalarm
		BOOL bSuccess = CLIENT_GetNewDevConfig(m_LoginID, CFG_CMD_VIDEOBLIND, nCurChannel, szOutBuffer, 32*1024, &nalarmerror, 3000);		
		if (bSuccess)
		{
			//解析
			int nRetLen = 0;
			BOOL bRet = CLIENT_ParseData(CFG_CMD_VIDEOBLIND, szOutBuffer, (char *)m_BlindInfo, sizeof(CFG_SHELTER_INFO), &nRetLen);
			if (bRet == FALSE)
			{
				MessageBox(ConvertString("Parse data error"), ConvertString("Prompt"));
			}
			else
			{
				//p3
				memcpy(pShelterInfo, m_BlindInfo, sizeof(CFG_SHELTER_INFO));
						
			}				
		}
		else
		{
			MessageBox(ConvertString("GetConfig failed(BlindAlarm)!"), ConvertString("Prompt"));	
		}
					
	}
							
	if (szOutBuffer)
	{
		delete []szOutBuffer;
		szOutBuffer = NULL;
	}
				
}

void CClientDemo5Dlg::GetLossAlarmConfigInfo(CFG_VIDEOLOST_INFO *pVideoLostInf, int nCurChannel)
{

	if(pVideoLostInf == NULL)
	{
		return;
	}

	
	char *szOutBuffer = new char[32*1024];
	if (szOutBuffer == NULL)
	{
		return;	
	}
	if (nCurChannel < 0 || nCurChannel >= CHANNEL_NUM_LIMIT)
	{
		return;
	}
	
	int nalarmerror = 0;
//	int i = nCurChannel;
	{
		//lossalarm
		BOOL bSuccess = CLIENT_GetNewDevConfig(m_LoginID, CFG_CMD_VIDEOLOST, nCurChannel, szOutBuffer, 32*1024, &nalarmerror, 3000);		
		if (bSuccess)
		{	
			int nRetLen = 0;
			//解析
			BOOL bRet = CLIENT_ParseData(CFG_CMD_VIDEOLOST, szOutBuffer, (char *)m_VideoLostInfo, sizeof(CFG_VIDEOLOST_INFO), &nRetLen);
			if (bRet == FALSE)
			{
				MessageBox(ConvertString("Parse data error"), ConvertString("Prompt"));
			}
			else
			{
				memcpy(pVideoLostInf, m_VideoLostInfo, sizeof(CFG_VIDEOLOST_INFO));
			}
		}
		else
		{
			MessageBox(ConvertString("GetConfig failed!"), ConvertString("Prompt"));	
		}
				}
	if (szOutBuffer)
	{
		delete []szOutBuffer;
		szOutBuffer = NULL;
	}
	
}

void CClientDemo5Dlg::SetAlarmConfigInfo(DHDEV_ALARM_SCHEDULE_EX *pAlarmInfo)
{
	if(0 != m_LoginID && pAlarmInfo != NULL)
	{
		DWORD dwRetLen = 0;
		DHDEV_SYSTEM_ATTR_CFG sysConfigInfo = {0};
		BOOL bAllSuccess = TRUE;	
		BOOL bSuccess = CLIENT_GetDevConfig(m_LoginID, DH_DEV_DEVICECFG, 0,
			&sysConfigInfo, sizeof(DHDEV_SYSTEM_ATTR_CFG), &dwRetLen);
		if (bSuccess && dwRetLen == sizeof(DHDEV_SYSTEM_ATTR_CFG))
		{			
			if(m_b3ProDev == FALSE)
			{
				if (strlen(pAlarmInfo->szAlarmName) > 0)
				{
					CLIENT_SetDevConfig(m_LoginID, DH_DEV_LOCALALARM_NAME_CFG, 0
						, pAlarmInfo->szAlarmName, strlen(pAlarmInfo->szAlarmName));
				}
				
				if (bSuccess)
				{
					MessageBox(ConvertString("Save config info successfully!"), ConvertString("Prompt"));
				}
				else
				{
					MessageBox(ConvertString("Save config info failed!"), ConvertString("Prompt"));
				}
			}	
		}
	}
	else
	{
		MessageBox(ConvertString("Login first!"), ConvertString("Prompt"));
	}
}


void CClientDemo5Dlg::SetAlarmInConfigInfo(CFG_ALARMIN_INFO *pAlarmIn, int nCurChannel)
{

	char *szOutBuffer = new char[32*1024];
	if (szOutBuffer == NULL)
	{
		return;	
	}
				
	int nalarmerror = 0;	
	int nrestart = 0;
				
	int i = nCurChannel;
				
	//for (i = 0; i < nAlarmInCount; i++)
	if(0 != m_LoginID && pAlarmIn != NULL)
	{
		//alarm		
		memset(szOutBuffer, 0, 32*1024);
		BOOL bRet = CLIENT_PacketData(CFG_CMD_ALARMINPUT, pAlarmIn, sizeof(CFG_ALARMIN_INFO), szOutBuffer, 32*1024);
		if (bRet == FALSE)
		{
			MessageBox(ConvertString("Pack data error"), ConvertString("Prompt"));
		}
		else
		{	
			BOOL bSuccess = CLIENT_SetNewDevConfig(m_LoginID, CFG_CMD_ALARMINPUT, i, (char *)szOutBuffer, 32*1024, &nalarmerror, &nrestart, 3000);		
			if (bSuccess)
			{
				if (nrestart == 1)
				{
					MessageBox(ConvertString("Save config info successfully!devide need restart!"), ConvertString("Prompt"));
				}	
			}
			else
			{
				MessageBox(ConvertString("SetConfig failed(alarm)!"), ConvertString("Prompt"));	
			}	
		}	
	}
	else
	{
		MessageBox(ConvertString("Login first!"), ConvertString("Prompt"));
	}

	if (szOutBuffer)
	{
		delete []szOutBuffer;
		szOutBuffer = NULL;
	}
}

void CClientDemo5Dlg::SetMotionAlarmConfigInfo(int nCurChannel, CFG_MOTION_INFO* pMotionInfo)
{
	char *szOutBuffer = new char[32*1024];
	if (szOutBuffer == NULL)
	{
		return;	
	}
				
	int nalarmerror = 0;	
	int nrestart = 0;
				
	if(0 != m_LoginID && pMotionInfo != NULL)
	{
		//motionalarm
		memset(szOutBuffer, 0, 32*1024);
		BOOL bRet;
		if (pMotionInfo)
		{
			memset(szOutBuffer, 0, 32 * 1024);
			bRet = CLIENT_PacketData(CFG_CMD_MOTIONDETECT, 
									pMotionInfo, 
									sizeof(CFG_MOTION_INFO), 
									szOutBuffer,
									32 * 1024);
			if (bRet)
			{
				bRet = CLIENT_SetNewDevConfig(m_LoginID,
											CFG_CMD_MOTIONDETECT,
											nCurChannel,
											szOutBuffer,
											32 * 1024,
											&nalarmerror,
											&nrestart, 
											4000);
				if(!bRet)
				{
					MessageBox(ConvertString("SetConfig failed(motionarea)!"), ConvertString("Prompt"));
				}
			}
		}
	}
	else
	{
		MessageBox(ConvertString("Login first!"), ConvertString("Prompt"));
	}

	if (szOutBuffer)
	{
		delete []szOutBuffer;
		szOutBuffer = NULL;
	}
}


void CClientDemo5Dlg::SetBlindAlarmConfigInfo(CFG_SHELTER_INFO *pShelterInfo, int nCurChannel)
{
	char *szOutBuffer = new char[32*1024];
	if (szOutBuffer == NULL)
	{
		return;	
	}
				
	int nalarmerror = 0;	
	int nrestart = 0;
				
	int i = nCurChannel;
				
	//for (i = 0; i < nAlarmInCount; i++)
	if(0 != m_LoginID && pShelterInfo != NULL)
	{
		//blindalarm
		
		memset(szOutBuffer, 0, 32*1024);
	
		BOOL bRet = CLIENT_PacketData(CFG_CMD_VIDEOBLIND, pShelterInfo, sizeof(CFG_SHELTER_INFO), szOutBuffer, 32*1024);
		if (bRet == FALSE)
		{
			MessageBox(ConvertString("Pack data error"), ConvertString("Prompt"));
		}
		else
		{
			BOOL bSuccess = CLIENT_SetNewDevConfig(m_LoginID, CFG_CMD_VIDEOBLIND, i, (char *)szOutBuffer, 32*1024, &nalarmerror, &nrestart, 3000);		
			if (bSuccess)
			{
				if (nrestart == 1)
				{
					MessageBox(ConvertString("Save config info successfully!devide need restart!"), ConvertString("Prompt"));
				}
				
			}
			else
			{
				MessageBox(ConvertString("SetConfig failed(blindalarm)!"), ConvertString("Prompt"));	
			}	
			
		}
	}
	else
	{
		MessageBox(ConvertString("Login first!"), ConvertString("Prompt"));
	}
	
	if (szOutBuffer)
	{
		delete []szOutBuffer;
		szOutBuffer = NULL;
	}
	
}

void CClientDemo5Dlg::SetLossAlarmConfigInfo(CFG_VIDEOLOST_INFO *pVideoLostInf, int nCurChannel)
{
	char *szOutBuffer = new char[32*1024];
	if (szOutBuffer == NULL)
	{
		return;	
	}
				
	int nalarmerror = 0;	
	int nrestart = 0;
				
	int i = nCurChannel;

	if(0 != m_LoginID && pVideoLostInf != NULL)
	{
		//lossalarm
		memset(szOutBuffer, 0, 32*1024);
		
		BOOL bRet = CLIENT_PacketData(CFG_CMD_VIDEOLOST, pVideoLostInf, sizeof(CFG_VIDEOLOST_INFO), szOutBuffer, 32*1024);
		if (bRet == FALSE)
		{
			MessageBox(ConvertString("Pack data error"), ConvertString("Prompt"));
		}
		else
		{
			BOOL bSuccess = CLIENT_SetNewDevConfig(m_LoginID, CFG_CMD_VIDEOLOST, i, (char *)szOutBuffer, 32*1024, &nalarmerror, &nrestart, 3000);		
			if (bSuccess)
			{
				if (nrestart == 1)
				{
					MessageBox(ConvertString("Save config info successfully!devide need restart!"), ConvertString("Prompt"));
				}
				
			}
			else
			{
				MessageBox(ConvertString("SetConfig failed(lossalarm)!"), ConvertString("Prompt"));	
			}	
			
		}	
	}
	else
	{
		MessageBox(ConvertString("Login first!"), ConvertString("Prompt"));
	}
	
	if (szOutBuffer)
	{
		delete []szOutBuffer;
		szOutBuffer = NULL;
	}	
}


void CClientDemo5Dlg::OnButtonRevert() 
{
	// TODO: Add your control notification handler code here
	if(0 != m_LoginID)
	{
		int nIndex = m_ctlRevertType.GetCurSel();
		DWORD dwFlag = m_ctlRevertType.GetItemData(nIndex);
		BOOL bSuccess = CLIENT_ControlDevice(m_LoginID,DH_CTRL_RESTOREDEFAULT,&dwFlag,30000);
		if(bSuccess)
		{
			MessageBox(ConvertString("Set successfully!"), ConvertString("Prompt"));
			//Device property 
            m_serverDlg.CleanAll();
			GetDeviceConfigInfo();
			//Video channel property 
			//First clear config info
	        m_channelDlg.CleanAll();
			GetChannelConfigInfo();
			//COM property 
            m_commDlg.CleanAll();
			GetCommConfigInfo();
			//Record configuration 
            m_recordDlg.CleanAll(false);
			GetRecordConfigInfo();
			//Network configuration 
            m_networkDlg.CleanAll();
			GetNetWorkConfigInfo();
			//Alarm configuration 
            m_alarmDlg.CleanAll();
			GetAlarmConfigInfo();
		}
		else
		{
			MessageBox(ConvertString("Set failed! It is possible that the device doesn't support the function!"), ConvertString("Prompt"));
		}
	}
	else
	{
		MessageBox(ConvertString("Login first!"), ConvertString("Prompt"));
	}
}

void CClientDemo5Dlg::InitCombo()
{
	int nIndex = m_ctlRevertType.AddString(ConvertString("Common Setting"));
	m_ctlRevertType.SetItemData(nIndex,DH_RESTORE_COMMON);
	nIndex = m_ctlRevertType.AddString(ConvertString("Coding Setting"));
	m_ctlRevertType.SetItemData(nIndex,DH_RESTORE_CODING);
	nIndex = m_ctlRevertType.AddString(ConvertString("Record Setting"));
	m_ctlRevertType.SetItemData(nIndex,DH_RESTORE_VIDEO);
	nIndex = m_ctlRevertType.AddString(ConvertString("COM Setting"));
	m_ctlRevertType.SetItemData(nIndex,DH_RESTORE_COMM);
	nIndex = m_ctlRevertType.AddString(ConvertString("Network Setting"));
	m_ctlRevertType.SetItemData(nIndex,DH_RESTORE_NETWORK);
	nIndex = m_ctlRevertType.AddString(ConvertString("Alarm Setting"));
	m_ctlRevertType.SetItemData(nIndex,DH_RESTORE_ALARM);
	nIndex = m_ctlRevertType.AddString(ConvertString("Video Detecting"));
	m_ctlRevertType.SetItemData(nIndex,DH_RESTORE_VIDEODETECT);
	nIndex = m_ctlRevertType.AddString(ConvertString("PTZ Control"));
	m_ctlRevertType.SetItemData(nIndex,DH_RESTORE_PTZ);
	nIndex = m_ctlRevertType.AddString(ConvertString("Ouput Mode"));
	m_ctlRevertType.SetItemData(nIndex,DH_RESTORE_OUTPUTMODE);
	nIndex = m_ctlRevertType.AddString(ConvertString("Channel Name"));
	m_ctlRevertType.SetItemData(nIndex,DH_RESTORE_CHANNELNAME);
	nIndex = m_ctlRevertType.AddString(ConvertString("Camera Attribute"));
	m_ctlRevertType.SetItemData(nIndex,DH_RESTORE_VIDEOINOPTIONS);
	nIndex = m_ctlRevertType.AddString(ConvertString("CPS"));
	m_ctlRevertType.SetItemData(nIndex,DH_RESTORE_CPS);
	nIndex = m_ctlRevertType.AddString(ConvertString("Video analysis"));
	m_ctlRevertType.SetItemData(nIndex,DH_RESTORE_INTELLIGENT);
	nIndex = m_ctlRevertType.AddString(ConvertString("Remote Device configuration"));
	m_ctlRevertType.SetItemData(nIndex,DH_RESTORE_REMOTEDEVICE);
	nIndex = m_ctlRevertType.AddString(ConvertString("Restore all config"));
	m_ctlRevertType.SetItemData(nIndex,DH_RESTORE_ALL);
	nIndex = m_ctlRevertType.AddString(ConvertString("Common Setting|Video Setting"));
	m_ctlRevertType.SetItemData(nIndex,DH_RESTORE_COMMON | DH_RESTORE_VIDEO);
	nIndex = m_ctlRevertType.AddString(ConvertString("COM Setting|Alarm Setting"));
	m_ctlRevertType.SetItemData(nIndex,DH_RESTORE_COMM | DH_RESTORE_ALARM);
	nIndex = m_ctlRevertType.AddString(ConvertString("PTZ Control|Channel Name"));
	m_ctlRevertType.SetItemData(nIndex,DH_RESTORE_PTZ | DH_RESTORE_CHANNELNAME);
	m_ctlRevertType.SetCurSel(0);
}

//Get multiple privacy mask zones information 
void CClientDemo5Dlg::GetCoverConfigInfo()
{
	if(0 != m_LoginID)
	{
		//limit the amount to 256
		int nChannelCount = m_nChannel > CHANNEL_NUM_LIMIT ? CHANNEL_NUM_LIMIT : m_nChannel;
		m_coverDlg.InitDlgInfo(nChannelCount);	
	}
	else
	{
		MessageBox(ConvertString("Login first!"), ConvertString("Prompt"));
	}
}

void CClientDemo5Dlg::GetOneCoverConfigInfo(DHDEV_VIDEOCOVER_CFG *pInfo, int nCurChannel)
{
	if(0 != m_LoginID || pInfo != NULL)
	{	
		char *szOutBuffer = new char[32*1024];
		if (szOutBuffer == NULL)
		{	
			return;	
		}
		int nerror = 0;
		int i = nCurChannel;
		//	for (int i = 0; i < nChannelCount; i++)
		{
			BOOL bSuccess = CLIENT_GetNewDevConfig(m_LoginID, CFG_CMD_ENCODE, i, szOutBuffer, 32*1024, &nerror, 3000);		
			if (bSuccess)
			{
				memset(pInfo, 0, sizeof(DHDEV_VIDEOCOVER_CFG));
				CFG_ENCODE_INFO stuEncodeInfo = {0};
				//解析
				int nRetLen = 0;
				BOOL bRet = CLIENT_ParseData(CFG_CMD_ENCODE, szOutBuffer, (char *)&stuEncodeInfo, sizeof(CFG_ENCODE_INFO), &nRetLen);
				if (bRet == FALSE)
				{
					MessageBox(ConvertString("Parser data error"), ConvertString("Prompt"));
				}
				else
				{
					memcpy(&m_VideoCoveInfo, &stuEncodeInfo.stuVideoCover, sizeof(CFG_VIDEO_COVER));
					//char Name[64] = {0} ;
					//Change_Utf8_Assic((unsigned char *)stuEncodeInfo.szChnName, Name);
					strncpy(pInfo->szChannelName, stuEncodeInfo.szChnName,DH_CHAN_NAME_LEN);	
					
					pInfo->bTotalBlocks = m_VideoCoveInfo.nTotalBlocks;	
					pInfo->bCoverCount = m_VideoCoveInfo.nCurBlocks;

					if(stuEncodeInfo.dwCoverEnableMask == 0)
					{
						pInfo->bCoverCount = 0;
					}

					for (int k = 0; k < pInfo->bTotalBlocks; k++)
					{
						pInfo->CoverBlock[k].bBlockType = m_VideoCoveInfo.stuCoverBlock[k].nBlockType;
						pInfo->CoverBlock[k].bPriview = m_VideoCoveInfo.stuCoverBlock[k].nPreviewBlend;	
						pInfo->CoverBlock[k].bEncode = m_VideoCoveInfo.stuCoverBlock[k].nEncodeBlend;
						
						pInfo->CoverBlock[k].nColor |= m_VideoCoveInfo.stuCoverBlock[k].stuColor.nRed;	
						pInfo->CoverBlock[k].nColor <<= 8;
						pInfo->CoverBlock[k].nColor |= m_VideoCoveInfo.stuCoverBlock[k].stuColor.nGreen;	
						pInfo->CoverBlock[k].nColor <<= 8;
						pInfo->CoverBlock[k].nColor |= m_VideoCoveInfo.stuCoverBlock[k].stuColor.nBlue;	
						pInfo->CoverBlock[k].nColor <<= 8;
						pInfo->CoverBlock[k].nColor |= m_VideoCoveInfo.stuCoverBlock[k].stuColor.nAlpha;	

						pInfo->CoverBlock[k].rcBlock.left = m_VideoCoveInfo.stuCoverBlock[k].stuRect.nLeft;
						pInfo->CoverBlock[k].rcBlock.top = m_VideoCoveInfo.stuCoverBlock[k].stuRect.nTop;	
						pInfo->CoverBlock[k].rcBlock.right = m_VideoCoveInfo.stuCoverBlock[k].stuRect.nRight;	
						pInfo->CoverBlock[k].rcBlock.bottom = m_VideoCoveInfo.stuCoverBlock[k].stuRect.nBottom;			
					}	
				}	
			}
			else
			{
				MessageBox(ConvertString("GetConfig failed(cover)!"), ConvertString("Prompt"));	
			}
		}
		
		if (szOutBuffer)
		{
			delete []szOutBuffer;
			szOutBuffer = NULL;
		}
	}	
	else
	{
		MessageBox(ConvertString("Login first!"), ConvertString("Prompt"));
	}		
}

void CClientDemo5Dlg::SetOneCoverConfigInfo(DHDEV_VIDEOCOVER_CFG *pInfo, int nCurChannel)
{
	if(0 != m_LoginID && pInfo != NULL)
	{
		char *szInBuffer = new char[32*1024];
		if (szInBuffer == NULL)
		{
			return;	
		}
		int nerror = 0;
		int nrestart = 0;
		int i = nCurChannel;
		//	for (int i = 0; i < nLength; i++)
		{
			memset(szInBuffer, 0, 32*1024);
			//组包
			m_VideoCoveInfo.nTotalBlocks = pInfo->bTotalBlocks;	
			m_VideoCoveInfo.nCurBlocks = pInfo->bCoverCount;
			
			for (int k = 0; k < pInfo->bCoverCount; k++)
			{
				m_VideoCoveInfo.stuCoverBlock[k].nBlockType = pInfo->CoverBlock[k].bBlockType;
				m_VideoCoveInfo.stuCoverBlock[k].nPreviewBlend = pInfo->CoverBlock[k].bPriview;	
				m_VideoCoveInfo.stuCoverBlock[k].nEncodeBlend = pInfo->CoverBlock[k].bEncode;
				
				m_VideoCoveInfo.stuCoverBlock[k].stuColor.nRed = (pInfo->CoverBlock[k].nColor>>24)&0xff;	
				m_VideoCoveInfo.stuCoverBlock[k].stuColor.nGreen = (pInfo->CoverBlock[k].nColor>>16)&0xff;		
				m_VideoCoveInfo.stuCoverBlock[k].stuColor.nBlue = (pInfo->CoverBlock[k].nColor>>8)&0xff;	
				m_VideoCoveInfo.stuCoverBlock[k].stuColor.nAlpha = pInfo->CoverBlock[k].nColor&0xff;;	
				
				m_VideoCoveInfo.stuCoverBlock[k].stuRect.nLeft = pInfo->CoverBlock[k].rcBlock.left;
				m_VideoCoveInfo.stuCoverBlock[k].stuRect.nTop = pInfo->CoverBlock[k].rcBlock.top;	
				m_VideoCoveInfo.stuCoverBlock[k].stuRect.nRight = pInfo->CoverBlock[k].rcBlock.right;	
				m_VideoCoveInfo.stuCoverBlock[k].stuRect.nBottom = pInfo->CoverBlock[k].rcBlock.bottom;			
			}

			if (pInfo->bCoverCount == 0)
			{
				m_stuEncodeInfo.dwCoverEnableMask = 0;
			}
		
			CFG_ENCODE_INFO stuEncoudeInfo = {0};

			GetOneChannelConfigInfo(&stuEncoudeInfo, i);
			memcpy(&m_stuEncodeInfo.stuVideoCover, &m_VideoCoveInfo, sizeof(CFG_VIDEO_COVER));

			BOOL bRet = CLIENT_PacketData(CFG_CMD_ENCODE, (char *)&m_stuEncodeInfo, sizeof(CFG_ENCODE_INFO), szInBuffer, 32*1024);
			if (bRet == FALSE)
			{
				MessageBox(ConvertString("Pack data error"), ConvertString("Prompt"));
			}
			else
			{
				BOOL bSuccess = CLIENT_SetNewDevConfig(m_LoginID, CFG_CMD_ENCODE, i, szInBuffer, 32*1024, &nerror, &nrestart, 5000);		
				if (bSuccess)
				{
					if (nrestart == 1)
					{
						MessageBox(ConvertString("Save config info successfully!devide need restart!"), ConvertString("Prompt"));
					}
				}
				else
				{
					
					MessageBox(ConvertString("SetConfig failed"), ConvertString("Prompt"));	
				}
				
			}
		}
		
		if (szInBuffer)
		{
			delete []szInBuffer;
			szInBuffer = NULL;
		}
	}
	
	else
	{
		MessageBox(ConvertString("Login first!"), ConvertString("Prompt"));
	}
}

void CClientDemo5Dlg::GetStrategyConfigInfo()
{
	if(m_LoginID != 0)
	{
		DWORD dwRetLen =0;
	
        CFG_DVRIP_INFO stuDVRIPInfo = {0};
        if (GetDVRIPConfig(stuDVRIPInfo))
        {
            m_StrategyDlg.m_StrategyTrans.InitDlgInfo(&stuDVRIPInfo);
        }
		
		DHDEV_DOWNLOAD_STRATEGY_CFG stuDownload;
		BOOL bSuccess = CLIENT_GetDevConfig(m_LoginID,DH_DEV_DOWNLOAD_STRATEGY,0,(VOID*)&stuDownload,sizeof(DHDEV_DOWNLOAD_STRATEGY_CFG),&dwRetLen);
		if(bSuccess && dwRetLen == sizeof(DHDEV_DOWNLOAD_STRATEGY_CFG))
		{
			m_StrategyDlg.m_StrategyDownload.InitDlgInfo(&stuDownload);
		}
		else
		{
			MessageBox(ConvertString("get record transmission strategy failed!"), ConvertString("Prompt"));
		}
		m_StrategyDlg.m_StrategyIPFileter.m_lLogin = m_LoginID;
		//m_StrategyDlg.m_StrategyMacFilter.m_lLogin = m_LoginID;

		m_StrategyDlg.m_StrategyIPFileter.GetIPFilterCfg();
		//m_StrategyDlg.m_StrategyMacFilter.GetMacFilterCfg();


		m_StrategyDlg.m_StrategyEncryption.m_lLogin = m_LoginID;
		m_StrategyDlg.m_StrategyEncryption.m_nChannel = m_nChannel > CHANNEL_NUM_LIMIT ? CHANNEL_NUM_LIMIT : m_nChannel;
		m_StrategyDlg.m_StrategyEncryption.GetEncryptionCfg();
		
	}
	else
	{
		MessageBox(ConvertString("Login first!"), ConvertString("Prompt"));
	}
}

void CClientDemo5Dlg::SetStrategyConfigInfo(CFG_DVRIP_INFO* pDVRIPInfo,
											DHDEV_DOWNLOAD_STRATEGY_CFG* pDownloadInfo)
{
	if(0 != m_LoginID && pDVRIPInfo != NULL && pDownloadInfo != NULL)
	{
		//Save information 
		SetDVRIPConfig(*pDVRIPInfo);

		BOOL bSuccess = CLIENT_SetDevConfig(m_LoginID, DH_DEV_DOWNLOAD_STRATEGY, -1,
			pDownloadInfo, sizeof(DHDEV_DOWNLOAD_STRATEGY_CFG), SDK_DEMO_WAITTIME);
		if (bSuccess)
		{
			//MessageBox(ConvertString("save record transmission strategy successfully!"), ConvertString("Prompt"));
		}
		else
		{
			MessageBox(ConvertString("save record transmission strategy failed!"), ConvertString("Prompt"));
		}
	}
	else
	{
		MessageBox(ConvertString("Login first!"), ConvertString("Prompt"));
	}
}

//Configuration file 
LONG CClientDemo5Dlg::ImportConfigFile(char* szPathName, fDownLoadPosCallBack cbUploadPos, DWORD dwUser)
{
	if(NULL == szPathName || NULL == cbUploadPos )
	{
		return -1;
	}

	return CLIENT_ImportConfigFile(m_LoginID, szPathName, cbUploadPos, dwUser, 0);
}

LONG CClientDemo5Dlg::ExportConfigFile(char* szFileName, DH_CONFIG_FILE_TYPE emConfigFileType, fDownLoadPosCallBack cbUploadPos, DWORD dwUser)
{
	if(NULL == szFileName || NULL == cbUploadPos )
	{
		return -1;
	}
	
	return CLIENT_ExportConfigFile(m_LoginID, emConfigFileType, szFileName, cbUploadPos, dwUser);
}

BOOL g_bSignal = TRUE;
void CClientDemo5Dlg::OnTimer(UINT_PTR nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if (g_bSignal)
	{
//		OnBtnLogin();
		g_bSignal = FALSE;
	}
	else
	{
//		OnBtnLogout();
		g_bSignal = TRUE;
	}
	
	CDialog::OnTimer(nIDEvent);
}


void CClientDemo5Dlg::ResolutionSizetoInt(int nResolution, int *nWidth, int *nHeight)
{
	if(m_nVideoStandard == 0)  //PAL
	{
		switch (nResolution)
		{
			case 0: 			*nWidth = 704;	*nHeight = 576;		break;//D1
			case 1:				*nWidth = 352;	*nHeight = 576;		break;//HD1
			case 2:				*nWidth = 704;	*nHeight = 288;		break;//BCIF
			case 3:				*nWidth = 352;	*nHeight = 288;		break;//CIF
			case 4:				*nWidth = 176;	*nHeight = 144;		break;//QCIF
			case 5:				*nWidth = 640;	*nHeight = 480;		break;//VGA
			case 6:				*nWidth = 320;	*nHeight = 240;		break;//QVGA
			case 7:				*nWidth = 480;	*nHeight = 480;		break;//SVCD
			case 8:				*nWidth = 160;	*nHeight = 128;		break;//QQVGA
			case 9:				*nWidth = 800;  *nHeight = 592;		break;//SVGA
			case 10:			*nWidth = 1024;	*nHeight = 768;		break;//XVGA
			case 11: 			*nWidth = 1280;	*nHeight = 800;		break;//WXGA
			case 12:			*nWidth = 1280;	*nHeight = 1024;	break;//SXGA
			case 13:			*nWidth = 1600;	*nHeight = 1024;	break;//WSXGA
			case 14:			*nWidth = 1600;	*nHeight = 1200;	break;//UXGA
			case 15:			*nWidth = 1920;	*nHeight = 1200;	break;//WUXGA
			case 16:			*nWidth = 240;	*nHeight = 192;		break;//LTF
			case 17:			*nWidth = 1280;	*nHeight = 720;		break;//720
			case 18:			*nWidth = 1920;	*nHeight = 1080;	break;//1080
			case 19:			*nWidth = 1280;	*nHeight = 960;		break;//1_3M
			case 20:			*nWidth = 1872;	*nHeight = 1408;	break;//2M
			case 21:			*nWidth = 3744;	*nHeight = 1408;	break;//5M
			case 22:			*nWidth = 2048;	*nHeight = 1536;	break;//3M
			case 23:			*nWidth = 2432;	*nHeight = 2050;	break;//5_0M
			case 24:			*nWidth = 1216;	*nHeight = 1024;	break;//1_2M
			case 25:			*nWidth = 1408;	*nHeight = 1024;	break;//1408_1024
			case 26:			*nWidth = 3296;	*nHeight = 2472;	break;//8M
			case 27:			*nWidth = 2560;	*nHeight = 1920;	break;//2560_1920
			case 28:			*nWidth = 960;	*nHeight = 576;		break;//960H
			case 29:			*nWidth = 960;  *nHeight = 720;		break;//960_720
			case 30:			*nWidth = 640;	*nHeight = 360;		break;//NHD
			case 31:			*nWidth = 320;	*nHeight = 180;		break;//QNHD
			case 32:			*nWidth = 160;	*nHeight = 90;		break;//QQNHD
			default:	ASSERT(FALSE);				break;
		}
	}		
	else
	{
		switch (nResolution)
		{
			case 0: 			*nWidth = 704;	*nHeight = 480;		break;//D1
			case 1:				*nWidth = 352;	*nHeight = 480;		break;//HD1
			case 2:				*nWidth = 704;	*nHeight = 240;		break;//BCIF
			case 3:				*nWidth = 352;	*nHeight = 240;		break;//CIF
			case 4:				*nWidth = 176;	*nHeight = 120;		break;//QCIF
			case 5:				*nWidth = 640;	*nHeight = 480;		break;//VGA
			case 6:				*nWidth = 320;	*nHeight = 240;		break;//QVGA
			case 7:				*nWidth = 480;	*nHeight = 480;		break;//SVCD
			case 8:				*nWidth = 160;	*nHeight = 128;		break;//QQVGA
			case 9:				*nWidth = 800;  *nHeight = 592;		break;//SVGA
			case 10:			*nWidth = 1024;	*nHeight = 768;		break;//XVGA
			case 11: 			*nWidth = 1280;	*nHeight = 800;		break;//WXGA
			case 12:			*nWidth = 1280;	*nHeight = 1024;	break;//SXGA
			case 13:			*nWidth = 1600;	*nHeight = 1024;	break;//WSXGA
			case 14:			*nWidth = 1600;	*nHeight = 1200;	break;//UXGA
			case 15:			*nWidth = 1920;	*nHeight = 1200;	break;//WUXGA
			case 16:			*nWidth = 240;	*nHeight = 192;		break;//LTF
			case 17:			*nWidth = 1280;	*nHeight = 720;		break;//720
			case 18:			*nWidth = 1920;	*nHeight = 1080;	break;//1080
			case 19:			*nWidth = 1280;	*nHeight = 960;		break;//1_3M
			case 20:			*nWidth = 1872;	*nHeight = 1408;	break;//2M
			case 21:			*nWidth = 3744;	*nHeight = 1408;	break;//5M
			case 22:			*nWidth = 2048;	*nHeight = 1536;	break;//3M
			case 23:			*nWidth = 2432;	*nHeight = 2050;	break;//5_0M
			case 24:			*nWidth = 1216;	*nHeight = 1024;	break;//1_2M
			case 25:			*nWidth = 1408;	*nHeight = 1024;	break;//1408_1024
			case 26:			*nWidth = 3296;	*nHeight = 2472;	break;//8M
			case 27:			*nWidth = 2560;	*nHeight = 1920;	break;//2560_1920
			case 28:			*nWidth = 960;	*nHeight = 480;		break;//960H
			case 29:			*nWidth = 960;  *nHeight = 720;		break;//960_720
			case 30:			*nWidth = 640;	*nHeight = 360;		break;//NHD
			case 31:			*nWidth = 320;	*nHeight = 180;		break;//QNHD
			case 32:			*nWidth = 160;	*nHeight = 90;		break;//QQNHD
			default:	ASSERT(FALSE);				break;
		}
	}
}

int CClientDemo5Dlg::ResolutionInttoSize(int nWidth, int nHeight)
{
	int nResolution = 0;

	if(m_nVideoStandard == 0)  //PAL
	{
		if (nWidth == 704 && nHeight == 576)
		{
			nResolution = 0;
		}
		else if (nWidth == 352 && nHeight == 576)
		{
			nResolution = 1;
		}
		else if (nWidth == 704 && nHeight == 288)
		{
			nResolution = 2;
		}
		else if (nWidth == 352 && nHeight == 288)
		{
			nResolution = 3;
		}
		else if (nWidth == 176 && nHeight == 144)
		{
			nResolution = 4;
		}
		else if (nWidth == 640 && nHeight == 480)
		{
			nResolution = 5;
		}
		else if (nWidth == 320 && nHeight == 240)
		{
			nResolution = 6;
		}
		else if (nWidth == 480 && nHeight == 480)
		{
			nResolution = 7;
		}
		else if (nWidth == 160 && nHeight == 128)
		{
			nResolution = 8;
		}
		else if (nWidth == 800 && nHeight == 592)
		{
			nResolution = 9;
		}
		else if (nWidth == 1024 && nHeight == 768)
		{
			nResolution = 10;
		}
		else if (nWidth == 1280 && nHeight == 800)
		{
			nResolution = 11;
		}
		else if (nWidth == 1280 && nHeight == 1024)
		{
			nResolution = 12;
		}
		else if (nWidth == 1600 && nHeight == 1024)
		{
			nResolution = 13;
		}
		else if (nWidth == 1600 && nHeight == 1200)
		{
			nResolution = 14;
		}
		else if (nWidth == 1920 && nHeight == 1200)
		{
			nResolution = 15;
		}
		else if (nWidth == 240 && nHeight == 192)
		{
			nResolution = 16;
		}
		else if (nWidth == 1280 && nHeight == 720)
		{
			nResolution = 17;
		}
		else if (nWidth == 1920 && nHeight == 1080)
		{
			nResolution = 18;
		}
		else if (nWidth == 1280 && nHeight == 960)
		{
			nResolution = 19;
		}
		else if (nWidth == 1872 && nHeight == 1408)
		{
			nResolution = 20;
		}
		else if (nWidth == 3744 && nHeight == 1408)
		{
			nResolution = 21;
		}
		else if (nWidth == 2048 && nHeight == 1536)
		{
			nResolution = 22;
		}
		else if (nWidth == 2432 && nHeight == 2050)
		{
			nResolution = 23;
		}
		else if (nWidth == 1216 && nHeight == 1024)
		{
			nResolution = 24;
		}
		else if (nWidth == 1408 && nHeight == 1024)
		{
			nResolution = 25;
		}
		else if (nWidth == 3296 && nHeight == 2472)
		{
			nResolution = 26;
		}
		else if (nWidth == 2560 && nHeight == 1920)
		{
			nResolution = 27;
		}
		else if (nWidth == 960 && nHeight == 576)
		{
			nResolution = 28;
		}
		else if (nWidth == 960 && nHeight == 720)
		{
			nResolution = 29;
		}
		else if (nWidth == 640 && nHeight == 360)
		{
			nResolution = 30;
		}
		else if (nWidth == 320 && nHeight == 180)
		{
			nResolution = 31;
		}
		else if (nWidth == 160 && nHeight == 90)
		{
			nResolution = 32;
		}
	}
	else
	{
		if (nWidth == 704 && nHeight == 480)
		{
			nResolution = 0;
		}
		else if (nWidth == 352 && nHeight == 480)
		{
			nResolution = 1;
		}
		else if (nWidth == 704 && nHeight == 240)
		{
			nResolution = 2;
		}
		else if (nWidth == 352 && nHeight == 240)
		{
			nResolution = 3;
		}
		else if (nWidth == 176 && nHeight == 120)
		{
			nResolution = 4;
		}
		else if (nWidth == 640 && nHeight == 480)
		{
			nResolution = 5;
		}
		else if (nWidth == 320 && nHeight == 240)
		{
			nResolution = 6;
		}
		else if (nWidth == 480 && nHeight == 480)
		{
			nResolution = 7;
		}
		else if (nWidth == 160 && nHeight == 128)
		{
			nResolution = 8;
		}
		else if (nWidth == 800 && nHeight == 592)
		{
			nResolution = 9;
		}
		else if (nWidth == 1024 && nHeight == 768)
		{
			nResolution = 10;
		}
		else if (nWidth == 1280 && nHeight == 800)
		{
			nResolution = 11;
		}
		else if (nWidth == 1280 && nHeight == 1024)
		{
			nResolution = 12;
		}
		else if (nWidth == 1600 && nHeight == 1024)
		{
			nResolution = 13;
		}
		else if (nWidth == 1600 && nHeight == 1200)
		{
			nResolution = 14;
		}
		else if (nWidth == 1920 && nHeight == 1200)
		{
			nResolution = 15;
		}
		else if (nWidth == 240 && nHeight == 192)
		{
			nResolution = 16;
		}
		else if (nWidth == 1280 && nHeight == 720)
		{
			nResolution = 17;
		}
		else if (nWidth == 1920 && nHeight == 1080)
		{
			nResolution = 18;
		}
		else if (nWidth == 1280 && nHeight == 960)
		{
			nResolution = 19;
		}
		else if (nWidth == 1872 && nHeight == 1408)
		{
			nResolution = 20;
		}
		else if (nWidth == 3744 && nHeight == 1408)
		{
			nResolution = 21;
		}
		else if (nWidth == 2048 && nHeight == 1536)
		{
			nResolution = 22;
		}
		else if (nWidth == 2432 && nHeight == 2050)
		{
			nResolution = 23;
		}
		else if (nWidth == 1216 && nHeight == 1024)
		{
			nResolution = 24;
		}
		else if (nWidth == 1408 && nHeight == 1024)
		{
			nResolution = 25;
		}
		else if (nWidth == 3296 && nHeight == 2472)
		{
			nResolution = 26;
		}
		else if (nWidth == 2560 && nHeight == 1920)
		{
			nResolution = 27;
		}
		else if (nWidth == 960 && nHeight == 480)
		{
			nResolution = 28;
		}
		else if (nWidth == 960 && nHeight == 720)
		{
			nResolution = 29;
		}
		else if (nWidth == 640 && nHeight == 360)
		{
			nResolution = 30;
		}
		else if (nWidth == 320 && nHeight == 180)
		{
			nResolution = 31;
		}
		else if (nWidth == 160 && nHeight == 90)
		{
			nResolution = 32;
		}
	}

	return nResolution;
}

void CClientDemo5Dlg::ParseEventHandle(CFG_ALARM_MSG_HANDLE &stuHandlle, DH_MSG_HANDLE_EX *pstruHandle)
{
	if (pstruHandle == NULL)
	{
		return;
	}

	for (int i = 0; i < 32; i++)
	{
		pstruHandle->byRecordChannel[i] = (stuHandlle.dwRecordMask[0]>>i)&0x01;	
		pstruHandle->byRelAlarmOut[i] = (stuHandlle.dwAlarmOutMask[0]>>i)&0x01;		
		pstruHandle->struPtzLink[i].iType = stuHandlle.stuPtzLink[i].emType;
		pstruHandle->struPtzLink[i].iValue = stuHandlle.stuPtzLink[i].nValue;
		pstruHandle->byTour[i] = (stuHandlle.dwTourMask[0]>>i)&0x01;			
		pstruHandle->bySnap[i] = (stuHandlle.dwSnapshot[0]>>i)&0x01;		
	}

	pstruHandle->dwMatrix = stuHandlle.dwMatrixMask[0];	
	
	if (stuHandlle.abRecordEnable)
	{	
		if (stuHandlle.bRecordEnable)
		{
			pstruHandle->dwActionFlag |= DH_ALARM_RECORD;	
		}
		pstruHandle->dwActionMask |= DH_ALARM_RECORD;
	} 
	
	if (stuHandlle.abAlarmOutEn)
	{
		if (stuHandlle.bAlarmOutEn)
		{
			pstruHandle->dwActionFlag |= DH_ALARM_OUT;
		}
		pstruHandle->dwActionMask |= DH_ALARM_OUT;
	}
	
	if (stuHandlle.abPtzLinkEn)
	{
		if (stuHandlle.bPtzLinkEn)
		{
			pstruHandle->dwActionFlag |= DH_ALARM_PTZ;
		}
		pstruHandle->dwActionMask |= DH_ALARM_PTZ;
	}

	if (stuHandlle.abTourEnable)
	{
		if (stuHandlle.bTourEnable)
		{
			pstruHandle->dwActionFlag |= DH_ALARM_TOUR;
		}
		pstruHandle->dwActionMask |= DH_ALARM_TOUR;
	}
	
	if (stuHandlle.abSnapshotEn)
	{
		if (stuHandlle.bSnapshotEn)
		{
			pstruHandle->dwActionFlag |= DH_ALARM_SNAP;
		}
		pstruHandle->dwActionMask |= DH_ALARM_SNAP;
	}

	if (stuHandlle.abTipEnable)
	{
		if (stuHandlle.bTipEnable)
		{
			pstruHandle->dwActionFlag |= DH_ALARM_TIP;
		}
		pstruHandle->dwActionMask |= DH_ALARM_TIP;
	}

	if (stuHandlle.abMailEnable)
	{
		if (stuHandlle.bMailEnable)
		{
			pstruHandle->dwActionFlag |= DH_ALARM_MAIL;
		}
		pstruHandle->dwActionMask |= DH_ALARM_MAIL;
	}

	if (stuHandlle.abMessageEnable)
	{
		if (stuHandlle.bMessageEnable)
		{
			pstruHandle->dwActionFlag |= DH_ALARM_UPLOAD;
		}
		pstruHandle->dwActionMask |= DH_ALARM_UPLOAD;
	}

	if (stuHandlle.abBeepEnable)
	{
		if (stuHandlle.bBeepEnable)
		{
			pstruHandle->dwActionFlag |= DH_ALARM_BEEP;
		}
		pstruHandle->dwActionMask |= DH_ALARM_BEEP;
	}

	if (stuHandlle.abVoiceEnable)
	{
		if (stuHandlle.bVoiceEnable)
		{
			pstruHandle->dwActionFlag |= DH_ALARM_VOICE;
		}
		pstruHandle->dwActionMask |= DH_ALARM_VOICE;
	}
	
	pstruHandle->bLog = stuHandlle.bLogEnable;
	pstruHandle->bMatrixEn = stuHandlle.bMatrixEnable;
	pstruHandle->dwEventLatch = stuHandlle.nEventLatch;
	pstruHandle->dwRecLatch = stuHandlle.nRecordLatch;	
	pstruHandle->dwDuration = stuHandlle.nAlarmOutLatch;	
	pstruHandle->bySnapshotTimes = stuHandlle.nSnapshotTimes;	
	pstruHandle->bMMSEn = stuHandlle.bMMSEnable;	
	pstruHandle->bMessageToNet = stuHandlle.bMessageToNetEn;	
}

void CClientDemo5Dlg::BuildEventHandle(DH_MSG_HANDLE_EX stuHandlle, CFG_ALARM_MSG_HANDLE *pstruHandle)
{
	if (pstruHandle == NULL)
	{
		return;
	}

	pstruHandle->dwRecordMask[0] = 0;
	pstruHandle->dwAlarmOutMask[0] = 0;
	pstruHandle->dwTourMask[0] = 0;
	pstruHandle->dwSnapshot[0] = 0;

	for (int i = 0; i < 32; i++)
	{
		if (stuHandlle.byRecordChannel[i])
		{
			pstruHandle->dwRecordMask[0] |= (0x01<<i);
		}
		if (stuHandlle.byRelAlarmOut[i])
		{
			pstruHandle->dwAlarmOutMask[0] |= (0x01<<i);
		}
		if (stuHandlle.byTour[i])
		{
			pstruHandle->dwTourMask[0] |= (0x01<<i);
		}
		if (stuHandlle.bySnap[i])
		{
			pstruHandle->dwSnapshot[0] |= (0x01<<i);
		}
		pstruHandle->stuPtzLink[i].emType = (CFG_LINK_TYPE)stuHandlle.struPtzLink[i].iType;
		pstruHandle->stuPtzLink[i].nValue = stuHandlle.struPtzLink[i].iValue;
	}
	
	pstruHandle->dwMatrixMask[0] = stuHandlle.dwMatrix; 
	pstruHandle->bRecordEnable = (stuHandlle.dwActionFlag&DH_ALARM_RECORD)>0?1:0;
	pstruHandle->bAlarmOutEn = (stuHandlle.dwActionFlag&DH_ALARM_OUT)>0?1:0;
	pstruHandle->bPtzLinkEn = (stuHandlle.dwActionFlag&DH_ALARM_PTZ)>0?1:0;
	pstruHandle->bTourEnable = (stuHandlle.dwActionFlag&DH_ALARM_TOUR)>0?1:0;
	pstruHandle->bSnapshotEn = (stuHandlle.dwActionFlag&DH_ALARM_SNAP)>0?1:0;
	pstruHandle->bTipEnable = (stuHandlle.dwActionFlag&DH_ALARM_TIP)>0?1:0;
	pstruHandle->bMailEnable = (stuHandlle.dwActionFlag&DH_ALARM_MAIL)>0?1:0;
	pstruHandle->bMessageEnable = (stuHandlle.dwActionFlag&DH_ALARM_UPLOAD)>0?1:0;
	pstruHandle->bBeepEnable = (stuHandlle.dwActionFlag&DH_ALARM_BEEP)>0?1:0;
	pstruHandle->abVoiceEnable = (stuHandlle.dwActionFlag&DH_ALARM_VOICE)>0?1:0;
	
	pstruHandle->bLogEnable = stuHandlle.bLog;
	pstruHandle->bMatrixEnable = stuHandlle.bMatrixEn;
	pstruHandle->nEventLatch = stuHandlle.dwEventLatch;
	pstruHandle->nRecordLatch = stuHandlle.dwRecLatch;	
	pstruHandle->nAlarmOutLatch = stuHandlle.dwDuration;	
	pstruHandle->nSnapshotTimes = stuHandlle.bySnapshotTimes;	
	pstruHandle->bMMSEnable = stuHandlle.bMMSEn;	
	pstruHandle->bMessageToNetEn = stuHandlle.bMessageToNet;
}

void CClientDemo5Dlg::Change_Utf8_Assic(unsigned char * pUTF8, char *destbuf)
{
	int nSrcStrLen = strlen((char*)pUTF8);
	int nDestStrLen = nSrcStrLen*2;
	char* tmpBuf = new char[nDestStrLen];
	memset(tmpBuf, 0, nDestStrLen);

	int nNum = MultiByteToWideChar(CP_UTF8, 0, (char*)pUTF8, nSrcStrLen, (LPWSTR)tmpBuf, nDestStrLen);
	nNum = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)tmpBuf, nNum, destbuf, nSrcStrLen, NULL, NULL);
	
	delete tmpBuf;
	tmpBuf = NULL;
	return ;
}

void CClientDemo5Dlg::Change_Assic_UTF8(char *pStrGBKData, int nlen, char *pbuf, int buflen)
{
	int nDestStrLen = nlen*2;
	char* tmpBuf = new char[nDestStrLen];
	memset(tmpBuf, 0, nDestStrLen);

	int nNum = MultiByteToWideChar(CP_ACP, 0, (char*)pStrGBKData, nlen, (LPWSTR)tmpBuf, nDestStrLen);
	nNum = WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)tmpBuf, nNum, pbuf, buflen, NULL, NULL);
	
	delete tmpBuf;
	tmpBuf = NULL;
	return ;
}

BOOL CClientDemo5Dlg::InitAlarmName(DHDEV_ALARM_SCHEDULE_EX* pAlarmInfo )
{
	BOOL bSuccess = TRUE;
	// 获取通道的报警名称
	char pBufName[2200] = {0};
	memset(pBufName, 0, 2200);
	DWORD dwRetLen = 0;
	bSuccess = CLIENT_GetDevConfig(m_LoginID, DH_DEV_LOCALALARM_NAME_CFG, -1
		, pBufName, 2200, &dwRetLen);

	if (bSuccess)
	{
		memcpy(pAlarmInfo->szAlarmName, pBufName
			, strlen(pBufName)>=sizeof(pAlarmInfo->szAlarmName)?sizeof(pAlarmInfo->szAlarmName)-1:strlen(pBufName));
		pAlarmInfo->szAlarmName[34*64-1] = '\0';
	}
	else
	{
		memset(pAlarmInfo->szAlarmName, 0, sizeof(pAlarmInfo->szAlarmName));
	}

	return bSuccess;
}

BOOL CClientDemo5Dlg::SetAlarmName(const DHDEV_ALARM_SCHEDULE_EX* pAlarmInfo )
{
    BOOL bSuccess = FALSE;
    // 获取通道的报警名称
    bSuccess = CLIENT_SetDevConfig(m_LoginID, DH_DEV_LOCALALARM_NAME_CFG, -1
        , (void *)pAlarmInfo->szAlarmName, strlen(pAlarmInfo->szAlarmName));
    
    return bSuccess;
}

void CClientDemo5Dlg::InitAVCFGVIdeoWidget(AV_CFG_VideoWidget *pstVideoWidget)
{
	if(NULL == pstVideoWidget)
	{
		return;
	}
	else
	{
		pstVideoWidget->nStructSize = sizeof(AV_CFG_VideoWidget);
		pstVideoWidget->stuChannelTitle.nStructSize = sizeof(AV_CFG_VideoWidgetChannelTitle);
		pstVideoWidget->stuTimeTitle.nStructSize = sizeof(AV_CFG_VideoWidgetTimeTitle);
		pstVideoWidget->stuChannelTitle.stuBackColor.nStructSize = sizeof(AV_CFG_Color);
		pstVideoWidget->stuChannelTitle.stuFrontColor.nStructSize = sizeof(AV_CFG_Color);
		pstVideoWidget->stuChannelTitle.stuRect.nStructSize = sizeof(AV_CFG_Rect);
		pstVideoWidget->stuTimeTitle.stuBackColor.nStructSize = sizeof(AV_CFG_Color);
		pstVideoWidget->stuTimeTitle.stuFrontColor.nStructSize = sizeof(AV_CFG_Color);
		pstVideoWidget->stuTimeTitle.stuRect.nStructSize = sizeof(AV_CFG_Rect);
		
		int j = 0;
		for (j=0; j<AV_CFG_Max_Video_Widget_Cover; ++j)
		{
			pstVideoWidget->stuCovers[j].nStructSize = sizeof(AV_CFG_VideoWidgetCover);
			pstVideoWidget->stuCovers[j].stuFrontColor.nStructSize = sizeof(AV_CFG_Color);
			pstVideoWidget->stuCovers[j].stuBackColor.nStructSize = sizeof(AV_CFG_Color);
			pstVideoWidget->stuCovers[j].stuRect.nStructSize = sizeof(AV_CFG_Rect);
		}
		for (j=0; j<AV_CFG_Max_Video_Widget_Custom_Title; ++j)
		{
			pstVideoWidget->stuCustomTitle[j].nStructSize = sizeof(AV_CFG_VideoWidgetCustomTitle);
			pstVideoWidget->stuCustomTitle[j].stuFrontColor.nStructSize = sizeof(AV_CFG_Color);
			pstVideoWidget->stuCustomTitle[j].stuBackColor.nStructSize = sizeof(AV_CFG_Color);
			pstVideoWidget->stuCustomTitle[j].stuRect.nStructSize = sizeof(AV_CFG_Rect);
		}

	}

}


void CClientDemo5Dlg::GetOneChannelOsdInfo(AV_CFG_VideoWidget *pstVideoWidget, int nCurChannel)
{
	if(0 != m_LoginID)
	{
		if(NULL == pstVideoWidget)
		{
			return ;
		}
		
		char *szOutBuffer = new char[32*1024];
		if(NULL == szOutBuffer)
		{
			return;
		}

		if(nCurChannel < 0 || nCurChannel >= CHANNEL_NUM_LIMIT)
		{
			return ;
		}
		
		memset(pstVideoWidget, 0, sizeof(AV_CFG_VideoWidget));
		
		InitAVCFGVIdeoWidget(pstVideoWidget);

		int nerror = 0;

		BOOL bSuccess = CLIENT_GetNewDevConfig(m_LoginID, CFG_CMD_VIDEOWIDGET, nCurChannel, szOutBuffer, 32*1024, &nerror, 6000);
		if(bSuccess)
		{
			int nRetLen = 0;
			BOOL bRet = CLIENT_ParseData(CFG_CMD_VIDEOWIDGET, szOutBuffer, pstVideoWidget, sizeof(AV_CFG_VideoWidget), &nRetLen);
			if(!bRet)
			{
				MessageBox(ConvertString("OSD Parse data error"), ConvertString("Prompt"));
			}

		}
		else
		{
			MessageBox(ConvertString("Get osd data failed!"), ConvertString("Prompt"));
		}

		if (szOutBuffer)
		{
			delete []szOutBuffer;
			szOutBuffer = NULL;
		}

	}
	else
	{
		MessageBox(ConvertString("Login first!"), ConvertString("Prompt"));
	}
}
void CClientDemo5Dlg::SetOneChannelOsdInfo(AV_CFG_VideoWidget *pstVideoWidget, int nCurChannel)
{
	if(0 != m_LoginID)
	{

		if(NULL == pstVideoWidget)
		{
			return;
		}
		if(nCurChannel < 0 || nCurChannel >= CHANNEL_NUM_LIMIT)
		{
			return;
		}

		char *szOutBuffer = new char[32*1024];
		if(NULL == szOutBuffer)
		{
			return;
		}

		
		int nerror   = 0;
		int nrestart = 0;

		BOOL bRet = CLIENT_PacketData(CFG_CMD_VIDEOWIDGET, (char *)pstVideoWidget, sizeof(AV_CFG_VideoWidget), szOutBuffer, 32*1024);
		if(bRet)
		{
			BOOL bSuccess = CLIENT_SetNewDevConfig(m_LoginID, CFG_CMD_VIDEOWIDGET, nCurChannel, szOutBuffer, 32*1024, &nerror, &nrestart, 6000);
			if(bSuccess)
			{
				if (nrestart == 1)
				{
					MessageBox(ConvertString("Save config info successfully!devide need restart!"), ConvertString("Prompt"));
				}

			}
			else
			{
				MessageBox(ConvertString("Save config info failed!"), ConvertString("Prompt"));
			}
			
		}
		else
		{
			MessageBox(ConvertString("Pack data failed!"), ConvertString("Prompt"));
		}
		if(szOutBuffer)
		{
			delete[] szOutBuffer;
			szOutBuffer = NULL;
		}
	}
	else
	{
		MessageBox(ConvertString("Login first!"), ConvertString("Prompt"));
	}
}
void CClientDemo5Dlg::InitAVCFGVideoColor(AV_CFG_ChannelVideoColor *pstChannelVideoColor)
{
	if(NULL == pstChannelVideoColor)
	{
		return;
	}
	else
	{
		pstChannelVideoColor->nStructSize = sizeof(AV_CFG_ChannelVideoColor);
		for(int i = 0; i < AV_CFG_Max_VideoColor; i ++)
		{
			pstChannelVideoColor->stuColor[i].nStructSize = sizeof(AV_CFG_VideoColor);
			pstChannelVideoColor->stuColor[i].stuTimeSection.nStructSize = sizeof(AV_CFG_TimeSection);
		}
	}
}
void CClientDemo5Dlg::GetOneChannelVideoColor(AV_CFG_ChannelVideoColor *pstChannelVideoColor, int nCurChannel)
{
	if(0 != m_LoginID)
	{
		if(NULL == pstChannelVideoColor)
		{
			return;
		}

		char *szOutBuffer = new char[32*1024];
		if(NULL == szOutBuffer)
		{
			return;
		}
		if(nCurChannel < 0 || nCurChannel >= CHANNEL_NUM_LIMIT)
		{
			return ;
		}

		memset(pstChannelVideoColor, 0, sizeof(AV_CFG_ChannelVideoColor));
		
		InitAVCFGVideoColor(pstChannelVideoColor);

		int nerror = 0;

		BOOL bSuccess = CLIENT_GetNewDevConfig(m_LoginID, CFG_CMD_VIDEOCOLOR, nCurChannel, szOutBuffer, 32*1024, &nerror, 3000);
		if(bSuccess)
		{
			int nRetLen = 0;
			BOOL bRet = CLIENT_ParseData(CFG_CMD_VIDEOCOLOR, szOutBuffer, pstChannelVideoColor, sizeof(AV_CFG_ChannelVideoColor),&nRetLen);
			if(!bRet)
			{
				MessageBox(ConvertString("VideoColor Parse data error"), ConvertString("Prompt"));
			}
		}
		else
		{
			MessageBox(ConvertString("Get VideoColor data failed!"), ConvertString("Prompt"));
		}
		
		if(szOutBuffer)
		{
			delete[] szOutBuffer;
			szOutBuffer = NULL;
		}

	}
	else
	{
		MessageBox(ConvertString("Login first!"), ConvertString("Prompt"));
	}
}

BOOL CClientDemo5Dlg::IsWholeDay(AV_CFG_ChannelVideoColor *pstChannelVideoColor)
{
	int nAllSeconds = 0;
	int nCount = pstChannelVideoColor->nColorNum;
	nCount = nCount > AV_CFG_Max_VideoColor ? AV_CFG_Max_VideoColor:nCount;
	for (int i=0; i<nCount; i++)
	{
		if (pstChannelVideoColor->stuColor[i].stuTimeSection.nMask & 1)
		{
			int nBeginSecs = pstChannelVideoColor->stuColor[i].stuTimeSection.nBeginHour * 60 * 60 + pstChannelVideoColor->stuColor[i].stuTimeSection.nBeginMinute * 60 
				+ pstChannelVideoColor->stuColor[i].stuTimeSection.nBeginSecond;
			int nEndSecs = pstChannelVideoColor->stuColor[i].stuTimeSection.nEndHour * 60 * 60 + pstChannelVideoColor->stuColor[i].stuTimeSection.nEndMinute * 60 
				+ pstChannelVideoColor->stuColor[i].stuTimeSection.nEndSecond;
			nAllSeconds += nEndSecs - nBeginSecs;
		}
	}

	const int K_ONE_DAY_SECS = 24 * 60 * 60;
	return nAllSeconds == K_ONE_DAY_SECS ? TRUE : FALSE;
}

void CClientDemo5Dlg::SetOneChannelVideoColor(AV_CFG_ChannelVideoColor *pstChannelVideoColor, int nCurChannel)
{
	if(0 != m_LoginID)
	{
		if(NULL == pstChannelVideoColor)
		{
			return;
		}
		if(nCurChannel < 0 || nCurChannel >= CHANNEL_NUM_LIMIT)
		{
			return;
		}
		if (!IsWholeDay(pstChannelVideoColor))
		{
			MessageBox(ConvertString("The time sections must add to a whole day!"), ConvertString("Prompt"));
			return;
		}

		char *szOutBuffer = new char[32*1024];
		if(NULL == szOutBuffer)
		{
			return;
		}
		
		int nerror   = 0;
		int nrestart = 0;

		BOOL bRet = CLIENT_PacketData(CFG_CMD_VIDEOCOLOR, (char *)pstChannelVideoColor, sizeof(AV_CFG_ChannelVideoColor), szOutBuffer, 32*1024);
		if(bRet)
		{
			BOOL bSuccess = CLIENT_SetNewDevConfig(m_LoginID, CFG_CMD_VIDEOCOLOR, nCurChannel, szOutBuffer, 32*1024, &nerror, &nrestart, 3000);
			if(bSuccess)
			{
				if (nrestart == 1)
				{
					MessageBox(ConvertString("Save config info successfully!devide need restart!"), ConvertString("Prompt"));
				}
				
			}
			else
			{
				MessageBox(ConvertString("Save video color info failed!"), ConvertString("Prompt"));
			}
			
		}
		else
		{
			MessageBox(ConvertString("Pack data failed!"), ConvertString("Prompt"));
		}
		if(szOutBuffer)
		{
			delete[] szOutBuffer;
			szOutBuffer = NULL;
		}
	}
	else
	{
		MessageBox(ConvertString("Login first!"), ConvertString("Prompt"));
	}
}
void CClientDemo5Dlg::GetOneChannelName(AV_CFG_ChannelName *pstChannelName, int nCurChannel)
{
	if(0 != m_LoginID)
	{
		if(NULL == pstChannelName)
		{
			return;
		}
		
		char *szOutBuffer = new char[32*1024];
		if(NULL == szOutBuffer)
		{
			return;
		}
		if(nCurChannel < 0 || nCurChannel >= CHANNEL_NUM_LIMIT)
		{
			return ;
		}
		
		memset(pstChannelName, 0, sizeof(AV_CFG_ChannelName));
		
		InitAVCFGChannelName(pstChannelName);
		
		int nerror = 0;
		
		BOOL bSuccess = CLIENT_GetNewDevConfig(m_LoginID, CFG_CMD_CHANNELTITLE, nCurChannel, szOutBuffer, 32*1024, &nerror, SDK_DEMO_WAITTIME);
		if(bSuccess)
		{
			int nRetLen = 0;
			BOOL bRet = CLIENT_ParseData(CFG_CMD_CHANNELTITLE, szOutBuffer, pstChannelName, sizeof(AV_CFG_ChannelName),&nRetLen);
			if(!bRet)
			{
				MessageBox(ConvertString("Channel Title Parse data error"), ConvertString("Prompt"));
			}
		}
		else
		{
			MessageBox(ConvertString("Get channel title failed!"), ConvertString("Prompt"));
		}
		
		if(szOutBuffer)
		{
			delete[] szOutBuffer;
			szOutBuffer = NULL;
		}
		
	}
	else
	{
		MessageBox(ConvertString("Login first!"), ConvertString("Prompt"));
	}
	
}
void CClientDemo5Dlg::SetOneChannelName(AV_CFG_ChannelName *pstChannelName, int nCurChannel)
{
	if(0 != m_LoginID)
	{
		if(NULL == pstChannelName)
		{
			return;
		}
		if(nCurChannel < 0 || nCurChannel >= CHANNEL_NUM_LIMIT)
		{
			return;
		}
		char *szOutBuffer = new char[32*1024];
		if(NULL == szOutBuffer)
		{
			return;
		}
		
		int nerror   = 0;
		int nrestart = 0;
		
		BOOL bRet = CLIENT_PacketData(CFG_CMD_CHANNELTITLE, (char *)pstChannelName, sizeof(AV_CFG_ChannelName), szOutBuffer, 32*1024);
		if(bRet)
		{
			BOOL bSuccess = CLIENT_SetNewDevConfig(m_LoginID, CFG_CMD_CHANNELTITLE, nCurChannel, szOutBuffer, 32*1024, &nerror, &nrestart, SDK_DEMO_WAITTIME);
			if(bSuccess)
			{
				if (nrestart == 1)
				{
					MessageBox(ConvertString("Save config info successfully!devide need restart!"), ConvertString("Prompt"));
				}
				
			}
			else
			{
				MessageBox(ConvertString("Save channel title failed!"), ConvertString("Prompt"));
			}
			
		}
		else
		{
			MessageBox(ConvertString("Pack data failed!"), ConvertString("Prompt"));
		}
		if(szOutBuffer)
		{
			delete[] szOutBuffer;
			szOutBuffer = NULL;
		}
	}
	else
	{
		MessageBox(ConvertString("Login first!"), ConvertString("Prompt"));
	}
}

void CClientDemo5Dlg::InitAVCFGChannelName(AV_CFG_ChannelName *pstChannelName)
{
	if(NULL == pstChannelName)
	{
		return;	
	}
	else
	{
		pstChannelName->nStructSize = sizeof(AV_CFG_ChannelName);
	}

}
void CClientDemo5Dlg::GetOneVideoInOption(CFG_VIDEO_IN_OPTIONS * pstVideoInOption, int nCurChannel)
{
	if(0 != m_LoginID)
	{
		if(NULL == pstVideoInOption)
		{
			return;
		}
		
		char *szOutBuffer = new char[32*1024];
		if(NULL == szOutBuffer)
		{
			return;
		}
		if(nCurChannel < 0 || nCurChannel >= CHANNEL_NUM_LIMIT)
		{
			return ;
		}
		
		memset(pstVideoInOption, 0, sizeof(CFG_VIDEO_IN_OPTIONS));
			
		int nerror = 0;
		
		BOOL bSuccess = CLIENT_GetNewDevConfig(m_LoginID, CFG_CMD_VIDEOINOPTIONS, nCurChannel, szOutBuffer, 32*1024, &nerror, 3000);
		if(bSuccess)
		{
			int nRetLen = 0;
			BOOL bRet = CLIENT_ParseData(CFG_CMD_VIDEOINOPTIONS, szOutBuffer, pstVideoInOption, sizeof(CFG_VIDEO_IN_OPTIONS),&nRetLen);
			if(!bRet)
			{
				MessageBox(ConvertString("VideoColor Parse data error"), ConvertString("Prompt"));
			}
		}
		else
		{
			MessageBox(ConvertString("Get VideoColor data failed!"), ConvertString("Prompt"));
		}
		
		if(szOutBuffer)
		{
			delete[] szOutBuffer;
			szOutBuffer = NULL;
		}
		
	}
	else
	{
		MessageBox(ConvertString("Login first!"), ConvertString("Prompt"));
	}
}
void CClientDemo5Dlg::SetOneVideoInOption(CFG_VIDEO_IN_OPTIONS * pstVideoInOption, int nCurChannel)
{
	if(0 != m_LoginID)
	{
		if(NULL == pstVideoInOption)
		{
			return;
		}
		if(nCurChannel < 0 || nCurChannel >= CHANNEL_NUM_LIMIT)
		{
			return;
		}
		char *szOutBuffer = new char[32*1024];
		if(NULL == szOutBuffer)
		{
			return;
		}
		
		int nerror   = 0;
		int nrestart = 0;
		
		BOOL bRet = CLIENT_PacketData(CFG_CMD_VIDEOINOPTIONS, (char *)pstVideoInOption, sizeof(CFG_VIDEO_IN_OPTIONS), szOutBuffer, 32*1024);
		if(bRet)
		{
			BOOL bSuccess = CLIENT_SetNewDevConfig(m_LoginID, CFG_CMD_VIDEOINOPTIONS, nCurChannel, szOutBuffer, 32*1024, &nerror, &nrestart, 3000);
			if(bSuccess)
			{
				if (nrestart == 1)
				{
					MessageBox(ConvertString("Save config info successfully!devide need restart!"), ConvertString("Prompt"));
				}
				
			}
			else
			{
				MessageBox(ConvertString("Save config info failed!"), ConvertString("Prompt"));
			}
			
		}
		else
		{
			MessageBox(ConvertString("Pack data failed!"), ConvertString("Prompt"));
		}
		if(szOutBuffer)
		{
			delete[] szOutBuffer;
			szOutBuffer = NULL;
		}
	}
	else
	{
		MessageBox(ConvertString("Login first!"), ConvertString("Prompt"));
	}

}
void CClientDemo5Dlg::GetOneVideoCapVieoInfo(CFG_CAP_VIDEOINPUT_INFO *pstCapVieoInput, int nCurChannel)
{
	if(0 != m_LoginID)
	{
		if(NULL == pstCapVieoInput)
		{
			return;
		}
		
		char *szOutBuffer = new char[32*1024];
		if(NULL == szOutBuffer)
		{
			return;
		}
		if(nCurChannel < 0 || nCurChannel >= CHANNEL_NUM_LIMIT)
		{
			return ;
		}
		
		memset(pstCapVieoInput, 0, sizeof(CFG_CAP_VIDEOINPUT_INFO));
		
		int nerror = 0;
		
		BOOL bSuccess = CLIENT_QueryNewSystemInfo(m_LoginID, CFG_CAP_CMD_VIDEOINPUT, nCurChannel, szOutBuffer, 32*1024, &nerror, 3000);
		if(bSuccess)
		{
			int nRetLen = 0;
			BOOL bRet = CLIENT_ParseData(CFG_CAP_CMD_VIDEOINPUT, szOutBuffer, pstCapVieoInput, sizeof(CFG_CAP_VIDEOINPUT_INFO),&nRetLen);
			if(!bRet)
			{
				MessageBox(ConvertString("VideoColor Parse data error"), ConvertString("Prompt"));
			}
		}
		else
		{
			MessageBox(ConvertString("Get VideoColor data failed!"), ConvertString("Prompt"));
		}
		
		if(szOutBuffer)
		{
			delete[] szOutBuffer;
			szOutBuffer = NULL;
		}
		
	}
	else
	{
		MessageBox(ConvertString("Login first!"), ConvertString("Prompt"));
	}
}
void CClientDemo5Dlg::SetFTPEXConfigInfo(CFG_NAS_INFO_EX *pstNasInfoEx,int nCurChannel)
{

	if(0 != m_LoginID)
	{
		if(NULL == pstNasInfoEx)
		{
			return;
		}
		if(nCurChannel < 0 || nCurChannel >= CHANNEL_NUM_LIMIT)
		{
			return;
		}
		char *szOutBuffer = new char[256*1024];
		if(NULL == szOutBuffer)
		{
			return;
		}
		
		int nerror   = 0;
		int nrestart = 0;
		
		BOOL bRet = CLIENT_PacketData(CFG_CMD_NASEX, (char *)pstNasInfoEx, sizeof(CFG_NAS_INFO_EX), szOutBuffer, 256*1024);
		if(bRet)
		{
			BOOL bSuccess = CLIENT_SetNewDevConfig(m_LoginID, CFG_CMD_NASEX, nCurChannel, szOutBuffer, 256*1024, &nerror, &nrestart, 6000);
			if(bSuccess)
			{
				if (nrestart == 1)
				{
					MessageBox(ConvertString("Save config info successfully!devide need restart!"), ConvertString("Prompt"));
				}
				
			}
			else
			{
				MessageBox(ConvertString("Save config info failed!"), ConvertString("Prompt"));
			}
			
		}
		else
		{
			MessageBox(ConvertString("Pack data failed!"), ConvertString("Prompt"));
		}
		if(szOutBuffer)
		{
			delete[] szOutBuffer;
			szOutBuffer = NULL;
		}
	}
	else
	{
		MessageBox(ConvertString("Login first!"), ConvertString("Prompt"));
	}
	
}
void CClientDemo5Dlg::GetFTPEXConfigInfo(CFG_NAS_INFO_EX *pstNasInfoEx,int nCurChannel)
{
	if(0 != m_LoginID)
	{
		if(NULL == pstNasInfoEx)
		{
			return;
		}
		if(nCurChannel < 0 || nCurChannel >= CHANNEL_NUM_LIMIT)
		{
			return ;
		}
		char *szOutBuffer = new char[256*1024];
		if(NULL == szOutBuffer)
		{
			return;
		}		
		memset(pstNasInfoEx, 0, sizeof(CFG_NAS_INFO_EX));
		
		int nerror = 0;
		
		BOOL bSuccess = CLIENT_GetNewDevConfig(m_LoginID, CFG_CMD_NASEX, nCurChannel, szOutBuffer, 256*1024, &nerror, 3000);
		if(bSuccess)
		{
			int nRetLen = 0;
			BOOL bRet = CLIENT_ParseData(CFG_CMD_NASEX, szOutBuffer, pstNasInfoEx, sizeof(CFG_NAS_INFO_EX),&nRetLen);
			if(!bRet)
			{
				MessageBox(ConvertString("VideoColor Parse data error"), ConvertString("Prompt"));
			}
		}
		else
		{
			MessageBox(ConvertString("Get VideoColor data failed!"), ConvertString("Prompt"));
		}
		
		if(szOutBuffer)
		{
			delete[] szOutBuffer;
			szOutBuffer = NULL;
		}
		
	}
	else
	{
		MessageBox(ConvertString("Login first!"), ConvertString("Prompt"));
	}
}
void CClientDemo5Dlg::GetFtpExInfo()
{
	if(0 != m_LoginID)
	{
		m_configFTPMain.InitDlgInfo();
	}
	else
	{
		MessageBox(ConvertString("Login first!"), ConvertString("Prompt"));
	}
}

void CClientDemo5Dlg::GetChannelConfigInfoEx()
{
    if(0 != m_LoginID)
    {
        m_channelDlgEx.InitDlgInfo(m_nChannel, m_nVideoStandard);
    }
    else
    {
        MessageBox(ConvertString("Login first!"), ConvertString("Prompt"));
    }
}

void CClientDemo5Dlg::GetRemoteStorageLimit(CFG_REMOTE_STORAGELIMIT_GROUP *pstRemoteStorage, int nCurChannel)
{
    if(0 == m_LoginID)
	{
        MessageBox(ConvertString("Login first!"), ConvertString("Prompt"));
		return;
	}
	if(NULL == pstRemoteStorage)
	{
		return;
	}
	if(nCurChannel < 0 || nCurChannel >= CHANNEL_NUM_LIMIT)
	{
		return ;
	}
    std::string outBuffer(512*1024, 0);
	//memset(pstRemoteStorage, 0, sizeof(CFG_REMOTE_STORAGELIMIT_GROUP));

	int nerror = 0;
	BOOL bSuccess = CLIENT_GetNewDevConfig(m_LoginID, CFG_CMD_REMOTE_STORAGE_LIMIT, nCurChannel, &outBuffer[0], outBuffer.capacity(), &nerror, 3000);
	if(bSuccess)
	{
		int nRetLen = 0;
		BOOL bRet = CLIENT_ParseData(CFG_CMD_REMOTE_STORAGE_LIMIT, &outBuffer[0], pstRemoteStorage, sizeof(CFG_REMOTE_STORAGELIMIT_GROUP),&nRetLen);
		if(!bRet)
		{
			MessageBox(ConvertString("RemoteStorageLimit Parse data error!"), ConvertString("Prompt"));
		}
	}
	else
	{
        // int nError = (0x7fffffff&CLIENT_GetLastError());
		MessageBox(ConvertString("Get RemoteStorageLimit data failed!"), ConvertString("Prompt"));
	}
	
}

void CClientDemo5Dlg::SetRemoteStorageLimit(CFG_REMOTE_STORAGELIMIT_GROUP *pstRemoteStorage, int nCurChannel)
{
    if(0 == m_LoginID)
    {
        MessageBox(ConvertString("Login first!"), ConvertString("Prompt"));
        return;
    }
    if(NULL == pstRemoteStorage)
    {
        return;
    }
    if(nCurChannel < 0 || nCurChannel >= CHANNEL_NUM_LIMIT)
    {
        return ;
    }
    char *szOutBuffer = new char[256*1024];
    if(NULL == szOutBuffer)
    {
        return;
    }
    memset(szOutBuffer, 0, 256*1024);
    int nerror   = 0;
    int nrestart = 0;
    
    BOOL bRet = CLIENT_PacketData(CFG_CMD_REMOTE_STORAGE_LIMIT, (char *)pstRemoteStorage, sizeof(CFG_REMOTE_STORAGELIMIT_GROUP), szOutBuffer, 256*1024);
    if(bRet)
    {
        BOOL bSuccess = CLIENT_SetNewDevConfig(m_LoginID, CFG_CMD_REMOTE_STORAGE_LIMIT, nCurChannel, szOutBuffer, 256*1024, &nerror, &nrestart, 6000);
        if(bSuccess)
        {
            if (nrestart == 1)
            {
                MessageBox(ConvertString("Save config info successfully!devide need restart!"), ConvertString("Prompt"));
            }
            
        }
        else
        {
            MessageBox(ConvertString("Save config info failed!"), ConvertString("Prompt"));
        }
        
    }
    else
    {
        MessageBox(ConvertString("Pack data failed!"), ConvertString("Prompt"));
    }
    if(szOutBuffer)
    {
        delete[] szOutBuffer;
        szOutBuffer = NULL;
	}    
}

BOOL CClientDemo5Dlg::GetMailConfig(CFG_EMAIL_INFO& stuMailInfo)
{
    BOOL bRet = FALSE;
    int nBufferLen = 32 * 1024;
    char *szOutBuffer = new char[nBufferLen];
    if(NULL == szOutBuffer)
    {
        return bRet;
    }
    memset(szOutBuffer, 0, nBufferLen);
    int nerror = 0;
    BOOL bSuccess = CLIENT_GetNewDevConfig(m_LoginID, CFG_CMD_EMAIL, -1, 
        szOutBuffer, nBufferLen, &nerror, SDK_DEMO_WAITTIME);
    if(bSuccess)
    {
        int nRetLen = 0;
        BOOL bRetParse = CLIENT_ParseData(CFG_CMD_EMAIL, szOutBuffer, &stuMailInfo, 
            sizeof(CFG_EMAIL_INFO),&nRetLen);
        if(bRetParse)
        {
            bRet = TRUE;
        }
        else
        {
            MessageBox(ConvertString("MailConfig Parse data error!"), ConvertString("Prompt"));
        }
	}
    else
    {
        MessageBox(ConvertString("Get MailConfig data failed!"), ConvertString("Prompt"));
    }
    
    if(szOutBuffer)
    {
        delete[] szOutBuffer;
        szOutBuffer = NULL;
	}
    return bRet;
}

BOOL CClientDemo5Dlg::SetMailConfig(CFG_EMAIL_INFO& stuMailInfo)
{
    BOOL bRet = FALSE;
    int nBufferLen = 32*1024;
    char *szOutBuffer = new char[nBufferLen];
    if(NULL == szOutBuffer)
    {
        return bRet;
    }
    memset(szOutBuffer, 0, nBufferLen);
    int nerror   = 0;
    int nrestart = 0;
    BOOL bRetPacket = CLIENT_PacketData(CFG_CMD_EMAIL, (char *)&stuMailInfo, sizeof(CFG_EMAIL_INFO), 
        szOutBuffer, nBufferLen);
    if(bRetPacket)
    {
        BOOL bSuccess = CLIENT_SetNewDevConfig(m_LoginID, CFG_CMD_EMAIL, -1, 
            szOutBuffer, nBufferLen, &nerror, &nrestart, SDK_DEMO_WAITTIME);
        if(bSuccess)
        {
            if (nrestart == 1)
            {
                MessageBox(ConvertString("Save config info successfully!devide need restart!"), 
                    ConvertString("Prompt"));
            }
            bRet = TRUE;
        }
        else
        {
            MessageBox(ConvertString("Save mail config info failed!"), ConvertString("Prompt"));
        }
    }
    else
    {
        MessageBox(ConvertString("Packet MailConfig data failed!"), ConvertString("Prompt"));
    }
    if(szOutBuffer)
    {
        delete[] szOutBuffer;
        szOutBuffer = NULL;
	} 
    return bRet;
}

BOOL CClientDemo5Dlg::GetDVRIPConfig(CFG_DVRIP_INFO& stuDVRIPInfo, int nWaitTime)
{
    BOOL bRet = FALSE;
    int nBufferLen = 32 * 1024;
    char *szOutBuffer = new char[nBufferLen];
    if(NULL == szOutBuffer)
    {
        return bRet;
    }
    memset(szOutBuffer, 0, nBufferLen);
    int nerror = 0;
    BOOL bSuccess = CLIENT_GetNewDevConfig(m_LoginID, CFG_CMD_DVRIP, -1, 
        szOutBuffer, nBufferLen, &nerror, nWaitTime);
    if(bSuccess)
    {
        int nRetLen = 0;
        BOOL bRetParse = CLIENT_ParseData(CFG_CMD_DVRIP, szOutBuffer, &stuDVRIPInfo, 
            sizeof(stuDVRIPInfo),&nRetLen);
        if(bRetParse)
        {
            bRet = TRUE;
        }
        else
        {
            MessageBox(ConvertString("Parse net transmission strategy data error!"), ConvertString("Prompt"));
        }
    }
    else
    {
        MessageBox(ConvertString("get net transmission strategy failed!"), ConvertString("Prompt"));
    }
    
    if(szOutBuffer)
    {
        delete[] szOutBuffer;
        szOutBuffer = NULL;
    }
    return bRet;
}

BOOL CClientDemo5Dlg::SetDVRIPConfig(CFG_DVRIP_INFO& stuDVRIPInfo, int nWaitTime)
{
    BOOL bRet = FALSE;
    int nBufferLen = 32*1024;
    char *szOutBuffer = new char[nBufferLen];
    if(NULL == szOutBuffer)
    {
        return bRet;
    }
    memset(szOutBuffer, 0, nBufferLen);
    int nerror   = 0;
    int nrestart = 0;
    BOOL bRetPacket = CLIENT_PacketData(CFG_CMD_DVRIP, (char *)&stuDVRIPInfo, sizeof(CFG_DVRIP_INFO), 
        szOutBuffer, nBufferLen);
    if(bRetPacket)
    {
        BOOL bSuccess = CLIENT_SetNewDevConfig(m_LoginID, CFG_CMD_DVRIP, -1, 
            szOutBuffer, nBufferLen, &nerror, &nrestart, nWaitTime);
        if(bSuccess)
        {
            if (nrestart == 1)
            {
                MessageBox(ConvertString("Save config info successfully!devide need restart!"), 
                    ConvertString("Prompt"));
            }
            bRet = TRUE;
        }
        else
        {
            MessageBox(ConvertString("save net transmission strategy failed!"), ConvertString("Prompt"));
        }
    }
    else
    {
        MessageBox(ConvertString("Packet net transmission strategy failed!"), ConvertString("Prompt"));
    }
    if(szOutBuffer)
    {
        delete[] szOutBuffer;
        szOutBuffer = NULL;
    } 
    return bRet;
}

BOOL CClientDemo5Dlg::GetVideoDetectCaps(NET_IN_VIDEO_DETECT_CAPS& stuInParam , NET_OUT_VIDEO_DETECT_CAPS& stuOutParam)
{
    return CLIENT_GetDevCaps(m_LoginID, NET_VIDEO_DETECT_CAPS  , &stuInParam , &stuOutParam, 1000);
}
