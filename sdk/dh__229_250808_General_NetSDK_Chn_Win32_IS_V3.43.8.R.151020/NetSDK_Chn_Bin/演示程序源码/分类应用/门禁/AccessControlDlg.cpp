// AccessControlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AccessControl.h"
#include "AccessControlDlg.h"

#include "DlgCapability.h"
#include "AlarmSubscribe.h"
#include "DlgVersion.h"
#include "DlgQueryLog.h"
#include "DlgDeviceTime.h"
#include "DlgUpgrade.h"
#include "DlgDoorControl.h"
#include "DlgUserManage.h"
#include "DlgRecordSetControl.h"
#include "RecordSetFinder.h"

#include "DlgCfgNetwork.h"
#include "DlgCfgAccessControlGeneral.h"
#include "DlgCfgAccessControl.h"
#include "DlgCfgTimeSchedule.h"
#include "DlgCfgNTP.h"

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
// CAccessControlDlg dialog

CAccessControlDlg::CAccessControlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAccessControlDlg::IDD, pParent)
	, m_lLoginID(0)
	, m_nVideoInput(0)
	, m_nAlarmIn(0)
	, m_nAlarmOut(0)
	, m_nAccessGroup(0)
{
	//{{AFX_DATA_INIT(CAccessControlDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAccessControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAccessControlDlg)
	DDX_Control(pDX, IDC_LIST_INFOPRINT, m_lstPrint);
	DDX_Control(pDX, IDC_CMB_CONTROLQUERY, m_cmbControlQueryType);
	DDX_Control(pDX, IDC_CMB_CONFIG, m_cmbConfig);
	DDX_Control(pDX, IDC_IPADDRESS, m_DvrIPAddr);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAccessControlDlg, CDialog)
	//{{AFX_MSG_MAP(CAccessControlDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_DEVICE_DISCONNECTED, OnDeviceDisconnected)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_LOGIN, OnBtnLogin)
	ON_BN_CLICKED(IDC_BTN_LOGOUT, OnBtnLogout)
	ON_BN_CLICKED(IDC_BTN_CAPABILITY, OnBtnCapability)
	ON_BN_CLICKED(IDC_BTN_SUBSCIBE, OnBtnSubscibe)
	ON_BN_CLICKED(IDC_BTN_RECORDSET_CONTROL, OnBtnRecordsetControl)
	ON_BN_CLICKED(IDC_BTN_RECORDSET_FIND, OnBtnRecordsetFind)
	ON_BN_CLICKED(IDC_BTN_CONTROLQUERY, OnBtnControlQuery)
	ON_BN_CLICKED(IDC_BTN_CONFIG, OnBtnConfig)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// private method handlers

void CALLBACK DemoDisConnectCallBack(LLONG lLoginID, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser)
{
	if(0 != dwUser)
	{
		CAccessControlDlg *dlg = (CAccessControlDlg *)dwUser;
		
		// 在该线程由SDK内部维护，弹窗将阻塞线程，应当异步传递消息
		char* szIp = new char[strlen(pchDVRIP) + 1];
		assert(szIp);
		memset(szIp, 0, strlen(pchDVRIP) + 1);
		strncpy(szIp, pchDVRIP, strlen(pchDVRIP));
		dlg->PostMessage(WM_DEVICE_DISCONNECTED, (WPARAM)szIp, (LPARAM)nDVRPort);
	}
}

LRESULT CAccessControlDlg::OnDeviceDisconnected(WPARAM wParam, LPARAM lParam)
{
	if (wParam && lParam)
	{
		char* szIp = (char*)wParam;
		
		CString csOut;
		csOut.Format("%s:%s:%d %s!", ConvertString("Device"), (char*)szIp, (LONG)lParam, ConvertString("disconnected"));
		MessageBox(csOut, ConvertString("Prompt"));
		
		delete[]szIp;
		szIp = NULL;

		OnBtnLogout();
	}
	return 0;
}

