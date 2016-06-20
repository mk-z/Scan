// Real Load PictureDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Real Load Picture.h"
#include "Real Load PictureDlg.h"
#include "Utility.h"
#include "DialogConfig.h"

#include <iostream>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
CPlayAPI g_PlayAPI;

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
// CRealLoadPictureDlg dialog

CRealLoadPictureDlg::CRealLoadPictureDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRealLoadPictureDlg::IDD, pParent)
{
	m_lLoginID = 0;
	//{{AFX_DATA_INIT(CRealLoadPictureDlg)
	m_csUserName = _T("");
	m_nPort = 0;
	m_csPassword = _T("");

	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	g_PlayAPI.LoadPlayDll();
}

void CRealLoadPictureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRealLoadPictureDlg)
	DDX_Control(pDX, IDC_IPADDRESS_IP, m_ipcIP);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_csUserName);
	DDX_Text(pDX, IDC_EDIT_PORT, m_nPort);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_csPassword);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRealLoadPictureDlg, CDialog)
	//{{AFX_MSG_MAP(CRealLoadPictureDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_EVENT_RULE, OnButtonEventRule)
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, OnButtonLogin)
	ON_BN_CLICKED(IDC_BUTTON_LOGOUT, OnButtonLogout)
	ON_BN_CLICKED(IDC_BUTTON_DATA_QUERY, OnButtonDataQuery)
	//}}AFX_MSG_MAP
	ON_WM_CLOSE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRealLoadPictureDlg message handlers

BOOL CRealLoadPictureDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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


	::CoInitialize(NULL);
	
	//数据保存文件夹的设置
	CDialogConfig dlgCfg;
	dlgCfg.DoModal();

	//读取数据文件夹的位置
	string strCfgFilePath;
	string strCfgDefaultFolder;
	GetModulePath("dhnetsdk.dll", strCfgFilePath);
	strCfgDefaultFolder = strCfgFilePath;
	strCfgFilePath.append(CFG_CFG_FILE_NAME);
	strCfgDefaultFolder.append(PC_DATA_STORE_FOLDER);
	char szFolder[1024] = {0};
	::GetPrivateProfileString(CFG_SECTION_CFG, CFG_KEY_DATA_PATH, strCfgDefaultFolder.c_str(), szFolder, 1024, strCfgFilePath.c_str());

	//Create direct any way
	::CreateDirectory(szFolder, NULL);
	
	// TODO: Add extra initialization here
	g_SetWndStaticText(this);
	/************************************************************************/
	/* 初始化两个对话框                                                     */
	/************************************************************************/
	const int LEFT_SIZE = 5;	//左侧间距
	const int TOP_SIZE	= 95;	//顶部间距
	RECT dlgRect = {0};
	m_dlgEventRule.Create(IDD_DIALOG_EVENT_RULE, this);
	m_dlgEventRule.GetWindowRect(&dlgRect);
	m_dlgEventRule.MoveWindow(LEFT_SIZE, TOP_SIZE, dlgRect.right - dlgRect.left, dlgRect.bottom - dlgRect.top, TRUE);
	m_dlgEventRule.ShowWindow(SW_SHOW);

	m_dlgPCQuery.Create(IDD_DIALOG_PC_QUERY, this);
	m_dlgPCQuery.GetWindowRect(&dlgRect);
	m_dlgPCQuery.MoveWindow(LEFT_SIZE, TOP_SIZE, dlgRect.right - dlgRect.left, dlgRect.bottom - dlgRect.top, TRUE);
	m_dlgPCQuery.ShowWindow(SW_HIDE);

	m_dlgEventRule.SetPCQueryDlg(&m_dlgPCQuery);
	m_dlgPCQuery.SetEventRuleDlg(&m_dlgEventRule);

	/************************************************************************/
	/*                                                                      */
	/************************************************************************/
	SetDlgItemText(IDC_IPADDRESS_IP, "192.168.20.25");
	SetDlgItemInt(IDC_EDIT_PORT, 37777);
	SetDlgItemText(IDC_EDIT_USERNAME, "admin");
	SetDlgItemText(IDC_EDIT_PASSWORD, "admin");
	
	/************************************************************************/
	/*                                                                      */
	/************************************************************************/
	CLIENT_Init(CRealLoadPictureDlg::OnDisConnect, (LDWORD)this);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CRealLoadPictureDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CRealLoadPictureDlg::OnPaint() 
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
HCURSOR CRealLoadPictureDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CRealLoadPictureDlg::OnButtonEventRule() 
{
	m_dlgPCQuery.ShowWindow(SW_HIDE);
	m_dlgEventRule.ShowWindow(SW_SHOW);
	m_dlgEventRule.DisplayFilter();
}

void CRealLoadPictureDlg::OnButtonDataQuery() 
{	
	m_dlgEventRule.ShowWindow(SW_HIDE);
	m_dlgPCQuery.ShowWindow(SW_SHOW);
}


void CRealLoadPictureDlg::OnDisConnect(LLONG lLoginID, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser)
{
	
	return;
}

void CRealLoadPictureDlg::OnButtonLogin() 
{
	if (UpdateData(TRUE) == FALSE)
	{
		return;
	}

	char szIp[32] = {0};
	m_ipcIP.GetWindowText(szIp, sizeof(szIp));
	NET_DEVICEINFO netDevInfo = {0};
	int error = 0;
	char* szUserName = m_csUserName.GetBuffer(0);
 	LONG lLoginID = CLIENT_Login(szIp, (WORD)m_nPort, m_csUserName.GetBuffer(0), m_csPassword.GetBuffer(0), &netDevInfo, &error);
	if (lLoginID == 0)
	{
		MessageBox(ConvertString("Login failed!"),ConvertString("Prompt"));
		return;
	}

	//Login ok
	m_lLoginID = lLoginID;
	GetDlgItem(IDC_BUTTON_LOGIN)->EnableWindow(FALSE);
	m_dlgEventRule.UpdateDeviceInfo(lLoginID, netDevInfo, TRUE);
}

void CRealLoadPictureDlg::OnButtonLogout() 
{
	if (m_lLoginID == 0)
	{
		MessageBox(ConvertString("Not login yet!"),ConvertString("Prompt"));
	}
	CLIENT_Logout(m_lLoginID);
	m_lLoginID = 0;

	GetDlgItem(IDC_BUTTON_LOGIN)->EnableWindow(TRUE);
	NET_DEVICEINFO netDevInfo = {0};
	m_dlgEventRule.UpdateDeviceInfo(0, netDevInfo, FALSE);
}



void CRealLoadPictureDlg::OnClose()
{
	CLIENT_Cleanup(); // 释放sdk资源
	CDialog::OnClose();
}

BOOL CRealLoadPictureDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg-> message   ==   WM_KEYDOWN) 
    { 
		switch(pMsg-> wParam) 
		{
		case   VK_RETURN://屏蔽回车 
			return   TRUE; 
		case   VK_ESCAPE://屏蔽Esc 
			return   TRUE; 
		} 
	 } 
	return CDialog::PreTranslateMessage(pMsg);
}
