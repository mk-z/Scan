// ClientDemo4Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "ClientDemo4.h"
#include "ClientDemo4Dlg.h"
#include "ClientDlg.h"
#include "ServerDlg.h"

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
// CClientDemo4Dlg dialog

CClientDemo4Dlg::CClientDemo4Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClientDemo4Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CClientDemo4Dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bServer = FALSE;
}

void CClientDemo4Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClientDemo4Dlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CClientDemo4Dlg, CDialog)
	//{{AFX_MSG_MAP(CClientDemo4Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RADIO_CLIENT, OnRadioClient)
	ON_BN_CLICKED(IDC_RADIO_SERVER, OnRadioServer)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientDemo4Dlg message handlers
//Callback function when device disconnected
void CALLBACK DisConnectFunc(LONG lLoginID, char *pchDVRIP, LONG nDVRPort, DWORD dwUser)
{
	AfxMessageBox(ConvertString("Network disconnected!"));
}

BOOL CClientDemo4Dlg::OnInitDialog()
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
	CLIENT_Init(DisConnectFunc, (DWORD)this);
    
	// 初始化成功后设置网络参数
	NET_PARAM stuNetParam = {0};
	// 目前仅单独设置获取设备信息时间（部分设备因性能问题，没法在默认时间内完成，其他参数暂时保持默认）
	stuNetParam.nGetDevInfoTime = 3000;
	CLIENT_SetNetworkParam(&stuNetParam);
	
	((CButton*)GetDlgItem(IDC_RADIO_CLIENT))->SetCheck(1);
	UpdateData(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CClientDemo4Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CClientDemo4Dlg::OnPaint() 
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
HCURSOR CClientDemo4Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CClientDemo4Dlg::OnOK() 
{
	// TODO: Add extra validation here
	//this->ShowWindow(SW_HIDE);
	if (m_bServer)
	{
		CServerDlg dlg;
		dlg.DoModal();
	}
	else
	{
		CClientDlg dlg;
		dlg.DoModal();
	}
	
	//CDialog::OnOK();
}

void CClientDemo4Dlg::OnRadioClient() 
{
	// TODO: Add your control notification handler code here
	m_bServer = FALSE;
}

void CClientDemo4Dlg::OnRadioServer() 
{
	// TODO: Add your control notification handler code here
	m_bServer = TRUE;
}

void CClientDemo4Dlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	CLIENT_Cleanup();

	CDialog::OnClose();
}










