void CAccessControlDlg::InitDlg()
{
	//Set initial IP address, port, user name, password
	{
		CString csIp = ConvertString("ip", DEVICE_PARAM);
		if (csIp == CString("ip"))
		{
			m_DvrIPAddr.SetWindowText("172.23.2.72");
		} 
		else
		{
			m_DvrIPAddr.SetWindowText(csIp);
		}
		
		CString csPort = ConvertString("port", DEVICE_PARAM);
		if (csPort == CString("port"))
		{
			SetDlgItemInt(IDC_EDT_PORT, 37777);
		} 
		else
		{
			GetDlgItem(IDC_EDT_PORT)->SetWindowText(csPort);
		}
		
		CString csName = ConvertString("username", DEVICE_PARAM);
		if (csName == CString("username"))
		{
			GetDlgItem(IDC_EDT_NAME)->SetWindowText("system");
		} 
		else
		{
			GetDlgItem(IDC_EDT_NAME)->SetWindowText(csName);
		}
		
		CString csPsw = ConvertString("password", DEVICE_PARAM);
		if (csPsw == CString("password"))
		{
			GetDlgItem(IDC_EDT_PWD)->SetWindowText("123456");
		} 
		else
		{
			GetDlgItem(IDC_EDT_PWD)->SetWindowText(csPsw);
		}
	}

	{
		m_cmbConfig.ResetContent();
		for (int i = 0; i < sizeof(stuDemoEmConfigType) / sizeof(stuDemoEmConfigType[0]); i++)
		{
			m_cmbConfig.InsertString(-1, ConvertString(stuDemoEmConfigType[i].szName, DLG_MAIN));
		}
		m_cmbConfig.SetCurSel(-1);
		
		m_cmbControlQueryType.ResetContent();
		for (int j = 0; j < sizeof(stuDemoEmControlQueryType) / sizeof(stuDemoEmControlQueryType[0]); j++)
		{
			m_cmbControlQueryType.InsertString(-1, ConvertString(stuDemoEmControlQueryType[j].szName, DLG_MAIN));
		}
		m_cmbControlQueryType.SetCurSel(-1);
	}

	GetDlgItem(IDC_BTN_LOGOUT)->EnableWindow(FALSE);
}

BOOL CAccessControlDlg::InitNetSDK()
{
	NET_PARAM stuParam = {0};
	
	CString csConnectBufSize = ConvertString("ConnectBufSize", SDK_PARAM);
	if (csConnectBufSize == CString("ConnectBufSize"))
	{
		stuParam.nConnectBufSize = 250 * 1024;
	}
	else
	{
		stuParam.nConnectBufSize = atoi(csConnectBufSize.GetBuffer(0));
	}
	
	CString csConnectTime = ConvertString("ConnectTime", SDK_PARAM);
	if (csConnectTime == CString("ConnectTime"))
	{
		stuParam.nConnectTime = 1500;
	} 
	else
	{
		stuParam.nConnectTime = atoi(csConnectTime.GetBuffer(0));
	}
	
	CString csConnectTryNum = ConvertString("ConnetTryNum", SDK_PARAM);
	if (csConnectTryNum == CString("ConnetTryNum"))
	{
		stuParam.nConnectTryNum = 1;
	} 
	else
	{
		stuParam.nConnectTryNum = atoi(csConnectTryNum.GetBuffer(0));
	}
	
	CString csGetDevInfoTime = ConvertString("GetDevInfoTime", SDK_PARAM);
	if (csGetDevInfoTime == CString("GetDevInfoTime"))
	{
		stuParam.nGetDevInfoTime = 5000;
	} 
	else
	{
		stuParam.nGetDevInfoTime = atoi(csGetDevInfoTime.GetBuffer(0));
	}
	
	CString csWaitTime = ConvertString("WaitTime", SDK_PARAM);
	if (csWaitTime == CString("WaitTime"))
	{
		stuParam.nWaittime = 5000;
	} 
	else
	{
		stuParam.nWaittime = atoi(csWaitTime.GetBuffer(0));
	}
	
	CLIENT_SetNetworkParam(&stuParam);

	return CLIENT_Init(DemoDisConnectCallBack, (LDWORD)this);
}

//Display log in failure reason 
void CAccessControlDlg::ShowLoginErrorReason(int nError)
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

void CAccessControlDlg::PrintInfo(const CString& csInfo)
{

}

BOOL CAccessControlDlg::GetAccessCount(int& nCount)
{
    char szBuf[1024] = {0};
    int nError = 0;
    BOOL bRet = CLIENT_QueryNewSystemInfo(m_lLoginID, CFG_CAP_CMD_ACCESSCONTROLMANAGER, -1, szBuf, sizeof(szBuf), &nError, 3000);
    if (bRet)
    {
        CFG_CAP_ACCESSCONTROL stuCap = {0};
        DWORD dwRet = 0;
        bRet = CLIENT_ParseData(CFG_CAP_CMD_ACCESSCONTROLMANAGER, szBuf, &stuCap, sizeof(stuCap), &dwRet);
        if (bRet && dwRet == sizeof(CFG_CAP_ACCESSCONTROL))
        {
            nCount = stuCap.nAccessControlGroups;
        }
        else
        {
            return FALSE;
        }
    }
    else
    {
        return FALSE;
	}
    return TRUE;
}

void CAccessControlDlg::CQofVersion()
{
	CDlgVersion dlg(this, m_lLoginID);
	dlg.DoModal();
}

void CAccessControlDlg::CQofReboot()
{
	if (MessageBox(ConvertString("Are you sure to reboot?"), ConvertString("Prompt"), MB_YESNO) == IDYES)
	{
		BOOL bRet = CLIENT_ControlDevice(m_lLoginID, DH_CTRL_REBOOT, NULL, 3000);
		if (!bRet)
		{
			CString csInfo;
			csInfo.Format("%s0x%08x", ConvertString("Reboot failed:"), CLIENT_GetLastError());
			MessageBox(csInfo, ConvertString("Prompt"));
		}
	}
}

void CAccessControlDlg::CQofRestoreAll()
{
	if (MessageBox(ConvertString("Are you sure to restore all?"), ConvertString("Prompt"), MB_YESNO) == IDYES)
	{
		BOOL bRet = CLIENT_ControlDevice(m_lLoginID, DH_CTRL_RESTOREDEFAULT, NULL, 3000);
		if (!bRet)
		{
			CString csInfo;
			csInfo.Format("%s0x%08x", ConvertString("Restore all failed:"), CLIENT_GetLastError());
			MessageBox(csInfo, ConvertString("Prompt"));
		}
	}
}

void CAccessControlDlg::CQofDoor()
{
	CDlgDoorControl dlg(this, m_lLoginID);
	dlg.DoModal();
}

void CAccessControlDlg::CQofLog()
{
	CDlgQueryLog dlg(this, m_lLoginID);
	dlg.DoModal();
}

void CAccessControlDlg::CQofMac()
{	
	DHDEV_NETINTERFACE_INFO stuInfo[DH_MAX_NETINTERFACE_NUM] = {0};
	for (int i = 0; i < DH_MAX_NETINTERFACE_NUM; i++)
	{
		stuInfo[i].dwSize = sizeof(DHDEV_NETINTERFACE_INFO);
	}
	int nRet = 0;
	BOOL bRet = CLIENT_QueryDevState(m_lLoginID, DH_DEVSTATE_NETINTERFACE, (char*)&stuInfo, sizeof(stuInfo) * DH_MAX_NETINTERFACE_NUM, &nRet, 3000);
	if (bRet)
	{
		MessageBox(stuInfo[0].szMAC, ConvertString("Prompt"));
	}
	else
	{
		CString csInfo;
		csInfo.Format("%s0x%08x", ConvertString("Get Mac failed:"), CLIENT_GetLastError());
		MessageBox(csInfo, ConvertString("Prompt"));
	}
}

void CAccessControlDlg::CQofTime()
{
	CDlgDeviceTime dlg(this, m_lLoginID);
	dlg.DoModal();
}

void CAccessControlDlg::CQofUpgrade()
{
	CDlgUpgrade dlg(this, m_lLoginID);
	dlg.DoModal();
}

void CAccessControlDlg::CQofModifyPwd()
{
	CDlgUserManage dlg(this, m_lLoginID);
	dlg.DoModal();
}

void CAccessControlDlg::CFGofNetwork()
{
	CDlgCfgNetwork dlg(this, m_lLoginID);
	dlg.DoModal();
}

void CAccessControlDlg::CFGofAccessControlGeneral()
{
	CDlgCfgAccessControlGeneral dlg(this, m_lLoginID);
	dlg.DoModal();
}

void CAccessControlDlg::CFGofAccessControl()
{
	CDlgCfgAccessControl dlg(this, m_lLoginID);
	dlg.DoModal();
}

void CAccessControlDlg::CFGofAccessTimeSechdule()
{
	CDlgCfgTimeSchedule dlg(this, m_lLoginID);
	dlg.DoModal();
}

void CAccessControlDlg::CFGofNTP()
{
	CDlgCfgNTP dlg(this, m_lLoginID);
	dlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CAccessControlDlg message handlers

BOOL CAccessControlDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
    g_SetWndStaticText(this, DLG_MAIN);
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
	InitDlg();
	InitNetSDK();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAccessControlDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CAccessControlDlg::OnPaint() 
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
HCURSOR CAccessControlDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CAccessControlDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
    if (pMsg->message == WM_KEYDOWN || pMsg->message == WM_KEYUP)
    {
        if (VK_ESCAPE == pMsg->wParam)
        {
            if (MessageBox(ConvertString("Exit?"), ConvertString("Prompt"), MB_YESNO) != IDYES)
            {
                return TRUE;
            }
        }
        else if (VK_RETURN == pMsg->wParam)
        {
            return TRUE;
        }
    }
	return CDialog::PreTranslateMessage(pMsg);
}

void CAccessControlDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	OnBtnLogout();
	CLIENT_Cleanup();
}

void CAccessControlDlg::OnBtnLogin() 
{
	// TODO: Add your control notification handler code here
	CString csIp;
	m_DvrIPAddr.GetWindowText(csIp);

	unsigned short sPort = GetDlgItemInt(IDC_EDT_PORT, NULL, FALSE);

	CString csName;
	GetDlgItemText(IDC_EDT_NAME, csName);

	CString csPwd;
	GetDlgItemText(IDC_EDT_PWD, csPwd);

	NET_DEVICEINFO stuInfo = {0};
	int nErr = 0;
	LLONG lLoginID = CLIENT_LoginEx(csIp.GetBuffer(0), sPort, csName.GetBuffer(0), csPwd.GetBuffer(0), 0, NULL, &stuInfo, &nErr);
	if (lLoginID != NULL)
	{
		m_lLoginID	= lLoginID;
		m_emType	= (NET_DEVICE_TYPE)stuInfo.byDVRType;
		m_nAlarmIn	= stuInfo.byAlarmInPortNum;
		m_nAlarmOut = stuInfo.byAlarmOutPortNum;
		
		GetDlgItem(IDC_IPADDRESS)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDT_PORT)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDT_NAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDT_PWD)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_LOGIN)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_LOGOUT)->EnableWindow();

        GetAccessCount(m_nAccessGroup);
	}
	else
	{
		ShowLoginErrorReason(nErr);
	}
}

void CAccessControlDlg::OnBtnLogout() 
{
	// TODO: Add your control notification handler code here
	if (m_lLoginID != NULL)
	{
		CLIENT_Logout(m_lLoginID);
		m_lLoginID = NULL;

		GetDlgItem(IDC_IPADDRESS)->EnableWindow();
		GetDlgItem(IDC_EDT_PORT)->EnableWindow();
		GetDlgItem(IDC_EDT_NAME)->EnableWindow();
		GetDlgItem(IDC_EDT_PWD)->EnableWindow();
		GetDlgItem(IDC_BTN_LOGIN)->EnableWindow();
		GetDlgItem(IDC_BTN_LOGOUT)->EnableWindow(FALSE);
	}
}

void CAccessControlDlg::OnBtnCapability() 
{
	// TODO: Add your control notification handler code here
	CDlgCapability dlg(this, m_lLoginID, m_nAlarmIn, m_nAlarmOut);
	dlg.DoModal();
}

void CAccessControlDlg::OnBtnSubscibe() 
{
	// TODO: Add your control notification handler code here
	AlarmSubscribe dlg(this, m_lLoginID, m_nAlarmIn, m_nAccessGroup);
	dlg.DoModal();
}

void CAccessControlDlg::OnBtnRecordsetControl() 
{
	// TODO: Add your control notification handler code here
	CDlgRecordSetControl dlg(this, m_lLoginID, m_nAccessGroup);
	dlg.DoModal();
}

void CAccessControlDlg::OnBtnRecordsetFind() 
{
	// TODO: Add your control notification handler code here
	CRecordSetFinder dlg(this, m_lLoginID, m_nAccessGroup);
	dlg.DoModal();
}

void CAccessControlDlg::OnBtnControlQuery() 
{
	// TODO: Add your control notification handler code here
	int nCurSel = m_cmbControlQueryType.GetCurSel();
	switch (nCurSel)
	{
	case EM_CONTROL_QUERY_VERSION:
		CQofVersion();
		break;
	case EM_CONTROL_QUERY_REBOOT:
		CQofReboot();
		break;
	case EM_CONTROL_QUERY_RESTOREALL:
		CQofRestoreAll();
		break;
	case EM_CONTROL_QUERY_DOOR_CONTROL:
		CQofDoor();
		break;
	case EM_CONTROL_QUERY_LOG:
		CQofLog();
		break;
	case EM_CONTROL_QUERY_MAC:
		CQofMac();
		break;
	case EM_CONTROL_QUERY_TIME:
		CQofTime();
		break;
	case EM_CONTROL_QUERY_UPGRADE:
		CQofUpgrade();
		break;
	case EM_CONTROL_QUERY_MODIFY_PWD:
		CQofModifyPwd();
		break;
	default:
		break;
	}
}

void CAccessControlDlg::OnBtnConfig() 
{
	// TODO: Add your control notification handler code here
	int nCurSel = m_cmbConfig.GetCurSel();
	switch (nCurSel)
	{
	case EM_CONFIG_NETWORK:
		CFGofNetwork();
		break;
	case EM_CONFIG_ACCESSCONTROL_GENERAL:
		CFGofAccessControlGeneral();
		break;
	case EM_CONFIG_ACCESSCONTROL:
		CFGofAccessControl();
		break;
	case EM_CONFIG_ACCESS_TIMESECHDULE:
		CFGofAccessTimeSechdule();
		break;
	case EM_CONFIG_NTP:
		CFGofNTP();
		break;
	default:
		break;
	}
}
